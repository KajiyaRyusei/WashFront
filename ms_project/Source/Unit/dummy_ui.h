//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �_�~�[Ui
// 
// Created by Ryusei Kajiya on 20151012
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "ui.h"

//*****************************************************************************
// �O���錾

//*****************************************************************************
// �N���X�݌v
class DummyUi: public Ui
{
public:

	DummyUi(Application* application, World* world) : Ui(application, world)
	{
		Initialize();
	}
	virtual ~DummyUi(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override{}

	void SetList(std::list<Unit*> *list);
	void UpdateMap(D3DXVECTOR3 player_position);

private:

};