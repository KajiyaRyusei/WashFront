//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// アニメーションモデル
// 
// Created by Ryusei Kajiya on 20151014
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "animation_model_unit.h"

#include "System/application.h"

#include "Shader/Shader/animation_shader.h"

#include "Resource/Mesh/Mesh/mesh_factory_amo.h"

#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_main.h"

#include "DrawCommand/command_buffer.h"

#include "Animation/animation_system.h"

#include "Input/input_manager.h"

namespace
{
	static u32 d_pose_id = 0;
}

//=============================================================================
// 初期化
void AnimationModelUnit::Initialize()
{
	// シェーダの作成
	_shader = new ShaderAnimation();

	// メッシュの作成
	MeshFactoryAMO mesh_factory;
	mesh_factory.Create(
		_application->GetRendererDevice(),
		"Data/AnimationModel/oba_walk.amo",
		_mesh_list);

	// アニメーションの読み込み
	_animation.LoadAnimationFile(
		"Data/Animation/oba_walk.oaf",
		_mesh_list.size());

	// アニメーションシステムの作成
	_animation_system = new AnimationSystem();
}

//=============================================================================
// 終了
void AnimationModelUnit::Finalize()
{
	SafeDelete(_animation_system);
	_animation.UnLoadAnimationFile();
	for( auto it : _mesh_list )
	{
		SafeDelete(it);
	}
	SafeDelete(_shader);
}

//=============================================================================
// 更新
void AnimationModelUnit::Update()
{
	// 行列の作成
	D3DXMATRIX matrix_world, matrix_scaling;
	static float rotation = 0;
	D3DXMatrixRotationYawPitchRoll(&matrix_world, rotation, 0.f, 0.f);
	float scaling = 0.007f;
	D3DXMatrixScaling(&matrix_scaling, scaling, scaling, scaling);
	rotation += 0.01f;
	matrix_world *= matrix_scaling;

	CameraGameMain* camera = static_cast<CameraGameMain*>(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_MAIN));
	D3DXMATRIX matrix_projection = camera->GetMatrixProjection();
	D3DXMATRIX matrix_view = camera->GetMatrixView();
	D3DXMATRIX matrix_world_view_projection = matrix_world * matrix_view * matrix_projection;

	// ライトの方向作成
	_shader->SetWorldViewProjection(matrix_world_view_projection);
	D3DXVECTOR4 light_direction(0.f, -0.5f, -1.f, 0.f);
	D3DXMATRIX matrix_world_inverse;
	D3DXMatrixInverse(&matrix_world_inverse, nullptr, &matrix_world);
	D3DXVec4Transform(&light_direction, &light_direction, &matrix_world_inverse);
	D3DXVec4Normalize(&light_direction, &light_direction);
	_shader->SetLightDirection(light_direction);

	// フレームの更新
	_animation_system->AdvanceFrame(1);

	
	if( _application->GetInputManager()->CheckTrigger(INPUT_EVENT_1) )
	{
		d_pose_id = 0;
	}
	else if( _application->GetInputManager()->CheckTrigger(INPUT_EVENT_2) )
	{
		d_pose_id = 1;
	}
	else if( _application->GetInputManager()->CheckTrigger(INPUT_EVENT_3) )
	{
		d_pose_id = 2;
	}
	else if( _application->GetInputManager()->CheckTrigger(INPUT_EVENT_4) )
	{
		d_pose_id = 3;
	}
	else if( _application->GetInputManager()->CheckTrigger(INPUT_EVENT_5) )
	{
		d_pose_id = 4;
	}
}

//=============================================================================
// 描画
void AnimationModelUnit::Draw()
{
	// 描画する情報を押し込む：１度の描画に１度しか呼ばないこと
	D3DXMATRIX animation_matrix_list[ShaderAnimation::kMatrixMax];

	for( auto it : _mesh_list )
	{
		// アニメーション行列計算
		if( d_pose_id == 0 )
		{
			_animation_system->ComputeHumanPose(animation_matrix_list, ShaderAnimation::kMatrixMax, _animation, HUMAN_POSE_FRONT);
		}
		else if( d_pose_id == 1)
		{
			_animation_system->ComputeHumanPose(animation_matrix_list, ShaderAnimation::kMatrixMax, _animation, HUMAN_POSE_LEFT);
		}
		else if( d_pose_id == 2 )
		{
			_animation_system->ComputeHumanPose(animation_matrix_list, ShaderAnimation::kMatrixMax, _animation, HUMAN_POSE_RIGHT);
		}
		else if( d_pose_id == 3 )
		{
			_animation_system->ComputeHumanPose(animation_matrix_list, ShaderAnimation::kMatrixMax, _animation, HUMAN_POSE_TOP);
		}
		else if( d_pose_id == 4 )
		{
			_animation_system->ComputeHumanPose(animation_matrix_list, ShaderAnimation::kMatrixMax, _animation, HUMAN_POSE_BOTTOM);
		}
		
		_shader->SetAnimationMatrix(animation_matrix_list);


		S_GetCommandBuffer()->PushRenderState(RENDER_STATE_DEFAULT, GetID());
		S_GetCommandBuffer()->PushShader(_shader, GetID());
		S_GetCommandBuffer()->PushMesh(it, GetID());
	}
}