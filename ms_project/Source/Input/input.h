//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// ���͊��N���X
// 
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �O���錾
class InputEventBuffer;

//*****************************************************************************
// �N���X�݌v
class Input
{
public:
	Input(InputEventBuffer *input_event_buffer);
	virtual ~Input(){}
	virtual void Initialize(void){}
	virtual void Finalize() = 0;
	virtual void Update() = 0;

protected:
	LPDIRECTINPUTDEVICE8 _direct_input_device;
	InputEventBuffer *_input_event_buffer;
};
