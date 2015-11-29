//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// スコア
// 
// Created by Chiharu Kamiyama on 20151127
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
class ScoreBack;

//*****************************************************************************
// クラス設計
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