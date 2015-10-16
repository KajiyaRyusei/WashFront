//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// キューブメッシュ作成
// 
// Created by Ryusei Kajiya on 20151012
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "mesh_factory_cube.h"

//*****************************************************************************
// 3D用頂点フォーマット
struct VERTEX_CUBE
{
	D3DXVECTOR3	position;	// 頂点
	D3DXVECTOR3	normal;		// 法線ベクトル
	D3DXVECTOR2	texcoord;	// テクスチャ座標
};

//=============================================================================
// 作成
MeshBuffer* MeshFactoryCube::Create(RendererDevice* renderer_device)
{
	MeshBuffer* mesh = new MeshBuffer(renderer_device);

	// 頂点バッファの作成
	// 共有データの設定
	mesh->RegisterVertexCount(0, 8);
	mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0);
	mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0);
	mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0);

	// 頂点バッファの作成
	mesh->CreateVertexBuffer(D3DUSAGE_WRITEONLY, D3DPOOL_MANAGED);

	// 頂点データの設定
	mesh->RegisterPrimitiveCount(1);
	mesh->SetPrimitiveCount(0, 12);

	// インデックスバッファの作成
	mesh->RegisterIndexCount(1);
	mesh->RegisterIndexInformation(0, 36);
	mesh->CreateIndexBuffer(D3DUSAGE_WRITEONLY, D3DFMT_INDEX16);

	// 頂点情報の作成
	VERTEX_CUBE* vertex = nullptr;
	mesh->GetVertexBuffer(0)->Lock(0, 0, (void**)&vertex, 0);

	// 座標
	vertex[0].position = D3DXVECTOR3(-1,  1, -1.f);
	vertex[1].position = D3DXVECTOR3( 1,  1, -1.f);
	vertex[2].position = D3DXVECTOR3( 1, -1, -1.f);
	vertex[3].position = D3DXVECTOR3(-1, -1, -1.f);
	vertex[4].position = D3DXVECTOR3(-1,  1,  1.f);
	vertex[5].position = D3DXVECTOR3( 1,  1,  1.f);
	vertex[6].position = D3DXVECTOR3( 1, -1,  1.f);
	vertex[7].position = D3DXVECTOR3(-1, -1,  1.f);

	// 法線
	D3DXVECTOR3 center_position(0.f, 0.f, 0.f);
	vertex[0].normal = D3DXVECTOR3(-1,  1, -1.f) - center_position;
	vertex[1].normal = D3DXVECTOR3( 1,  1, -1.f) - center_position;
	vertex[2].normal = D3DXVECTOR3( 1, -1, -1.f) - center_position;
	vertex[3].normal = D3DXVECTOR3(-1, -1, -1.f) - center_position;
	vertex[4].normal = D3DXVECTOR3(-1,  1,  1.f) - center_position;
	vertex[5].normal = D3DXVECTOR3( 1,  1,  1.f) - center_position;
	vertex[6].normal = D3DXVECTOR3( 1, -1,  1.f) - center_position;
	vertex[7].normal = D3DXVECTOR3(-1, -1,  1.f) - center_position;

	for( int i = 0; i < 8; ++i )
	{
		D3DXVec3Normalize(&vertex[i].normal, &vertex[i].normal);
	}

	// テクスチャ
	vertex[0].texcoord = D3DXVECTOR2( 1,  1);
	vertex[1].texcoord = D3DXVECTOR2( 1,  1);
	vertex[2].texcoord = D3DXVECTOR2( 1, -1);
	vertex[3].texcoord = D3DXVECTOR2(-1, -1);
	vertex[4].texcoord = D3DXVECTOR2(-1,  1);
	vertex[5].texcoord = D3DXVECTOR2( 1,  1);
	vertex[6].texcoord = D3DXVECTOR2( 1, -1);
	vertex[7].texcoord = D3DXVECTOR2(-1, -1);

	mesh->GetVertexBuffer(0)->Unlock();

	// index情報の作成
	u16* index;
	mesh->GetIndexBuffer(0)->Lock(0, 0, (void**)&index, 0);

	index[0] = 0;
	index[1] = 1;
	index[2] = 3;

	index[3] = 1;
	index[4] = 2;
	index[5] = 3;

	index[6] = 1;
	index[7] = 5;
	index[8] = 2;

	index[9] = 5;
	index[10] = 6;
	index[11] = 2;

	index[12] = 5;
	index[13] = 4;
	index[14] = 6;

	index[15] = 4;
	index[16] = 7;
	index[17] = 6;

	index[18] = 4;
	index[19] = 5;
	index[20] = 0;

	index[21] = 5;
	index[22] = 1;
	index[23] = 0;

	index[24] = 4;
	index[25] = 0;
	index[26] = 7;

	index[27] = 0;
	index[28] = 3;
	index[29] = 7;

	index[30] = 3;
	index[31] = 2;
	index[32] = 7;

	index[33] = 2;
	index[34] = 6;
	index[35] = 7;


	mesh->GetIndexBuffer(0)->Unlock();

	mesh->SetPrimitiveType(D3DPT_TRIANGLELIST);

	return mesh;
}