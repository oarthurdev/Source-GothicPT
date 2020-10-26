#define CLAN_VIEWCLANINFO_CPP
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <math.h>

#include "tjclanDEF.h"

#ifdef USE_PROSTONTALE		

#include "sinbaram\\SinLinkHeader.h"
#include "HoBaram\\HoLinkHeader.h"
#include "Language\\language.h"
#include "HoBaram\\HoTextFile.h"

#endif

#include "tjclan.h"
#include "cE_report.h"
#include "cE_CJoin.h"
#include "cE_CViewClanInfo.h"


#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"

extern char szConnServerName[16];



CViewClanInfo::CViewClanInfo()
{
	bFlag = FALSE;
	ClanInfo_nNum = -1;


	ZeroMemory(ClanInfo, sizeof(CLANINFO)*CLAN_MAX);
	ZeroMemory(szClanMarkNum, sizeof(szClanMarkNum));






}

CViewClanInfo::~CViewClanInfo()
{
	int i;
	for(i = 0; i < CLAN_MAX; i++)
	{
	#ifdef USE_PROSTONTALE
		if(ClanInfo[i].hClanMark)
		{
			ClanInfo[i].hClanMark->Release();
			ClanInfo[i].hClanMark = NULL;
		}

		if(ClanInfo[i].hClanMark32)
		{
			ClanInfo[i].hClanMark32->Release();
			ClanInfo[i].hClanMark32 = NULL;
		}
	#else
		DeleteObject(ClanInfo[i].hClanMark);
	#endif
	}


}


int CViewClanInfo::readFILE_ClanInfo(DWORD clanNum)
{
	char GServer[4];
	char ClanUnique[64];
	char szClanNum[64];
	char szTemp[256];
	int nClanMarklen = 0;

	CLANINFO *pCL = &ClanInfo[0];
	int nCount = 0;
	ZeroMemory(szClanNum, sizeof(szClanNum));
	ZeroMemory(GServer, sizeof(GServer));
	ZeroMemory(ClanUnique, sizeof(ClanUnique));

	for(int i = 0; i < CLAN_MAX; i++, pCL++)
	{
		if((pCL->nStatus == 0) || pCL->nStatus == 3)
		{
			nCount = i;

			break;
		}
	}


	wsprintf(szClanNum, "%u", clanNum);

	nClanMarklen = lstrlen(szClanNum);

	if(nClanMarklen == 9)
	{
		GServer[0] = szClanNum[0];

		strcpy(ClanUnique, &szClanNum[3]);
	}
	else
	{
		GServer[0] = szClanNum[0];
		GServer[1] = szClanNum[1];
		strcpy(ClanUnique, &szClanNum[4]);
	}





#ifdef  USE_PROSTONTALE	
	ClanInfo[nCount].dwTime = GetCurrentTime();
	wsprintf(szTemp, "%s\\%s\\%s_%s.rep", CLANINFO_DIR, szConnServerName, GServer, ClanUnique);



	HANDLE hFile;
	DWORD dwRead;
	hFile = CreateFile(szTemp, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
					   NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile != INVALID_HANDLE_VALUE)
	{

		ReadFile(hFile, &ClanInfo[nCount].ClanInfoHeader, sizeof(CLANINFOHEADER), &dwRead, NULL);
		CloseHandle(hFile);
	}


	wsprintf(szTemp, "%s\\%s\\%s_%s.%s", CLANINFO_DIR, szConnServerName, GServer, ClanUnique, SAVE_EXE);

	if(ClanInfo[nCount].hClanMark != NULL)
	{
		ClanInfo[nCount].hClanMark32->Release();
		ClanInfo[nCount].hClanMark32 = NULL;
	}

	if(ClanInfo[nCount].hClanMark32 != NULL)
	{
		ClanInfo[nCount].hClanMark32->Release();
		ClanInfo[nCount].hClanMark32 = NULL;
	}

	ClanInfo[nCount].hClanMark = LoadDibSurfaceOffscreen(szTemp);
	if(ClanInfo[nCount].hClanMark != NULL)
	{
		ClanInfo[nCount].nStatus = 2;
		return nCount;
	}
	else return 0;
#else
	ClanInfo[nCount].dwTime = GetCurrentTime();
	wsprintf(szTemp, "%s\\%s\\%s_%s.rep", CLANINFO_DIR, szConnServerName, GServer, ClanUnique);
	FILE *fp;
	fp = fopen(szTemp, "rb");
	fread(&ClanInfo[nCount].ClanInfoHeader, sizeof(CLANINFOHEADER), 1, fp);
	fclose(fp);
	wsprintf(szTemp, "%s\\%s\\%s_%s.%s", CLANINFO_DIR, szConnServerName, GServer, ClanUnique, SAVE_EXE);
	ClanInfo[nCount].hClanMark = (HBITMAP)LoadImage(NULL, szTemp,
													IMAGE_BITMAP,
													0, 0, LR_LOADFROMFILE);
	if(ClanInfo[nCount].hClanMark != NULL)
	{
		ClanInfo[nCount].nStatus = 2;
		return nCount;
	}
	else return 0;



#endif

#ifdef CLAN_DEBUG
	DebugMessage("CViewClanInfo::readFILE_ClanInfo(클랜번호 : %d)", clanNum);
#endif



	return nCount;
}

int CViewClanInfo::Search_Memory(char *clanNum)
{
	CLANINFO *pCL = &ClanInfo[0];

	struct clanMarkNUMS
	{
		char gn[2];
		char cnt[2];
		char cNum[6];
		char notuse;
	};
	union Uni_cl
	{
		char buf[100];
		clanMarkNUMS cl;
	};
	Uni_cl uni_cl;


	int l = strlen(clanNum);


	char buf[10];
	int nstr = lstrlen(clanNum);
	if(l >= 10)
	{
		uni_cl.cl.gn[0] = clanNum[0];
		uni_cl.cl.gn[1] = clanNum[1];
		uni_cl.cl.cnt[0] = clanNum[2];
		uni_cl.cl.cnt[1] = clanNum[3];
		strcpy(uni_cl.cl.cNum, &clanNum[4]);
	}
	else
	{
		uni_cl.cl.gn[0] = clanNum[0];
		uni_cl.cl.cnt[0] = clanNum[1];
		uni_cl.cl.cnt[1] = clanNum[2];
		strcpy(uni_cl.cl.cNum, &clanNum[3]);
	}
	if(l >= 10)
	{
		buf[0] = uni_cl.cl.gn[0];
		buf[1] = uni_cl.cl.gn[1];
	}
	else
	{
		buf[0] = uni_cl.cl.gn[0];
		buf[1] = 0;
	}
	int  gn = atoi(buf);
	buf[0] = uni_cl.cl.cnt[0];
	buf[1] = uni_cl.cl.cnt[1];
	buf[2] = 0;
	int  cnt = atoi(buf);
	int  int_Cmark = atoi(uni_cl.cl.cNum);



	for(int i = 0; i < CLAN_MAX; i++, pCL++)
	{
		if(pCL->nStatus == 0) continue;

		int l2 = strlen(pCL->ClanInfoHeader.ClanMark_Num);

		if(l == l2 &&  strcmp(pCL->ClanInfoHeader.ClanMark_Num, clanNum) == 0)
		{
			pCL->dwTime = GetCurrentTime();
			return (0x8000 | i);
		}


		l = lstrlen(pCL->ClanInfoHeader.ClanMark_Num);
		if(l >= 10)
		{
			uni_cl.cl.gn[0] = pCL->ClanInfoHeader.ClanMark_Num[0];
			uni_cl.cl.gn[1] = pCL->ClanInfoHeader.ClanMark_Num[1];
			uni_cl.cl.cnt[0] = pCL->ClanInfoHeader.ClanMark_Num[2];
			uni_cl.cl.cnt[1] = pCL->ClanInfoHeader.ClanMark_Num[3];
			strcpy(uni_cl.cl.cNum, &pCL->ClanInfoHeader.ClanMark_Num[4]);
		}
		else
		{
			uni_cl.cl.gn[0] = pCL->ClanInfoHeader.ClanMark_Num[0];
			uni_cl.cl.cnt[0] = pCL->ClanInfoHeader.ClanMark_Num[1];
			uni_cl.cl.cnt[1] = pCL->ClanInfoHeader.ClanMark_Num[2];
			strcpy(uni_cl.cl.cNum, &pCL->ClanInfoHeader.ClanMark_Num[3]);
		}

		if(l >= 10)
		{
			buf[0] = uni_cl.cl.gn[0];
			buf[1] = uni_cl.cl.gn[1];
		}
		else
		{
			buf[0] = uni_cl.cl.gn[0];
			buf[1] = 0;
		}

		int  gn2 = atoi(buf);
		buf[0] = uni_cl.cl.cnt[0];
		buf[1] = uni_cl.cl.cnt[1];
		buf[2] = 0;
		int  cnt2 = atoi(buf);
		int  int_Cmark2 = atoi(uni_cl.cl.cNum);

		if(l == l2 &&  int_Cmark == int_Cmark2)
		{
			pCL->dwTime = GetCurrentTime();
			return (0xC000 | i);

		}
	}

	return 0;
}




int CViewClanInfo::Search_Files(char *clanNum)
{
	char GServer[4];
	char szClanNum[64];
	char szTemp[256];
	int nClanNum;
	int nClanNum1;
	int nClanMarklen = 0;
	CLANINFOHEADER claninfoheader;

	CLANINFO *pCL = &ClanInfo[0];

	nClanNum = atoi(clanNum);







	nClanMarklen = lstrlen(clanNum);
	ZeroMemory(GServer, sizeof(GServer));
	ZeroMemory(szClanNum, sizeof(szClanNum));

	if(nClanMarklen == 9)
	{
		GServer[0] = clanNum[0];
		strcpy(szClanNum, &clanNum[3]);
	}
	else
	{
		GServer[0] = clanNum[0];
		GServer[1] = clanNum[1];
		strcpy(szClanNum, &clanNum[4]);
	}




	wsprintf(szTemp, "%s\\%s\\%s_%s.rep", CLANINFO_DIR, szConnServerName, GServer, szClanNum);





	HANDLE hFile;
	DWORD dwRead;
	hFile = CreateFile(szTemp, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
					   NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile != INVALID_HANDLE_VALUE)
	{
		ReadFile(hFile, &claninfoheader, sizeof(CLANINFOHEADER), &dwRead, NULL);
		CloseHandle(hFile);


		nClanNum1 = atoi(claninfoheader.ClanMark_Num);
		if(nClanNum != nClanNum1)
		{
			return 0;
		}
		else
		{
		#ifdef  USE_PROSTONTALE
			wsprintf(szTemp, "%s\\%s\\%s_%s.%s", CLANINFO_DIR, szConnServerName, GServer, szClanNum, SAVE_EXE);
			LPDIRECT3DTEXTURE9 ld = NULL;
			ld = LoadDibSurfaceOffscreen(szTemp);
			if(ld != NULL)
			{

				ld->Release();
				ld = NULL;

				return 1;
			}
			else return 0;
		#else
			wsprintf(szTemp, "%s\\%s\\%s_%s_16.%s", CLANINFO_DIR, szConnServerName, GServer, szClanNum, SAVE_EXE);
			HBITMAP ld = NULL;
			ld = (HBITMAP)LoadImage(NULL, szTemp,
									IMAGE_BITMAP,
									0, 0, LR_LOADFROMFILE);

			if(ld != NULL)
			{



				DeleteObject(ld);

				ld = NULL;

				return 1;
			}
			else return 0;
		#endif

		}
	}

	return 0;
}


int CViewClanInfo::SearchClan(DWORD dwClanNum)
{

	char ClanMarkNum[100];

	char GServer[3];
	char szNum[64];
	int i;
	ZeroMemory(ClanMarkNum, sizeof(char) * 100);


	sprintf(ClanMarkNum, "%u", dwClanNum);
	if(ClanMarkNum == NULL) return 0;
	int nStr = lstrlen(ClanMarkNum);
	if(nStr >= 10)
	{
		GServer[0] = ClanMarkNum[0];
		GServer[1] = ClanMarkNum[1];
		strcpy(szNum, &ClanMarkNum[4]);
	}
	else
	{


		GServer[0] = ClanMarkNum[0];
		strcpy(szNum, &ClanMarkNum[3]);
	}





	ClanInfo_nNum = -1;
	bFlag = FALSE;






	i = Search_Memory(ClanMarkNum);
	if(i != 0)
	{
		int chk = (i >> 8);
		if(chk == 0x80)
		{
			ClanInfo_nNum = (i & 0x0fff);
			return 1;
		}
		if(chk == 0xC0)
		{
			int infoN = i & 0x0fff;
			DownLoadClanInfo(infoN, dwClanNum);
			ClanInfo_nNum = infoN;
			return 1;
		}
	}


	i = Search_Files(ClanMarkNum);
	if(i == 1)
	{



		ClanInfo_nNum = readFILE_ClanInfo(dwClanNum);

		return 1;
	}
	else
	{
		ClanInfo_nNum = DownLoadClanInfo(-1, dwClanNum);
		return 1;

	}


	ClanInfo_nNum = DownLoadClanInfo(-1, dwClanNum);
	return 0;

	return 0;
}




int downClanSu = 0;
void is_allDown()
{
	if(OpenFlag == 0 && downClanSu == 0)
	{
		WebDB.Suspend();
	}
}


void debug_fd2(char *fmt, ...);





int clanINFO_result2(int ret_code, char *marknum, CLANINFO *ci)
{
#ifdef CLAN_DEBUG
	DebugMessage("clanINFO_result2에서 클랜마크 읽어옴(클랜번호 : %s)", marknum);
#endif
	char szTemp[256];
	wsprintf(szTemp, "%s\\%s\\%s_%s.%s", CLANINFO_DIR, szConnServerName, ci->ClanInfoHeader.Gserver,
			 ci->ClanInfoHeader.UniqueClaClanInfo_nNum, SAVE_EXE);

#ifdef  USE_PROSTONTALE
	if(ci->hClanMark != NULL)
	{
		ci->hClanMark32->Release();
		ci->hClanMark32 = NULL;
	}
	ci->hClanMark = LoadDibSurfaceOffscreen(szTemp);
#else
#endif




	return 0;

}


int clanINFO_Load32X32(int clinfo_n)
{
#ifdef CLAN_DEBUG
	DebugMessage("clanINFO_Load32X32에서32x32 클랜마크 읽어옴(클랜 인포 번호 : %d)", clinfo_n);
#endif

	CLANINFO *ci = &ClanInfo[clinfo_n];

	char szTemp[256];
	wsprintf(szTemp, "%s\\%s\\%s_%s.%s", CLANINFO_DIR, szConnServerName, ci->ClanInfoHeader.Gserver,
			 ci->ClanInfoHeader.UniqueClaClanInfo_nNum, SAVE_EXE);

	if(ci->hClanMark32 != NULL)
	{
		ci->hClanMark32->Release();
		ci->hClanMark32 = NULL;
	}
	ci->hClanMark32 = LoadDibSurfaceOffscreen(szTemp);
	return 0;
}




BOOL bViewClanInfoDown = FALSE;
int CViewClanInfo::DownLoadClanInfo(int num, DWORD dwClanNum)
{

	int nNum;
	char MarkNum[64];
	wsprintf(MarkNum, "%u", dwClanNum);


	nCheckDownLoad = 1;
	CLANINFO *pCL = &ClanInfo[0];


	bViewClanInfoDown = TRUE;

	if(num < 0)
	{
		int i = 0;
		for(i = 0; i < CLAN_MAX; i++, pCL++)
		{
			if((pCL->nStatus == 0) || pCL->nStatus == 3)
			{
				nNum = i;
				pCL->nStatus = 1;
				strcpy(pCL->ClanInfoHeader.ClanMark_Num, MarkNum);
				break;
			}
		}

		if(i == CLAN_MAX)
		{
			SortDelete();
			nNum = nLowTime;
		}
	}
	else nNum = num;
	WebDB.Suspend();
	WebDB.Resume();




	WebDB.ReadClanInfo(MarkNum, &ClanInfo[nNum]);


	downClanSu++;


#ifdef CLAN_DEBUG
	DebugMessage("DownLoadClanInfo(%d,클랜번호 : %d )에서 클랜정보를 다운 받음", num, dwClanNum);
#endif

	return nNum;
}



void CViewClanInfo::Main()
{
}




char* clanINFO_result(char *marknum, char *szInfo, CLANINFO* ci)
{
	debug_fd2("clanINFO_result marknum %s ", marknum);
	return g_ViewClanInfo.AddClanInfo(marknum, szInfo, ci);
}


char* CViewClanInfo::AddClanInfo(char *marknum, char *szInfo, CLANINFO* ci)
{
	char szClanReport[90];
	char szTemp[100];
	BOOL bFlag = FALSE;


	HANDLE hFile = NULL;
	DWORD dwWrite;
	int nClanMarklen = 0;





















	ci->ClanInfoHeader.nClanMark = atoi(marknum);
	chk_readStrBuf("CName=", szInfo, ci->ClanInfoHeader.ClanName);


	ParsingData("CNote=", szInfo, ci->ClanInfoHeader.ClanReport);

	strcpy(szClanReport, ci->ClanInfoHeader.ClanReport);
	strcpy(ci->ClanInfoHeader.ClanMark_Num, marknum);




	nClanMarklen = lstrlen(ci->ClanInfoHeader.ClanMark_Num);

	if(nClanMarklen == 9)
	{
		ci->ClanInfoHeader.Gserver[0] = ci->ClanInfoHeader.ClanMark_Num[0];
		strcpy(ci->ClanInfoHeader.UniqueClaClanInfo_nNum, &ci->ClanInfoHeader.ClanMark_Num[3]);
	}
	else
	{
		ci->ClanInfoHeader.Gserver[0] = ci->ClanInfoHeader.ClanMark_Num[0];
		ci->ClanInfoHeader.Gserver[1] = ci->ClanInfoHeader.ClanMark_Num[1];
		strcpy(ci->ClanInfoHeader.UniqueClaClanInfo_nNum, &ci->ClanInfoHeader.ClanMark_Num[4]);
	}

	ci->dwTime = GetCurrentTime();

	wsprintf(szTemp, "%s\\%s\\%s_%s.rep", CLANINFO_DIR, szConnServerName, ci->ClanInfoHeader.Gserver, ci->ClanInfoHeader.UniqueClaClanInfo_nNum);
	hFile = CreateFile(szTemp, GENERIC_WRITE, FILE_SHARE_WRITE,
					   NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile != INVALID_HANDLE_VALUE)
	{
		WriteFile(hFile, &ci->ClanInfoHeader, sizeof(CLANINFOHEADER), &dwWrite, NULL);
		CloseHandle(hFile);
	}








#ifdef CLAN_DEBUG
	DebugMessage("AddClanInfo()호출 마크번호 : %s", marknum);
#endif
	return ci->ClanInfoHeader.ClanName;

}


int CViewClanInfo::chk_readStrBuf(char *cmd, char *readbuf, char *retBuf)
{
	int iRejectCode = -1;
	char *pBuf;

	pBuf = strstr(readbuf, cmd);
	if(pBuf == NULL)
	{
		return iRejectCode;
	}

	pBuf = pBuf + strlen(cmd);
	while(1)
	{
		if(*pBuf == '\n') return 0;
		if(*pBuf != ' ') break;
		pBuf++;
	}
	sscanf(pBuf, "%s", retBuf);

	return iRejectCode;
}

void CViewClanInfo::ParsingData(char* cmd, char* data, char* save)
{
	char *pBuf;
	int nCount = 0;
	char szTemp[500];
	ZeroMemory(szTemp, sizeof(char) * 500);
	pBuf = strstr(data, cmd);
	pBuf = pBuf + strlen(cmd);
	strcpy(szTemp, pBuf);
	if(pBuf == NULL)
	{
		return;
	}

	pBuf = pBuf + strlen(cmd);
	while(1)
	{

		if(szTemp[nCount] == '\r') break;
		save[nCount] = szTemp[nCount];
		nCount++;

	}

}

void CViewClanInfo::SortDelete()
{
	int i;
	DWORD dwTimeSave;
	nLowTime = 0;
	dwTimeSave = ClanInfo[0].dwTime;
	for(i = 1; i < CLAN_MAX; i++)
	{
		if(ClanInfo[i].dwTime < dwTimeSave)
		{
			dwTimeSave = ClanInfo[i].dwTime;
			nLowTime = i;
		}
	}
#ifdef USE_PROSTONTALE		
	if(ClanInfo[nLowTime].hClanMark != NULL)
	{

		ClanInfo[nLowTime].hClanMark->Release();
		ClanInfo[nLowTime].hClanMark = NULL;
	}
#else
	if(ClanInfo[nLowTime].hClanMark != NULL)
	{

		DeleteObject(ClanInfo[nLowTime].hClanMark);

	}
#endif
	ZeroMemory(&ClanInfo[nLowTime], sizeof(CLANINFO));
}


BOOL CViewClanInfo::SearchDirectory()
{
	WIN32_FIND_DATA wfd;
	HANDLE hFind;
	char t[50];
	wsprintf(t, "%s\\*.dat", CLANINFO_DIR);
	hFind = FindFirstFile(t, &wfd);
	if(hFind == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	return TRUE;
}

void CViewClanInfo::MakeDirectory()
{



	CreateDirectory(CLANINFO_DIR, NULL);


}

void CViewClanInfo::LoadData()
{
	WIN32_FIND_DATA wfd;
	HANDLE hFind = NULL;
	char szFile[100];
	char szFileName[100];
	BOOL bReturn = FALSE;
	BOOL bNext_Folder = TRUE;
	int nCount = 0;

	ZeroMemory(szFile, sizeof(szFile));

	while(1)
	{
		wsprintf(szFile, "%s\\*.rep", CLANINFO_DIR);
		if(bNext_Folder == TRUE)
		{
			hFind = FindFirstFile(szFile, &wfd);
			if(hFind == INVALID_HANDLE_VALUE)
			{
				break;
			}
		}
		bNext_Folder = FALSE;
		memset(szFileName, 0, sizeof(szFileName));
		wsprintf(szFileName, "%s\\%s", CLANINFO_DIR, wfd.cFileName);
		ReadToFile(szFileName, nCount);
		bReturn = FindNextFile(hFind, &wfd);

		if(!bReturn)
		{
			break;
		}
		nCount++;
	}

	bReturn = FALSE;
	bNext_Folder = TRUE;
	nCount = 0;

	while(1)
	{
		wsprintf(szFile, "%s\\*.bmp", CLANINFO_DIR);
		if(bNext_Folder == TRUE)
		{
			hFind = FindFirstFile(szFile, &wfd);
			if(hFind == INVALID_HANDLE_VALUE)
			{
				break;
			}
		}
		bNext_Folder = FALSE;
		memset(szFileName, 0, sizeof(szFileName));
		wsprintf(szFileName, "%s\\%s", CLANINFO_DIR, wfd.cFileName);
		ReadToImage(szFileName, nCount);
		bReturn = FindNextFile(hFind, &wfd);

		if(!bReturn)
		{
			break;
		}
		nCount++;
	}
}

void CViewClanInfo::ReadToFile(char *file, int count)
{




	HANDLE hFile;
	DWORD dwRead;
	hFile = CreateFile(file, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
					   NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile != INVALID_HANDLE_VALUE)
	{
		ReadFile(hFile, &ClanInfo[count].ClanInfoHeader, sizeof(CLANINFOHEADER), &dwRead, NULL);
		CloseHandle(hFile);
	}

}

void CViewClanInfo::ReadToImage(char *file, int count)
{

#ifdef  USE_PROSTONTALE
	ClanInfo[count].hClanMark = LoadDibSurfaceOffscreen(file);
#else			
	ClanInfo[count].hClanMark = (HBITMAP)LoadImage(NULL, file,
												   IMAGE_BITMAP,
												   0, 0, LR_LOADFROMFILE);

#endif					
}


BOOL CViewClanInfo::CheckWhere(char *MarkNum)
{

	char ClanMarkNum[64];
	strcpy(ClanMarkNum, MarkNum);
	char szTemp[64];

	wsprintf(szTemp, "%s\\%c_%s.rep", ClanMarkNum[0], ClanMarkNum[3]);



	HANDLE hFile;
	DWORD dwAcess = 0;
	hFile = CreateFile(szTemp, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
					   NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile != INVALID_HANDLE_VALUE)
	{
		SetFilePointer(hFile, 0, NULL, FILE_END);

		int chk = WriteFile(hFile, &ClanInfo[ClanInfo_nNum].ClanInfoHeader, sizeof(CLANINFOHEADER), &dwAcess, NULL);

		CloseHandle(hFile);
	}





	wsprintf(szTemp, "%s\\%c_%s.bmp", ClanMarkNum[0], ClanMarkNum[3]);

#ifdef  USE_PROSTONTALE
	ClanInfo[ClanInfo_nNum].hClanMark = LoadDibSurfaceOffscreen(szTemp);
#else			
	ClanInfo[ClanInfo_nNum].hClanMark = (HBITMAP)LoadImage(NULL, szTemp,
														   IMAGE_BITMAP,
														   0, 0, LR_LOADFROMFILE);
#endif			

	if(ClanInfo[ClanInfo_nNum].hClanMark == NULL)
	{
		ZeroMemory(&ClanInfo[ClanInfo_nNum].ClanInfoHeader, sizeof(CLANINFOHEADER));
		return FALSE;
	}

	ClanInfo[ClanInfo_nNum].dwTime = GetCurrentTime();
	ClanInfo[ClanInfo_nNum].nStatus = 2;

	return TRUE;
}
