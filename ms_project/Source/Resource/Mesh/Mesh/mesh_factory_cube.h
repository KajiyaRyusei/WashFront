//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// キューブメッシュ作成
// 
// 8頂点しかないので法線とUVがあってないと思う
// 
// Created by Ryusei Kajiya on 20151022
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "mesh_factory.h"

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
};