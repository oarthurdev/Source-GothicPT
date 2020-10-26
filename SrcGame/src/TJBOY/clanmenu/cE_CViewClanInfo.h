#pragma once

#include "tjclanDEF.h"

#ifndef __CLAN_VIEWCLANINFO_HPP__
#define __CLAN_VIEWCLANINFO_HPP__



#define CLAN_MAX		500

#define CLANINFO_DIR	"savedata\\clanDATA"  
typedef struct _tagClanInfoHeader
{
	char		ClanMark_Num[40];
	DWORD		nClanMark;
	char		ClanName[40];
	char		ClanReport[90];
	char		Gserver[4];
	char		UniqueClaClanInfo_nNum[64];

}CLANINFOHEADER;

typedef struct _tagClanInfo
{
	CLANINFOHEADER ClanInfoHeader;

#ifdef USE_PROSTONTALE		
	LPDIRECT3DTEXTURE9    hClanMark;
	LPDIRECT3DTEXTURE9    hClanMark32;
#else
	HBITMAP					hClanMark;
#endif
	DWORD	dwTime;
	int		nStatus;
	int		nSaveNum;

}CLANINFO;



class CViewClanInfo
{
public:
	CViewClanInfo();
	~CViewClanInfo();
public:
	int Init(int Life);
	int Clear();


	void Main();
	char* AddClanInfo(char *marknum, char *szInfo, CLANINFO* ci);
	int DownLoadClanInfo(int num, DWORD dwClanNum);
	int chk_readStrBuf(char *cmd, char *readbuf, char *retBuf);
	void SortDelete();
	void LoadData();
	BOOL SearchDirectory();
	void ReadToFile(char *file, int count);
	void ReadToImage(char *file, int count);
	void MakeDirectory();
	BOOL CheckWhere(char *MarkNum);
	inline BOOL GetFlag()
	{
		return bFlag;
	}
	void ParsingData(char* cmd, char* data, char* save);
	int readFILE_ClanInfo(DWORD clanNum);


private:

	BOOL bFlag;



	int		nClanInfo_Menu;
	int		nClanInfo_Menu2;
	char	szClanMarkNum[64];
	int		nLowTime;




public:

	int SearchClan(DWORD dwClanNum);

	int Search_Memory(char *clanNum);

	int Search_Files(char *clanNum);


};
#endif









#ifdef CLAN_VIEWCLANINFO_CPP


class CViewClanInfo g_ViewClanInfo;
CLANINFO ClanInfo[CLAN_MAX];
int	ClanInfo_nNum;
int		nDoCheck = 0;
int	nCheckDownLoad = -1;



#else



extern int	nCheckDownLoad;
extern int		nDoCheck;

extern class CViewClanInfo g_ViewClanInfo;
extern CLANINFO ClanInfo[CLAN_MAX];
extern int ClanInfo_nNum;


#endif
