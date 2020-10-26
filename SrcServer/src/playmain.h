#pragma once

#include "smLib3d\smType.h"


class smPAT3D;
class smCHAR;
class smSTAGE3D;
class scITEM;
class smOBJ3D;
struct smTRANS_COMMAND;

#define OTHER_PLAYER_MAX		1024
#define OTHER_PLAYER_MASK		1023


#define	SHADOW_PAT_MAX		4


#define	ICE_FOOT_PAT_MAX		2
extern	smPAT3D *PatIceFoot[ICE_FOOT_PAT_MAX];



#define	GAME_WORLDTIME_MIN		800



#define GAME_HOUR_DAY			4
#define GAME_HOUR_GLOW			22
#define GAME_HOUR_DARKNESS		23
#define GAME_HOUR_NIGHT			24


extern DWORD	dwBattleTime;
extern DWORD	dwBattleQuitTime;
extern DWORD	dwCloseBoxTime;

extern int GameMode;

extern int	PkMode;
extern int	DispApp_SkillPoint;

extern int		Moving_DblClick;
extern POINT3D	MousePos_DblClick;

extern POINT3D	TracePos_DblClick;
extern int TraceMode_DblClick;


extern	int	ActionGameMode;

extern smPAT3D  *PatShadow[SHADOW_PAT_MAX];
extern smPAT3D  *PatArrow;
extern smPAT3D	*PatEffectShield;
extern smPAT3D	*PatSparkShield;
extern smPAT3D	*PatDivineShield;
extern smPAT3D	*PatGodlyShield;
extern smPAT3D	*PatCrown;


extern smCHAR *lpCurPlayer;
extern smCHAR chrOtherPlayer[OTHER_PLAYER_MAX];
extern char PlayerName[64];

extern	int	RecordFailCount;



extern smSTAGE3D *smStage;
extern int PlayCounter;
extern smSTAGE3D *smGameStage[2];
extern smSTAGE3D *smGameStageWall[2];
extern DWORD	dwPlayTime;
extern DWORD	dwMemError;

extern char szGameStageName[2][64];

extern int	BackColor_R;
extern int	BackColor_G;
extern int	BackColor_B;

extern int	BackColor_mR;
extern int	BackColor_mG;
extern int	BackColor_mB;

extern int	DarkLevel_Fix;

extern int DarkLevel;
extern int DarkLightRange;
extern DWORD	dwGameWorldTime;
extern DWORD	dwGameHour;
extern DWORD	dwGameMin;
extern DWORD	dwGameTimeOffset;

extern DWORD	UseEtherCoreCode;


extern int MatBlood[2];

extern int MatEnergyBox[2];

extern	int WeatherMode;

extern int		MsTraceCount;
extern int		MsTraceMode;

extern	RECT	MsSelRect;
extern	POINT	MsSelPos;

extern	int		SelMouseButton;

extern  int		AttCancel;
extern  int		AttAutoCont;


extern  smCHAR	*lpCharSelPlayer;
extern	smCHAR	*lpCharMsTrace;

extern	scITEM	*lpSelItem;
extern	scITEM	*lpMsTraceItem;

extern	int		RestartPlayCount;



extern int AdminCharDisable;

#define DISP_ITEM_MAX	1024
extern scITEM	scItems[DISP_ITEM_MAX];



extern int	Record_BlockCount;
extern int	Record_DefenceCount;
extern int	Record_RecvDamageCount;
extern int  Record_TotalRecvDamageCount;

extern DWORD SkillFalconPoint;



extern	DWORD	AutoMouse_LastCheckTime;
extern	DWORD	AutoMouse_StartCheckTime;
extern	int		AutoMouse_WM_Count;
extern	int 	AutoMouse_Distance;
extern	int		AutoMouse_Attack_Count;



int TraceAttackPlay();

int CancelAttack();

int GetMouseSelAngle();

int GetCharAngle(smCHAR *lpChar1, smCHAR *lpChar2);

int SetChrArmor(smCHAR *lpChar, int ItemNum);


void InitStageLoader();

void InitStage();
void CloseStage();
int DisplayStage(int x, int y, int z, int angX, int angY, int angZ);



int InitPat3D();
int ClosePat3D();
int PlayObj3D(smOBJ3D *obj3d, int x, int y, int z, int ax, int ay, int az);
int PlayPat3D();
int DrawPat3D_Alpha();
int DrawPat3D(int x, int y, int z, int ax, int ay, int az);
int DrawPat2D(int x, int y, int z, int ax, int ay, int az);


int DrawPatShadow(int x, int y, int z, int ax, int ay, int az);

int InitBackGround();
int CloseBackGround();
int DrawBG(int x, int y, int z, int ax, int ay, int az);

int ChangeBG(int BgNum);
int BGMain();


extern CRITICAL_SECTION	cDrawSection;

extern int SkipNextField;

extern int AdminCharMode;

extern char *NpcSelectedName;


int GetPartyTradeButtonPos(int x, int y);

int DisplayPartyTradeButton();


int	DamageExp(smCHAR *lpChar, int AttackDamage);


smSTAGE3D *LoadStage2(char *szStageFile);

smSTAGE3D *LoadStage(char *szStageFile);



extern POINT3D TraceCameraPosi;
extern POINT3D TraceTargetPosi;
extern HFONT	hFont;
extern int QuitSave;

extern int	DebugPlayer;

extern int DispEachMode;
extern int		EachTradeButton;
extern int		EachTradeButtonMode;
extern RECT		RectTradeButton;
extern smCHAR	chrEachPlayer;
extern smCHAR	*chrEachMaster;

extern char szExitInfo_URL[128];

int SetIME_Mode(BOOL mode);

int DrawEachPlayer(float fx, float fy, int SizeMode);
int EachPlayerMain();
int CloseEachPlayer();
int OpenEachPlayer(smCHAR *lpChar);

int GetPlayMouseAngle();
int SetMousePlay(int flag);


void SetPlayerBodyPattern(char *szBodyFile);
void SetPlayerPattern(char *szFile);


int CheckCode_2Byte(char *Str);

int SetPartyPosion(smTRANS_COMMAND *lpTransCommand);



int	StartQuest_Code(DWORD wCode);

int EndQuest_Code(DWORD wCode);

int SetQuestBoard();


int Record_ClinetLogFile(char *szMessage);

extern int DisplayDebug;
extern int LastAttackDamage;
extern int ImeChatLen;
extern	POINT	ImePositon;


#define	sinITEM_WEAPON	0x01000000
#define	sinITEM_DEFENCE	0x02000000
#define	sinITEM_MASK1	0xFF000000
#define	sinITEM_MASK2	0xFFFF0000
#define	sinITEM_MASK3	0x0000FFFF


int QuitGame();
int SetIME_Mode(BOOL mode);


extern int QuitSave;
extern DWORD	dwLastMouseMoveTime;
extern DWORD	dwLastCharMoveTime;

extern int	PlayTimerMax;

extern DWORD dwM_BlurTime;



int WingWarpGate_Field(int dwFieldCode);



extern int ParkPlayMode;
extern int ParkPlaying;

int Init_ParkPlayer();
int Stop_ParkPlayer();
int Play_ParkPlayer(char *szPath, int x, int y, int w, int h, int PlayMode);

