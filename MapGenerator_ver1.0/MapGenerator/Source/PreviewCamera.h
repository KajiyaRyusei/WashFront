//=============================================================================
//
// プレビュー用カメラクラス [PreviewCamera.h]
// Author : KEITA OHUCHI
//
//=============================================================================
#ifndef _PREVIEW_CAMERA_H_
#define _PREVIEW_CAMERA_H_

#include <Windows.h>
#include "Main.h"
#include "Camera.h"
#include "RouteManager.h"


//-----------------------------------------------------------------------------
// クラス定義
//-----------------------------------------------------------------------------
class PreviewCamera : public Camera {
public:
	//=========================================================================
	// コンストラクタとデストラクタ
	//=========================================================================
	PreviewCamera();
	virtual ~PreviewCamera();

	//=========================================================================
	// 初期化処理
	//=========================================================================
	HRESULT Init();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 focus_pos) { return S_OK; };

	//=========================================================================
	// 更新処理
	//=========================================================================
	void Update();


private:
	float		length_;
	float		time_;
	RoutePoint	currentPoint_;
	RoutePoint	nextPoint_;
};


#endif


// End of file