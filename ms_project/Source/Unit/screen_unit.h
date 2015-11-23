//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// スクリーン用ユニット : 2Dオブジェクト
// 
// Created by Ryusei Kajiya on 20151102
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
<<<<<<< HEAD
class ShaderScreen;
=======
class Shader2D;
class MeshBuffer;
>>>>>>> origin/Mochizuki-desk

//*****************************************************************************
// クラス設計
class ScreenUnit : public Unit
{
public:

	ScreenUnit(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~ScreenUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override{}

	//テクスチャ作成
	void CreateTexture( LPCWSTR texture_filename );
	// 座標セット
	void SetPosition( D3DXVECTOR3 pos )
	{
		_position = pos;
	}
	// 大きさセット
	void SetScaling( D3DXVECTOR3 scale )
	{
		_scaling = scale;
	}

protected:
	//uv値
	D3DXVECTOR2 _texture_uv;

	//オフセット値
	D3DXVECTOR2 _texture_offset;

	//アルファ値
	float _texture_alpha;

	//ポジション
	D3DXVECTOR3 _position;

	//角度
	float _rotation;

	//スケール
	D3DXVECTOR3 _scaling;

private:

	// シェーダー
<<<<<<< HEAD
	ShaderScreen* _shader;
=======
	Shader2D* _shader;

	// メッシュ
	MeshBuffer* _mesh;

	//テクスチャ
	LPDIRECT3DTEXTURE9 _texture;


>>>>>>> origin/Mochizuki-desk
};