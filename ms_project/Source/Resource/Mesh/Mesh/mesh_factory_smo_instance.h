//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// インスタンススタティックメッシュ作成
// 
// Created by Ryusei Kajiya on 20151215
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "mesh_factory.h"

//*****************************************************************************
// 3D用頂点フォーマット
struct VERTEX_SMO_INSTANCE
{
	D3DXVECTOR3	position;	// 頂点
	D3DXVECTOR3	normal;		// 法線ベクトル
	D3DXVECTOR2	texcoord;	// テクスチャ座標
	D3DXVECTOR3	tangent;	// 接ベクトル
};

//*****************************************************************************
// クラス設計
class MeshFactorySMOInstance : MeshFactory
{
public:

	// これを呼んでも意味ないよ
	virtual MeshBuffer* Create(RendererDevice* renderer_device) override{ UNREFERENCED_PARAMETER(renderer_device); return nullptr; }

	// こっち呼んでね
	void Create(
		RendererDevice* renderer_device,
		std::string file_name,
		std::vector<MeshBuffer*>& mesh_list,
		u32 instance_max);

	// 行列の登録
	void RegisterMatrix(const D3DXMATRIX* matrices, u32 instance_count, std::vector<MeshBuffer*>& mesh_list);

private:
	
	// 従法線と接ベクトルを求める
	void TangentCompute(MeshBuffer* mesh);

	u32 _instance_max;
};