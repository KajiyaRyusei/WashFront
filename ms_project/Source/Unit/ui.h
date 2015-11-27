//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Ui
// 
// Created by Ryusei Kajiya on 20151012
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "unit.h"

//*****************************************************************************
// 前方宣言
class Map;


//*****************************************************************************
// クラス設計
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

	//リストに登録
	virtual void SetList(std::list<Unit*> *list);

	//マップ更新
	virtual void UpdateMap(D3DXVECTOR3 player_position);

private:
	Map* _map;
};