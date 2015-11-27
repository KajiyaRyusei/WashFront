////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////
//// �����Ԃ��̃I�u�W�F�N�g�v�[��
//// 
//// Created by Ryusei Kajiya on 20151125
////
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
////*****************************************************************************
//// ���d�C���N���[�h�h�~
//#pragma once
//
////*****************************************************************************
//// include
//#include "Unit/unit.h"
//#include "water_spray.h"
//
////*****************************************************************************
//// �O���錾
//class MeshBuffer;
//class ShaderWaterSpray;
//
////*****************************************************************************
//// �N���X�݌v
//class WaterSprayPool : public Unit
//{
//public:
//	WaterSprayPool(Application* application, World* world);
//	virtual ~WaterSprayPool();
//
//	// �쐬
//	void Create(
//		const D3DXVECTOR3& position,
//		const D3DXQUATERNION& quaternion);
//
//	// �A�j���[�V����:�`������˂Ă�B
//	void Animate();
//
//	virtual void Initialize() override{};
//	virtual void Finalize() override{};
//	virtual void Update() override{};
//	virtual void Draw() override{};
//	virtual void CollisionUpdate() override{};
//
//private:
//	static const u32 kPoolSize = 10;
//	WaterSpray _particles[kPoolSize];
//	WaterSpray* _first_available;
//	MeshBuffer* _mesh;
//	D3DXMATRIX _spray_matrices[kPoolSize];
//	ShaderWaterSpray* _shader;
//};
