//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �w�i�p�V��
// 
// Created by Ryusei Kajiya on 20151102
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "back_ground.h"
#include "Shader/Shader/back_ground_shader.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"

//���\�[�X
#include "Resource/cube_texture_resource.h"
#include "Resource/mesh_resource.h"

//=============================================================================
// ������
void BackGroundUnit::Initialize()
{
	// �V�F�[�_�̍쐬
	_shader = new ShaderBackGround();

	// �L���[�u�}�b�v�Z�b�g
	LPDIRECT3DCUBETEXTURE9 texture = _game_world->GetCubeTextureResource()->Get(CUBE_TEXTURE_RESOURE_GRID_ZERO_ONE_SPECULAR);
	_shader->SetAlbedoCubeTexture(texture);
}

//=============================================================================
// �I��
void BackGroundUnit::Finalize()
{
	SafeDelete(_shader);
}

//=============================================================================
// �X�V
void BackGroundUnit::Update()
{
	
}

//=============================================================================
// �`��
void BackGroundUnit::Draw()
{
	// �J�����擾
	Camera* camera = _application->GetCameraManager()->GetCurrentCamera();
	D3DXMATRIX matrix_scaling;
	static const float kScaling = 500.f;
	D3DXMatrixScaling(&matrix_scaling, kScaling, kScaling, kScaling);
	D3DXMATRIX matrix_world_view_projection = matrix_scaling * camera->GetMatrixView() * camera->GetMatrixProjection();
	_shader->SetWorldViewProjection(matrix_world_view_projection);

	// �`�悷������������ށF�P�x�̕`��ɂP�x�����Ă΂Ȃ�����
	S_GetCommandBuffer()->PushRenderState(RENDER_STATE_BACKGROUND,GetID());
	S_GetCommandBuffer()->PushShader(_shader, GetID());
	S_GetCommandBuffer()->PushMesh(_game_world->GetMeshResource()->Get(MESH_RESOURE_BOX), GetID());
}
