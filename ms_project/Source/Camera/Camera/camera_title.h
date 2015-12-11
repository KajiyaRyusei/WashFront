//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// タイトルカメラ
// 
// Created by Ryusei Kajiya on 20151201
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
class CameraTitle : public Camera
{
public:

	CameraTitle(Application* application) : Camera(application){ Initialize(); }
	virtual ~CameraTitle(){}

	// 初期化
	virtual void Initialize() override;

	// プロジェクションとビュー行列作成
	virtual void CreateMatrix() override;

};