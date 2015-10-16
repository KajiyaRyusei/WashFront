//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// コマンドバッファ
// 
// Created by Ryusei Kajiya on 20151009
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once


//*****************************************************************************
// 前方宣言
class MeshBuffer;
class ShaderBase;

//*****************************************************************************
// 列挙
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
// クラス宣言
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

	// 情報押し込み
	void PushMesh(const MeshBuffer* mesh, u32 id);
	void PushShader(const ShaderBase* shader, u32 id);
	void PushRenderState(const RENDER_STATE render_state, u32 id);

	// 情報取り出し
	const RENDER_STATE GetRenderStateBuffer(u32 index) const;

	// レンダーステートの長さを取得
	const u32 CommandBuffer::LengthRenderState() const;

	// シェーダ―のイテレータを取得
	std::list<CommandBuffer::ShaderBuffer>::const_iterator ShaderBegin(u32 index) const;
	std::list<CommandBuffer::ShaderBuffer>::const_iterator ShaderEnd(u32 index) const;

	// ソート
	void Sort();
	// 中身を空にする
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

	// 全体バッファの最大値
	static const u32 kMaxBuffer = 1000;
	u32 _render_state_buffer_index;
	u32 _shader_buffer_index;
	u32 _mesh_buffer_index;
	AllBuffer all_buffer_[kMaxBuffer];

};