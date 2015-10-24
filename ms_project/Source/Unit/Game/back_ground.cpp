//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �w�i�p�V��
// 
// Created by Ryusei Kajiya on 20151022
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "back_ground.h"
#include "System/application.h"
#include "Shader/Shader/back_ground_shader.h"
#include "Shader/Shader/lambert.h"
#include "Resource/Mesh/Mesh/mesh_factory_cube.h"
#include "DrawCommand/command_buffer.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"
#include "Resource/resource_box.h"
#include "Renderer/directx9.h"

//=============================================================================
// ������
void BackGroundUnit::Initialize()
{
	// �V�F�[�_�̍쐬
	//_shader = new ShaderLambert();
	_shader = new ShaderBackGround();

	// ���b�V���̍쐬
	MeshFactoryCube cube_factory;
	_mesh = cube_factory.Create(_application->GetRendererDevice());

	// �e�N�X�`���̍쐬
	D3DXCreateCubeTextureFromFile(_application->GetRendererDevice()->GetDevice(), L"Data/CubeTexture/rnl_cross.dds", &_texture);
}

//=============================================================================
// �I��
void BackGroundUnit::Finalize()
{
	SafeDelete(_shader);
	SafeDelete(_mesh);
	SafeRelease(_texture);
}

//=============================================================================
// �X�V
void BackGroundUnit::Update()
{
	CameraGamePlayer* camera = static_cast<CameraGamePlayer*>(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER));
	D3DXMATRIX matrix_scaling;
	static const float kScaling = 500.f;
	D3DXMatrixScaling(&matrix_scaling, kScaling, kScaling, kScaling);
	D3DXMATRIX matrix_world_view_projection = matrix_scaling * camera->GetMatrixView() * camera->GetMatrixProjection();
	_shader->SetWorldViewProjection(matrix_world_view_projection);

	// cube_texture�Z�b�g
	_shader->SetAlbedoCubeTexture(_texture);
}

//=============================================================================
// �`��
void BackGroundUnit::Draw()
{
	// �`�悷������������ށF�P�x�̕`��ɂP�x�����Ă΂Ȃ�����
	S_GetCommandBuffer()->PushRenderState(RENDER_STATE_BACKGROUND,GetID());
	S_GetCommandBuffer()->PushShader(_shader, GetID());
	S_GetCommandBuffer()->PushMesh(_mesh, GetID());
}
