//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �C���X�^���X�X�^�e�B�b�N���b�V���쐬
// 
// Created by Ryusei Kajiya on 20151215
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
struct VERTEX_SMO_INSTANCE
{
	D3DXVECTOR3	position;	// ���_
	D3DXVECTOR3	normal;		// �@���x�N�g��
	D3DXVECTOR2	texcoord;	// �e�N�X�`�����W
	D3DXVECTOR3	tangent;	// �ڃx�N�g��
};

//*****************************************************************************
// �N���X�݌v
class MeshFactorySMOInstance : MeshFactory
{
public:

	// ������Ă�ł��Ӗ��Ȃ���
	virtual MeshBuffer* Create(RendererDevice* renderer_device) override{ UNREFERENCED_PARAMETER(renderer_device); return nullptr; }

	// �������Ă�ł�
	void Create(
		RendererDevice* renderer_device,
		std::string file_name,
		std::vector<MeshBuffer*>& mesh_list,
		u32 instance_max);

	// �s��̓o�^
	void RegisterMatrix(const D3DXMATRIX* matrices, u32 instance_count, std::vector<MeshBuffer*>& mesh_list);

private:
	
	// �]�@���Ɛڃx�N�g�������߂�
	void TangentCompute(MeshBuffer* mesh);

	u32 _instance_max;
};