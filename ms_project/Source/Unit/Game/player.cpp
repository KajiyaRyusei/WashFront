//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �v���C���[
// 
// Created by Ryusei Kajiya on 20151022
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "player.h"
#include "System/application.h"
#include "Shader/Shader/PBL_animation_shader.h"
#include "Resource/Mesh/Mesh/mesh_factory_amo.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"
#include "DrawCommand/command_buffer.h"
#include "Animation/animation_system.h"
#include "Input/input_manager.h"
#include "Algorithm/often_use.h"
#include "DevelopTool/develop_tool_manager.h"

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
}

//=============================================================================
// �I��
void PlayerUnit::Finalize()
{
	SafeDelete(_animation_system);
	_animation.UnLoadAnimationFile();
	for( auto it : _mesh_list )
	{
		SafeDelete(it);
	}
	SafeDelete(_shader);
}

//=============================================================================
// �X�V
void PlayerUnit::Update()
{
	static float position_z = 0.f;
	//position_z += 0.1f;
	// �s��̍쐬
	D3DXMATRIX matrix_world;
	algo::CreateWorld(matrix_world, D3DXVECTOR3(0.f, 0.f, position_z), D3DXVECTOR3(0.f, 0.f, 0.f), D3DXVECTOR3(0.007f, 0.007f, 0.007f));
	CameraGamePlayer* camera = static_cast<CameraGamePlayer*>(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER));
	D3DXMATRIX matrix_world_view_projection;
	algo::CreateWVP(matrix_world_view_projection,matrix_world,camera);

	// �v���C���[�̃|�W�V������������
	camera->SetPlayerPosition(D3DXVECTOR3(0.f, 0.f, position_z));

	// ���C�g�̕����쐬
	D3DXVECTOR4 light_direction;
	algo::CreateLocalDirection(light_direction, D3DXVECTOR4(0.f, -0.5f, -1.f, 0.f), matrix_world);

	// �V�F�[�_�̐ݒ�
	_shader->SetWorldViewProjection(matrix_world_view_projection);
	_shader->SetLightDirection(light_direction);

	// �t���[���̍X�V
	_animation_system->AdvanceFrame(1);
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
		_animation_system->ComputeHumanPose(animation_matrix_list, ShaderPBLAnimation::kMatrixMax, _animation, camera->GetCameraRotation());
		_shader->SetAnimationMatrix(animation_matrix_list);
		S_GetCommandBuffer()->PushRenderState(RENDER_STATE_DEFAULT, GetID());
		S_GetCommandBuffer()->PushShader(_shader, GetID());
		S_GetCommandBuffer()->PushMesh(it, GetID());
	}
}

//=============================================================================
// �V�F�[�_�p�����[�^�[�̐ݒ�
void PlayerUnit::SettingShaderParameter()
{

}