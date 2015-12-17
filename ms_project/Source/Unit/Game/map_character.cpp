//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// マップキャラクター
// 
// Created by Chiharu Kamiyama on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit/Game/map_character.h"
#include "Unit/Game/map.h"
#include "World/collision_grid.h"
#include "Unit/ui.h"
#include "Windows/window.h"


//定数
static const int kMaxPass = 4;

//=============================================================================
// 初期化
void MapCharacter::Initialize()
{
	//各値初期化
	CreateTexture(TEXT("Data/Texture/map_character.png"));
	_texture_uv = D3DXVECTOR2(1.0f, 1.0f);
	_texture_offset = D3DXVECTOR2(0.0f, 0.0f);
	_texture_alpha = 1.0f;

	_position = D3DXVECTOR3(0.0f,
		(float)_application->GetWindow()->GetSizeWindowHeight() / 2,
		0.0f);
	_rotation = 0.0f;
	_scaling = D3DXVECTOR3(50.0f, 50.0f, 1.0f);

	//総移動距離算出
/*	D3DXVECTOR3 pass[kMaxPass];
	pass[0] = _game_world->GetCollisionGrid()->CellCenterPoint(1, 1);
	pass[1] = _game_world->GetCollisionGrid()->CellCenterPoint(3, 1);
	pass[2] = _game_world->GetCollisionGrid()->CellCenterPoint(3, 3);
	pass[3] = _game_world->GetCollisionGrid()->CellCenterPoint(1, 3);

	D3DXVECTOR3 vec;

	float distance = 0.0f;

	vec = pass[1] - pass[0];

	distance += abs(vec.x);
	distance += abs(vec.y);
	distance += abs(vec.z);

	vec = pass[2] - pass[1];

	distance += abs(vec.x);
	distance += abs(vec.y);
	distance += abs(vec.z);

	vec = pass[3] - pass[2];

	distance += abs(vec.x);
	distance += abs(vec.y);
	distance += abs(vec.z);

	vec = pass[0] - pass[3];

	distance += abs(vec.x);
	distance += abs(vec.y);
	distance += abs(vec.z);

	//総距離保存
	_map_distance = distance;
	*/
	_map_distance = 0.0f;
	_character_distance = 0;
	_map_character_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_map_character_old_position = _map_character_position;
}

//=============================================================================
// 終了
void MapCharacter::Finalize()
{
}

//=============================================================================
// 更新
void MapCharacter::Update()
{
	D3DXVECTOR3 vec;
	vec = _map_character_position - _map_character_old_position;

	//移動量計算
	float distance = 0.0f;
	distance = abs(vec.x);
	distance += abs(vec.y);
	distance += abs(vec.z);

	//差分移動
	_character_distance += distance;
	float per = _character_distance / _map_distance;

	//ウィンドウの幅
	float window_width = (float)_application->GetWindow()->GetSizeWindowWidth();

	//場所算出
	float pos_x = window_width * per;


	//全部隠れたら下リピートのやつと一緒に。
	if ((pos_x - _scaling.x / 2) >= window_width)
	{
		if (_id == 0)
		{
			_character_distance -= _map_distance;
			pos_x = _scaling.x / 2;
		}
	}


	//上端まで行ったらリピート表示
	if ((pos_x + _scaling.x / 2) >= window_width)
	{
		if (_id == 1)
		{
			//はみ出した差分を計算
			float difference = 0.0f;
			difference = pos_x - _scaling.x / 2 - window_width;

			//はみ出した分下から出す。
			pos_x = difference;

			if (pos_x <= window_width)
			{
				_character_distance -= _map_distance;
			}
		}
	}



	//場所更新
	SetPosition(D3DXVECTOR3(pos_x, _position.y, _position.z));

	//表示更新
	ScreenUnit::Update();
}

//=============================================================================
// 描画
void MapCharacter::Draw()
{
	ScreenUnit::Draw();

}

//=============================================================================
// 座標設定
void MapCharacter::SetMapCharacterPosition(D3DXVECTOR3 position)
{
	_map_character_old_position = _map_character_position;
	_map_character_position = position;
}

//=============================================================================
//マップキャラクター初期位置セット
void MapCharacter::InitMapCharacterPosition(D3DXVECTOR3 position)
{
	_map_character_position = position;
	_map_character_old_position = _map_character_position;

}