//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ��Ԋi�q : ��ԕ���
// 
// Created by Ryusei Kajiya on 20151023
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "space_grid.h"

#include "Unit/unit.h"

//=============================================================================
// ���j�b�g�̑���
void SpaceGrid::HandleUnit(Unit* unit, Unit* other_unit)
{
	while( other_unit != nullptr)
	{
		// ��̓͂��͈͕͂ʂ̃Z���ł�����
		if( fabs(D3DXVec3Length(&unit->_world_position) 
			- D3DXVec3Length(&other_unit->_world_position)) < kAttackDistance )
		{
			//HandleAtack();
		}
		// ��������̏���:�Փ˔���Ƃ�AI
		UNREFERENCED_PARAMETER(unit);

		// ���̃��j�b�g��
		other_unit = other_unit->_next;
	}
}

//=============================================================================
// �}�X�ڂ̃��j�b�g����
void SpaceGrid::HandleCell(s32 x, s32 y,s32 z)
{
	Unit* unit = _cells[x][y][z];

	while( unit != nullptr)
	{
		HandleUnit(unit,unit->_next);

		// �אڂ���Z������������B
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
// Unit�̒ǉ�
void SpaceGrid::AddUnit(Unit* unit, D3DXVECTOR3 position)
{
	// �ǂ̃Z���������o
	s32 cell_x = CellCalculation(position.x);
	s32 cell_y = CellCalculation(position.y);
	s32 cell_z = CellCalculation(position.z);

	// �����Ă���Z���̐擪�ɒǉ�
	unit->_previous = nullptr;
	unit->_next = _cells[cell_x][cell_y][cell_z];
	_cells[cell_x][cell_y][cell_z] = unit;

	if( unit->_next != nullptr)
	{
		unit->_next->_previous = unit;
	}
}

//=============================================================================
// Unit�̈ړ�
void SpaceGrid::MoveUnit(Unit* unit, D3DXVECTOR3 position, D3DXVECTOR3 previous_position)
{
	// �O�̃Z�����Z�o
	s32 previous_cell_x = CellCalculation(previous_position.x);
	s32 previous_cell_y = CellCalculation(previous_position.y);
	s32 previous_cell_z = CellCalculation(previous_position.z);

	// ���݂̃Z�����Z�o
	s32 cell_x = CellCalculation(position.x);
	s32 cell_y = CellCalculation(position.y);
	s32 cell_z = CellCalculation(position.z);

	// �Z�����ς��Ȃ���Ώ������I���
	if( previous_cell_x == cell_x && previous_cell_y == cell_y && previous_cell_z == cell_z)
	{
		return;
	}

	// ������Z���̃��X�g���폜����
	if( unit->_previous != nullptr)
	{
		unit->_previous->_next = nullptr;
	}

	if( unit->_next != nullptr)
	{
		unit->_next->_previous = unit->_previous;
	}

	// ���X�g�̐擪�ł���΍폜
	if( _cells[previous_cell_x][previous_cell_y][previous_cell_z] == unit )
	{
		_cells[previous_cell_x][previous_cell_y][previous_cell_z] = unit->_next;
	}

	// �V�����Z���ɒǉ�����
	AddUnit(unit, position);
}

//=============================================================================
// �Z���̎Z�o
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