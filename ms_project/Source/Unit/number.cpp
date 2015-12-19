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
const D3DXVECTOR3	position = D3DXVECTOR3(0.0f, 0.0f, 0.0);
const D3DXVECTOR3	scaling = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
const float			speed = 1.0f / 5.0f;

//=============================================================================
// ������
void NumberUnit::Initialize()
{
	// �e�N�X�`��
	CreateTexture(TEXT("Data/Texture/number_color_yellow.png"));
	// UV�l
	_texture_uv = D3DXVECTOR2(1.0f, 0.1f);
	// �I�t�Z�b�g
	_texture_offset = D3DXVECTOR2(0.0f, 0.0f);
	// �����l
	_texture_alpha = 1.0f;
	// ���W
	_position = position;
	// �p�x
	_rotation = 0.0f;
	// �傫��
	_scaling = scaling;
	// �l
	_value = 0;

	_grade = 0.0f;
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
	float v = float(_value % 10) * 0.1f;
	D3DXVECTOR2 dest = D3DXVECTOR2(0.0f, v);
	_grade += speed;
	if( _grade >= 1.0f )
	{
		_grade = 1.0f;
	}
	D3DXVec2Lerp(&_texture_offset, &_texture_offset, &dest, _grade);//_texture_offset	= D3DXVECTOR2( 0.0f , v );
	if( _grade >= 1.0f )
	{
		_grade = 0.0f;
	}
}

//=============================================================================
// ���l�Z�b�g
void NumberUnit::SetValue(int value)
{
	_value = value;
}