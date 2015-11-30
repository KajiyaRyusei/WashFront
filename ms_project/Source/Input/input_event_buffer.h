//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �C���v�b�g�C�x���g
//
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �C���N���[�h
#include"input_alias.h"

//*****************************************************************************
// �N���X�݌v
class InputEventBuffer
{
public:
	InputEventBuffer();
	virtual ~InputEventBuffer(){}

	void Initialize(
		HWND window_handle,
		HINSTANCE instance_handle);
	void Finalize();

	// �_�C���N�g�C���v�b�g�擾
	LPDIRECTINPUT8 GetDirectInput(){ return _direct_input; }

	// �C�x���g�f�[�^�̎擾
	u8 GetInputEventList(INPUT_EVENT input_event)
	{
		return _input_event_list[input_event];
	}
	// �C�x���g�f�[�^�̐ݒ�
	void SetInputEventList(
		INPUT_EVENT input_event,
		bool press,
		bool trigger,
		bool release)
	{
		_input_event_list[input_event] = (press << 0) + (trigger << 1) + (release << 2);
	}
	// �C�x���g�o�����[�f�[�^�̎擾
	s32 GetInputEventValue(INPUT_EVENT_VALUE input_event_value)
	{
		return _input_event_value_list[input_event_value];
	}
	// �C�x���g�o�����[�f�[�^�̐ݒ�
	void SetInputEventValue(
		INPUT_EVENT_VALUE input_event_value,
		s32 value)
	{
		_input_event_value_list[input_event_value] = value;
	}
	// �C���v�b�g�f�o�C�X�p�E�B���h�E�n���h�����擾
	HWND GetWindowHandle(){ return _handle_window; }
private:
	LPDIRECTINPUT8 _direct_input;
	u8 _input_event_list[INPUT_EVENT_MAX];
	s32 _input_event_value_list[INPUT_EVENT_MAX];
	HWND _handle_window;
	HINSTANCE _handle_instance;
};