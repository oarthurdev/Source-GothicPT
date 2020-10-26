#define _WIN32_WINNT    0x0403  
#define _WIN32_WINDOWS  0x0403

#include <windows.h>
#include <io.h>
#include <stdio.h>         
#include <string.h>        
#include <memory.h>
#include <process.h>       


#include "Resources\\resource.h"
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

#include "Language\\language.h"

#include "..\\sinbaram\\sinitem.h"

#include "ClientFuncPos.h"

#include "OnServer.h"
#include "svr_Damage.h"

#include "svrEventSpawn.h"			

#include "svrEventGame.h"				

#include "..\\damage.h"




#ifdef _W_SERVER

#include "Database\DataBase.h"

#endif

#include "Login\Login.h"


#ifdef _W_SERVER
#include "ServerMsg.h"
#else

#define CHAT_ANGERMONSTER_MAX		2
char *szAngerMonster[CHAT_ANGERMONSTER_MAX] = { "","" };
char *szMonsterFlagMsg = "";
#define		SERVER_DOWN_MSG_COUNT	2
char *szServerDownMsg[SERVER_DOWN_MSG_COUNT] = { "", "" };
char *szSeverDownCountMsg = "";
char	*srMsg_Bl_01;
char	*srMsg_Bl_02;
char	*srMsg_BI_03;
char	*srMsg_BI_04;
char	*srMsg_Bl_100;
char	*srMsg_Bl_1001;
char	*srMsg_Bl_101;
char	*srMsg_Bl_102;
char	*srMsg_011;
char	*srMsg_038;
char	*srMsg_300;
char	*srMsg_301;
char	*srMsg_400;
char	*srMsg_401;
char	*srItem_BB;

char *srBlessCastle_LeagueMsg_01;
char *srBlessCastle_LeagueMsg_02;
char *srBlessCastle_LeagueMsg_03;
char *srBlessCastle_LeagueMsg_04;
char *srBlessCastle_LeagueMsg_05;

char *srMsg_StartUser_PresentItem;

char *szMiniMorif;
char *szWantedMorif;




char *szMon_FireCrystal;
char *szMon_LightningCrystal;
char *szMon_IceCrystal;
char *szMon_TowerCrystal;
char *szMon_Castledoor;

char *szMon_Curse_Soldier_A;
char *szMon_Curse_Soldier_B;
char *szMon_Curse_Soldier_C;
char *szMon_Castledoor_Soldier;

char *StateInitEvent1;
char *StateInitEvent2;
char *StateInitEvent3;
char *StateInitEvent4;
char *szEvent_HopeMsg_StateInit;

#endif

#include "Language\\Chinese\\c_TimeLimit.h" 


#ifdef _LANGUAGE_BRAZIL
char *finehack_message = "http://info.pristontale.com/blackWarning/warning.asp?id=%s&name=%s";
#endif

#define MAX_MONEY 1000000000

int LogOnThread_Count;
int	LogOnThread_Process;
int LogOnThread_ProcessTime;
int LogOnThread_Sucess;

char	szLastLogInID[64];
int		LastLogInResult = 0;


int rsRefreshConfig();

HFONT	hServerFont = 0;

int		Svr_DisplayMode = 0;



char *srEventMonName1 = "좀비";

#define	srCRISTAL_MAX		20		
#define MARVELCRISTAL_MAX	8
#define srKIDMONSTER_MAX	1	
#define srSOD_GUARD_MONSTER_MAX	5	

struct srCRISTAL_MONSTER
{
	char *szName;
	smCHAR_INFO	*lpCharInfo;
	int	RndCount;
};



static int rsSOD_CRYSTAL_GUARD_MONSTER_POS[7][3] = {

	{33,		34560,		-25785},
	{33,		34200,		-26080},
	{33,		34900,		-26080},
	{33,		33745,		-28575},
	{33,		35345,		-28575},
	{33,		34135,		-30575},
	{33,		34975,		-30575}
};



struct srOPENKID_MONSTER
{
	char *szParentMonName;
	char *szChildMonName;
	int	mon_Num;
	int mon_Count;
};



srOPENKID_MONSTER srOpenKidMonster[srKIDMONSTER_MAX] = {

	{szWantedMorif,		szMiniMorif,			0,		3}
};


srOPENKID_MONSTER srOpenSODCrystalGuardMonster[srSOD_GUARD_MONSTER_MAX] = {

	{szMon_FireCrystal ,		szMon_Curse_Soldier_A,		100,		10},
	{szMon_IceCrystal,			szMon_Curse_Soldier_B,		100,		10},
	{szMon_LightningCrystal,	szMon_Curse_Soldier_C,		100,		10},
	{szMon_TowerCrystal,		szMon_Curse_Soldier_B,		100,		10},
	{szMon_Castledoor,			szMon_Castledoor_Soldier,	101,		6}
};

#define	srCRISTAL_RANDOM		8
#define	srCRISTAL_CLAN			9
#define srCLAN_MONSTER_MAX		3
#define	srCRISTAL_CASTLE_START	13
#define	srCRISTAL_CASTLE_END	16

#define	srCRISTAL_SKELETON		16	
#define	srCRISTAL_KAOS			17	
#define	srCRISTAL_IMPERNA		18	
#define srCRISTAL_EXTREME		19		
#define	srCRISTAL_MARVEL_RANDOM	20		
#define	srCRISTAL_G_DIVINE_CLAN			21		



srCRISTAL_MONSTER	srCristalMonster[srCRISTAL_MAX] = {
	{ "Hopi"				, 0 , 20	},
	{ " 홉고블린 "			, 0 , 20	},
	{ " 디코이 "			, 0 , 15	},
	{ " 바곤 "				, 0 , 15	},
	{ " 헤드커터 "			, 0 , 15	},
	{ " 파이곤 "			, 0 , 10	},
	{ " 킹호피 "			, 0 , 5		},
	{ " 헐크 "				, 0 , 0		},
	{ " 랜덤 "				, 0 , 0		},
	{ "가디안 세인트"		, 0 , 0		},
	{ " 웹 "				, 0 , 0		},
	{ " 다크 스펙터 "		, 0 , 0		},
	{ " 아이언 가드 "		, 0 , 0		},
	{ "리카르텐 민병대"		, 0 , 0		},
	{ "리카르텐 경비대"		, 0 , 0		},
	{ "블레스왕국 경비대"	, 0 , 0		},

	{ "스켈레톤 크리스탈"	, 0 , 0		},
	{ "카오스   크리스탈"	, 0 , 0		},
	{ "인페르나 크리스탈"	, 0 , 0		},
	{ "가디안 디바인"		, 0 , 0		}

};






srCRISTAL_MONSTER	srCristalMonsterBoss[srCRISTAL_MAX] = {
	{ " 짱피 "				, 0 , 20	},
	{ " 와일드 고블린 "		, 0 , 20	},
	{ " 맥시멈 디코이 "		, 0 , 15	},
	{ " 바우톤 "			, 0 , 15	},
	{ " 베가 드미르 "		, 0 , 15	},
	{ " 헬싱 "				, 0 , 10	},
	{ " 호러피온 "			, 0 , 5		},
	{ " 타이푼 "			, 0 , 0		},
	{ " 랜덤 "				, 0 , 0		},
	{ "가디안 세인트"		, 0 , 0		},
	{ " 커즈웹 "			, 0 , 0		},
	{ " 다크 팬텀 "			, 0 , 0		},
	{ " 이미티르 가드 "		, 0 , 0		},
	{ "리카르텐 민병대"		, 0 , 0		},
	{ "리카르텐 경비대"		, 0 , 0		},
	{ "블레스왕국 경비대"	, 0 , 0		},

	{ "스켈레톤 크리스탈"	, 0 , 0		},
	{ "카오스   크리스탈"	, 0 , 0		},
	{ "인페르나 크리스탈"	, 0 , 0		},
	{ "가디안 디바인"		, 0 , 0		}
};

srCRISTAL_MONSTER srMarvelCristalMonster[MARVELCRISTAL_MAX] = {
	{ " 바곤 "				, 0 , 20	},
	{ " 헤드커터 "			, 0 , 20	},
	{ " 파이곤 "			, 0 , 15	},
	{ " 킹호피 "			, 0 , 15	},
	{ " 헐크 "				, 0 , 12	},
	{ " 웹 "				, 0 , 10	},
	{ " 다크 스펙터 "		, 0 , 5		},
	{ " 아이언 가드 "		, 0 , 3		}
};


srCRISTAL_MONSTER srMarvelCristalMonsterBoss[MARVELCRISTAL_MAX] = {
	{ " 바우톤 "			, 0 , 20	},
	{ " 베가 드미르 "		, 0 , 20	},
	{ " 헬싱 "				, 0 , 15	},
	{ " 호러피온 "			, 0 , 15	},
	{ " 타이푼 "			, 0 , 12	},
	{ " 커즈웹 "			, 0 , 10	},
	{ " 다크 팬텀 "			, 0 , 5		},
	{ " 이미티르 가드 "		, 0 , 3		}
};

#define	srSKILL_MONSTER_MAX		3


srCRISTAL_MONSTER	srSkillMonster[srSKILL_MONSTER_MAX] = {
	{ "메탈 고렘"		, 0 , 0	},
	{ "울버린"			, 0 , 0	},
	{ "파이어 엘레멘탈"	, 0 , 0	}
};


srCRISTAL_MONSTER	srCristalMonsterEnemy[7] = {
	{ " 코크리스의 영혼 "				, 0 , 20	},
	{ " 리치의 영혼 "		, 0 , 20	},
	{ " 싸이클롭스의 영혼 "		, 0 , 15	},
	{ " 메핏의 영혼 "			, 0 , 15	},
	{ " 비독의 영혼 "		, 0 , 15	},
	{ " 좀비의 영혼 "				, 0 , 10	},
	{ " 디코이의 영혼 "			, 0 , 5		}
};


srCRISTAL_MONSTER	srCristalMonsterEnemy2[7] = {
	{ " 뱀피릭 뱃의 영혼 "				, 0 , 20	},
	{ " 그리븐의 영혼 "		, 0 , 20	},
	{ " 이블 스네일의 영혼 "		, 0 , 15	},
	{ " 크립트의 영혼 "			, 0 , 15	},
	{ " 부마의 영혼 "		, 0 , 15	},
	{ " 바곤의 영혼 "				, 0 , 10	},
	{ " 타이탄의 영혼 "			, 0 , 5		}
};


srCRISTAL_MONSTER	srCristalMonsterEnemy3[7] = {
	{ " 비블의 영혼 "				, 0 , 20	},
	{ " 슬레이온의 영혼 "		, 0 , 20	},
	{ " 슬러터의 영혼 "		, 0 , 15	},
	{ " 타워 고렘의 영혼 "			, 0 , 15	},
	{ " 머미의 영혼 "		, 0 , 15	},
	{ " 나즈의 영혼 "				, 0 , 10	},
	{ " 위치의 영혼 "			, 0 , 5		}
};


srCRISTAL_MONSTER	srCristalMonsterEnemy4[7] = {
	{ " 버서커의 영혼 "				, 0 , 20	},
	{ " 타이푼의 영혼 "		, 0 , 20	},
	{ " 리자드포크의 영혼 "		, 0 , 15	},
	{ " 램페이지의 영혼 "			, 0 , 15	},
	{ " 아벨린의 영혼 "		, 0 , 15	},
	{ " 인큐버스의 영혼 "				, 0 , 10	},
	{ " 새드니스의 영혼 "			, 0 , 5		}
};


srCRISTAL_MONSTER	srCristalMonsterEnemy5[7] = {
	{ " 디-머신의 영혼 "				, 0 , 20	},
	{ " 킹호피의 영혼 "		, 0 , 20	},
	{ " 오메가의 영혼 "		, 0 , 15	},
	{ " 데드존의 영혼 "			, 0 , 15	},
	{ " 아이스 고렘의 영혼 "		, 0 , 15	},
	{ " 콜드아이의 영혼 "				, 0 , 10	},
	{ " 굴가르의 영혼 "			, 0 , 5		}
};


srCRISTAL_MONSTER	srCristalMonsterEnemy6[7] = {
	{ " 뱀피릭 뱃의 영혼 "				, 0 , 20	},
	{ " 그리븐의 영혼 "		, 0 , 20	},
	{ " 이블 스네일의 영혼 "		, 0 , 15	},
	{ " 크립트의 영혼 "			, 0 , 15	},
	{ " 부마의 영혼 "		, 0 , 15	},
	{ " 바곤의 영혼 "				, 0 , 10	},
	{ " 머핀의 영혼 "			, 0 , 5		}
};


srCRISTAL_MONSTER	srCristalMonsterEnemy7[7] = {
	{ " 비블의 영혼 "				, 0 , 20	},
	{ " 슬레이온의 영혼 "		, 0 , 20	},
	{ " 슬러터의 영혼 "		, 0 , 15	},
	{ " 타워 고렘의 영혼 "			, 0 , 15	},
	{ " 머미의 영혼 "		, 0 , 15	},
	{ " 나즈의 영혼 "				, 0 , 10	},
	{ " 슬리버의 영혼 "			, 0 , 5		}
};


srCRISTAL_MONSTER	srCristalMonsterEnemy8[7] = {
	{ " 버서커의 영혼 "				, 0 , 20	},
	{ " 타이푼의 영혼 "		, 0 , 20	},
	{ " 리자드포크의 영혼 "		, 0 , 15	},
	{ " 램페이지의 영혼 "			, 0 , 15	},
	{ " 아벨린의 영혼 "		, 0 , 15	},
	{ " 인큐버스의 영혼 "				, 0 , 10	},
	{ " 메트론의 영혼 "			, 0 , 5		}
};


srCRISTAL_MONSTER	srCristalMonsterEnemy9[7] = {
	{ " 디-머신의 영혼 "				, 0 , 20	},
	{ " 킹호피의 영혼 "		, 0 , 20	},
	{ " 오메가의 영혼 "		, 0 , 15	},
	{ " 데드존의 영혼 "			, 0 , 15	},
	{ " 아이스 고렘의 영혼 "		, 0 , 15	},
	{ " 콜드아이의 영혼 "				, 0 , 10	},
	{ " 그로테스크의 영혼 "			, 0 , 5		}
};




#define	srBC_MONSTER_MAX		4
#define	srBC_MONSTER_TOTAL		16
srCRISTAL_MONSTER	srBillingCrystalMonster[srBC_MONSTER_TOTAL] = {
	{ " 스켈레톤 아처 "     , 0 , 0	},
	{ " 스켈레톤 레인저 "	, 0 , 0	},
	{ " 스켈레톤 워리어 "	, 0 , 0	},
	{ " 스켈레톤 나이트 "	, 0 , 0	},

	{ " 나즈 "	        , 0 , 0	},
	{ " 헤비 고블린 "	, 0 , 0	},
	{ " 스트라이더 "	, 0 , 0	},
	{ " 디-머신 "	        , 0 , 0	},

	{ " 라투 "	        , 0 , 0	},
	{ " 그로테스크 "	, 0 , 0	},
	{ " 아이언 피스트 "	, 0 , 0	},
	{ " 프로스트 에이션트 "	, 0 , 0	},

	{ " 오미크론 "	        , 0 , 35	},
	{ " 스파이더 트루퍼 "	, 0 , 30	},
	{ " 마운틴 "	, 0 , 20	},
	{ " 오메가 "	, 0 , 15	}
};




#define srHAMMER_MONSTER_MAX		16

smCHAR_INFO	*srCharInfo_HammerMonster[srHAMMER_MONSTER_MAX];
int	srHammerMonsterCount = 0;


#ifdef _W_SERVER
char *szAdminIP = "211.219.44.";
char *szAdminIP2 = "211.44.231.";
#else
char *szAdminIP = "220.76.89.";
char *szAdminIP2 = "220.76.88.";
#endif

#define MYWM_NOTIFYICON		(WM_USER+140)
#define MYWM_USER_COUNT		(WM_USER+110)
#define ID_MESSTEXT		101

void TrayIconClose();
void TrayIconCreat();

int InitAll();

void RemoveAll();


CRITICAL_SECTION	cSerSection;
static CRITICAL_SECTION	cOdbcSection;

char	szServer_DebugString[256];
DWORD	dwServer_DebugMessage;
char	szServer_DebugLastUserID[ACCOUNT_SIZE];
char	szServer_DebugLastUserName[NAME_SIZE];
int		Server_DebugCount;

int		rsNSpriteMode = 0;

int		rsOpenNPC_RandomPos = 0;

HWND	hDebugWnd = 0;
#define	SWM_DISPDEBUG	(WM_USER+77)


int	ServerMode = 0;
int	Server_SqlReady = 0;
int	ServerNameCode = 0;

static HINSTANCE hInst;
extern HWND hwnd;
static HWND hMsgTextWnd;
static HDC	hdc = NULL;
static int Quit = 0;
static char *szAppName = "GothicPT";
static LONG APIENTRY WndProc(HWND, UINT, WPARAM, LPARAM);
static int WinWidth = 320;
static int WinHeight = 240;

static int WSA_RecvMsgCount = 0;

static	int AccountPerl = 100;
static	int	ShutDownFlag = 0;
static	int	ShutDownLeftTime = 0;

INT SetupDefWindow(HINSTANCE hInstance, HANDLE hPreInst, LPSTR lpszCmdParam, int nCmdShow)
{
	WNDCLASS	wndclass;

	hInst = hInstance;

	if(!hPreInst)
	{
		wndclass.style = CS_HREDRAW | CS_VREDRAW;
		wndclass.lpfnWndProc = WndProc;
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hInstance = hInst;
		wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SERVER_ICON));
		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wndclass.lpszMenuName = "IDR_MENU1";
		wndclass.lpszClassName = szAppName;
		RegisterClass(&wndclass);
	}

	
	int posX = (GetSystemMetrics(SM_CXSCREEN) - 350) / 2;
	int posY = (GetSystemMetrics(SM_CYSCREEN) - 350) / 2;

	
	hwnd = CreateWindow(szAppName, szAppName, WS_SYSMENU | WS_MINIMIZEBOX | WS_MINIMIZE, posX, posY, 350, 350, NULL, NULL, hInst, NULL);




	HMENU	hMenu;
	hMenu = CreateMenu();

	hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU2));

	SetMenu(hwnd, hMenu);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);



#ifdef _LANGUAGE_BRAZIL
	SetWindowText(hwnd, "Server [ GothicPT ]");
#endif


#ifndef _LANGUAGE_KOREAN
	AccountPerl = 40;
#endif


	TrayIconCreat();

	ServerMode = TRUE;
	szServer_DebugString[0] = 0;


	rsRefreshConfig();



	InitGameSocket(TRUE);

	InitAll();

	if(cSettings::GetInstance()->cPort)
		InitBindSock(cSettings::GetInstance()->cPort);
	else
		InitBindSock(TCP_SERVPORT);


	EnableMenuItem(GetMenu(hwnd), ID_STOP, MF_ENABLED);
	EnableMenuItem(GetMenu(hwnd), ID_START, MF_GRAYED);

	return	TRUE;

}


char szMessageBuff[256];
DWORD ListBuff[smSOCKBUFF_SIZE / 4];
int PlayerCount;



struct	rsSERVER_NOTICE
{
	DWORD Counter;
	char szMessage[256];
};
rsSERVER_NOTICE	rsNoticeMessage;



extern	smWINSOCK	smWSock[CONNECTMAX];

#define DIST_AROUND_NEAR	(256*256)
#define DIST_AROUND_MIDDLE	(16*64 * 16*64)

#define CHATBUFF_MAX		1024
#define CHATBUFF_MASK		1023

#define TRANS_IPMAX			(1000/sizeof(TRANS_IPLIST))


#define AREA_USERMAX		256
#define AREA_MAX			256

#define AUTOPLAYER_MAX		2048
#define AUTOPLAYER_MASK		2047


int rsConnectUserLimit = 800;


#ifdef	_LANGUAGE_THAILOW		


#define	TRANS_MAX_CHAR_LIMIT	24
#define	TRANS_MAX_USER_LIMIT	16
#else
#define	TRANS_MAX_CHAR_LIMIT	28
#define	TRANS_MAX_USER_LIMIT	18
#endif



#define	OVER_TRANS_TIME		1500

#define STAGE_MAX			10
smSTAGE3D	*lpsmStage[STAGE_MAX];

DWORD		dwPlayServTime = 0;
DWORD		dwOffsetTime = 0;

#define	CHR_MONSTER_MAX		400
#define	DEF_ITEM_MAX		1000 


#define	REOPEN_COUNT_NUM	256


#define TRANS_VIEW_LIMIT		(64*64)


#define OPEN_START_MONSTER_MAX		3


#define	STG_ITEM_WAIT_TIME		(1000*60*3)
#define	STG_ITEM_WAIT_TIME_LOW	(1000*90)


#define ITEM_SET_DIST	24

POINT	ptItemSettingPosi[8] = {
	{  0			 , -ITEM_SET_DIST },
	{  ITEM_SET_DIST , -ITEM_SET_DIST },
	{  ITEM_SET_DIST ,  0			  },
	{  ITEM_SET_DIST ,  ITEM_SET_DIST },
	{  0             ,  ITEM_SET_DIST },
	{ -ITEM_SET_DIST ,  ITEM_SET_DIST },
	{ -ITEM_SET_DIST ,  0             },
	{ -ITEM_SET_DIST , -ITEM_SET_DIST }
};



int	LoginServer = 0;
int	AutoPlayServer = 0;
int	UserPlayServer = 0;

int chrMonsterCnt;
int	EventMonster = 0;


#define	LIMIT_PK_LEVEL	20				


int	rsHardCoreEvent = 0;
int	rsDamgeOffEvent = 0;



int	rsDamgeOffEvent1 = 0;
int	rsDamgeOffEvent2 = 0;


int rsDefenseOffEvent = 0;

int	rsCristalEvent = 0;
DWORD	dwBabelPlayTime = 0;
int		BabelPlayField = -1;


char *MonsterPath = "GameServer\\monster\\";
char *ItemPath = "GameServer\\OpenItem\\";
char *szNpcInfoPath = "GameServer\\npc\\";
char *szFieldInfoPath = "GameServer\\Field\\";
char *HackLogDirectory = "LogFile";
char *LogDirectory = "LogFile";
char *DebugLogDirectory = "LogDebug";
char *AdminLogDirectory = "LogAdmin";


char *EventLogDirectory = "EventLog";


static char *szDebugServer = "penguin-pc";

int	DefaultItemCount;


static int	ChatBuffCnt;
static char TransTemp[1024];
static char	szChkID[ACCOUNT_SIZE];



smCHAR_INFO chrMonsterList[CHR_MONSTER_MAX];
smCHAR_MONSTER_INFO chrMonInfoList[CHR_MONSTER_MAX];
rsPLAYINFO rsPlayInfo[CONNECTMAX];
static CHATBUFF ChatBuff[CHATBUFF_MAX];
sDEF_ITEMINFO DefaultItems[DEF_ITEM_MAX];
smCHAR chrAutoPlayer[AUTOPLAYER_MAX];

smCHAR_INFO	*chrNpcMonsterInfo = 0;

DWORD	dwConnectCount = 0;
DWORD	rsAutoPlayTransCount = 0;


rsCURRENCY_LOG	CurrencyLog;


int ActivePlayCounter;
int	srAutoPlayCount = 0;

smCHAR		*lpActiveChar;

time_t		tServerTime = 0;

char *rsRecordDataBuff = 0;


int			srAcceptErrorCount = 0;
int			srLastAcceptRsult = 0;
int			srRouteErrorCount = 0;
int			srLogFailedCount = 0;


static int			spJobCode = 0;
static int			spItemNormal = 0;
static DWORD		spJobCodeTime = 0;


static int			spTimeAdjust = 0;
static DWORD		spTimeAdjustTime = 0;


char	*szLogItemDataDirectory = "LogItemData";



rsUSER_LIST_TOP10	rsUserListDamageTop10;





#ifdef _LANGUAGE_ENGLISH
#ifdef _LANGUAGE_PHILIPIN
#define	rsBLESSCASTLE_TAX_TIME			23
#else
#define	rsBLESSCASTLE_TAX_TIME			4
#endif
#else
#ifdef _LANGUAGE_VEITNAM
#define	rsBLESSCASTLE_TAX_TIME			23
#else
#define	rsBLESSCASTLE_TAX_TIME			2
#endif
#endif

rsBLESS_CASTLE		rsBlessCastle;





int rsRecvSystemInfo(rsPLAYINFO *lpPlayInfo, void *Buff);

int rsInit_SerToServer();

int	rsDisconnectSystemLine(smWINSOCK *lpsmSock);


int DisconnectUser(smWINSOCK *lpsmSock);

int SaveThrowItem(rsPLAYINFO *lpPlayInfo, DWORD dwCode, DWORD dwKey, DWORD dwSum);

int rsLogAccount(rsPLAYINFO *lpPlayInfo, char *szID, char *szPassword);

int rsGetLogOnQueCount();


int RecordHackLogFile(rsPLAYINFO *lpPlayInfo, void *lpTransCommand);


int RecordDebugPlayLogFile(rsPLAYINFO *lpPlayInfo);

int RecordMixItem(rsPLAYINFO *lpPlayInfo, sITEMINFO *lpSrcItem, sITEMINFO *lpMixItem);

int RecordAgingItem(rsPLAYINFO *lpPlayInfo, sITEMINFO *lpSrcItem, sITEMINFO *lpMixItem, int Mode);



int	InitCrackFinding();

int rsSendNetLOG(rsPLAYINFO *lpPlayInfo);

int RecordCollectMoney(rsPLAYINFO *lpPlayInfo, int Money);

int RecordDeleteCharacter(const char *szID, char *szIP, smCHAR_INFO *lpCharInfo);

int RecordGetHighItem(rsPLAYINFO *lpPlayInfo, struct STG_ITEMS *lpStgItem);

int rsCheckChildServer(char *szIP);


int	rsShutDown();


int RecordSmeltingItem(rsPLAYINFO *lpPlayInfo, sITEMINFO *lpSmeltingItem);

int RecordManufactureItem(rsPLAYINFO *lpPlayInfo, sITEMINFO *lpManufactureItem);


int RecordMixtureResetItem(rsPLAYINFO *lpPlayInfo, sITEMINFO *lpMixtureResetItem);


int RecordMovieBloodyBattleItem(rsPLAYINFO *lpPlayInfo, sITEMINFO *lpMovieBloodyBattleItem);

class STG_AREA;


int rsOpenEventMonster(int EventCode, int wParam, int lParam, int sParam);

int rsReOpenEventMonster(STG_AREA *lpStgArea, smCHAR *lpChar);

int rsCloseEventMonster(int EventCode);

int rsPutItem(rsPLAYINFO *lpPlayInfo, DWORD dwItemCode);

int rsPutItem(rsPLAYINFO *lpPlayInfo, DWORD dwItemCode, int spJobCode);

int rsPutItemUnique(rsPLAYINFO *lpPlayInfo, DWORD dwItemCode, int spJobCode, DWORD dwUniqueCode);


int rsPutItem2(rsPLAYINFO *lpPlayInfo, sITEMINFO *lpItem);

int rsCheck_ChageJob(rsPLAYINFO *lpPlayInfo, int NewCnageJob);

int CreatePresentItem(DWORD dwItemCode, STG_AREA *lpStgArea, int x, int y, int z, int count);



int rsOpenBossMonster(STG_AREA *lpStgArea, sBOSS_MONSTER *lpBossMonster);

int rsCharChanger(smCHAR *lpChar, smCHAR_INFO *lpCharInfo, smCHAR_MONSTER_INFO *lpMonInfo);


int	rsInitHardCoreEvent();

int SendOpenCollectMoney(smWINSOCK *lpsmSock);

int rsCheckHardCoreEventArea(int x, int y, int z);

int	rsTransUpdateSod(rsPLAYINFO *lpPlayInfo);



STG_AREA *FindStageField(int x, int z);

extern TRANS_SERVER_LIST	TransServerList;
extern rsSERVER_CONFIG		rsServerConfig;

int rsSendServerList(smWINSOCK *lpsmSock, int ClanTicket);


int rsSendDataServer(smWINSOCK *lpsmSock, void *szData);

int rsSendGameServer(smWINSOCK *lpsmSock, void *szData);

int rsSendAreaServer(smWINSOCK *lpsmSock, void *szData);


int	rsSendCommandUser(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND_EX	*lpTransCommandEx);


int	rsRecordFixExp(rsPLAYINFO *lpPlayInfo);


int rsAddBackListID(const char *szID, DWORD dwTime);

DWORD rsCheckBackListID(char *szID);

int rsResetBackList();

int rsFreekBackListID(char *szID);

int rsShowBlackList(smWINSOCK *lpsmSock, char *szID);

int RecordJobChanger(rsPLAYINFO *lpPlayInfo);

int	rsCheckBlockUserFile(char *szID);

int rsAddBlockUserFile(const char *szID, char *szLog);

int rsSendGameServerExp(rsPLAYINFO *lpPlayInfo);


int	rsCheckEnableIP(DWORD dwUserIP);

int	rsCheckDisableIP(DWORD dwUserIP);

DWORD GetSwapIPCode(char *szIP);

int	rsCheckAdminIP(DWORD dwUserIP);

int	rsCheckSystemIP(DWORD dwUserIP);

int	rsCheckLoginServerIP(DWORD dwUserIP);


int	rsAddInvenItem(rsPLAYINFO *lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum);

int	rsDeleteInvenItem(rsPLAYINFO *lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum);

int	rsFindInvenItem(rsPLAYINFO *lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum);

int	rsCheckInvenItem(rsPLAYINFO *lpPlayInfo, DWORD dwCode);


int	rsCheck_ItemSecCode(rsPLAYINFO *lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum, int Money, DWORD dwSeCode_0, DWORD dwSeCode_1, DWORD dwSeCode_2, DWORD dwSeCode_3, int *pPotionCount);

int	rsRegist_ItemSecCode(rsPLAYINFO *lpPlayInfo, TRANS_ITEMINFO *lpTransItemInfo, int NewItem);

int	rsRegist_ItemSecCode(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND_EX *lpTransCommandEx);


int Record_TempLogFile(char *szMessage);

int Record_BillingLogFile(rsPLAYINFO *lpPlayInfo, DWORD wParam, DWORD lParam, DWORD sParam, DWORD eParam);

int Record_DeadUser(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);


int RecordShutdownLOG(int LogCode, int LParam, int SParam);



int rsLoadCopiedItemList();

int rsRemoveCopiedItemList();

int rsCheckCopiedItem(sITEMINFO *lpItem);

int rsCheckCopiedItem(DWORD dwCode, DWORD dwHead, DWORD dwChkSum);


int rsSend_ResultSOD(rsPLAYINFO *lpPlayInfo, int Point, int KillCount, int TotalPoint, int TotalSucessUser, int TotalUser, int ClassCode);

int	rsRecvSkillPartyUser(TRANS_PARTY_SKILL *lpTransPartySkill);

int rsRecvProcessSkill(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);

int rsCancelSkill(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);

int rsUpdateSkill(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);


int rsClanUpdate(rsPLAYINFO *lpPlayInfo, TRANS_CLAN_COMMAND_USER *lpTransClanUser);


int rsRecvYahooMotion(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);


rsPLAYINFO *FindUserFromName(char *szName);



int	rsPushKillMonster(smCHAR *lpChar, rsPLAYINFO *lpPlayInfo, STG_AREA *lpStgArea);



int	rsSaveAdminCommand(rsPLAYINFO *lpPlayInfo, char *szChatCommand, int Level);

int	rsRecordAdminCommand(rsPLAYINFO *lpPlayInfo, char *szChatCommand, int Level);

AccountTypes getSecurityLevel(rsPLAYINFO *lpPlayInfo);

int rsRecvStarPoint(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);

int rsRecvSodClanCash(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);

int rsRecvGiveMoney(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);

int rsRecvPaymentMoney(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);

DWORD rsOpenEventPuzzleItem(rsPLAYINFO *lpPlayInfo, smCHAR *lpChar);

int	rsTrade_PersonalShop(rsPLAYINFO *lpPlayInfo, rsPLAYINFO *lpPlayInfo2, smTRANS_COMMAND_BUFF *lpTransCommandBuff);

int	rsUseLovelyItem(rsPLAYINFO *lpPlayInfo, DWORD	dwItemCode);

int	rsMorifEventMessage(smCHAR *lpChar);

int	rsMollyWolfEventMessage(smCHAR *lpChar);

int	rsQuestMasterMessage(smCHAR *lpChar, rsPLAYINFO *lpPlayInfo);

int	rsSantaGoblinEventMessage(smCHAR *lpChar);




int	rsChichenDayEventMessage(smCHAR *lpChar);


int rsGetQuestCommand(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);


int	rsSetNoticeMessage(char *szMessage);


int rsInit_Castle();

int	rsStart_CombatCastle();

int	rsEnd_CombatCastle(int DefenceFlag);

int	rsEnd_CombatCastle();

int	rsEasy_CastleMode();

int rsMain_CombatCastle();

int	rsSelectDamageClanTop10(smCHAR *lpChar, rsUSER_LIST_TOP10 *lpUserListDamageTop10);

int	rsRecvBlessCastleInfoFromGameServer(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND_EX *lpTransCommand);

int	rsSendBlessCastleInfoToDataServer(rsPLAYINFO *lpPlayInfo);

int	rsBlessCastle_SoulFountainMain();

int rsLoadCastleInfo();

int	rsSaveCastleInfo();

int RecordBlessCastleLOG(rsUSER_LIST_TOP10 *lpUserListDamageTop10);

int RecordBlessCastleSetup(rsPLAYINFO *lpPlayInfo, smTRANS_BLESSCASTLE *lpBlessCastleSetup);


int rsCheck_BlessCastleClanSkill(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);

int rsSendBlessCastleClanSkill(rsPLAYINFO *lpPlayInfo);

int	rsOpenSiegeCastleItem(DWORD dwItemCode, int x, int y, int z, rsPLAYINFO *lpPlayInfo);


int rsCheckPlayField(rsPLAYINFO *lpPlayInfo);

int rsStartUser_PresentItem(rsPLAYINFO *lpPlayInfo);

DWORD rsLowLevelItem(rsPLAYINFO *lpPlayInfo, smCHAR *lpChar);

int rsRecvUpdateServerParam(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);


int rsSendUserID_MainServer(rsPLAYINFO *lpPlayInfo);
int rsRecvUserID_MainServer(rsPLAYINFO *lpPlayInfo, smTRANS_CHAR_COMMAND2 *lpTransCharCommand);


int rsRecvHackTrap(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCharCommand);

#ifdef _CHECK_MESH

int rsRecvCheckItemMesh(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);
#endif


int	rsSendCloseClient(rsPLAYINFO *lpPlayInfo);


int rsPutItem_TreasureBox(rsPLAYINFO *lpPlayInfo, DWORD Code);


int rsPutItem_CapsuleItem(rsPLAYINFO *lpPlayInfo, DWORD Code);



int rsFiltChatMsg(rsPLAYINFO *lpPlayInfo, char *szMsg, int len);
int rsRecvEventGame(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand);

int Event_UserInfo_Init(rsPLAYINFO *lpPlayInfo, WORD sTime);



#define	ITEMLOG_GET				0
#define	ITEMLOG_PUT				6
#define	ITEMLOG_MIXING			3
#define	ITEMLOG_MIXLOST			9
#define	ITEMLOG_AGING			4
#define	ITEMLOG_AGINGLOST		10
#define	ITEMLOG_AGINGUP			12
#define	ITEMLOG_BUYSHOP			5
#define	ITEMLOG_SELLSHOP		7
#define	ITEMLOG_TRADE			8
#define	ITEMLOG_USED			11
#define	ITEMLOG_EXPRESS			13
#define	ITEMLOG_GETWING			14
#define	ITEMLOG_WINGLOST		15
#define	ITEMLOG_BUYSTAR			16

#define	ITEMLOG_AGING_2UP		17
#define	ITEMLOG_AGING_2DOWN		18
#define	ITEMLOG_AGING_1DOWN		19
#define	ITEMLOG_AGING_KEEP		20

#define	ITEMLOG_PRESENT			21
#define	ITEMLOG_MYSHOP			22

#define	ITEMLOG_USE_ALCHMY		24
#define	ITEMLOG_LOST_ALCHMY		25
#define	ITEMLOG_GET_ALCHMY		26

#define	ITEMLOG_GET_RECON		27
#define	ITEMLOG_LOST_RECON		28
#define ITEMLOG_SMELTING_LOST	29		
#define ITEMLOG_SMELTING_GET	30		
#define ITEMLOG_MANUFACTURE_LOST 31		
#define ITEMLOG_MANUFACTURE_GET 32		
#define ITEMLOG_MANUFACTURE_FAIL 33		
#define ITEMLOG_MIXTURE_RESET_LOST	34		
#define ITEMLOG_MIXTURE_RESET_FAIL	35		
#define ITEMLOG_MIXTURE_RESET_GET	36		


int	rsRecord_ItemLOG(rsPLAYINFO *lpPlayInfo, DWORD dwItemCode, DWORD	dwHead, DWORD dwChkSum, int Flag);

int	rsRecord_ItemLog2(rsPLAYINFO *lpPlayInfo, DWORD dwItemCode, DWORD	dwHead, DWORD dwChkSum, int Flag);

int	rsRecord_ItemLog_Change(rsPLAYINFO *lpPlayInfo, DWORD dwItemCode, DWORD	dwHead, DWORD dwChkSum,
	DWORD dwItemCode2, DWORD	dwHead2, DWORD dwChkSum2, int Flag);

int	rsRecord_ItemLost(rsPLAYINFO *lpPlayInfo, DWORD *lpItemCode, DWORD *lpHead, DWORD *lpChkSum, int Flag);

int	rsRecord_ItemLog_Trade(rsPLAYINFO *lpPlayInfo, rsPLAYINFO *lpPlayInfo2, TRANS_TRADE_ITEMKEY *lpTransTradeItemKey);

int	rsRecord_ItemLog_Post(rsPLAYINFO *lpPlayInfo, DWORD dwItemCode, DWORD	dwHead, DWORD dwChkSum, DWORD dwGCode, char *szTelNum, int Flag);


int rsRecord_SmeltingItemLOG(rsPLAYINFO *lpPlayInfo, DWORD *lpItemCode, DWORD *lpHead, DWORD *lpChkSum, int Flag);

int rsRecord_ManufactureItemLOG(rsPLAYINFO *lpPlayInfo, DWORD *lpItemCode, DWORD *lpHead, DWORD *lpChkSum, int Flag);


int rsRecord_MixtureResetItemLOG(rsPLAYINFO *lpPlayInfo, sMIXTURE_RESET_ITEM_SERVER *pMixtureResetItem_Server, int Flag);




int rsSendAreaOpenKidMonster(rsPLAYINFO	*lpPlayInfo, smCHAR *lpChar);
int rsOpenKidMonster(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand, int mon_Num);


int rsSendAreaOpenSODGuardMonster(rsPLAYINFO *lpPlayInfo, smCHAR *lpChar);
int rsOpenSODGuardMonster(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand, int mon_Num);




struct	smTRANS_SYSTEM_COMMAND
{
	int		size, code;

	int		tCode;
	DWORD	dwObjectSerial;
	DWORD	dwNameCode;
	int		x, y, z;

	DWORD	Param[32];
};

#define	smTRANS_SYSCODE_CONNECT			0x1000
#define	smTRANS_SYSCODE_KILL_MONSTER	0x1100
#define	smTRANS_SYSCODE_GET_MONEY		0x1110
#define	smTRANS_SYSCODE_GET_ITEM		0x1112
#define	smTRANS_SYSCODE_DMG_USER_LIST	0x1120
#define	smTRANS_SYSCODE_NETSTATE		0x1200
#define	smTRANS_SYSCODE_NETSUCCESS		0x1250

#define	smTRANS_SYSCODE_CONNECT_USER	0x1300
#define	smTRANS_SYSCODE_USER_FAILED		0x1302
#define	smTRANS_SYSCODE_EXP_INFO		0x1310


#define	SER_TO_SERVER_SOCKET_MAX	4
#define	SER_TO_SERVER_SOCKET_MASK	3

smWINSOCK	*lpsmSock_SerToServer[SER_TO_SERVER_SOCKET_MAX] = { 0,0,0,0 };
DWORD		dwSerToSerIP = 0;
DWORD		dwSerToSer_Count = 0;
char		szSerToSerIP[32];

#define	SER_TO_LOGIN_SOCKET_MAX	16
rsPLAYINFO	*lpPlayInfo_LoginServer[SER_TO_LOGIN_SOCKET_MAX] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
DWORD		dwSerToLogin_Count = 0;
DWORD		dwSerToLogin_Num = 0;


rsKILL_MONSTER_INFO	rsKillMonster_Que[srMONSTER_KILL_QUE_MAX + 10];
int	rsKillMonster_Push = 0;
int	rsKillMonster_Pop = 0;

HANDLE	hSerToServer_Thread = 0;
DWORD	dwSerToServer_ID = 0;

int	rsSystemNetCount = 0;
int	rsSystemLineConnCount = 0;
int rsSystemLineFailedCount = 0;
int rsSystemLinePlayCount = 0;



int	rsGetSystemLineCount();
int	rsSetSerToLoginLine();
int rsSendPacketToLoginLine(char *szBuff, int size);


smWINSOCK	*rsFindNextSertoServerSock();
int	rsSendMoneyToSystemLine(rsPLAYINFO *lpPlayInfo, int Money);
int rsSendCharInfoToLoginServer(rsPLAYINFO *lpPlayInfo);

int	rsMonHuntCount = 0;
int	rsMonOpenCount = 0;
int	rsItemOpenCount = 0;
int	rsMoneyTotalCount = 0;
int	rsItemBuffOverCount = 0;


int	rsSendMoneyToUser(rsPLAYINFO *lpPlayInfo, int Money);

POINT3D	*lprsFixedPoint = 0;


extern int	Server_LimitVersion;


int Server_AllocMemory()
{
	
	
	
	
	
	

	memset(chrMonsterList, 0, sizeof(chrMonsterList));
	memset(chrMonInfoList, 0, sizeof(chrMonInfoList));
	memset(rsPlayInfo, 0, sizeof(rsPlayInfo));
	memset(ChatBuff, 0, sizeof(ChatBuff));
	memset(DefaultItems, 0, sizeof(DefaultItems));
	memset(chrAutoPlayer, 0, sizeof(chrAutoPlayer));

	
	
	
	
	
	
	
	

	return TRUE;
}


int Server_RemoveMemory()
{
	
	
	
	
	

	memset(chrMonsterList, 0, sizeof(chrMonsterList));
	memset(chrMonInfoList, 0, sizeof(chrMonInfoList));
	memset(rsPlayInfo, 0, sizeof(rsPlayInfo));
	memset(ChatBuff, 0, sizeof(ChatBuff));
	memset(DefaultItems, 0, sizeof(DefaultItems));
	memset(chrAutoPlayer, 0, sizeof(chrAutoPlayer));

	return TRUE;
}



int rsRefreshConfig()
{
	return TRUE;
}






int rsLogOut(rsPLAYINFO *lpPlayInfo)
{
	int BlockTime;
	int Money;

	if(lpPlayInfo && lpPlayInfo->getAccount().size() && lpPlayInfo->lpsmSock)
	{

		if(lpPlayInfo->getName().size())
		{
			Money = lpPlayInfo->ServerMoney - lpPlayInfo->WareHouseMoney;

			RecordLogSql(LOG_SQL_LOGOUT, lpPlayInfo->lpsmSock->szIPAddr, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(), lpPlayInfo->szGPCode, 1, lpPlayInfo->smCharInfo.JOB_CODE,
				GetExp64(&lpPlayInfo->smCharInfo), lpPlayInfo->smCharInfo.Level, Money);
		}


		if(rsServerConfig.PresentLevel > 0 && lpPlayInfo->spLevel_Start > 0 && rsServerConfig.PresentLevel > lpPlayInfo->CharLevelMax)
		{

			lpPlayInfo->smCharInfo.Level = GetLevelFromExp(GetExp64(&lpPlayInfo->smCharInfo));

			if(lpPlayInfo->spLevel_Start < rsServerConfig.PresentLevel && lpPlayInfo->smCharInfo.Level >= rsServerConfig.PresentLevel)
			{


				rsAddPostBox_Present(lpPlayInfo);


				rsRecord_ItemLog_Post(lpPlayInfo, 99, 0, 0, lpPlayInfo->smCharInfo.Level, 0, ITEMLOG_PRESENT);

			}
		}


		if(lpPlayInfo->BlockTime == 0x7FFFFFFF)
			BlockTime = 60 * 24 * 30 * 3;
		else
			BlockTime = lpPlayInfo->BlockTime / (60 * 1000);


		RecordGameLogSql(GAMELOG_SQL_LOGOUT, lpPlayInfo->lpsmSock->szIPAddr,
			lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(), lpPlayInfo->szGPCode,
			lpPlayInfo->smCharInfo.JOB_CODE, lpPlayInfo->szGuid, BlockTime);



		if(lpPlayInfo->szGPCode[0])
		{

			bSql_Logout(lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(), lpPlayInfo->lpsmSock->szIPAddr, lpPlayInfo->szGPCode,
				lpPlayInfo->DisuseDay, lpPlayInfo->UsePeriod, lpPlayInfo->szGuid, lpPlayInfo->Bl_RNo);

		}

		if(lpPlayInfo->ClanTicketCode && lpPlayInfo->getName().size())
			bClan_UserTicket(lpPlayInfo, 1);



		rsRecordFixExp(lpPlayInfo);

	}


	if(rsServerConfig.ExpGameTimeMode)
	{
		if(lpPlayInfo->dwExpGameTimeCheck)
		{
			bSql_GetExpGameTime(lpPlayInfo, lpPlayInfo->dwExpGameTime / 1000);
		}
	}

	return TRUE;
}



int InitMonster()
{

	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;
	char	szFindPath[64];
	char	szFilePath[64];

	chrMonsterCnt = 0;

	ZeroMemory(chrMonsterList, sizeof(smCHAR_INFO)*CHR_MONSTER_MAX);
	ZeroMemory(chrMonInfoList, sizeof(smCHAR_MONSTER_INFO)*CHR_MONSTER_MAX);

	strcpy_s(szFindPath, MonsterPath);
	lstrcat(szFindPath, "*.inf");

	hFindHandle = FindFirstFile(szFindPath, &fd);
	if(hFindHandle != INVALID_HANDLE_VALUE)
	{
		while(1)
		{
			strcpy_s(szFilePath, MonsterPath);
			lstrcat(szFilePath, fd.cFileName);

			smCharDecode(szFilePath, &chrMonsterList[chrMonsterCnt], &chrMonInfoList[chrMonsterCnt], 0);


			chrMonInfoList[chrMonsterCnt].dwAutoCharCode = GetSpeedSum(chrMonsterList[chrMonsterCnt].szName);


			if(rsServerConfig.TestSeverMode)
			{
				chrMonsterList[chrMonsterCnt].Exp *= 4;
				chrMonInfoList[chrMonsterCnt].GetExp *= 4;
			}

			ReformCharForm(&chrMonsterList[chrMonsterCnt]);

			chrMonsterCnt++;

			if(FindNextFile(hFindHandle, &fd) == FALSE) break;
			if(chrMonsterCnt >= CHR_MONSTER_MAX) break;
		}
	}
	FindClose(hFindHandle);



	int cnt, cnt2;


	rsInitHardCoreEvent();


	for(cnt = 0; cnt < chrMonsterCnt; cnt++)
	{


		if(chrMonsterList[cnt].szModelName[0])
		{
			LoadOftenMeshPattern(chrMonsterList[cnt].szModelName);
		}


		if(lstrcmp(chrMonsterList[cnt].szName, srEventMonName1) == 0)
		{
			chrNpcMonsterInfo = &chrMonsterList[cnt];
		}


		for(cnt2 = 0; cnt2 < srCRISTAL_MAX; cnt2++)
		{
			if(lstrcmp(chrMonsterList[cnt].szName, srCristalMonster[cnt2].szName) == 0)
			{
				srCristalMonster[cnt2].lpCharInfo = &chrMonsterList[cnt];
			}
		}
		for(cnt2 = 0; cnt2 < srCRISTAL_MAX; cnt2++)
		{
			if(lstrcmp(chrMonsterList[cnt].szName, srCristalMonsterBoss[cnt2].szName) == 0)
			{
				srCristalMonsterBoss[cnt2].lpCharInfo = &chrMonsterList[cnt];
			}
		}
		for(cnt2 = 0; cnt2 < srSKILL_MONSTER_MAX; cnt2++)
		{
			if(lstrcmp(chrMonsterList[cnt].szName, srSkillMonster[cnt2].szName) == 0)
			{
				srSkillMonster[cnt2].lpCharInfo = &chrMonsterList[cnt];
			}
		}
		for(cnt2 = 0; cnt2 < srBC_MONSTER_TOTAL; cnt2++)
		{
			if(lstrcmp(chrMonsterList[cnt].szName, srBillingCrystalMonster[cnt2].szName) == 0)
			{
				srBillingCrystalMonster[cnt2].lpCharInfo = &chrMonsterList[cnt];
			}
		}


		for(cnt2 = 0; cnt2 < 7; cnt2++)
		{
			if(lstrcmp(chrMonsterList[cnt].szName, srCristalMonsterEnemy[cnt2].szName) == 0)
			{
				srCristalMonsterEnemy[cnt2].lpCharInfo = &chrMonsterList[cnt];
			}
		}


		for(cnt2 = 0; cnt2 < 7; cnt2++)
		{
			if(lstrcmp(chrMonsterList[cnt].szName, srCristalMonsterEnemy2[cnt2].szName) == 0)
			{
				srCristalMonsterEnemy2[cnt2].lpCharInfo = &chrMonsterList[cnt];
			}
		}


		for(cnt2 = 0; cnt2 < 7; cnt2++)
		{
			if(lstrcmp(chrMonsterList[cnt].szName, srCristalMonsterEnemy3[cnt2].szName) == 0)
			{
				srCristalMonsterEnemy3[cnt2].lpCharInfo = &chrMonsterList[cnt];
			}
		}


		for(cnt2 = 0; cnt2 < 7; cnt2++)
		{
			if(lstrcmp(chrMonsterList[cnt].szName, srCristalMonsterEnemy4[cnt2].szName) == 0)
			{
				srCristalMonsterEnemy4[cnt2].lpCharInfo = &chrMonsterList[cnt];
			}
		}


		for(cnt2 = 0; cnt2 < 7; cnt2++)
		{
			if(lstrcmp(chrMonsterList[cnt].szName, srCristalMonsterEnemy5[cnt2].szName) == 0)
			{
				srCristalMonsterEnemy5[cnt2].lpCharInfo = &chrMonsterList[cnt];
			}
		}


		for(cnt2 = 0; cnt2 < 7; cnt2++)
		{
			if(lstrcmp(chrMonsterList[cnt].szName, srCristalMonsterEnemy6[cnt2].szName) == 0)
			{
				srCristalMonsterEnemy6[cnt2].lpCharInfo = &chrMonsterList[cnt];
			}
		}


		for(cnt2 = 0; cnt2 < 7; cnt2++)
		{
			if(lstrcmp(chrMonsterList[cnt].szName, srCristalMonsterEnemy7[cnt2].szName) == 0)
			{
				srCristalMonsterEnemy7[cnt2].lpCharInfo = &chrMonsterList[cnt];
			}
		}


		for(cnt2 = 0; cnt2 < 7; cnt2++)
		{
			if(lstrcmp(chrMonsterList[cnt].szName, srCristalMonsterEnemy8[cnt2].szName) == 0)
			{
				srCristalMonsterEnemy8[cnt2].lpCharInfo = &chrMonsterList[cnt];
			}
		}


		for(cnt2 = 0; cnt2 < 7; cnt2++)
		{
			if(lstrcmp(chrMonsterList[cnt].szName, srCristalMonsterEnemy9[cnt2].szName) == 0)
			{
				srCristalMonsterEnemy9[cnt2].lpCharInfo = &chrMonsterList[cnt];
			}
		}


		for(cnt2 = 0; cnt2 < MARVELCRISTAL_MAX; cnt2++)
		{
			if(lstrcmp(chrMonsterList[cnt].szName, srMarvelCristalMonster[cnt2].szName) == 0)
			{
				srMarvelCristalMonster[cnt2].lpCharInfo = &chrMonsterList[cnt];
			}
		}



		if(chrMonsterList[cnt].wPlayClass[0] == MONSTER_CLASS_HAMMER)
		{
			if(srHammerMonsterCount < srHAMMER_MONSTER_MAX)
				srCharInfo_HammerMonster[srHammerMonsterCount++] = &chrMonsterList[cnt];
		}


		if(chrMonInfoList[cnt].szName[0] && !chrMonsterList[cnt].szName[0])
		{
			strcpy_s(chrMonsterList[cnt].szName, chrMonInfoList[cnt].szName);
			chrMonInfoList[cnt].szName[0] = 0;
		}

	}


	return TRUE;
}


int ConvertMonsterNames()
{
	int cnt;

	for(cnt = 0; cnt < chrMonsterCnt; cnt++)
	{

		if(chrMonInfoList[cnt].szName[0] && chrMonsterList[cnt].szName[0])
		{
			strcpy_s(chrMonsterList[cnt].szName, chrMonInfoList[cnt].szName);
			chrMonInfoList[cnt].szName[0] = 0;
		}
	}

	return TRUE;
}


char *szUserModelPath = "char\\tmABCD";


int rsCheckActiveFile(char *szFile)
{
	WIN32_FIND_DATA	fd;
	HANDLE	hFindHandle;

	hFindHandle = FindFirstFile(szFile, &fd);
	if(hFindHandle == INVALID_HANDLE_VALUE) return FALSE;
	FindClose(hFindHandle);


	int cnt, len;
	char szFileName[128] = { 0 };

	len = lstrlen(szFile);
	memcpy(szFileName, szFile, len + 1);

	for(cnt = len - 1; cnt >= 0; cnt--)
	{
		if(szFileName[cnt] == '\\')
		{
			szFileName[cnt] = 0;
			break;
		}
	}

	if(lstrcmpi(szFileName, szUserModelPath) != 0)
		return FALSE;

	return TRUE;
}




int InitItems()
{
	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;
	char	szFindPath[64];
	char	szFilePath[64];
	sDEF_ITEMINFO	DefItem;

	DefaultItemCount = 0;

	strcpy_s(szFindPath, ItemPath);
	lstrcat(szFindPath, "*.txt");

	hFindHandle = FindFirstFile(szFindPath, &fd);
	if(hFindHandle != INVALID_HANDLE_VALUE)
	{
		while(1)
		{
			strcpy_s(szFilePath, ItemPath);
			lstrcat(szFilePath, fd.cFileName);

			DecodeItemInfo(szFilePath, &DefaultItems[DefaultItemCount]);

			memcpy(&DefItem, &DefaultItems[DefaultItemCount], sizeof(sDEF_ITEMINFO));
			SetLowerItem(&DefItem);


			DefItem.Item.BackUpKey = 0;
			DefItem.Item.BackUpChkSum = 0;
			DefItem.Item.dwCreateTime = 0;

			DefaultItems[DefaultItemCount].DefCompressDataLen = EecodeCompress((BYTE *)&DefItem.Item, (BYTE *)DefaultItems[DefaultItemCount].DefCompressData, sizeof(sITEMINFO));

			DefaultItemCount++;

			if(FindNextFile(hFindHandle, &fd) == FALSE) break;
			if(DefaultItemCount >= DEF_ITEM_MAX) break;
		}
	}
	FindClose(hFindHandle);


	return TRUE;
}


char *SetFieldInfoPath(char *SaveBuff, char *szFieldPath, char *InfoExt)
{
	int cnt;
	int len;
	char *szFile;

	len = lstrlen(szFieldPath);
	cnt = len - 1;

	szFile = szFieldPath;

	while(cnt > 0)
	{
		if(szFieldPath[cnt] == '\\')
		{
			szFile = &szFieldPath[cnt + 1];
			break;
		}
		cnt--;
	}

	wsprintf(SaveBuff, "%s%s.%s", szFieldInfoPath, szFile, InfoExt);

	return SaveBuff;
}


DWORD	dwServ_GameTimeHour;
DWORD	dwServ_NightDay;


DWORD	GetGameTimeHour()
{
	DWORD	dwTime;

	dwTime = GetCurrentTime() - dwOffsetTime;
	dwTime = (dwTime / GAME_WORLDTIME_MIN) / 60;
	dwTime = dwTime - (((int)(dwTime / 24)) * 24);

	return dwTime;
}


int rsGetUserCounter(int Counter)
{
	return Counter;

}






#define START_POINT_MAX			8
#define START_POINT_MASK		(START_POINT_MAX-1)

POINT	StartPointNpc[START_POINT_MAX] = {
	{ 1692 , -584 },
	{ 34 , -618 },
	{ -741 , 877 },
	{ 1000 , 1000 }
};

POINT	StartPoint[START_POINT_MAX] = {
	{	-1500,	-2800 },
	{	600,	-3200 },
	{	840,	-4000 },
	{	-90,	-5000 },
	{	-900,	-6500 },
	{	-1600,	-7100 },
	{	-3000,	-7200 },
	{	400,	-6100 }
};



int StartPointCnt = 0;




int	rsLoadCreateItemToHDD(psITEM	*lpItem, char *szFileCode);

int	rsSaveCreateItemToHDD(psITEM	*lpItem);

int	rsSaveAgingItemToHDD(sITEMINFO *lpItem);





rsPLAYINFO *srFindUserFromSerial(DWORD dwObjectSerial)
{
	int cnt;

	if(dwObjectSerial == 0) return NULL;

	for(cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial == dwObjectSerial)
		{
			return &rsPlayInfo[cnt];
		}
	}

	return NULL;
}


smCHAR *srFindCharFromSerial(DWORD dwObjectSerial)
{
	int cnt;

	if(dwObjectSerial == 0) return NULL;

	for(cnt = 0; cnt < AUTOPLAYER_MAX; cnt++)
	{
		if(chrAutoPlayer[cnt].dwObjectSerial == dwObjectSerial &&
			chrAutoPlayer[cnt].Flag)
		{

			return &chrAutoPlayer[cnt];
		}
	}

	return NULL;
}


smCHAR *srFindCharFromSerial(DWORD dwObjectSerial, int AreaNum)
{

	int cnt;
	STG_AREA *lpStgArea;


	if(dwObjectSerial && AreaNum < STAGE_AREA_MAX && StageArea[AreaNum].lpStage)
	{
		lpStgArea = &StageArea[AreaNum];

		for(cnt = 0; cnt < STG_MONSTER_MAX; cnt++)
		{
			if(lpStgArea->lpCharMonster[cnt] && lpStgArea->lpCharMonster[cnt]->dwObjectSerial == dwObjectSerial)
			{
				return lpStgArea->lpCharMonster[cnt];
			}
		}
	}

	return NULL;
}



smCHAR *srFindEmptyChar()
{
	int cnt;

	for(cnt = 0; cnt < AUTOPLAYER_MAX; cnt++)
	{
		if(!chrAutoPlayer[cnt].Flag)
		{
			return &chrAutoPlayer[cnt];
		}
	}

	return NULL;
}



int srSetItemFromCode(psITEM *lpsItem, char *szCoed)
{
	int cnt;
	DWORD dwCode;
	DWORD dwCodeMask1, dwCodeMask2;

	for(cnt = 0; cnt < MAX_ITEM; cnt++)
	{
		if(lstrcmpi(szCoed, sItem[cnt].LastCategory) == 0)
		{
			dwCode = sItem[cnt].CODE; break;
		}
	}

	if(cnt >= MAX_ITEM) return FALSE;

	for(cnt = 0; cnt < DefaultItemCount; cnt++)
	{
		if(DefaultItems[cnt].Item.CODE == dwCode && !DefaultItems[cnt].Item.UniqueItem)
		{
			CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt], spJobCode, spItemNormal);


			if(spTimeAdjust)
			{
				dwCodeMask1 = lpsItem->ItemInfo.CODE&sinITEM_MASK2;
				dwCodeMask2 = lpsItem->ItemInfo.CODE&sinITEM_MASK3;
				if((dwCodeMask1 == sinDA1 || dwCodeMask1 == sinDA2) && dwCodeMask2 >= sin31)
				{
					ReformItem_AdjustTime(&lpsItem->ItemInfo, spTimeAdjust);
				}


				if((dwCodeMask1 == sinOA1 && dwCodeMask2 == sin32) || (dwCodeMask1 == sinOR2 && dwCodeMask2 == sin27) ||
					(dwCodeMask1 == sinOA1 && dwCodeMask2 == sin33) || (dwCodeMask1 == sinOR2 && dwCodeMask2 == sin28))
				{
					ReformItem_AdjustTime(&lpsItem->ItemInfo, spTimeAdjust);
				}
			}


			rsSaveCreateItemToHDD(lpsItem);
			return TRUE;
		}
	}


	return FALSE;
}



int srSetItemFromName(psITEM *lpsItem, char *szItemName)
{
	int cnt;

	for(cnt = 0; cnt < DefaultItemCount; cnt++)
	{
		if(lstrcmpi(DefaultItems[cnt].Item.ItemName, szItemName) == 0)
		{
			CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt], spJobCode, spItemNormal);

			rsSaveCreateItemToHDD(lpsItem);
			return TRUE;
		}
	}

	return FALSE;
}


int srSetItemFromLogData(psITEM *lpsItem, char *LogFileCode)
{

	return rsLoadCreateItemToHDD(lpsItem, LogFileCode);
}



int srLinkNpcItem(smCHAR *lpChar)
{
	int cnt, cnt2;
	DWORD	dwCode;

	for(cnt = 0; cnt < lpChar->smMonsterInfo.SellAttackItemCount; cnt++)
	{
		dwCode = (DWORD)lpChar->smMonsterInfo.SellAttackItem[cnt];
		lpChar->smMonsterInfo.SellAttackItem[cnt] = 0;
		for(cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
		{
			if(!DefaultItems[cnt2].Item.UniqueItem && dwCode == DefaultItems[cnt2].Item.CODE)
			{
				lpChar->smMonsterInfo.SellAttackItem[cnt] = &DefaultItems[cnt2];
				break;
			}
		}
	}

	for(cnt = 0; cnt < lpChar->smMonsterInfo.SellDefenceItemCount; cnt++)
	{
		dwCode = (DWORD)lpChar->smMonsterInfo.SellDefenceItem[cnt];
		lpChar->smMonsterInfo.SellDefenceItem[cnt] = 0;
		for(cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
		{
			if(!DefaultItems[cnt2].Item.UniqueItem && dwCode == DefaultItems[cnt2].Item.CODE)
			{
				lpChar->smMonsterInfo.SellDefenceItem[cnt] = &DefaultItems[cnt2];
				break;
			}
		}
	}

	for(cnt = 0; cnt < lpChar->smMonsterInfo.SellEtcItemCount; cnt++)
	{
		dwCode = (DWORD)lpChar->smMonsterInfo.SellEtcItem[cnt];
		lpChar->smMonsterInfo.SellEtcItem[cnt] = 0;
		for(cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
		{
			if(!DefaultItems[cnt2].Item.UniqueItem && dwCode == DefaultItems[cnt2].Item.CODE)
			{
				lpChar->smMonsterInfo.SellEtcItem[cnt] = &DefaultItems[cnt2];
				break;
			}
		}
	}
	return TRUE;
}


int srGetRandomItem(psITEM *lpsItem)
{

	int	rnd;

	ZeroMemory(lpsItem, sizeof(sITEMINFO));

	if(((GetCurrentTime() >> 4) & 0x3) == 0)
	{
		rnd = GetRandomPos(1, 100);
		lpsItem->ItemInfo.CODE = sinGG1 | sin01;
		wsprintf(lpsItem->ItemInfo.ItemName, sinGold, rnd);
		lpsItem->ItemInfo.Money = rnd;
		ReformItem(&lpsItem->ItemInfo);
	}
	else
	{
		rnd = rand() % DefaultItemCount;
		if(DefaultItems[rnd].Item.UniqueItem) return FALSE;
		CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[rnd]);
	}


	return TRUE;
}

#define	OS_TRAN	(sinOS1|sin06)
#define	OS_MUKY	(sinOS1|sin07)
#define	OS_DEBI	(sinOS1|sin08)
#define	OS_ALL	(sinOS1|sin12)


DWORD	dwMorifFieldItem[] = {

	OS_TRAN,	OS_TRAN,	OS_TRAN,	OS_TRAN,

	OS_TRAN,	OS_TRAN,	OS_TRAN,	OS_TRAN,

	OS_TRAN,	OS_MUKY,	OS_MUKY,	OS_MUKY,

	OS_DEBI ,	OS_MUKY,	OS_MUKY,	OS_DEBI ,

	OS_TRAN,	OS_TRAN,	OS_TRAN,	OS_TRAN,

	OS_TRAN,	OS_TRAN,	OS_ALL , 	OS_ALL ,

	OS_DEBI,	OS_DEBI,	OS_ALL ,	OS_ALL ,

	OS_ALL,		OS_TRAN,	OS_TRAN,	OS_ALL,

	OS_TRAN,	OS_TRAN,	OS_TRAN,	OS_TRAN
};


int	srCheckMorifItemField(DWORD dwItemCode, STG_AREA *lpStgArea)
{

	DWORD	dwItemCodeMask = dwItemCode&sinITEM_MASK3;

	if(!lpStgArea || !lpStgArea->lpField) return FALSE;

	DWORD	dwAreaCode = lpStgArea->lpField->FieldCode;

	if(dwAreaCode >= 0 && dwAreaCode < 36)
	{

		if(dwMorifFieldItem[dwAreaCode] == OS_ALL && dwItemCodeMask < sin05)
			return FALSE;

		if(dwItemCodeMask > (dwMorifFieldItem[dwAreaCode] & sinITEM_MASK3))
			return FALSE;
	}

	return TRUE;
}




int srGetMonsterItem(rsPLAYINFO *lpPlayInfo, smCHAR *lpChar, psITEM *lpsItem)
{

	int	rnd;
	int cnt, cnt2;
	int rcnt;
	DWORD dwCode;
	smCHAR_MONSTER_INFO *lpMonInfo = &lpChar->smMonsterInfo;
	STG_AREA *lpStgArea;

	ZeroMemory(lpsItem, sizeof(sITEMINFO));

	if(lpMonInfo->FallItemPerMax == 0 || lpMonInfo->FallItemCount == 0) return FALSE;


	if(rsServerConfig.Event_Mandoo)
	{
		rnd = rand() % 100;
		dwCode = 0;

		if(rnd < 4)
		{

			dwCode = (sinSP1 | sin01);
		}
		else
		{
			if(rnd < 6)
			{

				dwCode = (sinSP1 | sin02);
			}
		}

		if(dwCode)
		{

			for(cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
			{
				if(DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem)
				{
					CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
					return TRUE;
				}
			}
		}
	}


	if(rsServerConfig.Event_ValentineDay)
	{
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);

		if(cnt > 15 || (lpChar->smCharInfo.Level < 20 && cnt>8))
		{
			rnd = rsServerConfig.Event_ValentineDay;
		}

		if(rnd < rsServerConfig.Event_ValentineDay)
		{
			dwCode = 0;
			rnd = rand() % 10;
			if(rnd < 7)
			{

				dwCode = (sinCH1 | sin01);

#ifdef _LANGUAGE_THAI_RING
				dwCode = (sinOR2 | sin01);
#endif
#ifdef _LANGUAGE_JAPANESE_RING
				dwCode = (sinOR2 | sin01);
#endif
			}
			else
			{

				dwCode = (sinCH1 | sin02);
#ifdef _LANGUAGE_THAI_RING
				dwCode = (sinOR2 | sin01);
#endif
#ifdef _LANGUAGE_JAPANESE_RING
				dwCode = (sinOR2 | sin01);
#endif
			}

			if(dwCode)
			{

				for(cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if(DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem)
					{
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}


	if(rsServerConfig.Event_CoupleRing)
	{
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);

		if(cnt > 15 || (lpChar->smCharInfo.Level < 20 && cnt>8))
		{
			rnd = rsServerConfig.Event_CoupleRing;
		}

		if(rnd < rsServerConfig.Event_CoupleRing)
		{
			dwCode = 0;
			dwCode = (sinSP1 | sin16);

			if(dwCode)
			{

				for(cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if(DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem)
					{
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}


	if(rsServerConfig.Event_Watermelon)
	{
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);

		if(cnt > 15 || (lpChar->smCharInfo.Level < 20 && cnt>8))
		{
			rnd = rsServerConfig.Event_Watermelon;
		}

		if(rnd < rsServerConfig.Event_Watermelon)
		{
			dwCode = 0;
			dwCode = (sinSP1 | sin15);

			if(dwCode)
			{

				for(cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if(DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem)
					{
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}


	if(rsServerConfig.Event_Star)
	{
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);

		if(cnt > 15 || (lpChar->smCharInfo.Level < 20 && cnt>8))
		{
			rnd = rsServerConfig.Event_Star;
		}

		if(rnd < rsServerConfig.Event_Star)
		{
			dwCode = 0;
			dwCode = (sinSP1 | sin26);

			if(dwCode)
			{

				for(cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if(DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem)
					{
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}



	if(rsServerConfig.Event_Valentine)
	{
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);

		if(cnt > 15)
		{
			rnd = rsServerConfig.Event_Valentine;
		}

		if(rnd < rsServerConfig.Event_Valentine)
		{
			dwCode = 0;
			dwCode = (sinSP1 | sin35);

			if(dwCode)
			{

				for(cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if(DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem)
					{
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}


	if(rsServerConfig.Event_PristonAlphabet)
	{
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);

		if(cnt > 15 || (lpChar->smCharInfo.Level < 20 && cnt>8))
		{
			rnd = rsServerConfig.Event_PristonAlphabet;
		}

		if(rnd < rsServerConfig.Event_PristonAlphabet)
		{
			dwCode = 0;
			rnd = rand() % 100;
			if(rnd < 15)
			{
				dwCode = (sinSP1 | sin27);
			}
			else if(rnd < 30)
			{
				dwCode = (sinSP1 | sin28);
			}
			else if(rnd < 44)
			{
				dwCode = (sinSP1 | sin29);
			}
			else if(rnd < 58)
			{
				dwCode = (sinSP1 | sin30);
			}
			else if(rnd < 72)
			{
				dwCode = (sinSP1 | sin31);
			}
			else if(rnd < 86)
			{
				dwCode = (sinSP1 | sin32);
			}
			else
				dwCode = (sinSP1 | sin33);

			if(dwCode)
			{

				for(cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if(DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem)
					{
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}





	if(rsServerConfig.Event_WhiteContrast)
	{
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);

		if(cnt > 15)
		{
			rnd = rsServerConfig.Event_WhiteContrast;
		}

		if(rnd < rsServerConfig.Event_WhiteContrast)
		{
			dwCode = 0;
			rnd = rand() % 4;

			if(rnd == 0) dwCode = (sinPR2 | sin09);
			else if(rnd == 1) dwCode = (sinPR2 | sin10);
			else if(rnd == 2) dwCode = (sinPR2 | sin11);
			else dwCode = (sinDR1 | sin10);



			if(dwCode)
			{

				for(cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if(DefaultItems[cnt2].Item.CODE == dwCode)
					{
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}



	if(rsServerConfig.Event_Candydays)
	{
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);

		if(cnt > 15)
		{
			rnd = rsServerConfig.Event_Candydays;
		}

		if(rnd < rsServerConfig.Event_Candydays)
		{
			dwCode = 0;
			dwCode = (sinSP1 | sin36);

			if(dwCode)
			{

				for(cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if(DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem)
					{
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}




	if(rsServerConfig.Event_BlackSmith)
	{
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);

		if(cnt > 15)
		{
			rnd = rsServerConfig.Event_BlackSmith;
		}

		if(rnd < rsServerConfig.Event_BlackSmith)
		{
			dwCode = 0;
			rnd = rand() % 4;

			if(rnd == 0) dwCode = (sinPR2 | sin12);
			else if(rnd == 1) dwCode = (sinPR2 | sin13);
			else if(rnd == 2) dwCode = (sinPR2 | sin14);
			else dwCode = (sinDR1 | sin11);



			if(dwCode)
			{

				for(cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if(DefaultItems[cnt2].Item.CODE == dwCode)
					{
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}



	if(rsServerConfig.Event_MagicalGreen)
	{
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);


		if(cnt > 15)
		{
			rnd = rsServerConfig.Event_MagicalGreen;
		}

		if(rnd < rsServerConfig.Event_MagicalGreen)
		{
			dwCode = 0;

			if(FieldLimitLevel_Table[lpPlayInfo->Position.Area] >= 60)
			{
				dwCode = (sinSP1 | sin38);
			}

			else
			{
				dwCode = (sinSP1 | sin37);
			}


			if(dwCode)
			{

				for(cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if(DefaultItems[cnt2].Item.CODE == dwCode)
					{
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}



	if(rsServerConfig.Event_TearOfKara)
	{
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);

		if(cnt > 15)
		{
			rnd = rsServerConfig.Event_TearOfKara;
		}

		if(rnd < rsServerConfig.Event_TearOfKara)
		{
			dwCode = 0;
			dwCode = (sinSP1 | sin39);

			if(dwCode)
			{

				for(cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if(DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem)
					{
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}



	if(rsServerConfig.Event_MovieBloodyBattle)
	{
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);

		if(cnt > 15 || (lpChar->smCharInfo.Level < 20 && cnt>7))
		{
			rnd = rsServerConfig.Event_PristonAlphabet;
		}

		if(rnd < rsServerConfig.Event_MovieBloodyBattle)
		{
			dwCode = 0;
			rnd = rand() % 100;
			if(rnd < 25)
			{
				dwCode = (sinSP1 | sin60);
			}
			else if(rnd < 50)
			{
				dwCode = (sinSP1 | sin61);
			}
			else if(rnd < 75)
			{
				dwCode = (sinSP1 | sin62);
			}
			else
			{
				dwCode = (sinSP1 | sin63);
			}


			if(dwCode)
			{

				for(cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if(DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem)
					{
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}



	if(rsServerConfig.Event_WhiteDay)
	{
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);

		if(cnt > 15 || (lpChar->smCharInfo.Level < 20 && cnt>8))
		{
			rnd = rsServerConfig.Event_WhiteDay;
		}

		if(rnd < rsServerConfig.Event_WhiteDay)
		{
			dwCode = 0;
			rnd = rand() % 10;
			if(rnd < 7)
			{

				dwCode = (sinCH1 | sin03);
			}
			else
			{

				dwCode = (sinCH1 | sin04);
			}

			if(dwCode)
			{

				for(cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if(DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem)
					{
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}


	if(rsServerConfig.Event_Puzzle && (rand() % 10000) < rsServerConfig.Event_Puzzle)
	{


		dwCode = rsOpenEventPuzzleItem(lpPlayInfo, lpChar);

		if(dwCode)
		{

			for(cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
			{
				if(DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem)
				{
					CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
					return TRUE;
				}
			}
		}
	}

	if(rsServerConfig.Event_NineFox)
	{

		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);
		cnt2 = rsServerConfig.Event_NineFox;

		if(cnt > 15 || (lpChar->smCharInfo.Level < 20 && cnt>10))
		{
			rnd = cnt2;
		}
		else
		{
			if(lpPlayInfo->smCharInfo.Level < 20)
			{
				cnt2 = (rsServerConfig.Event_NineFox * 40) / 100;
			}
			else if(lpPlayInfo->smCharInfo.Level < 40)
			{
				cnt2 = (rsServerConfig.Event_NineFox * 60) / 100;
			}
			else if(lpPlayInfo->smCharInfo.Level < 60)
			{
				cnt2 = (rsServerConfig.Event_NineFox * 80) / 100;
			}
		}

		if(rnd < cnt2)
		{

			if((rand() % 2) == 0)
				dwCode = (sinGF1 | sin03);
			else
				dwCode = (sinGF1 | sin04);

			if(dwCode)
			{

				for(cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if(DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem)
					{
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}

	if(rsServerConfig.EVENT_Christmas)
	{

		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);
		cnt2 = rsServerConfig.EVENT_Christmas;

		if(cnt < 10)
		{
			cnt2 = rsServerConfig.EVENT_Christmas;
		}

		if(cnt < 10)
		{
			cnt2 = (rsServerConfig.EVENT_Christmas * 30) / 100;
		}

		if(rnd < cnt2)
		{

			dwCode = (sinGF1 | sin05);
			if(cnt > 10)
			{
				dwCode = 0;
			}

			if(dwCode)
			{

				for(cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if(DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem)
					{
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}


	if(rsServerConfig.Event_GiftBox)
	{
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);

		if(cnt > 15 || (lpChar->smCharInfo.Level < 20 && cnt>8))
		{
			rnd = rsServerConfig.Event_GiftBox;
		}

		if(rnd < rsServerConfig.Event_GiftBox)
		{
			dwCode = 0;
			if(lpChar->smCharInfo.Level >= 1 && lpChar->smCharInfo.Level < 20)
			{
				dwCode = (sinSP1 | sin10);
			}
			else if(lpChar->smCharInfo.Level >= 20 && lpChar->smCharInfo.Level < 40)
			{
				dwCode = (sinSP1 | sin09);
			}
			else if(lpChar->smCharInfo.Level >= 40 && lpChar->smCharInfo.Level < 60)
			{
				dwCode = (sinSP1 | sin08);
			}
			else if(lpChar->smCharInfo.Level >= 60 && lpChar->smCharInfo.Level < 80)
			{
				dwCode = (sinSP1 | sin07);
			}
			else if(lpChar->smCharInfo.Level >= 80 && lpChar->smCharInfo.Level < 100)
			{
				dwCode = (sinSP1 | sin06);
			}
			else if(lpChar->smCharInfo.Level >= 100)
			{
				dwCode = (sinSP1 | sin05);
			}

			if(dwCode)
			{

				for(cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if(DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem)
					{
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}

	if(lpPlayInfo->Position.Area == rsACTION_FIELD)
	{
		rnd = rand() % 10000;

		if(rnd < 150)
		{
			dwCode = (sinGF1 | sin02);

			for(cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
			{
				if(DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem)
				{
					CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
					return TRUE;
				}
			}
		}
	}





	dwCode = rsLowLevelItem(lpPlayInfo, lpChar);
	if(dwCode)
	{

		for(cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
		{
			if(DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem)
			{
				CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2], lpPlayInfo->smCharInfo.JOB_CODE);
				return TRUE;
			}
		}
	}


	rsSendAreaOpenKidMonster(lpPlayInfo, lpChar);


	if(lpPlayInfo->Position.Area == rsCASTLE_FIELD)
	{
		rsSendAreaOpenSODGuardMonster(lpPlayInfo, lpChar);
	}


	rnd = (rand() << 7) | ((GetCurrentTime() >> 2) & 0x7F);
	rnd = rnd%lpMonInfo->FallItemPerMax;

	if(!rsServerConfig.AreaServer.IP_Count)
	{
		if(!lpMonInfo->FallItems[0].dwItemCode && (rand() % 1000) < 10) return FALSE;
	}

	rcnt = 0;
	for(cnt = 0; cnt < lpMonInfo->FallItemCount; cnt++)
	{
		if(rnd >= rcnt && rnd < (rcnt + lpMonInfo->FallItems[cnt].Percentage))
		{
			if(!lpMonInfo->FallItems[cnt].dwItemCode) return FALSE;

			if(lpMonInfo->FallItems[cnt].dwItemCode == (sinGG1 | sin01))
			{
				rnd = GetRandomPos(lpMonInfo->FallItems[cnt].sPrice[0], lpMonInfo->FallItems[cnt].sPrice[1]);
				lpsItem->ItemInfo.CODE = sinGG1 | sin01;
				wsprintf(lpsItem->ItemInfo.ItemName, sinGold, rnd);
				lpsItem->ItemInfo.Money = rnd;
				ReformItem(&lpsItem->ItemInfo);
				rsMoneyTotalCount += rnd;
				return TRUE;
			}

			dwCode = lpMonInfo->FallItems[cnt].dwItemCode;


			for(cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
			{
				if(DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem)
				{

					if(lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_NPC_MOLLYWOLF && (dwCode&sinITEM_MASK2) == sinFO1)
					{

						lpStgArea = (STG_AREA *)lpChar->lpExt1;
						if(lpStgArea->lpField && lpStgArea->lpField->State == FIELD_STATE_FOREST)
							return FALSE;
					}


					if(DefaultItems[cnt2].sGenDay[0] > 0)
					{

						if(DefaultItems[cnt2].sGenDay[0] <= DefaultItems[cnt2].sGenDay[1])
						{
							return FALSE;
						}
						else
						{
							DefaultItems[cnt2].sGenDay[1]++;
						}
					}
					CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);


					rsSaveCreateItemToHDD(lpsItem);
					rsItemOpenCount++;
					return TRUE;
				}
			}
			return FALSE;
		}
		rcnt += lpMonInfo->FallItems[cnt].Percentage;
	}

	return FALSE;
}





DWORD ObjectSerialCnt = 0x2000;


DWORD GetNewObjectSerial()
{
	DWORD	code;

	code = (ObjectSerialCnt & 0x0FFFFFFF) | (rsServerConfig.ServerCode << 28);

	ObjectSerialCnt++;

	return code;
}



smCHAR_INFO *SetMonsterModelRandom(smCHAR_INFO *lpCharInfo)
{
	smCHAR_INFO *lpInfo;

	lpInfo = &chrMonsterList[(rand() % chrMonsterCnt)];
	memcpy(lpCharInfo, lpInfo, sizeof(smCHAR_INFO));

	return lpInfo;
}








STG_AREA	*StageArea;





int OpenEventMonster(smCHAR_INFO *lpCharInfo, STG_AREA *lpStgArea)
{
	int cnt;
	int MonCnt;


	if(lpCharInfo->dwCharSoundCode == snCHAR_SOUND_HOPT)
	{
		if((rand() % 100) > 30) return FALSE;

		MonCnt = 0;
		for(cnt = 0; cnt < STG_MONSTER_MAX; cnt++)
		{
			if(lpStgArea->lpCharMonster[cnt])
			{
				if(lpStgArea->lpCharMonster[cnt]->smCharInfo.dwCharSoundCode == snCHAR_SOUND_HOPYKING)
				{
					MonCnt++;
				}
			}
		}
		if(MonCnt >= 40) return FALSE;

		for(cnt = 0; cnt < chrMonsterCnt; cnt++)
		{
			if(chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_HOPYKING)
			{
				memcpy(lpCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));
				break;
			}
		}
	}


	return TRUE;
}



int	OpenEnemyMonsterFromCristal(DWORD dwItemCode, int x, int y, int z, rsPLAYINFO *lpPlayInfo)
{
#ifdef _W_SERVER

	STG_CHAR_INFO StgCharInfo;

	int nRan = 0;
	nRan = rand() % 7;

	srCRISTAL_MONSTER *lpCristalMonster = nullptr;

	if(dwItemCode == (sinGP2 | sin01)) lpCristalMonster = &srCristalMonsterEnemy[nRan];
	else if(dwItemCode == (sinGP2 | sin02)) lpCristalMonster = &srCristalMonsterEnemy2[nRan];
	else if(dwItemCode == (sinGP2 | sin03)) lpCristalMonster = &srCristalMonsterEnemy3[nRan];
	else if(dwItemCode == (sinGP2 | sin04)) lpCristalMonster = &srCristalMonsterEnemy4[nRan];
	else if(dwItemCode == (sinGP2 | sin05)) lpCristalMonster = &srCristalMonsterEnemy5[nRan];
	else if(dwItemCode == (sinGP2 | sin06)) lpCristalMonster = &srCristalMonsterEnemy6[nRan];
	else if(dwItemCode == (sinGP2 | sin07)) lpCristalMonster = &srCristalMonsterEnemy7[nRan];
	else if(dwItemCode == (sinGP2 | sin08)) lpCristalMonster = &srCristalMonsterEnemy8[nRan];
	else if(dwItemCode == (sinGP2 | sin09)) lpCristalMonster = &srCristalMonsterEnemy9[nRan];

	if(!lpCristalMonster)
	{
		return false;
	}



	STG_AREA *lpStgArea = FindStageField(x, z);

	if(lpStgArea)
	{

		if(lpStgArea->lpField->State == FIELD_STATE_VILLAGE || lpPlayInfo->Position.Area == rsCASTLE_FIELD || lpPlayInfo->Position.Area == 29 || lpPlayInfo->Position.Area == 16)
		{
			return FALSE;
		}
	}

	StgCharInfo.PosiState = smCHAR_STATE_ENEMY;
	StgCharInfo.smCharInfo.Life[0] = 100;
	StgCharInfo.smCharInfo.Mana[0] = 100;
	StgCharInfo.smCharInfo.Life[1] = 100;
	StgCharInfo.smCharInfo.State = TRUE;

	memcpy(&StgCharInfo.smCharInfo, lpCristalMonster->lpCharInfo, sizeof(smCHAR_INFO));
	lpStgArea->EvnMonster = TRUE;
	smCHAR *lpChar = lpStgArea->OpenMonster(&StgCharInfo, 0);

	if(lpChar)
	{
		lpChar->pX = x;
		lpChar->pY = y;
		lpChar->pZ = z;
		lpChar->DistAroundDbl = 0;
		lpChar->SetMotionFromCode(CHRMOTION_STATE_STAND);
		lpChar->TargetMoveCount = 0;
		lpChar->nCheckChar = 100;

		lpChar->dwUpdateCharInfoTime = dwPlayServTime + 4 * 60 * 1000;


		smTRANS_COMMAND_EX	TransCommandEx;

		ZeroMemory(&TransCommandEx, sizeof(smTRANS_COMMAND_EX));
		TransCommandEx.WParam = smCOMMNAD_USER_WARP;
		TransCommandEx.LParam = x;
		TransCommandEx.SParam = y;
		TransCommandEx.EParam = z;
		rsSendCommandUser(lpPlayInfo, &TransCommandEx);
	}

	return TRUE;
#endif
	return FALSE;
}



int	OpenMonsterFromCristal(DWORD dwItemCode, int x, int y, int z, rsPLAYINFO *lpPlayInfo)
{
#ifdef _W_SERVER

	STG_AREA	*lpStgArea;
	STG_CHAR_INFO StgCharInfo;
	smCHAR	*lpChar;
	srCRISTAL_MONSTER	*lpCristalMonster;
	int cnt, cnt2;
	int height, dx, dy, dz, ta;
	int	CodeCount;
	int	RndCnt, RndNum;
	int	ClanCnt;
	TRANS_CHATMESSAGE	TransChatMessage;
	int	sx, sy, sz, dist;
	int	MyMonFlag;
	int CastleFlag = 0;
	int	BlessSolderCnt[3];
	int BlessCristalCode;
	int	BillingCrystalFlag = 0;

	CodeCount = ((dwItemCode & 0xFFFF) >> 8) - 1;

	if(CodeCount == srCRISTAL_RANDOM)
	{

		CodeCount = 0;

		RndNum = rand() % 100;
		RndCnt = 0;
		for(cnt = 0; cnt < srCRISTAL_RANDOM; cnt++)
		{
			if(srCristalMonster[CodeCount].RndCount)
			{
				RndCnt += srCristalMonster[cnt].RndCount;
				if(RndNum < RndCnt)
				{
					CodeCount = cnt;
					break;
				}
			}
		}
	}


	if(CodeCount == srCRISTAL_MARVEL_RANDOM)
	{
		CodeCount = 0;
		RndNum = rand() % 100;
		RndCnt = 0;
		for(cnt = 0; cnt < MARVELCRISTAL_MAX; cnt++)
		{
			if(srMarvelCristalMonster[CodeCount].RndCount)
			{
				RndCnt += srMarvelCristalMonster[cnt].RndCount;
				if(RndNum < RndCnt)
				{
					CodeCount = cnt;
					break;
				}
			}
		}
	}

	if(rsCristalEvent)
	{
		if(srCRISTAL_RANDOM == ((dwItemCode & 0xFFFF) >> 8) - 1)
		{
			lpCristalMonster = &srCristalMonsterBoss[CodeCount];
		}
		else if(srCRISTAL_MARVEL_RANDOM == ((dwItemCode & 0xFFFF) >> 8) - 1)
		{
			lpCristalMonster = &srMarvelCristalMonsterBoss[CodeCount];
		}
		else if(srCRISTAL_G_DIVINE_CLAN == ((dwItemCode & 0xFFFF) >> 8) - 1)
		{
			lpCristalMonster = &srMarvelCristalMonsterBoss[srCRISTAL_MAX - 1];
		}
		else
			lpCristalMonster = &srCristalMonsterBoss[CodeCount];

		BillingCrystalFlag = TRUE;
	}
	else
	{
		if(srCRISTAL_RANDOM == ((dwItemCode & 0xFFFF) >> 8) - 1)
		{
			lpCristalMonster = &srCristalMonster[CodeCount];
		}
		else if(srCRISTAL_MARVEL_RANDOM == ((dwItemCode & 0xFFFF) >> 8) - 1)
		{
			lpCristalMonster = &srMarvelCristalMonster[CodeCount];
		}
		else if(srCRISTAL_G_DIVINE_CLAN == ((dwItemCode & 0xFFFF) >> 8) - 1)
		{
			lpCristalMonster = &srMarvelCristalMonster[srCRISTAL_MAX - 1];
		}
		else
			lpCristalMonster = &srCristalMonster[CodeCount];

		BillingCrystalFlag = TRUE;
	}


	switch(CodeCount)
	{
	case srCRISTAL_SKELETON:
		lpCristalMonster = &srBillingCrystalMonster[(rand() % srBC_MONSTER_MAX)];
		BillingCrystalFlag = TRUE;
		break;
	case srCRISTAL_KAOS:
		lpCristalMonster = &srBillingCrystalMonster[(rand() % srBC_MONSTER_MAX) + srBC_MONSTER_MAX];
		BillingCrystalFlag = TRUE;
		break;
	case srCRISTAL_IMPERNA:
		lpCristalMonster = &srBillingCrystalMonster[(rand() % srBC_MONSTER_MAX) + srBC_MONSTER_MAX * 2];
		BillingCrystalFlag = TRUE;
		break;
	case srCRISTAL_EXTREME:
		int code = 12;
		RndNum = rand() % 100;
		RndCnt = 0;
		for(cnt = srBC_MONSTER_MAX * 3; cnt < srBC_MONSTER_MAX * 3 + 4; cnt++)
		{
			if(srBillingCrystalMonster[code].RndCount)
			{
				RndCnt += srBillingCrystalMonster[cnt].RndCount;
				if(RndNum < RndCnt)
				{
					code = cnt;
					break;
				}
			}
		}
		lpCristalMonster = &srBillingCrystalMonster[code];
		BillingCrystalFlag = TRUE;
		break;
	}

	if(!lpCristalMonster->lpCharInfo) return FALSE;

	lpStgArea = FindStageField(x, z);
	if(lpStgArea)
	{
		if(lpStgArea->lpField->State == FIELD_STATE_VILLAGE) return FALSE;
		if(CodeCount >= srCRISTAL_CASTLE_START && CodeCount < srCRISTAL_CASTLE_END)
		{

			if(!rsBlessCastle.CastleMode || !lpPlayInfo->dwClanCode || lpPlayInfo->dwClanCode != rsBlessCastle.dwMasterClan || lpPlayInfo->Position.Area != rsCASTLE_FIELD)
			{

				TransChatMessage.code = OpCode::OPCODE_MESSAGEBOX;
				TransChatMessage.dwIP = 0;
				TransChatMessage.dwObjectSerial = 0;
				strcpy_s(TransChatMessage.szMessage, srMsg_202);
				TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);

				lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
				return -1;
			}

			ClanCnt = 0;
			MyMonFlag = 0;
			BlessSolderCnt[0] = 0;
			BlessSolderCnt[1] = 0;
			BlessSolderCnt[2] = 0;
			for(cnt = 0; cnt < STG_MONSTER_MAX; cnt++)
			{
				if(lpStgArea->lpCharMonster[cnt] && lpStgArea->lpCharMonster[cnt]->dwClanCode == lpPlayInfo->dwClanCode)
				{
					if(lpStgArea->lpCharMonster[cnt]->smCharInfo.Life[0] > 0 && lpStgArea->lpCharMonster[cnt]->smCharInfo.Next_Exp)
					{
						ClanCnt++;
						if(lpStgArea->lpCharMonster[cnt]->smCharInfo.Next_Exp == lpPlayInfo->dwObjectSerial)
							MyMonFlag++;
						switch(lpStgArea->lpCharMonster[cnt]->smCharInfo.dwCharSoundCode)
						{
						case snCHAR_SOUND_CASTLE_SOLDER_A:
							BlessSolderCnt[0]++;
							break;
						case snCHAR_SOUND_CASTLE_SOLDER_B:
							BlessSolderCnt[1]++;
							break;
						case snCHAR_SOUND_CASTLE_SOLDER_C:
							BlessSolderCnt[2]++;
							break;

						}
					}
				}
			}

			BlessCristalCode = 0;

			switch(dwItemCode)
			{
			case sinGP1 | sin14:
				BlessCristalCode = 0;
				break;
			case sinGP1 | sin15:
				BlessCristalCode = 1;
				break;
			case sinGP1 | sin16:
				BlessCristalCode = 2;
				break;
			}


			if(ClanCnt >= srCASLTE_SOLDER_CLAN_MAX || MyMonFlag >= srCASLTE_SOLDER_MAX || BlessSolderCnt[BlessCristalCode] >= srCASLTE_SOLDER_KIND_MAX)
			{

				TransChatMessage.code = OpCode::OPCODE_MESSAGEBOX;
				TransChatMessage.dwIP = 0;
				TransChatMessage.dwObjectSerial = 0;
				strcpy_s(TransChatMessage.szMessage, srMsg_200);
				TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);

				lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
				return -1;
			}

			CastleFlag = TRUE;
		}

		if(CodeCount == srCRISTAL_CLAN)
		{
			if(!lpPlayInfo->smCharInfo.ClassClan) return FALSE;
			ClanCnt = 0;
			MyMonFlag = 0;
			for(cnt = 0; cnt < STG_MONSTER_MAX; cnt++)
			{
				if(lpStgArea->lpCharMonster[cnt] && lpStgArea->lpCharMonster[cnt]->smCharInfo.ClassClan == lpPlayInfo->smCharInfo.ClassClan)
				{
					sx = (lpPlayInfo->Position.x - lpStgArea->lpCharMonster[cnt]->pX) >> FLOATNS;
					sy = (lpPlayInfo->Position.y - lpStgArea->lpCharMonster[cnt]->pY) >> FLOATNS;
					sz = (lpPlayInfo->Position.z - lpStgArea->lpCharMonster[cnt]->pZ) >> FLOATNS;
					dist = sx*sx + sy*sy + sz*sz;
					if(dist < DIST_TRANSLEVEL_LOW)	ClanCnt++;
					if(lpStgArea->lpCharMonster[cnt]->smCharInfo.Next_Exp == lpPlayInfo->dwObjectSerial)
						MyMonFlag++;
				}
			}

			if(ClanCnt > (srCLAN_MONSTER_MAX - 1))
			{
				TransChatMessage.code = OpCode::OPCODE_MESSAGEBOX;
				TransChatMessage.dwIP = 0;
				TransChatMessage.dwObjectSerial = 0;
				strcpy_s(TransChatMessage.szMessage, srMsg_200);
				TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);

				lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
				return -1;
			}

			if(MyMonFlag)
			{
				TransChatMessage.code = OpCode::OPCODE_MESSAGEBOX;
				TransChatMessage.dwIP = 0;
				TransChatMessage.dwObjectSerial = 0;
				strcpy_s(TransChatMessage.szMessage, srMsg_201);
				TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);

				lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
				return -1;
			}
		}

		for(cnt = 0; cnt < 8; cnt++)
		{
			cnt2 = rand() % 8;
			dx = x + (ptItemSettingPosi[cnt2 & 7].x << (FLOATNS + 1));
			dz = z + (ptItemSettingPosi[cnt2 & 7].y << (FLOATNS + 1));
			dy = y;
			cnt2++;


			height = lpStgArea->lpStage->GetFloorHeight(dx, dy, dz, 32 * fONE);
			if(height != CLIP_OUT)
			{

				ta = abs(height - dy);
				if(ta < 32 * fONE)
				{
					break;
				}
			}
		}
		if(cnt < 8)
		{
			x = dx;
			z = dz;
			y = height;
		}

		StgCharInfo.PosiState = smCHAR_STATE_ENEMY;
		StgCharInfo.smCharInfo.Life[0] = 100;
		StgCharInfo.smCharInfo.Mana[0] = 100;
		StgCharInfo.smCharInfo.Life[1] = 100;
		StgCharInfo.smCharInfo.State = TRUE;

		memcpy(&StgCharInfo.smCharInfo, lpCristalMonster->lpCharInfo, sizeof(smCHAR_INFO));

		lpStgArea->EvnMonster = TRUE;
		lpChar = lpStgArea->OpenMonster(&StgCharInfo, 0);
		if(lpChar)
		{
			lpChar->pX = x;
			lpChar->pY = y;
			lpChar->pZ = z;
			lpChar->DistAroundDbl = 0;
			lpChar->SetMotionFromCode(CHRMOTION_STATE_STAND);
			lpChar->TargetMoveCount = 0;
			if(lpPlayInfo)
			{
				strcpy_s(lpChar->smCharInfo.szModelName2 + 1, sizeof(lpChar->smCharInfo.szModelName2) - 1, lpPlayInfo->smCharInfo.szName);
				lpChar->smCharInfo.Next_Exp = lpPlayInfo->dwObjectSerial;

				if(CastleFlag)
				{

					lpChar->smMonsterInfo.PotionCount = StgCharInfo.smCharInfo.lpMonInfo->PotionCount;
					lpChar->dwClanCode = rsBlessCastle.dwMasterClan;
				}
				else
				{
					lpChar->lpMasterPlayInfo = lpPlayInfo;
					lpChar->smMonsterInfo.dwAutoCharCode = 0;
					lpChar->dwUpdateCharInfoTime = dwPlayServTime + 4 * 60 * 1000;
					lpChar->smCharInfo.Brood = smCHAR_MONSTER_USER;

					if(lpPlayInfo->smCharInfo.Level > 0 && lpPlayInfo->smCharInfo.Level < 100)
					{

						lpChar->dwUpdateCharInfoTime += lpPlayInfo->smCharInfo.Level * 1000 * 2;
						lpChar->smCharInfo.Life[1] += lpPlayInfo->smCharInfo.Level * 3;
						lpChar->smCharInfo.Life[0] = lpChar->smCharInfo.Life[1];
					}

					if(CodeCount == srCRISTAL_CLAN)
						lpChar->smCharInfo.ClassClan = lpPlayInfo->smCharInfo.ClassClan;

					lpChar->Clan_CastleMasterFlag = BillingCrystalFlag;
				}

				smTRANS_COMMAND_EX	TransCommandEx;

				ZeroMemory(&TransCommandEx, sizeof(smTRANS_COMMAND_EX));
				TransCommandEx.WParam = smCOMMNAD_USER_WARP;
				TransCommandEx.LParam = x;
				TransCommandEx.SParam = y;
				TransCommandEx.EParam = z;
				rsSendCommandUser(lpPlayInfo, &TransCommandEx);
			}

			return TRUE;
		}
	}
#endif
	return FALSE;
}




smCHAR *rsGetLinkChar(smCHAR *lpMasterChar)
{
	for(int cnt = 0; cnt < AUTOPLAYER_MAX; cnt++)
	{
		if(chrAutoPlayer[cnt].Flag &&
			lpMasterChar != &chrAutoPlayer[cnt] &&
			chrAutoPlayer[cnt].lpLinkChar == lpMasterChar &&
			chrAutoPlayer[cnt].smCharInfo.Life[0] > 0)
		{

			if(!lpMasterChar->lpLinkPlayInfo || lpMasterChar->lpLinkPlayInfo == chrAutoPlayer[cnt].lpLinkPlayInfo)
				return &chrAutoPlayer[cnt];
		}
	}

	return NULL;
}


smCHAR *OpenMonsterFromSkill(DWORD SkillCode, int x, int y, int z, rsPLAYINFO *lpPlayInfo, smCHAR *lpEnemyChar)
{
#ifdef _W_SERVER

	STG_AREA	*lpStgArea;
	STG_CHAR_INFO StgCharInfo;
	smCHAR	*lpChar;
	srCRISTAL_MONSTER	*lpCristalMonster = 0;
	int cnt, cnt2;
	int height, dx, dy, dz, ta;


	int	SkillMonsterAttackFlag = 0;

	switch(SkillCode)
	{
	case SKILL_PLAY_METAL_GOLEM:
		lpCristalMonster = &srSkillMonster[0];
		SkillMonsterAttackFlag = TRUE;
		break;
	case SKILL_PLAY_RECALL_WOLVERIN:
		lpCristalMonster = &srSkillMonster[1];
		SkillMonsterAttackFlag = TRUE;
		break;
	case SKILL_PLAY_FIRE_ELEMENTAL:
		lpCristalMonster = &srSkillMonster[2];
		SkillMonsterAttackFlag = TRUE;
		break;
	}

	if(!lpCristalMonster->lpCharInfo) return NULL;

	if(lpPlayInfo)
	{

		for(cnt = 0; cnt < AUTOPLAYER_MAX; cnt++)
		{
			if(chrAutoPlayer[cnt].Flag &&
				chrAutoPlayer[cnt].lpMasterPlayInfo == lpPlayInfo &&
				chrAutoPlayer[cnt].HoSkillCode == SkillCode &&
				chrAutoPlayer[cnt].smCharInfo.Life[0] > 0)
			{

				chrAutoPlayer[cnt].smCharInfo.Life[0] = 0;
				chrAutoPlayer[cnt].HoSkillCode = 0;
				chrAutoPlayer[cnt].SetMotionFromCode(CHRMOTION_STATE_DEAD);
			}
		}
	}

	lpStgArea = FindStageField(x, z);
	if(lpStgArea)
	{
		if(lpStgArea->lpField->State == FIELD_STATE_VILLAGE) return NULL;

		for(cnt = 0; cnt < 8; cnt++)
		{
			cnt2 = rand() % 8;
			dx = x + (ptItemSettingPosi[cnt2 & 7].x << (FLOATNS + 1));
			dz = z + (ptItemSettingPosi[cnt2 & 7].y << (FLOATNS + 1));
			dy = y;
			cnt2++;


			height = lpStgArea->lpStage->GetFloorHeight(dx, dy, dz, 32 * fONE);
			if(height != CLIP_OUT)
			{

				ta = abs(height - dy);
				if(ta < 32 * fONE)
				{
					break;
				}
			}
		}
		if(cnt < 8)
		{
			x = dx;
			z = dz;
			y = height;
		}

		StgCharInfo.PosiState = smCHAR_STATE_ENEMY;
		StgCharInfo.smCharInfo.Life[0] = 100;
		StgCharInfo.smCharInfo.Mana[0] = 100;
		StgCharInfo.smCharInfo.Life[1] = 100;
		StgCharInfo.smCharInfo.State = TRUE;

		memcpy(&StgCharInfo.smCharInfo, lpCristalMonster->lpCharInfo, sizeof(smCHAR_INFO));

		lpStgArea->EvnMonster = TRUE;
		lpChar = lpStgArea->OpenMonster(&StgCharInfo, 0);
		if(lpChar)
		{
			lpChar->pX = x;
			lpChar->pY = y;
			lpChar->pZ = z;
			lpChar->DistAroundDbl = 0;
			lpChar->SetMotionFromCode(CHRMOTION_STATE_STAND);
			lpChar->TargetMoveCount = 0;

			smTRANS_COMMAND_EX	TransCommandEx;

			ZeroMemory(&TransCommandEx, sizeof(smTRANS_COMMAND_EX));
			TransCommandEx.WParam = smCOMMNAD_USER_WARP;
			TransCommandEx.LParam = x;
			TransCommandEx.SParam = y;
			TransCommandEx.EParam = z;

			if(lpPlayInfo && !lpEnemyChar)
			{
				lpChar->lpMasterPlayInfo = lpPlayInfo;
				lpChar->smMonsterInfo.dwAutoCharCode = 0;
				lpChar->HoSkillCode = SkillCode;
				lpChar->HoSkillMode = 0;

				lpChar->smCharInfo.Brood = smCHAR_MONSTER_USER;
				strcpy_s(lpChar->smCharInfo.szModelName2 + 1, sizeof(lpChar->smCharInfo.szModelName2) - 1, lpPlayInfo->smCharInfo.szName);
				lpChar->smCharInfo.Next_Exp = lpPlayInfo->dwObjectSerial;
				lpChar->dwUpdateCharInfoTime = dwPlayServTime + 4 * 60 * 1000;

				lpPlayInfo->lpLinkChar = lpChar;
				lpPlayInfo->dwLinkCharCode = lpChar->dwObjectSerial;
				lpChar->Clan_CastleMasterFlag = SkillMonsterAttackFlag;
				rsSendCommandUser(lpPlayInfo, &TransCommandEx);
			}

			if(lpEnemyChar && lpEnemyChar->lpLinkPlayInfo)
			{
				lpChar->lpLinkPlayInfo = lpEnemyChar->lpLinkPlayInfo;
				lpChar->dwLinkObjectCode = lpEnemyChar->dwLinkObjectCode;
				lpChar->lpLinkChar = lpEnemyChar;
				lpChar->dwUpdateCharInfoTime = dwPlayServTime + 5 * 60 * 1000;

				if(lpEnemyChar->lpLinkPlayInfo->lpsmSock)
					lpEnemyChar->lpLinkPlayInfo->lpsmSock->Send((char *)&TransCommandEx, TransCommandEx.size, TRUE);
			}

			return lpChar;
		}
	}
#endif
	return NULL;
}


smCHAR *OpenMonster_QuestArena(rsPLAYINFO *lpPlayInfo, DWORD dwQuestCode, int Param = 0)
{
	STG_AREA	*lpStgArea;
	STG_CHAR_INFO StgCharInfo;
	int	len, cnt, pow;
	smCHAR	*lpChar;
	DWORD	dwSndCode;
	int		OpenLevel = 0;


	switch(dwQuestCode)
	{
	case SIN_QUEST_CODE_CHANGEJOB4:
		if(lpPlayInfo->smCharInfo.JOB_CODE <= 4 || lpPlayInfo->smCharInfo.JOB_CODE == 9)
			dwSndCode = snCHAR_SOUND_NPC_SKILLMASTER;
		else
			dwSndCode = snCHAR_SOUND_NPC_MAGICMASTER;
		break;

	case HAQUEST_CODE_FURYOFPHANTOM:
		dwSndCode = snCHAR_SOUND_FURY;
		switch(Param)
		{
		case 1:
			OpenLevel = 118; break;
		case 2:
			OpenLevel = 119; break;
		case 3:
			OpenLevel = 120; break;
		}
	}


	for(cnt = 0; cnt < AUTOPLAYER_MAX; cnt++)
	{
		if(chrAutoPlayer[cnt].Flag &&
			chrAutoPlayer[cnt].lpLinkPlayInfo == lpPlayInfo &&
			chrAutoPlayer[cnt].dwLinkObjectCode == lpPlayInfo->dwObjectSerial)
		{

			chrAutoPlayer[cnt].Close();
			((STG_AREA *)chrAutoPlayer[cnt].lpExt1)->MonsterCount--;
			((STG_AREA *)chrAutoPlayer[cnt].lpExt1)->DeleteMonTable(&chrAutoPlayer[cnt]);
		}
	}

	lpStgArea = &StageArea[QUEST_ARENA_FIELD];

	if(lpStgArea)
	{
		len = 0;

		StgCharInfo.PosiState = smCHAR_STATE_ENEMY;
		StgCharInfo.smCharInfo.Life[0] = 100;
		StgCharInfo.smCharInfo.Mana[0] = 100;
		StgCharInfo.smCharInfo.Life[1] = 100;
		StgCharInfo.smCharInfo.State = TRUE;


		for(cnt = 0; cnt < chrMonsterCnt; cnt++)
		{
			if(chrMonsterList[cnt].dwCharSoundCode == dwSndCode && (OpenLevel == 0 || OpenLevel == chrMonsterList[cnt].Level))
			{
				memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));
				len++;
				break;
			}
		}

		if(len)
		{
			lpStgArea->EvnMonster = TRUE;
			lpChar = lpStgArea->OpenMonster(&StgCharInfo, 0);
			if(lpChar)
			{
				lpChar->SetPosi(QUEST_ARENA_NPC_POS_X, 0, QUEST_ARENA_NPC_POS_Z, 0, 0, 0);
				lpChar->DistAroundDbl = 0;
				lpChar->SetMotionFromCode(CHRMOTION_STATE_STAND);
				lpChar->TargetMoveCount = 0;
				lpChar->lpLinkPlayInfo = lpPlayInfo;
				lpChar->dwLinkObjectCode = lpPlayInfo->dwObjectSerial;
				lpChar->dwUpdateCharInfoTime = dwPlayServTime + 30 * 60 * 1000;


				pow = lpPlayInfo->smCharInfo.Level - 60;
				if(pow < 0) pow = 0;
				pow += pow / 2;

				lpChar->smCharInfo.Life[0] += (lpChar->smCharInfo.Life[0] * pow) / 100;
				if(lpChar->smCharInfo.Life[0] < 0 || lpChar->smCharInfo.Life[0]>30000) lpChar->smCharInfo.Life[0] = 30000;
				lpChar->smCharInfo.Life[1] = lpChar->smCharInfo.Life[0];

				lpChar->smCharInfo.Attack_Damage[0] += (lpChar->smCharInfo.Attack_Damage[0] * pow) / 100;
				lpChar->smCharInfo.Attack_Damage[1] += (lpChar->smCharInfo.Attack_Damage[1] * pow) / 100;

				lpChar->smMonsterInfo.SkillDamage[0] += (lpChar->smMonsterInfo.SkillDamage[0] * pow) / 100;
				lpChar->smMonsterInfo.SkillDamage[1] += (lpChar->smMonsterInfo.SkillDamage[1] * pow) / 100;

				lpChar->smMonsterInfo.PotionCount += 3;

				return lpChar;
			}
		}
	}

	return NULL;
}




smCHAR *OpenMonsterFromName(char *szName, int x, int y, int z, rsPLAYINFO *lpPlayInfo = 0)
{
	STG_AREA	*lpStgArea;
	STG_CHAR_INFO StgCharInfo;
	int	len, cnt;
	smCHAR	*lpChar;

	lpStgArea = FindStageField(x, z);
	if(lpStgArea)
	{
		len = 0;

		StgCharInfo.PosiState = smCHAR_STATE_ENEMY;
		StgCharInfo.smCharInfo.Life[0] = 100;
		StgCharInfo.smCharInfo.Mana[0] = 100;
		StgCharInfo.smCharInfo.Life[1] = 100;
		StgCharInfo.smCharInfo.State = TRUE;

		if(szName && szName[0])
		{

			for(cnt = 0; cnt < chrMonsterCnt; cnt++)
			{
				if(lstrcmp(chrMonsterList[cnt].szName, szName) == 0)
				{
					memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));
					len++;
					break;
				}
			}
		}

		if(len)
		{
			lpStgArea->EvnMonster = TRUE;
			lpChar = lpStgArea->OpenMonster(&StgCharInfo, 0);
			if(lpChar)
			{
				lpChar->pX = x;
				lpChar->pY = y;
				lpChar->pZ = z;
				lpChar->DistAroundDbl = 0;
				lpChar->SetMotionFromCode(CHRMOTION_STATE_STAND);
				lpChar->TargetMoveCount = 0;

				if(lpPlayInfo)
				{
					lpChar->lpMasterPlayInfo = lpPlayInfo;
					lpChar->smMonsterInfo.dwAutoCharCode = 0;

					lpChar->smCharInfo.Brood = smCHAR_MONSTER_USER;
					strcpy_s(lpChar->smCharInfo.szModelName2 + 1, sizeof(lpChar->smCharInfo.szModelName2) - 1, lpPlayInfo->smCharInfo.szName);
					lpChar->smCharInfo.Next_Exp = lpPlayInfo->dwObjectSerial;
					lpChar->dwUpdateCharInfoTime = dwPlayServTime + 4 * 60 * 1000;
				}

				return lpChar;
			}
		}
	}

	return FALSE;
}


int rsGetMonCountFlag(smCHAR *lpChar)
{
	STG_AREA	*lpStgArea;
	if(!lpChar->lpExt1) return -1;

	lpStgArea = (STG_AREA *)lpChar->lpExt1;

	return lpStgArea->StartPointMonCount[lpChar->OpenStartPostion];
}


smCHAR *rsOpenSubMonster(smCHAR *lpMainChar, DWORD dwCharSoundCode, int x, int y, int z, int MaxFlag)
{
	STG_AREA	*lpStgArea;
	STG_CHAR_INFO StgCharInfo;
	int	len, cnt;
	smCHAR	*lpChar;
	smCHAR_INFO	*lpCharInfo;


	if(!lpMainChar->lpExt1) return FALSE;

	lpStgArea = (STG_AREA *)lpMainChar->lpExt1;


	if(lpStgArea->StartPointMonCount[lpMainChar->OpenStartPostion] >= MaxFlag) return FALSE;




	if(lpStgArea)
	{
		len = 0;

		StgCharInfo.PosiState = smCHAR_STATE_ENEMY;
		StgCharInfo.smCharInfo.Life[0] = 100;
		StgCharInfo.smCharInfo.Mana[0] = 100;
		StgCharInfo.smCharInfo.Life[1] = 100;
		StgCharInfo.smCharInfo.State = TRUE;

		lpCharInfo = 0;


		for(cnt = 0; cnt < chrMonsterCnt; cnt++)
		{
			if(chrMonsterList[cnt].dwCharSoundCode == dwCharSoundCode)
			{
				memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));
				len++;
				break;
			}
		}

		if(len)
		{



			lpChar = srFindEmptyChar();
			if(!lpChar) return NULL;


			lpChar->Init();
			lpChar->lpStage = lpMainChar->lpStage;
			lpChar->SetPosi(x, y, z, lpMainChar->Angle.x, lpMainChar->Angle.y, lpMainChar->Angle.z);

			lpChar->PosiAround.x = x;
			lpChar->PosiAround.y = lpChar->pY;
			lpChar->PosiAround.z = y;
			lpChar->DistAroundDbl = DIST_AROUND_MIDDLE;

			lpChar->OpenStartPostion = lpMainChar->OpenStartPostion;


			lpStgArea->MonsterCount++;
			lpChar->lpExt1 = lpStgArea;
			lpChar->dwObjectSerial = GetNewObjectSerial();
			lpChar->ActionPattern = 5;
			memcpy(&lpChar->smCharInfo, &StgCharInfo.smCharInfo, sizeof(smCHAR_INFO));
			memcpy(&lpChar->smMonsterInfo, StgCharInfo.smCharInfo.lpMonInfo, sizeof(smCHAR_MONSTER_INFO));
			lpChar->SetLoadPattern(lpChar->smCharInfo.szModelName);


			lpChar->smCharInfo.StatePoint = StgCharInfo.smCharInfo.lpMonInfo->ClassCode;

			lpChar->DistAroundDbl = 0;
			lpChar->AttackUserFlag = 0;
			lpChar->lpExt2 = 0;



			lpChar->lpExpAttackPlayInfo = 0;
			lpChar->ExpAttackLife = 0;

			lpStgArea->AddMonTable(lpChar);
			lpChar->ReopenCount = REOPEN_COUNT_NUM;
			lpChar->dwLastTransTime = dwPlayServTime;


			if(lpChar->smMonsterInfo.PotionCount)
			{
				if((rand() % 100) < lpChar->smMonsterInfo.PotionPercent)
				{
					lpChar->smMonsterInfo.PotionCount = (rand() % lpChar->smMonsterInfo.PotionCount) + 1;
				}
				else
				{
					lpChar->smMonsterInfo.PotionCount = 0;
				}
			}

#ifdef	_LANGUAGE_JAPANESE 
			if(rsDamgeOffEvent)
			{

				lpChar->smCharInfo.Attack_Damage[0] = (lpChar->smCharInfo.Attack_Damage[0] * ATTACK_RATE) / 100;
				lpChar->smCharInfo.Attack_Damage[1] = (lpChar->smCharInfo.Attack_Damage[1] * ATTACK_RATE) / 100;
				if(lpChar->smMonsterInfo.SkillDamage[0])
				{
					lpChar->smMonsterInfo.SkillDamage[0] = (lpChar->smMonsterInfo.SkillDamage[0] * ATTACK_RATE) / 100;
					lpChar->smMonsterInfo.SkillDamage[1] = (lpChar->smMonsterInfo.SkillDamage[1] * ATTACK_RATE) / 100;
				}
			}
#else

			if(rsDamgeOffEvent1)
			{

				lpChar->smCharInfo.Attack_Damage[0] = (lpChar->smCharInfo.Attack_Damage[0] * 75) / 100;
				lpChar->smCharInfo.Attack_Damage[1] = (lpChar->smCharInfo.Attack_Damage[1] * 75) / 100;
				if(lpChar->smMonsterInfo.SkillDamage[0])
				{
					lpChar->smMonsterInfo.SkillDamage[0] = (lpChar->smMonsterInfo.SkillDamage[0] * 75) / 100;
					lpChar->smMonsterInfo.SkillDamage[1] = (lpChar->smMonsterInfo.SkillDamage[1] * 75) / 100;
				}
			}

			if(rsDamgeOffEvent2)
			{

				lpChar->smCharInfo.Attack_Damage[0] = (lpChar->smCharInfo.Attack_Damage[0] * 50) / 100;
				lpChar->smCharInfo.Attack_Damage[1] = (lpChar->smCharInfo.Attack_Damage[1] * 50) / 100;
				if(lpChar->smMonsterInfo.SkillDamage[0])
				{
					lpChar->smMonsterInfo.SkillDamage[0] = (lpChar->smMonsterInfo.SkillDamage[0] * 50) / 100;
					lpChar->smMonsterInfo.SkillDamage[1] = (lpChar->smMonsterInfo.SkillDamage[1] * 50) / 100;
				}
			}
#endif


			if(rsDefenseOffEvent)
			{

				lpChar->smCharInfo.Defence = (lpChar->smCharInfo.Defence*DEFENSE_RATE) / 100;
			}
			rsMonOpenCount++;

			lpChar->SetMotionFromCode(CHRMOTION_STATE_STAND);
			lpChar->TargetMoveCount = 0;

			return lpChar;
		}
	}

	return FALSE;
}







POINT3D	rsHardCoreEventOpenPos[7][3] = {
	{
		{ 18967,  1154,	3055 },
		{ 19995,  1154,	2134 },
		{ 19485,  1154,	2615 }
	},
	{
		{ 20838,  1154,	3024 },
		{ 21671,  1154,	2193 },
		{ 21255,  1154,	2615 }
	},
	{
		{ 22478,  1154,	3049 },
		{ 23437,  1154,	2135 },
		{ 22948,  1154,	2615 }
	},
	{
		{ 24204,  1154,	3094 },
		{ 25173,  1154,	2135 },
		{ 24674,  1154,	2615 }
	},

	{
		{ 20509,  1621,	5284 },
		{ 21544,  1621,	4261 },
		{ 21012,  1621,	4773 }
	},
	{
		{ 22575,  1621,	5253 },
		{ 23610,  1621,	4230 },
		{ 23077,  1621,	4742 }
	},

	{
		{ 21538,  1638,	7057 },
		{ 22527,  1638,	6079 },
		{ 22018,  1638,	6569 }
	}
};


int	rsSod_RoundTable[8][2] = {
	{	0,	4	},
	{	0,	4	},
	{	0,	4	},
	{	4,	6	},
	{	4,	6	},
	{	4,	6	},
	{	6,	7	},
	{	6,	7	}
};


int	rsSod_RoundRoomTable[4][8] = {
	{	0,	0,	0,	4,	4,	4,	6,	6	},
	{	1,	1,	1,	4,	4,	4,	6,	6	},
	{	2,	2,	2,	5,	5,	5,	6,	6	},
	{	3,	3,	3,	5,	5,	5,	6,	6	}
};




int rsHardCoreEventArea[4] = { 18516 , 25715, 1541 , 7178 };



int	rsHardCoreEventInterLineZ = -32 * fONE;
int	rsHardCoreEventInterLineZ2 = -64 * fONE;
int	rsHardCoreEventPosY = (950 - 32)*fONE;
int	rsHardCoreEventOutLineZ = -600 * fONE;
int	rsHardCoreEvent_TicketHour = 4;

DWORD	dwHardCoreEvent_OutTime;

int	rsEventTicketCount;
int	rsEventTicketLevel[4];

int	rsHardCoreEventMode = 0;
int	rsHardCoreEventTimeOver = 0;

#define	rsEVENT_TICKET_LEVEL_TOTAL		549


struct	sSOD_USER
{
	rsPLAYINFO	*lpPlayInfo;
	DWORD		dwConnCode;
	DWORD		Temp[4];
};

#define	rsSOD_USER_MAX	120
#define	rsSOD_UPDATE_TIME	6000

sSOD_USER	rsSodUser[rsSOD_USER_MAX];
int	rsSodUserCount;
DWORD	rsTransSodTime = 0;
DWORD	dwSoD_DelayTime = 0;

int	rsSodTeamScore[4];
int	rsSodTeamRank[4];

#ifdef	_W_SERVER


#define XOR_ITEM_SeCode_0	0x536c56ba
#define XOR_ITEM_SeCode_1	0x9ab536cd
#define XOR_ITEM_SeCode_2	0xc6abce56

DWORD rsITEM_SecCode_Xor[16] = {
	0x6794bca6 ,
		0x78645fe3 ,
		0xcea82934 ,
		0x56fdca87 ,
		0x357d3653 ,
		0xf3487eba ,
		0x3478978f ,
		0x6793fbc2 ,
		0x5842eec6 ,
		0x257ecdb5 ,
		0x579cbec5 ,
		0x985612ab ,
		0x5487cc56 ,
		0xba7d4553 ,
		0xeca53b96 ,
		0xb5c549ce
};


DWORD rsRegist_EnterKey(DWORD _dwCode, DWORD _dwAdd)
{
	return rsITEM_SecCode_Xor[(_dwCode + _dwAdd) & 0xF];
}

#define	SOD_DEFAULT_DELAY	5


sHCORE_MONSTER	sHCoreEvent1[] = {
	{ { "비독" , 0, 40 }			, { "코크리스", 0, 40 }		, { "디코이", 0, 20 }		, { "", 0, 0 }		, { "", 0, 0 }		, 100 , 6 , 0 , 40 , SOD_DEFAULT_DELAY },
	{ { "바곤" , 0, 35 }		, { "스켈레톤아처", 0, 20 }		, { "크립트", 0, 45 }		, { "", 0, 0 }		, { "", 0, 0 }		, 100 , 8 , 0 , 40 , SOD_DEFAULT_DELAY },
	{ { "싸이클롭스 나이트" , 0, 35 }		, { "스켈레톤아처", 0, 30 }		, { "스켈레톤워리어", 0, 35 }		, { "", 0, 0 }		, { "언홀리 나이트", 0, 0 }		, 100 , 10 , 0 , 40 , SOD_DEFAULT_DELAY },
	{ { "헤드커터" , 0, 45 }		, { "스켈레톤레인저", 0, 25 }	, { "이블 메이플", 0, 20 }	, { "웹", 0, 10 }	, { "", 0, 0 }		, 100 , 12 , 0 , 35 , SOD_DEFAULT_DELAY * 2 },
	{ { "일루젼나이트" , 0, 30 }			, { "파이곤", 0, 20 }	, { "둠 가드", 0, 40 }		, { "그리븐", 0, 10 }	, { "", 0, 0 }		, 100 , 15 , 0 , 30 , SOD_DEFAULT_DELAY},
	{ { "헐크" , 0, 20 }			, { "파이곤", 0, 20 }	, { "슬러터", 0, 40 }		, { "쉐도우", 0, 20 }	, { "베르문 악타룬", 0, 0 }		, 100 , 18 , 0 , 25, SOD_DEFAULT_DELAY },
	{ { "오미크론" , 0, 30 }			, { "스티지언", 0, 40 }		, { "헐크", 0, 20 } 	, { "둠 가드", 0, 10 }	, { "", 0, 0 }		, 100 , 21 , 0 , 20, SOD_DEFAULT_DELAY * 3 },
	{ { "아이언 가드" , 0, 20 }			, { "킹호피", 0, 30 }		, { "인큐버스", 0, 30 }		, { "하이퍼 머신", 0, 20 }	, { "둠 로드", 0, 0 }		, 100 , 0 , 50000 , 15 , SOD_DEFAULT_DELAY },
	{ { "" , 0, 0 } 			, { "", 0, 0 } 			, { "", 0, 0 } 			, { "", 0, 0 } 		, { "", 0, 0 }		, 0 , 3 , 0 , 0}
};

sHCORE_MONSTER	sHCoreEvent2[] = {
	{ { "메핏" , 0, 40 }		, { "노쓰고블린", 0, 40 }		, { "데벌리쉬 트리", 0, 20 }		, { "", 0, 0 }		, { "", 0, 0 }		, 100 , 6 , 0 , 40	,	SOD_DEFAULT_DELAY	},
	{ { "바곤" , 0, 25 }		, { "메핏", 0, 40 }		, { "부마", 0, 35 }		, { "", 0, 0 }		, { "", 0, 0 }		, 100 , 8 , 0 , 40	,	SOD_DEFAULT_DELAY	},
	{ { "싸이클롭스 나이트" , 0, 30 }			, { "스켈레톤아처", 0, 30 }		, { "스켈레톤워리어", 0, 40 }		, { "", 0, 0 }		, { "언홀리 나이트", 0, 0 }		, 100 , 10 , 0 , 40,	SOD_DEFAULT_DELAY	},
	{ { "스켈레톤나이트" , 0, 45 }		, { "스켈레톤레인저", 0, 25 }	, { "마이어 키퍼", 0, 20 }	, { "웹", 0, 10 }	, { "", 0, 0 }		, 100 , 12 , 0 , 35,	SOD_DEFAULT_DELAY * 2	},
	{ { "슬러터" , 0, 30 }	, { "파이곤", 0, 20 }		, { "다크 나이트", 0, 40 }		, { "그리븐", 0, 10 }	, { "", 0, 0 }		, 100 , 15 , 0 , 30,	SOD_DEFAULT_DELAY	},
	{ { "헐크", 0, 20 }		, { "슬리버", 0, 20 }	, { "아벨리스크-L", 0, 40 }	, { "쉐도우" , 0, 20 }	, { "베르문 악타룬", 0, 0 }		, 100 , 18 , 0 , 25,	SOD_DEFAULT_DELAY },
	{ { "다우린" , 0, 30 }			, { "스티지언", 0, 40 }	, { "헐크", 0, 20 }	, { "둠 가드", 0, 10 }	, { "", 0, 0 }		, 100 , 21 , 0 , 20,	SOD_DEFAULT_DELAY * 3	},
	{ { "아이언 가드" , 0, 20}			, { "킹호피", 0, 30 }	, { "아벨리스크 로드", 0, 30 }	, { "하이퍼 머신", 0, 20 }	, { "둠 로드", 0, 0 }		, 100 , 0 , 50000 , 15,	SOD_DEFAULT_DELAY	},
	{ { "" , 0, 0 } 			, { "", 0, 0 } 			, { "", 0, 0 } 			, { "", 0, 0 } 		, { "", 0, 0 }		, 0 , 3 , 0 , 0}
};


sHCORE_MONSTER	sHCoreEvent3[] = {
	{ { "메핏" , 0, 40 }		, { "좀비", 0, 40 }		, { "홉고블린 칩", 0, 20 }		, { "", 0, 0 }		, { "", 0, 0 }		, 100 , 6 , 0 , 40,	SOD_DEFAULT_DELAY},
	{ { "구울" , 0, 25 }			, { "스켈레톤아처", 0, 40 }		, { "싸이클롭스", 0, 35 }	, { "", 0, 0 }		, { "", 0, 0 }		, 100 , 8 , 0 , 40,	SOD_DEFAULT_DELAY},
	{ { "마이티고블린" , 0, 30 }		, { "스켈레톤아처", 0, 30 }		, { "아머드 비틀", 0, 40 }		, { "", 0, 0 }		, { "언홀리 나이트", 0, 0 }		, 100 , 10 , 0 , 40,	SOD_DEFAULT_DELAY},
	{ { "타이탄" , 0, 45 }		, { "스켈레톤레인저", 0, 25 }		, { "머디 고렘", 0, 20 }	, { "웹", 0, 10 }	, { "", 0, 0 }		, 100 , 12 , 0 , 35,	SOD_DEFAULT_DELAY * 2},
	{ { "나이트메어" , 0, 30 }		, { "파이곤", 0, 20 }		, { "비블", 0, 40 }		, { "그리븐", 0, 10 }	, { "", 0, 0 }		, 100 , 15 , 0 , 30,	SOD_DEFAULT_DELAY},
	{ { "헐크", 0, 20 }		, { "슬리버", 0, 20 }	, { "아벨리스크-L", 0, 40 }	, { "쉐도우" , 0, 20 }	, { "베르문 악타룬", 0, 0 }		, 100 , 18 , 0 , 25,	SOD_DEFAULT_DELAY},
	{ { "오미크론" , 0, 30 }			, { "스티지언", 0, 40 }		, { "헐크", 0, 20 }	, { "둠 가드", 0, 10 }	, { "", 0, 0 }		, 100 , 21 , 0 , 20,	SOD_DEFAULT_DELAY * 3},
	{ { "아이언 가드" , 0, 20 }			, { "체인 고렘", 0, 30 }	, { "위치", 0, 30 }		, { "하이퍼 머신", 0, 20 }	, { "둠 로드", 0, 0 }		, 100 , 0 , 50000 , 15,	SOD_DEFAULT_DELAY},
	{ { "" , 0, 0 } 			, { "", 0, 0 } 			, { "", 0, 0 } 			, { "", 0, 0 } 		, { "", 0, 0 }		, 0 , 3 , 0 , 0}
};







sHCORE_MONSTER	sHCoreEvent_Bellatra[3][hCORE_ROUND_MAX];
sHCORE_MONSTER	*sHCoreEvent = sHCoreEvent2;

_sHCORE_MONSTER	hCoreMonsters[5];

TRANS_SOD_RESULT	TransSodResult;
TRANS_SOD_RESULT	TransSodResult_RealTime[5];
TRANS_SOD_RESULT	TransSodResult_Round;

int	rsHardCoreEvent_Count;
int rsHardCoreEvent_MonsterMax;

smCHAR_INFO	*rsHardCoreBoss;
int rsHardCoreEvent_OpenBoss[8];
int rsHardCoreEvent_OpenCount[8];

int	rsHardCoreEvent_TotalUser;
int	rsSoD_StartCode;
int	rsSOD_Tax = 5;
char rsSOD_Text[256] = { 0, };

#ifdef _LANGUAGE_ENGLISH

#ifdef _BELLATRA_OLD_VERSION
int	rsSOD_ScoreDiv = 35;
#else
int	rsSOD_ScoreDiv = 30;
#endif

#else

#ifdef _BELLATRA_OLD_VERSION
int	rsSOD_ScoreDiv = 18;
#else
int	rsSOD_ScoreDiv = 15;
#endif

#endif














int	rsInitHardCoreEvent()
{
	int cnt, cnt2;
	int total;

	rsHardCoreEvent_Count = 0;
	rsHardCoreEvent_TotalUser = 0;


	sHCoreEvent = sHCoreEvent1;
	cnt = 0;
	while(1)
	{
		if(sHCoreEvent[cnt].hCoreMonster1.szName[0] == 0) break;

		total = 0;


		for(cnt2 = 0; cnt2 < chrMonsterCnt; cnt2++)
		{
			if(!sHCoreEvent[cnt].hCoreMonster1.lpCharInfo &&
				lstrcmpi(sHCoreEvent[cnt].hCoreMonster1.szName, chrMonsterList[cnt2].szName) == 0)
			{
				sHCoreEvent[cnt].hCoreMonster1.lpCharInfo = &chrMonsterList[cnt2];
			}
			if(!sHCoreEvent[cnt].hCoreMonster2.lpCharInfo &&
				lstrcmpi(sHCoreEvent[cnt].hCoreMonster2.szName, chrMonsterList[cnt2].szName) == 0)
			{
				sHCoreEvent[cnt].hCoreMonster2.lpCharInfo = &chrMonsterList[cnt2];
			}
			if(!sHCoreEvent[cnt].hCoreMonster3.lpCharInfo &&
				lstrcmpi(sHCoreEvent[cnt].hCoreMonster3.szName, chrMonsterList[cnt2].szName) == 0)
			{
				sHCoreEvent[cnt].hCoreMonster3.lpCharInfo = &chrMonsterList[cnt2];
			}
			if(!sHCoreEvent[cnt].hCoreMonster4.lpCharInfo &&
				lstrcmpi(sHCoreEvent[cnt].hCoreMonster4.szName, chrMonsterList[cnt2].szName) == 0)
			{
				sHCoreEvent[cnt].hCoreMonster4.lpCharInfo = &chrMonsterList[cnt2];
			}
			if(!sHCoreEvent[cnt].hCoreMonsterBoss.lpCharInfo &&
				lstrcmpi(sHCoreEvent[cnt].hCoreMonsterBoss.szName, chrMonsterList[cnt2].szName) == 0)
			{
				sHCoreEvent[cnt].hCoreMonsterBoss.lpCharInfo = &chrMonsterList[cnt2];
			}
		}

		if(sHCoreEvent[cnt].hCoreMonster2.lpCharInfo)
			sHCoreEvent[cnt].hCoreMonster2.perCount += sHCoreEvent[cnt].hCoreMonster1.perCount;
		if(sHCoreEvent[cnt].hCoreMonster3.lpCharInfo)
			sHCoreEvent[cnt].hCoreMonster3.perCount += sHCoreEvent[cnt].hCoreMonster2.perCount;
		if(sHCoreEvent[cnt].hCoreMonster4.lpCharInfo)
			sHCoreEvent[cnt].hCoreMonster4.perCount += sHCoreEvent[cnt].hCoreMonster3.perCount;


		cnt++;
	}

	sHCoreEvent = sHCoreEvent2;
	cnt = 0;
	while(1)
	{
		if(sHCoreEvent[cnt].hCoreMonster1.szName[0] == 0) break;

		total = 0;


		for(cnt2 = 0; cnt2 < chrMonsterCnt; cnt2++)
		{
			if(!sHCoreEvent[cnt].hCoreMonster1.lpCharInfo &&
				lstrcmpi(sHCoreEvent[cnt].hCoreMonster1.szName, chrMonsterList[cnt2].szName) == 0)
			{
				sHCoreEvent[cnt].hCoreMonster1.lpCharInfo = &chrMonsterList[cnt2];
			}
			if(!sHCoreEvent[cnt].hCoreMonster2.lpCharInfo &&
				lstrcmpi(sHCoreEvent[cnt].hCoreMonster2.szName, chrMonsterList[cnt2].szName) == 0)
			{
				sHCoreEvent[cnt].hCoreMonster2.lpCharInfo = &chrMonsterList[cnt2];
			}
			if(!sHCoreEvent[cnt].hCoreMonster3.lpCharInfo &&
				lstrcmpi(sHCoreEvent[cnt].hCoreMonster3.szName, chrMonsterList[cnt2].szName) == 0)
			{
				sHCoreEvent[cnt].hCoreMonster3.lpCharInfo = &chrMonsterList[cnt2];
			}
			if(!sHCoreEvent[cnt].hCoreMonster4.lpCharInfo &&
				lstrcmpi(sHCoreEvent[cnt].hCoreMonster4.szName, chrMonsterList[cnt2].szName) == 0)
			{
				sHCoreEvent[cnt].hCoreMonster4.lpCharInfo = &chrMonsterList[cnt2];
			}
			if(!sHCoreEvent[cnt].hCoreMonsterBoss.lpCharInfo &&
				lstrcmpi(sHCoreEvent[cnt].hCoreMonsterBoss.szName, chrMonsterList[cnt2].szName) == 0)
			{
				sHCoreEvent[cnt].hCoreMonsterBoss.lpCharInfo = &chrMonsterList[cnt2];
			}
		}

		if(sHCoreEvent[cnt].hCoreMonster2.lpCharInfo)
			sHCoreEvent[cnt].hCoreMonster2.perCount += sHCoreEvent[cnt].hCoreMonster1.perCount;
		if(sHCoreEvent[cnt].hCoreMonster3.lpCharInfo)
			sHCoreEvent[cnt].hCoreMonster3.perCount += sHCoreEvent[cnt].hCoreMonster2.perCount;
		if(sHCoreEvent[cnt].hCoreMonster4.lpCharInfo)
			sHCoreEvent[cnt].hCoreMonster4.perCount += sHCoreEvent[cnt].hCoreMonster3.perCount;

		cnt++;
	}

	sHCoreEvent = sHCoreEvent3;
	cnt = 0;
	while(1)
	{
		if(sHCoreEvent[cnt].hCoreMonster1.szName[0] == 0) break;

		total = 0;


		for(cnt2 = 0; cnt2 < chrMonsterCnt; cnt2++)
		{
			if(!sHCoreEvent[cnt].hCoreMonster1.lpCharInfo &&
				lstrcmpi(sHCoreEvent[cnt].hCoreMonster1.szName, chrMonsterList[cnt2].szName) == 0)
			{
				sHCoreEvent[cnt].hCoreMonster1.lpCharInfo = &chrMonsterList[cnt2];
			}
			if(!sHCoreEvent[cnt].hCoreMonster2.lpCharInfo &&
				lstrcmpi(sHCoreEvent[cnt].hCoreMonster2.szName, chrMonsterList[cnt2].szName) == 0)
			{
				sHCoreEvent[cnt].hCoreMonster2.lpCharInfo = &chrMonsterList[cnt2];
			}
			if(!sHCoreEvent[cnt].hCoreMonster3.lpCharInfo &&
				lstrcmpi(sHCoreEvent[cnt].hCoreMonster3.szName, chrMonsterList[cnt2].szName) == 0)
			{
				sHCoreEvent[cnt].hCoreMonster3.lpCharInfo = &chrMonsterList[cnt2];
			}
			if(!sHCoreEvent[cnt].hCoreMonster4.lpCharInfo &&
				lstrcmpi(sHCoreEvent[cnt].hCoreMonster4.szName, chrMonsterList[cnt2].szName) == 0)
			{
				sHCoreEvent[cnt].hCoreMonster4.lpCharInfo = &chrMonsterList[cnt2];
			}
			if(!sHCoreEvent[cnt].hCoreMonsterBoss.lpCharInfo &&
				lstrcmpi(sHCoreEvent[cnt].hCoreMonsterBoss.szName, chrMonsterList[cnt2].szName) == 0)
			{
				sHCoreEvent[cnt].hCoreMonsterBoss.lpCharInfo = &chrMonsterList[cnt2];
			}
		}

		if(sHCoreEvent[cnt].hCoreMonster2.lpCharInfo)
			sHCoreEvent[cnt].hCoreMonster2.perCount += sHCoreEvent[cnt].hCoreMonster1.perCount;
		if(sHCoreEvent[cnt].hCoreMonster3.lpCharInfo)
			sHCoreEvent[cnt].hCoreMonster3.perCount += sHCoreEvent[cnt].hCoreMonster2.perCount;
		if(sHCoreEvent[cnt].hCoreMonster4.lpCharInfo)
			sHCoreEvent[cnt].hCoreMonster4.perCount += sHCoreEvent[cnt].hCoreMonster3.perCount;

		cnt++;
	}

	memcpy(sHCoreEvent_Bellatra[0], sHCoreEvent1, sizeof(sHCORE_MONSTER)*hCORE_ROUND_MAX);
	memcpy(sHCoreEvent_Bellatra[1], sHCoreEvent2, sizeof(sHCORE_MONSTER)*hCORE_ROUND_MAX);
	memcpy(sHCoreEvent_Bellatra[2], sHCoreEvent3, sizeof(sHCORE_MONSTER)*hCORE_ROUND_MAX);

	memcpy(&hCoreMonsters[0], &sHCoreEvent[0].hCoreMonster1, sizeof(_sHCORE_MONSTER));
	memcpy(&hCoreMonsters[1], &sHCoreEvent[0].hCoreMonster2, sizeof(_sHCORE_MONSTER));
	memcpy(&hCoreMonsters[2], &sHCoreEvent[0].hCoreMonster3, sizeof(_sHCORE_MONSTER));
	memcpy(&hCoreMonsters[3], &sHCoreEvent[0].hCoreMonster4, sizeof(_sHCORE_MONSTER));
	memcpy(&hCoreMonsters[4], &sHCoreEvent[0].hCoreMonsterBoss, sizeof(_sHCORE_MONSTER));
	rsEventTicketCount = 0;

	rsEventTicketLevel[0] = 0;
	rsEventTicketLevel[1] = 0;
	rsEventTicketLevel[2] = 0;
	rsEventTicketLevel[3] = 0;

	rsHardCoreEvent_MonsterMax = 40;

	rsSoD_StartCode = (ServerNameCode << 24) | ((tServerTime) & 0xFFFFFF);

	ZeroMemory(&TransSodResult, sizeof(TRANS_SOD_RESULT));
	ZeroMemory(&TransSodResult_RealTime[0], sizeof(TRANS_SOD_RESULT));
	ZeroMemory(&TransSodResult_RealTime[1], sizeof(TRANS_SOD_RESULT));
	ZeroMemory(&TransSodResult_RealTime[2], sizeof(TRANS_SOD_RESULT));
	ZeroMemory(&TransSodResult_RealTime[3], sizeof(TRANS_SOD_RESULT));
	ZeroMemory(&TransSodResult_RealTime[4], sizeof(TRANS_SOD_RESULT));
	ZeroMemory(&TransSodResult_Round, sizeof(TRANS_SOD_RESULT));

	ZeroMemory(rsSodTeamScore, sizeof(int) * 4);
	ZeroMemory(rsSodUser, sizeof(sSOD_USER)*rsSOD_USER_MAX);
	rsSodUserCount = 0;


	return TRUE;
}


int	rsOpen_SODConfig()
{

	int cnt, cnt2;

	if(Open_SODConfig("Bellatra\\bellatra.ini", sHCoreEvent_Bellatra[0], &rsSOD_Tax, rsSOD_Text, sizeof(rsSOD_Text), &rsSOD_ScoreDiv) == 0)
	{
		memcpy(sHCoreEvent_Bellatra[0], sHCoreEvent1, sizeof(sHCORE_MONSTER)*hCORE_ROUND_MAX);
		memcpy(sHCoreEvent_Bellatra[1], sHCoreEvent2, sizeof(sHCORE_MONSTER)*hCORE_ROUND_MAX);
		memcpy(sHCoreEvent_Bellatra[2], sHCoreEvent3, sizeof(sHCORE_MONSTER)*hCORE_ROUND_MAX);
		return FALSE;
	}


	sHCoreEvent = sHCoreEvent_Bellatra[0];
	cnt = 0;
	while(1)
	{
		if(sHCoreEvent[cnt].hCoreMonster1.szName[0] == 0) break;
		if(cnt >= rsHARDCORE_COUNT_END) break;


		for(cnt2 = 0; cnt2 < chrMonsterCnt; cnt2++)
		{
			if(!sHCoreEvent[cnt].hCoreMonster1.lpCharInfo &&
				lstrcmpi(sHCoreEvent[cnt].hCoreMonster1.szName, chrMonsterList[cnt2].szName) == 0)
			{
				sHCoreEvent[cnt].hCoreMonster1.lpCharInfo = &chrMonsterList[cnt2];
			}
			if(!sHCoreEvent[cnt].hCoreMonster2.lpCharInfo &&
				lstrcmpi(sHCoreEvent[cnt].hCoreMonster2.szName, chrMonsterList[cnt2].szName) == 0)
			{
				sHCoreEvent[cnt].hCoreMonster2.lpCharInfo = &chrMonsterList[cnt2];
			}
			if(!sHCoreEvent[cnt].hCoreMonster3.lpCharInfo &&
				lstrcmpi(sHCoreEvent[cnt].hCoreMonster3.szName, chrMonsterList[cnt2].szName) == 0)
			{
				sHCoreEvent[cnt].hCoreMonster3.lpCharInfo = &chrMonsterList[cnt2];
			}
			if(!sHCoreEvent[cnt].hCoreMonster4.lpCharInfo &&
				lstrcmpi(sHCoreEvent[cnt].hCoreMonster4.szName, chrMonsterList[cnt2].szName) == 0)
			{
				sHCoreEvent[cnt].hCoreMonster4.lpCharInfo = &chrMonsterList[cnt2];
			}
			if(!sHCoreEvent[cnt].hCoreMonsterBoss.lpCharInfo &&
				lstrcmpi(sHCoreEvent[cnt].hCoreMonsterBoss.szName, chrMonsterList[cnt2].szName) == 0)
			{
				sHCoreEvent[cnt].hCoreMonsterBoss.lpCharInfo = &chrMonsterList[cnt2];
			}
		}

		if(sHCoreEvent[cnt].hCoreMonster2.lpCharInfo)
			sHCoreEvent[cnt].hCoreMonster2.perCount += sHCoreEvent[cnt].hCoreMonster1.perCount;
		if(sHCoreEvent[cnt].hCoreMonster3.lpCharInfo)
			sHCoreEvent[cnt].hCoreMonster3.perCount += sHCoreEvent[cnt].hCoreMonster2.perCount;
		if(sHCoreEvent[cnt].hCoreMonster4.lpCharInfo)
			sHCoreEvent[cnt].hCoreMonster4.perCount += sHCoreEvent[cnt].hCoreMonster3.perCount;


		cnt++;
	}

	memcpy(sHCoreEvent_Bellatra[1], sHCoreEvent, sizeof(sHCORE_MONSTER)*hCORE_ROUND_MAX);
	memcpy(sHCoreEvent_Bellatra[2], sHCoreEvent, sizeof(sHCORE_MONSTER)*hCORE_ROUND_MAX);

	return TRUE;
}




int	rsGetHardCoreEventOpenMonsterPos(int *mx, int *my, int *mz, int Room)
{
	int x, y, z;
	int cx, cz;

	x = rsHardCoreEventOpenPos[Room][0].x;
	y = rsHardCoreEventOpenPos[Room][0].y;
	z = rsHardCoreEventOpenPos[Room][0].z;

	cx = rsHardCoreEventOpenPos[Room][1].x - x;
	cz = z - rsHardCoreEventOpenPos[Room][1].z;

	cx = rand() % cx;
	cz = rand() % cz;

	*mx = (x + cx)*fONE;
	*mz = (z - cz)*fONE;
	*my = y*fONE;

	return TRUE;
}


int rsSetSodTeamRank()
{
	int cnt, cnt1;
	int r1, r2;

	rsSodTeamRank[0] = 0;
	rsSodTeamRank[1] = 1;
	rsSodTeamRank[2] = 2;
	rsSodTeamRank[3] = 3;

	for(cnt = 0; cnt < 4; cnt++)
	{
		for(cnt1 = cnt; cnt1 < 4; cnt1++)
		{
			r1 = rsSodTeamRank[cnt];
			r2 = rsSodTeamRank[cnt1];

			if(rsSodTeamScore[r1] < rsSodTeamScore[r2])
			{
				rsSodTeamRank[cnt] = r2;
				rsSodTeamRank[cnt1] = r1;
			}
		}
	}

	return TRUE;
}

int rsHardCoreEvent_OpenMonster(STG_AREA *lpStgArea, STG_CHAR_INFO *lpStgCharInfo)
{

	STG_CHAR_INFO		 StgCharInfo;

	TRANS_CHATMESSAGE	TransChatMessage;
	TRANS_CHATMESSAGE	TransChatMessage2;
	smTRANS_COMMAND		smTransCommand;
	smTRANS_COMMAND		smTransCommand2;

	smCHAR	*lpChar;
	int x, y, z;
	int total;
	int	total2;
	int totalScore;

	int cnt, mcnt;
	int	rnk;
	int	money;

	if(rsHardCoreEventTimeOver)
	{
		if(rsHardCoreEventMode)
			rsHardCoreEventTimeOver = FALSE;
		else
			return TRUE;
	}

	if(dwServ_GameTimeHour == sHCoreEvent[rsHardCoreEvent_Count].StartHour)
	{

		if(rsHardCoreEvent_Count == 0)
			rsOpen_SODConfig();


		for(cnt = 0; cnt < STG_MONSTER_MAX; cnt++)
		{
			if(lpStgArea->lpCharMonster[cnt])
			{
				if(lpStgArea->lpCharMonster[cnt]->Flag && lpStgArea->lpCharMonster[cnt]->PartyFlag == rsHARDCORE_EVENT_FLAG &&
					lpStgArea->lpCharMonster[cnt]->MotionInfo->State != CHRMOTION_STATE_DEAD)
				{
					lpStgArea->lpCharMonster[cnt]->smCharInfo.Life[0] = 0;
					lpStgArea->lpCharMonster[cnt]->SetMotionFromCode(CHRMOTION_STATE_DEAD);

					if(!sHCoreEvent[rsHardCoreEvent_Count].hCoreMonster1.szName[0])
					{

						lpStgArea->lpCharMonster[cnt]->PartyParam = (sinPM1 | sin04);


						if(rsPushKillMonster(lpStgArea->lpCharMonster[cnt], 0, ((STG_AREA *)lpStgArea->lpCharMonster[cnt]->lpExt1)) == FALSE)
						{
							CreatePresentItem(lpStgArea->lpCharMonster[cnt]->PartyParam, ((STG_AREA *)lpStgArea->lpCharMonster[cnt]->lpExt1), lpStgArea->lpCharMonster[cnt]->pX, lpStgArea->lpCharMonster[cnt]->pY, lpStgArea->lpCharMonster[cnt]->pZ, 3);
						}
					}

				}
			}
		}

		if(sHCoreEvent[rsHardCoreEvent_Count].State > 0)
		{
			total = 0;
			for(cnt = 0; cnt < CONNECTMAX; cnt++)
			{
				if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].EventMode == rsHARDCORE_EVENT_FLAG)
				{
					if(rsCheckHardCoreEventArea(rsPlayInfo[cnt].Position.x, rsPlayInfo[cnt].Position.y, rsPlayInfo[cnt].Position.z) == TRUE)
					{
						if(total < rsPlayInfo[cnt].EventScore)
							total = rsPlayInfo[cnt].EventScore;
					}
				}
			}
			if(total < sHCoreEvent[rsHardCoreEvent_Count].State)
			{
				rsHardCoreEvent_Count++;
			}
		}

		if(!sHCoreEvent[rsHardCoreEvent_Count].hCoreMonster1.szName[0])
		{


			switch(rand() % 3)
			{
			case 0:
				sHCoreEvent = sHCoreEvent_Bellatra[0];
				break;
			case 1:
				sHCoreEvent = sHCoreEvent_Bellatra[1];
				break;
			case 2:
				sHCoreEvent = sHCoreEvent_Bellatra[2];
				break;
			}

			rsHardCoreEvent_Count = 0;
			memcpy(&hCoreMonsters[0], &sHCoreEvent[rsHardCoreEvent_Count].hCoreMonster1, sizeof(_sHCORE_MONSTER));
			memcpy(&hCoreMonsters[1], &sHCoreEvent[rsHardCoreEvent_Count].hCoreMonster2, sizeof(_sHCORE_MONSTER));
			memcpy(&hCoreMonsters[2], &sHCoreEvent[rsHardCoreEvent_Count].hCoreMonster3, sizeof(_sHCORE_MONSTER));
			memcpy(&hCoreMonsters[3], &sHCoreEvent[rsHardCoreEvent_Count].hCoreMonster4, sizeof(_sHCORE_MONSTER));
			memcpy(&hCoreMonsters[4], &sHCoreEvent[rsHardCoreEvent_Count].hCoreMonsterBoss, sizeof(_sHCORE_MONSTER));

			rsHardCoreEvent_MonsterMax = sHCoreEvent[rsHardCoreEvent_Count].MaxMonster;
			ZeroMemory(rsHardCoreEvent_OpenBoss, sizeof(int) * 8);
			ZeroMemory(rsHardCoreEvent_OpenCount, sizeof(int) * 8);
			rsHardCoreBoss = sHCoreEvent[rsHardCoreEvent_Count].hCoreMonsterBoss.lpCharInfo;

			dwHardCoreEvent_OutTime = dwPlayServTime + 30000;
			rsEventTicketCount = 0;
			rsEventTicketLevel[0] = 0;
			rsEventTicketLevel[1] = 0;
			rsEventTicketLevel[2] = 0;
			rsEventTicketLevel[3] = 0;

			TransChatMessage.code = OpCode::OPCODE_MESSAGEBOX;
			TransChatMessage.dwIP = 0;
			TransChatMessage.dwObjectSerial = 0;


			total2 = 0;
			totalScore = 0;
			for(cnt = 0; cnt < CONNECTMAX; cnt++)
			{
				if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].EventMode == rsHARDCORE_EVENT_FLAG)
				{
					if(rsCheckHardCoreEventArea(rsPlayInfo[cnt].Position.x, rsPlayInfo[cnt].Position.y, rsPlayInfo[cnt].Position.z) == TRUE)
					{
						totalScore += rsPlayInfo[cnt].EventScore;
						total2++;
					}
				}
			}

			ZeroMemory(&TransSodResult, sizeof(TRANS_SOD_RESULT));

			for(cnt = 0; cnt < CONNECTMAX; cnt++)
			{
				if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].EventMode == rsHARDCORE_EVENT_FLAG)
				{
					if(rsCheckHardCoreEventArea(rsPlayInfo[cnt].Position.x, rsPlayInfo[cnt].Position.y, rsPlayInfo[cnt].Position.z) == TRUE)
					{

						money = rsPlayInfo[cnt].EventScore - ((rsPlayInfo[cnt].EventScore*rsSOD_Tax) / 100);


						ZeroMemory(&smTransCommand, sizeof(smTRANS_COMMAND));
						smTransCommand.code = OpCode::OPCODE_SOD_INFOMATION;
						smTransCommand.size = sizeof(smTRANS_COMMAND);
						smTransCommand.WParam = 4;
						smTransCommand.LParam = rsHardCoreEvent_Count;
						smTransCommand.SParam = 100;
						smTransCommand.EParam = money;
						rsPlayInfo[cnt].lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);


						if(TransSodResult.ResultCount < SOD_RESULT_MAX && !rsPlayInfo[cnt].HideMode)
						{
							TransSodResult.Result[TransSodResult.ResultCount].lpPlayInfo = &rsPlayInfo[cnt];
							strcpy_s(TransSodResult.Result[TransSodResult.ResultCount].szName, rsPlayInfo[cnt].smCharInfo.szName);
							TransSodResult.Result[TransSodResult.ResultCount].Class = rsPlayInfo[cnt].smCharInfo.ClassClan;
							TransSodResult.Result[TransSodResult.ResultCount].JobCode = rsPlayInfo[cnt].smCharInfo.JOB_CODE;
							TransSodResult.Result[TransSodResult.ResultCount].Score = rsPlayInfo[cnt].EventScore;
							TransSodResult.Result[TransSodResult.ResultCount].Monster = rsPlayInfo[cnt].EventCount;
							TransSodResult.ResultCount++;
						}

						mcnt = money;


						if(dwSerToSerIP)
						{
							if(rsSendMoneyToSystemLine(&rsPlayInfo[cnt], mcnt) == TRUE)
							{
								mcnt = 0;
							}
						}

						if(mcnt)
						{


							rsSendMoneyToUser(&rsPlayInfo[cnt], mcnt);


						}



						rsSend_ResultSOD(&rsPlayInfo[cnt], rsPlayInfo[cnt].EventScore, rsPlayInfo[cnt].EventCount, totalScore, total2, rsHardCoreEvent_TotalUser, rsSoD_StartCode);

						if(rsPlayInfo[cnt].EventScore >= 400000)
						{


							smTransCommand.size = sizeof(smTRANS_COMMAND);
							smTransCommand.code = OpCode::OPCODE_SET_BLACKLIST;
							smTransCommand.WParam = 21000;
							smTransCommand.SParam = rsPlayInfo[cnt].EventMode;
							smTransCommand.LParam = rsPlayInfo[cnt].EventScore;
							rsSendDataServer(rsPlayInfo[cnt].lpsmSock, &smTransCommand);

						}

					}
					else
					{

						rsSend_ResultSOD(&rsPlayInfo[cnt], 0, rsPlayInfo[cnt].EventCount, 0, 0, rsHardCoreEvent_TotalUser, rsSoD_StartCode);
					}
				}
			}


			TransSodResult.code = OpCode::OPCODE_SOD_RESULT;
			TransSodResult.size = sizeof(TRANS_SOD_RESULT) - ((SOD_RESULT_MAX - TransSodResult.ResultCount) * sizeof(_SOD_RESULT));
			TransSodResult.dwGameCode = rsSoD_StartCode;
			TransSodResult.dwGameTime = (DWORD)tServerTime;
			TransSodResult.dwDisplayMode = TRUE;

			for(cnt = 0; cnt < TransSodResult.ResultCount; cnt++)
			{
				if(TransSodResult.Result[cnt].lpPlayInfo && TransSodResult.Result[cnt].lpPlayInfo->lpsmSock)
				{
					TransSodResult.Result[cnt].lpPlayInfo->lpsmSock->Send((char *)&TransSodResult, TransSodResult.size, TRUE);
				}
			}
			TransSodResult.dwDisplayMode = FALSE;

			return TRUE;
		}


		memcpy(&hCoreMonsters[0], &sHCoreEvent[rsHardCoreEvent_Count].hCoreMonster1, sizeof(_sHCORE_MONSTER));
		memcpy(&hCoreMonsters[1], &sHCoreEvent[rsHardCoreEvent_Count].hCoreMonster2, sizeof(_sHCORE_MONSTER));
		memcpy(&hCoreMonsters[2], &sHCoreEvent[rsHardCoreEvent_Count].hCoreMonster3, sizeof(_sHCORE_MONSTER));
		memcpy(&hCoreMonsters[3], &sHCoreEvent[rsHardCoreEvent_Count].hCoreMonster4, sizeof(_sHCORE_MONSTER));
		memcpy(&hCoreMonsters[4], &sHCoreEvent[rsHardCoreEvent_Count].hCoreMonsterBoss, sizeof(_sHCORE_MONSTER));

		rsHardCoreEvent_MonsterMax = sHCoreEvent[rsHardCoreEvent_Count].MaxMonster;
		ZeroMemory(rsHardCoreEvent_OpenBoss, sizeof(int) * 8);
		ZeroMemory(rsHardCoreEvent_OpenCount, sizeof(int) * 8);
		rsHardCoreBoss = sHCoreEvent[rsHardCoreEvent_Count].hCoreMonsterBoss.lpCharInfo;

		if(hCoreMonsters[0].lpCharInfo)
		{

			dwSoD_DelayTime = dwPlayServTime + sHCoreEvent[rsHardCoreEvent_Count].DelayTime * 1000;


			ZeroMemory(&smTransCommand2, sizeof(smTRANS_COMMAND));
			smTransCommand2.code = OpCode::OPCODE_SOD_INFOMATION;
			smTransCommand2.size = sizeof(smTRANS_COMMAND);
			smTransCommand2.WParam = 1;
			smTransCommand2.LParam = rsHardCoreEvent_Count;
			smTransCommand2.SParam = -1;


			ZeroMemory(&smTransCommand, sizeof(smTRANS_COMMAND));
			smTransCommand.code = OpCode::OPCODE_SOD_INFOMATION;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = 3;
			smTransCommand.LParam = rsHardCoreEvent_Count;
			smTransCommand.SParam = -1;


			rsSetSodTeamRank();

			if(rsHardCoreEvent_Count == 3 || rsHardCoreEvent_Count == 6)
			{

				for(cnt = 0; cnt < CONNECTMAX; cnt++)
				{
					if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].EventMode == rsHARDCORE_EVENT_FLAG)
					{
						if(rsCheckHardCoreEventArea(rsPlayInfo[cnt].Position.x, rsPlayInfo[cnt].Position.y, rsPlayInfo[cnt].Position.z) == TRUE)
						{

							if(rsPlayInfo[cnt].sEventParam[0] == rsSodTeamRank[0] || (rsPlayInfo[cnt].sEventParam[0] == rsSodTeamRank[1] && rsHardCoreEvent_Count == 3))
							{


								if(rsPlayInfo[cnt].sEventParam[0] == rsSodTeamRank[0])
									smTransCommand2.SParam = rsSod_RoundRoomTable[0][rsHardCoreEvent_Count];
								else
									smTransCommand2.SParam = rsSod_RoundRoomTable[2][rsHardCoreEvent_Count];

								rsPlayInfo[cnt].lpsmSock->Send((char *)&smTransCommand2, smTransCommand2.size, TRUE);

							}
							else
							{


								rsPlayInfo[cnt].lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);


								rsSend_ResultSOD(&rsPlayInfo[cnt], -rsPlayInfo[cnt].EventScore, rsPlayInfo[cnt].EventCount, 0, 0, rsHardCoreEvent_TotalUser, rsSoD_StartCode);

#ifdef _BELLATRA_OLD_VERSION_NOMOEY
								money = 0;
#else
								money = rsPlayInfo[cnt].EventScore - ((rsPlayInfo[cnt].EventScore*rsSOD_Tax) / 100);


								if(dwSerToSerIP && rsSendMoneyToSystemLine(&rsPlayInfo[cnt], money) == TRUE)
								{

								}
								else
								{

									rsSendMoneyToUser(&rsPlayInfo[cnt], money);
								}
#endif
								rsPlayInfo[cnt].EventMode = 0;
								rsPlayInfo[cnt].EventScore = 0;
								rsPlayInfo[cnt].EventCount = 0;

								rnk = 1;
								if(rsPlayInfo[cnt].sEventParam[0] == rsSodTeamRank[1]) rnk = 2;
								if(rsPlayInfo[cnt].sEventParam[0] == rsSodTeamRank[2]) rnk = 3;
								if(rsPlayInfo[cnt].sEventParam[0] == rsSodTeamRank[3]) rnk = 4;




								wsprintf(TransChatMessage2.szMessage, srMsg_110, rnk, money);
								TransChatMessage2.code = OpCode::OPCODE_MESSAGEBOX;
								TransChatMessage2.size = 32 + lstrlen(TransChatMessage2.szMessage);
								TransChatMessage2.dwIP = 0;
								TransChatMessage2.dwObjectSerial = 0;

								rsPlayInfo[cnt].lpsmSock->Send((char *)&TransChatMessage2, TransChatMessage2.size, TRUE);

							}
						}
					}
				}
				smTransCommand2.size = 0;
			}
		}

		total = 0;
		for(cnt = 0; cnt < CONNECTMAX; cnt++)
		{
			if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].EventMode == rsHARDCORE_EVENT_FLAG)
			{
				if(rsCheckHardCoreEventArea(rsPlayInfo[cnt].Position.x, rsPlayInfo[cnt].Position.y, rsPlayInfo[cnt].Position.z) == TRUE)
				{

					if(smTransCommand2.size)
						rsPlayInfo[cnt].lpsmSock->Send((char *)&smTransCommand2, smTransCommand2.size, TRUE);
					total++;

				}
				else
				{
					rsPlayInfo[cnt].EventMode = 0;

					rsSend_ResultSOD(&rsPlayInfo[cnt], 0, rsPlayInfo[cnt].EventCount, 0, 0, rsHardCoreEvent_TotalUser, rsSoD_StartCode);
				}

			}
		}

		rsHardCoreEvent_Count++;

		return FALSE;
	}

	if(!rsHardCoreEvent_Count)
	{

		if(dwHardCoreEvent_OutTime && dwHardCoreEvent_OutTime < dwPlayServTime)
		{
			for(cnt = 0; cnt < CONNECTMAX; cnt++)
			{
				if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].EventMode == rsHARDCORE_EVENT_FLAG)
				{
					rsPlayInfo[cnt].EventMode = 0;
					rsPlayInfo[cnt].EventScore = 0;
					rsPlayInfo[cnt].EventCount = 0;

					if(rsCheckHardCoreEventArea(rsPlayInfo[cnt].Position.x, rsPlayInfo[cnt].Position.y, rsPlayInfo[cnt].Position.z) == TRUE)
					{
						smTransCommand.WParam = rsSOD_VILLAGE;
						smTransCommand.code = OpCode::OPCODE_WARPFIELD;
						smTransCommand.size = sizeof(smTRANS_COMMAND);
						smTransCommand.SParam = StageArea[rsSOD_VILLAGE].lpField->cX*fONE;
						smTransCommand.LParam = StageArea[rsSOD_VILLAGE].lpField->cZ*fONE;
						rsPlayInfo[cnt].lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
					}

				}
			}
			rsHardCoreEvent_TotalUser = 0;
			dwHardCoreEvent_OutTime = 0;
			if(!rsHardCoreEventMode) rsHardCoreEventTimeOver = TRUE;

			rsSoD_StartCode = (ServerNameCode << 24) | ((tServerTime) & 0xFFFFFF);
			ZeroMemory(rsSodTeamScore, sizeof(int) * 4);

			ZeroMemory(rsSodUser, sizeof(sSOD_USER)*rsSOD_USER_MAX);
			rsSodUserCount = 0;

		}

		return FALSE;
	}

	if(rsTransSodTime < dwPlayServTime)
	{
		rsTransUpdateSod(0);
		rsTransSodTime = dwPlayServTime + rsSOD_UPDATE_TIME;
	}

	int	RndCnt;
	int	MonMax[8];
	int	SodRoundCount = rsHardCoreEvent_Count - 1;

	if(SodRoundCount<0 || SodRoundCount >= 8 || dwSoD_DelayTime>dwPlayServTime)
		return FALSE;

	ZeroMemory(MonMax, sizeof(int) * 8);

	for(cnt = 0; cnt < STG_MONSTER_MAX; cnt++)
	{
		if(lpStgArea->lpCharMonster[cnt])
		{
			if(lpStgArea->lpCharMonster[cnt]->Flag && lpStgArea->lpCharMonster[cnt]->PartyFlag == rsHARDCORE_EVENT_FLAG &&
				lpStgArea->lpCharMonster[cnt]->MotionInfo->State != CHRMOTION_STATE_DEAD)
			{

				if(lpStgArea->lpCharMonster[cnt]->PartyParam >= 0 && lpStgArea->lpCharMonster[cnt]->PartyParam < 8)
				{
					MonMax[lpStgArea->lpCharMonster[cnt]->PartyParam]++;
				}
			}
		}
	}

	for(RndCnt = rsSod_RoundTable[SodRoundCount][0]; RndCnt < rsSod_RoundTable[SodRoundCount][1]; RndCnt++)
	{

		mcnt = MonMax[RndCnt];

		if(mcnt > rsHardCoreEvent_MonsterMax)
		{
			continue;
		}

		if(rsHardCoreBoss && !rsHardCoreEvent_OpenBoss[RndCnt] && rsHardCoreEvent_OpenCount[RndCnt] > (rsHardCoreEvent_MonsterMax - 10))
		{

			memcpy(&lpStgCharInfo->smCharInfo, rsHardCoreBoss, sizeof(smCHAR_INFO));
			rsHardCoreEvent_OpenBoss[RndCnt] ++;
		}
		else
		{
			cnt = rand() % 100;
			if(hCoreMonsters[0].lpCharInfo && cnt <= hCoreMonsters[0].perCount)
			{
				memcpy(&lpStgCharInfo->smCharInfo, hCoreMonsters[0].lpCharInfo, sizeof(smCHAR_INFO));
			}
			else if(hCoreMonsters[1].lpCharInfo && cnt <= hCoreMonsters[1].perCount)
			{
				memcpy(&lpStgCharInfo->smCharInfo, hCoreMonsters[1].lpCharInfo, sizeof(smCHAR_INFO));
			}
			else if(hCoreMonsters[2].lpCharInfo && cnt <= hCoreMonsters[2].perCount)
			{
				memcpy(&lpStgCharInfo->smCharInfo, hCoreMonsters[2].lpCharInfo, sizeof(smCHAR_INFO));
			}
			else if(hCoreMonsters[3].lpCharInfo && cnt <= hCoreMonsters[3].perCount)
			{
				memcpy(&lpStgCharInfo->smCharInfo, hCoreMonsters[3].lpCharInfo, sizeof(smCHAR_INFO));
			}
		}

		rsGetHardCoreEventOpenMonsterPos(&x, &y, &z, RndCnt);

		StgCharInfo.PosiState = smCHAR_STATE_ENEMY;
		StgCharInfo.smCharInfo.Life[0] = 100;
		StgCharInfo.smCharInfo.Mana[0] = 100;
		StgCharInfo.smCharInfo.Life[1] = 100;
		StgCharInfo.smCharInfo.State = TRUE;

		lpStgArea->EvnMonster = TRUE;
		lpChar = lpStgArea->OpenMonster(lpStgCharInfo, 0);
		if(lpChar)
		{
			lpChar->pX = x;
			lpChar->pY = y;
			lpChar->pZ = z;
			lpChar->SetMotionFromCode(CHRMOTION_STATE_STAND);
			lpChar->TargetMoveCount = 0;
			lpChar->PartyFlag = rsHARDCORE_EVENT_FLAG;
			lpChar->PartyParam = RndCnt;

			lpChar->PosiAround.x = rsHardCoreEventOpenPos[RndCnt][2].x*fONE;
			lpChar->PosiAround.y = rsHardCoreEventOpenPos[RndCnt][2].y*fONE;
			lpChar->PosiAround.z = rsHardCoreEventOpenPos[RndCnt][2].z*fONE;
			lpChar->DistAroundDbl = (12 * 64 * 12 * 64);

			lpChar->smCharInfo.Sight = 800 * 800;

			rsHardCoreEvent_OpenCount[RndCnt]++;

			continue;
		}
	}

	return FALSE;
}

DWORD	dwSodRealScore_Time[5] = { 0,0,0,0,0 };


TRANS_SOD_RESULT *rsSod_GetRealTimeScore(rsPLAYINFO *lpPlayInfo, int TeamNum)
{
	int cnt, rc;
	int	Team;

	Team = TeamNum;
	if(Team > 4 || Team < 0) Team = 0;

	if((dwSodRealScore_Time[Team] + 10000) < dwPlayServTime)
	{

		ZeroMemory(&TransSodResult_RealTime[Team], sizeof(TRANS_SOD_RESULT));

		for(cnt = 0; cnt < CONNECTMAX; cnt++)
		{
			if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].EventMode == rsHARDCORE_EVENT_FLAG && (Team == 0 || (rsPlayInfo[cnt].sEventParam[0] + 1) == Team))
			{
				if(!rsPlayInfo[cnt].HideMode && rsCheckHardCoreEventArea(rsPlayInfo[cnt].Position.x, rsPlayInfo[cnt].Position.y, rsPlayInfo[cnt].Position.z) == TRUE)
				{

					if(TransSodResult_RealTime[Team].ResultCount < SOD_RESULT_MAX)
					{
						rc = TransSodResult_RealTime[Team].ResultCount;
						TransSodResult_RealTime[Team].Result[rc].lpPlayInfo = &rsPlayInfo[cnt];
						strcpy_s(TransSodResult_RealTime[Team].Result[rc].szName, rsPlayInfo[cnt].smCharInfo.szName);
						TransSodResult_RealTime[Team].Result[rc].Class = rsPlayInfo[cnt].smCharInfo.ClassClan;
						TransSodResult_RealTime[Team].Result[rc].JobCode = rsPlayInfo[cnt].smCharInfo.JOB_CODE;
						TransSodResult_RealTime[Team].Result[rc].Score = rsPlayInfo[cnt].EventScore;
						TransSodResult_RealTime[Team].Result[rc].Monster = rsPlayInfo[cnt].EventCount;
						TransSodResult_RealTime[Team].ResultCount++;
					}
				}
			}
		}

		dwSodRealScore_Time[Team] = dwPlayServTime;
	}

	if(TransSodResult_RealTime[Team].ResultCount == 0) return NULL;

	TransSodResult_RealTime[Team].code = OpCode::OPCODE_SOD_RESULT2;
	TransSodResult_RealTime[Team].size = sizeof(TRANS_SOD_RESULT) - ((SOD_RESULT_MAX - TransSodResult_RealTime[Team].ResultCount) * sizeof(_SOD_RESULT));
	TransSodResult_RealTime[Team].dwGameCode = rsSoD_StartCode;
	TransSodResult_RealTime[Team].dwGameTime = (DWORD)tServerTime;
	TransSodResult_RealTime[Team].dwDisplayMode = TRUE;

	if(lpPlayInfo && lpPlayInfo->lpsmSock)
		lpPlayInfo->lpsmSock->Send((char *)&TransSodResult_RealTime[Team], TransSodResult_RealTime[Team].size, TRUE);


	return &TransSodResult_RealTime[Team];
}





int	rsTransUpdateSod(rsPLAYINFO *lpPlayInfo)
{

	int cnt, SndCount;
	smTRANS_COMMAND_SOD	smTransCommand;

	ZeroMemory(&smTransCommand, sizeof(smTRANS_COMMAND_SOD));
	smTransCommand.smTransCommand.size = sizeof(smTRANS_COMMAND_SOD);
	smTransCommand.smTransCommand.code = OpCode::OPCODE_SOD_INFOMATION;
	smTransCommand.smTransCommand.WParam = 2;

	smTransCommand.smTransCommand.SParam = rsHardCoreEvent_Count;


	smTransCommand.TeamScore[0] = rsSodTeamScore[0];
	smTransCommand.TeamScore[1] = rsSodTeamScore[1];
	smTransCommand.TeamScore[2] = rsSodTeamScore[2];
	smTransCommand.TeamScore[3] = rsSodTeamScore[3];

	SndCount = 0;

	if(lpPlayInfo)
	{

		if(lpPlayInfo->lpsmSock && lpPlayInfo->EventMode == rsHARDCORE_EVENT_FLAG)
		{
			smTransCommand.MyScore = lpPlayInfo->EventScore;
			smTransCommand.MyTeam = lpPlayInfo->sEventParam[0];
			smTransCommand.smTransCommand.LParam = 1;

			lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.smTransCommand.size, TRUE);
			SndCount++;
		}
	}
	else
	{

		for(cnt = 0; cnt < rsSodUserCount; cnt++)
		{
			if(rsSodUser[cnt].lpPlayInfo && rsSodUser[cnt].lpPlayInfo->lpsmSock &&
				rsSodUser[cnt].lpPlayInfo->EventMode == rsHARDCORE_EVENT_FLAG &&
				rsSodUser[cnt].lpPlayInfo->dwConnectCount == rsSodUser[cnt].dwConnCode)
			{

				smTransCommand.MyScore = rsSodUser[cnt].lpPlayInfo->EventScore;
				smTransCommand.MyTeam = rsSodUser[cnt].lpPlayInfo->sEventParam[0];
				rsSodUser[cnt].lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.smTransCommand.size, TRUE);
				SndCount++;
			}
		}
	}


	return SndCount;
}


int rsShowHardCoreEventScore(rsPLAYINFO *lpPlayInfo)
{



	if((lpPlayInfo->dwEventTime + 500) > dwPlayServTime) return FALSE;

	lpPlayInfo->dwEventTime = dwPlayServTime;

	rsTransUpdateSod(lpPlayInfo);

	return TRUE;
}


int rsShowHardCoreEventScore2(rsPLAYINFO *lpPlayInfo, smCHAR *lpChar, int Score)
{
	TRANS_CHATMESSAGE	TransChatMessage;

	wsprintf(TransChatMessage.szMessage, srMsg_111, lpChar->smCharInfo.szName, Score);
	TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
	TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
	TransChatMessage.dwIP = 3;
	TransChatMessage.dwObjectSerial = 0;

	if(lpPlayInfo && lpPlayInfo->lpsmSock)
	{
		lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
	}

	return TRUE;
}



int rsSoD_CatchItem_SD201(rsPLAYINFO *lpPlayInfo, int StagePos, STG_AREA	*lpStgArea)
{
	int cnt;
	int	Damage;
	int x, z;

	for(cnt = 0; cnt < STG_MONSTER_MAX; cnt++)
	{
		if(lpStgArea->lpCharMonster[cnt])
		{
			if(lpStgArea->lpCharMonster[cnt]->Flag && lpStgArea->lpCharMonster[cnt]->PartyFlag == rsHARDCORE_EVENT_FLAG &&
				lpStgArea->lpCharMonster[cnt]->MotionInfo->State != CHRMOTION_STATE_DEAD &&
				lpStgArea->lpCharMonster[cnt]->smCharInfo.wPlayClass[0] != MONSTER_CLASS_BOSS)
			{

				x = lpStgArea->lpCharMonster[cnt]->pX >> FLOATNS;
				z = lpStgArea->lpCharMonster[cnt]->pZ >> FLOATNS;

				if(x > rsHardCoreEventOpenPos[StagePos][0].x && x<rsHardCoreEventOpenPos[StagePos][1].x &&
					z>rsHardCoreEventOpenPos[StagePos][1].z && z < rsHardCoreEventOpenPos[StagePos][0].z)
				{

					Damage = lpStgArea->lpCharMonster[cnt]->smCharInfo.Life[1] / 3;

					lpStgArea->lpCharMonster[cnt]->smCharInfo.Life[0] -= Damage;
					if(lpStgArea->lpCharMonster[cnt]->smCharInfo.Life[0] <= 0)
					{
						lpStgArea->lpCharMonster[cnt]->smCharInfo.Life[0] = 1;
					}

					lpStgArea->lpCharMonster[cnt]->SetMotionFromCode(CHRMOTION_STATE_DAMAGE);
				}
			}
		}
	}


	return TRUE;
}


int rsSoD_CatchItem_SD202(rsPLAYINFO *lpPlayInfo, int StagePos, STG_AREA	*lpStgArea)
{
	int cnt;
	int x, z;

	for(cnt = 0; cnt < STG_MONSTER_MAX; cnt++)
	{
		if(lpStgArea->lpCharMonster[cnt])
		{
			if(lpStgArea->lpCharMonster[cnt]->Flag && lpStgArea->lpCharMonster[cnt]->PartyFlag == rsHARDCORE_EVENT_FLAG &&
				lpStgArea->lpCharMonster[cnt]->MotionInfo->State != CHRMOTION_STATE_DEAD)
			{

				x = lpStgArea->lpCharMonster[cnt]->pX >> FLOATNS;
				z = lpStgArea->lpCharMonster[cnt]->pZ >> FLOATNS;

				if(x > rsHardCoreEventOpenPos[StagePos][0].x && x<rsHardCoreEventOpenPos[StagePos][1].x &&
					z>rsHardCoreEventOpenPos[StagePos][1].z && z < rsHardCoreEventOpenPos[StagePos][0].z)
				{

					lpStgArea->lpCharMonster[cnt]->SetMotionFromCode(CHRMOTION_STATE_DAMAGE);
					lpStgArea->lpCharMonster[cnt]->PlayStunCount = 16 * 10;
				}
			}
		}
	}


	return TRUE;
}


int rsSoD_CatchItem_SD203(rsPLAYINFO *lpPlayInfo, int StagePos, STG_AREA	*lpStgArea)
{
	int cnt;
	int x, z;

	for(cnt = 0; cnt < STG_MONSTER_MAX; cnt++)
	{
		if(lpStgArea->lpCharMonster[cnt])
		{
			if(lpStgArea->lpCharMonster[cnt]->Flag && lpStgArea->lpCharMonster[cnt]->PartyFlag == rsHARDCORE_EVENT_FLAG &&
				lpStgArea->lpCharMonster[cnt]->MotionInfo->State != CHRMOTION_STATE_DEAD)
			{

				x = lpStgArea->lpCharMonster[cnt]->pX >> FLOATNS;
				z = lpStgArea->lpCharMonster[cnt]->pZ >> FLOATNS;

				if(x > rsHardCoreEventOpenPos[StagePos][0].x && x<rsHardCoreEventOpenPos[StagePos][1].x &&
					z>rsHardCoreEventOpenPos[StagePos][1].z && z < rsHardCoreEventOpenPos[StagePos][0].z)
				{

					lpStgArea->lpCharMonster[cnt]->SetMotionFromCode(CHRMOTION_STATE_DAMAGE);
					lpStgArea->lpCharMonster[cnt]->PlaySlowCount = 16 * 15;
					lpStgArea->lpCharMonster[cnt]->PlaySlowSpeed = 0;
				}
			}
		}
	}


	return TRUE;
}



int rsSoD_CatchItem_SD204(rsPLAYINFO *lpPlayInfo, int StagePos, STG_AREA	*lpStgArea)
{
	int cnt = 0;
	int x = 0, z = 0;
	int RndCnt = -1;
	smCHAR_INFO	*lpCharInfo = nullptr;
	smCHAR_MONSTER_INFO	*lpMonInfo = nullptr;

	smCHAR_INFO	*lpCharInfoBoss = nullptr;
	smCHAR_MONSTER_INFO	*lpMonInfoBoss = nullptr;

	int Param = 0;


	for(cnt = 0; cnt < chrMonsterCnt; cnt++)
	{

		if(chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_RABIE && chrMonsterList[cnt].szName[0] != ' ')
		{
			if(!lpCharInfo)
			{
				lpCharInfo = &chrMonsterList[cnt];
				lpMonInfo = &chrMonInfoList[cnt];
			}
		}

		if(chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_MUTANTRABIE && chrMonsterList[cnt].wPlayClass[0] == MONSTER_CLASS_BOSS)
		{
			if(!lpCharInfoBoss && chrMonsterList[cnt].wPlayClass[0] == MONSTER_CLASS_BOSS)
			{
				lpCharInfoBoss = &chrMonsterList[cnt];
				lpMonInfoBoss = &chrMonInfoList[cnt];
			}
		}

	}

	if(!lpCharInfo) return FALSE;


	for(cnt = 0; cnt < STG_MONSTER_MAX; cnt++)
	{
		if(lpStgArea->lpCharMonster[cnt])
		{
			if(lpStgArea->lpCharMonster[cnt]->Flag && lpStgArea->lpCharMonster[cnt]->PartyFlag == rsHARDCORE_EVENT_FLAG &&
				lpStgArea->lpCharMonster[cnt]->MotionInfo->State != CHRMOTION_STATE_DEAD &&
				lpStgArea->lpCharMonster[cnt]->smCharInfo.wPlayClass[0] != MONSTER_CLASS_BOSS)
			{

				x = lpStgArea->lpCharMonster[cnt]->pX >> FLOATNS;
				z = lpStgArea->lpCharMonster[cnt]->pZ >> FLOATNS;

				if(x > rsHardCoreEventOpenPos[StagePos][0].x && x<rsHardCoreEventOpenPos[StagePos][1].x &&
					z>rsHardCoreEventOpenPos[StagePos][1].z && z < rsHardCoreEventOpenPos[StagePos][0].z)
				{

					RndCnt = lpStgArea->lpCharMonster[cnt]->PartyParam;

					if((rand() % 2) == 0)
					{
						Param = lpStgArea->lpCharMonster[cnt]->PartyParam;
						rsCharChanger(lpStgArea->lpCharMonster[cnt], lpCharInfo, lpMonInfo);

						lpStgArea->lpCharMonster[cnt]->PartyFlag = rsHARDCORE_EVENT_FLAG;
						lpStgArea->lpCharMonster[cnt]->PartyParam = Param;

						lpStgArea->lpCharMonster[cnt]->DistAroundDbl = (12 * 64 * 12 * 64);
						lpStgArea->lpCharMonster[cnt]->smCharInfo.Sight = 800 * 800;
					}

				}
			}
		}
	}

	if(lpCharInfoBoss || RndCnt < 0)
	{

		STG_CHAR_INFO		 StgCharInfo;
		smCHAR				*lpChar;
		smTRANS_COMMAND_EX	TransCommandEx;

		StgCharInfo.PosiState = smCHAR_STATE_ENEMY;
		StgCharInfo.smCharInfo.Life[0] = 100;
		StgCharInfo.smCharInfo.Mana[0] = 100;
		StgCharInfo.smCharInfo.Life[1] = 100;
		StgCharInfo.smCharInfo.State = TRUE;

		memcpy(&StgCharInfo.smCharInfo, lpCharInfoBoss, sizeof(smCHAR_INFO));

		lpStgArea->EvnMonster = TRUE;
		lpChar = lpStgArea->OpenMonster(&StgCharInfo, 0);
		if(lpChar)
		{
			lpChar->pX = rsHardCoreEventOpenPos[RndCnt][2].x*fONE;
			lpChar->pY = rsHardCoreEventOpenPos[RndCnt][2].y*fONE;
			lpChar->pZ = rsHardCoreEventOpenPos[RndCnt][2].z*fONE;

			lpChar->SetMotionFromCode(CHRMOTION_STATE_STAND);
			lpChar->TargetMoveCount = 0;
			lpChar->PartyFlag = rsHARDCORE_EVENT_FLAG;
			lpChar->PartyParam = RndCnt;

			lpChar->PosiAround.x = rsHardCoreEventOpenPos[RndCnt][2].x*fONE;
			lpChar->PosiAround.y = rsHardCoreEventOpenPos[RndCnt][2].y*fONE;
			lpChar->PosiAround.z = rsHardCoreEventOpenPos[RndCnt][2].z*fONE;
			lpChar->DistAroundDbl = (12 * 64 * 12 * 64);

			lpChar->smCharInfo.Sight = 800 * 800;

			ZeroMemory(&TransCommandEx, sizeof(smTRANS_COMMAND_EX));
			TransCommandEx.WParam = smCOMMNAD_USER_WARP;
			TransCommandEx.LParam = lpChar->pX;
			TransCommandEx.SParam = lpChar->pY;
			TransCommandEx.EParam = lpChar->pZ;
			rsSendCommandUser(lpPlayInfo, &TransCommandEx);

		}

	}


	return TRUE;
}


int rsSoD_CatchItem_SD205(rsPLAYINFO *lpPlayInfo, int StagePos, STG_AREA	*lpStgArea, DWORD MonSndCode, int Level)
{
	int cnt;
	int x, y, z;
	smCHAR_INFO	*lpCharInfo = 0;
	smCHAR_MONSTER_INFO	*lpMonInfo;


	for(cnt = 0; cnt < chrMonsterCnt; cnt++)
	{

		if(chrMonsterList[cnt].dwCharSoundCode == MonSndCode && (Level == 0 || chrMonsterList[cnt].Level == Level))
		{
			if(!lpCharInfo)
			{
				lpCharInfo = &chrMonsterList[cnt];
				lpMonInfo = &chrMonInfoList[cnt];
				break;
			}
		}
	}

	if(!lpCharInfo || StagePos < 0) return FALSE;


	STG_CHAR_INFO		 StgCharInfo;
	smCHAR				*lpChar;
	smTRANS_COMMAND_EX	TransCommandEx;

	StgCharInfo.PosiState = smCHAR_STATE_ENEMY;
	StgCharInfo.smCharInfo.Life[0] = 100;
	StgCharInfo.smCharInfo.Mana[0] = 100;
	StgCharInfo.smCharInfo.Life[1] = 100;
	StgCharInfo.smCharInfo.State = TRUE;

	x = rsHardCoreEventOpenPos[StagePos][2].x*fONE;
	y = rsHardCoreEventOpenPos[StagePos][2].y*fONE;
	z = rsHardCoreEventOpenPos[StagePos][2].z*fONE;

	lpStgArea->EvnMonster = TRUE;
	memcpy(&StgCharInfo.smCharInfo, lpCharInfo, sizeof(smCHAR_INFO));

	lpChar = lpStgArea->OpenMonster(&StgCharInfo, 0);
	if(lpChar)
	{
		lpChar->lpMasterPlayInfo = lpPlayInfo;
		lpChar->smMonsterInfo.dwAutoCharCode = 0;
		lpChar->smCharInfo.Brood = smCHAR_MONSTER_USER;
		strcpy_s(lpChar->smCharInfo.szModelName2 + 1, sizeof(lpChar->smCharInfo.szModelName2) - 1, lpPlayInfo->smCharInfo.szName);
		lpChar->smCharInfo.Next_Exp = lpPlayInfo->dwObjectSerial;
		lpChar->dwUpdateCharInfoTime = dwPlayServTime + 4 * 60 * 1000;

		lpChar->pX = x;
		lpChar->pY = y;
		lpChar->pZ = z;

		ZeroMemory(&TransCommandEx, sizeof(smTRANS_COMMAND_EX));
		TransCommandEx.WParam = smCOMMNAD_USER_WARP;
		TransCommandEx.LParam = x;
		TransCommandEx.SParam = y;
		TransCommandEx.EParam = z;
		rsSendCommandUser(lpPlayInfo, &TransCommandEx);

	}

	return TRUE;
}




int rsSoD_CatchItem_SD207(rsPLAYINFO *lpPlayInfo, int StagePos, STG_AREA	*lpStgArea)
{


	int team = lpPlayInfo->sEventParam[0];

	if(team < 0 || team >= 4) return FALSE;


	if(lpPlayInfo->EventMode == rsHARDCORE_EVENT_FLAG && rsCheckHardCoreEventArea(lpPlayInfo->Position.x, lpPlayInfo->Position.y, lpPlayInfo->Position.z) == TRUE)
	{

		lpPlayInfo->EventScore += 5000;
		rsSodTeamScore[team] += 5000;


		rsTransUpdateSod(lpPlayInfo);
	}

	return TRUE;
}


int	rsSendCommandSodUserTeam(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND	*lpTransCommandEx)
{
	int cnt;
	int SndCnt = 0;

	for(cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial)
		{

			if(rsPlayInfo[cnt].EventMode == rsHARDCORE_EVENT_FLAG &&
				rsPlayInfo[cnt].sEventParam[0] == lpPlayInfo->sEventParam[0] &&
				rsCheckHardCoreEventArea(rsPlayInfo[cnt].Position.x, rsPlayInfo[cnt].Position.y, rsPlayInfo[cnt].Position.z) == TRUE)
			{

				rsPlayInfo[cnt].lpsmSock->Send((char *)lpTransCommandEx, lpTransCommandEx->size, TRUE);
				SndCnt++;
			}
		}
	}

	return TRUE;
}




int	rsSoD_CatchItem(DWORD dwItemCode, rsPLAYINFO *lpPlayInfo)
{

	int	StagePos;
	int cnt;
	STG_AREA	*lpStgArea;
	int x, z;
	smTRANS_COMMAND	smTransCommand;

	StagePos = -1;

	x = lpPlayInfo->Position.x >> FLOATNS;
	z = lpPlayInfo->Position.z >> FLOATNS;

	for(cnt = 0; cnt < 7; cnt++)
	{
		if(x > rsHardCoreEventOpenPos[cnt][0].x && x<rsHardCoreEventOpenPos[cnt][1].x &&
			z>rsHardCoreEventOpenPos[cnt][1].z && z < rsHardCoreEventOpenPos[cnt][0].z)
		{

			StagePos = cnt;
			break;
		}
	}


	lpStgArea = &StageArea[rsSOD_FIELD];
	if(!lpStgArea->lpStage) return FALSE;

	smTransCommand.code = OpCode::OPCODE_PROCESS_SKILL;;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = SKILL_PLAY_SOD_ITEM;
	smTransCommand.LParam = lpPlayInfo->dwObjectSerial;

	if(StagePos >= 0 && lpStgArea)
	{
		switch(dwItemCode)
		{
		case (sinSD2 | sin01):
			rsSoD_CatchItem_SD201(lpPlayInfo, StagePos, lpStgArea);

			smTransCommand.SParam = 1;
			smTransCommand.EParam = 0;
			rsSendCommandSodUserTeam(lpPlayInfo, &smTransCommand);
			break;

		case (sinSD2 | sin02):
			rsSoD_CatchItem_SD202(lpPlayInfo, StagePos, lpStgArea);

			smTransCommand.SParam = 2;
			smTransCommand.EParam = 0;
			rsSendCommandSodUserTeam(lpPlayInfo, &smTransCommand);
			break;

		case (sinSD2 | sin03):
			rsSoD_CatchItem_SD203(lpPlayInfo, StagePos, lpStgArea);

			smTransCommand.SParam = 3;
			smTransCommand.EParam = 0;
			rsSendCommandSodUserTeam(lpPlayInfo, &smTransCommand);
			break;

		case (sinSD2 | sin04):
			rsSoD_CatchItem_SD204(lpPlayInfo, StagePos, lpStgArea);

			smTransCommand.SParam = 4;
			smTransCommand.EParam = 0;
			rsSendCommandSodUserTeam(lpPlayInfo, &smTransCommand);
			break;

		case (sinSD2 | sin05):
			rsSoD_CatchItem_SD205(lpPlayInfo, StagePos, lpStgArea, snCHAR_SOUND_STYGIANLORD, 85);

			smTransCommand.SParam = 5;
			smTransCommand.EParam = 0;
			rsSendCommandSodUserTeam(lpPlayInfo, &smTransCommand);
			break;

		case (sinSD2 | sin06):
			rsSoD_CatchItem_SD205(lpPlayInfo, StagePos, lpStgArea, snCHAR_SOUND_GUARDIAN_SAINT, 0);

			smTransCommand.SParam = 6;
			smTransCommand.EParam = 0;
			rsSendCommandSodUserTeam(lpPlayInfo, &smTransCommand);
			break;

		case (sinSD2 | sin07):
			rsSoD_CatchItem_SD207(lpPlayInfo, StagePos, lpStgArea);

			smTransCommand.SParam = 7;
			smTransCommand.EParam = 0;

			lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

			break;

		}
	}

	return TRUE;
}







int SendOpenEvent(smCHAR *lpChar, rsPLAYINFO *lpPlayInfo, int EventFlag)
{
	TRANS_CHATMESSAGE	TransChatMessage;
	smWINSOCK *lpsmSock;
	int	NpcTeam;
	int	MsgNum = -1;
	int MsgCnt = lpChar->smMonsterInfo.NpcMsgCount;


	NpcTeam = lpChar->smMonsterInfo.EventNPC;
	if(NpcTeam <= 0 || NpcTeam > 4) return FALSE;

	lpPlayInfo->sEventParam[0] = NpcTeam - 1;

	lpsmSock = lpPlayInfo->lpsmSock;

	TransChatMessage.szMessage[0] = 0;
	TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
	TransChatMessage.dwIP = 0;
	TransChatMessage.dwObjectSerial = lpChar->dwObjectSerial;


	if(!rsServerConfig.Event_HardCore) return FALSE;

	if(!rsHardCoreEventMode)
	{

		if(MsgCnt)
		{
			strcpy_s(TransChatMessage.szMessage, lpChar->smMonsterInfo.lpNpcMessage[5 + rand() % 3]);
		}
		else
			strcpy_s(TransChatMessage.szMessage, srMsg_108);

		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
		return TRUE;
	}

	if(lpPlayInfo->smCharInfo.Level < 40)
	{


		if(MsgCnt)
		{
			strcpy_s(TransChatMessage.szMessage, lpChar->smMonsterInfo.lpNpcMessage[8]);
		}
		else
			strcpy_s(TransChatMessage.szMessage, srMsg_107);

		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);

		rsSod_GetRealTimeScore(lpPlayInfo, NpcTeam);
		if(lpPlayInfo->EventMode == 0)	lpPlayInfo->sEventParam[0] = NpcTeam - 1;

		return TRUE;
	}

	if((rsHardCoreEvent_TicketHour != dwServ_GameTimeHour && (rsHardCoreEvent_TicketHour + 1) != dwServ_GameTimeHour) ||
		rsEventTicketLevel[NpcTeam - 1] > rsEVENT_TICKET_LEVEL_TOTAL)
	{

		if(MsgCnt)
		{
			strcpy_s(TransChatMessage.szMessage, lpChar->smMonsterInfo.lpNpcMessage[2 + rand() % 3]);
		}
		else
		{
			if((dwServ_GameTimeHour & 1) == 0)
				strcpy_s(TransChatMessage.szMessage, srMsg_100);
			else
				strcpy_s(TransChatMessage.szMessage, srMsg_101);
		}


		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);

		rsSod_GetRealTimeScore(lpPlayInfo, NpcTeam);
		if(lpPlayInfo->EventMode == 0)	lpPlayInfo->sEventParam[0] = NpcTeam - 1;

		return TRUE;
	}

	if(MsgCnt)
	{
		strcpy_s(TransChatMessage.szMessage, lpChar->smMonsterInfo.lpNpcMessage[0]);
	}
	else
	{
		strcpy_s(TransChatMessage.szMessage, srMsg_102);
	}


	TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
	lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
	lpPlayInfo->EventMode = EventFlag;


	SendOpenCollectMoney(lpsmSock);

	return TRUE;
}


int rsEnterHardCoreEvent(rsPLAYINFO *lpPlayInfo, int Money)
{
	int cnt;

	TRANS_CHATMESSAGE	TransChatMessage;
	smTRANS_COMMAND		smTransCommand;

	if(lpPlayInfo->sEventParam[0] < 0 || lpPlayInfo->sEventParam[0] >= 4) return FALSE;

	if(lpPlayInfo->getSecurity() > AccountTypes::SEC_GAMEMASTER && Money == -1) goto skip_enterSOD;

	if(rsEventTicketLevel[lpPlayInfo->sEventParam[0]] > rsEVENT_TICKET_LEVEL_TOTAL ||
		(DWORD)rsHardCoreEvent_TicketHour > dwServ_GameTimeHour ||
		((DWORD)rsHardCoreEvent_TicketHour + 2) < dwServ_GameTimeHour)
	{






		if(dwSerToSerIP)
			rsSendMoneyToSystemLine(lpPlayInfo, Money);
		else
			rsSendMoneyToUser(lpPlayInfo, Money);


		strcpy_s(TransChatMessage.szMessage, srMsg_106);
		TransChatMessage.code = OpCode::OPCODE_MESSAGEBOX;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		TransChatMessage.dwIP = 0;
		TransChatMessage.dwObjectSerial = 0;
		lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);

		return FALSE;
	}

skip_enterSOD:


	for(cnt = 0; cnt < STAGE_AREA_MAX; cnt++)
	{
		if(StageArea[cnt].lpStage && StageArea[cnt].lpField->FieldCode == rsSOD_FIELD)
		{
			smTransCommand.WParam = StageArea[cnt].lpField->FieldCode;
			smTransCommand.code = OpCode::OPCODE_WARPFIELD;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.SParam = rsHardCoreEventOpenPos[lpPlayInfo->sEventParam[0]][2].x*fONE;
			smTransCommand.LParam = rsHardCoreEventOpenPos[lpPlayInfo->sEventParam[0]][2].z*fONE;
			lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
			rsEventTicketCount++;
			rsEventTicketLevel[lpPlayInfo->sEventParam[0]] += lpPlayInfo->smCharInfo.Level;
			lpPlayInfo->EventMode = rsHARDCORE_EVENT_FLAG;
			lpPlayInfo->EventScore = 0;
			lpPlayInfo->EventCount = 0;
			lpPlayInfo->dwEventTime = dwPlayServTime;

			lpPlayInfo->sEventParam[1] = 0;

			lpPlayInfo->Position.x = smTransCommand.SParam;
			lpPlayInfo->Position.z = smTransCommand.LParam;

			rsHardCoreEvent_TotalUser++;


			if(rsSodUserCount < rsSOD_USER_MAX)
			{
				rsSodUser[rsSodUserCount].lpPlayInfo = lpPlayInfo;
				rsSodUser[rsSodUserCount].dwConnCode = lpPlayInfo->dwConnectCount;
				rsSodUserCount++;
			}

		}
	}

	return TRUE;
}


#else


int	rsInitHardCoreEvent()
{
	return TRUE;
}
int rsHardCoreEvent_OpenMonster(STG_AREA *lpStgArea, STG_CHAR_INFO *lpStgCharInfo)
{
	return TRUE;
}

int rsShowHardCoreEventScore(rsPLAYINFO *lpPlayInfo)
{
	return TRUE;
}

#endif


int rsCheckHardCoreEventArea(int x, int y, int z)
{
	int mx, my, mz;

	mx = x >> FLOATNS;
	my = y >> FLOATNS;
	mz = z >> FLOATNS;

	if(y >= rsHardCoreEventOpenPos[0][0].y - 32)
	{

		if(rsHardCoreEventArea[0]<mx && rsHardCoreEventArea[1]>mx &&
			rsHardCoreEventArea[2]<mz && rsHardCoreEventArea[3]>mz)
		{


			return TRUE;
		}
	}

	return FALSE;
}


int rsGetSoD_AreaCode(int x, int y, int z)
{
	int mx, my, mz;
	int cnt;


	mx = x >> FLOATNS;
	my = y >> FLOATNS;
	mz = z >> FLOATNS;

	if(y >= rsHardCoreEventOpenPos[0][0].y - 32)
	{

		if(rsHardCoreEventArea[0]<mx && rsHardCoreEventArea[1]>mx &&
			rsHardCoreEventArea[2]<mz && rsHardCoreEventArea[3]>mz)
		{

			for(cnt = 0; cnt < 7; cnt++)
			{

				if(mx > rsHardCoreEventOpenPos[cnt][0].x && mx<rsHardCoreEventOpenPos[cnt][1].x &&
					mz>rsHardCoreEventOpenPos[cnt][1].z && mz < rsHardCoreEventOpenPos[cnt][0].z)
				{

					return cnt;
				}
			}

		}
	}

	return -1;
}




WORD	wLastCheckDay = 0;
WORD	wLastCheckHour = 0;
WORD	wLastCheckMin = 0;
static	int EventBossMonsterFlag = 0;
DWORD	dwEventBossMonterTime = 0;
int		OpenBossTimeMin = 1;



int EventMonsterTime()
{
	SYSTEMTIME	st;

	int cnt, cnt2, cnt3;

	GetLocalTime(&st);

	EventMonster = FALSE;

	if(wLastCheckHour != st.wHour && st.wHour == rsBLESSCASTLE_TAX_TIME)
	{
		rsBlessCastle.Tax = rsBlessCastle.NextTax;
		rsBlessCastle.SelectedSkill = rsBlessCastle.BlessCastleSetup.ClanSkill;
	}


	if(rsServerConfig.sBlessCastle_StartTime[0] && rsServerConfig.sBlessCastle_StartTime[1])
	{
		if(rsServerConfig.BlessCastleMode)
		{
			if(!rsBlessCastle.CastleMode && wLastCheckHour != st.wHour &&
				st.wDayOfWeek == rsServerConfig.sBlessCastle_StartTime[0] &&
				st.wHour == rsServerConfig.sBlessCastle_StartTime[1])
			{
				rsStart_CombatCastle();
			}
		}

		if(wLastCheckMin == 29 && st.wMinute == 30 &&
			st.wDayOfWeek == rsServerConfig.sBlessCastle_StartTime[0] &&
			st.wHour == rsServerConfig.sBlessCastle_StartTime[1] - 1)
		{

			rsSetNoticeMessage(srBlessCastle_LeagueMsg_04);
		}
		if(wLastCheckHour == rsServerConfig.sBlessCastle_StartTime[1] - 2 &&
			st.wDayOfWeek == rsServerConfig.sBlessCastle_StartTime[0] &&
			st.wHour == rsServerConfig.sBlessCastle_StartTime[1] - 1)
		{

			rsSetNoticeMessage(srBlessCastle_LeagueMsg_05);
		}
	}




	if(rsServerConfig.Event_HardCore == 2)
	{
		rsHardCoreEventMode = TRUE;
	}
	else
	{
		rsHardCoreEventMode = FALSE;
#ifndef		_LANGUAGE_ENGLISH
#ifdef	_LANGUAGE_JAPANESE		
		if(st.wDayOfWeek == 0 || st.wDayOfWeek == 6)
		{
			rsHardCoreEventMode = TRUE;
		}
		else
		{
			if(st.wHour >= 14 || st.wHour < 2)
			{

				rsHardCoreEventMode = TRUE;
			}
		}
#else
#ifdef _LANGUAGE_CHINESE
		if(st.wDayOfWeek >= 0 && st.wDayOfWeek <= 6)
		{
			if(st.wHour >= 20 && st.wHour < 22)
			{
				rsHardCoreEventMode = TRUE;
			}
			else
			{
				rsHardCoreEventMode = FALSE;
			}
		}
		else
		{
			rsHardCoreEventMode = FALSE;
		}

#else
#ifdef _LANGUAGE_VEITNAM
		if(st.wDayOfWeek == 0 || st.wDayOfWeek == 6)
		{
			if(st.wHour >= 7 || st.wHour < 3)
				rsHardCoreEventMode = TRUE;

		}
		else
		{

			if(st.wHour >= 8 || st.wHour < 2)
				rsHardCoreEventMode = TRUE;
		}
#else
#ifdef _LANGUAGE_BRAZIL
		if(st.wDayOfWeek == 0 || st.wDayOfWeek == 6)
		{
			rsHardCoreEventMode = TRUE;
		}
		else
		{
			if(st.wHour >= 14 || st.wHour < 4)
				rsHardCoreEventMode = TRUE;
		}
#else

		if(st.wHour >= 0 && st.wHour < 6)
		{

			rsHardCoreEventMode = TRUE;
		}
		else if(st.wHour >= 12 && st.wHour < 18)
		{

			rsHardCoreEventMode = TRUE;
		}
#endif
#endif
#endif
#endif
#else
#ifdef _LANGUAGE_PHILIPIN
		if(st.wHour >= 20 || st.wHour < 2)	rsHardCoreEventMode = TRUE;
		else if(st.wHour >= 13 && st.wHour < 19)		rsHardCoreEventMode = TRUE;
#else

		if(st.wHour >= 0 && st.wHour < 6)
		{

			rsHardCoreEventMode = TRUE;
		}
		else if(st.wHour >= 12 && st.wHour < 18)
		{

			rsHardCoreEventMode = TRUE;
		}
#endif
#endif
	}


#ifdef _LANGUAGE_JAPANESE 

	if(rsServerConfig.Event_DamageOff)
	{

		rsDamgeOffEvent = TRUE;





		if(rsServerConfig.Event_DamageOff == 2) rsDamgeOffEvent = TRUE;
	}
	else
		rsDamgeOffEvent = FALSE;

#else
#ifdef _LANGUAGE_PHILIPIN





	if(rsServerConfig.Event_DamageOff1) rsDamgeOffEvent1 = TRUE;
	else  rsDamgeOffEvent1 = FALSE;

	if(rsServerConfig.Event_DamageOff2) rsDamgeOffEvent2 = TRUE;
	else  rsDamgeOffEvent2 = FALSE;
#else

	if(rsServerConfig.Event_DamageOff)
	{


		rsDamgeOffEvent = TRUE;






		if(rsServerConfig.Event_DamageOff == 2) rsDamgeOffEvent = TRUE;
	}
	else
		rsDamgeOffEvent = FALSE;
#endif
#endif


	if(rsServerConfig.Event_DamageOff1 == 2) rsDamgeOffEvent1 = TRUE;
	if(rsServerConfig.Event_DamageOff2 == 2) rsDamgeOffEvent2 = TRUE;




	if(rsServerConfig.Event_DefenseOff)
	{
		if((st.wHour >= 0 && st.wHour < 6) || st.wHour >= 12 && st.wHour < 18)
		{
			rsDefenseOffEvent = TRUE;
		}
		else
		{
			rsDefenseOffEvent = FALSE;
		}

		if(rsServerConfig.Event_DefenseOff == 2) rsDefenseOffEvent = TRUE;
	}
	else
		rsDefenseOffEvent = FALSE;





	if(rsServerConfig.Event_Cristal)
	{
		if(st.wDayOfWeek != 0 || st.wDayOfWeek != 6)
		{
			if((st.wHour >= 12 && st.wHour <= 23) || rsServerConfig.Event_Cristal == 2)
			{
				rsCristalEvent = TRUE;
			}
			else
			{
				rsCristalEvent = FALSE;
			}
		}
		else if(st.wDayOfWeek == 0 || st.wDayOfWeek == 6)
		{
			rsCristalEvent = TRUE;
		}
		else
		{
			rsCristalEvent = FALSE;
		}
	}
	else
		rsCristalEvent = FALSE;

	if(wLastCheckDay != st.wDay)
	{


		for(cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
		{
			if(DefaultItems[cnt2].sGenDay[0])
			{
				DefaultItems[cnt2].sGenDay[1] = 0;
			}
		}
		wLastCheckDay = st.wDay;
		OpenBossTimeMin = (rand() % 45) + 1;


		if(rsServerConfig.ExpGameTimeMode)
		{
			for(cnt = 0; cnt < CONNECTMAX; cnt++)
			{
				if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwExpGameTime)
					rsPlayInfo[cnt].dwExpGameTime = 0;
			}
		}

	}



	if(!EventBossMonsterFlag && st.wMinute == OpenBossTimeMin && (dwEventBossMonterTime + 60 * 1000 * 10) < dwPlayServTime)
	{
		for(cnt = 0; cnt < STAGE_AREA_MAX; cnt++)
		{
			if(StageArea[cnt].lpStage)
			{
				if(StageArea[cnt].rsMonsterList.BossMonsterCount > 0)
				{
					for(cnt2 = 0; cnt2 < StageArea[cnt].rsMonsterList.BossMonsterCount; cnt2++)
					{
						for(cnt3 = 0; cnt3 < StageArea[cnt].rsMonsterList.sBossMonsters[cnt2].OpenTimeCount; cnt3++)
						{
							if(st.wHour == StageArea[cnt].rsMonsterList.sBossMonsters[cnt2].bOpenTime[cnt3])
							{


								rsOpenBossMonster(&StageArea[cnt], &StageArea[cnt].rsMonsterList.sBossMonsters[cnt2]);
								break;
							}
						}
					}
				}
			}
		}
		EventBossMonsterFlag = TRUE;
		dwEventBossMonterTime = dwPlayServTime;
	}
	else
	{
		if(EventBossMonsterFlag && st.wMinute != OpenBossTimeMin)
		{
			EventBossMonsterFlag = 0;
		}
	}

	wLastCheckHour = st.wHour;
	wLastCheckMin = st.wMinute;

	return TRUE;
}






STG_AREA::STG_AREA()
{
	ZeroMemory(&Head, sizeof(STG_AREA));
}


int STG_AREA::Close()
{
	if(lpStageCharInfo)
	{
		delete lpStageCharInfo; lpStageCharInfo = 0;
	}
	if(lpStage)
	{
		delete lpStage; lpStage = 0;
	}

	return TRUE;
}



smTRNAS_PLAYERINFO *STG_AREA::FindCharInfoFixed(smTRNAS_PLAYERINFO *lpTransPlayerInfo)
{
	int cnt;

	if(lpTransPlayerInfo)
	{
		for(cnt = 0; cnt < FIX_CHAR_MAX; cnt++)
		{
			if(TransCharFixed[cnt].code &&
				TransCharFixed[cnt].dwObjectSerial == lpTransPlayerInfo->dwObjectSerial)
				return &TransCharFixed[cnt];
		}
	}
	else
	{
		for(cnt = 0; cnt < FIX_CHAR_MAX; cnt++)
		{
			if(TransCharFixed[cnt].code == 0) return &TransCharFixed[cnt];
		}
	}

	return NULL;
}



int STG_AREA::AddCharInfoFixed(smTRNAS_PLAYERINFO *lpTransPlayerInfo)
{
	smTRNAS_PLAYERINFO	*lpFindPlayerInfo;

	lpFindPlayerInfo = FindCharInfoFixed(lpTransPlayerInfo);
	if(lpFindPlayerInfo) return FALSE;

	lpFindPlayerInfo = FindCharInfoFixed(0);
	if(lpFindPlayerInfo)
	{
		rsOpenNPC_RandomPos = -1;
		memcpy(lpFindPlayerInfo, lpTransPlayerInfo, sizeof(smTRNAS_PLAYERINFO));
		OpenNpc(lpFindPlayerInfo);
		SaveCharInfoFixed(szCharFixedFile);
		return TRUE;
	}

	return FALSE;
}


int STG_AREA::DeleteCharInfoFixed(smTRNAS_PLAYERINFO *lpTransPlayerInfo)
{
	smTRNAS_PLAYERINFO	*lpFindPlayerInfo;
	smCHAR	*lpChar;

	lpFindPlayerInfo = FindCharInfoFixed(lpTransPlayerInfo);
	if(lpFindPlayerInfo)
	{
		lpFindPlayerInfo->code = 0;

		lpChar = srFindCharFromSerial(lpTransPlayerInfo->dwObjectSerial);
		if(lpChar)
		{
			lpChar->Close();
		}
		SaveCharInfoFixed(szCharFixedFile);
		return TRUE;
	}

	return FALSE;
}



int STG_AREA::LoadCharInfoFixed(char *szFile)
{
	FILE *fp;

	fp = fopen(szFile, "rb");
	if(fp)
	{
		fread(TransCharFixed, sizeof(smTRNAS_PLAYERINFO)*FIX_CHAR_MAX, 1, fp);
		fclose(fp);
		return TRUE;
	}
	return FALSE;
}


int STG_AREA::SaveCharInfoFixed(char *szFile)
{
	FILE *fp;

	fp = fopen(szFile, "wb");
	if(fp)
	{
		fwrite(TransCharFixed, sizeof(smTRNAS_PLAYERINFO)*FIX_CHAR_MAX, 1, fp);
		fclose(fp);
	}

	return TRUE;
}




int STG_AREA::OpenNpc(smTRNAS_PLAYERINFO *lpTransPlayerInfo)
{

	smCHAR *lpChar;
	char *lpFileName;
	int dist, cnt;


	for(cnt = 0; cnt < AUTOPLAYER_MAX; cnt++)
	{
		if(chrAutoPlayer[cnt].Flag &&
			chrAutoPlayer[cnt].smCharInfo.State == smCHAR_STATE_NPC &&
			chrAutoPlayer[cnt].pX == lpTransPlayerInfo->x &&
			chrAutoPlayer[cnt].pY == lpTransPlayerInfo->y &&
			chrAutoPlayer[cnt].pZ == lpTransPlayerInfo->z)
		{



			return FALSE;
		}
	}



	lpChar = srFindEmptyChar();
	if(lpChar)
	{
		lpChar->Init();

		lpTransPlayerInfo->dwObjectSerial = GetNewObjectSerial();
		lpChar->pX = lpTransPlayerInfo->x;
		lpChar->pY = lpTransPlayerInfo->y;
		lpChar->pZ = lpTransPlayerInfo->z;
		lpChar->Angle.x = lpTransPlayerInfo->ax;
		lpChar->Angle.y = lpTransPlayerInfo->ay;
		lpChar->Angle.z = lpTransPlayerInfo->az;

		lpChar->PosiAround.x = lpTransPlayerInfo->x;
		lpChar->PosiAround.y = lpTransPlayerInfo->y;
		lpChar->PosiAround.z = lpTransPlayerInfo->z;
		lpChar->DistAroundDbl = DIST_AROUND_NEAR;


		lpChar->lpExt1 = (void *)&Head;
		lpChar->dwObjectSerial = lpTransPlayerInfo->dwObjectSerial;
		lpChar->ActionPattern = 12;
		memcpy(&lpChar->smCharInfo, &lpTransPlayerInfo->smCharInfo, sizeof(smCHAR_INFO));


		lpFileName = lpChar->smCharInfo.szModelName2;
		if(lpFileName[0])
		{

			lpChar->szChatMessage[0] = 0;
			ZeroMemory(&lpChar->smMonsterInfo, sizeof(smCHAR_MONSTER_INFO));
			smCharDecode(lpFileName, &lpChar->smCharInfo, &lpChar->smMonsterInfo, lpChar->szChatMessage, sizeof(lpChar->szChatMessage));

			if(rsOpenNPC_RandomPos != -1 && lpChar->smMonsterInfo.OpenCount[1])
			{
				if((rsOpenNPC_RandomPos%lpChar->smMonsterInfo.OpenCount[1]) != lpChar->smMonsterInfo.OpenCount[0])
				{
					lpChar->Flag = 0;
					return FALSE;
				}
			}


			if(lpChar->smMonsterInfo.szName[0])
			{
				strcpy_s(lpChar->smCharInfo.szName, lpChar->smMonsterInfo.szName);
				lpChar->smMonsterInfo.szName[0] = 0;
			}
			srLinkNpcItem(lpChar);

			dist = lpChar->smMonsterInfo.MoveRange >> FLOATNS;
			lpChar->DistAroundDbl = dist*dist;
		}

		lpChar->SetLoadPattern(lpChar->smCharInfo.szModelName);
		lpChar->lpStage = lpStage;

		if(lpChar->FindMotionCountFromCode(CHRMOTION_STATE_WALK) == 0)
		{

			lpChar->MoveSpeed = 0;
		}

		return TRUE;
	}

	return FALSE;
}


STG_ITEMS *STG_AREA::FindItem(int x, int y, int z)
{
	int cnt;

	for(cnt = 0; cnt < STG_ITEM_MAX; cnt++)
	{
		if(StgItems[cnt].state &&
			StgItems[cnt].x == x && StgItems[cnt].y == y && StgItems[cnt].z == z)
		{

			return	&StgItems[cnt];

		}
	}

	return NULL;
}


STG_ITEMS *STG_AREA::AddItem(psITEM *lpItem, int x, int y, int z, int BeginMode)
{
	int cnt, cnt2;
	STG_ITEMS *lpStgItem;
	int height;
	int dx, dz, dy;
	int ta;
	DWORD dwItem;


	for(cnt = 0; cnt < 8; cnt++)
	{
		ItemSettingCount++;
		dx = x + ptItemSettingPosi[ItemSettingCount & 7].x;
		dz = z + ptItemSettingPosi[ItemSettingCount & 7].y;
		dy = y << FLOATNS;


		height = lpStage->GetFloorHeight(dx << FLOATNS, dy, dz << FLOATNS, 32 * fONE);
		if(height != CLIP_OUT)
		{

			ta = abs(height - dy);
			if(ta < 32 * fONE)
			{
				lpStgItem = FindItem(x, y, z);
				if(!lpStgItem) break;
			}
		}
	}

	if(cnt < 8)
	{
		x = dx;
		z = dz;
		y = height >> FLOATNS;
	}

	for(cnt2 = 0; cnt2 < 2; cnt2++)
	{
		for(cnt = 0; cnt < STG_ITEM_MAX; cnt++)
		{
			if(!StgItems[cnt].state || (cnt2 && StgItems[cnt].Level == 0))
			{
				StgItems[cnt].x = x;
				StgItems[cnt].y = y;
				StgItems[cnt].z = z;
				StgItems[cnt].state = TRUE;
				memcpy(&StgItems[cnt].Item, lpItem, sizeof(psITEM));

				StgItems[cnt].dwCreateTime = GetCurrentTime();
				StgItems[cnt].BeginMode = BeginMode;

				dwItem = StgItems[cnt].Item.ItemInfo.CODE & sinITEM_MASK2;

				if(dwItem == sinGG1 || dwItem == sinPL1 || dwItem == sinPS1)
				{

					StgItems[cnt].dwLoseTime = StgItems[cnt].dwCreateTime + STG_ITEM_WAIT_TIME_LOW;
				}
				else
				{
					StgItems[cnt].dwLoseTime = StgItems[cnt].dwCreateTime + STG_ITEM_WAIT_TIME;
				}


				if(dwItem != sinPM1 && dwItem != sinPL1 && dwItem != sinPS1 && dwItem != sinGG1) StgItems[cnt].Level = 1;
				else dwItem = 0;

				return	&StgItems[cnt];
			}
		}
		rsItemBuffOverCount++;
	}

	return FALSE;
}


int STG_AREA::DeleteItem(STG_ITEMS *lpStgItem)
{
	int cnt;
	int rx, rz, dist;
	smTRANS_ACITON_ITEM	TransActionItem;

	if(lpStgItem)
	{
		lpStgItem->state = NULL;

		TransActionItem.size = sizeof(smTRANS_ACITON_ITEM);
		TransActionItem.code = OpCode::OPCODE_DELITEM;
		TransActionItem.x = lpStgItem->x << FLOATNS;
		TransActionItem.y = lpStgItem->y << FLOATNS;
		TransActionItem.z = lpStgItem->z << FLOATNS;
		TransActionItem.lpStgArea = (void *)this;

		for(cnt = 0; cnt < CONNECTMAX; cnt++)
		{
			if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial)
			{

				rx = lpStgItem->x - (rsPlayInfo[cnt].Position.x >> FLOATNS);
				rz = lpStgItem->z - (rsPlayInfo[cnt].Position.z >> FLOATNS);
				dist = rx*rx + rz*rz;
				if(dist < DIST_TRANSLEVEL_MHIGH && abs(rx) < TRANS_VIEW_LIMIT && abs(rz) < TRANS_VIEW_LIMIT)
				{
					rsPlayInfo[cnt].lpsmSock->Send((char *)&TransActionItem, TransActionItem.size, TRUE);
				}
			}
		}
	}

	return TRUE;
}


int STG_AREA::DeleteItem(int x, int y, int z)
{
	STG_ITEMS *lpStgItem;

	lpStgItem = FindItem(x, y, z);

	if(lpStgItem)
	{
		return DeleteItem(lpStgItem);
	}

	return FALSE;
}




int STG_AREA::SendStgItem(rsPLAYINFO *lpPlayInfo)
{
	smTRANS_ITEMS	TransItems;
	int cnt, scnt;
	int dx, dz, dist;
	DWORD	dwCode;

	cnt = 0;
	scnt = 0;

	while(1)
	{
		if(scnt >= TRANS_ITEM_MAX) break;
		if(cnt >= STG_ITEM_MAX) break;

		if(StgItems[cnt].state && StgItems[cnt].Level && StgItems[cnt].dwCreateTime<dwPlayServTime &&
			(StgItems[cnt].dwLoseTime - 10000)>dwPlayServTime)
		{

			dx = StgItems[cnt].x - (lpPlayInfo->Position.x >> FLOATNS);
			dz = StgItems[cnt].z - (lpPlayInfo->Position.z >> FLOATNS);

			dist = dx*dx + dz*dz;

			if(dist < DIST_TRANSLEVEL_MHIGH && abs(dx) < TRANS_VIEW_LIMIT && abs(dz) < TRANS_VIEW_LIMIT)
			{
				dwCode = StgItems[cnt].Item.ItemInfo.CODE;

				TransItems.Items[scnt].state = StgItems[cnt].state;
				TransItems.Items[scnt].x = StgItems[cnt].x << FLOATNS;
				TransItems.Items[scnt].y = StgItems[cnt].y << FLOATNS;
				TransItems.Items[scnt].z = StgItems[cnt].z << FLOATNS;
				TransItems.Items[scnt].ItemCode = dwCode;
				TransItems.Items[scnt].lpStgArea = (void *)this;

				dwCode = dwCode&sinITEM_MASK2;

				if(StgItems[cnt].Item.ItemInfo.PotionCount > 1 && (dwCode&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
				{
					wsprintf(TransItems.Items[scnt].szName, "%sx%d", StgItems[cnt].Item.ItemInfo.ItemName, StgItems[cnt].Item.ItemInfo.PotionCount);
				}
				else
					strcpy_s(TransItems.Items[scnt].szName, StgItems[cnt].Item.ItemInfo.ItemName);


				if(dwCode == sinPZ1 || dwCode == sinPZ2)
				{
					if(StgItems[cnt].Item.ItemInfo.PotionCount < 2)
					{
						TransItems.Items[scnt].ItemCode = sinPZ1 | sin00;
						strcpy_s(TransItems.Items[scnt].szName, srItem_BB);
					}
				}

				scnt++;
			}
		}
		cnt++;
	}

	cnt = 0;

	while(1)
	{
		if(scnt >= TRANS_ITEM_MAX) break;
		if(cnt >= STG_ITEM_MAX) break;

		if(StgItems[cnt].state && !StgItems[cnt].Level && StgItems[cnt].dwCreateTime<dwPlayServTime &&
			(StgItems[cnt].dwLoseTime - 10000)>dwPlayServTime)
		{

			dx = StgItems[cnt].x - (lpPlayInfo->Position.x >> FLOATNS);
			dz = StgItems[cnt].z - (lpPlayInfo->Position.z >> FLOATNS);

			dist = dx*dx + dz*dz;

			if(dist < DIST_TRANSLEVEL_MHIGH && abs(dx) < TRANS_VIEW_LIMIT && abs(dz) < TRANS_VIEW_LIMIT)
			{
				dwCode = StgItems[cnt].Item.ItemInfo.CODE;

				TransItems.Items[scnt].state = StgItems[cnt].state;
				TransItems.Items[scnt].x = StgItems[cnt].x << FLOATNS;
				TransItems.Items[scnt].y = StgItems[cnt].y << FLOATNS;
				TransItems.Items[scnt].z = StgItems[cnt].z << FLOATNS;
				TransItems.Items[scnt].ItemCode = dwCode;
				TransItems.Items[scnt].lpStgArea = (void *)this;

				dwCode = dwCode&sinITEM_MASK2;

				if(StgItems[cnt].Item.ItemInfo.PotionCount > 1 && (dwCode&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
				{
					wsprintf(TransItems.Items[scnt].szName, "%sx%d", StgItems[cnt].Item.ItemInfo.ItemName, StgItems[cnt].Item.ItemInfo.PotionCount);
				}
				else
					strcpy_s(TransItems.Items[scnt].szName, StgItems[cnt].Item.ItemInfo.ItemName);


				if(dwCode == sinPZ1 || dwCode == sinPZ2)
				{
					if(StgItems[cnt].Item.ItemInfo.PotionCount < 2)
					{
						TransItems.Items[scnt].ItemCode = sinPZ1 | sin00;
						strcpy_s(TransItems.Items[scnt].szName, srItem_BB);
					}
				}

				scnt++;
			}
		}
		cnt++;
	}


	TransItems.code = OpCode::OPCODE_PLAYITEM;
	TransItems.size = sizeof(TRANS_ITEM)*scnt + 16;
	TransItems.state = 1;
	TransItems.Count = scnt;

	if(scnt > 0 && lpPlayInfo && lpPlayInfo->lpsmSock)
		return lpPlayInfo->lpsmSock->Send((char *)&TransItems, TransItems.size, TRUE);

	return FALSE;
}


int STG_AREA::SendStgItem(rsPLAYINFO *lpPlayInfo, STG_ITEMS *lpStgItem)
{
	smTRANS_ITEMS	TransItems;
	DWORD	dwCode;

	if(!lpStgItem->state) return FALSE;


	dwCode = lpStgItem->Item.ItemInfo.CODE;

	TransItems.Items[0].state = lpStgItem->state;
	TransItems.Items[0].x = lpStgItem->x << FLOATNS;
	TransItems.Items[0].y = lpStgItem->y << FLOATNS;
	TransItems.Items[0].z = lpStgItem->z << FLOATNS;
	TransItems.Items[0].ItemCode = dwCode;
	TransItems.Items[0].lpStgArea = (void *)this;

	dwCode = dwCode&sinITEM_MASK2;

	if(lpStgItem->Item.ItemInfo.PotionCount > 1 && (dwCode&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
	{
		wsprintf(TransItems.Items[0].szName, "%sx%d", lpStgItem->Item.ItemInfo.ItemName, lpStgItem->Item.ItemInfo.PotionCount);
	}
	else
		strcpy_s(TransItems.Items[0].szName, lpStgItem->Item.ItemInfo.ItemName);



	if(dwCode == sinPZ1 || dwCode == sinPZ2)
	{
		if(lpStgItem->Item.ItemInfo.PotionCount < 2)
		{
			TransItems.Items[0].ItemCode = sinPZ1 | sin00;
			strcpy_s(TransItems.Items[0].szName, srItem_BB);
		}
	}


	TransItems.code = OpCode::OPCODE_PLAYITEM;
	TransItems.size = sizeof(TRANS_ITEM) + 16;
	TransItems.state = 1;
	TransItems.Count = 1;

	if(lpPlayInfo && lpPlayInfo->lpsmSock)
		return lpPlayInfo->lpsmSock->Send((char *)&TransItems, TransItems.size, TRUE);

	return FALSE;
}


int STG_AREA::SendStgItemToNearUsers(STG_ITEMS *lpStgItem)
{
	int cnt;
	int rx, rz, dist;
	smTRANS_ITEMS	TransItems;
	DWORD	dwCode;

	if(lpStgItem)
	{
		dwCode = lpStgItem->Item.ItemInfo.CODE;

		TransItems.Items[0].state = lpStgItem->state;
		TransItems.Items[0].x = lpStgItem->x << FLOATNS;
		TransItems.Items[0].y = lpStgItem->y << FLOATNS;
		TransItems.Items[0].z = lpStgItem->z << FLOATNS;
		TransItems.Items[0].ItemCode = dwCode;
		TransItems.Items[0].lpStgArea = (void *)this;

		dwCode = dwCode&sinITEM_MASK2;

		if(lpStgItem->Item.ItemInfo.PotionCount > 1 && (dwCode&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
		{
			wsprintf(TransItems.Items[0].szName, "%sx%d", lpStgItem->Item.ItemInfo.ItemName, lpStgItem->Item.ItemInfo.PotionCount);
		}
		else
			strcpy_s(TransItems.Items[0].szName, lpStgItem->Item.ItemInfo.ItemName);


		if(dwCode == sinPZ1 || dwCode == sinPZ2)
		{
			if(lpStgItem->Item.ItemInfo.PotionCount < 2)
			{
				TransItems.Items[0].ItemCode = sinPZ1 | sin00;
				strcpy_s(TransItems.Items[0].szName, srItem_BB);
			}
		}

		TransItems.code = OpCode::OPCODE_PLAYITEM;
		TransItems.size = sizeof(TRANS_ITEM) + 16;
		TransItems.state = 1;
		TransItems.Count = 1;

		for(cnt = 0; cnt < CONNECTMAX; cnt++)
		{
			if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial)
			{
				rx = lpStgItem->x - (rsPlayInfo[cnt].Position.x >> FLOATNS);
				rz = lpStgItem->z - (rsPlayInfo[cnt].Position.z >> FLOATNS);
				dist = rx*rx + rz*rz;

				if(dist < DIST_TRANSLEVEL_HIGH && abs(rx) < TRANS_VIEW_LIMIT && abs(rz) < TRANS_VIEW_LIMIT)
				{
					rsPlayInfo[cnt].lpsmSock->Send((char *)&TransItems, TransItems.size, TRUE);
				}
			}
		}
	}

	return TRUE;
}



int STG_AREA::SendStgItemToPartyUsers(rsPLAYINFO *lpPlayInfo, STG_ITEMS *lpStgItem)
{
	int cnt;
	int rx, rz, dist;
	smTRANS_ITEMS	TransItems;
	DWORD	dwCode;

	if(lpStgItem && lpPlayInfo && lpPlayInfo->lpPartyMaster)
	{
		dwCode = lpStgItem->Item.ItemInfo.CODE;

		TransItems.Items[0].state = lpStgItem->state;
		TransItems.Items[0].x = lpStgItem->x << FLOATNS;
		TransItems.Items[0].y = lpStgItem->y << FLOATNS;
		TransItems.Items[0].z = lpStgItem->z << FLOATNS;
		TransItems.Items[0].ItemCode = dwCode;
		TransItems.Items[0].lpStgArea = (void *)this;

		dwCode = dwCode&sinITEM_MASK2;

		if(lpStgItem->Item.ItemInfo.PotionCount > 1 && (dwCode&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
		{
			wsprintf(TransItems.Items[0].szName, "%sx%d", lpStgItem->Item.ItemInfo.ItemName, lpStgItem->Item.ItemInfo.PotionCount);
		}
		else
			strcpy_s(TransItems.Items[0].szName, lpStgItem->Item.ItemInfo.ItemName);


		if(dwCode == sinPZ1 || dwCode == sinPZ2)
		{
			if(lpStgItem->Item.ItemInfo.PotionCount < 2)
			{
				TransItems.Items[0].ItemCode = sinPZ1 | sin00;
				strcpy_s(TransItems.Items[0].szName, srItem_BB);
			}
		}

		TransItems.code = OpCode::OPCODE_PLAYITEM;
		TransItems.size = sizeof(TRANS_ITEM) + 16;
		TransItems.state = 1;
		TransItems.Count = 1;

		for(cnt = 0; cnt < CONNECTMAX; cnt++)
		{
			if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial &&
				rsPlayInfo[cnt].dwPartyInfo && lpPlayInfo->lpPartyMaster == rsPlayInfo[cnt].lpPartyMaster)
			{

				rx = lpStgItem->x - (rsPlayInfo[cnt].Position.x >> FLOATNS);
				rz = lpStgItem->z - (rsPlayInfo[cnt].Position.z >> FLOATNS);
				dist = rx*rx + rz*rz;

				if(dist < DIST_TRANSLEVEL_HIGH && abs(rx) < TRANS_VIEW_LIMIT && abs(rz) < TRANS_VIEW_LIMIT)
				{
					rsPlayInfo[cnt].lpsmSock->Send((char *)&TransItems, TransItems.size, TRUE);
				}
			}
		}
	}

	return TRUE;
}



int STG_AREA::SendStgItems()
{
	int cnt;

	for(cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial && (dwPlayServTime - rsPlayInfo[cnt].dwLastRecvTime) < OVER_TRANS_TIME)
		{

			SendStgItem(&rsPlayInfo[cnt]);
		}
	}

	return TRUE;
}




int STG_AREA::SendStartPos(rsPLAYINFO *lpPlayInfo)
{
	smTRANS_ITEMS	TransItems;
	int cnt, scnt;
	int dx, dz, dist;

	cnt = 0;
	scnt = 0;

	StartPointActiveCount = 0;
	StartPointOpenCount = 0;

	while(1)
	{
		if(scnt >= TRANS_ITEM_MAX) break;
		if(cnt >= STG_START_POINT_MAX) break;

		if(StartPoint[cnt].state)
		{
			dx = StartPoint[cnt].x - (lpPlayInfo->Position.x >> FLOATNS);
			dz = StartPoint[cnt].z - (lpPlayInfo->Position.z >> FLOATNS);

			dist = dx*dx + dz*dz;

			if(dist < DIST_TRANSLEVEL_CONNECT && abs(dx) < TRANS_VIEW_LIMIT && abs(dz) < TRANS_VIEW_LIMIT)
			{

				StartPointNearPlay[cnt] ++;

				if(lpPlayInfo->getSecurity() >= AccountTypes::SEC_ADMINISTRATOR)
				{
					TransItems.Items[scnt].state = StartPoint[cnt].state;
					TransItems.Items[scnt].x = StartPoint[cnt].x << FLOATNS;
					TransItems.Items[scnt].y = 0;
					TransItems.Items[scnt].z = StartPoint[cnt].z << FLOATNS;
					TransItems.Items[scnt].ItemCode = 0;
					TransItems.Items[scnt].lpStgArea = (void *)this;


#ifdef _LANGUAGE_KOREAN
					wsprintf(TransItems.Items[scnt].szName, szMonsterFlagMsg, cnt, StartPointMonCount[cnt]);
#else
					strcpy_s(TransItems.Items[scnt].szName, szMonsterFlagMsg);
#endif
					scnt++;
				}
			}

			if(StartPointNearPlay[cnt])	StartPointActiveCount++;
			StartPointOpenCount++;

		}


		cnt++;
	}

	if(lpPlayInfo->getSecurity() >= AccountTypes::SEC_ADMINISTRATOR)
	{
		TransItems.code = OpCode::OPCODE_PLAYITEM;
		TransItems.size = sizeof(TRANS_ITEM)*scnt + 16;
		TransItems.state = 1;
		TransItems.Count = scnt;

		if(scnt > 0 && lpPlayInfo && lpPlayInfo->lpsmSock)
			return lpPlayInfo->lpsmSock->Send((char *)&TransItems, TransItems.size, TRUE);
	}
	return TRUE;
}

int STG_AREA::LoadStartPoint(char *szFile)
{
	FILE *fp;

	fp = fopen(szFile, "rb");
	if(fp)
	{
		fread(StartPoint, sizeof(STG_START_POINT)*STG_START_POINT_MAX, 1, fp);
		fclose(fp);
		dwActiveMode |= 1;
	}

	return TRUE;
}

int STG_AREA::SaveStartPoint(char *szFile)
{
	FILE *fp;

	fp = fopen(szFile, "wb");
	if(fp)
	{
		fwrite(StartPoint, sizeof(STG_START_POINT)*STG_START_POINT_MAX, 1, fp);
		fclose(fp);
		dwActiveMode |= 1;
	}

	return TRUE;
}







int	STG_AREA::FindEmptyMonTable()
{
	int cnt;

	for(cnt = 0; cnt < STG_MONSTER_MAX; cnt++)
	{
		if(lpCharMonster[cnt] == 0) return cnt;
	}

	return -1;
}


int	STG_AREA::AddMonTable(smCHAR *lpChar)
{
	int	cnt;
	int mtab;


	StartPointMonCount[lpChar->OpenStartPostion] ++;

	mtab = FindEmptyMonTable();
	if(mtab >= 0)
	{
		lpCharMonster[mtab] = lpChar;
		lpChar->lpExt4 = this;

		MonsterLastPoint = mtab;
		for(cnt = mtab; cnt < STG_MONSTER_MAX; cnt++)
		{
			if(lpCharMonster[cnt])
				MonsterLastPoint = cnt + 1;
		}
		return TRUE;
	}

	return FALSE;
}


int	STG_AREA::DeleteMonTable(smCHAR *lpChar)
{
	int cnt;



	if(StartPointMonCount[lpChar->OpenStartPostion] > 0)
		StartPointMonCount[lpChar->OpenStartPostion] --;

	for(cnt = 0; cnt < MonsterLastPoint; cnt++)
	{
		if(lpCharMonster[cnt] == lpChar)
		{
			lpCharMonster[cnt] = NULL;
			return TRUE;
		}
	}

	return FALSE;
}


smCHAR *STG_AREA::OpenMonster(STG_CHAR_INFO *lpStgCharInfo, int gGroup)
{

	smCHAR *lpChar;
	int dist;
	int x, y, z;
	int cnt;



	lpChar = srFindEmptyChar();
	if(!lpChar) return NULL;


	if(SetStartPosChar(lpChar) == TRUE)
	{
		MonsterCount++;
		lpChar->lpExt1 = (void *)&Head;
		lpChar->dwObjectSerial = GetNewObjectSerial();
		lpChar->ActionPattern = 5;
		memcpy(&lpChar->smCharInfo, &lpStgCharInfo->smCharInfo, sizeof(smCHAR_INFO));
		memcpy(&lpChar->smMonsterInfo, lpStgCharInfo->smCharInfo.lpMonInfo, sizeof(smCHAR_MONSTER_INFO));
		lpChar->SetLoadPattern(lpChar->smCharInfo.szModelName);


		lpChar->smCharInfo.StatePoint = lpStgCharInfo->smCharInfo.lpMonInfo->ClassCode;

		dist = 64 * 20;
		lpChar->DistAroundDbl = dist*dist;
		lpChar->AttackUserFlag = 0;
		lpChar->lpExt2 = 0;



		lpChar->lpExpAttackPlayInfo = 0;
		lpChar->ExpAttackLife = 0;


		lpChar->Angle.y = (GetCurrentTime() << 2)&ANGCLIP;
		lpChar->SetMotionFromCode(CHRMOTION_STATE_WALK);
		lpChar->TargetMoveCount = 2;

		AddMonTable(lpChar);

		if(lprsFixedPoint)
			lpChar->ReopenCount = REOPEN_COUNT_NUM * 32;
		else
			lpChar->ReopenCount = REOPEN_COUNT_NUM;

		lpChar->dwLastTransTime = dwPlayServTime;


		if(lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_DEATHKNIGHT || lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_KELVEZU || lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_MOKOVA)
		{
			lpChar->UseObject_VirtualLife = lpChar->smMonsterInfo.PotionCount;
			lpChar->sObject_VirtualLife[0] = lpChar->UseObject_VirtualLife;
			lpChar->sObject_VirtualLife[1] = lpChar->UseObject_VirtualLife;
			lpChar->sObject_DisplayLife[0] = lpChar->UseObject_VirtualLife;
			lpChar->sObject_DisplayLife[1] = lpChar->UseObject_VirtualLife;
		}
		else
		{

			if(lpChar->smMonsterInfo.PotionCount)
			{
				if((rand() % 100) < lpChar->smMonsterInfo.PotionPercent)
				{
					lpChar->smMonsterInfo.PotionCount = (rand() % lpChar->smMonsterInfo.PotionCount) + 1;
				}
				else
				{
					lpChar->smMonsterInfo.PotionCount = 0;
				}
			}
		}

#ifdef	_LANGUAGE_JAPANESE 
		if(rsDamgeOffEvent)
		{

			lpChar->smCharInfo.Attack_Damage[0] = (lpChar->smCharInfo.Attack_Damage[0] * ATTACK_RATE) / 100;
			lpChar->smCharInfo.Attack_Damage[1] = (lpChar->smCharInfo.Attack_Damage[1] * ATTACK_RATE) / 100;
			if(lpChar->smMonsterInfo.SkillDamage[0])
			{
				lpChar->smMonsterInfo.SkillDamage[0] = (lpChar->smMonsterInfo.SkillDamage[0] * ATTACK_RATE) / 100;
				lpChar->smMonsterInfo.SkillDamage[1] = (lpChar->smMonsterInfo.SkillDamage[1] * ATTACK_RATE) / 100;
			}
		}
#else

		if(rsDamgeOffEvent1)
		{

			lpChar->smCharInfo.Attack_Damage[0] = (lpChar->smCharInfo.Attack_Damage[0] * 75) / 100;
			lpChar->smCharInfo.Attack_Damage[1] = (lpChar->smCharInfo.Attack_Damage[1] * 75) / 100;
			if(lpChar->smMonsterInfo.SkillDamage[0])
			{
				lpChar->smMonsterInfo.SkillDamage[0] = (lpChar->smMonsterInfo.SkillDamage[0] * 75) / 100;
				lpChar->smMonsterInfo.SkillDamage[1] = (lpChar->smMonsterInfo.SkillDamage[1] * 75) / 100;
			}
		}

		if(rsDamgeOffEvent2)
		{

			lpChar->smCharInfo.Attack_Damage[0] = (lpChar->smCharInfo.Attack_Damage[0] * 50) / 100;
			lpChar->smCharInfo.Attack_Damage[1] = (lpChar->smCharInfo.Attack_Damage[1] * 50) / 100;
			if(lpChar->smMonsterInfo.SkillDamage[0])
			{
				lpChar->smMonsterInfo.SkillDamage[0] = (lpChar->smMonsterInfo.SkillDamage[0] * 50) / 100;
				lpChar->smMonsterInfo.SkillDamage[1] = (lpChar->smMonsterInfo.SkillDamage[1] * 50) / 100;
			}
		}
#endif



		if(rsDefenseOffEvent)
		{

			lpChar->smCharInfo.Defence = (lpChar->smCharInfo.Defence*DEFENSE_RATE) / 100;
		}


		if(lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_VAMPRICMACHINE)
		{
			lpChar->DontMoveFlag = 1;
		}



		rsMonOpenCount++;

	}
	else
	{
		lpChar->Close();
		return NULL;
	}



	x = lpChar->pX;
	y = lpChar->pY;
	z = lpChar->pZ;

	for(cnt = 1; cnt < gGroup; cnt++)
	{

		lpChar = srFindEmptyChar();
		if(!lpChar) return NULL;

		if(SetStartPosNearChar(lpChar, x, y, z) == TRUE)
		{
			MonsterCount++;
			lpChar->lpExt1 = (void *)&Head;
			lpChar->dwObjectSerial = GetNewObjectSerial();
			lpChar->ActionPattern = 5;
			memcpy(&lpChar->smCharInfo, &lpStgCharInfo->smCharInfo, sizeof(smCHAR_INFO));
			memcpy(&lpChar->smMonsterInfo, lpStgCharInfo->smCharInfo.lpMonInfo, sizeof(smCHAR_MONSTER_INFO));
			lpChar->SetLoadPattern(lpChar->smCharInfo.szModelName);


			lpChar->smCharInfo.StatePoint = lpStgCharInfo->smCharInfo.lpMonInfo->ClassCode;

			dist = 64 * 20;
			lpChar->DistAroundDbl = dist*dist;
			lpChar->AttackUserFlag = 0;
			lpChar->lpExt2 = 0;


			lpChar->lpExpAttackPlayInfo = 0;
			lpChar->ExpAttackLife = 0;

			AddMonTable(lpChar);

			if(lprsFixedPoint)
				lpChar->ReopenCount = REOPEN_COUNT_NUM * 32;
			else
				lpChar->ReopenCount = REOPEN_COUNT_NUM;

			lpChar->dwLastTransTime = dwPlayServTime;


			if(lpChar->smMonsterInfo.PotionCount)
			{
				if((rand() % 100) < lpChar->smMonsterInfo.PotionPercent)
				{
					lpChar->smMonsterInfo.PotionCount = (rand() % lpChar->smMonsterInfo.PotionCount) + 1;
				}
				else
				{
					lpChar->smMonsterInfo.PotionCount = 0;
				}
			}

#ifdef	_LANGUAGE_JAPANESE 
			if(rsDamgeOffEvent)
			{

				lpChar->smCharInfo.Attack_Damage[0] = (lpChar->smCharInfo.Attack_Damage[0] * ATTACK_RATE) / 100;
				lpChar->smCharInfo.Attack_Damage[1] = (lpChar->smCharInfo.Attack_Damage[1] * ATTACK_RATE) / 100;
				if(lpChar->smMonsterInfo.SkillDamage[0])
				{
					lpChar->smMonsterInfo.SkillDamage[0] = (lpChar->smMonsterInfo.SkillDamage[0] * ATTACK_RATE) / 100;
					lpChar->smMonsterInfo.SkillDamage[1] = (lpChar->smMonsterInfo.SkillDamage[1] * ATTACK_RATE) / 100;
				}
			}
#else

			if(rsDamgeOffEvent1)
			{

				lpChar->smCharInfo.Attack_Damage[0] = (lpChar->smCharInfo.Attack_Damage[0] * 75) / 100;
				lpChar->smCharInfo.Attack_Damage[1] = (lpChar->smCharInfo.Attack_Damage[1] * 75) / 100;
				if(lpChar->smMonsterInfo.SkillDamage[0])
				{
					lpChar->smMonsterInfo.SkillDamage[0] = (lpChar->smMonsterInfo.SkillDamage[0] * 75) / 100;
					lpChar->smMonsterInfo.SkillDamage[1] = (lpChar->smMonsterInfo.SkillDamage[1] * 75) / 100;
				}
			}

			if(rsDamgeOffEvent2)
			{

				lpChar->smCharInfo.Attack_Damage[0] = (lpChar->smCharInfo.Attack_Damage[0] * 50) / 100;
				lpChar->smCharInfo.Attack_Damage[1] = (lpChar->smCharInfo.Attack_Damage[1] * 50) / 100;
				if(lpChar->smMonsterInfo.SkillDamage[0])
				{
					lpChar->smMonsterInfo.SkillDamage[0] = (lpChar->smMonsterInfo.SkillDamage[0] * 50) / 100;
					lpChar->smMonsterInfo.SkillDamage[1] = (lpChar->smMonsterInfo.SkillDamage[1] * 50) / 100;
				}
			}
#endif


			if(rsDefenseOffEvent)
			{

				lpChar->smCharInfo.Defence = (lpChar->smCharInfo.Defence*DEFENSE_RATE) / 100;
			}

			rsMonOpenCount++;


			if(lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_VAMPRICMACHINE ||
				lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_DOOR)
			{
				lpChar->DontMoveFlag = 2;
			}


		}
		else
		{
			lpChar->Close();
			return NULL;
		}
	}

	return lpChar;
}

int STG_AREA::SendStartPointFlag()
{
	int cnt;

	ZeroMemory(StartPointNearPlay, sizeof(int) * STG_START_POINT_MAX);

	for(cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial)
		{

			SendStartPos(&rsPlayInfo[cnt]);
		}
	}

	return TRUE;
}



int STG_AREA::Main()
{
	STG_CHAR_INFO StgCharInfo;
	int cnt;
	int rnd;
	int gGroup;
	DWORD	OsCode;
	smCHAR_INFO *lpCharInfo;

	Counter++;

	if(chrMonsterCnt > 0 && MonsterCount < rsMonsterList.LimitMax &&
		(Counter&rsMonsterList.OpenInterval) == 0 &&
		(lpField->FieldEvent != FIELD_EVENT_NIGHTMARE || FieldNightDay))
	{
		StgCharInfo.PosiState = TRUE;
		StgCharInfo.smCharInfo.Life[0] = 100;
		StgCharInfo.smCharInfo.Mana[0] = 100;
		StgCharInfo.smCharInfo.Life[1] = 100;
		StgCharInfo.smCharInfo.State = TRUE;

		if(rsMonsterList.Counter)
		{

			rnd = (rand() % rsMonsterList.PecetageCount);
			for(cnt = 0; cnt < rsMonsterList.Counter; cnt++)
			{
				if(rsMonsterList.rsMonster[cnt].NumOpenStart > rnd) break;
			}
			memcpy(&StgCharInfo.smCharInfo, rsMonsterList.rsMonster[cnt - 1].lpCharInfo, sizeof(smCHAR_INFO));

			if(EventMonster)
			{

				OpenEventMonster(&StgCharInfo.smCharInfo, this);
			}
			lpCharInfo = &StgCharInfo.smCharInfo;

			if(lpCharInfo && StgCharInfo.smCharInfo.lpMonInfo)
			{
				gGroup = GetRandomPos(StgCharInfo.smCharInfo.lpMonInfo->GenerateGroup[0],
					StgCharInfo.smCharInfo.lpMonInfo->GenerateGroup[1]);

				if(gGroup <= 0) gGroup = 1;


				if(Event_dwMonsterTime > dwPlayServTime && Event_MonsterPercentage > 0 && Event_lpChrMonster)
				{
					if((rand() % 1000) < Event_MonsterPercentage)
					{
						memcpy(&StgCharInfo.smCharInfo, Event_lpChrMonster, sizeof(smCHAR_INFO));
						gGroup = 1;
					}
				}



				if(rsServerConfig.Event_Child && srHammerMonsterCount > 0)
				{

					if((rand() % 1000) < rsServerConfig.Event_Child)
					{
						if(lpField->State == FIELD_STATE_FOREST)
						{
							for(cnt = 0; cnt < srHammerMonsterCount; cnt++)
							{

								if(srCharInfo_HammerMonster[cnt]->dwCharSoundCode == snCHAR_SOUND_HOBGOBLIN)
								{
									memcpy(&StgCharInfo.smCharInfo, srCharInfo_HammerMonster[cnt], sizeof(smCHAR_INFO));
									break;
								}
							}
						}
						else
							memcpy(&StgCharInfo.smCharInfo, srCharInfo_HammerMonster[rand() % srHammerMonsterCount], sizeof(smCHAR_INFO));

						gGroup = 1;
					}
				}

				if(rsServerConfig.Event_MorifSheltom)
				{

					if((rand() % 1000) < rsServerConfig.Event_MorifSheltom)
					{
						for(cnt = 0; cnt < chrMonsterCnt; cnt++)
						{
							if(chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_NPC_MORIF && chrMonsterList[cnt].Level == 60)
							{
								memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));
								break;
							}
						}
						gGroup = 1;
					}
				}


				if(rsServerConfig.Event_WorldCup)
				{

					int chrFind = 0;
					int rFind = rand() % 4;
					if((rand() % 1000) < rsServerConfig.Event_WorldCup)
					{
						for(cnt = 0; cnt < chrMonsterCnt; cnt++)
						{
							if(chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_WORLDCUP)
							{
								memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));
								if(chrFind == rFind) break;
								chrFind++;
							}
						}
						gGroup = 1;
					}
				}

				if(rsServerConfig.Event_MollyWolf)
				{

					if((rand() % 1000) < rsServerConfig.Event_MollyWolf)
					{
						for(cnt = 0; cnt < chrMonsterCnt; cnt++)
						{
							if(chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_NPC_MOLLYWOLF)
							{
								memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));
								break;
							}
						}
						gGroup = 1;
					}
				}

				if(rsServerConfig.Event_Ghost)
				{

					if((rand() % 1000) < rsServerConfig.Event_Ghost)
					{
						for(cnt = 0; cnt < chrMonsterCnt; cnt++)
						{
							if(chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_MRGHOST && chrMonsterList[cnt].wPlayClass[0] == MONSTER_CLASS_GHOST)
							{
								memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));
								break;
							}
						}
						gGroup = 1;
					}
				}

				if(rsServerConfig.Event_SantaGoblin)
				{

					if((rand() % 1000) < rsServerConfig.Event_SantaGoblin)
					{
						for(cnt = 0; cnt < chrMonsterCnt; cnt++)
						{
							if(chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_HOBGOBLIN && chrMonsterList[cnt].Level == 60)
							{
								memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));
								break;
							}
						}
						gGroup = 1;
					}
				}

				if(rsServerConfig.Event_SummerChicken)
				{

					if((rand() % 1000) < rsServerConfig.Event_SummerChicken)
					{
						for(cnt = 0; cnt < chrMonsterCnt; cnt++)
						{
							if(chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_RABIE && chrMonsterList[cnt].Level >= 10 && chrMonsterList[cnt].wPlayClass[1])
							{

								memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));
								break;
							}
						}
						gGroup = 1;
					}
				}


				if(rsServerConfig.Event_WarerMelonMonster)
				{
					if((rand() % 10000) < rsServerConfig.Event_WarerMelonMonster)
					{
						for(cnt = 0; cnt < chrMonsterCnt; cnt++)
						{
							if(chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_WATERMELON)
							{
								memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));
								break;
							}
						}
						gGroup = 1;
					}
				}


				if(rsServerConfig.Event_Chichen_Day)
				{
					if((rand() % 1000) < rsServerConfig.Event_Chichen_Day)
					{
						for(cnt = 0; cnt < chrMonsterCnt; cnt++)
						{
							if(chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_BEBECHICK)
							{
								memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));
								break;
							}
						}
						gGroup = 1;
					}
				}


				OpenMonster(&StgCharInfo, gGroup);
			}
		}

	}

	switch(Counter & 0x1FF)
	{
	case 0x80:
		SendStartPointFlag();
		break;
	case 0xC0:
		SendStgItems();
		break;
	}

	DWORD	dwTime;
	int		dist;

	dwTime = dwPlayServTime;

	for(cnt = 0; cnt < STG_ITEM_MAX; cnt++)
	{
		if(StgItems[cnt].state)
		{
			if(StgItems[cnt].dwLoseTime < dwTime)
			{
				StgItems[cnt].state = 0;
			}
		}
	}


	if(rsServerConfig.Event_HardCore && lpField->FieldCode == rsSOD_FIELD && rsMonsterList.Counter > 0)
	{
		if((Counter & 0x3F) == 0)
		{

			memcpy(&StgCharInfo.smCharInfo, rsMonsterList.rsMonster[0].lpCharInfo, sizeof(smCHAR_INFO));
			rsHardCoreEvent_OpenMonster(this, &StgCharInfo);
		}
	}


	if(lpField->FieldCode == rsCASTLE_FIELD)
	{

		rsMain_CombatCastle();
	}

	rsEventSpawn_Main(this);


	if(FieldNightDay != dwServ_NightDay)
	{
		if(lpField->FieldEvent == FIELD_EVENT_NIGHTMARE)
		{
			if(dwServ_NightDay)
			{

				for(cnt = 0; cnt < AUTOPLAYER_MAX; cnt++)
				{
					if(chrAutoPlayer[cnt].Flag && chrAutoPlayer[cnt].lpExt1 == this &&
						chrAutoPlayer[cnt].smCharInfo.State == smCHAR_STATE_NPC &&
						chrAutoPlayer[cnt].smMonsterInfo.EventNPC == 0)
					{

						chrAutoPlayer[cnt].Close();

						chrAutoPlayer[cnt].Flag = TRUE;


						rnd = chrAutoPlayer[cnt].smCharInfo.bUpdateInfo[0];
						OsCode = chrAutoPlayer[cnt].dwObjectSerial;


						memcpy(&chrAutoPlayer[cnt].smCharInfo, chrNpcMonsterInfo, sizeof(smCHAR_INFO));
						memcpy(&chrAutoPlayer[cnt].smMonsterInfo, chrNpcMonsterInfo->lpMonInfo, sizeof(smCHAR_MONSTER_INFO));
						chrAutoPlayer[cnt].ActionPattern = 5;
						MonsterCount++;
						chrAutoPlayer[cnt].SetLoadPattern(chrAutoPlayer[cnt].smCharInfo.szModelName);

						dist = 64 * 20;
						chrAutoPlayer[cnt].DistAroundDbl = dist*dist;
						AddMonTable(&chrAutoPlayer[cnt]);
						chrAutoPlayer[cnt].ReopenCount = REOPEN_COUNT_NUM;
						chrAutoPlayer[cnt].SetMotionFromCode(CHRMOTION_STATE_STAND);

						chrAutoPlayer[cnt].smCharInfo.bUpdateInfo[0] = rnd + 1;
						chrAutoPlayer[cnt].dwObjectSerial = OsCode;
					}
				}
			}
			else
			{

				for(cnt = 0; cnt < AUTOPLAYER_MAX; cnt++)
				{
					if(chrAutoPlayer[cnt].Flag && chrAutoPlayer[cnt].lpExt1 == this &&
						chrAutoPlayer[cnt].smCharInfo.State == smCHAR_STATE_ENEMY)
					{


						chrAutoPlayer[cnt].smCharInfo.Life[0] = 0;
						chrAutoPlayer[cnt].SetMotionFromCode(CHRMOTION_STATE_DEAD);
					}
				}

				rsOpenNPC_RandomPos = rand();

				for(cnt = 0; cnt < FIX_CHAR_MAX; cnt++)
				{
					if(TransCharFixed[cnt].code)
						OpenNpc(&TransCharFixed[cnt]);
				}
			}
		}

		if(lpField->FieldCode == 3)
		{


			if(dwServ_NightDay)
			{


				rsCloseEventMonster(100);
				rsOpenEventMonster(100, 0, 0, 0);

			}
			else
			{
				rsCloseEventMonster(100);


				for(cnt = 0; cnt < FIX_CHAR_MAX; cnt++)
				{
					if(TransCharFixed[cnt].code && TransCharFixed[cnt].smCharInfo.dwCharSoundCode == snCHAR_SOUND_WOLVERLIN)
						OpenNpc(&TransCharFixed[cnt]);
				}

			}
		}

		FieldNightDay = dwServ_NightDay;
	}

	return TRUE;
}




int STG_AREA::LoadStage(char *szFile)
{
	smSTAGE3D *lpRes;
	int cnt;

	lpStage = new smSTAGE3D;
	lpRes = smSTAGE3D_ReadASE(szFile, lpStage);
	lpStage->Head = TRUE;


	if(lpRes)
	{

		SetFieldInfoPath(szStartPointFile, szFile, "spp");
		LoadStartPoint(szStartPointFile);

		SetFieldInfoPath(szCharFixedFile, szFile, "spc");
		if(LoadCharInfoFixed(szCharFixedFile))
		{
			for(cnt = 0; cnt < FIX_CHAR_MAX; cnt++)
			{
				if(TransCharFixed[cnt].code)
					OpenNpc(&TransCharFixed[cnt]);
			}
			dwActiveMode |= 2;
		}

		SetFieldInfoPath(szCharMonsterFile, szFile, "spm");


		DecodeOpenMonster(szCharMonsterFile, &rsMonsterList, chrMonsterList, chrMonsterCnt);
		if(!rsMonsterList.LimitMax) rsMonsterList.LimitMax = 10;

		return TRUE;
	}

	delete lpStage;
	lpStage = 0;

	return FALSE;
}



int STG_AREA::FindStartPoint(int x, int z)
{
	int cnt;
	for(cnt = 0; cnt < STG_START_POINT_MAX; cnt++)
	{
		if(StartPoint[cnt].state &&
			StartPoint[cnt].x == x && StartPoint[cnt].z == z)
		{
			return cnt;
		}
	}

	return -1;
}





int STG_AREA::AddStartPoint(int x, int z, int state)
{
	int cnt;


	cnt = FindStartPoint(x, z);
	if(cnt >= 0) return FALSE;

	for(cnt = 0; cnt < STG_START_POINT_MAX; cnt++)
	{
		if(!StartPoint[cnt].state)
		{
			StartPoint[cnt].state = state;
			StartPoint[cnt].x = x;
			StartPoint[cnt].z = z;
			StartPointMonCount[cnt] = 0;
			SaveStartPoint(szStartPointFile);
			return TRUE;
		}
	}

	return FALSE;
}


int STG_AREA::DeleteStartPoint(int x, int z)
{
	int cnt;

	cnt = FindStartPoint(x, z);
	if(cnt >= 0)
	{
		StartPoint[cnt].state = 0;
		StartPointMonCount[cnt] = 0;
		SaveStartPoint(szStartPointFile);
		return TRUE;
	}
	return FALSE;
}

int STG_AREA::StartPosRandomize()
{
	int cnt;
	int end;
	int rnd;

	end = 1;

	for(cnt = STG_START_POINT_MAX - 1; cnt >= 0; cnt--)
	{
		if(StartPoint[cnt].state)
		{
			end = cnt + 1;
		}
	}

	rnd = rand() % end;

	StartPointCnt = rnd;

	return TRUE;
}


int STG_AREA::SetStartPosChar(smCHAR *lpChar)
{
	int x, y, cnt;
	int flag;

	flag = 0;

	for(cnt = StartPointCnt; cnt < STG_START_POINT_MAX; cnt++)
	{
		if(StartPoint[cnt].state && StartPointNearPlay[cnt] &&
			StartPointMonCount[cnt] < rsMonsterList.OpenLimit &&
			dwStartPoint_OpenTime[cnt] < dwPlayServTime)
		{

			x = StartPoint[cnt].x * fONE;
			y = StartPoint[cnt].z * fONE;
			StartPointCnt = cnt + 1;
			StartPointLastOpenCount = cnt;
			flag++;
			break;
		}
	}

	if(flag == 0)
	{
		for(cnt = 0; cnt < STG_START_POINT_MAX; cnt++)
		{
			if(StartPoint[cnt].state && StartPointNearPlay[cnt] &&
				StartPointMonCount[cnt] < rsMonsterList.OpenLimit &&
				dwStartPoint_OpenTime[cnt] < dwPlayServTime)
			{

				x = StartPoint[cnt].x * fONE;
				y = StartPoint[cnt].z * fONE;
				StartPointCnt = cnt + 1;
				StartPointLastOpenCount = cnt;
				flag++;
				break;
			}
		}
	}

	if(flag == 0 && EvnMonster)
	{
		EvnMonster = 0;



		for(cnt = StartPointCnt; cnt < STG_START_POINT_MAX; cnt++)
		{
			if(StartPoint[cnt].state && StartPointNearPlay[cnt])
			{
				x = StartPoint[cnt].x * fONE;
				y = StartPoint[cnt].z * fONE;
				flag++;
				break;
			}
		}

		if(flag == 0 && StartPointCnt < STG_START_POINT_MAX)
		{
			for(cnt = 0; cnt < StartPointCnt; cnt++)
			{
				if(StartPoint[cnt].state && StartPointNearPlay[cnt])
				{
					x = StartPoint[cnt].x * fONE;
					y = StartPoint[cnt].z * fONE;
					flag++;
					break;
				}
			}
		}

		if(flag == 0)
		{
			for(cnt = 0; cnt < STG_START_POINT_MAX; cnt++)
			{
				if(StartPoint[cnt].state)
				{
					x = StartPoint[cnt].x * fONE;
					y = StartPoint[cnt].z * fONE;
					flag++;
					break;
				}
			}
		}
	}

	if(flag > 0)
	{

		if(lprsFixedPoint)
		{
			x = lprsFixedPoint->x;
			y = lprsFixedPoint->z;
		}

		lpChar->Init();
		lpChar->lpStage = lpStage;
		lpChar->SetPosi(x, 0, y, 0, 0, 0);

		lpChar->PosiAround.x = x;
		lpChar->PosiAround.y = lpChar->pY;
		lpChar->PosiAround.z = y;
		lpChar->DistAroundDbl = DIST_AROUND_MIDDLE;

		lpChar->OpenStartPostion = StartPointLastOpenCount;

		dwStartPoint_OpenTime[StartPointLastOpenCount] = dwPlayServTime + rsMonsterList.dwIntervalTime;

		return TRUE;
	}

	return FALSE;
}



int STG_AREA::SetStartPosNearChar(smCHAR *lpChar, int cx, int cy, int cz)
{
	int cnt;
	int height;
	int mCnt;
	int x, y, z;

	for(cnt = 0; cnt < 8; cnt++)
	{
		MonsterSettingCount++;
		mCnt = MonsterSettingCount & 7;

		x = cx + ptItemSettingPosi[mCnt].x * 4 * fONE;
		z = cz + ptItemSettingPosi[mCnt].y * 4 * fONE;
		y = cy;


		height = lpStage->GetFloorHeight(x, y, z, 32 * fONE);
		if(height != CLIP_OUT)
		{
			if(abs(height - y) < fONE * 64) break;
		}
	}

	if(cnt < 8)
	{
		lpChar->Init();
		lpChar->lpStage = lpStage;
		lpChar->SetPosi(x, 0, z, 0, 0, 0);
		lpChar->PosiAround.x = x;
		lpChar->PosiAround.y = lpChar->pY;
		lpChar->PosiAround.z = z;
		lpChar->DistAroundDbl = DIST_AROUND_MIDDLE;
		lpChar->OpenStartPostion = StartPointLastOpenCount;
		return TRUE;
	}

	return FALSE;
}


int STG_AREA::SetPosNearChar(smCHAR *lpChar, int cx, int cy, int cz)
{
	int cnt;
	int height;
	int mCnt;
	int x, y, z;

	for(cnt = 0; cnt < 8; cnt++)
	{
		MonsterSettingCount++;
		mCnt = MonsterSettingCount & 7;

		x = cx + ptItemSettingPosi[mCnt].x * 4 * fONE;
		z = cz + ptItemSettingPosi[mCnt].y * 4 * fONE;
		y = cy;


		height = lpStage->GetFloorHeight(x, y, z, 32 * fONE);
		if(height != CLIP_OUT)
		{
			if(abs(height - y) < fONE * 64) break;
		}
	}

	if(cnt < 8)
	{
		lpChar->SetPosi(x, 0, z, 0, 0, 0);
		lpChar->PosiAround.x = x;
		lpChar->PosiAround.y = lpChar->pY;
		lpChar->PosiAround.z = z;
		lpChar->DistAroundDbl = DIST_AROUND_MIDDLE;
		return TRUE;
	}

	return FALSE;
}



int SetStartPosChar(smCHAR *lpChar)
{
	int x, y, cnt;


	cnt = StartPointCnt;
	x = StartPoint[cnt].x * fONE;
	y = StartPoint[cnt].y * fONE;

	StartPointCnt++;
	if(StartPointCnt >= START_POINT_MAX) StartPointCnt = 0;

	return TRUE;
}


int srInitChar()
{
	int cnt;

	InitPatterns();

	for(cnt = 0; cnt < AUTOPLAYER_MAX; cnt++)
	{
		chrAutoPlayer[cnt].Init();
		chrAutoPlayer[cnt].lpStage = lpsmStage[1];
	}

	return TRUE;
}

int srRemoveChar()
{


	ClosePatterns();

	return TRUE;
}



STG_AREA *FindStageField(int x, int z)
{
	int cnt;
	int he;

	for(cnt = 0; cnt < STAGE_AREA_MAX; cnt++)
	{
		if(StageArea[cnt].lpStage)
		{
			he = StageArea[cnt].lpStage->GetHeight(x, z);
			if(he > 0)
			{
				return &StageArea[cnt];
			}
		}
	}

	return NULL;
}



int srReadStage()
{
	int cnt;


	InitStageLoader();
	InitField();




	cnt = 0;

	while(1)
	{
		if(sField[cnt].szName[0] == 0) break;




		StageArea[cnt].LoadStage(sField[cnt].szName);
		StageArea[cnt].lpField = &sField[cnt];
		cnt++;
	}



	lpsmStage[0] = StageArea[0].lpStage;
	lpsmStage[1] = StageArea[0].lpStage;



	return TRUE;
}

int srRemoveStage()
{

	return TRUE;
}






int rsSendCharInfo(smCHAR *lpChar, rsPLAYINFO *lpPlayInfo)
{

	smTRNAS_PLAYERINFO	TransPlayerInfo;

	memcpy(&TransPlayerInfo.smCharInfo, &lpChar->smCharInfo, sizeof(smCHAR_INFO));
	TransPlayerInfo.size = sizeof(smTRNAS_PLAYERINFO);
	TransPlayerInfo.code = OpCode::OPCODE_PLAYERINFO;
	TransPlayerInfo.dwObjectSerial = lpChar->dwObjectSerial;

	TransPlayerInfo.x = lpChar->pX;
	TransPlayerInfo.y = lpChar->pY;
	TransPlayerInfo.z = lpChar->pZ;

	if(lpPlayInfo->getSecurity() < AccountTypes::SEC_GAMEMASTER)
	{
		TransPlayerInfo.smCharInfo.Attack_Damage[0] = 1000;
		TransPlayerInfo.smCharInfo.Attack_Damage[1] = 9999;

	}

	return lpPlayInfo->lpsmSock->Send((char *)&TransPlayerInfo, TransPlayerInfo.size, TRUE);
}




int rsSendPlayerInfo(rsPLAYINFO *lpSndPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	smCHAR		*lpChar;
	rsPLAYINFO	*lpPlayInfo;
	smTRNAS_PLAYERINFO	TransPlayerInfo;


	lpChar = srFindCharFromSerial(lpTransCommand->WParam);
	if(lpChar)
	{

		rsSendCharInfo(lpChar, lpSndPlayInfo);
		return TRUE;
	}



	lpPlayInfo = srFindUserFromSerial(lpTransCommand->WParam);
	if(lpPlayInfo && lpPlayInfo->dwObjectSerial && lpSndPlayInfo && lpSndPlayInfo->lpsmSock)
	{

		memcpy(&TransPlayerInfo.smCharInfo, &lpPlayInfo->smCharInfo, sizeof(smCHAR_INFO));

		TransPlayerInfo.size = sizeof(smTRNAS_PLAYERINFO);
		TransPlayerInfo.code = OpCode::OPCODE_PLAYERINFO;
		TransPlayerInfo.dwObjectSerial = lpPlayInfo->dwObjectSerial;

		TransPlayerInfo.x = lpPlayInfo->Position.x;
		TransPlayerInfo.y = lpPlayInfo->Position.y;
		TransPlayerInfo.z = lpPlayInfo->Position.z;

		return lpSndPlayInfo->lpsmSock->Send((char *)&TransPlayerInfo, TransPlayerInfo.size, TRUE);
	}

	return TRUE;
}


int rsSendPlayerInfoQuick(rsPLAYINFO *lpSndPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	smCHAR		*lpChar;
	rsPLAYINFO	*lpPlayInfo;
	smTRNAS_PLAYERINFO_QUICK	TransPlayerInfoQ;
	int			QuickSize;


	lpChar = srFindCharFromSerial(lpTransCommand->WParam);
	if(lpChar)
	{
		rsSendCharInfo(lpChar, lpSndPlayInfo);
		return TRUE;
	}


	lpPlayInfo = srFindUserFromSerial(lpTransCommand->WParam);
	if(lpPlayInfo && lpPlayInfo->dwObjectSerial && lpSndPlayInfo && lpSndPlayInfo->lpsmSock)
	{

		if(lpPlayInfo->smCharInfo.bUpdateInfo[0] != 0)
		{


			QuickSize = smCHAR_INFO_QUICK_SIZE2;
		}
		else
		{
			QuickSize = smCHAR_INFO_QUICK_SIZE;
		}

		memcpy(&TransPlayerInfoQ.smCharInfo, &lpPlayInfo->smCharInfo, QuickSize);
		TransPlayerInfoQ.size = sizeof(smTRNAS_PLAYERINFO_QUICK) - (sizeof(smCHAR_INFO) - QuickSize);
		TransPlayerInfoQ.code = OpCode::OPCODE_PLAYERINFO_Q;
		TransPlayerInfoQ.dwObjectSerial = lpPlayInfo->dwObjectSerial;
		TransPlayerInfoQ.x = lpPlayInfo->Position.x;
		TransPlayerInfoQ.y = lpPlayInfo->Position.y;
		TransPlayerInfoQ.z = lpPlayInfo->Position.z;

		return lpSndPlayInfo->lpsmSock->Send((char *)&TransPlayerInfoQ, TransPlayerInfoQ.size, TRUE);
	}

	return TRUE;
}


int srGetTotalExp(int exp, int level)
{
	if(level < 0)
	{
		level *= -1;
	}

	int result = 0;


	if(level <= 10)
	{
		result = exp;
	}
	if(level <= 20)
	{
		result = (int)(exp * 0.85);
	}
	if(level <= 30)
	{
		result = (int)(exp * 0.70);
	}
	else
	{
		result = (int)(exp * 0.55);
	}

	if(result < 0)
	{
		result = (int)(exp * 0.5);
	}

	return result;
}


int rsSendTransSkillAttack(smCHAR *lpChar, rsPLAYINFO *lpPlayInfo)
{
	TRANS_ATTACKDATA TransAttackData;
	int	temp;



	if(lpChar->dwClanCode && lpChar->dwClanCode == lpPlayInfo->dwClanCode)
		return NULL;


	TransAttackData.code = OpCode::OPCODE_ATTACKDATA;
	TransAttackData.size = sizeof(TRANS_ATTACKDATA);

	TransAttackData.x = lpPlayInfo->Position.x;
	TransAttackData.y = lpPlayInfo->Position.y;
	TransAttackData.z = lpPlayInfo->Position.z;

	TransAttackData.AttackState = 0x80;

	TransAttackData.AttackSize = 32 * fONE;
	TransAttackData.Power = GetRandomPos(lpChar->smMonsterInfo.SkillDamage[0], lpChar->smMonsterInfo.SkillDamage[1]);

	TransAttackData.dwDestObjectSerial = lpChar->dwObjectSerial;
	TransAttackData.dwTarObjectSerial = lpPlayInfo->dwObjectSerial;

	TransAttackData.sRating[0] = lpChar->smCharInfo.Level;
	TransAttackData.sRating[1] = lpChar->smCharInfo.Attack_Rating;


	if(lpPlayInfo->dwSiegeItem_Scroll_Time && lpPlayInfo->dwSiegeItem_Scroll_Time < dwPlayServTime)
	{
		lpPlayInfo->dwSiegeItem_Scroll_Code = 0;
		lpPlayInfo->dwSiegeItem_Scroll_Time = 0;
	}
	if(lpPlayInfo->dwSiegeItem_Stone1_Time && lpPlayInfo->dwSiegeItem_Stone1_Time < dwPlayServTime)
	{
		lpPlayInfo->dwSiegeItem_Stone1_Code = 0;
		lpPlayInfo->dwSiegeItem_Stone1_Time = 0;
	}

	if(lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_B)
	{

		TransAttackData.sRating[0] = -SKILL_PLAY_ICE_CRYSTAL;
		TransAttackData.sRating[1] = 4;
	}
	else if(lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_G)
	{

		TransAttackData.sRating[0] = -SKILL_PLAY_LIGHTNING_CRYSTAL;
		TransAttackData.sRating[1] = 3;
	}
	else if(lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_R)
	{

		TransAttackData.sRating[0] = -SKILL_PLAY_FIRE_CRYSTAL;
		TransAttackData.sRating[1] = 1;
	}

	if(lpPlayInfo->dwSiegeItem_Stone1_Code && lpPlayInfo->dwSiegeItem_Stone1_Code == lpChar->smCharInfo.dwCharSoundCode)
	{

		TransAttackData.Power /= 2;
		TransAttackData.sRating[0] = lpChar->smCharInfo.Level;
		TransAttackData.sRating[1] = lpChar->smCharInfo.Attack_Rating;
	}

	if(lpPlayInfo->dwSiegeItem_Scroll_Code == (sinBC1 | sin01))
	{
		if(lpPlayInfo->Position.Area == rsCASTLE_FIELD) return FALSE;
	}
	if(lpPlayInfo->dwSiegeItem_Scroll_Code == (sinBI1 | sin05))
		return FALSE;


	if(lpPlayInfo->dwSkill_PhysicalAbsorb_Time)
	{
		if(lpPlayInfo->dwSkill_PhysicalAbsorb_Time > dwPlayServTime)
		{
			TransAttackData.Power -= lpPlayInfo->dwSkill_PhysicalAbsorb_Param;
			if(TransAttackData.Power < 0) return FALSE;
		}
		else
		{
			lpPlayInfo->dwSkill_PhysicalAbsorb_Time = 0;
			lpPlayInfo->dwSkill_PhysicalAbsorb_Param = 0;
		}
	}

	if(lpPlayInfo->dwSkill_MetalArmor_Time)
	{
		if(lpPlayInfo->dwSkill_MetalArmor_Time > dwPlayServTime)
		{
			TransAttackData.Power -= lpPlayInfo->dwSkill_MetalArmor_Param;
			if(TransAttackData.Power < 0) return FALSE;
		}
		else
		{
			lpPlayInfo->dwSkill_MetalArmor_Time = 0;
			lpPlayInfo->dwSkill_MetalArmor_Param = 0;
		}
	}



	if(lpPlayInfo->dwSkill_HolyBody_Time)
	{
		if(lpPlayInfo->dwSkill_HolyBody_Time > dwPlayServTime)
		{
			if(lpChar->smCharInfo.Brood == smCHAR_MONSTER_UNDEAD)
			{
				TransAttackData.Power -= (TransAttackData.Power*lpPlayInfo->dwSkill_HolyBody_Param) / 100;
				if(TransAttackData.Power < 0) return FALSE;
			}
		}
		else
		{
			lpPlayInfo->dwSkill_HolyBody_Time = 0;
			lpPlayInfo->dwSkill_HolyBody_Param = 0;
		}
	}

	if(lpPlayInfo->dwSkill_VirtualLife_Time)
	{
		if(lpPlayInfo->dwSkill_VirtualLife_Time > dwPlayServTime)
		{
			TransAttackData.Power -= (TransAttackData.Power*lpPlayInfo->dwSkill_VirtualLife_Param) / 100;
			if(TransAttackData.Power < 0) return FALSE;
		}
		else
		{
			lpPlayInfo->dwSkill_VirtualLife_Time = 0;
			lpPlayInfo->dwSkill_VirtualLife_Param = 0;
		}
	}

	if(lpPlayInfo->dwSkill_EnergyShield_Time)
	{
		if(lpPlayInfo->dwSkill_EnergyShield_Time > dwPlayServTime)
		{
			temp = (TransAttackData.Power*lpPlayInfo->dwSkill_EnergyShield_Param) / 100;
			TransAttackData.Power -= temp;
			TransAttackData.AttackState |= (temp << 16);
			if(TransAttackData.Power < 0) return FALSE;
		}
		else
		{
			lpPlayInfo->dwSkill_EnergyShield_Time = 0;
			lpPlayInfo->dwSkill_EnergyShield_Param = 0;
		}
	}

	if(lpPlayInfo->dwBlessSkill_Code)
	{
		if(lpPlayInfo->dwBlessSkill_Code == SKILL_PLAY_BLESS_ABSORB)
		{
			if(lpPlayInfo->dwBlessSkill_Time > dwPlayServTime)
			{
				TransAttackData.Power -= lpPlayInfo->dwBlessSkill_Param;
				if(TransAttackData.Power < 0) return FALSE;
			}
			else
			{
				lpPlayInfo->dwBlessSkill_Code = 0;
				lpPlayInfo->dwBlessSkill_Time = 0;
			}
		}
	}


	if(lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CHAOSCARA && lpChar->smMonsterInfo.SkillRangeRect.left == 0 && lpChar->smMonsterInfo.SkillRangeRect.right == 0)
	{
		TransAttackData.sRating[0] = -SKILL_PLAY_CHAOSCARA_VAMP;
		TransAttackData.sRating[1] = 0;
	}

	TransAttackData.dwChkSum = TransAttackData.Power * 2002 +
		(TransAttackData.x * TransAttackData.y * TransAttackData.z);

	if(lpPlayInfo->lpsmSock)
	{


		lpPlayInfo->Send_AttackCount++;
		lpPlayInfo->Send_AttackDamage += TransAttackData.Power;

		if(rsServerConfig.CrazyPacketMode && lpPlayInfo->dwDecPacketCode &&
			lpPlayInfo->dwDecPacketTime2 < dwPlayServTime)
		{

			TransAttackData.code = OpCode::OPCODE_ATTACKDATA2;
			TransAttackData.dwDamageChkSum = dm_GetDamgeChkSum_S2V(&TransAttackData);

			if(lpPlayInfo)
				rsEncodeDamagePacket(lpPlayInfo, &TransAttackData);
		}
		else
			TransAttackData.dwDamageChkSum = dm_GetDamgeChkSum_S2V(&TransAttackData);


		return lpPlayInfo->lpsmSock->Send((char *)&TransAttackData, TransAttackData.size, TRUE);
	}

	return NULL;
}



int rsCharChanger(smCHAR *lpChar, smCHAR_INFO *lpCharInfo, smCHAR_MONSTER_INFO *lpMonInfo)
{
	int rnd, OsCode;
	int dist;
	STG_AREA	*lpStgArea;


	lpStgArea = (STG_AREA *)lpChar->lpExt1;

	lpChar->Close();
	lpChar->Flag = TRUE;


	rnd = lpChar->smCharInfo.bUpdateInfo[0];
	OsCode = lpChar->dwObjectSerial;



	memcpy(&lpChar->smCharInfo, lpCharInfo, sizeof(smCHAR_INFO));
	memcpy(&lpChar->smMonsterInfo, lpMonInfo, sizeof(smCHAR_MONSTER_INFO));
	lpChar->ActionPattern = 5;

	lpChar->SetLoadPattern(lpChar->smCharInfo.szModelName);

	dist = 64 * 30;
	lpChar->DistAroundDbl = dist*dist;
	lpChar->PosiAround.x = lpChar->pX;
	lpChar->PosiAround.z = lpChar->pZ;




	lpChar->ReopenCount = REOPEN_COUNT_NUM;
	lpChar->SetMotionFromCode(CHRMOTION_STATE_STAND);
	lpChar->smCharInfo.bUpdateInfo[0] = rnd + 1;
	lpChar->dwObjectSerial = OsCode;
	lpChar->lpTargetPlayInfo = 0;
	lpChar->smCharInfo.Life[0] = lpChar->smCharInfo.Life[1];
	lpChar->smCharInfo.StatePoint = lpMonInfo->ClassCode;


	if(lpChar->smMonsterInfo.PotionCount)
	{
		if((rand() % 100) < lpChar->smMonsterInfo.PotionPercent)
		{
			lpChar->smMonsterInfo.PotionCount = (rand() % lpChar->smMonsterInfo.PotionCount) + 1;
		}
		else
		{
			lpChar->smMonsterInfo.PotionCount = 0;
		}
	}


	return TRUE;
}



int	SelectDamageTop10(smCHAR *lpChar, rsUSER_LIST_TOP10 *lpUserListDamageTop10)
{
	int cnt, cnt2;
	int ChkCnt;
	smWINSOCK	*lpsmSock;

	if(!lpChar->lpAttackDamageList || !lpUserListDamageTop10) return FALSE;

	ZeroMemory(lpUserListDamageTop10, sizeof(rsUSER_LIST_TOP10));

	for(cnt = 0; cnt < 10; cnt++)
	{
		ChkCnt = -1;
		for(cnt2 = 0; cnt2 < ATTACK_DAMAGE_LIST_MAX; cnt2++)
		{
			if(lpChar->lpAttackDamageList[cnt2].dwUserCode &&
				lpChar->lpAttackDamageList[cnt2].DamageCount > lpUserListDamageTop10->Damage[cnt])
			{

				lpUserListDamageTop10->dwUserCode[cnt] = lpChar->lpAttackDamageList[cnt2].dwUserCode;
				lpUserListDamageTop10->Damage[cnt] = lpChar->lpAttackDamageList[cnt2].DamageCount;
				lpUserListDamageTop10->Counter[cnt] = lpChar->lpAttackDamageList[cnt2].Count;

				ChkCnt = cnt2;
			}
		}

		if(ChkCnt >= 0)
			lpChar->lpAttackDamageList[ChkCnt].dwUserCode = 0;
	}

	lpUserListDamageTop10->dwUpdateTime = dwPlayServTime;
	lpUserListDamageTop10->dwCharCode = lpChar->dwObjectSerial;

	lpUserListDamageTop10->code = OpCode::OPCODE_SYSTEM;
	lpUserListDamageTop10->size = sizeof(rsUSER_LIST_TOP10);
	lpUserListDamageTop10->tCode = smTRANS_SYSCODE_DMG_USER_LIST;
	lpUserListDamageTop10->dwObjectSerial = rsServerConfig.ServerCode;

	if(!dwSerToSerIP) return TRUE;

	lpsmSock = rsFindNextSertoServerSock();

	if(lpsmSock)
		return lpsmSock->Send((char *)lpUserListDamageTop10, lpUserListDamageTop10->size, TRUE);

	return FALSE;
}



DWORD dwSoD_ItemDropTable[8][2] = {
	{	(sinSD2 | sin01)	,	20	},
	{	(sinSD2 | sin02)	,	40	},
	{	(sinSD2 | sin03)	,	60	},
	{	(sinSD2 | sin04)	,	68	},
	{	(sinSD2 | sin05)	,	80	},
	{	(sinSD2 | sin06)	,	95	},
	{	(sinSD2 | sin07)	,	100	},
	{	0,0 }
};




int rsOpen_SodItem(smCHAR *lpChar, rsPLAYINFO *lprsPlayInfo)
{
	int rnd, cnt, cnt2;
	psITEM	psItem;
	STG_ITEMS	*lpStgItem;


	rnd = rand() % 1000;
	if(rnd < 20)
	{
		rnd = rand() % 100;
		for(cnt = 0; cnt < 7; cnt++)
		{
			if(dwSoD_ItemDropTable[cnt][0] == 0) return FALSE;
			if((DWORD)rnd < dwSoD_ItemDropTable[cnt][1])
			{

				for(cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if(DefaultItems[cnt2].Item.CODE == dwSoD_ItemDropTable[cnt][0] && !DefaultItems[cnt2].Item.UniqueItem)
					{
						CreateDefItem(&psItem.ItemInfo, &DefaultItems[cnt2]);

						psItem.state = TRUE;
						lpStgItem = ((STG_AREA *)lpChar->lpExt1)->AddItem(&psItem, lpChar->pX >> FLOATNS, lpChar->pY >> FLOATNS, lpChar->pZ >> FLOATNS, TRUE);
						((STG_AREA *)lpChar->lpExt1)->SendStgItemToNearUsers(lpStgItem);

						break;
					}
				}
				return TRUE;
			}
		}
	}

	return FALSE;
}


int rsCheckEventItem(DWORD dwItemCode, rsPLAYINFO *lpPlayInfo, smCHAR *lpChar)
{
	int rnd;


	if(lpChar->smMonsterInfo.dwEvnetItem == (sinQT1 | sin13))
	{

		rnd = rand() % 100;

		if(lpPlayInfo->smCharInfo.ChangeJob < 3 && rnd <= 20)
		{
			return TRUE;
		}
	}
	else
		return TRUE;


	return FALSE;
}



int rsOpen_MonsterItemExp(smCHAR *lpChar, rsPLAYINFO *lprsPlayInfo)
{
	psITEM		sItem;
	psITEM		*lpsItem = &sItem;
	STG_ITEMS	*lpStgItem;
	smTRANS_COMMAND	smTransCommand;
	int			cnt, cnt2;
	DWORD		dwCode;


	rsPLAYINFO	*lpDamagePlayInfo[10];
	int			DmgPlayUse = FALSE;


	if(rsUserListDamageTop10.dwCharCode && rsUserListDamageTop10.dwCharCode == lpChar->dwObjectSerial)
	{
		for(cnt = 0; cnt < 10; cnt++)
		{
			if(rsUserListDamageTop10.dwUserCode[cnt])
			{
				lpDamagePlayInfo[cnt] = srFindUserFromSerial(rsUserListDamageTop10.dwUserCode[cnt]);
			}
			else
				lpDamagePlayInfo[cnt] = 0;
		}

#ifdef _LANGUAGE_KOREAN
#ifdef _TEST_SERVER

		TRANS_CHATMESSAGE	TransChatMessage;

		for(cnt2 = 0; cnt2 < 10; cnt2++)
		{
			if(lpDamagePlayInfo[cnt2] && lpDamagePlayInfo[cnt2]->AdminMode >= 3)
			{
				for(cnt = 0; cnt < 6; cnt++)
				{
					if(lpDamagePlayInfo[cnt])
					{

						wsprintf(TransChatMessage.szMessage, "%s(%d)> %s ( %d  %d )",
							lpChar->smCharInfo.szName, cnt,
							lpDamagePlayInfo[cnt]->smCharInfo.szName,
							rsUserListDamageTop10.Damage[cnt],
							rsUserListDamageTop10.Counter[cnt]);

						TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
						TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
						TransChatMessage.dwIP = 0;
						TransChatMessage.dwObjectSerial = lpDamagePlayInfo[cnt]->dwObjectSerial;
						lpDamagePlayInfo[cnt2]->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
					}
				}
			}
		}

#endif
#endif

		ZeroMemory(&rsUserListDamageTop10, sizeof(rsUSER_LIST_TOP10));
		DmgPlayUse = TRUE;

		int	BabelHornSort[10];
		int	BabelHornSortCnt;

		BabelHornSortCnt = 2;
		BabelHornSort[0] = 0;
		BabelHornSort[1] = 1;

		for(cnt = 2; cnt < 10; cnt++)
		{
			for(cnt2 = 0; cnt2 < cnt; cnt2++)
			{
				if(lpDamagePlayInfo[cnt] && lpDamagePlayInfo[cnt]->lpsmSock &&
					lpDamagePlayInfo[cnt2] && lpDamagePlayInfo[cnt2]->lpsmSock &&
					lpDamagePlayInfo[cnt]->smCharInfo.JOB_CODE == lpDamagePlayInfo[cnt2]->smCharInfo.JOB_CODE)
				{
					break;
				}
			}
			if(cnt2 == cnt)
			{
				BabelHornSort[BabelHornSortCnt++] = cnt;
			}
		}


		if(rsServerConfig.Event_BabelHorn && lpChar->lpExt1)
		{
			if(BabelHornSortCnt <= 2)
			{

				for(cnt = 0; cnt < rsServerConfig.Event_BabelHorn; cnt++)
				{
					if(lpDamagePlayInfo[cnt] && lpDamagePlayInfo[cnt]->lpsmSock)
					{
						rsPutItem(lpDamagePlayInfo[cnt], (sinGF1 | sin02));
					}
				}
			}
			else
			{
				for(cnt = 0; cnt < rsServerConfig.Event_BabelHorn; cnt++)
				{
					if(cnt < BabelHornSortCnt)
					{
						cnt2 = BabelHornSort[cnt];
						if(lpDamagePlayInfo[cnt2] && lpDamagePlayInfo[cnt2]->lpsmSock)
						{
							rsPutItem(lpDamagePlayInfo[cnt2], (sinGF1 | sin02));
						}
					}
				}
			}
		}
	}

	if(lpChar->smMonsterInfo.dwEvnetItem)
	{

		if(rsCheckEventItem(lpChar->smMonsterInfo.dwEvnetItem, lprsPlayInfo, lpChar) == TRUE)
			rsPutItem(lprsPlayInfo, lpChar->smMonsterInfo.dwEvnetItem);
	}


	for(cnt = 0; cnt < lpChar->smMonsterInfo.FallItemPlusCount; cnt++)
	{

		if((rand() % 10000) < lpChar->smMonsterInfo.FallItems_Plus[cnt].Percentage)
		{
			dwCode = lpChar->smMonsterInfo.FallItems_Plus[cnt].dwItemCode;
			for(cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
			{
				if(DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem)
				{
					CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
					if(rsServerConfig.Event_Potion)
					{

						if((lpsItem->ItemInfo.CODE&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
						{
							lpsItem->ItemInfo.PotionCount = (rand() % rsServerConfig.Event_Potion) + 1;
						}
					}

					dwCode = (lpsItem->ItemInfo.CODE&sinITEM_MASK2);
					if(dwCode == sinMA2 || dwCode == sinQT1)
					{

						rsPutItem2(lprsPlayInfo, &lpsItem->ItemInfo);
						break;
					}

					dwCode = (lpsItem->ItemInfo.CODE&sinITEM_MASK2);

					if(lpChar->PartyFlag != rsHARDCORE_EVENT_FLAG || (lpsItem->ItemInfo.CODE != (sinGG1 | sin01) && (lpsItem->ItemInfo.CODE&sinITEM_MASK1) != (sinPM1&sinITEM_MASK1)))
					{
						lpsItem->state = TRUE;
						lpStgItem = ((STG_AREA *)lpChar->lpExt1)->AddItem(lpsItem, lpChar->pX >> FLOATNS, lpChar->pY >> FLOATNS, lpChar->pZ >> FLOATNS, TRUE);

						if(lpStgItem)
						{
							if(lpChar->smMonsterInfo.AllSeeItem)
							{
								((STG_AREA *)lpChar->lpExt1)->SendStgItemToNearUsers(lpStgItem);
							}
							else
							{
								if(DmgPlayUse)
								{

									for(cnt2 = 0; cnt2 < 6; cnt2++)
									{
										if(lpDamagePlayInfo[cnt2])
										{
											((STG_AREA *)lpChar->lpExt1)->SendStgItem(lpDamagePlayInfo[cnt2], lpStgItem);
										}
									}
								}
								else
									((STG_AREA *)lpChar->lpExt1)->SendStgItem(lprsPlayInfo, lpStgItem);


								lpStgItem->dwCreateTime += 5000;
							}
						}
					}
					break;
				}
			}
		}
	}



	int FallItemMax = lpChar->smMonsterInfo.FallItemMax;


	if(FallItemMax > 0)
	{
		int	FallRandom = 0;

		if(lprsPlayInfo->dwTime_PrimeItem_X2 > 0)
		{
			switch(lprsPlayInfo->dwPrimeItem_PackageCode)
			{
			case PRIME_ITEM_PACKAGE_NONE:
				FallRandom = 50;
				break;
			case PRIME_ITEM_PACKAGE_BRONZE:
				FallRandom = 20;
				break;
			case PRIME_ITEM_PACKAGE_SILVER:
				FallRandom = 30;
				break;
			case PRIME_ITEM_PACKAGE_GOLD:
				FallRandom = 40;
				break;
			case PRIME_ITEM_PACKAGE_ULTRA:
				FallRandom = 50;
				break;
			case PRIME_ITEM_PACKAGE_NONE_50_EXPUP:
				FallRandom = 50;
				break;
			case PRIME_ITEM_PACKAGE_NONE_100_EXPUP:
				FallRandom = 50;
				break;
			}

		}

		if(lprsPlayInfo->dwTime_PrimeItem_PhenixPet > 0)
		{
			FallRandom += 5;			
		}

		if(lprsPlayInfo->Bl_RNo > 0)
			FallRandom += 0;

		if(FallRandom && (rand() % 100) < FallRandom)
		{
			FallItemMax++;
		}
	}



	if(rsServerConfig.ExpGameTimeMode == 3)
	{
		int giCnt = rsGetExp_GameTime(lprsPlayInfo);
		FallItemMax = (FallItemMax*giCnt) / 100;
		if(giCnt > 0 && FallItemMax == 0)
		{
			if((rand() % 100) < giCnt) FallItemMax = 1;
		}
	}



	for(cnt = 0; cnt < FallItemMax; cnt++)
	{

		if(srGetMonsterItem(lprsPlayInfo, lpChar, lpsItem) == TRUE)
		{

			if(rsServerConfig.Event_Potion)
			{

				if((lpsItem->ItemInfo.CODE&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
				{
					lpsItem->ItemInfo.PotionCount = (rand() % rsServerConfig.Event_Potion) + 1;
				}
			}


#ifdef _LANGUAGE_CHINESE
			if(rsServerConfig.ExpGameTimeMode == 3 && lpsItem->ItemInfo.CODE == (sinGG1 | sin01))
			{
				lpsItem->ItemInfo.Money = (lpsItem->ItemInfo.Money*rsGetExp_GameTime(lprsPlayInfo)) / 100;
				if(!lpsItem->ItemInfo.Money) continue;
				ReformItem(&lpsItem->ItemInfo);
			}
#endif




			dwCode = (lpsItem->ItemInfo.CODE&sinITEM_MASK2);
			if(dwCode == sinMA2 || dwCode == sinQT1)
			{

				if(!lprsPlayInfo->smCharInfo.ChangeJob)
					rsPutItem2(lprsPlayInfo, &lpsItem->ItemInfo);
				else
				{
					if(lprsPlayInfo->smCharInfo.ChangeJob == 1 && lpsItem->ItemInfo.CODE == (sinQT1 | sin06))
					{
						rsPutItem2(lprsPlayInfo, &lpsItem->ItemInfo);
					}
				}
			}
			else
			{

				if(lpChar->PartyFlag != rsHARDCORE_EVENT_FLAG || (lpsItem->ItemInfo.CODE != (sinGG1 | sin01) && (lpsItem->ItemInfo.CODE&sinITEM_MASK1) != (sinPM1&sinITEM_MASK1)))
				{
					lpsItem->state = TRUE;
					lpStgItem = ((STG_AREA *)lpChar->lpExt1)->AddItem(lpsItem, lpChar->pX >> FLOATNS, lpChar->pY >> FLOATNS, lpChar->pZ >> FLOATNS, TRUE);


					if(lpStgItem)
					{
						if(lpChar->smMonsterInfo.AllSeeItem)
						{
							((STG_AREA *)lpChar->lpExt1)->SendStgItemToNearUsers(lpStgItem);
						}
						else
						{
							if(DmgPlayUse)
							{

								for(cnt2 = 0; cnt2 < 6; cnt2++)
								{
									if(lpDamagePlayInfo[cnt2])
									{
										((STG_AREA *)lpChar->lpExt1)->SendStgItem(lpDamagePlayInfo[cnt2], lpStgItem);
									}
								}
							}
							else
								((STG_AREA *)lpChar->lpExt1)->SendStgItem(lprsPlayInfo, lpStgItem);


							lpStgItem->dwCreateTime += 5000;
						}
					}
				}
			}
		}
	}


	if(lprsPlayInfo->BadPlayer)
	{

		cnt = lprsPlayInfo->MonsterKillCounter;
		if(cnt > 45) cnt = 45;
		cnt = (lpChar->smMonsterInfo.GetExp*cnt) / 50;
		lpChar->smMonsterInfo.GetExp -= cnt;
	}

	int	ExpBack = 0;


	if(rsServerConfig.Event_ExpUp)
	{
		ExpBack = lpChar->smMonsterInfo.GetExp;

#ifdef	_LANGUAGE_PHILIPIN
		int ExpBackup;



		if(lprsPlayInfo->smCharInfo.Level < 25) ExpBackup = 400;

		else
		{
			if(rsServerConfig.Event_ExpUp >= 100 && rsServerConfig.Event_ExpUp < 200)
				lpChar->smMonsterInfo.GetExp += (lpChar->smMonsterInfo.GetExp * 100) / 100;
			else if(rsServerConfig.Event_ExpUp >= 200 && rsServerConfig.Event_ExpUp < 300)
				lpChar->smMonsterInfo.GetExp += (lpChar->smMonsterInfo.GetExp * 200) / 100;
			else if(rsServerConfig.Event_ExpUp >= 300 && rsServerConfig.Event_ExpUp < 400)
				lpChar->smMonsterInfo.GetExp += (lpChar->smMonsterInfo.GetExp * 300) / 100;
			else if(rsServerConfig.Event_ExpUp >= 400)
				lpChar->smMonsterInfo.GetExp += (lpChar->smMonsterInfo.GetExp * 400) / 100;


			else
				lpChar->smMonsterInfo.GetExp += (lpChar->smMonsterInfo.GetExp * 100) / 100;

		}

#else
		if(rsServerConfig.Event_ExpUp >= 100 && rsServerConfig.Event_ExpUp < 200)
			lpChar->smMonsterInfo.GetExp += (lpChar->smMonsterInfo.GetExp * 100) / 100;
		else if(rsServerConfig.Event_ExpUp >= 200 && rsServerConfig.Event_ExpUp < 300)
			lpChar->smMonsterInfo.GetExp += (lpChar->smMonsterInfo.GetExp * 200) / 100;
		else if(rsServerConfig.Event_ExpUp >= 300 && rsServerConfig.Event_ExpUp < 400)
			lpChar->smMonsterInfo.GetExp += (lpChar->smMonsterInfo.GetExp * 300) / 100;
		else if(rsServerConfig.Event_ExpUp >= 400)
			lpChar->smMonsterInfo.GetExp += (lpChar->smMonsterInfo.GetExp * 400) / 100;
		else
			lpChar->smMonsterInfo.GetExp += (lpChar->smMonsterInfo.GetExp * 100) / 100;

#endif

	}

#ifdef _LANGUAGE_ARGENTINA
	if(rsServerConfig.Event_ExpUp_latin)
	{
		ExpBack = lpChar->smMonsterInfo.GetExp;

		if(lprsPlayInfo->smCharInfo.Level <= 20)
		{
			lpChar->smMonsterInfo.GetExp += (lpChar->smMonsterInfo.GetExp * 200) / 100;
		}
		else if(lprsPlayInfo->smCharInfo.Level > 20 && lprsPlayInfo->smCharInfo.Level <= 30)
		{
			lpChar->smMonsterInfo.GetExp += (lpChar->smMonsterInfo.GetExp * 100) / 100;
		}
		else if(lprsPlayInfo->smCharInfo.Level > 80 && lprsPlayInfo->smCharInfo.Level <= 90)
		{
			lpChar->smMonsterInfo.GetExp += (lpChar->smMonsterInfo.GetExp * 100) / 100;
		}
		else
		{
			lpChar->smMonsterInfo.GetExp;
		}
	}
#endif

	if(lprsPlayInfo->dwPartyInfo)
	{

		if(!lprsPlayInfo->lpPartyMaster || lprsPlayInfo->lpPartyMaster->GetPartyExp(lpChar, lprsPlayInfo) == FALSE)
		{

			lprsPlayInfo->dwPartyInfo = PARTY_STATE_NONE;
			lprsPlayInfo->lpPartyMaster = NULL;
		}
	}
	else
	{

		smTransCommand.code = OpCode::OPCODE_ADDEXP;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = srGetTotalExp(lpChar->smMonsterInfo.GetExp, lpChar->smCharInfo.Level - lprsPlayInfo->smCharInfo.Level);

		if(smTransCommand.WParam)
		{

			int ExpUp = 0;

			if(lprsPlayInfo->dwTime_PrimeItem_ExpUp > 0)
			{
				switch(lprsPlayInfo->dwPrimeItem_PackageCode)
				{
				case PRIME_ITEM_PACKAGE_NONE:					ExpUp += 30;					break;
				case PRIME_ITEM_PACKAGE_BRONZE:					ExpUp += 10;					break;
				case PRIME_ITEM_PACKAGE_SILVER:					ExpUp += 20;					break;
				case PRIME_ITEM_PACKAGE_GOLD:					ExpUp += 30;					break;
				case PRIME_ITEM_PACKAGE_ULTRA:					ExpUp += 40;					break;
				case PRIME_ITEM_PACKAGE_NONE_50_EXPUP:			ExpUp += 50;					break;
				case PRIME_ITEM_PACKAGE_NONE_100_EXPUP:			ExpUp += 100;					break;
				}
			}


			if(lprsPlayInfo->Bl_RNo > 0)
			{
				ExpUp += 20;
			}

			if(lprsPlayInfo->dwTime_PrimeItem_PhenixPet > 0)
			{
				ExpUp += 5;
			}

			if(rsServerConfig.ExpGameTimeMode)
			{
				smTransCommand.WParam = (smTransCommand.WParam * rsGetExp_GameTime(lprsPlayInfo)) / 100;
			}

			if(ExpUp)
			{
				smTransCommand.WParam += (smTransCommand.WParam*ExpUp) / 100;
			}

			smTransCommand.LParam = lpChar->dwObjectSerial;
			smTransCommand.SParam = (smTransCommand.WParam * 3 + smTransCommand.LParam * 13) * 2002;

			lprsPlayInfo->spEXP_Out += smTransCommand.WParam;
			smTransCommand.EParam = smTransCommand.SParam^lprsPlayInfo->spEXP_Out;

			lprsPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
		}
	}

	if(ExpBack)
	{
		lpChar->smMonsterInfo.GetExp = ExpBack;
	}

	lprsPlayInfo->MonsterKillCounter++;

	rsMonHuntCount++;


	return TRUE;
}


int rsOpen_MonsterItemExp(rsKILL_MONSTER_INFO *lpKillMonInfo)
{
	rsPLAYINFO *lprsPlayInfo;
	smCHAR	smChar;
	int		cnt;

	for(cnt = 0; cnt < chrMonsterCnt; cnt++)
	{
		if(chrMonInfoList[cnt].dwAutoCharCode == lpKillMonInfo->dwAutoCharCode &&
			chrMonsterList[cnt].dwCharSoundCode == lpKillMonInfo->dwCharSoundCode)
		{

			memcpy(&smChar.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));
			memcpy(&smChar.smMonsterInfo, &chrMonInfoList[cnt], sizeof(smCHAR_MONSTER_INFO));
			break;
		}
	}
	if(cnt >= chrMonsterCnt) return FALSE;

	if(lpKillMonInfo->PartyFlag == rsHARDCORE_EVENT_FLAG && lpKillMonInfo->dwParam[0] >= sinPM1)
	{


		CreatePresentItem(lpKillMonInfo->dwParam[0], &StageArea[lpKillMonInfo->Area], lpKillMonInfo->x, lpKillMonInfo->y, lpKillMonInfo->z, 3);
		return TRUE;
	}

	lprsPlayInfo = srFindUserFromSerial(lpKillMonInfo->dwUserObjectSerial);
	if(!lprsPlayInfo) return FALSE;

	smChar.pX = lpKillMonInfo->x;
	smChar.pY = lpKillMonInfo->y;
	smChar.pZ = lpKillMonInfo->z;
	smChar.dwObjectSerial = lpKillMonInfo->dwMonObjectSerial;
	smChar.PartyFlag = lpKillMonInfo->PartyFlag;
	smChar.lpExt1 = &StageArea[lpKillMonInfo->Area];
	smChar.lpExt2 = 0;
	smChar.lpExt3 = 0;
	smChar.lpExt4 = 0;

	return rsOpen_MonsterItemExp(&smChar, lprsPlayInfo);
}


int srAutoCharMain(smCHAR *lpChar)
{

#ifdef _W_SERVER

	int pX, pZ, pY;
	int rX, rZ, rY;
	int dist, dist2;
	int MinDist;
	rsPLAYINFO	*lprsPlayInfo;
	smCHAR		*lpCharTarget;
	STG_AREA	*lpStgArea;
	int	score;
	int	TragetSerachFlag = 0;
	int	MonAttackFlag;
	smTRANS_COMMAND smTransCommand;

	int cnt;

	if(lpChar->PatLoading) return TRUE;

	lpChar->Main();

	if(lpChar->MotionInfo)
	{

		if(rsServerConfig.Event_MorifSheltom && lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_NPC_MORIF && lpChar->smCharInfo.Level == 60)
		{

			rsMorifEventMessage(lpChar);
		}
		if(rsServerConfig.Event_MollyWolf && lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_NPC_MOLLYWOLF)
		{

			rsMollyWolfEventMessage(lpChar);
		}
		if(lpChar->lpLinkPlayInfo && lpChar->dwLinkObjectCode == lpChar->lpLinkPlayInfo->dwObjectSerial)
		{

			rsQuestMasterMessage(lpChar, lpChar->lpLinkPlayInfo);
		}
		if(rsServerConfig.Event_SantaGoblin && lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_HOBGOBLIN && lpChar->smCharInfo.Level == 60)
		{

			rsSantaGoblinEventMessage(lpChar);
		}

		if(rsServerConfig.Event_Chichen_Day && lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_PAPACHICK)
		{

			rsChichenDayEventMessage(lpChar);
		}

		if(lpChar->MotionInfo->State == CHRMOTION_STATE_DEAD)
		{

			if(lpChar->lpAttackDamageList)
			{


				if(lpChar->smCharInfo.dwCharSoundCode != snCHAR_SOUND_CASTLE_TOWER_B)
				{

					SelectDamageTop10(lpChar, &rsUserListDamageTop10);
				}

				delete lpChar->lpAttackDamageList;
				lpChar->lpAttackDamageList = 0;
			}


			if(lpChar->lpExt2 && lpChar->FrameCounter > 128 && !lpChar->lpMasterPlayInfo)
			{
				lprsPlayInfo = (rsPLAYINFO *)lpChar->lpExt2;
				lpChar->lpExt2 = 0;

				if(lpChar->lpExpAttackPlayInfo && lpChar->lpExpAttackPlayInfo != lprsPlayInfo)
				{

					if(lpChar->ExpAttackLife >= ((lpChar->smCharInfo.Life[1] * 40) / 100))
					{
						lprsPlayInfo = lpChar->lpExpAttackPlayInfo;
					}
				}

				if(lpChar->smMonsterInfo.dwEvnetItem)
				{


					if(lpChar->smMonsterInfo.EventCode)
						rsReOpenEventMonster((STG_AREA *)lpChar->lpExt1, lpChar);
				}

				if(lprsPlayInfo->lpsmSock && lprsPlayInfo->dwObjectSerial)
				{



					if(rsPushKillMonster(lpChar, lprsPlayInfo, ((STG_AREA *)lpChar->lpExt1)) == FALSE)
					{
						rsOpen_MonsterItemExp(lpChar, lprsPlayInfo);
					}
					else
					{
						lprsPlayInfo->MonsterKillCounter++;
					}



					if(lprsPlayInfo->EventMode == rsHARDCORE_EVENT_FLAG && lpChar->PartyFlag == rsHARDCORE_EVENT_FLAG && rsHardCoreEvent_Count)
					{
						if(!lpChar->lpExt3)
						{

							if(rsServerConfig.TestSeverMode)
								score = (lpChar->smMonsterInfo.GetExp >> 2) / rsSOD_ScoreDiv;
							else
								score = lpChar->smMonsterInfo.GetExp / rsSOD_ScoreDiv;

							if(lpChar->smCharInfo.wPlayClass[0] == MONSTER_CLASS_BOSS)
							{
								score *= rsHardCoreEvent_Count * 2;


								rsShowHardCoreEventScore2(lprsPlayInfo, lpChar, score);
							}

							lprsPlayInfo->EventScore += score;
							lprsPlayInfo->EventCount++;
							if(lprsPlayInfo->sEventParam[0] >= 0 && lprsPlayInfo->sEventParam[0] < 4)
								rsSodTeamScore[lprsPlayInfo->sEventParam[0]] += score;

							rsShowHardCoreEventScore(lprsPlayInfo);

							rsOpen_SodItem(lpChar, lprsPlayInfo);
						}
					}

					if((lprsPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level) < 20)
					{
						lprsPlayInfo->dwMacroTime = dwPlayServTime;
					}

				}

				rsEventSpawn_KillMonster(lprsPlayInfo, lpChar);

			}

			if(lpChar->FrameCounter > 400)
			{
				if(lpChar->lpMasterPlayInfo && lpChar->HoSkillCode && lpChar->lpMasterPlayInfo->lpsmSock)
				{

					smTransCommand.code = OpCode::OPCODE_CANCEL_SKILL;
					smTransCommand.size = sizeof(smTRANS_COMMAND);
					smTransCommand.WParam = lpChar->HoSkillCode;
					smTransCommand.LParam = lpChar->dwObjectSerial;
					smTransCommand.SParam = 0;
					smTransCommand.EParam = 0;
					lpChar->lpMasterPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
				}

				lpChar->Close();
				((STG_AREA *)lpChar->lpExt1)->MonsterCount--;
				((STG_AREA *)lpChar->lpExt1)->DeleteMonTable(lpChar);
				return TRUE;
			}
		}

		if(lpChar->MotionInfo->State == CHRMOTION_STATE_WARP &&
			lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_HUNGKY && lpChar->FrameCounter > 60)
		{

			for(cnt = 0; cnt < chrMonsterCnt; cnt++)
			{

				if(chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_HULK && chrMonsterList[cnt].szName[0] != ' ')
				{
					if(lpChar->AttackAnger <= 80)
					{
						if(chrMonsterList[cnt].Level < 80)
						{

							rsCharChanger(lpChar, &chrMonsterList[cnt], &chrMonInfoList[cnt]);
							break;
						}
					}
					else
					{
						if(chrMonsterList[cnt].Level >= 80)
						{

							rsCharChanger(lpChar, &chrMonsterList[cnt], &chrMonInfoList[cnt]);
							break;
						}
					}
				}
			}
		}


		if(lpChar->MotionInfo->State == CHRMOTION_STATE_WARP &&
			lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_DEADHOPT && lpChar->FrameCounter > 60)
		{
			for(cnt = 0; cnt < chrMonsterCnt; cnt++)
			{
				if(chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_DEADKINGHOPY && chrMonsterList[cnt].szName[0] != ' ')
				{
					if(lpChar->AttackAnger <= 80)
					{
						if(chrMonsterList[cnt].Level >= 108)
						{
							rsCharChanger(lpChar, &chrMonsterList[cnt], &chrMonInfoList[cnt]);
							break;
						}
					}
					else
					{
						if(chrMonsterList[cnt].Level >= 108)
						{
							rsCharChanger(lpChar, &chrMonsterList[cnt], &chrMonInfoList[cnt]);
							break;
						}
					}
				}
			}
		}


		if(lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_BEBECHICK)
		{
			int Event_tempLife = 0;
			Event_tempLife = (lpChar->smCharInfo.Life[0] * 100) / lpChar->smCharInfo.Life[1];
			if(Event_tempLife < 20)
			{
				for(cnt = 0; cnt < chrMonsterCnt; cnt++)
				{
					if(chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_PAPACHICK && chrMonsterList[cnt].szName[0] != ' ')
					{
						rsCharChanger(lpChar, &chrMonsterList[cnt], &chrMonInfoList[cnt]);
						break;
					}
				}
			}
		}
	}



	if(lpChar->AttackUserFlag)
	{

		lpChar->AttackUserFlag = 0;
		if(lpChar->lpTargetPlayInfo)
			lpChar->lpTargetPlayInfo->HitMonsterCount = 0;

	}

	if(lpChar->smCharInfo.Life[0] < 0) lpChar->smCharInfo.Life[0] = 0;
	if(lpChar->smCharInfo.Life[0] > lpChar->smCharInfo.Life[1]) lpChar->smCharInfo.Life[0] = lpChar->smCharInfo.Life[1];

	lpChar->ReopenCount = REOPEN_COUNT_NUM;

	if((srAutoPlayCount & 0x3F) == 0)
	{
		lpChar->MakeTransPlayData(lpChar->srTransBuff, 0x10, 4);

		pX = lpChar->pX;
		pY = lpChar->pY;
		pZ = lpChar->pZ;

		MinDist = DIST_TRANSLEVEL_LOW;

		lpStgArea = ((STG_AREA *)lpChar->lpExt1);

		if(lpStgArea && lpChar->lpMasterPlayInfo)
		{
			lpCharTarget = 0;

			for(cnt = 0; cnt < lpStgArea->MonsterLastPoint; cnt++)
			{
				if(lpStgArea->lpCharMonster[cnt] && lpStgArea->lpCharMonster[cnt] != lpChar &&
					lpStgArea->lpCharMonster[cnt]->smCharInfo.Life[0] > 0)
				{


					if(lpChar->HoSkillCode && !lpChar->HoSkillMode && lpChar->lpMasterPlayInfo && lpChar->lpMasterPlayInfo->lpChrTarget != lpStgArea->lpCharMonster[cnt])
						continue;

					MonAttackFlag = 1;


					if(lpChar->smCharInfo.ClassClan && lpChar->smCharInfo.ClassClan == lpStgArea->lpCharMonster[cnt]->smCharInfo.ClassClan)
						MonAttackFlag = 0;



					if(lpChar->HoSkillCode && lpChar->Clan_CastleMasterFlag && lpStgArea->lpCharMonster[cnt]->Clan_CastleMasterFlag)
					{
						if(lpStgArea->lpCharMonster[cnt]->HoSkillCode)
							MonAttackFlag = 0;
						else if(lpStgArea->lpCharMonster[cnt]->dwLinkObjectCode && lpStgArea->lpCharMonster[cnt]->dwLinkObjectCode != lpChar->lpMasterPlayInfo->dwObjectSerial)
							MonAttackFlag = 0;
					}


					if(lpChar->Clan_CastleMasterFlag && lpStgArea->lpCharMonster[cnt]->Clan_CastleMasterFlag)
						MonAttackFlag = 0;



					if(lpChar == lpStgArea->lpCharMonster[cnt]->lpLinkChar || lpChar->lpLinkChar == lpStgArea->lpCharMonster[cnt])
						MonAttackFlag = 0;

					if(MonAttackFlag)
					{

						rX = (pX - lpStgArea->lpCharMonster[cnt]->pX) >> FLOATNS;
						rY = (pY - lpStgArea->lpCharMonster[cnt]->pY) >> FLOATNS;
						rZ = (pZ - lpStgArea->lpCharMonster[cnt]->pZ) >> FLOATNS;

						dist = rX*rX + rZ*rZ + rY*rY;

						if(dist < DIST_TRANSLEVEL_CONNECT && abs(rX) < TRANS_VIEW_LIMIT && abs(rZ) < TRANS_VIEW_LIMIT)
						{

							if(dist < MinDist && abs(rY) < 140)
							{
								MinDist = dist;

								if(dist < lpChar->smCharInfo.Sight)
								{
									lpCharTarget = lpStgArea->lpCharMonster[cnt];


								}
							}
						}
					}
				}
			}

			lpChar->lpTargetChar = lpCharTarget;

			if(lpCharTarget)
			{
				lpChar->SetNextTarget(
					lpCharTarget->pX,
					lpCharTarget->pY,
					lpCharTarget->pZ);
			}

			if(lpChar->dwUpdateCharInfoTime && lpChar->dwUpdateCharInfoTime < dwPlayServTime && lpChar->smCharInfo.Life[0]>0)
			{

				lpChar->smCharInfo.Life[0] = 0;
				lpChar->SetMotionFromCode(CHRMOTION_STATE_DEAD);
			}

		}
		else
		{

			TragetSerachFlag = FALSE;

			if(lpChar->dwCompulsionTime)
			{

				if(lpChar->dwCompulsionTime > dwPlayServTime && lpChar->lpCompulsionPlayInfo && lpChar->lpCompulsionPlayInfo->lpsmSock)
				{
					lpChar->lpTargetPlayInfo = lpChar->lpCompulsionPlayInfo;

					lpChar->SetNextTarget(
						lpChar->lpTargetPlayInfo->Position.x,
						lpChar->lpTargetPlayInfo->Position.y,
						lpChar->lpTargetPlayInfo->Position.z);

					TragetSerachFlag = TRUE;
				}
				else
				{
					lpChar->dwCompulsionTime = 0;
					lpChar->lpCompulsionPlayInfo = 0;
				}
			}

			if(!TragetSerachFlag)
			{
				if(!lpChar->lpTargetChar)
				{
					lprsPlayInfo = 0;
					for(cnt = 0; cnt < CONNECTMAX; cnt++)
					{
						if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial && rsPlayInfo[cnt].smCharInfo.Life[0] &&
							rsPlayInfo[cnt].smCharInfo.State != smCHAR_STATE_ENEMY)
						{


							if(lpChar->dwLinkObjectCode && lpChar->dwLinkObjectCode != rsPlayInfo[cnt].dwObjectSerial) continue;
							if(lpChar->dwClanCode && lpChar->dwClanCode == rsPlayInfo[cnt].dwClanCode) continue;

							rX = (pX - rsPlayInfo[cnt].Position.x) >> FLOATNS;
							rY = (pY - rsPlayInfo[cnt].Position.y) >> FLOATNS;
							rZ = (pZ - rsPlayInfo[cnt].Position.z) >> FLOATNS;

							dist = rX*rX + rZ*rZ + rY*rY;

							if(dist < DIST_TRANSLEVEL_CONNECT && abs(rX) < TRANS_VIEW_LIMIT && abs(rZ) < TRANS_VIEW_LIMIT)
							{

								if(lpChar->AttackSkillRange && abs(rY) < 140)
								{
									if(lpChar->smMonsterInfo.SkillDistance && lpChar->smMonsterInfo.SkillRangeRect.left && lpChar->smMonsterInfo.SkillRangeRect.right)
									{
										if(rsPlayInfo[cnt].Position.x > lpChar->smMonsterInfo.SkillRangeRect.left &&
											rsPlayInfo[cnt].Position.x<lpChar->smMonsterInfo.SkillRangeRect.right &&
											rsPlayInfo[cnt].Position.z>lpChar->smMonsterInfo.SkillRangeRect.top &&
											rsPlayInfo[cnt].Position.z < lpChar->smMonsterInfo.SkillRangeRect.bottom)
										{

											rsSendTransSkillAttack(lpChar, &rsPlayInfo[cnt]);
										}
									}
									else
									{
										if(dist < lpChar->AttackSkillRange)
										{

											rsSendTransSkillAttack(lpChar, &rsPlayInfo[cnt]);
										}
									}
								}

								if(dist < MinDist && abs(rY) < 140)
								{

									dist2 = lpChar->smCharInfo.Sight;


									if(rsPlayInfo[cnt].dwSkill_Vanish_Time)
									{
										if(rsPlayInfo[cnt].dwSkill_Vanish_Time < dwPlayServTime)
										{

											rsPlayInfo[cnt].dwSkill_Vanish_Time = 0;
											rsPlayInfo[cnt].dwSkill_Vanish_Param = 0;
										}
										else
										{

											if(lpChar->smCharInfo.dwCharSoundCode != snCHAR_SOUND_BABEL &&
												lpChar->smCharInfo.dwCharSoundCode != snCHAR_SOUND_DEATHKNIGHT &&
												lpChar->smCharInfo.dwCharSoundCode != snCHAR_SOUND_KELVEZU &&
												lpChar->smCharInfo.dwCharSoundCode != snCHAR_SOUND_MOKOVA)
											{
												dist2 = (lpChar->smMonsterInfo.Real_Sight*Vanish_Range[rsPlayInfo[cnt].dwSkill_Vanish_Param]) / 100;
												dist2 = lpChar->smMonsterInfo.Real_Sight + dist2;
												if(dist2 > 0) dist2 *= dist2;
												else dist2 = 0;
											}
										}
									}


									if(dist < dist2 && !rsPlayInfo[cnt].HideMode)
									{


										if(lpChar->PartyFlag == rsHARDCORE_EVENT_FLAG)
										{
											if(rsPlayInfo[cnt].EventMode == rsHARDCORE_EVENT_FLAG)
												lprsPlayInfo = &rsPlayInfo[cnt];
										}
										else
											lprsPlayInfo = &rsPlayInfo[cnt];

										MinDist = dist;
									}
								}
							}
						}
					}

					if(lpChar->PlayStunCount) lprsPlayInfo = 0;
					if(lpChar->AttackSkillRange) lpChar->AttackSkillRange = 0;

					if(!lpChar->dwTargetLockTime)
					{
						lpChar->lpTargetPlayInfo = lprsPlayInfo;

						if(lprsPlayInfo)
						{
							lpChar->SetNextTarget(
								lprsPlayInfo->Position.x,
								lprsPlayInfo->Position.y,
								lprsPlayInfo->Position.z);
						}
					}
					else
					{
						if(lpChar->dwTargetLockTime < dwPlayServTime)
							lpChar->dwTargetLockTime = 0;
					}
				}
				else
				{
					lpChar->SetNextTarget(lpChar->lpTargetChar->pX, lpChar->lpTargetChar->pY, lpChar->lpTargetChar->pZ);
				}
			}
		}


		if(lpChar->nCheckChar == 100)
		{
			if(lpChar->dwUpdateCharInfoTime && lpChar->dwUpdateCharInfoTime < dwPlayServTime && lpChar->smCharInfo.Life[0]>0)
			{

				lpChar->smCharInfo.Life[0] = 0;
				lpChar->SetMotionFromCode(CHRMOTION_STATE_DEAD);
			}
		}



		if(lpChar->ActionPattern == 5 && lpChar->dwLastTransTime && (lpChar->dwLastTransTime + 5 * 60 * 1000) < dwPlayServTime && !lpChar->dwUpdateCharInfoTime)
		{

			lpChar->Close();
			((STG_AREA *)lpChar->lpExt1)->MonsterCount--;
			((STG_AREA *)lpChar->lpExt1)->DeleteMonTable(lpChar);
		}
	}
#endif
	return TRUE;

}


smCHAR *Serv_CheckOtherPlayPosi(int x, int y, int z)
{
	int cnt;
	int dist;
	int dx, dz;
	smCHAR *lpChar;
	STG_AREA	*lpStgArea_AutoPlayer;


	lpStgArea_AutoPlayer = (STG_AREA *)lpActiveChar->lpExt1;

	if(!lpStgArea_AutoPlayer) 	return NULL;

	for(cnt = 0; cnt < lpStgArea_AutoPlayer->MonsterLastPoint; cnt++)
	{
		lpChar = lpStgArea_AutoPlayer->lpCharMonster[cnt];

		if(lpChar && lpActiveChar != lpChar && lpChar->smCharInfo.Life[0] > 0)
		{
			if((y - 32 * fONE) < lpChar->pY && (y + 32 * fONE) > lpChar->pY)
			{

				dx = (lpChar->pX - x) >> FLOATNS;
				dz = (lpChar->pZ - z) >> FLOATNS;
				dist = dx*dx + dz*dz;
				if(dist < (32 * 32)) return lpChar;
			}
		}
	}

	return NULL;
}


int srAutoPlayMain()
{
	int cnt, ChrCnt;

	dwPlayTime = GetCurrentTime();


	if((srAutoPlayCount & 3) == 0)
	{
		ActivePlayCounter = 0;

		for(ChrCnt = 0; ChrCnt < AUTOPLAYER_MAX; ChrCnt++)
		{
			if(chrAutoPlayer[ChrCnt].Flag)
			{
				lpActiveChar = &chrAutoPlayer[ChrCnt];
				if(chrAutoPlayer[ChrCnt].NearPlayCount || chrAutoPlayer[ChrCnt].MotionInfo->State == CHRMOTION_STATE_DEAD ||
					chrAutoPlayer[ChrCnt].smMonsterInfo.EventCode)
				{

					srAutoCharMain(&chrAutoPlayer[ChrCnt]);
					chrAutoPlayer[ChrCnt].NearPlayCount--;
				}
				else
				{
					if(lpActiveChar->smCharInfo.State == smCHAR_STATE_ENEMY && !lpActiveChar->smMonsterInfo.EventCode)
					{
						lpActiveChar->ReopenCount--;
						if(lpActiveChar->ReopenCount <= 0)
						{

							lpActiveChar->Close();
							((STG_AREA *)lpActiveChar->lpExt1)->MonsterCount--;
							((STG_AREA *)lpActiveChar->lpExt1)->DeleteMonTable(lpActiveChar);
						}
					}
				}
				ActivePlayCounter++;
			}
		}
	}



	srAutoPlayCount++;
	if((srAutoPlayCount & 0x3F) == 0)
	{
		rsAutoPlayTransCount++;
	}

	for(cnt = 0; cnt < STAGE_AREA_MAX; cnt++)
	{
		if(StageArea[cnt].lpStage)
		{
			StageArea[cnt].Main();
		}
	}

	if((srAutoPlayCount & 0x3FF) == 0)
	{
		dwServ_GameTimeHour = GetGameTimeHour();

		if(dwServ_GameTimeHour >= GAME_HOUR_DAY && dwServ_GameTimeHour < GAME_HOUR_DARKNESS)
			dwServ_NightDay = FALSE;
		else
			dwServ_NightDay = TRUE;
	}

	return TRUE;
}


int srTransPlayData(rsPLAYINFO *lpPlayInfo)
{

	char TransBuff[TRANS_BUFF_SIZE];
	char *lpTransBuff;
	smPLAYDATA_GROUP *lpPlayDataGroup;
	int cnt;
	smPLAYDATA	*lpPlayData;
	int dist;
	int size;
	int x, z;
	int PlayDataCnt;
	smCHAR *lpChar;
	int	TransDataCount;
	int	TransOver;
	int	ClipCnt;
	int SndFlag;
	smTRANS_COMMAND	*lpTransCommand;
	smTRANS_COMMAND_EX	*lpTransCommandEx;
	int SoloMode = 0;


	lpPlayDataGroup = (smPLAYDATA_GROUP *)TransBuff;
	lpTransBuff = TransBuff + sizeof(smPLAYDATA_GROUP);

	lpPlayDataGroup->code = OpCode::OPCODE_PLAYDATAGROUP;

	lpPlayDataGroup->dwSendCode = 0x80000000 + (lpPlayInfo->SendPlayGroupCount & 0x00FFFFFF);

	PlayDataCnt = 0;
	TransDataCount = 0;
	SndFlag = 0;

	TransOver = lpPlayInfo->LastTransAutoPlayCount + AUTOPLAYER_MAX;

	//if(lpPlayInfo->Position.Area == QUEST_ARENA_FIELD && lpPlayInfo->getSecurity() <= AccountTypes::SEC_GAMEMASTER)
		//SoloMode = FALSE;

	if(lpPlayInfo->lpChrTarget)
	{

		lpChar = lpPlayInfo->lpChrTarget;
		if(lpChar->Flag && lpChar->dwObjectSerial == lpPlayInfo->dwTarObjSerial &&
			lpChar->srTransBuffSize)
		{
			x = (lpChar->pX - lpPlayInfo->Position.x) >> FLOATNS;
			z = (lpChar->pZ - lpPlayInfo->Position.z) >> FLOATNS;
			dist = x*x + z*z;

			if(dist < DIST_TRANSLEVEL_HIGH && abs(x) < TRANS_VIEW_LIMIT && abs(z) < TRANS_VIEW_LIMIT)
			{

				size = ((smTRANS_PLAYDATA *)lpChar->srTransBuff)->size;
				memcpy(lpTransBuff, lpChar->srTransBuff, size);
				lpTransBuff += size;
				TransDataCount += 3;
				PlayDataCnt++;
				lpChar->NearPlayCount = 256;
			}
			else
			{
				lpPlayInfo->lpChrTarget = 0;
			}
		}
		else
		{
			lpPlayInfo->lpChrTarget = 0;
		}
	}

	for(cnt = lpPlayInfo->LastTransAutoPlayCount; cnt < TransOver; cnt++)
	{
		ClipCnt = cnt&AUTOPLAYER_MASK;

		if(SoloMode && chrAutoPlayer[ClipCnt].dwLinkObjectCode != lpPlayInfo->dwObjectSerial)
		{
			if(chrAutoPlayer[ClipCnt].smCharInfo.Brood != smCHAR_MONSTER_USER || chrAutoPlayer[ClipCnt].lpMasterPlayInfo != lpPlayInfo)
				continue;
		}

		if(chrAutoPlayer[ClipCnt].Flag && chrAutoPlayer[ClipCnt].srTransBuffSize)
		{
			lpChar = &chrAutoPlayer[ClipCnt];
			x = (lpChar->pX - lpPlayInfo->Position.x) >> FLOATNS;
			z = (lpChar->pZ - lpPlayInfo->Position.z) >> FLOATNS;
			dist = x*x + z*z;


			if(dist < DIST_TRANSLEVEL_CONNECT && lpPlayInfo->lpChrTarget != lpChar &&
				abs(x) < TRANS_VIEW_LIMIT && abs(z) < TRANS_VIEW_LIMIT)
			{
				size = ((smTRANS_PLAYDATA *)lpChar->srTransBuff)->size;


				if((lpTransBuff - TransBuff + size) >= (TRANS_BUFF_SIZE - sizeof(smTRANS_COMMAND)))
				{
					lpPlayDataGroup->size = (lpTransBuff - TransBuff);
					lpPlayDataGroup->PlayDataCnt = PlayDataCnt;
					lpPlayInfo->lpsmSock->Send((char *)lpPlayDataGroup, lpPlayDataGroup->size, TRUE);

					PlayDataCnt = 0;
					lpTransBuff = TransBuff + sizeof(smPLAYDATA_GROUP);
					SndFlag++;
					break;
				}

				if(lpPlayInfo->Position.Area == rsCASTLE_FIELD && chrAutoPlayer[ClipCnt].DontMoveFlag)
				{

					if(chrAutoPlayer[ClipCnt].smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_TOWER_B ||
						chrAutoPlayer[ClipCnt].smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_DOOR)
					{
						dist = DIST_TRANSLEVEL_HIGH - 1;
					}
				}

				if(dist < DIST_TRANSLEVEL_HIGH)
				{

					memcpy(lpTransBuff, lpChar->srTransBuff, size);
					lpTransBuff += size;
					TransDataCount += 3;
					PlayDataCnt++;
					lpChar->NearPlayCount = 256;
					if(TransDataCount >= TRANS_MAX_CHAR_LIMIT) break;
				}
				else
				{
					if(lpChar->MotionInfo->State != CHRMOTION_STATE_DEAD)
					{

						lpPlayData = (smPLAYDATA *)lpTransBuff;

						lpPlayData->size = sizeof(smPLAYDATA);
						lpPlayData->code = OpCode::OPCODE_PLAYDATA1;
						lpPlayData->x = lpChar->pX;
						lpPlayData->y = lpChar->pY;
						lpPlayData->z = lpChar->pZ;

						lpPlayData->angle[0] = lpChar->Angle.x;
						lpPlayData->angle[1] = lpChar->Angle.y;
						lpPlayData->angle[2] = lpChar->Angle.z;
						lpPlayData->angle[3] = (short)lpChar->MotionInfo->State;
						lpPlayData->frame = lpChar->frame;
						lpPlayData->dwObjectSerial = lpChar->dwObjectSerial;
						lpPlayData->dwAutoCharCode = lpChar->smMonsterInfo.dwAutoCharCode;

						lpTransBuff += sizeof(smPLAYDATA);

						TransDataCount++;
						PlayDataCnt++;
						lpChar->NearPlayCount = 256;
						if(TransDataCount >= TRANS_MAX_CHAR_LIMIT) break;
					}
				}
			}
		}
	}


	if(lpPlayInfo->Position.Area == BabelPlayField && dwBabelPlayTime > dwPlayServTime)
	{
		lpTransCommand = (smTRANS_COMMAND *)lpTransBuff;
		lpTransCommand->code = OpCode::OPCODE_PLAY_COMMAND;
		lpTransCommand->size = sizeof(smTRANS_COMMAND);
		lpTransCommand->WParam = lpPlayInfo->dwObjectSerial;
		lpTransCommand->LParam = smCOMMAND_PLAY_BABEL;
		lpTransCommand->SParam = BabelPlayField;
		lpTransCommand->EParam = 0;
		lpTransBuff += sizeof(smTRANS_COMMAND);
	}


	if(lpPlayInfo->Position.Area == rsCASTLE_FIELD && StageArea[rsCASTLE_FIELD].dwActiveMode)
	{

		lpTransCommandEx = (smTRANS_COMMAND_EX *)lpTransBuff;
		lpTransCommandEx->code = OpCode::OPCODE_PLAY_COMMAND;
		lpTransCommandEx->size = sizeof(smTRANS_COMMAND_EX);
		lpTransCommandEx->WParam = lpPlayInfo->dwObjectSerial;
		lpTransCommandEx->LParam = smCOMMAND_PLAY_BELSS_CASTLE;
		lpTransCommandEx->SParam = (rsBlessCastle.CastleMode << 16) | ((rsBlessCastle.DefenceLevel) & 0xFFFF);
		lpTransCommandEx->EParam = rsBlessCastle.dwMasterClan;
		lpTransCommandEx->WxParam = ((int *)rsBlessCastle.TimeSec)[0];
		lpTransCommandEx->LxParam = ((int *)rsBlessCastle.bCrystalSolderCount)[0];
		lpTransCommandEx->SxParam = ((int *)lpPlayInfo->sBlessCastle_Damage)[0];
		lpTransCommandEx->ExParam = 0;
		lpTransBuff += sizeof(smTRANS_COMMAND_EX);

		((int *)lpPlayInfo->sBlessCastle_Damage)[0] = 0;
	}




	if (rsServerConfig.Enable_PKField_All)
	{
		if (rsServerConfig.Enable_PKField >= 0 && StageArea[lpPlayInfo->Position.Area].dwActiveMode && lpPlayInfo->Position.Area != 3 && lpPlayInfo->Position.Area != 21)
		{

			if (lpPlayInfo->Position.Area >= 11 && lpPlayInfo->Position.Area <= 34)
			{
				lpTransCommand = (smTRANS_COMMAND*)lpTransBuff;
				lpTransCommand->code = OpCode::OPCODE_PLAY_COMMAND;
				lpTransCommand->size = sizeof(smTRANS_COMMAND);
				lpTransCommand->WParam = lpPlayInfo->dwObjectSerial;
				lpTransCommand->LParam = smCOMMAND_PLAY_PK_FIELD;
				lpTransCommand->SParam = lpPlayInfo->Position.Area;
				lpTransCommand->EParam = 0;
				lpTransBuff += sizeof(smTRANS_COMMAND);
			}
		}
	}
	else
	{
		if (lpPlayInfo->Position.Area == rsServerConfig.Enable_PKField && rsServerConfig.Enable_PKField >= 0 && StageArea[rsServerConfig.Enable_PKField].dwActiveMode)
		{
			lpTransCommand = (smTRANS_COMMAND*)lpTransBuff;
			lpTransCommand->code = OpCode::OPCODE_PLAY_COMMAND;
			lpTransCommand->size = sizeof(smTRANS_COMMAND);
			lpTransCommand->WParam = lpPlayInfo->dwObjectSerial;
			lpTransCommand->LParam = smCOMMAND_PLAY_PK_FIELD;
			lpTransCommand->SParam = rsServerConfig.Enable_PKField;
			lpTransCommand->EParam = 0;
			lpTransBuff += sizeof(smTRANS_COMMAND);
		}
		if (lpPlayInfo->Position.Area == rsServerConfig.Enable_PKField1 && rsServerConfig.Enable_PKField1 >= 0 && StageArea[rsServerConfig.Enable_PKField1].dwActiveMode)
		{
			lpTransCommand = (smTRANS_COMMAND*)lpTransBuff;
			lpTransCommand->code = OpCode::OPCODE_PLAY_COMMAND;
			lpTransCommand->size = sizeof(smTRANS_COMMAND);
			lpTransCommand->WParam = lpPlayInfo->dwObjectSerial;
			lpTransCommand->LParam = smCOMMAND_PLAY_PK_FIELD;
			lpTransCommand->SParam = rsServerConfig.Enable_PKField1;
			lpTransCommand->EParam = 0;
			lpTransBuff += sizeof(smTRANS_COMMAND);
		}
		if (lpPlayInfo->Position.Area == rsServerConfig.Enable_PKField2 && rsServerConfig.Enable_PKField2 >= 0 && StageArea[rsServerConfig.Enable_PKField2].dwActiveMode)
		{
			lpTransCommand = (smTRANS_COMMAND*)lpTransBuff;
			lpTransCommand->code = OpCode::OPCODE_PLAY_COMMAND;
			lpTransCommand->size = sizeof(smTRANS_COMMAND);
			lpTransCommand->WParam = lpPlayInfo->dwObjectSerial;
			lpTransCommand->LParam = smCOMMAND_PLAY_PK_FIELD;
			lpTransCommand->SParam = rsServerConfig.Enable_PKField2;
			lpTransCommand->EParam = 0;
			lpTransBuff += sizeof(smTRANS_COMMAND);
		}
		if (lpPlayInfo->Position.Area == rsServerConfig.Enable_PKField3 && rsServerConfig.Enable_PKField3 >= 0 && StageArea[rsServerConfig.Enable_PKField3].dwActiveMode)
		{
			lpTransCommand = (smTRANS_COMMAND*)lpTransBuff;
			lpTransCommand->code = OpCode::OPCODE_PLAY_COMMAND;
			lpTransCommand->size = sizeof(smTRANS_COMMAND);
			lpTransCommand->WParam = lpPlayInfo->dwObjectSerial;
			lpTransCommand->LParam = smCOMMAND_PLAY_PK_FIELD;
			lpTransCommand->SParam = rsServerConfig.Enable_PKField3;
			lpTransCommand->EParam = 0;
			lpTransBuff += sizeof(smTRANS_COMMAND);
		}
	}


	if(SndFlag == 0)
	{
		lpPlayDataGroup->size = (lpTransBuff - TransBuff);
		lpPlayDataGroup->PlayDataCnt = PlayDataCnt;
		lpPlayInfo->lpsmSock->Send((char *)lpPlayDataGroup, lpPlayDataGroup->size, TRUE);
	}

	ClipCnt = cnt&AUTOPLAYER_MASK;
	lpPlayInfo->LastTransAutoPlayCount = ClipCnt;
	lpPlayInfo->SendPlayGroupCount++;

	if((lpPlayInfo->SendPlayGroupCount & 0x1F) == 0)
	{
		if(rsServerConfig.Event_HardCore)
		{

			if(rsCheckHardCoreEventArea(lpPlayInfo->Position.x, lpPlayInfo->Position.y, lpPlayInfo->Position.z) == TRUE)
			{

				if(lpPlayInfo->EventMode != rsHARDCORE_EVENT_FLAG)
				{

					lpPlayInfo->AreaOutCount++;




					if(lpPlayInfo->AreaOutCount == 10)
					{

						smTRANS_COMMAND	smTransCommand;
						smTransCommand.size = sizeof(smTRANS_COMMAND);
						smTransCommand.code = OpCode::OPCODE_SET_BLACKLIST;
						smTransCommand.WParam = 1840;
						smTransCommand.SParam = lpPlayInfo->smCharInfo.Level;
						smTransCommand.LParam = 9100;
						rsSendDataServer(lpPlayInfo->lpsmSock, &smTransCommand);
						lpPlayInfo->AreaOutCount = 0;
					}
				}
			}


		}

	}

	return TRUE;
}


#define TRANS_MAX_USER_LIMIT_OVER		(TRANS_MAX_USER_LIMIT*4)


int rsConnectViewDist = DIST_TRANSLEVEL_CONNECT;


int srTransPlayUserData(rsPLAYINFO *lpPlayInfo)
{

	char TransBuff[TRANS_BUFF_SIZE];
	char *lpTransBuff;
	smPLAYDATA_GROUP *lpPlayDataGroup;
	int cnt;
	smPLAYDATA	*lpPlayData;
	int dist;
	int size;
	int x, z;
	int PlayDataCnt;
	int TransDataCount;
	int	sbCnt;

	rsPLAYINFO *lpPlayInfo2;
	TRANS_CHATMESSAGE	TransChatMessage;
	int	TransOver;
	int	ClipCnt;
	int SndFlag;
	int	ddist;
	DWORD	dwSendFrame;
	DWORD	dwRecvFrame;

	int sLen;
	int SoloMode = 0;

	lpPlayDataGroup = (smPLAYDATA_GROUP *)TransBuff;
	lpTransBuff = TransBuff + sizeof(smPLAYDATA_GROUP);

	lpPlayDataGroup->code = OpCode::OPCODE_PLAYDATAGROUP;

	lpPlayDataGroup->dwSendCode = lpPlayInfo->SendPlayGroupCount & 0x00FFFFFF;

	PlayDataCnt = 0;
	TransDataCount = 0;
	SndFlag = 0;

	
	if(lpPlayInfo->dwPartyInfo == PARTY_STATE_MASTER && lpPlayInfo->PartyUpdateFlag)
	{

		lpPlayInfo->UpdatePartyPlayInfo();
	}

	//if(lpPlayInfo->Position.Area == QUEST_ARENA_FIELD) SoloMode = FALSE;

	if(lpPlayInfo->szChatMessage[0])
	{
		sLen = lstrlen(lpPlayInfo->szChatMessage) + 1;
		TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
		TransChatMessage.size = 32 + lstrlen(lpPlayInfo->szChatMessage);
		TransChatMessage.dwObjectSerial = lpPlayInfo->dwObjectSerial;
		memcpy(TransChatMessage.szMessage, lpPlayInfo->szChatMessage, sLen);

		if(lpPlayInfo->ChatMsgMode)
		{
			TransChatMessage.dwIP = lpPlayInfo->ChatMsgMode;
			lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
			ddist = DIST_TRANSLEVEL_LOW;
		}
		else
		{
			TransChatMessage.dwIP = lpPlayInfo->lpsmSock->acc_sin.sin_addr.S_un.S_addr;
			ddist = DIST_TRANSLEVEL_HIGH;
		}

		for(cnt = 0; cnt < CONNECTMAX; cnt++)
		{
			if(rsPlayInfo[cnt].lpsmSock && &rsPlayInfo[cnt] != lpPlayInfo && rsPlayInfo[cnt].TransInfoFlag &&
				(!SoloMode || rsPlayInfo[cnt].getSecurity() >= AccountTypes::SEC_ADMINISTRATOR))
			{



				lpPlayInfo2 = &rsPlayInfo[cnt];

				x = (lpPlayInfo2->Position.x - lpPlayInfo->Position.x) >> FLOATNS;
				z = (lpPlayInfo2->Position.z - lpPlayInfo->Position.z) >> FLOATNS;
				dist = x*x + z*z;

				if(dist < ddist && abs(x) < TRANS_VIEW_LIMIT && abs(z) < TRANS_VIEW_LIMIT)
				{

					lpPlayInfo2->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
				}

			}
		}
		lpPlayInfo->szChatMessage[0] = 0;
	}
	else
		sLen = 0;



	if((lpPlayInfo->dwLastMotionRecvTime + 10000) < dwPlayServTime) return FALSE;

	TransOver = lpPlayInfo->LastTransPlayUserCount + CONNECTMAX;


	for(cnt = lpPlayInfo->LastTransPlayUserCount; cnt < TransOver; cnt++)
	{
		ClipCnt = cnt&CONNECTMAX_MASK;

		if(rsPlayInfo[ClipCnt].lpsmSock && &rsPlayInfo[ClipCnt] != lpPlayInfo && rsPlayInfo[ClipCnt].TransInfoFlag &&
			rsPlayInfo[ClipCnt].srRecvPlayBuffCnt > 0 && !rsPlayInfo[ClipCnt].HideMode &&
			(!SoloMode || rsPlayInfo[ClipCnt].getSecurity() >= AccountTypes::SEC_ADMINISTRATOR))
		{

			lpPlayInfo2 = &rsPlayInfo[ClipCnt];
			dwRecvFrame = lpPlayInfo2->srRecvPlayBuffCnt;
			dwSendFrame = lpPlayInfo->dwSendFrames[ClipCnt];

			x = (lpPlayInfo2->Position.x - lpPlayInfo->Position.x) >> FLOATNS;
			z = (lpPlayInfo2->Position.z - lpPlayInfo->Position.z) >> FLOATNS;
			dist = x*x + z*z;

			if(dist < rsConnectViewDist && abs(x) < TRANS_VIEW_LIMIT && abs(z) < TRANS_VIEW_LIMIT)
			{
				if(lpPlayInfo2->PlayBuffSleep && dwSendFrame >= dwRecvFrame)
				{

					if(dist < DIST_TRANSLEVEL_HIGH)
					{
						sbCnt = srPLAYBUFF_MAX;
					}
					else
					{
						sbCnt = -1;
					}
				}
				else
				{
					if(!dwSendFrame || dwSendFrame >= dwRecvFrame)
					{
						sbCnt = -1;
						lpPlayInfo->dwSendFrames[ClipCnt] = dwRecvFrame;
					}
					else
					{
						if((dwRecvFrame - dwSendFrame) > srPLAYBUFF_MASK)
							dwSendFrame = dwRecvFrame - srPLAYBUFF_MASK;

						sbCnt = dwSendFrame&srPLAYBUFF_MASK;
						dwSendFrame++;
						lpPlayInfo->dwSendFrames[ClipCnt] = dwSendFrame;
					}
				}


				if(sbCnt >= 0)
				{
					size = ((smTRANS_PLAYDATA *)lpPlayInfo2->srPlayBuff[sbCnt])->size;


					if((lpTransBuff - TransBuff + size) >= TRANS_BUFF_SIZE)
					{
						lpPlayDataGroup->size = (lpTransBuff - TransBuff);
						lpPlayDataGroup->PlayDataCnt = PlayDataCnt;
						lpPlayInfo->lpsmSock->Send((char *)lpPlayDataGroup, lpPlayDataGroup->size, TRUE);

						PlayDataCnt = 0;
						lpTransBuff = TransBuff + sizeof(smPLAYDATA_GROUP);
						SndFlag++;
						break;
					}

					if(lpPlayInfo->BefUserPacketLoop > TRANS_MAX_USER_LIMIT_OVER &&
						dist > DIST_TRANSLEVEL_NEAR && sbCnt != srPLAYBUFF_MAX)
					{

						dist = DIST_TRANSLEVEL_HIGH;
					}

					if(dist < DIST_TRANSLEVEL_HIGH)
					{

						memcpy(lpTransBuff, lpPlayInfo2->srPlayBuff[sbCnt], size);
						lpTransBuff += size;

						if(sbCnt == srPLAYBUFF_MAX)
							TransDataCount += 2;
						else
							TransDataCount += 4;

						PlayDataCnt++;
						if(TransDataCount >= TRANS_MAX_USER_LIMIT) break;
					}
					else
					{

						lpPlayData = (smPLAYDATA *)lpTransBuff;

						lpPlayData->size = sizeof(smPLAYDATA);
						lpPlayData->code = OpCode::OPCODE_PLAYDATA1;
						lpPlayData->x = lpPlayInfo2->Position.x;
						lpPlayData->y = lpPlayInfo2->Position.y;
						lpPlayData->z = lpPlayInfo2->Position.z;

						lpPlayData->angle[0] = 0;
						lpPlayData->angle[1] = 0;
						lpPlayData->angle[2] = 0;
						lpPlayData->angle[3] = 0;
						lpPlayData->frame = 0;
						lpPlayData->dwObjectSerial = lpPlayInfo2->dwObjectSerial;
						lpPlayData->dwAutoCharCode = 0;

						lpTransBuff += sizeof(smPLAYDATA);

						TransDataCount++;
						PlayDataCnt++;
						if(TransDataCount >= TRANS_MAX_USER_LIMIT) break;
					}
				}
			}
		}

		if(cnt == CONNECTMAX)
		{

			lpPlayInfo->BefUserPacketLoop = lpPlayInfo->UserPacketLoop;
			lpPlayInfo->UserPacketLoop = 0;
		}
	}


	if(SndFlag == 0 && (PlayDataCnt || (lpPlayInfo->SendPlayGroupCount & 3) == 0))
	{
		lpPlayDataGroup->size = (lpTransBuff - TransBuff);
		lpPlayDataGroup->PlayDataCnt = PlayDataCnt;
		lpPlayInfo->lpsmSock->Send((char *)lpPlayDataGroup, lpPlayDataGroup->size, TRUE);
	}

	ClipCnt = cnt&CONNECTMAX_MASK;
	lpPlayInfo->LastTransPlayUserCount = ClipCnt;
	lpPlayInfo->SendPlayGroupCount++;
	lpPlayInfo->UserPacketLoop += TransDataCount;

	return TRUE;
}



DWORD srAutoTransCounter = 0;


int srAutoTransPlay()
{
	int cnt;

	int start;
	DWORD	dwWaitTime;

	smTRANS_COMMAND	smTransCommand;
	char	szTempBuff[128];








	if(AutoPlayServer)
	{
		start = srAutoTransCounter & 0x3F;

		for(cnt = start; cnt < CONNECTMAX; cnt += 0x40)
		{
			if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial &&
				(dwPlayServTime - rsPlayInfo[cnt].dwLastRecvTime) < OVER_TRANS_TIME)
			{


				srTransPlayData(&rsPlayInfo[cnt]);

				rsSendGameServerExp(&rsPlayInfo[cnt]);
			}
		}
	}

	if(UserPlayServer)
	{
		start = srAutoTransCounter & 0x1F;

		for(cnt = start; cnt < CONNECTMAX; cnt += 0x20)
		{
			if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial &&
				((dwPlayServTime - rsPlayInfo[cnt].dwLastRecvTime) < OVER_TRANS_TIME || rsPlayInfo[cnt].PlayBuffSleep))
			{

				srTransPlayUserData(&rsPlayInfo[cnt]);
			}
		}

		if(start == 0x3F)
		{

			for(cnt = 0; cnt < CONNECTMAX; cnt++)
			{
				if(rsPlayInfo[cnt].lpsmSock)
				{
					if(rsPlayInfo[cnt].PlayBuffSleep != 0)
					{
						rsPlayInfo[cnt].PlayBuffSleep++;
					}

				}
			}
		}
	}




	for(cnt = (srAutoTransCounter & 0x1FF); cnt < CONNECTMAX; cnt += 0x200)
	{
		if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwLastRecvTime)
		{


			if(rsServerConfig.ExpGameTimeMode && rsPlayInfo[cnt].dwExpGameTimeCheck &&
				rsPlayInfo[cnt].Position.Area < STAGE_AREA_MAX && StageArea[rsPlayInfo[cnt].Position.Area].lpField)
			{

				int gTimeChk = rsPlayInfo[cnt].dwExpGameTime / (1000 * 60);
				int gTimeOld = rsPlayInfo[cnt].dwExpGameTime;


				rsPlayInfo[cnt].dwExpGameTime += (dwPlayServTime - rsPlayInfo[cnt].dwExpGameTimeCheck);

				if(rsServerConfig.ExpGameTimeMode == 3)
				{
					rsDispay_GameTime(&rsPlayInfo[cnt], gTimeOld);
				}



				if(rsServerConfig.ExpGameTimeMode == 2)
				{
					int gTime = rsPlayInfo[cnt].dwExpGameTime / (1000 * 60);
					if(gTime > (5 * 60 - 5) && gTimeChk != gTime)
					{

						TRANS_CHATMESSAGE	TransChatMessage;
						wsprintf(TransChatMessage.szMessage, srMsg_Bl_01, (5 * 60) - gTime);
						TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
						TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
						TransChatMessage.dwIP = 3;
						TransChatMessage.dwObjectSerial = 0;
						rsPlayInfo[cnt].lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);

						if(gTime >= 5 * 60)
						{
							rsSendCloseClient(&rsPlayInfo[cnt]);
						}
					}
				}


				rsPlayInfo[cnt].dwExpGameTimeCheck = dwPlayServTime;
			}


			if(rsPlayInfo[cnt].smCharInfo.dwEventTime_T && (rsPlayInfo[cnt].smCharInfo.dwEventTime_T + 60) < (DWORD)tServerTime)
			{
				rsPlayInfo[cnt].smCharInfo.dwEventTime_T = 0;
				rsPlayInfo[cnt].smCharInfo.SizeLevel = 1;
			}


			if(rsPlayInfo[cnt].dwStartUser_PresentItem_Time && rsPlayInfo[cnt].dwStartUser_PresentItem_Time < dwPlayServTime)
			{
				rsStartUser_PresentItem(&rsPlayInfo[cnt]);
			}

			if(UserPlayServer && (rsPlayInfo[cnt].dwMacroChkTime + 60000) > dwPlayServTime)
			{
				if(rsPlayInfo[cnt].Position.Area < STAGE_AREA_MAX && StageArea[rsPlayInfo[cnt].Position.Area].lpField &&
					StageArea[rsPlayInfo[cnt].Position.Area].lpField->State == FIELD_STATE_VILLAGE)
				{

					rsPlayInfo[cnt].dwMacroAngTime = 0;
					rsPlayInfo[cnt].dwMacroTime = 0;
				}


				if(rsPlayInfo[cnt].dwMacroAngTime && rsPlayInfo[cnt].dwMacroAngTime + (60000 * 2) < dwPlayServTime)
				{

					rsPlayInfo[cnt].dwMacroAngTime = 0;
					rsPlayInfo[cnt].dwMacroTime = 0;
				}
				if(rsPlayInfo[cnt].dwMacroTime && rsPlayInfo[cnt].dwMacroTime + (60000 * 60) < dwPlayServTime)
				{

					smTransCommand.code = OpCode::OPCODE_SET_BLACKLIST;
					smTransCommand.size = sizeof(smTRANS_COMMAND);
					smTransCommand.WParam = 8102;
					smTransCommand.LParam = (dwPlayServTime - rsPlayInfo[cnt].dwMacroTime) / 60000;
					smTransCommand.SParam = rsPlayInfo[cnt].Position.Area;
					smTransCommand.EParam = rsServerConfig.ServerCode;
					rsSendDataServer(rsPlayInfo[cnt].lpsmSock, &smTransCommand);

					rsPlayInfo[cnt].dwMacroAngTime = 0;
					rsPlayInfo[cnt].dwMacroTime = 0;
				}
			}

			dwWaitTime = rsPlayInfo[cnt].dwLastRecvTime + (1000 * 60 * 6);

			if(dwWaitTime < dwPlayServTime ||
				(rsPlayInfo[cnt].dwHopeDisconnectTime && rsPlayInfo[cnt].dwHopeDisconnectTime < dwPlayServTime))
			{

				if(rsPlayInfo[cnt].lpsmSock)
				{
					wsprintf(szTempBuff, "ID( %s ) Name( %s ) IP( %s ) TimeOut Message\r\n",
						rsPlayInfo[cnt].getAccount().c_str(), rsPlayInfo[cnt].getName().c_str(), rsPlayInfo[cnt].lpsmSock->szIPAddr);
					Record_TempLogFile(szTempBuff);
				}

				DisconnectUser(rsPlayInfo[cnt].lpsmSock);
			}


			if(rsServerConfig.ClientFuncCheckMode)
			{
				if(rsPlayInfo[cnt].dwClientFunChk_NextTime < dwPlayServTime)
				{
					rsCheckClientFuncMem(&rsPlayInfo[cnt]);
					rsPlayInfo[cnt].dwClientFunChk_NextTime = dwPlayServTime + 60 * 1000;

					if(!rsPlayInfo[cnt].dwFuncChkErrorFlag)
					{
						if(rsPlayInfo[cnt].FuncChkFailCount1 > 10 || rsPlayInfo[cnt].FuncChkFailCount2 > 10)
						{

							if(rsPlayInfo[cnt].lpsmSock)
							{
								wsprintf(szTempBuff, "ID( %s ) Name( %s ) IP( %s ) Func Check Out Message\r\n",
									rsPlayInfo[cnt].getAccount().c_str(), rsPlayInfo[cnt].getName().c_str(), rsPlayInfo[cnt].lpsmSock->szIPAddr);
								Record_TempLogFile(szTempBuff);
							}

							DisconnectUser(rsPlayInfo[cnt].lpsmSock);
						}
						else
						{
							if(rsPlayInfo[cnt].ClientFunChk1_Count > 60)
							{
								rsPlayInfo[cnt].ClientFunChk1_Count = 0;
								rsPlayInfo[cnt].FuncChkFailCount1 = 0;
								rsPlayInfo[cnt].FuncChkSucessCount1 = 0;
							}
							if(rsPlayInfo[cnt].ClientFunChk2_Count > 80)
							{
								rsPlayInfo[cnt].ClientFunChk2_Count = 0;
								rsPlayInfo[cnt].FuncChkFailCount2 = 0;
								rsPlayInfo[cnt].FuncChkSucessCount2 = 0;
							}

							if((rsPlayInfo[cnt].ClientFunChk1_Count > 10 && rsPlayInfo[cnt].FuncChkSucessCount1 < (rsPlayInfo[cnt].ClientFunChk1_Count >> 1)) ||
								(rsPlayInfo[cnt].ClientFunChk2_Count > 10 && rsPlayInfo[cnt].FuncChkSucessCount2 < (rsPlayInfo[cnt].ClientFunChk2_Count >> 1)))
							{

								smTransCommand.WParam = 1132;
								if(rsPlayInfo[cnt].ClientFunChk1_Count)
									smTransCommand.LParam = (rsPlayInfo[cnt].FuncChkSucessCount1 * 100) / rsPlayInfo[cnt].ClientFunChk1_Count;
								else
									smTransCommand.LParam = 0;

								if(rsPlayInfo[cnt].ClientFunChk2_Count)
									smTransCommand.SParam = (rsPlayInfo[cnt].FuncChkSucessCount2 * 100) / rsPlayInfo[cnt].ClientFunChk2_Count;
								else
									smTransCommand.SParam = 0;

								RecordHackLogFile(&rsPlayInfo[cnt], &smTransCommand);

								DisconnectUser(rsPlayInfo[cnt].lpsmSock);
							}

						}
					}
				}
			}

		}

		if(smWSock[cnt].sock && smWSock[cnt].dwLastRecvTime &&
			(smWSock[cnt].dwLastRecvTime + 1000 * 60 * 8) < dwPlayServTime)
		{

			wsprintf(szTempBuff, "Socket IP( %s ) TimeOut Message\r\n", smWSock[cnt].szIPAddr);
			Record_TempLogFile(szTempBuff);

			DisconnectUser(&smWSock[cnt]);
		}

	}

	if(UserPlayServer || AutoPlayServer)
	{

		start = srAutoTransCounter & 0x3F;
		for(cnt = start; cnt < CONNECTMAX; cnt += 0x40)
		{
			if(rsPlayInfo[cnt].lpsmSock && (dwPlayServTime - rsPlayInfo[cnt].dwLastRecvTime) > 4000)
			{
				if(rsPlayInfo[cnt].dwObjectSerial ||
					(rsPlayInfo[cnt].SystemLine && (dwPlayServTime - rsPlayInfo[cnt].dwLastRecvTime) > 10000))
				{

					if(rsPlayInfo[cnt].lpsmSock->WaitReadMessage == 0)
					{
						rsPlayInfo[cnt].lpsmSock->WaitReadMessage = 24;
					}
				}
			}
		}
	}
	else
	{

		start = srAutoTransCounter & 0x3F;
		for(cnt = start; cnt < CONNECTMAX; cnt += 0x40)
		{
			if(rsPlayInfo[cnt].lpsmSock && (dwPlayServTime - rsPlayInfo[cnt].dwLastRecvTime) > 9000)
			{
				if(!rsPlayInfo[cnt].getName().empty() ||
					(rsPlayInfo[cnt].SystemLine && (dwPlayServTime - rsPlayInfo[cnt].dwLastRecvTime) > 10000))
				{

					if(rsPlayInfo[cnt].lpsmSock->WaitReadMessage == 0)
					{
						rsPlayInfo[cnt].lpsmSock->WaitReadMessage = 24;
					}
				}
			}
		}
	}

	srAutoTransCounter++;
	return TRUE;
}

static int srBillingCounter = 0;

static DWORD dwBillingTime = 0;


int srDisplayBillingTime(rsPLAYINFO *lpPlayInfo, int Add_BillingTime)
{

	return TRUE;


	struct tm *today;

	int y, m, d, h, hm, hs;
	TRANS_CHATMESSAGE	TransChatMessage;
	int Time;
	char	*lpBuff;
	char	szBuff[128];


	if((lpPlayInfo->Bl_Meter&BIMASK_PRORATE_USER) != 0) return FALSE;
	if((lpPlayInfo->Bl_Meter&BIMASK_FREE_USER) != 0) return FALSE;

	if(lpPlayInfo->Bl_RNo > 0)
		lpBuff = srMsg_Bl_02;
	else
		lpBuff = "";

	szBuff[0] = 0;

	if(lpPlayInfo->DisuseDay)
	{


		today = localtime(&lpPlayInfo->DisuseDay);


		if(Add_BillingTime)
		{
			today = localtime((time_t *)&Add_BillingTime);
		}


		if(today)
		{
			y = today->tm_year + 1900;
			m = today->tm_mon + 1;
			d = today->tm_mday;
			h = today->tm_hour;
			hm = today->tm_min;
			hs = today->tm_sec;

#ifdef	_LANGUAGE_TAIWAN		
			wsprintf(TransChatMessage.szMessage, srMsg_Bl_100, lpBuff, y, m, d, h, hm, szBuff);
#endif

#ifdef _LANGUAGE_THAI
			wsprintf(TransChatMessage.szMessage, srMsg_Bl_100, lpBuff, d, m, y, h, hm, szBuff);
#endif

#ifdef _LANGUAGE_ENGLISH
#ifdef _LANGUAGE_PHILIPIN
			if(hm != 0)	wsprintf(TransChatMessage.szMessage, srMsg_Bl_100p, lpBuff, h, hm, m, d, y, szBuff);
			else		wsprintf(TransChatMessage.szMessage, srMsg_Bl_1001p, lpBuff, h, hm, m, d, y, szBuff);
#else
			if(hm != 0)	wsprintf(TransChatMessage.szMessage, srMsg_Bl_100, lpBuff, h, hm, m, d, y, szBuff);
			else		wsprintf(TransChatMessage.szMessage, srMsg_Bl_1001, lpBuff, h, hm, m, d, y, szBuff);
#endif
#endif


#ifdef _LANGUAGE_CHINESE													   
			if(hm != 0)	wsprintf(TransChatMessage.szMessage, srMsg_Bl_100, lpBuff, y, m, d, h, hm, szBuff);
			else		wsprintf(TransChatMessage.szMessage, srMsg_Bl_1001, lpBuff, y, m, d, h, hm, szBuff);
#endif
#ifdef _LANGUAGE_VEITNAM
			if(hm != 0)	wsprintf(TransChatMessage.szMessage, srMsg_Bl_100, lpBuff, h, hm, m, d, y, szBuff);
			else		wsprintf(TransChatMessage.szMessage, srMsg_Bl_1001, lpBuff, h, hm, m, d, y, szBuff);
#endif

#ifdef _LANGUAGE_BRAZIL
			if(hm != 0)	wsprintf(TransChatMessage.szMessage, srMsg_Bl_100, lpBuff, h, hm, m, d, y, szBuff);
			else		wsprintf(TransChatMessage.szMessage, srMsg_Bl_1001, lpBuff, h, hm, m, d, y, szBuff);
#endif
#ifdef	_LANGUAGE_JAPANESE 
			wsprintf(TransChatMessage.szMessage, srMsg_Bl_100, lpBuff, y, m, d, szBuff);
#endif

			TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
			TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
			TransChatMessage.dwIP = 3;
			TransChatMessage.dwObjectSerial = 0;

			if(lpPlayInfo->lpsmSock)
				lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
		}
	}


	if(lpPlayInfo->dwPeriodTime)
	{

		if(Add_BillingTime)
		{
			wsprintf(szBuff, srMsg_BI_04, Add_BillingTime / (60 * 60));
		}

		if(lpPlayInfo->dwPeriodTime > (DWORD)tServerTime)
			Time = (lpPlayInfo->dwPeriodTime - (DWORD)tServerTime) / 60;
		else
			Time = 0;

		if(Time < 0) Time = 0;


		Time += Add_BillingTime / 60;
		szBuff[0] = 0;


		h = Time / 60;
		m = Time % 60;

		if(h > 0)
		{
			wsprintf(TransChatMessage.szMessage, srMsg_Bl_101, lpBuff, h, m, szBuff);
		}
		else
		{
			wsprintf(TransChatMessage.szMessage, srMsg_Bl_102, lpBuff, m, szBuff);
		}

		TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		TransChatMessage.dwIP = 3;
		TransChatMessage.dwObjectSerial = 0;
		if(lpPlayInfo->lpsmSock)
			lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
	}


	return TRUE;
}

int srBillingMain()
{
	int cnt;
	int Time;
	int HiddenPeriod;

	srBillingCounter++;

	if((srBillingCounter & 0xF) == 0)
	{

		cnt = (srBillingCounter >> 4)&CONNECTMAX_MASK;

		if(rsPlayInfo[cnt].lpsmSock && !rsPlayInfo[cnt].getAccount().empty() && !rsPlayInfo[cnt].getName().empty() && rsPlayInfo[cnt].dwObjectSerial)
		{
			if(rsPlayInfo[cnt].Bl_RNo)
			{
				if(rsPlayInfo[cnt].Bl_RNo > 0 || ((srBillingCounter >> 4)&CONNECTMAX) == 0)
				{
					bSql_PCUse(&rsPlayInfo[cnt]);
				}
			}

		}
	}

	if((srBillingCounter & 0xFFF) != 0)
	{
		return FALSE;
	}

	if(dwBillingTime >= dwPlayServTime)
		return FALSE;

	dwBillingTime = dwPlayServTime;

	smTRANS_COMMAND	smTransCommand;
	TRANS_CHATMESSAGE	TransChatMessage;


	smTransCommand.code = OpCode::OPCODE_CLOSECLIENT;
	smTransCommand.size = sizeof(smTRANS_COMMAND);


	for(cnt = 0; cnt < CONNECTMAX; cnt++)
	{

		if(rsPlayInfo[cnt].lpsmSock && !rsPlayInfo[cnt].getAccount().empty() && !rsPlayInfo[cnt].getName().empty() && rsPlayInfo[cnt].dwObjectSerial)
		{

			if(rsPlayInfo[cnt].dwPeriodTime2)
			{

				Time = rsPlayInfo[cnt].dwPeriodTime2 - (int)tServerTime;
				if(Time < 6 * 60 && Time>0)
				{
					if(rsPlayInfo[cnt].dwPeriodTime != rsPlayInfo[cnt].dwPeriodTime2)
					{
						rsPlayInfo[cnt].dwPeriodTime = rsPlayInfo[cnt].dwPeriodTime2;
					}
					HiddenPeriod = TRUE;
				}
				else
					HiddenPeriod = FALSE;

			}
			else
			{
				HiddenPeriod = FALSE;
			}

			if(rsPlayInfo[cnt].DisuseDay && HiddenPeriod == FALSE)
			{

				Time = (int)rsPlayInfo[cnt].DisuseDay - (int)tServerTime;


				if(Time < 6 * 60 && Time>0)
				{
					if(Time < 5 * 60)
					{
						wsprintf(TransChatMessage.szMessage, srMsg_Bl_01, Time / 60);
						TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
						TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
						TransChatMessage.dwIP = 3;
						TransChatMessage.dwObjectSerial = 0;
						if(rsServerConfig.DispBillingTime) rsPlayInfo[cnt].lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
					}
					bSql_PCSearchReserv(&rsPlayInfo[cnt]);
				}

				if(rsPlayInfo[cnt].DisuseDay < tServerTime)
				{
					rsPlayInfo[cnt].lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

					Record_BillingLogFile(&rsPlayInfo[cnt], (DWORD)rsPlayInfo[cnt].DisuseDay, rsPlayInfo[cnt].dwPeriodTime, (DWORD)tServerTime, rsPlayInfo[cnt].Bl_RNo);
				}
			}

			if(rsPlayInfo[cnt].dwPeriodTime)
			{

				Time = rsPlayInfo[cnt].dwPeriodTime - (int)tServerTime;

				if(Time < 6 * 60 && Time>0)
				{
					if(Time < 5 * 60)
					{

						wsprintf(TransChatMessage.szMessage, srMsg_Bl_01, Time / 60);
						TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
						TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
						TransChatMessage.dwIP = 3;
						TransChatMessage.dwObjectSerial = 0;
						if(rsServerConfig.DispBillingTime)  rsPlayInfo[cnt].lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
					}
					bSql_PCSearchReserv(&rsPlayInfo[cnt]);
				}

				if(Time <= 0)
				{
					rsPlayInfo[cnt].lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
					if(!HiddenPeriod)
					{

						Record_BillingLogFile(&rsPlayInfo[cnt], (DWORD)rsPlayInfo[cnt].DisuseDay, rsPlayInfo[cnt].dwPeriodTime, (DWORD)tServerTime, rsPlayInfo[cnt].Bl_RNo);
					}
				}
			}

		}
	}

	return TRUE;
}





static DWORD FrameSkipTimer = 0;
static DWORD fps = 70;
static DWORD FpsTime;



int srPlayMain()
{
	int cnt = 0;

	if(FrameSkipTimer == 0)
	{
		FrameSkipTimer = GetCurrentTime();
		FpsTime = 1000 / fps;
	}


	EnterCriticalSection(&cSerSection);

	while(1)
	{
		if(FrameSkipTimer > GetCurrentTime()) break;
		if(Quit) break;
		if(cnt > 70 * 2)
		{
			FrameSkipTimer = GetCurrentTime();
			break;
		}

		FrameSkipTimer += FpsTime;
		if(AutoPlayServer) srAutoPlayMain();
		srAutoTransPlay();
		if(LoginServer) srBillingMain();

		cnt++;
	}


	LeaveCriticalSection(&cSerSection);

	return cnt;
}



int InitAll()
{
	DWORD nsize = 32;
	char szServerName[32] = { 0 };

	ChatBuffCnt = 0;

	GetComputerName(szServerName, &nsize);

	ServerNameCode = GetSpeedSum(szServerName);


	rsNoticeMessage.Counter = 0;
	rsNoticeMessage.szMessage[0] = 0;


	Server_AllocMemory();

	if(rsServerConfig.UseRecorMemory)
	{
		rsRecordDataBuff = new char[(srRECORD_MEMORY_SIZE + 256)*CONNECTMAX];

		if(!rsRecordDataBuff)
		{
			MessageBox(NULL, "Error Record Memory", "Alloc Failed - Hotuk Server", MB_OK);
		}
	}
	else
	{
		rsRecordDataBuff = 0;
	}

	for(int cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		ZeroMemory(&rsPlayInfo[cnt], sizeof(rsPLAYINFO));

		if(rsRecordDataBuff)
		{
			rsPlayInfo[cnt].lpRecordDataBuff = rsRecordDataBuff + ((srRECORD_MEMORY_SIZE + 256)*cnt);
		}
	}

	InitMaterial();

	srInitChar();

	InitMonster();

	InitItems();

	LoadOftenNpc();

	InitCrackFinding();

	Stage_StepHeight = fONE * 20;

	StageArea = new STG_AREA[STAGE_AREA_MAX];
	srReadStage();

	ConvertMonsterNames();

	AutoPlayServer = rsServerConfig.AutoPlayer;

	SetTimer(hwnd, 0, 100, NULL);
	dwPlayServTime = GetCurrentTime();

	InitLogSql();

	rsResetClientFuncPos();

	rsLoadCopiedItemList();

	RecordShutdownLOG(50020, 0, 0);

	rsInit_SerToServer();

	ZeroMemory(&rsUserListDamageTop10, sizeof(rsUSER_LIST_TOP10));

	OpenBossTimeMin = (rand() % 45) + 1;

	rsInit_Castle();

	ZeroMemory(&CurrencyLog, sizeof(rsCURRENCY_LOG));


	return TRUE;
}


void RemoveAll()
{
	smTRANS_COMMAND smTransCommand;

	RecordShutdownLOG(50030, 0, 0);

	for(int cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		if(rsPlayInfo[cnt].lpRecordDataBuff)
		{
			if(rsPlayInfo[cnt].lpsmSock && !rsPlayInfo[cnt].getName().empty())
			{
				if(rsRecordMemoryBuffToFile(&rsPlayInfo[cnt], rsPlayInfo[cnt].getName().c_str(), rsPlayInfo[cnt].lpRecordDataBuff) == TRUE)
				{
					if(lstrcmpi(rsPlayInfo[cnt].getName().c_str(), ((TRANS_RECORD_DATA *)rsPlayInfo[cnt].lpRecordDataBuff)->smCharInfo.szName) != 0)
					{
						smTransCommand.WParam = 10002;
						smTransCommand.LParam = (DWORD)rsPlayInfo[cnt].getName().c_str();
						smTransCommand.SParam = (DWORD)((TRANS_RECORD_DATA *)rsPlayInfo[cnt].lpRecordDataBuff)->smCharInfo.szName;
						RecordHackLogFile(&rsPlayInfo[cnt], &smTransCommand);
					}

					rsSaveThrowData(&rsPlayInfo[cnt]);
					rsRecordMemoryBuff_CheckInvenItem(&rsPlayInfo[cnt], 1);
				}
			}
		}
	}

	if(rsRecordDataBuff)
	{
		delete rsRecordDataBuff;
	}

	rsCloseDataBase();
	CloseLogSql();

	EnterCriticalSection(&cSerSection);

	srRemoveChar();
	srRemoveStage();
	CloseMaterial();

	if(StageArea)
	{
		for(int cnt = STAGE_AREA_MAX - 1; cnt >= 0; cnt--)
		{
			StageArea[cnt].Close();
		}

		delete[] StageArea;
		StageArea = nullptr;
	}

	rsRemoveCopiedItemList();


	Server_RemoveMemory();


	LeaveCriticalSection(&cSerSection);

}

DWORD dwConnIPCheckTime = 0;


int AddNewPlayInfo(smWINSOCK *lpsmSock)
{
	int cnt, cnt2;
	DWORD	dwMyIP;
	int	SameIPCount = 0;
	smTRANS_COMMAND	TransCommand;

	dwMyIP = lpsmSock->acc_sin.sin_addr.S_un.S_addr;

	for(cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].lpsmSock->acc_sin.sin_addr.S_un.S_addr == dwMyIP)
		{
			SameIPCount++;
		}
		else
		{
			if(rsPlayInfo[cnt].lpsmSock == 0) break;
		}
	}
	if(cnt == CONNECTMAX) return FALSE;


	if(SameIPCount > 32)
	{

		if(rsCheckSystemIP(dwMyIP) == FALSE)
		{

			DisconnectUser(lpsmSock);

			if(abs((long)dwConnIPCheckTime - (long)dwPlayServTime) > 60 * 1000 * 3)
			{

				smTRANS_COMMAND smTransCommand;
				smTransCommand.WParam = 5000;
				smTransCommand.SParam = SameIPCount;
				smTransCommand.LParam = dwMyIP;
				RecordHackLogFile(0, &smTransCommand);
			}

			return FALSE;
		}
	}

	if(ShutDownFlag)
	{

		if(strstr(lpsmSock->szIPAddr, szAdminIP) == 0)
		{
			DisconnectUser(lpsmSock);
			return FALSE;
		}
	}


	lpsmSock->ExtData1 = (void *)&rsPlayInfo[cnt];


	rsPlayInfo[cnt].lpsmSock = lpsmSock;
	rsPlayInfo[cnt].ChatBuffCnt = ChatBuffCnt;
	rsPlayInfo[cnt].SendListCnt = 0;
	rsPlayInfo[cnt].Position.Area = 0xFFFFFFFF;
	rsPlayInfo[cnt].TransInfoFlag = FALSE;
	rsPlayInfo[cnt].SystemLine = 0;
	rsPlayInfo[cnt].CharLevelMax = 0;
	rsPlayInfo[cnt].AdminOperMode = 0;
	rsPlayInfo[cnt].dwDataError = 0;

	for(cnt2 = 0; cnt2 < srPLAYBUFF_MAX + 1; cnt2++)
		rsPlayInfo[cnt].srPlayBuffSize[cnt2] = 0;

	rsPlayInfo[cnt].srSendPlayBuffCnt = 0;
	rsPlayInfo[cnt].srRecvPlayBuffCnt = 0;
	rsPlayInfo[cnt].dwObjectSerial = 0;
	rsPlayInfo[cnt].szChatMessage[0] = 0;
	rsPlayInfo[cnt].lpRecordBase = 0;
	rsPlayInfo[cnt].lpPostBoxItem = 0;
	rsPlayInfo[cnt].PostPassFailCount = 0;


	rsPlayInfo[cnt].security = AccountTypes::SEC_PLAYER;
	rsPlayInfo[cnt].HideMode = 0;
	rsPlayInfo[cnt].CharLoadingCount = 0;
	rsPlayInfo[cnt].dwNoticeCount = rsNoticeMessage.Counter;

	rsPlayInfo[cnt].LastTransPlayUserCount = 0;
	rsPlayInfo[cnt].LastTransAutoPlayCount = 0;

	rsPlayInfo[cnt].UnsaveMoney = -1;
	rsPlayInfo[cnt].ThrowItemCount = 0;

	rsPlayInfo[cnt].setAccountId(0);
	rsPlayInfo[cnt].setAccount('\0');
	rsPlayInfo[cnt].setPassword('\0');
	rsPlayInfo[cnt].setName('\0');
	ZeroMemory(rsPlayInfo[cnt].szServerID, sizeof(rsPlayInfo[cnt].szServerID));

	rsPlayInfo[cnt].dwLastRecvTime = dwPlayServTime;
	rsPlayInfo[cnt].dwLastMotionRecvTime = dwPlayServTime;

	rsPlayInfo[cnt].dwConnectCount = dwConnectCount;

	rsPlayInfo[cnt].SendPlayGroupCount = 0;

	rsPlayInfo[cnt].MonTranCount = 0;
	rsPlayInfo[cnt].CharTransCount = 0;
	rsPlayInfo[cnt].HitMonsterCount = 0;
	rsPlayInfo[cnt].UserPacketLoop = 0;
	rsPlayInfo[cnt].BefUserPacketLoop = 0;

	rsPlayInfo[cnt].lpChrTarget = 0;
	rsPlayInfo[cnt].dwTarObjSerial = 0;
	rsPlayInfo[cnt].smCharInfo.szName[0] = 0;
	rsPlayInfo[cnt].smCharInfo.Level = 0;
	rsPlayInfo[cnt].CrackWarning = 0;
	rsPlayInfo[cnt].dwTime_Disconnect = 0;
	rsPlayInfo[cnt].EventMode = 0;
	rsPlayInfo[cnt].AreaOutCount = 0;


	rsPlayInfo[cnt].dwPartyInfo = 0;
	rsPlayInfo[cnt].lpPartyMaster = 0;

	rsPlayInfo[cnt].DamagePacketCount = 0;
	rsPlayInfo[cnt].dwDamagePacketTime = 0;
	rsPlayInfo[cnt].AttackCount = 0;
	rsPlayInfo[cnt].dwAttackTime = dwPlayServTime;
	rsPlayInfo[cnt].dwConnectTime = dwPlayServTime;
	rsPlayInfo[cnt].dwRecvTimePlayBuff = 0;
	rsPlayInfo[cnt].BadPlayer = 0;
	rsPlayInfo[cnt].dwPacketAttackCount = 0;
	rsPlayInfo[cnt].dwPacketAttackTime = dwPlayServTime;

	rsPlayInfo[cnt].BlockTime = 0;
	rsPlayInfo[cnt].MonsterKillCounter = 0;
	rsPlayInfo[cnt].WhisperMode = 0;
	rsPlayInfo[cnt].Event_StarTicketLevel = 0;


	rsPlayInfo[cnt].dwClanCode = 0;
	rsPlayInfo[cnt].SucessCheck_ClanCode = 0;


	rsPlayInfo[cnt].spExp_Start = 0;
	rsPlayInfo[cnt].spMoney_Start = 0;
	rsPlayInfo[cnt].spLevel_Start = 0;

	rsPlayInfo[cnt].spExp_InOut_Total = 0;
	rsPlayInfo[cnt].spMoney_In_Total = 0;
	rsPlayInfo[cnt].spMoney_InOut_Total = 0;

	rsPlayInfo[cnt].spEXP_Out = 0;
	rsPlayInfo[cnt].spMoney_In = 0;
	rsPlayInfo[cnt].spMoney_Out = 0;
	rsPlayInfo[cnt].dwLastExpMoneyCheckTime = dwPlayServTime;
	rsPlayInfo[cnt].dwLastExpMoneyTransServer = dwPlayServTime;

	rsPlayInfo[cnt].ServerMoney = 0;
	rsPlayInfo[cnt].WareHouseMoney = 0;
	rsPlayInfo[cnt].dwNSpriteTime = 0;

	for(cnt2 = 0; cnt2 < 8; cnt2++)
	{
		rsPlayInfo[cnt].dwGameServerExp[cnt2] = 0;
		ZeroMemory(rsPlayInfo[cnt].RcvItemSecCodeBuff[cnt2], sizeof(int) * 16);
	}
	rsPlayInfo[cnt].SndItemSecCodeCount = 1;

	rsPlayInfo[cnt].smCharInfo.Level = 0;
	rsPlayInfo[cnt].smCharInfo.Exp = 0;
	rsPlayInfo[cnt].smCharInfo.Exp_High = 0;
	rsPlayInfo[cnt].smCharInfo.Money = 0;
	rsPlayInfo[cnt].smCharInfo.JOB_CODE = 0;


	rsPlayInfo[cnt].RecordWarningCount = 0;
	rsPlayInfo[cnt].RecordWarningExp = 0;
	rsPlayInfo[cnt].WarningCount = 0;

	rsPlayInfo[cnt].dwLastTradeChksum = 0;


	rsPlayInfo[cnt].Send_AttackCount = 0;
	rsPlayInfo[cnt].Send_AttackDamage = 0;
	rsPlayInfo[cnt].Recv_AttackCount = 0;
	rsPlayInfo[cnt].Recv_AttackDamage = 0;


	rsPlayInfo[cnt].dwHopeDisconnectTime = 0;

	rsPlayInfo[cnt].Client_Version = 0;

	rsPlayInfo[cnt].UpdateInfo_WarnigCounter = 0;


	rsPlayInfo[cnt].dwMacroTime = 0;
	rsPlayInfo[cnt].dwMacroAngTime = 0;
	rsPlayInfo[cnt].dwMacroChkTime = 0;


	rsPlayInfo[cnt].dwClientFuncChk_1 = 0;
	rsPlayInfo[cnt].dwClientFuncChk_2 = 0;
	rsPlayInfo[cnt].FuncChkFailCount1 = 0;
	rsPlayInfo[cnt].FuncChkFailCount2 = 0;
	rsPlayInfo[cnt].dwFuncChkErrorFlag = 0;
	rsPlayInfo[cnt].ClientFunChk1_Count = 0;
	rsPlayInfo[cnt].ClientFunChk2_Count = 0;
	rsPlayInfo[cnt].FuncChkSucessCount1 = 0;
	rsPlayInfo[cnt].FuncChkSucessCount2 = 0;
	rsPlayInfo[cnt].dwClientFunChk_NextTime = dwPlayServTime + 60 * 1000 * 5;

	rsPlayInfo[cnt].dwLastSaveTime = 0;

	rsPlayInfo[cnt].dwClentOS = 0;
	rsPlayInfo[cnt].dwClentModulChkSum = 0;
	rsPlayInfo[cnt].ClentModuleCount = 0;



	rsPlayInfo[cnt].szGuid[0] = 0;
	rsPlayInfo[cnt].szGPCode[0] = 0;
	rsPlayInfo[cnt].GpCode = -1;
	rsPlayInfo[cnt].GpType = -1;
	rsPlayInfo[cnt].DisuseDay = 0;
	rsPlayInfo[cnt].dwPeriodTime = 0;
	rsPlayInfo[cnt].Bl_RNo = 0;
	rsPlayInfo[cnt].Bl_Meter = 0;
	rsPlayInfo[cnt].dwPeriodTime2 = 0;




	rsPlayInfo[cnt].dwSkill_AutoMation_Time = 0;
	rsPlayInfo[cnt].dwSkill_AutoMation_Param = 0;
	rsPlayInfo[cnt].dwSkill_Maximize_Time = 0;
	rsPlayInfo[cnt].dwSkill_Maximize_Param = 0;
	rsPlayInfo[cnt].dwSkill_PhysicalAbsorb_Time = 0;
	rsPlayInfo[cnt].dwSkill_PhysicalAbsorb_Param = 0;
	rsPlayInfo[cnt].dwSkill_ExtreamShield_Time = 0;
	rsPlayInfo[cnt].dwSkill_ExtreamShield_Param = 0;

	rsPlayInfo[cnt].dwSkill_HolyBody_Time = 0;
	rsPlayInfo[cnt].dwSkill_HolyBody_Param = 0;
	rsPlayInfo[cnt].dwSkill_HolyValor_Time = 0;
	rsPlayInfo[cnt].dwSkill_HolyValor_Param = 0;
	rsPlayInfo[cnt].dwSkill_HolyReflection_Time = 0;
	rsPlayInfo[cnt].dwSkill_HolyReflection_Param = 0;
	rsPlayInfo[cnt].dwSkill_EnchantWeapon_Time = 0;
	rsPlayInfo[cnt].dwSkill_EnchantWeapon_Param = 0;

	rsPlayInfo[cnt].dwSkill_SparkShield_Time = 0;
	rsPlayInfo[cnt].dwSkill_MetalArmor_Param = 0;
	rsPlayInfo[cnt].dwSkill_SparkShield_Time = 0;
	rsPlayInfo[cnt].dwSkill_SparkShield_Param = 0;

	rsPlayInfo[cnt].dwSKill_Falcon_Time = 0;
	rsPlayInfo[cnt].dwSKill_Falcon_Damage[0] = 0;
	rsPlayInfo[cnt].dwSKill_Falcon_Damage[1] = 0;

	rsPlayInfo[cnt].dwSkill_DivineInhalation_Time = 0;
	rsPlayInfo[cnt].dwSkill_DivineInhalation_Param = 0;

	rsPlayInfo[cnt].dwSkill_TriumphOfValhalla_Time = 0;
	rsPlayInfo[cnt].dwSkill_TriumphOfValhalla_Param = 0;

	rsPlayInfo[cnt].dwSkill_VirtualLife_Time = 0;
	rsPlayInfo[cnt].dwSkill_VirtualLife_Param = 0;

	rsPlayInfo[cnt].dwSkill_EnergyShield_Time = 0;
	rsPlayInfo[cnt].dwSkill_EnergyShield_Param = 0;

	rsPlayInfo[cnt].dwSkill_SpiritElemental_Time = 0;
	rsPlayInfo[cnt].dwSkill_SpiritElemental_Param = 0;

	rsPlayInfo[cnt].dwSkill_DancingSword_Time = 0;
	rsPlayInfo[cnt].dwSkill_DancingSword_Param = 0;
	rsPlayInfo[cnt].dwSkill_DancingSword_DelayTime = 0;

	rsPlayInfo[cnt].dwSkill_Vanish_Time = 0;
	rsPlayInfo[cnt].dwSkill_Vanish_Param = 0;

	rsPlayInfo[cnt].dwSkill_Compulsion_Time = 0;
	rsPlayInfo[cnt].dwSkill_Compulsion_Param = 0;

	rsPlayInfo[cnt].dwSkill_MagneticSphere_Time = 0;
	rsPlayInfo[cnt].dwSkill_MagneticSphere_Param = 0;

	rsPlayInfo[cnt].dwSkill_Berserker_Time = 0;
	rsPlayInfo[cnt].dwSkill_Berserker_Param = 0;

	rsPlayInfo[cnt].dwSkill_AssassinEye_Time = 0;
	rsPlayInfo[cnt].dwSkill_AssassinEye_Param = 0;

	rsPlayInfo[cnt].dwSkill_Vague_Time = 0;
	rsPlayInfo[cnt].dwSkill_Vague_Param = 0;

	rsPlayInfo[cnt].dwSkill_ForceOfNature_Time = 0;

	rsPlayInfo[cnt].dwSkill_GodlyShied_Time = 0;
	rsPlayInfo[cnt].dwSkill_GodlyShied_Param = 0;

	rsPlayInfo[cnt].dwSkill_GodsBless_Time = 0;
	rsPlayInfo[cnt].dwSkill_GodsBless_Param = 0;

	rsPlayInfo[cnt].dwSkill_HallOfValhalla_Time = 0;

	rsPlayInfo[cnt].dwSkill_FrostJavelin_Time = 0;
	rsPlayInfo[cnt].dwSkill_FrostJavelin_Param = 0;

	rsPlayInfo[cnt].dwSkill_RegenerationField_Time = 0;

	rsPlayInfo[cnt].dwSkill_SummonMuspell_Time = 0;
	rsPlayInfo[cnt].dwSkill_SummonMuspell_Param = 0;




	rsPlayInfo[cnt].dwCurse_Attack_Time = 0;
	rsPlayInfo[cnt].dwCurse_Defence_Time = 0;



	rsPlayInfo[cnt].dwForceOrb_Code = 0;
	rsPlayInfo[cnt].dwForceOrb_Time = 0;
	rsPlayInfo[cnt].dwForceOrb_Damage = 0;

	rsPlayInfo[cnt].dwForceOrb_SaveCode = 0;
	rsPlayInfo[cnt].dwForceOrb_SaveTime = 0;
	rsPlayInfo[cnt].dwForceOrb_SaveDamage = 0;
	rsPlayInfo[cnt].dwForceOrb_NextSetTime = 0;


	rsPlayInfo[cnt].dwLifeBooster_Code = 0;
	rsPlayInfo[cnt].dwLifeBooster_Time = 0;
	rsPlayInfo[cnt].dwLifeBooster_Data = 0;

	rsPlayInfo[cnt].dwLifeBooster_SaveCode = 0;
	rsPlayInfo[cnt].dwLifeBooster_SaveTime = 0;
	rsPlayInfo[cnt].dwLifeBooster_SaveData = 0;
	rsPlayInfo[cnt].dwLifeBooster_NextSetTime = 0;

	rsPlayInfo[cnt].dwManaBooster_Code = 0;
	rsPlayInfo[cnt].dwManaBooster_Time = 0;
	rsPlayInfo[cnt].dwManaBooster_Data = 0;

	rsPlayInfo[cnt].dwManaBooster_SaveCode = 0;
	rsPlayInfo[cnt].dwManaBooster_SaveTime = 0;
	rsPlayInfo[cnt].dwManaBooster_SaveData = 0;
	rsPlayInfo[cnt].dwManaBooster_NextSetTime = 0;

	rsPlayInfo[cnt].dwStaminaBooster_Code = 0;
	rsPlayInfo[cnt].dwStaminaBooster_Time = 0;
	rsPlayInfo[cnt].dwStaminaBooster_Data = 0;

	rsPlayInfo[cnt].dwStaminaBooster_SaveCode = 0;
	rsPlayInfo[cnt].dwStaminaBooster_SaveTime = 0;
	rsPlayInfo[cnt].dwStaminaBooster_SaveData = 0;
	rsPlayInfo[cnt].dwStaminaBooster_NextSetTime = 0;


	rsPlayInfo[cnt].dwSkillDelay_Code = 0;
	rsPlayInfo[cnt].dwSkillDelay_Time = 0;
	rsPlayInfo[cnt].dwSkillDelay_Data = 0;

	rsPlayInfo[cnt].dwSkillDelay_SaveCode = 0;
	rsPlayInfo[cnt].dwSkillDelay_SaveTime = 0;
	rsPlayInfo[cnt].dwSkillDelay_SaveData = 0;
	rsPlayInfo[cnt].dwSkillDelay_NextSetTime = 0;



	rsPlayInfo[cnt].dwPrimeItem_NextSetTime = 0;
	rsPlayInfo[cnt].dwTime_PrimeItem_X2 = 0;
	rsPlayInfo[cnt].dwTime_PrimeItem_ExpUp = 0;

	rsPlayInfo[cnt].dwTime_PrimeItem_VampCuspid = 0;
	rsPlayInfo[cnt].dwTime_PrimeItem_VampCuspid_EX = 0;
	rsPlayInfo[cnt].dwTime_PrimeItem_ManaRecharg = 0;
	rsPlayInfo[cnt].dwTime_PrimeItem_ManaReduce = 0;
	rsPlayInfo[cnt].dwTime_PrimeItem_MightofAwell = 0;
	rsPlayInfo[cnt].dwTime_PrimeItem_MightofAwell2 = 0;
	rsPlayInfo[cnt].dwTime_PrimeItem_PhenixPet = 0;
	rsPlayInfo[cnt].dwTime_PrimeItem_HelpPet = 0;
	rsPlayInfo[cnt].dwTime_PrimeItem_StaminaReduce = 0;

	rsPlayInfo[cnt].dwPrimeItem_PackageCode = 0;



	rsPlayInfo[cnt].dwPCBang_Pet_AttackTime = 0;
	rsPlayInfo[cnt].dwPCBang_Pet_NextSetTime = 0;

	rsPlayInfo[cnt].lpLinkChar = 0;


	((DWORD *)rsPlayInfo[cnt].sBlessCastle_Damage)[0] = 0;
	rsPlayInfo[cnt].dwCheck_MasterClanTime = 0;

	rsPlayInfo[cnt].CastleMaster.Flag = 0;
	rsPlayInfo[cnt].dwBlessSkill_Code = 0;
	rsPlayInfo[cnt].dwBlessSkill_Time = 0;

	rsPlayInfo[cnt].dwSiegeItem_Scroll_Time = 0;
	rsPlayInfo[cnt].dwSiegeItem_Scroll_Code = 0;
	rsPlayInfo[cnt].dwSiegeItem_Stone1_Time = 0;
	rsPlayInfo[cnt].dwSiegeItem_Stone1_Code = 0;
	rsPlayInfo[cnt].dwSiegeItem_Stone2_Time = 0;
	rsPlayInfo[cnt].dwSiegeItem_Stone2_Code = 0;



	((DWORD *)rsPlayInfo[cnt].sLimitDamage)[0] = 0;
	((DWORD *)rsPlayInfo[cnt].sLimitCritical)[0] = 0;

	((DWORD *)rsPlayInfo[cnt].sLowLevel_PresentItem)[0] = 0;
	rsPlayInfo[cnt].dwStartUser_PresentItem_Time = 0;
	rsPlayInfo[cnt].dwStartUser_PresentItem_Count = 0;

	((DWORD *)rsPlayInfo[cnt].sCheckPlayField_Count)[0] = 0;

	rsPlayInfo[cnt].ClanTicketCode = 0;

	rsPlayInfo[cnt].dwDecPacketCode = 0;
	rsPlayInfo[cnt].dwDecPacketTime = 0;

	ZeroMemory(rsPlayInfo[cnt].dwSendFrames, CONNECTMAX * sizeof(DWORD));
	ZeroMemory(rsPlayInfo[cnt].InvenItemInfo, INVEN_ITEM_INFO_MAX * sizeof(sTHROW_ITEM_INFO));
	rsPlayInfo[cnt].OpenWarehouseInfoFlag = 0;
	rsPlayInfo[cnt].TradePotionInfoCount = 0;
	rsPlayInfo[cnt].MyShopListCount = 0;
	rsPlayInfo[cnt].dwMyShopTradeTime = 0;

	rsPlayInfo[cnt].dwTradeMsgCode = 0;
	rsPlayInfo[cnt].dwHaQuestItemCount = 0;



	rsPlayInfo[cnt].szUserExpTimeID[0] = 0;
	rsPlayInfo[cnt].szUserExpTimeName[0] = 0;
	rsPlayInfo[cnt].dwExpGameTime = 0;
	rsPlayInfo[cnt].dwExpGameTimeCheck = 0;

	if(rsPlayInfo[cnt].lpRecordDataBuff)
	{
		((TRANS_RECORD_DATA *)rsPlayInfo[cnt].lpRecordDataBuff)->size = 0;
		rsPlayInfo[cnt].dwRecordDataTime = dwPlayServTime;

		if(rsPlayInfo[cnt].lpRecordDataBuff != (rsRecordDataBuff + ((srRECORD_MEMORY_SIZE + 256)*cnt)))
		{
			TransCommand.WParam = 10007;
			TransCommand.LParam = (int)rsRecordDataBuff + ((srRECORD_MEMORY_SIZE + 256)*cnt);
			TransCommand.SParam = (int)rsPlayInfo[cnt].lpRecordDataBuff;
			RecordHackLogFile(&rsPlayInfo[cnt], &TransCommand);
		}
	}
	else
		rsPlayInfo[cnt].dwRecordDataTime = 0;


	dwConnectCount++;


	TransCommand.code = OpCode::OPCODE_VERSION;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = Server_LimitVersion;
	TransCommand.LParam = 0;

	lpsmSock->Send((char *)&TransCommand, TransCommand.size, TRUE);


	return TRUE;
}


int IsStgArea(STG_AREA *lpStgArea)
{
	for(int cnt = 0; cnt < STAGE_AREA_MAX; cnt++)
	{
		if(lpStgArea == &StageArea[cnt])
			return TRUE;
	}
	return FALSE;
}



int	rsSendServerNoticeToUser(rsPLAYINFO *lpPlayInfo)
{
	TRANS_CHATMESSAGE	TransChatMessage;

	wsprintf(TransChatMessage.szMessage, srMsg_011, rsNoticeMessage.szMessage);
	TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
	TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
	TransChatMessage.dwIP = 3;
	TransChatMessage.dwObjectSerial = 0;

	if(lpPlayInfo->lpsmSock)
		lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);

	lpPlayInfo->dwNoticeCount = rsNoticeMessage.Counter;

	return TRUE;
}


int	rsSetNoticeMessage(char *szMessage)
{
	strcpy_s(rsNoticeMessage.szMessage, szMessage);
	rsNoticeMessage.Counter++;

	return rsNoticeMessage.Counter;
}



int	SendSaveClientData(rsPLAYINFO *lpPlayInfo)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.code = OpCode::OPCODE_SAVECLIENT;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	if(lpPlayInfo && lpPlayInfo->lpsmSock)
	{
		lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
	}

	return TRUE;
}


int	rsSendCloseClient(rsPLAYINFO *lpPlayInfo)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.code = OpCode::OPCODE_CLOSECLIENT;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	if(lpPlayInfo && lpPlayInfo->lpsmSock)
	{
		lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
	}

	return TRUE;
}


int	rsRecordFixExp(rsPLAYINFO *lpPlayInfo)
{
	smTRANS_COMMAND	smTransCommand;
	int tExp;

	if(lpPlayInfo->RecordWarningExp)
	{

		tExp = lpPlayInfo->dwGameServerExp[0] + lpPlayInfo->dwGameServerExp[1] + lpPlayInfo->dwGameServerExp[2] + lpPlayInfo->dwGameServerExp[3] +
			lpPlayInfo->dwGameServerExp[4] + lpPlayInfo->dwGameServerExp[5] + lpPlayInfo->dwGameServerExp[6] + lpPlayInfo->dwGameServerExp[7];

		smTransCommand.WParam = 6630;
		smTransCommand.LParam = lpPlayInfo->smCharInfo.Level;
		smTransCommand.SParam = lpPlayInfo->RecordWarningExp / 1000;
		smTransCommand.EParam = (int)((tExp + lpPlayInfo->spExp_Start) / 1000);
		RecordHackLogFile(lpPlayInfo, &smTransCommand);


	}
	return TRUE;
}


int SaveThrowItemOver(rsPLAYINFO *lpPlayInfo, DWORD dwCode, DWORD dwKey, DWORD dwSum)
{
	int cnt;
	int LowCount;
	DWORD	LowCode;
	DWORD	Code;

	if(lpPlayInfo->ThrowItemCount <= 0) return FALSE;

	LowCount = 0;
	LowCode = lpPlayInfo->ThrowItemInfo[LowCount].dwCode & sinITEM_MASK3;

	for(cnt = 1; cnt < lpPlayInfo->ThrowItemCount; cnt++)
	{
		Code = lpPlayInfo->ThrowItemInfo[cnt].dwCode & sinITEM_MASK3;
		if(Code < LowCode)
		{
			LowCode = Code;
			LowCount = cnt;
		}
	}

	lpPlayInfo->ThrowItemInfo[LowCount].dwCode = dwCode;
	lpPlayInfo->ThrowItemInfo[LowCount].dwKey = dwKey;
	lpPlayInfo->ThrowItemInfo[LowCount].dwSum = dwSum;

	return TRUE;
}



int SaveThrowItem(rsPLAYINFO *lpPlayInfo, DWORD dwCode, DWORD dwKey, DWORD dwSum)
{
	int cnt;

	if((dwCode&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1)) return TRUE;

	for(cnt = 0; cnt < lpPlayInfo->ThrowItemCount; cnt++)
	{
		if(lpPlayInfo->ThrowItemInfo[cnt].dwCode == dwCode &&
			lpPlayInfo->ThrowItemInfo[cnt].dwKey == dwKey &&
			lpPlayInfo->ThrowItemInfo[cnt].dwSum == dwSum)
		{

			return TRUE;
		}
	}


	if(lpPlayInfo->ThrowItemCount >= THROW_ITEM_INFO_MAX - 1)
	{

		return SaveThrowItemOver(lpPlayInfo, dwCode, dwKey, dwSum);
	}

	lpPlayInfo->ThrowItemInfo[lpPlayInfo->ThrowItemCount].dwCode = dwCode;
	lpPlayInfo->ThrowItemInfo[lpPlayInfo->ThrowItemCount].dwKey = dwKey;
	lpPlayInfo->ThrowItemInfo[lpPlayInfo->ThrowItemCount].dwSum = dwSum;

	if(lpPlayInfo->ThrowItemCount < THROW_ITEM_INFO_MAX - 1)
	{
		lpPlayInfo->ThrowItemCount++;

		if(lpPlayInfo->ThrowItemCount == THROW_ITEM_INFO_MAX - 32 ||
			lpPlayInfo->ThrowItemCount > THROW_ITEM_INFO_MAX - 48)
		{

			SendSaveClientData(lpPlayInfo);
		}
	}

	return TRUE;
}


int SaveThrowItem2(rsPLAYINFO *lpPlayInfo, DWORD dwCode, DWORD dwKey, DWORD dwSum)
{
	int cnt;

	if((dwCode&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1)) return TRUE;

	for(cnt = 0; cnt < lpPlayInfo->ThrowItemCount; cnt++)
	{
		if(lpPlayInfo->ThrowItemInfo[cnt].dwCode == dwCode &&
			lpPlayInfo->ThrowItemInfo[cnt].dwKey == dwKey &&
			lpPlayInfo->ThrowItemInfo[cnt].dwSum == dwSum)
		{

			return TRUE;
		}
	}

	if(lpPlayInfo->ThrowItemCount >= THROW_ITEM_INFO_MAX - 1)
	{

		return SaveThrowItemOver(lpPlayInfo, dwCode, dwKey, dwSum);
	}

	lpPlayInfo->ThrowItemInfo[lpPlayInfo->ThrowItemCount].dwCode = dwCode;
	lpPlayInfo->ThrowItemInfo[lpPlayInfo->ThrowItemCount].dwKey = dwKey;
	lpPlayInfo->ThrowItemInfo[lpPlayInfo->ThrowItemCount].dwSum = dwSum;

	if(lpPlayInfo->ThrowItemCount < THROW_ITEM_INFO_MAX - 1)
	{
		lpPlayInfo->ThrowItemCount++;
	}

	return TRUE;
}


int SaveThrowItems(rsPLAYINFO *lpPlayInfo, TRANS_THROW_ITEMS	*lpTransThrowItems)
{
	int cnt;

	for(cnt = 0; cnt < lpTransThrowItems->ThrowItemCount; cnt++)
	{
		if(lpPlayInfo->ThrowItemCount >= THROW_ITEM_INFO_MAX - 1)
		{

			SaveThrowItemOver(lpPlayInfo,
				lpTransThrowItems->ThrowItems[cnt].dwCode,
				lpTransThrowItems->ThrowItems[cnt].dwHead,
				lpTransThrowItems->ThrowItems[cnt].dwChkSum);
		}
		else
		{
			lpPlayInfo->ThrowItemInfo[lpPlayInfo->ThrowItemCount].dwCode = lpTransThrowItems->ThrowItems[cnt].dwCode;
			lpPlayInfo->ThrowItemInfo[lpPlayInfo->ThrowItemCount].dwKey = lpTransThrowItems->ThrowItems[cnt].dwHead;
			lpPlayInfo->ThrowItemInfo[lpPlayInfo->ThrowItemCount].dwSum = lpTransThrowItems->ThrowItems[cnt].dwChkSum;
			lpPlayInfo->ThrowItemCount++;
		}
	}

	return TRUE;
}


int	rsFindInvenItem(rsPLAYINFO *lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum)
{
	int cnt;

	if(!rsServerConfig.ServerInventoryMode) return INVEN_ITEM_INFO_MAX;


	if((dwCode&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1) || dwCode == (sinGG1 | sin01)) return INVEN_ITEM_INFO_MAX;

	for(cnt = 0; cnt < INVEN_ITEM_INFO_MAX; cnt++)
	{
		if(lpPlayInfo->InvenItemInfo[cnt].dwCode &&
			lpPlayInfo->InvenItemInfo[cnt].dwCode == dwCode &&
			lpPlayInfo->InvenItemInfo[cnt].dwKey == dwHead &&
			lpPlayInfo->InvenItemInfo[cnt].dwSum == dwChkSum)
		{

			return cnt;
		}
	}


	if(lpPlayInfo->OpenWarehouseInfoFlag)
	{
		for(cnt = 0; cnt < 100; cnt++)
		{
			if(lpPlayInfo->WareHouseItemInfo[cnt].dwCode &&
				lpPlayInfo->WareHouseItemInfo[cnt].dwCode == dwCode &&
				lpPlayInfo->WareHouseItemInfo[cnt].dwKey == dwHead &&
				lpPlayInfo->WareHouseItemInfo[cnt].dwSum == dwChkSum)
			{

				return INVEN_ITEM_INFO_MAX;
			}
		}
	}

	return -1;
}


int	rsCheckInvenItem(rsPLAYINFO *lpPlayInfo, DWORD dwCode)
{
	int cnt;

	if(!rsServerConfig.ServerInventoryMode) return INVEN_ITEM_INFO_MAX;


	if((dwCode&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1) || dwCode == (sinGG1 | sin01)) return INVEN_ITEM_INFO_MAX;

	for(cnt = 0; cnt < INVEN_ITEM_INFO_MAX; cnt++)
	{
		if(lpPlayInfo->InvenItemInfo[cnt].dwCode &&
			lpPlayInfo->InvenItemInfo[cnt].dwCode == dwCode)
		{
			return cnt;
		}
	}


	if(lpPlayInfo->OpenWarehouseInfoFlag)
	{
		for(cnt = 0; cnt < 100; cnt++)
		{
			if(lpPlayInfo->WareHouseItemInfo[cnt].dwCode &&
				lpPlayInfo->WareHouseItemInfo[cnt].dwCode == dwCode)
			{
				return INVEN_ITEM_INFO_MAX;
			}
		}
	}

	return -1;
}



int	rsDeleteInvenItem(rsPLAYINFO *lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum)
{
	int cnt;

	if(!rsServerConfig.ServerInventoryMode) return INVEN_ITEM_INFO_MAX;


	if((dwCode&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1) || dwCode == (sinGG1 | sin01)) return INVEN_ITEM_INFO_MAX;

	for(cnt = 0; cnt < INVEN_ITEM_INFO_MAX; cnt++)
	{
		if(lpPlayInfo->InvenItemInfo[cnt].dwCode &&
			lpPlayInfo->InvenItemInfo[cnt].dwCode == dwCode &&
			lpPlayInfo->InvenItemInfo[cnt].dwKey == dwHead &&
			lpPlayInfo->InvenItemInfo[cnt].dwSum == dwChkSum)
		{

			lpPlayInfo->InvenItemInfo[cnt].dwCode = 0;
			return cnt;
		}
	}

	if(lpPlayInfo->OpenWarehouseInfoFlag)
	{
		for(cnt = 0; cnt < 100; cnt++)
		{
			if(lpPlayInfo->WareHouseItemInfo[cnt].dwCode &&
				lpPlayInfo->WareHouseItemInfo[cnt].dwCode == dwCode &&
				lpPlayInfo->WareHouseItemInfo[cnt].dwKey == dwHead &&
				lpPlayInfo->WareHouseItemInfo[cnt].dwSum == dwChkSum)
			{

				lpPlayInfo->WareHouseItemInfo[cnt].dwCode = 0;
				return INVEN_ITEM_INFO_MAX;
			}
		}
	}


	return -1;
}


int	rsAddInvenItem(rsPLAYINFO *lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum)
{
	int	cnt;
	int	Empty;


	if(!rsServerConfig.ServerInventoryMode) return INVEN_ITEM_INFO_MAX;


	if((dwCode&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1) || dwCode == (sinGG1 | sin01)) return INVEN_ITEM_INFO_MAX;

	Empty = -1;

	for(cnt = 0; cnt < INVEN_ITEM_INFO_MAX; cnt++)
	{
		if(lpPlayInfo->InvenItemInfo[cnt].dwCode)
		{
			if(lpPlayInfo->InvenItemInfo[cnt].dwCode == dwCode &&
				lpPlayInfo->InvenItemInfo[cnt].dwKey == dwHead &&
				lpPlayInfo->InvenItemInfo[cnt].dwSum == dwChkSum)
			{

				return cnt;
			}
		}
		else
		{
			Empty = cnt;
		}
	}

	if(lpPlayInfo->OpenWarehouseInfoFlag)
	{
		for(cnt = 0; cnt < 100; cnt++)
		{
			if(lpPlayInfo->WareHouseItemInfo[cnt].dwCode &&
				lpPlayInfo->WareHouseItemInfo[cnt].dwCode == dwCode &&
				lpPlayInfo->WareHouseItemInfo[cnt].dwKey == dwHead &&
				lpPlayInfo->WareHouseItemInfo[cnt].dwSum == dwChkSum)
			{

				return INVEN_ITEM_INFO_MAX;
			}
		}
	}

	if(Empty >= 0)
	{
		lpPlayInfo->InvenItemInfo[Empty].dwCode = dwCode;
		lpPlayInfo->InvenItemInfo[Empty].dwKey = dwHead;
		lpPlayInfo->InvenItemInfo[Empty].dwSum = dwChkSum;
		return Empty;
	}

	smTRANS_COMMAND	smTransCommand;

	smTransCommand.WParam = 8050;
	smTransCommand.LParam = dwCode;
	smTransCommand.SParam = Empty;
	smTransCommand.EParam = (int)lpPlayInfo->OpenWarehouseInfoFlag;
	RecordHackLogFile(lpPlayInfo, &smTransCommand);



	return -1;
}


int rsGetServerPotion(rsPLAYINFO *lpPlayInfo, DWORD dwPotionCode)
{
	int x = -1, y = -1;

	switch(dwPotionCode)
	{
	case (sinPL1 | sin01):
		x = 0; y = 0;
		break;
	case (sinPL1 | sin02):
		x = 0; y = 1;
		break;
	case (sinPL1 | sin03):
		x = 0; y = 2;
		break;
	case (sinPL1 | sin04):
		x = 0; y = 3;
		break;

	case (sinPM1 | sin01):
		x = 1; y = 0;
		break;
	case (sinPM1 | sin02):
		x = 1; y = 1;
		break;
	case (sinPM1 | sin03):
		x = 1; y = 2;
		break;
	case (sinPM1 | sin04):
		x = 1; y = 3;
		break;

	case (sinPS1 | sin01):
		x = 2; y = 0;
		break;
	case (sinPS1 | sin02):
		x = 2; y = 1;
		break;
	case (sinPS1 | sin03):
		x = 2; y = 2;
		break;
	case (sinPS1 | sin04):
		x = 2; y = 3;
		break;
	}

	if(x >= 0 && y >= 0)
		return lpPlayInfo->ServerPotion[x][y];

	return 0;

}


int rsAddServerPotion(rsPLAYINFO *lpPlayInfo, DWORD dwPotionCode, int PotionCount)
{
	int Count = PotionCount;
	int x, y, pos;

	if(!rsServerConfig.PotionMonitor) return FALSE;

	x = -1;
	y = -1;
	pos = 0;

	switch(dwPotionCode)
	{
	case (sinPL1 | sin01):
		x = 0; y = 0;
		break;
	case (sinPL1 | sin02):
		x = 0; y = 1;
		break;
	case (sinPL1 | sin03):
		x = 0; y = 2;
		break;
	case (sinPL1 | sin04):
		x = 0; y = 3;
		break;

	case (sinPM1 | sin01):
		x = 1; y = 0;
		break;
	case (sinPM1 | sin02):
		x = 1; y = 1;
		break;
	case (sinPM1 | sin03):
		x = 1; y = 2;
		break;
	case (sinPM1 | sin04):
		x = 1; y = 3;
		break;

	case (sinPS1 | sin01):
		x = 2; y = 0;
		break;
	case (sinPS1 | sin02):
		x = 2; y = 1;
		break;
	case (sinPS1 | sin03):
		x = 2; y = 2;
		break;
	case (sinPS1 | sin04):
		x = 2; y = 3;
		break;
	}

	pos = lpPlayInfo->ServerPotion[x][y] + Count;

	if(pos < 0 && Count < 0)
	{
		lpPlayInfo->ServerPotion[x][y] = 0;
		return pos;
	}

	lpPlayInfo->ServerPotion[x][y] = pos;




	return pos;
}


int rsServerPotionErrorLOG(rsPLAYINFO *lpPlayInfo, DWORD dwCode, int Count, int Position)
{
	smTRANS_COMMAND_EX	smTransCommandEx;

	if(lpPlayInfo->WarningCount < 3)
	{

		smTransCommandEx.WParam = 8810;
		smTransCommandEx.LParam = dwCode;
		smTransCommandEx.SParam = Count;
		smTransCommandEx.EParam = Position;
		RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
	}

	return TRUE;
}



int	rsGetTradePotionInfo(rsPLAYINFO *lpPlayInfo, DWORD dwCode)
{
	int cnt;

	for(cnt = 0; cnt < lpPlayInfo->TradePotionInfoCount; cnt++)
	{
		if(lpPlayInfo->dwTradePotionInfo[cnt] == dwCode)
		{
			return TRUE;
		}
	}

	return FALSE;
}


int	rsAddTradePotionInfo(rsPLAYINFO *lpPlayInfo, DWORD	dwCode)
{

	if(lpPlayInfo->TradePotionInfoCount >= 16) return FALSE;

	if(rsGetTradePotionInfo(lpPlayInfo, dwCode) == TRUE) return TRUE;

	lpPlayInfo->dwTradePotionInfo[lpPlayInfo->TradePotionInfoCount++] = dwCode;

	return TRUE;
}




int	rsTradeInvenItem(rsPLAYINFO *lpPlayInfo, rsPLAYINFO *lpPlayInfo2, TRANS_TRADE_ITEMKEY *lpTransTradeItemKey)
{
	int cnt;
	int money;
	smTRANS_COMMAND_EX	smTransCommand;
	DWORD	dwTradeCode;
	DWORD	dwTradeTime;
	int	PotionCount;

	if(!lpPlayInfo || !lpPlayInfo2) return FALSE;


	dwTradeCode = (lpTransTradeItemKey->Money * lpPlayInfo->dwObjectSerial + lpPlayInfo2->dwObjectSerial);
	for(cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
	{
		if(lpTransTradeItemKey->dwItemCode[cnt])
		{
			dwTradeCode += (lpTransTradeItemKey->dwItemCode[cnt] + lpTransTradeItemKey->dwItemKey[cnt] +
				lpTransTradeItemKey->dwItemSum[cnt])*(cnt + 2);
		}
	}
	dwTradeTime = dwPlayServTime;

	if((dwTradeTime - lpPlayInfo->dwLastTradeTime) < 8000 && lpPlayInfo->dwLastTradeChksum == dwTradeCode)
	{

		for(cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
		{
			if(lpTransTradeItemKey->dwItemCode[cnt])
			{
				if((lpTransTradeItemKey->dwItemCode[cnt] & sinITEM_MASK1) != (sinPM1&sinITEM_MASK1))
				{
					if(rsDeleteInvenItem(lpPlayInfo,
						lpTransTradeItemKey->dwItemCode[cnt],
						lpTransTradeItemKey->dwItemKey[cnt],
						lpTransTradeItemKey->dwItemSum[cnt]) >= 0)
					{


						smTransCommand.WParam = 8000;
						smTransCommand.WxParam = 31;
						smTransCommand.LxParam = (int)"*TRADE CHECKING ERROR*";
						smTransCommand.LParam = lpTransTradeItemKey->dwItemCode[cnt];
						smTransCommand.SParam = lpTransTradeItemKey->dwItemKey[cnt];
						smTransCommand.EParam = lpTransTradeItemKey->dwItemSum[cnt];
						RecordHackLogFile(lpPlayInfo, &smTransCommand);
					}
				}
			}
		}
		return TRUE;
	}

	lpPlayInfo->TradePotionInfoCount = 0;

	if(lpTransTradeItemKey->Money)
	{

		money = lpTransTradeItemKey->Money - 193;
		if(lpPlayInfo->ServerMoney < money)
		{


			smTransCommand.WParam = 8010;
			smTransCommand.LParam = 30;
			smTransCommand.SParam = lpPlayInfo->ServerMoney;
			smTransCommand.EParam = money;
			RecordHackLogFile(lpPlayInfo, &smTransCommand);


			return FALSE;
		}

		lpPlayInfo->SubServerMoney(money, WHERE_TRADE);
		lpPlayInfo2->AddServerMoney(money, WHERE_TRADE);
	}

	for(cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
	{
		if(lpTransTradeItemKey->dwItemCode[cnt])
		{

			if((lpTransTradeItemKey->dwItemCode[cnt] & sinITEM_MASK1) != (sinPM1&sinITEM_MASK1))
			{
				if(rsDeleteInvenItem(lpPlayInfo, lpTransTradeItemKey->dwItemCode[cnt],
					lpTransTradeItemKey->dwItemKey[cnt],
					lpTransTradeItemKey->dwItemSum[cnt]) < 0)
				{


					smTransCommand.WParam = 8000;
					smTransCommand.WxParam = 30;
					smTransCommand.LxParam = (int)"*TRADE ITEM*";
					smTransCommand.LParam = lpTransTradeItemKey->dwItemCode[cnt];
					smTransCommand.SParam = lpTransTradeItemKey->dwItemKey[cnt];
					smTransCommand.EParam = lpTransTradeItemKey->dwItemSum[cnt];
					RecordHackLogFile(lpPlayInfo, &smTransCommand);


					lpTransTradeItemKey->dwItemKey[cnt] = 0;

				}
			}
			else
			{



				PotionCount = 0x5cbc ^ (lpTransTradeItemKey->dwItemSum[cnt] >> 16) ^ lpTransTradeItemKey->dwItemSum[cnt];
				PotionCount &= 0xFFFF;

				if(rsAddServerPotion(lpPlayInfo, lpTransTradeItemKey->dwItemCode[cnt], -PotionCount) < 0)
				{

					rsServerPotionErrorLOG(lpPlayInfo, lpTransTradeItemKey->dwItemCode[cnt], -PotionCount, 100);
					return FALSE;
				}
				rsAddServerPotion(lpPlayInfo2, lpTransTradeItemKey->dwItemCode[cnt], PotionCount);


				rsAddTradePotionInfo(lpPlayInfo, lpTransTradeItemKey->dwItemCode[cnt]);
			}

			if(lpTransTradeItemKey->dwItemKey[cnt])
			{
				rsAddInvenItem(lpPlayInfo2, lpTransTradeItemKey->dwItemCode[cnt],
					lpTransTradeItemKey->dwItemKey[cnt],
					lpTransTradeItemKey->dwItemSum[cnt]);


				SaveThrowItem2(lpPlayInfo, lpTransTradeItemKey->dwItemCode[cnt], lpTransTradeItemKey->dwItemKey[cnt], lpTransTradeItemKey->dwItemSum[cnt]);
			}

		}
	}

	lpPlayInfo->dwLastTradeTime = dwTradeTime;
	lpPlayInfo->dwLastTradeChksum = dwTradeCode;


	rsRecord_ItemLog_Trade(lpPlayInfo, lpPlayInfo2, lpTransTradeItemKey);

	return TRUE;
}


int SendChatMessage()
{
	int cnt;
	TRANS_CHATBUFF	tChatBuff;
	rsPLAYINFO	*lpPlayInfo;
	CHATBUFF	*lpChatBuff;
	int len;

	for(cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		lpPlayInfo = &rsPlayInfo[cnt];
		if(lpPlayInfo->lpsmSock && rsPlayInfo[cnt].dwObjectSerial && lpPlayInfo->ChatBuffCnt < ChatBuffCnt)
		{

			if((ChatBuffCnt - lpPlayInfo->ChatBuffCnt) > 32)
			{
				lpPlayInfo->ChatBuffCnt = ChatBuffCnt - 8;
			}

			lpChatBuff = &ChatBuff[lpPlayInfo->ChatBuffCnt & CHATBUFF_MASK];

			len = sizeof(TRANS_CHATBUFF) + lstrlen(lpChatBuff->szMessage) + 1;

			tChatBuff.code = OpCode::OPCODE_CHATMESSAGE;
			tChatBuff.dwIP = lpChatBuff->dwIP;
			tChatBuff.size = len;
			memcpy(TransTemp, &tChatBuff, sizeof(TRANS_CHATBUFF));
			strcpy_s(TransTemp + sizeof(TRANS_CHATBUFF), sizeof(TransTemp) - sizeof(TRANS_CHATBUFF), lpChatBuff->szMessage);
			if(lpPlayInfo->lpsmSock->Send(TransTemp, len, TRUE) == TRUE)
			{
				lpPlayInfo->ChatBuffCnt++;
			}
		}
	}

	return TRUE;
}



int SendShopItemList(smWINSOCK *lpsmSock, smCHAR *lpChar)
{
	int cnt;
	char szBuff[smSOCKBUFF_SIZE];
	smTRANS_SELL_ITEM	*lpTransSellItem;
	sDEF_ITEMINFO		*lpDefItem;
	char *lpBuff;
	int TransLen;
	int	ItemCount;



	lpTransSellItem = (smTRANS_SELL_ITEM *)szBuff;

	lpTransSellItem->code = OpCode::OPCODE_SHOP_ITEMLIST;

	if(lpChar->smMonsterInfo.SellAttackItemCount)
	{
		ItemCount = 0;

		lpBuff = ((char *)lpTransSellItem) + sizeof(smTRANS_SELL_ITEM);
		TransLen = sizeof(smTRANS_SELL_ITEM);
		for(cnt = 0; cnt < lpChar->smMonsterInfo.SellAttackItemCount; cnt++)
		{
			lpDefItem = (sDEF_ITEMINFO *)lpChar->smMonsterInfo.SellAttackItem[cnt];
			if(lpDefItem && (TransLen + lpDefItem->DefCompressDataLen) < smSOCKBUFF_SIZE)
			{
				memcpy(lpBuff, lpDefItem->DefCompressData, lpDefItem->DefCompressDataLen);
				TransLen += lpDefItem->DefCompressDataLen;
				lpBuff += lpDefItem->DefCompressDataLen;
				ItemCount++;
			}
		}
		lpTransSellItem->size = TransLen;
		lpTransSellItem->ItemKind = 1;
		lpTransSellItem->ItemCounter = ItemCount;
		lpsmSock->Send((char *)lpTransSellItem, lpTransSellItem->size, TRUE);
	}


	if(lpChar->smMonsterInfo.SellDefenceItemCount)
	{
		ItemCount = 0;

		lpBuff = ((char *)lpTransSellItem) + sizeof(smTRANS_SELL_ITEM);
		TransLen = sizeof(smTRANS_SELL_ITEM);
		for(cnt = 0; cnt < lpChar->smMonsterInfo.SellDefenceItemCount; cnt++)
		{
			lpDefItem = (sDEF_ITEMINFO *)lpChar->smMonsterInfo.SellDefenceItem[cnt];
			if(lpDefItem && (TransLen + lpDefItem->DefCompressDataLen) < smSOCKBUFF_SIZE)
			{
				memcpy(lpBuff, lpDefItem->DefCompressData, lpDefItem->DefCompressDataLen);
				TransLen += lpDefItem->DefCompressDataLen;
				lpBuff += lpDefItem->DefCompressDataLen;
				ItemCount++;
			}
		}
		lpTransSellItem->size = TransLen;
		lpTransSellItem->ItemKind = 2;
		lpTransSellItem->ItemCounter = ItemCount;
		lpsmSock->Send((char *)lpTransSellItem, lpTransSellItem->size, TRUE);
	}


	if(lpChar->smMonsterInfo.SellEtcItemCount)
	{
		ItemCount = 0;

		lpBuff = ((char *)lpTransSellItem) + sizeof(smTRANS_SELL_ITEM);
		TransLen = sizeof(smTRANS_SELL_ITEM);
		for(cnt = 0; cnt < lpChar->smMonsterInfo.SellEtcItemCount; cnt++)
		{
			lpDefItem = (sDEF_ITEMINFO *)lpChar->smMonsterInfo.SellEtcItem[cnt];
			if(lpDefItem && (TransLen + lpDefItem->DefCompressDataLen) < smSOCKBUFF_SIZE)
			{
				memcpy(lpBuff, lpDefItem->DefCompressData, lpDefItem->DefCompressDataLen);
				TransLen += lpDefItem->DefCompressDataLen;
				lpBuff += lpDefItem->DefCompressDataLen;
				ItemCount++;
			}
		}
		lpTransSellItem->size = TransLen;
		lpTransSellItem->ItemKind = 3;
		lpTransSellItem->ItemCounter = ItemCount;
		lpsmSock->Send((char *)lpTransSellItem, lpTransSellItem->size, TRUE);
	}


	return TRUE;
}

int SendSkillMenu(smWINSOCK *lpsmSock, smCHAR *lpChar, int Mode)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = OpCode::OPCODE_SKILL_MENU;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = Mode;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;


	if(rsServerConfig.Disable_Quest == Mode)
		smTransCommand.WParam = FALSE;




	return lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
}


int SendWareHouseToClient(rsPLAYINFO *lpPlayInfo)
{

	if((lpPlayInfo->dwDataError&rsDATA_ERROR_WAREHOUSE) != 0)
		return FALSE;

	if(!lpPlayInfo->getAccount().empty() && !lpPlayInfo->szServerID[0] && ((TRANS_RECORD_DATA *)lpPlayInfo->lpRecordDataBuff)->size > 0)
	{

		return rsLoadWareHouseData(lpPlayInfo);
	}

	return FALSE;
}


int SendOpenWareHouse(smWINSOCK *lpsmSock)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = OpCode::OPCODE_OPEN_WAREHOUSE;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	return lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
}


int SendOpenMixItem(smWINSOCK *lpsmSock, int MixFlag)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = OpCode::OPCODE_OPEN_MIXITEM;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = MixFlag;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	return lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
}


int SendOpenSmelting(smWINSOCK *lpsmSock)
{
	smTRANS_COMMAND smTransCommand;

	smTransCommand.code = OpCode::OPCODE_OPEN_SMELTING;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	return lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
}

int SendOpenManufacture(smWINSOCK *lpsmSock)
{
	smTRANS_COMMAND smTransCommand;

	smTransCommand.code = OpCode::OPCODE_OPEN_MANUFACTURE;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	return lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
}


int SendOpenCollectMoney(smWINSOCK *lpsmSock)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = OpCode::OPCODE_OPEN_COLLECT;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	return lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
}


int SendOpenEventGift(smWINSOCK *lpsmSock)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = OpCode::OPCODE_OPEN_EVENTGIFT;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	return lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
}



int SendOpenGiftExpress(rsPLAYINFO *lpPlayInfo, DWORD	dwItemCode, DWORD dwPassCode_Param)
{
	if(rsLoadPostBox(lpPlayInfo) == FALSE) return FALSE;
	if(!lpPlayInfo->lpPostBoxItem) return FALSE;
	TRANS_CHATMESSAGE	TransChatMessage;

	if(lpPlayInfo->PostPassFailCount >= 5)
	{


		strcpy_s(TransChatMessage.szMessage, srMsg_301);
		TransChatMessage.code = OpCode::OPCODE_MESSAGEBOX;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		TransChatMessage.dwIP = 0;
		TransChatMessage.dwObjectSerial = 0;
		lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);

		return FALSE;
	}

	char	szBuff[sizeof(TRANS_POST_ITEM) + sizeof(sITEMINFO) + 64];
	TRANS_POST_ITEM	*lpTransPostItem = (TRANS_POST_ITEM *)szBuff;
	sITEMINFO *lpItem = (sITEMINFO *)(szBuff + sizeof(TRANS_POST_ITEM));
	int		cnt, cnt2;
	psITEM	psItem;
	int		spJobCode;
	DWORD	dwPassCode;
	DWORD	dwFormCode;
	char	*szPassCode;
	int		TempWeight = 0;

	ZeroMemory(lpTransPostItem, sizeof(TRANS_POST_ITEM));

	lpTransPostItem->code = OpCode::OPCODE_ITEM_EXPRESS;

	if(dwItemCode)
	{
		spJobCode = 0;
		dwPassCode = 0;
		dwFormCode = 0;
		szPassCode = 0;

		for(cnt = 0; cnt < lpPlayInfo->lpPostBoxItem->ItemCounter; cnt++)
		{
			if(lpPlayInfo->lpPostBoxItem->PostItem[cnt].Flag &&
				lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwItemCode == dwItemCode &&
				(lpPlayInfo->lpPostBoxItem->PostItem[cnt].szCharName[0] == '*' ||
					lstrcmpi(lpPlayInfo->getName().c_str(), lpPlayInfo->lpPostBoxItem->PostItem[cnt].szCharName) == 0))
			{

				spJobCode = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwJobCode;
				dwFormCode = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwFormCode;
				dwPassCode = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwPassCode;
				szPassCode = lpPlayInfo->lpPostBoxItem->PostItem[cnt].szPassCode;

				if(dwPassCode && dwPassCode != dwPassCode_Param)
				{

					cnt = lpPlayInfo->lpPostBoxItem->ItemCounter;
					lpPlayInfo->PostPassFailCount++;

					strcpy_s(TransChatMessage.szMessage, srMsg_300);
					TransChatMessage.code = OpCode::OPCODE_MESSAGEBOX;
					TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
					TransChatMessage.dwIP = 0;
					TransChatMessage.dwObjectSerial = 0;
					lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);

					break;
				}

				lpPlayInfo->lpPostBoxItem->PostItem[cnt].Flag = 0;
				break;
			}
		}
		if(cnt < lpPlayInfo->lpPostBoxItem->ItemCounter)
		{

			lpPlayInfo->PostPassFailCount = 0;

			if(dwItemCode == (sinGG1 | sin01))
			{
				lpTransPostItem->dwItemFlag = TRUE;
				ZeroMemory(lpItem, sizeof(sITEMINFO));
				lpItem->CODE = sinGG1 | sin01;
				lpItem->Money = spJobCode;
				ReformItem(lpItem);
				lpPlayInfo->AddServerMoney(spJobCode, WHERE_GIFT_EXPRESS);


				rsRecord_ItemLog_Post(lpPlayInfo, lpItem->CODE, 0, spJobCode, dwFormCode, szPassCode, ITEMLOG_EXPRESS);

			}
			else if(dwItemCode == (sinGG1 | sin02))
			{
				lpTransPostItem->dwItemFlag = TRUE;
				ZeroMemory(lpItem, sizeof(sITEMINFO));
				lpItem->CODE = sinGG1 | sin02;
				lpItem->Money = spJobCode;
				ReformItem(lpItem);
				lpPlayInfo->dwGameServerExp[rsServerConfig.ServerCode] += spJobCode;


				rsRecord_ItemLog_Post(lpPlayInfo, lpItem->CODE, 0, spJobCode, dwFormCode, szPassCode, ITEMLOG_EXPRESS);
			}
			else
			{
				for(cnt = 0; cnt < DefaultItemCount; cnt++)
				{
					if(DefaultItems[cnt].Item.CODE == dwItemCode && !DefaultItems[cnt].Item.UniqueItem)
					{
						CreateDefItem(&psItem.ItemInfo, &DefaultItems[cnt], spJobCode, 1);
						lpTransPostItem->dwItemFlag = TRUE;

						TempWeight = DefaultItems[cnt].Item.Weight;
						memcpy(lpItem, &psItem.ItemInfo, sizeof(sITEMINFO));

						if((dwItemCode&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
						{

							lpItem->PotionCount = spJobCode;

							rsAddServerPotion(lpPlayInfo, dwItemCode, lpItem->PotionCount);


							rsRecord_ItemLog_Post(lpPlayInfo, lpItem->CODE, 0, spJobCode, dwFormCode, szPassCode, ITEMLOG_EXPRESS);
						}
						else
						{

							rsAddInvenItem(lpPlayInfo, lpItem->CODE, lpItem->ItemHeader.Head, lpItem->ItemHeader.dwChkSum);


							rsRecord_ItemLog_Post(lpPlayInfo, lpItem->CODE, lpItem->ItemHeader.Head, lpItem->ItemHeader.dwChkSum,
								dwFormCode, szPassCode, ITEMLOG_EXPRESS);

						}

						break;
					}
				}
			}
		}
	}


	for(cnt = 0; cnt < lpPlayInfo->lpPostBoxItem->ItemCounter; cnt++)
	{
		if(lpPlayInfo->lpPostBoxItem->PostItem[cnt].Flag &&
			(lpPlayInfo->lpPostBoxItem->PostItem[cnt].szCharName[0] == '*' ||
				lstrcmpi(lpPlayInfo->getName().c_str(), lpPlayInfo->lpPostBoxItem->PostItem[cnt].szCharName) == 0))
		{

			if(lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwItemCode == (sinGG1 | sin01) ||
				lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwItemCode == (sinGG1 | sin02))
			{

				strcpy_s(lpTransPostItem->szItemName, lpPlayInfo->lpPostBoxItem->PostItem[cnt].szItemCode);
				strcpy_s(lpTransPostItem->szDoc, lpPlayInfo->lpPostBoxItem->PostItem[cnt].szDoc);

				lpTransPostItem->dwItemCode = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwItemCode;
				lpTransPostItem->dwItemJobCode = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwJobCode;
				lpTransPostItem->dwParam[0] = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwParam[0];
				lpTransPostItem->dwParam[1] = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwParam[1];
				lpTransPostItem->dwParam[2] = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwParam[2];
				lpTransPostItem->dwParam[3] = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwParam[3];

				lpTransPostItem->Weight = TempWeight;
				break;

			}
			else
			{

				for(cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if(DefaultItems[cnt2].Item.CODE == lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwItemCode &&
						!DefaultItems[cnt2].Item.UniqueItem)
					{
						strcpy_s(lpTransPostItem->szItemName, DefaultItems[cnt2].Item.ItemName);
						strcpy_s(lpTransPostItem->szDoc, lpPlayInfo->lpPostBoxItem->PostItem[cnt].szDoc);

						lpTransPostItem->dwItemCode = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwItemCode;
						lpTransPostItem->dwItemJobCode = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwJobCode;
						lpTransPostItem->dwParam[0] = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwParam[0];
						lpTransPostItem->dwParam[1] = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwParam[1];
						lpTransPostItem->dwParam[2] = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwParam[2];
						lpTransPostItem->dwParam[3] = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwParam[3];

						lpTransPostItem->Weight = DefaultItems[cnt2].Item.Weight;
						break;
					}
				}
				if(cnt2 < DefaultItemCount) break;
			}
		}
	}


	lpTransPostItem->size = sizeof(TRANS_POST_ITEM);
	if(lpTransPostItem->dwItemFlag) lpTransPostItem->size += sizeof(sITEMINFO);

	if(lpPlayInfo->lpsmSock || (lpTransPostItem->dwItemCode || lpTransPostItem->dwItemFlag))
	{
		lpPlayInfo->lpsmSock->Send((char *)lpTransPostItem, lpTransPostItem->size, TRUE);
	}

	return TRUE;
}



int SendOpenAgingItem(smWINSOCK *lpsmSock)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = OpCode::OPCODE_OPEN_AGING;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	return lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
}


int SendOpenMixtureItemReset(smWINSOCK *lpsmSock)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = OpCode::OPCODE_OPEN_MIXTURE_RESET;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	return lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
}


int rsSend_BadPlayerToGameServer(smWINSOCK *lpsmSock, int BadPlayer)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = OpCode::OPCODE_BAD_PLAYER;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = BadPlayer;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	return rsSendGameServer(lpsmSock, &smTransCommand);
}


int rsSend_PlayerKilling(smWINSOCK *lpsmSock)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = OpCode::OPCODE_PLAYERKILLING;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	if(lpsmSock)
		return lpsmSock->Send((char *)&smTransCommand, sizeof(smTRANS_COMMAND), TRUE);

	return FALSE;
}



int SendOpenClanMenu(smWINSOCK *lpsmSock)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = OpCode::OPCODE_OPEN_CLANMENU;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	return lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
}


int rsProcessQuest(rsPLAYINFO *lpPlayInfo, smCHAR *lpChar, int QuestCode, int QuestParam)
{
	smTRANS_COMMAND	smTransCommand;

	if(!lpPlayInfo->lpsmSock) return FALSE;

	smTransCommand.code = OpCode::OPCODE_QUEST_MESSAGE;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = lpChar->smMonsterInfo.QuestCode;
	smTransCommand.LParam = lpChar->smMonsterInfo.QuestParam;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	switch(QuestCode)
	{
	case SIN_QUEST_CODE_CHANGEJOB2_NPC_M:
	case SIN_QUEST_CODE_CHANGEJOB2_NPC_D:

		if(QuestParam == 1)
		{

			smTransCommand.SParam = rsPutItem(lpPlayInfo, sinMA1 | sin01);
		}
		break;

	case SIN_QUEST_CODE_CHANGEJOB4:
	case HAQUEST_CODE_FURYOFPHANTOM:
		smTransCommand.WParam = QuestCode;
		smTransCommand.LParam = QuestParam;
		break;
	}

	lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

	return TRUE;
}


int rsGetQuestCommand(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	DWORD dwItemCode;

	if(!lpPlayInfo->lpsmSock) return FALSE;

	switch(lpTransCommand->WParam)
	{
	case SIN_QUEST_CODE_LEVEL85:

		if(lpPlayInfo->smCharInfo.Level >= 85)
			rsPutItem(lpPlayInfo, sinQT1 | sin08);
		break;
	case SIN_QUEST_CODE_LEVEL90:

		if(lpPlayInfo->smCharInfo.Level >= 90)
			rsPutItem(lpPlayInfo, sinQT1 | sin07);
		break;

	case SIN_QUEST_CODE_CHANGEJOB4:
		if(lpPlayInfo->smCharInfo.Level >= 49 && lpTransCommand->LParam == QUEST_ARENA_FIELD)
		{

			OpenMonster_QuestArena(lpPlayInfo, SIN_QUEST_CODE_CHANGEJOB4);
		}
		break;

	case HAQUEST_CODE_FURYOFPHANTOM:
		if(lpPlayInfo->smCharInfo.Level >= 99 && lpTransCommand->LParam == QUEST_ARENA_FIELD)
		{

			OpenMonster_QuestArena(lpPlayInfo, HAQUEST_CODE_FURYOFPHANTOM, lpTransCommand->SParam);
		}
		break;

	}

#include "svrHaQuest.h"			

	return TRUE;
}




int	rsDeleteClientItem(rsPLAYINFO *lpPlayInfo, sITEMINFO *lpItem)
{
	TRANS_ITEM_CODE	TransItemCode;


	TransItemCode.code = OpCode::OPCODE_ERRORITEM;
	TransItemCode.size = sizeof(TRANS_ITEM_CODE);
	TransItemCode.dwFlag = FALSE;
	TransItemCode.dwHead = lpItem->ItemHeader.Head;
	TransItemCode.dwChkSum = lpItem->ItemHeader.dwChkSum;
	TransItemCode.dwItemCode = lpItem->CODE;
	TransItemCode.dwTime = 0;

	if(lpPlayInfo && lpPlayInfo->lpsmSock)
	{
		lpPlayInfo->lpsmSock->Send((char *)&TransItemCode, TransItemCode.size, TRUE);
	}

	return TRUE;
}



int	rsDeleteClientItem(rsPLAYINFO *lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum)
{
	TRANS_ITEM_CODE	TransItemCode;


	TransItemCode.code = OpCode::OPCODE_ERRORITEM;
	TransItemCode.size = sizeof(TRANS_ITEM_CODE);
	TransItemCode.dwFlag = FALSE;
	TransItemCode.dwHead = dwHead;
	TransItemCode.dwChkSum = dwChkSum;
	TransItemCode.dwItemCode = dwCode;
	TransItemCode.dwTime = 0;

	if(lpPlayInfo && lpPlayInfo->lpsmSock)
	{
		lpPlayInfo->lpsmSock->Send((char *)&TransItemCode, TransItemCode.size, TRUE);
	}

	return TRUE;
}


int rsRecvAgingUpgradeItem(rsPLAYINFO	*lpPlayInfo, TRANS_ITEMINFO *lpTransItemInfo)
{
	sITEMINFO sItemInfo;

	if(CheckItemForm(&lpTransItemInfo->Item) == FALSE) return FALSE;


	if(rsDeleteInvenItem(lpPlayInfo, lpTransItemInfo->Item.CODE, lpTransItemInfo->Item.ItemHeader.Head, lpTransItemInfo->Item.ItemHeader.dwChkSum) < 0)
		return FALSE;


	memcpy(&sItemInfo, &lpTransItemInfo->Item, sizeof(sITEMINFO));

	lpTransItemInfo->Item.dwCreateTime = 0;
	sinSetAgingItemIncreState(&lpTransItemInfo->Item);


	rsAddInvenItem(lpPlayInfo, lpTransItemInfo->Item.CODE, lpTransItemInfo->Item.ItemHeader.Head, lpTransItemInfo->Item.ItemHeader.dwChkSum);


	rsSaveAgingItemToHDD(&lpTransItemInfo->Item);


	RecordAgingItem(lpPlayInfo, &sItemInfo, &lpTransItemInfo->Item, TRUE);


	rsRecord_ItemLog_Change(lpPlayInfo, sItemInfo.CODE, sItemInfo.ItemHeader.Head, sItemInfo.ItemHeader.dwChkSum,
		lpTransItemInfo->Item.CODE, lpTransItemInfo->Item.ItemHeader.Head, lpTransItemInfo->Item.ItemHeader.dwChkSum, ITEMLOG_AGINGUP);


	return lpPlayInfo->lpsmSock->Send((char *)lpTransItemInfo, lpTransItemInfo->size, TRUE);
}


int rsRecvAgingItem(rsPLAYINFO *lpPlayInfo, sCRAFTITEM_SERVER *pCraftItem_Server)
{
	cAGING		ccItem;
	sITEMINFO	sItemInfo;
	smTRANS_COMMAND	smTransCommand;
	smTRANS_COMMAND_EX	smTransCommandEx;

	int cnt;
	int	ErrorFlag;
	int Price;
	int	QuestMode;
	int	AgingCnt, AgingLog;






	ErrorFlag = 0;


	rsRecord_ItemLost(lpPlayInfo, pCraftItem_Server->SheltomCode, pCraftItem_Server->Head, pCraftItem_Server->CheckSum, ITEMLOG_AGINGLOST);

	for(cnt = 0; cnt < 12; cnt++)
	{

		if(pCraftItem_Server->SheltomCode[cnt])
		{


			if(rsDeleteInvenItem(lpPlayInfo, pCraftItem_Server->SheltomCode[cnt],
				pCraftItem_Server->Head[cnt], pCraftItem_Server->CheckSum[cnt]) < 0)
			{


				smTransCommandEx.WParam = 8000;
				smTransCommandEx.WxParam = 70;
				smTransCommandEx.LxParam = (int)"*AGING SHELTON*";
				smTransCommandEx.LParam = pCraftItem_Server->SheltomCode[cnt];
				smTransCommandEx.SParam = pCraftItem_Server->Head[cnt];
				smTransCommandEx.EParam = pCraftItem_Server->CheckSum[cnt];
				RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
				ErrorFlag++;

				pCraftItem_Server->SheltomCode[cnt] = 0;
			}

			SaveThrowItem(lpPlayInfo, pCraftItem_Server->SheltomCode[cnt],
				pCraftItem_Server->Head[cnt], pCraftItem_Server->CheckSum[cnt]);
		}
	}

	memcpy(&sItemInfo, &pCraftItem_Server->DesCraftItem.sItemInfo, sizeof(sITEMINFO));



#ifdef AGING_MONEY_FREE
	Price = 0;
#else
	Price = ((sItemInfo.ItemAgingNum[0] + 1) * sItemInfo.Price) / 2;
#endif

	CurrencyLog.int64_AgingMoney += Price;

	if(rsServerConfig.ServerInventoryMode && sItemInfo.ItemKindCode != ITEM_KIND_QUEST_WEAPON)
	{
		if(lpPlayInfo->ServerMoney < Price)
		{

			smTransCommand.WParam = 8010;
			smTransCommand.LParam = 70;
			smTransCommand.SParam = lpPlayInfo->ServerMoney;
			smTransCommand.EParam = Price;
			RecordHackLogFile(lpPlayInfo, &smTransCommand);

			lpPlayInfo->SetServerMoney(0, WHERE_AGINGITEM);
			ErrorFlag++;
		}
		else
		{
			lpPlayInfo->SubServerMoney(Price, WHERE_AGINGITEM);
			lpPlayInfo->UnsaveMoney = lpPlayInfo->ServerMoney;
		}
	}

	if(CheckItemForm(&sItemInfo) == FALSE || CheckMixItem(&sItemInfo) == FALSE)
	{


		sAging_Recv.Result = FALSE;
		sAging_Recv.size = 32;
		if(lpPlayInfo && lpPlayInfo->lpsmSock)
		{
			lpPlayInfo->lpsmSock->Send((char *)&sAging_Recv, sAging_Recv.size, TRUE);
		}


		smTransCommand.WParam = 99000;
		smTransCommand.SParam = 0;
		smTransCommand.LParam = 1;
		RecordHackLogFile(lpPlayInfo, &smTransCommand);

		return TRUE;
	}

	if((sItemInfo.CODE&sinITEM_MASK2) == sinMA1)
		QuestMode = TRUE;
	else
	{
		if(lpPlayInfo->getSecurity() >= AccountTypes::SEC_CONSOLE)
			QuestMode = -1;
		else
			QuestMode = FALSE;
	}


	if(pCraftItem_Server->A_StoneItemCode)
	{
		if((pCraftItem_Server->A_StoneItemCode == (sinBI1 | sin10) || pCraftItem_Server->A_StoneItemCode == (sinBI1 | sin11) ||
			pCraftItem_Server->A_StoneItemCode == (sinBI1 | sin60) || pCraftItem_Server->A_StoneItemCode == (sinBI1 | sin85)) &&
			rsDeleteInvenItem(lpPlayInfo,
				pCraftItem_Server->A_StoneItemCode,
				pCraftItem_Server->A_StoneHead,
				pCraftItem_Server->A_StoneCheckSum) >= 0)
		{

			rsRecord_ItemLog2(lpPlayInfo, pCraftItem_Server->A_StoneItemCode, pCraftItem_Server->A_StoneHead, pCraftItem_Server->A_StoneCheckSum, ITEMLOG_AGINGLOST);

			SaveThrowItem(lpPlayInfo,
				pCraftItem_Server->A_StoneItemCode, pCraftItem_Server->A_StoneHead, pCraftItem_Server->A_StoneCheckSum);
		}
		else
		{


			smTransCommandEx.WParam = 8000;
			smTransCommandEx.WxParam = 70;
			smTransCommandEx.LxParam = (int)"Aging Stone";
			smTransCommandEx.LParam = pCraftItem_Server->A_StoneItemCode;
			smTransCommandEx.SParam = pCraftItem_Server->A_StoneHead;
			smTransCommandEx.EParam = pCraftItem_Server->A_StoneCheckSum;
			RecordHackLogFile(lpPlayInfo, &smTransCommandEx);

			pCraftItem_Server->A_StoneItemCode = 0;
		}
	}
	else
	{
		pCraftItem_Server->A_StoneItemCode = 0;
	}

	ccItem.sinRecvAgingItem(pCraftItem_Server);
	cnt = ccItem.AgingItem(QuestMode);


	if(ErrorFlag) sAging_Recv.Result = FALSE;


	if(rsDeleteInvenItem(lpPlayInfo, sItemInfo.CODE, sItemInfo.ItemHeader.Head, sItemInfo.ItemHeader.dwChkSum) < 0)
	{

		sAging_Recv.size = 32;
		sAging_Recv.Result = FALSE;


		smTransCommandEx.WParam = 8000;
		smTransCommandEx.WxParam = 70;
		smTransCommandEx.LxParam = (int)sItemInfo.ItemName;
		smTransCommandEx.LParam = sItemInfo.CODE;
		smTransCommandEx.SParam = sItemInfo.ItemHeader.Head;
		smTransCommandEx.EParam = sItemInfo.ItemHeader.dwChkSum;
		RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
	}

	sAging_Recv.code = OpCode::OPCODE_AGINGITEM;
	if(sAging_Recv.Result)
	{


		if(QuestMode == TRUE)
		{
			for(cnt = 0; cnt < DefaultItemCount; cnt++)
			{
				if(DefaultItems[cnt].Item.CODE == sAging_Recv.DesCraftItem.sItemInfo.CODE)
				{
					CreateDefItem(&sAging_Recv.DesCraftItem.sItemInfo, &DefaultItems[cnt]);
					break;
				}
			}
		}

		ReformItem(&sAging_Recv.DesCraftItem.sItemInfo);
		sAging_Recv.size = sizeof(sITEM) + 32;

		rsAddInvenItem(lpPlayInfo, sAging_Recv.DesCraftItem.sItemInfo.CODE,
			sAging_Recv.DesCraftItem.sItemInfo.ItemHeader.Head,
			sAging_Recv.DesCraftItem.sItemInfo.ItemHeader.dwChkSum);

		if(QuestMode != TRUE)
		{

			RecordAgingItem(lpPlayInfo, &sItemInfo, &sAging_Recv.DesCraftItem.sItemInfo, FALSE);

			AgingCnt = sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0] - sItemInfo.ItemAgingNum[0];
			AgingLog = ITEMLOG_AGING;

			switch(sAging_Recv.Result)
			{
			case 4:
				AgingLog = ITEMLOG_AGING_2UP;
				break;
			case 3:
				AgingLog = ITEMLOG_AGING;
				break;



			case 1:
				AgingLog = ITEMLOG_AGING_1DOWN;
				break;
			case 2:
				AgingLog = ITEMLOG_AGING_2DOWN;
				break;
			}


			rsRecord_ItemLog_Change(lpPlayInfo, sItemInfo.CODE, sItemInfo.ItemHeader.Head, sItemInfo.ItemHeader.dwChkSum,
				sAging_Recv.DesCraftItem.sItemInfo.CODE, sAging_Recv.DesCraftItem.sItemInfo.ItemHeader.Head, sAging_Recv.DesCraftItem.sItemInfo.ItemHeader.dwChkSum, AgingLog);


			rsSaveAgingItemToHDD(&sAging_Recv.DesCraftItem.sItemInfo);
		}

		SaveThrowItem(lpPlayInfo, sItemInfo.CODE, sItemInfo.ItemHeader.Head, sItemInfo.ItemHeader.dwChkSum);

	}
	else
	{
		sAging_Recv.size = 32;

		if(QuestMode != TRUE)
		{

			RecordAgingItem(lpPlayInfo, &sItemInfo, 0, FALSE);


			rsRecord_ItemLog2(lpPlayInfo, sItemInfo.CODE, sItemInfo.ItemHeader.Head, sItemInfo.ItemHeader.dwChkSum, ITEMLOG_AGINGLOST);
		}
	}

	if(lpPlayInfo && lpPlayInfo->lpsmSock)
	{
		lpPlayInfo->lpsmSock->Send((char *)&sAging_Recv, sAging_Recv.size, TRUE);
	}

	return TRUE;
}



int rsRecvCraftItem(rsPLAYINFO *lpPlayInfo, sCRAFTITEM_SERVER *pCraftItem_Server)
{

	cCRAFTITEM	ccItem;
	sITEMINFO	sItemInfo;
	smTRANS_COMMAND	smTransCommand;
	smTRANS_COMMAND_EX	smTransCommandEx;

	int cnt;
	int	ErrorFlag;
	int Result;
	DWORD ItemCraftType = 0;
	int RandNum = 0;



	ErrorFlag = 0;

	for(cnt = 0; cnt < 12; cnt++)
	{
		if((pCraftItem_Server->SheltomCode[cnt] & sinITEM_MASK2) == sinSE1)
		{
			ItemCraftType = sinSE1;
			break;
		}
	}

	int iCountCelesto = 0;
	for (cnt = 0; cnt < 12; cnt++)
	{
		if ((pCraftItem_Server->SheltomCode[cnt]) == (sinOS1 | sin09))
		{
			iCountCelesto += 1;
		}
	}


	if(ItemCraftType == sinSE1)
	{

		rsRecord_ItemLost(lpPlayInfo, pCraftItem_Server->SheltomCode, pCraftItem_Server->Head, pCraftItem_Server->CheckSum, ITEMLOG_LOST_RECON);
	}
	else
	{

		rsRecord_ItemLost(lpPlayInfo, pCraftItem_Server->SheltomCode, pCraftItem_Server->Head, pCraftItem_Server->CheckSum, ITEMLOG_MIXLOST);
	}

	for(cnt = 0; cnt < 12; cnt++)
	{

		if(pCraftItem_Server->SheltomCode[cnt])
		{


			if(rsDeleteInvenItem(lpPlayInfo, pCraftItem_Server->SheltomCode[cnt],
				pCraftItem_Server->Head[cnt], pCraftItem_Server->CheckSum[cnt]) < 0)
			{


				smTransCommandEx.WParam = 8000;
				smTransCommandEx.WxParam = 50;
				smTransCommandEx.LxParam = (int)"*MIXTRUE SHELTON*";
				smTransCommandEx.LParam = pCraftItem_Server->SheltomCode[cnt];
				smTransCommandEx.SParam = pCraftItem_Server->Head[cnt];
				smTransCommandEx.EParam = pCraftItem_Server->CheckSum[cnt];
				RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
				ErrorFlag++;

				pCraftItem_Server->SheltomCode[cnt] = 0;
			}

			SaveThrowItem(lpPlayInfo, pCraftItem_Server->SheltomCode[cnt],
				pCraftItem_Server->Head[cnt], pCraftItem_Server->CheckSum[cnt]);
		}
	}

	memcpy(&sItemInfo, &pCraftItem_Server->DesCraftItem.sItemInfo, sizeof(sITEMINFO));

	CurrencyLog.int64_CraftMoney += sItemInfo.Price;

	if(rsServerConfig.ServerInventoryMode)
	{
		if(lpPlayInfo->ServerMoney < sItemInfo.Price)
		{

			smTransCommand.WParam = 8010;
			smTransCommand.LParam = 50;
			smTransCommand.SParam = lpPlayInfo->ServerMoney;
			smTransCommand.EParam = sItemInfo.Price;
			RecordHackLogFile(lpPlayInfo, &smTransCommand);

			lpPlayInfo->SetServerMoney(0, WHERE_CRAFTITEM);
			ErrorFlag++;
		}
		else
		{
			lpPlayInfo->SubServerMoney(sItemInfo.Price, WHERE_CRAFTITEM);
			lpPlayInfo->UnsaveMoney = lpPlayInfo->ServerMoney;
		}
	}


	if(CheckItemForm(&sItemInfo) == FALSE || sItemInfo.ItemKindCode != 0 || CheckMixItem(&sItemInfo) == FALSE)
	{


		sCraftItem_Recv.Result = FALSE;
		sCraftItem_Recv.size = 32;
		if(lpPlayInfo && lpPlayInfo->lpsmSock)
		{
			lpPlayInfo->lpsmSock->Send((char *)&sCraftItem_Recv, sCraftItem_Recv.size, TRUE);
		}


		smTransCommand.WParam = 99000;
		smTransCommand.SParam = 0;
		smTransCommand.LParam = 0;
		RecordHackLogFile(lpPlayInfo, &smTransCommand);

		return TRUE;
	}


	if(pCraftItem_Server->A_StoneItemCode)
	{
		if((pCraftItem_Server->A_StoneItemCode == (sinBI1 | sin90)) &&
			rsDeleteInvenItem(lpPlayInfo,
				pCraftItem_Server->A_StoneItemCode,
				pCraftItem_Server->A_StoneHead,
				pCraftItem_Server->A_StoneCheckSum) >= 0)
		{

			rsRecord_ItemLog2(lpPlayInfo, pCraftItem_Server->A_StoneItemCode, pCraftItem_Server->A_StoneHead, pCraftItem_Server->A_StoneCheckSum, ITEMLOG_LOST_RECON);

			SaveThrowItem(lpPlayInfo,
				pCraftItem_Server->A_StoneItemCode, pCraftItem_Server->A_StoneHead, pCraftItem_Server->A_StoneCheckSum);


			RandNum = GetRandomPos(1, 100);
			if(RandNum < 51)
				spJobCode = lpPlayInfo->smCharInfo.JOB_CODE;
			else
				spJobCode = lpPlayInfo->smCharInfo.JOB_CODE + 100;
		}
		else
		{


			smTransCommandEx.WParam = 8000;
			smTransCommandEx.WxParam = 70;
			smTransCommandEx.LxParam = (int)"Aging Stone";
			smTransCommandEx.LParam = pCraftItem_Server->A_StoneItemCode;
			smTransCommandEx.SParam = pCraftItem_Server->A_StoneHead;
			smTransCommandEx.EParam = pCraftItem_Server->A_StoneCheckSum;
			RecordHackLogFile(lpPlayInfo, &smTransCommandEx);

			pCraftItem_Server->A_StoneItemCode = 0;
		}
	}
	else
	{
		pCraftItem_Server->A_StoneItemCode = 0;
	}

	ccItem.sinRecvCraftItem(pCraftItem_Server);
	Result = ccItem.MixingItem();


	if(ErrorFlag) sCraftItem_Recv.Result = FALSE;

	if(Result == 2000)
	{

		for(cnt = 0; cnt < DefaultItemCount; cnt++)
		{
			if(DefaultItems[cnt].Item.CODE == sCraftItem_Recv.DesCraftItem.sItemInfo.CODE && !DefaultItems[cnt].Item.UniqueItem)
			{
				CreateDefItem(&sCraftItem_Recv.DesCraftItem.sItemInfo, &DefaultItems[cnt], spJobCode);
				break;
			}
		}
	}


	spJobCode = 0;

	sCraftItem_Recv.code = OpCode::OPCODE_CRAFTITEM;
	if(sCraftItem_Recv.Result == TRUE)
	{
		ReformItem(&sCraftItem_Recv.DesCraftItem.sItemInfo);
		sCraftItem_Recv.size = sizeof(sITEM) + 32;



		if(rsDeleteInvenItem(lpPlayInfo, sItemInfo.CODE, sItemInfo.ItemHeader.Head, sItemInfo.ItemHeader.dwChkSum) >= 0)
		{
			rsAddInvenItem(lpPlayInfo, sCraftItem_Recv.DesCraftItem.sItemInfo.CODE,
				sCraftItem_Recv.DesCraftItem.sItemInfo.ItemHeader.Head,
				sCraftItem_Recv.DesCraftItem.sItemInfo.ItemHeader.dwChkSum);


			RecordMixItem(lpPlayInfo, &sItemInfo, &sCraftItem_Recv.DesCraftItem.sItemInfo);

			if(ItemCraftType == sinSE1)
			{

				rsRecord_ItemLog_Change(lpPlayInfo, sItemInfo.CODE, sItemInfo.ItemHeader.Head, sItemInfo.ItemHeader.dwChkSum,
					sCraftItem_Recv.DesCraftItem.sItemInfo.CODE, sCraftItem_Recv.DesCraftItem.sItemInfo.ItemHeader.Head, sCraftItem_Recv.DesCraftItem.sItemInfo.ItemHeader.dwChkSum, ITEMLOG_GET_RECON);
			}
			else
			{

				rsRecord_ItemLog_Change(lpPlayInfo, sItemInfo.CODE, sItemInfo.ItemHeader.Head, sItemInfo.ItemHeader.dwChkSum,
					sCraftItem_Recv.DesCraftItem.sItemInfo.CODE, sCraftItem_Recv.DesCraftItem.sItemInfo.ItemHeader.Head, sCraftItem_Recv.DesCraftItem.sItemInfo.ItemHeader.dwChkSum, ITEMLOG_MIXING);
			}


			rsSaveAgingItemToHDD(&sCraftItem_Recv.DesCraftItem.sItemInfo);


		}
		else
		{
			sCraftItem_Recv.size = 32;
			sCraftItem_Recv.Result = FALSE;


			smTransCommandEx.WParam = 8000;
			smTransCommandEx.WxParam = 50;
			smTransCommandEx.LxParam = (int)sItemInfo.ItemName;
			smTransCommandEx.LParam = sItemInfo.CODE;
			smTransCommandEx.SParam = sItemInfo.ItemHeader.Head;
			smTransCommandEx.EParam = sItemInfo.ItemHeader.dwChkSum;
			RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
		}
		SaveThrowItem(lpPlayInfo, sItemInfo.CODE, sItemInfo.ItemHeader.Head, sItemInfo.ItemHeader.dwChkSum);

	}
	else
	{
		sCraftItem_Recv.size = 32;
	}

	if(lpPlayInfo && lpPlayInfo->lpsmSock)
	{
		lpPlayInfo->lpsmSock->Send((char *)&sCraftItem_Recv, sCraftItem_Recv.size, TRUE);
	}

	return TRUE;
}


int rsRecvSmeltingItem(rsPLAYINFO *lpPlayInfo, sSMELTINGITEM_SERVER *pSmeltingItem_Server)
{
	CSmeltingItem ccItem;


	smTRANS_COMMAND_EX	smTransCommandEx;

	int cnt;
	int	ErrorFlag;

	DWORD ItemSmeltingType = 0;

	bool bFirst_Ore = TRUE;
	bool bOre_OK = TRUE;
	DWORD first_Ore = 0;
	DWORD Next_Ore = 0;
	int ore_num = 0;
	int crystal_num = 0;

	bool bFirst_Sheltom = TRUE;
	bool bSheltom_OK = TRUE;
	DWORD first_Sheltom = 0;
	DWORD Next_Sheltom = 0;

	ErrorFlag = 0;


	rsRecord_SmeltingItemLOG(lpPlayInfo, pSmeltingItem_Server->SmeltingCode, pSmeltingItem_Server->Head, pSmeltingItem_Server->CheckSum, ITEMLOG_SMELTING_LOST);
	for(cnt = 0; cnt < 3; cnt++)
	{
		if(pSmeltingItem_Server->SmeltingCode[cnt])
		{
			if((pSmeltingItem_Server->SmeltingCode[cnt] & sinITEM_MASK2) == sinPR1)
			{
				if(ore_num < 3)
				{
					ItemSmeltingType = sinPR1;
					ore_num++;
				}
			}
			else if((pSmeltingItem_Server->SmeltingCode[cnt] & sinITEM_MASK2) == sinPR2)
			{
				if(crystal_num < 3)
				{
					ItemSmeltingType = sinPR2;
					crystal_num++;
				}

			}
			if(rsDeleteInvenItem(lpPlayInfo, pSmeltingItem_Server->SmeltingCode[cnt],
				pSmeltingItem_Server->Head[cnt], pSmeltingItem_Server->CheckSum[cnt]) < 0)
			{
				if(ItemSmeltingType == sinPR1)
				{

					smTransCommandEx.WParam = 8000;
					smTransCommandEx.WxParam = 50;
					smTransCommandEx.LxParam = (int)"*SMELTING ORE*";
					smTransCommandEx.LParam = pSmeltingItem_Server->SmeltingCode[cnt];
					smTransCommandEx.SParam = pSmeltingItem_Server->Head[cnt];
					smTransCommandEx.EParam = pSmeltingItem_Server->CheckSum[cnt];
					RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
				}
				else if(ItemSmeltingType == sinPR2)
				{

					smTransCommandEx.WParam = 8000;
					smTransCommandEx.WxParam = 50;
					smTransCommandEx.LxParam = (int)"*SMELTING CRYSTAL*";
					smTransCommandEx.LParam = pSmeltingItem_Server->SmeltingCode[cnt];
					smTransCommandEx.SParam = pSmeltingItem_Server->Head[cnt];
					smTransCommandEx.EParam = pSmeltingItem_Server->CheckSum[cnt];
					RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
				}
				ErrorFlag++;

				pSmeltingItem_Server->SmeltingCode[cnt] = 0;
			}
			else
			{
				if(bFirst_Ore)
				{
					first_Ore = pSmeltingItem_Server->SmeltingCode[cnt];
					Next_Ore = pSmeltingItem_Server->SmeltingCode[cnt];
					bFirst_Ore = FALSE;
				}
				else
				{
					Next_Ore = pSmeltingItem_Server->SmeltingCode[cnt];
				}
				if(first_Ore != Next_Ore)
				{
					bOre_OK = FALSE;
					ErrorFlag++;
				}
			}
			SaveThrowItem(lpPlayInfo, pSmeltingItem_Server->SmeltingCode[cnt],
				pSmeltingItem_Server->Head[cnt], pSmeltingItem_Server->CheckSum[cnt]);
		}
	}

	if(ItemSmeltingType == sinPR1 && ore_num != 3)
	{
		bOre_OK = FALSE;
		ErrorFlag++;
	}
	else if(ItemSmeltingType == sinPR2 && crystal_num != 3)
	{
		bOre_OK = FALSE;
		ErrorFlag++;
	}

	if(pSmeltingItem_Server->SmeltingCode[4])
	{
		if(rsDeleteInvenItem(lpPlayInfo, pSmeltingItem_Server->SmeltingCode[4],
			pSmeltingItem_Server->Head[4], pSmeltingItem_Server->CheckSum[4]) < 0)
		{

			smTransCommandEx.WParam = 8000;
			smTransCommandEx.WxParam = 50;
			smTransCommandEx.LxParam = (int)"*SMELTING SHELTON*";
			smTransCommandEx.LParam = pSmeltingItem_Server->SmeltingCode[4];
			smTransCommandEx.SParam = pSmeltingItem_Server->Head[4];
			smTransCommandEx.EParam = pSmeltingItem_Server->CheckSum[4];
			RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
			ErrorFlag++;

			pSmeltingItem_Server->SmeltingCode[4] = 0;
		}
		if(bFirst_Sheltom)
		{
			first_Sheltom = pSmeltingItem_Server->SmeltingCode[4];
			Next_Sheltom = pSmeltingItem_Server->SmeltingCode[4];
			bFirst_Sheltom = FALSE;
		}
		else
		{
			Next_Sheltom = pSmeltingItem_Server->SmeltingCode[4];
		}
		if(first_Sheltom != Next_Sheltom)
		{
			bSheltom_OK = FALSE;
			ErrorFlag++;
		}
		SaveThrowItem(lpPlayInfo, pSmeltingItem_Server->SmeltingCode[4],
			pSmeltingItem_Server->Head[4], pSmeltingItem_Server->CheckSum[4]);
	}

	DWORD code = 0;
	if(bOre_OK && bSheltom_OK)
	{
		if((Next_Ore & sinITEM_MASK2) == sinPR1)
		{
			if(Next_Ore == (sinPR1 | sin01) && Next_Sheltom == (sinOS1 | sin06))
			{
				code = (sinPR2 | sin01);
			}
			else if(Next_Ore == (sinPR1 | sin02) && Next_Sheltom == (sinOS1 | sin07))
			{
				code = (sinPR2 | sin02);
			}
			else if(Next_Ore == (sinPR1 | sin03) && Next_Sheltom == (sinOS1 | sin08))
			{
				code = (sinPR2 | sin03);
			}
			else if(Next_Ore == (sinPR1 | sin04) && Next_Sheltom == (sinOS1 | sin09))
			{
				code = (sinPR2 | sin04);
			}
			else if(Next_Ore == (sinPR1 | sin05) && Next_Sheltom == (sinOS1 | sin10))
			{
				code = (sinPR2 | sin05);
			}
			else if(Next_Ore == (sinPR1 | sin06) && Next_Sheltom == (sinOS1 | sin11))
			{
				code = (sinPR2 | sin06);
			}
			else if(Next_Ore == (sinPR1 | sin07) && Next_Sheltom == (sinOS1 | sin12))
			{
				code = (sinPR2 | sin07);
			}
			else if(Next_Ore == (sinPR1 | sin07) && Next_Sheltom == (sinOS1 | sin13))
			{
				code = (sinPR2 | sin08);
			}
		}

		else if((Next_Ore & sinITEM_MASK2) == sinPR2)
		{
			if(Next_Ore == (sinPR2 | sin01) && Next_Sheltom == (sinOS1 | sin07))
			{
				switch(rand() % 2)
				{
				case 0:
					code = (sinPR3 | sin01);
					break;
				case 1:
					code = (sinPR4 | sin01);
					break;
				}
			}
			else if(Next_Ore == (sinPR2 | sin02) && Next_Sheltom == (sinOS1 | sin08))
			{
				switch(rand() % 2)
				{
				case 0:
					code = (sinPR3 | sin02);
					break;
				case 1:
					code = (sinPR4 | sin02);
					break;
				}
			}
			else if(Next_Ore == (sinPR2 | sin03) && Next_Sheltom == (sinOS1 | sin09))
			{
				switch(rand() % 2)
				{
				case 0:
					code = (sinPR3 | sin03);
					break;
				case 1:
					code = (sinPR4 | sin03);
					break;
				}
			}
			else if(Next_Ore == (sinPR2 | sin04) && Next_Sheltom == (sinOS1 | sin10))
			{
				switch(rand() % 2)
				{
				case 0:
					code = (sinPR3 | sin04);
					break;
				case 1:
					code = (sinPR4 | sin04);
					break;
				}
			}
			else if(Next_Ore == (sinPR2 | sin05) && Next_Sheltom == (sinOS1 | sin11))
			{
				switch(rand() % 2)
				{
				case 0:
					code = (sinPR3 | sin05);
					break;
				case 1:
					code = (sinPR4 | sin05);
					break;
				}
			}
			else if(Next_Ore == (sinPR2 | sin06) && Next_Sheltom == (sinOS1 | sin12))
			{
				switch(rand() % 2)
				{
				case 0:
					code = (sinPR3 | sin06);
					break;
				case 1:
					code = (sinPR4 | sin06);
					break;
				}
			}
			else if(Next_Ore == (sinPR2 | sin07) && Next_Sheltom == (sinOS1 | sin13))
			{
				switch(rand() % 2)
				{
				case 0:
					code = (sinPR3 | sin07);
					break;
				case 1:
					code = (sinPR4 | sin07);
					break;
				}
			}

			else if(Next_Ore == (sinPR2 | sin09) && Next_Sheltom == (sinOS1 | sin03))
			{
				switch(rand() % 2)
				{
				case 0:
					code = (sinPR3 | sin09);
					break;
				case 1:
					code = (sinPR4 | sin09);
					break;
				}
			}


			else if(Next_Ore == (sinPR2 | sin10) && Next_Sheltom == (sinOS1 | sin04))
			{
				switch(rand() % 2)
				{
				case 0:
					code = (sinPR3 | sin10);
					break;
				case 1:
					code = (sinPR4 | sin10);
					break;
				}
			}


			else if(Next_Ore == (sinPR2 | sin11) && Next_Sheltom == (sinOS1 | sin05))
			{
				switch(rand() % 2)
				{
				case 0:
					code = (sinPR3 | sin11);
					break;
				case 1:
					code = (sinPR4 | sin11);
					break;
				}
			}


			else if(Next_Ore == (sinPR2 | sin12) && Next_Sheltom == (sinOS1 | sin03))
			{
				switch(rand() % 2)
				{
				case 0:
					code = (sinPR3 | sin12);
					break;
				case 1:
					code = (sinPR4 | sin12);
					break;
				}
			}

			else if(Next_Ore == (sinPR2 | sin13) && Next_Sheltom == (sinOS1 | sin04))
			{
				switch(rand() % 2)
				{
				case 0:
					code = (sinPR3 | sin13);
					break;
				case 1:
					code = (sinPR4 | sin13);
					break;
				}
			}

			else if(Next_Ore == (sinPR2 | sin14) && Next_Sheltom == (sinOS1 | sin05))
			{
				switch(rand() % 2)
				{
				case 0:
					code = (sinPR3 | sin14);
					break;
				case 1:
					code = (sinPR4 | sin14);
					break;
				}
			}

		}
		else
		{
			ErrorFlag++;
		}

		if(code != 0)
		{
			for(cnt = 0; cnt < DefaultItemCount; cnt++)
			{
				if(DefaultItems[cnt].Item.CODE == code)
				{

					CreateDefItem(&pSmeltingItem_Server->DesSmeltingItem.sItemInfo, &DefaultItems[cnt]);
					break;
				}
			}
		}

	}

	ccItem.sinRecvSmeltingItem(pSmeltingItem_Server);

	if(ErrorFlag)
	{
		sSmeltingItem_Recv.Result = FALSE;
	}
	else
	{
		sSmeltingItem_Recv.Result = TRUE;
	}

	if(sSmeltingItem_Recv.Result == TRUE)
	{
		ReformItem(&sSmeltingItem_Recv.DesSmeltingItem.sItemInfo);
		sSmeltingItem_Recv.size = sizeof(sITEM) + 32;

		rsAddInvenItem(lpPlayInfo, sSmeltingItem_Recv.DesSmeltingItem.sItemInfo.CODE,
			sSmeltingItem_Recv.DesSmeltingItem.sItemInfo.ItemHeader.Head,
			sSmeltingItem_Recv.DesSmeltingItem.sItemInfo.ItemHeader.dwChkSum);

		rsRecord_ItemLog2(lpPlayInfo, sSmeltingItem_Recv.DesSmeltingItem.sItemInfo.CODE, sSmeltingItem_Recv.DesSmeltingItem.sItemInfo.ItemHeader.Head,
			sSmeltingItem_Recv.DesSmeltingItem.sItemInfo.ItemHeader.dwChkSum, ITEMLOG_SMELTING_GET);

		RecordSmeltingItem(lpPlayInfo, &sSmeltingItem_Recv.DesSmeltingItem.sItemInfo);

	}
	else
	{
		sSmeltingItem_Recv.size = 32;
	}

	sSmeltingItem_Recv.code = OpCode::OPCODE_SMELTINGITEM;

	if(lpPlayInfo && lpPlayInfo->lpsmSock)
	{
		lpPlayInfo->lpsmSock->Send((char *)&sSmeltingItem_Recv, sSmeltingItem_Recv.size, TRUE);
	}

	return TRUE;
}


int ManufactureItemInfo(rsPLAYINFO* lpPlayInfo, int spJobCode)
{
	int JobCodeItem = 0;
	JobCodeItem = spJobCode;

	DWORD	dwItem = 0;

	DWORD CreateItemCode[40] = {	(sinOS1 | sin18), (sinOS1 | sin18), (sinOS1 | sin18), (sinOS1 | sin18), (sinOS1 | sin18), (sinOS1 | sin18), (sinOS1 | sin18), (sinOS1 | sin18),
									(sinOS1 | sin19), (sinOS1 | sin19), (sinOS1 | sin19), (sinOS1 | sin19), (sinOS1 | sin19), (sinOS1 | sin19), (sinOS1 | sin19), (sinOS1 | sin19),
									(sinOS1 | sin20), (sinOS1 | sin20), (sinOS1 | sin20), (sinOS1 | sin20), (sinOS1 | sin20), (sinOS1 | sin20), (sinOS1 | sin20), (sinOS1 | sin20),
									(sinOS1 | sin21), (sinOS1 | sin21), (sinOS1 | sin21), (sinOS1 | sin21), (sinOS1 | sin21), (sinOS1 | sin21), (sinOS1 | sin21), (sinOS1 | sin21),
									(sinOS1 | sin22), (sinOS1 | sin22), (sinOS1 | sin22), (sinOS1 | sin22), (sinOS1 | sin22), (sinOS1 | sin22), (sinOS1 | sin22), (sinOS1 | sin22),
	};
	int num = 0;
	SManufacture_ResultItemInfo_Server Item_Recv;
	ZeroMemory(&Item_Recv, sizeof(SManufacture_ResultItemInfo_Server));
	Item_Recv.smTransCommand.code = OpCode::OPCODE_MANUFACTURE_WEIGHT_PRICE;
	Item_Recv.smTransCommand.size = sizeof(SManufacture_ResultItemInfo_Server);
	for (int i = 0; i < 40; i++)
	{
		for (int cnt = 0; cnt < DefaultItemCount; cnt++)
		{
			if (CreateItemCode[i] > 0 && CreateItemCode[i] == DefaultItems[cnt].Item.CODE)
			{
				Item_Recv.ItemCode[num] = DefaultItems[cnt].Item.CODE;
				strcpy_s(Item_Recv.ItemName[num], DefaultItems[cnt].Item.ItemName);
				Item_Recv.Weight[num] = DefaultItems[cnt].Item.Weight;
				Item_Recv.Price[num] = DefaultItems[cnt].Item.Price;
				num++;
			}
		}
	}
	if (lpPlayInfo && lpPlayInfo->lpsmSock)
	{
		lpPlayInfo->lpsmSock->Send((char*)& Item_Recv, Item_Recv.smTransCommand.size, TRUE);
	}
	return TRUE;
}

int rsRecvManufactureItem(rsPLAYINFO *lpPlayInfo, SManufactureItem_Server *pManufactureItem_Server)
{
	CManufacture ccItem;

	smTRANS_COMMAND_EX	smTransCommandEx;

	int JobCodeItem = 0;
	JobCodeItem = lpPlayInfo->smCharInfo.JOB_CODE;

	int cnt;
	int	ErrorFlag;
	DWORD ItemSmeltingType = 0;
	bool  bProbability = FALSE;
	ErrorFlag = 0;

	if(pManufactureItem_Server->RuneCode[0])
	{
		if(rsDeleteInvenItem(lpPlayInfo, pManufactureItem_Server->RuneCode[0],
			pManufactureItem_Server->Head[0], pManufactureItem_Server->CheckSum[0]) < 0)
		{

			smTransCommandEx.WParam = 8000;
			smTransCommandEx.WxParam = 50;
			smTransCommandEx.LxParam = (int)"*Manufacture Recipe*";
			smTransCommandEx.LParam = pManufactureItem_Server->RuneCode[0];
			smTransCommandEx.SParam = pManufactureItem_Server->Head[0];
			smTransCommandEx.EParam = pManufactureItem_Server->CheckSum[0];
			RecordHackLogFile(lpPlayInfo, &smTransCommandEx);

			ErrorFlag++;

			pManufactureItem_Server->RuneCode[0] = 0;
		}
		SaveThrowItem(lpPlayInfo, pManufactureItem_Server->RuneCode[0],
			pManufactureItem_Server->Head[0], pManufactureItem_Server->CheckSum[0]);
	}

	for(cnt = 1; cnt < 4; cnt++)
	{
		if(pManufactureItem_Server->RuneCode[cnt])
		{
			if(rsDeleteInvenItem(lpPlayInfo, pManufactureItem_Server->RuneCode[cnt],
				pManufactureItem_Server->Head[cnt], pManufactureItem_Server->CheckSum[cnt]) < 0)
			{

				smTransCommandEx.WParam = 8000;
				smTransCommandEx.WxParam = 50;
				smTransCommandEx.LxParam = (int)"*Manufacture Rune*";
				smTransCommandEx.LParam = pManufactureItem_Server->RuneCode[cnt];
				smTransCommandEx.SParam = pManufactureItem_Server->Head[cnt];
				smTransCommandEx.EParam = pManufactureItem_Server->CheckSum[cnt];
				RecordHackLogFile(lpPlayInfo, &smTransCommandEx);

				ErrorFlag++;

				pManufactureItem_Server->RuneCode[cnt] = 0;
			}
			SaveThrowItem(lpPlayInfo, pManufactureItem_Server->RuneCode[cnt],
				pManufactureItem_Server->Head[cnt], pManufactureItem_Server->CheckSum[cnt]);
		}
	}

	DWORD ResultItemCode = 0;


	if (ErrorFlag == 0)
	{

		ResultItemCode = ManufactureCheckRune(lpPlayInfo, pManufactureItem_Server->RuneCode[0], pManufactureItem_Server->RuneCode);
		if (ResultItemCode == (sinOA2 | sin31))
		{
			srand((UINT)time(NULL));

			if ((rand() % 100) < 20)

			{
				for (cnt = 0; cnt < DefaultItemCount; cnt++)
				{
					if (DefaultItems[cnt].Item.CODE == ResultItemCode)
					{

						CreateItemPerf(&pManufactureItem_Server->DesManufactureItem.sItemInfo, &DefaultItems[cnt], JobCodeItem);
						bProbability = TRUE;
						break;
					}
				}
			}
			else
			{
				ErrorFlag++;
			}
		}
		else if (ResultItemCode != 0)
		{
			srand((UINT)time(NULL));

			if ((rand() % 100) < 50)

			{
				for (cnt = 0; cnt < DefaultItemCount; cnt++)
				{
					if (DefaultItems[cnt].Item.CODE == ResultItemCode)
					{

						CreateItemPerf(&pManufactureItem_Server->DesManufactureItem.sItemInfo, &DefaultItems[cnt], JobCodeItem);
						bProbability = TRUE;
						break;
					}
				}
			}
			else
			{
				ErrorFlag++;
			}
		}
		else
		{
			ErrorFlag++;
		}
	}
	else
	{
		ErrorFlag++;
	}
	ccItem.sinRecvManufactureItem(pManufactureItem_Server);

	if(bProbability)
	{
		g_sManufactureItem_Recv.Result = TRUE;
	}

	if(ErrorFlag)
	{
		g_sManufactureItem_Recv.Result = FALSE;
	}


	if(g_sManufactureItem_Recv.Result == TRUE)
	{
		ReformItem(&g_sManufactureItem_Recv.DesManufactureItem.sItemInfo);
		g_sManufactureItem_Recv.size = sizeof(sITEM) + 32;

		rsRecord_ManufactureItemLOG(lpPlayInfo, pManufactureItem_Server->RuneCode, pManufactureItem_Server->Head, pManufactureItem_Server->CheckSum, ITEMLOG_MANUFACTURE_LOST);

		rsAddInvenItem(lpPlayInfo, g_sManufactureItem_Recv.DesManufactureItem.sItemInfo.CODE,
			g_sManufactureItem_Recv.DesManufactureItem.sItemInfo.ItemHeader.Head,
			g_sManufactureItem_Recv.DesManufactureItem.sItemInfo.ItemHeader.dwChkSum);

		rsRecord_ItemLog2(lpPlayInfo, g_sManufactureItem_Recv.DesManufactureItem.sItemInfo.CODE, g_sManufactureItem_Recv.DesManufactureItem.sItemInfo.ItemHeader.Head,
			g_sManufactureItem_Recv.DesManufactureItem.sItemInfo.ItemHeader.dwChkSum, ITEMLOG_MANUFACTURE_GET);


		RecordManufactureItem(lpPlayInfo, &g_sManufactureItem_Recv.DesManufactureItem.sItemInfo);

	}
	else
	{
		g_sManufactureItem_Recv.size = 32;
		rsRecord_ManufactureItemLOG(lpPlayInfo, pManufactureItem_Server->RuneCode, pManufactureItem_Server->Head, pManufactureItem_Server->CheckSum, ITEMLOG_MANUFACTURE_FAIL);
	}

	g_sManufactureItem_Recv.code = OpCode::OPCODE_MANUFACTURE;

	if(lpPlayInfo && lpPlayInfo->lpsmSock)
	{
		lpPlayInfo->lpsmSock->Send((char *)&g_sManufactureItem_Recv, g_sManufactureItem_Recv.size, TRUE);
	}

	return TRUE;
}


int rsRecvMixtureResetItem(rsPLAYINFO *lpPlayInfo, sMIXTURE_RESET_ITEM_SERVER *pMixtureResetItem_Server)
{
	cMIXTURERESET ccItem;
	smTRANS_COMMAND_EX	smTransCommandEx;
	int ErrorFlag = 0;
	int MixtureResetSuccess = FALSE;


	if(pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.CODE)
	{
		if(rsDeleteInvenItem(lpPlayInfo, pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.CODE,
			pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.ItemHeader.Head,
			pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.ItemHeader.dwChkSum) < 0)
		{

			smTransCommandEx.WParam = 8000;
			smTransCommandEx.WxParam = 50;
			smTransCommandEx.LxParam = (int)"*Mixture Reset Item*";
			smTransCommandEx.LParam = pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.CODE;
			smTransCommandEx.SParam = pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.ItemHeader.Head;
			smTransCommandEx.EParam = pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.ItemHeader.dwChkSum;
			RecordHackLogFile(lpPlayInfo, &smTransCommandEx);

			ErrorFlag++;

			pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.CODE = 0;
		}

		SaveThrowItem(lpPlayInfo, pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.CODE,
			pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.ItemHeader.Head,
			pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.ItemHeader.dwChkSum);
	}


	if(pMixtureResetItem_Server->dwMixtureResetStoneItemCode)
	{
		if(rsDeleteInvenItem(lpPlayInfo, pMixtureResetItem_Server->dwMixtureResetStoneItemCode,
			pMixtureResetItem_Server->dwMixtureResetStoneHead, pMixtureResetItem_Server->dwMixtureResetStoneCheckSum) < 0)
		{

			smTransCommandEx.WParam = 8000;
			smTransCommandEx.WxParam = 50;
			smTransCommandEx.LxParam = (int)"*Mixture Reset Stone*";
			smTransCommandEx.LParam = pMixtureResetItem_Server->dwMixtureResetStoneItemCode;
			smTransCommandEx.SParam = pMixtureResetItem_Server->dwMixtureResetStoneHead;
			smTransCommandEx.EParam = pMixtureResetItem_Server->dwMixtureResetStoneCheckSum;
			RecordHackLogFile(lpPlayInfo, &smTransCommandEx);

			ErrorFlag++;

			pMixtureResetItem_Server->dwMixtureResetStoneItemCode = 0;
		}

		SaveThrowItem(lpPlayInfo, pMixtureResetItem_Server->dwMixtureResetStoneItemCode,
			pMixtureResetItem_Server->dwMixtureResetStoneHead, pMixtureResetItem_Server->dwMixtureResetStoneCheckSum);
	}


	DWORD dwResultItemCode = 0;
	dwResultItemCode = pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.CODE;



	DWORD dwSpecialJob = 0;
	dwSpecialJob = pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.JobCodeMask;

	int	i;
	DWORD dwJobCode = 0;
	JOB_DATA_CODE *pJobDataCode = 0;


	for(i = 1; i < 9; i++)
	{
		pJobDataCode = GetJobDataCode(i, 0);
		if(pJobDataCode->JobBitCode == dwSpecialJob)
		{
			dwJobCode = pJobDataCode->JobCode;
			break;
		}
	}


	if(i == 9)
	{
		dwJobCode = 0;
		NotItemSpecial = 1;
	}


	if(ErrorFlag == 0)
	{
		if(dwResultItemCode != 0)
		{
			for(int cnt = 0; cnt < DefaultItemCount; cnt++)
			{
				if(DefaultItems[cnt].Item.CODE == dwResultItemCode)
				{
					CreateDefItem(&pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo, &DefaultItems[cnt], dwJobCode);
					MixtureResetSuccess = TRUE;
					break;
				}
			}
		}
		else
		{
			ErrorFlag++;
		}
	}
	else
	{
		ErrorFlag++;
	}


	ccItem.sinRecvMixtureItemReset(pMixtureResetItem_Server);


	if(MixtureResetSuccess)
		sMixtureReset_Recv.Result = TRUE;


	if(ErrorFlag)
		sMixtureReset_Recv.Result = FALSE;

	if(sMixtureReset_Recv.Result == TRUE)
	{
		ReformItem(&sMixtureReset_Recv.DesMixtureResetItem.sItemInfo);
		sMixtureReset_Recv.size = sizeof(sITEM) + 32;


		rsRecord_MixtureResetItemLOG(lpPlayInfo, pMixtureResetItem_Server, ITEMLOG_MIXTURE_RESET_LOST);


		rsAddInvenItem(lpPlayInfo, sMixtureReset_Recv.DesMixtureResetItem.sItemInfo.CODE,
			sMixtureReset_Recv.DesMixtureResetItem.sItemInfo.ItemHeader.Head,
			sMixtureReset_Recv.DesMixtureResetItem.sItemInfo.ItemHeader.dwChkSum);


		rsRecord_ItemLog2(lpPlayInfo, sMixtureReset_Recv.DesMixtureResetItem.sItemInfo.CODE, sMixtureReset_Recv.DesMixtureResetItem.sItemInfo.ItemHeader.Head,
			sMixtureReset_Recv.DesMixtureResetItem.sItemInfo.ItemHeader.dwChkSum, ITEMLOG_MIXTURE_RESET_GET);


		RecordMixtureResetItem(lpPlayInfo, &sMixtureReset_Recv.DesMixtureResetItem.sItemInfo);
	}
	else
	{
		sMixtureReset_Recv.size = 32;
		rsRecord_MixtureResetItemLOG(lpPlayInfo, pMixtureResetItem_Server, ITEMLOG_MIXTURE_RESET_FAIL);
	}


	sMixtureReset_Recv.code = OpCode::OPCODE_MIXTURE_RESET_ITEM;

	if(lpPlayInfo && lpPlayInfo->lpsmSock)
	{
		lpPlayInfo->lpsmSock->Send((char *)&sMixtureReset_Recv, sMixtureReset_Recv.size, TRUE);
	}


	return TRUE;
}


int rsRecvWingItem(rsPLAYINFO *lpPlayInfo, sCRAFTITEM_SERVER *pCraftItem_Server)
{

	sITEMINFO	sItemInfo;
	smTRANS_COMMAND	smTransCommand;
	smTRANS_COMMAND_EX	smTransCommandEx;

	int cnt;
	int	ErrorFlag;
	int	PotionCount = 0;
	int result;
	int	Money;
	int	ForceMode = 0;

	ErrorFlag = 0;

	if(pCraftItem_Server->DesCraftItem.CODE == 1000)
		ForceMode = TRUE;


	if(ForceMode)
		rsRecord_ItemLost(lpPlayInfo, pCraftItem_Server->SheltomCode, pCraftItem_Server->Head, pCraftItem_Server->CheckSum, ITEMLOG_LOST_ALCHMY);
	else

		rsRecord_ItemLost(lpPlayInfo, pCraftItem_Server->SheltomCode, pCraftItem_Server->Head, pCraftItem_Server->CheckSum, ITEMLOG_WINGLOST);

	for(cnt = 0; cnt < 12; cnt++)
	{

		if(pCraftItem_Server->SheltomCode[cnt])
		{


			if(rsDeleteInvenItem(lpPlayInfo, pCraftItem_Server->SheltomCode[cnt],
				pCraftItem_Server->Head[cnt], pCraftItem_Server->CheckSum[cnt]) < 0)
			{


				smTransCommandEx.WParam = 8000;
				smTransCommandEx.WxParam = 50;
				smTransCommandEx.LxParam = (int)"*WING CRISTAL*";
				smTransCommandEx.LParam = pCraftItem_Server->SheltomCode[cnt];
				smTransCommandEx.SParam = pCraftItem_Server->Head[cnt];
				smTransCommandEx.EParam = pCraftItem_Server->CheckSum[cnt];
				RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
				ErrorFlag++;
			}

			SaveThrowItem(lpPlayInfo, pCraftItem_Server->SheltomCode[cnt],
				pCraftItem_Server->Head[cnt], pCraftItem_Server->CheckSum[cnt]);
		}
	}

	memcpy(&sItemInfo, &pCraftItem_Server->DesCraftItem.sItemInfo, sizeof(sITEMINFO));
	Money = pCraftItem_Server->Money;


	if(sItemInfo.CODE && CheckItemForm(&sItemInfo) == FALSE)
	{


		pCraftItem_Server->Result = FALSE;
		pCraftItem_Server->size = 32;
		if(lpPlayInfo && lpPlayInfo->lpsmSock)
		{
			lpPlayInfo->lpsmSock->Send((char *)pCraftItem_Server, pCraftItem_Server->size, TRUE);
		}


		smTransCommand.WParam = 99000;
		smTransCommand.SParam = 1;
		smTransCommand.LParam = sItemInfo.CODE;
		RecordHackLogFile(lpPlayInfo, &smTransCommand);

		return TRUE;
	}


	rsDeleteInvenItem(lpPlayInfo, pCraftItem_Server->DesCraftItem.sItemInfo.CODE,
		pCraftItem_Server->DesCraftItem.sItemInfo.ItemHeader.Head,
		pCraftItem_Server->DesCraftItem.sItemInfo.ItemHeader.dwChkSum);


	result = 0;

	if(!ErrorFlag)
		result = sinWingItemQuestServer(pCraftItem_Server, &lpPlayInfo->smCharInfo);
	else
		pCraftItem_Server->Result = FALSE;

	if(result == 0x100)
	{

		TRANS_ITEMINFO_GROUP	TransItemGroup;
		TRANS_ITEMINFO_GROUP2	TransItemGroup2;
		int cnt2, ItemCnt, LenSize;

		if(lpPlayInfo->ServerMoney >= Money)
		{
			lpPlayInfo->SubServerMoney(Money, WHERE_FORECORB);
			CurrencyLog.int64_ForceOrbMoney += Money;
		}
		else
		{

			smTransCommandEx.WParam = 8000;
			smTransCommandEx.WxParam = 50;
			smTransCommandEx.LxParam = (int)"*FORCE MONEY ERROR*";
			smTransCommandEx.LParam = (sinGG1 | sin01);
			smTransCommandEx.SParam = Money;
			smTransCommandEx.EParam = lpPlayInfo->ServerMoney;
			RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
			return FALSE;
		}

		ZeroMemory(&TransItemGroup2, sizeof(TRANS_ITEMINFO_GROUP2));

		ItemCnt = 0;

		for(cnt = 0; cnt < 12; cnt++)
		{
			if(pCraftItem_Server->SheltomCode[cnt])
			{
				for(cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if(DefaultItems[cnt2].Item.CODE == pCraftItem_Server->SheltomCode[cnt] && !DefaultItems[cnt2].Item.UniqueItem)
					{
						CreateDefItem(&TransItemGroup.sItemInfo[ItemCnt], &DefaultItems[cnt2]);

						rsAddInvenItem(lpPlayInfo, TransItemGroup.sItemInfo[ItemCnt].CODE,
							TransItemGroup.sItemInfo[ItemCnt].ItemHeader.Head,
							TransItemGroup.sItemInfo[ItemCnt].ItemHeader.dwChkSum);


						rsRecord_ItemLog2(lpPlayInfo,
							TransItemGroup.sItemInfo[ItemCnt].CODE,
							TransItemGroup.sItemInfo[ItemCnt].ItemHeader.Head,
							TransItemGroup.sItemInfo[ItemCnt].ItemHeader.dwChkSum,
							ITEMLOG_GET_ALCHMY);

						ItemCnt++;
						break;
					}
				}
			}
		}

		LenSize = EecodeCompress((BYTE *)TransItemGroup.sItemInfo, (BYTE *)TransItemGroup2.szBuff, sizeof(sITEMINFO)*ItemCnt, sizeof(sITEMINFO)*TRANS_GROUPITEM_MAX);
		TransItemGroup2.ItemCount = ItemCnt;
		TransItemGroup2.Result = pCraftItem_Server->Result;
		TransItemGroup2.size = LenSize + TRANS_GROUPITEM_HEADER_SIZE;
		TransItemGroup2.code = OpCode::OPCODE_ITEM_FORCEORB;

		if(lpPlayInfo && lpPlayInfo->lpsmSock)
		{
			lpPlayInfo->lpsmSock->Send((char *)&TransItemGroup2, TransItemGroup2.size, TRUE);
		}

		return TRUE;
	}

	if(pCraftItem_Server->Result == SIN_WINGRESULT_CRISTAL)
	{

		bSql_EventJoin(lpPlayInfo);
		pCraftItem_Server->Result = TRUE;
	}

	if(pCraftItem_Server->Result == TRUE && pCraftItem_Server->DesCraftItem.sItemInfo.CODE && !ErrorFlag)
	{


		if(pCraftItem_Server->DesCraftItem.sItemInfo.ItemKindCode == ITEM_KIND_QUEST_WEAPON)
		{

			for(cnt = 0; cnt < DefaultItemCount; cnt++)
			{
				if(DefaultItems[cnt].Item.CODE == pCraftItem_Server->DesCraftItem.sItemInfo.CODE && DefaultItems[cnt].Item.UniqueItem == ITEM_UNIQUE_CODE_QUEST)
				{
					CreateDefItem(&pCraftItem_Server->DesCraftItem.sItemInfo, &DefaultItems[cnt]);
					pCraftItem_Server->DesCraftItem.sItemInfo.ItemKindCode = ITEM_KIND_QUEST_WEAPON;
					SetChangeJob3QuestItem(&pCraftItem_Server->DesCraftItem.sItemInfo);
					break;
				}
			}
		}
		else
		{
			for(cnt = 0; cnt < DefaultItemCount; cnt++)
			{
				if(DefaultItems[cnt].Item.CODE == pCraftItem_Server->DesCraftItem.sItemInfo.CODE && !DefaultItems[cnt].Item.UniqueItem)
				{

					if(DefaultItems[cnt].sGenDay[0] && DefaultItems[cnt].sGenDay[1] >= DefaultItems[cnt].sGenDay[0])
					{


						pCraftItem_Server->DesCraftItem.sItemInfo.CODE = (sinPM1 | sin04);
						pCraftItem_Server->DesCraftItem.sItemInfo.PotionCount = 30;


#ifdef	_TEST_SERVER
						if(lpPlayInfo->getSecurity() > AccountTypes::SEC_VIP)
						{
							TRANS_CHATMESSAGE	TransChatMessage;
							wsprintf(TransChatMessage.szMessage, "오늘 발생할수 있는 아이템수를 초과했습니다(%d/%d)",
								DefaultItems[cnt].sGenDay[1], DefaultItems[cnt].sGenDay[0]);

							TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
							TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
							TransChatMessage.dwIP = 0;
							TransChatMessage.dwObjectSerial = 0;

							lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
						}
#endif


						for(cnt = 0; cnt < DefaultItemCount; cnt++)
						{
							if(DefaultItems[cnt].Item.CODE == pCraftItem_Server->DesCraftItem.sItemInfo.CODE)
							{
								break;
							}
						}
						if(cnt >= DefaultItemCount)
							return FALSE;
					}

					DefaultItems[cnt].sGenDay[1]++;

					if((DefaultItems[cnt].Item.CODE&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
					{

						PotionCount = pCraftItem_Server->DesCraftItem.sItemInfo.PotionCount;
						CreateDefItem(&pCraftItem_Server->DesCraftItem.sItemInfo, &DefaultItems[cnt]);
						pCraftItem_Server->DesCraftItem.sItemInfo.PotionCount = PotionCount;

						rsAddServerPotion(lpPlayInfo, pCraftItem_Server->DesCraftItem.sItemInfo.CODE, PotionCount);
					}
					else
					{
						CreateDefItem(&pCraftItem_Server->DesCraftItem.sItemInfo, &DefaultItems[cnt], -1);
					}
					break;
				}
			}
		}
		if(cnt < DefaultItemCount)
		{



			ReformItem(&pCraftItem_Server->DesCraftItem.sItemInfo);

			rsAddInvenItem(lpPlayInfo, pCraftItem_Server->DesCraftItem.sItemInfo.CODE,
				pCraftItem_Server->DesCraftItem.sItemInfo.ItemHeader.Head,
				pCraftItem_Server->DesCraftItem.sItemInfo.ItemHeader.dwChkSum);


			rsRecord_ItemLog2(lpPlayInfo,
				pCraftItem_Server->DesCraftItem.sItemInfo.CODE,
				pCraftItem_Server->DesCraftItem.sItemInfo.ItemHeader.Head,
				pCraftItem_Server->DesCraftItem.sItemInfo.ItemHeader.dwChkSum,
				ITEMLOG_GETWING);

			pCraftItem_Server->size = sizeof(sCRAFTITEM_SERVER);
			if(lpPlayInfo && lpPlayInfo->lpsmSock)
			{
				lpPlayInfo->lpsmSock->Send((char *)pCraftItem_Server, pCraftItem_Server->size, TRUE);
			}

			return TRUE;
		}
	}




	smTransCommand.WParam = 99000;
	smTransCommand.SParam = 1;
	smTransCommand.LParam = sItemInfo.CODE;
	RecordHackLogFile(lpPlayInfo, &smTransCommand);

	pCraftItem_Server->size = sizeof(sCRAFTITEM_SERVER);;
	pCraftItem_Server->Result = FALSE;

	if(lpPlayInfo && lpPlayInfo->lpsmSock)
	{
		lpPlayInfo->lpsmSock->Send((char *)pCraftItem_Server, pCraftItem_Server->size, TRUE);
	}

	return TRUE;
}

#ifdef _W_SERVER


int rsRecvMakeLinkCore(rsPLAYINFO *lpPlayInfo, TRANS_ITEMINFO *lpTransItemInfo)
{
	int len, len2;

	if(lpPlayInfo->getName().empty() || CheckItemForm(&lpTransItemInfo->Item) == FALSE) return FALSE;


	if(rsDeleteInvenItem(lpPlayInfo, lpTransItemInfo->Item.CODE, lpTransItemInfo->Item.ItemHeader.Head, lpTransItemInfo->Item.ItemHeader.dwChkSum) < 0)
		return FALSE;


	lpTransItemInfo->Item.BackUpKey = lpTransItemInfo->Item.ItemHeader.Head;
	lpTransItemInfo->Item.BackUpChkSum = lpTransItemInfo->Item.ItemHeader.dwChkSum;

	len = lstrlen(lpTransItemInfo->Item.ItemName) + 1;
	len2 = lpPlayInfo->getName().size();

	if((len + len2) > 32)
	{
		return FALSE;
	}

	strcpy_s(lpTransItemInfo->Item.ItemName + len, sizeof(lpTransItemInfo->Item.ItemName) - len, lpPlayInfo->getName().c_str());

	ReformItem(&lpTransItemInfo->Item);


	rsAddInvenItem(lpPlayInfo, lpTransItemInfo->Item.CODE, lpTransItemInfo->Item.ItemHeader.Head, lpTransItemInfo->Item.ItemHeader.dwChkSum);

	lpPlayInfo->lpsmSock->Send((char *)lpTransItemInfo, lpTransItemInfo->size, TRUE);

	return TRUE;
}


int rsRecvUseLinkCore(rsPLAYINFO *lpPlayInfo, TRANS_ITEMINFO *lpTransItemInfo)
{
	char *szName;
	int len;
	rsPLAYINFO *lpPlayInfo2;
	TRANS_CHATMESSAGE	TransChatMessage;
	smTRANS_COMMAND_EX	smTransCommandEx;
	STG_AREA	*lpStgArea;

	if(!lpPlayInfo->lpsmSock) return FALSE;
	if(CheckItemForm(&lpTransItemInfo->Item) == FALSE) return FALSE;


	lpTransItemInfo->Item.ItemName[31] = 0;
	len = lstrlen(lpTransItemInfo->Item.ItemName);

	szName = &lpTransItemInfo->Item.ItemName[len + 1];
	if(!szName[0]) return FALSE;

	lpPlayInfo2 = FindUserFromName(szName);

	if(!lpPlayInfo2 || !lpPlayInfo2->dwObjectSerial || !lpPlayInfo->dwClanCode || lpPlayInfo->EventMode || lpPlayInfo2->EventMode ||
		rsCheckHardCoreEventArea(lpPlayInfo2->Position.x, lpPlayInfo2->Position.y, lpPlayInfo2->Position.z) == TRUE ||
		lpPlayInfo->Position.Area == QUEST_ARENA_FIELD || lpPlayInfo2->Position.Area == rsCASTLE_FIELD)
	{

		strcpy_s(TransChatMessage.szMessage, szNotLinkCore);
		TransChatMessage.code = OpCode::OPCODE_MESSAGEBOX;
		TransChatMessage.dwIP = 0;
		TransChatMessage.dwObjectSerial = 0;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);

		lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
		return FALSE;
	}

	if(lpPlayInfo2->dwClanCode != lpPlayInfo->dwClanCode)
	{
		strcpy_s(TransChatMessage.szMessage, szNotLinkCore2);
		TransChatMessage.code = OpCode::OPCODE_MESSAGEBOX;
		TransChatMessage.dwIP = 0;
		TransChatMessage.dwObjectSerial = 0;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);

		lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
		return FALSE;
	}

	lpStgArea = FindStageField(lpPlayInfo2->Position.x, lpPlayInfo2->Position.z);

	if(lpStgArea)
	{

		if(lpStgArea->lpField)
		{
			if(lpPlayInfo->smCharInfo.Level < FieldLimitLevel_Table[lpStgArea->lpField->FieldCode] ||
				lpStgArea->lpField->FieldCode == QUEST_ARENA_FIELD)
			{

				strcpy_s(TransChatMessage.szMessage, szNotLinkCore3);
				TransChatMessage.code = OpCode::OPCODE_MESSAGEBOX;
				TransChatMessage.dwIP = 0;
				TransChatMessage.dwObjectSerial = 0;
				TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);

				lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
				return FALSE;
			}
		}

		smTransCommandEx.code = OpCode::OPCODE_USE_LINKCORE;
		smTransCommandEx.size = sizeof(smTRANS_COMMAND_EX);
		smTransCommandEx.WxParam = lpTransItemInfo->Item.CODE;
		smTransCommandEx.LxParam = lpTransItemInfo->Item.ItemHeader.Head;
		smTransCommandEx.SxParam = lpTransItemInfo->Item.ItemHeader.dwChkSum;
		smTransCommandEx.ExParam = 0;
		smTransCommandEx.WParam = lpPlayInfo2->Position.x;
		smTransCommandEx.LParam = lpPlayInfo2->Position.y;
		smTransCommandEx.SParam = lpPlayInfo2->Position.z;
		smTransCommandEx.EParam = lpStgArea->lpField->FieldCode;

		lpPlayInfo->lpsmSock->Send((char *)&smTransCommandEx, smTransCommandEx.size, TRUE);
		return TRUE;
	}

	return FALSE;
}

#endif



int	rsPlayHealing(smTRANS_COMMAND *lpTransCommand)
{
	smCHAR	*lpChar;
	rsPLAYINFO *lpPlayInfo;

	lpChar = srFindCharFromSerial(lpTransCommand->SParam);
	if(lpChar)
	{

		if(lpChar && lpChar->smCharInfo.Life[0] > 0)
		{
			if(!lpChar->DontMoveFlag || lpChar->smCharInfo.dwCharSoundCode != snCHAR_SOUND_CASTLE_TOWER_B)
			{
#ifdef _LANGUAGE_PHILIPIN
				if(lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_DOOR ||
					lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_TOWER_B
					)
					return TRUE;
#else

				if(lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_DOOR




					)
					return TRUE;
#endif

				lpChar->smCharInfo.Life[0] += lpTransCommand->WParam;
				if(lpChar->smCharInfo.Life[0] > lpChar->smCharInfo.Life[1])
					lpChar->smCharInfo.Life[0] = lpChar->smCharInfo.Life[1];
			}
		}
		return TRUE;
	}
	lpPlayInfo = srFindUserFromSerial(lpTransCommand->SParam);
	if(lpPlayInfo && lpPlayInfo->lpsmSock)
	{

		if(lpPlayInfo->dwSkill_VirtualLife_Time && lpPlayInfo->dwSkill_VirtualLife_Time > dwPlayServTime)
		{

			lpTransCommand->WParam -= (lpTransCommand->WParam*lpPlayInfo->dwSkill_VirtualLife_Param) / 100;
		}


		lpPlayInfo->lpsmSock->Send((char *)lpTransCommand, lpTransCommand->size, TRUE);
		return TRUE;
	}

	return	FALSE;
}

int rsPlayGrandHealing(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	int cnt;
	rsPLAYINFO *lpPartyMaster;
	smTRANS_COMMAND	smTransCommand;

	if(lpPlayInfo->dwPartyInfo && lpPlayInfo->lpPartyMaster)
	{
		lpPartyMaster = lpPlayInfo->lpPartyMaster;

		memcpy(&smTransCommand, lpTransCommand, sizeof(smTRANS_COMMAND));

		for(cnt = 0; cnt < lpPartyMaster->PartyUserCount; cnt++)
		{
			if(lpPartyMaster->lpPartyPlayers[cnt] && lpPartyMaster->lpPartyPlayers[cnt]->lpsmSock)
			{

				if(lpPlayInfo != lpPartyMaster->lpPartyPlayers[cnt])
				{

					if(lpPlayInfo->dwSkill_VirtualLife_Time && lpPlayInfo->dwSkill_VirtualLife_Time > dwPlayServTime)
					{

						smTransCommand.LParam = lpTransCommand->LParam;
						smTransCommand.LParam -= (lpTransCommand->LParam*lpPlayInfo->dwSkill_VirtualLife_Param) / 100;
						lpPartyMaster->lpPartyPlayers[cnt]->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
					}
					else
					{
						lpPartyMaster->lpPartyPlayers[cnt]->lpsmSock->Send((char *)lpTransCommand, lpTransCommand->size, TRUE);
					}
				}

			}
		}
	}


	return TRUE;
}


int	rsPlayHolyMind(smTRANS_COMMAND *lpTransCommand)
{
	smCHAR	*lpChar;
	int time;
	int bio;

	lpChar = srFindCharFromSerial(lpTransCommand->SParam);
	if(lpChar)
	{
		time = lpTransCommand->LParam << 4;
		bio = lpChar->smCharInfo.Resistance[sITEMINFO_BIONIC];
		if(bio < 0) bio = 0;
		if(bio > 100) bio = 100;
		time = (time*(100 - bio)) / 100;
		if(time > 0)
		{
			lpChar->PlayHolyMind[0] = lpTransCommand->WParam;
			lpChar->PlayHolyMind[1] = time;
		}
		return TRUE;
	}



	return FALSE;
}


int rsCheck_ResulSOD(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND_EX *lpTransCommandEx)
{
	DWORD Code;

#ifdef _W_SERVER
	Code = 0x0c5c55cc;

	Code ^= lpTransCommandEx->WParam << 1;
	Code ^= lpTransCommandEx->LParam << 2;
	Code ^= lpTransCommandEx->SParam << 3;
	Code ^= lpTransCommandEx->EParam << 4;

	Code ^= lpTransCommandEx->WxParam << 16;
	Code ^= lpTransCommandEx->LxParam << 17;
	Code ^= lpTransCommandEx->SxParam << 18;

	Code ^= lpPlayInfo->dwObjectSerial << 16;

#else
	Code = 0x3ea832ff;
#endif

	return Code & 0x7FFFFFFF;
}


int rsSend_ResultSOD(rsPLAYINFO *lpPlayInfo, int Point, int KillCount, int TotalPoint, int TotalSucessUser, int TotalUser, int SoDCode)
{
	smTRANS_COMMAND_EX	smTransCommand;

	smTransCommand.code = OpCode::OPCODE_SOD_RESULT;
	smTransCommand.size = sizeof(smTRANS_COMMAND_EX);
	smTransCommand.WParam = lpPlayInfo->smCharInfo.Level;
	smTransCommand.LParam = Point;
	smTransCommand.SParam = KillCount;
	smTransCommand.EParam = SoDCode;
	smTransCommand.WxParam = TotalPoint;
	smTransCommand.LxParam = TotalSucessUser;
	smTransCommand.SxParam = TotalUser;
	smTransCommand.ExParam = rsCheck_ResulSOD(lpPlayInfo, &smTransCommand);
	rsSendDataServer(lpPlayInfo->lpsmSock, &smTransCommand);

	return TRUE;
}




int rsCompAttackData(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	int avg1, avg2;
	smTRANS_COMMAND	smTransCommand;

	if(lpPlayInfo->Send_AttackCount > 255)
	{
		avg1 = lpPlayInfo->Send_AttackDamage / lpPlayInfo->Send_AttackCount;
		if(lpTransCommand->WParam)
			avg2 = (-lpTransCommand->LParam) / (-lpTransCommand->WParam);
		else
			avg2 = 0;

		if(avg1 > (((avg2 * 340) >> 8) + 16) && lpPlayInfo->WarningCount < 10)
		{


			smTransCommand.code = OpCode::OPCODE_SET_BLACKLIST;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = 8110;
			smTransCommand.LParam = avg1;
			smTransCommand.SParam = avg2;
			smTransCommand.EParam = lpPlayInfo->Send_AttackCount;
			if(lpPlayInfo)
			{
				rsSendDataServer(lpPlayInfo->lpsmSock, &smTransCommand);
			}
			lpPlayInfo->WarningCount++;
		}
	}


	return TRUE;
}


int CheckInvenItemPosition(rsPLAYINFO *lpPlayInfo, TRANS_USINGITEM *lpTransUsingItem)
{

#ifdef _W_SERVER

	int cnt, cnt2;
	int Pos;
	DWORD dwCode;
	int	MaxAttack;
	smTRANS_COMMAND	smTransCommand;

	MaxAttack = 4;

	int	PosOk;

	for(cnt = 0; cnt < lpTransUsingItem->ItemListCount; cnt++)
	{
		dwCode = lpTransUsingItem->ItemList[cnt].dwCode&sinITEM_MASK2;
		Pos = lpTransUsingItem->ItemList[cnt].Performance[0] & 0xFF;
		PosOk = TRUE;


		if(lpTransUsingItem->ItemList[cnt].Performance[1] > MaxAttack)
			MaxAttack = lpTransUsingItem->ItemList[cnt].Performance[1];

		if((dwCode&sinITEM_MASK1) == 0x01000000)
			dwCode = sinWA1;
		if((dwCode&sinITEM_MASK1) == 0x04000000)
			dwCode = sinPM1;


		switch(dwCode)
		{
		case sinWA1:
			if(Pos != 1)
				PosOk = FALSE;
			break;
		case sinDA1:
		case sinDA2:
			if(Pos != 3)
				PosOk = FALSE;
			break;

		case sinDB1:
			if(Pos != 10)
				PosOk = FALSE;
			break;

		case sinDG1:
			if(Pos != 9)
				PosOk = FALSE;
			break;

		case sinDS1:
		case sinOM1:
			if(Pos != 2)
				PosOk = FALSE;
			break;


		case sinPM1:
			if(Pos < 11 || Pos>13)
				PosOk = FALSE;
			break;

		case sinOS1:
			if(Pos != 7)
				PosOk = FALSE;
			break;

		case sinOA1:
			if(Pos != 4)
				PosOk = FALSE;
			break;
		case sinOA2:
			if(Pos != 8)
				PosOk = FALSE;
			break;
		case sinOR1:
			if(Pos != 5 && Pos != 6)
				PosOk = FALSE;
			break;
		}

		if(PosOk == FALSE)
		{


			smTransCommand.code = OpCode::OPCODE_SET_BLACKLIST;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = 8040;
			smTransCommand.LParam = lpTransUsingItem->ItemList[cnt].dwCode;
			smTransCommand.SParam = 0;
			smTransCommand.EParam = lpTransUsingItem->ItemList[cnt].Performance[0];

			if(lpPlayInfo)
			{
				rsSendDataServer(lpPlayInfo->lpsmSock, &smTransCommand);
			}

			return FALSE;
		}

		for(cnt2 = 0; cnt2 < lpTransUsingItem->ItemListCount; cnt2++)
		{
			if(cnt != cnt2)
			{
				if(lpTransUsingItem->ItemList[cnt].Performance[0] == lpTransUsingItem->ItemList[cnt2].Performance[0])
				{


					smTransCommand.code = OpCode::OPCODE_SET_BLACKLIST;
					smTransCommand.size = sizeof(smTRANS_COMMAND);
					smTransCommand.WParam = 8040;
					smTransCommand.LParam = lpTransUsingItem->ItemList[cnt].dwCode;
					smTransCommand.SParam = lpTransUsingItem->ItemList[cnt2].dwCode;
					smTransCommand.EParam = lpTransUsingItem->ItemList[cnt2].Performance[0];

					if(lpPlayInfo)
					{
						rsSendDataServer(lpPlayInfo->lpsmSock, &smTransCommand);
					}

					return FALSE;
				}
			}
		}
	}

#endif
	return TRUE;
}


int CheckInvenItemPosition2(rsPLAYINFO *lpPlayInfo, TRANS_USINGITEM *lpTransUsingItem)
{

#ifdef _W_SERVER

	int cnt, cnt2;
	int Pos;
	DWORD dwCode;
	int	MaxAttack;
	smTRANS_COMMAND	smTransCommand;
	int	eWeapon, eShield;
	DWORD eWeaponCode, eShieldCode;

	MaxAttack = 4;
	eWeapon = 0;
	eShield = 0;

	int	PosOk;

	for(cnt = 0; cnt < lpTransUsingItem->ItemListCount; cnt++)
	{
		dwCode = lpTransUsingItem->ItemList[cnt].dwCode&sinITEM_MASK2;
		Pos = lpTransUsingItem->ItemList[cnt].Performance[0] & 0xFF;
		PosOk = TRUE;


		if(lpTransUsingItem->ItemList[cnt].Performance[1] > MaxAttack)
			MaxAttack = lpTransUsingItem->ItemList[cnt].Performance[1];

		if((dwCode&sinITEM_MASK1) == 0x01000000)
			dwCode = sinWA1;
		if((dwCode&sinITEM_MASK1) == 0x04000000)
			dwCode = sinPM1;


		switch(dwCode)
		{
		case sinWA1:
			if(Pos != 1)
				PosOk = FALSE;

			eWeapon++;
			eWeaponCode = lpTransUsingItem->ItemList[cnt].dwCode;
			break;
		case sinDA1:
		case sinDA2:
			if(Pos != 3)
				PosOk = FALSE;
			break;

		case sinDB1:
			if(Pos != 10)
				PosOk = FALSE;
			break;

		case sinDG1:
			if(Pos != 9)
				PosOk = FALSE;
			break;

		case sinDS1:
		case sinOM1:
			if(Pos != 2)
				PosOk = FALSE;

			eShield++;
			eShieldCode = lpTransUsingItem->ItemList[cnt].dwCode;
			break;


		case sinPM1:
			if(Pos < 11 || Pos>13)
				PosOk = FALSE;
			break;

		case sinOS1:
			if(Pos != 7)
				PosOk = FALSE;
			break;

		case sinOA1:
			if(Pos != 4)
				PosOk = FALSE;
			break;
		case sinOA2:
			if(Pos != 8)
				PosOk = FALSE;
			break;
		case sinOR1:
			if(Pos != 5 && Pos != 6)
				PosOk = FALSE;
			break;
		}

		if(PosOk == FALSE)
		{


			smTransCommand.code = OpCode::OPCODE_SET_BLACKLIST;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = 8040;
			smTransCommand.LParam = lpTransUsingItem->ItemList[cnt].dwCode;
			smTransCommand.SParam = 0;
			smTransCommand.EParam = lpTransUsingItem->ItemList[cnt].Performance[0];

			if(lpPlayInfo)
			{
				rsSendDataServer(lpPlayInfo->lpsmSock, &smTransCommand);
			}

			return FALSE;
		}

		for(cnt2 = 0; cnt2 < lpTransUsingItem->ItemListCount; cnt2++)
		{
			if(cnt != cnt2)
			{
				if(lpTransUsingItem->ItemList[cnt].Performance[0] == lpTransUsingItem->ItemList[cnt2].Performance[0])
				{


					smTransCommand.code = OpCode::OPCODE_SET_BLACKLIST;
					smTransCommand.size = sizeof(smTRANS_COMMAND);
					smTransCommand.WParam = 8040;
					smTransCommand.LParam = lpTransUsingItem->ItemList[cnt].dwCode;
					smTransCommand.SParam = lpTransUsingItem->ItemList[cnt2].dwCode;
					smTransCommand.EParam = lpTransUsingItem->ItemList[cnt2].Performance[0];

					if(lpPlayInfo)
					{
						rsSendDataServer(lpPlayInfo->lpsmSock, &smTransCommand);
					}

					return FALSE;
				}
			}
		}
	}


	if(eShield && eWeapon)
	{
		for(cnt = 0; cnt < MAX_ITEM; cnt++)
		{
			if(sItem[cnt].CODE == (sinGG1 | sin01)) break;

			if(sItem[cnt].CODE == eWeaponCode)
			{
				if(sItem[cnt].Class == ITEM_CLASS_WEAPON_TWO)
				{
					smTransCommand.code = OpCode::OPCODE_SET_BLACKLIST;
					smTransCommand.size = sizeof(smTRANS_COMMAND);
					smTransCommand.WParam = 8040;
					smTransCommand.LParam = eWeaponCode;
					smTransCommand.SParam = eShieldCode;
					smTransCommand.EParam = -1;

					if(lpPlayInfo)
					{
						rsSendDataServer(lpPlayInfo->lpsmSock, &smTransCommand);
					}
					return FALSE;
				}
				break;
			}
		}
	}



#endif
	return TRUE;
}



int rsRecvRecordTradeItem(rsPLAYINFO *lpPlayInfo, TRANS_RECORD_TRADE_ITEMS *lpTransRecordTradeItems)
{

	return TRUE;
}



int rsCheckItemTempCode(rsPLAYINFO *lpPlayInfo, sITEMINFO *lpItem)
{

#ifdef _W_SERVER
	if(lpItem->ItemHeader.dwChkSum == (lpItem->Temp0 - lpItem->CODE))
	{
		return TRUE;
	}
	if((lpItem->CODE&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
	{
		return TRUE;
	}


	smTRANS_COMMAND	smTransCommand;
	smTransCommand.code = OpCode::OPCODE_SET_BLACKLIST;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 6810;
	smTransCommand.LParam = lpItem->CODE;
	smTransCommand.SParam = lpItem->ItemHeader.Head;
	smTransCommand.EParam = lpItem->ItemHeader.dwChkSum;

	if(lpPlayInfo)
	{
		rsSendDataServer(lpPlayInfo->lpsmSock, &smTransCommand);
	}

#endif
	return FALSE;
}




int	rsCheckItemCode(rsPLAYINFO *lpPlayInfo, sITEMINFO *lpItem)
{
#ifdef _W_SERVER
	int result;

	TRANS_ITEM_CODE	TransItemCode;

	if(!lpItem->ItemName[0]) return TRUE;

	result = CheckItemForm(lpItem);

	if(result == TRUE) result = CheckMixItem(lpItem);


	if(result == TRUE)
	{

		rsCheckItemTempCode(lpPlayInfo, lpItem);

		return TRUE;
	}

#ifndef	_NEW_ITEM_FORMCODE

	return TRUE;

#endif




	if(lpItem->ItemHeader.Head == 0 || (lpItem->CODE&sinITEM_MASK2) == sinQT1)
	{
		return TRUE;
	}



	TransItemCode.code = OpCode::OPCODE_ERRORITEM;
	TransItemCode.size = sizeof(TRANS_ITEM_CODE);
	TransItemCode.dwFlag = FALSE;
	TransItemCode.dwHead = lpItem->ItemHeader.Head;
	TransItemCode.dwChkSum = lpItem->ItemHeader.dwChkSum;
	TransItemCode.dwItemCode = lpItem->CODE;
	TransItemCode.dwTime = 0;
	if(lpPlayInfo && lpPlayInfo->lpsmSock)
	{
		lpPlayInfo->lpsmSock->Send((char *)&TransItemCode, TransItemCode.size, TRUE);
	}


	smTRANS_COMMAND	smTransCommand;
	smTransCommand.code = OpCode::OPCODE_SET_BLACKLIST;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 6800;
	smTransCommand.LParam = lpItem->CODE;
	smTransCommand.SParam = lpItem->ItemHeader.Head;
	smTransCommand.EParam = lpItem->ItemHeader.dwChkSum;
	rsSendDataServer(lpPlayInfo->lpsmSock, &smTransCommand);

	char	*szErrorItemDir = "ItemError";
	char	szBuff[256];
	FILE	*fp;

	CreateDirectory(szErrorItemDir, NULL);
	wsprintf(szBuff, "%s\\%s(%d).itm", szErrorItemDir, lpPlayInfo->smCharInfo.szName, lpItem->ItemHeader.dwChkSum);
	fp = fopen(szBuff, "wb");
	if(fp)
	{
		fwrite(lpItem, sizeof(sITEMINFO), 1, fp);
		fclose(fp);
	}


#endif

	return TRUE;
}





#ifdef	_W_SERVER


int	rsRegist_ItemSecCode(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND_EX *lpTransCommandEx)
{

	if(!rsServerConfig.ServerInventoryMode) return 1;

	DWORD	cnt;
	DWORD	Key;

	DWORD	dwOs = lpPlayInfo->dwObjectSerial;
	DWORD	dwCode_Name = lpPlayInfo->dwCode_Name;
	DWORD	dwSvCode = rsServerConfig.ServerCode;
	DWORD	dwSndCount = lpPlayInfo->SndItemSecCodeCount;
	DWORD	dwItemChkSum = lpTransCommandEx->LParam^lpTransCommandEx->SParam;
	DWORD	dwSeCode[4];

	Key = (dwPlayServTime & 0xFFFF) ^ lpTransCommandEx->SParam;
	Key = Key ^ (Key << 10);

	if((lpTransCommandEx->WParam&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
	{

		Key &= 0xFFFF0000;
		cnt = lpTransCommandEx->EParam^lpTransCommandEx->SParam^lpTransCommandEx->code;
		if(cnt == 0) cnt = 1;
		Key |= (cnt & 0xFFFF) ^ 0x3c15;
	}


	dwSeCode[0] = (dwSvCode << 16) | (dwSndCount & 0xFFFF);
	dwSeCode[0] &= 0x7FFFFFFF;

	dwSeCode[1] = dwItemChkSum ^ ((dwCode_Name & 0xFFFF) | (lpPlayInfo->dwObjectSerial << 16));
	dwSeCode[2] = lpTransCommandEx->ExParam^dwSeCode[0] ^ dwSeCode[1];
	dwSeCode[3] = Key;

	lpTransCommandEx->WxParam = dwSeCode[0] ^ (XOR_ITEM_SeCode_0^rsRegist_EnterKey(Key^lpPlayInfo->dwObjectSerial, 0));
	lpTransCommandEx->LxParam = dwSeCode[1] ^ (XOR_ITEM_SeCode_1^rsRegist_EnterKey(Key^lpPlayInfo->dwObjectSerial, 1));
	lpTransCommandEx->SxParam = dwSeCode[2] ^ (XOR_ITEM_SeCode_2^rsRegist_EnterKey(Key^lpPlayInfo->dwObjectSerial, 2));
	lpTransCommandEx->ExParam = dwSeCode[3];

	lpPlayInfo->SndItemSecCodeCount++;

	return TRUE;
}




int	rsRegist_ItemSecCode(rsPLAYINFO *lpPlayInfo, TRANS_ITEMINFO *lpTransItemInfo, int NewItem)
{



	if(!rsServerConfig.ServerInventoryMode) return 1;

	DWORD	cnt;
	DWORD	Key;

	DWORD	dwOs = lpPlayInfo->dwObjectSerial;
	DWORD	dwCode_Name = lpPlayInfo->dwCode_Name;
	DWORD	dwSvCode = rsServerConfig.ServerCode;
	DWORD	dwSndCount = lpPlayInfo->SndItemSecCodeCount;
	DWORD	dwItemChkSum = lpTransItemInfo->Item.ItemHeader.dwChkSum^lpTransItemInfo->Item.ItemHeader.Head;


	Key = (dwPlayServTime & 0xFFFF) ^ dwItemChkSum;
	Key = Key ^ (Key << 10);

	if((lpTransItemInfo->Item.CODE&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
	{

		Key &= 0xFFFF0000;
		cnt = lpTransItemInfo->Item.PotionCount;
		if(cnt == 0) cnt = 1;
		Key |= (cnt & 0xFFFF) ^ 0x3c15;
	}

	lpTransItemInfo->dwSeCode[0] = (dwSvCode << 16) | (dwSndCount & 0xFFFF);
	if(NewItem) lpTransItemInfo->dwSeCode[0] |= 0x8000000;
	else lpTransItemInfo->dwSeCode[0] &= 0x7FFFFFFF;

	lpTransItemInfo->dwSeCode[1] = dwItemChkSum ^ ((dwCode_Name & 0xFFFF) | (lpPlayInfo->dwObjectSerial << 16));
	lpTransItemInfo->dwSeCode[2] = lpTransItemInfo->Item.Money^lpTransItemInfo->dwSeCode[0] ^ lpTransItemInfo->dwSeCode[1];
	lpTransItemInfo->dwSeCode[3] = Key;

	lpTransItemInfo->dwSeCode[0] ^= (XOR_ITEM_SeCode_0^rsRegist_EnterKey(Key^lpPlayInfo->dwObjectSerial, 0));
	lpTransItemInfo->dwSeCode[1] ^= (XOR_ITEM_SeCode_1^rsRegist_EnterKey(Key^lpPlayInfo->dwObjectSerial, 1));
	lpTransItemInfo->dwSeCode[2] ^= (XOR_ITEM_SeCode_2^rsRegist_EnterKey(Key^lpPlayInfo->dwObjectSerial, 2));

	lpPlayInfo->SndItemSecCodeCount++;

	return TRUE;
}


int rsDEBUG_SecCode_SvCode;
int rsDEBUG_SecCode_SndCount;



int	rsCheck_ItemSecCode(rsPLAYINFO *lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum, int Money, DWORD dwSeCode_0, DWORD dwSeCode_1, DWORD dwSeCode_2, DWORD dwSeCode_3, int *pPotionCount)
{
	DWORD	cnt;
	DWORD	Key;

	DWORD	dwSeCode[4];
	smTRANS_COMMAND	smTransCommand;



	if(!rsServerConfig.ServerInventoryMode) return 1;

	Key = dwSeCode_3;

	if((dwCode&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
		*pPotionCount = (Key & 0xFFFF) ^ 0x3c15;
	else
		*pPotionCount = 0;

	dwSeCode[0] = dwSeCode_0 ^ (XOR_ITEM_SeCode_0^rsRegist_EnterKey(Key^lpPlayInfo->dwObjectSerial, 0));
	dwSeCode[1] = dwSeCode_1 ^ (XOR_ITEM_SeCode_1^rsRegist_EnterKey(Key^lpPlayInfo->dwObjectSerial, 1));
	dwSeCode[2] = dwSeCode_2 ^ (XOR_ITEM_SeCode_2^rsRegist_EnterKey(Key^lpPlayInfo->dwObjectSerial, 2));

	DWORD	dwSvCode;
	DWORD	dwCmpCode;
	int SndCount;

	dwCmpCode = (dwHead^dwChkSum) ^ ((lpPlayInfo->dwCode_Name & 0xFFFF) | (lpPlayInfo->dwObjectSerial << 16));
	if(dwSeCode[1] != dwCmpCode)
	{

		smTransCommand.WParam = 8020;
		smTransCommand.LParam = 1;
		smTransCommand.SParam = dwSeCode[1];
		smTransCommand.EParam = dwCmpCode;
		RecordHackLogFile(lpPlayInfo, &smTransCommand);

		return NULL;
	}

	dwCmpCode = Money^dwSeCode[0] ^ dwSeCode[1];
	if(dwCmpCode != dwSeCode[2])
	{

		smTransCommand.WParam = 8020;
		smTransCommand.LParam = 2;
		smTransCommand.SParam = dwSeCode[2];
		smTransCommand.EParam = dwCmpCode;
		RecordHackLogFile(lpPlayInfo, &smTransCommand);

		return NULL;
	}

	dwSvCode = (dwSeCode[0] & 0x7FFFFFF) >> 16;
	SndCount = dwSeCode[0] & 0xFFFF;
	if(dwSvCode >= 8)
	{
		return NULL;
	}


	rsDEBUG_SecCode_SvCode = dwSvCode;
	rsDEBUG_SecCode_SndCount = SndCount;


	int	Min, Max, sCnt;
	int	MinCnt;

	Min = 0xFFFF;
	Max = 0;

	for(cnt = 0; cnt < 16; cnt++)
	{
		sCnt = lpPlayInfo->RcvItemSecCodeBuff[dwSvCode][cnt];

		if(sCnt > Max) Max = sCnt;
		if(sCnt < Min)
		{
			Min = sCnt; MinCnt = cnt;
		}
		if(SndCount == sCnt)
		{

			smTransCommand.WParam = 8020;
			smTransCommand.LParam = 3;
			smTransCommand.SParam = dwSvCode;
			smTransCommand.EParam = SndCount;
			RecordHackLogFile(lpPlayInfo, &smTransCommand);
			return NULL;
		}
	}

	if((Max - 16) > SndCount)
	{

		smTransCommand.WParam = 8020;
		smTransCommand.LParam = 4;
		smTransCommand.SParam = Max;
		smTransCommand.EParam = SndCount;
		RecordHackLogFile(lpPlayInfo, &smTransCommand);
		return NULL;
	}

	if(SndCount > Max)
	{
		lpPlayInfo->RcvItemSecCodeBuff[dwSvCode][MinCnt] = SndCount;
	}

	if(dwSeCode[0] & 0x7FFFFFF) return 2;

	return 1;
}

#else


int	rsRegist_ItemSecCode(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND_EX *lpTransCommandEx)
{
	return	TRUE;
}

int	rsRegist_ItemSecCode(rsPLAYINFO *lpPlayInfo, TRANS_ITEMINFO *lpTransItemInfo, int NewItem)
{
	return	TRUE;
}

int	rsCheck_ItemSecCode(rsPLAYINFO *lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum, int Money, DWORD dwSeCode_0, DWORD dwSeCode_1, DWORD dwSeCode_2, DWORD dwSeCode_3, int *pPotionCount)
{
	return	TRUE;
}

#endif



int rsRecvBuyShopItem(rsPLAYINFO *lpPlayInfo, TRANS_BUY_SHOPITEM *lpTransBuyShopItem)
{
	int money;

	if(!rsServerConfig.ServerInventoryMode)
	{
		lpPlayInfo->ServerMoney = 100000000;
	}


	if(!rsServerConfig.TestSeverMode)
	{
		if((lpTransBuyShopItem->sItem.sItemInfo.CODE&sinITEM_MASK2) == sinPM1) return FALSE;

	}

	if(CheckItemForm(&lpTransBuyShopItem->sItem.sItemInfo) == TRUE &&
		lpTransBuyShopItem->sItem.sItemInfo.Price <= lpPlayInfo->ServerMoney &&
		lpTransBuyShopItem->sItem.sItemInfo.dwCreateTime == 0)
	{


		ReformItem(&lpTransBuyShopItem->sItem.sItemInfo);
		if(lpPlayInfo && lpPlayInfo->lpsmSock)
		{


			rsAddInvenItem(lpPlayInfo, lpTransBuyShopItem->sItem.sItemInfo.CODE,
				lpTransBuyShopItem->sItem.sItemInfo.ItemHeader.Head,
				lpTransBuyShopItem->sItem.sItemInfo.ItemHeader.dwChkSum);



			rsRecord_ItemLOG(lpPlayInfo,
				lpTransBuyShopItem->sItem.sItemInfo.CODE,
				lpTransBuyShopItem->sItem.sItemInfo.ItemHeader.Head,
				lpTransBuyShopItem->sItem.sItemInfo.ItemHeader.dwChkSum,
				ITEMLOG_BUYSHOP);


			if(lpTransBuyShopItem->ItemCount > 0 && (lpTransBuyShopItem->sItem.sItemInfo.CODE&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
			{

				money = lpTransBuyShopItem->sItem.sItemInfo.Price*lpTransBuyShopItem->ItemCount;
				lpPlayInfo->SubServerMoney(money, WHERE_BUY_POTION);
				rsAddServerPotion(lpPlayInfo, lpTransBuyShopItem->sItem.sItemInfo.CODE, lpTransBuyShopItem->ItemCount);

				switch((lpTransBuyShopItem->sItem.sItemInfo.CODE&sinITEM_MASK2))
				{
				case sinPL1:
					CurrencyLog.int64_ShopPotionMoney[0] += money;
					break;
				case sinPM1:
					CurrencyLog.int64_ShopPotionMoney[1] += money;
					break;
				case sinPS1:
					CurrencyLog.int64_ShopPotionMoney[2] += money;
					break;
				}

			}
			else
			{
				lpPlayInfo->SubServerMoney(lpTransBuyShopItem->sItem.sItemInfo.Price, WHERE_BUY_ITEM);
				CurrencyLog.int64_ShopMoney += lpTransBuyShopItem->sItem.sItemInfo.Price;
			}

			return lpPlayInfo->lpsmSock->Send((char *)lpTransBuyShopItem, lpTransBuyShopItem->size, TRUE);
		}
	}

	if(lpTransBuyShopItem->sItem.sItemInfo.Price > lpPlayInfo->ServerMoney)
	{
		smTRANS_COMMAND	smTransCommand;

		smTransCommand.WParam = 8010;
		smTransCommand.LParam = 10;
		smTransCommand.SParam = lpPlayInfo->ServerMoney;
		smTransCommand.EParam = lpTransBuyShopItem->sItem.sItemInfo.Price;
		RecordHackLogFile(lpPlayInfo, &smTransCommand);

	}

	return FALSE;
}


int rsRecvSellShopItem(rsPLAYINFO *lpPlayInfo, TRANS_ITEMINFO *lpTransItemInfo)
{
	smTRANS_COMMAND		smTransCommand;
	smTRANS_COMMAND_EX	smTransCommandEx;

	float Dur[2];
	float Price;
	int	  Price2, PriceMax;
	int	  PriceDiv;


	if((lpTransItemInfo->Item.CODE&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1) || lpTransItemInfo->Item.CODE == (sinGF1 | sin01))
	{

		return FALSE;
	}


	if(CheckItemForm(&lpTransItemInfo->Item) == FALSE)
	{


		smTransCommandEx.WParam = 8830;
		smTransCommandEx.LParam = lpTransItemInfo->Item.CODE;
		smTransCommandEx.SParam = lpTransItemInfo->Item.Price;
		smTransCommandEx.EParam = 0;
		RecordHackLogFile(lpPlayInfo, &smTransCommandEx);

		return FALSE;
	}


	if(rsDeleteInvenItem(lpPlayInfo, lpTransItemInfo->Item.CODE,
		lpTransItemInfo->Item.ItemHeader.Head,
		lpTransItemInfo->Item.ItemHeader.dwChkSum) >= 0)
	{



		Dur[0] = lpTransItemInfo->Item.Durability[0];
		Dur[1] = lpTransItemInfo->Item.Durability[1];
		Price = (float)lpTransItemInfo->Item.Price;

		if(Dur[0] == 0)Dur[0] = 1;
		if(Dur[1] == 0)Dur[1] = 1;

		PriceDiv = 5;

		Price2 = (int)((Price*(Dur[0] / Dur[1])) + (Price - (Price*(Dur[0] / Dur[1])))*0.25);
		Price2 = Price2 / PriceDiv;
		PriceMax = lpTransItemInfo->Item.Price / PriceDiv;

		smTransCommand.code = OpCode::OPCODE_SHOP_SELLITEM;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = lpTransItemInfo->Item.CODE;
		smTransCommand.LParam = lpTransItemInfo->Item.ItemHeader.Head;
		smTransCommand.SParam = lpTransItemInfo->Item.ItemHeader.dwChkSum;


		if(PriceMax < Price2)
			smTransCommand.EParam = PriceMax;
		else
			smTransCommand.EParam = Price2;
		//Divisao pre�o venda item
		if ((lpTransItemInfo->Item.CODE & sinITEM_MASK2) == sinGB1) {
			smTransCommand.EParam = (int)Price;
		}





		if(lpPlayInfo->lpsmSock)
		{
			lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
		}

		lpPlayInfo->UnsaveMoney = lpTransItemInfo->y - smTransCommand.EParam;
		lpPlayInfo->AddServerMoney(smTransCommand.EParam, WHERE_SELL_ITEM);

		SaveThrowItem(lpPlayInfo, lpTransItemInfo->Item.CODE,
			lpTransItemInfo->Item.ItemHeader.Head,
			lpTransItemInfo->Item.ItemHeader.dwChkSum);


		rsRecord_ItemLOG(lpPlayInfo,
			lpTransItemInfo->Item.CODE,
			lpTransItemInfo->Item.ItemHeader.Head,
			lpTransItemInfo->Item.ItemHeader.dwChkSum,
			ITEMLOG_SELLSHOP);


	}
	else
	{


		smTransCommandEx.WParam = 8000;
		smTransCommandEx.WxParam = 10;
		smTransCommandEx.LxParam = (int)lpTransItemInfo->Item.ItemName;
		smTransCommandEx.LParam = lpTransItemInfo->Item.CODE;
		smTransCommandEx.SParam = lpTransItemInfo->Item.ItemHeader.Head;
		smTransCommandEx.EParam = lpTransItemInfo->Item.ItemHeader.dwChkSum;
		RecordHackLogFile(lpPlayInfo, &smTransCommandEx);

	}

	return TRUE;
}



int	rsCompareItems(sITEMINFO	*lpItem1, sITEMINFO	*lpItem2)
{
	if(lpItem1->CODE && lpItem1->CODE == lpItem2->CODE)
	{
		if(lpItem1->ItemHeader.dwTime == lpItem2->ItemHeader.dwTime &&
			lpItem1->ItemHeader.dwChkSum == lpItem2->ItemHeader.dwChkSum &&
			lpItem1->ItemHeader.Head == lpItem2->ItemHeader.Head)
		{

			return TRUE;
		}

		if(lpItem1->ItemHeader.dwChkSum == lpItem2->BackUpChkSum &&
			lpItem1->ItemHeader.Head == lpItem2->BackUpKey)
		{

			return TRUE;
		}

		if(lpItem2->ItemHeader.dwChkSum == lpItem1->BackUpChkSum &&
			lpItem2->ItemHeader.Head == lpItem1->BackUpKey)
		{

			return TRUE;
		}

		if(lpItem1->BackUpChkSum && lpItem1->BackUpKey &&
			lpItem2->BackUpChkSum == lpItem1->BackUpChkSum &&
			lpItem2->BackUpKey == lpItem1->BackUpKey)
		{

			return TRUE;
		}
	}

	return FALSE;
}


int rsCheckStgAreaItem(STG_AREA *lpStgArea, sITEMINFO	*lpItem)
{
	int cnt;

	if(lpItem->CODE < sinPM1 && (lpItem->CODE&sinITEM_MASK3) >= sin08)
	{

		for(cnt = 0; cnt < STG_ITEM_MAX; cnt++)
		{
			if(lpStgArea->StgItems[cnt].state)
			{
				if(rsCompareItems(lpItem, &lpStgArea->StgItems[cnt].Item.ItemInfo) == TRUE)
				{
					lpStgArea->StgItems[cnt].state = 0;
					return FALSE;
				}
			}
		}

	}

	return TRUE;
}


int rsSendDataServer(smWINSOCK *lpsmSock, void *szData)
{
	TRANS_SEND_DATASERVER	TransSendDataServer;
	int size;


	if(!lpsmSock) return FALSE;

	size = ((smTRANS_COMMAND *)szData)->size;

	if(size > 4096 || size < 0) return FALSE;

	memcpy(TransSendDataServer.szBuff, szData, size);
	TransSendDataServer.code = OpCode::OPCODE_SEND_DATASERVER;
	TransSendDataServer.size = size + 16;

	return lpsmSock->Send((char *)&TransSendDataServer, TransSendDataServer.size, TRUE);
}


int rsSendGameServer(smWINSOCK *lpsmSock, void *szData)
{
	TRANS_SEND_DATASERVER	TransSendDataServer;
	int size;


	if(!lpsmSock) return FALSE;

	size = ((smTRANS_COMMAND *)szData)->size;

	if(size > 4096 || size < 0) return FALSE;

	memcpy(TransSendDataServer.szBuff, szData, size);
	TransSendDataServer.code = OpCode::OPCODE_SEND_GAMESERVER;
	TransSendDataServer.size = size + 16;

	return lpsmSock->Send((char *)&TransSendDataServer, TransSendDataServer.size, TRUE);
}


int rsSendAreaServer(smWINSOCK *lpsmSock, void *szData)
{
	TRANS_SEND_DATASERVER	TransSendDataServer;
	int size;


	if(!lpsmSock) return FALSE;

	size = ((smTRANS_COMMAND *)szData)->size;

	if(size > 4096 || size < 0) return FALSE;

	memcpy(TransSendDataServer.szBuff, szData, size);
	TransSendDataServer.code = OpCode::OPCODE_SEND_AREASERVER;
	TransSendDataServer.size = size + 16;

	return lpsmSock->Send((char *)&TransSendDataServer, TransSendDataServer.size, TRUE);
}



int rsSendAGameServer(smWINSOCK *lpsmSock, void *szData)
{
	TRANS_SEND_DATASERVER	TransSendDataServer;
	int size;


	if(!lpsmSock) return FALSE;

	size = ((smTRANS_COMMAND *)szData)->size;

	if(size > 4096 || size < 0) return FALSE;

	memcpy(TransSendDataServer.szBuff, szData, size);
	TransSendDataServer.code = OpCode::OPCODE_SEND_AGAME_SERVER;
	TransSendDataServer.size = size + 16;

	return lpsmSock->Send((char *)&TransSendDataServer, TransSendDataServer.size, TRUE);
}



int rsSendAGameServer_PrimeItem2(smWINSOCK *lpsmSock, void *szData)
{
	TRANS_SEND_DATASERVER	TransSendDataServer;
	int size;


	if(!lpsmSock) return FALSE;

	size = ((smTRANS_COMMAND *)szData)->size;

	if(size > 4096 || size < 0) return FALSE;

	memcpy(TransSendDataServer.szBuff, szData, size);
	TransSendDataServer.code = OpCode::OPCODE_SEND_AGAME_PRIMEITEM_DATA2;
	TransSendDataServer.size = size + 16;

	return lpsmSock->Send((char *)&TransSendDataServer, TransSendDataServer.size, TRUE);
}



int rsSendAGameServer_PrimeItem3(smWINSOCK *lpsmSock, void *szData)
{
	TRANS_SEND_DATASERVER	TransSendDataServer;
	int size;


	if(!lpsmSock) return FALSE;

	size = ((smTRANS_COMMAND *)szData)->size;

	if(size > 4096 || size < 0) return FALSE;

	memcpy(TransSendDataServer.szBuff, szData, size);
	TransSendDataServer.code = OpCode::OPCODE_SEND_AGAME_PRIMEITEM_DATA3;
	TransSendDataServer.size = size + 16;

	return lpsmSock->Send((char *)&TransSendDataServer, TransSendDataServer.size, TRUE);
}




int rsSendAGameServer_PrimeItem4(smWINSOCK *lpsmSock, void *szData)
{
	TRANS_SEND_DATASERVER	TransSendDataServer;
	int size;


	if(!lpsmSock) return FALSE;

	size = ((smTRANS_COMMAND *)szData)->size;

	if(size > 4096 || size < 0) return FALSE;

	memcpy(TransSendDataServer.szBuff, szData, size);
	TransSendDataServer.code = OpCode::OPCODE_SEND_AGAME_PRIMEITEM_DATA4;
	TransSendDataServer.size = size + 16;

	return lpsmSock->Send((char *)&TransSendDataServer, TransSendDataServer.size, TRUE);
}

int	rsCheckTotalExpMoney(rsPLAYINFO *lpPlayInfo, TRANS_TOTAL_EXPMONEY *TransTotalExpMoney)
{
	smTRANS_COMMAND	smTransCommand;

	int ErrorFlag = 0;

	int Exp = TransTotalExpMoney->sServerExp.Total1 ^ TransTotalExpMoney->sServerExp.Total2;

	if(Exp > lpPlayInfo->spEXP_Out)
	{
		ErrorFlag++;
	}

	if(TransTotalExpMoney->sServerExp.InputExp > lpPlayInfo->spEXP_Out)
	{
		ErrorFlag++;
	}

	if(abs(lpPlayInfo->spEXP_Out - TransTotalExpMoney->sServerExp.InputExp) > (lpPlayInfo->smCharInfo.Level * TOTAL_CHECK_EXP_MAX))
	{
		ErrorFlag++;
	}

	if(ErrorFlag)
	{

		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = OpCode::OPCODE_SET_BLACKLIST;
		smTransCommand.WParam = 6500;
		smTransCommand.LParam = TransTotalExpMoney->sServerExp.InputExp;
		smTransCommand.SParam = lpPlayInfo->spEXP_Out;
		smTransCommand.EParam = rsServerConfig.ServerCode;
		rsSendDataServer(lpPlayInfo->lpsmSock, &smTransCommand);

		if(!lpPlayInfo->dwHopeDisconnectTime)
		{
			lpPlayInfo->dwHopeDisconnectTime = dwPlayServTime + 20 * 1000;
		}
	}


	lpPlayInfo->dwLastExpMoneyCheckTime = dwPlayServTime;

	return TRUE;
}

#ifdef	_W_SERVER


int rsSendGameServerExp(rsPLAYINFO *lpPlayInfo)
{
	smTRANS_COMMAND	smTransCommand;
	DWORD	dwCodeKey;

	dwCodeKey = dwPlayServTime & 0x3FFFFFFF;

	if(lpPlayInfo->spEXP_Out > 0 && (dwPlayServTime - lpPlayInfo->dwLastExpMoneyTransServer) > 60 * 1000)
	{


		smTransCommand.code = OpCode::OPCODE_CHECK_EXPDATA;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = rsServerConfig.ServerCode;
		smTransCommand.SParam = (lpPlayInfo->spEXP_Out + 11223344) ^ 0x55cc55cc ^ ((dwCodeKey << 17) | (dwCodeKey >> 8));
		smTransCommand.EParam = dwCodeKey;


		smTransCommand.LParam = (97531 * smTransCommand.SParam) ^ ((smTransCommand.EParam << 21) ^ (smTransCommand.EParam >> 5));



		rsSendDataServer(lpPlayInfo->lpsmSock, &smTransCommand);
		lpPlayInfo->dwLastExpMoneyTransServer = dwPlayServTime;
	}

	return TRUE;
}


int rsRecvGameServerExp(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	int cnt, code;
	int	sfcode;
	smTRANS_COMMAND	smTransCommand;

	cnt = lpTransCommand->WParam;
	if(cnt >= 0 && cnt < 8)
	{


		sfcode = (97531 * lpTransCommand->SParam) ^ ((lpTransCommand->EParam << 21) ^ (lpTransCommand->EParam >> 5));



		code = lpTransCommand->SParam ^ 0x55cc55cc ^ ((lpTransCommand->EParam << 17) | (lpTransCommand->EParam >> 8));
		code -= 11223344;



		if(lpTransCommand->LParam != sfcode)
		{

			smTransCommand.WParam = 7120;
			smTransCommand.LParam = lpTransCommand->SParam;
			smTransCommand.SParam = sfcode;
			smTransCommand.EParam = code;
			RecordHackLogFile(lpPlayInfo, &smTransCommand);
			return FALSE;
		}

		if((int)lpPlayInfo->dwGameServerExp[cnt] < code)
			lpPlayInfo->dwGameServerExp[cnt] = code;

		return TRUE;
	}

	return FALSE;
}



int rsSendGameServer_PrimeItem(rsPLAYINFO *lpPlayInfo)
{
	smTRANS_COMMAND_EX	smTransCommand;
	DWORD	dwCodeKey;
	DWORD	dwMaskKey;
	DWORD	dwServTime_T = (DWORD)tServerTime;

	if(lpPlayInfo->dwPrimeItem_NextSetTime < dwPlayServTime)
	{
		dwCodeKey = dwPlayServTime & 0x3FFFFFFF;
		lpPlayInfo->dwPrimeItem_NextSetTime = dwPlayServTime + 1000 * 60;

		dwMaskKey = lpPlayInfo->dwObjectSerial*(lpPlayInfo->dwCode_Name << 3);
		dwMaskKey ^= dwCodeKey;



		smTransCommand.code = OpCode::OPCODE_PRIMEITEM_DATA;
		smTransCommand.size = sizeof(smTRANS_COMMAND_EX);
		smTransCommand.WParam = (lpPlayInfo->dwTime_PrimeItem_X2) ^ dwMaskKey;
		smTransCommand.LParam = (lpPlayInfo->dwTime_PrimeItem_ExpUp) ^ dwMaskKey;
		smTransCommand.SParam = (lpPlayInfo->dwTime_PrimeItem_X2 + lpPlayInfo->dwTime_PrimeItem_ExpUp + smTransCommand.code) ^ dwMaskKey;
		smTransCommand.EParam = dwCodeKey;
		smTransCommand.WxParam = (lpPlayInfo->dwTime_PrimeItem_VampCuspid) ^ dwMaskKey;
		smTransCommand.LxParam = (lpPlayInfo->dwTime_PrimeItem_ManaRecharg) ^ dwMaskKey;
		smTransCommand.SxParam = (lpPlayInfo->dwTime_PrimeItem_VampCuspid + lpPlayInfo->dwTime_PrimeItem_ManaRecharg + smTransCommand.code) ^ dwMaskKey;
		smTransCommand.ExParam = (lpPlayInfo->dwPrimeItem_PackageCode ^ ((smTransCommand.WParam + smTransCommand.LParam)) ^ dwMaskKey);

		rsSendAGameServer(lpPlayInfo->lpsmSock, &smTransCommand);



		rsSendGameServer_PrimeItem2(lpPlayInfo);

		rsSendGameServer_PrimeItem3(lpPlayInfo);

	}

	return TRUE;
}




int rsSendGameServer_PrimeItem2(rsPLAYINFO *lpPlayInfo)
{
	smTRANS_COMMAND_EX	smTransCommand;
	DWORD	dwCodeKey;
	DWORD	dwMaskKey;
	DWORD	dwServTime_T = (DWORD)tServerTime;













	dwCodeKey = dwPlayServTime & 0x3FFFFFFF;


	dwMaskKey = lpPlayInfo->dwObjectSerial*(lpPlayInfo->dwCode_Name << 3);
	dwMaskKey ^= dwCodeKey;



	smTransCommand.code = OpCode::OPCODE_PRIMEITEM_DATA2;
	smTransCommand.size = sizeof(smTRANS_COMMAND_EX);
	smTransCommand.WParam = (lpPlayInfo->dwTime_PrimeItem_ManaReduce) ^ dwMaskKey;
	smTransCommand.LParam = (lpPlayInfo->dwTime_PrimeItem_MightofAwell) ^ dwMaskKey;
	smTransCommand.SParam = (lpPlayInfo->dwTime_PrimeItem_ManaReduce + lpPlayInfo->dwTime_PrimeItem_MightofAwell + smTransCommand.code) ^ dwMaskKey;
	smTransCommand.EParam = dwCodeKey;
	smTransCommand.WxParam = (lpPlayInfo->dwTime_PrimeItem_MightofAwell2) ^ dwMaskKey;
	smTransCommand.LxParam = (lpPlayInfo->dwTime_PrimeItem_PhenixPet) ^ dwMaskKey;
	smTransCommand.SxParam = (lpPlayInfo->dwTime_PrimeItem_MightofAwell2 + lpPlayInfo->dwTime_PrimeItem_PhenixPet + smTransCommand.code) ^ dwMaskKey;


	rsSendAGameServer_PrimeItem2(lpPlayInfo->lpsmSock, &smTransCommand);


	return TRUE;
}





int rsSendGameServer_PrimeItem3(rsPLAYINFO *lpPlayInfo)
{
	smTRANS_COMMAND_EX	smTransCommand;
	DWORD	dwCodeKey;
	DWORD	dwMaskKey;

	dwCodeKey = dwPlayServTime & 0x3FFFFFFF;
	dwMaskKey = lpPlayInfo->dwObjectSerial*(lpPlayInfo->dwCode_Name << 3);
	dwMaskKey ^= dwCodeKey;


	smTransCommand.code = OpCode::OPCODE_PRIMEITEM_DATA3;
	smTransCommand.size = sizeof(smTRANS_COMMAND_EX);
	smTransCommand.WParam = (lpPlayInfo->dwTime_PrimeItem_HelpPet) ^ dwMaskKey;
	smTransCommand.LParam = (lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX) ^ dwMaskKey;
	smTransCommand.SParam = (lpPlayInfo->dwTime_PrimeItem_HelpPet + lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX + smTransCommand.code) ^ dwMaskKey;
	smTransCommand.EParam = dwCodeKey;
	smTransCommand.WxParam = (lpPlayInfo->dwTime_PrimeItem_StaminaReduce) ^ dwMaskKey;
	smTransCommand.LxParam = (0) ^ dwMaskKey;
	smTransCommand.SxParam = (lpPlayInfo->dwTime_PrimeItem_StaminaReduce + 0 + smTransCommand.code) ^ dwMaskKey;
	smTransCommand.ExParam = (0) ^ dwMaskKey;

	rsSendAGameServer_PrimeItem3(lpPlayInfo->lpsmSock, &smTransCommand);

	return TRUE;
}


int rsSendGameServer_PrimeItem4(rsPLAYINFO *lpPlayInfo)
{
	smTRANS_COMMAND_EX	smTransCommand;
	DWORD	dwCodeKey;
	DWORD	dwMaskKey;
	DWORD	dwServTime_T = (DWORD)tServerTime;

	if(lpPlayInfo->dwPrimeItem_NextSetTime < dwPlayServTime)
	{
		dwCodeKey = dwPlayServTime & 0x3FFFFFFF;
		lpPlayInfo->dwPrimeItem_NextSetTime = dwPlayServTime + 1000 * 60;

		dwMaskKey = lpPlayInfo->dwObjectSerial*(lpPlayInfo->dwCode_Name << 3);
		dwMaskKey ^= dwCodeKey;





		smTransCommand.code = OpCode::OPCODE_PRIMEITEM_DATA4;
		smTransCommand.size = sizeof(smTRANS_COMMAND_EX);
		smTransCommand.WParam = (lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX) ^ dwMaskKey;
		smTransCommand.LParam = (0) ^ dwMaskKey;
		smTransCommand.SParam = (lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX + 0 + smTransCommand.code) ^ dwMaskKey;
		smTransCommand.EParam = dwCodeKey;
		smTransCommand.WxParam = (0) ^ dwMaskKey;
		smTransCommand.LxParam = (0) ^ dwMaskKey;
		smTransCommand.SxParam = (0) ^ dwMaskKey;
		smTransCommand.ExParam = (0) ^ dwMaskKey;

		rsSendAGameServer_PrimeItem4(lpPlayInfo->lpsmSock, &smTransCommand);
	}

	return TRUE;
}


int rsRecvGameServer_PrimeItem(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND_EX *lpTransCommand)
{

	DWORD	dwCodeKey;
	DWORD	dwMaskKey;

	smTRANS_COMMAND_EX	smTransCommand;

	memcpy(&smTransCommand, lpTransCommand, sizeof(smTRANS_COMMAND_EX));

	dwCodeKey = lpTransCommand->EParam;
	dwMaskKey = lpPlayInfo->dwObjectSerial*(lpPlayInfo->dwCode_Name << 3);
	dwMaskKey ^= dwCodeKey;

	smTransCommand.WParam ^= dwMaskKey;
	smTransCommand.LParam ^= dwMaskKey;
	smTransCommand.SParam ^= dwMaskKey;
	smTransCommand.WxParam ^= dwMaskKey;
	smTransCommand.LxParam ^= dwMaskKey;
	smTransCommand.SxParam ^= dwMaskKey;
	smTransCommand.ExParam ^= (lpTransCommand->WParam + lpTransCommand->LParam) ^ dwMaskKey;

	if(smTransCommand.SParam == ((smTransCommand.WParam + smTransCommand.LParam + smTransCommand.code)))
	{
		lpPlayInfo->dwTime_PrimeItem_X2 = smTransCommand.WParam;
		lpPlayInfo->dwTime_PrimeItem_ExpUp = smTransCommand.LParam;
	}
	if(smTransCommand.SxParam == ((smTransCommand.WxParam + smTransCommand.LxParam + smTransCommand.code)))
	{
		lpPlayInfo->dwTime_PrimeItem_VampCuspid = smTransCommand.WxParam;
		lpPlayInfo->dwTime_PrimeItem_ManaRecharg = smTransCommand.LxParam;
	}

	if(smTransCommand.WParam || smTransCommand.LParam)
	{
		lpPlayInfo->dwPrimeItem_PackageCode = smTransCommand.ExParam;
	}

	return TRUE;
}




int rsRecvGameServer_PrimeItem2(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND_EX *lpTransCommand)
{

	DWORD	dwCodeKey;
	DWORD	dwMaskKey;

	smTRANS_COMMAND_EX	smTransCommand;

	memcpy(&smTransCommand, lpTransCommand, sizeof(smTRANS_COMMAND_EX));

	dwCodeKey = lpTransCommand->EParam;
	dwMaskKey = lpPlayInfo->dwObjectSerial*(lpPlayInfo->dwCode_Name << 3);
	dwMaskKey ^= dwCodeKey;

	smTransCommand.WParam ^= dwMaskKey;
	smTransCommand.LParam ^= dwMaskKey;
	smTransCommand.SParam ^= dwMaskKey;
	smTransCommand.WxParam ^= dwMaskKey;
	smTransCommand.LxParam ^= dwMaskKey;
	smTransCommand.SxParam ^= dwMaskKey;
	smTransCommand.ExParam ^= (lpTransCommand->WParam + lpTransCommand->LParam) ^ dwMaskKey;

	if(smTransCommand.SParam == (smTransCommand.WParam + smTransCommand.LParam + smTransCommand.code))
	{
		lpPlayInfo->dwTime_PrimeItem_ManaReduce = smTransCommand.WParam;
		lpPlayInfo->dwTime_PrimeItem_MightofAwell = smTransCommand.LParam;
	}
	if(smTransCommand.SxParam == ((smTransCommand.WxParam + smTransCommand.LxParam + smTransCommand.code)))
	{
		lpPlayInfo->dwTime_PrimeItem_MightofAwell2 = smTransCommand.WxParam;
		lpPlayInfo->dwTime_PrimeItem_PhenixPet = smTransCommand.LxParam;
	}





	return TRUE;
}




int rsRecvGameServer_PrimeItem3(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND_EX *lpTransCommand)
{

	DWORD	dwCodeKey;
	DWORD	dwMaskKey;

	smTRANS_COMMAND_EX	smTransCommand;

	memcpy(&smTransCommand, lpTransCommand, sizeof(smTRANS_COMMAND_EX));

	dwCodeKey = lpTransCommand->EParam;
	dwMaskKey = lpPlayInfo->dwObjectSerial*(lpPlayInfo->dwCode_Name << 3);
	dwMaskKey ^= dwCodeKey;

	smTransCommand.WParam ^= dwMaskKey;
	smTransCommand.LParam ^= dwMaskKey;
	smTransCommand.SParam ^= dwMaskKey;
	smTransCommand.WxParam ^= dwMaskKey;
	smTransCommand.LxParam ^= dwMaskKey;
	smTransCommand.SxParam ^= dwMaskKey;
	smTransCommand.ExParam ^= (lpTransCommand->WParam + lpTransCommand->LParam) ^ dwMaskKey;

	if(smTransCommand.SParam == (smTransCommand.WParam + smTransCommand.LParam + smTransCommand.code))
	{
		lpPlayInfo->dwTime_PrimeItem_HelpPet = smTransCommand.WParam;
		lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX = smTransCommand.LParam;
	}
	if(smTransCommand.SxParam == ((smTransCommand.WxParam + smTransCommand.LxParam + smTransCommand.code)))
	{
		lpPlayInfo->dwTime_PrimeItem_StaminaReduce = smTransCommand.WxParam;
	}

	return TRUE;
}



int rsRecvGameServer_PrimeItem4(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND_EX *lpTransCommand)
{

	DWORD	dwCodeKey;
	DWORD	dwMaskKey;

	smTRANS_COMMAND_EX	smTransCommand;

	memcpy(&smTransCommand, lpTransCommand, sizeof(smTRANS_COMMAND_EX));

	dwCodeKey = lpTransCommand->EParam;
	dwMaskKey = lpPlayInfo->dwObjectSerial*(lpPlayInfo->dwCode_Name << 3);
	dwMaskKey ^= dwCodeKey;

	smTransCommand.WParam ^= dwMaskKey;
	smTransCommand.LParam ^= dwMaskKey;
	smTransCommand.SParam ^= dwMaskKey;
	smTransCommand.WxParam ^= dwMaskKey;
	smTransCommand.LxParam ^= dwMaskKey;
	smTransCommand.SxParam ^= dwMaskKey;
	smTransCommand.ExParam ^= (lpTransCommand->WParam + lpTransCommand->LParam) ^ dwMaskKey;

	if(smTransCommand.SParam == (smTransCommand.WParam + smTransCommand.LParam + smTransCommand.code))
	{
		lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX = smTransCommand.WParam;
	}

	return TRUE;
}



int rsSendAreaServer_PCBangPet(rsPLAYINFO *lpPlayInfo)
{
	smTRANS_COMMAND	smTransCommand;
	DWORD	dwCodeKey;
	DWORD	dwMaskKey;

	if(lpPlayInfo->dwObjectSerial && lpPlayInfo->dwPCBang_Pet_NextSetTime < dwPlayServTime && lpPlayInfo->Bl_RNo>0)
	{



		if(!lpPlayInfo->dwPCBang_Pet_NextSetTime)
		{

			ZeroMemory(&smTransCommand, sizeof(smTRANS_COMMAND));
			smTransCommand.code = OpCode::OPCODE_PCBANG_PET;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
		}


		dwCodeKey = dwPlayServTime & 0x3FFFFFFF;
		lpPlayInfo->dwPCBang_Pet_NextSetTime = dwPlayServTime + 1000 * 17;

		dwMaskKey = lpPlayInfo->dwObjectSerial*(lpPlayInfo->dwCode_Name << 3);
		dwMaskKey ^= dwCodeKey;



		smTransCommand.code = OpCode::OPCODE_PCBANG_PET;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = (lpPlayInfo->Bl_RNo) ^ dwMaskKey;
		smTransCommand.LParam = (lpPlayInfo->dwPCBang_Pet_NextSetTime) ^ dwMaskKey;
		smTransCommand.SParam = (lpPlayInfo->Bl_RNo + lpPlayInfo->dwPCBang_Pet_NextSetTime + smTransCommand.code) ^ dwMaskKey;
		smTransCommand.EParam = dwCodeKey;

		rsSendAGameServer(lpPlayInfo->lpsmSock, &smTransCommand);
	}

	return TRUE;
}




int rsSendAreaServer_PhenixPet(rsPLAYINFO *lpPlayInfo)
{
	smTRANS_COMMAND	smTransCommand;
	DWORD	dwCodeKey;
	DWORD	dwMaskKey;

	if(lpPlayInfo->dwObjectSerial && lpPlayInfo->dwPCBang_Pet_NextSetTime < dwPlayServTime && lpPlayInfo->dwTime_PrimeItem_PhenixPet > 0)
	{

		if(!lpPlayInfo->dwPCBang_Pet_NextSetTime)
		{

			ZeroMemory(&smTransCommand, sizeof(smTRANS_COMMAND));
			smTransCommand.code = OpCode::OPCODE_PHENIX_PET;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
		}


		dwCodeKey = dwPlayServTime & 0x3FFFFFFF;
		lpPlayInfo->dwPCBang_Pet_NextSetTime = dwPlayServTime + 1000 * 17;

		dwMaskKey = lpPlayInfo->dwObjectSerial*(lpPlayInfo->dwCode_Name << 3);
		dwMaskKey ^= dwCodeKey;



		smTransCommand.code = OpCode::OPCODE_PHENIX_PET;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = (lpPlayInfo->dwTime_PrimeItem_PhenixPet) ^ dwMaskKey;
		smTransCommand.LParam = (lpPlayInfo->dwPCBang_Pet_NextSetTime) ^ dwMaskKey;
		smTransCommand.SParam = (lpPlayInfo->dwTime_PrimeItem_PhenixPet + lpPlayInfo->dwPCBang_Pet_NextSetTime + smTransCommand.code) ^ dwMaskKey;
		smTransCommand.EParam = dwCodeKey;

		rsSendAGameServer(lpPlayInfo->lpsmSock, &smTransCommand);
	}

	return TRUE;
}


int rsRecvAreaServer_PhenixPet(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{

	DWORD	dwCodeKey;
	DWORD	dwMaskKey;

	smTRANS_COMMAND	smTransCommand;

	memcpy(&smTransCommand, lpTransCommand, sizeof(smTRANS_COMMAND));

	dwCodeKey = lpTransCommand->EParam;
	dwMaskKey = lpPlayInfo->dwObjectSerial*(lpPlayInfo->dwCode_Name << 3);
	dwMaskKey ^= dwCodeKey;

	smTransCommand.WParam ^= dwMaskKey;
	smTransCommand.LParam ^= dwMaskKey;
	smTransCommand.SParam ^= dwMaskKey;

	if(smTransCommand.SParam == ((smTransCommand.WParam + smTransCommand.LParam + smTransCommand.code)))
	{
		lpPlayInfo->dwTime_PrimeItem_PhenixPet = smTransCommand.WParam;
		return TRUE;
	}

	return FALSE;
}


int rsRecvAreaServer_PCBangPet(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{

	DWORD	dwCodeKey;
	DWORD	dwMaskKey;

	smTRANS_COMMAND	smTransCommand;

	memcpy(&smTransCommand, lpTransCommand, sizeof(smTRANS_COMMAND));

	dwCodeKey = lpTransCommand->EParam;
	dwMaskKey = lpPlayInfo->dwObjectSerial*(lpPlayInfo->dwCode_Name << 3);
	dwMaskKey ^= dwCodeKey;

	smTransCommand.WParam ^= dwMaskKey;
	smTransCommand.LParam ^= dwMaskKey;
	smTransCommand.SParam ^= dwMaskKey;

	if(smTransCommand.SParam == ((smTransCommand.WParam + smTransCommand.LParam + smTransCommand.code)))
	{
		lpPlayInfo->Bl_RNo = smTransCommand.WParam;
		return TRUE;
	}

	return FALSE;
}


int rsSendAreaServer_HelpPet(rsPLAYINFO *lpPlayInfo)
{
	smTRANS_COMMAND	smTransCommand;
	DWORD	dwCodeKey;
	DWORD	dwMaskKey;

	if(lpPlayInfo->dwObjectSerial && lpPlayInfo->dwHelp_Pet_NextSetTime < dwPlayServTime && lpPlayInfo->dwTime_PrimeItem_HelpPet > 0)
	{

		if(!lpPlayInfo->dwHelp_Pet_NextSetTime)
		{

			ZeroMemory(&smTransCommand, sizeof(smTRANS_COMMAND));
			smTransCommand.code = OpCode::OPCODE_HELP_PET;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
		}


		dwCodeKey = dwPlayServTime & 0x3FFFFFFF;
		lpPlayInfo->dwHelp_Pet_NextSetTime = dwPlayServTime + 1000 * 17;

		dwMaskKey = lpPlayInfo->dwObjectSerial*(lpPlayInfo->dwCode_Name << 3);
		dwMaskKey ^= dwCodeKey;



		smTransCommand.code = OpCode::OPCODE_HELP_PET;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = (lpPlayInfo->dwTime_PrimeItem_HelpPet) ^ dwMaskKey;
		smTransCommand.LParam = (lpPlayInfo->dwHelp_Pet_NextSetTime) ^ dwMaskKey;
		smTransCommand.SParam = (lpPlayInfo->dwTime_PrimeItem_HelpPet + lpPlayInfo->dwHelp_Pet_NextSetTime + smTransCommand.code) ^ dwMaskKey;
		smTransCommand.EParam = dwCodeKey;

		rsSendAGameServer_PrimeItem3(lpPlayInfo->lpsmSock, &smTransCommand);
	}

	return TRUE;
}


int rsRecvAreaServer_HelpPet(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{

	DWORD	dwCodeKey;
	DWORD	dwMaskKey;

	smTRANS_COMMAND	smTransCommand;

	memcpy(&smTransCommand, lpTransCommand, sizeof(smTRANS_COMMAND));

	dwCodeKey = lpTransCommand->EParam;
	dwMaskKey = lpPlayInfo->dwObjectSerial*(lpPlayInfo->dwCode_Name << 3);
	dwMaskKey ^= dwCodeKey;

	smTransCommand.WParam ^= dwMaskKey;
	smTransCommand.LParam ^= dwMaskKey;
	smTransCommand.SParam ^= dwMaskKey;

	if(smTransCommand.SParam == ((smTransCommand.WParam + smTransCommand.LParam + smTransCommand.code)))
	{
		lpPlayInfo->dwTime_PrimeItem_HelpPet = smTransCommand.WParam;
		return TRUE;
	}

	return FALSE;
}



int rsSendAreaServerForceOrb(rsPLAYINFO *lpPlayInfo)
{
	smTRANS_COMMAND	smTransCommand;
	DWORD	dwCodeKey;
	DWORD	dwMaskKey;

	if(lpPlayInfo->dwForceOrb_SaveTime && lpPlayInfo->dwForceOrb_SaveTime > dwPlayServTime)
	{

		if(lpPlayInfo->dwForceOrb_NextSetTime && lpPlayInfo->dwForceOrb_NextSetTime > dwPlayServTime)
			return FALSE;

		dwCodeKey = dwPlayServTime & 0x3FFFFFFF;
		lpPlayInfo->dwForceOrb_NextSetTime = dwPlayServTime + 1000 * 30;

		dwMaskKey = lpPlayInfo->dwObjectSerial*(lpPlayInfo->dwCode_Name << 3);
		dwMaskKey ^= dwCodeKey;



		smTransCommand.code = OpCode::OPCODE_FORCEORB_DATA;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = (lpPlayInfo->dwForceOrb_SaveCode) ^ dwMaskKey;
		smTransCommand.LParam = (lpPlayInfo->dwForceOrb_SaveTime - dwPlayServTime) ^ dwMaskKey;
		smTransCommand.SParam = lpPlayInfo->dwForceOrb_SaveDamage^dwMaskKey;
		smTransCommand.EParam = dwCodeKey;

		rsSendAreaServer(lpPlayInfo->lpsmSock, &smTransCommand);
	}
	else
	{
		lpPlayInfo->dwForceOrb_NextSetTime = 0;
		lpPlayInfo->dwForceOrb_SaveCode = 0;
		lpPlayInfo->dwForceOrb_SaveTime = 0;
		lpPlayInfo->dwForceOrb_SaveDamage = 0;
	}


	rsSendGameServer_PrimeItem(lpPlayInfo);

	if(rsServerConfig.Event_PCBangPet)
	{

		rsSendAreaServer_PCBangPet(lpPlayInfo);
	}

	if(lpPlayInfo->dwTime_PrimeItem_PhenixPet > 0)
	{
		rsSendAreaServer_PhenixPet(lpPlayInfo);
	}


	if(lpPlayInfo->dwTime_PrimeItem_HelpPet > 0)
	{
		rsSendAreaServer_HelpPet(lpPlayInfo);
	}

	return TRUE;
}


int rsRecvAreaServerForceOrb(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{

	DWORD	dwCodeKey;
	DWORD	dwMaskKey;
	int		cnt;
	smTRANS_COMMAND	smTransCommand;

	memcpy(&smTransCommand, lpTransCommand, sizeof(smTRANS_COMMAND));

	dwCodeKey = lpTransCommand->EParam;
	dwMaskKey = lpPlayInfo->dwObjectSerial*(lpPlayInfo->dwCode_Name << 3);
	dwMaskKey ^= dwCodeKey;

	smTransCommand.WParam ^= dwMaskKey;
	smTransCommand.LParam ^= dwMaskKey;
	smTransCommand.SParam ^= dwMaskKey;

	if((smTransCommand.WParam&sinITEM_MASK2) != sinFO1) return FALSE;

	cnt = (smTransCommand.WParam&sinITEM_MASK3) >> 8;
	if((smTransCommand.WParam&sinITEM_MASK3) >= sin26)
	{
		cnt -= 16;
	}
	cnt--;

	if(cnt >= 0 && cnt < 14 && smTransCommand.SParam <= ForceOrbDamage[cnt] && smTransCommand.LParam <= (ForceOrbUseTime[cnt] * 1000))
	{

		lpPlayInfo->dwForceOrb_Code = smTransCommand.WParam;
		lpPlayInfo->dwForceOrb_Time = dwPlayServTime + smTransCommand.LParam;
		lpPlayInfo->dwForceOrb_Damage = smTransCommand.SParam;
		return TRUE;
	}

	else if(cnt >= 20 && cnt < 32 && smTransCommand.SParam <= MagicForceOrbDamage[cnt - 20] && smTransCommand.LParam <= (MagicForceOrbUseTime[cnt - 20] * 1000))
	{

		lpPlayInfo->dwForceOrb_Code = smTransCommand.WParam;
		lpPlayInfo->dwForceOrb_Time = dwPlayServTime + smTransCommand.LParam;
		lpPlayInfo->dwForceOrb_Damage = smTransCommand.SParam;
		return TRUE;
	}

	else if(cnt >= 34 && cnt < 37 && smTransCommand.SParam <= BillingMagicForceOrbDamage[cnt - 34] && smTransCommand.LParam <= (BillingMagicForceOrbUseTime[cnt - 34] * 1000))
	{

		lpPlayInfo->dwForceOrb_Code = smTransCommand.WParam;
		lpPlayInfo->dwForceOrb_Time = dwPlayServTime + smTransCommand.LParam;
		lpPlayInfo->dwForceOrb_Damage = smTransCommand.SParam;
		return TRUE;
	}

	return FALSE;
}


int rsSendAreaServerBoosterItem(rsPLAYINFO *lpPlayInfo)
{
	smTRANS_COMMAND	smTransCommand;
	DWORD	dwCodeKey;
	DWORD	dwMaskKey;


	if(lpPlayInfo->dwLifeBooster_SaveTime && lpPlayInfo->dwLifeBooster_SaveTime > dwPlayServTime)
	{

		if(lpPlayInfo->dwLifeBooster_NextSetTime && lpPlayInfo->dwLifeBooster_NextSetTime > dwPlayServTime)
			return FALSE;

		dwCodeKey = dwPlayServTime & 0x3FFFFFFF;
		lpPlayInfo->dwLifeBooster_NextSetTime = dwPlayServTime + 1000 * 30;

		dwMaskKey = lpPlayInfo->dwObjectSerial*(lpPlayInfo->dwCode_Name << 3);
		dwMaskKey ^= dwCodeKey;



		smTransCommand.code = OpCode::OPCODE_BOOSTER_DATA;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = (lpPlayInfo->dwLifeBooster_SaveCode) ^ dwMaskKey;
		smTransCommand.LParam = (lpPlayInfo->dwLifeBooster_SaveTime - dwPlayServTime) ^ dwMaskKey;
		smTransCommand.SParam = lpPlayInfo->dwLifeBooster_SaveData^dwMaskKey;
		smTransCommand.EParam = dwCodeKey;

		rsSendAreaServer(lpPlayInfo->lpsmSock, &smTransCommand);
	}
	else
	{
		lpPlayInfo->dwLifeBooster_NextSetTime = 0;
		lpPlayInfo->dwLifeBooster_SaveCode = 0;
		lpPlayInfo->dwLifeBooster_SaveTime = 0;
		lpPlayInfo->dwLifeBooster_SaveData = 0;
	}


	if(lpPlayInfo->dwManaBooster_SaveTime && lpPlayInfo->dwManaBooster_SaveTime > dwPlayServTime)
	{

		if(lpPlayInfo->dwManaBooster_NextSetTime && lpPlayInfo->dwManaBooster_NextSetTime > dwPlayServTime)
			return FALSE;

		dwCodeKey = dwPlayServTime & 0x3FFFFFFF;
		lpPlayInfo->dwManaBooster_NextSetTime = dwPlayServTime + 1000 * 30;

		dwMaskKey = lpPlayInfo->dwObjectSerial*(lpPlayInfo->dwCode_Name << 3);
		dwMaskKey ^= dwCodeKey;



		smTransCommand.code = OpCode::OPCODE_BOOSTER_DATA;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = (lpPlayInfo->dwManaBooster_SaveCode) ^ dwMaskKey;
		smTransCommand.LParam = (lpPlayInfo->dwManaBooster_SaveTime - dwPlayServTime) ^ dwMaskKey;
		smTransCommand.SParam = lpPlayInfo->dwManaBooster_SaveData^dwMaskKey;
		smTransCommand.EParam = dwCodeKey;

		rsSendAreaServer(lpPlayInfo->lpsmSock, &smTransCommand);
	}
	else
	{
		lpPlayInfo->dwManaBooster_NextSetTime = 0;
		lpPlayInfo->dwManaBooster_SaveCode = 0;
		lpPlayInfo->dwManaBooster_SaveTime = 0;
		lpPlayInfo->dwManaBooster_SaveData = 0;
	}


	if(lpPlayInfo->dwStaminaBooster_SaveTime && lpPlayInfo->dwStaminaBooster_SaveTime > dwPlayServTime)
	{

		if(lpPlayInfo->dwStaminaBooster_NextSetTime && lpPlayInfo->dwStaminaBooster_NextSetTime > dwPlayServTime)
			return FALSE;

		dwCodeKey = dwPlayServTime & 0x3FFFFFFF;
		lpPlayInfo->dwStaminaBooster_NextSetTime = dwPlayServTime + 1000 * 30;

		dwMaskKey = lpPlayInfo->dwObjectSerial*(lpPlayInfo->dwCode_Name << 3);
		dwMaskKey ^= dwCodeKey;



		smTransCommand.code = OpCode::OPCODE_BOOSTER_DATA;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = (lpPlayInfo->dwStaminaBooster_SaveCode) ^ dwMaskKey;
		smTransCommand.LParam = (lpPlayInfo->dwStaminaBooster_SaveTime - dwPlayServTime) ^ dwMaskKey;
		smTransCommand.SParam = lpPlayInfo->dwStaminaBooster_SaveData^dwMaskKey;
		smTransCommand.EParam = dwCodeKey;

		rsSendAreaServer(lpPlayInfo->lpsmSock, &smTransCommand);
	}
	else
	{
		lpPlayInfo->dwStaminaBooster_NextSetTime = 0;
		lpPlayInfo->dwStaminaBooster_SaveCode = 0;
		lpPlayInfo->dwStaminaBooster_SaveTime = 0;
		lpPlayInfo->dwStaminaBooster_SaveData = 0;
	}

	return TRUE;
}



int rsRecvAreaServerBoosterItem(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{

	DWORD	dwCodeKey;
	DWORD	dwMaskKey;
	DWORD	dwItemMask;
	int		cnt = 0;
	smTRANS_COMMAND	smTransCommand;

	memcpy(&smTransCommand, lpTransCommand, sizeof(smTRANS_COMMAND));

	dwCodeKey = lpTransCommand->EParam;
	dwMaskKey = lpPlayInfo->dwObjectSerial*(lpPlayInfo->dwCode_Name << 3);
	dwMaskKey ^= dwCodeKey;

	smTransCommand.WParam ^= dwMaskKey;
	smTransCommand.LParam ^= dwMaskKey;
	smTransCommand.SParam ^= dwMaskKey;

	if((smTransCommand.WParam&sinITEM_MASK2) != sinBC1) return FALSE;

	dwItemMask = smTransCommand.WParam&sinITEM_MASK3;
	if(dwItemMask == sin21 || dwItemMask == sin24 || dwItemMask == sin27) cnt = 0;
	if(dwItemMask == sin22 || dwItemMask == sin25 || dwItemMask == sin28) cnt = 1;
	if(dwItemMask == sin23 || dwItemMask == sin26 || dwItemMask == sin29) cnt = 2;


	if(dwItemMask == sin21 || dwItemMask == sin22 || dwItemMask == sin23)
	{
		if(smTransCommand.LParam <= (BoosterItem_UseTime[cnt] * 1000))
		{
			lpPlayInfo->dwLifeBooster_Code = smTransCommand.WParam;
			lpPlayInfo->dwLifeBooster_Time = dwPlayServTime + smTransCommand.LParam;
			lpPlayInfo->dwLifeBooster_Data = smTransCommand.SParam;
			return TRUE;
		}
	}

	if(dwItemMask == sin24 || dwItemMask == sin25 || dwItemMask == sin26)
	{
		if(smTransCommand.LParam <= (BoosterItem_UseTime[cnt] * 1000))
		{
			lpPlayInfo->dwManaBooster_Code = smTransCommand.WParam;
			lpPlayInfo->dwManaBooster_Time = dwPlayServTime + smTransCommand.LParam;
			lpPlayInfo->dwManaBooster_Data = smTransCommand.SParam;
			return TRUE;
		}
	}

	if(dwItemMask == sin27 || dwItemMask == sin28 || dwItemMask == sin29)
	{
		if(smTransCommand.LParam <= (BoosterItem_UseTime[cnt] * 1000))
		{
			lpPlayInfo->dwStaminaBooster_Code = smTransCommand.WParam;
			lpPlayInfo->dwStaminaBooster_Time = dwPlayServTime + smTransCommand.LParam;
			lpPlayInfo->dwStaminaBooster_Data = smTransCommand.SParam;
			return TRUE;
		}
	}

	return FALSE;
}


int rsSendAreaServerSkillDelayItem(rsPLAYINFO *lpPlayInfo)
{
	smTRANS_COMMAND	smTransCommand;
	DWORD	dwCodeKey;
	DWORD	dwMaskKey;

	if(lpPlayInfo->dwSkillDelay_SaveTime && lpPlayInfo->dwSkillDelay_SaveTime > dwPlayServTime)
	{

		if(lpPlayInfo->dwSkillDelay_NextSetTime && lpPlayInfo->dwSkillDelay_NextSetTime > dwPlayServTime)
			return FALSE;

		dwCodeKey = dwPlayServTime & 0x3FFFFFFF;
		lpPlayInfo->dwSkillDelay_NextSetTime = dwPlayServTime + 1000 * 30;

		dwMaskKey = lpPlayInfo->dwObjectSerial*(lpPlayInfo->dwCode_Name << 3);
		dwMaskKey ^= dwCodeKey;



		smTransCommand.code = OpCode::OPCODE_SKILLDELAY_DATA;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = (lpPlayInfo->dwSkillDelay_SaveCode) ^ dwMaskKey;
		smTransCommand.LParam = (lpPlayInfo->dwSkillDelay_SaveTime - dwPlayServTime) ^ dwMaskKey;
		smTransCommand.SParam = lpPlayInfo->dwSkillDelay_SaveData^dwMaskKey;
		smTransCommand.EParam = dwCodeKey;

		rsSendAreaServer(lpPlayInfo->lpsmSock, &smTransCommand);
	}
	else
	{
		lpPlayInfo->dwSkillDelay_NextSetTime = 0;
		lpPlayInfo->dwSkillDelay_SaveCode = 0;
		lpPlayInfo->dwSkillDelay_SaveTime = 0;
		lpPlayInfo->dwSkillDelay_SaveData = 0;
	}


	return TRUE;
}


int rsRecvAreaServerSkillDelayItem(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{

	DWORD	dwCodeKey;
	DWORD	dwMaskKey;
	DWORD	dwItemMask;
	int		cnt = 0;
	smTRANS_COMMAND	smTransCommand;

	memcpy(&smTransCommand, lpTransCommand, sizeof(smTRANS_COMMAND));

	dwCodeKey = lpTransCommand->EParam;
	dwMaskKey = lpPlayInfo->dwObjectSerial*(lpPlayInfo->dwCode_Name << 3);
	dwMaskKey ^= dwCodeKey;

	smTransCommand.WParam ^= dwMaskKey;
	smTransCommand.LParam ^= dwMaskKey;
	smTransCommand.SParam ^= dwMaskKey;

	if((smTransCommand.WParam&sinITEM_MASK2) != sinBC1) return FALSE;

	dwItemMask = smTransCommand.WParam&sinITEM_MASK3;
	if(dwItemMask == sin30 || dwItemMask == sin33 || dwItemMask == sin36) cnt = 0;
	if(dwItemMask == sin31 || dwItemMask == sin34 || dwItemMask == sin37) cnt = 1;
	if(dwItemMask == sin32 || dwItemMask == sin35 || dwItemMask == sin38) cnt = 2;

	if(dwItemMask == sin30 || dwItemMask == sin31 || dwItemMask == sin32)
	{
		if(smTransCommand.LParam <= (BoosterItem_UseTime[cnt] * 1000))
		{
			lpPlayInfo->dwSkillDelay_Code = smTransCommand.WParam;
			lpPlayInfo->dwSkillDelay_Time = dwPlayServTime + smTransCommand.LParam;
			lpPlayInfo->dwSkillDelay_Data = smTransCommand.SParam;
			return TRUE;
		}
	}

	return FALSE;
}




#else


int rsSendGameServerExp(rsPLAYINFO *lpPlayInfo)
{
	return TRUE;
}

int rsRecvGameServerExp(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	return TRUE;
}

#endif








int rsReOpenEventMonster(STG_AREA *lpStgArea, smCHAR *lpChar)
{
	STG_CHAR_INFO StgCharInfo;
	int cnt;

	if(!lpChar->smMonsterInfo.EventCode || !lpStgArea) return FALSE;

	if(lpChar->smMonsterInfo.EventCode == 100 && !dwServ_NightDay)
		return FALSE;


	for(cnt = 0; cnt < chrMonsterCnt; cnt++)
	{
		if(chrMonsterList[cnt].lpMonInfo->EventCode == lpChar->smMonsterInfo.EventCode &&
			chrMonsterList[cnt].lpMonInfo->EventInfo == lpChar->smMonsterInfo.EventInfo &&
			lstrcmp(chrMonsterList[cnt].szName, lpChar->smCharInfo.szName) == 0)
		{

			memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));
			lpStgArea->EvnMonster = TRUE;
			lpStgArea->OpenMonster(&StgCharInfo, 0);
			break;
		}
	}


	return TRUE;
}




int rsOpenEventMonster(int EventCode, int wParam, int lParam, int sParam)
{

	STG_CHAR_INFO StgCharInfo;
	STG_AREA	*lpStgArea;

	int cnt;



	switch(EventCode)
	{
	case 100:
		for(cnt = 0; cnt < chrMonsterCnt; cnt++)
		{
			if(chrMonsterList[cnt].lpMonInfo && chrMonsterList[cnt].lpMonInfo->EventCode == EventCode)
			{
				memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));

				lpStgArea = &StageArea[chrMonsterList[cnt].lpMonInfo->EventInfo];

				lpStgArea->EvnMonster = TRUE;
				lpStgArea->OpenMonster(&StgCharInfo, 0);
				lpStgArea->StartPosRandomize();
			}
		}
		break;

	case 110:


		break;
	}


	return FALSE;
}


int rsCloseEventMonster(int EventCode)
{
	int cnt;

	for(cnt = 0; cnt < AUTOPLAYER_MAX; cnt++)
	{
		if(chrAutoPlayer[cnt].Flag && chrAutoPlayer[cnt].smMonsterInfo.EventCode == EventCode)
		{

			if(chrAutoPlayer[cnt].MotionInfo->State != CHRMOTION_STATE_DEAD)
			{
				if(chrAutoPlayer[cnt].SetMotionFromCode(CHRMOTION_STATE_WARP) == FALSE)
				{
					chrAutoPlayer[cnt].Close();
				}

				if(chrAutoPlayer[cnt].lpExt1)
				{
					((STG_AREA *)chrAutoPlayer[cnt].lpExt1)->MonsterCount--;
					((STG_AREA *)chrAutoPlayer[cnt].lpExt1)->DeleteMonTable(&chrAutoPlayer[cnt]);
				}
			}
			else
			{
				chrAutoPlayer[cnt].Close();
				if(chrAutoPlayer[cnt].lpExt1)
				{
					((STG_AREA *)chrAutoPlayer[cnt].lpExt1)->MonsterCount--;
					((STG_AREA *)chrAutoPlayer[cnt].lpExt1)->DeleteMonTable(&chrAutoPlayer[cnt]);
				}
			}
		}
	}

	return TRUE;
}



int rsOpenBossMonster(STG_AREA *lpStgArea, sBOSS_MONSTER *lpBossMonster)
{
	STG_CHAR_INFO StgCharInfo;
	int cnt = 0;
	POINT3D	pos3D;
	smCHAR *lpChar = nullptr;

	if(lpBossMonster->MasterMonster->dwCharSoundCode == snCHAR_SOUND_BABEL && lpStgArea->lpField)
	{
		if(dwBabelPlayTime > dwPlayServTime)
		{
			return FALSE;
		}

		if(lpStgArea->lpField->FieldCode == rsBABEL_FIELD)
		{
			pos3D.x = 50172 * fONE;
			pos3D.y = 0;
			pos3D.z = 13193 * fONE;
		}
		else
		{
			pos3D.x = 37086 * fONE;
			pos3D.y = 0;
			pos3D.z = 26425 * fONE;
		}

		lprsFixedPoint = &pos3D;
		BabelPlayField = lpStgArea->lpField->FieldCode;

		for(cnt = 0; cnt < STG_MONSTER_MAX; cnt++)
		{
			if(lpStgArea->lpCharMonster[cnt])
			{
				if(lpStgArea->lpCharMonster[cnt]->Flag && lpStgArea->lpCharMonster[cnt]->MotionInfo->State != CHRMOTION_STATE_DEAD)
				{
					lpStgArea->lpCharMonster[cnt]->SetMotionFromCode(CHRMOTION_STATE_DAMAGE);
					lpStgArea->lpCharMonster[cnt]->PlayStunCount = 16 * 8;
				}
			}
		}
	}


	if(lpBossMonster->MasterMonster->dwCharSoundCode == snCHAR_SOUND_DEATHKNIGHT &&
		lpStgArea->lpField && lpStgArea->lpField->FieldCode == 31)
	{

		pos3D.x = 34042 * fONE;
		pos3D.y = 0;
		pos3D.z = 36709 * fONE;
		lprsFixedPoint = &pos3D;

	}


	if(lpBossMonster->MasterMonster->dwCharSoundCode == snCHAR_SOUND_KELVEZU &&
		lpStgArea->lpField && lpStgArea->lpField->FieldCode == rsKELVEZU_FIELD)
	{

		pos3D.x = 33023 * fONE;
		pos3D.y = 0;
		pos3D.z = 52608 * fONE;
		lprsFixedPoint = &pos3D;

	}

	if(lpBossMonster->MasterMonster->dwCharSoundCode == snCHAR_SOUND_MOKOVA &&
		lpStgArea->lpField && lpStgArea->lpField->FieldCode == rsMOKOVA_FIELD)
	{

		pos3D.x = -12057 * fONE;
		pos3D.y = 0;
		pos3D.z = 13225 * fONE;
		lprsFixedPoint = &pos3D;
	}


	if(lpBossMonster->MasterMonster->dwCharSoundCode == snCHAR_SOUND_FURY &&
		lpStgArea->lpField && lpStgArea->lpField->FieldCode == 42)
	{
		pos3D.x = -872 * fONE;
		pos3D.y = 0;
		pos3D.z = -45168 * fONE;
		lprsFixedPoint = &pos3D;
	}




	if(lpBossMonster->MasterMonster)
	{
		memcpy(&StgCharInfo.smCharInfo, lpBossMonster->MasterMonster, sizeof(smCHAR_INFO));
		lpStgArea->EvnMonster = TRUE;
		lpChar = lpStgArea->OpenMonster(&StgCharInfo, 0);
		lpStgArea->StartPointCnt = lpStgArea->StartPointLastOpenCount;
	}


	if(lpBossMonster->SlaveMonster)
	{
		memcpy(&StgCharInfo.smCharInfo, lpBossMonster->SlaveMonster, sizeof(smCHAR_INFO));
		lpStgArea->EvnMonster = TRUE;
		lpStgArea->OpenMonster(&StgCharInfo, lpBossMonster->SlaveCount);
	}

	if(lprsFixedPoint)
	{
		lprsFixedPoint = 0;
		if(lpChar)
		{
			lpChar->lpAttackDamageList = new ATTACK_DAMAGE_LIST[ATTACK_DAMAGE_LIST_MAX];
			if(lpChar->lpAttackDamageList)
				ZeroMemory(lpChar->lpAttackDamageList, sizeof(ATTACK_DAMAGE_LIST)*ATTACK_DAMAGE_LIST_MAX);
		}
	}

	return FALSE;
}


int	rsSendCommandUser(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND_EX	*lpTransCommandEx)
{
	int cnt;
	int rx, rz, dist;
	int x, z;

	lpTransCommandEx->code = OpCode::OPCODE_COMMAND_USER;
	lpTransCommandEx->size = sizeof(smTRANS_COMMAND_EX);

	x = lpPlayInfo->Position.x;
	z = lpPlayInfo->Position.z;

	for(cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial)
		{
			rx = (x - rsPlayInfo[cnt].Position.x) >> FLOATNS;
			rz = (z - rsPlayInfo[cnt].Position.z) >> FLOATNS;
			dist = rx*rx + rz*rz;

			if(dist < DIST_TRANSLEVEL_HIGH && abs(rx) < TRANS_VIEW_LIMIT && abs(rz) < TRANS_VIEW_LIMIT)
			{
				rsPlayInfo[cnt].lpsmSock->Send((char *)lpTransCommandEx, lpTransCommandEx->size, TRUE);
			}
		}
	}

	return TRUE;
}


int	rsSendCommandUser2(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	int cnt;
	int rx, rz, dist;
	int x, z;

	x = lpPlayInfo->Position.x;
	z = lpPlayInfo->Position.z;

	for(cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial)
		{
			rx = (x - rsPlayInfo[cnt].Position.x) >> FLOATNS;
			rz = (z - rsPlayInfo[cnt].Position.z) >> FLOATNS;
			dist = rx*rx + rz*rz;

			if(dist < DIST_TRANSLEVEL_HIGH && abs(rx) < TRANS_VIEW_LIMIT && abs(rz) < TRANS_VIEW_LIMIT)
			{
				rsPlayInfo[cnt].lpsmSock->Send((char *)lpTransCommand, lpTransCommand->size, TRUE);
			}
		}
	}

	return TRUE;
}











static int rsCompString(char *src1, char *src2)
{
	int cnt;
	int len1, len2;
	int len;

	len1 = lstrlen(src1);
	len2 = lstrlen(src2);

	if(len1 < len2) len = len1;
	else len = len2;

	if(!len) return NULL;

	for(cnt = 0; cnt < len1; cnt++)
	{
		if(src1[cnt] == 0) break;
		if(src1[cnt] != src2[cnt]) return NULL;
	}

	return cnt;
}

char *rsGetWord(char *q, char *p)
{


	if(*p == 0)
	{
		*q = 0; return p;
	}

	while((*p == 32) || (*p == 9) || (*p == 58))
	{
		p++;
	}

	while((*p != 32) && (*p != 9) && (*p != 58) && (*p != 0))
	{
		if(*p == '\n' || *p == '\r') break;
		*q++ = *p++;
	}
	*q++ = 0;



	return p;
}


rsPLAYINFO *FindUserFromName(char *szName)
{
	int cnt;

	for(cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].TransInfoFlag)
		{
			if(lstrcmpi(rsPlayInfo[cnt].smCharInfo.szName, szName) == 0)
			{
				return &rsPlayInfo[cnt];
			}
		}
	}

	return NULL;
}

rsPLAYINFO *FindUserFromName2(char *szName)
{
	int cnt;

	for(cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		if(rsPlayInfo[cnt].lpsmSock)
		{
			if(lstrcmpi(rsPlayInfo[cnt].getName().c_str(), szName) == 0)
			{
				return &rsPlayInfo[cnt];
			}
		}
	}

	return NULL;
}


rsPLAYINFO *FindUserFromCode(DWORD dwUserCode)
{
	int cnt;

	if(dwUserCode)
	{
		for(cnt = 0; cnt < CONNECTMAX; cnt++)
		{
			if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial == dwUserCode)
			{
				return &rsPlayInfo[cnt];
			}
		}
	}

	return NULL;
}


rsPLAYINFO *FindUserFromName3(char *szName)
{
	int cnt;

	for(cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		if(rsPlayInfo[cnt].lpsmSock)
		{
			if(!rsPlayInfo[cnt].getName().empty())
			{
				if(lstrcmpi(rsPlayInfo[cnt].getName().c_str(), szName) == 0)
				{
					return &rsPlayInfo[cnt];
				}
			}
			else
			{
				if(lstrcmpi(rsPlayInfo[cnt].smCharInfo.szName, szName) == 0)
				{
					return &rsPlayInfo[cnt];
				}
			}
		}
	}

	return NULL;
}

rsPLAYINFO *FindUserFromCodeName(char *szName, DWORD dwSpeedSum)
{
	int cnt;

	for(cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		if(rsPlayInfo[cnt].lpsmSock)
		{
			if(rsPlayInfo[cnt].dwCode_Name == dwSpeedSum && lstrcmpi(rsPlayInfo[cnt].getName().c_str(), szName) == 0)
			{
				return &rsPlayInfo[cnt];
			}
		}
	}

	return NULL;
}


rsPLAYINFO *FindUserFromID(char *szID)
{
	for(int cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		if(rsPlayInfo[cnt].lpsmSock && !rsPlayInfo[cnt].getAccount().empty())
		{
			if(lstrcmpi(rsPlayInfo[cnt].getAccount().c_str(), szID) == 0)
			{
				return &rsPlayInfo[cnt];
			}
		}
	}

	return NULL;
}





int CreatePresentItem(DWORD dwItemCode, STG_AREA *lpStgArea, int x, int y, int z, int count)
{
	psITEM			psItem;
	int				cnt;
	STG_ITEMS		*lpStgItem;

	ZeroMemory(&psItem, sizeof(psITEM));

	for(cnt = 0; cnt < DefaultItemCount; cnt++)
	{
		if(DefaultItems[cnt].Item.CODE == dwItemCode && !DefaultItems[cnt].Item.UniqueItem)
		{
			CreateDefItem(&psItem.ItemInfo, &DefaultItems[cnt]);

			psItem.state = TRUE;
			if((psItem.ItemInfo.CODE&sinITEM_MASK2) == (sinPM1&sinITEM_MASK2))
			{
				psItem.ItemInfo.PotionCount = (rand() % count) + 1;
			}

			lpStgItem = lpStgArea->AddItem(&psItem, x >> FLOATNS, y >> FLOATNS, z >> FLOATNS, TRUE);
			lpStgItem->dwCreateTime += 5000;


			return TRUE;
		}
	}
	return FALSE;
}



int CreateCommandItem(rsPLAYINFO *lpPlayInfo, rsPLAYINFO *lpPlayInfo2, char *szItem)
{
	psITEM			*lpsItem;
	STG_AREA		*lpStgArea;
	TRANS_ITEMINFO	TransItemInfo;
	char		szItemName[32];
	int cnt, cnt2, len;
	int val;

	val = FALSE;

	if(spJobCodeTime < dwPlayServTime)
	{
		spJobCode = 0;
		spItemNormal = 0;
		spJobCodeTime = 0;
	}

	if(spTimeAdjustTime < dwPlayServTime)
	{
		spTimeAdjustTime = 0;
		spTimeAdjust = 0;
	}


	if(lpPlayInfo->getSecurity() < AccountTypes::SEC_ADMINISTRATOR && szItem[0] != '@')
		return FALSE;

	lpsItem = new psITEM;

	if(szItem[0] != '\"')
	{
		if(szItem[0] != '@')
		{
			if(srSetItemFromCode(lpsItem, szItem) == TRUE)
			{
				if(lpPlayInfo2)
				{

					if(lpPlayInfo2->lpsmSock)
					{
						TransItemInfo.code = OpCode::OPCODE_PUTITEM;
						TransItemInfo.size = sizeof(TRANS_ITEMINFO);
						memcpy(&TransItemInfo.Item, &lpsItem->ItemInfo, sizeof(sITEMINFO));


						rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);
						if (lpPlayInfo2->lpsmSock)
							lpPlayInfo2->lpsmSock->Send((char *)&TransItemInfo, TransItemInfo.size, TRUE);
						val = TRUE;
					}
				}
				else
				{

					lpStgArea = FindStageField(lpPlayInfo->Position.x, lpPlayInfo->Position.z);
					if(lpStgArea)
					{
						lpsItem->state = TRUE;
						lpStgArea->AddItem(lpsItem, lpPlayInfo->Position.x >> FLOATNS, lpPlayInfo->Position.y >> FLOATNS, lpPlayInfo->Position.z >> FLOATNS, TRUE);
						val = TRUE;
					}
				}
			}
		}
		else
		{

			if(srSetItemFromLogData(lpsItem, szItem + 1) == TRUE)
			{
				if(lpPlayInfo2)
				{

					if(lpPlayInfo2->lpsmSock)
					{
						TransItemInfo.code = OpCode::OPCODE_PUTITEM;
						TransItemInfo.size = sizeof(TRANS_ITEMINFO);
						memcpy(&TransItemInfo.Item, &lpsItem->ItemInfo, sizeof(sITEMINFO));
						rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);
						lpPlayInfo2->lpsmSock->Send((char *)&TransItemInfo, TransItemInfo.size, TRUE);
						val = TRUE;
					}
				}
				else
				{

					lpStgArea = FindStageField(lpPlayInfo->Position.x, lpPlayInfo->Position.z);
					if(lpStgArea)
					{
						lpsItem->state = TRUE;
						lpStgArea->AddItem(lpsItem, lpPlayInfo->Position.x >> FLOATNS, lpPlayInfo->Position.y >> FLOATNS, lpPlayInfo->Position.z >> FLOATNS, TRUE);
						val = TRUE;
					}
				}
			}
		}
	}
	else
	{
		cnt2 = 0;
		len = lstrlen(szItem);
		for(cnt = 1; cnt < len; cnt++)
		{
			if(szItem[cnt] == '\"')
			{
				szItemName[cnt2] = 0; break;
			}
			szItemName[cnt2++] = szItem[cnt];
		}


		if(srSetItemFromName(lpsItem, szItemName) == TRUE)
		{
			if(lpPlayInfo2)
			{

				if(lpPlayInfo2->lpsmSock)
				{
					TransItemInfo.code = OpCode::OPCODE_PUTITEM;
					TransItemInfo.size = sizeof(TRANS_ITEMINFO);
					memcpy(&TransItemInfo.Item, &lpsItem->ItemInfo, sizeof(sITEMINFO));
					rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);
					lpPlayInfo2->lpsmSock->Send((char *)&TransItemInfo, TransItemInfo.size, TRUE);
					val = TRUE;
				}
			}
			else
			{

				lpStgArea = FindStageField(lpPlayInfo->Position.x, lpPlayInfo->Position.z);
				if(lpStgArea)
				{
					lpsItem->state = TRUE;
					lpStgArea->AddItem(lpsItem, lpPlayInfo->Position.x >> FLOATNS, lpPlayInfo->Position.y >> FLOATNS, lpPlayInfo->Position.z >> FLOATNS, TRUE);
					val = TRUE;
				}
			}
		}
	}
	delete lpsItem;

	return val;
}


int rsPutItem_PointTicket(rsPLAYINFO *lpPlayInfo, int Price)
{
	TRANS_ITEMINFO	TransItemInfo;
	psITEM	psItem;
	int cnt;

	for(cnt = 0; cnt < DefaultItemCount; cnt++)
	{
		if(DefaultItems[cnt].Item.CODE == (sinGF1 | sin01) && !DefaultItems[cnt].Item.UniqueItem)
		{
			CreateDefItem(&psItem.ItemInfo, &DefaultItems[cnt]);

			if(lpPlayInfo->lpsmSock)
			{
				TransItemInfo.code = OpCode::OPCODE_PUTITEM;
				TransItemInfo.size = sizeof(TRANS_ITEMINFO);
				memcpy(&TransItemInfo.Item, &psItem.ItemInfo, sizeof(sITEMINFO));
				TransItemInfo.Item.Price = Price;
				ReformItem(&TransItemInfo.Item);
				rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);
				lpPlayInfo->lpsmSock->Send((char *)&TransItemInfo, TransItemInfo.size, TRUE);
			}
			return TRUE;
		}
	}

	return TRUE;
}


int rsCheck_ChageJob(rsPLAYINFO *lpPlayInfo, int NewCnageJob)
{
	DWORD	dwItemCode;
	psITEM	psItem;
	int cnt;

	if(lpPlayInfo->smCharInfo.ChangeJob == 1 && NewCnageJob == 2)
	{

		dwItemCode = sinOR2 | sin03;

		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MAGICIAN || lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_PRIESTESS)
			dwItemCode = sinOR2 | sin02;

		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_ATALANTA || lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_ARCHER)
			dwItemCode = sinOR2 | sin04;

		for(cnt = 0; cnt < INVEN_ITEM_INFO_MAX; cnt++)
		{
			if(lpPlayInfo->InvenItemInfo[cnt].dwCode == dwItemCode)
				return FALSE;
		}

		for(cnt = 0; cnt < DefaultItemCount; cnt++)
		{
			if(DefaultItems[cnt].Item.CODE == dwItemCode)
			{
				CreateDefItem(&psItem.ItemInfo, &DefaultItems[cnt]);
				psItem.ItemInfo.ItemKindCode = ITEM_KIND_QUEST_WEAPON;
				ReformItem(&psItem.ItemInfo);

				return rsPutItem2(lpPlayInfo, &psItem.ItemInfo);
			}
		}

	}

	return FALSE;
}



int rsPutItem(rsPLAYINFO *lpPlayInfo, DWORD dwItemCode)
{
	TRANS_ITEMINFO	TransItemInfo;
	psITEM	psItem;
	int cnt;

	for(cnt = 0; cnt < DefaultItemCount; cnt++)
	{
		if(DefaultItems[cnt].Item.CODE == dwItemCode && !DefaultItems[cnt].Item.UniqueItem)
		{
			CreateDefItem(&psItem.ItemInfo, &DefaultItems[cnt]);

			if(lpPlayInfo->lpsmSock)
			{
				TransItemInfo.code = OpCode::OPCODE_PUTITEM;
				TransItemInfo.size = sizeof(TRANS_ITEMINFO);
				memcpy(&TransItemInfo.Item, &psItem.ItemInfo, sizeof(sITEMINFO));
				rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);
				lpPlayInfo->lpsmSock->Send((char *)&TransItemInfo, TransItemInfo.size, TRUE);
			}
			return TRUE;
		}
	}

	return TRUE;
}


int rsPutItem(rsPLAYINFO *lpPlayInfo, DWORD dwItemCode, int spJobCode)
{
	TRANS_ITEMINFO	TransItemInfo;
	psITEM	psItem;
	int cnt;
	int JobCodeItem = 0;
	int PotionCount = 0;

	if((dwItemCode&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
	{

		PotionCount = spJobCode;
	}
	else
	{

		JobCodeItem = spJobCode;
	}


	for(cnt = 0; cnt < DefaultItemCount; cnt++)
	{
		if(DefaultItems[cnt].Item.CODE == dwItemCode && !DefaultItems[cnt].Item.UniqueItem)
		{
			CreateDefItem(&psItem.ItemInfo, &DefaultItems[cnt], JobCodeItem);

			psItem.ItemInfo.PotionCount = PotionCount;

			if(lpPlayInfo->lpsmSock)
			{
				TransItemInfo.code = OpCode::OPCODE_PUTITEM;
				TransItemInfo.size = sizeof(TRANS_ITEMINFO);
				memcpy(&TransItemInfo.Item, &psItem.ItemInfo, sizeof(sITEMINFO));
				rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);
				lpPlayInfo->lpsmSock->Send((char *)&TransItemInfo, TransItemInfo.size, TRUE);
			}
			return TRUE;
		}
	}

	return TRUE;
}


int rsPutItemUnique(rsPLAYINFO *lpPlayInfo, DWORD dwItemCode, int spJobCode, DWORD dwUniqueCode)
{
	TRANS_ITEMINFO	TransItemInfo;
	psITEM	psItem;
	int cnt;
	int JobCodeItem = 0;
	int PotionCount = 0;

	if((dwItemCode&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
	{

		PotionCount = spJobCode;
	}
	else
	{

		JobCodeItem = spJobCode;
	}


	for(cnt = 0; cnt < DefaultItemCount; cnt++)
	{
		if(DefaultItems[cnt].Item.CODE == dwItemCode && DefaultItems[cnt].Item.UniqueItem == dwUniqueCode)
		{
			CreateDefItem(&psItem.ItemInfo, &DefaultItems[cnt], JobCodeItem);

			psItem.ItemInfo.PotionCount = PotionCount;

			if(lpPlayInfo->lpsmSock)
			{
				TransItemInfo.code = OpCode::OPCODE_PUTITEM;
				TransItemInfo.size = sizeof(TRANS_ITEMINFO);
				memcpy(&TransItemInfo.Item, &psItem.ItemInfo, sizeof(sITEMINFO));
				rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);
				lpPlayInfo->lpsmSock->Send((char *)&TransItemInfo, TransItemInfo.size, TRUE);
			}
			return TRUE;
		}
	}

	return TRUE;
}



sDEF_ITEMINFO *rsPutItem3(rsPLAYINFO *lpPlayInfo, DWORD dwItemCode)
{
	TRANS_ITEMINFO	TransItemInfo;
	psITEM	psItem;
	int cnt;

	for(cnt = 0; cnt < DefaultItemCount; cnt++)
	{
		if(DefaultItems[cnt].Item.CODE == dwItemCode && !DefaultItems[cnt].Item.UniqueItem)
		{
			CreateDefItem(&psItem.ItemInfo, &DefaultItems[cnt]);

			if(lpPlayInfo->lpsmSock)
			{
				TransItemInfo.code = OpCode::OPCODE_PUTITEM;
				TransItemInfo.size = sizeof(TRANS_ITEMINFO);
				memcpy(&TransItemInfo.Item, &psItem.ItemInfo, sizeof(sITEMINFO));
				rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);
				lpPlayInfo->lpsmSock->Send((char *)&TransItemInfo, TransItemInfo.size, TRUE);
			}
			return &DefaultItems[cnt];
		}
	}

	return NULL;
}



int rsPutItem2(rsPLAYINFO *lpPlayInfo, sITEMINFO *lpItem)
{
	TRANS_ITEMINFO	TransItemInfo;

	if(lpPlayInfo->lpsmSock)
	{
		TransItemInfo.code = OpCode::OPCODE_PUTITEM;
		TransItemInfo.size = sizeof(TRANS_ITEMINFO);
		memcpy(&TransItemInfo.Item, lpItem, sizeof(sITEMINFO));
		rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);
		return lpPlayInfo->lpsmSock->Send((char *)&TransItemInfo, TransItemInfo.size, TRUE);
	}
	return FALSE;
}


int rsSendNetLOG(rsPLAYINFO *lpPlayInfo)
{
	TRANS_CHATMESSAGE	TransChatMessage;

	wsprintf(TransChatMessage.szMessage,
		"> Rcv(%d) Snd(%d) ScoopRcv(%d) ScoopFail(%d) SndFail(%d) RcvFail(%d)",
		lpPlayInfo->lpsmSock->RecvPacketCount,
		lpPlayInfo->lpsmSock->SendPacketCount,
		lpPlayInfo->lpsmSock->RecvPopCount,
		lpPlayInfo->lpsmSock->RecvPopErrorCount,
		lpPlayInfo->lpsmSock->SendPacketErrorCount,
		lpPlayInfo->lpsmSock->RecvPacketErrorCount);


	TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
	TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
	TransChatMessage.dwIP = 0;
	TransChatMessage.dwObjectSerial = 0;

	return lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
}

int	InitCrackFinding()
{
	return TRUE;
}

int	SendFindCrack(smWINSOCK *lpsmSock)
{
	return TRUE;
}

int RecvCommand(rsPLAYINFO *lpPlayInfo, char *szChatCommand)
{
	return TRUE;
}








bool initialize(rsPLAYINFO *player)
{

	return false;
}



bool handlePlayerLoginOpcode(smTHREADSOCK *SockInfo)
{

	return false;
}


int RecvMessage(smTHREADSOCK *SockInfo)
{
	return TRUE;
}



int MakePlayerList()
{
	int cnt;
	int ListCnt;

	PlayerCount = 0;
	ListCnt = 2;

	for(cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		if(smWSock[cnt].sock)
		{
			ListBuff[ListCnt++] = smWSock[cnt].acc_sin.sin_addr.S_un.S_addr;
			PlayerCount++;
		}
	}

	ListBuff[0] = ListCnt * sizeof(DWORD);
	ListBuff[1] = OpCode::OPCODE_IPLIST;

	return ListBuff[0];
}


void DisplayMessage()
{
#ifdef _W_SERVER


	int cnt;
	int SockCnt;
	int	pCnt = 0;
	DWORD pTimeMax = 0;
	DWORD pAvgTime = 0;

	SockCnt = 1000;
	for(cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		if(smWSock[cnt].sock || smWSock[cnt].lpsmRecvRoute || smWSock[cnt].lpsmSendRoute)
		{
			SockCnt++;
		}
	}

	cnt = rsGetUserCounter(PlayerCount);

	if(ShutDownFlag)
	{
		wsprintf(szMessageBuff, "Servidor desligando (%d)\r\nFechando servidor\r\nRestam %d Min.\r\n", cnt, ShutDownLeftTime + 1);
		SetWindowText(hMsgTextWnd, szMessageBuff);
		return;
	}

	szMessageBuff[0] = 0;
	pCnt = b_SqlGetQueProcessTime(&pTimeMax, &pAvgTime);

	switch(Svr_DisplayMode)
	{

	case 0:

		if(AutoPlayServer || UserPlayServer)
		{
			wsprintf(szMessageBuff, "Status do Servidor\r\nUsuarios : %d\r\nMonstros: %d\r\nMensagens Recebidas : %d\r\nProcessos: ( Snd:%d Rcv:%d )\r\nErros de Rota: %d\r\nErros de Conex�o : %d (%d)",
				cnt, ActivePlayCounter, WSA_RecvMsgCount,
				GetUseingSendThreadCount(), GetUseingRecvThreadCount(),
				srRouteErrorCount,
				srAcceptErrorCount, srLastAcceptRsult);
		}
		else
		{
			wsprintf(szMessageBuff, "[Login Server]\r\nUsu�rios : %d\r\nFalha no Login: %d\r\nProcesso Login: %d/%d Proc(%d) DLL_Code(%d)\r\n�ltimo Login: %s (%d)\r\nLogin Que: %d\r\nLogQue Using: %d\r\nLogQue Process: %d/ Avg(%d) Max(%d)\r\nLogQue Failed: %d\r\nItem Log: Using(%d) Failed(%d)\r\nEvent Log: Using(%d) Failed(%d)\r\n",
				cnt, srLogFailedCount,
				LogOnThread_Sucess, LogOnThread_Count, LogOnThread_Process, UseDLL_Code,
				szLastLogInID, LastLogInResult,
				rsGetLogOnQueCount(),
				b_SqlGetQueSize(), pCnt, pAvgTime, pTimeMax,
				b_SqlGetLossCount(),
				b_SqlGetItemQueSize(), b_SqlGetItemLossCount(),
				b_SqlGetEventQueSize(), b_SqlGetEventLossCount());
		}
		break;

	case 1:
		wsprintf(szMessageBuff, "[Informa寤es do Jogo]\r\nContador de Experi�ncia: %d\r\nOp. Monstro: %d\r\nItem: %d [Mny %d]\r\nItemBuffOver: %d\r\n",
			rsMonHuntCount, rsMonOpenCount, rsItemOpenCount, rsMoneyTotalCount, rsItemBuffOverCount);
		break;

	case 2:


		wsprintf(szMessageBuff, "[Configura豫o]\r\nC�digo do Servidor: %d\r\nNome do Servidor: %s\r\nVers�o: %d\r\nSafeCode Count: %d\r\nCheckSum Count: %d\r\nMonster: %d\r\nItem: %d",
			rsServerConfig.ServerCode, rsServerConfig.szServerName, rsServerConfig.LimitVersion,
			rsServerConfig.SafeClientCodeCount, rsServerConfig.ClientCheckSumCount, chrMonsterCnt, DefaultItemCount);

		break;

	case 3:


		wsprintf(szMessageBuff, "[Informa豫o de 햞ea]\r\n[Aser]Line: %d\r\n[Aser]NetState.: %d\r\n[Aser]Conn.: %d (%d)\r\n[Aser]Process: %d",
			rsGetSystemLineCount(), rsSystemNetCount, rsSystemLineConnCount, rsSystemLineFailedCount, rsSystemLinePlayCount);

		break;

	}

	WSA_RecvMsgCount = 0;
	srRouteErrorCount = 0;
	SetWindowText(hMsgTextWnd, szMessageBuff);
#endif
}


int Serv_ConnectPlayer(smWINSOCK *lpsmSock)
{


	EnterCriticalSection(&cSerSection);

	PlayerCount++;

	AddNewPlayInfo(lpsmSock);


	LeaveCriticalSection(&cSerSection);






	return TRUE;
}


int RecordSaveThrowData(rsPLAYINFO *lpPlayInfo)
{

	return TRUE;
}


int rsRecordCheckFile(rsPLAYINFO *lpPlayInfo)
{
	FILE	*fp;
	char	*lpBuff;
	char	szFile[64];
	int		result;
	smTRANS_COMMAND	smTransCommand;


	result = FALSE;

	if(!lpPlayInfo) return FALSE;
	if(!lpPlayInfo->lpRecordDataBuff || lpPlayInfo->getAccount().empty() || lpPlayInfo->getName().empty()) return FALSE;

	lpBuff = lpPlayInfo->lpRecordDataBuff;
	lpPlayInfo->lpRecordDataBuff = new char[sizeof(TRANS_RECORD_DATA)];
	if(lpPlayInfo->lpRecordDataBuff)
	{
		GetUserDataFile(lpPlayInfo->getName().c_str(), szFile);
		fp = fopen(szFile, "rb");
		if(fp)
		{
			fread(lpPlayInfo->lpRecordDataBuff, sizeof(TRANS_RECORD_DATA), 1, fp);
			fclose(fp);

			if(((TRANS_RECORD_DATA *)lpPlayInfo->lpRecordDataBuff)->code &&
				((TRANS_RECORD_DATA *)lpPlayInfo->lpRecordDataBuff)->size > 0)
			{


				rsSaveThrowData(lpPlayInfo);

				rsRecordMemoryBuff_CheckInvenItem(lpPlayInfo);

				rsRecordMemoryBuffToFile(lpPlayInfo, lpPlayInfo->getName().c_str(), lpPlayInfo->lpRecordDataBuff);


				smTransCommand.WParam = 8400;
				smTransCommand.LParam = ((TRANS_RECORD_DATA *)lpPlayInfo->lpRecordDataBuff)->size;
				smTransCommand.SParam = 0;
				smTransCommand.EParam = 0;
				RecordHackLogFile(lpPlayInfo, &smTransCommand);

				result = TRUE;
			}
		}
		delete	lpPlayInfo->lpRecordDataBuff;
	}
	lpPlayInfo->lpRecordDataBuff = lpBuff;

	return result;
}




int Serv_DisconnectPlayer(smWINSOCK *lpsmSock)
{
	rsPLAYINFO *tpInfo;
	int cnt;
	smTRANS_COMMAND	smTransCommand;

	if(!lpsmSock) return TRUE;
	if(!lpsmSock->sock) return TRUE;


	EnterCriticalSection(&cSerSection);

	PlayerCount--;

	tpInfo = (rsPLAYINFO *)lpsmSock->ExtData1;


	if(LoginServer && tpInfo)
	{
		dwServer_DebugMessage = 100;
		strcpy_s(szServer_DebugLastUserID, tpInfo->getAccount().c_str());
		strcpy_s(szServer_DebugLastUserName, tpInfo->getName().c_str());
	}
	Server_DebugCount = 100;

	if(tpInfo->lpRecordDataBuff && !tpInfo->getAccount().empty() && !tpInfo->getName().empty() &&
		((TRANS_RECORD_DATA *)tpInfo->lpRecordDataBuff)->size > 0)
	{

		((TRANS_RECORD_DATA *)tpInfo->lpRecordDataBuff)->smCharInfo.szName[31] = 0;
		if(lstrcmpi(((TRANS_RECORD_DATA *)tpInfo->lpRecordDataBuff)->smCharInfo.szName, tpInfo->getName().c_str()) == 0)
		{

			if(rsServerConfig.ServerInventoryMode)
			{
				Server_DebugCount = 101;

				rsSaveThrowData(tpInfo);
				Server_DebugCount = 102;

				rsRecordMemoryBuff_CheckInvenItem(tpInfo);
			}

			Server_DebugCount = 103;


			for(cnt = 0; cnt < 6; cnt++)
			{
				if(rsRecordMemoryBuffToFile(tpInfo, tpInfo->getName().c_str(), tpInfo->lpRecordDataBuff) == TRUE) break;


				smTransCommand.WParam = 8080;
				smTransCommand.LParam = 1;
				smTransCommand.SParam = cnt;
				smTransCommand.EParam = ((TRANS_RECORD_DATA *)tpInfo->lpRecordDataBuff)->size;
				RecordHackLogFile(tpInfo, &smTransCommand);
			}
			((TRANS_RECORD_DATA *)tpInfo->lpRecordDataBuff)->size = 0;

		}
		else
		{
			smTRANS_COMMAND smTransCommand;
			smTransCommand.WParam = 10000;
			smTransCommand.LParam = (DWORD)tpInfo->smCharInfo.szName;
			smTransCommand.SParam = (DWORD)((TRANS_RECORD_DATA *)tpInfo->lpRecordDataBuff)->smCharInfo.szName;
			RecordHackLogFile(tpInfo, &smTransCommand);
		}
	}
	else
	{

		rsRecordCheckFile(tpInfo);
	}



	Server_DebugCount = 104;

	tpInfo->DisconnectPartyUser();

	rsLogOut(tpInfo);

	tpInfo->lpsmSock = 0;
	if(tpInfo->lpAreaPlayInfo)
	{
		*tpInfo->lpAreaPlayInfo = 0;
		tpInfo->lpAreaPlayInfo = 0;
	}
	if(tpInfo->lpRecordBase)
	{
		delete tpInfo->lpRecordBase;
		tpInfo->lpRecordBase = 0;
	}
	if(tpInfo->lpPostBoxItem)
	{
		rsSavePostBox(tpInfo);
		delete	tpInfo->lpPostBoxItem;
		tpInfo->lpPostBoxItem = 0;
	}

	Server_DebugCount = 105;

	if((tpInfo->ThrowItemCount > 0 || tpInfo->UnsaveMoney >= 0) && !tpInfo->getName().empty())
		RecordSaveThrowData(tpInfo);

	if(tpInfo->SystemLine)
	{

		rsDisconnectSystemLine(lpsmSock);
		if(tpInfo->SystemLine == 2)	rsSetSerToLoginLine();
	}



	Server_DebugCount = 190;


	LeaveCriticalSection(&cSerSection);

	return TRUE;
}


extern CRITICAL_SECTION	cSocketSection;



int DisconnectUser(smWINSOCK *lpsmSock)
{
	rsPLAYINFO *tpInfo;

	DWORD	dwExitCode;
	int SecFlag;
	int cnt;
	smTRANS_COMMAND	smTransCommand;


	if(!lpsmSock) return TRUE;
	if(!lpsmSock->sock) return TRUE;

	if(cSocketSection.OwningThread) SecFlag = FALSE;
	else SecFlag = TRUE;


	if(SecFlag) smEnterCSectionSocket();

	PlayerCount--;

	tpInfo = (rsPLAYINFO *)lpsmSock->ExtData1;


	if(LoginServer && tpInfo)
	{
		dwServer_DebugMessage = 200;
		strcpy_s(szServer_DebugLastUserID, tpInfo->getAccount().c_str());
		strcpy_s(szServer_DebugLastUserName, tpInfo->getName().c_str());
	}
	Server_DebugCount = 200;

	if(tpInfo && tpInfo->lpsmSock == lpsmSock)
	{




		if(tpInfo->lpRecordDataBuff && !tpInfo->getAccount().empty() && !tpInfo->getName().empty() &&
			((TRANS_RECORD_DATA *)tpInfo->lpRecordDataBuff)->size > 0)
		{

			((TRANS_RECORD_DATA *)tpInfo->lpRecordDataBuff)->smCharInfo.szName[31] = 0;

			if(lstrcmpi(((TRANS_RECORD_DATA *)tpInfo->lpRecordDataBuff)->smCharInfo.szName, tpInfo->getName().c_str()) == 0)
			{

				if(rsServerConfig.ServerInventoryMode)
				{
					Server_DebugCount = 201;


					rsSaveThrowData(tpInfo);

					Server_DebugCount = 202;


					rsRecordMemoryBuff_CheckInvenItem(tpInfo);
				}

				Server_DebugCount = 203;

				for(cnt = 0; cnt < 6; cnt++)
				{
					if(rsRecordMemoryBuffToFile(tpInfo, tpInfo->getName().c_str(), tpInfo->lpRecordDataBuff) == TRUE) break;


					smTransCommand.WParam = 8080;
					smTransCommand.LParam = 2;
					smTransCommand.SParam = cnt;
					smTransCommand.EParam = ((TRANS_RECORD_DATA *)tpInfo->lpRecordDataBuff)->size;
					RecordHackLogFile(tpInfo, &smTransCommand);
				}
				((TRANS_RECORD_DATA *)tpInfo->lpRecordDataBuff)->size = 0;

			}
			else
			{
				smTRANS_COMMAND smTransCommand;
				smTransCommand.WParam = 10001;
				smTransCommand.LParam = (DWORD)tpInfo->smCharInfo.szName;
				smTransCommand.SParam = (DWORD)((TRANS_RECORD_DATA *)tpInfo->lpRecordDataBuff)->smCharInfo.szName;
				RecordHackLogFile(tpInfo, &smTransCommand);
			}
		}
		else
		{


			rsRecordCheckFile(tpInfo);
		}


		Server_DebugCount = 204;

		tpInfo->DisconnectPartyUser();


		rsLogOut(tpInfo);

		tpInfo->lpsmSock = 0;
		if(tpInfo->lpAreaPlayInfo)
		{
			*tpInfo->lpAreaPlayInfo = 0;
			tpInfo->lpAreaPlayInfo = 0;
		}
		if(tpInfo->lpRecordBase)
		{
			delete tpInfo->lpRecordBase;
			tpInfo->lpRecordBase = 0;
		}
		if(tpInfo->lpPostBoxItem)
		{
			rsSavePostBox(tpInfo);
			delete	tpInfo->lpPostBoxItem;
			tpInfo->lpPostBoxItem = 0;
		}

		Server_DebugCount = 205;

		if((tpInfo->ThrowItemCount > 0 || tpInfo->UnsaveMoney >= 0) && !tpInfo->getName().empty())
			RecordSaveThrowData(tpInfo);

		if(tpInfo->SystemLine)
		{

			rsDisconnectSystemLine(lpsmSock);
			if(tpInfo->SystemLine == 2)	rsSetSerToLoginLine();
		}

	}

	Server_DebugCount = 290;

	if(!smTransThreadMode)
	{

		lpsmSock->smSendState.dwExitThread = TRUE;
		ResumeThread(lpsmSock->hSendThread);

		lpsmSock->smRecvState.dwExitThread = TRUE;
		ResumeThread(lpsmSock->hRecvThread);


		WaitForSingleObject(lpsmSock->hSendThread, 5000);
		GetExitCodeThread(lpsmSock->hSendThread, &dwExitCode);

		if(dwExitCode == STILL_ACTIVE)
		{
			lpsmSock->smSendState.dwExitThread = TRUE;
			ResumeThread(lpsmSock->hSendThread);

			WaitForSingleObject(lpsmSock->hSendThread, 5000);
			GetExitCodeThread(lpsmSock->hSendThread, &dwExitCode);

			if(dwExitCode == STILL_ACTIVE)
			{
				TerminateThread(lpsmSock->hSendThread, 1);
			}
		}


		WaitForSingleObject(lpsmSock->hRecvThread, 5000);
		GetExitCodeThread(lpsmSock->hRecvThread, &dwExitCode);

		if(dwExitCode == STILL_ACTIVE)
		{
			lpsmSock->smRecvState.dwExitThread = TRUE;
			ResumeThread(lpsmSock->hRecvThread);

			WaitForSingleObject(lpsmSock->hRecvThread, 5000);
			GetExitCodeThread(lpsmSock->hRecvThread, &dwExitCode);

			if(dwExitCode == STILL_ACTIVE)
			{
				TerminateThread(lpsmSock->hRecvThread, 1);
			}
		}
	}
	else
	{

		ClearTransQueSocket(lpsmSock);
	}


	ClearPacketSendQue(lpsmSock);

	closesocket(lpsmSock->sock);
	lpsmSock->sock = 0;


	if(SecFlag) smLeaveCSectionSocket();

	return TRUE;
}


int RecordShutdownLOG(int LogCode, int LParam, int SParam)
{
	smTRANS_COMMAND smTransCommand;

	smTransCommand.WParam = LogCode;
	smTransCommand.LParam = LParam;
	smTransCommand.SParam = SParam;
	RecordHackLogFile(0, &smTransCommand);

	return TRUE;
}



DWORD dwTimeCounter = 0;

static LONG APIENTRY WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
	int cnt;
	DWORD dwOldTime;

	switch(messg)
	{
	case WM_CREATE:
		hMsgTextWnd = CreateWindow("EDIT", "",
			WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_LEFT | ES_MULTILINE | ES_READONLY,
			8, 8,
			350 - 32, 350 - 75,
			hWnd, (HMENU)ID_MESSTEXT,
			hInst, NULL);

		ShowWindow(hMsgTextWnd, SW_SHOW);


		wsprintf(szMessageBuff, "Sistema inicializando ( %d )", CONNECTMAX);


		SetWindowText(hMsgTextWnd, szMessageBuff);


		InitializeCriticalSection(&cSerSection);
		InitializeCriticalSection(&cOdbcSection);

		break;

	case WSA_ACCEPT:
		cnt = WSAMessage_Accept(wParam, lParam);
		if(cnt != TRUE)
		{

			srAcceptErrorCount++;
			srLastAcceptRsult = cnt;
		}
		break;

	case WSA_READ:
		WSAMessage_Read(wParam, lParam);
		WSA_RecvMsgCount++;
		break;

	case SWM_SENDSUCCESS:
		break;

	case SWM_RECVSUCCESS:

		RecvMessage((smTHREADSOCK *)wParam);
		break;

	case WM_CLOSE:
		ShowWindow(hWnd, SW_HIDE);
		break;
	case WM_KEYDOWN:
		break;

	case WM_KEYUP:
		break;

	case WM_CHAR:
		break;

	case WM_LBUTTONDOWN:



		break;
	case WM_RBUTTONDOWN:
		break;

	case WM_DESTROY:
		TrayIconClose();
		WSACleanup();
		PostQuitMessage(0);
		break;

	case WM_TIMER:

		dwOldTime = dwPlayServTime;
		dwPlayServTime = GetCurrentTime();

		if(dwOldTime > 0xFFFF0000 && dwPlayServTime < 0xFFFF)
		{
			rsShutDown();

			RecordShutdownLOG(50000, dwOldTime, dwPlayServTime);
		}

		srPlayMain();

		if((dwTimeCounter & 0x1FF) == 0)
		{

			srRouteErrorCount = CheckLostTransThread();


			PlayerCount = 0;
			for(cnt = 0; cnt < CONNECTMAX; cnt++)
			{
				if(rsPlayInfo[cnt].lpsmSock)
				{
					PlayerCount++;
				}
			}

			DisplayMessage();
			EventMonsterTime();
			::time(&tServerTime);

			if((dwTimeCounter & 0xFFF) == 0)
			{
				bSql_RecordCurrency();
			}
		}



		if((dwTimeCounter & 0x7) == 0)
		{

			smCheckWaitMessage();


			if((dwTimeCounter & 0x3F) == 0)
			{
				rsTimeRecData();
			}
		}
		dwTimeCounter++;
		break;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case ID_START:
		case ID_STOP:





			break;

		case ID_CONFIG:
			rsRefreshConfig();
			break;

		case ID_RELOAD_LIST:
			EnterCriticalSection(&cSerSection);
			rsLoadCopiedItemList();
			LeaveCriticalSection(&cSerSection);
			break;

		case ID_QUIT:
			if(!Quit)
			{
				EnterCriticalSection(&cSerSection);
				rsSaveCastleInfo();
				LeaveCriticalSection(&cSerSection);
			}
			Quit = 1;
			break;

		case ID_SHUTDOWN:

			rsShutDown();
			DisplayMessage();
			EnableMenuItem(GetMenu(hWnd), ID_SHUTDOWN, MF_GRAYED);
			break;

		case ID_VIEW_SERVERINFOMATION:
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_SERVERINFOMATION, MF_CHECKED);
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_GAMEINFOMATION, MF_UNCHECKED);
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_CONFIGURATION, MF_UNCHECKED);
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_AREASERVER, MF_UNCHECKED);
			Svr_DisplayMode = 0;
			DisplayMessage();
			break;

		case ID_VIEW_GAMEINFOMATION:
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_SERVERINFOMATION, MF_UNCHECKED);
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_GAMEINFOMATION, MF_CHECKED);
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_CONFIGURATION, MF_UNCHECKED);
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_AREASERVER, MF_UNCHECKED);
			Svr_DisplayMode = 1;
			DisplayMessage();
			break;

		case ID_VIEW_CONFIGURATION:
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_SERVERINFOMATION, MF_UNCHECKED);
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_GAMEINFOMATION, MF_UNCHECKED);
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_CONFIGURATION, MF_CHECKED);
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_AREASERVER, MF_UNCHECKED);
			Svr_DisplayMode = 2;
			DisplayMessage();
			break;

		case ID_VIEW_AREASERVER:
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_SERVERINFOMATION, MF_UNCHECKED);
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_GAMEINFOMATION, MF_UNCHECKED);
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_CONFIGURATION, MF_UNCHECKED);
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_AREASERVER, MF_CHECKED);
			Svr_DisplayMode = 3;
			DisplayMessage();
			break;


		}
		break;


	case MYWM_NOTIFYICON:
		switch(lParam)
		{
		case WM_LBUTTONDBLCLK:
			ShowWindow(hWnd, SW_RESTORE);
			SetForegroundWindow(hWnd);
			break;
		case WM_RBUTTONDOWN:
			ShowWindow(hWnd, SW_HIDE);
			break;
		default:
			break;
		}
		break;

	case MYWM_USER_COUNT:

		return rsGetUserCounter(PlayerCount);

	default:
		return DefWindowProc(hWnd, messg, wParam, lParam);
		break;
	}
	return 0L;
}



INT WINAPI ServerWinMain(HINSTANCE hInst, HINSTANCE hPreInst, LPSTR lpCmdLine, INT nCmdShow)
{
	MSG Msg;

	SetupDefWindow(hInst, hPreInst, lpCmdLine, nCmdShow);

	bool done = false;

	while(!done)
	{
		if(PeekMessage(&Msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);

			if(Msg.message == WM_QUIT)
			{
				done = true;
			}

			if(Quit != 0)
			{
				done = true;
			}
		}
		else
		{
			WaitMessage();
		}
	}

	rsSaveCastleInfo();

	if(fpNetLog) fclose(fpNetLog);

	quit = 1;

	bSql_ServerExit();

	TrayIconClose();
	CloseBindSock();

	RemoveAll();



	return Msg.wParam;
}







void TrayIconCreat()
{
	NOTIFYICONDATA tnd;
	HICON hIcon;

	tnd.cbSize = sizeof(NOTIFYICONDATA);

	tnd.hWnd = hwnd;
	tnd.uID = 99;
	tnd.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;

	tnd.uCallbackMessage = MYWM_NOTIFYICON;

	hIcon = (HICON)LoadIcon(hInst, MAKEINTRESOURCE(IDI_SERVER_ICON));

	tnd.hIcon = hIcon;
	strcpy(tnd.szTip, "GothicPT");



	Shell_NotifyIcon(NIM_ADD, &tnd);


	if(hIcon)
		DestroyIcon(hIcon);

}

void TrayIconClose()
{


	NOTIFYICONDATA tnd;

	tnd.cbSize = sizeof(NOTIFYICONDATA);
	tnd.hWnd = hwnd;

	tnd.uID = 99;
	Shell_NotifyIcon(NIM_DELETE, &tnd);

}






















struct LOGACCOUNT_INFO
{
	rsPLAYINFO	*lpPlayInfo;
	DWORD		dwConnectCount;
	char		szID[ACCOUNT_SIZE];
	char		szPassword[PASSWORD_SIZE];
	char		szIP[16];
	int			Flag;

	LOGACCOUNT_INFO()
	{
		lpPlayInfo = nullptr;
		dwConnectCount = 0;
		memset(szID, 0, sizeof(szID));
		memset(szPassword, 0, sizeof(szPassword));
		memset(szIP, 0, sizeof(szIP));
		Flag = 0;
	}
};

LOGACCOUNT_INFO	aLogAccount;

HANDLE hLogAccountThread = 0;
DWORD dwLogAccountThreadId = 0;

#define URS_LOG_THREAD_MAX		4
HANDLE hUrsLogAccountThread[URS_LOG_THREAD_MAX];
DWORD dwUrsLogAccountThreadId[URS_LOG_THREAD_MAX];
DWORD	hUrsMutiThreadFlag = 0;

#define LOG_ACCOUNT_QUE_MAX		64
#define LOG_ACCOUNT_QUE_MASK	63


LOGACCOUNT_INFO	LogAccountQue[LOG_ACCOUNT_QUE_MAX * 2];
int	PushLogAccountQue = 0;
int	PopLogAccountQue = 0;


int rsGetLogOnQueCount()
{
	return PushLogAccountQue - PopLogAccountQue;
}


int PushLogAccount(rsPLAYINFO *lpPlayInfo, char *szID, char *szPassword, char *szIP)
{
	int cnt = PushLogAccountQue & LOG_ACCOUNT_QUE_MASK;
	int que = PushLogAccountQue - PopLogAccountQue;

	if(que >= LOG_ACCOUNT_QUE_MAX)
	{
		if(hUrsMutiThreadFlag)
		{
			for(cnt = 0; cnt < URS_LOG_THREAD_MAX; cnt++)
			{
				if(hUrsLogAccountThread[cnt])
					ResumeThread(hUrsLogAccountThread[cnt]);
			}
		}
		else
		{
			ResumeThread(hLogAccountThread);
		}
		return FALSE;
	}

	LogAccountQue[cnt].lpPlayInfo = lpPlayInfo;
	LogAccountQue[cnt].dwConnectCount = lpPlayInfo->dwConnectCount;
	strcpy_s(LogAccountQue[cnt].szID, szID);
	strcpy_s(LogAccountQue[cnt].szPassword, szPassword);
	strcpy_s(LogAccountQue[cnt].szIP, szIP);
	LogAccountQue[cnt].Flag = 0;

	PushLogAccountQue++;

	if(hUrsMutiThreadFlag)
	{
		for(cnt = 0; cnt < URS_LOG_THREAD_MAX; cnt++)
		{
			if(hUrsLogAccountThread[cnt])
				ResumeThread(hUrsLogAccountThread[cnt]);
		}
	}
	else
	{
		ResumeThread(hLogAccountThread);
	}

	return	TRUE;
}



LOGACCOUNT_INFO *PopLogAccount()
{
	int cnt;
	int que;

	cnt = PopLogAccountQue & LOG_ACCOUNT_QUE_MASK;
	que = PushLogAccountQue - PopLogAccountQue;
	if(que <= 0) return NULL;
	PopLogAccountQue++;

	return &LogAccountQue[cnt];
}



int		Th_Record_PCJungFlag = -1;
HANDLE	hRecord_PCJung_Thread = 0;

DWORD WINAPI RecordPCJung_Thread(void *pInfo)
{
	HANDLE	hThread;
	DWORD	dwTime;
	DWORD	dwLastTime;
	int cnt;
	JUNGIP	Record_PcJungIP;
	JUNGIP	Record_PcJungIP2;

	hThread = GetCurrentThread();
	dwTime = GetCurrentTime();
	dwLastTime = dwTime;

	while(1)
	{
		
		
		EnterCriticalSection(&cSerSection);

		Record_PcJungIP.IPCount = 0;
		Record_PcJungIP2.IPCount = 0;

		for(cnt = 0; cnt < CONNECTMAX; cnt++)
		{
			if(rsPlayInfo[cnt].lpsmSock && !rsPlayInfo[cnt].getAccount().empty() && rsPlayInfo[cnt].GpType == 1)
			{
				if(rsPlayInfo[cnt].GpCode == 0)
				{

					if(Record_PcJungIP.IPCount < JUNGIP_MAX)
					{
						Record_PcJungIP.IP[Record_PcJungIP.IPCount++] =
							rsPlayInfo[cnt].lpsmSock->acc_sin.sin_addr.S_un.S_addr;
					}
				}
				if(rsPlayInfo[cnt].GpCode == 1)
				{

					if(Record_PcJungIP2.IPCount < JUNGIP_MAX)
					{
						Record_PcJungIP2.IP[Record_PcJungIP2.IPCount++] =
							rsPlayInfo[cnt].lpsmSock->acc_sin.sin_addr.S_un.S_addr;
					}
				}
			}
		}
		LeaveCriticalSection(&cSerSection);

		if(Record_PcJungIP.IPCount)
		{
			b_IPRecord(rsServerConfig.szServerName, &Record_PcJungIP);
		}

		if(Record_PcJungIP2.IPCount)
		{
			b_IPRecordTime(rsServerConfig.szServerName, &Record_PcJungIP2);
		}
		

		Sleep(1000 * 60 * 2);
	}

	ExitThread(TRUE);
	return TRUE;
}



int OpenRecordPCJung_Thread()
{
	DWORD	dwRecordPCJungThreadID;

	if(!hRecord_PCJung_Thread)
	{
		hRecord_PCJung_Thread = CreateThread(NULL, 0, RecordPCJung_Thread, 0, 0, &dwRecordPCJungThreadID);
	}

	return TRUE;
}


DWORD WINAPI LogAccountThreadProc(void *pInfo)
{
	int val = 0;

	return val;
}



int rsLogAccount(rsPLAYINFO *lpPlayInfo, char *szID, char *szPassword)
{
	if(!hLogAccountThread)
	{
		hLogAccountThread = CreateThread(NULL, 0, LogAccountThreadProc, 0, 0, &dwLogAccountThreadId);
		SetThreadPriority(hLogAccountThread, THREAD_PRIORITY_ABOVE_NORMAL);

		CreateDataServerDirectory();

		LoginServer = TRUE;

		if(!rsBlessCastle.CastleMode) rsLoadCastleInfo();
	}

	if(!hLogAccountThread) return FALSE;


	if(lpPlayInfo->lpsmSock)
		return PushLogAccount(lpPlayInfo, szID, szPassword, lpPlayInfo->lpsmSock->szIPAddr);
	else
		return FALSE;
}



int rsSendServerList(smWINSOCK *lpsmSock, int ClanTicket)
{
	if(!TransServerList.ServerCount) return FALSE;

	if(!TransServerList.code)
	{
		TransServerList.code = OpCode::OPCODE_SERVER_INFO;
		TransServerList.size = sizeof(TRANS_SERVER_LIST) -
			(sizeof(_TRANS_SERVER_INFO)*(TRANS_SERVER_MAX - (TransServerList.ServerCount + TransServerList.ClanServerCount)));
	}

	TransServerList.dwServerTime_t = (DWORD)tServerTime;
	TransServerList.ClanTicket = ClanTicket;

	return lpsmSock->Send((char *)&TransServerList, TransServerList.size, TRUE);
}


int rsCheckChildServer(char *szIP)
{
	int cnt;

	for(cnt = 0; cnt < TransServerList.ServerCount; cnt++)
	{
		if(TransServerList.ServerInfo[cnt].szServerIp1[0])
		{
			if(lstrcmp(szIP, TransServerList.ServerInfo[cnt].szServerIp1) == 0)
				return TRUE;
		}
		if(TransServerList.ServerInfo[cnt].szServerIp2[0])
		{
			if(lstrcmp(szIP, TransServerList.ServerInfo[cnt].szServerIp2) == 0)
				return TRUE;
		}
		if(TransServerList.ServerInfo[cnt].szServerIp3[0])
		{
			if(lstrcmp(szIP, TransServerList.ServerInfo[cnt].szServerIp3) == 0)
				return TRUE;
		}
	}

	return FALSE;
}







#define		SERVER_DOWN_MIN			8

DWORD WINAPI ShutDownThreadProc(void *pInfo)
{




	int cnt;

	TRANS_CHATMESSAGE	TransChatMessage;
	smTRANS_COMMAND		smTransCommand;
	int	rsServerDownCount = 0;
	DWORD	dwShutDownTime = GetCurrentTime() + 60 * 1000 * SERVER_DOWN_MIN;

	DWORD	dwTime;
	int		Sec, Min;
	int		SleepTime;

	bSql_ServerDown();

	while(1)
	{
		if(Quit)
		{
			ExitThread(TRUE);
			return TRUE;
		}

		dwTime = GetCurrentTime();
		Sec = (dwShutDownTime - dwTime);
		Sec /= 1000;
		if(Sec < 0)
		{
			break;
		}

		Min = Sec / 60;
		Sec = Sec % 60;
		ShutDownLeftTime = Min;

		if(rsServerDownCount < SERVER_DOWN_MSG_COUNT)
		{
			strcpy_s(TransChatMessage.szMessage, szServerDownMsg[rsServerDownCount]);
			rsServerDownCount++;
			Sleep(500);
		}
		else
		{
			wsprintf(TransChatMessage.szMessage, szSeverDownCountMsg, Min, Sec);
			if(Min == 0)
				Sleep(1000 * 5);
			else
				Sleep(1000 * 30);
		}

		TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
		TransChatMessage.dwIP = 3;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		TransChatMessage.dwObjectSerial = 0;

		for(cnt = 0; cnt < CONNECTMAX; cnt++)
		{
			SleepTime = 0;
			EnterCriticalSection(&cSerSection);
			if(rsPlayInfo[cnt].lpsmSock)
			{
				rsPlayInfo[cnt].lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
				SleepTime = 5;
			}
			LeaveCriticalSection(&cSerSection);
			if(SleepTime > 0) Sleep(SleepTime);
			if(Quit)
			{
				ExitThread(TRUE);
				return TRUE;
			}
		}

	}

	for(cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		SleepTime = 0;
		EnterCriticalSection(&cSerSection);
		if(rsPlayInfo[cnt].lpsmSock)
		{

			smTransCommand.code = OpCode::OPCODE_CLOSECLIENT;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			rsPlayInfo[cnt].lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
			SleepTime = 5;
		}
		LeaveCriticalSection(&cSerSection);
		if(SleepTime > 0) Sleep(SleepTime);
		if(Quit)
		{
			ExitThread(TRUE);
			return TRUE;
		}
	}

	Sleep(1000 * 60);

	Quit = 1;



	ExitThread(TRUE);

	return TRUE;
}

HANDLE hShutDownThread = 0;
DWORD dwShutDownThreadId = 0;

int	rsShutDown()
{
	if(!hShutDownThread)
	{
		hShutDownThread = CreateThread(NULL, 0, ShutDownThreadProc, 0, 0, &dwShutDownThreadId);
		ShutDownFlag = TRUE;
		ShutDownLeftTime = SERVER_DOWN_MIN;

		RecordShutdownLOG(50010, 0, 0);
		return TRUE;
	}

	return FALSE;
}













#ifdef	_LANGUAGE_KOREAN
#include "serverlog.h"
#else
#include "e_serverlog.h"
#endif

int	rsSendTransCommand(rsPLAYINFO *lpPlayInfo, DWORD	dwCode, int WParam, int LParam, int SParam, int EParam)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = dwCode;
	smTransCommand.WParam = WParam;
	smTransCommand.LParam = LParam;
	smTransCommand.SParam = SParam;
	smTransCommand.EParam = EParam;

	if(lpPlayInfo && lpPlayInfo->lpsmSock)
	{
		return lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
	}

	return FALSE;
}


int RecordHackLogFile(rsPLAYINFO *lpPlayInfo, void *lpBuff)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];



	smTRANS_COMMAND_EX	*lpTransCommand = (smTRANS_COMMAND_EX *)lpBuff;

#ifndef	_NEW_ITEM_FORMCODE

	if(lpTransCommand->WParam == 6800)
	{

		return FALSE;
	}
#endif

#ifdef	_LANGUAGE_KOREAN
#ifndef _TEST_SERVER
	if(lpTransCommand->WParam == 7100)
	{

		return FALSE;
	}
#endif
#endif

	GetLocalTime(&st);
	wsprintf(szFileName, filenameHack, HackLogDirectory, st.wMonth, st.wDay);


	if(lpPlayInfo && lpPlayInfo->lpsmSock)
	{
		

		wsprintf(szBuff, "%d:%d:%d IP-( %s ) ID-( %s ) Name-( %s ) / ( %d ) - ( %d , %d )\r\n",
			st.wHour, st.wMinute, st.wSecond, lpPlayInfo->lpsmSock->szIPAddr, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
			lpTransCommand->WParam, lpTransCommand->LParam, lpTransCommand->SParam);
	}
	else
	{
		wsprintf(szBuff, "%d:%d:%d ( %d ) - ( %d , %d )\r\n", st.wHour, st.wMinute, st.wSecond, lpTransCommand->WParam, lpTransCommand->LParam, lpTransCommand->SParam);
	}



#ifdef _W_SERVER
	smTRANS_COMMAND	smTransCommand;

	if(lpPlayInfo && lpPlayInfo->lpsmSock)
	{
		switch(lpTransCommand->WParam)
		{
		case -1:
		{

			wsprintf(szBuff, "%d:%d:%d IP:[ %s ] ID:[ %s ] Name:[ %s ] / Param:[ %d ] - ( Power User Hacker [ %d ])\r\n",
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->lpsmSock->szIPAddr, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpTransCommand->WParam, lpTransCommand->LParam);
		}
		break;
		case 1000:
		{

			wsprintf(szBuff, msg1000,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam);


			if(!lpPlayInfo->BlockTime)
				lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 1000 * 60 * 18);

		}
		break;

		case 1010:
		{

			wsprintf(szBuff, msg1010,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam);
		}
		break;

		case 1011:
		{

			wsprintf(szBuff, msg1011,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam);
		}
		break;

		case 1100:
		{
			wsprintf(szBuff, msg1100,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, (char *)lpTransCommand->LParam);

			if(strstr((char *)lpTransCommand->LParam, "FPE") != 0)
			{
				lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 0x7FFFFFFF);

			}
			else
			{

				lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 1000 * 60 * 60);
			}

		}
		break;

		case 1101:
		{

			wsprintf(szBuff, msg1101,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->smCharInfo.szName,
				lpPlayInfo->lpsmSock->szIPAddr, (char *)lpTransCommand->LParam);

			if(strstr((char *)lpTransCommand->LParam, "FPE") != 0)
			{
				lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 1000 * 60 * 60 * 24);
			}
			else
			{

				lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 1000 * 60 * 60);
			}
		}
		break;

		case 1102:
		{

			wsprintf(szBuff, msg1102,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam);

			if(!lpPlayInfo->BlockTime)
				lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 1000 * 60 * 19);

		}
		break;

		case 1103:
		{

			wsprintf(szBuff, msg1103,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->SParam, lpTransCommand->LParam);
		}
		break;

		case 1110:
		{

			wsprintf(szBuff, msg1110,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->SParam, lpTransCommand->LParam);


			if(!lpPlayInfo->BlockTime)
				lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 1000 * 60 * 60 * 1);

		}
		break;

		case 1120:
		{

			wsprintf(szBuff, msg1120,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->SParam, lpTransCommand->LParam);



			lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 0x7FFFFFFF);


			DisconnectUser(lpPlayInfo->lpsmSock);
		}
		break;

		case 1130:
		{

			wsprintf(szBuff, msg1130,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);

			lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 0x7FFFFFFF);

			rsAddBlockUserFile(lpPlayInfo->getAccount().c_str(), szBuff);
		}
		break;

		case 1132:
		{

			wsprintf(szBuff, msg1132,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);

			if(!lpPlayInfo->BlockTime)
				lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 1000 * 60 * 60 * 24);
		}
		break;

		case 1150:
		{

			wsprintf(szBuff, msg1150,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->SParam, lpTransCommand->LParam);
		}
		break;

		case 1200:
		{

			wsprintf(szBuff, msg1200,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam);

			lpPlayInfo->CrackWarning = lpTransCommand->WParam;


			if(!lpPlayInfo->BlockTime)
				lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 1000 * 60 * 60 * 2);



			rsSendCloseClient(lpPlayInfo);

		}
		break;

		case 1250:
		{

			wsprintf(szBuff, msg1250,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);

			lpPlayInfo->CrackWarning = lpTransCommand->WParam;






			rsSendCloseClient(lpPlayInfo);


		}
		break;

		case 1400:
		{

			wsprintf(szBuff, msg1400,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->smCharInfo.szName,
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam);



		}
		break;

		case 1500:
		{

			wsprintf(szBuff, msg1500,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam);
		}
		break;

		case 1510:
		{

			wsprintf(szBuff, msg1510,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam);


			DisconnectUser(lpPlayInfo->lpsmSock);
		}
		break;

		case 1530:
		{
			wsprintf(szBuff, msg1530,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);

			if(rsServerConfig.Dis_PotionError)
			{

				if(!lpPlayInfo->BlockTime)
					lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), rsServerConfig.Dis_PotionError*(1000 * 60));

				lpPlayInfo->dwTime_Disconnect = 1;
				rsSendTransCommand(lpPlayInfo, OpCode::OPCODE_CLEARPOTION, 0, 0, 0, 0);
			}



		}
		break;

		case 1600:
		{
			wsprintf(szBuff, msg1600,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->smCharInfo.szName,
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam);


			if(!lpPlayInfo->BlockTime)
				lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 1000 * 60 * 60);

		}
		break;

		case 1800:
		{

			wsprintf(szBuff, msg1800,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->smCharInfo.szName,
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam);
		}
		break;

		case 1820:
		{

			wsprintf(szBuff, msg1820,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam);

			lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 0x7FFFFFFF);

			rsSendCloseClient(lpPlayInfo);
		}
		break;

		case 1821:
		{
			wsprintf(szBuff, msg1821,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam);

			lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 0x7FFFFFFF);

			rsSendCloseClient(lpPlayInfo);
		}
		break;

		case 1823:
		{
			wsprintf(szBuff, msg1823,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam);

			rsSendCloseClient(lpPlayInfo);
		}
		break;

		case 1830:
		{

			wsprintf(szBuff, msg1830,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->smCharInfo.szName,
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam);
		}
		break;

		case 1833:
		{

			wsprintf(szBuff, msg1833,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->smCharInfo.szName,
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam);
		}
		break;

		case 1840:
		{

			wsprintf(szBuff, msg1840,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);

			if(lpTransCommand->LParam == 9100)
			{

				rsSendCloseClient(lpPlayInfo);
			}
		}
		break;

		case 1900:
		{

			wsprintf(szBuff, msg1900,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->smCharInfo.szName,
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam);
		}
		break;

		case 1950:
		{

			wsprintf(szBuff, msg1950,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->smCharInfo.szName,
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam);
		}
		break;

		case 1960:
		{

			wsprintf(szBuff, msg1960,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);
		}
		break;

		case 2000:
		{

			wsprintf(szBuff, msg2000,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);
		}
		break;

		case 2100:
		{

			wsprintf(szBuff, msg2100,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);

			lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 0x7FFFFFFF);
		}break;
		case 2110:
		{

			wsprintf(szBuff, msg2110,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);
		}break;
		case 2120:
		{

			wsprintf(szBuff, msg2120,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		}break;
		case 2300:
		{

			wsprintf(szBuff, msg2300,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);
		}break;
		case 2400:
		{

			wsprintf(szBuff, msg2400,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);
		}break;
		case 2700:
		{

			wsprintf(szBuff, msg2700,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);
		}break;
		case 2800:
		{

			wsprintf(szBuff, msg2800,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		}break;
		case 4000:
		{
			wsprintf(szBuff, msg4000,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);
		}break;
		case 4100:
		{

			wsprintf(szBuff, msg4100,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);
		}break;
		case 5000:
		{

			wsprintf(szBuff, msg5000,
				st.wHour, st.wMinute, st.wSecond, lpTransCommand->LParam, lpTransCommand->SParam);
		}break;
		case 5100:
		{

			wsprintf(szBuff, msg5100,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->smCharInfo.szName,
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);
		}break;
		case 5200:
		{

			wsprintf(szBuff, msg5200,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->SParam, lpTransCommand->LParam);
		}break;
		case 6000:
		{

			wsprintf(szBuff, msg6000,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->SParam, lpTransCommand->LParam);


			lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 1000 * 60 * 60 * 1);

		}break;
		case 6100:
		{

			wsprintf(szBuff, msg6100,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);
		}break;
		case 6200:
		{

			wsprintf(szBuff, msg6200,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);


			if(lpPlayInfo->BlockTime < 1000 * 60 * 10)
				lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 1000 * 60 * 10);
		}break;
		case 6500:
		{

			wsprintf(szBuff, msg6500,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);

		}break;
		case 6510:
		{

			wsprintf(szBuff, msg6510,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);

		}break;
		case 6600:
		{

			wsprintf(szBuff, msg6600,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);



			lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 0x7FFFFFFF);
		}break;
		case 6610:
		{

			wsprintf(szBuff, msg6610,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);

		}break;
		case 6611:
		{

			wsprintf(szBuff, msg6611,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);


			if(!lpPlayInfo->BlockTime)
				lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 1000 * 60 * 30);
		}break;
		case 6612:
		{

			wsprintf(szBuff, msg6612,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);


			if(!lpPlayInfo->BlockTime)
				lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 1000 * 60 * 30);
		}break;
		case 6620:
		{

			wsprintf(szBuff, msg6620,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);


			if(!lpPlayInfo->BlockTime)
				lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 1000 * 60 * 60);
		}break;
		case 6630:
		{

			wsprintf(szBuff, msg6630,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		}break;
		case 6800:
		{

			wsprintf(szBuff, msg6800,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);

			if(rsServerConfig.ItemCodeOut > 0)
			{
				if((lpTransCommand->LParam&sinITEM_MASK1) < (sinPM1&sinITEM_MASK1))
				{
					lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 0x7FFFFFFF);
				}
				lpPlayInfo->dwTime_Disconnect = 1;
			}
		}break;
		case 6810:
		{

			wsprintf(szBuff, msg6810,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);

			if(rsServerConfig.ItemCodeOut > 1)
			{
				lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 1000 * 60 * 60 * 24);
				DisconnectUser(lpPlayInfo->lpsmSock);
			}
		}break;
		case 6900:
		{

			wsprintf(szBuff, msg6900,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);

			lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 0x7FFFFFFF);

		}break;
		case 6910:
		{

			wsprintf(szBuff, msg6910,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, (lpTransCommand->SParam & 0xFFFF), (lpTransCommand->SParam >> 16), lpTransCommand->EParam);
		}break;
		case 6920:
		{

			wsprintf(szBuff, msg6920,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);

		}break;
		case 7000:
		{

			wsprintf(szBuff, msg7000,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);


		}break;
		case 7010:
		{

			wsprintf(szBuff, msg7010,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);



			if(lpPlayInfo->getSecurity() > AccountTypes::SEC_VIP)
			{
				rsSendCloseClient(lpPlayInfo);
			}

		}break;
		case 7020:
		{

			wsprintf(szBuff, msg7020,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		}break;
		case 7030:
		{

			wsprintf(szBuff, msg7030,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		}break;
		case 7100:
		{

			wsprintf(szBuff, msg7100,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		}break;
		case 7110:
		{

			if(lpPlayInfo->WarningCount > 10 + (rand() % 10))
			{

				return FALSE;
			}

			wsprintf(szBuff, msg7110,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);


			lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 1000 * 60 * 60);
		}break;
		case 7120:
		{

			wsprintf(szBuff, msg7120,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);

			lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 0x7FFFFFFF);
			lpPlayInfo->dwHopeDisconnectTime = 30000;
		}break;
		case 7130:
		{

			wsprintf(szBuff, msg7130,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		}break;
		case 7140:
		{

			wsprintf(szBuff, msg7140,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->lpsmSock->szIPAddr);

			rsAddBackListID(lpPlayInfo->getAccount().c_str(), 1000 * 60 * 16);

			return FALSE;
		}break;
		case 7150:
		{

			wsprintf(szBuff, msg7150,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		}break;
		case 7160:
		{

			wsprintf(szBuff, msg7160,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		}break;
		case 8000:
		{

			wsprintf(szBuff, msg8000,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->WxParam, lpTransCommand->LxParam, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		}break;
		case 8010:
		{

			wsprintf(szBuff, msg8010,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		}break;
		case 8020:
		{

			wsprintf(szBuff, msg8020,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		}break;
		case 8030:
		{

			wsprintf(szBuff, msg8030,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		}break;
		case 8040:
		{

			if(lpPlayInfo->smCharInfo.Level >= 21)
			{
				rsSendCloseClient(lpPlayInfo);

#ifdef	_LANGUAGE_BRAZIL
				lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 0x7FFFFFFF);
				lpPlayInfo->dwHopeDisconnectTime = dwPlayServTime + 3 * 60 * 1000;
#endif
			}

			if(lpPlayInfo->WarningCount > 10) return FALSE;


			wsprintf(szBuff, msg8040,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);


		}break;
		case 8050:
		{

			wsprintf(szBuff, msg8050,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);




			if(lpPlayInfo->WarningCount > 2)
			{
				if(lpPlayInfo->WarningCount > 6)
				{
					rsSendCloseClient(lpPlayInfo);
				}
				else
				{

					rsSend_BadPlayerToGameServer(lpPlayInfo->lpsmSock, 1);
				}
			}

		}break;
		case 8060:
		{

			wsprintf(szBuff, msg8060,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		}break;
		case 8070:
		{

			wsprintf(szBuff, msg8070,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->WxParam, lpTransCommand->LxParam, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		}break;
		case 8080:
		{

			wsprintf(szBuff, msg8080,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		}break;
		case 8100:
		{

			wsprintf(szBuff, msg8100,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam);

			if(lpTransCommand->LParam >= 200 && lpPlayInfo->WarningCount > 4)
			{

				rsSend_BadPlayerToGameServer(lpPlayInfo->lpsmSock, 1);
			}

		}break;
		case 8102:
		{

			wsprintf(szBuff, msg8102,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		}break;
		case 8110:
		{

			wsprintf(szBuff, msg8110,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		}break;
		case 8120:
		{

			wsprintf(szBuff, msg8120,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		}break;
		case 8140:
		{

			wsprintf(szBuff, msg8140,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);
		}break;
		case 8200:
		{

			wsprintf(szBuff, msg8200,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		}break;
		case 8210:
		{

			wsprintf(szBuff, msg8210,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam, lpTransCommand->SxParam, lpTransCommand->ExParam);
		}break;
		case 8300:
		{

			wsprintf(szBuff, msg8300,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam);
		}break;
		case 8400:
		{

			wsprintf(szBuff, msg8400,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);
		}break;
		case 8500:
		{

			wsprintf(szBuff, msg8500,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		}break;
		case 8510:
		{

			wsprintf(szBuff, msg8510,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->WxParam,
				lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam,
				lpTransCommand->LxParam, lpTransCommand->SxParam, lpTransCommand->ExParam);
		}break;
		case 8520:
		{

			wsprintf(szBuff, msg8520,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam);
		}break;
		case 8530:
		{

			wsprintf(szBuff, msg8530,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam);
		}break;
		case 8540:
		{

			wsprintf(szBuff, msg8540,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);

			DisconnectUser(lpPlayInfo->lpsmSock);
		}break;
		case 8550:
		{

			if(lpPlayInfo->WarningCount > 30) return FALSE;


			wsprintf(szBuff, msg8550,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);


		}break;
		case 8560:
		{

			wsprintf(szBuff, msg8560,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);

		}break;
		case 8570:
		{

			wsprintf(szBuff, msg8570,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);

			rsSendCloseClient(lpPlayInfo);
		}break;
		case 8580:
		{

			wsprintf(szBuff, msg8580,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);

			rsSendCloseClient(lpPlayInfo);
		}break;
		case 8600:
		{

			if(lpPlayInfo->WarningCount > 20 + (rand() % 10))
			{

				return FALSE;
			}

			wsprintf(szBuff, msg8600,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);
		}break;
		case 8700:
		{

			wsprintf(szBuff, msg8700,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);
		}break;
		case 8710:
		{

			wsprintf(szBuff, msg8710,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);
		}break;
		case 8720:
		{

			wsprintf(szBuff, msg8720,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);
		}break;
		case 8730:
		{

			wsprintf(szBuff, msg8730,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);
		}break;
		case 8800:
		{

			wsprintf(szBuff, msg8800,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		}break;
		case 8810:
		{

			wsprintf(szBuff, msg8810,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		}break;
		case 8820:
		{

			wsprintf(szBuff, msg8820,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);

		}break;
		case 8830:
		{

			wsprintf(szBuff, msg8830,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);

		}break;
		case 8840:
		{

			wsprintf(szBuff, msg8840,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->WxParam, lpTransCommand->LxParam, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		}break;
		case 8850:
		{

			wsprintf(szBuff, msg8850,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);
		}break;
		case 8860:
		{

			wsprintf(szBuff, msg8860,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->WxParam, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam, lpTransCommand->LxParam);
		}break;
		case 8870:
		{

			wsprintf(szBuff, msg8870,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
		}break;
		case 8880:
		{

			wsprintf(szBuff, msg8880,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);

			rsSendCloseClient(lpPlayInfo);
		}break;
		case 8890:
		{

			wsprintf(szBuff, msg8890,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);

			lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 0x7FFFFFFF);
		}break;
		case 8900:
		{

			wsprintf(szBuff, msg8900,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);
		}break;
#ifdef _CHECK_MESH
		case 8910:
		{

			wsprintf(szBuff, msg8910,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szID, lpPlayInfo->szName,
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);
		}break;
#endif
		case 99000:
		{


			wsprintf(szBuff, "%d:%d:%d - ID:( %s ) / Name:( %s ) / IP ( %s ) Item Mixing Error ( %d )( %d )\r\n",
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);


		}break;
		case 10000:
		{

			wsprintf(szBuff, msg10000,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->SParam, lpTransCommand->LParam);
		}break;
		case 10001:
		{

			wsprintf(szBuff, msg10001,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->SParam, lpTransCommand->LParam);
		}break;
		case 10002:
		{

			wsprintf(szBuff, msg10002,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->SParam, lpTransCommand->LParam);
		}break;
		case 10003:
		{

			wsprintf(szBuff, msg10003,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->SParam, lpTransCommand->LParam);
		}break;
		case 10005:
		{

			wsprintf(szBuff, msg10005,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->SParam, lpTransCommand->LParam);
		}break;
		case 10006:
		{

			wsprintf(szBuff, msg10006,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->SParam, lpTransCommand->LParam);
		}break;
		case 10007:
		{

			wsprintf(szBuff, msg10007,
				st.wHour, st.wMinute, st.wSecond,
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->SParam, lpTransCommand->LParam);
		}break;
		case 10010:
		{

			wsprintf(szBuff, msg10010,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam);
		}break;
		case 10020:
		{

			wsprintf(szBuff, msg10020,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);
		}break;
		case 11000:
		{

			wsprintf(szBuff, msg11000,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr);
		}
		break;
		case 21000:
		{

			wsprintf(szBuff, msg21000,
				st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
				lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->LParam, lpTransCommand->SParam);
		}
		break;
		}

		if(lpTransCommand->WParam < 1000)
		{

			char szTemp[256];
			wsprintf(szTemp, "logfile [ %d %d %d %d ]\r\n",
				lpTransCommand->WParam, lpTransCommand->LParam, lpTransCommand->SParam, lpTransCommand->EParam);
			Record_TempLogFile(szTemp);


			if(LoginServer)
			{
				wsprintf(szTemp, "DebugLog - LastMsg( %d ) LastUserID( %s ) LastUserName( %s ) DebugCount( %d )\r\n",
					dwServer_DebugMessage, szServer_DebugLastUserID, szServer_DebugLastUserName, Server_DebugCount);
			}
			Record_TempLogFile(szTemp);




			if(lpTransCommand->WParam != 100)
			{

				wsprintf(szBuff, msgHack,
					st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
					lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->WParam);

				if(lpTransCommand->WParam == 82 || lpTransCommand->WParam == 83 || lpTransCommand->WParam == 5)
				{
					lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 0x7FFFFFFF);
					lpPlayInfo->dwHopeDisconnectTime = 2000;
				}
				if(lpTransCommand->WParam == 55 || lpTransCommand->WParam == 54)
				{
					if(lpPlayInfo->getSecurity() >= AccountTypes::SEC_MODERATOR) return FALSE;
					if(lpPlayInfo->WarningCount > 12 && !lpPlayInfo->dwHopeDisconnectTime)
						lpPlayInfo->dwHopeDisconnectTime = 2000;
				}
			}
			else
			{

				wsprintf(szBuff, msgHack100,
					st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
					lpPlayInfo->lpsmSock->szIPAddr, lpTransCommand->WParam, lpTransCommand->SParam, lpTransCommand->LParam, lpTransCommand->EParam);

				if(lpPlayInfo->BlockTime && lpTransCommand->LParam >= 140)
				{
					lpPlayInfo->BadPlayer = 2;

					smTransCommand.code = OpCode::OPCODE_BAD_PLAYER;
					smTransCommand.size = sizeof(smTRANS_COMMAND);
					smTransCommand.WParam = 2;
					smTransCommand.LParam = 0;
					smTransCommand.SParam = 0;
					smTransCommand.EParam = 0;

					if(lpPlayInfo->lpsmSock)
						rsSendGameServer(lpPlayInfo->lpsmSock, &smTransCommand);
				}
			}




			if(!lpPlayInfo->BlockTime && lpTransCommand->WParam != 99)
				lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 1000 * 60 * 21);

			Record_TempLogFile(szBuff);
			Record_TempLogFile(szFileName);
			Record_TempLogFile(HackLogDirectory);

		}

	}

	if(lpTransCommand->WParam == 50000)
	{

		wsprintf(szBuff, "%d:%d:%d >**** Timer Overflow **** - ( %d / %d )\r\n",
			st.wHour, st.wMinute, st.wSecond, lpTransCommand->LParam, lpTransCommand->SParam);
	}
	if(lpTransCommand->WParam == 50010)
	{

		wsprintf(szBuff, "%d:%d:%d >**** Shutdown Service **** - ( %d / %d )\r\n",
			st.wHour, st.wMinute, st.wSecond, lpTransCommand->LParam, lpTransCommand->SParam);
	}
	if(lpTransCommand->WParam == 50020)
	{

		wsprintf(szBuff, "%d:%d:%d >**** Starting Service **** - ( %d / %d )\r\n",
			st.wHour, st.wMinute, st.wSecond, lpTransCommand->LParam, lpTransCommand->SParam);
	}
	if(lpTransCommand->WParam == 50030)
	{

		wsprintf(szBuff, "%d:%d:%d >**** Closed Service **** - ( %d / %d )\r\n",
			st.wHour, st.wMinute, st.wSecond, lpTransCommand->LParam, lpTransCommand->SParam);
	}


#endif

	CreateDirectory(HackLogDirectory, NULL);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	if(lpPlayInfo) lpPlayInfo->WarningCount++;

	return TRUE;
}


int RecordDebugPlayLogFile(rsPLAYINFO *lpPlayInfo)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if(!lpPlayInfo->lpsmSock) return FALSE;

	GetLocalTime(&st);
	wsprintf(szFileName, filenameDebugLogin, DebugLogDirectory, st.wMonth, st.wDay);

	if(!lpPlayInfo->getAccount().empty())
	{
		wsprintf(szBuff, msgDebugloginID,
			st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
			lpPlayInfo->lpsmSock->szIPAddr, (int)lpPlayInfo->getSecurity());
	}
	else
	{
		wsprintf(szBuff, msgDebugloginIP,
			st.wHour, st.wMinute, st.wSecond, lpPlayInfo->smCharInfo.szName,
			lpPlayInfo->lpsmSock->szIPAddr, (int)lpPlayInfo->getSecurity());
	}

	CreateDirectory(DebugLogDirectory, NULL);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}



int RecordJobChanger(rsPLAYINFO *lpPlayInfo)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if(!lpPlayInfo->lpsmSock) return FALSE;

	GetLocalTime(&st);
	wsprintf(szFileName, "LogFile\\(전업)%d월%d일.log", st.wMonth, st.wDay);

	wsprintf(szBuff, "ID( %s ) Name( %s ) IP( %s ) - 직업( %d )/전업( %d )/레벨( %d )\r\n",
		lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(), lpPlayInfo->lpsmSock->szIPAddr,
		lpPlayInfo->smCharInfo.JOB_CODE, lpPlayInfo->smCharInfo.ChangeJob, lpPlayInfo->smCharInfo.Level);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}


int Record_TempLogFile(char *szMessage)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	int len;
	char	szFileName[128];
	char	szBuff[256];

	GetLocalTime(&st);
	wsprintf(szFileName, "LogFile\\(Temp)%d-%d.log", st.wMonth, st.wDay);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE) return FALSE;


	wsprintf(szBuff, "%d:%d:%d - %s", st.wHour, st.wMinute, st.wSecond, szMessage);
	len = lstrlen(szBuff);
	if(szBuff[len - 1] != '\n')
	{
		szBuff[len] = '\r';
		szBuff[len + 1] = '\n';
		len += 2;
	}

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, len, &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}


int Record_BillingLogFile(rsPLAYINFO *lpPlayInfo, DWORD wParam, DWORD lParam, DWORD sParam, DWORD eParam)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if(!lpPlayInfo || !lpPlayInfo->lpsmSock) return FALSE;

	GetLocalTime(&st);
	wsprintf(szFileName, "LogFile\\(Billing)%d-%d.log", st.wMonth, st.wDay);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE) return FALSE;

	wsprintf(szBuff, "%d:%d:%d - ID( %s ) Name( %s ) IP( %s ) - DisuseDay(%d) dwPeriodTime(%d) tTime(%d) PcUse(%d)\r\n", st.wHour, st.wMinute, st.wSecond,
		lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(), lpPlayInfo->lpsmSock->szIPAddr, wParam, lParam, sParam, eParam);

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}


int Record_DeadUser(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if(!lpPlayInfo->lpsmSock || lpPlayInfo->smCharInfo.Level < 30) return FALSE;

	GetLocalTime(&st);
#ifdef _LANGUAGE_KOREAN
	wsprintf(szFileName, "LogFile\\(Death)%d월%d일.log", st.wMonth, st.wDay);
#else
	wsprintf(szFileName, "LogFile\\(Death)%d-%d.log", st.wMonth, st.wDay);
#endif

	wsprintf(szBuff, "%d:%d:%d - ID( %s ) Name( %s ) IP( %s ) - Level( %d )/Area( %d )\r\n",
		st.wHour, st.wMinute, st.wSecond,
		lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(), lpPlayInfo->lpsmSock->szIPAddr,
		lpPlayInfo->smCharInfo.Level, lpPlayInfo->Position.Area);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}



int RecordMixItem(rsPLAYINFO *lpPlayInfo, sITEMINFO *lpSrcItem, sITEMINFO *lpMixItem)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if(!lpPlayInfo->lpsmSock) return FALSE;

	GetLocalTime(&st);
	wsprintf(szFileName, filenameMixItem, HackLogDirectory, st.wMonth, st.wDay);

	wsprintf(szBuff, msgMixItem,
		st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
		lpPlayInfo->lpsmSock->szIPAddr, lpSrcItem->ItemName,
		lpSrcItem->ItemHeader.Head, lpSrcItem->ItemHeader.dwChkSum, lpSrcItem->ItemHeader.dwTime,
		lpMixItem->ItemHeader.Head, lpMixItem->ItemHeader.dwChkSum, lpMixItem->ItemHeader.dwTime);



	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}


int RecordAgingItem(rsPLAYINFO *lpPlayInfo, sITEMINFO *lpSrcItem, sITEMINFO *lpMixItem, int Mode)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];
	char	*lpMsg;

	if(!lpPlayInfo->lpsmSock) return FALSE;

	GetLocalTime(&st);
	wsprintf(szFileName, filenameAgingItem, HackLogDirectory, st.wMonth, st.wDay);

	if(lpMixItem)
	{
		if(!Mode) lpMsg = msgAgingItem;
		else lpMsg = msgAgingUpItem;

		wsprintf(szBuff, lpMsg,
			st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
			lpPlayInfo->lpsmSock->szIPAddr, lpSrcItem->ItemName, lpMixItem->ItemAgingNum[0],
			lpSrcItem->ItemHeader.Head, lpSrcItem->ItemHeader.dwChkSum, lpSrcItem->ItemHeader.dwTime,
			lpMixItem->ItemHeader.Head, lpMixItem->ItemHeader.dwChkSum, lpMixItem->ItemHeader.dwTime);

	}
	else
	{
		wsprintf(szBuff, msgAgingFailItem,
			st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
			lpPlayInfo->lpsmSock->szIPAddr, lpSrcItem->ItemName, lpSrcItem->ItemAgingNum[0],
			lpSrcItem->ItemHeader.Head, lpSrcItem->ItemHeader.dwChkSum, lpSrcItem->ItemHeader.dwTime);
	}



	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}


char *szRecordCollectDirectory = "CollMoney";


int RecordCollectMoney(rsPLAYINFO *lpPlayInfo, int Money)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];
	int		TotalMoney = 0;
	FILE	*fp;

	CreateDirectory(szRecordCollectDirectory, NULL);
	GetLocalTime(&st);

	wsprintf(szFileName, filenameCollectMoney, szRecordCollectDirectory, st.wMonth, st.wDay);


	fp = fopen(szFileName, "rb");
	if(fp)
	{
		fread(szBuff, 256, 1, fp);
		fclose(fp);
		TotalMoney = atoi(szBuff);
	}

	TotalMoney += Money;


	fp = fopen(szFileName, "wb");
	if(fp)
	{
		wsprintf(szBuff, "%d", TotalMoney);
		fwrite(szBuff, lstrlen(szBuff) + 1, 1, fp);
		fclose(fp);
	}

	wsprintf(szFileName, filenameCollectMoney, szRecordCollectDirectory, st.wMonth, st.wDay);

	wsprintf(szBuff, msgKindPeople,
		st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
		lpPlayInfo->lpsmSock->szIPAddr, Money, TotalMoney);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}



int RecordHackLogMoney(smCHAR_INFO *lpCharInfo)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];


	if(!lpCharInfo) return FALSE;

	GetLocalTime(&st);
	wsprintf(szFileName, filenameHackLogMoney, HackLogDirectory, st.wMonth, st.wDay);

	CreateDirectory(HackLogDirectory, NULL);

	wsprintf(szBuff, msgHackMoney,
		st.wHour, st.wMinute, st.wSecond,
		lpCharInfo->szName, lpCharInfo->Level, lpCharInfo->Money);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);


	return TRUE;


}


int RecordGetHighItem(rsPLAYINFO *lpPlayInfo, STG_ITEMS *lpStgItem)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if(!lpPlayInfo || !lpStgItem) return FALSE;
	if(!lpStgItem->BeginMode) return FALSE;

	GetLocalTime(&st);
	wsprintf(szFileName, filenameGetHighItem, HackLogDirectory, st.wMonth, st.wDay);

	CreateDirectory(HackLogDirectory, NULL);

	wsprintf(szBuff, msgHighItem,
		st.wHour, st.wMinute, st.wSecond,
		lpPlayInfo->smCharInfo.szName, lpPlayInfo->smCharInfo.Level,
		lpStgItem->Item.ItemInfo.ItemName,
		lpStgItem->Item.ItemInfo.CODE,
		lpStgItem->Item.ItemInfo.ItemHeader.Head,
		lpStgItem->Item.ItemInfo.ItemHeader.dwChkSum,
		lpStgItem->Item.ItemInfo.JobCodeMask,
		lpStgItem->BeginMode);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}




int RecordDeleteCharacter(const char *szID, char *szIP, smCHAR_INFO *lpCharInfo)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if(!szID || !szIP || !lpCharInfo) return FALSE;

	GetLocalTime(&st);
	wsprintf(szFileName, filenameDeleteCharacter, LogDirectory, st.wMonth, st.wDay);

	CreateDirectory(LogDirectory, NULL);

	wsprintf(szBuff, msgCharDelete1,
		st.wHour, st.wMinute, st.wSecond,
		szID, lpCharInfo->szName, szIP, lpCharInfo->Level,
		lpCharInfo->Exp, lpCharInfo->Money);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}


int RecordDeleteCharacterError(const char *szID, char *szName)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	GetLocalTime(&st);
	wsprintf(szFileName, filenameDeleteCharactererror, LogDirectory, st.wMonth, st.wDay);

	CreateDirectory(LogDirectory, NULL);

	wsprintf(szBuff, msgCharDelete2,
		st.wHour, st.wMinute, st.wSecond,
		szID, szName);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}




int RecordBlackUser(const char *szID, DWORD dwTime)
{
#ifdef _W_SERVER

	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if(!szID) return FALSE;


	GetLocalTime(&st);
	wsprintf(szFileName, filenameBlackUser, LogDirectory, st.wMonth, st.wDay);

	CreateDirectory(LogDirectory, NULL);

	wsprintf(szBuff, msgBlackUser,
		st.wHour, st.wMinute, st.wSecond,
		szID, dwTime / (1000 * 60));

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

#endif

	return TRUE;
}


int RecordSmeltingItem(rsPLAYINFO *lpPlayInfo, sITEMINFO *lpSmeltingItem)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if(!lpPlayInfo->lpsmSock)
	{
		return FALSE;
	}

	GetLocalTime(&st);
	wsprintf(szFileName, filenameSmeltingItem, HackLogDirectory, st.wMonth, st.wDay);

	wsprintf(szBuff, msgSmeltingItem,
		st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
		lpPlayInfo->lpsmSock->szIPAddr, lpSmeltingItem->ItemName,
		lpSmeltingItem->ItemHeader.Head, lpSmeltingItem->ItemHeader.dwChkSum, lpSmeltingItem->ItemHeader.dwTime);


	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

int RecordManufactureItem(rsPLAYINFO *lpPlayInfo, sITEMINFO *lpManufactureItem)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if(!lpPlayInfo->lpsmSock)
	{
		return FALSE;
	}

	GetLocalTime(&st);
	wsprintf(szFileName, filenameManufactureItem, HackLogDirectory, st.wMonth, st.wDay);

	wsprintf(szBuff, msgManufactureItem,
		st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
		lpPlayInfo->lpsmSock->szIPAddr, lpManufactureItem->ItemName,
		lpManufactureItem->ItemHeader.Head, lpManufactureItem->ItemHeader.dwChkSum, lpManufactureItem->ItemHeader.dwTime);


	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}


int RecordMixtureResetItem(rsPLAYINFO *lpPlayInfo, sITEMINFO *lpMixtureResetItem)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if(!lpPlayInfo->lpsmSock)
	{
		return FALSE;
	}

	GetLocalTime(&st);
	wsprintf(szFileName, filenameMixtureResetItem, HackLogDirectory, st.wMonth, st.wDay);

	wsprintf(szBuff, msgMixtureResetItem,
		st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(),
		lpPlayInfo->lpsmSock->szIPAddr, lpMixtureResetItem->ItemName,
		lpMixtureResetItem->ItemHeader.Head, lpMixtureResetItem->ItemHeader.dwChkSum, lpMixtureResetItem->ItemHeader.dwTime);


	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}



int RecordMovieBloodyBattleItem(rsPLAYINFO *lpPlayInfo, sITEMINFO *lpMovieBloodyBattleItem)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if(!lpPlayInfo->lpsmSock)
	{
		return FALSE;
	}

	CreateDirectory(EventLogDirectory, NULL);

	GetLocalTime(&st);
	wsprintf(szFileName, filenameMovieBloodyBattleItem, EventLogDirectory, st.wMonth, st.wDay);

	wsprintf(szBuff, MovieBloodyBattleLog,
		st.wHour, st.wMinute, st.wSecond, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str());


	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

#ifdef _W_SERVER
char	*szBlackUserDir = "BlackUser";
char	*szEverBlockDir = "BlockUser";
#else
char	*szBlackUserDir = "WhiteBird";
char	*szEverBlockDir = "StoneBird";
#endif




int rsAddBlockUserFile(const char *szID, char *szLog)
{
	char szBuff[256];
	FILE *fp;

	if(!rsServerConfig.ForeverBlockMode)	return FALSE;

	CreateDirectory(szEverBlockDir, NULL);

	wsprintf(szBuff, "%s\\%s.fev", szEverBlockDir, szID);


	fp = fopen(szBuff, "wb");
	if(fp)
	{
		fwrite(szLog, lstrlen(szLog), 1, fp);
		fclose(fp);
	}

	return TRUE;
}


int	rsCheckBlockUserFile(char *szID)
{

	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;
	char szBuff[256];

	wsprintf(szBuff, "%s\\%s.fev", szEverBlockDir, szID);


	hFindHandle = FindFirstFile(szBuff, &fd);
	if(hFindHandle == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	FindClose(hFindHandle);
	return TRUE;
}




int ResetBlackUserFiles()
{

	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;
	char szBuff[256];

	wsprintf(szBuff, "%s\\*.bur", szBlackUserDir);
	CreateDirectory(szBlackUserDir, NULL);


	hFindHandle = FindFirstFile(szBuff, &fd);
	if(hFindHandle == INVALID_HANDLE_VALUE)
	{
		FindClose(hFindHandle);
		return 0;
	}
	while(1)
	{
		wsprintf(szBuff, "%s\\%s", szBlackUserDir, fd.cFileName);
		DeleteFile(szBuff);
		if(FindNextFile(hFindHandle, &fd) == FALSE) break;
	}
	FindClose(hFindHandle);


	return TRUE;
}


int ResetBlackUserFiles(const char *szID, DWORD dwTime)
{
	char szBuff[256];
	char szBuff2[256];
	FILE *fp;
	SYSTEMTIME	st;


	wsprintf(szBuff, "%s\\%s.bur", szBlackUserDir, szID);

	if(dwTime)
	{

		GetLocalTime(&st);
		wsprintf(szBuff2, msgBlackUser, st.wHour, st.wMinute, st.wSecond, szID, dwTime / (1000 * 60));
		fp = fopen(szBuff, "wb");
		if(fp)
		{
			fwrite(szBuff2, lstrlen(szBuff2), 1, fp);
			fclose(fp);
		}
	}
	else
	{

		DeleteFile(szBuff);
	}

	return TRUE;
}


int FindBlackUserFile(char *szID)
{

	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;
	char szBuff[256];

	wsprintf(szBuff, "%s\\%s.bur", szBlackUserDir, szID);


	hFindHandle = FindFirstFile(szBuff, &fd);

	if(hFindHandle == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	FindClose(hFindHandle);
	return TRUE;
}

int rsCompareCharInfo(smCHAR_INFO *cSrc, smCHAR_INFO *cDest)
{








	return TRUE;
}

struct	srBLACK_LIST
{
	char	szID[ACCOUNT_SIZE];
	DWORD	dwFreeTime;
};

#define	srBLACK_LIST_MAX	400


srBLACK_LIST	srBlackList[srBLACK_LIST_MAX];
int	rsBlackListInit = 0;


int rsAddBackListID(const char *szID, DWORD dwTime)
{
	int cnt;
	DWORD	dwBloackTime;
	DWORD	dwFreeTime;

	if(!szID[0]) return FALSE;

	if(!rsBlackListInit)
	{

		rsResetBackList();
	}

	dwBloackTime = dwTime;

	if(rsServerConfig.BlockLevel > 0)
	{
		dwBloackTime = dwTime / rsServerConfig.BlockLevel;
	}
	if(rsServerConfig.BlockLevel < 0)
	{
		dwBloackTime = dwTime * abs(rsServerConfig.BlockLevel);
	}

	if(rsServerConfig.BlockLevel_LogOut)
		return dwBloackTime;


	dwFreeTime = dwPlayServTime + dwBloackTime;
	if(dwFreeTime < dwPlayServTime) dwFreeTime = 0xFFFFFFFF;

	RecordBlackUser(szID, dwBloackTime);

	for(cnt = 0; cnt < srBLACK_LIST_MAX; cnt++)
	{
		if(srBlackList[cnt].szID[0] && lstrcmpi(srBlackList[cnt].szID, szID) == 0)
		{
			if(srBlackList[cnt].dwFreeTime < dwFreeTime)
			{
				srBlackList[cnt].dwFreeTime = dwFreeTime;


				ResetBlackUserFiles(szID, dwBloackTime);
			}
			return dwBloackTime;
		}
	}


	for(cnt = 0; cnt < srBLACK_LIST_MAX; cnt++)
	{
		if(!srBlackList[cnt].szID[0])
		{
			strcpy_s(srBlackList[cnt].szID, szID);
			srBlackList[cnt].dwFreeTime = dwFreeTime;


			ResetBlackUserFiles(szID, dwBloackTime);

			return dwBloackTime;
		}
	}


	return FALSE;
}


DWORD rsCheckBackListID(char *szID)
{
	int cnt;

	for(cnt = 0; cnt < srBLACK_LIST_MAX; cnt++)
	{

		if(srBlackList[cnt].szID[0])
		{
			if(srBlackList[cnt].dwFreeTime < dwPlayServTime)
			{

				ResetBlackUserFiles(srBlackList[cnt].szID, 0);
				srBlackList[cnt].dwFreeTime = 0;
				srBlackList[cnt].szID[0] = 0;
			}
			else
			{
				if(lstrcmpi(srBlackList[cnt].szID, szID) == 0)
				{



					if(FindBlackUserFile(szID) == TRUE)
					{
						return srBlackList[cnt].dwFreeTime;
					}


					srBlackList[cnt].dwFreeTime = 0;
					srBlackList[cnt].szID[0] = 0;
					break;
				}
			}
		}
	}


	return NULL;
}


int rsFreekBackListID(char *szID)
{
	int cnt;

	for(cnt = 0; cnt < srBLACK_LIST_MAX; cnt++)
	{
		if(srBlackList[cnt].szID[0] && lstrcmpi(srBlackList[cnt].szID, szID) == 0)
		{

			ResetBlackUserFiles(srBlackList[cnt].szID, 0);

			srBlackList[cnt].dwFreeTime = 0;
			srBlackList[cnt].szID[0] = 0;
			return TRUE;
		}
	}

	return FALSE;
}


int rsResetBackList()
{
	int cnt;

	for(cnt = 0; cnt < srBLACK_LIST_MAX; cnt++)
	{
		srBlackList[cnt].dwFreeTime = 0;
		srBlackList[cnt].szID[0] = 0;
	}


	ResetBlackUserFiles();

	rsBlackListInit = TRUE;

	return TRUE;
}


int rsShowBlackList(smWINSOCK *lpsmSock, char *szID)
{
	TRANS_CHATMESSAGE	TransChatMessage;
	int cnt;
	int dcnt;

	TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
	TransChatMessage.dwIP = 0;
	TransChatMessage.dwObjectSerial = 0;

	dcnt = 0;

	for(cnt = 0; cnt < srBLACK_LIST_MAX; cnt++)
	{
		if(srBlackList[cnt].szID[0])
		{
			if(!szID[0] || lstrcmpi(szID, srBlackList[cnt].szID) == 0)
			{
				wsprintf(TransChatMessage.szMessage, "> ID ( %s ) / ( %d )Min.", srBlackList[cnt].szID, (srBlackList[cnt].dwFreeTime - dwPlayServTime) / 60000);
				TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
				lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
				dcnt++;
			}
		}
	}

	wsprintf(TransChatMessage.szMessage, "> Total %d Users", dcnt);
	TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
	lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);

	return TRUE;
}



DWORD SwapIPCode(DWORD dwIP)
{
	BYTE	bIP[4];

	bIP[0] = (BYTE)(dwIP & 0xFF);
	bIP[1] = (BYTE)((dwIP >> 8) & 0xFF);
	bIP[2] = (BYTE)((dwIP >> 16) & 0xFF);
	bIP[3] = (BYTE)((dwIP >> 24) & 0xFF);

	return (bIP[0] << 24) | (bIP[1] << 16) | (bIP[2] << 8) | (bIP[3]);
}


DWORD GetSwapIPCode(char *szIP)
{
	return SwapIPCode(inet_addr(szIP));
}


int	rsCheckDisableIP(DWORD dwUserIP)
{
	DWORD	dwIP;
	int		cnt;

	dwIP = SwapIPCode(dwUserIP);

	for(cnt = 0; cnt < rsServerConfig.DisableIP_Count; cnt++)
	{
		if(dwIP >= rsServerConfig.DisableIP[cnt][0] && dwIP <= rsServerConfig.DisableIP[cnt][1])
		{
			return TRUE;
		}
	}

	return FALSE;
}


int	rsCheckEnableIP(DWORD dwUserIP)
{
	DWORD	dwIP;
	int		cnt;

	dwIP = SwapIPCode(dwUserIP);

	for(cnt = 0; cnt < rsServerConfig.EnableIP_Count; cnt++)
	{
		if(dwIP >= rsServerConfig.EnableIP[cnt][0] && dwIP <= rsServerConfig.EnableIP[cnt][1])
		{
			return TRUE;
		}
	}

	return FALSE;
}


int	rsCheckAdminIP(DWORD dwUserIP)
{
	DWORD	dwIP;
	int		cnt;

	dwIP = SwapIPCode(dwUserIP);

	for(cnt = 0; cnt < rsServerConfig.AdminIP_Count; cnt++)
	{
		if(dwIP >= rsServerConfig.AdminIP[cnt][0] && dwIP <= rsServerConfig.AdminIP[cnt][1])
		{
			return TRUE;
		}
	}

	return FALSE;
}


int	rsCheckSystemIP(DWORD dwUserIP)
{

	return FALSE;
}


int	rsCheckLoginServerIP(DWORD dwUserIP)
{
	return FALSE;
}


int	rsRecord_ItemLOG(rsPLAYINFO *lpPlayInfo, DWORD dwItemCode, DWORD dwHead, DWORD dwChkSum, int Flag)
{
	LogITEM	LogItem;

	if(!lpPlayInfo->lpsmSock) return FALSE;

	ZeroMemory(&LogItem, sizeof(LogITEM));

	if(!rsServerConfig.TestSeverMode && (dwItemCode&sinITEM_MASK2) != sinGP1 &&
		(dwItemCode&sinITEM_MASK2) != sinQW1 && (dwItemCode&sinITEM_MASK2) != sinOR2 &&
		(dwItemCode&sinITEM_MASK2) != sinPZ1 && (dwItemCode&sinITEM_MASK2) != sinPZ2 &&
		(dwItemCode&sinITEM_MASK2) != sinSE1 && (dwItemCode&sinITEM_MASK2) != sinBI1 &&
		(dwItemCode&sinITEM_MASK2) != sinBI2 &&
		(dwItemCode&sinITEM_MASK2) != sinGF1 && (dwItemCode&sinITEM_MASK2) != sinBC1 &&

		(dwItemCode&sinITEM_MASK2) != sinPR1 && (dwItemCode&sinITEM_MASK2) != sinPR2 &&
		(dwItemCode&sinITEM_MASK2) != sinPR3 && (dwItemCode&sinITEM_MASK2) != sinPR4 &&
		(dwItemCode&sinITEM_MASK2) != sinWR1 && (dwItemCode&sinITEM_MASK2) != sinDR1 &&

		(dwItemCode&sinITEM_MASK2) != sinSP1)
	{

		if(dwItemCode == (sinGG1 | sin01))
		{

			if(dwHead < 10000) return FALSE;
		}
		else
		{
			if(dwItemCode >= sinPM1) return FALSE;
			if((dwItemCode&sinITEM_MASK2) == sinOS1 || (dwItemCode&sinITEM_MASK2) == sinFO1)
			{

				if((dwItemCode&sinITEM_MASK3) < sin05) return FALSE;
			}
			else
			{

				if((dwItemCode&sinITEM_MASK3) < sin07) return FALSE;
			}
		}
	}

	LogItem.Flag = Flag;
	strcpy_s(LogItem.UserID, lpPlayInfo->getAccount().c_str());
	strcpy_s(LogItem.CharName, lpPlayInfo->getName().c_str());
	LogItem.IP = lpPlayInfo->lpsmSock->acc_sin.sin_addr.S_un.S_addr;
	LogItem.Item[0].dwCode = dwItemCode;
	LogItem.Item[0].dwINo[0] = dwHead;
	LogItem.Item[0].dwINo[1] = dwChkSum;
	LogItem.ItemCount = 1;
	LogItem.size = sizeof(LogITEM) - (sizeof(_LogITEM)*(32 - LogItem.ItemCount));


	return b_PushLogItemQue(1, LogItem.size, &LogItem);
}


int	rsRecord_ItemLog2(rsPLAYINFO *lpPlayInfo, DWORD dwItemCode, DWORD	dwHead, DWORD dwChkSum, int Flag)
{
	LogITEM	LogItem;

	ZeroMemory(&LogItem, sizeof(LogITEM));

	if(!lpPlayInfo->lpsmSock) return FALSE;

	LogItem.Flag = Flag;
	strcpy_s(LogItem.UserID, lpPlayInfo->getAccount().c_str());
	strcpy_s(LogItem.CharName, lpPlayInfo->getName().c_str());
	LogItem.IP = lpPlayInfo->lpsmSock->acc_sin.sin_addr.S_un.S_addr;
	LogItem.Item[0].dwCode = dwItemCode;
	LogItem.Item[0].dwINo[0] = dwHead;
	LogItem.Item[0].dwINo[1] = dwChkSum;
	LogItem.ItemCount = 1;
	LogItem.size = sizeof(LogITEM) - (sizeof(_LogITEM)*(32 - LogItem.ItemCount));


	return b_PushLogItemQue(1, LogItem.size, &LogItem);
}



int	rsRecord_ItemLog_Change(rsPLAYINFO *lpPlayInfo, DWORD dwItemCode, DWORD	dwHead, DWORD dwChkSum,
	DWORD dwItemCode2, DWORD	dwHead2, DWORD dwChkSum2, int Flag)
{
	LogITEM	LogItem;

	ZeroMemory(&LogItem, sizeof(LogITEM));

	if(!lpPlayInfo->lpsmSock) return FALSE;

	LogItem.Flag = Flag;
	strcpy_s(LogItem.UserID, lpPlayInfo->getAccount().c_str());
	strcpy_s(LogItem.CharName, lpPlayInfo->getName().c_str());
	LogItem.IP = lpPlayInfo->lpsmSock->acc_sin.sin_addr.S_un.S_addr;

	LogItem.Item[0].dwCode = dwItemCode;
	LogItem.Item[0].dwINo[0] = dwHead;
	LogItem.Item[0].dwINo[1] = dwChkSum;

	LogItem.Item[1].dwCode = dwItemCode2;
	LogItem.Item[1].dwINo[0] = dwHead2;
	LogItem.Item[1].dwINo[1] = dwChkSum2;

	LogItem.ItemCount = 2;
	LogItem.size = sizeof(LogITEM) - (sizeof(_LogITEM)*(32 - LogItem.ItemCount));


	return b_PushLogItemQue(1, LogItem.size, &LogItem);
}


int	rsRecord_ItemLost(rsPLAYINFO *lpPlayInfo, DWORD *lpItemCode, DWORD *lpHead, DWORD *lpChkSum, int Flag)
{
	LogITEM	LogItem;
	int cnt;

	ZeroMemory(&LogItem, sizeof(LogITEM));

	if(!lpPlayInfo->lpsmSock) return FALSE;

	LogItem.Flag = Flag;
	strcpy_s(LogItem.UserID, lpPlayInfo->getAccount().c_str());
	strcpy_s(LogItem.CharName, lpPlayInfo->getName().c_str());
	LogItem.IP = lpPlayInfo->lpsmSock->acc_sin.sin_addr.S_un.S_addr;

	LogItem.ItemCount = 0;
	for(cnt = 0; cnt < 12; cnt++)
	{
		if(lpItemCode[cnt])
		{
			LogItem.Item[LogItem.ItemCount].dwCode = lpItemCode[cnt];
			LogItem.Item[LogItem.ItemCount].dwINo[0] = lpHead[cnt];
			LogItem.Item[LogItem.ItemCount].dwINo[1] = lpChkSum[cnt];
			LogItem.ItemCount++;
		}
	}

	if(LogItem.ItemCount == 0) return FALSE;

	LogItem.size = sizeof(LogITEM) - (sizeof(_LogITEM)*(32 - LogItem.ItemCount));


	return b_PushLogItemQue(1, LogItem.size, &LogItem);
}



int	rsRecord_ItemLog_Trade(rsPLAYINFO *lpPlayInfo, rsPLAYINFO *lpPlayInfo2, TRANS_TRADE_ITEMKEY *lpTransTradeItemKey)
{

	LogITEM_TRADE	LogItem;
	int cnt;

	ZeroMemory(&LogItem, sizeof(LogITEM_TRADE));

	if(!lpPlayInfo->lpsmSock) return FALSE;
	if(!lpPlayInfo2->lpsmSock) return FALSE;

	LogItem.Flag = 8;
	strcpy_s(LogItem.UserID, lpPlayInfo->getAccount().c_str());
	strcpy_s(LogItem.CharName, lpPlayInfo->getName().c_str());
	strcpy_s(LogItem.TUserID, lpPlayInfo2->getAccount().c_str());
	strcpy_s(LogItem.TCharName, lpPlayInfo2->getName().c_str());
	LogItem.IP = lpPlayInfo->lpsmSock->acc_sin.sin_addr.S_un.S_addr;
	LogItem.TIP = lpPlayInfo2->lpsmSock->acc_sin.sin_addr.S_un.S_addr;

	if(lpTransTradeItemKey->Money > 0)
		LogItem.Money = lpTransTradeItemKey->Money - 193;
	else
		LogItem.Money = 0;

	LogItem.ItemCount = 0;

	for(cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
	{
		if(lpTransTradeItemKey->dwItemCode[cnt])
		{
			LogItem.Item[LogItem.ItemCount].dwCode = lpTransTradeItemKey->dwItemCode[cnt];
			LogItem.Item[LogItem.ItemCount].dwINo[0] = lpTransTradeItemKey->dwItemKey[cnt];
			LogItem.Item[LogItem.ItemCount].dwINo[1] = lpTransTradeItemKey->dwItemSum[cnt];
			LogItem.ItemCount++;
		}
	}
	LogItem.size = sizeof(LogITEM_TRADE) - (sizeof(_LogITEM)*(32 - LogItem.ItemCount));


	return b_PushLogItemQue(2, LogItem.size, &LogItem);
}


int	rsRecord_ItemLog_MyShop(rsPLAYINFO *lpPlayInfo, rsPLAYINFO *lpPlayInfo2, DWORD dwItemCode, DWORD dwHead, DWORD dwChkSum, int Price)
{

	LogITEM_TRADE	LogItem;

	if(!lpPlayInfo->lpsmSock) return FALSE;
	if(!lpPlayInfo2->lpsmSock) return FALSE;

	ZeroMemory(&LogItem, sizeof(LogITEM_TRADE));
	LogItem.Flag = ITEMLOG_MYSHOP;
	strcpy_s(LogItem.UserID, lpPlayInfo->getAccount().c_str());
	strcpy_s(LogItem.CharName, lpPlayInfo->getName().c_str());
	strcpy_s(LogItem.TUserID, lpPlayInfo2->getAccount().c_str());
	strcpy_s(LogItem.TCharName, lpPlayInfo2->getName().c_str());
	LogItem.IP = lpPlayInfo->lpsmSock->acc_sin.sin_addr.S_un.S_addr;
	LogItem.TIP = lpPlayInfo2->lpsmSock->acc_sin.sin_addr.S_un.S_addr;

	LogItem.Money = Price;

	LogItem.size = sizeof(LogITEM_TRADE) - (sizeof(_LogITEM)*(32 - LogItem.ItemCount));


	b_PushLogItemQue(2, LogItem.size, &LogItem);


	ZeroMemory(&LogItem, sizeof(LogITEM_TRADE));
	LogItem.Flag = ITEMLOG_MYSHOP;
	strcpy_s(LogItem.UserID, lpPlayInfo2->getAccount().c_str());
	strcpy_s(LogItem.CharName, lpPlayInfo2->getName().c_str());
	strcpy_s(LogItem.TUserID, lpPlayInfo->getAccount().c_str());
	strcpy_s(LogItem.TCharName, lpPlayInfo->getName().c_str());
	LogItem.IP = lpPlayInfo2->lpsmSock->acc_sin.sin_addr.S_un.S_addr;
	LogItem.TIP = lpPlayInfo->lpsmSock->acc_sin.sin_addr.S_un.S_addr;

	LogItem.Item[0].dwCode = dwItemCode;
	LogItem.Item[0].dwINo[0] = dwHead;
	LogItem.Item[0].dwINo[1] = dwChkSum;
	LogItem.ItemCount = 1;

	LogItem.size = sizeof(LogITEM_TRADE) - (sizeof(_LogITEM)*(32 - LogItem.ItemCount));


	b_PushLogItemQue(2, LogItem.size, &LogItem);

	return TRUE;
}



int	rsRecord_ItemLog_Post(rsPLAYINFO *lpPlayInfo, DWORD dwItemCode, DWORD	dwHead, DWORD dwChkSum, DWORD dwGCode, char *szTelNum, int Flag)
{
	LogGiftITEM	LogItem;

	if(!lpPlayInfo->lpsmSock) return FALSE;

	ZeroMemory(&LogItem, sizeof(LogGiftITEM));

	LogItem.Flag = Flag;
	strcpy_s(LogItem.UserID, lpPlayInfo->getAccount().c_str());
	strcpy_s(LogItem.CharName, lpPlayInfo->getName().c_str());
	LogItem.IP = lpPlayInfo->lpsmSock->acc_sin.sin_addr.S_un.S_addr;
	LogItem.Gitem.dwCode = dwItemCode;
	LogItem.Gitem.dwINo[0] = dwHead;
	LogItem.Gitem.dwINo[1] = dwChkSum;
	LogItem.GNo = dwGCode;
	LogItem.size = sizeof(LogGiftITEM);

	if(szTelNum && szTelNum[0])
	{
		szTelNum[15] = 0;
		strcpy_s(LogItem.TEL, szTelNum);
	}


	return b_PushLogItemQue(3, LogItem.size, &LogItem);
}


int	rsRecord_SmeltingItemLOG(rsPLAYINFO *lpPlayInfo, DWORD *lpItemCode, DWORD *lpHead, DWORD *lpChkSum, int Flag)
{
	LogITEM LogItem;
	int cnt;
	ZeroMemory(&LogItem, sizeof(LogITEM));

	if(!lpPlayInfo->lpsmSock) return FALSE;

	LogItem.Flag = Flag;
	strcpy_s(LogItem.UserID, lpPlayInfo->getAccount().c_str());
	strcpy_s(LogItem.CharName, lpPlayInfo->getName().c_str());
	LogItem.IP = lpPlayInfo->lpsmSock->acc_sin.sin_addr.S_un.S_addr;

	LogItem.ItemCount = 0;
	for(cnt = 0; cnt < 5; cnt++)
	{
		if(lpItemCode[cnt])
		{
			LogItem.Item[LogItem.ItemCount].dwCode = lpItemCode[cnt];
			LogItem.Item[LogItem.ItemCount].dwINo[0] = lpHead[cnt];
			LogItem.Item[LogItem.ItemCount].dwINo[1] = lpChkSum[cnt];
			LogItem.ItemCount++;
		}
	}

	if(LogItem.ItemCount == 0) return FALSE;
	LogItem.size = sizeof(LogITEM) - (sizeof(_LogITEM)*(32 - LogItem.ItemCount));


	return b_PushLogItemQue(1, LogItem.size, &LogItem);
}

int	rsRecord_ManufactureItemLOG(rsPLAYINFO *lpPlayInfo, DWORD *lpItemCode, DWORD *lpHead, DWORD *lpChkSum, int Flag)
{
	LogITEM LogItem;
	int cnt;
	ZeroMemory(&LogItem, sizeof(LogITEM));

	if(!lpPlayInfo->lpsmSock) return FALSE;

	LogItem.Flag = Flag;
	strcpy_s(LogItem.UserID, lpPlayInfo->getAccount().c_str());
	strcpy_s(LogItem.CharName, lpPlayInfo->getName().c_str());
	LogItem.IP = lpPlayInfo->lpsmSock->acc_sin.sin_addr.S_un.S_addr;

	LogItem.ItemCount = 0;
	for(cnt = 0; cnt < 4; cnt++)
	{
		if(lpItemCode[cnt])
		{
			LogItem.Item[LogItem.ItemCount].dwCode = lpItemCode[cnt];
			LogItem.Item[LogItem.ItemCount].dwINo[0] = lpHead[cnt];
			LogItem.Item[LogItem.ItemCount].dwINo[1] = lpChkSum[cnt];
			LogItem.ItemCount++;
		}
	}

	if(LogItem.ItemCount == 0) return FALSE;
	LogItem.size = sizeof(LogITEM) - (sizeof(_LogITEM)*(32 - LogItem.ItemCount));


	return b_PushLogItemQue(1, LogItem.size, &LogItem);
}


int rsRecord_MixtureResetItemLOG(rsPLAYINFO *lpPlayInfo, sMIXTURE_RESET_ITEM_SERVER *pMixtureResetItem_Server, int Flag)
{
	LogITEM LogItem;
	ZeroMemory(&LogItem, sizeof(LogITEM));

	if(!lpPlayInfo->lpsmSock) return FALSE;

	LogItem.Flag = Flag;
	strcpy_s(LogItem.UserID, lpPlayInfo->getAccount().c_str());
	strcpy_s(LogItem.CharName, lpPlayInfo->getName().c_str());
	LogItem.IP = lpPlayInfo->lpsmSock->acc_sin.sin_addr.S_un.S_addr;

	LogItem.ItemCount = 0;


	LogItem.Item[LogItem.ItemCount].dwCode = pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.CODE;
	LogItem.Item[LogItem.ItemCount].dwINo[0] = pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.ItemHeader.Head;
	LogItem.Item[LogItem.ItemCount].dwINo[1] = pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.ItemHeader.dwChkSum;
	LogItem.ItemCount++;


	LogItem.Item[LogItem.ItemCount].dwCode = pMixtureResetItem_Server->dwMixtureResetStoneItemCode;
	LogItem.Item[LogItem.ItemCount].dwINo[0] = pMixtureResetItem_Server->dwMixtureResetStoneHead;
	LogItem.Item[LogItem.ItemCount].dwINo[1] = pMixtureResetItem_Server->dwMixtureResetStoneCheckSum;
	LogItem.ItemCount++;

	if(LogItem.ItemCount == 0) return FALSE;
	LogItem.size = sizeof(LogITEM) - (sizeof(_LogITEM)*(32 - LogItem.ItemCount));


	return b_PushLogItemQue(1, LogItem.size, &LogItem);
}



int	rsSaveAgingItemToHDD(sITEMINFO *lpItem)
{

	char	szBuff[256];
	FILE	*fp;


	CreateDirectory(szLogItemDataDirectory, NULL);


	wsprintf(szBuff, "%s\\%d@%d.itm", szLogItemDataDirectory, lpItem->ItemHeader.Head, lpItem->ItemHeader.dwChkSum);
	fp = fopen(szBuff, "wb");
	if(fp)
	{
		fwrite(lpItem, sizeof(sITEMINFO), 1, fp);
		fclose(fp);
		return TRUE;
	}

	return FALSE;
}


int	rsSaveCreateItemToHDD(psITEM	*lpItem)
{
	DWORD	dwCode;
	char	szBuff[256];
	FILE	*fp;


	dwCode = lpItem->ItemInfo.CODE;
	if(dwCode >= sinPM1) return FALSE;
	if((dwCode&sinITEM_MASK2) == sinOS1)
	{

		if((dwCode&sinITEM_MASK3) < sin05) return FALSE;
	}
	else
	{

		if((dwCode&sinITEM_MASK3) < sin08) return FALSE;
	}

	CreateDirectory(szLogItemDataDirectory, NULL);


	wsprintf(szBuff, "%s\\%d@%d.itm", szLogItemDataDirectory, lpItem->ItemInfo.ItemHeader.Head, lpItem->ItemInfo.ItemHeader.dwChkSum);
	fp = fopen(szBuff, "wb");
	if(fp)
	{
		fwrite(&lpItem->ItemInfo, sizeof(sITEMINFO), 1, fp);
		fclose(fp);
		return TRUE;
	}

	return FALSE;
}


int	rsLoadCreateItemToHDD(psITEM	*lpItem, char *szFileCode)
{
	FILE *fp;
	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;
	char	szBuff[256];

	wsprintf(szBuff, "%s\\%s.itm", szLogItemDataDirectory, szFileCode);

	hFindHandle = FindFirstFile(szBuff, &fd);
	if(hFindHandle != INVALID_HANDLE_VALUE)
	{
		FindClose(hFindHandle);

		fp = fopen(szBuff, "rb");
		if(fp)
		{
			fread(&lpItem->ItemInfo, sizeof(sITEMINFO), 1, fp);
			fclose(fp);
		}
		return TRUE;
	}

	return FALSE;
}



struct	sRECORD_COPIED_ITEM_HEAD
{
	char	szHeader[16];
	int		TotalCount;
	int		A_ItemCount;
	int		D_ItemCount;
	int		S_ItemCount;
	int		E_ItemCount;

	int		Temp[7];
};

struct	sRECORD_COPIED_ITEM
{
	DWORD	dwItemCode;
	DWORD	dwHead;
	DWORD	dwChkSum;
	DWORD	dwTemp;
};

struct sRECORD_COPIED_ITEM_FILE
{
	sRECORD_COPIED_ITEM_HEAD	sHeader;
	sRECORD_COPIED_ITEM			sCopiedItem[4096];
};


sRECORD_COPIED_ITEM	*lpCopiedItem_List = 0;
sRECORD_COPIED_ITEM	*lpCopiedItem_Sheltom_List = 0;

int rsCopiedItem_Count = 0;
int rsCopiedItem_Sheltom_Count = 0;



int rsLoadCopiedItemList()
{
	sRECORD_COPIED_ITEM_FILE	sCopiedItems;
	FILE *fp;
	int cnt;

	rsRemoveCopiedItemList();

	fp = fopen("cpItem.dat", "rb");
	if(!fp) return FALSE;

	fread(&sCopiedItems, sizeof(sRECORD_COPIED_ITEM_FILE), 1, fp);
	fclose(fp);

	if(sCopiedItems.sHeader.TotalCount >= 4096 || sCopiedItems.sHeader.TotalCount < 0) return FALSE;

	rsCopiedItem_Sheltom_Count = 0;
	rsCopiedItem_Count = 0;

	for(cnt = 0; cnt < sCopiedItems.sHeader.TotalCount; cnt++)
	{
		if((sCopiedItems.sCopiedItem[cnt].dwItemCode&sinITEM_MASK2) == sinOS1)
		{

			rsCopiedItem_Sheltom_Count++;
		}
		else
		{

			rsCopiedItem_Count++;
		}
	}

	if(rsCopiedItem_Count) lpCopiedItem_List = new sRECORD_COPIED_ITEM[rsCopiedItem_Count];
	if(rsCopiedItem_Sheltom_Count) lpCopiedItem_Sheltom_List = new sRECORD_COPIED_ITEM[rsCopiedItem_Sheltom_Count];


	rsCopiedItem_Sheltom_Count = 0;
	rsCopiedItem_Count = 0;

	for(cnt = 0; cnt < sCopiedItems.sHeader.TotalCount; cnt++)
	{
		if((sCopiedItems.sCopiedItem[cnt].dwItemCode&sinITEM_MASK2) == sinOS1)
		{

			lpCopiedItem_Sheltom_List[rsCopiedItem_Sheltom_Count].dwItemCode = sCopiedItems.sCopiedItem[cnt].dwItemCode;
			lpCopiedItem_Sheltom_List[rsCopiedItem_Sheltom_Count].dwHead = sCopiedItems.sCopiedItem[cnt].dwHead;
			lpCopiedItem_Sheltom_List[rsCopiedItem_Sheltom_Count].dwChkSum = sCopiedItems.sCopiedItem[cnt].dwChkSum;
			rsCopiedItem_Sheltom_Count++;
		}
		else
		{

			lpCopiedItem_List[rsCopiedItem_Count].dwItemCode = sCopiedItems.sCopiedItem[cnt].dwItemCode;
			lpCopiedItem_List[rsCopiedItem_Count].dwHead = sCopiedItems.sCopiedItem[cnt].dwHead;
			lpCopiedItem_List[rsCopiedItem_Count].dwChkSum = sCopiedItems.sCopiedItem[cnt].dwChkSum;
			rsCopiedItem_Count++;
		}
	}

	return TRUE;
}


int rsRemoveCopiedItemList()
{
	if(lpCopiedItem_List)
	{
		delete lpCopiedItem_List;
		lpCopiedItem_List = 0;
	}
	if(lpCopiedItem_Sheltom_List)
	{
		delete lpCopiedItem_Sheltom_List;
		lpCopiedItem_Sheltom_List = 0;
	}

	rsCopiedItem_Sheltom_Count = 0;
	rsCopiedItem_Count = 0;

	return TRUE;
}




int rsCheckCopiedItem(DWORD dwCode, DWORD dwHead, DWORD dwChkSum)
{
	int cnt;

	if((dwCode&sinITEM_MASK2) == sinOS1)
	{

		if(!lpCopiedItem_Sheltom_List || rsCopiedItem_Sheltom_Count <= 0) return FALSE;

		for(cnt = 0; cnt < rsCopiedItem_Sheltom_Count; cnt++)
		{
			if(dwCode == lpCopiedItem_Sheltom_List[cnt].dwItemCode &&
				dwHead == lpCopiedItem_Sheltom_List[cnt].dwHead &&
				dwChkSum == lpCopiedItem_Sheltom_List[cnt].dwChkSum)
			{

				return TRUE;
			}
		}
	}
	else
	{

		if(!lpCopiedItem_List || rsCopiedItem_Count <= 0) return FALSE;

		for(cnt = 0; cnt < rsCopiedItem_Count; cnt++)
		{
			if(dwCode == lpCopiedItem_List[cnt].dwItemCode &&
				dwHead == lpCopiedItem_List[cnt].dwHead &&
				dwChkSum == lpCopiedItem_List[cnt].dwChkSum)
			{

				return TRUE;
			}
		}
	}


	return FALSE;
}


int rsCheckCopiedItem(sITEMINFO *lpItem)
{
	DWORD dwHead, dwChkSum;

	if(lpItem->BackUpKey && lpItem->BackUpChkSum)
	{
		dwHead = lpItem->BackUpKey;
		dwChkSum = lpItem->BackUpChkSum;
	}
	else
	{
		dwHead = lpItem->ItemHeader.Head;
		dwChkSum = lpItem->ItemHeader.dwChkSum;
	}

	return rsCheckCopiedItem(lpItem->CODE, dwHead, dwChkSum);
}











int rsUpdateSkill(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	switch(lpTransCommand->WParam)
	{

	case SKILL_PLAY_METAL_GOLEM:
	case SKILL_PLAY_RECALL_WOLVERIN:
	case SKILL_PLAY_FIRE_ELEMENTAL:
	case SKILL_PLAY_R_KNIGHT:
	case SKILL_METAL_GOLEM:
	case SKILL_RECALL_WOLVERIN:
	case SKILL_FIRE_ELEMENTAL:
	case SKILL_R_KNIGHT:
		if(lpPlayInfo->lpLinkChar && lpPlayInfo->lpLinkChar->dwObjectSerial == lpPlayInfo->dwLinkCharCode && lpPlayInfo->lpLinkChar->HoSkillCode)
		{

			lpPlayInfo->lpLinkChar->HoSkillMode = lpTransCommand->LParam;
			lpPlayInfo->lpLinkChar->lpTargetPlayInfo = 0;
			lpPlayInfo->lpLinkChar->lpTargetChar = 0;
		}
		break;
	}

	return TRUE;
}



int rsCancelSkill(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	switch(lpTransCommand->WParam)
	{
	case 0:
		lpPlayInfo->dwSkill_PhysicalAbsorb_Time = 0;
		lpPlayInfo->dwSkill_PhysicalAbsorb_Param = 0;

		lpPlayInfo->dwSkill_ExtreamShield_Time = 0;
		lpPlayInfo->dwSkill_ExtreamShield_Param = 0;

		lpPlayInfo->dwSkill_AutoMation_Time = 0;
		lpPlayInfo->dwSkill_AutoMation_Param = 0;

		lpPlayInfo->dwSkill_Maximize_Time = 0;
		lpPlayInfo->dwSkill_Maximize_Param = 0;

		lpPlayInfo->dwSkill_HolyBody_Time = 0;
		lpPlayInfo->dwSkill_HolyBody_Param = 0;

		lpPlayInfo->dwSkill_HolyValor_Time = 0;
		lpPlayInfo->dwSkill_HolyValor_Param = 0;

		lpPlayInfo->dwSkill_HolyReflection_Time = 0;
		lpPlayInfo->dwSkill_HolyReflection_Param = 0;

		lpPlayInfo->dwSkill_EnchantWeapon_Time = 0;
		lpPlayInfo->dwSkill_EnchantWeapon_Param = 0;


		lpPlayInfo->dwSkill_MetalArmor_Time = 0;
		lpPlayInfo->dwSkill_MetalArmor_Param = 0;
		lpPlayInfo->dwSkill_SparkShield_Time = 0;
		lpPlayInfo->dwSkill_SparkShield_Param = 0;

		lpPlayInfo->dwSKill_Falcon_Time = 0;
		lpPlayInfo->dwSKill_Falcon_Damage[0] = 0;
		lpPlayInfo->dwSKill_Falcon_Damage[1] = 0;

		lpPlayInfo->dwSkill_DivineInhalation_Time = 0;
		lpPlayInfo->dwSkill_DivineInhalation_Param = 0;

		lpPlayInfo->dwSkill_TriumphOfValhalla_Time = 0;
		lpPlayInfo->dwSkill_TriumphOfValhalla_Param = 0;

		lpPlayInfo->dwSkill_VirtualLife_Time = 0;
		lpPlayInfo->dwSkill_VirtualLife_Param = 0;


		lpPlayInfo->dwSkill_EnergyShield_Time = 0;
		lpPlayInfo->dwSkill_EnergyShield_Param = 0;

		lpPlayInfo->dwSkill_SpiritElemental_Time = 0;
		lpPlayInfo->dwSkill_SpiritElemental_Param = 0;

		lpPlayInfo->dwSkill_DancingSword_Time = 0;
		lpPlayInfo->dwSkill_DancingSword_Param = 0;
		lpPlayInfo->dwSkill_DancingSword_DelayTime = 0;

		lpPlayInfo->dwSkill_Vanish_Time = 0;
		lpPlayInfo->dwSkill_Vanish_Param = 0;

		lpPlayInfo->dwSkill_MagneticSphere_Time = 0;
		lpPlayInfo->dwSkill_MagneticSphere_Param = 0;

		lpPlayInfo->dwSkill_Berserker_Time = 0;
		lpPlayInfo->dwSkill_Berserker_Param = 0;

		lpPlayInfo->dwSkill_AssassinEye_Time = 0;
		lpPlayInfo->dwSkill_AssassinEye_Param = 0;

		lpPlayInfo->dwSkill_Vague_Time = 0;
		lpPlayInfo->dwSkill_Vague_Param = 0;

		lpPlayInfo->dwSkill_ForceOfNature_Time = 0;
		lpPlayInfo->wSkill_ForceOfNature_Param[0] = 0;
		lpPlayInfo->wSkill_ForceOfNature_Param[1] = 0;

		lpPlayInfo->dwSkill_GodlyShied_Time = 0;
		lpPlayInfo->dwSkill_GodlyShied_Param = 0;

		lpPlayInfo->dwSkill_GodsBless_Time = 0;
		lpPlayInfo->dwSkill_GodsBless_Param = 0;

		lpPlayInfo->dwSkill_HallOfValhalla_Time = 0;

		lpPlayInfo->dwSkill_FrostJavelin_Time = 0;
		lpPlayInfo->dwSkill_FrostJavelin_Param = 0;

		lpPlayInfo->dwSkill_RegenerationField_Time = 0;

		lpPlayInfo->dwSkill_SummonMuspell_Time = 0;
		lpPlayInfo->dwSkill_SummonMuspell_Param = 0;


		lpPlayInfo->dwCurse_Attack_Time = 0;
		lpPlayInfo->dwCurse_Defence_Time = 0;
		break;

	case SKILL_PLAY_HOLY_VALOR:
		lpPlayInfo->dwSkill_HolyValor_Time = 0;
		lpPlayInfo->dwSkill_HolyValor_Param = 0;
		break;

	case SKILL_PLAY_AUTOMATION:
		lpPlayInfo->dwSkill_AutoMation_Time = 0;
		lpPlayInfo->dwSkill_AutoMation_Param = 0;
		break;

	case SKILL_PLAY_MAXIMIZE:
		lpPlayInfo->dwSkill_Maximize_Time = 0;
		lpPlayInfo->dwSkill_Maximize_Param = 0;
		break;

	case SKILL_PLAY_PHYSICAL_ABSORB:
		lpPlayInfo->dwSkill_PhysicalAbsorb_Time = 0;
		lpPlayInfo->dwSkill_PhysicalAbsorb_Param = 0;
		break;

	case SKILL_PLAY_EXTREME_SHIELD:
		lpPlayInfo->dwSkill_ExtreamShield_Time = 0;
		lpPlayInfo->dwSkill_ExtreamShield_Param = 0;
		break;

	case SKILL_PLAY_FROST_JAVELIN:
		lpPlayInfo->dwSkill_FrostJavelin_Time = 0;
		lpPlayInfo->dwSkill_FrostJavelin_Param = 0;
		break;


	}

	return TRUE;
}

int rsProcessSkillPartyUser(rsPLAYINFO *lpPlayInfo, TRANS_PARTY_SKILL *lpTransPartySkill)
{
	int point = lpTransPartySkill->Point - 1;

	if(point < 0 || point >= 10)
	{
		return FALSE;
	}

	switch(lpTransPartySkill->dwSkillCode)
	{
	case SKILL_PLAY_HOLY_VALOR:

		lpPlayInfo->dwSkill_HolyValor_Time = dwPlayServTime + (Holy_Valor_Time[point] * 1000);
		lpPlayInfo->dwSkill_HolyValor_Param = Holy_Valor_Damage[point];
		return TRUE;

	}


	return FALSE;
}


int	rsRecvSkillPartyUser(TRANS_PARTY_SKILL *lpTransPartySkill)
{
	int cnt;
	rsPLAYINFO *lpPlayInfo;

	for(cnt = 0; cnt < lpTransPartySkill->PartyCount; cnt++)
	{
		lpPlayInfo = srFindUserFromSerial(lpTransPartySkill->dwPartyUser[cnt]);
		if(lpPlayInfo && lpPlayInfo->lpsmSock)
		{
			if(rsProcessSkillPartyUser(lpPlayInfo, lpTransPartySkill) == TRUE)
			{
				lpPlayInfo->lpsmSock->Send((char *)lpTransPartySkill, lpTransPartySkill->size, TRUE);
			}
		}
	}

	return TRUE;
}


int rsRecvProcessSkill(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	DWORD dwSkillCode;
	int point;
	rsPLAYINFO *lpPlayInfo2;
	smTRANS_COMMAND_EX	TransCommandEx;
	int	lv;
	smCHAR	*lpChar;
	int cnt, x, y, z, dist, size;

	dwSkillCode = lpTransCommand->WParam & 0xFF;
	point = (lpTransCommand->WParam >> 8) & 0xF;
	point -= 1;

	if(point < 0) point = lpTransCommand->LParam - 1;

	if(point < 0 || point >= 10) return FALSE;


	if(rsCheckSkillLevel(lpPlayInfo, dwSkillCode) == FALSE)
	{
		if(lpPlayInfo->WarningCount < 5 && dwSkillCode != SKILL_PLAY_RESURRECTION)
		{


			TransCommandEx.size = sizeof(smTRANS_COMMAND);
			TransCommandEx.code = OpCode::OPCODE_SET_BLACKLIST;
			TransCommandEx.WParam = 8850;
			TransCommandEx.LParam = lpPlayInfo->smCharInfo.Level;
			TransCommandEx.SParam = dwSkillCode;
			TransCommandEx.EParam = point;
			rsSendDataServer(lpPlayInfo->lpsmSock, &TransCommandEx);
			lpPlayInfo->WarningCount++;
		}
	}


	switch(dwSkillCode)
	{
	case SKILL_PLAY_HOLY_REFLECTION:
		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_PRIESTESS)
		{

			lpPlayInfo->dwSkill_HolyReflection_Time = dwPlayServTime + Holy_Reflection_Time[point] * 1000;
			lpPlayInfo->dwSkill_HolyReflection_Param = Holy_Reflection_Return_Damage[point];
		}
		break;

	case SKILL_PLAY_ENCHANT_WEAPON:
		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MAGICIAN)
		{

			lpPlayInfo2 = srFindUserFromSerial(lpTransCommand->SParam);
			if(lpPlayInfo2 && lpPlayInfo2->lpsmSock)
			{
				lpPlayInfo2->dwSkill_EnchantWeapon_Time = dwPlayServTime + Enchant_Weapon_Time[point] * 1000;
				lpPlayInfo2->dwSkill_EnchantWeapon_Param = (point + 1) | (lpTransCommand->EParam << 8);
				if(lpPlayInfo2 != lpPlayInfo)
					lpPlayInfo2->lpsmSock->Send((char *)lpTransCommand, lpTransCommand->size, TRUE);
			}
		}
		break;

	case SKILL_PLAY_AUTOMATION:
		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MECHANICIAN)
		{

			lpPlayInfo->dwSkill_AutoMation_Time = dwPlayServTime + Automation_Time[point] * 1000;
			lpPlayInfo->dwSkill_AutoMation_Param = Automation_Damage[point];
		}
		break;

	case SKILL_PLAY_MAXIMIZE:
		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MECHANICIAN)
		{

			lpPlayInfo->dwSkill_Maximize_Time = dwPlayServTime + Maximize_Time[point] * 1000;
			lpPlayInfo->dwSkill_Maximize_Param = Maximize_Damage[point];
		}
		break;

	case SKILL_PLAY_PHYSICAL_ABSORB:
		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MECHANICIAN)
		{

			lpPlayInfo->dwSkill_PhysicalAbsorb_Time = dwPlayServTime + P_Absorb_UseTime[point] * 1000;
			lpPlayInfo->dwSkill_PhysicalAbsorb_Param = GetRandomPos(P_Absorb[point][0], P_Absorb[point][1]);
		}
		break;

	case SKILL_PLAY_EXTREME_SHIELD:
		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MECHANICIAN)
		{

			lpPlayInfo->dwSkill_ExtreamShield_Time = dwPlayServTime + E_Shield_UseTime[point] * 1000;
			lpPlayInfo->dwSkill_ExtreamShield_Param = E_Shield_BlockRate[point];
		}
		break;

	case SKILL_PLAY_HOLY_BODY:
		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_KNIGHT)
		{

			lpPlayInfo->dwSkill_HolyBody_Time = dwPlayServTime + HolyBody_Time[point] * 1000;
			lpPlayInfo->dwSkill_HolyBody_Param = HolyBody_Absorb[point];
		}
		break;

	case SKILL_PLAY_METAL_ARMOR:
		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MECHANICIAN)
		{

			lpPlayInfo->dwSkill_MetalArmor_Time = dwPlayServTime + Metal_Armor_Time[point] * 1000;
			if(lpTransCommand->SParam > 0 && lpTransCommand->SParam <= 10)
			{
				lpPlayInfo->dwSkill_MetalArmor_Param = (P_Absorb[lpTransCommand->SParam - 1][0] + P_Absorb[lpTransCommand->SParam - 1][1]) / 2;
			}
			else
				lpPlayInfo->dwSkill_MetalArmor_Param = 0;
		}
		break;

	case SKILL_PLAY_SPARK_SHIELD:
		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MECHANICIAN)
		{

			lpPlayInfo->dwSkill_SparkShield_Time = dwPlayServTime + Spark_Shield_Time[point] * 1000;
			if(lpTransCommand->SParam > 0 && lpTransCommand->SParam <= 10)
			{
				lpPlayInfo->dwSkill_SparkShield_Param = (Spark_Shield_Damage[point] * Spark_Damage[lpTransCommand->SParam - 1][0]) / 100;
				lpPlayInfo->dwSkill_SparkShield_Param <<= 16;
				lpPlayInfo->dwSkill_SparkShield_Param |= (Spark_Shield_Damage[point] * Spark_Damage[lpTransCommand->SParam - 1][1]) / 100;
			}
			else
				lpPlayInfo->dwSkill_SparkShield_Param = 0;
		}
		break;


	case SKILL_PLAY_FALCON:
		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_ARCHER)
		{
			lpPlayInfo->dwSKill_Falcon_Time = dwPlayServTime + Falcon_Time[point] * 1000;
			lpPlayInfo->dwSKill_Falcon_Damage[0] = Falcon_Damage[point][0];
			lpPlayInfo->dwSKill_Falcon_Damage[1] = Falcon_Damage[point][1];
		}
		break;

	case SKILL_PLAY_GOLDEN_FALCON:
		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_ARCHER)
		{
			if(lpTransCommand->SParam > 0 && lpTransCommand->SParam <= 10)
			{
				lpPlayInfo->dwSKill_Falcon_Time = dwPlayServTime + Golden_Falcon_Time[point] * 1000;
				lpPlayInfo->dwSKill_Falcon_Damage[0] = Falcon_Damage[lpTransCommand->SParam - 1][0];
				lpPlayInfo->dwSKill_Falcon_Damage[1] = Falcon_Damage[lpTransCommand->SParam - 1][1];
				lpPlayInfo->dwSKill_Falcon_Damage[0] = (lpPlayInfo->dwSKill_Falcon_Damage[0] * Golden_Falcon_Damage[point]) / 100;
				lpPlayInfo->dwSKill_Falcon_Damage[1] = (lpPlayInfo->dwSKill_Falcon_Damage[1] * Golden_Falcon_Damage[point]) / 100;
			}
		}
		break;


	case SKILL_PLAY_DIVINE_INHALATION:
		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_KNIGHT)
		{
			lpPlayInfo->dwSkill_DivineInhalation_Time = dwPlayServTime + D_Inhalation_Time[point] * 1000;
			lpPlayInfo->dwSkill_DivineInhalation_Param = point;
		}
		break;


	case SKILL_PLAY_RESURRECTION:
		if(lpTransCommand->SParam)
		{
			if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_PRIESTESS)
			{
				lpPlayInfo2 = srFindUserFromSerial(lpTransCommand->SParam);
				if(lpPlayInfo2)
				{
					if((rand() % 100) < Resurrection_Percent[point])
					{
						if(lpPlayInfo2 != lpPlayInfo)
							lpPlayInfo2->lpsmSock->Send((char *)lpTransCommand, lpTransCommand->size, TRUE);
					}
				}
			}
		}
		else
		{

			ZeroMemory(&TransCommandEx, sizeof(smTRANS_COMMAND_EX));
			TransCommandEx.WParam = smCOMMNAD_USER_RESURRECTION;
			TransCommandEx.LParam = lpPlayInfo->dwObjectSerial;
			TransCommandEx.SParam = 0;
			TransCommandEx.EParam = 0;
			rsSendCommandUser(lpPlayInfo, &TransCommandEx);
		}
		break;

		
	case SKILL_PLAY_VIRTUAL_LIFE:
		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_PRIESTESS)
		{

			if(!lpTransCommand->SParam)
			{
				lpPlayInfo->dwSkill_VirtualLife_Time = dwPlayServTime + Virtual_Life_Time[point] * 1000;
				lpPlayInfo->dwSkill_VirtualLife_Param = Virtual_Life_Percent[point];
			}
			else
			{
				lpPlayInfo2 = srFindUserFromSerial(lpTransCommand->SParam);
				if(lpPlayInfo2 && lpPlayInfo2->dwSkill_VirtualLife_Time < dwPlayServTime)
				{
					lpPlayInfo2->dwSkill_VirtualLife_Time = dwPlayServTime + Virtual_Life_Time[point] * 1000;
					lpPlayInfo2->dwSkill_VirtualLife_Param = Virtual_Life_Percent[point];
					lpPlayInfo2->lpsmSock->Send((char *)lpTransCommand, lpTransCommand->size, TRUE);
				}
			}
		}
		break;

	case SKILL_PLAY_ZENITH:

		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MAGICIAN)
		{

		}
		break;

	case SKILL_PLAY_ENERGY_SHIELD:

		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MAGICIAN)
		{
			lpPlayInfo->dwSkill_EnergyShield_Time = dwPlayServTime + Energy_Shield_Time[point] * 1000;
			lpPlayInfo->dwSkill_EnergyShield_Param = Energy_Shield_DecDamage[point];
		}
		break;

	case SKILL_PLAY_SPIRIT_ELEMENTAL:

		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MAGICIAN)
		{
			lpPlayInfo->dwSkill_SpiritElemental_Time = dwPlayServTime + Spirit_Elemental_Time[point] * 1000;
			lpPlayInfo->dwSkill_SpiritElemental_Param = Spirit_Elemental_Damage[point];
		}
		break;

	case SKILL_PLAY_DANCING_SWORD:

		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MAGICIAN)
		{
			lpPlayInfo->dwSkill_DancingSword_Time = dwPlayServTime + Dancing_Sword_Time[point] * 1000;
			lpPlayInfo->dwSkill_DancingSword_Param = (lpTransCommand->SParam) | (point << 16);
			lpPlayInfo->dwSkill_DancingSword_DelayTime = 0;
		}
		break;

	case SKILL_PLAY_TRIUMPH_OF_VALHALLA:

		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_ATALANTA)
		{
			if(lpPlayInfo->smCharInfo.Level > 0 && lpPlayInfo->smCharInfo.Level < CHAR_LEVEL_MAX)
				lv = lpPlayInfo->smCharInfo.Level / 4;
			else
				lv = 0;

			if(!lpTransCommand->SParam)
			{
				lpPlayInfo->dwSkill_TriumphOfValhalla_Time = dwPlayServTime + (T_Of_Valhalla_Time[point] * 1000);
				lpPlayInfo->dwSkill_TriumphOfValhalla_Param = T_Of_Valhalla_Damage[point] + lv;

				lpPlayInfo->dwSkill_HallOfValhalla_Time = 0;
			}
			else
			{
				lpPlayInfo2 = srFindUserFromSerial(lpTransCommand->SParam);
				if(lpPlayInfo2)
				{
					if(lpPlayInfo2->dwSkill_HallOfValhalla_Time < dwPlayServTime)
					{
						lpPlayInfo2->dwSkill_TriumphOfValhalla_Time = dwPlayServTime + (T_Of_Valhalla_Time[point] * 1000);
						lpPlayInfo2->dwSkill_TriumphOfValhalla_Param = (T_Of_Valhalla_Damage[point] + lv) / 2;
						lpTransCommand->EParam = lpPlayInfo->smCharInfo.Level;
						lpPlayInfo2->lpsmSock->Send((char *)lpTransCommand, lpTransCommand->size, TRUE);
					}
				}
			}
		}
		return TRUE;

	case SKILL_PLAY_VANISH:

		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_PIKEMAN)
		{
			lpPlayInfo->dwSkill_Vanish_Time = dwPlayServTime + Vanish_Time[point] * 1000;
			lpPlayInfo->dwSkill_Vanish_Param = point;
		}
		break;

	case SKILL_PLAY_MAGNETIC_SPHERE:
		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MECHANICIAN)
		{
			lpPlayInfo->dwSkill_MagneticSphere_Time = dwPlayServTime + Magnetic_Sphere_Time[point] * 1000;
			lpPlayInfo->dwSkill_MagneticSphere_Param = point;
		}
		break;

	case SKILL_PLAY_METAL_GOLEM:
		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MECHANICIAN)
		{
			lpChar = OpenMonsterFromSkill(dwSkillCode, lpPlayInfo->Position.x, lpPlayInfo->Position.y, lpPlayInfo->Position.z, lpPlayInfo, 0);
			if(lpChar)
			{
				lpChar->dwUpdateCharInfoTime = dwPlayServTime + 355 * 1000;
				lpChar->smCharInfo.Attack_Damage[0] = Metal_Golem_Damage[point][0];
				lpChar->smCharInfo.Attack_Damage[1] = Metal_Golem_Damage[point][1];
				lpChar->smCharInfo.Attack_Rating = Metal_Golem_Hit[point];
				lpChar->smCharInfo.Defence = Metal_Golem_Defense[point];


				lpChar->smCharInfo.Life[0] = Metal_Golem_Life[point] + lpPlayInfo->smCharInfo.Strength * 2;
				lpChar->smCharInfo.Life[1] = lpChar->smCharInfo.Life[0];

				lpChar->sMoveStepCount[0] = 1;
				lpChar->sMoveStepCount[1] = 2;

				lpChar->smCharInfo.wPlayClass[1] = fONE + point * 15;
			}
		}
		break;


	case SKILL_PLAY_BERSERKER:
		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_FIGHTER)
		{
			lpPlayInfo->dwSkill_Berserker_Time = dwPlayServTime + Berserker_Time[point] * 1000;
			lpPlayInfo->dwSkill_Berserker_Param = point;
		}
		break;

	case SKILL_PLAY_ASSASSIN_EYE:
		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_PIKEMAN)
		{
			lpPlayInfo->dwSkill_AssassinEye_Time = dwPlayServTime + Assassin_Eye_Time[point] * 1000;
			lpPlayInfo->dwSkill_AssassinEye_Param = point;
		}
		break;

	case SKILL_PLAY_VAGUE:
		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_PIKEMAN)
		{
			lpPlayInfo->dwSkill_Vague_Time = dwPlayServTime + Vague_Time[point] * 1000;
			lpPlayInfo->dwSkill_Vague_Param = point;
		}
		break;

	case SKILL_PLAY_RECALL_WOLVERIN:
		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_ARCHER)
		{
			lpChar = OpenMonsterFromSkill(dwSkillCode, lpPlayInfo->Position.x, lpPlayInfo->Position.y, lpPlayInfo->Position.z, lpPlayInfo, 0);
			if(lpChar)
			{
				lpChar->dwUpdateCharInfoTime = dwPlayServTime + 355 * 1000;
				lpChar->smCharInfo.Attack_Damage[0] = Recall_Wolverin_Damage[point][0];
				lpChar->smCharInfo.Attack_Damage[1] = Recall_Wolverin_Damage[point][1];
				lpChar->smCharInfo.Attack_Rating = Recall_Wolverin_Hit[point];
				lpChar->smCharInfo.Defence = Recall_Wolverin_Defense[point] + lpPlayInfo->smCharInfo.Dexterity * 2;
				lpChar->smCharInfo.Life[0] = Recall_Wolverin_Life[point];
				lpChar->smCharInfo.Life[1] = Recall_Wolverin_Life[point];

				lpChar->sMoveStepCount[0] = 1;
				lpChar->sMoveStepCount[1] = 2;

				lpChar->smCharInfo.wPlayClass[1] = (fONE / 2) + point * 12;
			}
		}
		break;

	case SKILL_PLAY_FORCE_OF_NATURE:
		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_ARCHER)
		{
			lpPlayInfo->dwSkill_ForceOfNature_Time = dwPlayServTime + Force_Of_Nature_Time[point] * 1000;
			lpPlayInfo->wSkill_ForceOfNature_Param[0] = Force_Of_Nature_AddDamage[point];
			lpPlayInfo->wSkill_ForceOfNature_Param[1] = Force_Of_Nature_FalconAddDamage[point];

			size = 300 * 300;
			for(cnt = 0; cnt < CONNECTMAX; cnt++)
			{
				if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial &&
					lpPlayInfo != &rsPlayInfo[cnt] &&
					rsPlayInfo[cnt].Position.Area == lpPlayInfo->Position.Area &&
					(rsPlayInfo[cnt].Position.Area != rsCASTLE_FIELD || (rsPlayInfo[cnt].dwClanCode && rsPlayInfo[cnt].dwClanCode == lpPlayInfo->dwClanCode)))
				{
					x = (lpPlayInfo->Position.x - rsPlayInfo[cnt].Position.x) >> FLOATNS;
					y = (lpPlayInfo->Position.y - rsPlayInfo[cnt].Position.y) >> FLOATNS;
					z = (lpPlayInfo->Position.z - rsPlayInfo[cnt].Position.z) >> FLOATNS;

					dist = x*x + z*z;
					if(dist < size && abs(y) < 80)
					{
						rsPlayInfo[cnt].dwSkill_ForceOfNature_Time = dwPlayServTime + Force_Of_Nature_Time[point] * 1000;
						rsPlayInfo[cnt].wSkill_ForceOfNature_Param[0] = Force_Of_Nature_AddDamage[point] / 2;
						rsPlayInfo[cnt].wSkill_ForceOfNature_Param[1] = Force_Of_Nature_FalconAddDamage[point];
						rsPlayInfo[cnt].lpsmSock->Send((char *)lpTransCommand, lpTransCommand->size, TRUE);

					}
				}
			}
		}
		break;

	case SKILL_PLAY_GODLY_SHIELD:
		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_KNIGHT)
		{
			lpPlayInfo->dwSkill_GodlyShied_Time = dwPlayServTime + Godly_Shield_Time[point] * 1000;
			lpPlayInfo->dwSkill_GodlyShied_Param = point;
		}
		break;

	case SKILL_PLAY_GODS_BLESS:
		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_KNIGHT)
		{
			lpPlayInfo->dwSkill_GodsBless_Time = dwPlayServTime + God_Bless_Time[point] * 1000;
			lpPlayInfo->dwSkill_GodsBless_Param = God_Bless_AddDamage[point];
		}
		break;

	case SKILL_PLAY_HALL_OF_VALHALLA:
		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_ATALANTA)
		{

			if(lpPlayInfo->smCharInfo.Level > 0 && lpPlayInfo->smCharInfo.Level < CHAR_LEVEL_MAX)
			{
				lv = lpPlayInfo->smCharInfo.Level / 4;
				lpTransCommand->EParam = lpPlayInfo->smCharInfo.Level;
			}
			else
			{
				lv = 0;
				lpTransCommand->EParam = 1;
			}

			lpPlayInfo->dwSkill_HallOfValhalla_Time = dwPlayServTime + Hall_Of_Valhalla_Time[point] * 1000;
			lpPlayInfo->wSkill_HallOfValhalla_Param[0] = Hall_Of_Valhalla_AddEvation[point];
			lpPlayInfo->wSkill_HallOfValhalla_Param[1] = T_Of_Valhalla_Damage[lpTransCommand->SParam - 1] + lv;

			lpPlayInfo->dwSkill_TriumphOfValhalla_Time = 0;




			size = 350 * 350;
			for(cnt = 0; cnt < CONNECTMAX; cnt++)
			{
				if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial &&
					lpPlayInfo != &rsPlayInfo[cnt] &&
					rsPlayInfo[cnt].Position.Area == lpPlayInfo->Position.Area &&
					(rsPlayInfo[cnt].Position.Area != rsCASTLE_FIELD || (rsPlayInfo[cnt].dwClanCode && rsPlayInfo[cnt].dwClanCode == lpPlayInfo->dwClanCode)))
				{
					x = (lpPlayInfo->Position.x - rsPlayInfo[cnt].Position.x) >> FLOATNS;
					y = (lpPlayInfo->Position.y - rsPlayInfo[cnt].Position.y) >> FLOATNS;
					z = (lpPlayInfo->Position.z - rsPlayInfo[cnt].Position.z) >> FLOATNS;

					dist = x*x + z*z;
					if(dist < size && abs(y) < 80)
					{
						if(rsPlayInfo[cnt].dwSkill_TriumphOfValhalla_Time < dwPlayServTime)
						{
							rsPlayInfo[cnt].dwSkill_HallOfValhalla_Time = dwPlayServTime + Hall_Of_Valhalla_Time[point] * 1000;
							rsPlayInfo[cnt].wSkill_HallOfValhalla_Param[0] = Hall_Of_Valhalla_AddEvation[point] / 2;
							rsPlayInfo[cnt].wSkill_HallOfValhalla_Param[1] = (T_Of_Valhalla_Damage[lpTransCommand->SParam - 1] + lv) / 2;
							rsPlayInfo[cnt].lpsmSock->Send((char *)lpTransCommand, lpTransCommand->size, TRUE);
						}
					}
				}
			}
		}
		break;

	case SKILL_PLAY_FROST_JAVELIN:
		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_ATALANTA)
		{
			lpPlayInfo->dwSkill_FrostJavelin_Time = dwPlayServTime + Frost_Javelin_Time[point] * 1000;
			lpPlayInfo->dwSkill_FrostJavelin_Param = point;
		}
		break;

	case SKILL_PLAY_REGENERATION_FIELD:
		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_PRIESTESS)
		{
			lpPlayInfo->dwSkill_RegenerationField_Time = dwPlayServTime + Regeneration_Field_Time[point] * 1000;
		}
		break;

	case SKILL_PLAY_SUMMON_MUSPELL:
		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_PRIESTESS)
		{
			lpPlayInfo->dwSkill_SummonMuspell_Time = dwPlayServTime + Summon_Muspell_Time[point] * 1000;
			lpPlayInfo->dwSkill_SummonMuspell_Param = point;
		}
		break;

	case SKILL_PLAY_FIRE_ELEMENTAL:
		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MAGICIAN)
		{
			lpChar = OpenMonsterFromSkill(dwSkillCode, lpPlayInfo->Position.x, lpPlayInfo->Position.y, lpPlayInfo->Position.z, lpPlayInfo, 0);
			if(lpChar)
			{
				lpChar->dwUpdateCharInfoTime = dwPlayServTime + 355 * 1000;
				lpChar->smCharInfo.Attack_Damage[0] = Fire_Elemental_Damage[point][0];
				lpChar->smCharInfo.Attack_Damage[1] = Fire_Elemental_Damage[point][1];
				lpChar->smCharInfo.Attack_Rating = Fire_Elemental_Hit[point];
				lpChar->smCharInfo.Life[0] = Fire_Elemental_Life[point];
				lpChar->smCharInfo.Life[1] = Fire_Elemental_Life[point];

				lpChar->sMoveStepCount[0] = 1;
				lpChar->sMoveStepCount[1] = 2;

			}
		}
		break;

	}

	return TRUE;
}



int rsProcessAttack_SkillHolyReflection(rsPLAYINFO *lpPlayInfo, smCHAR *lpChar)
{
	int pow;
	smTRANS_COMMAND	smTransCommand;
	int rs;

	if(!lpPlayInfo->dwSkill_HolyReflection_Time) return TRUE;

	if(lpPlayInfo->dwSkill_HolyReflection_Time < dwPlayServTime)
	{
		lpPlayInfo->dwSkill_HolyReflection_Time = 0;
		return TRUE;
	}

	if(lpChar->smCharInfo.Brood != smCHAR_MONSTER_UNDEAD) return TRUE;


	pow = GetRandomPos(lpChar->smCharInfo.Attack_Damage[0], lpChar->smCharInfo.Attack_Damage[1]);
	pow = (pow*lpPlayInfo->dwSkill_HolyReflection_Param) / 100;
	rs = lpChar->smCharInfo.Resistance[sITEMINFO_BIONIC];
	if(rs)
	{
		if(rs >= 100) rs = 100;
		if(rs <= -100) rs = -100;
		pow -= ((pow*rs) / 100);
	}
	pow -= (pow * lpChar->smCharInfo.Absorption) / 100;

	if(pow > 0)
	{

		lpChar->smCharInfo.Life[0] -= pow;

		if(lpChar->smCharInfo.Life[0] > 0)
		{


		}
		else
		{
			lpChar->SetMotionFromCode(CHRMOTION_STATE_DEAD);
			lpChar->lpExt2 = (void *)lpPlayInfo;
		}
	}

	if(lpPlayInfo->lpsmSock)
	{
		smTransCommand.code = OpCode::OPCODE_PROCESS_SKILL;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = SKILL_PLAY_HOLY_REFLECTION;
		smTransCommand.LParam = pow;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = 0;
		lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
	}


	return TRUE;
}




int rsClanUpdate(rsPLAYINFO *lpPlayInfo, TRANS_CLAN_COMMAND_USER *lpTransClanUser)
{
	rsCLAN_INFOMATION	ClanInfomation;
	smTRANS_COMMAND		smTransCommand;
	int	cnt;
	rsPLAYINFO	*lpPlayInfo2;


	if(RecvClanCommand(lpTransClanUser, ClanInfomation.ClanUserInfo) == TRUE)
	{
		ZeroMemory(&smTransCommand, sizeof(smTRANS_COMMAND));
		smTransCommand.code = OpCode::OPCODE_CLAN_UPDATE;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = lpPlayInfo->dwObjectSerial;

		for(cnt = 0; cnt < lpTransClanUser->UserCount; cnt++)
		{
			lpPlayInfo2 = FindUserFromCodeName(ClanInfomation.ClanUserInfo[cnt].szName, ClanInfomation.ClanUserInfo[cnt].dwSpeedSum);
			if(lpPlayInfo2)
			{

				lpPlayInfo2->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
			}
		}
	}

	return TRUE;
}


int rsRecvYahooMotion(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	int cnt;
	STG_AREA	*lpStgArea;
	smCHAR		*lpCharList[srCLAN_MONSTER_MAX];
	int			ClanMonCount = 0;
	int			ClanPoint;
	int			x, y, z, dist;


	if(lpPlayInfo->dwClanCode && lpPlayInfo->Position.Area >= 0 && lpPlayInfo->Position.Area < STAGE_AREA_MAX)
	{

		lpStgArea = &StageArea[lpPlayInfo->Position.Area];

		for(cnt = 0; cnt < STG_MONSTER_MAX; cnt++)
		{
			if(lpStgArea->lpCharMonster[cnt] && lpStgArea->lpCharMonster[cnt]->smCharInfo.ClassClan == lpPlayInfo->smCharInfo.ClassClan)
			{
				if(ClanMonCount >= srCLAN_MONSTER_MAX) break;

				x = (lpPlayInfo->Position.x - lpStgArea->lpCharMonster[cnt]->pX) >> FLOATNS;
				y = (lpPlayInfo->Position.y - lpStgArea->lpCharMonster[cnt]->pY) >> FLOATNS;
				z = (lpPlayInfo->Position.z - lpStgArea->lpCharMonster[cnt]->pZ) >> FLOATNS;
				dist = x*x + y*y + z*z;

				if(dist < DIST_TRANSLEVEL_LOW)
					lpCharList[ClanMonCount++] = lpStgArea->lpCharMonster[cnt];
			}
		}

		if(ClanMonCount)
		{

			ClanPoint = (lpPlayInfo->smCharInfo.Level >> 2) / ClanMonCount;
			if(ClanPoint == 0) ClanPoint = 1;

			for(cnt = 0; cnt < ClanMonCount; cnt++)
			{
				if(lpCharList[cnt]->smCharInfo.Life[0] > 0)
				{
					lpCharList[cnt]->smCharInfo.Life[0] += ClanPoint;
					if(lpCharList[cnt]->smCharInfo.Life[0] > lpCharList[cnt]->smCharInfo.Life[1])
						lpCharList[cnt]->smCharInfo.Life[0] = lpCharList[cnt]->smCharInfo.Life[1];
				}
			}
		}
	}

	return TRUE;
}


smCHAR *rsFindAroundMonster(smCHAR *lpChar, int RoundDist)
{
	STG_AREA	*lpStgArea;
	int cnt;
	int x, y, z, dist;
	int ddist2;

	ddist2 = RoundDist*RoundDist;

	lpStgArea = (STG_AREA *)lpChar->lpExt4;
	if(lpStgArea)
	{
		for(cnt = 0; cnt < STG_MONSTER_MAX; cnt++)
		{
			if(lpStgArea->lpCharMonster[cnt] && lpStgArea->lpCharMonster[cnt] != lpChar &&
				!lpStgArea->lpCharMonster[cnt]->PlayHolyPower[1] &&
				lpStgArea->lpCharMonster[cnt]->smCharInfo.Life[0] > 0)
			{

				x = (lpStgArea->lpCharMonster[cnt]->pX - lpChar->pX) >> FLOATNS;
				y = (lpStgArea->lpCharMonster[cnt]->pY - lpChar->pY) >> FLOATNS;
				z = (lpStgArea->lpCharMonster[cnt]->pZ - lpChar->pZ) >> FLOATNS;
				dist = x*x + z*z;

				if(abs(y) < 80 && dist < ddist2)
				{
					return lpStgArea->lpCharMonster[cnt];
				}
			}
		}
	}

	return NULL;
}




smCHAR *rsSkillDamage_AroundMonster(smCHAR *lpChar)
{
	STG_AREA	*lpStgArea;
	int cnt;
	int x, y, z, dist;
	int ddist2;
	smCHAR *lpTargetChar;

	int RoundDist = lpChar->smMonsterInfo.SkillRange;
	int	pw, pow;

	ddist2 = RoundDist*RoundDist;
	pow = GetRandomPos(lpChar->smMonsterInfo.SkillDamage[0], lpChar->smMonsterInfo.SkillDamage[1]);

	lpStgArea = (STG_AREA *)lpChar->lpExt4;
	if(lpStgArea)
	{
		for(cnt = 0; cnt < STG_MONSTER_MAX; cnt++)
		{
			if(lpStgArea->lpCharMonster[cnt] && lpStgArea->lpCharMonster[cnt] != lpChar && lpStgArea->lpCharMonster[cnt]->smCharInfo.Life[0] > 0)
			{

				x = (lpStgArea->lpCharMonster[cnt]->pX - lpChar->pX) >> FLOATNS;
				y = (lpStgArea->lpCharMonster[cnt]->pY - lpChar->pY) >> FLOATNS;
				z = (lpStgArea->lpCharMonster[cnt]->pZ - lpChar->pZ) >> FLOATNS;
				dist = x*x + z*z;

				if(abs(y) < 80 && dist < ddist2)
				{

					lpTargetChar = lpStgArea->lpCharMonster[cnt];

					if(lpChar->smCharInfo.ClassClan != 0 && lpChar->smCharInfo.ClassClan == lpTargetChar->smCharInfo.ClassClan)
					{
						pw = 0;
					}
					else
					{
						pw = pow;
						pw -= (pow*lpTargetChar->smCharInfo.Absorption) / 100;
					}

					if(pw > 0)
					{
						lpTargetChar->smCharInfo.Life[0] -= pw;
						if(lpTargetChar->smCharInfo.Life[0] <= 0)
						{
							lpTargetChar->smCharInfo.Life[0] = 0;
							lpTargetChar->SetMotionFromCode(CHRMOTION_STATE_DEAD);
							if(lpChar->lpMasterPlayInfo && lpChar->lpMasterPlayInfo->lpsmSock && lpChar->lpMasterPlayInfo->dwObjectSerial && lpChar->lpMasterPlayInfo->dwObjectSerial == lpChar->smCharInfo.Next_Exp)
							{
								lpTargetChar->lpExt2 = lpChar->lpMasterPlayInfo;
								lpTargetChar->smMonsterInfo.GetExp >>= 1;
								lpTargetChar->lpExt3 = lpChar;
							}
							else
							{
								if(lpChar->lpMasterPlayInfo)
								{

									lpChar->smCharInfo.Life[0] = 0;
									lpChar->SetMotionFromCode(CHRMOTION_STATE_DEAD);
								}
								else
								{
									lpChar->lpTargetChar = 0;
								}
							}
						}
						else
						{
							if(lpTargetChar->MotionInfo->State != CHRMOTION_STATE_DEAD)
							{
								lpTargetChar->SetMotionFromCode(CHRMOTION_STATE_DAMAGE);
							}
						}
					}

				}
			}
		}
	}

	return NULL;
}


smCHAR *rsSkillMonster_AroundMonster(smCHAR *lpChar, int RoundDist)
{
	STG_AREA	*lpStgArea;
	int cnt;
	int x, y, z, dist;
	int ddist2;
	smCHAR *lpTargetChar;

	ddist2 = RoundDist*RoundDist;

	lpStgArea = (STG_AREA *)lpChar->lpExt4;
	if(lpStgArea)
	{
		for(cnt = 0; cnt < STG_MONSTER_MAX; cnt++)
		{
			if(lpStgArea->lpCharMonster[cnt] && lpStgArea->lpCharMonster[cnt] != lpChar && lpStgArea->lpCharMonster[cnt]->smCharInfo.Life[0] > 0)
			{

				x = (lpStgArea->lpCharMonster[cnt]->pX - lpChar->pX) >> FLOATNS;
				y = (lpStgArea->lpCharMonster[cnt]->pY - lpChar->pY) >> FLOATNS;
				z = (lpStgArea->lpCharMonster[cnt]->pZ - lpChar->pZ) >> FLOATNS;
				dist = x*x + z*z;

				if(abs(y) < 80 && dist < ddist2)
				{
					if(lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_RATOO)
					{
						lpTargetChar = lpStgArea->lpCharMonster[cnt];
						lpTargetChar->PlayStunCount = 0;
					}
				}
			}
		}
	}

	return NULL;
}




int	rsSendMoneyToUser(rsPLAYINFO *lpPlayInfo, int Money)
{
	TRANS_ITEMINFO	TransItemInfo;


	ZeroMemory(&TransItemInfo, sizeof(TRANS_ITEMINFO));

	TransItemInfo.code = OpCode::OPCODE_PUTITEM;
	TransItemInfo.size = sizeof(TRANS_ITEMINFO);
	TransItemInfo.Item.CODE = (sinGG1 | sin01);
	TransItemInfo.Item.Money = Money;
	wsprintf(TransItemInfo.Item.ItemName, sinGold, Money);
	ReformItem(&TransItemInfo.Item);

	lpPlayInfo->spMoney_Out += TransItemInfo.Item.Money;
	TransItemInfo.x = dwPlayServTime;
	TransItemInfo.y = TransItemInfo.Item.ItemHeader.dwChkSum;
	TransItemInfo.z = lpPlayInfo->spMoney_Out ^ (TransItemInfo.x + TransItemInfo.y);

	rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);

	lpPlayInfo->lpsmSock->Send((char *)&TransItemInfo, TransItemInfo.size, TRUE);

	return TRUE;
}





int	rsPutItemToSystemLine(rsPLAYINFO *lpPlayInfo, DWORD dwItemCode)
{
	smTRANS_SYSTEM_COMMAND	TransSystemCommand;
	smWINSOCK	*lpsmSock;

	ZeroMemory(&TransSystemCommand, sizeof(smTRANS_SYSTEM_COMMAND));
	TransSystemCommand.code = OpCode::OPCODE_SYSTEM;
	TransSystemCommand.size = sizeof(smTRANS_SYSTEM_COMMAND);
	TransSystemCommand.tCode = smTRANS_SYSCODE_GET_ITEM;
	TransSystemCommand.dwObjectSerial = rsServerConfig.ServerCode;
	TransSystemCommand.Param[0] = lpPlayInfo->dwObjectSerial;
	TransSystemCommand.Param[1] = dwItemCode;

	lpsmSock = rsFindNextSertoServerSock();

	if(lpsmSock)
		return lpsmSock->Send((char *)&TransSystemCommand, TransSystemCommand.size, TRUE);

	return FALSE;
}


int	rsSendMoneyToSystemLine(rsPLAYINFO *lpPlayInfo, int Money)
{
	smTRANS_SYSTEM_COMMAND	TransSystemCommand;
	smWINSOCK	*lpsmSock;

	ZeroMemory(&TransSystemCommand, sizeof(smTRANS_SYSTEM_COMMAND));
	TransSystemCommand.code = OpCode::OPCODE_SYSTEM;
	TransSystemCommand.size = sizeof(smTRANS_SYSTEM_COMMAND);
	TransSystemCommand.tCode = smTRANS_SYSCODE_GET_MONEY;
	TransSystemCommand.dwObjectSerial = rsServerConfig.ServerCode;
	TransSystemCommand.Param[0] = lpPlayInfo->dwObjectSerial;
	TransSystemCommand.Param[1] = Money;

	lpsmSock = rsFindNextSertoServerSock();

	if(lpsmSock)
		return lpsmSock->Send((char *)&TransSystemCommand, TransSystemCommand.size, TRUE);

	return FALSE;
}



int rsSendCharInfoToLoginServer(rsPLAYINFO *lpPlayInfo)
{

	smTRANS_CHAR_COMMAND	smTransCharCommand;

	if(!dwSerToLogin_Count) return FALSE;

	smTransCharCommand.code = OpCode::OPCODE_SYSTEM;
	smTransCharCommand.size = sizeof(smTRANS_CHAR_COMMAND);
	smTransCharCommand.LParam = smTRANS_SYSCODE_CONNECT_USER;
	smTransCharCommand.WParam = lpPlayInfo->dwObjectSerial;
	smTransCharCommand.SParam = lpPlayInfo->dwCode_Name;
	strcpy_s(smTransCharCommand.szName, lpPlayInfo->smCharInfo.szName);


	return rsSendPacketToLoginLine((char *)&smTransCharCommand, smTransCharCommand.size);
}



int	rsGetSystemLineCount()
{
	int cnt;
	int	LineCount = 0;

	for(cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].SystemLine)
			LineCount++;
	}

	return LineCount;
}




int	rsSetSerToLoginLine()
{
	int	cnt;

	dwSerToLogin_Count = 0;
	dwSerToLogin_Num = 0;

	for(cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].SystemLine == 2)
		{
			if(dwSerToLogin_Count >= SER_TO_LOGIN_SOCKET_MAX) break;
			lpPlayInfo_LoginServer[dwSerToLogin_Count++] = &rsPlayInfo[cnt];
		}
	}

	return dwSerToLogin_Count;
}


int rsSendPacketToLoginLine(char *szBuff, int size)
{
	if(dwSerToLogin_Count == 0) return NULL;
	if(dwSerToLogin_Num >= dwSerToLogin_Count) dwSerToLogin_Num = 0;

	if(lpPlayInfo_LoginServer[dwSerToLogin_Num]->lpsmSock && lpPlayInfo_LoginServer[dwSerToLogin_Num]->SystemLine == 2)
	{
		return lpPlayInfo_LoginServer[dwSerToLogin_Num++]->lpsmSock->Send(szBuff, size, TRUE);
	}

	return FALSE;
}



int rsRecvSystemInfo(rsPLAYINFO *lpPlayInfo, void *Buff)
{
	

	return TRUE;
}



int	rsPushKillMonster(smCHAR *lpChar, rsPLAYINFO *lpPlayInfo, STG_AREA *lpStgArea)
{
	int cnt;

	if(!dwSerToSerIP) return FALSE;

	if((rsKillMonster_Push - rsKillMonster_Pop) >= srMONSTER_KILL_QUE_MASK)
	{


		return TRUE;
	}

	cnt = rsKillMonster_Push&srMONSTER_KILL_QUE_MASK;

	rsKillMonster_Que[cnt].dwAutoCharCode = lpChar->smMonsterInfo.dwAutoCharCode;
	rsKillMonster_Que[cnt].dwCharSoundCode = lpChar->smCharInfo.dwCharSoundCode;
	rsKillMonster_Que[cnt].dwMonObjectSerial = lpChar->dwObjectSerial;

	rsKillMonster_Que[cnt].x = lpChar->pX;
	rsKillMonster_Que[cnt].y = lpChar->pY;
	rsKillMonster_Que[cnt].z = lpChar->pZ;

	rsKillMonster_Que[cnt].PartyFlag = lpChar->PartyFlag;

	if(lpPlayInfo)
		rsKillMonster_Que[cnt].dwUserObjectSerial = lpPlayInfo->dwObjectSerial;
	else
		rsKillMonster_Que[cnt].dwUserObjectSerial = 0;

	if(lpStgArea && lpStgArea->lpField)
		rsKillMonster_Que[cnt].Area = lpStgArea->lpField->FieldCode;
	else
		rsKillMonster_Que[cnt].Area = -1;


	rsKillMonster_Que[cnt].dwParam[0] = 0;
	rsKillMonster_Que[cnt].dwParam[1] = 0;
	rsKillMonster_Que[cnt].dwParam[2] = 0;
	rsKillMonster_Que[cnt].dwParam[3] = 0;

	if(rsKillMonster_Que[cnt].PartyFlag == rsHARDCORE_EVENT_FLAG)
	{
		rsKillMonster_Que[cnt].dwParam[0] = lpChar->PartyParam;
	}

	rsKillMonster_Push++;

	return TRUE;
}

int	rsSendKillMonsterInfo(smWINSOCK *lpsmSock)
{
	char	szBuff[4096];
	TRANS_KILL_MONSTER_INFO	*lpTransKillMonInfo = (TRANS_KILL_MONSTER_INFO *)szBuff;
	rsKILL_MONSTER_INFO	*lpKillMonInfo = (rsKILL_MONSTER_INFO *)(szBuff + sizeof(TRANS_KILL_MONSTER_INFO));

	int	cnt, mCnt;


	mCnt = 0;

	while(1)
	{
		if(rsKillMonster_Pop == rsKillMonster_Push) break;
		if(mCnt > 48) break;

		cnt = rsKillMonster_Pop&srMONSTER_KILL_QUE_MASK;

		memcpy(lpKillMonInfo, &rsKillMonster_Que[cnt], sizeof(rsKILL_MONSTER_INFO));

		lpKillMonInfo++;
		rsKillMonster_Pop++;
		mCnt++;
	}

	if(!mCnt) return FALSE;

	lpTransKillMonInfo->size = sizeof(TRANS_KILL_MONSTER_INFO) + sizeof(rsKILL_MONSTER_INFO)*mCnt;
	lpTransKillMonInfo->code = OpCode::OPCODE_SYSTEM;
	lpTransKillMonInfo->tCode = smTRANS_SYSCODE_KILL_MONSTER;
	lpTransKillMonInfo->KillInfo_Count = mCnt;
	lpTransKillMonInfo->Temp[0] = 0;
	lpTransKillMonInfo->Temp[1] = 0;
	lpTransKillMonInfo->Temp[2] = 0;
	lpTransKillMonInfo->Temp[3] = 0;

	if(lpsmSock) lpsmSock->Send((char *)lpTransKillMonInfo, lpTransKillMonInfo->size, TRUE);

	return mCnt;
}


smWINSOCK	*rsFindNextSertoServerSock()
{
	int cnt;
	smWINSOCK	*lpsmSock;

	for(cnt = 0; cnt < SER_TO_SERVER_SOCKET_MAX; cnt++)
	{
		lpsmSock = lpsmSock_SerToServer[(cnt + dwSerToSer_Count)&SER_TO_SERVER_SOCKET_MASK];
		if(lpsmSock) return lpsmSock;
	}

	return NULL;
}



DWORD WINAPI rsTransServerMain_Thread(void *pInfo)
{
	HANDLE	hThread;
	DWORD	dwTime;
	int		cnt;
	int		Count;
	smWINSOCK	*lpsmSock;
	smTRANS_SYSTEM_COMMAND	TransSystemCommand;
	rsPLAYINFO	*lpPlayInfo;

	hThread = GetCurrentThread();
	dwTime = GetCurrentTime();
	Count = 0;

	while(1)
	{
		Sleep(200);
		if(quit) break;
		if(!dwSerToSerIP) continue;

		EnterCriticalSection(&cSerSection);


		for(cnt = 0; cnt < SER_TO_SERVER_SOCKET_MAX; cnt++)
		{
			if(!lpsmSock_SerToServer[cnt] || lpsmSock_SerToServer[cnt]->acc_sin.sin_addr.S_un.S_addr != dwSerToSerIP)
			{

				LeaveCriticalSection(&cSerSection);
				lpsmSock = smConnectSock3(szSerToSerIP, TCP_SERVPORT);
				if(quit) goto quit_thread;

				if(lpsmSock) Serv_ConnectPlayer(lpsmSock);

				EnterCriticalSection(&cSerSection);

				if(lpsmSock)
				{

					rsSystemLineConnCount++;

					if(lpsmSock_SerToServer[cnt])
					{
						DisconnectUser(lpsmSock_SerToServer[cnt]);
					}
					lpsmSock_SerToServer[cnt] = lpsmSock;

					lpPlayInfo = (rsPLAYINFO *)lpsmSock->ExtData1;
					if(lpPlayInfo) lpPlayInfo->SystemLine = TRUE;

					ZeroMemory(&TransSystemCommand, sizeof(smTRANS_SYSTEM_COMMAND));
					TransSystemCommand.code = OpCode::OPCODE_SYSTEM;
					TransSystemCommand.size = sizeof(smTRANS_SYSTEM_COMMAND);
					TransSystemCommand.tCode = smTRANS_SYSCODE_CONNECT;
					TransSystemCommand.dwObjectSerial = rsServerConfig.ServerCode;
					lpsmSock->Send((char *)&TransSystemCommand, TransSystemCommand.size, TRUE);
				}
			}
		}


		dwTime = GetCurrentTime();

		if((Count & 0x1F) == 0)
		{
			ZeroMemory(&TransSystemCommand, sizeof(smTRANS_SYSTEM_COMMAND));
			TransSystemCommand.code = OpCode::OPCODE_SYSTEM;
			TransSystemCommand.size = sizeof(smTRANS_SYSTEM_COMMAND);
			TransSystemCommand.tCode = smTRANS_SYSCODE_NETSTATE;

			for(cnt = 0; cnt < SER_TO_SERVER_SOCKET_MAX; cnt++)
			{
				if(lpsmSock_SerToServer[cnt])
				{
					if((lpsmSock_SerToServer[cnt]->dwDeadLockTime + (1000 * 45)) < dwTime)
					{

						DisconnectUser(lpsmSock_SerToServer[cnt]);
						lpsmSock_SerToServer[cnt] = 0;
						rsSystemLineFailedCount++;
					}
					else
					{
						lpsmSock_SerToServer[cnt]->Send((char *)&TransSystemCommand, TransSystemCommand.size, TRUE);
					}
				}
			}
		}



		for(cnt = 0; cnt < 32; cnt++)
		{
			lpsmSock = rsFindNextSertoServerSock();
			if(!lpsmSock || rsSendKillMonsterInfo(lpsmSock) == FALSE) break;
			dwSerToSer_Count++;
		}

		LeaveCriticalSection(&cSerSection);

		Count++;
	}

quit_thread:

	ExitThread(TRUE);
	return TRUE;
}



int rsInit_SerToServer()
{


	return TRUE;
}


int	rsDisconnectSystemLine(smWINSOCK *lpsmSock)
{
	int cnt;

	for(cnt = 0; cnt < SER_TO_SERVER_SOCKET_MAX; cnt++)
	{
		if(lpsmSock_SerToServer[cnt] == lpsmSock)
		{
			lpsmSock_SerToServer[cnt] = 0;
			return TRUE;
		}
	}

	return FALSE;
}



int	rsSaveAdminCommand(rsPLAYINFO *lpPlayInfo, char *szChatCommand, int Level)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];
	int		len;

	if(!lpPlayInfo->lpsmSock) return FALSE;

	CreateDirectory(AdminLogDirectory, NULL);

	GetLocalTime(&st);


	wsprintf(szBuff, "%d:%d:%d - ID( %s ) Name( %s ) IP( %s ) AdminLv( %d )> %s\r\n",
		st.wHour, st.wMinute, st.wSecond,
		lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(), lpPlayInfo->lpsmSock->szIPAddr, Level, szChatCommand);

	len = lstrlen(szBuff);

#ifdef _LANGUAGE_KOREAN				
	wsprintf(szFileName, "%s\\(Admin)%d-%d.xog", AdminLogDirectory, st.wMonth, st.wDay);
	for(int cnt = 0; cnt < len; cnt++)
	{
		szBuff[cnt] = szBuff[cnt] ^ 0x55;
	}
#else
	wsprintf(szFileName, "%s\\(Admin)%d-%d.log", AdminLogDirectory, st.wMonth, st.wDay);
#endif

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, len, &dwAcess, NULL);
	CloseHandle(hFile);


	return TRUE;
}


int	rsRecordAdminCommand(rsPLAYINFO *lpPlayInfo, char *szChatCommand, int Level)
{
	TRANS_CHATMESSAGE	TransChatMessage;

	if(!rsServerConfig.RecordAdminCommand) return FALSE;
	if(Level > rsServerConfig.RecordAdminCommand) return FALSE;

	if(LoginServer)
	{
		rsSaveAdminCommand(lpPlayInfo, szChatCommand, (int)lpPlayInfo->getSecurity());
		return TRUE;
	}

	strcpy_s(TransChatMessage.szMessage, szChatCommand);
	TransChatMessage.dwIP = (int)lpPlayInfo->getSecurity();
	TransChatMessage.dwObjectSerial = lpPlayInfo->dwObjectSerial;
	TransChatMessage.size = lstrlen(TransChatMessage.szMessage) + 32;
	TransChatMessage.code = OpCode::OPCODE_REC_ADMIN_COMMAND;

	return rsSendDataServer(lpPlayInfo->lpsmSock, &TransChatMessage);
}


AccountTypes getSecurityLevel(rsPLAYINFO *lpPlayInfo)
{
	smWINSOCK *lpsmSock = lpPlayInfo->lpsmSock;

	if(!lpPlayInfo->BlockTime)
		lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->getAccount().c_str(), 1000 * 60 * 60 * 24);

	DisconnectUser(lpsmSock);

	return AccountTypes::SEC_PLAYER;
}


int	rsClanMoneyLOG(rsPLAYINFO *lpPlayInfo, int Money, int RestMoney)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];
	int		len;

	if(!lpPlayInfo->lpsmSock) return FALSE;

	CreateDirectory(HackLogDirectory, NULL);

	GetLocalTime(&st);


	wsprintf(szBuff, "%d:%d:%d - ID( %s ) Name( %s ) IP( %s ) Money( %d ) RestMoney( %d )\r\n",
		st.wHour, st.wMinute, st.wSecond,
		lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str(), lpPlayInfo->lpsmSock->szIPAddr, Money, RestMoney);

	len = lstrlen(szBuff);

	wsprintf(szFileName, "%s\\(ClanMoney)%d-%d.log", HackLogDirectory, st.wMonth, st.wDay);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, len, &dwAcess, NULL);
	CloseHandle(hFile);


	return TRUE;
}


static int	TestStarPoint = 0;
#define	STAR_POINT_PRICE	100000


int rsRecvStarPoint(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{

	int cnt;
	int InvFlag;
	int	StarPoint = 0;
	TRANS_CHATMESSAGE	TransChatMessage;


	if(lpTransCommand->WParam > 0)
	{

		StarPoint = lpTransCommand->WParam / STAR_POINT_PRICE;

		if(lpTransCommand->LParam)
		{

			if(lpPlayInfo->ServerMoney < lpTransCommand->WParam)
			{
				return FALSE;
			}

			lpPlayInfo->SubServerMoney(lpTransCommand->WParam, WHERE_STAR_POINT);



			rsRecord_ItemLog2(lpPlayInfo, sinGG1 | sin01, lpTransCommand->WParam, 0, ITEMLOG_BUYSTAR);

		}
		else
		{

			InvFlag = 0;


			for(cnt = 0; cnt < INVEN_ITEM_INFO_MAX; cnt++)
			{
				if(lpPlayInfo->InvenItemInfo[cnt].dwCode == (sinGF1 | sin01))
				{


					rsRecord_ItemLog2(lpPlayInfo, lpPlayInfo->InvenItemInfo[cnt].dwCode,
						lpPlayInfo->InvenItemInfo[cnt].dwKey, lpPlayInfo->InvenItemInfo[cnt].dwSum, ITEMLOG_BUYSTAR);

					lpPlayInfo->InvenItemInfo[cnt].dwCode = 0;
					InvFlag++;
				}
			}
			if(InvFlag == 0) return FALSE;
		}

		if(bSql_StarPoint(lpPlayInfo, StarPoint, lpTransCommand->LParam) == FALSE)
		{


			TestStarPoint += lpTransCommand->WParam / STAR_POINT_PRICE;
			lpTransCommand->WParam = TestStarPoint;

			if(lpPlayInfo->lpsmSock)
				lpPlayInfo->lpsmSock->Send((char *)lpTransCommand, sizeof(smTRANS_COMMAND), TRUE);
		}

		if(StarPoint > 0)
		{
			TransChatMessage.code = OpCode::OPCODE_MESSAGEBOX;
			TransChatMessage.dwIP = 0;
			TransChatMessage.dwObjectSerial = 0;
			wsprintf(TransChatMessage.szMessage, srMsg_400, StarPoint);
			TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
			lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
		}
	}
	else
	{
		if(bSql_StarPoint(lpPlayInfo, StarPoint, lpTransCommand->LParam) == FALSE)
		{
			lpTransCommand->WParam = TestStarPoint;
			if(lpPlayInfo->lpsmSock)
				lpPlayInfo->lpsmSock->Send((char *)lpTransCommand, sizeof(smTRANS_COMMAND), TRUE);
		}
	}

	return TRUE;
}


static int	TestSodClanCash = 0;


int rsRecvSodClanCash(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{



	int cash, kind;

	cash = lpTransCommand->WParam;
	kind = lpTransCommand->SParam;


	if(cash > 0)
	{
		if(bSql_ClanMoney(lpPlayInfo, cash, 1, kind) == FALSE)
		{
			if(lpPlayInfo->getSecurity() > AccountTypes::SEC_VIP)
			{

				if(TestSodClanCash < cash)
				{

					return FALSE;
				}

				lpPlayInfo->AddServerMoney(cash, WHERE_CLAN_MONEY);
				TestSodClanCash -= cash;

				lpTransCommand->WParam = TestSodClanCash;
				lpTransCommand->LParam = cash;


				rsClanMoneyLOG(lpPlayInfo, cash, TestSodClanCash);

				if(lpPlayInfo->lpsmSock)
					lpPlayInfo->lpsmSock->Send((char *)lpTransCommand, sizeof(smTRANS_COMMAND), TRUE);
			}
		}
	}
	else
	{

		if(bSql_ClanMoney(lpPlayInfo, 0, 0, kind) == FALSE)
		{
			lpTransCommand->WParam = TestSodClanCash;
			lpTransCommand->LParam = 0;
			if(lpPlayInfo->lpsmSock)
				lpPlayInfo->lpsmSock->Send((char *)lpTransCommand, sizeof(smTRANS_COMMAND), TRUE);
		}
	}

	return TRUE;
}




int rsRecvGiveMoney(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{

	TRANS_CHATMESSAGE	TransChatMessage;


	if(lpTransCommand->WParam > 0)
	{

		if(lpPlayInfo->ServerMoney < lpTransCommand->WParam)
		{
			return FALSE;
		}
		lpPlayInfo->SubServerMoney(lpTransCommand->WParam, WHERE_GIVE_MONEY);


		bSql_GiveMoney(lpPlayInfo, lpTransCommand->WParam);

		TransChatMessage.code = OpCode::OPCODE_MESSAGEBOX;
		TransChatMessage.dwIP = 0;
		TransChatMessage.dwObjectSerial = 0;
		wsprintf(TransChatMessage.szMessage, srMsg_401, lpTransCommand->WParam);
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);

	}

	return TRUE;
}


int rsRecvPaymentMoney(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	if(lpTransCommand->LParam < 0 || lpTransCommand->LParam>1000000) return FALSE;

	switch(lpTransCommand->WParam)
	{
	case 1:
		CurrencyLog.int64_LearnSkillMoney += lpTransCommand->LParam;
		lpPlayInfo->SubServerMoney(lpTransCommand->LParam, WHERE_LEARNSKILL);
		break;
	case 2:
		CurrencyLog.int64_WarpgateMoney += lpTransCommand->LParam;
		lpPlayInfo->SubServerMoney(lpTransCommand->LParam, WHERE_WARPGATE);
		break;
	}

	return TRUE;
}



int rsEventLogOn_Sucess(rsPLAYINFO *lpPlayInfo)
{

	smTRANS_COMMAND	smTransCommand;


	if((lpPlayInfo->Bl_Meter&BIMASK_BIRTHDAY_USER) != 0)
	{

		if(rsServerConfig.Event_ComicBirthDay == 1)
		{
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.code = OpCode::OPCODE_COMIC_SKIN;
			smTransCommand.WParam = (rand() % 2) + 1;
			smTransCommand.LParam = 60 * 24 * 6;
			smTransCommand.SParam = 0;
			smTransCommand.EParam = 0;
			lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
		}
	}

	if((lpPlayInfo->Bl_Meter&BIMASK_VIP_USER) != 0)
	{

		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = OpCode::OPCODE_CHANGE_EVENT;
		smTransCommand.WParam = lpPlayInfo->Bl_Meter;
		smTransCommand.LParam = lpPlayInfo->Bl_RNo;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = 1;
		lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
	}


	return TRUE;
}



struct	sPUZZLE_ITEM
{
	DWORD	dwItemCode;
	int		Percent;
};

sPUZZLE_ITEM	sPuzzleItem[] = {

	{	(sinPZ1 | sin01)	,	        743	},
	{	(sinPZ1 | sin02)	,	       1466	},
	{	(sinPZ1 | sin03)	,	       2170	},

	{	(sinPZ2 | sin01)	,	       2913	},
	{	(sinPZ2 | sin02)	,	       3636	},
	{	(sinPZ2 | sin03)	,	       4340	},

	{	(sinPZ1 | sin04)	,	       4990	},
	{	(sinPZ1 | sin05)	,	       5290	},
	{	(sinPZ2 | sin04)	,	       5940	},
	{	(sinPZ2 | sin05)	,	       6240	},

	{	(sinPZ1 | sin05)	,	       6590	},
	{	(sinPZ1 | sin06)	,	       6940	},
	{	(sinPZ2 | sin05)	,	       7290	},
	{	(sinPZ2 | sin06)	,	       7640 },

	{	(sinPZ1 | sin06)	,	       7940	},
	{	(sinPZ1 | sin07)	,	       8320	},
	{	(sinPZ2 | sin06)	,	       8620	},
	{	(sinPZ2 | sin07)	,	       9000	},

	{	(sinPZ1 | sin08)	,	       9500	},
	{	(sinPZ2 | sin08)	,	       10000},
	{	0,0	}

};



DWORD rsOpenEventPuzzleItem(rsPLAYINFO *lpPlayInfo, smCHAR *lpChar)
{
	int	cnt;
	int	rnd;

	if(abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level) > 15)
		return NULL;

	if(lpChar->smCharInfo.Level < 20 && abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level)>8)
		return NULL;


	if(lpChar->PartyFlag == rsHARDCORE_EVENT_FLAG) return NULL;

	rnd = rand() % 10000;

	cnt = 0;
	while(1)
	{
		if(!sPuzzleItem[cnt].dwItemCode) break;

		if(rnd < sPuzzleItem[cnt].Percent)
			return sPuzzleItem[cnt].dwItemCode;

		cnt++;
	}

	return NULL;
}


int rsDebugMessageToClient(rsPLAYINFO *lpPlayInfo, char *szDmgMsg)
{
	TRANS_CHATMESSAGE	TransChatMessage;

	if(lpPlayInfo->getSecurity() <= AccountTypes::SEC_MODERATOR) return FALSE;

	strcpy_s(TransChatMessage.szMessage, szDmgMsg);
	TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
	TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
	TransChatMessage.dwIP = 0;
	TransChatMessage.dwObjectSerial = 0;
	lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);

	return TRUE;
}



int	rsTrade_PersonalShop(rsPLAYINFO *lpPlayInfo, rsPLAYINFO *lpPlayInfo2, smTRANS_COMMAND_BUFF *lpTransCommandBuff)
{
	sMYSHOP_ITEM_SERVER	*lpMyShopItem = (sMYSHOP_ITEM_SERVER *)lpTransCommandBuff->Buff;
	int	cnt, mCnt;
	int PotionFlag;

#ifdef _TEST_SERVER
	char szBuff[256];
#endif

	switch(lpMyShopItem->SendFlag)
	{

	case 1:
		if(lpMyShopItem->Price > MAX_MONEY) return FALSE;
		if(lpPlayInfo->dwMyShopTradeTime > dwPlayServTime)
		{
#ifdef _TEST_SERVER

			rsDebugMessageToClient(lpPlayInfo, "> 개인상점 구입 대기 오류");
#endif
			return FALSE;
		}

		PotionFlag = TRUE;


		if((lpMyShopItem->CODE&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
		{
			if(rsGetServerPotion(lpPlayInfo2, lpMyShopItem->CODE) < (int)lpMyShopItem->sTime)
			{


				PotionFlag = FALSE;
			}
		}
#ifdef _TEST_SERVER

		rsDebugMessageToClient(lpPlayInfo, "> 개인상점 구입 신청");

		wsprintf(szBuff, "> 개인상점 구입 신청 ( %d %d )", lpPlayInfo->dwMyShopTradeTime / 1000, dwPlayServTime / 1000);
		rsDebugMessageToClient(lpPlayInfo, szBuff);

#endif

		if(rsFindInvenItem(lpPlayInfo2, lpMyShopItem->CODE, lpMyShopItem->Head, lpMyShopItem->CkSum) >= 0 &&
			lpPlayInfo->ServerMoney >= (int)lpMyShopItem->Price && PotionFlag == TRUE)
		{

			lpPlayInfo->dwMyShopTradeTime = dwPlayServTime + 500;
#ifdef _TEST_SERVER

			wsprintf(szBuff, "> 개인상점 구입 대기 ( %d %d )", lpPlayInfo->dwMyShopTradeTime / 1000, dwPlayServTime / 1000);
			rsDebugMessageToClient(lpPlayInfo, szBuff);
#endif

			if(lpPlayInfo->MyShopListCount == 0)
			{
				ZeroMemory(lpPlayInfo->sMyShopList, sizeof(sMYSHOP_SELL_INFO)*MYSHOP_LIST_MAX);
			}
			else
			{
				for(cnt = 0; cnt < MYSHOP_LIST_MAX; cnt++)
				{
					if(lpPlayInfo->sMyShopList[cnt].dwCode &&
						lpMyShopItem->CODE == lpPlayInfo->sMyShopList[cnt].dwCode &&
						lpMyShopItem->Head == lpPlayInfo->sMyShopList[cnt].dwHead &&
						lpMyShopItem->CkSum == lpPlayInfo->sMyShopList[cnt].dwChkSum &&
						lpMyShopItem->Price == lpPlayInfo->sMyShopList[cnt].Price)
					{
						return TRUE;
					}
				}
			}

			mCnt = lpPlayInfo->MyShopListCount&MYSHOP_LIST_MASK;
			lpPlayInfo->sMyShopList[mCnt].dwCode = lpMyShopItem->CODE;
			lpPlayInfo->sMyShopList[mCnt].dwHead = lpMyShopItem->Head;
			lpPlayInfo->sMyShopList[mCnt].dwChkSum = lpMyShopItem->CkSum;
			lpPlayInfo->sMyShopList[mCnt].Price = lpMyShopItem->Price;
			lpPlayInfo->MyShopListCount++;
			return TRUE;
		}

		if(lpPlayInfo->ServerMoney >= (int)lpMyShopItem->Price)
		{
			lpTransCommandBuff->smTransCommand.LParam = lpPlayInfo2->dwObjectSerial;
			lpTransCommandBuff->smTransCommand.SParam = lpPlayInfo->dwObjectSerial;
			lpMyShopItem->SendFlag = 3;
			if(lpPlayInfo->lpsmSock)
				lpPlayInfo->lpsmSock->Send((char *)lpTransCommandBuff, lpTransCommandBuff->smTransCommand.size, TRUE);
		}
		return FALSE;

	case 2:
		if(lpMyShopItem->Price > MAX_MONEY) return FALSE;

		for(cnt = 0; cnt < MYSHOP_LIST_MAX; cnt++)
		{
			if(lpPlayInfo2->sMyShopList[cnt].dwCode &&
				lpMyShopItem->CODE == lpPlayInfo2->sMyShopList[cnt].dwCode &&
				lpMyShopItem->Head == lpPlayInfo2->sMyShopList[cnt].dwHead &&
				lpMyShopItem->CkSum == lpPlayInfo2->sMyShopList[cnt].dwChkSum &&
				lpMyShopItem->Price == lpPlayInfo2->sMyShopList[cnt].Price)
			{
				if(lpPlayInfo2->ServerMoney >= (int)lpMyShopItem->Price)
				{


					if((lpMyShopItem->CODE&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
					{
						if(rsAddServerPotion(lpPlayInfo, lpMyShopItem->CODE, -(int)(lpMyShopItem->sTime)) < 0)
						{

							rsServerPotionErrorLOG(lpPlayInfo, lpMyShopItem->CODE, -(int)lpMyShopItem->sTime, 310);
							return FALSE;
						}
						rsAddServerPotion(lpPlayInfo2, lpMyShopItem->CODE, lpMyShopItem->sTime);
					}

					if(rsDeleteInvenItem(lpPlayInfo, lpMyShopItem->CODE, lpMyShopItem->Head, lpMyShopItem->CkSum) >= 0)
					{

						lpPlayInfo2->SubServerMoney(lpMyShopItem->Price, WHERE_PERSONAL_SHOP);
						lpPlayInfo->AddServerMoney(lpMyShopItem->Price, WHERE_PERSONAL_SHOP);

						rsAddInvenItem(lpPlayInfo2, lpMyShopItem->CODE, lpMyShopItem->Head, lpMyShopItem->CkSum);


						if((lpMyShopItem->CODE&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
						{
							rsRecord_ItemLog_MyShop(lpPlayInfo, lpPlayInfo2,
								lpMyShopItem->CODE, lpMyShopItem->sTime, 0,
								lpMyShopItem->Price);
						}
						else
						{
							rsRecord_ItemLog_MyShop(lpPlayInfo, lpPlayInfo2,
								lpMyShopItem->CODE, lpMyShopItem->Head, lpMyShopItem->CkSum,
								lpMyShopItem->Price);
						}

						return TRUE;
					}
				}
				break;
			}
		}
		return FALSE;

	}

#ifdef _TEST_SERVER

	wsprintf(szBuff, "> 개인상점 메세지 ( %d )", lpMyShopItem->SendFlag);
	rsDebugMessageToClient(lpPlayInfo2, szBuff);
#endif


	return TRUE;
}

//Vl
int	rsUseLovelyItem(rsPLAYINFO* lpPlayInfo, DWORD	dwItemCode)
{

	int	JobCode;
	int Level = 0;
	smTRANS_COMMAND	smTransCommand;

	JobCode = lpPlayInfo->smCharInfo.JOB_CODE;

	switch (dwItemCode)
	{
	case (sinCH1 | sin01):

		if (JobCode == JOBCODE_ATALANTA || JobCode == JOBCODE_ARCHER || JobCode == JOBCODE_PRIESTESS || JobCode == JOBCODE_ASSASSINE)
			return FALSE;
		Level = 4;
		break;

	case (sinCH1 | sin02):

		if (JobCode == JOBCODE_ATALANTA || JobCode == JOBCODE_ARCHER || JobCode == JOBCODE_PRIESTESS || JobCode == JOBCODE_ASSASSINE)
			return FALSE;
		Level = 7;

		break;

	case (sinCH1 | sin03):
		if (JobCode == JOBCODE_FIGHTER || JobCode == JOBCODE_MECHANICIAN || JobCode == JOBCODE_PIKEMAN || JobCode == JOBCODE_KNIGHT || JobCode == JOBCODE_MAGICIAN || JobCode == JOBCODE_SHAMAN)
			return FALSE;
		Level = 4;
		break;

	case (sinCH1 | sin04):
		if (JobCode == JOBCODE_FIGHTER || JobCode == JOBCODE_MECHANICIAN || JobCode == JOBCODE_PIKEMAN || JobCode == JOBCODE_KNIGHT || JobCode == JOBCODE_MAGICIAN || JobCode == JOBCODE_SHAMAN)
			return FALSE;
		Level = 8;
		break;

	}

	if (Level == 0) return FALSE;

	smTransCommand.code = OpCode::OPCODE_PROCESS_SKILL2;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = SKILL_PLAY_LOVELY_LIFE;
	smTransCommand.LParam = lpPlayInfo->dwObjectSerial;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	lpPlayInfo->dwSkill_VirtualLife_Time = dwPlayServTime + Virtual_Life_Time[Level - 1] * 1000;
	lpPlayInfo->dwSkill_VirtualLife_Param = Virtual_Life_Percent[Level - 1];
	smTransCommand.WParam |= (Level << 9);
	rsSendCommandUser2(lpPlayInfo, &smTransCommand);


	return TRUE;
}



static int	Babel_LifeRegenTable[10][2] = {
	{	1800	,	2300	},
	{	1900	,	2400	},
	{	2000	,	2550	},
	{	2150	,	2650	},
	{	2300	,	2800	},
	{	2400	,	2900	},
	{	2500	,	3000	},
	{	2600	,	3100	},
	{	2700	,	3200	},
	{	2800	,	3300	}
};


int rsGetMonsterLifeRegen(smCHAR *lpChar)
{
	int cnt;
	rsPLAYINFO *lpPlayInfo;
	STG_AREA	*lpStgArea = (STG_AREA *)lpChar->lpExt1;
	int x, y, z, dist;
	int NearUserCnt;
	int dRange;
	rsPLAYINFO	*lpDebugPlayInfo = 0;
	int	RegenLife;

	if(lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_BABEL)
	{

		dRange = 260 * 260;
		NearUserCnt = 0;

		for(cnt = 0; cnt < CONNECTMAX; cnt++)
		{
			lpPlayInfo = &rsPlayInfo[cnt];
			if(lpPlayInfo->lpsmSock && lpPlayInfo->dwObjectSerial && lpPlayInfo->Position.Area == lpStgArea->lpField->FieldCode)
			{

				x = (lpChar->pX - lpPlayInfo->Position.x) >> FLOATNS;
				y = (lpChar->pY - lpPlayInfo->Position.y) >> FLOATNS;
				z = (lpChar->pZ - lpPlayInfo->Position.z) >> FLOATNS;
				dist = x*x + z*z;

				if(abs(y) < 60 && dist < dRange && abs(x) < TRANS_VIEW_LIMIT && abs(z) < TRANS_VIEW_LIMIT)
				{
					NearUserCnt++;

					if(lpPlayInfo->getSecurity() >= AccountTypes::SEC_GAMEMASTER)
						lpDebugPlayInfo = lpPlayInfo;
				}
			}
		}

		cnt = 0;
		if(NearUserCnt > 6)
		{
			if(NearUserCnt > 15)
				cnt = 9;
			else
				cnt = NearUserCnt - 6;
		}

		if(lpChar->smCharInfo.Life[0] < (lpChar->smCharInfo.Life[1] / 5))
			RegenLife = Babel_LifeRegenTable[cnt][1];
		else
			RegenLife = Babel_LifeRegenTable[cnt][0];

#ifdef _LANGUAGE_KOREAN
		if(lpDebugPlayInfo)
		{
			TRANS_CHATMESSAGE	TransChatMessage;

			wsprintf(TransChatMessage.szMessage, "바벨 생명 재생 ( 주변:%d명 ) ( 재생력:%d )", NearUserCnt, RegenLife);
			TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
			TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
			TransChatMessage.dwIP = 0;
			TransChatMessage.dwObjectSerial = 0;
			lpDebugPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
		}
#endif
		return RegenLife;
	}

	return 0;
}


int rsSendRangeDamage(smCHAR *lpChar, rsPLAYINFO *lpMainPlayInfo, int Range, int SubDamgePers)
{
	int cnt;
	rsPLAYINFO *lpPlayInfo;
	STG_AREA	*lpStgArea = (STG_AREA *)lpChar->lpExt1;
	int x, y, z, dist;
	int dRange = Range*Range;
	int BackDamge[2];

	int		UserCount = 0;
	rsPLAYINFO	*lpUserList[16];

	int		sndUserCount = 0;
	rsPLAYINFO	*lpSndUserList[128];


	if(!lpStgArea || !lpStgArea->lpField) return FALSE;


	lpUserList[UserCount++] = lpMainPlayInfo;
	lpSndUserList[sndUserCount++] = lpMainPlayInfo;

	for(cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		lpPlayInfo = &rsPlayInfo[cnt];
		if(lpPlayInfo->lpsmSock && lpPlayInfo->dwObjectSerial && lpPlayInfo->Position.Area == lpStgArea->lpField->FieldCode && lpPlayInfo != lpMainPlayInfo)
		{

			x = (lpMainPlayInfo->Position.x - lpPlayInfo->Position.x) >> FLOATNS;
			y = (lpMainPlayInfo->Position.y - lpPlayInfo->Position.y) >> FLOATNS;
			z = (lpMainPlayInfo->Position.z - lpPlayInfo->Position.z) >> FLOATNS;
			dist = x*x + z*z;

			if(abs(y) < 60 && dist < dRange && abs(x) < TRANS_VIEW_LIMIT && abs(z) < TRANS_VIEW_LIMIT)
			{
				if(UserCount < 16)
					lpUserList[UserCount++] = lpPlayInfo;
			}

			if(dist < DIST_TRANSLEVEL_HIGH && abs(x) < TRANS_VIEW_LIMIT && abs(z) < TRANS_VIEW_LIMIT)
			{
				if(sndUserCount < 128)
					lpSndUserList[sndUserCount++] = lpPlayInfo;
			}

		}
	}

	BackDamge[0] = lpChar->smCharInfo.Attack_Damage[0];
	BackDamge[1] = lpChar->smCharInfo.Attack_Damage[1];

	lpChar->smCharInfo.Attack_Damage[0] = (lpChar->smCharInfo.Attack_Damage[0] * SubDamgePers) / fONE;
	lpChar->smCharInfo.Attack_Damage[1] = (lpChar->smCharInfo.Attack_Damage[1] * SubDamgePers) / fONE;


	for(cnt = 0; cnt < UserCount; cnt++)
	{
		if(lpUserList[cnt] != lpMainPlayInfo)
			lpChar->SendTransAttack(0, lpUserList[cnt]->lpsmSock, 0);
	}


	lpChar->smCharInfo.Attack_Damage[0] = BackDamge[0];
	lpChar->smCharInfo.Attack_Damage[1] = BackDamge[1];

	TRANS_SKIL_ATTACKDATA	TransSkillAttackData;
	ZeroMemory(&TransSkillAttackData, sizeof(TRANS_SKIL_ATTACKDATA));

	TransSkillAttackData.size = sizeof(TRANS_SKIL_ATTACKDATA) - (sizeof(DWORD)*(SKIL_ATTACK_CHAR_MAX - UserCount));
	if(UserCount > 0 && TransSkillAttackData.size > 32)
	{
		TransSkillAttackData.code = OpCode::OPCODE_ATTACK_SLASH_LIST;
		TransSkillAttackData.dwDestObjectSerial = lpChar->dwObjectSerial;
		TransSkillAttackData.TargetCount = UserCount;
		for(cnt = 0; cnt < UserCount; cnt++)
		{
			TransSkillAttackData.dwTarObjectSerial[cnt] = lpUserList[cnt]->dwObjectSerial;
		}
		for(cnt = 0; cnt < sndUserCount; cnt++)
		{
			if(lpSndUserList[cnt]->lpsmSock)
				lpSndUserList[cnt]->lpsmSock->Send((char *)&TransSkillAttackData, TransSkillAttackData.size, TRUE);
		}
	}

	return TRUE;
}



int	rsMorifEventMessage(smCHAR *lpChar)
{
#ifdef _W_SERVER
	TRANS_CHATMESSAGE	TransChatMessage;
	char	*lpChatMsg = 0;

	if(lpChar->dwChatMessageTimer > dwPlayServTime) return FALSE;

	if(lpChar->MotionInfo->State == CHRMOTION_STATE_DEAD && lpChar->FrameCounter > 40)
	{
		lpChatMsg = szMorifChatDropMsg[rand() % MORIF_CHAT_DROP_MAX];
		lpChar->dwChatMessageTimer = dwPlayServTime + 60 * 1000;
	}
	else
	{
		if((rand() % 100) < 15)
		{
			lpChatMsg = szMorifChatMsg[rand() % MORIF_CHAT_MAX];
		}
		lpChar->dwChatMessageTimer = dwPlayServTime + 4 * 1000;
	}

	if(lpChar->lpTargetPlayInfo && lpChatMsg)
	{

		wsprintf(TransChatMessage.szMessage, "%s: %s ", lpChar->smCharInfo.szName, lpChatMsg);
		TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		TransChatMessage.dwIP = 0;
		TransChatMessage.dwObjectSerial = lpChar->dwObjectSerial;

		rsSendCommandUser2(lpChar->lpTargetPlayInfo, (smTRANS_COMMAND *)&TransChatMessage);

		return TRUE;
	}
#endif
	return FALSE;
}


int	rsMollyWolfEventMessage(smCHAR *lpChar)
{
#ifdef _W_SERVER
	TRANS_CHATMESSAGE	TransChatMessage;
	char	*lpChatMsg = 0;

	if(lpChar->dwChatMessageTimer > dwPlayServTime) return FALSE;

	if(lpChar->MotionInfo->State == CHRMOTION_STATE_DEAD && lpChar->FrameCounter > 40)
	{
		lpChatMsg = szMollyWolfChatDropMsg[rand() % MOLLYWOLF_CHAT_DROP_MAX];
		lpChar->dwChatMessageTimer = dwPlayServTime + 60 * 1000;
	}
	else
	{
		if((rand() % 100) < 15)
		{
			lpChatMsg = szMollyWolfChatMsg[rand() % MOLLYWOLF_CHAT_MAX];
		}
		lpChar->dwChatMessageTimer = dwPlayServTime + 4 * 1000;
	}

	if(lpChar->lpTargetPlayInfo && lpChatMsg)
	{

		wsprintf(TransChatMessage.szMessage, "%s: %s ", lpChar->smCharInfo.szName, lpChatMsg);
		TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		TransChatMessage.dwIP = 0;
		TransChatMessage.dwObjectSerial = lpChar->dwObjectSerial;

		rsSendCommandUser2(lpChar->lpTargetPlayInfo, (smTRANS_COMMAND *)&TransChatMessage);

		return TRUE;
	}
#endif
	return FALSE;
}



int	rsChichenDayEventMessage(smCHAR *lpChar)
{
#ifdef _W_SERVER
	TRANS_CHATMESSAGE	TransChatMessage;
	char	*lpChatMsg = 0;

	if(lpChar->dwChatMessageTimer > dwPlayServTime) return FALSE;

	if(lpChar->MotionInfo->State == CHRMOTION_STATE_DEAD && lpChar->FrameCounter > 40)
	{
		lpChatMsg = szPaPaChichenChatDropMsg[rand() % PAPACHICHEN_CHAT_DROP_MAX];
		lpChar->dwChatMessageTimer = dwPlayServTime + 60 * 1000;
	}
	else
	{
		lpChatMsg = szPaPaChichenChatMsg[rand() % PAPACHICHEN_CHAT_MAX];
		lpChar->dwChatMessageTimer = dwPlayServTime + 4 * 1000;
	}

	if(lpChar->lpTargetPlayInfo && lpChatMsg)
	{

		wsprintf(TransChatMessage.szMessage, "%s: %s ", lpChar->smCharInfo.szName, lpChatMsg);
		TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		TransChatMessage.dwIP = 0;
		TransChatMessage.dwObjectSerial = lpChar->dwObjectSerial;

		rsSendCommandUser2(lpChar->lpTargetPlayInfo, (smTRANS_COMMAND *)&TransChatMessage);

		return TRUE;
	}
#endif
	return FALSE;
}



int	rsQuestMasterMessage(smCHAR *lpChar, rsPLAYINFO *lpPlayInfo)
{
#ifdef _W_SERVER
	TRANS_CHATMESSAGE	TransChatMessage;
	char	*lpChatMsg = 0;
	int x, z, dist;

	if(lpChar->dwChatMessageTimer > dwPlayServTime) return FALSE;
	if(lpChar->ActionPattern == 12) return FALSE;

	if((rand() % 100) < 30)
	{
		switch(lpChar->smCharInfo.dwCharSoundCode)
		{
		case snCHAR_SOUND_NPC_SKILLMASTER:
			lpChatMsg = szSkillMasterChatMsg[rand() % SKILLMASTER_CHAT_MAX];
			break;
		case snCHAR_SOUND_NPC_MAGICMASTER:
			lpChatMsg = szMagicMasterChatMsg[rand() % MAGICMASTER_CHAT_MAX];
			break;
		}
	}

	lpChar->dwChatMessageTimer = dwPlayServTime + 4 * 1000;

	if(lpChar && lpChatMsg && lpPlayInfo->lpsmSock)
	{

		x = (lpChar->pX - lpPlayInfo->Position.x) >> FLOATNS;
		z = (lpChar->pZ - lpPlayInfo->Position.z) >> FLOATNS;
		dist = x*x + z*z;

		if(dist < DIST_TRANSLEVEL_LOW && abs(x) < TRANS_VIEW_LIMIT && abs(z) < TRANS_VIEW_LIMIT)
		{
			wsprintf(TransChatMessage.szMessage, "%s: %s ", lpChar->smCharInfo.szName, lpChatMsg);
			TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
			TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
			TransChatMessage.dwIP = 0;
			TransChatMessage.dwObjectSerial = lpChar->dwObjectSerial;

			lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
		}
		return TRUE;
	}
#endif
	return FALSE;
}


int	rsSantaGoblinEventMessage(smCHAR *lpChar)
{
#ifdef _W_SERVER
	TRANS_CHATMESSAGE	TransChatMessage;
	char	*lpChatMsg = 0;

	if(lpChar->dwChatMessageTimer > dwPlayServTime) return FALSE;


	if(lpChar->MotionInfo->State == CHRMOTION_STATE_DEAD && lpChar->FrameCounter > 40)
	{
		lpChar->dwChatMessageTimer = dwPlayServTime + 60 * 1000;
		return FALSE;
	}
	else
	{
		if((rand() % 100) < 15)
		{
			lpChatMsg = szSantaGoblinChatMsg[rand() % SANTAGOBLIN_CHAT_MAX];
		}
		lpChar->dwChatMessageTimer = dwPlayServTime + 4 * 1000;
	}

	if(lpChar->lpTargetPlayInfo && lpChatMsg)
	{

		wsprintf(TransChatMessage.szMessage, "%s: %s ", lpChar->smCharInfo.szName, lpChatMsg);
		TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		TransChatMessage.dwIP = 0;
		TransChatMessage.dwObjectSerial = lpChar->dwObjectSerial;

		rsSendCommandUser2(lpChar->lpTargetPlayInfo, (smTRANS_COMMAND *)&TransChatMessage);

		return TRUE;
	}
#endif
	return FALSE;
}






smCHAR *rsOpenCastleFieldObject(STG_AREA *lpStgArea, smCHAR_INFO *lpCharInfo, int x, int y, int z)
{
	smCHAR	*lpChar;
	STG_CHAR_INFO StgCharInfo;

	if(lpStgArea)
	{
		StgCharInfo.PosiState = smCHAR_STATE_ENEMY;
		StgCharInfo.smCharInfo.Life[0] = 100;
		StgCharInfo.smCharInfo.Mana[0] = 100;
		StgCharInfo.smCharInfo.Life[1] = 100;
		StgCharInfo.smCharInfo.State = TRUE;

		memcpy(&StgCharInfo.smCharInfo, lpCharInfo, sizeof(smCHAR_INFO));

		lpStgArea->EvnMonster = TRUE;
		lpChar = lpStgArea->OpenMonster(&StgCharInfo, 0);
		if(lpChar)
		{
			lpChar->pX = x;
			lpChar->pY = y;
			lpChar->pZ = z;
			lpChar->Angle.x = 0;
			lpChar->Angle.y = 0;
			lpChar->Angle.z = 0;
			lpChar->DistAroundDbl = 0;
			lpChar->SetMotionFromCode(CHRMOTION_STATE_STAND);
			lpChar->TargetMoveCount = 0;
			if(lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_TOWER_B ||
				lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_R ||
				lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_G ||
				lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_B ||
				lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_N ||
				lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_DOOR ||
				lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_DEATHKNIGHT)
			{
				lpChar->DontMoveFlag = 2;

				if(StgCharInfo.smCharInfo.lpMonInfo && StgCharInfo.smCharInfo.lpMonInfo->PotionCount)
				{

					lpChar->smMonsterInfo.PotionCount = 0;

					lpChar->UseObject_VirtualLife = StgCharInfo.smCharInfo.lpMonInfo->PotionCount;
					lpChar->sObject_VirtualLife[0] = lpChar->UseObject_VirtualLife;
					lpChar->sObject_VirtualLife[1] = lpChar->UseObject_VirtualLife;
					lpChar->sObject_DisplayLife[0] = lpChar->UseObject_VirtualLife;
					lpChar->sObject_DisplayLife[1] = lpChar->UseObject_VirtualLife;
				}
			}
			else
			{

				lpChar->smMonsterInfo.PotionCount = StgCharInfo.smCharInfo.lpMonInfo->PotionCount;
				lpChar->PosiAround.x = x;
				lpChar->PosiAround.y = y;
				lpChar->PosiAround.z = z;
				lpChar->DistAroundDbl = DIST_AROUND_MIDDLE;
			}

			lpChar->dwClanCode = rsBlessCastle.dwMasterClan;

			return lpChar;
		}
	}

	return FALSE;
}

#include	"BlessCastle.h"

static	DWORD	dwBlessCastle_TowerRegenTime;

struct BLESS_CASTLE_OPEN_LEAUGE
{
	int		GameMode;
	DWORD	dwStartTime;
	DWORD	dwEndTime;
	DWORD	dwRestartTime;
};

static BLESS_CASTLE_OPEN_LEAUGE	rsBlessCastleOpenLeauge;



int rsInit_Castle()
{
	ZeroMemory(&rsBlessCastle, sizeof(rsBLESS_CASTLE));
	ZeroMemory(&rsBlessCastleOpenLeauge, sizeof(BLESS_CASTLE_OPEN_LEAUGE));

	rsLoadCastleInfo();

	rsBlessCastle.dwSoulFountainTime = 0;
	rsBlessCastle.dwSoulFountainTime2 = 0;
	rsBlessCastle.lpAttackDamageList = 0;
	rsBlessCastle.lpChar_ValhallaTower = 0;

	ZeroMemory(&rsBlessCastle.ClanTop10, sizeof(rsUSER_LIST_TOP10));

	dwBlessCastle_TowerRegenTime = 0;

	return TRUE;
}


int rsMain_CombatCastle()
{
	int cnt;
	int DoorCount = 0;
	int	ValhallaTowerCount = 0;
	int	CrystalTowerCount = 0;
	smCHAR *lpChar;
	smCHAR *lpChar_ValhallaTower = 0;
	STG_AREA	*lpStgArea = &StageArea[rsCASTLE_FIELD];
	int	UpdateFlag = 0;

	rsBlessCastle.Counter++;

	rsBlessCastle_SoulFountainMain();

	if(rsBlessCastleOpenLeauge.GameMode)
	{
		if(rsBlessCastleOpenLeauge.dwEndTime && rsBlessCastleOpenLeauge.dwEndTime < dwPlayServTime)
		{

			rsBlessCastleOpenLeauge.GameMode = 0;
		}
		else
		{
			if(!rsBlessCastle.CastleMode)
			{
				if(rsBlessCastleOpenLeauge.dwRestartTime && rsBlessCastleOpenLeauge.dwRestartTime < dwPlayServTime)
				{

					rsStart_CombatCastle();
				}
			}
		}
	}

	if(!rsBlessCastle.CastleMode)
	{
		rsBlessCastle.TimeSec[0] = 0;
		rsBlessCastle.TimeSec[1] = 0;
		return FALSE;
	}

	if(rsBlessCastle.CastleMode == 3)
	{

		if(rsBlessCastle.dwBattleOverTime < dwPlayServTime)
		{
			rsEnd_CombatCastle();
		}
		return TRUE;
	}

	if((rsBlessCastle.Counter & 0x1F) == 0)
	{


		rsBlessCastle.TimeSec[0] = (short)((dwPlayServTime - rsBlessCastle.dwStartTime) / 1000);
		rsBlessCastle.TimeSec[1] = (short)((rsBlessCastle.dwBattleOverTime - rsBlessCastle.dwStartTime) / 1000);

		((DWORD *)rsBlessCastle.bCrystalSolderCount)[0] = 0;
		((DWORD *)rsBlessCastle.bCrystalTowerCount)[0] = 0;


		for(cnt = 0; cnt < STG_MONSTER_MAX; cnt++)
		{
			if(lpStgArea->lpCharMonster[cnt] && lpStgArea->lpCharMonster[cnt]->smCharInfo.Life[0] > 0)
			{
				lpChar = lpStgArea->lpCharMonster[cnt];
				if(lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_DOOR)
				{
					DoorCount++;
				}
				else if(lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_TOWER_B)
				{
					ValhallaTowerCount++;
					lpChar_ValhallaTower = lpChar;
				}
				else if(lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_R ||
					lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_G ||
					lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_B ||
					lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_N)
				{

					switch(lpChar->smCharInfo.dwCharSoundCode)
					{
					case snCHAR_SOUND_CASTLE_CRYSTAL_R:
						if(rsBlessCastle.bCrystalTowerCount[0] < 100) rsBlessCastle.bCrystalTowerCount[0] ++;
						break;
					case snCHAR_SOUND_CASTLE_CRYSTAL_G:
						if(rsBlessCastle.bCrystalTowerCount[1] < 100) rsBlessCastle.bCrystalTowerCount[1] ++;
						break;
					case snCHAR_SOUND_CASTLE_CRYSTAL_B:
						if(rsBlessCastle.bCrystalTowerCount[2] < 100) rsBlessCastle.bCrystalTowerCount[2] ++;
						break;
					case snCHAR_SOUND_CASTLE_CRYSTAL_N:
						if(rsBlessCastle.bCrystalTowerCount[3] < 100) rsBlessCastle.bCrystalTowerCount[3] ++;
						break;
					}


					CrystalTowerCount++;


					if(rsBlessCastle.DefenceLevel == 0 &&
						rsBlessCastle.lpAttackDamageList &&
						!lpChar->lpAttackDamageList_BlessCastle)
					{
						lpChar->lpAttackDamageList_BlessCastle = rsBlessCastle.lpAttackDamageList;
					}

				}
				else if(lpChar->smCharInfo.Next_Exp)
				{

					switch(lpChar->smCharInfo.dwCharSoundCode)
					{
					case snCHAR_SOUND_CASTLE_SOLDER_A:
						if(rsBlessCastle.bCrystalSolderCount[0] < 100) rsBlessCastle.bCrystalSolderCount[0]++;
						break;
					case snCHAR_SOUND_CASTLE_SOLDER_B:
						if(rsBlessCastle.bCrystalSolderCount[1] < 100) rsBlessCastle.bCrystalSolderCount[1]++;
						break;
					case snCHAR_SOUND_CASTLE_SOLDER_C:
						if(rsBlessCastle.bCrystalSolderCount[2] < 100) rsBlessCastle.bCrystalSolderCount[2]++;
						break;
					}
				}

				lpChar->dwLastTransTime = dwPlayServTime;
				lpChar->ReopenCount = REOPEN_COUNT_NUM;
			}
		}

		if(rsBlessCastle.DefenceLevel == 0 && DoorCount == 0)
		{
			rsBlessCastle.DefenceLevel++;
		}

		if(ValhallaTowerCount == 0)
		{
			rsEnd_CombatCastle(0);


			if(rsBlessCastle.ClanTop10.dwUserCode[0])
			{
				rsBlessCastle.dwMasterClan = GetClanCode(rsBlessCastle.ClanTop10.dwUserCode[0]);
				UpdateFlag = 2;
				rsSaveCastleInfo();
			}
		}
		else if(rsBlessCastle.dwBattleOverTime < dwPlayServTime)
		{

			rsEnd_CombatCastle(1);
			UpdateFlag = 2;
			rsSaveCastleInfo();
		}

		rsBlessCastle.lpChar_ValhallaTower = lpChar_ValhallaTower;


		if(lpChar_ValhallaTower)
		{
			if(CrystalTowerCount > 0)
			{
				lpChar_ValhallaTower->smCharInfo.Life[0] = lpChar_ValhallaTower->smCharInfo.Life[1];
			}
			else
			{

				if(!lpChar_ValhallaTower->lpAttackDamageList)
				{
					if(rsBlessCastle.lpAttackDamageList)
					{
						lpChar_ValhallaTower->lpAttackDamageList = rsBlessCastle.lpAttackDamageList;
						rsBlessCastle.lpAttackDamageList = 0;
					}
					else
					{
						lpChar_ValhallaTower->lpAttackDamageList = new ATTACK_DAMAGE_LIST[ATTACK_DAMAGE_LIST_MAX];
						if(lpChar_ValhallaTower->lpAttackDamageList)
							ZeroMemory(lpChar_ValhallaTower->lpAttackDamageList, sizeof(ATTACK_DAMAGE_LIST)*ATTACK_DAMAGE_LIST_MAX);
					}
				}
			}

			if(rsBlessCastle.DefenceLevel)
			{
				rsSelectDamageClanTop10(lpChar_ValhallaTower, &rsBlessCastle.ClanTop10);
			}
		}
	}

	if(rsBlessCastle.ClanTop10.code)
	{
		for(cnt = (rsBlessCastle.Counter & 0x1F); cnt < CONNECTMAX; cnt += 0x20)
		{
			if(rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial && rsPlayInfo[cnt].Position.Area == rsCASTLE_FIELD)
			{

				rsPlayInfo[cnt].lpsmSock->Send((char *)&rsBlessCastle.ClanTop10, rsBlessCastle.ClanTop10.size, TRUE);
				if(UpdateFlag > 0)
				{
					rsSendBlessCastleInfoToDataServer(&rsPlayInfo[cnt]);
					UpdateFlag--;
				}
			}
		}
	}

	return TRUE;
}



int	rsStart_CombatCastle()
{
	int cnt;
	STG_AREA	*lpStgArea = &StageArea[rsCASTLE_FIELD];
	smCHAR	*lpChar;

	if(rsServerConfig.BlessCastleMode == 2)
	{

		rsBlessCastleOpenLeauge.GameMode = 1;
		rsBlessCastleOpenLeauge.dwStartTime = dwPlayServTime;
		rsBlessCastleOpenLeauge.dwEndTime = dwPlayServTime + 120 * 60 * 1000;
		rsServerConfig.BlessCastleMode = 1;
	}

	rsBlessCastle.CastleMode = 1;
	rsBlessCastle.Counter = 0;
	rsBlessCastle.DefenceLevel = 0;
	rsBlessCastle.dwBattleOverTime = dwPlayServTime + 120 * 60 * 1000;
	rsBlessCastle.dwStartTime = dwPlayServTime;
	rsBlessCastle.TimeSec[0] = 0;
	rsBlessCastle.TimeSec[1] = 0;

	rsBlessCastle.dwScoreLogTime = dwPlayServTime + 5 * 60 * 1000;

	if(rsBlessCastleOpenLeauge.GameMode)
	{
		rsBlessCastle.dwBattleOverTime = rsBlessCastleOpenLeauge.dwEndTime;
		rsBlessCastleOpenLeauge.dwRestartTime = 0;
		rsSetNoticeMessage("League");
	}



	if(!rsBlessCastle.lpAttackDamageList)
		rsBlessCastle.lpAttackDamageList = new ATTACK_DAMAGE_LIST[ATTACK_DAMAGE_LIST_MAX];
	if(rsBlessCastle.lpAttackDamageList)
		ZeroMemory(rsBlessCastle.lpAttackDamageList, sizeof(ATTACK_DAMAGE_LIST)*ATTACK_DAMAGE_LIST_MAX);


	if(rsBlessCastle.dwMasterClan == 0)
	{


		rsBlessCastle.BlessCastleSetup.MercenaryNum[0] = 20;
		rsBlessCastle.BlessCastleSetup.MercenaryNum[1] = 20;
		rsBlessCastle.BlessCastleSetup.MercenaryNum[2] = 20;
		rsBlessCastle.BlessCastleSetup.MercenaryNum[3] = 0;


		for(cnt = 0; cnt < 6; cnt++)
		{
			rsBlessCastle.BlessCastleSetup.Tower[cnt] = (rand() % 3) + 1;
		}
	}


	ZeroMemory(&rsBlessCastle.ClanTop10, sizeof(rsUSER_LIST_TOP10));


	for(cnt = 0; cnt < AUTOPLAYER_MAX; cnt++)
	{
		if(chrAutoPlayer[cnt].Flag && chrAutoPlayer[cnt].lpExt1 == lpStgArea)
		{



			chrAutoPlayer[cnt].Close();
			if(lpStgArea->DeleteMonTable(&chrAutoPlayer[cnt]) == TRUE)
				lpStgArea->MonsterCount--;
		}
	}

	smCHAR_INFO	*lpChar_CastleDoor = 0;
	smCHAR_INFO	*lpChar_CastleTower_B = 0;
	smCHAR_INFO	*lpChar_CastleCrystal_R = 0;
	smCHAR_INFO	*lpChar_CastleCrystal_G = 0;
	smCHAR_INFO	*lpChar_CastleCrystal_B = 0;
	smCHAR_INFO	*lpChar_CastleCrystal_N = 0;
	smCHAR_INFO	*lpChar_CastleSolder_A = 0;
	smCHAR_INFO	*lpChar_CastleSolder_B = 0;
	smCHAR_INFO	*lpChar_CastleSolder_C = 0;
	smCHAR_INFO	*lpChar_SetTower = 0;

	for(cnt = 0; cnt < chrMonsterCnt; cnt++)
	{
		if(chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_CASTLE_DOOR)
		{
			lpChar_CastleDoor = &chrMonsterList[cnt];
		}
		if(chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_CASTLE_TOWER_B)
		{
			lpChar_CastleTower_B = &chrMonsterList[cnt];
		}
		if(chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_R)
		{
			lpChar_CastleCrystal_R = &chrMonsterList[cnt];
		}
		if(chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_G)
		{
			lpChar_CastleCrystal_G = &chrMonsterList[cnt];
		}
		if(chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_B)
		{
			lpChar_CastleCrystal_B = &chrMonsterList[cnt];
		}
		if(chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_N)
		{
			lpChar_CastleCrystal_N = &chrMonsterList[cnt];
		}

		if(chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_CASTLE_SOLDER_A)
		{
			lpChar_CastleSolder_A = &chrMonsterList[cnt];
		}
		if(chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_CASTLE_SOLDER_B)
		{
			lpChar_CastleSolder_B = &chrMonsterList[cnt];
		}
		if(chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_CASTLE_SOLDER_C)
		{
			lpChar_CastleSolder_C = &chrMonsterList[cnt];
		}

	}


	if(lpChar_CastleDoor)
	{

		rsOpenCastleFieldObject(lpStgArea, lpChar_CastleDoor, pCastle_Door.x*fONE, pCastle_Door.z*fONE, pCastle_Door.y*fONE);
	}
	if(lpChar_CastleTower_B)
	{

		lpChar = rsOpenCastleFieldObject(lpStgArea, lpChar_CastleTower_B, pCastle_ValhallaTower.x*fONE, pCastle_ValhallaTower.z*fONE, pCastle_ValhallaTower.y*fONE);

	}


	cnt = 0;
	while(1)
	{
		if(pCastle_CrystalTower[cnt].x == 0) break;

		lpChar_SetTower = lpChar_CastleCrystal_N;

		switch(rsBlessCastle.BlessCastleSetup.Tower[cnt])
		{
		case SIN_GURAD_CRISTAL_ICE:
			lpChar_SetTower = lpChar_CastleCrystal_B;
			break;
		case SIN_GURAD_CRISTAL_LIGHTNING:
			lpChar_SetTower = lpChar_CastleCrystal_G;
			break;
		case SIN_GURAD_CRISTAL_FIRE:
			lpChar_SetTower = lpChar_CastleCrystal_R;
			break;
		}

		if(lpChar_SetTower)
		{
			lpChar = rsOpenCastleFieldObject(lpStgArea, lpChar_SetTower, pCastle_CrystalTower[cnt].x*fONE, pCastle_CrystalTower[cnt].z*fONE, pCastle_CrystalTower[cnt].y*fONE);

		}
		cnt++;
	}

	for(cnt = 0; cnt < 3; cnt++)
	{
		if(rsBlessCastle.BlessCastleSetup.MercenaryNum[cnt] > MERCENARY_SOLDER_MAX)
			rsBlessCastle.BlessCastleSetup.MercenaryNum[cnt] = MERCENARY_SOLDER_MAX;
	}


	if(lpChar_CastleSolder_A)
	{
		for(cnt = 0; cnt < rsBlessCastle.BlessCastleSetup.MercenaryNum[0]; cnt++)
		{
			rsOpenCastleFieldObject(lpStgArea, lpChar_CastleSolder_A, PosMercenarySolder_A[cnt].x*fONE, PosMercenarySolder_A[cnt].z*fONE, PosMercenarySolder_A[cnt].y*fONE);
		}
	}

	if(lpChar_CastleSolder_B)
	{
		for(cnt = 0; cnt < rsBlessCastle.BlessCastleSetup.MercenaryNum[1]; cnt++)
		{
			rsOpenCastleFieldObject(lpStgArea, lpChar_CastleSolder_B, PosMercenarySolder_B[cnt].x*fONE, PosMercenarySolder_B[cnt].z*fONE, PosMercenarySolder_B[cnt].y*fONE);
		}
	}

	if(lpChar_CastleSolder_C)
	{
		for(cnt = 0; cnt < rsBlessCastle.BlessCastleSetup.MercenaryNum[2]; cnt++)
		{
			rsOpenCastleFieldObject(lpStgArea, lpChar_CastleSolder_C, PosMercenarySolder_C[cnt].x*fONE, PosMercenarySolder_C[cnt].z*fONE, PosMercenarySolder_C[cnt].y*fONE);
		}
	}


	rsSetNoticeMessage(srBlessCastle_LeagueMsg_02);

	return TRUE;
}


int	rsEnd_CombatCastle(int DefenceFlag)
{
	int cnt;
	STG_AREA	*lpStgArea = &StageArea[rsCASTLE_FIELD];

	rsBlessCastle.CastleMode = 3;
	rsBlessCastle.dwBattleOverTime = dwPlayServTime + 5000;

	for(cnt = 0; cnt < AUTOPLAYER_MAX; cnt++)
	{
		if(chrAutoPlayer[cnt].Flag && chrAutoPlayer[cnt].lpExt1 == lpStgArea && chrAutoPlayer[cnt].smCharInfo.State == smCHAR_STATE_ENEMY)
		{
			if(DefenceFlag && chrAutoPlayer[cnt].smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_TOWER_B)
			{

				chrAutoPlayer[cnt].smCharInfo.Life[0] = chrAutoPlayer[cnt].smCharInfo.Life[1];
				chrAutoPlayer[cnt].SetMotionFromCode(CHRMOTION_STATE_STAND);
			}
			else
			{

				chrAutoPlayer[cnt].smCharInfo.Life[0] = 0;
				chrAutoPlayer[cnt].SetMotionFromCode(CHRMOTION_STATE_DEAD);
			}
		}
	}



	for(cnt = 0; cnt < FIX_CHAR_MAX; cnt++)
	{
		if(lpStgArea->TransCharFixed[cnt].code)
			lpStgArea->OpenNpc(&lpStgArea->TransCharFixed[cnt]);
	}


	return TRUE;
}


int	rsEnd_CombatCastle()
{
	int cnt;
	STG_AREA	*lpStgArea = &StageArea[rsCASTLE_FIELD];

	rsBlessCastle.CastleMode = 0;
	rsBlessCastle.TimeSec[0] = 0;
	rsBlessCastle.TimeSec[1] = 0;


	rsBlessCastle.BlessCastleSetup.MercenaryNum[0] = 0;
	rsBlessCastle.BlessCastleSetup.MercenaryNum[1] = 0;
	rsBlessCastle.BlessCastleSetup.MercenaryNum[2] = 0;
	rsBlessCastle.BlessCastleSetup.MercenaryNum[3] = 0;


	ZeroMemory(rsBlessCastle.BlessCastleSetup.Tower, sizeof(short) * 12);

	if(rsBlessCastle.lpAttackDamageList)
	{
		delete rsBlessCastle.lpAttackDamageList;
		rsBlessCastle.lpAttackDamageList = 0;
	}


	for(cnt = 0; cnt < AUTOPLAYER_MAX; cnt++)
	{
		if(chrAutoPlayer[cnt].Flag && chrAutoPlayer[cnt].lpExt1 == lpStgArea)
		{
			chrAutoPlayer[cnt].Close();
			if(lpStgArea->DeleteMonTable(&chrAutoPlayer[cnt]) == TRUE)
			{
				lpStgArea->MonsterCount--;
			}
		}
	}


	for(cnt = 0; cnt < FIX_CHAR_MAX; cnt++)
	{
		if(lpStgArea->TransCharFixed[cnt].code)
			lpStgArea->OpenNpc(&lpStgArea->TransCharFixed[cnt]);
	}

	rsSetNoticeMessage(srBlessCastle_LeagueMsg_03);

	if(rsBlessCastleOpenLeauge.GameMode)
	{
		rsBlessCastleOpenLeauge.dwRestartTime = dwPlayServTime + 1000 * 60 * 3;
		if(rsBlessCastleOpenLeauge.dwRestartTime >= rsBlessCastleOpenLeauge.dwEndTime)
		{

			rsBlessCastleOpenLeauge.GameMode = 0;
			rsBlessCastleOpenLeauge.dwEndTime = 0;
			rsBlessCastleOpenLeauge.dwRestartTime = 0;
		}
		else
		{
			rsSetNoticeMessage(srBlessCastle_LeagueMsg_01);
		}
	}

	return TRUE;
}



int	rsEasy_CastleMode()
{
	STG_AREA *lpStgArea = &StageArea[rsCASTLE_FIELD];

	for(int cnt = 0; cnt < AUTOPLAYER_MAX; cnt++)
	{
		if(chrAutoPlayer[cnt].Flag && chrAutoPlayer[cnt].lpExt1 == lpStgArea && chrAutoPlayer[cnt].smCharInfo.State == smCHAR_STATE_ENEMY)
		{

			chrAutoPlayer[cnt].sObject_VirtualLife[0] = 0;
			chrAutoPlayer[cnt].smCharInfo.Life[0] = 1;
		}
	}

	return TRUE;
}


int rsCheck_BlessCastleClanSkill(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	DWORD Code;

#ifdef _W_SERVER
	Code = 0x0c3c5645;

	Code ^= lpTransCommand->WParam << 2;
	Code ^= lpTransCommand->LParam << 6;
	Code ^= lpTransCommand->SParam << 1;

	Code ^= lpPlayInfo->dwObjectSerial << 16;

#else
	Code = 0x3ea832ff;
#endif

	return Code & 0x7FFFFFFF;
}




int rsCheck_BlessCastleTax(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND_EX *lpTransCommandEx)
{
	DWORD Code;

#ifdef _W_SERVER
	Code = 0x056c3c45;

	Code ^= lpTransCommandEx->WParam << 1;
	Code ^= lpTransCommandEx->LParam << 2;
	Code ^= lpTransCommandEx->SParam << 3;
	Code ^= lpTransCommandEx->EParam << 4;

	Code ^= lpTransCommandEx->WxParam << 16;
	Code ^= lpTransCommandEx->LxParam << 17;
	Code ^= lpTransCommandEx->SxParam << 18;

	Code ^= lpPlayInfo->dwObjectSerial << 16;

#else
	Code = 0x3ea832ff;
#endif

	return Code & 0x7FFFFFFF;
}


int	rsSendBlessCastleInfoToDataServer(rsPLAYINFO *lpPlayInfo)
{
#ifdef _W_SERVER

	smTRANS_COMMAND_EX	smTransCommand;

	smTransCommand.code = OpCode::OPCODE_BLESSCASTLE_TAX;
	smTransCommand.size = sizeof(smTRANS_COMMAND_EX);
	smTransCommand.WParam = (DWORD)rsBlessCastle.dwMasterClan^lpPlayInfo->dwObjectSerial^OpCode::OPCODE_BLESSCASTLE_TAX;
	smTransCommand.LParam = rsBlessCastle.Tax^smTransCommand.WParam;
	smTransCommand.SParam = rsBlessCastle.NextTax^smTransCommand.LParam;
	smTransCommand.EParam = ((rsBlessCastle.SelectedSkill << 16) | (rsBlessCastle.BlessCastleSetup.ClanSkill & 0xFFFF)) ^ smTransCommand.SParam;
	smTransCommand.WxParam = 0;
	smTransCommand.LxParam = 0;
	smTransCommand.SxParam = 0;
	smTransCommand.ExParam = rsCheck_BlessCastleTax(lpPlayInfo, &smTransCommand);

	if(lpPlayInfo->lpsmSock)
		rsSendDataServer(lpPlayInfo->lpsmSock, &smTransCommand);
#endif
	return TRUE;
}




int	rsRecvBlessCastleInfoFromGameServer(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND_EX *lpTransCommand)
{
#ifdef _W_SERVER

	if(rsCheck_BlessCastleTax(lpPlayInfo, lpTransCommand) == lpTransCommand->ExParam)
	{
		lpTransCommand->EParam ^= lpTransCommand->SParam;
		lpTransCommand->SParam ^= lpTransCommand->LParam;
		lpTransCommand->LParam ^= lpTransCommand->WParam;
		lpTransCommand->WParam ^= lpPlayInfo->dwObjectSerial^OpCode::OPCODE_BLESSCASTLE_TAX;

		rsBlessCastle.BlessCastleSetup.ClanSkill = lpTransCommand->EParam & 0xFFFF;

		rsBlessCastle.SelectedSkill = rsBlessCastle.BlessCastleSetup.ClanSkill;
		rsBlessCastle.NextTax = lpTransCommand->SParam;
		rsBlessCastle.Tax = lpTransCommand->LParam;
		rsBlessCastle.dwMasterClan = (DWORD)lpTransCommand->WParam;


		rsSaveCastleInfo();

		return TRUE;
	}
#endif

	return FALSE;
}




int rsRecvBlessCastInfo(rsPLAYINFO *lpPlayInfo, void *lpPacket)
{
	smTRANS_BLESSCASTLE *lpBlessCastleSetup = (smTRANS_BLESSCASTLE *)lpPacket;
	smTRANS_COMMAND		smTransCommand;

	switch(lpBlessCastleSetup->smTransCommand.WParam)
	{
	case 0:
		if(lpBlessCastleSetup->smTransCommand.SParam != rsBlessCastle.Tax)
		{

			smTransCommand.code = OpCode::OPCODE_BLESSCASTLE_TAX;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = 0;
			smTransCommand.LParam = rsBlessCastle.dwMasterClan;
			smTransCommand.SParam = rsBlessCastle.Tax;
			smTransCommand.EParam = 0;

			lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
		}
		break;


	case 1:
		if(lpPlayInfo->dwClanCode == rsBlessCastle.dwMasterClan || lpPlayInfo->getSecurity() > AccountTypes::SEC_GAMEMASTER)
		{

			if(StageArea[rsCASTLE_FIELD].dwActiveMode)
			{
				memcpy(&rsBlessCastle.BlessCastleSetup, lpBlessCastleSetup, sizeof(smTRANS_BLESSCASTLE));

				rsBlessCastle.NextTax = rsBlessCastle.BlessCastleSetup.TaxRate;
				rsSendBlessCastleInfoToDataServer(lpPlayInfo);
				rsSaveCastleInfo();


				RecordBlessCastleSetup(lpPlayInfo, lpBlessCastleSetup);
			}

		}
		break;
	}

	return TRUE;
}




int rsSendBlessCastInfo(rsPLAYINFO *lpPlayInfo, int Mode)
{
	smTRANS_BLESSCASTLE	smTransBlessCastle;

	memcpy(&smTransBlessCastle, &rsBlessCastle.BlessCastleSetup, sizeof(smTRANS_BLESSCASTLE));

	smTransBlessCastle.smTransCommand.size = sizeof(smTRANS_BLESSCASTLE);
	smTransBlessCastle.smTransCommand.code = OpCode::OPCODE_BLESSCASTLE_INFO;
	smTransBlessCastle.smTransCommand.WParam = Mode;
	smTransBlessCastle.smTransCommand.LParam = 0;
	smTransBlessCastle.smTransCommand.SParam = 0;
	smTransBlessCastle.smTransCommand.EParam = 0;

	smTransBlessCastle.dwMasterClan = rsBlessCastle.dwMasterClan;
	smTransBlessCastle.Price = 0;

	switch(Mode)
	{
	case 1:
		if(lpPlayInfo->dwClanCode == rsBlessCastle.dwMasterClan || lpPlayInfo->getSecurity() > AccountTypes::SEC_VIP)
		{
			if(lpPlayInfo->lpsmSock)
				lpPlayInfo->lpsmSock->Send((char *)&smTransBlessCastle, smTransBlessCastle.smTransCommand.size, TRUE);
		}
		break;

	}

	return TRUE;
}




int	rsSelectDamageClanTop10(smCHAR *lpChar, rsUSER_LIST_TOP10 *lpUserListDamageTop10)
{
	int cnt, cnt2;
	int ChkCnt;
	int	TotalDamage = 0;
	ATTACK_DAMAGE_LIST	AttackDamageList[ATTACK_DAMAGE_LIST_MAX];

	if(!lpUserListDamageTop10) return FALSE;

	ZeroMemory(lpUserListDamageTop10, sizeof(rsUSER_LIST_TOP10));

	if(lpChar->lpAttackDamageList)
	{
		memcpy(AttackDamageList, lpChar->lpAttackDamageList, sizeof(ATTACK_DAMAGE_LIST)*ATTACK_DAMAGE_LIST_MAX);
	}
	else if(rsBlessCastle.lpAttackDamageList)
	{
		memcpy(AttackDamageList, rsBlessCastle.lpAttackDamageList, sizeof(ATTACK_DAMAGE_LIST)*ATTACK_DAMAGE_LIST_MAX);
	}
	else
		return FALSE;

	for(cnt2 = 0; cnt2 < ATTACK_DAMAGE_LIST_MAX; cnt2++)
	{
		TotalDamage += AttackDamageList[cnt2].DamageCount;
	}

	for(cnt = 0; cnt < 10; cnt++)
	{
		ChkCnt = -1;
		for(cnt2 = 0; cnt2 < ATTACK_DAMAGE_LIST_MAX; cnt2++)
		{
			if(AttackDamageList[cnt2].dwUserCode && GetClanCode(AttackDamageList[cnt2].dwUserCode) != rsBlessCastle.dwMasterClan &&
				AttackDamageList[cnt2].DamageCount > lpUserListDamageTop10->Damage[cnt])
			{

				lpUserListDamageTop10->dwUserCode[cnt] = AttackDamageList[cnt2].dwUserCode;
				lpUserListDamageTop10->Damage[cnt] = AttackDamageList[cnt2].DamageCount;
				lpUserListDamageTop10->Counter[cnt] = AttackDamageList[cnt2].Count;

				ChkCnt = cnt2;
			}
		}

		if(ChkCnt >= 0)
			AttackDamageList[ChkCnt].dwUserCode = 0;
	}


	((DWORD *)lpUserListDamageTop10->bCrystalTowerCount)[0] = ((DWORD *)rsBlessCastle.bCrystalTowerCount)[0];

	lpUserListDamageTop10->dwUpdateTime = dwPlayServTime;
	lpUserListDamageTop10->dwCharCode = lpChar->dwObjectSerial;

	lpUserListDamageTop10->code = OpCode::OPCODE_BLESSCASTLE_INFO;
	lpUserListDamageTop10->size = sizeof(rsUSER_LIST_TOP10);
	lpUserListDamageTop10->tCode = rsServerConfig.ServerCode;
	lpUserListDamageTop10->dwObjectSerial = 2;
	lpUserListDamageTop10->dwTotalDamage = TotalDamage;



	if(rsBlessCastle.dwScoreLogTime && rsBlessCastle.dwScoreLogTime < dwPlayServTime)
	{
		rsBlessCastle.dwScoreLogTime = dwPlayServTime + 5 * 60 * 1000;

		RecordBlessCastleLOG(lpUserListDamageTop10);
	}

	return TRUE;
}


int	rsBlessCastle_SoulFountainMain()
{
	int cnt, mcnt, last;
	rsPLAYINFO *lpPlayInfo;
	TRANS_CHATMESSAGE	TransChatMessage;

	if(!rsBlessCastle.dwMasterClan || rsBlessCastle.CastleMode)
		return FALSE;

	if(rsBlessCastle.dwSoulFountainTime < dwPlayServTime)
	{
		rsBlessCastle.dwSoulFountainTime = dwPlayServTime + 60 * 1000;
		if(rsBlessCastle.SoulFountain_PotionCount < 1440)
			rsBlessCastle.SoulFountain_PotionCount++;
	}

	if(!rsBlessCastle.SoulFountain_PotionCount || rsBlessCastle.dwSoulFountainTime2 > dwPlayServTime) return FALSE;

	rsBlessCastle.dwSoulFountainTime2 = dwPlayServTime + 1000;

	last = rsBlessCastle.SoulFountain_LastUserCount + CONNECTMAX;

	for(cnt = rsBlessCastle.SoulFountain_LastUserCount + 1; cnt <= last; cnt++)
	{
		mcnt = cnt & CONNECTMAX_MASK;
		lpPlayInfo = &rsPlayInfo[mcnt];
		if(lpPlayInfo->lpsmSock && lpPlayInfo->dwObjectSerial && lpPlayInfo->Position.Area == rsCASTLE_FIELD)
		{
			if(rsBlessCastle.SoulFountain_PotionCount > 0 && lpPlayInfo->dwClanCode &&
				lpPlayInfo->dwClanCode == rsBlessCastle.dwMasterClan &&
				lpPlayInfo->Position.x > CastleSoulFountain_Area[0] &&
				lpPlayInfo->Position.x<CastleSoulFountain_Area[1] &&
				lpPlayInfo->Position.z>CastleSoulFountain_Area[2] &&
				lpPlayInfo->Position.z < CastleSoulFountain_Area[3])
			{


				if(dwSerToSerIP)
					rsPutItemToSystemLine(lpPlayInfo, (sinPM1 | sin04));
				else
					rsPutItem(lpPlayInfo, (sinPM1 | sin04));

				rsBlessCastle.SoulFountain_PotionCount--;

				wsprintf(TransChatMessage.szMessage, srMsg_038, lpPlayInfo->smCharInfo.szName, rsBlessCastle.SoulFountain_PotionCount);
				TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
				TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
				TransChatMessage.dwIP = 0;
				TransChatMessage.dwObjectSerial = 0;

				rsSendCommandUser2(lpPlayInfo, (smTRANS_COMMAND *)&TransChatMessage);

				rsBlessCastle.SoulFountain_LastUserCount = mcnt;
				break;
			}

		}
	}


	return TRUE;
}


int rsSendBlessCastleClanSkill(rsPLAYINFO *lpPlayInfo)
{
	smTRANS_COMMAND smTransCommand;

	if(lpPlayInfo->dwClanCode && lpPlayInfo->dwClanCode == rsBlessCastle.dwMasterClan)
	{

		if(!lpPlayInfo->SucessCheck_ClanCode)
		{
			bClan_GetClanMarkCode(lpPlayInfo);
		}

		if(!lpPlayInfo->CastleMaster.Flag)
		{
			lpPlayInfo->CastleMaster.dwCheckTime = 0;
			lpPlayInfo->CastleMaster.SelectSkill = rsBlessCastle.SelectedSkill;
			lpPlayInfo->CastleMaster.Flag = TRUE;
		}

		if(lpPlayInfo->CastleMaster.dwCheckTime < dwPlayServTime)
		{

			smTransCommand.code = OpCode::OPCODE_PROCESS_CLAN_SKILL;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = rsBlessCastle.SelectedSkill;
			smTransCommand.LParam = lpPlayInfo->dwClanCode;
			smTransCommand.SParam = 0;
			smTransCommand.EParam = rsCheck_BlessCastleClanSkill(lpPlayInfo, &smTransCommand);
			lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

			lpPlayInfo->CastleMaster.dwCheckTime = dwPlayServTime + 1000 * 60;
		}
		return TRUE;
	}
	return FALSE;
}



DWORD GetClanCode(int ClassClanCode)
{
	DWORD dwCode = ClassClanCode % 1000000;
	DWORD dwCode1 = ClassClanCode / 100000000;
	DWORD dwCode2 = dwCode1 * 100000000;

	return dwCode + dwCode2;
}


int	rsSaveCastleInfo()
{
#ifdef _W_SERVER
	FILE *fp;

	if(!StageArea[rsCASTLE_FIELD].dwActiveMode && !UseDLL_Code)
		return FALSE;

	fp = fopen("BlessCastle.dat", "wb");
	if(fp)
	{
		fwrite(&rsBlessCastle, sizeof(rsBLESS_CASTLE), 1, fp);
		fclose(fp);
		return TRUE;
	}
#endif
	return FALSE;
}


int rsLoadCastleInfo()
{
#ifdef _W_SERVER
	if(!StageArea[rsCASTLE_FIELD].dwActiveMode && !UseDLL_Code)
		return FALSE;

	FILE *fp = nullptr;
	fopen_s(&fp, "BlessCastle.dat", "rb");

	if(fp)
	{
		fread(&rsBlessCastle, sizeof(rsBLESS_CASTLE), 1, fp);
		fclose(fp);
		return TRUE;
	}
#endif
	return FALSE;
}




int rsSiegeItemSucess(rsPLAYINFO *lpPlayInfo, DWORD dwItemCode)
{

	smTRANS_COMMAND	smTransCommand;

	smTransCommand.code = OpCode::OPCODE_PROCESS_SKILL2;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = SKILL_PLAY_BLESS_SIEGE_ITEM;
	smTransCommand.LParam = lpPlayInfo->dwObjectSerial;
	smTransCommand.SParam = dwItemCode;
	smTransCommand.EParam = 0;
	lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

	return TRUE;
}


int	rsOpenSiegeCastleItem(DWORD dwItemCode, int x, int y, int z, rsPLAYINFO *lpPlayInfo)
{
	smTRANS_COMMAND	smTransCommand;

	switch(dwItemCode)
	{
	case (sinBI1 | sin05):
		lpPlayInfo->dwSiegeItem_Scroll_Time = dwPlayServTime + 30 * 1000;
		lpPlayInfo->dwSiegeItem_Scroll_Code = dwItemCode;
		lpPlayInfo->dwSiegeItem_Scroll_Param = 2;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBI1 | sin06):
		lpPlayInfo->dwSiegeItem_Scroll_Time = dwPlayServTime + 60 * 60 * 1000;
		lpPlayInfo->dwSiegeItem_Scroll_Code = dwItemCode;
		lpPlayInfo->dwSiegeItem_Scroll_Param = 15;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBI1 | sin07):
		lpPlayInfo->dwSiegeItem_Scroll_Time = dwPlayServTime + 60 * 60 * 1000;
		lpPlayInfo->dwSiegeItem_Scroll_Code = dwItemCode;
		lpPlayInfo->dwSiegeItem_Scroll_Param = 15;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBI1 | sin09):
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = OpCode::OPCODE_COMIC_SKIN;
		smTransCommand.WParam = (rand() % 2) + 1;
		smTransCommand.LParam = 60 * 10;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = 0;
		lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
		return TRUE;


	case (sinBI1 | sin19):

		return TRUE;
	case (sinBI1 | sin20):

		return TRUE;
	case (sinBI1 | sin81):

		return TRUE;

	case (sinBI1 | sin86):

		return TRUE;
	case (sinBI1 | sin87):

		return TRUE;
	case (sinBI1 | sin88):

		return TRUE;

	case (sinBI1 | sin21):

		return TRUE;
	case (sinBI1 | sin22):

		return TRUE;
	case (sinBI1 | sin82):

		return TRUE;


	case (sinBI1 | sin12):
	case (sinBI1 | sin13):

	case (sinBI1 | sin14):
	case (sinBI1 | sin15):
	case (sinBI1 | sin78):

		return TRUE;

	case (sinBC1 | sin21):
		lpPlayInfo->dwLifeBooster_Code = dwItemCode;
		lpPlayInfo->dwLifeBooster_Time = dwPlayServTime + BoosterItem_UseTime[0] * 1000;
		lpPlayInfo->dwLifeBooster_Data = BoosterItem_DataPercent[0];
		return TRUE;
	case (sinBC1 | sin22):
		lpPlayInfo->dwLifeBooster_Code = dwItemCode;
		lpPlayInfo->dwLifeBooster_Time = dwPlayServTime + BoosterItem_UseTime[1] * 1000;
		lpPlayInfo->dwLifeBooster_Data = BoosterItem_DataPercent[0];
		return TRUE;
	case (sinBC1 | sin23):
		lpPlayInfo->dwLifeBooster_Code = dwItemCode;
		lpPlayInfo->dwLifeBooster_Time = dwPlayServTime + BoosterItem_UseTime[2] * 1000;
		lpPlayInfo->dwLifeBooster_Data = BoosterItem_DataPercent[0];
		return TRUE;
	case (sinBC1 | sin24):
		lpPlayInfo->dwManaBooster_Code = dwItemCode;
		lpPlayInfo->dwManaBooster_Time = dwPlayServTime + BoosterItem_UseTime[0] * 1000;
		lpPlayInfo->dwManaBooster_Data = BoosterItem_DataPercent[1];
		return TRUE;
	case (sinBC1 | sin25):
		lpPlayInfo->dwManaBooster_Code = dwItemCode;
		lpPlayInfo->dwManaBooster_Time = dwPlayServTime + BoosterItem_UseTime[1] * 1000;
		lpPlayInfo->dwManaBooster_Data = BoosterItem_DataPercent[1];
		return TRUE;
	case (sinBC1 | sin26):
		lpPlayInfo->dwManaBooster_Code = dwItemCode;
		lpPlayInfo->dwManaBooster_Time = dwPlayServTime + BoosterItem_UseTime[2] * 1000;
		lpPlayInfo->dwManaBooster_Data = BoosterItem_DataPercent[1];
		return TRUE;
	case (sinBC1 | sin27):
		lpPlayInfo->dwStaminaBooster_Code = dwItemCode;
		lpPlayInfo->dwStaminaBooster_Time = dwPlayServTime + BoosterItem_UseTime[0] * 1000;
		lpPlayInfo->dwStaminaBooster_Data = BoosterItem_DataPercent[2];
		return TRUE;
	case (sinBC1 | sin28):
		lpPlayInfo->dwStaminaBooster_Code = dwItemCode;
		lpPlayInfo->dwStaminaBooster_Time = dwPlayServTime + BoosterItem_UseTime[1] * 1000;
		lpPlayInfo->dwStaminaBooster_Data = BoosterItem_DataPercent[2];
		return TRUE;
	case (sinBC1 | sin29):
		lpPlayInfo->dwStaminaBooster_Code = dwItemCode;
		lpPlayInfo->dwStaminaBooster_Time = dwPlayServTime + BoosterItem_UseTime[2] * 1000;
		lpPlayInfo->dwStaminaBooster_Data = BoosterItem_DataPercent[2];
		return TRUE;
	}


	if(lpPlayInfo->Position.Area != rsCASTLE_FIELD)
		return FALSE;

	switch(dwItemCode)
	{
	case (sinBC1 | sin01):
		lpPlayInfo->dwSiegeItem_Scroll_Time = dwPlayServTime + 30 * 1000;
		lpPlayInfo->dwSiegeItem_Scroll_Code = dwItemCode;
		lpPlayInfo->dwSiegeItem_Scroll_Param = 2;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBC1 | sin02):
		lpPlayInfo->dwSiegeItem_Scroll_Time = dwPlayServTime + 30 * 1000;
		lpPlayInfo->dwSiegeItem_Scroll_Code = dwItemCode;
		lpPlayInfo->dwSiegeItem_Scroll_Param = 5;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBC1 | sin03):
		lpPlayInfo->dwSiegeItem_Scroll_Time = dwPlayServTime + 30 * 1000;
		lpPlayInfo->dwSiegeItem_Scroll_Code = dwItemCode;
		lpPlayInfo->dwSiegeItem_Scroll_Param = 5;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBC1 | sin04):
	case (sinBC1 | sin05):
		return FALSE;



	case (sinBC1 | sin06):
		lpPlayInfo->dwSiegeItem_Stone1_Time = dwPlayServTime + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone1_Code = snCHAR_SOUND_CASTLE_CRYSTAL_R;
		lpPlayInfo->dwSiegeItem_Stone1_Param = 50;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBC1 | sin07):
		lpPlayInfo->dwSiegeItem_Stone1_Time = dwPlayServTime + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone1_Code = snCHAR_SOUND_CASTLE_CRYSTAL_B;
		lpPlayInfo->dwSiegeItem_Stone1_Param = 50;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBC1 | sin08):
		lpPlayInfo->dwSiegeItem_Stone1_Time = dwPlayServTime + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone1_Code = snCHAR_SOUND_CASTLE_CRYSTAL_G;
		lpPlayInfo->dwSiegeItem_Stone1_Param = 50;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBC1 | sin09):
		lpPlayInfo->dwSiegeItem_Stone2_Time = dwPlayServTime + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone2_Code = JOBCODE_FIGHTER;
		lpPlayInfo->dwSiegeItem_Stone2_Param = 20;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBC1 | sin10):
		lpPlayInfo->dwSiegeItem_Stone2_Time = dwPlayServTime + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone2_Code = JOBCODE_MECHANICIAN;
		lpPlayInfo->dwSiegeItem_Stone2_Param = 20;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBC1 | sin11):
		lpPlayInfo->dwSiegeItem_Stone2_Time = dwPlayServTime + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone2_Code = JOBCODE_PIKEMAN;
		lpPlayInfo->dwSiegeItem_Stone2_Param = 20;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBC1 | sin12):
		lpPlayInfo->dwSiegeItem_Stone2_Time = dwPlayServTime + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone2_Code = JOBCODE_ARCHER;
		lpPlayInfo->dwSiegeItem_Stone2_Param = 20;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBC1 | sin13):
		lpPlayInfo->dwSiegeItem_Stone2_Time = dwPlayServTime + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone2_Code = JOBCODE_KNIGHT;
		lpPlayInfo->dwSiegeItem_Stone2_Param = 20;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBC1 | sin14):
		lpPlayInfo->dwSiegeItem_Stone2_Time = dwPlayServTime + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone2_Code = JOBCODE_ATALANTA;
		lpPlayInfo->dwSiegeItem_Stone2_Param = 20;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBC1 | sin15):
		lpPlayInfo->dwSiegeItem_Stone2_Time = dwPlayServTime + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone2_Code = JOBCODE_MAGICIAN;
		lpPlayInfo->dwSiegeItem_Stone2_Param = 20;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBC1 | sin16):
		lpPlayInfo->dwSiegeItem_Stone2_Time = dwPlayServTime + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone2_Code = JOBCODE_PRIESTESS;
		lpPlayInfo->dwSiegeItem_Stone2_Param = 20;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	}

	return TRUE;
}



int RecordBlessCastleLOG(rsUSER_LIST_TOP10 *lpUserListDamageTop10)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];
	char	szBuff2[4096];
	int cnt;

	GetLocalTime(&st);
	wsprintf(szFileName, filenameBlessCaslte, HackLogDirectory, st.wMonth, st.wDay);


	wsprintf(szBuff2, "=================== Check Time [ %d:%d:%d ] =====================\r\n",
		st.wHour, st.wMinute, st.wSecond);


	for(cnt = 0; cnt < 10; cnt++)
	{

		wsprintf(szBuff, "%d> ClanCode[%d] Damage:%d Count:%d \r\n",
			cnt + 1,
			lpUserListDamageTop10->dwUserCode[cnt],
			lpUserListDamageTop10->Damage[cnt],
			lpUserListDamageTop10->Damage[cnt],
			lpUserListDamageTop10->Counter[cnt]);

		lstrcat(szBuff2, szBuff);

	}

	wsprintf(szBuff, "* Tower Crystal ( %d %d %d %d )\r\n",
		lpUserListDamageTop10->bCrystalTowerCount[0],
		lpUserListDamageTop10->bCrystalTowerCount[1],
		lpUserListDamageTop10->bCrystalTowerCount[2],
		lpUserListDamageTop10->bCrystalTowerCount[3]);

	lstrcat(szBuff2, szBuff);


	if(rsBlessCastle.lpChar_ValhallaTower && rsBlessCastle.lpChar_ValhallaTower->Flag && rsBlessCastle.lpChar_ValhallaTower->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_TOWER_B)
	{
		wsprintf(szBuff, "* ValhallaTower ( %d:%d )/( %d/%d )\r\n",
			rsBlessCastle.lpChar_ValhallaTower->smMonsterInfo.PotionCount,
			rsBlessCastle.lpChar_ValhallaTower->smCharInfo.Life[0],

			rsBlessCastle.lpChar_ValhallaTower->sObject_DisplayLife[0],
			rsBlessCastle.lpChar_ValhallaTower->sObject_DisplayLife[1]);

		lstrcat(szBuff2, szBuff);
	}


	CreateDirectory(DebugLogDirectory, NULL);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff2, lstrlen(szBuff2), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}


int RecordBlessCastleSetup(rsPLAYINFO *lpPlayInfo, smTRANS_BLESSCASTLE *lpBlessCastleSetup)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];
	char	szBuff2[4096];

	GetLocalTime(&st);
	wsprintf(szFileName, filenameBlessCaslte, HackLogDirectory, st.wMonth, st.wDay);

	wsprintf(szBuff, "%d:%d:%d - Name(%s)/IP(%s) MasterClan(%d) Price(%d)\r\n",
		st.wHour, st.wMinute, st.wSecond,
		lpPlayInfo->smCharInfo.szName, lpPlayInfo->lpsmSock->szIPAddr,
		rsBlessCastle.dwMasterClan, lpBlessCastleSetup->Price);

	wsprintf(szBuff2, "%s=> TaxRate(%d) Tower(%d %d %d %d %d %d) Mercenary(%d %d %d) ClanSkill(%d)\r\n\r\n", szBuff,
		lpBlessCastleSetup->TaxRate,
		lpBlessCastleSetup->Tower[0], lpBlessCastleSetup->Tower[1], lpBlessCastleSetup->Tower[2],
		lpBlessCastleSetup->Tower[3], lpBlessCastleSetup->Tower[4], lpBlessCastleSetup->Tower[5],
		lpBlessCastleSetup->MercenaryNum[0], lpBlessCastleSetup->MercenaryNum[1], lpBlessCastleSetup->MercenaryNum[2],
		lpBlessCastleSetup->ClanSkill);


	CreateDirectory(DebugLogDirectory, NULL);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff2, lstrlen(szBuff2), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}



int rsFault_PlayField(rsPLAYINFO *lpPlayInfo, int height)
{
	smTRANS_COMMAND_EX	smTransCommandEx;

	lpPlayInfo->sCheckPlayField_Count[1]++;

	if(lpPlayInfo->WarningCount < 10 && lpPlayInfo->sCheckPlayField_Count[1] >= 3)
	{

		smTransCommandEx.size = sizeof(smTRANS_COMMAND_EX);
		smTransCommandEx.code = OpCode::OPCODE_SET_BLACKLIST;
		smTransCommandEx.WParam = 8860;
		smTransCommandEx.LParam = lpPlayInfo->Position.x / fONE;
		smTransCommandEx.SParam = lpPlayInfo->Position.y / fONE;
		smTransCommandEx.EParam = lpPlayInfo->Position.z / fONE;
		smTransCommandEx.WxParam = lpPlayInfo->Position.Area;
		smTransCommandEx.LxParam = height / fONE;
		smTransCommandEx.SxParam = 0;
		smTransCommandEx.ExParam = 0;

		rsSendDataServer(lpPlayInfo->lpsmSock, &smTransCommandEx);
		lpPlayInfo->WarningCount++;

		lpPlayInfo->sCheckPlayField_Count[1] = 0;
	}

	return TRUE;
}


int rsCheckPlayField(rsPLAYINFO *lpPlayInfo)
{

	if(!rsServerConfig.CheckPlayField) return TRUE;

	lpPlayInfo->sCheckPlayField_Count[0]++;

	if((lpPlayInfo->sCheckPlayField_Count[0] & 0xF) != 0) return FALSE;



	if(lpPlayInfo->Position.Area > STAGE_AREA_MAX || lpPlayInfo->Position.Area < 0)
	{
		rsFault_PlayField(lpPlayInfo, 0);
		return FALSE;
	}

	STG_AREA	*lpStgArea = &StageArea[lpPlayInfo->Position.Area];
	smSTAGE3D	*lpStage = lpStgArea->lpStage;
	int	height;
	int heCnt;

	if(!lpStage)
	{
		rsFault_PlayField(lpPlayInfo, 0);
		return FALSE;
	}

	height = lpStage->CheckFloorFaceHeight(lpPlayInfo->Position.x, lpPlayInfo->Position.y, lpPlayInfo->Position.z, 10 * fONE);
	if(height > 0)
	{
		heCnt = 0;
		height = lpStage->CheckFloorFaceHeight(lpPlayInfo->Position.x + 4 * fONE, lpPlayInfo->Position.y + 4 * fONE, lpPlayInfo->Position.z, 10 * fONE);
		if(height > 0) heCnt++;
		height = lpStage->CheckFloorFaceHeight(lpPlayInfo->Position.x + 4 * fONE, lpPlayInfo->Position.y - 4 * fONE, lpPlayInfo->Position.z, 10 * fONE);
		if(height > 0) heCnt++;
		height = lpStage->CheckFloorFaceHeight(lpPlayInfo->Position.x - 4 * fONE, lpPlayInfo->Position.y + 4 * fONE, lpPlayInfo->Position.z, 10 * fONE);
		if(height > 0) heCnt++;
		height = lpStage->CheckFloorFaceHeight(lpPlayInfo->Position.x - 4 * fONE, lpPlayInfo->Position.y - 4 * fONE, lpPlayInfo->Position.z, 10 * fONE);
		if(height > 0) heCnt++;

		height = lpStage->CheckFloorFaceHeight(lpPlayInfo->Position.x + 0 * fONE, lpPlayInfo->Position.y + 2 * fONE, lpPlayInfo->Position.z, 10 * fONE);
		if(height > 0) heCnt++;
		height = lpStage->CheckFloorFaceHeight(lpPlayInfo->Position.x + 0 * fONE, lpPlayInfo->Position.y - 2 * fONE, lpPlayInfo->Position.z, 10 * fONE);
		if(height > 0) heCnt++;
		height = lpStage->CheckFloorFaceHeight(lpPlayInfo->Position.x + 2 * fONE, lpPlayInfo->Position.y + 0 * fONE, lpPlayInfo->Position.z, 10 * fONE);
		if(height > 0) heCnt++;
		height = lpStage->CheckFloorFaceHeight(lpPlayInfo->Position.x - 2 * fONE, lpPlayInfo->Position.y - 0 * fONE, lpPlayInfo->Position.z, 10 * fONE);
		if(height > 0) heCnt++;

		if(heCnt >= 8)
		{
			rsFault_PlayField(lpPlayInfo, height);
			return FALSE;
		}
	}

	lpPlayInfo->sCheckPlayField_Count[1] = 0;

	return TRUE;
}

#define PRESENTITEM_LEVEL_MAX		4

#include "AutoDropItem.h"



DWORD rsLowLevelItem(rsPLAYINFO *lpPlayInfo, smCHAR *lpChar)
{
	int rnd;
	int lev, job;
	int SelCnt;

	if(!lpPlayInfo->sLowLevel_PresentItem[0] || lpPlayInfo->sLowLevel_PresentItem[0] >= PRESENTITEM_LEVEL_MAX) return NULL;

	if(abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level) > 8)
		return NULL;
	job = lpPlayInfo->smCharInfo.JOB_CODE - 1;
	if(job < 0 || job >= 8) return NULL;

	if(lpPlayInfo->dwCode_Name & 1)
		lev = rsPresentItem_LevelType_1[job][lpPlayInfo->sLowLevel_PresentItem[0]][0];
	else
		lev = rsPresentItem_LevelType_2[job][lpPlayInfo->sLowLevel_PresentItem[0]][0];

	if(lpPlayInfo->smCharInfo.Level < lev) return NULL;

	rnd = (lpPlayInfo->smCharInfo.Level - lev + 1) * 5;

	if((rand() % 1000) < rnd)
	{

		SelCnt = lpPlayInfo->sLowLevel_PresentItem[0];

		lpPlayInfo->sLowLevel_PresentItem[0]++;


		rsUpdateServerParam(lpPlayInfo, smUPDATE_PARAM_LOWUSER_PRESENT, lpPlayInfo->sLowLevel_PresentItem[0], lpPlayInfo->sLowLevel_PresentItem[1], TRUE);

		if(lpPlayInfo->smCharInfo.Level < (lev + 10))
		{

#ifdef _TEST_SERVER
			TRANS_CHATMESSAGE TransChatMessage;

			if(lpPlayInfo->getSecurity() > AccountTypes::SEC_VIP)
			{
				wsprintf(TransChatMessage.szMessage, "필연적 아이템 과의 만남( %d )", SelCnt);
				TransChatMessage.code = OpCode::OPCODE_CHATMESSAGE;
				TransChatMessage.dwIP = 0;
				TransChatMessage.dwObjectSerial = 0;
				TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);

				lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
			}
#endif

			if(lpPlayInfo->dwCode_Name & 1)
				return rsPresentItem_LevelType_1[job][SelCnt][1];
			else
				return rsPresentItem_LevelType_2[job][SelCnt][1];
		}
	}

	return NULL;
}


int rsRecvUpdateServerParam(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{

	switch(lpTransCommand->WParam)
	{
	case smUPDATE_PARAM_LOWUSER_PRESENT:
		lpPlayInfo->sLowLevel_PresentItem[0] = lpTransCommand->LParam;
		lpPlayInfo->sLowLevel_PresentItem[1] = lpTransCommand->SParam;
		break;
	}

	return TRUE;
}


int	rsUpdateServerParam(rsPLAYINFO *lpPlayInfo, DWORD dwUpdateCode, int Param1, int Param2, int TargetMode)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = OpCode::OPCODE_UPDATE_SERVER_PARAM;
	smTransCommand.WParam = dwUpdateCode;
	smTransCommand.LParam = Param1;
	smTransCommand.SParam = Param2;
	smTransCommand.EParam = rsServerConfig.ServerCode;

	if(lpPlayInfo->lpsmSock)
	{
		if(TargetMode)
			return rsSendDataServer(lpPlayInfo->lpsmSock, &smTransCommand);
		else
			return rsSendGameServer(lpPlayInfo->lpsmSock, &smTransCommand);
	}

	return NULL;
}



int rsStartUser_PresentItem(rsPLAYINFO *lpPlayInfo)
{
	TRANS_CHATMESSAGE TransChatMessage;
	sDEF_ITEMINFO *lpDefItem = 0;

	switch(lpPlayInfo->dwStartUser_PresentItem_Count)
	{

	case 1:
		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_ARCHER)
			lpDefItem = rsPutItem3(lpPlayInfo, (sinWS1 | sin01));
		else if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_ATALANTA)
			lpDefItem = rsPutItem3(lpPlayInfo, (sinWT1 | sin01));
		else if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MAGICIAN)
			lpDefItem = rsPutItem3(lpPlayInfo, (sinWM1 | sin01));
		else if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_PRIESTESS)
			lpDefItem = rsPutItem3(lpPlayInfo, (sinWM1 | sin01));
		else
		{

			switch(rand() % 3)
			{
			case 0:
				lpDefItem = rsPutItem3(lpPlayInfo, (sinWS2 | sin01));
				break;
			case 1:
				lpDefItem = rsPutItem3(lpPlayInfo, (sinWA1 | sin01));
				break;
			case 2:
				lpDefItem = rsPutItem3(lpPlayInfo, (sinWH1 | sin01));
				break;
			}
		}
		break;
	case 2:
		if(lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MAGICIAN || lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_PRIESTESS)
			lpDefItem = rsPutItem3(lpPlayInfo, (sinDA2 | sin02));
		else
			lpDefItem = rsPutItem3(lpPlayInfo, (sinDA1 | sin02));
		break;

	case 3:
		lpDefItem = rsPutItem3(lpPlayInfo, (sinGP1 | sin01));
		break;
	case 4:
		lpDefItem = rsPutItem3(lpPlayInfo, (sinGP1 | sin01));
		break;
	case 5:
		lpDefItem = rsPutItem3(lpPlayInfo, (sinGP1 | sin01));
		break;
#ifdef _LANGUAGE_PHILIPIN	
	case 6:
		lpDefItem = rsPutItem3(lpPlayInfo, (sinPL1 | sin02));
		break;
	case 7:
		lpDefItem = rsPutItem3(lpPlayInfo, (sinPL1 | sin02));
		break;
	case 8:
		lpDefItem = rsPutItem3(lpPlayInfo, (sinPL1 | sin02));
		break;
	case 9:
		lpDefItem = rsPutItem3(lpPlayInfo, (sinPL1 | sin02));
		break;
	case 10:
		lpDefItem = rsPutItem3(lpPlayInfo, (sinPL1 | sin02));
		break;
	case 11:
		lpDefItem = rsPutItem3(lpPlayInfo, (sinPS1 | sin02));
		break;
	case 12:
		lpDefItem = rsPutItem3(lpPlayInfo, (sinPS1 | sin02));
		break;
	case 13:
		lpDefItem = rsPutItem3(lpPlayInfo, (sinPS1 | sin02));
		break;
	case 14:
		lpDefItem = rsPutItem3(lpPlayInfo, (sinPS1 | sin02));
		break;
	case 15:
		lpDefItem = rsPutItem3(lpPlayInfo, (sinPS1 | sin02));
		break;
#endif
	}


	if(lpDefItem)
	{
		wsprintf(TransChatMessage.szMessage, srMsg_StartUser_PresentItem, lpDefItem->Item.ItemName);
		TransChatMessage.code = OpCode::OPCODE_MESSAGEBOX;
		TransChatMessage.dwIP = 0;
		TransChatMessage.dwObjectSerial = 0;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);

		lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);

		smTRANS_COMMAND	smTransCommand;
		smTransCommand.code = OpCode::OPCODE_NOTICE_BOX;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = lpDefItem->Item.CODE;
		smTransCommand.LParam = 0;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = 0;
		lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
	}

	lpPlayInfo->dwStartUser_PresentItem_Count++;
#ifndef _LANGUAGE_PHILIPIN
	lpPlayInfo->dwStartUser_PresentItem_Time = dwPlayServTime + 1000 * 60 * 1;
#else 
	lpPlayInfo->dwStartUser_PresentItem_Time = dwPlayServTime + 1000 * 3 * 1;
#endif

	return TRUE;
}


int rsSendUserID_MainServer(rsPLAYINFO *lpPlayInfo)
{

	smTRANS_CHAR_COMMAND2	smTransCharCommand;

	smTransCharCommand.code = OpCode::OPCODE_USER_ID;
	smTransCharCommand.size = sizeof(smTRANS_CHAR_COMMAND2);
	smTransCharCommand.WParam = 0;
	smTransCharCommand.LParam = 0;
	smTransCharCommand.SParam = 0;

	strcpy_s(smTransCharCommand.szId, lpPlayInfo->getAccount().c_str());
	strcpy_s(smTransCharCommand.szName, lpPlayInfo->getName().c_str());

	return rsSendGameServer(lpPlayInfo->lpsmSock, &smTransCharCommand);
}

int rsRecvUserID_MainServer(rsPLAYINFO *lpPlayInfo, smTRANS_CHAR_COMMAND2 *lpTransCharCommand)
{
	strcpy_s(lpPlayInfo->szUserExpTimeID, lpTransCharCommand->szId);
	strcpy_s(lpPlayInfo->szUserExpTimeName, lpTransCharCommand->szName);

	if(lpPlayInfo->dwExpGameTimeCheck == 0)
		bSql_GetExpGameTime(lpPlayInfo, 0);

	return TRUE;
}

int rsGetExp_GameTime(rsPLAYINFO *lpPlayInfo)
{

	int gTime = lpPlayInfo->dwExpGameTime / (1000 * 60 * 60);

	if(lpPlayInfo->dwExpGameTimeCheck)
	{
		if(gTime < 3)
		{
			return 100;
		}
		else if(gTime < 5)
		{
			return 50;
		}
		return 0;
	}

	return 100;
}

int rsDispay_GameTime(rsPLAYINFO *lpPlayInfo, DWORD dwTimeOld)
{

	int gTime = lpPlayInfo->dwExpGameTime / (1000 * 60);
	int gTimeOld = dwTimeOld / (1000 * 60);
	bool	bDisplay = true;
	int	Remainder = 0;
	int	OldRemainder = 0;
	TRANS_CHATMESSAGE	TransChatMessage;
	memset(&TransChatMessage, 0, sizeof(TRANS_CHATMESSAGE));



	if(gTime >= 1 * 60 && gTimeOld < 1 * 60)
	{
		wsprintf(TransChatMessage.szMessage, MSG_TL_1_00);
	}
	else if(gTime >= 2 * 60 && gTimeOld < 2 * 60)
	{
		wsprintf(TransChatMessage.szMessage, MSG_TL_2_00);
	}

	else if(gTime >= 3 * 60 && gTimeOld < 3 * 60)
	{
		wsprintf(TransChatMessage.szMessage, MSG_TL_3_00);
	}
	else if(gTime >= (3 * 60 + 30) && gTimeOld < (3 * 60 + 30))
	{
		wsprintf(TransChatMessage.szMessage, MSG_TL_3_30);
	}
	else if(gTime >= 4 * 60 && gTimeOld < 4 * 60)
	{
		wsprintf(TransChatMessage.szMessage, MSG_TL_4_00);
	}
	else if(gTime >= (4 * 60 + 30) && gTimeOld < (4 * 60 + 30))
	{
		wsprintf(TransChatMessage.szMessage, MSG_TL_4_30);
	}

	else if(gTime >= 5 * 60)
	{
		Remainder = gTime % 60;
		OldRemainder = gTimeOld % 60;

		wsprintf(TransChatMessage.szMessage, MSG_TL_X_00);

		if(OldRemainder < 15 && Remainder >= 15)
		{
		}
		else if(OldRemainder < 30 && Remainder >= 30)
		{
		}
		else if(OldRemainder < 45 && Remainder >= 45)
		{
		}
		else if(OldRemainder > Remainder)
		{
		}
		else
		{
			bDisplay = false;
		}
	}

	else
	{
		bDisplay = false;
	}


	if(bDisplay == true)
	{
		TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		TransChatMessage.dwIP = 3;
		TransChatMessage.dwObjectSerial = 0;
		lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
	}

	return 0;
}



int	rsHackTrap_FieldNPC[] = {
	sinNPC_SHOP,
	0,
	0,
	sinNPC_SHOP | sinNPC_MIX | sinNPC_WARE | sinNPC_SKILL | sinNPC_FORCE | sinNPC_MANUFACTURE,
	0,
	0,
	sinNPC_SHOP | sinNPC_WARE,
	sinNPC_SHOP,
	0,
	sinNPC_SHOP,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	sinNPC_SHOP,
	0,
	0,
	sinNPC_SHOP | sinNPC_AGING | sinNPC_WARE | sinNPC_SKILL | sinNPC_FORCE | sinNPC_SMELTING,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	sinNPC_SHOP | sinNPC_WARE | sinNPC_FORCE,
	0,
	0,
	0,
	sinNPC_SHOP | sinNPC_WARE,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
};

int rsRecvHackTrap(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCharCommand)
{
	smTRANS_COMMAND	smTransCommand;

	switch(lpTransCharCommand->WParam)
	{
	case 100:

		if((rsHackTrap_FieldNPC[lpTransCharCommand->SParam] & lpTransCharCommand->LParam) == 0)
		{
			if(lpPlayInfo->WarningCount < 20 || rsServerConfig.TestSeverMode)
			{
				smTransCommand.WParam = 8900;
				smTransCommand.LParam = lpTransCharCommand->SParam;
				smTransCommand.SParam = lpTransCharCommand->LParam;
				RecordHackLogFile(lpPlayInfo, &smTransCommand);
			}
		}
		break;

	}

	return TRUE;
}

#ifdef _CHECK_MESH

static DWORD	dwItemMeshCode = 0;
int rsRecvCheckItemMesh(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{
	smTRANS_COMMAND		smTransCommand;

	if(!dwItemMeshCode)
	{
		dwItemMeshCode = lpTransCommand->WParam;
		return TRUE;
	}

	if(dwItemMeshCode != lpTransCommand->WParam)
	{

		smTransCommand.WParam = 8910;
		smTransCommand.LParam = dwItemMeshCode;
		smTransCommand.SParam = lpTransCommand->WParam;
		RecordHackLogFile(lpPlayInfo, &smTransCommand);

		lpPlayInfo->dwHopeDisconnectTime = dwPlayServTime + 60 * 1000;
	}

	return TRUE;
}
#endif

DWORD ManufactureCheckRune(rsPLAYINFO* lpPlayInfo, DWORD RecipeCode, DWORD* pRuneCode)
{

	int RuneCnt = 0;
	DWORD Arm_Armor_Code[5] = { sin01, sin02, sin03, sin04, sin05 };
	DWORD CheckRuneCode[5][1][3] = { {
			//Shelton 1
			{ (sinPR3 | sin01), (sinPR3 | sin02), (sinPR3 | sin03) },},
			//Shelton 2
{			{ (sinPR3 | sin04), (sinPR3 | sin05), (sinPR3 | sin06) },},
			//Shelton 3
{			{ (sinPR3 | sin07), (sinPR3 | sin08), (sinPR3 | sin09) },},
			//Shelton 4
{			{ (sinPR3 | sin10), (sinPR3 | sin11), (sinPR3 | sin12) },},
			//Shelton 5
			{ (sinPR3 | sin13), (sinPR3 | sin14), (sinPR3 | sin15) }, };

	DWORD	dwItem = 0;

	DWORD CreateItemCode[2][5][10] = { {
			//Shelton 1
			{ (sinOS1 | sin18), (sinOS1 | sin18), (sinOS1 | sin18), (sinOS1 | sin18), (sinOS1 | sin18), (sinOS1 | sin18), (sinOS1 | sin18), (sinOS1 | sin18), (sinOS1 | sin18),(sinOS1 | sin18), },
			//Shelton 2
			{ (sinOS1 | sin19), (sinOS1 | sin19), (sinOS1 | sin19), (sinOS1 | sin19), (sinOS1 | sin19), (sinOS1 | sin19), (sinOS1 | sin19), (sinOS1 | sin19), (sinOS1 | sin19),(sinOS1 | sin19), },
			//Shelton 3
			{ (sinOS1 | sin20), (sinOS1 | sin20), (sinOS1 | sin20), (sinOS1 | sin20), (sinOS1 | sin20), (sinOS1 | sin20), (sinOS1 | sin20), (sinOS1 | sin20), (sinOS1 | sin20),(sinOS1 | sin20), },
			//Shelton 4							
			{ (sinOS1 | sin21), (sinOS1 | sin21), (sinOS1 | sin21), (sinOS1 | sin21), (sinOS1 | sin21), (sinOS1 | sin21), (sinOS1 | sin21), (sinOS1 | sin21), (sinOS1 | sin21),(sinOS1 | sin21), },
			//Shelton 5								
			{ (sinOS1 | sin22), (sinOS1 | sin22), (sinOS1 | sin22), (sinOS1 | sin22), (sinOS1 | sin22), (sinOS1 | sin22), (sinOS1 | sin22), (sinOS1 | sin22), (sinOS1 | sin22),(sinOS1 | sin22), },}


	};
	if ((RecipeCode & sinITEM_MASK2) == sinWR1)
	{
		for (int i = 0; i < MAX_RECIPE_KIND; i++)
		{
			if (Arm_Armor_Code[i] == (RecipeCode & sinITEM_MASK3))
			{
				for (int j = 0; j < MAX_RUNE; j++)
				{
					RuneCnt = 0;
					for (int x = 0; x < 3; x++)
					{
						for (int y = 0; y < 3; y++)
						{
							if (CheckRuneCode[i][j][x] == pRuneCode[y + 1])
							{
								RuneCnt++;
								break;
							}
						}
						if (RuneCnt == 3)
						{
							return CreateItemCode[0][i][j];
						}
					}
				}
			}
		}
	}
	return FALSE;
}



int rsPutItem_TreasureBox(rsPLAYINFO *lpPlayInfo, DWORD Code)
{
	TRANS_ITEMINFO	TransItemInfo;
	psITEM	psItem;
	int cnt;
	int nClass = 0;
	int Randum[6][8] =
	{
		{ 2000, 2900, 1000, 1500, 1000, 100, 750, 750 },
		{ 2600, 2620, 700, 1000, 1500, 80, 750, 750 },
		{ 2750, 2400, 800, 1500, 1000, 50, 750, 750 },
		{ 2450, 2850, 500, 1500, 1000, 200, 750, 750 },
		{ 2320, 2000, 1500, 1500, 1000, 180, 750, 750 },
		{ 2850, 2000, 1000, 1500, 1000, 150, 750, 750 }
	};

	switch((Code & sinITEM_MASK3))
	{
	case sin05:
		nClass = 0;
		break;
	case sin06:
		nClass = 1;
		break;
	case sin07:
		nClass = 2;
		break;
	case sin08:
		nClass = 3;
		break;
	case sin09:
		nClass = 4;
		break;
	case sin10:
		nClass = 5;
		break;
	}

	int CodeCount = 0;
	int RndNum = rand() % 10000;
	int RndCnt = 0;
	for(cnt = 0; cnt < 8; cnt++)
	{
		if(Randum[nClass][CodeCount])
		{
			RndCnt += Randum[nClass][cnt];
			if(RndNum < RndCnt)
			{
				CodeCount = cnt;
				break;
			}
		}
	}

	DWORD ItemCode[6][8] =
	{
		{ (sinPM1 | sin04), (sinBI1 | sin08), (sinGP1 | sin19), (sinFO1 | sin08),(sinFO1 | sin08), (sinBI2 | sin09), (sinBI1 | sin21), (sinBI1 | sin19) },
		{ (sinPM1 | sin04), (sinBI1 | sin08), (sinGP1 | sin19), (sinFO1 | sin08),(sinFO1 | sin07), (sinBI2 | sin09), (sinBI1 | sin21), (sinBI1 | sin19) },
		{ (sinPM1 | sin04), (sinBI1 | sin08), (sinGP1 | sin18), (sinFO1 | sin07),(sinFO1 | sin06), (sinBI2 | sin09), (sinBI1 | sin21), (sinBI1 | sin19) },
		{ (sinPM1 | sin03), (sinBI1 | sin08), (sinGP1 | sin18), (sinFO1 | sin06),(sinFO1 | sin05), (sinBI2 | sin05), (sinBI1 | sin21), (sinBI1 | sin19) },
		{ (sinPM1 | sin03), (sinBI1 | sin08), (sinGP1 | sin17), (sinFO1 | sin04),(sinFO1 | sin04), (sinBI2 | sin05), (sinBI1 | sin21), (sinBI1 | sin19) },
		{ (sinPM1 | sin02), (sinBI1 | sin08), (sinGP1 | sin17), (sinFO1 | sin04),(sinFO1 | sin04), (sinBI2 | sin05), (sinBI1 | sin21), (sinBI1 | sin19) }
	};
	if((Code & sinITEM_MASK2) == sinSP1)
	{

		for(int j = 0; j < DefaultItemCount; j++)
		{

			if(ItemCode[nClass][CodeCount] == DefaultItems[j].Item.CODE)
			{
				CreateDefItem(&psItem.ItemInfo, &DefaultItems[j]);
				if(CodeCount == 0)
				{
					psItem.ItemInfo.PotionCount = 10;
				}
				if(lpPlayInfo->lpsmSock)
				{
					TransItemInfo.code = OpCode::OPCODE_PUTITEM;
					TransItemInfo.size = sizeof(TRANS_ITEMINFO);
					memcpy(&TransItemInfo.Item, &psItem.ItemInfo, sizeof(sITEMINFO));

					ReformItem(&TransItemInfo.Item);
					rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);
					lpPlayInfo->lpsmSock->Send((char *)&TransItemInfo, TransItemInfo.size, TRUE);
				}
				return TRUE;
			}
		}
	}
	return TRUE;
}


int rsPutItem_CapsuleItem(rsPLAYINFO *lpPlayInfo, DWORD Code)
{
	TRANS_ITEMINFO	TransItemInfo;
	psITEM	psItem;
	int cnt;
	int nClass = 0;
	int Randum[1][12] =
	{
		{ 1000, 500, 1000,  1000,  1000,  800, 1000, 600,  1000,  1000,  800, 300}
	};

	switch((Code & sinITEM_MASK3))
	{
	case sin34:
		nClass = 0;
		break;
	}

	int CodeCount = 0;
	int RndNum = rand() % 10000;
	int RndCnt = 0;
	for(cnt = 0; cnt < 12; cnt++)
	{
		if(Randum[nClass][CodeCount])
		{
			RndCnt += Randum[nClass][cnt];
			if(RndNum < RndCnt)
			{
				CodeCount = cnt;
				break;
			}
		}
	}

	DWORD ItemCode[1][12] =
	{
		{ (sinFO1 | sin06), (sinFO1 | sin06), (sinFO1 | sin07), (sinFO1 | sin08), (sinFO1 | sin09), (sinFO1 | sin10),
		(sinFO1 | sin25), (sinFO1 | sin25), (sinFO1 | sin26), (sinFO1 | sin27), (sinFO1 | sin28), (sinSE1 | sin01) }
	};

	if((Code & sinITEM_MASK2) == sinSP1)
	{

		for(int j = 0; j < DefaultItemCount; j++)
		{

			if(ItemCode[nClass][CodeCount] == DefaultItems[j].Item.CODE)
			{
				CreateDefItem(&psItem.ItemInfo, &DefaultItems[j]);
				if(CodeCount == 10 || CodeCount == 11)
				{
					psItem.ItemInfo.PotionCount = 30;
				}

				if(lpPlayInfo->lpsmSock)
				{
					TransItemInfo.code = OpCode::OPCODE_PUTITEM;
					TransItemInfo.size = sizeof(TRANS_ITEMINFO);
					memcpy(&TransItemInfo.Item, &psItem.ItemInfo, sizeof(sITEMINFO));
					ReformItem(&TransItemInfo.Item);
					rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);
					lpPlayInfo->lpsmSock->Send((char *)&TransItemInfo, TransItemInfo.size, TRUE);
				}
				return TRUE;
			}
		}
	}
	return TRUE;

}


int rsSendAreaOpenKidMonster(rsPLAYINFO	*lpPlayInfo, smCHAR *lpChar)
{
	int cnt2;

	for(cnt2 = 0; cnt2 < srKIDMONSTER_MAX; cnt2++)
	{
		if(lstrcmp(lpChar->smCharInfo.szName, srOpenKidMonster[cnt2].szParentMonName) == 0)
		{
			smTRANS_COMMAND smTransCommand;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.code = OpCode::OPCODE_OPENMONSTER;
			smTransCommand.WParam = lpChar->pX;
			smTransCommand.SParam = lpChar->pY;
			smTransCommand.LParam = lpChar->pZ;
			smTransCommand.EParam = srOpenKidMonster[cnt2].mon_Num;;
			rsSendAreaServer(lpPlayInfo->lpsmSock, &smTransCommand);

			break;
		}
	}

	return TRUE;
}


int rsOpenKidMonster(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand, int mon_Num)
{
	int x = 0;
	int z = 0;
	STG_AREA		*lpStgArea;
	STG_CHAR_INFO	StgCharInfo;
	smCHAR			*lpChar;

	for(int cnt = 0; cnt < chrMonsterCnt; cnt++)
	{
		if(lstrcmp(chrMonsterList[cnt].szName, srOpenKidMonster[mon_Num].szChildMonName) == 0)
		{
			for(int i = 0; i < srOpenKidMonster[mon_Num].mon_Count; i++)
			{
				x = rand() % (128 * fONE);
				z = rand() % (128 * fONE);
				x -= 64 * fONE;
				z -= 64 * fONE;
				lpStgArea = FindStageField(lpPlayInfo->Position.x, lpPlayInfo->Position.z);

				if(lpStgArea)
				{
					StgCharInfo.PosiState = smCHAR_STATE_ENEMY;
					StgCharInfo.smCharInfo.Life[0] = 100;
					StgCharInfo.smCharInfo.Mana[0] = 100;
					StgCharInfo.smCharInfo.Life[1] = 100;
					StgCharInfo.smCharInfo.State = TRUE;

					memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));

					lpStgArea->EvnMonster = TRUE;
					lpChar = lpStgArea->OpenMonster(&StgCharInfo, 0);
					if(lpChar)
					{
						lpChar->pX = lpTransCommand->WParam + x;
						lpChar->pY = lpTransCommand->SParam;
						lpChar->pZ = lpTransCommand->LParam + z;
						lpChar->DistAroundDbl = 0;
						lpChar->SetMotionFromCode(CHRMOTION_STATE_STAND);
						lpChar->TargetMoveCount = 0;

						smTRANS_COMMAND_EX	TransCommandEx;

						ZeroMemory(&TransCommandEx, sizeof(smTRANS_COMMAND_EX));
						TransCommandEx.WParam = smCOMMNAD_USER_WARP;
						TransCommandEx.LParam = lpTransCommand->WParam + x;
						TransCommandEx.SParam = lpTransCommand->SParam;
						TransCommandEx.EParam = lpTransCommand->LParam + z;
						rsSendCommandUser(lpPlayInfo, &TransCommandEx);
					}
				}
			}
			break;
		}
	}

	return TRUE;
}



int rsSendAreaOpenSODGuardMonster(rsPLAYINFO *lpPlayInfo, smCHAR *lpChar)
{
	int cnt2;

	for(cnt2 = 0; cnt2 < srSOD_GUARD_MONSTER_MAX; cnt2++)
	{
		if(lstrcmp(lpChar->smCharInfo.szName, srOpenSODCrystalGuardMonster[cnt2].szParentMonName) == 0)
		{
			smTRANS_COMMAND smTransCommand;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.code = OpCode::OPCODE_OPENMONSTER;
			smTransCommand.WParam = lpChar->pX;
			smTransCommand.SParam = lpChar->pY;
			smTransCommand.LParam = lpChar->pZ;
			smTransCommand.EParam = srOpenSODCrystalGuardMonster[cnt2].mon_Num;
			rsSendAreaServer(lpPlayInfo->lpsmSock, &smTransCommand);

			break;
		}
	}

	return TRUE;
}



int rsOpenSODGuardMonster(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand, int mon_Num)
{
	int x = 0;
	int z = 0;
	STG_AREA		*lpStgArea;
	STG_CHAR_INFO	StgCharInfo;
	smCHAR			*lpChar;
	int mon_x = 0;
	int mon_z = 0;
	int dist = 0;
	int rand_num = 0;

	if(mon_Num == 4)
	{
		rand_num = 4;
	}
	else
		rand_num = GetRandomPos(0, 2);

	for(int cnt = 0; cnt < chrMonsterCnt; cnt++)
	{
		if(lstrcmp(chrMonsterList[cnt].szName, srOpenSODCrystalGuardMonster[rand_num].szChildMonName) == 0)
		{
			for(int j = 0; j < 7; j++)
			{
				if(lpPlayInfo->Position.Area == rsSOD_CRYSTAL_GUARD_MONSTER_POS[j][0])
				{
					mon_x = abs(lpTransCommand->WParam / fONE - rsSOD_CRYSTAL_GUARD_MONSTER_POS[j][1]);
					mon_z = abs(lpTransCommand->LParam / fONE - rsSOD_CRYSTAL_GUARD_MONSTER_POS[j][2]);
					dist = mon_x*mon_x + mon_z*mon_z;
					if(dist < 300 * 300)
					{
						for(int i = 0; i < srOpenSODCrystalGuardMonster[rand_num].mon_Count; i++)
						{
							x = rand() % (128 * fONE);
							z = rand() % (128 * fONE);
							x -= 64 * fONE;
							z -= 64 * fONE;
							lpStgArea = FindStageField(lpPlayInfo->Position.x, lpPlayInfo->Position.z);

							if(lpStgArea)
							{
								StgCharInfo.PosiState = smCHAR_STATE_ENEMY;
								StgCharInfo.smCharInfo.Life[0] = 100;
								StgCharInfo.smCharInfo.Mana[0] = 100;
								StgCharInfo.smCharInfo.Life[1] = 100;
								StgCharInfo.smCharInfo.State = TRUE;

								memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));

								lpStgArea->EvnMonster = TRUE;
								lpChar = lpStgArea->OpenMonster(&StgCharInfo, 0);
								if(lpChar)
								{
									lpChar->pX = rsSOD_CRYSTAL_GUARD_MONSTER_POS[j][1] * fONE + x;
									lpChar->pY = lpTransCommand->SParam;
									lpChar->pZ = rsSOD_CRYSTAL_GUARD_MONSTER_POS[j][2] * fONE + z;
									lpChar->PosiAround.x = rsSOD_CRYSTAL_GUARD_MONSTER_POS[j][1] * fONE + x;
									lpChar->PosiAround.y = lpTransCommand->SParam;
									lpChar->PosiAround.z = rsSOD_CRYSTAL_GUARD_MONSTER_POS[j][2] * fONE + z;
									lpChar->DistAroundDbl = DIST_AROUND_MIDDLE;
									lpChar->SetMotionFromCode(CHRMOTION_STATE_STAND);
									lpChar->TargetMoveCount = 0;

									smTRANS_COMMAND_EX	TransCommandEx;

									ZeroMemory(&TransCommandEx, sizeof(smTRANS_COMMAND_EX));
									TransCommandEx.WParam = smCOMMNAD_USER_WARP;
									TransCommandEx.LParam = rsSOD_CRYSTAL_GUARD_MONSTER_POS[j][1] * fONE + x;
									TransCommandEx.SParam = lpTransCommand->SParam;
									TransCommandEx.EParam = rsSOD_CRYSTAL_GUARD_MONSTER_POS[j][2] * fONE + z;
									rsSendCommandUser(lpPlayInfo, &TransCommandEx);
								}
							}
						}

					}
				}
			}
			break;
		}
	}

	return TRUE;
}



int rsFiltChatMsg(rsPLAYINFO *lpPlayInfo, char *szMsg, int len)
{

	sveFiltChatMsg(lpPlayInfo, szMsg, len);

	return TRUE;
}


int rsRecvEventGame(rsPLAYINFO *lpPlayInfo, smTRANS_COMMAND *lpTransCommand)
{

	switch(lpTransCommand->WParam)
	{
	case smCODE_EVENT_STATE_INIT:
		rsEventGame_State_Init(lpPlayInfo, lpTransCommand);
		break;
	}

	return TRUE;
}


int	rsUseSoccerBallPotionItem(DWORD dwItemCode, rsPLAYINFO *lpPlayInfo)
{
	smTRANS_COMMAND	smTransCommand;

	if(dwItemCode != (sinSP1 | sin40))
		return -1;

	switch(dwItemCode)
	{
	case (sinSP1 | sin40):
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = OpCode::OPCODE_COMIC_SKIN;
		smTransCommand.WParam = 3;
		smTransCommand.LParam = 60 * 60 * 3;
		smTransCommand.SParam = 1;
		smTransCommand.EParam = 0;
		lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
		break;
	}

	return TRUE;
}


int SetAgingItem(sITEMINFO *pItem, int AgingNum)
{
	pItem->ItemKindCode = ITEM_KIND_AGING;


	if(((pItem->CODE & sinITEM_MASK2) >= sinWA1) && ((pItem->CODE & sinITEM_MASK2) <= sinDA2))
	{
		for(int i = 0; i < AgingNum; i++)
		{
			sinSetAgingItemIncreState(pItem);
		}
	}

	return TRUE;
}



#ifdef _XIGNCODE_SERVER

int rsXignCode_resultCode_Verify(rsPLAYINFO *lpPlayInfo, XIGNCODE_PACKET *packet)
{
	if(ZSWAVE_Verify(lpPlayInfo->Xigncode_tempdata.xigncode_handle, (CPACKETDATA)packet->data, sizeof(packet->data)) != TRUE)
	{

		char szReport[128];
		int result_data = ZSWAVE_VerifyEx(lpPlayInfo->Xigncode_tempdata.xigncode_handle, (char *)packet->data, sizeof(packet->data), szReport, sizeof(szReport));

		switch(result_data)
		{
		case Z_RTN_NONCLIENT:
			rsXignCode_recordLog::getInstance()->output(lpPlayInfo, 8930, Z_RTN_NONCLIENT, szReport);
				lpPlayInfo->dwHopeDisconnectTime = dwPlayServTime + 5000;
			break;

		case Z_RTN_BLACK_CODE:
			rsXignCode_recordLog::getInstance()->output(lpPlayInfo, 8930, Z_RTN_BLACK_CODE, szReport);
				lpPlayInfo->dwHopeDisconnectTime = dwPlayServTime + 5000;
			break;

		case Z_RTN_SUSPICIOUS:


			break;

		case Z_RTN_USERDEFINED:


			break;

		case Z_RTN_RESEND:
			lpPlayInfo->Xigncode_tempdata.m_ceComplete = FALSE;
			rsXignCode_recordLog::getInstance()->output(lpPlayInfo, 8930, Z_RTN_RESEND, szReport);
				break;

		default:
			break;
		}
	}


	ZSWAVE_Close(lpPlayInfo->Xigncode_tempdata.xigncode_handle);
	lpPlayInfo->Xigncode_tempdata.xigncode_handle = NULL;

	return TRUE;
}


int rsXignCode_recordLog::getInstance()->output(rsPLAYINFO *lpPlayInfo, int msg_num, int result_data, char *szReport)
{
	char *return_value[6] = {
			"0"
			"Z_RTN_NONCLIENT",
			"Z_RTN_BLACK_CODE",
			"Z_RTN_SUSPICIOUS",
			"Z_RTN_USERDEFINED",
			"Z_RTN_RESEND"
	};

	smTRANS_COMMAND		smTransCommand;
	smTransCommand.WParam = msg_num;
	smTransCommand.LParam = (DWORD)return_value[result_data - 1];
	smTransCommand.SParam = (DWORD)szReport;
	smTransCommand.EParam = result_data;
	RecordHackLogFile(lpPlayInfo, &smTransCommand);

	return TRUE;
}





int rsXignCode_selected_code_SendPacket(rsPLAYINFO *lpPlayInfo)
{
	XIGNCODE_PACKET pkt;
	memset(&pkt, 0, sizeof(pkt));
	int scan_Type = lpPlayInfo->Xigncode_tempdata.m_type;

	if(lpPlayInfo->Xigncode_tempdata.dwWaitTime_NC < dwPlayServTime + 1)
	{
		switch(scan_Type)
		{
		case 1:
			lpPlayInfo->Xigncode_tempdata.xigncode_handle = ZSWAVE_Open(PACKET_SIZE, Z_SCAN_TYPE_ANTI_CHEAT_ENGINE);
			lpPlayInfo->Xigncode_tempdata.m_pcount = ZSWAVE_GetDataCount(lpPlayInfo->Xigncode_tempdata.xigncode_handle);
			break;
		case 2:
			lpPlayInfo->Xigncode_tempdata.xigncode_handle = ZSWAVE_Open(PACKET_SIZE, Z_SCAN_TYPE_ANTI_NONECLIENTBOT);
			lpPlayInfo->Xigncode_tempdata.m_pcount = ZSWAVE_GetDataCount(lpPlayInfo->Xigncode_tempdata.xigncode_handle);
			break;
		default:
			break;
		}

		for(int i = 0; i < lpPlayInfo->Xigncode_tempdata.m_pcount; i++)
		{
			if(ZSWAVE_GetDataAt(lpPlayInfo->Xigncode_tempdata.xigncode_handle, i, (char *)pkt.data) != TRUE)
			{
				return FALSE;
			}

			pkt.code = OpCode::OPCODE_XIGNCODE_PACKET;
			pkt.size = sizeof(pkt);
			lpPlayInfo->lpsmSock->Send((char *)&pkt, pkt.size, TRUE);

			if(lpPlayInfo->Xigncode_tempdata.m_ceComplete == TRUE && scan_Type == Z_SCAN_TYPE_ANTI_CHEAT_ENGINE)
			{
				lpPlayInfo->CE_code_count++;
				break;
			}
		}

		if(scan_Type == Z_SCAN_TYPE_ANTI_CHEAT_ENGINE)
		{
			lpPlayInfo->Xigncode_tempdata.m_ceComplete = TRUE;
		}

		lpPlayInfo->Xigncode_tempdata.dwWaitTime_NC = lpPlayInfo->Xigncode_tempdata.dwWaitTime_NC + (1000 * 60);

		if(lpPlayInfo->Xigncode_tempdata.m_type == 2)
		{
			lpPlayInfo->Xigncode_tempdata.m_type = 1;
		}
		else if(lpPlayInfo->Xigncode_tempdata.m_type == 1 && lpPlayInfo->CE_code_count == 10)
		{
			lpPlayInfo->CE_code_count = 0;
			lpPlayInfo->Xigncode_tempdata.m_type = 2;
		}

	}

	return TRUE;
}

#endif 
