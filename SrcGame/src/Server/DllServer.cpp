#include <windows.h>
#include <io.h>
#include <stdio.h>         
#include <string.h>        
#include <memory.h>
#include <process.h>       

#include "Resources\resource.h"
#include "..\\smwsock.h"

#include "..\\smlib3d\\smd3d.h"
#include "..\\character.h"
#include "..\\fileread.h"
#include "..\\playmain.h"
#include "..\\field.h"
#include "..\\sinbaram\\sinlinkheader.h"
#include "..\\effectsnd.h"

#include "..\\record.h"
#include "..\playsub.h"

#include "DllServer.h"
#include "onserver.h"

#define		BILLING_METER_RATE

#define	SWM_DISPDEBUG	(WM_USER+77)


char szServerName[64] = "Unnamed Server";


CRITICAL_SECTION cSqlSection;



int InitLogSql()
{
	return TRUE;
}
int CloseLogSql()
{
	return TRUE;
}
int RecordLogSql(DWORD	dwRecCode, char *szIP, const char *lpUserID, const char *lpCharName, char *szGPCode, int Race, int JobCode, INT64 Exp64, DWORD dwLevel, DWORD dwMoney)
{
	return TRUE;
}
int RecordGameLogSql(DWORD	dwRecCode, char *szIP, const char *lpUserID, const char *lpCharName, char *szGPCode, int JobCode, char *szGuid, int BlockTime)
{
	return TRUE;
}

int	bSql_LogOn(char *lpszPID, char *lpszPWD, char *lpszIP, char *lpszGPCode, char *lpszDisuseDay, char *lpszUsePeriod, char *szGuid, char *lpszPCRNo)
{
	return TRUE;
}

int	bSql_Logout(const char *lpszPID, const char *lpszCID, char *lpszIP, char *lpszGPCode, time_t DisuseDay, int UsePeriod, char *szGuid, int PCRNo)
{
	return TRUE;
}


int	bSql_ServerDown()
{
	return TRUE;
}
int	bSql_ServerExit()
{
	return TRUE;
}
int	bSql_GetGPCode(char *GPCode, char *PG)
{
	return TRUE;
}


int	bSql_PCUse(rsPLAYINFO *lpPlayInfo)
{
	return TRUE;
}

int	bUrs_Expined(rsPLAYINFO *lpPlayInfo)
{
	return TRUE;
}


int	bSql_PCSearchReserv(rsPLAYINFO *lpPlayInfo)
{
	return TRUE;
}

int	bSql_ChangeUserIdGpCodeGame(int PCRNo)
{
	return TRUE;
}

int	bSql_EventLogon(rsPLAYINFO *lpPlayInfo)
{
	return TRUE;
}

int	bSql_EventLogOut(rsPLAYINFO *lpPlayInfo)
{
	return TRUE;
}



int	bSql_PCRNoReservProduct(rsPLAYINFO *lpPlayInfo)
{
	return TRUE;
}


int	b_IPRecord(char *lpszServerName, struct JUNGIP *JungIP)
{
	return TRUE;
}

int	b_IPRecordTime(char *lpszServerName, struct JUNGIP *JungIP)
{
	return TRUE;
}


int	bSql_SODRecord(rsPLAYINFO *lpPlayInfo, int Level, int SodScore, int SodKillCount, int SodTotalScore, int SodTotalSucessUser, int SodTotalUser, int SodCode)
{
	return TRUE;
}

int	bSql_StarPoint(rsPLAYINFO *lpPlayInfo, int StarPoint, int CashFlag)
{
	return TRUE;
}


int	bSql_PollData(rsPLAYINFO *lpPlayInfo, int PollKind, int PollCount, BYTE *PollData)
{
	return TRUE;
}


int	bSql_GetExpGameTime(rsPLAYINFO *lpPlayInfo, int GamePlayTime)
{
	return TRUE;
}


int	bSql_EventJoin(rsPLAYINFO *lpPlayInfo)
{
	return TRUE;
}

int	bSql_ClanMoney(rsPLAYINFO *lpPlayInfo, int Cash, int CashFlag, int Kind)
{
	return	TRUE;
}


int	bClan_GetClanMarkCode(rsPLAYINFO *lpPlayInfo)
{
	return TRUE;
}

int	bSql_RecordCurrency()
{
	return	TRUE;
}


int	bSql_GiveMoney(rsPLAYINFO *lpPlayInfo, int Money)
{
	return TRUE;
}

int b_SqlGetQueSize()
{
	return TRUE;
}
int b_SqlGetLossCount()
{
	return TRUE;
}
int b_SqlGetQueProcessTime(DWORD *pTimeMax, DWORD *pAvgTime)
{
	return TRUE;
}

int b_PopLogItemQue(LogITEM_QUE *lpLogItemQue)
{
	return TRUE;
}

int	b_PushLogItemQue(int type, int size, void *lpLogItemData)
{
	return TRUE;
}


int b_SqlGetItemQueSize()
{
	return TRUE;
}
int b_SqlGetItemLossCount()
{
	return TRUE;
}


int b_PopLogEventQue(LogEVENT_QUE *lpLogEventQue)
{
	return TRUE;
}

int	b_PushLogEventQue(int type, int size, void *lpLogEventData)
{
	return TRUE;
}


int b_SqlGetEventQueSize()
{
	return TRUE;
}
int b_SqlGetEventLossCount()
{
	return TRUE;
}



int	bClan_UserTicket(rsPLAYINFO *lpPlayInfo, int gubun)
{
	return TRUE;
}

int	bClan_InsertPoint(rsPLAYINFO *lpPlayInfo, int point)
{
	return TRUE;
}


DWORD nSprite_GetResult(DWORD nRecvNum)
{
	return TRUE;
}

