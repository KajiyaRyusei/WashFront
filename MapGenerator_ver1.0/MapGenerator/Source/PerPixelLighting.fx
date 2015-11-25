//=============================================================================
// �p�[�s�N�Z�����C�e�B���O
//
// Author : KEITA OHUCHI
//=============================================================================

//=============================================================================
// �萔���W�X�^
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
// �o�[�e�b�N�X�V�F�[�_
//=============================================================================
void VS(in inVS iv, out outVS ov)
{
	// �X�N���[�����W
	ov.Position = mul(float4(iv.Position, 1.0f), WVP);

	// ���[���h���W
	ov.WorldPosition = mul(float4(iv.Position, 1.0f), World);

	// ���[���h�@��
	ov.WorldNormal = normalize(mul(float4(iv.Normal, 0.0f), World));

	// �e�N�X�`�����W
	ov.TexCoord = iv.TexCoord;
}

//=============================================================================
// �s�N�Z���V�F�[�_
//=============================================================================
float4 PS(in inPS ip) : COLOR0
{

	return tex2D(TextureSampler, ip.TexCoord);
	// �n�[�t�����o�[�g
	float power = dot(normalize(ip.WorldNormal), -normalize(LightDirection)) * 0.5f + 0.5f;
	float3 diffuse = MaterialDiffuse * LightDiffuse * power;

	return float4(diffuse, MaterialDiffuse.a);
}


// End of file