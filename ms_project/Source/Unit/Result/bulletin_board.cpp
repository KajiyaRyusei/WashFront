//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Message_Box
// 
// Created by Toshiki Mochizuki on 20151123
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit\Result/bulletin_board.h"

//*****************************************************************************
// const
const D3DXVECTOR3	position	= D3DXVECTOR3( 480.0f , 240.0f , 0.0 );
const D3DXVECTOR3	scaling		= D3DXVECTOR3( 800.0f , 430.0f , 0.0f );

//=============================================================================
// ������
void BulletinUnit::Initialize()
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
void BulletinUnit::Finalize()
{

}

//=============================================================================
// �X�V
void BulletinUnit::Update()
{
	ScreenUnit::Update();
}

//=============================================================================
// �X�V
void BulletinUnit::CollisionUpdate()
{

}

//=============================================================================
// �`��
void BulletinUnit::Draw()
{
	ScreenUnit::Draw();
}

