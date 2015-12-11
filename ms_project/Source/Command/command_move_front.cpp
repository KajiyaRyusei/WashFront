//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ‘OˆÚ“®
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
// ŽwŽ¦
void CommandMoveFront::Execute(PlayerUnit* player)
{
	// ƒJƒƒ‰‚ÌŽæ“¾
	D3DXVECTOR3 camera_rotation = player->_player_camera->GetCameraRotation();
}