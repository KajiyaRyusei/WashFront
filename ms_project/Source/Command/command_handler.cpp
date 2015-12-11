//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �R�}���h�̎��
//
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Command/command_handler.h"
#include "Input/input_manager.h"

// �R�}���h
#include "Command/command_fire.h"
#include "Command/command_move_front.h"
#include "Command/command_move_back.h"
#include "Command/command_move_right.h"
#include "Command/command_move_left.h"
#include "Command/command_move_up.h"
#include "Command/command_move_down.h"
#include "Command/command_move.h"

//=============================================================================
// �R���X�g���N�^
CommandHandler::CommandHandler()
{
	_fire = new CommandFire();
	_move_front = new CommandMoveFront();
	_move_back  = new CommandMoveBack();
	_move_right = new CommandMoveRight();
	_move_left  = new CommandMoveLeft();
	_move_up = new CommandMoveUp();
	_move_down  = new CommandMoveDown();
	_move = new CommandMove();
}
//=============================================================================
// �f�X�g���N�^
CommandHandler::~CommandHandler()
{
	SafeDelete(_move_front);
	SafeDelete(_move_back);
	SafeDelete(_move_right);
	SafeDelete(_move_left);
	SafeDelete(_move_up);
	SafeDelete(_move_down);
	SafeDelete(_fire);
	SafeDelete(_move);
}
//=============================================================================
// ���̓R�}���h
Command* CommandHandler::HandleInput(InputManager* input, Command::CONTROLLER_TYPE type)
{
	u32 input_event_type = INPUT_EVENT_VALUE_PAD0_RTRIGGER + type;
	s32 pad_value = input->GetEventValue(static_cast<INPUT_EVENT_VALUE>(input_event_type));
	if( input->CheckPress(INPUT_EVENT_SPACE) || pad_value )
	{
		_fire->PressPower(pad_value);
		return _fire;
	}

	return nullptr;
}

//=============================================================================
// �ړ��p�R�}���h
Command* CommandHandler::HandleInputMove(InputManager* input, Command::CONTROLLER_TYPE type)
{
	u32 input_event_type = INPUT_EVENT_VALUE_PAD0_LSTICK_Y + type;
	s32 pad_value = input->GetEventValue(static_cast<INPUT_EVENT_VALUE>(input_event_type));
	if( input->GetEventValue(INPUT_EVENT_VALUE_PAD0_LSTICK_X) || pad_value )
	{
		_move->PressPower(pad_value);
		return _move;
	}

	return nullptr;
}