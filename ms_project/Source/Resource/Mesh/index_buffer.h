//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// インデックスバッファ
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
class IndexBuffer
{
	friend class MeshBuffer;
public:
	explicit IndexBuffer(RendererDevice* renderer_device);
	virtual ~IndexBuffer();

	// インデックスカウントの登録
	// インデックスバッファ作成命令の前に登録
	bool RegisterIndexCount(u16 index_buffer_count)
	{
		_index_buffer_count = index_buffer_count;
		_index_count = new u32[index_buffer_count];
		return true;
	}

	// インデックス情報の登録
	// インデックスバッファ作成命令の前に登録
	// RegisterIndexCountの後に呼ぶ
	bool RegisterIndexInformation(u16 index_buffer_index, u32 index_count)
	{
		_index_count[index_buffer_index] = index_count;
		return true;
	}

	// 登録されたインデックスデータ情報をもとにインデックスバッファ群を作成する。
	// この関数の前にRegisterIndexCountとRegisterIndexInformationで登録しておく
	bool CreateIndexBuffer(u32 usage, D3DFORMAT format);

	void BindIndexBuffer(u16 index_buffer_index) const;

	// インデックスバッファ先頭アドレスを取得
	virtual LPDIRECT3DINDEXBUFFER9 GetIndexBuffer(u16 index_buffer_index) const
	{
		return _index_buffers[index_buffer_index];
	}

	// 解放
	void ReleaseBuffers()
	{
		for( u32 i = 0; i < _index_buffer_count; ++i )
		{
			SafeRelease(_index_buffers[i]);
		}
	}

private:

	LPDIRECT3DDEVICE9 _device;
	LPDIRECT3DINDEXBUFFER9* _index_buffers;
	u16 _index_buffer_count;
	u32* _index_count;
};