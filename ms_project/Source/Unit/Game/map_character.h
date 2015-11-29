//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// マップキャラクター
// 
// Created by Chiharu Kamiyama on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Unit/screen_unit.h"


//*****************************************************************************
// 前方宣言

//*****************************************************************************
// クラス設計
class MapCharacter : public ScreenUnit
{
public:

	MapCharacter(Application* application, World* world) : ScreenUnit(application, world)
	{
		Initialize();
	}
	virtual ~MapCharacter(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override{}

	void SetMapCharacterPosition(D3DXVECTOR3 position);
	float GetMapCharacterDistance(void){ return _map_distance; };

	void SetId(int id){ _id = id; }

private:
	float _map_distance;
	float _character_distance;
	D3DXVECTOR3 _map_character_old_position;
	D3DXVECTOR3 _map_character_position;
	int _id;

};