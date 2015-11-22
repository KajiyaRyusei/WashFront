//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// スクリーン用ユニット : 2Dオブジェクト
// 
// Created by Ryusei Kajiya on 20151012
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
class Shader2D;
class MeshBuffer;

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
	Shader2D* _shader;

	// メッシュ
	MeshBuffer* _mesh;

	//テクスチャ
	LPDIRECT3DTEXTURE9 _texture;


};