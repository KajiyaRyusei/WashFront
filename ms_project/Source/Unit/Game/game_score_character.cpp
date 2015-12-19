//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �X�R�A����
// 
// Created by Chiharu Kamiyama on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "game_score_character.h"
#include "Windows/window.h"


//�萔
static const D3DXVECTOR3 scaling(80.0f, 80.0f, 1.0f);


//=============================================================================
// ������
void GameScoreCharacter::Initialize()
{
	//�e�l������
	CreateTexture(TEXT("Data/Texture/game_score_character.png"));
	_texture_uv = D3DXVECTOR2(1.0f, 1.0f);
	_texture_offset = D3DXVECTOR2(0.0f, 0.0f);
	_texture_alpha = 1.0f;

	_scaling = scaling;
	_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_rotation = 0.0f;
}

//=============================================================================
// �I��
void GameScoreCharacter::Finalize()
{

}

//=============================================================================
// �X�V
void GameScoreCharacter::Update()
{
	ScreenUnit::Update();

}

//=============================================================================
// �`��
void GameScoreCharacter::Draw()
{
	ScreenUnit::Draw();
}