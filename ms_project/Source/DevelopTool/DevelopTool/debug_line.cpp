﻿//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// デバッグ用ライン
//
// Created by Ryusei Kajiya on 20151023
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "debug_line.h"
#include "Renderer/directx9.h"

//*****************************************************************************
// 頂点構造体
struct VERTEX_LINE
{
	D3DXVECTOR3 position;
	D3DCOLOR color;
};

//=============================================================================
// 初期化
void DebugLine::Initialize()
{
#ifndef _RELEASE
	for( u32 i = 0; i < kMaxLine; ++i )
	{
		_lines[i].vertices[0] = D3DXVECTOR3(0.f, 0.f, 0.f);
		_lines[i].vertices[1] = D3DXVECTOR3(0.f, 0.f, 1.f);
		_lines[i].position = D3DXVECTOR3(0.f, 0.f, 0.f);
		_lines[i].rotation = D3DXVECTOR3(0.f, 0.f, 0.f);
	}
	_current_line_index = 0;
#endif
}

//=============================================================================
// 終了
void DebugLine::Finalize()
{
#ifndef _RELEASE

#endif
	
}

//=============================================================================
// 描画
void DebugLine::Draw()
{
#ifndef _RELEASE

	D3DXMATRIX projection,view,world,rotation_matrix,transform_matrix;
	D3DXMatrixIdentity(&world);
	LPDIRECT3DDEVICE9 device = Reference::GetInstance().GetRenderer()->GetDevice();
	device->SetRenderState(D3DRS_ZENABLE, FALSE);
	device->SetRenderState(D3DRS_LIGHTING, FALSE);

	VERTEX_LINE vertex[2];

	for( u32 i = 0; i < _current_line_index; ++i )
	{
		D3DXMatrixRotationYawPitchRoll(&rotation_matrix, _lines[i].rotation.y, _lines[i].rotation.x, _lines[i].rotation.z);
		D3DXMatrixTranslation(&transform_matrix, _lines[i].position.x, _lines[i].position.y, _lines[i].position.z);
		world = rotation_matrix * transform_matrix;
		device->SetTransform(D3DTS_WORLD, &world);
		
		vertex[0].position = _lines[_current_line_index].vertices[0];
		vertex[1].position = _lines[_current_line_index].vertices[1];
		vertex[0].color = D3DCOLOR_ARGB(255, 255, 0, 0);
		vertex[1].color = D3DCOLOR_ARGB(255, 255, 0, 0);
		
		device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
		device->DrawPrimitiveUP(D3DPT_LINELIST, 1, vertex, sizeof(VERTEX_LINE));
		
	}
	device->SetRenderState(D3DRS_LIGHTING, TRUE);
	device->SetRenderState(D3DRS_ZENABLE, TRUE);

	_current_line_index = 0;
#endif
}

//=============================================================================
// ラインの登録
void DebugLine::RegisteLine(const fx32 length, const D3DXVECTOR3& position, const D3DXVECTOR3& rotation)
{
#ifndef _RELEASE
	if( _current_line_index  >= kMaxLine )
	{
		OutputDebugStringA("デバックラインの登録数を超えてます");
		return;
	}
	_lines[_current_line_index].position = position;
	_lines[_current_line_index].rotation = rotation;
	_lines[_current_line_index].vertices[0] = D3DXVECTOR3(0.f, 0.f, 0.f);
	_lines[_current_line_index].vertices[1] = D3DXVECTOR3(length, length, length);
	++_current_line_index;
#else
	UNREFERENCED_PARAMETER(length);
	UNREFERENCED_PARAMETER(position);
	UNREFERENCED_PARAMETER(rotation);
#endif
}
