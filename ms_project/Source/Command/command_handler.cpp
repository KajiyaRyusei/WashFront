//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// コマンドの受取
//
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Command/command_handler.h"
#include "Input/input_manager.h"

// コマンド
#include "Command/command_fire.h"
#include "Command/command_move.h"
#include "Command/command_change_water.h"

//=============================================================================
// コンストラクタ
CommandHandler::CommandHandler()
{
	_fire = new CommandFire();
	_move = new CommandMove();
	_chage_level = new CommandChangeWater();
}
//=============================================================================
// デストラクタ
CommandHandler::~CommandHandler()
{
	SafeDelete(_fire);
	SafeDelete(_move);
	SafeDelete(_chage_level);
}
//=============================================================================
// 入力コマンド
Command* CommandHandler::HandleInput(InputManager* input, Command::CONTROLLER_TYPE type)
{
	u32 rtrigger_input_event_type = INPUT_EVENT_VALUE_PAD0_RTRIGGER + type;
	s32 rtrigger_pad_value = input->GetEventValue(static_cast<INPUT_EVENT_VALUE>(rtrigger_input_event_type));
	if( input->CheckPress(INPUT_EVENT_SPACE) || rtrigger_pad_value )
	{
		_fire->PressPower(rtrigger_pad_value);
		return _fire;
	}

	return nullptr;
}

//=============================================================================
// 移動用コマンド
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

//=============================================================================
// InputEvent用コマンド
Command* CommandHandler::HandleInputEvent(InputManager* input, Command::CONTROLLER_TYPE type)
{
	u32 input_event_type;
	u32 input_controller_type;

	if( type == Command::CONTROLLER_TYPE_1P)
	{
		input_controller_type = 0;
	}
	else
	{
		input_controller_type = 15;
	}
	input_event_type = input_controller_type + INPUT_EVENT_PAD0_14;
	if( input->CheckPress(static_cast<INPUT_EVENT>(input_event_type)) )
	{
		static_cast<CommandChangeWater*>(_chage_level)->SetLevel(0);

		return _chage_level;
	}
	input_event_type = input_controller_type + INPUT_EVENT_PAD0_15;
	if( input->CheckPress(static_cast<INPUT_EVENT>(input_event_type)) )
	{
		static_cast<CommandChangeWater*>(_chage_level)->SetLevel(1);

		return _chage_level;
	}
	input_event_type = input_controller_type + INPUT_EVENT_PAD0_12;
	if( input->CheckPress(static_cast<INPUT_EVENT>(input_event_type)) )
	{
		static_cast<CommandChangeWater*>(_chage_level)->SetLevel(2);

		return _chage_level;
	}

	return nullptr;
}