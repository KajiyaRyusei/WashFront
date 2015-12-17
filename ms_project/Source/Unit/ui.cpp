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
#include "Unit/Game/mission_ui.h"
#include "Unit/Game/game_score.h"

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

	//ミッション登録
	_mission = new MissionUi(_application, _game_world);
	list->push_back(_mission);
	_mission->SetMissonCharacterList(list);

	//スコア登録
	_game_score = new GameScore(_application, _game_world);
	list->push_front(_game_score);
	_game_score->SetGameScoreCharacterList(list);

}

//=============================================================================
//マップ初期化
void Ui::SetMap(float max_map_distance, D3DXVECTOR3 init_player_position)
{
	_map->SetMap(max_map_distance, init_player_position);
}

//=============================================================================
//マップ更新
void Ui::UpdateMap(D3DXVECTOR3 player_position)
{
	_map->SetMapCharacterPosition(player_position);
}


//=============================================================================
//スコア更新
void Ui::UpdateScore(int player_id, int addscore)
{
	_game_score->UpdateGameScore(player_id, addscore);
}

//=============================================================================
//メーター水量更新（引数…プレイヤー番号、水量減算数）
void Ui::UpdateMeter(int playe_id, float amount)
{
	_meter->UpdateMeterWater(playe_id, amount);
}

//=============================================================================
//メーターレベルアップ（引数…プレイヤー番号、レベル（1～3）、最大水量）
void Ui::LevelUpMeter(int player_id, int level, float max_water)
{
	_meter->UpdateMeterLevel(player_id, level, max_water);
}