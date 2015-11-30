//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �C���f�b�N�X�o�b�t�@
// 
// Created by Ryusei Kajiya on 20151007
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "index_buffer.h"
#include "Renderer/directx9.h"


//=============================================================================
// �R���X�g���N�^
IndexBuffer::IndexBuffer(RendererDevice* renderer_device) :
	_device(renderer_device->GetDevice()),
	_index_buffers(nullptr),
	_index_buffer_count(0),
	_index_count(nullptr)
{
	if( renderer_device->GetDevice() == nullptr )
	{
		OutputDebugStringA("=========================================================\n");
		OutputDebugStringA("�f�o�C�X�̑��݂�F���ł��܂���ł���\n");
		OutputDebugStringA("=========================================================\n");
		return;
	}
}

//=============================================================================
// �f�X�g���N�^
IndexBuffer::~IndexBuffer()
{
	ReleaseBuffers();
	SafeDeleteArray(_index_buffers);
	SafeDeleteArray(_index_count);
}

//=============================================================================
// �o�^���ꂽ�C���f�b�N�X�f�[�^�������ƂɃC���f�b�N�X�o�b�t�@�Q���쐬����B
bool IndexBuffer::CreateIndexBuffer(u32 usage, D3DFORMAT format)
{
	_index_buffers = new LPDIRECT3DINDEXBUFFER9[_index_buffer_count];

	for( u32 i = 0; i < _index_buffer_count; ++i )
	{
		const s32 length = (format == D3DFMT_INDEX16 ? sizeof(u16) : sizeof(u32)) * _index_count[i];

		const HRESULT handle_result = _device->CreateIndexBuffer(
			length,
			usage,
			format,
			D3DPOOL_MANAGED,
			&_index_buffers[i],
			nullptr);

		if( FAILED(handle_result) )
		{
			OutputDebugStringA("=========================================================\n");
			OutputDebugStringA("indexbuffer�̍쐬�Ɏ��s\n");
			OutputDebugStringA("=========================================================\n");
			return false;
		}
	}

	return true;
}

//=============================================================================
// �C���f�b�N�X�o�b�t�@���o�C���h
void IndexBuffer::BindIndexBuffer(u16 index_buffer_index) const
{
	if( _index_buffers != nullptr )
	{
		_device->SetIndices(_index_buffers[index_buffer_index]);
	}
}