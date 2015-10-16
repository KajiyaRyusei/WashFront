//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ���[���h�r���[�v���W�F�N�V����
//
// Created by Ryusei Kajiya on 20151009
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
	class WorldViewProjection
	{
	public:
		WorldViewProjection() : _handle_world_view_projection(nullptr) {}
		virtual ~WorldViewProjection() {}

		// �n���h���擾���s���܂��B
		void InitializeWorldViewProjection(LPD3DXEFFECT effect)
		{
			_handle_world_view_projection = effect->GetParameterByName(nullptr, "uniform_world_view_projection");
			ASSERT(_handle_world_view_projection != nullptr, "�n���h���ǂݍ��݂Ɏ��s���܂����B");
		}

		 // �V�F�[�_�[�ɑ��M
		void SendWorldViewProjection(LPD3DXEFFECT effect) const
		{
			effect->SetMatrix(_handle_world_view_projection, &_world_view_projection);
		}

		// �~���[�e�[�^
		void SetWorldViewProjection(const D3DXMATRIX& world_view_projection)
		{
			_world_view_projection = world_view_projection;
		}

	private:
		D3DXHANDLE _handle_world_view_projection;
		D3DXMATRIX _world_view_projection;
	};

};
