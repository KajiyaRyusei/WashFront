//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Score
// 
// Created by Toshiki Mochizuki on 20151123
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit\Result\score.h"
#include "Unit\number.h"
#include "Unit\Result\bulletin_board.h"

//*****************************************************************************
// const
const D3DXVECTOR3	position[ 8 ] =
{
	D3DXVECTOR3( 430.0f , 670.0f , 0.0f ) ,
	D3DXVECTOR3( 430.0f , 730.0f , 0.0f ) ,
	D3DXVECTOR3( 430.0f , 790.0f , 0.0f ) ,
	D3DXVECTOR3( 430.0f , 850.0f , 0.0f ) ,
	D3DXVECTOR3( 830.0f , 670.0f , 0.0f ) ,
	D3DXVECTOR3( 830.0f , 730.0f , 0.0f ) ,
	D3DXVECTOR3( 830.0f , 790.0f , 0.0f ) ,
	D3DXVECTOR3( 830.0f , 850.0f , 0.0f )
};

const float			dest_pos_Y[ 4 ] =
{
	120.0f ,
	180.0f ,
	240.0f ,
	300.0f
};

const D3DXVECTOR3	scaling			= D3DXVECTOR3( 30.0f , 50.0f , 0.0f );
const int			countUpTime		= 120;
const float			countTimeSpeed	= 1.0f / countUpTime;

//*****************************************************************************
// static
int ScoreUnit::_num = 0;
bool ScoreUnit::_finish_flg = false;
//=============================================================================
// 初期化
void ScoreUnit::Initialize()
{
	for( int i = 0; i < digit; i++ )
	{
		_score[ i ] = new NumberUnit( _application, _game_world);
		_score[ i ]->SetPosition( D3DXVECTOR3( position[ _num ].x - ( ( float )i * scaling.x ) , position[ _num ].y , 0.0f ) );
		_score[ i ]->SetScaling( scaling );
	}
	_grade			= 0.0f;
	_timeCnt		= 0;
	_score_value	= 0;
	_id				= _num;
	_num++;
}

//=============================================================================
// 終了
void ScoreUnit::Finalize()
{
	for( int i = 0; i < digit; i++ )
	{
		
		SafeDelete( _score[ i ] );
	}
}

//=============================================================================
// 更新
void ScoreUnit::Update()
{
	if( BulletinUnit::GetUpdateFlg() )
	{
		for( int i = 0; i < digit; i++ )
		{
			D3DXVECTOR3 pos = _score[ i ]->GetPosition();
			if( pos.y > dest_pos_Y[ _id % 4 ] )
			{
				_score[ i ]->SetPosition( D3DXVECTOR3( pos.x , pos.y - 10 , pos.z ) );
			}
		}
	}
	if( BulletinUnit::GetDispFlg() )
	{
		_timeCnt++;
		if( _timeCnt > ( _id % 4 ) * countUpTime + countUpTime )
		{
			_grade += countTimeSpeed;
			if( _grade >= 1.0f )
			{
				_grade = 1.0f;
			}
			_score_value = ( int )( _dest_score * _grade );
		}
	}

	for( int i = 0; i < digit; i++ )
	{
		// mokuteki no atai wo okuru( ex 12345 no baai score[ 2 ] ha 3 )
		_score[ i ]->SetValue( _score_value / Pow( 10 , i ) );
		// hanei
		_score[ i ]->Update();
	}
	
	if( _id == 7 && _grade >= 1.0f )
	{
		_finish_flg = true;
	}
}

//=============================================================================
// 更新
void ScoreUnit::CollisionUpdate()
{

}

//=============================================================================
// 描画
void ScoreUnit::Draw()
{
	for( int i = 0; i < digit; i++ )
	{
		_score[ i ]->Draw();
	}
}

//=============================================================================
// 累乗
int ScoreUnit::Pow( int num , int mulutiplier )
{
	// 0乗を考慮
	int f = 1;

	// 累乗処理
	for( int i = 0; i < mulutiplier; i++ )
	{
		f *= num;
	}
	// リターン
	return f;
}