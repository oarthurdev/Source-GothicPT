



#pragma once

#ifndef __CE_DELETECHA_HPP__
#define __CE_DELETECHA_HPP__

#include "clan_Enti.h"



#define CLAN_DELETECHA_START					800  
#define CLAN_DELETECHA_RELEASECLAN_BEFORE        801  
#define CLAN_DELETECHA_RELEASECLAN              802
#define CLAN_DELETECHA_SECESSION_BEFORE			803  
#define CLAN_DELETECHA_SECESSION				804
#define CLAN_DIRECT_DELETE					805



class CLANEntity_deletecha : public CLANEntity
{
public:
	CLANEntity_deletecha();
	~CLANEntity_deletecha();

	int Init(int Life);
	int Clear();

	void Main();
	void Draw();
	void menuInit(int num);
	void SetDeleteChaInfo(char *id, char *gserver, char *chaname);

	BOOL bFlag;
public:
	inline int GetHowDeleteChaFlag()
	{
		return nHowDeleteChaFlag;
	}
	inline void SetHowDeleteChaFlag()
	{
		nHowDeleteChaFlag = 0;
	}
public:
	int nHowDeleteChaFlag;



};


#endif 



#ifdef CE_DELETECHA_CPP

class CLANEntity_deletecha cClanDeleteCha;



#else

extern class CLANEntity_deletecha cClanDeleteCha;



#endif
