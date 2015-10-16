//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �X�^�e�B�b�N���f��
// 
// Created by Ryusei Kajiya on 20151014
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
class StaticModelUnit : public Unit
{
public:

	StaticModelUnit(Application* application, SpaceGrid* grid) : Unit(application, grid)
	{
		Initialize();
	}
	virtual ~StaticModelUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:

	// �V�F�[�_�[
	ShaderLambert* _shader;

	// ���b�V��
	std::vector<MeshBuffer*> _mesh_list;
};