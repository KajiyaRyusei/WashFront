//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ‰ºˆÚ“®
//
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Command/command_change_water.h"
#include "Unit/Game/player.h"
#include "Unit/Game/weapon.h"
// ui
#include "Unit/ui.h"

// sound
#include "Sound/sound.h"

//*****************************************************************************
// ’è”
namespace
{
	static const fx32 kWaterAmount = 10.f;
}

//=============================================================================
// ŽwŽ¦
void CommandChangeWater::Execute(PlayerUnit* player)
{
	player->_weapon->WeaponLevel(static_cast<WEAPON_LEVEL>(_level));
	s32 player_id;
	if( player->_controller_type == Command::CONTROLLER_TYPE_1P)
	{
		player->_application->GetSound()->Play(SE_WEAPON_CHANGE);
		player_id = 1;
	}
	else
	{
		player->_application->GetSound()->Play(SE_WEAPON_CHANGE_2);
		player_id = 0;
	}
	player->SelectWeaponTexture(_level);
	player->_game_world->GetUi()->LevelUpMeter(player_id, _level + 1);
	player->_game_world->GetUi()->UpdateMeter(player_id, kWaterAmount);
	
}