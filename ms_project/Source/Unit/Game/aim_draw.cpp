//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �`��pAIM
// 
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "aim_draw.h"
#include "Shader/Shader/aim_shader.h"
#include "Resource/Mesh/Mesh/mesh_factory_sprite.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"
#include "Renderer/directx9.h"

//=============================================================================
// ������
void AimDrawUnit::Initialize()
{
	// �V�F�[�_�̍쐬
	_shader = new ShaderAim();

	// ���b�V���̍쐬
	MeshFactorySprite mesh_factory;
	_mesh = mesh_factory.Create(_application->GetRendererDevice());

	// �e�N�X�`��
	LPDIRECT3DDEVICE9 device = _application->GetRendererDevice()->GetDevice();
	D3DXCreateTextureFromFileEx(device, L"Data/Texture/aim.png", 0, 0, 0, 0, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xff, nullptr, nullptr, &_albedo_map);
	_shader->SetAlbedoTexture(_albedo_map);
}

//=============================================================================
// �I��
void AimDrawUnit::Finalize()
{
	SafeRelease(_albedo_map);
	SafeDelete(_mesh);
	SafeDelete(_shader);
}

//=============================================================================
// �X�V
void AimDrawUnit::Update()
{
	CalculatePosition();
}

//=============================================================================
// �`��
void AimDrawUnit::Draw()
{
	// �`�悷������������ށF�P�x�̕`��ɂP�x�����Ă΂Ȃ�����
	S_GetCommandBuffer()->PushRenderState(RENDER_STATE_AIM, GetID());
	S_GetCommandBuffer()->PushShader(_shader, GetID());
	S_GetCommandBuffer()->PushMesh(_mesh, GetID());
}

//=============================================================================
// �J�������玩���̈ʒu���Z�o
void AimDrawUnit::CalculatePosition()
{
	// �J�����擾
	CameraGamePlayer* camera = static_cast<CameraGamePlayer*>(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER));

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

	// �J�����̎��_�ƒ����_���玩���̍��W�����߂�
	D3DXVECTOR3 eye = camera->GetVectorEye();
	D3DXVECTOR3 look_at = camera->GetVectorLookAt();
	D3DXVec3Lerp(&_world.position, &eye, &look_at,0.5f);
	_world.scale = D3DXVECTOR3(1.f, 1.f, 1.f);

	D3DXMATRIX scaling_matrix, translation_matrix;

	D3DXMatrixScaling(&scaling_matrix, _world.scale.x, _world.scale.y, _world.scale.z);
	D3DXMatrixTranslation(&translation_matrix, _world.position.x, _world.position.y, _world.position.z);
	_world.matrix = inverse_view * scaling_matrix * translation_matrix;
	_matrix_world_view_projection = _world.matrix * view * projection;
	_shader->SetWorldViewProjection(_matrix_world_view_projection);

}