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
#include "Shader/Shader/screen_2d_shader.h"
//定数
namespace
{
	static const D3DXVECTOR3 kScaling(45.0f, 80.0f, 1.0f);
	static u32 kOverHeatTime = 150;
	static const D3DXVECTOR4 kNormalColor(1.f,1.f,1.f,1.f);
	static const D3DXVECTOR4 kOverHeatColor(1.f, 0.f, 0.f, 1.f);
}

//=============================================================================
// 初期化
void MeterWater::Initialize()
{
	//各値初期化
	CreateTexture(TEXT("Data/Texture/meter_water.png"));
	_texture_uv = D3DXVECTOR2(1.0f, 1.0f);
	_texture_offset = D3DXVECTOR2(0.0f, 0.0f);
	_texture_alpha = 1.0f;

	_scaling = kScaling;
	_position = D3DXVECTOR3(_scaling.x / 2 + 40.0f,
		_application->GetWindow()->GetSizeWindowHeight() - _scaling.y / 2 - 60.0f,
		0.0f);
	_rotation = 0.0f;

	_water_max = 500.0f;
	_current_water = _water_max;
	_is_overheat = false;
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
	
	if( _is_overheat )
	{
		++_over_heat_time;
		if( kOverHeatTime < _over_heat_time )
		{
			_is_overheat = false;
		}
		_shader->SetAmbientColor(kOverHeatColor);
	}
	else
	{
		_shader->SetAmbientColor(kNormalColor);
	}

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
	if( _current_water > 0.0f )
	{
		_current_water -= amount;

		//現在の水量計算
		float per = _current_water / _water_max;

		float oldscale_y = _scaling.y;

		//スケール減算
		_scaling.y = kScaling.y * per;

		float distance_scale = oldscale_y - _scaling.y;

		//場所減算
		_position.y += distance_scale / 2;

	}
	if( _current_water <= 0.f)
	{// オーバー状態
		_is_overheat = true;
		_over_heat_time = 0;
	}
}
void MeterWater::UpdateMeterWaterAdd(float amount)
{
	if( _is_overheat == true )
	{
		return;
	}
	if( _current_water < _water_max )
	{
		_current_water += amount;

		//現在の水量計算
		float per = _current_water / _water_max;

		float oldscale_y = _scaling.y;

		//スケール減算
		_scaling.y = kScaling.y * per;

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
	_scaling.y = kScaling.y;

	//場所をもとに戻す
	_position = _start_position;
}
