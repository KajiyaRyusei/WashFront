//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// 汚れの計算
// 
// Created by Ryusei Kajiya on 20151103
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Algorithm/dirt_math.h"
#include "Resource/Mesh/mesh_buffer.h"
#include "Resource/Mesh/Mesh/mesh_factory_mesh_field.h"

//*****************************************************************************
// よく使う関数群
namespace algo
{
	void DirtBasicTransformation(MeshBuffer* mesh)
	{
		UNREFERENCED_PARAMETER(mesh);
		//mesh->GetVertexBuffer(0)->Lock(0, 0, (void**)&vertex, 0);
	}
}