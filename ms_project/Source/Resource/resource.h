//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���\�[�X�C���^�[�t�F�[�X
//
// Created by Ryusei Kajiya on 20151102
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "Resource/resource_box.h"

//*****************************************************************************
// �O���錾
class RendererDevice;

//*****************************************************************************
// �N���X�݌v
template<class T, typename ID>
class Resource
{
public:

	Resource(){ _resource_box = new ResourceBox<T>; }
	virtual ~Resource(){ SafeDelete(_resource_box); }
	// �쐬
	virtual void Create(ID id, RendererDevice* device) = 0;
	// �S�폜
	virtual void Clear() = 0;
	// �擾
	virtual T Get(ID id) = 0;

protected:
	ResourceBox<T>* _resource_box;
};