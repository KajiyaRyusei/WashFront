//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Animationメッシュリソース
//
// Created by Ryusei Kajiya on 20151102
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Resource/resource.h"

//*****************************************************************************
// 前方宣言
class MeshBuffer;

//*****************************************************************************
// アニメーションメッシュリソースID
enum ANIMATION_MESH_RESOURE_ID
{
	ANIMATION_MESH_RESOURE_GRANDPA = 0,
	ANIMATION_MESH_RESOURE_WEAPON_01,
};

//*****************************************************************************
// クラス設計
class AnimationMeshResource : public Resource<std::vector<MeshBuffer*>, ANIMATION_MESH_RESOURE_ID>
{
public:
	AnimationMeshResource(){}
	virtual ~AnimationMeshResource(){ Clear(); }
	// 作成
	void Create(ANIMATION_MESH_RESOURE_ID id, RendererDevice* device) override;
	// 全削除
	void Clear() override;
	// 取得
	std::vector<MeshBuffer*> Get(ANIMATION_MESH_RESOURE_ID id) override;
};