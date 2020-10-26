
#include "HoLinkHeader.h"
#include "HoMinMax.h"

float RandomNumber(float fMin, float fMax)
{
	if(fMin == fMax) return(fMin);
	float fRandom = (float)rand() / (float)RAND_MAX;
	return((fRandom * (float)fabs(fMax - fMin)) + fMin);
}


int RandomNumber(int iMin, int iMax)
{
	if(iMin == iMax) return(iMin);
	return((rand() % (abs(iMax - iMin) + 1)) + iMin);
}



D3DXVECTOR3 RandomNumber(D3DXVECTOR3 vMin, D3DXVECTOR3 vMax)
{
	float x = RandomNumber(vMin.x, vMax.x);
	float y = RandomNumber(vMin.y, vMax.y);
	float z = RandomNumber(vMin.z, vMax.z);

	D3DXVECTOR3 temp;
	temp.x = x;
	temp.y = y;
	temp.z = z;

	return(temp);
}

D3DCOLORVALUE RandomNumber(D3DCOLORVALUE Min, D3DCOLORVALUE Max)
{
	float r = RandomNumber(Min.r, Max.r);
	float g = RandomNumber(Min.g, Max.g);
	float b = RandomNumber(Min.b, Max.b);
	float a = RandomNumber(Min.a, Max.a);

	D3DCOLORVALUE temp;
	temp.r = r;
	temp.g = g;
	temp.b = b;
	temp.a = a;
	return(temp);
}
