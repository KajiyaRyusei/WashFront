//=============================================================================
//
// X�t�@�C�����f���N���X [SceneX.h]
// Author : KEITA OHUCHI
//
//=============================================================================
#ifndef _SCENE_X_H_
#define _SCENE_X_H_

#include "Main.h"
#include "Scene.h"
#include "Model.h"


//-----------------------------------------------------------------------------
// �O���錾
//-----------------------------------------------------------------------------
class Model;


//-----------------------------------------------------------------------------
// �N���X��`
//-----------------------------------------------------------------------------
class SceneX : public Scene {
public:
	//=========================================================================
	// �R���X�g���N�^�ƃf�X�g���N�^
	//=========================================================================
	SceneX(int priority = 0);
	virtual ~SceneX();

	//=========================================================================
	// ����������
	//=========================================================================
	virtual HRESULT Init();
	virtual HRESULT Init(char *modelFileName);
	virtual HRESULT Init(char *modelFileName, char *textureFileName);
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
	static SceneX *Create();


	//=========================================================================
	// ���f���̐ݒ�
	//=========================================================================
	void SetModel(char *xFileName);

	//=========================================================================
	// ��]�̎擾
	//=========================================================================
	D3DXVECTOR3 GetRotation() { return rotation_; };
	//=========================================================================
	// �}�g���N�X�̐ݒ�
	//=========================================================================
	void SetWorldMatrix(D3DXMATRIX matrix) { worldMatrix_ = matrix; };

protected:
	Model		*model_;

	D3DXMATRIX	worldMatrix_;  // ���[���h�}�g���b�N�X
	D3DXVECTOR3	scale_;  // �傫��
	D3DXVECTOR3	rotation_;  // ����
};


#endif


// End of file