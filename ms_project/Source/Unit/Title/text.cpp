//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// TEXT
// 
// Created by Toshiki Mochizuki on 20151122
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit\Title\text.h"

//*****************************************************************************
// const
const D3DXVECTOR3	position	= D3DXVECTOR3( 480.0f , 500.0f , 0.0 );
const D3DXVECTOR3	scaling		= D3DXVECTOR3( 500.0f , 50.0f , 0.0f );
const int			exsist_time = 90;

//=============================================================================
// ������
void TextUnit::Initialize()
{
	// �e�N�X�`��
	CreateTexture(TEXT("Data/Texture/moji000.png"));
	// UV�l
	_texture_uv		= D3DXVECTOR2(1.0f, 1.0f);
	// �I�t�Z�b�g
	_texture_offset = D3DXVECTOR2(0.0f, 0.0f);
	// �����l
	_texture_alpha	= 1.0f;
	// �����l�̕ω����x
	_a_speed	= 1.0f / exsist_time;
	// ���W
	_position	= position;
	// �p�x
	_rotation	= 0.0f;
	// �傫��
	_scaling	= scaling;
}

//=============================================================================
// �I��
void TextUnit::Finalize()
{
	
}

//=============================================================================
// �X�V
void TextUnit::Update()
{
	// �_��
	_texture_alpha += _a_speed;
	if( _texture_alpha < 0.0f || _texture_alpha > 1.0f )
	{
		_a_speed *= -1.0f;
	}

	ScreenUnit::Update();
}

//=============================================================================
// �X�V
void TextUnit::CollisionUpdate()
{
	
}

//=============================================================================
// �`��
void TextUnit::Draw()
{
	ScreenUnit::Draw();
}

