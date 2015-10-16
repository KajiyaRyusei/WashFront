//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// アニメーションデータ
//
// Created by Ryusei Kajiya on 20151009
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

namespace data
{
	//*****************************************************************************
	// 構造体定義
	struct KeyData
	{
	public:
		KeyData() : matrix_animation(nullptr){}
		// ボーンの数だけ
		D3DXMATRIX* matrix_animation;
	};
	struct ObjectAnimationFile
	{
	public:
		ObjectAnimationFile() :
			end_frame(0),
			max_bone(0),
			key(nullptr){}

		u32 end_frame;
		u32 max_bone;
		// フレームの数だけ
		KeyData* key;

		void LoadAnimationFile(const std::string file_name, const u32 mesh_list_size)
		{
			std::ifstream file;
			std::string line;
			file.open(file_name, std::ios::out);
			if( file.fail() == true )
			{
				OutputDebugStringA("ファイル入力にエラーが発生しました\n");
			}

			// 浮動小数点の精度
			file.precision(5);


			// フレームの最大数
			file >> end_frame;
			// ボーン数
			file >> max_bone;

			// フレームの最大数だけキーを確保
			key = new KeyData[end_frame];

			// アニメーション行列の確保
			for( unsigned int frame = 0; frame < end_frame; ++frame )
			{
				key[frame].matrix_animation = new D3DXMATRIX[max_bone];
			}

			for( u32 frame = 0; frame < end_frame; ++frame )
			{
				for( unsigned int mesh_id = 0; mesh_id < mesh_list_size; ++mesh_id )
				{
					for( unsigned int matrix_index = 0; matrix_index < max_bone; ++matrix_index )
					{
						file >> key[frame].matrix_animation[matrix_index]._11 >> key[frame].matrix_animation[matrix_index]._12 >> key[frame].matrix_animation[matrix_index]._13 >> key[frame].matrix_animation[matrix_index]._14
							>> key[frame].matrix_animation[matrix_index]._21 >> key[frame].matrix_animation[matrix_index]._22 >> key[frame].matrix_animation[matrix_index]._23 >> key[frame].matrix_animation[matrix_index]._24
							>> key[frame].matrix_animation[matrix_index]._31 >> key[frame].matrix_animation[matrix_index]._32 >> key[frame].matrix_animation[matrix_index]._33 >> key[frame].matrix_animation[matrix_index]._34
							>> key[frame].matrix_animation[matrix_index]._41 >> key[frame].matrix_animation[matrix_index]._42 >> key[frame].matrix_animation[matrix_index]._43 >> key[frame].matrix_animation[matrix_index]._44;
					}
				}
			}
		}

		void UnLoadAnimationFile()
		{
			// アニメーションデータの削除
			for( u32 frame = 0; frame < end_frame; ++frame )
			{
				SafeDeleteArray(key[frame].matrix_animation);
			}
			SafeDeleteArray(key);
		}
	};
};

