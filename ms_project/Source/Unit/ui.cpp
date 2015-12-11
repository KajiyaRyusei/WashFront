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
}

//=============================================================================
//�}�b�v�X�V
void Ui::UpdateMap(D3DXVECTOR3 player_position)
{
	_map->SetMapCharacterPosition(player_position);
}

//=============================================================================
//�X�R�A�X�V
void Ui::UpdateScore(int score)
{
	score = score;
}
