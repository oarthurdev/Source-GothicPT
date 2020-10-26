
#ifndef _NET_PLAY_HEADER

#define	_NET_PLAY_HEADER

#include "smPacket.h"

extern smWINSOCK	*smWsockServer;
extern smWINSOCK	*smWsockDataServer;

extern int ChatScrollPoint;
extern int DispChatMsgHeight;
extern int DispChatMode;

extern int BellatraEffectInitFlag;

extern char	szConnServerName[16];

extern int	Version_WareHouse;
extern int	Version_CharInfo;

extern smTRANS_COMMAND	*lpTransVirtualPotion;

extern DWORD	dwTime_ServerT;
extern DWORD	dwTime_ConnectMS;

extern int		InitClanMode;

extern DWORD	dwYahooTime;



extern DWORD	dwSkill_DivineLightning_Target[8];
extern int		DivineLightning_Target_Count;
extern int		DivineLightning_FindCount;



smCHAR *FindAutoPlayer(DWORD dwObjectSerial);

smCHAR *FindChrPlayer(DWORD dwObjectSerial);

smCHAR *FindDeadPartyUser();

smCHAR *FindNearMonster(smCHAR *lpCurChar);



int ClearAttMonsterCode();
int	AddAttMonsterCode(DWORD dwCode);
int	CheckAttMonsterCode(DWORD dwCode);



smWINSOCK *GetServerSock(int ServerCode);

smWINSOCK *GetAreaServerSock();


int RecvPlayData(smTHREADSOCK *pData);

int PlayRecvMessageQue();


int	SetChatMsgFilter(int mode);

int DisplayChatMessage(HDC hdc, int x, int y, int MaxLine);

int DisplayChatMessage2(HDC hdc, int x, int y, int StrMax, int LineMax);
int DisplayChatMessage3(HDC hdc, int x, int y, int StrMax, int LineMax, int Mode);

int RecallSavedChatCommand(HWND hChatWnd, int Arrow);


int SendChatMessageToServer(char *szMessage);

int ConnectOtherPlayer(DWORD dwIP);

int NetWorkPlay();

int AddChatBuff(char *szMsg, DWORD dwIP);

int AddChatBuff(char *szMsg);

DWORD EncodeParam(DWORD Param);


int ThrowPutItem(sITEM *lpItem, int x, int y, int z);

int ThrowPutItem2(sITEMINFO *lpItem, int x, int y, int z);


int SendDeleteStartPoint(int x, int z);

int SendAddStartPoint(int x, int z);

int SendAdd_Npc(smCHAR *lpCharSample, int state);

int SendDelete_Npc(smCHAR *lpCharSample);

int SendGetRecordData(char *szName);



int	SaveGameData();

int GetSaveResult();


int	TransUserCommand(DWORD dwCode, char *szID, char *szName);


int	Send_GetCharInfo(DWORD	dwObjectSerial, int ServerCode);

int	TransCheckNetwork();


int SendAdminMode(AccountTypes type);


int SendNetworkQuality(DWORD NetworkQuality);

int SendCheckIP(int Code, smWINSOCK *lpsmSock);


int SendSetObjectSerial(DWORD dwObjectSerial);

int SendSetObjectSerial_First(DWORD dwObjectSerial);


int SendSaveThrowItem(sITEMINFO *lpItemInfo);

int SendSaveThrowItem2(sITEMINFO *lpItemInfo);

int SendSaveMoney();

int SendContinueServer(DWORD dwObjectSerial, smWINSOCK *lpsmSock);

int CheckCracker();

int CheckCracker(TRANS_FIND_CRACKER *lpTransFindCrack);

int SendSetHackUser(int StopGame);

int SendSetHackUser2(int Type, int LParam);

int SendSetHackUser3(int Type, int LParam, int SParam);

int SendCopyItemUser(int CopyItemCount);

int SendCopyOtherUser(char *szName, int Mode);

int SendPlayUpdateInfo();

int SendUpdateClanInfo();

int SendOpenMonster(int State);


int SendRequestTrade(int dwObjectSerial, int Flag);

int SendTradeItem(DWORD dwSender);

int RecvTradeItems(TRANS_TRADEITEMS *lpTransTradeItems);

int SendTradeSucessKey(DWORD dwSender);

int SendTradeCheckItem(DWORD dwSender);

int GetTradeDistanceFromCode(DWORD dwObjectSerial);

int GetTradeDistance(smCHAR *lpChar);


int Skil_RangeAttack(int x, int y, int z, int range, int power, int TargetState);

int Skil_RangeAttack_User(int x, int y, int z, int range, int power, int TargetState);

int Skil_RangeBoxAttack(smCHAR *lpCurChar, RECT *lpRect, int power, int TargetState, int UseAttackRating);

int Skil_RangeBoxEffect(smCHAR *lpCurChar, RECT *lpRect, DWORD dwSkillCode, int TargetState);

int Skil_RangeEffect(smCHAR *lpCurChar, int Range, DWORD dwSkillCode, int TargetState, int point);



int QuickSendTransAttack(smCHAR *lpChar, int power, int AttackState, int Resistance);
int QuickSendTransAttack(smCHAR *lpChar, int power);
int QuickSendTransAttack(smCHAR *lpChar, int power, int Resistance);





int SendJoinPartyUser(DWORD dwObjectCode);




struct sWAREHOUSE;
int	SaveWareHouse(sWAREHOUSE *lpWareHouse, TRANS_WAREHOUSE *lpTransWareHouse);
int	SaveWareHouse(sWAREHOUSE *lpWareHouse);

int	LoadWareHouse(TRANS_WAREHOUSE *lpTransWareHouse, sWAREHOUSE *lpWareHouse, int flag);
int	LoadWareHouse(TRANS_WAREHOUSE *lpTransWareHouse, sWAREHOUSE *lpWareHouse);


int SendCollectMoney(int Money);



int PlayerKilling(DWORD dwObjectSerial);


smWINSOCK *ConnectServer_Main();

int DisconnectServerFull();


smWINSOCK *ConnectServer_InfoMain();

smWINSOCK *ConnectServer_GameMain(char *szIP1, DWORD dwPort1, char *szIP2, DWORD dwPort2);

smWINSOCK *ConnectServer_GameMain(char *szIP1, DWORD dwPort1, char *szIP2, DWORD dwPort2, char *szIP3, DWORD dwPort3);

int DisconnectServer_GameMain();


extern smWINSOCK	*smWsockServer;
extern smWINSOCK	*smWsockDataServer;
extern smWINSOCK	*smWsockUserServer;
extern smWINSOCK	*smWsockExtendServer;


extern	int	ReconnDataServer;
extern	int	ReconnServer;


extern int	DisconnectFlag;
extern int	DisconnectServerCode;

extern int	WarningHack;


extern int TradeSendSucessFlag;
extern DWORD	dwTradeMaskTime;
extern int	TradeItemSucessFlag;

extern	DWORD	dwLastRecvGameServerTime;
extern	DWORD	dwLastRecvGameServerTime2;
extern	DWORD	dwLastRecvGameServerTime3;
extern	DWORD	dwLastRecvGameServerTime4;



struct	PK_FIELD_STATE
{
	DWORD	dwPlay_FieldTime;
	int		FieldCode;
};
extern PK_FIELD_STATE	PK_FieldState;



#define DIS_TIME_OVER		30000

#define DISPLAY_TRANS_TIME_OVER		7000
#define DISPLAY_TRANS_TIME_OVER_FAR	4000


#define PLAY_SERVER_CODE_MAIN		1
#define PLAY_SERVER_CODE_USER		2
#define PLAY_SERVER_CODE_EXTEND		3

#define PLAY_SERVER_CODE_AREA1		11
#define PLAY_SERVER_CODE_AREA2		12


extern char *szNetLogFile;
extern FILE *fpNetLog;

extern TRANS_SKIL_ATTACKDATA	Back_TransSkilAttackData;


extern TRANS_ITEMINFO	TransRecvItem;



int	SetTotalAddMoney(int Money);
int	SetTotalSubMoney(int Money);
int	SetTotalAddExp(int Exp);
int	SetTotalSubExp(int Exp);
int GetTotalExp();
int	GetTotalMoney();
int GetTotalSubExp();



int SendSmeltingItemToServer(void *lpsSmeltingItem_Send);

int SendManufactureItemToServer(void *lpsManufactureItem_Send);

int SendMixtureResetItemToServer(void *lpsMixtureResetItem_Send);


int SendCraftItemToServer(void *lpsCraftItem_Send);

int SendAgingItemToServer(void *lpsCraftItem_Send);

int SendAgingUpgradeItemToServer(sITEMINFO *lpItem);

int SendLinkCoreToServer(sITEMINFO *lpItem);

int SendWingItemToServer(void *lpsCraftItem_Send);


int	SellItemToServer(sITEMINFO *lpItem, int Count);

extern DWORD	dwLastCheckItemTime;

int	SendCheckItemToServer(sITEMINFO *lpItem);

int CheckInvenItemToServer();



DWORD funcCheckMemSum(DWORD FuncPoint, int count);


int CheckRecvTrnsItemQue();

int SendUseItemCodeToServer(sITEMINFO *lpItem);


int	SendCommandUser(int wParam, int lParam, int sParam, int eParam);

int RecvCommandUser(smTRANS_COMMAND_EX *lpTransCommandEx);


int	SendCommand_AreaServer(DWORD dwCode, int wParam, int lParam, int sParam, int eParam);

int	SendCommand_DataServer(DWORD dwCode, int wParam, int lParam, int sParam, int eParam);


int	Init_RecordDamage();

int	Record_SendDamage(smWINSOCK *lpsmSock, int Damage);

int	Record_RecvDamage(smWINSOCK *lpsmSock, int Damage);


int	SendPartySkillToServer(DWORD dwSkillCode, int SkillLevel, int Around, int wParam, int lParam, int sParam, int eParam);

int SendCancelSkillToServer(DWORD dwSkillCode, int lParam, int sParam, int eParam);

int SendProcessSKillToServer(DWORD dwSkillCode, int point, int Param1, int Param2);

int SendUpdateSkillToServer(DWORD dwSkillCode, int lParam, int sParam, int eParam);



int RecvClanJoinService(smTRANS_CHAR_COMMAND2 *lpTransCharCommand);

int SendClanJoinService(DWORD dwMsgCode, smCHAR *lpChar);

int SendJoinClan();


int	SkillPlay_DivineLightning_Select(smCHAR *lpChar, int SkillPoint);

int SkillPlay_DivineLightning_Effect(smCHAR *lpChar, int SkillPoint);

int SkillPlay_VenomSpear_Effect(smCHAR *lpChar, int SkillPoint);

int SkillPlay_Monster_Effect(smCHAR *lpChar, int EffectKind, int Range);

int SkillPlay_MummyLord_Effect(smCHAR *lpChar, int Range);



DWORD	GetPlayTime_T();

int	ChangeBigHeadMode(int Mode, int Time);


int	RecvClanCommand(TRANS_CLAN_COMMAND_USER *lpTransClanUser, _CLAN_USER_INFO *ClanUserInfo);


int SendFalconDamage(smCHAR *lpChar);

int SendDancingSwordDamage(smCHAR *lpChar);

int SendLowLevelPetDamage(smCHAR *lpChar, int petType);

int SendPCBangPetDamage(smCHAR *lpChar, int petType);


int SendMegneticSphereDamage(smCHAR *lpChar);

int SendMuspellDamage(smCHAR *lpChar);



int	SendMaxDamageToServer(WORD MinDamage, WORD MaxDamage, WORD Critical);

int SetMaxDamage(smCHAR_INFO *lpCharInfo);


int ReformSkillInfo();

int SaveCheckSkill();


int	SendItemExpress(DWORD	dwItemCode, char *szPassCode);

int	SendItemExpress(DWORD	dwItemCode);


int SendClanYahooMotion();

int	SendStarPointToServer(int Price, int Cash);

int	SendGiveMoneyToServer(int Money);


#define	CLANMONEY_KIND_SOD		0
#define	CLANMONEY_KIND_CASTLE	1


int	SendClanMoneyToServer(int Money, int Flag, int Kind);
int	SendClanMoneyToServer(int Money, int Flag);

int	SendPaymentMoneyToServer(int Money, int Flag);



int SendOpenPersonalTrade(char *szTradeMsg, void *lpPersTrade);
int SendClosePersonalTrade();
int	Send_ShowMyShopItem(smCHAR *lpChar);
int	Send_MyShopItemList(smTRANS_COMMAND	*lpTransCommand);
int	Recv_MyShopItemList(TRANS_TRADEITEMS *lpTransTradeItems);
int	Send_PersonalShopItem(DWORD dwCharCode, void *lpShopItem);
int	UpdateMyShopList(void *lpMyShop);


int SendsServerDoc(char *szTradeMsg);




int DeleteEventItem_TimeOut(sITEMINFO	*lpsItem);


int SendQuestCommandToServer(DWORD dwQuestCode, int Param1, int Param2, int Param3);


int Start_QuestArena(DWORD dwQuestCode, int Param1, int Param2);


int	SendBlessCastleToServer(smTRANS_BLESSCASTLE *lpBlessCastleSetup, int Mode);

int RecvBlessCastInfo(void *lpPacket);

int	Send_GetBlessCastleTax();

int SetBlessCastleMaster(DWORD dwClanCode, int Mode);


int	SendResistanceToServer();



sITEMINFO *FindItemFromCode(DWORD dwItemCode);


int	SendPublicPollingToServer(int PollCode, int PollCnt, BYTE *bPollingData);


int HackTrap_CheckOpenFlag();

int	SendHackTrapToServer(DWORD dwTrapCode, int Param);

#ifdef _XIGNCODE_CLIENT

int Xigncode_Client_Recv(smWINSOCK *lpsmSock, XIGNCODE_PACKET *pack);
int Xigncode_Client_Start();
#endif

#endif