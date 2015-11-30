//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// キューブメッシュ作成
// 
// Created by Ryusei Kajiya on 20151103
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
struct VERTEX_CUBE
{
	D3DXVECTOR3	position;	// 頂点
	D3DXVECTOR3	normal;		// 法線ベクトル
	D3DXVECTOR2	texcoord;	// テクスチャ座標
	D3DXVECTOR3	tangent;	// 接ベクトル
	D3DXVECTOR3	binormal;	// 従法線
};
//*****************************************************************************
// クラス設計
class MeshFactoryCube : MeshFactory
{
public:
	virtual MeshBuffer* Create(RendererDevice* renderer_device) override;

private:

	// 法線を中心から放射状につける
	void NormalComputeSlanting(MeshBuffer* mesh);
	// 法線を面からまっすぐにつける
	void NormalComputeStraight(MeshBuffer* mesh);
	// 従法線と接ベクトルを求める
	void TangentCompute(MeshBuffer* mesh);
};