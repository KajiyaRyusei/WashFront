//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 水シリンダー
//
// Created by Ryusei Kajiya on 20151114
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
struct VERTEX_WATER_CYLINDER
{
	D3DXVECTOR3	position;	// 頂点
	D3DXVECTOR3	normal;		// 法線ベクトル
	D3DXVECTOR2	texcoord;	// テクスチャ座標
	D3DXVECTOR3	tangent;	// 接ベクトル
	D3DXVECTOR3	binormal;	// 従法線
	fx32 weight[3];			// 重み
};

//*****************************************************************************
// クラス設計
class MeshFactoryWaterCylinder : MeshFactory
{
public:
	virtual MeshBuffer* Create(RendererDevice* renderer_device) override;

private:

	// 座標計算
	void PositionCompute(MeshBuffer* mesh);

	// 法線計算
	void NormalCompute(MeshBuffer* mesh);

	// 従法線と接ベクトルを求める
	void TangentCompute(MeshBuffer* mesh);

};