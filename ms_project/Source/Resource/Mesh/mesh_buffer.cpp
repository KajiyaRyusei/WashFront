//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// メッシュバッファ
// 
// Created by Ryusei Kajiya on 20151008
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "mesh_buffer.h"
#include "Renderer/directx9.h"

#include "index_buffer.h"
#include "vertex_buffer.h"

//=============================================================================
// コンストラクタ
MeshBuffer::MeshBuffer(RendererDevice* renderer_device) :
	_device(renderer_device->GetDevice()),
	_is_dead(false),
	_index_buffer(new IndexBuffer(renderer_device)),
	_vertex_buffer(new VertexBuffer(renderer_device))
{}

//=============================================================================
// デストラクタ
MeshBuffer::~MeshBuffer()
{
	SafeDelete(_index_buffer);
	SafeDelete(_vertex_buffer);
}

//=============================================================================
// 描画
void MeshBuffer::Draw(u16 index_buffer_index) const
{
	if( _vertex_buffer->_primitive_count[index_buffer_index] <= 0 )
	{
		OutputDebugStringA("=========================================================\n");
		OutputDebugStringA("ポリゴンの大きさがないよ\n");
		OutputDebugStringA("=========================================================\n");
		return;
	}

	if( _index_buffer->_index_buffers != nullptr )
	{
		_device->DrawIndexedPrimitive(_vertex_buffer->_primitive_type, 0, 0, _vertex_buffer->_vertex_count[0], 0, _vertex_buffer->_primitive_count[index_buffer_index]);
	}
	else
	{
		_device->DrawPrimitive(_vertex_buffer->_primitive_type, 0, _vertex_buffer->_primitive_count[index_buffer_index]);
	}

	if( _vertex_buffer->_vertex_count[1] > 0 )
	{// インスタシングの場合戻す
		_device->SetStreamSourceFreq(0, 1);
		_device->SetStreamSourceFreq(1, 1);
	}
}


//=============================================================================
// index関連
bool MeshBuffer::RegisterIndexCount(u16 index_buffer_count)
{
	return _index_buffer->RegisterIndexCount(index_buffer_count);
}
bool MeshBuffer::RegisterIndexInformation(u16 index_buffer_index, u32 index_count)
{
	return _index_buffer->RegisterIndexInformation(index_buffer_index, index_count);
}
bool MeshBuffer::CreateIndexBuffer(u32 usage, D3DFORMAT format)
{
	return _index_buffer->CreateIndexBuffer(usage, format);
}
void MeshBuffer::BindIndexBuffer(u16 index_buffer_index) const
{
	_index_buffer->BindIndexBuffer(index_buffer_index);
}
LPDIRECT3DINDEXBUFFER9 MeshBuffer::GetIndexBuffer(u16 index_buffer_index) const
{
	return _index_buffer->GetIndexBuffer(index_buffer_index);
}

//=============================================================================
// vertex関連
bool MeshBuffer::CreateVertexBuffer(u32 usage, D3DPOOL pool)
{
	return _vertex_buffer->CreateVertexBuffer(usage,pool);
}
bool MeshBuffer::RegisterVertexCount(u16 vertex_buffer_index, u32 count)
{
	return _vertex_buffer->RegisterVertexCount(vertex_buffer_index, count);
}
bool MeshBuffer::RegisterVertexInformation(u16 stream_index, D3DDECLTYPE data_type, D3DDECLMETHOD processing_method, D3DDECLUSAGE semantics, u8 semantic_index)
{
	return _vertex_buffer->RegisterVertexInformation(stream_index, data_type, processing_method, semantics, semantic_index);
}
void MeshBuffer::RegisterPrimitiveCount(u16 primitive_count)
{
	_vertex_buffer->RegisterPrimitiveCount(primitive_count);
}
void MeshBuffer::SetPrimitiveType(D3DPRIMITIVETYPE primitive_type)
{
	_vertex_buffer->SetPrimitiveType(primitive_type);
}
void MeshBuffer::SetPrimitiveCount(u16 primitive_index, u32 primitive_count)
{
	_vertex_buffer->SetPrimitiveCount(primitive_index, primitive_count);
}
void MeshBuffer::SetVertexCount(u16 vertex_buffer_index, u32 vertex_count)
{
	_vertex_buffer->SetVertexCount(vertex_buffer_index, vertex_count);
}
void MeshBuffer::BindVertexBuffer(void) const
{
	_vertex_buffer->BindVertexBuffer();
}
LPDIRECT3DVERTEXBUFFER9 MeshBuffer::GetVertexBuffer(u16 vertex_buffer_index) const
{
	return _vertex_buffer->_vertex_buffers[vertex_buffer_index];
}
u32 MeshBuffer::GetPrimitiveCount(u16 primitive_index)
{
	return _vertex_buffer->_primitive_count[primitive_index];
}
u32 MeshBuffer::GetVertexCount(u16 primitive_index)
{
	return _vertex_buffer->_vertex_count[primitive_index];
}
u16 MeshBuffer::GetVertexSize(u16 primitive_index)
{
	return _vertex_buffer->_vertex_size[primitive_index];
}