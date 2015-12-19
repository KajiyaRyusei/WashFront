//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���ړ�
//
// Created by Ryusei Kajiya on 20151217
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "Command/command.h"

//*****************************************************************************
// �N���X�݌v
class CommandChangeWater : public Command
{
public:
	CommandChangeWater() : _level(0){}
	virtual ~CommandChangeWater(){}

	virtual void Execute(PlayerUnit* player);

	void SetLevel(const u8 level){ _level = level; }

private:

	u8 _level;
};