//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// キーボード
// 
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// インクルード
#include "../input.h"

//*****************************************************************************
// クラス設計
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