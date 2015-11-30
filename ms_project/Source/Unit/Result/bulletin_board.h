//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Bulletin_Board
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
class BulletinUnit : public ScreenUnit
{
public:

	BulletinUnit(Application* application, World* world) : ScreenUnit(application, world)
	{
		Initialize();
	}
	virtual ~BulletinUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;

	static bool GetDispFlg( void )
	{
		return _disp_flg;
	}

	static bool GetUpdateFlg( void )
	{
		return _update_flg;
	}

private:

	int _timeCnt;

	static bool _disp_flg;
	static bool _update_flg;

};