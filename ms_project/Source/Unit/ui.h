//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Ui
// 
// Created by Chiharu Kamiyama on 20151012
//
// �ύX�_�F�J�W��
//<�d�l�ύX�ɂ��ȉ��̕�����ύX>
//�ELevelUpMeter���ĂԂƐ�����ɖ��^���̏�ԂŌĂ΂��̂ŁA���x���A�b�v���镔���Ɛ��̗ʂ����߂镔����ʁX�ɂ���
//�E���̗ʂ��擾�ł���悤�ɂ����B
//�E�I�[�o�[�q�[�g��Ԃɂ���悤�ɂ����B
//�E���̗ʂ��A�b�v������֐���ǉ�
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// include
#include "unit.h"

//*****************************************************************************
// �O���錾
class Map;
class Meter;
class MissionUi;
class GameScore;

//*****************************************************************************
// �N���X�݌v
class Ui : public Unit
{
public:

	Ui(Application* application, World* world) : Unit(application, world)
	{
		Initialize();
	}
	virtual ~Ui(){ Finalize(); }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void CollisionUpdate() override{}

	//���X�g�ɓo�^
	virtual void SetList(std::list<Unit*> *list);

	//�}�b�v�Z�b�g�i�}�b�v�̈���̋����A�����v���C���[���W�j
	void SetMap(float max_map_distance, D3DXVECTOR3 init_player_position);

	//�}�b�v�X�V(�����c�v���C���[���W)
	virtual void UpdateMap(D3DXVECTOR3 player_position);

	//�X�R�A�X�V�i�����c�v���C���[�ԍ��A�X�R�A���Z���j
	void UpdateScore(int player_id, int addscore);

	//���[�^�[���ʍX�V�i�����c�v���C���[�ԍ��A���ʌ��Z���j
	void UpdateMeter(int playe_id, float amount);

	//���[�^�[���x���A�b�v�i�����c�v���C���[�ԍ��A���x���i1�`3�j�j
	void LevelUpMeter(int player_id, int level);

	// ���̍ő�ʌ���(�����c�v���C���[�ԍ��A�ő吅��)
	void MaxWaterMeter(int player_id, float max_water);

	// ���̗ʎ擾
	fx32 GetWaterMeter(s32 player_id);

	// �I�[�o�[�q�[�g
	void OverHeat(s32 player_id);

	//���[�^�[���ʍX�V�i�����c�v���C���[�ԍ��A���ʉ��Z���j
	void UpdateMeterAdd(int playe_id, float amount);

	// �X�R�A�̎擾
	s32 GetScore(int player_id);

private:
	Map* _map;
	Meter* _meter;
	MissionUi* _mission;
	GameScore *_game_score;
};