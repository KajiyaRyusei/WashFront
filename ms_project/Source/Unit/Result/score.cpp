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
const float			moveDistance[ 2 ]
{
	550.0f ,
	980.0f
};

//*****************************************************************************
// static
bool ScoreUnit::_finish_flg = false;

//=============================================================================
// 初期化
void ScoreUnit::Initialize()
{
	
	_score[ 0 ]		= new NumberUnit( _application, _game_world);
	_score_value	= 0;
	_finish_flg		= false;
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
	for( int i = 0; i < digit; i++ )
	{
		int a = CheckDigit( _score_value );
		if( a > i )
		{
			if( _score[ i ] == nullptr )
			{
				_score[ i ] = new NumberUnit( _application , _game_world );
				D3DXVECTOR3 pos = _score[ 0 ]->GetPosition();
				_score[ i ]->SetPosition( D3DXVECTOR3( pos.x - ( i * _scale.x ) , pos.y , pos.z ) );
				_score[ i ]->SetScaling( _scale );
			}
		}
		if( _score[ i ] != nullptr )
		{
			// mokuteki no atai wo okuru( ex 12345 no baai score[ 2 ] ha 3 )
			_score[ i ]->SetValue( _score_value / Pow( 10 , i ) );
			// hanei
			_score[ i ]->Update();
		}
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
		if( _score[ i ] != nullptr )
		{
			_score[ i ]->Draw();
		}
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

void ScoreUnit::CountUp( float grade )
{
	if( grade >= 0.0f )
	{
		if( grade >= 1.0f )
		{
			grade = 1.0f;
		}

		_score_value = ( int )( _dest_score * grade );
	}
}

void ScoreUnit::Move( void )
{
	float destPosY = _fPos.y - moveDistance[ windowSizeID ];

	for( int i = 0; i < digit; i++ )
	{
		if( _score[ i ] != nullptr )
		{
			D3DXVECTOR3 pos = _score[ i ]->GetPosition();
			if( pos.y > destPosY )
			{
				float y = BulletinUnit::Easing( _fPos.y , destPosY );
				_score[ i ]->SetPosition( D3DXVECTOR3( pos.x , y , pos.z ) );
			}
		}
	}
}

int ScoreUnit::CheckDigit( int value )
{
	int ans = 0;
	for( int i = 0; i <= digit; i++ )
	{
		if( value / Pow( 10 , i ) == 0 && value != 0 && value > 10 )
		{
			return ans;
		}
		ans++;	
	}
	return 1;
}

void ScoreUnit::SetPos( D3DXVECTOR3 pos )
{
	_pos	= pos;
	_fPos	= pos;
	_score[ 0 ]->SetPosition( _pos );
}

void ScoreUnit::SetScale( D3DXVECTOR3 scale )
{
	_scale = scale;
	_score[ 0 ]->SetScaling( scale );
}