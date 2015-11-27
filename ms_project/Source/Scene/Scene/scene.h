//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �V�[��
// 
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "System/application.h"

//*****************************************************************************
// �O���錾
//��ŏ����Ă�������
class Ui;

//*****************************************************************************
// �N���X�݌v
class Scene
{
public:
	Scene(Application* application) :
		_application{ application }
	{}

	virtual ~Scene(){}

	// ������
	virtual void Initialize() = 0;

	// �I��
	virtual void Finalize() = 0;

	// �X�V
	virtual void Update() = 0;

	// �`��
	virtual void Draw() = 0;

	//UI�擾
	//��ŏ����Ă�������
	Ui *GetSceneUi(void)
	{ return _ui; }

protected:

	// �f�[�^
	Application *_application;

	//UI
	Ui *_ui;

};