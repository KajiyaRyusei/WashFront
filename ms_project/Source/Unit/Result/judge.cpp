//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// JudgeUnit
// 
// Created by Toshiki Mochizuki on 20151123
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit\Result/Judge.h"

//*****************************************************************************
// const
const D3DXVECTOR3	position	= D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
const D3DXVECTOR3	scaling		= D3DXVECTOR3( 300.0f , 80.0f , 0.0f );

//=============================================================================
// 初期化
void JudgeUnit::Initialize()
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
void JudgeUnit::Finalize()
{

}

//=============================================================================
// 更新
void JudgeUnit::Update()
{
	ScreenUnit::Update();
}

//=============================================================================
// 更新
void JudgeUnit::CollisionUpdate()
{

}

//=============================================================================
// 描画
void JudgeUnit::Draw()
{
	ScreenUnit::Draw();
}

