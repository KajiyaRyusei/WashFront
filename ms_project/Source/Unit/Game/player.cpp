//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// プレイヤー
// 
// Created by Ryusei Kajiya on 20151130
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit/Game/player.h"
#include "Shader/Shader/toon_player_shader.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"
#include "Animation/animation_system.h"
#include "Input/input_manager.h"
#include "Algorithm/often_use.h"
#include "DevelopTool/develop_tool_manager.h"
#include "Unit/Game/aim.h"
#include "World/collision_grid.h"
#include "Unit/Game/weapon.h"
#include "Unit/Game/water_back.h"
//リソース
#include "Resource/cube_texture_resource.h"
#include "Resource/texture_resource.h"
#include "Resource/animation_mesh_resource.h"
#include "Resource/Mesh/mesh_buffer.h"
#include "Resource/Mesh/Mesh/mesh_factory_amo.h"
// ルート
#include "Data/data_route.h"

//*****************************************************************************
// 定数
namespace
{
	static const D3DXVECTOR3 kVectorFromCamera(0.f, 0.f, 5.f);
}

//=============================================================================
// 初期化
void PlayerUnit::Initialize()
{
	// アニメーションモデルの読み込み
	auto mesh_list = _game_world->GetAnimationMeshResource()->Get(ANIMATION_MESH_RESOURE_GRANDPA);
	_animation.LoadAnimationFile("Data/Animation/new_standby60.oaf", mesh_list.size());

	// アニメーションシステムの作成
	_animation_system = new AnimationSystem();

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


	_shader[3].SetDiffuseCubeMap(diffuse_cube_map2);
	_shader[3].SetSpecularCubeMap(specular_cube_map2);
	_shader[3].SetAlbedoTexture(albedo_map2);

	// 座標
	_position.current = D3DXVECTOR3(0.f,0.f,0.f);
	_position.previous = _position.current;
	_world.position = _position.current;
	_world.rotation = D3DXVECTOR3(0.f, 0.f, 0.f);
	_world.scale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);

	// Aim
	_aim = new AimUnit(_application, _game_world);
	_aim->SetPlayer(this);

	// コマンドハンドラ
	_command_handler = new CommandHandler();

	// 武器
	_weapon = new WeaponUnit(_application, _game_world);
	_weapon->SetPlayer(this);

	// 後ろ水
	_back_water = new WaterBackUnit(_application, _game_world);
}

//=============================================================================
// 終了
void PlayerUnit::Finalize()
{
	SafeDelete(_weapon);
	
	SafeDelete(_aim);
	SafeDelete(_animation_system);
	_animation.UnLoadAnimationFile();
	SafeDeleteArray(_shader);
	SafeDelete(_command_handler);
	SafeDelete(_back_water);
}

//=============================================================================
// 更新
void PlayerUnit::Update()
{
	// プレイヤーの座標変更
	PassRootDecision();

	AimUpdate();
	_weapon->Update();
	_back_water->Update();
	_animation_system->AdvanceFrame(1);
}
//=============================================================================
// 衝突判定用更新
void PlayerUnit::CollisionUpdate()
{
	// Aimの衝突判定用更新
	_aim->CollisionUpdate();

	// 弾を発射 
	Command* command = _command_handler->HandleInput(_application->GetInputManager(), _controller_type);
	if( command != nullptr )
	{
		command->Execute(this);
	}

	// プレイヤーのポジションを教える
	_player_camera->SetPlayerPosition(_position.current);
}

//=============================================================================
// 描画
void PlayerUnit::Draw()
{
	Camera* camera = _application->GetCameraManager()->GetCurrentCamera();
	D3DXVECTOR3 culling_point(_position.current);

	if( camera->GetFrustumCulling().ClipCheck(_position.current, 10.f) )
	{
		SettingShaderParameter();

		// 描画する情報を押し込む：１度の描画に１度しか呼ばないこと
		D3DXMATRIX animation_matrix_list[ShaderToonPlayer::kMatrixMax];
		for( u8 i = 0; i < ShaderToonPlayer::kMatrixMax; ++i )
		{
			D3DXMatrixIdentity(&animation_matrix_list[i]);
		}

		auto mesh_list = _game_world->GetAnimationMeshResource()->Get(ANIMATION_MESH_RESOURE_GRANDPA);

		u32 mesh_id = 0;
		for( auto it = mesh_list.begin(); it != mesh_list.end(); ++it, ++mesh_id )
		{
			UNREFERENCED_PARAMETER(it);
			_animation_system->ComputeHumanPose(animation_matrix_list, ShaderToonPlayer::kMatrixMax, _animation, _player_camera->GetCameraRotation(), mesh_id);
			_shader[mesh_id].SetAnimationMatrix(animation_matrix_list);

			//if( mesh_id  == 3)
			{
				S_GetCommandBuffer()->PushRenderState(RENDER_STATE_DEFAULT, GetID());
				S_GetCommandBuffer()->PushShader(&_shader[mesh_id], GetID());
				S_GetCommandBuffer()->PushMesh((*it), GetID());
			}
			
		}

		// 武器の描画
		_weapon->SetPosition(_world.matrix, animation_matrix_list[15]);
		_weapon->Draw();

		// 後ろ水の描画
		CompositionWater2Animation(animation_matrix_list);

		// Aimの描画
		_aim->Draw();
	}
	
}

//=============================================================================
// シェーダパラメーターの設定
void PlayerUnit::SettingShaderParameter()
{
	// カメラの取得
	Camera* camera = _application->GetCameraManager()->GetCurrentCamera();

	// 行列の作成
	_world.position = _position.current;

	// HAKC
	//_world.rotation.y += 0.01f;

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
// Aimの更新
void PlayerUnit::AimUpdate()
{

	Command* command = _command_handler->HandleInputMove(_application->GetInputManager(), _controller_type);
	if( command != nullptr )
	{
		command->Execute(this);
	}
	else
	{
		D3DXVECTOR3 zero_vector(0.f,0.f,0.f);
		_aim->SetRotation(zero_vector);
	}

	_aim->Update();
}

//=============================================================================
// 座標と向き設定
void PlayerUnit::PassRootDecision()
{
	data::Route route = _player_camera->GetCurrentRoute();
	D3DXVECTOR3 eye_position = _player_camera->GetVectorEye();

	// 視点を中心に注視点を回転
	D3DXMATRIX player_rotation_matrix;
	D3DXMatrixRotationQuaternion(&player_rotation_matrix, &route.player_quaternion);
	D3DXVec3TransformCoord(&_position.current, &kVectorFromCamera, &player_rotation_matrix);
	_position.current += eye_position;

	_world.rotation.y = atan2f(_aim->GetTargetPosition().x - _position.current.x, _aim->GetTargetPosition().z - _position.current.z);
	_world.rotation.x = atan2f(_position.current.y, _aim->GetTargetPosition().y);
	_world.rotation.x += D3DX_PI * -0.3f;
}

//=============================================================================
// 水とアニメーションを合わせる
void PlayerUnit::CompositionWater2Animation(const D3DXMATRIX* matrices)
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
	D3DXMatrixTranslation(&offset_matrix, 296, -533.f, -465.f);
	D3DXVec3Transform(&back_water_position, &temp_water_position, &offset_matrix);
	

	temp_water_position = static_cast<D3DXVECTOR3>(back_water_position);
	D3DXVec3Transform(&back_water_position, &temp_water_position, &_world.matrix);

	mesh_list[3]->GetVertexBuffer(0)->Unlock();

	_back_water->SetPosition(static_cast<D3DXVECTOR3>(back_water_position));
	_back_water->Draw();
}

//=============================================================================
// プレイヤーの座標を取得
const D3DXVECTOR3 PlayerUnit::GetPosition()
{
	D3DXVECTOR3 player_point;
	player_point = _world.position;

	player_point.y += 1.2f;

	return player_point;
}