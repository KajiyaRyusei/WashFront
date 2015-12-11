//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// キューブテクスチャリソース
//
// Created by Ryusei Kajiya on 20151102
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Resource/cube_texture_resource.h"
#include "Renderer/directx9.h"

//*****************************************************************************
// 定数
namespace
{
	static const LPCWSTR kCubeTextureResourceNames[] =
	{
		L"Data/CubeTexture/bill_cube_texture.dds",
		L"Data/CubeTexture/bill_cube_texture.dds",
		L"Data/CubeTexture/sky_cube.dds",
		L"Data/CubeTexture/sky_cube.dds"
	};
}

//=============================================================================
// 作成
void CubeTextureResource::Create(CUBE_TEXTURE_RESOURE_ID id, RendererDevice* device)
{
	LPDIRECT3DCUBETEXTURE9 diffuse_texture = nullptr;
	LPDIRECT3DCUBETEXTURE9 specular_texture = nullptr;

	if( id%2 == 0)
	{// 割り切れるのはディフューズ
		D3DXCreateCubeTextureFromFileEx(device->GetDevice(), kCubeTextureResourceNames[id], 2, 1, 0, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xff, nullptr, nullptr, &diffuse_texture);
		if( _resource_box->Add(diffuse_texture, id) == false )
		{
			SafeRelease(diffuse_texture);
		}
	}
	else
	{// 割り切れないのはスペキュラ
		D3DXCreateCubeTextureFromFileEx(device->GetDevice(), kCubeTextureResourceNames[id], 0, 0, 0, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xff, nullptr, nullptr, &specular_texture);
		if( _resource_box->Add(specular_texture, id) == false )
		{
			SafeRelease(specular_texture);
		}
	}
	
	
}

//=============================================================================
// 全削除
void CubeTextureResource::Clear()
{
	for( auto it = _resource_box->Begin(); it != _resource_box->End(); ++it )
	{
		SafeRelease(it->second);
	}
}

//=============================================================================
// 取得
LPDIRECT3DCUBETEXTURE9 CubeTextureResource::Get(CUBE_TEXTURE_RESOURE_ID id)
{
	return _resource_box->Get(id);
}