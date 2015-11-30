//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// �l�I�ɂ悭�g���֐��Q
// 
// Created by Ryusei Kajiya on 20151022
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �O���錾
class Camera;

//*****************************************************************************
// �悭�g���֐��Q
namespace algo
{
	//====================================
	// ���[���h�r���[�v���W�F�N�V�����̍쐬
	D3DXMATRIX& CreateWVP(
		D3DXMATRIX& world_view_projection,
		const D3DXMATRIX& world,
		const Camera* camera);

	//====================================
	// ���[���h�s��̍쐬
	D3DXMATRIX& CreateWorld(
		D3DXMATRIX& world,
		const D3DXVECTOR3& position,
		const D3DXVECTOR3& rotation,
		const D3DXVECTOR3& scale);

	//====================================
	// ���[���h�̕��������[�J���ɍ��킹��
	D3DXVECTOR4& CreateLocalDirection(
		D3DXVECTOR4& inverse_vector,
		const D3DXVECTOR4& vector,
		const D3DXMATRIX& world);

	//====================================
	// �x�W�F�Ȑ�
	D3DXVECTOR3& BezierCurve2D(
		D3DXVECTOR3& out_point,
		const D3DXVECTOR3& start_point,
		const D3DXVECTOR3& end_point,
		const D3DXVECTOR3& control_point,
		const fx32 frame);

	//====================================
	// ���_���W��UV����ڃx�N�g���Ə]�@�������߂�
	// *�k�ރ|���S���͂Ȃɂ������ɕԂ�
	void ComputeTangentAndBinormal(
		const D3DXVECTOR3 &position_one,
		const D3DXVECTOR3 &position_two,
		const D3DXVECTOR3 &position_three,
		const D3DXVECTOR2 &texcoord_one,
		const D3DXVECTOR2 &texcoord_two,
		const D3DXVECTOR2 &texcoord_three,
		D3DXVECTOR3* tangent,
		D3DXVECTOR3* binormal);
}

