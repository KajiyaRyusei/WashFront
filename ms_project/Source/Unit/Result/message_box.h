//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Message_Box
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
// �N���X�݌v
class Message_BoxUnit : public ScreenUnit
{
public:

	Message_BoxUnit(Application* application, World* world) : ScreenUnit(application, world)
	{
		Initialize();
	}
	virtual ~Message_BoxUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;

	void SetPosition( D3DXVECTOR3 pos )
	{
		_position	= pos;
		_pos		= pos;
	}

private:

	D3DXVECTOR3 _pos;
};