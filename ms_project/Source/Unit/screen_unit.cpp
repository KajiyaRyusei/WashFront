//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �e�X�g�X�N���[���p���j�b�g
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
// ������
void ScreenUnit::Initialize()
{
	// �V�F�[�_�̍쐬
	_shader = new Shader2D();

	// ���_�o�b�t�@�̍쐬
	MeshFactory2DSprite sprite_factory;
	_mesh = sprite_factory.Create(_application->GetRendererDevice());

	D3DXVECTOR4 ambient(1.f,1.f,1.f,1.f);
	_shader->SetAmbientColor(ambient);

	_visible = true;
}

//=============================================================================
// �I
void ScreenUnit::Finalize()
{
	SafeDelete(_shader);
	SafeDelete(_mesh);
	SafeRelease(_texture);
}

//=============================================================================
// �X�V
void ScreenUnit::Update()
{
	D3DXMATRIX matrix_screen, matrix_rotation, matrix_scale, matrix_translation;
	D3DXMatrixIdentity(&matrix_screen);

	//�ꏊ�𐮂���
	D3DXVECTOR3 pos = _position;
	pos *= 2;

	//�s��쐬
	D3DXMatrixScaling(&matrix_scale, _scaling.x, _scaling.y, _scaling.z);
	D3DXMatrixRotationZ(&matrix_rotation, _rotation);
	D3DXMatrixTranslation(&matrix_translation, pos.x, pos.y, pos.z);


	matrix_screen = matrix_rotation * matrix_scale * matrix_translation;

	//�s��𑗂�
	_shader->SetScreenMatrix(matrix_screen);


	//�e�N�X�`���֘A�̒l�𑗂�
	_shader->SetScreenTextureUv(D3DXVECTOR2(static_cast<fx32>(_texture_uv.x), static_cast<fx32>(_texture_uv.y)));
	_shader->SetScreenTextureOffset(D3DXVECTOR2(static_cast<fx32>(_texture_offset.x), static_cast<fx32>(_texture_offset.y)));
	_shader->SetScreenTextureAlpha(_texture_alpha);

	//�X�N���[���T�C�Y�𑗂�
	_shader->SetScreenSize(D3DXVECTOR2(
		static_cast<fx32>(_application->GetWindow()->GetSizeWindowWidth()),
		static_cast<fx32>(_application->GetWindow()->GetSizeWindowHeight())));
}

//=============================================================================
// �`��
void ScreenUnit::Draw()
{
	if( _visible == true )
	{
		// �`�悷������������ށF�P�x�̕`��ɂP�x�����Ă΂Ȃ�����
		S_GetCommandBuffer()->PushRenderState(RENDER_STATE_2D, GetID());
		S_GetCommandBuffer()->PushShader(_shader, GetID());
		S_GetCommandBuffer()->PushMesh(_mesh, GetID());
	}
}

//=============================================================================
// �e�N�X�`���쐬
void ScreenUnit::CreateTexture(LPCWSTR texture_filename)
{
	//�f�o�C�X
	LPDIRECT3DDEVICE9 device = _application->GetRendererDevice()->GetDevice();

	//�e�N�X�`���쐬
	D3DXCreateTextureFromFile(device, texture_filename, &_texture);

	//�e�N�X�`���o�^
	_shader->SetAlbedoTexture(_texture);

}

//=============================================================================
// �F��I��
void ScreenUnit::SelectColor(const D3DXVECTOR4& color)
{
	_shader->SetAmbientColor(color);
}