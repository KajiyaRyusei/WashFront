//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �}�b�v�L�����N�^�[
// 
// Created by Chiharu Kamiyama on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit/Game/map_character.h"
#include "Unit/Game/map.h"
#include "World/collision_grid.h"
#include "Unit/ui.h"
#include "Windows/window.h"


//�萔
static const int kMaxPass = 4;

//=============================================================================
// ������
void MapCharacter::Initialize()
{
	//�e�l������
	CreateTexture(TEXT("Data/Texture/mapPoint.png"));
	_texture_uv = D3DXVECTOR2(1.0f, 1.0f);
	_texture_offset = D3DXVECTOR2(0.0f, 0.0f);
	_texture_alpha = 1.0f;

	_position = D3DXVECTOR3((float)_application->GetWindow()->GetSizeWindowWidth() / 2,
							(float)_application->GetWindow()->GetSizeWindowHeight(),
							0.0f);
	_rotation = 0.0f;
	_scaling = D3DXVECTOR3( 50.0f, 50.0f, 1.0f );

	//���ړ������Z�o
	D3DXVECTOR3 pass[kMaxPass];
	pass[0] = _game_world->GetCollisionGrid()->CellCenterPoint(1, 1);
	pass[1] = _game_world->GetCollisionGrid()->CellCenterPoint(3, 1);
	pass[2] = _game_world->GetCollisionGrid()->CellCenterPoint(3, 3);
	pass[3] = _game_world->GetCollisionGrid()->CellCenterPoint(1, 3);

	D3DXVECTOR3 vec;
	
	float distance = 0.0f;

	vec = pass[1] - pass[0];

	distance += abs(vec.x);
	distance += abs(vec.y);
	distance += abs(vec.z);

	vec = pass[2] - pass[1];

	distance += abs(vec.x);
	distance += abs(vec.y);
	distance += abs(vec.z);

	vec = pass[3] - pass[2];

	distance += abs(vec.x);
	distance += abs(vec.y);
	distance += abs(vec.z);

	vec = pass[0] - pass[3];

	distance += abs(vec.x);
	distance += abs(vec.y);
	distance += abs(vec.z);

	//�������ۑ�
	_map_distance = distance;

	_character_distance = 0;
	_map_character_position = pass[0];
	_map_character_old_position = _map_character_position;
}

//=============================================================================
// �I��
void MapCharacter::Finalize()
{
}

//=============================================================================
// �X�V
void MapCharacter::Update()
{
	D3DXVECTOR3 vec;
	vec = _map_character_position - _map_character_old_position;

	//�ړ��ʌv�Z
	float distance = 0.0f;
	distance = abs(vec.x);
	distance += abs(vec.y);
	distance += abs(vec.z);

	//�����ړ�
	_character_distance += distance;
	float per = _character_distance / _map_distance;

	//�E�B���h�E�̍���
	float window_height = (float)_application->GetWindow()->GetSizeWindowHeight();

	//�ꏊ�Z�o
	float pos_y = window_height - (window_height * per);


	//�S���B�ꂽ�牺���s�[�g�̂�ƈꏏ�ɁB
	if ((pos_y + _scaling.y / 2) <= 0.0f)
	{
		if (_id == 0)
		{
			_character_distance -= _map_distance;
			pos_y = window_height - _scaling.y / 2;
		}
	}


	//��[�܂ōs�����烊�s�[�g�\��
	if ((pos_y - _scaling.y / 2) <= 0.0f)
	{
		if (_id == 1)
		{
			//�͂ݏo�����������v�Z
			float difference = 0.0f;
			difference = pos_y - _scaling.y / 2;

			//�͂ݏo������������o���B
			pos_y = difference + window_height + _scaling.y / 2;

			if (pos_y <= window_height)
			{
				_character_distance = 0.0f;
			}
		}
	}
	

	
	//�ꏊ�X�V
	SetPosition(D3DXVECTOR3(_position.x, pos_y, _position.z));

	//�\���X�V
	ScreenUnit::Update();
}

//=============================================================================
// �`��
void MapCharacter::Draw()
{
	ScreenUnit::Draw();

}

//=============================================================================
// ���W�ݒ�
void MapCharacter::SetMapCharacterPosition(D3DXVECTOR3 position)
{
	_map_character_old_position = _map_character_position;
	_map_character_position = position;
}