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
	Command* HandleInput(InputManager* input);

private:
	Command* _fire;
	Command* _move_front;
	Command* _move_back;
	Command* _move_right;
	Command* _move_left;
	Command* _move_up;
	Command* _move_down;
};