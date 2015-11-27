//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// インスタンスしたスプライト
// 
// Created by Ryusei Kajiya on 20151125
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
struct VERTEX_INSTANCE_SPRITE
{
	D3DXVECTOR3	position;	// 頂点
	D3DXVECTOR3	normal;		// 法線ベクトル
	D3DXVECTOR2	texcoord;	// テクスチャ座標
};

//*****************************************************************************
// クラス設計
class MeshFactoryInstanceSprite : MeshFactory
{
public:
	MeshFactoryInstanceSprite() : _instance_max(10){}
	virtual MeshBuffer* Create(RendererDevice* renderer_device) override;
	MeshBuffer* Create(RendererDevice* renderer_device, u32 instance_max)
	{
		_instance_max = instance_max;
		return Create(renderer_device);
	}

	void RegisterMatrix(const D3DXMATRIX* matrices, MeshBuffer* mesh);

private:
	u32 _instance_max;
};