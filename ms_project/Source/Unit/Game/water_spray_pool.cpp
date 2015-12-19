//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �����Ԃ��̃I�u�W�F�N�g�v�[��
// 
// Created by Ryusei Kajiya on 20151125
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit/Game/water_spray_pool.h"
#include "Resource/Mesh/Mesh/mesh_factory_sprite_instance.h"
#include "Resource/Mesh/Mesh/mesh_factory_sprite.h"
#include "Shader/Shader/water_spray_shader.h"
#include "Renderer/directx9.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"

//=============================================================================
// �R���X�g���N�^
WaterSprayPool::WaterSprayPool(Application* application, World* world) : Unit(application, world)
{
	_first_available = &_particles[0];

	for( u32 i = 0; i < kPoolSize-1; ++i )
	{
		_particles[i].SetNext(&_particles[i+1]);
		D3DXMatrixIdentity(&_spray_matrices[i]);
	}

	_particles[kPoolSize - 1].SetNext(nullptr);
	D3DXMatrixIdentity(&_spray_matrices[kPoolSize - 1]);

	MeshFactorySpriteInstance factory;
	_mesh = factory.Create(application->GetRendererDevice(), kPoolSize);

	_shader = new ShaderWaterSpray();
	D3DXCreateTextureFromFileA(application->GetRendererDevice()->GetDevice(), "Data/Texture/water_spray2.png", &_albedo_map);
	_shader->SetAlbedoTexture(_albedo_map);
}

//=============================================================================
// �f�X�g���N�^
WaterSprayPool::~WaterSprayPool()
{
	SafeDelete(_mesh);
	SafeDelete(_shader);
	SafeRelease(_albedo_map);
}

//=============================================================================
// �쐬
void WaterSprayPool::Create(
	const D3DXVECTOR3& position,
	const fx32 rotation)
{
	if( _first_available == nullptr)
	{
#ifndef _RELEASE
		OutputDebugStringA("�����Ԃ��v�[���������ς�����\n");
#endif
		return;
	}

	WaterSpray* new_particle = _first_available;
	_first_available = new_particle->GetNext();
	new_particle->Initialize(position, rotation);
}
//=============================================================================
// �A�j���[�V����
void WaterSprayPool::Animate()
{
	for( u32 i = 0; i < kPoolSize; ++i )
	{
		if( _particles[i].Animate(_spray_matrices[i]) )
		{
			_particles[i].SetNext(_first_available);
			_first_available = &_particles[i];
		}
	}

	MeshFactorySpriteInstance factory;
	factory.RegisterMatrix(_spray_matrices, kPoolSize,_mesh);

	Camera* camera = _application->GetCameraManager()->GetCurrentCamera();
	D3DXMATRIX view_projection = camera->GetMatrixView() * camera->GetMatrixProjection();

	_shader->SetViewProjection(view_projection);

	// �`�悷������������ށF�P�x�̕`��ɂP�x�����Ă΂Ȃ�����
	S_GetCommandBuffer()->PushRenderState(RENDER_STATE_TRANSLUCENT, GetID());
	S_GetCommandBuffer()->PushShader(_shader, GetID());
	S_GetCommandBuffer()->PushMesh(_mesh, GetID());
}
