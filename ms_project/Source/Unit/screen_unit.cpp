//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// テストスクリーン用ユニット
// 
// Created by Ryusei Kajiya on 20151012
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "screen_unit.h"

#include "System/application.h"

#include "Shader/Shader/screen_shader.h"

#include "Resource/Mesh/Mesh/mesh_factory_sprite.h"

#include "DrawCommand/command_buffer.h"

#include "Windows/window.h"

//=============================================================================
// 初期化
void ScreenUnit::Initialize()
{
	// シェーダの作成
	_shader = new ShaderScreen();

	// 頂点バッファの作成
	MeshFactorySprite sprite_factory;
	_mesh = sprite_factory.Create(_application->GetRendererDevice());
}

//=============================================================================
// 終了
void ScreenUnit::Finalize()
{
	SafeDelete(_shader);
	SafeDelete(_mesh);
}

//=============================================================================
// 更新
void ScreenUnit::Update()
{
	D3DXMATRIX matrix_screen, matrix_rotation, matrix_scale, matrix_translation;
	D3DXMatrixIdentity(&matrix_screen);

	static const fx32 scaling(100.f);
	static fx32 rotation(0.f);
	rotation += 0.01f;
	static D3DXVECTOR3 position(100.f, 100.f, 0.f);

	D3DXMatrixScaling(&matrix_scale, scaling, scaling, scaling);
	D3DXMatrixRotationZ(&matrix_rotation, rotation);
	D3DXMatrixTranslation(&matrix_translation, position.x, position.y, position.z);

	matrix_screen = matrix_rotation * matrix_scale * matrix_translation;

	_shader->SetScreenMatrix(matrix_screen);

	_shader->SetScreenSize(D3DXVECTOR2(
		static_cast<fx32>(_application->GetWindow()->GetSizeWindowWidth()),
		static_cast<fx32>(_application->GetWindow()->GetSizeWindowHeight())));
}

//=============================================================================
// 描画
void ScreenUnit::Draw()
{

	// 描画する情報を押し込む：１度の描画に１度しか呼ばないこと
	S_GetCommandBuffer()->PushRenderState(RENDER_STATE_2D,GetID());
	S_GetCommandBuffer()->PushShader(_shader, GetID());
	S_GetCommandBuffer()->PushMesh(_mesh, GetID());
}