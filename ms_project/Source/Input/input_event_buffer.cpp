//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// �C���v�b�g�C�x���g
// 
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// �C���N���[�h
#include "input_event_buffer.h"

//=============================================================================
// �R���X�g���N�^
InputEventBuffer::InputEventBuffer():
	_direct_input(nullptr),
	_handle_window(nullptr),
	_handle_instance(nullptr)
{
	ZeroMemory(_input_event_list, sizeof(_input_event_list));
	ZeroMemory(_input_event_value_list, sizeof(_input_event_value_list));
}

//=============================================================================
// ������
void InputEventBuffer::Initialize(
	HWND window_handle,
	HINSTANCE instance_handle)
{
	_handle_window = window_handle;
	_handle_instance = instance_handle;

	HRESULT result_handle = DirectInput8Create(
		instance_handle,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void **)&_direct_input,
		nullptr);

	ASSERT(result_handle == S_OK, "�C���v�b�g�f�o�C�X�̍쐬���s");
}

//=============================================================================
// �I��
void InputEventBuffer::Finalize()
{
	SafeRelease(_direct_input);
}