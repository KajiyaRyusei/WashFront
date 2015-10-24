//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �Q�[�����C���J����
// 
// Created by Ryusei Kajiya on 20151022
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
class CameraGameMain : public Camera
{
public:

	CameraGameMain(Application* application) : Camera(application){ Initialize(); }
	virtual ~CameraGameMain(){}

	// ������
	virtual void Initialize() override;

	// �v���W�F�N�V�����ƃr���[�s��쐬
	virtual void CreateMatrix() override;

};