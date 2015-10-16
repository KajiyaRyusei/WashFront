//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �X�^�e�B�b�N���f��
// 
// Created by Ryusei Kajiya on 20151014
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "static_model_unit.h"

#include "System/application.h"

#include "Shader/Shader/lambert.h"

#include "Resource/Mesh/Mesh/mesh_factory_smo.h"

#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_main.h"

#include "DrawCommand/command_buffer.h"

//=============================================================================
// ������
void StaticModelUnit::Initialize()
{
	// �V�F�[�_�̍쐬
	_shader = new ShaderLambert();

	// ���b�V���̍쐬
	MeshFactorySMO mesh_factory;
	mesh_factory.Create(
		_application->GetRendererDevice(),
		"Data/StaticModel/oba_walk.smo",
		_mesh_list);
}

//=============================================================================
// �I��
void StaticModelUnit::Finalize()
{
	SafeDelete(_shader);

	for( auto it : _mesh_list )
	{
		SafeDelete(it);
	}
}

//=============================================================================
// �X�V
void StaticModelUnit::Update()
{
	D3DXMATRIX matrix_world, matrix_scaling;
	static float rotation = 0;
	D3DXMatrixRotationYawPitchRoll(&matrix_world, rotation, 0.f, 0.f);
	float scaling = 0.005f;
	D3DXMatrixScaling(&matrix_scaling, scaling, scaling, scaling);
	rotation += 0.01f;
	matrix_world *= matrix_scaling;

	CameraGameMain* camera = static_cast<CameraGameMain*>(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_MAIN));
	D3DXMATRIX matrix_projection = camera->GetMatrixProjection();
	D3DXMATRIX matrix_view = camera->GetMatrixView();

	D3DXMATRIX matrix_world_view_projection = matrix_world * matrix_view * matrix_projection;

	_shader->SetWorldViewProjection(matrix_world_view_projection);
	D3DXVECTOR4 light_direction(0.f, -0.5f, -1.f, 0.f);
	D3DXMATRIX matrix_world_inverse;
	D3DXMatrixInverse(&matrix_world_inverse, nullptr, &matrix_world);
	D3DXVec4Transform(&light_direction, &light_direction, &matrix_world_inverse);
	D3DXVec4Normalize(&light_direction, &light_direction);
	_shader->SetLightDirection(light_direction);
}

//=============================================================================
// �`��
void StaticModelUnit::Draw()
{
	// �`�悷������������ށF�P�x�̕`��ɂP�x�����Ă΂Ȃ�����
	for( auto it : _mesh_list )
	{
		S_GetCommandBuffer()->PushRenderState(RENDER_STATE_DEFAULT, GetID());
		S_GetCommandBuffer()->PushShader(_shader, GetID());
		S_GetCommandBuffer()->PushMesh(it, GetID());
	}
}