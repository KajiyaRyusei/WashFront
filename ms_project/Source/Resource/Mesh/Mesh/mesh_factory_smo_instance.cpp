//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �C���X�^���X�X�^�e�B�b�N���b�V���쐬
// 
// Created by Ryusei Kajiya on 20151215
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "mesh_factory_smo_instance.h"
#include "Algorithm/often_use.h"

//=============================================================================
// �쐬
void MeshFactorySMOInstance::Create(
	RendererDevice* renderer_device,
	std::string file_name,
	std::vector<MeshBuffer*>& mesh_list,
	u32 instance_max)
{
	_instance_max = instance_max;

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
		std::vector<VERTEX_SMO_INSTANCE> vertices;
		vertices.reserve(mesh_vertex_count);

		for( unsigned int vertex_id = 0; vertex_id < mesh_vertex_count; ++vertex_id )
		{// ���_
			VERTEX_SMO_INSTANCE vertex;
			file.read((char*)&vertex.position, sizeof(D3DXVECTOR3));
			file.read((char*)&vertex.normal, sizeof(D3DXVECTOR3));
			file.read((char*)&vertex.texcoord, sizeof(D3DXVECTOR2));

			vertices.push_back(vertex);
		}

		// ���_�o�b�t�@�̐��m��
		mesh->RegisterVertexCount(0, mesh_vertex_count);
		// ���L�f�[�^
		mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0);
		mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0);
		mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0);
		mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1);

		// �Œ�f�[�^(�C���X�^���X�f�[�^)
		mesh->RegisterVertexCount(1, _instance_max);
		mesh->RegisterVertexInformation(1, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2);
		mesh->RegisterVertexInformation(1, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3);
		mesh->RegisterVertexInformation(1, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 4);
		mesh->RegisterVertexInformation(1, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 5);

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
		VERTEX_SMO_INSTANCE* vertex = nullptr;
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
void MeshFactorySMOInstance::TangentCompute(MeshBuffer* mesh)
{
	VERTEX_SMO_INSTANCE* vertex = nullptr;
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

//=============================================================================
// �s��̓o�^
void MeshFactorySMOInstance::RegisterMatrix(const D3DXMATRIX* matrices, u32 instance_count, std::vector<MeshBuffer*>& mesh_list)
{
	for( auto mesh : mesh_list )
	{
		// �C���X�^���X�f�[�^�̏�����
		D3DXVECTOR4* instance_data = nullptr;
		mesh->GetVertexBuffer(1)->Lock(0, 0, (void**)&instance_data, 0);

		u32 matrix_index = 0;
		for( u32 i = 0; i < instance_count * 4; i += 4 )
		{
			instance_data[i + 0] = D3DXVECTOR4(matrices[matrix_index]._11, matrices[matrix_index]._12, matrices[matrix_index]._13, matrices[matrix_index]._14);
			instance_data[i + 1] = D3DXVECTOR4(matrices[matrix_index]._21, matrices[matrix_index]._22, matrices[matrix_index]._23, matrices[matrix_index]._24);
			instance_data[i + 2] = D3DXVECTOR4(matrices[matrix_index]._31, matrices[matrix_index]._32, matrices[matrix_index]._33, matrices[matrix_index]._34);
			instance_data[i + 3] = D3DXVECTOR4(matrices[matrix_index]._41, matrices[matrix_index]._42, matrices[matrix_index]._43, matrices[matrix_index]._44);
			++matrix_index;
		}

		mesh->GetVertexBuffer(1)->Unlock();
	}
}