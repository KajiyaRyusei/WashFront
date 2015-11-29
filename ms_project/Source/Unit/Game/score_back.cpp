//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// スコア背景
// 
// Created by Chiharu Kamiyama on 20151127
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "score_back.h"
#include "Windows/window.h"

//定数
D3DXVECTOR2 kNumberSize = D3DXVECTOR2(50.0f, 100.0f);
int kNumberNum = 5;
float kScoreBackMarge = 20.0f;
float kScoreNumberMarge = 10.0f;

//=============================================================================
// 初期化
void ScoreBack::Initialize()
{
	//各値初期化
	CreateTexture(TEXT("Data/Texture/field001.jpg"));
	_texture_uv = D3DXVECTOR2(0.2f, 1.0f);
	_texture_offset = D3DXVECTOR2(0.0f, 1.0f);
	_texture_alpha = 1.0f;

	float scaling_x = (kNumberSize.x + kScoreNumberMarge )* kNumberNum + kScoreBackMarge * 2;


	_position = D3DXVECTOR3(_application->GetWindow()->GetSizeWindowWidth() / 2 - kNumberSize.x * kNumberNum,
							 30.0f, 0.0f);

	_rotation = 0.0f;
	_scaling = D3DXVECTOR3( scaling_x, kNumberSize.y + kScoreBackMarge, 1.0f);
}

//=============================================================================
// 終了
void ScoreBack::Finalize()
{

}

//=============================================================================
// 更新
void ScoreBack::Update()
{	
	ScreenUnit::Update();

}

//=============================================================================
// 描画
void ScoreBack::Draw()
{
	ScreenUnit::Draw();

}