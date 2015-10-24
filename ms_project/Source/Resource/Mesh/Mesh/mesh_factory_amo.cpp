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

//*****************************************************************************
// 3D用頂点フォーマット
struct VERTEX_AMO
{
	D3DXVECTOR3 position;		// 座標
	D3DXVECTOR3 normal;			// 法線
	D3DXVECTOR2 texcoord;		// テクスチャ座標
	fx32 weight[4];			// 重み
	u8 bone_index[4];// ボーンインデックス

	VERTEX_AMO() : position(0.f, 0.f, 0.f), normal(0.f, 0.f, 0.f), texcoord(0.f, 0.f){ ZeroMemory(bone_index, sizeof(u8)* 4); ZeroMemory(weight, sizeof(fx32)* 4); }
};

//=============================================================================
// 作成
void MeshFactoryAMO::Create(
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
	u32 number_mesh(0);
	file >> number_mesh;

	// 確保
	mesh_list.reserve(number_mesh);

	for( u32 mesh_id = 0; mesh_id < number_mesh; ++mesh_id )
	{
		MeshBuffer* mesh = new MeshBuffer(renderer_device);

		//// 頂点数
		unsigned int mesh_vertex_count(0);
		file >> mesh_vertex_count;
		std::vector<VERTEX_AMO> vertices;
		vertices.reserve(mesh_vertex_count);

		for( u32 vertex_id = 0; vertex_id < mesh_vertex_count; ++vertex_id )
		{// 頂点
			u32 vertex_bone[4];
			VERTEX_AMO vertex;
			file >> vertex.position.x >> vertex.position.y >> vertex.position.z;
			file >> vertex.normal.x >> vertex.normal.y >> vertex.normal.z;
			file >> vertex.texcoord.x >> vertex.texcoord.y;
			file >> vertex.weight[0] >> vertex.weight[1] >> vertex.weight[2] >> vertex.weight[3];
			file >> vertex_bone[0] >> vertex_bone[1] >> vertex_bone[2] >> vertex_bone[3];
			for( int i = 0; i < 4; ++i )
			{
				vertex.bone_index[i] = static_cast<u8>(vertex_bone[i]);
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
		file >> index_buffer_count;
		std::vector<u32> indices;
		indices.reserve(index_buffer_count);
		for( u32 index_id = 0; index_id < index_buffer_count; ++index_id )
		{// インデックス
			u32 index;
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