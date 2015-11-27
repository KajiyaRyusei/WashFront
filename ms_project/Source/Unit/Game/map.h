//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// AIM
// 
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "Unit/unit.h"

//*****************************************************************************
// �O���錾
class MapBack;
class MapCharacter;

static const int kPlayerNum = 2;

//*****************************************************************************
// �N���X�݌v
class Map : public Unit
{
public:

	Map(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~Map(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;

	//�}�b�v�L�����N�^�[�ʒu�ݒ�
	void SetMapCharacterPosition(D3DXVECTOR3 position);
	
private:
	MapBack *_map_back;
	MapCharacter *_map_character[2];
};