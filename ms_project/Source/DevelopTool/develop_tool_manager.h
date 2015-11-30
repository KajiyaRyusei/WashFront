//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �f�o�b�O�c�[���}�l�[�W���[
// 
// Created by Ryusei Kajiya on 20151007
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "DevelopTool/debug_print.h"
#include "DevelopTool/debug_line.h"
#include "DevelopTool/debug_line_box.h"
#include "DevelopTool/debug_box.h"
#include "DevelopTool/debug_sphere.h"

//*****************************************************************************
// �N���X�݌v
class DevelopToolManager
{
public:

	DevelopToolManager()
	{
		Initialize();
	}

	virtual ~DevelopToolManager()
	{
		Finalize();
	}

	void Initialize();
	void Finalize();
	void Update();
	void Draw();

	DebugPrint& GetDebugPrint(){ return _debug_print; }
	DebugLine& GetDebugLine(){ return _debug_line; }
	DebugLineBox& GetDebugLineBox(){ return _debug_line_box; }
	DebugBox& GetDebugBox(){ return _debug_box; }
	DebugSphere& GetDebugSphere(){ return _debug_sphere; }

private:
	DebugPrint _debug_print;
	DebugLine _debug_line;
	DebugLineBox _debug_line_box;
	DebugBox _debug_box;
	DebugSphere _debug_sphere;
};