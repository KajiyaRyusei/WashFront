//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 水弾
// 
// Created by Ryusei Kajiya on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit/Game/water_bullet.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"
#include "Algorithm/often_use.h"
#include "Shader/Shader/water_shader.h"
#include "World/collision_grid.h"

//リソース
#include "Resource/cube_texture_resource.h"
#include "Resource/texture_resource.h"
#include "Resource/mesh_resource.h"

#include "Unit/Game/player.h"

//*****************************************************************************
// 定数
namespace
{
	static const fx32 kReleaseOfCoefficient = 0.5f;
}

//=============================================================================
// 初期化
void WaterBulletUnit::Initialize()
{
	// シェーダの作成
	_shader = new ShaderWater();

	// テクスチャ
	LPDIRECT3DTEXTURE9 albedo_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_WATER_BALL_TEXTURE);
	LPDIRECT3DTEXTURE9 normal_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_WATER_NORMAL_TEXTURE);

	_shader->SetAlbedoTexture(albedo_map);
	_shader->SetNormalTexture(normal_map);

	// 座標の設定
	_position.current = D3DXVECTOR3(0.f,0.f,0.f);
	_position.previous = _position.current;
	_world.position = _position.current;
	_world.scale = D3DXVECTOR3(1.f, 1.f, 1.f);
	_world.rotation = D3DXVECTOR3(0.f, 0.f, 0.f);
	_release_of = 0.f;
	_destination_release_of = _release_of;

	// 色の初期値
	_ambient = D3DXVECTOR4(0.97f, 0.8f, 0.75f, 1.f);
}

//=============================================================================
// 終了
void WaterBulletUnit::Finalize()
{
	SafeDelete(_shader);
}

//=============================================================================
// 更新
void WaterBulletUnit::Update()
{
	_release_of += (_destination_release_of - _release_of) * kReleaseOfCoefficient;
	_destination_release_of -= kReleaseOfCoefficient*0.2f;
	if( _destination_release_of  <= 0.f)
	{
		_destination_release_of = 0.f;
	}
}
//=============================================================================
// 衝突判定用更新
void WaterBulletUnit::CollisionUpdate()
{

}

//=============================================================================
// 描画
void WaterBulletUnit::Draw()
{
	_start_point = _player->GetPosition();
	_rotation_y = atan2f(_end_point.x - _start_point.x, _end_point.z - _start_point.z);
	_start_point += D3DXVECTOR3(sinf(_rotation_y - 0.6f) * 0.35f, -0.25f, cosf(_rotation_y - 0.6f) * 0.35f);

	// シェーダパラメーターの更新
	SettingShaderParameter();

	// 描画する情報を押し込む：１度の描画に１度しか呼ばないこと
	auto mesh = _game_world->GetMeshResource()->Get(MESH_RESOURE_WATER_CYLINDER);
	S_GetCommandBuffer()->PushRenderState(RENDER_STATE_DEFAULT, GetID());
	S_GetCommandBuffer()->PushShader(_shader, GetID());
	S_GetCommandBuffer()->PushMesh(mesh, GetID());
}

//=============================================================================
// シェーダパラメーターの設定
void WaterBulletUnit::SettingShaderParameter()
{
	// カメラ取得
	Camera* camera = _application->GetCameraManager()->GetCurrentCamera();
	// 行列の作成
	_world.position = _position.current;
	algo::CreateWorld(_world.matrix, _world.position, _world.rotation, _world.scale);
	algo::CreateWVP(_matrix_world_view_projection, _world.matrix, camera);
	// ライトの方向作成
	D3DXVECTOR4 light_direction(0.2f, -0.8f, 0.5f, 0.f);
	D3DXVECTOR4 eye(camera->GetVectorEye(), 0.f);

	// シェーダの設定
	_shader->SetWorldViewProjection(_matrix_world_view_projection);
	_shader->SetLightDirection(light_direction);
	_shader->SetAmbientColor(_ambient);
	_shader->SetEyePosition(eye);
	_shader->SetFresnel(0.6f);
	_shader->SetMetalness(0.2f);
	_shader->SetRoughness(0.3f);
	_shader->SetWorld(_world.matrix);
	static D3DXVECTOR2 texcoord_move(0.f,0.f);
	texcoord_move.y -= 0.03f;
	_shader->SetTexcoordMove(texcoord_move);


	D3DXMATRIX matrix_composition[3], matrix_translration[3], matrix_rotation[3], matrix_scale[3];

	D3DXMatrixIdentity(&matrix_composition[0]);
	D3DXMatrixIdentity(&matrix_composition[1]);
	D3DXMatrixIdentity(&matrix_composition[2]);

	D3DXMatrixTranslation(&matrix_translration[0], _start_point.x, _start_point.y, _start_point.z);
	D3DXMatrixTranslation(&matrix_translration[1], _control_point.x, _control_point.y, _control_point.z);
	D3DXMatrixTranslation(&matrix_translration[2], _end_point.x, _end_point.y, _end_point.z);

	D3DXMatrixRotationYawPitchRoll(&matrix_rotation[0], _rotation_y, 0.f, 0.f);
	D3DXMatrixRotationYawPitchRoll(&matrix_rotation[1], _rotation_y, 0.f, 0.f);
	D3DXMatrixRotationYawPitchRoll(&matrix_rotation[2], _rotation_y, 0.f, 0.f);

	D3DXMatrixScaling(&matrix_scale[0], _release_of*0.03f, _release_of*0.03f, _release_of);
	D3DXMatrixScaling(&matrix_scale[1], _release_of * 0.5f, _release_of* 0.5f, _release_of);
	D3DXMatrixScaling(&matrix_scale[2], _release_of*2.0f, _release_of*2.0f, _release_of);

	//D3DXMatrixScaling(&matrix_scale[0], 1.f, 1.f, 1.f);
	//D3DXMatrixScaling(&matrix_scale[1], 1.f, 1.f, 1.f);
	//D3DXMatrixScaling(&matrix_scale[2], 1.f, 1.f, 1.f);


	_application->GetDevelopToolManager()->GetDebugPrint().Print("水の位置 : %f %f %f \n", _end_point.x, _end_point.y, _end_point.z);

	for( int i = 0; i < 3; ++i )
	{
		matrix_composition[i] = matrix_scale[i] * matrix_rotation[i] * matrix_translration[i];
	}

	_shader->SetWaterMatrix(matrix_composition);
}

//=============================================================================
// 発射
void WaterBulletUnit::Fire(const D3DXVECTOR3& end)
{
	_start_point = _player->GetPosition();
	_end_point = end;
	D3DXVec3Lerp(&_control_point, &_start_point, &_end_point,0.3f);
	D3DXVECTOR3 control_point2;
	D3DXVec3Lerp(&control_point2, &_start_point, &_end_point, 0.3f);
	_control_point.y += 0.5f;
	//_control_point.x = control_point2.x;
	//_control_point.z = control_point2.z;
	_destination_release_of = 1.f;
}