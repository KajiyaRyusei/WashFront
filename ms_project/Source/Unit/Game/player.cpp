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
#include "Resource/Mesh/Mesh/mesh_factory_amo.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"
#include "Animation/animation_system.h"
#include "Input/input_manager.h"
#include "Algorithm/often_use.h"
#include "DevelopTool/develop_tool_manager.h"
#include "Renderer/directx9.h"
#include "Unit/Game/aim.h"
#include "Command/command_handler.h"
#include "Unit/Game/bullet.h"
#include "World/collision_grid.h"

//*****************************************************************************
// �萔
namespace
{
	static const fx32 kPassFrameVelocity = 0.004f;
}

//=============================================================================
// ������
void PlayerUnit::Initialize()
{
	// �V�F�[�_�̍쐬
	_shader = new ShaderPBLAnimation();

	// ���b�V���̍쐬
	MeshFactoryAMO mesh_factory;
	mesh_factory.Create(_application->GetRendererDevice(), "Data/AnimationModel/oba_walk.amo", _mesh_list);

	// �A�j���[�V�����̓ǂݍ���
	_animation.LoadAnimationFile("Data/Animation/oba_walk.oaf",_mesh_list.size());

	// �A�j���[�V�����V�X�e���̍쐬
	_animation_system = new AnimationSystem();

	// �e�N�X�`��
	LPDIRECT3DDEVICE9 device = _application->GetRendererDevice()->GetDevice();
	D3DXCreateCubeTextureFromFileEx(device, L"Data/CubeTexture/rnl_cross.dds", 2, 1, 0, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xff, nullptr, nullptr, &_diffuse_cube_map);
	D3DXCreateCubeTextureFromFileEx(device, L"Data/CubeTexture/rnl_cross.dds", 0, 0, 0, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xff, nullptr, nullptr, &_specular_cube_map);
	D3DXCreateTextureFromFileEx(device, L"Data/Texture/oba.jpg", 0, 0, 0, 0, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xff, nullptr, nullptr, &_albedo_map);

	// ���W
	_position.current = D3DXVECTOR3(0.f,0.f,0.f);
	_position.previous = _position.current;
	_world.position = _position.current;
	_world.rotation = D3DXVECTOR3(0.f, 0.f, 0.f);
	_world.scale = D3DXVECTOR3(0.007f, 0.007f, 0.007f);

	// Aim
	_aim = new AimUnit(_application, _game_world);

	// �R�}���h�n���h��
	_command_handler = new CommandHandler();

	// �e
	_bullet = new BulletUnit(_application,_game_world);

	// �p�X
	_pass_point_list[0] = _game_world->GetCollisionGrid()->CellCenterPoint(1, 1);
	_pass_point_list[1] = _game_world->GetCollisionGrid()->CellCenterPoint(3, 1);
	_pass_point_list[2] = _game_world->GetCollisionGrid()->CellCenterPoint(3, 3);
	_pass_point_list[3] = _game_world->GetCollisionGrid()->CellCenterPoint(1, 3);
	_pass_frame = 0;

	// �ŏ��̌����Ă���x�N�g��
	_front_vector = _pass_point_list[1] - _pass_point_list[0];
	_lower_body_rotation = 0.f;
}

//=============================================================================
// �I��
void PlayerUnit::Finalize()
{
	SafeDelete(_bullet);
	SafeDelete(_aim);

	SafeRelease(_diffuse_cube_map);
	SafeRelease(_specular_cube_map);
	SafeRelease(_albedo_map);

	SafeDelete(_animation_system);
	_animation.UnLoadAnimationFile();
	for( auto it : _mesh_list )
	{
		SafeDelete(it);
	}

	SafeDelete(_shader);
	SafeDelete(_command_handler);
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
	_animation_system->AdvanceFrame(1);
	SettingShaderParameter();
	AimUpdate();
	_bullet->Update();
}
//=============================================================================
// �Փ˔���p�X�V
void PlayerUnit::CollisionUpdate()
{
	// Aim�̏Փ˔���p�X�V
	_aim->CollisionUpdate();
	_bullet->CollisionUpdate();

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
	CameraGamePlayer* camera = static_cast<CameraGamePlayer*>(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER));
	for( auto it : _mesh_list )
	{
		_animation_system->ComputeHumanPose(animation_matrix_list, ShaderPBLAnimation::kMatrixMax, _animation, camera->GetCameraRotation(), D3DXVECTOR3(0.f, 0.f, 0.f));
		_shader->SetAnimationMatrix(animation_matrix_list);
		S_GetCommandBuffer()->PushRenderState(RENDER_STATE_DEFAULT, GetID());
		S_GetCommandBuffer()->PushShader(_shader, GetID());
		S_GetCommandBuffer()->PushMesh(it, GetID());
		//UNREFERENCED_PARAMETER(it);
	}

	// Aim�̕`��
	_aim->Draw();
	// �e�̕`��
	_bullet->Draw();
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
	D3DXVECTOR4 ambient(0.97f, 0.8f, 0.75f, 1.f);
	D3DXVECTOR4 eye(camera->GetVectorEye(), 0.f);
	// �V�F�[�_�̐ݒ�
	_shader->SetWorldViewProjection(_matrix_world_view_projection);
	_shader->SetWorld(_world.matrix);
	_shader->SetLightDirection(light_direction);
	_shader->SetAlbedoTexture(_albedo_map);
	_shader->SetAmbientColor(ambient);
	_shader->SetDiffuseCubeMap(_diffuse_cube_map);
	_shader->SetSpecularCubeMap(_specular_cube_map);
	_shader->SetEyePosition(eye);
	_shader->SetFresnel(0.3f);
	_shader->SetMetalness(0.0f);
	_shader->SetRoughness(1.0f);
	_shader->SetWorld(_world.matrix);
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

	// �p�x�擾
	D3DXVECTOR3 normal_eye_look_at;
	D3DXVECTOR3 normal_front_vector;

	D3DXVec3Normalize(&normal_eye_look_at, &vector_eye_look_at);
	D3DXVec3Normalize(&normal_front_vector, &_front_vector);
	float dot = D3DXVec3Dot(&normal_eye_look_at, &normal_front_vector);

	if( dot <= 0 )
	{
		vector_eye_look_at *= -1;

		D3DXVECTOR3 eye_look_at_12_cross;
		D3DXVec3Cross(&eye_look_at_12_cross, &normal_eye_look_at, &normal_front_vector);
		if( eye_look_at_12_cross.y <= 0 )
		{
			_lower_body_rotation += D3DX_PI;
		}
		if( eye_look_at_12_cross.y > 0 )
		{
			_lower_body_rotation -= D3DX_PI;
		}
	}
}