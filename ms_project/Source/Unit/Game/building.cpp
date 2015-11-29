//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ビル
// 
// Created by Ryusei Kajiya on 20151102
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit/Game/building.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"
#include "Algorithm/often_use.h"
#include "Shader/Shader/PBL_static_shader.h"
#include "World/collision_grid.h"

//リソース
#include "Resource/cube_texture_resource.h"
#include "Resource/texture_resource.h"

// mesh
#include "Resource/Mesh/mesh_buffer.h"
#include "Resource/Mesh/Mesh/mesh_factory_smo.h"
#include "Unit/Game/water_spray_pool.h"

//*****************************************************************************
// 定数
namespace
{
	static const fx32 kCleanVelocity = 0.02f;
}

//=============================================================================
// 初期化
void BuildingUnit::Initialize(
	const D3DXVECTOR3& position,
	const D3DXVECTOR3& rotaiton,
	const D3DXVECTOR3& scale)
{
	// シェーダの作成
	MeshFactorySMO mesh_factory;
	mesh_factory.Create(_application->GetRendererDevice(), "Data/StaticModel/biru_1.smo", _mesh_list);
	_shader_size = _mesh_list.size();
	_shader = new ShaderPBLStatic[_mesh_list.size()];

	LPDIRECT3DTEXTURE9 albedo_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_BILL_TEXTURE);
	LPDIRECT3DTEXTURE9 metalness_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_BILL_METALNESS_TEXTURE);
	LPDIRECT3DTEXTURE9 dirt_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_DIRTY_TEXTURE);
	LPDIRECT3DCUBETEXTURE9 diffuse_cube_map = _game_world->GetCubeTextureResource()->Get(CUBE_TEXTURE_RESOURE_GRID_ZERO_ZERO_DIFFUSE);
	LPDIRECT3DCUBETEXTURE9 specular_cube_map = _game_world->GetCubeTextureResource()->Get(CUBE_TEXTURE_RESOURE_GRID_ZERO_ZERO_SPECULAR);

	for( u32 shader_index = 0; shader_index < _shader_size; ++shader_index )
	{
		_shader[shader_index].SetAlbedoTexture(albedo_map);
		_shader[shader_index].SetDirtyTexture(dirt_map);
		_shader[shader_index].SetMetalnessMap(metalness_map);
		_shader[shader_index].SetDiffuseCubeMap(diffuse_cube_map);
		_shader[shader_index].SetSpecularCubeMap(specular_cube_map);
	}

	// 座標の設定
	_position.current = position;
	_position.previous = _position.current;
	_world.position = _position.current;
	_world.scale = scale;
	_world.rotation = rotaiton;

	D3DXVECTOR3 mesh_point_array[1000];
	D3DXVECTOR3 mesh_normal_array[1000];
	u32 vertex_count = 0;
	for( auto it = _mesh_list.begin(); it != _mesh_list.end(); ++it)
	{
		vertex_count = (*it)->GetVertexCount(0);
		VERTEX_SMO* vertex = nullptr;
		(*it)->GetVertexBuffer(0)->Lock(0, 0, (void**)&vertex, 0);

		for( u32 vertex_id = 0; vertex_id < vertex_count; ++vertex_id )
		{
			mesh_point_array[vertex_id] = vertex[vertex_id].position;
			mesh_normal_array[vertex_id] = vertex[vertex_id].normal;
		}

		(*it)->GetVertexBuffer(0)->Unlock();
	}

	// ボリュームの作成
	CreateVolumeMeshPoint(_world.position, _world.scale, _world.rotation, vertex_count, mesh_point_array, mesh_normal_array);
	D3DXVECTOR3 volume_box_size(_world.scale*100.f);
	volume_box_size.y *= 10.f;
	CreateVolumeBox(_world.position, volume_box_size, _world.rotation);

	// 空間に突っ込む
	_game_world->GetCollisionGrid()->AddUnit(this, _position);
}

//=============================================================================
// 終了
void BuildingUnit::Finalize()
{
	SafeDeleteArray(_shader);
	for( auto it = _mesh_list.begin(); it != _mesh_list.end(); ++it)
	{
		SafeDelete(*it);
	}
}

//=============================================================================
// 更新
void BuildingUnit::Update()
{
	// シェーダパラメーターの更新
	SettingShaderParameter();
	CleanUp();
}
//=============================================================================
// 衝突判定用更新
void BuildingUnit::CollisionUpdate()
{
	s32 cell_x = 0;
	s32 cell_z = 0;
	_game_world->GetCollisionGrid()->SelfCoordinatesCell(&cell_x, &cell_z, _position);
	_game_world->GetCollisionGrid()->HandleCell(cell_x, cell_z);
}

//=============================================================================
// 描画
void BuildingUnit::Draw()
{
	u32 mesh_id = 0;
	for( auto it = _mesh_list.begin(); it != _mesh_list.end(); ++it, ++mesh_id )
	{
		S_GetCommandBuffer()->PushRenderState(RENDER_STATE_DEFAULT, GetID());
		S_GetCommandBuffer()->PushShader(&_shader[mesh_id], GetID());
		S_GetCommandBuffer()->PushMesh((*it), GetID());
	}

	_box->DebugDraw();
}

//=============================================================================
// シェーダパラメーターの設定
void BuildingUnit::SettingShaderParameter()
{
	// カメラ取得
	CameraGamePlayer* camera = static_cast<CameraGamePlayer*>(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER));
	
	// 行列の作成
	_world.position = _position.current;
	algo::CreateWorld(_world.matrix, _world.position, _world.rotation, _world.scale);
	algo::CreateWVP(_matrix_world_view_projection, _world.matrix, camera);
	// ライトの方向作成
	D3DXVECTOR4 light_direction(0.2f, -0.8f, 0.5f, 0.f);
	D3DXVECTOR4 ambient(1.0f, 1.0f, 1.0f, 1.f);
	D3DXVECTOR4 eye(camera->GetVectorEye(), 0.f);
	for( u32 shader_index = 0; shader_index < _shader_size; ++shader_index )
	{
		_shader[shader_index].SetWorldViewProjection(_matrix_world_view_projection);
		_shader[shader_index].SetWorld(_world.matrix);
		_shader[shader_index].SetLightDirection(light_direction);
		_shader[shader_index].SetAmbientColor(ambient);
		_shader[shader_index].SetEyePosition(eye);
		_shader[shader_index].SetFresnel(1.0f);
		_shader[shader_index].SetMetalness(1.0f);
		_shader[shader_index].SetRoughness(1.0f);
		_shader[shader_index].SetWorld(_world.matrix);
	}
}

//=============================================================================
// 座標設定
void BuildingUnit::CollisionMeshPoint(u32 point_index)
{
	_clean_index_list.push_back(point_index);
	_game_world->GetWaterSprayPool()->Create(_volume_mesh_point->points[point_index], _volume_mesh_point->attitudes[point_index]);
}

//=============================================================================
// 衝突している点をお掃除
void BuildingUnit::CleanUp()
{

	for( auto it = _mesh_list.begin(); it != _mesh_list.end(); ++it )
	{
		VERTEX_SMO* vertex = nullptr;
		(*it)->GetVertexBuffer(0)->Lock(0, 0, (void**)&vertex, 0);

		for( auto index : _clean_index_list)
		{
			if( vertex[index].cleanliness > 0.f)
			{
				vertex[index].cleanliness -= kCleanVelocity;
			}
			else
			{
				//_clean_index_list.erase(std::remove_if(_clean_index_list.begin(), _clean_index_list.end(),index), _clean_index_list.end());
			}
		}

		(*it)->GetVertexBuffer(0)->Unlock();
	}
}