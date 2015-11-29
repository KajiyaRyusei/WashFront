//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 背景
// 
// Created by Ryusei Kajiya on 20151022
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//-------------------------------------
// 頂点シェーダ入力
//-------------------------------------
struct VertexShaderInput
{
	float3 position	: POSITION0;
	float3 normal	: NORMAL0;
};

//-------------------------------------
// 頂点シェーダ出力
//-------------------------------------
struct VertexShaderOutput
{
	float4 position	: POSITION;
	float3 normal	: TEXCOORD0;
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
uniform float4x4 uniform_world_view_projection;

// テクスチャ
texture uniform_albedo_cube_texture;
sampler uniform_albedo_cube_sampler = sampler_state {
	Texture = <uniform_albedo_cube_texture>;
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
	output.position = mul(float4(input.position, 1.0f), uniform_world_view_projection);

	// 法線受け渡し
	output.normal = normalize(input.normal);

	return output;
}

//=============================================================================
// ピクセルシェーダ
PixelShaderOutput PS(VertexShaderOutput input)
{
	PixelShaderOutput output = (PixelShaderOutput)0;

	output.render_target0 = texCUBE(uniform_albedo_cube_sampler, input.normal);
	//output.render_target0 = float4(input.normal, 1);
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
		CULLMODE = CW;

		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}
}