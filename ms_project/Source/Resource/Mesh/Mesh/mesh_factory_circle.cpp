//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 円メッシュ
// 
// Created by Ryusei Kajiya on 20151213
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "mesh_factory_circle.h"

//*****************************************************************************
// 定数
namespace
{
	static const fx32 kVertexSize = 1.f;
	static const u32 kVertexCount =30;
}


//=============================================================================
// 作成
MeshBuffer* MeshFactoryCircle::Create(RendererDevice* renderer_device)
{
	MeshBuffer* mesh = new MeshBuffer(renderer_device);

	// 頂点バッファの作成
	// 共有データの設定
	mesh->RegisterVertexCount(0, kVertexCount);
	mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0);
	mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0);
	mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0);

	// 頂点バッファの作成
	mesh->CreateVertexBuffer(D3DUSAGE_WRITEONLY, D3DPOOL_MANAGED);

	// 頂点データの設定
	mesh->RegisterPrimitiveCount(1);
	mesh->SetPrimitiveType(D3DPT_TRIANGLEFAN);
	mesh->SetPrimitiveCount(0, kVertexCount - 2);

	// インデックスバッファの作成
	mesh->RegisterIndexCount(1);
	mesh->RegisterIndexInformation(0, kVertexCount);
	mesh->CreateIndexBuffer(D3DUSAGE_WRITEONLY, D3DFMT_INDEX16);

	// 頂点情報の作成
	VERTEX_CIRCLE* vertex = nullptr;
	mesh->GetVertexBuffer(0)->Lock(0, 0, (void**)&vertex, 0);

	for( u32 i = 0; i < kVertexCount; ++i )
	{
		vertex[i].normal = D3DXVECTOR3(0.f, 0.f, -1.f);
	}


	fx32 one_sita = D3DX_PI / (kVertexCount - 2) * 2.f;
	fx32 sita = 0.f;
	vertex[0].position = D3DXVECTOR3(0.0f, 0.f, 0.f);

	for( u16 i = 1; i < kVertexCount;++i )
	{
		fx32 x = cosf(sita) * kVertexSize;
		fx32 y = sinf(sita) * kVertexSize;
		vertex[i].position = D3DXVECTOR3(x, y, 0.f);
		vertex[i].texcoord = D3DXVECTOR2(x, y);
		sita += one_sita;
	}


	mesh->GetVertexBuffer(0)->Unlock();

	// index情報の作成
	u16* index;
	mesh->GetIndexBuffer(0)->Lock(0, 0, (void**)&index, 0);

	for( u16 i = 0; i < kVertexCount; ++i )
	{
		index[i] = i;
	}

	mesh->GetIndexBuffer(0)->Unlock();

	return mesh;
}