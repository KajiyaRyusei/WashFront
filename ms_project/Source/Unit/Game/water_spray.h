//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �����Ԃ�
// 
// Created by Ryusei Kajiya on 20151125
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �N���X�݌v
class WaterSpray
{
public:
	WaterSpray();

	WaterSpray* GetNext() const { return _state._next; }
	void SetNext(WaterSpray* next){ _state._next = next; }
	// ������
	void Initialize(
		const D3DXVECTOR3& position,
		const fx32 rotation);
	// �A�j���[�V����
	bool Animate(D3DXMATRIX& matrix);
	// �g�p���Ă��邩
	bool IsUse()const;

private:

	fx32 _frame;

	union
	{
		struct
		{
			D3DXVECTOR3 _position;
			fx32 _rotation;
			D3DXVECTOR3 _scale;
		};
		WaterSpray* _next;
	}_state;

};