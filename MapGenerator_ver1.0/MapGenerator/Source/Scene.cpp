//=============================================================================
//
// �I�u�W�F�N�g�̃X�[�p�[�N���X [Scene.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "Scene.h"
#include "Manager.h"
#include "TextureFactory.h"


//-----------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------
Scene *Scene::first_[PRIORITY_MAX] = {};	// ���X�g�̐擪�A�h���X
Scene *Scene::last_[PRIORITY_MAX] = {};	// ���X�g�̏I�[�A�h���X


//=========================================================================
// �R���X�g���N�^
//=========================================================================
Scene::Scene(int priority) : renderFlag_(true)
{
	// �����o�ϐ��̏�����
	texture_ = nullptr;
	position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	priority_ = priority;
	deleteFlag_ = false;
	type_ = OBJECTTYPE_NONE;

	// ���X�g�ɒǉ�
	LinkList();
}

//=========================================================================
// �f�X�g���N�^
//=========================================================================
Scene::~Scene()
{
	// ���X�g����폜
	UnlinkList();
}

//=========================================================================
// �������
//=========================================================================
void Scene::Release()
{
	// �폜�t���OON
	deleteFlag_ = true;
}

//=========================================================================
// �S�C���X�^���X�̍X�V����
//=========================================================================
void Scene::UpdateAll()
{

	// �X�V���[�v
	for (int count = 0; count < PRIORITY_MAX; ++count) {
		Scene *curr = first_[count];
		Scene *next;

		// �S�C���X�^���X�̍X�V
		while (curr) {
			next = curr->next_;
			curr->Update();  // �X�V����

			// �폜�t���O�̊m�F
			if (curr->deleteFlag_) {
				// �C���X�^���X�̍폜
				delete curr;
			}
			curr = next;  // �J�����g�����炷
		}
	}

}

//=========================================================================
// �S�C���X�^���X�̕`�揈��
//=========================================================================
void Scene::DrawAll()
{

	for (int count = 0; count < PRIORITY_MAX; ++count) {
		Scene *curr = first_[count];
		Scene *next;

		// �S�C���X�^���X�̍X�V
		while (curr) {
			next = curr->next_;  // ���̃|�C���^�ۑ�
			if (curr->renderFlag_) {
				curr->Draw();  // �`�揈��
			}
			curr = next;  // �J�����g�����炷
		}
	}

}

//=========================================================================
// �S�C���X�^���X�̉������
//=========================================================================
void Scene::ReleaseAll()
{

	for (int count = 0; count < PRIORITY_MAX; ++count) {
		Scene *curr = first_[count];
		Scene *next;

		// �S�C���X�^���X�̍X�V
		while (curr) {
			next = curr->next_;  // ���̃|�C���^�ۑ�
			delete curr;  // �������
			curr = next;  // �J�����g�����炷
		}
	}

}

//=========================================================================
// ���X�g�ɒǉ����鏈��
//=========================================================================
void Scene::LinkList()
{

	if (!first_[priority_]) {  // ���X�g����̏ꍇ
		prev_ = nullptr;
		next_ = nullptr;
		first_[priority_] = this;
		last_[priority_] = this;
	} else {  // ���X�g�����݂���ꍇ
		prev_ = last_[priority_];
		next_ = nullptr;
		prev_->next_ = this;
		last_[priority_] = this;
	}

}

//=========================================================================
// ���X�g����폜���鏈��
//=========================================================================
void Scene::UnlinkList()
{

	if (first_[priority_] == last_[priority_]) {  // ���X�g�̗v�f���ЂƂ̏ꍇ
		first_[priority_] = nullptr;
		last_[priority_] = nullptr;
	} else {  // �������݂���ꍇ
		if (this == first_[priority_]) {  // ���X�g�̐擪
			first_[priority_] = next_;
			next_->prev_ = nullptr;
		} else if (this == last_[priority_]) {  // ���X�g�̏I�[
			last_[priority_] = prev_;
			prev_->next_ = nullptr;
		} else {  // ���X�g�̒���
			prev_->next_ = next_;
			next_->prev_ = prev_;
		}
	}

}

//=========================================================================
// �e�N�X�`���ݒ�
//=========================================================================
void Scene::SetTexture(char *fileName)
{
	if (fileName) {
		texture_ = Manager::GetInstance()->GetTextureFactory()->GetTexture(fileName);
	}
}


// End of file