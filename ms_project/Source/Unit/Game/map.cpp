//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �}�b�v
// 
// Created by Chiharu Kamiyama on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "map.h"
#include "Unit/Game/map_back.h"
#include "Unit/Game/map_character.h"


//=============================================================================
// ������
void Map::Initialize()
{
	//�}�b�v�w�i�̍쐬
	_map_back = new MapBack(_application, _game_world);

	//�}�b�v�L�����N�^�[�̍쐬
	for (int i = 0; i < 2; i++)
	{
		_map_character[i] = new MapCharacter(_application, _game_world);
		_map_character[i]->SetId(i);
	}
}


//=============================================================================
// �I��
void Map::Finalize()
{

	SafeDelete(_map_back);
	for (int i = 0; i < 2; i++)
	{
		SafeDelete(_map_character[i]);

	}
}

//=============================================================================
// �X�V
void Map::Update()
{	

	_map_back->Update();
	
	for (int i = 0; i < 2; i++)
	{
		_map_character[i]->Update();
	}

}

//=============================================================================
// �`��
void Map::Draw()
{

	_map_back->Draw();
	for (int i = 0; i < 2; i++)
	{
		_map_character[i]->Draw();
	}
}

//=============================================================================
// �����蔻��
void Map::CollisionUpdate()
{
}

//=============================================================================
//�}�b�v�L�����N�^�[�ʒu�ݒ�
void Map::SetMapCharacterPosition(D3DXVECTOR3 position)
{
	for (int i = 0; i < 2; i++)
	{
		_map_character[i]->SetMapCharacterPosition(position);
	}
}