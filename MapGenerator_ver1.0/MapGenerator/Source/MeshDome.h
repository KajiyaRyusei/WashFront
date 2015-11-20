//=============================================================================
//
// ���b�V���h�[���N���X [MeshDome.h]
// Author : KEITA OHUCHI
//
//=============================================================================
#ifndef _MESH_DOME_H_
#define _MESH_DOME_H_

#include "Scene3D.h"


//-----------------------------------------------------------------------------
// �N���X��`
//-----------------------------------------------------------------------------
class MeshDome : public Scene3D {
public:
	//=========================================================================
	// �R���X�g���N�^�ƃf�X�g���N�^
	//=========================================================================
	MeshDome(int priority = PRIORITY_SKY);
	~MeshDome();

	//=========================================================================
	// ����������
	//=========================================================================
	virtual HRESULT Init(D3DXVECTOR3 pos,
		int block_num_x, int block_num_y,
		float radius);
	//=========================================================================
	// �X�V����
	//=========================================================================
	virtual void Update();
	//=========================================================================
	// �`�揈��
	//=========================================================================
	virtual void Draw();

	//=========================================================================
	// ��������
	//=========================================================================
	static MeshDome *Create(D3DXVECTOR3 pos,
		int block_num_x, int block_num_y,
		float radius);


private:
	LPDIRECT3DINDEXBUFFER9	indexBuffer_;  // �C���f�b�N�X�o�b�t�@
	int						indexNum_;  // ���_�̑��C���f�b�N�X��
	int						vertexNum_;  // �����_��
	int						polygonNum_;  // ���|���S����
	int						blockNumX_, blockNumY_;  // �u���b�N��
	float					radius_;  // ���a
};


#endif


// End of file.