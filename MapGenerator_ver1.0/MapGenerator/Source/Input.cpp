//=============================================================================
//
// ���͏��� [Input.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "Input.h"


//=============================================================================
// �R���X�g���N�^
//=============================================================================
Input::Input()
{
	input_ = nullptr;
	device_ = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Input::~Input()
{

	// DirectInput�I�u�W�F�N�g�̉��
	SafeRelease(input_);
	// �f�o�C�X�̉��
	SafeRelease(device_);

}

//=============================================================================
// ���͏��̏�����
//=============================================================================
HRESULT Input::Init(HINSTANCE instance, HWND wnd)
{
	HRESULT hr;

	// DirectInput�I�u�W�F�N�g�̍쐬
	if (input_ == nullptr) {
		hr = DirectInput8Create(instance,
								DIRECTINPUT_VERSION,
								IID_IDirectInput8,
								(void **)&input_, nullptr);
		if (FAILED(hr)) {
			MessageBox(nullptr, "DirectInput�I�u�W�F�N�g���쐬�ł��܂���ł���",
					   "�C���v�b�g�̏�����", MB_OK);
			return hr;
		}
	}


	return S_OK;
}


// End of file