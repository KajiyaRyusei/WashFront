//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �R�}���h�̎��
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
// �O���錾
class InputManager;

//*****************************************************************************
// �N���X�݌v
class CommandHandler
{
public:

	CommandHandler();
	virtual ~CommandHandler();

	// ���̓R�}���h
	Command* HandleInput(InputManager* input, Command::CONTROLLER_TYPE type);

	// �ړ��p�R�}���h
	Command* HandleInputMove(InputManager* input, Command::CONTROLLER_TYPE type);

	// InputEvent�p�R�}���h
	Command* HandleInputEvent(InputManager* input, Command::CONTROLLER_TYPE type);

private:
	Command* _fire;
	Command* _move;
	Command* _chage_level;
};