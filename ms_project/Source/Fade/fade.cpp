//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �t�F�[�h
//
// Created by Ryusei Kajiya on 20151013
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// �C���N���[�h
#include "fade.h"
#include "System/application.h"
#include "Shader/PostEffect/fade_shader.h"
#include "Resource/Mesh/Mesh/mesh_factory_sprite.h"
#include "Resource/Mesh/Mesh/mesh_factory_circle.h"
#include "Renderer/directx9.h"

#include "Windows/window.h"

//*****************************************************************************
// �萔
namespace
{
	// fade�̑��x
	static const float kFadingVelocity = 0.02f;
}

//=============================================================================
// �R���X�g���N�^
Fade::Fade(Application *application) :
	_shader{ nullptr },
	_mesh{ nullptr },
	_application{ application },
	_fade_color(0.f, 0.f, 0.f, 1.f),
	_is_fade_in{ false },
	_is_fade_out{ true },
	_is_fade_now{ true }
{
	Initialize(application);
}

//=============================================================================
// ������
void Fade::Initialize(Application *application)
{
	// �V�F�[�_�̍쐬
	_shader = new ShaderFade();

	// ���_�o�b�t�@�̍쐬
	MeshFactorySprite sprite_factory;
	_mesh = sprite_factory.Create(application->GetRendererDevice());

	D3DXCreateTextureFromFileA(
		application->GetRendererDevice()->GetDevice(), 
		"Data/Texture/ojiichan_icon.png",
		&_texture);

	_shader->SetAlbedoTexture(_texture);
}
//=============================================================================
// �I��
void Fade::Finalize()
{
	SafeDelete(_shader);
	SafeDelete(_mesh);
	SafeRelease(_texture);
}
//=============================================================================
// �X�V
void Fade::Update()
{
	Fading();

	D3DXMATRIX matrix_screen, matrix_scale, matrix_translation, matrix_rotation;
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

	D3DXMATRIX matrix_texcoord;

	D3DXMatrixTranslation(&matrix_translation, -0.5f,-0.5f, 0.f);
	//D3DXMatrixTranslation(&matrix_translation, -0.5f, -0.5f, 0.f);
	matrix_texcoord = matrix_translation;

	D3DXMatrixScaling(&matrix_scale,
		(_fade_color.w) * 7.0f * -1.f,
		(_fade_color.w) * 7.0f * -1.f,
		1.f);

	matrix_texcoord *= matrix_scale;

	D3DXMatrixTranslation(&matrix_translation,0.5f,0.5f,0.f);

	matrix_texcoord *= matrix_translation;

	_shader->SetTexcoordMatrix(matrix_texcoord);

}
//=============================================================================
// �`��
void Fade::Draw()
{
	if( _is_fade_now )
	{
		_shader->Begin(0);
		_shader->AssignExceptMaterial();
		_shader->BeginPass(0);
		_shader->CommitChanges();

		// �`��
		_mesh->BindVertexBuffer();
		_mesh->BindIndexBuffer(0);
		_mesh->Draw(0);

		_shader->EndPass();
		_shader->End();
	}
	
}

//=============================================================================
// �t�F�[�h�̍X�V
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
// �t�F�[�h�C��
void Fade::FadeIn()
{
	_fade_color = D3DXVECTOR4(0.f, 0.f, 0.f, 0.f);
	_is_fade_in = true;
	_is_fade_now = true;
}

//=============================================================================
// �t�F�[�h�A�E�g
void Fade::FadeOut()
{
	_fade_color = D3DXVECTOR4(0.f, 0.f, 0.f, 1.f);
	_is_fade_out = true;
	_is_fade_now = true;
}
