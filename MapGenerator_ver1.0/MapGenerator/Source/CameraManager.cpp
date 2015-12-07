//=============================================================================
//
// カメラマネージャ [CameraManager.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "CameraManager.h"
#include "Camera.h"


//=========================================================================
// コンストラクタ
//=========================================================================
CameraManager::CameraManager() :
camera_(nullptr)
{
}

//=========================================================================
// デストラクタ
//=========================================================================
CameraManager::~CameraManager()
{
	// カメラの解放
	SafeDelete(edit_);
	SafeDelete(preview_);
}

//=========================================================================
// 初期化処理
//=========================================================================
HRESULT CameraManager::Init()
{
	// カメラの設定
	//camera_ = new Camera();
	//camera_->Init();

	edit_ = new EditorCamera();
	edit_->Init();

	preview_ = new PreviewCamera();


	return S_OK;
}

//=========================================================================
// 更新処理
//=========================================================================
void CameraManager::Update()
{
	// カメラの更新
	if (camera_) {
		camera_->Update();
	}
}

//=========================================================================
// カメラの設定処理
//=========================================================================
void CameraManager::SetCamera()
{
	// カメラを設定
	if (camera_) {
		camera_->Set();
	}
}


// End of file