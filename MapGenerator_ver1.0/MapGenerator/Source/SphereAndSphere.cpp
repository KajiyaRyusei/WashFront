//=============================================================================
//
// ‹…‚Æ‹…‚ÌÕ“Ë”»’èƒNƒ‰ƒX [SphereAndSphere.cpp]
// Author : KEITA OHUCHI
//
//=============================================================================

#include "SphereAndSphere.h"
#include "BoundingSphere.h"
#include "Renderer.h"


//=========================================================================
// Õ“Ë”»’èˆ—
//=========================================================================
bool SphereAndSphere::Check(Shape *shapeA, Shape *shapeB)
{
	BoundingSphere *sphereA = dynamic_cast<BoundingSphere *>(shapeA);
	BoundingSphere *sphereB = dynamic_cast<BoundingSphere *>(shapeB);

	D3DXVECTOR3 vecAToB = sphereA->GetPosition() - sphereB->GetPosition();
	float lenSqAToB = D3DXVec3LengthSq(&vecAToB);
	float radiusAB = sphereA->GetRadius() + sphereB->GetRadius();

	return lenSqAToB < radiusAB * radiusAB ? true : false;
}


// End of file