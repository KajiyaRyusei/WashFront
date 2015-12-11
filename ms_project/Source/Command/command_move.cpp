//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ‰ºˆÚ“®
//
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Command/command_move.h"
#include "Unit/Game/player.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"
#include "Input/input_manager.h"
#include "Unit/Game/aim.h"

//*****************************************************************************
// ’è”
namespace
{
	static const fx32 kRotationLimitX = 0.01f;
	static const fx32 kRotationLimitY = 0.01f;
	static const fx32 kMoveVelocity = 0.0005f;
}

//=============================================================================
// ŽwŽ¦
void CommandMove::Execute(PlayerUnit* player)
{
	// ƒJƒƒ‰‚ÌŽæ“¾
	u32 input_event_type_x = INPUT_EVENT_VALUE_PAD0_LSTICK_Y + player->_controller_type;
	u32 input_event_type_y = INPUT_EVENT_VALUE_PAD0_LSTICK_X + player->_controller_type;
	s32 pad_value_x = player->_application->GetInputManager()->GetEventValue(static_cast<INPUT_EVENT_VALUE>(input_event_type_x));
	s32 pad_value_y = player->_application->GetInputManager()->GetEventValue(static_cast<INPUT_EVENT_VALUE>(input_event_type_y));
	D3DXVECTOR3 target_rotation(0.f, 0.f, 0.f);
	target_rotation.x = static_cast<fx32>(-pad_value_x) * kMoveVelocity;
	target_rotation.y = static_cast<fx32>(pad_value_y) * kMoveVelocity;

	player->_aim->SetRotation(target_rotation);
}