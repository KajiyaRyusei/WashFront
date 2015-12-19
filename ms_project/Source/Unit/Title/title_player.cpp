//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// タイトルプレイヤー
// 
// Created by Ryusei Kajiya on 20151212
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit/Title/title_player.h"
#include "Shader/Shader/toon_player_shader.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_title.h"
#include "Animation/animation_system.h"
#include "Algorithm/often_use.h"
#include "DevelopTool/develop_tool_manager.h"
#include "World/collision_grid.h"
#include "Unit/Game/water_back.h"
#include "Unit/Title/title_weapon.h"

//リソース
#include "Resource/cube_texture_resource.h"
#include "Resource/texture_resource.h"
#include "Resource/animation_mesh_resource.h"
#include "Resource/Mesh/mesh_buffer.h"
#include "Resource/Mesh/Mesh/mesh_factory_amo.h"
#include "Resource/animation_resource.h"

//=============================================================================
// 初期化
void TitlePlayerUnit::Initialize()
{
	// メッシュの取得
	auto mesh_list = _game_world->GetAnimationMeshResource()->Get(ANIMATION_MESH_RESOURE_GRANDPA);
	// アニメーションの取得
	_statnce_animation = _game_world->GetAnimationResource()->Get(ANIMATION_RESOURE_STANCE);

	// アニメーションシステムの作成
	_statnce_animation_system = new AnimationSystem();

	LPDIRECT3DTEXTURE9 albedo_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_PLAYER_TEXTURE);
	LPDIRECT3DTEXTURE9 albedo_map2 = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_PLAYER_BAG_TEXTURE);
	LPDIRECT3DTEXTURE9 albedo_map3 = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_PLAYER_FACE);
	LPDIRECT3DCUBETEXTURE9 diffuse_cube_map = _game_world->GetCubeTextureResource()->Get(CUBE_TEXTURE_RESOURE_GRID_ZERO_ONE_DIFFUSE);
	LPDIRECT3DCUBETEXTURE9 diffuse_cube_map2 = _game_world->GetCubeTextureResource()->Get(CUBE_TEXTURE_RESOURE_GRID_ZERO_ZERO_DIFFUSE);
	LPDIRECT3DCUBETEXTURE9 specular_cube_map = _game_world->GetCubeTextureResource()->Get(CUBE_TEXTURE_RESOURE_GRID_ZERO_ONE_SPECULAR);
	LPDIRECT3DCUBETEXTURE9 specular_cube_map2 = _game_world->GetCubeTextureResource()->Get(CUBE_TEXTURE_RESOURE_GRID_ZERO_ZERO_SPECULAR);
	LPDIRECT3DTEXTURE9 toon_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_TOON_TEXTURE);

	// シェーダの作成
	_shader_size = mesh_list.size();
	_shader = new ShaderToonPlayer[mesh_list.size()];

	for( u32 shader_index = 0; shader_index < _shader_size; ++shader_index )
	{
		_shader[shader_index].SetAlbedoTexture(albedo_map);
		_shader[shader_index].SetToonTexture(toon_map);
		_shader[shader_index].SetDiffuseCubeMap(diffuse_cube_map);
		_shader[shader_index].SetSpecularCubeMap(specular_cube_map);
	}

	_shader[0].SetAlbedoTexture(albedo_map3);
	_shader[2].SetAlbedoTexture(albedo_map3);


	_shader[3].SetDiffuseCubeMap(diffuse_cube_map2);
	_shader[3].SetSpecularCubeMap(specular_cube_map2);
	_shader[3].SetAlbedoTexture(albedo_map2);

	// 座標
	_position.current = D3DXVECTOR3(100.3f, 98.0f, 102.2f);
	_position.previous = _position.current;
	_world.position = _position.current;
	_world.rotation = D3DXVECTOR3(0.f, D3DX_PI, 0.f);
	_world.scale = D3DXVECTOR3(0.01f,0.01f, 0.01f);

	// 後ろ水
	_back_water = new WaterBackUnit(_application, _game_world);

	_weapon = new TitleWeaponUnit(_application, _game_world);
}

//=============================================================================
// 終了
void TitlePlayerUnit::Finalize()
{
	SafeDelete(_statnce_animation_system);
	SafeDeleteArray(_shader);
	SafeDelete(_back_water);
	SafeDelete(_weapon);
}

//=============================================================================
// 更新
void TitlePlayerUnit::Update()
{
	_back_water->Update();
	_weapon->Update();
	_statnce_animation_system->AdvanceFrame(1);
}

//=============================================================================
// 描画
void TitlePlayerUnit::Draw()
{

	SettingShaderParameter();

	// 描画する情報を押し込む：１度の描画に１度しか呼ばないこと
	D3DXMATRIX animation_matrix_list[ShaderToonPlayer::kMatrixMax];

	auto mesh_list = _game_world->GetAnimationMeshResource()->Get(ANIMATION_MESH_RESOURE_GRANDPA);

	u32 mesh_id = 0;
	D3DXVECTOR3 upper_rotation(0.f,0.f,0.f);
	for( auto it = mesh_list.begin(); it != mesh_list.end(); ++it, ++mesh_id )
	{
		UNREFERENCED_PARAMETER(it);
		_statnce_animation_system->ComputeHumanPose(animation_matrix_list, ShaderToonPlayer::kMatrixMax, *_statnce_animation, upper_rotation, mesh_id);

		_shader[mesh_id].SetAnimationMatrix(animation_matrix_list);

		//if( mesh_id == 2)
		{
			S_GetCommandBuffer()->PushRenderState(RENDER_STATE_DEFAULT, GetID());
			S_GetCommandBuffer()->PushShader(&_shader[mesh_id], GetID());
			S_GetCommandBuffer()->PushMesh((*it), GetID());
		}
		
		
	}

	_weapon->SetPosition(_world.matrix, animation_matrix_list[15]);
	_weapon->Draw();

	// 後ろ水の描画
	CompositionWater2Animation(animation_matrix_list);
}

//=============================================================================
// シェーダパラメーターの設定
void TitlePlayerUnit::SettingShaderParameter()
{
	// カメラの取得
	Camera* camera = _application->GetCameraManager()->GetCamera(CAMERA_TYPE_TITLE);

	// 行列の作成
	algo::CreateWorld(_world.matrix, _world.position, _world.rotation, _world.scale);
	algo::CreateWVP(_matrix_world_view_projection, _world.matrix, camera);

	// ライトの方向作成
	D3DXVECTOR4 light_direction(0.2f, -0.8f, 0.5f, 0.f);
	D3DXVECTOR4 ambient(0.97f, 0.8f, 0.75f, 1.0f);
	D3DXVECTOR4 eye(camera->GetVectorEye(), 0.f);

	for( u32 shader_index = 0; shader_index < _shader_size; ++shader_index )
	{
		// シェーダの設定
		_shader[shader_index].SetWorldViewProjection(_matrix_world_view_projection);
		_shader[shader_index].SetWorld(_world.matrix);
		_shader[shader_index].SetLightDirection(light_direction);
		_shader[shader_index].SetEyePosition(eye);
		_shader[shader_index].SetWorld(_world.matrix);
	}
}
//=============================================================================
// 水とアニメーションを合わせる
void TitlePlayerUnit::CompositionWater2Animation(const D3DXMATRIX* matrices)
{
	D3DXMATRIX water_back_matrix;
	D3DXVECTOR4 back_water_position;

	auto mesh_list = _game_world->GetAnimationMeshResource()->Get(ANIMATION_MESH_RESOURE_GRANDPA);

	VERTEX_AMO* vertex = nullptr;
	mesh_list[3]->GetVertexBuffer(0)->Lock(0,0,(void**)&vertex,0);

	u32 vertex_index = 340;
	water_back_matrix = matrices[vertex[vertex_index].bone_index[0]] * vertex[vertex_index].weight[0];
	water_back_matrix += matrices[vertex[vertex_index].bone_index[1]] * vertex[vertex_index].weight[1];
	water_back_matrix += matrices[vertex[vertex_index].bone_index[2]] * vertex[vertex_index].weight[2];
	water_back_matrix += matrices[vertex[vertex_index].bone_index[3]] * vertex[vertex_index].weight[3];

	D3DXVec3Transform(&back_water_position, &vertex[vertex_index].position, &water_back_matrix);

	D3DXMATRIX offset_matrix;
	D3DXVECTOR3 temp_water_position = static_cast<D3DXVECTOR3>(back_water_position);
	D3DXVECTOR3 stans_vector(296, -653.f, -365.f);
	D3DXMatrixTranslation(&offset_matrix, stans_vector.x, stans_vector.y, stans_vector.z);
	D3DXVec3Transform(&back_water_position, &temp_water_position, &offset_matrix);

	temp_water_position = static_cast<D3DXVECTOR3>(back_water_position);
	D3DXVec3Transform(&back_water_position, &temp_water_position, &_world.matrix);

	mesh_list[3]->GetVertexBuffer(0)->Unlock();

	_back_water->SetPosition(static_cast<D3DXVECTOR3>(back_water_position));
	_back_water->Draw();
}

//=============================================================================
// テクスチャを選択
void TitlePlayerUnit::SelectAlbedoTexture(bool is_player_one)
{
	LPDIRECT3DTEXTURE9 albedo_map;
	LPDIRECT3DTEXTURE9 albedo_map2;
	LPDIRECT3DTEXTURE9 albedo_map3;


	if( is_player_one )
	{
		albedo_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_PLAYER_TEXTURE);
		albedo_map2 = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_PLAYER_BAG_TEXTURE);
		albedo_map3 = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_PLAYER_FACE);
	}
	else
	{
		albedo_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_PLAYER_2_TEXTURE);
		albedo_map2 = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_PLAYER_2_BAG);
		albedo_map3 = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_PLAYER_2_FACE);
	}

	for( u32 shader_index = 0; shader_index < _shader_size; ++shader_index )
	{
		_shader[shader_index].SetAlbedoTexture(albedo_map);
	}
	_shader[0].SetAlbedoTexture(albedo_map3);
	_shader[1].SetAlbedoTexture(albedo_map);
	_shader[2].SetAlbedoTexture(albedo_map3);
	_shader[3].SetAlbedoTexture(albedo_map2);

	_weapon->SelectAlbedoTexture(is_player_one);
}