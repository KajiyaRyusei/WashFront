//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Result_BG
// 
// Created by Toshiki Mochizuki on 20151123
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit\Result\result_bg.h"

//*****************************************************************************
// const
const D3DXVECTOR3	position	= D3DXVECTOR3( 480.0f , 270.0f , 0.0 );
const D3DXVECTOR3	scaling		= D3DXVECTOR3( 960.0f , 540.0f , 0.0f );

//=============================================================================
// 初期化
void Result_BGUnit::Initialize()
{
	// テクスチャ
	CreateTexture(TEXT("Data/Texture/result_bg.png"));
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
void Result_BGUnit::Finalize()
{

}

//=============================================================================
// 更新
void Result_BGUnit::Update()
{
	ScreenUnit::Update();
}

//=============================================================================
// 更新
void Result_BGUnit::CollisionUpdate()
{

}

//=============================================================================
// 描画
void Result_BGUnit::Draw()
{
	ScreenUnit::Draw();
}

