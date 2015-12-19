//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Ui
// 
// Created by Chiharu Kamiyama on 20151012
//
// 変更点：カジヤ
//<仕様変更により以下の部分を変更>
//・LevelUpMeterを呼ぶと水が常に満タンの状態で呼ばれるので、レベルアップする部分と水の量を決める部分を別々にした
//・水の量を取得できるようにした。
//・オーバーヒート状態にするようにした。
//・水の量をアップさせる関数を追加
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
class Meter;
class MissionUi;
class GameScore;

//*****************************************************************************
// クラス設計
class Ui : public Unit
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

	//マップセット（マップの一周の距離、初期プレイヤー座標）
	void SetMap(float max_map_distance, D3DXVECTOR3 init_player_position);

	//マップ更新(引数…プレイヤー座標)
	virtual void UpdateMap(D3DXVECTOR3 player_position);

	//スコア更新（引数…プレイヤー番号、スコア加算数）
	void UpdateScore(int player_id, int addscore);

	//メーター水量更新（引数…プレイヤー番号、水量減算数）
	void UpdateMeter(int playe_id, float amount);

	//メーターレベルアップ（引数…プレイヤー番号、レベル（1～3））
	void LevelUpMeter(int player_id, int level);

	// 水の最大量決定(引数…プレイヤー番号、最大水量)
	void MaxWaterMeter(int player_id, float max_water);

	// 水の量取得
	fx32 GetWaterMeter(s32 player_id);

	// オーバーヒート
	void OverHeat(s32 player_id);

	//メーター水量更新（引数…プレイヤー番号、水量加算数）
	void UpdateMeterAdd(int playe_id, float amount);

	// スコアの取得
	s32 GetScore(int player_id);

private:
	Map* _map;
	Meter* _meter;
	MissionUi* _mission;
	GameScore *_game_score;
};