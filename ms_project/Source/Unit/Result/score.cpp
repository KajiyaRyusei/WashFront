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

//*****************************************************************************
// const
const D3DXVECTOR3	position[ 8 ] =
{
	D3DXVECTOR3( 430.0f , 120.0f , 0.0f ) ,
	D3DXVECTOR3( 430.0f , 180.0f , 0.0f ) ,
	D3DXVECTOR3( 430.0f , 240.0f , 0.0f ) ,
	D3DXVECTOR3( 430.0f , 300.0f , 0.0f ) ,
	D3DXVECTOR3( 830.0f , 120.0f , 0.0f ) ,
	D3DXVECTOR3( 830.0f , 180.0f , 0.0f ) ,
	D3DXVECTOR3( 830.0f , 240.0f , 0.0f ) ,
	D3DXVECTOR3( 830.0f , 300.0f , 0.0f )
};

const D3DXVECTOR3	scaling		= D3DXVECTOR3( 30.0f , 50.0f , 0.0f );

//*****************************************************************************
// static
int ScoreUnit::_num = 0;

//=============================================================================
// ������
void ScoreUnit::Initialize()
{
	for( int i = 0; i < digit; i++ )
	{
		_score[ i ] = new NumberUnit( _app, _world);
		_score[ i ]->SetPosition( D3DXVECTOR3( position[ _num ].x - ( ( float )i * scaling.x ) , position[ _num ].y , 0.0f ) );
		_score[ i ]->SetScaling( scaling );
	}
	_score_value = 12345;
	_num++;
}

//=============================================================================
// �I��
void ScoreUnit::Finalize()
{
	for( int i = 0; i < digit; i++ )
	{
		
		SafeDelete( _score[ i ] );
	}
}

//=============================================================================
// �X�V
void ScoreUnit::Update()
{
	for( int i = 0; i < digit; i++ )
	{
		_score[ i ]->SetValue( _score_value / Pow( 10 , i + 1 ) );
		_score[ i ]->Update();
	}
}

//=============================================================================
// �X�V
void ScoreUnit::CollisionUpdate()
{

}

//=============================================================================
// �`��
void ScoreUnit::Draw()
{
	for( int i = 0; i < digit; i++ )
	{
		_score[ i ]->Draw();
	}
}

//=============================================================================
// �ݏ�
int ScoreUnit::Pow( int num , int mulutiplier )
{
	// 0����l��
	int f = 1;

	// �ݏ揈��
	for( int i = 0; i < mulutiplier; i++ )
	{
		f *= num;
	}
	// ���^�[��
	return f;
}