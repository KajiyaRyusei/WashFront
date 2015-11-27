////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////
//// 水しぶきのオブジェクトプール
//// 
//// Created by Ryusei Kajiya on 20151125
////
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
////*****************************************************************************
//// include
//#include "Unit/Game/water_spray_pool.h"
//#include "Resource/Mesh/Mesh/mesh_factory_instance_sprite.h"
//#include "Shader/Shader/water_spray_shader.h"
//
////=============================================================================
//// コンストラクタ
//WaterSprayPool::WaterSprayPool(Application* application, World* world) : Unit(application, world)
//{
//	_first_available = &_particles[0];
//
//	for( u32 i = 0; i < kPoolSize-1; ++i )
//	{
//		_particles[i].SetNext(&_particles[i+1]);
//	}
//
//	_particles[kPoolSize - 1].SetNext(nullptr);
//
//	MeshFactoryInstanceSprite factory;
//	_mesh = factory.Create(application->GetRendererDevice(), kPoolSize);
//	_shader = new ShaderWaterSpray();
//}
////=============================================================================
//// デストラクタ
//WaterSprayPool::~WaterSprayPool()
//{
//	SafeDelete(_mesh);
//	SafeDelete(_shader);
//}
//
////=============================================================================
//// 作成
//void WaterSprayPool::Create(
//	const D3DXVECTOR3& position,
//	const D3DXQUATERNION& quaternion)
//{
//	if( _first_available != nullptr)
//	{
//		OutputDebugStringA("水しぶきプールがいっぱいだよ\n");
//		return;
//	}
//
//	WaterSpray* new_particle = _first_available;
//	_first_available = new_particle->GetNext();
//	new_particle->Initialize(position, quaternion);
//}
////=============================================================================
//// アニメーション
//void WaterSprayPool::Animate()
//{
//	for( u32 i = 0; i < kPoolSize; ++i )
//	{
//		if( _particles[i].Animate())
//		{
//			_particles[i].SetNext(_first_available);
//			_first_available = &_particles[i];
//		}
//	}
//
//	MeshFactoryInstanceSprite factory;
//	factory.RegisterMatrix(_spray_matrices, _mesh);
//
//	// 描画する情報を押し込む：１度の描画に１度しか呼ばないこと
//	S_GetCommandBuffer()->PushRenderState(RENDER_STATE_TRANSLUCENT, GetID());
//	S_GetCommandBuffer()->PushShader(_shader, GetID());
//	S_GetCommandBuffer()->PushMesh(_mesh, GetID());
//}