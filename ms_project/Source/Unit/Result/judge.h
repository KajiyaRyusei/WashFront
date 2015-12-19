//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// JudgeUnit
// 
// Created by Toshiki Mochizuki on 20151123
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "Unit\screen_unit.h"

//*****************************************************************************
// �O���錾

//*****************************************************************************
// const
const int disp_time = 1;

//*****************************************************************************
// �N���X�݌v
class JudgeUnit : public ScreenUnit
{
public:

	JudgeUnit(Application* application, World* world) : ScreenUnit(application, world)
	{
		Initialize();
	}
	virtual ~JudgeUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;

	void SetTime(int time)
	{
		_timeCnt = time;
	}

	int GetTime(void)
	{
		return _timeCnt;
	}

private:

	int _timeCnt;
};