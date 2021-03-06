//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// スクリーンに描画する
// 
// Created by Ryusei Kajiya on 20151012
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//-------------------------------------
// 頂点シェーダ入力
//-------------------------------------
struct VertexShaderInput
{
	float2 position	: POSITION0;
	float2 texcoord	: TEXCOORD0;
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
float2 uniform_screen_size;
float4x4 uniform_screen_matrix;
float2 uniform_texture_uv;
float2 uniform_texture_offset;
float uniform_texture_alpha;
float4 uniform_ambient_color;

uniform texture uniform_albedo_texture;
uniform sampler uniform_albedo_sampler = sampler_state{
	Texture = <uniform_albedo_texture>;
	MinFilter = ANISOTROPIC;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	MaxAnisotropy = 16;
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
	float4 position= float4(input.position.x, input.position.y, 0.f, 1.f);

	position = mul(position, uniform_screen_matrix);

	output.position = float4(
		(position.x - uniform_screen_size.x) / (uniform_screen_size.x),
		-(position.y - uniform_screen_size.y) / (uniform_screen_size.y),
		0.f,
		1.0f);

	// テクセル座標
	float2 tex;
	tex.x = input.texcoord.x * uniform_texture_uv.x;
	tex.y = input.texcoord.y * uniform_texture_uv.y;	

	tex.x += uniform_texture_offset.x;
	tex.y += uniform_texture_offset.y;

	output.texcoord = tex;

	return output;
}


//=============================================================================
// ピクセルシェーダ
PixelShaderOutput PS(VertexShaderOutput input)
{
	PixelShaderOutput output = (PixelShaderOutput)0;

	float4 albedo = tex2D(uniform_albedo_sampler, input.texcoord);

	output.render_target0 = albedo * uniform_texture_alpha * uniform_ambient_color;
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
	//	CullMode = NONE;

		CullMode = CCW;

		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();

	}
}