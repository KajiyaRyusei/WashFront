//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// メーター水
// 
// Created by Chiharu Kamiyama on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "meter_water.h"
#include "Windows/window.h"
#include "Unit/screen_unit.h"

//定数
static const D3DXVECTOR3 scaling(45.0f, 80.0f, 1.0f);


//=============================================================================
// 初期化
void MeterWater::Initialize()
{
	//各値初期化
	CreateTexture(TEXT("Data/Texture/meter_water.png"));
	_texture_uv = D3DXVECTOR2(1.0f, 1.0f);
	_texture_offset = D3DXVECTOR2(0.0f, 0.0f);
	_texture_alpha = 1.0f;

	_scaling = scaling;
	_position = D3DXVECTOR3(_scaling.x / 2 + 40.0f,
		_application->GetWindow()->GetSizeWindowHeight() - _scaling.y / 2 - 60.0f,
		0.0f);
	_rotation = 0.0f;

	_water_max = 500.0f;
	_current_water = _water_max;

}

//=============================================================================
// 終了
void MeterWater::Finalize()
{

}

//=============================================================================
// 更新
void MeterWater::Update()
{

	ScreenUnit::Update();
}

//=============================================================================
// 描画
void MeterWater::Draw()
{
	ScreenUnit::Draw();

}

//=============================================================================
// 水量変化
void MeterWater::UpdateMeterWater(float amount)
{
	if (_current_water > 0.0f)
	{
		_current_water -= amount;

		//現在の水量計算
		float per = _current_water / _water_max;

		float oldscale_y = _scaling.y;

		//スケール減算
		_scaling.y = scaling.y * per;

		float distance_scale = oldscale_y - _scaling.y;

		//場所減算
		_position.y += distance_scale / 2;
	}
}

//=============================================================================
// メーターレベルアップ
void MeterWater::LevelUpMeterWater(float water_max)
{
	//最大量更新
	_water_max = water_max;
	_current_water = _water_max;

	//スケールをもとに戻す
	_scaling.y = scaling.y;

	//場所をもとに戻す
	_position = _start_position;
}
