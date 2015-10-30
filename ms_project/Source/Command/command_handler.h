//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// コマンドの受取
//
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Command/command.h"

//*****************************************************************************
// 前方宣言
class InputManager;

//*****************************************************************************
// クラス設計
class CommandHandler
{
public:
	CommandHandler();
	virtual ~CommandHandler();

	// 入力コマンド
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