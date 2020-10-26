







#ifndef _HO_EFFECT_UTIL_H_
#define _HO_EFFECT_UTIL_H_
#include "math\\mathGlobal.h"
#include "math\\point3.h"
#include "math\\color4.h"

float RandomNumber(float fMin, float fMax);
int RandomNumber(int iMin, int iMax);

point3 RandomNumber(point3 vMin, point3 vMax);
color4 RandomNumber(color4 Min, color4 Max);


template <class T> class HoEffectMinMax
{
	public:
		HoEffectMinMax()
		{
			Min = T(); Max = T();
		}

		HoEffectMinMax(T tMin, T tMax)
		{
			Min = tMin; Max = tMax;
		}

		~HoEffectMinMax()
		{
		}

		T Min;
		T Max;

		T GetRandom(void)
		{
			return(RandomNumber(Min, Max));
		}

		T GetRange(void)
		{
			return(abs(Max-Min));
		}
};

#endif
 
