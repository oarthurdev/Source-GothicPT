
#include <windows.h>

#include <math.h>
#include "smSin.h"

int sinus[(ANGLE_360 + 1)];
int cosinus[(ANGLE_360 + 1)];
int *GetSin = sinus;
int *GetCos = cosinus;


int wSinus[(ANGLE_360 + 1)];
int wCosinus[(ANGLE_360 + 1)];

int *sdGetSin = wSinus;
int *sdGetCos = wCosinus;

double dbSinus[(ANGLE_360 + 1)];
double dbCosinus[(ANGLE_360 + 1)];
double *dbGetSin = dbSinus;
double *dbGetCos = dbCosinus;

int zDSin(int deg)
{
	return(sinus[deg & ANGLE_MASK]);
}

int zRSin(double rad)
{
	return(zDSin((int)(rad * ANGLE_180 / PI)));
}

int zDCos(int deg)
{
	return(cosinus[deg & ANGLE_MASK]);
}

int zRCos(double rad)
{
	return(zDCos((int)(rad * ANGLE_180 / PI)));
}


void initSinCos()
{
	int count;
	float ang;

	for(count = 0; count <= ANGLE_360; count++)
	{

		ang = ((float)count) * PI / (float)ANGLE_180;

		sinus[count] = (int)(sin(ang) * 65536);
		cosinus[count] = (int)(cos(ang) * 65536);

		wSinus[count] = (int)(sin(ang) * 32768);
		wCosinus[count] = (int)(cos(ang) * 32768);

		dbSinus[count] = sin(ang);
		dbCosinus[count] = cos(ang);

	}

}

