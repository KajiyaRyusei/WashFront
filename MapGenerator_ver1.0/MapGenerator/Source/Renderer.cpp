//=============================================================================
//
// �����_���[�N���X [Renderer.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Renderer.h"
#include "Main.h"
#include "Scene.h"
#include "Debug.h"
#include "Manager.h"
#include "Keyboard.h"


//=============================================================================
// �R���X�g���N�^
//=============================================================================
Renderer::Renderer()
{
	// �����o�ϐ��̃N���A
	direct3D_ = nullptr;
	device_ = nullptr;

#ifdef _DEBUG
	wireframe_ = false;
#endif
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Renderer::~Renderer()
{

	// �f�o�C�X�I�u�W�F�N�g�̊J��
	SafeRelease(device_);
	// Direct3D�I�u�W�F�N�g�̊J��
	SafeRelease(direct3D_);

}

//=============================================================================
// ����������
//=============================================================================
HRESULT Renderer::Init(HINSTANCE instance, HWND wnd, BOOL window)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	direct3D_ = Direct3DCreate9(D3D_SDK_VERSION);
	if (direct3D_ == nullptr) {
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(direct3D_->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))) {
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));  // ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;  // �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;  // �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;  // �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;  // �o�b�N�o�b�t�@�t�H�[�}�b�g�̓f�B�X�v���C���[�h�ɍ��킹�Ďg��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;  // �f���M���ɓ������ăt���b�v����
	d3dpp.Windowed = window;  // �E�B���h�E���[�h
	d3dpp.EnableAutoDepthStencil = TRUE;  // �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;  // �f�v�X�o�b�t�@�Ƃ���24bit, �X�e���V���o�b�t�@�Ƃ���8bit���g��

	if (window) {  // �E�B���h�E���[�h
		d3dpp.FullScreen_RefreshRateInHz = 0;  // ���t���b�V�����[�g
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; // �C���^�[�o��
	} else {  // �t���X�N���[�����[�h
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;  // ���t���b�V�����[�g
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;  // �C���^�[�o��
	}

	// �f�o�C�X�I�u�W�F�N�g�̐���
	// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(direct3D_->CreateDevice(D3DADAPTER_DEFAULT, 
										D3DDEVTYPE_HAL,
										wnd, 
										D3DCREATE_HARDWARE_VERTEXPROCESSING, 
										&d3dpp, &device_))) {
		// ��L�̐ݒ肪���s������
		// [�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ�
		if (FAILED(direct3D_->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_HAL, 
											wnd, 
											D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
											&d3dpp, &device_))) {
		// ��L�̐ݒ肪���s������
		// [�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
		if (FAILED(direct3D_->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_REF,
											wnd, 
											D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
											&d3dpp, &device_))) {
				// ���������s
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�p�����[�^�̐ݒ�
	device_->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);  // ���ʂ��J�����O
	device_->SetRenderState(D3DRS_ZENABLE, TRUE);  // Z�o�b�t�@���g�p
	device_->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);  // ���u�����h���s��
	device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  // ���\�[�X�J���[�̎w��
	device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);  // ���f�X�e�B�l�[�V�����J���[�̎w��

	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	device_->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);  // �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	device_->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);  // �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	device_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);  // �e�N�X�`���k���t�B���^���[�h��ݒ�
	device_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);  // �e�N�X�`���g��t�B���^���[�h��ݒ�

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	//device_->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	//device_->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//device_->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
	device_->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);  // �A���t�@�u�����f�B���O������ݒ�
	device_->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);  // �ŏ��̃A���t�@����
	device_->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);  // �Q�Ԗڂ̃A���t�@����


    // �t�H�O
	/*
    device_->SetRenderState(D3DRS_FOGENABLE, TRUE);
    device_->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
	device_->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);
    float start = 50;
    float end = 200;
    device_->SetRenderState(D3DRS_FOGSTART, *(DWORD *)(&start));
    device_->SetRenderState(D3DRS_FOGEND, *(DWORD *)(&end));
	*/

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void Renderer::Update()
{
#ifdef _DEBUG
	Keyboard *key = Manager::GetInstance()->GetKeyboard();
	if (key->GetTriggerKey(DIK_F2)) {
		if (wireframe_) {
			wireframe_ = false;
			device_->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			//device_->SetRenderState(D3DRS_LIGHTING, TRUE);
		} else {
			wireframe_ = true;
			device_->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			//device_->SetRenderState(D3DRS_LIGHTING, FALSE);
		}
	}
#endif
}

//=========================================================================
// �`��J�n����
//=========================================================================
bool Renderer::BeginDraw()
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	device_->Clear(0, nullptr, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),
					D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), 1.0f, 0);

	// �`��̊J�n
	return SUCCEEDED(device_->BeginScene());
}

//=========================================================================
// �`��I������
//=========================================================================
void Renderer::EndDraw()
{

	// �`��̏I��
	device_->EndScene();

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	device_->Present(nullptr, nullptr, nullptr, nullptr);

}


// End of file