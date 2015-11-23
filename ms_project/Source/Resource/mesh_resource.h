//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// メッシュリソース
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
// メッシュリソースID
enum MESH_RESOURE_ID
{
	MESH_RESOURE_BOX = 0,
	MESH_RESOURE_SPRITE,
	MESH_RESOURE_MESH_FIELD,
	MESH_RESOURE_WATER_CYLINDER,
	MESH_RESOURE_WATER_CYLINDER_BACK,
};

//*****************************************************************************
// クラス設計
class MeshResource : public Resource<MeshBuffer*, MESH_RESOURE_ID>
{
public:
	MeshResource(){}
	virtual ~MeshResource(){ Clear(); }

	// 作成
	void Create(MESH_RESOURE_ID id, RendererDevice* device) override;
	// 全削除
	void Clear() override;
	// 取得
	MeshBuffer* Get(MESH_RESOURE_ID id) override;
};