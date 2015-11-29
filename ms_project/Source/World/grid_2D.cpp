//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 2D格子
// 
// Created by Ryusei Kajiya on 20151028
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "World/grid_2D.h"
#include "Unit/unit.h"

//=============================================================================
// マス目のユニット操作
void Grid2D::HandleCell(s32 x, s32 z)
{
	Unit* unit = _cells[x][z];

	while( unit != nullptr)
	{
		HandleUnit(unit,unit->_next);

		// 隣接するセルも処理する。 : 四方しかしてません。
		if( x > 0)
		{
			HandleUnit(unit, _cells[x - 1][z]);
		}

		if( x < kMaxCell -1 )
		{
			HandleUnit(unit, _cells[x + 1][z]);
		}

		if( z > 0)
		{
			HandleUnit(unit, _cells[x][z - 1]);
		}

		if( z < kMaxCell - 1 )
		{
			HandleUnit(unit, _cells[x][z + 1]);
		}

		unit = unit->_next;
	}
}

//=============================================================================
// Unitの追加
void Grid2D::AddUnit(Unit* unit, const data::Position& position)
{
	// どのセルかを検出
	s32 cell_x = CellCalculation(position.current.x);
	s32 cell_z = CellCalculation(position.current.z);

	// 入っているセルの先頭に追加
	unit->_previous = nullptr;
	unit->_next = _cells[cell_x][cell_z];
	_cells[cell_x][cell_z] = unit;

	if( unit->_next != nullptr)
	{
		unit->_next->_previous = unit;
	}
}
//=============================================================================
// Unitの移動
void Grid2D::MoveUnit(Unit* unit, const data::Position& position)
{

	// 前のセルを算出
	s32 previous_cell_x = CellCalculation(unit->_position.previous.x);
	s32 previous_cell_z = CellCalculation(unit->_position.previous.z);

	// 現在のセルを算出
	s32 cell_x = CellCalculation(position.current.x);
	s32 cell_z = CellCalculation(position.current.z);

	// セルが変わらなければ処理を終わる
	if( previous_cell_x == cell_x && previous_cell_z == cell_z)
	{
		return;
	}

	// 前回の座標を保存
	unit->_position.previous = position.current;

	// 今いるセルのリストを削除する
	if( unit->_previous != nullptr)
	{
		unit->_previous->_next = unit->_next;
	}

	if( unit->_next != nullptr)
	{
		unit->_next->_previous = unit->_previous;
	}

	// リストの先頭であれば削除
	if( _cells[previous_cell_x][previous_cell_z] == unit )
	{
		_cells[previous_cell_x][previous_cell_z] = unit->_next;
	}

	// 新しいセルに追加する
	AddUnit(unit, position);

	
}

//=============================================================================
// 座標のcellのindexを返す
void Grid2D::SelfCoordinatesCell(
	s32* cell_x,
	s32* cell_z,
	const data::Position& position)
{
	// 現在のセルを算出
	*cell_x = CellCalculation(position.current.x);
	*cell_z = CellCalculation(position.current.z);
}

//=============================================================================
// セルの算出
s32 Grid2D::CellCalculation(fx32 position)
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