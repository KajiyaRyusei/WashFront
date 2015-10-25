//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ��Ԋi�q : ��ԕ���
// 
// Created by Ryusei Kajiya on 20151023
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
				for( s32 z = 0; z < kMaxCell; ++z )
				{
					_cells[x][y][z] = nullptr;
				}
			}
		}
	}

	virtual ~SpaceGrid()
	{

	}

	// ���j�b�g�̑���
	void HandleUnit(Unit* unit, Unit* other_unit);

	// �}�X�ڂ̃��j�b�g����
	void HandleCell(s32 x, s32 y, s32 z);

	// ���j�b�g�̒ǉ�
	void AddUnit(Unit* unit, D3DXVECTOR3 position);

	// ���j�b�g�̈ړ�
	void MoveUnit(Unit* unit, D3DXVECTOR3 position, D3DXVECTOR3 previous_position);

	// ���j�b�g�̃N���A
	void Clear();

	// �Z���̃T�C�Y
	static const s32 S_GetMaxCell() { return kMaxCell; }

	// �Z���̐�
	static const s32 S_GetSizeCell() { return kSizeCell; }

private:

	static const s32 kMaxCell = 5;
	static const s32 kSizeCell = 50;
	static const s32 kAttackDistance = 5;

	Unit* _cells[kMaxCell][kMaxCell][kMaxCell];

	// �g�p������}�b�v
	// LPDIRECT3DCUBETEXTURE9 _diffuse_cube_maps[kMaxCell][kMaxCell][kMaxCell];
	// LPDIRECT3DCUBETEXTURE9 _specular_cube_maps[kMaxCell][kMaxCell][kMaxCell];

	// �Z���̎Z�o
	s32 CellCalculation(fx32 position);
};
