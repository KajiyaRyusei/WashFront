//=============================================================================
//
// �L�[�{�[�h���͏��� [Keyboard.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================
#include "Main.h"
#include "Keyboard.h"


//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define REPEAT_FRAME (20)
#define KEY_MASK (0x0080)


//=============================================================================
// �R���X�g���N�^
//=============================================================================
Keyboard::Keyboard()
{
	// �����o�ϐ�������
	memset(pressKey_, 0, sizeof(pressKey_));
	memset(triggerKey_, 0, sizeof(triggerKey_));
	memset(releaseKey_, 0, sizeof(releaseKey_));
	memset(repeatKey_, 0, sizeof(repeatKey_));
	memset(keyCounter_, 0, sizeof(keyCounter_));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Keyboard::~Keyboard()
{
}

//=============================================================================
// ���͏��̏�����
//=============================================================================
HRESULT Keyboard::Init(HINSTANCE instance, HWND wnd)
{
	HRESULT hr;

	// �e�N���X�̏���������
	Input::Init(instance, wnd);

	// �f�o�C�X�I�u�W�F�N�g���쐬
	hr = input_->CreateDevice(GUID_SysKeyboard, &device_, nullptr);
	if (FAILED(hr)) {
		MessageBox(nullptr,
			"�f�o�C�X�I�u�W�F�N�g���쐬�ł��܂���ł���",
			"�L�[�{�[�h�̏�����", MB_OK);
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr = device_->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr)) {
		MessageBox(nullptr,
			"�f�[�^�t�H�[�}�b�g���ݒ�ł��܂���ł���",
			"�L�[�{�[�h�̏�����", MB_OK);
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = device_->SetCooperativeLevel(wnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr)) {
		MessageBox(nullptr,
			"�������[�h���ݒ�ł��܂���ł���",
			"�L�[�{�[�h�̏�����", MB_OK);
	}


	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	device_->Acquire();


	return S_OK;
}

//=============================================================================
// ���͏��̍X�V����
//=============================================================================
void Keyboard::Update()
{
	BYTE key_state[KEY_MAX];
	anykeyFlag_ = false;


	if (SUCCEEDED(device_->GetDeviceState(sizeof(key_state), &key_state))) {
		// �e��L�[���͏�Ԃ̍쐬�ƕۑ�
		for (int nKey = 0; nKey < KEY_MAX; nKey++) {

			// �������Ԃ̃J�E���g�A�b�v
			if (key_state[nKey]) {
				keyCounter_[nKey]++;
				anykeyFlag_ = true;
			} else {
				keyCounter_[nKey] = 0;
			}


			triggerKey_[nKey] = ~(pressKey_[nKey] & key_state[nKey]) & key_state[nKey];  // �g���K�[�L�[
			releaseKey_[nKey] = ~(pressKey_[nKey] & key_state[nKey]) & pressKey_[nKey];  // �����[�X�L�[

			// ���s�[�g�L�[
			if (keyCounter_[nKey] < REPEAT_FRAME) {
				repeatKey_[nKey] = triggerKey_[nKey];
			} else {
				repeatKey_[nKey] = key_state[nKey];
			}

			pressKey_[nKey] = key_state[nKey];  // �v���X�L�[
		}
	} else {
		// �L�[�{�[�h�̃A�N�Z�X�����Ď擾
		device_->Acquire();
	}
}

//=============================================================================
// �L�[�{�[�h�̃v���X��Ԃ��擾
//=============================================================================
bool Keyboard::GetPressKey(int key)
{
	if (pressKey_[key] & KEY_MASK) {
		return true;
	}


	return false;
}

//=============================================================================
// �L�[�{�[�h�̃g���K�[��Ԃ��擾
//=============================================================================
bool Keyboard::GetTriggerKey(int key)
{
	if (triggerKey_[key] & KEY_MASK) {
		return true;
	}


	return false;
}

//=============================================================================
// �L�[�{�[�h�̃��s�[�g��Ԃ��擾
//=============================================================================
bool Keyboard::GetRepeatKey(int key)
{
	if (repeatKey_[key] & KEY_MASK) {
		return true;
	}


	return false;
}

//=============================================================================
// �L�[�{�[�h�̃����|�X��Ԃ��擾
//=============================================================================
bool Keyboard::GetReleaseKey(int key)
{
	if (releaseKey_[key] & KEY_MASK) {
		return true;
	}


	return false;
}


// End of file