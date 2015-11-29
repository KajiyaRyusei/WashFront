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
const D3DXVECTOR3	position	= D3DXVECTOR3( 480.0f , 790.0f , 0.0 );
const D3DXVECTOR3	scaling		= D3DXVECTOR3( 800.0f , 430.0f , 0.0f );
const float			dest_pos_Y	= 240.0f;
const int			startTime	= 60;

//*****************************************************************************
// static
bool BulletinUnit::_disp_flg	= false;
bool BulletinUnit::_update_flg	= false;
//=============================================================================
// 初期化
void BulletinUnit::Initialize()
{
	// テクスチャ
	CreateTexture(TEXT("Data/Texture/black.jpg"));
	// UV値
	_texture_uv		= D3DXVECTOR2(1.0f, 1.0f);
	// オフセット
	_texture_offset = D3DXVECTOR2(0.0f, 0.0f);
	// 透明値
	_texture_alpha	= 1.0f;
	// 角度
	_rotation	= 0.0f;
	// 大きさ
	_scaling	= scaling;
	// 座標
	_position	= position;
	//
	_timeCnt	= 0;
	//
	_disp_flg	= false;
	_update_flg = false;
}

//=============================================================================
// 終了
void BulletinUnit::Finalize()
{

}

//=============================================================================
// 更新
void BulletinUnit::Update()
{
	_timeCnt++;

	if( _timeCnt > startTime )
	{
		_update_flg = true;
		if( _position.y > dest_pos_Y )
		{
			_position.y -= 10;
		}
		else
		{
			_disp_flg = true;
		}
	}

	ScreenUnit::Update();
}

//=============================================================================
// 更新
void BulletinUnit::CollisionUpdate()
{

}

//=============================================================================
// 描画
void BulletinUnit::Draw()
{
	ScreenUnit::Draw();
}

