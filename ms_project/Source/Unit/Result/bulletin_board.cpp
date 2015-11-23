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
const D3DXVECTOR3	position	= D3DXVECTOR3( 480.0f , 240.0f , 0.0 );
const D3DXVECTOR3	scaling		= D3DXVECTOR3( 800.0f , 430.0f , 0.0f );

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

