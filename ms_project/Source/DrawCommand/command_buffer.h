//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �R�}���h�o�b�t�@
// 
// Created by Ryusei Kajiya on 20151009
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once


//*****************************************************************************
// �O���錾
class MeshBuffer;
class ShaderBase;

//*****************************************************************************
// ��
enum RENDER_STATE
{
	RENDER_STATE_LIGHT_DEPTH = 0,
	RENDER_STATE_DEFAULT,
	RENDER_STATE_SHADOW,
	RENDER_STATE_FIELD,
	RENDER_STATE_2D,
	RENDER_STATE_MAX
};

//*****************************************************************************
// �N���X�錾
class CommandBuffer
{
public:

	struct MeshDataBuffer
	{
		const MeshBuffer* mesh;
		u32 object_id;
	};

	struct ShaderBuffer
	{
		const ShaderBase* shader;
		u32 object_id;
		std::list<MeshDataBuffer> mesh_list;
	};

	struct RenderStateBuffer
	{
		RENDER_STATE render_state;
		u32 shader_length;
		u32 object_id;
		std::list<ShaderBuffer> shader_list;
		bool operator<(const RenderStateBuffer& right_hand_side);
		bool operator>(const RenderStateBuffer& right_hand_side);
		bool operator==(const RenderStateBuffer& right_hand_side);
	};

	CommandBuffer() : 
		_render_state_buffer_index(0),
		_shader_buffer_index(0),
		_mesh_buffer_index(0)
	{
		Clear();
	}

	virtual ~CommandBuffer(){}

	// ��񉟂�����
	void PushMesh(const MeshBuffer* mesh, u32 id);
	void PushShader(const ShaderBase* shader, u32 id);
	void PushRenderState(const RENDER_STATE render_state, u32 id);

	// �����o��
	const RENDER_STATE GetRenderStateBuffer(u32 index) const;

	// �����_�[�X�e�[�g�̒������擾
	const u32 CommandBuffer::LengthRenderState() const;

	// �V�F�[�_�\�̃C�e���[�^���擾
	std::list<CommandBuffer::ShaderBuffer>::const_iterator ShaderBegin(u32 index) const;
	std::list<CommandBuffer::ShaderBuffer>::const_iterator ShaderEnd(u32 index) const;

	// �\�[�g
	void Sort();
	// ���g����ɂ���
	void Clear();

private:

	struct AllBuffer
	{
		RENDER_STATE render_state;
		const ShaderBase *shader;
		const MeshBuffer* mesh;
		u32 object_id;
		bool use;
	};

	RenderStateBuffer render_state_buffer_[RENDER_STATE_MAX];

	// �S�̃o�b�t�@�̍ő�l
	static const u32 kMaxBuffer = 1000;
	u32 _render_state_buffer_index;
	u32 _shader_buffer_index;
	u32 _mesh_buffer_index;
	AllBuffer all_buffer_[kMaxBuffer];

};