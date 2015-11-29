//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �C���X�^���X�X�v���C�g
//
// Created by Ryusei Kajiya on 20151128
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
struct VERTEX_SPRITE_INSTANCE
{
	D3DXVECTOR3	position;	// ���_
	D3DXVECTOR3	normal;		// �@���x�N�g��
	D3DXVECTOR2	texcoord;	// �e�N�X�`�����W
};

//*****************************************************************************
// �N���X�݌v
class MeshFactorySpriteInstance : MeshFactory
{
public:
	MeshFactorySpriteInstance() : _instance_max(10){}
	MeshBuffer* Create(RendererDevice* renderer_device,u32 instance_count);
	virtual MeshBuffer* Create(RendererDevice* renderer_device) override;
	// �s��̓o�^
	void RegisterMatrix(const D3DXMATRIX* matrices, u32 instance_count, MeshBuffer* mesh);

private:

	u32 _instance_max;
};