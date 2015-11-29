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
	
};