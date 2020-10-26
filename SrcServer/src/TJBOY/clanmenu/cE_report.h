#pragma once

#ifndef __CE_REPORT_HPP__
#define __CE_REPORT_HPP__

#include "clan_Enti.h"

#define REPORT_MAX 512
class CLANEntity_report : public CLANEntity
{
public:
	CLANEntity_report();
	~CLANEntity_report();

	int Init(int Life);
	int Clear();

	void Main();
	void RenderMain();
	void Draw();
	void InitMsg(char *msg);


	void menuInit(int num, LONG x, LONG y);
public:



	char szReport[REPORT_MAX];

};


#endif 





#ifdef CE_REPORT_CPP

class CLANEntity_report cClanReport;



#else

extern class CLANEntity_report cClanReport;



#endif
