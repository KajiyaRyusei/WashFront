//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Ui
// 
// Created by Ryusei Kajiya on 20151012
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "ui.h"

//GameUnit
#include "Unit/Game/map.h"
#include "Unit/Game/meter.h"


//=============================================================================
// 初期化
void Ui::Initialize()
{
	
}

//=============================================================================
// 終
void Ui::Finalize()
{
}

//=============================================================================
// 更新
void Ui::Update()
{
}

//=============================================================================
// 描画
void Ui::Draw()
{
}

//=============================================================================
// リストにUI関連登録
void Ui::SetList(std::list<Unit*> *list)
{
	//マップ登録
	_map = new Map(_application, _game_world);
	list->push_back(_map);
	_map->SetMapCharacterList(list);

	//メーター登録	
	_meter = new Meter(_application, _game_world);
	list->push_back(_meter);
	_meter->SetMeterCharacterList(list);
}

//=============================================================================
//マップ更新
void Ui::UpdateMap(D3DXVECTOR3 player_position)
{
	_map->SetMapCharacterPosition(player_position);
}

//=============================================================================
//スコア更新
void Ui::UpdateScore(int score)
{
	score = score;
}
