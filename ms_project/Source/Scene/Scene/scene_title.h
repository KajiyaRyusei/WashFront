//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �V�[���F�^�C�g��
// 
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �C���N���[�h
#include "scene.h"

//*****************************************************************************
// �O���錾
class World;

//*****************************************************************************
// �N���X�݌v
class SceneTitle : public Scene
{
public:

	// �R���X�g���N�^
	explicit SceneTitle(Application* application);

	// �f�X�g���N�^
	virtual ~SceneTitle(){ Finalize(); }

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
	
};

