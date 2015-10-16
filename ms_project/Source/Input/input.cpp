//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// ���͊��N���X
// 
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// �C���N���[�h
#include "input.h"
#include "input_event_buffer.h"

//=============================================================================
// �R���X�g���N�^
Input::Input(InputEventBuffer *input_event_buffer) :
	_direct_input_device(nullptr),
	_input_event_buffer(input_event_buffer)
{

}

//=============================================================================
// �I��
void Input::Finalize()
{
	if (_direct_input_device != nullptr)
	{
		_direct_input_device->Unacquire();
		_direct_input_device->Release();
		_direct_input_device = nullptr;
	}
}