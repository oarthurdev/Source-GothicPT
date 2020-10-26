#pragma once

#ifndef __CE_ISCLANMEMBER_HPP__
#define __CE_ISCLANMEMBER_HPP__

#include "clan_Enti.h"

class CLANEntity_IsClanMember : public CLANEntity
{
public:
	CLANEntity_IsClanMember();
	~CLANEntity_IsClanMember();

	int Init(int Life);
	int Clear();

	void Main();
	void RenderMain();


	void menuInit(int num);
public:

};


#endif 





#ifdef CE_ISCLANMEMBER_CPP

class CLANEntity_IsClanMember cIsClanMember;

#else

extern class CLANEntity_IsClanMember cIsClanMember;

#endif
