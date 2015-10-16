//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 空間格子 : 空間分割
// 
// Created by Ryusei Kajiya on 20151009
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// 前方宣言
class Unit;

//*****************************************************************************
// クラス設計
class SpaceGrid
{
public:

	SpaceGrid()
	{
		for( s32 x = 0; x < kMaxCell; ++x )
		{
			for( s32 y = 0; y < kMaxCell; ++y )
			{
				_cells[x][y] = nullptr;
			}
		}
	}

	virtual ~SpaceGrid(){}

	// ユニットの操作
	void HandleUnit(Unit* unit, Unit* other_unit);

	// マス目のユニット操作
	void HandleCell(s32 x, s32 y);

	// ユニットの追加
	void AddUnit(Unit* unit);

private:

	static const s32 kMaxCell = 10;
	static const s32 kSizeCell = 20;

	Unit* _cells[kMaxCell][kMaxCell];
};