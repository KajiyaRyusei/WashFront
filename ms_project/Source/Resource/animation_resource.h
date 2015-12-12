//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �A�j���[�V�������\�[�X
//
// Created by Ryusei Kajiya on 20151211
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "Resource/resource.h"
#include "Data/data_oaf.h"

//*****************************************************************************
// �e�N�X�`�����\�[�XID
enum ANIMATION_RESOURE_ID
{
	ANIMATION_RESOURE_STANCE = 0,
	ANIMATION_RESOURE_SHOT
};

//*****************************************************************************
// �N���X�݌v
class AnimationResource : public Resource<data::ObjectAnimationFile*, ANIMATION_RESOURE_ID>
{
public:

	AnimationResource(){}
	virtual ~AnimationResource(){ Clear(); }

	// �쐬
	void Create(ANIMATION_RESOURE_ID id, RendererDevice* device) override
	{
		UNREFERENCED_PARAMETER(id);
		UNREFERENCED_PARAMETER(device);
	};
	// �쐬
	void Create(ANIMATION_RESOURE_ID id, u32 mesh_list_size);
	// �S�폜
	void Clear() override;
	// �擾
	data::ObjectAnimationFile* Get(ANIMATION_RESOURE_ID id) override;
};