//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// マップ
// 
// Created by Chiharu Kamiyama on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "map.h"
#include "Unit/Game/map_back.h"
#include "Unit/Game/map_character.h"


//=============================================================================
// 初期化
void Map::Initialize()
{
}


//=============================================================================
// 終了
void Map::Finalize()
{

}

//=============================================================================
// 更新
void Map::Update()
{

}

//=============================================================================
// 描画
void Map::Draw()
{
}

//=============================================================================
// 当たり判定
void Map::CollisionUpdate()
{
}

//=============================================================================
//マップキャラクター位置設定
void Map::SetMapCharacterPosition(D3DXVECTOR3 position)
{
	for (int i = 0; i < 2; i++)
	{
		_map_character[i]->SetMapCharacterPosition(position);
	}
}

//=============================================================================
//マップ初期設定
void Map::SetMap(float max_map_distance, D3DXVECTOR3 init_player_position)
{
	for (int i = 0; i < 2; i++)
	{
		_map_character[i]->SetMapAllDistance(max_map_distance);
		_map_character[i]->InitMapCharacterPosition(init_player_position);
	}
}


//=============================================================================
//リストセット
void Map::SetMapCharacterList(std::list<Unit*> *list)
{
	//マップ背景登録
	_map_back = new MapBack(_application, _game_world);
	list->push_back(_map_back);

	//マップキャラクターの作成
	for (int i = 0; i < 2; i++)
	{
		_map_character[i] = new MapCharacter(_application, _game_world);
		_map_character[i]->SetId(i);
		list->push_back(_map_character[i]);
	}
}