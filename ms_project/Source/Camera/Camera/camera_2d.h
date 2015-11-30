//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 2D�J����
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
class Camera2D : public Camera
{
public:

	explicit Camera2D(Application* application) : Camera(application){ Initialize(); }
	virtual ~Camera2D(){}

	// ������
	virtual void Initialize() override;

	// �v���W�F�N�V�����ƃr���[�s��쐬
	virtual void CreateMatrix() override;

};