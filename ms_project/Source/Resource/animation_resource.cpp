//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// アニメーションリソース
//
// Created by Ryusei Kajiya on 20151211
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Resource/animation_resource.h"

//*****************************************************************************
// 定数
namespace
{
	static char* kAnimationResourceNames[] =
	{
		"Data/Animation/new_standby60.oaf",
		"Data/Animation/new_shoot.oaf",
	};
}

//=============================================================================
// 作成
void AnimationResource::Create(ANIMATION_RESOURE_ID id, u32 mesh_list_size)
{
	data::ObjectAnimationFile *animation = new data::ObjectAnimationFile;
	animation->LoadAnimationFile(kAnimationResourceNames[id], mesh_list_size);

	if( _resource_box->Add(animation, id) == false )
	{
		animation->UnLoadAnimationFile();
		SafeDelete(animation);
	}
}

//=============================================================================
// 全削除
void AnimationResource::Clear()
{
	for( auto it = _resource_box->Begin(); it != _resource_box->End();++it )
	{
		it->second->UnLoadAnimationFile();
		SafeDelete(it->second);
	}
}

//=============================================================================
// 取得
data::ObjectAnimationFile* AnimationResource::Get(ANIMATION_RESOURE_ID id)
{
	return _resource_box->Get(id);
}
