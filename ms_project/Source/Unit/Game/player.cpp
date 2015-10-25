//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// プレイヤー
// 
// Created by Ryusei Kajiya on 20151022
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "player.h"
#include "System/application.h"
#include "Shader/Shader/PBL_animation_shader.h"
#include "Resource/Mesh/Mesh/mesh_factory_amo.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"
#include "DrawCommand/command_buffer.h"
#include "Animation/animation_system.h"
#include "Input/input_manager.h"
#include "Algorithm/often_use.h"
#include "DevelopTool/develop_tool_manager.h"
#include "Renderer/directx9.h"

//=============================================================================
// 初期化
void PlayerUnit::Initialize()
{
	// シェーダの作成
	_shader = new ShaderPBLAnimation();

	// メッシュの作成
	MeshFactoryAMO mesh_factory;
	mesh_factory.Create(_application->GetRendererDevice(), "Data/AnimationModel/oba_walk.amo", _mesh_list);

	// アニメーションの読み込み
	_animation.LoadAnimationFile("Data/Animation/oba_walk.oaf",_mesh_list.size());

	// アニメーションシステムの作成
	_animation_system = new AnimationSystem();

	// テクスチャ
	LPDIRECT3DDEVICE9 device = _application->GetRendererDevice()->GetDevice();
	D3DXCreateCubeTextureFromFileEx(device, L"Data/CubeTexture/rnl_cross.dds", 2, 1, 0, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xff, nullptr, nullptr, &_diffuse_cube_map);
	D3DXCreateCubeTextureFromFileEx(device, L"Data/CubeTexture/rnl_cross.dds", 0, 0, 0, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xff, nullptr, nullptr, &_specular_cube_map);
	D3DXCreateTextureFromFileEx(device, L"Data/Texture/oba.jpg", 0, 0, 0, 0, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xff, nullptr, nullptr, &_albedo_map);

}

//=============================================================================
// 終了
void PlayerUnit::Finalize()
{
	SafeRelease(_diffuse_cube_map);
	SafeRelease(_specular_cube_map);
	SafeRelease(_albedo_map);

	SafeDelete(_animation_system);
	_animation.UnLoadAnimationFile();
	for( auto it : _mesh_list )
	{
		SafeDelete(it);
	}
	SafeDelete(_shader);
}

//=============================================================================
// 更新
void PlayerUnit::Update()
{
	// カメラ取得
	CameraGamePlayer* camera = static_cast<CameraGamePlayer*>(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER));

	// プレイヤーのポジションを教える
	camera->SetPlayerPosition(D3DXVECTOR3(0.f, 0.f, _world.position.z));

	// フレームの更新
	_animation_system->AdvanceFrame(1);

	SettingShaderParameter();
}

//=============================================================================
// 描画
void PlayerUnit::Draw()
{
	// 描画する情報を押し込む：１度の描画に１度しか呼ばないこと
	D3DXMATRIX animation_matrix_list[ShaderPBLAnimation::kMatrixMax];
	CameraGamePlayer* camera = static_cast<CameraGamePlayer*>(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER));
	for( auto it : _mesh_list )
	{
		_animation_system->ComputeHumanPose(animation_matrix_list, ShaderPBLAnimation::kMatrixMax, _animation, camera->GetCameraRotation());
		_shader->SetAnimationMatrix(animation_matrix_list);
		S_GetCommandBuffer()->PushRenderState(RENDER_STATE_DEFAULT, GetID());
		S_GetCommandBuffer()->PushShader(_shader, GetID());
		S_GetCommandBuffer()->PushMesh(it, GetID());
	}
}

//=============================================================================
// シェーダパラメーターの設定
void PlayerUnit::SettingShaderParameter()
{
	static float position_z = 0.f;
	static float rotation = 0.f;
	//rotation += 0.01f;
	// カメラ取得
	CameraGamePlayer* camera = static_cast<CameraGamePlayer*>(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER));
	// 行列の作成
	_world.position.z = position_z;
	_world.rotation.y = rotation;
	_world.scale = D3DXVECTOR3(0.007f, 0.007f, 0.007f);
	algo::CreateWorld(_world.matrix, _world.position, _world.rotation, _world.scale);	
	algo::CreateWVP(_matrix_world_view_projection, _world.matrix, camera);
	// ライトの方向作成
	D3DXVECTOR4 light_direction(0.2f, -0.8f, 0.5f, 0.f);
	D3DXVECTOR4 ambient(0.97f, 0.8f, 0.75f, 1.f);
	D3DXVECTOR4 eye(camera->GetVectorEye(), 0.f);
	// シェーダの設定
	_shader->SetWorldViewProjection(_matrix_world_view_projection);
	_shader->SetWorld(_world.matrix);
	_shader->SetLightDirection(light_direction);
	_shader->SetAlbedoTexture(_albedo_map);
	_shader->SetAmbientColor(ambient);
	_shader->SetDiffuseCubeMap(_diffuse_cube_map);
	_shader->SetSpecularCubeMap(_specular_cube_map);
	_shader->SetEyePosition(eye);
	_shader->SetFresnel(0.3f);
	_shader->SetMetalness(0.0f);
	_shader->SetRoughness(1.0f);
	_shader->SetWorld(_world.matrix);
}
