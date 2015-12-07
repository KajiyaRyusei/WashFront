//=============================================================================
//
// 3Dポリゴンのクラス [Scene3D.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "Scene3d.h"
#include "Manager.h"


//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define TEXTURE_NAME (nullptr)
#define POLYGON_WIDTH (250.0f)
#define POLYGON_DEPTH (250.0f)


//=============================================================================
// コンストラクタ
//=============================================================================
Scene3D::Scene3D(int priority) : Scene(priority)
{
	// メンバ変数の初期化
	vertexBuffer_ = nullptr;  // 頂点情報格納ワーク
	D3DXMatrixIdentity(&worldMatrix_);  // ワールドマトリクス
	scale_ = D3DXVECTOR3(1.0f, 1.0f, 1.0f);  // 大きさ
	rotation_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // 向き
}

//=============================================================================
// デストラクタ
//=============================================================================
Scene3D::~Scene3D()
{
	SafeRelease(vertexBuffer_);
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Scene3D::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size, char *texturePath)
{
	position_ = pos;

	// 頂点座標の設定
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	// テクスチャの読み込み
	SetTexture(TEXTURE_NAME);

	// 頂点バッファの生成（メモリの確保）
	if (FAILED(device->CreateVertexBuffer(
							sizeof(VERTEX_3D) * 4,  // 確保するメモリのサイズ
							D3DUSAGE_WRITEONLY,
							FVF_VERTEX_3D,  // 使用する頂点フォーマット
							D3DPOOL_MANAGED,
							&vertexBuffer_,  // 頂点バッファの先頭アドレスの入ったポインタ変数のアドレス
							nullptr))) {
		return E_FAIL;
	}

	float fAngle = atan2f(size.x / 2, size.y / 2);  // 対角線のなす角初期化
	float fLength = sqrtf((size.x / 2) * (size.x / 2) 
							+(size.y / 2) * (size.y / 2));  // 対角線の長さ初期化


	// 頂点座標の設定
	VERTEX_3D *pVtx;
	vertexBuffer_->Lock(0, 0, (void**)&pVtx, 0);  // 頂点情報をロック

	pVtx[0].vtx = D3DXVECTOR3(-sinf(fAngle) * fLength, 0.0f, cosf(fAngle) * fLength);
	pVtx[1].vtx = D3DXVECTOR3(sinf(fAngle) * fLength, 0.0f, cosf(fAngle) * fLength);
	pVtx[2].vtx = D3DXVECTOR3(-sinf(fAngle) * fLength, 0.0f, -cosf(fAngle) * fLength);
	pVtx[3].vtx = D3DXVECTOR3(sinf(fAngle) * fLength, 0.0f, -cosf(fAngle) * fLength);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ情報の初期化
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	vertexBuffer_->Unlock();  // 頂点情報をアンロック


	SetTexture(texturePath);


	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void Scene3D::Update()
{
}

//=============================================================================
// 描画処理
//=============================================================================
void Scene3D::Draw()
{
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;  // 大きさ, 回転, 位置の行列

	// ワールドマトリックスの設定
	D3DXMatrixIdentity(&worldMatrix_);  // 単位行列で初期化

	D3DXMatrixScaling(&mtxScl, scale_.x, scale_.y, scale_.z);  // 地面のスケールを反映
	D3DXMatrixMultiply(&worldMatrix_, &worldMatrix_, &mtxScl);  // 行列のかけ合わせ

	D3DXMatrixRotationYawPitchRoll(&mtxRot, rotation_.y, rotation_.x, rotation_.z);  // 地面の回転を反映(y, x, z)
	D3DXMatrixMultiply(&worldMatrix_, &worldMatrix_, &mtxRot);  // 行列のかけ合わせ

	D3DXMatrixTranslation(&mtxTranslate, position_.x, position_.y, position_.z);  // 地面の位置を反映
	D3DXMatrixMultiply(&worldMatrix_, &worldMatrix_, &mtxTranslate);  // 行列のかけ合わせ

	device->SetTransform(D3DTS_WORLD, &worldMatrix_);  // 行列の設定


	// 3Dポリゴンの描画
	// 頂点バッファをデータストリームにバインド
	device->SetStreamSource(0, vertexBuffer_, 0, sizeof(VERTEX_3D));

	device->SetFVF(FVF_VERTEX_3D);  // 頂点フォーマットの設定
	device->SetTexture(0, texture_);  // テクスチャの設定
	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);  // ポリゴンの描画
}


// End of file