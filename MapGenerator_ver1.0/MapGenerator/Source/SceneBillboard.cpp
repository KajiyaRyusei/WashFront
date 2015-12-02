//=============================================================================
//
// ビルボードクラス [SceneBillboard.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "SceneBillboard.h"
#include "Renderer.h"
#include "ObjectManager.h"
#include "CameraManager.h"
#include "Camera.h"
#include "Manager.h"
#include "Mouse.h"
#include "Debug.h"


//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define POLYGON_WIDTH (1.0f)
#define POLYGON_HEIGHT (1.0f)


//=============================================================================
// コンストラクタ
//=============================================================================
SceneBillboard::SceneBillboard(int priority) : Scene(priority)
{
	// メンバ変数の初期化
	vertexBuffer_ = nullptr;  // 頂点情報格納ワーク
	D3DXMatrixIdentity(&worldMatrix_);  // ワールドマトリクス
}

//=============================================================================
// デストラクタ
//=============================================================================
SceneBillboard::~SceneBillboard()
{

	SafeRelease(vertexBuffer_);

}


HRESULT SceneBillboard::Init(D3DXVECTOR2 size, D3DXCOLOR color)
{
	// 頂点座標の設定
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	// 頂点バッファの生成（メモリの確保）
	if (FAILED(device->CreateVertexBuffer(
		sizeof(VERTEX_3D)* 4,  // 確保するメモリのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,  // 使用する頂点フォーマット
		D3DPOOL_MANAGED,
		&vertexBuffer_,  // 頂点バッファの先頭アドレスの入ったポインタ変数のアドレス
		nullptr))) {
		return E_FAIL;
	}

	float fAngle = atan2f(size.x / 2, size.y / 2);  // 対角線のなす角初期化
	float fLength = sqrtf((size.x / 2) * (size.x / 2)
		+ (size.y / 2) * (size.y / 2));  // 対角線の長さ初期化

	// 頂点座標の設定
	VERTEX_3D *pVtx;
	vertexBuffer_->Lock(0, 0, (void**)&pVtx, 0);  // 頂点情報をロック

	pVtx[0].vtx = D3DXVECTOR3(-sinf(fAngle) * fLength, cosf(fAngle) * fLength, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(sinf(fAngle) * fLength, cosf(fAngle) * fLength, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-sinf(fAngle) * fLength, -cosf(fAngle) * fLength, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(sinf(fAngle) * fLength, -cosf(fAngle) * fLength, 0.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].diffuse = pVtx[1].diffuse = pVtx[2].diffuse = pVtx[3].diffuse = color;

	// テクスチャ情報の初期化
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	vertexBuffer_->Unlock();  // 頂点情報をアンロック


	return S_OK;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT SceneBillboard::Init()
{
	// 頂点座標の設定
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

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

	float fAngle = atan2f(POLYGON_WIDTH / 2, POLYGON_HEIGHT / 2);  // 対角線のなす角初期化
	float fLength = sqrtf((POLYGON_WIDTH / 2) * (POLYGON_WIDTH / 2) 
							+(POLYGON_HEIGHT / 2) * (POLYGON_HEIGHT / 2));  // 対角線の長さ初期化

	// 頂点座標の設定
	VERTEX_3D *pVtx;
	vertexBuffer_->Lock(0, 0, (void**)&pVtx, 0);  // 頂点情報をロック

	pVtx[0].vtx = D3DXVECTOR3(-sinf(fAngle) * fLength, cosf(fAngle) * fLength, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(sinf(fAngle) * fLength, cosf(fAngle) * fLength, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-sinf(fAngle) * fLength, -cosf(fAngle) * fLength, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(sinf(fAngle) * fLength, -cosf(fAngle) * fLength, 0.0f);

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


	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void SceneBillboard::Update()
{
}

//=============================================================================
// 描画処理
//=============================================================================
void SceneBillboard::Draw()
{
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();
	Camera *camera = Manager::GetInstance()->GetCameraManager()->GetCamera();
	D3DXMATRIX view_mtx = camera->GetViewMtx();
	D3DXMATRIX translate_mtx;  // 位置の行列
	D3DMATERIAL9 def_mtr;  // デフォルトマテリアル
	device->GetMaterial(&def_mtr);  // 現在のマテリアル退避
	
	// ライトの描画を無効に
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	device->SetRenderState(D3DRS_ZENABLE, false);
	// アルファテスト有効
	device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	device->SetRenderState(D3DRS_ALPHAREF, 0);
	device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// エミッシブ設定
	D3DMATERIAL9 mtr;
	ZeroMemory(&mtr,sizeof(mtr));
	mtr.Emissive = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	device->SetMaterial(&mtr);
	
	// ワールドマトリックスの設定
	D3DXMatrixIdentity(&worldMatrix_);  // 単位行列で初期化
	D3DXMatrixInverse(&worldMatrix_, nullptr, &view_mtx);  // ビューマトリクスの逆行列を代入
	worldMatrix_._41 = 0.0f;  // 行列の要素を0初期化
	worldMatrix_._42 = 0.0f;  // 行列の要素を0初期化
	worldMatrix_._43 = 0.0f;  // 行列の要素を0初期化

	D3DXMatrixTranslation(&translate_mtx, position_.x, position_.y, position_.z);  // ビルボードの位置を反映
	D3DXMatrixMultiply(&worldMatrix_, &worldMatrix_, &translate_mtx);  // 行列のかけ合わせ
	device->SetTransform(D3DTS_WORLD, &worldMatrix_);  // 行列の設定


	// 3Dポリゴンの描画
	// 頂点バッファをデータストリームにバインド
	device->SetStreamSource(0, vertexBuffer_, 0, sizeof(VERTEX_3D));

	device->SetFVF(FVF_VERTEX_3D);  // 頂点フォーマットの設定
	device->SetTexture(0, texture_);  // テクスチャの設定
	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);  // ポリゴンの描画
	

	// マテリアルを元に戻す
	device->SetMaterial(&def_mtr);

	// アルファテスト無効
	device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	// ライトの描画を有効に
	device->SetRenderState(D3DRS_LIGHTING, TRUE);
	device->SetRenderState(D3DRS_ZENABLE, true);
}

//=============================================================================
// 生成処理
//=============================================================================
SceneBillboard *SceneBillboard::Create()
{
	// 生成
	SceneBillboard *scene = new SceneBillboard;
	// 初期化
	scene->Init();


	return scene;
}


// End of file