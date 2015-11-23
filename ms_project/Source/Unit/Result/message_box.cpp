//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Message_Box
// 
// Created by Toshiki Mochizuki on 20151123
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit\Result/message_box.h"

//*****************************************************************************
// const
const D3DXVECTOR3	scaling		= D3DXVECTOR3( 150.0f , 40.0f , 0.0f );

//=============================================================================
// ������
void Message_BoxUnit::Initialize()
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
	// ���W( �K���O�ŃZ�b�g���邱�� )
	_position	= D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
}

//=============================================================================
// �I��
void Message_BoxUnit::Finalize()
{

}

//=============================================================================
// �X�V
void Message_BoxUnit::Update()
{
	ScreenUnit::Update();
}

//=============================================================================
// �X�V
void Message_BoxUnit::CollisionUpdate()
{

}

//=============================================================================
// �`��
void Message_BoxUnit::Draw()
{
	ScreenUnit::Draw();
}

