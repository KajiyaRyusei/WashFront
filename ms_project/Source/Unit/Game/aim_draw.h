//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 描画用AIM
// 
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Unit/unit.h"
#include "Data/data_world.h"

//*****************************************************************************
// 前方宣言
class MeshBuffer;
class ShaderAim;

//*****************************************************************************
// クラス設計
class AimDrawUnit : public Unit
{
public:
	AimDrawUnit(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~AimDrawUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override{};

private:

	// シェーダー
	ShaderAim* _shader;
	// メッシュ
	MeshBuffer* _mesh;
	// テクスチャ
	LPDIRECT3DTEXTURE9 _albedo_map;
	data::World _world;
	D3DXMATRIX _matrix_world_view_projection;
	// 自分の位置を算出
	void CalculatePosition();
};