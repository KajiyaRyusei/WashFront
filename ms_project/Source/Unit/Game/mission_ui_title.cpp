//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ミッションUIタイトル
// 
// Created by Chiharu Kamiyama on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "mission_ui_title.h"
#include "Windows/window.h"


//定数
static const D3DXVECTOR3 scaling(100.0f, 40.0f, 1.0f);


//=============================================================================
// 初期化
void MissionUiTitle::Initialize()
{
	//各値初期化
	CreateTexture(TEXT("Data/Texture/mission_ui_title.png"));
	_texture_uv = D3DXVECTOR2(1.0f, 1.0f);
	_texture_offset = D3DXVECTOR2(0.0f, 0.0f);
	_texture_alpha = 1.0f;

	_scaling = scaling;
	_position = D3DXVECTOR3(_scaling.x / 2 + 15.0f,
		_application->GetWindow()->GetSizeWindowHeight() - _scaling.y / 2 - 20.0f,
		0.0f);
	_rotation = 0.0f;
}

//=============================================================================
// 終了
void MissionUiTitle::Finalize()
{

}

//=============================================================================
// 更新
void MissionUiTitle::Update()
{
	ScreenUnit::Update();

}

//=============================================================================
// 描画
void MissionUiTitle::Draw()
{
	ScreenUnit::Draw();

}