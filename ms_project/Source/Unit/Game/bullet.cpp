//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// バレット
// 
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit/Game/bullet.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"
#include "Algorithm/often_use.h"
#include "Renderer/directx9.h"
#include "Shader/Shader/PBL_static_shader.h"
#include "Resource/Mesh/Mesh/mesh_factory_cube.h"
#include "World/collision_grid.h"

//=============================================================================
// 初期化
void BulletUnit::Initialize()
{
	// シェーダの作成
	_shader = new ShaderPBLStatic();

	// メッシュの作成
	MeshFactoryCube mesh_factory;
	_mesh = mesh_factory.Create(_application->GetRendererDevice());

	// テクスチャ
	LPDIRECT3DDEVICE9 device = _application->GetRendererDevice()->GetDevice();
	D3DXCreateCubeTextureFromFileEx(device, L"Data/CubeTexture/rnl_cross.dds", 2, 1, 0, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xff, nullptr, nullptr, &_diffuse_cube_map);
	D3DXCreateCubeTextureFromFileEx(device, L"Data/CubeTexture/rnl_cross.dds", 0, 0, 0, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xff, nullptr, nullptr, &_specular_cube_map);

	ASSERT(S_OK == D3DXCreateTextureFromFileEx(device, L"Data/Texture/Orange_glazed_pxr128_bmp.jpg", 0, 0, 0, 0, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xff, nullptr, nullptr, &_albedo_map),"テクスチャ読み込み失敗");
	ASSERT(S_OK == D3DXCreateTextureFromFileEx(device, L"Data/Texture/Orange_glazed_pxr128_normal.jpg", 0, 0, 0, 0, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xff, nullptr, nullptr, &_normal_map), "テクスチャ読み込み失敗");


	// 座標の設定
	_position.current = D3DXVECTOR3(0.f, 0.f, 0.f);
	_position.previous = _position.current;
	_world.position = _position.current;
	_world.scale = D3DXVECTOR3(1.f, 1.f, 1.f);
	_world.rotation = D3DXVECTOR3(0.f, 0.f, 0.f);

	// 弾の設定
	_start_point = _position.current;
	_end_point = _position.current;
	_control_point = _position.current;
	_frame_velocity = 0.f;
	_frame = 1.f;

	// ボリュームの作成
	CreateVolumeShpre(_world.position, _world.scale.x);

	// 空間に突っ込む
	_game_world->GetCollisionGrid()->AddUnit(this, _position);
}

//=============================================================================
// 終了
void BulletUnit::Finalize()
{
	SafeRelease(_diffuse_cube_map);
	SafeRelease(_specular_cube_map);
	SafeRelease(_albedo_map);
	SafeRelease(_normal_map);
	SafeDelete(_mesh);
	SafeDelete(_shader);
}

//=============================================================================
// 更新
void BulletUnit::Update()
{
	// シェーダパラメーターの更新
	if( _frame >= 1.f)
	{
		//_position.current = D3DXVECTOR3(100000.f, 100000.f, 100000.f);
		//_game_world->GetCollisionGrid()->MoveUnit(this, _position);
		_shpere->position = D3DXVECTOR3(100000.f, 100000.f, 100000.f);
	}
	else
	{
		Move();
		_game_world->GetCollisionGrid()->MoveUnit(this, _position);
		_shpere->position = _position.current;
	}

}
//=============================================================================
// 衝突判定用更新
void BulletUnit::CollisionUpdate()
{

}
//=============================================================================
// 衝突判定時処理
void BulletUnit::CollisionSphere()
{
	_frame = 1.f;
}
//=============================================================================
// 描画
void BulletUnit::Draw()
{
	SettingShaderParameter();
	// 描画する情報を押し込む：１度の描画に１度しか呼ばないこと
	if( _frame < 1.f )
	{
		S_GetCommandBuffer()->PushRenderState(RENDER_STATE_DEFAULT, GetID());
		S_GetCommandBuffer()->PushShader(_shader, GetID());
		S_GetCommandBuffer()->PushMesh(_mesh, GetID());
	}

	_shpere->DebugDraw();
}

//=============================================================================
// シェーダパラメーターの設定
void BulletUnit::SettingShaderParameter()
{
	// カメラ取得
	CameraGamePlayer* camera = static_cast<CameraGamePlayer*>(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER));
	// 行列の作成
	_world.position = _position.current;
	_world.rotation.x += 0.5f;
	algo::CreateWorld(_world.matrix, _world.position, _world.rotation, _world.scale);
	algo::CreateWVP(_matrix_world_view_projection, _world.matrix, camera);
	// ライトの方向作成
	D3DXVECTOR4 light_direction(0.2f, -0.8f, 0.5f, 0.f);
	D3DXVECTOR4 ambient(0.0f, 0.0f, 1.0f, 1.f);
	D3DXVECTOR4 eye(camera->GetVectorEye(), 0.f);
	// シェーダの設定
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
// 発射
void BulletUnit::Fire(
	const D3DXVECTOR3& start,
	const D3DXVECTOR3& end,
	const fx32 velocity)
{
	if( _frame < 1.f )
	{
		return;
	}
	_start_point = start;
	_end_point = end;
	_control_point = (start + end) / 2;
	_control_point.y += 3.f;
	_frame_velocity = velocity;
	_frame = 0.f;
	_position.current = start;
}

//=============================================================================
// 移動
void BulletUnit::Move()
{
	algo::BezierCurve2D(_position.current,_start_point,_end_point,_control_point,_frame);
	_frame += _frame_velocity;
}
