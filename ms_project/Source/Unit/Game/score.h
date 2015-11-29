//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �X�R�A
// 
// Created by Chiharu Kamiyama on 20151127
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
class ScoreBack;

//*****************************************************************************
// �N���X�݌v
class Score : public Unit
{
public:

	Score(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~Score(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;

	void SetListScoreCharacter(std::list<Unit*> *list);
	
private:
	ScoreBack *_score_back;
	
};