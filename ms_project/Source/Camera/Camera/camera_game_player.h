//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �v���C���[�p�J����
//
// Created by Ryusei Kajiya on 20151130
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "camera.h"
#include "Data/data_route.h"

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

	// ���_�̃��[�g��ݒ�
	void SetRoute(std::vector<data::Route>&& route){ _route = route; }

	// ���݂̃��[�g�̎擾
	const data::Route& GetCurrentRoute(){ return _current_route; }

private:

	void PassRootDecision();

	// �v���C���[�̍��W
	D3DXVECTOR3 _player_position;
	// �ړ��p�X
	std::vector<data::Route> _route;
	data::Route _current_route;
	fx32 _pass_frame;
	// ��]�֌W
	D3DXVECTOR3 _rotation;
	D3DXVECTOR3 _destnation_rotation_velocity;
	D3DXVECTOR3 _rotation_velocity;
};