//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// スプライトメッシュ作成
// 
// Created by Ryusei Kajiya on 20151014
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "mesh_factory_smo.h"

//*****************************************************************************
// 3D用頂点フォーマット
struct VERTEX_SMO
{
	D3DXVECTOR3	position;	// 頂点
	D3DXVECTOR3	normal;		// 法線ベクトル
	D3DXVECTOR2	texcoord;	// テクスチャ座標
};

//=============================================================================
// 作成
void MeshFactorySMO::Create(
	RendererDevice* renderer_device,
	std::string file_name,
	std::vector<MeshBuffer*>& mesh_list)
{
	std::ifstream file;
	std::string line;
	file.open(file_name, std::ios::out);
	if( file.fail() == true )
	{
		OutputDebugStringA("ファイル入力にエラーが発生しました\n");
	}

	// 浮動小数点の精度
	file.precision(5);

	// メッシュ数
	unsigned int number_mesh(0);
	file >> number_mesh;

	// 確保
	mesh_list.reserve(number_mesh);

	for( unsigned int mesh_id = 0; mesh_id < number_mesh; ++mesh_id )
	{
		MeshBuffer* mesh = new MeshBuffer(renderer_device);

		//// 頂点数
		unsigned int mesh_vertex_count(0);
		file >> mesh_vertex_count;
		std::vector<VERTEX_SMO> vertices;
		vertices.reserve(mesh_vertex_count);

		for( unsigned int vertex_id = 0; vertex_id < mesh_vertex_count; ++vertex_id )
		{// 頂点
			VERTEX_SMO vertex;
			file >> vertex.position.x >> vertex.position.y >> vertex.position.z;
			file >> vertex.normal.x >> vertex.normal.y >> vertex.normal.z;
			file >> vertex.texcoord.x >> vertex.texcoord.y;

			vertices.push_back(vertex);
		}

		// 頂点バッファの数確保
		mesh->RegisterVertexCount(0, mesh_vertex_count);
		// 頂点宣言
		mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0);
		mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0);
		mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0);
		// 頂点バッファの作成
		mesh->CreateVertexBuffer(D3DUSAGE_WRITEONLY, D3DPOOL_MANAGED);

		// インデックス数
		u32 index_buffer_count = 0;
		file >> index_buffer_count;
		std::vector<u32> indices;
		indices.reserve(index_buffer_count);
		for( u32 index_id = 0; index_id < index_buffer_count; ++index_id )
		{// インデックス
			DWORD index;
			file >> index;
			indices.push_back(index);
		}

		// インデックスバッファの作成
		mesh->RegisterIndexCount(1);
		mesh->RegisterIndexInformation(0, index_buffer_count);
		mesh->CreateIndexBuffer(D3DUSAGE_WRITEONLY, D3DFMT_INDEX32);

		// 頂点データの設定
		mesh->RegisterPrimitiveCount();
		mesh->SetPrimitiveType(D3DPT_TRIANGLELIST);
		mesh->SetPrimitiveCount(0, indices.size() / 3);

		// 頂点情報の作成
		VERTEX_SMO* vertex = nullptr;
		mesh->GetVertexBuffer(0)->Lock(0, 0, (void**)&vertex, 0);

		for( u32 vertex_id = 0; vertex_id < mesh_vertex_count; ++vertex_id )
		{
			vertex[vertex_id] = vertices[vertex_id];
		}

		mesh->GetVertexBuffer(0)->Unlock();

		// index情報の作成
		u32* index;
		mesh->GetIndexBuffer(0)->Lock(0, 0, (void**)&index, 0);

		for( u32 index_id = 0; index_id < index_buffer_count; ++index_id )
		{// インデックス
			index[index_id] = indices[index_id];
		}

		mesh->GetIndexBuffer(0)->Unlock();

		mesh_list.push_back(mesh);
	}
}