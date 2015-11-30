//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���b�V���o�b�t�@
// 
// Created by Ryusei Kajiya on 20151008
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �O���錾
class IndexBuffer;
class VertexBuffer;
class RendererDevice;

//*****************************************************************************
// �N���X�݌v
class MeshBuffer
{
public:

	explicit MeshBuffer(RendererDevice* renderer_device);
	virtual ~MeshBuffer();

	// ����ł��邩�ǂ���
	virtual bool IsDead() const { return _is_dead; }

	// ���g���E��
	virtual void KillMySelf(){ _is_dead = true; }

	// �`��
	void Draw(u16 index_buffer_index) const;

	// index�֘A
	bool RegisterIndexCount(u16 index_buffer_count);
	bool RegisterIndexInformation(u16 index_buffer_index, u32 index_count);
	bool CreateIndexBuffer(u32 usage, D3DFORMAT format);
	void BindIndexBuffer(u16 index_buffer_index) const;
	virtual LPDIRECT3DINDEXBUFFER9 GetIndexBuffer(u16 index_buffer_index) const;

	// vertex�֘A
	bool CreateVertexBuffer(u32 usage, D3DPOOL pool);
	bool RegisterVertexCount(u16 vertex_buffer_index, u32 count);
	bool RegisterVertexInformation(u16 stream_index,D3DDECLTYPE data_type,D3DDECLMETHOD processing_method,D3DDECLUSAGE semantics,u8 semantic_index);
	void RegisterPrimitiveCount(u16 primitive_count = 1);
	void SetPrimitiveType(D3DPRIMITIVETYPE primitive_type);
	void SetPrimitiveCount(u16 primitive_index, u32 primitive_count);
	void SetVertexCount(u16 vertex_buffer_index, u32 vertex_count);
	void BindVertexBuffer(void) const;
	virtual  LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer(u16 vertex_buffer_index) const;
	u32 GetPrimitiveCount(u16 primitive_index);
	u32 GetVertexCount(u16 primitive_index);
	u16 GetVertexSize(u16 primitive_index);

private:

	LPDIRECT3DDEVICE9 _device;
	bool _is_dead;
	IndexBuffer* _index_buffer;
	VertexBuffer* _vertex_buffer;
};