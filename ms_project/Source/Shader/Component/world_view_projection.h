//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ワールドビュープロジェクション
//
// Created by Ryusei Kajiya on 20151009
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
	class WorldViewProjection
	{
	public:
		WorldViewProjection() : _handle_world_view_projection(nullptr) {}
		virtual ~WorldViewProjection() {}

		// ハンドル取得を行います。
		void InitializeWorldViewProjection(LPD3DXEFFECT effect)
		{
			_handle_world_view_projection = effect->GetParameterByName(nullptr, "uniform_world_view_projection");
			ASSERT(_handle_world_view_projection != nullptr, "ハンドル読み込みに失敗しました。");
		}

		 // シェーダーに送信
		void SendWorldViewProjection(LPD3DXEFFECT effect) const
		{
			effect->SetMatrix(_handle_world_view_projection, &_world_view_projection);
		}

		// ミューテータ
		void SetWorldViewProjection(const D3DXMATRIX& world_view_projection)
		{
			_world_view_projection = world_view_projection;
		}

	private:
		D3DXHANDLE _handle_world_view_projection;
		D3DXMATRIX _world_view_projection;
	};

};
