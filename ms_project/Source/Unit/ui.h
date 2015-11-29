//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Ui
// 
// Created by Ryusei Kajiya on 20151012
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "unit.h"

//*****************************************************************************
// �O���錾
class Map;
class Score;
class Meter;

//*****************************************************************************
// �N���X�݌v
class Ui: public Unit
{
public:

	Ui(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~Ui(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override{}

	//���X�g�ɓo�^
	virtual void SetList(std::list<Unit*> *list);

	//�}�b�v�X�V
	virtual void UpdateMap(D3DXVECTOR3 player_position);

	//�X�R�A�X�V
	virtual void UpdateScore(int score);

private:
	Map* _map;
	Score* _score;
	Meter* _meter;
};