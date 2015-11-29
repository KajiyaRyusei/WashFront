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