//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 背景用天球
// 
// Created by Ryusei Kajiya on 20151102
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Unit/unit.h"
#include "Data/data_projection.h"

//*****************************************************************************
// 前方宣言
class ShaderBackGround;

//*****************************************************************************
// クラス設計
class BackGroundUnit : public Unit
{
public:

	BackGroundUnit(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~BackGroundUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override{};
private:

	// シェーダー
	ShaderBackGround* _shader;

};