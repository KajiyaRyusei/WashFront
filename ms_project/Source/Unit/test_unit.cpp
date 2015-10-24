//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// テスト用ユニット
// 
// Created by Ryusei Kajiya on 20151009
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "test_unit.h"

#include "System/application.h"

#include "Shader/Shader/lambert.h"

#include "Resource/Mesh/Mesh/mesh_factory_cube.h"

#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_main.h"

#include "DrawCommand/command_buffer.h"

//=============================================================================
// 初期化
void TestUnit::Initialize()
{
	// シェーダの作成
	_shader = new ShaderLambert();

	// メッシュの作成
	MeshFactoryCube cube_factory;
	_mesh = cube_factory.Create(_application->GetRendererDevice());
}

//=============================================================================
// 終了
void TestUnit::Finalize()
{
	SafeDelete(_shader);
	SafeDelete(_mesh);
}

//=============================================================================
// 更新
void TestUnit::Update()
{
	D3DXMATRIX matrix_world;
	static float rotation = 0;
	D3DXMatrixRotationYawPitchRoll(&matrix_world, rotation, 0.f, 0.f);
	rotation += 0.01f;

	CameraGameMain* camera = static_cast<CameraGameMain*>(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_MAIN));
	D3DXMATRIX matrix_projection = camera->GetMatrixProjection();
	D3DXMATRIX matrix_view = camera->GetMatrixView();

	D3DXMATRIX matrix_world_view_projection = matrix_world * matrix_view * matrix_projection;

	_shader->SetWorldViewProjection(matrix_world_view_projection);
	D3DXVECTOR4 light_direction(0.f, -0.5f, -1.f, 0.f);
	D3DXMATRIX matrix_world_inverse;
	D3DXMatrixInverse(&matrix_world_inverse, nullptr, &matrix_world);
	D3DXVec4Transform(&light_direction, &light_direction, &matrix_world_inverse);
	D3DXVec4Normalize(&light_direction, &light_direction);
	_shader->SetLightDirection(light_direction);
}

//=============================================================================
// 描画
void TestUnit::Draw()
{
	// 描画する情報を押し込む：１度の描画に１度しか呼ばないこと
	S_GetCommandBuffer()->PushRenderState(RENDER_STATE_DEFAULT,GetID());
	S_GetCommandBuffer()->PushShader(_shader, GetID());
	S_GetCommandBuffer()->PushMesh(_mesh, GetID());
}