//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �r��
// 
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit/Game/building.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"
#include "Algorithm/often_use.h"
#include "Renderer/directx9.h"
#include "Shader/Shader/PBL_static_shader.h"
#include "Resource/Mesh/Mesh/mesh_factory_cube.h"
#include "World/collision_grid.h"

//=============================================================================
// ������
void BuildingUnit::Initialize()
{
	// �V�F�[�_�̍쐬
	_shader = new ShaderPBLStatic();

	// ���b�V���̍쐬
	MeshFactoryCube mesh_factory;
	_mesh = mesh_factory.Create(_application->GetRendererDevice());
	// �e�N�X�`��
	LPDIRECT3DDEVICE9 device = _application->GetRendererDevice()->GetDevice();
	D3DXCreateCubeTextureFromFileEx(device, L"Data/CubeTexture/rnl_cross.dds", 2, 1, 0, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xff, nullptr, nullptr, &_diffuse_cube_map);
	D3DXCreateCubeTextureFromFileEx(device, L"Data/CubeTexture/rnl_cross.dds", 0, 0, 0, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xff, nullptr, nullptr, &_specular_cube_map);

	ASSERT(S_OK == D3DXCreateTextureFromFileEx(device, L"Data/Texture/Orange_glazed_pxr128_bmp.jpg", 0, 0, 0, 0, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xff, nullptr, nullptr, &_albedo_map),"�e�N�X�`���ǂݍ��ݎ��s");
	ASSERT(S_OK == D3DXCreateTextureFromFileEx(device, L"Data/Texture/Orange_glazed_pxr128_normal.jpg", 0, 0, 0, 0, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xff, nullptr, nullptr, &_normal_map), "�e�N�X�`���ǂݍ��ݎ��s");

	// ���W�̐ݒ�
	_position.current = _game_world->GetCollisionGrid()->CellCenterPoint(2, 2);
	_position.previous = _position.current;
	_world.position = _position.current;
	_world.scale = D3DXVECTOR3(12.f, 55.f, 12.f);
	_world.rotation = D3DXVECTOR3(0.f, 0.f, 0.f);

	// �{�����[���̍쐬
	CreateVolumeBox(_world.position, _world.scale, _world.rotation);

	// ��Ԃɓ˂�����
	_game_world->GetCollisionGrid()->AddUnit(this, _position);
}

//=============================================================================
// �I��
void BuildingUnit::Finalize()
{
	SafeRelease(_diffuse_cube_map);
	SafeRelease(_specular_cube_map);
	SafeRelease(_albedo_map);
	SafeRelease(_normal_map);
	SafeDelete(_mesh);
	SafeDelete(_shader);
}

//=============================================================================
// �X�V
void BuildingUnit::Update()
{
	// �V�F�[�_�p�����[�^�[�̍X�V
	SettingShaderParameter();

	//_game_world->GetCollisionGrid()->MoveUnit(this, _position);
}
//=============================================================================
// �Փ˔���p�X�V
void BuildingUnit::CollisionUpdate()
{

}

//=============================================================================
// �`��
void BuildingUnit::Draw()
{
	// �`�悷������������ށF�P�x�̕`��ɂP�x�����Ă΂Ȃ�����
	S_GetCommandBuffer()->PushRenderState(RENDER_STATE_DEFAULT, GetID());
	S_GetCommandBuffer()->PushShader(_shader, GetID());
	S_GetCommandBuffer()->PushMesh(_mesh, GetID());
}

//=============================================================================
// �V�F�[�_�p�����[�^�[�̐ݒ�
void BuildingUnit::SettingShaderParameter()
{
	// �J�����擾
	CameraGamePlayer* camera = static_cast<CameraGamePlayer*>(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER));
	// �s��̍쐬
	_world.position = _position.current;
	algo::CreateWorld(_world.matrix, _world.position, _world.rotation, _world.scale);
	algo::CreateWVP(_matrix_world_view_projection, _world.matrix, camera);
	// ���C�g�̕����쐬
	D3DXVECTOR4 light_direction(0.2f, -0.8f, 0.5f, 0.f);
	D3DXVECTOR4 ambient(0.8f, 0.8f, 0.8f, 1.f);
	D3DXVECTOR4 eye(camera->GetVectorEye(), 0.f);
	// �V�F�[�_�̐ݒ�
	_shader->SetWorldViewProjection(_matrix_world_view_projection);
	_shader->SetWorld(_world.matrix);
	_shader->SetLightDirection(light_direction);
	_shader->SetAlbedoTexture(_albedo_map);
	_shader->SetNormalTexture(_normal_map);
	_shader->SetAmbientColor(ambient);
	_shader->SetDiffuseCubeMap(_diffuse_cube_map);
	_shader->SetSpecularCubeMap(_specular_cube_map);
	_shader->SetEyePosition(eye);
	_shader->SetFresnel(0.5f);
	_shader->SetMetalness(0.1f);
	_shader->SetRoughness(0.8f);
	_shader->SetWorld(_world.matrix);
}

//=============================================================================
// ���W�ݒ�
void BuildingUnit::SetPosition(const D3DXVECTOR3& position)
{
	_position.current = position;
	_box->position = position;
	_box->Calculation8Point();
	_game_world->GetCollisionGrid()->MoveUnit(this, _position);
}