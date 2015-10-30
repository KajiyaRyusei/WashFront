//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �X�N���[���ɕ`�悷��
// 
// Created by Ryusei Kajiya on 20151012
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
	output.texcoord = input.texcoord;

	return output;
}


//=============================================================================
// �s�N�Z���V�F�[�_
PixelShaderOutput PS(VertexShaderOutput input)
{
	PixelShaderOutput output = (PixelShaderOutput)0;
	output.render_target0 = float4(1, 1, 1, 1);
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

		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}
}