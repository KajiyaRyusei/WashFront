//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �C���f�b�N�X�o�b�t�@
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
class IndexBuffer
{
	friend class MeshBuffer;
public:
	explicit IndexBuffer(RendererDevice* renderer_device);
	virtual ~IndexBuffer();

	// �C���f�b�N�X�J�E���g�̓o�^
	// �C���f�b�N�X�o�b�t�@�쐬���߂̑O�ɓo�^
	bool RegisterIndexCount(u16 index_buffer_count)
	{
		_index_buffer_count = index_buffer_count;
		_index_count = new u32[index_buffer_count];
		return true;
	}

	// �C���f�b�N�X���̓o�^
	// �C���f�b�N�X�o�b�t�@�쐬���߂̑O�ɓo�^
	// RegisterIndexCount�̌�ɌĂ�
	bool RegisterIndexInformation(u16 index_buffer_index, u32 index_count)
	{
		_index_count[index_buffer_index] = index_count;
		return true;
	}

	// �o�^���ꂽ�C���f�b�N�X�f�[�^�������ƂɃC���f�b�N�X�o�b�t�@�Q���쐬����B
	// ���̊֐��̑O��RegisterIndexCount��RegisterIndexInformation�œo�^���Ă���
	bool CreateIndexBuffer(u32 usage, D3DFORMAT format);

	void BindIndexBuffer(u16 index_buffer_index) const;

	// �C���f�b�N�X�o�b�t�@�擪�A�h���X���擾
	virtual LPDIRECT3DINDEXBUFFER9 GetIndexBuffer(u16 index_buffer_index) const
	{
		return _index_buffers[index_buffer_index];
	}

	// ���
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