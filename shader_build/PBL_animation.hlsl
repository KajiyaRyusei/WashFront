//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 物理ベースレンダリングアニメーション
// 
// Created by Ryusei Kajiya on 20151023
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
	float4 weight	: BLENDWEIGHT;
	int4  bone_index : BLENDINDICES;
};
//-------------------------------------
// 頂点シェーダ出力
//-------------------------------------
struct VertexShaderOutput
{
	float4 position		 : POSITION;
	float3 normal		 : TEXCOORD0;
	float2 texcoord		 : TEXCOORD1;
	float3 world_position: TEXCOORD2;
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
uniform float4x4 uniform_world;
uniform float4 uniform_light_direction;
uniform float4x4 uniform_animation_matrix_list[40];
uniform float3 uniform_eye_position;
uniform float uniform_roughness;
uniform float uniform_metalness;
uniform float uniform_fresnel;
uniform float4 uniform_ambient_color;

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

//-------------------------------------
// ベックマン分布関数 : 材質の粗さを定義するもの
float Beckmann(float roughness, float dot_normal_half)
{
	float roughness2 = roughness * roughness;
	float dot_normal_half2 = dot_normal_half * dot_normal_half;
	return exp((dot_normal_half2 - 1) / (roughness2 * dot_normal_half2)) / (roughness2 * dot_normal_half2 * dot_normal_half2);
}
//-------------------------------------
// Trowbridge-Reitz(GGX)
float GGX(float roughness,float dot_normal_half)
{
	float roughness2 = roughness * roughness;
	float D = (dot_normal_half * dot_normal_half) * (roughness2 - 1) + 1;
	D = 3.141592 *(D * D);
	return roughness2 / D;
}
//-------------------------------------
// 幾何学減衰率
float GeometricalAttenuationFactor(
	float dot_normal_half,
	float dot_normal_eye,
	float dot_eye_half,
	float dot_normal_light)
{
	return min(1, min(2 * dot_normal_half * dot_normal_eye / dot_eye_half, 2 * dot_normal_half * dot_normal_light / dot_eye_half));
}
//-------------------------------------
// フレネル　：反射光の割合 : FROM SCHLICK(重いから近似式を使用)
float Fresnel(float fresnel, float dot_eye_half)
{
	return fresnel + (1 - fresnel) * pow(1 - dot_eye_half, 5);
}

//-------------------------------------
// クックトランス
float3 CookTorrance(
	float3 light_direction,
	float3 eye,
	float3 normal)
{
	// ライトと視線の中間
	float3 lv_half = normalize(light_direction + eye);
	float dot_normal_half = dot(normal, lv_half);
	float dot_eye_half = dot(eye, lv_half);
	float dot_normal_light = dot(normal, light_direction);
	float dot_normal_eye = dot(normal, eye);

	float D = GGX(uniform_roughness, dot_normal_half);
	//float D = Beckmann(uniform_roughness, dot_normal_half);
	float F = Fresnel(uniform_fresnel, dot_eye_half);
	float G = GeometricalAttenuationFactor(dot_normal_half, dot_normal_eye, dot_eye_half, dot_normal_light);

	return max(0, F * D * G / dot_normal_eye);
}

//-------------------------------------
// オ―レンネイヤー
float3 OrenNayar(
	float3 light_direction,
	float3 eye,
	float3 normal,
	float3 albedo)
{
	float dot_eye_normal = dot(eye, normal);
	float dot_light_normal = dot(light_direction, normal);
	float theta_r = acos(dot_eye_normal);// 視線と法線のcosから角度を算出
	float raoughness2 = pow(uniform_roughness, 2);

	float cos_phi_diff = dot(normalize(eye - normal * dot_eye_normal), normalize(light_direction - normal * dot_light_normal));

	// ライトと法線のcosから角度を算出
	float theta_i = acos(dot_light_normal);

	// 大きい角度
	float alpha = max(theta_i, theta_r);

	// 小さい角度
	float beta = min(theta_i, theta_r);
	
	float C1 = 1.0 - 0.5 * raoughness2 / (raoughness2 + 0.33f);
	float C2 = 0.45 * raoughness2 / (raoughness2 + 0.09f);

	float cos_ln = cos(dot_light_normal);
	float cos_ir = cos(asin(dot_eye_normal) - asin(dot_light_normal));
	float sin_alpha = sin(alpha);
	float tan_beta = tan(beta);

	return (float3)(albedo * cos_ln * (C1 + (C2 * cos_ir * sin_alpha * tan_beta)) / 3.141592);
}

//-------------------------------------
// バーレイ
float3 Burley(
	float3 light_direction,
	float3 eye,
	float3 normal,
	float3 albedo)
{
	float3 lv_half = normalize(light_direction + eye);
	float dot_normal_light = dot(normal, light_direction);
	float dot_normal_eye = dot(normal, eye);
	float dot_light_half = dot(light_direction, lv_half);

	float Fd90 = 0.5f + 2 * pow(dot_light_half, 2) * uniform_roughness;

	return (1 + (Fd90 - 1) * pow(1 - dot_normal_light, 5)) * (1 + (Fd90 - 1) * pow(1 - dot_normal_eye, 5)) * albedo / 3.141592;
}

//=============================================================================
// 頂点シェーダ
VertexShaderOutput VS(VertexShaderInput input)
{
	// 出力データの用意
	VertexShaderOutput output = (VertexShaderOutput)0;

	// 座標変換
	float4 position = float4(input.position.x, input.position.y, input.position.z, 1.0f);
	float4x4 composition_matrix;
	composition_matrix = uniform_animation_matrix_list[input.bone_index[0]] * input.weight.x;
	composition_matrix += uniform_animation_matrix_list[input.bone_index[1]] * input.weight.y;
	composition_matrix += uniform_animation_matrix_list[input.bone_index[2]] * input.weight.z;
	composition_matrix += uniform_animation_matrix_list[input.bone_index[3]] * input.weight.w;
	position = mul(position, composition_matrix);
	output.position = mul(position, uniform_world_view_projection);

	// ワールド変換頂点を送る
	output.world_position = mul(position, uniform_world).xyz;

	// 法線もアニメーションに合わせてあとにワールド変換
	float4 normal = float4(input.normal.x, input.normal.y, input.normal.z, 0.f);
	normal = normalize(normal);
	normal = mul(normal, composition_matrix);
	normal = mul(normal, uniform_world);
	output.normal = normalize(normal).xyz;


	// テクセル座標
	output.texcoord = input.texcoord;

	return output;
}

//=============================================================================
// ピクセルシェーダ
PixelShaderOutput PS(VertexShaderOutput input)
{
	PixelShaderOutput output = (PixelShaderOutput)0;

	// ライトベクトル
	float3 light_direction = uniform_light_direction.xyz;
	// 視線ベクトル
	float3 eye = normalize(uniform_eye_position - input.world_position);
	// アルベド色
	float3 albedo = tex2D(uniform_albedo_sampler, input.texcoord).xyz;
	// 拡散反射色
	float3 diffuse = OrenNayar(light_direction, eye, input.normal, uniform_ambient_color.xyz);
	// 鏡面反射色
	float3 specular = CookTorrance(light_direction, eye, input.normal);
	// 環境光色
	float3 R = reflect(eye, input.normal);
	float4 specular_cube_ambient = texCUBE(uniform_specular_cube_sampler, -R);
	float4 diffuse_cube_ambient = texCUBE(uniform_diffuse_cube_sampler, input.normal);

	output.render_target0.xyz = (diffuse + specular) * albedo;
	output.render_target0.xyz = lerp(diffuse_cube_ambient.xyz, specular_cube_ambient.xyz, uniform_metalness) * output.render_target0.xyz;
	output.render_target0.a = uniform_ambient_color.w;

	// ガンマ補正
	output.render_target0.xyz = pow(output.render_target0.xyz, 1.f / 2.2f);

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
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_3_0 PS();
	}
}