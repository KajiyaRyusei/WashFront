//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �~�b�V�������[�^�[
// 
// Created by Chiharu Kamiyama on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "mission_meter.h"
#include "Windows/window.h"


//�萔
static const D3DXVECTOR3 scaling(480.0f, 30.0f, 1.0f);


//=============================================================================
// ������
void MissionMeter::Initialize()
{
	//�e�l������
	CreateTexture(TEXT("Data/Texture/mission_meter.png"));
	_texture_uv = D3DXVECTOR2(1.0f, 1.0f);
	_texture_offset = D3DXVECTOR2(0.0f, 0.0f);
	_texture_alpha = 1.0f;

	_scaling = scaling;
	_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_rotation = 0.0f;
}

//=============================================================================
// �I��
void MissionMeter::Finalize()
{

}

//=============================================================================
// �X�V
void MissionMeter::Update()
{
	ScreenUnit::Update();

}

//=============================================================================
// �`��
void MissionMeter::Draw()
{
	ScreenUnit::Draw();

}