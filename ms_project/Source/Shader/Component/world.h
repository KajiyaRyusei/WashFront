//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ワールド
//
// Created by Ryusei Kajiya on 20151023
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
	class World
	{
	public:
		World() : _handle_world(nullptr) {}
		virtual ~World() {}

		// ハンドル取得を行います。
		void InitializeWorld(LPD3DXEFFECT effect)
		{
			_handle_world = effect->GetParameterByName(nullptr, "uniform_world");
			ASSERT(_handle_world != nullptr, "ハンドル読み込みに失敗しました。");
		}

		 // シェーダーに送信
		void SendWorld(LPD3DXEFFECT effect) const
		{
			effect->SetMatrix(_handle_world, &_world);
		}

		// ミューテータ
		void SetWorld(const D3DXMATRIX& world)
		{
			_world = world;
		}

	private:
		D3DXHANDLE _handle_world;
		D3DXMATRIX _world;
	};

};
