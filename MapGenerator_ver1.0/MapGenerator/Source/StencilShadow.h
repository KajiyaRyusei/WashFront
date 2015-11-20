//=============================================================================
//
// ステンシルシャドウクラス [Stencilshadow.h]
// Author : KEITA OHUCHI
//
//=============================================================================
#ifndef _STENCIL_SHADOW_H_
#define _STENCIL_SHADOW_H_


#include "Main.h"
#include "Scene.h"


//-----------------------------------------------------------------------------
// 前方宣言
//-----------------------------------------------------------------------------
class SceneX;
class Scene2D;


//-----------------------------------------------------------------------------
// クラス定義
//-----------------------------------------------------------------------------
class StencilShadow : public Scene {
public:
	//=========================================================================
	// コンストラクタとデストラクタ
	//=========================================================================
	StencilShadow(int priority = PRIORITY_STENCIL_SHADOW);
	virtual ~StencilShadow();

	//=========================================================================
	// 初期化処理
	//=========================================================================
	HRESULT Init() {
		return S_OK;
	};
	HRESULT Init(D3DXVECTOR3 pos) {
		position_ = pos;
		return S_OK;
	};
	//=========================================================================
	// 更新処理
	//=========================================================================
	void Update();
	//=========================================================================
	// 描画処理
	//=========================================================================
	void Draw();

	//=========================================================================
	// 大きさの設定
	//=========================================================================
	void SetScale(float scale) {
		scale_.x = scale;
		scale_.z = scale;
	};

private:
	SceneX		*shadow_;
	Scene2D		*polygon_;
	D3DXVECTOR3	scale_;
};


#endif


// End of file