//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �f�o�b�O�c�[���}�l�[�W���[
// 
// Created by Ryusei Kajiya on 20151007
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//******************************************************************************
// include
#include "develop_tool_manager.h"

//==============================================================================
// ������
void DevelopToolManager::Initialize()
{
#ifndef _RELEASE
	_debug_print.Initialize();
	_debug_line.Initialize();
	_debug_line_box.Initialize();
#endif
}

//==============================================================================
// �I��
void DevelopToolManager::Finalize()
{
#ifndef _RELEASE
	_debug_print.Finalize();
	_debug_line.Finalize();
	_debug_line_box.Finalize();
#endif
}

//==============================================================================
// �X�V
void DevelopToolManager::Update()
{
#ifndef _RELEASE

#endif
}

//==============================================================================
// �`��
void DevelopToolManager::Draw()
{
#ifndef _RELEASE
	_debug_line.Draw();
	_debug_line_box.Draw();
	_debug_print.Draw();
#endif
}
