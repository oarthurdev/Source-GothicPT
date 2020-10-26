#ifndef	_SMPACKET_HEADER

#define _SMPACKET_HEADER

#include "sinbaram\\sinitem.h"
#include <atltime.h>
#include "smwsock.h"
#include <stdint.h>
#include <map>
#include <unordered_map>
#include <string>
#include "Log\Log.h"
#include "global_def.h"

int GetBattleLevel(int Exp);
int GetExpNextLevel(int Level);
extern int VIPExpAdd;
extern int VIPHPAdd;
extern int VIPMPAdd;
extern int VIPSTMAdd;
extern int VIPATKAdd;
extern int KillDelay;
extern int VIPDROPAdd;
extern int QCountKill;
struct BATTLE_ARENA_POINT {
	int size;
	int code;
	char NPlayer1[32];
	char NPlayer2[32];
	char NPlayer3[32];
	int  BPlayer1;
	int  BPlayer2;
	int  BPlayer3;
};

enum OpCode
{
	OPCODE_NULL,
	OPCODE_OPENLIVE,
	OPCODE_SYSTEM,
	OPCODE_CONNECTED,
	OPCODE_RECORDDATA,
	OPCODE_GETRECORDDATA,
	OPCODE_FAILRECORDDATA,
	OPCODE_RECORDRESULT,
	OPCODE_ID_GETUSERINFO,
	OPCODE_ID_SETUSERINFO,
	OPCODE_DELRECORDDATA,
	OPCODE_INSRECORDDATA,
	OPCODE_ISRECORDDATA,
	OPCODE_VERSION,
	OPCODE_CHECK_NETSTATE,
	OPCODE_AUTH_ADMIN_MODE,
	OPCODE_SET_OBJSERIAL,
	OPCODE_CHECK_NETSTATE2,
	OPCODE_CHECK_NETSTATE3,
	OPCODE_CHECK_NETSTATE4,
	OPCODE_CHECK_NETSTATE5,
	OPCODE_IPLIST,
	OPCODE_CHATMESSAGE,
	OPCODE_POSITION,
	OPCODE_PLAYLIST,
	OPCODE_CONTINUEDATA,
	OPCODE_WHISPERMESSAGE,
	OPCODE_COUPLERING,
	OPCODE_PLAYDATA1,
	OPCODE_PLAYDATA2,
	OPCODE_PLAYDATA3,
	OPCODE_TRANSPLAYDATA,
	OPCODE_PLAYDATAGROUP,
	OPCODE_PLAY_COMMAND,
	OPCODE_PARTY_CHATMSG,
	OPCODE_ADDEXP_PARTY,
	OPCODE_ATTACKDATA,
	OPCODE_ADDEXP,
	OPCODE_PLAYERINFO2,
	OPCODE_SET_BLACKLIST,
	OPCODE_SET_ITEMCOPYLIST,
	OPCODE_SKIL_ATTACKDATA,
	OPCODE_FINDCRACK,
	OPCODE_MODULE_WARNIG,
	OPCODE_UPDATE_CINFO,
	OPCODE_OPENMONSTER,
	OPCODE_WARPFIELD,
	OPCODE_TRADEITEMS,
	OPCODE_TRADE_REQUST,
	OPCODE_TRADE_ITEMKEY,
	OPCODE_TRADE_READYITEM,
	OPCODE_SKILL_MENU,
	OPCODE_FINDCRACK2,
	OPCODE_WAREHOUSE,
	OPCODE_OPEN_WAREHOUSE,
	OPCODE_OPEN_MIXITEM,
	OPCODE_OPEN_COLLECT,
	OPCODE_COLLECTMONEY,
	OPCODE_PLAYERINFO_Q,
	OPCODE_OPEN_AGING,
	OPCODE_SKIL_ATTACKUSER,
	OPCODE_OPEN_EVENTGIFT,
	OPCODE_PLAYERINFO,
	OPCODE_GETPLAYERINFO,
	OPCODE_FAILCONNECT,
	OPCODE_PLAYITEM,
	OPCODE_DELITEM,
	OPCODE_PUTITEM,
	OPCODE_THROWITEM,
	OPCODE_SHOP_ITEMLIST,
	OPCODE_SAVETHROWITEM,
	OPCODE_SAVETHROWMONEY,
	OPCODE_SAVETHROWITEM2,
	OPCODE_SAVETHROWITEMS,
	OPCODE_PLAYERKILLING,
	OPCODE_GETITEM,
	OPCODE_USEITEM_CODE,
	OPCODE_COMMAND_USER,
	OPCODE_WING_NPC,
	OPCODE_PAYMENT_MONEY,
	OPCODE_MEDIA_NPC,
	OPCODE_ADD_STARTPOSI,
	OPCODE_DEL_STARTPOSI,
	OPCODE_ADD_NPC,
	OPCODE_DEL_NPC,
	OPCODE_ADMIN_COPYCHAR,
	OPCODE_PARTY_UPDATE,
	OPCODE_PARTY_REQUEST,
	OPCODE_PARTY_JOIN,
	OPCODE_PARTY_PLAYUPDATE,
	OPCODE_PARTY_RELEASE,
	OPCODE_PARTY_COMMAND,
	OPCODE_OPEN_MIXTURE_RESET,
	OPCODE_PCBANG_PET,
	OPCODE_PHENIX_PET,
	OPCODE_HELP_PET,
	OPCODE_SERVER_INFO,
	OPCODE_PARTY_POTION,
	OPCODE_HEALING,
	OPCODE_HOLYMIND,
	OPCODE_WISP,
	OPCODE_GRAND_HEALING,
	OPCODE_VAMPRIC_CUSPID,
	OPCODE_VAMPRIC_CUSPID_EX,
	OPCODE_MANA_RECHARGING,
	OPCODE_RECORD_TRADE,
	OPCODE_NETWORK_QUALITY,
	OPCODE_PROCESSINFO,
	OPCODE_CLOSECLIENT,
	OPCODE_CHECKIP,
	OPCODE_SAVECLIENT,
	OPCODE_EFFECT_ITEM,
	OPCODE_EFFECT_WEAPON,
	OPCODE_EFFECT_STUN,
	OPCODE_EFFECT_CURSE,
	OPCODE_EFFECT_ICE,
	OPCODE_EFFECT_CURSELAZY,
	OPCODE_EFFECT_WISP,
	OPCODE_EFFECT_POISION,
	OPCODE_EFFECT_VANISH,
	OPCODE_EFFECT_PERSHOP,
	OPCODE_EFFECT_LOWPET,
	OPCODE_EFFECT_CLANMGR,
	OPCODE_EFFECT_FORCEORB,
	OPCODE_EFFECT_CURSE_QUEST,
	OPCODE_EFFECT_BLESS_SCORE,
	OPCODE_EFFECT_KEEPSKILL,
	OPCODE_CONT_OBJSERIAL,
	OPCODE_MESSAGEBOX,
	OPCODE_FUNCERROR,
	OPCODE_FUNCTION_MEM2,
	OPCODE_SET_BLACKLIST2,
	OPCODE_SET_BLACKLIST3,
	OPCODE_BAD_PLAYER,
	OPCODE_FIX_ATTACK,
	OPCODE_DEAD_PLAYER,
	OPCODE_CLIENT_ERROR,
	OPCODE_INVEN_ERR_ITEM,
	OPCODE_INVEN_ERR_MONEY,
	OPCODE_INVEN_POSITION,
	OPCODE_INVEN_POSITION2,
	OPCODE_OPEN_CLANMENU,
	OPCODE_OPEN_STARPOINT,
	OPCODE_STARPOINT,
	OPCODE_OPEN_GIVEMONEY,
	OPCODE_GIVEMONEY,
	OPCODE_CLANMONEY,
	OPCODE_ITEM_EXPRESS,
	OPCODE_OPEN_MYSHOP,
	OPCODE_CALL_MYSHOP,
	OPCODE_MYSHOP_ITEM,
	OPCODE_MYSHOP_MESSAGE,
	OPCODE_MYSHOP_TRADE,
	OPCODE_EFFECT_PCBANGPET,
	OPCODE_CHECK_NETSTATE20,
	OPCODE_CHECK_EXPMONEY,
	OPCODE_CHECK_EXPDATA,
	OPCODE_FORCEORB_DATA,
	OPCODE_PRIMEITEM_DATA,
	OPCODE_PRIMEITEM_DATA2,
	OPCODE_PRIMEITEM_DATA3,
	OPCODE_PRIMEITEM_DATA4,
	OPCODE_BOOSTER_DATA,
	OPCODE_AGING_DATA,
	OPCODE_SKILLDELAY_DATA,
	OPCODE_SEND_DATASERVER,
	OPCODE_SEND_GAMESERVER,
	OPCODE_SEND_AREASERVER,
	OPCODE_SEND_AGAME_SERVER,
	OPCODE_SEND_AGAME_PRIMEITEM_DATA2,
	OPCODE_SEND_AGAME_PRIMEITEM_DATA3,
	OPCODE_SEND_AGAME_PRIMEITEM_DATA4,
	OPCODE_CRAFTITEM,
	OPCODE_AGINGITEM,
	OPCODE_AGING_UPGRADE,
	OPCODE_MAKE_LINKCORE,
	OPCODE_USE_LINKCORE,
	OPCODE_WINGITEM,
	OPCODE_SHOPTITEM,
	OPCODE_SHOP_SELLITEM,
	OPCODE_ITEM_FORCEORB,
	OPCODE_QUEST_COMMAND,
	OPCODE_EXITINFO_URL,
	OPCODE_CHECKITEM,
	OPCODE_ERRORITEM,
	OPCODE_CLEARPOTION,
#ifdef _CHECK_MESH
	OPCODE_CHECK_ITEMMESH,
#endif
	OPCODE_CLIENT_FUNCPOS,
	OPCODE_GETCLIENT_FUNCPOS,
	OPCODE_FUNCTION_MEM,
	OPCODE_FUNCTON_RESULT,
	OPCODE_PROCESS_TIMEMAX,
	OPCODE_REC_DAMAGEDATA,
	OPCODE_SOD_RESULT,
	OPCODE_SOD_RESULT2,
	OPCODE_PARTY_SKILL,
	OPCODE_CANCEL_SKILL,
	OPCODE_PROCESS_SKILL,
	OPCODE_PROCESS_SKILL2,
	OPCODE_PROCESS_CLAN_SKILL,
	OPCODE_UPDATEL_SKILL,
	OPCODE_SUCCESS_EVATION,
	OPCODE_SUCCESS_DEFENSE,
	OPCODE_RESISTANCE,
	OPCODE_PUBLIC_POLLING,
	OPCODE_NOTICE_BOX,
	OPCODE_HACKTRAP,
	OPCODE_VIRTURAL_POTION,
	OPCODE_CLAN_SERVICE,
	OPCODE_CLAN_UPDATE,
	OPCODE_QUEST_MESSAGE,
	OPCODE_DEAD_USER,
	OPCODE_YAHOO_MOTION,
	OPCODE_CHANGE_EVENT,
	OPCODE_CLIENTINFO,
	OPCODE_WARNING_BLINK_ATT,
	OPCODE_ATTACK_DAMAGE,
	OPCODE_RANGE_DAMAGE,
	OPCODE_ATTACK_RESULT,
	OPCODE_DISP_DAMAGE,
	OPCODE_ATTACKDATA2,
	OPCODE_LIMIT_DAMAGE,
	OPCODE_WARNING_CLIENT,
	OPCODE_WARNING_SKILL,
	OPCODE_COMIC_SKIN,
	OPCODE_REC_ADMIN_COMMAND,
	OPCODE_SOD_INFOMATION,
	OPCODE_BLESSCASTLE_INFO,
	OPCODE_BLESSCASTLE_TAX,
	OPCODE_ATTACK_SLASH_LIST,
	OPCODE_UPDATE_SERVER_PARAM,
	OPCODE_USER_ID,
	OPCODE_DAMAGE_ENCODE_MEM,
	OPCODE_DAMAGE_ENCODE_MEM2,
	OPCODE_PACKET_DYNFUNC,
	OPCODE_AREA_SERVER_MAP,
	OPCODE_OPEN_SMELTING,
	OPCODE_SMELTINGITEM,
	OPCODE_OPEN_MANUFACTURE,
	OPCODE_MANUFACTURE,
	OPCODE_MANUFACTURE_WEIGHT_PRICE,
	OPCODE_GIFTBOX_MONEY,
	OPCODE_PREMIUMITEM_INIT,
	OPCODE_MIXTURE_RESET_ITEM,
	OPCODE_EVENT_GAME,
	OPCODE_ITEMDOC,
	CHANGE_WINDOW_TITLE,
	CHECK_SOD_CROWN,
	BATTLE_POINTS,
	UPDATE_BATTLE_POINTS,
	INIT_CHEAT_PROTECTION,
	FIND_CHEAT,
	SEARCH_GAME_CHEAT,
	DELETE_ITEM_PREMIUM,
	UPDATE_ITEM_PREMIUM,
	SET_ITEM_PREMIUM,
	EFFECT_CURSE_PVP,
	SEND_ALERT_PVP,
	OPCODE_UPDATE_PREMIUMITEM_TIME,
	OPCODE_SHOWITEMINFO_PERF,
	PLAYER_GM,
	EFFECT_GM,
	EFFECT_BETA,
	PLAYER_TOP_LEVEL,
	EFFECT_TOP_LEVEL,
	VALE_LEVEL,
	BOSS_TIME,
	PLAYER_BETA,
	PLAYER_GLADIADOR,
	BLESS_CROWN,
    OPCODE_UPDATE_PARTYMODE,
	OPCODE_SPOILER_INFO,
	OPCODE_QUEST_INFO,
	OPCODE_START_QUEST,
	OPCODE_CANCEL_QUEST,
	OPCODE_GET_REWARD,
	OPCODE_NEW_ADDEXP,
	OPCODE_LUCKYBOX,
	OPCODE_EXPLVL1,
	OPCODE_BUFFS,
	OPCODE_ISBETA
};

#define smTRANSCODE_CURRENT_MANA  0x70000024
#define smTRANSCODE_PARTY_MODE  0x70000025

#define smTRANSCODE_OPEN_BATTLE_ARENA       0x59000000
#define smTRANSCODE_ENTER_BATTLE_ARENA      0x59000001
#define smTRANSCODE_POINT_BATTLE_ARENA      0x59000002
#define smTRANSCODE_CLOSE_BATTLE_ARENA      0x59000003
#define smTRANSCODE_CLOSE_BOSS_MUNDO        0x59000009
#define smTRANSCODE_CONG_BATTLE_ARENA       0x59000004
#define smTRANSCODE_YOU_ARE_GLADIATOR       0x59000005
#define smTRANSCODE_YOU_NOT_ARE_GLADIATOR   0x59000006
#define smTRANSCODE_IT_IS_GLADIATOR         0x59000007
#define smTRANSCODE_TIME_BATTLE_ARENA       0x59000008
#define smTRANSCODE_OPEN_PROGRESS_DIARY    0x69000000
#define smTRANSCODE_UPDATE_DIARY           0x69000001
#define smTRANSCODE_REQUEST_DIARY          0x69000002
#define smTRANSCODE_UPDATE_BATTLE_LEVEL    0x69000003
#define smTRANSCODE_ENTER_BOSS_MUNDO	   0x69000004
#define smTRANSCODE_NOT_GLADI			   0x69000005
#define smTRANSCODE_GLADI				   0x69000006
#define smTRANSCODE_LOST				   0x69000007
#define smTRANSCODE_RESETBP				   0x69000008

#define	smTRANSCODE_MECH_INFO		0x48480000
#define	smTRANSCODE_FIGHTER_INFO	0x48480001
#define	smTRANSCODE_PIKE_INFO		0x48480002
#define	smTRANSCODE_ARCHER_INFO		0x48480003
#define	smTRANSCODE_KINA_INFO		0x48480004
#define	smTRANSCODE_ATA_INFO		0x48480005
#define	smTRANSCODE_SACER_INFO		0x48480006
#define	smTRANSCODE_MAGE_INFO		0x48480007
#define smTRANSCODE_ASSASSIN_INFO   0x48470008
#define smTRANSCODE_SHAMAN_INFO     0x48470009

struct BUFF_KILL
{
	int flag;
	int x;
	int y;
	int alpha;
	int image;
};

struct PACKET_CROWN
{
	int size;
	int code;
	DWORD Silver;
	DWORD Bronze;
};

struct PACKET_BUFFS
{
	int size;
	int code;
	int SetBoss1Bonus1;
	int SetBoss1Bonus2;
	int SetBoss2Bonus1;
	int SetBoss2Bonus2;
};


struct sNEW_QUEST_INFO
{
	int QuestID;
	int QuestKind;
	char QuestName[128];
	bool QuestActive;
};

struct smTRANS_QUEST_FULL
{
	int size, code;

	int QuestID;
	int QuestKind;
	char QuestName[128];
	char QuestTitle[128];
	int LevelMin, LevelMax;
	int ClanLevelMin, ClanLevelMax;
	int PartyFlag;
	char QuestDesc[500];
	int QuestType;

	int MonsterCount;
	char MonsterNames[4][32];
	int MonsterCounts[4];
	int MonsterKilled[4];
	int MonsterMaps[4];

	int RewardCount;
	char RewardNames[4][32];
	int RewardCounts[4];
	int RewardGold;
	INT64 RewardExp;
	int RewardCoin;
	int RewardTCoin;
	INT64 RewardClanExp;

	SYSTEMTIME EndTime;
};

struct smTRANS_QUEST_INFO
{
	int size, code;

	int SpoilerNum;
	int QuestCount;
	sNEW_QUEST_INFO QuestInfo[58];
};

struct smTRANS_COMMAND_QWORD
{
	int size, code;

	INT64 LParam;
	INT64 WParam;
	INT64 SParam;
	INT64 EParam;
};

#define PACKET_KILL                 0x49470004

#define OPCODE_ENCODE_PACKET 0x80010000
#define OPCODE_ENCODE_PACKET2 0x90010000





#define smUPDATE_PARAM_LOWUSER_PRESENT	0x100
#define	rsHARDCORE_EVENT_FLAG     0x100
#define smCODE_SOD_EFFECT           100 
#define smCODE_EVENT_STATE_INIT       100


#define TRANS_BUFF_SIZE 4096

#define	smCHAR_STATE_NPC 0
#define	smCHAR_STATE_ENEMY 1
#define	smCHAR_STATE_USER 0x80

#define	smCHAR_MONSTER_NATURAL	0x80
#define	smCHAR_MONSTER_GOOD 0x81
#define	smCHAR_MONSTER_EVIL 0x82

#define	smCHAR_MONSTER_NORMAL	0x00
#define	smCHAR_MONSTER_UNDEAD	0x90
#define	smCHAR_MONSTER_MUTANT	0x91
#define	smCHAR_MONSTER_DEMON	0x92
#define	smCHAR_MONSTER_MECHANIC	0x93

#define	smCHAR_MONSTER_USER 0xA0

#define	smCOMMNAD_USER_WARP 0x100
#define	smCOMMNAD_USER_AGINGUP	0x110
#define	smCOMMNAD_USER_HOLY_INCANTATION	0x120
#define	smCOMMNAD_USER_RESURRECTION	0x130
#define	smCOMMNAD_USER_FORCEORB	0x140
#define	smCOMMNAD_USER_VALENTO	0x150
#define	smCOMMNAD_USER_FIREFLOWER	0x160

#define	smCOMMAND_PLAY_BABEL 0x200
#define	smCOMMAND_PLAY_BELSS_CASTLE	0x210
#define	smCOMMAND_PLAY_PK_FIELD 0x220
#define	smCOMMAND_PLAY_KELVEZU 0x230





#define ACCOUNT_SIZE 21
#define PASSWORD_SIZE 32
#define NAME_SIZE 32



class	smCHAR;

class	rsRECORD_DBASE;

#define	FALLITEM_MAX 200
#define	FALLITEM2_MAX 3

struct _FALLITEM
{
	DWORD	dwItemCode;
	int Percentage;
	int	sPrice[2];
};

#define	NPC_MESSAGE_MAX 20


struct smCHAR_MONSTER_INFO
{
	char	szName[NAME_SIZE];

	short	SkillDamage[2];
	int SkillRange;
	int SkillRating;
	int SkillDistance;
	RECT	SkillRangeRect;
	int SkillCurse;

	int AttackPattern;
	int ActiveHour;
	int IQ;
	int Nature;
	int Undead;
	int GenerateGroup[2];
	int GetExp;
	int SpAttackPercetage;
	int MoveRange;
	int DamageStunPers;

	int PotionCount;
	int PotionPercent;

	int AllSeeItem;
	int FallItemCount;
	int FallItemPerMax;
	int FallItemMax;
	int FallItemPlusCount;

	int ClassCode;

	int UseEventModel;

	int Real_Sight;

	_FALLITEM	FallItems[FALLITEM_MAX];
	_FALLITEM	FallItems_Plus[FALLITEM2_MAX];



	int SellAttackItemCount;
	void	*SellAttackItem[32];
	int SellDefenceItemCount;
	void	*SellDefenceItem[32];
	int SellEtcItemCount;
	void	*SellEtcItem[32];

	int SkillMaster;
	int SkillChangeJob;
	int WareHouseMaster;
	int ItemMix;
	int ItemAging;
	int CollectMoney;
	int EventGift;
	int Smelting;
	int Manufacture;
	int MixtureReset;
	int ItemShop;
	int ItemTShop;
	int BattleArena;
	int QuestDiary;
	int RestaureItem;

#ifdef _LANGUAGE_VEITNAM
	int WowEvent;
#endif

	int EventCode;
	int EventInfo;
	DWORD	dwEvnetItem;
	int EventNPC;
	int ClanNPC;
	int GiftExpress;
	int WingQuestNpc;
	int StarPointNpc;
	int GiveMoneyNpc;
	int TelePortNpc;
	int BlessCastleNPC;
	int PollingNpc;

	char	*szMediaPlayNPC_Title;
	char	*szMediaPlayNPC_Path;

	int QuestCode;
	int QuestParam;

	short	OpenCount[2];

	DWORD	dwAutoCharCode;

	char	*lpNpcMessage[NPC_MESSAGE_MAX];
	int NpcMsgCount;

};



struct smCHAR_INFO
{
	char	szName[NAME_SIZE];
	char	szModelName[64];
	char	szModelName2[60];
	DWORD	ModelNameCode2;

	DWORD	dwObjectSerial;


	int ClassClan;
	int State;
	int SizeLevel;
	DWORD	dwCharSoundCode;


	DWORD JOB_CODE;
	int   Level;
	int   Strength;
	int   Spirit;
	int   Talent;
	int   Dexterity;
	int   Health;


	int	  Accuracy;
	int   Attack_Rating;
	int   Attack_Damage[2];
	int	  Attack_Speed;
	int	  Shooting_Range;
	int	  Critical_Hit;

	int   Defence;
	int   Chance_Block;
	int   Absorption;

	int   Move_Speed;
	int   Sight;
	short Weight[2];


	short	Resistance[8];
	short	Attack_Resistance[8];


	short   Life[2];
	short   Mana[2];
	short   Stamina[2];

	float	Life_Regen;
	float	Mana_Regen;
	float	Stamina_Regen;

	int Exp;
	int Next_Exp;

	int Money;

	smCHAR_MONSTER_INFO	*lpMonInfo;

	DWORD	Brood;

	int StatePoint;
	BYTE	bUpdateInfo[4];
	short	ArrowPosi[2];
	int Potion_Space;

	int     LifeFunction;
	int     ManaFunction;
	int     StaminaFunction;
	short   DamageFunction[2];

	DWORD	RefomCode;

	DWORD	ChangeJob;
	DWORD	JobBitMask;

	WORD	wPlayerKilling[2];
	WORD	wPlayClass[2];

	int Exp_High;
	DWORD	dwEventTime_T;
	short	sEventParam[2];

	short	sPresentItem[2];


	short GravityScroolCheck[2];

	DWORD	dwTemp[11];

	DWORD	dwLoginServerIP;
	DWORD	dwLoginServerSafeKey;

	WORD	wVersion[2];



};


#define	smCHAR_INFO_QUICK_SIZE 192
#define	smCHAR_INFO_QUICK_SIZE2 352

#define	THROW_ITEM_INFO_MAX 64
#define	THROW_ITEM_INFO_MASK	63
#define	INVEN_ITEM_INFO_MAX 300


struct	sTHROW_ITEM_INFO
{

	DWORD	dwCode;
	DWORD	dwKey;
	DWORD	dwSum;
};



struct rsPLAYPOS
{
	DWORD	Area;
	int x, y, z;

	rsPLAYPOS()
	{
		Area = 0;
		x = 0;
		y = 0;
		z = 0;
	}
};


struct TRANS_PLAYPOS
{
	int size, code;

	rsPLAYPOS	rsPlayPos;
	short Hp[2];

	TRANS_PLAYPOS()
	{
		size = 0;
		code = 0;
		Hp[0] = 0;
		Hp[1] = 0;
	}
};



struct ChangeTitle
{
	unsigned int size;
	unsigned short opcode;
	char buffer[255];

	ChangeTitle()
	{
		size = 0;
		opcode = 0;
		memset(buffer, 0, sizeof(buffer));
	}
};

struct TRANS_ATTACKDATA
{
	int size, code;

	DWORD	dwDestObjectSerial;
	DWORD	dwTarObjectSerial;

	int x, y, z;
	int AttackState;
	int AttackSize;
	int Power;
	DWORD	dwChkSum;

	short	sRating[2];
	DWORD	dwDamageChkSum;
};

struct TRANS_ATTACKDATA2
{
	int size, code;

	DWORD	dwChkSum;

	DWORD	dwDestObjectSerial;
	DWORD	dwTarObjectSerial;

	int x, y, z;
	int AttackState;
	int AttackSize;
	short	Power[2];
	short	Power2[2];
	short	Critical[2];
	int SkillCode;
	DWORD	dwTime;
	int AttackCount;
	short	MotionCount[2];
	DWORD	dwWeaponCode;
	short	Area[2];
	int Temp[4];
};



#define SKIL_ATTACK_CHAR_MAX 42

struct TRANS_SKIL_ATTACKDATA
{
	int size, code;

	DWORD	dwDestObjectSerial;

	int x, y, z;
	int AttackState;
	int AttackSize;
	int Power;

	DWORD	dwChkSum;

	int	TargetCount;
	DWORD	dwTarObjectSerial[SKIL_ATTACK_CHAR_MAX];
};

struct TRANS_SKIL_ATTACKDATA2
{
	int size, code;

	DWORD	dwDestObjectSerial;

	DWORD	dwChkSum;

	int x, y, z;
	int AttackState;
	int AttackSize;
	short	Power[2];
	short	Power2[2];
	short	Critical[2];
	int SkillCode;
	DWORD	dwTime;
	int AttackCount;
	short	MotionCount[2];
	DWORD	dwWeaponCode;
	short	Area[2];
	int Temp[4];

	DWORD	dwMainTargetObject;

	int	TargetCount;
	DWORD	dwTarObjectSerial[SKIL_ATTACK_CHAR_MAX];
};






struct TRANS_AREAINFO_HEADER
{
	int size;
	int code;
	DWORD	dwIP;
	int Stats;
	int TransListCnt;
};

struct TRANS_IPLIST
{
	DWORD	dwIP;
	rsPLAYPOS	Pos;
};


#define	POST_ITEM_MAX 500

struct _POST_BOX_ITEM
{
	int Flag;
	char	szCharName[32];
	char	szItemCode[32];
	char	szSpeJob[32];
	char	szDoc[128];
	char	szFormCode[64];
	char	szPassCode[16];

	DWORD	dwItemCode;
	DWORD	dwJobCode;
	DWORD	dwFormCode;
	DWORD	dwPassCode;
	DWORD	dwParam[4];
};

struct	rsPOST_BOX_ITEM
{
	DWORD	dwHead;
	int ItemCounter;

	_POST_BOX_ITEM	PostItem[POST_ITEM_MAX];
};

struct	TRANS_POST_ITEM
{
	int size, code;

	char	szItemName[32];
	char	szDoc[128];
	DWORD	dwItemCode;
	DWORD	dwItemJobCode;
	DWORD	dwParam[4];

	DWORD	dwItemFlag;
	int Weight;
};






#define	srPLAYBUFF_MAX 4
#define	srPLAYBUFF_MASK 3

#define	PARTY_PLAYER_MAX 6


#define	srRECORD_DEFAULT_SIZE	16384

#define	srRECORD_MEMORY_SIZE	24576


#define SKILL_POINT_COLUM_MAX	16

struct	TRANS_PARTY_PLAYINFO;

struct	npGAME_GUARD_AUTH_INFO
{
	DWORD	Auth_Value;
	DWORD	Auth_Time;
	DWORD	Auth_Count;
	DWORD	Auth_Retry;
};


struct	sMYSHOP_SELL_INFO
{
	DWORD	dwCode;
	DWORD	dwHead;
	DWORD	dwChkSum;
	int Price;
};

#define	MYSHOP_LIST_MAX 32
#define	MYSHOP_LIST_MASK	31


struct	sCASTLE_MASTER
{
	int Flag;
	DWORD	dwCheckTime;
	int SelectSkill;
};


#define	rsDATA_ERROR_WAREHOUSE 1



struct smTRANS_COMMAND
{
	int	size;
	int code;

	int LParam;
	int WParam;
	int SParam;
	int EParam;

	smTRANS_COMMAND()
	{
		size = 0;
		code = 0;
		LParam = 0;
		WParam = 0;
		SParam = 0;
		EParam = 0;
	}
};


#define PACKET_SIZE 512


//typedef struct _WSABUF
//{
//	u_long      len;
//	char FAR *  buf;
//} WSABUF, FAR * LPWSABUF;

enum class AccountTypes : uint8_t
{
	SEC_PLAYER = 0,
	SEC_VIP,
	SEC_MODERATOR,
	SEC_GAMEMASTER,
	SEC_ADMINISTRATOR,
	SEC_CONSOLE
};

static std::map<AccountTypes, char*> AccountTypesMap =
{
	{ AccountTypes::SEC_PLAYER, "Usuário" },
	{ AccountTypes::SEC_VIP, "VIP" },
	{ AccountTypes::SEC_MODERATOR, "Moderador" },
	{ AccountTypes::SEC_GAMEMASTER, "Game Master" },
	{ AccountTypes::SEC_ADMINISTRATOR, "Administrador" },
	{ AccountTypes::SEC_CONSOLE, "Super Usuário" },
};



class rsPLAYINFO
{
private:
	int accountId;
	char account[ACCOUNT_SIZE];
	char password[PASSWORD_SIZE];
	char name[NAME_SIZE];


public:
	char szServerID[32];
	DWORD dwCode_ID;
	DWORD dwCode_Name;
	int AdminOperMode;

	DWORD dwDataError;

	int TransInfoFlag;
	int ChatBuffCnt;

	int SystemLine;

	int CharLoadingCount;

	rsPLAYPOS Position;
	rsPLAYINFO **lpAreaPlayInfo;

	int SendListCnt;

	DWORD dwDecPacketCode;
	BYTE bPacketXor[2];
	DWORD dwDecPacketTime;
	DWORD dwDecPacketTime2;

	smCHAR_INFO smCharInfo;

	int CharLevelMax;
	DWORD dwNoticeCount;

	char srPlayBuff[srPLAYBUFF_MAX + 1][TRANS_BUFF_SIZE];
	int srPlayBuffSize[srPLAYBUFF_MAX + 1];

	int PlayBuffSleep;

	sTHROW_ITEM_INFO	ThrowItemInfo[THROW_ITEM_INFO_MAX];

	sTHROW_ITEM_INFO	InvenItemInfo[INVEN_ITEM_INFO_MAX + 16];
	sTHROW_ITEM_INFO	WareHouseItemInfo[120];
	int OpenWarehouseInfoFlag;


	DWORD dwTradePotionInfo[16];
	int TradePotionInfoCount;

	sMYSHOP_SELL_INFO	sMyShopList[MYSHOP_LIST_MAX];
	int MyShopListCount;
	DWORD dwMyShopTradeTime;

	int ThrowItemCount;

	int UnsaveMoney;

	int ServerMoney;
	int WareHouseMoney;

	DWORD dwRecvTimePlayBuff;
	DWORD srSendPlayBuffCnt;
	DWORD srRecvPlayBuffCnt;

	DWORD dwObjectSerial;

	int ChatMsgMode;
	char szChatMessage[256];


	char szTradeMessage[128];
	DWORD dwTradeMsgCode;

	smWINSOCK *lpsmSock;

	DWORD dwLastRecvTime;
	DWORD dwLastMotionRecvTime;

	int UpdateInfo_WaitCounter;
	int UpdateInfo_WarnigCounter;

	rsRECORD_DBASE	*lpRecordBase;
	rsPOST_BOX_ITEM	*lpPostBoxItem;
	int PostPassFailCount;

	// user
	AccountTypes security;
	int HideMode;

	DWORD dwConnectTime;

	int LastTransPlayUserCount;
	int LastTransAutoPlayCount;

	DWORD dwConnectCount;

	int frame;
	DWORD SendPlayGroupCount;

	DWORD MonTranCount;
	DWORD CharTransCount;

	int HitMonsterCount;
	smCHAR *lpChrTarget;
	DWORD dwTarObjSerial;

	int UserPacketLoop;
	int BefUserPacketLoop;

	int AttackCount;
	DWORD dwAttackTime;
	DWORD dwLastAttackTime;
	int DamagePacketCount;
	DWORD dwDamagePacketTime;

	int MonsterKillCounter;
	DWORD dwLastTradeChksum;
	DWORD dwLastTradeTime;


	short sLowLevel_PresentItem[2];

	DWORD dwStartUser_PresentItem_Time;
	DWORD dwStartUser_PresentItem_Count;

	int  KillCount;
	DWORD KillTime;

	bool isReceivedExpUp = false;



	int Send_AttackCount;
	int Send_AttackDamage;
	int Recv_AttackCount;
	int Recv_AttackDamage;



	DWORD dwMacroTime;
	int Macro_PosX;
	int Macro_PosZ;
	int Macro_AngY;
	DWORD dwMacroAngTime;
	DWORD dwMacroChkTime;



	DWORD dwSendFrames[CONNECTMAX];

	int CrackWarning;
	DWORD dwTime_Disconnect;
	int BadPlayer;
	DWORD dwPacketAttackCount;
	DWORD dwPacketAttackTime;
	int WarningCount;

	char *lpRecordDataBuff;
	DWORD dwRecordDataTime;

	int EventMode;
	int EventScore;
	int EventCount;
	DWORD dwEventTime;
	short sEventParam[2];

	int AreaOutCount;

	int BlockTime;

	int WhisperMode;

	int Event_StarTicketLevel;




	INT64 spExp_Start;
	int spMoney_Start;
	int spLevel_Start;

	int spExp_InOut_Total;
	int spMoney_In_Total;
	int spMoney_InOut_Total;

	int spEXP_Out;
	int spMoney_In;
	int spMoney_Out;

	DWORD dwLastExpMoneyCheckTime;
	DWORD dwLastExpMoneyTransServer;

	DWORD dwHopeDisconnectTime;

	int Client_Version;

	DWORD dwLastSaveTime;

	DWORD dwGameServerExp[8];

	DWORD dwNSpriteTime;


	DWORD dwClientFuncChk_1;
	DWORD dwClientFuncChk_2;
	int FuncChkFailCount1;
	int FuncChkFailCount2;
	int FuncChkSucessCount1;
	int FuncChkSucessCount2;
	DWORD dwFuncChkErrorFlag;
	int ClientFunChk1_Count;
	int ClientFunChk2_Count;

	DWORD dwClientFunChk_NextTime;

	int RecordWarningCount;
	int RecordWarningExp;

	DWORD dwClentOS;
	WORD wClentOSVersion[2];
	DWORD dwClentModulChkSum;
	int ClentModuleCount;

	DWORD dwDamagePacketKey[2];
	DWORD dwDamagePacketKey2[2];



	DWORD PartyUpdateFlag;
	DWORD dwPartyInfo;
	rsPLAYINFO *lpPartyMaster;
	DWORD PartyMasterObjectCode;
	rsPLAYINFO *lpPartyPlayers[PARTY_PLAYER_MAX];
	DWORD dwPartyObjectCode[PARTY_PLAYER_MAX];
	DWORD PartyLevelAverage;
	int PartyUserCount;


	DWORD dwClanCode;
	int ClanTicketCode;
	int SucessCheck_ClanCode;




	char	szGuid[128];
	char	szPwd[33];
	char	szGPCode[16];
	time_t	DisuseDay;
	int UsePeriod;
	int GpCode;
	int GpType;
	DWORD	dwPeriodTime;
	int Bl_RNo;
	int Bl_Meter;
	DWORD	dwPeriodTime2;




	int SndItemSecCodeCount;
	int RcvItemSecCodeBuff[8][16];



	short	sLimitDamage[2];
	short	sLimitCritical[2];



	int ServerPotion[3][4];




	DWORD	dwSkill_AutoMation_Time;
	int dwSkill_AutoMation_Param;

	DWORD	dwSkill_Maximize_Time;
	int dwSkill_Maximize_Param;

	DWORD	dwSkill_PhysicalAbsorb_Time;
	int dwSkill_PhysicalAbsorb_Param;

	DWORD	dwSkill_ExtreamShield_Time;
	int dwSkill_ExtreamShield_Param;


	DWORD	dwSkill_HolyBody_Time;
	int dwSkill_HolyBody_Param;

	DWORD	dwSkill_HolyValor_Time;
	int dwSkill_HolyValor_Param;

	DWORD	dwSkill_Alas_Time;
	int		dwSkill_Alas_Param;

	DWORD   dwSkill_RainMaker_Time;
	int     dwSkill_RainMaker_Param;

	DWORD	dwSkill_HolyReflection_Time;
	int dwSkill_HolyReflection_Param;

	DWORD	dwSkill_EnchantWeapon_Time;
	int dwSkill_EnchantWeapon_Param;

	DWORD	dwSkill_MetalArmor_Time;
	int dwSkill_MetalArmor_Param;


	DWORD	dwSkill_SparkShield_Time;
	int dwSkill_SparkShield_Param;


	DWORD	dwSKill_Falcon_Time;
	short	dwSKill_Falcon_Damage[2];


	DWORD	dwSkill_DivineInhalation_Time;
	DWORD	dwSkill_DivineInhalation_Param;


	DWORD	dwSkill_TriumphOfValhalla_Time;
	DWORD	dwSkill_TriumphOfValhalla_Param;


	DWORD	dwSkill_VirtualLife_Time;
	DWORD	dwSkill_VirtualLife_Param;

	DWORD	dwSkill_Blind_Time;
	DWORD	dwSkill_Blind_Param;

	DWORD   dwSkill_ChasingHunt_Time;
	DWORD   dwSkill_ChasingHunt_Param;


	DWORD	dwSkill_EnergyShield_Time;
	DWORD	dwSkill_EnergyShield_Param;


	DWORD	dwSkill_SpiritElemental_Time;
	DWORD	dwSkill_SpiritElemental_Param;


	DWORD	dwSkill_DancingSword_Time;
	DWORD	dwSkill_DancingSword_Param;
	DWORD	dwSkill_DancingSword_DelayTime;


	DWORD	dwSkill_Vanish_Time;
	DWORD	dwSkill_Vanish_Param;


	DWORD	dwSkill_Compulsion_Time;
	DWORD	dwSkill_Compulsion_Param;


	DWORD	dwSkill_MagneticSphere_Time;
	DWORD	dwSkill_MagneticSphere_Param;


	DWORD	dwSkill_Berserker_Time;
	DWORD	dwSkill_Berserker_Param;


	DWORD	dwSkill_AssassinEye_Time;
	DWORD	dwSkill_AssassinEye_Param;


	DWORD	dwSkill_Vague_Time;
	DWORD	dwSkill_Vague_Param;


	DWORD	dwSkill_ForceOfNature_Time;
	WORD	wSkill_ForceOfNature_Param[2];


	DWORD	dwSkill_GodlyShied_Time;
	DWORD	dwSkill_GodlyShied_Param;


	DWORD	dwSkill_GodsBless_Time;
	DWORD	dwSkill_GodsBless_Param;


	DWORD	dwSkill_HallOfValhalla_Time;
	WORD	wSkill_HallOfValhalla_Param[2];


	DWORD	dwSkill_FrostJavelin_Time;
	DWORD	dwSkill_FrostJavelin_Param;


	DWORD	dwSkill_RegenerationField_Time;


	DWORD	dwSkill_SummonMuspell_Time;
	DWORD	dwSkill_SummonMuspell_Param;




	DWORD	dwCurse_Attack_Time;
	DWORD	dwCurse_Attack_Param;

	DWORD	dwCurse_Defence_Time;
	DWORD	dwCurse_Defence_Param;



	BYTE	bSkillPoint[SKILL_POINT_COLUM_MAX];






	DWORD	dwForceOrb_Code;
	DWORD	dwForceOrb_Time;
	DWORD	dwForceOrb_Damage;

	DWORD	dwForceOrb_SaveCode;
	DWORD	dwForceOrb_SaveTime;
	DWORD	dwForceOrb_SaveDamage;
	DWORD	dwForceOrb_NextSetTime;


	DWORD	dwLifeBooster_Code;
	DWORD	dwLifeBooster_Time;
	DWORD	dwLifeBooster_Data;

	DWORD	dwLifeBooster_SaveCode;
	DWORD	dwLifeBooster_SaveTime;
	DWORD	dwLifeBooster_SaveData;
	DWORD	dwLifeBooster_NextSetTime;


	DWORD	dwManaBooster_Code;
	DWORD	dwManaBooster_Time;
	DWORD	dwManaBooster_Data;

	DWORD	dwManaBooster_SaveCode;
	DWORD	dwManaBooster_SaveTime;
	DWORD	dwManaBooster_SaveData;
	DWORD	dwManaBooster_NextSetTime;


	DWORD	dwStaminaBooster_Code;
	DWORD	dwStaminaBooster_Time;
	DWORD	dwStaminaBooster_Data;

	DWORD	dwStaminaBooster_SaveCode;
	DWORD	dwStaminaBooster_SaveTime;
	DWORD	dwStaminaBooster_SaveData;
	DWORD	dwStaminaBooster_NextSetTime;



	DWORD	dwPrimeItem_NextSetTime;
	DWORD	dwTime_PrimeItem_X2;
	DWORD	dwTime_PrimeItem_ExpUp;
	DWORD	dwPrimeItem_PackageCode;

	DWORD	dwTime_PrimeItem_VampCuspid;
	DWORD	dwTime_PrimeItem_ManaRecharg;
	DWORD	dwTime_PrimeItem_MightofAwell;
	DWORD	dwTime_PrimeItem_MightofAwell2;
	DWORD	dwTime_PrimeItem_ManaReduce;
	DWORD	dwTime_PrimeItem_PhenixPet;
	DWORD	dwTime_PrimeItem_HelpPet;
	DWORD	dwTime_PrimeItem_VampCuspid_EX;
	DWORD	dwTime_PrimeItem_StaminaReduce;

	DWORD	dwTime_BigHead1;
	DWORD	dwTime_BigHead2;
	DWORD	dwTime_BigHead3;
	DWORD	dwTime_BigHead4;

	DWORD   dwTime_VIP;
	DWORD	dwPCBang_Pet_AttackTime;
	DWORD	dwPCBang_Pet_NextSetTime;


	DWORD	dwHelp_Pet_AttackTime;
	DWORD	dwHelp_Pet_NextSetTime;


	DWORD	dwSkillDelay_Code;
	DWORD	dwSkillDelay_Time;
	DWORD	dwSkillDelay_Data;

	DWORD	dwSkillDelay_SaveCode;
	DWORD	dwSkillDelay_SaveTime;
	DWORD	dwSkillDelay_SaveData;
	DWORD	dwSkillDelay_NextSetTime;

	int     iVIP;
	DWORD   tVIP;

	DWORD   QuestDiary_State;
	DWORD   QuestDiary_Time;
	DWORD   QuestDiary_Kill;
	int     BattleLevel;
	int     BattleExp;

	smCHAR	*lpLinkChar;
	DWORD	dwLinkCharCode;


	short	sBlessCastle_Damage[2];
	DWORD	dwCheck_MasterClanTime;


	sCASTLE_MASTER	CastleMaster;
	DWORD	dwBlessSkill_Code;
	DWORD	dwBlessSkill_Time;
	DWORD	dwBlessSkill_Param;

	DWORD	dwSiegeItem_Scroll_Time;
	DWORD	dwSiegeItem_Scroll_Code;
	DWORD	dwSiegeItem_Scroll_Param;

	DWORD	dwSiegeItem_Stone1_Time;
	DWORD	dwSiegeItem_Stone1_Code;
	DWORD	dwSiegeItem_Stone1_Param;

	DWORD	dwSiegeItem_Stone2_Time;
	DWORD	dwSiegeItem_Stone2_Code;
	DWORD	dwSiegeItem_Stone2_Param;

	short	sCheckPlayField_Count[2];

	DWORD	dwHaQuestItemCount;

	char	szUserExpTimeID[ACCOUNT_SIZE];
	char	szUserExpTimeName[NAME_SIZE];
	DWORD	dwExpGameTime;
	DWORD	dwExpGameTimeCheck;
	DWORD   dwCountMin;

	UINT lastMessageTick;
	bool auth = false;

	int iPartyMode = 0;


	bool setSecurity(AccountTypes value)
	{
		security = value;

		return true;
	}

	bool setAccountId(int value)
	{
		bool result = false;

		if (value >= 0)
		{
			accountId = value;
			result = true;
		}
		else
		{
			Log::getInstance()->output(LOG_SERVER, "[OUT OF RANGE]: setAccountId(int value): value < 0 [%d]", value);
		}

		return result;
	}

	bool setAccount(const char* value)
	{
		bool result = false;

		if (value)
		{
			size_t len = strlen(value);

			if (len > ACCOUNT_SIZE - 1)
			{
				Log::getInstance()->output(LOG_SERVER, "[OVERFLOW]: setAccount(const char* value): strlen(value) > (ACCOUNT_SIZE - 1) [%s]", value);
			}
			else
			{
				strcpy_s(account, sizeof(account), value);
				account[ACCOUNT_SIZE - 1] = '\0';
				result = true;
			}
		}

		if (!result)
		{
			::memset(account, 0, sizeof(account));
		}

		return result;

	}

	bool setPassword(const char* value)
	{
		bool result = false;

		if (value)
		{
			size_t len = strlen(value);

			if (len > PASSWORD_SIZE - 1)
			{
				Log::getInstance()->output(LOG_SERVER, "[OVERFLOW]: setPassword(const char* value): strlen(value) > (PASSWORD_SIZE - 1) [%s]", value);
			}
			else
			{
				strcpy_s(password, sizeof(password), value);
				password[PASSWORD_SIZE - 1] = '\0';
				result = true;
			}
		}

		if (!result)
		{
			::memset(password, 0, sizeof(password));
		}

		return result;
	}

	bool setName(const char* value)
	{
		bool result = false;

		if (value)
		{
			size_t len = strlen(value);

			if (len > NAME_SIZE - 1)
			{
				Log::getInstance()->output(LOG_SERVER, "[OVERFLOW]: setName(const char* value): strlen(value) > (NAME_SIZE - 1) [%s]", value);
			}
			else
			{
				strcpy_s(name, sizeof(name), value);
				name[NAME_SIZE - 1] = '\0';
				result = true;
			}
		}

		if (!result)
		{
			::memset(name, 0, sizeof(name));
		}

		return result;
	}

	AccountTypes getSecurity() const
	{
		return security;
	}

	int getAccountId() const
	{
		return accountId;
	}

	std::string getAccount() const
	{
		return std::string(account);
	}
	std::string getPassword() const
	{
		return std::string(password);
	}

	std::string getName() const
	{
		return std::string(name);
	}


	bool setLastMessageTick(UINT value)
	{
		lastMessageTick = value;

		return true;
	}

	UINT getLastMessageTick() const
	{
		return lastMessageTick;
	}

	int	CreateParty(rsPLAYINFO* lpPlayInfo);
	int UpdatePartyMode(rsPLAYINFO* lpPlayInfo, int Mode);
	int	JoinPartyPlayer(rsPLAYINFO* lpPlayInfo);
	int	DeletePartyPlayer(rsPLAYINFO* lpPlayInfo);
	int ChangePartyPlayer(rsPLAYINFO* lpOldPlayInfo, rsPLAYINFO* lpNewPlayInfo);
	int	UpdatePartyPlayer();
	int	UpdatePartyPlayInfo();
	int GetPartyMoney(sITEMINFO* lpDefItemInfo, rsPLAYINFO* lpPlayInfo);
	int GetPartyExp(smCHAR* lpChar, rsPLAYINFO* lpPlayInfo);
	int PartyChatting(rsPLAYINFO* lpPlayInfo);

	int	UpdateServerPartyPlayer(TRANS_PARTY_PLAYINFO* lpTransPartyPlayInfo);


	int	LeavePartyMaster(rsPLAYINFO* lpPlayInfo);
	int	ReleaseParty();


	int SendPartyMessage(char* szMessage, DWORD dwCode);

	int SendPartyData(rsPLAYINFO* lpPlayInfo_From, char* szData);


	int	JoinParty(rsPLAYINFO* lpPlayMaster);
	int	SecedeParty();
	int	DisconnectPartyUser();


	int	AddServerMoney(int Money, int WhereParam = 0);
	int	SubServerMoney(int Money, int WhereParam = 0);
	int	SetServerMoney(int Money, int WhereParam = 0);

	int	CallBack_ClanMarkNum(int ClanMarkNum);


};

typedef rsPLAYINFO Player;











#define BILLING_GPTYPE_DAY 0
#define BILLING_GPTYPE_TIME 1
#define BILLING_GPTYPE_FREE 2
#define BILLING_GPTYPE_POTAL	3

#define BILLING_PGTYPE_PERSONAL	0
#define BILLING_PGTYPE_PCROOM	0









struct TRANS_CHATBUFF
{
	int size;
	int code;
	DWORD	dwIP;
};

struct CHATBUFF
{
	DWORD	dwIP;
	char szMessage[256];
};

struct TRANS_CHATMESSAGE
{
	int size;
	int code;
	DWORD	dwIP;
	DWORD	dwObjectSerial;

	char szMessage[256];

	TRANS_CHATMESSAGE()
	{
		size = 0;
		code = 0;
		dwIP = 0;
		dwObjectSerial = 0;
		ZeroMemory(szMessage, sizeof(szMessage));
	}
};

struct smPLAYDATA_GROUP
{
	int size, code;
	int PlayDataCnt;
	DWORD	dwSendCode;
};


#define smPLAYBUFF_FRAME_NONE 0xFFFF0000

#define	smPLAYBUFF_ITEM_BODY 0
#define	smPLAYBUFF_ITEM_LEFT 1
#define	smPLAYBUFF_ITEM_RIGHT 2
#define	smPLAYBUFF_ITEM_SKIL 3

struct smPLAYBUFF
{
	int x, y, z;
	DWORD	frame;
	short	angle[4];

	short	wStickItems[4];
	DWORD	dwTargetSerial;
};




struct smPLAYDATA
{
	int	size;
	int code;

	DWORD	dwObjectSerial;

	int x, y, z;
	short angle[4];

	DWORD	frame;
	DWORD	dwAutoCharCode;

};

struct smPLAYDATA2
{
	int	size;
	int code;

	DWORD	dwObjectSerial;

	short	BuffCount[2];
	smPLAYBUFF	PlayBuff[2];
	DWORD	dwTarget;

};

struct smPLAYDATA3
{
	int	size;
	int code;

	DWORD	dwObjectSerial;

	short	BuffCount[3];
	smPLAYBUFF	PlayBuff[3];
	DWORD	dwTarget;
};



struct smTRANS_PLAYBUFF
{
	int BuffCount;
	smPLAYBUFF	PlayBuff;
};

#define TRANS_PLAYDATA_EVENT_LEVEL 0
#define TRANS_PLAYDATA_EVENT_POTION 1
#define TRANS_PLAYDATA_EVENT_SKIL 2
#define TRANS_PLAYDATA_EVENT_EXT 3


struct smTRANS_PLAYDATA
{
	int	size;
	int code;

	DWORD	dwObjectSerial;
	DWORD	dwTarget;

	int PlayBuffCnt;
	int StartPosi;

	short	Hp[2];
	DWORD	dwAutoCharCode;
	short	wArea[2];
	BYTE	bUpdateInfo[4];
	BYTE	bEventInfo[4];
};


struct smEFFECT_ITEM
{
	int size, code;

	DWORD	dwItemCode;

	int ColorBlink;
	short	sColors[4];
	DWORD	DispEffect;
	DWORD	BlinkScale;
};


struct smTRANS_CHAR_COMMAND
{
	int	size;
	int code;

	int LParam;
	int WParam;
	int SParam;

	char szName[NAME_SIZE];

	smTRANS_CHAR_COMMAND()
	{
		size = 0;
		code = 0;
		LParam = 0;
		WParam = 0;
		SParam = 0;

		memset(szName, 0, sizeof(szName));
	}
};


struct smTRANS_CHAR_COMMAND2
{
	int	size;
	int code;

	int LParam;
	int WParam;
	int SParam;

	char	szId[ACCOUNT_SIZE];
	char	szName[NAME_SIZE];

	smTRANS_CHAR_COMMAND2()
	{
		size = 0;
		code = 0;
		LParam = 0;
		WParam = 0;
		SParam = 0;

		memset(szId, 0, sizeof(szId));
		memset(szName, 0, sizeof(szName));
	}
};






struct smTRNAS_PLAYERINFO
{
	int	size;
	int code;

	smCHAR_INFO	smCharInfo;

	DWORD	dwObjectSerial;

	int	x, y, z;
	int ax, ay, az;
	int state;
};

struct smTRNAS_PLAYERINFO_QUICK
{
	int	size;
	int code;

	DWORD	dwObjectSerial;

	int	x, y, z;
	int ax, ay, az;
	int state;

	smCHAR_INFO	smCharInfo;
};


struct smTRANS_COMMAND_DWORD
{
	int	size;
	int code;

	DWORD LParam;
	DWORD WParam;
	DWORD SParam;
	DWORD EParam;
};

struct smTRANS_COMMAND_EX
{
	int	size;
	int code;

	int LParam;
	int WParam;
	int SParam;
	int EParam;

	int LxParam;
	int WxParam;
	int SxParam;
	int ExParam;

	smTRANS_COMMAND_EX()
	{
		size = 0;
		code = 0;
		LParam = 0;
		WParam = 0;
		SParam = 0;
		EParam = 0;
		LxParam = 0;
		WxParam = 0;
		SxParam = 0;
		ExParam = 0;
	}

};

struct smTRANS_COMMAND_BUFF
{
	smTRANS_COMMAND smTransCommand;
	char	*Buff[256];
};

struct smTRANS_COMMAND_SOD
{
	smTRANS_COMMAND smTransCommand;
	int MyScore;
	int MyTeam;
	int TeamScore[4];
	int Temp[4];
};

struct smTRANS_COMMAND_POLLING
{
	smTRANS_COMMAND smTransCommand;
	BYTE	bPolling[10];
};


struct smTRANS_RESISTANCE
{
	int	size;
	int code;
	int	Param;
	short Resistance[8];
	int	Absorb;
};


struct smTRANS_BLESSCASTLE
{
	smTRANS_COMMAND smTransCommand;
	int TaxRate;
	short Tower[12];
	unsigned char	MercenaryNum[4];
	int ClanSkill;
	int Price;
	DWORD dwMasterClan;
	int Temp[4];
};


struct	rsUSER_LIST_TOP10
{

	int size, code;

	int tCode;
	DWORD	dwObjectSerial;
	DWORD	dwNameCode;
	int x, y, z;



	DWORD	dwCharCode;
	DWORD	dwUpdateTime;
	DWORD	dwTotalDamage;
	char	bCrystalTowerCount[4];
	DWORD	dwTemp[2];

	DWORD	dwUserCode[10];
	int Damage[10];
	int Counter[10];
};







#define	TRANS_GROUPITEM_MAX 16
#define	TRANS_GROUPITEM_HEADER_SIZE (14*4)


struct	TRANS_ITEMINFO_GROUP
{
	int	size, code;

	int Index;
	int Result;
	int Money;
	int	ItemCount;

	DWORD	dwTemp[8];

	sITEMINFO	sItemInfo[TRANS_GROUPITEM_MAX];
};


struct	TRANS_ITEMINFO_GROUP2
{
	int	size, code;

	int Index;
	int Result;
	int Money;
	int	ItemCount;

	DWORD	dwTemp[8];

	char	szBuff[sizeof(sITEMINFO) * TRANS_GROUPITEM_MAX];
};


struct TRANS_ITEMINFO
{



	int	size, code;




	sITEMINFO	Item;

	int x, y, z;

	DWORD	dwSeCode[4];
};

struct	TRANS_ITEM_CODE
{
	int size, code;

	DWORD	dwFlag;

	DWORD	dwItemCode;
	DWORD	dwHead;
	DWORD	dwChkSum;
	DWORD	dwTime;
};

struct TRANS_ITEM
{
	int state;

	int type;
	int ItemCode;

	int x, y, z;
	char szName[64];
	void *lpStgArea;
	DWORD       iClass;
};

struct _TRANS_THROW_ITEM
{
	DWORD	dwCode;
	DWORD	dwHead;
	DWORD	dwChkSum;
};

#define	THROW_ITEMS_MAX 32

#define	TRANS_THROW_ITEMS_DEFSIZE	(sizeof(int)*4)

struct TRANS_THROW_ITEMS
{
	int size, code;
	int ThrowItemCount;
	int Temp;

	_TRANS_THROW_ITEM	ThrowItems[THROW_ITEMS_MAX];
};


struct _TRANS_RECORD_TRADE_ITEM
{
	DWORD	dwCode;
	DWORD	dwHead;
	DWORD	dwChkSum;
	int State;
};


#define _MAX_TRADE_ITEM 20

struct TRANS_TRADE_ITEMKEY
{
	int size, code;
	DWORD	dwSender;
	DWORD	dwRecver;
	DWORD	dwSum;

	DWORD	dwItemCode[_MAX_TRADE_ITEM];
	DWORD	dwItemKey[_MAX_TRADE_ITEM];
	DWORD	dwItemSum[_MAX_TRADE_ITEM];

	int Money;
	int Coin;
};

#define	TRADE_RECV_ITEMS_MAX 32


#define	TRANS_RECORD_TRADE_DEFSIZE (sizeof(int)*16)

struct TRANS_RECORD_TRADE_ITEMS
{
	int size, code;
	int Money;
	int ThrowItemCount;
	char	szTradeUserName[32];
	int Temp[4];

	_TRANS_RECORD_TRADE_ITEM	Items[TRADE_RECV_ITEMS_MAX];
};

#define TRANS_ITEM_MAX 16


struct smTRANS_ITEMS
{
	int size, code;

	int state;
	int Count;

	TRANS_ITEM	Items[TRANS_ITEM_MAX];
};


struct smTRANS_ACITON_ITEM
{
	int size, code;

	int state;

	int x, y, z;
	void *lpStgArea;
};


struct smTRANS_SELL_ITEM
{
	int size, code;
	int	ItemKind;
	int	ItemCounter;
	int	Ext[4];
};


#define TRANS_TRADE_BUFF_SIZE 4000
struct TRANS_TRADEITEMS
{
	int size, code;
	DWORD	dwSender;
	DWORD	dwRecver;
	DWORD	dwSum;
	DWORD	Temp[4];

	BYTE	TradeBuff[TRANS_TRADE_BUFF_SIZE];
};

#define	SOD_RESULT_MAX	32

struct	_SOD_RESULT
{
	char szName[32];
	rsPLAYINFO	*lpPlayInfo;
	int JobCode;
	int Class;
	int Score;
	int Monster;
	DWORD dwTemp[4];
};


struct	TRANS_SOD_RESULT
{
	int	size, code;

	DWORD	dwGameCode;
	DWORD	dwGameTime;
	DWORD	dwDisplayMode;
	short	TeamRound[2];

	DWORD	dwTemp[15];

	int ResultCount;

	_SOD_RESULT	Result[SOD_RESULT_MAX];
};


struct	sSERVER_MONEY
{
	int	InputMoney;
	int	Counter;
	int	TotalX;
	int	TotalY;
	int	TotalZ;
};

struct sSERVER_EXP
{
	int	Counter;
	int	InputExp;
	int	Total1;
	int	Total2;
};

struct TRANS_TOTAL_EXPMONEY
{
	int	size, code;

	sSERVER_MONEY	sServerMoney;
	sSERVER_EXP sServerExp;
};


struct	TRANS_SEND_DATASERVER
{
	int size, code;
	char	szBuff[1024];
};


struct	TRANS_BUY_SHOPITEM
{
	int	size, code;

	sITEM	sItem;
	int ItemCount;
};


struct	_TRANS_USINGITEM
{
	DWORD	dwCode;
	short	Performance[8];
};

struct	TRANS_USINGITEM
{
	int	size, code;
	int	ItemListCount;
	_TRANS_USINGITEM	ItemList[16];
};


struct TRANS_PREMIUM_TIME
{
	int	size;
	int code;

	DWORD	ThirdEye;
	DWORD	ExpUp;
	DWORD	VampCuspid;
	DWORD	ManaRecharg;
	DWORD	MightofAwell;
	DWORD	MightofAwell2;
	DWORD	ManaReduce;
	DWORD	PhenixPet;
	DWORD	HelpPet;
	DWORD	VampCuspidEx;
	DWORD	StaminaReduce;
	DWORD   VIP;

	TRANS_PREMIUM_TIME()
	{
		size = 0;
		code = 0;
		ThirdEye = 0;
		ExpUp = 0;
		VampCuspid = 0;
		ManaRecharg = 0;
		MightofAwell = 0;
		MightofAwell2 = 0;
		ManaReduce = 0;
		PhenixPet = 0;
		HelpPet = 0;
		VampCuspidEx = 0;
		StaminaReduce = 0;
		VIP = 0;
	}
};

#define	FIND_CRACK_LIST_MAX 64

struct	_CRACK_NAME
{
	char	szName1[12];
	char	szName2[12];
	char	szClass[12];
};

struct	TRANS_FIND_CRACKER
{
	int size, code;

	int FindCounter;

	_CRACK_NAME	CrackName[FIND_CRACK_LIST_MAX];

	char	szTemp[128];
};

#define	PARTY_STATE_NONE 0
#define	PARTY_STATE_MASTER 1
#define	PARTY_STATE_MEMBER 2


struct _PARTY_USER
{
	char	szName[32];
	char	szModelName[64];
	char	szModelName2[64];

	DWORD	dwObjectSerial;
	DWORD	Level;
	short	Life[2];
	short	Mana[2];
	int x, z;
	int JobCode;
};

struct TRANS_PARTY_USERS
{
	int size, code;

	DWORD	dwObjectSerial;
	DWORD	dwTemp[8];

	int PartyUserCount;

	_PARTY_USER PartyUser[PARTY_PLAYER_MAX];
	int iPartyMode;
};

struct _PARTY_PLAYINFO
{
	DWORD	dwObjectSerial;
	DWORD	Level;
	short	Life[2];
	short	Mana[2];
	int x, z;
};

struct	TRANS_PARTY_PLAYINFO
{
	int size, code;

	DWORD	dwObjectSerial;
	DWORD	dwTemp;

	int PartyUserCount;

	_PARTY_PLAYINFO	PlayInfo[PARTY_PLAYER_MAX];
};

struct	TRANS_PARTY_SKILL
{
	int size, code;
	DWORD	dwSkillCode;
	int Point;
	int wParam;
	int lParam;
	int sParam;
	int eParam;
	int PartyCount;
	DWORD	dwPartyUser[8];
};

struct TRANS_CLAN_COMMAND_USER
{
	int size, code;
	int	Param[4];
	int	UserCount;

	char	szUserBuff[2048];
};

#define	CLAN_USER_MAX	64

struct _CLAN_USER_INFO
{
	char szName[32];
	DWORD dwSpeedSum;
	DWORD dwObjectSerial;
	rsPLAYINFO* lpPlayInfo;
};

struct	rsCLAN_INFOMATION
{
	DWORD	dwClanCode;
	DWORD	dwTemp[32];

	_CLAN_USER_INFO	ClanUserInfo[CLAN_USER_MAX];
};


struct	TRANS_WAREHOUSE
{
	int size, code;

	DWORD	dwChkSum;
	WORD	wVersion[2];
	int WareHouseMoney;
	int UserMoney;
	DWORD	dwTemp[5];

	int DataSize;
	BYTE	Data[sizeof(sITEM) * 100 + 256];
};

#define	TRANS_SERVER_MAX 8


struct _TRANS_SERVER_INFO
{
	char	szServerName[32];
	char	szServerIp1[20];
	char	szServerIp2[20];
	char	szServerIp3[20];

	DWORD	dwServerPort1;
	DWORD	dwServerPort2;
	DWORD	dwServerPort3;

	DWORD	ConnState;
};


struct TRANS_SERVER_LIST
{
	int size, code;

	char	szServerName[16];

	DWORD	dwServerTime_t;
	int ClanTicket;
	int	dwTemp[1];
	int	ClanServerCount;
	int	ServerCount;
	_TRANS_SERVER_INFO ServerInfo[TRANS_SERVER_MAX];

	TRANS_SERVER_LIST()
	{
		size = 0;
		code = 0;
		ZeroMemory(szServerName, sizeof(szServerName));
		dwServerTime_t = 0;
		ClanTicket = 0;
		ZeroMemory(&dwTemp, sizeof(dwTemp));
		ClanServerCount = 0;
		ServerCount = 0;
		ZeroMemory(&ServerInfo, sizeof(ServerInfo));
	}
};

const int SERVER_MAP_MAX = 64;

struct	TRANS_SEVER_MAP
{
	int size, code;

	DWORD	dwTemp[30];

	int IP_Count;
	DWORD	dwIP[SERVER_MAP_MAX];
};

struct	TT_DATA_SERVER_INFO
{
	char	szServerID[16];
	char	szServerPath[128];
};


#define	SYSTEM_IP_MAX 32
#define	LOGIN_IP_MAX 16
#define	DISABLE_IP_MAX 500
#define	ENABLE_IP_MAX 100
#define	ADMIN_IP_MAX 16
#define CLAN_SERVER_MAX 3
#define ENABLE_MODULE_CHECK_MAX	64	
#define	TT_DATA_SERVER_MAX 16


struct rsSERVER_CONFIG
{
	DWORD	ServerCode;
	DWORD	AutoPlayer;
	DWORD	DisableParty;
	DWORD	EnablePlayerKill;
	DWORD	ConnectUserMax;

	int TestSeverMode;

	int UseRecorMemory;
	int PotionMonitor;

	int ClientCheckSumCount;
	int ClientCheckOut;
	DWORD	dwClientCheckSum[32];

	int SafeClientCodeCount;
	int ClientCodeCheckOut;
	DWORD	dwSafeClientCode[32];

	int LimitVersion;

	char	szServerName[64];
	int Enable_PK;
	int CheckProtect;

	int BlockLevel;
	int BlockLevel_LogOut;
	int ItemCodeOut;

	int ClientFuncCheckMode;
	int Enable_PartyItem;


	int Event_Mandoo;
	int Event_HardCore;
	int Event_DamageOff;



	int Event_DamageOff1;
	int Event_DamageOff2;


	int Event_DefenseOff;

	int Event_Child;
	int Event_Cristal;
	int Event_Potion;
	int Event_StarPointTicket;
	int Event_ValentineDay;
	int Event_WhiteDay;
	int Event_MorifSheltom;
	int Event_MollyWolf;
	int Event_Ghost;
	int Event_SantaGoblin;
	int Event_WorldCup;
	int Event_ExpUp;
	int Event_CoupleRing;
	int Event_Watermelon;
	int Event_Star;
	int Event_Valentine;
	int Event_PristonAlphabet;
	int Event_WhiteContrast;
	int Event_Candydays;
	int Event_BlackSmith;
	int Event_MagicalGreen;
	int Event_TearOfKara;
	int Event_WarerMelonMonster;
	int Event_Chichen_Day;
	int Event_MovieBloodyBattle;


#ifdef _LANGUAGE_ARGENTINA
	int Event_ExpUp_latin;
#endif

	int Event_SummerChicken;
	int Event_GiftBox;

	int BlessCastleMode;
	short	sBlessCastle_StartTime[2];

	int Record_JobChanger;
	int ForeverBlockMode;

	int Permit_Exp;
	int Permit_Money;

	int ClientProcessTimeChk;
	int ClientProcessTimeChkOut;
	int Dis_PotionError;

	int ExpFixMode;

	char	szBlockUserPath[64];

	int DispBillingTime;

	//int Disable_LogIn;
	int allowed_login;
	int Disable_LogQue;
	int Disable_CheckLogOut;

	int ExpGameTimeMode;

	int ServerInventoryMode;

	DWORD	DisableIP[DISABLE_IP_MAX][2];
	int DisableIP_Count;

	DWORD	EnableIP[ENABLE_IP_MAX][2];
	int EnableIP_Count;

	DWORD	AdminIP[ADMIN_IP_MAX][2];
	int AdminIP_Count;

	char	szBackupPath[80];

	char szClanServerIP[CLAN_SERVER_MAX][20];
	int ClanServerPort[CLAN_SERVER_MAX];
	int ClanServerCount;


	DWORD	Enable_ClientModule[ENABLE_MODULE_CHECK_MAX];
	int Enable_ClientModuleCount;

	int Disable_DecSkillPoint;

	int Disable_Quest;

	int CrazyPacketMode;

	char	szNoticeURL[256];


	TRANS_SEVER_MAP	AreaServer;

	int RecordAdminCommand;

	int FreeLevel;
	char	szFreeGpCode[32];
	int PresentLevel;
	int Event_ComicBirthDay;
	int Event_Puzzle;
	int Event_BabelHorn;
	int Event_NineFox;
	int EVENT_Christmas;
	int EventPlay_BitMask;
	int Event_PCBangPet;

	int StartUser_PresentItem;

	int GameGuard_Auth;

	int RemoveNProtectTime;

	int TT_DataServer_Count;
	TT_DATA_SERVER_INFO TT_DataServer[TT_DATA_SERVER_MAX];

	int FixedStartField;
	int DisableThrowItem;

	int CheckPlayField;

	int Enable_PKField;
	int Enable_PKField1;
	int Enable_PKField2;
	int Enable_PKField3;

	int Enable_PKField_All;


	int CheckModelFile;

#ifdef LOG_THE_PK
	bool bPK_LOG;
#endif

	rsSERVER_CONFIG()
	{
		ServerCode = 0;
		AutoPlayer = 0;
		DisableParty = 0;
		EnablePlayerKill = 0;
		ConnectUserMax = 0;
		TestSeverMode = 0;
		UseRecorMemory = 0;
		PotionMonitor = 0;
		ClientCheckSumCount = 0;
		ClientCheckOut = 0;
		ZeroMemory(&dwClientCheckSum, sizeof(dwClientCheckSum));
		SafeClientCodeCount = 0;
		ClientCodeCheckOut = 0;
		ZeroMemory(&dwSafeClientCode, sizeof(dwSafeClientCode));
		LimitVersion = 0;
		ZeroMemory(szServerName, sizeof(szServerName));
		Enable_PK = 0;
		CheckProtect = 0;
		BlockLevel = 0;
		BlockLevel_LogOut = 0;
		ItemCodeOut = 0;
		ClientFuncCheckMode = 0;
		Enable_PartyItem = 0;
		Event_Mandoo = 0;
		Event_HardCore = 0;
		Event_DamageOff = 0;
		Event_DamageOff1 = 0;
		Event_DamageOff2 = 0;
		Event_DefenseOff = 0;
		Event_Child = 0;
		Event_Cristal = 0;
		Event_Potion = 0;
		Event_StarPointTicket = 0;
		Event_ValentineDay = 0;
		Event_WhiteDay = 0;
		Event_MorifSheltom = 0;
		Event_MollyWolf = 0;
		Event_Ghost = 0;
		Event_SantaGoblin = 0;
		Event_WorldCup = 0;
		Event_ExpUp = 0;
		Event_CoupleRing = 0;
		Event_Watermelon = 0;
		Event_Star = 0;
		Event_Valentine = 0;
		Event_PristonAlphabet = 0;
		Event_WhiteContrast = 0;
		Event_Candydays = 0;
		Event_BlackSmith = 0;
		Event_MagicalGreen = 0;
		Event_TearOfKara = 0;
		Event_WarerMelonMonster = 0;
		Event_Chichen_Day = 0;
		Event_MovieBloodyBattle = 0;
#ifdef _LANGUAGE_ARGENTINA
		Event_ExpUp_latin = 0;
#endif
		Event_SummerChicken = 0;
		Event_GiftBox = 0;
		BlessCastleMode = 0;
		ZeroMemory(&sBlessCastle_StartTime, sizeof(sBlessCastle_StartTime));
		Record_JobChanger = 0;
		ForeverBlockMode = 0;
		Permit_Exp = 0;
		Permit_Money = 0;
		ClientProcessTimeChk = 0;
		ClientProcessTimeChkOut = 0;
		Dis_PotionError = 0;
		ExpFixMode = 0;
		ZeroMemory(szBlockUserPath, sizeof(szBlockUserPath));
		DispBillingTime = 0;
		//Disable_LogIn = 0;
		allowed_login = 0;
		Disable_LogQue = 0;
		Disable_CheckLogOut = 0;
		//Disable_LogIn2 = 0;
		ExpGameTimeMode = 0;
		ServerInventoryMode = 0;
		ZeroMemory(&DisableIP, sizeof(DisableIP));
		DisableIP_Count = 0;
		ZeroMemory(&EnableIP, sizeof(EnableIP));
		EnableIP_Count = 0;
		ZeroMemory(&AdminIP, sizeof(AdminIP));
		AdminIP_Count = 0;
		ZeroMemory(szBackupPath, sizeof(szBackupPath));
		ZeroMemory(szClanServerIP, sizeof(szClanServerIP));
		ZeroMemory(&ClanServerPort, sizeof(ClanServerPort));
		ClanServerCount = 0;
		ZeroMemory(&Enable_ClientModule, sizeof(Enable_ClientModule));
		Enable_ClientModuleCount = 0;
		Disable_DecSkillPoint = 0;
		Disable_Quest = 0;
		CrazyPacketMode = 0;
		ZeroMemory(szNoticeURL, sizeof(szNoticeURL));
		RecordAdminCommand = 0;
		FreeLevel = 0;
		ZeroMemory(szFreeGpCode, sizeof(szFreeGpCode));
		PresentLevel = 0;
		Event_ComicBirthDay = 0;
		Event_Puzzle = 0;
		Event_BabelHorn = 0;
		Event_NineFox = 0;
		EVENT_Christmas = 0;
		EventPlay_BitMask = 0;
		Event_PCBangPet = 0;
		StartUser_PresentItem = 0;
		GameGuard_Auth = 0;
		RemoveNProtectTime = 0;
		TT_DataServer_Count = 0;
		ZeroMemory(&TT_DataServer, sizeof(TT_DataServer));
		FixedStartField = 0;
		DisableThrowItem = 0;
		CheckPlayField = 0;
		Enable_PKField = -1;
		Enable_PKField_All = 0;
		CheckModelFile = 0;

#ifdef LOG_THE_PK 
		bPK_LOG = true;
#endif
	}
};


extern int	ServerMode;


class smWINSOCK;

int Serv_ConnectPlayer(smWINSOCK *lpsmSock);

int Serv_DisconnectPlayer(smWINSOCK *lpsmSock);

smCHAR *Serv_CheckOtherPlayPosi(int x, int y, int z);


#define	TOTAL_CHECK_MONEY_MAX 52000
#define	TOTAL_CHECK_EXP_MAX 500000

#define	dwFUNC_VALUE_MAX	64

struct	sFUNC_VALUE
{
	DWORD	dwFunc;
	DWORD	dwLen;
	DWORD	dwChkSum;
};

struct	TRANS_CLIENT_FUNPOS
{
	int	size, code;

	int	ClientVersion;

	DWORD	dwFunc_CheckMemSum;
	int FuncCount;

	sFUNC_VALUE	dwFuncValue[dwFUNC_VALUE_MAX];
};

struct	TRANS_FUNC_MEMORY
{
	int size, code;
	int Param[8];
	char	szData[6000];
};

struct	sCHK_POTION_COUNT
{
	int	Ps101;
	int	Ps102;
	int	Ps103;
	int	Ps104;

	int	Pm101;
	int	Pm102;
	int	Pm103;
	int	Pm104;

	int	Pl101;
	int	Pl102;
	int	Pl103;
	int	Pl104;
};


struct	sSOD_SCORE
{
	int Flag;
	DWORD	dwDispTime;
	int Score;
	int MyTeam;
	int TeamScore[4];
	int Round;
	DWORD	dwPlayTime;



	DWORD	dwSoD_NextStageTime;
	int SodNextStageNum;
	int NextRound;
	DWORD	dwSoD_CloseStageTime;


	int EffectStartCount;
	int EffectCode;


	int ScoreEffectCount;

};

#define MAX_JOBNUM 	10

#define	JOBCODE_FIGHTER 1
#define	JOBCODE_MECHANICIAN 2
#define	JOBCODE_ARCHER 3
#define	JOBCODE_PIKEMAN 4
#define	JOBCODE_ATALANTA 5
#define	JOBCODE_KNIGHT 6
#define	JOBCODE_MAGICIAN 7
#define	JOBCODE_PRIESTESS 8
#define JOBCODE_ASSASSINE 9
#define JOBCODE_SHAMAN    10

#define	CHAR_EVENT_STARPOINT 300

#define	ITEM_UNIQUE_CODE_NORMAL 1
#define	ITEM_UNIQUE_CODE_QUEST 2


#define BIMASK_PRORATE_USER 1
#define BIMASK_FREE_USER 2
#define BIMASK_VIP_USER 4
#define BIMASK_BIRTHDAY_USER 8
#define BIMASK_TIMELEVEL_USER 16
#define BIMASK_ADULT_USER 32


#define	MONSTER_CLASS_NORMAL 0
#define	MONSTER_CLASS_BOSS 1
#define	MONSTER_CLASS_HAMMER 200
#define	MONSTER_CLASS_GHOST 300

#endif