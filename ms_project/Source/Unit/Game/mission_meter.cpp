//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ミッションメーター
// 
// Created by Chiharu Kamiyama on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "mission_meter.h"
#include "Windows/window.h"


//定数
static const D3DXVECTOR3 scaling(480.0f, 30.0f, 1.0f);


//=============================================================================
// 初期化
void MissionMeter::Initialize()
{
	//各値初期化
	CreateTexture(TEXT("Data/Texture/mission_meter.png"));
	_texture_uv = D3DXVECTOR2(1.0f, 1.0f);
	_texture_offset = D3DXVECTOR2(0.0f, 0.0f);
	_texture_alpha = 1.0f;

	_scaling = scaling;
	_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_rotation = 0.0f;
}

//=============================================================================
// 終了
void MissionMeter::Finalize()
{

}

//=============================================================================
// 更新
void MissionMeter::Update()
{
	ScreenUnit::Update();

}

//=============================================================================
// 描画
void MissionMeter::Draw()
{
	ScreenUnit::Draw();

}