//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ビル
// 
// Created by Ryusei Kajiya on 20151201
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit/Game/building.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"
#include "Algorithm/often_use.h"
#include "Shader/Shader/toon_building_shader.h"
#include "World/collision_grid.h"

//リソース
#include "Resource/cube_texture_resource.h"
#include "Resource/texture_resource.h"

// mesh
#include "Resource/Mesh/mesh_buffer.h"
#include "Resource/Mesh/Mesh/mesh_factory_smo.h"
#include "Unit/Game/water_spray_pool.h"

// 衝突用
#include "Collision/collision_system.h"

//UI
#include "Unit/ui.h"

//*****************************************************************************
// 定数
namespace
{
	static const fx32 kCleanVelocity = 0.035f;
}

//=============================================================================
// 初期化
void BuildingUnit::Initialize(
	const D3DXVECTOR3& position,
	const D3DXVECTOR3& rotaiton,
	const D3DXVECTOR3& scale,
	std::string file_name)
{
	// シェーダの作成
	MeshFactorySMO mesh_factory;
	mesh_factory.Create(_application->GetRendererDevice(), file_name, _mesh_list);
	_shader_size = _mesh_list.size();
	_shader = new ShaderToonBuilding[_mesh_list.size()];

	LPDIRECT3DTEXTURE9 albedo_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_BILL_TEXTURE);
	LPDIRECT3DTEXTURE9 dirt_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_DIRTY_TEXTURE);
	LPDIRECT3DCUBETEXTURE9 diffuse_cube_map = _game_world->GetCubeTextureResource()->Get(CUBE_TEXTURE_RESOURE_GRID_ZERO_ZERO_DIFFUSE);
	LPDIRECT3DTEXTURE9 toon_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_TOON_TEXTURE);
	LPDIRECT3DTEXTURE9 normal_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_BILL_NORMAL_TEXTURE);

	for( u32 shader_index = 0; shader_index < _shader_size; ++shader_index )
	{
		_shader[shader_index].SetAlbedoTexture(albedo_map);
		_shader[shader_index].SetDirtyTexture(dirt_map);
		_shader[shader_index].SetDiffuseCubeMap(diffuse_cube_map);
		_shader[shader_index].SetToonTexture(toon_map);
		_shader[shader_index].SetNormalTexture(normal_map);
	}

	// 座標の設定
	_position.current = position;
	_position.previous = _position.current;
	_world.position = _position.current;
	_world.scale = scale;
	_world.rotation = rotaiton;

	D3DXVECTOR3 mesh_point_array[3000];
	D3DXVECTOR3 mesh_normal_array[3000];
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
	D3DXVECTOR3 volume_box_size(_world.scale*6.f);
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
	Camera* camera = _application->GetCameraManager()->GetCurrentCamera();
	D3DXVECTOR3 culling_point(_box->position);
	culling_point.y += _box->size.y + 10.f;
	if( camera->GetFrustumCulling().ClipCheckBox(culling_point, _box->size*3.f) )
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

	_box->DebugDraw();
}

//=============================================================================
// シェーダパラメーターの設定
void BuildingUnit::SettingShaderParameter()
{
	// カメラ取得
	Camera* camera = _application->GetCameraManager()->GetCurrentCamera();

	// 行列の作成
	_world.position = _position.current;
	algo::CreateWorld(_world.matrix, _world.position, _world.rotation, _world.scale);
	algo::CreateWVP(_matrix_world_view_projection, _world.matrix, camera);

	// ライトの方向作成
	D3DXVECTOR4 light_direction(0.2f, -0.8f, 0.5f, 0.f);
	static D3DXVECTOR4 basic_ambient(0.8f, 0.5f, 0.2f, 1.f);
	static D3DXVECTOR4 dirt_ambient(0.8f*0.35f, 0.5f*0.2f, 0.2f*0.2f, 1.f);
	static D3DXVECTOR4 ambient(1.0f, 0.3f, 0.2f, 1.f);
	static D3DXVECTOR3 ambient_bezier(0.0f, 0.0f, 0.0f);
	static fx32 ambient_coefficient = 0.f;
	ambient_coefficient += 0.002f;
	static fx32 ambient_coefficient_floating = 0.f;
	static fx32 ambient_coefficient_floating_2 = 0.f;
	ambient_coefficient_floating_2 = modf(ambient_coefficient, &ambient_coefficient_floating);
	algo::BezierCurve2D(ambient_bezier, (D3DXVECTOR3)basic_ambient, (D3DXVECTOR3)basic_ambient, (D3DXVECTOR3)dirt_ambient, ambient_coefficient_floating_2);
	ambient = D3DXVECTOR4(ambient_bezier.x, ambient_bezier.y, ambient_bezier.z,1.f);

	D3DXVECTOR4 eye(camera->GetVectorEye(), 0.f);
	static D3DXVECTOR2 texcoord_move(0.f,0.f);
	texcoord_move.y -= 0.0001f;

	for( u32 shader_index = 0; shader_index < _shader_size; ++shader_index )
	{
		_shader[shader_index].SetWorldViewProjection(_matrix_world_view_projection);
		_shader[shader_index].SetWorld(_world.matrix);
		_shader[shader_index].SetView(camera->GetMatrixView());
		_shader[shader_index].SetLightDirection(light_direction);
		_shader[shader_index].SetAmbientColor(ambient);
		_shader[shader_index].SetEyePosition(eye);
		_shader[shader_index].SetTexcoordMove(texcoord_move);
	}
}

//=============================================================================
// 座標設定
void BuildingUnit::CollisionMeshPoint(u32 point_index)
{
	_clean_index_list.push_back(point_index);

	D3DXVECTOR3 front_vector(sinf(_volume_mesh_point->attitudes[point_index]) *1.f, 0.f, cosf(_volume_mesh_point->attitudes[point_index]) *1.f);
	_game_world->GetWaterSprayPool()->Create(_volume_mesh_point->points[point_index] + front_vector, _volume_mesh_point->attitudes[point_index]);
}

//=============================================================================
// 衝突している点をお掃除
void BuildingUnit::CleanUp()
{
	for( auto it = _mesh_list.begin(); it != _mesh_list.end(); ++it )
	{
		VERTEX_SMO* vertex = nullptr;
		(*it)->GetVertexBuffer(0)->Lock(0, 0, (void**)&vertex, 0);

		std::list<u32>::iterator index_it;
		for( index_it = _clean_index_list.begin(); index_it != _clean_index_list.end(); )
		{
			if( vertex[*index_it].cleanliness < 1.5f )
			{
				vertex[*index_it].cleanliness += kCleanVelocity;

			}
			else
			{
				index_it = _clean_index_list.erase(index_it);
				continue;
			}
			++index_it;
		}

		(*it)->GetVertexBuffer(0)->Unlock();
	}

}

//=============================================================================
// 汚れのセット
void BuildingUnit::SettingDirty(std::vector<data::Dirt>& dirt_list)
{
	for( auto it = _mesh_list.begin(); it != _mesh_list.end(); ++it )
	{
		u32 vertex_count = (*it)->GetVertexCount(0);
		VERTEX_SMO* vertex = nullptr;
		(*it)->GetVertexBuffer(0)->Lock(0, 0, (void**)&vertex, 0);

		for( u32 vertex_id = 0; vertex_id < vertex_count; ++vertex_id )
		{
			for( auto it : dirt_list )
			{
				if( collision::Sphrere2Point(
					it.point,
					_volume_mesh_point->points[vertex_id],
					it.radius) )
				{
					vertex[vertex_id].cleanliness = 0.f;
				}
			}
		}
		(*it)->GetVertexBuffer(0)->Unlock();
	}
}