//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// JudgeUnit
// 
// Created by Toshiki Mochizuki on 20151123
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit\Result/Judge.h"

//*****************************************************************************
// const
const D3DXVECTOR3	position	= D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
const D3DXVECTOR3	scaling		= D3DXVECTOR3( 300.0f , 80.0f , 0.0f );

//=============================================================================
// ������
void JudgeUnit::Initialize()
{
	// �e�N�X�`��
	CreateTexture(TEXT("Data/Texture/black.jpg"));
	// UV�l
	_texture_uv		= D3DXVECTOR2(1.0f, 1.0f);
	// �I�t�Z�b�g
	_texture_offset = D3DXVECTOR2(0.0f, 0.0f);
	// �����l
	_texture_alpha	= 1.0f;
	// �p�x
	_rotation	= 0.0f;
	// �傫��
	_scaling	= scaling;
	// ���W
	_position	= position;
}

//=============================================================================
// �I��
void JudgeUnit::Finalize()
{

}

//=============================================================================
// �X�V
void JudgeUnit::Update()
{
	ScreenUnit::Update();
}

//=============================================================================
// �X�V
void JudgeUnit::CollisionUpdate()
{

}

//=============================================================================
// �`��
void JudgeUnit::Draw()
{
	ScreenUnit::Draw();
}

