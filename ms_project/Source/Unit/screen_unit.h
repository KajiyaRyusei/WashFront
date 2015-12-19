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
	
	// 座標セット
	virtual void SetPosition(D3DXVECTOR3 pos)
	{
		_position = pos;
	}

	D3DXVECTOR3 GetPosition( void )
	{
		return _position;
	}

	// 大きさセット
	void SetScaling(D3DXVECTOR3 scale)
	{
		_scaling = scale;
	}

	// ローテーションの加算
	void AddRotation(fx32 _add_rotation)
	{
		_rotation += _add_rotation;
	}

	// 色の選択
	void SelectColor(const D3DXVECTOR4& color);

	void ChangeTexture(LPCWSTR texture_fileName);

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

	//
	bool _visible;


protected:

	// シェーダー
	Shader2D* _shader;

	// メッシュ
	MeshBuffer* _mesh;

	//テクスチャ
	LPDIRECT3DTEXTURE9 _texture;

	
};