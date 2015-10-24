//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// フェード
//
// Created by Ryusei Kajiya on 20151013
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// 前方宣言
class ShaderFade;
class MeshBuffer;
class Application;

//*****************************************************************************
// クラス定義
class Fade
{
public:

	explicit Fade(Application* application);

	virtual ~Fade(){ Finalize(); }

	// 初期化
	void Initialize(Application* application);

	// 終了
	void Finalize();

	// 更新
	void Update();

	// 描画
	void Draw();

	// フェードインから呼ぶと0~1~0になる
	void FadeIn();

	// フェードアウトから呼ぶと1~0になる
	void FadeOut();

	// フェードが1の状態をなら
	const bool IsFadeTop()const
	{
		if( _fade_color.w >= 1.f )
		{
			return true;
		}
		return false;
	}

	// フェードしているかどうか
	const bool IsFadeNow() const
	{
		return _is_fade_now;
	}

private:

	// シェーダー
	ShaderFade* _shader;
	// メッシュ
	MeshBuffer* _mesh;
	// アプリケーション
	Application* _application;
	// フェードカラー
	D3DXVECTOR4 _fade_color;
	// フェードフラグ
	bool _is_fade_in;
	bool _is_fade_out;
	bool _is_fade_now;
	// フェードの更新
	void Fading();
};