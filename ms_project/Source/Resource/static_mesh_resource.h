//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Staticメッシュリソース
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
// スタティックメッシュリソースID
enum STATIC_MESH_RESOURE_ID
{
	STATIC_MESH_RESOURE_BILL_000 = 0,
	STATIC_MESH_RESOURE_BILL_001,
	STATIC_MESH_RESOURE_BILL_002,
	STATIC_MESH_RESOURE_BILL_003,
	STATIC_MESH_RESOURE_BILL_HAIKEI,
	STATIC_MESH_RESOURE_CLOUD_000,
	STATIC_MESH_RESOURE_CLOUD_001,
	STATIC_MESH_RESOURE_CLOUD_002,
	STATIC_MESH_RESOURE_BILL_001_LOW,
	STATIC_MESH_RESOURE_BILL_002_LOW,
	STATIC_MESH_RESOURE_ROAD
};

//*****************************************************************************
// クラス設計
class StaticMeshResource : public Resource<std::vector<MeshBuffer*>, STATIC_MESH_RESOURE_ID>
{
public:
	StaticMeshResource(){}
	virtual ~StaticMeshResource(){ Clear(); }

	// 作成
	void Create(STATIC_MESH_RESOURE_ID id, RendererDevice* device) override;
	// 全削除
	void Clear() override;
	// 取得
	std::vector<MeshBuffer*> Get(STATIC_MESH_RESOURE_ID id) override;
};