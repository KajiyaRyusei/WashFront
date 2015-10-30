//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// BOX
//
// Created by Ryusei Kajiya on 20151028
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
	struct Box
	{
	public:
		Box() : 
			position(0.f,0.f,0.f),
			size(1.f,1.f,1.f),
			rotation(0.f,0.f,0.f)
		{
			Calculation8Point();
		}

		D3DXVECTOR3 position;
		D3DXVECTOR3 size;
		D3DXVECTOR3 rotation;

		D3DXVECTOR3 points[8];

		void DebugDraw()
		{
			DebugBox& box = Reference::GetInstance().GetDevelopToolManager()->GetDebugBox();

			box.RegisteBox(
				D3DXVECTOR3(size.x / 2.f, size.y / 2.f, size.z/ 2.f),
				position,
				rotation);
		}

		void Calculation8Point()
		{
			D3DXMATRIX world_matrix,rotation_matrix, tranlation_matrix;

			points[0] = D3DXVECTOR3(-size.x,  size.y,   size.z);
			points[1] = D3DXVECTOR3( size.x,  size.y,   size.z);
			points[2] = D3DXVECTOR3(-size.x, -size.y,   size.z);
			points[3] = D3DXVECTOR3( size.x, -size.y,   size.z);
			points[4] = D3DXVECTOR3(-size.x,  size.y,  -size.z);
			points[5] = D3DXVECTOR3( size.x,  size.y,  -size.z);
			points[6] = D3DXVECTOR3(-size.x, -size.y,  -size.z);
			points[7] = D3DXVECTOR3( size.x, -size.y,  -size.z);

			for( int i = 0; i < 8; ++i )
			{
				D3DXVECTOR4 transform;
				D3DXMatrixRotationYawPitchRoll(&rotation_matrix, rotation.y, rotation.x, rotation.z);
				D3DXMatrixTranslation(&tranlation_matrix, position.x, position.y, position.z);
				world_matrix = rotation_matrix * tranlation_matrix;

				D3DXVec3Transform(&transform, &points[i], &world_matrix);

				points[i].x = transform.x;
				points[i].y = transform.y;
				points[i].z = transform.z;
			}
		}
	};
};

