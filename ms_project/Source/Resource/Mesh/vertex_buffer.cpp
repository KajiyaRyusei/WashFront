//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 頂点バッファ
// 
// Created by Ryusei Kajiya on 20151007
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "vertex_buffer.h"
#include "Renderer/directx9.h"

//*****************************************************************************
// 定数
namespace
{
	// データタイプからビット数への変換表
	const u8 kDataTypeToBitTable[] = 
	{
		8 * sizeof(float),		// D3DDECLTYPE_FLOAT1    =  0,	// 1D float expanded to (value, 0., 0., 1.)
		8 * sizeof(float)* 2,	// D3DDECLTYPE_FLOAT2    =  1,	// 2D float expanded to (value, value, 0., 1.)
		8 * sizeof(float)* 3,	// D3DDECLTYPE_FLOAT3    =  2,	// 3D float expanded to (value, value, value, 1.)
		8 * sizeof(float)* 4,	// D3DDECLTYPE_FLOAT4    =  3,	// 4D float
		8 * sizeof(D3DCOLOR),	// D3DDECLTYPE_D3DCOLOR  =  4,	// 4D packed unsigned bytes mapped to 0. to 1. range

		// Input is in D3DCOLOR format (ARGB) expanded to (R, G, B, A)
		8 * sizeof(u8)* 4,		// D3DDECLTYPE_Uu84    =  5,	// 4D unsigned byte
		8 * sizeof(short)* 2,	// D3DDECLTYPE_SHORT2    =  6,	// 2D signed short expanded to (value, value, 0., 1.)
		8 * sizeof(short)* 4,	// D3DDECLTYPE_SHORT4    =  7,	// 4D signed short

		// The following types are valid only with vertex shaders >= 2.0
		8 * sizeof(u8)* 4,		// D3DDECLTYPE_Uu84N   =  8,	// Each of 4 bytes is normalized by dividing to 255.0
		8 * sizeof(short)* 2,	// D3DDECLTYPE_SHORT2N   =  9,	// 2D signed short normalized (v[0]/32767.0,v[1]/32767.0,0,1)
		8 * sizeof(short)* 4,	// D3DDECLTYPE_SHORT4N   = 10,	// 4D signed short normalized (v[0]/32767.0,v[1]/32767.0,v[2]/32767.0,v[3]/32767.0)
		8 * sizeof(WORD)* 2,	// D3DDECLTYPE_USHORT2N  = 11,	// 2D unsigned short normalized (v[0]/65535.0,v[1]/65535.0,0,1)
		8 * sizeof(WORD)* 4,	// D3DDECLTYPE_USHORT4N  = 12,	// 4D unsigned short normalized (v[0]/65535.0,v[1]/65535.0,v[2]/65535.0,v[3]/65535.0)
		10 * 3,					// D3DDECLTYPE_UDEC3     = 13,	// 3D unsigned 10 10 10 format expanded to (value, value, value, 1)
		10 * 3,					// D3DDECLTYPE_DEC3N     = 14,	// 3D signed 10 10 10 format normalized and expanded to (v[0]/511.0, v[1]/511.0, v[2]/511.0, 1)
		16 * 2,					// D3DDECLTYPE_FLOAT16_2 = 15,	// Two 16-bit floating point values, expanded to (value, value, 0, 1)
		16 * 4,					// D3DDECLTYPE_FLOAT16_4 = 16,	// Four 16-bit floating point values
		0,						// D3DDECLTYPE_UNUSED    = 17,	// When the type field in a decl is unused.
	};

	// D3DDECL_END()
	const D3DVERTEXELEMENT9 kElementTerminate = D3DDECL_END();
};

//=============================================================================
// コンストラクタ
VertexBuffer::VertexBuffer(RendererDevice* renderer_device) :
	_device(renderer_device->GetDevice()),
	_vertex_buffers(nullptr),
	_declaration(nullptr),
	_primitive_type(D3DPT_TRIANGLESTRIP),
	_element_count(0),
	_vertex_count(nullptr),
	_vertex_size(nullptr),
	_primitive_count(nullptr)
{
	if( renderer_device->GetDevice() == nullptr)
	{
		OutputDebugStringA("=========================================================\n");
		OutputDebugStringA("デバイスの存在を認識できませんでした\n");
		OutputDebugStringA("=========================================================\n");
		return;
	}

	_vertex_element[0] = kElementTerminate;
	_vertex_buffers = new LPDIRECT3DVERTEXBUFFER9[kMaxVertexBuffer];
	_vertex_count = new u32[kMaxVertexBuffer];
	_vertex_size = new u16[kMaxVertexBuffer];

	for( u32 i = 0; i < kMaxVertexBuffer; ++i )
	{
		_vertex_buffers[i] = nullptr;
		_vertex_count[i] = 0;
		_vertex_size[i] = 0;
	}
}

//=============================================================================
// デストラクタ
VertexBuffer::~VertexBuffer()
{
	ReleaseBuffers();
	SafeDeleteArray(_vertex_buffers);
	SafeDeleteArray(_vertex_count);
	SafeDeleteArray(_vertex_size);
	SafeDeleteArray(_primitive_count);
}

//=============================================================================
// 登録された頂点データをもとに頂点バッファ群を作成する。
bool VertexBuffer::CreateVertexBuffer(u32 usage, D3DPOOL pool)
{
	if( _vertex_count[0] == 0)
	{
		OutputDebugStringA("=========================================================\n");
		OutputDebugStringA("頂点数未登録です。\n");
		OutputDebugStringA("=========================================================\n");
		return false;
	}

	if( _element_count == 0)
	{
		OutputDebugStringA("=========================================================\n");
		OutputDebugStringA("頂点情報未登録です。\n");
		OutputDebugStringA("=========================================================\n");
		return false;
	}

	HRESULT handle_result = _device->CreateVertexDeclaration(
		_vertex_element,
		&_declaration);

	if( FAILED(handle_result))
	{
		OutputDebugStringA("=========================================================\n");
		OutputDebugStringA("頂点宣言作成失敗\n");
		OutputDebugStringA("=========================================================\n");
		return false;
	}

	for( u32 i = 0; i < kMaxVertexBuffer; ++i )
	{
		if( _vertex_count[i] == 0)
		{// 頂点数未登録ならその時点で終了
			break;
		}
		handle_result = _device->CreateVertexBuffer(
			_vertex_size[i] * _vertex_count[i],
			usage,
			0,
			pool,
			&_vertex_buffers[i],
			nullptr);

		if( FAILED(handle_result) )
		{
			OutputDebugStringA("=========================================================\n");
			OutputDebugStringA("vertex_buffer作成失敗\n");
			OutputDebugStringA("=========================================================\n");
			ReleaseBuffers();
			return false;
		}
	}

	return true;
}

//=============================================================================
// 頂点数の登録
bool VertexBuffer::RegisterVertexCount(u16 vertex_buffer_index, u32 count)
{
	if( _vertex_count[vertex_buffer_index] != 0)
	{
		OutputDebugStringA("=========================================================\n");
		OutputDebugStringA("頂点数の値が未初期化だよ\n");
		OutputDebugStringA("=========================================================\n");
		return false;
	}
	
	_vertex_count[vertex_buffer_index] = count;

	return true;
}

//=============================================================================
// 頂点情報の登録
bool VertexBuffer::RegisterVertexInformation(
	u16 stream_index,
	D3DDECLTYPE data_type,
	D3DDECLMETHOD processing_method,
	D3DDECLUSAGE semantics,
	u8 semantic_index)
{
	if( _element_count >= kMaxElement)
	{
		OutputDebugStringA("=========================================================\n");
		OutputDebugStringA("エレメント数超えてるよ\n");
		OutputDebugStringA("=========================================================\n");
		return false;
	}

	if( stream_index >= kMaxVertexBuffer )
	{
		OutputDebugStringA("=========================================================\n");
		OutputDebugStringA("ストリーム数超えてるよ\n");
		OutputDebugStringA("=========================================================\n");
		return false;
	}

	_vertex_element[_element_count].Stream = stream_index;
	_vertex_element[_element_count].Offset = _vertex_size[stream_index];
	_vertex_element[_element_count].Type = static_cast<BYTE>(data_type);
	_vertex_element[_element_count].Method = static_cast<BYTE>(processing_method);
	_vertex_element[_element_count].Usage = static_cast<BYTE>(semantics);
	_vertex_element[_element_count].UsageIndex = static_cast<BYTE>(semantic_index);

	// D3DDECL_ENDの設定
	_vertex_element[++_element_count] = kElementTerminate;

	// オフセットの加算
	_vertex_size[stream_index] += static_cast<u16>(kDataTypeToBitTable[data_type] * 0.125f);

	return true;
}

//=============================================================================
// 頂点バッファをバインド
void VertexBuffer::BindVertexBuffer(void) const
{
	_device->SetVertexDeclaration(_declaration);

	if( _vertex_count[1] > 0)
	{// ストリームカウントからインスタシング判定
		_device->SetStreamSourceFreq(0,D3DSTREAMSOURCE_INDEXEDDATA | _vertex_count[1]);
		_device->SetStreamSourceFreq(1, static_cast<UINT>(D3DSTREAMSOURCE_INSTANCEDATA | 1));
		_device->SetStreamSource(0, _vertex_buffers[0], 0, _vertex_size[0]);
		_device->SetStreamSource(0, _vertex_buffers[1], 0, _vertex_size[1]);
	}
	else
	{
		_device->SetStreamSource(0, _vertex_buffers[0], 0, _vertex_size[0]);
	}
}


