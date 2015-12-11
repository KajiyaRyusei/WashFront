//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// �J�����Ǘ�
// 
// Created by Ryusei Kajiya on 20151006
// 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �O���錾
class Camera;
class Application;

//*****************************************************************************
// ��
enum CAMERA_TYPE
{
	CAMERA_TYPE_GAME_MAIN = 0,
	CAMERA_TYPE_GAME_PLAYER_1P,
	CAMERA_TYPE_GAME_PLAYER_2P,
	CAMERA_TYPE_2D,
	CAMERA_TYPE_TITLE,
	CAMERA_TYPE_MAX
};

//*****************************************************************************
// �N���X�݌v
class CameraManager
{
public:

	// �R���X�g���N�^
	CameraManager(Application* application) : _application(application){ Initialize(); }

	// �f�X�g���N�^
	virtual ~CameraManager(){ Finalize(); }

	// ������
	void Initialize();

	// �I��
	void Finalize();

	// �X�V
	void Update();

	// �J�����̃|�C���^�擾
	Camera* GetCamera(CAMERA_TYPE type){ return _cameras[type]; }

	// ���݂̃J�����̎擾
	Camera* GetCurrentCamera(){ return _current_camera; }
	// �J�����̃Z�b�g
	void SetCurrentCamera(Camera* camera){ _current_camera = camera; }

private:

	Camera* _cameras[CAMERA_TYPE_MAX];
	Camera* _current_camera;
	Application* _application;
};