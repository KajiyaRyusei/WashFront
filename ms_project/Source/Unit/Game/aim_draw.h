//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �`��pAIM
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
class MeshBuffer;
class ShaderAim;

//*****************************************************************************
// �N���X�݌v
class AimDrawUnit : public Unit
{
public:
	AimDrawUnit(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~AimDrawUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override{};

private:

	// �V�F�[�_�[
	ShaderAim* _shader;
	// ���b�V��
	MeshBuffer* _mesh;
	// �e�N�X�`��
	LPDIRECT3DTEXTURE9 _albedo_map;
	data::World _world;
	D3DXMATRIX _matrix_world_view_projection;
	// �����̈ʒu���Z�o
	void CalculatePosition();
};