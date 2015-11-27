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
	//マップ背景の作成
	_map_back = new MapBack(_application, _game_world);

	//マップキャラクターの作成
	for (int i = 0; i < 2; i++)
	{
		_map_character[i] = new MapCharacter(_application, _game_world);
		_map_character[i]->SetId(i);
	}
}


//=============================================================================
// 終了
void Map::Finalize()
{

	SafeDelete(_map_back);
	for (int i = 0; i < 2; i++)
	{
		SafeDelete(_map_character[i]);

	}
}

//=============================================================================
// 更新
void Map::Update()
{	

	_map_back->Update();
	
	for (int i = 0; i < 2; i++)
	{
		_map_character[i]->Update();
	}

}

//=============================================================================
// 描画
void Map::Draw()
{

	_map_back->Draw();
	for (int i = 0; i < 2; i++)
	{
		_map_character[i]->Draw();
	}
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