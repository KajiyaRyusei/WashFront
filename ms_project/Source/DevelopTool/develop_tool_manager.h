//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// デバッグツールマネージャー
// 
// Created by Ryusei Kajiya on 20151007
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "DevelopTool/debug_print.h"

//*****************************************************************************
// クラス設計
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