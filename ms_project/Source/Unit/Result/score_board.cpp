//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Score_Board
// 
// Created by Toshiki Mochizuki on 20151123
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit\Result/score_board.h"

//*****************************************************************************
// const
const D3DXVECTOR3	position	= D3DXVECTOR3( 0.0f , 0.0f , 0.0 );
const D3DXVECTOR3	scaling		= D3DXVECTOR3( 350.0f , 400.0f , 0.0f );

//=============================================================================
// ������
void Score_BoardUnit::Initialize()
{
	// �e�N�X�`��
	CreateTexture(TEXT("Data/Texture/white.jpg"));
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
void Score_BoardUnit::Finalize()
{

}

//=============================================================================
// �X�V
void Score_BoardUnit::Update()
{
	ScreenUnit::Update();
}

//=============================================================================
// �X�V
void Score_BoardUnit::CollisionUpdate()
{

}

//=============================================================================
// �`��
void Score_BoardUnit::Draw()
{
	ScreenUnit::Draw();
}

