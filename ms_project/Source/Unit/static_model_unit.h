//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// スタティックモデル
// 
// Created by Ryusei Kajiya on 20151014
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "unit.h"

//*****************************************************************************
// 前方宣言
class ShaderLambert;
class MeshBuffer;

//*****************************************************************************
// クラス設計
class StaticModelUnit : public Unit
{
public:

	StaticModelUnit(Application* application, SpaceGrid* grid) : Unit(application, grid)
	{
		Initialize();
	}
	virtual ~StaticModelUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:

	// シェーダー
	ShaderLambert* _shader;

	// メッシュ
	std::vector<MeshBuffer*> _mesh_list;
};