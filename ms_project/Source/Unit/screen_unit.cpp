//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �e�X�g�X�N���[���p���j�b�g
// 
// Created by Ryusei Kajiya on 20151012
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "screen_unit.h"

#include "System/application.h"

#include "Shader/Shader/screen_shader.h"

#include "Resource/Mesh/Mesh/mesh_factory_sprite.h"

#include "DrawCommand/command_buffer.h"

#include "Windows/window.h"

//=============================================================================
// ������
void ScreenUnit::Initialize()
{
	// �V�F�[�_�̍쐬
	_shader = new ShaderScreen();

	// ���_�o�b�t�@�̍쐬
	MeshFactorySprite sprite_factory;
	_mesh = sprite_factory.Create(_application->GetRendererDevice());
}

//=============================================================================
// �I��
void ScreenUnit::Finalize()
{
	SafeDelete(_shader);
	SafeDelete(_mesh);
}

//=============================================================================
// �X�V
void ScreenUnit::Update()
{
	D3DXMATRIX matrix_screen, matrix_rotation, matrix_scale, matrix_translation;
	D3DXMatrixIdentity(&matrix_screen);

	static const fx32 scaling(100.f);
	static fx32 rotation(0.f);
	rotation += 0.01f;
	static D3DXVECTOR3 position(100.f, 100.f, 0.f);

	D3DXMatrixScaling(&matrix_scale, scaling, scaling, scaling);
	D3DXMatrixRotationZ(&matrix_rotation, rotation);
	D3DXMatrixTranslation(&matrix_translation, position.x, position.y, position.z);

	matrix_screen = matrix_rotation * matrix_scale * matrix_translation;

	_shader->SetScreenMatrix(matrix_screen);

	_shader->SetScreenSize(D3DXVECTOR2(
		static_cast<fx32>(_application->GetWindow()->GetSizeWindowWidth()),
		static_cast<fx32>(_application->GetWindow()->GetSizeWindowHeight())));
}

//=============================================================================
// �`��
void ScreenUnit::Draw()
{

	// �`�悷������������ށF�P�x�̕`��ɂP�x�����Ă΂Ȃ�����
	S_GetCommandBuffer()->PushRenderState(RENDER_STATE_2D,GetID());
	S_GetCommandBuffer()->PushShader(_shader, GetID());
	S_GetCommandBuffer()->PushMesh(_mesh, GetID());
}