//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// アニメーションデータ
//
// Created by Ryusei Kajiya on 20151111
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

namespace data
{
	//************************************
	// フレームデータ
	struct FrameData
	{
		FrameData() : matrix_animation(nullptr){}
		// クラスターの数だけ
		D3DXMATRIX* matrix_animation;
	};
	//************************************
	// アニメーションメッシュデータ
	struct AnimationData
	{
		AnimationData() : frame(nullptr), number_cluster(0){}
		// クラスター数
		u32 number_cluster;
		// フレーム情報
		FrameData* frame;
	};
	//************************************
	// アニメーションファイル
	struct ObjectAnimationFile
	{
	public:
		ObjectAnimationFile() :
			end_frame(0),
			animation(nullptr){}

		u32 end_frame;
		u32 mesh_size;
		// フレームの数だけ
		AnimationData* animation;

		void LoadAnimationFile(const std::string file_name, const u32 mesh_list_size)
		{
			mesh_size = mesh_list_size;
			std::ifstream file;
			std::string line;
			file.open(file_name, std::ios_base::binary);
			if( file.fail() == true )
			{
				OutputDebugStringA("ファイル入力にエラーが発生しました\n");
			}


			// 浮動小数点の精度
			file.precision(5);

			// フレームの最大数
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
			// アニメーションデータの削除
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

