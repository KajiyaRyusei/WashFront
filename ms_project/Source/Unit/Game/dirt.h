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
class ShaderPBLStatic;
class MeshBuffer;

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
	bool _is_invisible;

};