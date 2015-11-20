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
BOOL CALLBACK DlgProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam);

// �t�@�C���̓ǂݍ���
void ImportFile(HWND windowHandle);

// ���f���̐���
void CreateModel(HWND hDlg);

// ���N���b�N���̃C�x���g
void ClickLeftEvent();

// �ǂݍ��݊֐�
void ReadMapFile(HWND hWnd);

// �ۑ��֐�
void SaveMapFile(HWND hWnd);



//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
HWND g_windowHandle = nullptr;
HWND g_dialogHandle = nullptr;

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
	g_dialogHandle = CreateDialog(instance, MAKEINTRESOURCE(IDD_DIALOG1),
		g_windowHandle, DlgProc);
	ShowWindow(g_dialogHandle, cmd_show);
	UpdateWindow(g_dialogHandle);


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
			ImportFile(wnd);
			break;


		// ���O�����ĕۑ�
		case ID_40006:
			// �ۑ�
			SaveMapFile(wnd);
			break;

		default:
			break;
		}


	// �}�E�X���N���b�N��
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
// �_�C�A���O�v���V�[�W��
//=============================================================================
BOOL CALLBACK DlgProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg) {

	// �_�C�A���O������
	case WM_INITDIALOG:

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

		// ���W : X��
		case IDC_EDIT2:
			if (HIWORD(wParam) == EN_UPDATE) {

				Building *building = Manager::GetInstance()->GetObjectManager()->GetSelectBuilding();
				if (building) {
					char str[4096] = {};
					GetWindowText(
						(HWND)GetDlgItem(g_dialogHandle, IDC_EDIT2),		// �X���C�_�[�̃n���h��
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
						(HWND)GetDlgItem(g_dialogHandle, IDC_EDIT3),		// �X���C�_�[�̃n���h��
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
						(HWND)GetDlgItem(g_dialogHandle, IDC_EDIT4),		// �X���C�_�[�̃n���h��
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
						(HWND)GetDlgItem(g_dialogHandle, IDC_EDIT5),		// �X���C�_�[�̃n���h��
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
						(HWND)GetDlgItem(g_dialogHandle, IDC_EDIT6),		// �X���C�_�[�̃n���h��
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
						(HWND)GetDlgItem(g_dialogHandle, IDC_EDIT7),		// �X���C�_�[�̃n���h��
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

	// �R���{�{�b�N�X�Ƀt�@�C�����ǉ�
	case WM_NULL:
	{
		
		const char *fileName = Manager::GetInstance()->GetImportFileManager()->GetFileName(g_szFile);

		HWND hCombo = GetDlgItem(hDlg, IDC_COMBO1);

		SendMessage(
			(HWND)hCombo,			// �R���{�{�b�N�X�̃n���h��
			(UINT)CB_ADDSTRING,		// ���ڂ̒ǉ�
			0,						// �O�Œ�
			(LPARAM)fileName		// �ǉ����鍀�ڂ̕�����
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
// �t�@�C���̓ǂݍ���
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

	// �_�C�A���O�̏��
	if (ofn.lStructSize == 0) {
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = windowHandle;
		ofn.lpstrInitialDir = szPath;	// �����t�H���_�ʒu
		ofn.lpstrFile = g_szFile;		// �I���t�@�C���i�[
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrFilter = "���f���f�[�^(*.x)\0*.x";
		ofn.lpstrTitle = "���f���̃C���|�[�g";
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	}

	// �_�C�A���O�\��
	if (GetOpenFileName(&ofn)) {

		// ���f���t�@�C���̓ǂݍ���
		if (!Manager::GetInstance()->GetImportFileManager()->ImportFile(g_szFile))
			MessageBox(g_windowHandle, "���łɓǂݍ��܂�Ă��܂�", "�x��", MB_OK);
		else
			SendMessage(g_dialogHandle, WM_NULL, 0, 0);
	}
}

// ���f���̐���
void CreateModel(HWND hDlg)
{

	// �R���{�{�b�N�X���琶�����郂�f���̃t�@�C�����擾
	HWND hCombo = GetDlgItem(hDlg, IDC_COMBO1);
	int index = SendMessage(
		(HWND)hCombo,			// �R���{�{�b�N�X�̃n���h��
		(UINT)CB_GETCURSEL,		// �I�𒆂̃C���f�b�N�X�擾
		0,						// �O�Œ�
		0						// �ǉ����鍀�ڂ̕�����
		);


	// �t�@�C�����̎擾
	int intTxtLen = SendMessage(hCombo, CB_GETLBTEXTLEN, index, 0);
	if (intTxtLen != CB_ERR)
	{
		char* pszBuf = new char[intTxtLen + 1];
		if (SendMessage(hCombo, CB_GETLBTEXT, index, (LPARAM)pszBuf) != CB_ERR)
		{
			// ���f���̐���
			Manager::GetInstance()->GetObjectManager()->CreateBuilding(
				Manager::GetInstance()->GetImportFileManager()->GetFilePath(pszBuf));
		}
		delete[] pszBuf;
	}

}


// ���N���b�N���̃C�x���g
void ClickLeftEvent()
{
	// �}�E�X�ƃI�u�W�F�N�g�̏Փ˔���
	Manager::GetInstance()->GetObjectManager()->CheckCollisionMouseAndObject();


	// �X���C�_�[��I�𒆂̃I�u�W�F�N�g�̍��W�ɍ��킹��
	Building *building = Manager::GetInstance()->GetObjectManager()->GetSelectBuilding();
	if (building) {
		D3DXVECTOR3 position = building->GetPosition();
		D3DXVECTOR3 rotation = building->GetRotation();
		D3DXVECTOR3 scale = building->GetScale();


		// �����X���C�_�[
		SendMessage(
			(HWND)GetDlgItem(g_dialogHandle, IDC_SLIDER5),	// �X���C�_�[�̃n���h��
			(UINT)TBM_SETPOS,								// ���W�̎擾(0�`100)
			(WPARAM)TRUE,									// �O�Œ�
			(LPARAM)((rotation.x + D3DX_PI) / (D3DX_PI * 2) * 100)			// �ǉ����鍀�ڂ̕�����
			);
		SendMessage(
			(HWND)GetDlgItem(g_dialogHandle, IDC_SLIDER6),	// �X���C�_�[�̃n���h��
			(UINT)TBM_SETPOS,								// ���W�̎擾(0�`100)
			(WPARAM)TRUE,									// �O�Œ�
			(LPARAM)((rotation.y + D3DX_PI) / (D3DX_PI * 2) * 100)			// �ǉ����鍀�ڂ̕�����
			);
		SendMessage(
			(HWND)GetDlgItem(g_dialogHandle, IDC_SLIDER7),	// �X���C�_�[�̃n���h��
			(UINT)TBM_SETPOS,								// ���W�̎擾(0�`100)
			(WPARAM)TRUE,									// �O�Œ�
			(LPARAM)((rotation.z + D3DX_PI) / (D3DX_PI * 2) * 100)			// �ǉ����鍀�ڂ̕�����
			);



		// ���W�G�f�B�b�g�{�b�N�X
		char str[4096] = {};
		sprintf(str, "%.1f", position.x);
		SetWindowText(
			(HWND)GetDlgItem(g_dialogHandle, IDC_EDIT2),		// �X���C�_�[�̃n���h��
			str		// �ǉ����鍀�ڂ̕�����
			);

		sprintf(str, "%.1f", position.y);
		SetWindowText(
			(HWND)GetDlgItem(g_dialogHandle, IDC_EDIT3),		// �X���C�_�[�̃n���h��
			str		// �ǉ����鍀�ڂ̕�����
			);

		sprintf(str, "%.1f", position.z);
		SetWindowText(
			(HWND)GetDlgItem(g_dialogHandle, IDC_EDIT4),		// �X���C�_�[�̃n���h��
			str		// �ǉ����鍀�ڂ̕�����
			);



		// �X�P�[���G�f�B�b�g�{�b�N�X
		sprintf(str, "%.1f", scale.x);
		SetWindowText(
			(HWND)GetDlgItem(g_dialogHandle, IDC_EDIT5),		// �X���C�_�[�̃n���h��
			str		// �ǉ����鍀�ڂ̕�����
			);

		sprintf(str, "%.1f", scale.y);
		SetWindowText(
			(HWND)GetDlgItem(g_dialogHandle, IDC_EDIT6),		// �X���C�_�[�̃n���h��
			str		// �ǉ����鍀�ڂ̕�����
			);

		sprintf(str, "%.1f", scale.z);
		SetWindowText(
			(HWND)GetDlgItem(g_dialogHandle, IDC_EDIT7),		// �X���C�_�[�̃n���h��
			str		// �ǉ����鍀�ڂ̕�����
			);

	}
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
			HWND hCombo = GetDlgItem(g_dialogHandle, IDC_COMBO1);
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

HWND GetDialogHandle()
{
	return g_dialogHandle;
}


// End of file