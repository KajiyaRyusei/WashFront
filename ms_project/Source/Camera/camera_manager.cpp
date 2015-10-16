//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// カメラ管理
// 
// Created by Ryusei Kajiya on 20151006
// 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// インクルード
#include "camera_manager.h"

// カメラども
#include "Camera/camera_game_main.h"
#include "Camera/camera_2d.h"

//=============================================================================
// 初期化
void CameraManager::Initialize()
{
	_cameras[CAMERA_TYPE_GAME_MAIN] = new CameraGameMain();
	_cameras[CAMERA_TYPE_2D] = new Camera2D();
}
//=============================================================================
// 終了
void CameraManager::Finalize()
{
	for( s32 i = 0; i < CAMERA_TYPE_MAX; ++i )
	{
		SafeDelete(_cameras[i]);
	}
}
//=============================================================================
// 更新
void CameraManager::Update()
{
	for( s32 i = 0; i < CAMERA_TYPE_MAX; ++i )
	{
		_cameras[i]->CreateMatrix();
	}
}
