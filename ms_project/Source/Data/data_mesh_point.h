//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���b�V���|�C���g
//
// Created by Ryusei Kajiya on 20151123
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "DevelopTool/develop_tool_manager.h"

namespace data
{
	//*****************************************************************************
	// �\���̒�`
	struct MeshPoint
	{
	public:

		MeshPoint(
			const D3DXVECTOR3& position_data,
			const D3DXVECTOR3& scale_data,
			const D3DXVECTOR3& rotation_data,
			const u32 vertex_size,
			const D3DXVECTOR3* point_array,
			const D3DXVECTOR3* normal_array) :
			position(position_data),
			scale(scale_data),
			rotation(rotation_data),
			size_point(vertex_size)
		{
			points = new D3DXVECTOR3[vertex_size];
			dirt_level = new u8[vertex_size];
			attitudes = new fx32[vertex_size];
			for( u32 i = 0; i < size_point; ++i )
			{
				dirt_level[i] = 0;
				points[i] = point_array[i];
			}
			CalculationPointAndAttitudes(normal_array);
		}

		virtual ~MeshPoint()
		{
			SafeDeleteArray(points);
			SafeDeleteArray(dirt_level);
			SafeDeleteArray(attitudes);
		}

		D3DXVECTOR3 position;
		D3DXVECTOR3 scale;
		D3DXVECTOR3 rotation;
		D3DXVECTOR3* points;
		fx32* attitudes;
		u32 size_point;
		u8* dirt_level;

		// �p���p�N�H�[�^�j�I���ƍ��W�v�Z
		void CalculationPointAndAttitudes(const D3DXVECTOR3* normal_array)
		{
			D3DXMATRIX world_matrix, rotation_matrix, tranlation_matrix, scale_matrix;
			for( u32 i = 0; i < size_point; ++i )
			{
				D3DXVECTOR4 transform;
				D3DXMatrixScaling(&scale_matrix, scale.x, scale.y, scale.z);
				D3DXMatrixRotationYawPitchRoll(&rotation_matrix, rotation.y, rotation.x, rotation.z);
				D3DXMatrixTranslation(&tranlation_matrix, position.x, position.y, position.z);
				world_matrix = rotation_matrix *scale_matrix* tranlation_matrix;

				// ���W�v�Z
				D3DXVec3Transform(&transform, &points[i], &world_matrix);
				points[i].x = transform.x;
				points[i].y = transform.y;
				points[i].z = transform.z;

				// �p���p��]
				attitudes[i] = atan2(normal_array[i].x, normal_array[i].z);
			}
		}
	};
};

