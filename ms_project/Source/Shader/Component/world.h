//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���[���h
//
// Created by Ryusei Kajiya on 20151023
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �N���X�݌v
namespace component
{

	// �ڂ����̓t�@�C���擪�̃R�����g���Q�Ƃ��Ă��������B
	class World
	{
	public:
		World() : _handle_world(nullptr) {}
		virtual ~World() {}

		// �n���h���擾���s���܂��B
		void InitializeWorld(LPD3DXEFFECT effect)
		{
			_handle_world = effect->GetParameterByName(nullptr, "uniform_world");
			ASSERT(_handle_world != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}

		 // �V�F�[�_�[�ɑ��M
		void SendWorld(LPD3DXEFFECT effect) const
		{
			effect->SetMatrix(_handle_world, &_world);
		}

		// �~���[�e�[�^
		void SetWorld(const D3DXMATRIX& world)
		{
			_world = world;
		}

	private:
		D3DXHANDLE _handle_world;
		D3DXMATRIX _world;
	};

};
