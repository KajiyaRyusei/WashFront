//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// LOGO_BG
// 
// Created by Toshiki Mochizuki on 20151122
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit\Title\logo_bg.h"

//*****************************************************************************
// const
const D3DXVECTOR3	position	= D3DXVECTOR3( 480.0f , 150.0f , 0.0 );
const D3DXVECTOR3	scaling		= D3DXVECTOR3( 500.0f , 250.0f , 0.0f );

//=============================================================================
// ������
void Logo_BGUnit::Initialize()
{
	// �e�N�X�`��
	CreateTexture(TEXT("Data/Texture/white.jpg"));
	// UV�l
	_texture_uv		= D3DXVECTOR2(1.0f, 1.0f);
	// �I�t�Z�b�g
	_texture_offset = D3DXVECTOR2(0.0f, 0.0f);
	// �����l
	_texture_alpha	= 1.0f;
	// ���W
	_position	= position;
	// �p�x
	_rotation	= 0.0f;
	// �傫��
	_scaling	= scaling;
}

//=============================================================================
// �I��
void Logo_BGUnit::Finalize()
{

}

//=============================================================================
// �X�V
void Logo_BGUnit::Update()
{
	ScreenUnit::Update();
}

//=============================================================================
// �X�V
void Logo_BGUnit::CollisionUpdate()
{

}

//=============================================================================
// �`��
void Logo_BGUnit::Draw()
{
	ScreenUnit::Draw();
}

