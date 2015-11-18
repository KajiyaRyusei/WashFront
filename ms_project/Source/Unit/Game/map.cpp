//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// マップ
// 
// Created by Chiharu Kamiyama on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "map.h"

#include "Renderer/directx9.h"
#include "System/application.h"


#include "Shader/Shader/screen_shader.h"
#include "Shader/Shader/screen_2d_shader.h"


#include "Resource/Mesh/Mesh/mesh_factory_2d_sprite.h"

#include "Windows/window.h"

//定数
static const D3DXVECTOR3 position = D3DXVECTOR3(300.0f, 300.0f, 0.0f);
static const D3DXVECTOR3 scaling = D3DXVECTOR3(300.0f, 300.0f, 1.0f);

//=============================================================================
// 初期化
void Map::Initialize()
{
	CreateTexture(TEXT("Data/Texture/bild_effect.png"));
	_texture_uv = D3DXVECTOR2(0.2f, 1.0f);
	_texture_offset = D3DXVECTOR2(0.0f, 1.0f);
	_texture_alpha = 1.0f;

	_position = position;
	_rotation = 0.0f;
	_scaling = scaling;
}

//=============================================================================
// 終了
void Map::Finalize()
{

}

//=============================================================================
// 更新
void Map::Update()
{

	_texture_offset.x += 0.005f;

	if (_texture_offset.x == 1.2f)
	{
		_texture_offset.x = 0.2f;
	}
	
	ScreenUnit::Update();


/*	if (_alpha_flag)
	{
		_texture_alpha -= 0.1f;

		if (_texture_alpha < 0.0f)
		{
			_texture_alpha = 0.0f;
			_alpha_flag = false;
		}
	}
	else
	{
		_texture_alpha += 0.1f;

		if (_texture_alpha > 1.0f)
		{
			_texture_alpha = 1.0f;
			_alpha_flag = true;
		}

	}

	_shader->SetScreenTextureUv(D3DXVECTOR2(static_cast<fx32>(_texture_uv.x), static_cast<fx32>(_texture_uv.y)));
	_shader->SetScreenTextureOffset(D3DXVECTOR2(static_cast<fx32>(_texture_offset.x), static_cast<fx32>(_texture_offset.y)));
	_shader->SetScreenTextureAlpha(_texture_alpha);

	_shader->SetScreenSize(D3DXVECTOR2(
		static_cast<fx32>(_application->GetWindow()->GetSizeWindowWidth()),
		static_cast<fx32>(_application->GetWindow()->GetSizeWindowHeight())));
*/
}

//=============================================================================
// 描画
void Map::Draw()
{
	ScreenUnit::Draw();

}