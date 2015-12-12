//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// TEXT
// 
// Created by Toshiki Mochizuki on 20151
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
class TextUnit : public ScreenUnit
{
public:

	TextUnit(Application* application, World* world) : ScreenUnit(application, world)
	{
		Initialize();
	}
	virtual ~TextUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;



private:

	int _timeCnt;
	// a値の変化速度
	float _a_speed;

};