//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �A�j���[�V�������f��
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
#include "Data/data_oaf.h"

//*****************************************************************************
// �O���錾
class ShaderAnimation;
class MeshBuffer;
class AnimationSystem;

//*****************************************************************************
// �N���X�݌v
class AnimationModelUnit : public Unit
{
public:

	AnimationModelUnit(Application* application, SpaceGrid* grid) : Unit(application, grid)
	{
		Initialize();
	}
	virtual ~AnimationModelUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:

	// �V�F�[�_�[
	ShaderAnimation* _shader;
	// ���b�V��
	std::vector<MeshBuffer*> _mesh_list;
	// �A�j���[�V����
	data::ObjectAnimationFile _animation;
	// �A�j���[�V�����V�X�e��
	AnimationSystem* _animation_system;

};