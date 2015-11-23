//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// directx9�@�\
//
// Created by Ryusei Kajiya on 20151006
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// �C���N���[�h
#include "directx9.h"
//#include "reference.h"

//=============================================================================
// ������
HRESULT RendererDevice::Initialize(
	const HWND handle_window,
	const u32 size_window_width,
	const u32 size_window_height,
	const bool is_full_screen)
{
	D3DDISPLAYMODE display_mode;

	// Direct3D�I�u�W�F�N�g�̍쐬
	_direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (_direct3d == nullptr)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(_direct3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &display_mode)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&_present_parameters, sizeof(_present_parameters));	// ���[�N���[���N���A
	_present_parameters.BackBufferCount = 1;						// �o�b�N�o�b�t�@�̐�
	_present_parameters.BackBufferWidth = size_window_width;		// �Q�[����ʃT�C�Y(��)
	_present_parameters.BackBufferHeight = size_window_height;		// �Q�[����ʃT�C�Y(����)
	_present_parameters.BackBufferFormat = display_mode.Format;		// �o�b�N�o�b�t�@�t�H�[�}�b�g�̓f�B�X�v���C���[�h�ɍ��킹�Ďg��
	_present_parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;			// �f���M���ɓ������ăt���b�v����
	_present_parameters.Windowed = true;							// �E�B���h�E���[�h
	_present_parameters.EnableAutoDepthStencil = TRUE;				// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	_present_parameters.AutoDepthStencilFormat = D3DFMT_D24S8;		// �f�v�X�o�b�t�@�Ƃ���24bit�E�X�e���V����8bit�g�p
	_present_parameters.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;	// �}���`�T���v�����O
	DWORD multi_sample_quality = 0;
	_direct3d->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,D3DFMT_X8R8G8B8,true,D3DMULTISAMPLE_4_SAMPLES,&multi_sample_quality);
	_present_parameters.MultiSampleQuality = multi_sample_quality-1;

	if( is_full_screen == false)
	{// �E�B���h�E���[�h
		_present_parameters.FullScreen_RefreshRateInHz = 0;							// ���t���b�V�����[�g
		_present_parameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// �C���^�[�o��
	}
	else
	{// �t���X�N���[�����[�h
		_present_parameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���t���b�V�����[�g
		_present_parameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��
	}

	// �f�o�C�X�I�u�W�F�N�g�̐���
	if (FAILED(_direct3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		handle_window,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		//D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,// �}���`�X���b�h�g�p��
		&_present_parameters,
		&_direct_device)))
	{
		// ��L�̐ݒ肪���s������
		// [�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ�
		if (FAILED(_direct3d->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			handle_window,
			//D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,// �}���`�X���b�h�g�p��
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&_present_parameters,
			&_direct_device)))
		{
			// ��L�̐ݒ肪���s������
			// [�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
			if (FAILED(_direct3d->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				handle_window,
				//D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,// �}���`�X���b�h�g�p��
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&_present_parameters,
				&_direct_device)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�p�����[�^�̐ݒ�
	InitializeRenderState();
	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	InitializeSamplerState();
	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	InitializeTextureStageState();
	// �f�o�C�X�\�͂̒���
	ExamineDeviceCapacity();


	// �o�b�N�o�b�t�@�Ə����f�v�X�X�e���V�����擾
	_direct_device->GetRenderTarget(0, &_back_buffer);
	_direct_device->GetDepthStencilSurface(&_depth_stencil_surface);

	// �o�^
	//Reference::GetInstance().SetDevice(_direct_device);

	return S_OK;
}
//=============================================================================
// �I��
void RendererDevice::Finalize()
{
	SafeRelease(_direct3d);
	SafeRelease(_direct_device);
}
//=============================================================================
// �����_�����O�^�[�Q�b�g�̃N���A
void RendererDevice::Clear(const u8 clear_flag, const u8* clear_colors)
{
	_direct_device->Clear(0, nullptr, clear_flag, D3DCOLOR_RGBA(clear_colors[0], clear_colors[1], clear_colors[2], clear_colors[3]), 1.f, 0);
}
//=============================================================================
// �`��̊J�n
void RendererDevice::Begin()
{
	if( FAILED(_direct_device->BeginScene()) )
	{
		OutputDebugStringA("�`��J�n���s");
		return;
	}
}
//=============================================================================
// �`��̏I��
void RendererDevice::End()
{
	_direct_device->EndScene();
}

//=============================================================================
// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
void RendererDevice::Swap()
{
	if( _direct_device->Present(nullptr, nullptr, nullptr, nullptr) == D3DERR_DEVICELOST)
	{
		DeviceLostCounterPlan();
	}
}

//=============================================================================
// �o�b�N�o�b�t�@��Z�o�b�t�@�̃Z�b�g
void RendererDevice::Set()
{
	_direct_device->SetRenderTarget(0, _back_buffer);
	_direct_device->SetDepthStencilSurface(_depth_stencil_surface);
}
//=============================================================================
//�@�����_�[�X�e�[�g������
void RendererDevice::InitializeRenderState()
{
	_direct_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);			// �|���S���ʂ�\��
	//_direct_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);		// ���C���[�t���[����\��
	_direct_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
	_direct_device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffff);			// �S�ẴJ���[�������݂��s��
	_direct_device->SetRenderState(D3DRS_FOGENABLE, FALSE);					// �t�H�O�s�g�p
	_direct_device->SetRenderState(D3DRS_LIGHTING, FALSE);					// ���C�g��s�g�p
	_direct_device->SetRenderState(D3DRS_STENCILENABLE, FALSE);				// �X�e���V���ɏ������܂Ȃ�
	_direct_device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);				// ���e�X�g���s��
	_direct_device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			// ���u�����h���s��
	_direct_device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			// ���u�����h�̎��
	_direct_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	_direct_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��
}

//=============================================================================
// �T���v���[�X�e�[�g������
void RendererDevice::InitializeSamplerState()
{
	_direct_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	_direct_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	_direct_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	_direct_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�
}

//=============================================================================
// �e�N�X�`���X�e�[�W�X�e�[�g������
void RendererDevice::InitializeTextureStageState()
{
	_direct_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O������ݒ�
	_direct_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	_direct_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����
}

//=============================================================================
// �f�o�C�X�̔\�͂𒲍�
void RendererDevice::ExamineDeviceCapacity()
{
	D3DCAPS9 capacity;
	_direct_device->GetDeviceCaps(&capacity);
	MyOutputDebugString(L"���_�u�����h�̍s��̍ő吔�F%d\n",capacity.MaxVertexBlendMatrices);
	if( capacity.VertexShaderVersion >= D3DVS_VERSION(3,0))
	{
		OutputDebugStringA("���_�V�F�[�_�o�[�W����3.0�Ή��ł�\n");
	}
	
	if( capacity.PixelShaderVersion >= D3DPS_VERSION(3,0))
	{
		OutputDebugStringA("�s�N�Z���V�F�[�_�o�[�W����3.0�Ή��ł�\n");
	}
	MyOutputDebugString(L"���_�萔���W�X�^�̍ő吔�F%d\n", capacity.MaxVertexShaderConst);
	MyOutputDebugString(L"�s�N�Z���V�F�[�_���������_���W�X�^�́F%d\n", 224);
	//MyOutputDebugString(L"�}���`�T���v�����O�̃N�I���e�B�́F%d\n", capacity.);
}

//=============================================================================
// �f�o�C�X���X�g�΍�
void RendererDevice::DeviceLostCounterPlan()
{
	// ���A�\���`�F�b�N
	HRESULT handle_result = _direct_device->TestCooperativeLevel();

	OutputDebugStringA("=========================================================\n");
	OutputDebugStringA("�f�o�C�X���X�g���܂���\n");
	OutputDebugStringA("=========================================================\n");

	ASSERT(handle_result == D3DERR_DEVICELOST,"�f�o�C�X���A����\n");

	if( handle_result == D3DERR_DEVICENOTRESET )
	{
		_direct_device->Reset(&_present_parameters);
	}
}
