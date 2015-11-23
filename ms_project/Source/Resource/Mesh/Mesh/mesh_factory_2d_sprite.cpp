//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// スプライトメッシュ作成
// 
// Created by Ryusei Kajiya on 20151012
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "mesh_factory_2d_sprite.h"

//*****************************************************************************
// 3D用頂点フォーマット
struct VERTEX_SPRITE
{
	D3DXVECTOR3	position;	// 頂点
	D3DXVECTOR3	normal;		// 法線ベクトル
	D3DXVECTOR2	texcoord;	// テクスチャ座標
};

//=============================================================================
// 作成
MeshBuffer* MeshFactory2DSprite::Create(RendererDevice* renderer_device)
{
	MeshBuffer* mesh = new MeshBuffer(renderer_device);

	// 頂点バッファの作成
	// 共有データの設定
	mesh->RegisterVertexCount(0, 4);
	mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0);
	mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0);
	mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0);

	// 頂点バッファの作成
	mesh->CreateVertexBuffer(D3DUSAGE_WRITEONLY, D3DPOOL_MANAGED);

	// 頂点データの設定
	mesh->RegisterPrimitiveCount(1);
	mesh->SetPrimitiveType(D3DPT_TRIANGLESTRIP);
	mesh->SetPrimitiveCount(0, 2);

	// インデックスバッファの作成
	mesh->RegisterIndexCount(1);
	mesh->RegisterIndexInformation(0, 4);
	mesh->CreateIndexBuffer(D3DUSAGE_WRITEONLY, D3DFMT_INDEX16);

	// 頂点情報の作成
	VERTEX_SPRITE* vertex = nullptr;
	mesh->GetVertexBuffer(0)->Lock(0, 0, (void**)&vertex, 0);

	for( u32 i = 0; i < 4; ++i )
	{
		vertex[i].normal = D3DXVECTOR3(0.f, 0.f, -1.f);
	}

	vertex[0].texcoord = D3DXVECTOR2(0.f, 0.f);
	vertex[1].texcoord = D3DXVECTOR2(1.f, 0.f);
	vertex[2].texcoord = D3DXVECTOR2(0.f, 1.f);
	vertex[3].texcoord = D3DXVECTOR2(1.f, 1.f);

	static const fx32 size = 1.f;

	vertex[0].position = D3DXVECTOR3(-size, -size, 0.f);
	vertex[1].position = D3DXVECTOR3(size, -size, 0.f);
	vertex[2].position = D3DXVECTOR3(-size, size, 0.f);
	vertex[3].position = D3DXVECTOR3(size, size, 0.f);

	mesh->GetVertexBuffer(0)->Unlock();

	// index情報の作成
	u16* index;
	mesh->GetIndexBuffer(0)->Lock(0, 0, (void**)&index, 0);

	index[0] = 0;
	index[1] = 1;
	index[2] = 2;
	index[3] = 3;

	mesh->GetIndexBuffer(0)->Unlock();

	return mesh;
}