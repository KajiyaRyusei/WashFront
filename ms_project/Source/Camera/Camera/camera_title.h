//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �^�C�g���J����
// 
// Created by Ryusei Kajiya on 20151201
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "camera.h"

//*****************************************************************************
// �N���X�݌v
class CameraTitle : public Camera
{
public:

	CameraTitle(Application* application) : Camera(application){ Initialize(); }
	virtual ~CameraTitle(){}

	// ������
	virtual void Initialize() override;

	// �v���W�F�N�V�����ƃr���[�s��쐬
	virtual void CreateMatrix() override;

};