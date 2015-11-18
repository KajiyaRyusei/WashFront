//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// マップ
// 
// Created by Chiharu Kamiyama on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "map.h"

//定数
static const D3DXVECTOR3 position = D3DXVECTOR3(300.0f, 300.0f, 0.0f);
static const D3DXVECTOR3 scaling = D3DXVECTOR3(300.0f, 300.0f, 1.0f);

//=============================================================================
// 初期化
void Map::Initialize()
{
	CreateTexture(TEXT("Data/Texture/bild_effect.png"));
	_texture_uv = D3DXVECTOR2(0.2f, 1.0f);
	_texture_offset = D3DXVECTOR2(0.0f, 1.0f);
	_texture_alpha = 1.0f;

	_position = position;
	_rotation = 0.0f;
	_scaling = scaling;
}

//=============================================================================
// 終了
void Map::Finalize()
{

}

//=============================================================================
// 更新
void Map::Update()
{

	_texture_offset.x += 0.005f;

	if (_texture_offset.x == 1.2f)
	{
		_texture_offset.x = 0.2f;
	}
	
	ScreenUnit::Update();

}

//=============================================================================
// 描画
void Map::Draw()
{
	ScreenUnit::Draw();

}