//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �A�j���[�V����
// 
// Created by Ryusei Kajiya on 20151014
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//-------------------------------------
// ���_�V�F�[�_����
//-------------------------------------
struct VertexShaderInput
{
	float3 position	: POSITION0;
	float3 normal	: NORMAL0;
	float2 texcoord	: TEXCOORD0;
	float4 weight	: BLENDWEIGHT;
	int4  bone_index : BLENDINDICES;
};

//-------------------------------------
// ���_�V�F�[�_�o��
//-------------------------------------
struct VertexShaderOutput
{
	float4 position	: POSITION;
	float3 normal	: TEXCOORD0;
	float2 texcoord	: TEXCOORD1;
};

//-------------------------------------
// �s�N�Z���V�F�[�_�o��
//-------------------------------------
struct PixelShaderOutput
{
	float4 render_target0	: COLOR0;
	float4 render_target1	: COLOR1;
	float4 render_target2	: COLOR2;
	float4 render_target3	: COLOR3;
};

//=============================================================================
// ���j�t�H�[��
uniform float4x4 uniform_world_view_projection;
uniform float4 uniform_light_direction;
uniform float4x4 uniform_animation_matrix_list[40];

//=============================================================================
// ���_�V�F�[�_
VertexShaderOutput VS(VertexShaderInput input)
{
	// �o�̓f�[�^�̗p��
	VertexShaderOutput output = (VertexShaderOutput)0;

	// ���W�ϊ�
	float4x4 composition_matrix;
	composition_matrix = uniform_animation_matrix_list[input.bone_index[0]] * input.weight.x;
	composition_matrix += uniform_animation_matrix_list[input.bone_index[1]] * input.weight.y;
	composition_matrix += uniform_animation_matrix_list[input.bone_index[2]] * input.weight.z;
	composition_matrix += uniform_animation_matrix_list[input.bone_index[3]] * input.weight.w;
	float4 position = mul(float4(input.position, 1.0f), composition_matrix);
	output.position = mul(position, uniform_world_view_projection);


	// �@�����A�j���[�V�����ɍ��킹��
	float4 normal = float4(input.normal.x, input.normal.y, input.normal.z, 0.f);
	normal = mul(normal, composition_matrix);
	output.normal = normalize(normal).xyz;

	// �e�N�Z�����W
	output.texcoord = input.texcoord;

	return output;
}


//=============================================================================
// �s�N�Z���V�F�[�_
PixelShaderOutput PS(VertexShaderOutput input)
{
	PixelShaderOutput output = (PixelShaderOutput)0;

	// �F
	float4 color = (float4)0;
	float3 light_direction = -normalize(uniform_light_direction.xyz);
	float3 normal = normalize(input.normal);
	color.xyz = dot(normal, light_direction) * 0.5f + 0.5f;
	color.w = 1.f;

	output.render_target0 = color;

	//output.render_target0 = float4(1, 1, 1, 1);
	output.render_target1 = float4(1, 1, 1, 1);
	output.render_target2 = float4(1, 1, 1, 1);
	output.render_target3 = float4(1, 1, 1, 1);

	return output;
}


//=============================================================================
// �e�N�j�b�N
technique Techniques
{
	pass P0
	{

		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}
}