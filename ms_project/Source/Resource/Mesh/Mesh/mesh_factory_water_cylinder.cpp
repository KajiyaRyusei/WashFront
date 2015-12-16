//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���V�����_�[
//
// Created by Ryusei Kajiya on 20151114
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "mesh_factory_water_cylinder.h"
#include "Algorithm/often_use.h"



//*****************************************************************************
// �萔
namespace
{
	// ���b�V���̃T�C�Y�ƕ�����
	static const s32 kNumberBlockY = 20;
	static const s32 kNumberBlockX = 20;
	static const fx32 kSizeBlockY =1.2f;
	static const fx32 kSizeBlockX =1.5f;
}

//=============================================================================
// �쐬
MeshBuffer* MeshFactoryWaterCylinder::Create(RendererDevice* renderer_device)
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
	mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0);

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

	// ���W����
	PositionCompute(mesh);

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
// ���W�v�Z
void MeshFactoryWaterCylinder::PositionCompute(MeshBuffer* mesh)
{
	VERTEX_WATER_CYLINDER* vertex = nullptr;
	mesh->GetVertexBuffer(0)->Lock(0, 0, (void**)&vertex, 0);

	s32 vertex_index = 0;
	fx32 one_texcoord_x = 1.f / kNumberBlockX;
	fx32 one_texcoord_y = 1.f / kNumberBlockY;
	fx32 one_sita = D3DX_PI / kNumberBlockX * 2.f;
	fx32 one_weight = 1.f/kNumberBlockY;

	for( s32 y = 0; y <= kNumberBlockY; ++y )
	{
		fx32 weight_zero = 1 - (one_weight*y);
		fx32 weight_two = one_weight*y;
		fx32 weight_one = 1 - fabs(weight_zero - weight_two);

		fx32 sita = 0.f;
		for( s32 x = 0; x <= kNumberBlockX; ++x )
		{
			fx32 block_size_x = sinf(sita) * kSizeBlockX;
			fx32 block_size_z = cosf(sita) * kSizeBlockX;

			vertex[vertex_index].position = D3DXVECTOR3(
				block_size_z,
				block_size_x,
				y * kSizeBlockY );

			vertex[vertex_index].texcoord = D3DXVECTOR2(one_texcoord_x * x, one_texcoord_y * y);

			vertex[vertex_index].weight[0] = weight_zero;
			vertex[vertex_index].weight[1] = weight_one;
			vertex[vertex_index].weight[2] = weight_two;

			// ���_�z��
			vertex_index++;
			sita += one_sita;
		}
	}

	mesh->GetVertexBuffer(0)->Unlock();
}
//=============================================================================
// �@���v�Z
void MeshFactoryWaterCylinder::NormalCompute(MeshBuffer* mesh)
{
	VERTEX_WATER_CYLINDER* vertex = nullptr;
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
void MeshFactoryWaterCylinder::TangentCompute(MeshBuffer* mesh)
{
	VERTEX_WATER_CYLINDER* vertex = nullptr;
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