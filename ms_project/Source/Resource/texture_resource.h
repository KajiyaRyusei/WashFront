//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �e�N�X�`�����\�[�X
//
// Created by Ryusei Kajiya on 20151122
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "Resource/resource.h"

//*****************************************************************************
// �e�N�X�`�����\�[�XID
enum TEXTURE_RESOURE_ID
{
	TEXTURE_RESOURE_PLAYER_TEXTURE = 0,
	TEXTURE_RESOURE_BILL_TEXTURE,
	TEXTURE_RESOURE_AIM_TEXTURE,
	TEXTURE_RESOURE_DIRT_NORMAL_TEXTURE,
	TEXTURE_RESOURE_WATER_BALL_TEXTURE,
	TEXTURE_RESOURE_WATER_NORMAL_TEXTURE,
	TEXTURE_RESOURE_BILL_METALNESS_TEXTURE,
	TEXTURE_RESOURE_DIRTY_TEXTURE,
	TEXTURE_RESOURE_PLAYER_BAG_TEXTURE,
	TEXTURE_RESOURE_PLAYER_METALNESS_TEXTURE,
	TEXTURE_RESOURE_PLAYER_BAG_METALNESS_TEXTURE,
	TEXTURE_RESOURE_TOON_TEXTURE,
	TEXTURE_RESOURE_BILL_NORMAL_TEXTURE,
	TEXTURE_RESOURE_PLAYER_FACE,
	TEXTURE_RESOURE_PLAYER_2_TEXTURE,
	TEXTURE_RESOURE_PLAYER_2_BAG,
	TEXTURE_RESOURE_PLAYER_2_FACE,
	TEXTURE_RESOURE_BILL_TEXTURE_001,
	TEXTURE_RESOURE_BILL_TEXTURE_002,
	TEXTURE_RESOURE_BILL_TEXTURE_003,
	TEXTURE_RESOURE_BILL_TEXTURE_004,
	TEXTURE_RESOURE_PLAYER_BAG_GREEN,
	TEXTURE_RESOURE_PLAYER_BAG_ORANGE,
};

//*****************************************************************************
// �N���X�݌v
class TextureResource : public Resource<LPDIRECT3DTEXTURE9, TEXTURE_RESOURE_ID>
{
public:

	TextureResource(){}
	virtual ~TextureResource(){ Clear(); }

	// �쐬
	void Create(TEXTURE_RESOURE_ID id, RendererDevice* device) override;
	// �S�폜
	void Clear() override;
	// �擾
	LPDIRECT3DTEXTURE9 Get(TEXTURE_RESOURE_ID id) override;
};