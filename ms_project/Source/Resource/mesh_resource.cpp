//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// メッシュリソース
//
// Created by Ryusei Kajiya on 20151102
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Resource/mesh_resource.h"
#include "Resource/Mesh/Mesh/mesh_factory_cube.h"
#include "Resource/Mesh/Mesh/mesh_factory_sprite.h"
#include "Resource/Mesh/Mesh/mesh_factory_mesh_field.h"
#include "Resource/Mesh/Mesh/mesh_factory_water_cylinder.h"
#include "Resource/Mesh/Mesh/mesh_factory_water_cylinder_back.h"

//=============================================================================
// 作成
void MeshResource::Create(MESH_RESOURE_ID id, RendererDevice* device)
{
	MeshBuffer* mesh = nullptr;
	switch( id )
	{
		case MESH_RESOURE_BOX:
		{
			MeshFactoryCube mesh_factory;
			mesh = mesh_factory.Create(device);
			break;
		}
		case MESH_RESOURE_SPRITE:
		{
			MeshFactorySprite mesh_factory;
			mesh = mesh_factory.Create(device);
			break;
		}
		case MESH_RESOURE_MESH_FIELD:
		{
			MeshFactoryMeshField mesh_factory;
			mesh = mesh_factory.Create(device);
			break;
		}
		case MESH_RESOURE_WATER_CYLINDER:
		{
			MeshFactoryWaterCylinder mesh_factory;
			mesh = mesh_factory.Create(device);
			break;
		}
		case MESH_RESOURE_WATER_CYLINDER_BACK:
		{
			MeshFactoryWaterCylinderBack mesh_factory;
			mesh = mesh_factory.Create(device);
			break;
		}
		default:
		{
			break;
		}
	}
	if( _resource_box->Add(mesh, id) == false )
	{
		SafeDelete(mesh);
	}
	
}

//=============================================================================
// 全削除
void MeshResource::Clear()
{
	for( auto it = _resource_box->Begin(); it != _resource_box->End(); ++it )
	{
		SafeDelete(it->second);
	}
}

//=============================================================================
// 取得
MeshBuffer* MeshResource::Get(MESH_RESOURE_ID id)
{
	return _resource_box->Get(id);
}
