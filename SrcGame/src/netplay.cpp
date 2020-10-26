


#include "smlib3d\\smd3d.h"

#include "smwsock.h"
#include "character.h"
#include "playmain.h"
#include "fileread.h"

#include "particle.h"
#include "sinbaram\\sinlinkheader.h"
#include "record.h"
#include "netplay.h"
#include "playsub.h"
#include "field.h"
#include "Language\\language.h"
#include "Language\\jts.h"
#include "TextMessage.h"
#include "cracker.h"
#include "tjboy\\clanmenu\\tjclanDEF.h"
#include "tjboy\\clanmenu\\tjclan.h"
#include "tjboy\\clanmenu\\help.h"
#include "damage.h"
#include "skillsub.h"

#include "AreaServer.h"

#include "BellatraFontEffect.h"
#include "Server\\onserver.h"


#include "cQuestWindow.h"

#include "WinInt\\WinIntThread.h"
#include "WinInt\\WavIntHttp.h"
#include "WinInt\\ZipLib.h"


#include "CurseFilter.h"		

#include "AntiCheat\AntiCheat.h"
#include "Log\Log.h"
#include "sinbaram\\sinSkill_InfoIni.h"
#include "cPartyWindow.h"

#include "../Shared/smPacket.h"

extern int WinSizeX;
extern int WinSizeY;
extern HWND hwnd;

int EventBattleArena;
DWORD EventBattleArenaTime;
int QuestDiaryState;
int QuestDiaryKill1;
int QuestDiaryKill2;
int CharBattleLevel;
int CharBattleExp1;
int CharBattleExp2;
DWORD ClanTop2 = 0;
DWORD ClanTop3 = 0;


#define SERVER_CHAR_INFO


#define RECORD_TIME_STEP		(5*60*1000)

#define NET_LOADING_WAIT_LIMIT		10000


extern CRITICAL_SECTION	cSection;
extern rsRECORD_DBASE	rsRecorder;
DWORD	dwLastRecordTime = 0;
char szReiArena[32];
CRITICAL_SECTION	cServSection;
BUFF_KILL BuffKill[32];
int MatBuffKill[4];
int Debug_SendCount = 0;
int Debug_RecvCount1 = 0;
int Debug_RecvCount2 = 0;
int Debug_RecvCount3 = 0;

int NetWorkInitFlag = 0;
int	BellatraEffectInitFlag = 0;
SBL_SetFontEffect SoD_SetFontEffect;


DWORD	dwTime_ServerT = 0;
DWORD	dwTime_ConnectMS = 0;




//ATUALIZAR VERSÃO PARA LOGAR
#ifdef _LANGUAGE_BRAZIL
#ifndef	_WINMODE_DEBUG
#define	CLIENT_VERSION_NUM		4135
#else
#define	CLIENT_VERSION_NUM		70517
#endif
#endif

int MatG = 0;
int MatQD = 0;
int MatB = 0;
#define CLIENT_VERSION_CHECK	(-CLIENT_VERSION_NUM * 2)

int	Client_Version = CLIENT_VERSION_NUM;
int	Server_LimitVersion = CLIENT_VERSION_NUM;

int ChatBuffCnt;
int	Version_WareHouse = 1;
int	Version_CharInfo = 1;
int ReiPVP = 0;
int PlayerGM = 0;
int PlayerBeta = 0;
int PLayerTopLevel = 0;

//Buffs SET BOSS
int SetBoss1Bonus1;
int SetBoss1Bonus2;
int SetBoss2Bonus1;
int SetBoss2Bonus2;

smWINSOCK	*smWsockServer = 0;
smWINSOCK	*smWsockDataServer = 0;
smWINSOCK	*smWsockUserServer = 0;
smWINSOCK	*smWsockExtendServer = 0;

BATTLE_ARENA_POINT Battle;

int	ReconnDataServer = 0;
int	ReconnServer = 0;

char	szConnServerName[16];

DWORD	dwRecvUserServerTime = 0;
DWORD	dwRecvDataServerTime = 0;
DWORD	dwRecvServerTime = 0;
DWORD	dwRecvExtendServerTime = 0;


int	rsRecvDataServer = TRUE;
int	rsRecvServer = TRUE;
int	rsRecvUserServer = TRUE;
int	rsRecvExtendServer = TRUE;

const int CHATBUFF_MAX = 64;
const int CHATBUFF_MASK = 63;

DWORD dwMyIP;

CHATBUFF ChatBuff[CHATBUFF_MAX];
CHATBUFF ChatBuff2[6][CHATBUFF_MAX];


int	ChatBuffCnt2[6] = { 0,0,0,0,0,0 };
int ChatDispCnt = 0;
int	ChatBuffCompCnt = 0;

char *szDefaultServIP = "211.50.44.170";

char *szNetLogFile = "debugnet.log";
FILE *fpNetLog = 0;


int	DisconnectFlag = 0;
int	DisconnectServerCode = 0;


int	WarningHack = 0;

DWORD	dwQuestDelayTime = 0;

DWORD	dwLoadingTime = 0;

char szServIP[32];
DWORD dwServPort;
char szDataServIP[32];
DWORD dwDataServPort;
char szUserServIP[32];
DWORD dwUserServPort;
char szExtendServIP[32];
DWORD dwExtendServPort;



DWORD	dwConnectedClientTime = 0;
DWORD	dwConnectedServerTime = 0;
DWORD	dwLastRecvGameServerTime = 0;
DWORD	dwLastRecvGameServerTime2 = 0;
DWORD	dwLastRecvGameServerTime3 = 0;
DWORD	dwLastRecvGameServerTime4 = 0;

typedef DWORD(*LPFN_CheckMem)(TRANS_FUNC_MEMORY *TransFuncMem, smTRANS_COMMAND	*lpTransCommand);
LPFN_CheckMem	fnChkMem2;


static int	CompWareHouseMoney = 0;
int	WareHouseSubMoney = 0;
int TotalSubMoney = 0;
int TotalAddMoney = 0;
int	TotalAddExp = 0;
int	TotalSubExp = 0;


smTRANS_COMMAND	*lpTransVirtualPotion = 0;


LPFN_CheckMem	fnChkMem;
DWORD	dwMemFunChkCode = 0;

int	RecvMemFuncData(TRANS_FUNC_MEMORY *TransFuncMem);
int	RecvMemFuncData2(TRANS_FUNC_MEMORY *TransFuncMem);

DWORD funcCheckMemSum(DWORD FuncPoint, int count);

int CheckProcessModule();



smPLAYDATA	PlayData;
char	TransBuff[smSOCKBUFF_SIZE];
int		TransLen;



TRANS_ITEMINFO	TransThrowItem;

TRANS_ITEMINFO	TransRecvItem;


TRANS_TRADE_ITEMKEY	LastTransTradeItemKey;
DWORD				dwLastTransTradeKeyTime = 0;

int					InitClanMode = 0;

DWORD				dwYahooTime = 0;

int					ServerHideMode = 0;

int nCristalInUse = 0;

PK_FIELD_STATE	PK_FieldState;

std::unordered_map<DWORD, sITEMINFO> mapItemInfo;

bool bSendGetItemInfoPerf = false;

struct TRANS_TRADE_CHECKITEM
{
	int size, code;
	DWORD	dwSender;
	DWORD	dwRecver;
	DWORD	dwSum;

	DWORD	dwSendItemCode[MAX_TRADE_ITEM];
	DWORD	dwSendItemSum[MAX_TRADE_ITEM];

	DWORD	dwRecvItemCode[MAX_TRADE_ITEM];
	DWORD	dwRecvItemSum[MAX_TRADE_ITEM];
};



int		TradeItemSucessFlag = 0;
int		TradeRecvItemKeyFlag = 0;
int		TradeSendSucessFlag = 0;
DWORD	dwTradeMaskTime = 0;
int		TradeItemCancelCount = 0;

TRANS_TRADEITEMS	TransLastRecvTrade;

TRANS_TRADEITEMS	TransTradeItems_MyShop;


DWORD	dwLastWareHouseChkSum = 0;


int		TransAgingItemFlag;

smTRANS_COMMAND	TransServerConnectInfo;


int ConnectOtherPlayer(DWORD dwIP);

int HoRecvMessage(DWORD dwCode, void *RecvBuff);


int RecvTradeSucessKey(TRANS_TRADE_ITEMKEY *lpTransTradeItemKey, sTRADE *lpTrade);

int SendTradeSucessKey(sTRADE *lpTrade, DWORD dwSender);

int RecvTradeCheckItem(TRANS_TRADE_CHECKITEM *lpTransTradeCheckItem);

int SendCrackWindow(HWND hWnd);


int ThrowItemToServer(smTRANS_COMMAND_EX *lpTransCommand);

int RecvCheckItemFromServer(TRANS_ITEM_CODE *lpTransItemCode);

int RecvItemInfoPerf(TRANS_ITEMINFO *lpTransItemInfo);

int	SendClientFuncPos();


int OpenTimeCheckThread();

int SendPlayTimerMax();



TRANS_ITEMINFO	*FindRecvTransItemQue(DWORD dwCode, DWORD dwHead, DWORD dwChkSum);

int	PushRecvTransItemQue(TRANS_ITEMINFO *lpTransItemInfo);


int RecvProcessSkill(smTRANS_COMMAND *lpTransCommand);

int RecvPartySkillFromServer(TRANS_PARTY_SKILL *lpTransPartySkill);


int FiltQuestItem(TRANS_ITEMINFO	*lpTransItemInfo, DWORD dwPacketCode);

int SucessLinkCore(smTRANS_COMMAND_EX *lpTransCommandEx);

int RecvSodGameInfomation(void *Info);


int RecvForceOrbItem(TRANS_ITEMINFO_GROUP2 *lpTransItemGroup2);


int XTrap_Recv(smTRANS_COMMAND *lpPacket, smWINSOCK *lpsmSock);


rsBLESS_CASTLE	rsBlessCastleOld;


DWORD	dwResistance_SendingTime = 0;



#define	ATT_MONSTER_MAX	128
#define	ATT_MONSTER_MASK	(ATT_MONSTER_MAX-1)

DWORD	dwAttMonsterCodeList[ATT_MONSTER_MAX];
int		AttMonsterCodeCount = 0;


int ClearAttMonsterCode()
{
	int cnt;
	for (cnt = 0; cnt < ATT_MONSTER_MAX; cnt++)
	{
		dwAttMonsterCodeList[cnt] = 0;
	}
	return TRUE;
}

int	AddAttMonsterCode(DWORD dwCode)
{
	int mcnt;
	if (dwCode)
	{
		mcnt = (AttMonsterCodeCount - 1)&ATT_MONSTER_MASK;
		if (dwAttMonsterCodeList[mcnt] == dwCode) return TRUE;
		mcnt = AttMonsterCodeCount & ATT_MONSTER_MASK;
		dwAttMonsterCodeList[mcnt] = dwCode;
		AttMonsterCodeCount++;
		return TRUE;
	}

	return FALSE;
}

int	CheckAttMonsterCode(DWORD dwCode)
{
	int cnt;
	for (cnt = 0; cnt < ATT_MONSTER_MAX; cnt++)
	{
		if (dwAttMonsterCodeList[cnt] == dwCode) return TRUE;
	}
	return FALSE;
}


int CheckServerInfo(smTRANS_COMMAND *lpTransCommand)
{
	if ((-Client_Version * 2) != CLIENT_VERSION_CHECK)
	{
		SetGameError(1);
		return TRUE;
	}

	if (Client_Version < lpTransCommand->WParam)
	{
		SetGameError(1);
		return TRUE;
	}

	if (lpTransCommand->LParam > 0)
	{
		SetGameError(2);
		return TRUE;
	}

	SetGameError(0);
	return TRUE;
}


int SendProcessInfo()
{
	TRANS_CHATMESSAGE	smTransChatMessage;

	if (smWsockDataServer)
	{
		smTransChatMessage.code = OpCode::OPCODE_PROCESSINFO;
		smTransChatMessage.dwIP = dwExeCheckSum;
		smTransChatMessage.dwObjectSerial = dwExeCheckSum;

		strcpy_s(smTransChatMessage.szMessage, szProcessPath);
		smTransChatMessage.size = 32 + lstrlen(szProcessPath);

		return smWsockDataServer->Send((char *)&smTransChatMessage, smTransChatMessage.size, TRUE);
	}
	return FALSE;
}



smWINSOCK *ConnectServer_Main()
{
	char server1[32];
	char server2[32];
	char server3[32];


	if (!smWsockServer)
	{
		if (server2[0])
			strcpy_s(szServIP, server2);
		else
			strcpy_s(szServIP, szDefaultServIP);

		if (cSettings::GetInstance()->cPort)
			dwServPort = cSettings::GetInstance()->cPort;
		else
			dwServPort = 10009;

		smWsockServer = smConnectSock(szServIP, (WORD)dwServPort);
	}

	if (smWsockServer && !smWsockDataServer)
	{

		if (server1[0] && lstrcmpi(server1, server2) != 0)
		{
			strcpy_s(szDataServIP, server1);
			dwDataServPort = cSettings::GetInstance()->cPort;
			smWsockDataServer = smConnectSock(szDataServIP, (WORD)dwDataServPort);
		}
		else
		{

			strcpy_s(szDataServIP, szServIP);
			dwDataServPort = dwServPort;
			smWsockDataServer = smWsockServer;
		}
	}

	if (smWsockServer && smWsockDataServer && !smWsockUserServer)
	{

		if (server3[0] && lstrcmpi(server3, server2) != 0)
		{
			strcpy_s(szUserServIP, server3);
			dwUserServPort = cSettings::GetInstance()->cPort;
			smWsockUserServer = smConnectSock(szUserServIP, (WORD)dwUserServPort);
		}
		else
		{

			strcpy_s(szUserServIP, szServIP);
			dwUserServPort = dwServPort;
			smWsockUserServer = smWsockServer;
		}
	}

	if (smWsockServer && smWsockDataServer && !smWsockExtendServer)
	{

		if (server2[0] && lstrcmpi(server2, server2) != 0)
		{
			strcpy_s(szExtendServIP, server2);
			dwExtendServPort = cSettings::GetInstance()->cPort;
			smWsockExtendServer = smConnectSock(szExtendServIP, (WORD)dwExtendServPort);
		}
		else
		{

			strcpy_s(szExtendServIP, szServIP);
			dwExtendServPort = dwServPort;
			smWsockExtendServer = smWsockServer;
		}
	}


	if (smWsockServer && smWsockDataServer && smWsockUserServer)
	{

		if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
		{

		}

		return smWsockServer;
	}

	return NULL;
}


int DisconnectServerFull()
{

	if (smWsockDataServer && smWsockDataServer != smWsockServer)
	{
		smWsockDataServer->CloseSocket();
		smWsockDataServer = 0;
	}
	if (smWsockUserServer && smWsockUserServer != smWsockServer)
	{
		smWsockUserServer->CloseSocket();
		smWsockUserServer = 0;
	}
	if (smWsockExtendServer && smWsockExtendServer != smWsockServer)
	{
		smWsockExtendServer->CloseSocket();
		smWsockExtendServer = 0;
	}
	if (smWsockServer)
	{
		smWsockServer->CloseSocket();
		smWsockServer = 0;
	}

	DisconnectFlag = 0;

	return TRUE;
}



smWINSOCK *ConnectServer_InfoMain()
{
	if (!smWsockDataServer)
	{
		char server1[32];

		strcpy_s(server1, sizeof(server1), cSettings::GetInstance()->Server1);

		if (server1[0])
		{
			dwDataServPort = TCP_SERVPORT;
			smWsockDataServer = smConnectSock(server1, (WORD)dwDataServPort);
			ZeroMemory(&TransServerConnectInfo, sizeof(smTRANS_COMMAND));
			return smWsockDataServer;
		}
	}


	return NULL;
}

int szBossTime = 0 ;
int szPlayerBeta = 0 ;

smWINSOCK *ConnectServer_GameMain(char *szIP1, DWORD dwPort1, char *szIP2, DWORD dwPort2)
{
	int ServerInfoFlag = 0;

	if (smWsockServer && lstrcmp(smWsockServer->szIPAddr, szIP1) != 0)
	{
		DisconnectServer_GameMain();
	}
	if (smWsockUserServer && lstrcmp(smWsockUserServer->szIPAddr, szIP2) != 0)
	{
		DisconnectServer_GameMain();
	}

	if (!smWsockServer)
	{

		if (smWsockDataServer && lstrcmp(smWsockDataServer->szIPAddr, szIP1) == 0 && dwDataServPort == dwPort1)
		{
			smWsockServer = smWsockDataServer;
			dwServPort = dwDataServPort;

			ServerInfoFlag = TRUE;
		}
		else
		{
			smWsockServer = smConnectSock(szIP1, (WORD)dwPort1);
			dwServPort = dwPort1;
		}

	}

	if (!smWsockUserServer)
	{
		if (smWsockServer && lstrcmp(smWsockServer->szIPAddr, szIP2) == 0 && dwServPort == dwPort2)
		{

			smWsockUserServer = smWsockServer;
			dwUserServPort = dwServPort;
		}
		else
		{
			smWsockUserServer = smConnectSock(szIP2, (WORD)dwPort2);
			dwUserServPort = dwPort2;
		}
	}


	if (smWsockServer && smWsockUserServer)
	{
		if (ServerInfoFlag)
		{
			CheckServerInfo(&TransServerConnectInfo);
		}

		return smWsockServer;
	}
	return NULL;
}


smWINSOCK *ConnectServer_GameMain(char *szIP1, DWORD dwPort1, char *szIP2, DWORD dwPort2, char *szIP3, DWORD dwPort3)
{
	int ServerInfoFlag = 0;

	if (smWsockServer && lstrcmp(smWsockServer->szIPAddr, szIP1) != 0)
	{
		DisconnectServer_GameMain();
	}
	if (smWsockUserServer && lstrcmp(smWsockUserServer->szIPAddr, szIP2) != 0)
	{
		DisconnectServer_GameMain();
	}
	if (smWsockExtendServer && lstrcmp(smWsockExtendServer->szIPAddr, szIP3) != 0)
	{
		DisconnectServer_GameMain();
	}

	if (!smWsockServer)
	{

		if (smWsockDataServer && lstrcmp(smWsockDataServer->szIPAddr, szIP1) == 0 && dwDataServPort == dwPort1)
		{
			smWsockServer = smWsockDataServer;
			dwServPort = dwDataServPort;

			ServerInfoFlag = TRUE;
		}
		else
		{
			smWsockServer = smConnectSock(szIP1, (WORD)dwPort1);
			dwServPort = dwPort1;
		}

	}

	if (!smWsockUserServer)
	{
		if (smWsockServer && lstrcmp(smWsockServer->szIPAddr, szIP2) == 0 && dwServPort == dwPort2)
		{
			smWsockUserServer = smWsockServer;
			dwUserServPort = dwServPort;
		}
		else
		{
			smWsockUserServer = smConnectSock(szIP2, (WORD)dwPort2);
			dwUserServPort = dwPort2;
		}
	}

	if (!smWsockExtendServer)
	{
		if ((smWsockServer && lstrcmp(smWsockServer->szIPAddr, szIP3) == 0 && dwServPort == dwPort3) || !szIP3[0])
		{
			smWsockExtendServer = smWsockServer;
			dwExtendServPort = dwServPort;
		}
		else
		{
			smWsockExtendServer = smConnectSock(szIP3, (WORD)dwPort3);
			dwExtendServPort = dwPort3;
		}
	}

	if (smWsockServer && smWsockUserServer && smWsockExtendServer)
	{
		if (ServerInfoFlag)
		{

			CheckServerInfo(&TransServerConnectInfo);
		}

		return smWsockServer;
	}
	return NULL;
}



int DisconnectServer_GameMain()
{
	if (smWsockExtendServer && smWsockExtendServer != smWsockServer)
	{
		if (smWsockDataServer != smWsockExtendServer)
		{
			smWsockExtendServer->CloseSocket();
		}
	}
	smWsockExtendServer = 0;

	if (smWsockUserServer && smWsockUserServer != smWsockServer)
	{
		if (smWsockDataServer != smWsockUserServer)
		{
			smWsockUserServer->CloseSocket();
		}
	}
	smWsockUserServer = 0;


	if (smWsockServer && smWsockDataServer != smWsockServer)
	{
		if (smWsockDataServer != smWsockServer)
		{
			smWsockServer->CloseSocket();
		}
	}
	smWsockServer = 0;

	DisconnectFlag = 0;

	return TRUE;
}


smWINSOCK *GetServerSock(int ServerCode)
{
	switch (ServerCode)
	{
	case PLAY_SERVER_CODE_EXTEND:
		if (smWsockExtendServer && smWsockServer != smWsockExtendServer)
			return smWsockExtendServer;
		else
			return smWsockUserServer;

	case PLAY_SERVER_CODE_USER:
		return smWsockUserServer;

	case PLAY_SERVER_CODE_MAIN:
		return smWsockServer;

	case PLAY_SERVER_CODE_AREA1:
		return lpWSockServer_DispArea[0];

	case PLAY_SERVER_CODE_AREA2:
		return lpWSockServer_DispArea[1];

	}

	return NULL;
}


smWINSOCK *GetAreaServerSock()
{
	int ServerCode;

	if (lpCurPlayer->OnStageField >= 0)
	{
		if (AreaServerMode)
		{
			return lpWSockServer_DispArea[lpCurPlayer->OnStageField];
		}
		else
		{
			ServerCode = StageField[lpCurPlayer->OnStageField]->ServerCode;
			return GetServerSock(ServerCode);
		}
	}

	return NULL;
}



scITEM *FindScItem(int x, int z)
{
	int cnt;

	for (cnt = 0; cnt < DISP_ITEM_MAX; cnt++)
	{
		if (scItems[cnt].Flag && scItems[cnt].pX == x && scItems[cnt].pZ == z)
		{
			return &scItems[cnt];
		}
	}

	return NULL;
}


scITEM *FindEmptyScItem()
{
	int cnt;

	for (cnt = 0; cnt < DISP_ITEM_MAX; cnt++)
	{
		if (!scItems[cnt].Flag) return &scItems[cnt];
	}

	return NULL;
}


int GetTradeDistance(smCHAR *lpChar)
{
	int	x, y, z;
	int dist;

	x = (lpCurPlayer->pX - lpChar->pX) >> FLOATNS;
	y = (lpCurPlayer->pY - lpChar->pY) >> FLOATNS;
	z = (lpCurPlayer->pZ - lpChar->pZ) >> FLOATNS;

	dist = x * x + y * y + z * z;

	if (dist < (256 * 256)) return TRUE;

	return FALSE;
}


int GetTradeDistanceFromCode(DWORD dwObjectSerial)
{
	smCHAR *lpChar;

	lpChar = FindAutoPlayer(dwObjectSerial);

	if (lpChar && lpChar->DisplayFlag && lpChar->smCharInfo.szName[0])
	{

		return  GetTradeDistance(lpChar);

	}
	return FALSE;
}


int	CheckStartCharInfo()
{

	smCHAR_INFO	smCharInfo;
	int cnt;

	memcpy(&smCharInfo, sinChar, sizeof(smCHAR_INFO));

	CheckCharForm();
	CodeXorExp = dwPlayTime + smCharInfo.Exp;
	CodeXorExp_High = dwPlayTime | (dwPlayTime*dwPlayTime);
	CodeXorLife = (dwPlayTime*smCharInfo.Life[0]) & 0xFFFF;
	cnt = smCharInfo.Dexterity + smCharInfo.Health + smCharInfo.Spirit + smCharInfo.Strength + smCharInfo.Talent;

	if (smCharInfo.Level >= 2 || cnt > 102 || smCharInfo.Exp || smCharInfo.ChangeJob || smCharInfo.Money)
	{

		SendSetHackUser2(6000, smCharInfo.Money);
		WarningHack = TRUE;
		return FALSE;
	}

	lpCurPlayer->smCharInfo.Exp ^= CodeXorExp;
	lpCurPlayer->smCharInfo.Exp_High ^= CodeXorExp_High;

	lpCurPlayer->smCharInfo.Life[0] ^= CodeXorLife;
	ReformCharForm();

	return TRUE;
}


int	RecvMemFuncData2(TRANS_FUNC_MEMORY *TransFuncMem)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.size = -1;
	fnChkMem2 = (LPFN_CheckMem)((void *)TransFuncMem->szData);
	fnChkMem2(TransFuncMem, &smTransCommand);

	ZeroMemory(TransFuncMem, 1500);

	if (smTransCommand.size > 0 && smWsockDataServer)
	{
		smTransCommand.code = OpCode::OPCODE_FUNCTION_MEM2;
		smWsockDataServer->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
	}

	return TRUE;
}



sSERVER_MONEY	sServerMoney[3] = { {0,0,0,0,0},{0,0,0,0,0} };
sSERVER_EXP		sServerExp[3] = { {0,0,0,0},{0,0,0,0} };
DWORD			dwLastSendTotalExpMoenyTime = 0;


int	SendTotalExpMoney()
{
	TRANS_TOTAL_EXPMONEY	TransTotalExpMoney;

	if ((dwLastSendTotalExpMoenyTime + 30000) > dwPlayTime) return FALSE;

	TransTotalExpMoney.code = OpCode::OPCODE_CHECK_EXPMONEY;
	TransTotalExpMoney.size = sizeof(TRANS_TOTAL_EXPMONEY);

	if (smWsockServer)
	{
		memcpy(&TransTotalExpMoney.sServerExp, &sServerExp[0], sizeof(sSERVER_EXP));
		memcpy(&TransTotalExpMoney.sServerMoney, &sServerMoney[0], sizeof(sSERVER_MONEY));
		smWsockServer->Send((char *)&TransTotalExpMoney, TransTotalExpMoney.size, TRUE);
	}
	if (smWsockUserServer && smWsockUserServer != smWsockServer)
	{
		memcpy(&TransTotalExpMoney.sServerExp, &sServerExp[1], sizeof(sSERVER_EXP));
		memcpy(&TransTotalExpMoney.sServerMoney, &sServerMoney[1], sizeof(sSERVER_MONEY));
		smWsockUserServer->Send((char *)&TransTotalExpMoney, TransTotalExpMoney.size, TRUE);
	}
	if (smWsockExtendServer && smWsockExtendServer != smWsockServer)
	{
		memcpy(&TransTotalExpMoney.sServerExp, &sServerExp[2], sizeof(sSERVER_EXP));
		memcpy(&TransTotalExpMoney.sServerMoney, &sServerMoney[2], sizeof(sSERVER_MONEY));
		smWsockExtendServer->Send((char *)&TransTotalExpMoney, TransTotalExpMoney.size, TRUE);
	}

	dwLastSendTotalExpMoenyTime = dwPlayTime;

	return TRUE;
}

extern int TradeBPEXP();

int CheckServerMoney(smWINSOCK *lpsmSock, TRANS_ITEMINFO	*lpTransItemInfo)
{
	sSERVER_MONEY	*lpServerMoney;

	lpServerMoney = 0;

	if (lpsmSock == smWsockServer)
	{
		lpServerMoney = &sServerMoney[0];
	}
	else
	{
		if (lpsmSock == smWsockUserServer)
		{
			lpServerMoney = &sServerMoney[1];
		}
		else if (lpsmSock == smWsockExtendServer)
		{
			lpServerMoney = &sServerMoney[2];
		}
	}

	if (lpServerMoney)
	{
		lpServerMoney->InputMoney += lpTransItemInfo->Item.Money;
		lpServerMoney->Counter++;
		lpServerMoney->TotalX = lpTransItemInfo->x;
		lpServerMoney->TotalY = lpTransItemInfo->y;
		lpServerMoney->TotalZ = lpTransItemInfo->z;



		int cnt;
		cnt = lpServerMoney->TotalZ ^ (lpServerMoney->TotalX + lpServerMoney->TotalY);
		cnt += 200;
		if (cnt < lpServerMoney->InputMoney)
		{

		}
	}

	return TRUE;
}


int CheckServerExp(smWINSOCK *lpsmSock, smTRANS_COMMAND	*lpTransCommand)
{
	sSERVER_EXP	*lpServerExp = nullptr;

	if (lpsmSock == smWsockServer)
	{
		lpServerExp = &sServerExp[0];
	}
	else
	{
		if (lpsmSock == smWsockUserServer)
		{
			lpServerExp = &sServerExp[1];
		}
		else if (lpsmSock == smWsockExtendServer)
		{
			lpServerExp = &sServerExp[2];
		}
	}

	if (lpServerExp)
	{
		lpServerExp->InputExp += lpTransCommand->WParam;
		lpServerExp->Counter++;
		lpServerExp->Total1 = lpTransCommand->SParam;
		lpServerExp->Total2 = lpTransCommand->EParam;


		int cnt = (lpServerExp->Total1 ^ lpServerExp->Total2) + 1600000;

		if (cnt < lpServerExp->InputExp)
		{
			
			
		}

	}

	return TRUE;
}


int CreateConnectThread(DWORD dwIP);

int CreateDisconnectThread(smWINSOCK *lpsmSock);


int FindNewOtherPlayer()
{
	int cnt;

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (!chrOtherPlayer[cnt].Flag)
			return cnt;
	}

	return -1;
}


smCHAR *FindAutoPlayer(DWORD dwObjectSerial)
{
	int cnt;

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].dwObjectSerial == dwObjectSerial)
		{
			return &chrOtherPlayer[cnt];
		}
	}

	return NULL;
}

extern bool bcanadd;

smCHAR *FindChrPlayer(DWORD dwObjectSerial)
{
	int cnt;

	if (lpCurPlayer->dwObjectSerial == dwObjectSerial)
		return lpCurPlayer;

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].dwObjectSerial == dwObjectSerial)
		{
			return &chrOtherPlayer[cnt];
		}
	}

	return NULL;
}


smCHAR *FindDeadPartyUser()
{
	int cnt;
	smCHAR *lpChar;
	int dist, x, y, z;
	int	NearDist;

	lpChar = 0;
	NearDist = 300 * 300;

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].PartyFlag && chrOtherPlayer[cnt].smCharInfo.State == smCHAR_STATE_USER)
		{
			if (chrOtherPlayer[cnt].MotionInfo->State == CHRMOTION_STATE_DEAD)
			{

				x = (lpCurPlayer->pX - chrOtherPlayer[cnt].pX) >> FLOATNS;
				y = (lpCurPlayer->pY - chrOtherPlayer[cnt].pY) >> FLOATNS;
				z = (lpCurPlayer->pZ - chrOtherPlayer[cnt].pZ) >> FLOATNS;

				dist = x * x + z * z + y * y;

				if (dist < NearDist)
				{
					lpChar = &chrOtherPlayer[cnt];
					NearDist = dist;
				}
			}
		}
	}

	return lpChar;
}

BOOL bReiPVP = FALSE;
BOOL bGm = FALSE;
BOOL bTopLevel = FALSE;
BOOL betaPlayer = FALSE;

smCHAR *FindNearMonster(smCHAR *lpCurChar)
{
	int cnt;
	smCHAR *lpChar;
	int dist, x, y, z;
	int	NearDist;

	lpChar = 0;
	NearDist = 300 * 300;

	if (!lpCurChar) return NULL;

	if (lpCurChar != lpCurPlayer)
	{
		x = (lpCurChar->pX - lpCurPlayer->pX) >> FLOATNS;
		y = (lpCurChar->pY - lpCurPlayer->pY) >> FLOATNS;
		z = (lpCurChar->pZ - lpCurPlayer->pZ) >> FLOATNS;

		dist = x * x + z * z + y * y;
		if (dist < NearDist)
		{
			if (!lpCurChar->smCharInfo.ClassClan || lpCurChar->smCharInfo.ClassClan != lpCurPlayer->smCharInfo.ClassClan)
			{
				lpChar = lpCurPlayer;
				NearDist = dist;
			}
		}
	}

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].smCharInfo.State == smCHAR_STATE_ENEMY && lpCurChar != &chrOtherPlayer[cnt])
		{//Pvp Clan?
			if (chrOtherPlayer[cnt].smCharInfo.Brood != smCHAR_MONSTER_USER && chrOtherPlayer[cnt].smCharInfo.Life[0] > 0/* &&
				(!chrOtherPlayer[cnt].smCharInfo.ClassClan || chrOtherPlayer[cnt].smCharInfo.ClassClan != lpCurChar->smCharInfo.ClassClan)*/)
			{
				x = (lpCurChar->pX - chrOtherPlayer[cnt].pX) >> FLOATNS;
				y = (lpCurChar->pY - chrOtherPlayer[cnt].pY) >> FLOATNS;
				z = (lpCurChar->pZ - chrOtherPlayer[cnt].pZ) >> FLOATNS;

				dist = x * x + z * z + y * y;

				if (dist < NearDist)
				{
					lpChar = &chrOtherPlayer[cnt];
					NearDist = dist;
				}
			}
		}
	}

	return lpChar;
}


smCHAR *FindEmptyChar()
{
	int cnt;

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (!chrOtherPlayer[cnt].Flag)
			return &chrOtherPlayer[cnt];
	}

	return NULL;
}


int AddChatBuff(char *szMsg, DWORD dwIP)
{
	int ChatCnt = ChatBuffCnt & CHATBUFF_MASK;
	ChatBuff[ChatCnt].dwIP = dwIP;
	strcpy_s(ChatBuff[ChatCnt].szMessage, szMsg);
	ChatBuffCnt++;
	ChatDispCnt = 70 * 10;
	if (ChatScrollPoint)
		ChatScrollPoint++;

	return ChatBuffCnt;
}


int AddChatBuff(char *szMsg)
{
	return AddChatBuff(szMsg, 0);
}



int	ChatBuffFilter(char *szMsg, DWORD dwIP)
{
	int cnt, len, cnt2;
	char	szBuff[256];
	char	szBuff2[64];

	if (dwIP >= 256) return TRUE;

	len = lstrlen(szMsg);

	for (cnt = 0; cnt < len; cnt++)
	{
		if (szMsg[cnt] == '>')
		{
			szBuff[cnt] = 0;
			break;
		}
		else
		{
			szBuff[cnt] = szMsg[cnt];
		}
	}

	if (cnt < len)
	{
		if (lstrcmpi(szBuff, "De") == 0)
		{
			cnt2 = 0;
			szBuff[0] = 0;
			for (cnt = cnt + 1; cnt < len; cnt++)
			{
				if (szMsg[cnt] == ':')
				{
					szBuff[cnt2] = 0;
					break;
				}
				else
				{
					if (szMsg[cnt] != ' ')
						szBuff[cnt2++] = szMsg[cnt];
				}
			}
			if (cnt < len  && szBuff[0])
			{

				for (cnt2 = 0; cnt2 < 15; cnt2++)
				{
					if (InterfaceParty.chat_IDs(2, cnt2, szBuff2) == TRUE)
					{
						if (lstrcmpi(szBuff, szBuff2) == 0)
						{
							wsprintf(szBuff, "** %s %s", szBuff2, mgRefuseWhisper);
							SendChatMessageToServer(szBuff);
							return FALSE;
						}
					}
				}

				InterfaceParty.latest_Insert(szBuff);
			}

			return TRUE;
		}

		if (lstrcmpi(szBuff, "Para") == 0)
		{
			cnt2 = 0;
			szBuff[0] = 0;
			for (cnt = cnt + 1; cnt < len; cnt++)
			{
				if (szMsg[cnt] == ':')
				{
					szBuff[cnt2] = 0;
					break;
				}
				else
				{
					if (szMsg[cnt] != ' ')
						szBuff[cnt2++] = szMsg[cnt];
				}
			}
			if (cnt < len && szBuff[0])
			{
				InterfaceParty.latest_Insert(szBuff);
			}
			return TRUE;
		}
	}





	return TRUE;
}



DWORD	ConvSysTimeToGameTime(DWORD dwTime)
{
	return dwTime / GAME_WORLDTIME_MIN;
}

//DispLoading

#define RECV_DATA_QUE_COUNT		64
#define RECV_DATA_QUE_MASK		63


class	rsTRANS_SERVER
{
	char TransBuff[smSOCKBUFF_SIZE];
	rsRECORD_DBASE *lpRecorder;
	smTHREADSOCK *RecvDataQue[RECV_DATA_QUE_COUNT];
	int	RecvDataQuePush;
	int	RecvDataQuePop;
	TRANS_PLAYPOS TransPlayPosLast;
	int	TransPlayPosCount;

public:
	smWINSOCK *lpsmSock;

	rsTRANS_SERVER();

	int	Init(smWINSOCK *lpsmsock);
	int SendChat(char *szMessage);
	int SendPlayData(smCHAR *lpChar);

	int RecvMessage(smTHREADSOCK *SockInfo);

	int RecvMessageQue();

};

rsTRANS_SERVER::rsTRANS_SERVER()
{
	ZeroMemory(TransBuff, sizeof(TransBuff));
	lpRecorder = nullptr;
	ZeroMemory(RecvDataQue, RECV_DATA_QUE_COUNT * 4);
	RecvDataQuePush = 0;
	RecvDataQuePop = 0;
	TransPlayPosCount = 0;
	lpsmSock = nullptr;
}


int rsTRANS_SERVER::RecvMessageQue()
{
	int cnt;

	if (RecvDataQuePop >= RecvDataQuePush) return TRUE;
	if (MessageLoading) return FALSE;


	EnterCriticalSection(&cSection);

	while (1)
	{
		if (RecvDataQuePop >= RecvDataQuePush) break;

		cnt = RecvDataQuePop & RECV_DATA_QUE_MASK;

		if (RecvDataQue[cnt])
		{
			RecvMessage(RecvDataQue[cnt]);

			delete RecvDataQue[cnt];
			RecvDataQue[cnt] = 0;
		}

		RecvDataQuePop++;
	}


	LeaveCriticalSection(&cSection);

	return TRUE;
}


DWORD	dwGetCharInfoTime = 0;


#ifndef _A
#define _A

#include "AntiCheat\AntiCheat.h"

#endif

extern AntiCheat * pcAntiCheat;

int rsTRANS_SERVER::RecvMessage(smTHREADSOCK *pData)
{
	MECH_INFO *lpMechInfo;
	FIGHTER_INFO *lpFighterInfo;
	PIKE_INFO *lpPikeInfo;
	ARCHER_INFO *lpArcherInfo;
	KINA_INFO *lpKinaInfo;
	ATA_INFO *lpAtaInfo;
	SACER_INFO *lpSacerInfo;
	MAGE_INFO *lpMageInfo;
	ASSASSIN_INFO *lpAssassinInfo;
	SHAMAN_INFO * lpShamanInfo;
	DWORD *IPData;




	int cnt;
	int x, z;
	int ServerCode;


	smCHAR	*lpChar;

	char msg[32] = { 0 };
	int ChatCnt;

	int RcvCnt;


	TRANS_ITEMINFO				*lpTransItemInfo;


	smPLAYDATA					*lpPlayData1;
	smTRANS_COMMAND				TransCommand;
	smTRANS_COMMAND_EX			TransCommandEx;
	smTRANS_COMMAND				*lpTransCommand;
	smTRANS_COMMAND_EX			*lpTransCommandEx;
	smTRANS_ACITON_ITEM			*lpTransActionItem;
	smTRANS_CHAR_COMMAND		*lpTransCharCommand;
	smTRNAS_PLAYERINFO			*lpTransPlayerInfo;
	TRANS_CHATMESSAGE			*lpTransChatMessage;
	TRANS_POST_ITEM				*lpTransPostItem;
	TRANS_PREMIUM_TIME			*lpTransPremiumTime;



	DWORD	dwTime;
	//	DWORD	dwDataKey;
	smCHAR_INFO	*lpCharInfo_MsgBack = 0;
	int		addExp, addMoney;
	//	DWORD	dwEncCode;


	IPData = (DWORD *)(pData->Buff);

	if (MessageLoading)
	{
		switch (IPData[1])
		{

		case OpCode::OPCODE_ATTACKDATA2:
		case OpCode::OPCODE_ATTACKDATA:
		case OpCode::OPCODE_PLAYDATA1:
		case OpCode::OPCODE_PLAYDATA2:
		case OpCode::OPCODE_PLAYDATA3:
		case OpCode::OPCODE_TRANSPLAYDATA:
		case OpCode::OPCODE_PLAYDATAGROUP:
		case OpCode::OPCODE_PLAYITEM:
			return TRUE;
		}


		cnt = RecvDataQuePush - RecvDataQuePop;


		if (cnt >= RECV_DATA_QUE_COUNT) return FALSE;

		cnt = RecvDataQuePush & RECV_DATA_QUE_MASK;

		if (!RecvDataQue[cnt])
		{
			RecvDataQue[cnt] = new smTHREADSOCK;
			if (RecvDataQue[cnt])
			{
				memcpy(RecvDataQue[cnt], pData, sizeof(smTHREADSOCK));
				RecvDataQuePush++;
				return TRUE;
			}
		}
		return FALSE;
	}

	//dwEncCode = (IPData[1] & 0xFFFF0000);
	//if(dwEncCode == OPCODE_ENCODE_PACKET || dwEncCode == OPCODE_ENCODE_PACKET2)
	//{
	//	smTHREADSOCK smEncData;

	//	addExp = 0;
	//	addMoney = 0;

	//	memcpy(&smEncData, pData, sizeof(smTHREADSOCK) - smSOCKBUFF_SIZE);

	//	if(dwEncCode == OPCODE_ENCODE_PACKET2)
	//	{
	//		if(fnDecodePacket)
	//			dwDataKey = fnDecodePacket((BYTE *)pData->Buff, (BYTE *)smEncData.Buff);
	//		else
	//			return FALSE;
	//	}
	//	else
	//		dwDataKey = DecodePacket((BYTE *)pData->Buff, (BYTE *)smEncData.Buff);

	//	if(!dwDataKey)
	//		return FALSE;

	//	cnt = dwDataKey & 0xFFFF;

	//	if(pData->smMySock->CheckEncRecvPacket(cnt) == TRUE)
	//	{

	//		return FALSE;
	//	}

	//	if(cnt < (pData->smMySock->EncPacketRecvCount - ENC_PACKET_REC_MAX))
	//	{

	//		return FALSE;
	//	}
	//	pData->smMySock->PushEncRecvPacket(cnt);


	//	pData = &smEncData;
	//	IPData = (DWORD *)(pData->Buff);

	//	lpCharInfo_MsgBack = new smCHAR_INFO;
	//	if(lpCharInfo_MsgBack)
	//	{
	//		memcpy(lpCharInfo_MsgBack, &lpCurPlayer->smCharInfo, sizeof(smCHAR_INFO));
	//	}
	//}
	//else
	//{
	//	if(IPData[1] == OpCode::OPCODE_PUTITEM || IPData[1] == OpCode::OPCODE_ADDEXP)
	//		return FALSE;

	//}

//#ifdef _DEBUG
//	Log::getInstance()->output(LOG_DEBUG, "Recv %s (%x) %d\r\n", GetTranscodeNameByOpcode(IPData[1]), IPData[1], IPData[0]);
//#endif

	switch (IPData[1])
	{

	case smTRANSCODE_SHAMAN_INFO:
		lpShamanInfo = (SHAMAN_INFO*)pData->Buff;

		memcpy(DarkBolt_Damage, lpShamanInfo->DarkBolt_Damage, sizeof(DarkBolt_Damage));
		memcpy(DarkBolt_UseMana, lpShamanInfo->DarkBolt_UseMana, sizeof(DarkBolt_UseMana));
		memcpy(InnerPeace_Add, lpShamanInfo->InnerPeace_Add, sizeof(InnerPeace_Add));

		memcpy(SoulManacle_Time, lpShamanInfo->SoulManacle_Time, sizeof(SoulManacle_Time));
		memcpy(SoulManacle_UseMana, lpShamanInfo->SoulManacle_UseMana, sizeof(SoulManacle_UseMana));
		memcpy(Haunt_Damage, lpShamanInfo->Haunt_Damage, sizeof(Haunt_Damage));

		memcpy(Haunt_UseMana, lpShamanInfo->Haunt_UseMana, sizeof(Haunt_UseMana));
		memcpy(Scratch_Damage, lpShamanInfo->Scratch_Damage, sizeof(Scratch_Damage));
		memcpy(Scratch_UseMana, lpShamanInfo->Scratch_UseMana, sizeof(Scratch_UseMana));

		memcpy(Judgement_Damage, lpShamanInfo->Judgement_Damage, sizeof(Judgement_Damage));

		memcpy(Judgement_Range, lpShamanInfo->Judgement_Range, sizeof(Judgement_Range));
		memcpy(Judgement_UseMana, lpShamanInfo->Judgement_UseMana, sizeof(Judgement_UseMana));
		memcpy(DarkWave_Damage, lpShamanInfo->DarkWave_Damage, sizeof(DarkWave_Damage));

		memcpy(DarkWave_Area, lpShamanInfo->DarkWave_Area, sizeof(DarkWave_Area));
		memcpy(DarkWave_Range, lpShamanInfo->DarkWave_Range, sizeof(DarkWave_Range));
		memcpy(DarkWave_UseMana, lpShamanInfo->DarkWave_UseMana, sizeof(DarkWave_UseMana));

		memcpy(CurseLazy_SpeedSubPercent, lpShamanInfo->CurseLazy_SpeedSubPercent, sizeof(CurseLazy_SpeedSubPercent));
		memcpy(CurseLazy_DamageSubPercent, lpShamanInfo->CurseLazy_DamageSubPercent, sizeof(CurseLazy_DamageSubPercent));
		memcpy(CurseLazy_Area, lpShamanInfo->CurseLazy_Area, sizeof(CurseLazy_Area));
		memcpy(CurseLazy_Time, lpShamanInfo->CurseLazy_Time, sizeof(CurseLazy_Time));

		memcpy(CurseLazy_UseMana, lpShamanInfo->CurseLazy_UseMana, sizeof(CurseLazy_UseMana));
		memcpy(SpiritualFlare_Damage, lpShamanInfo->SpiritualFlare_Damage, sizeof(SpiritualFlare_Damage));
		memcpy(SpiritualFlare_Area, lpShamanInfo->SpiritualFlare_Area, sizeof(SpiritualFlare_Area));

		memcpy(SpiritualFlare_Range, lpShamanInfo->SpiritualFlare_Range, sizeof(SpiritualFlare_Range));
		memcpy(SpiritualFlare_UseMana, lpShamanInfo->SpiritualFlare_UseMana, sizeof(SpiritualFlare_UseMana));
		memcpy(ChasingHunt_Time, lpShamanInfo->ChasingHunt_Time, sizeof(ChasingHunt_Time));

		memcpy(ChasingHunt_Area, lpShamanInfo->ChasingHunt_Area, sizeof(ChasingHunt_Area));
		memcpy(ChasingHunt_UseMana, lpShamanInfo->ChasingHunt_UseMana, sizeof(ChasingHunt_UseMana));
		memcpy(LandGhost_Damage, lpShamanInfo->LandGhost_Damage, sizeof(LandGhost_Damage));

		memcpy(LandGhost_Range, lpShamanInfo->LandGhost_Range, sizeof(LandGhost_Range));

		memcpy(LandGhost_UseMana, lpShamanInfo->LandGhost_UseMana, sizeof(LandGhost_UseMana));
		memcpy(MourningOfPray_Damage, lpShamanInfo->MourningOfPray_Damage, sizeof(MourningOfPray_Damage));
		memcpy(MourningOfPray_Range, lpShamanInfo->MourningOfPray_Range, sizeof(MourningOfPray_Range));

		memcpy(MourningOfPray_UseMana, lpShamanInfo->MourningOfPray_UseMana, sizeof(MourningOfPray_UseMana));
		memcpy(BloodyKnight_Damage, lpShamanInfo->BloodyKnight_Damage, sizeof(BloodyKnight_Damage));
		memcpy(BloodyKnight_Hit, lpShamanInfo->BloodyKnight_Hit, sizeof(BloodyKnight_Hit));
		memcpy(BloodyKnight_Defense, lpShamanInfo->BloodyKnight_Defense, sizeof(BloodyKnight_Defense));

		memcpy(BloodyKnight_Life, lpShamanInfo->BloodyKnight_Life, sizeof(BloodyKnight_Life));
		memcpy(BloodyKnight_UseMana, lpShamanInfo->BloodyKnight_UseMana, sizeof(BloodyKnight_UseMana));
		memcpy(BloodyKnight_Time, lpShamanInfo->BloodyKnight_Time, sizeof(BloodyKnight_Time));
		memcpy(AdventMigal_AttackRate, lpShamanInfo->AdventMigal_AttackRate, sizeof(AdventMigal_AttackRate));
		memcpy(AdventMigal_UseMana, lpShamanInfo->AdventMigal_UseMana, sizeof(AdventMigal_UseMana));
		memcpy(AdventMigal_Time, lpShamanInfo->AdventMigal_Time, sizeof(AdventMigal_Time));
		memcpy(RainMaker_Absorb, lpShamanInfo->RainMaker_Absorb, sizeof(RainMaker_Absorb));
		memcpy(RainMaker_UseMana, lpShamanInfo->RainMaker_UseMana, sizeof(RainMaker_UseMana));
		memcpy(RainMaker_Time, lpShamanInfo->RainMaker_Time, sizeof(RainMaker_Time));
		memcpy(AdventMidranda_UseMana, lpShamanInfo->AdventMidranda_UseMana, sizeof(AdventMidranda_UseMana));
		memcpy(AdventMidranda_Speed, lpShamanInfo->AdventMidranda_Speed, sizeof(AdventMidranda_Speed));
		memcpy(AdventMidranda_Time, lpShamanInfo->AdventMidranda_Time, sizeof(AdventMidranda_Time));

		cInvenTory.SetItemToChar();


		break;

	case smTRANSCODE_ASSASSIN_INFO:
		lpAssassinInfo = (ASSASSIN_INFO*)pData->Buff;

		memcpy(Stinger_Damage, lpAssassinInfo->Stinger_Damage, sizeof(Stinger_Damage));
		memcpy(Stinger_Damage, lpAssassinInfo->Stinger_Damage, sizeof(Stinger_Damage));
		memcpy(Double_Blow_Damage, lpAssassinInfo->Double_Blow_Damage, sizeof(Double_Blow_Damage));

		memcpy(DoubleBlow_UseMana, lpAssassinInfo->DoubleBlow_UseMana, sizeof(DoubleBlow_UseMana));
		memcpy(D_Mastery_DamagePercent, lpAssassinInfo->D_Mastery_DamagePercent, sizeof(D_Mastery_DamagePercent));
		memcpy(Wisp_UseTime, lpAssassinInfo->Wisp_UseTime, sizeof(Wisp_UseTime));

		memcpy(Wisp_Reduction, lpAssassinInfo->Wisp_Reduction, sizeof(Wisp_Reduction));
		memcpy(Wisp_UseMana, lpAssassinInfo->Wisp_UseMana, sizeof(Wisp_UseMana));
		memcpy(VenomThorn_Time, lpAssassinInfo->VenomThorn_Chance, sizeof(VenomThorn_Chance));

		memcpy(VenomThorn_Damage, lpAssassinInfo->VenomThorn_Damage, sizeof(VenomThorn_Damage));

		memcpy(VenomThorn_UseMana, lpAssassinInfo->VenomThorn_UseMana, sizeof(VenomThorn_UseMana));
		memcpy(Alas_Time, lpAssassinInfo->Alas_Time, sizeof(Alas_Time));
		memcpy(Alas_UseMana, lpAssassinInfo->Alas_UseMana, sizeof(Alas_UseMana));

		memcpy(Alas_EvasionPercent, lpAssassinInfo->Alas_EvasionPercent, sizeof(Alas_EvasionPercent));
		memcpy(SoulChock_Range, lpAssassinInfo->SoulChock_Range, sizeof(SoulChock_Range));
		memcpy(SoulChock_Time, lpAssassinInfo->SoulChock_Time, sizeof(SoulChock_Time));

		memcpy(SoulChock_UseMana, lpAssassinInfo->SoulChock_UseMana, sizeof(SoulChock_UseMana));
		memcpy(A_Mastery_AddPercent, lpAssassinInfo->A_Mastery_AddPercent, sizeof(A_Mastery_AddPercent));
		memcpy(A_Mastery_AddPercent2, lpAssassinInfo->A_Mastery_AddPercent2, sizeof(A_Mastery_AddPercent2));
		memcpy(SoreSword_Damage, lpAssassinInfo->SoreSword_Damage, sizeof(SoreSword_Damage));

		memcpy(SoreSword_UseMana, lpAssassinInfo->SoreSword_UseMana, sizeof(SoreSword_UseMana));
		memcpy(BeatUp_Damage, lpAssassinInfo->BeatUp_Damage, sizeof(BeatUp_Damage));
		memcpy(BeatUp_Area, lpAssassinInfo->BeatUp_Area, sizeof(BeatUp_Area));

		memcpy(BeatUp_UseMana, lpAssassinInfo->BeatUp_UseMana, sizeof(BeatUp_UseMana));

		memcpy(Inpes_Time, lpAssassinInfo->Inpes_Time, sizeof(Inpes_Time));
		memcpy(Inpes_Speed, lpAssassinInfo->Inpes_Speed, sizeof(Inpes_Speed));
		memcpy(Inpes_UseMana, lpAssassinInfo->Inpes_UseMana, sizeof(Inpes_UseMana));

		memcpy(Blind_Time, lpAssassinInfo->Blind_Time, sizeof(Blind_Time));
		memcpy(Blind_Damage, lpAssassinInfo->Blind_Damage, sizeof(Blind_Damage));
		memcpy(Blind_Range, lpAssassinInfo->Blind_Range, sizeof(Blind_Range));

		memcpy(Blind_UseMana, lpAssassinInfo->Blind_UseMana, sizeof(Blind_UseMana));

		memcpy(FrostWind_Damage, lpAssassinInfo->FrostWind_Damage, sizeof(FrostWind_Damage));
		memcpy(FrostWind_UseMana, lpAssassinInfo->FrostWind_UseMana, sizeof(FrostWind_UseMana));
		memcpy(F_Mastery_Critical, lpAssassinInfo->F_Mastery_Critical, sizeof(F_Mastery_Critical));

		memcpy(ViolenceStab_Damage, lpAssassinInfo->ViolenceStab_Damage, sizeof(ViolenceStab_Damage));
		memcpy(ViolenceStab_UseMana, lpAssassinInfo->ViolenceStab_UseMana, sizeof(ViolenceStab_UseMana));

		//memcpy(Polluted_UseMana, lpAssassinInfo->Polluted_UseMana, sizeof(Polluted_UseMana));
		memcpy(PastingShadow_Damage, lpAssassinInfo->PastingShadow_Damage, sizeof(PastingShadow_Damage));
		memcpy(PastingShadow_UseMana, lpAssassinInfo->PastingShadow_UseMana, sizeof(PastingShadow_UseMana));
		cInvenTory.SetItemToChar();

		break;

	case smTRANSCODE_MECH_INFO:
		lpMechInfo = (MECH_INFO*)pData->Buff;

		memcpy(E_Shield_BlockRate, lpMechInfo->E_Shield_BlockRate, sizeof(E_Shield_BlockRate));
		memcpy(E_Shield_UseTime, lpMechInfo->E_Shield_UseTime, sizeof(E_Shield_UseTime));
		memcpy(E_Shield_UseMana, lpMechInfo->E_Shield_UseMana, sizeof(E_Shield_UseMana));

		memcpy(Mechanic_Bomb_Damage, lpMechInfo->Mechanic_Bomb_Damage, sizeof(Mechanic_Bomb_Damage));
		memcpy(Mechanic_Bomb_Attack_Range, lpMechInfo->Mechanic_Bomb_Attack_Range, sizeof(Mechanic_Bomb_Attack_Range));
		memcpy(Mechanic_Bomb_UseMana, lpMechInfo->Mechanic_Bomb_UseMana, sizeof(Mechanic_Bomb_UseMana));

		memcpy(P_Absorb, lpMechInfo->P_Absorb, sizeof(P_Absorb));
		memcpy(P_Absorb_UseTime, lpMechInfo->P_Absorb_UseTime, sizeof(P_Absorb_UseTime));
		memcpy(P_Absor_bUseMana, lpMechInfo->P_Absor_bUseMana, sizeof(P_Absor_bUseMana));

		memcpy(PlusPoison, lpMechInfo->PlusPoison, sizeof(PlusPoison));

		memcpy(G_Smash_Attack_Rate, lpMechInfo->G_Smash_Attack_Rate, sizeof(G_Smash_Attack_Rate));
		memcpy(G_Smash_Attack_Rage, lpMechInfo->G_Smash_Attack_Rage, sizeof(G_Smash_Attack_Rage));
		memcpy(G_Smash_UseMana, lpMechInfo->G_Smash_UseMana, sizeof(G_Smash_UseMana));

		memcpy(Maximize_Damage, lpMechInfo->Maximize_Damage, sizeof(Maximize_Damage));
		memcpy(Maximize_Time, lpMechInfo->Maximize_Time, sizeof(Maximize_Time));
		memcpy(Maximize_UseMana, lpMechInfo->Maximize_UseMana, sizeof(Maximize_UseMana));

		memcpy(Automation_Damage, lpMechInfo->Automation_Damage, sizeof(Automation_Damage));
		memcpy(Automation_Speed, lpMechInfo->Automation_Speed, sizeof(Automation_Speed));
		memcpy(Automation_Time, lpMechInfo->Automation_Time, sizeof(Automation_Time));
		memcpy(Automation_UseMana, lpMechInfo->Automation_UseMana, sizeof(Automation_UseMana));

		memcpy(Spark_Damage, lpMechInfo->Spark_Damage, sizeof(Spark_Damage));
		memcpy(Spark_Area, lpMechInfo->Spark_Area, sizeof(Spark_Area));
		memcpy(Spark_UseMana, lpMechInfo->Spark_UseMana, sizeof(Spark_UseMana));

		memcpy(Metal_Armor_Defense, lpMechInfo->Metal_Armor_Defense, sizeof(Metal_Armor_Defense));
		memcpy(Metal_Armor_Time, lpMechInfo->Metal_Armor_Time, sizeof(Metal_Armor_Time));
		memcpy(Metal_Armor_UseMana, lpMechInfo->Metal_Armor_UseMana, sizeof(Metal_Armor_UseMana));

		memcpy(Grand_Smash_AttackRate, lpMechInfo->Grand_Smash_AttackRate, sizeof(Grand_Smash_AttackRate));
		memcpy(Grand_Smash_Damage, lpMechInfo->Grand_Smash_Damage, sizeof(Grand_Smash_Damage));
		memcpy(Grand_Smash_UseMana, lpMechInfo->Grand_Smash_UseMana, sizeof(Grand_Smash_UseMana));

		memcpy(M_Weapon_Mastey, lpMechInfo->M_Weapon_Mastey, sizeof(M_Weapon_Mastey));

		memcpy(Spark_Shield_Damage, lpMechInfo->Spark_Shield_Damage, sizeof(Spark_Shield_Damage));
		memcpy(Spark_Shield_Defense, lpMechInfo->Spark_Shield_Defense, sizeof(Spark_Shield_Defense));
		memcpy(Spark_Shield_Time, lpMechInfo->Spark_Shield_Time, sizeof(Spark_Shield_Time));
		memcpy(Spark_Shield_UseMana, lpMechInfo->Spark_Shield_UseMana, sizeof(Spark_Shield_UseMana));

		memcpy(Impulsion_LightingDamage, lpMechInfo->Impulsion_LightingDamage, sizeof(Impulsion_LightingDamage));
		memcpy(Impulsion_Range, lpMechInfo->Impulsion_Range, sizeof(Impulsion_Range));
		memcpy(Impulsion_LightingNum, lpMechInfo->Impulsion_LightingNum, sizeof(Impulsion_LightingNum));
		memcpy(Impulsion_UseMana, lpMechInfo->Impulsion_UseMana, sizeof(Impulsion_UseMana));

		memcpy(Compulsion_AddAbsorb, lpMechInfo->Compulsion_AddAbsorb, sizeof(Compulsion_AddAbsorb));
		memcpy(Compulsion_Area, lpMechInfo->Compulsion_Area, sizeof(Compulsion_Area));
		memcpy(Compulsion_Time, lpMechInfo->Compulsion_Time, sizeof(Compulsion_Time));
		memcpy(Compulsion_UseMana, lpMechInfo->Compulsion_UseMana, sizeof(Compulsion_UseMana));

		memcpy(Magnetic_Sphere_AddDamage, lpMechInfo->Magnetic_Sphere_AddDamage, sizeof(Magnetic_Sphere_AddDamage));
		memcpy(Magnetic_Sphere_Area, lpMechInfo->Magnetic_Sphere_Area, sizeof(Magnetic_Sphere_Area));
		memcpy(Magnetic_Sphere_AttackDelay, lpMechInfo->Magnetic_Sphere_AttackDelay, sizeof(Magnetic_Sphere_AttackDelay));
		memcpy(Magnetic_Sphere_Time, lpMechInfo->Magnetic_Sphere_Time, sizeof(Magnetic_Sphere_Time));
		memcpy(Magnetic_Sphere_UseMana, lpMechInfo->Magnetic_Sphere_UseMana, sizeof(Magnetic_Sphere_UseMana));

		memcpy(Metal_Golem_Damage, lpMechInfo->Metal_Golem_Damage, sizeof(Metal_Golem_Damage));
		memcpy(Metal_Golem_Hit, lpMechInfo->Metal_Golem_Hit, sizeof(Metal_Golem_Hit));
		memcpy(Metal_Golem_Defense, lpMechInfo->Metal_Golem_Defense, sizeof(Metal_Golem_Defense));
		memcpy(Metal_Golem_Life, lpMechInfo->Metal_Golem_Life, sizeof(Metal_Golem_Life));
		memcpy(Metal_Golem_UseMana, lpMechInfo->Metal_Golem_UseMana, sizeof(Metal_Golem_UseMana));

		cInvenTory.SetItemToChar();


		break;
	case smTRANSCODE_FIGHTER_INFO:
		lpFighterInfo = (FIGHTER_INFO*)pData->Buff;


		memcpy(Melee_Mastery_DamagePercent, lpFighterInfo->Melee_Mastery_DamagePercent, sizeof(Melee_Mastery_DamagePercent));

		memcpy(PlusFire, lpFighterInfo->PlusFire, sizeof(PlusFire));

		memcpy(Raving_Damage, lpFighterInfo->Raving_Damage, sizeof(Raving_Damage));
		memcpy(Ravind_Speed, lpFighterInfo->Ravind_Speed, sizeof(Ravind_Speed));
		memcpy(Raving_UseLife, lpFighterInfo->Raving_UseLife, sizeof(Raving_UseLife));
		memcpy(Raving_UseMana, lpFighterInfo->Raving_UseMana, sizeof(Raving_UseMana));

		memcpy(Impact_Attack_Rating, lpFighterInfo->Impact_Attack_Rating, sizeof(Impact_Attack_Rating));
		memcpy(Impact_Damage, lpFighterInfo->Impact_Damage, sizeof(Impact_Damage));
		memcpy(Impact_UseMana, lpFighterInfo->Impact_UseMana, sizeof(Impact_UseMana));

		memcpy(T_Impact_Damage, lpFighterInfo->T_Impact_Damage, sizeof(T_Impact_Damage));
		memcpy(T_Impact_Hit, lpFighterInfo->T_Impact_Hit, sizeof(T_Impact_Hit));
		memcpy(T_Impact_UseMana, lpFighterInfo->T_Impact_UseMana, sizeof(T_Impact_UseMana));

		memcpy(B_Swing_Damage, lpFighterInfo->B_Swing_Damage, sizeof(B_Swing_Damage));
		memcpy(B_Swing_Critical, lpFighterInfo->B_Swing_Critical, sizeof(B_Swing_Critical));
		memcpy(B_Swing_UseMana, lpFighterInfo->B_Swing_UseMana, sizeof(B_Swing_UseMana));

		memcpy(Roar_Range, lpFighterInfo->Roar_Range, sizeof(Roar_Range));
		memcpy(Roar_Time, lpFighterInfo->Roar_Time, sizeof(Roar_Time));
		memcpy(Roar_UseMana, lpFighterInfo->Roar_UseMana, sizeof(Roar_UseMana));

		memcpy(R_Zecram_Damage, lpFighterInfo->R_Zecram_Damage, sizeof(R_Zecram_Damage));
		memcpy(R_Zecram_UseMana, lpFighterInfo->R_Zecram_UseMana, sizeof(R_Zecram_UseMana));

		memcpy(Concentration_AttackRate, lpFighterInfo->Concentration_AttackRate, sizeof(Concentration_AttackRate));
		memcpy(Concentration_Time, lpFighterInfo->Concentration_Time, sizeof(Concentration_Time));
		memcpy(Concentration_UseMana, lpFighterInfo->Concentration_UseMana, sizeof(Concentration_UseMana));

		memcpy(A_Crash_Damage, lpFighterInfo->A_Crash_Damage, sizeof(A_Crash_Damage));
		memcpy(A_Crash_AttackRate, lpFighterInfo->A_Crash_AttackRate, sizeof(A_Crash_AttackRate));
		memcpy(A_Crash_UseMana, lpFighterInfo->A_Crash_UseMana, sizeof(A_Crash_UseMana));

		memcpy(Swift_Axe_Speed, lpFighterInfo->Swift_Axe_Speed, sizeof(Swift_Axe_Speed));
		memcpy(Swift_Axe_Time, lpFighterInfo->Swift_Axe_Time, sizeof(Swift_Axe_Time));
		memcpy(Swift_Axe_UseMana, lpFighterInfo->Swift_Axe_UseMana, sizeof(Swift_Axe_UseMana));

		memcpy(B_Crash_Damage, lpFighterInfo->B_Crash_Damage, sizeof(B_Crash_Damage));
		memcpy(B_Crash_DemonDamage, lpFighterInfo->B_Crash_DemonDamage, sizeof(B_Crash_DemonDamage));
		memcpy(B_Crash_UseMana, lpFighterInfo->B_Crash_UseMana, sizeof(B_Crash_UseMana));

		memcpy(Berserker_AddAttack, lpFighterInfo->Berserker_AddAttack, sizeof(Berserker_AddAttack));
		memcpy(Berserker_SubAbsorb, lpFighterInfo->Berserker_SubAbsorb, sizeof(Berserker_SubAbsorb));
		memcpy(Berserker_Time, lpFighterInfo->Berserker_Time, sizeof(Berserker_Time));
		memcpy(Berserker_UseMana, lpFighterInfo->Berserker_UseMana, sizeof(Berserker_UseMana));

		memcpy(Cyclone_Strike_DamagePercent, lpFighterInfo->Cyclone_Strike_DamagePercent, sizeof(Cyclone_Strike_DamagePercent));
		memcpy(Cyclone_Strike_AreaDamage, lpFighterInfo->Cyclone_Strike_AreaDamage, sizeof(Cyclone_Strike_AreaDamage));
		memcpy(Cyclone_Strike_AttackNum, lpFighterInfo->Cyclone_Strike_AttackNum, sizeof(Cyclone_Strike_AttackNum));
		memcpy(Cyclone_Strike_Area, lpFighterInfo->Cyclone_Strike_Area, sizeof(Cyclone_Strike_Area));
		memcpy(Cyclone_Strike_UseMana, lpFighterInfo->Cyclone_Strike_UseMana, sizeof(Cyclone_Strike_UseMana));

		memcpy(Boost_Health_Life, lpFighterInfo->Boost_Health_Life, sizeof(Boost_Health_Life));

		cInvenTory.SetItemToChar();


		break;


	case smTRANSCODE_PIKE_INFO:
		lpPikeInfo = (PIKE_INFO*)pData->Buff;

		memcpy(Pike_Wind_Throw_Height, lpPikeInfo->Pike_Wind_Throw_Height, sizeof(Pike_Wind_Throw_Height));
		memcpy(Pike_Wind_Damage, lpPikeInfo->Pike_Wind_Damage, sizeof(Pike_Wind_Damage));
		memcpy(Pike_Wind_Push_Lenght, lpPikeInfo->Pike_Wind_Push_Lenght, sizeof(Pike_Wind_Push_Lenght));
		memcpy(Pike_Wind_UseMana, lpPikeInfo->Pike_Wind_UseMana, sizeof(Pike_Wind_UseMana));

		memcpy(PlusIce, lpPikeInfo->PlusIce, sizeof(PlusIce));

		memcpy(Critical_Hit_Critical, lpPikeInfo->Critical_Hit_Critical, sizeof(Critical_Hit_Critical));
		memcpy(Critical_Hit_UseMana, lpPikeInfo->Critical_Hit_UseMana, sizeof(Critical_Hit_UseMana));

		memcpy(Jumping_Crash_UseMana, lpPikeInfo->Jumping_Crash_UseMana, sizeof(Jumping_Crash_UseMana));
		memcpy(Jumping_Crash_Attack_Rating, lpPikeInfo->Jumping_Crash_Attack_Rating, sizeof(Jumping_Crash_Attack_Rating));
		memcpy(Jumping_Crash_Damage, lpPikeInfo->Jumping_Crash_Damage, sizeof(Jumping_Crash_Damage));

		memcpy(G_Pike_Damage, lpPikeInfo->G_Pike_Damage, sizeof(G_Pike_Damage));
		memcpy(G_Pike_Range, lpPikeInfo->G_Pike_Range, sizeof(G_Pike_Range));
		memcpy(G_Pike_UseMana, lpPikeInfo->G_Pike_UseMana, sizeof(G_Pike_UseMana));
		memcpy(G_Pike_Time, lpPikeInfo->G_Pike_Time, sizeof(G_Pike_Time));

		memcpy(Tornado_Damage, lpPikeInfo->Tornado_Damage, sizeof(Tornado_Damage));
		memcpy(Tornado_Stun, lpPikeInfo->Tornado_Stun, sizeof(Tornado_Stun));
		memcpy(Tornado_Range, lpPikeInfo->Tornado_Range, sizeof(Tornado_Range));
		memcpy(Tornado_UseMana, lpPikeInfo->Tornado_UseMana, sizeof(Tornado_UseMana));

		memcpy(W_D_Mastery_Block, lpPikeInfo->W_D_Mastery_Block, sizeof(W_D_Mastery_Block));

		memcpy(Expansion_Size, lpPikeInfo->Expansion_Size, sizeof(Expansion_Size));
		memcpy(Expansion_Damage, lpPikeInfo->Expansion_Damage, sizeof(Expansion_Damage));
		memcpy(Expansion_UseMana, lpPikeInfo->Expansion_UseMana, sizeof(Expansion_UseMana));

		memcpy(VenomSpear_Damage, lpPikeInfo->VenomSpear_Damage, sizeof(VenomSpear_Damage));
		memcpy(VenomSpear_Num, lpPikeInfo->VenomSpear_Num, sizeof(VenomSpear_Num));
		memcpy(VenomSpear_Time, lpPikeInfo->VenomSpear_Time, sizeof(VenomSpear_Time));
		memcpy(VenomSpear_Range, lpPikeInfo->VenomSpear_Range, sizeof(VenomSpear_Range));
		memcpy(VenomSpear_UseMana, lpPikeInfo->VenomSpear_UseMana, sizeof(VenomSpear_UseMana));

		memcpy(Vanish_Speed, lpPikeInfo->Vanish_Speed, sizeof(Vanish_Speed));
		memcpy(Vanish_Damage, lpPikeInfo->Vanish_Damage, sizeof(Vanish_Damage));
		memcpy(Vanish_Range, lpPikeInfo->Vanish_Range, sizeof(Vanish_Range));
		memcpy(Vanish_Time, lpPikeInfo->Vanish_Time, sizeof(Vanish_Time));
		memcpy(Vanish_UseMana, lpPikeInfo->Vanish_UseMana, sizeof(Vanish_UseMana));

		memcpy(Critical_Mastery_Critical, lpPikeInfo->Critical_Mastery_Critical, sizeof(Critical_Mastery_Critical));

		memcpy(Chain_Lance_Damage, lpPikeInfo->Chain_Lance_Damage, sizeof(Chain_Lance_Damage));
		memcpy(Chain_Lance_UseMana, lpPikeInfo->Chain_Lance_UseMana, sizeof(Chain_Lance_UseMana));

		memcpy(Assassin_Eye_AddCritical, lpPikeInfo->Assassin_Eye_AddCritical, sizeof(Assassin_Eye_AddCritical));
		memcpy(Assassin_Eye_M_SubCritical, lpPikeInfo->Assassin_Eye_M_SubCritical, sizeof(Assassin_Eye_M_SubCritical));
		memcpy(Assassin_Eye_Time, lpPikeInfo->Assassin_Eye_Time, sizeof(Assassin_Eye_Time));
		memcpy(Assassin_Eye_UseMana, lpPikeInfo->Assassin_Eye_UseMana, sizeof(Assassin_Eye_UseMana));

		memcpy(Charging_Strike_DamagePercent, lpPikeInfo->Charging_Strike_DamagePercent, sizeof(Charging_Strike_DamagePercent));
		memcpy(Charging_Strike_CharingDamagePercent, lpPikeInfo->Charging_Strike_CharingDamagePercent, sizeof(Charging_Strike_CharingDamagePercent));
		memcpy(Charging_Strike_Time, lpPikeInfo->Charging_Strike_Time, sizeof(Charging_Strike_Time));
		memcpy(Charging_Strike_UseMana, lpPikeInfo->Charging_Strike_UseMana, sizeof(Charging_Strike_UseMana));

		memcpy(Vague_EvasionPercent, lpPikeInfo->Vague_EvasionPercent, sizeof(Vague_EvasionPercent));
		memcpy(Vague_Time, lpPikeInfo->Vague_Time, sizeof(Vague_Time));
		memcpy(Vague_UseMana, lpPikeInfo->Vague_UseMana, sizeof(Vague_UseMana));

		memcpy(Shadow_Master_DamagePercent, lpPikeInfo->Shadow_Master_DamagePercent, sizeof(Shadow_Master_DamagePercent));
		memcpy(Shadow_Master_AddHit, lpPikeInfo->Shadow_Master_AddHit, sizeof(Shadow_Master_AddHit));
		memcpy(Shadow_Master_ShadowNum, lpPikeInfo->Shadow_Master_ShadowNum, sizeof(Shadow_Master_ShadowNum));
		memcpy(Shadow_Master_UseMana, lpPikeInfo->Shadow_Master_UseMana, sizeof(Shadow_Master_UseMana));

		cInvenTory.SetItemToChar();

		break;


	case smTRANSCODE_ARCHER_INFO:
		lpArcherInfo = (ARCHER_INFO*)pData->Buff;

		memcpy(Scout_Hawk_Attack_Rate, lpArcherInfo->Scout_Hawk_Attack_Rate, sizeof(Scout_Hawk_Attack_Rate));
		memcpy(Scout_Hawk_UseTime, lpArcherInfo->Scout_Hawk_UseTime, sizeof(Scout_Hawk_UseTime));
		memcpy(Scout_Hawk_UseMana, lpArcherInfo->Scout_Hawk_UseMana, sizeof(Scout_Hawk_UseMana));

		memcpy(S_Mastery_DamagePercent, lpArcherInfo->S_Mastery_DamagePercent, sizeof(S_Mastery_DamagePercent));

		memcpy(Wind_Arrow_Speed, lpArcherInfo->Wind_Arrow_Speed, sizeof(Wind_Arrow_Speed));
		memcpy(Wind_Arrow_Damage, lpArcherInfo->Wind_Arrow_Damage, sizeof(Wind_Arrow_Damage));
		memcpy(Wind_Arrow_UseMana, lpArcherInfo->Wind_Arrow_UseMana, sizeof(Wind_Arrow_UseMana));

		memcpy(Perfect_Aim_Attack_Rate, lpArcherInfo->Perfect_Aim_Attack_Rate, sizeof(Perfect_Aim_Attack_Rate));
		memcpy(Perfect_Aim_Damage, lpArcherInfo->Perfect_Aim_Damage, sizeof(Perfect_Aim_Damage));
		memcpy(Perfect_Aim_Damage_LV, lpArcherInfo->Perfect_Aim_Damage_LV, sizeof(Perfect_Aim_Damage_LV));
		memcpy(Perfect_Aim_UseMana, lpArcherInfo->Perfect_Aim_UseMana, sizeof(Perfect_Aim_UseMana));

		memcpy(D_Eye_Attack_Rate, lpArcherInfo->D_Eye_Attack_Rate, sizeof(D_Eye_Attack_Rate));

		memcpy(Falcon_Damage, lpArcherInfo->Falcon_Damage, sizeof(Falcon_Damage));
		memcpy(Falcon_Time, lpArcherInfo->Falcon_Time, sizeof(Falcon_Time));
		memcpy(Falcon_UseMana, lpArcherInfo->Falcon_UseMana, sizeof(Falcon_UseMana));

		memcpy(A_Rage_ArrowNum, lpArcherInfo->A_Rage_ArrowNum, sizeof(A_Rage_ArrowNum));
		memcpy(A_Rage_Damage, lpArcherInfo->A_Rage_Damage, sizeof(A_Rage_Damage));
		memcpy(A_Rage_Area, lpArcherInfo->A_Rage_Area, sizeof(A_Rage_Area));
		memcpy(A_Rage_UseMana, lpArcherInfo->A_Rage_UseMana, sizeof(A_Rage_UseMana));

		memcpy(Avalanche_Speed, lpArcherInfo->Avalanche_Speed, sizeof(Avalanche_Speed));
		memcpy(Avalanche_Damage, lpArcherInfo->Avalanche_Damage, sizeof(Avalanche_Damage));
		memcpy(Avalanche_ArrowNum, lpArcherInfo->Avalanche_ArrowNum, sizeof(Avalanche_ArrowNum));
		memcpy(Avalanche_UseMana, lpArcherInfo->Avalanche_UseMana, sizeof(Avalanche_UseMana));

		memcpy(Elemental_Shot_Ice, lpArcherInfo->Elemental_Shot_Ice, sizeof(Elemental_Shot_Ice));
		memcpy(Elemental_Shot_Fire, lpArcherInfo->Elemental_Shot_Fire, sizeof(Elemental_Shot_Fire));
		memcpy(Elemental_Shot_Lightning, lpArcherInfo->Elemental_Shot_Lightning, sizeof(Elemental_Shot_Lightning));
		memcpy(Elemental_Shot_UseMana, lpArcherInfo->Elemental_Shot_UseMana, sizeof(Elemental_Shot_UseMana));

		memcpy(Golden_Falcon_Damage, lpArcherInfo->Golden_Falcon_Damage, sizeof(Golden_Falcon_Damage));
		memcpy(Golden_Falcon_LifeRegen, lpArcherInfo->Golden_Falcon_LifeRegen, sizeof(Golden_Falcon_LifeRegen));
		memcpy(Golden_Falcon_Time, lpArcherInfo->Golden_Falcon_Time, sizeof(Golden_Falcon_Time));
		memcpy(Golden_Falcon_UseMana, lpArcherInfo->Golden_Falcon_UseMana, sizeof(Golden_Falcon_UseMana));

		memcpy(BombShot_Damage, lpArcherInfo->BombShot_Damage, sizeof(BombShot_Damage));
		memcpy(BombShot_DemonDamage, lpArcherInfo->BombShot_DemonDamage, sizeof(BombShot_DemonDamage));
		memcpy(BombShot_AddDamage, lpArcherInfo->BombShot_AddDamage, sizeof(BombShot_AddDamage));
		memcpy(BombShot_Area, lpArcherInfo->BombShot_Area, sizeof(BombShot_Area));
		memcpy(BombShot_UseMana, lpArcherInfo->BombShot_UseMana, sizeof(BombShot_UseMana));

		memcpy(Perforation_Damage, lpArcherInfo->Perforation_Damage, sizeof(Perforation_Damage));
		memcpy(Perforation_Critical, lpArcherInfo->Perforation_Critical, sizeof(Perforation_Critical));
		memcpy(Perforation_UseMana, lpArcherInfo->Perforation_UseMana, sizeof(Perforation_UseMana));
		memcpy(Perforation_Attack_Range, lpArcherInfo->Perforation_Attack_Range, sizeof(Perforation_Attack_Range));

		memcpy(Recall_Wolverin_Damage, lpArcherInfo->Recall_Wolverin_Damage, sizeof(Recall_Wolverin_Damage));
		memcpy(Recall_Wolverin_Hit, lpArcherInfo->Recall_Wolverin_Hit, sizeof(Recall_Wolverin_Hit));
		memcpy(Recall_Wolverin_Defense, lpArcherInfo->Recall_Wolverin_Defense, sizeof(Recall_Wolverin_Defense));
		memcpy(Recall_Wolverin_Life, lpArcherInfo->Recall_Wolverin_Life, sizeof(Recall_Wolverin_Life));
		memcpy(Recall_Wolverin_UseMana, lpArcherInfo->Recall_Wolverin_UseMana, sizeof(Recall_Wolverin_UseMana));

		memcpy(Evasion_Mastery_AddPercent, lpArcherInfo->Evasion_Mastery_AddPercent, sizeof(Evasion_Mastery_AddPercent));

		memcpy(Phoenix_Shot_DamagePercent, lpArcherInfo->Phoenix_Shot_DamagePercent, sizeof(Phoenix_Shot_DamagePercent));
		memcpy(Phoenix_Shot_Time, lpArcherInfo->Phoenix_Shot_Time, sizeof(Phoenix_Shot_Time));
		memcpy(Phoenix_Shot_UseMana, lpArcherInfo->Phoenix_Shot_UseMana, sizeof(Phoenix_Shot_UseMana));

		memcpy(Force_Of_Nature_AddDamage, lpArcherInfo->Force_Of_Nature_AddDamage, sizeof(Force_Of_Nature_AddDamage));
		memcpy(Force_Of_Nature_AddHit, lpArcherInfo->Force_Of_Nature_AddHit, sizeof(Force_Of_Nature_AddHit));
		memcpy(Force_Of_Nature_FalconAddDamage, lpArcherInfo->Force_Of_Nature_FalconAddDamage, sizeof(Force_Of_Nature_FalconAddDamage));
		memcpy(Force_Of_Nature_Time, lpArcherInfo->Force_Of_Nature_Time, sizeof(Force_Of_Nature_Time));
		memcpy(Force_Of_Nature_UseMana, lpArcherInfo->Force_Of_Nature_UseMana, sizeof(Force_Of_Nature_UseMana));

		cInvenTory.SetItemToChar();

		break;


	case smTRANSCODE_KINA_INFO:
		lpKinaInfo = (KINA_INFO*)pData->Buff;

		memcpy(Sword_Blast_UseMana, lpKinaInfo->Sword_Blast_UseMana, sizeof(Sword_Blast_UseMana));
		memcpy(Sword_Blast_Damage, lpKinaInfo->Sword_Blast_Damage, sizeof(Sword_Blast_Damage));
		memcpy(Sword_Blast_ShootingRange, lpKinaInfo->Sword_Blast_ShootingRange, sizeof(Sword_Blast_ShootingRange));

		memcpy(HolyBody_UseMana, lpKinaInfo->HolyBody_UseMana, sizeof(HolyBody_UseMana));
		memcpy(HolyBody_Absorb, lpKinaInfo->HolyBody_Absorb, sizeof(HolyBody_Absorb));
		memcpy(HolyBody_Time, lpKinaInfo->HolyBody_Time, sizeof(HolyBody_Time));

		memcpy(P_Traning_Stamina, lpKinaInfo->P_Traning_Stamina, sizeof(P_Traning_Stamina));

		memcpy(D_Crash_UseMana, lpKinaInfo->D_Crash_UseMana, sizeof(D_Crash_UseMana));
		memcpy(D_Crash_Damage, lpKinaInfo->D_Crash_Damage, sizeof(D_Crash_Damage));
		memcpy(D_Crash_Critical, lpKinaInfo->D_Crash_Critical, sizeof(D_Crash_Critical));

		memcpy(Holy_Valor_Damage, lpKinaInfo->Holy_Valor_Damage, sizeof(Holy_Valor_Damage));
		memcpy(Holy_Valor_Time, lpKinaInfo->Holy_Valor_Time, sizeof(Holy_Valor_Time));
		memcpy(Holy_Valor_Mana, lpKinaInfo->Holy_Valor_Mana, sizeof(Holy_Valor_Mana));

		memcpy(Brandish_Range, lpKinaInfo->Brandish_Range, sizeof(Brandish_Range));
		memcpy(Brandish_Damage, lpKinaInfo->Brandish_Damage, sizeof(Brandish_Damage));
		memcpy(Brandish_Mana, lpKinaInfo->Brandish_Mana, sizeof(Brandish_Mana));

		memcpy(Piercing_Damage, lpKinaInfo->Piercing_Damage, sizeof(Piercing_Damage));
		memcpy(Piercing_Attack_Rating, lpKinaInfo->Piercing_Attack_Rating, sizeof(Piercing_Attack_Rating));
		memcpy(Piercing_Mana, lpKinaInfo->Piercing_Mana, sizeof(Piercing_Mana));

		memcpy(Drastic_Spirit_Defense, lpKinaInfo->Drastic_Spirit_Defense, sizeof(Drastic_Spirit_Defense));
		memcpy(Drastic_Spirit_Time, lpKinaInfo->Drastic_Spirit_Time, sizeof(Drastic_Spirit_Time));
		memcpy(Drastic_Spirit_Mana, lpKinaInfo->Drastic_Spirit_Mana, sizeof(Drastic_Spirit_Mana));

		memcpy(Sword_Mastery_DamagePercent, lpKinaInfo->Sword_Mastery_DamagePercent, sizeof(Sword_Mastery_DamagePercent));

		memcpy(D_Inhalation_Life, lpKinaInfo->D_Inhalation_Life, sizeof(D_Inhalation_Life));
		memcpy(D_Inhalation_Block, lpKinaInfo->D_Inhalation_Block, sizeof(D_Inhalation_Block));
		memcpy(D_Inhalation_Time, lpKinaInfo->D_Inhalation_Time, sizeof(D_Inhalation_Time));
		memcpy(D_Inhalation_UseMana, lpKinaInfo->D_Inhalation_UseMana, sizeof(D_Inhalation_UseMana));

		memcpy(H_Incantation_Success, lpKinaInfo->H_Incantation_Success, sizeof(H_Incantation_Success));
		memcpy(H_Incantation_AddLife, lpKinaInfo->H_Incantation_AddLife, sizeof(H_Incantation_AddLife));
		memcpy(H_Incantation_Time, lpKinaInfo->H_Incantation_Time, sizeof(H_Incantation_Time));
		memcpy(H_Incantation_UseMana, lpKinaInfo->H_Incantation_UseMana, sizeof(H_Incantation_UseMana));

		memcpy(Grand_Cross_Damage, lpKinaInfo->Grand_Cross_Damage, sizeof(Grand_Cross_Damage));
		memcpy(Grand_Cross_AttackRate, lpKinaInfo->Grand_Cross_AttackRate, sizeof(Grand_Cross_AttackRate));
		memcpy(Grand_Cross_UndeadDamage, lpKinaInfo->Grand_Cross_UndeadDamage, sizeof(Grand_Cross_UndeadDamage));
		memcpy(Grand_Cross_UseMana, lpKinaInfo->Grand_Cross_UseMana, sizeof(Grand_Cross_UseMana));

		memcpy(Godly_Shield_AbsorbPercent, lpKinaInfo->Godly_Shield_AbsorbPercent, sizeof(Godly_Shield_AbsorbPercent));
		memcpy(Godly_Shield_Time, lpKinaInfo->Godly_Shield_Time, sizeof(Godly_Shield_Time));
		memcpy(Godly_Shield_UseMana, lpKinaInfo->Godly_Shield_UseMana, sizeof(Godly_Shield_UseMana));

		memcpy(God_Bless_AddDamage, lpKinaInfo->God_Bless_AddDamage, sizeof(God_Bless_AddDamage));
		memcpy(God_Bless_Time, lpKinaInfo->God_Bless_Time, sizeof(God_Bless_Time));
		memcpy(God_Bless_UseMana, lpKinaInfo->God_Bless_UseMana, sizeof(God_Bless_UseMana));

		memcpy(Sword_Of_Justice_DamagePercent, lpKinaInfo->Sword_Of_Justice_DamagePercent, sizeof(Sword_Of_Justice_DamagePercent));
		memcpy(Sword_Of_Justice_Area, lpKinaInfo->Sword_Of_Justice_Area, sizeof(Sword_Of_Justice_Area));
		memcpy(Sword_Of_Justice_UseMana, lpKinaInfo->Sword_Of_Justice_UseMana, sizeof(Sword_Of_Justice_UseMana));

		memcpy(Divine_Piercing_DamagePercent, lpKinaInfo->Divine_Piercing_DamagePercent, sizeof(Divine_Piercing_DamagePercent));
		memcpy(Divine_Piercing_AddHit, lpKinaInfo->Divine_Piercing_AddHit, sizeof(Divine_Piercing_AddHit));
		memcpy(Divine_Piercing_AttackNum, lpKinaInfo->Divine_Piercing_AttackNum, sizeof(Divine_Piercing_AttackNum));
		memcpy(Divine_Piercing_UseMana, lpKinaInfo->Divine_Piercing_UseMana, sizeof(Divine_Piercing_UseMana));

		// TIER 5

		memcpy(Soul_Breaker_DamagePercent, lpKinaInfo->Soul_Breaker_DamagePercent, sizeof(Soul_Breaker_DamagePercent));
		memcpy(Soul_Breaker_AttackRate, lpKinaInfo->Soul_Breaker_AttackRate, sizeof(Soul_Breaker_AttackRate));
		memcpy(Soul_Breaker_UseMana, lpKinaInfo->Soul_Breaker_UseMana, sizeof(Soul_Breaker_UseMana));

		cInvenTory.SetItemToChar();


		break;


	case smTRANSCODE_ATA_INFO:
		lpAtaInfo = (ATA_INFO*)pData->Buff;

		memcpy(S_Strike_UseMana, lpAtaInfo->S_Strike_UseMana, sizeof(S_Strike_UseMana));
		memcpy(S_Strike_Damage, lpAtaInfo->S_Strike_Damage, sizeof(S_Strike_Damage));

		memcpy(Farina_UseMana, lpAtaInfo->Farina_UseMana, sizeof(Farina_UseMana));
		memcpy(Farina_Speed, lpAtaInfo->Farina_Speed, sizeof(Farina_Speed));
		memcpy(Farina_AttackRate, lpAtaInfo->Farina_AttackRate, sizeof(Farina_AttackRate));

		memcpy(T_Mastery_Damage, lpAtaInfo->T_Mastery_Damage, sizeof(T_Mastery_Damage));

		memcpy(V_Spear_UseMana, lpAtaInfo->V_Spear_UseMana, sizeof(V_Spear_UseMana));
		memcpy(V_Spear_Damage, lpAtaInfo->V_Spear_Damage, sizeof(V_Spear_Damage));

		memcpy(Windy_Attack_Rating, lpAtaInfo->Windy_Attack_Rating, sizeof(Windy_Attack_Rating));
		memcpy(Windy_Time, lpAtaInfo->Windy_Time, sizeof(Windy_Time));
		memcpy(Windy_Mana, lpAtaInfo->Windy_Mana, sizeof(Windy_Mana));

		memcpy(Twist_Javelin_Damage, lpAtaInfo->Twist_Javelin_Damage, sizeof(Twist_Javelin_Damage));
		memcpy(Twist_Javelin_Attack_Rating, lpAtaInfo->Twist_Javelin_Attack_Rating, sizeof(Twist_Javelin_Attack_Rating));
		memcpy(Twist_Javelin_Mana, lpAtaInfo->Twist_Javelin_Mana, sizeof(Twist_Javelin_Mana));

		memcpy(Soul_Sucker_Absorb, lpAtaInfo->Soul_Sucker_Absorb, sizeof(Soul_Sucker_Absorb));
		memcpy(Soul_Sucker_Mana, lpAtaInfo->Soul_Sucker_Mana, sizeof(Soul_Sucker_Mana));

		memcpy(Fire_Javelin_Damage, lpAtaInfo->Fire_Javelin_Damage, sizeof(Fire_Javelin_Damage));
		memcpy(Fire_Javelin_Mana, lpAtaInfo->Fire_Javelin_Mana, sizeof(Fire_Javelin_Mana));

		memcpy(Split_Javelin_AttackNum, lpAtaInfo->Split_Javelin_AttackNum, sizeof(Split_Javelin_AttackNum));
		memcpy(Split_Javelin_Damage, lpAtaInfo->Split_Javelin_Damage, sizeof(Split_Javelin_Damage));
		memcpy(Split_Javelin_AttackRate, lpAtaInfo->Split_Javelin_AttackRate, sizeof(Split_Javelin_AttackRate));
		memcpy(Split_Javelin_UseMana, lpAtaInfo->Split_Javelin_UseMana, sizeof(Split_Javelin_UseMana));

		memcpy(T_Of_Valhalla_Damage, lpAtaInfo->T_Of_Valhalla_Damage, sizeof(T_Of_Valhalla_Damage));
		memcpy(T_Of_Valhalla_Time, lpAtaInfo->T_Of_Valhalla_Time, sizeof(T_Of_Valhalla_Time));
		memcpy(T_Of_Valhalla_UseMana, lpAtaInfo->T_Of_Valhalla_UseMana, sizeof(T_Of_Valhalla_UseMana));

		memcpy(Lightning_Javelin_Damage, lpAtaInfo->Lightning_Javelin_Damage, sizeof(Lightning_Javelin_Damage));
		memcpy(Lightning_Javelin_UseMana, lpAtaInfo->Lightning_Javelin_UseMana, sizeof(Lightning_Javelin_UseMana));

		memcpy(Storm_Javelin_Damage, lpAtaInfo->Storm_Javelin_Damage, sizeof(Storm_Javelin_Damage));
		memcpy(Storm_Javelin_UseMana, lpAtaInfo->Storm_Javelin_UseMana, sizeof(Storm_Javelin_UseMana));

		memcpy(Hall_Of_Valhalla_AddEvation, lpAtaInfo->Hall_Of_Valhalla_AddEvation, sizeof(Hall_Of_Valhalla_AddEvation));
		memcpy(Hall_Of_Valhalla_Time, lpAtaInfo->Hall_Of_Valhalla_Time, sizeof(Hall_Of_Valhalla_Time));
		memcpy(Hall_Of_Valhalla_UseMana, lpAtaInfo->Hall_Of_Valhalla_UseMana, sizeof(Hall_Of_Valhalla_UseMana));

		memcpy(X_Rage_DamagePercent, lpAtaInfo->X_Rage_DamagePercent, sizeof(X_Rage_DamagePercent));
		memcpy(X_Rage_Area, lpAtaInfo->X_Rage_Area, sizeof(X_Rage_Area));
		memcpy(X_Rage_UseMana, lpAtaInfo->X_Rage_UseMana, sizeof(X_Rage_UseMana));

		memcpy(Frost_Javelin_IceAddDamage, lpAtaInfo->Frost_Javelin_IceAddDamage, sizeof(Frost_Javelin_IceAddDamage));
		memcpy(Frost_Javelin_SpeedSubPercent, lpAtaInfo->Frost_Javelin_SpeedSubPercent, sizeof(Frost_Javelin_SpeedSubPercent));
		memcpy(Frost_Javelin_IceTime, lpAtaInfo->Frost_Javelin_IceTime, sizeof(Frost_Javelin_IceTime));
		memcpy(Frost_Javelin_Time, lpAtaInfo->Frost_Javelin_Time, sizeof(Frost_Javelin_Time));
		memcpy(Frost_Javelin_UseMana, lpAtaInfo->Frost_Javelin_UseMana, sizeof(Frost_Javelin_UseMana));

		memcpy(Vengeance_DamagePercent, lpAtaInfo->Vengeance_DamagePercent, sizeof(Vengeance_DamagePercent));
		memcpy(Vengeance_Range, lpAtaInfo->Vengeance_Range, sizeof(Vengeance_Range));
		memcpy(Vengeance_UseMana, lpAtaInfo->Vengeance_UseMana, sizeof(Vengeance_UseMana));
		memcpy(Vengeance_AddCritical, lpAtaInfo->Vengeance_AddCritical, sizeof(Vengeance_AddCritical));

		cInvenTory.SetItemToChar();


		break;


	case smTRANSCODE_SACER_INFO:
		lpSacerInfo = (SACER_INFO*)pData->Buff;

		memcpy(Healing_UseMana, lpSacerInfo->Healing_UseMana, sizeof(Healing_UseMana));
		memcpy(Healing_Heal, lpSacerInfo->Healing_Heal, sizeof(Healing_Heal));

		memcpy(HolyBolt_UseMana, lpSacerInfo->HolyBolt_UseMana, sizeof(HolyBolt_UseMana));
		memcpy(HolyBolt_Damage, lpSacerInfo->HolyBolt_Damage, sizeof(HolyBolt_Damage));

		memcpy(M_Spark_UseMana, lpSacerInfo->M_Spark_UseMana, sizeof(M_Spark_UseMana));
		memcpy(M_Spark_Damage, lpSacerInfo->M_Spark_Damage, sizeof(M_Spark_Damage));
		memcpy(M_Spark_Num, lpSacerInfo->M_Spark_Num, sizeof(M_Spark_Num));

		memcpy(HolyMind_UseMana, lpSacerInfo->HolyMind_UseMana, sizeof(HolyMind_UseMana));
		memcpy(HolyMind_DecDamage, lpSacerInfo->HolyMind_DecDamage, sizeof(HolyMind_DecDamage));
		memcpy(HolyMind_Time, lpSacerInfo->HolyMind_Time, sizeof(HolyMind_Time));

		memcpy(Meditation_Regen, lpSacerInfo->Meditation_Regen, sizeof(Meditation_Regen));

		memcpy(Divine_Lightning_Damage, lpSacerInfo->Divine_Lightning_Damage, sizeof(Divine_Lightning_Damage));
		memcpy(Divine_Lightning_Num, lpSacerInfo->Divine_Lightning_Num, sizeof(Divine_Lightning_Num));
		memcpy(Divine_Lightning_Mana, lpSacerInfo->Divine_Lightning_Mana, sizeof(Divine_Lightning_Mana));

		memcpy(Holy_Reflection_Return_Damage, lpSacerInfo->Holy_Reflection_Return_Damage, sizeof(Holy_Reflection_Return_Damage));
		memcpy(Holy_Reflection_Time, lpSacerInfo->Holy_Reflection_Time, sizeof(Holy_Reflection_Time));
		memcpy(Holy_Reflection_Mana, lpSacerInfo->Holy_Reflection_Mana, sizeof(Holy_Reflection_Mana));

		memcpy(Grand_Healing, lpSacerInfo->Grand_Healing, sizeof(Grand_Healing));
		memcpy(Grand_Healing_Range, lpSacerInfo->Grand_Healing_Range, sizeof(Grand_Healing_Range));
		memcpy(Grand_Healing_Mana, lpSacerInfo->Grand_Healing_Mana, sizeof(Grand_Healing_Mana));

		memcpy(Vigor_Ball_Damage, lpSacerInfo->Vigor_Ball_Damage, sizeof(Vigor_Ball_Damage));
		memcpy(Vigor_Ball_UseMana, lpSacerInfo->Vigor_Ball_UseMana, sizeof(Vigor_Ball_UseMana));

		memcpy(Resurrection_Percent, lpSacerInfo->Resurrection_Percent, sizeof(Resurrection_Percent));
		memcpy(Resurrection_Exp, lpSacerInfo->Resurrection_Exp, sizeof(Resurrection_Exp));
		memcpy(Resurrection_UseMana, lpSacerInfo->Resurrection_UseMana, sizeof(Resurrection_UseMana));

		memcpy(Extinction_Percent, lpSacerInfo->Extinction_Percent, sizeof(Extinction_Percent));
		memcpy(Extinction_Amount, lpSacerInfo->Extinction_Amount, sizeof(Extinction_Amount));
		memcpy(Extinction_UseMana, lpSacerInfo->Extinction_UseMana, sizeof(Extinction_UseMana));

		memcpy(Virtual_Life_Percent, lpSacerInfo->Virtual_Life_Percent, sizeof(Virtual_Life_Percent));
		memcpy(Virtual_Life_Time, lpSacerInfo->Virtual_Life_Time, sizeof(Virtual_Life_Time));
		memcpy(Virtual_Life_UseMana, lpSacerInfo->Virtual_Life_UseMana, sizeof(Virtual_Life_UseMana));

		memcpy(Glacial_Spike_Damage, lpSacerInfo->Glacial_Spike_Damage, sizeof(Glacial_Spike_Damage));
		memcpy(Glacial_Spike_Area, lpSacerInfo->Glacial_Spike_Area, sizeof(Glacial_Spike_Area));
		memcpy(Glacial_Spike_UseMana, lpSacerInfo->Glacial_Spike_UseMana, sizeof(Glacial_Spike_UseMana));

		memcpy(Regeneration_Field_LifeRegen, lpSacerInfo->Regeneration_Field_LifeRegen, sizeof(Regeneration_Field_LifeRegen));
		memcpy(Regeneration_Field_ManaRegen, lpSacerInfo->Regeneration_Field_ManaRegen, sizeof(Regeneration_Field_ManaRegen));
		memcpy(Regeneration_Field_Time, lpSacerInfo->Regeneration_Field_Time, sizeof(Regeneration_Field_Time));
		memcpy(Regeneration_Field_Area, lpSacerInfo->Regeneration_Field_Area, sizeof(Regeneration_Field_Area));
		memcpy(Regeneration_Field_UseMana, lpSacerInfo->Regeneration_Field_UseMana, sizeof(Regeneration_Field_UseMana));

		memcpy(Chain_Lightning_Damage, lpSacerInfo->Chain_Lightning_Damage, sizeof(Chain_Lightning_Damage));
		memcpy(Chain_Lightning_Num, lpSacerInfo->Chain_Lightning_Num, sizeof(Chain_Lightning_Num));
		memcpy(Chain_Lightning_Range, lpSacerInfo->Chain_Lightning_Range, sizeof(Chain_Lightning_Range));
		memcpy(Chain_Lightning_UseMana, lpSacerInfo->Chain_Lightning_UseMana, sizeof(Chain_Lightning_UseMana));

		memcpy(Summon_Muspell_Damage, lpSacerInfo->Summon_Muspell_Damage, sizeof(Summon_Muspell_Damage));
		memcpy(Summon_Muspell_Attack_Delay, lpSacerInfo->Summon_Muspell_Attack_Delay, sizeof(Summon_Muspell_Attack_Delay));
		memcpy(Summon_Muspell_UndeadAbsorbPercent, lpSacerInfo->Summon_Muspell_UndeadAbsorbPercent, sizeof(Summon_Muspell_UndeadAbsorbPercent));
		memcpy(Summon_Muspell_BlockPercent, lpSacerInfo->Summon_Muspell_BlockPercent, sizeof(Summon_Muspell_BlockPercent));
		memcpy(Summon_Muspell_Time, lpSacerInfo->Summon_Muspell_Time, sizeof(Summon_Muspell_Time));
		memcpy(Summon_Muspell_UseMana, lpSacerInfo->Summon_Muspell_UseMana, sizeof(Summon_Muspell_UseMana));

		cInvenTory.SetItemToChar();


		break;


	case smTRANSCODE_MAGE_INFO:
		lpMageInfo = (MAGE_INFO*)pData->Buff;

		memcpy(Agony_UseMana, lpMageInfo->Agony_UseMana, sizeof(Agony_UseMana));
		memcpy(Agony_ConvLife, lpMageInfo->Agony_ConvLife, sizeof(Agony_ConvLife));

		memcpy(FireBolt_UseMana, lpMageInfo->FireBolt_UseMana, sizeof(FireBolt_UseMana));
		memcpy(FireBolt_Damage, lpMageInfo->FireBolt_Damage, sizeof(FireBolt_Damage));

		memcpy(Zenith_UseMana, lpMageInfo->Zenith_UseMana, sizeof(Zenith_UseMana));
		memcpy(Zenith_Element, lpMageInfo->Zenith_Element, sizeof(Zenith_Element));
		memcpy(Zenith_Time, lpMageInfo->Zenith_Time, sizeof(Zenith_Time));

		memcpy(FireBall_UseMana, lpMageInfo->FireBall_UseMana, sizeof(FireBall_UseMana));
		memcpy(FireBall_Damage, lpMageInfo->FireBall_Damage, sizeof(FireBall_Damage));
		memcpy(FireBall_Area, lpMageInfo->FireBall_Area, sizeof(FireBall_Area));
		memcpy(FireBall_Range, lpMageInfo->FireBall_Range, sizeof(FireBall_Range));

		memcpy(Mental_Mastery_Mana, lpMageInfo->Mental_Mastery_Mana, sizeof(Mental_Mastery_Mana));

		memcpy(Watornado_Damage, lpMageInfo->Watornado_Damage, sizeof(Watornado_Damage));
		memcpy(Watornado_Area, lpMageInfo->Watornado_Area, sizeof(Watornado_Area));
		memcpy(Watornado_Range, lpMageInfo->Watornado_Range, sizeof(Watornado_Range));
		memcpy(Watornado_Mana, lpMageInfo->Watornado_Mana, sizeof(Watornado_Mana));

		memcpy(Enchant_Weapon_Damage_Ice, lpMageInfo->Enchant_Weapon_Damage_Ice, sizeof(Enchant_Weapon_Damage_Ice));
		memcpy(Enchant_Weapon_Damage_Fire, lpMageInfo->Enchant_Weapon_Damage_Fire, sizeof(Enchant_Weapon_Damage_Fire));
		memcpy(Enchant_Weapon_Damage_Lightning, lpMageInfo->Enchant_Weapon_Damage_Lightning, sizeof(Enchant_Weapon_Damage_Lightning));
		memcpy(Enchant_Weapon_Time, lpMageInfo->Enchant_Weapon_Time, sizeof(Enchant_Weapon_Time));
		memcpy(Enchant_Weapon_Mana, lpMageInfo->Enchant_Weapon_Mana, sizeof(Enchant_Weapon_Mana));

		memcpy(Dead_Ray_Damage, lpMageInfo->Dead_Ray_Damage, sizeof(Dead_Ray_Damage));
		memcpy(Dead_Ray_Range, lpMageInfo->Dead_Ray_Range, sizeof(Dead_Ray_Range));
		memcpy(Dead_Ray_Mana, lpMageInfo->Dead_Ray_Mana, sizeof(Dead_Ray_Mana));

		memcpy(Energy_Shield_DecDamage, lpMageInfo->Energy_Shield_DecDamage, sizeof(Energy_Shield_DecDamage));
		memcpy(Energy_Shield_Time, lpMageInfo->Energy_Shield_Time, sizeof(Energy_Shield_Time));
		memcpy(Energy_Shield_UseMana, lpMageInfo->Energy_Shield_UseMana, sizeof(Energy_Shield_UseMana));

		memcpy(Diastrophism_Damage, lpMageInfo->Diastrophism_Damage, sizeof(Diastrophism_Damage));
		memcpy(Diastrophism_Area, lpMageInfo->Diastrophism_Area, sizeof(Diastrophism_Area));
		memcpy(Diastrophism_UseMana, lpMageInfo->Diastrophism_UseMana, sizeof(Diastrophism_UseMana));

		memcpy(Spirit_Elemental_RegenMana, lpMageInfo->Spirit_Elemental_RegenMana, sizeof(Spirit_Elemental_RegenMana));
		memcpy(Spirit_Elemental_Damage, lpMageInfo->Spirit_Elemental_Damage, sizeof(Spirit_Elemental_Damage));
		memcpy(Spirit_Elemental_Time, lpMageInfo->Spirit_Elemental_Time, sizeof(Spirit_Elemental_Time));
		memcpy(Spirit_Elemental_UseMana, lpMageInfo->Spirit_Elemental_UseMana, sizeof(Spirit_Elemental_UseMana));

		memcpy(Dancing_Sword_IceDamage, lpMageInfo->Dancing_Sword_IceDamage, sizeof(Dancing_Sword_IceDamage));
		memcpy(Dancing_Sword_FireDamage, lpMageInfo->Dancing_Sword_FireDamage, sizeof(Dancing_Sword_FireDamage));
		memcpy(Dancing_Sword_AttackDelay, lpMageInfo->Dancing_Sword_AttackDelay, sizeof(Dancing_Sword_AttackDelay));
		memcpy(Dancing_Sword_Time, lpMageInfo->Dancing_Sword_Time, sizeof(Dancing_Sword_Time));
		memcpy(Dancing_Sword_UseMana, lpMageInfo->Dancing_Sword_UseMana, sizeof(Dancing_Sword_UseMana));

		memcpy(Fire_Elemental_Damage, lpMageInfo->Fire_Elemental_Damage, sizeof(Fire_Elemental_Damage));
		memcpy(Fire_Elemental_Hit, lpMageInfo->Fire_Elemental_Hit, sizeof(Fire_Elemental_Hit));
		memcpy(Fire_Elemental_Life, lpMageInfo->Fire_Elemental_Life, sizeof(Fire_Elemental_Life));
		memcpy(Fire_Elemental_UseMana, lpMageInfo->Fire_Elemental_UseMana, sizeof(Fire_Elemental_UseMana));

		memcpy(Flame_Wave_FireDamage, lpMageInfo->Flame_Wave_FireDamage, sizeof(Flame_Wave_FireDamage));
		memcpy(Flame_Wave_Area, lpMageInfo->Flame_Wave_Area, sizeof(Flame_Wave_Area));
		memcpy(Flame_Wave_UseMana, lpMageInfo->Flame_Wave_UseMana, sizeof(Flame_Wave_UseMana));

		memcpy(Distortion_SpeedSubPercent, lpMageInfo->Distortion_SpeedSubPercent, sizeof(Distortion_SpeedSubPercent));
		memcpy(Distortion_DamageSubPercent, lpMageInfo->Distortion_DamageSubPercent, sizeof(Distortion_DamageSubPercent));
		memcpy(Distortion_Area, lpMageInfo->Distortion_Area, sizeof(Distortion_Area));
		memcpy(Distortion_Time, lpMageInfo->Distortion_Time, sizeof(Distortion_Time));
		memcpy(Distortion_UseMana, lpMageInfo->Distortion_UseMana, sizeof(Distortion_UseMana));

		memcpy(Meteo_Damage, lpMageInfo->Meteo_Damage, sizeof(Meteo_Damage));
		memcpy(Meteo_Area, lpMageInfo->Meteo_Area, sizeof(Meteo_Area));
		memcpy(Meteo_UseMana, lpMageInfo->Meteo_UseMana, sizeof(Meteo_UseMana));

		cInvenTory.SetItemToChar();

		//AddChatBuff("Habilidades foram atualizadas");

		break;

	case OpCode::OPCODE_EXPLVL1:
	{
		chaPremiumitem.UsePremiumItem(155);
		AddChatBuff("Você recebeu o Kit Iniciante");
	}
	break;
	case OpCode::SEARCH_GAME_CHEAT:
	{
		pcAntiCheat->ReceivePacketHandler((PacketChecksumFunctionList*)pData->Buff);
	}
	break;
	case OpCode::INIT_CHEAT_PROTECTION:
	{
		pcAntiCheat->HandlePacket((PacketWindowList*)pData->Buff);
	}
	break;

	case OpCode::OPCODE_SPOILER_INFO:
		cQuestWindow.handlePacket((smTRANS_QUEST_INFO*)pData->Buff);
		break;

	case OpCode::OPCODE_QUEST_INFO:
		cQuestWindow.handlePacket((smTRANS_QUEST_FULL*)pData->Buff);
		break;

	case OpCode::SET_ITEM_PREMIUM:
	{
		smTRANS_COMMAND * smPacket;
		smPacket = (smTRANS_COMMAND*)pData->Buff;

		int iCount = 0;
		int iTimeLeft = smPacket->WParam;
		int iItemType = smPacket->SParam;

		if (iItemType > 0 && iTimeLeft > 0)
		{
			chaPremiumitem.SetUpKeepItem(nsPremiumItem::BIGHEAD1, SINITEM_TIME_ONEDAY, true, UpKeepItemName[13], 30);
			chaPremiumitem.SetItemPremiumTime(nsPremiumItem::BIGHEAD1, iTimeLeft);
			chaPremiumitem.SetBigHeadType(iItemType);
			cInvenTory.SetItemToChar();

			switch (chaPremiumitem.GetBigHeadType())
			{
			case 1:
				ChangeHairModel(13);
				break;
			case 2:
				ChangeHairModel(14);
				break;
			case 3:
				ChangeHairModel(15);
				break;
			case 4:
				ChangeHairModel(16);
				break;
			}
		}
	}
	break;

	case OpCode::OPCODE_CHATMESSAGE:

		ChatCnt = ChatBuffCnt & CHATBUFF_MASK;
		ChatBuff[ChatCnt].dwIP = IPData[2];
		strcpy_s(ChatBuff[ChatCnt].szMessage, &pData->Buff[3 * 4]);
		ChatBuffCnt++;
		ChatDispCnt = 70 * 10;
		if (ChatScrollPoint)
		{
			ChatScrollPoint++;
		}

		break;


	case OpCode::OPCODE_AUTH_ADMIN_MODE:
	{
		smTRANS_COMMAND	*TransCommand = (smTRANS_COMMAND *)pData->Buff;

		if (TransCommand)
		{
			if (TransCommand->WParam)
			{
				smConfig.setSecurity(AccountTypes(TransCommand->WParam));
				smConfig.setSecurityAuth(true);
			}
			else
			{
				smConfig.setSecurity(AccountTypes::SEC_PLAYER);
			}
		}
	}
	break;

	case OpCode::OPCODE_PLAYLIST:
		break;

	case OpCode::OPCODE_PLAYERINFO:

		lpTransPlayerInfo = (smTRNAS_PLAYERINFO *)pData->Buff;

		lpChar = FindAutoPlayer(lpTransPlayerInfo->dwObjectSerial);

		if (lpChar)
		{
			lpChar->RecvPlayData(pData);

			RequestPartyPlayers(lpChar);
		}


		if (lpTransPlayerInfo->smCharInfo.State == smCHAR_STATE_ENEMY && lpTransPlayerInfo->smCharInfo.Brood != smCHAR_MONSTER_USER)
			SaveCharInfoCache(lpTransPlayerInfo);

		break;

	case OpCode::OPCODE_PLAYERINFO_Q:

		lpChar = FindAutoPlayer(((smTRNAS_PLAYERINFO_QUICK *)pData->Buff)->dwObjectSerial);

		if (lpChar)
		{
			lpChar->RecvPlayData(pData);

			RequestPartyPlayers(lpChar);
		}
		break;

	case OpCode::OPCODE_PLAYDATAGROUP:


		smPLAYDATA_GROUP *lpPlayDataGroup;
		char *lpTransBuff;

		lpPlayDataGroup = (smPLAYDATA_GROUP *)pData->Buff;
		lpTransBuff = pData->Buff + sizeof(smPLAYDATA_GROUP);

		if (!(lpPlayDataGroup->dwSendCode & 0x80000000))
		{
			rsRecvUserServer = TRUE;
		}

		ServerCode = 0;
		RcvCnt = 0;

		if (smWsockUserServer == pData->smMySock)
		{
			ServerCode = PLAY_SERVER_CODE_USER;
		}
		else
		{
			if (smWsockExtendServer == pData->smMySock)
				ServerCode = PLAY_SERVER_CODE_EXTEND;
			else
				ServerCode = PLAY_SERVER_CODE_MAIN;
		}

		if (AreaServerMode && ServerCode == PLAY_SERVER_CODE_MAIN)
		{
			if (lpWSockServer_DispArea[0] == pData->smMySock)
			{
				ServerCode = PLAY_SERVER_CODE_AREA1;
			}
			else  if (lpWSockServer_DispArea[1] == pData->smMySock)
			{
				ServerCode = PLAY_SERVER_CODE_AREA2;
			}
		}

		for (cnt = 0; cnt < lpPlayDataGroup->PlayDataCnt; cnt++)
		{

			lpPlayData1 = (smPLAYDATA *)lpTransBuff;
			lpChar = FindAutoPlayer(lpPlayData1->dwObjectSerial);

			if (lpChar)
			{
				lpChar->RecvPlayData2(lpTransBuff);
				if (lpChar->PlayBuffCnt < (lpChar->PlayBuffPosi_End - 70))
				{
					lpChar->PlayBuffCnt = lpChar->PlayBuffPosi_End - 70;
				}
			}
			else
			{
				if (RcvCnt < 8 || (RcvCnt < 16 && ((int *)lpTransBuff)[1] == OpCode::OPCODE_TRANSPLAYDATA))
				{
					RcvCnt++;
					lpChar = FindEmptyChar();
					if (lpChar)
					{

						lpChar->Init();
						lpChar->Flag = TRUE;
						lpChar->smCharInfo.szName[0] = 0;
						lpChar->ActionPattern = 99;
						lpChar->Pattern = 0;
						lpChar->AutoPlayer = TRUE;
						lpChar->TransSock = 0;
						lpChar->AutoPlayer = TRUE;
						lpChar->DisplayFlag = FALSE;
						lpChar->MotionInfo = 0;

						lpChar->dwObjectSerial = lpPlayData1->dwObjectSerial;
						lpChar->ServerCode = ServerCode;

						lpChar->ResetAttackTrans();




						lpTransPlayerInfo = GetCharInfoCache(lpTransBuff);
						if (lpTransPlayerInfo)
						{

							lpChar->SetTransPlayerInfo(lpTransPlayerInfo);


							RequestPartyPlayers(lpChar);
						}
						else
						{

							TransCommand.code = OpCode::OPCODE_GETPLAYERINFO;
							TransCommand.size = sizeof(smTRANS_COMMAND);
							TransCommand.WParam = lpPlayData1->dwObjectSerial;

							if (pData->smMySock->sock)
							{
								pData->smMySock->Send((char *)&TransCommand, TransCommand.size, TRUE);
							}
						}
					}
				}
			}
			lpTransBuff += lpPlayData1->size;
		}

		lpTransCommand = (smTRANS_COMMAND *)lpTransBuff;
		if (lpTransCommand->code == OpCode::OPCODE_PLAY_COMMAND && lpTransCommand->WParam == lpCurPlayer->dwObjectSerial)
		{

			switch (lpTransCommand->LParam)
			{
			case smCOMMAND_PLAY_BABEL:

				dwBabelPlayTime = dwPlayTime + 5000;
				BabelPlayField = lpTransCommand->SParam;
				break;

			case smCOMMAND_PLAY_PK_FIELD:

				PK_FieldState.dwPlay_FieldTime = dwPlayTime + 10000;
				PK_FieldState.FieldCode = lpTransCommand->SParam;
				break;

			case smCOMMAND_PLAY_BELSS_CASTLE:

				memcpy(&rsBlessCastleOld, &rsBlessCastle, sizeof(rsBLESS_CASTLE));

				lpTransCommandEx = (smTRANS_COMMAND_EX *)lpTransBuff;

				rsBlessCastle.CastleMode = lpTransCommandEx->SParam >> 16;
				rsBlessCastle.DefenceLevel = lpTransCommandEx->SParam & 0xFFFF;
				rsBlessCastle.dwMasterClan = lpTransCommandEx->EParam;
				((int *)rsBlessCastle.TimeSec)[0] = lpTransCommandEx->WxParam;
				((int *)rsBlessCastle.bCrystalSolderCount)[0] = lpTransCommandEx->LxParam;

				chaSiege.ShowPlayTime(rsBlessCastle.TimeSec[1] - rsBlessCastle.TimeSec[0]);


				lpCurPlayer->sBlessCastle_Damage[0] += lpTransCommandEx->SxParam & 0xFFFF;
				lpCurPlayer->sBlessCastle_Damage[1] += lpTransCommandEx->SxParam >> 16;

				if (rsBlessCastle.CastleMode == 3)
				{
					if (rsBlessCastleOld.CastleMode == 1)
					{

						RestartPlayCount = 400;
						StopBGM();
						esPlayContSound(14);
						chaSiege.ShowExitMessage();

						if (rsBlessCastle.dwMasterClan && rsBlessCastle.dwMasterClan == GetClanCode(lpCurPlayer->smCharInfo.ClassClan))
						{
							lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_YAHOO);
						}
					}
				}
				else if (rsBlessCastleOld.CastleMode && rsBlessCastle.CastleMode == 0)
				{

					if (!lpCurPlayer->smCharInfo.ClassClan || rsBlessCastle.dwMasterClan != GetClanCode(lpCurPlayer->smCharInfo.ClassClan))
					{

						WarpField2(rsCASTLE_FIELD);
					}
				}


				if ((dwResistance_SendingTime + 1000 * 60) < dwPlayTime)
				{
					SendResistanceToServer();
				}

				if (rsBlessCastle.dwMasterClan != rsBlessCastleOld.dwMasterClan)
				{


					UpdateCastleMasterClan(rsBlessCastle.dwMasterClan);
				}


				break;
			}
		}
		break;

	case OpCode::OPCODE_ATTACKDATA2:
#ifdef _USE_DYNAMIC_ENCODE
		if (fnDecodeDamagePacket)
			fnDecodeDamagePacket(0, pData->Buff);

		if (((TRANS_ATTACKDATA *)pData->Buff)->dwDamageChkSum != dm_GetDamgeChkSum_S2V((TRANS_ATTACKDATA *)pData->Buff))
		{
			SendSetHackUser3(8580, ((TRANS_ATTACKDATA *)pData->Buff)->Power, (DWORD)fnDecodeDamagePacket);
			break;
		}
#else
		dm_DecodePacket(0, pData->Buff);

		if (((TRANS_ATTACKDATA *)pData->Buff)->dwDamageChkSum != dm_GetDamgeChkSum_S2V((TRANS_ATTACKDATA *)pData->Buff))
		{
			SendSetHackUser3(8580, ((TRANS_ATTACKDATA *)pData->Buff)->Power, (DWORD)dm_DecodePacket);
			break;
		}
#endif
	case OpCode::OPCODE_ATTACKDATA:
		CheckInvenItemToServer();
		Record_RecvDamage(pData->smMySock, ((TRANS_ATTACKDATA *)pData->Buff)->Power);

	case OpCode::OPCODE_PLAYDATA1:
	case OpCode::OPCODE_PLAYDATA2:
	case OpCode::OPCODE_PLAYDATA3:
	case OpCode::OPCODE_TRANSPLAYDATA:


		ServerCode = 0;

		if (smWsockUserServer == pData->smMySock)
		{
			ServerCode = PLAY_SERVER_CODE_USER;
		}
		else
		{
			if (smWsockExtendServer != smWsockServer && smWsockExtendServer == pData->smMySock)
				ServerCode = PLAY_SERVER_CODE_EXTEND;
			else
				ServerCode = PLAY_SERVER_CODE_MAIN;
		}


		if (AreaServerMode && ServerCode == PLAY_SERVER_CODE_MAIN)
		{
			if (lpWSockServer_DispArea[0] == pData->smMySock)
			{
				ServerCode = PLAY_SERVER_CODE_AREA1;
			}
			else  if (lpWSockServer_DispArea[1] == pData->smMySock)
			{
				ServerCode = PLAY_SERVER_CODE_AREA2;
			}
		}


		lpPlayData1 = (smPLAYDATA *)pData->Buff;
		lpChar = FindAutoPlayer(lpPlayData1->dwObjectSerial);
		if (lpChar)
		{
			lpChar->RecvPlayData(pData);
			if (lpChar->PlayBuffCnt < (lpChar->PlayBuffPosi_End - 70))
			{
				lpChar->PlayBuffCnt = lpChar->PlayBuffPosi_End - 70;
			}
		}

		break;

	case OpCode::OPCODE_ATTACK_SLASH_LIST:

		memcpy(&Trans_SplashCharList, pData->Buff, sizeof(TRANS_SKIL_ATTACKDATA));
		break;


	case OpCode::OPCODE_ISBETA:

		sSKILL BetaPlayer;

		betaPlayer = TRUE;

		for (int j = 0; j < SIN_MAX_SKILL; j++)
		{
			if (sSkill[j].CODE == PLAYERBETA)
			{
				memcpy(&BetaPlayer, &sSkill[j], sizeof(sSKILL));
				BetaPlayer.UseTime = 604800;
				sinContinueSkillSet(&BetaPlayer);
				lpCurPlayer->PlayerBeta = TRUE;

				break;
			}
		}


		break;
	case OpCode::OPCODE_PLAYITEM:

		smTRANS_ITEMS	*lpTransItems;
		scITEM			*lpScItem;

		lpTransItems = (smTRANS_ITEMS *)pData->Buff;

		if (smWsockUserServer == pData->smMySock)
		{
			ServerCode = PLAY_SERVER_CODE_USER;
		}
		else
		{
			if (smWsockExtendServer != smWsockServer && smWsockExtendServer == pData->smMySock)
				ServerCode = PLAY_SERVER_CODE_EXTEND;
			else
				ServerCode = PLAY_SERVER_CODE_MAIN;
		}

		if (AreaServerMode && ServerCode == PLAY_SERVER_CODE_MAIN)
		{
			if (lpWSockServer_DispArea[0] == pData->smMySock)
			{
				ServerCode = PLAY_SERVER_CODE_AREA1;
			}
			else  if (lpWSockServer_DispArea[1] == pData->smMySock)
			{
				ServerCode = PLAY_SERVER_CODE_AREA2;
			}
		}

		for (cnt = 0; cnt < lpTransItems->Count; cnt++)
		{
			lpScItem = FindScItem(lpTransItems->Items[cnt].x, lpTransItems->Items[cnt].z);
			if (lpScItem)
			{
				lpScItem->dwLastTransTime = dwPlayTime;
			}
			else
			{

				lpScItem = FindEmptyScItem();
				if (lpScItem)
				{
					lpScItem->SetTransItem(&lpTransItems->Items[cnt]);
					lpScItem->ServerCode = ServerCode;
				}
			}
		}
		break;

	case OpCode::OPCODE_DELITEM:

		lpTransActionItem = (smTRANS_ACITON_ITEM *)pData->Buff;
		lpScItem = FindScItem(lpTransActionItem->x, lpTransActionItem->z);
		if (lpScItem)
		{


			EnterCriticalSection(&cDrawSection);
			smEnterTextureCriticalSection();

			lpScItem->Close();


			smLeaveTextureCriticalSection();
			LeaveCriticalSection(&cDrawSection);

		}
		break;

	case OpCode::OPCODE_PUTITEM:

		lpTransItemInfo = (TRANS_ITEMINFO *)pData->Buff;


		if (FiltQuestItem(lpTransItemInfo, OpCode::OPCODE_PUTITEM) == FALSE) break;



		if (PushRecvTransItemQue(lpTransItemInfo) == TRUE)
		{

			TransCommandEx.code = OpCode::OPCODE_GETITEM;
			TransCommandEx.size = sizeof(smTRANS_COMMAND_EX);
			TransCommandEx.WParam = lpTransItemInfo->Item.CODE;
			TransCommandEx.LParam = lpTransItemInfo->Item.ItemHeader.Head;
			TransCommandEx.SParam = lpTransItemInfo->Item.ItemHeader.dwChkSum;
			TransCommandEx.EParam = lpTransItemInfo->Item.Money^OpCode::OPCODE_GETITEM^lpTransItemInfo->Item.ItemHeader.dwChkSum;

			TransCommandEx.WxParam = lpTransItemInfo->dwSeCode[0];
			TransCommandEx.LxParam = lpTransItemInfo->dwSeCode[1];
			TransCommandEx.SxParam = lpTransItemInfo->dwSeCode[2];
			TransCommandEx.ExParam = lpTransItemInfo->dwSeCode[3];
			if (smWsockDataServer)
				smWsockDataServer->Send((char *)&TransCommandEx, TransCommandEx.size, TRUE);

			break;
		}


		ComparePotion();

		memcpy(&TransRecvItem, lpTransItemInfo, sizeof(TRANS_ITEMINFO));


		if (CheckItemForm(&lpTransItemInfo->Item) == TRUE)
		{
			if (lpTransItemInfo->Item.CODE == (sinGG1 | sin01))
			{
				if (cInvenTory.CheckMoneyLimit(lpTransItemInfo->Item.Money) == TRUE)
				{

					lpCurPlayer->smCharInfo.Money += lpTransItemInfo->Item.Money;
					ReformCharForm();
					sinPlaySound(SIN_SOUND_COIN, 400);

					addMoney = lpTransItemInfo->Item.Money;

					CheckServerMoney(pData->smMySock, lpTransItemInfo);

				}
				else
				{

					ThrowPutItem2(&lpTransItemInfo->Item, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
				}
			}
			else
			{
				if ((lpTransItemInfo->Item.CODE&sinITEM_MASK2) == sinQT1 || lpTransItemInfo->Item.ItemKindCode == ITEM_KIND_QUEST_WEAPON)
				{


					if (sinSetQuestItem(&lpTransItemInfo->Item) == TRUE)
					{
						SaveGameData();
					}
				}
				else
				{
					sinSetInvenItem(&lpTransItemInfo->Item);


					if (lpTransItemInfo->Item.Price >= 3000)
						SaveGameData();

					if ((lpTransItemInfo->Item.CODE&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
					{

						ResetPotion2();
					}
				}
			}

		}
		ZeroMemory(&TransRecvItem, sizeof(TRANS_ITEMINFO));
		ResetInvenItemCode();
		break;

	case OpCode::OPCODE_GETITEM:

		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;

		lpTransItemInfo = FindRecvTransItemQue(lpTransCommand->WParam, lpTransCommand->LParam, lpTransCommand->SParam);

		if (!lpTransItemInfo) break;

		if (FiltQuestItem(lpTransItemInfo, OpCode::OPCODE_GETITEM) == FALSE) break;


		ComparePotion();

		memcpy(&TransRecvItem, lpTransItemInfo, sizeof(TRANS_ITEMINFO));


		if (CheckItemForm(&lpTransItemInfo->Item) == TRUE)
		{
			if (lpTransItemInfo->Item.CODE == (sinGG1 | sin01))
			{
				if (cInvenTory.CheckMoneyLimit(lpTransItemInfo->Item.Money) == TRUE)
				{

					lpCurPlayer->smCharInfo.Money += lpTransItemInfo->Item.Money;
					ReformCharForm();
					sinPlaySound(SIN_SOUND_COIN, 400);

					addMoney = lpTransItemInfo->Item.Money;

					CheckServerMoney(pData->smMySock, lpTransItemInfo);

				}
				else
				{

					ThrowPutItem2(&lpTransItemInfo->Item, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
				}
			}
			else
			{
				if ((lpTransItemInfo->Item.CODE&sinITEM_MASK2) == sinQT1 || lpTransItemInfo->Item.ItemKindCode == ITEM_KIND_QUEST_WEAPON)
				{


					if (sinSetQuestItem(&lpTransItemInfo->Item) == TRUE)
					{
						SaveGameData();
					}
				}
				else
				{
					if ((lpTransItemInfo->Item.CODE&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
					{
						if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR && VRKeyBuff['P'] && VRKeyBuff['O'])
						{
							lpTransItemInfo->Item.PotionCount *= 2;
						}
					}

					sinSetInvenItem(&lpTransItemInfo->Item);


					if (lpTransItemInfo->Item.Price >= 3000)
						SaveGameData();

					if ((lpTransItemInfo->Item.CODE&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
					{


						ResetPotion2();
					}
				}
			}

		}
		ZeroMemory(&TransRecvItem, sizeof(TRANS_ITEMINFO));
		ZeroMemory(lpTransItemInfo, sizeof(TRANS_ITEMINFO));

		ResetInvenItemCode();
		break;


	case OpCode::OPCODE_MESSAGEBOX:

		lpTransChatMessage = (TRANS_CHATMESSAGE *)pData->Buff;
		cMessageBox.ShowMessageEvent(lpTransChatMessage->szMessage);
		break;

	case OpCode::OPCODE_WHISPERMESSAGE:


		lpTransChatMessage = (TRANS_CHATMESSAGE *)pData->Buff;

		lpChar = FindAutoPlayer(lpTransChatMessage->dwObjectSerial);
		if (lpChar && lpTransChatMessage->dwIP != 4)
		{
			strcpy_s(lpChar->szChatMessage, lpTransChatMessage->szMessage);
			lpChar->dwChatMessageTimer = dwPlayTime + 1000 * 5;

			if (lpChar->smCharInfo.State == smCHAR_STATE_USER)
			{

				ChatCnt = ChatBuffCnt & CHATBUFF_MASK;
				ChatBuff[ChatCnt].dwIP = smCHAR_STATE_USER;
				strcpy_s(ChatBuff[ChatCnt].szMessage, lpTransChatMessage->szMessage);
				ChatBuffCnt++;
				ChatDispCnt = 70 * 10;
				if (ChatScrollPoint)
				{
					ChatScrollPoint++;
				}

				if (chrEachPlayer.Flag && chrEachMaster == lpChar)
				{
					strcpy_s(chrEachPlayer.szChatMessage, lpTransChatMessage->szMessage);
				}
			}
			else if (lpChar->smCharInfo.State == smCHAR_STATE_NPC)
			{
				if (FindTalkSound(lpChar->szChatMessage) == FALSE)
				{
					StopTalkSound();

					strcpy_s(g_szPlayTalkSoundName, g_szTalkSoundName);
					g_PlayTalkSoundSum = g_TalkSoundSum;
				}

				strcpy_s(chrEachPlayer.szChatMessage, lpChar->szChatMessage);
				chrEachPlayer.TalkSoundSum = g_TalkSoundSum;
			}

		}
		else
		{
			ChatCnt = ChatBuffCnt & CHATBUFF_MASK;
			ChatBuff[ChatCnt].dwIP = lpTransChatMessage->dwIP;
			strcpy_s(ChatBuff[ChatCnt].szMessage, lpTransChatMessage->szMessage);

			if (ChatBuffFilter(ChatBuff[ChatCnt].szMessage, ChatBuff[ChatCnt].dwIP) == TRUE)
			{
				ChatBuffCnt++;
				ChatDispCnt = 70 * 10;

				if (lpTransChatMessage->dwIP == 1 || lpTransChatMessage->dwIP == 3)
				{

					if (!cInterFace.ChatFlag)
					{

						esPlaySound(8, 360);
						cInterFace.ChatFlag = 1;
					}
				}
			}
		}

		break;
		/*
	case OpCode::BATTLE_POINTS:
	{
		smTRANS_COMMAND* smTransCommand = (smTRANS_COMMAND*)pData->Buff;

		lpCurPlayer->sBlessCastle_Damage[1] = smTransCommand->WParam;


		if (smTransCommand->SParam)
		{
			sSKILL haPVP;

			ReiPVP = TRUE;

			for (int j = 0; j < SIN_MAX_SKILL; j++)
			{
				if (sSkill[j].CODE == REIPVP)
				{
					memcpy(&haPVP, &sSkill[j], sizeof(sSKILL));
					haPVP.UseTime = 604800;
					sinContinueSkillSet(&haPVP);
					bReiPVP = TRUE;
					lpCurPlayer->PlayCursePvP = TRUE;
					break;
				}
			}
		}
		break; 
	}
	*/
	case OpCode::BOSS_TIME:
	{
		smTRANS_COMMAND* smTransCommand = (smTRANS_COMMAND*)pData->Buff;

		//wsprintf(szBossTime, "%02d", smTransCommand->WParam);
		szBossTime = smTransCommand->WParam;

		break;
	}

	case OpCode::PLAYER_GM:
	{
		smTRANS_COMMAND * smTransCommand = (smTRANS_COMMAND *)pData->Buff;

		if (smTransCommand->SParam)
		{
			sSKILL haGM;

			PlayerGM = TRUE;

			for (int j = 0; j < SIN_MAX_SKILL; j++)
			{
				if (sSkill[j].CODE == PLAYERGM)
				{
					memcpy(&haGM, &sSkill[j], sizeof(sSKILL));
					haGM.UseTime = 604800;
					sinContinueSkillSet(&haGM);
					bGm = TRUE;
					lpCurPlayer->PlayerGm = TRUE;

					break;
				}
			}
		}
		break;
	}
	
	case OpCode::PLAYER_BETA:
	{
		smTRANS_COMMAND * smTransCommand = (smTRANS_COMMAND *)pData->Buff;

		//lpCurPlayer->sBlessCastle_Damage[1] = smTransCommand->WParam;

		if (smTransCommand->SParam)
		{
			sSKILL haTopLevel;

			PLayerTopLevel = TRUE;

			for (int j = 0; j < SIN_MAX_SKILL; j++)
			{
				if (sSkill[j].CODE == PLAYER_TOPLEVEL)
				{
					memcpy(&haTopLevel, &sSkill[j], sizeof(sSKILL));
					haTopLevel.UseTime = 604800;
					sinContinueSkillSet(&haTopLevel);
					bTopLevel = TRUE;
					lpCurPlayer->PlayerTopLevel = TRUE;
					break;
				}
			}
		}
		break;
	}
	
	case OpCode::OPCODE_CONNECTED:

		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;


		SaveCheckSkill();
		lpCurPlayer->dwObjectSerial = lpCurPlayer->smCharInfo.dwObjectSerial;
		ReformSkillInfo();

		if (pData->smMySock == smWsockServer)
		{

			dwGameWorldTime = ConvSysTimeToGameTime(lpTransCommand->LParam);
			dwGameHour = dwGameWorldTime / 60;
			dwGameHour = dwGameHour - (((int)(dwGameHour / 24)) * 24);
			dwGameMin = dwGameWorldTime - (((int)(dwGameWorldTime / 60)) * 60);



			dwConnectedClientTime = GetCurrentTime();
			dwConnectedServerTime = lpTransCommand->LParam;
			dwLastRecvGameServerTime = dwConnectedClientTime;


			if (smWsockServer != smWsockUserServer)
				SendSetObjectSerial_First(lpCurPlayer->smCharInfo.dwObjectSerial);




			SendNetworkQuality(cSettings::GetInstance()->cNetwork);



			SendProcessInfo();




		}

		break;

	case OpCode::OPCODE_RECORDDATA:

		if (!lpRecorder)
		{
			lpRecorder = new rsRECORD_DBASE;
			lpRecorder->TransLastPartCount = 0;
			ZeroMemory(lpRecorder->TransDataBlock, 64);
		}


		if (lpRecorder->RecvRecordDataFromServer((TRANS_RECORD_DATAS *)pData->Buff) == TRUE)
		{

			if (AdminCharDisable)
			{
				ZeroMemory(cInvenTory.InvenItem, sizeof(sITEM)*INVENTORY_MAXITEM);
				ZeroMemory(cInvenTory.InvenItemTemp, sizeof(sITEM)*INVENTORY_MAXITEM);

				lpCurPlayer->SetTool(0, hvPOSI_LHAND);
				lpCurPlayer->SetTool(0, hvPOSI_RHAND);
			}

			lpRecorder->ResotrRecordData(&lpCurPlayer->smCharInfo, cInvenTory.InvenItem, cInvenTory.InvenItemTemp, &MouseItem);

			if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR) {
				AddChatBuff(lpRecorder->TransRecordData.GameSaveInfo.szMasterID);
			}

			if (lpRecorder)
			{
				delete lpRecorder;
				lpRecorder = 0;
			}

			dwLoadingTime = 0;


			if ((lpCurPlayer->smCharInfo.JOB_CODE == 3 || lpCurPlayer->smCharInfo.JOB_CODE == 5 || lpCurPlayer->smCharInfo.JOB_CODE == 7)
				&& lpCurPlayer->Pattern)
			{

				lpCurPlayer->SetPattern(lpCurPlayer->Pattern);
			}


			if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR && smConfig.szFile_Player[0])
			{

				strcpy_s(lpCurPlayer->smCharInfo.szModelName, smConfig.szFile_Player);
				lpCurPlayer->smCharInfo.szModelName2[0] = 0;

				CharLower(lpCurPlayer->smCharInfo.szModelName);

				lpCurPlayer->smCharInfo.State = smCHAR_STATE_USER;

				if (smConfig.szFile_Enemy[0])
				{
					if (strstr(lpCurPlayer->smCharInfo.szModelName, "monster") != 0)
						lpCurPlayer->smCharInfo.State = smCHAR_STATE_ENEMY;
					if (strstr(lpCurPlayer->smCharInfo.szModelName, "npc") != 0)
						lpCurPlayer->smCharInfo.State = smCHAR_STATE_NPC;
				}

				AddLoaderPattern(lpCurPlayer, lpCurPlayer->smCharInfo.szModelName, lpCurPlayer->smCharInfo.szModelName2);
				ReformCharForm();
			}

			lpCurPlayer->Flag = TRUE;

			if (!lpCurPlayer->smCharInfo.dwEventTime_T || GetPlayTime_T() > lpCurPlayer->smCharInfo.dwEventTime_T)
			{
				lpCurPlayer->smCharInfo.SizeLevel = 1;
				lpCurPlayer->smCharInfo.dwEventTime_T = 0;
			}


			if (lpCurPlayer->smCharInfo.SizeLevel > 0x1000 && lpCurPlayer->smCharInfo.SizeLevel <= 0x1002)
			{
				ChangeModelSkin(lpCurPlayer, 1, lpCurPlayer->smCharInfo.SizeLevel + 3 - 0x1000, 0, 0);
				ReformCharForm();
				cInvenTory.IncreViewDamage(15);
			}
			else if (lpCurPlayer->smCharInfo.dwEventTime_T > 0 && lpCurPlayer->smCharInfo.SizeLevel == 1)
			{
				ChangeModelSkin(lpCurPlayer, 0, 6, 0, 0);
				ReformCharForm();
			}
			else
			{
				if (lpCurPlayer->smCharInfo.ChangeJob >= 0 && lpCurPlayer->smCharInfo.ChangeJob < 4)
				{
					ChangeModelSkin(lpCurPlayer, 0, lpCurPlayer->smCharInfo.ChangeJob, 0, GetFaceHairSkin(lpCurPlayer));
					ReformCharForm();
				}
			}

#ifdef  __CLANSUBCHIP__
			if (cldata.myPosition == 100 || cldata.myPosition == 101 || cldata.myPosition == 104)
			{
#else
			if (cldata.myPosition == 100 || cldata.myPosition == 101)
			{
#endif

				lpCurPlayer->smCharInfo.ClassClan = cldata.intClanMark;
				lpCurPlayer->dwClanManageBit = cldata.CNFlag;

				int SetSODSkill(int SODSkill);

				SetSODSkill(cldata.CNFlag);
			}
			else
				lpCurPlayer->smCharInfo.ClassClan = 0;

			if (cldata.myPosition)
				InitClanMode = cldata.myPosition;

			if (!AdminCharDisable)
			{

				rsRecorder.dwNextRecordTime = dwPlayTime + RECORD_TIME_STEP;

				lpCurPlayer->SendCharInfo(smWsockServer);
			}
			else
			{
				AddLoaderPattern(lpCurPlayer, lpCurPlayer->smCharInfo.szModelName, lpCurPlayer->smCharInfo.szModelName2);

				ReformCharForm();
			}


			if (lpCurPlayer->smCharInfo.Life[0] == 0)
			{

				lpCurPlayer->MoveFlag = FALSE;
				WarpStartField(&x, &z);
				lpCurPlayer->SetPosi(x, 0, z, 0, 0, 0);
				TraceCameraPosi.x = lpCurPlayer->pX;
				TraceCameraPosi.y = lpCurPlayer->pY;
				TraceCameraPosi.z = lpCurPlayer->pZ;
				TraceTargetPosi.x = lpCurPlayer->pX;
				TraceTargetPosi.y = lpCurPlayer->pY;
				TraceTargetPosi.z = lpCurPlayer->pZ;

				lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_RESTART);
				StartEffect(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, EFFECT_GAME_START1);
				SetDynLight(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 100, 100, 100, 0, 200);
				CharPlaySound(lpCurPlayer);
				dwBattleTime = 0;
				dwBattleQuitTime = 0;


				lpCurPlayer->OnStageField = -1;
				if (smGameStage[0])
				{
					cnt = smGameStage[0]->GetFloorHeight(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, lpCurPlayer->Pattern->SizeHeight);
					lpCurPlayer->OnStageField = 0;
				}
				if (cnt == CLIP_OUT && smGameStage[1])
				{
					lpCurPlayer->OnStageField = 1;
				}
			}


			cnt = lpCurPlayer->smCharInfo.Life[0];
			if (cnt > lpCurPlayer->smCharInfo.Life[1] || cnt < 0)
			{

				CheckCharForm();
				lpCurPlayer->smCharInfo.Life[0] = lpCurPlayer->smCharInfo.Life[1] / 2;
				ReformCharForm();
			}

			CheckCharForm();
			CodeXorExp = dwPlayTime + lpCurPlayer->smCharInfo.Exp;
			CodeXorExp_High = dwPlayTime | (dwPlayTime*dwPlayTime);
			CodeXorLife = (dwPlayTime*lpCurPlayer->smCharInfo.Life[0]) & 0xFFFF;
			lpCurPlayer->smCharInfo.Exp ^= CodeXorExp;
			lpCurPlayer->smCharInfo.Exp_High ^= CodeXorExp_High;
			lpCurPlayer->smCharInfo.Life[0] ^= CodeXorLife;
			ReformCharForm();

			ResetPotion();
			ResetInvenItemCode();

			ReformSkillInfo();


			SendProcessInfo();


			ResetEnergyGraph(4);


			ResetInvenMoney();

			CheckPlaySkill();
		}

		break;

	case OpCode::OPCODE_FAILRECORDDATA:

		lpTransCharCommand = (smTRANS_CHAR_COMMAND *)pData->Buff;
		lpCurPlayer->smCharInfo.dwObjectSerial = lpTransCharCommand->WParam;
		lpCurPlayer->smCharInfo.dwLoginServerSafeKey = lpTransCharCommand->LParam;

		if (!lpCurPlayer->smCharInfo.JOB_CODE && smConfig.getSecurity() < AccountTypes::SEC_MODERATOR)
		{//LOG_GAME
			Log::getInstance()->output(LOG_GAME, "SetDisconnectFlag: 11");
			DisconnectFlag = GetCurrentTime();
			break;
		}


		if (!AdminCharDisable)
		{
			CheckStartCharInfo();
			rsRecorder.dwNextRecordTime = dwPlayTime + RECORD_TIME_STEP;
			dwLoadingTime = 0;
			lpCurPlayer->SendCharInfo(smWsockServer);

			InitHelp();
			cHelpPet.CheckPetData();
			cPCBANGPet.CheckPetData();
		}
		break;

	case OpCode::OPCODE_RECORDRESULT:

		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;
		rsRecorder.dwRecordTime = 0;
		rsRecorder.dwNextRecordTime = dwPlayTime + RECORD_TIME_STEP;
		dwLastRecordTime = dwPlayTime;
		if (lpTransCommand->WParam)
		{
			RecordFailCount = 0;
			if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR) AddChatBuff("Salvo com sucesso.");
		}
		else
		{
			RecordFailCount++;
			if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR) AddChatBuff("Falha ao salvar.");
		}


		cSinSiege.SetTaxRate(lpTransCommand->SParam);

		SetBlessCastleMaster(lpTransCommand->EParam, 0);

		break;

	case OpCode::OPCODE_BLESSCASTLE_TAX:

		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;
		cSinSiege.SetTaxRate(lpTransCommand->SParam);
		break;

	case OpCode::OPCODE_ADDEXP:
	case OpCode::OPCODE_ADDEXP_PARTY:

		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;

		lpChar = FindAutoPlayer(lpTransCommand->LParam);
		if (lpChar && !lpChar->RecvExp)
		{
			if (lpTransCommand->SParam == ((lpTransCommand->WParam * 3 + lpTransCommand->LParam * 13) * 2002))
			{

				CheckServerExp(pData->smMySock, lpTransCommand);

				setexp();
				AddExp(lpTransCommand->WParam);
				lpChar->RecvExp += lpTransCommand->WParam;
				addExp = lpTransCommand->WParam;

				if (IPData[1] == OpCode::OPCODE_ADDEXP)
				{
					CheckChangeJob3QuestItem(lpChar->smCharInfo.StatePoint);
				}
			}
			else
			{

				SendSetHackUser2(1800, lpTransCommand->WParam);
			}
		}
		else
		{
		}
		break;

	case OpCode::OPCODE_NEW_ADDEXP:
		smTRANS_COMMAND_QWORD* lpTransCommandQ;
		lpTransCommandQ = (smTRANS_COMMAND_QWORD*)pData->Buff;
		setexp();
		AddExp(lpTransCommandQ->WParam);
		break;

	case OpCode::OPCODE_SERVER_INFO:
		TRANS_SERVER_LIST	*lpTransServerList;

		lpTransServerList = (TRANS_SERVER_LIST *)pData->Buff;
		sinItemTime = lpTransServerList->dwServerTime_t;
		dwTime_ServerT = sinItemTime;
		dwTime_ConnectMS = GetCurrentTime();



		cnt = lpTransServerList->ClanServerCount;
		if (cnt)
		{
			cnt = lpTransServerList->ServerCount;
			web_DB_ip_port_init(lpTransServerList->ServerInfo[cnt].szServerIp1, lpTransServerList->ServerInfo[cnt].dwServerPort1,
				lpTransServerList->ServerInfo[cnt].szServerIp2, lpTransServerList->ServerInfo[cnt].dwServerPort2,
				lpTransServerList->ClanTicket);
		}


		CheckProcessModule();


		HoRecvMessage(IPData[1], pData->Buff);
		break;
	case GET_FAILED_ITEMS:
	{
		RestaureWindow::GetInstance()->ReceiveFailedItems((FailedItemsPckg*)pData->Buff);
		RestaureWindow::GetInstance()->OpenWindow();
		//RestaureWindow::GetInstance()->openFlag = true;
		break;
	}
	case OpCode::OPCODE_ID_SETUSERINFO:
		if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
		{

			TRANS_USERCHAR_INFO	*lpTransUserCharInfo = (TRANS_USERCHAR_INFO	*)pData->Buff;
			FILE	*fp;
			for (cnt = 0; cnt < lpTransUserCharInfo->PlayUserCount; cnt++)
			{
				if (!lpTransUserCharInfo->CharInfo[cnt].szModelName2[0])
				{
					fp = fopen(lpTransUserCharInfo->CharInfo[cnt].szModelName, "rb");
					if (!fp)
					{
						x = lstrlen(lpTransUserCharInfo->CharInfo[cnt].szModelName);
						lpTransUserCharInfo->CharInfo[cnt].szModelName[x - 1] = 'x';
						fp = fopen(lpTransUserCharInfo->CharInfo[cnt].szModelName, "rb");
					}
					if (fp)
					{
						fclose(fp);
					}
					else
					{
						strcpy_s(lpTransUserCharInfo->CharInfo[cnt].szModelName,
							"char\\monster\\hopy\\hopy.ini");
					}
				}
			}
		}

	case OpCode::OPCODE_ISRECORDDATA:
	case OpCode::OPCODE_INSRECORDDATA:
	case OpCode::OPCODE_FAILCONNECT:

		HoRecvMessage(IPData[1], pData->Buff);
		break;

	case OpCode::OPCODE_SHOP_ITEMLIST:



		ComparePotion();

		sinRecvMessage(IPData[1], pData->Buff);

		Send_GetBlessCastleTax();

		break;

	case OpCode::OPCODE_SKILL_MENU:
		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;


		if (lpCurPlayer->OnStageField >= 0)
		{

			if (dwQuestDelayTime > dwPlayTime) lpTransCommand->WParam = 0;

			sinSkillMaster(lpTransCommand->WParam);

			dwQuestDelayTime = dwPlayTime + 1000 * 5;
		}


		break;

	case OpCode::OPCODE_VERSION:

		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;

		if (pData->smMySock == smWsockDataServer)
		{
			memcpy(&TransServerConnectInfo, lpTransCommand, sizeof(smTRANS_COMMAND));
		}

		if (pData->smMySock == smWsockDataServer || pData->smMySock == smWsockServer)
		{
			CheckServerInfo(lpTransCommand);
		}
		break;

	case OpCode::OPCODE_CHECK_NETSTATE:


		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;

		dwTime = ConvSysTimeToGameTime(lpTransCommand->SParam);

		if (abs((long)dwGameWorldTime - (long)dwTime) > 10)
			dwGameWorldTime = dwTime;

		dwLastRecvGameServerTime = GetCurrentTime();
		rsRecvServer = TRUE;

		if (lpTransCommand->WParam && lpTransCommand->EParam)
		{

			dwMemFunChkCode = funcCheckMemSum(lpTransCommand->WParam, lpTransCommand->EParam);
			dwMemFunChkCode = (dwMemFunChkCode << 16) | (lpTransCommand->WParam & 0xFFFF);
		}

		
			
		break;

	case OpCode::OPCODE_CHECK_NETSTATE2:
	case OpCode::OPCODE_CHECK_NETSTATE20:
		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;

		dwLastRecvGameServerTime2 = GetCurrentTime();
		rsRecvDataServer = TRUE;

		if (lpTransCommand->WParam && lpTransCommand->EParam)
		{

			dwMemFunChkCode = funcCheckMemSum(lpTransCommand->WParam, lpTransCommand->EParam);
			dwMemFunChkCode = (dwMemFunChkCode << 16) | (lpTransCommand->WParam & 0xFFFF);
		}

		
		break;

	case OpCode::OPCODE_CHECK_NETSTATE3:
		dwLastRecvGameServerTime3 = GetCurrentTime();
		rsRecvUserServer = TRUE;
		
		break;

	case OpCode::OPCODE_CHECK_NETSTATE4:
	case OpCode::OPCODE_CHECK_NETSTATE5:
		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;

		if (AreaServerMode)
		{
			if (lpWSockServer_Area[0] && lpWSockServer_Area[0] == (smWINSOCK *)lpTransCommand->EParam)
			{
				lpWSockServer_Area[0]->dwDeadLockTime = GetCurrentTime();
				
			}
			if (lpWSockServer_Area[1] && lpWSockServer_Area[1] == (smWINSOCK *)lpTransCommand->EParam)
			{
				lpWSockServer_Area[1]->dwDeadLockTime = GetCurrentTime();
				
			}
		}
		else
		{
			dwLastRecvGameServerTime4 = GetCurrentTime();
			rsRecvExtendServer = TRUE;
			
		}
		break;

	case OpCode::OPCODE_WARPFIELD:

		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;

		if (lpTransCommand->WParam == rsSOD_FIELD &&
			lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->FieldCode == rsSOD_VILLAGE)
		{

			if (!BellatraEffectInitFlag)
			{
				CreateBellatraFontEffect();
				BellatraEffectInitFlag = TRUE;
			}

			if (SoD_SetFontEffect.eBL_Type != E_BL_LODING)
			{
				SetBellatraFontEffect(E_BL_LODING, &SoD_SetFontEffect);
				sSodScore.SodNextStageNum = -2;
				sSodScore.dwSoD_NextStageTime = dwPlayTime + 3000;
				sSodScore.NextRound = 0;
				StopBGM();
			}
		}


		CloseEachPlayer();

		WarpFieldNearPos(lpTransCommand->WParam, lpTransCommand->SParam, lpTransCommand->LParam, &x, &z);

		lpCurPlayer->SetPosi(lpTransCommand->SParam, 0, lpTransCommand->LParam, 0, 0, 0);
		TraceCameraPosi.x = lpCurPlayer->pX;
		TraceCameraPosi.y = lpCurPlayer->pY;
		TraceCameraPosi.z = lpCurPlayer->pZ;
		TraceTargetPosi.x = lpCurPlayer->pX;
		TraceTargetPosi.y = lpCurPlayer->pY;
		TraceTargetPosi.z = lpCurPlayer->pZ;


		lpCurPlayer->OnStageField = -1;
		if (smGameStage[0])
		{
			cnt = smGameStage[0]->GetFloorHeight(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, lpCurPlayer->Pattern->SizeHeight);
			lpCurPlayer->OnStageField = 0;
		}
		if (cnt == CLIP_OUT && smGameStage[1])
		{
			lpCurPlayer->OnStageField = 1;
		}
		break;

	case OpCode::OPCODE_TRADEITEMS:


		if (cTrade.OpenFlag && cTrade.TradeCharCode == ((TRANS_TRADEITEMS *)pData->Buff)->dwSender)
		{
			RecvTradeItems((TRANS_TRADEITEMS *)pData->Buff);
		}
		break;

	case OpCode::OPCODE_TRADE_ITEMKEY:


		if (DisconnectFlag)
			break;

		if (!TradeRecvItemKeyFlag)
		{
			if (RecvTradeSucessKey((TRANS_TRADE_ITEMKEY *)pData->Buff, &sTradeRecv) == TRUE)
			{
				TradeRecvItemKeyFlag = TRUE;

				if (TradeItemSucessFlag)
				{
					if (sTrade.Money) AddInvenMoney(-(sTrade.Money - 193));
					if (sTradeRecv.Money) AddInvenMoney(sTradeRecv.Money - 193);

					memset(sTrade.TradeItem, 0, sizeof(sITEM)*MAX_TRADE_ITEM);
					sTrade.Money = 0;
					ReformTrade(&sTrade);

					CloseEachPlayer();
					cTrade.CheckOkTradeItem();
					ResetPotion();
					SaveGameData();
					ResetInvenItemCode();
				}
			}
			else
			{

				cTrade.CancelTradeItem();
			}
		}
		break;

	case OpCode::OPCODE_TRADE_READYITEM:



		if (DisconnectFlag)
			break;
		if (TradeItemSucessFlag)
			break;

		if (sTrade.CheckFlag)
		{

			TradeItemSucessFlag = TRUE;
			sTradeRecv.CheckFlag = TRUE;
			if (RecvTradeCheckItem((TRANS_TRADE_CHECKITEM *)pData->Buff) == TRUE)
			{
				SendTradeSucessKey(((TRANS_TRADE_CHECKITEM *)pData->Buff)->dwSender);

				if (TradeRecvItemKeyFlag)
				{
					if (sTrade.Money) AddInvenMoney(-(sTrade.Money - 193));
					if (sTradeRecv.Money) AddInvenMoney(sTradeRecv.Money - 193);

					memset(sTrade.TradeItem, 0, sizeof(sITEM)*MAX_TRADE_ITEM);
					sTrade.Money = 0;
					ReformTrade(&sTrade);

					CloseEachPlayer();
					cTrade.CheckOkTradeItem();
					ResetPotion();
					SaveGameData();
					ResetInvenItemCode();
				}
			}
			break;
		}




		cTrade.CancelTradeItem();
		break;

	case OpCode::OPCODE_TRADE_REQUST:

		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;
		lpChar = FindAutoPlayer(lpTransCommand->SParam);

		if (lpChar && lpChar->DisplayFlag && lpChar->smCharInfo.szName[0] &&
			!cWareHouse.OpenFlag && !cCraftItem.OpenFlag && !cAging.OpenFlag && !cMyShop.OpenFlag || cMixtureReset.OpenFlag)
		{

			switch (lpTransCommand->LParam)
			{
			case 0:

				if (GetTradeDistance(lpChar) == FALSE) break;

				if (lpCurPlayer->smCharInfo.Weight[0] > lpCurPlayer->smCharInfo.Weight[1])
				{
					cMessageBox.ShowMessageEvent(mgWeightOver);
					break;
				}



				if (!cTrade.OpenFlag)
				{
					sinRequestTrade(lpTransCommand->SParam, lpChar->smCharInfo.szName);
					if (DispEachMode == 0)
					{
						OpenEachPlayer(lpChar);
						DispEachMode = 0;
						if (lpChar) InterfaceParty.latest_Insert(lpChar->smCharInfo.szName);
					}
				}
				break;
			case 1:

				if (GetTradeDistance(lpChar) == FALSE) break;
				if (cShop.OpenFlag) break;

				if (lpCurPlayer->smCharInfo.Weight[0] > lpCurPlayer->smCharInfo.Weight[1])
				{
					cMessageBox.ShowMessageEvent(mgWeightOver);
					break;
				}


				if (!cTrade.OpenFlag)
					SendRequestTrade(lpTransCommand->SParam, 2);
			case 2:

				if (!cTrade.OpenFlag)
				{
					cTrade.OpenFlag = TRUE;
					cInvenTory.OpenFlag = TRUE;
					cInterFace.CheckAllBox(SIN_TRADE);
					cTrade.TradeCharCode = lpTransCommand->SParam;
					TradeItemSucessFlag = 0;
					TradeRecvItemKeyFlag = 0;
					TradeSendSucessFlag = 0;
					TradeItemCancelCount = 0;
					TransLastRecvTrade.code = 0;
					memset(&sTrade, 0, sizeof(sTRADE));
					memset(&sTradeRecv, 0, sizeof(sTRADE));
					ReformTrade((void *)&sTrade);
					ReformTrade((void *)&sTradeRecv);
					strcpy_s(cTrade.szTradeCharName, lpChar->smCharInfo.szName);

					if (lpCurPlayer->MoveFlag)
					{

						CancelAttack();
						lpCurPlayer->MoveFlag = 0;
					}
					EachTradeButton = 0;
					OpenEachPlayer(lpChar);
					DispEachMode = TRUE;
					if (lpChar) InterfaceParty.latest_Insert(lpChar->smCharInfo.szName);
				}
				break;
			case 3:

				if (cTrade.OpenFlag)
				{
					if (TradeRecvItemKeyFlag)
					{
						memset(sTrade.TradeItem, 0, sizeof(sITEM)*MAX_TRADE_ITEM);
						sTrade.Money = 0;
						ReformTrade(&sTrade);
					}
					cTrade.CancelTradeItem();
				}
				break;
			}
		}
		break;

	case OpCode::OPCODE_FINDCRACK:


		CheckCracker((TRANS_FIND_CRACKER *)pData->Buff);
		break;


	case OpCode::OPCODE_PARTY_REQUEST:

		if (!cWareHouse.OpenFlag)
		{
			lpTransCharCommand = (smTRANS_CHAR_COMMAND*)pData->Buff;
			SetInterfaceParty(lpTransCharCommand->szName, lpTransCharCommand->WParam);
		}
		break;

	case OpCode::OPCODE_PARTY_UPDATE:

		TRANS_PARTY_USERS* lpTransPartyUsers;

		lpTransPartyUsers = (TRANS_PARTY_USERS*)pData->Buff;

		/*if(!InterfaceParty.PartyMemberCount)
		{

			InterfaceParty.Main_menuSet(1);
			if(InterfaceParty.PartyPosState == PARTY_NONE)	ShowParty();
		}


		InterfaceParty.MouseDownPartyMember = -1;*/

		cParty.iPartyMode = lpTransPartyUsers->iPartyMode;


		for (cnt = 0; cnt < lpTransPartyUsers->PartyUserCount; cnt++)
		{

			/*hoPartyMember	save_PM;
			ZeroMemory((void*)&save_PM, sizeof(save_PM));

			save_PM.ChrCode = lpTransPartyUsers->PartyUser[cnt].dwObjectSerial;
			save_PM.Life = (lpTransPartyUsers->PartyUser[cnt].Life[0] * 100) / lpTransPartyUsers->PartyUser[cnt].Life[1];
			save_PM.Level = lpTransPartyUsers->PartyUser[cnt].Level;
			save_PM.CharacterPos.x = lpTransPartyUsers->PartyUser[cnt].x;
			save_PM.CharacterPos.z = lpTransPartyUsers->PartyUser[cnt].z;
			save_PM.CharacterPos.y = 0;
			strcpy_s(save_PM.Name, lpTransPartyUsers->PartyUser[cnt].szName);
			strcpy_s(save_PM.ModelName1, lpTransPartyUsers->PartyUser[cnt].szModelName);
			strcpy_s(save_PM.ModelName2, lpTransPartyUsers->PartyUser[cnt].szModelName2);
			save_PM.JangFlag = 0;
			if(cnt == 0)
				save_PM.JangFlag = TRUE;

			InterfaceParty.AddMember(&save_PM, cnt);*/

			cParty.AddMember(&lpTransPartyUsers->PartyUser[cnt], cnt);
		}
		//InterfaceParty.AddMember_memberSu(lpTransPartyUsers->PartyUserCount);


		RequestPartyPlayers(0);
		break;

	case OpCode::OPCODE_PARTY_PLAYUPDATE:

	{
		TRANS_PARTY_PLAYINFO* lpTransPartyPlayInfo;
		lpTransPartyPlayInfo = (TRANS_PARTY_PLAYINFO*)pData->Buff;
		int count = lpTransPartyPlayInfo->PartyUserCount;

		if (count < 0 || count >(PARTY_PLAYER_MAX - 1))
		{
			break;
		}

		for (cnt = 0; cnt < count; cnt++)
		{

			/*hoPartyMember	save_PM;
			ZeroMemory((void*)&save_PM, sizeof(save_PM));

			save_PM.ChrCode = lpTransPartyPlayInfo->PlayInfo[cnt].dwObjectSerial;
			save_PM.Life = (lpTransPartyPlayInfo->PlayInfo[cnt].Life[0] * 100) / lpTransPartyPlayInfo->PlayInfo[cnt].Life[1];
			save_PM.Level = lpTransPartyPlayInfo->PlayInfo[cnt].Level;
			save_PM.CharacterPos.x = lpTransPartyPlayInfo->PlayInfo[cnt].x;
			save_PM.CharacterPos.z = lpTransPartyPlayInfo->PlayInfo[cnt].z;

			InterfaceParty.PARTY_PLAYUPDATE(&save_PM, cnt);*/
			cParty.UpdateMember(&lpTransPartyPlayInfo->PlayInfo[cnt]);
		}

		if (lpTransPartyPlayInfo->PlayInfo[0].dwObjectSerial == lpCurPlayer->dwObjectSerial)
		{

			if (smWsockServer && smWsockServer != smWsockUserServer)
			{
				smWsockServer->Send((char*)lpTransPartyPlayInfo, lpTransPartyPlayInfo->size, TRUE);
			}
			if (smWsockExtendServer && smWsockExtendServer != smWsockServer)
			{
				smWsockExtendServer->Send((char*)lpTransPartyPlayInfo, lpTransPartyPlayInfo->size, TRUE);
			}
		}
	}
	break;

	case OpCode::OPCODE_PARTY_RELEASE:

		lpTransCommand = (smTRANS_COMMAND*)pData->Buff;

		//InterfaceParty.PARTY_RELEASE();
		cParty.Clear();

		RequestPartyPlayers(0);


		if (smWsockServer && smWsockServer != smWsockUserServer)
		{
			smWsockServer->Send((char*)lpTransCommand, lpTransCommand->size, TRUE);
		}

		if (smWsockExtendServer && smWsockExtendServer != smWsockServer)
		{
			smWsockExtendServer->Send((char*)lpTransCommand, lpTransCommand->size, TRUE);
		}
		break;

	case OpCode::OPCODE_WAREHOUSE:


		if (!cWareHouse.OpenFlag && !cTrade.OpenFlag && !cMyShop.OpenFlag)
		{
			if (LoadWareHouse((TRANS_WAREHOUSE*)pData->Buff, &sWareHouse) == TRUE)
			{
				cWareHouse.LoadWareHouseItemIamge();
				cWareHouse.BackUpInvenItem();
				ResetInvenItemCode();
				ResetInvenMoney();
			}
		}
		break;

	case OpCode::OPCODE_OPEN_WAREHOUSE:

		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;

		if (lpCurPlayer->smCharInfo.Weight[0] > lpCurPlayer->smCharInfo.Weight[1])
		{
			cMessageBox.ShowMessageEvent(mgWeightOver);
			break;
		}

		if (smWsockDataServer && !cWareHouse.OpenFlag && !cTrade.OpenFlag)
		{
			smWsockDataServer->Send((char *)lpTransCommand, lpTransCommand->size, TRUE);
		}
		break;
	case PACKET_KILL:
	{
		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;
		if (!MatBuffKill[0])
		{
			MatBuffKill[0] = CreateTextureMaterial("game\\images\\kill\\2.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
			MatBuffKill[1] = CreateTextureMaterial("game\\images\\kill\\3.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
			MatBuffKill[2] = CreateTextureMaterial("game\\images\\kill\\4.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
			MatBuffKill[3] = CreateTextureMaterial("game\\images\\kill\\5.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
			ReadTextures();
		}

		if (lpTransCommand->WParam > 1)
		{
			for (int i = 0; i < 32; i++)
			{
				if (!BuffKill[i].flag)
				{
					BuffKill[i].flag = 1;
					if (lpTransCommand->WParam == 2)
						BuffKill[i].image = MatBuffKill[0];
					else
						if (lpTransCommand->WParam == 3)
							BuffKill[i].image = MatBuffKill[1];
						else
							if (lpTransCommand->WParam == 4)
								BuffKill[i].image = MatBuffKill[2];
							else
								if (lpTransCommand->WParam >= 5)
									BuffKill[i].image = MatBuffKill[3];
					BuffKill[i].x = 0;
					BuffKill[i].y = 100;
					BuffKill[i].alpha = 0;
					ReadTextures();
					break;
				}
			}
		}
	}
	break;
	case smTRANSCODE_IT_IS_GLADIATOR:
	{
		
	}
	break;
	case smTRANSCODE_YOU_ARE_GLADIATOR:
	{

		if (!MatG)
		{
			MatG = CreateTextureMaterial("image\\Sinimage\\skill\\keep\\gladiator.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
			ReadTextures();
		}

		if (cSkill.SearchContiueSkillCODE(PLAYER_ARENA) != PLAYER_ARENA)
		{
			sSKILL TempSkill;
			memset(&TempSkill, 0, sizeof(sSKILL));
			TempSkill.CODE = PLAYER_ARENA;
			TempSkill.UseTime = 604800;
			TempSkill.Point = 1;
			TempSkill.MatIcon = MatG;
			lpCurPlayer->PlayGladiador = TRUE;
			sinContinueSkillSet(&TempSkill);
			sinPlaySound(SIN_SOUND_EAT_POTION2);
			lpTransChatMessage = (TRANS_CHATMESSAGE*)pData->Buff;
			lstrcpy(szReiArena, lpTransChatMessage->szMessage);

	}

	}
	break;

	case OpCode::BLESS_CROWN:
	{
		PACKET_CROWN* packet = (PACKET_CROWN*)pData->Buff;

		ClanTop2 = packet->Silver;
		ClanTop3 = packet->Bronze;

		if (lpCurPlayer->smCharInfo.ClassClan && GetClanCode(lpCurPlayer->smCharInfo.ClassClan) == packet->Silver)
			lpCurPlayer->BlessCrown = 2;
		else
			if (lpCurPlayer->smCharInfo.ClassClan && GetClanCode(lpCurPlayer->smCharInfo.ClassClan) == packet->Bronze)
				lpCurPlayer->BlessCrown = 3;
			else
				lpCurPlayer->BlessCrown = 0;
	}
	break;

	case OpCode::OPCODE_BUFFS:
	{
		PACKET_BUFFS* packet = (PACKET_BUFFS*)pData->Buff;

		SetBoss1Bonus1 = packet->SetBoss1Bonus1;
		SetBoss1Bonus2 = packet->SetBoss1Bonus2;
		SetBoss2Bonus1 = packet->SetBoss2Bonus1;
		SetBoss2Bonus2 = packet->SetBoss2Bonus2;
		cInvenTory.SetItemToChar();
	}
	break;


	case smTRANSCODE_YOU_NOT_ARE_GLADIATOR:
		cSkill.CancelContinueSkill(PLAYER_ARENA);
		lpCurPlayer->PlayGladiador = FALSE;
		break;

		
	case smTRANSCODE_RESETBP:
		cSkill.CancelContinueSkill(REIPVP);
		bReiPVP = FALSE;
		lpCurPlayer->PlayCursePvP = FALSE;
		break;
	case OPEN_RECOVERY_AGING_NPC:
		RestaureWindow::GetInstance()->getFailedItems();	
		break;
	case smTRANSCODE_OPEN_TSHOP:
		TShop::GetInstance()->Open();
		break;
	case TPACKET_SEND_ITEM_GAME:
		TShop::GetInstance()->RecvItemToServer((SHOP*)pData->Buff);
		break;
	case TPACKET_SEND_COIN_GAME:
		TShop::GetInstance()->RecvCoinToServer((SHOP_COIN*)pData->Buff);
		break;

	case smTRANSCODE_OPEN_SHOP:
		Shop::GetInstance()->Open();
		break;
	case PACKET_SEND_ITEM_GAME:
		Shop::GetInstance()->RecvItemToServer((SHOP*)pData->Buff);
		break;
	case PACKET_SEND_COIN_GAME:
		Shop::GetInstance()->RecvCoinToServer((SHOP_COIN*)pData->Buff);
		break;

	case OpCode::OPCODE_OPEN_MIXITEM:

		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;

		if (lpCurPlayer->smCharInfo.Weight[0] > lpCurPlayer->smCharInfo.Weight[1])
		{
			cMessageBox.ShowMessageEvent(mgWeightOver);
			break;
		}

		if (lpTransCommand->WParam == 200)
		{

			cInterFace.CheckAllBox(SIN_CRAFTITEM);
			cCraftItem.ForceFlag = 1;
		}
		else
			cInterFace.CheckAllBox(SIN_CRAFTITEM);

		break;

	case OpCode::OPCODE_OPEN_COLLECT:

		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;
		if (lpTransCommand->WParam == 5)
		{

			cSinSod2.ShowSod2MessageBox();
		}
		else
			sinShowEventSmashingTV();

		break;

	case OpCode::OPCODE_OPEN_EVENTGIFT:



		if (sinChar->wVersion[1] == 1)
			cMessageBox.ShowMessage(MESSAGE_ALREADY_INITSTATE);
		else
			cMessageBox.ShowMessage3(MESSAGE_EVENT_GYUNGFUM, "");

		break;

	case OpCode::OPCODE_OPEN_AGING:

		if (lpCurPlayer->smCharInfo.Weight[0] > lpCurPlayer->smCharInfo.Weight[1])
		{
			cMessageBox.ShowMessageEvent(mgWeightOver);
			break;
		}
		cInterFace.CheckAllBox(SIN_AGING);
		break;
	case OpCode::OPCODE_OPEN_SMELTING:

		if (lpCurPlayer->smCharInfo.Weight[0] > lpCurPlayer->smCharInfo.Weight[1])
		{
			cMessageBox.ShowMessageEvent(mgWeightOver);
			break;
		}
		cInterFace.CheckAllBox(SIN_SMELTING);
		break;
	case OpCode::OPCODE_OPEN_MANUFACTURE:

		if (lpCurPlayer->smCharInfo.Weight[0] > lpCurPlayer->smCharInfo.Weight[1])
		{
			cMessageBox.ShowMessageEvent(mgWeightOver);
			break;
		}
		cInterFace.CheckAllBox(SIN_MANUFACTURE);
		break;
	case OpCode::OPCODE_OPEN_MIXTURE_RESET:

		if (lpCurPlayer->smCharInfo.Weight[0] > lpCurPlayer->smCharInfo.Weight[1])
		{
			cMessageBox.ShowMessageEvent(mgWeightOver);
			break;
		}
		cInterFace.CheckAllBox(SIN_MIXTURE_RESET);
		break;
	case OpCode::OPCODE_SAVETHROWITEM2:

		ThrowItemToServer((smTRANS_COMMAND_EX *)pData->Buff);
		break;

	case OpCode::OPCODE_CLOSECLIENT:
		//LOG_GAME
		DisconnectServerCode = 0;
		Log::getInstance()->output(LOG_GAME, "SetDisconnectFlag: 13");
		DisconnectFlag = GetCurrentTime();
		break;

	case OpCode::OPCODE_PLAYERKILLING:

		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;

		if (DeadPlayerExp(lpCurPlayer) == TRUE)
		{
		}
		break;

	case OpCode::OPCODE_SEND_DATASERVER:

		if (smWsockDataServer)
		{
			smWsockDataServer->Send(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff, ((smTRANS_COMMAND *)(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff))->size, TRUE);
		}
		break;

	case OpCode::OPCODE_SEND_GAMESERVER:

		if (smWsockServer)
		{
			smWsockServer->Send(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff, ((smTRANS_COMMAND *)(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff))->size, TRUE);
		}
		if (smWsockUserServer && smWsockUserServer != smWsockServer)
		{
			smWsockUserServer->Send(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff, ((smTRANS_COMMAND *)(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff))->size, TRUE);
		}
		if (smWsockExtendServer && smWsockExtendServer != smWsockServer)
		{
			smWsockExtendServer->Send(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff, ((smTRANS_COMMAND *)(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff))->size, TRUE);
		}
		break;

	case OpCode::OPCODE_SEND_AREASERVER:

		lpsmSock = GetAreaServerSock();
		if (lpsmSock)
			lpsmSock->Send(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff, ((smTRANS_COMMAND *)(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff))->size, TRUE);
		else
			smWsockServer->Send(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff, ((smTRANS_COMMAND *)(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff))->size, TRUE);

		break;

	case OpCode::OPCODE_SEND_AGAME_SERVER:

		lpsmSock = GetAreaServerSock();

		for (int i = 0; i < SINUPKEEPITEM_MAX; i++)
		{

			if (chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::THIRD_EYES)
			{
				if (chaPremiumitem.UpKeepItem[i].IconTime[1] - chaPremiumitem.UpKeepItem[i].IconTime[0] <= 0)
				{
					chaPremiumitem.m_ThirdEyesTime = 0;
				}
			}

			else if (chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::EXPUP_POTION)
			{
				if (chaPremiumitem.UpKeepItem[i].IconTime[1] - chaPremiumitem.UpKeepItem[i].IconTime[0] <= 0)
				{
					chaPremiumitem.m_ExpUpPotionTime = 0;
				}
			}

			else if (chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::VAMPIRIC_CUS)
			{
				if (chaPremiumitem.UpKeepItem[i].IconTime[1] - chaPremiumitem.UpKeepItem[i].IconTime[0] <= 0)
				{
					chaPremiumitem.m_VampiricCuspidTime = 0;
				}
			}

			else if (chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::MANA_RECHAR_P)
			{
				if (chaPremiumitem.UpKeepItem[i].IconTime[1] - chaPremiumitem.UpKeepItem[i].IconTime[0] <= 0)
				{
					chaPremiumitem.m_ManaRechargingPTime = 0;
				}
			}
		}



		if (lpsmSock)
		{
			lpsmSock->Send(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff, ((smTRANS_COMMAND *)(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff))->size, TRUE);

			if (lpsmSock != smWsockServer)
				smWsockServer->Send(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff, ((smTRANS_COMMAND *)(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff))->size, TRUE);
		}
		else
			smWsockServer->Send(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff, ((smTRANS_COMMAND *)(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff))->size, TRUE);

		break;

	case OpCode::OPCODE_FUNCTION_MEM2:

		RecvMemFuncData2((TRANS_FUNC_MEMORY *)pData->Buff);
		break;

	case OpCode::OPCODE_CRAFTITEM:

		if (((sCRAFTITEM_SERVER *)pData->Buff)->Result == TRUE)
		{

			cCraftItem.sinRecvCraftItemResult((sCRAFTITEM_SERVER *)pData->Buff);

			cInvenTory.DeleteInvenItemToServer(((sCRAFTITEM_SERVER *)pData->Buff)->DesCraftItem.sItemInfo.CODE,
				((sCRAFTITEM_SERVER *)pData->Buff)->DesCraftItem.sItemInfo.BackUpKey,
				((sCRAFTITEM_SERVER *)pData->Buff)->DesCraftItem.sItemInfo.BackUpChkSum);



			if (FindInvenItem(((sCRAFTITEM_SERVER *)pData->Buff)->DesCraftItem.sItemInfo.CODE,
				((sCRAFTITEM_SERVER *)pData->Buff)->DesCraftItem.sItemInfo.BackUpKey,
				((sCRAFTITEM_SERVER *)pData->Buff)->DesCraftItem.sItemInfo.BackUpChkSum) != 0)
			{

				SendInvenItemError(0, ((sCRAFTITEM_SERVER *)pData->Buff)->DesCraftItem.sItemInfo.CODE,
					((sCRAFTITEM_SERVER *)pData->Buff)->DesCraftItem.sItemInfo.BackUpKey,
					((sCRAFTITEM_SERVER *)pData->Buff)->DesCraftItem.sItemInfo.BackUpChkSum);
				break;
			}

			ResetInvenItemCode();
			SaveGameData();
			break;

		}
		cCraftItem.sinRecvCraftItemResult((sCRAFTITEM_SERVER *)pData->Buff);
		ResetInvenItemCode();
		SaveGameData();
		break;

	case OpCode::OPCODE_AGINGITEM:

		if (((sCRAFTITEM_SERVER *)pData->Buff)->Result)
		{

			cAging.sinRecvAgingItemResult((sCRAFTITEM_SERVER *)pData->Buff);

			cInvenTory.DeleteInvenItemToServer(((sCRAFTITEM_SERVER *)pData->Buff)->DesCraftItem.sItemInfo.CODE,
				((sCRAFTITEM_SERVER *)pData->Buff)->DesCraftItem.sItemInfo.BackUpKey,
				((sCRAFTITEM_SERVER *)pData->Buff)->DesCraftItem.sItemInfo.BackUpChkSum);



			if (FindInvenItem(((sCRAFTITEM_SERVER *)pData->Buff)->DesCraftItem.sItemInfo.CODE,
				((sCRAFTITEM_SERVER *)pData->Buff)->DesCraftItem.sItemInfo.BackUpKey,
				((sCRAFTITEM_SERVER *)pData->Buff)->DesCraftItem.sItemInfo.BackUpChkSum) != 0)
			{

				SendInvenItemError(0, ((sCRAFTITEM_SERVER *)pData->Buff)->DesCraftItem.sItemInfo.CODE,
					((sCRAFTITEM_SERVER *)pData->Buff)->DesCraftItem.sItemInfo.BackUpKey,
					((sCRAFTITEM_SERVER *)pData->Buff)->DesCraftItem.sItemInfo.BackUpChkSum);
				break;
			}

			ResetInvenItemCode();
			SaveGameData();
			break;

		}
		cAging.sinRecvAgingItemResult((sCRAFTITEM_SERVER *)pData->Buff);
		ResetInvenItemCode();
		SaveGameData();
		break;

	case OpCode::OPCODE_AGING_UPGRADE:

		sinRecvAgingIncreStateItem(&((TRANS_ITEMINFO *)pData->Buff)->Item);
		TransAgingItemFlag = FALSE;
		ResetInvenItemCode();
		SaveGameData();


		SendCommandUser(smCOMMNAD_USER_AGINGUP, 0, 0, 0);

		if ((((TRANS_ITEMINFO *)pData->Buff)->Item).CODE == cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE &&
			cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.ItemName[0])
		{

			if (lpCurPlayer->smCharInfo.JOB_CODE == 9 && (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE&sinITEM_MASK2) == sinWD1)
			{
				sinSetCharItem(cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE, 2, TRUE);
				sinSetCharItem(cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE, 4, TRUE);
			}
			else
				sinSetCharItem(cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE, cInvenTory.InvenItem[sInven[0].ItemIndex - 1].SetModelPosi, TRUE);
		}
		else
			if ((((TRANS_ITEMINFO *)pData->Buff)->Item).CODE == cInvenTory.InvenItem[sInven[1].ItemIndex - 1].CODE &&
				cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sItemInfo.ItemName[0])
			{

				if (lpCurPlayer->smCharInfo.JOB_CODE == 9 && (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE&sinITEM_MASK2) == sinWD1)
				{
					sinSetCharItem(cInvenTory.InvenItem[sInven[1].ItemIndex - 1].CODE, 2, TRUE);
					sinSetCharItem(cInvenTory.InvenItem[sInven[1].ItemIndex - 1].CODE, 4, TRUE);
				}
				else
					sinSetCharItem(cInvenTory.InvenItem[sInven[1].ItemIndex - 1].CODE, cInvenTory.InvenItem[sInven[1].ItemIndex - 1].SetModelPosi, TRUE);

			}
		break;

	case OpCode::OPCODE_MAKE_LINKCORE:

		cInvenTory.RecvLinkCore(&((TRANS_ITEMINFO *)pData->Buff)->Item);
		ResetInvenItemCode();
		SaveGameData();
		break;

	case OpCode::OPCODE_USE_LINKCORE:

		SucessLinkCore((smTRANS_COMMAND_EX *)pData->Buff);
		break;

	case OpCode::OPCODE_WINGITEM:


		RecvWingItem((sCRAFTITEM_SERVER *)pData->Buff);
		ResetInvenItemCode();
		SaveGameData();
		break;

	case OpCode::OPCODE_ITEM_FORCEORB:

		RecvForceOrbItem((TRANS_ITEMINFO_GROUP2 *)pData->Buff);
		ResetInvenItemCode();
		SaveGameData();
		break;

	case OpCode::OPCODE_SHOPTITEM:

		if ((((TRANS_BUY_SHOPITEM *)pData->Buff)->sItem.sItemInfo.CODE&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
		{
			ComparePotion();
		}


		cShop.RecvBuyItemToServer(&((TRANS_BUY_SHOPITEM *)pData->Buff)->sItem, ((TRANS_BUY_SHOPITEM *)pData->Buff)->ItemCount);

		if ((((TRANS_BUY_SHOPITEM *)pData->Buff)->sItem.sItemInfo.CODE&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
		{

			ResetPotion();
		}

		ResetInvenItemCode();
		break;

	case OpCode::OPCODE_SHOP_SELLITEM:

		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;


		if (FindInvenItem(lpTransCommand->WParam, lpTransCommand->LParam, lpTransCommand->SParam) == 0)
		{
			CheckCharForm();
			sinPlusMoney(lpTransCommand->EParam);
			ReformCharForm();
			AddInvenMoney(lpTransCommand->EParam);
		}
		else
		{
			SendInvenItemError(0, lpTransCommand->WParam, lpTransCommand->LParam, lpTransCommand->SParam);
		}
		break;

	case OpCode::OPCODE_CHECKITEM:
	case OpCode::OPCODE_ERRORITEM:
	case OpCode::OPCODE_CLEARPOTION:

		RecvCheckItemFromServer((TRANS_ITEM_CODE *)pData->Buff);
		break;

	case OpCode::OPCODE_SHOWITEMINFO_PERF:
		RecvItemInfoPerf((TRANS_ITEMINFO *)pData->Buff);
		break;

	case OpCode::OPCODE_GETCLIENT_FUNCPOS:

		SendClientFuncPos();
		break;

	case OpCode::OPCODE_FUNCTION_MEM:

		RecvMemFuncData((TRANS_FUNC_MEMORY *)pData->Buff);
		break;

	case OpCode::OPCODE_PARTY_POTION:

		SetPartyPosion((smTRANS_COMMAND *)pData->Buff);
		break;

	case OpCode::OPCODE_HEALING:
	case OpCode::OPCODE_GRAND_HEALING:
	case OpCode::OPCODE_VAMPRIC_CUSPID:
	case OpCode::OPCODE_VAMPRIC_CUSPID_EX:
	case OpCode::OPCODE_MANA_RECHARGING:

		SetPartyPosion((smTRANS_COMMAND *)pData->Buff);
		break;

	case OpCode::OPCODE_SAVECLIENT:

		SaveGameData();
		break;


	case smTRANSCODE_POINT_BATTLE_ARENA:
	{
		BATTLE_ARENA_POINT * packet = (BATTLE_ARENA_POINT *)pData->Buff;
		memcpy(&Battle, packet, sizeof(BATTLE_ARENA_POINT));
	}
	break;

	case smTRANSCODE_ENTER_BATTLE_ARENA:
		switch (EventBattleArena)
		{
		case 1://Arena de Batalha
			WarpField2(50);
			break;
		case 3://Boss Mundo
			WarpField2(32);
			break;
		}
		
		break;
	case smTRANSCODE_TIME_BATTLE_ARENA:
	{
		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;
		EventBattleArena = lpTransCommand->WParam;
		EventBattleArenaTime = lpTransCommand->LParam;
	}
	break;
	case smTRANSCODE_CLOSE_BOSS_MUNDO:
		EventBattleArena = 0;
		WarpField2(3);
		break;
	case smTRANSCODE_CLOSE_BATTLE_ARENA:
		EventBattleArena = 0;
		WarpField2(3);
		NotGladiador();
		AddChatBuff("Infelizmente você não foi o vencedor , tente amanhã.");
		break;

	case smTRANSCODE_CONG_BATTLE_ARENA:
		EventBattleArena = 0;
		WarpField2(3);
		Gladiador();
		AddChatBuff("Parabéns voçê foi o vencedor da Arena de Batalha.");
		//cSinHelp.sinShowHelp(SIN_HELP_KIND_BATTLE_ARENA, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\BattleArena_6.sin");
		break;

	case smTRANSCODE_UPDATE_DIARY:
	{
		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;
		QuestDiaryState = lpTransCommand->LParam;
		QuestDiaryKill1 = lpTransCommand->WParam;
		QuestDiaryKill2 = lpTransCommand->SParam;

		if (QuestDiaryState == 0 && cSkill.SearchContiueSkillCODE(QUEST_DIARY) == QUEST_DIARY)
			cSkill.CancelContinueSkill(QUEST_DIARY);
		else
		{
			if (QuestDiaryState == 1 && cSkill.SearchContiueSkillCODE(QUEST_DIARY) != QUEST_DIARY)
			{
				if (!MatQD)
				{
					MatG = CreateTextureMaterial("image\\Sinimage\\skill\\keep\\QuestTimer.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
					ReadTextures();
				}

				sSKILL TempSkill;
				memset(&TempSkill, 0, sizeof(sSKILL));
				TempSkill.CODE = QUEST_DIARY;
				TempSkill.UseTime = 604800;
				TempSkill.Point = 1;
				TempSkill.MatIcon = MatG;
				sinContinueSkillSet(&TempSkill);
				sinPlaySound(SIN_SOUND_EAT_POTION2);
			}
		}
		if (QuestDiaryState == 2)
			cSkill.CancelContinueSkill(QUEST_DIARY);
	}
	break;

	case smTRANSCODE_UPDATE_BATTLE_LEVEL:
	{
		
		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;
		CharBattleLevel = lpTransCommand->LParam;
		CharBattleExp1 = lpTransCommand->WParam;
		CharBattleExp2 = lpTransCommand->SParam;

		if (cSkill.SearchContiueSkillCODE(BATTLE_LEVEL) != BATTLE_LEVEL && CharBattleLevel)
		{
			if (!MatB)
			{
				MatB = CreateTextureMaterial("image\\Sinimage\\skill\\keep\\battle.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
				ReadTextures();
			}

			sSKILL TempSkill;
			memset(&TempSkill, 0, sizeof(sSKILL));
			TempSkill.CODE = BATTLE_LEVEL;
			TempSkill.UseTime = 604800;
			TempSkill.Point = CharBattleLevel;
			TempSkill.MatIcon = MatB;
			sinContinueSkillSet(&TempSkill);
			lpCurPlayer->BattleLevel = TRUE;
			sinPlaySound(SIN_SOUND_EAT_POTION2);
		}
		else
		{
			for (int i = 0; i < MAX_CONTINUE_SKILL; i++)
			{
				if (ContinueSkill[i].Flag)
				{
					if (ContinueSkill[i].CODE == BATTLE_LEVEL)
					{
						ContinueSkill[i].Point = CharBattleLevel;
						break;
					}
				}
			}
		}
	}
	break;

	case smTRANSCODE_OPEN_PROGRESS_DIARY:
	{
		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;

		switch (lpTransCommand->LParam)
		{
		case 0:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST_DIARY, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\QuestDiary_1.sin");
			break;
		case 1:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST_DIARY, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\QuestDiary_2.sin");
			break;
		case 2:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST_DIARY, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\QuestDiary_3.sin");
			break;
		}

		QuestDiaryState = lpTransCommand->LParam;
		QuestDiaryKill1 = lpTransCommand->WParam;
		QuestDiaryKill2 = lpTransCommand->SParam;
	}
	break;

		case smTRANSCODE_OPEN_BATTLE_ARENA:
	{
		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;

		EventBattleArena = lpTransCommand->LParam;

		Battle::GetInstance()->Open();

		/*
		switch (EventBattleArena)
		{
		case 0://Desativado
			cSinHelp.sinShowHelp(SIN_HELP_KIND_BATTLE_ARENA, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\BattleArena_1.sin");
			break;
		case 1://Abre Battle Arena
			cSinHelp.sinShowHelp(SIN_HELP_KIND_BATTLE_ARENA, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\BattleArena_2.sin");
			break;
		case 2://Evento Iniciado
			cSinHelp.sinShowHelp(SIN_HELP_KIND_BATTLE_ARENA, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\BattleArena_3.sin");
			break;
		case 3://Boss Mundo
			cSinHelp.sinShowHelp(SIN_HELP_KIND_BATTLE_ARENA, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\BattleArena_4.sin");
			break;
		}
		*/
		
	}
	break;

	case OpCode::OPCODE_DEAD_PLAYER:

		if (lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_DEAD)
		{
			lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_DEAD);
			sinSetLife(0);
			ReformCharForm();
			CharPlaySound(lpCurPlayer);
			DeadPlayerExp(lpCurPlayer);
			sinCheckQuest85Die();
			SaveGameData();
			ResetEnergyGraph(0);
		}
		break;

	case OpCode::OPCODE_COMMAND_USER:

		RecvCommandUser((smTRANS_COMMAND_EX *)pData->Buff);
		break;

	case OpCode::OPCODE_OPEN_CLANMENU:

		void CLANmenu_meetNPC();
		CLANmenu_meetNPC();


		if (!lpCurPlayer->smCharInfo.dwEventTime_T && smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR && VRKeyBuff[VK_CONTROL])
		{
			ChangeBigHeadMode((rand() % 2) + 1, 60 * 5);
			StartSkill(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, SKILL_UP1);
			SkillPlaySound(SKILL_SOUND_LEARN, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
		}
		break;

	case OpCode::OPCODE_COMIC_SKIN:

		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;
		if (!lpCurPlayer->smCharInfo.dwEventTime_T)
		{
			ChangeBigHeadMode(lpTransCommand->WParam, lpTransCommand->LParam);
			StartSkill(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, SKILL_UP1);
			SkillPlaySound(SKILL_SOUND_LEARN, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);


			if (!lpTransCommand->SParam)
				cInvenTory.IncreViewDamage(15);
		}
		break;

	case OpCode::OPCODE_CLAN_SERVICE:

		RecvClanJoinService((smTRANS_CHAR_COMMAND2 *)pData->Buff);
		break;


	case OpCode::OPCODE_VIRTURAL_POTION:

		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;

		if (!lpTransVirtualPotion)
		{
			lpTransVirtualPotion = new smTRANS_COMMAND;
			if (lpTransVirtualPotion)
			{
				memcpy(lpTransVirtualPotion, lpTransCommand, sizeof(smTRANS_COMMAND));
			}
		}
		break;

	case OpCode::OPCODE_PROCESS_SKILL:
	case OpCode::OPCODE_PROCESS_SKILL2:

		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;
		RecvProcessSkill(lpTransCommand);
		break;

	case OpCode::OPCODE_PROCESS_CLAN_SKILL:

		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;
		chaSiege.SetClanSkill(lpTransCommand->WParam);


		lpsmSock = GetAreaServerSock();
		if (lpsmSock) lpsmSock->Send((char *)lpTransCommand, lpTransCommand->size, TRUE);
		break;

	case OpCode::OPCODE_CANCEL_SKILL:

		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;

		{
			int iCrystalCode = lpTransCommand->LParam;

			if (iCrystalCode != 0)
			{
				sSKILL haCrystalTimer;
				int iCodeToCancel = 0;
				for (int j = 0; j < SIN_MAX_SKILL; j++)
				{
					if (sSkill[j].SkillTaget_CODE == iCrystalCode)
					{
						sSkill[j].SkillTaget_CODE = 0;
						iCodeToCancel = sSkill[j].CODE;
						nCristalInUse--;
						break;
					}
				}

				if (iCodeToCancel)
					cSkill.CancelContinueSkill(iCodeToCancel);
			}
		}


		switch (lpTransCommand->WParam)
		{
		case SKILL_PLAY_METAL_GOLEM:
			cnt = SKILL_METAL_GOLEM;
			break;
		case SKILL_PLAY_RECALL_WOLVERIN:
			cnt = SKILL_RECALL_WOLVERIN;
			break;
		case SKILL_PLAY_FIRE_ELEMENTAL:
			cnt = SKILL_FIRE_ELEMENTAL;
			break;
		case SKILL_PLAY_R_KNIGHT:
			cnt = SKILL_R_KNIGHT;
			break;
		}
		cSkill.CancelContinueSkill(cnt);
		break;

	case OpCode::OPCODE_PARTY_SKILL:

		RecvPartySkillFromServer((TRANS_PARTY_SKILL *)pData->Buff);
		break;

	case OpCode::OPCODE_CLAN_UPDATE:

		Updatecldata();
		break;

	case OpCode::OPCODE_QUEST_MESSAGE:

		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;

		if (lpTransCommand->WParam == SIN_QUEST_CODE_CHANGEJOB4)
		{
			CancelAttack();

			lpChar = FindAutoPlayer(lpTransCommand->LParam);
			if (lpChar)
			{
				OpenEachPlayer(lpChar);
				DispEachMode = TRUE;
			}

			sinBattleNpcResult(1);
		}
		else if (lpTransCommand->WParam == HAQUEST_CODE_FURYOFPHANTOM)
		{

			chaQuest.RecvBattleNpcResult(1);
		}
		else
			sinMorayionNpcChangeJob_Two();

		break;

	case OpCode::OPCODE_ATTACK_RESULT:

		if (lpCurPlayer->AttackCritcal >= 0)
		{
			lpCurPlayer->AttackCritcal = ((smTRANS_COMMAND *)pData->Buff)->WParam;
		}
		break;

	case OpCode::OPCODE_DISP_DAMAGE:
		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;
		LastAttackDamage = ((smTRANS_COMMAND *)pData->Buff)->WParam;
		DrawDamage::GetInstance()->AddTargetDamage(lpTransCommand->WParam, lpTransCommand->LParam, 0);
		break;


	case OpCode::OPCODE_DAMAGE_ENCODE_MEM:

		RecvDamagePacketModule((TRANS_FUNC_MEMORY *)pData->Buff);
		break;

	case OpCode::OPCODE_DAMAGE_ENCODE_MEM2:

		RecvDamagePacketModule2((TRANS_FUNC_MEMORY *)pData->Buff);
		break;

	case OpCode::OPCODE_PACKET_DYNFUNC:

		RecvDynPacketModule((TRANS_FUNC_MEMORY *)pData->Buff);
		break;

	case OpCode::OPCODE_GETPLAYERINFO:

		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;
		if (lpTransCommand->LParam != lpCurPlayer->smCharInfo.bUpdateInfo[0])
		{
			SendSetObjectSerial(lpCurPlayer->dwObjectSerial);
		}
		break;

	case OpCode::OPCODE_AREA_SERVER_MAP:

		RecvAreaServerMap((TRANS_SEVER_MAP *)pData->Buff);
		break;

	case OpCode::OPCODE_ITEM_EXPRESS:

		lpTransPostItem = (TRANS_POST_ITEM *)pData->Buff;

		if (lpTransPostItem->dwItemFlag)
		{
			ComparePotion();
			cInvenTory.SetInvenToItemInfo((sITEMINFO *)(pData->Buff + sizeof(TRANS_POST_ITEM)));
			ResetInvenItemCode();

			if ((((sITEMINFO *)(pData->Buff + sizeof(TRANS_POST_ITEM)))->CODE&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
			{

				ResetPotion2();
			}
			SaveGameData();
		}

		if (lpCurPlayer->smCharInfo.Weight[0] > lpCurPlayer->smCharInfo.Weight[1])
		{
			cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
			break;
		}

		if (lpTransPostItem->dwItemCode)
		{


			if (sinChar->Weight[0] + lpTransPostItem->Weight > sinChar->Weight[1])
			{
				cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
				break;
			}

			memset(&sMessageBox_RecvItem.RecvItem, 0, sizeof(sITEM));
			sMessageBox_RecvItem.RecvItem.CODE = lpTransPostItem->dwItemCode;
			sMessageBox_RecvItem.Flag = 1;
			sMessageBox_RecvItem.szItem[0] = 0;
			cInvenTory.OpenFlag = 1;
			sMessageBox_RecvItem.Param[0] = lpTransPostItem->dwParam[0];


			if (sMessageBox_RecvItem.RecvItem.CODE == (sinGG1 | sin01))
			{
				cInvenTory.LoadMoneyExpImage(&sMessageBox_RecvItem.RecvItem);
				sMessageBox_RecvItem.RecvItem.SellPrice = lpTransPostItem->dwItemJobCode;
				strcpy_s(sMessageBox_RecvItem.szDoc, lpTransPostItem->szDoc);
				break;

			}

			if (sMessageBox_RecvItem.RecvItem.CODE == (sinGG1 | sin02))
			{
				cInvenTory.LoadMoneyExpImage(&sMessageBox_RecvItem.RecvItem);
				sMessageBox_RecvItem.RecvItem.OldX = lpTransPostItem->dwItemJobCode;
				strcpy_s(sMessageBox_RecvItem.szDoc, lpTransPostItem->szDoc);
				break;
			}

			if ((sMessageBox_RecvItem.RecvItem.CODE & sinITEM_MASK1) == 0x04000000)
			{
				sMessageBox_RecvItem.RecvItem.PotionCount = lpTransPostItem->dwItemJobCode;
				cInvenTory.CheckInvenEmpty(&sMessageBox_RecvItem.RecvItem);
				strcpy_s(sMessageBox_RecvItem.szItem, lpTransPostItem->szItemName);
				strcpy_s(sMessageBox_RecvItem.szDoc, lpTransPostItem->szDoc);
				break;

			}


			cInvenTory.CheckInvenEmpty(&sMessageBox_RecvItem.RecvItem);
			strcpy_s(sMessageBox_RecvItem.szItem, lpTransPostItem->szItemName);
			strcpy_s(sMessageBox_RecvItem.szDoc, lpTransPostItem->szDoc);
		}
		break;

	case OpCode::OPCODE_SOD_RESULT:

		cSinHelp.ShowSodRanking((TRANS_SOD_RESULT *)pData->Buff, 1);
		break;

	case OpCode::OPCODE_SOD_RESULT2:

		cSinHelp.ShowSodRanking((TRANS_SOD_RESULT *)pData->Buff, 0);
		break;

	case OpCode::OPCODE_SOD_INFOMATION:

		RecvSodGameInfomation(pData->Buff);
		break;


	case OpCode::OPCODE_WING_NPC:

		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;

		if (lpTransCommand->LParam)
		{

			switch (lpTransCommand->LParam)
			{
			case 1:
				sinShowTeleportMap();
				break;
			case 2:
				haShowCastleTeleportMap();
				break;
			case 3:
				TeleportDungeon();
				break;
			case 7:
				TradeBPEXP();
				break;
			}
		}

		switch (lpTransCommand->WParam)
		{
		case 0:
		case 1:
			cInvenTory.sinWingQuestNpc();
			break;
		case 2:
			cInvenTory.SendPuzzleNpc();
			break;
		case 3:
			cInvenTory.CheckEventItem();
			break;
		case 4:
			cInvenTory.CheckFoxEventItem();
			break;
		case 5:
			cInvenTory.CheckCristalEventItem();
			break;
		case 8:
			cInvenTory.CheckWatermelonEventItem();
			break;
		case 9:
			cInvenTory.CheckValentineEventItem();
			break;
		case 10:
			cInvenTory.CheckPristonAlphabetEventItem();
			break;
		case 11:
			cInvenTory.CheckCandydaysEventItem();
			break;
		case 12:
			cInvenTory.CheckMagicalGreenEventItem();
			break;

		case 13:
			cInvenTory.CheckTearOfKaraEventItem();
			break;

		case 14:
			cInvenTory.CheckFindinvestigatorEventItem();
			break;
		case 15:
			cInvenTory.CheckFindinvestigatorKamiuEventItem();
			break;
		case 16:
			cInvenTory.CheckFindinvestigatorEtoEventItem();
			break;

		}
		break;

	case OpCode::OPCODE_OPEN_STARPOINT:

		StarShopNPC();
		break;

	case OpCode::OPCODE_STARPOINT:

		sinStarPoint(((smTRANS_COMMAND *)pData->Buff)->WParam);

		break;

	case OpCode::OPCODE_CLANMONEY:

		sinRecvClanMoney(((smTRANS_COMMAND *)pData->Buff)->WParam, ((smTRANS_COMMAND *)pData->Buff)->LParam);
		break;

	case OpCode::OPCODE_OPEN_GIVEMONEY:

		cMessageBox.ShowMessage2(MESSAGE_GIVE_MONEY);
		break;

	case OpCode::OPCODE_CHANGE_EVENT:

		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;
		if (sBiInfo)
		{
			sBiInfo->EventPlay[0] = lpTransCommand->WParam & 0xFFFF;
			sBiInfo->EventPlay[1] = (lpTransCommand->WParam >> 16) & 0xFFFF;
			sBiInfo->PCRNo = lpTransCommand->LParam;
			cInvenTory.SetItemToChar();
		}

		if (lpTransCommand->EParam)
		{
			GoNotice_chking = 1;
		}
		break;

	case OpCode::OPCODE_CALL_MYSHOP:

		if (lpCurPlayer->dwTradeMsgCode)
			Send_MyShopItemList((smTRANS_COMMAND *)pData->Buff);
		break;

	case OpCode::OPCODE_MYSHOP_ITEM:

		Recv_MyShopItemList((TRANS_TRADEITEMS *)pData->Buff);
		break;

	case OpCode::OPCODE_MYSHOP_MESSAGE:

		lpTransChatMessage = (TRANS_CHATMESSAGE *)pData->Buff;

		lpChar = FindAutoPlayer(lpTransChatMessage->dwObjectSerial);
		if (lpChar && lpChar->dwTradeMsgCode)
		{


			wsprintf(lpChar->szTradeMessage, "%s: %s", lpChar->smCharInfo.szName, lpTransChatMessage->szMessage);
		}
		break;

	case OpCode::OPCODE_MYSHOP_TRADE:

		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;

		cMyShop.RecvMyShopItem(lpTransCommand->SParam,
			(sMYSHOP_ITEM_SERVER *)(((smTRANS_COMMAND_BUFF *)pData->Buff)->Buff));

		break;

	case OpCode::OPCODE_SUCCESS_EVATION:

		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;

		AddTimeEffect(OpCode::OPCODE_SUCCESS_EVATION, dwPlayTime + 500, lpTransCommand->WParam, lpTransCommand->LParam, lpTransCommand->SParam);
		break;

	case OpCode::OPCODE_SUCCESS_DEFENSE:

		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;

		AddTimeEffect(OpCode::OPCODE_SUCCESS_DEFENSE, dwPlayTime + 500, lpTransCommand->WParam, lpTransCommand->LParam, lpTransCommand->SParam);
		break;

	case OpCode::OPCODE_BLESSCASTLE_INFO:

		RecvBlessCastInfo(pData->Buff);
		break;

	case OpCode::OPCODE_MEDIA_NPC:

		lpTransChatMessage = (TRANS_CHATMESSAGE *)pData->Buff;
		chaSiege.ShowCastlePlayMovie(lpTransChatMessage->szMessage,
			lpTransChatMessage->szMessage + lstrlen(lpTransChatMessage->szMessage) + 1,
			0);

		break;

	case OpCode::OPCODE_EXITINFO_URL:

		lpTransChatMessage = (TRANS_CHATMESSAGE *)pData->Buff;
		strcpy_s(szExitInfo_URL, lpTransChatMessage->szMessage);
		break;

	case OpCode::OPCODE_PUBLIC_POLLING:

		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;
		cSinHelp.ShowResearchMenu(lpTransCommand->WParam, lpTransCommand->LParam);
		break;

	case OpCode::OPCODE_NOTICE_BOX:


		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;
		cHelp_Menu.haGuidHelpLevel_1(lpTransCommand->WParam);
		break;

	case OpCode::OPCODE_PCBANG_PET:



		break;
	case OpCode::OPCODE_PHENIX_PET:


		break;

	case OpCode::OPCODE_HELP_PET:
		break;

#ifdef _xTrap_GUARD
	case OpCode::OPCODE_XTRAP_PACKET:
		XTrap_Recv((smTRANS_COMMAND *)pData->Buff, smWsockDataServer);
		break;
#endif

	case OpCode::OPCODE_SMELTINGITEM:
		SmeltingItem.sinRecvSmeltingItemResult((sSMELTINGITEM_SERVER *)pData->Buff);
		ResetInvenItemCode();
		SaveGameData();
		break;
	case OpCode::OPCODE_MANUFACTURE:
		ManufactureItem.RecvManufactureItemResult((SManufactureItem_Server *)pData->Buff);
		ResetInvenItemCode();
		SaveGameData();
		break;
	case OpCode::OPCODE_MIXTURE_RESET_ITEM:

		cMixtureReset.sinRecvMixtureItemResetResult((sMIXTURE_RESET_ITEM_SERVER *)pData->Buff);
		ResetInvenItemCode();
		SaveGameData();
		break;
	case OpCode::OPCODE_MANUFACTURE_WEIGHT_PRICE:
		ManufactureItemResultInfo((SManufacture_ResultItemInfo_Server *)pData->Buff);
		break;
	case OpCode::OPCODE_SEND_AGAME_PRIMEITEM_DATA2:

		lpsmSock = GetAreaServerSock();
		for (int i = 0; i < SINUPKEEPITEM_MAX; i++)
		{
			if (chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::MIGHT_OF_AWELL)
			{
				if (chaPremiumitem.UpKeepItem[i].IconTime[1] - chaPremiumitem.UpKeepItem[i].IconTime[0] <= 0)
				{
					chaPremiumitem.m_MightofAwellTime = 0;
					chaPremiumitem.m_MightofAwellWeight = 0;
				}
			}

			if (chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::MANA_REDUCE_P)
			{
				if (chaPremiumitem.UpKeepItem[i].IconTime[1] - chaPremiumitem.UpKeepItem[i].IconTime[0] <= 0)
				{
					chaPremiumitem.m_ManaReducePotiontime = 0;
					chaPremiumitem.m_ManaReducePotionValue = 0;
				}
			}
			else if (chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::MIGHT_OF_AWELL)
			{
				if (chaPremiumitem.UpKeepItem[i].IconTime[1] - chaPremiumitem.UpKeepItem[i].IconTime[0] <= 0)
				{
					chaPremiumitem.m_MightofAwellTime = 0;
					chaPremiumitem.m_MightofAwellWeight = 0;
				}
			}
			else if (chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::PHENIX_PET)
			{
				if (chaPremiumitem.UpKeepItem[i].IconTime[1] - chaPremiumitem.UpKeepItem[i].IconTime[0] <= 0)
				{
					chaPremiumitem.m_PhenixPetTime = 0;
					cPCBANGPet.ClosePet();
				}
			}
		}
		if (lpsmSock)
		{
			lpsmSock->Send(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff, ((smTRANS_COMMAND *)(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff))->size, TRUE);

			if (lpsmSock != smWsockServer)
				smWsockServer->Send(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff, ((smTRANS_COMMAND *)(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff))->size, TRUE);
		}
		else
			smWsockServer->Send(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff, ((smTRANS_COMMAND *)(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff))->size, TRUE);
		break;


	case OpCode::OPCODE_SEND_AGAME_PRIMEITEM_DATA3:

		lpsmSock = GetAreaServerSock();
		for (int i = 0; i < SINUPKEEPITEM_MAX; i++)
		{
			if (chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::HELP_PET_TERRY)
			{
				if (chaPremiumitem.UpKeepItem[i].IconTime[1] - chaPremiumitem.UpKeepItem[i].IconTime[0] <= 0)
				{

					chaPremiumitem.m_TerryTime = 0;

					chaPremiumitem.m_HelpPetTime = 0;
					sinChar->GravityScroolCheck[1] = 0;
					cHelpPet.ClosePet();
				}
			}
			else if (chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::HELP_PET_NEPSYS)
			{
				if (chaPremiumitem.UpKeepItem[i].IconTime[1] - chaPremiumitem.UpKeepItem[i].IconTime[0] <= 0)
				{
					chaPremiumitem.m_HelpPetTime = 0;
					cHelpPet.ClosePet();
				}
			}
			else if (chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::HELP_PET_IO)
			{
				if (chaPremiumitem.UpKeepItem[i].IconTime[1] - chaPremiumitem.UpKeepItem[i].IconTime[0] <= 0)
				{
					chaPremiumitem.m_HelpPetTime = 0;
					cHelpPet.ClosePet();
				}
			}
			else if (chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::HELP_PET_MUTE)
			{
				if (chaPremiumitem.UpKeepItem[i].IconTime[1] - chaPremiumitem.UpKeepItem[i].IconTime[0] <= 0)
				{
					chaPremiumitem.m_HelpPetTime = 0;
					sinChar->GravityScroolCheck[1] = 0;
					cHelpPet.ClosePet();
				}
			}
			else if (chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::STAMINA_REDUCE_P)
			{
				if (chaPremiumitem.UpKeepItem[i].IconTime[1] - chaPremiumitem.UpKeepItem[i].IconTime[0] <= 0)
				{
					chaPremiumitem.m_StaminaReducePotiontime = 0;
					chaPremiumitem.m_StaminaReducePotionValue = 0;
					chaPremiumitem.SetStaminaReducePotionTime(chaPremiumitem.m_StaminaReducePotiontime);
				}
			}

			else if (chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::VAMPIRIC_CUS_EX)
			{
				if (chaPremiumitem.UpKeepItem[i].IconTime[1] - chaPremiumitem.UpKeepItem[i].IconTime[0] <= 0)
				{
					chaPremiumitem.m_VampiricCuspidEXTime = 0;
				}
			}
		}

		for (int i = 0; i < SINUPKEEPITEM_MAX; i++)
		{
			if (chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::VAMPIRIC_CUS_EX)
			{
				if (chaPremiumitem.UpKeepItem[i].IconTime[1] - chaPremiumitem.UpKeepItem[i].IconTime[0] <= 0)
				{
					chaPremiumitem.m_VampiricCuspidEXTime = 0;
				}
			}

		}


		if (lpsmSock)
		{
			lpsmSock->Send(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff, ((smTRANS_COMMAND *)(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff))->size, TRUE);

			if (lpsmSock != smWsockServer)
				smWsockServer->Send(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff, ((smTRANS_COMMAND *)(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff))->size, TRUE);
		}
		else
			smWsockServer->Send(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff, ((smTRANS_COMMAND *)(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff))->size, TRUE);

		break;


	case OpCode::OPCODE_SEND_AGAME_PRIMEITEM_DATA4:

		lpsmSock = GetAreaServerSock();
		for (int i = 0; i < SINUPKEEPITEM_MAX; i++)
		{
			if (chaPremiumitem.UpKeepItem[i].TGAImageNumber == nsPremiumItem::VAMPIRIC_CUS_EX)
			{
				if (chaPremiumitem.UpKeepItem[i].IconTime[1] - chaPremiumitem.UpKeepItem[i].IconTime[0] <= 0)
				{
					chaPremiumitem.m_VampiricCuspidEXTime = 0;
				}
			}

		}
		if (lpsmSock)
		{
			lpsmSock->Send(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff, ((smTRANS_COMMAND *)(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff))->size, TRUE);

			if (lpsmSock != smWsockServer)
				smWsockServer->Send(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff, ((smTRANS_COMMAND *)(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff))->size, TRUE);
		}
		else
			smWsockServer->Send(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff, ((smTRANS_COMMAND *)(((TRANS_SEND_DATASERVER *)pData->Buff)->szBuff))->size, TRUE);
		break;


	case OpCode::OPCODE_UPDATE_PREMIUMITEM_TIME:

		if (chaPremiumitem.bUpdateTimeDelayFlag == true) break;

		lpTransPremiumTime = (TRANS_PREMIUM_TIME *)pData->Buff;

		chaPremiumitem.m_ThirdEyesTime = lpTransPremiumTime->ThirdEye;
		chaPremiumitem.m_ExpUpPotionTime = lpTransPremiumTime->ExpUp;
		chaPremiumitem.m_VampiricCuspidTime = lpTransPremiumTime->VampCuspid;
		chaPremiumitem.m_ManaRechargingPTime = lpTransPremiumTime->ManaRecharg;
		chaPremiumitem.m_ManaReducePotiontime = lpTransPremiumTime->ManaReduce;
		chaPremiumitem.m_MightofAwellTime = lpTransPremiumTime->MightofAwell;
		if (!chaPremiumitem.m_MightofAwellTime)
			chaPremiumitem.m_MightofAwellTime = lpTransPremiumTime->MightofAwell2;


		chaPremiumitem.m_PhenixPetTime = lpTransPremiumTime->PhenixPet;

		chaPremiumitem.m_HelpPetTime = lpTransPremiumTime->HelpPet;
		chaPremiumitem.m_VampiricCuspidEXTime = lpTransPremiumTime->VampCuspidEx;
		chaPremiumitem.m_StaminaReducePotiontime = lpTransPremiumTime->StaminaReduce;

		if (chaPremiumitem.m_ThirdEyesTime > PRIME_ITEM_TIME_7D || chaPremiumitem.m_ExpUpPotionTime > PRIME_ITEM_TIME_7D ||
			chaPremiumitem.m_VampiricCuspidTime > PRIME_ITEM_TIME_7D || chaPremiumitem.m_ManaRechargingPTime > PRIME_ITEM_TIME_7D ||
			chaPremiumitem.m_ManaReducePotiontime > PRIME_ITEM_TIME_7D || chaPremiumitem.m_MightofAwellTime > PRIME_ITEM_TIME_7D || chaPremiumitem.m_PhenixPetTime > PRIME_ITEM_TIME_7D ||
			chaPremiumitem.m_HelpPetTime > PRIME_ITEM_TIME_7D || chaPremiumitem.m_StaminaReducePotiontime > PRIME_ITEM_TIME_7D || chaPremiumitem.m_VampiricCuspidEXTime > PRIME_ITEM_TIME_7D)
		{
			break;
		}

		for (int i = 0; i < SINUPKEEPITEM_MAX; i++)
		{
			int TGANumber = chaPremiumitem.UpKeepItem[i].TGAImageNumber;

			switch (TGANumber)
			{
			case nsPremiumItem::THIRD_EYES:
				chaPremiumitem.UpKeepItem[i].IconTime[1] = chaPremiumitem.m_ThirdEyesTime;
				break;

			case nsPremiumItem::EXPUP_POTION:
				chaPremiumitem.UpKeepItem[i].IconTime[1] = chaPremiumitem.m_ExpUpPotionTime;
				break;

			case nsPremiumItem::VAMPIRIC_CUS:
				chaPremiumitem.UpKeepItem[i].IconTime[1] = chaPremiumitem.m_VampiricCuspidTime;
				break;

			case nsPremiumItem::MANA_RECHAR_P:
				chaPremiumitem.UpKeepItem[i].IconTime[1] = chaPremiumitem.m_ManaRechargingPTime;
				break;

			case nsPremiumItem::MIGHT_OF_AWELL:
				chaPremiumitem.UpKeepItem[i].IconTime[1] = chaPremiumitem.m_MightofAwellTime;
				break;

			case nsPremiumItem::MANA_REDUCE_P:
				chaPremiumitem.UpKeepItem[i].IconTime[1] = chaPremiumitem.m_ManaReducePotiontime;
				break;

			case nsPremiumItem::PHENIX_PET:
				chaPremiumitem.UpKeepItem[i].IconTime[1] = chaPremiumitem.m_PhenixPetTime;
				break;

			case nsPremiumItem::HELP_PET_TERRY:
			case nsPremiumItem::HELP_PET_NEPSYS:
			case nsPremiumItem::HELP_PET_IO:
			case nsPremiumItem::HELP_PET_MUTE:
				chaPremiumitem.UpKeepItem[i].IconTime[1] = chaPremiumitem.m_HelpPetTime;
				break;

			case nsPremiumItem::VAMPIRIC_CUS_EX:
				chaPremiumitem.UpKeepItem[i].IconTime[1] = chaPremiumitem.m_VampiricCuspidEXTime;
				break;

			case nsPremiumItem::STAMINA_REDUCE_P:
				chaPremiumitem.UpKeepItem[i].IconTime[1] = chaPremiumitem.m_StaminaReducePotiontime;
				break;
			}

		}
		break;

	case OpCode::OPCODE_COUPLERING:
	{
		cInvenTory.DeleteCoupleRing();
	}
	break;


	case OpCode::OPCODE_PREMIUMITEM_INIT:
		lpTransCommand = (smTRANS_COMMAND *)pData->Buff;
		for (int i = 0; i < SINUPKEEPITEM_MAX; i++)
		{
			if (chaPremiumitem.UpKeepItem[i].TGAImageNumber == lpTransCommand->WParam)
			{
				chaPremiumitem.UpKeepItem[i].IconTime[1] = chaPremiumitem.UpKeepItem[i].IconTime[0];
				if (lpTransCommand->WParam == 8 || lpTransCommand->WParam == 9 || lpTransCommand->WParam == 10 || lpTransCommand->WParam == 11)
				{
					cHelpPet.ClosePet();
				}
				else if (lpTransCommand->WParam == 12)
				{
					cPCBANGPet.ClosePet();
				}
				else if (lpTransCommand->WParam == 6)
				{
					chaPremiumitem.m_ManaReducePotiontime = 0;
					chaPremiumitem.SetManaReducePotionTime(chaPremiumitem.m_ManaReducePotiontime);
				}
				else if (lpTransCommand->WParam == 7)
				{
					chaPremiumitem.m_StaminaReducePotiontime = 0;
					chaPremiumitem.SetStaminaReducePotionTime(chaPremiumitem.m_StaminaReducePotiontime);
				}
			}
		}
		break;

#ifdef _XTRAP_GUARD_4_CLIENT
	case OpCode::OPCODE_XTRAP_PACKET:
		XTrap_Recv((smTRANS_COMMAND *)pData->Buff, smWsockDataServer);
		break;
#endif


#ifdef _XIGNCODE_CLIENT
	case OpCode::OPCODE_XIGNCODE_PACKET:
		XIGNCODE_PACKET *pack = (XIGNCODE_PACKET *)pData->Buff;
		Xigncode_Client_Recv(smWsockDataServer, pack);
		break;
#endif
	}

	if (lpCharInfo_MsgBack)
	{

		if (addExp)
		{

			cnt = (lpCurPlayer->smCharInfo.Exp^CodeXorExp) - (lpCharInfo_MsgBack->Exp^CodeXorExp);
			if (cnt > addExp)
			{
				memcpy(&lpCurPlayer->smCharInfo, lpCharInfo_MsgBack, sizeof(smCHAR_INFO));
				SaveGameData();
				lpCurPlayer->smCharInfo.Exp++;
			}
		}

		if (addMoney)
		{
			cnt = lpCurPlayer->smCharInfo.Money - lpCharInfo_MsgBack->Money;

			if (cnt >= addMoney)
			{
				if (addMoney >= 2000)
					SaveGameData();
			}
			else
			{

				lpCurPlayer->smCharInfo.Money = lpCharInfo_MsgBack->Money;
			}


			AddInvenMoney(addMoney);

		}

		delete lpCharInfo_MsgBack;
	}

	return TRUE;
}

int rsTRANS_SERVER::Init(smWINSOCK *lpsmsock)
{

	lpsmSock = lpsmsock;
	lpRecorder = 0;


	InitializeCriticalSection(&cServSection);

	RecvDataQuePush = 0;
	RecvDataQuePop = 0;

	ZeroMemory(RecvDataQue, RECV_DATA_QUE_COUNT * 4);

	return TRUE;
}



extern int szSpaceSorting(char *lpString);


int rsTRANS_SERVER::SendChat(char *szMessage)
{
	int len = 0;

	if (!szMessage || !szMessage[0]) return FALSE;

	if (szMessage[0] == '/' && (szMessage[1] == ';' || szMessage[1] == ':'))
	{

		szSpaceSorting(szMessage);
	}

	if (szMessage[0] == '`' && szMessage[1] == '/')
	{
		len = lstrlen(szMessage + 1) + 9;
		strcpy_s(TransBuff + 8, sizeof(TransBuff) - 8, szMessage + 1);
		((int *)TransBuff)[0] = len;
		((int *)TransBuff)[1] = OpCode::OPCODE_CHATMESSAGE;
		if (smWsockDataServer) smWsockDataServer->Send(TransBuff, len, TRUE);
		return TRUE;
	}

	if (szMessage[0] == '~' && szMessage[1] == '/')
	{

		len = lstrlen(szMessage + 1) + 9;
		strcpy_s(TransBuff + 8, sizeof(TransBuff) - 8, szMessage + 1);
		((int *)TransBuff)[0] = len;
		((int *)TransBuff)[1] = OpCode::OPCODE_CHATMESSAGE;
		if (smWsockServer) smWsockServer->Send(TransBuff, len, TRUE);
		if (smWsockServer != smWsockUserServer && smWsockUserServer) smWsockUserServer->Send(TransBuff, len, TRUE);
		if (smWsockServer != smWsockExtendServer && smWsockExtendServer) smWsockExtendServer->Send(TransBuff, len, TRUE);
		if (AreaServerMode)
		{
			if (lpWSockServer_Area[0]) lpWSockServer_Area[0]->Send(TransBuff, len, TRUE);
			if (lpWSockServer_Area[1]) lpWSockServer_Area[1]->Send(TransBuff, len, TRUE);
		}

	}
	else
	{

		if (szMessage[0] == '@')
		{


			wsprintf(TransBuff + 8, "%s> %s", PlayerName, szMessage + 1);
			len = lstrlen(TransBuff + 8) + 9;
			((int *)TransBuff)[0] = len;
			((int *)TransBuff)[1] = OpCode::OPCODE_PARTY_CHATMSG;

			if (smWsockServer) smWsockServer->Send(TransBuff, len, TRUE);
			AddChatBuff(TransBuff + 8, 4);
			return TRUE;
		}
		else
		{
			strcpy_s(TransBuff + 8, sizeof(TransBuff) - 8, szMessage);
			len = lstrlen(szMessage) + 9;

			((int *)TransBuff)[0] = len;
			((int *)TransBuff)[1] = OpCode::OPCODE_CHATMESSAGE;
		}

		if (szMessage[0] == '/')
		{

			if (szMessage[1] == 'c' && szMessage[2] == 'o' && szMessage[3] == 'u' && szMessage[4] == 'p' &&
				szMessage[5] == 'l' && szMessage[6] == 'e')
			{
				if (smWsockUserServer && cInvenTory.SearchItemCode(sinSP1 | sin15)) smWsockUserServer->Send(TransBuff, len, TRUE);
				return TRUE;
			}

			if (szMessage[1] == '/')
			{
				if (smWsockUserServer) smWsockUserServer->Send(TransBuff, len, TRUE);
			}
			else
			{
				if (smWsockServer) smWsockServer->Send(TransBuff, len, TRUE);
			}

			return TRUE;
		}

		if (AreaServerMode)
		{
			if (lpCurPlayer->OnStageField >= 0 && lpWSockServer_DispArea[lpCurPlayer->OnStageField])
			{
				lpWSockServer_DispArea[lpCurPlayer->OnStageField]->Send(TransBuff, len, TRUE);
			}
		}
		else
			if (smWsockUserServer) smWsockUserServer->Send(TransBuff, len, TRUE);

	}
	return TRUE;
}


int rsTRANS_SERVER::SendPlayData(smCHAR *lpChar)
{


	TRANS_PLAYPOS *lpTransPlayPos;
	int	dist, x, y, z;

	TransPlayPosCount++;

	if ((TransPlayPosCount & 1) == 0)
	{
		x = (TransPlayPosLast.rsPlayPos.x - lpChar->pX) >> FLOATNS;
		y = (TransPlayPosLast.rsPlayPos.y - lpChar->pY) >> FLOATNS;
		z = (TransPlayPosLast.rsPlayPos.z - lpChar->pZ) >> FLOATNS;
		dist = x * x + y * y + z * z;

		if (sinGetLife() > 0 && dist < (16 * 16 * 16))
		{

			return TRUE;
		}
	}

	lpTransPlayPos = (TRANS_PLAYPOS *)TransBuff;
	lpTransPlayPos->code = OpCode::OPCODE_POSITION;
	lpTransPlayPos->size = sizeof(TRANS_PLAYPOS);

	if (lpCurPlayer->OnStageField >= 0)
		lpTransPlayPos->rsPlayPos.Area = StageField[lpCurPlayer->OnStageField]->FieldCode;
	else
		lpTransPlayPos->rsPlayPos.Area = -1;

	lpTransPlayPos->rsPlayPos.x = lpChar->pX;
	lpTransPlayPos->rsPlayPos.y = lpChar->pY;
	lpTransPlayPos->rsPlayPos.z = lpChar->pZ;

	if (lpCurPlayer->MotionInfo && lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_DEAD)
		lpTransPlayPos->Hp[0] = 0;
	else
		lpTransPlayPos->Hp[0] = sinGetLife();

	lpTransPlayPos->Hp[1] = lpChar->smCharInfo.Life[1];

	if (smWsockServer)
		smWsockServer->Send((char *)lpTransPlayPos, lpTransPlayPos->size, TRUE);

	if (smWsockExtendServer && smWsockExtendServer != smWsockServer)
		smWsockExtendServer->Send((char *)lpTransPlayPos, lpTransPlayPos->size, TRUE);


	int	MainArea, SubArea;

	if (AreaServerMode)
	{
		if (lpCurPlayer->OnStageField >= 0)
		{
			MainArea = (lpCurPlayer->OnStageField) & 1;
			SubArea = (lpCurPlayer->OnStageField + 1) & 1;

			if (lpWSockServer_DispArea[SubArea] && lpWSockServer_DispArea[MainArea] != lpWSockServer_DispArea[SubArea])
			{
				lpWSockServer_DispArea[SubArea]->Send((char *)lpTransPlayPos, lpTransPlayPos->size, TRUE);
			}
		}
	}


	return TRUE;
}



rsTRANS_SERVER	rsMainServer;









#define SAVE_CHAT_COMMAND_MAX		16
#define SAVE_CHAT_COMMAND_MASK		15

char szSaveChatCommands[SAVE_CHAT_COMMAND_MAX][256];
int ChatCommandSaveCnt = 0;
int ChatSaveRecallCnt = 0;


int SaveChatCommand(char *szMessage)
{
	int len, cnt;
	int mcnt;
	char szBuff[256];

	len = lstrlen(szMessage);
	strcpy_s(szBuff, szMessage);

	for (cnt = 0; cnt < len; cnt++)
	{
		if (szBuff[cnt] == ' ')
		{
			szBuff[cnt] = 0;
			break;
		}
	}
	lstrcat(szBuff, " ");


	for (cnt = 0; cnt < ChatCommandSaveCnt; cnt++)
	{
		if (cnt >= SAVE_CHAT_COMMAND_MAX) break;
		if (lstrcmp(szSaveChatCommands[cnt], szBuff) == 0)
			return TRUE;
	}

	mcnt = ChatCommandSaveCnt & SAVE_CHAT_COMMAND_MASK;
	strcpy_s(szSaveChatCommands[mcnt], szBuff);

	ChatCommandSaveCnt++;
	ChatSaveRecallCnt = ChatCommandSaveCnt;

	return TRUE;
}


int RecallSavedChatCommand(HWND hChatWnd, int Arrow)
{
	int mcnt;
	int len;

	if (ChatCommandSaveCnt <= 0) return FALSE;

	if (Arrow)
	{
		ChatSaveRecallCnt--;
		if (ChatSaveRecallCnt < 0)
		{
			ChatSaveRecallCnt = ChatCommandSaveCnt - 1;
		}
	}
	else
	{
		ChatSaveRecallCnt++;
		if (ChatSaveRecallCnt >= ChatCommandSaveCnt)
		{
			ChatSaveRecallCnt = ChatCommandSaveCnt - 1;
			SetWindowText(hChatWnd, "");
			return TRUE;
		}
	}

	mcnt = ChatSaveRecallCnt & SAVE_CHAT_COMMAND_MASK;
	SetWindowText(hChatWnd, szSaveChatCommands[mcnt]);

	len = lstrlen(szSaveChatCommands[mcnt]);
	SendMessage(hChatWnd, EM_SETSEL, len, len);

	return TRUE;
}


int rsCompString(char *src1, char *src2)
{
	int cnt;
	int len1, len2;
	int len;

	len1 = lstrlen(src1);
	len2 = lstrlen(src2);

	if (len1 < len2) len = len1;
	else len = len2;

	if (!len) return NULL;

	for (cnt = 0; cnt < len1; cnt++)
	{
		if (src1[cnt] == 0) break;
		if (src1[cnt] != src2[cnt]) return NULL;
	}

	return cnt;
}



char szLastChatMessage[256];
DWORD	dwLastChatTime;
DWORD	dwContiueChatCount = 0;
#include "CurseFilter.h"		

char *rsGetWord(char *q, char *p);

extern int WaveCameraMode;


int SendChatMessageToServer(char *szChatMessage)
{

	char szMessage[256];
	char *lpMsg = 0;
	int	 cnt;
	int	 WhispFlag;
	char szBuff[256];
	smWINSOCK	*lpsmSock;

	if (szChatMessage[0] == '/' && (szChatMessage[1] == ';' || szChatMessage[1] == ':')) WhispFlag = TRUE;
	else WhispFlag = FALSE;

	if (dwLastChatTime && dwLastChatTime > dwPlayTime) return FALSE;

	if (dwLastChatTime && (dwPlayTime - dwLastChatTime) < 2000 && WhispFlag == FALSE)
	{
		dwContiueChatCount++;
		if (dwContiueChatCount > 10)
		{

			wsprintf(szMessage, mgContinueChat, lpCurPlayer->smCharInfo.szName);
			strcpy_s(lpCurPlayer->szChatMessage, szMessage);
			lpCurPlayer->dwChatMessageTimer = dwPlayTime + 1000 * 7;

			dwLastChatTime = lpCurPlayer->dwChatMessageTimer;
			return FALSE;
		}
	}
	else
		dwContiueChatCount = 0;

	strcpy_s(szMessage, szChatMessage);

	for (cnt = 0; cnt < 64; cnt++)
	{
		if (!szMessage[cnt]) break;
		if (szMessage[cnt] == ':' && szMessage[cnt + 1] == ' ')
		{
			lpMsg = szMessage + cnt + 2;
			break;
		}
	}

	if (lpMsg && (lstrcmpi(mgYahoo, lpMsg) == 0 || lstrcmpi("yahoo", lpMsg) == 0))
	{

		dwYahooTime = dwPlayTime + 60 * 1000;

		if (lpCurPlayer && lpCurPlayer->MotionInfo)
		{
			if (lpCurPlayer->MotionInfo->State < 0x100)
			{
				if (lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_YAHOO))
				{

				}
			}
		}
		return TRUE;
	}


	if (szMessage[0] != '/' && szMessage[0] != '~' && szMessage[0] != '`' && szMessage[0] != '@')
	{
		AddChatBuff(szMessage, 256);

		strcpy_s(lpCurPlayer->szChatMessage, szMessage);
		lpCurPlayer->dwChatMessageTimer = dwPlayTime + 1000 * 7;
	}
	else
	{
		if (szMessage[1] != '*' && szMessage[0] != '@')
		{

			SaveChatCommand(szMessage);
		}

		char *lpBuff;
		int cnt, len;

//COMANDO PLAYER 
		if (szMessage[0] == '/')
		{

			if (StageField[lpCurPlayer->OnStageField]->FieldCode != 50)
			{

				len = rsCompString("/ConcluirQuests", szMessage);

				if (len)
				{
					SendChatMessageToServer("GothicPT: Todas as quest terminadas");
					if (sinQuest_Level30.State < 3 && sinChar->Level >= 30) {
						CheckCharForm();
						sinChar->StatePoint += 5;
						cMessageBox.ShowMessage(MESSAGE_PLUS_STATE_POINT5);
						sinPlaySound(SIN_SOUND_EAT_POTION2);
						sinQuest_levelLog |= QUESTBIT_LEVEL_30;
						sinQuest_Level30.State = 3;
						sinQuest_Level30.BackUpCode = sinQuest_Level30.CODE;
						sinQuest_Level30.CODE = 0;
						EndQuest_Code(sinQuest_Level30.BackUpCode);
						sinQuest_Level30.CODE = 0;
						ReformCharForm();
					}

					if (sinQuest_Level55.State < 2 && sinChar->Level >= 55 && sinChar->JOB_CODE < 5) {
						CheckCharForm();
						sinSkill.SkillPoint += 1;
						cMessageBox.ShowMessage(MESSAGE_PLUS_SKILL_POINT);
						sinPlaySound(SIN_SOUND_EAT_POTION2);
						sinQuest_levelLog |= QUESTBIT_LEVEL_55;
						sinQuest_Level55.State = 3;
						sinQuest_Level55.BackUpCode = sinQuest_Level55.CODE;
						sinQuest_Level55.CODE = 0;
						EndQuest_Code(sinQuest_Level55.BackUpCode);
						sinQuest_Level55.CODE = 0;

						ReformCharForm();

					}
					if (sinQuest_Level55_2.State < 2 && sinChar->Level >= 55 && sinChar->JOB_CODE > 4) {
						CheckCharForm();
						sinSkill.SkillPoint += 1;
						cMessageBox.ShowMessage(MESSAGE_PLUS_SKILL_POINT);
						sinPlaySound(SIN_SOUND_EAT_POTION2);
						sinQuest_levelLog |= QUESTBIT_LEVEL_55;
						sinQuest_Level55_2.State = 3;
						sinQuest_Level55_2.BackUpCode = sinQuest_Level55_2.CODE;
						sinQuest_Level55_2.CODE = 0;
						EndQuest_Code(sinQuest_Level55_2.BackUpCode);
						sinQuest_Level55_2.CODE = 0;
						ReformCharForm();
					}

					if (sinQuest_Level70.State < 2 && sinChar->Level >= 70) {
						CheckCharForm();
						sinChar->StatePoint += 5;
						sinSkill.SkillPoint += 1;
						cMessageBox.ShowMessage(MESSAGE_PLUS_POINT_70);
						sinPlaySound(SIN_SOUND_EAT_POTION2);
						sinQuest_levelLog |= QUESTBIT_LEVEL_70;
						sinQuest_Level70.State = 3;
						sinQuest_Level70.BackUpCode = sinQuest_Level70.CODE;
						sinQuest_Level70.CODE = 0;
						EndQuest_Code(sinQuest_Level70.BackUpCode);
						sinQuest_Level70.CODE = 0;
						ReformCharForm();
					}

					if (sinQuest_Level80.State < 2 && sinChar->Level >= 80) {
						CheckCharForm();
						sinChar->StatePoint += 5;
						sinSkill.SkillPoint += 2;
						cMessageBox.ShowMessage(MESSAGE_PLUS_POINT_80);
						sinPlaySound(SIN_SOUND_EAT_POTION2);
						sinQuest_levelLog |= QUESTBIT_LEVEL_80;
						sinQuest_Level80.State = 3;
						sinQuest_Level80.BackUpCode = sinQuest_Level80.CODE;
						sinQuest_Level80.CODE = 0;
						EndQuest_Code(sinQuest_Level80.BackUpCode);
						sinQuest_Level80.CODE = 0;
						ReformCharForm();
					}

					if (sinQuest_Level85.State < 4 && sinChar->Level >= 85) {
						CheckCharForm();
						sinQuest_levelLog |= QUESTBIT_LEVEL_85;
						sinQuest_Level85.State = 4;
						sinQuest_Level85.BackUpCode = sinQuest_Level85.CODE;
						sinQuest_Level85.CODE = 0;
						EndQuest_Code(sinQuest_Level85.BackUpCode);
						sinQuest_Level85.CODE = 0;
						ReformCharForm();
					}

					if (sinQuest_Level90.State < 3 && sinChar->Level >= 90) {
						CheckCharForm();
						sinQuest_levelLog |= QUESTBIT_LEVEL_90;
						sinQuest_Level90.State = 3;
						sinQuest_Level90.BackUpCode = sinQuest_Level90.CODE;
						sinQuest_Level90.CODE = 0;
						EndQuest_Code(sinQuest_Level90.BackUpCode);
						sinQuest_Level90.CODE = 0;
						ReformCharForm();
						cInvenTory.SetItemToChar();
						if (!cInvenTory.SearchItemCode(sinQT1 | sin07)) {
							SendQuestCommandToServer(SIN_QUEST_CODE_LEVEL90, 0, 0, 0);
						}
					}
					if (sinQuest_Level80_2.State == 3) {
						DeleteQuestItem(sinQT1 | sin09);
						DeleteQuestItem(sinQT1 | sin10);
						DeleteQuestItem(sinQT1 | sin11);
					}
					if (sinQuest_Level80_2.State < 5 && sinChar->Level >= 80) {
						CheckCharForm();
						sinQuest_levelLog |= QUESTBIT_LEVEL_80_2;
						sinQuest_Level80_2.BackUpCode = sinQuest_Level80_2.CODE;
						sinQuest_Level80_2.CODE = 0;
						EndQuest_Code(sinQuest_Level80_2.BackUpCode);
						sinQuest_Level80_2.CODE = 0;
						sinQuest_Level80_2.State = 5;

						if (cInvenTory.SearchItemCode(sinQT1 | sin12)) {
							DeleteQuestItem(sinQT1 | sin12);
						}

						ReformCharStatePoint(sinChar, sinQuest_levelLog);
						ReformCharForm();
						cInvenTory.SetItemToChar();
						sinPlaySound(SIN_SOUND_EAT_POTION2);
						cMessageBox.ShowMessage(MESSAGE_PLUS_POINT_80_2);
						SetQuestBoard();
					}

					if (sinQuest_Level90_2.State < 4 && sinChar->Level >= 90) {
						CheckCharForm();
						sinQuest_levelLog |= QUESTBIT_LEVEL_90_2;
						sinQuest_Level90_2.BackUpCode = sinQuest_Level90_2.CODE;
						sinQuest_Level90_2.CODE = 0;
						EndQuest_Code(sinQuest_Level90_2.BackUpCode);
						sinQuest_Level90_2.CODE = 0;
						sinQuest_Level90_2.State = 4;
						if (cInvenTory.SearchItemCode(sinQT1 | sin13)) {
							DeleteQuestItem(sinQT1 | sin13);
						}
						ReformCharStatePoint(sinChar, sinQuest_levelLog);
						ReformCharForm();
						cInvenTory.SetItemToChar();
						sinPlaySound(SIN_SOUND_EAT_POTION2);
						cMessageBox.ShowMessage(MESSAGE_PLUS_POINT_90_2);
						SetQuestBoard();
					}
				}

				len = rsCompString("/city", szMessage);

				if (len)
				{
					WarpField2(3);
					return TRUE;
				}

				len = rsCompString("/help", szMessage);

				if (len)
				{
					AddChatBuff("> /killme -> Se matar", 5);
					AddChatBuff("> /city -> Teleportar para Ricarten", 5);
					AddChatBuff("> /ConcluirQuests -> Conclui Todas as Quests", 5);
					return TRUE;
				}
				
			}

#ifndef _LANGUAGE_PHILIPIN

			len = rsCompString("/latency", szMessage);
			if (!len)	len = rsCompString("/LATENCY", szMessage);

			if (len)
			{
				lpBuff = szMessage + len;
				lpBuff = rsGetWord(szBuff, lpBuff);
				cnt = atoi(szBuff);
				if (cnt < 0 || cnt>500 || !szBuff[0]) cnt = 30;
				if (cnt < 10) cnt = 0;
				smTransTurbRcvMode = cnt;

				wsprintf(szMessage, ">latency ( %d ms )", cnt);
				AddChatBuff(szMessage, 0);

				return TRUE;
			}
#endif


			len = rsCompString("/camera_wave_off", szMessage);
			if (len)
			{
				WaveCameraMode = FALSE;
				return TRUE;
			}
			













			len = rsCompString("/camera_wave_on", szMessage);
			if (len)
			{
				WaveCameraMode = TRUE;
				return TRUE;
			}


		}


#ifdef	_WINMODE_DEBUG
		int num;
		int r, g, b;

		if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
		{


			len = rsCompString("/dark", szMessage);
			if (len)
			{
				lpBuff = szMessage + len;
				lpBuff = rsGetWord(szBuff, lpBuff);
				cnt = atoi(szBuff);
				if (cnt > -256 && cnt < 256) DarkLevel_Fix = cnt;
				else DarkLevel_Fix = 0;

				return TRUE;
			}


			len = rsCompString("/color", szMessage);
			if (len)
			{
				lpBuff = szMessage + len;
				lpBuff = rsGetWord(szBuff, lpBuff);
				cnt = atoi(szBuff);
				if (cnt > -110 && cnt < 110) r = cnt;
				else return TRUE;
				lpBuff = rsGetWord(szBuff, lpBuff);
				cnt = atoi(szBuff);
				if (cnt > -110 && cnt < 110) g = cnt;
				else return TRUE;
				lpBuff = rsGetWord(szBuff, lpBuff);
				cnt = atoi(szBuff);
				if (cnt > -110 && cnt < 110) b = cnt;
				else return TRUE;

				BackColor_mR = r;
				BackColor_mG = g;
				BackColor_mB = b;

				return TRUE;
			}


			len = rsCompString("/time_offset", szMessage);
			if (len)
			{
				lpBuff = szMessage + len;
				lpBuff = rsGetWord(szBuff, lpBuff);
				cnt = atoi(szBuff);

				dwGameTimeOffset = cnt;
				return TRUE;
			}


			len = rsCompString("/expup", szMessage);
			if (len)
			{
				lpBuff = szMessage + len;
				lpBuff = rsGetWord(szBuff, lpBuff);
				cnt = atoi(szBuff);

				AddExp(cnt);

				wsprintf(szBuff, ">( %d )", cnt);
				AddChatBuff(szBuff);
				return TRUE;
			}


			len = rsCompString("/talk", szMessage);
			if (len)
			{
				lpBuff = szMessage + len;
				len = lstrlen(lpBuff);
				for (cnt = 0; cnt < len; cnt++)
				{
					if (lpBuff[0] == 0) break;
					if (lpBuff[0] != ' ')
					{

						if (chrEachMaster && chrEachMaster->dwObjectSerial)
						{
							wsprintf(szBuff + 8, "/talk %d %s", chrEachMaster->dwObjectSerial, lpBuff);
							len = lstrlen(szBuff + 8) + 10;
							((int *)szBuff)[0] = len;
							((int *)szBuff)[1] = OpCode::OPCODE_CHATMESSAGE;
							lpsmSock = GetAreaServerSock();
							if (lpsmSock)
								lpsmSock->Send(szBuff, len, TRUE);
						}
						return TRUE;
					}
					lpBuff++;
				}
			}


			len = rsCompString("/set_absorb", szMessage);
			if (len)
			{
				lpBuff = szMessage + len;
				len = lstrlen(lpBuff);
				for (cnt = 0; cnt < len; cnt++)
				{
					if (lpBuff[0] == 0) break;
					if (lpBuff[0] != ' ')
					{

						if (chrEachMaster && chrEachMaster->dwObjectSerial)
						{
							wsprintf(szBuff + 8, "/set_absorb %d %s", chrEachMaster->dwObjectSerial, lpBuff);
							len = lstrlen(szBuff + 8) + 10;
							((int *)szBuff)[0] = len;
							((int *)szBuff)[1] = OpCode::OPCODE_CHATMESSAGE;
							lpsmSock = GetAreaServerSock();
							if (lpsmSock)
								lpsmSock->Send(szBuff, len, TRUE);
						}
						return TRUE;
					}
					lpBuff++;
				}
			}


			len = rsCompString("/player_location", szMessage);
			if (len)
			{
				lpBuff = szMessage + len;
				lpBuff = rsGetWord(szBuff, lpBuff);
				lpCurPlayer->pX = atoi(szBuff)*fONE;
				lpBuff = rsGetWord(szBuff, lpBuff);
				lpCurPlayer->pY = atoi(szBuff)*fONE;
				lpBuff = rsGetWord(szBuff, lpBuff);
				lpCurPlayer->pZ = atoi(szBuff)*fONE;
				return TRUE;
			}



			len = rsCompString("/play_movie", szMessage);
			if (len)
			{
				lpBuff = szMessage + len;
				len = lstrlen(lpBuff);
				for (cnt = 0; cnt < len; cnt++)
				{
					if (lpBuff[0] == 0) break;
					if (lpBuff[0] != ' ')
					{
						return Play_ParkPlayer(lpBuff, 200, 200, 320, 240, 120);
					}
					lpBuff++;
				}
			}


			len = rsCompString("/stop_movie", szMessage);
			if (len)
			{
				lpBuff = szMessage + len;
				len = lstrlen(lpBuff);
				for (cnt = 0; cnt < len; cnt++)
				{
					if (lpBuff[0] == 0) break;
					if (lpBuff[0] != ' ')
					{
						return Stop_ParkPlayer();
					}
					lpBuff++;
				}
			}

			len = rsCompString("/load", szMessage);
			if (len)
			{
				lpBuff = szMessage + len;
				len = lstrlen(lpBuff);
				for (cnt = 0; cnt < len; cnt++)
				{
					if (lpBuff[0] == 0) break;
					if (lpBuff[0] != ' ')
					{
						return SendCopyOtherUser(lpBuff, 0);
					}
					lpBuff++;
				}
			}


			len = rsCompString("/body", szMessage);
			if (len)
			{
				lpBuff = szMessage + len;
				len = lstrlen(lpBuff);
				for (cnt = 0; cnt < len; cnt++)
				{
					if (lpBuff[0] == 0) break;
					if (lpBuff[0] != ' ')
					{
						SetPlayerBodyPattern(lpBuff);
						return TRUE;
					}
					lpBuff++;
				}
			}


			len = rsCompString("/mymodel", szMessage);
			if (len && lpCurPlayer->smCharInfo.Level <= 3)
			{
				lpBuff = szMessage + len;
				len = lstrlen(lpBuff);
				for (cnt = 0; cnt < len; cnt++)
				{
					if (lpBuff[0] == 0) break;
					if (lpBuff[0] != ' ')
					{
						SetPlayerPattern(lpBuff);
						return TRUE;
					}
					lpBuff++;
				}
			}


			len = rsCompString("/myhairmodel", szMessage);
			if (len)
			{
				lpBuff = szMessage + len;
				len = lstrlen(lpBuff);
				for (cnt = 0; cnt < len; cnt++)
				{
					if (lpBuff[0] == 0) break;
					if (lpBuff[0] != ' ')
					{
						ChangeHairModel(atoi(lpBuff));
						return TRUE;
					}
					lpBuff++;
				}
			}



			len = rsCompString("/deload", szMessage);
			if (len)
			{
				lpBuff = szMessage + len;
				len = lstrlen(lpBuff);
				for (cnt = 0; cnt < len; cnt++)
				{
					if (lpBuff[0] == 0) break;
					if (lpBuff[0] != ' ')
					{
						return SendCopyOtherUser(lpBuff, 1);
					}
					lpBuff++;
				}
			}


			len = rsCompString("/baload", szMessage);
			if (len)
			{
				lpBuff = szMessage + len;
				len = lstrlen(lpBuff);
				for (cnt = 0; cnt < len; cnt++)
				{
					if (lpBuff[0] == 0) break;
					if (lpBuff[0] != ' ')
					{
						return SendCopyOtherUser(lpBuff, 2);
					}
					lpBuff++;
				}
			}


			len = rsCompString("/ren", szMessage);
			if (len && AdminCharDisable)
			{
				lpBuff = szMessage + len;
				len = lstrlen(lpBuff);
				for (cnt = 0; cnt < len; cnt++)
				{
					if (lpBuff[0] == 0) break;
					if (lpBuff[0] != ' ')
					{
						strcpy_s(lpCurPlayer->smCharInfo.szName, lpBuff);
						ReformCharForm();
						return TRUE;
					}
					lpBuff++;
				}
			}


			len = rsCompString("/ÇÊµåº¯°æ", szMessage);
			if (!len)
				len = rsCompString("/field", szMessage);

			if (len)
			{
				lpBuff = szMessage + len;
				len = lstrlen(lpBuff);
				for (cnt = 0; cnt < len; cnt++)
				{
					if (lpBuff[0] == 0)
						break;
					if (lpBuff[0] != ' ')
					{

						num = atoi(lpBuff);


						WarpField2(num);


						return TRUE;
					}
					lpBuff++;
				}
			}

			len = rsCompString("/save", szMessage);
			if (len)
			{
				cnt = AdminCharDisable;
				AdminCharDisable = FALSE;
				SaveGameData();
				AdminCharDisable = cnt;
			}



			len = rsCompString("/face_path", szMessage);
			if (len)
			{
				lpBuff = szMessage + len;
				len = lstrlen(lpBuff);
				for (cnt = 0; cnt < len; cnt++)
				{
					if (lpBuff[0] == 0) break;
					if (lpBuff[0] != ' ')
					{




						FILE *fp = fopen(lpBuff, "rb");
						if (!fp) return FALSE;
						fclose(fp);


						SetJobFace(lpBuff);
						return TRUE;
					}
					lpBuff++;
				}
			}

			if (AreaServerMode)
			{
				len = rsCompString("/show", szMessage);
				if (!len) len = rsCompString("~/show", szMessage);
				if (len)
				{
					ServerHideMode = FALSE;
				}
				len = rsCompString("/hide", szMessage);
				if (!len) len = rsCompString("~/hide", szMessage);
				if (len)
				{
					ServerHideMode = TRUE;
				}
			}

		}
#endif

	}

	if (smConfig.getSecurity() < AccountTypes::SEC_MODERATOR && szMessage[0] != '/')
	{
		if ((dwPlayTime - dwLastChatTime) < 5000 && lstrcmpi(szLastChatMessage, szMessage) == 0)
		{

			return TRUE;
		}
	}

	strcpy_s(szLastChatMessage, szMessage);
	dwLastChatTime = dwPlayTime;

#ifdef _LANGUAGE_KOREAN
	if ((szMessage[0] == '/' && (szMessage[1] == ';' || szMessage[1] == ':')) ||
		(szMessage[1] == '/' && (szMessage[2] == ';' || szMessage[2] == ':')))
	{


		cnt = 0;
		lpMsg = szMessage;
		while (1)
		{
			if (!szMessage[cnt]) break;
			if (szMessage[cnt] == ' ')
			{
				lpMsg = &szMessage[cnt + 1];
				break;
			}
			cnt++;
		}
		ConvertString(lpMsg, lstrlen(lpMsg) + 16);
	}
#endif
#ifdef _LANGUAGE_CHINESE
	if ((szMessage[0] == '/' && (szMessage[1] == ';' || szMessage[1] == ':')) ||
		(szMessage[1] == '/' && (szMessage[2] == ';' || szMessage[2] == ':')))
	{


		cnt = 0;
		lpMsg = szMessage;
		while (1)
		{
			if (!szMessage[cnt]) break;
			if (szMessage[cnt] == ' ')
			{
				lpMsg = &szMessage[cnt + 1];
				break;
			}
			cnt++;
		}
		ConvertStringTHAI(lpMsg, lstrlen(lpMsg) + 16);
	}
#endif

#ifdef _LANGUAGE_THAI
	if ((szMessage[0] == '/' && (szMessage[1] == ';' || szMessage[1] == ':')) ||
		(szMessage[1] == '/' && (szMessage[2] == ';' || szMessage[2] == ':')))
	{


		cnt = 0;
		lpMsg = szMessage;
		while (1)
		{
			if (!szMessage[cnt]) break;
			if (szMessage[cnt] == ' ')
			{
				lpMsg = &szMessage[cnt + 1];
				break;
			}
			cnt++;
		}
		ConvertStringTHAI(lpMsg, lstrlen(lpMsg) + 16);
	}
#endif

	szMessage[78] = 0;
	return rsMainServer.SendChat(szMessage);
}



int ChatScrollPoint = 0;


int DisplayChatMessage(HDC hdc, int x, int y, int MaxLine)
{
	int cnt;
	int chatCnt;
	char *lpString;
	int start, end;

	if (ChatDispCnt == 0) return FALSE;

	if (ChatScrollPoint > CHATBUFF_MASK)
		ChatScrollPoint = CHATBUFF_MASK;
	if (ChatScrollPoint < 0)
		ChatScrollPoint = 0;

	start = ChatBuffCnt - MaxLine - ChatScrollPoint;
	end = ChatBuffCnt - ChatScrollPoint;

	for (cnt = start; cnt < end; cnt++)
	{
		if (cnt >= 0)
		{
			chatCnt = cnt & CHATBUFF_MASK;
			lpString = ChatBuff[chatCnt].szMessage;

			SetFontTextColor( RGB(0, 0, 0));
			dsTextLineOut( x + 1, y + 1, lpString, lstrlen(lpString));
			if (ChatBuff[chatCnt].dwIP == dwMyIP)
				SetFontTextColor( RGB(255, 128, 96));
			else
			{
				SetFontTextColor( RGB(255, 255, 128));

				switch (ChatBuff[chatCnt].dwIP)
				{
				case 1:
					SetFontTextColor( RGB(255, 128, 96));
					break;
				case 2:
					SetFontTextColor( RGB(96, 256, 255));
					break;
				}
			}
			dsTextLineOut( x, y, lpString, lstrlen(lpString));
		}
		y += 16;
	}

	return TRUE;
}










int GetNextLineCount(char *szString, int LineMax)
{
	int cnt;
	int len;
	char *lp;

	len = lstrlen(szString);
	if (len <= LineMax) return 0;

	lp = szString;

	cnt = 0;

	while (1)
	{

		if (CheckCode_2Byte(lp) == 2)
		{
			cnt += 2;
			lp += 2;
		}
		else
		{
			cnt++;
			lp++;
		}

		if (cnt > (LineMax - 2)) break;
	}


	return cnt;
}

int SetIpColor( DWORD dwIP)
{

	if (dwIP == dwMyIP)
	{
		SetFontTextColor( RGB(255, 128, 96));
		return TRUE;
	}
	//CORES DO CHAT
	switch (dwIP)
	{
	case 0:		SetFontTextColor(RGB(255, 128, 96));		break;
	case 1:		SetFontTextColor(RGB(150, 190, 255));		break;
	case 2:		SetFontTextColor(RGB(150, 190, 255));		break;
	case 3:		SetFontTextColor(RGB(230, 160, 255));		break;
	case 4:		SetFontTextColor(RGB(200, 255, 0));		break;
	case 5:		SetFontTextColor(RGB(255, 255, 80));		break;
	case 6:		SetFontTextColor(RGB(200, 255, 255));		break;
	case 9:		SetFontTextColor(RGB(200, 128, 128));		break;
	case 10:	SetFontTextColor(RGB(230, 160, 255));		break;
	case 11:	SetFontTextColor(RGB(238, 173, 45));		break;
	case 12:	SetFontTextColor(RGB(255, 176, 127));		break;
	case 13:	SetFontTextColor(RGB(255, 47, 41));		break;
	case 14:	SetFontTextColor(RGB(117, 254, 255));		break;
	default:	SetFontTextColor(RGB(255, 255, 192));		break;
	}

	return TRUE;
}

static int	DisplayChatFilter = -1;
int	DispChatMsgHeight = 6;
int	DispChatMode = 0;


int	SetChatMsgFilter(int mode)
{

	DisplayChatFilter = -1;
	ChatScrollPoint = 0;

	switch (mode)
	{
	case 0:
		DisplayChatFilter = -1;
		break;

	case 1:
		DisplayChatFilter = 5;
		break;

	case 2:
		DisplayChatFilter = 4;
		break;

	case 3:
		DisplayChatFilter = 6;
		break;

	case 4:
		DisplayChatFilter = 1;
		break;
	}

	DispChatMode = mode;

	return TRUE;
}

int ChatBuffSort()
{
	int cnt, cnt2;
	int mCnt, nCnt;
	int	Col;

	if (ChatBuffCnt <= ChatBuffCompCnt) return FALSE;

	for (cnt = ChatBuffCompCnt; cnt < ChatBuffCnt; cnt++)
	{
		mCnt = cnt & CHATBUFF_MASK;
		Col = 0;
		switch (ChatBuff[mCnt].dwIP)
		{
		case 5:
			Col = 1;
			break;
		case 4:
			Col = 2;
			break;

		case 6:
			Col = 3;
			break;
		case 1:
			Col = 4;
			break;

		case 9:
			Col = 5;
			break;
		}
		nCnt = ChatBuffCnt2[Col] & CHATBUFF_MASK;
		memcpy(&ChatBuff2[Col][nCnt], &ChatBuff[mCnt], sizeof(CHATBUFF));
		ChatBuffCnt2[Col]++;

		if (Col > 0 && Col < 5)
		{
			nCnt = ChatBuffCnt2[0] & CHATBUFF_MASK;
			memcpy(&ChatBuff2[0][nCnt], &ChatBuff[mCnt], sizeof(CHATBUFF));
			ChatBuffCnt2[0]++;
		}

		if (Col == 0 && ChatBuff[mCnt].dwIP < 10)
		{
			for (cnt2 = 1; cnt2 < 5; cnt2++)
			{
				nCnt = ChatBuffCnt2[cnt2] & CHATBUFF_MASK;
				memcpy(&ChatBuff2[cnt2][nCnt], &ChatBuff[mCnt], sizeof(CHATBUFF));
				ChatBuffCnt2[cnt2]++;
			}
		}
	}

	ChatBuffCompCnt = ChatBuffCnt;

	return TRUE;
}

int DisplayChatMessage3(int x, int y, int StrMax, int LineMax, int Mode)
{
	int result;
	int ModeBackup = DispChatMode;
	int	ScrollBackup = ChatScrollPoint;

	DispChatMode = Mode;
	if (LineMax <= 6)
		ChatScrollPoint = 0;

	result = DisplayChatMessage2(x, y, StrMax, LineMax);

	DispChatMode = ModeBackup;
	ChatScrollPoint = ScrollBackup;
	return result;
}


int DisplayChatMessage2( int x, int y, int StrMax, int LineMax)
{
	int cnt = 0;
	int chatCnt = 0;
	char *lpString = nullptr;
	int LineCnt = 0;
	int CutPos = 0;
	int len = 0;
	int start = 0;
	int end = 0;
	int fl_Count = 0;

	DWORD shColor = RGB(74, 74, 74);

	ChatBuffSort();

	LineCnt = 0;

	if (ChatScrollPoint > (CHATBUFF_MAX - 32))
		ChatScrollPoint = (CHATBUFF_MAX - 32);
	if (ChatScrollPoint < 0)
		ChatScrollPoint = 0;

	fl_Count = DispChatMode;
	if (fl_Count < 0) fl_Count = 0;

	start = ChatBuffCnt2[fl_Count] - 1 - ChatScrollPoint;
	end = ChatBuffCnt2[fl_Count] - 32 - ChatScrollPoint;

	DispChatMsgHeight = 0;

	for (cnt = start; cnt >= end; cnt--)
	{
		if (cnt >= 0)
		{
			chatCnt = cnt & CHATBUFF_MASK;

			lpString = ChatBuff2[fl_Count][chatCnt].szMessage;

			DispChatMsgHeight++;

			len = lstrlen(lpString);
			if (len > StrMax)
			{

				CutPos = GetNextLineCount(lpString, StrMax);

				SetFontTextColor( shColor);
				dsTextLineOut( x - 1, y - 1, lpString + CutPos, len - CutPos);
				SetIpColor(ChatBuff2[fl_Count][chatCnt].dwIP);
				dsTextLineOut( x, y, lpString + CutPos, len - CutPos);

				y -= 12;
				LineCnt++;
				if (LineCnt >= LineMax) break;

				SetFontTextColor( shColor);
				dsTextLineOut( x - 1, y - 1, lpString, CutPos);
				SetIpColor(ChatBuff2[fl_Count][chatCnt].dwIP);


				char semi[MAX_PATH] = { 0 };
				char presemi[MAX_PATH] = { 0 };
				char backsemi[MAX_PATH] = { 0 };

				bool bsemi = 0;

				strcpy_s(semi, sizeof(semi), lpString);

				int k = 0, prelen = 0, lenth = 0;

				lenth = strlen(semi);

				for (int i = 0; i < lenth; i++)
				{
					backsemi[k] = semi[i];

					k++;

					if ((bsemi == 0) && (semi[i] == ':'))
					{
						strcpy_s(presemi, sizeof(presemi), backsemi);
						ZeroMemory(backsemi, MAX_PATH);
						bsemi++;
						k = 0;
					}
				}

				if (bsemi)
				{
					SIZE size;

					prelen = strlen(presemi);
					SetFontTextColor( RGB(100, 255, 50));
					dsTextLineOut( x, y, presemi, prelen);
					GetFontTextExtentPoint( presemi, prelen, &size);

					int j = 0;
					j = x + size.cx;
					SetIpColor(ChatBuff2[fl_Count][chatCnt].dwIP);
					dsTextLineOut( j, y, backsemi, CutPos - prelen);
				}
				else dsTextLineOut( x, y, lpString, CutPos);

				y -= 12;
				LineCnt++;
				if (LineCnt >= LineMax) break;

			}
			else
			{

				SetFontTextColor( shColor);
				dsTextLineOut( x - 1, y - 1, lpString, len);
				SetIpColor(ChatBuff2[fl_Count][chatCnt].dwIP);

				char semi[MAX_PATH] = { 0 };
				char presemi[MAX_PATH] = { 0 };
				char backsemi[MAX_PATH] = { 0 };

				bool bsemi = 0;
				strcpy_s(semi, sizeof(semi), lpString);

				int k = 0, prelen = 0, lenth = 0;
				lenth = strlen(semi);

				for (int i = 0; i < lenth; i++)
				{
					backsemi[k] = semi[i];
					k++;
					if ((bsemi == 0) && (semi[i] == ':'))
					{
						strcpy_s(presemi, sizeof(presemi), backsemi);
						ZeroMemory(backsemi, MAX_PATH);
						bsemi++;
						k = 0;
					}
				}

				if (bsemi)
				{
					SIZE size;

					prelen = strlen(presemi);
					SetFontTextColor( RGB(100, 255, 50));
					dsTextLineOut( x, y, presemi, prelen);
					GetFontTextExtentPoint( presemi, prelen, &size);

					int j = x + size.cx;
					SetIpColor(ChatBuff2[fl_Count][chatCnt].dwIP);
					dsTextLineOut( j, y, backsemi, strlen(backsemi));
				}
				else dsTextLineOut( x, y, lpString, len);


				y -= 12;
				LineCnt++;
				if (LineCnt >= LineMax) break;
			}

		}
	}

	return TRUE;
}


int ConnectPlayer(smWINSOCK *lpsmSock)
{
	Log::getInstance()->output(LOG_DEBUG, "ConnectPlayer");
	int OthPlayerCnt;

	if (ServerMode)
		return Serv_ConnectPlayer(lpsmSock);



	EnterCriticalSection(&cSection);

	OthPlayerCnt = FindNewOtherPlayer();
	if (OthPlayerCnt >= 0)
	{
		lpsmSock->ExtData1 = (void *)&chrOtherPlayer[OthPlayerCnt];
		chrOtherPlayer[OthPlayerCnt].Init();
		chrOtherPlayer[OthPlayerCnt].TransSendWait = 1;
		chrOtherPlayer[OthPlayerCnt].TransSock = lpsmSock;
		chrOtherPlayer[OthPlayerCnt].TransLastSendCnt = PlayCounter - 70;
		chrOtherPlayer[OthPlayerCnt].Flag = 1;
		chrOtherPlayer[OthPlayerCnt].smCharInfo.szName[0] = 0;
		chrOtherPlayer[OthPlayerCnt].ActionPattern = 99;
		chrOtherPlayer[OthPlayerCnt].Pattern = 0;
		chrOtherPlayer[OthPlayerCnt].AutoPlayer = 0;

		lpCurPlayer->SendCharInfo(lpsmSock);


	}


	LeaveCriticalSection(&cSection);

	return TRUE;
}


int DisconnectPlayer(smWINSOCK *lpsmSock)
{
	if (ServerMode)
		return Serv_DisconnectPlayer(lpsmSock);

	DWORD dwTime = GetCurrentTime();

	if (smWsockServer && lpsmSock->sock == smWsockServer->sock)
	{
		AddChatBuff("Connection lost to Server");
		if (smWsockServer == smWsockDataServer)
			smWsockDataServer = 0;
		if (smWsockServer == smWsockUserServer)
			smWsockUserServer = 0;
		if (smWsockServer == smWsockExtendServer)
			smWsockExtendServer = 0;
		//LOG_GAME
		smWsockServer = 0;
		Log::getInstance()->output(LOG_GAME, "SetDisconnectFlag: 14");
		DisconnectFlag = dwTime;


		if (cTrade.OpenFlag)
		{
			SendRequestTrade(cTrade.TradeCharCode, 3);
			cTrade.CancelTradeItem();
		}
		return TRUE;
	}

	if (smWsockDataServer && lpsmSock->sock == smWsockDataServer->sock)
	{//LOG_GAME
		AddChatBuff("Connection lost to Dataserver");
		smWsockDataServer = 0;
		Log::getInstance()->output(LOG_GAME, "SetDisconnectFlag: 15");
		DisconnectFlag = dwTime;



		if (cTrade.OpenFlag)
		{
			SendRequestTrade(cTrade.TradeCharCode, 3);
			cTrade.CancelTradeItem();
		}
		return TRUE;
	}

	if (smWsockUserServer && lpsmSock->sock == smWsockUserServer->sock)
	{//LOG_GAME
		AddChatBuff("Connection lost to Server");
		smWsockUserServer = 0;
		Log::getInstance()->output(LOG_GAME, "SetDisconnectFlag: 16");
		DisconnectFlag = dwTime;


		if (cTrade.OpenFlag)
		{
			SendRequestTrade(cTrade.TradeCharCode, 3);
			cTrade.CancelTradeItem();
		}
		return TRUE;
	}

	if (smWsockExtendServer && lpsmSock->sock == smWsockExtendServer->sock)
	{//
		AddChatBuff("Connection lost to Server");
		smWsockExtendServer = 0;
		Log::getInstance()->output(LOG_GAME, "SetDisconnectFlag: 18");
		DisconnectFlag = dwTime;


		if (cTrade.OpenFlag)
		{
			SendRequestTrade(cTrade.TradeCharCode, 3);
			cTrade.CancelTradeItem();
		}
		return TRUE;

	}

	char szBuff[256];


	if (AreaServerMode)
	{
		if (lpWSockServer_Area[0] && lpWSockServer_Area[0]->sock == lpsmSock->sock)
		{
			if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
			{
				wsprintf(szBuff, "Disconnect Area Server (%s)", lpWSockServer_Area[0]->szIPAddr);
				AddChatBuff(szBuff, 0);
			}
			if (lpWSockServer_Area[0] == lpWSockServer_DispArea[0]) lpWSockServer_DispArea[0] = 0;
			if (lpWSockServer_Area[0] == lpWSockServer_DispArea[1]) lpWSockServer_DispArea[1] = 0;

			lpWSockServer_Area[0] = 0;
			return TRUE;
		}
		if (lpWSockServer_Area[1] && lpWSockServer_Area[1]->sock == lpsmSock->sock)
		{
			if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
			{
				wsprintf(szBuff, "Disconnect Area Server (%s)", lpWSockServer_Area[1]->szIPAddr);
				AddChatBuff(szBuff, 0);
			}

			if (lpWSockServer_Area[1] == lpWSockServer_DispArea[0]) lpWSockServer_DispArea[0] = 0;
			if (lpWSockServer_Area[1] == lpWSockServer_DispArea[1]) lpWSockServer_DispArea[1] = 0;

			lpWSockServer_Area[1] = 0;
			return TRUE;
		}
	}




	EnterCriticalSection(&cSection);

	smCHAR *lpPlayer = (smCHAR *)lpsmSock->ExtData1;

	if (lpPlayer)
		lpPlayer->Close();

	LeaveCriticalSection(&cSection);

	return TRUE;
}


int Ts_LastSendCounter;
DWORD	dwLastSendPosiTime = 0;
DWORD	dwLastSendPlayTime = 0;


int SendPlayDataToServer()
{
	if (smWsockServer != smWsockUserServer || AreaServerMode)
	{
		return rsMainServer.SendPlayData(lpCurPlayer);
	}

	return TRUE;
}



int ConnectOtherPlayer(DWORD dwIP)
{
	smWINSOCK *lpsmSock;
	int OthPlayerCnt;

	OthPlayerCnt = FindNewOtherPlayer();
	if (OthPlayerCnt >= 0)
	{
		lpsmSock = smConnectSock2(ConvStrIP(dwIP), TCP_GAMEPORT);
		if (lpsmSock)
		{
			ConnectPlayer(lpsmSock);
			return TRUE;
		}
	}
	return FALSE;
}

DWORD WINAPI ConnectPlayThreadProc(void *pInfo)
{

	ConnectOtherPlayer((DWORD)pInfo);

	ExitThread(TRUE);
	return TRUE;
}

DWORD WINAPI DisconnectPlayThreadProc(void *pInfo)
{

	((smWINSOCK *)pInfo)->CloseSocket();

	ExitThread(TRUE);
	return TRUE;
}




int CreateConnectThread(DWORD dwIP)
{
	DWORD dwMsgId;
	CreateThread(NULL, 0, ConnectPlayThreadProc, (void *)dwIP, 0, &dwMsgId);

	return TRUE;
}


int CreateDisconnectThread(smWINSOCK *lpsmSock)
{
	DWORD dwMsgId;
	CreateThread(NULL, 0, DisconnectPlayThreadProc, (void *)lpsmSock, 0, &dwMsgId);

	return TRUE;
}



int DisconnectFarPlayer()
{
	int mx, mz, dDist;
	int cnt;
	int timeover;

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{

		if (chrOtherPlayer[cnt].Flag)
		{

			if ((chrOtherPlayer[cnt].dwLastTransTime + DIS_TIME_OVER) < dwPlayTime)
				timeover = TRUE;
			else
				timeover = FALSE;


			mx = (lpCurPlayer->pX - chrOtherPlayer[cnt].pX) >> FLOATNS;
			mz = (lpCurPlayer->pZ - chrOtherPlayer[cnt].pZ) >> FLOATNS;
			dDist = mx * mx + mz * mz;

			if ((chrOtherPlayer[cnt].DisplayFlag && dDist > DIST_TRANSLEVEL_DISCONNECT) || timeover)
			{

				chrOtherPlayer[cnt].Flag = 0;

				if (chrOtherPlayer[cnt].TransSock)
				{
					chrOtherPlayer[cnt].TransSock->CloseSocket();
				}
				else
				{

					EnterCriticalSection(&cSection);
					chrOtherPlayer[cnt].Close();

					LeaveCriticalSection(&cSection);
				}
			}
		}
	}

	return TRUE;
}

DWORD	dwExtendServ_RecvTime = 0;
DWORD	dwUserServ_RecvTime = 0;
DWORD	dwMainServ_RecvTime = 0;
DWORD	dwDataServ_RecvTime = 0;


int RecvPlayData(smTHREADSOCK *pData)
{

	DWORD *IPData;


	DWORD	dwTime;


	EnterCriticalSection(&cSection);


	IPData = (DWORD *)(pData->Buff);



	dwTime = GetCurrentTime();

	if (pData->smMySock == smWsockDataServer)
	{
		dwRecvDataServerTime = dwTime;
		dwDataServ_RecvTime = dwTime;
	}
	if (pData->smMySock == smWsockUserServer)
	{
		dwRecvUserServerTime = dwTime;
		dwUserServ_RecvTime = dwTime;
		Debug_RecvCount2++;
	}
	if (pData->smMySock == smWsockExtendServer)
	{
		dwRecvExtendServerTime = dwTime;
		dwExtendServ_RecvTime = dwTime;
		Debug_RecvCount3++;
	}
	if (pData->smMySock == smWsockServer)
	{
		Debug_RecvCount1++;
		dwRecvServerTime = dwTime;
		dwMainServ_RecvTime = dwTime;
	}


	rsMainServer.RecvMessage(pData);


	LeaveCriticalSection(&cSection);

	return TRUE;
}


int PlayRecvMessageQue()
{
	return rsMainServer.RecvMessageQue();
}


int LastSendCnt;

#define	NET_SENDING_WAIT_TIME		400
#define	NET_SENDING_WAIT_TIME2		1000

int NetStandCnt = 0;
extern int GameMode;

DWORD	NetScoopTime = 2000;


int NetWorkPlay()
{
	int cnt = 0;
	DWORD dwTime = 0;
	DWORD dwTime2 = 0;
	smWINSOCK *lpsmSock = nullptr;

	switch (cldata.CNFlag)
	{
	case 0:
		if (cSkill.SearchContiueSkillCODE(SOD_SKILL_GOLD))
			cSkill.CancelContinueSkill(SOD_SKILL_GOLD);
		else if (cSkill.SearchContiueSkillCODE(SOD_SKILL_SILVER))
			cSkill.CancelContinueSkill(SOD_SKILL_SILVER);
		else if (cSkill.SearchContiueSkillCODE(SOD_SKILL_BRONZE))
			cSkill.CancelContinueSkill(SOD_SKILL_BRONZE);
		break;
	case 1:

		if (cSkill.SearchContiueSkillCODE(SOD_SKILL_GOLD) != SOD_SKILL_GOLD)
		{

			sSKILL TempSkill;
			memset(&TempSkill, 0, sizeof(sSKILL));
			TempSkill.CODE = SOD_SKILL_GOLD;
			TempSkill.UseTime = 604800;
			TempSkill.Point = 1;
			sinContinueSkillSet(&TempSkill);
			sinPlaySound(SIN_SOUND_EAT_POTION2);

			if (cSkill.SearchContiueSkillCODE(SOD_SKILL_SILVER))
				cSkill.CancelContinueSkill(SOD_SKILL_SILVER);
			else if (cSkill.SearchContiueSkillCODE(SOD_SKILL_BRONZE))
				cSkill.CancelContinueSkill(SOD_SKILL_BRONZE);

			cInvenTory.SetItemToChar();
		}
		break;
	case 2:

		if (cSkill.SearchContiueSkillCODE(SOD_SKILL_SILVER) != SOD_SKILL_SILVER)
		{

			sSKILL TempSkill;
			memset(&TempSkill, 0, sizeof(sSKILL));
			TempSkill.CODE = SOD_SKILL_SILVER;
			TempSkill.UseTime = 604800;
			TempSkill.Point = 1;
			sinContinueSkillSet(&TempSkill);
			sinPlaySound(SIN_SOUND_EAT_POTION2);

			if (cSkill.SearchContiueSkillCODE(SOD_SKILL_GOLD))
				cSkill.CancelContinueSkill(SOD_SKILL_GOLD);
			else if (cSkill.SearchContiueSkillCODE(SOD_SKILL_BRONZE))
				cSkill.CancelContinueSkill(SOD_SKILL_BRONZE);

			cInvenTory.SetItemToChar();
		}

		break;
	case 3:

		if (cSkill.SearchContiueSkillCODE(SOD_SKILL_BRONZE) != SOD_SKILL_BRONZE)
		{

			sSKILL TempSkill;
			memset(&TempSkill, 0, sizeof(sSKILL));
			TempSkill.CODE = SOD_SKILL_BRONZE;
			TempSkill.UseTime = 604800;
			TempSkill.Point = 1;
			sinContinueSkillSet(&TempSkill);
			sinPlaySound(SIN_SOUND_EAT_POTION2);

			if (cSkill.SearchContiueSkillCODE(SOD_SKILL_SILVER))
				cSkill.CancelContinueSkill(SOD_SKILL_SILVER);
			else if (cSkill.SearchContiueSkillCODE(SOD_SKILL_GOLD))
				cSkill.CancelContinueSkill(SOD_SKILL_GOLD);

			cInvenTory.SetItemToChar();
		}

		break;

	}

	if (lpCurPlayer->BlessCrown == 2)
	{
		if (cSkill.SearchContiueSkillCODE(BC_SKILL_BRONZE))
			cSkill.CancelContinueSkill(BC_SKILL_BRONZE);

		if (cSkill.SearchContiueSkillCODE(BC_SKILL_SILVER) != BC_SKILL_SILVER)
		{
			sSKILL TempSkill;
			memset(&TempSkill, 0, sizeof(sSKILL));
			TempSkill.CODE = BC_SKILL_SILVER;
			TempSkill.UseTime = 604800;
			TempSkill.Point = 1;
			sinContinueSkillSet(&TempSkill);
			sinPlaySound(SIN_SOUND_EAT_POTION2);
		}

	}
	else if (lpCurPlayer->BlessCrown == 3)
	{
		if (cSkill.SearchContiueSkillCODE(BC_SKILL_SILVER))
			cSkill.CancelContinueSkill(BC_SKILL_SILVER);

		if (cSkill.SearchContiueSkillCODE(BC_SKILL_BRONZE) != BC_SKILL_BRONZE)
		{
			sSKILL TempSkill;
			memset(&TempSkill, 0, sizeof(sSKILL));
			TempSkill.CODE = BC_SKILL_BRONZE;
			TempSkill.UseTime = 604800;
			TempSkill.Point = 1;
			sinContinueSkillSet(&TempSkill);
			sinPlaySound(SIN_SOUND_EAT_POTION2);
		}
	}
	else
	{
		if (cSkill.SearchContiueSkillCODE(BC_SKILL_BRONZE))
			cSkill.CancelContinueSkill(BC_SKILL_BRONZE);

		if (cSkill.SearchContiueSkillCODE(BC_SKILL_SILVER))
			cSkill.CancelContinueSkill(BC_SKILL_SILVER);
	}

	if (NetWorkInitFlag == 0)
	{
		if (!smWsockServer || !smWsockDataServer || !smWsockUserServer || !smWsockExtendServer)
		{
			if (ConnectServer_Main() == NULL)
				return FALSE;

		}

		NetWorkInitFlag = TRUE;

		rsMainServer.Init(smWsockServer);

		SendPlayDataToServer();


		if (smWsockDataServer)
		{
			SendGetRecordData(lpCurPlayer->smCharInfo.szName);


			if (smWsockServer && smWsockDataServer != smWsockServer)
			{
				SendCheckIP(1, smWsockServer);
			}
			if (smWsockUserServer && smWsockDataServer != smWsockUserServer)
			{
				SendCheckIP(2, smWsockUserServer);
			}
			if (smWsockExtendServer && smWsockExtendServer != smWsockServer && smWsockDataServer != smWsockExtendServer)
			{
				SendCheckIP(3, smWsockExtendServer);
			}
		}

		ChatBuffCnt = 0;
		ChatDispCnt = 0;

		Ts_LastSendCounter = PlayCounter;
		TransThrowItem.code = 0;

		RecordFailCount = 0;
		dwLastWareHouseChkSum = 0;

		TransAgingItemFlag = 0;


		ZeroMemory(&TransRecvItem, sizeof(TRANS_ITEMINFO));

		Trans_SplashCharList.code = 0;

		ZeroMemory(&PK_FieldState, sizeof(PK_FIELD_STATE));
		PK_FieldState.FieldCode = -1;



		ClearAttMonsterCode();

		Init_RecordDamage();

		switch (cSettings::GetInstance()->cNetwork)
		{
		case 0:
			NetScoopTime = 3000;
			break;
		case 1:
			NetScoopTime = 2000;
			break;
		case 2:
			NetScoopTime = 1000;
			break;
		case 3:
			NetScoopTime = 5000;
			smTransTurbRcvMode = 50;
			break;
		}

	}
	else
	{
		if (cTrade.OpenFlag)
		{

			if (!TradeSendSucessFlag && sTrade.CheckFlag && sTradeRecv.CheckFlag)
			{
				SendTradeCheckItem(cTrade.TradeCharCode);
				TradeSendSucessFlag = TRUE;
			}
		}
		if (dwTradeMaskTime)
		{

			if (dwTradeMaskTime < dwPlayTime) dwTradeMaskTime = 0;
		}

		dwTime = dwPlayTime - dwLastSendPosiTime;
		dwTime2 = dwPlayTime - dwRecvServerTime;


		if ((PlayCounter - Ts_LastSendCounter) > PLAYSERVER_SENDCOUNTER)
		{


			SendPlayDataToServer();

			DisconnectFarPlayer();


			Ts_LastSendCounter = PlayCounter;
			dwLastSendPosiTime = dwPlayTime;
		}






		if (smWsockUserServer)
		{



			dwTime = dwPlayTime - dwLastSendPlayTime;
			dwTime2 = dwPlayTime - dwRecvUserServerTime;


			if ((lpCurPlayer->PlayBuffCnt & 0x3F) == 0 && lpCurPlayer->dwObjectSerial &&
				dwTime > NET_SENDING_WAIT_TIME)
			{

				if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR && AdminCharDisable)
				{
					if (smWsockServer == smWsockUserServer)
					{
						rsMainServer.SendPlayData(lpCurPlayer);
					}
				}
				else
				{
					if (AreaServerMode)
					{
						if (lpCurPlayer->OnStageField >= 0)
						{
							lpsmSock = lpWSockServer_DispArea[lpCurPlayer->OnStageField];
						}

					}
					else
					{
						lpsmSock = smWsockUserServer;
					}

					if (lpsmSock)
					{
						lpCurPlayer->MakeTransPlayData(lpCurPlayer->srTransBuff, 0x40);
						if (((smTRANS_PLAYDATA *)lpCurPlayer->srTransBuff)->PlayBuffCnt > 1)
						{

							lpsmSock->Send(lpCurPlayer->srTransBuff, ((smTRANS_PLAYDATA *)lpCurPlayer->srTransBuff)->size, TRUE);
							NetStandCnt = 0;
						}
						else
						{



							lpsmSock->Send(lpCurPlayer->srTransBuff, ((smTRANS_PLAYDATA *)lpCurPlayer->srTransBuff)->size, TRUE);
							NetStandCnt++;
						}
					}
				}

				Debug_SendCount++;

				rsRecvUserServer = FALSE;
				dwLastSendPlayTime = dwPlayTime;
			}
		}


		if (dwLoadingTime)
		{
			dwTime = GetCurrentTime();
			if (dwTime > (dwLoadingTime + NET_LOADING_WAIT_LIMIT))
			{
				//LOG_GAME
				Log::getInstance()->output(LOG_GAME, "SetDisconnectFlag: 19");
				DisconnectFlag = GetCurrentTime();
				dwLoadingTime = 0;
			}
		}


		cnt = PlayCounter & 0x1FF;
		if (cnt == 0)
		{

			TransCheckNetwork();
		}
		else if (cnt == 0x80)
		{

			SendPlayTimerMax();
		}



		if ((PlayCounter & 0x1F) == 0)
		{
			dwTime = GetCurrentTime();
			if (GameMode == 2 && dwMainServ_RecvTime && smWsockServer && (dwTime - dwMainServ_RecvTime) > 3000)
			{

				if (smWsockServer->WaitReadMessage >= 0)
				{
					smWsockServer->WaitReadMessage += 24;
					if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
						AddChatBuff("Scoop Recv Route(Main)");
				}
				else
				{
					if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
						AddChatBuff("Error Server(Main)");
				}
			}
			if (GameMode == 2 && smWsockUserServer && dwUserServ_RecvTime &&
				smWsockServer != smWsockUserServer && (dwTime - dwUserServ_RecvTime) > 3000)
			{

				if (smWsockUserServer->WaitReadMessage >= 0)
				{
					smWsockUserServer->WaitReadMessage += 24;
					if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
						AddChatBuff("Scoop Recv Route(User)");
				}
				else
				{
					if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
						AddChatBuff("Error Server(User)");
				}
			}
			if (GameMode == 2 && smWsockExtendServer && dwExtendServ_RecvTime &&
				smWsockServer != smWsockExtendServer && (dwTime - dwExtendServ_RecvTime) > 3000)
			{

				if (smWsockExtendServer->WaitReadMessage >= 0)
				{
					smWsockExtendServer->WaitReadMessage += 24;
					if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
						AddChatBuff("Scoop Recv Route(Extend)");
				}
				else
				{
					if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
						AddChatBuff("Error Server(Extend)");
				}
			}


			if (GameMode == 2 && ((dwTime - dwDataServ_RecvTime) > 7000 || dwLoadingTime) && smWsockDataServer && smWsockDataServer != smWsockServer)
			{
				smWsockDataServer->WaitReadMessage += 24;
				if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR && DisplayDebug)
					AddChatBuff("Scoop Recv Route(Data)");
			}

			if (GameMode == 2 && AreaServerMode)
			{
				if (lpWSockServer_Area[0] && lpWSockServer_Area[0]->dwLastRecvTime)
				{
					if ((dwTime - lpWSockServer_Area[0]->dwLastRecvTime) > 2000)
					{
						lpWSockServer_Area[0]->WaitReadMessage += 24;
						smCheckWaitMessage(lpWSockServer_Area[0]);
					}
				}
				if (lpWSockServer_Area[1] && lpWSockServer_Area[1]->dwLastRecvTime)
				{
					if ((dwTime - lpWSockServer_Area[1]->dwLastRecvTime) > 2000)
					{
						lpWSockServer_Area[1]->WaitReadMessage += 24;
						smCheckWaitMessage(lpWSockServer_Area[1]);
					}
				}



			}




		}


	}
#ifndef _LANGUAGE_CHINESE	
#ifndef _LANGUAGE_VEITNAM	
#ifndef _LANGUAGE_PHILIPIN	
#ifndef _LANGUAGE_ENGLISH	










#endif
#endif
#endif
#endif



	if (dwLastTransTradeKeyTime && (dwLastTransTradeKeyTime + 800) < dwPlayTime)
	{
		if (smWsockDataServer)
			smWsockDataServer->Send((char *)&LastTransTradeItemKey, LastTransTradeItemKey.size, TRUE);

		dwLastTransTradeKeyTime = 0;
	}


	if (ChatDispCnt > 0) ChatDispCnt--;

	return TRUE;
}



int ThrowPutItem(sITEM *lpItem, int x, int y, int z)
{


	if ((dwRecvServerTime + 4000) < dwPlayTime || QuitSave || TransThrowItem.code)
		return FALSE;

	if (AdminCharDisable || WarningHack || !smWsockDataServer || !smWsockServer)
		return FALSE;


	if (!SendSaveThrowItem2(&lpItem->sItemInfo))
		return FALSE;

	TransThrowItem.code = OpCode::OPCODE_THROWITEM;
	TransThrowItem.size = sizeof(TRANS_ITEMINFO);
	TransThrowItem.x = x;
	TransThrowItem.y = y;
	TransThrowItem.z = z;

	memcpy(&TransThrowItem.Item, &lpItem->sItemInfo, sizeof(sITEMINFO));

	return TRUE;
}

int ThrowPutItem2(sITEMINFO *lpItem, int x, int y, int z)
{


	if ((dwRecvServerTime + 4000) < dwPlayTime || QuitSave || TransThrowItem.code)
		return FALSE;

	if (AdminCharDisable || WarningHack || !smWsockDataServer || !smWsockServer)
		return FALSE;


	if (!SendSaveThrowItem2(lpItem))
		return FALSE;

	TransThrowItem.code = OpCode::OPCODE_THROWITEM;
	TransThrowItem.size = sizeof(TRANS_ITEMINFO);
	TransThrowItem.x = x;
	TransThrowItem.y = y;
	TransThrowItem.z = z;

	memcpy(&TransThrowItem.Item, lpItem, sizeof(sITEMINFO));




	return TRUE;
}






int	ThrowPotionCount = 0;


int ThrowItemToServer(smTRANS_COMMAND_EX *lpTransCommand)
{
	smTRANS_COMMAND	smTransCommand;
	smWINSOCK	*lpsmSock;
	DWORD	dwItemCodeMask;
	int		cnt;

	if (TransThrowItem.code &&
		TransThrowItem.Item.CODE == (DWORD)lpTransCommand->WParam &&
		TransThrowItem.Item.ItemHeader.Head == (DWORD)lpTransCommand->LParam &&
		TransThrowItem.Item.ItemHeader.dwChkSum == (DWORD)lpTransCommand->SParam)
	{

		if ((TransThrowItem.Item.CODE&sinITEM_MASK1) != (sinPM1&sinITEM_MASK1))
		{
			cInvenTory.DeleteInvenItemToServer(TransThrowItem.Item.CODE, TransThrowItem.Item.ItemHeader.Head, TransThrowItem.Item.ItemHeader.dwChkSum);


			if (FindInvenItem(TransThrowItem.Item.CODE,
				TransThrowItem.Item.ItemHeader.Head,
				TransThrowItem.Item.ItemHeader.dwChkSum) != 0)
			{

				SendInvenItemError(0, TransThrowItem.Item.CODE,
					TransThrowItem.Item.ItemHeader.Head,
					TransThrowItem.Item.ItemHeader.dwChkSum);

				TransThrowItem.code = 0;
				return TRUE;
			}
		}
		else
		{
			if ((dwPlayTime - dwLastRecordTime) > 4000 && TransThrowItem.Item.PotionCount >= 10)
			{

				SaveGameData();
				ThrowPotionCount = 0;
			}
			else
			{
				ThrowPotionCount += TransThrowItem.Item.PotionCount;
				if (ThrowPotionCount >= 15)
				{
					ThrowPotionCount = 0;
					SaveGameData();
				}
			}
		}

		if ((TransThrowItem.Item.CODE&sinITEM_MASK2) == sinBC1)
		{

			if (TransThrowItem.Item.PotionCount == 100)
				TransThrowItem.Item.PotionCount = 200;

			if (TransThrowItem.Item.CODE == (sinBC1 | sin04) && TransThrowItem.Item.PotionCount == 200)
			{

				smTransCommand.size = sizeof(smTRANS_COMMAND);
				smTransCommand.code = OpCode::OPCODE_PARTY_POTION;
				smTransCommand.WParam = 3000;
				smTransCommand.LParam = 3000;
				smTransCommand.SParam = 3000;
				smTransCommand.EParam = lpCurPlayer->dwObjectSerial;

				if (smWsockUserServer)
					smWsockUserServer->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

				SetPartyPosion(&smTransCommand);

				TransThrowItem.code = 0;
				return TRUE;
			}
		}

		if (!TransThrowItem.Item.SpecialItemFlag[0])
		{
			TransThrowItem.dwSeCode[0] = lpTransCommand->WxParam;
			TransThrowItem.dwSeCode[1] = lpTransCommand->LxParam;
			TransThrowItem.dwSeCode[2] = lpTransCommand->SxParam;
			TransThrowItem.dwSeCode[3] = lpTransCommand->ExParam;

			dwItemCodeMask = TransThrowItem.Item.CODE&sinITEM_MASK2;


			if (((dwItemCodeMask == sinGP1 || dwItemCodeMask == sinCH1 || dwItemCodeMask == sinFO1 || dwItemCodeMask == sinGP2) && TransThrowItem.Item.PotionCount == 100) ||
				(TransThrowItem.Item.CODE == (sinGG1 | sin01) && TransThrowItem.Item.ItemKindCode == OpCode::OPCODE_COLLECTMONEY) ||
				(dwItemCodeMask == sinBC1 && TransThrowItem.Item.PotionCount == 200) ||
				(dwItemCodeMask == sinBI1 && TransThrowItem.Item.PotionCount == 300) ||
				(dwItemCodeMask == sinBI2 && TransThrowItem.Item.PotionCount == 300))
			{
				lpsmSock = GetAreaServerSock();
				if (lpsmSock)
					lpsmSock->Send((char *)&TransThrowItem, TransThrowItem.size, TRUE);
				else
					smWsockServer->Send((char *)&TransThrowItem, TransThrowItem.size, TRUE);

				if (dwItemCodeMask == sinFO1)
				{

					cnt = (TransThrowItem.Item.CODE&sinITEM_MASK3) >> 8;
					cnt--;
					if (cnt >= 0 && cnt < 15)
					{
						lpCurPlayer->dwForceOrbCode = TransThrowItem.Item.CODE;
						lpCurPlayer->dwForceOrbTime = dwPlayTime + ForceOrbUseTime[cnt] * 1000;
						AssaParticle_ShelltomWeapon(lpCurPlayer, ForceOrbUseTime[cnt] * 70, cnt);


						SendCommandUser(smCOMMNAD_USER_FORCEORB, 0, 0, 0);
						StartSkill(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, SKILL_UP1);
						SkillPlaySound(SKILL_SOUND_LEARN, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
					}

					else if (cnt >= 20 && cnt < 34)
					{
						lpCurPlayer->dwForceOrbCode = TransThrowItem.Item.CODE;
						lpCurPlayer->dwForceOrbTime = dwPlayTime + MagicForceOrbUseTime[cnt - 20] * 1000;

						AssaParticle_ShelltomWeapon(lpCurPlayer, MagicForceOrbUseTime[cnt - 20] * 70, cnt);


						SendCommandUser(smCOMMNAD_USER_FORCEORB, 0, 0, 0);
						StartSkill(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, SKILL_UP1);
						SkillPlaySound(SKILL_SOUND_LEARN, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
					}
					else if (cnt >= 34 && cnt < 37)
					{
						lpCurPlayer->dwForceOrbCode = TransThrowItem.Item.CODE;
						lpCurPlayer->dwForceOrbTime = dwPlayTime + BillingMagicForceOrbUseTime[cnt - 34] * 1000;

						AssaParticle_ShelltomWeapon(lpCurPlayer, BillingMagicForceOrbUseTime[cnt - 34] * 70, cnt);


						SendCommandUser(smCOMMNAD_USER_FORCEORB, 0, 0, 0);
						StartSkill(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, SKILL_UP1);
						SkillPlaySound(SKILL_SOUND_LEARN, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
					}
				}


				if (dwItemCodeMask == sinBI1 || dwItemCodeMask == sinBI2)
				{
					//Olho Mágico (3h)
					if (TransThrowItem.Item.CODE == (sinBI1 | sin12))
					{
						chaPremiumitem.SetThirdEyesTime(PRIME_ITEM_TIME_3H);
					}
					//Poçao EXP (3h)
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin13))
					{
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_3H);
					}
					//Olho Mágico (7d)
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin14))
					{
						chaPremiumitem.SetThirdEyesTime(60 * 60 * 24 * 1);
					}
					//Poçao EXP (7d)
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin15))
					{
						chaPremiumitem.SetExpUpPotionTime(60*60*24*1);
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin23))
					{
						cnt = (rand() % 8192) * 2;
						DWORD	dwTable = GetTableNum(cnt);
						AddTimeEffect(SKILL_EFFECT_FIREFLOWER, dwPlayTime, (dwTable >> 24) & 0xFF, 0, 0, lpCurPlayer);
						AddTimeEffect(SKILL_EFFECT_FIREFLOWER, dwPlayTime + 500, (dwTable >> 16) & 0xFF, 0, 0, lpCurPlayer);
						AddTimeEffect(SKILL_EFFECT_FIREFLOWER, dwPlayTime + 1000, (dwTable >> 8) & 0xFF, 0, 0, lpCurPlayer);
						AddTimeEffect(SKILL_EFFECT_FIREFLOWER, dwPlayTime + 1500, dwTable & 0xFF, 0, 0, lpCurPlayer);
						lpCurPlayer->dwNextMotionCode = CHRMOTION_STATE_YAHOO;
						SendCommandUser(smCOMMNAD_USER_FIREFLOWER, cnt, 0, 0);
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin24))
					{
						chaPremiumitem.SetExpUpPotionTime(60*60*24*3);
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin25))
					{
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_EXPUPx7);
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin26))
					{
						chaPremiumitem.SetMightOfAwellTime(60 * 60 * 24 * 1);
						chaPremiumitem.SetMightOfAwellWeight(1500);
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin27))
					{
						chaPremiumitem.SetMightOfAwellTime(60 * 60 * 3);
						chaPremiumitem.SetMightOfAwellWeight(1500);
					}
					//Poção Redutora de Mana (3h)
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin28))
					{
						chaPremiumitem.SetManaReducePotionTime(PRIME_ITEM_TIME_3H);
						chaPremiumitem.SetManaReducePotionValue(30);
					}
					//Poção Redutora de Mana (7d)
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin29))
					{
						chaPremiumitem.SetManaReducePotionTime(60 * 60 * 24 * 1);
						chaPremiumitem.SetManaReducePotionValue(30);
					}


					else if (TransThrowItem.Item.CODE == (sinBI2 | sin93))
					{
						chaPremiumitem.SetManaReducePotionTime(60*60*24*2);
						chaPremiumitem.SetManaReducePotionValue(30);
					}

					

					else if (TransThrowItem.Item.CODE == (sinBI1 | sin30))
					{
						chaPremiumitem.SetMightOfAwellTime(60*60*24*2);
						chaPremiumitem.SetMightOfAwellWeight(1500);
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin31))
					{
						chaPremiumitem.SetMightOfAwellTime(60*60*24*3);
						chaPremiumitem.SetMightOfAwellWeight(1500);
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin32))
					{
						chaPremiumitem.SetPhenixPetTime(60 * 60 * 24 * 2);
						cPCBANGPet.PetKind = TRUE;
						cPCBANGPet.ShowPet();
					}
					//Fênix (7d)
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin33))
					{
						chaPremiumitem.SetPhenixPetTime(60 * 60 * 24 * 3);
						cPCBANGPet.PetKind = TRUE;
						cPCBANGPet.ShowPet();
					}
					//Fênix (3h)
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin34))
					{
						chaPremiumitem.SetPhenixPetTime(PRIME_ITEM_TIME_3H);
						cPCBANGPet.PetKind = TRUE;
						cPCBANGPet.ShowPet();
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin43))
					{
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_EXPUP);
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin44))
					{
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_EXPUPx7);
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin50))
					{
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE4);
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin51))
					{
						chaPremiumitem.SetPhenixPetTime(PRIME_ITEM_TIME_PACKAGE4);
						cPCBANGPet.PetKind = TRUE;
						cPCBANGPet.ShowPet();
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin52))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_24H);


						cHelpPet.PetKind = HoLowLevelPet::Type::Terry + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin53))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_24H);

						cHelpPet.PetKind = HoLowLevelPet::Type::Nepsys + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin54))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_24H);

						cHelpPet.PetKind = HoLowLevelPet::Type::Io + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin55))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_24H);

						cHelpPet.PetKind = HoLowLevelPet::Type::Mute + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}


					else if (TransThrowItem.Item.CODE == (sinBI1 | sin69))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_PACKAGE2);


						cHelpPet.PetKind = HoLowLevelPet::Type::Terry + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin70))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_PACKAGE2);

						cHelpPet.PetKind = HoLowLevelPet::Type::Nepsys + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin71))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_PACKAGE2);

						cHelpPet.PetKind = HoLowLevelPet::Type::Io + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin72))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_PACKAGE2);

						cHelpPet.PetKind = HoLowLevelPet::Type::Mute + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}


					else if (TransThrowItem.Item.CODE == (sinBI1 | sin80))
					{
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE5);
					}


					else if (TransThrowItem.Item.CODE == (sinBI1 | sin77))
					{
						chaPremiumitem.SetPhenixPetTime(PRIME_ITEM_TIME_PACKAGE5);
						cPCBANGPet.PetKind = TRUE;
						cPCBANGPet.ShowPet();
					}

					else if (TransThrowItem.Item.CODE == (sinBI1 | sin65))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_PACKAGE3);


						cHelpPet.PetKind = HoLowLevelPet::Type::Terry + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin66))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_PACKAGE3);

						cHelpPet.PetKind = HoLowLevelPet::Type::Nepsys + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin67))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_PACKAGE3);

						cHelpPet.PetKind = HoLowLevelPet::Type::Io + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin68))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_PACKAGE3);

						cHelpPet.PetKind = HoLowLevelPet::Type::Mute + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}

					else if (TransThrowItem.Item.CODE == (sinBI1 | sin73))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_PACKAGE5);


						cHelpPet.PetKind = HoLowLevelPet::Type::Terry + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin74))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_PACKAGE5);

						cHelpPet.PetKind = HoLowLevelPet::Type::Nepsys + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin75))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_PACKAGE5);

						cHelpPet.PetKind = HoLowLevelPet::Type::Io + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin76))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_PACKAGE5);

						cHelpPet.PetKind = HoLowLevelPet::Type::Mute + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}


					else if (TransThrowItem.Item.CODE == (sinBI1 | sin78))
					{
						chaPremiumitem.SetThirdEyesTime(PRIME_ITEM_TIME_PACKAGE5);
					}


					else if (TransThrowItem.Item.CODE == (sinBI1 | sin79))
					{
						chaPremiumitem.SetExpUpPotionTime(60*60*24*2);
					}


					else if (TransThrowItem.Item.CODE == (sinBI1 | sin83))
					{
						chaPremiumitem.SetManaReducePotionTime(60*60*24*2);
						chaPremiumitem.SetManaReducePotionValue(30);
					}
					//Redutora STM (3h)
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin91))
					{
						chaPremiumitem.SetStaminaReducePotionTime(PRIME_ITEM_TIME_3H);
						chaPremiumitem.SetStaminaReducePotionValue(30);
					}
					//Redutora STM (7d)
					else if (TransThrowItem.Item.CODE == (	sinBI1 | sin92))
					{
						chaPremiumitem.SetStaminaReducePotionTime(60 * 60 * 24 * 1);
						chaPremiumitem.SetStaminaReducePotionValue(30);
					}
					else if (TransThrowItem.Item.CODE == (sinBI2 | sin94))
					{
					chaPremiumitem.SetStaminaReducePotionTime(60*60*24*2);
					chaPremiumitem.SetStaminaReducePotionValue(30);
					}
					else if (TransThrowItem.Item.CODE == (sinBI2 | sin95))
					{
					chaPremiumitem.SetStaminaReducePotionTime(60 * 60 * 24 * 3);
					chaPremiumitem.SetStaminaReducePotionValue(30);
					}
					else if (TransThrowItem.Item.CODE == (sinBI2 | sin96))
					{
					chaPremiumitem.SetManaRechargingPTime(60 * 60 * 24 * 2);
					}
					else if (TransThrowItem.Item.CODE == (sinBI2 | sin97))
					{
					chaPremiumitem.SetManaRechargingPTime(60 * 60 * 24 * 3);
					}

					if (TransThrowItem.Item.CODE == ((sinBI2 | sin01)))
					{
						int test = 1;
					}

					switch (TransThrowItem.Item.CODE)
					{
					case (sinBI2 | sin01):
					case (sinBI2 | sin05):
					case (sinBI2 | sin09):
					case (sinBI2 | sin23):
						chaPremiumitem.SetThirdEyesTime(PRIME_ITEM_TIME_PACKAGE1);
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE1);
						break;
					case (sinBI2 | sin02):
					case (sinBI2 | sin06):
					case (sinBI2 | sin10):
					case (sinBI2 | sin24):
						chaPremiumitem.SetThirdEyesTime(PRIME_ITEM_TIME_PACKAGE2);
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE2);
						break;
					case (sinBI2 | sin03):
					case (sinBI2 | sin07):
					case (sinBI2 | sin11):
					case (sinBI2 | sin25):
						chaPremiumitem.SetThirdEyesTime(PRIME_ITEM_TIME_PACKAGE3);
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE3);
						break;
					case (sinBI2 | sin04):
					case (sinBI2 | sin08):
					case (sinBI2 | sin12):
						chaPremiumitem.SetThirdEyesTime(PRIME_ITEM_TIME_PACKAGE4);
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE4);
						break;
					case (sinBI2 | sin26):
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE1);
						chaPremiumitem.SetManaReducePotionTime(PRIME_ITEM_TIME_PACKAGE1);
						chaPremiumitem.SetManaReducePotionValue(10);
						break;
					case (sinBI2 | sin27):
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE2);
						chaPremiumitem.SetManaReducePotionTime(PRIME_ITEM_TIME_PACKAGE2);
						chaPremiumitem.SetManaReducePotionValue(10);
						break;
					case (sinBI2 | sin28):
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE3);
						chaPremiumitem.SetManaReducePotionTime(PRIME_ITEM_TIME_PACKAGE3);
						chaPremiumitem.SetManaReducePotionValue(10);
						break;
					case (sinBI2 | sin29):
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE1);
						chaPremiumitem.SetManaReducePotionTime(PRIME_ITEM_TIME_PACKAGE1);
						chaPremiumitem.SetManaReducePotionValue(20);
						break;
					case (sinBI2 | sin30):
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE2);
						chaPremiumitem.SetManaReducePotionTime(PRIME_ITEM_TIME_PACKAGE2);
						chaPremiumitem.SetManaReducePotionValue(20);
						break;
					case (sinBI2 | sin31):
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE3);
						chaPremiumitem.SetManaReducePotionTime(PRIME_ITEM_TIME_PACKAGE3);
						chaPremiumitem.SetManaReducePotionValue(20);
						break;
					case (sinBI2 | sin32):
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE1);
						chaPremiumitem.SetManaReducePotionTime(PRIME_ITEM_TIME_PACKAGE1);
						chaPremiumitem.SetManaReducePotionValue(30);
						break;
					case (sinBI2 | sin33):
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE2);
						chaPremiumitem.SetManaReducePotionTime(PRIME_ITEM_TIME_PACKAGE2);
						chaPremiumitem.SetManaReducePotionValue(30);
						break;
					case (sinBI2 | sin34):
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE3);
						chaPremiumitem.SetManaReducePotionTime(PRIME_ITEM_TIME_PACKAGE3);
						chaPremiumitem.SetManaReducePotionValue(30);
						break;
					case (sinBI2 | sin35):
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE1);
						chaPremiumitem.SetManaReducePotionTime(PRIME_ITEM_TIME_PACKAGE1);
						chaPremiumitem.SetManaReducePotionValue(40);
						break;
					case (sinBI2 | sin36):
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE2);
						chaPremiumitem.SetManaReducePotionTime(PRIME_ITEM_TIME_PACKAGE2);
						chaPremiumitem.SetManaReducePotionValue(40);
						break;
					case (sinBI2 | sin37):
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE3);
						chaPremiumitem.SetManaReducePotionTime(PRIME_ITEM_TIME_PACKAGE3);
						chaPremiumitem.SetManaReducePotionValue(40);
						break;
					}
				}

			}
			else
			{
				smWsockServer->Send((char *)&TransThrowItem, TransThrowItem.size, TRUE);
			}
		}

	}

	TransThrowItem.code = 0;
	return TRUE;
}



int SendAddStartPoint(int x, int z)
{
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = OpCode::OPCODE_ADD_STARTPOSI;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.LParam = x;
	TransCommand.WParam = z;
	TransCommand.SParam = TRUE;

	smWINSOCK *lpsmSock;
	lpsmSock = GetAreaServerSock();
	if (lpsmSock)
	{
		return lpsmSock->Send((char *)&TransCommand, TransCommand.size, TRUE);
	}
	return NULL;
}


int SendDeleteStartPoint(int x, int z)
{
	smTRANS_COMMAND TransCommand;

	TransCommand.code = OpCode::OPCODE_DEL_STARTPOSI;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.LParam = x;
	TransCommand.WParam = z;
	TransCommand.SParam = TRUE;

	scITEM *lpItem = FindScItem(x, z);

	if (lpItem)
	{
		smWINSOCK *lpsmSock = GetServerSock(lpItem->ServerCode);
		lpItem->Close();

		if (lpsmSock)
			return lpsmSock->Send((char *)&TransCommand, TransCommand.size, TRUE);
	}

	return NULL;
}





int SendAdd_Npc(smCHAR *lpCharSample, int state)
{
	smTRNAS_PLAYERINFO	smTransPlayerInfo;

	smTransPlayerInfo.code = OpCode::OPCODE_ADD_NPC;
	smTransPlayerInfo.size = sizeof(smTRNAS_PLAYERINFO);
	memcpy(&smTransPlayerInfo.smCharInfo, &lpCharSample->smCharInfo, sizeof(smCHAR_INFO));
	smTransPlayerInfo.smCharInfo.State = 0;


	strcpy_s(smTransPlayerInfo.smCharInfo.szModelName2, NpcSelectedName);

	smTransPlayerInfo.smCharInfo.Life[0] = 100;
	smTransPlayerInfo.smCharInfo.Mana[0] = 100;
	smTransPlayerInfo.smCharInfo.Life[1] = 100;

	smTransPlayerInfo.x = lpCharSample->pX;
	smTransPlayerInfo.y = lpCharSample->pY;
	smTransPlayerInfo.z = lpCharSample->pZ;

	smTransPlayerInfo.ax = lpCharSample->Angle.x;
	smTransPlayerInfo.ay = lpCharSample->Angle.y;
	smTransPlayerInfo.az = lpCharSample->Angle.z;

	smTransPlayerInfo.state = state;

	smWINSOCK *lpsmSock;
	lpsmSock = GetAreaServerSock();
	if (lpsmSock)
	{
		return lpsmSock->Send((char *)&smTransPlayerInfo, smTransPlayerInfo.size, TRUE);
	}

	return NULL;
}


int SendDelete_Npc(smCHAR *lpCharSample)
{
	smTRNAS_PLAYERINFO	smTransPlayerInfo;
	smWINSOCK *lpsmSock;

	smTransPlayerInfo.code = OpCode::OPCODE_DEL_NPC;
	smTransPlayerInfo.size = sizeof(smTRNAS_PLAYERINFO);
	memcpy(&smTransPlayerInfo.smCharInfo, &lpCharSample->smCharInfo, sizeof(smCHAR_INFO));

	smTransPlayerInfo.x = lpCharSample->pX;
	smTransPlayerInfo.y = lpCharSample->pY;
	smTransPlayerInfo.z = lpCharSample->pZ;

	smTransPlayerInfo.ax = lpCharSample->Angle.x;
	smTransPlayerInfo.ay = lpCharSample->Angle.y;
	smTransPlayerInfo.az = lpCharSample->Angle.z;

	smTransPlayerInfo.dwObjectSerial = lpCharSample->dwObjectSerial;

	lpsmSock = GetServerSock(lpCharSample->ServerCode);
	lpCharSample->Close();

	if (lpsmSock)
	{
		return lpsmSock->Send((char *)&smTransPlayerInfo, smTransPlayerInfo.size, TRUE);
	}
	return NULL;
}


int SendGetRecordData(char *szName)
{
	smTRANS_CHAR_COMMAND smTransCharCommand;

	if (smWsockDataServer)
	{
		smTransCharCommand.code = OpCode::OPCODE_GETRECORDDATA;
		smTransCharCommand.size = sizeof(smTRANS_CHAR_COMMAND);

		smTransCharCommand.WParam = dwExeCheckSum;
		smTransCharCommand.LParam = FALSE;
		smTransCharCommand.SParam = Client_Version;

		strcpy_s(smTransCharCommand.szName, szName);

		dwLoadingTime = GetCurrentTime();

		return smWsockDataServer->Send((char *)&smTransCharCommand, smTransCharCommand.size, TRUE);
	}

	return FALSE;
}

char *szCmdOpenMonster[10] = {
	"È©°íºí¸°",
	"È©°íºí¸°",
	"È©°íºí¸°",
	"Å·È£ÇÇ",
	"Å¸ÀÌÅº",
	0,0,0,0,0
};



int SendOpenMonster(int State)
{
	smTRANS_CHAR_COMMAND smTransCharCommand;
	char *szMonName = "";

	smTransCharCommand.code = OpCode::OPCODE_OPENMONSTER;
	smTransCharCommand.size = sizeof(smTRANS_CHAR_COMMAND);
	smTransCharCommand.WParam = State;
	smTransCharCommand.LParam = 0;
	smTransCharCommand.SParam = 0;

	if (State >= 0)
	{
		szMonName = smConfig.szCmdOpenMonster[State];
		if (!szMonName[0]) szMonName = szCmdOpenMonster[State];
	}

	if (State >= 0 && szMonName)
		strcpy_s(smTransCharCommand.szName, szMonName);
	else
		smTransCharCommand.szName[0];


	smWINSOCK *lpsmSock;
	lpsmSock = GetAreaServerSock();
	if (lpsmSock)
	{
		return lpsmSock->Send((char *)&smTransCharCommand, smTransCharCommand.size, TRUE);
	}

	return FALSE;

}


int	CodeXorCharInfo()
{
	lpCurPlayer->smCharInfo.Exp ^= CodeXorExp;
	lpCurPlayer->smCharInfo.Exp_High ^= CodeXorExp_High;
	lpCurPlayer->smCharInfo.Life[0] ^= CodeXorLife;
	return TRUE;
}


int SaveCheckSkill()
{

	ReformSkillInfo();

	for (int j = 1; j < SIN_MAX_USE_SKILL; j++)
	{
		if (sinSkill.UseSkill[j].Flag && sinSkill.UseSkill[j].Point)
		{
			if (cSkill.CheckSkillPointForm(&sinSkill.UseSkill[j]) == FALSE)
				return FALSE;
			if (cSkill.CheckSkillMasteryForm(&sinSkill.UseSkill[j]) == FALSE)
				return FALSE;
		}
	}

	return TRUE;
}


int ReformSkillInfo()
{
	for (int j = 1; j < SIN_MAX_USE_SKILL; j++)
	{
		cSkill.ReformSkillMasteryForm(&sinSkill.UseSkill[j]);
		cSkill.ReformSkillPointForm(&sinSkill.UseSkill[j]);
	}
	return TRUE;
}


int	SaveGameData()
{
	if (smWsockDataServer && !rsRecorder.dwRecordTime &&
		lpCurPlayer->smCharInfo.JOB_CODE && !AdminCharDisable && !cTrade.OpenFlag && !cWareHouse.OpenFlag && !QuitSave)
	{



		if (!WarningHack && CheckCharForm() != FALSE && SaveCheckSkill() == TRUE)
		{
			CodeXorCharInfo();
			ReformCharForm();

			rsRecorder.MakeRecordData(&lpCurPlayer->smCharInfo, cInvenTory.InvenItem, cInvenTory.InvenItemTemp, &MouseItem);
			rsRecorder.SendRecordDataToServer(smWsockDataServer);
			rsRecorder.dwRecordTime = dwPlayTime;

			if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
			{
				AddChatBuff("Salvando o jogo");
			}

			CodeXorCharInfo();
			ReformCharForm();
			CheckPlaySkill();
			return TRUE;
		}
	}
	return FALSE;
}


int GetSaveResult()
{
	if (rsRecorder.dwRecordTime) return FALSE;

	return TRUE;
}



smTRANS_COMMAND	smMessageCommandBuff;


int	TransUserCommand(DWORD dwCode, char *szID, char *szName)
{
	smTRANS_CHAR_COMMAND2	TransCharCommand2;

	TransCharCommand2.code = dwCode;
	TransCharCommand2.size = sizeof(smTRANS_CHAR_COMMAND2);

	if (szID)
	{
		strcpy_s(TransCharCommand2.szId, szID);
	}

	if (szName)
	{
		strcpy_s(TransCharCommand2.szName, szName);
	}

	return smWsockDataServer->Send((char *)&TransCharCommand2, TransCharCommand2.size, TRUE);
}




int	Send_GetCharInfo(DWORD dwObjectSerial, int ServerCode)
{
	smTRANS_COMMAND	TransCommand;
	smWINSOCK *lpsmSock;

	TransCommand.code = OpCode::OPCODE_GETPLAYERINFO;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = dwObjectSerial;

	lpsmSock = GetServerSock(ServerCode);

	if (lpsmSock)
	{
		return lpsmSock->Send((char *)&TransCommand, TransCommand.size, TRUE);
	}
	return FALSE;
}

#define DEADLOCK_CHECK_LIMIT_TIME		(30*1000)
#define DEADLOCK_CHECK_LIMIT_TIME2		(60*1000)
#define RECONNECT_LIMIT_TIME			(7*1000)


static DWORD dwCheckNetCount = 0;
static DWORD dwLastTransCheckTime = 0;
static int	ReconnectCount = 0;


int	TransCheckNetwork()
{
	smTRANS_COMMAND			TransCommand;
	DWORD	dwTime, dwTime2;
	smWINSOCK	*lpOldSock;



	if (!dwConnectedServerTime)
		return FALSE;



	OpenTimeCheckThread();


	dwTime = GetCurrentTime();
	dwTime2 = dwTime;

	if ((dwTime - dwLastTransCheckTime) < 4000)
		return FALSE;

	dwLastTransCheckTime = dwTime;


	if ((dwMainServ_RecvTime && (dwMainServ_RecvTime + RECONNECT_LIMIT_TIME) < dwTime) ||
		(dwLastRecvGameServerTime + DEADLOCK_CHECK_LIMIT_TIME) < dwTime ||
		!smWsockServer || smWsockServer->WaitReadMessage < 0)
	{


		dwLastRecvGameServerTime = dwTime;

		lpOldSock = smWsockServer;

		if (lpOldSock == smWsockDataServer)
			smWsockDataServer = 0;
		if (lpOldSock == smWsockUserServer)
			smWsockUserServer = 0;
		if (lpOldSock == smWsockExtendServer)
			smWsockExtendServer = 0;

		smWsockServer = 0;
		ConnectServer_Main();

		if (smWsockServer)
		{


			SendContinueServer(lpCurPlayer->dwObjectSerial, smWsockServer);

			char szBuff[256];
			wsprintf(szBuff, "Reconnect Server(Main)");
			AddChatBuff(szBuff);

			if (dwLastRecvGameServerTime && dwLastRecvGameServerTime < dwTime2) dwLastRecvGameServerTime = dwTime2;
			if (dwLastRecvGameServerTime2 && dwLastRecvGameServerTime2 < dwTime2) dwLastRecvGameServerTime2 = dwTime2;
			if (dwLastRecvGameServerTime3 && dwLastRecvGameServerTime3 < dwTime2) dwLastRecvGameServerTime3 = dwTime2;
			if (dwLastRecvGameServerTime4 && dwLastRecvGameServerTime4 < dwTime2) dwLastRecvGameServerTime4 = dwTime2;
			ReconnServer++;

			return TRUE;
		}
		//LOG_GAME
		DisconnectServerCode = 1;
		Log::getInstance()->output(LOG_GAME, "SetDisconnectFlag: 20");
		DisconnectFlag = GetCurrentTime();
		return FALSE;
	}




	dwTime = (dwTime - dwConnectedClientTime) + dwConnectedServerTime;

	TransCommand.code = OpCode::OPCODE_CHECK_NETSTATE;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = dwTime;
	TransCommand.LParam = dwCheckNetCount;
	TransCommand.SParam = GetSafeCode2() + ((dwMemError^dwPlayTime) - 8080);
	TransCommand.EParam = dwMemFunChkCode;

	dwCheckNetCount++;

	if (smWsockServer) smWsockServer->Send((char *)&TransCommand, TransCommand.size, TRUE);

	if (smWsockDataServer && smWsockServer != smWsockDataServer)
	{
		if (dwLastRecvGameServerTime2 && (dwLastRecvGameServerTime2 + DEADLOCK_CHECK_LIMIT_TIME2) < dwTime2)
		{//LOG_GAME
			Log::getInstance()->output(LOG_GAME, "SetDisconnectFlag: 21");
			DisconnectFlag = GetCurrentTime();
			DisconnectServerCode = 2;
			return FALSE;
		}




		TransCommand.code = OpCode::OPCODE_CHECK_NETSTATE2;
		smWsockDataServer->Send((char *)&TransCommand, TransCommand.size, TRUE);
		if (!dwLastRecvGameServerTime2) dwLastRecvGameServerTime2 = dwTime2;
	}


	if (smWsockUserServer && smWsockServer != smWsockUserServer)
	{
		if ((dwLastRecvGameServerTime3 && (dwLastRecvGameServerTime3 + DEADLOCK_CHECK_LIMIT_TIME) < dwTime2) ||
			(dwUserServ_RecvTime && (dwUserServ_RecvTime + RECONNECT_LIMIT_TIME) < dwTime2) ||
			smWsockUserServer->WaitReadMessage < 0)
		{

			smWsockUserServer = 0;
			ConnectServer_Main();

			if (smWsockUserServer)
			{


				SendContinueServer(lpCurPlayer->dwObjectSerial, smWsockUserServer);

				char szBuff[256];
				wsprintf(szBuff, "Reconnect Server(User)");
				AddChatBuff(szBuff);
				if (dwLastRecvGameServerTime && dwLastRecvGameServerTime < dwTime2) dwLastRecvGameServerTime = dwTime2;
				if (dwLastRecvGameServerTime2 && dwLastRecvGameServerTime2 < dwTime2) dwLastRecvGameServerTime2 = dwTime2;
				if (dwLastRecvGameServerTime3 && dwLastRecvGameServerTime3 < dwTime2) dwLastRecvGameServerTime3 = dwTime2;
				if (dwLastRecvGameServerTime4 && dwLastRecvGameServerTime4 < dwTime2) dwLastRecvGameServerTime4 = dwTime2;

				ReconnDataServer++;

				return TRUE;
			}
			//LOG_GAME
			DisconnectServerCode = 3;
			Log::getInstance()->output(LOG_GAME, "SetDisconnectFlag: 22");
			DisconnectFlag = GetCurrentTime();
			return FALSE;
		}

		TransCommand.code = OpCode::OPCODE_CHECK_NETSTATE3;
		smWsockUserServer->Send((char *)&TransCommand, TransCommand.size, TRUE);
		if (!dwLastRecvGameServerTime3) dwLastRecvGameServerTime3 = dwTime2;

	}

	if (smWsockExtendServer && smWsockServer != smWsockExtendServer)
	{
		if ((dwLastRecvGameServerTime4 && (dwLastRecvGameServerTime4 + DEADLOCK_CHECK_LIMIT_TIME) < dwTime2) ||
			(dwExtendServ_RecvTime && (dwExtendServ_RecvTime + RECONNECT_LIMIT_TIME) < dwTime2) ||
			smWsockExtendServer->WaitReadMessage < 0)
		{

			smWsockExtendServer = 0;
			ConnectServer_Main();

			if (smWsockExtendServer)
			{
				SendContinueServer(lpCurPlayer->dwObjectSerial, smWsockExtendServer);

				char szBuff[256];
				wsprintf(szBuff, "Reconnect Server(Extend)");
				AddChatBuff(szBuff);
				if (dwLastRecvGameServerTime && dwLastRecvGameServerTime < dwTime2) dwLastRecvGameServerTime = dwTime2;
				if (dwLastRecvGameServerTime2 && dwLastRecvGameServerTime2 < dwTime2) dwLastRecvGameServerTime2 = dwTime2;
				if (dwLastRecvGameServerTime3 && dwLastRecvGameServerTime3 < dwTime2) dwLastRecvGameServerTime3 = dwTime2;
				if (dwLastRecvGameServerTime4 && dwLastRecvGameServerTime4 < dwTime2) dwLastRecvGameServerTime4 = dwTime2;



				return TRUE;
			}
			//LOG_GAME
			DisconnectServerCode = 3;
			Log::getInstance()->output(LOG_GAME, "SetDisconnectFlag: 23");
			DisconnectFlag = GetCurrentTime();
			return FALSE;
		}

		TransCommand.code = OpCode::OPCODE_CHECK_NETSTATE4;
		smWsockExtendServer->Send((char *)&TransCommand, TransCommand.size, TRUE);
		if (!dwLastRecvGameServerTime4) dwLastRecvGameServerTime4 = dwTime2;

	}
	if (AreaServerMode)
	{

		int cnt;
		for (cnt = 0; cnt < 2; cnt++)
		{
			if (lpWSockServer_Area[cnt])
			{
				if ((lpWSockServer_Area[cnt]->dwDeadLockTime + DEADLOCK_CHECK_LIMIT_TIME) < dwTime2 ||
					lpWSockServer_Area[cnt]->WaitReadMessage < 0)
				{

					lpOldSock = lpWSockServer_Area[cnt];
					lpWSockServer_Area[cnt] = smConnectSock(lpOldSock->szIPAddr, TCP_SERVPORT);

					if (lpWSockServer_Area[cnt])
					{
						SendContinueServer(lpCurPlayer->dwObjectSerial, lpWSockServer_Area[cnt]);

						char szBuff[256];
						wsprintf(szBuff, "Reconnect Server Area (%d)", cnt);
						AddChatBuff(szBuff);

					}
					else
					{
						lpOldSock->CloseSocket();
					}
				}

				if (lpWSockServer_Area[cnt])
				{
					TransCommand.code = OpCode::OPCODE_CHECK_NETSTATE5;
					TransCommand.EParam = (DWORD)lpWSockServer_Area[cnt];
					lpWSockServer_Area[cnt]->Send((char*)& TransCommand, TransCommand.size, TRUE);

				}
			}
		}
	}



	SendTotalExpMoney();

	CheckMaxDamage();


	return TRUE;
}


int SendAdminMode(AccountTypes type)
{
	Log::getInstance()->output(LOG_DEBUG, "SEND POWER USER TO SERVER");
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = OpCode::OPCODE_AUTH_ADMIN_MODE;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = (int)type;
	TransCommand.LParam = 0;
	TransCommand.SParam = 0;

	if (smWsockDataServer && smWsockServer != smWsockDataServer)
		smWsockDataServer->Send((char *)&TransCommand, TransCommand.size, TRUE);

	if (smWsockUserServer && smWsockServer != smWsockUserServer && smWsockDataServer != smWsockUserServer)
		smWsockUserServer->Send((char *)&TransCommand, TransCommand.size, TRUE);

	if (smWsockExtendServer && smWsockServer != smWsockExtendServer && smWsockDataServer != smWsockExtendServer)
		smWsockExtendServer->Send((char *)&TransCommand, TransCommand.size, TRUE);


	return smWsockServer->Send((char *)&TransCommand, TransCommand.size, TRUE);
}


int SendNetworkQuality(DWORD NetworkQuality)
{
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = OpCode::OPCODE_NETWORK_QUALITY;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = NetworkQuality;
	TransCommand.LParam = 0;
	TransCommand.SParam = 0;

	if (smWsockUserServer && smWsockServer != smWsockUserServer)
		smWsockUserServer->Send((char *)&TransCommand, TransCommand.size, TRUE);

	if (smWsockExtendServer && smWsockServer != smWsockExtendServer)
		smWsockExtendServer->Send((char *)&TransCommand, TransCommand.size, TRUE);

	return smWsockServer->Send((char *)&TransCommand, TransCommand.size, TRUE);
}


int SendCheckIP(int Code, smWINSOCK *lpsmSock)
{
	smTRANS_CHAR_COMMAND TransCharCommand;

	TransCharCommand.code = OpCode::OPCODE_CHECKIP;
	TransCharCommand.size = sizeof(smTRANS_CHAR_COMMAND);
	TransCharCommand.WParam = Code;
	TransCharCommand.LParam = 0;
	TransCharCommand.SParam = 0;

	strcpy_s(TransCharCommand.szName, lpsmSock->szIPAddr);

	return smWsockDataServer->Send((char *)&TransCharCommand, TransCharCommand.size, TRUE);
}


int SendSetObjectSerial(DWORD dwObjectSerial)
{

	smTRNAS_PLAYERINFO	TransPlayerInfo;

	memcpy(&TransPlayerInfo.smCharInfo, &lpCurPlayer->smCharInfo, sizeof(smCHAR_INFO));
	TransPlayerInfo.size = sizeof(smTRNAS_PLAYERINFO);
	TransPlayerInfo.code = OpCode::OPCODE_PLAYERINFO2;
	TransPlayerInfo.dwObjectSerial = lpCurPlayer->dwObjectSerial;

	TransPlayerInfo.x = lpCurPlayer->pX;
	TransPlayerInfo.y = lpCurPlayer->pY;
	TransPlayerInfo.z = lpCurPlayer->pZ;

	smWsockServer->Send((char *)&TransPlayerInfo, TransPlayerInfo.size, TRUE);

	if (smWsockServer != smWsockUserServer)
		smWsockUserServer->Send((char *)&TransPlayerInfo, TransPlayerInfo.size, TRUE);

	if (smWsockServer != smWsockExtendServer)
		smWsockExtendServer->Send((char *)&TransPlayerInfo, TransPlayerInfo.size, TRUE);

	if (AreaServerMode)
	{
		if (lpWSockServer_Area[0]) lpWSockServer_Area[0]->Send((char *)&TransPlayerInfo, TransPlayerInfo.size, TRUE);
		if (lpWSockServer_Area[1]) lpWSockServer_Area[1]->Send((char *)&TransPlayerInfo, TransPlayerInfo.size, TRUE);
	}

	return TRUE;
}


int SendSetObjectSerial_First(DWORD dwObjectSerial)
{

	smTRNAS_PLAYERINFO	TransPlayerInfo;

	memcpy(&TransPlayerInfo.smCharInfo, &lpCurPlayer->smCharInfo, sizeof(smCHAR_INFO));
	TransPlayerInfo.size = sizeof(smTRNAS_PLAYERINFO);
	TransPlayerInfo.code = OpCode::OPCODE_PLAYERINFO2;
	TransPlayerInfo.dwObjectSerial = lpCurPlayer->dwObjectSerial;

	TransPlayerInfo.x = lpCurPlayer->pX;
	TransPlayerInfo.y = lpCurPlayer->pY;
	TransPlayerInfo.z = lpCurPlayer->pZ;



	if (smWsockServer != smWsockUserServer)
		smWsockUserServer->Send((char *)&TransPlayerInfo, TransPlayerInfo.size, TRUE);

	if (smWsockServer != smWsockExtendServer)
		smWsockExtendServer->Send((char *)&TransPlayerInfo, TransPlayerInfo.size, TRUE);

	return TRUE;
}


int SendContinueServer(DWORD dwObjectSerial, smWINSOCK *lpsmSock)
{
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = OpCode::OPCODE_CONT_OBJSERIAL;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = dwObjectSerial;
	TransCommand.LParam = 0;
	TransCommand.SParam = 0;

	return lpsmSock->Send((char *)&TransCommand, TransCommand.size, TRUE);
}


int SendSetHackUser3(int Type, int LParam, int SParam)
{
	Log::getInstance()->output(LOG_DEBUG, "SendSetHackUser3: Type(%d)  LParam(%d)  SParam(%d)", Type, LParam, SParam);

	smTRANS_COMMAND	TransCommand;

	TransCommand.code = OpCode::OPCODE_SET_BLACKLIST2;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = Type;
	TransCommand.LParam = LParam;
	TransCommand.SParam = SParam;

	if (smWsockDataServer)
		smWsockDataServer->Send((char *)&TransCommand, TransCommand.size, TRUE);

	return TRUE;
}


int CheckCracker()
{
	char *szName;
	char TransBuff[1024];
	int len;

	szName = FindCracker();

	if (szName)
	{

		if (smWsockDataServer)
		{
			len = lstrlen(szName) + 9;
			strcpy_s(TransBuff + 8, sizeof(TransBuff) - 8, szName);
			((int *)TransBuff)[0] = len;
			((int *)TransBuff)[1] = OpCode::OPCODE_FINDCRACK;

			smWsockDataServer->Send(TransBuff, len, TRUE);
		}
		return TRUE;
	}
	return FALSE;
}


int CheckCracker(TRANS_FIND_CRACKER *lpTransFindCrack)
{
	char *szName;
	char TransBuff[1024];
	int len;
	char	*lpBuff;

	if (lpTransFindCrack)
		szName = FindCracker(lpTransFindCrack);
	else
		szName = FindCrackCont();

	if (szName)
	{

		if (smWsockDataServer)
		{
			len = lstrlen(szName) + 9;
			strcpy_s(TransBuff + 8, sizeof(TransBuff) - 8, szName);
			((int *)TransBuff)[0] = len;
			((int *)TransBuff)[1] = OpCode::OPCODE_FINDCRACK;

			smWsockDataServer->Send(TransBuff, len, TRUE);
		}
		return TRUE;
	}

	if (lpTransFindCrack)
	{
		if (lpTransFindCrack->size > (lpTransFindCrack->FindCounter*((int)sizeof(_CRACK_NAME)) + 16))
		{
			lpBuff = (char *)&lpTransFindCrack->CrackName[lpTransFindCrack->FindCounter];
			if (lpBuff[0])
			{

				GetNoticeUrl(lpBuff);
			}
		}
	}

	return FALSE;
}


int SendCrackWindow(HWND hWnd)
{
	Log::getInstance()->output(LOG_DEBUG, "SendCrackWindow");

	char *szName;
	char TransBuff[1024];
	int len;


	if (smWsockServer)
	{

		szName = TransBuff + 8;
		GetWindowText(hWnd, szName, 32);
		len = lstrlen(szName) + 9;
		((int *)TransBuff)[0] = len;
		((int *)TransBuff)[1] = OpCode::OPCODE_FINDCRACK2;

		smWsockServer->Send(TransBuff, len, TRUE);
	}
	return TRUE;
}


int SendSetHackUser(int StopGame)
{
	Log::getInstance()->output(LOG_DEBUG, "SendSetHackUser: StopGame(%d)", StopGame);

	smTRANS_COMMAND	TransCommand;

	TransCommand.code = OpCode::OPCODE_SET_BLACKLIST;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = StopGame;
	TransCommand.LParam = 0;
	TransCommand.SParam = 0;

	WarningHack = StopGame;

	if (smWsockDataServer)
		smWsockDataServer->Send((char *)&TransCommand, TransCommand.size, TRUE);

	if (WarningHack)
	{//LOG_GAME
		DisconnectServerCode = 4;
		Log::getInstance()->output(LOG_GAME, "SetDisconnectFlag: 25");
		DisconnectFlag = GetCurrentTime();
	}

	return TRUE;
}


int SendSetHackUser2(int Type, int LParam)
{
	Log::getInstance()->output(LOG_DEBUG, "SendSetHackUser2: Type(%d)  LParam(%d)", Type, LParam);

	smTRANS_COMMAND	TransCommand;

	TransCommand.code = OpCode::OPCODE_SET_BLACKLIST;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = Type;
	TransCommand.LParam = LParam;
	TransCommand.SParam = 0;

	if (smWsockDataServer)
		smWsockDataServer->Send((char *)&TransCommand, TransCommand.size, TRUE);

	return TRUE;
}


int SendCopyItemUser(int CopyItemCount)
{
	

	smTRANS_COMMAND	TransCommand;

	TransCommand.code = OpCode::OPCODE_SET_ITEMCOPYLIST;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = CopyItemCount;
	TransCommand.LParam = 0;
	TransCommand.SParam = 0;

	if (smWsockDataServer)
		smWsockDataServer->Send((char *)&TransCommand, TransCommand.size, TRUE);

	return TRUE;
}


int SendSaveThrowItem(sITEMINFO *lpItemInfo)
{
	smTRANS_COMMAND	TransCommand;


	if ((lpItemInfo->CODE&sinITEM_MASK1) != (sinPM1&sinITEM_MASK1))	return FALSE;


	TransCommand.code = OpCode::OPCODE_SAVETHROWITEM;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = lpItemInfo->CODE;
	TransCommand.LParam = lpItemInfo->ItemHeader.Head;
	TransCommand.SParam = lpItemInfo->ItemHeader.dwChkSum;

	if ((lpItemInfo->CODE&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
		ComparePotion();

	if (smWsockDataServer)
		smWsockDataServer->Send((char *)&TransCommand, TransCommand.size, TRUE);

	return TRUE;
}



int	SendRecordTradeItems(sTRADE *lpTrade)
{

	TRANS_RECORD_TRADE_ITEMS	TransRecordTradeItems;
	int cnt;

	ZeroMemory(&TransRecordTradeItems, sizeof(TRANS_RECORD_TRADE_ITEMS));

	TransRecordTradeItems.code = OpCode::OPCODE_RECORD_TRADE;
	TransRecordTradeItems.Money = lpTrade->Money - 193;
	strcpy_s(TransRecordTradeItems.szTradeUserName, cTrade.szTradeCharName);

	for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
	{
		if (lpTrade->TradeItem[cnt].Flag && TransRecordTradeItems.ThrowItemCount < TRADE_RECV_ITEMS_MAX)
		{
			TransRecordTradeItems.Items[TransRecordTradeItems.ThrowItemCount].dwCode = lpTrade->TradeItem[cnt].sItemInfo.CODE;
			TransRecordTradeItems.Items[TransRecordTradeItems.ThrowItemCount].dwHead = lpTrade->TradeItem[cnt].sItemInfo.ItemHeader.Head;
			TransRecordTradeItems.Items[TransRecordTradeItems.ThrowItemCount].dwChkSum = lpTrade->TradeItem[cnt].sItemInfo.ItemHeader.dwChkSum;
			TransRecordTradeItems.ThrowItemCount++;
		}
	}


	TransRecordTradeItems.size = TRANS_RECORD_TRADE_DEFSIZE + TransRecordTradeItems.ThrowItemCount * sizeof(_TRANS_RECORD_TRADE_ITEM);

	return smWsockDataServer->Send((char *)&TransRecordTradeItems, TransRecordTradeItems.size, TRUE);
}


int SendSaveThrowItem2(sITEMINFO *lpItemInfo)
{
	smTRANS_COMMAND_EX	TransCommand;


	TransCommand.code = OpCode::OPCODE_SAVETHROWITEM2;
	TransCommand.size = sizeof(smTRANS_COMMAND_EX);
	TransCommand.WParam = lpItemInfo->CODE;
	TransCommand.LParam = lpItemInfo->ItemHeader.Head;
	TransCommand.SParam = lpItemInfo->ItemHeader.dwChkSum;
	TransCommand.EParam = lpItemInfo->PotionCount^TransCommand.SParam^TransCommand.code;

	TransCommand.WxParam = lpCurPlayer->smCharInfo.Money;
	TransCommand.LxParam = EncodeParam(TransCommand.WxParam);
	TransCommand.SxParam = GetTotalMoney() ^ TransCommand.LxParam;
	TransCommand.ExParam = lpItemInfo->Money;

	if ((lpItemInfo->CODE&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
		ComparePotion();


	AddInvenMoney(-lpItemInfo->Money);

	return smWsockDataServer->Send((char *)&TransCommand, TransCommand.size, TRUE);
}


int SendSaveMoney()
{
	smTRANS_COMMAND	TransCommand;

	if (cWareHouse.OpenFlag && CompWareHouseMoney) return FALSE;

	TransCommand.code = OpCode::OPCODE_SAVETHROWMONEY;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = lpCurPlayer->smCharInfo.Money;
	TransCommand.LParam = EncodeParam(TransCommand.WParam);
	TransCommand.SParam = GetTotalMoney() ^ TransCommand.LParam;

	return smWsockDataServer->Send((char *)&TransCommand, TransCommand.size, TRUE);
}


int SendCopyOtherUser(char *szName, int Mode)
{
	smTRANS_CHAR_COMMAND	TransCharCommand;
	int cnt, len;

	TransCharCommand.code = OpCode::OPCODE_GETRECORDDATA;
	TransCharCommand.size = sizeof(smTRANS_CHAR_COMMAND);
	TransCharCommand.WParam = dwExeCheckSum;
	TransCharCommand.LParam = Mode;
	TransCharCommand.SParam = 0;


	if (Mode == 2)
	{
		len = lstrlen(szName);
		for (cnt = 0; cnt < len; cnt++)
		{
			if (szName[cnt] == ' ')
			{
				TransCharCommand.LParam = atoi(&szName[cnt]);
				szName[cnt] = 0;
				if (TransCharCommand.LParam < 1000) TransCharCommand.LParam = Mode;
				break;
			}
		}
	}

	strcpy_s(TransCharCommand.szName, szName);

	AdminCharDisable = TRUE;

	if (smWsockDataServer)
		return smWsockDataServer->Send((char *)&TransCharCommand, TransCharCommand.size, TRUE);

	return NULL;
}


int SendPlayUpdateInfo()
{
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = OpCode::OPCODE_UPDATE_CINFO;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = 0;
	TransCommand.LParam = lpCurPlayer->smCharInfo.Level;
	TransCommand.SParam = 0;
	TransCommand.EParam = 0;

	return smWsockServer->Send((char *)&TransCommand, TransCommand.size, TRUE);
}


int SendUpdateClanInfo()
{
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = OpCode::OPCODE_UPDATE_CINFO;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = 1;
	TransCommand.LParam = lpCurPlayer->smCharInfo.Level;
	TransCommand.SParam = lpCurPlayer->smCharInfo.ClassClan;
	TransCommand.EParam = lpCurPlayer->smCharInfo.bUpdateInfo[0];

	if (smWsockServer)
		smWsockServer->Send((char *)&TransCommand, TransCommand.size, TRUE);

	if (smWsockUserServer && smWsockServer != smWsockUserServer)
		smWsockUserServer->Send((char *)&TransCommand, TransCommand.size, TRUE);

	if (smWsockExtendServer && smWsockServer != smWsockExtendServer)
		smWsockExtendServer->Send((char *)&TransCommand, TransCommand.size, TRUE);

	if (smWsockDataServer && smWsockServer != smWsockDataServer && rsBlessCastle.dwMasterClan == GetClanCode(lpCurPlayer->smCharInfo.ClassClan))
		smWsockDataServer->Send((char *)&TransCommand, TransCommand.size, TRUE);

	if (AreaServerMode)
	{
		if (lpWSockServer_Area[0]) lpWSockServer_Area[0]->Send((char *)&TransCommand, TransCommand.size, TRUE);
		if (lpWSockServer_Area[1]) lpWSockServer_Area[1]->Send((char *)&TransCommand, TransCommand.size, TRUE);
	}

	return TRUE;
}









TRANS_SKIL_ATTACKDATA	Back_TransSkilAttackData;


int Skil_RangeAttack(int x, int y, int z, int range, int power, int TargetState)
{

	TRANS_SKIL_ATTACKDATA	TransSkilAttackData;
	int cnt, mCnt;

	int	dRange;
	int dx, dy, dz, dist;
	smCHAR	*lpChar;
	smWINSOCK *lpsmSendSock = 0;



	Record_ClinetLogFile("±¸¹öÀü °ø°ÝÆÐÅ¶ - Skil_RangeAttack ");
	quit = 1;
	return TRUE;


	mCnt = 0;

	dRange = range >> FLOATNS;
	dRange *= dRange;

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (mCnt >= SKIL_ATTACK_CHAR_MAX) break;
		if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].smCharInfo.State == smCHAR_STATE_ENEMY)
		{
			lpChar = &chrOtherPlayer[cnt];

			dx = (x - lpChar->pX) >> FLOATNS;
			dy = (y - lpChar->pY) >> FLOATNS;
			dz = (z - lpChar->pZ) >> FLOATNS;
			dist = dx * dx + dy * dy + dz * dz;

			if (dist < dRange)
			{



				TransSkilAttackData.dwTarObjectSerial[mCnt++] = chrOtherPlayer[cnt].dwObjectSerial;


				if (lpChar->smCharInfo.Life[1] && lpChar->smCharInfo.Life[0] == lpChar->smCharInfo.Life[1])
				{
					lpChar->EnableStateBar = TRUE;
				}

			}
		}
	}

	TransSkilAttackData.TargetCount = mCnt;

	TransSkilAttackData.code = OpCode::OPCODE_SKIL_ATTACKDATA;
	TransSkilAttackData.size = (sizeof(TRANS_SKIL_ATTACKDATA) - sizeof(DWORD)*SKIL_ATTACK_CHAR_MAX);
	TransSkilAttackData.size += sizeof(DWORD)*mCnt + 16;

	TransSkilAttackData.x = x;
	TransSkilAttackData.y = y;
	TransSkilAttackData.z = z;

	TransSkilAttackData.AttackState = TargetState;
	TransSkilAttackData.AttackSize = range;
	TransSkilAttackData.Power = power;

	TransSkilAttackData.dwChkSum = TransSkilAttackData.Power * 2002 +
		(TransSkilAttackData.x * TransSkilAttackData.y * TransSkilAttackData.z);

	LastAttackDamage = power;

	memcpy(&Back_TransSkilAttackData, &TransSkilAttackData, sizeof(TRANS_SKIL_ATTACKDATA));

	lpsmSendSock = GetAreaServerSock();

	if (lpsmSendSock && mCnt > 0)
	{

		Record_SendDamage(lpsmSendSock, TransSkilAttackData.Power);

		lpsmSendSock->Send((char *)&TransSkilAttackData, TransSkilAttackData.size, TRUE);
	}

	if (PkMode)
	{

		Skil_RangeAttack_User(x, y, z, range, power, TargetState);
	}

	return TRUE;
}



int Skil_RangeAttack_User(int x, int y, int z, int range, int power, int TargetState)
{
	TRANS_SKIL_ATTACKDATA	TransSkilAttackData;
	int cnt, mCnt;

	int	dRange;
	int dx, dy, dz, dist;
	smCHAR	*lpChar;
	smWINSOCK *lpsmSendSock = 0;

	mCnt = 0;

	dRange = range >> FLOATNS;
	dRange *= dRange;

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (mCnt >= SKIL_ATTACK_CHAR_MAX) break;
		if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].smCharInfo.State == smCHAR_STATE_USER)
		{
			lpChar = &chrOtherPlayer[cnt];

			dx = (x - lpChar->pX) >> FLOATNS;
			dy = (y - lpChar->pY) >> FLOATNS;
			dz = (z - lpChar->pZ) >> FLOATNS;
			dist = dx * dx + dy * dy + dz * dz;

			if (dist < dRange)
			{

				TransSkilAttackData.dwTarObjectSerial[mCnt++] = chrOtherPlayer[cnt].dwObjectSerial;

			}
		}
	}

	TransSkilAttackData.TargetCount = mCnt;

	TransSkilAttackData.code = OpCode::OPCODE_SKIL_ATTACKUSER;
	TransSkilAttackData.size = (sizeof(TRANS_SKIL_ATTACKDATA) - sizeof(DWORD)*SKIL_ATTACK_CHAR_MAX);
	TransSkilAttackData.size += sizeof(DWORD)*mCnt + 16;

	TransSkilAttackData.x = x;
	TransSkilAttackData.y = y;
	TransSkilAttackData.z = z;

	TransSkilAttackData.AttackState = TargetState;
	TransSkilAttackData.AttackSize = range;
	TransSkilAttackData.Power = power;

	TransSkilAttackData.dwChkSum = TransSkilAttackData.Power * 2002 +
		(TransSkilAttackData.x * TransSkilAttackData.y * TransSkilAttackData.z);


	if (mCnt > 0)
	{

		Record_SendDamage(smWsockUserServer, TransSkilAttackData.Power);

		smWsockUserServer->Send((char *)&TransSkilAttackData, TransSkilAttackData.size, TRUE);
	}







	return TRUE;
}


int Skil_RangeBoxAttack(smCHAR *lpCurChar, RECT *lpRect, int power, int TargetState, int UseAttackRating)
{

	TRANS_SKIL_ATTACKDATA	TransSkilAttackData;
	int cnt, mCnt;
	int dx, dy, dz;
	int Attack, accuracy;
	smCHAR	*lpChar;
	smWINSOCK *lpsmSendSock = 0;



	Record_ClinetLogFile("±¸¹öÀü °ø°ÝÆÐÅ¶ - Skil_RangeBoxAttack ");
	quit = 1;
	return TRUE;


	mCnt = 0;

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (mCnt >= SKIL_ATTACK_CHAR_MAX) break;
		if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].smCharInfo.State == smCHAR_STATE_ENEMY)
		{
			lpChar = &chrOtherPlayer[cnt];

			dx = (lpChar->pX - lpCurChar->pX) >> FLOATNS;
			dy = (lpChar->pY - lpCurChar->pY) >> FLOATNS;
			dz = (lpChar->pZ - lpCurChar->pZ) >> FLOATNS;


			GetMoveLocation(dx, dy, dz, 0, (-lpCurChar->Angle.y)&ANGCLIP, 0);

			if (GeoResult_X > lpRect->left && GeoResult_X<lpRect->right  &&
				GeoResult_Z>lpRect->top && GeoResult_Z < lpRect->bottom && abs(dy) < 256)
			{

				Attack = TRUE;

				if (UseAttackRating)
				{
					accuracy = sinGetAccuracy(chrOtherPlayer[cnt].smCharInfo.Level, chrOtherPlayer[cnt].smCharInfo.Defence);
					if ((rand() % 100) > accuracy)
						Attack = FALSE;
				}

				if (Attack)
				{
					TransSkilAttackData.dwTarObjectSerial[mCnt++] = chrOtherPlayer[cnt].dwObjectSerial;


					if (lpChar->smCharInfo.Life[1] && lpChar->smCharInfo.Life[0] == lpChar->smCharInfo.Life[1])
					{
						lpChar->EnableStateBar = TRUE;
					}
				}
			}

		}
	}

	TransSkilAttackData.TargetCount = mCnt;

	TransSkilAttackData.code = OpCode::OPCODE_SKIL_ATTACKDATA;
	TransSkilAttackData.size = (sizeof(TRANS_SKIL_ATTACKDATA) - sizeof(DWORD)*SKIL_ATTACK_CHAR_MAX);
	TransSkilAttackData.size += sizeof(DWORD)*mCnt + 16;

	TransSkilAttackData.x = lpCurChar->pX;
	TransSkilAttackData.y = lpCurChar->pY;
	TransSkilAttackData.z = lpCurChar->pZ;

	TransSkilAttackData.AttackState = TargetState;
	TransSkilAttackData.AttackSize = 0;
	TransSkilAttackData.Power = power;

	LastAttackDamage = power;

	TransSkilAttackData.dwChkSum = TransSkilAttackData.Power * 2002 +
		(TransSkilAttackData.x * TransSkilAttackData.y * TransSkilAttackData.z);


	memcpy(&Back_TransSkilAttackData, &TransSkilAttackData, sizeof(TRANS_SKIL_ATTACKDATA));

	lpsmSendSock = GetAreaServerSock();

	if (lpsmSendSock && mCnt > 0)
	{

		Record_SendDamage(lpsmSendSock, TransSkilAttackData.Power);

		lpsmSendSock->Send((char *)&TransSkilAttackData, TransSkilAttackData.size, TRUE);
	}
	return TRUE;
}


int Skill_CharRangeEffect(DWORD dwSkillCode, smCHAR *lpCurChar, smCHAR *lpCharTarget, int point)
{
	int time, rs;

	switch (dwSkillCode)
	{
	case SKILL_PLAY_ROAR:
		time = Roar_Time[point - 1];

		rs = lpCharTarget->smCharInfo.Resistance[sITEMINFO_BIONIC];
		if (rs < 0) rs = 0;
		if (rs >= 100) rs = 100;
		rs = 100 - rs;
		time = (time*rs) / 100;

		if (time)
		{
			if (time > 2) time = 2;
			AssaParticle_Stune(lpCharTarget, time);
			return TRUE;
		}
		break;

	case SKILL_PLAY_SOUL_SUCKER:
		if (lpCharTarget->smCharInfo.Brood != smCHAR_MONSTER_UNDEAD &&
			((lpCharTarget->smCharInfo.Life[1] * 50) / 100) < lpCharTarget->smCharInfo.Life[0])
		{

			sinSkillEffect_Soul_Sucker(lpCurChar, lpCharTarget);
			return TRUE;
		}
		break;

	}
	return FALSE;
}



int Skil_RangeBoxEffect(smCHAR *lpCurChar, RECT *lpRect, DWORD dwSkillCode, int TargetState)
{

	int cnt, mCnt;
	int dx, dy, dz;
	smCHAR	*lpChar;

	mCnt = 0;

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (mCnt >= SKIL_ATTACK_CHAR_MAX) break;
		if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].smCharInfo.State == smCHAR_STATE_ENEMY &&
			lpCurChar != &chrOtherPlayer[cnt])
		{

			lpChar = &chrOtherPlayer[cnt];

			dx = (lpChar->pX - lpCurChar->pX) >> FLOATNS;
			dy = (lpChar->pY - lpCurChar->pY) >> FLOATNS;
			dz = (lpChar->pZ - lpCurChar->pZ) >> FLOATNS;


			GetMoveLocation(dx, dy, dz, 0, (-lpCurChar->Angle.y)&ANGCLIP, 0);

			if (GeoResult_X > lpRect->left && GeoResult_X<lpRect->right  &&
				GeoResult_Z>lpRect->top && GeoResult_Z < lpRect->bottom && abs(dy) < 256)
			{

				if (Skill_CharRangeEffect(dwSkillCode, lpCurChar, &chrOtherPlayer[cnt], 0) == TRUE)
				{
					mCnt++;
				}
			}

		}
	}

	return mCnt;
}


int Skil_RangeEffect(smCHAR *lpCurChar, int Range, DWORD dwSkillCode, int TargetState, int point)
{

	int cnt, mCnt;
	int dx, dy, dz;
	smCHAR	*lpChar;
	int	dRange;

	dRange = Range * Range;

	mCnt = 0;

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (mCnt >= SKIL_ATTACK_CHAR_MAX) break;
		if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].smCharInfo.State == smCHAR_STATE_ENEMY &&
			lpCurChar != &chrOtherPlayer[cnt])
		{

			lpChar = &chrOtherPlayer[cnt];

			dx = (lpChar->pX - lpCurChar->pX) >> FLOATNS;
			dy = (lpChar->pY - lpCurChar->pY) >> FLOATNS;
			dz = (lpChar->pZ - lpCurChar->pZ) >> FLOATNS;

			if ((dx*dx + dy * dy + dz * dz) < dRange)
			{
				if (Skill_CharRangeEffect(dwSkillCode, lpCurChar, &chrOtherPlayer[cnt], point) == TRUE)
				{
					mCnt++;
				}
			}

		}
	}

	return mCnt;
}





DWORD EncodeParam(DWORD Param)
{
	return (Param + (Param << 4)) * 2002;
}




int QuickSendTransAttack(smCHAR *lpChar, int power, int AttackState, int Resistance)
{
	TRANS_ATTACKDATA	TransAttackData;
	smWINSOCK *lpsmSendSock = 0;
	int pow;


	Record_ClinetLogFile("±¸¹öÀü °ø°ÝÆÐÅ¶ - QuickSendTransAttack ");
	quit = 1;
	return TRUE;


	if (RestartPlayCount != 0) return FALSE;

	TransAttackData.code = OpCode::OPCODE_ATTACKDATA;
	TransAttackData.size = sizeof(TRANS_ATTACKDATA);

	TransAttackData.x = lpChar->pX;
	TransAttackData.y = lpChar->pY;
	TransAttackData.z = lpChar->pZ;

	TransAttackData.AttackState = AttackState;
	TransAttackData.AttackSize = 48 * fONE;
	TransAttackData.Power = power;

	if (Resistance)
	{
		TransAttackData.AttackState |= (Resistance << 16);
		pow = Resistance >> 4;
		if (pow > 0 && pow < 512)
		{
			TransAttackData.Power += pow;
		}
	}

	TransAttackData.dwDestObjectSerial = lpCurPlayer->dwObjectSerial;
	TransAttackData.dwTarObjectSerial = lpChar->dwObjectSerial;
	TransAttackData.dwChkSum = TransAttackData.Power * 2002 +
		(TransAttackData.x * TransAttackData.y * TransAttackData.z);

	LastAttackDamage = TransAttackData.Power;


	if (lpChar->smCharInfo.Life[1] && lpChar->smCharInfo.Life[0] == lpChar->smCharInfo.Life[1])
	{
		lpChar->EnableStateBar = TRUE;
	}

	if (lpChar->ServerCode)
	{
		lpsmSendSock = GetServerSock(lpChar->ServerCode);
	}


	if (lpsmSendSock)
	{

		Record_SendDamage(lpsmSendSock, TransAttackData.Power);

		return lpsmSendSock->Send((char *)&TransAttackData, TransAttackData.size, TRUE);
	}

	return NULL;
}


int QuickSendTransAttack(smCHAR *lpChar, int power)
{
	return QuickSendTransAttack(lpChar, power, 1, 0);
}

int QuickSendTransAttack(smCHAR *lpChar, int power, int Resistance)
{
	return QuickSendTransAttack(lpChar, power, 1, Resistance);
}





int SendRequestTrade(int dwObjectSerial, int Flag)
{
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = OpCode::OPCODE_TRADE_REQUST;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = dwObjectSerial;
	TransCommand.LParam = Flag;
	TransCommand.SParam = lpCurPlayer->dwObjectSerial;

	if (smWsockUserServer)
		return smWsockUserServer->Send((char *)&TransCommand, TransCommand.size, TRUE);

	return FALSE;
}


int SendTradeItem(sTRADE *lpTrade, DWORD dwSender)
{
	int cnt;
	int len;
	int	PotionError = 0;
	TRANS_TRADEITEMS TransTradeItems;
	sTRADE	sTradeBuff;

	len = 0;


	if (CheckTrade((void *)lpTrade) == FALSE)
	{
		SendRequestTrade(dwSender, 3);
		cTrade.CancelTradeItem();
		return FALSE;
	}

	memcpy(&sTradeBuff, lpTrade, sizeof(sTRADE));


	PotionError = ComparePotion();

	for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
	{
		if (!sTradeBuff.TradeItem[cnt].Flag)
		{
			ZeroMemory(&sTradeBuff.TradeItem[cnt], sizeof(sITEM));
		}
		else
		{
			sTradeBuff.TradeItem[cnt].sItemInfo.ItemHeader.Head = 0;
			if (PotionError)
			{
				sTradeBuff.TradeItem[cnt].sItemInfo.PotionCount = sTradeBuff.TradeItem[cnt].sItemInfo.ItemHeader.Head + 1;
			}
			len++;
		}
	}


	len = EecodeCompress((BYTE *)&sTradeBuff, TransTradeItems.TradeBuff, sizeof(sTRADE));
	if (len > TRANS_TRADE_BUFF_SIZE) return FALSE;

	TransTradeItems.code = OpCode::OPCODE_TRADEITEMS;
	TransTradeItems.size = len + 48;
	TransTradeItems.dwSum = 0;
	TransTradeItems.dwSender = lpCurPlayer->dwObjectSerial;
	TransTradeItems.dwRecver = dwSender;
	TransTradeItems.Temp[0] = 0;
	TransTradeItems.Temp[1] = 0;
	TransTradeItems.Temp[2] = 0;
	TransTradeItems.Temp[3] = 0;

	if (smWsockUserServer)
		return smWsockServer->Send((char *)&TransTradeItems, TransTradeItems.size, TRUE);

	return FALSE;
}


int RecvTradeItems(TRANS_TRADEITEMS *lpTransTradeItems, sTRADE *lpTrade)
{

	DecodeCompress(lpTransTradeItems->TradeBuff, (BYTE *)lpTrade);
	memcpy(&TransLastRecvTrade, lpTransTradeItems, lpTransTradeItems->size);
	return TRUE;
}


int SendTradeItem(DWORD dwSender)
{
	return SendTradeItem(&sTrade, dwSender);
}

int RecvTradeItems(TRANS_TRADEITEMS *lpTransTradeItems)
{
	int res;

	res = RecvTradeItems(lpTransTradeItems, &sTradeRecv);
	cTrade.LoadTradeItemIamge();
	cTrade.CheckTradeButtonOk();

	ItemPickUpFlag = 1;


	if (CheckTrade(&sTradeRecv) == FALSE)
	{
		SendRequestTrade(lpTransTradeItems->dwSender, 3);
		cTrade.CancelTradeItem();
		return FALSE;
	}

	if (sTrade.CheckFlag && !sTradeRecv.CheckFlag)
	{
		sTrade.CheckFlag = 0;
		TradeItemCancelCount++;
		if (TradeItemCancelCount >= 3)
		{

			SendRequestTrade(lpTransTradeItems->dwSender, 3);
			cTrade.CancelTradeItem();
			return FALSE;
		}
		else
		{
			cMessageBox.ShowMessage(MESSAGE_MOVE_TRADE_ITEM);
			SendTradeItem(lpTransTradeItems->dwSender);
		}
	}

	return res;
}


int SendTradeSucessKey(DWORD dwSender)
{

	return SendTradeSucessKey(&sTrade, dwSender);
}






int SendTradeSucessKey(sTRADE *lpTrade, DWORD dwSender)
{

	TRANS_TRADE_ITEMKEY	TransTradeItemKey;
	int cnt;
	int	TradeOpenFlag, CancelFlag;

	if (DisconnectFlag)
		return FALSE;

	TransTradeItemKey.code = OpCode::OPCODE_TRADE_ITEMKEY;
	TransTradeItemKey.size = sizeof(TRANS_TRADE_ITEMKEY);
	TransTradeItemKey.dwSender = lpCurPlayer->dwObjectSerial;;
	TransTradeItemKey.dwRecver = dwSender;
	TransTradeItemKey.Money = lpTrade->Money;
	TransTradeItemKey.Coin = lpTrade->Coin;

	TradeOpenFlag = cTrade.OpenFlag;
	cTrade.OpenFlag = 0;
	CancelFlag = 0;

	for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
	{
		if (lpTrade->TradeItem[cnt].Flag)
		{
			TransTradeItemKey.dwItemCode[cnt] = lpTrade->TradeItem[cnt].sItemInfo.CODE;
			TransTradeItemKey.dwItemKey[cnt] = lpTrade->TradeItem[cnt].sItemInfo.ItemHeader.Head;
			TransTradeItemKey.dwItemSum[cnt] = lpTrade->TradeItem[cnt].sItemInfo.ItemHeader.dwChkSum;

			if (FindInvenItem(lpTrade->TradeItem[cnt].sItemInfo.CODE,
				lpTrade->TradeItem[cnt].sItemInfo.ItemHeader.Head,
				lpTrade->TradeItem[cnt].sItemInfo.ItemHeader.dwChkSum) != 0)
			{

				CancelFlag = TRUE;


				SendInvenItemError(1, lpTrade->TradeItem[cnt].sItemInfo.CODE,
					lpTrade->TradeItem[cnt].sItemInfo.ItemHeader.Head,
					lpTrade->TradeItem[cnt].sItemInfo.ItemHeader.dwChkSum);
			}

			if ((TransTradeItemKey.dwItemCode[cnt] & sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
			{

				TransTradeItemKey.dwItemSum[cnt] = lpTrade->TradeItem[cnt].sItemInfo.PotionCount & 0xFFFF;
				TransTradeItemKey.dwItemSum[cnt] |= (lpTrade->TradeItem[cnt].sItemInfo.ItemHeader.dwChkSum) << 16;
				TransTradeItemKey.dwItemSum[cnt] ^= (TransTradeItemKey.dwItemSum[cnt] >> 16) ^ 0x5cbc;
			}

		}
		else
		{
			TransTradeItemKey.dwItemCode[cnt] = 0;
			TransTradeItemKey.dwItemKey[cnt] = 0;
			TransTradeItemKey.dwItemSum[cnt] = 0;
		}
	}

	cTrade.OpenFlag = TradeOpenFlag;

	if (!CancelFlag)
	{


		if (smWsockDataServer)
			smWsockDataServer->Send((char *)&TransTradeItemKey, TransTradeItemKey.size, TRUE);



		memcpy(&LastTransTradeItemKey, &TransTradeItemKey, sizeof(TRANS_TRADE_ITEMKEY));
		dwLastTransTradeKeyTime = dwPlayTime;
	}

	dwTradeMaskTime = dwPlayTime + 3000;

	return TRUE;
}



int RecvTradeSucessKey(TRANS_TRADE_ITEMKEY *lpTransTradeItemKey, sTRADE *lpTrade)
{
	int cnt;
	sTRADE sChkTrade;
	DWORD	dwChkSum1, dwChkSum2;
	int	ItemFlag;

	dwTradeMaskTime = dwPlayTime + 3000;

	if (TransLastRecvTrade.code)
	{

		DecodeCompress(TransLastRecvTrade.TradeBuff, (BYTE *)&sChkTrade);
		for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
		{
			memcpy(&lpTrade->TradeItem[cnt].sItemInfo, &sChkTrade.TradeItem[cnt].sItemInfo, sizeof(sITEMINFO));
		}
	}


	for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
	{
		if (lpTrade->TradeItem[cnt].Flag)
		{

			dwChkSum1 = lpTransTradeItemKey->dwItemSum[cnt];
			dwChkSum2 = lpTrade->TradeItem[cnt].sItemInfo.ItemHeader.dwChkSum;
			if ((lpTrade->TradeItem[cnt].sItemInfo.CODE&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
			{

				ItemFlag = 1;
				dwChkSum1 = dwChkSum1 >> 16;
				dwChkSum2 = dwChkSum2 & 0xFFFF;
			}
			else
				ItemFlag = 0;

			if (lpTransTradeItemKey->dwItemCode[cnt] == lpTrade->TradeItem[cnt].sItemInfo.CODE && dwChkSum1 == dwChkSum2)
			{


				lpTrade->TradeItem[cnt].sItemInfo.ItemHeader.Head = lpTransTradeItemKey->dwItemKey[cnt];


				if (!lpTrade->TradeItem[cnt].sItemInfo.ItemHeader.Head)
					lpTrade->TradeItem[cnt].Flag = 0;
				else
				{
					if (ItemFlag == 1)
					{

						ReformItem(&lpTrade->TradeItem[cnt].sItemInfo);
					}
				}
			}
			else
			{
				return FALSE;
			}
		}
		else
		{
			if (lpTransTradeItemKey->dwItemCode[cnt])
				return FALSE;

		}
	}



	return TRUE;
}




int SendTradeCheckItem(DWORD dwSender)
{

	TRANS_TRADE_CHECKITEM	TransTradeCheckItem;
	int cnt;

	if (DisconnectFlag)
		return FALSE;

	TransTradeCheckItem.code = OpCode::OPCODE_TRADE_READYITEM;
	TransTradeCheckItem.size = sizeof(TRANS_TRADE_CHECKITEM);
	TransTradeCheckItem.dwSender = lpCurPlayer->dwObjectSerial;
	TransTradeCheckItem.dwRecver = dwSender;

	if (sTrade.Money)
	{
		SendSaveMoney();
	}

	for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
	{
		if (sTrade.TradeItem[cnt].Flag)
		{
			TransTradeCheckItem.dwSendItemCode[cnt] = sTrade.TradeItem[cnt].sItemInfo.CODE;
			TransTradeCheckItem.dwSendItemSum[cnt] = sTrade.TradeItem[cnt].sItemInfo.ItemHeader.dwChkSum;




			if (CheckItemForm(&sTrade.TradeItem[cnt].sItemInfo) == FALSE)
				return FALSE;

		}
		else
		{
			TransTradeCheckItem.dwSendItemCode[cnt] = 0;
			TransTradeCheckItem.dwSendItemSum[cnt] = 0;
		}
	}


	for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
	{
		if (sTradeRecv.TradeItem[cnt].Flag)
		{
			TransTradeCheckItem.dwRecvItemCode[cnt] = sTradeRecv.TradeItem[cnt].sItemInfo.CODE;
			TransTradeCheckItem.dwRecvItemSum[cnt] = sTradeRecv.TradeItem[cnt].sItemInfo.ItemHeader.dwChkSum;
		}
		else
		{
			TransTradeCheckItem.dwRecvItemCode[cnt] = 0;
			TransTradeCheckItem.dwRecvItemSum[cnt] = 0;
		}
	}


	if (smWsockServer)
		smWsockServer->Send((char *)&TransTradeCheckItem, TransTradeCheckItem.size, TRUE);

	if (smWsockUserServer && smWsockServer != smWsockUserServer)
		smWsockUserServer->Send((char *)&TransTradeCheckItem, TransTradeCheckItem.size, TRUE);

	dwTradeMaskTime = dwPlayTime + 3000;

	return TRUE;
}


int RecvTradeCheckItem(TRANS_TRADE_CHECKITEM *lpTransTradeCheckItem)
{
	int cnt;

	dwTradeMaskTime = dwPlayTime + 3000;

	if (DisconnectFlag)
		return FALSE;

	for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
	{
		if (sTrade.TradeItem[cnt].Flag)
		{
			if (lpTransTradeCheckItem->dwRecvItemCode[cnt] != sTrade.TradeItem[cnt].sItemInfo.CODE ||
				((lpTransTradeCheckItem->dwRecvItemCode[cnt] & sinITEM_MASK1) != (sinPM1&sinITEM_MASK1) &&
					lpTransTradeCheckItem->dwRecvItemSum[cnt] != sTrade.TradeItem[cnt].sItemInfo.ItemHeader.dwChkSum))
			{

				return FALSE;

			}
		}
		else
		{
			if (lpTransTradeCheckItem->dwRecvItemCode[cnt])
				return FALSE;
		}

		if (sTradeRecv.TradeItem[cnt].Flag)
		{
			if (lpTransTradeCheckItem->dwSendItemCode[cnt] != sTradeRecv.TradeItem[cnt].sItemInfo.CODE ||
				((lpTransTradeCheckItem->dwSendItemCode[cnt] & sinITEM_MASK1) != (sinPM1&sinITEM_MASK1) &&
					lpTransTradeCheckItem->dwSendItemSum[cnt] != sTradeRecv.TradeItem[cnt].sItemInfo.ItemHeader.dwChkSum))
			{

				return FALSE;

			}
		}
		else
		{
			if (lpTransTradeCheckItem->dwSendItemCode[cnt])
				return FALSE;
		}
	}

	return TRUE;
}








int SendJoinPartyUser(DWORD dwObjectCode)
{
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = OpCode::OPCODE_PARTY_JOIN;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = dwObjectCode;
	TransCommand.LParam = 0;
	TransCommand.SParam = 0;

	return smWsockUserServer->Send((char *)&TransCommand, TransCommand.size, TRUE);
}


int	PartyButton(int Num, int Button)
{


	DWORD	dwCode;
	smTRANS_COMMAND	smTransCommand;

	if (!InterfaceParty.PartyMemberCount) return FALSE;

	dwCode = 0;

	if (Num >= 0)
		dwCode = InterfaceParty.PartyMember[Num].ChrCode;
	else
		dwCode = 0;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = OpCode::OPCODE_PARTY_COMMAND;
	smTransCommand.WParam = dwCode;
	smTransCommand.LParam = Button;
	smTransCommand.SParam = 0;

	if (Button < 3 && InterfaceParty.PartyMember[0].ChrCode != lpCurPlayer->dwObjectSerial)
	{

		return FALSE;
	}

	return smWsockUserServer->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
}







int	SetTotalSubMoney(int Money)
{
	TotalSubMoney += Money;

	return TRUE;
}

int	SetTotalAddMoney(int Money)
{
	TotalAddMoney += Money;

	return TRUE;
}

int	SetTotalAddExp(int Exp)
{
	TotalAddExp += Exp;

	return TRUE;
}

int	SetTotalSubExp(int Exp)
{
	TotalSubExp += Exp;

	return TRUE;
}

int	GetTotalMoney()
{
	int m;

	m = sServerMoney[0].InputMoney + sServerMoney[1].InputMoney + sServerMoney[2].InputMoney + WareHouseSubMoney + TotalAddMoney - TotalSubMoney;

	return m;
}

int GetTotalSubExp()
{
	int m;

	m = (sServerExp[0].InputExp + sServerExp[1].InputExp + sServerExp[2].InputExp) - (TotalAddExp - TotalSubExp);

	return m;
}

int GetTotalExp()
{
	int m;

	m = sServerExp[0].InputExp + sServerExp[1].InputExp + sServerExp[2].InputExp + TotalAddExp - TotalSubExp;

	return m;
}


int	SaveWareHouse(sWAREHOUSE *lpWareHouse, TRANS_WAREHOUSE *lpTransWareHouse)
{
	TRANS_WAREHOUSE	TransWareHouse;

	sWAREHOUSE	WareHouseCheck;
	int	CompSize;
	int cnt;
	DWORD	dwChkSum;
	char	*szComp1, *szComp2;
	int	flag;

	if (lpTransWareHouse) flag = 1;
	else flag = 0;

	if (!flag && QuitSave)	return FALSE;

	for (cnt = 0; cnt < 100; cnt++)
	{
		if (!lpWareHouse->WareHouseItem[cnt].Flag)
		{
			ZeroMemory(&lpWareHouse->WareHouseItem[cnt], sizeof(sITEM));
		}
	}


	CompSize = EecodeCompress((BYTE *)lpWareHouse, (BYTE *)TransWareHouse.Data, sizeof(sWAREHOUSE), sizeof(sITEM) * 100);



	if (!flag && CompSize > (smSOCKBUFF_SIZE - 256))
		return FALSE;

	if (flag && CompSize > (smSOCKBUFF_SIZE - 140))
		return FALSE;


	DecodeCompress((BYTE *)TransWareHouse.Data, (BYTE *)&WareHouseCheck, sizeof(sWAREHOUSE));

	szComp1 = (char *)lpWareHouse;
	szComp2 = (char *)&WareHouseCheck;

	dwChkSum = 0;

	for (cnt = 0; cnt < sizeof(sWAREHOUSE); cnt++)
	{
		if (szComp1[cnt] != szComp2[cnt])
		{
			return FALSE;
		}
		else
		{
			dwChkSum += szComp1[cnt] * (cnt + 1);
		}
	}



	WareHouseSubMoney += (CompWareHouseMoney - lpWareHouse->Money);
	CompWareHouseMoney = 0;


	TransWareHouse.code = OpCode::OPCODE_WAREHOUSE;
	TransWareHouse.size = sizeof(TRANS_WAREHOUSE) - (sizeof(sWAREHOUSE) - CompSize);
	TransWareHouse.DataSize = CompSize;
	TransWareHouse.dwChkSum = dwChkSum;
	TransWareHouse.wVersion[0] = Version_WareHouse;
	TransWareHouse.wVersion[1] = 0;

	if (!flag)
	{

		TransWareHouse.WareHouseMoney = lpWareHouse->Money ^ (dwChkSum^OpCode::OPCODE_WAREHOUSE);
		TransWareHouse.UserMoney = lpCurPlayer->smCharInfo.Money ^ (dwChkSum^OpCode::OPCODE_WAREHOUSE);
	}

	TransWareHouse.dwTemp[0] = 0;
	TransWareHouse.dwTemp[1] = 0;
	TransWareHouse.dwTemp[2] = 0;
	TransWareHouse.dwTemp[3] = 0;
	TransWareHouse.dwTemp[4] = 0;

	dwLastWareHouseChkSum = dwChkSum;

	if (flag)
	{
		memcpy(lpTransWareHouse, &TransWareHouse, sizeof(TRANS_WAREHOUSE));
		return TRUE;
	}

	if (TransWareHouse.size > smSOCKBUFF_SIZE) TransWareHouse.size = smSOCKBUFF_SIZE;

	if (smWsockDataServer)
	{
		smWsockDataServer->Send((char *)&TransWareHouse, TransWareHouse.size, TRUE);

		SaveGameData();
		return TRUE;
	}

	return FALSE;
}

int	SaveWareHouse(sWAREHOUSE *lpWareHouse)
{
	return SaveWareHouse(lpWareHouse, 0);
}


int	LoadWareHouse(TRANS_WAREHOUSE *lpTransWareHouse, sWAREHOUSE *lpWareHouse, int flag)
{
	sWAREHOUSE	WareHouseCheck;
	int cnt;
	DWORD	dwChkSum;
	char	*szComp;
	//char	szMsgBuff[128];

	if (lpTransWareHouse->DataSize == 0)
	{

		ZeroMemory(lpWareHouse, sizeof(sWAREHOUSE));
		lpWareHouse->Money = 2023;
		lpWareHouse->Weight[0] = 500;
		CompWareHouseMoney = lpWareHouse->Money;
		return TRUE;
	}

	DecodeCompress((BYTE *)lpTransWareHouse->Data, (BYTE *)&WareHouseCheck);

	dwChkSum = 0;

	szComp = (char *)&WareHouseCheck;

	for (cnt = 0; cnt < sizeof(sWAREHOUSE); cnt++)
	{
		dwChkSum += szComp[cnt] * (cnt + 1);
	}
	if (dwChkSum == lpTransWareHouse->dwChkSum)
	{

		if (!flag && dwLastWareHouseChkSum && dwLastWareHouseChkSum != lpTransWareHouse->dwChkSum && smConfig.getSecurity() < AccountTypes::SEC_MODERATOR)
		{

			return FALSE;
		}

		memcpy(lpWareHouse, &WareHouseCheck, sizeof(sWAREHOUSE));

		CompWareHouseMoney = lpWareHouse->Money;

		for (cnt = 0; cnt < 100; cnt++)
		{
			if (lpWareHouse->WareHouseItem[cnt].Flag)
			{


				if (!lpWareHouse->WareHouseItem[cnt].sItemInfo.Temp0)
					lpWareHouse->WareHouseItem[cnt].sItemInfo.Temp0 = lpWareHouse->WareHouseItem[cnt].sItemInfo.ItemHeader.dwChkSum + lpWareHouse->WareHouseItem[cnt].sItemInfo.CODE;



				if (!lpWareHouse->WareHouseItem[cnt].sItemInfo.ItemHeader.dwTime)
				{

					lpWareHouse->WareHouseItem[cnt].sItemInfo.ItemHeader.dwTime =
						(lpWareHouse->WareHouseItem[cnt].sItemInfo.ItemHeader.Head >> 2) ^ (lpWareHouse->WareHouseItem[cnt].sItemInfo.ItemHeader.dwChkSum << 2);
				}


				if ((lpWareHouse->WareHouseItem[cnt].sItemInfo.CODE&sinITEM_MASK2) == sinSP1)
				{

					if (lpWareHouse->WareHouseItem[cnt].sItemInfo.PotionCount > 1)	lpWareHouse->WareHouseItem[cnt].Flag = 0;



				}

				if (DeleteEventItem_TimeOut(&lpWareHouse->WareHouseItem[cnt].sItemInfo) == TRUE)
				{

					lpWareHouse->WareHouseItem[cnt].Flag = 0;
					//wsprintf(szMsgBuff, mgItemTimeOut, lpWareHouse->WareHouseItem[cnt].sItemInfo.ItemName);
					//AddChatBuff(szMsgBuff, 0);
				}
			}
		}
		return TRUE;
	}

	return FALSE;
}


int	LoadWareHouse(TRANS_WAREHOUSE *lpTransWareHouse, sWAREHOUSE *lpWareHouse)
{
	return LoadWareHouse(lpTransWareHouse, lpWareHouse, 0);
}


int SendCollectMoney(int Money)
{


	sITEM	sItemMoney;
	int j;


	memset(&sItemMoney, 0, sizeof(sITEM));
	sItemMoney.sItemInfo.CODE = sinGG1 | sin01;
	for (j = 0; j < MAX_ITEM; j++)
	{
		if (sItem[j].CODE == sItemMoney.sItemInfo.CODE)
		{
			memcpy(&sItemMoney, &sItem[j], sizeof(sITEM));
			sItemMoney.sItemInfo.Money = Money;
			sItemMoney.sItemInfo.ItemKindCode = OpCode::OPCODE_COLLECTMONEY;
			ReformItem(&sItemMoney.sItemInfo);
			if (sinThrowItemToFeild(&sItemMoney))
			{
				AddInvenMoney(-Money);
				return TRUE;
			}
		}
	}

	return FALSE;
}


int PlayerKilling(DWORD dwObjectSerial)
{
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = OpCode::OPCODE_PLAYERKILLING;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = dwObjectSerial;
	TransCommand.LParam = lpCurPlayer->dwObjectSerial;
	TransCommand.SParam = 0;

	if (smWsockUserServer)
	{
		return smWsockUserServer->Send((char *)&TransCommand, TransCommand.size, TRUE);
	}
	return FALSE;
}




int SendCraftItemToServer(void *lpsCraftItem_Send)
{

	sCRAFTITEM_SERVER	*lpCraftItem_Send = (sCRAFTITEM_SERVER *)lpsCraftItem_Send;

	lpCraftItem_Send->size = sizeof(sCRAFTITEM_SERVER);
	lpCraftItem_Send->code = OpCode::OPCODE_CRAFTITEM;

	if (smWsockDataServer)
	{
		return smWsockDataServer->Send((char *)lpCraftItem_Send, lpCraftItem_Send->size, TRUE);
	}

	return FALSE;
}


int SendWingItemToServer(void *lpsCraftItem_Send)
{

	sCRAFTITEM_SERVER	*lpCraftItem_Send = (sCRAFTITEM_SERVER *)lpsCraftItem_Send;

	lpCraftItem_Send->size = sizeof(sCRAFTITEM_SERVER);
	lpCraftItem_Send->code = OpCode::OPCODE_WINGITEM;

	if (smWsockDataServer)
	{
		return smWsockDataServer->Send((char *)lpCraftItem_Send, lpCraftItem_Send->size, TRUE);
	}

	return FALSE;
}



int SendAgingItemToServer(void *lpsCraftItem_Send)
{

	sCRAFTITEM_SERVER	*lpCraftItem_Send = (sCRAFTITEM_SERVER *)lpsCraftItem_Send;

	lpCraftItem_Send->size = sizeof(sCRAFTITEM_SERVER);
	lpCraftItem_Send->code = OpCode::OPCODE_AGINGITEM;

	if (smWsockDataServer)
	{
		return smWsockDataServer->Send((char *)lpCraftItem_Send, lpCraftItem_Send->size, TRUE);
	}

	return FALSE;
}


int SendLinkCoreToServer(sITEMINFO *lpItem)
{
	TRANS_ITEMINFO	TransItemInfo;
	int len;

	TransItemInfo.size = sizeof(TRANS_ITEMINFO);
	TransItemInfo.code = OpCode::OPCODE_MAKE_LINKCORE;
	memcpy(&TransItemInfo.Item, lpItem, sizeof(sITEMINFO));

	TransItemInfo.x = lpCurPlayer->pX;
	TransItemInfo.y = lpCurPlayer->pY;
	TransItemInfo.z = lpCurPlayer->pZ;

	TransItemInfo.dwSeCode[0] = 0;
	TransItemInfo.dwSeCode[1] = 0;
	TransItemInfo.dwSeCode[2] = 0;
	TransItemInfo.dwSeCode[3] = 0;

	len = lstrlen(lpItem->ItemName);
	if (lpItem->ItemName[len + 1])
	{
		TransItemInfo.code = OpCode::OPCODE_USE_LINKCORE;

		if (lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_ROOM)
		{

			return FALSE;
		}

		if (smWsockServer)
			return smWsockServer->Send((char *)&TransItemInfo, TransItemInfo.size, TRUE);
	}

	if (smWsockDataServer)
	{
		return smWsockDataServer->Send((char *)&TransItemInfo, TransItemInfo.size, TRUE);
	}

	return FALSE;
}

int SucessLinkCore(smTRANS_COMMAND_EX *lpTransCommandEx)
{
	int x, z, cnt;

	sITEMINFO	*lpItem;


	lpItem = FindInvenItem(lpTransCommandEx->WxParam, lpTransCommandEx->LxParam, lpTransCommandEx->SxParam);

	if (lpItem)
	{
		SendUseItemCodeToServer(lpItem);
		cInvenTory.DeleteInvenItemToServer(lpTransCommandEx->WxParam, lpTransCommandEx->LxParam, lpTransCommandEx->SxParam);
		ResetInvenItemCode();

		if (FindInvenItem(lpTransCommandEx->WxParam, lpTransCommandEx->LxParam, lpTransCommandEx->SxParam) != 0) return FALSE;

	}
	else
		return FALSE;


	CloseEachPlayer();

	WarpFieldNearPos(lpTransCommandEx->EParam, lpTransCommandEx->WParam, lpTransCommandEx->SParam, &x, &z);

	lpCurPlayer->SetPosi(lpTransCommandEx->WParam, lpTransCommandEx->LParam, lpTransCommandEx->SParam, 0, 0, 0);
	TraceCameraPosi.x = lpCurPlayer->pX;
	TraceCameraPosi.y = lpCurPlayer->pY;
	TraceCameraPosi.z = lpCurPlayer->pZ;
	TraceTargetPosi.x = lpCurPlayer->pX;
	TraceTargetPosi.y = lpCurPlayer->pY;
	TraceTargetPosi.z = lpCurPlayer->pZ;


	lpCurPlayer->OnStageField = -1;
	if (smGameStage[0])
	{
		cnt = smGameStage[0]->GetFloorHeight(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, lpCurPlayer->Pattern->SizeHeight);
		lpCurPlayer->OnStageField = 0;
	}
	if (cnt == CLIP_OUT && smGameStage[1])
	{
		lpCurPlayer->OnStageField = 1;
	}

	StartEffect(lpCurPlayer->pX, lpCurPlayer->pY + 48 * fONE, lpCurPlayer->pZ, EFFECT_RETURN1);
	SkillPlaySound(SKILL_SOUND_LEARN, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
	RestartPlayCount = 350;

	return TRUE;
}



int SendAgingUpgradeItemToServer(sITEMINFO *lpItem)
{
	TRANS_ITEMINFO	TransItemInfo;

	if (TransAgingItemFlag) return FALSE;

	TransItemInfo.code = OpCode::OPCODE_AGING_UPGRADE;
	TransItemInfo.size = sizeof(TRANS_ITEMINFO);
	TransItemInfo.x = 0;
	TransItemInfo.y = 0;
	TransItemInfo.z = 0;
	memcpy(&TransItemInfo.Item, lpItem, sizeof(sITEMINFO));

	if (smWsockDataServer)
	{
		if (smWsockDataServer->Send((char *)&TransItemInfo, TransItemInfo.size, TRUE) == TRUE)
		{
			TransAgingItemFlag = TRUE;
			return TRUE;
		}
	}
	return FALSE;
}





int ClearInvenPotionCount()
{
	int cnt;

	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (cInvenTory.InvenItem[cnt].Flag && (cInvenTory.InvenItem[cnt].sItemInfo.CODE&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
		{
			cInvenTory.InvenItem[cnt].sItemInfo.PotionCount = 1;
		}
	}

	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (cInvenTory.InvenItemTemp[cnt].Flag && (cInvenTory.InvenItemTemp[cnt].sItemInfo.CODE&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
		{
			cInvenTory.InvenItemTemp[cnt].sItemInfo.PotionCount = 1;
		}
	}

	if (cTrade.OpenFlag)
	{
		for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
		{
			if (sTrade.TradeItem[cnt].Flag && (sTrade.TradeItem[cnt].sItemInfo.CODE&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
			{
				sTrade.TradeItem[cnt].sItemInfo.PotionCount = 1;
			}
		}
	}

	if (MouseItem.Flag && (MouseItem.sItemInfo.CODE&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
		MouseItem.sItemInfo.PotionCount = 1;

	cInvenTory.ReFormPotionNum();

	SaveGameData();

	return TRUE;
}


sITEMINFO *FindItemFromCode(DWORD dwItemCode)
{
	int cnt;

	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (cInvenTory.InvenItem[cnt].Flag && cInvenTory.InvenItem[cnt].sItemInfo.CODE == dwItemCode)
		{
			return &cInvenTory.InvenItem[cnt].sItemInfo;
		}
	}
	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (cInvenTory.InvenItemTemp[cnt].Flag && cInvenTory.InvenItemTemp[cnt].sItemInfo.CODE == dwItemCode)
		{
			return &cInvenTory.InvenItemTemp[cnt].sItemInfo;
		}
	}

	return NULL;
}

int SendGetItemInfoPerf(DWORD dwItemCode)
{
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = OpCode::OPCODE_SHOWITEMINFO_PERF;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = dwItemCode;
	TransCommand.LParam = 0;
	TransCommand.SParam = 0;

	if (smWsockUserServer)
		smWsockUserServer->Send((char *)&TransCommand, TransCommand.size, TRUE);

	return TRUE;
}

DWORD	dwLastCheckItemTime = 0;


int	SendCheckItemToServer(sITEMINFO *lpItem)
{

	TRANS_ITEMINFO	TransItemInfo;



	if ((dwLastCheckItemTime + 10000) > dwPlayTime)
	{

		return FALSE;
	}


	TransItemInfo.code = OpCode::OPCODE_CHECKITEM;
	TransItemInfo.size = sizeof(TRANS_ITEMINFO);

	memcpy(&TransItemInfo.Item, lpItem, sizeof(sITEMINFO));

	TransItemInfo.x = 0;
	TransItemInfo.y = 0;
	TransItemInfo.z = 0;

	if (smWsockUserServer)
	{
		smWsockUserServer->Send((char *)&TransItemInfo, TransItemInfo.size, TRUE);
	}
	dwLastCheckItemTime = dwPlayTime;

	return TRUE;
}


int RecvCheckItemFromServer(TRANS_ITEM_CODE *lpTransItemCode)
{

	switch (lpTransItemCode->code)
	{
	case OpCode::OPCODE_CHECKITEM:



		break;

	case OpCode::OPCODE_ERRORITEM:

		cInvenTory.DeleteInvenItemToServer(lpTransItemCode->dwItemCode, lpTransItemCode->dwHead, lpTransItemCode->dwChkSum);


		if (FindInvenItem(lpTransItemCode->dwItemCode, lpTransItemCode->dwHead, lpTransItemCode->dwChkSum) == 0)
		{

			SendInvenItemError(0, lpTransItemCode->dwItemCode, lpTransItemCode->dwHead, lpTransItemCode->dwChkSum);
			ResetInvenItemCode();
		}

		break;

	case OpCode::OPCODE_CLEARPOTION:

		ClearInvenPotionCount();
		break;
	}

	return TRUE;
}

int RecvItemInfoPerf(TRANS_ITEMINFO *lpTransItemInfo)
{
	DWORD dwKey = 0;

	dwKey = lpTransItemInfo->Item.CODE;

	std::unordered_map<DWORD, sITEMINFO>::const_iterator it = mapItemInfo.find(dwKey);

	if (it == mapItemInfo.end())
	{
		mapItemInfo[dwKey] = lpTransItemInfo->Item;
	}

	bSendGetItemInfoPerf = false;

	return TRUE;
}


int	SellItemToServer(sITEMINFO *lpItem, int Count)
{

	TRANS_ITEMINFO	TransItemInfo;

	TransItemInfo.code = OpCode::OPCODE_SHOP_SELLITEM;
	TransItemInfo.size = sizeof(TRANS_ITEMINFO);

	memcpy(&TransItemInfo.Item, lpItem, sizeof(sITEMINFO));

#ifdef _TEST_SERVER

	if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR && VRKeyBuff[VK_CONTROL] && VRKeyBuff['N'] && VRKeyBuff['B'])
	{

		lpItem->Durability[0] = lpItem->Durability[1] * 100;
	}
#endif

	TransItemInfo.x = Count;
	TransItemInfo.y = lpCurPlayer->smCharInfo.Money;
	TransItemInfo.z = 0;

	if (smWsockDataServer)
	{
		return smWsockDataServer->Send((char *)&TransItemInfo, TransItemInfo.size, TRUE);
	}

	return FALSE;
}





int Chk_InventPosCount = 1;
DWORD	dwCheckInvenItemTime = 0;


int CheckInvenItemToServer()
{
	int cnt;

	if (dwCheckInvenItemTime > dwPlayTime) return TRUE;

	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (cInvenTory.InvenItem[cnt].ItemPosition == Chk_InventPosCount)
		{

			SendCheckItemToServer(&cInvenTory.InvenItem[cnt].sItemInfo);
		}
	}

	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (cInvenTory.InvenItemTemp[cnt].ItemPosition == Chk_InventPosCount)
		{

			SendCheckItemToServer(&cInvenTory.InvenItemTemp[cnt].sItemInfo);
		}
	}

	Chk_InventPosCount++;
	dwCheckInvenItemTime = dwPlayTime + 55 * 1000;

	if (Chk_InventPosCount >= 11 || Chk_InventPosCount < 1) Chk_InventPosCount = 1;

	return TRUE;
}



HANDLE	hTimeCheckThread = 0;
int		TimeCheckCounter;

DWORD WINAPI TimeCheckThread(void *pInfo)
{
	HANDLE	hThread;
	DWORD	dwTime;
	DWORD	dwLastTime;
	int		cnt;

	hThread = GetCurrentThread();
	dwTime = GetCurrentTime();
	dwLastTime = dwTime;
	TimeCheckCounter = 0;

	while (1)
	{
		dwTime = GetCurrentTime();
		cnt = dwTime - dwLastTime;
		if (cnt > PlayTimerMax) PlayTimerMax = cnt;
		dwLastTime = dwTime;
		TimeCheckCounter++;
		Sleep(800);
	}

	ExitThread(TRUE);
	return TRUE;
}



int OpenTimeCheckThread()
{
	DWORD	dwTimeCheckThreadID;

	if (!hTimeCheckThread)
	{
		hTimeCheckThread = CreateThread(NULL, 0, TimeCheckThread, 0, 0, &dwTimeCheckThreadID);
	}

	return TRUE;
}

int	PlayTimerMax_SendingCount = 0;

int SendPlayTimerMax()
{
	smTRANS_COMMAND	smTransCommand;

	if (PlayTimerMax >= 10000 || (PlayTimerMax_SendingCount & 0x7) == 0)
	{
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = OpCode::OPCODE_PROCESS_TIMEMAX;
		smTransCommand.WParam = PlayTimerMax;
		smTransCommand.LParam = TimeCheckCounter;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = 0;

		if (smWsockDataServer)
			smWsockDataServer->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

		PlayTimerMax = 0;
	}

	PlayTimerMax_SendingCount++;

	return TRUE;
}








DWORD funcCheckMemSum(DWORD FuncPoint, int count)
{
	int cnt;
	DWORD dwSum;
	int	xcnt;
	DWORD *lpGetPrtectPoint;


	lpGetPrtectPoint = (DWORD *)FuncPoint;

	dwSum = 0;
	xcnt = 1;

	for (cnt = 0; cnt < count; cnt++)
	{
		xcnt += cnt;
		dwSum += lpGetPrtectPoint[cnt] * xcnt;
	}

	return dwSum;
}







DWORD	dwFuncList[][2] = {
	{ (DWORD)funcCheckMemSum << 1				,	512		},
	{ (DWORD)Check_PlaySubReleaseFunc << 1	,	512		},
	{ (DWORD)PlayPat3D << 1					,	2048	},
	{ (DWORD)Check_CodeSafe << 1				,	1024	},
	{ (DWORD)AddExp << 1						,	512		},
	{ (DWORD)sinSetLife << 1					,	512		},
	{ (DWORD)NetWorkPlay << 1					,	2800	},

	{ (DWORD)E_Shield_BlockRate << 1			,	(DWORD)((Meteo_UseMana - E_Shield_BlockRate) + 10) },

	{ (DWORD)Code_VRamBuffOpen << 1			,	3600	},
	{ 0,0 }
};




int	SendClientFuncPos()
{

	TRANS_CLIENT_FUNPOS	TransClientFuncPos;
	int cnt;


	ZeroMemory(&TransClientFuncPos, sizeof(TRANS_CLIENT_FUNPOS));

	TransClientFuncPos.code = OpCode::OPCODE_CLIENT_FUNCPOS;
	TransClientFuncPos.size = sizeof(TRANS_CLIENT_FUNPOS);
	TransClientFuncPos.ClientVersion = Client_Version;

	cnt = 0;
	TransClientFuncPos.dwFunc_CheckMemSum = dwFuncList[cnt][0] >> 1;
	TransClientFuncPos.dwFuncValue[cnt].dwFunc = dwFuncList[cnt][0] >> 1;
	TransClientFuncPos.dwFuncValue[cnt].dwLen = dwFuncList[cnt][1];
	TransClientFuncPos.dwFuncValue[cnt].dwChkSum = funcCheckMemSum(TransClientFuncPos.dwFuncValue[cnt].dwFunc, TransClientFuncPos.dwFuncValue[cnt].dwLen);


	while (1)
	{

		if (dwFuncList[cnt][0] == 0) break;
		if (cnt >= dwFUNC_VALUE_MAX)  break;

		TransClientFuncPos.dwFuncValue[cnt].dwFunc = dwFuncList[cnt][0] >> 1;
		TransClientFuncPos.dwFuncValue[cnt].dwLen = dwFuncList[cnt][1];
		TransClientFuncPos.dwFuncValue[cnt].dwChkSum = funcCheckMemSum(TransClientFuncPos.dwFuncValue[cnt].dwFunc, TransClientFuncPos.dwFuncValue[cnt].dwLen);

		cnt++;
	}

	TransClientFuncPos.FuncCount = cnt;


	if (smWsockDataServer)
		return smWsockDataServer->Send((char *)&TransClientFuncPos, TransClientFuncPos.size, TRUE);

	return FALSE;
}



int	RecvMemFuncData(TRANS_FUNC_MEMORY *TransFuncMem)
{
	smTRANS_COMMAND	smTransCommand;

	fnChkMem = (LPFN_CheckMem)((void *)TransFuncMem->szData);

	smTransCommand.size = 0;

	fnChkMem(TransFuncMem, &smTransCommand);

	if (smWsockDataServer && smTransCommand.size > 0)
		smWsockDataServer->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

	return TRUE;
}




#define	RECV_TRANSITEM_QUE_MAX			256
#define	RECV_TRANSITEM_QUE_MASK			255

TRANS_ITEMINFO	Recv_TransItemInfo_Que[RECV_TRANSITEM_QUE_MAX];

int	RecvTransItemQue_Push = 0;
int	RecvTransItemQue_Pop = 0;


int	PushRecvTransItemQue(TRANS_ITEMINFO *lpTransItemInfo)
{
	int mCnt;

	mCnt = RecvTransItemQue_Push & RECV_TRANSITEM_QUE_MASK;

	memcpy(&Recv_TransItemInfo_Que[mCnt], lpTransItemInfo, sizeof(TRANS_ITEMINFO));
	RecvTransItemQue_Push++;
	RecvTransItemQue_Pop = RecvTransItemQue_Push - RECV_TRANSITEM_QUE_MASK;
	if (RecvTransItemQue_Pop < 0) RecvTransItemQue_Pop = 0;

	return TRUE;
}


TRANS_ITEMINFO	*FindRecvTransItemQue(DWORD dwCode, DWORD dwHead, DWORD dwChkSum)
{
	int cnt, mCnt;

	for (cnt = RecvTransItemQue_Pop; cnt < RecvTransItemQue_Push; cnt++)
	{
		mCnt = cnt & RECV_TRANSITEM_QUE_MASK;

		if (Recv_TransItemInfo_Que[mCnt].Item.CODE == dwCode &&
			Recv_TransItemInfo_Que[mCnt].Item.ItemHeader.Head == dwHead &&
			Recv_TransItemInfo_Que[mCnt].Item.ItemHeader.dwChkSum == dwChkSum)
		{

			return &Recv_TransItemInfo_Que[mCnt];
		}
	}

	return NULL;
}


int CheckRecvTrnsItemQue()
{
	int cnt, mCnt;

	for (cnt = RecvTransItemQue_Pop; cnt < RecvTransItemQue_Push; cnt++)
	{
		mCnt = cnt & RECV_TRANSITEM_QUE_MASK;
		if (Recv_TransItemInfo_Que[mCnt].Item.CODE) return FALSE;
	}

	return TRUE;
}


int SendUseItemCodeToServer(sITEMINFO *lpItem)
{
	smTRANS_COMMAND_EX	smTransCommandEx;

	smTransCommandEx.code = OpCode::OPCODE_USEITEM_CODE;
	smTransCommandEx.size = sizeof(smTRANS_COMMAND);
	smTransCommandEx.WParam = lpItem->CODE;
	smTransCommandEx.LParam = lpItem->ItemHeader.Head;
	smTransCommandEx.SParam = lpItem->ItemHeader.dwChkSum;
	smTransCommandEx.EParam = lpItem->PotionCount;

	smTransCommandEx.WxParam = 0;
	smTransCommandEx.LxParam = 0;
	smTransCommandEx.SxParam = 0;
	smTransCommandEx.ExParam = 0;

	if (smWsockDataServer)
	{
		return smWsockDataServer->Send((char *)&smTransCommandEx, smTransCommandEx.size, TRUE);
	}

	return FALSE;
}


int RecvCommandUser(smTRANS_COMMAND_EX *lpTransCommandEx)
{
	smCHAR *lpChar;
	smCHAR *lpChar2;

	switch (lpTransCommandEx->WParam)
	{
	case smCOMMNAD_USER_WARP:

		StartEffect(lpTransCommandEx->LParam, lpTransCommandEx->SParam, lpTransCommandEx->EParam, EFFECT_RETURN1);
		SkillPlaySound(SKILL_SOUND_LEARN, lpTransCommandEx->LParam, lpTransCommandEx->SParam, lpTransCommandEx->EParam);



		if (lpTransCommandEx->SxParam == lpCurPlayer->dwObjectSerial)
		{
			int iCode = 0;

			// Verifica o LxParam, se for TRUE é cristal
			if (lpTransCommandEx->LxParam == TRUE)
			{
				switch (lpTransCommandEx->WxParam)
				{
					// Verifica qual cristal é
				case sinGP1 | sin01:
					iCode = 1;
					break;
				case sinGP1 | sin02:
					iCode = 2;
					break;
				case sinGP1 | sin03:
					iCode = 3;
					break;
				case sinGP1 | sin04:
					iCode = 4;
					break;
				case sinGP1 | sin05:
					iCode = 5;
					break;
				case sinGP1 | sin06:
					iCode = 6;
					break;
				case sinGP1 | sin07:
					iCode = 7;
					break;
				case sinGP1 | sin08:
					iCode = 8;
					break;
				case sinGP1 | sin09:
					iCode = 9;
					break;
				case sinGP1 | sin10:
					iCode = 10;
					break;
				case sinGP1 | sin11:
					iCode = 11;
					break;
				case sinGP1 | sin12:
					iCode = 12;
					break;
				case sinGP1 | sin13:
					iCode = 13;
					break;
				case sinGP1 | sin14:
					iCode = 14;
					break;
				case sinGP1 | sin15:
					iCode = 15;
					break;
				case sinGP1 | sin16:
					iCode = 16;
					break;
				case sinGP1 | sin17:
					iCode = 17;
					break;
				case sinGP1 | sin18:
					iCode = 18;
					break;
				case sinGP1 | sin19:
					iCode = 19;
					break;
				case sinGP1 | sin20:
					iCode = 20;
					break;
				default:
					break;
				}


				// Criar o Buff
				sSKILL haCrystalTimer;
				for (int j = 0; j < SIN_MAX_SKILL; j++)
				{
					if (sSkill[j].CODE == iCode)
					{
						//nCristalInUse++;
						sSkill[j].SkillTaget_CODE = lpTransCommandEx->ExParam;
						memcpy(&haCrystalTimer, &sSkill[j], sizeof(sSKILL));
						haCrystalTimer.UseTime = 240; // 4 minutos //TEMPO DO CRISTAL
						haCrystalTimer.SkillTaget_CODE = lpTransCommandEx->ExParam;
						sinContinueSkillSet(&haCrystalTimer);
						break;
					}
				}
			}
		}

		break;


	case smCOMMNAD_USER_AGINGUP:

		lpChar = FindChrPlayer(lpTransCommandEx->WxParam);
		if (lpChar)
		{
			StartEffect(lpChar->pX, lpChar->pY, lpChar->pZ, EFFECT_AGING);
			esPlaySound(7, GetDistVolume(lpChar->pX, lpChar->pY, lpChar->pZ), 1600);
		}
		break;

	case smCOMMNAD_USER_HOLY_INCANTATION:
		lpChar = FindChrPlayer(lpTransCommandEx->LParam);
		if (lpChar)
		{
			AssaParticle_HolyIncantationPart(lpChar, lpTransCommandEx->SParam);
		}
		break;

	case smCOMMNAD_USER_RESURRECTION:
		lpChar = FindChrPlayer(lpTransCommandEx->LParam);
		if (lpChar)
		{
			AssaParticle_ResurrectionPart(lpChar);
		}
		break;

	case smCOMMNAD_USER_FORCEORB:

		lpChar = FindChrPlayer(lpTransCommandEx->WxParam);
		if (lpChar)
		{
			StartSkill(lpChar->pX, lpChar->pY, lpChar->pZ, 0, 0, 0, SKILL_UP1);
			SkillPlaySound(SKILL_SOUND_LEARN, lpChar->pX, lpChar->pY, lpChar->pZ);
		}
		break;

	case smCOMMNAD_USER_VALENTO:

		lpChar = FindChrPlayer(lpTransCommandEx->LParam);
		lpChar2 = FindChrPlayer(lpTransCommandEx->SParam);
		if (lpChar && lpChar2)
		{
			sinSkillEffect_Soul_Sucker(lpChar, lpChar2);
		}
		break;

	case smCOMMNAD_USER_FIREFLOWER:
		lpChar = FindChrPlayer(lpTransCommandEx->WxParam);
		if (lpChar && lpChar != lpCurPlayer)
		{
			DWORD	dwTable = GetTableNum(lpTransCommandEx->LParam);
			AddTimeEffect(SKILL_EFFECT_FIREFLOWER, dwPlayTime + 1000, (dwTable >> 24) & 0xFF, 0, 0, lpChar);
			AddTimeEffect(SKILL_EFFECT_FIREFLOWER, dwPlayTime + 1500, (dwTable >> 16) & 0xFF, 0, 0, lpChar);
			AddTimeEffect(SKILL_EFFECT_FIREFLOWER, dwPlayTime + 2000, (dwTable >> 8) & 0xFF, 0, 0, lpChar);
			AddTimeEffect(SKILL_EFFECT_FIREFLOWER, dwPlayTime + 2500, dwTable & 0xFF, 0, 0, lpChar);
		}
		break;

	}

	return TRUE;
}


int	SendCommandUser(int wParam, int lParam, int sParam, int eParam)
{
	smTRANS_COMMAND_EX	smTransCommandEx;

	smTransCommandEx.code = OpCode::OPCODE_COMMAND_USER;
	smTransCommandEx.size = sizeof(smTRANS_COMMAND_EX);
	smTransCommandEx.WParam = wParam;
	smTransCommandEx.LParam = lParam;
	smTransCommandEx.SParam = sParam;
	smTransCommandEx.EParam = eParam;

	smTransCommandEx.WxParam = lpCurPlayer->dwObjectSerial;
	smTransCommandEx.LxParam = 0;
	smTransCommandEx.SxParam = 0;
	smTransCommandEx.ExParam = 0;

	if (smWsockUserServer)
	{
		return smWsockUserServer->Send((char *)&smTransCommandEx, smTransCommandEx.size, TRUE);
	}
	return FALSE;
}


int	SendCommand_AreaServer(DWORD dwCode, int wParam, int lParam, int sParam, int eParam)
{
	smTRANS_COMMAND	smTransCommand;
	smWINSOCK	*lpsmSock;

	smTransCommand.code = dwCode;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = wParam;
	smTransCommand.LParam = lParam;
	smTransCommand.SParam = sParam;
	smTransCommand.EParam = eParam;

	lpsmSock = GetAreaServerSock();
	if (lpsmSock)
	{
		return lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
	}

	return FALSE;
}


int	SendCommand_DataServer(DWORD dwCode, int wParam, int lParam, int sParam, int eParam)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.code = dwCode;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = wParam;
	smTransCommand.LParam = lParam;
	smTransCommand.SParam = sParam;
	smTransCommand.EParam = eParam;

	if (smWsockDataServer)
	{
		return smWsockDataServer->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
	}

	return FALSE;
}

struct	sDAMAGE_RECORD
{
	int	Damage;
	int	Count;
};

sDAMAGE_RECORD	sRecvDamage[3];
sDAMAGE_RECORD	sSendDamage[3];



int	Init_RecordDamage()
{
	ZeroMemory(sRecvDamage, sizeof(sDAMAGE_RECORD) * 3);
	ZeroMemory(sSendDamage, sizeof(sDAMAGE_RECORD) * 3);

	return TRUE;
}


int	Record_RecvDamage(smWINSOCK *lpsmSock, int Damage)
{
	smTRANS_COMMAND	smTransCommand;

	if (smWsockServer == lpsmSock)
	{
		sRecvDamage[0].Damage -= Damage;
		sRecvDamage[0].Count--;

		if ((sRecvDamage[0].Count & 0x1FF) == 0)
		{
			smTransCommand.code = OpCode::OPCODE_REC_DAMAGEDATA;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = sRecvDamage[0].Count;
			smTransCommand.LParam = sRecvDamage[0].Damage;
			smTransCommand.SParam = sSendDamage[0].Count;
			smTransCommand.EParam = sSendDamage[0].Damage;
			if (lpsmSock) lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
		}
	}
	else if (smWsockUserServer == lpsmSock)
	{
		sRecvDamage[1].Damage -= Damage;
		sRecvDamage[1].Count--;

		if ((sRecvDamage[1].Count & 0x1FF) == 0)
		{
			smTransCommand.code = OpCode::OPCODE_REC_DAMAGEDATA;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = sRecvDamage[1].Count;
			smTransCommand.LParam = sRecvDamage[1].Damage;
			smTransCommand.SParam = sSendDamage[1].Count;
			smTransCommand.EParam = sSendDamage[1].Damage;
			if (lpsmSock) lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
		}

	}
	else if (smWsockExtendServer == lpsmSock)
	{
		sRecvDamage[2].Damage -= Damage;
		sRecvDamage[2].Count--;

		if ((sRecvDamage[2].Count & 0x1FF) == 0)
		{
			smTransCommand.code = OpCode::OPCODE_REC_DAMAGEDATA;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = sRecvDamage[2].Count;
			smTransCommand.LParam = sRecvDamage[2].Damage;
			smTransCommand.SParam = sSendDamage[2].Count;
			smTransCommand.EParam = sSendDamage[2].Damage;
			if (lpsmSock) lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
		}
	}

	return TRUE;
}


int	Record_SendDamage(smWINSOCK *lpsmSock, int Damage)
{
	smTRANS_COMMAND	smTransCommand;

	if (smWsockServer == lpsmSock)
	{
		sSendDamage[0].Damage -= Damage;
		sSendDamage[0].Count--;

		if ((sRecvDamage[0].Count & 0x1FF) == 0)
		{
			smTransCommand.code = OpCode::OPCODE_REC_DAMAGEDATA;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = sRecvDamage[0].Count;
			smTransCommand.LParam = sRecvDamage[0].Damage;
			smTransCommand.SParam = sSendDamage[0].Count;
			smTransCommand.EParam = sSendDamage[0].Damage;
			if (lpsmSock) lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
		}
	}
	else if (smWsockUserServer == lpsmSock)
	{
		sSendDamage[1].Damage -= Damage;
		sSendDamage[1].Count--;

		if ((sRecvDamage[1].Count & 0x1FF) == 0)
		{
			smTransCommand.code = OpCode::OPCODE_REC_DAMAGEDATA;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = sRecvDamage[1].Count;
			smTransCommand.LParam = sRecvDamage[1].Damage;
			smTransCommand.SParam = sSendDamage[1].Count;
			smTransCommand.EParam = sSendDamage[1].Damage;
			if (lpsmSock) lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
		}

	}
	else if (smWsockExtendServer == lpsmSock)
	{
		sSendDamage[2].Damage -= Damage;
		sSendDamage[2].Count--;

		if ((sRecvDamage[2].Count & 0x1FF) == 0)
		{
			smTransCommand.code = OpCode::OPCODE_REC_DAMAGEDATA;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = sRecvDamage[2].Count;
			smTransCommand.LParam = sRecvDamage[2].Damage;
			smTransCommand.SParam = sSendDamage[2].Count;
			smTransCommand.EParam = sSendDamage[2].Damage;
			if (lpsmSock) lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
		}
	}

	return TRUE;
}


int	SendPartySkillToServer(DWORD dwSkillCode, int SkillLevel, int Around, int wParam, int lParam, int sParam, int eParam)
{
	int x, y, z, dist;
	int cnt;
	int PartyCount;
	TRANS_PARTY_SKILL	TransPartySkill;
	smWINSOCK	*lpsmSock;

	TransPartySkill.code = OpCode::OPCODE_PARTY_SKILL;
	TransPartySkill.dwSkillCode = dwSkillCode;
	TransPartySkill.wParam = wParam;
	TransPartySkill.lParam = lParam;
	TransPartySkill.sParam = sParam;
	TransPartySkill.eParam = eParam;

	PartyCount = 0;

	TransPartySkill.dwPartyUser[PartyCount++] = lpCurPlayer->dwObjectSerial;

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].dwObjectSerial && chrOtherPlayer[cnt].PartyFlag)
		{
			x = (lpCurPlayer->pX - chrOtherPlayer[cnt].pX) >> FLOATNS;
			y = (lpCurPlayer->pY - chrOtherPlayer[cnt].pY) >> FLOATNS;
			z = (lpCurPlayer->pZ - chrOtherPlayer[cnt].pZ) >> FLOATNS;
			dist = x * x + y * y + z * z;
			if (dist < (Around*Around))
			{
				TransPartySkill.dwPartyUser[PartyCount++] = chrOtherPlayer[cnt].dwObjectSerial;
			}
		}
	}

	TransPartySkill.PartyCount = PartyCount;
	TransPartySkill.Point = SkillLevel;
	TransPartySkill.size = sizeof(TRANS_PARTY_SKILL) - (8 - PartyCount) * 4;

	lpsmSock = GetAreaServerSock();
	if (lpsmSock) lpsmSock->Send((char *)&TransPartySkill, TransPartySkill.size, TRUE);

	return TRUE;
}


int SendCancelSkillToServer(DWORD dwSkillCode, int lParam, int sParam, int eParam)
{
	smWINSOCK	*lpsmSock;
	smTRANS_COMMAND smTransCommand;

	smTransCommand.code = OpCode::OPCODE_CANCEL_SKILL;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = dwSkillCode;
	smTransCommand.LParam = lParam;
	smTransCommand.SParam = sParam;
	smTransCommand.EParam = eParam;

	lpsmSock = GetAreaServerSock();
	if (lpsmSock) lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

	return TRUE;
}


int SendUpdateSkillToServer(DWORD dwSkillCode, int lParam, int sParam, int eParam)
{
	smWINSOCK	*lpsmSock;
	smTRANS_COMMAND smTransCommand;

	smTransCommand.code = OpCode::OPCODE_UPDATEL_SKILL;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = dwSkillCode;
	smTransCommand.LParam = lParam;
	smTransCommand.SParam = sParam;
	smTransCommand.EParam = eParam;

	lpsmSock = GetAreaServerSock();
	if (lpsmSock) lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

	return TRUE;
}


int SendProcessSKillToServer(DWORD dwSkillCode, int point, int Param1, int Param2)
{

	smWINSOCK	*lpsmSock;
	smTRANS_COMMAND smTransCommand;

	smTransCommand.code = OpCode::OPCODE_PROCESS_SKILL2;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = dwSkillCode | (point << 8);
	smTransCommand.LParam = lpCurPlayer->dwObjectSerial;
	smTransCommand.SParam = Param1;
	smTransCommand.EParam = Param2;

	smTransCommand.LParam = dm_GetCommandChkSum(&smTransCommand, lpCurPlayer->dwObjectSerial);

#ifdef _USE_DYNAMIC_ENCODE
	if (fnEncodeDamagePacket)
	{
		fnEncodeDamagePacket(&smTransCommand);

		lpsmSock = GetAreaServerSock();
		if (lpsmSock)
			lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
	}
#else
	dm_EncodePacket(&smTransCommand);

	lpsmSock = GetAreaServerSock();
	if (lpsmSock)
		lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
#endif

	return TRUE;


}


int RecvPartySkillFromServer(TRANS_PARTY_SKILL *lpTransPartySkill)
{
	int cnt, cnt2, cnt3;
	int time;
	int flag;


	switch (lpTransPartySkill->dwSkillCode)
	{

	case SKILL_PLAY_ALAS:

		if (lpTransPartySkill->Point < 1 || lpTransPartySkill->Point>10) break;
		time = Alas_Time[lpTransPartySkill->Point - 1];
		for (cnt = 1; cnt < lpTransPartySkill->PartyCount; cnt++)
		{
			if (lpCurPlayer->dwObjectSerial == lpTransPartySkill->dwPartyUser[cnt])
			{
				flag = 0;

				for (cnt3 = 0; cnt3 < 10; cnt3++)
				{
					if (ContinueSkill[cnt].Flag)
					{
						
						
							
						
					}
				}
				if (flag)
				{
					SendCancelSkillToServer(lpTransPartySkill->dwSkillCode, 0, 0, 0);
				}
				else
				{
					AssaParticle_KeepSkillEffect("Alas", lpCurPlayer, time, SKILL_ALAS);
					sSKILL sSkill;
					ZeroMemory(&sSkill, sizeof(sSKILL));
					sSkill.CODE = SKILL_ALAS;
					sSkill.UseTime = time;
					sSkill.Flag = TRUE;
					sSkill.Point = lpTransPartySkill->Point;
					sinContinueSkillSet(&sSkill);
				}
			}
			else
			{
				for (cnt2 = 0; cnt2 < OTHER_PLAYER_MAX; cnt2++)
				{
					if (chrOtherPlayer[cnt2].Flag &&
						chrOtherPlayer[cnt2].dwObjectSerial == lpTransPartySkill->dwPartyUser[cnt])
					{
						AssaParticle_KeepSkillEffect("Alas", &chrOtherPlayer[cnt2], time, SKILL_ALAS);
					}
				}
			}
		}
		break;

	case SKILL_PLAY_HOLY_VALOR:

		if (lpTransPartySkill->Point < 1 || lpTransPartySkill->Point>10) break;

		time = Holy_Valor_Time[lpTransPartySkill->Point - 1];
		for (cnt = 1; cnt < lpTransPartySkill->PartyCount; cnt++)
		{
			if (lpCurPlayer->dwObjectSerial == lpTransPartySkill->dwPartyUser[cnt])
			{

				flag = 0;

				for (cnt3 = 0; cnt3 < 10; cnt3++)
				{
					if (ContinueSkill[cnt].Flag)
					{
						if (ContinueSkill[cnt].CODE == SKILL_DRASTIC_SPIRIT || ContinueSkill[cnt].CODE == SKILL_HOLY_BODY)
						{
							flag++;
						}
					}
				}

				if (flag)
				{




					SendCancelSkillToServer(lpTransPartySkill->dwSkillCode, 0, 0, 0);
				}
				else
				{

					AssaParticle_HolyValor_Member(lpCurPlayer, time);
					sSKILL sSkill;

					ZeroMemory(&sSkill, sizeof(sSKILL));
					sSkill.CODE = SKILL_HOLY_VALOR;
					sSkill.UseTime = time;
					sSkill.Flag = TRUE;
					sSkill.Point = lpTransPartySkill->Point;
					sinContinueSkillSet(&sSkill);
				}
			}
			else
			{
				for (cnt2 = 0; cnt2 < OTHER_PLAYER_MAX; cnt2++)
				{
					if (chrOtherPlayer[cnt2].Flag &&
						chrOtherPlayer[cnt2].dwObjectSerial == lpTransPartySkill->dwPartyUser[cnt])
					{
						AssaParticle_HolyValor_Member(&chrOtherPlayer[cnt2], time);
					}
				}
			}
		}
		break;


	case SKILL_PLAY_EXTINCTION:

		for (cnt = 0; cnt < lpTransPartySkill->PartyCount; cnt++)
		{
			for (cnt2 = 0; cnt2 < OTHER_PLAYER_MAX; cnt2++)
			{
				if (chrOtherPlayer[cnt2].Flag &&
					chrOtherPlayer[cnt2].dwObjectSerial == lpTransPartySkill->dwPartyUser[cnt])
				{
					AssaParticle_Extinction(&chrOtherPlayer[cnt2]);
					SkillPlaySound(SKILL_SOUND_SKILL_EXTINTION, chrOtherPlayer[cnt2].pX, chrOtherPlayer[cnt2].pY, chrOtherPlayer[cnt2].pZ);
				}
			}
		}
		break;

	}


	return TRUE;
}

DWORD	dwLastClanUserCode = 0;


int SendClanJoinService(DWORD dwMsgCode, smCHAR *lpChar)
{
	smTRANS_CHAR_COMMAND2	smTransCharCommand;

#ifdef  __CLANSUBCHIP__
	if (cldata.myPosition != 101 && cldata.myPosition != 104) return FALSE;
#else
	if (cldata.myPosition != 101) return FALSE;
#endif

	smTransCharCommand.code = OpCode::OPCODE_CLAN_SERVICE;
	smTransCharCommand.size = sizeof(smTRANS_CHAR_COMMAND2);
	smTransCharCommand.WParam = dwMsgCode;
	smTransCharCommand.LParam = lpChar->dwObjectSerial;
	smTransCharCommand.SParam = lpCurPlayer->dwObjectSerial;
	strcpy_s(smTransCharCommand.szName, cldata.name);
	strcpy_s(smTransCharCommand.szId, UserAccount);

	if (smWsockUserServer)
		smWsockUserServer->Send((char *)&smTransCharCommand, smTransCharCommand.size, TRUE);

	return TRUE;
}


int SendJoinClan()
{
	smTRANS_CHAR_COMMAND2	smTransCharCommand;

	if (!dwLastClanUserCode) return FALSE;

	smTransCharCommand.code = OpCode::OPCODE_CLAN_SERVICE;
	smTransCharCommand.size = sizeof(smTRANS_CHAR_COMMAND2);
	smTransCharCommand.WParam = 2;
	smTransCharCommand.LParam = dwLastClanUserCode;
	smTransCharCommand.SParam = lpCurPlayer->dwObjectSerial;
	strcpy_s(smTransCharCommand.szName, lpCurPlayer->smCharInfo.szName);
	strcpy_s(smTransCharCommand.szId, UserAccount);

	if (smWsockUserServer)
		smWsockUserServer->Send((char *)&smTransCharCommand, smTransCharCommand.size, TRUE);

	return TRUE;
}


int RecvClanJoinService(smTRANS_CHAR_COMMAND2 *lpTransCharCommand)
{
	smCHAR *lpChar;

	switch (lpTransCharCommand->WParam)
	{
	case 1:
		if (cldata.myPosition == 102 || cldata.myPosition == 103)
		{

			lpChar = FindAutoPlayer(lpTransCharCommand->SParam);
			if (lpChar)
			{
				ClanJoin(lpTransCharCommand->szName, lpChar->smCharInfo.szName);
				OpenEachPlayer(lpChar);
				DispEachMode = TRUE;
				dwLastClanUserCode = lpTransCharCommand->SParam;
			}
		}
		break;

	case 2:
#ifdef  __CLANSUBCHIP__
		if (cldata.myPosition == 101 || cldata.myPosition == 104)
		{
#else
		if (cldata.myPosition == 101)
		{
#endif
			lpChar = FindAutoPlayer(lpTransCharCommand->SParam);
			if (lpChar)
				menu_joinOpen_Chip(1, lpTransCharCommand->szId, lpTransCharCommand->szName, lpChar->smCharInfo.JOB_CODE, lpChar->smCharInfo.Level);
			else
				menu_joinOpen_Chip(1, lpTransCharCommand->szId, lpTransCharCommand->szName, 0, 0);
		}
		break;
	}

	return TRUE;
}




DWORD	dwSkill_DivineLightning_Target[8];
int		DivineLightning_Target_Count = 0;
int		DivineLightning_FindCount = 0;


int	SkillPlay_DivineLightning_Select(smCHAR *lpChar, int SkillPoint)
{
	int cnt, TargetCount;
	int x, y, z, dist;
	int	LightningCount;
	int cCount;
	TRANS_SKIL_ATTACKDATA	TransSkilAttackData;
	smWINSOCK *lpsmSendSock = 0;


	Record_ClinetLogFile("±¸¹öÀü °ø°ÝÆÐÅ¶ - SkillPlay_DivineLightning_Select ");
	quit = 1;
	return TRUE;

	if (lpChar != lpCurPlayer) return FALSE;

	TargetCount = 0;

	LightningCount = Divine_Lightning_Num[SkillPoint - 1];

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{

		cCount = (DivineLightning_FindCount + cnt)&OTHER_PLAYER_MASK;

		if (chrOtherPlayer[cCount].Flag && chrOtherPlayer[cCount].dwObjectSerial &&
			lpChar != &chrOtherPlayer[cCount] && chrOtherPlayer[cCount].smCharInfo.State == smCHAR_STATE_ENEMY &&
			chrOtherPlayer[cCount].smCharInfo.Brood != smCHAR_MONSTER_USER &&
			chrOtherPlayer[cCount].smCharInfo.Life[0] > 0)
		{

			x = (lpChar->pX - chrOtherPlayer[cCount].pX) >> FLOATNS;
			y = (lpChar->pY - chrOtherPlayer[cCount].pY) >> FLOATNS;
			z = (lpChar->pZ - chrOtherPlayer[cCount].pZ) >> FLOATNS;

			dist = x * x + y * y + z * z;

			if (dist < (160 * 160))
			{
				dwSkill_DivineLightning_Target[TargetCount] = chrOtherPlayer[cCount].dwObjectSerial;
				TransSkilAttackData.dwTarObjectSerial[TargetCount] = chrOtherPlayer[cCount].dwObjectSerial;
				TargetCount++;

				if (chrOtherPlayer[cCount].smCharInfo.Life[1] && chrOtherPlayer[cCount].smCharInfo.Life[0] == chrOtherPlayer[cCount].smCharInfo.Life[1])
				{
					chrOtherPlayer[cCount].EnableStateBar = TRUE;
				}
				if (TargetCount >= LightningCount)
				{
					DivineLightning_FindCount = cCount;
					break;
				}
			}
		}
	}

	TransSkilAttackData.TargetCount = TargetCount;
	DivineLightning_Target_Count = TargetCount;

	TransSkilAttackData.code = OpCode::OPCODE_SKIL_ATTACKDATA;
	TransSkilAttackData.size = (sizeof(TRANS_SKIL_ATTACKDATA) - sizeof(DWORD)*SKIL_ATTACK_CHAR_MAX);
	TransSkilAttackData.size += sizeof(DWORD)*TargetCount + 16;

	TransSkilAttackData.x = lpChar->pX;
	TransSkilAttackData.y = lpChar->pY;
	TransSkilAttackData.z = lpChar->pZ;

	TransSkilAttackData.AttackState = 103;
	TransSkilAttackData.AttackSize = 160 * 160;
	TransSkilAttackData.Power = Divine_Lightning_Damage[SkillPoint - 1];

	lpsmSendSock = GetAreaServerSock();

	if (lpsmSendSock && TargetCount > 0)
	{

		Record_SendDamage(lpsmSendSock, TransSkilAttackData.Power);

		lpsmSendSock->Send((char *)&TransSkilAttackData, TransSkilAttackData.size, TRUE);
	}

	return TRUE;
}


int SkillPlay_DivineLightning_Effect(smCHAR *lpChar, int SkillPoint)
{
	int cnt, TargetCount;
	int x, y, z, dist;
	int	LightningCount;
	int cCount;
	smCHAR *lpTarChar;

	TargetCount = 0;

	if (lpChar == lpCurPlayer)
	{
		for (cnt = 0; cnt < DivineLightning_Target_Count; cnt++)
		{
			lpTarChar = FindAutoPlayer(dwSkill_DivineLightning_Target[cnt]);
			if (lpTarChar)
			{
				AssaParticle_DivineLighting(lpTarChar);
				TargetCount++;
			}
		}
	}
	else
	{
		LightningCount = Divine_Lightning_Num[SkillPoint - 1];

		for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
		{
			cCount = (DivineLightning_FindCount + cnt)&OTHER_PLAYER_MASK;
			if (chrOtherPlayer[cCount].Flag && chrOtherPlayer[cCount].dwObjectSerial &&
				lpChar != &chrOtherPlayer[cCount] && chrOtherPlayer[cCount].smCharInfo.State == smCHAR_STATE_ENEMY &&
				chrOtherPlayer[cCount].smCharInfo.Brood != smCHAR_MONSTER_USER &&
				chrOtherPlayer[cCount].smCharInfo.Life[0] > 0)
			{

				x = (lpChar->pX - chrOtherPlayer[cCount].pX) >> FLOATNS;
				y = (lpChar->pY - chrOtherPlayer[cCount].pY) >> FLOATNS;
				z = (lpChar->pZ - chrOtherPlayer[cCount].pZ) >> FLOATNS;

				dist = x * x + y * y + z * z;

				if (dist < (160 * 160))
				{
					AssaParticle_DivineLighting(&chrOtherPlayer[cCount]);
					TargetCount++;
					if (TargetCount >= LightningCount)
					{
						DivineLightning_FindCount = cCount;
						break;
					}
				}
			}
		}

		if (TargetCount < LightningCount && lpChar->smCharInfo.State == smCHAR_STATE_ENEMY)
		{
			x = (lpChar->pX - lpCurPlayer->pX) >> FLOATNS;
			y = (lpChar->pY - lpCurPlayer->pY) >> FLOATNS;
			z = (lpChar->pZ - lpCurPlayer->pZ) >> FLOATNS;

			dist = x * x + y * y + z * z;

			if (dist < (160 * 160))
			{
				AssaParticle_DivineLighting(lpCurPlayer);
				TargetCount++;
			}
		}

	}


	return TargetCount;
}



int SkillPlay_MummyLord_Effect(smCHAR *lpChar, int Range)
{
	int cnt, TargetCount;
	int x, y, z, dist;
	int	dRange = Range * Range;

	TargetCount = 0;

	if (lpChar->smCharInfo.Brood != smCHAR_MONSTER_USER)
	{

		for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
		{
			if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].dwObjectSerial &&
				lpChar != &chrOtherPlayer[cnt] && chrOtherPlayer[cnt].smCharInfo.State == smCHAR_STATE_USER &&
				chrOtherPlayer[cnt].smCharInfo.Life[0] > 0)
			{

				x = (lpChar->pX - chrOtherPlayer[cnt].pX) >> FLOATNS;
				y = (lpChar->pY - chrOtherPlayer[cnt].pY) >> FLOATNS;
				z = (lpChar->pZ - chrOtherPlayer[cnt].pZ) >> FLOATNS;

				dist = x * x + y * y + z * z;

				if (dist < dRange)
				{
					ParkAssaParticle_DivineLighting(&chrOtherPlayer[cnt]);
					TargetCount++;
				}

			}

		}

		if (lpChar->smCharInfo.State == smCHAR_STATE_ENEMY)
		{
			x = (lpChar->pX - lpCurPlayer->pX) >> FLOATNS;
			y = (lpChar->pY - lpCurPlayer->pY) >> FLOATNS;
			z = (lpChar->pZ - lpCurPlayer->pZ) >> FLOATNS;

			dist = x * x + y * y + z * z;

			if (dist < dRange)
			{
				ParkAssaParticle_DivineLighting(lpCurPlayer);
				TargetCount++;
			}
		}
	}
	else
	{

		for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
		{
			if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].dwObjectSerial &&
				lpChar != &chrOtherPlayer[cnt] && chrOtherPlayer[cnt].smCharInfo.State == smCHAR_STATE_ENEMY &&
				chrOtherPlayer[cnt].smCharInfo.Life[0] > 0)
			{

				x = (lpChar->pX - chrOtherPlayer[cnt].pX) >> FLOATNS;
				y = (lpChar->pY - chrOtherPlayer[cnt].pY) >> FLOATNS;
				z = (lpChar->pZ - chrOtherPlayer[cnt].pZ) >> FLOATNS;

				dist = x * x + y * y + z * z;

				if (dist < dRange)
				{
					ParkAssaParticle_DivineLighting(&chrOtherPlayer[cnt]);
					TargetCount++;
				}

			}
		}
	}


	return TargetCount;
}



int SkillPlay_VenomSpear_Effect(smCHAR *lpChar, int SkillPoint)
{
	int cnt, TargetCount;
	int x, y, z, dist;
	int	LightningCount;
	int cCount;
	smCHAR *lpTarChar;
	int range;

	range = VenomSpear_Range[SkillPoint - 1];
	range *= range;

	TargetCount = 0;

	if (lpChar == lpCurPlayer)
	{
		for (cnt = 0; cnt < DivineLightning_Target_Count; cnt++)
		{
			lpTarChar = FindAutoPlayer(dwSkill_DivineLightning_Target[cnt]);
			if (lpTarChar)
			{
				AssaParticle_VeonmSpear(lpTarChar);
				TargetCount++;
			}
		}
	}
	else
	{
		LightningCount = Divine_Lightning_Num[SkillPoint - 1];

		for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
		{
			cCount = (DivineLightning_FindCount + cnt)&OTHER_PLAYER_MASK;
			if (chrOtherPlayer[cCount].Flag && chrOtherPlayer[cCount].dwObjectSerial &&
				lpChar != &chrOtherPlayer[cCount] && chrOtherPlayer[cCount].smCharInfo.State == smCHAR_STATE_ENEMY &&
				chrOtherPlayer[cCount].smCharInfo.Brood != smCHAR_MONSTER_USER &&
				chrOtherPlayer[cCount].smCharInfo.Life[0] > 0)
			{

				x = (lpChar->pX - chrOtherPlayer[cCount].pX) >> FLOATNS;
				y = (lpChar->pY - chrOtherPlayer[cCount].pY) >> FLOATNS;
				z = (lpChar->pZ - chrOtherPlayer[cCount].pZ) >> FLOATNS;

				dist = x * x + y * y + z * z;

				if (dist < range)
				{
					AssaParticle_VeonmSpear(&chrOtherPlayer[cCount]);
					TargetCount++;
					if (TargetCount >= LightningCount)
					{
						DivineLightning_FindCount = cCount;
						break;
					}
				}
			}
		}
	}


	return TargetCount;
}


int SkillPlay_Monster_Effect(smCHAR *lpChar, int EffectKind, int Range)
{
	int cnt, TargetCount;
	int x, y, z, dist;
	int dDist = Range * Range;


	TargetCount = 0;

	x = (lpChar->pX - lpCurPlayer->pX) >> FLOATNS;
	y = (lpChar->pY - lpCurPlayer->pY) >> FLOATNS;
	z = (lpChar->pZ - lpCurPlayer->pZ) >> FLOATNS;

	dist = x * x + y * y + z * z;

	if (dist < dDist)
	{
		ParkAssaParticle_ChaosKaraSkill_User(lpCurPlayer);
		TargetCount++;
	}


	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].dwObjectSerial &&
			lpChar != &chrOtherPlayer[cnt] && chrOtherPlayer[cnt].smCharInfo.State == smCHAR_STATE_USER &&
			chrOtherPlayer[cnt].smCharInfo.Life[0] > 0)
		{
			x = (lpChar->pX - chrOtherPlayer[cnt].pX) >> FLOATNS;
			y = (lpChar->pY - chrOtherPlayer[cnt].pY) >> FLOATNS;
			z = (lpChar->pZ - chrOtherPlayer[cnt].pZ) >> FLOATNS;

			dist = x * x + y * y + z * z;

			if (dist < dDist)
			{
				ParkAssaParticle_ChaosKaraSkill_User(&chrOtherPlayer[cnt]);
				TargetCount++;
			}
		}
	}

	return TargetCount;
}





int RecvProcessSkill(smTRANS_COMMAND *lpTransCommand)
{
	int cnt;
	int dwSkillCode, point;
	smCHAR	*lpChar, *lpChar2;
	POINT3D	Pos1, Pos2;

	dwSkillCode = lpTransCommand->WParam & 0xFF;
	point = (lpTransCommand->WParam >> 8) & 0xF;

	switch (dwSkillCode)
	{
	case SKILL_PLAY_HOLY_REFLECTION:

		sinSkillEffect_Holy_Reflection_Defense(lpCurPlayer);
		break;

	case SKILL_PLAY_ENCHANT_WEAPON:

		cnt = Enchant_Weapon_Time[point - 1];
		lpCurPlayer->EnchantEffect_Point = point;

		cSkill.SetEnchant_Weapon(cnt, point);

		switch (lpTransCommand->EParam)
		{
		case 0:
			AssaParticle_EnchantWeaponIceJang(lpCurPlayer, cnt);
			lpCurPlayer->WeaponEffect = sITEMINFO_ICE + 1;
			lpCurPlayer->dwWeaponEffectTime = dwPlayTime + cnt * 1000;
			break;
		case 1:
			AssaParticle_EnchantWeaponLightJang(lpCurPlayer, cnt);
			lpCurPlayer->WeaponEffect = sITEMINFO_LIGHTING + 1;
			lpCurPlayer->dwWeaponEffectTime = dwPlayTime + cnt * 1000;
			break;
		case 2:
			AssaParticle_EnchantWeaponFireJang(lpCurPlayer, cnt);
			lpCurPlayer->WeaponEffect = sITEMINFO_FIRE + 1;
			lpCurPlayer->dwWeaponEffectTime = dwPlayTime + cnt * 1000;
			break;
		}
		break;

	case SKILL_PLAY_RESURRECTION:

		if (lpCurPlayer->MotionInfo && lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_DEAD)
		{
			SendProcessSKillToServer(SKILL_PLAY_RESURRECTION, point, 0, 0);

			lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_RESTART);
			StartEffect(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, EFFECT_GAME_START1);
			SetDynLight(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 100, 100, 100, 0, 200);
			CharPlaySound(lpCurPlayer);

			sinSetLife(lpCurPlayer->smCharInfo.Life[1] / 2);
			ResetEnergyGraph(4);
			lpCurPlayer->MoveFlag = FALSE;
			RestartPlayCount = 350;
			ReStartFlag = 0;
		}
		break;

	case SKILL_PLAY_VIRTUAL_LIFE:

		cSkill.SetVirtualLife(Virtual_Life_Time[point - 1], point);
		AssaParticle_VirtualLife(lpCurPlayer, Virtual_Life_Time[point - 1]);
		break;

	case SKILL_PLAY_LOVELY_LIFE:

		if (lpTransCommand->LParam == lpCurPlayer->dwObjectSerial)
		{
			cSkill.SetVirtualLife(Virtual_Life_Time[point - 1], point);
			AssaParticle_VirtualLife(lpCurPlayer, Virtual_Life_Time[point - 1]);
			SkillPlaySound(SKILL_SOUND_SKILL_VIRTUAL_LIFE, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
		}
		else
		{
			lpChar = FindChrPlayer(lpTransCommand->LParam);
			if (lpChar)
			{
				AssaParticle_VirtualLife(lpChar, Virtual_Life_Time[point - 1]);
				SkillPlaySound(SKILL_SOUND_SKILL_VIRTUAL_LIFE, lpChar->pX, lpChar->pY, lpChar->pZ);
			}
		}
		break;

	case SKILL_PLAY_VANISH:

		lpCurPlayer->PlayVanish = 0;
		cSkill.CancelContinueSkill(SKILL_VANISH);

		if (dwM_BlurTime) dwM_BlurTime = dwPlayTime;
		break;

	case SKILL_PLAY_TRIUMPH_OF_VALHALLA:

		cSkill.SetT_Of_Valhalla(point, lpTransCommand->EParam);
		AssaParticle_TriumphOfValhalla(lpCurPlayer, T_Of_Valhalla_Time[point - 1]);
		break;

	case SKILL_PLAY_SPARK_SHIELD:



		lpChar = FindChrPlayer(lpTransCommand->LParam);
		lpChar2 = FindChrPlayer(lpTransCommand->SParam);
		if (lpChar && lpChar2)
		{

			if (lpChar->HvLeftHand.PatTool)
			{
				if (lpChar->GetToolBipPoint(&lpChar->HvLeftHand, &Pos1.x, &Pos1.y, &Pos1.z))
				{

					Pos2.x = lpChar2->pX;
					Pos2.y = lpChar2->pY + 24 * fONE;
					Pos2.z = lpChar2->pZ;

					AssaParticle_SparkShieldDefence(&Pos1, &Pos2);
					SkillPlaySound(SKILL_SOUND_SKILL_SPARK2, lpChar->pX, lpChar->pY, lpChar->pZ);
				}
			}
		}
		break;

	case SKILL_PLAY_HALL_OF_VALHALLA:

		cSkill.HellOfValhalla(Hall_Of_Valhalla_Time[point - 1], point, lpTransCommand->SParam, lpTransCommand->EParam, 1);
		SkillValhallaHallOfValhallaHandEffect(lpCurPlayer, (float)lpTransCommand->EParam);
		lpCurPlayer->dwHallOfValhallaTime = dwPlayTime + Hall_Of_Valhalla_Time[point - 1] * 1000;
		break;

	case SKILL_PLAY_FORCE_OF_NATURE:

		cSkill.ForeceOfNature(Force_Of_Nature_Time[point - 1], point, 1);
		SkillSagittarionForceOfNature1(lpCurPlayer, (float)Force_Of_Nature_Time[point - 1]);
		lpCurPlayer->dwForceOfNatureTime = dwPlayTime + Force_Of_Nature_Time[point - 1] * 1000;
		break;


	case SKILL_PLAY_SOD_ITEM:


		switch (lpTransCommand->SParam)
		{
		case 1:
			SetBellatraFontEffect(E_BL_QUAKE_SEAL);
			SetBellatraFontEffect(E_BL_FONT_QUAKE_SEAL);
			EffectWaveCamera(50, 3);
			SkillPlaySound(SKILL_SOUND_SKILL_DIASTROPHISM, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
			break;

		case 2:
			SetBellatraFontEffect(E_BL_STUN_SEAL);
			SetBellatraFontEffect(E_BL_FONT_STUN_SEAL);
			EffectWaveCamera(50, 3);
			SkillPlaySound(SKILL_SOUND_SKILL_DIASTROPHISM, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
			break;

		case 3:
			SetBellatraFontEffect(E_BL_FREEZE_SEAL);
			SetBellatraFontEffect(E_BL_FONT_FREEZE_SEAL);
			EffectWaveCamera(50, 3);
			SkillPlaySound(SKILL_SOUND_SKILL_DIASTROPHISM, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
			break;

		case 4:
			SetBellatraFontEffect(E_BL_RABBIE_SEAL);
			SetBellatraFontEffect(E_BL_FONT_RABBIE_SEAL);
			EffectWaveCamera(50, 3);
			SkillPlaySound(SKILL_SOUND_SKILL_DIASTROPHISM, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
			break;

		case 5:
			SetBellatraFontEffect(E_BL_STYGIAN_SEAL);
			SetBellatraFontEffect(E_BL_FONT_STYGIAN_SEAL);
			break;

		case 6:
			SetBellatraFontEffect(E_BL_GUARDIAN_SEAL);
			SetBellatraFontEffect(E_BL_FONT_GUARDIAN_SEAL);
			break;

		case 7:
			SetBellatraFontEffect(E_BL_POINT_SEAL);
			SetBellatraFontEffect(E_BL_FONT_POINT_SEAL);
			break;
		}
		esPlaySound(19, 360);
		break;

	case SKILL_PLAY_HEALING:

		lpChar = FindChrPlayer(lpTransCommand->LParam);
		if (lpChar)
		{
			sinEffect_Healing2(lpChar);
			SkillPlaySound(SKILL_SOUND_SKILL_HEALING, lpChar->pX, lpChar->pY, lpChar->pZ);
		}
		break;

	case SKILL_PLAY_BLESS_SIEGE_ITEM:


		switch (lpTransCommand->SParam)
		{
		case (sinBC1 | sin01):

			lpCurPlayer->PlayInvincible = 70 * 30;
			break;
		case (sinBC1 | sin02):

			break;
		case (sinBC1 | sin03):

			break;

		case (sinBC1 | sin05):

			lpCurPlayer->PlayInvincible = 70 * 3;
			break;

		case (sinBC1 | sin06):

			break;
		case (sinBC1 | sin07):

			break;
		case (sinBC1 | sin08):

			break;
		case (sinBC1 | sin09):

			break;
		case (sinBC1 | sin10):

			break;
		case (sinBC1 | sin11):

			break;
		case (sinBC1 | sin12):

			break;
		case (sinBC1 | sin13):

			break;
		case (sinBC1 | sin14):

			break;
		case (sinBC1 | sin15):

			break;
		case (sinBC1 | sin16):

			break;
		}
		break;

	}

	return TRUE;
}
















int SendClanCommandUser(smWINSOCK *lpsmSock, DWORD	dwCode, int Param1, int Param2, CLANWONLIST *lpClanUserList, int ClanUserCount)
{

	TRANS_CLAN_COMMAND_USER	TransClanUser;
	int	cnt, len;
	DWORD	dwSpeedSum;
	int	BuffSize;

	TransClanUser.code = dwCode;

	TransClanUser.Param[0] = Param1;
	TransClanUser.Param[1] = Param2;
	TransClanUser.Param[2] = 0;
	TransClanUser.Param[3] = 0;
	TransClanUser.UserCount = ClanUserCount;

	char *lpBuff = TransClanUser.szUserBuff;

	for (cnt = 0; cnt < ClanUserCount; cnt++)
	{
		dwSpeedSum = GetSpeedSum(lpClanUserList->clanWon[cnt]);

		((DWORD *)lpBuff)[0] = dwSpeedSum;

		lpBuff += sizeof(DWORD);

		strcpy_s(lpBuff, sizeof(TransClanUser.szUserBuff), lpClanUserList->clanWon[cnt]);
		len = lstrlen(lpClanUserList->clanWon[cnt]);
		lpBuff += len + 1;
	}

	BuffSize = lpBuff - TransClanUser.szUserBuff;
	BuffSize += 16;

	TransClanUser.size = 32 + BuffSize;

	if (lpsmSock && ClanUserCount > 0)
	{
		lpsmSock->Send((char *)&TransClanUser, TransClanUser.size, TRUE);
	}

	return TRUE;
}


int	RecvClanCommand(TRANS_CLAN_COMMAND_USER *lpTransClanUser, _CLAN_USER_INFO *ClanUserInfo)
{
	int cnt;
	int cnt2;
	char *lpBuff;
	char	ch;

	lpBuff = lpTransClanUser->szUserBuff;

	if (lpTransClanUser->UserCount >= CLAN_USER_MAX) return FALSE;

	for (cnt = 0; cnt < lpTransClanUser->UserCount; cnt++)
	{
		ClanUserInfo[cnt].dwSpeedSum = ((DWORD *)lpBuff)[0];
		lpBuff += sizeof(DWORD);
		for (cnt2 = 0; cnt2 < 32; cnt2++)
		{
			ch = *lpBuff;
			ClanUserInfo[cnt].szName[cnt2] = ch;
			lpBuff++;
			if (!ch) break;
		}
		ClanUserInfo[cnt].szName[31] = 0;
	}

	return TRUE;
}


int FiltQuestItem(TRANS_ITEMINFO	*lpTransItemInfo, DWORD dwPacketCode)
{
	int cnt;

	if (chaQuest.sHaQuestElementary[6].CODE != HAQUEST_CODE_ELEMENTARY_G)
	{

		cnt = cInvenTory.SearchItemCode(sinQT1 | sin16);
		if (cnt >= 1)
		{
			DeleteQuestItem(sinQT1 | sin16);
		}
		if (lpTransItemInfo->Item.CODE == (sinQT1 | sin16))
		{
			return FALSE;
		}

	}

	switch (sinQuest_ChangeJob2.CODE)
	{
	case SIN_QUEST_CODE_CHANGEJOB2_NPC_M:

		if (lpTransItemInfo->Item.CODE == (sinMA2 | sin01))
		{
			if (!cInvenTory.SearchItemCode(sinMA1 | sin01)) return FALSE;
			if (cInvenTory.SearchItemCode(sinQT1 | sin04)) return FALSE;
			cnt = cInvenTory.SearchItemCode(sinMA2 | sin01);
			if (cnt >= 9) return FALSE;
		}
		if (lpTransItemInfo->Item.CODE == (sinMA2 | sin02)) return FALSE;
		return TRUE;

	case SIN_QUEST_CODE_CHANGEJOB2_NPC_D:

		if (lpTransItemInfo->Item.CODE == (sinMA2 | sin02))
		{
			if (!cInvenTory.SearchItemCode(sinMA1 | sin01)) return FALSE;
			if (cInvenTory.SearchItemCode(sinQT1 | sin05)) return FALSE;
			cnt = cInvenTory.SearchItemCode(sinMA2 | sin02);
			if (cnt >= 7) return FALSE;
		}
		if (lpTransItemInfo->Item.CODE == (sinMA2 | sin01)) return FALSE;
		return TRUE;
	}



	if (lpTransItemInfo->Item.CODE == (sinQT1 | sin06))
	{
		if (sinQuest_ChangeJob3.CODE == SIN_QUEST_CODE_CHANGEJOB3)
		{
			cnt = cInvenTory.SearchItemCode(sinQT1 | sin06);
			if (cnt >= 3) return FALSE;
			return TRUE;
		}
		return FALSE;
	}


	if (lpTransItemInfo->Item.CODE == (sinQT1 | sin09))
	{
		if (sinQuest_Level80_2.CODE == SIN_QUEST_CODE_LEVEL80_2)
		{
			cnt = cInvenTory.SearchItemCode(sinQT1 | sin09);
			if (cnt >= 1) return FALSE;
			return TRUE;
		}
		return FALSE;
	}

	if (lpTransItemInfo->Item.CODE == (sinQT1 | sin10))
	{
		if (sinQuest_Level80_2.CODE == SIN_QUEST_CODE_LEVEL80_2)
		{
			cnt = cInvenTory.SearchItemCode(sinQT1 | sin10);
			if (cnt >= 1) return FALSE;
			return TRUE;
		}
		return FALSE;
	}

	if (lpTransItemInfo->Item.CODE == (sinQT1 | sin11))
	{
		if (sinQuest_Level80_2.CODE == SIN_QUEST_CODE_LEVEL80_2)
		{
			cnt = cInvenTory.SearchItemCode(sinQT1 | sin11);
			if (cnt >= 1) return FALSE;
			return TRUE;
		}
		return FALSE;
	}



	if (lpTransItemInfo->Item.CODE == (sinQT1 | sin13))
	{

		if (sinQuest_ChangeJob4.CODE == SIN_QUEST_CODE_CHANGEJOB4 && sinQuest_ChangeJob4.State == 5)
		{
			cnt = cInvenTory.SearchItemCode(sinQT1 | sin13);
			if (cnt >= 1 || CheckAttMonsterCode(sinQuest_ChangeJob4.Kind) == FALSE)
				return FALSE;

			return TRUE;
		}
		return FALSE;
	}




	if (lpTransItemInfo->Item.CODE == (sinQT1 | sin16))
	{

		if (chaQuest.sHaQuestElementary[6].CODE == HAQUEST_CODE_ELEMENTARY_G)
		{
			cnt = cInvenTory.SearchItemCode(sinQT1 | sin16);
			if (cnt >= 1)
				return FALSE;

			if (dwPacketCode == OpCode::OPCODE_GETITEM)
			{

				char szBuff[256];

				AddChatBuff(szBuff, 6);
			}
			return TRUE;
		}
		return FALSE;
	}


	if ((lpTransItemInfo->Item.CODE&sinITEM_MASK2) == sinMA1 ||
		(lpTransItemInfo->Item.CODE&sinITEM_MASK2) == sinMA2)
	{


		return FALSE;
	}

	return TRUE;
}

POINT GetProcessModule();


int CheckProcessModule()
{
	POINT p;
	OSVERSIONINFO VersionInfo;
	BOOL Result;
	smTRANS_COMMAND	smTransCommand;


	return TRUE;

	VersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	ZeroMemory(&smTransCommand, sizeof(smTRANS_COMMAND));
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = OpCode::OPCODE_CLIENTINFO;

	Result = GetVersionEx(&VersionInfo);
	p = GetProcessModule();

	if (Result != FALSE)
	{
		smTransCommand.WParam = VersionInfo.dwPlatformId;
		smTransCommand.LParam = (VersionInfo.dwMajorVersion * 100) + VersionInfo.dwMinorVersion;
		smTransCommand.LParam = (smTransCommand.LParam << 16) | (VersionInfo.dwBuildNumber & 0xFFFF);
		smTransCommand.SParam = p.x;
		smTransCommand.EParam = p.y;

		smTransCommand.WParam ^= ((DWORD *)(UserAccount + 0))[0];
		smTransCommand.LParam ^= ((DWORD *)(UserAccount + 1))[0];
		smTransCommand.SParam ^= ((DWORD *)(UserAccount + 2))[0];
		smTransCommand.EParam ^= ((DWORD *)(UserAccount + 3))[0];

		if (smWsockDataServer)
			smWsockDataServer->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
	}

	return TRUE;
}


int SendFalconDamage(smCHAR *lpChar)
{
	DWORD point;
	int cnt;

	if (lpChar == lpCurPlayer && lpChar->chrAttackTarget)
	{
		point = ((SkillFalconPoint ^ ((DWORD)chrOtherPlayer^lpCurPlayer->dwObjectSerial)) + 1) << 8;
		point |= SKILL_PLAY_FALCON;
		cnt = dm_SendTransDamage(lpChar->chrAttackTarget, 0, 0, 0, 0, point, FALSE);
		DamageExp(lpChar->chrAttackTarget, cnt);
		return cnt;
	}
	return NULL;
}


int SendDancingSwordDamage(smCHAR *lpChar)
{
	DWORD point;
	int cnt;
	int wpDamage[2];

	if (lpChar)
	{

		wpDamage[0] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[0];
		wpDamage[1] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[1];

		point = 1 << 8;
		point |= SKILL_PLAY_DANCING_SWORD;
		cnt = dm_SendTransDamage(lpChar, wpDamage[0], wpDamage[1], 0, 0, point, FALSE);
		DamageExp(lpChar, cnt);

		if ((rand() % 2) == 0)
			SkillPlaySound(SKILL_SOUND_SKILL_DANCING_SWORD_ATK1, lpChar->pX, lpChar->pY, lpChar->pZ);
		else
			SkillPlaySound(SKILL_SOUND_SKILL_DANCING_SWORD_ATK2, lpChar->pX, lpChar->pY, lpChar->pZ);

		return cnt;
	}
	return FALSE;
}



int SendMegneticSphereDamage(smCHAR *lpChar)
{
	DWORD point;
	int cnt;
	int wpDamage[2];

	if (lpChar)
	{

		wpDamage[0] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[0];
		wpDamage[1] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[1];

		point = 1 << 8;
		point |= SKILL_PLAY_MAGNETIC_SPHERE;
		cnt = dm_SendTransDamage(lpChar, wpDamage[0], wpDamage[1], 0, 0, point, FALSE);
		DamageExp(lpChar, cnt);

		if ((rand() % 2) == 0)
			SkillPlaySound(SKILL_SOUND_SKILL_DANCING_SWORD_ATK1, lpChar->pX, lpChar->pY, lpChar->pZ);
		else
			SkillPlaySound(SKILL_SOUND_SKILL_DANCING_SWORD_ATK2, lpChar->pX, lpChar->pY, lpChar->pZ);

		return cnt;
	}
	return FALSE;
}


int SendMuspellDamage(smCHAR *lpChar)
{
	DWORD point;
	int cnt;
	int wpDamage[2];

	if (lpChar)
	{

		wpDamage[0] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[0];
		wpDamage[1] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[1];

		point = 1 << 8;
		point |= SKILL_PLAY_SUMMON_MUSPELL;
		cnt = dm_SendTransDamage(lpChar, wpDamage[0], wpDamage[1], 0, 0, point, FALSE);
		DamageExp(lpChar, cnt);

		if ((rand() % 2) == 0)
			SkillPlaySound(SKILL_SOUND_SKILL_DANCING_SWORD_ATK1, lpChar->pX, lpChar->pY, lpChar->pZ);
		else
			SkillPlaySound(SKILL_SOUND_SKILL_DANCING_SWORD_ATK2, lpChar->pX, lpChar->pY, lpChar->pZ);

		return cnt;
	}
	return FALSE;
}




int SendLowLevelPetDamage(smCHAR *lpChar, int petType)
{
	DWORD point;
	int cnt;
	int wpDamage[2];

	if (lpChar)
	{

		wpDamage[0] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[0];
		wpDamage[1] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[1];

		point = (1 + petType) << 8;
		point |= SKILL_PLAY_PET_ATTACK;
		cnt = dm_SendTransDamage(lpChar, wpDamage[0], wpDamage[1], 0, 0, point, FALSE);
		DamageExp(lpChar, cnt);

		return cnt;
	}
	return FALSE;
}



int SendPCBangPetDamage(smCHAR *lpChar, int petType)
{
	DWORD point;
	int cnt;
	int wpDamage[2];

	if (lpChar)
	{

		wpDamage[0] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[0];
		wpDamage[1] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[1];

		point = (1 + petType) << 8;
		point |= SKILL_PLAY_PET_ATTACK2;
		cnt = dm_SendTransDamage(lpChar, wpDamage[0], wpDamage[1], 0, 0, point, FALSE);
		DamageExp(lpChar, cnt);

		return cnt;
	}
	return FALSE;
}




int	SendItemExpress(DWORD	dwItemCode, char *szPassCode)
{
	smTRANS_COMMAND	smTransCommand;

	ZeroMemory((char *)&smTransCommand, sizeof(smTRANS_COMMAND));
	smTransCommand.code = OpCode::OPCODE_ITEM_EXPRESS;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = dwItemCode;

	if (szPassCode)
		smTransCommand.LParam = GetSpeedSum(szPassCode);

	if (smWsockDataServer)
		return smWsockDataServer->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

	return FALSE;
}


int	SendItemExpress(DWORD	dwItemCode)
{
	return	SendItemExpress(dwItemCode, 0);
}



int SendClanYahooMotion()
{
	smTRANS_COMMAND	smTransCommand;
	smWINSOCK *lpsmSock;

	if (lpCurPlayer->smCharInfo.ClassClan)
	{
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = OpCode::OPCODE_YAHOO_MOTION;
		smTransCommand.WParam = dwPlayTime;
		smTransCommand.LParam = 0;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = 0;

		lpsmSock = GetAreaServerSock();
		if (lpsmSock)
			lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

		return TRUE;

	}
	return FALSE;
}


int	SendStarPointToServer(int Price, int Cash)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = OpCode::OPCODE_STARPOINT;
	smTransCommand.WParam = Price;
	smTransCommand.LParam = Cash;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	if (smWsockDataServer)
		return smWsockDataServer->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

	return FALSE;
}


int	SendGiveMoneyToServer(int Money)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = OpCode::OPCODE_GIVEMONEY;
	smTransCommand.WParam = Money;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	if (smWsockDataServer)
		return smWsockDataServer->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

	return FALSE;
}


int	SendClanMoneyToServer(int Money, int Flag, int Kind)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = OpCode::OPCODE_CLANMONEY;
	smTransCommand.WParam = Money;
	smTransCommand.LParam = Flag;
	smTransCommand.SParam = Kind;
	smTransCommand.EParam = 0;

	if (smWsockDataServer)
		return smWsockDataServer->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

	return FALSE;
}

int	SendClanMoneyToServer(int Money, int Flag)
{
	return	SendClanMoneyToServer(Money, Flag, 0);
}


int	SendPaymentMoneyToServer(int Money, int Flag)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = OpCode::OPCODE_PAYMENT_MONEY;
	smTransCommand.WParam = Flag;
	smTransCommand.LParam = Money;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	if (smWsockDataServer)
		return smWsockDataServer->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

	return FALSE;
}







int	Send_ShowMyShopItem(smCHAR *lpChar)
{
	smTRANS_COMMAND	smTransCommand;
	int	result;
	smWINSOCK	*lpsmSock;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = OpCode::OPCODE_CALL_MYSHOP;
	smTransCommand.WParam = 0;
	smTransCommand.LParam = lpChar->dwObjectSerial;
	smTransCommand.SParam = lpCurPlayer->dwObjectSerial;
	smTransCommand.EParam = 0;

	lpsmSock = GetAreaServerSock();
	if (lpsmSock)
		result = lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

	return result;
}


int	Send_MyShopItemList(smTRANS_COMMAND	*lpTransCommand)
{
	int	result;
	smWINSOCK	*lpsmSock;

	TransTradeItems_MyShop.dwRecver = lpTransCommand->SParam;

	lpsmSock = GetAreaServerSock();
	if (lpsmSock)
		result = lpsmSock->Send((char *)&TransTradeItems_MyShop, TransTradeItems_MyShop.size, TRUE);

	return result;
}



int	Recv_MyShopItemList(TRANS_TRADEITEMS *lpTransTradeItems)
{
	sMYSHOP MyShopItem;
	smCHAR	*lpChar;


	DecodeCompress(lpTransTradeItems->TradeBuff, (BYTE *)&MyShopItem);


	cCharShop.RecvShopItem(&MyShopItem);


	lpChar = FindAutoPlayer(lpTransTradeItems->dwSender);

	if (lpChar && lpChar->DisplayFlag && lpChar->smCharInfo.szName[0])
	{
		OpenEachPlayer(lpChar);
		DispEachMode = TRUE;
	}

	return TRUE;
}



int	Send_PersonalShopItem(DWORD dwCharCode, void *lpShopItem)
{
	smTRANS_COMMAND_BUFF	smtBuff;


	smtBuff.smTransCommand.code = OpCode::OPCODE_MYSHOP_TRADE;
	smtBuff.smTransCommand.size = sizeof(smTRANS_COMMAND) + sizeof(sMYSHOP_ITEM_SERVER);
	smtBuff.smTransCommand.WParam = 0;
	smtBuff.smTransCommand.LParam = dwCharCode;
	smtBuff.smTransCommand.SParam = lpCurPlayer->dwObjectSerial;
	smtBuff.smTransCommand.EParam = 0;

	memcpy(smtBuff.Buff, lpShopItem, sizeof(sMYSHOP_ITEM_SERVER));

	if (smWsockDataServer)
		return smWsockDataServer->Send((char *)&smtBuff, smtBuff.smTransCommand.size, TRUE);

	return FALSE;
}


int	UpdateMyShopList(void *lpMyShop)
{
	sMYSHOP *lpMyShopItem = (sMYSHOP *)lpMyShop;
	int	result = 0;
	int		len;

	ZeroMemory(&TransTradeItems_MyShop, sizeof(TRANS_TRADEITEMS));


	len = EecodeCompress((BYTE *)lpMyShopItem, TransTradeItems_MyShop.TradeBuff, sizeof(sMYSHOP));
	if (len > TRANS_TRADE_BUFF_SIZE) return FALSE;

	TransTradeItems_MyShop.code = OpCode::OPCODE_MYSHOP_ITEM;
	TransTradeItems_MyShop.size = len + 48;
	TransTradeItems_MyShop.dwSum = 0;
	TransTradeItems_MyShop.dwSender = lpCurPlayer->dwObjectSerial;
	TransTradeItems_MyShop.dwRecver = 0;
	TransTradeItems_MyShop.Temp[0] = 0;
	TransTradeItems_MyShop.Temp[1] = 0;
	TransTradeItems_MyShop.Temp[2] = 0;
	TransTradeItems_MyShop.Temp[3] = 0;

	return TRUE;
}


int SendOpenPersonalTrade(char *szTradeMsg, void *lpPersTrade)
{
	TRANS_CHATMESSAGE	TransChatMessage;
	smWINSOCK	*lpsmSock;
	int	result = 0;
	DWORD	dwCode;
	sMYSHOP *lpMyShopItem = (sMYSHOP *)lpPersTrade;
	int		len;




	ZeroMemory(&TransTradeItems_MyShop, sizeof(TRANS_TRADEITEMS));


	ZeroMemory(&TransChatMessage, sizeof(TRANS_CHATMESSAGE));


	len = EecodeCompress((BYTE *)lpMyShopItem, TransTradeItems_MyShop.TradeBuff, sizeof(sMYSHOP));
	if (len > TRANS_TRADE_BUFF_SIZE) return FALSE;

	TransTradeItems_MyShop.code = OpCode::OPCODE_MYSHOP_ITEM;
	TransTradeItems_MyShop.size = len + 48;
	TransTradeItems_MyShop.dwSum = 0;
	TransTradeItems_MyShop.dwSender = lpCurPlayer->dwObjectSerial;
	TransTradeItems_MyShop.dwRecver = 0;
	TransTradeItems_MyShop.Temp[0] = 0;
	TransTradeItems_MyShop.Temp[1] = 0;
	TransTradeItems_MyShop.Temp[2] = 0;
	TransTradeItems_MyShop.Temp[3] = 0;


	TransChatMessage.code = OpCode::OPCODE_OPEN_MYSHOP;
	TransChatMessage.size = sizeof(TRANS_CHATMESSAGE);
	strcpy_s(TransChatMessage.szMessage, szTradeMsg);

	dwCode = GetSpeedSum(szTradeMsg);
	TransChatMessage.dwIP = dwCode;

	lpsmSock = GetAreaServerSock();
	if (lpsmSock)




		result = lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);

	if (result)
	{

		wsprintf(lpCurPlayer->szTradeMessage, "%s: %s", lpCurPlayer->smCharInfo.szName, szTradeMsg);
		lpCurPlayer->dwTradeMsgCode = dwCode;
	}

	return result;
}


int SendClosePersonalTrade()
{
	TRANS_CHATMESSAGE	TransChatMessage;
	smWINSOCK	*lpsmSock;
	int	result = 0;

	ZeroMemory(&TransChatMessage, sizeof(TRANS_CHATMESSAGE));

	TransChatMessage.code = OpCode::OPCODE_OPEN_MYSHOP;
	TransChatMessage.size = sizeof(TRANS_CHATMESSAGE);
	lpsmSock = GetAreaServerSock();
	if (lpsmSock)
		result = lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);

	lpCurPlayer->dwTradeMsgCode = 0;
	lpCurPlayer->szTradeMessage[0] = 0;

	return result;
}


int SendsServerDoc(char *szTradeMsg)
{
	TRANS_CHATMESSAGE	TransChatMessage;
	smWINSOCK	*lpsmSock;
	int	result = 0;


	ZeroMemory(&TransChatMessage, sizeof(TRANS_CHATMESSAGE));

	TransChatMessage.code = OpCode::OPCODE_ITEMDOC;
	TransChatMessage.size = sizeof(TRANS_CHATMESSAGE);
	strcpy_s(TransChatMessage.szMessage, szTradeMsg);

	lpsmSock = GetAreaServerSock();
	if (lpsmSock)
		result = lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);

	return result;
}



int DeleteEventItem_TimeOut(sITEMINFO	*lpsItem)
{

	struct	tm	tm;
	time_t		ttm;
	DWORD		dwCreateTime;

	DWORD		dwItemCode;

	dwItemCode = lpsItem->CODE&sinITEM_MASK2;

	DWORD NowTime = GetPlayTime_T();

	/*
	if (lpsItem->CODE == (sinCA1 | sin01) || lpsItem->CODE == (sinCA1 | sin02) || lpsItem->CODE == (sinCA1 | sin03) ||
		lpsItem->CODE == (sinCA1 | sin04) || lpsItem->CODE == (sinCA1 | sin05) || lpsItem->CODE == (sinCA1 | sin06) || 
		lpsItem->CODE == (sinCA1 | sin08) || lpsItem->CODE == (sinCA1 | sin09) || 
		lpsItem->CODE == (sinCA1 | sin10) || lpsItem->CODE == (sinCA1 | sin11) || lpsItem->CODE == (sinCA1 | sin12) ||
		lpsItem->CODE == (sinCA2 | sin01) || lpsItem->CODE == (sinCA2 | sin02) || lpsItem->CODE == (sinCA2 | sin03) ||
		lpsItem->CODE == (sinCA2 | sin04) || lpsItem->CODE == (sinCA2 | sin05) || lpsItem->CODE == (sinCA2 | sin06) ||
		lpsItem->CODE == (sinCA2 | sin08) || lpsItem->CODE == (sinCA2 | sin09) ||
		lpsItem->CODE == (sinCA2 | sin10) || lpsItem->CODE == (sinCA2 | sin11) || lpsItem->CODE == (sinCA2 | sin12))
	{
		if (lpsItem->dwCreateTime + (60 * 60 * 24 * 7) < NowTime)
			return TRUE;
	}

	if (lpsItem->CODE == (sinCA1 | sin07) || lpsItem->CODE == (sinCA2 | sin07))
	{
		if (lpsItem->dwCreateTime + (60 * 60 * 23) < NowTime)
			return TRUE;
	}
	*/
	if (lpsItem->CODE == (sinBI2 | sin81))
	{
		if (lpsItem->dwCreateTime + (60 * 30) < NowTime)
			return TRUE;
	}



	if (lpsItem->CODE != (sinOR2 | sin01) &&
		dwItemCode != sinPZ1 && dwItemCode != sinPZ2)
		return FALSE;

#ifdef _LANGUAGE_THAI_DELETE_RING
	if (lpsItem->CODE == (sinOR2 | sin01)) return TRUE;
#endif

	tm.tm_year = 2020 - 1900;
	tm.tm_mon = 4 - 1;
	tm.tm_mday = 1;
	tm.tm_hour = 15;
	tm.tm_min = 30;
	tm.tm_sec = 0;
	ttm = mktime(&tm);

	dwCreateTime = (DWORD)ttm;

	if (lpsItem->dwCreateTime < dwCreateTime) return TRUE;

	return FALSE;
}

int RecvSodGameInfomation(void *Info)
{
	smTRANS_COMMAND_SOD	*lpTransCommand = (smTRANS_COMMAND_SOD *)Info;

	if (!BellatraEffectInitFlag)
	{
		CreateBellatraFontEffect();
		BellatraEffectInitFlag = TRUE;
	}

	switch (lpTransCommand->smTransCommand.WParam)
	{
	case 1:
		if (SoD_SetFontEffect.eBL_Type == E_BL_LODING)
		{
			CheckBellatraFontEffect(&SoD_SetFontEffect, TRUE);
		}

		if (lpTransCommand->smTransCommand.SParam < 0)
		{


			sSodScore.EffectStartCount = 70 * 3;
			sSodScore.EffectCode = lpTransCommand->smTransCommand.LParam + 1;
		}
		else
		{
			if (lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_DEAD) break;

			sSodScore.SodNextStageNum = lpTransCommand->smTransCommand.SParam;
			sSodScore.dwSoD_NextStageTime = dwPlayTime + 9000;
			sSodScore.dwSoD_CloseStageTime = dwPlayTime + 5000;
			sSodScore.NextRound = lpTransCommand->smTransCommand.LParam + 1;

			StopBGM();
			esPlayContSound(14);
			lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_YAHOO);

			SetBellatraFontEffect(E_BL_FONT_STAGE);
			SetBellatraFontEffect(E_BL_FONT_COMPLETE);
			SoDGateFlag = TRUE;
		}
		break;

	case 3:

		if (lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_DEAD) break;

		sSodScore.SodNextStageNum = -1;
		sSodScore.dwSoD_NextStageTime = dwPlayTime + 8000;
		sSodScore.dwSoD_CloseStageTime = dwPlayTime + 6000;
		sSodScore.NextRound = -1;

		StopBGM();
		esPlayContSound(15);

		SetBellatraFontEffect(E_BL_FONT_STAGE);
		SetBellatraFontEffect(E_BL_FONT_FAIL);
		SoDGateFlag = TRUE;
		break;

	case 4:

		if (lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_DEAD) break;

		sSodScore.SodNextStageNum = lpTransCommand->smTransCommand.SParam;
		sSodScore.dwSoD_NextStageTime = dwPlayTime + 7000;
		sSodScore.NextRound = lpTransCommand->smTransCommand.LParam + 1;

		StopBGM();
		esPlayContSound(16);
		lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_YAHOO);


		SetBellatraFontEffect(E_BL_FONT_CON);
		SoDGateFlag = FALSE;


		char szBuff[128];
		wsprintf(szBuff, mgSOD_Clear, lpTransCommand->smTransCommand.EParam);
		cMessageBox.ShowMessageEvent(szBuff);

		break;

	case 2:

		if (lpTransCommand->smTransCommand.LParam)
		{

			sSodScore.ScoreEffectCount = 255;

		}
		else
		{



		}

		if (!sSodScore.dwSoD_NextStageTime)
		{
			if (sSodScore.Round != lpTransCommand->smTransCommand.SParam)
			{
				switch (lpTransCommand->smTransCommand.SParam)
				{
				case 1:
					sSodScore.dwPlayTime = dwPlayTime;
					PlayBGM_Direct(BGM_CODE_SOD1);
					break;

				case 4:
					PlayBGM_Direct(BGM_CODE_SOD2);
					break;

				case 7:
					PlayBGM_Direct(BGM_CODE_SOD3);
					break;
				}
			}
			sSodScore.Round = lpTransCommand->smTransCommand.SParam;
		}

		sSodScore.dwDispTime = dwPlayTime + 10 * 1000;
		sSodScore.MyTeam = lpTransCommand->MyTeam;
		sSodScore.Score = lpTransCommand->MyScore;
		sSodScore.TeamScore[0] = lpTransCommand->TeamScore[0];
		sSodScore.TeamScore[1] = lpTransCommand->TeamScore[1];
		sSodScore.TeamScore[2] = lpTransCommand->TeamScore[2];
		sSodScore.TeamScore[3] = lpTransCommand->TeamScore[3];

		break;

	case smCODE_SOD_EFFECT:
		if (!BellatraEffectInitFlag)
		{
			CreateBellatraFontEffect();
			BellatraEffectInitFlag = TRUE;
		}
		SetBellatraFontEffect((EBL_FontEffectType)lpTransCommand->smTransCommand.LParam);
		break;

	}

	return TRUE;
}


int RecvForceOrbItem(TRANS_ITEMINFO_GROUP2 *lpTransItemGroup2)
{
	TRANS_ITEMINFO_GROUP	TransItemGroup;

	ZeroMemory(&TransItemGroup, sizeof(TRANS_ITEMINFO_GROUP));
	memcpy(&TransItemGroup, lpTransItemGroup2, TRANS_GROUPITEM_HEADER_SIZE);

	DecodeCompress((BYTE *)lpTransItemGroup2->szBuff, (BYTE *)TransItemGroup.sItemInfo, sizeof(sITEMINFO)*TRANS_GROUPITEM_MAX);



	sinRecvForceOrb(TransItemGroup.sItemInfo, TransItemGroup.ItemCount);


	return TRUE;
}


int SendQuestCommandToServer(DWORD dwQuestCode, int Param1, int Param2, int Param3)
{

	smTRANS_COMMAND	smTransCommand;
	int	result = 0;
	smWINSOCK *lpsmSock;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = OpCode::OPCODE_QUEST_COMMAND;
	smTransCommand.WParam = dwQuestCode;
	smTransCommand.LParam = Param1;
	smTransCommand.SParam = Param2;
	smTransCommand.EParam = Param3;

	if (dwQuestCode >= HAQUEST_CODE_ELEMENTARY_A && dwQuestCode <= HAQUEST_CODE_FURYOFPHANTOM)
	{
		lpsmSock = smWsockDataServer;
		if (lpsmSock)
			result = lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

		return result;
	}

	lpsmSock = smWsockServer;
	if (lpsmSock)
		result = lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

	return result;
}


int Start_QuestArena(DWORD dwQuestCode, int Param1, int Param2)
{
	smTRANS_COMMAND	smTransCommand;
	int	result = 0;
	smWINSOCK *lpsmSock;



	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = OpCode::OPCODE_QUEST_COMMAND;
	smTransCommand.WParam = dwQuestCode;
	smTransCommand.LParam = QUEST_ARENA_FIELD;
	smTransCommand.SParam = Param1;
	smTransCommand.EParam = Param2;

	lpsmSock = GetAreaServerSock();
	if (lpsmSock)
		result = lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

	if (result)
		WarpField2(QUEST_ARENA_FIELD);



	return FALSE;
}


int	SendBlessCastleToServer(smTRANS_BLESSCASTLE *lpBlessCastleSetup, int Mode)
{
	smWINSOCK *lpsmSock;

	lpBlessCastleSetup->smTransCommand.size = sizeof(smTRANS_BLESSCASTLE);
	lpBlessCastleSetup->smTransCommand.code = OpCode::OPCODE_BLESSCASTLE_INFO;
	lpBlessCastleSetup->smTransCommand.WParam = 1;
	lpBlessCastleSetup->smTransCommand.LParam = Mode;
	lpBlessCastleSetup->smTransCommand.SParam = 0;
	lpBlessCastleSetup->smTransCommand.EParam = 0;

	lpsmSock = GetAreaServerSock();
	if (lpsmSock)
		return lpsmSock->Send((char *)lpBlessCastleSetup, lpBlessCastleSetup->smTransCommand.size, TRUE);

	return FALSE;
}


int	Send_GetBlessCastleTax()
{
	smTRANS_COMMAND	smTransCommand;

	ZeroMemory(&smTransCommand, sizeof(smTRANS_COMMAND));

	smTransCommand.code = OpCode::OPCODE_BLESSCASTLE_INFO;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.SParam = cSinSiege.GetTaxRate();

	if (smWsockDataServer)
		return smWsockDataServer->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

	return FALSE;
}

int RecvBlessCastInfo(void *lpPacket)
{
	smTRANS_BLESSCASTLE *lpBlessCastleSetup = (smTRANS_BLESSCASTLE *)lpPacket;
	rsUSER_LIST_TOP10	*lpClanListTop10;

	switch (lpBlessCastleSetup->smTransCommand.WParam)
	{
	case 1:
		chaSiege.ShowSiegeMenu(lpBlessCastleSetup);
		break;

	case 2:
		lpClanListTop10 = (rsUSER_LIST_TOP10 *)lpPacket;

		chaSiege.ShowSiegeScore(lpClanListTop10);
		break;
	}

	return TRUE;
}


int SetBlessCastleMaster(DWORD dwClanCode, int Mode)
{

	if (!Mode && lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->FieldCode == rsCASTLE_FIELD)
	{

	}
	else
	{
		if (rsBlessCastle.dwMasterClan != dwClanCode)
		{

			UpdateCastleMasterClan(rsBlessCastle.dwMasterClan);
		}

		rsBlessCastle.dwMasterClan = dwClanCode;
	}

	return TRUE;
}


int	SendResistanceToServer()
{
	smTRANS_RESISTANCE	smTransResistance;
	smWINSOCK *lpsmSock;

	dwResistance_SendingTime = dwPlayTime;

	smTransResistance.code = OpCode::OPCODE_RESISTANCE;
	smTransResistance.size = sizeof(smTRANS_RESISTANCE);
	smTransResistance.Param = 0;
	memcpy(smTransResistance.Resistance, lpCurPlayer->smCharInfo.Resistance, sizeof(short) * 8);
	smTransResistance.Absorb = lpCurPlayer->smCharInfo.Absorption;

	lpsmSock = GetAreaServerSock();
	if (lpsmSock)
		return lpsmSock->Send((char *)&smTransResistance, smTransResistance.size, TRUE);

	return FALSE;
}


int	SendPublicPollingToServer(int PollCode, int PollCnt, BYTE *bPollingData)
{
	smTRANS_COMMAND_POLLING	smTransPolling;

	ZeroMemory(&smTransPolling, sizeof(smTRANS_COMMAND_POLLING));

	smTransPolling.smTransCommand.code = OpCode::OPCODE_PUBLIC_POLLING;
	smTransPolling.smTransCommand.size = sizeof(smTRANS_COMMAND_POLLING);
	smTransPolling.smTransCommand.WParam = PollCode;
	smTransPolling.smTransCommand.LParam = PollCnt;
	memcpy(smTransPolling.bPolling, bPollingData, PollCnt);

	if (smWsockDataServer)
		smWsockDataServer->Send((char *)&smTransPolling, smTransPolling.smTransCommand.size, TRUE);


	return TRUE;
}




int XTrap_Recv(smTRANS_COMMAND *lpPacket, smWINSOCK *lpsmSock)
{
	return TRUE;
}



int	HackTrap_OpenFlagMask = 0;


int HackTrap_CheckOpenFlag()
{
	int ChkCnt = 0;


	if (cShop.OpenFlag && cShop.UseItemFlag == 0)
	{
		if ((HackTrap_OpenFlagMask & sinNPC_SHOP) == 0)
		{
			HackTrap_OpenFlagMask |= sinNPC_SHOP;
			SendHackTrapToServer(100, sinNPC_SHOP);
		}
		ChkCnt++;
	}

	if (cWareHouse.OpenFlag)
	{
		if ((HackTrap_OpenFlagMask&sinNPC_WARE) == 0)
		{
			HackTrap_OpenFlagMask |= sinNPC_WARE;
			SendHackTrapToServer(100, sinNPC_WARE);
		}
		ChkCnt++;
	}
	if (cCraftItem.OpenFlag)
	{
		if (cCraftItem.ForceFlag)return false;

		if ((HackTrap_OpenFlagMask&sinNPC_MIX) == 0)
		{
			HackTrap_OpenFlagMask |= sinNPC_MIX;
			SendHackTrapToServer(100, sinNPC_MIX);
		}

		ChkCnt++;
	}
	if (cCraftItem.ForceFlag)
	{
		if (cCraftItem.OpenFlag)return false;

		if ((HackTrap_OpenFlagMask&sinNPC_FORCE) == 0)
		{
			HackTrap_OpenFlagMask |= sinNPC_FORCE;
			SendHackTrapToServer(100, sinNPC_FORCE);
		}
		ChkCnt++;
	}
	if (cAging.OpenFlag)
	{
		if ((HackTrap_OpenFlagMask&sinNPC_AGING) == 0)
		{
			HackTrap_OpenFlagMask |= sinNPC_AGING;
			SendHackTrapToServer(100, sinNPC_AGING);
		}
		ChkCnt++;
	}


	if (SmeltingItem.OpenFlag)
	{
		if ((HackTrap_OpenFlagMask&sinNPC_SMELTING) == 0)
		{
			HackTrap_OpenFlagMask |= sinNPC_SMELTING;
			SendHackTrapToServer(100, sinNPC_SMELTING);
		}
		ChkCnt++;
	}

	if (ManufactureItem.m_OpenFlag)
	{
		if ((HackTrap_OpenFlagMask&sinNPC_MANUFACTURE) == 0)
		{
			HackTrap_OpenFlagMask |= sinNPC_MANUFACTURE;
			SendHackTrapToServer(100, sinNPC_MANUFACTURE);
		}
		ChkCnt++;
	}


	if (cMixtureReset.OpenFlag)
	{
		if ((HackTrap_OpenFlagMask & sinNPC_MIXTURE_RESET) == 0)
		{
			HackTrap_OpenFlagMask |= sinNPC_MIXTURE_RESET;
			SendHackTrapToServer(100, sinNPC_MIXTURE_RESET);
		}

		ChkCnt++;
	}

	if (SkillMasterFlag)
	{
		if ((HackTrap_OpenFlagMask&sinNPC_SKILL) == 0)
		{
			HackTrap_OpenFlagMask |= sinNPC_SKILL;
			SendHackTrapToServer(100, sinNPC_SKILL);
		}
		ChkCnt++;
	}

	if (!ChkCnt)
		HackTrap_OpenFlagMask = 0;

	return	TRUE;
}



int	SendHackTrapToServer(DWORD dwTrapCode, int Param)
{
	smTRANS_COMMAND	smTransCommand;

	ZeroMemory(&smTransCommand, sizeof(smTRANS_COMMAND));

	smTransCommand.code = OpCode::OPCODE_HACKTRAP;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = dwTrapCode;
	smTransCommand.LParam = Param;

	if (dwTrapCode == 100)
	{

		if (lpCurPlayer->OnStageField >= 0)
		{
			smTransCommand.SParam = StageField[lpCurPlayer->OnStageField]->FieldCode;
		}
		else
			return FALSE;
	}

	if (smWsockDataServer)
		smWsockDataServer->Send((char *)&smTransCommand, smTransCommand.size, TRUE);


	return TRUE;
}


int SendSmeltingItemToServer(void *lpsSmeltingItem_Send)
{
	sSMELTINGITEM_SERVER	*lpSmeltingItem_Send = (sSMELTINGITEM_SERVER *)lpsSmeltingItem_Send;

	lpSmeltingItem_Send->size = sizeof(sSMELTINGITEM_SERVER);
	lpSmeltingItem_Send->code = OpCode::OPCODE_SMELTINGITEM;

	if (smWsockDataServer)
		return smWsockDataServer->Send((char *)lpSmeltingItem_Send, lpSmeltingItem_Send->size, TRUE);

	return FALSE;
}

int SendManufactureItemToServer(void *lpsManufactureItem_Send)
{
	SManufactureItem_Server *lpManufactureItem_Send = (SManufactureItem_Server *)lpsManufactureItem_Send;

	lpManufactureItem_Send->size = sizeof(SManufactureItem_Server);
	lpManufactureItem_Send->code = OpCode::OPCODE_MANUFACTURE;

	if (smWsockDataServer)
		return smWsockDataServer->Send((char *)lpManufactureItem_Send, lpManufactureItem_Send->size, TRUE);

	return FALSE;
}


int SendMixtureResetItemToServer(void *lpsMixtureResetItem_Send)
{

	sMIXTURE_RESET_ITEM_SERVER *lpMixtureResetItem_Send = (sMIXTURE_RESET_ITEM_SERVER *)lpsMixtureResetItem_Send;


	lpMixtureResetItem_Send->size = sizeof(sMIXTURE_RESET_ITEM_SERVER);
	lpMixtureResetItem_Send->code = OpCode::OPCODE_MIXTURE_RESET_ITEM;


	if (smWsockDataServer)
		return smWsockDataServer->Send((char *)lpMixtureResetItem_Send, lpMixtureResetItem_Send->size, TRUE);

	return FALSE;
}

#ifdef _XIGNCODE_CLIENT


int Xigncode_Client_Start()
{
	smTRANS_COMMAND	smTransCommand;

	ZeroMemory(&smTransCommand, sizeof(smTRANS_COMMAND));

	smTransCommand.code = OpCode::OPCODE_XIGNCODE_START;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = TRUE;

	if (smWsockDataServer)
		smWsockDataServer->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

	return TRUE;
}


XIGNCODE_PACKET return_packet;

int Xigncode_Client_Recv(smWINSOCK *lpsmSock, XIGNCODE_PACKET *pack)
{

	memset(&return_packet, 0, sizeof(return_packet));

	if (ZCWAVE_Probe((char *)pack->data, (char *)return_packet.data, sizeof(return_packet.data)))
	{
		return_packet.size = sizeof(return_packet);
		return_packet.code = OpCode::OPCODE_XIGNCODE_PACKET;
		lpsmSock->Send((char *)&return_packet, return_packet.size, TRUE);
	}

	return TRUE;
}
#endif

