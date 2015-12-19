//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// �E�B���h�E
// 
// Created by Ryusei Kajiya on 20151005
// 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// �C���N���[�h
#include "window.h"
#include "window_procedure.h"

//*****************************************************************************
// �萔
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
// �R���X�g���N�^
Window::Window(HINSTANCE handle_instance) :
	_handle_window{ nullptr },
	_handle_instance{ handle_instance },
	_size_window_width{ kSizeWindowWidth },
	_size_window_height{kSizeWindowHeight}
{
	Initialize();
}

//=============================================================================
// ������
void Window::Initialize()
{

	// �E�B���h�E�N���X�쐬
	WNDCLASSEX window_class;
	window_class.cbSize = sizeof(WNDCLASSEX);				// �\���̂̃T�C�Y
	window_class.style = CS_CLASSDC;						// �E�B���h�E�X�^�C��
	window_class.lpfnWndProc = WindowProcedure;				// �E�B���h�E�v���V�[�W��
	window_class.cbClsExtra = 0;							// �\���
	window_class.cbWndExtra = 0;							// �\���
	window_class.hInstance = _handle_instance;				// �C���X�^���X
	window_class.hIcon = nullptr;							// �A�C�R��
	window_class.hCursor = LoadCursor(nullptr, IDC_ARROW);	// �J�[�\��
	window_class.hbrBackground = (HBRUSH)(COLOR_WINDOW + 0);// �w�i�F
	window_class.lpszClassName = kWindowClass;				// �N���X�l�[��
	window_class.lpszMenuName = kWindowName;				// ���j���[�l�[��
	window_class.hIconSm = nullptr;							// �������A�C�R��

	// �o�^
	RegisterClassEx(&window_class);

	// �E�B���h�E�쐬�F�^�C�g���o�[������A�T�C�Y�̕ύX�ł��Ȃ��E�B���h�E�̎��͂��͂ޘg���s�N�Z���P�ʂŎ擾 + �^�C�g���o�[�̍������s�N�Z���P�ʂŎ擾
	u32 window_size_width = kSizeWindowWidth + GetSystemMetrics(SM_CXDLGFRAME) * 2;
	u32 window_size_height = kSizeWindowHeight + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION);

	// ����ԁ{�^�C�g���Ƙg�����{�^�C�g���o�[���쐬�{���j���[�{�b�N�X��z�u�{�ŏ����ƍő剻������
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

	ASSERT(_handle_window != nullptr, "�E�B���h�E�n���h���̎擾�Ɏ��s���܂���\n");

	// �E�B���h�E�\��
	ShowWindow(_handle_window, SW_SHOW);
	UpdateWindow(_handle_window);

	// �o�^
	Reference::GetInstance().SetHandleWindow(_handle_window);
	Reference::GetInstance().SetSizeScreenHeight(kSizeWindowWidth);
	Reference::GetInstance().SetSizeScreenWidth(kSizeWindowWidth);
}
//=============================================================================
// �I��
void Window::Finalize()
{
	UnregisterClass(kWindowClass, _handle_instance);
}
