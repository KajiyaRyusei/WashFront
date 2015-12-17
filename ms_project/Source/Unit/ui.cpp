//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Ui
// 
// Created by Ryusei Kajiya on 20151012
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "ui.h"

//GameUnit
#include "Unit/Game/map.h"
#include "Unit/Game/meter.h"
#include "Unit/Game/mission_ui.h"
#include "Unit/Game/game_score.h"

//=============================================================================
// ������
void Ui::Initialize()
{

}

//=============================================================================
// �I
void Ui::Finalize()
{
}

//=============================================================================
// �X�V
void Ui::Update()
{
}

//=============================================================================
// �`��
void Ui::Draw()
{
}

//=============================================================================
// ���X�g��UI�֘A�o�^
void Ui::SetList(std::list<Unit*> *list)
{
	//�}�b�v�o�^
	_map = new Map(_application, _game_world);
	list->push_back(_map);
	_map->SetMapCharacterList(list);

	//���[�^�[�o�^	
	_meter = new Meter(_application, _game_world);
	list->push_back(_meter);
	_meter->SetMeterCharacterList(list);

	//�~�b�V�����o�^
	_mission = new MissionUi(_application, _game_world);
	list->push_back(_mission);
	_mission->SetMissonCharacterList(list);

	//�X�R�A�o�^
	_game_score = new GameScore(_application, _game_world);
	list->push_front(_game_score);
	_game_score->SetGameScoreCharacterList(list);

}

//=============================================================================
//�}�b�v������
void Ui::SetMap(float max_map_distance, D3DXVECTOR3 init_player_position)
{
	_map->SetMap(max_map_distance, init_player_position);
}

//=============================================================================
//�}�b�v�X�V
void Ui::UpdateMap(D3DXVECTOR3 player_position)
{
	_map->SetMapCharacterPosition(player_position);
}


//=============================================================================
//�X�R�A�X�V
void Ui::UpdateScore(int player_id, int addscore)
{
	_game_score->UpdateGameScore(player_id, addscore);
}

//=============================================================================
//���[�^�[���ʍX�V�i�����c�v���C���[�ԍ��A���ʌ��Z���j
void Ui::UpdateMeter(int playe_id, float amount)
{
	_meter->UpdateMeterWater(playe_id, amount);
}

//=============================================================================
//���[�^�[���x���A�b�v�i�����c�v���C���[�ԍ��A���x���i1�`3�j�A�ő吅�ʁj
void Ui::LevelUpMeter(int player_id, int level, float max_water)
{
	_meter->UpdateMeterLevel(player_id, level, max_water);
}