#include "HoEffectUtil.h"

#include "HoNewEffectHeader.h"
#ifndef _HO_NEW_WIN32_
float RandomNumber(float fMin, float fMax)
{
    
    if (fMin == fMax) return(fMin);
    float fRandom = (float)rand() / (float)RAND_MAX;
    return((fRandom * (float)fabs(fMax-fMin))+fMin);
}


int RandomNumber(int iMin, int iMax)
{
    
    if (iMin == iMax) return(iMin);
    return((rand() % (abs(iMax-iMin)+1))+iMin);
}
#endif 

point3 RandomNumber(point3 vMin, point3 vMax)
{
  float x = RandomNumber(vMin.x, vMax.x);
  float y = RandomNumber(vMin.y, vMax.y);
  float z = RandomNumber(vMin.z, vMax.z);

  point3 temp;
  temp.x = x;
  temp.y = y;
  temp.z = z;

  return(temp);
}

color4 RandomNumber(color4 Min, color4 Max)
{
  float r = RandomNumber(Min.r, Max.r);
  float g = RandomNumber(Min.g, Max.g);
  float b = RandomNumber(Min.b, Max.b);
  float a = RandomNumber(Min.a, Max.a);

  color4 temp;
  temp.r = r;
  temp.g = g;
  temp.b = b;
  temp.a = a;
  return(temp);
}
