//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// コマンドプロセッサ
// 
// Created by Ryusei Kajiya on 20151009
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "command_processor.h"
#include "Resource/Mesh/mesh_buffer.h"
#include "DrawCommand/command_buffer.h"
#include "Shader/shader_base.h"

//=============================================================================
// ライトからの深度
void CommandProcessor::ProccessLightDepth(void) const
{
	Proccess(RENDER_STATE_LIGHT_DEPTH);
}
//=============================================================================
// 通常
void CommandProcessor::ProccessDefault(void) const
{
	Proccess(RENDER_STATE_DEFAULT);
}
//=============================================================================
// 影
void CommandProcessor::ProccessShadow(void) const
{
	Proccess(RENDER_STATE_SHADOW);
}
//=============================================================================
// フィールド
void CommandProcessor::ProccessField(void) const
{
	Proccess(RENDER_STATE_FIELD);
}
//=============================================================================
// バックグラウンド
void CommandProcessor::ProccessBackGround(void) const
{
	Proccess(RENDER_STATE_BACKGROUND);
}
//=============================================================================
// 半透明
void CommandProcessor::ProccessTranslucent(void) const
{
	Proccess(RENDER_STATE_TRANSLUCENT);
}
//=============================================================================
// 照準
void CommandProcessor::ProccessAIM(void) const
{
	Proccess(RENDER_STATE_AIM);
}
//=============================================================================
// 2D
void CommandProcessor::Proccess2D(void) const
{
	Proccess(RENDER_STATE_2D);
}

//=============================================================================
// 描画処理
void CommandProcessor::Proccess(u32 render_state_paramater) const
{
	for( auto shader = _command_buffer.ShaderBegin(render_state_paramater); shader != _command_buffer.ShaderEnd(render_state_paramater); ++shader )
	{// シェーダループ

		const ShaderBase& shader_base = *shader->shader;
		u32 number_shader_pass = 0;

		// シェーダ描画の開始
		shader_base.Begin(&number_shader_pass);
		// シェーダ割り当て
		shader_base.AssignExceptMaterial();

		// シェーダパスループ
		for( u32 count_shader_pass = 0; count_shader_pass < number_shader_pass; ++count_shader_pass )
		{
			// パスの設定
			shader_base.BeginPass(count_shader_pass);
			for( auto mesh = shader->mesh_list.begin(); mesh != shader->mesh_list.end(); ++mesh )
			{
				const MeshBuffer& mesh_buffer = *mesh->mesh;
				mesh_buffer.BindVertexBuffer();
				mesh_buffer.BindIndexBuffer(0);
				// 描画
				shader_base.CommitChanges();
				mesh_buffer.Draw(0);
			}
			shader_base.EndPass();
		}
		shader_base.End();
	}
}
