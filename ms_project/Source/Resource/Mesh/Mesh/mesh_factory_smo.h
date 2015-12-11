//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �X�^�e�B�b�N���b�V���쐬
// 
// Created by Ryusei Kajiya on 20151014
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
struct VERTEX_SMO
{
	D3DXVECTOR3	position;	// ���_
	D3DXVECTOR3	normal;		// �@���x�N�g��
	D3DXVECTOR2	texcoord;	// �e�N�X�`�����W
	D3DXVECTOR3	tangent;	// �ڃx�N�g��
	fx32 cleanliness;		// ����
};

//*****************************************************************************
// �N���X�݌v
class MeshFactorySMO : MeshFactory
{
public:

	// ������Ă�ł��Ӗ��Ȃ���
	virtual MeshBuffer* Create(RendererDevice* renderer_device) override{ UNREFERENCED_PARAMETER(renderer_device); return nullptr; }

	// �������Ă�ł�
	void Create(
		RendererDevice* renderer_device,
		std::string file_name,
		std::vector<MeshBuffer*>& mesh_list);

private:
	
	// �]�@���Ɛڃx�N�g�������߂�
	void TangentCompute(MeshBuffer* mesh);
};