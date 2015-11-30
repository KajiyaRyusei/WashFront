//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Animation���b�V�����\�[�X
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
// �A�j���[�V�������b�V�����\�[�XID
enum ANIMATION_MESH_RESOURE_ID
{
	ANIMATION_MESH_RESOURE_GRANDPA = 0,
	ANIMATION_MESH_RESOURE_WEAPON_01,
};

//*****************************************************************************
// �N���X�݌v
class AnimationMeshResource : public Resource<std::vector<MeshBuffer*>, ANIMATION_MESH_RESOURE_ID>
{
public:
	AnimationMeshResource(){}
	virtual ~AnimationMeshResource(){ Clear(); }
	// �쐬
	void Create(ANIMATION_MESH_RESOURE_ID id, RendererDevice* device) override;
	// �S�폜
	void Clear() override;
	// �擾
	std::vector<MeshBuffer*> Get(ANIMATION_MESH_RESOURE_ID id) override;
};