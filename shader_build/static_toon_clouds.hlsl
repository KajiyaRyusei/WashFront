//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �ÓI�_
// 
// Created by Ryusei Kajiya on 20151214
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

	float4 world_matrix_1 : TEXCOORD2;
	float4 world_matrix_2 : TEXCOORD3;
	float4 world_matrix_3 : TEXCOORD4;
	float4 world_matrix_4 : TEXCOORD5;
};

//-------------------------------------
// ���_�V�F�[�_�o��
//-------------------------------------
struct VertexShaderOutput
{
	float4 position	: POSITION;
	float3 normal	: TEXCOORD0;
	float2 texcoord	: TEXCOORD1;
	float3 world_position: TEXCOORD2;
	float depth : TEXCOORD3;
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
uniform float4x4 uniform_view_projection;
uniform float4x4 uniform_view;
uniform float4 uniform_light_direction;

// �e�N�X�`��
uniform texture uniform_diffuse_cube_texture;
uniform sampler uniform_diffuse_cube_sampler = sampler_state
{
	Texture = <uniform_diffuse_cube_texture>;
	MinFilter = ANISOTROPIC;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	MaxAnisotropy = 16;
	AddressU = WRAP;
	AddressV = WRAP;
};

uniform texture uniform_toon_texture;
uniform sampler uniform_toon_sampler = sampler_state {
	Texture = <uniform_toon_texture>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

//-------------------------------------
// �n�[�t�����o�[�g
float HalfLambert(
	float3 normal,
	float3 light_direction)
{
	float power = 0.f;
	power = dot(light_direction, normal) * 0.5f + 0.5f;
	return power;
}
//=============================================================================
// ���_�V�F�[�_
VertexShaderOutput VS(VertexShaderInput input)
{
	// �o�̓f�[�^�̗p��
	VertexShaderOutput output = (VertexShaderOutput)0;

	// ���W�ϊ�
	float4x4 world_matrix = (float4x4)0;

	world_matrix._11 = input.world_matrix_1.x;
	world_matrix._12 = input.world_matrix_1.y;
	world_matrix._13 = input.world_matrix_1.z;
	world_matrix._14 = input.world_matrix_1.w;

	world_matrix._21 = input.world_matrix_2.x;
	world_matrix._22 = input.world_matrix_2.y;
	world_matrix._23 = input.world_matrix_2.z;
	world_matrix._24 = input.world_matrix_2.w;

	world_matrix._31 = input.world_matrix_3.x;
	world_matrix._32 = input.world_matrix_3.y;
	world_matrix._33 = input.world_matrix_3.z;
	world_matrix._34 = input.world_matrix_3.w;

	world_matrix._41 = input.world_matrix_4.x;
	world_matrix._42 = input.world_matrix_4.y;
	world_matrix._43 = input.world_matrix_4.z;
	world_matrix._44 = input.world_matrix_4.w;

	float4x4 world_view_projection = mul(world_matrix, uniform_view_projection);

	// ���W�ϊ�
	output.position = mul(float4(input.position, 1.0f), world_view_projection);

	// ���[���h���W
	output.world_position = mul(float4(input.position, 1.0f), world_matrix).xyz;

	// �r���[�ϊ����_
	float3 world_view_position = mul(float4(output.world_position, 1.0f), uniform_view).xyz;
	output.depth = world_view_position.z / (5.f - 100.f);

	// �@��
	float4 normal = float4(input.normal.x, input.normal.y, input.normal.z, 0.f);
	output.normal = mul(normal, world_matrix).xyz;

	// �e�N�X�`�����W
	output.texcoord = input.texcoord;

	return output;
}

//=============================================================================
// �s�N�Z���V�F�[�_
PixelShaderOutput PS(VertexShaderOutput input)
{
	PixelShaderOutput output = (PixelShaderOutput)0;

	// �@��
	float3 normal = normalize(input.normal);

	// ����
	float3 diffuse_cube_ambient = texCUBE(uniform_diffuse_cube_sampler, input.normal).xyz;

	// �A���x�h
	float3 albedo = (diffuse_cube_ambient.xyz * 0.5f);

	// �g�U�Ɩ�
	float3 light_direction = -normalize(uniform_light_direction.xyz);
	float power = HalfLambert(normal, light_direction);

	// toon
	float3 toon_color = tex2D(uniform_toon_sampler, float2(power, 0.01f)).xyz;

	output.render_target0.xyz = toon_color + albedo;
	//output.render_target0.xyz *= 2.f;
	//output.render_target0.xyz *= output.render_target0.xyz;
	//output.render_target0.xyz = pow(output.render_target0.xyz, 2.2f);
	output.render_target0.a = 1.f;

	//output.render_target0 = (float4)1.f;

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
		CullMode = None;
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();
	}
}