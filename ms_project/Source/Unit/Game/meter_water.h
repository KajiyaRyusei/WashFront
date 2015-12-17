//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// メーター水
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
class MeterWater : public ScreenUnit
{
public:

	MeterWater(Application* application, World* world) : ScreenUnit(application, world)
	{
		Initialize();
	}
	virtual ~MeterWater(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override{}

	void UpdateMeterWater(float amount);
	void LevelUpMeterWater(float water_max);

	void SetInitPosition(D3DXVECTOR3 position){ _start_position = position; }
	float GetCurrentWater(void){ return _current_water; }


private:
	float _water_max;
	float _current_water;
	D3DXVECTOR3 _start_position;
};