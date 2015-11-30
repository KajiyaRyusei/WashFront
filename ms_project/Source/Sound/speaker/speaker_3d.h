//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// 3D�T�E���h�X�s�[�J�[
// 
// Created by Ryusei Kajiya on 20151021
// 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "speaker.h"

//*****************************************************************************
// �O���錾
class Application;

//*****************************************************************************
// �N���X�݌v
class Speaker3D : public Speaker
{
public:
	Speaker3D(XactCueIndex cue_index, Application* application) :
		Speaker(cue_index, application)
	{
		_emitter.pCone = nullptr;
		_emitter.OrientFront = D3DXVECTOR3(0.0f, 0.0f, 1.0f);         // �G�~�b�^�̐��ʃx�N�g��
		_emitter.OrientTop = D3DXVECTOR3(0.0f, 1.0f, 0.0f);             // �G�~�b�^�̏�x�N�g��
		_emitter.Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);            // �G�~�b�^�̍��W
		_emitter.Velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);            // �G�~�b�^�̑��x(�h�b�v���[�Ɏg�p)
		_emitter.ChannelCount = 1;                                    // �G�~�b�^�̃`�����l���J�E���g(�G�~�b�^�̐��B0���傫���l���w��)
		_emitter.ChannelRadius = 0.0f;                                // �`�����l���J�E���g��1�ȏ�̏ꍇ�ɃG�~�b�^���z�u�������W����̋����B�}���`�`�����l���G�~�b�^�Ŏg�p
		_emitter.CurveDistanceScaler = 1.0f;                          // �J�[�u�����X�P�[��(#1)
		_emitter.pChannelAzimuths = nullptr;                          // ���W�A���P�ʂ̕��ʊp�ŕ\�����`�����l���ʒu�e�[�u���B�}���`�`�����l���G�~�b�^�Ŏg�p
		_emitter.pVolumeCurve = nullptr;                              // �{�����[�����x���J�[�u(#1)
		_emitter.pLFECurve = nullptr;                                 // LFE ���[���I�t�����J�[�u(#1)
		_emitter.pLPFDirectCurve = nullptr;                           // ���[�p�X �t�B���^�[ (LPF) �_�C���N�g �p�X�W�������J�[�u(#1)
		_emitter.pLPFReverbCurve = nullptr;                           // LPF ���o�[�u �p�X�W�������J�[�u(#1)
		_emitter.pReverbCurve = nullptr;                              // ���o�[�u �Z���h ���x�������J�[�u(#1)
		_emitter.DopplerScaler = 1.0f;                                // �h�b�v���[�Έڌ��ʂ��������邽�߂Ɏg�p����h�b�v���[�ΈڃX�P�[���[(#1)
		_emitter.InnerRadius = 10.0f;                                 // �������a�̌v�Z�Ɏg�p�����l(��������܂��ݒ肵�Ȃ��ƁA�G�~�b�^���W�����X�i�[���W�ɏd�Ȃ����Ƃ������ςɂȂ�)
	}
	virtual ~Speaker3D(){}
	bool Play(void);
	void Pause(void);
	void Stop(void);

	bool IsPlaying(void) const;

	void Update(void);

	void SetEmitterPosition(D3DXVECTOR3 position)
	{
		_emitter.Position = position;
	}

private:
	X3DAUDIO_EMITTER _emitter;
};
