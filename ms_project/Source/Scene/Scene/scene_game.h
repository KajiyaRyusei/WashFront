//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �V�[���F�Q�[��
// 
// Created by Ryusei Kajiya on 20151130
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �C���N���[�h
#include "scene.h"
#include "Data/data_dirt.h"

//*****************************************************************************
// �O���錾
class World;
class PlayerUnit;

//*****************************************************************************
// �N���X�݌v
class SceneGame : public Scene
{
public:

	// �R���X�g���N�^
	explicit SceneGame(Application* application);

	// �f�X�g���N�^
	virtual ~SceneGame(){ Finalize(); }

	// ������
	virtual void Initialize() override;

	// �I��
	virtual void Finalize() override;

	// �X�V
	virtual void Update() override;

	// �`��
	virtual void Draw() override;

private:
	World* _world;

	void MapGeneration();
	void ResourceGeneration();
	void RouteRead();
	std::vector<data::Dirt> DirtyRead();
};

