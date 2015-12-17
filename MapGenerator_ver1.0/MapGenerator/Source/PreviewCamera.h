//=============================================================================
//
// �v���r���[�p�J�����N���X [PreviewCamera.h]
// Author : KEITA OHUCHI
//
//=============================================================================
#ifndef _PREVIEW_CAMERA_H_
#define _PREVIEW_CAMERA_H_

#include <Windows.h>
#include "Main.h"
#include "Camera.h"
#include "RouteManager.h"


class SceneBillboard;
class SceneX;

//-----------------------------------------------------------------------------
// �N���X��`
//-----------------------------------------------------------------------------
class PreviewCamera : public Camera {
public:
	//=========================================================================
	// �R���X�g���N�^�ƃf�X�g���N�^
	//=========================================================================
	PreviewCamera();
	virtual ~PreviewCamera();

	//=========================================================================
	// ����������
	//=========================================================================
	HRESULT Init();
	HRESULT Init(int index);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 focus_pos) { return S_OK; };

	//=========================================================================
	// �X�V����
	//=========================================================================
	void Update();

	void Set();

private:
	float		length_;
	float		time_;
	RoutePoint	*currentPoint_;
	RoutePoint	*nextPoint_;
	int			index_;
//	SceneBillboard *player_;
	SceneX *mplayer_;
};


#endif


// End of file