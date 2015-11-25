//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �A�j���[�V�����f�[�^
//
// Created by Ryusei Kajiya on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

namespace data
{
	//************************************
	// �t���[���f�[�^
	struct FrameData
	{
		FrameData() : matrix_animation(nullptr){}
		// �N���X�^�[�̐�����
		D3DXMATRIX* matrix_animation;
	};
	//************************************
	// �A�j���[�V�������b�V���f�[�^
	struct AnimationData
	{
		AnimationData() : frame(nullptr), number_cluster(0){}
		// �N���X�^�[��
		u32 number_cluster;
		// �t���[�����
		FrameData* frame;
	};
	//************************************
	// �A�j���[�V�����t�@�C��
	struct ObjectAnimationFile
	{
	public:
		ObjectAnimationFile() :
			end_frame(0),
			animation(nullptr){}

		u32 end_frame;
		u32 mesh_size;
		// �t���[���̐�����
		AnimationData* animation;

		void LoadAnimationFile(const std::string file_name, const u32 mesh_list_size)
		{
			mesh_size = mesh_list_size;
			std::ifstream file;
			std::string line;
			file.open(file_name, std::ios_base::binary);
			if( file.fail() == true )
			{
				OutputDebugStringA("�t�@�C�����͂ɃG���[���������܂���\n");
			}


			// ���������_�̐��x
			file.precision(5);

			// �t���[���̍ő吔
			file.read((char*)&end_frame, sizeof(u32));

			animation = new AnimationData[mesh_list_size];

			for( u32 mesh_id = 0; mesh_id < mesh_list_size; ++mesh_id )
			{
				file.read((char*)&animation[mesh_id].number_cluster, sizeof(u32));

				animation[mesh_id].frame = new FrameData[end_frame];

				
				for( u32 frame = 0; frame < end_frame; ++frame )
				{
					animation[mesh_id].frame[frame].matrix_animation = new D3DXMATRIX[animation[mesh_id].number_cluster];

					for( u32 matrix_index = 0; matrix_index < animation[mesh_id].number_cluster; ++matrix_index )
					{
						file.read((char*)&animation[mesh_id].frame[frame].matrix_animation[matrix_index], sizeof(D3DXMATRIX));
					}
				}
			}
		}

		void UnLoadAnimationFile()
		{
			// �A�j���[�V�����f�[�^�̍폜
			for( u32 mesh_id = 0; mesh_id < mesh_size; ++mesh_id )
			{
				for( u32 frame = 0; frame < end_frame; ++frame )
				{
					SafeDeleteArray(animation[mesh_id].frame[frame].matrix_animation);
				}
				SafeDeleteArray(animation[mesh_id].frame);
			}
			SafeDeleteArray(animation);
		}
	};
};

