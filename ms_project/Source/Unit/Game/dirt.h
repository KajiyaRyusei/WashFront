//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// よごれ
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
class ShaderPBLStatic;
class MeshBuffer;

//*****************************************************************************
// クラス設計
class DirtUnit : public Unit
{
public:

	DirtUnit(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}

	virtual ~DirtUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;
	virtual void CollisionSphere() override;

	// 座標設定
	void SetPosition(const D3DXVECTOR3& position);

private:

	// シェーダー
	ShaderPBLStatic* _shader;
	// メッシュ
	MeshBuffer* _mesh;
	// シェーダパラメーターの設定
	void SettingShaderParameter();
	data::World _world;

	D3DXMATRIX _matrix_world_view_projection;
	LPDIRECT3DCUBETEXTURE9 _diffuse_cube_map;
	LPDIRECT3DCUBETEXTURE9 _specular_cube_map;
	LPDIRECT3DTEXTURE9 _albedo_map;
	LPDIRECT3DTEXTURE9 _normal_map;
	bool _is_invisible;

};