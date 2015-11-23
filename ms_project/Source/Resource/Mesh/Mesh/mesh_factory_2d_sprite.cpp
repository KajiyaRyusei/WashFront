//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �X�v���C�g���b�V���쐬
// 
// Created by Ryusei Kajiya on 20151012
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "mesh_factory_2d_sprite.h"

//*****************************************************************************
// 3D�p���_�t�H�[�}�b�g
struct VERTEX_SPRITE
{
	D3DXVECTOR3	position;	// ���_
	D3DXVECTOR3	normal;		// �@���x�N�g��
	D3DXVECTOR2	texcoord;	// �e�N�X�`�����W
};

//=============================================================================
// �쐬
MeshBuffer* MeshFactory2DSprite::Create(RendererDevice* renderer_device)
{
	MeshBuffer* mesh = new MeshBuffer(renderer_device);

	// ���_�o�b�t�@�̍쐬
	// ���L�f�[�^�̐ݒ�
	mesh->RegisterVertexCount(0, 4);
	mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0);
	mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0);
	mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0);

	// ���_�o�b�t�@�̍쐬
	mesh->CreateVertexBuffer(D3DUSAGE_WRITEONLY, D3DPOOL_MANAGED);

	// ���_�f�[�^�̐ݒ�
	mesh->RegisterPrimitiveCount(1);
	mesh->SetPrimitiveType(D3DPT_TRIANGLESTRIP);
	mesh->SetPrimitiveCount(0, 2);

	// �C���f�b�N�X�o�b�t�@�̍쐬
	mesh->RegisterIndexCount(1);
	mesh->RegisterIndexInformation(0, 4);
	mesh->CreateIndexBuffer(D3DUSAGE_WRITEONLY, D3DFMT_INDEX16);

	// ���_���̍쐬
	VERTEX_SPRITE* vertex = nullptr;
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

	vertex[0].position = D3DXVECTOR3(-size, -size, 0.f);
	vertex[1].position = D3DXVECTOR3(size, -size, 0.f);
	vertex[2].position = D3DXVECTOR3(-size, size, 0.f);
	vertex[3].position = D3DXVECTOR3(size, size, 0.f);

	mesh->GetVertexBuffer(0)->Unlock();

	// index���̍쐬
	u16* index;
	mesh->GetIndexBuffer(0)->Lock(0, 0, (void**)&index, 0);

	index[0] = 0;
	index[1] = 1;
	index[2] = 2;
	index[3] = 3;

	mesh->GetIndexBuffer(0)->Unlock();

	return mesh;
}