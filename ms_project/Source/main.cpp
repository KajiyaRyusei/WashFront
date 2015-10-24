//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �G���g���[�|�C���g
//
// Created by Ryusei Kajiya on 20151005
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// �C���N���[�h
#include "System/system_flow.h"

//=============================================================================
// �G���g���[�|�C���g
s32 APIENTRY WinMain(
	HINSTANCE handle_instance,
	HINSTANCE handle_instance_previous,
	LPSTR command_line,
	s32 command_show)
{
	// ���g�p�錾
	UNREFERENCED_PARAMETER(handle_instance_previous);
	UNREFERENCED_PARAMETER(handle_instance);
	UNREFERENCED_PARAMETER(command_line);
	UNREFERENCED_PARAMETER(command_show);

#ifdef _DEBUG
	OutputDebugString(L"�f�o�b�O���[�h\n");
#endif
#ifdef _DEVELOP
	OutputDebugString(L"�f�x���b�v���[�h\n");
#endif
#ifdef _RELEASE
	OutputDebugString(L"�����[�X���[�h\n");
#endif

#ifndef _RELEASE
	// ���������[�N�����p�֐�
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	static SystemFlow system;

	system.Initialize(handle_instance);

	system.MessageLoop();

	system.Finalize();

	return 0;
}
