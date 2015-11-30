//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// コマンドバッファ
// 
// Created by Ryusei Kajiya on 20151009
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "command_buffer.h"

#include "Resource/Mesh/mesh_buffer.h"
#include "Shader/shader_base.h"

//=============================================================================
// 頂点情報の押し込み
void CommandBuffer::PushMesh(const MeshBuffer* mesh, u32 id)
{

	all_buffer_[_mesh_buffer_index].object_id = id;
	all_buffer_[_mesh_buffer_index].use = true;
	all_buffer_[_mesh_buffer_index].mesh = mesh;

	++_mesh_buffer_index;
}

//=============================================================================
// シェーダ―の押し込み
void CommandBuffer::PushShader(const ShaderBase* shader, u32 id)
{
	all_buffer_[_shader_buffer_index].object_id = id;
	all_buffer_[_shader_buffer_index].use = true;
	all_buffer_[_shader_buffer_index].shader = shader;

	++_shader_buffer_index;
}

//=============================================================================
// レンダーステートの押し込み
void CommandBuffer::PushRenderState(const RENDER_STATE render_state, u32 id)
{
	all_buffer_[_render_state_buffer_index].use = true;
	all_buffer_[_render_state_buffer_index].object_id = id;
	all_buffer_[_render_state_buffer_index].render_state = render_state;

	++_render_state_buffer_index;
}

//=============================================================================
// レンダーステートの取り出し
const RENDER_STATE CommandBuffer::GetRenderStateBuffer(u32 id) const
{
	return render_state_buffer_[id].render_state;
}
//=============================================================================
// レンダーステートの最大数取り出し
const u32 CommandBuffer::LengthRenderState() const
{
	return RENDER_STATE_MAX;
}

//=============================================================================
// シェーダの先頭を指すイテレーターを返す
std::list<CommandBuffer::ShaderBuffer>::const_iterator CommandBuffer::ShaderBegin(u32 index) const
{
	return render_state_buffer_[index].shader_list.begin();
}

//=============================================================================
// シェーダ―の終端を指すイテレーターを返す
std::list<CommandBuffer::ShaderBuffer>::const_iterator CommandBuffer::ShaderEnd(u32 index) const
{
	return render_state_buffer_[index].shader_list.end();
}

//=============================================================================
// バッファ内を効率よく描画するためソート
void CommandBuffer::Sort()
{

	for (int i = 0; i < RENDER_STATE_MAX; ++i)
	{
		render_state_buffer_[i].render_state = static_cast<RENDER_STATE>(i);
	}

	// 情報を入れる
	for( u32 i = 0; i < kMaxBuffer; ++i )
	{
		if (all_buffer_[i].use)
		{
			for (u32 j = 0; j < RENDER_STATE_MAX; ++j)
			{
				if (render_state_buffer_[j].render_state == all_buffer_[i].render_state)
				{
					// 頂点情報を入れる
					MeshDataBuffer mesh_buffer;
					mesh_buffer.object_id = all_buffer_[i].object_id;
					mesh_buffer.mesh = all_buffer_[i].mesh;

					// シェーダ－情報を入れる
					ShaderBuffer shader_buffer;
					shader_buffer.object_id = all_buffer_[i].object_id;
					shader_buffer.shader = all_buffer_[i].shader;
					shader_buffer.mesh_list.push_back(mesh_buffer);

					// レンダーステート情報を入れる
					render_state_buffer_[j].shader_list.push_back(shader_buffer);
				}
			}
		}
	}
}

//=============================================================================
// クリア
void CommandBuffer::Clear()
{
	for (u32 i = 0; i < RENDER_STATE_MAX; ++i)
	{
		render_state_buffer_[i].shader_list.clear();
	}

	for (u32 i = 0; i < kMaxBuffer; ++i)
	{
		all_buffer_[i].object_id = 0;
		all_buffer_[i].shader = nullptr;
		all_buffer_[i].mesh = nullptr;
		all_buffer_[i].use = false;
		all_buffer_[i].render_state = RENDER_STATE_DEFAULT;
	}

	_render_state_buffer_index = 0;
	_shader_buffer_index = 0;
	_mesh_buffer_index = 0;
}

//=============================================================================
// レンダーステートのソート用オペレータ
bool CommandBuffer::RenderStateBuffer::operator<(const RenderStateBuffer& rhs)
{
	return this->render_state < rhs.render_state;
}

bool CommandBuffer::RenderStateBuffer::operator>(const RenderStateBuffer& rhs)
{
	return this->render_state > rhs.render_state;
}

bool CommandBuffer::RenderStateBuffer::operator==(const RenderStateBuffer& rhs)
{
	return this->render_state == rhs.render_state;
}