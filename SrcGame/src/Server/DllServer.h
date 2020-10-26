#ifndef DATABASE_DLL_H
#define DATABASE_DLL_H


int InitLogSql();
int CloseLogSql();
int RecordLogSql(DWORD	dwRecCode, char *szIP, const char *lpUserID, const  char *lpCharName, char *szGPCode, int Race, int JobCode, INT64 Exp64, DWORD dwLevel, DWORD dwMoney);
int RecordGameLogSql(DWORD	dwRecCode, char *szIP, const char *lpUserID, const  char *lpCharName, char *szGPCode, int JobCode, char *szGuid, int BlockTime);

#define		LOG_SQL_LOGIN			0
#define		LOG_SQL_NEWCHAR			1
#define		LOG_SQL_DELCHAR			2
#define		LOG_SQL_LOGOUT			3


#define		GAMELOG_SQL_LOGIN		0x100
#define		GAMELOG_SQL_LOGOUT		0x101

#define		GAMELOG_SQL_SOD			0x102
#define		GAMELOG_SQL_STARPOINT	0x104
#define		GAMELOG_SQL_GIVEMONEY	0x106
#define		GAMELOG_SQL_CLANMONEY	0x107
#define		GAMELOG_SQL_SIEGETAX	0x108
#define		GAMELOG_SQL_POLLRECORD	0x109

#define		GAMELOG_SQL_EVENTJOIN	0x110

#define		BILLING_SQL_LOGOUT		0x201
#define		BILLING_SQL_PCUSE		0x202
#define		BILLING_SQL_PC_SRESERV	0x203
#define		BILLING_SQL_PC_TIME		0x204
#define		BILLING_SQL_BILL_CHANGE	0x205
#define		BILLING_SQL_EVENT_LOGIN		0x206
#define		BILLING_SQL_EVENT_LOGOUT	0x207

#define		BILLING_DISPLAY			0x210


#define		BILLING_URS_EXPINED		0x400

#define		CLAN_USER_TICKET		0x801
#define		CLAN_INSERT_POINT		0x802
#define		CLAN_GET_MARKCODE		0x803

#define		EGT_GET_EXPGAMETIME		0x901

#define		LOAD_DLL_NONE			0
#define		LOAD_DLL_SQL			1
#define		LOAD_DLL_URS			2

extern		int UseDLL_Code;


int	bSql_LogOn(char *lpszPID, char *lpszPWD, char *lpszIP, char *lpszGPCode, char *lpszDisuseDay, char *lpszUsePeriod, char *szGuid, char *lpszPCRNo, char *lpszGubunCode);
int	bSql_Logout(const char *lpszPID, const char *lpszCID, char *lpszIP, char *lpszGPCode, time_t DisuseDay, int UsePeriod, char *szGuid, int PCRNo);
int	bSql_EventLogon(rsPLAYINFO *lpPlayInfo);
int	bSql_EventLogOut(rsPLAYINFO *lpPlayInfo);


int	bSql_GetExpGameTime(rsPLAYINFO *lpPlayInfo, int GamePlayTime);


int	bSql_GetGPCode(char *GPCode, char *PG);
int	bSql_PCUse(rsPLAYINFO *lpPlayInfo);
int	bSql_PCSearchReserv(rsPLAYINFO *lpPlayInfo);
int	bSql_ChangeUserIdGpCodeGame(int PCRNo);

int	bSql_PCRNoReservProduct(rsPLAYINFO *lpPlayInfo);
int	bSql_GetQueLogOut(char *szID);
int	bSql_SODRecord(rsPLAYINFO *lpPlayInfo, int Level, int SodScore, int SodKillCount, int SodTotalScore, int SodTotalSucessUser, int SodTotalUser, int SodCode);
int	bSql_StarPoint(rsPLAYINFO *lpPlayInfo, int StarPoint, int CashFlag);
int	bSql_GiveMoney(rsPLAYINFO *lpPlayInfo, int Money);
int	bSql_PollRecord(rsPLAYINFO *lpPlayInfo, int PollKind, int PollCount, BYTE *PollData);
int	bSql_ClanMoney(rsPLAYINFO *lpPlayInfo, int Cash, int CashFlag, int Kind);
int	bClan_GetClanMarkCode(rsPLAYINFO *lpPlayInfo);

int	bSql_EventJoin(rsPLAYINFO *lpPlayInfo);
int	bSql_RecordCurrency();

int b_SqlGetLossCount();
int b_SqlGetQueSize();
int b_SqlGetQueProcessTime(DWORD *pTimeMax, DWORD *pAvgTime);


int	bSql_ServerDown();
int	bSql_ServerExit();



struct	_LogITEM
{
	DWORD	dwCode;
	DWORD	dwINo[2];
};



struct LogITEM
{
	int 		size;
	char 		UserID[ACCOUNT_SIZE];
	char 		CharName[NAME_SIZE];
	long 		IP;
	int 		Flag;
	int		ItemCount;
	_LogITEM Item[32];
};


struct LogITEM_TRADE
{
	int 		size;
	char 		UserID[ACCOUNT_SIZE];
	char 		CharName[NAME_SIZE];
	long		IP;
	int 		Flag;

	char 		TUserID[ACCOUNT_SIZE];
	char 		TCharName[NAME_SIZE];
	long 		TIP;
	int		Money;
	int		ItemCount;
	_LogITEM 	Item[32];
};



struct LogGiftITEM
{
	int 		size;
	char 		UserID[ACCOUNT_SIZE];
	char 		CharName[NAME_SIZE];
	long 		IP;
	int 		Flag;
	long		GNo;
	char 		TEL[16];
	_LogITEM 	Gitem;
};


struct	LogITEM_QUE
{
	int		LogType;
	char	szBuff[sizeof(LogITEM_TRADE)];
};

#define		LOG_ITEM_QUE_MAX		1024
#define		LOG_ITEM_QUE_MASK		1023


struct	LogEVENT_QUE
{
	int		LogType;
	char	szBuff[512];
};
#define		LOG_EVENT_QUE_MAX		256
#define		LOG_EVENT_QUE_MASK		255


int b_PopLogItemQue(LogITEM_QUE *lpLogItemQue);

int	b_PushLogItemQue(int type, int size, void *lpLogItemData);

int b_SqlGetItemQueSize();
int b_SqlGetItemLossCount();



int	b_PushLogEventQue(int type, int size, void *lpLogEventData);

int b_PopLogEventQue(LogEVENT_QUE *lpLogEventQue);
int b_SqlGetEventQueSize();
int b_SqlGetEventLossCount();


int	b_IPRecord(char *lpszServerName, struct JUNGIP *JungIP);

int	b_IPRecordTime(char *lpszServerName, struct JUNGIP *JungIP);

#define	JUNGIP_MAX	1024

struct JUNGIP
{
	int	  IPCount;
	DWORD IP[JUNGIP_MAX];
};


int bClan_GetTicket();

int	bClan_UserTicket(rsPLAYINFO *lpPlayInfo, int gubun);

int	bClan_InsertPoint(rsPLAYINFO *lpPlayInfo, int point);






#endif 
