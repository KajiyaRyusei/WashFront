//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// directx9�@�\
// 
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �N���X�݌v
class RendererDevice
{
public:

	RendererDevice(
		const HWND handle_window,
		const u32 size_window_width,
		const u32 size_window_height,
		const bool is_full_screen) :
			_direct3d{ nullptr },
			_direct_device{ nullptr }
	{
		Initialize(handle_window,size_window_width,size_window_height,is_full_screen);
	}

	virtual ~RendererDevice(){ Finalize(); }

	// ������
	HRESULT Initialize(
		const HWND handle_window,
		const u32 size_window_width,
		const u32 size_window_height,
		const bool is_full_screen);

	// �I��
	void Finalize();

	// �����_�����O�^�[�Q�b�g�̃N���A
	void Clear(const u8 clear_flag, const u8* clear_colors);

	// �`��̊J�n
	void Begin();

	// �`��̏I��
	void End();

	// �o�b�N�o�b�t�@�̃Z�b�g
	void Set();

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	void Swap();

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 GetDevice(){ return _direct_device; }

	// �f�o�C�X���X�g�΍�
	void DeviceLostCounterPlan();

private:

	//�@�����_�[�X�e�[�g������
	void InitializeRenderState();

	// �T���v���[�X�e�[�g������
	void InitializeSamplerState();

	// �e�N�X�`���X�e�[�W�X�e�[�g������
	void InitializeTextureStageState();

	// �f�o�C�X�̔\�͂𒲍�
	void ExamineDeviceCapacity();

	// �f�o�C�X
	LPDIRECT3D9 _direct3d;
	// direct3D
	LPDIRECT3DDEVICE9 _direct_device;
	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
	D3DPRESENT_PARAMETERS _present_parameters;

	// �o�b�N�o�b�t�@�Ə����f�v�X�X�e���V��
	LPDIRECT3DSURFACE9 _back_buffer;
	LPDIRECT3DSURFACE9 _depth_stencil_surface;
};
