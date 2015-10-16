//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �e�X�g�p���j�b�g : 3D�I�u�W�F�N�g�̏�����
// 
// Created by Ryusei Kajiya on 20151009
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "unit.h"

//*****************************************************************************
// �O���錾
class ShaderLambert;
class MeshBuffer;

//*****************************************************************************
// �N���X�݌v
class TestUnit : public Unit
{
public:

	TestUnit(Application* application, SpaceGrid* grid) : Unit(application, grid)
	{
		Initialize();
	}
	virtual ~TestUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:

	// �V�F�[�_�[
	ShaderLambert* _shader;

	// ���b�V��
	MeshBuffer* _mesh;
};