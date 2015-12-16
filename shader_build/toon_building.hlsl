//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �r���g�D�[��
// 
// Created by Ryusei Kajiya on 20151202
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//-------------------------------------
// ���_�V�F�[�_����
//-------------------------------------
struct VertexShaderInput
{
	float3 position	 : POSITION0;
	float3 normal	 : NORMAL0;
	float2 texcoord	 : TEXCOORD0;
	float3 tangent	 : TEXCOORD1;
	float cleanliness : TEXCOORD2;
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
	float3 world_tangent : TEXCOORD3;
	float cleanliness : TEXCOORD4;
	float depth : TEXCOORD5;
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

uniform texture uniform_albedo_texture;
uniform sampler uniform_albedo_sampler = sampler_state {
	Texture = <uniform_albedo_texture>;
	MinFilter = ANISOTROPIC;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	MaxAnisotropy = 16;
	AddressU = WRAP;
	AddressV = WRAP;
};

uniform texture uniform_normal_texture;
uniform sampler uniform_normal_sampler = sampler_state {
	Texture = <uniform_normal_texture>;
	MinFilter = ANISOTROPIC;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	MaxAnisotropy = 8;
	AddressU = WRAP;
	AddressV = WRAP;
};

uniform texture uniform_dirty_texture;
uniform sampler uniform_dirty_sampler = sampler_state {
	Texture = <uniform_dirty_texture>;
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

uniform float4x4 uniform_world_view_projection;
uniform float4x4 uniform_world;
uniform float4x4 uniform_view;
uniform float4 uniform_light_direction;
uniform float3 uniform_eye_position;
uniform float4 uniform_ambient_color;
uniform float2 uniform_texcoord_move;

//-------------------------------------
// �ڋ�Ԗ@�������[���h�@���ɕϊ�
float3 NormalSampler2WorldSpace(
	float3 normal_map_sampler,
	float3 normal_world,
	float3 tangent_world)
{
	float3 normal_t = normal_map_sampler * 2.f - 1.f;
	float3 N = normal_world;
	float3 T = normalize(tangent_world - dot(tangent_world, N) * N);
	float3 B = cross(N, T);
	// �ڋ�ԁ����[���h��Ԃ̕ϊ��s��
	float3x3 TBN = float3x3(T, B, N);

	float3 bump_normal_world = mul(normal_t, TBN);
	return bump_normal_world;
}

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
	output.position = mul(float4(input.position, 1.0f), uniform_world_view_projection);

	// ���[���h�ϊ����_�𑗂�
	output.world_position = mul(float4(input.position, 1.0f), uniform_world).xyz;

	// �r���[�ϊ����_
	float3 world_view_position = mul(float4(output.world_position, 1.0f), uniform_view).xyz;
	output.depth = world_view_position.z / (5.f - 100.f);

	// �@��
	float4 normal = float4(input.normal.x, input.normal.y, input.normal.z, 0.f);
	output.normal = mul(normal, uniform_world).xyz;

	// �e�N�Z�����W
	output.texcoord = input.texcoord;

	// ���[���h�ڐ�
	float4 tangent = float4(input.tangent.x, input.tangent.y, input.tangent.z, 1.f);
	output.world_tangent = mul(tangent, uniform_world).xyz;
	output.world_tangent = normalize(output.world_tangent);

	// ����
	output.cleanliness = input.cleanliness;

	return output;
}


//=============================================================================
// �s�N�Z���V�F�[�_
PixelShaderOutput PS(VertexShaderOutput input)
{
	PixelShaderOutput output = (PixelShaderOutput)0;

	float fog_amount = 1.f - smoothstep(0, 10, input.world_position.y);

	// �@��
	float3 normal = normalize(input.normal);
	float3 normal_sampler = lerp(tex2D(uniform_dirty_sampler, input.texcoord + uniform_texcoord_move), tex2D(uniform_normal_sampler, input.texcoord), input.cleanliness).xyz;
	//normal_sampler = normalize(normal_sampler);
	input.world_tangent = normalize(input.world_tangent);
	normal = NormalSampler2WorldSpace(normal_sampler, normal, input.world_tangent);
	normal = normalize(normal);

	// ����
	float3 diffuse_cube_ambient = texCUBE(uniform_diffuse_cube_sampler, input.normal).xyz;

	// �A���x�h
	float3 albedo = lerp(uniform_ambient_color.xyz, tex2D(uniform_albedo_sampler, input.texcoord).xyz + (diffuse_cube_ambient.xyz*0.5f), input.cleanliness);

	// �F
	float4 color = (float4)0;
	float3 light_direction = -normalize(uniform_light_direction.xyz);

	// �g�U�Ɩ�
	float power = HalfLambert(normal, light_direction);

	// toon
	float3 toon_color = tex2D(uniform_toon_sampler, float2(power, 0.01f)).xyz;

	color.xyz = toon_color * albedo;
	color.a = uniform_ambient_color.a;
	output.render_target0= color;
	output.render_target0.xyz = lerp(color.xyz, float3(0.6f, 0.8f, 0.95f), fog_amount);

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
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();
	}
}