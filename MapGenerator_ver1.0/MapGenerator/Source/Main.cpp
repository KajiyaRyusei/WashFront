//=============================================================================
//
// ���C������ [Main.cpp]
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
// �}�N����`
//-----------------------------------------------------------------------------
#define CLASS_NAME		("AppClass")				// �E�C���h�E�̃N���X��
#define WINDOW_NAME		("MAP GENERATOR")			// �E�C���h�E�̃L���v�V������
#define ICON_PATH		("")	// exe�A�C�R��


//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM w_param, LPARAM l_param);

// �_�C�A���O�v���V�[�W��
BOOL CALLBACK ObjectDlgProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam);

// �_�C�A���O�v���V�[�W��
BOOL CALLBACK RouteDlgProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam);

// �_�C�A���O�v���V�[�W��
BOOL CALLBACK DirtDlgProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam);

// ���f���t�@�C���̓ǂݍ���
void ImportModelFile(HWND windowHandle);

// �e�N�X�`���t�@�C���̓ǂݍ���
void ImportTextureFile(HWND windowHandle);

// ���f���̐���
void CreateModel(HWND hDlg);

// ���N���b�N���̃C�x���g
void ClickLeftEventObjectMode();
void ClickLeftEventRouteMode();
void ClickLeftEventDirtMode();

// �ǂݍ��݊֐�
void ReadMapFile(HWND hWnd);

// �ۑ��֐�
void SaveMapFile(HWND hWnd);

// �ǂݍ��݊֐�
void ReadRouteFile(HWND hWnd);

// �ۑ��֐�
void SaveRouteFile(HWND hWnd);

// �ǂݍ��݊֐�
void ReadDirtFile(HWND hWnd);

// �ۑ��֐�
void SaveDirtFile(HWND hWnd);


//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
HWND g_windowHandle = nullptr;
HWND g_objectDialogHandle = nullptr;
HWND g_routeDialogHandle = nullptr;
HWND g_dirtDialogHandle = nullptr;

MODE g_mode = MODE_OBJECT;

TCHAR g_szFile[MAX_PATH] = {};


#ifdef _DEBUG
float g_fps_count;  // FPS�J�E���^
#endif


//=============================================================================
// �G���g���|�C���g
//=============================================================================
int APIENTRY WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR cmd_line, int cmd_show)
{
	UNREFERENCED_PARAMETER(prev_instance);  // �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(cmd_line);  // �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	// �v���O�����I�������������[�N���o
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

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
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


	// �O���t�B�b�N���̏�����
	bool window = true;
#ifdef _RELEASE
	if (IDYES == MessageBox(g_windowHandle, "�t���X�N���[���Ŏ��s���܂����H", "��ʃ��[�h", MB_YESNO)) {
		window = false;
	}
#endif




	// ����������(�E�B���h�E���쐬���Ă���s��)
	if (FAILED(Manager::GetInstance()->Init(instance, g_windowHandle, window))) {
		return -1;
	}

	//�t���[���J�E���g������
	timeBeginPeriod(1);  // ����\��ݒ�
	dwExecLastTime =
	dwFPSLastTime = timeGetTime();
	dwCurrentTime =
	dwFrameCount = 0;


	// �E�C���h�E�̕\��(�����������̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(g_windowHandle, cmd_show);
	UpdateWindow(g_windowHandle);



	// �_�C�A���O�̍쐬
	g_objectDialogHandle = CreateDialog(instance, MAKEINTRESOURCE(IDD_DIALOG1),
		g_windowHandle, ObjectDlgProc);
	ShowWindow(g_objectDialogHandle, cmd_show);
	UpdateWindow(g_objectDialogHandle);


	// �_�C�A���O�̍쐬
	g_routeDialogHandle = CreateDialog(instance, MAKEINTRESOURCE(IDD_DIALOG2),
		g_windowHandle, RouteDlgProc);
	//ShowWindow(g_routeDialogHandle, cmd_show);
	UpdateWindow(g_routeDialogHandle);


	// �_�C�A���O�̍쐬
	g_dirtDialogHandle = CreateDialog(instance, MAKEINTRESOURCE(IDD_DIALOG3),
		g_windowHandle, DirtDlgProc);
	//ShowWindow(g_dirtDialogHandle, cmd_show);
	UpdateWindow(g_dirtDialogHandle);



	// ���b�Z�[�W���[�v
	while (1) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {  // PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			} else {
				// ���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		} else {
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500) {  // 0.5�b���ƂɎ��s
#ifdef _DEBUG
				g_fps_count = dwFrameCount * 1000.0f / (dwCurrentTime - dwFPSLastTime);
#endif
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60)) {
			dwExecLastTime = dwCurrentTime;

				// �X�V����
				Manager::GetInstance()->Update();

				// �`�揈��
				Manager::GetInstance()->Draw();

				dwFrameCount++;
			}
		}
	}

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
	Manager::Destory();

	timeEndPeriod(1);  // ����\��߂�


	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CLOSE:
		if (IDYES == MessageBox(g_windowHandle, "�I�����܂����H", "�v���O�����̏I��", MB_YESNO))
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

		// �J��
		case ID_40001:
			// �t�@�C���̓ǂݍ���
			if (IDYES == MessageBox(g_windowHandle, "���݂̕ҏW���͔j������܂�����낵���ł���", "�x��", MB_YESNO))
				ReadMapFile(wnd);
			break;

		// �I��
		case ID_40002:
			if (IDYES == MessageBox(g_windowHandle, "�I�����܂����H", "�v���O�����̏I��", MB_YESNO))
				DestroyWindow(wnd);
			break;


		// ���f���̃C���|�[�g
		case ID_40003:
			// ���f���t�@�C���ǂݍ���
			ImportModelFile(wnd);
			break;

			// �e�N�X�`���̃C���|�[�g
		case ID_40007:
			// �e�N�X�`���t�@�C���ǂݍ���
			ImportTextureFile(wnd);
			break;

		// ���O�����ĕۑ�
		case ID_40006:
			// �ۑ�
			SaveMapFile(wnd);
			break;

		// ���[�g�̕ۑ�
		case ID_40008:
			SaveRouteFile(wnd);
			break;

			// ���[�g�̓ǂݍ���
		case ID_40009:
			if (IDYES == MessageBox(g_windowHandle, "���݂̕ҏW���͔j������܂�����낵���ł���", "�x��", MB_YESNO))
				ReadRouteFile(wnd);
			break;

			// ����̕ۑ�
		case ID_40010:
			SaveDirtFile(wnd);
			break;

			// ����̓ǂݍ���
		case ID_40011:
			if (IDYES == MessageBox(g_windowHandle, "���݂̕ҏW���͔j������܂�����낵���ł���", "�x��", MB_YESNO))
				ReadDirtFile(wnd);
			break;


			// �I�u�W�F�N�g
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
			// ���[�g
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
			// ����
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


		// �}�E�X���N���b�N��
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
// �_�C�A���O�v���V�[�W��
//=============================================================================
BOOL CALLBACK ObjectDlgProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg) {

		// �_�C�A���O������
	case WM_INITDIALOG:
	{
		// �X�s���R���g���[���ƃG�f�B�b�g�{�b�N�X�̊֘A�t��

		SendMessage(
			(HWND)GetDlgItem(hDlg, IDC_SPIN1),		// �X�s���R���g���[���̃n���h��
			(UINT)UDM_SETBUDDY,
			(WPARAM)GetDlgItem(hDlg, IDC_EDIT2),	// �֘A�t����R���g���[���̃n���h��
			0										// 0�Œ�
			);
		SendMessage(
			(HWND)GetDlgItem(hDlg, IDC_SPIN2),		// �X�s���R���g���[���̃n���h��
			(UINT)UDM_SETBUDDY,
			(WPARAM)GetDlgItem(hDlg, IDC_EDIT3),	// �֘A�t����R���g���[���̃n���h��
			0										// 0�Œ�
			);
		SendMessage(
			(HWND)GetDlgItem(hDlg, IDC_SPIN3),		// �X�s���R���g���[���̃n���h��
			(UINT)UDM_SETBUDDY,
			(WPARAM)GetDlgItem(hDlg, IDC_EDIT4),	// �֘A�t����R���g���[���̃n���h��
			0										// 0�Œ�
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


		// ���f���̐���
		case IDC_BUTTON1:
			CreateModel(hDlg);
			break;

		// �R�s�[
		case IDC_BUTTON2:
			Manager::GetInstance()->GetObjectManager()->CopyBuilding();
			break;

		// ���W : X��
		case IDC_EDIT2:
			if (HIWORD(wParam) == EN_UPDATE) {

				Building *building = Manager::GetInstance()->GetObjectManager()->GetSelectBuilding();
				if (building) {
					char str[4096] = {};
					GetWindowText(
						(HWND)GetDlgItem(g_objectDialogHandle, IDC_EDIT2),		// �X���C�_�[�̃n���h��
						str, 4096);
					double positionX = atof(str);
					building->SetPositionX((float)positionX);
				}
			}
			break;

		// ���W : Y��
		case IDC_EDIT3:
			if (HIWORD(wParam) == EN_UPDATE) {

				Building *building = Manager::GetInstance()->GetObjectManager()->GetSelectBuilding();
				if (building) {
					char str[4096] = {};
					GetWindowText(
						(HWND)GetDlgItem(g_objectDialogHandle, IDC_EDIT3),		// �X���C�_�[�̃n���h��
						str, 4096);
					double positionY = atof(str);
					building->SetPositionY((float)positionY);
				}
			}
			break;

		// ���W : Z��
		case IDC_EDIT4:
			if (HIWORD(wParam) == EN_UPDATE) {

				Building *building = Manager::GetInstance()->GetObjectManager()->GetSelectBuilding();
				if (building) {
					char str[4096] = {};
					GetWindowText(
						(HWND)GetDlgItem(g_objectDialogHandle, IDC_EDIT4),		// �X���C�_�[�̃n���h��
						str, 4096);
					double positionZ = atof(str);
					building->SetPositionZ((float)positionZ);
				}
			}
			break;


		// �X�P�[�� : X��
		case IDC_EDIT5:
			if (HIWORD(wParam) == EN_UPDATE) {

				Building *building = Manager::GetInstance()->GetObjectManager()->GetSelectBuilding();
				if (building) {
					char str[4096] = {};
					GetWindowText(
						(HWND)GetDlgItem(g_objectDialogHandle, IDC_EDIT5),		// �X���C�_�[�̃n���h��
						str, 4096);
					double scaleX = atof(str);
					building->SetScaleX((float)scaleX);
				}
			}
			break;

		// �X�P�[�� : Y��
		case IDC_EDIT6:
			if (HIWORD(wParam) == EN_UPDATE) {

				Building *building = Manager::GetInstance()->GetObjectManager()->GetSelectBuilding();
				if (building) {
					char str[4096] = {};
					GetWindowText(
						(HWND)GetDlgItem(g_objectDialogHandle, IDC_EDIT6),		// �X���C�_�[�̃n���h��
						str, 4096);
					double scaleY = atof(str);
					building->SetScaleY((float)scaleY);
				}
			}
			break;

			// �X�P�[�� : X��
		case IDC_EDIT7:
			if (HIWORD(wParam) == EN_UPDATE) {

				Building *building = Manager::GetInstance()->GetObjectManager()->GetSelectBuilding();
				if (building) {
					char str[4096] = {};
					GetWindowText(
						(HWND)GetDlgItem(g_objectDialogHandle, IDC_EDIT7),		// �X���C�_�[�̃n���h��
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


	// �����X���C�_�[�̒l���擾
	case WM_HSCROLL:
	{
		
		Building *building = Manager::GetInstance()->GetObjectManager()->GetSelectBuilding();
		if (building) {

			float position = (float)SendMessage(
				(HWND)lParam,			// �X���C�_�[�̃n���h��
				(UINT)TBM_GETPOS,		// ���W�̎擾(0�`100)
				0,						// �O�Œ�
				0						// �ǉ����鍀�ڂ̕�����
				);

			// ���� : X���X���C�_�[
			if ((HWND)lParam == GetDlgItem(hDlg, IDC_SLIDER5)) {
				building->SetRotationX((position / 100 - 0.5f) * D3DX_PI * 2);
			}
			// ���� : Y���X���C�_�[
			if ((HWND)lParam == GetDlgItem(hDlg, IDC_SLIDER6)) {
				building->SetRotationY((position / 100 - 0.5f) * D3DX_PI * 2);
			}
			// ���� : Z���X���C�_�[
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
					(HWND)GetDlgItem(hDlg, IDC_EDIT2),		// �X���C�_�[�̃n���h��
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
					(HWND)GetDlgItem(hDlg, IDC_EDIT3),		// �X���C�_�[�̃n���h��
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
					(HWND)GetDlgItem(hDlg, IDC_EDIT4),		// �X���C�_�[�̃n���h��
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
					(HWND)GetDlgItem(hDlg, IDC_EDIT5),		// �X���C�_�[�̃n���h��
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
					(HWND)GetDlgItem(hDlg, IDC_EDIT6),		// �X���C�_�[�̃n���h��
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
					(HWND)GetDlgItem(hDlg, IDC_EDIT7),		// �X���C�_�[�̃n���h��
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
// Window�n���h���̎擾
//=============================================================================
HWND GetWindowHandle()
{
	return g_windowHandle;
}


#ifdef _DEBUG
//=============================================================================
// FPS�J�E���^�̎擾
//=============================================================================
float GetFps()
{
	return g_fps_count;
}
#endif



//=============================================================================
// ���f���t�@�C���̓ǂݍ���
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

	// �_�C�A���O�̏��
	if (ofn.lStructSize == 0) {
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = windowHandle;
		ofn.lpstrInitialDir = szPath;	// �����t�H���_�ʒu
		ofn.lpstrFile = g_szFile;		// �I���t�@�C���i�[
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrFilter = "���f���f�[�^(*.fbx)\0*.fbx";
		ofn.lpstrTitle = "���f���̃C���|�[�g";
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	}

	// �_�C�A���O�\��
	if (GetOpenFileName(&ofn)) {

		// ���f���t�@�C���̓ǂݍ���
		if (!Manager::GetInstance()->GetImportFileManager()->ImportFile(g_szFile))
			MessageBox(g_windowHandle, "���łɓǂݍ��܂�Ă��܂�", "�x��", MB_OK);
		else
			SendMessage(g_objectDialogHandle, WM_NULL, 0, 0);
	}
}

//=============================================================================
// �e�N�X�`���t�@�C���̓ǂݍ���
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

	// �_�C�A���O�̏��
	if (ofn.lStructSize == 0) {
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = windowHandle;
		ofn.lpstrInitialDir = szPath;	// �����t�H���_�ʒu
		ofn.lpstrFile = g_szFile;		// �I���t�@�C���i�[
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrFilter = "JPEG(*.jpg)\0*.jpg\0PNG(*.png)\0*.png";
		ofn.lpstrTitle = "�e�N�X�`���̃C���|�[�g";
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	}

	// �_�C�A���O�\��
	if (GetOpenFileName(&ofn)) {

		// ���f���t�@�C���̓ǂݍ���
		if (!Manager::GetInstance()->GetImportFileManager()->ImportFile(g_szFile))
			MessageBox(g_windowHandle, "���łɓǂݍ��܂�Ă��܂�", "�x��", MB_OK);
		else
			SendMessage(g_objectDialogHandle, WM_NULL, 0, 0);
	}
}


// ���f���̐���
void CreateModel(HWND hDlg)
{

	// �R���{�{�b�N�X���琶�����郂�f���̃t�@�C�����擾
	HWND hCombo1 = GetDlgItem(hDlg, IDC_COMBO1);
	int modelIndex = SendMessage(
		(HWND)hCombo1,			// �R���{�{�b�N�X�̃n���h��
		(UINT)CB_GETCURSEL,		// �I�𒆂̃C���f�b�N�X�擾
		0,						// �O�Œ�
		0						// �ǉ����鍀�ڂ̕�����
		);

	// �R���{�{�b�N�X���琶������e�N�X�`���̃t�@�C�����擾
	HWND hCombo2 = GetDlgItem(hDlg, IDC_COMBO2);
	int textureIndex = SendMessage(
		(HWND)hCombo2,			// �R���{�{�b�N�X�̃n���h��
		(UINT)CB_GETCURSEL,		// �I�𒆂̃C���f�b�N�X�擾
		0,						// �O�Œ�
		0						// �ǉ����鍀�ڂ̕�����
		);

	// �t�@�C�����̎擾
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

					// ���f���̐���
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


// ���N���b�N���̃C�x���g
void ClickLeftEventObjectMode()
{
	// �}�E�X�ƃI�u�W�F�N�g�̏Փ˔���
	Manager::GetInstance()->GetObjectManager()->CheckCollisionMouseAndObject();


	// �X���C�_�[��I�𒆂̃I�u�W�F�N�g�̍��W�ɍ��킹��
	Building *building = Manager::GetInstance()->GetObjectManager()->GetSelectBuilding();
	if (building) {
		D3DXVECTOR3 position = building->GetPosition();
		D3DXVECTOR3 rotation = building->GetRotation();
		D3DXVECTOR3 scale = building->GetScale();
		bool collision = building->GetCollision();


		// �����X���C�_�[
		SendMessage(
			(HWND)GetDlgItem(g_objectDialogHandle, IDC_SLIDER5),	// �X���C�_�[�̃n���h��
			(UINT)TBM_SETPOS,								// ���W�̎擾(0�`100)
			(WPARAM)TRUE,									// �O�Œ�
			(LPARAM)((rotation.x + D3DX_PI) / (D3DX_PI * 2) * 100)			// �ǉ����鍀�ڂ̕�����
			);
		SendMessage(
			(HWND)GetDlgItem(g_objectDialogHandle, IDC_SLIDER6),	// �X���C�_�[�̃n���h��
			(UINT)TBM_SETPOS,								// ���W�̎擾(0�`100)
			(WPARAM)TRUE,									// �O�Œ�
			(LPARAM)((rotation.y + D3DX_PI) / (D3DX_PI * 2) * 100)			// �ǉ����鍀�ڂ̕�����
			);
		SendMessage(
			(HWND)GetDlgItem(g_objectDialogHandle, IDC_SLIDER7),	// �X���C�_�[�̃n���h��
			(UINT)TBM_SETPOS,								// ���W�̎擾(0�`100)
			(WPARAM)TRUE,									// �O�Œ�
			(LPARAM)((rotation.z + D3DX_PI) / (D3DX_PI * 2) * 100)			// �ǉ����鍀�ڂ̕�����
			);



		// ���W�G�f�B�b�g�{�b�N�X
		char str[4096] = {};
		sprintf(str, "%.3f", position.x);
		SetWindowText(
			(HWND)GetDlgItem(g_objectDialogHandle, IDC_EDIT2),		// �X���C�_�[�̃n���h��
			str		// �ǉ����鍀�ڂ̕�����
			);

		sprintf(str, "%.3f", position.y);
		SetWindowText(
			(HWND)GetDlgItem(g_objectDialogHandle, IDC_EDIT3),		// �X���C�_�[�̃n���h��
			str		// �ǉ����鍀�ڂ̕�����
			);

		sprintf(str, "%.3f", position.z);
		SetWindowText(
			(HWND)GetDlgItem(g_objectDialogHandle, IDC_EDIT4),		// �X���C�_�[�̃n���h��
			str		// �ǉ����鍀�ڂ̕�����
			);



		// �X�P�[���G�f�B�b�g�{�b�N�X
		sprintf(str, "%.3f", scale.x);
		SetWindowText(
			(HWND)GetDlgItem(g_objectDialogHandle, IDC_EDIT5),		// �X���C�_�[�̃n���h��
			str		// �ǉ����鍀�ڂ̕�����
			);

		sprintf(str, "%.3f", scale.y);
		SetWindowText(
			(HWND)GetDlgItem(g_objectDialogHandle, IDC_EDIT6),		// �X���C�_�[�̃n���h��
			str		// �ǉ����鍀�ڂ̕�����
			);

		sprintf(str, "%.3f", scale.z);
		SetWindowText(
			(HWND)GetDlgItem(g_objectDialogHandle, IDC_EDIT7),		// �X���C�_�[�̃n���h��
			str		// �ǉ����鍀�ڂ̕�����
			);


		if (collision)
			SendMessage((HWND)GetDlgItem(g_objectDialogHandle, IDC_CHECK1),
				(UINT)BM_SETCHECK, (WPARAM)BST_CHECKED, 0);
		else
			SendMessage((HWND)GetDlgItem(g_objectDialogHandle, IDC_CHECK1),
			(UINT)BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);

	}
}

// ���N���b�N���̃C�x���g
void ClickLeftEventRouteMode()
{
	D3DXVECTOR3 position = Manager::GetInstance()->GetObjectManager()->GetCursor()->GetPosition();

	HWND radio1 = GetDlgItem(g_routeDialogHandle, IDC_RADIO6);
	HWND radio2 = GetDlgItem(g_routeDialogHandle, IDC_RADIO7);
	
	// ���� : �ǉ�
	if (SendMessage(radio1, BM_GETCHECK, 0, 0) == 1) {
		Manager::GetInstance()->GetRouteManager()->CreatePoint(position);
	}
	// ���� : �}��
	if (SendMessage(radio2, BM_GETCHECK, 0, 0) == 1) {
		Manager::GetInstance()->GetRouteManager()->InsertPoint(position);
	}
}

// ���N���b�N���̃C�x���g
void ClickLeftEventDirtMode()
{
}




// �ǂݍ��݊֐�
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
		ofn.lpstrInitialDir = szPath;	// �����t�H���_�ʒu
		ofn.lpstrFile = szFile;			// �I���t�@�C���i�[
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrDefExt = TEXT(".map");
		ofn.lpstrFilter = TEXT("�}�b�v�t�@�C��(*.map)\0*.map\0");
		ofn.lpstrTitle = TEXT("�J��");
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	}

	if (GetSaveFileName(&ofn)) {
		FILE *file = nullptr;
		file = fopen(szFile, "rt");
		if (file) {

			// ���݂̏󋵔j��
			HWND hCombo = GetDlgItem(g_objectDialogHandle, IDC_COMBO1);
			SendMessage((HWND)hCombo, (UINT)CB_RESETCONTENT, 0, 0);
			Manager::GetInstance()->GetObjectManager()->AllDeleteBuilding();
			
			// �ǂݍ���
			Manager::GetInstance()->GetImportFileManager()->ReadImportData(file);
			Manager::GetInstance()->GetImportFileManager()->AllImportFile();
			Manager::GetInstance()->GetObjectManager()->ReadBuildingData(file);

			fclose(file);
		}
		else {
			MessageBox(g_windowHandle, "�ǂݍ��݂Ɏ��s���܂���", "�x��", MB_OK);
		}
	}
}

// �ۑ��֐�
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
		ofn.lpstrInitialDir = szPath;	// �����t�H���_�ʒu
		ofn.lpstrFile = szFile;			// �I���t�@�C���i�[
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrDefExt = TEXT(".map");
		ofn.lpstrFilter = TEXT("�}�b�v�t�@�C��(*.map)\0*.map\0");
		ofn.lpstrTitle = TEXT("���O��t���ĕۑ�");
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
			MessageBox(g_windowHandle, "�ۑ��Ɏ��s���܂���", "�x��", MB_OK);
		}
	}
}






// �_�C�A���O�v���V�[�W��
BOOL CALLBACK RouteDlgProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg) {

		// �_�C�A���O������
	case WM_INITDIALOG:
	{

		// �X�s���R���g���[���ƃG�f�B�b�g�{�b�N�X�̊֘A�t��
		SendMessage(
			(HWND)GetDlgItem(hDlg, IDC_SPIN1),		// �X�s���R���g���[���̃n���h��
			(UINT)UDM_SETBUDDY,
			(WPARAM)GetDlgItem(hDlg, IDC_EDIT2),	// �֘A�t����R���g���[���̃n���h��
			0										// 0�Œ�
			);
		SendMessage(
			(HWND)GetDlgItem(hDlg, IDC_SPIN2),		// �X�s���R���g���[���̃n���h��
			(UINT)UDM_SETBUDDY,
			(WPARAM)GetDlgItem(hDlg, IDC_EDIT3),	// �֘A�t����R���g���[���̃n���h��
			0										// 0�Œ�
			);
		SendMessage(
			(HWND)GetDlgItem(hDlg, IDC_SPIN3),		// �X�s���R���g���[���̃n���h��
			(UINT)UDM_SETBUDDY,
			(WPARAM)GetDlgItem(hDlg, IDC_EDIT4),	// �֘A�t����R���g���[���̃n���h��
			0										// 0�Œ�
			);
		SendMessage(
			(HWND)GetDlgItem(hDlg, IDC_SPIN11),		// �X�s���R���g���[���̃n���h��
			(UINT)UDM_SETBUDDY,
			(WPARAM)GetDlgItem(hDlg, IDC_EDIT11),	// �֘A�t����R���g���[���̃n���h��
			0										// 0�Œ�
			);


		// ���[�h�̐ݒ�
		HWND radio = GetDlgItem(hDlg, IDC_RADIO6);
		SendMessage(
			(HWND)radio,		// ���W�I�{�^���̃n���h��
			(UINT)BM_SETCHECK,
			(WPARAM)BST_CHECKED,
			0					// �O�Œ�
			);


		HWND combo = GetDlgItem(hDlg, IDC_COMBO5);
		SendMessage((HWND)combo, (UINT)CB_ADDSTRING, 0, (LPARAM)"1P�J����");
		SendMessage((HWND)combo, (UINT)CB_ADDSTRING, 0, (LPARAM)"2P�J����");

		combo = GetDlgItem(hDlg, IDC_COMBO1);
		SendMessage((HWND)combo, (UINT)CB_ADDSTRING, 0, (LPARAM)"�ʏ�");
		SendMessage((HWND)combo, (UINT)CB_ADDSTRING, 0, (LPARAM)"�C�x���g");

	}
		return TRUE;

		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			return TRUE;

		case IDCANCEL:
			return TRUE;

		// �v���r���[�Đ�
		case IDC_BUTTON2:
		{
			HWND combo = GetDlgItem(hDlg, IDC_COMBO5);
			int index = SendMessage((HWND)combo, (UINT)CB_GETCURSEL, 0, (LPARAM)0);
			Manager::GetInstance()->GetCameraManager()->ChangePreviewCamera(index);
		}
			break;

		// �v���r���[��~
		case IDC_BUTTON3:
			Manager::GetInstance()->GetCameraManager()->ChangeEditorCamera();
			break;

			// ���[�g�̑I��
		case IDC_COMBO5:

			// �I�������Ƃ�
			if (HIWORD(wParam) == CBN_SELCHANGE) {
				// �R���{�{�b�N�X���琶�����郂�f���̃t�@�C�����擾
				HWND hCombo = GetDlgItem(hDlg, IDC_COMBO5);
				int index = SendMessage(
					(HWND)hCombo,			// �R���{�{�b�N�X�̃n���h��
					(UINT)CB_GETCURSEL,		// �I�𒆂̃C���f�b�N�X�擾
					0,						// �O�Œ�
					0						// �ǉ����鍀�ڂ̕�����
					);

				// �I�𒆂̃��[�g��ύX
				Manager::GetInstance()->GetRouteManager()->SetRouteMode(index);
			}
			break;


		// �_�̑I��
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


			// �_�̐����������͍폜
		case IDC_BUTTON1:
		{
			HWND radio1 = GetDlgItem(hDlg, IDC_RADIO6);
			HWND radio2 = GetDlgItem(hDlg, IDC_RADIO7);
			HWND radio3 = GetDlgItem(hDlg, IDC_RADIO8);

			// ���� : �ǉ�
			if (SendMessage(radio1, BM_GETCHECK, 0, 0) == 1) {
				Manager::GetInstance()->GetRouteManager()->CreatePoint();
			}
			// ���� : �}��
			if (SendMessage(radio2, BM_GETCHECK, 0, 0) == 1) {
				Manager::GetInstance()->GetRouteManager()->InsertPoint();
			}
			// �폜
			if (SendMessage(radio3, BM_GETCHECK, 0, 0) == 1) {
				Manager::GetInstance()->GetRouteManager()->DeletePoint();
			}
		}
			break;

			// ���W : X��
		case IDC_EDIT2:
			if (HIWORD(wParam) == EN_UPDATE) {
				char str[4096] = {};
				GetWindowText(
					(HWND)GetDlgItem(g_routeDialogHandle, IDC_EDIT2),		// �X���C�_�[�̃n���h��
					str, 4096);
				double positionX = atof(str);
				Manager::GetInstance()->GetRouteManager()->SetPositionX((float)positionX);
			}
			break;

			// ���W : Y��
		case IDC_EDIT3:
			if (HIWORD(wParam) == EN_UPDATE) {
				char str[4096] = {};
				GetWindowText(
					(HWND)GetDlgItem(g_routeDialogHandle, IDC_EDIT3),		// �X���C�_�[�̃n���h��
					str, 4096);
				double positionY = atof(str);
				Manager::GetInstance()->GetRouteManager()->SetPositionY((float)positionY);
			}
			break;

			// ���W : Z��
		case IDC_EDIT4:
			if (HIWORD(wParam) == EN_UPDATE) {
				char str[4096] = {};
				GetWindowText(
					(HWND)GetDlgItem(g_routeDialogHandle, IDC_EDIT4),		// �X���C�_�[�̃n���h��
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
					(HWND)GetDlgItem(g_routeDialogHandle, IDC_EDIT11),		// �X���C�_�[�̃n���h��
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
				(HWND)hCombo,			// �R���{�{�b�N�X�̃n���h��
				(UINT)CB_GETCURSEL,		// �I�𒆂̃C���f�b�N�X�擾
				0,						// �O�Œ�
				0						// �ǉ����鍀�ڂ̕�����
				);

			Manager::GetInstance()->GetRouteManager()->SetState(index);
		}
			break;

		default:
			break;
		}
		break;

		// �����X���C�_�[�̒l���擾
	case WM_HSCROLL:
	{

		float position = (float)SendMessage(
			(HWND)lParam,			// �X���C�_�[�̃n���h��
			(UINT)TBM_GETPOS,		// ���W�̎擾(0�`100)
			0,						// �O�Œ�
			0						// �ǉ����鍀�ڂ̕�����
			);

		// ���� : X���X���C�_�[
		if ((HWND)lParam == GetDlgItem(hDlg, IDC_SLIDER1)) {
			Manager::GetInstance()->GetRouteManager()->SetRotationX(
				(position / 100 - 0.5f) * D3DX_PI * 2);
		}
		// ���� : Y���X���C�_�[
		if ((HWND)lParam == GetDlgItem(hDlg, IDC_SLIDER2)) {
			Manager::GetInstance()->GetRouteManager()->SetRotationY(
				(position / 100 - 0.5f) * D3DX_PI * 2);
		}
		// ���� : Z���X���C�_�[
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
					(HWND)GetDlgItem(hDlg, IDC_EDIT2),		// �X���C�_�[�̃n���h��
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
					(HWND)GetDlgItem(hDlg, IDC_EDIT3),		// �X���C�_�[�̃n���h��
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
					(HWND)GetDlgItem(hDlg, IDC_EDIT4),		// �X���C�_�[�̃n���h��
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
					(HWND)GetDlgItem(hDlg, IDC_EDIT11),		// �X���C�_�[�̃n���h��
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

// �ǂݍ��݊֐�
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
		ofn.lpstrInitialDir = szPath;	// �����t�H���_�ʒu
		ofn.lpstrFile = szFile;			// �I���t�@�C���i�[
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrDefExt = TEXT(".rt");
		ofn.lpstrFilter = TEXT("���[�g�t�@�C��(*.rt)\0*.rt\0");
		ofn.lpstrTitle = TEXT("�J��");
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	}

	if (GetSaveFileName(&ofn)) {
		FILE *file = nullptr;
		file = fopen(szFile, "rt");
		if (file) {

			// ���݂̏󋵔j��
			HWND hCombo = GetDlgItem(g_routeDialogHandle, IDC_COMBO4);
			SendMessage((HWND)hCombo, (UINT)CB_RESETCONTENT, 0, 0);
			hCombo = GetDlgItem(g_routeDialogHandle, IDC_COMBO2);
			SendMessage((HWND)hCombo, (UINT)CB_RESETCONTENT, 0, 0);
			Manager::GetInstance()->GetRouteManager()->AllDeletePoint();

			// �ǂݍ���
			Manager::GetInstance()->GetRouteManager()->InputData(file);

			fclose(file);
		}
		else {
			MessageBox(g_windowHandle, "�ǂݍ��݂Ɏ��s���܂���", "�x��", MB_OK);
		}
	}
}

// �ۑ��֐�
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
		ofn.lpstrInitialDir = szPath;	// �����t�H���_�ʒu
		ofn.lpstrFile = szFile;			// �I���t�@�C���i�[
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrDefExt = TEXT(".rt");
		ofn.lpstrFilter = TEXT("���[�g�t�@�C��(*.rt)\0*.rt\0");
		ofn.lpstrTitle = TEXT("���O��t���ĕۑ�");
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
			MessageBox(g_windowHandle, "�ۑ��Ɏ��s���܂���", "�x��", MB_OK);
		}
	}
}






// �_�C�A���O�v���V�[�W��
BOOL CALLBACK DirtDlgProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg) {

		// �_�C�A���O������
	case WM_INITDIALOG:
	{

		// �X�s���R���g���[���ƃG�f�B�b�g�{�b�N�X�̊֘A�t��
		SendMessage(
			(HWND)GetDlgItem(hDlg, IDC_SPIN1),		// �X�s���R���g���[���̃n���h��
			(UINT)UDM_SETBUDDY,
			(WPARAM)GetDlgItem(hDlg, IDC_EDIT2),	// �֘A�t����R���g���[���̃n���h��
			0										// 0�Œ�
			);
		SendMessage(
			(HWND)GetDlgItem(hDlg, IDC_SPIN2),		// �X�s���R���g���[���̃n���h��
			(UINT)UDM_SETBUDDY,
			(WPARAM)GetDlgItem(hDlg, IDC_EDIT3),	// �֘A�t����R���g���[���̃n���h��
			0										// 0�Œ�
			);
		SendMessage(
			(HWND)GetDlgItem(hDlg, IDC_SPIN3),		// �X�s���R���g���[���̃n���h��
			(UINT)UDM_SETBUDDY,
			(WPARAM)GetDlgItem(hDlg, IDC_EDIT4),	// �֘A�t����R���g���[���̃n���h��
			0										// 0�Œ�
			);

		SendMessage(
			(HWND)GetDlgItem(hDlg, IDC_SPIN7),		// �X�s���R���g���[���̃n���h��
			(UINT)UDM_SETBUDDY,
			(WPARAM)GetDlgItem(hDlg, IDC_EDIT5),	// �֘A�t����R���g���[���̃n���h��
			0										// 0�Œ�
			);

		// ���[�h�̐ݒ�
		HWND radio = GetDlgItem(hDlg, IDC_RADIO6);
		SendMessage(
			(HWND)radio,		// ���W�I�{�^���̃n���h��
			(UINT)BM_SETCHECK,
			(WPARAM)BST_CHECKED,
			0					// �O�Œ�
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

		// ����̑I��
		case IDC_COMBO1:

			// �I�������Ƃ�
			if (HIWORD(wParam) == CBN_SELCHANGE) {
				// �R���{�{�b�N�X���琶�����郂�f���̃t�@�C�����擾
				HWND hCombo1 = GetDlgItem(hDlg, IDC_COMBO1);
				int index = SendMessage(
					(HWND)hCombo1,			// �R���{�{�b�N�X�̃n���h��
					(UINT)CB_GETCURSEL,		// �I�𒆂̃C���f�b�N�X�擾
					0,						// �O�Œ�
					0						// �ǉ����鍀�ڂ̕�����
					);

				// �I�𒆂̓_�ύX
				Manager::GetInstance()->GetDirtManager()->SetDirtListCursor(index);


				D3DXVECTOR3 position = Manager::GetInstance()->GetDirtManager()->GetPosition();
				float radius = Manager::GetInstance()->GetDirtManager()->GetRadius();
				// ���W�G�f�B�b�g�{�b�N�X
				char str[4096] = {};
				sprintf(str, "%.3f", position.x);
				SetWindowText(
					(HWND)GetDlgItem(g_dirtDialogHandle, IDC_EDIT2),		// �X���C�_�[�̃n���h��
					str		// �ǉ����鍀�ڂ̕�����
					);

				sprintf(str, "%.3f", position.y);
				SetWindowText(
					(HWND)GetDlgItem(g_dirtDialogHandle, IDC_EDIT3),		// �X���C�_�[�̃n���h��
					str		// �ǉ����鍀�ڂ̕�����
					);

				sprintf(str, "%.3f", position.z);
				SetWindowText(
					(HWND)GetDlgItem(g_dirtDialogHandle, IDC_EDIT4),		// �X���C�_�[�̃n���h��
					str		// �ǉ����鍀�ڂ̕�����
					);

				sprintf(str, "%.3f", radius);
				SetWindowText(
					(HWND)GetDlgItem(g_dirtDialogHandle, IDC_EDIT5),		// �X���C�_�[�̃n���h��
					str		// �ǉ����鍀�ڂ̕�����
					);
			}
			break;


		// �_�̐����������͍폜
		case IDC_BUTTON1:
		{
			HWND radio1 = GetDlgItem(hDlg, IDC_RADIO6);
			HWND radio3 = GetDlgItem(hDlg, IDC_RADIO8);

			// ���� : �ǉ�
			if (SendMessage(radio1, BM_GETCHECK, 0, 0) == 1) {
				Manager::GetInstance()->GetDirtManager()->CreateDirt();
			}
			// �폜
			if (SendMessage(radio3, BM_GETCHECK, 0, 0) == 1) {
				Manager::GetInstance()->GetDirtManager()->DeleteDirt();
			}
		}
			break;


		// ���W : X��
		case IDC_EDIT2:
			if (HIWORD(wParam) == EN_UPDATE) {
				char str[4096] = {};
				GetWindowText(
					(HWND)GetDlgItem(g_dirtDialogHandle, IDC_EDIT2),		// �X���C�_�[�̃n���h��
					str, 4096);
				double positionX = atof(str);
				Manager::GetInstance()->GetDirtManager()->SetPositionX((float)positionX);
			}
			break;

			// ���W : Y��
		case IDC_EDIT3:
			if (HIWORD(wParam) == EN_UPDATE) {
				char str[4096] = {};
				GetWindowText(
					(HWND)GetDlgItem(g_dirtDialogHandle, IDC_EDIT3),		// �X���C�_�[�̃n���h��
					str, 4096);
				double positionY = atof(str);
				Manager::GetInstance()->GetDirtManager()->SetPositionY((float)positionY);
			}
			break;

			// ���W : Z��
		case IDC_EDIT4:
			if (HIWORD(wParam) == EN_UPDATE) {
				char str[4096] = {};
				GetWindowText(
					(HWND)GetDlgItem(g_dirtDialogHandle, IDC_EDIT4),		// �X���C�_�[�̃n���h��
					str, 4096);
				double positionZ = atof(str);
				Manager::GetInstance()->GetDirtManager()->SetPositionZ((float)positionZ);
			}
			break;


			// ���a
		case IDC_EDIT5:
			if (HIWORD(wParam) == EN_UPDATE) {
				char str[4096] = {};
				GetWindowText(
					(HWND)GetDlgItem(g_dirtDialogHandle, IDC_EDIT5),		// �X���C�_�[�̃n���h��
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
					(HWND)GetDlgItem(hDlg, IDC_EDIT2),		// �X���C�_�[�̃n���h��
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
					(HWND)GetDlgItem(hDlg, IDC_EDIT3),		// �X���C�_�[�̃n���h��
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
					(HWND)GetDlgItem(hDlg, IDC_EDIT4),		// �X���C�_�[�̃n���h��
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
					(HWND)GetDlgItem(hDlg, IDC_EDIT5),		// �X���C�_�[�̃n���h��
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

// �ǂݍ��݊֐�
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
		ofn.lpstrInitialDir = szPath;	// �����t�H���_�ʒu
		ofn.lpstrFile = szFile;			// �I���t�@�C���i�[
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrDefExt = TEXT(".drt");
		ofn.lpstrFilter = TEXT("����t�@�C��(*.drt)\0*.drt\0");
		ofn.lpstrTitle = TEXT("�J��");
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	}

	if (GetSaveFileName(&ofn)) {
		FILE *file = nullptr;
		file = fopen(szFile, "rt");
		if (file) {

			// ���݂̏󋵔j��
			HWND hCombo = GetDlgItem(g_dirtDialogHandle, IDC_COMBO1);
			SendMessage((HWND)hCombo, (UINT)CB_RESETCONTENT, 0, 0);
			Manager::GetInstance()->GetDirtManager()->AllDeleteDirt();

			// �ǂݍ���
			Manager::GetInstance()->GetDirtManager()->InputData(file);

			fclose(file);
		}
		else {
			MessageBox(g_windowHandle, "�ǂݍ��݂Ɏ��s���܂���", "�x��", MB_OK);
		}
	}
}

// �ۑ��֐�
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
		ofn.lpstrInitialDir = szPath;	// �����t�H���_�ʒu
		ofn.lpstrFile = szFile;			// �I���t�@�C���i�[
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrDefExt = TEXT(".drt");
		ofn.lpstrFilter = TEXT("����t�@�C��(*.drt)\0*.drt\0");
		ofn.lpstrTitle = TEXT("���O��t���ĕۑ�");
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
			MessageBox(g_windowHandle, "�ۑ��Ɏ��s���܂���", "�x��", MB_OK);
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