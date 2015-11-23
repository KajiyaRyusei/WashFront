//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���b�V���t�B�[���h�쐬
// 
// Created by Ryusei Kajiya on 20151103
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "mesh_factory_mesh_field.h"
#include "Algorithm/often_use.h"
#include "Algorithm/perlin_noise.h"

//*****************************************************************************
// �萔
namespace
{
	// ���b�V���̃T�C�Y�ƕ�����
	static const s32 kNumberBlockY = 20;
	static const s32 kNumberBlockX = 20;
	static const fx32 kSizeBlockY =0.3f;
	static const fx32 kSizeBlockX =0.3f;
}

//=============================================================================
// �쐬
MeshBuffer* MeshFactoryMeshField::Create(RendererDevice* renderer_device)
{
	MeshBuffer* mesh = new MeshBuffer(renderer_device);

	s32 vertex_count = (kNumberBlockX + 1) * (kNumberBlockY + 1);
	u16 index_count = static_cast<u16>(vertex_count + ((kNumberBlockX - 1)*(kNumberBlockY + 1)) + ((kNumberBlockX - 1) * 2));
	s32 primitive_count = index_count - 2;

	// ���_�o�b�t�@�̍쐬
	// ���L�f�[�^�̐ݒ�
	mesh->RegisterVertexCount(0, vertex_count);
	mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0);
	mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0);
	mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0);
	mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0);
	mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0);
	mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0);

	// ���_�o�b�t�@�̍쐬
	mesh->CreateVertexBuffer(D3DUSAGE_WRITEONLY, D3DPOOL_MANAGED);

	// ���_�f�[�^�̐ݒ�
	mesh->RegisterPrimitiveCount(1);
	mesh->SetPrimitiveType(D3DPT_TRIANGLESTRIP);
	mesh->SetPrimitiveCount(0, primitive_count);

	// �C���f�b�N�X�o�b�t�@�̍쐬
	mesh->RegisterIndexCount(1);
	mesh->RegisterIndexInformation(0, index_count);
	mesh->CreateIndexBuffer(D3DUSAGE_WRITEONLY, D3DFMT_INDEX16);

	//------------------------------------
	// ���_���̍쐬
	VERTEX_MESH_FIELD* vertex = nullptr;
	mesh->GetVertexBuffer(0)->Lock(0, 0, (void**)&vertex, 0);

	s32 vertex_index = 0;
	fx32 one_texcoord_x = 1.f / kNumberBlockX;
	fx32 one_texcoord_y = 1.f / kNumberBlockY;
	fx32 displace_x = kNumberBlockX * kSizeBlockX * 0.5f;
	fx32 displace_y = kNumberBlockY * kSizeBlockY * 0.5f;
	s32 vertex_count_half = vertex_count / 2;
	fx32 one_weight = 1.f / vertex_count_half;

	for( s32 y = 0; y <= kNumberBlockY; ++y )
	{
		for( s32 x = 0; x <= kNumberBlockX; ++x )
		{
			vertex[vertex_index].position = D3DXVECTOR3(
				static_cast<fx32>(x * kSizeBlockX) - displace_x,
				0.f, 
				static_cast<fx32>(y * kSizeBlockY) - displace_y);
			vertex[vertex_index].texcoord = D3DXVECTOR2(
				one_texcoord_x * x, one_texcoord_y * y);

			s32 weight_weight = abs(vertex_index - vertex_count_half);
			vertex[vertex_index].weight = one_weight*weight_weight;

			// ���_�z��
			vertex_index++;
		}
	}

	mesh->GetVertexBuffer(0)->Unlock();

	// ���W����
	RandomPosition(mesh);

	// �@��
	NormalCompute(mesh);

	// �ڃx�N�g��
	TangentCompute(mesh);

	//------------------------------------
	// index���̍쐬
	u16* index;
	mesh->GetIndexBuffer(0)->Lock(0, 0, (void**)&index, 0);

	//�C���f�b�N�X�J�E���g�p
	u16 index_index = 0;

	//X���[�v
	for( u16 x = 0; x<kNumberBlockX; ++x )
	{
		//Z���[�v
		for( u16 y = 0; y<kNumberBlockY + 1; ++y )
		{
			//��
			index[index_index] = x + (y*(kNumberBlockX + 1));
			index_index++;

			//�E
			index[index_index] = (x + 1) + (y*(kNumberBlockX + 1));
			index_index++;

			if( x != kNumberBlockX - 1 && y == kNumberBlockY )
			{//�k�ރ|���S���ɍ��킹�Ĕԍ���t����
				//�E
				index[index_index] = (x + 1) + (y*(kNumberBlockX + 1));
				index_index++;

				//��
				index[index_index] = (x + 1) + ((y - kNumberBlockY)*(kNumberBlockX + 1));
				index_index++;
			}
		}
	}

	mesh->GetIndexBuffer(0)->Unlock();

	return mesh;
}

//=============================================================================
// �@���v�Z
void MeshFactoryMeshField::NormalCompute(MeshBuffer* mesh)
{
	VERTEX_MESH_FIELD* vertex = nullptr;
	mesh->GetVertexBuffer(0)->Lock(0, 0, (void**)&vertex, 0);

	D3DXVECTOR3 vector_one, vector_two, vector_normal;

	D3DXVECTOR3 normal[kNumberBlockX * 2][kNumberBlockY];

	// �ʂ̖@������
	for( s32 y = 0; y < kNumberBlockY; ++y )
	{
		for( s32 x = 0; x < kNumberBlockX; ++x )
		{
			s32 start_index = y * (kNumberBlockX + 1) + 1 + x;
			s32 end_index_one = y *(kNumberBlockX + 1) + x;
			s32 end_index_two = (y + 1)	*	(kNumberBlockX + 1) + x;
			vector_one = vertex[end_index_one].position - vertex[start_index].position;
			vector_two = vertex[end_index_two].position - vertex[start_index].position;

			D3DXVec3Cross(&vector_normal, &vector_one, &vector_two);
			D3DXVec3Normalize(&vector_normal, &vector_normal);

			s32 normal_index_x = x * 2;
			s32 normal_index_y = y;

			normal[normal_index_x][normal_index_y] = vector_normal;

			end_index_one = (y + 1) * (kNumberBlockX + 1) + x;
			end_index_two = (y + 1) * (kNumberBlockX + 1) + 1 + x;
			vector_one = vertex[end_index_one].position - vertex[start_index].position;
			vector_two = vertex[end_index_two].position - vertex[start_index].position;

			D3DXVec3Cross(&vector_normal, &vector_one, &vector_two);
			D3DXVec3Normalize(&vector_normal, &vector_normal);

			normal_index_x = x * 2 + 1;

			normal[normal_index_x][normal_index_y] = vector_normal;
		}
	}

	s32 vertex_index = 0;

	// ���_�̖@������
	for( s32 y = 0; y <= kNumberBlockY; ++y )
	{
		s32 temp_count = 0;

		for( s32 x = 0; x <= kNumberBlockX; ++x )
		{
			if( y == 0 )					// ��
			{
				if( x == 0 )				// ����
				{
					vertex[vertex_index].normal = normal[0][0];
				}
				else if( x == kNumberBlockX )// �E��
				{
					vector_normal = (normal[temp_count][0] + normal[temp_count + 1][0]) *0.5f;
					D3DXVec3Normalize(&vector_normal, &vector_normal);
					vertex[vertex_index].normal = vector_normal;
				}
				else
				{
					vector_normal = (normal[temp_count][0] + normal[temp_count + 1][0]) * 0.5f + normal[temp_count + 2][0];
					D3DXVec3Normalize(&vector_normal, &vector_normal);
					temp_count += 2;
					vertex[vertex_index].normal = vector_normal;
				}

			}
			else if( y == kNumberBlockY )	// ��
			{
				if( x == 0 )				// ����
				{
					vector_normal = (normal[0][y - 1] + normal[1][y - 1]) *0.5f;
					D3DXVec3Normalize(&vector_normal, &vector_normal);
					vertex[vertex_index].normal = vector_normal;
				}
				else if( x == kNumberBlockX )// �E��
				{
					vector_normal = normal[kNumberBlockX * 2 - 1][kNumberBlockY - 1];
					D3DXVec3Normalize(&vector_normal, &vector_normal);
					vertex[vertex_index].normal = vector_normal;
				}
				else
				{
					vector_normal = normal[temp_count + 1][y - 1] + (normal[temp_count + 2][y - 1] + normal[temp_count + 3][y - 1]) *0.5f;
					D3DXVec3Normalize(&vector_normal, &vector_normal);
					temp_count += 2;
					vertex[vertex_index].normal = vector_normal;
				}
			}
			else							// ���̑�
			{
				if( x == 0 )				// ��
				{
					vector_normal = (normal[0][y - 1] + normal[1][y - 1]) *0.5f + normal[0][y];
					D3DXVec3Normalize(&vector_normal, &vector_normal);
					vertex[vertex_index].normal = vector_normal;
				}
				else if( x == kNumberBlockX )// �E
				{
					vector_normal = normal[(kNumberBlockX * 2) - 1][y - 1] + (normal[(kNumberBlockX * 2) - 2][y] + normal[(kNumberBlockX * 2) - 1][y]) * 0.5f;
					D3DXVec3Normalize(&vector_normal, &vector_normal);
					vertex[vertex_index].normal = vector_normal;
				}
				else
				{
					vector_one = normal[temp_count + 1][y - 1] + (normal[temp_count + 2][y - 1] + normal[temp_count + 3][y - 1]) * 0.5f;
					vector_two = (normal[temp_count + 1][y] + normal[temp_count + 2][y]) *0.5f + normal[temp_count + 3][y];
					vector_normal = vector_one + vector_two;
					D3DXVec3Normalize(&vector_normal, &vector_normal);
					temp_count += 2;
					vertex[vertex_index].normal = vector_normal;
				}
			}
			vertex_index++;
		}
	}

	mesh->GetVertexBuffer(0)->Unlock();
}

//=============================================================================
// �]�@���Ɛڃx�N�g�������߂�
void MeshFactoryMeshField::TangentCompute(MeshBuffer* mesh)
{
	VERTEX_MESH_FIELD* vertex = nullptr;
	mesh->GetVertexBuffer(0)->Lock(0, 0, (void**)&vertex, 0);

	s32 vertex_index = 0;
	s32 index_one = 0;
	s32 index_two = 0;
	s32 index_three = 0;

	for( s32 y = 0; y <= kNumberBlockY; ++y )
	{
		for( s32 x = 0; x <= kNumberBlockX; ++x )
		{
			if( y == 0)
			{// ��
				if( x == 0 )
				{// ����
					index_one = 0;
					index_two = 1;
					index_three = (kNumberBlockX + 1);
				}
				else if( x == kNumberBlockX )
				{// �E��
					index_one = kNumberBlockX - 1;
					index_two = kNumberBlockX;
					index_three = kNumberBlockX*2 + 1;
				}
				else
				{// ���̂ق�
					index_one = x;
					index_two = x + 1;
					index_three = kNumberBlockX * 2;
				}
			}
			else if( y == kNumberBlockY )
			{// ��
				if( x == 0 )
				{// ����
					index_one = vertex_index - (kNumberBlockX + 1);
					index_two = vertex_index;
					index_three = vertex_index + 1;
				}
				else if( x == kNumberBlockX )
				{// �E��
					index_one = vertex_index - (kNumberBlockX + 1);
					index_two = vertex_index - 1;
					index_three = vertex_index;
				}
				else
				{// ���̂ق�
					index_one = vertex_index;
					index_two = vertex_index + 1;
					index_three = vertex_index - kNumberBlockX;
				}
			}
			else
			{
				if( x == 0 )
				{// ��
					index_one = vertex_index;
					index_two = vertex_index + 1;
					index_three = vertex_index - kNumberBlockX;
				}
				else if( x == kNumberBlockX )
				{// �E
					index_one = vertex_index;
					index_two = vertex_index - 1;
					index_three = vertex_index - (kNumberBlockX + 1);
				}
				else
				{// ���̂ق�
					index_one = vertex_index;
					index_two = vertex_index + 1;
					index_three = vertex_index - kNumberBlockX;
				}
			}

			algo::ComputeTangentAndBinormal(
				vertex[index_one].position, vertex[index_two].position, vertex[index_three].position,
				vertex[index_one].texcoord, vertex[index_two].texcoord, vertex[index_three].texcoord,
				&vertex[vertex_index].tangent, &vertex[vertex_index].binormal);

			vertex_index++;
		}
	}

	mesh->GetVertexBuffer(0)->Unlock();
}

//=============================================================================
// ���_��K���ɂ���
void MeshFactoryMeshField::RandomPosition(MeshBuffer* mesh)
{
	//------------------------------------
	// ���_���̍쐬
	VERTEX_MESH_FIELD* vertex = nullptr;
	mesh->GetVertexBuffer(0)->Lock(0, 0, (void**)&vertex, 0);

	s32 vertex_index = 0;;

	std::random_device random_device;
	std::mt19937 mt(random_device());
	std::uniform_int_distribution<s32> height_distribution(0, 999999999);
	std::uniform_real_distribution<fx32> x_distribution(0.0, 0.2f);
	std::uniform_real_distribution<fx32> z_distribution(0.0, 0.2f);
	D3DXVECTOR3 length_vector;
	fx32 vertex_length[kNumberBlockY / 2];

	for( s32 i = 0; i < kNumberBlockY/2; ++i )
	{
		s32 length_index = (kNumberBlockX + 1)*i + kNumberBlockX/2;
		length_vector = vertex[length_index].position - D3DXVECTOR3(0.f, 0.f, 0.f);
		vertex_length[i] = D3DXVec3Length(&length_vector);
	}

	D3DXVECTOR3 scaling(1.5f,1.f,1.f);
	D3DXMATRIX scale_matrix;
	D3DXMatrixScaling(&scale_matrix, scaling.x, scaling.y, scaling.z);

	vertex_index = 0;

	PerlinNoise perlin_noise;
	perlin_noise.SetSeed(height_distribution(mt));
	perlin_noise.SetPersistence(0.65f);
	perlin_noise.SetFrequency(0.07f);

	for( s32 y = 0; y <= kNumberBlockY; ++y )
	{
		for( s32 x = 0; x <= kNumberBlockX; ++x )
		{
			fx32 length = 0.f;

			for( s32 i = 0; i < kNumberBlockY / 2; ++i )
			{
				length_vector = vertex[vertex_index].position - D3DXVECTOR3(0.f, 0.f, 0.f);
				length = D3DXVec3Length(&length_vector);

				if( vertex_length[i] <= length )
				{
					length = vertex_length[i];
					break;
				}
			}

			fx32 sita = atan2f(0.f - vertex[vertex_index].position.x, 0.f - vertex[vertex_index].position.z);
			vertex[vertex_index].position = D3DXVECTOR3(
				sinf(sita) * -length + x_distribution(mt),
				perlin_noise.GetNoise(static_cast<fx32>(x), static_cast<fx32>(y))*2.f,
				cosf(sita) * -length + z_distribution(mt));

			D3DXVec3TransformCoord(&vertex[vertex_index].position, &vertex[vertex_index].position, &scale_matrix);

			// ���_�z��
			vertex_index++;
		}
	}

	mesh->GetVertexBuffer(0)->Unlock();
}