//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// ウィンドウ
// 
// Created by Ryusei Kajiya on 20151005
// 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// インクルード
#include "window.h"
#include "window_procedure.h"

//*****************************************************************************
// 定数
namespace
{
	static const LPCWSTR kWindowClass = TEXT("Wash Front");
	static const LPCWSTR kWindowName = TEXT("Wash Front");
	 static const u32 kSizeWindowWidth = 1280;
	 static const u32 kSizeWindowHeight = 720;
	//static const u32 kSizeWindowWidth = 960;
	//static const u32 kSizeWindowHeight = 540;
};

//=============================================================================
// コンストラクタ
Window::Window(HINSTANCE handle_instance) :
	_handle_window{ nullptr },
	_handle_instance{ handle_instance },
	_size_window_width{ kSizeWindowWidth },
	_size_window_height{kSizeWindowHeight}
{
	Initialize();
}

//=============================================================================
// 初期化
void Window::Initialize()
{

	// ウィンドウクラス作成
	WNDCLASSEX window_class;
	window_class.cbSize = sizeof(WNDCLASSEX);				// 構造体のサイズ
	window_class.style = CS_CLASSDC;						// ウィンドウスタイル
	window_class.lpfnWndProc = WindowProcedure;				// ウィンドウプロシージャ
	window_class.cbClsExtra = 0;							// 予約語
	window_class.cbWndExtra = 0;							// 予約語
	window_class.hInstance = _handle_instance;				// インスタンス
	window_class.hIcon = nullptr;							// アイコン
	window_class.hCursor = LoadCursor(nullptr, IDC_ARROW);	// カーソル
	window_class.hbrBackground = (HBRUSH)(COLOR_WINDOW + 0);// 背景色
	window_class.lpszClassName = kWindowClass;				// クラスネーム
	window_class.lpszMenuName = kWindowName;				// メニューネーム
	window_class.hIconSm = nullptr;							// 小さいアイコン

	// 登録
	RegisterClassEx(&window_class);

	// ウィンドウ作成：タイトルバーがあり、サイズの変更できないウィンドウの周囲を囲む枠をピクセル単位で取得 + タイトルバーの高さをピクセル単位で取得
	u32 window_size_width = kSizeWindowWidth + GetSystemMetrics(SM_CXDLGFRAME) * 2;
	u32 window_size_height = kSizeWindowHeight + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION);

	// 可視状態＋タイトルと枠をもつ＋タイトルバーを作成＋メニューボックスを配置＋最小化と最大化を許可
	_handle_window = CreateWindowEx(
		0,
		kWindowClass,
		kWindowName,
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		window_size_width,
		window_size_height,
		nullptr,
		nullptr,
		_handle_instance,
		nullptr);

	ASSERT(_handle_window != nullptr, "ウィンドウハンドルの取得に失敗しました\n");

	// ウィンドウ表示
	ShowWindow(_handle_window, SW_SHOW);
	UpdateWindow(_handle_window);

	// 登録
	Reference::GetInstance().SetHandleWindow(_handle_window);
	Reference::GetInstance().SetSizeScreenHeight(kSizeWindowWidth);
	Reference::GetInstance().SetSizeScreenWidth(kSizeWindowWidth);
}
//=============================================================================
// 終了
void Window::Finalize()
{
	UnregisterClass(kWindowClass, _handle_instance);
}
