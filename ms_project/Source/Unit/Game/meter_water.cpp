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

//�萔
static const D3DXVECTOR3 scaling(45.0f, 80.0f, 1.0f);


//=============================================================================
// ������
void MeterWater::Initialize()
{
	//�e�l������
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
// �I��
void MeterWater::Finalize()
{

}

//=============================================================================
// �X�V
void MeterWater::Update()
{

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
	if (_current_water > 0.0f)
	{
		_current_water -= amount;

		//���݂̐��ʌv�Z
		float per = _current_water / _water_max;

		float oldscale_y = _scaling.y;

		//�X�P�[�����Z
		_scaling.y = scaling.y * per;

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
	_scaling.y = scaling.y;

	//�ꏊ�����Ƃɖ߂�
	_position = _start_position;
}
