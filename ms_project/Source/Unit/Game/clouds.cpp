//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 雲
// 
// Created by Ryusei Kajiya on 201511214
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit/Game/clouds.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"
#include "Algorithm/often_use.h"
#include "Shader/Shader/static_toon_cloud_shader.h"

//リソース
#include "Resource/cube_texture_resource.h"
#include "Resource/texture_resource.h"

#include "Resource/Mesh/Mesh/mesh_factory_smo_instance.h"

//*****************************************************************************
// 定数
namespace
{
	static const fx32 kLimitedZ = 1000.f;
}

//=============================================================================
// 初期化
void CloudsUnit::Initialize()
{
	CloudSelect();
	_shader_size = _mesh_list.size();
	_shader = new ShaderStaticToonCloud[_shader_size];

	LPDIRECT3DCUBETEXTURE9 diffuse_cube_map = _game_world->GetCubeTextureResource()->Get(CUBE_TEXTURE_RESOURE_GRID_ZERO_ZERO_DIFFUSE);
	LPDIRECT3DTEXTURE9 toon_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_TOON_TEXTURE);

	for( u32 shader_index = 0; shader_index < _shader_size; ++shader_index )
	{
		_shader[shader_index].SetDiffuseCubeMap(diffuse_cube_map);
		_shader[shader_index].SetToonTexture(toon_map);
	}

	CloudSettingPosition();
}

//=============================================================================
// 終了
void CloudsUnit::Finalize()
{
	SafeDeleteArray(_shader);
	for( auto it = _mesh_list.begin(); it != _mesh_list.end(); ++it )
	{
		SafeDelete(*it);
	}
}

//=============================================================================
// 更新
void CloudsUnit::Update()
{
	LimitedPosition();
	MovePosition();
}

//=============================================================================
// 描画
void CloudsUnit::Draw()
{
	SettingShaderParameter();

	MeshFactorySMOInstance factory;
	
	factory.RegisterMatrix(_work_world_matrix, kCloudMax,_mesh_list);

	u32 mesh_id = 0;

	for( auto it = _mesh_list.begin(); it != _mesh_list.end(); ++it, ++mesh_id )
	{
		UNREFERENCED_PARAMETER(it);
		S_GetCommandBuffer()->PushRenderState(RENDER_STATE_DEFAULT, GetID());
		S_GetCommandBuffer()->PushShader(&_shader[mesh_id], GetID());
		S_GetCommandBuffer()->PushMesh((*it), GetID());
	}
}

//=============================================================================
// シェーダパラメーターの設定
void CloudsUnit::SettingShaderParameter()
{
	// カメラ取得
	Camera* camera = _application->GetCameraManager()->GetCurrentCamera();

	for( u32 i = 0; i < kCloudMax; ++i )
	{
		algo::CreateWorld(_world[i].matrix, _world[i].position, _world[i].rotation, _world[i].scale);
		_work_world_matrix[i] = _world[i].matrix;
		_matrix_view_projection = camera->GetMatrixView() * camera->GetMatrixProjection();

		// ライトの方向作成
		D3DXVECTOR4 light_direction(0.2f, -0.8f, 0.5f, 0.f);

		for( u32 shader_index = 0; shader_index < _shader_size; ++shader_index )
		{
			_shader[shader_index].SetViewProjection(_matrix_view_projection);
			_shader[shader_index].SetView(camera->GetMatrixView());
			_shader[shader_index].SetLightDirection(light_direction);
		}
	}
}

//=============================================================================
// 雲選択
void CloudsUnit::CloudSelect()
{
	std::random_device rd;

	std::mt19937 mt(rd());

	std::uniform_int_distribution<s32> dice(0, 2);

	std::uniform_real_distribution<fx32> dice_float(0.f, 0.3f);

	MeshFactorySMOInstance factory;

	factory.Create(_application->GetRendererDevice(),"Data/StaticModel/cloud_1.smo",_mesh_list,kCloudMax);
	switch( dice(mt) )
	{
	case 0:
		factory.Create(_application->GetRendererDevice(), "Data/StaticModel/cloud_1.smo", _mesh_list, kCloudMax);
		break;
	case 1:
		factory.Create(_application->GetRendererDevice(), "Data/StaticModel/cloud_2.smo", _mesh_list, kCloudMax);
		break;
	case 2:
		factory.Create(_application->GetRendererDevice(), "Data/StaticModel/cloud_3.smo", _mesh_list, kCloudMax);
		break;
	default:
		factory.Create(_application->GetRendererDevice(), "Data/StaticModel/cloud_1.smo", _mesh_list, kCloudMax);
		break;
	}

	_velocity.current.z = dice_float(mt);
}

//=============================================================================
// 座標の限界
void CloudsUnit::LimitedPosition()
{
	for( u32 i = 0; i < kCloudMax; ++i )
	{
		if( _world[i].position.z > kLimitedZ )
		{
			_world[i].position.z = 0;
		}
	}
}

//=============================================================================
// 座標の限界
void CloudsUnit::MovePosition()
{
	for( u32 i = 0; i < kCloudMax; ++i )
	{
		_world[i].position.z += _velocity.current.z;
	}
	
}

//=============================================================================
// 雲のポジションランダム
void CloudsUnit::CloudSettingPosition()
{
	D3DXVECTOR3 positions[kCloudMax];
	positions[0] = D3DXVECTOR3(300.f, 200.f, 500.f);
	positions[1] = D3DXVECTOR3(20.f, 200.f, 10.f);
	positions[2] = D3DXVECTOR3(100.f, 240.f, 390.f);
	positions[3] = D3DXVECTOR3(500.f, 250.f, 200.f);
	positions[4] = D3DXVECTOR3(400.f, 200.f, 10.f);
	positions[5] = D3DXVECTOR3(30.f, 210.f, 500.f);
	positions[6] = D3DXVECTOR3(10.f, 230.f, 120.f);
	positions[7] = D3DXVECTOR3(10.f, 200.f, 400.f);
	positions[8] = D3DXVECTOR3(300.f, 200.f, 100.f);
	positions[9] = D3DXVECTOR3(200.f, 280.f, 100.f);

	positions[10] = D3DXVECTOR3(-200.f, 110.f, 100.f);
	positions[11] = D3DXVECTOR3(-100.f, 130.f, 220.f);
	positions[12] = D3DXVECTOR3(500.f, 30.f, 300.f);
	positions[13] = D3DXVECTOR3(450.f, 120.f, 300.f);
	positions[14] = D3DXVECTOR3(-300.f, 140.f, 100.f);

	fx32 scales[kCloudMax];
	scales[0] = 5.f;
	scales[1] = 4.f;
	scales[2] = 8.f;
	scales[3] = 6.f;
	scales[4] = 7.f;
	scales[5] = 4.f;
	scales[6] = 10.f;
	scales[7] = 7.f;
	scales[8] = 4.f;
	scales[9] = 7.f;

	scales[10] = 4.f;
	scales[11] = 10.f;
	scales[12] = 9.f;
	scales[13] = 8.f;
	scales[14] = 7.f;

	fx32 rotations[kCloudMax];
	rotations[0] = 0.f;
	rotations[1] = 0.5f;
	rotations[2] = -0.1f;
	rotations[3] = 0.3f;
	rotations[4] = 0.4f;
	rotations[5] = -0.2f;
	rotations[6] = 0.f;
	rotations[7] = 0.f;
	rotations[8] = 0.2f;
	rotations[9] = -0.1f;

	rotations[10] = -0.2f;
	rotations[11] = 0.f;
	rotations[12] = 0.f;
	rotations[13] = 0.2f;
	rotations[14] = -0.1f;

	for( u32 i = 0; i < kCloudMax; ++i )
	{
		_world[i].position = positions[i];
		_world[i].scale = D3DXVECTOR3(scales[i], scales[i], scales[i]);
		_world[i].rotation = D3DXVECTOR3(rotations[i], rotations[i], rotations[i]);
	}
}