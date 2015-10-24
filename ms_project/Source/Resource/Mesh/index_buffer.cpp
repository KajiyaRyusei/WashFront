//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// インデックスバッファ
// 
// Created by Ryusei Kajiya on 20151007
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "index_buffer.h"
#include "Renderer/directx9.h"


//=============================================================================
// コンストラクタ
IndexBuffer::IndexBuffer(RendererDevice* renderer_device) :
	_device(renderer_device->GetDevice()),
	_index_buffers(nullptr),
	_index_buffer_count(0),
	_index_count(nullptr)
{
	if( renderer_device->GetDevice() == nullptr )
	{
		OutputDebugStringA("=========================================================\n");
		OutputDebugStringA("デバイスの存在を認識できませんでした\n");
		OutputDebugStringA("=========================================================\n");
		return;
	}
}

//=============================================================================
// デストラクタ
IndexBuffer::~IndexBuffer()
{
	ReleaseBuffers();
	SafeDeleteArray(_index_buffers);
	SafeDeleteArray(_index_count);
}

//=============================================================================
// 登録されたインデックスデータ情報をもとにインデックスバッファ群を作成する。
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
			OutputDebugStringA("indexbufferの作成に失敗\n");
			OutputDebugStringA("=========================================================\n");
			return false;
		}
	}

	return true;
}

//=============================================================================
// インデックスバッファをバインド
void IndexBuffer::BindIndexBuffer(u16 index_buffer_index) const
{
	if( _index_buffers != nullptr )
	{
		_device->SetIndices(_index_buffers[index_buffer_index]);
	}
}