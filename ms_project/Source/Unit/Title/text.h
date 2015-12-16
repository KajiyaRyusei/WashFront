//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// TEXT
// 
// Created by Toshiki Mochizuki on 20151
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
// �N���X�݌v
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
	// a�l�̕ω����x
	float _a_speed;

};