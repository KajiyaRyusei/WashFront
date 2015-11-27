//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �C���X�^���X�����X�v���C�g
// 
// Created by Ryusei Kajiya on 20151125
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "mesh_factory.h"

//*****************************************************************************
// 3D�p���_�t�H�[�}�b�g
struct VERTEX_INSTANCE_SPRITE
{
	D3DXVECTOR3	position;	// ���_
	D3DXVECTOR3	normal;		// �@���x�N�g��
	D3DXVECTOR2	texcoord;	// �e�N�X�`�����W
};

//*****************************************************************************
// �N���X�݌v
class MeshFactoryInstanceSprite : MeshFactory
{
public:
	MeshFactoryInstanceSprite() : _instance_max(10){}
	virtual MeshBuffer* Create(RendererDevice* renderer_device) override;
	MeshBuffer* Create(RendererDevice* renderer_device, u32 instance_max)
	{
		_instance_max = instance_max;
		return Create(renderer_device);
	}

	void RegisterMatrix(const D3DXMATRIX* matrices, MeshBuffer* mesh);

private:
	u32 _instance_max;
};