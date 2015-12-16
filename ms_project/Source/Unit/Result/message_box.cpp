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
#include "Unit\Result\bulletin_board.h"

//*****************************************************************************
// const
const D3DXVECTOR3	scaling = D3DXVECTOR3(80.0f, 20.0f, 0.0f);
const float			dest_pos_Y[2] =
{
	550.0f,
	980.0f
};

//=============================================================================
// ������
void Message_BoxUnit::Initialize()
{
	// �e�N�X�`��
	CreateTexture(TEXT("Data/Texture/black.jpg"));
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
	// ���W( �K���O�ŃZ�b�g���邱�� )
	_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	if( BulletinUnit::GetUpdateFlg() )
	{
		if( _pos.y - dest_pos_Y[windowSizeID] < _position.y )
		{
			_position.y = BulletinUnit::Easing(_pos.y, (_pos.y - dest_pos_Y[windowSizeID]));
		}
	}
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

