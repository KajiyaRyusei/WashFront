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

#include "Renderer/directx9.h"
#include "System/application.h"


#include "Shader/Shader/screen_shader.h"
#include "Shader/Shader/screen_2d_shader.h"

#include "Resource/Mesh/Mesh/mesh_factory_2d_sprite.h"

#include "Windows/window.h"

//=============================================================================
// 初期化
void ScreenUnit::Initialize()
{
	// シェーダの作成
	_shader = new Shader2D();

	// 頂点バッファの作成
	MeshFactory2DSprite sprite_factory;
	_mesh = sprite_factory.Create(_application->GetRendererDevice());

	D3DXVECTOR4 ambient(1.f,1.f,1.f,1.f);
	_shader->SetAmbientColor(ambient);

	_visible = true;
}

//=============================================================================
// 終
void ScreenUnit::Finalize()
{
	SafeDelete(_shader);
	SafeDelete(_mesh);
	SafeRelease(_texture);
}

//=============================================================================
// 更新
void ScreenUnit::Update()
{
	D3DXMATRIX matrix_screen, matrix_rotation, matrix_scale, matrix_translation;
	D3DXMatrixIdentity(&matrix_screen);

	//場所を整える
	D3DXVECTOR3 pos = _position;
	pos *= 2;

	//行列作成
	D3DXMatrixScaling(&matrix_scale, _scaling.x, _scaling.y, _scaling.z);
	D3DXMatrixRotationZ(&matrix_rotation, _rotation);
	D3DXMatrixTranslation(&matrix_translation, pos.x, pos.y, pos.z);


	matrix_screen = matrix_rotation * matrix_scale * matrix_translation;

	//行列を送る
	_shader->SetScreenMatrix(matrix_screen);


	//テクスチャ関連の値を送る
	_shader->SetScreenTextureUv(D3DXVECTOR2(static_cast<fx32>(_texture_uv.x), static_cast<fx32>(_texture_uv.y)));
	_shader->SetScreenTextureOffset(D3DXVECTOR2(static_cast<fx32>(_texture_offset.x), static_cast<fx32>(_texture_offset.y)));
	_shader->SetScreenTextureAlpha(_texture_alpha);

	//スクリーンサイズを送る
	_shader->SetScreenSize(D3DXVECTOR2(
		static_cast<fx32>(_application->GetWindow()->GetSizeWindowWidth()),
		static_cast<fx32>(_application->GetWindow()->GetSizeWindowHeight())));
}

//=============================================================================
// 描画
void ScreenUnit::Draw()
{
	if( _visible == true )
	{
		// 描画する情報を押し込む：１度の描画に１度しか呼ばないこと
		S_GetCommandBuffer()->PushRenderState(RENDER_STATE_2D, GetID());
		S_GetCommandBuffer()->PushShader(_shader, GetID());
		S_GetCommandBuffer()->PushMesh(_mesh, GetID());
	}
}

//=============================================================================
// テクスチャ作成
void ScreenUnit::CreateTexture(LPCWSTR texture_filename)
{
	//デバイス
	LPDIRECT3DDEVICE9 device = _application->GetRendererDevice()->GetDevice();

	//テクスチャ作成
	D3DXCreateTextureFromFile(device, texture_filename, &_texture);

	//テクスチャ登録
	_shader->SetAlbedoTexture(_texture);

}

//=============================================================================
// 色を選択
void ScreenUnit::SelectColor(const D3DXVECTOR4& color)
{
	_shader->SetAmbientColor(color);
}