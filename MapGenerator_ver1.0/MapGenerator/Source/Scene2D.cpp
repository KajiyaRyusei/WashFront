//=============================================================================
//
// 2Dポリゴンのクラス [Scene2D.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "Scene2d.h"
#include "Manager.h"
#include "Keyboard.h"


//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define ANIMATION_RATIO	(0.4f)	// アニメーションの割合
#define MOVEMENT_RATIO	(0.3f)	// 移動の割合


//=========================================================================
// コンストラクタ
//=========================================================================
Scene2D::Scene2D(int priority) : Scene(priority)
{

	rotation_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertexBuffer_ = nullptr;
	width_ = destWidth_ = 0.0f;
	height_ = destHeight_ = 0.0f;
	flashFlag_ = false;
	flashSpeed_ = 0.0f;
	destPosition_ = D3DXVECTOR3(0, 0, 0);

}

//=========================================================================
// デストラクタ
//=========================================================================
Scene2D::~Scene2D()
{

	SafeRelease(vertexBuffer_);

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Scene2D::Init(D3DXVECTOR3 pos, float width, float height, D3DXCOLOR color)
{
	// メンバ変数の初期化
	width_ = destWidth_ = width;
	height_ = destHeight_ = height;
	position_ = destPosition_ = pos;

	// 頂点座標の設定
	VERTEX_2D *pVtx;
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	// 頂点バッファの生成（メモリの確保）
	if (FAILED(device->CreateVertexBuffer(
							sizeof(VERTEX_2D) * 4,  // 確保するメモリのサイズ
							D3DUSAGE_WRITEONLY,
							FVF_VERTEX_2D,  // 使用する頂点フォーマット
							D3DPOOL_MANAGED,
							&vertexBuffer_,  // 頂点バッファの先頭アドレスの入ったポインタ変数のアドレス
							nullptr))) {
		return E_FAIL;
	}


	// 頂点座標の設定
	vertexBuffer_->Lock(0, 0, (void**)&pVtx, 0);  // 頂点情報をロック

	pVtx[0].vtx = D3DXVECTOR3(position_.x - width / 2 + 0.5f, position_.y - height / 2 + 0.5f, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(position_.x + width / 2 - 0.5f, position_.y - height / 2 + 0.5f, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(position_.x - width / 2 + 0.5f, position_.y + height / 2 - 0.5f, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(position_.x + width / 2 - 0.5f, position_.y + height / 2 - 0.5f, 0.0f);
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	pVtx[0].diffuse = color;
	pVtx[1].diffuse = color;
	pVtx[2].diffuse = color;
	pVtx[3].diffuse = color;

	// テクスチャ情報の初期化
	pVtx[0].tex = D3DXVECTOR2(0.001f, 0.001f);
	pVtx[1].tex = D3DXVECTOR2(0.999f, 0.001f);
	pVtx[2].tex = D3DXVECTOR2(0.001f, 0.999f);
	pVtx[3].tex = D3DXVECTOR2(0.999f, 0.999f);

	vertexBuffer_->Unlock();  // 頂点情報をアンロック


	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void Scene2D::Update()
{
	VERTEX_2D *pVtx;
	D3DXCOLOR color;


	width_ += (destWidth_ - width_) * ANIMATION_RATIO;
	height_ += (destHeight_ - height_) * ANIMATION_RATIO;
	position_ += (destPosition_ - position_) * MOVEMENT_RATIO;


	// 頂点座標の設定
	vertexBuffer_->Lock(0, 0, (void**)&pVtx, 0);  // 頂点情報をロック

	pVtx[0].vtx = D3DXVECTOR3(position_.x - width_ / 2, position_.y - height_ / 2, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(position_.x + width_ / 2, position_.y - height_ / 2, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(position_.x - width_ / 2, position_.y + height_ / 2, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(position_.x + width_ / 2, position_.y + height_ / 2, 0.0f);

	// 点滅するか
	if (flashFlag_) {
		color = pVtx[0].diffuse;
		color.a += flashSpeed_;
		if (color.a < 0.2f) {
			color.a = 0.2f;
			flashSpeed_ *= -1.0f;
		} else if (1.0f < color.a) {
			color.a = 1.0f;
			flashSpeed_ *= -1.0f;
		}
		pVtx[0].diffuse = color;
		pVtx[1].diffuse = color;
		pVtx[2].diffuse = color;
		pVtx[3].diffuse = color;
	}

	vertexBuffer_->Unlock();  // 頂点情報をアンロック
}

//=============================================================================
// 描画処理
//=============================================================================
void Scene2D::Draw()
{
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();


	device->SetRenderState(D3DRS_ZENABLE, FALSE);

	// 頂点バッファをデータストリームにバインド
	device->SetStreamSource(0, vertexBuffer_, 0, sizeof(VERTEX_2D));
		
	device->SetFVF(FVF_VERTEX_2D);  // 頂点フォーマットの設定
	device->SetTexture(0, texture_);  // テクスチャの設定
	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);  // ポリゴンの描画

	device->SetRenderState(D3DRS_ZENABLE, TRUE);

}

//=============================================================================
// 生成処理
//=============================================================================
Scene2D *Scene2D::Create(D3DXVECTOR3 pos, float width, float height, D3DXCOLOR color)
{
	// 生成
	Scene2D *scene2D = new Scene2D();
	// 初期化
	scene2D->Init(pos, width, height, color);
	

	return scene2D;
}

//=========================================================================
// 色の設定
//=========================================================================
void Scene2D::SetColor(D3DXCOLOR color)
{
	// 頂点座標の設定
	VERTEX_2D *pVtx;
	
	// 頂点座標の設定
	vertexBuffer_->Lock(0, 0, (void**)&pVtx, 0);  // 頂点情報をロック

	pVtx[0].diffuse = color;
	pVtx[1].diffuse = color;
	pVtx[2].diffuse = color;
	pVtx[3].diffuse = color;

	vertexBuffer_->Unlock();
}

//=========================================================================
// 幅の設定
//=========================================================================
void Scene2D::SetWidth(float width)
{
	width_ = destWidth_ = width;

	VERTEX_2D *pVtx;
	vertexBuffer_->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(position_.x - width_ / 2, position_.y - height_ / 2, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(position_.x + width_ / 2, position_.y - height_ / 2, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(position_.x - width_ / 2, position_.y + height_ / 2, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(position_.x + width_ / 2, position_.y + height_ / 2, 0.0f);

	vertexBuffer_->Unlock();
}
//=========================================================================
// 高さの設定
//=========================================================================
void Scene2D::SetHeight(float height)
{
	height_ = destHeight_ = height;

	VERTEX_2D *pVtx;
	vertexBuffer_->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(position_.x - width_ / 2, position_.y - height_ / 2, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(position_.x + width_ / 2, position_.y - height_ / 2, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(position_.x - width_ / 2, position_.y + height_ / 2, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(position_.x + width_ / 2, position_.y + height_ / 2, 0.0f);

	vertexBuffer_->Unlock();
}



// End of file