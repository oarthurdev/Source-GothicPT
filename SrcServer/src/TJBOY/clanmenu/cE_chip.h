#pragma once

#ifndef __CE_CHIP_HPP__
#define __CE_CHIP_HPP__

#include "clan_Enti.h"

#define HELPCONTENT_TXT "image\\clanImage\\Help\\Help.msg"

class CLANEntity_chip : public CLANEntity
{
public:
	CLANEntity_chip();
	~CLANEntity_chip();

	int Init(int Life);
	int Clear();

	void Main();
	void RenderMain();
	void Draw();


	void menuInit(int num);
	int chkMark(char *clanName);
	BOOL CheckMark(char* filename);
	BOOL SearchMarkClient(char *clanName);
	BOOL SearchMarkServer(char *clanName);


public:

	int Money;
	int	nClanWon[40];
	int  nReleaseClanWon;
	BOOL bSubChip;




	int nScl_Bar;
	RECT scrIconPos;
	int nMark;

	int  nChkMark;
	char szRemoveClanWon[500];

	char     szRemoveClanWonResultMsg[1024];
	char     szReconfReleaseMsg[2048];
	int      nRemoveRight;
	BOOL     bClan6Down;
	BOOL     bPFlag;
	BOOL		bRelease;
	char szDrawMenuMsg[2024];
	char szTemp[1024];
	BOOL bRemoveSecondCheck;
	BOOL bisSubChip;
	int nSavePos;

};


#endif 


#ifdef CE_CHIP_CPP

class CLANEntity_chip cClanChip;

#else

extern class CLANEntity_chip cClanChip;

#endif
