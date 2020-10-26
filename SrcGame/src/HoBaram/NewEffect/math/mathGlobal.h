

#ifndef _MATHGLOBAL_H
#define _MATHGLOBAL_H

#ifndef EPSILON
#define EPSILON 0.001f
#endif

#ifndef PI
#define PI 3.1415926f
#endif

#ifndef SIGN_BIT
#define SIGN_BIT 0x80000000
#endif

#ifndef INV_SIGN_BIT
#define INV_SIGN_BIT 0x7FFFFFFF
#endif

#include <stdlib.h>


inline float FastFabs( const float &in )
{
	int* temp = (int*)&in;
	int out = *temp & INV_SIGN_BIT;
	return *((float*)&out);
}


inline float FRand()
{
	return (float)(rand()-RAND_MAX/2) / (RAND_MAX/2);
}

#endif 
