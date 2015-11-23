//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���ړ�
//
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Command/command_move_back.h"
#include "Unit/Game/player.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"

//=============================================================================
// �w��
void CommandMoveBack::Execute(PlayerUnit* player)
{
	// �J�����̎擾
	CameraGamePlayer* camera = static_cast<CameraGamePlayer*>(player->_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER));
	D3DXVECTOR3 camera_rotation = camera->GetCameraRotation();
	player->DebugMove(camera_rotation.y);
}