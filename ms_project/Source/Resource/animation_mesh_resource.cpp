//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Animationメッシュリソース
//
// Created by Ryusei Kajiya on 20151102
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Resource/animation_mesh_resource.h"
#include "Resource/Mesh/Mesh/mesh_factory_amo.h"

//*****************************************************************************
// 定数
namespace
{
	static const char* kAnimationMeshResourceNames[] =
	{
		"Data/AnimationModel/ojianime.amo",
		"Data/AnimationModel/weapon_01.amo"
	};
}

//=============================================================================
// 作成
void AnimationMeshResource::Create(ANIMATION_MESH_RESOURE_ID id, RendererDevice* device)
{
	// メッシュの作成
	MeshFactoryAMO mesh_factory;
	std::vector<MeshBuffer*> mesh_list;
	mesh_factory.Create(device, kAnimationMeshResourceNames[id], mesh_list);
	if( _resource_box->Add(mesh_list, id) == false )
	{
		for( auto mesh : mesh_list )
		{
			SafeDelete(mesh);
		}
	}
}

//=============================================================================
// 全削除
void AnimationMeshResource::Clear()
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
// 取得
std::vector<MeshBuffer*> AnimationMeshResource::Get(ANIMATION_MESH_RESOURE_ID id)
{
	return _resource_box->Get(id);
}
