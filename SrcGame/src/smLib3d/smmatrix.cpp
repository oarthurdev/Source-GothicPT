#include "smd3d.h"


void smZeroMatrix(smMATRIX &m)
{
	ZeroMemory(&m, sizeof(smMATRIX));

}


void smIdentityMatrix(smMATRIX &m)
{
	m._11 = fONE;   m._12 = 0;       m._13 = 0;       m._14 = 0;
	m._21 = 0;   m._22 = fONE;    m._23 = 0;       m._24 = 0;
	m._31 = 0;   m._32 = 0;       m._33 = fONE;    m._34 = 0;
	m._41 = 0;   m._42 = 0;       m._43 = 0;	      m._44 = fONE;

}


void smMatrixMult(smMATRIX &m, smMATRIX &a, smMATRIX &b)
{

	int *pA = (int *)&a;
	int *pB = (int *)&b;
	int  pM[16];

	ZeroMemory(pM, sizeof(smMATRIX));

	for(WORD i = 0; i < 4; i++)
		for(WORD j = 0; j < 4; j++)
			for(WORD k = 0; k < 4; k++)
				pM[4 * j + i] += (pA[4 * j + k] * pB[4 * k + i]) >> FLOATNS;

	memcpy(&m, pM, sizeof(smMATRIX));

}



void smMatrixMult2(smMATRIX &m, smMATRIX &a, smMATRIX &b)
{

	int *pA = (int *)&a;
	int *pB = (int *)&b;
	int  pM[16];

	ZeroMemory(pM, sizeof(smMATRIX));

	for(WORD i = 0; i < 4; i++)
		for(WORD j = 0; j < 4; j++)
			for(WORD k = 0; k < 4; k++)
				pM[4 * i + j] += (pA[4 * k + j] * pB[4 * i + k]) >> FLOATNS;

	memcpy(&m, pM, sizeof(smMATRIX));

}




void smRotateXMatrix(smMATRIX &m, int rads)
{
	int 	cosine, sine;

	cosine = GetCos[rads] >> FLOATDS;
	sine = GetSin[rads] >> FLOATDS;

	m._22 = cosine;
	m._23 = sine;
	m._32 = -sine;
	m._33 = cosine;
}


void smRotateYMatrix(smMATRIX &m, int rads)
{
	int cosine, sine;

	cosine = GetCos[rads] >> FLOATDS;
	sine = GetSin[rads] >> FLOATDS;

	m._11 = cosine;
	m._13 = -sine;
	m._31 = sine;
	m._33 = cosine;

}


void smRotateZMatrix(smMATRIX &m, int rads)
{
	int 	cosine, sine;

	cosine = GetCos[rads] >> FLOATDS;
	sine = GetSin[rads] >> FLOATDS;

	m._11 = cosine;
	m._12 = sine;
	m._21 = -sine;
	m._22 = cosine;

}



void smTranslateMatrix(smMATRIX &m, int x, int y, int z)
{

	m._41 = x << FLOATNS;
	m._42 = y << FLOATNS;
	m._43 = z << FLOATNS;

}


void smMatrixShift(smMATRIX &m, int shift)
{
	m._11 >>= shift;
	m._12 >>= shift;
	m._13 >>= shift;
	m._14 >>= shift;

	m._21 >>= shift;
	m._22 >>= shift;
	m._23 >>= shift;
	m._24 >>= shift;

	m._31 >>= shift;
	m._32 >>= shift;
	m._33 >>= shift;
	m._34 >>= shift;

	m._41 >>= shift;
	m._42 >>= shift;
	m._43 >>= shift;
	m._44 >>= shift;
}

int smMatrixInvert(smMATRIX &q, smMATRIX &a)
{

	if(abs(a._44 - fONE) > 1)
		return FALSE;
	if(abs(a._14) > 1 || abs(a._24) > 1 || abs(a._34) > 1)
		return FALSE;



	int fDetInv = ((a._11 * ((a._22 * a._33 - a._23 * a._32) >> FLOATNS)) -
		(a._12 * ((a._21 * a._33 - a._23 * a._31) >> FLOATNS)) +
				   (a._13 * ((a._21 * a._32 - a._22 * a._31) >> FLOATNS))) >> FLOATNS;

	if(fDetInv)
		fDetInv = (fONE << FLOATNS) / fDetInv;







	q._11 = (fDetInv * ((a._22 * a._33 - a._23 * a._32) >> FLOATNS) >> FLOATNS);
	q._12 = -(fDetInv * ((a._12 * a._33 - a._13 * a._32) >> FLOATNS) >> FLOATNS);
	q._13 = (fDetInv * ((a._12 * a._23 - a._13 * a._22) >> FLOATNS) >> FLOATNS);
	q._14 = 0;

	q._21 = -(fDetInv * ((a._21 * a._33 - a._23 * a._31) >> FLOATNS) >> FLOATNS);
	q._22 = (fDetInv * ((a._11 * a._33 - a._13 * a._31) >> FLOATNS) >> FLOATNS);
	q._23 = -(fDetInv * ((a._11 * a._23 - a._13 * a._21) >> FLOATNS) >> FLOATNS);
	q._24 = 0;

	q._31 = (fDetInv * ((a._21 * a._32 - a._22 * a._31) >> FLOATNS) >> FLOATNS);
	q._32 = -(fDetInv * ((a._11 * a._32 - a._12 * a._31) >> FLOATNS) >> FLOATNS);
	q._33 = (fDetInv * ((a._11 * a._22 - a._12 * a._21) >> FLOATNS) >> FLOATNS);
	q._34 = 0;

	q._41 = -((a._41 * q._11 + a._42 * q._21 + a._43 * q._31) >> FLOATNS);
	q._42 = -((a._41 * q._12 + a._42 * q._22 + a._43 * q._32) >> FLOATNS);
	q._43 = -((a._41 * q._13 + a._42 * q._23 + a._43 * q._33) >> FLOATNS);
	q._44 = fONE;

	return TRUE;
}





void smMatrixFromQuaternion(smMATRIX& mat, float x, float y, float z, float w)
{
	int xx = (int)(x*x*fONE); int yy = (int)(y*y*fONE); int zz = (int)(z*z*fONE);
	int xy = (int)(x*y*fONE); int xz = (int)(x*z*fONE); int yz = (int)(y*z*fONE);
	int wx = (int)(w*x*fONE); int wy = (int)(w*y*fONE); int wz = (int)(w*z*fONE);

	mat._11 = fONE - 2 * (yy + zz);
	mat._12 = 2 * (xy - wz);
	mat._13 = 2 * (xz + wy);

	mat._21 = 2 * (xy + wz);
	mat._22 = fONE - 2 * (xx + zz);
	mat._23 = 2 * (yz - wx);

	mat._31 = 2 * (xz - wy);
	mat._32 = 2 * (yz + wx);
	mat._33 = fONE - 2 * (xx + yy);

	mat._14 = mat._24 = mat._34 = 0;
	mat._41 = mat._42 = mat._43 = 0;
	mat._44 = fONE;
}





void smQuaternionMult(int& Qx, int& Qy, int& Qz, int & Qw,
					  int Ax, int Ay, int Az, int Aw,
					  int Bx, int By, int Bz, int Bw)
{
	int Dx = (Bw*Ax + Bx*Aw + By*Az + Bz*Ay) >> FLOATNS;
	int Dy = (Bw*Ay + By*Aw + Bz*Ax + Bx*Az) >> FLOATNS;
	int Dz = (Bw*Az + Bz*Aw + Bx*Ay + By*Ax) >> FLOATNS;
	int Dw = (Bw*Aw + Bx*Ax + By*Ay + Bz*Az) >> FLOATNS;

	Qx = Dx; Qy = Dy; Qz = Dz; Qw = Dw;
}





void smQuaternionFromAxis(float &x, float &y, float &z, float &w)
{

	double a, b, c, d;

	double fHalfAngle = w / 2;
	double sn = sin(fHalfAngle);
	d = cos(fHalfAngle);

	a = sn*x;
	b = sn*y;
	c = sn*z;

	x = (float)a;
	y = (float)b;
	z = (float)c;
	w = (float)d;
}

void smDQuaternionFromAxis(double &x, double &y, double &z, double &w)
{

	double a, b, c, d;

	double fHalfAngle = w / 2;
	double sn = sin(fHalfAngle);
	d = cos(fHalfAngle);

	a = sn*x;
	b = sn*y;
	c = sn*z;

	x = a;
	y = b;
	z = c;
	w = d;
}














VOID D3DMath_QuaternionSlerp(FLOAT& Qx, FLOAT& Qy, FLOAT& Qz, FLOAT& Qw, FLOAT Ax, FLOAT Ay, FLOAT Az, FLOAT Aw,
							 FLOAT Bx, FLOAT By, FLOAT Bz, FLOAT Bw, FLOAT fAlpha)
{
	FLOAT fScale1;
	FLOAT fScale2;


	FLOAT fCosTheta = Ax*Bx + Ay*By + Az*Bz + Aw*Bw;

	if(fCosTheta < 0.0f)
	{

		Ax = -Ax; Ay = -Ay; Ax = -Az; Aw = -Aw;
		fCosTheta = -fCosTheta;
	}

	if(fCosTheta + 1.0f > 0.05f)
	{

		if(1.0f - fCosTheta < 0.05f)
		{
			fScale1 = 1.0f - fAlpha;
			fScale2 = fAlpha;
		}
		else
		{
			FLOAT fTheta = (FLOAT)acos(fCosTheta);
			FLOAT fSinTheta = (FLOAT)sin(fTheta);

			fScale1 = (FLOAT)sin(fTheta * (1.0f - fAlpha)) / fSinTheta;
			fScale2 = (FLOAT)sin(fTheta * fAlpha) / fSinTheta;
		}
	}
	else
	{
		Bx = -Ay;
		By = Ax;
		Bz = -Aw;
		Bw = Az;
		fScale1 = (FLOAT)sin(g_PI * (0.5f - fAlpha));
		fScale2 = (FLOAT)sin(g_PI * fAlpha);
	}

	Qx = fScale1 * Ax + fScale2 * Bx;
	Qy = fScale1 * Ay + fScale2 * By;
	Qz = fScale1 * Az + fScale2 * Bz;
	Qw = fScale1 * Aw + fScale2 * Bw;
}


void smMatrixFromDMatrix(smMATRIX &m, smDMATRIX &d)
{
	m._11 = (int)(d._11 * fONE);
	m._12 = (int)(d._12 * fONE);
	m._13 = (int)(d._13 * fONE);
	m._14 = (int)(d._14 * fONE);

	m._21 = (int)(d._21 * fONE);
	m._22 = (int)(d._22 * fONE);
	m._23 = (int)(d._23 * fONE);
	m._24 = (int)(d._24 * fONE);

	m._31 = (int)(d._31 * fONE);
	m._32 = (int)(d._32 * fONE);
	m._33 = (int)(d._33 * fONE);
	m._34 = (int)(d._34 * fONE);

	m._41 = (int)(d._41 * fONE);
	m._42 = (int)(d._42 * fONE);
	m._43 = (int)(d._43 * fONE);
	m._44 = (int)(d._44 * fONE);
}

void smDZeroMatrix(smDMATRIX &m)
{
	ZeroMemory(&m, sizeof(smDMATRIX));

}

void smDIdentityMatrix(smDMATRIX &m)
{
	m._11 = 1;   m._12 = 0;      m._13 = 0;      m._14 = 0;
	m._21 = 0;   m._22 = 1;		m._23 = 0;      m._24 = 0;
	m._31 = 0;   m._32 = 0;      m._33 = 1;		m._34 = 0;
	m._41 = 0;   m._42 = 0;      m._43 = 0;      m._44 = 1;

}


void smDRotateXMatrix(smDMATRIX &m, int rads)
{
	double 	cosine, sine;

	cosine = dbGetCos[rads];
	sine = dbGetSin[rads];

	m._22 = cosine;
	m._23 = sine;
	m._32 = -sine;
	m._33 = cosine;
}


void smDRotateYMatrix(smDMATRIX &m, int rads)
{
	double 	cosine, sine;

	cosine = dbGetCos[rads];
	sine = dbGetSin[rads];

	m._11 = cosine;
	m._13 = -sine;
	m._31 = sine;
	m._33 = cosine;

}


void smDRotateZMatrix(smDMATRIX &m, int rads)
{
	double 	cosine, sine;

	cosine = dbGetCos[rads];
	sine = dbGetSin[rads];

	m._11 = cosine;
	m._12 = sine;
	m._21 = -sine;
	m._22 = cosine;

}


void smDTranslateMatrix(smDMATRIX &m, float x, float y, float z)
{

	m._41 = x;
	m._42 = y;
	m._43 = z;

}


void smDMatrixMult(smDMATRIX &m, smDMATRIX &a, smDMATRIX &b)
{

	double *pA = (double *)&a;
	double *pB = (double *)&b;
	double  pM[16];

	ZeroMemory(pM, sizeof(smDMATRIX));

	for(WORD i = 0; i < 4; i++)
		for(WORD j = 0; j < 4; j++)
			for(WORD k = 0; k < 4; k++)
				pM[4 * j + i] += pA[4 * j + k] * pB[4 * k + i];

	memcpy(&m, pM, sizeof(smDMATRIX));

}


void smDMatrixFromQuaternion(smDMATRIX& mat, double x, double y, double z, double w)
{
	double xx = x*x; double yy = y*y; double zz = z*z;
	double xy = x*y; double xz = x*z; double yz = y*z;
	double wx = w*x; double wy = w*y; double wz = w*z;

	mat._11 = 1 - 2 * (yy + zz);
	mat._12 = 2 * (xy - wz);
	mat._13 = 2 * (xz + wy);

	mat._21 = 2 * (xy + wz);
	mat._22 = 1 - 2 * (xx + zz);
	mat._23 = 2 * (yz - wx);

	mat._31 = 2 * (xz - wy);
	mat._32 = 2 * (yz + wx);
	mat._33 = 1 - 2 * (xx + yy);

	mat._14 = mat._24 = mat._34 = 0;
	mat._41 = mat._42 = mat._43 = 0;
	mat._44 = 1;
}





void smDQuaternionFromMatrix(FLOAT& x, FLOAT& y, FLOAT& z, FLOAT& w, smDMATRIX& mat)
{
	if(mat._11 + mat._22 + mat._33 > 0.0f)
	{
		FLOAT s = (FLOAT)sqrt(mat._11 + mat._22 + mat._33 + mat._44);

		x = (FLOAT)((mat._23 - mat._32) / (2 * s));
		y = (FLOAT)((mat._31 - mat._13) / (2 * s));
		z = (FLOAT)((mat._12 - mat._21) / (2 * s));
		w = 0.5f * s;
	}
	else
	{


	}
	FLOAT xx = x*x; FLOAT yy = y*y; FLOAT zz = z*z;
	FLOAT xy = x*y; FLOAT xz = x*z; FLOAT yz = y*z;
	FLOAT wx = w*x; FLOAT wy = w*y; FLOAT wz = w*z;

	mat._11 = 1 - 2 * (yy + zz);
	mat._12 = 2 * (xy - wz);
	mat._13 = 2 * (xz + wy);

	mat._21 = 2 * (xy + wz);
	mat._22 = 1 - 2 * (xx + zz);
	mat._23 = 2 * (yz - wx);

	mat._31 = 2 * (xz - wy);
	mat._32 = 2 * (yz + wx);
	mat._33 = 1 - 2 * (xx + yy);

	mat._14 = mat._24 = mat._34 = 0.0f;
	mat._41 = mat._42 = mat._43 = 0.0f;
	mat._44 = 1.0f;
}





void smEZeroMatrix(smEMATRIX &m)
{
	ZeroMemory(&m, sizeof(smMATRIX));

}


void smEIdentityMatrix(smEMATRIX &m)
{
	m._11 = wfONE;   m._12 = 0;       m._13 = 0;       m._14 = 0;
	m._21 = 0;    m._22 = wfONE;   m._23 = 0;       m._24 = 0;
	m._31 = 0;    m._32 = 0;       m._33 = wfONE;   m._34 = 0;
	m._41 = 0;    m._42 = 0;       m._43 = 0;	   m._44 = wfONE;

}


void smEMatrixMult(smEMATRIX &m, smEMATRIX &a, smEMATRIX &b)
{

	int *pA = (int *)&a;
	int *pB = (int *)&b;
	int  pM[16];

	ZeroMemory(pM, sizeof(smEMATRIX));

	for(WORD i = 0; i < 4; i++)
		for(WORD j = 0; j < 4; j++)
			for(WORD k = 0; k < 4; k++)
				pM[4 * j + i] += (pA[4 * j + k] * pB[4 * k + i]) >> wFLOATS;

	memcpy(&m, pM, sizeof(smEMATRIX));

}


void smEMatrixMult2(smEMATRIX &m, smEMATRIX &a, smEMATRIX &b)
{

	int *pA = (int *)&a;
	int *pB = (int *)&b;
	int  pM[16];

	ZeroMemory(pM, sizeof(smEMATRIX));

	for(WORD i = 0; i < 4; i++)
		for(WORD j = 0; j < 4; j++)
			for(WORD k = 0; k < 4; k++)
				pM[4 * i + j] += (pA[4 * k + j] * pB[4 * i + k]) >> wFLOATS;

	memcpy(&m, pM, sizeof(smEMATRIX));

}


void smERotateXMatrix(smEMATRIX &m, int rads)
{
	int 	cosine, sine;

	cosine = sdGetCos[rads];
	sine = sdGetSin[rads];

	m._22 = cosine;
	m._23 = sine;
	m._32 = -sine;
	m._33 = cosine;
}


void smERotateYMatrix(smEMATRIX &m, int rads)
{
	int 	cosine, sine;

	cosine = sdGetCos[rads];
	sine = sdGetSin[rads];

	m._11 = cosine;
	m._13 = -sine;
	m._31 = sine;
	m._33 = cosine;

}


void smERotateZMatrix(smEMATRIX &m, int rads)
{
	int 	cosine, sine;

	cosine = sdGetCos[rads];
	sine = sdGetSin[rads];

	m._11 = cosine;
	m._12 = sine;
	m._21 = -sine;
	m._22 = cosine;

}


void smETranslateMatrix(smEMATRIX &m, int x, int y, int z)
{

	m._41 = x << wSHIFT_FLOAT;
	m._42 = y << wSHIFT_FLOAT;
	m._43 = z << wSHIFT_FLOAT;

}


void smEMatrixShift(smEMATRIX &m, int shift)
{
	m._11 >>= shift;
	m._12 >>= shift;
	m._13 >>= shift;
	m._14 >>= shift;

	m._21 >>= shift;
	m._22 >>= shift;
	m._23 >>= shift;
	m._24 >>= shift;

	m._31 >>= shift;
	m._32 >>= shift;
	m._33 >>= shift;
	m._34 >>= shift;

	m._41 >>= shift;
	m._42 >>= shift;
	m._43 >>= shift;
	m._44 >>= shift;
}


void smFZeroMatrix(smFMATRIX &m)
{
	ZeroMemory(&m, sizeof(smFMATRIX));

}

void smFIdentityMatrix(smFMATRIX &m)
{
	m._11 = 1;   m._12 = 0;      m._13 = 0;      m._14 = 0;
	m._21 = 0;   m._22 = 1;		m._23 = 0;      m._24 = 0;
	m._31 = 0;   m._32 = 0;      m._33 = 1;		m._34 = 0;
	m._41 = 0;   m._42 = 0;      m._43 = 0;      m._44 = 1;

}







HRESULT smFMatrixInvert(smFMATRIX& q, smFMATRIX& a)
{
	if(fabs(a._44 - 1.0f) > .001f)
		return E_INVALIDARG;
	if(fabs(a._14) > .001f || fabs(a._24) > .001f || fabs(a._34) > .001f)
		return E_INVALIDARG;

	FLOAT fDetInv = 1.0f / (a._11 * (a._22 * a._33 - a._23 * a._32) -
							a._12 * (a._21 * a._33 - a._23 * a._31) +
							a._13 * (a._21 * a._32 - a._22 * a._31));

	q._11 = fDetInv * (a._22 * a._33 - a._23 * a._32);
	q._12 = -fDetInv * (a._12 * a._33 - a._13 * a._32);
	q._13 = fDetInv * (a._12 * a._23 - a._13 * a._22);
	q._14 = 0.0f;

	q._21 = -fDetInv * (a._21 * a._33 - a._23 * a._31);
	q._22 = fDetInv * (a._11 * a._33 - a._13 * a._31);
	q._23 = -fDetInv * (a._11 * a._23 - a._13 * a._21);
	q._24 = 0.0f;

	q._31 = fDetInv * (a._21 * a._32 - a._22 * a._31);
	q._32 = -fDetInv * (a._11 * a._32 - a._12 * a._31);
	q._33 = fDetInv * (a._11 * a._22 - a._12 * a._21);
	q._34 = 0.0f;

	q._41 = -(a._41 * q._11 + a._42 * q._21 + a._43 * q._31);
	q._42 = -(a._41 * q._12 + a._42 * q._22 + a._43 * q._32);
	q._43 = -(a._41 * q._13 + a._42 * q._23 + a._43 * q._33);
	q._44 = 1.0f;

	return S_OK;
}


void smFRotateXMatrix(smFMATRIX &m, int rads)
{
	float  	cosine, sine;

	cosine = (float)dbGetCos[rads];
	sine = (float)dbGetSin[rads];

	m._22 = cosine;
	m._23 = sine;
	m._32 = -sine;
	m._33 = cosine;
}


void smFRotateYMatrix(smFMATRIX &m, int rads)
{
	float 	cosine, sine;

	cosine = (float)dbGetCos[rads];
	sine = (float)dbGetSin[rads];

	m._11 = cosine;
	m._13 = -sine;
	m._31 = sine;
	m._33 = cosine;

}


void smFRotateZMatrix(smFMATRIX &m, int rads)
{
	float 	cosine, sine;

	cosine = (float)dbGetCos[rads];
	sine = (float)dbGetSin[rads];

	m._11 = cosine;
	m._12 = sine;
	m._21 = -sine;
	m._22 = cosine;

}


void smFTranslateMatrix(smFMATRIX &m, float x, float y, float z)
{

	m._41 = x;
	m._42 = y;
	m._43 = z;

}



void smFMatrixMult(smFMATRIX &m, smFMATRIX &a, smFMATRIX &b)
{

	float *pA = (float *)&a;
	float *pB = (float *)&b;
	float  pM[16];

	ZeroMemory(pM, sizeof(smFMATRIX));

	for(WORD i = 0; i < 4; i++)
		for(WORD j = 0; j < 4; j++)
			for(WORD k = 0; k < 4; k++)
				pM[4 * j + i] += pA[4 * j + k] * pB[4 * k + i];

	memcpy(&m, pM, sizeof(smFMATRIX));

}

void smFMatrixFromQuaternion(smFMATRIX& mat, float x, float y, float z, float w)
{
	float xx = x*x; float yy = y*y; float zz = z*z;
	float xy = x*y; float xz = x*z; float yz = y*z;
	float wx = w*x; float wy = w*y; float wz = w*z;

	mat._11 = 1 - 2 * (yy + zz);
	mat._12 = 2 * (xy - wz);
	mat._13 = 2 * (xz + wy);

	mat._21 = 2 * (xy + wz);
	mat._22 = 1 - 2 * (xx + zz);
	mat._23 = 2 * (yz - wx);

	mat._31 = 2 * (xz - wy);
	mat._32 = 2 * (yz + wx);
	mat._33 = 1 - 2 * (xx + yy);

	mat._14 = mat._24 = mat._34 = 0;
	mat._41 = mat._42 = mat._43 = 0;
	mat._44 = 1;
}





void smFQuaternionFromMatrix(FLOAT& x, FLOAT& y, FLOAT& z, FLOAT& w, smFMATRIX& mat)
{
	if(mat._11 + mat._22 + mat._33 > 0.0f)
	{
		FLOAT s = (FLOAT)sqrt(mat._11 + mat._22 + mat._33 + mat._44);

		x = (FLOAT)((mat._23 - mat._32) / (2 * s));
		y = (FLOAT)((mat._31 - mat._13) / (2 * s));
		z = (FLOAT)((mat._12 - mat._21) / (2 * s));
		w = 0.5f * s;
	}
	else
	{


	}
	FLOAT xx = x*x; FLOAT yy = y*y; FLOAT zz = z*z;
	FLOAT xy = x*y; FLOAT xz = x*z; FLOAT yz = y*z;
	FLOAT wx = w*x; FLOAT wy = w*y; FLOAT wz = w*z;

	mat._11 = 1 - 2 * (yy + zz);
	mat._12 = 2 * (xy - wz);
	mat._13 = 2 * (xz + wy);

	mat._21 = 2 * (xy + wz);
	mat._22 = 1 - 2 * (xx + zz);
	mat._23 = 2 * (yz - wx);

	mat._31 = 2 * (xz - wy);
	mat._32 = 2 * (yz + wx);
	mat._33 = 1 - 2 * (xx + yy);

	mat._14 = mat._24 = mat._34 = 0.0f;
	mat._41 = mat._42 = mat._43 = 0.0f;
	mat._44 = 1.0f;
}

void smMatrixFromFMatrix(smMATRIX &m, smFMATRIX &d)
{
	m._11 = (int)(d._11 * fONE);
	m._12 = (int)(d._12 * fONE);
	m._13 = (int)(d._13 * fONE);
	m._14 = (int)(d._14 * fONE);

	m._21 = (int)(d._21 * fONE);
	m._22 = (int)(d._22 * fONE);
	m._23 = (int)(d._23 * fONE);
	m._24 = (int)(d._24 * fONE);

	m._31 = (int)(d._31 * fONE);
	m._32 = (int)(d._32 * fONE);
	m._33 = (int)(d._33 * fONE);
	m._34 = (int)(d._34 * fONE);

	m._41 = (int)(d._41 * fONE);
	m._42 = (int)(d._42 * fONE);
	m._43 = (int)(d._43 * fONE);
	m._44 = (int)(d._44 * fONE);
}

void smFMatrixFromMatrix(smFMATRIX &m, smMATRIX &d)
{
	m._11 = ((float)d._11) / fONE;
	m._12 = ((float)d._12) / fONE;
	m._13 = ((float)d._13) / fONE;
	m._14 = ((float)d._14) / fONE;

	m._21 = ((float)d._21) / fONE;
	m._22 = ((float)d._22) / fONE;
	m._23 = ((float)d._23) / fONE;
	m._24 = ((float)d._24) / fONE;

	m._31 = ((float)d._31) / fONE;
	m._32 = ((float)d._32) / fONE;
	m._33 = ((float)d._33) / fONE;
	m._34 = ((float)d._34) / fONE;

	m._41 = ((float)d._41) / fONE;
	m._42 = ((float)d._42) / fONE;
	m._43 = ((float)d._43) / fONE;
	m._44 = ((float)d._44) / fONE;


}



void smFMatrixFromDMatrix(smFMATRIX &m, smDMATRIX &d)
{
	m._11 = (float)d._11;
	m._12 = (float)d._12;
	m._13 = (float)d._13;
	m._14 = (float)d._14;

	m._21 = (float)d._21;
	m._22 = (float)d._22;
	m._23 = (float)d._23;
	m._24 = (float)d._24;

	m._31 = (float)d._31;
	m._32 = (float)d._32;
	m._33 = (float)d._33;
	m._34 = (float)d._34;

	m._41 = (float)d._41;
	m._42 = (float)d._42;
	m._43 = (float)d._43;
	m._44 = (float)d._44;
}





HRESULT D3D_SetProjectionMatrix(D3DMATRIX &mat, float fFOV, float fAspect, float fNearPlane, float fFarPlane)
{
	if(fabs(fFarPlane - fNearPlane) < 0.01f)
		return E_INVALIDARG;
	if(fabs(sin(fFOV / 2)) < 0.01f)
		return E_INVALIDARG;

	FLOAT w = fAspect * (cosf(fFOV / 2) / sinf(fFOV / 2));
	FLOAT h = 1.0f  * cosf(fFOV / 2) / sinf(fFOV / 2);
	FLOAT Q = fFarPlane / (fFarPlane - fNearPlane);

	ZeroMemory(&mat, sizeof(D3DMATRIX));
	mat._11 = w;
	mat._22 = h;
	mat._33 = Q;
	mat._34 = 1.0f;
	mat._43 = -Q*fNearPlane;

	return S_OK;
}





int smEMatrixInvert(smEMATRIX &q, smEMATRIX &a)
{
	if(abs(a._44 - wfONE) > 1)
		return FALSE;
	if(abs(a._14) > 1 || abs(a._24) > 1 || abs(a._34) > 1)
		return FALSE;

	int fDetInv = (wfONE << wFLOATS) /
		((a._11 * ((a._22 * a._33 - a._23 * a._32) >> wFLOATS) -
		  a._12 * ((a._21 * a._33 - a._23 * a._31) >> wFLOATS) +
		  a._13 * ((a._21 * a._32 - a._22 * a._31) >> wFLOATS)) >> wFLOATS);


	q._11 = (fDetInv * ((a._22 * a._33 - a._23 * a._32) >> wFLOATS) >> wFLOATS);
	q._12 = -(fDetInv * ((a._12 * a._33 - a._13 * a._32) >> wFLOATS) >> wFLOATS);
	q._13 = (fDetInv * ((a._12 * a._23 - a._13 * a._22) >> wFLOATS) >> wFLOATS);
	q._14 = 0;

	q._21 = -(fDetInv * ((a._21 * a._33 - a._23 * a._31) >> wFLOATS) >> wFLOATS);
	q._22 = (fDetInv * ((a._11 * a._33 - a._13 * a._31) >> wFLOATS) >> wFLOATS);
	q._23 = -(fDetInv * ((a._11 * a._23 - a._13 * a._21) >> wFLOATS) >> wFLOATS);
	q._24 = 0;

	q._31 = (fDetInv * ((a._21 * a._32 - a._22 * a._31) >> wFLOATS) >> wFLOATS);
	q._32 = -(fDetInv * ((a._11 * a._32 - a._12 * a._31) >> wFLOATS) >> wFLOATS);
	q._33 = (fDetInv * ((a._11 * a._22 - a._12 * a._21) >> wFLOATS) >> wFLOATS);
	q._34 = 0;

	q._41 = -((a._41 * q._11 + a._42 * q._21 + a._43 * q._31) >> wFLOATS);
	q._42 = -((a._41 * q._12 + a._42 * q._22 + a._43 * q._32) >> wFLOATS);
	q._43 = -((a._41 * q._13 + a._42 * q._23 + a._43 * q._33) >> wFLOATS);
	q._44 = wfONE;

	return TRUE;
}

