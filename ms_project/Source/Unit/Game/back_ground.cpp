//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 背景用天球
// 
// Created by Ryusei Kajiya on 20151102
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "back_ground.h"
#include "Shader/Shader/back_ground_shader.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"

//リソース
#include "Resource/cube_texture_resource.h"
#include "Resource/mesh_resource.h"

//=============================================================================
// 初期化
void BackGroundUnit::Initialize()
{
	// シェーダの作成
	_shader = new ShaderBackGround();

	// キューブマップセット
	LPDIRECT3DCUBETEXTURE9 texture = _game_world->GetCubeTextureResource()->Get(CUBE_TEXTURE_RESOURE_GRID_ZERO_ONE_SPECULAR);
	_shader->SetAlbedoCubeTexture(texture);
}

//=============================================================================
// 終了
void BackGroundUnit::Finalize()
{
	SafeDelete(_shader);
}

//=============================================================================
// 更新
void BackGroundUnit::Update()
{
	
}

//=============================================================================
// 描画
void BackGroundUnit::Draw()
{
	// カメラ取得
	Camera* camera = _application->GetCameraManager()->GetCurrentCamera();
	D3DXMATRIX matrix_scaling;
	static const float kScaling = 500.f;
	D3DXMatrixScaling(&matrix_scaling, kScaling, kScaling, kScaling);
	D3DXMATRIX matrix_world_view_projection = matrix_scaling * camera->GetMatrixView() * camera->GetMatrixProjection();
	_shader->SetWorldViewProjection(matrix_world_view_projection);

	// 描画する情報を押し込む：１度の描画に１度しか呼ばないこと
	S_GetCommandBuffer()->PushRenderState(RENDER_STATE_BACKGROUND,GetID());
	S_GetCommandBuffer()->PushShader(_shader, GetID());
	S_GetCommandBuffer()->PushMesh(_game_world->GetMeshResource()->Get(MESH_RESOURE_BOX), GetID());
}
