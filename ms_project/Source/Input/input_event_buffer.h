//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// インプットイベント
//
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// インクルード
#include"input_alias.h"

//*****************************************************************************
// クラス設計
class InputEventBuffer
{
public:
	InputEventBuffer();
	virtual ~InputEventBuffer(){}

	void Initialize(
		HWND window_handle,
		HINSTANCE instance_handle);
	void Finalize();

	// ダイレクトインプット取得
	LPDIRECTINPUT8 GetDirectInput(){ return _direct_input; }

	// イベントデータの取得
	u8 GetInputEventList(INPUT_EVENT input_event)
	{
		return _input_event_list[input_event];
	}
	// イベントデータの設定
	void SetInputEventList(
		INPUT_EVENT input_event,
		bool press,
		bool trigger,
		bool release)
	{
		_input_event_list[input_event] = (press << 0) + (trigger << 1) + (release << 2);
	}
	// イベントバリューデータの取得
	s32 GetInputEventValue(INPUT_EVENT_VALUE input_event_value)
	{
		return _input_event_value_list[input_event_value];
	}
	// イベントバリューデータの設定
	void SetInputEventValue(
		INPUT_EVENT_VALUE input_event_value,
		s32 value)
	{
		_input_event_value_list[input_event_value] = value;
	}
	// インプットデバイス用ウィンドウハンドルを取得
	HWND GetWindowHandle(){ return _handle_window; }
private:
	LPDIRECTINPUT8 _direct_input;
	u8 _input_event_list[INPUT_EVENT_MAX];
	s32 _input_event_value_list[INPUT_EVENT_MAX];
	HWND _handle_window;
	HINSTANCE _handle_instance;
};