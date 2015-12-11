//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �J����
// 
// Created by Ryusei Kajiya on 20151201
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "Data/data_projection.h"
#include "Data/data_view.h"
#include "Algorithm/frustum_culling.h"

//*****************************************************************************
// �O���錾
class Application;

//*****************************************************************************
// �N���X�݌v
class Camera
{
public:

	explicit Camera(Application* application) : _application(application){}

	virtual ~Camera(){}

	// ������
	virtual void Initialize() = 0;

	// �r���[�v���W�F�N�V�����̍쐬
	virtual void CreateMatrix() = 0;

	// �r���[�s��A�N�Z�T
	const D3DXMATRIX& GetMatrixView() const{ return _view.matrix; }
	void SetMatrixView(const D3DXMATRIX &view){ _view.matrix = view; }

	// �v���W�F�N�V�����s��A�N�Z�T
	const D3DXMATRIX& GetMatrixProjection() const { return _projection.matrix; }
	void SetMatrixProjection(const D3DXMATRIX &projection){ _projection.matrix = projection; }

	// ���_�̃A�N�Z�T
	const D3DXVECTOR3& GetVectorEye() const { return _view.eye; }
	void SetVectorEye(const D3DXVECTOR3 &eye){ _view.eye = eye; }

	// �����_�̃A�N�Z�T
	const D3DXVECTOR3& GetVectorLookAt() const { return _view.look_at; }
	void SetVectorLookAt(const D3DXVECTOR3 &look_at){ _view.look_at = look_at; }

	// ��x�N�g���̃A�N�Z�T
	const D3DXVECTOR3& GetVectorUp() const { return _view.up; }
	void SetVectorUp(const D3DXVECTOR3 &up){ _view.up = up; }

	// �r���[�|�[�g�̃A�N�Z�T
	const D3DVIEWPORT9& GetViewport() const { return _viewport; }
	void SetViewport(const D3DVIEWPORT9& viewport){ _viewport = viewport; }

	// fov�̃A�N�Z�T
	const fx32 GetFov() const { return _projection.fov; }
	void SetFov(const fx32 fov){ _projection.fov = fov; }

	// aspect�̃A�N�Z�T
	const fx32 GetAspect() const { return _projection.aspect; }
	void SetAspect(const fx32 aspect){ _projection.aspect= aspect; }

	// near�̃A�N�Z�T
	const fx32 GetNear() const { return _projection.camera_near; }
	void SetNear(const fx32 camera_near){ _projection.camera_near = camera_near; }

	// far�̃A�N�Z�T
	const fx32 GetFar() const { return _projection.camera_far; }
	void SetFar(const fx32 camera_far){ _projection.camera_far = camera_far; }

	// ������J�����O�̃Q�b�g
	FrustumCulling& GetFrustumCulling(){ return _frustum_culling;}

protected:

	data::View _view;
	data::Projection _projection;
	D3DVIEWPORT9 _viewport;
	Application* _application;
	FrustumCulling _frustum_culling;
};