//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �_
// 
// Created by Ryusei Kajiya on 201511214
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "Unit/unit.h"
#include "Data/data_world.h"
#include "Data/data_velocity.h"

//*****************************************************************************
// �O���錾
class ShaderStaticToonCloud;
class MeshBuffer;

//*****************************************************************************
// �N���X�݌v
class CloudsUnit : public Unit
{
public:

	CloudsUnit(
		Application* application,
		World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~CloudsUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override{}

	// �_�̃|�W�V�����ݒ�
	void CloudSettingPosition();

private:

	static const u32 kCloudMax = 15;

	// �V�F�[�_�[
	ShaderStaticToonCloud* _shader;
	u32 _shader_size;
	// �V�F�[�_�p�����[�^�[�̐ݒ�
	void SettingShaderParameter();
	data::World _world[kCloudMax];
	D3DXMATRIX _work_world_matrix[kCloudMax];
	data::Velocity _velocity;
	D3DXMATRIX _matrix_view_projection;
	// ���b�V��
	std::vector<MeshBuffer*> _mesh_list;

	// �_�I��
	void CloudSelect();

	// ���W�̈ړ�
	void MovePosition();
	// ���W�̌��E
	void LimitedPosition();
};