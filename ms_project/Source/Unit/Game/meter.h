//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// メーター
// 
// Created by Chiharu Kamiyama on 20151029
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
class MeterGear;
class MeterLevel;


typedef struct
{
	MeterFrame *_meter_frame;
	MeterWater *_meter_water;
	MeterGear *_meter_gear;
	MeterLevel *_meter_level;

}METER;

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

	//メーター水量更新
	void UpdateMeterWater(int player_id, float amount);
	//メーターレベル更新
	void UpdateMeterLevel(int player_id, int level, float water_max);
	//メーター水量取得
	float GetCurrentMeterWater(int player_id);

private:
	METER _meter[2];
};