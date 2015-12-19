//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 水しぶきのオブジェクトプール
// 
// Created by Ryusei Kajiya on 20151125
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Unit/unit.h"
#include "water_spray.h"

//*****************************************************************************
// 前方宣言
class MeshBuffer;
class ShaderWaterSpray;

//*****************************************************************************
// クラス設計
class WaterSprayPool : public Unit
{
public:
	WaterSprayPool(Application* application, World* world);
	virtual ~WaterSprayPool();

	// 作成
	virtual void Create(
		const D3DXVECTOR3& position,
		const fx32 rotation);

	// アニメーション:描画も兼ねてる。
	virtual void Animate();

	virtual void Initialize() override{};
	virtual void Finalize() override{};
	virtual void Update() override{};
	virtual void Draw() override{};
	virtual void CollisionUpdate() override{};

private:

	static const u32 kPoolSize = 30;
	WaterSpray _particles[kPoolSize];
	WaterSpray* _first_available;
	MeshBuffer* _mesh;
	D3DXMATRIX _spray_matrices[kPoolSize];
	ShaderWaterSpray* _shader;
	LPDIRECT3DTEXTURE9 _albedo_map;

};
