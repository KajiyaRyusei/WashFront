//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���[�^�[���x��
// 
// Created by Chiharu Kamiyama on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "meter_level.h"
#include "Windows/window.h"


//�萔
static const D3DXVECTOR3 scaling(90.0f, 50.0f, 1.0f);

//=============================================================================
// ������
void MeterLevel::Initialize()
{
	//�e�l������
	CreateTexture(TEXT("Data/Texture/meter_level.png"));
	_texture_uv = D3DXVECTOR2(1.0f, 0.3f);
	_texture_offset = D3DXVECTOR2(0.0f, 0.0f);
	_texture_alpha = 1.0f;

	_scaling = scaling;
	_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_rotation = 0.0f;

	_meter_level = 1;
}

//=============================================================================
// �I��
void MeterLevel::Finalize()
{

}

//=============================================================================
// �X�V
void MeterLevel::Update()
{
	if (_texture_offset.y != (_meter_level - 1) * 0.33f)
	{
		_texture_offset.y += 0.05f;

		if (_texture_offset.y >= (_meter_level - 1) * 0.33f)
		{
			_texture_offset.y = (_meter_level - 1) * 0.33f;
		}
	}
	ScreenUnit::Update();

}

//=============================================================================
// �`��
void MeterLevel::Draw()
{
	ScreenUnit::Draw();
}

//=============================================================================
// �`��
void MeterLevel::UpdateWaerLevel(int level)
{
	_meter_level = level;
}