//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �L���[�u���b�V���쐬
// 
// 8���_�����Ȃ��̂Ŗ@����UV�������ĂȂ��Ǝv��
// 
// Created by Ryusei Kajiya on 20151022
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
class MeshFactoryCube : MeshFactory
{
public:
	virtual MeshBuffer* Create(RendererDevice* renderer_device) override;

private:

	// �@���𒆐S������ˏ�ɂ���
	void NormalComputeSlanting(MeshBuffer* mesh);
	// �@����ʂ���܂������ɂ���
	void NormalComputeStraight(MeshBuffer* mesh);
};