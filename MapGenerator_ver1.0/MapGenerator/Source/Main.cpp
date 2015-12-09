//=============================================================================
//
// メイン処理 [Main.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "Manager.h"
#include "../resource.h"
#include "ImportFileManager.h"
#include "ObjectManager.h"
#include "Building.h"
#include "RouteManager.h"
#include "DirtManager.h"
#include "Cursor.h"
#include "CameraManager.h"
#include <commctrl.h>


//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define CLASS_NAME		("AppClass")				// ウインドウのクラス名
#define WINDOW_NAME		("MAP GENERATOR")			// ウインドウのキャプション名
#define ICON_PATH		("")	// exeアイコン


//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------

// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM w_param, LPARAM l_param);

// ダイアログプロシージャ
BOOL CALLBACK ObjectDlgProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam);

// ダイアログプロシージャ
BOOL CALLBACK RouteDlgProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam);

// ダイアログプロシージャ
BOOL CALLBACK DirtDlgProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam);

// モデルファイルの読み込み
void ImportModelFile(HWND windowHandle);

// テクスチャファイルの読み込み
void ImportTextureFile(HWND windowHandle);

// モデルの生成
void CreateModel(HWND hDlg);

// 左クリック時のイベント
void ClickLeftEventObjectMode();
void ClickLeftEventRouteMode();
void ClickLeftEventDirtMode();

// 読み込み関数
void ReadMapFile(HWND hWnd);

// 保存関数
void SaveMapFile(HWND hWnd);

// 読み込み関数
void ReadRouteFile(HWND hWnd);

// 保存関数
void SaveRouteFile(HWND hWnd);

// 読み込み関数
void ReadDirtFile(HWND hWnd);

// 保存関数
void SaveDirtFile(HWND hWnd);


//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
HWND g_windowHandle = nullptr;
HWND g_objectDialogHandle = nullptr;
HWND g_routeDialogHandle = nullptr;
HWND g_dirtDialogHandle = nullptr;

MODE g_mode = MODE_OBJECT;

TCHAR g_szFile[MAX_PATH] = {};


#ifdef _DEBUG
float g_fps_count;  // FPSカウンタ
#endif


//=============================================================================
// エントリポイント
//=============================================================================
int APIENTRY WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR cmd_line, int cmd_show)
{
	UNREFERENCED_PARAMETER(prev_instance);  // 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(cmd_line);  // 無くても良いけど、警告が出る（未使用宣言）

	// プログラム終了時メモリリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;


	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		instance,
		(HICON)LoadImage(instance, ICON_PATH, IMAGE_ICON, 0, 0, LR_SHARED | LR_LOADFROMFILE),
		LoadCursor(nullptr, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		MAKEINTRESOURCE(IDR_MENU1),
		CLASS_NAME,
		nullptr
	};


	MSG msg;

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
	g_windowHandle = CreateWindowEx(
		0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,
		SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
		nullptr,
		nullptr,
		instance,
		nullptr);


	// グラフィック環境の初期化
	bool window = true;
#ifdef _RELEASE
	if (IDYES == MessageBox(g_windowHandle, "フルスクリーンで実行しますか？", "画面モード", MB_YESNO)) {
		window = false;
	}
#endif




	// 初期化処理(ウィンドウを作成してから行う)
	if (FAILED(Manager::GetInstance()->Init(instance, g_windowHandle, window))) {
		return -1;
	}

	//フレームカウント初期化
	timeBeginPeriod(1);  // 分解能を設定
	dwExecLastTime =
	dwFPSLastTime = timeGetTime();
	dwCurrentTime =
	dwFrameCount = 0;


	// ウインドウの表示(初期化処理の後に呼ばないと駄目)
	ShowWindow(g_windowHandle, cmd_show);
	UpdateWindow(g_windowHandle);



	// ダイアログの作成
	g_objectDialogHandle = CreateDialog(instance, MAKEINTRESOURCE(IDD_DIALOG1),
		g_windowHandle, ObjectDlgProc);
	ShowWindow(g_objectDialogHandle, cmd_show);
	UpdateWindow(g_objectDialogHandle);


	// ダイアログの作成
	g_routeDialogHandle = CreateDialog(instance, MAKEINTRESOURCE(IDD_DIALOG2),
		g_windowHandle, RouteDlgProc);
	//ShowWindow(g_routeDialogHandle, cmd_show);
	UpdateWindow(g_routeDialogHandle);


	// ダイアログの作成
	g_dirtDialogHandle = CreateDialog(instance, MAKEINTRESOURCE(IDD_DIALOG3),
		g_windowHandle, DirtDlgProc);
	//ShowWindow(g_dirtDialogHandle, cmd_show);
	UpdateWindow(g_dirtDialogHandle);



	// メッセージループ
	while (1) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {  // PostQuitMessage()が呼ばれたらループ終了
				break;
			} else {
				// メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		} else {
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500) {  // 0.5秒ごとに実行
#ifdef _DEBUG
				g_fps_count = dwFrameCount * 1000.0f / (dwCurrentTime - dwFPSLastTime);
#endif
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60)) {
			dwExecLastTime = dwCurrentTime;

				// 更新処理
				Manager::GetInstance()->Update();

				// 描画処理
				Manager::GetInstance()->Draw();

				dwFrameCount++;
			}
		}
	}

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 終了処理
	Manager::Destory();

	timeEndPeriod(1);  // 分解能を戻す


	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CLOSE:
		if (IDYES == MessageBox(g_windowHandle, "終了しますか？", "プログラムの終了", MB_YESNO))
			DestroyWindow(wnd);
		else
			return 0;

	case WM_KEYDOWN:
		switch (w_param) {
		case VK_ESCAPE:
//			DestroyWindow(wnd);
			break;
		}
	break;


	case WM_COMMAND:
		switch (LOWORD(w_param)) {

		// 開く
		case ID_40001:
			// ファイルの読み込み
			if (IDYES == MessageBox(g_windowHandle, "現在の編集情報は破棄されますがよろしいですか", "警告", MB_YESNO))
				ReadMapFile(wnd);
			break;

		// 終了
		case ID_40002:
			if (IDYES == MessageBox(g_windowHandle, "終了しますか？", "プログラムの終了", MB_YESNO))
				DestroyWindow(wnd);
			break;


		// モデルのインポート
		case ID_40003:
			// モデルファイル読み込み
			ImportModelFile(wnd);
			break;

			// テクスチャのインポート
		case ID_40007:
			// テクスチャファイル読み込み
			ImportTextureFile(wnd);
			break;

		// 名前をつけて保存
		case ID_40006:
			// 保存
			SaveMapFile(wnd);
			break;

		// ルートの保存
		case ID_40008:
			SaveRouteFile(wnd);
			break;

			// ルートの読み込み
		case ID_40009:
			if (IDYES == MessageBox(g_windowHandle, "現在の編集情報は破棄されますがよろしいですか", "警告", MB_YESNO))
				ReadRouteFile(wnd);
			break;

			// 汚れの保存
		case ID_40010:
			SaveDirtFile(wnd);
			break;

			// 汚れの読み込み
		case ID_40011:
			if (IDYES == MessageBox(g_windowHandle, "現在の編集情報は破棄されますがよろしいですか", "警告", MB_YESNO))
				ReadDirtFile(wnd);
			break;


			// オブジェクト
		case ID_40013:
		{
				HMENU menu = GetMenu(wnd);
				CheckMenuItem(menu, ID_40013, MF_BYCOMMAND | MFS_CHECKED);
				CheckMenuItem(menu, ID_40014, MF_BYCOMMAND | MFS_UNCHECKED);
				CheckMenuItem(menu, ID_40015, MF_BYCOMMAND | MFS_UNCHECKED);
				ShowWindow(g_objectDialogHandle, SW_SHOW);
				ShowWindow(g_routeDialogHandle, SW_HIDE);
				ShowWindow(g_dirtDialogHandle, SW_HIDE);
				g_mode = MODE_OBJECT;
				 break;
		}
			// ルート
		case ID_40014:
		{
			HMENU menu = GetMenu(wnd);
			CheckMenuItem(menu, ID_40013, MF_BYCOMMAND | MFS_UNCHECKED);
			CheckMenuItem(menu, ID_40014, MF_BYCOMMAND | MFS_CHECKED);
			CheckMenuItem(menu, ID_40015, MF_BYCOMMAND | MFS_UNCHECKED);
			ShowWindow(g_objectDialogHandle, SW_HIDE);
			ShowWindow(g_routeDialogHandle, SW_SHOW);
			ShowWindow(g_dirtDialogHandle, SW_HIDE);
			g_mode = MODE_ROUTE;
			break;
		}
			// 汚れ
		case ID_40015:
		{
			HMENU menu = GetMenu(wnd);
			CheckMenuItem(menu, ID_40013, MF_BYCOMMAND | MFS_UNCHECKED);
			CheckMenuItem(menu, ID_40014, MF_BYCOMMAND | MFS_UNCHECKED);
			CheckMenuItem(menu, ID_40015, MF_BYCOMMAND | MFS_CHECKED);
			ShowWindow(g_objectDialogHandle, SW_HIDE);
			ShowWindow(g_routeDialogHandle, SW_HIDE);
			ShowWindow(g_dirtDialogHandle, SW_SHOW);
			g_mode = MODE_DIRT;
			break;
		}

		default:
			break;
		}
		break;


		// マウス左クリック時
	case WM_LBUTTONDOWN:
	{
		switch (g_mode) {
		case MODE_OBJECT:
			ClickLeftEventObjectMode();
			break;
		case MODE_ROUTE:
			ClickLeftEventRouteMode();
			break;
		case MODE_DIRT:
			ClickLeftEventDirtMode();
			break;
		default:
			break;
		}

	}
	break;

	default:
		break;
	}

	return DefWindowProc(wnd, msg, w_param, l_param);
}


//=============================================================================
// ダイアログプロシージャ
//=============================================================================
BOOL CALLBACK ObjectDlgProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg) {

		// ダイアログ初期化
	case WM_INITDIALOG:
	{
		// スピンコントロールとエディットボックスの関連付け

		SendMessage(
			(HWND)GetDlgItem(hDlg, IDC_SPIN1),		// スピンコントロールのハンドル
			(UINT)UDM_SETBUDDY,
			(WPARAM)GetDlgItem(hDlg, IDC_EDIT2),	// 関連付けるコントロールのハンドル
			0										// 0固定
			);
		SendMessage(
			(HWND)GetDlgItem(hDlg, IDC_SPIN2),		// スピンコントロールのハンドル
			(UINT)UDM_SETBUDDY,
			(WPARAM)GetDlgItem(hDlg, IDC_EDIT3),	// 関連付けるコントロールのハンドル
			0										// 0固定
			);
		SendMessage(
			(HWND)GetDlgItem(hDlg, IDC_SPIN3),		// スピンコントロールのハンドル
			(UINT)UDM_SETBUDDY,
			(WPARAM)GetDlgItem(hDlg, IDC_EDIT4),	// 関連付けるコントロールのハンドル
			0										// 0固定
			);
	}
		return TRUE;

		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			 return TRUE;

		case IDCANCEL:
			 return TRUE;


		// モデルの生成
		case IDC_BUTTON1:
			CreateModel(hDlg);
			break;

		// コピー
		case IDC_BUTTON2:
			Manager::GetInstance()->GetObjectManager()->CopyBuilding();
			break;

		// 座標 : X軸
		case IDC_EDIT2:
			if (HIWORD(wParam) == EN_UPDATE) {

				Building *building = Manager::GetInstance()->GetObjectManager()->GetSelectBuilding();
				if (building) {
					char str[4096] = {};
					GetWindowText(
						(HWND)GetDlgItem(g_objectDialogHandle, IDC_EDIT2),		// スライダーのハンドル
						str, 4096);
					double positionX = atof(str);
					building->SetPositionX((float)positionX);
				}
			}
			break;

		// 座標 : Y軸
		case IDC_EDIT3:
			if (HIWORD(wParam) == EN_UPDATE) {

				Building *building = Manager::GetInstance()->GetObjectManager()->GetSelectBuilding();
				if (building) {
					char str[4096] = {};
					GetWindowText(
						(HWND)GetDlgItem(g_objectDialogHandle, IDC_EDIT3),		// スライダーのハンドル
						str, 4096);
					double positionY = atof(str);
					building->SetPositionY((float)positionY);
				}
			}
			break;

		// 座標 : Z軸
		case IDC_EDIT4:
			if (HIWORD(wParam) == EN_UPDATE) {

				Building *building = Manager::GetInstance()->GetObjectManager()->GetSelectBuilding();
				if (building) {
					char str[4096] = {};
					GetWindowText(
						(HWND)GetDlgItem(g_objectDialogHandle, IDC_EDIT4),		// スライダーのハンドル
						str, 4096);
					double positionZ = atof(str);
					building->SetPositionZ((float)positionZ);
				}
			}
			break;


		// スケール : X軸
		case IDC_EDIT5:
			if (HIWORD(wParam) == EN_UPDATE) {

				Building *building = Manager::GetInstance()->GetObjectManager()->GetSelectBuilding();
				if (building) {
					char str[4096] = {};
					GetWindowText(
						(HWND)GetDlgItem(g_objectDialogHandle, IDC_EDIT5),		// スライダーのハンドル
						str, 4096);
					double scaleX = atof(str);
					building->SetScaleX((float)scaleX);
				}
			}
			break;

		// スケール : Y軸
		case IDC_EDIT6:
			if (HIWORD(wParam) == EN_UPDATE) {

				Building *building = Manager::GetInstance()->GetObjectManager()->GetSelectBuilding();
				if (building) {
					char str[4096] = {};
					GetWindowText(
						(HWND)GetDlgItem(g_objectDialogHandle, IDC_EDIT6),		// スライダーのハンドル
						str, 4096);
					double scaleY = atof(str);
					building->SetScaleY((float)scaleY);
				}
			}
			break;

			// スケール : X軸
		case IDC_EDIT7:
			if (HIWORD(wParam) == EN_UPDATE) {

				Building *building = Manager::GetInstance()->GetObjectManager()->GetSelectBuilding();
				if (building) {
					char str[4096] = {};
					GetWindowText(
						(HWND)GetDlgItem(g_objectDialogHandle, IDC_EDIT7),		// スライダーのハンドル
						str, 4096);
					double scaleZ = atof(str);
					building->SetScaleZ((float)scaleZ);
				}
			}
			break;

		case IDC_CHECK1:
		{
			bool check;
			Building *building = Manager::GetInstance()->GetObjectManager()->GetSelectBuilding();
			if (building) {
				check = (bool)SendMessage((HWND)GetDlgItem(hDlg, IDC_CHECK1), (UINT)BM_GETCHECK, 0, 0);
				building->SetCollision(check);
			}
		}
			break;


		default:
			return FALSE;
		}
		break;


	// 水平スライダーの値を取得
	case WM_HSCROLL:
	{
		
		Building *building = Manager::GetInstance()->GetObjectManager()->GetSelectBuilding();
		if (building) {

			float position = (float)SendMessage(
				(HWND)lParam,			// スライダーのハンドル
				(UINT)TBM_GETPOS,		// 座標の取得(0～100)
				0,						// ０固定
				0						// 追加する項目の文字列
				);

			// 向き : X軸スライダー
			if ((HWND)lParam == GetDlgItem(hDlg, IDC_SLIDER5)) {
				building->SetRotationX((position / 100 - 0.5f) * D3DX_PI * 2);
			}
			// 向き : Y軸スライダー
			if ((HWND)lParam == GetDlgItem(hDlg, IDC_SLIDER6)) {
				building->SetRotationY((position / 100 - 0.5f) * D3DX_PI * 2);
			}
			// 向き : Z軸スライダー
			if ((HWND)lParam == GetDlgItem(hDlg, IDC_SLIDER7)) {
				building->SetRotationZ((position / 100 - 0.5f) * D3DX_PI * 2);
			}

		}
		break;
	}


	case WM_NOTIFY:
		if (wParam == (WPARAM)IDC_SPIN1)
		{
			LPNMUPDOWN lpnmud = (LPNMUPDOWN)lParam;
			if (lpnmud->hdr.code == UDN_DELTAPOS)
			{
				char str[4096] = {};
				GetWindowText(
					(HWND)GetDlgItem(hDlg, IDC_EDIT2),		// スライダーのハンドル
					str, 4096);
				double positionX = atof(str);
				if ((lpnmud->iDelta) < 0)
				{
					positionX += 1.f;
				} else if ((lpnmud->iDelta) > 0)
				{
					positionX -= 1.f;
				}
				sprintf(str, "%.3f", positionX);
				SetDlgItemText(hDlg, IDC_EDIT2, (LPCTSTR)str);
			}
		}
		if (wParam == (WPARAM)IDC_SPIN2)
		{
			LPNMUPDOWN lpnmud = (LPNMUPDOWN)lParam;
			if (lpnmud->hdr.code == UDN_DELTAPOS)
			{
				char str[4096] = {};
				GetWindowText(
					(HWND)GetDlgItem(hDlg, IDC_EDIT3),		// スライダーのハンドル
					str, 4096);
				double positionX = atof(str);
				if ((lpnmud->iDelta) < 0)
				{
					positionX += 1.f;
				}
				else if ((lpnmud->iDelta) > 0)
				{
					positionX -= 1.f;
				}
				sprintf(str, "%.3f", positionX);
				SetDlgItemText(hDlg, IDC_EDIT3, (LPCTSTR)str);
			}
		}
		if (wParam == (WPARAM)IDC_SPIN3)
		{
			LPNMUPDOWN lpnmud = (LPNMUPDOWN)lParam;
			if (lpnmud->hdr.code == UDN_DELTAPOS)
			{
				char str[4096] = {};
				GetWindowText(
					(HWND)GetDlgItem(hDlg, IDC_EDIT4),		// スライダーのハンドル
					str, 4096);
				double positionX = atof(str);
				if ((lpnmud->iDelta) < 0)
				{
					positionX += 1.f;
				}
				else if ((lpnmud->iDelta) > 0)
				{
					positionX -= 1.f;
				}
				sprintf(str, "%.3f", positionX);
				SetDlgItemText(hDlg, IDC_EDIT4, (LPCTSTR)str);
			}
		}


		if (wParam == (WPARAM)IDC_SPIN4)
		{
			LPNMUPDOWN lpnmud = (LPNMUPDOWN)lParam;
			if (lpnmud->hdr.code == UDN_DELTAPOS)
			{
				char str[4096] = {};
				GetWindowText(
					(HWND)GetDlgItem(hDlg, IDC_EDIT5),		// スライダーのハンドル
					str, 4096);
				double positionX = atof(str);
				if ((lpnmud->iDelta) < 0)
				{
					positionX += 0.1f;
				}
				else if ((lpnmud->iDelta) > 0)
				{
					positionX -= 0.1f;
				}
				sprintf(str, "%.3f", positionX);
				SetDlgItemText(hDlg, IDC_EDIT5, (LPCTSTR)str);
			}
		}
		if (wParam == (WPARAM)IDC_SPIN5)
		{
			LPNMUPDOWN lpnmud = (LPNMUPDOWN)lParam;
			if (lpnmud->hdr.code == UDN_DELTAPOS)
			{
				char str[4096] = {};
				GetWindowText(
					(HWND)GetDlgItem(hDlg, IDC_EDIT6),		// スライダーのハンドル
					str, 4096);
				double positionX = atof(str);
				if ((lpnmud->iDelta) < 0)
				{
					positionX += 0.1f;
				}
				else if ((lpnmud->iDelta) > 0)
				{
					positionX -= 0.1f;
				}
				sprintf(str, "%.3f", positionX);
				SetDlgItemText(hDlg, IDC_EDIT6, (LPCTSTR)str);
			}
		}
		if (wParam == (WPARAM)IDC_SPIN6)
		{
			LPNMUPDOWN lpnmud = (LPNMUPDOWN)lParam;
			if (lpnmud->hdr.code == UDN_DELTAPOS)
			{
				char str[4096] = {};
				GetWindowText(
					(HWND)GetDlgItem(hDlg, IDC_EDIT7),		// スライダーのハンドル
					str, 4096);
				double positionX = atof(str);
				if ((lpnmud->iDelta) < 0)
				{
					positionX += 0.1f;
				}
				else if ((lpnmud->iDelta) > 0)
				{
					positionX -= 0.1f;
				}
				sprintf(str, "%.3f", positionX);
				SetDlgItemText(hDlg, IDC_EDIT7, (LPCTSTR)str);
			}
		}
		break;

		return TRUE;

	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return TRUE;

	default:
		break;
	}

	return FALSE;
}


//=============================================================================
// Windowハンドルの取得
//=============================================================================
HWND GetWindowHandle()
{
	return g_windowHandle;
}


#ifdef _DEBUG
//=============================================================================
// FPSカウンタの取得
//=============================================================================
float GetFps()
{
	return g_fps_count;
}
#endif



//=============================================================================
// モデルファイルの読み込み
//=============================================================================
void ImportModelFile(HWND windowHandle)
{
	OPENFILENAME ofn = {};
	TCHAR szPath[MAX_PATH] = { 0 };
	TCHAR szFile[MAX_PATH] = {};
	memset(g_szFile, 0, sizeof(TCHAR) * MAX_PATH);

	if (szPath[0] == TEXT('\0')) {
		GetCurrentDirectory(MAX_PATH, szPath);
	}

	// ダイアログの情報
	if (ofn.lStructSize == 0) {
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = windowHandle;
		ofn.lpstrInitialDir = szPath;	// 初期フォルダ位置
		ofn.lpstrFile = g_szFile;		// 選択ファイル格納
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrFilter = "モデルデータ(*.fbx)\0*.fbx";
		ofn.lpstrTitle = "モデルのインポート";
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	}

	// ダイアログ表示
	if (GetOpenFileName(&ofn)) {

		// モデルファイルの読み込み
		if (!Manager::GetInstance()->GetImportFileManager()->ImportFile(g_szFile))
			MessageBox(g_windowHandle, "すでに読み込まれています", "警告", MB_OK);
		else
			SendMessage(g_objectDialogHandle, WM_NULL, 0, 0);
	}
}

//=============================================================================
// テクスチャファイルの読み込み
//=============================================================================
void ImportTextureFile(HWND windowHandle)
{
	OPENFILENAME ofn = {};
	TCHAR szPath[MAX_PATH] = { 0 };
	TCHAR szFile[MAX_PATH] = {};
	memset(g_szFile, 0, sizeof(TCHAR)* MAX_PATH);

	if (szPath[0] == TEXT('\0')) {
		GetCurrentDirectory(MAX_PATH, szPath);
	}

	// ダイアログの情報
	if (ofn.lStructSize == 0) {
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = windowHandle;
		ofn.lpstrInitialDir = szPath;	// 初期フォルダ位置
		ofn.lpstrFile = g_szFile;		// 選択ファイル格納
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrFilter = "JPEG(*.jpg)\0*.jpg\0PNG(*.png)\0*.png";
		ofn.lpstrTitle = "テクスチャのインポート";
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	}

	// ダイアログ表示
	if (GetOpenFileName(&ofn)) {

		// モデルファイルの読み込み
		if (!Manager::GetInstance()->GetImportFileManager()->ImportFile(g_szFile))
			MessageBox(g_windowHandle, "すでに読み込まれています", "警告", MB_OK);
		else
			SendMessage(g_objectDialogHandle, WM_NULL, 0, 0);
	}
}


// モデルの生成
void CreateModel(HWND hDlg)
{

	// コンボボックスから生成するモデルのファイル名取得
	HWND hCombo1 = GetDlgItem(hDlg, IDC_COMBO1);
	int modelIndex = SendMessage(
		(HWND)hCombo1,			// コンボボックスのハンドル
		(UINT)CB_GETCURSEL,		// 選択中のインデックス取得
		0,						// ０固定
		0						// 追加する項目の文字列
		);

	// コンボボックスから生成するテクスチャのファイル名取得
	HWND hCombo2 = GetDlgItem(hDlg, IDC_COMBO2);
	int textureIndex = SendMessage(
		(HWND)hCombo2,			// コンボボックスのハンドル
		(UINT)CB_GETCURSEL,		// 選択中のインデックス取得
		0,						// ０固定
		0						// 追加する項目の文字列
		);

	// ファイル名の取得
	int intTxtLen = SendMessage(hCombo1, CB_GETLBTEXTLEN, modelIndex, 0);
	if (intTxtLen != CB_ERR)
	{
		char* modelBuf = new char[intTxtLen + 1];
		if (SendMessage(hCombo1, CB_GETLBTEXT, modelIndex, (LPARAM)modelBuf) != CB_ERR)
		{
			intTxtLen = SendMessage(hCombo2, CB_GETLBTEXTLEN, textureIndex, 0);
			if (intTxtLen != CB_ERR)
			{
				char* textureBuf = new char[intTxtLen + 1];
				if (SendMessage(hCombo2, CB_GETLBTEXT, textureIndex, (LPARAM)textureBuf) != CB_ERR)
				{

					// モデルの生成
					Manager::GetInstance()->GetObjectManager()->CreateBuilding(
						Manager::GetInstance()->GetImportFileManager()->GetModelFilePath(modelBuf),
						Manager::GetInstance()->GetImportFileManager()->GetTextureFilePath(textureBuf));
				}
				delete[] textureBuf;
			}
		}
		delete[] modelBuf;
	}

}


// 左クリック時のイベント
void ClickLeftEventObjectMode()
{
	// マウスとオブジェクトの衝突判定
	Manager::GetInstance()->GetObjectManager()->CheckCollisionMouseAndObject();


	// スライダーを選択中のオブジェクトの座標に合わせる
	Building *building = Manager::GetInstance()->GetObjectManager()->GetSelectBuilding();
	if (building) {
		D3DXVECTOR3 position = building->GetPosition();
		D3DXVECTOR3 rotation = building->GetRotation();
		D3DXVECTOR3 scale = building->GetScale();
		bool collision = building->GetCollision();


		// 向きスライダー
		SendMessage(
			(HWND)GetDlgItem(g_objectDialogHandle, IDC_SLIDER5),	// スライダーのハンドル
			(UINT)TBM_SETPOS,								// 座標の取得(0～100)
			(WPARAM)TRUE,									// ０固定
			(LPARAM)((rotation.x + D3DX_PI) / (D3DX_PI * 2) * 100)			// 追加する項目の文字列
			);
		SendMessage(
			(HWND)GetDlgItem(g_objectDialogHandle, IDC_SLIDER6),	// スライダーのハンドル
			(UINT)TBM_SETPOS,								// 座標の取得(0～100)
			(WPARAM)TRUE,									// ０固定
			(LPARAM)((rotation.y + D3DX_PI) / (D3DX_PI * 2) * 100)			// 追加する項目の文字列
			);
		SendMessage(
			(HWND)GetDlgItem(g_objectDialogHandle, IDC_SLIDER7),	// スライダーのハンドル
			(UINT)TBM_SETPOS,								// 座標の取得(0～100)
			(WPARAM)TRUE,									// ０固定
			(LPARAM)((rotation.z + D3DX_PI) / (D3DX_PI * 2) * 100)			// 追加する項目の文字列
			);



		// 座標エディットボックス
		char str[4096] = {};
		sprintf(str, "%.3f", position.x);
		SetWindowText(
			(HWND)GetDlgItem(g_objectDialogHandle, IDC_EDIT2),		// スライダーのハンドル
			str		// 追加する項目の文字列
			);

		sprintf(str, "%.3f", position.y);
		SetWindowText(
			(HWND)GetDlgItem(g_objectDialogHandle, IDC_EDIT3),		// スライダーのハンドル
			str		// 追加する項目の文字列
			);

		sprintf(str, "%.3f", position.z);
		SetWindowText(
			(HWND)GetDlgItem(g_objectDialogHandle, IDC_EDIT4),		// スライダーのハンドル
			str		// 追加する項目の文字列
			);



		// スケールエディットボックス
		sprintf(str, "%.3f", scale.x);
		SetWindowText(
			(HWND)GetDlgItem(g_objectDialogHandle, IDC_EDIT5),		// スライダーのハンドル
			str		// 追加する項目の文字列
			);

		sprintf(str, "%.3f", scale.y);
		SetWindowText(
			(HWND)GetDlgItem(g_objectDialogHandle, IDC_EDIT6),		// スライダーのハンドル
			str		// 追加する項目の文字列
			);

		sprintf(str, "%.3f", scale.z);
		SetWindowText(
			(HWND)GetDlgItem(g_objectDialogHandle, IDC_EDIT7),		// スライダーのハンドル
			str		// 追加する項目の文字列
			);


		if (collision)
			SendMessage((HWND)GetDlgItem(g_objectDialogHandle, IDC_CHECK1),
				(UINT)BM_SETCHECK, (WPARAM)BST_CHECKED, 0);
		else
			SendMessage((HWND)GetDlgItem(g_objectDialogHandle, IDC_CHECK1),
			(UINT)BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);

	}
}

// 左クリック時のイベント
void ClickLeftEventRouteMode()
{
	D3DXVECTOR3 position = Manager::GetInstance()->GetObjectManager()->GetCursor()->GetPosition();

	HWND radio1 = GetDlgItem(g_routeDialogHandle, IDC_RADIO6);
	HWND radio2 = GetDlgItem(g_routeDialogHandle, IDC_RADIO7);
	
	// 生成 : 追加
	if (SendMessage(radio1, BM_GETCHECK, 0, 0) == 1) {
		Manager::GetInstance()->GetRouteManager()->CreatePoint(position);
	}
	// 生成 : 挿入
	if (SendMessage(radio2, BM_GETCHECK, 0, 0) == 1) {
		Manager::GetInstance()->GetRouteManager()->InsertPoint(position);
	}
}

// 左クリック時のイベント
void ClickLeftEventDirtMode()
{
}




// 読み込み関数
void ReadMapFile(HWND hWnd)
{
	OPENFILENAME ofn = {};
	TCHAR szPath[MAX_PATH] = { 0 };
	TCHAR szFile[MAX_PATH] = {};

	if (szPath[0] == TEXT('\0')) {
		GetCurrentDirectory(MAX_PATH, szPath);
	}
	if (ofn.lStructSize == 0) {
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = hWnd;
		ofn.lpstrInitialDir = szPath;	// 初期フォルダ位置
		ofn.lpstrFile = szFile;			// 選択ファイル格納
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrDefExt = TEXT(".map");
		ofn.lpstrFilter = TEXT("マップファイル(*.map)\0*.map\0");
		ofn.lpstrTitle = TEXT("開く");
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	}

	if (GetSaveFileName(&ofn)) {
		FILE *file = nullptr;
		file = fopen(szFile, "rt");
		if (file) {

			// 現在の状況破棄
			HWND hCombo = GetDlgItem(g_objectDialogHandle, IDC_COMBO1);
			SendMessage((HWND)hCombo, (UINT)CB_RESETCONTENT, 0, 0);
			Manager::GetInstance()->GetObjectManager()->AllDeleteBuilding();
			
			// 読み込み
			Manager::GetInstance()->GetImportFileManager()->ReadImportData(file);
			Manager::GetInstance()->GetImportFileManager()->AllImportFile();
			Manager::GetInstance()->GetObjectManager()->ReadBuildingData(file);

			fclose(file);
		}
		else {
			MessageBox(g_windowHandle, "読み込みに失敗しました", "警告", MB_OK);
		}
	}
}

// 保存関数
void SaveMapFile(HWND hWnd)
{
	OPENFILENAME ofn = {};
	TCHAR szPath[MAX_PATH] = { 0 };
	TCHAR szFile[MAX_PATH] = {};

	if (szPath[0] == TEXT('\0')) {
		GetCurrentDirectory(MAX_PATH, szPath);
	}
	if (ofn.lStructSize == 0) {
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = hWnd;
		ofn.lpstrInitialDir = szPath;	// 初期フォルダ位置
		ofn.lpstrFile = szFile;			// 選択ファイル格納
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrDefExt = TEXT(".map");
		ofn.lpstrFilter = TEXT("マップファイル(*.map)\0*.map\0");
		ofn.lpstrTitle = TEXT("名前を付けて保存");
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;
	}

	if (GetSaveFileName(&ofn)) {
		FILE *file = nullptr;
		file = fopen(szFile, "wt");
		if (file) {
			Manager::GetInstance()->GetImportFileManager()->SaveImportData(file);
			Manager::GetInstance()->GetObjectManager()->SaveBuildingData(file);
			fclose(file);
		} else {
			MessageBox(g_windowHandle, "保存に失敗しました", "警告", MB_OK);
		}
	}
}






// ダイアログプロシージャ
BOOL CALLBACK RouteDlgProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg) {

		// ダイアログ初期化
	case WM_INITDIALOG:
	{

		// スピンコントロールとエディットボックスの関連付け
		SendMessage(
			(HWND)GetDlgItem(hDlg, IDC_SPIN1),		// スピンコントロールのハンドル
			(UINT)UDM_SETBUDDY,
			(WPARAM)GetDlgItem(hDlg, IDC_EDIT2),	// 関連付けるコントロールのハンドル
			0										// 0固定
			);
		SendMessage(
			(HWND)GetDlgItem(hDlg, IDC_SPIN2),		// スピンコントロールのハンドル
			(UINT)UDM_SETBUDDY,
			(WPARAM)GetDlgItem(hDlg, IDC_EDIT3),	// 関連付けるコントロールのハンドル
			0										// 0固定
			);
		SendMessage(
			(HWND)GetDlgItem(hDlg, IDC_SPIN3),		// スピンコントロールのハンドル
			(UINT)UDM_SETBUDDY,
			(WPARAM)GetDlgItem(hDlg, IDC_EDIT4),	// 関連付けるコントロールのハンドル
			0										// 0固定
			);
		SendMessage(
			(HWND)GetDlgItem(hDlg, IDC_SPIN11),		// スピンコントロールのハンドル
			(UINT)UDM_SETBUDDY,
			(WPARAM)GetDlgItem(hDlg, IDC_EDIT11),	// 関連付けるコントロールのハンドル
			0										// 0固定
			);


		// モードの設定
		HWND radio = GetDlgItem(hDlg, IDC_RADIO6);
		SendMessage(
			(HWND)radio,		// ラジオボタンのハンドル
			(UINT)BM_SETCHECK,
			(WPARAM)BST_CHECKED,
			0					// ０固定
			);


		HWND combo = GetDlgItem(hDlg, IDC_COMBO5);
		SendMessage((HWND)combo, (UINT)CB_ADDSTRING, 0, (LPARAM)"1Pカメラ");
		SendMessage((HWND)combo, (UINT)CB_ADDSTRING, 0, (LPARAM)"2Pカメラ");

		combo = GetDlgItem(hDlg, IDC_COMBO1);
		SendMessage((HWND)combo, (UINT)CB_ADDSTRING, 0, (LPARAM)"通常");
		SendMessage((HWND)combo, (UINT)CB_ADDSTRING, 0, (LPARAM)"イベント");

	}
		return TRUE;

		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			return TRUE;

		case IDCANCEL:
			return TRUE;

		// プレビュー再生
		case IDC_BUTTON2:
		{
			HWND combo = GetDlgItem(hDlg, IDC_COMBO5);
			int index = SendMessage((HWND)combo, (UINT)CB_GETCURSEL, 0, (LPARAM)0);
			Manager::GetInstance()->GetCameraManager()->ChangePreviewCamera(index);
		}
			break;

		// プレビュー停止
		case IDC_BUTTON3:
			Manager::GetInstance()->GetCameraManager()->ChangeEditorCamera();
			break;

			// ルートの選択
		case IDC_COMBO5:

			// 選択したとき
			if (HIWORD(wParam) == CBN_SELCHANGE) {
				// コンボボックスから生成するモデルのファイル名取得
				HWND hCombo = GetDlgItem(hDlg, IDC_COMBO5);
				int index = SendMessage(
					(HWND)hCombo,			// コンボボックスのハンドル
					(UINT)CB_GETCURSEL,		// 選択中のインデックス取得
					0,						// ０固定
					0						// 追加する項目の文字列
					);

				// 選択中のルートを変更
				Manager::GetInstance()->GetRouteManager()->SetRouteMode(index);
			}
			break;


		// 点の選択
		case IDC_COMBO4:
			if (HIWORD(wParam) == CBN_SELCHANGE
				&& Manager::GetInstance()->GetRouteManager()->GetRouteMode() == ROUTE_MODE_1P_CAMERA) {
				Manager::GetInstance()->GetRouteManager()->SelectPoint(IDC_COMBO4);
			}
			break;
		case IDC_COMBO2:
			if (HIWORD(wParam) == CBN_SELCHANGE
				&& Manager::GetInstance()->GetRouteManager()->GetRouteMode() == ROUTE_MODE_2P_CAMERA) {
				Manager::GetInstance()->GetRouteManager()->SelectPoint(IDC_COMBO2);
			}
			break;


			// 点の生成もしくは削除
		case IDC_BUTTON1:
		{
			HWND radio1 = GetDlgItem(hDlg, IDC_RADIO6);
			HWND radio2 = GetDlgItem(hDlg, IDC_RADIO7);
			HWND radio3 = GetDlgItem(hDlg, IDC_RADIO8);

			// 生成 : 追加
			if (SendMessage(radio1, BM_GETCHECK, 0, 0) == 1) {
				Manager::GetInstance()->GetRouteManager()->CreatePoint();
			}
			// 生成 : 挿入
			if (SendMessage(radio2, BM_GETCHECK, 0, 0) == 1) {
				Manager::GetInstance()->GetRouteManager()->InsertPoint();
			}
			// 削除
			if (SendMessage(radio3, BM_GETCHECK, 0, 0) == 1) {
				Manager::GetInstance()->GetRouteManager()->DeletePoint();
			}
		}
			break;

			// 座標 : X軸
		case IDC_EDIT2:
			if (HIWORD(wParam) == EN_UPDATE) {
				char str[4096] = {};
				GetWindowText(
					(HWND)GetDlgItem(g_routeDialogHandle, IDC_EDIT2),		// スライダーのハンドル
					str, 4096);
				double positionX = atof(str);
				Manager::GetInstance()->GetRouteManager()->SetPositionX((float)positionX);
			}
			break;

			// 座標 : Y軸
		case IDC_EDIT3:
			if (HIWORD(wParam) == EN_UPDATE) {
				char str[4096] = {};
				GetWindowText(
					(HWND)GetDlgItem(g_routeDialogHandle, IDC_EDIT3),		// スライダーのハンドル
					str, 4096);
				double positionY = atof(str);
				Manager::GetInstance()->GetRouteManager()->SetPositionY((float)positionY);
			}
			break;

			// 座標 : Z軸
		case IDC_EDIT4:
			if (HIWORD(wParam) == EN_UPDATE) {
				char str[4096] = {};
				GetWindowText(
					(HWND)GetDlgItem(g_routeDialogHandle, IDC_EDIT4),		// スライダーのハンドル
					str, 4096);
				double positionZ = atof(str);
				Manager::GetInstance()->GetRouteManager()->SetPositionZ((float)positionZ);
			}
			break;

			// Speed
		case IDC_EDIT11:
			if (HIWORD(wParam) == EN_UPDATE) {
				char str[4096] = {};
				GetWindowText(
					(HWND)GetDlgItem(g_routeDialogHandle, IDC_EDIT11),		// スライダーのハンドル
					str, 4096);
				double speed = atof(str);
				Manager::GetInstance()->GetRouteManager()->SetSpeed((float)speed);
			}
			break;


			// state
		case IDC_COMBO1:
		{
			HWND hCombo = GetDlgItem(hDlg, IDC_COMBO1);
			int index = SendMessage(
				(HWND)hCombo,			// コンボボックスのハンドル
				(UINT)CB_GETCURSEL,		// 選択中のインデックス取得
				0,						// ０固定
				0						// 追加する項目の文字列
				);

			Manager::GetInstance()->GetRouteManager()->SetState(index);
		}
			break;

		default:
			break;
		}
		break;

		// 水平スライダーの値を取得
	case WM_HSCROLL:
	{

		float position = (float)SendMessage(
			(HWND)lParam,			// スライダーのハンドル
			(UINT)TBM_GETPOS,		// 座標の取得(0～100)
			0,						// ０固定
			0						// 追加する項目の文字列
			);

		// 向き : X軸スライダー
		if ((HWND)lParam == GetDlgItem(hDlg, IDC_SLIDER1)) {
			Manager::GetInstance()->GetRouteManager()->SetRotationX(
				(position / 100 - 0.5f) * D3DX_PI * 2);
		}
		// 向き : Y軸スライダー
		if ((HWND)lParam == GetDlgItem(hDlg, IDC_SLIDER2)) {
			Manager::GetInstance()->GetRouteManager()->SetRotationY(
				(position / 100 - 0.5f) * D3DX_PI * 2);
		}
		// 向き : Z軸スライダー
		if ((HWND)lParam == GetDlgItem(hDlg, IDC_SLIDER3)) {
			Manager::GetInstance()->GetRouteManager()->SetRotationZ(
				(position / 100 - 0.5f) * D3DX_PI * 2);
		}

		// PlayerDirection : X
		if ((HWND)lParam == GetDlgItem(hDlg, IDC_SLIDER4)) {
			Manager::GetInstance()->GetRouteManager()->SetPlayerDirectionX(
				(position / 100 - 0.5f) * D3DX_PI * 2);
		}
		// PlayerDirection : Y
		if ((HWND)lParam == GetDlgItem(hDlg, IDC_SLIDER8)) {
			Manager::GetInstance()->GetRouteManager()->SetPlayerDirectionY(
				(position / 100 - 0.5f) * D3DX_PI * 2);
		}
		// PlayerDirection : Z
		if ((HWND)lParam == GetDlgItem(hDlg, IDC_SLIDER9)) {
			Manager::GetInstance()->GetRouteManager()->SetPlayerDirectionZ(
				(position / 100 - 0.5f) * D3DX_PI * 2);
		}
	}
		break;

	case WM_NOTIFY:
		if (wParam == (WPARAM)IDC_SPIN1)
		{
			LPNMUPDOWN lpnmud = (LPNMUPDOWN)lParam;
			if (lpnmud->hdr.code == UDN_DELTAPOS)
			{
				char str[4096] = {};
				GetWindowText(
					(HWND)GetDlgItem(hDlg, IDC_EDIT2),		// スライダーのハンドル
					str, 4096);
				double positionX = atof(str);
				if ((lpnmud->iDelta) < 0)
				{
					positionX += 1.f;
				}
				else if ((lpnmud->iDelta) > 0)
				{
					positionX -= 1.f;
				}
				sprintf(str, "%.3f", positionX);
				SetDlgItemText(hDlg, IDC_EDIT2, (LPCTSTR)str);
			}
		}
		if (wParam == (WPARAM)IDC_SPIN2)
		{
			LPNMUPDOWN lpnmud = (LPNMUPDOWN)lParam;
			if (lpnmud->hdr.code == UDN_DELTAPOS)
			{
				char str[4096] = {};
				GetWindowText(
					(HWND)GetDlgItem(hDlg, IDC_EDIT3),		// スライダーのハンドル
					str, 4096);
				double positionX = atof(str);
				if ((lpnmud->iDelta) < 0)
				{
					positionX += 1.f;
				}
				else if ((lpnmud->iDelta) > 0)
				{
					positionX -= 1.f;
				}
				sprintf(str, "%.3f", positionX);
				SetDlgItemText(hDlg, IDC_EDIT3, (LPCTSTR)str);
			}
		}
		if (wParam == (WPARAM)IDC_SPIN3)
		{
			LPNMUPDOWN lpnmud = (LPNMUPDOWN)lParam;
			if (lpnmud->hdr.code == UDN_DELTAPOS)
			{
				char str[4096] = {};
				GetWindowText(
					(HWND)GetDlgItem(hDlg, IDC_EDIT4),		// スライダーのハンドル
					str, 4096);
				double positionX = atof(str);
				if ((lpnmud->iDelta) < 0)
				{
					positionX += 1.f;
				}
				else if ((lpnmud->iDelta) > 0)
				{
					positionX -= 1.f;
				}
				sprintf(str, "%.3f", positionX);
				SetDlgItemText(hDlg, IDC_EDIT4, (LPCTSTR)str);
			}
		}

		if (wParam == (WPARAM)IDC_SPIN11)
		{
			LPNMUPDOWN lpnmud = (LPNMUPDOWN)lParam;
			if (lpnmud->hdr.code == UDN_DELTAPOS)
			{
				char str[4096] = {};
				GetWindowText(
					(HWND)GetDlgItem(hDlg, IDC_EDIT11),		// スライダーのハンドル
					str, 4096);
				double positionX = atof(str);
				if ((lpnmud->iDelta) < 0)
				{
					positionX += 0.01f;
				}
				else if ((lpnmud->iDelta) > 0)
				{
					positionX -= 0.01f;
				}
				sprintf(str, "%.3f", positionX);
				SetDlgItemText(hDlg, IDC_EDIT11, (LPCTSTR)str);
			}
		}
		break;

	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return TRUE;

	default:
		break;
	}

	return FALSE;
}

// 読み込み関数
void ReadRouteFile(HWND hWnd)
{
	OPENFILENAME ofn = {};
	TCHAR szPath[MAX_PATH] = { 0 };
	TCHAR szFile[MAX_PATH] = {};

	if (szPath[0] == TEXT('\0')) {
		GetCurrentDirectory(MAX_PATH, szPath);
	}
	if (ofn.lStructSize == 0) {
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = hWnd;
		ofn.lpstrInitialDir = szPath;	// 初期フォルダ位置
		ofn.lpstrFile = szFile;			// 選択ファイル格納
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrDefExt = TEXT(".rt");
		ofn.lpstrFilter = TEXT("ルートファイル(*.rt)\0*.rt\0");
		ofn.lpstrTitle = TEXT("開く");
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	}

	if (GetSaveFileName(&ofn)) {
		FILE *file = nullptr;
		file = fopen(szFile, "rt");
		if (file) {

			// 現在の状況破棄
			HWND hCombo = GetDlgItem(g_routeDialogHandle, IDC_COMBO4);
			SendMessage((HWND)hCombo, (UINT)CB_RESETCONTENT, 0, 0);
			hCombo = GetDlgItem(g_routeDialogHandle, IDC_COMBO2);
			SendMessage((HWND)hCombo, (UINT)CB_RESETCONTENT, 0, 0);
			Manager::GetInstance()->GetRouteManager()->AllDeletePoint();

			// 読み込み
			Manager::GetInstance()->GetRouteManager()->InputData(file);

			fclose(file);
		}
		else {
			MessageBox(g_windowHandle, "読み込みに失敗しました", "警告", MB_OK);
		}
	}
}

// 保存関数
void SaveRouteFile(HWND hWnd)
{
	OPENFILENAME ofn = {};
	TCHAR szPath[MAX_PATH] = { 0 };
	TCHAR szFile[MAX_PATH] = {};

	if (szPath[0] == TEXT('\0')) {
		GetCurrentDirectory(MAX_PATH, szPath);
	}
	if (ofn.lStructSize == 0) {
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = hWnd;
		ofn.lpstrInitialDir = szPath;	// 初期フォルダ位置
		ofn.lpstrFile = szFile;			// 選択ファイル格納
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrDefExt = TEXT(".rt");
		ofn.lpstrFilter = TEXT("ルートファイル(*.rt)\0*.rt\0");
		ofn.lpstrTitle = TEXT("名前を付けて保存");
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;
	}

	if (GetSaveFileName(&ofn)) {
		FILE *file = nullptr;
		file = fopen(szFile, "wt");

		if (file) {
			Manager::GetInstance()->GetRouteManager()->OutputData(file);
			fclose(file);
		}
		else {
			MessageBox(g_windowHandle, "保存に失敗しました", "警告", MB_OK);
		}
	}
}






// ダイアログプロシージャ
BOOL CALLBACK DirtDlgProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg) {

		// ダイアログ初期化
	case WM_INITDIALOG:
	{

		// スピンコントロールとエディットボックスの関連付け
		SendMessage(
			(HWND)GetDlgItem(hDlg, IDC_SPIN1),		// スピンコントロールのハンドル
			(UINT)UDM_SETBUDDY,
			(WPARAM)GetDlgItem(hDlg, IDC_EDIT2),	// 関連付けるコントロールのハンドル
			0										// 0固定
			);
		SendMessage(
			(HWND)GetDlgItem(hDlg, IDC_SPIN2),		// スピンコントロールのハンドル
			(UINT)UDM_SETBUDDY,
			(WPARAM)GetDlgItem(hDlg, IDC_EDIT3),	// 関連付けるコントロールのハンドル
			0										// 0固定
			);
		SendMessage(
			(HWND)GetDlgItem(hDlg, IDC_SPIN3),		// スピンコントロールのハンドル
			(UINT)UDM_SETBUDDY,
			(WPARAM)GetDlgItem(hDlg, IDC_EDIT4),	// 関連付けるコントロールのハンドル
			0										// 0固定
			);

		SendMessage(
			(HWND)GetDlgItem(hDlg, IDC_SPIN7),		// スピンコントロールのハンドル
			(UINT)UDM_SETBUDDY,
			(WPARAM)GetDlgItem(hDlg, IDC_EDIT5),	// 関連付けるコントロールのハンドル
			0										// 0固定
			);

		// モードの設定
		HWND radio = GetDlgItem(hDlg, IDC_RADIO6);
		SendMessage(
			(HWND)radio,		// ラジオボタンのハンドル
			(UINT)BM_SETCHECK,
			(WPARAM)BST_CHECKED,
			0					// ０固定
			);
	}
		return TRUE;

		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			return TRUE;

		case IDCANCEL:
			return TRUE;

		// 汚れの選択
		case IDC_COMBO1:

			// 選択したとき
			if (HIWORD(wParam) == CBN_SELCHANGE) {
				// コンボボックスから生成するモデルのファイル名取得
				HWND hCombo1 = GetDlgItem(hDlg, IDC_COMBO1);
				int index = SendMessage(
					(HWND)hCombo1,			// コンボボックスのハンドル
					(UINT)CB_GETCURSEL,		// 選択中のインデックス取得
					0,						// ０固定
					0						// 追加する項目の文字列
					);

				// 選択中の点変更
				Manager::GetInstance()->GetDirtManager()->SetDirtListCursor(index);


				D3DXVECTOR3 position = Manager::GetInstance()->GetDirtManager()->GetPosition();
				float radius = Manager::GetInstance()->GetDirtManager()->GetRadius();
				// 座標エディットボックス
				char str[4096] = {};
				sprintf(str, "%.3f", position.x);
				SetWindowText(
					(HWND)GetDlgItem(g_dirtDialogHandle, IDC_EDIT2),		// スライダーのハンドル
					str		// 追加する項目の文字列
					);

				sprintf(str, "%.3f", position.y);
				SetWindowText(
					(HWND)GetDlgItem(g_dirtDialogHandle, IDC_EDIT3),		// スライダーのハンドル
					str		// 追加する項目の文字列
					);

				sprintf(str, "%.3f", position.z);
				SetWindowText(
					(HWND)GetDlgItem(g_dirtDialogHandle, IDC_EDIT4),		// スライダーのハンドル
					str		// 追加する項目の文字列
					);

				sprintf(str, "%.3f", radius);
				SetWindowText(
					(HWND)GetDlgItem(g_dirtDialogHandle, IDC_EDIT5),		// スライダーのハンドル
					str		// 追加する項目の文字列
					);
			}
			break;


		// 点の生成もしくは削除
		case IDC_BUTTON1:
		{
			HWND radio1 = GetDlgItem(hDlg, IDC_RADIO6);
			HWND radio3 = GetDlgItem(hDlg, IDC_RADIO8);

			// 生成 : 追加
			if (SendMessage(radio1, BM_GETCHECK, 0, 0) == 1) {
				Manager::GetInstance()->GetDirtManager()->CreateDirt();
			}
			// 削除
			if (SendMessage(radio3, BM_GETCHECK, 0, 0) == 1) {
				Manager::GetInstance()->GetDirtManager()->DeleteDirt();
			}
		}
			break;


		// 座標 : X軸
		case IDC_EDIT2:
			if (HIWORD(wParam) == EN_UPDATE) {
				char str[4096] = {};
				GetWindowText(
					(HWND)GetDlgItem(g_dirtDialogHandle, IDC_EDIT2),		// スライダーのハンドル
					str, 4096);
				double positionX = atof(str);
				Manager::GetInstance()->GetDirtManager()->SetPositionX((float)positionX);
			}
			break;

			// 座標 : Y軸
		case IDC_EDIT3:
			if (HIWORD(wParam) == EN_UPDATE) {
				char str[4096] = {};
				GetWindowText(
					(HWND)GetDlgItem(g_dirtDialogHandle, IDC_EDIT3),		// スライダーのハンドル
					str, 4096);
				double positionY = atof(str);
				Manager::GetInstance()->GetDirtManager()->SetPositionY((float)positionY);
			}
			break;

			// 座標 : Z軸
		case IDC_EDIT4:
			if (HIWORD(wParam) == EN_UPDATE) {
				char str[4096] = {};
				GetWindowText(
					(HWND)GetDlgItem(g_dirtDialogHandle, IDC_EDIT4),		// スライダーのハンドル
					str, 4096);
				double positionZ = atof(str);
				Manager::GetInstance()->GetDirtManager()->SetPositionZ((float)positionZ);
			}
			break;


			// 半径
		case IDC_EDIT5:
			if (HIWORD(wParam) == EN_UPDATE) {
				char str[4096] = {};
				GetWindowText(
					(HWND)GetDlgItem(g_dirtDialogHandle, IDC_EDIT5),		// スライダーのハンドル
					str, 4096);
				double radius = atof(str);
				Manager::GetInstance()->GetDirtManager()->SetRadius((float)radius);
			}
			break;


		default:
			break;
		}
		break;


	case WM_NOTIFY:
		if (wParam == (WPARAM)IDC_SPIN1)
		{
			LPNMUPDOWN lpnmud = (LPNMUPDOWN)lParam;
			if (lpnmud->hdr.code == UDN_DELTAPOS)
			{
				char str[4096] = {};
				GetWindowText(
					(HWND)GetDlgItem(hDlg, IDC_EDIT2),		// スライダーのハンドル
					str, 4096);
				double positionX = atof(str);
				if ((lpnmud->iDelta) < 0)
				{
					positionX += 1.f;
				}
				else if ((lpnmud->iDelta) > 0)
				{
					positionX -= 1.f;
				}
				sprintf(str, "%.3f", positionX);
				SetDlgItemText(hDlg, IDC_EDIT2, (LPCTSTR)str);
			}
		}
		if (wParam == (WPARAM)IDC_SPIN2)
		{
			LPNMUPDOWN lpnmud = (LPNMUPDOWN)lParam;
			if (lpnmud->hdr.code == UDN_DELTAPOS)
			{
				char str[4096] = {};
				GetWindowText(
					(HWND)GetDlgItem(hDlg, IDC_EDIT3),		// スライダーのハンドル
					str, 4096);
				double positionX = atof(str);
				if ((lpnmud->iDelta) < 0)
				{
					positionX += 1.f;
				}
				else if ((lpnmud->iDelta) > 0)
				{
					positionX -= 1.f;
				}
				sprintf(str, "%.3f", positionX);
				SetDlgItemText(hDlg, IDC_EDIT3, (LPCTSTR)str);
			}
		}
		if (wParam == (WPARAM)IDC_SPIN3)
		{
			LPNMUPDOWN lpnmud = (LPNMUPDOWN)lParam;
			if (lpnmud->hdr.code == UDN_DELTAPOS)
			{
				char str[4096] = {};
				GetWindowText(
					(HWND)GetDlgItem(hDlg, IDC_EDIT4),		// スライダーのハンドル
					str, 4096);
				double positionX = atof(str);
				if ((lpnmud->iDelta) < 0)
				{
					positionX += 1.f;
				}
				else if ((lpnmud->iDelta) > 0)
				{
					positionX -= 1.f;
				}
				sprintf(str, "%.3f", positionX);
				SetDlgItemText(hDlg, IDC_EDIT4, (LPCTSTR)str);
			}
		}

		if (wParam == (WPARAM)IDC_SPIN7)
		{
			LPNMUPDOWN lpnmud = (LPNMUPDOWN)lParam;
			if (lpnmud->hdr.code == UDN_DELTAPOS)
			{
				char str[4096] = {};
				GetWindowText(
					(HWND)GetDlgItem(hDlg, IDC_EDIT5),		// スライダーのハンドル
					str, 4096);
				double positionX = atof(str);
				if ((lpnmud->iDelta) < 0)
				{
					positionX += 1.f;
				}
				else if ((lpnmud->iDelta) > 0)
				{
					positionX -= 1.f;
				}
				sprintf(str, "%.3f", positionX);
				SetDlgItemText(hDlg, IDC_EDIT5, (LPCTSTR)str);
			}
		}
		break;

	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return TRUE;

	default:
		break;
	}

	return FALSE;
}

// 読み込み関数
void ReadDirtFile(HWND hWnd)
{
	OPENFILENAME ofn = {};
	TCHAR szPath[MAX_PATH] = { 0 };
	TCHAR szFile[MAX_PATH] = {};

	if (szPath[0] == TEXT('\0')) {
		GetCurrentDirectory(MAX_PATH, szPath);
	}
	if (ofn.lStructSize == 0) {
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = hWnd;
		ofn.lpstrInitialDir = szPath;	// 初期フォルダ位置
		ofn.lpstrFile = szFile;			// 選択ファイル格納
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrDefExt = TEXT(".drt");
		ofn.lpstrFilter = TEXT("汚れファイル(*.drt)\0*.drt\0");
		ofn.lpstrTitle = TEXT("開く");
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	}

	if (GetSaveFileName(&ofn)) {
		FILE *file = nullptr;
		file = fopen(szFile, "rt");
		if (file) {

			// 現在の状況破棄
			HWND hCombo = GetDlgItem(g_dirtDialogHandle, IDC_COMBO1);
			SendMessage((HWND)hCombo, (UINT)CB_RESETCONTENT, 0, 0);
			Manager::GetInstance()->GetDirtManager()->AllDeleteDirt();

			// 読み込み
			Manager::GetInstance()->GetDirtManager()->InputData(file);

			fclose(file);
		}
		else {
			MessageBox(g_windowHandle, "読み込みに失敗しました", "警告", MB_OK);
		}
	}
}

// 保存関数
void SaveDirtFile(HWND hWnd)
{
	OPENFILENAME ofn = {};
	TCHAR szPath[MAX_PATH] = { 0 };
	TCHAR szFile[MAX_PATH] = {};

	if (szPath[0] == TEXT('\0')) {
		GetCurrentDirectory(MAX_PATH, szPath);
	}
	if (ofn.lStructSize == 0) {
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = hWnd;
		ofn.lpstrInitialDir = szPath;	// 初期フォルダ位置
		ofn.lpstrFile = szFile;			// 選択ファイル格納
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrDefExt = TEXT(".drt");
		ofn.lpstrFilter = TEXT("汚れファイル(*.drt)\0*.drt\0");
		ofn.lpstrTitle = TEXT("名前を付けて保存");
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;
	}

	if (GetSaveFileName(&ofn)) {
		FILE *file = nullptr;
		file = fopen(szFile, "wt");
		if (file) {
			Manager::GetInstance()->GetDirtManager()->OutputData(file);
			fclose(file);
		}
		else {
			MessageBox(g_windowHandle, "保存に失敗しました", "警告", MB_OK);
		}
	}
}



HWND GetObjectDialogHandle()
{
	return g_objectDialogHandle;
}

HWND GetRouteDialogHandle()
{
	return g_routeDialogHandle;
}

HWND GetDirtDialogHandle()
{
	return g_dirtDialogHandle;
}

MODE GetMode()
{
	return g_mode;
}


// End of file