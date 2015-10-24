//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �v���C���[
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
#include "Data/data_oaf.h"

//*****************************************************************************
// �O���錾
class ShaderPBLAnimation;
class MeshBuffer;
class AnimationSystem;

//*****************************************************************************
// �N���X�݌v
class PlayerUnit : public Unit
{
public:

	PlayerUnit(Application* application, SpaceGrid* grid) : Unit(application, grid)
	{
		Initialize();
	}
	virtual ~PlayerUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;

private:

	// �V�F�[�_�[
	ShaderPBLAnimation* _shader;
	// ���b�V��
	std::vector<MeshBuffer*> _mesh_list;
	// �A�j���[�V����
	data::ObjectAnimationFile _animation;
	// �A�j���[�V�����V�X�e��
	AnimationSystem* _animation_system;

	// �V�F�[�_�p�����[�^�[�̐ݒ�
	void SettingShaderParameter();

};