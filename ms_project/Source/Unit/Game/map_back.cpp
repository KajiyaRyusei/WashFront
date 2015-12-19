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
#include "Windows/window.h"


//定数

//=============================================================================
// 初期化
void MapBack::Initialize()
{
	//各値初期化
	CreateTexture(TEXT("Data/Texture/map_back.png"));
	_texture_uv = D3DXVECTOR2(1.0f, 1.0f);
	_texture_offset = D3DXVECTOR2(0.0f, 0.0f);
	_texture_alpha = 1.0f;

	_position = D3DXVECTOR3((float)_application->GetWindow()->GetSizeWindowWidth() / 2,
		(float)_application->GetWindow()->GetSizeWindowHeight() / 2, 0.0f);
	_rotation = 0.0f;
	_scaling = D3DXVECTOR3((float)_application->GetWindow()->GetSizeWindowWidth(), 50.0f, 1.0f);
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