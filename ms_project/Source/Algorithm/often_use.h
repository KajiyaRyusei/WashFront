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

}

