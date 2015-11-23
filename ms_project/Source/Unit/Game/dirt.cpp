//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �悲��
// 
// Created by Ryusei Kajiya on 20151029
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "Unit/Game/dirt.h"
#include "Camera/camera_manager.h"
#include "Camera/Camera/camera_game_player.h"
#include "Algorithm/often_use.h"
#include "Shader/Shader/dirt_shader.h"
#include "World/collision_grid.h"

//���\�[�X
#include "Resource/cube_texture_resource.h"
#include "Resource/texture_resource.h"
#include "Resource/mesh_resource.h"

//=============================================================================
// ������
void DirtUnit::Initialize()
{
	// �V�F�[�_�̍쐬
	_shader = new ShaderDirt();

	// �e�N�X�`��
	LPDIRECT3DTEXTURE9 normal_map = _game_world->GetTextureResource()->Get(TEXTURE_RESOURE_DIRT_NORMAL_TEXTURE);
	_shader->SetNormalTexture(normal_map);

	// ���W�̐ݒ�
	_position.current = _game_world->GetCollisionGrid()->CellCenterPoint(2, 2) + D3DXVECTOR3(-7.f, 5.f, -7.f);
	_position.previous = _position.current;
	_world.position = _position.current;
	_world.scale = D3DXVECTOR3(3.f, 3.f, 3.f);
	_world.rotation = D3DXVECTOR3(0.f, 0.f, 0.f);

	// �{�����[���̍쐬
	CreateVolumeShpre(_world.position, _world.scale.x);

	// ��Ԃɓ˂�����
	_game_world->GetCollisionGrid()->AddUnit(this, _position);

	_is_invisible = false;
}

//=============================================================================
// �I��
void DirtUnit::Finalize()
{
	SafeDelete(_shader);
}

//=============================================================================
// �X�V
void DirtUnit::Update()
{
	SettingShaderParameter();

	if( _is_invisible == true )
	{
		_position.current = D3DXVECTOR3(10000.f,1000.f,10000.f);
		_shpere->position = _position.current;
	}
}
//=============================================================================
// �Փ˔���p�X�V
void DirtUnit::CollisionUpdate()
{
	if( _is_invisible  == false)
	{
		s32 cell_x = 0;
		s32 cell_z = 0;
		_game_world->GetCollisionGrid()->SelfCoordinatesCell(&cell_x, &cell_z, _position);
		_game_world->GetCollisionGrid()->HandleCell(cell_x, cell_z);
	}
	
}
//=============================================================================
// �Փ˔��莞����
void DirtUnit::CollisionSphere()
{
	_is_invisible = true;
}
//=============================================================================
// �`��
void DirtUnit::Draw()
{
	if( _is_invisible == false )
	{
		// �`�悷������������ށF�P�x�̕`��ɂP�x�����Ă΂Ȃ�����
		S_GetCommandBuffer()->PushRenderState(RENDER_STATE_DEFAULT, GetID());
		S_GetCommandBuffer()->PushShader(_shader, GetID());
		S_GetCommandBuffer()->PushMesh(_game_world->GetMeshResource()->Get(MESH_RESOURE_MESH_FIELD), GetID());
	}

	//_shpere->DebugDraw();
}

//=============================================================================
// �V�F�[�_�p�����[�^�[�̐ݒ�
void DirtUnit::SettingShaderParameter()
{
	// �J�����擾
	CameraGamePlayer* camera = static_cast<CameraGamePlayer*>(_application->GetCameraManager()->GetCamera(CAMERA_TYPE_GAME_PLAYER));
	// �s��̍쐬
	_world.position = _position.current;
	_world.rotation.x = D3DX_PI*0.5f;
	algo::CreateWorld(_world.matrix, _world.position, _world.rotation, _world.scale);
	algo::CreateWVP(_matrix_world_view_projection, _world.matrix, camera);
	// ���C�g�̕����쐬
	D3DXVECTOR4 light_direction(0.2f, -0.8f, 0.5f, 0.f);
	D3DXVECTOR4 ambient(0.25f, 0.15f, 0.15f, 1.f);
	D3DXVECTOR4 eye(camera->GetVectorEye(), 0.f);
	// �V�F�[�_�̐ݒ�
	_shader->SetWorldViewProjection(_matrix_world_view_projection);
	
	//D3DXMatrixIdentity(&_world.matrix);

	//_world.matrix._41 = -2.f;
	//_world.matrix._42 = 2.f;
	//_world.matrix._43 = -2.f;
	static D3DXVECTOR2 texcoord_move(0.f,0.f);
	texcoord_move.y += 0.0001f;
	//texcoord_move.x += 0.0001f;
	D3DXMATRIX world_inverse_transpose;
	D3DXMatrixInverse(&world_inverse_transpose, nullptr, &_world.matrix);
	D3DXMatrixTranspose(&world_inverse_transpose, &world_inverse_transpose);
	_shader->SetWorldInverseTranspose(world_inverse_transpose);
	_shader->SetTexcoordMove(texcoord_move);

	D3DXMATRIX dirt_move_matrix;
	D3DXMatrixIdentity(&dirt_move_matrix);
	//dirt_move_matrix._41 = -2.f;
	//dirt_move_matrix._42 = -2.f;
	//dirt_move_matrix._43 = -2.f;
	_shader->SetDirtMoveMatrix(dirt_move_matrix);
	_shader->SetWorld(_world.matrix);
	_shader->SetLightDirection(light_direction);
	_shader->SetAmbientColor(ambient);
	_shader->SetEyePosition(eye);
	_shader->SetFresnel(0.4f);
	_shader->SetMetalness(0.03f);
	_shader->SetRoughness(0.7f);
	_shader->SetWorld(_world.matrix);
}

//=============================================================================
// ���W�ݒ�
void DirtUnit::SetPosition(const D3DXVECTOR3& position)
{
	_position.current = position;
	_shpere->position = position;
	_game_world->GetCollisionGrid()->MoveUnit(this, _position);
}