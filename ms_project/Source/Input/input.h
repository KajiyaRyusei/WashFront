//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// 入力基底クラス
// 
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// 前方宣言
class InputEventBuffer;

//*****************************************************************************
// クラス設計
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
