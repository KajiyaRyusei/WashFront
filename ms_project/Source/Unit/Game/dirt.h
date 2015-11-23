//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �悲��
// 
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "Unit/unit.h"
#include "Data/data_world.h"

//*****************************************************************************
// �O���錾
class ShaderDirt;

//*****************************************************************************
// �N���X�݌v
class DirtUnit : public Unit
{
public:

	DirtUnit(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}

	virtual ~DirtUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;
	virtual void CollisionSphere() override;

	// ���W�ݒ�
	void SetPosition(const D3DXVECTOR3& position);

private:

	// �V�F�[�_�[
	ShaderDirt* _shader;
	// �V�F�[�_�p�����[�^�[�̐ݒ�
	void SettingShaderParameter();
	data::World _world;

	D3DXMATRIX _matrix_world_view_projection;
	bool _is_invisible;

};