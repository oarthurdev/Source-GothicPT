#define TJSCROLL_CPP

#include "tjScroll.h"

void fd2(char *fmt, ...);





extern int TJwheel;



int TJBscrollWheel(int wheel)
{
	void fd2(char *fmt, ...);



	if(wheel != 0)
	{
		if(tscr.lifef || tscr_CL.lifef || tscr_Guide.lifef)
		{
			TJwheel = wheel;




			return 1;
		}
	}


	return 0;
}

void TJBscrollWheelClear()
{
	TJwheel = 0;
	tscr.lifef = 0;

}

void TJBscrollWheelClear_ChatL()
{
	TJwheel = 0;
	tscr_CL.lifef = 0;
	void chatList_Main_CHATLIST_END();
	chatList_Main_CHATLIST_END();
}

void TJBscrollWheelClear_Guide()
{
	TJwheel = 0;
	tscr_Guide.lifef = 0;
}

tSCROLL::tSCROLL()
{
}

tSCROLL::~tSCROLL()
{
}


void tSCROLL::Init(int flag)
{
	lifef = flag;
}



void tSCROLL::Init(int t, int b, int scrLineSu, int ViewLineSu)
{
	top = t;
	bot = b;
	allLineSu = scrLineSu;
	viewLineSu = ViewLineSu;

	int scrLen = bot - top;
	step = scrLen / (scrLineSu + 1);

	lifef = 1;
}

int tSCROLL::topScrollLineNum(int point)
{
	if(lifef == 0) return -1;

	int curP = point - top;
	int currentScrllLineNum = curP / step;
	if(currentScrllLineNum > allLineSu)
		currentScrllLineNum = allLineSu;



	int i = currentScrllLineNum + viewLineSu;
	if(i > allLineSu)
	{
		currentScrllLineNum = allLineSu - viewLineSu;
	}

	return currentScrllLineNum;
}



int tSCROLL::ret_WHEELpoint(int wheelN, int point)
{
	if(lifef == 0) return point;

	if(wheelN < 0)
	{
		point += step;
		if((bot - 9) < point)
			point = bot - 9;
	}

	if(wheelN > 0)
	{
		point -= step;

		if(top > point)
			point = top;
	}

	return point;
}








