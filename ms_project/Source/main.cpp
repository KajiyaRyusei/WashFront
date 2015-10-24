//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// エントリーポイント
//
// Created by Ryusei Kajiya on 20151005
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// インクルード
#include "System/system_flow.h"

//=============================================================================
// エントリーポイント
s32 APIENTRY WinMain(
	HINSTANCE handle_instance,
	HINSTANCE handle_instance_previous,
	LPSTR command_line,
	s32 command_show)
{
	// 未使用宣言
	UNREFERENCED_PARAMETER(handle_instance_previous);
	UNREFERENCED_PARAMETER(handle_instance);
	UNREFERENCED_PARAMETER(command_line);
	UNREFERENCED_PARAMETER(command_show);

#ifdef _DEBUG
	OutputDebugString(L"デバッグモード\n");
#endif
#ifdef _DEVELOP
	OutputDebugString(L"デベロップモード\n");
#endif
#ifdef _RELEASE
	OutputDebugString(L"リリースモード\n");
#endif

#ifndef _RELEASE
	// メモリリーク調査用関数
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	static SystemFlow system;

	system.Initialize(handle_instance);

	system.MessageLoop();

	system.Finalize();

	return 0;
}
