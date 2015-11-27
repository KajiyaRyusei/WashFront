//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// インスタンスしたスプライト
// 
// Created by Ryusei Kajiya on 20151125
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "mesh_factory_instance_sprite.h"

//=============================================================================
// 作成
MeshBuffer* MeshFactoryInstanceSprite::Create(RendererDevice* renderer_device)
{
	MeshBuffer* mesh = new MeshBuffer(renderer_device);

	// 頂点バッファの作成
	// 共有データの設定
	mesh->RegisterVertexCount(0, 4);
	mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0);
	mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0);
	mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0);

	// 固定データ
	mesh->RegisterVertexCount(1, _instance_max);
	mesh->RegisterVertexInformation(1, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1);
	mesh->RegisterVertexInformation(1, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2);
	mesh->RegisterVertexInformation(1, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3);
	mesh->RegisterVertexInformation(1, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 4);

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
	VERTEX_INSTANCE_SPRITE* vertex = nullptr;
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

	vertex[0].position = D3DXVECTOR3(-size, size, 0.f);
	vertex[1].position = D3DXVECTOR3(size, size, 0.f);
	vertex[2].position = D3DXVECTOR3(-size, -size, 0.f);
	vertex[3].position = D3DXVECTOR3(size, -size, 0.f);

	mesh->GetVertexBuffer(0)->Unlock();

	// index情報の作成
	u16* index;
	mesh->GetIndexBuffer(0)->Lock(0, 0, (void**)&index, 0);

	index[0] = 0;
	index[1] = 2;
	index[2] = 1;
	index[3] = 3;

	mesh->GetIndexBuffer(0)->Unlock();

	// 固定データの作成
	// インスタンシングデータの初期化
	D3DXVECTOR4* instance_data;
	mesh->GetVertexBuffer(1)->Lock(0, 0, (void**)&instance_data, 0);

	D3DXMATRIX identity_matrix;
	D3DXMatrixIdentity(&identity_matrix);

	for( u32 i = 0; i < _instance_max * 4; i+=4 )
	{
		instance_data[i + 0] = D3DXVECTOR4(identity_matrix._11, identity_matrix._12, identity_matrix._13, identity_matrix._14);
		instance_data[i + 1] = D3DXVECTOR4(identity_matrix._21, identity_matrix._22, identity_matrix._23, identity_matrix._24);
		instance_data[i + 2] = D3DXVECTOR4(identity_matrix._31, identity_matrix._32, identity_matrix._33, identity_matrix._34);
		instance_data[i + 3] = D3DXVECTOR4(identity_matrix._41, identity_matrix._42, identity_matrix._43, identity_matrix._44);
	}

	mesh->GetVertexBuffer(1)->Unlock();

	return mesh;
}

//=============================================================================
// 作成
void MeshFactoryInstanceSprite::RegisterMatrix(const D3DXMATRIX* matrices, MeshBuffer* mesh)
{
	// インスタンシングデータの初期化
	D3DXVECTOR4* instance_data;
	mesh->GetVertexBuffer(1)->Lock(0, 0, (void**)&instance_data, 0);

	D3DXMATRIX identity_matrix;
	D3DXMatrixIdentity(&identity_matrix);

	u32 matrix_index = 0;
	for( u32 i = 0; i < _instance_max * 4; i += 4, matrix_index++)
	{
		instance_data[i + 0] = D3DXVECTOR4(matrices[matrix_index]._11, matrices[matrix_index]._12, matrices[matrix_index]._13, matrices[matrix_index]._14);
		instance_data[i + 1] = D3DXVECTOR4(matrices[matrix_index]._21, matrices[matrix_index]._22, matrices[matrix_index]._23, matrices[matrix_index]._24);
		instance_data[i + 2] = D3DXVECTOR4(matrices[matrix_index]._31, matrices[matrix_index]._32, matrices[matrix_index]._33, matrices[matrix_index]._34);
		instance_data[i + 3] = D3DXVECTOR4(matrices[matrix_index]._41, matrices[matrix_index]._42, matrices[matrix_index]._43, matrices[matrix_index]._44);
	}

	mesh->GetVertexBuffer(1)->Unlock();
}