//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// デバッグツールマネージャー
// 
// Created by Ryusei Kajiya on 20151007
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//******************************************************************************
// include
#include "develop_tool_manager.h"

//==============================================================================
// 初期化
void DevelopToolManager::Initialize()
{
#ifndef _RELEASE
	_debug_print.Initialize();
	_debug_line.Initialize();
	_debug_line_box.Initialize();
#endif
}

//==============================================================================
// 終了
void DevelopToolManager::Finalize()
{
#ifndef _RELEASE
	_debug_print.Finalize();
	_debug_line.Finalize();
	_debug_line_box.Finalize();
#endif
}

//==============================================================================
// 更新
void DevelopToolManager::Update()
{
#ifndef _RELEASE

#endif
}

//==============================================================================
// 描画
void DevelopToolManager::Draw()
{
#ifndef _RELEASE
	_debug_line.Draw();
	_debug_line_box.Draw();
	_debug_print.Draw();
#endif
}
