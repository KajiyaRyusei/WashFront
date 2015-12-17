//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// メーター
// 
// Created by Chiharu Kamiyama on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "meter.h"
#include "Unit/Game/meter_frame.h"
#include "Unit/Game/meter_water.h"
#include "Unit/Game/meter_level.h"
#include "Unit/Game/meter_gear.h"
#include "Windows/window.h"


//=============================================================================
// 初期化
void Meter::Initialize()
{
}


//=============================================================================
// 終了
void Meter::Finalize()
{

}

//=============================================================================
// 更新
void Meter::Update()
{
/*	
	//水量更新
	UpdateMeterWater(0, 3);

	float water = GetCurrentMeterWater(0);

	//メーターレベルアップ
	if (water <= 0.0f)
	{
		UpdateMeterLevel(0, 2, 700);
	}
	*/
}

//=============================================================================
// 描画
void Meter::Draw()
{
}

//=============================================================================
// 当たり判定
void Meter::CollisionUpdate()
{
}


//=============================================================================
//リストセット
void Meter::SetMeterCharacterList(std::list<Unit*> *list)
{
	float window_height = (float)_application->GetWindow()->GetSizeWindowHeight();

	//メーター水をリストに登録
	for (int i = 0; i < 2; i++)
	{
		//メーター歯車をリストに登録
		_meter[i]._meter_gear = new MeterGear(_application, _game_world);
		list->push_back(_meter[i]._meter_gear);

		//メーター水をリストに登録
		_meter[i]._meter_water = new MeterWater(_application, _game_world);
		list->push_back(_meter[i]._meter_water);

		//メーター枠をリストに登録
		_meter[i]._meter_frame = new MeterFrame(_application, _game_world);
		list->push_back(_meter[i]._meter_frame);

		//メーターレベルをリストに登録
		_meter[i]._meter_level = new MeterLevel(_application, _game_world);
		list->push_back(_meter[i]._meter_level);

	}

	float meter_height = window_height - 210.0f / 2;

	_meter[0]._meter_frame->SetPosition(D3DXVECTOR3(85.0f, meter_height + 20.0f, 0.0f));
	_meter[0]._meter_gear->SetPosition(D3DXVECTOR3(85.0f, meter_height + 20.0f, 0.0f));
	_meter[0]._meter_level->SetPosition(D3DXVECTOR3(85.0f, meter_height - 50 + 20.0f, 0.0f));
	_meter[0]._meter_water->SetPosition(D3DXVECTOR3(85.0f, meter_height + 20.0f, 0.0f));
	_meter[0]._meter_water->SetInitPosition(D3DXVECTOR3(85.0f, meter_height + 20.0f, 0.0f));

	float meter_height_center_distance = meter_height - window_height / 2;

	_meter[1]._meter_frame->SetPosition(D3DXVECTOR3(85.0f, meter_height_center_distance, 0.0f));
	_meter[1]._meter_gear->SetPosition(D3DXVECTOR3(85.0f, meter_height_center_distance, 0.0f));
	_meter[1]._meter_level->SetPosition(D3DXVECTOR3(85.0f, meter_height_center_distance - 50, 0.0f));
	_meter[1]._meter_water->SetPosition(D3DXVECTOR3(85.0f, meter_height_center_distance, 0.0f));
	_meter[1]._meter_water->SetInitPosition(D3DXVECTOR3(85.0f, meter_height_center_distance, 0.0f));
}

//=============================================================================
//メーター水量更新
void Meter::UpdateMeterWater(int player_id, float amount)
{
	_meter[player_id]._meter_water->UpdateMeterWater(amount);
}

//=============================================================================
//メーター水量レベル更新
void Meter::UpdateMeterLevel(int player_id, int level, float water_max)
{
	//水量更新
	_meter[player_id]._meter_water->LevelUpMeterWater(water_max);
	_meter[player_id]._meter_level->UpdateWaerLevel(level);
}

//=============================================================================
//メーター水量取得
float Meter::GetCurrentMeterWater(int player_id)
{
	float water = _meter[player_id]._meter_water->GetCurrentWater();

	return water;
}


