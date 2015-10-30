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
#include "Command/command_move_front.h"
#include "Command/command_move_back.h"
#include "Command/command_move_right.h"
#include "Command/command_move_left.h"
#include "Command/command_move_up.h"
#include "Command/command_move_down.h"

//=============================================================================
// コンストラクタ
CommandHandler::CommandHandler()
{
	_fire = new CommandFire();
	_move_front = new CommandMoveFront();
	_move_back  = new CommandMoveBack();
	_move_right = new CommandMoveRight();
	_move_left  = new CommandMoveLeft();
	_move_up = new CommandMoveUp();
	_move_down  = new CommandMoveDown();
}
//=============================================================================
// デストラクタ
CommandHandler::~CommandHandler()
{
	SafeDelete(_move_front);
	SafeDelete(_move_back);
	SafeDelete(_move_right);
	SafeDelete(_move_left);
	SafeDelete(_move_up);
	SafeDelete(_move_down);
	SafeDelete(_fire);
}
//=============================================================================
// 入力コマンド
Command* CommandHandler::HandleInput(InputManager* input)
{
	/*if( input->CheckPress(INPUT_EVENT_A) )
	{
		return _move_left;
	}
	if( input->CheckPress(INPUT_EVENT_D) )
	{
		return _move_right;
	}
	if( input->CheckPress(INPUT_EVENT_W) )
	{
		return _move_front;
	}
	if( input->CheckPress(INPUT_EVENT_S) )
	{
		return _move_back;
	}
	if( input->CheckPress(INPUT_EVENT_Q) )
	{
		return _move_up;
	}
	if( input->CheckPress(INPUT_EVENT_E) )
	{
		return _move_down;
	}*/
	if( input->CheckPress(INPUT_EVENT_SPACE) )
	{
		return _fire;
	}

	return nullptr;
}