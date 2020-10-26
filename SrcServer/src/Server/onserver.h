#pragma once

#include <fileread.h>
#include <smPacket.h>

#define	LIMIT_PK_LEVEL	20				

#define AUTOPLAYER_MAX		2048
#define AUTOPLAYER_MASK		2047



#define	PRIME_ITEM_TIME_THIRDEYES		(60*60*24)
#define	PRIME_ITEM_TIME_EXPUP			(60*60*24)

#define	PRIME_ITEM_TIME_THIRDEYESx7		(60*60*24*7)
#define	PRIME_ITEM_TIME_EXPUPx7			(60*60*24*7)

#define	PRIME_ITEM_TIME_VAMPCUSPID		(60*60*3)	
#define	PRIME_ITEM_TIME_MANARECHARG		(60*60*3)	

#define	PRIME_ITEM_TIME_VAMPCUSPIDx2	(60*60*24)	
#define	PRIME_ITEM_TIME_MANARECHARGx2	(60*60*24)	

#define	PRIME_ITEM_TIME_PACKAGE1		(60*60*3)
#define	PRIME_ITEM_TIME_PACKAGE2		(60*60*24)
#define	PRIME_ITEM_TIME_PACKAGE3		(60*60*24*7)
#define	PRIME_ITEM_TIME_PACKAGE4		(60*60*24*30)
#define	PRIME_ITEM_TIME_PACKAGE5		(60*60*1) 


#define	PRIME_ITEM_PACKAGE_NONE			0
#define	PRIME_ITEM_PACKAGE_BRONZE		1
#define	PRIME_ITEM_PACKAGE_SILVER		2
#define	PRIME_ITEM_PACKAGE_GOLD			3
#define	PRIME_ITEM_PACKAGE_ULTRA		4


#define PRIME_ITEM_MIGHTOFAWELL			5
#define PRIME_ITEM_MANAREDUCE			6



#define	rsSOD_FIELD			30
#define	rsSOD_VILLAGE		9
#define	rsBABEL_FIELD		27
#define	rsKELVEZU_FIELD		36
#define	rsMOKOVA_FIELD		38

#define	rsCASTLE_FIELD	33
#define	rsACTION_FIELD	39
#define	rsHG_FIELD	32


#define	QUEST_ARENA_FIELD		32
#define	QUEST_ARENA_NPC_POS_X	(22091*fONE)
#define	QUEST_ARENA_NPC_POS_Z	(9673*fONE)


#define	WHERE_TRADE				300
#define	WHERE_GIFT_EXPRESS		600
#define	WHERE_AGINGITEM			400
#define	WHERE_CRAFTITEM			420
#define	WHERE_FORECORB			440
#define	WHERE_LEARNSKILL		460
#define	WHERE_WARPGATE			470
#define	WHERE_BUY_ITEM			200
#define	WHERE_BUY_POTION		210
#define	WHERE_SELL_ITEM			220
#define	WHERE_LOAD_PLAYER		100
#define	WHERE_THROW_ITEM		120
#define	WHERE_GET_ITEM			130
#define	WHERE_STAR_POINT		620
#define	WHERE_CLAN_MONEY		630
#define	WHERE_GIVE_MONEY		640
#define	WHERE_PERSONAL_SHOP		320
#define	WHERE_OPEN_WAREHOUES	500


#define STG_START_POINT_MAX			200

struct STG_CHAR_INFO
{

	smCHAR_INFO	smCharInfo;

	int		PosiState;

	int		StartFixed;
	POINT	StartPosi;

};

struct STG_START_POINT
{
	int state;
	int x, z;
};

#define STG_ITEM_MAX	1024

struct psITEM
{

	int		state;
	int		Serial;


	sITEMINFO	ItemInfo;
};

struct	STG_ITEMS
{
	int		state;
	int		x, y, z;
	psITEM	Item;
	DWORD	dwCreateTime;
	DWORD	dwLoseTime;
	DWORD	Level;
	int		BeginMode;
};


struct Rune_Formula
{
	DWORD Recipe;
	DWORD Rune[3];
};



#define FIX_CHAR_MAX	100

#define	STG_MONSTER_MAX		256


class smSTAGE3D;
class sFIELD;

class STG_AREA
{
public:
	DWORD	Head;

	smSTAGE3D			*lpStage;
	sFIELD				*lpField;

	char				szStartPointFile[64];
	char				szCharFixedFile[64];
	char				szCharMonsterFile[64];

	STG_START_POINT		StartPoint[STG_START_POINT_MAX];
	int					StartPointNearPlay[STG_START_POINT_MAX];
	int					StartPointMonCount[STG_START_POINT_MAX];
	int					StartPointCnt;
	int					StartPointLastOpenCount;
	DWORD				dwStartPoint_OpenTime[STG_START_POINT_MAX];

	int					StartPointOpenCount;
	int					StartPointActiveCount;

	STG_ITEMS			StgItems[STG_ITEM_MAX];

	STG_CHAR_INFO		*lpStageCharInfo;

	smTRNAS_PLAYERINFO	TransCharFixed[FIX_CHAR_MAX];

	rsSTG_MONSTER_LIST	rsMonsterList;

	int					StgCharInfoCnt;

	int					ItemSettingCount;
	int					MonsterSettingCount;

	int					Counter;

	DWORD				FieldNightDay;

	smCHAR				*lpCharMonster[STG_MONSTER_MAX];
	int					MonsterCount;
	int					MonsterLastPoint;

	int					EvnMonster;

	DWORD				Event_dwMonsterTime;
	smCHAR_INFO			*Event_lpChrMonster;
	int					Event_MonsterPercentage;

	DWORD				dwActiveMode;

	STG_AREA();


	int	Close();

	int LoadStage(char *szFile);

	smCHAR *OpenMonster(STG_CHAR_INFO *lpStgCharInfo, int gGroup = 1);
	int Main();

	int SendStartPos(rsPLAYINFO *lpPlayInfo);

	int LoadStartPoint(char *szFile);
	int SaveStartPoint(char *szFile);
	int FindStartPoint(int x, int z);
	int AddStartPoint(int x, int z, int state);
	int DeleteStartPoint(int x, int z);
	int SetStartPosChar(smCHAR *lpChar);
	int SetStartPosNearChar(smCHAR *lpChar, int cx, int cy, int cz);
	int SetPosNearChar(smCHAR *lpChar, int cx, int cy, int cz);
	int StartPosRandomize();

	int SendStartPointFlag();

	smTRNAS_PLAYERINFO *FindCharInfoFixed(smTRNAS_PLAYERINFO *lpTransPlayerInfo);
	int	AddCharInfoFixed(smTRNAS_PLAYERINFO *lpTransPlayerInfo);
	int	DeleteCharInfoFixed(smTRNAS_PLAYERINFO *lpTransPlayerInfo);
	int OpenNpc(smTRNAS_PLAYERINFO *lpTransPlayerInfo);
	int LoadCharInfoFixed(char *szFile);
	int SaveCharInfoFixed(char *szFile);

	STG_ITEMS *FindItem(int x, int y, int z);
	STG_ITEMS *AddItem(psITEM *lpItem, int x, int y, int z, int BeginMode = 0);
	int	DeleteItem(int x, int y, int z);
	int DeleteItem(STG_ITEMS *lpStgItem);
	int SendStgItem(rsPLAYINFO *lpPlayInfo);
	int SendStgItems();
	int SendStgItem(rsPLAYINFO *lpPlayInfo, STG_ITEMS *lpStgItem);
	int SendStgItemToNearUsers(STG_ITEMS *lpStgItem);
	int SendStgItemToPartyUsers(rsPLAYINFO *lpPlayInfo, STG_ITEMS *lpStgItem);

	int	FindEmptyMonTable();
	int	AddMonTable(smCHAR *lpChar);
	int	DeleteMonTable(smCHAR *lpChar);


	int LoadEnemyList(char *szFile);
};


#define STAGE_AREA_MAX		64

extern STG_AREA	*StageArea;

extern DWORD		dwPlayServTime;
extern rsSERVER_CONFIG		rsServerConfig;
//extern smCHAR		*chrAutoPlayer;
//extern rsPLAYINFO	*rsPlayInfo;
extern smCHAR chrAutoPlayer[AUTOPLAYER_MAX];
extern rsPLAYINFO rsPlayInfo[CONNECTMAX];

extern int Server_SqlReady;
extern HWND	hDebugWnd;
extern CRITICAL_SECTION	cSerSection;
extern int Server_SqlReady;

extern time_t		tServerTime;

extern DWORD		dwBabelPlayTime;
extern int			BabelPlayField;

extern DWORD		dwKelvezuPlayTime;
extern int			KelvezuPlayField;


#define srCASLTE_SOLDER_CLAN_MAX	20
#define srCASLTE_SOLDER_MAX			1
#define srCASLTE_SOLDER_KIND_MAX	5

struct	ATTACK_DAMAGE_LIST;

struct	rsBLESS_CASTLE
{

	int		CastleMode;
	DWORD	dwMasterClan;
	int		DefenceLevel;
	DWORD	dwLimitTime;
	int		Counter;

	int		Tax;
	int		NextTax;

	DWORD	dwBattleOverTime;
	int		SoulFountain_PotionCount;
	DWORD	dwSoulFountainTime;
	DWORD	dwSoulFountainTime2;
	int		SoulFountain_LastUserCount;

	DWORD	dwStartTime;
	short	TimeSec[2];
	int		SelectedSkill;

	int		Temp[10];

	smTRANS_BLESSCASTLE	BlessCastleSetup;
	rsUSER_LIST_TOP10	ClanTop10;
	ATTACK_DAMAGE_LIST	*lpAttackDamageList;
	char	bCrystalSolderCount[4];
	char	bCrystalTowerCount[4];
	smCHAR	*lpChar_ValhallaTower;
	DWORD	dwScoreLogTime;

};

extern rsBLESS_CASTLE	rsBlessCastle;


struct	rsCURRENCY_LOG
{

	INT64	int64_CraftMoney;
	INT64	int64_AgingMoney;
	INT64	int64_ShopMoney;
	INT64	int64_ShopPotionMoney[3];

	INT64	int64_ForceOrbMoney;
	INT64	int64_WarpgateMoney;
	INT64	int64_LearnSkillMoney;
};

extern	rsCURRENCY_LOG	CurrencyLog;



#define	srMONSTER_KILL_QUE_MAX		1024
#define	srMONSTER_KILL_QUE_MASK		1023

struct	rsKILL_MONSTER_INFO
{
	DWORD	dwAutoCharCode;
	DWORD	dwCharSoundCode;
	DWORD	dwMonObjectSerial;
	DWORD	dwUserObjectSerial;
	int		x, y, z, Area;
	int		PartyFlag;
	DWORD	dwParam[4];
};

struct	TRANS_KILL_MONSTER_INFO
{
	int		size, code;
	DWORD	tCode;
	int		KillInfo_Count;
	int		Temp[4];
};





#define	rsHARDCORE_COUNT_END	8	
#define	hCORE_ROUND_MAX		9

struct	_sHCORE_MONSTER
{
	char	szName[NAME_SIZE];
	smCHAR_INFO	*lpCharInfo;
	int		perCount;
};

struct	sHCORE_MONSTER
{

	_sHCORE_MONSTER	hCoreMonster1;
	_sHCORE_MONSTER	hCoreMonster2;
	_sHCORE_MONSTER	hCoreMonster3;
	_sHCORE_MONSTER	hCoreMonster4;
	_sHCORE_MONSTER	hCoreMonsterBoss;

	int		PerCount;
	int		StartHour;
	int		State;
	int		MaxMonster;
	int		DelayTime;
};




int rsSendDataServer(smWINSOCK *lpsmSock, void *szData);

int rsProcessQuest(rsPLAYINFO *lpPlayInfo, smCHAR *lpChar, int QuestCode, int QuestParam);

int SendShopItemList(smWINSOCK *lpsmSock, smCHAR *lpChar);

int SendSkillMenu(smWINSOCK *lpsmSock, smCHAR *lpChar, int Mode);

int SendOpenWareHouse(smWINSOCK *lpsmSock);

int SendOpenMixItem(smWINSOCK *lpsmSock, int MixFlag);

int SendOpenCollectMoney(smWINSOCK *lpsmSock);

int SendOpenEventGift(smWINSOCK *lpsmSock);

int SendOpenAgingItem(smWINSOCK *lpsmSock);

int SendOpenClanMenu(smWINSOCK *lpsmSock);

int SendOpenEvent(smCHAR *lpChar, rsPLAYINFO *lpPlayInfo, int EventFlag);

int SendOpenGiftExpress(rsPLAYINFO *lpPlayInfo, DWORD	dwItemCode, DWORD dwPassCode_Param);

int SendOpenSmelting(smWINSOCK *lpsmSock);

int SendOpenManufacture(smWINSOCK *lpsmSock);

TRANS_SOD_RESULT *rsSod_GetRealTimeScore(rsPLAYINFO *lpPlayInfo);

int SendOpenShop(smWINSOCK *lpsmSock);

int SendOpenTShop(smWINSOCK *lpsmSock);

int SendOpenMixtureItemReset(smWINSOCK *lpsmSock);

int SendOpenBattleArena(smWINSOCK *lpsmSock);

int SendOpenRestaureWindow(smWINSOCK* lpsmSock);

int SendProgressDiary(rsPLAYINFO * Player);

int DisconnectUser(smWINSOCK *lpsmSock);

int RecordHackLogFile(rsPLAYINFO *lpPlayInfo, void *lpTransCommand);


int RecvRangeAttack(rsPLAYINFO *lpPlayInfo, TRANS_SKIL_ATTACKDATA *lpTransSkilAttackData);

int RecvRangeAttackUser(rsPLAYINFO *lpPlayInfo, TRANS_SKIL_ATTACKDATA *lpTransSkilAttackData);



smCHAR *srFindCharFromSerial(DWORD dwObjectSerial, int AreaNum);

smCHAR *srFindCharFromSerial(DWORD dwObjectSerial);

rsPLAYINFO *srFindUserFromSerial(DWORD dwObjectSerial);

int rsPlayGrandHealing(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);

int	rsPlayHealing(smTRANS_COMMAND *lpTransCommand);


int srDisplayBillingTime(rsPLAYINFO *lpPlayInfo, int Add_BillingTime);

void OnlineReward();

int	rsSendCommandUser(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND_EX	*lpTransCommandEx);

int	rsSendCommandUser2(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);



int	rsShutDown();

DWORD GetSwapIPCode(char *szIP);


int rsEventLogOn_Sucess(rsPLAYINFO *lpPlayInfo);




int rsGetSoD_AreaCode(int x, int y, int z);

int rsSendRangeDamage(smCHAR *lpChar, rsPLAYINFO *lpMainPlayInfo, int Range, int SubDamgePers);

int rsGetMonsterLifeRegen(smCHAR *lpChar);


int	rsClanMoneyLog(rsPLAYINFO *lpPlayInfo, int Money, int RestMoney);



int rsAddServerPotion(rsPLAYINFO *lpPlayInfo, DWORD dwPotionCode, int PotionCount);

int rsGetServerPotion(rsPLAYINFO *lpPlayInfo, DWORD dwPotionCode);


int RecordHackLogFile(rsPLAYINFO *lpPlayInfo, void *lpBuff);

class rsPLAYINFO;

rsPLAYINFO *FindUserFromName(char *szName);
rsPLAYINFO *FindUserFromName2(char *szName);

smCHAR *OpenMonsterFromSkill(DWORD SkillCode, int x, int y, int z, rsPLAYINFO *lpPlayInfo, smCHAR *lpEnemyChar);

smCHAR *rsGetLinkChar(smCHAR *lpMasterChar);



int rsRecvBlessCastInfo(rsPLAYINFO *lpPlayInfo, void *lpPacket);

int rsSendBlessCastInfo(rsPLAYINFO *lpPlayInfo, int Mode);


DWORD GetClanCode(int ClassClanCode);



int	rsUpdateServerParam(rsPLAYINFO *lpPlayInfo, DWORD dwUpdateCode, int Param1, int Param2, int TargetMode);



int rsDebugMessageToClient(rsPLAYINFO *lpPlayInfo, char *szDmgMsg);



int rsGetExp_GameTime(rsPLAYINFO *lpPlayInfo);

DWORD ManufactureCheckRune(rsPLAYINFO *lpPlayInfo, DWORD RecipeCode, DWORD *pRuneCode);


int rsDispay_GameTime(rsPLAYINFO *lpPlayInfo, DWORD dwTimeOld);


int	rsUseSoccerBallPotionItem(DWORD dwItemCode, rsPLAYINFO *lpPlayInfo);


int SetAgingItem(sITEMINFO *pItem, int AgingNum);
