//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 空間格子 : 空間分割
// 
// Created by Ryusei Kajiya on 20151023
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

	// ユニットの操作
	void HandleUnit(Unit* unit, Unit* other_unit);

	// マス目のユニット操作
	void HandleCell(s32 x, s32 y, s32 z);

	// ユニットの追加
	void AddUnit(Unit* unit, D3DXVECTOR3 position);

	// ユニットの移動
	void MoveUnit(Unit* unit, D3DXVECTOR3 position, D3DXVECTOR3 previous_position);

	// ユニットのクリア
	void Clear();

	// セルのサイズ
	static const s32 S_GetMaxCell() { return kMaxCell; }

	// セルの数
	static const s32 S_GetSizeCell() { return kSizeCell; }

private:

	static const s32 kMaxCell = 5;
	static const s32 kSizeCell = 50;
	static const s32 kAttackDistance = 5;

	Unit* _cells[kMaxCell][kMaxCell][kMaxCell];

	// 使用する環境マップ
	// LPDIRECT3DCUBETEXTURE9 _diffuse_cube_maps[kMaxCell][kMaxCell][kMaxCell];
	// LPDIRECT3DCUBETEXTURE9 _specular_cube_maps[kMaxCell][kMaxCell][kMaxCell];

	// セルの算出
	s32 CellCalculation(fx32 position);
};
