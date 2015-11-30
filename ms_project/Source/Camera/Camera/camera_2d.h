//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 2Dカメラ
// 
// Created by Ryusei Kajiya on 20151022
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "camera.h"

//*****************************************************************************
// クラス設計
class Camera2D : public Camera
{
public:

	explicit Camera2D(Application* application) : Camera(application){ Initialize(); }
	virtual ~Camera2D(){}

	// 初期化
	virtual void Initialize() override;

	// プロジェクションとビュー行列作成
	virtual void CreateMatrix() override;

};