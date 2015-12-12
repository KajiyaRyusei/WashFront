//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// ������J�����O
//
// Created by Ryusei Kajiya on 20151201
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// ���d�C���N���[�h�h�~
#pragma once

//*****************************************************************************
// �N���X�݌v
class FrustumCulling
{
public:

	typedef enum
	{
		ViewVolumePlaneTop = 0,
		ViewVolumePlaneBottom,
		ViewVolumePlaneLeft,
		ViewVolumePlaneRight,
		ViewVolumePlaneFront,
		ViewVolumePlaneBack,
		ViewVolumePlaneMax
	}PLANE_TYPE;

	//=============================================================================
	// ��������쐬
	inline void MakeClip(
		const D3DVIEWPORT9& viewport,
		D3DXMATRIX matProj,
		D3DXMATRIX matView)
	{
		// viewport.MinZ / MaxZ �́A�ʏ킻�ꂼ�� 0 / 1
		float x1 = (float)viewport.X;
		float y1 = (float)viewport.Y;
		float x2 = (float)viewport.X + (float)viewport.Width;
		float y2 = (float)viewport.Y + (float)viewport.Height;

		// ������̂W�_���i�[�����C���X�^���X
		D3DXVECTOR3 Near[4];
		Near[0] = D3DXVECTOR3(x1, y1, viewport.MinZ); // ���� (�ϊ���)
		Near[1] = D3DXVECTOR3(x2, y1, viewport.MinZ); // �E�� (�ϊ���)
		Near[2] = D3DXVECTOR3(x1, y2, viewport.MinZ); // ���� (�ϊ���)
		Near[3] = D3DXVECTOR3(x2, y2, viewport.MinZ); // �E�� (�ϊ���)

		D3DXVECTOR3 Far[4];
		Far[0] = D3DXVECTOR3(x1, y1, viewport.MaxZ); // ���� (�ϊ���)
		Far[1] = D3DXVECTOR3(x2, y1, viewport.MaxZ); // �E�� (�ϊ���)
		Far[2] = D3DXVECTOR3(x1, y2, viewport.MaxZ); // ���� (�ϊ���)
		Far[3] = D3DXVECTOR3(x2, y2, viewport.MaxZ); // �E�� (�ϊ���)

		// ������̂W�_�̌v�Z
		D3DXMATRIX mat_world;
		D3DXMatrixIdentity(&mat_world);
		D3DVIEWPORT9 *pViewport = const_cast<D3DVIEWPORT9*>(&viewport);

		// ���[���h �� �r���[ �� �ˉe �� �X�N���[���ϊ� �̋t���s��
		for(int i = 0; i < 4; ++i)
		{
			D3DXVec3Unproject(&Near[i], &Near[i],pViewport, &matProj, &matView, &mat_world);
			D3DXVec3Unproject(&Far[i], &Far[i],pViewport, &matProj, &matView, &mat_world);
		}

		// �������6�̖ʂ��Z�o
		D3DXPLANE Top, Bottom, Left, Right, Front, Back;

		// �� ( F����AN����AN�E�� )
		D3DXPlaneNormalize(&Top,D3DXPlaneFromPoints(&Top, &(Far[2]), &(Near[2]), &(Near[3])));
		// �� ( F�����AN�E���AN���� )
		D3DXPlaneNormalize(&Bottom,D3DXPlaneFromPoints(&Bottom, &(Far[0]), &(Near[1]), &(Near[0])));

		// �� ( F�����AN�����AN���� )
		D3DXPlaneNormalize(&Left,D3DXPlaneFromPoints(&Left, &(Far[0]), &(Near[0]), &(Near[2])));
		// �E ( F�E���AN�E��AN�E�� )
		D3DXPlaneNormalize(&Right,D3DXPlaneFromPoints(&Right, &(Far[1]), &(Near[3]), &(Near[1])));

		// ��O ( N����AN�����AN�E��)
		D3DXPlaneNormalize(&Front,D3DXPlaneFromPoints(&Front, &(Near[2]), &(Near[0]), &(Near[3])));
		// �� ( F�E��AF�����AF����)
		D3DXPlaneNormalize(&Back,D3DXPlaneFromPoints(&Back, &(Far[3]), &(Far[0]), &(Far[2])));

		_view_plane[ViewVolumePlaneTop] = Top;
		_view_plane[ViewVolumePlaneBottom] = Bottom;
		_view_plane[ViewVolumePlaneLeft] = Left;
		_view_plane[ViewVolumePlaneRight] = Right;
		_view_plane[ViewVolumePlaneFront] = Front;
		_view_plane[ViewVolumePlaneBack] = Back;
	}


	//=============================================================================
	// ������J�����O �`�F�b�N
	inline bool ClipCheck(const D3DXVECTOR3& pos, const float& radius)
	{

		//const D3DXPLANE& Top = _view_plane[ViewVolumePlaneTop];
		//const D3DXPLANE& Bottom = _view_plane[ViewVolumePlaneBottom];
		const D3DXPLANE& Left = _view_plane[ViewVolumePlaneLeft];
		const D3DXPLANE& Right = _view_plane[ViewVolumePlaneRight];
		const D3DXPLANE& Front = _view_plane[ViewVolumePlaneFront];
		const D3DXPLANE& Back = _view_plane[ViewVolumePlaneBack];

		/*if(Top.a*pos.x + Top.b*pos.y + Top.c * pos.z + Top.d > radius)
		{
			return false;
		}
		else if(Bottom.a*pos.x + Bottom.b*pos.y + Bottom.c * pos.z + Bottom.d > radius)
		{
			return false;
		}*/

		if(Left.a*pos.x + Left.b*pos.y + Left.c * pos.z + Left.d > radius)
		{
			return false;
		}
		else if(Right.a*pos.x + Right.b*pos.y + Right.c * pos.z + Right.d > radius)
		{
			return false;
		}

		if(Front.a*pos.x + Front.b*pos.y + Front.c * pos.z + Front.d > radius)
		{
			return false;
		}
		else if(Back.a*pos.x + Back.b*pos.y + Back.c * pos.z + Back.d > radius)
		{
			return false;
		}

		return true;
	}

	//=============================================================================
	// ������J�����O �`�F�b�N : box
	inline bool ClipCheckBox(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
	{

		const D3DXPLANE& Top = _view_plane[ViewVolumePlaneTop];
		const D3DXPLANE& Bottom = _view_plane[ViewVolumePlaneBottom];
		const D3DXPLANE& Left = _view_plane[ViewVolumePlaneLeft];
		const D3DXPLANE& Right = _view_plane[ViewVolumePlaneRight];
		const D3DXPLANE& Front = _view_plane[ViewVolumePlaneFront];
		const D3DXPLANE& Back = _view_plane[ViewVolumePlaneBack];

		if( Top.a*pos.x + Top.b*pos.y + Top.c * pos.z + Top.d > size.y )
		{
			return false;
		}
		else if( Bottom.a*pos.x + Bottom.b*pos.y + Bottom.c * pos.z + Bottom.d > size .y)
		{
			return false;
		}

		if( Left.a*pos.x + Left.b*pos.y + Left.c * pos.z + Left.d > size.x )
		{
			return false;
		}
		else if( Right.a*pos.x + Right.b*pos.y + Right.c * pos.z + Right.d > size.x )
		{
			return false;
		}

		if( Front.a*pos.x + Front.b*pos.y + Front.c * pos.z + Front.d > size.z )
		{
			return false;
		}
		else if( Back.a*pos.x + Back.b*pos.y + Back.c * pos.z + Back.d > size.z )
		{
			return false;
		}

		return true;
	}

private:
	D3DXPLANE _view_plane[ViewVolumePlaneMax];
};