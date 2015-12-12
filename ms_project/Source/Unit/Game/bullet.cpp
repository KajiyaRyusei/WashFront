//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �o���b�g
// 
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit/Game/bullet.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"
#include "Algorithm/often_use.h"
#include "World/collision_grid.h"

//=============================================================================
// �萔
namespace
{
	static const fx32 kLevelOneBulletSize = 3.f;
	static const fx32 kLevelTwoBulletSize = 5.f;
	static const fx32 kLevelThreeBulletSize = 7.f;
}

//=============================================================================
// ������
void BulletUnit::Initialize()
{
	// ���W�̐ݒ�
	_position.current = D3DXVECTOR3(0.f, 0.f, 0.f);
	_position.previous = _position.current;
	_world.position = _position.current;
	_world.scale = D3DXVECTOR3(_bullet_size, _bullet_size, _bullet_size);
	_world.rotation = D3DXVECTOR3(0.f, 0.f, 0.f);

	// �e�̐ݒ�
	_start_point = _position.current;
	_end_point = _position.current;
	_control_point = _position.current;
	_frame_velocity = 0.f;
	_frame = 1.f;

	// �{�����[���̍쐬
	CreateVolumeShpre(_world.position, _world.scale.x);

	ReNewBulletSize(kLevelOneBulletSize);

	// ��Ԃɓ˂�����
	_game_world->GetCollisionGrid()->AddUnit(this, _position);
}

//=============================================================================
// �I��
void BulletUnit::Finalize()
{

}

//=============================================================================
// �X�V
void BulletUnit::Update()
{
	// �V�F�[�_�p�����[�^�[�̍X�V
	if( _frame >= 1.f)
	{
		_shpere->position = D3DXVECTOR3(100000.f, 100000.f, 100000.f);
	}
	else
	{
		Move();
		_game_world->GetCollisionGrid()->MoveUnit(this, _position);
		_shpere->position = _position.current;
	}
}
//=============================================================================
// �Փ˔���p�X�V
void BulletUnit::CollisionUpdate()
{

}
//=============================================================================
// �Փ˔��莞���� : ��
void BulletUnit::CollisionSphere()
{
	_frame = 1.f;
}
//=============================================================================
// �Փ˔��莞���� : �{�b�N�X
void BulletUnit::CollisionBox()
{
	_frame = 1.f;
}
//=============================================================================
// �`��
void BulletUnit::Draw()
{
	//_shpere->DebugDraw();
}

//=============================================================================
// ����
void BulletUnit::Fire(
	const D3DXVECTOR3& start,
	const D3DXVECTOR3& end,
	const fx32 velocity)
{
	if( _frame < 1.f )
	{
		return;
	}
	_start_point = start;
	_end_point = end;
	_control_point = (start + end) / 2;
	_control_point.y += 5.f;
	_frame_velocity = velocity;
	_frame = 0.f;
	_position.current = start;
}

//=============================================================================
// �ړ�
void BulletUnit::Move()
{
	algo::BezierCurve2D(_position.current,_start_point,_end_point,_control_point,_frame);
	_frame += _frame_velocity;
}

//=============================================================================
// �o���b�g�T�C�Y�X�V
void BulletUnit::ReNewBulletSize(const fx32 size)
{
	_bullet_size = size;
	_shpere->radius = _bullet_size;
	_world.scale = D3DXVECTOR3(_bullet_size, _bullet_size, _bullet_size);
}