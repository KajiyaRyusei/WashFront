//=============================================================================
//
// ���C������ [Main.h]
// Author : KEITA OHUCHI
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_


//-----------------------------------------------------------------------------
// �C���N���[�h
//-----------------------------------------------------------------------------
// Warning�΍�
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <windows.h>
#include "Renderer.h"

// ���������[�N���o
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define SCREEN_WIDTH (640)	// �E�C���h�E�̕�
#define SCREEN_HEIGHT (360)	// �E�C���h�E�̍���


//-----------------------------------------------------------------------------
// �񋓌^��`
//-----------------------------------------------------------------------------
enum MODE {
	MODE_NONE = (0),
	MODE_OBJECT,
	MODE_ROUTE,
	MODE_DIRT,
	MODE_MAX
};


//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
HWND GetWindowHandle();


//-----------------------------------------------------------------------------
// �C�����C���֐���`
//-----------------------------------------------------------------------------
// �p�x�̐��K��
static inline void NormalizeRotation(float &r) {
	if (r < -D3DX_PI) {
		r += D3DX_PI * 2;
	} else if (D3DX_PI < r) {
		r -= D3DX_PI * 2;
	}
};

// �|�C���^�̈��S�ȊJ������
template <class T>
static inline void SafeDelete(T*& p) {
	if (p) {
		delete p;
		p = nullptr;
	}
};
// �|�C���^�z��̈��S�ȊJ������
template <class T>
static inline void SafeDeleteArray(T*& p) {
	if (p) {
		delete[] p;
		p = nullptr;
	}
};
// �����[�X���̈��S�ȊJ������
template <class T>
static inline void SafeRelease(T*& p) {
	if (p) {
		p->Release();
		p = nullptr;
	}
};


// ���������[�N���o
#ifdef _DEBUG
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif


//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
//=============================================================================
// FPS�̎擾
//=============================================================================
float GetFps();

HWND GetObjectDialogHandle();
HWND GetRouteDialogHandle();
HWND GetDirtDialogHandle();
MODE GetMode();

#endif


// End of file