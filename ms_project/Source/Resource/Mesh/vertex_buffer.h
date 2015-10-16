//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 頂点バッファ
// 
// Created by Ryusei Kajiya on 20151007
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// 前方宣言
class RendererDevice;

//*****************************************************************************
// クラス設計
class VertexBuffer
{
	friend class MeshBuffer;

public:

	explicit VertexBuffer(RendererDevice* renderer_device);
	virtual ~VertexBuffer();


	// 登録された頂点データをもとに頂点バッファ群を作成する。
	bool CreateVertexBuffer(u32 usage, D3DPOOL pool);

	// 頂点数の登録
	// 頂点バッファ作成命令に前に登録
	bool RegisterVertexCount(u16 vertex_buffer_index, u32 count);

	// 頂点情報の登録
	// 頂点バッファ作成命令の前に登録
	bool RegisterVertexInformation(
		u16 stream_index,
		D3DDECLTYPE data_type,
		D3DDECLMETHOD processing_method,
		D3DDECLUSAGE semantics,
		u8 semantic_index);

	// パーツアニメーション用に異なるモデルの個数を登録する。
	// 通常時も1を入力してください。
	void RegisterPrimitiveCount(u16 primitive_count )
	{
		_primitive_count = new u32[primitive_count];
	}

	// プリミティブのタイプを設定
	void SetPrimitiveType(D3DPRIMITIVETYPE primitive_type)
	{
		_primitive_type = primitive_type;
	}

	// プリミティブの数を登録
	void SetPrimitiveCount(u16 primitive_index,u32 primitive_count)
	{
		_primitive_count[primitive_index] = primitive_count;
	}

	// 頂点数を登録
	void SetVertexCount(u16 vertex_buffer_index, u32 vertex_count)
	{
		_vertex_count[vertex_buffer_index] = vertex_count;
	}

	// 描画デバイスへ設定
	// 描画直前に呼び出してください
	void BindVertexBuffer(void) const;

	// 頂点バッファ先頭アドレスを取得
	virtual  LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer(u16 vertex_buffer_index) const
	{
		return _vertex_buffers[vertex_buffer_index];
	}

	// プリミティブ数取得
	u32 GetPrimitiveCount(u16 primitive_index)
	{
		return _primitive_count[primitive_index];
	}

	// 解放
	void ReleaseBuffers()
	{
		for( u32 i = 0; i < kMaxVertexBuffer; ++i )
		{
			SafeRelease(_vertex_buffers[i]);
		}
	}

private:

	static const u8 kMaxElement = 64;
	static const u32 kMaxVertexBuffer = 2;

	LPDIRECT3DDEVICE9 _device;
	D3DVERTEXELEMENT9 _vertex_element[kMaxElement + 1];
	LPDIRECT3DVERTEXBUFFER9* _vertex_buffers;
	LPDIRECT3DVERTEXDECLARATION9 _declaration;
	D3DPRIMITIVETYPE _primitive_type;

	u32 _element_count;
	u32* _vertex_count;
	u16* _vertex_size;
	u32* _primitive_count;

};