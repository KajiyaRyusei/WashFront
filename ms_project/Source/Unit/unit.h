//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ユニット
// 
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// include
#include "DrawCommand/command_buffer_holder.h"
#include "DrawCommand/command_buffer.h"
#include "System/application.h"
#include "World/world.h"
#include "Data/data_position.h"
#include "Data/data_box.h"
#include "Data/data_shpere.h"
#include "Data/data_line.h"
#include "Data/data_mesh_point.h"

//*****************************************************************************
// クラス設計
class Unit : public CommandBufferHolder
{
	friend class CollisionGrid;
	friend class Grid2D;

public:

	Unit(Application* application, World* world);
	virtual ~Unit();

	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Update() = 0;
	virtual void CollisionUpdate() = 0;
	virtual void CollisionSphere(){}
	virtual void CollisionBox(){}
	virtual void CollisionMeshPoint(u32 point_index){ UNREFERENCED_PARAMETER(point_index); }
	virtual void CollisionLine(const D3DXVECTOR3& impact_point){ UNREFERENCED_PARAMETER(impact_point); }
	virtual void Draw() = 0;

	// シーンの切り替え時に呼び出してください。
	static void ResetID(){ s_unit_id = 0; }

	// 自分のオブジェクトID : Unit１つにつき１つ
	u32 GetID() const { return _id; }

protected:

	Application* _application;
	World* _game_world;

	// 座標
	data::Position _position;
	// 球のボリューム
	data::Shpere* _shpere;
	// ボックスのボリューム
	data::Box* _box;
	// ラインのボリューム
	data::Line* _line;
	// メッシュのポイント
	data::MeshPoint* _volume_mesh_point;

	//------------------------------------
	// 衝突判定用ボリュームの作成
	void CreateVolumeShpre(
		const D3DXVECTOR3 &position,
		const fx32 &radius)
	{
		_shpere = new data::Shpere;
		_shpere->position = position;
		_shpere->radius = radius;
	}
	void CreateVolumeBox(
		const D3DXVECTOR3& position,
		const D3DXVECTOR3& size,
		const D3DXVECTOR3& rotation)
	{
		_box = new data::Box;
		_box->position = position;
		_box->size = size;
		_box->rotation = rotation;
		_box->Calculation8Point();
	}
	void CreateVolumeLine(
		const D3DXVECTOR3& start,
		const D3DXVECTOR3& end )
	{
		_line = new data::Line;
		_line->start_point = start;
		_line->end_point = end;
	}

	void CreateVolumeMeshPoint(
		const D3DXVECTOR3& position,
		const D3DXVECTOR3& scale,
		const D3DXVECTOR3& rotation,
		const u32 vertex_size,
		const D3DXVECTOR3* point_array,
		const D3DXVECTOR3* normal_array)
	{
		_volume_mesh_point = new data::MeshPoint(
			position, scale, rotation,
			vertex_size, point_array, normal_array);
	}


private:

	Unit* _next;
	Unit* _previous;
	static u32 s_unit_id;
	u32 _id;
};