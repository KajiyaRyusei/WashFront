//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// スコア文字
// 
// Created by Chiharu Kamiyama on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "game_score_character.h"
#include "Windows/window.h"


//定数
static const D3DXVECTOR3 scaling(80.0f, 80.0f, 1.0f);


//=============================================================================
// 初期化
void GameScoreCharacter::Initialize()
{
	//各値初期化
	CreateTexture(TEXT("Data/Texture/game_score_character.png"));
	_texture_uv = D3DXVECTOR2(1.0f, 1.0f);
	_texture_offset = D3DXVECTOR2(0.0f, 0.0f);
	_texture_alpha = 1.0f;

	_scaling = scaling;
	_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_rotation = 0.0f;
}

//=============================================================================
// 終了
void GameScoreCharacter::Finalize()
{

}

//=============================================================================
// 更新
void GameScoreCharacter::Update()
{
	ScreenUnit::Update();

}

//=============================================================================
// 描画
void GameScoreCharacter::Draw()
{
	ScreenUnit::Draw();
}