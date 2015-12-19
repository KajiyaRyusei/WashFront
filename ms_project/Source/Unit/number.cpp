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
// 初期化
void NumberUnit::Initialize()
{
	// テクスチャ
	CreateTexture(TEXT("Data/Texture/number_color_yellow.png"));
	// UV値
	_texture_uv = D3DXVECTOR2(1.0f, 0.1f);
	// オフセット
	_texture_offset = D3DXVECTOR2(0.0f, 0.0f);
	// 透明値
	_texture_alpha = 1.0f;
	// 座標
	_position = position;
	// 角度
	_rotation = 0.0f;
	// 大きさ
	_scaling = scaling;
	// 値
	_value = 0;

	_grade = 0.0f;
}

//=============================================================================
// 終了
void NumberUnit::Finalize()
{

}

//=============================================================================
// 更新
void NumberUnit::Update()
{
	Reflection();
	ScreenUnit::Update();
}

//=============================================================================
// 更新
void NumberUnit::CollisionUpdate()
{

}

//=============================================================================
// 描画
void NumberUnit::Draw()
{
	ScreenUnit::Draw();
}

//=============================================================================
// 反映
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
// 数値セット
void NumberUnit::SetValue(int value)
{
	_value = value;
}