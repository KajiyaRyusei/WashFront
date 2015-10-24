//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// デバッグ用ラインキューブ
//
// Created by Ryusei Kajiya on 20151023
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "debug_line_box.h"
#include "Renderer/directx9.h"
#include "Algorithm/often_use.h"



//=============================================================================
// 初期化
void DebugLineBox::Initialize()
{
#ifndef _RELEASE
	for( u32 i = 0; i < kMaxBox; ++i )
	{
		_boxs[i].position = D3DXVECTOR3(0.f, 0.f, 0.f);
		_boxs[i].rotation = D3DXVECTOR3(0.f, 0.f, 0.f);
		_boxs[i].scaling = D3DXVECTOR3(1.f, 1.f, 1.f);
	}

	_current_line_box_index = 0;

	D3DXVECTOR3 ltf(1.f, 1.f, 1.f);
	D3DXVECTOR3 rtf(-1.f, 1.f, 1.f);
	D3DXVECTOR3 lbf(1.f, -1.f, 1.f);
	D3DXVECTOR3 rbf(-1.f, -1.f, 1.f);
	D3DXVECTOR3 rtb(-1.f, 1.f, -1.f);
	D3DXVECTOR3 rbb(-1.f, -1.f, -1.f);
	D3DXVECTOR3 ltb(1.f, 1.f, -1.f);
	D3DXVECTOR3 lbb(1.f, -1.f, -1.f);

	vertices[0].position = ltf;
	vertices[1].position = ltb;
	vertices[2].position = rtb;
	vertices[3].position = rtf;
	vertices[4].position = ltf;
	vertices[5].position = rtf;
	vertices[6].position = rbf;
	vertices[7].position = lbf;
	vertices[8].position = ltf;
	vertices[9].position = ltb;
	vertices[10].position = lbb;
	vertices[11].position = lbf;
	vertices[12].position = ltf;
	vertices[13].position = lbf;
	vertices[14].position = lbb;
	vertices[15].position = rbb;
	vertices[16].position = rbf;
	vertices[17].position = lbf;
	vertices[18].position = rbf;
	vertices[19].position = rbb;
	vertices[20].position = rtb;
	vertices[21].position = rtf;

	for( u32 i = 0; i < kVertexMax; ++i )
	{
		vertices[i].color = D3DCOLOR_ARGB(255, 0, 0, 255);
	}

#endif
}

//=============================================================================
// 終了
void DebugLineBox::Finalize()
{
#ifndef _RELEASE

#endif
}

//=============================================================================
// 描画
void DebugLineBox::Draw()
{
#ifndef _RELEASE


	D3DXMATRIX world, rotation_matrix, transform_matrix;
	D3DXMatrixIdentity(&world);
	LPDIRECT3DDEVICE9 device = Reference::GetInstance().GetRenderer()->GetDevice();
	//device->SetRenderState(D3DRS_ZENABLE, FALSE);
	device->SetRenderState(D3DRS_LIGHTING, FALSE);

	for( u32 i = 0; i < _current_line_box_index; ++i )
	{
		algo::CreateWorld(world, _boxs[i].position, _boxs[i].rotation, _boxs[i].scaling);
		device->SetTransform(D3DTS_WORLD, &world);

		device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
		device->DrawPrimitiveUP(D3DPT_LINESTRIP, kVertexMax-1, vertices, sizeof(VERTEX_CUBE));

	}
	device->SetRenderState(D3DRS_LIGHTING, TRUE);
	device->SetRenderState(D3DRS_ZENABLE, TRUE);

	_current_line_box_index = 0;
#endif
}

//=============================================================================
// 登録
void DebugLineBox::RegisteBox(
	const D3DXVECTOR3& volume,
	const D3DXVECTOR3& position,
	const D3DXVECTOR3& rotation)
{
#ifndef _RELEASE
	if( _current_line_box_index >= kMaxBox )
	{
		OutputDebugStringA("デバックボックスの登録数を超えてます");
		return;
	}

	_boxs[_current_line_box_index].position = position;
	_boxs[_current_line_box_index].rotation = rotation;
	_boxs[_current_line_box_index].scaling = volume;

	++_current_line_box_index;
#else
	UNREFERENCED_PARAMETER(volume);
	UNREFERENCED_PARAMETER(position);
	UNREFERENCED_PARAMETER(rotation);
#endif
}