//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// カメラ管理
// 
// Created by Ryusei Kajiya on 20151006
// 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// 前方宣言
class Camera;
class Application;

//*****************************************************************************
// 列挙
enum CAMERA_TYPE
{
	CAMERA_TYPE_GAME_MAIN = 0,
	CAMERA_TYPE_GAME_PLAYER_1P,
	CAMERA_TYPE_GAME_PLAYER_2P,
	CAMERA_TYPE_2D,
	CAMERA_TYPE_TITLE,
	CAMERA_TYPE_MAX
};

//*****************************************************************************
// クラス設計
class CameraManager
{
public:

	// コンストラクタ
	CameraManager(Application* application) : _application(application){ Initialize(); }

	// デストラクタ
	virtual ~CameraManager(){ Finalize(); }

	// 初期化
	void Initialize();

	// 終了
	void Finalize();

	// 更新
	void Update();

	// カメラのポインタ取得
	Camera* GetCamera(CAMERA_TYPE type){ return _cameras[type]; }

	// 現在のカメラの取得
	Camera* GetCurrentCamera(){ return _current_camera; }
	// カメラのセット
	void SetCurrentCamera(Camera* camera){ _current_camera = camera; }

private:

	Camera* _cameras[CAMERA_TYPE_MAX];
	Camera* _current_camera;
	Application* _application;
};