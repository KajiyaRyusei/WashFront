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
#include "Renderer/directx9.h"
#include "Shader/Shader/PBL_static_shader.h"
#include "Resource/Mesh/Mesh/mesh_factory_cube.h"
#include "World/collision_grid.h"

//=============================================================================
// ������
void BulletUnit::Initialize()
{
	// �V�F�[�_�̍쐬
	_shader = new ShaderPBLStatic();

	// ���b�V���̍쐬
	MeshFactoryCube mesh_factory;
	_mesh = mesh_factory.Create(_application->GetRendererDevice());

	// �e�N�X�`��
	LPDIRECT3DDEVICE9 device = _application->GetRendererDevice()->GetDevice();
	D3DXCreateCubeTextureFromFileEx(device, L"Data/CubeTexture/rnl_cross.dds", 2, 1, 0, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xff, nullptr, nullptr, &_diffuse_cube_map);
	D3DXCreateCubeTextureFromFileEx(device, L"Data/CubeTexture/rnl_cross.dds", 0, 0, 0, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xff, nullptr, nullptr, &_specular_cube_map);

	ASSERT(S_OK == D3DXCreateTextureFromFileEx(device, L"Data/Texture/Orange_glazed_pxr128_bmp.jpg", 0, 0, 0, 0, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xff, nullptr, nullptr, &_albedo_map),"�e�N�X�`���ǂݍ��ݎ��s");
	ASSERT(S_OK == D3DXCreateTextureFromFileEx(device, L"Data/Texture/Orange_glazed_pxr128_normal.jpg", 0, 0, 0, 0, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xff, nullptr, nullptr, &_normal_map), "�e�N�X�`���ǂݍ��ݎ��s");


	// ���W�̐ݒ�
	_position.current = D3DXVECTOR3(0.f, 0.f, 0.f);
	_position.previous = _position.current;
	_world.position = _position.current;
	_world.scale = D3DXVECTOR3(1.f, 1.f, 1.f);
	_world.rotation = D3DXVECTOR3(0.f, 0.f, 0.f);

	// �e�̐ݒ�
	_start_point = _position.current;
	_end_point = _position.current;
	_control_point = _position.current;
	_frame_velocity = 0.f;
	_frame = 1.f;

	// �{�����[���̍쐬
	CreateVolumeShpre(_world.position, _world.scale.x);

	// ��Ԃɓ˂�����
	_game_world->GetCollisionGrid()->AddUnit(this, _position);
}

//=============================================================================
// �I��
void BulletUnit::Finalize()
{
	SafeRelease(_diffuse_cube_map);
	SafeRelease(_specular_cube_map);
	SafeRelease(_albedo_map);
	SafeRelease(_normal_map);
	SafeDelete(_mesh);
	SafeDelete(_shader);
}

//=============================================================================
// �X�V
void BulletUnit::Update()
{
	// �V�F�[�_�p�����[�^�[�̍X�V
	if( _frame >= 1.f)
	{
		//_position.current = D3DXVECTOR3(100000.f, 100000.f, 100000.f);
		//_game_world->GetCollisionGrid()->MoveUnit(this, _position);
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
// �Փ˔��莞����
void BulletUnit::CollisionSphere()
{
	_frame = 1.f;
}
//=============================================================================
// �`��
void BulletUnit::Draw()
{
	SettingShaderParameter();
	// �`�悷������������ށF�P�x�̕`��ɂP�x�����Ă΂Ȃ�����
	if( _frame < 1.f )
	{
		S_GetCommandBuffer()->PushRenderState(RENDER_STATE_DEFAULT, GetID());
		S_GetCommandBuffer()->PushShader(_shader, GetID());
		S_GetCommandBuffer()->PushMesh(_mesh, GetID());
	}

	_shpere->DebugDraw();
}

//=============================================================================
// �V�F�[�_�p�����[�^�[�̐ݒ�
void BulletUnit::SettingShaderParameter()
{
	// �J�����擾
	CameraGamePlayer* camera = static_cast<CameraGamePlayer*>(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER));
	// �s��̍쐬
	_world.position = _position.current;
	_world.rotation.x += 0.5f;
	algo::CreateWorld(_world.matrix, _world.position, _world.rotation, _world.scale);
	algo::CreateWVP(_matrix_world_view_projection, _world.matrix, camera);
	// ���C�g�̕����쐬
	D3DXVECTOR4 light_direction(0.2f, -0.8f, 0.5f, 0.f);
	D3DXVECTOR4 ambient(0.0f, 0.0f, 1.0f, 1.f);
	D3DXVECTOR4 eye(camera->GetVectorEye(), 0.f);
	// �V�F�[�_�̐ݒ�
	_shader->SetWorldViewProjection(_matrix_world_view_projection);
	_shader->SetWorld(_world.matrix);
	_shader->SetLightDirection(light_direction);
	_shader->SetAlbedoTexture(_albedo_map);
	_shader->SetNormalTexture(_normal_map);
	_shader->SetAmbientColor(ambient);
	_shader->SetDiffuseCubeMap(_diffuse_cube_map);
	_shader->SetSpecularCubeMap(_specular_cube_map);
	_shader->SetEyePosition(eye);
	_shader->SetFresnel(0.5f);
	_shader->SetMetalness(0.1f);
	_shader->SetRoughness(0.8f);
	_shader->SetWorld(_world.matrix);
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
	_control_point.y += 3.f;
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
