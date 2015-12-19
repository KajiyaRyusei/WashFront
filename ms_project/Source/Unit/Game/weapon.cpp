//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���e
// 
// Created by Ryusei Kajiya on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit/Game/weapon.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"
#include "Algorithm/often_use.h"
#include "Shader/Shader/toon_weapon_shader.h"
#include "World/collision_grid.h"
#include "Unit/Game/bullet.h"
#include "Unit/Game/water_bullet.h"

//���\�[�X
#include "Resource/cube_texture_resource.h"
#include "Resource/texture_resource.h"
#include "Resource/animation_mesh_resource.h"

//*****************************************************************************
// �萔
namespace
{
	static const fx32 kBulletVelocity = 0.08f;
}

//=============================================================================
// ������
void WeaponUnit::Initialize()
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

	// ���W�̐ݒ�
	_position.current = _game_world->GetCollisionGrid()->CellCenterPoint(2, 1);
	_position.current.y = 5.f;
	_position.previous = _position.current;
	_world.position = _position.current;
	_world.scale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);
	_world.rotation = D3DXVECTOR3(0.f, 0.f, 0.f);

	// �e
	_bullet = new BulletUnit(_application, _game_world);
	_water_bullet = new WaterBulletUnit(_application, _game_world);

	WeaponLevel(WEAPON_LEVEL_ONE);
}

//=============================================================================
// �I��
void WeaponUnit::Finalize()
{
	SafeDelete(_bullet);
	SafeDelete(_water_bullet);
	SafeDeleteArray(_shader);
}

//=============================================================================
// �X�V
void WeaponUnit::Update()
{
	_bullet->Update();
	_water_bullet->Update();
#ifdef _DEBUG
	DebugWeaponLevelSelect();
#endif
}
//=============================================================================
// �`��
void WeaponUnit::Draw()
{
	// �V�F�[�_�p�����[�^�[�̍X�V
	SettingShaderParameter();

	auto mesh_list = _game_world->GetAnimationMeshResource()->Get(ANIMATION_MESH_RESOURE_WEAPON_01);
	D3DXMATRIX animation_matrix_list[ShaderToonWeapon::kMatrixMax];
	for( u8 i = 0; i < ShaderToonWeapon::kMatrixMax; ++i )
	{
		D3DXMatrixIdentity(&animation_matrix_list[i]);
	}

	u32 mesh_id = 0;
	animation_matrix_list[2] = _animation_matrix;

	for( auto it = mesh_list.begin(); it != mesh_list.end(); ++it, ++mesh_id )
	{
		_shader[mesh_id].SetAnimationMatrix(animation_matrix_list);
		S_GetCommandBuffer()->PushRenderState(RENDER_STATE_DEFAULT, GetID());
		S_GetCommandBuffer()->PushShader(&_shader[mesh_id], GetID());
		S_GetCommandBuffer()->PushMesh((*it), GetID());
	}

	// �e�̕`��
	_bullet->Draw();
	_water_bullet->Draw();
}
//=============================================================================
// �Փ˔���p�X�V
void WeaponUnit::CollisionUpdate()
{
	_bullet->CollisionUpdate();
}
//=============================================================================
// �V�F�[�_�p�����[�^�[�̐ݒ�
void WeaponUnit::SettingShaderParameter()
{
	// �J�����擾
	Camera* camera = _application->GetCameraManager()->GetCurrentCamera();
	// �s��̍쐬
	algo::CreateWVP(_matrix_world_view_projection, _world.matrix, camera);
	// ���C�g�̕����쐬
	D3DXVECTOR4 light_direction(0.2f, -0.8f, 0.5f, 0.f);
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
// ����
void WeaponUnit::Fire(
	const D3DXVECTOR3& start,
	const D3DXVECTOR3& end,
	const Command::CONTROLLER_TYPE controller_type)
{
	_bullet->Fire(start, end, kBulletVelocity, controller_type);
	_water_bullet->Fire(end);
}

//=============================================================================
// �s��̐ݒ�
void WeaponUnit::SetPosition(
	const D3DXMATRIX& world,
	const D3DXMATRIX& animation)
{
	_world.matrix = world;
	_animation_matrix = animation;
}

//=============================================================================
// �v���C���[�̐ݒ�
void WeaponUnit::SetPlayer(PlayerUnit* player)
{
	_water_bullet->SetPlayer(player);
}

//=============================================================================
// ���탌�x���A�b�v
void WeaponUnit::WeaponLevel(WEAPON_LEVEL level)
{
	D3DXVECTOR4 ambient;
	switch( level )
	{
	case WEAPON_LEVEL_ONE:
		_bullet->ReNewBulletSize(WEAPON_LEVEL_ONE);
		ambient = D3DXVECTOR4(0.2f, 0.2f, 0.55f, 1.f);
		_water_bullet->ReNewAmbientColor(ambient);
		break;
	case WEAPON_LEVEL_TWO:
		_bullet->ReNewBulletSize(WEAPON_LEVEL_TWO);
		ambient = D3DXVECTOR4(0.45f, 0.3f, 0.2f, 1.f);
		_water_bullet->ReNewAmbientColor(ambient);
		break;
	case WEAPON_LEVEL_THREE:
		_bullet->ReNewBulletSize(WEAPON_LEVEL_THREE);
		ambient = D3DXVECTOR4(1.0f, 0.4f, 0.15f, 1.f);
		_water_bullet->ReNewAmbientColor(ambient);
		break;
	default:
		break;
	}
}

//=============================================================================
// �f�o�b�O�p���탌�x���X�V
#ifdef _DEBUG
#include "Input/input_manager.h"
void WeaponUnit::DebugWeaponLevelSelect()
{
	if( _application->GetInputManager()->CheckTrigger(INPUT_EVENT_1) )
	{
		WeaponLevel(WEAPON_LEVEL_ONE);
	}
	else if( _application->GetInputManager()->CheckTrigger(INPUT_EVENT_2) )
	{
		WeaponLevel(WEAPON_LEVEL_TWO);
	}
	else if( _application->GetInputManager()->CheckTrigger(INPUT_EVENT_3) )
	{
		WeaponLevel(WEAPON_LEVEL_THREE);
	}
}
#endif

//=============================================================================
// �e�N�X�`����I��
void WeaponUnit::SelectAlbedoTexture(bool _is_player_one)
{
	LPDIRECT3DTEXTURE9 albedo_map;

	if( _is_player_one )
	{
		albedo_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_PLAYER_BAG_TEXTURE);
	}
	else
	{
		albedo_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_PLAYER_2_TEXTURE);
	}

	for( u32 shader_index = 0; shader_index < _shader_size; ++shader_index )
	{
		_shader[shader_index].SetAlbedoTexture(albedo_map);
	}
}