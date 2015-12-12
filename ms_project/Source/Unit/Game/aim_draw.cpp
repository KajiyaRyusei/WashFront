//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �`��pAIM
// 
// Created by Ryusei Kajiya on 20151102
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "aim_draw.h"
#include "Shader/Shader/aim_shader.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"
#include "Renderer/directx9.h"

//���\�[�X
#include "Resource/texture_resource.h"
#include "Resource/mesh_resource.h"

//=============================================================================
// ������
void AimDrawUnit::Initialize()
{
	// �V�F�[�_�̍쐬
	_shader = new ShaderAim();
	LPDIRECT3DTEXTURE9 albedo_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_AIM_TEXTURE);
	_shader->SetAlbedoTexture(albedo_map);

}

//=============================================================================
// �I��
void AimDrawUnit::Finalize()
{
	SafeDelete(_shader);
}

//=============================================================================
// �X�V
void AimDrawUnit::Update()
{
	
}

//=============================================================================
// �`��
void AimDrawUnit::Draw()
{
	CalculatePosition();
	// �`�悷������������ށF�P�x�̕`��ɂP�x�����Ă΂Ȃ�����
	S_GetCommandBuffer()->PushRenderState(RENDER_STATE_AIM, GetID());
	S_GetCommandBuffer()->PushShader(_shader, GetID());
	S_GetCommandBuffer()->PushMesh(_game_world->GetMeshResource()->Get(MESH_RESOURE_SPRITE), GetID());
}

//=============================================================================
// �J�������玩���̈ʒu���Z�o
void AimDrawUnit::CalculatePosition()
{
	// �J�����擾
	Camera* camera = _application->GetCameraManager()->GetCurrentCamera();

	// ��]��ł�����
	D3DXMATRIX view = camera->GetMatrixView();
	D3DXMATRIX projection = camera->GetMatrixProjection();
	D3DXMATRIX inverse_view;
	D3DXMatrixInverse(&inverse_view, nullptr, &view);
	D3DXMATRIX test_matrix = inverse_view * view;

	// ���݂��폜
	inverse_view._41 = 0.f;
	inverse_view._42 = 0.f;
	inverse_view._43 = 0.f;

	_world.scale = D3DXVECTOR3(3.f, 3.f,3.f);

	D3DXMATRIX scaling_matrix, translation_matrix;

	D3DXMatrixScaling(&scaling_matrix, _world.scale.x, _world.scale.y, _world.scale.z);
	D3DXMatrixTranslation(&translation_matrix, _world.position.x, _world.position.y, _world.position.z);
	_world.matrix = inverse_view * scaling_matrix * translation_matrix;
	_matrix_world_view_projection = _world.matrix * view * projection;
	_shader->SetWorldViewProjection(_matrix_world_view_projection);

	static D3DXVECTOR4 s_ambient_color(0.f,1.f,0.f,1.f);

	if( _is_hit )
	{
		s_ambient_color = D3DXVECTOR4(0.f, 1.f, 0.f, 1.f);
	}
	else
	{
		s_ambient_color = D3DXVECTOR4(1.f, 1.f, 1.f, 1.f);
	}

	_shader->SetAmbientColor(s_ambient_color);
}