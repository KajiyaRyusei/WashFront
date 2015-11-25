//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
// fbx全般　：test
// 
// Author : ryusei kajiya
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// インクルード
#include "Main.h"
#include "fbx.h"
#include "Manager.h"
#include "Renderer.h"
#include "CameraManager.h"
#include "Camera.h"


//=============================================================================
// 初期化
void KFbxObject::Initialze()
{
	// デバイスの取得

	LoadShader();
	Read("Data/Fbx/golem_kaiten.fbx");

}

void KFbxObject::Initialze(std::string filePath)
{
	LoadShader();
	Read(filePath);
}


//=============================================================================
// 終了
void KFbxObject::Uninit()
{
	UnLoadShader();
	Release();
}
//=============================================================================
// 描画
void KFbxObject::Draw(D3DXMATRIX world)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetRenderer()->GetDevice();

	// カメラの取得
	Camera* camera = Manager::GetInstance()->GetCameraManager()->GetCamera();

	// 行列の取得
	D3DXMATRIX projection_matrix = camera->GetProjectionMtx();
	D3DXMATRIX view_matrix = camera->GetViewMtx();
	D3DXMATRIX world_view_projection_matrix = world * view_matrix * projection_matrix;

	// 行列をセット
	_vertex_shader_constant_table->SetMatrix(device, "WVP", &world_view_projection_matrix);
	_vertex_shader_constant_table->SetMatrix(device, "World", &world);


	// 頂点宣言
	device->SetVertexDeclaration(_declaration);
	// シェーダをセット
	device->SetVertexShader(_vertex_shader);
	device->SetPixelShader(_pixel_shader);

	for( unsigned int mesh_id = 0; mesh_id < _mesh_list.size(); ++mesh_id )
	{
		if( _mesh_list[mesh_id].index_buffer == nullptr || _mesh_list[mesh_id].vertex_buffer == nullptr )
		{
			OutputDebugStringA("メッシュが存在しません\n");
			continue;
		}


		// テクスチャフェッチ
//		device->SetTexture(0, nullptr);

		// マテリアルの設定

		// インデックスバッファのセット
		device->SetIndices(_mesh_list[mesh_id].index_buffer);

		// 頂点の情報を流す
		device->SetStreamSource(0, _mesh_list[mesh_id].vertex_buffer, 0, sizeof(VERTEX_ANIMATION));

		// 描画
		device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _mesh_list[mesh_id].vertex_list.size(), 0, _mesh_list[mesh_id].index_list.size() / 3);
	}



	// シェーダをセット
	device->SetVertexShader(nullptr);
	device->SetPixelShader(nullptr);
}

//=============================================================================
// 読み込み
void KFbxObject::Read(std::string file_name)
{
	_fbx_manager = FbxManager::Create();
	FbxImporter* importer = FbxImporter::Create(_fbx_manager, "my_scene");
	FbxScene* scene = FbxScene::Create(_fbx_manager, file_name.c_str());

	// ファイルの読み込み
	importer->Initialize(file_name.c_str());

	// FBXのバージョンチェック
	FbxVersionCheck(importer);

	//シーンデータの抽出
	importer->Import(scene);

	// ジオメトリの三角化
	FbxGeometryConverter geometryConverter(_fbx_manager);
	geometryConverter.Triangulate(scene, true);

	//// 座標系の変更
	//FbxAxisSystem scene_axis_system = scene->GetGlobalSettings().GetAxisSystem();
	//FbxAxisSystem target_axis_system(FbxAxisSystem::DirectX);
	//if( scene_axis_system != target_axis_system )
	//{
	//	OutputDebugStringA("座標系をDirectXに変更しました。\n");
	//	target_axis_system.ConvertScene(scene);
	//}

	// ノード名からノードIDを取得できるように辞書に登録
	int node_count = scene->GetNodeCount();
	for( int i = 0; i < node_count; ++i )
	{
		FbxNode* node =  scene->GetNode(i);
		_node_id_dictionary.insert({ node->GetName(), i });
	}

	// シーンに含まれるマテリアルの解析
	int material_count = scene->GetMaterialCount();
	_material_list.reserve(material_count);
	for( int i = 0; i < material_count; ++i )
	{
		FbxSurfaceMaterial* material = scene->GetMaterial(i);
		MATERIAL_DATA model_material = ParseMaterial(material);
		_material_list.push_back(model_material);
		_material_id_dictionary.insert({ model_material.material_name, i });
	}

	// シーンに含まれるメッシュの解析
	int mesh_count = scene->GetMemberCount<FbxMesh>();
	_mesh_list.reserve(mesh_count);
	for( int i = 0; i < mesh_count; ++i )
	{
		FbxMesh* mesh = scene->GetMember<FbxMesh>(i);
		_mesh_list.push_back(ParseMesh(mesh));
	}

	// 頂点情報とインデックス情報の作成
	for( auto& mesh : _mesh_list )
	{
		CreateIndexBuffer(mesh.index_list, &mesh.index_buffer);
		CreateVertexBuffer(mesh.vertex_list, &mesh.vertex_buffer);
	}

	// 破棄
	scene->Destroy();

	importer->Destroy();

}


//=============================================================================
// FBXのバージョンチェック
void KFbxObject::FbxVersionCheck(FbxImporter* importer)
{
	// sdkのバージョンを確保する変数
	int sdk_major, sdk_miner, sdk_revision;

	// sdkのバージョンを取得
	FbxManager::GetFileFormatVersion(sdk_major, sdk_miner, sdk_revision);

	// fbxファイルのバージョンを確保する変数
	int file_major, file_miner, file_revision;

	// ファイルのバージョンを取得
	importer->GetFileVersion(file_major, file_miner, file_revision);

	// SDKとﾌｧｲﾙのﾊﾞｰｼﾞｮﾝの確認
	if( sdk_major != file_major || sdk_miner != file_miner || sdk_revision != file_revision )
	{
		OutputDebugStringA("ファイルとSDKのバージョンが違います\n");
	}
}

//=============================================================================
// シーンに含まれるメッシュの解析
MESH_DATA KFbxObject::ParseMesh(FbxMesh* mesh)
{
	if( mesh == nullptr )
	{
		OutputDebugStringA("メッシュが存在しません！\n");
	}

	// メッシュのノード取得
	FbxNode* node = mesh->GetNode();

	if( node->GetMaterialCount() != 1 )
	{
		OutputDebugStringA("マテリアルが１のものしか対応していません!\n");
	}

	MESH_DATA model_mesh;
	// ノードの名前取得
	model_mesh.node_name = node->GetName();
	// ノードのマテリアル0の名前を取得
	model_mesh.material_name = node->GetMaterial(0)->GetName();

	// ペースポーズの行列を作成しておく
	//FbxAMatrix baseposeMatrix = node->EvaluateGlobalTransform();

	// ペースポーズの逆行列を作成しておく
	//FbxAMatrix baseposeInverseMatrix = node->EvaluateGlobalTransform().Inverse();

	// ペースポーズの逆行列をDirectX用に変換
	//model_mesh.inverse_mesh_basepose_matrix = D3DXMatrixToFbxMatrix(baseposeInverseMatrix);

	// インデックスリスト取得
	std::vector<DWORD> index_list = GetIndexList(mesh);

	// 全て展開した状態の頂点取得
	std::vector<D3DXVECTOR3> position_list = GetPositionList(mesh, index_list);
	std::vector<D3DXVECTOR3> normal_list = GetNormalList(mesh, index_list);
	std::vector<D3DXVECTOR2> texcoord_list = GetTexcoordList(mesh, index_list, 0);

	std::vector<ModelBoneWeight> bone_weight_list;
	GetWeightIndex(mesh, index_list, bone_weight_list, model_mesh.bone_node_name_list, model_mesh.inverse_bone_basepose_matrix_list, model_mesh.bone_basepose_matrix_list);

	// 頂点をインターリーブド配列に
	std::vector<VERTEX_ANIMATION> model_vertex_list;
	model_vertex_list.reserve(index_list.size());

	for( unsigned int i = 0; i < index_list.size(); ++i )
	{
		VERTEX_ANIMATION vertex;
		vertex.position = position_list[i];
		vertex.normal = normal_list[i];
		vertex.texcoord = (texcoord_list.size() == 0) ? D3DXVECTOR2(0.0f, 0.0f): texcoord_list[i];

		if( bone_weight_list.size() > 0 )
		{
			
			for( int j = 0; j < 4; ++j )
			{
				vertex.bone_index[j] = bone_weight_list[i].bone_index[j];
				vertex.weight[j] = bone_weight_list[i].weight[j];
			}
		}
		else
		{
			for( int j = 0; j < 4; ++j )
			{
				vertex.bone_index[j] = 0;
				
				if( j == 0)
				{
					vertex.weight[j] = 1.f;
				}
				else
				{
					vertex.weight[j] = 0.f;
				}
			}
		}

		// 頂点を詰め込む
		model_vertex_list.push_back(vertex);
	}

	// 重複頂点を除いてインデックス作成
	std::vector<VERTEX_ANIMATION>& model_vertex_list_optimize = model_mesh.vertex_list;
	model_vertex_list_optimize.reserve(model_vertex_list.size());

	std::vector<DWORD>& model_index_list = model_mesh.index_list;
	model_index_list.reserve(index_list.size());

	for( auto& vertex : model_vertex_list )
	{
		// 重複しているか？
		auto it = std::find(model_vertex_list_optimize.begin(), model_vertex_list_optimize.end(), vertex);
		if( it == model_vertex_list_optimize.end() )
		{// 重複していない
			model_index_list.push_back(model_vertex_list_optimize.size());
			model_vertex_list_optimize.push_back(vertex);
		}
		else
		{// 重複している
			int __w64 index = std::distance(model_vertex_list_optimize.begin(), it);
			model_index_list.push_back(index);
		}
	}

	return model_mesh;
}

//=============================================================================
// 頂点インデックスリストの取得
std::vector<DWORD> KFbxObject::GetIndexList(FbxMesh* mesh)
{
	// あらかじめ三角形化してある
	auto polygon_count = mesh->GetPolygonCount();

	std::vector<DWORD> index_list;
	index_list.reserve(polygon_count * 3);

	for( int i = 0; i < polygon_count; ++i )
	{
		index_list.push_back(mesh->GetPolygonVertex(i, 0));
		index_list.push_back(mesh->GetPolygonVertex(i, 1));
		index_list.push_back(mesh->GetPolygonVertex(i, 2));
	}

	return index_list;
}

//=============================================================================
// 頂点座標の取得
std::vector<D3DXVECTOR3> KFbxObject::GetPositionList(FbxMesh* mesh, const std::vector<DWORD>& index_list)
{
	// コントロールポイントがいわゆる位置座標
	std::vector<D3DXVECTOR3> position_list;
	position_list.reserve(index_list.size());

	for( auto index : index_list )
	{
		FbxVector4 control_point = mesh->GetControlPointAt(index);
		D3DXVECTOR3 temp_position;

		if( control_point[3] == 0.0f )
		{
			temp_position = D3DXVECTOR3(static_cast<float>(control_point[0]), static_cast<float>(control_point[1]), static_cast<float>(control_point[2]));
		}
		else
		{
			temp_position = D3DXVECTOR3(static_cast<float>(control_point[0] / control_point[3]), static_cast<float>(control_point[1] / control_point[3]), static_cast<float>(control_point[2] / control_point[3]));
		}

		position_list.push_back(temp_position);
	}

	return position_list;
}
//=============================================================================
// 法線の取得
std::vector<D3DXVECTOR3> KFbxObject::GetNormalList(FbxMesh* mesh, const std::vector<DWORD>& index_list)
{
	// 法線要素数取得
	int element_count = mesh->GetElementNormalCount();

	if( element_count != 1 )
	{
		OutputDebugStringA("法線要素が1のみ対応しています。\n");
	}

	// 法線の情報を取得
	FbxGeometryElementNormal* element = mesh->GetElementNormal();
	FbxLayerElement::EMappingMode mapping_mode = element->GetMappingMode();
	FbxLayerElement::EReferenceMode reference_mode = element->GetReferenceMode();
	const FbxLayerElementArrayTemplate<int>& index_array = element->GetIndexArray();
	const FbxLayerElementArrayTemplate<FbxVector4>&  direct_array = element->GetDirectArray();

	if( reference_mode != FbxGeometryElement::eDirect && reference_mode != FbxGeometryElement::eIndexToDirect )
	{
		OutputDebugStringA("eDirctかeIndexDirectのみ対応しています。\n");
	}

	std::vector<D3DXVECTOR3> normal_list;
	normal_list.reserve(index_list.size());

	if( mapping_mode == FbxGeometryElement::eByControlPoint )
	{// コントロールポイントでマッピング

		for( auto index : index_list )
		{
			DWORD normal_index = (reference_mode == FbxGeometryElement::eDirect)? index: index_array.GetAt(index);
			FbxVector4 normal = direct_array.GetAt(normal_index);
			normal_list.push_back(D3DXVECTOR3(static_cast<float>(normal[0]), static_cast<float>(normal[1]), static_cast<float>(normal[2])));
		}
	}
	else if( mapping_mode == FbxGeometryElement::eByPolygonVertex )
	{// ポリゴンバーテックス（インデックス）でマッピング

		int index_by_polygon_vertex = 0;
		int polygon_count = mesh->GetPolygonCount();
		for( int i = 0; i < polygon_count; ++i )
		{
			auto polygonSize = mesh->GetPolygonSize(i);

			for( int j = 0; j < polygonSize; ++j )
			{
				DWORD normal_index = (reference_mode == FbxGeometryElement::eDirect) ? index_by_polygon_vertex : index_array.GetAt(index_by_polygon_vertex);
				FbxVector4 normal = direct_array.GetAt(normal_index);

				normal_list.push_back(D3DXVECTOR3(static_cast<float>(normal[0]), static_cast<float>(normal[1]), static_cast<float>(normal[2])));

				++index_by_polygon_vertex;
			}
		}
	}

	return normal_list;
}
//=============================================================================
// テクスチャ座標の取得
std::vector<D3DXVECTOR2> KFbxObject::GetTexcoordList(FbxMesh* mesh, const std::vector<DWORD>& index_list, int no_uv)
{
	std::vector<D3DXVECTOR2> texcoord_list;

	int element_count = mesh->GetElementUVCount();
	if( no_uv + 1 > element_count )
	{
		OutputDebugStringA("このNo.のテクスチャ座標は存在しません。\n");
		return texcoord_list;
	}


	FbxGeometryElementUV* element = mesh->GetElementUV(no_uv);
	FbxLayerElement::EMappingMode mapping_mode = element->GetMappingMode();
	FbxLayerElement::EReferenceMode reference_mode = element->GetReferenceMode();
	const FbxLayerElementArrayTemplate<int>& index_array = element->GetIndexArray();
	const FbxLayerElementArrayTemplate<FbxVector2>&  direct_array = element->GetDirectArray();

	// eDirctかeIndexDirectのみ対応
	if( reference_mode != FbxGeometryElement::eDirect && reference_mode != FbxGeometryElement::eIndexToDirect )
	{
		OutputDebugStringA("eDirctかeIndexDirectのみ対応しています。\n");
	}

	texcoord_list.reserve(index_list.size());

	if( mapping_mode == FbxGeometryElement::eByControlPoint )
	{// コントロールポイントでマッピング
		for( DWORD index : index_list )
		{
			DWORD texcoord_index = (reference_mode == FbxGeometryElement::eDirect)? index: index_array.GetAt(index);
			FbxVector2 texcoord = direct_array.GetAt(texcoord_index);
			// DirectXのUV座標に変換
			texcoord_list.push_back(D3DXVECTOR2(static_cast<float>(texcoord[0]), static_cast<float>(1.f - texcoord[1])));
		}
	}
	else if( mapping_mode == FbxGeometryElement::eByPolygonVertex )
	{// ポリゴンバーテックス（インデックス）でマッピング
		int index_by_polygon_vertex = 0;
		int polygon_count = mesh->GetPolygonCount();

		for( int i = 0; i < polygon_count; ++i )
		{
			int polygon_size = mesh->GetPolygonSize(i);

			for( int j = 0; j < polygon_size; ++j )
			{
				DWORD texcoord_index = (reference_mode == FbxGeometryElement::eDirect)? index_by_polygon_vertex: index_array.GetAt(index_by_polygon_vertex);
				FbxVector2 texcoord = direct_array.GetAt(texcoord_index);
				// DirectXのUV座標に変換
				texcoord_list.push_back(D3DXVECTOR2(static_cast<float>(texcoord[0]), static_cast<float>(1.f - texcoord[1])));

				++index_by_polygon_vertex;
			}
		}
	}

	return texcoord_list;
}

//=============================================================================
// 重みとボーンインデックスの取得
void KFbxObject::GetWeightIndex(FbxMesh* mesh, const std::vector<DWORD>& index_list, std::vector<ModelBoneWeight>& bone_weight_list, std::vector<std::string>& bone_node_name_list, std::vector<D3DXMATRIX>& inverse_basepose_matrix_list, std::vector<D3DXMATRIX>& basepose_matrix_list)
{
	int skin_count = mesh->GetDeformerCount(FbxDeformer::eSkin);
	if( skin_count == 0 )
	{
		OutputDebugStringA("スキンが存在しません。\n");
		return;
	}
	if( skin_count > 1 )
	{
		OutputDebugStringA("スキンが1つの場合にしか対応しません\n");
		return;
	}

	int control_points_count = mesh->GetControlPointsCount();
	using TmpWeight = std::pair<int, float>;
	std::vector<std::vector<TmpWeight>> tmp_bone_weight_list(control_points_count);

	FbxSkin* skin = static_cast<FbxSkin*>(mesh->GetDeformer(0, FbxDeformer::eSkin));
	int cluster_count = skin->GetClusterCount();

	for( int i = 0; i < cluster_count; ++i )
	{
		auto cluster = skin->GetCluster(i);

		if( cluster->GetLinkMode() != FbxCluster::eNormalize )
		{
			OutputDebugStringA("eNormalizeしか対応しません。\n");
			return;
		}

		std::string name = cluster->GetLink()->GetName();

		bone_node_name_list.push_back(cluster->GetLink()->GetName());

		int index_count = cluster->GetControlPointIndicesCount();
		int* indices = cluster->GetControlPointIndices();
		double* weights = cluster->GetControlPointWeights();

		for( int j = 0; j < index_count; ++j )
		{
			auto controlPointIndex = indices[j];
			tmp_bone_weight_list[controlPointIndex].push_back({ i, static_cast<float>(weights[j]) });
		}

		
		FbxNode* bone_node = cluster->GetLink();
		FbxAMatrix baseposeMatrix = cluster->GetLink()->EvaluateGlobalTransform(0);

		D3DXMATRIX basepose_matrix = D3DXMatrixToFbxMatrix(baseposeMatrix);
		D3DXMATRIX inverse_basepose_matrix;

		//D3DXMatrixRhs2Lhs(basepose_matrix);

		// ペースポーズの逆行列を作成しておく
		D3DXMatrixInverse(&inverse_basepose_matrix, nullptr, &basepose_matrix);

		D3DXMATRIX test_matrix = inverse_basepose_matrix * basepose_matrix;


		// ベースポーズを突っ込む
		basepose_matrix_list.push_back(basepose_matrix);

		// 突っ込む
		inverse_basepose_matrix_list.push_back(inverse_basepose_matrix);
	}

	// コントロールポイントに対応したウェイトを作成
	std::vector<ModelBoneWeight> bone_weight_list_control_points;
	for( auto& tmp_bone_weight : tmp_bone_weight_list )
	{
		// ウェイトの大きさでソート
		std::sort(tmp_bone_weight.begin(), tmp_bone_weight.end(), [](const TmpWeight& weightA, const TmpWeight& weightB){ return weightA.second > weightB.second; });

		// 1頂点に4つより多くウェイトが割り振られているなら影響が少ないものは無視する
		while( tmp_bone_weight.size() > 4 )
		{
			tmp_bone_weight.pop_back();
		}

		// 4つに満たない場合はダミーを挿入
		while( tmp_bone_weight.size() < 4 )
		{
			tmp_bone_weight.push_back({ 0, 0.0f });
		}

		ModelBoneWeight weight;
		float total = 0.0f;
		for( int i = 0; i < 4; ++i )
		{
			weight.bone_index[i] = tmp_bone_weight[i].first;
			weight.weight[i] = tmp_bone_weight[i].second;

			total += tmp_bone_weight[i].second;
		}

		for( int i = 0; i < 4; ++i )
		{// ウェイトの正規化
			weight.weight[i] /= total;
		}

		bone_weight_list_control_points.push_back(weight);
	}

	// インデックスで展開
	for( auto index : index_list )
	{
		bone_weight_list.push_back(bone_weight_list_control_points[index]);
	}
}

//=============================================================================
// シーンに含まれるマテリアルの解析
MATERIAL_DATA KFbxObject::ParseMaterial(FbxSurfaceMaterial* material)
{
	MATERIAL_DATA model_material;
	// マテリアル名の取得
	model_material.material_name = material->GetName();

	const FbxImplementation* implementation = GetImplementation(material, FBXSDK_IMPLEMENTATION_CGFX);
	if( implementation  == nullptr)
	{// CGFXのみ対応
		OutputDebugStringA("CGFXのみ対応\n");
		return model_material;
	}

	const FbxBindingTable* root_table = implementation->GetRootTable();
	int entry_count = root_table->GetEntryCount();

	for( int i = 0; i < entry_count; ++i )
	{
		FbxBindingTableEntry entry = root_table->GetEntry(i);

		FbxProperty fbx_property = material->FindPropertyHierarchical(entry.GetSource());
		if( !fbx_property.IsValid() )
		{
			fbx_property = material->RootProperty.FindHierarchical(entry.GetSource());
		}

		int texture_count = fbx_property.GetSrcObjectCount<FbxTexture>();
		if( texture_count > 0 )
		{
			std::string source = entry.GetSource();

			for( int j = 0; j < fbx_property.GetSrcObjectCount<FbxFileTexture>(); ++j )
			{
				FbxFileTexture* texture = fbx_property.GetSrcObject<FbxFileTexture>(j);
				std::string texture_name = texture->GetFileName();
				texture_name = texture_name.substr(texture_name.find_last_of('/') + 1);

				if( source == "Maya|DiffuseTexture" )
				{
					model_material.diffuse_texture_name = texture_name;
				}
				else if( source == "Maya|NormalTexture" )
				{
					model_material.normal_texture_name = texture_name;
				}
				else if( source == "Maya|SpecularTexture" )
				{
					model_material.specular_texture_name = texture_name;
				}
				else if( source == "Maya|FalloffTexture" )
				{
					model_material.falloff_texture_name = texture_name;
				}
				else if( source == "Maya|ReflectionMapTexture" )
				{
					model_material.reflection_map_texture_name = texture_name;
				}
			}
		}
	}

	return model_material;
}

//=============================================================================
// 行列のコンバート
D3DXMATRIX KFbxObject::D3DXMatrixToFbxMatrix(const FbxAMatrix& fbx_matrix)
{
	D3DXMATRIX return_matrix;

	return_matrix._11 = static_cast<float>(fbx_matrix.Get(0, 0));
	return_matrix._12 = static_cast<float>(fbx_matrix.Get(0, 1));
	return_matrix._13 = static_cast<float>(fbx_matrix.Get(0, 2));
	return_matrix._14 = static_cast<float>(fbx_matrix.Get(0, 3));
	return_matrix._21 = static_cast<float>(fbx_matrix.Get(1, 0));
	return_matrix._22 = static_cast<float>(fbx_matrix.Get(1, 1));
	return_matrix._23 = static_cast<float>(fbx_matrix.Get(1, 2));
	return_matrix._24 = static_cast<float>(fbx_matrix.Get(1, 3));
	return_matrix._31 = static_cast<float>(fbx_matrix.Get(2, 0));
	return_matrix._32 = static_cast<float>(fbx_matrix.Get(2, 1));
	return_matrix._33 = static_cast<float>(fbx_matrix.Get(2, 2));
	return_matrix._34 = static_cast<float>(fbx_matrix.Get(2, 3));
	return_matrix._41 = static_cast<float>(fbx_matrix.Get(3, 0));
	return_matrix._42 = static_cast<float>(fbx_matrix.Get(3, 1));
	return_matrix._43 = static_cast<float>(fbx_matrix.Get(3, 2));
	return_matrix._44 = static_cast<float>(fbx_matrix.Get(3, 3));

	return return_matrix;
}

//=============================================================================
// 右手系を左手系に変換
void KFbxObject::D3DXMatrixRhs2Lhs(D3DXMATRIX& rhs_matrix)
{
	//rhs_matrix._31 *= -1;
	//rhs_matrix._32 *= -1;
	rhs_matrix._33 *= -1;
	//rhs_matrix._34 *= -1;
	//rhs_matrix._43 *= -1;
}

//=============================================================================
// 解放
void KFbxObject::Release()
{
	_fbx_manager->Destroy();
	for(auto& mesh : _mesh_list )
	{
		SafeRelease(mesh.index_buffer);
		SafeRelease(mesh.vertex_buffer);
	}
}

//=============================================================================
// シェーダの読み込み
void KFbxObject::LoadShader()
{
	HRESULT handle_result = S_OK;
	LPD3DXBUFFER buffer, error;

	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetRenderer()->GetDevice();

	
	// 頂点シェーダをコンパイル
	handle_result = D3DXCompileShaderFromFile("./Source/PerPixelLighting.fx",nullptr,nullptr,"VS","vs_2_0",0,&buffer,&error,&_vertex_shader_constant_table);

	if( FAILED(handle_result) )
	{
		OutputDebugStringA((char*)error->GetBufferPointer());
		SafeRelease(error);
		return;
	}

	handle_result = device->CreateVertexShader(static_cast<DWORD*>(buffer->GetBufferPointer()),&_vertex_shader);
	SafeRelease(buffer);
	if( FAILED(handle_result) )
	{
		return ;
	}

	// ピクセルシェーダをコンパイル
	handle_result = D3DXCompileShaderFromFile("./Source/PerPixelLighting.fx", nullptr, nullptr, "PS", "ps_2_0", 0, &buffer, &error, &_pixel_shader_constant_table);

	if( FAILED(handle_result) )
	{
		OutputDebugStringA((char*)error->GetBufferPointer());
		SafeRelease(error);
		return;
	}

	handle_result = device->CreatePixelShader(static_cast<DWORD*>(buffer->GetBufferPointer()), &_pixel_shader);
	
	SafeRelease(buffer);
	if( FAILED(handle_result) )
	{
		return;
	}
	
	// 頂点宣言の作成
	D3DVERTEXELEMENT9	vertex_element[] = {
		{ 0, sizeof(float) * 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, sizeof(float) * 3, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		{ 0, sizeof(float) * 6, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		{ 0, sizeof(float) * 8, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0 },
		{ 0, sizeof(float) * 12, D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0 },
		D3DDECL_END()
	};

	device->CreateVertexDeclaration(vertex_element, &_declaration);


}
//=============================================================================
// シェーダの解放
void KFbxObject::UnLoadShader()
{
	SafeRelease(_vertex_shader_constant_table);
	SafeRelease(_vertex_shader);
	SafeRelease(_pixel_shader_constant_table);
	SafeRelease(_pixel_shader);
	SafeRelease(_declaration);
}

//=============================================================================
// 頂点バッファの作成
void KFbxObject::CreateVertexBuffer(std::vector<VERTEX_ANIMATION>& vertices, LPDIRECT3DVERTEXBUFFER9* vertex_buffer)
{
	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetRenderer()->GetDevice();

	if( FAILED(device->CreateVertexBuffer(sizeof(VERTEX_ANIMATION)*vertices.size(),
		//D3DUSAGE_SOFTWAREPROCESSING, NULL, D3DPOOL_MANAGED, vertex_buffer, NULL)) )
		D3DUSAGE_WRITEONLY, NULL, D3DPOOL_MANAGED, vertex_buffer, NULL)) )
	{
		OutputDebugStringA("頂点バッファの確保に失敗しました\n");
		return;
	}

	VERTEX_ANIMATION* vertex;
	(*vertex_buffer)->Lock(0, 0, (void**)&vertex, 0);

	//頂点データの読み込み
	for( DWORD i = 0; i < vertices.size(); i++ )
	{
		vertex[i] = vertices[i];
	}

	(*vertex_buffer)->Unlock();
}

//=============================================================================
// インデックスバッファの作成
void KFbxObject::CreateIndexBuffer(std::vector<DWORD>& indices, LPDIRECT3DINDEXBUFFER9* index_buffer)
{
	LPDIRECT3DDEVICE9 device = Manager::GetInstance()->GetRenderer()->GetDevice();

	if( FAILED(device->CreateIndexBuffer(sizeof(DWORD)*indices.size(), D3DUSAGE_WRITEONLY, D3DFMT_INDEX32, D3DPOOL_MANAGED, index_buffer, NULL)) )
	{
		OutputDebugStringA("インデックスバッファの確保に失敗しました\n");
	}

	DWORD* index;
	(*index_buffer)->Lock(0, 0, (void**)&index, 0);

	for( DWORD i = 0; i < indices.size(); i++ )
	{
		index[i] = indices[i];
	}

	(*index_buffer)->Unlock();
}

//=============================================================================
// アニメーションの読み込み
void KFbxObject::LoadAnimation(std::string file_name)
{
	FbxImporter* importer = FbxImporter::Create(_fbx_manager, "animation_scene");
	_animation_scene = FbxScene::Create(_fbx_manager, file_name.c_str());

	// ファイルの読み込み
	importer->Initialize(file_name.c_str());

	// FBXのバージョンチェック
	FbxVersionCheck(importer);

	//シーンデータの抽出
	importer->Import(_animation_scene);

	//// 座標系の変更
	//FbxAxisSystem scene_axis_system = _animation_scene->GetGlobalSettings().GetAxisSystem();
	//int spin = 0;
	//_animation_scene->GetGlobalSettings().GetAxisSystem().GetUpVector(spin);
	//int front = 0;
	//_animation_scene->GetGlobalSettings().GetAxisSystem().GetFrontVector(front);
	//if( FbxAxisSystem::eYAxis == spin )
	//{
	//	OutputDebugStringA("Yが上です。\n");
	//}
	//if( FbxAxisSystem::eZAxis == spin )
	//{
	//	OutputDebugStringA("Zが上です。\n");
	//}
	//if( FbxAxisSystem::eXAxis == spin )
	//{
	//	OutputDebugStringA("Xが上です。\n");
	//}

	//if( FbxAxisSystem::eParityEven == front )
	//{
	//	OutputDebugStringA("偶数\n");
	//}
	//if( FbxAxisSystem::eParityOdd == front )
	//{
	//	OutputDebugStringA("Zが前です。\n");
	//}

	//FbxAxisSystem target_axis_system(FbxAxisSystem::DirectX);
	//if( scene_axis_system != target_axis_system )
	//{
	//	OutputDebugStringA("座標系をDirectXに変更しました。\n");
	//	target_axis_system.ConvertScene(_animation_scene);
	//}

	// アニメーションフレーム数取得
	int animation_stack_count = importer->GetAnimStackCount();
	if( animation_stack_count != 1)
	{
		OutputDebugStringA("アニメーション情報が含まれておりません。\n");
	}

	// 1版目のタイムラインからのみ取得
	FbxTakeInfo* take_info = importer->GetTakeInfo(0);

	FbxTime import_offset = take_info->mImportOffset;
	FbxTime start_time = take_info->mLocalTimeSpan.GetStart();
	FbxTime stop_time = take_info->mLocalTimeSpan.GetStop();

	_animation_start_frame = (import_offset.Get() + start_time.Get()) / FbxTime::GetOneFrameValue(FbxTime::eFrames60);
	_animation_end_frame = (import_offset.Get() + stop_time.Get()) / FbxTime::GetOneFrameValue(FbxTime::eFrames60);
	_animation_frame_count = 0;

	importer->Destroy();

	// ノード名からノードIDを取得できるように辞書に登録
	int node_count = _animation_scene->GetNodeCount();

	for( int i = 0; i < node_count; ++i )
	{
		auto fbxNode = _animation_scene->GetNode(i);
		_node_id_dictionary_animation.insert({ fbxNode->GetName(), i });
	}
}

//=============================================================================
// ボーン行列の取得
void KFbxObject::GetBoneMatrix(FbxLongLong frame, int mesh_id, D3DXMATRIX* out_matrix_list, int matrix_count)
{
	MESH_DATA& model_mesh = _mesh_list[mesh_id];

	if( model_mesh.bone_node_name_list.size() == 0 )
	{
		D3DXMatrixIdentity(&out_matrix_list[0]);
		return;
	}

	if( model_mesh.bone_node_name_list.size() >= static_cast<unsigned int>(matrix_count) )
	{
		OutputDebugStringA("ボーンの数が格納用行列の数を超えています。\n");
	}

	FbxTime time;
	time.Set(FbxTime::GetOneFrameValue(FbxTime::eFrames60) * frame);

	for(unsigned int i = 0; i < model_mesh.bone_node_name_list.size(); ++i )
	{
		std::string& bone_node_name = model_mesh.bone_node_name_list[i];
		int bone_node_id = _node_id_dictionary_animation.at(bone_node_name);
		FbxNode* bone_node = _animation_scene->GetNode(bone_node_id);

		FbxAMatrix& bone_matrix = bone_node->EvaluateGlobalTransform(time);
		FbxVector4 bone_scaling = bone_node->EvaluateGlobalTransform(time).GetS();
		FbxQuaternion bone_rotation = bone_node->EvaluateGlobalTransform(time).GetQ();
		FbxVector4 bone_translation = bone_node->EvaluateGlobalTransform(time).GetT();

		
		
		D3DXMATRIX& out_matrix = out_matrix_list[i];
		D3DXMATRIX scaling_matrix, rotation_matrix, translation_matrix;
		D3DXMatrixScaling(&scaling_matrix, bone_scaling[0], bone_scaling[1], bone_scaling[2]);
		//D3DXMatrixRhs2Lhs(scaling_matrix);
		D3DXMatrixRotationQuaternion(&rotation_matrix, &D3DXQUATERNION(bone_rotation[0], bone_rotation[1], bone_rotation[2], bone_rotation[3]));
		//D3DXMatrixRhs2Lhs(rotation_matrix);
		D3DXMatrixTranslation(&translation_matrix, bone_translation[0], bone_translation[1], bone_translation[2]);
		//D3DXMatrixRhs2Lhs(translation_matrix);


		D3DXMATRIX test_matrix = D3DXMatrixToFbxMatrix(bone_matrix);

		//test_matrix = scaling_matrix * rotation_matrix * translation_matrix;

		//D3DXMatrixRhs2Lhs(test_matrix);


		//D3DXMatrixRhs2Lhs(scaling_matrix);
		//D3DXMatrixRhs2Lhs(rotation_matrix);
		//D3DXMatrixRhs2Lhs(translation_matrix);

		//test_matrix = scaling_matrix * rotation_matrix * translation_matrix;

		// 取得した行列にベースポーズの逆行列をかける
		D3DXMATRIX baseposeMatrix = model_mesh.bone_basepose_matrix_list[i];
		D3DXMATRIX invBaseposeMatrix = model_mesh.inverse_bone_basepose_matrix_list[i];
		out_matrix = invBaseposeMatrix * test_matrix;

		//D3DXMatrixRhs2Lhs(out_matrix);
	}
}

//=============================================================================
// メッシュ行列の取得
void KFbxObject::GetMeshMatrix(FbxLongLong frame, int mesh_id, D3DXMATRIX* out_matrix)
{
	MESH_DATA& model_mesh = _mesh_list[mesh_id];

	auto it = _node_id_dictionary_animation.find(model_mesh.node_name);
	if( it == this->_node_id_dictionary_animation.end() )
	{
		D3DXMatrixIdentity(out_matrix);
		return;
	}

	int mesh_node_id = it->second;
	FbxNode* mesh_node = _animation_scene->GetNode(mesh_node_id);

	FbxTime time;
	time.Set(FbxTime::GetOneFrameValue(FbxTime::eFrames60) * static_cast<FbxLongLong>(frame));

	FbxAMatrix& mesh_matrix = mesh_node->EvaluateGlobalTransform(time);

	*out_matrix = D3DXMatrixToFbxMatrix(mesh_matrix);

	// 取得した行列にベースポーズの逆行列をかける
	*out_matrix *= model_mesh.inverse_mesh_basepose_matrix;
}

//=============================================================================
// アニメーション用に情報を抜き出す。
void KFbxObject::PickupAnimationInformation(int mesh_id)
{
	MESH_DATA& model_mesh = _mesh_list[mesh_id];

	// メッシュに依存するボーンの数分確保
	model_mesh.inverse_bone_basepose_quaternion_list.resize(model_mesh.bone_node_name_list.size());
	model_mesh.inverse_bone_basepose_transform_list.resize(model_mesh.bone_node_name_list.size());
	model_mesh.inverse_bone_basepose_scaling_list.resize(model_mesh.bone_node_name_list.size());

	// キーの分だけ好きなだけ確保
	static const unsigned int kIntervalKey = 10;
	model_mesh.max_key = _animation_end_frame / kIntervalKey;
	for( unsigned int i = 0; i < model_mesh.bone_node_name_list.size(); ++i )
	{
		model_mesh.inverse_bone_basepose_quaternion_list[i].resize(model_mesh.max_key);
		model_mesh.inverse_bone_basepose_transform_list[i].resize(model_mesh.max_key);
		model_mesh.inverse_bone_basepose_scaling_list[i].resize(model_mesh.max_key);
	}


	FbxLongLong frame = 0;
	for( unsigned int key = 0; key < model_mesh.max_key; ++key, frame += kIntervalKey )
	{
		FbxTime time;
		time.Set(FbxTime::GetOneFrameValue(FbxTime::eFrames60) * frame);

		for( unsigned int i = 0; i < model_mesh.bone_node_name_list.size(); ++i )
		{
			std::string& bone_node_name = model_mesh.bone_node_name_list[i];
			int bone_node_id = _node_id_dictionary_animation.at(bone_node_name);
			FbxNode* bone_node = _animation_scene->GetNode(bone_node_id);

			// スケーリング成分抜き出し
			FbxDouble3 scaling = bone_node->EvaluateGlobalTransform(time).GetS();
			model_mesh.inverse_bone_basepose_scaling_list[i][key] = D3DXVECTOR3(scaling[0], scaling[1], scaling[2]);
			// クォータニオン成分抜き出し
			FbxDouble4 quaternion = bone_node->EvaluateGlobalTransform(time).GetQ();
			model_mesh.inverse_bone_basepose_quaternion_list[i][key] = D3DXQUATERNION(quaternion[0], quaternion[1], quaternion[2], quaternion[3]);
			// 回転成分?抜き出し
			FbxDouble3 rotation = bone_node->EvaluateGlobalTransform(time).GetR();
			// 平行移動成分抜き出し
			FbxDouble3 transform = bone_node->EvaluateGlobalTransform(time).GetT();
			model_mesh.inverse_bone_basepose_transform_list[i][key] = D3DXVECTOR3(transform[0], transform[1], transform[2]);
		}
	}

}