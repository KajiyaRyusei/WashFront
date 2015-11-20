//=============================================================================
//
// ���E���N���X [BoundingSphere.h]
// Author : KEITA OHUCHI
//
//=============================================================================
#ifndef _BOUNDING_SPHERE_H_
#define _BOUNDING_SPHERE_H_

#include "Shape.h"
#include "Renderer.h"


//-----------------------------------------------------------------------------
// �N���X��`
//-----------------------------------------------------------------------------
class BoundingSphere : public Shape {
public:
	//=========================================================================
	// �R���X�g���N�^�ƃf�X�g���N�^
	//=========================================================================
	BoundingSphere() {};
	virtual ~BoundingSphere() {};

	//=========================================================================
	// �`�揈��
	//=========================================================================
	void Draw();


	//=========================================================================
	// �`��̎擾����
	//=========================================================================
	SHAPE_TYPE GetType() { return SHAPE_TYPE_SPHERE; };
	//=========================================================================
	// ���S���W�̎擾����
	//=========================================================================
	D3DXVECTOR3 GetPosition() { return position_; };
	//=========================================================================
	// ���a�̎擾����
	//=========================================================================
	float GetRadius() { return radius_; };

	//=========================================================================
	// ���S���W�̐ݒ菈��
	//=========================================================================
	void SetPosition(D3DXVECTOR3 pos) { position_ = pos; };
	//=========================================================================
	// ���a�̐ݒ菈��
	//=========================================================================
	void SetRadius(float radius) { radius_ = radius; };


private:
	D3DXVECTOR3 position_;  // ���S���W
	float radius_;  // ���a
};


#endif


// End of file