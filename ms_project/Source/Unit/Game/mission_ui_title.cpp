//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �~�b�V����UI�^�C�g��
// 
// Created by Chiharu Kamiyama on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "mission_ui_title.h"
#include "Windows/window.h"


//�萔
static const D3DXVECTOR3 scaling(100.0f, 40.0f, 1.0f);


//=============================================================================
// ������
void MissionUiTitle::Initialize()
{
	//�e�l������
	CreateTexture(TEXT("Data/Texture/mission_ui_title.png"));
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
void MissionUiTitle::Finalize()
{

}

//=============================================================================
// �X�V
void MissionUiTitle::Update()
{
	ScreenUnit::Update();

}

//=============================================================================
// �`��
void MissionUiTitle::Draw()
{
	ScreenUnit::Draw();

}