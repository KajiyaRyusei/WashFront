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
	
	//場所セット
	void SetPosition(D3DXVECTOR3 position)
	{
		_position = position;
	}

	//場所取得
	D3DXVECTOR3 GetPosition(void)
	{
		return _position;
	}

	//大きさセット
	void SetScale(D3DXVECTOR3 scaling)
	{
		_scaling = scaling;
	}

	//大きさ取得
	D3DXVECTOR3 GetScaling(void)
	{
		return _scaling;
	}

	//角度セット
	void SetRotation(float rotation)
	{
		_rotation = rotation;
	}

	//角度取得
	float GetRotation(void)
	{
		return _rotation;
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
	Shader2D* _shader;

	// メッシュ
	MeshBuffer* _mesh;

	//テクスチャ
	LPDIRECT3DTEXTURE9 _texture;


};