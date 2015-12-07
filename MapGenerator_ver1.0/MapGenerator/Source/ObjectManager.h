//=============================================================================
//
// �I�u�W�F�N�g�}�l�[�W���N���X [ObjectManager.h]
// Author : KEITA OHUCHI
//
//=============================================================================
#ifndef _OBJECT_MANAGER_H_
#define _OBJECT_MANAGER_H_

#include "Main.h"



//-----------------------------------------------------------------------------
// STL�g�p�錾
//-----------------------------------------------------------------------------
using namespace std;
#include <vector>


//-----------------------------------------------------------------------------
// �O���錾
//-----------------------------------------------------------------------------

// �Q�[���I�u�W�F�N�g
class MeshField;
class MeshCylinder;
class MeshDome;
class Player;
class Light;
class Scene3D;
class Building;

// �Փ˔���
class CollisionManager;

class Cursor;



//-----------------------------------------------------------------------------
// �N���X��`
//-----------------------------------------------------------------------------
class ObjectManager {
public:
	//=========================================================================
	// �R���X�g���N�^�ƃf�X�g���N�^
	//=========================================================================
	ObjectManager();
	virtual ~ObjectManager();

	//=========================================================================
	// ����������
	//=========================================================================
	HRESULT Init();
	//=========================================================================
	// �X�V����
	//=========================================================================
	void Update();
	//=========================================================================
	// �`�揈��
	//=========================================================================
	void Draw();

	//=========================================================================
	// �}�E�X�ƃI�u�W�F�N�g�̏Փ˔���
	//=========================================================================
	void CheckCollisionMouseAndObject();
	void CollisionMouseAndObject();


	//=========================================================================
	// �C���X�^���X�̐���
	//=========================================================================
	Building *CreateBuilding(const char *modelFileName, const char *textureFilePath);
	Building *CreateBuilding(const char *fileName, const char *textureFilePath,
		D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale, bool collision);
	Building *CopyBuilding();

	//=========================================================================
	// �C���X�^���X�̑S�폜
	//=========================================================================
	void AllDeleteBuilding();

	//=========================================================================
	// �C���X�^���X�̎擾
	//=========================================================================
	MeshField *GetField() { return field_; };
	Player *GetPlayer() { return player_;  };
	CollisionManager *GetCollisionManager() { return collisionManager_; };
	Building *GetSelectBuilding();
	Cursor *GetCursor() { return cursor_; }


	//=========================================================================
	// ���������I�u�W�F�N�g�����O���o��
	//=========================================================================
	void SaveBuildingData(FILE *outputFile);

	//=========================================================================
	// ��������I�u�W�F�N�g�����O������
	//=========================================================================
	void ReadBuildingData(FILE *inputFile);


#ifdef _DEBUG
	// �A�b�v�f�[�g�t���O�̎擾
	bool GetUpdateFlag() { return updateFlag_; };
#endif


private:
	static const int LIGHT_NUM = 3;

	Scene3D				*water_;					// ��


	// ���C�g
	Light				*light_[LIGHT_NUM];

	// �Q�[���I�u�W�F�N�g
	MeshField			*field_;					// �t�B�[���h
	MeshCylinder		*mountain_;					// �R
	MeshDome			*sky_;						// ��
	Player				*player_;					// �v���C���[

	std::vector <Building*>	buildingList_;			// �r���̃��X�g
	int						buildingListCursor_;	// �J�[�\��

	// �Փ˔���
	CollisionManager	*collisionManager_;			// �Փ˔���̊Ǘ�

	Cursor				*cursor_;


#ifdef _DEBUG
	// �X�V�t���O
	bool	updateFlag_;
#endif

};


#endif


// End of file