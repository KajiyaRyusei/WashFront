//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �t�F�[�h
//
// Created by Ryusei Kajiya on 20151013
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �O���錾
class ShaderFade;
class MeshBuffer;
class Application;

//*****************************************************************************
// �N���X��`
class Fade
{
public:

	explicit Fade(Application* application);

	virtual ~Fade(){ Finalize(); }

	// ������
	void Initialize(Application* application);

	// �I��
	void Finalize();

	// �X�V
	void Update();

	// �`��
	void Draw();

	// �t�F�[�h�C������ĂԂ�0~1~0�ɂȂ�
	void FadeIn();

	// �t�F�[�h�A�E�g����ĂԂ�1~0�ɂȂ�
	void FadeOut();

	// �t�F�[�h��1�̏�Ԃ��Ȃ�
	const bool IsFadeTop()const
	{
		if( _fade_color.w >= 1.f )
		{
			return true;
		}
		return false;
	}

	// �t�F�[�h���Ă��邩�ǂ���
	const bool IsFadeNow() const
	{
		return _is_fade_now;
	}

private:

	// �V�F�[�_�[
	ShaderFade* _shader;
	// ���b�V��
	MeshBuffer* _mesh;
	// �A�v���P�[�V����
	Application* _application;
	// �t�F�[�h�J���[
	D3DXVECTOR4 _fade_color;
	// �t�F�[�h�t���O
	bool _is_fade_in;
	bool _is_fade_out;
	bool _is_fade_now;
	// �t�F�[�h�̍X�V
	void Fading();
};