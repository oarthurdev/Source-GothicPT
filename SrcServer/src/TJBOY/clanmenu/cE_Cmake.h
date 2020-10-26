#pragma once

#ifndef __CE_NOUSER_HPP__
#define __CE_NOUSER_HPP__

#include "clan_Enti.h"

class CLANEntity_make : public CLANEntity
{
public:
	CLANEntity_make();
	~CLANEntity_make();

	int Init(int Life);
	int Clear();

	void Main();
	void RenderMain();
	void Draw();


	void menuInit(int num);
public:
	char szClanMakeMsg[256];;

	bool m_bEventClanMoney;


};


#endif 


#ifdef CE_CMAKE_CPP

class CLANEntity_make cClanMake;

#else

extern class CLANEntity_make cClanMake;

#endif
