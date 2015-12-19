//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���[�^�[��
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
//�萔
namespace
{
	static const D3DXVECTOR3 kScaling(45.0f, 80.0f, 1.0f);
	static u32 kOverHeatTime = 150;
	static const D3DXVECTOR4 kNormalColor(1.f,1.f,1.f,1.f);
	static const D3DXVECTOR4 kOverHeatColor(1.f, 0.f, 0.f, 1.f);
}

//=============================================================================
// ������
void MeterWater::Initialize()
{
	//�e�l������
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
// �I��
void MeterWater::Finalize()
{

}

//=============================================================================
// �X�V
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
// �`��
void MeterWater::Draw()
{
	ScreenUnit::Draw();
}

//=============================================================================
// ���ʕω�
void MeterWater::UpdateMeterWater(float amount)
{
	if( _current_water > 0.0f )
	{
		_current_water -= amount;

		//���݂̐��ʌv�Z
		float per = _current_water / _water_max;

		float oldscale_y = _scaling.y;

		//�X�P�[�����Z
		_scaling.y = kScaling.y * per;

		float distance_scale = oldscale_y - _scaling.y;

		//�ꏊ���Z
		_position.y += distance_scale / 2;

	}
	if( _current_water <= 0.f)
	{// �I�[�o�[���
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

		//���݂̐��ʌv�Z
		float per = _current_water / _water_max;

		float oldscale_y = _scaling.y;

		//�X�P�[�����Z
		_scaling.y = kScaling.y * per;

		float distance_scale = oldscale_y - _scaling.y;

		//�ꏊ���Z
		_position.y += distance_scale / 2;
	}
}

//=============================================================================
// ���[�^�[���x���A�b�v
void MeterWater::LevelUpMeterWater(float water_max)
{
	//�ő�ʍX�V
	_water_max = water_max;
	_current_water = _water_max;

	//�X�P�[�������Ƃɖ߂�
	_scaling.y = kScaling.y;

	//�ꏊ�����Ƃɖ߂�
	_position = _start_position;
}
