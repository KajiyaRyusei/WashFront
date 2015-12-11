//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �R�}���h����
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

//=============================================================================
// �w��
void CommandFire::Execute(PlayerUnit* player)
{
	player->_weapon->Fire(player->GetPosition(), player->_aim->GetTargetPosition());
}