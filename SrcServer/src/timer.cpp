#define TIMER_CPP
#include <windows.h>

#include "timer.h"

DWORD rateNum;
DWORD frameTime = 0;


void InitFrameTime(DWORD ft)
{
	frameTime = ft;
}

void TimeClear(void)
{
	rateNum = timeGetTime();
}

DWORD GetSkipFrame(void)
{
	DWORD gt;
	while(1)
	{
		gt = timeGetTime() - rateNum;
		if(gt >= frameTime) break;
	}
	return (gt / frameTime);
}

