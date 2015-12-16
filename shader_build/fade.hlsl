//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �t�F�[�h�̃V�F�[�_�[
// 
// Created by Ryusei Kajiya on 20151013
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//-------------------------------------
// ���_�V�F�[�_����
//-------------------------------------
struct VertexShaderInput
{
	float2 position	: POSITION0;
	float2 texcoord	: TEXCOORD0;
};

//-------------------------------------
// ���_�V�F�[�_�o��
//-------------------------------------
struct VertexShaderOutput
{
	float4 position	: POSITION;
	float2 texcoord	: TEXCOORD0;
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
float2 uniform_screen_size;
float4x4 uniform_screen_matrix;
float4 uniform_ambient_color;
float4x4 uniform_texcoord_matrix;

uniform texture uniform_albedo_texture;
uniform sampler uniform_albedo_sampler = sampler_state {
	Texture = <uniform_albedo_texture>;
	MinFilter = ANISOTROPIC;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	MaxAnisotropy = 16;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

//=============================================================================
// ���_�V�F�[�_
VertexShaderOutput VS(VertexShaderInput input)
{
	// �o�̓f�[�^�̗p��
	VertexShaderOutput output = (VertexShaderOutput)0;

	// ���W�ϊ�
	float4 position= float4(input.position.x, input.position.y, 0.f, 1.f);

	position = mul(position, uniform_screen_matrix);

	output.position = float4(
		(position.x - uniform_screen_size.x) / uniform_screen_size.x,
		-(position.y - uniform_screen_size.y) / uniform_screen_size.y,
		0.f,
		1.0f);

	// �e�N�Z�����W
	float3 texcoord_work = float3(input.texcoord,0.f);
	output.texcoord.xy = mul(texcoord_work, uniform_texcoord_matrix).xy;
	output.texcoord.x += uniform_texcoord_matrix._41;
	output.texcoord.y += uniform_texcoord_matrix._42;

	return output;
}


//=============================================================================
// �s�N�Z���V�F�[�_
PixelShaderOutput PS(VertexShaderOutput input)
{
	PixelShaderOutput output = (PixelShaderOutput)0;


	output.render_target0 = uniform_ambient_color;

	float4 texture_color = tex2D(uniform_albedo_sampler, input.texcoord);

	int a = (int)uniform_ambient_color.a;

	output.render_target0.a = 1 - texture_color.a + uniform_ambient_color.a;

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
		ZENABLE = FALSE;
		ALPHAREF = 0;
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();
	}
}