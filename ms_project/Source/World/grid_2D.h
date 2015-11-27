//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 2D�i�q
// 
// Created by Ryusei Kajiya on 20151028
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "Data/data_position.h"

//*****************************************************************************
// �O���錾
class Unit;

//*****************************************************************************
// �N���X�݌v
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

	// ���j�b�g�̑���
	virtual void HandleUnit(Unit* unit, Unit* other_unit) = 0;

	// �}�X�ڂ̃��j�b�g����
	void HandleCell(s32 x, s32 z);

	// ���j�b�g�̒ǉ�
	void AddUnit(Unit* unit, const data::Position& position);

	// ���j�b�g�̈ړ�
	void MoveUnit(Unit* unit, const data::Position& position);

	// ���W��cell��index��Ԃ�
	void SelfCoordinatesCell(
		s32* cell_x,
		s32* cell_z,
		const data::Position& position);

	// �Z���̃T�C�Y
	static const s32 S_GetMaxCell() { return kMaxCell; }

	// �Z���̐�
	static const s32 S_GetSizeCell() { return kSizeCell; }

	// ���̃Z���̒��S�|�C���g�������Ă���
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

	// �Z���̎Z�o
	s32 CellCalculation(fx32 position);
};
