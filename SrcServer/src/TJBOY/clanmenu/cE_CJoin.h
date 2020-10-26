#pragma once

#ifndef __CE_CJOIN_HPP__
#define __CE_CJOIN_HPP__


#include "clan_Enti.h"

#define CLANWONLEVEL_TABLE 100

class CLANEntity_JOIN : public CLANEntity
{
public:
	CLANEntity_JOIN();
	~CLANEntity_JOIN();

	int Init(int Life);
	int Clear();

	void Main();
	void Draw();
	void menuInit(int num);
	void AddClanWon();

	void SetLevelTable();
	BOOL CheckClanWon(int level);


	int GetMaxClanWonCount(int level);


public:
	int nJoinAnswer;
	char szUserJoin[256];
	char szTemp[1024];
	char szTemp1[1024];


};

#endif 


#ifdef CE_CJOIN_CPP

class CLANEntity_JOIN cClanJoin;

#else

extern class CLANEntity_JOIN cClanJoin;

#endif
