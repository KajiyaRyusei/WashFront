//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// アニメーションマトリックス
//
// Created by Ryusei Kajiya on 20151014
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
	class AnimationMatrix
	{
	public:
		AnimationMatrix() : _handle_animation_matrix(nullptr)
		{

		}
		virtual ~AnimationMatrix() {}

		// ハンドル取得を行います。
		void InitializeAnimationMatrix(LPD3DXEFFECT effect)
		{
			_handle_animation_matrix = effect->GetParameterByName(nullptr, "uniform_animation_matrix_list");
			ASSERT(_handle_animation_matrix != nullptr, "ハンドル読み込みに失敗しました。");
		}

		 // シェーダーに送信
		void SendAnimationMatrix(LPD3DXEFFECT effect) const
		{
			effect->SetMatrixArray(_handle_animation_matrix, _animation_matrix_list, 40);
		}

		// ミューテータ
		// 行列の最大数は現在40個です。
		void SetAnimationMatrix(const D3DXMATRIX* animation_matrix_list )
		{
			for( u8 i = 0; i < kMatrixMax;++i )
			{
				_animation_matrix_list[i] = animation_matrix_list[i];
			}
		}

		static const u8 kMatrixMax = 18;

	private:
		D3DXHANDLE _handle_animation_matrix;
		D3DXMATRIX _animation_matrix_list[kMatrixMax];
	};

};
