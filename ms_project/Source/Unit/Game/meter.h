//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// メーター
// 
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Unit/unit.h"

//*****************************************************************************
// 前方宣言
class MeterFrame;
class MeterWater;


//*****************************************************************************
// クラス設計
class Meter : public Unit
{
public:

	Meter(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~Meter(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;

	void SetMeterCharacterList(std::list<Unit*> *list);
	
private:
	MeterFrame *_meter_frame;
	MeterWater *_meter_water;
};