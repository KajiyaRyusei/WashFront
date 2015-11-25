//=============================================================================
//
// 汚れ [Dirt.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================
#include "Dirt.h"
#include "Manager.h"
#include "Renderer.h"


VERTEX_3D Dirt::vertexBuffer_[9] = {
	{ D3DXVECTOR3(sinf(-D3DX_PI), cosf(-D3DX_PI), 0.0f), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1, 0, 0, 1), D3DXVECTOR2(0, 0) },
	{ D3DXVECTOR3(sinf(-D3DX_PI * 3 / 4), cosf(-D3DX_PI * 3 / 4), 0.0f), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1, 0, 0, 1), D3DXVECTOR2(0, 0) },
	{ D3DXVECTOR3(sinf(-D3DX_PI / 2), cosf(-D3DX_PI / 2), 0.0f), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1, 0, 0, 1), D3DXVECTOR2(0, 0) },
	{ D3DXVECTOR3(sinf(-D3DX_PI / 4), cosf(-D3DX_PI / 4), 0.0f), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1, 0, 0, 1), D3DXVECTOR2(0, 0) },
	{ D3DXVECTOR3(sinf(0.0f), cosf(0.0f), 0.0f), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1, 0, 0, 1), D3DXVECTOR2(0, 0) },
	{ D3DXVECTOR3(sinf(D3DX_PI / 4), cosf(D3DX_PI / 4), 0.0f), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1, 0, 0, 1), D3DXVECTOR2(0, 0) },
	{ D3DXVECTOR3(sinf(D3DX_PI / 2), cosf(D3DX_PI / 2), 0.0f), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1, 0, 0, 1), D3DXVECTOR2(0, 0) },
	{ D3DXVECTOR3(sinf(D3DX_PI * 3 / 4), cosf(D3DX_PI * 3 / 4), 0.0f), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1, 0, 0, 1), D3DXVECTOR2(0, 0) },
	{ D3DXVECTOR3(sinf(-D3DX_PI), cosf(-D3DX_PI), 0.0f), D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1, 0, 0, 1), D3DXVECTOR2(0, 0) },


};


//=========================================================================
// コンストラクタとデストラクタ
//=========================================================================
Dirt::Dirt() :
position_(D3DXVECTOR3(0, 0, 0)),
radius_(0)
{
}

//=========================================================================
// コンストラクタとデストラクタ
//=========================================================================
Dirt::~Dirt()
{
}

//=========================================================================
// 初期化処理
//=========================================================================
HRESULT Dirt::Init()
{

	radius_ = 1.0f;

	return S_OK;
}

//=========================================================================
// 更新処理
//=========================================================================
void Dirt::Update()
{
}

//=========================================================================
// 描画処理
//=========================================================================
void Dirt::Draw()
{
	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetRenderer()->GetDevice();
	device->SetRenderState(D3DRS_LIGHTING, false);


	device->SetFVF(FVF_VERTEX_3D);		// 頂点フォーマットの設定
	device->SetTexture(0, nullptr);


	// ワールドマトリックスの設定
	D3DXMATRIX worldMatrix, scale, rotation, position;
	D3DXMatrixIdentity(&worldMatrix);
	D3DXMatrixScaling(&scale, radius_, radius_, radius_);
	D3DXMatrixRotationYawPitchRoll(&rotation, 0.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&position, position_.x, position_.y, position_.z);
	
	worldMatrix = scale * rotation * position;
	device->SetTransform(D3DTS_WORLD, &worldMatrix);
	device->DrawPrimitiveUP(D3DPT_LINESTRIP, 8, vertexBuffer_, sizeof(VERTEX_3D));


	D3DXMatrixRotationYawPitchRoll(&rotation, 0.0f, D3DX_PI / 2, 0.0f);
	worldMatrix = scale * rotation * position;
	device->SetTransform(D3DTS_WORLD, &worldMatrix);
	device->DrawPrimitiveUP(D3DPT_LINESTRIP, 8, vertexBuffer_, sizeof(VERTEX_3D));


	D3DXMatrixRotationYawPitchRoll(&rotation, D3DX_PI / 2, 0.0f, 0.0f);
	worldMatrix = scale * rotation * position;
	device->SetTransform(D3DTS_WORLD, &worldMatrix);
	device->DrawPrimitiveUP(D3DPT_LINESTRIP, 8, vertexBuffer_, sizeof(VERTEX_3D));


	device->SetRenderState(D3DRS_LIGHTING, true);
}


// End of file