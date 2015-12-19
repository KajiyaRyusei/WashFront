//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �w�i�p�r��
// 
// Created by Ryusei Kajiya on 201511214
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit/Game/static_building.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"
#include "Algorithm/often_use.h"
#include "Shader/Shader/static_toon_building_shader.h"

//���\�[�X
#include "Resource/cube_texture_resource.h"
#include "Resource/texture_resource.h"


// mesh
#include "Resource/Mesh/mesh_buffer.h"

//=============================================================================
// ������
void StaticBuildingUnit::Initialize(
	const D3DXVECTOR3& position,
	const D3DXVECTOR3& rotaiton,
	const D3DXVECTOR3& scale,
	STATIC_MESH_RESOURE_ID id)
{
	// �V�F�[�_�̍쐬
	_mesh_list = _game_world->GetStaticMeshResource()->Get(id);
	_shader_size = _mesh_list.size();
	_shader = new ShaderStaticToonBuilding[_shader_size];

	LPDIRECT3DTEXTURE9 albedo_map;

	static u32 albedo_texture_id = 0;

	switch( albedo_texture_id % 5 )
	{
	case 0:
		albedo_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_BILL_TEXTURE);
		break;
	case 1:
		albedo_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_BILL_TEXTURE_001);
		break;
	case 2:
		albedo_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_BILL_TEXTURE_002);
		break;
	case 3:
		albedo_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_BILL_TEXTURE_003);
		break;
	case 4:
		albedo_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_BILL_TEXTURE_004);
		break;
	default:
		break;
	}
	++albedo_texture_id;

	LPDIRECT3DCUBETEXTURE9 diffuse_cube_map = _game_world->GetCubeTextureResource()->Get(CUBE_TEXTURE_RESOURE_GRID_ZERO_ZERO_DIFFUSE);
	LPDIRECT3DTEXTURE9 toon_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_TOON_TEXTURE);
	LPDIRECT3DTEXTURE9 normal_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_BILL_NORMAL_TEXTURE);

	for( u32 shader_index = 0; shader_index < _shader_size; ++shader_index )
	{
		_shader[shader_index].SetAlbedoTexture(albedo_map);
		_shader[shader_index].SetDiffuseCubeMap(diffuse_cube_map);
		_shader[shader_index].SetToonTexture(toon_map);
		_shader[shader_index].SetNormalTexture(normal_map);
	}

	// ���W�̐ݒ�
	_position.current = position;
	_position.previous = _position.current;
	_world.position = _position.current;
	_world.scale = scale;
	_world.rotation = rotaiton;
}

//=============================================================================
// �I��
void StaticBuildingUnit::Finalize()
{
	SafeDeleteArray(_shader);
}

//=============================================================================
// �X�V
void StaticBuildingUnit::Update()
{

}

//=============================================================================
// �`��
void StaticBuildingUnit::Draw()
{
	Camera* camera = _application->GetCameraManager()->GetCurrentCamera();
	D3DXVECTOR3 culling_point(_position.current);
	culling_point.y += 50.f;
	if( camera->GetFrustumCulling().ClipCheck(culling_point, 20.f) )
	{
		SettingShaderParameter();

		u32 mesh_id = 0;
		for( auto it = _mesh_list.begin(); it != _mesh_list.end(); ++it, ++mesh_id )
		{
			UNREFERENCED_PARAMETER(it);
			S_GetCommandBuffer()->PushRenderState(RENDER_STATE_DEFAULT, GetID());
			S_GetCommandBuffer()->PushShader(&_shader[mesh_id], GetID());
			S_GetCommandBuffer()->PushMesh((*it), GetID());
		}
	}
}

//=============================================================================
// �V�F�[�_�p�����[�^�[�̐ݒ�
void StaticBuildingUnit::SettingShaderParameter()
{
	// �J�����擾
	Camera* camera = _application->GetCameraManager()->GetCurrentCamera();

	// �s��̍쐬
	_world.position = _position.current;
	algo::CreateWorld(_world.matrix, _world.position, _world.rotation, _world.scale);
	algo::CreateWVP(_matrix_world_view_projection, _world.matrix, camera);

	// ���C�g�̕����쐬
	D3DXVECTOR4 light_direction(0.2f, -0.8f, 0.5f, 0.f);

	for( u32 shader_index = 0; shader_index < _shader_size; ++shader_index )
	{
		_shader[shader_index].SetWorldViewProjection(_matrix_world_view_projection);
		_shader[shader_index].SetWorld(_world.matrix);
		_shader[shader_index].SetView(camera->GetMatrixView());
		_shader[shader_index].SetLightDirection(light_direction);
	}
}