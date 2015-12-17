//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �}�b�v�w�i
// 
// Created by Chiharu Kamiyama on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "meter_frame.h"
#include "Windows/window.h"


//�萔
static const D3DXVECTOR3 scaling(100.0f, 150.0f, 1.0f);


//=============================================================================
// ������
void MeterFrame::Initialize()
{
	//�e�l������
	CreateTexture(TEXT("Data/Texture/meter_frame.png"));
	_texture_uv = D3DXVECTOR2(1.0f, 1.0f);
	_texture_offset = D3DXVECTOR2(0.0f, 0.0f);
	_texture_alpha = 1.0f;

	_scaling = scaling;
	_position = D3DXVECTOR3(_scaling.x / 2 + 15.0f,
		_application->GetWindow()->GetSizeWindowHeight() - _scaling.y / 2 - 20.0f,
		0.0f);
	_rotation = 0.0f;
}

//=============================================================================
// �I��
void MeterFrame::Finalize()
{

}

//=============================================================================
// �X�V
void MeterFrame::Update()
{
	ScreenUnit::Update();

}

//=============================================================================
// �`��
void MeterFrame::Draw()
{
	ScreenUnit::Draw();

}