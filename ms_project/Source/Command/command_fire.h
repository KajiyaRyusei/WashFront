//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �R�}���h����
//
// Created by Ryusei Kajiya on 20151029
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
class CommandFire : public Command
{
public:
	CommandFire(){}
	virtual ~CommandFire(){}

	virtual void Execute(PlayerUnit* player);
};