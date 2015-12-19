//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �Q�[���X�R�A
// 
// Created by Chiharu Kamiyama on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "game_score.h"
#include "Unit/Game/game_score.h"
#include "Unit/Result/score.h"
#include "Unit/Game/game_score_character.h"

static const float _game_score_grade = 0.2f;

//=============================================================================
// ������
void GameScore::Initialize()
{
	
}


//=============================================================================
// �I��
void GameScore::Finalize()
{

}

//=============================================================================
// �X�V
void GameScore::Update()
{

}

//=============================================================================
// �`��
void GameScore::Draw()
{
}

//=============================================================================
// �����蔻��
void GameScore::CollisionUpdate()
{
}

//=============================================================================
//���X�g�Z�b�g
void GameScore::SetGameScoreCharacterList(std::list<Unit*> *list)
{
	for (int i = 0; i < 2; i++)
	{
		//�X�R�A������
		_game_score[i].score = 0;

		//�Q�[���X�R�A�o�^
		_game_score[i]._score_unit = new ScoreUnit(_application, _game_world);
		list->push_back(_game_score[i]._score_unit);

		//�|�C���g�����o�^
		_game_score[i]._game_score_character = new GameScoreCharacter(_application, _game_world);
		list->push_back(_game_score[i]._game_score_character);

	}

	_game_score[0]._score_unit->SetPos(D3DXVECTOR3(1160.0f, 50.0f, 0.0f));
	_game_score[0]._game_score_character->SetPosition(D3DXVECTOR3(1240.0f, 55.0f, 0.0f));

	_game_score[1]._score_unit->SetPos(D3DXVECTOR3(1160.0f, 450.0f, 0.0f));
	_game_score[1]._game_score_character->SetPosition(D3DXVECTOR3(1240.0f, 455.0f, 0.0f));

	_game_score[0]._score_unit->SetScale(D3DXVECTOR3(50.0f, 100.0f, 0.0f));
	_game_score[1]._score_unit->SetScale(D3DXVECTOR3(50.0f, 100.0f, 0.0f));

}


//=============================================================================
//�X�R�A�X�V
void GameScore::UpdateGameScore(int player_id, int addscore)
{
	_game_score[player_id].score += addscore;

	_game_score[player_id]._score_unit->SetDestScore(_game_score[player_id].score);

	_game_score[player_id]._score_unit->CountUp(_game_score_grade);

}