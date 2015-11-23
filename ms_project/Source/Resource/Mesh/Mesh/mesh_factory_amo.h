//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// アニメーションメッシュ作成
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
struct VERTEX_AMO
{
	D3DXVECTOR3 position;		// 座標
	D3DXVECTOR3 normal;			// 法線
	D3DXVECTOR2 texcoord;		// テクスチャ座標
	fx32 weight[4];			// 重み
	u8 bone_index[4];// ボーンインデックス
};

//*****************************************************************************
// クラス設計
class MeshFactoryAMO : MeshFactory
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
	
};