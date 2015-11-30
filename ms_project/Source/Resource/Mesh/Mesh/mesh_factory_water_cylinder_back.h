//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 水シリンダー後ろ用
//
// Created by Ryusei Kajiya on 20151123
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
struct VERTEX_WATER_CYLINDER_BACK
{
	D3DXVECTOR3	position;	// 座標
	D3DXVECTOR3	normal;		// 法線ベクトル
	D3DXVECTOR2	texcoord;	// テクスチャ座標
	D3DCOLOR color;			// 色
	D3DXVECTOR3	tangent;	// 接ベクトル
	D3DXVECTOR3	binormal;	// 従法線
};

//*****************************************************************************
// クラス設計
class MeshFactoryWaterCylinderBack : MeshFactory
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