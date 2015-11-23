//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// ���͂̊Ǘ�
// 
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// �C���N���[�h
#include "input_manager.h"
#include "input_event_buffer.h"
#include "keyboard/input_keyboard.h"
#include "xinput\input_x.h"

//*****************************************************************************
// �萔
namespace
{
	static const char kPressBit		= 0x01;
	static const char kTriggerBit	= 0x02;
	static const char kReleaseBit	= 0x04;
	static const char kRepeateBit	= 0x08;
};

//=============================================================================
// ������
void InputManager::Initialize(
	HWND handle_window,
	HINSTANCE handle_instance)
{
	// �C�x���g�o�b�t�@����
	_input_event_buffer = new InputEventBuffer();
	ASSERT(_input_event_buffer != nullptr,"�C�x���g�o�b�t�@���������s");
	_input_event_buffer->Initialize(handle_window, handle_instance);

	// �L�[�{�[�h����
	_input_device_list.push_back(new InputKeyboard(_input_event_buffer));

	// XInput
	_input_device_list.push_back( new InputX( _input_event_buffer ) );

	for (auto it = _input_device_list.begin(); it < _input_device_list.end(); ++it)
	{// �f�o�C�X�̏�����
		(*it)->Initialize();
	}
	// ���t�@�����X�o�^
}

//=============================================================================
// �I��
void InputManager::Finalize()
{

	for (auto it = _input_device_list.begin(); it < _input_device_list.end(); ++it)
	{// �f�o�C�X�̏I��
		(*it)->Finalize();
		SafeDelete((*it));
	}
	_input_device_list.clear();

	if (_input_event_buffer != nullptr)
	{// �C�x���g�o�b�t�@�̏I��
		_input_event_buffer->Finalize();
		SafeDelete(_input_event_buffer);
	}
}

//=============================================================================
// �X�V
void InputManager::Update()
{
	for (auto it = _input_device_list.begin(); it < _input_device_list.end(); ++it)
	{// �f�o�C�X�̍X�V
		(*it)->Update();
	}
}

//=============================================================================
// �v���X
bool InputManager::CheckPress(INPUT_EVENT input_event)
{
	return _input_event_buffer->GetInputEventList(input_event) & kPressBit ? true : false;
}
//=============================================================================
// �g���K�[
bool InputManager::CheckTrigger(INPUT_EVENT input_event)
{
	return _input_event_buffer->GetInputEventList(input_event) & kTriggerBit ? true : false;
}
//=============================================================================
// �����[�X
bool InputManager::CheckRelease(INPUT_EVENT input_event)
{
	return _input_event_buffer->GetInputEventList(input_event) & kReleaseBit ? true : false;
}
//=============================================================================
// ���s�[�g
bool InputManager::CheckRepeat(INPUT_EVENT input_event)
{
	return _input_event_buffer->GetInputEventList(input_event) & kRepeateBit ? true : false;
}
//=============================================================================
// �f�[�^�Z�b�g
void InputManager::SetEventValue(INPUT_EVENT_VALUE input_event_value ,s32 Value)
{
	_input_event_buffer->SetInputEventValue( input_event_value , Value );
}
//=============================================================================
// �f�[�^�擾
s32 InputManager::GetEventValue(INPUT_EVENT_VALUE input_event_value)
{
	return _input_event_buffer->GetInputEventValue( input_event_value );
}