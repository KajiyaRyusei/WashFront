//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 水しぶきのオブジェクトプールのダミー
// 
// Created by Ryusei Kajiya on 20151128
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Unit/unit.h"
#include "water_spray_pool.h"

//*****************************************************************************
// クラス設計
class WaterSprayPoolDummy : public WaterSprayPool
{
public:
	WaterSprayPoolDummy(Application* application, World* world) : WaterSprayPool(application, world)
	{
		UNREFERENCED_PARAMETER(application);
		UNREFERENCED_PARAMETER(world);
	}

	virtual ~WaterSprayPoolDummy(){}

	// 作成
	virtual void Create(
		const D3DXVECTOR3& position,
		const fx32 rotation) override
	{
		UNREFERENCED_PARAMETER(position);
		UNREFERENCED_PARAMETER(rotation);
	}

	// アニメーション:描画も兼ねてる。
	virtual void Animate()override{}

	virtual void Initialize() override{}
	virtual void Finalize() override{}
	virtual void Update() override{}
	virtual void Draw() override{}
	virtual void CollisionUpdate() override{}
};
