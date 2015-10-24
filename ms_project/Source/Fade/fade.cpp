//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// フェード
//
// Created by Ryusei Kajiya on 20151013
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// インクルード
#include "fade.h"
#include "System/application.h"
#include "Shader/PostEffect/fade_shader.h"
#include "Resource/Mesh/Mesh/mesh_factory_sprite.h"

#include "Windows/window.h"

//*****************************************************************************
// 定数
namespace
{
	// fadeの速度
	static const float kFadingVelocity = 0.02f;
}

//=============================================================================
// コンストラクタ
Fade::Fade(Application *application) :
	_shader{ nullptr },
	_mesh{ nullptr },
	_application{ application },
	_fade_color(1.f, 1.f, 1.f, 1.f),
	_is_fade_in{ false },
	_is_fade_out{ true },
	_is_fade_now{ true }
{
	Initialize(application);
}

//=============================================================================
// 初期化
void Fade::Initialize(Application *application)
{
	// シェーダの作成
	_shader = new ShaderFade();

	// 頂点バッファの作成
	MeshFactorySprite sprite_factory;
	_mesh = sprite_factory.Create(application->GetRendererDevice());
}
//=============================================================================
// 終了
void Fade::Finalize()
{
	SafeDelete(_shader);
	SafeDelete(_mesh);
}
//=============================================================================
// 更新
void Fade::Update()
{
	Fading();

	D3DXMATRIX matrix_screen, matrix_scale, matrix_translation;
	D3DXMatrixIdentity(&matrix_screen);

	D3DXMatrixScaling(&matrix_scale, 
		static_cast<fx32>(_application->GetWindow()->GetSizeWindowWidth()),
		static_cast<fx32>(_application->GetWindow()->GetSizeWindowHeight()),
		1.f);

	D3DXMatrixTranslation(&matrix_translation, 
		static_cast<fx32>(_application->GetWindow()->GetSizeWindowWidth()),
		static_cast<fx32>(_application->GetWindow()->GetSizeWindowHeight()),
		0.f);

	matrix_screen = matrix_scale * matrix_translation;

	_shader->SetScreenMatrix(matrix_screen);

	_shader->SetScreenSize(D3DXVECTOR2(
		static_cast<fx32>(_application->GetWindow()->GetSizeWindowWidth()),
		static_cast<fx32>(_application->GetWindow()->GetSizeWindowHeight())));

	_shader->SetAmbientColor(_fade_color);
}
//=============================================================================
// 描画
void Fade::Draw()
{
	_shader->Begin(0);
	_shader->AssignExceptMaterial();
	_shader->BeginPass(0);
	_shader->CommitChanges();

	// 描画
	_mesh->BindVertexBuffer();
	_mesh->BindIndexBuffer(0);
	_mesh->Draw(0);

	_shader->EndPass();
	_shader->End();
}

//=============================================================================
// フェードの更新
void Fade::Fading()
{
	if( _is_fade_in )
	{
		_fade_color.w += kFadingVelocity;

		if( _fade_color.w  >= 1.f)
		{
			_is_fade_in = false;
			_is_fade_out = true;
		}
	}
	else
	{
		if( _is_fade_out )
		{
			_fade_color.w -= kFadingVelocity;
		}

		if( _fade_color.w  <= 0.f )
		{
			_is_fade_out = false;
			_is_fade_now = false;
		}
	}
}

//=============================================================================
// フェードイン
void Fade::FadeIn()
{
	_fade_color = D3DXVECTOR4(1.f, 1.f, 1.f, 0.f);
	_is_fade_in = true;
	_is_fade_now = true;
}

//=============================================================================
// フェードアウト
void Fade::FadeOut()
{
	_fade_color = D3DXVECTOR4(1.f, 1.f, 1.f, 1.f);
	_is_fade_out = true;
	_is_fade_now = true;
}
