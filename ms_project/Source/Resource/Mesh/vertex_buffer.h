//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���_�o�b�t�@
// 
// Created by Ryusei Kajiya on 20151007
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �O���錾
class RendererDevice;

//*****************************************************************************
// �N���X�݌v
class VertexBuffer
{
	friend class MeshBuffer;

public:

	explicit VertexBuffer(RendererDevice* renderer_device);
	virtual ~VertexBuffer();


	// �o�^���ꂽ���_�f�[�^�����Ƃɒ��_�o�b�t�@�Q���쐬����B
	bool CreateVertexBuffer(u32 usage, D3DPOOL pool);

	// ���_���̓o�^
	// ���_�o�b�t�@�쐬���߂ɑO�ɓo�^
	bool RegisterVertexCount(u16 vertex_buffer_index, u32 count);

	// ���_���̓o�^
	// ���_�o�b�t�@�쐬���߂̑O�ɓo�^
	bool RegisterVertexInformation(
		u16 stream_index,
		D3DDECLTYPE data_type,
		D3DDECLMETHOD processing_method,
		D3DDECLUSAGE semantics,
		u8 semantic_index);

	// �p�[�c�A�j���[�V�����p�ɈقȂ郂�f���̌���o�^����B
	// �ʏ펞��1����͂��Ă��������B
	void RegisterPrimitiveCount(u16 primitive_count )
	{
		_primitive_count = new u32[primitive_count];
	}

	// �v���~�e�B�u�̃^�C�v��ݒ�
	void SetPrimitiveType(D3DPRIMITIVETYPE primitive_type)
	{
		_primitive_type = primitive_type;
	}

	// �v���~�e�B�u�̐���o�^
	void SetPrimitiveCount(u16 primitive_index,u32 primitive_count)
	{
		_primitive_count[primitive_index] = primitive_count;
	}

	// ���_����o�^
	void SetVertexCount(u16 vertex_buffer_index, u32 vertex_count)
	{
		_vertex_count[vertex_buffer_index] = vertex_count;
	}

	// �`��f�o�C�X�֐ݒ�
	// �`�撼�O�ɌĂяo���Ă�������
	void BindVertexBuffer(void) const;

	// ���_�o�b�t�@�擪�A�h���X���擾
	virtual  LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer(u16 vertex_buffer_index) const
	{
		return _vertex_buffers[vertex_buffer_index];
	}

	// �v���~�e�B�u���擾
	u32 GetPrimitiveCount(u16 primitive_index)
	{
		return _primitive_count[primitive_index];
	}

	// ���
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