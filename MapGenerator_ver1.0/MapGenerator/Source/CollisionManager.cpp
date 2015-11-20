//=============================================================================
//
// �Փ˔���Ǘ��N���X [CollisionManager.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "CollisionManager.h"
#include "BoxAndBox.h"
#include "BoxAndSphere.h"
#include "SphereAndSphere.h"
#include "Scene.h"
#ifdef _DEBUG
#include "Keyboard.h"
#include "Debug.h"
#endif


//-----------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------
// [0 or 1] : ���肷�邩�ǂ������߂�
// [false]  : ����͕K���s���Ȃ�
bool CollisionManager::collisionLayer_[COLLISION_LAYER_MAX][COLLISION_LAYER_MAX] = {
	/*
	{0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0},  // NONE
	{false, 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0,	 1},  // PLAYER
	{false, false, 0,	 0,	 0,	 0,	 0,	 0,	 0,	 0},  // ENEMY
	{false, false, false, 0,	 0,	 0,	 0,	 0,	 0,	 0},  // BULLET
	{false, false, false, false, 0,	 0,	 0,	 0,	 0,	 0},  // TREE
	{false, false, false, false, false, 0,	 0,	 0,	 0,	 0},  // WEED
	{false, false, false, false, false, false, 0,	 0,	 0,	 0},  // EXPLOSION
	{false, false, false, false, false, false, false, 0,	 0,	 0},  // ITEM
	{false, false, false, false, false, false, false, false, 0,	 0},  // GIMMICK
	{false, false, false, false, false, false, false, false, false, 0},  // GOAL
	*/
};


//=========================================================================
// �R���X�g���N�^
//=========================================================================
CollisionManager::CollisionManager()
{
	// �Փ˔���e�[�u���̐���
	checkTable_[SHAPE_TYPE_BOX][SHAPE_TYPE_BOX] = new BoxAndBox();
	checkTable_[SHAPE_TYPE_BOX][SHAPE_TYPE_SPHERE] = new BoxAndSphere();
	checkTable_[SHAPE_TYPE_SPHERE][SHAPE_TYPE_BOX] = new BoxAndSphere();
	checkTable_[SHAPE_TYPE_SPHERE][SHAPE_TYPE_SPHERE] = new SphereAndSphere();

	collisionLayer_[COLLISION_LAYER_PLAYER][COLLISION_LAYER_ENEMY] = true;
	//collisionLayer_[COLLISION_LAYER_ENEMY][COLLISION_LAYER_ENEMY] = true;
	collisionLayer_[COLLISION_LAYER_PLAYER][COLLISION_LAYER_ITEM] = true;

#ifdef _DEBUG
	shapeRenderFlag_ = false;
#else
	shapeRenderFlag_ = false;
#endif
}

//=========================================================================
// �f�X�g���N�^
//=========================================================================
CollisionManager::~CollisionManager()
{
	for (int i = 0; i < SHAPE_TYPE_MAX; ++i) {
		for (int j = 0; j < SHAPE_TYPE_MAX; ++j) {
			delete checkTable_[i][j];
		}
	}
}

//=========================================================================
// ����������
//=========================================================================
HRESULT CollisionManager::Init()
{
	return S_OK;
}

//=========================================================================
// �X�V����
//=========================================================================
void CollisionManager::Update()
{
	// �ʃ��C���[�̑S�I�u�W�F�N�g�̏Փ˔���
	for (int i = 0; i < COLLISION_LAYER_MAX; ++i) {
		for (int j = i + 1; j < COLLISION_LAYER_MAX; ++j) {
			// �e�[�u���Ŕ�����s�����m�F
			if (collisionLayer_[i][j]) {
				// �C�e���[�^
				list<Shape *>::iterator itrA;
				list<Shape *>::iterator itrB;
				
				// ���X�g���̏Փ˔���
				for (itrA = objectList_[i].begin();
					 itrA != objectList_[i].end(); ) {
					for (itrB = objectList_[j].begin();
						 itrB != objectList_[j].end(); ) {
							 
						// �Փ˔���
						if (CheckCollision((*itrA), (*itrB))) {
							// �e�̎擾
							Scene *sceneA = (*itrA)->GetParent();
							Scene *sceneB = (*itrB)->GetParent();

							// �Փˏ���
							bool eraseFlagA = sceneB->Collision(sceneA);
							bool eraseFlagB = sceneA->Collision(sceneB);

							// ���X�g����폜
							if (eraseFlagA && eraseFlagB) {
								itrA = objectList_[i].erase(itrA);
								objectList_[j].erase(itrB);
								itrB = objectList_[j].begin();
								continue;
							}
							if (eraseFlagA) {
								itrA = objectList_[i].erase(itrA);
								itrB = objectList_[j].begin();
								continue;
							}
							if (eraseFlagB) {
								itrB = objectList_[j].erase(itrB);
								continue;
							}
						}

						itrB++;
					}

					itrA++;
				}
			}
		}
	}

	// ���ꃌ�C���[�̑S�I�u�W�F�N�g�̏Փ˔���
	for (int i = 0; i < COLLISION_LAYER_MAX; ++i) {
		
		// ������s�����m�F
		if (collisionLayer_[i][i]) {
			// �C�e���[�^
			list<Shape *>::iterator itrA;
			list<Shape *>::iterator itrB;
				
			// ���X�g���̏Փ˔���
			for (itrA = objectList_[i].begin();
				 itrA != objectList_[i].end(); ) {
				itrB = itrA;
				itrB++;

				for (; itrB != objectList_[i].end(); ) {
						
					// �Փ˔���
					if (CheckCollision((*itrA), (*itrB))) {
						// �e�̎擾
						Scene *sceneA = (*itrA)->GetParent();
						Scene *sceneB = (*itrB)->GetParent();

						// �Փˏ���
						bool eraseFlagA = sceneB->Collision(sceneA);
						bool eraseFlagB = sceneA->Collision(sceneB);

						// ���X�g����폜
						if (eraseFlagA && eraseFlagB) {
							itrA = objectList_[i].erase(itrA);
							objectList_[i].erase(itrB);
							itrB = itrA;
							itrB++;
							continue;
						}
						if (eraseFlagA) {
							itrA = objectList_[i].erase(itrA);
							itrB = itrA;
							itrB++;
							continue;
						}
						if (eraseFlagB) {
							itrB = objectList_[i].erase(itrB);
							continue;
						}

					}

					itrB++;
				}

				itrA++;
			}
		}
	}


#ifdef _DEBUG
	if (Manager::GetInstance()->GetKeyboard()->GetTriggerKey(DIK_F1)) {
		if (shapeRenderFlag_) {
			shapeRenderFlag_ = false;
		} else {
			shapeRenderFlag_ = true;
		}
	}
	DebugProc::Printf("[F1] : DRAW COLLISION BOX[ON/OFF]\n");
#endif

}

//=========================================================================
// �`�揈��
//=========================================================================
void CollisionManager::Draw()
{
	if (shapeRenderFlag_) {
		// ���C�gOFF
		Manager::GetInstance()->GetRenderer()->GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
		// �e�N�X�`��OFF
		Manager::GetInstance()->GetRenderer()->GetDevice()->SetTexture(0, nullptr);
		for (int count = 0; count < COLLISION_LAYER_MAX; ++count) {
			// �C�e���[�^
			list<Shape *>::iterator itr;

			// ���X�g���̕`�揈��
			for (itr = objectList_[count].begin();
				 itr != objectList_[count].end();
				 ++itr) {
				(*itr)->Draw();
			}
		}
		// ���C�gON
		Manager::GetInstance()->GetRenderer()->GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}

//=========================================================================
// �Փ˔��胊�X�g�̒ǉ�����
//=========================================================================
void CollisionManager::AddList(COLLISION_LAYER layer, Shape *shape)
{
	objectList_[layer].push_back(shape);
}

//=========================================================================
// �Փ˔��胊�X�g�̍폜����
//=========================================================================
void CollisionManager::RemoveList(COLLISION_LAYER layer, Shape *shape)
{
	objectList_[layer].remove(shape);
}

//=========================================================================
// �Փ˔��胊�X�g�̑S�폜����
//=========================================================================
void CollisionManager::AllEraseList()
{
	list<Shape *>::iterator itr;
	for (int count = 0; count < COLLISION_LAYER_MAX; ++count) {
		for (itr = objectList_[count].begin();
			 itr != objectList_[count].end(); ) {
			// ���X�g����폜
			itr = objectList_[count].erase(itr);
		}
	}
}

//=========================================================================
// �Փ˔���I�ʏ���
//=========================================================================
bool CollisionManager::CheckCollision(Shape *shapeA, Shape *shapeB)
{
	return checkTable_[shapeA->GetType()][shapeB->GetType()]->Check(shapeA, shapeB);
}


// End of file