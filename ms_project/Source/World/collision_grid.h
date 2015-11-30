//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 衝突判定用格子 : XZ
// 
// Created by Ryusei Kajiya on 20151028
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "World/grid_2D.h"

//*****************************************************************************
// 前方宣言
class Unit;

//*****************************************************************************
// クラス設計
class CollisionGrid : public Grid2D
{
public:

	CollisionGrid(){}

	virtual ~CollisionGrid(){}

	// ユニットの操作
	virtual void HandleUnit(Unit* unit, Unit* other_unit) override;

	// デバッグ用描画
	void DebugDraw();

private:

	// 球と球
	void Sphrere2Sphere(Unit* unit, Unit* other_unit);

	// 球とボックス
	// 正確にはXZの円と円
	void Sphrere2Box(Unit* unit, Unit* other_unit);

	// 線とbox
	void Line2Box(Unit* unit, Unit* other_unit);

	// メッシュポイントと球
	void MeshPoint2Sphrere(Unit* unit, Unit* other_unit);
};
