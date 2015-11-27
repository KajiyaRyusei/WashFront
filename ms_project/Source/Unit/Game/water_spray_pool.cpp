////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////
//// �����Ԃ��̃I�u�W�F�N�g�v�[��
//// 
//// Created by Ryusei Kajiya on 20151125
////
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
////*****************************************************************************
//// include
//#include "Unit/Game/water_spray_pool.h"
//
////=============================================================================
//// �R���X�g���N�^
//WaterSprayPool::WaterSprayPool()
//{
//	_first_available = &_particles[0];
//
//	for( u32 i = 0; i < kPoolSize-1; ++i )
//	{
//		_particles[i].SetNext(&_particles[i+1]);
//	}
//
//	_particles[kPoolSize - 1].SetNext(nullptr);
//}
//
////=============================================================================
//// �쐬
//void WaterSprayPool::Create(
//	const D3DXVECTOR3& position,
//	const D3DXQUATERNION& quaternion)
//{
//	if( _first_available != nullptr)
//	{
//		OutputDebugStringA("�����Ԃ��v�[���������ς�����\n");
//		return;
//	}
//
//	WaterSpray* new_particle = _first_available;
//	_first_available = new_particle->GetNext();
//	new_particle->Initialize(position, quaternion);
//}
////=============================================================================
//// �A�j���[�V����
//void WaterSprayPool::Animate()
//{
//	for( u32 i = 0; i < kPoolSize; ++i )
//	{
//		if( _particles[i].Animate())
//		{
//			_particles[i].SetNext(_first_available);
//			_first_available = &_particles[i];
//		}
//	}
//}