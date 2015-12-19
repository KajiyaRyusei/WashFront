//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 下移動
//
// Created by Ryusei Kajiya on 20151217
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Command/command.h"

//*****************************************************************************
// クラス設計
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