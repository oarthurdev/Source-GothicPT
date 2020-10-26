#pragma once

#ifndef __CE_NOUSER_HPP__
#define __CE_NOUSER_HPP__

#include "clan_Enti.h"

class CLANEntity_nouser : public CLANEntity
{
public:
	CLANEntity_nouser();
	~CLANEntity_nouser();

	int Init(int Life);
	int Clear();

	void Main();
	void RenderMain();


	void menuInit(int num);
public:
	RECT menuPos[30];
	int menuSu;
	POINT BackStartPos;
};


#endif 




#ifdef CE_NOUSER_CPP
class CLANEntity_nouser cClanMake;

#else
extern class CLANEntity_nouser cClanMake;

#endif
