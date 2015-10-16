//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// システムの流れ
//
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// インクルード
#include "system_flow.h"
#include "application.h"
#include "Windows/window.h"
#include "Renderer/directx9.h"

//*****************************************************************************
// 定数
namespace
{
	static const fx32 kFrameRate = 1000.0f / 60.0f;
}

//=============================================================================
// 初期化
void SystemFlow::Initialize(const HINSTANCE handle_instance)
{
	// ウィンドウの生成
	_main_window = new Window(handle_instance);
	// レンダラ―の生成
	_renderer_device = new RendererDevice(_main_window->GetHandleWindow(), _main_window->GetSizeWindowWidth(), _main_window->GetSizeWindowHeight(),false);
	// 参照群に登録
	Reference::GetInstance().SetRenderer(_renderer_device);
	// アプリケーションの生成
	_applicaion = new Application(_main_window,_renderer_device);

	
}
//=============================================================================
// 終了
void SystemFlow::Finalize()
{
	SafeDelete(_applicaion);
	SafeDelete(_renderer_device);
	SafeDelete(_main_window);
}
//=============================================================================
// メッセージループ
void SystemFlow::MessageLoop()
{
	// 分解能を設定
	timeBeginPeriod(1);

	u64 exec_last_time = timeGetTime();
	u64 fps_last_time = timeGetTime();
	u64 current_time = 0;
	u64 frame_count = 0;
	u64 fps_count = 0;

	MSG message;
	bool no_exit = true;

	while( no_exit )
	{
		if (PeekMessage(
			&message,	// メッセージ情報
			nullptr,	// ウィンドウハンドル
			0,			// 最初のメッセージ
			0,			// 最後のメッセージ
			PM_REMOVE))	// メッセージを処理した後に、そのメッセージをキューから削除
		{// メッセージを受信したら
			if (message.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				no_exit = false;
			}
			else
			{// メッセージの翻訳と送出
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		else
		{// 通常のループ
			current_time = timeGetTime();
			if (current_time - fps_last_time >= 500)
			{// 0.5秒ごとに実行(fpsの確認)
				fps_count = frame_count * 1000 / (current_time - fps_last_time);
				fps_last_time = current_time;
				frame_count = 0;
			}

			if (current_time - exec_last_time >= 1000 / 60)
			{// fps調整
				exec_last_time = current_time;

				// 更新
				_applicaion->Update();

				// 描画
				_applicaion->Draw();

				frame_count = 0;
			}
		}
	}
	timeEndPeriod(1);
}
