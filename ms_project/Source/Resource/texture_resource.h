//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// テクスチャリソース
//
// Created by Ryusei Kajiya on 20151122
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Resource/resource.h"

//*****************************************************************************
// テクスチャリソースID
enum TEXTURE_RESOURE_ID
{
	TEXTURE_RESOURE_PLAYER_TEXTURE = 0,
	TEXTURE_RESOURE_BILL_TEXTURE,
	TEXTURE_RESOURE_AIM_TEXTURE,
	TEXTURE_RESOURE_DIRT_NORMAL_TEXTURE,
	TEXTURE_RESOURE_WATER_BALL_TEXTURE,
	TEXTURE_RESOURE_WATER_NORMAL_TEXTURE,
	TEXTURE_RESOURE_BILL_METALNESS_TEXTURE,
	TEXTURE_RESOURE_DIRTY_TEXTURE,
};

//*****************************************************************************
// クラス設計
class TextureResource : public Resource<LPDIRECT3DTEXTURE9, TEXTURE_RESOURE_ID>
{
public:

	TextureResource(){}
	virtual ~TextureResource(){ Clear(); }

	// 作成
	void Create(TEXTURE_RESOURE_ID id, RendererDevice* device) override;
	// 全削除
	void Clear() override;
	// 取得
	LPDIRECT3DTEXTURE9 Get(TEXTURE_RESOURE_ID id) override;
};