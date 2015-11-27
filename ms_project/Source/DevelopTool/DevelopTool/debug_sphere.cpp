//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// デバッグ用球
//
// Created by Ryusei Kajiya on 20151028
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "debug_sphere.h"
#include "Renderer/directx9.h"
#include "Algorithm/often_use.h"

//=============================================================================
// 初期化
void DebugSphere::Initialize()
{
#ifdef _DEBUG
	for( u32 i = 0; i < kMaxShpere; ++i )
	{
		_sphere[i].position = D3DXVECTOR3(0.f, 0.f, 0.f);
		_sphere[i].scale = 1.f;
	}

	_current_sphere_index = 0;

	LPDIRECT3DDEVICE9 device = Reference::GetInstance().GetRenderer()->GetDevice();
	D3DXCreateSphere(device, 1.f, 10, 10,&_mesh,nullptr);

#endif
}

//=============================================================================
// 終了
void DebugSphere::Finalize()
{
#ifdef _DEBUG
	SafeRelease(_mesh);
#endif
}

//=============================================================================
// 描画
void DebugSphere::Draw()
{
#ifdef _DEBUG

	D3DXMATRIX world, rotation_matrix, transform_matrix;
	D3DXMatrixIdentity(&world);
	LPDIRECT3DDEVICE9 device = Reference::GetInstance().GetRenderer()->GetDevice();
	device->SetRenderState(D3DRS_LIGHTING, FALSE);

	for( u32 i = 0; i < _current_sphere_index; ++i )
	{
		algo::CreateWorld(world, _sphere[i].position, D3DXVECTOR3(0.f, 0.f, 0.f), D3DXVECTOR3(_sphere[i].scale, _sphere[i].scale, _sphere[i].scale));
		device->SetTransform(D3DTS_WORLD, &world);
		_mesh->DrawSubset(0);
	}

	device->SetRenderState(D3DRS_LIGHTING, TRUE);

	_current_sphere_index = 0;
#endif
}

//=============================================================================
// 登録
void DebugSphere::RegisteSphere(
	const float scale,
	const D3DXVECTOR3& position)
{
#ifdef _DEBUG
	if( _current_sphere_index >= kMaxShpere )
	{
		OutputDebugStringA("デバックボックスの登録数を超えてます");
		return;
	}

	_sphere[_current_sphere_index].position = position;
	_sphere[_current_sphere_index].scale = scale;

	++_current_sphere_index;
#else
	UNREFERENCED_PARAMETER(scale);
	UNREFERENCED_PARAMETER(position);
#endif
}
