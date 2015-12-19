//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Static���b�V�����\�[�X
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
// �X�^�e�B�b�N���b�V�����\�[�XID
enum STATIC_MESH_RESOURE_ID
{
	STATIC_MESH_RESOURE_BILL_000 = 0,
	STATIC_MESH_RESOURE_BILL_001,
	STATIC_MESH_RESOURE_BILL_002,
	STATIC_MESH_RESOURE_BILL_003,
	STATIC_MESH_RESOURE_BILL_HAIKEI,
	STATIC_MESH_RESOURE_CLOUD_000,
	STATIC_MESH_RESOURE_CLOUD_001,
	STATIC_MESH_RESOURE_CLOUD_002,
	STATIC_MESH_RESOURE_BILL_001_LOW,
	STATIC_MESH_RESOURE_BILL_002_LOW,
	STATIC_MESH_RESOURE_ROAD
};

//*****************************************************************************
// �N���X�݌v
class StaticMeshResource : public Resource<std::vector<MeshBuffer*>, STATIC_MESH_RESOURE_ID>
{
public:
	StaticMeshResource(){}
	virtual ~StaticMeshResource(){ Clear(); }

	// �쐬
	void Create(STATIC_MESH_RESOURE_ID id, RendererDevice* device) override;
	// �S�폜
	void Clear() override;
	// �擾
	std::vector<MeshBuffer*> Get(STATIC_MESH_RESOURE_ID id) override;
};