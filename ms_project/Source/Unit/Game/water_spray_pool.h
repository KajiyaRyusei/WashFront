//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �����Ԃ��̃I�u�W�F�N�g�v�[��
// 
// Created by Ryusei Kajiya on 20151125
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "Unit/unit.h"
#include "water_spray.h"

//*****************************************************************************
// �O���錾
class MeshBuffer;
class ShaderWaterSpray;

//*****************************************************************************
// �N���X�݌v
class WaterSprayPool : public Unit
{
public:
	WaterSprayPool(Application* application, World* world);
	virtual ~WaterSprayPool();

	// �쐬
	virtual void Create(
		const D3DXVECTOR3& position,
		const fx32 rotation);

	// �A�j���[�V����:�`������˂Ă�B
	virtual void Animate();

	virtual void Initialize() override{};
	virtual void Finalize() override{};
	virtual void Update() override{};
	virtual void Draw() override{};
	virtual void CollisionUpdate() override{};

private:

	static const u32 kPoolSize = 30;
	WaterSpray _particles[kPoolSize];
	WaterSpray* _first_available;
	MeshBuffer* _mesh;
	D3DXMATRIX _spray_matrices[kPoolSize];
	ShaderWaterSpray* _shader;
	LPDIRECT3DTEXTURE9 _albedo_map;

};
