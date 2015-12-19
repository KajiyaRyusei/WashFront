//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �~�b�V�����t���[��
// 
// Created by Chiharu Kamiyama on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "mission_frame.h"
#include "Windows/window.h"


//�萔
static const D3DXVECTOR3 scaling(500.0f, 80.0f, 1.0f);


//=============================================================================
// ������
void MissionFrame::Initialize()
{
	//�e�l������
	CreateTexture(TEXT("Data/Texture/mission_frame.png"));
	_texture_uv = D3DXVECTOR2(1.0f, 1.0f);
	_texture_offset = D3DXVECTOR2(0.0f, 0.0f);
	_texture_alpha = 1.0f;

	_scaling = scaling;
	_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_rotation = 0.0f;
}

//=============================================================================
// �I��
void MissionFrame::Finalize()
{

}

//=============================================================================
// �X�V
void MissionFrame::Update()
{
	ScreenUnit::Update();

}

//=============================================================================
// �`��
void MissionFrame::Draw()
{
	ScreenUnit::Draw();

}