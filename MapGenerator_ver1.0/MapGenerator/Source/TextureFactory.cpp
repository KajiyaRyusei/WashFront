//=============================================================================
//
// テクスチャファクトリ [TextureFactory.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "TextureFactory.h"
#include "Manager.h"
#include "Renderer.h"


//=========================================================================
// コンストラクタ
//=========================================================================
TextureFactory::TextureFactory()
{
}

//=========================================================================
// デストラクタ
//=========================================================================
TextureFactory::~TextureFactory()
{
	
	// テクスチャポインタの解放
	for (auto itr = textureMap_.begin(); itr != textureMap_.end(); ++itr) {
		// 解放処理
		SafeRelease(itr->second);
	}
	textureMap_.clear();

}

//=========================================================================
// テクスチャのインポート
//=========================================================================
int TextureFactory::ImportTexture(std::string texturePath)
{
	// すでにあるかどうかチェック
	if (textureMap_.find(texturePath) == textureMap_.end()) {
		// テクスチャ生成
		D3DXCreateTextureFromFile(
			Manager::GetInstance()->GetRenderer()->GetDevice(),
			texturePath.c_str(),
			&textureMap_[texturePath]);
		return 1;
	} else {
		return 0;
	}

}

//=========================================================================
// テクスチャの取得
//=========================================================================
LPDIRECT3DTEXTURE9 TextureFactory::GetTexture(std::string texturePath)
{

	// すでにあるかどうかチェック
	if (textureMap_.find(texturePath) == textureMap_.end()) {
		// テクスチャ生成
		D3DXCreateTextureFromFile(
			Manager::GetInstance()->GetRenderer()->GetDevice(),
			texturePath.c_str(),
			&textureMap_[texturePath]);
	}

	return textureMap_[texturePath];

}


// End of file