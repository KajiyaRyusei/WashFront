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
BOOL CALLBACK DlgProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam);

// ファイルの読み込み
void ImportFile(HWND windowHandle);

// モデルの生成
void CreateModel(HWND hDlg);

// 左クリック時のイベント
void ClickLeftEvent();

// 読み込み関数
void ReadMapFile(HWND hWnd);

// 保存関数
void SaveMapFile(HWND hWnd);



//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
HWND g_windowHandle = nullptr;
HWND g_dialogHandle = nullptr;

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
	g_dialogHandle = CreateDialog(instance, MAKEINTRESOURCE(IDD_DIALOG1),
		g_windowHandle, DlgProc);
	ShowWindow(g_dialogHandle, cmd_show);
	UpdateWindow(g_dialogHandle);


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
			ImportFile(wnd);
			break;


		// 名前をつけて保存
		case ID_40006:
			// 保存
			SaveMapFile(wnd);
			break;

		default:
			break;
		}


	// マウス左クリック時
	case WM_LBUTTONDOWN:
	{
		ClickLeftEvent();
		break;
	}

	default:
		break;
	}

	return DefWindowProc(wnd, msg, w_param, l_param);
}


//=============================================================================
// ダイアログプロシージャ
//=============================================================================
BOOL CALLBACK DlgProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg) {

	// ダイアログ初期化
	case WM_INITDIALOG:

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

		// 座標 : X軸
		case IDC_EDIT2:
			if (HIWORD(wParam) == EN_UPDATE) {

				Building *building = Manager::GetInstance()->GetObjectManager()->GetSelectBuilding();
				if (building) {
					char str[4096] = {};
					GetWindowText(
						(HWND)GetDlgItem(g_dialogHandle, IDC_EDIT2),		// スライダーのハンドル
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
						(HWND)GetDlgItem(g_dialogHandle, IDC_EDIT3),		// スライダーのハンドル
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
						(HWND)GetDlgItem(g_dialogHandle, IDC_EDIT4),		// スライダーのハンドル
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
						(HWND)GetDlgItem(g_dialogHandle, IDC_EDIT5),		// スライダーのハンドル
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
						(HWND)GetDlgItem(g_dialogHandle, IDC_EDIT6),		// スライダーのハンドル
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
						(HWND)GetDlgItem(g_dialogHandle, IDC_EDIT7),		// スライダーのハンドル
						str, 4096);
					double scaleZ = atof(str);
					building->SetScaleZ((float)scaleZ);
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

	// コンボボックスにファイル名追加
	case WM_NULL:
	{
		
		const char *fileName = Manager::GetInstance()->GetImportFileManager()->GetFileName(g_szFile);

		HWND hCombo = GetDlgItem(hDlg, IDC_COMBO1);

		SendMessage(
			(HWND)hCombo,			// コンボボックスのハンドル
			(UINT)CB_ADDSTRING,		// 項目の追加
			0,						// ０固定
			(LPARAM)fileName		// 追加する項目の文字列
			);
		break;
	}

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
// ファイルの読み込み
//=============================================================================
void ImportFile(HWND windowHandle)
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
		ofn.lpstrFilter = "モデルデータ(*.x)\0*.x";
		ofn.lpstrTitle = "モデルのインポート";
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	}

	// ダイアログ表示
	if (GetOpenFileName(&ofn)) {

		// モデルファイルの読み込み
		if (!Manager::GetInstance()->GetImportFileManager()->ImportFile(g_szFile))
			MessageBox(g_windowHandle, "すでに読み込まれています", "警告", MB_OK);
		else
			SendMessage(g_dialogHandle, WM_NULL, 0, 0);
	}
}

// モデルの生成
void CreateModel(HWND hDlg)
{

	// コンボボックスから生成するモデルのファイル名取得
	HWND hCombo = GetDlgItem(hDlg, IDC_COMBO1);
	int index = SendMessage(
		(HWND)hCombo,			// コンボボックスのハンドル
		(UINT)CB_GETCURSEL,		// 選択中のインデックス取得
		0,						// ０固定
		0						// 追加する項目の文字列
		);


	// ファイル名の取得
	int intTxtLen = SendMessage(hCombo, CB_GETLBTEXTLEN, index, 0);
	if (intTxtLen != CB_ERR)
	{
		char* pszBuf = new char[intTxtLen + 1];
		if (SendMessage(hCombo, CB_GETLBTEXT, index, (LPARAM)pszBuf) != CB_ERR)
		{
			// モデルの生成
			Manager::GetInstance()->GetObjectManager()->CreateBuilding(
				Manager::GetInstance()->GetImportFileManager()->GetFilePath(pszBuf));
		}
		delete[] pszBuf;
	}

}


// 左クリック時のイベント
void ClickLeftEvent()
{
	// マウスとオブジェクトの衝突判定
	Manager::GetInstance()->GetObjectManager()->CheckCollisionMouseAndObject();


	// スライダーを選択中のオブジェクトの座標に合わせる
	Building *building = Manager::GetInstance()->GetObjectManager()->GetSelectBuilding();
	if (building) {
		D3DXVECTOR3 position = building->GetPosition();
		D3DXVECTOR3 rotation = building->GetRotation();
		D3DXVECTOR3 scale = building->GetScale();


		// 向きスライダー
		SendMessage(
			(HWND)GetDlgItem(g_dialogHandle, IDC_SLIDER5),	// スライダーのハンドル
			(UINT)TBM_SETPOS,								// 座標の取得(0～100)
			(WPARAM)TRUE,									// ０固定
			(LPARAM)((rotation.x + D3DX_PI) / (D3DX_PI * 2) * 100)			// 追加する項目の文字列
			);
		SendMessage(
			(HWND)GetDlgItem(g_dialogHandle, IDC_SLIDER6),	// スライダーのハンドル
			(UINT)TBM_SETPOS,								// 座標の取得(0～100)
			(WPARAM)TRUE,									// ０固定
			(LPARAM)((rotation.y + D3DX_PI) / (D3DX_PI * 2) * 100)			// 追加する項目の文字列
			);
		SendMessage(
			(HWND)GetDlgItem(g_dialogHandle, IDC_SLIDER7),	// スライダーのハンドル
			(UINT)TBM_SETPOS,								// 座標の取得(0～100)
			(WPARAM)TRUE,									// ０固定
			(LPARAM)((rotation.z + D3DX_PI) / (D3DX_PI * 2) * 100)			// 追加する項目の文字列
			);



		// 座標エディットボックス
		char str[4096] = {};
		sprintf(str, "%.1f", position.x);
		SetWindowText(
			(HWND)GetDlgItem(g_dialogHandle, IDC_EDIT2),		// スライダーのハンドル
			str		// 追加する項目の文字列
			);

		sprintf(str, "%.1f", position.y);
		SetWindowText(
			(HWND)GetDlgItem(g_dialogHandle, IDC_EDIT3),		// スライダーのハンドル
			str		// 追加する項目の文字列
			);

		sprintf(str, "%.1f", position.z);
		SetWindowText(
			(HWND)GetDlgItem(g_dialogHandle, IDC_EDIT4),		// スライダーのハンドル
			str		// 追加する項目の文字列
			);



		// スケールエディットボックス
		sprintf(str, "%.1f", scale.x);
		SetWindowText(
			(HWND)GetDlgItem(g_dialogHandle, IDC_EDIT5),		// スライダーのハンドル
			str		// 追加する項目の文字列
			);

		sprintf(str, "%.1f", scale.y);
		SetWindowText(
			(HWND)GetDlgItem(g_dialogHandle, IDC_EDIT6),		// スライダーのハンドル
			str		// 追加する項目の文字列
			);

		sprintf(str, "%.1f", scale.z);
		SetWindowText(
			(HWND)GetDlgItem(g_dialogHandle, IDC_EDIT7),		// スライダーのハンドル
			str		// 追加する項目の文字列
			);

	}
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
			HWND hCombo = GetDlgItem(g_dialogHandle, IDC_COMBO1);
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

HWND GetDialogHandle()
{
	return g_dialogHandle;
}


// End of file