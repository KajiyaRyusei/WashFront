//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �v���C���[
// 
// Created by Ryusei Kajiya on 20151130
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit/Game/player.h"
#include "Shader/Shader/toon_player_shader.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"
#include "Animation/animation_system.h"
#include "Input/input_manager.h"
#include "Algorithm/often_use.h"
#include "DevelopTool/develop_tool_manager.h"
#include "Unit/Game/aim.h"
#include "World/collision_grid.h"
#include "Unit/Game/weapon.h"
#include "Unit/Game/water_back.h"
//���\�[�X
#include "Resource/cube_texture_resource.h"
#include "Resource/texture_resource.h"
#include "Resource/animation_mesh_resource.h"
#include "Resource/Mesh/mesh_buffer.h"
#include "Resource/Mesh/Mesh/mesh_factory_amo.h"
#include "Resource/animation_resource.h"
// ���[�g
#include "Data/data_route.h"

//*****************************************************************************
// �萔
namespace
{
	static const D3DXVECTOR3 kVectorFromCamera(0.f, 0.f, 5.f);
	static const fx32 kBlendyCoefficient = 0.1f;
}

//=============================================================================
// ������
void PlayerUnit::Initialize()
{
	// ���b�V���̎擾
	auto mesh_list = _game_world->GetAnimationMeshResource()->Get(ANIMATION_MESH_RESOURE_GRANDPA);
	// �A�j���[�V�����̎擾
	_statnce_animation = _game_world->GetAnimationResource()->Get(ANIMATION_RESOURE_STANCE);
	_shot_animation = _game_world->GetAnimationResource()->Get(ANIMATION_RESOURE_SHOT);

	// �A�j���[�V�����V�X�e���̍쐬
	_statnce_animation_system = new AnimationSystem();
	_shot_animation_system = new AnimationSystem();

	LPDIRECT3DTEXTURE9 albedo_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_PLAYER_TEXTURE);
	LPDIRECT3DTEXTURE9 albedo_map2 = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_PLAYER_BAG_TEXTURE);
	LPDIRECT3DTEXTURE9 albedo_map3 = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_PLAYER_FACE);
	LPDIRECT3DCUBETEXTURE9 diffuse_cube_map = _game_world->GetCubeTextureResource()->Get(CUBE_TEXTURE_RESOURE_GRID_ZERO_ONE_DIFFUSE);
	LPDIRECT3DCUBETEXTURE9 diffuse_cube_map2 = _game_world->GetCubeTextureResource()->Get(CUBE_TEXTURE_RESOURE_GRID_ZERO_ZERO_DIFFUSE);
	LPDIRECT3DCUBETEXTURE9 specular_cube_map = _game_world->GetCubeTextureResource()->Get(CUBE_TEXTURE_RESOURE_GRID_ZERO_ONE_SPECULAR);
	LPDIRECT3DCUBETEXTURE9 specular_cube_map2 = _game_world->GetCubeTextureResource()->Get(CUBE_TEXTURE_RESOURE_GRID_ZERO_ZERO_SPECULAR);
	LPDIRECT3DTEXTURE9 toon_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_TOON_TEXTURE);

	// �V�F�[�_�̍쐬
	_shader_size = mesh_list.size();
	_shader = new ShaderToonPlayer[mesh_list.size()];

	for( u32 shader_index = 0; shader_index < _shader_size; ++shader_index )
	{
		_shader[shader_index].SetAlbedoTexture(albedo_map);
		_shader[shader_index].SetToonTexture(toon_map);
		_shader[shader_index].SetDiffuseCubeMap(diffuse_cube_map);
		_shader[shader_index].SetSpecularCubeMap(specular_cube_map);
	}

	_shader[0].SetAlbedoTexture(albedo_map3);
	_shader[2].SetAlbedoTexture(albedo_map3);


	_shader[3].SetDiffuseCubeMap(diffuse_cube_map2);
	_shader[3].SetSpecularCubeMap(specular_cube_map2);
	_shader[3].SetAlbedoTexture(albedo_map2);

	// ���W
	_position.current = D3DXVECTOR3(0.f,0.f,0.f);
	_position.previous = _position.current;
	_world.position = _position.current;
	_world.rotation = D3DXVECTOR3(0.f, 0.f, 0.f);
	_world.scale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);

	// Aim
	_aim = new AimUnit(_application, _game_world);
	_aim->SetPlayer(this);

	// �R�}���h�n���h��
	_command_handler = new CommandHandler();

	// ����
	_weapon = new WeaponUnit(_application, _game_world);
	_weapon->SetPlayer(this);

	// ��됅
	_back_water = new WaterBackUnit(_application, _game_world);

	// �u�����h��
	_destination_shot_animation_blend = 0.f;
	_shot_animation_blend = _destination_shot_animation_blend;
}

//=============================================================================
// �I��
void PlayerUnit::Finalize()
{
	SafeDelete(_weapon);
	
	SafeDelete(_aim);
	SafeDelete(_statnce_animation_system);
	SafeDelete(_shot_animation_system);
	SafeDeleteArray(_shader);
	SafeDelete(_command_handler);
	SafeDelete(_back_water);
}

//=============================================================================
// �X�V
void PlayerUnit::Update()
{
	// �v���C���[�̍��W�ύX
	PassRootDecision();
	AimUpdate();
	_weapon->Update();
	_back_water->Update();
	_statnce_animation_system->AdvanceFrame(1);
	_shot_animation_system->AdvanceFrame(1);
}
//=============================================================================
// �Փ˔���p�X�V
void PlayerUnit::CollisionUpdate()
{
	// Aim�̏Փ˔���p�X�V
	_aim->CollisionUpdate();

	// �e�𔭎� 
	Command* command = _command_handler->HandleInput(_application->GetInputManager(), _controller_type);
	if( command != nullptr )
	{
		_destination_shot_animation_blend = 1.f;
		command->Execute(this);
	}
	else
	{
		_destination_shot_animation_blend = 0.f;
	}

	_shot_animation_blend += (_destination_shot_animation_blend - _shot_animation_blend) * kBlendyCoefficient;

	// �v���C���[�̃|�W�V������������
	_player_camera->SetPlayerPosition(_position.current);

}

//=============================================================================
// �`��
void PlayerUnit::Draw()
{
	Camera* camera = _application->GetCameraManager()->GetCurrentCamera();
	D3DXVECTOR3 culling_point(_position.current);

	if( camera->GetFrustumCulling().ClipCheck(_position.current, 10.f) )
	{
		SettingShaderParameter();

		// �`�悷������������ށF�P�x�̕`��ɂP�x�����Ă΂Ȃ�����
		D3DXMATRIX statnce_animation_matrix_list[ShaderToonPlayer::kMatrixMax];
		D3DXMATRIX shot_animation_matrix_list[ShaderToonPlayer::kMatrixMax];
		D3DXMATRIX animation_matrix_list[ShaderToonPlayer::kMatrixMax];

		auto mesh_list = _game_world->GetAnimationMeshResource()->Get(ANIMATION_MESH_RESOURE_GRANDPA);

		u32 mesh_id = 0;
		for( auto it = mesh_list.begin(); it != mesh_list.end(); ++it, ++mesh_id )
		{
			UNREFERENCED_PARAMETER(it);
			_statnce_animation_system->ComputeHumanPose(statnce_animation_matrix_list, ShaderToonPlayer::kMatrixMax, *_statnce_animation, _player_camera->GetCameraRotation(), mesh_id);
			_shot_animation_system->ComputeHumanPose(shot_animation_matrix_list, ShaderToonPlayer::kMatrixMax, *_shot_animation, _player_camera->GetCameraRotation(), mesh_id);

			for( u32 i = 0; i < ShaderToonPlayer::kMatrixMax;++i )
			{
				animation_matrix_list[i] = statnce_animation_matrix_list[i] * (1 - _shot_animation_blend) + shot_animation_matrix_list[i] * _shot_animation_blend;
			}

			_shader[mesh_id].SetAnimationMatrix(animation_matrix_list);

			S_GetCommandBuffer()->PushRenderState(RENDER_STATE_DEFAULT, GetID());
			S_GetCommandBuffer()->PushShader(&_shader[mesh_id], GetID());
			S_GetCommandBuffer()->PushMesh((*it), GetID());
			
		}

		// ����̕`��
		_weapon->SetPosition(_world.matrix, animation_matrix_list[15]);
		_weapon->Draw();

		// ��됅�̕`��
		CompositionWater2Animation(animation_matrix_list);

		// Aim�̕`��
		_aim->Draw();
	}
	
}

//=============================================================================
// �V�F�[�_�p�����[�^�[�̐ݒ�
void PlayerUnit::SettingShaderParameter()
{
	// �J�����̎擾
	Camera* camera = _application->GetCameraManager()->GetCurrentCamera();

	// �s��̍쐬
	_world.position = _position.current;

	algo::CreateWorld(_world.matrix, _world.position, _world.rotation, _world.scale);
	algo::CreateWVP(_matrix_world_view_projection, _world.matrix, camera);

	// ���C�g�̕����쐬
	D3DXVECTOR4 light_direction(0.2f, -0.8f, 0.5f, 0.f);
	D3DXVECTOR4 ambient(0.97f, 0.8f, 0.75f, 1.0f);
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
// Aim�̍X�V
void PlayerUnit::AimUpdate()
{
	Command* command = _command_handler->HandleInputMove(_application->GetInputManager(), _controller_type);
	if( command != nullptr )
	{
		
		command->Execute(this);
	}
	else
	{
		
		D3DXVECTOR3 zero_vector(0.f,0.f,0.f);
		_aim->SetRotation(zero_vector);
	}

	_aim->Update();
}

//=============================================================================
// ���W�ƌ����ݒ�
void PlayerUnit::PassRootDecision()
{
	data::Route route = _player_camera->GetCurrentRoute();
	D3DXVECTOR3 eye_position = _player_camera->GetVectorEye();

	// ���_�𒆐S�ɒ����_����]
	D3DXMATRIX player_rotation_matrix;
	D3DXMatrixRotationQuaternion(&player_rotation_matrix, &route.player_quaternion);
	D3DXVec3TransformCoord(&_position.current, &kVectorFromCamera, &player_rotation_matrix);
	_position.current += eye_position;

	_world.rotation.y = atan2f(_aim->GetTargetPosition().x - _position.current.x, _aim->GetTargetPosition().z - _position.current.z);
	_world.rotation.x = atan2f(_position.current.y, _aim->GetTargetPosition().y);
	_world.rotation.x += D3DX_PI * -0.3f;
}

//=============================================================================
// ���ƃA�j���[�V���������킹��
void PlayerUnit::CompositionWater2Animation(const D3DXMATRIX* matrices)
{
	D3DXMATRIX water_back_matrix;
	D3DXVECTOR4 back_water_position;

	auto mesh_list = _game_world->GetAnimationMeshResource()->Get(ANIMATION_MESH_RESOURE_GRANDPA);

	VERTEX_AMO* vertex = nullptr;
	mesh_list[3]->GetVertexBuffer(0)->Lock(0,0,(void**)&vertex,0);

	u32 vertex_index = 340;
	water_back_matrix = matrices[vertex[vertex_index].bone_index[0]] * vertex[vertex_index].weight[0];
	water_back_matrix += matrices[vertex[vertex_index].bone_index[1]] * vertex[vertex_index].weight[1];
	water_back_matrix += matrices[vertex[vertex_index].bone_index[2]] * vertex[vertex_index].weight[2];
	water_back_matrix += matrices[vertex[vertex_index].bone_index[3]] * vertex[vertex_index].weight[3];

	D3DXVec3Transform(&back_water_position, &vertex[vertex_index].position, &water_back_matrix);

	D3DXMATRIX offset_matrix;
	D3DXVECTOR3 temp_water_position = static_cast<D3DXVECTOR3>(back_water_position);
	D3DXVECTOR3 stans_vector(296, -533.f, -465.f);
	D3DXVECTOR3 shot_vector(339, -573.f, -390.f);
	D3DXVECTOR3 offset_translation_vector = stans_vector * (1 - _shot_animation_blend) + shot_vector * _shot_animation_blend;
	D3DXMatrixTranslation(&offset_matrix, offset_translation_vector.x, offset_translation_vector.y, offset_translation_vector.z);
	D3DXVec3Transform(&back_water_position, &temp_water_position, &offset_matrix);

	temp_water_position = static_cast<D3DXVECTOR3>(back_water_position);
	D3DXVec3Transform(&back_water_position, &temp_water_position, &_world.matrix);

	mesh_list[3]->GetVertexBuffer(0)->Unlock();

	_back_water->SetPosition(static_cast<D3DXVECTOR3>(back_water_position));
	_back_water->Draw();
}

//=============================================================================
// �v���C���[�̍��W���擾
const D3DXVECTOR3 PlayerUnit::GetPosition()
{
	D3DXVECTOR3 player_point;
	player_point = _world.position;

	player_point.y += 1.2f;

	return player_point;
}