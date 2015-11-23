//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 汚れテクスチャ
//
// Created by Ryusei Kajiya on 20151122
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// クラス設計
namespace component
{
	// 詳しくはファイル先頭のコメントを参照してください。
	class DirtyMap
	{
	public:
		DirtyMap() : _handle_dirty_texture(nullptr) {}
		virtual ~DirtyMap() {}

		// ハンドル取得を行います。
		void InitializeDirtyTexture(LPD3DXEFFECT effect)
		{
			_handle_dirty_texture = effect->GetParameterByName(nullptr, "uniform_dirty_texture");
			ASSERT(_handle_dirty_texture != nullptr, "ハンドル読み込みに失敗しました。");
		}

		// シェーダーに送信
		void SendDirtyTexture(LPD3DXEFFECT effect) const
		{
			effect->SetTexture(_handle_dirty_texture, _dirty_texture);
		}

		// ミューテータ
		void SetDirtyTexture(const LPDIRECT3DTEXTURE9& dirty_texture)
		{
			_dirty_texture = dirty_texture;
		}

	private:
		D3DXHANDLE _handle_dirty_texture;
		LPDIRECT3DTEXTURE9 _dirty_texture;
	};

};
