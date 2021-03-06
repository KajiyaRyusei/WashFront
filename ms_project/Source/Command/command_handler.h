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
	Command* HandleInput(InputManager* input, Command::CONTROLLER_TYPE type);

	// 移動用コマンド
	Command* HandleInputMove(InputManager* input, Command::CONTROLLER_TYPE type);

	// InputEvent用コマンド
	Command* HandleInputEvent(InputManager* input, Command::CONTROLLER_TYPE type);

private:
	Command* _fire;
	Command* _move;
	Command* _chage_level;
};