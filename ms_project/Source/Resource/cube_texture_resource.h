//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �L���[�u�e�N�X�`�����\�[�X
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
// �L���[�u�e�N�X�`�����\�[�XID
enum CUBE_TEXTURE_RESOURE_ID
{// 2�Ŋ���؂��̂̓f�B�t���[�Y����؂�Ȃ��̂̓X�y�L����
	CUBE_TEXTURE_RESOURE_GRID_ZERO_ZERO_DIFFUSE = 0,
	CUBE_TEXTURE_RESOURE_GRID_ZERO_ZERO_SPECULAR,
	CUBE_TEXTURE_RESOURE_GRID_ZERO_ONE_DIFFUSE,
	CUBE_TEXTURE_RESOURE_GRID_ZERO_ONE_SPECULAR,
};

//*****************************************************************************
// �N���X�݌v
class CubeTextureResource : public Resource<LPDIRECT3DCUBETEXTURE9, CUBE_TEXTURE_RESOURE_ID>
{
public:
	CubeTextureResource(){}
	virtual ~CubeTextureResource(){ Clear(); }

	// �쐬
	void Create(CUBE_TEXTURE_RESOURE_ID id, RendererDevice* device) override;
	// �S�폜
	void Clear() override;
	// �擾
	LPDIRECT3DCUBETEXTURE9 Get(CUBE_TEXTURE_RESOURE_ID id) override;
};