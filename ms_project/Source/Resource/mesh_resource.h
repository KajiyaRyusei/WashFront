//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���b�V�����\�[�X
//
// Created by Ryusei Kajiya on 20151102
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "Resource/resource.h"

//*****************************************************************************
// �O���錾
class MeshBuffer;

//*****************************************************************************
// ���b�V�����\�[�XID
enum MESH_RESOURE_ID
{
	MESH_RESOURE_BOX = 0,
	MESH_RESOURE_SPRITE,
	MESH_RESOURE_MESH_FIELD,
	MESH_RESOURE_WATER_CYLINDER,
	MESH_RESOURE_WATER_CYLINDER_BACK,
};

//*****************************************************************************
// �N���X�݌v
class MeshResource : public Resource<MeshBuffer*, MESH_RESOURE_ID>
{
public:
	MeshResource(){}
	virtual ~MeshResource(){ Clear(); }

	// �쐬
	void Create(MESH_RESOURE_ID id, RendererDevice* device) override;
	// �S�폜
	void Clear() override;
	// �擾
	MeshBuffer* Get(MESH_RESOURE_ID id) override;
};