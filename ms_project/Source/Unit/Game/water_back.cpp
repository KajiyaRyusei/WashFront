//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ��됅
// 
// Created by Ryusei Kajiya on 20151123
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit/Game/water_back.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"
#include "Algorithm/often_use.h"
#include "Shader/Shader/water_back_shader.h"
#include "World/collision_grid.h"

//���\�[�X
#include "Resource/cube_texture_resource.h"
#include "Resource/texture_resource.h"
#include "Resource/mesh_resource.h"

//*****************************************************************************
// �萔
namespace
{
	static const fx32 kReleaseOfCoefficient = 0.5f;
}

//=============================================================================
// ������
void WaterBackUnit::Initialize()
{
	// �V�F�[�_�̍쐬
	_shader = new ShaderWaterBack();

	// �e�N�X�`��
	LPDIRECT3DTEXTURE9 albedo_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_WATER_BALL_TEXTURE);
	LPDIRECT3DTEXTURE9 normal_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_WATER_NORMAL_TEXTURE);

	_shader->SetAlbedoTexture(albedo_map);
	_shader->SetNormalTexture(normal_map);

	// ���W�̐ݒ�
	_position.current = D3DXVECTOR3(50.f,10.f,50.f);
	_position.previous = _position.current;
	_world.position = _position.current;
	_world.scale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);
	_world.rotation = D3DXVECTOR3(0.f, 0.f, 0.f);
}

//=============================================================================
// �I��
void WaterBackUnit::Finalize()
{
	SafeDelete(_shader);
}

//=============================================================================
// �X�V
void WaterBackUnit::Update()
{
	// �V�F�[�_�p�����[�^�[�̍X�V
	SettingShaderParameter();
}
//=============================================================================
// �Փ˔���p�X�V
void WaterBackUnit::CollisionUpdate()
{

}

//=============================================================================
// �`��
void WaterBackUnit::Draw()
{
	// �`�悷������������ށF�P�x�̕`��ɂP�x�����Ă΂Ȃ�����
	auto mesh = _game_world->GetMeshResource()->Get(MESH_RESOURE_WATER_CYLINDER_BACK);
	S_GetCommandBuffer()->PushRenderState(RENDER_STATE_TRANSLUCENT, GetID());
	S_GetCommandBuffer()->PushShader(_shader, GetID());
	S_GetCommandBuffer()->PushMesh(mesh, GetID());
}

//=============================================================================
// �V�F�[�_�p�����[�^�[�̐ݒ�
void WaterBackUnit::SettingShaderParameter()
{
	// �J�����擾
	CameraGamePlayer* camera = static_cast<CameraGamePlayer*>(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER));
	// �s��̍쐬
	_world.position = _position.current;
	algo::CreateWorld(_world.matrix, _world.position, _world.rotation, _world.scale);
	_animation_matrix._41 *= 0.1f;
	_animation_matrix._42 *= 0.1f;
	_animation_matrix._43 *= 0.1f;
	_world.matrix = _player_rotation_matrix *_animation_matrix  * _world.matrix;
	algo::CreateWVP(_matrix_world_view_projection, _world.matrix, camera);
	// ���C�g�̕����쐬
	D3DXVECTOR4 light_direction(0.2f, -0.8f, 0.5f, 0.f);
	D3DXVECTOR4 eye(camera->GetVectorEye(), 0.f);

	// �V�F�[�_�̐ݒ�
	_shader->SetWorldViewProjection(_matrix_world_view_projection);
	_shader->SetWorld(_world.matrix );
	_shader->SetLightDirection(light_direction);
	_shader->SetEyePosition(eye);
	_shader->SetFresnel(0.6f);
	_shader->SetMetalness(0.2f);
	_shader->SetRoughness(0.3f);
	_shader->SetWorld(_world.matrix);
	static D3DXVECTOR2 texcoord_move(0.f,0.f);
	//texcoord_move.x += 0.01f;
	texcoord_move.y -= 0.05f;
	_shader->SetTexcoordMove(texcoord_move);
}

//=============================================================================
// ���W�̐ݒ�
void WaterBackUnit::SetPosition(
	const D3DXVECTOR3& position,
	const D3DXVECTOR3& rotation,
	const D3DXMATRIX& animation_matrix)
{
	_position.current = position;
	D3DXMatrixRotationYawPitchRoll(&_player_rotation_matrix, -rotation.y, -rotation.x, rotation.z);
	_animation_matrix = animation_matrix;
}