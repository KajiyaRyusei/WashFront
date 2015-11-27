//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 水しぶき
// 
// Created by Ryusei Kajiya on 20151125
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//-------------------------------------
// 頂点シェーダ入力
//-------------------------------------
struct VertexShaderInput
{
	float3 position		: POSITION0;
	float3 normal		: NORMAL0;
	float2 texcoord		: TEXCOORD0;
	float4 world_matrix1: TEXCOORD1;
	float4 world_matrix2: TEXCOORD2;
	float4 world_matrix3: TEXCOORD3;
	float4 world_matrix4: TEXCOORD4;
};

//-------------------------------------
// 頂点シェーダ出力
//-------------------------------------
struct VertexShaderOutput
{
	float4 position	: POSITION;
	float2 texcoord	: TEXCOORD1;
};

//-------------------------------------
// ピクセルシェーダ出力
//-------------------------------------
struct PixelShaderOutput
{
	float4 render_target0	: COLOR0;
	float4 render_target1	: COLOR1;
	float4 render_target2	: COLOR2;
	float4 render_target3	: COLOR3;
};

//=============================================================================
// ユニフォーム
uniform float4x4 uniform_view_projection;
texture uniform_albedo_texture;
sampler uniform_albedo_sampler = sampler_state {
	Texture = <uniform_albedo_texture>;
	MinFilter = ANISOTROPIC;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	MaxAnisotropy = 8;
	AddressU = WRAP;
	AddressV = WRAP;
};

//=============================================================================
// 頂点シェーダ
VertexShaderOutput VS(VertexShaderInput input)
{
	// 出力データの用意
	VertexShaderOutput output = (VertexShaderOutput)0;

	// 座標変換
	float4 position = float4(input.position.x, input.position.y, input.position.z, 1.f);
	float4x4 world_matrix;

	world_matrix._11 = input.world_matrix1.x;
	world_matrix._12 = input.world_matrix1.y;
	world_matrix._13 = input.world_matrix1.z;
	world_matrix._14 = input.world_matrix1.w;
	world_matrix._21 = input.world_matrix2.x;
	world_matrix._22 = input.world_matrix2.y;
	world_matrix._23 = input.world_matrix2.z;
	world_matrix._24 = input.world_matrix2.w;
	world_matrix._31 = input.world_matrix3.x;
	world_matrix._32 = input.world_matrix3.y;
	world_matrix._33 = input.world_matrix3.z;
	world_matrix._34 = input.world_matrix3.w;
	world_matrix._41 = input.world_matrix4.x;
	world_matrix._42 = input.world_matrix4.y;
	world_matrix._43 = input.world_matrix4.z;
	world_matrix._44 = input.world_matrix4.w;

	position = mul(position, world_matrix);
	output.position = mul(position, uniform_view_projection);

	// テクセル座標
	output.texcoord = input.texcoord;

	return output;
}


//=============================================================================
// ピクセルシェーダ
PixelShaderOutput PS(VertexShaderOutput input)
{
	PixelShaderOutput output = (PixelShaderOutput)0;

	output.render_target0 = tex2D(uniform_albedo_sampler, input.texcoord);
	output.render_target1 = float4(1, 1, 1, 1);
	output.render_target2 = float4(1, 1, 1, 1);
	output.render_target3 = float4(1, 1, 1, 1);

	return output;
}


//=============================================================================
// テクニック
technique Techniques
{
	pass P0
	{
		CullMode = NONE;
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();

	}
}