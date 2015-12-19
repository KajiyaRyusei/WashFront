//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 水しぶき
// 
// Created by Ryusei Kajiya on 20151128
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//-------------------------------------
// 頂点シェーダ入力
//-------------------------------------
struct VertexShaderInput
{
	float3 position	: POSITION0;
	float3 normal	: NORMAL0;
	float2 texcoord	: TEXCOORD0;

	float4 world_matrix_1 : TEXCOORD1;
	float4 world_matrix_2 : TEXCOORD2;
	float4 world_matrix_3 : TEXCOORD3;
	float4 world_matrix_4 : TEXCOORD4;
};

//-------------------------------------
// 頂点シェーダ出力
//-------------------------------------
struct VertexShaderOutput
{
	float4 position	: POSITION;
	float3 normal	: TEXCOORD0;
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

// テクスチャ
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

	output.position = mul(float4(input.position, 1.0f), world_view_projection);

	// 法線受け渡し
	output.normal = normalize(input.normal);

	// テクスチャ座標
	output.texcoord = input.texcoord;

	return output;
}

//=============================================================================
// ピクセルシェーダ
PixelShaderOutput PS(VertexShaderOutput input)
{
	PixelShaderOutput output = (PixelShaderOutput)0;

	output.render_target0 = tex2D(uniform_albedo_sampler, input.texcoord);
	float2 center_point = float2(0.5,0.5);
	float distance_alpha = length(center_point - input.texcoord);
	output.render_target0.a *= 1.f - distance_alpha * 3.f;
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
		ZENABLE = FALSE;
		ALPHAREF = 25;
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();
	}
}