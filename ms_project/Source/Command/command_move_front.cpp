//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 前移動
//
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Command/command_move_front.h"
#include "Unit/Game/player.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"

//=============================================================================
// 指示
void CommandMoveFront::Execute(PlayerUnit* player)
{
	// カメラの取得
	CameraGamePlayer* camera = static_cast<CameraGamePlayer*>(player->_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER));
	D3DXVECTOR3 camera_rotation = camera->GetCameraRotation();
	player->DebugMove(3.14f + camera_rotation.y);
}