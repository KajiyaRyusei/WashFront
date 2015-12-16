//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// LOGO_BG
// 
// Created by Toshiki Mochizuki on 20151122
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit\Title\logo.h"

//*****************************************************************************
// const
const D3DXVECTOR3	position = D3DXVECTOR3(480.0f, 150.0f, 0.0);
const D3DXVECTOR3	scaling = D3DXVECTOR3(400.0f, 200.0f, 0.0f);
const D3DXVECTOR3	scaling_max = D3DXVECTOR3(420.0f, 220.0f, 0.0f);
const int			scale_time = 60;
const int			exsist_time = 90;

//=============================================================================
// 初期化
void LogoUnit::Initialize()
{
	// テクスチャ
	CreateTexture(TEXT("Data/Texture/black.jpg"));
	// UV値
	_texture_uv = D3DXVECTOR2(1.0f, 1.0f);
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
	// 拡縮
	_scale_speed = (scaling_max - scaling) / (float)scale_time;
}

//=============================================================================
// 終了
void LogoUnit::Finalize()
{

}

//=============================================================================
// 更新
void LogoUnit::Update()
{
	static int cnt = 0;
	cnt++;
	_scaling += _scale_speed;
	if( cnt % scale_time == 0 )
	{
		_scale_speed *= -1;
	}


	ScreenUnit::Update();
}

//=============================================================================
// 更新
void LogoUnit::CollisionUpdate()
{

}

//=============================================================================
// 描画
void LogoUnit::Draw()
{
	ScreenUnit::Draw();
}

