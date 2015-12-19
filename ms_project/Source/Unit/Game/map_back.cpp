//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �}�b�v�w�i
// 
// Created by Chiharu Kamiyama on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "map_back.h"
#include "Windows/window.h"


//�萔

//=============================================================================
// ������
void MapBack::Initialize()
{
	//�e�l������
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
// �I��
void MapBack::Finalize()
{

}

//=============================================================================
// �X�V
void MapBack::Update()
{
	ScreenUnit::Update();

}

//=============================================================================
// �`��
void MapBack::Draw()
{
	ScreenUnit::Draw();
}