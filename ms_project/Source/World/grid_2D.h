//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 2D格子
// 
// Created by Ryusei Kajiya on 20151028
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Data/data_position.h"

//*****************************************************************************
// 前方宣言
class Unit;

//*****************************************************************************
// クラス設計
class Grid2D
{
public:

	Grid2D()
	{
		for( s32 x = 0; x < kMaxCell; ++x )
		{
			for( s32 z = 0; z < kMaxCell; ++z )
			{
				_cells[x][z] = nullptr;
			}
		}
	}

	virtual ~Grid2D()
	{

	}

	// ユニットの操作
	virtual void HandleUnit(Unit* unit, Unit* other_unit) = 0;

	// マス目のユニット操作
	void HandleCell(s32 x, s32 z);

	// ユニットの追加
	void AddUnit(Unit* unit, const data::Position& position);

	// ユニットの移動
	void MoveUnit(Unit* unit, const data::Position& position);

	// 座標のcellのindexを返す
	void SelfCoordinatesCell(
		s32* cell_x,
		s32* cell_z,
		const data::Position& position);

	// セルのサイズ
	static const s32 S_GetMaxCell() { return kMaxCell; }

	// セルの数
	static const s32 S_GetSizeCell() { return kSizeCell; }

	// そのセルの中心ポイントを持ってくる
	D3DXVECTOR3 CellCenterPoint(s32 x, s32 z)
	{
		D3DXVECTOR3 work;
		work.x = static_cast<fx32>(kSizeCell)* x + (kSizeCell / 2);
		//work.y = 0.f;
		work.z = static_cast<fx32>(kSizeCell)* z + (kSizeCell / 2);
		return work;
	}

protected:

	static const s32 kMaxCell = 5;
	static const s32 kSizeCell = 30;

	Unit* _cells[kMaxCell][kMaxCell];

private:

	// セルの算出
	s32 CellCalculation(fx32 position);
};
