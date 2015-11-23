//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// メッシュポイント
//
// Created by Ryusei Kajiya on 20151123
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "DevelopTool/develop_tool_manager.h"

namespace data
{
	//*****************************************************************************
	// 構造体定義
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
			attitudes = new D3DXQUATERNION[vertex_size];
			for( u32 i = 0; i < size_point; ++i )
			{
				points[i] = point_array[i];
			}
			CalculationPointAndAttitudes(normal_array);
		}

		virtual ~MeshPoint()
		{
			SafeDeleteArray(points);
			SafeDeleteArray(attitudes);
		}

		D3DXVECTOR3 position;
		D3DXVECTOR3 scale;
		D3DXVECTOR3 rotation;
		D3DXVECTOR3* points;
		D3DXQUATERNION* attitudes;
		u32 size_point;

		// 姿勢用クォータニオンと座標計算
		void CalculationPointAndAttitudes(const D3DXVECTOR3* normal_array)
		{
			D3DXMATRIX world_matrix, rotation_matrix, tranlation_matrix, scale_matrix;
			D3DXVECTOR3 object_up(0.f,1.f,0.f);
			for( u32 i = 0; i < size_point; ++i )
			{
				D3DXVECTOR4 transform;
				D3DXMatrixScaling(&scale_matrix, scale.x, scale.y, scale.z);
				D3DXMatrixRotationYawPitchRoll(&rotation_matrix, rotation.y, rotation.x, rotation.z);
				D3DXMatrixTranslation(&tranlation_matrix, position.x, position.y, position.z);
				world_matrix = rotation_matrix *scale_matrix* tranlation_matrix;

				// 座標計算
				D3DXVec3Transform(&transform, &points[i], &world_matrix);
				points[i].x = transform.x;
				points[i].y = transform.y;
				points[i].z = transform.z;

				// 姿勢用クォータニオン計算
				D3DXVec3Transform(&transform, &normal_array[i], &world_matrix);
				D3DXVECTOR3 transform_vec3(transform);
				D3DXVECTOR3 axis;
				D3DXVec3Cross(&axis, &object_up, &transform_vec3);
				fx32 cos_sita = D3DXVec3Dot(&object_up, &transform_vec3);
				fx32 sita = acos(cos_sita);
				D3DXQuaternionRotationAxis(&attitudes[i], &axis, sita);
			}
		}
	};
};

