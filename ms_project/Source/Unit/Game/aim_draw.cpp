//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 描画用AIM
// 
// Created by Ryusei Kajiya on 20151102
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "aim_draw.h"
#include "Shader/Shader/aim_shader.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"
#include "Renderer/directx9.h"

//リソース
#include "Resource/texture_resource.h"
#include "Resource/mesh_resource.h"

//=============================================================================
// 初期化
void AimDrawUnit::Initialize()
{
	// シェーダの作成
	_shader = new ShaderAim();
	LPDIRECT3DTEXTURE9 albedo_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_AIM_TEXTURE);
	_shader->SetAlbedoTexture(albedo_map);

}

//=============================================================================
// 終了
void AimDrawUnit::Finalize()
{
	SafeDelete(_shader);
}

//=============================================================================
// 更新
void AimDrawUnit::Update()
{
	CalculatePosition();
}

//=============================================================================
// 描画
void AimDrawUnit::Draw()
{
	// 描画する情報を押し込む：１度の描画に１度しか呼ばないこと
	S_GetCommandBuffer()->PushRenderState(RENDER_STATE_AIM, GetID());
	S_GetCommandBuffer()->PushShader(_shader, GetID());
	S_GetCommandBuffer()->PushMesh(_game_world->GetMeshResource()->Get(MESH_RESOURE_SPRITE), GetID());
}

//=============================================================================
// カメラから自分の位置を算出
void AimDrawUnit::CalculatePosition()
{
	// カメラ取得
	CameraGamePlayer* camera = static_cast<CameraGamePlayer*>(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER));

	// 回転を打ち消し
	D3DXMATRIX view = camera->GetMatrixView();
	D3DXMATRIX projection = camera->GetMatrixProjection();
	D3DXMATRIX inverse_view;
	D3DXMatrixInverse(&inverse_view, nullptr, &view);
	D3DXMATRIX test_matrix = inverse_view * view;

	// ごみを削除
	inverse_view._41 = 0.f;
	inverse_view._42 = 0.f;
	inverse_view._43 = 0.f;

	// カメラの視点と注視点から自分の座標を求める
	D3DXVECTOR3 eye = camera->GetVectorEye();
	D3DXVECTOR3 look_at = camera->GetVectorLookAt();
	D3DXVec3Lerp(&_world.position, &eye, &look_at,0.5f);
	_world.scale = D3DXVECTOR3(1.f, 1.f, 1.f);

	D3DXMATRIX scaling_matrix, translation_matrix;

	D3DXMatrixScaling(&scaling_matrix, _world.scale.x, _world.scale.y, _world.scale.z);
	D3DXMatrixTranslation(&translation_matrix, _world.position.x, _world.position.y, _world.position.z);
	_world.matrix = inverse_view * scaling_matrix * translation_matrix;
	_matrix_world_view_projection = _world.matrix * view * projection;
	_shader->SetWorldViewProjection(_matrix_world_view_projection);

}