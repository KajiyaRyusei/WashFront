//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// �A�v���P�[�V����
// 
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// include
#include "application.h"
#include "Windows/window.h"
#include "Renderer/directx9.h"

// �}�l�[�W���[�Q
#include "Scene/scene_manager.h"
#include "Input/input_manager.h"
#include "Camera/camera_manager.h"
#include "DevelopTool/develop_tool_manager.h"
#include "Shader/effect_handle_manager.h"

// ���\�[�X�{�b�N�X
#include "Resource/resource_box.h"

// �`��
#include "DrawCommand/command_processor.h"
#include "DrawCommand/command_buffer.h"
#include "DrawCommand/command_buffer_holder.h"

// fade
#include "Fade/fade.h"

//*****************************************************************************
// �萔
namespace
{
	static const u8 kClearColors[4] = {0};
}

//=============================================================================
// ������
void Application::Initalize(Window *window, RendererDevice *renderer_device)
{
	UNREFERENCED_PARAMETER(renderer_device);

	// �e�N�X�`�����\�[�X�{�b�N�X�̍쐬
	_texture_box = new ResourceBox<LPDIRECT3DTEXTURE9>();
	Reference::GetInstance().SetTextureBox(_texture_box);

	// ���b�V�����\�[�X�{�b�N�X�̍쐬
	_mesh_box = new ResourceBox<MeshBuffer>();
	Reference::GetInstance().SetMeshBox(_mesh_box);

	// �h���[�R�}���h
	_command_buffer = new CommandBuffer();
	_command_processor = new CommandProcessor(*_command_buffer);
	CommandBufferHolder::S_SetCommandBuffer(_command_buffer);

	//------------------------------------
	// �}�l�[�W���[�̍쐬
	//------------------------------------
	// �C���v�b�g�}�l�[�W���[�̍쐬
	_input_manager = new InputManager(window->GetHandleWindow(), window->GetHandleInstance());
	Reference::GetInstance().SetInputManager(_input_manager);

	// �G�t�F�N�g�n���h���}�l�[�W���[�̍쐬
	_effect_handle_manager = new EffectHandleManager(renderer_device);
	Reference::GetInstance().SetEffectHandleManager(_effect_handle_manager);

	// �t�F�[�h�̍쐬
	_fade = new Fade(this);

	// �V�[���}�l�[�W���[�̍쐬
	_scene_manager = new SceneManager(this,_fade);
	Reference::GetInstance().SetSceneManager(_scene_manager);
	
	// �J�����}�l�[�W���[�̍쐬
	_camera_manager = new CameraManager();
	Reference::GetInstance().SetCameraManager(_camera_manager);

	// �f�x���b�v�c�[���}�l�[�W���[�̍쐬
	_develop_manager = new DevelopToolManager();
	Reference::GetInstance().SetDevelopToolManager(_develop_manager);

}
//=============================================================================
// �I��
void Application::Finalize()
{
	SafeDelete(_fade);
	SafeDelete(_camera_manager);
	SafeDelete(_develop_manager);
	SafeDelete(_scene_manager);
	SafeDelete(_effect_handle_manager);
	SafeDelete(_input_manager);

	SafeDelete(_command_buffer);
	SafeDelete(_command_processor);

	SafeDelete(_texture_box);
	SafeDelete(_mesh_box);
}
//=============================================================================
// �X�V
void Application::Update()
{
	_input_manager->Update();
	_camera_manager->Update();
	_scene_manager->Update();
	_develop_manager->Update();
}
//=============================================================================
// �`��
void Application::Draw()
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	_renderer_device->Clear((D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), kClearColors);

	// �`��̊J�n
	_renderer_device->Begin();

	// �e�V�[���`��
	_scene_manager->Draw();

	// �R�}���h�ɂ��܂��Ă�����̂�`��
	_command_buffer->Sort();
	_command_processor->ProccessLightDepth();
	_command_processor->ProccessDefault();
	_command_processor->ProccessField();
	_command_processor->ProccessShadow();
	_command_processor->Proccess2D();
	_command_buffer->Clear();

	// fade�̕`��
	_fade->Draw();

	// �f�o�b�O���̕`��
	_develop_manager->Draw();

	// �`��̏I��
	_renderer_device->End();

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	_renderer_device->Swap();
}