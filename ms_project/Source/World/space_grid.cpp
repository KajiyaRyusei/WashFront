//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 空間格子 : 空間分割
// 
// Created by Ryusei Kajiya on 20151023
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
		// 手の届く範囲は別のセルでも処理
		if( fabs(D3DXVec3Length(&unit->_world_position) 
			- D3DXVec3Length(&other_unit->_world_position)) < kAttackDistance )
		{
			//HandleAtack();
		}
		// 何かしらの処理:衝突判定とかAI
		UNREFERENCED_PARAMETER(unit);

		// 次のユニットへ
		other_unit = other_unit->_next;
	}
}

//=============================================================================
// マス目のユニット操作
void SpaceGrid::HandleCell(s32 x, s32 y,s32 z)
{
	Unit* unit = _cells[x][y][z];

	while( unit != nullptr)
	{
		HandleUnit(unit,unit->_next);

		// 隣接するセルも処理する。
		if( x > 0)
		{
			HandleUnit(unit, _cells[x - 1][y][z]);
		}
		if( y > 0)
		{
			HandleUnit(unit, _cells[x][y - 1][z]);
		}
		if(z > 0)
		{
			HandleUnit(unit, _cells[x][y][z - 1]);
		}

		if( x > 0 && y > 0  && x > 0)
		{
			HandleUnit(unit, _cells[x - 1][y - 1][z - 1]);
		}
		if( x > 0 && y < kMaxCell - 1 && z > 0)
		{
			HandleUnit(unit, _cells[x - 1][y + 1][z - 1]);
		}
		if( x > 0 && y <  0&& z > kMaxCell - 1 )
		{
			HandleUnit(unit, _cells[x - 1][y - 1][z + 1]);
		}

		unit = unit->_next;
	}
}

//=============================================================================
// Unitの追加
void SpaceGrid::AddUnit(Unit* unit, D3DXVECTOR3 position)
{
	// どのセルかを検出
	s32 cell_x = CellCalculation(position.x);
	s32 cell_y = CellCalculation(position.y);
	s32 cell_z = CellCalculation(position.z);

	// 入っているセルの先頭に追加
	unit->_previous = nullptr;
	unit->_next = _cells[cell_x][cell_y][cell_z];
	_cells[cell_x][cell_y][cell_z] = unit;

	if( unit->_next != nullptr)
	{
		unit->_next->_previous = unit;
	}
}

//=============================================================================
// Unitの移動
void SpaceGrid::MoveUnit(Unit* unit, D3DXVECTOR3 position, D3DXVECTOR3 previous_position)
{
	// 前のセルを算出
	s32 previous_cell_x = CellCalculation(previous_position.x);
	s32 previous_cell_y = CellCalculation(previous_position.y);
	s32 previous_cell_z = CellCalculation(previous_position.z);

	// 現在のセルを算出
	s32 cell_x = CellCalculation(position.x);
	s32 cell_y = CellCalculation(position.y);
	s32 cell_z = CellCalculation(position.z);

	// セルが変わらなければ処理を終わる
	if( previous_cell_x == cell_x && previous_cell_y == cell_y && previous_cell_z == cell_z)
	{
		return;
	}

	// 今いるセルのリストを削除する
	if( unit->_previous != nullptr)
	{
		unit->_previous->_next = nullptr;
	}

	if( unit->_next != nullptr)
	{
		unit->_next->_previous = unit->_previous;
	}

	// リストの先頭であれば削除
	if( _cells[previous_cell_x][previous_cell_y][previous_cell_z] == unit )
	{
		_cells[previous_cell_x][previous_cell_y][previous_cell_z] = unit->_next;
	}

	// 新しいセルに追加する
	AddUnit(unit, position);
}

//=============================================================================
// セルの算出
s32 SpaceGrid::CellCalculation(fx32 position)
{
	s32 cell = static_cast<s32>(position / kSizeCell);
	if( cell <= 0 )
	{
		cell = 0;
	}
	if( cell >= kSizeCell *kMaxCell )
	{
		cell = kMaxCell - 1;
	}

	return cell;
}