//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// デバッグ用Box
//
// Created by Ryusei Kajiya on 20151028
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "debug_box.h"
#include "Renderer/directx9.h"
#include "Algorithm/often_use.h"

//=============================================================================
// 初期化
void DebugBox::Initialize()
{
#ifdef _DEBUG
	for( u32 i = 0; i < kMaxBox; ++i )
	{
		_boxs[i].position = D3DXVECTOR3(0.f, 0.f, 0.f);
		_boxs[i].rotation = D3DXVECTOR3(0.f, 0.f, 0.f);
		_boxs[i].scaling = D3DXVECTOR3(1.f, 1.f, 1.f);
	}

	_current_box_index = 0;

	D3DXVECTOR3 ltf(1.f, 1.f, 1.f);
	D3DXVECTOR3 rtf(-1.f, 1.f, 1.f);
	D3DXVECTOR3 lbf(1.f, -1.f, 1.f);
	D3DXVECTOR3 rbf(-1.f, -1.f, 1.f);
	D3DXVECTOR3 rtb(-1.f, 1.f, -1.f);
	D3DXVECTOR3 rbb(-1.f, -1.f, -1.f);
	D3DXVECTOR3 ltb(1.f, 1.f, -1.f);
	D3DXVECTOR3 lbb(1.f, -1.f, -1.f);

	vertices[0].position = ltf;
	vertices[1].position = rtf;
	vertices[2].position = lbf;
	vertices[3].position = rbf;
	vertices[4].position = rbf;
	vertices[5].position = rtf;
	vertices[6].position = rbb;
	vertices[7].position = rtb;
	vertices[8].position = rtb;
	vertices[9].position = lbf;
	vertices[10].position = lbf;
	vertices[11].position = rbf;
	vertices[12].position = lbb;
	vertices[13].position = rbb;
	vertices[14].position = rbb;
	vertices[15].position = ltf;
	vertices[16].position = ltf;
	vertices[17].position = lbf;
	vertices[18].position = ltb;
	vertices[19].position = lbb;
	vertices[20].position = lbb;
	vertices[21].position = rtf;
	vertices[22].position = rtf;
	vertices[23].position = ltf;
	vertices[24].position = rtb;
	vertices[25].position = ltb;
	vertices[26].position = ltb;
	vertices[27].position = lbb;
	vertices[28].position = rtb;
	vertices[29].position = rbb;

	for( u32 i = 0; i < kVertexMax; ++i )
	{
		vertices[i].color = D3DCOLOR_ARGB(200, 255, 255, 0);
	}

#endif
}

//=============================================================================
// 終了
void DebugBox::Finalize()
{
#ifdef _DEBUG

#endif
}

//=============================================================================
// 描画
void DebugBox::Draw()
{
#ifdef _DEBUG

	D3DXMATRIX world, rotation_matrix, transform_matrix;
	D3DXMatrixIdentity(&world);
	LPDIRECT3DDEVICE9 device = Reference::GetInstance().GetRenderer()->GetDevice();
	device->SetRenderState(D3DRS_LIGHTING, FALSE);

	for( u32 i = 0; i < _current_box_index; ++i )
	{
		algo::CreateWorld(world, _boxs[i].position, _boxs[i].rotation, _boxs[i].scaling);
		device->SetTransform(D3DTS_WORLD, &world);
		device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
		device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, kVertexMax-2, vertices, sizeof(VERTEX_BOX));
	}

	device->SetRenderState(D3DRS_LIGHTING, TRUE);

	_current_box_index = 0;
#endif
}

//=============================================================================
// 登録
void DebugBox::RegisteBox(
	const D3DXVECTOR3& volume,
	const D3DXVECTOR3& position,
	const D3DXVECTOR3& rotation)
{
#ifdef _DEBUG

	if( _current_box_index >= kMaxBox )
	{
		OutputDebugStringA("デバックボックスの登録数を超えてます");
		return;
	}

	_boxs[_current_box_index].position = position;
	_boxs[_current_box_index].rotation = rotation;
	_boxs[_current_box_index].scaling = volume;

	++_current_box_index;
#else
	UNREFERENCED_PARAMETER(volume);
	UNREFERENCED_PARAMETER(position);
	UNREFERENCED_PARAMETER(rotation);
#endif
}
