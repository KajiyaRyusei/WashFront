//=============================================================================
//
// マネージャクラス [Manager.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include <time.h>
#include "Main.h"
#include "Manager.h"
// シーン
#include "ObjectManager.h"
// 共通クラス
#include "Renderer.h"
#include "Scene.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Debug.h"
#include "TextureFactory.h"
#include "ModelFactory.h"
#include "CameraManager.h"
#include "ObjectManager.h"
#include "ImportFileManager.h"
#include "RouteManager.h"
#include "DirtManager.h"


//-----------------------------------------------------------------------------
// 静的メンバ変数
//-----------------------------------------------------------------------------
Manager *Manager::instance_ = nullptr;


//=========================================================================
// コンストラクタ
//=========================================================================
Manager::Manager()
{

	// クリア
	renderer_ = nullptr;
	keyboard_ = nullptr;
	mouse_ = nullptr;
	debugProc_ = nullptr;
	textureFactory_ = nullptr;
	modelFactory_ = nullptr;
	cameraManager_ = nullptr;
	objectManager_ = nullptr;
	importFileManager_ = nullptr;
	routeManager_ = nullptr;
	dirtManager_ = nullptr;

}

//=========================================================================
// デストラクタ
//=========================================================================
Manager::~Manager()
{

	// レンダラーインスタンスの解放
	SafeDelete(renderer_);
	// キーボードインスタンスの解放
	SafeDelete(keyboard_);
	// マウスインスタンスの解放
	SafeDelete(mouse_);


	// テクスチャファクトリの解放
	SafeDelete(textureFactory_);
	// モデルファクトリの解放
	SafeDelete(modelFactory_);


	// カメラマネージャの解放
	SafeDelete(cameraManager_);

	// ファイル読み込みマネージャの解放
	SafeDelete(importFileManager_);

	// ルートマネージャの解放
	SafeDelete(routeManager_);

	// 汚れマネージャの解放
	SafeDelete(dirtManager_);

	// オブジェクトマネージャの解放
	SafeDelete(objectManager_);

#ifdef _DEBUG
	// デバッグプロシージャの解放
	SafeDelete(debugProc_);
#endif

}

//=========================================================================
// インスタンスの取得
//=========================================================================
Manager *Manager::GetInstance()
{
	if (!instance_) {
		instance_ = new Manager();
	}

	return instance_;
}

//=========================================================================
// インスタンスの破棄
//=========================================================================
void Manager::Destory()
{
	SafeDelete(instance_);
}


//=========================================================================
// 初期化処理
//=========================================================================
HRESULT Manager::Init(HINSTANCE instance, HWND wnd, BOOL window)
{
	// 乱数の初期化
	srand((unsigned int)time(nullptr));

	// レンダラーの生成
	renderer_ = new Renderer();
	renderer_->Init(instance, wnd, window);

	// テクスチャファクトリの生成
	textureFactory_ = new TextureFactory();
	// モデルファクトリの生成
	modelFactory_ = new ModelFactory();


	// キーボードの生成
	keyboard_ = new Keyboard();
	keyboard_->Init(instance, wnd);

	// マウスの生成
	mouse_ = new Mouse();
	mouse_->Init(instance, wnd);



	// カメラマネージャの生成
	cameraManager_ = new CameraManager();
	cameraManager_->Init();
	cameraManager_->ChangeEditorCamera();

	// ファイル読み込みマネージャの生成
	importFileManager_ = new ImportFileManager();
	importFileManager_->Init();

	// ルートマネージャの生成
	routeManager_ = new RouteManager();
	routeManager_->Init();

	// 汚れマネージャの生成
	dirtManager_ = new DirtManager();
	dirtManager_->Init();

	// オブジェクトマネージャの生成
	objectManager_ = new ObjectManager();
	objectManager_->Init();


#ifdef _DEBUG
	debugProc_ = new DebugProc();
	debugProc_->Init();
#endif


	return S_OK;
}

//=========================================================================
// 更新処理
//=========================================================================
void Manager::Update()
{

#ifdef _DEBUG
	debugProc_->Update();
	float fps = GetFps();
	DebugProc::Printf("[FPS : %f]\n", fps);
#endif

	// キーボードインスタンスの更新
	keyboard_->Update();
	// マウスの更新
	mouse_->Update();



	// 更新処理
	{
		// レンダラーインスタンスの更新
		renderer_->Update();

		// カメラの更新
		cameraManager_->Update();

		// シーンの更新
		objectManager_->Update();

		routeManager_->Update();
	}

}

//=========================================================================
// 描画処理
//=========================================================================
void Manager::Draw()
{
	
	// 描画開始
	if (renderer_->BeginDraw()) {

		// カメラの設定
		cameraManager_->SetCamera();

		// シーンインスタンスの描画処理
		Scene::DrawAll();

		// シーンの描画
		objectManager_->Draw();

		// ルートの描画
		routeManager_->Draw();

		// 汚れの描画
		dirtManager_->Draw();

#ifdef _DEBUG
		// デバッグ表示
		DebugProc::Draw();
#endif


		// 描画終了
		renderer_->EndDraw();
	}

}


// End of file