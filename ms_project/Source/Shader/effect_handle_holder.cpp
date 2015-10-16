//==============================================================================
//
// �G�t�F�N�g�̃n���h�����쐬�������Ă���
//
// Created by Ryusei Kajiya on 20151008
//
//==============================================================================

//******************************************************************************
// include
#include "effect_handle_holder.h"
#include "Renderer/directx9.h"

//==============================================================================
// �R���X�g���N�^
EffectHandleHolder::EffectHandleHolder(const char *effect_file_name, RendererDevice* renderer_device) :
	is_dead_(false)
{
	ID3DXBuffer* error = NULL;

	LPDIRECT3DDEVICE9 device = renderer_device->GetDevice();

	HRESULT handle_result = S_OK;

	handle_result = D3DXCreateEffectFromFileA(
		device,
		effect_file_name,
		nullptr,
		nullptr,
		D3DXSHADER_DEBUG,
		nullptr,
		&_effect_handle,
		&error);

	if( FAILED(handle_result) )
	{
		// �f�o�b�O�p�̕����o��
		OutputDebugStringA((char*)error->GetBufferPointer());
		// ���
		error->Release();
		return;
	}

	ASSERT(SUCCEEDED(handle_result), "�V�F�[�_����܂���ł���");

	SafeRelease(error);

	// �n���h���擾
	_handle_technique = _effect_handle->GetTechniqueByName("Techniques");

	// �Ƃ肠�����e�N�j�b�N�ݒ�
	_effect_handle->SetTechnique(_handle_technique);
}

//==============================================================================
// �f�X�g���N�^
EffectHandleHolder::~EffectHandleHolder()
{
	SafeRelease(_effect_handle);
}

//==============================================================================
// �V�F�[�_�J�n
void EffectHandleHolder::Begin(u32* pass) const
{
	_effect_handle->Begin(reinterpret_cast<u32*>(pass), 0);
}

//==============================================================================
// �V�F�[�_�I��
void EffectHandleHolder::End() const
{
	_effect_handle->End();
}

//==============================================================================
// �V�F�[�_�p�X�J�n
void EffectHandleHolder::BeginPass(u32 pass_number) const
{
	_effect_handle->BeginPass(pass_number);
}

//==============================================================================
// �V�F�[�_�p�X�I��
void EffectHandleHolder::EndPass() const
{
	_effect_handle->EndPass();
}

//==============================================================================
// �l���V�F�[�_�ɃR�~�b�g����
void EffectHandleHolder::CommitChanges() const
{
	_effect_handle->CommitChanges();
}