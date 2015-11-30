//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// �L�[�{�[�h
// 
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// �C���N���[�h
#include "input_keyboard.h"
#include "../input_event_buffer.h"

//=============================================================================
// �R���X�g���N�^
InputKeyboard::InputKeyboard(InputEventBuffer *input_event_buffer) :
	Input(input_event_buffer)
{
	ZeroMemory(_preview_key, sizeof(_preview_key));
}
//=============================================================================
// ������
void InputKeyboard::Initialize()
{
	HRESULT handle_result;
	LPDIRECTINPUT8 direct_input = _input_event_buffer->GetDirectInput();

	// �f�o�C�X�I�u�W�F�N�g�̍쐬
	handle_result = direct_input->CreateDevice(
		GUID_SysKeyboard,
		&_direct_input_device,
		nullptr);
	ASSERT(handle_result == S_OK, "�f�o�C�X�I�u�W�F�N�g�̍쐬�Ɏ��s");

	// �f�[�^�t�H�[�}�b�g��ݒ�
	handle_result = _direct_input_device->SetDataFormat(&c_dfDIKeyboard);
	ASSERT(handle_result == S_OK, "�f�[�^�t�H�[�}�b�g�̍쐬�Ɏ��s");

	// �������[�h��ݒ�
	handle_result = _direct_input_device->SetCooperativeLevel(
		_input_event_buffer->GetWindowHandle(),
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	ASSERT(handle_result == S_OK, "�������[�h�Ɏ��s");

	// �A�N�Z�X�����擾
	_direct_input_device->Acquire();


}
//=============================================================================
// �I��
void InputKeyboard::Finalize()
{
	Input::Finalize();
}
//=============================================================================
// �X�V
void InputKeyboard::Update()
{
	u8 key_state[kKeyMax] = {0};
	bool press_key = false;
	bool trigger_key = false;
	bool release_key = false;

	HRESULT result_handle = _direct_input_device->GetDeviceState(
		sizeof(key_state),
		key_state);
	if (FAILED(result_handle))
	{// �X�e�[�g��������������������
		ZeroMemory(key_state, sizeof(key_state));
		_direct_input_device->Acquire();
	}

	for (s32 i = 0; i < kKeyMax; ++i)
	{
		// �v���X�L�[�̎Z�o
		press_key = (key_state[i] & 0x80) ? true : false;

		// �g���K�[�L�[�̎Z�o
		trigger_key = (press_key ^ _preview_key[i]) & press_key;

		// �����[�X�L�[�̎Z�o
		release_key = (press_key ^ _preview_key[i]) & !press_key;

		// �v���r���[�L�[�̕ۑ�
		_preview_key[i] = press_key;

		// �C�x���g�o�b�t�@�Ƀf�[�^��ۑ����@�̌���
		_input_event_buffer->SetInputEventList(
			static_cast<INPUT_EVENT>(i),
			press_key, trigger_key, release_key);
	}
}