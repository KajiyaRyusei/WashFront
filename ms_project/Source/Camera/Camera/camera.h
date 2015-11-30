//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// カメラ
// 
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "Data/data_projection.h"
#include "Data/data_view.h"

//*****************************************************************************
// 前方宣言
class Application;

//*****************************************************************************
// クラス設計
class Camera
{
public:

	explicit Camera(Application* application) : _application(application){}

	virtual ~Camera(){}

	// 初期化
	virtual void Initialize() = 0;

	// ビュープロジェクションの作成
	virtual void CreateMatrix() = 0;

	// ビュー行列アクセサ
	const D3DXMATRIX& GetMatrixView() const{ return _view.matrix; }
	void SetMatrixView(const D3DXMATRIX &view){ _view.matrix = view; }

	// プロジェクション行列アクセサ
	const D3DXMATRIX& GetMatrixProjection() const { return _projection.matrix; }
	void SetMatrixProjection(const D3DXMATRIX &projection){ _projection.matrix = projection; }

	// 視点のアクセサ
	const D3DXVECTOR3& GetVectorEye() const { return _view.eye; }
	void SetVectorEye(const D3DXVECTOR3 &eye){ _view.eye = eye; }

	// 注視点のアクセサ
	const D3DXVECTOR3& GetVectorLookAt() const { return _view.look_at; }
	void SetVectorLookAt(const D3DXVECTOR3 &look_at){ _view.look_at = look_at; }

	// 上ベクトルのアクセサ
	const D3DXVECTOR3& GetVectorUp() const { return _view.up; }
	void SetVectorUp(const D3DXVECTOR3 &up){ _view.up = up; }

	// ビューポートのアクセサ
	const D3DVIEWPORT9& GetViewport() const { return _viewport; }
	void SetViewport(const D3DVIEWPORT9& viewport){ _viewport = viewport; }

protected:

	data::View _view;
	data::Projection _projection;
	D3DVIEWPORT9 _viewport;
	Application* _application;
};