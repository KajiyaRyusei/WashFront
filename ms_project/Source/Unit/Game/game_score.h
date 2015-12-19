//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �Q�[���X�R�A
// 
// Created by Ryusei Kajiya on 20151029
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
class ScoreUnit;
class GameScoreCharacter;

typedef struct
{
	int score;

	ScoreUnit *_score_unit;	//�X�R�A���j�b�g
	GameScoreCharacter *_game_score_character;
	
}GAME_SCORE;

//*****************************************************************************
// �N���X�݌v
class GameScore : public Unit
{
public:

	GameScore(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~GameScore(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;
	
	void SetGameScoreCharacterList(std::list<Unit*> *list);

	void UpdateGameScore(int player_id, int addscore);

private:
	GAME_SCORE _game_score[2];
};