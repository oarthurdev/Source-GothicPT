#include <windows.h>
#include "smlib3d\\smd3d.h"


BOOL CollisionLineVSPolygon(VECTOR* lpCollisionPoint, VECTOR* lpLineBegin, VECTOR* lpLineEnd,
							VECTOR* lpPolygonVtx1, VECTOR* lpPolygonVtx2, VECTOR* lpPolygonVtx3);

int smVectMatrix(VECTOR* lpPolygonVtx1, VECTOR* lpPolygonVtx2, VECTOR* lpPolygonVtx3);


float Vertex[3][3] = {
	{	20,   40,  0 },
	{	-10,  10, 10 },
	{	30 , 5, 5 }
};

float fLine[2][3] = {
	{ 5, 10 , 5 },
	{ 5,-10 , 5 }
};

void mksInit()
{
	int cnt;
	VECTOR CollisionPoint, Line[2];
	VECTOR v[3];

	for(cnt = 0; cnt < 3; cnt++)
	{
		v[cnt].x = Vertex[cnt][0];
		v[cnt].y = Vertex[cnt][1];
		v[cnt].z = Vertex[cnt][2];
	}
	for(cnt = 0; cnt < 2; cnt++)
	{
		Line[cnt].x = fLine[cnt][0];
		Line[cnt].y = fLine[cnt][1];
		Line[cnt].z = fLine[cnt][2];
	}

	cnt = CollisionLineVSPolygon(&CollisionPoint, &Line[0], &Line[1],
								 &v[0], &v[1], &v[2]);


	smVectMatrix(&v[0], &v[1], &v[2]);


	cnt = 0;

}




void smDRotateXMatrixSin(smDMATRIX &m, double sine, double cosine)
{
	m._22 = cosine;
	m._23 = sine;
	m._32 = -sine;
	m._33 = cosine;
}


void smDRotateYMatrixSin(smDMATRIX &m, double sine, double cosine)
{
	m._11 = cosine;
	m._13 = -sine;
	m._31 = sine;
	m._33 = cosine;
}


void smDRotateZMatrixSin(smDMATRIX &m, double sine, double cosine)
{
	m._11 = cosine;
	m._12 = sine;
	m._21 = -sine;
	m._22 = cosine;
}


void smFRotateXMatrixSin(smFMATRIX &m, float sine, float cosine)
{
	m._22 = cosine;
	m._23 = sine;
	m._32 = -sine;
	m._33 = cosine;
}


void smFRotateYMatrixSin(smFMATRIX &m, float sine, float cosine)
{
	m._11 = cosine;
	m._13 = -sine;
	m._31 = sine;
	m._33 = cosine;
}


void smFRotateZMatrixSin(smFMATRIX &m, float sine, float cosine)
{
	m._11 = cosine;
	m._12 = sine;
	m._21 = -sine;
	m._22 = cosine;
}


int smVectMatrix(VECTOR* lpPolygonVtx1,
				 VECTOR* lpPolygonVtx2,
				 VECTOR* lpPolygonVtx3)

{



	D3DVECTOR PolygonNormal, u, v;
	u.x = lpPolygonVtx2->x - lpPolygonVtx1->x;
	u.y = lpPolygonVtx2->y - lpPolygonVtx1->y;
	u.z = lpPolygonVtx2->z - lpPolygonVtx1->z;

	v.x = lpPolygonVtx3->x - lpPolygonVtx1->x;
	v.y = lpPolygonVtx3->y - lpPolygonVtx1->y;
	v.z = lpPolygonVtx3->z - lpPolygonVtx1->z;

	PolygonNormal.x = u.y*v.z - u.z*v.y;
	PolygonNormal.y = u.z*v.x - u.x*v.z;
	PolygonNormal.z = u.x*v.y - u.y*v.x;


	float CosX, SinX, CosY, SinY;
	float x, y, z, w, s;

	x = PolygonNormal.x;
	y = -PolygonNormal.y;
	z = PolygonNormal.z;

	w = (float)sqrt(x*x + z*z);
	s = (float)sqrt(w*w + y*y);

	CosX = w / s;
	SinX = y / s;
	if(w == 0)
	{
		CosY = 0;
		SinY = 1;
	}
	else
	{
		CosY = z / w;
		SinY = x / w;
	}

	smFMATRIX	fMatInv, fMat, fMatX, fMatY;


	smFIdentityMatrix(fMat);
	smFIdentityMatrix(fMatX);
	smFIdentityMatrix(fMatY);

	smFRotateXMatrixSin(fMatX, SinX, CosX);
	smFRotateYMatrixSin(fMatY, SinY, CosY);

	smFMatrixMult(fMatInv, fMatX, fMatY);
	smFMatrixInvert(fMat, fMatInv);

	float rx1, ry1, rz1;
	float rx2, ry2, rz2;
	float rx3, ry3, rz3;

	x = lpPolygonVtx1->x;
	y = lpPolygonVtx1->y;
	z = lpPolygonVtx1->z;

	rx1 = x * fMat._11 +
		y * fMat._21 +
		z * fMat._31;

	ry1 = x * fMat._12 +
		y * fMat._22 +
		z * fMat._32;

	rz1 = x * fMat._13 +
		y * fMat._23 +
		z * fMat._33;

	x = lpPolygonVtx2->x;
	y = lpPolygonVtx2->y;
	z = lpPolygonVtx2->z;

	rx2 = x * fMat._11 +
		y * fMat._21 +
		z * fMat._31;

	ry2 = x * fMat._12 +
		y * fMat._22 +
		z * fMat._32;

	rz2 = x * fMat._13 +
		y * fMat._23 +
		z * fMat._33;

	x = lpPolygonVtx3->x;
	y = lpPolygonVtx3->y;
	z = lpPolygonVtx3->z;

	rx3 = x * fMat._11 +
		y * fMat._21 +
		z * fMat._31;

	ry3 = x * fMat._12 +
		y * fMat._22 +
		z * fMat._32;

	rz3 = x * fMat._13 +
		y * fMat._23 +
		z * fMat._33;

	x = lpPolygonVtx2->x - lpPolygonVtx1->x;
	y = lpPolygonVtx2->y - lpPolygonVtx1->y;
	z = lpPolygonVtx2->z - lpPolygonVtx1->z;
	w = (float)sqrt(x*x + y*y + z*z);

	x = rx2 - rx1;
	y = ry2 - ry1;
	z = rz2 - rz1;
	s = (float)sqrt(x*x + y*y + z*z);

	return TRUE;
}





BOOL CollisionLineVSPolygon(VECTOR* lpCollisionPoint, VECTOR*
							lpLineBegin, VECTOR* lpLineEnd, VECTOR* lpPolygonVtx1, VECTOR*
							lpPolygonVtx2, VECTOR* lpPolygonVtx3)
{

	D3DVECTOR PolygonNormal, u, v;
	u.x = lpPolygonVtx2->x - lpPolygonVtx1->x;
	u.y = lpPolygonVtx2->y - lpPolygonVtx1->y;
	u.z = lpPolygonVtx2->z - lpPolygonVtx1->z;

	v.x = lpPolygonVtx3->x - lpPolygonVtx1->x;
	v.y = lpPolygonVtx3->y - lpPolygonVtx1->y;
	v.z = lpPolygonVtx3->z - lpPolygonVtx1->z;

	PolygonNormal.x = u.y*v.z - u.z*v.y;
	PolygonNormal.y = u.z*v.x - u.x*v.z;
	PolygonNormal.z = u.x*v.y - u.y*v.x;


	float denominator = ((PolygonNormal.x * (lpLineEnd->x - lpLineBegin->x)) +
		(PolygonNormal.y * (lpLineEnd->y - lpLineBegin->y)) +
						 (PolygonNormal.z * (lpLineEnd->z - lpLineBegin->z)));

	float t;

	if(denominator != 0)
	{
		t = ((-PolygonNormal.x * lpLineBegin->x + PolygonNormal.x * lpPolygonVtx1->x) +
			(-PolygonNormal.y * lpLineBegin->y + PolygonNormal.y * lpPolygonVtx1->y) +
			 (-PolygonNormal.z * lpLineBegin->z + PolygonNormal.z * lpPolygonVtx1->z)) / denominator;

		if((t >= 0.0f) && (t <= 1.0f))
		{
			lpCollisionPoint->x = lpLineBegin->x + (lpLineEnd->x - lpLineBegin->x) * t;
			lpCollisionPoint->y = lpLineBegin->y + (lpLineEnd->y - lpLineBegin->y) * t;
			lpCollisionPoint->z = lpLineBegin->z + (lpLineEnd->z - lpLineBegin->z) * t;
			return TRUE;
		}
		else
			return FALSE;
	}
	else
		return FALSE;
}

