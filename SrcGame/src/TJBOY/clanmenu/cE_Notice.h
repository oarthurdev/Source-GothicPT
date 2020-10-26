#pragma once

#ifndef __CE_NOTICE_HPP__
#define __CE_NOTICE_HPP__

#include "clan_Enti.h"

#define NOTICE_X	208
#define NOTICE_Y	61

#define NOTICECOUNT    5
#define NOTICE_WIDTH_COUNT 60
#define NOTICE_MAX  64
#define NOTICE_HEIGHT 52
#define HEIGHT_MAX 14

#define NOTICE_SCROLLBAR_LEFT  500


class CLANEntity_Notice : public CLANEntity
{
public:


	CLANEntity_Notice();
	~CLANEntity_Notice();

	int Init(int Life);
	int Clear();

	void Main();
	void Draw();
	void menuInit(int num);
	void NoticeCheck(char* buf);




	char szNotice[NOTICECOUNT][NOTICE_HEIGHT][NOTICE_MAX];

	RECT scrIconPos;
	int nScl_Bar;


public:
};


#endif 





#ifdef CE_NOTICE_CPP

class CLANEntity_Notice cClanNotice;

#else

extern class CLANEntity_Notice cClanNotice;

#endif
