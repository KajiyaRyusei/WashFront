//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �V�[���F���U���g
// 
// Created by Ryusei Kajiya on 20151123
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
class ScoreUnit;
class JudgeUnit;


//*****************************************************************************
// �N���X�݌v
class SceneResult : public Scene
{
public:

	// �R���X�g���N�^
	explicit SceneResult(Application* application);

	// �f�X�g���N�^
	virtual ~SceneResult(){ Finalize(); }

	// ������
	virtual void Initialize() override;

	// �I��
	virtual void Finalize() override;

	// �X�V
	virtual void Update() override;

	// �`��
	virtual void Draw() override;

private:
	World*		_world;
	ScoreUnit*	_pScore[ 8 ];
	JudgeUnit*	_pJudge[ 2 ];
	float		_grade;

};

