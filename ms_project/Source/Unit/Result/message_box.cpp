//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Message_Box
// 
// Created by Toshiki Mochizuki on 20151123
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit\Result/message_box.h"
#include "Unit\Result\bulletin_board.h"

//*****************************************************************************
// const
const D3DXVECTOR3	scaling = D3DXVECTOR3(80.0f, 20.0f, 0.0f);
const float			dest_pos_Y[2] =
{
	550.0f,
	980.0f
};

//=============================================================================
// 初期化
void Message_BoxUnit::Initialize()
{
	// テクスチャ
	CreateTexture(TEXT("Data/Texture/black.jpg"));
	// UV値
	_texture_uv = D3DXVECTOR2(1.0f, 1.0f);
	// オフセット
	_texture_offset = D3DXVECTOR2(0.0f, 0.0f);
	// 透明値
	_texture_alpha = 1.0f;
	// 角度
	_rotation = 0.0f;
	// 大きさ
	_scaling = scaling;
	// 座標( 必ず外でセットすること )
	_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// 終了
void Message_BoxUnit::Finalize()
{

}

//=============================================================================
// 更新
void Message_BoxUnit::Update()
{
	if( BulletinUnit::GetUpdateFlg() )
	{
		if( _pos.y - dest_pos_Y[windowSizeID] < _position.y )
		{
			_position.y = BulletinUnit::Easing(_pos.y, (_pos.y - dest_pos_Y[windowSizeID]));
		}
	}
	ScreenUnit::Update();
}

//=============================================================================
// 更新
void Message_BoxUnit::CollisionUpdate()
{

}

//=============================================================================
// 描画
void Message_BoxUnit::Draw()
{
	ScreenUnit::Draw();
}

