//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 背景用天球
// 
// Created by Ryusei Kajiya on 20151022
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Unit/unit.h"
#include "Data/data_projection.h"

//*****************************************************************************
// 前方宣言
class ShaderBackGround;
class ShaderLambert;
class MeshBuffer;

//*****************************************************************************
// クラス設計
class BackGroundUnit : public Unit
{
public:

	BackGroundUnit(Application* application, SpaceGrid* grid) : Unit(application, grid)
	{
		Initialize();
	}
	virtual ~BackGroundUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:

	// シェーダー
	ShaderBackGround* _shader;
	//ShaderLambert* _shader;
	// メッシュ
	MeshBuffer* _mesh;

	// テクスチャ
	LPDIRECT3DCUBETEXTURE9 _texture;

};