//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Score
// 
// Created by Toshiki Mochizuki on 20151123
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "Unit\unit.h"

//*****************************************************************************
// �O���錾
class NumberUnit;

//*****************************************************************************
// �萔
// keta
const int digit = 5;

//*****************************************************************************
// �N���X�݌v
class ScoreUnit : public Unit
{
public:

	ScoreUnit(Application* application, World* world) : Unit(application, world)
	{
		for( int i = 0; i < digit; i++ )
		{
			_score[i] = nullptr;
		}
		Initialize();
	}
	virtual ~ScoreUnit(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override;

	
	void CountUp(float grade);
	void Move(void);
	// �X�R�A�Z�b�g
	void SetDestScore(int value)
	{
		_dest_score = value;
	}

	// 
	static bool GetFlg(void)
	{
		return _finish_flg;
	}

	static void SetFlg(bool flg)
	{
		_finish_flg = flg;
	}

	void SetTexture( LPCWSTR fileName );

	// 
	void SetPos(D3DXVECTOR3 pos);


	// 
	void SetScale(D3DXVECTOR3 scale);



private:

	// �ݏ�
	int Pow(int num, int mulutipiler);
	//
	int CheckDigit(int value);

	// keta suu bun Instance wo kakuho
	NumberUnit*		_score[digit];
	// 
	// gennzai no atai
	int				_score_value;
	// mokuhyou no atai
	int				_dest_score;
	//
	D3DXVECTOR3		_pos;
	D3DXVECTOR3		_fPos;
	// 
	D3DXVECTOR3		_scale;
	//
	LPCWSTR			_fileName;

	// ���̃N���X�̃C���X�^���X�̐�
	static int		_num;
	// 
	static bool		_finish_flg;
};