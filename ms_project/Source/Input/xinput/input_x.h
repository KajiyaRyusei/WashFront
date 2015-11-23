//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// XInput
// 
// Created by Toshiki Mochizuki on 20151021
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �C���N���[�h
#include "../input.h"
#include <XInput.h>

//*****************************************************************************
// ���C�u����
#pragma comment ( lib , "Xinput.lib" )

//*****************************************************************************
// �N���X�݌v
class InputX:public Input
{
public:
	InputX(InputEventBuffer *input_event_buffer);
	virtual ~InputX(){}

	void Initialize();
	void Finalize();
	void Update();

private:
	static const u8	kControllMax	= 4;
	static const u8	kBitMax			= 16;
	static const u8 kOptionNum		= 8;
	DWORD			_device_num;
	XINPUT_STATE*	_preview_state;

};