//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �Փ˔���p�i�q : XZ
// 
// Created by Ryusei Kajiya on 20151028
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "World/collision_grid.h"
#include "Unit/unit.h"
#include "DevelopTool/develop_tool_manager.h"
#include "Collision/collision_system.h"

//*****************************************************************************
// �萔
namespace
{
	static const fx32 kAttackDistance = 50.f;
}

//=============================================================================
// ���j�b�g�̑���
void CollisionGrid::HandleUnit(Unit* unit, Unit* other_unit)
{
	while( other_unit != nullptr)
	{
		// ��̓͂��͈͕͂ʂ̃Z���ł�����
		D3DXVECTOR3 position_length_vector(unit->_position.current - other_unit->_position.current);
		fx32 position_length = D3DXVec3Length(&position_length_vector);
		// UNREFERENCED_PARAMETER(position_length);
		if( position_length < kAttackDistance )
		{
			if( other_unit ->_shpere != nullptr && 
				unit->_shpere != nullptr )
			{// ���Ƌ�
				if( collision::Sphrere2Sphrere(
					unit->_shpere->position,
					other_unit->_shpere->position,
					unit->_shpere->radius,
					other_unit->_shpere->radius) )
				{
					unit->CollisionSphere();
					other_unit->CollisionSphere();
				}
			}
			
			if( unit->_line != nullptr )
			{
				if( other_unit->_box != nullptr )
				{
					D3DXVECTOR3 impact_point;

					if( collision::Line2Box(
						&impact_point,
						unit->_line->start_point,
						unit->_line->end_point,
						other_unit->_box->points[0], other_unit->_box->points[1], other_unit->_box->points[2], other_unit->_box->points[3],
						other_unit->_box->points[4], other_unit->_box->points[5], other_unit->_box->points[6], other_unit->_box->points[7]) )
					{
						unit->CollisionLine(impact_point);
					}
				}
			}

			if( unit->_box != nullptr )
			{
				if( other_unit->_line != nullptr )
				{
					D3DXVECTOR3 impact_point;

					if( collision::Line2Box(
						&impact_point,
						other_unit->_line->start_point,
						other_unit->_line->end_point,
						unit->_box->points[0], unit->_box->points[1], unit->_box->points[2], unit->_box->points[3],
						unit->_box->points[4], unit->_box->points[5], unit->_box->points[6], unit->_box->points[7]) )
					{
						other_unit->CollisionLine(impact_point);
					}
				}
			}
		}

		// ���̃��j�b�g��
		other_unit = other_unit->_next;
	}
}

//=============================================================================
// �f�o�b�O�p�`��
void CollisionGrid::DebugDraw()
{
#ifndef RELEASE

	DebugLineBox& box = Reference::GetInstance().GetDevelopToolManager()->GetDebugLineBox();
	fx32 cell_size = static_cast<fx32>(S_GetSizeCell());
	s32 cell_max = S_GetMaxCell();

	for( s32 x = 0; x < cell_max; ++x )
	{
		for( s32 z = 0; z < cell_max; ++z )
		{
			box.RegisteBox(
				D3DXVECTOR3(cell_size / 2.f, cell_size / 2.f, cell_size / 2.f),
				D3DXVECTOR3(cell_size*x + (cell_size / 2.f), (cell_size / 2.f), cell_size*z + (cell_size / 2.f)),
				D3DXVECTOR3(0.f, 0.f, 0.f));
		}
	}

#endif
}
