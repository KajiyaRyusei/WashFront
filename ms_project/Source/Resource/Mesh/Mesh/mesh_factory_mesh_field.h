//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���b�V���t�B�[���h�쐬
// 
// Created by Ryusei Kajiya on 20151103
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
struct VERTEX_MESH_FIELD
{
	D3DXVECTOR3	position;	// ���_
	D3DXVECTOR3	normal;		// �@���x�N�g��
	D3DXVECTOR2	texcoord;	// �e�N�X�`�����W
	D3DXVECTOR3	tangent;	// �ڃx�N�g��
	D3DXVECTOR3	binormal;	// �]�@��
	fx32 weight;			// �d��
};

//*****************************************************************************
// �N���X�݌v
class MeshFactoryMeshField : MeshFactory
{
public:
	virtual MeshBuffer* Create(RendererDevice* renderer_device) override;

private:

	// �@���v�Z
	void NormalCompute(MeshBuffer* mesh);

	// �]�@���Ɛڃx�N�g�������߂�
	void TangentCompute(MeshBuffer* mesh);

	// ���_��K���ɂ���
	void RandomPosition(MeshBuffer* mesh);

	
};