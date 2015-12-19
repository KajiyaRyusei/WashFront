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
#include "Input\input_manager.h"
#include "Sound\sound.h"

//*****************************************************************************
// const
const D3DXVECTOR3	scaling = D3DXVECTOR3(800.0f, 430.0f, 0.0f);
const float			dest_pos_Y[2] =
{
	240.0f,
	320.0f
};
const int			startTime = 60;
const float			countSpeed = 1.0f / 60.0f;

//*****************************************************************************
// static
bool	BulletinUnit::_disp_flg = false;
bool	BulletinUnit::_update_flg = false;
float	BulletinUnit::_time = 0.0f;

//=============================================================================
// ������
void BulletinUnit::Initialize()
{
	// �e�N�X�`��
	CreateTexture(TEXT("Data/Texture/result.png"));
	// UV�l
	_texture_uv = D3DXVECTOR2(1.0f, 1.0f);

	// �I�t�Z�b�g
	_texture_offset = D3DXVECTOR2(0.0f, 0.0f);
	// �����l
	_texture_alpha = 1.0f;
	// �p�x
	_rotation = 0.0f;
	// �傫��
	_scaling = scaling;
	// ���W
	_position = D3DXVECTOR3(0.0f, 0.f, 0.0f);
	//
	_timeCnt = 0;
	//
	_disp_flg = false;
	_update_flg = false;
	//
	_time = 0.0f;
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
	_timeCnt++;
	if( _application->GetInputManager()->CheckTrigger(INPUT_EVENT_Z) )
	{
		_timeCnt = startTime + 1;
		_time = 1.0f - countSpeed - 0.001f;
	}

	if( _timeCnt > startTime )
	{
		_update_flg = true;

		if( _time < 1.0f )
		{
			_time += countSpeed;
			if( _time >= 1.0f )
			{
				_time = 1.0f;
			}
			_position.y = Easing(_tempPos.y, dest_pos_Y[windowSizeID]);
		}
		else if( _disp_flg == false )
		{
			_disp_flg = true;
			_application->GetSound()->Play(SE_COUNT);
		}
	}

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

//=============================================================================
// 
float BulletinUnit::Easing(float min, float max)
{
	float ret;

	if( _time < 0.5f )
	{
		ret = (2 * _time) * (2 * _time) * 0.5f;
	}
	else
	{
		ret = -((2 * _time - 2) * (2 * _time - 2)) * 0.5f + 1.0f;
	}
	ret = (max - min) * ret + min;
	return ret;
}