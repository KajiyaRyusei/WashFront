//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Message_Box
// 
// Created by Toshiki Mochizuki on 20151123
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Unit\screen_unit.h"

//*****************************************************************************
// 前方宣言


//*****************************************************************************
// クラス設計
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