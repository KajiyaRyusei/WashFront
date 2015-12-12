//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 視錘台カリング
//
// Created by Ryusei Kajiya on 20151201
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//*****************************************************************************
// 多重インクルード防止
#pragma once

//*****************************************************************************
// クラス設計
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
	// 視錘台を作成
	inline void MakeClip(
		const D3DVIEWPORT9& viewport,
		D3DXMATRIX matProj,
		D3DXMATRIX matView)
	{
		// viewport.MinZ / MaxZ は、通常それぞれ 0 / 1
		float x1 = (float)viewport.X;
		float y1 = (float)viewport.Y;
		float x2 = (float)viewport.X + (float)viewport.Width;
		float y2 = (float)viewport.Y + (float)viewport.Height;

		// 視錐台の８点が格納されるインスタンス
		D3DXVECTOR3 Near[4];
		Near[0] = D3DXVECTOR3(x1, y1, viewport.MinZ); // 左下 (変換後)
		Near[1] = D3DXVECTOR3(x2, y1, viewport.MinZ); // 右下 (変換後)
		Near[2] = D3DXVECTOR3(x1, y2, viewport.MinZ); // 左上 (変換後)
		Near[3] = D3DXVECTOR3(x2, y2, viewport.MinZ); // 右上 (変換後)

		D3DXVECTOR3 Far[4];
		Far[0] = D3DXVECTOR3(x1, y1, viewport.MaxZ); // 左下 (変換後)
		Far[1] = D3DXVECTOR3(x2, y1, viewport.MaxZ); // 右下 (変換後)
		Far[2] = D3DXVECTOR3(x1, y2, viewport.MaxZ); // 左上 (変換後)
		Far[3] = D3DXVECTOR3(x2, y2, viewport.MaxZ); // 右上 (変換後)

		// 視錐台の８点の計算
		D3DXMATRIX mat_world;
		D3DXMatrixIdentity(&mat_world);
		D3DVIEWPORT9 *pViewport = const_cast<D3DVIEWPORT9*>(&viewport);

		// ワールド → ビュー → 射影 → スクリーン変換 の逆を行う
		for(int i = 0; i < 4; ++i)
		{
			D3DXVec3Unproject(&Near[i], &Near[i],pViewport, &matProj, &matView, &mat_world);
			D3DXVec3Unproject(&Far[i], &Far[i],pViewport, &matProj, &matView, &mat_world);
		}

		// 視錐台の6つの面を算出
		D3DXPLANE Top, Bottom, Left, Right, Front, Back;

		// 上 ( F左上、N左上、N右上 )
		D3DXPlaneNormalize(&Top,D3DXPlaneFromPoints(&Top, &(Far[2]), &(Near[2]), &(Near[3])));
		// 下 ( F左下、N右下、N左下 )
		D3DXPlaneNormalize(&Bottom,D3DXPlaneFromPoints(&Bottom, &(Far[0]), &(Near[1]), &(Near[0])));

		// 左 ( F左下、N左下、N左上 )
		D3DXPlaneNormalize(&Left,D3DXPlaneFromPoints(&Left, &(Far[0]), &(Near[0]), &(Near[2])));
		// 右 ( F右下、N右上、N右下 )
		D3DXPlaneNormalize(&Right,D3DXPlaneFromPoints(&Right, &(Far[1]), &(Near[3]), &(Near[1])));

		// 手前 ( N左上、N左下、N右上)
		D3DXPlaneNormalize(&Front,D3DXPlaneFromPoints(&Front, &(Near[2]), &(Near[0]), &(Near[3])));
		// 奥 ( F右上、F左下、F左上)
		D3DXPlaneNormalize(&Back,D3DXPlaneFromPoints(&Back, &(Far[3]), &(Far[0]), &(Far[2])));

		_view_plane[ViewVolumePlaneTop] = Top;
		_view_plane[ViewVolumePlaneBottom] = Bottom;
		_view_plane[ViewVolumePlaneLeft] = Left;
		_view_plane[ViewVolumePlaneRight] = Right;
		_view_plane[ViewVolumePlaneFront] = Front;
		_view_plane[ViewVolumePlaneBack] = Back;
	}


	//=============================================================================
	// 視錐台カリング チェック
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
	// 視錐台カリング チェック : box
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