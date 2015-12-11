//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// スタティックメッシュ作成
// 
// Created by Ryusei Kajiya on 20151014
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
struct VERTEX_SMO
{
	D3DXVECTOR3	position;	// 頂点
	D3DXVECTOR3	normal;		// 法線ベクトル
	D3DXVECTOR2	texcoord;	// テクスチャ座標
	D3DXVECTOR3	tangent;	// 接ベクトル
	fx32 cleanliness;		// 汚れ具合
};

//*****************************************************************************
// クラス設計
class MeshFactorySMO : MeshFactory
{
public:

	// これを呼んでも意味ないよ
	virtual MeshBuffer* Create(RendererDevice* renderer_device) override{ UNREFERENCED_PARAMETER(renderer_device); return nullptr; }

	// こっち呼んでね
	void Create(
		RendererDevice* renderer_device,
		std::string file_name,
		std::vector<MeshBuffer*>& mesh_list);

private:
	
	// 従法線と接ベクトルを求める
	void TangentCompute(MeshBuffer* mesh);
};