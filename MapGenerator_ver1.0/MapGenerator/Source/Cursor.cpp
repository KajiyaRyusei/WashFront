//=============================================================================
//
// �J�[�\�� [Cursor.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "Main.h"
#include "Cursor.h"
#include "Renderer.h"
#include "ObjectManager.h"
#include "CameraManager.h"
#include "Camera.h"
#include "Manager.h"
#include "Mouse.h"
#include "Debug.h"
#include "TextureFactory.h"


//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define POLYGON_WIDTH (1.0f)
#define POLYGON_HEIGHT (1.0f)


//=========================================================================
// �R���X�g���N�^
//=========================================================================
Cursor::Cursor(int priority) : SceneBillboard(priority)
{
}

//=========================================================================
// �f�X�g���N�^
//=========================================================================
Cursor::~Cursor()
{
}

//=========================================================================
// ����������
//=========================================================================
HRESULT Cursor::Init()
{
	// ���_���W�̐ݒ�
	Renderer *renderer = Manager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 device = renderer->GetDevice();

	// ���_�o�b�t�@�̐����i�������̊m�ہj
	if (FAILED(device->CreateVertexBuffer(
		sizeof(VERTEX_3D)* 4,  // �m�ۂ��郁�����̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,  // �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&vertexBuffer_,  // ���_�o�b�t�@�̐擪�A�h���X�̓������|�C���^�ϐ��̃A�h���X
		nullptr))) {
		return E_FAIL;
	}

	float fAngle = atan2f(POLYGON_WIDTH / 2, POLYGON_HEIGHT / 2);  // �Ίp���̂Ȃ��p������
	float fLength = sqrtf((POLYGON_WIDTH / 2) * (POLYGON_WIDTH / 2)
		+ (POLYGON_HEIGHT / 2) * (POLYGON_HEIGHT / 2));  // �Ίp���̒���������

	// ���_���W�̐ݒ�
	VERTEX_3D *pVtx;
	vertexBuffer_->Lock(0, 0, (void**)&pVtx, 0);  // ���_�������b�N

	pVtx[0].vtx = D3DXVECTOR3(-sinf(fAngle) * fLength, cosf(fAngle) * fLength, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(sinf(fAngle) * fLength, cosf(fAngle) * fLength, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-sinf(fAngle) * fLength, -cosf(fAngle) * fLength, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(sinf(fAngle) * fLength, -cosf(fAngle) * fLength, 0.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����̏�����
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	vertexBuffer_->Unlock();  // ���_�����A�����b�N


	texture_ = Manager::GetInstance()->GetTextureFactory()->GetTexture(
		"./Resource/Texture/Game/texture000.png");


	return S_OK;
}

//=========================================================================
// �X�V����
//=========================================================================
void Cursor::Update()
{
	Camera *camera = Manager::GetInstance()->GetCameraManager()->GetCamera();

	// �E�B���h�E���擾
	HWND hWnd = GetWindowHandle();
	RECT rectWindow, rectClient;
	GetWindowRect(hWnd, &rectWindow);
	GetClientRect(hWnd, &rectClient);

	// �}�E�X�̃X�N���[�����W
	POINT screenPosition;
	GetCursorPos(&screenPosition);
	ScreenToClient(hWnd, &screenPosition);


	// �}�E�X�̃��C
	D3DXVECTOR3 nearPosition;
	D3DXVECTOR3 farPosition;
	D3DXVECTOR3 ray;
	nearPosition = camera->CalcScreenToWorld(D3DXVECTOR3((float)screenPosition.x, (float)screenPosition.y, 0.0f),
		D3DXVECTOR2((float)rectClient.right, (float)rectClient.bottom));
	farPosition = camera->CalcScreenToWorld(D3DXVECTOR3((float)screenPosition.x, (float)screenPosition.y, 1.0f),
		D3DXVECTOR2((float)rectClient.right, (float)rectClient.bottom));
	ray = farPosition - nearPosition;
	float length1 = nearPosition.y;
	float length2 = -farPosition.y;
	D3DXVECTOR3 v12 = ray * length1 / (length1 + length2);

	position_ = nearPosition + v12;

}

//=========================================================================
// �`�揈��
//=========================================================================
void Cursor::Draw()
{
	if (GetMode() == MODE_ROUTE) {
		Renderer *renderer = Manager::GetInstance()->GetRenderer();
		LPDIRECT3DDEVICE9 device = renderer->GetDevice();

		device->SetRenderState(D3DRS_ZENABLE, false);
		SceneBillboard::Draw();
		device->SetRenderState(D3DRS_ZENABLE, true);
	}
}


// End of file