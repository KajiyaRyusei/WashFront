//=============================================================================
// パーピクセルライティング
//
// Author : KEITA OHUCHI
//=============================================================================

//=============================================================================
// 定数レジスタ
//=============================================================================
float4x4 World;
float4x4 View;
float4x4 Projection;
float4x4 WVP;
float3 LightDirection;
float4 LightDiffuse;
float4 LightAmbient;
float3 CameraDirection;
float4 MaterialDiffuse;
float4 MaterialAmbient;

sampler TextureSampler;


struct inVS {
	float3 Position : POSITION0;
	float3 Normal : NORMAL0;
	float2 TexCoord : TEXCOORD0;
};

struct outVS {
	float4 Position : POSITION0;
	float2 TexCoord : TEXCOORD0;
	float3 WorldPosition : TEXCOORD1;
	float3 WorldNormal : TEXCOORD2;
};

struct inPS {
	float2 TexCoord : TEXCOORD0;
	float3 WorldPosition : TEXCOORD1;
	float3 WorldNormal : TEXCOORD2;
};

//=============================================================================
// バーテックスシェーダ
//=============================================================================
void VS(in inVS iv, out outVS ov)
{
	// スクリーン座標
	ov.Position = mul(float4(iv.Position, 1.0f), WVP);

	// ワールド座標
	ov.WorldPosition = mul(float4(iv.Position, 1.0f), World);

	// ワールド法線
	ov.WorldNormal = normalize(mul(float4(iv.Normal, 0.0f), World));

	// テクスチャ座標
	ov.TexCoord = iv.TexCoord;
}

//=============================================================================
// ピクセルシェーダ
//=============================================================================
float4 PS(in inPS ip) : COLOR0
{

	return tex2D(TextureSampler, ip.TexCoord);
	// ハーフランバート
	float power = dot(normalize(ip.WorldNormal), -normalize(LightDirection)) * 0.5f + 0.5f;
	float3 diffuse = MaterialDiffuse * LightDiffuse * power;

	return float4(diffuse, MaterialDiffuse.a);
}


// End of file