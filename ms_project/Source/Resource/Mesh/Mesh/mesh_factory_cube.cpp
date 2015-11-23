//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// キューブメッシュ作成
// 
// Created by Ryusei Kajiya on 20151103
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "mesh_factory_cube.h"
#include "Algorithm/often_use.h"

//=============================================================================
// 作成
MeshBuffer* MeshFactoryCube::Create(RendererDevice* renderer_device)
{
	MeshBuffer* mesh = new MeshBuffer(renderer_device);

	// 頂点バッファの作成
	// 共有データの設定
	mesh->RegisterVertexCount(0, 30);
	mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0);
	mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0);
	mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0);
	mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0);
	mesh->RegisterVertexInformation(0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0);

	// 頂点バッファの作成
	mesh->CreateVertexBuffer(D3DUSAGE_WRITEONLY, D3DPOOL_MANAGED);

	// 頂点データの設定
	mesh->RegisterPrimitiveCount(1);
	mesh->SetPrimitiveCount(0, 28);

	// 頂点情報の作成
	VERTEX_CUBE* vertex = nullptr;
	mesh->GetVertexBuffer(0)->Lock(0, 0, (void**)&vertex, 0);

	// 座標
	D3DXVECTOR3 ltf(1.f, 1.f, 1.f);
	vertex[0].position = ltf;
	vertex[15].position = ltf;
	vertex[16].position = ltf;
	vertex[23].position = ltf;

	D3DXVECTOR3 rtf(-1.f, 1.f, 1.f);
	vertex[1].position = rtf;
	vertex[5].position = rtf;
	vertex[21].position = rtf;
	vertex[22].position = rtf;

	D3DXVECTOR3 lbf(1.f, -1.f, 1.f);
	vertex[2].position = lbf;
	vertex[9].position = lbf;
	vertex[10].position = lbf;
	vertex[17].position = lbf;

	D3DXVECTOR3 rbf(-1.f, -1.f, 1.f);
	vertex[3].position = rbf;
	vertex[4].position = rbf;
	vertex[11].position = rbf;

	D3DXVECTOR3 rtb(-1.f, 1.f, -1.f);
	vertex[7].position = rtb;
	vertex[8].position = rtb;
	vertex[24].position = rtb;
	vertex[28].position = rtb;

	D3DXVECTOR3 rbb(-1.f, -1.f, -1.f);
	vertex[6].position = rbb;
	vertex[13].position = rbb;
	vertex[14].position = rbb;
	vertex[29].position = rbb;

	D3DXVECTOR3 ltb(1.f, 1.f, -1.f);
	vertex[18].position = ltb;
	vertex[25].position = ltb;
	vertex[26].position = ltb;
	
	D3DXVECTOR3 lbb(1.f, -1.f, -1.f);
	vertex[12].position = lbb;
	vertex[19].position = lbb;
	vertex[20].position = lbb;
	vertex[27].position = lbb;

	// テクスチャ
	D3DXVECTOR2 zz(0.f, 0.f);
	D3DXVECTOR2 oz(1.f, 0.f);
	D3DXVECTOR2 zo(0.f, 1.f);
	D3DXVECTOR2 oo(1.f, 1.f);

	vertex[0].texcoord = zz;
	vertex[1].texcoord = oz;
	vertex[2].texcoord = zo;
	vertex[3].texcoord = oo;

	vertex[4].texcoord = zz;
	vertex[5].texcoord = oz;
	vertex[6].texcoord = zo;
	vertex[7].texcoord = oo;
	vertex[8].texcoord = oo;

	vertex[9].texcoord = zz;
	vertex[10].texcoord = zz;
	vertex[11].texcoord = oz;
	vertex[12].texcoord = zo;
	vertex[13].texcoord = oo;

	vertex[14].texcoord = zz;
	vertex[15].texcoord = zz;
	vertex[16].texcoord = zz;
	vertex[17].texcoord = oz;
	vertex[18].texcoord = zo;
	vertex[19].texcoord = oo;

	vertex[20].texcoord = zz;
	vertex[21].texcoord = zz;
	vertex[22].texcoord = zz;
	vertex[23].texcoord = oz;
	vertex[24].texcoord = zo;

	vertex[25].texcoord = oo;
	vertex[26].texcoord = zz;
	vertex[27].texcoord = oz;
	vertex[28].texcoord = zo;
	vertex[29].texcoord = oo;

	mesh->GetVertexBuffer(0)->Unlock();
	mesh->SetPrimitiveType(D3DPT_TRIANGLESTRIP);

	NormalComputeSlanting(mesh);

	TangentCompute(mesh);

	return mesh;
}

//=============================================================================
// 法線作成
void MeshFactoryCube::NormalComputeSlanting(MeshBuffer* mesh)
{
	// 頂点情報の作成
	VERTEX_CUBE* vertex = nullptr;
	mesh->GetVertexBuffer(0)->Lock(0, 0, (void**)&vertex, 0);

	// 座標
	D3DXVECTOR3 ltf(1.f, 1.f, 1.f);
	vertex[0].normal = ltf;
	vertex[15].normal = ltf;
	vertex[16].normal = ltf;
	vertex[23].normal = ltf;

	D3DXVECTOR3 rtf(-1.f, 1.f, 1.f);
	vertex[1].normal = rtf;
	vertex[5].normal = rtf;
	vertex[21].normal = rtf;
	vertex[22].normal = rtf;

	D3DXVECTOR3 lbf(1.f, -1.f, 1.f);
	vertex[2].normal = lbf;
	vertex[9].normal = lbf;
	vertex[10].normal = lbf;
	vertex[17].normal = lbf;

	D3DXVECTOR3 rbf(-1.f, -1.f, 1.f);
	vertex[3].normal = rbf;
	vertex[4].normal = rbf;
	vertex[11].normal = rbf;

	D3DXVECTOR3 rtb(-1.f, 1.f, -1.f);
	vertex[7].normal = rtb;
	vertex[8].normal = rtb;
	vertex[24].normal = rtb;
	vertex[28].normal = rtb;

	D3DXVECTOR3 rbb(-1.f, -1.f, -1.f);
	vertex[6].normal = rbb;
	vertex[13].normal = rbb;
	vertex[14].normal = rbb;
	vertex[29].normal = rbb;

	D3DXVECTOR3 ltb(1.f, 1.f, -1.f);
	vertex[18].normal = ltb;
	vertex[25].normal = ltb;
	vertex[26].normal = ltb;

	D3DXVECTOR3 lbb(1.f, -1.f, -1.f);
	vertex[12].normal = lbb;
	vertex[19].normal = lbb;
	vertex[20].normal = lbb;
	vertex[27].normal = lbb;

	mesh->GetVertexBuffer(0)->Unlock();
}
void MeshFactoryCube::NormalComputeStraight(MeshBuffer* mesh)
{
	// 頂点情報の作成
	VERTEX_CUBE* vertex = nullptr;
	mesh->GetVertexBuffer(0)->Lock(0, 0, (void**)&vertex, 0);

	// 法線
	D3DXVECTOR3 front(0.f, 0.f, 1.f);
	D3DXVECTOR3 back(0.f, 0.f, -1.f);
	D3DXVECTOR3 left(1.f, 0.f, 0.f);
	D3DXVECTOR3 right(-1.f, 0.f, 0.f);
	D3DXVECTOR3 top(0.f, 1.f, 0.f);
	D3DXVECTOR3 bottom(0.f, -1.f, 0.f);
	D3DXVECTOR3 zero(0.f, 0.f, 0.f);

	vertex[0].normal = front;
	vertex[1].normal = front;
	vertex[2].normal = front;
	vertex[3].normal = front;
	vertex[4].normal = right;
	vertex[5].normal = right;
	vertex[6].normal = right;
	vertex[7].normal = right;
	vertex[8].normal = right;
	vertex[9].normal = right;
	vertex[10].normal = bottom;
	vertex[11].normal = bottom;
	vertex[12].normal = bottom;
	vertex[13].normal = bottom;
	vertex[14].normal = bottom;
	vertex[15].normal = left;
	vertex[16].normal = left;
	vertex[17].normal = left;
	vertex[18].normal = left;
	vertex[19].normal = left;
	vertex[20].normal = top;
	vertex[21].normal = top;
	vertex[22].normal = top;
	vertex[23].normal = top;
	vertex[24].normal = top;
	vertex[25].normal = top;
	vertex[26].normal = back;
	vertex[27].normal = back;
	vertex[28].normal = back;
	vertex[29].normal = back;

	mesh->GetVertexBuffer(0)->Unlock();
}

//=============================================================================
// 従法線と接ベクトルを求める
void MeshFactoryCube::TangentCompute(MeshBuffer* mesh)
{
	// 頂点情報の作成
	VERTEX_CUBE* vertex = nullptr;
	mesh->GetVertexBuffer(0)->Lock(0, 0, (void**)&vertex, 0);

	for( u32 i = 0; i < 30; ++i )
	{
		if( i >= 28)
		{
			algo::ComputeTangentAndBinormal(
				vertex[i-2].position, vertex[i - 1].position, vertex[i].position,
				vertex[i-2].texcoord, vertex[i - 1].texcoord, vertex[i].texcoord,
				&vertex[i].tangent, &vertex[i].binormal);
		}
		else
		{
			algo::ComputeTangentAndBinormal(
				vertex[i].position, vertex[i + 1].position, vertex[i+2].position,
				vertex[i].texcoord, vertex[i + 1].texcoord, vertex[i + 2].texcoord,
				&vertex[i].tangent, &vertex[i].binormal);
		}
	}

	mesh->GetVertexBuffer(0)->Unlock();
}