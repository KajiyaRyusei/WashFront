//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// コマンド発射
//
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Command/command_fire.h"
#include "Unit/Game/player.h"
#include "Unit/Game/bullet.h"
#include "Unit/Game/aim.h"

//=============================================================================
// 指示
void CommandFire::Execute(PlayerUnit* player)
{
	player->_bullet->Fire(
		player->_aim->GetStartPosition(),
		player->_aim->GetEndPosition(),
		0.05f);
}