//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ゲームメインカメラ
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
class CameraGameMain : public Camera
{
public:

	CameraGameMain(Application* application) : Camera(application){ Initialize(); }
	virtual ~CameraGameMain(){}

	// 初期化
	virtual void Initialize() override;

	// プロジェクションとビュー行列作成
	virtual void CreateMatrix() override;

};