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
}


//=============================================================================
// �I��
void Map::Finalize()
{

}

//=============================================================================
// �X�V
void Map::Update()
{

}

//=============================================================================
// �`��
void Map::Draw()
{
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

//=============================================================================
//�}�b�v�����ݒ�
void Map::SetMap(float max_map_distance, D3DXVECTOR3 init_player_position)
{
	for (int i = 0; i < 2; i++)
	{
		_map_character[i]->SetMapAllDistance(max_map_distance);
		_map_character[i]->InitMapCharacterPosition(init_player_position);
	}
}


//=============================================================================
//���X�g�Z�b�g
void Map::SetMapCharacterList(std::list<Unit*> *list)
{
	//�}�b�v�w�i�o�^
	_map_back = new MapBack(_application, _game_world);
	list->push_back(_map_back);

	//�}�b�v�L�����N�^�[�̍쐬
	for (int i = 0; i < 2; i++)
	{
		_map_character[i] = new MapCharacter(_application, _game_world);
		_map_character[i]->SetId(i);
		list->push_back(_map_character[i]);
	}
}