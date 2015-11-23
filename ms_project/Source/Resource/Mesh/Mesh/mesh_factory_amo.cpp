//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �A�j���[�V�������b�V���쐬
// 
// Created by Ryusei Kajiya on 20151014
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "mesh_factory_amo.h"



//=============================================================================
// �쐬
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
		OutputDebugStringA("�t�@�C�����͂ɃG���[���������܂���\n");
	}

	// ���������_�̐��x
	file.precision(5);

	// ���b�V����
	u32 number_mesh(0);
	file >> number_mesh;

	// �m��
	mesh_list.reserve(number_mesh);

	for( u32 mesh_id = 0; mesh_id < number_mesh; ++mesh_id )
	{
		MeshBuffer* mesh = new MeshBuffer(renderer_device);

		//// ���_��
		unsigned int mesh_vertex_count(0);
		file >> mesh_vertex_count;
		std::vector<VERTEX_AMO> vertices;
		vertices.reserve(mesh_vertex_count);

		for( u32 vertex_id = 0; vertex_id < mesh_vertex_count; ++vertex_id )
		{// ���_
			VERTEX_AMO vertex;
			u32 temp_vertex_bone_index[4];
			file >> vertex.position.x >> vertex.position.y >> vertex.position.z;
			file >> vertex.normal.x >> vertex.normal.y >> vertex.normal.z;
			file >> vertex.texcoord.x >> vertex.texcoord.y;
			file >> vertex.weight[0] >> vertex.weight[1] >> vertex.weight[2] >> vertex.weight[3];
			file >> temp_vertex_bone_index[0] >> temp_vertex_bone_index[1] >> temp_vertex_bone_index[2] >> temp_vertex_bone_index[3];

			for( u32 i = 0; i < 4; ++i )
			{
				vertex.bone_index[i] = static_cast<u8>(temp_vertex_bone_index[i]);
			}
			vertices.push_back(vertex);
		}

		// ���_�o�b�t�@�̐��m��
		mesh->RegisterVertexCount(0, mesh_vertex_count);
		// ���_�錾
		mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0);
		mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0);
		mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0);
		mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0);
		mesh->RegisterVertexInformation(0, D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0);

		// ���_�o�b�t�@�̍쐬
		mesh->CreateVertexBuffer(D3DUSAGE_WRITEONLY, D3DPOOL_MANAGED);

		// �C���f�b�N�X��
		u32 index_buffer_count = 0;
		file >> index_buffer_count;
		std::vector<u32> indices;
		indices.reserve(index_buffer_count);
		for( u32 index_id = 0; index_id < index_buffer_count; ++index_id )
		{// �C���f�b�N�X
			u32 index;
			file >> index;
			indices.push_back(index);
		}

		// �C���f�b�N�X�o�b�t�@�̍쐬
		mesh->RegisterIndexCount(1);
		mesh->RegisterIndexInformation(0, index_buffer_count);
		mesh->CreateIndexBuffer(D3DUSAGE_WRITEONLY, D3DFMT_INDEX32);

		// ���_�f�[�^�̐ݒ�
		mesh->RegisterPrimitiveCount();
		mesh->SetPrimitiveType(D3DPT_TRIANGLELIST);
		mesh->SetPrimitiveCount(0, indices.size() / 3);

		// ���_���̍쐬
		VERTEX_AMO* vertex = nullptr;
		mesh->GetVertexBuffer(0)->Lock(0, 0, (void**)&vertex, 0);

		for( u32 vertex_id = 0; vertex_id < mesh_vertex_count; ++vertex_id )
		{
			vertex[vertex_id] = vertices[vertex_id];
		}

		mesh->GetVertexBuffer(0)->Unlock();

		// index���̍쐬
		u32* index;
		mesh->GetIndexBuffer(0)->Lock(0, 0, (void**)&index, 0);

		for( u32 index_id = 0; index_id < index_buffer_count; ++index_id )
		{// �C���f�b�N�X
			index[index_id] = indices[index_id];
		}

		mesh->GetIndexBuffer(0)->Unlock();

		mesh_list.push_back(mesh);
	}
}