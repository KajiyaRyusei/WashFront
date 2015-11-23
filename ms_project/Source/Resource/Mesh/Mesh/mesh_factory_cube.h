//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �L���[�u���b�V���쐬
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
struct VERTEX_CUBE
{
	D3DXVECTOR3	position;	// ���_
	D3DXVECTOR3	normal;		// �@���x�N�g��
	D3DXVECTOR2	texcoord;	// �e�N�X�`�����W
	D3DXVECTOR3	tangent;	// �ڃx�N�g��
	D3DXVECTOR3	binormal;	// �]�@��
};
//*****************************************************************************
// �N���X�݌v
class MeshFactoryCube : MeshFactory
{
public:
	virtual MeshBuffer* Create(RendererDevice* renderer_device) override;

private:

	// �@���𒆐S������ˏ�ɂ���
	void NormalComputeSlanting(MeshBuffer* mesh);
	// �@����ʂ���܂������ɂ���
	void NormalComputeStraight(MeshBuffer* mesh);
	// �]�@���Ɛڃx�N�g�������߂�
	void TangentCompute(MeshBuffer* mesh);
};