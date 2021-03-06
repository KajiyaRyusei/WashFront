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
#include "Unit\Result\bulletin_board.h"

//*****************************************************************************
// const
const D3DXVECTOR3	position	= D3DXVECTOR3( 0.0f , 0.0f , 0.0 );
const D3DXVECTOR3	scaling		= D3DXVECTOR3( 350.0f , 400.0f , 0.0f );
const float			dest_pos_Y	= 240.0f;

//=============================================================================
// 初期化
void Score_BoardUnit::Initialize()
{
	// テクスチャ
	CreateTexture(TEXT("Data/Texture/white.jpg"));
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
}

//=============================================================================
// 終了
void Score_BoardUnit::Finalize()
{

}

//=============================================================================
// 更新
void Score_BoardUnit::Update()
{
	if( BulletinUnit::GetUpdateFlg() )
	{
		if( _position.y > dest_pos_Y )
		{
			_position.y -= 10;
		}
	}
	ScreenUnit::Update();
}

//=============================================================================
// 更新
void Score_BoardUnit::CollisionUpdate()
{

}

//=============================================================================
// 描画
void Score_BoardUnit::Draw()
{
	ScreenUnit::Draw();
}

