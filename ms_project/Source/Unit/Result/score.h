//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Score
// 
// Created by Toshiki Mochizuki on 20151123
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Unit\unit.h"

//*****************************************************************************
// 前方宣言
class NumberUnit;

//*****************************************************************************
// 定数
const int digit = 5;

//*****************************************************************************
// クラス設計
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

	// スコアセット
	void SetScoreValue( int value )
	{
		_score_value = value;
	}

private:

	// 累乗
	int Pow( int num , int mulutipiler );

	NumberUnit*		_score[ digit ];
	Application*	_app;
	World*			_world;
	int				_score_value;

	// このクラスのインスタンスの数
	static int		_num;
};