//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���e
// 
// Created by Ryusei Kajiya on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit/Title/title_weapon.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"
#include "Algorithm/often_use.h"
#include "Shader/Shader/toon_weapon_shader.h"
#include "World/collision_grid.h"

//���\�[�X
#include "Resource/cube_texture_resource.h"
#include "Resource/texture_resource.h"
#include "Resource/animation_mesh_resource.h"

//*****************************************************************************
// �萔
namespace
{
	static const fx32 kLevelOneBulletSize = 3.f;
	static const fx32 kLevelTwoBulletSize = 5.f;
	static const fx32 kLevelThreeBulletSize = 7.f;
	static const fx32 kBulletVelocity = 0.08f;
}

//=============================================================================
// ������
void TitleWeaponUnit::Initialize()
{
	// ���b�V���̍쐬
	
	auto mesh_list = _game_world->GetAnimationMeshResource()->Get(ANIMATION_MESH_RESOURE_GRANDPA);
	// �e�N�X�`��
	
	LPDIRECT3DTEXTURE9 albedo_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_PLAYER_BAG_TEXTURE);
	LPDIRECT3DCUBETEXTURE9 diffuse_cube_map = _game_world->GetCubeTextureResource()->Get(CUBE_TEXTURE_RESOURE_GRID_ZERO_ZERO_DIFFUSE);
	LPDIRECT3DCUBETEXTURE9 specular_cube_map = _game_world->GetCubeTextureResource()->Get(CUBE_TEXTURE_RESOURE_GRID_ZERO_ZERO_SPECULAR);
	LPDIRECT3DTEXTURE9 toon_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_TOON_TEXTURE);

	// �V�F�[�_�̍쐬
	_shader_size = mesh_list.size();
	_shader = new ShaderToonWeapon[mesh_list.size()];
	for( u32 shader_index = 0; shader_index < _shader_size; ++shader_index )
	{
		_shader[shader_index].SetToonTexture(toon_map);
		_shader[shader_index].SetAlbedoTexture(albedo_map);
		_shader[shader_index].SetDiffuseCubeMap(diffuse_cube_map);
		_shader[shader_index].SetSpecularCubeMap(specular_cube_map);
	}

	_shader->SetAlbedoTexture(albedo_map);
	_shader->SetDiffuseCubeMap(diffuse_cube_map);
	_shader->SetSpecularCubeMap(specular_cube_map);

	// ���W�̐ݒ�
	_position.current = _game_world->GetCollisionGrid()->CellCenterPoint(2, 1);
	_position.current.y = 5.f;
	_position.previous = _position.current;
	_world.position = _position.current;
	_world.scale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);
	_world.rotation = D3DXVECTOR3(0.f, 0.f, 0.f);

}

//=============================================================================
// �I��
void TitleWeaponUnit::Finalize()
{
	SafeDeleteArray(_shader);
}

//=============================================================================
// �X�V
void TitleWeaponUnit::Update()
{

}
//=============================================================================
// �`��
void TitleWeaponUnit::Draw()
{
	// �V�F�[�_�p�����[�^�[�̍X�V
	SettingShaderParameter();

	auto mesh_list = _game_world->GetAnimationMeshResource()->Get(ANIMATION_MESH_RESOURE_WEAPON_01);
	D3DXMATRIX animation_matrix_list[ShaderToonWeapon::kMatrixMax];
	for( u8 i = 0; i < ShaderToonWeapon::kMatrixMax; ++i )
	{
		D3DXMatrixIdentity(&animation_matrix_list[i]);
	}

	D3DXMATRIX test_matrix;
	D3DXMatrixIdentity(&test_matrix);
	D3DXMatrixRotationYawPitchRoll(&test_matrix,0.0f,0.0f,0.1f);

	//test_matrix._41 = 0.5f;
	u32 mesh_id = 0;
	animation_matrix_list[2] = _animation_matrix;

	for( auto it = mesh_list.begin(); it != mesh_list.end(); ++it, ++mesh_id )
	{
		_shader[mesh_id].SetAnimationMatrix(animation_matrix_list);
		S_GetCommandBuffer()->PushRenderState(RENDER_STATE_DEFAULT, GetID());
		S_GetCommandBuffer()->PushShader(&_shader[mesh_id], GetID());
		S_GetCommandBuffer()->PushMesh((*it), GetID());
	}

}
//=============================================================================
// �Փ˔���p�X�V
void TitleWeaponUnit::CollisionUpdate()
{
}
//=============================================================================
// �V�F�[�_�p�����[�^�[�̐ݒ�
void TitleWeaponUnit::SettingShaderParameter()
{
	// �J�����擾
	Camera* camera = _application->GetCameraManager()->GetCurrentCamera();
	// �s��̍쐬
	algo::CreateWVP(_matrix_world_view_projection, _world.matrix, camera);
	// ���C�g�̕����쐬
	D3DXVECTOR4 light_direction(0.2f, -0.8f, 0.5f, 0.f);
	D3DXVECTOR4 ambient(0.97f, 0.8f, 0.75f, 1.f);
	D3DXVECTOR4 eye(camera->GetVectorEye(), 0.f);

	for( u32 shader_index = 0; shader_index < _shader_size; ++shader_index )
	{
		// �V�F�[�_�̐ݒ�
		_shader[shader_index].SetWorldViewProjection(_matrix_world_view_projection);
		_shader[shader_index].SetWorld(_world.matrix);
		_shader[shader_index].SetLightDirection(light_direction);
		_shader[shader_index].SetEyePosition(eye);
		_shader[shader_index].SetWorld(_world.matrix);
	}
}

//=============================================================================
// �s��̐ݒ�
void TitleWeaponUnit::SetPosition(
	const D3DXMATRIX& world,
	const D3DXMATRIX& animation)
{
	_world.matrix = world;
	_animation_matrix = animation;
}
//=============================================================================
// �e�N�X�`����I��
void TitleWeaponUnit::SelectAlbedoTexture(bool _is_player_one)
{
	LPDIRECT3DTEXTURE9 albedo_map;

	if( _is_player_one )
	{
		albedo_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_PLAYER_BAG_TEXTURE);
	}
	else
	{
		albedo_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_PLAYER_2_BAG);
	}

	for( u32 shader_index = 0; shader_index < _shader_size; ++shader_index )
	{
		_shader[shader_index].SetAlbedoTexture(albedo_map);
	}
}