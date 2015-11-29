//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// �Փ˔���֐��Q
// 
// Created by Ryusei Kajiya on 20151028
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �Փ˔���֐��Q
namespace collision
{
	// ��`�Ƌ�`�̏Փ˔���
	bool Rect2Rect(
		const D3DXVECTOR2 &p1,	// ��`�@����̍��W
		const D3DXVECTOR2 &s1,	// ��`�@�傫��
		const D3DXVECTOR2 &p2,	// ��`�A����̍��W
		const D3DXVECTOR2 &s2);	// ��`�A�傫��

	// �_�ƎO�p�`�̏Փ˔���
	bool Point2Trigangle(
		const D3DXVECTOR3& point,		// �_
		const D3DXVECTOR3& point_one,	// �O�p�`�̍��W1
		const D3DXVECTOR3& point_two,	// �O�p�`�̍��W2
		const D3DXVECTOR3& point_three);// �O�p�`�̍��W3

	// ���ƎO�p�`�̏Փ˔���
	bool Line2Trigangle(
		D3DXVECTOR3* impact_point,		// �Փ˂��Ă�ꏊ
		const D3DXVECTOR3& start_point,	// �����̎n�_
		const D3DXVECTOR3& end_point,	// �����̏I�_
		const D3DXVECTOR3& point_one,	// �O�p�`�̍��W1
		const D3DXVECTOR3& point_two,	// �O�p�`�̍��W2
		const D3DXVECTOR3& point_three);// �O�p�`�̍��W3

	// ���Ǝl�p�`�̏Փ�
	bool Line2Square(
		D3DXVECTOR3* impact_point,		// �Փ˂��Ă�ꏊ
		const D3DXVECTOR3& start_point,	// �����̎n�_
		const D3DXVECTOR3& end_point,	// �����̏I�_
		const D3DXVECTOR3& point_one,	// �l�p�`�̍��W1
		const D3DXVECTOR3& point_two,	// �l�p�`�̍��W2
		const D3DXVECTOR3& point_three,	// �l�p�`�̍��W3
		const D3DXVECTOR3& point_four);	// �l�p�`�̍��W3

	// ���Ɨ����̂̏Փ�
	bool Line2Box(
		D3DXVECTOR3* impact_point,		// �Փ˂��Ă�ꏊ
		const D3DXVECTOR3& start_point,	// �����̎n�_
		const D3DXVECTOR3& end_point,	// �����̏I�_
		const D3DXVECTOR3& ltf,			// �����O
		const D3DXVECTOR3& rtf,			// �����O
		const D3DXVECTOR3& lbf,			// �����O
		const D3DXVECTOR3& rbf,			// �����O
		const D3DXVECTOR3& ltb,			// ������
		const D3DXVECTOR3& rtb,			// ������
		const D3DXVECTOR3& lbb,			// ������
		const D3DXVECTOR3& rbb);		// ������

	// ���Ƌ��̏Փ˔���
	bool Sphrere2Sphrere(
		const D3DXVECTOR3& point_one,	// ���̒��S�@
		const D3DXVECTOR3& point_two,	// ���̒��S�A
		const fx32 radius_one,			// ���̔��a�@
		const fx32 radius_two);			// ���̔��a�A
};