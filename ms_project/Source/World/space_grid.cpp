//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 空間格子 : 空間分割
// 
// Created by Ryusei Kajiya on 20151009
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "space_grid.h"

#include "Unit/unit.h"

//=============================================================================
// ユニットの操作
void SpaceGrid::HandleUnit(Unit* unit, Unit* other_unit)
{
	while( other_unit != nullptr)
	{
		// 何かしらの処理:衝突判定とかAI
		UNREFERENCED_PARAMETER(unit);

		// 次のユニットへ
		other_unit = other_unit->_next;
	}
}

//=============================================================================
// マス目のユニット操作
void SpaceGrid::HandleCell(s32 x, s32 y)
{
	Unit* unit = _cells[x][y];

	while( unit != nullptr)
	{
		HandleUnit(unit,unit->_next);

		// 隣接するセルも処理する。
		if( x > 0)
		{
			HandleUnit(unit, _cells[x - 1][y]);
		}
		if( y > 0)
		{
			HandleUnit(unit, _cells[x][y - 1]);
		}

		if( x > 0 && y > 0 )
		{
			HandleUnit(unit, _cells[x - 1][y - 1]);
		}

		if( x > 0 && y < kMaxCell - 1 )
		{
			HandleUnit(unit, _cells[x - 1][y + 1]);
		}

		unit = unit->_next;
	}
}

//=============================================================================
// Unitの追加
void SpaceGrid::AddUnit(Unit* unit)
{
	// どのセルかを検出
	s32 cell_x = static_cast<s32>(unit->_world_position.x / kSizeCell);
	if( cell_x  <= 0)
	{
		cell_x = 0;
	}
	if( cell_x  >= kSizeCell *kMaxCell)
	{
		cell_x = kMaxCell - 1;
	}
	s32 cell_y = static_cast<s32>(unit->_world_position.y / kSizeCell);
	if( cell_y <= 0 )
	{
		cell_y = 0;
	}
	if( cell_y >= kSizeCell *kMaxCell )
	{
		cell_y = kMaxCell - 1;
	}

	// 入っているセルの先頭に追加
	unit->_previous = nullptr;
	unit->_next = _cells[cell_x][cell_y];
	_cells[cell_x][cell_y] = unit;

	if( unit->_next != nullptr)
	{
		unit->_next->_previous = unit;
	}
}
