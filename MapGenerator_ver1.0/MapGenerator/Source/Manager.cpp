//=============================================================================
//
// �}�l�[�W���N���X [Manager.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include <time.h>
#include "Main.h"
#include "Manager.h"
// �V�[��
#include "ObjectManager.h"
// ���ʃN���X
#include "Renderer.h"
#include "Scene.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Debug.h"
#include "TextureFactory.h"
#include "ModelFactory.h"
#include "CameraManager.h"
#include "ObjectManager.h"
#include "ImportFileManager.h"
#include "RouteManager.h"
#include "DirtManager.h"


//-----------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------
Manager *Manager::instance_ = nullptr;


//=========================================================================
// �R���X�g���N�^
//=========================================================================
Manager::Manager()
{

	// �N���A
	renderer_ = nullptr;
	keyboard_ = nullptr;
	mouse_ = nullptr;
	debugProc_ = nullptr;
	textureFactory_ = nullptr;
	modelFactory_ = nullptr;
	cameraManager_ = nullptr;
	objectManager_ = nullptr;
	importFileManager_ = nullptr;
	routeManager_ = nullptr;
	dirtManager_ = nullptr;

}

//=========================================================================
// �f�X�g���N�^
//=========================================================================
Manager::~Manager()
{

	// �����_���[�C���X�^���X�̉��
	SafeDelete(renderer_);
	// �L�[�{�[�h�C���X�^���X�̉��
	SafeDelete(keyboard_);
	// �}�E�X�C���X�^���X�̉��
	SafeDelete(mouse_);


	// �e�N�X�`���t�@�N�g���̉��
	SafeDelete(textureFactory_);
	// ���f���t�@�N�g���̉��
	SafeDelete(modelFactory_);


	// �J�����}�l�[�W���̉��
	SafeDelete(cameraManager_);

	// �t�@�C���ǂݍ��݃}�l�[�W���̉��
	SafeDelete(importFileManager_);

	// ���[�g�}�l�[�W���̉��
	SafeDelete(routeManager_);

	// ����}�l�[�W���̉��
	SafeDelete(dirtManager_);

	// �I�u�W�F�N�g�}�l�[�W���̉��
	SafeDelete(objectManager_);

#ifdef _DEBUG
	// �f�o�b�O�v���V�[�W���̉��
	SafeDelete(debugProc_);
#endif

}

//=========================================================================
// �C���X�^���X�̎擾
//=========================================================================
Manager *Manager::GetInstance()
{
	if (!instance_) {
		instance_ = new Manager();
	}

	return instance_;
}

//=========================================================================
// �C���X�^���X�̔j��
//=========================================================================
void Manager::Destory()
{
	SafeDelete(instance_);
}


//=========================================================================
// ����������
//=========================================================================
HRESULT Manager::Init(HINSTANCE instance, HWND wnd, BOOL window)
{
	// �����̏�����
	srand((unsigned int)time(nullptr));

	// �����_���[�̐���
	renderer_ = new Renderer();
	renderer_->Init(instance, wnd, window);

	// �e�N�X�`���t�@�N�g���̐���
	textureFactory_ = new TextureFactory();
	// ���f���t�@�N�g���̐���
	modelFactory_ = new ModelFactory();


	// �L�[�{�[�h�̐���
	keyboard_ = new Keyboard();
	keyboard_->Init(instance, wnd);

	// �}�E�X�̐���
	mouse_ = new Mouse();
	mouse_->Init(instance, wnd);



	// �J�����}�l�[�W���̐���
	cameraManager_ = new CameraManager();
	cameraManager_->Init();
	cameraManager_->ChangeEditorCamera();

	// �t�@�C���ǂݍ��݃}�l�[�W���̐���
	importFileManager_ = new ImportFileManager();
	importFileManager_->Init();

	// ���[�g�}�l�[�W���̐���
	routeManager_ = new RouteManager();
	routeManager_->Init();

	// ����}�l�[�W���̐���
	dirtManager_ = new DirtManager();
	dirtManager_->Init();

	// �I�u�W�F�N�g�}�l�[�W���̐���
	objectManager_ = new ObjectManager();
	objectManager_->Init();


#ifdef _DEBUG
	debugProc_ = new DebugProc();
	debugProc_->Init();
#endif


	return S_OK;
}

//=========================================================================
// �X�V����
//=========================================================================
void Manager::Update()
{

#ifdef _DEBUG
	debugProc_->Update();
	float fps = GetFps();
	DebugProc::Printf("[FPS : %f]\n", fps);
#endif

	// �L�[�{�[�h�C���X�^���X�̍X�V
	keyboard_->Update();
	// �}�E�X�̍X�V
	mouse_->Update();



	// �X�V����
	{
		// �����_���[�C���X�^���X�̍X�V
		renderer_->Update();

		// �J�����̍X�V
		cameraManager_->Update();

		// �V�[���̍X�V
		objectManager_->Update();

		routeManager_->Update();
	}

}

//=========================================================================
// �`�揈��
//=========================================================================
void Manager::Draw()
{
	
	// �`��J�n
	if (renderer_->BeginDraw()) {

		// �J�����̐ݒ�
		cameraManager_->SetCamera();

		// �V�[���C���X�^���X�̕`�揈��
		Scene::DrawAll();

		// �V�[���̕`��
		objectManager_->Draw();

		// ���[�g�̕`��
		routeManager_->Draw();

		// ����̕`��
		dirtManager_->Draw();

#ifdef _DEBUG
		// �f�o�b�O�\��
		DebugProc::Draw();
#endif


		// �`��I��
		renderer_->EndDraw();
	}

}


// End of file