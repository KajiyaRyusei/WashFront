//==============================================================================
//
// �G�t�F�N�g�̃n���h�����쐬�������Ă���
//
// Created by Ryusei Kajiya on 20151008
//
//==============================================================================

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �O���錾
class RendererDevice;

//*****************************************************************************
// �N���X�݌v
class EffectHandleHolder
{
public:
	EffectHandleHolder(const char *effect_file_path, RendererDevice* renderer_device);
	virtual ~EffectHandleHolder();

	// �G�t�F�N�g�n���h���擾
	LPD3DXEFFECT effect_handle(void) const { return _effect_handle; }


	// ������邾��
	void Begin(u32* pass) const;
	void End() const;
	void BeginPass(u32 pass_number) const;
	void EndPass() const;
	void CommitChanges() const;

	//�폜�`�F�b�N
	virtual bool IsDead(void) const { return is_dead_; }

	//�폜�\�ɐݒ�
	virtual void KillMySelf(void) { is_dead_ = true; }

private:

	LPD3DXEFFECT _effect_handle;
	D3DXHANDLE _handle_technique;
	bool is_dead_;

};