//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Score
// 
// Created by Toshiki Mochizuki on 20151123
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "Unit\unit.h"

//*****************************************************************************
// �O���錾
class NumberUnit;

//*****************************************************************************
// �萔
const int digit = 5;

//*****************************************************************************
// �N���X�݌v
class ScoreUnit : public Unit
{
public:

	ScoreUnit(Application* application, World* world ) : Unit( application , world )
	{
		_app	= application;
		_world	= world;
		Initialize();
	}
	virtual ~ScoreUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;

	// �X�R�A�Z�b�g
	void SetScoreValue( int value )
	{
		_score_value = value;
	}

private:

	// �ݏ�
	int Pow( int num , int mulutipiler );

	NumberUnit*		_score[ digit ];
	Application*	_app;
	World*			_world;
	int				_score_value;

	// ���̃N���X�̃C���X�^���X�̐�
	static int		_num;
};