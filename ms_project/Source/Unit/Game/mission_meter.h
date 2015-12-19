//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ミッションメーター
// 
// Created by Chiharu Kamiyama on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Unit/screen_unit.h"


//*****************************************************************************
// 前方宣言

//*****************************************************************************
// クラス設計
class MissionMeter : public ScreenUnit
{
public:

	MissionMeter(Application* application, World* world) : ScreenUnit(application, world)
	{
		Initialize();
	}
	virtual ~MissionMeter(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override{}

private:

};