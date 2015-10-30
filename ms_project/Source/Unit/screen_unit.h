//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// テストスクリーン用ユニット : 2Dオブジェクトの書き方
// 
// Created by Ryusei Kajiya on 20151012
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "unit.h"

//*****************************************************************************
// 前方宣言
class ShaderScreen;
class MeshBuffer;

//*****************************************************************************
// クラス設計
class ScreenUnit : public Unit
{
public:

	ScreenUnit(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~ScreenUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override{}

private:

	// シェーダー
	ShaderScreen* _shader;

	// メッシュ
	MeshBuffer* _mesh;
};