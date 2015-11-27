//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// ���͂̊Ǘ�
// 
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �C���N���[�h
#include "input_alias.h"

//*****************************************************************************
// �O���錾
class Input;
class InputEventBuffer;

//*****************************************************************************
// �N���X�݌v
class InputManager
{
public:
	
	InputManager(
		HWND handle_window,
		HINSTANCE handle_instance) : 
		_input_event_buffer(nullptr)
	{
		Initialize(handle_window,handle_instance);
	}

	virtual ~InputManager(){ Finalize(); }

	// ������
	void Initialize(
		HWND handle_window,
		HINSTANCE handle_instance);

	// �I��
	void Finalize();

	// �X�V
	void Update();

	// �v���X
	bool CheckPress(INPUT_EVENT);

	// �g���K�[
	bool CheckTrigger(INPUT_EVENT);

	// �����[�X
	bool CheckRelease(INPUT_EVENT);

	// ���s�[�g
	bool CheckRepeat(INPUT_EVENT);

	// �f�[�^�ݒ�
	// �U���̐ݒ�
	// 0�͎~�܂�
	void SetEventValue(INPUT_EVENT_VALUE, s32 Value );

	// �f�[�^�擾
	// �p�b�h�̒l���Ԃ��Ă���
	s32 GetEventValue(INPUT_EVENT_VALUE);
	
private:

	std::vector<Input*> _input_device_list;
	InputEventBuffer *_input_event_buffer;
};