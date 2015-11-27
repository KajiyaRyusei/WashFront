//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Score_Board
// 
// Created by Toshiki Mochizuki on 20151123
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Unit\screen_unit.h"

//*****************************************************************************
// 前方宣言


//*****************************************************************************
// クラス設計
class Score_BoardUnit : public ScreenUnit
{
public:

	Score_BoardUnit(Application* application, World* world) : ScreenUnit(application, world)
	{
		Initialize();
	}
	virtual ~Score_BoardUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;



private:

};