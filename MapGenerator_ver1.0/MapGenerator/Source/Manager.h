//=============================================================================
//
// �}�l�[�W���N���X [Manager.h]
// Author : KEITA OHUCHI
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include <Windows.h>


//-----------------------------------------------------------------------------
// �O���錾
//-----------------------------------------------------------------------------
// ���ʃN���X
class Renderer;
class Keyboard;
class Mouse;
class DebugProc;
class TextureFactory;
class ModelFactory;
class CameraManager;
class ObjectManager;
class ImportFileManager;
class RouteManager;


//-----------------------------------------------------------------------------
// �N���X��`
//-----------------------------------------------------------------------------
class Manager {
private:
	//=========================================================================
	// �R���X�g���N�^
	//=========================================================================
	Manager();
	
public:
	//=========================================================================
	// �f�X�g���N�^
	//=========================================================================
	~Manager();

	//=========================================================================
	// �C���X�^���X�̎擾
	//=========================================================================
	static Manager *GetInstance();
	//=========================================================================
	// �C���X�^���X�̔j��
	//=========================================================================
	static void Destory();


	//=========================================================================
	// ����������
	//=========================================================================
	HRESULT Init(HINSTANCE instance, HWND wnd, BOOL window);
	//=========================================================================
	// �X�V����
	//=========================================================================
	void Update();
	//=========================================================================
	// �`�揈��
	//=========================================================================
	void Draw();


	//=========================================================================
	// �ێ����Ă���C���X�^���X�̎擾
	//=========================================================================
	Renderer *GetRenderer() { return renderer_; };
	Keyboard *GetKeyboard() { return keyboard_; };
	Mouse *GetMouse() { return mouse_; };
	TextureFactory *GetTextureFactory() { return textureFactory_; };
	ModelFactory *GetModelFactory() { return modelFactory_; };
	CameraManager *GetCameraManager() { return cameraManager_; };
	ImportFileManager *GetImportFileManager() { return importFileManager_; }
	ObjectManager *GetObjectManager() { return objectManager_; }
	RouteManager *GetRouteManager() { return routeManager_; }


private:
	static Manager		*instance_;				// �}�l�[�W���C���X�^���X



	// ���ʃN���X
	Renderer			*renderer_;				// �����_���[
	Keyboard			*keyboard_;				// �L�[�{�[�h����
	Mouse				*mouse_;				// �}�E�X����
	DebugProc			*debugProc_;			// �f�o�b�O�v���V�[�W��
	// �}�l�[�W��
	CameraManager		*cameraManager_;		// �J�����}�l�[�W��
	ObjectManager		*objectManager_;		// �I�u�W�F�N�g�}�l�[�W��
	ImportFileManager	*importFileManager_;	// �t�@�C���̓ǂݍ��݃}�l�[�W��
	RouteManager		*routeManager_;			// ���[�g�Ǘ��}�l�[�W��
	// �t�@�N�g��
	TextureFactory		*textureFactory_;		// �e�N�X�`���t�@�N�g��
	ModelFactory		*modelFactory_;			// ���f���t�@�N�g��

};


#endif


// End of file