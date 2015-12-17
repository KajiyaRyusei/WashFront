//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���[�^�[
// 
// Created by Chiharu Kamiyama on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "Unit/unit.h"

//*****************************************************************************
// �O���錾
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
// �N���X�݌v
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

	//���[�^�[���ʍX�V
	void UpdateMeterWater(int player_id, float amount);
	//���[�^�[���x���X�V
	void UpdateMeterLevel(int player_id, int level, float water_max);
	//���[�^�[���ʎ擾
	float GetCurrentMeterWater(int player_id);

private:
	METER _meter[2];
};