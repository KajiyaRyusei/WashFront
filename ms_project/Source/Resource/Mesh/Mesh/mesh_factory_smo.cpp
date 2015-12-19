//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �X�v���C�g���b�V���쐬
// 
// Created by Ryusei Kajiya on 20151014
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "mesh_factory_smo.h"
#include "Algorithm/often_use.h"

//=============================================================================
// �쐬
void MeshFactorySMO::Create(
	RendererDevice* renderer_device,
	std::string file_name,
	std::vector<MeshBuffer*>& mesh_list)
{
	std::ifstream file;
	std::string line;
	file.open(file_name, std::ios_base::binary);
	if( file.fail() == true )
	{
		OutputDebugStringA("�t�@�C�����͂ɃG���[���������܂���\n");
	}

	// ���������_�̐��x
	file.precision(5);

	// ���b�V����
	unsigned int number_mesh(0);
	file.read((char*)&number_mesh, sizeof(u32));

	// �m��
	mesh_list.reserve(number_mesh);

	for( unsigned int mesh_id = 0; mesh_id < number_mesh; ++mesh_id )
	{
		MeshBuffer* mesh = new MeshBuffer(renderer_device);

		//// ���_��
		unsigned int mesh_vertex_count(0);
		file.read((char*)&mesh_vertex_count, sizeof(u32));
		std::vector<VERTEX_SMO> vertices;
		vertices.reserve(mesh_vertex_count);

		for( unsigned int vertex_id = 0; vertex_id < mesh_vertex_count; ++vertex_id )
		{// ���_
			VERTEX_SMO vertex;
			file.read((char*)&vertex.position, sizeof(D3DXVECTOR3));
			file.read((char*)&vertex.normal, sizeof(D3DXVECTOR3));
			file.read((char*)&vertex.texcoord, sizeof(D3DXVECTOR2));
			vertex.cleanliness = D3DXVECTOR4(1.f,1.f,1.f,1.f);

			vertices.push_back(vertex);
		}

		// ���_�o�b�t�@�̐��m��
		mesh->RegisterVertexCount(0, mesh_vertex_count);
		// ���_�錾
		mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0);
		mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0);
		mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0);
		mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1);
		mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2);
		// ���_�o�b�t�@�̍쐬
		mesh->CreateVertexBuffer(D3DUSAGE_WRITEONLY, D3DPOOL_MANAGED);

		// �C���f�b�N�X��
		u32 index_buffer_count = 0;
		file.read((char*)&index_buffer_count, sizeof(u32));
		std::vector<u32> indices;
		indices.reserve(index_buffer_count);
		for( u32 index_id = 0; index_id < index_buffer_count; ++index_id )
		{// �C���f�b�N�X
			u32 index;
			file.read((char*)&index, sizeof(u32));
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
		VERTEX_SMO* vertex = nullptr;
		mesh->GetVertexBuffer(0)->Lock(0, 0, (void**)&vertex, 0);

		for( u32 vertex_id = 0; vertex_id < mesh_vertex_count; ++vertex_id )
		{
			vertex[vertex_id] = vertices[vertex_id];
		}

		mesh->GetVertexBuffer(0)->Unlock();

		// �ڃx�N�g���̍쐬
		TangentCompute(mesh);

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

//=============================================================================
// �]�@���Ɛڃx�N�g�������߂�
void MeshFactorySMO::TangentCompute(MeshBuffer* mesh)
{
	VERTEX_SMO* vertex = nullptr;
	mesh->GetVertexBuffer(0)->Lock(0, 0, (void**)&vertex, 0);

	s32 vertex_index = 0;
	s32 index_one = 0;
	s32 index_two = 0;
	s32 index_three = 0;

	for( u32 vertex_id = 0; vertex_id < mesh->GetVertexCount(0); ++vertex_id )
	{
		if( vertex_id == mesh->GetVertexCount(0) -1)
		{

		}
		else if( vertex_id == mesh->GetVertexCount(0) - 2 )
		{
			index_one = vertex_id;
			index_two = vertex_id + 1;
			index_three = vertex_id + 2;
		}
		else
		{
			index_one = vertex_id;
			index_two = vertex_id + 1;
			index_three = vertex_id + 2;
		}

		algo::ComputeTangentAndBinormal(
			vertex[index_one].position, vertex[index_two].position, vertex[index_three].position,
			vertex[index_one].texcoord, vertex[index_two].texcoord, vertex[index_three].texcoord,
			&vertex[vertex_index].tangent, nullptr);
	}

	mesh->GetVertexBuffer(0)->Unlock();
}
