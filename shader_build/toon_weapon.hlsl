//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �E�F�|���g�D�[��
// 
// Created by Ryusei Kajiya on 20151204
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
	float3 world_position: TEXCOORD2;
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

uniform texture uniform_specular_cube_texture;
uniform sampler uniform_specular_cube_sampler = sampler_state {
	Texture = <uniform_specular_cube_texture>;
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

uniform texture uniform_toon_texture;
uniform sampler uniform_toon_sampler = sampler_state {
	Texture = <uniform_toon_texture>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

uniform float4x4 uniform_animation_matrix_list[40];
uniform float4x4 uniform_world_view_projection;
uniform float4x4 uniform_world;
uniform float4 uniform_light_direction;
uniform float3 uniform_eye_position;

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
	float4 position = float4(input.position.x, input.position.y, input.position.z, 1.0f);
	float4x4 composition_matrix;
	composition_matrix = uniform_animation_matrix_list[input.bone_index[0]] * input.weight.x;
	composition_matrix += uniform_animation_matrix_list[input.bone_index[1]] * input.weight.y;
	composition_matrix += uniform_animation_matrix_list[input.bone_index[2]] * input.weight.z;
	composition_matrix += uniform_animation_matrix_list[input.bone_index[3]] * input.weight.w;
	position = mul(position, composition_matrix);
	output.position = mul(position, uniform_world_view_projection);

	// �@��
	float4 normal = float4(input.normal.x, input.normal.y, input.normal.z, 0.f);
	output.normal = mul(normal, uniform_world).xyz;

	// �e�N�Z�����W
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

	// �A���x�h
	float3 albedo = tex2D(uniform_albedo_sampler, input.texcoord).xyz;

	// ����
	float4 diffuse_cube_ambient = texCUBE(uniform_diffuse_cube_sampler, input.normal);

	// �g�U���ːF
	float4 color = (float4)0;
	float3 light_direction = -normalize(uniform_light_direction.xyz);
	float power = HalfLambert(normal, light_direction);
	float3 toon_color = tex2D(uniform_toon_sampler, float2(power, 0.5f)).xyz;

	color.xyz = toon_color * albedo;
	color.w = 1.f;
	output.render_target0 = color;

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
		CullMode = CW;
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();
	}
}