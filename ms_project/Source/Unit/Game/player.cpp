//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �v���C���[
// 
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit/Game/player.h"
#include "Shader/Shader/PBL_animation_shader.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"
#include "Animation/animation_system.h"
#include "Input/input_manager.h"
#include "Algorithm/often_use.h"
#include "DevelopTool/develop_tool_manager.h"
#include "Unit/Game/aim.h"
#include "Command/command_handler.h"
#include "World/collision_grid.h"
#include "Unit/Game/weapon.h"
#include "Unit/Game/water_back.h"

//���\�[�X
#include "Resource/cube_texture_resource.h"
#include "Resource/texture_resource.h"
#include "Resource/animation_mesh_resource.h"

//*****************************************************************************
// �萔
namespace
{
	static const fx32 kPassFrameVelocity = 0.0012f;
}

//=============================================================================
// ������
void PlayerUnit::Initialize()
{

	// �A�j���[�V�������f���̓ǂݍ���
	auto mesh_list = _game_world->GetAnimationMeshResource()->Get(ANIMATION_MESH_RESOURE_GRANDPA);
	_animation.LoadAnimationFile("Data/Animation/ojianime_2.oaf", mesh_list.size());

	// �A�j���[�V�����V�X�e���̍쐬
	_animation_system = new AnimationSystem();

	LPDIRECT3DTEXTURE9 albedo_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_PLAYER_TEXTURE);
	LPDIRECT3DCUBETEXTURE9 diffuse_cube_map = _game_world->GetCubeTextureResource()->Get(CUBE_TEXTURE_RESOURE_GRID_ZERO_ZERO_DIFFUSE);
	LPDIRECT3DCUBETEXTURE9 specular_cube_map = _game_world->GetCubeTextureResource()->Get(CUBE_TEXTURE_RESOURE_GRID_ZERO_ZERO_SPECULAR);

	// �V�F�[�_�̍쐬
	_shader_size = mesh_list.size();
	_shader = new ShaderPBLAnimation[mesh_list.size()];

	for( u32 shader_index = 0; shader_index < _shader_size; ++shader_index )
	{
		_shader[shader_index].SetAlbedoTexture(albedo_map);
		_shader[shader_index].SetDiffuseCubeMap(diffuse_cube_map);
		_shader[shader_index].SetSpecularCubeMap(specular_cube_map);
	}

	// ���W
	_position.current = D3DXVECTOR3(0.f,0.f,0.f);
	_position.previous = _position.current;
	_world.position = _position.current;
	_world.rotation = D3DXVECTOR3(0.f, 0.f, 0.f);
	_world.scale = D3DXVECTOR3(0.02f, 0.02f, 0.02f);

	// Aim
	_aim = new AimUnit(_application, _game_world);

	// �R�}���h�n���h��
	_command_handler = new CommandHandler();

	// ����
	_weapon = new WeaponUnit(_application, _game_world);

	// ��됅
	_back_water = new WaterBackUnit(_application, _game_world);

	// �p�X
	_pass_point_list[0] = _game_world->GetCollisionGrid()->CellCenterPoint(1, 1);
	_pass_point_list[1] = _game_world->GetCollisionGrid()->CellCenterPoint(3, 1);
	_pass_point_list[2] = _game_world->GetCollisionGrid()->CellCenterPoint(3, 3);
	_pass_point_list[3] = _game_world->GetCollisionGrid()->CellCenterPoint(1, 3);
	_pass_frame = 0;

	// �ŏ��̌����Ă���x�N�g��
	_front_vector = _pass_point_list[1] - _pass_point_list[0];
	_lower_body_rotation = D3DX_PI/2;
}

//=============================================================================
// �I��
void PlayerUnit::Finalize()
{
	SafeDelete(_weapon);
	
	SafeDelete(_aim);
	SafeDelete(_animation_system);
	_animation.UnLoadAnimationFile();
	SafeDeleteArray(_shader);
	SafeDelete(_command_handler);
	SafeDelete(_back_water);
}

//=============================================================================
// �X�V
void PlayerUnit::Update()
{
	// �J�����擾
	CameraGamePlayer* camera = static_cast<CameraGamePlayer*>(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER));
	// �v���C���[�̍��W�ύX
	PassRootDecision();
	// �v���C���[�̃|�W�V������������
	camera->SetPlayerPosition(_position.current);
	
	SettingShaderParameter();
	AimUpdate();
	_weapon->Update();
	_back_water->Update();
	
	
	_animation_system->AdvanceFrame(1);
}
//=============================================================================
// �Փ˔���p�X�V
void PlayerUnit::CollisionUpdate()
{
	// Aim�̏Փ˔���p�X�V
	_aim->CollisionUpdate();

	// �e�𔭎� : ���낢��R�}���h
	Command* command = _command_handler->HandleInput(_application->GetInputManager());
	if( command != nullptr )
	{
		command->Execute(this);
	}
}

//=============================================================================
// �`��
void PlayerUnit::Draw()
{
	// �`�悷������������ށF�P�x�̕`��ɂP�x�����Ă΂Ȃ�����
	D3DXMATRIX animation_matrix_list[ShaderPBLAnimation::kMatrixMax];
	for( u8 i = 0; i < ShaderPBLAnimation::kMatrixMax; ++i )
	{
		D3DXMatrixIdentity(&animation_matrix_list[i]);
	}
	
	CameraGamePlayer* camera = static_cast<CameraGamePlayer*>(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER));
	auto mesh_list = _game_world->GetAnimationMeshResource()->Get(ANIMATION_MESH_RESOURE_GRANDPA);

	u32 mesh_id = 0;
	for( auto it = mesh_list.begin(); it != mesh_list.end(); ++it, ++mesh_id)
	{
		UNREFERENCED_PARAMETER(it);
		_animation_system->ComputeHumanPose(animation_matrix_list, ShaderPBLAnimation::kMatrixMax, _animation, camera->GetCameraRotation(), D3DXVECTOR3(0.f, _lower_body_rotation, 0.f), mesh_id);
		_shader[mesh_id].SetAnimationMatrix(animation_matrix_list);
		S_GetCommandBuffer()->PushRenderState(RENDER_STATE_DEFAULT, GetID());
		S_GetCommandBuffer()->PushShader(&_shader[mesh_id], GetID());
		S_GetCommandBuffer()->PushMesh((*it), GetID());
	}

	// ����̕`��
	_weapon->SetPosition(_position.current, animation_matrix_list[15]);
	_weapon->Draw();

	// ��됅�̕`��
	//_animation_system->ComputeHumanPose(animation_matrix_list, ShaderPBLAnimation::kMatrixMax, _animation, camera->GetCameraRotation(), D3DXVECTOR3(0.f, _lower_body_rotation, 0.f), 1);
	D3DXVECTOR3 back_water_position(_position.current - _front_vector*0.01f);
	back_water_position.y += 1.5f;
	_back_water->SetPosition(back_water_position, camera->GetCameraRotation(), animation_matrix_list[0]);
	_back_water->Draw();

	// Aim�̕`��
	_aim->Draw();
	
}

//=============================================================================
// �V�F�[�_�p�����[�^�[�̐ݒ�
void PlayerUnit::SettingShaderParameter()
{
	// �J�����擾
	CameraGamePlayer* camera = static_cast<CameraGamePlayer*>(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER));
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
		_shader[shader_index].SetAmbientColor(ambient);
		_shader[shader_index].SetEyePosition(eye);
		_shader[shader_index].SetFresnel(0.3f);
		_shader[shader_index].SetMetalness(0.0f);
		_shader[shader_index].SetRoughness(1.0f);
		_shader[shader_index].SetWorld(_world.matrix);
	}
}

//=============================================================================
// Aim�̍X�V
void PlayerUnit::AimUpdate()
{
	// �J�����擾
	CameraGamePlayer* camera = static_cast<CameraGamePlayer*>(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER));

	D3DXVECTOR3 start_position(_world.position.x, _world.position.y + 2.f, _world.position.z);
	_aim->SetStartPosition(start_position);
	_aim->SetEndPosition(camera->GetVectorLookAt());
	// Aim�̍X�V
	_aim->Update();
}

//=============================================================================
// �ړ�
void PlayerUnit::DebugMove(const float rotaion_y)
{
	static const float velocity = 0.3f;
	_position.current.x += -sinf(rotaion_y)*velocity;
	_position.current.z += -cosf(rotaion_y)*velocity;
}

//=============================================================================
// �p�X�v�Z
void PlayerUnit::PassRootDecision()
{
	fx32 floating_index = 0;
	fx32 frame = modf(_pass_frame, &floating_index);
	s32 index = static_cast<s32>(floating_index);
	s32 index2 = (index + 1) % kMaxPass;
	D3DXVec3Lerp(&_position.current, &_pass_point_list[index], &_pass_point_list[index2], frame);
	
	
	_pass_frame += kPassFrameVelocity;
	if( _pass_frame >= static_cast<fx32>(kMaxPass) )
	{
		_pass_frame = 0;
	}

	LowerBodyControl();
}

//=============================================================================
// �����g�̕����𐧌�
void PlayerUnit::LowerBodyControl()
{
	// �J�����擾
	CameraGamePlayer* camera = static_cast<CameraGamePlayer*>(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER));

	// eye�x�N�g��
	D3DXVECTOR3 vector_eye_look_at(camera->GetVectorLookAt() - camera->GetVectorEye());

	// �t�����g�x�N�g��
	_front_vector = camera->GetVectorLookAt() - _position.current;
	D3DXVec3Normalize(&_front_vector, &_front_vector);

	// �p�x�擾
	D3DXVECTOR3 normal_eye_look_at;
	D3DXVECTOR3 normal_front_vector;

	D3DXVec3Normalize(&normal_eye_look_at, &vector_eye_look_at);
	D3DXVec3Normalize(&normal_front_vector, &_front_vector);
	D3DXVECTOR3 normal_minus_front_vector = -normal_front_vector;
	float dot = D3DXVec3Dot(&normal_eye_look_at, &normal_front_vector);

	if( dot <= 0 )
	{
		vector_eye_look_at *= -1;

		D3DXVECTOR3 eye_look_at_12_cross;
		D3DXVec3Cross(&eye_look_at_12_cross, &normal_eye_look_at, &normal_front_vector);
		if( eye_look_at_12_cross.y <= 0 )
		{
			_front_vector *= -1;
			_lower_body_rotation += D3DX_PI;
		}
		if( eye_look_at_12_cross.y > 0 )
		{
			_front_vector *= -1;
			_lower_body_rotation -= D3DX_PI;
		}
	}
}