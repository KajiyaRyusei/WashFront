//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �R�}���h�v���Z�b�T
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
// ���C�g����̐[�x
void CommandProcessor::ProccessLightDepth(void) const
{
	Proccess(RENDER_STATE_LIGHT_DEPTH);
}
//=============================================================================
// �ʏ�
void CommandProcessor::ProccessDefault(void) const
{
	Proccess(RENDER_STATE_DEFAULT);
}
//=============================================================================
// �e
void CommandProcessor::ProccessShadow(void) const
{
	Proccess(RENDER_STATE_SHADOW);
}
//=============================================================================
// �t�B�[���h
void CommandProcessor::ProccessField(void) const
{
	Proccess(RENDER_STATE_FIELD);
}
//=============================================================================
// �o�b�N�O���E���h
void CommandProcessor::ProccessBackGround(void) const
{
	Proccess(RENDER_STATE_BACKGROUND);
}
//=============================================================================
// ������
void CommandProcessor::ProccessTranslucent(void) const
{
	Proccess(RENDER_STATE_TRANSLUCENT);
}
//=============================================================================
// �Ə�
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
// �`�揈��
void CommandProcessor::Proccess(u32 render_state_paramater) const
{
	for( auto shader = _command_buffer.ShaderBegin(render_state_paramater); shader != _command_buffer.ShaderEnd(render_state_paramater); ++shader )
	{// �V�F�[�_���[�v

		const ShaderBase& shader_base = *shader->shader;
		u32 number_shader_pass = 0;

		// �V�F�[�_�`��̊J�n
		shader_base.Begin(&number_shader_pass);
		// �V�F�[�_���蓖��
		shader_base.AssignExceptMaterial();

		// �V�F�[�_�p�X���[�v
		for( u32 count_shader_pass = 0; count_shader_pass < number_shader_pass; ++count_shader_pass )
		{
			// �p�X�̐ݒ�
			shader_base.BeginPass(count_shader_pass);
			for( auto mesh = shader->mesh_list.begin(); mesh != shader->mesh_list.end(); ++mesh )
			{
				const MeshBuffer& mesh_buffer = *mesh->mesh;
				mesh_buffer.BindVertexBuffer();
				mesh_buffer.BindIndexBuffer(0);
				// �`��
				shader_base.CommitChanges();
				mesh_buffer.Draw(0);
			}
			shader_base.EndPass();
		}
		shader_base.End();
	}
}
