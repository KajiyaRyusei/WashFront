//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 2D�i�q
// 
// Created by Ryusei Kajiya on 20151028
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "World/grid_2D.h"
#include "Unit/unit.h"

//=============================================================================
// �}�X�ڂ̃��j�b�g����
void Grid2D::HandleCell(s32 x, s32 z)
{
	Unit* unit = _cells[x][z];

	while( unit != nullptr)
	{
		HandleUnit(unit,unit->_next);

		// �אڂ���Z������������B : �l���������Ă܂���B
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
// Unit�̒ǉ�
void Grid2D::AddUnit(Unit* unit, const data::Position& position)
{
	// �ǂ̃Z���������o
	s32 cell_x = CellCalculation(position.current.x);
	s32 cell_z = CellCalculation(position.current.z);

	// �����Ă���Z���̐擪�ɒǉ�
	unit->_previous = nullptr;
	unit->_next = _cells[cell_x][cell_z];
	_cells[cell_x][cell_z] = unit;

	if( unit->_next != nullptr)
	{
		unit->_next->_previous = unit;
	}
}
//=============================================================================
// Unit�̈ړ�
void Grid2D::MoveUnit(Unit* unit, const data::Position& position)
{

	// �O�̃Z�����Z�o
	s32 previous_cell_x = CellCalculation(unit->_position.previous.x);
	s32 previous_cell_z = CellCalculation(unit->_position.previous.z);

	// ���݂̃Z�����Z�o
	s32 cell_x = CellCalculation(position.current.x);
	s32 cell_z = CellCalculation(position.current.z);

	// �Z�����ς��Ȃ���Ώ������I���
	if( previous_cell_x == cell_x && previous_cell_z == cell_z)
	{
		return;
	}

	// �O��̍��W��ۑ�
	unit->_position.previous = position.current;

	// ������Z���̃��X�g���폜����
	if( unit->_previous != nullptr)
	{
		unit->_previous->_next = unit->_next;
	}

	if( unit->_next != nullptr)
	{
		unit->_next->_previous = unit->_previous;
	}

	// ���X�g�̐擪�ł���΍폜
	if( _cells[previous_cell_x][previous_cell_z] == unit )
	{
		_cells[previous_cell_x][previous_cell_z] = unit->_next;
	}

	// �V�����Z���ɒǉ�����
	AddUnit(unit, position);

	
}

//=============================================================================
// ���W��cell��index��Ԃ�
void Grid2D::SelfCoordinatesCell(
	s32* cell_x,
	s32* cell_z,
	const data::Position& position)
{
	// ���݂̃Z�����Z�o
	*cell_x = CellCalculation(position.current.x);
	*cell_z = CellCalculation(position.current.z);
}

//=============================================================================
// �Z���̎Z�o
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