//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// fbx全般　：test
// 
// Author : ryusei kajiya
//
// smo:static for model object
// amo:animation for mesh object
// oaf: original animation file
//
// スケーリングとクォータニオンと平行移動成分の抜き出し。
// とりあえず抜き出しキーは10フレームごとに。
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once


//-----------------------------------------------------------------------------
// STL使用宣言
//-----------------------------------------------------------------------------
using namespace std;
#include <map>
#include <string>
#include <vector>
#include <algorithm>

#include "Renderer.h"

#include <fbxsdk.h>



//*****************************************************************************
// 情報構造体
struct VERTEX_ANIMATION
{// FBX頂点
	D3DXVECTOR3 position;		// 座標
	D3DXVECTOR3 normal;			// 法線
	D3DXVECTOR2 texcoord;		// テクスチャ座標
	float weight[4];			// 重み
	unsigned char bone_index[4];// ボーンインデックス

	VERTEX_ANIMATION() : position(0.f, 0.f, 0.f), normal(0.f, 0.f, 0.f), texcoord(0.f, 0.f){ ZeroMemory(bone_index, sizeof(unsigned char)* 4); ZeroMemory(weight, sizeof(float)* 4); }
	bool operator == (const VERTEX_ANIMATION& src)const{ return memcmp(this, &src, sizeof(VERTEX_ANIMATION)) == 0; }
};

struct MESH_DATA
{
	std::string node_name;
	std::string material_name;
	std::vector<VERTEX_ANIMATION> vertex_list;
	std::vector<DWORD> index_list;
	D3DXMATRIX inverse_mesh_basepose_matrix;
	std::vector<std::string> bone_node_name_list;
	std::vector<D3DXMATRIX> inverse_bone_basepose_matrix_list;
	std::vector<D3DXMATRIX> bone_basepose_matrix_list;
	std::vector<std::vector<D3DXVECTOR3>> inverse_bone_basepose_transform_list;
	std::vector<std::vector<D3DXQUATERNION>> inverse_bone_basepose_quaternion_list;
	std::vector<std::vector<D3DXVECTOR3>> inverse_bone_basepose_scaling_list;
	unsigned int max_key;
	LPDIRECT3DVERTEXBUFFER9 vertex_buffer;
	LPDIRECT3DINDEXBUFFER9 index_buffer;
};

struct MATERIAL_DATA
{
	std::string material_name;
	std::string diffuse_texture_name;
	std::string normal_texture_name;
	std::string specular_texture_name;
	std::string falloff_texture_name;
	std::string reflection_map_texture_name;
};


struct ModelBoneWeight
{
	float weight[4];				// 重み
	unsigned char bone_index[4];// ボーンインデックス
public:
	ModelBoneWeight(){ ZeroMemory(weight, sizeof(float)* 4); ZeroMemory(bone_index, sizeof(unsigned char)* 4); }
};

//*****************************************************************************
// クラス設計
class KFbxObject
{
public:

	// 初期化
	void Initialze();
	void Initialze(std::string filePath);

	// 終了
	void Uninit();

	// 描画
	void Draw(D3DXMATRIX world);

	// オリジナルメッシュファイル保存
	void WriteOriginalMeshFileStatic(std::string file_name);
	void WriteOriginalMeshFileWeightAndIndex(std::string file_name);

	// アニメーションファイル保存
	void WriteOriginalAnimationFile(std::string file_name);

private:

	FbxManager* _fbx_manager;
	std::vector<MESH_DATA> _mesh_list;
	std::vector<MATERIAL_DATA> _material_list;
	std::map<std::string, int > _material_id_dictionary;
	std::map<std::string, int > _node_id_dictionary;

	// FBX情報の読み込み
	void Read(std::string file_name);

	// FBXのバージョンチェック
	void FbxVersionCheck(FbxImporter* importer);

	// シーンに含まれるメッシュの解析
	MESH_DATA ParseMesh(FbxMesh* mesh);

	// 頂点インデックスリストの取得
	std::vector<DWORD> GetIndexList(FbxMesh* mesh);

	// 頂点座標の取得
	std::vector<D3DXVECTOR3> GetPositionList(FbxMesh* mesh, const std::vector<DWORD>& index_list);

	// 法線の取得
	std::vector<D3DXVECTOR3> GetNormalList(FbxMesh* mesh, const std::vector<DWORD>& index_list);

	// テクスチャ座標の取得
	std::vector<D3DXVECTOR2> GetTexcoordList(FbxMesh* mesh, const std::vector<DWORD>& index_list, int no_uv);

	// 重みとボーンインデックスの取得
	void GetWeightIndex(FbxMesh* mesh, const std::vector<DWORD>& index_list, std::vector<ModelBoneWeight>& bone_weight_list, std::vector<std::string>& bone_node_name_list, std::vector<D3DXMATRIX>& inverse_basepose_matrix_list, std::vector<D3DXMATRIX>& basepose_matrix_list);

	// シーンに含まれるマテリアルの解析
	MATERIAL_DATA ParseMaterial(FbxSurfaceMaterial* material);

	// 行列のコンバート
	D3DXMATRIX D3DXMatrixToFbxMatrix(const FbxAMatrix& fbx_matrix);

	// 右手系を左手系に変換
	void D3DXMatrixRhs2Lhs(D3DXMATRIX& rhs_matrix);

	// 頂点バッファの作成
	void CreateVertexBuffer(std::vector<VERTEX_ANIMATION>& vertices, LPDIRECT3DVERTEXBUFFER9* vertex_buffer);

	// インデックスバッファの作成
	void CreateIndexBuffer(std::vector<DWORD>& indices, LPDIRECT3DINDEXBUFFER9* index_buffer);

	// 解放
	void Release();

	FbxScene* _animation_scene;
	FbxLongLong _animation_start_frame;
	FbxLongLong _animation_end_frame;
	FbxLongLong _animation_frame_count;
	std::map<std::string, int > _node_id_dictionary_animation;

	// アニメーションの読み込み
	void LoadAnimation(std::string file_name);

	// ボーン行列の取得
	void GetBoneMatrix(FbxLongLong frame, int mesh_id, D3DXMATRIX* out_matrix_list, int matrix_count);

	// アニメーション用に情報を抜き出す。
	void PickupAnimationInformation(int mesh_id);

	// メッシュ行列の取得
	void GetMeshMatrix(FbxLongLong frame, int mesh_id, D3DXMATRIX* out_matrix);

	// シェーダ
	LPDIRECT3DVERTEXSHADER9 _vertex_shader;
	// 頂点シェーダの定数テーブル
	LPD3DXCONSTANTTABLE _vertex_shader_constant_table;
	// ピクセルシェーダを受け取る変数
	LPDIRECT3DPIXELSHADER9 _pixel_shader;
	// ピクセルシェーダの定数テーブル
	LPD3DXCONSTANTTABLE _pixel_shader_constant_table;

	// 頂点宣言
	LPDIRECT3DVERTEXDECLARATION9 _declaration;

	// シェーダファイルの読み込み
	void LoadShader();

	// シェーダの解放
	void UnLoadShader();

};