//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Number
// 
// Created by Toshiki Mochizuki on 20151123
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit\number.h"

//*****************************************************************************
// const
const D3DXVECTOR3	position	= D3DXVECTOR3( 0.0f , 0.0f , 0.0 );
const D3DXVECTOR3	scaling		= D3DXVECTOR3( 0.0f , 0.0f , 0.0f );

//=============================================================================
// ������
void NumberUnit::Initialize()
{
	// �e�N�X�`��
	CreateTexture(TEXT("Data/Texture/number.png"));
	// UV�l
	_texture_uv		= D3DXVECTOR2(1.0f, 0.1f);
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
	// �l
	_value		= 0;
}

//=============================================================================
// �I��
void NumberUnit::Finalize()
{

}

//=============================================================================
// �X�V
void NumberUnit::Update()
{
	Reflection();
	ScreenUnit::Update();
}

//=============================================================================
// �X�V
void NumberUnit::CollisionUpdate()
{

}

//=============================================================================
// �`��
void NumberUnit::Draw()
{
	ScreenUnit::Draw();
}

//=============================================================================
// ���f
void NumberUnit::Reflection()
{
	float v = float( _value % 10 ) * 0.1f + 0.1f;

	_texture_offset	= D3DXVECTOR2( 0.0f , v );
	//_texture_uv		= D3DXVECTOR2( 1.0f , v );
}

//=============================================================================
// ���l�Z�b�g
void NumberUnit::SetValue( int value )
{
	_value = value;
}