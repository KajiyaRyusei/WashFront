//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// キューブテクスチャリソース
//
// Created by Ryusei Kajiya on 20151102
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Resource/resource.h"

//*****************************************************************************
// キューブテクスチャリソースID
enum CUBE_TEXTURE_RESOURE_ID
{// 2で割り切れるのはディフューズ割り切れないのはスペキュラ
	CUBE_TEXTURE_RESOURE_GRID_ZERO_ZERO_DIFFUSE = 0,
	CUBE_TEXTURE_RESOURE_GRID_ZERO_ZERO_SPECULAR,
	CUBE_TEXTURE_RESOURE_GRID_ZERO_ONE_DIFFUSE,
	CUBE_TEXTURE_RESOURE_GRID_ZERO_ONE_SPECULAR,
};

//*****************************************************************************
// クラス設計
class CubeTextureResource : public Resource<LPDIRECT3DCUBETEXTURE9, CUBE_TEXTURE_RESOURE_ID>
{
public:
	CubeTextureResource(){}
	virtual ~CubeTextureResource(){ Clear(); }

	// 作成
	void Create(CUBE_TEXTURE_RESOURE_ID id, RendererDevice* device) override;
	// 全削除
	void Clear() override;
	// 取得
	LPDIRECT3DCUBETEXTURE9 Get(CUBE_TEXTURE_RESOURE_ID id) override;
};