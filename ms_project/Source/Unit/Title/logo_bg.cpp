//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// LOGO_BG
// 
// Created by Toshiki Mochizuki on 20151122
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit\Title\logo_bg.h"

//*****************************************************************************
// const
const D3DXVECTOR3	position	= D3DXVECTOR3( 480.0f , 150.0f , 0.0 );
const D3DXVECTOR3	scaling		= D3DXVECTOR3( 500.0f , 250.0f , 0.0f );

//=============================================================================
// 初期化
void Logo_BGUnit::Initialize()
{
	// テクスチャ
	CreateTexture(TEXT("Data/Texture/white.jpg"));
	// UV値
	_texture_uv		= D3DXVECTOR2(1.0f, 1.0f);
	// オフセット
	_texture_offset = D3DXVECTOR2(0.0f, 0.0f);
	// 透明値
	_texture_alpha	= 1.0f;
	// 座標
	_position	= position;
	// 角度
	_rotation	= 0.0f;
	// 大きさ
	_scaling	= scaling;
}

//=============================================================================
// 終了
void Logo_BGUnit::Finalize()
{

}

//=============================================================================
// 更新
void Logo_BGUnit::Update()
{
	ScreenUnit::Update();
}

//=============================================================================
// 更新
void Logo_BGUnit::CollisionUpdate()
{

}

//=============================================================================
// 描画
void Logo_BGUnit::Draw()
{
	ScreenUnit::Draw();
}

