//=============================================================================
//
// �}�E�X�̓��͏��� [Mouse.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "Mouse.h"


//=============================================================================
// �R���X�g���N�^
//=============================================================================
Mouse::Mouse()
{
	memset(&pressMouse_, 0, sizeof(DIMOUSESTATE));
	memset(&triggerMouse_, 0, sizeof(DIMOUSESTATE));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Mouse::~Mouse()
{
}

//=============================================================================
// ���͏��̏�����
//=============================================================================
HRESULT Mouse::Init(HINSTANCE instance, HWND wnd)
{
	HRESULT hr;

	// �e�N���X�̏���������
	Input::Init(instance, wnd);

	if (!input_) {
		MessageBox(nullptr,
			"DirectInput�I�u�W�F�N�g���쐬�ł��܂���ł���",
			"�}�E�X�̏�����", MB_OK);
		
		return S_FALSE;
	}

	// �f�o�C�X�I�u�W�F�N�g���쐬
	hr = input_->CreateDevice(GUID_SysMouse, &device_, nullptr);
	if (FAILED(hr)) {
		MessageBox(nullptr,
			"�f�o�C�X�I�u�W�F�N�g���쐬�ł��܂���ł���",
			"�}�E�X�̏�����", MB_OK);
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr = device_->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr)) {
		MessageBox(nullptr,
			"�f�[�^�t�H�[�}�b�g���ݒ�ł��܂���ł���",
			"�}�E�X�̏�����", MB_OK);
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = device_->SetCooperativeLevel(wnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr)) {
		MessageBox(nullptr,
			"�������[�h���ݒ�ł��܂���ł���",
			"�}�E�X�̏�����", MB_OK);
	}


/*
	// �}�E�X�n���h���̏�����
	mouse__device_handle = CreateEvent(nullptr, FALSE, FALSE, nullptr);
	if (mouse__device_handle == nullptr) {
		return FALSE;
	}

	// �}�E�X�f�o�C�X�Ƃ̊֘A�t��
	hr = mouse__device->SetEventNotification(mouse__device_handle);
	if (FAILED(hr)) {
		return FALSE;
	}

	// �v���p�e�B�̏�����
	DIPROPDWORD dipdw;
	// the header
	dipdw.diph.dwSize	   = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj		= 0;
	dipdw.diph.dwHow		= DIPH_DEVICE;
	// the data
	dipdw.dwData			= 16;

	// �v���p�e�B�̐ݒ�
	hr = mouse__device->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (FAILED(hr)) {
		return FALSE;
	}
*/


	// �}�E�X�ւ̃A�N�Z�X�����l��(���͐���J�n)
	device_->Acquire();


	return S_OK;
}

//=============================================================================
// ���͏��̍X�V����
//=============================================================================
void Mouse::Update()
{
	DIMOUSESTATE mouse_state;
	if (SUCCEEDED(device_->GetDeviceState(sizeof(mouse_state), &mouse_state))) {
		for (int count = 0; count < BUTTON_MAX; ++count) {
			triggerMouse_.rgbButtons[count] =
				~(pressMouse_.rgbButtons[count] & mouse_state.rgbButtons[count]) & mouse_state.rgbButtons[count];  // �g���K�[����
		}
		pressMouse_ = mouse_state;  // ���X�V
	} else {
		// �L�[�{�[�h�̃A�N�Z�X�����Ď擾
		device_->Acquire();
	}
}

//=============================================================================
// �}�E�X�̏�Ԃ̎擾
//=============================================================================
DIMOUSESTATE Mouse::GetPressMouse()
{
	return pressMouse_;
}

//=============================================================================
// �g���K�[���̎擾
//=============================================================================
DIMOUSESTATE Mouse::GetTriggerMouse()
{
	return triggerMouse_;
}

// End of file