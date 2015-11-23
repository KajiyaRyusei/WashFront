//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// テクスチャリソース
//
// Created by Ryusei Kajiya on 20151122
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Resource/texture_resource.h"
#include "Renderer/directx9.h"

//*****************************************************************************
// 定数
namespace
{
	static const LPCWSTR kTextureResourceNames[] =
	{
		L"Data/Texture/oji_body.jpg",
		L"Data/Texture/window.png",
		L"Data/Texture/aim.png",
		L"Data/Texture/mud-normal.jpg",
		L"Data/Texture/water.jpg",
		L"Data/Texture/water-normal003.jpg",
		L"Data/Texture/window_spec.png",
		L"Data/Texture/dirty_000.jpg"
	};
}

//=============================================================================
// 作成
void TextureResource::Create(TEXTURE_RESOURE_ID id, RendererDevice* device)
{
	LPDIRECT3DTEXTURE9 texture;

	D3DXCreateTextureFromFileEx(device->GetDevice(), kTextureResourceNames[id], 0, 0, 0, 0, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xff, nullptr, nullptr, &texture);
	if( _resource_box->Add(texture, id) == false )
	{
		SafeRelease(texture);
	}
}

//=============================================================================
// 全削除
void TextureResource::Clear()
{
	for( auto it = _resource_box->Begin(); it != _resource_box->End();++it )
	{
		SafeRelease(it->second);
	}
}

//=============================================================================
// 取得
LPDIRECT3DTEXTURE9 TextureResource::Get(TEXTURE_RESOURE_ID id)
{
	return _resource_box->Get(id);
}
