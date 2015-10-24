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
}

//=============================================================================
// 終了
void PlayerUnit::Finalize()
{
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
	static float position_z = 0.f;
	//position_z += 0.1f;
	// 行列の作成
	D3DXMATRIX matrix_world;
	algo::CreateWorld(matrix_world, D3DXVECTOR3(0.f, 0.f, position_z), D3DXVECTOR3(0.f, 0.f, 0.f), D3DXVECTOR3(0.007f, 0.007f, 0.007f));
	CameraGamePlayer* camera = static_cast<CameraGamePlayer*>(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER));
	D3DXMATRIX matrix_world_view_projection;
	algo::CreateWVP(matrix_world_view_projection,matrix_world,camera);

	// プレイヤーのポジションを教える
	camera->SetPlayerPosition(D3DXVECTOR3(0.f, 0.f, position_z));

	// ライトの方向作成
	D3DXVECTOR4 light_direction;
	algo::CreateLocalDirection(light_direction, D3DXVECTOR4(0.f, -0.5f, -1.f, 0.f), matrix_world);

	// シェーダの設定
	_shader->SetWorldViewProjection(matrix_world_view_projection);
	_shader->SetLightDirection(light_direction);

	// フレームの更新
	_animation_system->AdvanceFrame(1);
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

}