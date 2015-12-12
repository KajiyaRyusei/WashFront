//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// アニメーションリソース
//
// Created by Ryusei Kajiya on 20151211
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Resource/resource.h"
#include "Data/data_oaf.h"

//*****************************************************************************
// テクスチャリソースID
enum ANIMATION_RESOURE_ID
{
	ANIMATION_RESOURE_STANCE = 0,
	ANIMATION_RESOURE_SHOT
};

//*****************************************************************************
// クラス設計
class AnimationResource : public Resource<data::ObjectAnimationFile*, ANIMATION_RESOURE_ID>
{
public:

	AnimationResource(){}
	virtual ~AnimationResource(){ Clear(); }

	// 作成
	void Create(ANIMATION_RESOURE_ID id, RendererDevice* device) override
	{
		UNREFERENCED_PARAMETER(id);
		UNREFERENCED_PARAMETER(device);
	};
	// 作成
	void Create(ANIMATION_RESOURE_ID id, u32 mesh_list_size);
	// 全削除
	void Clear() override;
	// 取得
	data::ObjectAnimationFile* Get(ANIMATION_RESOURE_ID id) override;
};