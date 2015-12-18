//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Result_BG
// 
// Created by Toshiki Mochizuki on 20151123
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit\Result\result_bg.h"

//*****************************************************************************
// const
const D3DXVECTOR3	position	= D3DXVECTOR3( 480.0f , 270.0f , 0.0 );
const D3DXVECTOR3	scaling		= D3DXVECTOR3( 960.0f , 540.0f , 0.0f );

//=============================================================================
// ������
void Result_BGUnit::Initialize()
{
	// �e�N�X�`��
	CreateTexture(TEXT("Data/Texture/result_bg.png"));
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
void Result_BGUnit::Finalize()
{

}

//=============================================================================
// �X�V
void Result_BGUnit::Update()
{
	ScreenUnit::Update();
}

//=============================================================================
// �X�V
void Result_BGUnit::CollisionUpdate()
{

}

//=============================================================================
// �`��
void Result_BGUnit::Draw()
{
	ScreenUnit::Draw();
}

