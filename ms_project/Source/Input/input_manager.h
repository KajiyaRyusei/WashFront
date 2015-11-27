//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// 入力の管理
// 
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// インクルード
#include "input_alias.h"

//*****************************************************************************
// 前方宣言
class Input;
class InputEventBuffer;

//*****************************************************************************
// クラス設計
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

	// 初期化
	void Initialize(
		HWND handle_window,
		HINSTANCE handle_instance);

	// 終了
	void Finalize();

	// 更新
	void Update();

	// プレス
	bool CheckPress(INPUT_EVENT);

	// トリガー
	bool CheckTrigger(INPUT_EVENT);

	// リリース
	bool CheckRelease(INPUT_EVENT);

	// リピート
	bool CheckRepeat(INPUT_EVENT);

	// データ設定
	// 振動の設定
	// 0は止まる
	void SetEventValue(INPUT_EVENT_VALUE, s32 Value );

	// データ取得
	// パッドの値が返ってくる
	s32 GetEventValue(INPUT_EVENT_VALUE);
	
private:

	std::vector<Input*> _input_device_list;
	InputEventBuffer *_input_event_buffer;
};