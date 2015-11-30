//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �A�j���[�V�������b�V���쐬
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
struct VERTEX_AMO
{
	D3DXVECTOR3 position;		// ���W
	D3DXVECTOR3 normal;			// �@��
	D3DXVECTOR2 texcoord;		// �e�N�X�`�����W
	fx32 weight[4];			// �d��
	u8 bone_index[4];// �{�[���C���f�b�N�X
};

//*****************************************************************************
// �N���X�݌v
class MeshFactoryAMO : MeshFactory
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
	
};