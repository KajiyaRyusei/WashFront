//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// ウィンドウ
// 
// Created by Ryusei Kajiya on 20151005
//
// ウィンドウコマンド一覧:http://wisdom.sakura.ne.jp/system/winapi/windata1.html
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// クラス設計
class Window
{
public:

	Window(HINSTANCE handle_instance);

	virtual ~Window(){ Finalize(); }

	void Initialize();

	void Finalize();

	const HWND GetHandleWindow() const{ return _handle_window; }
	const HINSTANCE GetHandleInstance() const{ return _handle_instance; }
	const s32 GetSizeWindowWidth() const{ return _size_window_width; }
	const s32 GetSizeWindowHeight() const{ return _size_window_height; }

private:

	HINSTANCE _handle_instance;
	HWND _handle_window;
	s32 _size_window_width;
	s32 _size_window_height;
};