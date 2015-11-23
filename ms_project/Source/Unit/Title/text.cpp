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
// 初期化
void TextUnit::Initialize()
{
	// テクスチャ
	CreateTexture(TEXT("Data/Texture/moji000.png"));
	// UV値
	_texture_uv		= D3DXVECTOR2(1.0f, 1.0f);
	// オフセット
	_texture_offset = D3DXVECTOR2(0.0f, 0.0f);
	// 透明値
	_texture_alpha	= 1.0f;
	// 透明値の変化速度
	_a_speed	= 1.0f / exsist_time;
	// 座標
	_position	= position;
	// 角度
	_rotation	= 0.0f;
	// 大きさ
	_scaling	= scaling;
}

//=============================================================================
// 終了
void TextUnit::Finalize()
{
	
}

//=============================================================================
// 更新
void TextUnit::Update()
{
	// 点滅
	_texture_alpha += _a_speed;
	if( _texture_alpha < 0.0f || _texture_alpha > 1.0f )
	{
		_a_speed *= -1.0f;
	}

	ScreenUnit::Update();
}

//=============================================================================
// 更新
void TextUnit::CollisionUpdate()
{
	
}

//=============================================================================
// 描画
void TextUnit::Draw()
{
	ScreenUnit::Draw();
}

