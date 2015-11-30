//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���V�����_�[���p
//
// Created by Ryusei Kajiya on 20151123
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
struct VERTEX_WATER_CYLINDER_BACK
{
	D3DXVECTOR3	position;	// ���W
	D3DXVECTOR3	normal;		// �@���x�N�g��
	D3DXVECTOR2	texcoord;	// �e�N�X�`�����W
	D3DCOLOR color;			// �F
	D3DXVECTOR3	tangent;	// �ڃx�N�g��
	D3DXVECTOR3	binormal;	// �]�@��
};

//*****************************************************************************
// �N���X�݌v
class MeshFactoryWaterCylinderBack : MeshFactory
{
public:
	virtual MeshBuffer* Create(RendererDevice* renderer_device) override;

private:

	// ���W�v�Z
	void PositionCompute(MeshBuffer* mesh);

	// �@���v�Z
	void NormalCompute(MeshBuffer* mesh);

	// �]�@���Ɛڃx�N�g�������߂�
	void TangentCompute(MeshBuffer* mesh);

};