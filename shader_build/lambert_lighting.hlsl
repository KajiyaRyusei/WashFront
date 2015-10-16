//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ランバート拡散照明
// 
// Created by Ryusei Kajiya on 20151009
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
float4x4 uniform_world_view_projection;
float4 uniform_light_direction;

//=============================================================================
// 頂点シェーダ
VertexShaderOutput VS(VertexShaderInput input)
{
	// 出力データの用意
	VertexShaderOutput output = (VertexShaderOutput)0;

	// 座標変換
	output.position = mul(float4(input.position, 1.0f), uniform_world_view_projection);

	// 法線
	output.normal = normalize(input.normal);

	// テクセル座標
	output.texcoord = input.texcoord;

	return output;
}


//=============================================================================
// ピクセルシェーダ
PixelShaderOutput PS(VertexShaderOutput input)
{
	PixelShaderOutput output = (PixelShaderOutput)0;

	// 色
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
// テクニック
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