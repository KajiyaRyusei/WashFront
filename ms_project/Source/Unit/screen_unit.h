//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �X�N���[���p���j�b�g : 2D�I�u�W�F�N�g
// 
// Created by Ryusei Kajiya on 20151102
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "unit.h"

//*****************************************************************************
// �O���錾
<<<<<<< HEAD
class ShaderScreen;
=======
class Shader2D;
class MeshBuffer;
>>>>>>> origin/Mochizuki-desk

//*****************************************************************************
// �N���X�݌v
class ScreenUnit : public Unit
{
public:

	ScreenUnit(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~ScreenUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override{}

	//�e�N�X�`���쐬
	void CreateTexture( LPCWSTR texture_filename );
	// ���W�Z�b�g
	void SetPosition( D3DXVECTOR3 pos )
	{
		_position = pos;
	}
	// �傫���Z�b�g
	void SetScaling( D3DXVECTOR3 scale )
	{
		_scaling = scale;
	}

protected:
	//uv�l
	D3DXVECTOR2 _texture_uv;

	//�I�t�Z�b�g�l
	D3DXVECTOR2 _texture_offset;

	//�A���t�@�l
	float _texture_alpha;

	//�|�W�V����
	D3DXVECTOR3 _position;

	//�p�x
	float _rotation;

	//�X�P�[��
	D3DXVECTOR3 _scaling;

private:

	// �V�F�[�_�[
<<<<<<< HEAD
	ShaderScreen* _shader;
=======
	Shader2D* _shader;

	// ���b�V��
	MeshBuffer* _mesh;

	//�e�N�X�`��
	LPDIRECT3DTEXTURE9 _texture;


>>>>>>> origin/Mochizuki-desk
};