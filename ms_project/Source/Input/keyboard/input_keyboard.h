//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// �L�[�{�[�h
// 
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �C���N���[�h
#include "../input.h"

//*****************************************************************************
// �N���X�݌v
class InputKeyboard:public Input
{
public:
	InputKeyboard(InputEventBuffer *input_event_buffer);
	virtual ~InputKeyboard(){}

	void Initialize();
	void Finalize();
	void Update();

private:
	static const u16 kKeyMax = 256;
	bool _preview_key[kKeyMax];
};