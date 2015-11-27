//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// AIM
// 
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Unit/unit.h"

//*****************************************************************************
// 前方宣言
class MapBack;
class MapCharacter;

static const int kPlayerNum = 2;

//*****************************************************************************
// クラス設計
class Map : public Unit
{
public:

	Map(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~Map(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;

	//マップキャラクター位置設定
	void SetMapCharacterPosition(D3DXVECTOR3 position);
	
private:
	MapBack *_map_back;
	MapCharacter *_map_character[2];
};