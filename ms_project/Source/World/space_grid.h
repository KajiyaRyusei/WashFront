//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ��Ԋi�q : ��ԕ���
// 
// Created by Ryusei Kajiya on 20151009
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �O���錾
class Unit;

//*****************************************************************************
// �N���X�݌v
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

	// ���j�b�g�̑���
	void HandleUnit(Unit* unit, Unit* other_unit);

	// �}�X�ڂ̃��j�b�g����
	void HandleCell(s32 x, s32 y);

	// ���j�b�g�̒ǉ�
	void AddUnit(Unit* unit);

private:

	static const s32 kMaxCell = 10;
	static const s32 kSizeCell = 20;

	Unit* _cells[kMaxCell][kMaxCell];
};