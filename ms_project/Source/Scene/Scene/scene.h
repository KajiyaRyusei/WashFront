//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// シーン
// 
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "System/application.h"

// 描画
#include "DrawCommand/command_processor.h"
#include "DrawCommand/command_buffer.h"
#include "DrawCommand/command_buffer_holder.h"

//*****************************************************************************
// クラス設計
class Scene
{
public:
	Scene(Application* application) :
		_application{ application }
	{}

	virtual ~Scene(){}

	// 初期化
	virtual void Initialize() = 0;

	// 終了
	virtual void Finalize() = 0;

	// 更新
	virtual void Update() = 0;

	// 描画
	virtual void Draw() = 0;

protected:

	// データ
	Application *_application;

};