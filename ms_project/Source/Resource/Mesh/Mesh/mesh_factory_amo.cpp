//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// アニメーションメッシュ作成
// 
// Created by Ryusei Kajiya on 20151014
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "mesh_factory_amo.h"



//=============================================================================
// 作成
void MeshFactoryAMO::Create(
	RendererDevice* renderer_device,
	std::string file_name,
	std::vector<MeshBuffer*>& mesh_list)
{
	std::ifstream file;
	std::string line;
	file.open(file_name, std::ios_base::binary);
	if( file.fail() == true )
	{
		OutputDebugStringA("ファイル入力にエラーが発生しました\n");
	}

	// 浮動小数点の精度
	file.precision(5);

	// メッシュ数
	u32 number_mesh(0);
	file.read((char*)&number_mesh, sizeof(u32));

	// 確保
	mesh_list.reserve(number_mesh);

	for( u32 mesh_id = 0; mesh_id < number_mesh; ++mesh_id )
	{
		MeshBuffer* mesh = new MeshBuffer(renderer_device);

		//// 頂点数
		unsigned int mesh_vertex_count(0);
		file.read((char*)&mesh_vertex_count, sizeof(u32));
		std::vector<VERTEX_AMO> vertices;
		vertices.reserve(mesh_vertex_count);

		for( u32 vertex_id = 0; vertex_id < mesh_vertex_count; ++vertex_id )
		{// 頂点
			VERTEX_AMO vertex;
			u32 temp_vertex_bone_index[4];

			file.read((char*)&vertex.position, sizeof(D3DXVECTOR3));
			file.read((char*)&vertex.normal, sizeof(D3DXVECTOR3));
			file.read((char*)&vertex.texcoord, sizeof(D3DXVECTOR2));
			file.read((char*)vertex.weight, sizeof(fx32)* 4);
			file.read((char*)temp_vertex_bone_index, sizeof(u32)* 4);

			for( u32 i = 0; i < 4; ++i )
			{
				vertex.bone_index[i] = static_cast<u8>(temp_vertex_bone_index[i]);
			}
			vertices.push_back(vertex);
		}

		// 頂点バッファの数確保
		mesh->RegisterVertexCount(0, mesh_vertex_count);
		// 頂点宣言
		mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0);
		mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0);
		mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0);
		mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0);
		mesh->RegisterVertexInformation(0, D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0);

		// 頂点バッファの作成
		mesh->CreateVertexBuffer(D3DUSAGE_WRITEONLY, D3DPOOL_MANAGED);

		// インデックス数
		u32 index_buffer_count = 0;
		file.read((char*)&index_buffer_count, sizeof(u32));
		std::vector<u32> indices;
		indices.reserve(index_buffer_count);
		for( u32 index_id = 0; index_id < index_buffer_count; ++index_id )
		{// インデックス
			u32 index;
			file.read((char*)&index, sizeof(u32));
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
		VERTEX_AMO* vertex = nullptr;
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