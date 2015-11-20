//=============================================================================
//
// ” ‚Æ” ‚ÌÕ“Ë”»’èƒNƒ‰ƒX [BoxAndBox.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "BoxAndBox.h"
#include "BoundingBox.h"


//=========================================================================
// Õ“Ë”»’èˆ—
//=========================================================================
bool BoxAndBox::Check(Shape *shapeA, Shape *shapeB)
{
	BoundingBox *boxA = dynamic_cast<BoundingBox *>(shapeA);
	BoundingBox *boxB = dynamic_cast<BoundingBox *>(shapeB);

	D3DXVECTOR3 minA = boxA->GetMin();
	D3DXVECTOR3 maxA = boxA->GetMax();
	D3DXVECTOR3 minB = boxB->GetMin();
	D3DXVECTOR3 maxB = boxB->GetMax();

	return (minA.z < maxB.z) && (minB.z < maxA.z) && (minA.x < maxB.x)
		&& (minB.x < maxA.x) && (minA.y < maxB.y) && (minB.y < maxA.y) ? true : false;
}


// End of file