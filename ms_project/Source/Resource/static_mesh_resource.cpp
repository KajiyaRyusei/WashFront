//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Static���b�V�����\�[�X
//
// Created by Ryusei Kajiya on 20151102
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Resource/static_mesh_resource.h"
#include "Resource/Mesh/Mesh/mesh_factory_smo.h"
//*****************************************************************************
// �萔
namespace
{
	static const char* kStaticMeshResourceNames[] =
	{
		"Data/StaticModel/new_biru_1.smo"
	};
}

//=============================================================================
// �쐬
void StaticMeshResource::Create(STATIC_MESH_RESOURE_ID id, RendererDevice* device)
{
	// ���b�V���̍쐬
	MeshFactorySMO mesh_factory;
	std::vector<MeshBuffer*> mesh_list;
	mesh_factory.Create(device, kStaticMeshResourceNames[id], mesh_list);
	if( _resource_box->Add(mesh_list, id) == false )
	{
		for( auto mesh : mesh_list )
		{
			SafeDelete(mesh);
		}
	}
}

//=============================================================================
// �S�폜
void StaticMeshResource::Clear()
{
	for( auto it = _resource_box->Begin(); it != _resource_box->End(); ++it )
	{
		for( auto mesh : it->second )
		{
			SafeDelete(mesh);
		}
	}
}

//=============================================================================
// �擾
std::vector<MeshBuffer*> StaticMeshResource::Get(STATIC_MESH_RESOURE_ID id)
{
	return _resource_box->Get(id);
}
