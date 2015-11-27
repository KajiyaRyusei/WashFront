//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// XInput
// 
// Created by Toshiki Mochizuki on 20151021
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// インクルード
#include "../input.h"
#include <XInput.h>

//*****************************************************************************
// ライブラリ
#pragma comment ( lib , "Xinput.lib" )

//*****************************************************************************
// クラス設計
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