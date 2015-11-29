//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// インスタンススプライト
//
// Created by Ryusei Kajiya on 20151128
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
struct VERTEX_SPRITE_INSTANCE
{
	D3DXVECTOR3	position;	// 頂点
	D3DXVECTOR3	normal;		// 法線ベクトル
	D3DXVECTOR2	texcoord;	// テクスチャ座標
};

//*****************************************************************************
// クラス設計
class MeshFactorySpriteInstance : MeshFactory
{
public:
	MeshFactorySpriteInstance() : _instance_max(10){}
	MeshBuffer* Create(RendererDevice* renderer_device,u32 instance_count);
	virtual MeshBuffer* Create(RendererDevice* renderer_device) override;
	// 行列の登録
	void RegisterMatrix(const D3DXMATRIX* matrices, u32 instance_count, MeshBuffer* mesh);

private:

	u32 _instance_max;
};