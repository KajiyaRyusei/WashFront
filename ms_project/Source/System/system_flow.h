//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// システムの流れ
//
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// 前方宣言
class Window;
class Application;
class RendererDevice;

//*****************************************************************************
// クラス設計
class SystemFlow
{
public:

	SystemFlow() :
		_main_window{ nullptr },
		_applicaion{ nullptr },
		_renderer_device{ nullptr }
	{}

	virtual ~SystemFlow(){ Finalize(); }

	// 初期化
	void Initialize(const HINSTANCE handle_instance);

	// 終了
	void Finalize();

	// メッセージループ
	void MessageLoop();

private:

	Window *_main_window;
	Application *_applicaion;
	RendererDevice *_renderer_device;
};