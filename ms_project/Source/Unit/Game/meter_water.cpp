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
							_application->GetWindow()->GetSizeWindowHeight() - _scaling.y/2 - 60.0f,
							0.0f);
	_rotation = 0.0f;
}

//=============================================================================
// �I��
void MeterWater::Finalize()
{

}

//=============================================================================
// �X�V
void MeterWater::Update()
{	/*
	_position.y += 1.0f;
	_scaling.y -= 1.0f;*/

	ScreenUnit::Update();
}

//=============================================================================
// �`��
void MeterWater::Draw()
{
	ScreenUnit::Draw();

}