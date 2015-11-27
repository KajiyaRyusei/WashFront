//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// マップ背景
// 
// Created by Chiharu Kamiyama on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "map_back.h"

//定数
static const D3DXVECTOR3 position = D3DXVECTOR3(960 / 2, 540 / 2, 0.0f);
static const D3DXVECTOR3 scaling = D3DXVECTOR3(50.0f, 720.0f, 1.0f);

//=============================================================================
// 初期化
void MapBack::Initialize()
{
	//各値初期化
	CreateTexture(TEXT("Data/Texture/field001.jpg"));
	_texture_uv = D3DXVECTOR2(0.2f, 1.0f);
	_texture_offset = D3DXVECTOR2(0.0f, 1.0f);
	_texture_alpha = 1.0f;

	_position = position;
	_rotation = 0.0f;
	_scaling = scaling;
}

//=============================================================================
// 終了
void MapBack::Finalize()
{

}

//=============================================================================
// 更新
void MapBack::Update()
{	
	ScreenUnit::Update();

}

//=============================================================================
// 描画
void MapBack::Draw()
{
	ScreenUnit::Draw();

}