//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �����o�[�g�g�U�Ɩ�
// 
// Created by Ryusei Kajiya on 20151009
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
float4x4 uniform_world_view_projection;
float4 uniform_light_direction;

//=============================================================================
// ���_�V�F�[�_
VertexShaderOutput VS(VertexShaderInput input)
{
	// �o�̓f�[�^�̗p��
	VertexShaderOutput output = (VertexShaderOutput)0;

	// ���W�ϊ�
	output.position = mul(float4(input.position, 1.0f), uniform_world_view_projection);

	// �@��
	output.normal = normalize(input.normal);

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
	color.xyz = max(dot(normal, light_direction), 0.0f);
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
		//CullMode = NONE;

		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();

		//CullMode = CCW;
	}
}