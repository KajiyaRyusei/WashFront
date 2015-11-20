//=============================================================================
//
// AABB �����t���E�{�b�N�X�N���X [BoundingBox.h]
// Author : KEITA OHUCHI
//
//=============================================================================
#ifndef _BOUNDING_BOX_H_
#define _BOUNDING_BOX_H_

#include "Manager.h"
#include "Renderer.h"
#include "Shape.h"


//-----------------------------------------------------------------------------
// �N���X��`
//-----------------------------------------------------------------------------
class BoundingBox : public Shape{
public:
	//=========================================================================
	// �R���X�g���N�^�ƃf�X�g���N�^
	//=========================================================================
	BoundingBox() {};
	virtual ~BoundingBox() {};

	//=========================================================================
	// �`�揈��
	//=========================================================================
	void Draw() {
		D3DXVECTOR3 vertexPos[8] = {
			D3DXVECTOR3(min_.x, max_.y, max_.z),
			D3DXVECTOR3(max_.x, max_.y, max_.z),
			D3DXVECTOR3(min_.x, max_.y, min_.z),
			D3DXVECTOR3(max_.x, max_.y, min_.z),
			D3DXVECTOR3(min_.x, min_.y, max_.z),
			D3DXVECTOR3(max_.x, min_.y, max_.z),
			D3DXVECTOR3(min_.x, min_.y, min_.z),
			D3DXVECTOR3(max_.x, min_.y, min_.z)
		};

		int line[12][2] = {
			{0, 1},
			{2, 3},
			{4, 5},
			{6, 7},
			{0, 2},
			{1, 3},
			{4, 6},
			{5, 7},
			{0, 4},
			{1, 5},
			{2, 6},
			{3, 7},
		};

		VERTEX_3D vertex[2];
		vertex[0].diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		vertex[1].diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

		LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetRenderer()->GetDevice();
		device->SetFVF(FVF_VERTEX_3D);		// ���_�t�H�[�}�b�g�̐ݒ�

		// ���[���h�}�g���b�N�X�̐ݒ�
		D3DXMATRIX worldMatrix;
		D3DXMatrixIdentity(&worldMatrix);
		device->SetTransform(D3DTS_WORLD, &worldMatrix);

		for (int count = 0; count < 12; ++count) {
			vertex[0].vtx = vertexPos[line[count][0]];
			vertex[1].vtx = vertexPos[line[count][1]];

			device->DrawPrimitiveUP(D3DPT_LINELIST, 1, vertex, sizeof(VERTEX_3D));
		}
	};


	//=========================================================================
	// �`��̎擾����
	//=========================================================================
	SHAPE_TYPE GetType() { return SHAPE_TYPE_BOX; };
	//=========================================================================
	// �ŏ����W�̎擾����
	//=========================================================================
	D3DXVECTOR3 GetMin() { return min_; };
	//=========================================================================
	// �ő���W�̎擾����
	//=========================================================================
	D3DXVECTOR3 GetMax() { return max_; };

	//=========================================================================
	// �ŏ����W�̐ݒ菈��
	//=========================================================================
	void SetMin(D3DXVECTOR3 min) { min_ = min; };
	//=========================================================================
	// �ő���W�̐ݒ菈��
	//=========================================================================
	void SetMax(D3DXVECTOR3 max) { max_ = max; };

	//=========================================================================
	// ���W�̐ݒ菈��
	//=========================================================================
	void SetCenterPosition(D3DXVECTOR3 position, D3DXVECTOR3 scale) {
		min_ = position - scale / 2;
		max_ = position + scale / 2;
	};


private:
	D3DXVECTOR3 min_;  // �ŏ����W
	D3DXVECTOR3 max_;  // �ő���W
};


#endif


// End of file