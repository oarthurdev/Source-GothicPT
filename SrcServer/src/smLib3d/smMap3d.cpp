#include "smd3d.h"

int DispPolyCnt;

int MidX = 640 / 2;
int MidY = 480 / 2;
int	viewdistZ = 640 / 2;
int ZDivision = 640 / 4;

int CameraX;
int CameraY;
int CameraZ;

int  CameraAngX;
int  CameraAngY;
int  CameraAngZ;


int	AddDepthZ = 0;


int	VRad_X[4] = { RAYCLIP_ANGLE , RAYCLIP_ANGLE , -RAYCLIP_ANGLE , -RAYCLIP_ANGLE };
int VRad_Y[4] = { RAYCLIP_ANGLE , -RAYCLIP_ANGLE , -RAYCLIP_ANGLE , RAYCLIP_ANGLE };
int	ViewRad_X[4];
int ViewRad_Y[4];
int ViewLength[4];

int ViewPosi_X[4];
int ViewPosi_Y[4];
int ViewLenFlag[4];
int ViewLenFlag2[4];
int ViewPointSort[4];

int		MapPosiLeft[256];
int		MapPosiRight[256];
int		MapPosiTop;
int		MapPosiBot;


POINT3D	pLight;



int ViewPointLen = 38 * SizeMAPCELL;
int ccDistZMin = ViewPointLen - (20 * SizeMAPCELL);


smRGB ccBackColor;
DWORD smBackColor = RGBA_MAKE(21, 17, 14, 255);

void smInitColorZClip(int r, int g, int b)
{
	ccBackColor.r = r;
	ccBackColor.g = g;
	ccBackColor.b = b;

	smBackColor = RGBA_MAKE(r, g, b, 255);
}

int DotProduct(POINT3D *p1, POINT3D *p2)
{
	return((int)((p1->x * p2->x) + (p1->y * p2->y) + (p1->z * p2->z)));
}

int tDotProduct(TPOINT3D *v0, TPOINT3D *v1, TPOINT3D *v2)
{

	int temp1, temp2, temp3;
	int tempX, tempY, tempZ;
	int tempA, tempB, tempC;

	tempX = v1->x - v0->x;
	tempY = v1->y - v0->y;
	tempZ = v1->z - v0->z;

	tempA = v2->x - v0->x;
	tempB = v2->y - v0->y;
	tempC = v2->z - v0->z;

	temp1 = ((tempY * tempC) - (tempZ * tempB)) >> 8;
	temp2 = ((tempZ * tempA) - (tempX * tempC)) >> 8;
	temp3 = ((tempX * tempB) - (tempY * tempA)) >> 8;

	return (temp1 * v1->x) + (temp2 * v1->y) + (temp3 * v1->z);
}


int SetNormal(POINT3D *p1, POINT3D *p2, POINT3D *p3, POINT3D *normal)
{
	float i, j, k, d;

	i = (float)(((p2->y - p1->y) * (p3->z - p1->z)) -
		((p2->z - p1->z) * (p3->y - p1->y)));

	j = (float)(((p2->z - p1->z) * (p3->x - p1->x)) -
		((p2->x - p1->x) * (p3->z - p1->z)));

	k = (float)(((p2->x - p1->x) * (p3->y - p1->y)) -
		((p2->y - p1->y) * (p3->x - p1->x)));


	d = (float)sqrt((double)((i * i) + (j * j) + (k * k)));
	i = (float)(i / d * 32767);
	j = (float)(j / d * 32767);
	k = (float)(k / d * 32767);

	normal->x = (int)i;
	normal->y = (int)j;
	normal->z = (int)k;

	return TRUE;
}


void SetViewLength()
{
	int i;
	for(i = 0; i < 4; i++)
		ViewLength[i] = ViewPointLen;
}


void SetViewRadian()
{
	int i;
	for(i = 0; i < 4; i++)
	{
		ViewRad_X[i] = GetRadian(CameraAngX + VRad_X[i]);
		ViewRad_Y[i] = GetRadian(CameraAngY + VRad_Y[i]);

		if(ViewRad_X[i] > ANGLE_180) ViewRad_X[i] = 0;

	}

	if(CameraAngX > ANGLE_180) CameraAngX = 0;
}


void GetMapPoint(int CpNum)
{

	int SideLen, MapLen, lenX, lenY;
	int tempX, tempY, tempH, tempT, tempX2;
	int sin_mX, cos_mX, sin_mY, cos_mY, cos_GX;
	int Vlen;

	sin_mX = zDSin(ViewRad_X[CpNum]);
	cos_mX = zDCos(ViewRad_X[CpNum]);
	sin_mY = zDSin(ViewRad_Y[CpNum]);
	cos_mY = zDCos(ViewRad_Y[CpNum]);

	Vlen = ViewLength[CpNum];

	ViewLenFlag2[CpNum] = 0;

	if(sin_mX != 0) SideLen = ((CameraY << 16) / sin_mX);
	else SideLen = -1;

	if(abs(SideLen) > Vlen || SideLen < 0)
	{

		tempY = (sin_mX * Vlen) >> 16;
		tempX = (cos_mX * Vlen) >> 16;
		tempH = CameraY - tempY;
		cos_GX = zDCos(CameraAngX);
		if(cos_GX == 0) tempT = 65536;
		else tempT = ((tempH << 16) / cos_GX);
		tempX2 = (zDSin(CameraAngX) * tempT) >> 16;
		MapLen = tempX - tempX2;

		ViewLenFlag[CpNum] = 0;
	}
	else
	{
		MapLen = (SideLen * cos_mX) >> 16;
		ViewLenFlag[CpNum] = 1;

		if(MapLen < 0) ViewLenFlag2[CpNum] = 1;
	}

	lenX = (sin_mY * MapLen) >> 16;
	lenY = (cos_mY * MapLen) >> 16;

	ViewPosi_Y[CpNum] = (CameraZ + lenY) >> ShiftMAPCELL_DIV;
	ViewPosi_X[CpNum] = (CameraX + lenX) >> ShiftMAPCELL_DIV;

}


int MakeMapTable()
{

	int i, j, j2;
	int k, l;
	int No0, No1, No2, Pri;
	int temp1, temp2;
	int temp3, temp4;

	int sindY, cosdY;

	int MinMSize = RAYCLIP_ADD;

	j = 0; j2 = 0;
	for(i = 0; i < 4; i++)
	{
		GetMapPoint(i);
		j += ViewLenFlag[i];
		j2 += ViewLenFlag2[i];
		ViewPointSort[i] = i;
	}

	if(j == 0) return NULL;

	if(j2 == 2)
	{
		if(ViewLenFlag2[0] == 1 && ViewLenFlag2[1] == 1)
		{
			temp3 = 0; temp4 = 1;
		}
		if(ViewLenFlag2[1] == 1 && ViewLenFlag2[2] == 1)
		{
			temp3 = 1; temp4 = 2;
		}
		if(ViewLenFlag2[2] == 1 && ViewLenFlag2[3] == 1)
		{
			temp3 = 2; temp4 = 3;
		}
		if(ViewLenFlag2[3] == 1 && ViewLenFlag2[0] == 1)
		{
			temp3 = 3; temp4 = 0;
		}

		temp1 = ViewPosi_X[temp3]; temp2 = ViewPosi_Y[temp3];
		ViewPosi_X[temp3] = ViewPosi_X[temp4]; ViewPosi_Y[temp3] = ViewPosi_Y[temp4];
		ViewPosi_X[temp4] = temp1; ViewPosi_Y[temp4] = temp2;
	}

	sindY = zDSin(CameraAngY);
	cosdY = zDCos(CameraAngY);

	if(CameraAngX < ANGLE_180)
	{
		for(i = 0; i < 4; i++)
		{
			if(i == 1 || i == 2)
			{

				if(CameraAngX >= (ANGLE_90 + VRad_X[0]))
				{
					ViewPosi_Y[i] -= ((MinMSize*sindY) >> 16);
					ViewPosi_X[i] += ((MinMSize*cosdY) >> 16);
				}
				else
				{
					ViewPosi_Y[i] += ((MinMSize*sindY) >> 16);
					ViewPosi_X[i] -= ((MinMSize*cosdY) >> 16);
				}

			}
			else
			{

				if(CameraAngX >= (ANGLE_90 + VRad_X[0]))
				{
					ViewPosi_Y[i] += ((MinMSize*sindY) >> 16);
					ViewPosi_X[i] -= ((MinMSize*cosdY) >> 16);
				}
				else
				{
					ViewPosi_Y[i] -= ((MinMSize*sindY) >> 16);
					ViewPosi_X[i] += ((MinMSize*cosdY) >> 16);
				}
			}
		}
	}

	else
	{
		for(i = 0; i < 4; i++)
		{
			if(i == 1 || i == 2)
			{
				if(CameraAngX >= (ANGLE_90 + VRad_X[0]))
				{
					ViewPosi_Y[i] += ((MinMSize*sindY) >> 16);
					ViewPosi_X[i] -= ((MinMSize*cosdY) >> 16);
				}
				else
				{
					ViewPosi_Y[i] -= ((MinMSize*sindY) >> 16);
					ViewPosi_X[i] += ((MinMSize*cosdY) >> 16);
				}
			}
			else
			{
				if(CameraAngX >= (ANGLE_90 + VRad_X[0]))
				{
					ViewPosi_Y[i] -= ((MinMSize*sindY) >> 16);
					ViewPosi_X[i] += ((MinMSize*cosdY) >> 16);
				}
				else
				{
					ViewPosi_Y[i] += ((MinMSize*sindY) >> 16);
					ViewPosi_X[i] -= ((MinMSize*cosdY) >> 16);
				}
			}
		}

	}



	sindY = zDSin(GetRadian(CameraAngY + ANGLE_90));
	cosdY = zDCos(GetRadian(CameraAngY + ANGLE_90));
	for(i = 0; i < 4; i++)
	{
		if(i == 0 || i == 1)
		{
			ViewPosi_Y[i] -= ((MinMSize*sindY) >> 16);
			ViewPosi_X[i] += ((MinMSize*cosdY) >> 16);
		}
		else
		{
			ViewPosi_Y[i] += ((MinMSize*sindY) >> 16);
			ViewPosi_X[i] -= ((MinMSize*cosdY) >> 16);
		}
	}




	for(i = 0; i < 3; i++)
		for(j = i + 1; j < 4; j++)
		{
			k = ViewPointSort[i];
			l = ViewPointSort[j];

			if(ViewPosi_Y[k] > ViewPosi_Y[l])
			{
				ViewPointSort[i] = l;
				ViewPointSort[j] = k;
			}
		}

	MapPosiTop = ViewPosi_Y[ViewPointSort[0]];
	MapPosiBot = ViewPosi_Y[ViewPointSort[3]];

	No0 = ViewPointSort[0];
	No1 = (No0 + 1) & 3;
	No2 = (No0 - 1) & 3;

	if(ViewPosi_X[No1] < ViewPosi_X[No2])
	{
		Pri = 1;
	}
	else
	{
		Pri = -1;
	}

	No0 = ViewPointSort[0];
	No1 = (No0 + Pri) & 3;

	while(1)
	{

		l = (ViewPosi_Y[No1] - ViewPosi_Y[No0]);
		if(l == 0) k = 0;
		else k = (((ViewPosi_X[No1] - ViewPosi_X[No0]) << 16) / l);
		l = ViewPosi_X[No0] << 16;

		for(i = ViewPosi_Y[No0]; i < ViewPosi_Y[No1]; i++)
		{
			MapPosiLeft[(i & 0xFF)] = l >> 16;
			l += k;
		}
		No0 = No1;
		No1 = (No0 + Pri) & 3;
		if(No0 == ViewPointSort[3]) break;
	}


	No0 = ViewPointSort[0];
	No1 = (No0 - Pri) & 3;

	while(1)
	{
		l = (ViewPosi_Y[No1] - ViewPosi_Y[No0]);
		if(l == 0) k = 0;
		else k = (((ViewPosi_X[No1] - ViewPosi_X[No0]) << 16) / l);
		l = ViewPosi_X[No0] << 16;

		for(i = ViewPosi_Y[No0]; i < ViewPosi_Y[No1]; i++)
		{
			MapPosiRight[(i & 0xFF)] = l >> 16;
			l += k;
		}
		No0 = No1;
		No1 = (No0 - Pri) & 3;
		if(No0 == ViewPointSort[3]) break;
	}

	return 1;
}


float smConvZ3D(float z)
{
	float rz;

	rz = (z + (float)AddDepthZ) / 4096.f;

	if(rz < 0) rz = 0;
	if(rz > 1) rz = 1;

	return rz;
}


int GetRadian(int Rad)
{
	return (Rad & ANGCLIP);
}

