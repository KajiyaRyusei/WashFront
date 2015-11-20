//=============================================================================
//
// 2Dアニメーションオブジェクト [SceneAnimation2D.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "SceneAnimation2D.h"
#include "Manager.h"
#include "Renderer.h"


//=========================================================================
// コンストラクタ
//=========================================================================
SceneAnimation2D::SceneAnimation2D(int priority) : Scene2D(priority)
{
	
	patternNumU_ = 1;
	patternNumV_ = 1;
	patternOnceFrame_ = 0;
	animationCounter_ = 0;

}
//=========================================================================
// デストラクタ
//=========================================================================
SceneAnimation2D::~SceneAnimation2D()
{
}


//=========================================================================
// 初期化処理
//=========================================================================
HRESULT SceneAnimation2D::Init(
	D3DXVECTOR3 pos, float width, float height, D3DXCOLOR color,
	int patternNumU, int patternNumV, int patternOnceFrame, char *textureFilePath)
{

	// メンバ変数の初期化
	if (patternNumU != 0)
		patternNumU_ = patternNumU;
	if (patternNumV != 0)
		patternNumV_ = patternNumV;
	patternOnceFrame_ = patternOnceFrame;
	animationCounter_ = 0;


	// 親クラスの初期化
	Scene2D::Init(pos, width, height, color);
	SetTexture(textureFilePath);


	// テクスチャ情報の初期化
	VERTEX_2D *pVtx;
	vertexBuffer_->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f / patternNumU_, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f / patternNumV_);
	pVtx[3].tex = D3DXVECTOR2(1.0f / patternNumU_, 1.0f / patternNumV_);

	vertexBuffer_->Unlock();


	return S_OK;

}

//=========================================================================
// 更新処理
//=========================================================================
void SceneAnimation2D::Update()
{

	// 親クラスの更新処理
	Scene2D::Update();


	// アニメーションの更新
	float textureU =
		(animationCounter_ / patternOnceFrame_) * (1.0f / patternNumU_);
	float textureV =
		(animationCounter_ / (patternOnceFrame_ * patternNumU_)) * (1.0f / patternNumV_);

	// テクスチャ情報の更新
	VERTEX_2D	*vtx;
	vertexBuffer_->Lock(0, 0, (void**)&vtx, 0);

	vtx[0].tex = D3DXVECTOR2(textureU, textureV);
	vtx[1].tex = D3DXVECTOR2(textureU + (1.0f / patternNumU_), textureV);
	vtx[2].tex = D3DXVECTOR2(textureU, textureV + (1.0f / patternNumV_));
	vtx[3].tex = D3DXVECTOR2(textureU + (1.0f / patternNumU_), textureV + (1.0f / patternNumV_));

	vertexBuffer_->Unlock();

	// カウントアップ
	animationCounter_++;

	// アニメーションが終わったら
	if (patternNumU_ * patternNumV_ <=
			(animationCounter_ / patternOnceFrame_)) {
		animationCounter_ = 0;
	}

}

//=========================================================================
// 描画処理
//=========================================================================
void SceneAnimation2D::Draw()
{

	// 親クラスの描画処理
	Scene2D::Draw();

}
	

// End of file