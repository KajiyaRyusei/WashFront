//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// fbx�S�ʁ@�Ftest
// 
// Author : ryusei kajiya
//
// smo:static for model object
// amo:animation for mesh object
// oaf: original animation file
//
// �X�P�[�����O�ƃN�H�[�^�j�I���ƕ��s�ړ������̔����o���B
// �Ƃ肠���������o���L�[��10�t���[�����ƂɁB
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once


//-----------------------------------------------------------------------------
// STL�g�p�錾
//-----------------------------------------------------------------------------
using namespace std;
#include <map>
#include <string>
#include <vector>
#include <algorithm>

#include "Renderer.h"

#include <fbxsdk.h>



//*****************************************************************************
// ���\����
struct VERTEX_ANIMATION
{// FBX���_
	D3DXVECTOR3 position;		// ���W
	D3DXVECTOR3 normal;			// �@��
	D3DXVECTOR2 texcoord;		// �e�N�X�`�����W
	float weight[4];			// �d��
	unsigned char bone_index[4];// �{�[���C���f�b�N�X

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
	float weight[4];				// �d��
	unsigned char bone_index[4];// �{�[���C���f�b�N�X
public:
	ModelBoneWeight(){ ZeroMemory(weight, sizeof(float)* 4); ZeroMemory(bone_index, sizeof(unsigned char)* 4); }
};

//*****************************************************************************
// �N���X�݌v
class KFbxObject
{
public:

	// ������
	void Initialze();
	void Initialze(std::string filePath);

	// �I��
	void Uninit();

	// �`��
	void Draw(D3DXMATRIX world);

	// �I���W�i�����b�V���t�@�C���ۑ�
	void WriteOriginalMeshFileStatic(std::string file_name);
	void WriteOriginalMeshFileWeightAndIndex(std::string file_name);

	// �A�j���[�V�����t�@�C���ۑ�
	void WriteOriginalAnimationFile(std::string file_name);

private:

	FbxManager* _fbx_manager;
	std::vector<MESH_DATA> _mesh_list;
	std::vector<MATERIAL_DATA> _material_list;
	std::map<std::string, int > _material_id_dictionary;
	std::map<std::string, int > _node_id_dictionary;

	// FBX���̓ǂݍ���
	void Read(std::string file_name);

	// FBX�̃o�[�W�����`�F�b�N
	void FbxVersionCheck(FbxImporter* importer);

	// �V�[���Ɋ܂܂�郁�b�V���̉��
	MESH_DATA ParseMesh(FbxMesh* mesh);

	// ���_�C���f�b�N�X���X�g�̎擾
	std::vector<DWORD> GetIndexList(FbxMesh* mesh);

	// ���_���W�̎擾
	std::vector<D3DXVECTOR3> GetPositionList(FbxMesh* mesh, const std::vector<DWORD>& index_list);

	// �@���̎擾
	std::vector<D3DXVECTOR3> GetNormalList(FbxMesh* mesh, const std::vector<DWORD>& index_list);

	// �e�N�X�`�����W�̎擾
	std::vector<D3DXVECTOR2> GetTexcoordList(FbxMesh* mesh, const std::vector<DWORD>& index_list, int no_uv);

	// �d�݂ƃ{�[���C���f�b�N�X�̎擾
	void GetWeightIndex(FbxMesh* mesh, const std::vector<DWORD>& index_list, std::vector<ModelBoneWeight>& bone_weight_list, std::vector<std::string>& bone_node_name_list, std::vector<D3DXMATRIX>& inverse_basepose_matrix_list, std::vector<D3DXMATRIX>& basepose_matrix_list);

	// �V�[���Ɋ܂܂��}�e���A���̉��
	MATERIAL_DATA ParseMaterial(FbxSurfaceMaterial* material);

	// �s��̃R���o�[�g
	D3DXMATRIX D3DXMatrixToFbxMatrix(const FbxAMatrix& fbx_matrix);

	// �E��n������n�ɕϊ�
	void D3DXMatrixRhs2Lhs(D3DXMATRIX& rhs_matrix);

	// ���_�o�b�t�@�̍쐬
	void CreateVertexBuffer(std::vector<VERTEX_ANIMATION>& vertices, LPDIRECT3DVERTEXBUFFER9* vertex_buffer);

	// �C���f�b�N�X�o�b�t�@�̍쐬
	void CreateIndexBuffer(std::vector<DWORD>& indices, LPDIRECT3DINDEXBUFFER9* index_buffer);

	// ���
	void Release();

	FbxScene* _animation_scene;
	FbxLongLong _animation_start_frame;
	FbxLongLong _animation_end_frame;
	FbxLongLong _animation_frame_count;
	std::map<std::string, int > _node_id_dictionary_animation;

	// �A�j���[�V�����̓ǂݍ���
	void LoadAnimation(std::string file_name);

	// �{�[���s��̎擾
	void GetBoneMatrix(FbxLongLong frame, int mesh_id, D3DXMATRIX* out_matrix_list, int matrix_count);

	// �A�j���[�V�����p�ɏ��𔲂��o���B
	void PickupAnimationInformation(int mesh_id);

	// ���b�V���s��̎擾
	void GetMeshMatrix(FbxLongLong frame, int mesh_id, D3DXMATRIX* out_matrix);

	// �V�F�[�_
	LPDIRECT3DVERTEXSHADER9 _vertex_shader;
	// ���_�V�F�[�_�̒萔�e�[�u��
	LPD3DXCONSTANTTABLE _vertex_shader_constant_table;
	// �s�N�Z���V�F�[�_���󂯎��ϐ�
	LPDIRECT3DPIXELSHADER9 _pixel_shader;
	// �s�N�Z���V�F�[�_�̒萔�e�[�u��
	LPD3DXCONSTANTTABLE _pixel_shader_constant_table;

	// ���_�錾
	LPDIRECT3DVERTEXDECLARATION9 _declaration;

	// �V�F�[�_�t�@�C���̓ǂݍ���
	void LoadShader();

	// �V�F�[�_�̉��
	void UnLoadShader();

};