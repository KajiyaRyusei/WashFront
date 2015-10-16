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

#ifndef _RELEASE

	void Initialize();
	void Finalize();
	void Update();
	void Draw();
#else

	void Initialize(){}
	void Finalize(){}
	void Update(){}
	void Draw(){}

#endif

	DebugPrint& GetDebugPrint(){ return _debug_print; }

private:
	DebugPrint _debug_print;
};