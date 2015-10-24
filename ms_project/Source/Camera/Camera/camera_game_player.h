//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �v���C���[�p�J����
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
class CameraGamePlayer : public Camera
{
public:

	CameraGamePlayer(Application* application) : Camera(application) { Initialize(); }
	virtual ~CameraGamePlayer(){}

	// ������
	virtual void Initialize() override;

	// �v���W�F�N�V�����ƃr���[�s��쐬
	virtual void CreateMatrix() override;

	// �v���C���[�̍��W���Z�b�g
	void SetPlayerPosition(D3DXVECTOR3 position){ _player_position = position; }

	// ���[�e�[�V�������擾
	D3DXVECTOR3& GetCameraRotation(){ return _rotation; }

private:

	
	void Chase();
	void Input();

	// �v���C���[�̍��W
	D3DXVECTOR3 _player_position;
	// ��]�֌W
	D3DXVECTOR3 _rotation;
	D3DXVECTOR3 _destnation_rotation_velocity;
	D3DXVECTOR3 _rotation_velocity;
};