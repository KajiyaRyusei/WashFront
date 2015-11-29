//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �o���b�g
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
class ShaderPBLStatic;
class MeshBuffer;

//*****************************************************************************
// �N���X�݌v
class BulletUnit : public Unit
{
public:

	BulletUnit(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}

	virtual ~BulletUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;
	virtual void CollisionSphere() override;

	// ����
	void Fire(
		const D3DXVECTOR3& start,
		const D3DXVECTOR3& end,
		const fx32 velocity);

private:

	// �V�F�[�_�[
	ShaderPBLStatic* _shader;
	// ���b�V��
	MeshBuffer* _mesh;
	// �V�F�[�_�p�����[�^�[�̐ݒ�
	void SettingShaderParameter();
	data::World _world;

	D3DXMATRIX _matrix_world_view_projection;
	LPDIRECT3DCUBETEXTURE9 _diffuse_cube_map;
	LPDIRECT3DCUBETEXTURE9 _specular_cube_map;
	LPDIRECT3DTEXTURE9 _albedo_map;
	LPDIRECT3DTEXTURE9 _normal_map;

	D3DXVECTOR3 _start_point;
	D3DXVECTOR3 _end_point;
	D3DXVECTOR3 _control_point;
	fx32 _frame_velocity;
	fx32 _frame;

	// �ړ�
	void Move();
};