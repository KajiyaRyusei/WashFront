//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// コマンド発射
//
// Created by Ryusei Kajiya on 20151118
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Command/command_fire.h"
#include "Unit/Game/player.h"
#include "Unit/Game/weapon.h"
#include "Unit/Game/aim.h"
// ui
#include "Unit/ui.h"

//*****************************************************************************
// 定数
namespace
{
	static const fx32 kWaterAmount = 1.5f;
}

//=============================================================================
// 指示
void CommandFire::Execute(PlayerUnit* player)
{
	s32 player_id;
	if( player->_controller_type == Command::CONTROLLER_TYPE_1P )
	{
		player_id = 1;
	}
	else
	{
		player_id = 0;
	}

	if( player->_game_world->GetUi()->GetWaterMeter(player_id) <= 0.f)
	{
		return;
	}
	player->_game_world->GetUi()->UpdateMeter(player_id, kWaterAmount);
	player->_weapon->Fire(player->GetPosition(), player->_aim->GetTargetPosition(),player->_controller_type);
}