//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �w�i�p�V��
// 
// Created by Ryusei Kajiya on 20151022
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "Unit/unit.h"
#include "Data/data_projection.h"

//*****************************************************************************
// �O���錾
class ShaderBackGround;
class ShaderLambert;
class MeshBuffer;

//*****************************************************************************
// �N���X�݌v
class BackGroundUnit : public Unit
{
public:

	BackGroundUnit(Application* application, SpaceGrid* grid) : Unit(application, grid)
	{
		Initialize();
	}
	virtual ~BackGroundUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:

	// �V�F�[�_�[
	ShaderBackGround* _shader;
	//ShaderLambert* _shader;
	// ���b�V��
	MeshBuffer* _mesh;

	// �e�N�X�`��
	LPDIRECT3DCUBETEXTURE9 _texture;

};