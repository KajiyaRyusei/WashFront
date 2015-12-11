//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// プレイヤーへのコマンド
//
// Created by Ryusei Kajiya on 20151204
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// 前方宣言
class PlayerUnit;

//*****************************************************************************
// クラス設計
class Command
{
public:

	enum CONTROLLER_TYPE
	{
		CONTROLLER_TYPE_1P = 0,
		CONTROLLER_TYPE_2P = 8
	};

	Command(){}
	virtual ~Command(){}

	virtual void Execute(PlayerUnit* player) = 0;

	void PressPower(const s32 power){ _power = power; }

protected:

	s32 _power;

};