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
#include "Unit\Result\score.h"

//*****************************************************************************
// const
const D3DXVECTOR3	position	= D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
const D3DXVECTOR3	scaling		= D3DXVECTOR3( 150.0f , 120.0f , 0.0f );


//*****************************************************************************
// static

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

	_visible	= false;

	_timeCnt	= 0;
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
	if( ScoreUnit::GetFlg() )
	{
		
		if( _timeCnt == disp_time )
		{

			_visible = true;
		}
		_timeCnt++;
	}
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

