//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 右移動
//
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Command/command_move_right.h"
#include "Unit/Game/player.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"

//=============================================================================
// 指示
void CommandMoveRight::Execute(PlayerUnit* player)
{
	// カメラの取得
	D3DXVECTOR3 camera_rotation = player->_player_camera->GetCameraRotation();
}