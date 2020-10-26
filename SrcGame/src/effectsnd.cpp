#include "smlib3d\\smd3d.h"
#include "smwsock.h"
#include "Settings.h"
#include "character.h"
#include "Sound\\dxwav.h"
#include "particle.h"
#include "fileread.h"
#include "playmain.h"
#include "drawsub.h"
#include "netplay.h"
#include "effectsnd.h"
#include "field.h"
#include "Language\\language.h"


extern char sangJuWav[NUM_SOUNDS][64];
extern char *sangJuWav2[NUM_SOUNDS];
extern int  sangJuWav_F[NUM_SOUNDS];

struct	snFIND_EFFECT
{
	char	*lpStringCode;
	DWORD	CharSoundCode;
};


struct	snEFFECT
{
	DWORD	RealSoundNum;
	DWORD	CharSoundCode;
	DWORD	MotionState;
	DWORD	WeaponState;
};


#define	snFIND_EFFECT_MAX			173		




snFIND_EFFECT	snFindEffects[snFIND_EFFECT_MAX] = {

	{ "game\\Audio\\Effects\\monster\\Grotesque\\",	snCHAR_SOUND_B_MUNDO},
	{ "game\\Audio\\Effects\\monster\\Tulla\\"	,	snCHAR_SOUND_B_TULLA},
	{ "game\\Audio\\Effects\\monster\\Fury\\"	,	snCHAR_SOUND_B_SHY},
	{ "game\\Audio\\Effects\\monster\\Draxos\\"	,	snCHAR_SOUND_B_DRAXOS},
	{ "game\\Audio\\Effects\\monster\\Midranda\\",	snCHAR_SOUND_B_MIDRANDA},
	{ "game\\Audio\\Effects\\monster\\Greedy\\"	,	snCHAR_SOUND_B_GREEDY},
	{ "game\\Audio\\Effects\\monster\\WLord\\"	,	snCHAR_SOUND_B_WLORD},





	{ "game\\Audio\\Effects\\monster\\cyclops\\"	,	snCHAR_SOUND_CYCLOPS	},
	{ "game\\Audio\\Effects\\monster\\hob goblin\\"	,	snCHAR_SOUND_HOBGOBLIN	},
	{ "game\\Audio\\Effects\\monster\\Imp\\"		,	snCHAR_SOUND_IMP		},
	{ "game\\Audio\\Effects\\monster\\miniG\\"		,	snCHAR_SOUND_MINIG		},
	{ "game\\Audio\\Effects\\monster\\plant\\"		,	snCHAR_SOUND_PLANT		},
	{ "game\\Audio\\Effects\\monster\\skeleton\\"	,	snCHAR_SOUND_SKELETON	},
	{ "game\\Audio\\Effects\\monster\\zombi\\"		,	snCHAR_SOUND_ZOMBI		},
	{ "game\\Audio\\Effects\\monster\\obit\\"		,	snCHAR_SOUND_OBIT		},

	{ "game\\Audio\\Effects\\monster\\hopt\\"		,	snCHAR_SOUND_HOPT		},
	{ "game\\Audio\\Effects\\monster\\bargon\\"		,	snCHAR_SOUND_BARGON		},
	{ "game\\Audio\\Effects\\monster\\leech\\"		,	snCHAR_SOUND_LEECH		},
	{ "game\\Audio\\Effects\\monster\\mushroom\\"	,	snCHAR_SOUND_MUSHROOM	},

	{ "game\\Audio\\Effects\\monster\\Arma\\"		,	snCHAR_SOUND_ARMA		},
	{ "game\\Audio\\Effects\\monster\\scorpion\\"	,	snCHAR_SOUND_SCORPION	},


	{ "game\\Audio\\Effects\\monster\\HeadCutter\\"	,	snCHAR_SOUND_HEADCUTTER	},
	{ "game\\Audio\\Effects\\monster\\Sandlem\\"	,	snCHAR_SOUND_SANDLEM	},
	{ "game\\Audio\\Effects\\monster\\Web\\"		,	snCHAR_SOUND_WEB		},
	{ "game\\Audio\\Effects\\monster\\HopyKing\\"	,	snCHAR_SOUND_HOPYKING	},
	{ "game\\Audio\\Effects\\monster\\Crip\\"		,	snCHAR_SOUND_CRIP		},
	{ "game\\Audio\\Effects\\monster\\Buma\\"		,	snCHAR_SOUND_BUMA		},
	{ "game\\Audio\\Effects\\monster\\Decoy\\"		,	snCHAR_SOUND_DECOY		},
	{ "game\\Audio\\Effects\\monster\\Doral\\"		,	snCHAR_SOUND_DORAL		},
	{ "game\\Audio\\Effects\\monster\\Figon\\"		,	snCHAR_SOUND_FIGON		},
	{ "game\\Audio\\Effects\\monster\\StoneGiant\\"	,	snCHAR_SOUND_STONEGIANT	},
	{ "game\\Audio\\Effects\\monster\\Greven\\"		,	snCHAR_SOUND_GREVEN		},
	{ "game\\Audio\\Effects\\monster\\illusionknight\\" ,snCHAR_SOUND_ILLUSIONKNIGHT },
	{ "game\\Audio\\Effects\\monster\\SkeletonRange\\"	,	snCHAR_SOUND_SKELETONRANGE},
	{ "game\\Audio\\Effects\\monster\\SkeletonMelee\\"	,	snCHAR_SOUND_SKELETONMELEE},

	{ "game\\Audio\\Effects\\monster\\wolverin\\"		,	snCHAR_SOUND_WOLVERLIN		},


	{ "game\\Audio\\Effects\\monster\\Rabie\\"		,	snCHAR_SOUND_RABIE		},
	{ "game\\Audio\\Effects\\monster\\Mudy\\"		,	snCHAR_SOUND_MUDY		},
	{ "game\\Audio\\Effects\\monster\\Sen\\"		,	snCHAR_SOUND_SEN		},
	{ "game\\Audio\\Effects\\monster\\Egan\\"		,	snCHAR_SOUND_EGAN		},
	{ "game\\Audio\\Effects\\monster\\BeeDog\\"		,	snCHAR_SOUND_BEEDOG		},
	{ "game\\Audio\\Effects\\monster\\MutantPlant\\",	snCHAR_SOUND_MUTANTPLANT},
	{ "game\\Audio\\Effects\\monster\\MutantRabie\\",	snCHAR_SOUND_MUTANTRABIE},
	{ "game\\Audio\\Effects\\monster\\MutantTree\\"	,	snCHAR_SOUND_MUTANTTREE	},
	{ "game\\Audio\\Effects\\monster\\Avelisk\\"	,	snCHAR_SOUND_AVELISK	},
	{ "game\\Audio\\Effects\\monster\\Naz\\"		,	snCHAR_SOUND_NAZ		},
	{ "game\\Audio\\Effects\\monster\\Mummy\\"		,	snCHAR_SOUND_MUMMY		},
	{ "game\\Audio\\Effects\\monster\\Hulk\\"		,	snCHAR_SOUND_HULK		},
	{ "game\\Audio\\Effects\\monster\\Hungky\\"		,	snCHAR_SOUND_HUNGKY	},
	{ "game\\Audio\\Effects\\monster\\Succubus\\"	,	snCHAR_SOUND_SUCCUBUS	},
	{ "game\\Audio\\Effects\\monster\\Dawlin\\"		,	snCHAR_SOUND_DAWLIN		},
	{ "game\\Audio\\Effects\\monster\\Shadow\\"		,	snCHAR_SOUND_SHADOW		},
	{ "game\\Audio\\Effects\\monster\\Berserker\\"	,	snCHAR_SOUND_BERSERKER	},
	{ "game\\Audio\\Effects\\monster\\IronGuard\\"	,	snCHAR_SOUND_IRONGUARD	},
	{ "game\\Audio\\Effects\\monster\\Fury\\"		,	snCHAR_SOUND_FURY		},
	{ "game\\Audio\\Effects\\monster\\Sliver\\"		,	snCHAR_SOUND_SLIVER		},

	{ "game\\Audio\\Effects\\monster\\Ratoo\\"		,	snCHAR_SOUND_RATOO		},
	{ "game\\Audio\\Effects\\monster\\Stygianlord\\",	snCHAR_SOUND_STYGIANLORD},
	{ "game\\Audio\\Effects\\monster\\Omicron\\"	,	snCHAR_SOUND_OMICRON	},
	{ "game\\Audio\\Effects\\monster\\D-Machine\\"	,	snCHAR_SOUND_DMACHINE	},
	{ "game\\Audio\\Effects\\monster\\Metron\\"		,	snCHAR_SOUND_METRON		},

	{ "game\\Audio\\Effects\\monster\\MrGhost\\"	,	snCHAR_SOUND_MRGHOST	},


	{ "game\\Audio\\Effects\\monster\\VAMPIRICBAT\\",	snCHAR_SOUND_VAMPIRICBAT	},
	{ "game\\Audio\\Effects\\monster\\MIREKEEPER\\"	,	snCHAR_SOUND_MIREKEEPER		},
	{ "game\\Audio\\Effects\\monster\\MUFFIN\\"		,	snCHAR_SOUND_MUFFIN			},
	{ "game\\Audio\\Effects\\monster\\SOLIDSNAIL\\"	,	snCHAR_SOUND_SOLIDSNAIL		},
	{ "game\\Audio\\Effects\\monster\\BEEVIL\\"		,	snCHAR_SOUND_BEEVIL			},
	{ "game\\Audio\\Effects\\monster\\NIGHTMARE\\"	,	snCHAR_SOUND_NIGHTMARE		},
	{ "game\\Audio\\Effects\\monster\\STONEGOLEM\\"	,	snCHAR_SOUND_STONEGOLEM		},
	{ "game\\Audio\\Effects\\monster\\THORNCRAWLER\\",	snCHAR_SOUND_THORNCRAWLER	},
	{ "game\\Audio\\Effects\\monster\\HEAVYGOBLIN\\",	snCHAR_SOUND_HEAVYGOBLIN	},
	{ "game\\Audio\\Effects\\monster\\EVILPLANT\\"	,	snCHAR_SOUND_EVILPLANT		},
	{ "game\\Audio\\Effects\\monster\\HAUNTINGPLANT\\",	snCHAR_SOUND_HAUNTINGPLANT	},
	{ "game\\Audio\\Effects\\monster\\DARKKNIGHT\\"	,	snCHAR_SOUND_DARKKNIGHT		},
	{ "game\\Audio\\Effects\\monster\\Guardian-Saint\\",snCHAR_SOUND_GUARDIAN_SAINT	},




	{ "game\\Audio\\Effects\\monster\\ChainGolem\\"	,	snCHAR_SOUND_CHAINGOLEM		},
	{ "game\\Audio\\Effects\\monster\\DeadZone\\"	,	snCHAR_SOUND_DEADZONE		},
	{ "game\\Audio\\Effects\\monster\\Grotesque\\"	,	snCHAR_SOUND_GROTESQUE		},
	{ "game\\Audio\\Effects\\monster\\Hypermachine\\",	snCHAR_SOUND_HYPERMACHINE	},
	{ "game\\Audio\\Effects\\monster\\IronFist\\"	,	snCHAR_SOUND_IRONFIST		},
	{ "game\\Audio\\Effects\\monster\\Morgon\\"		,	snCHAR_SOUND_MORGON			},
	{ "game\\Audio\\Effects\\monster\\Mountain\\"	,	snCHAR_SOUND_MOUNTAIN		},
	{ "game\\Audio\\Effects\\monster\\Rampage\\"	,	snCHAR_SOUND_RAMPAGE		},
	{ "game\\Audio\\Effects\\monster\\RunicGuardian\\",	snCHAR_SOUND_RUNICGUARDIAN	},
	{ "game\\Audio\\Effects\\monster\\Sadness\\"	,	snCHAR_SOUND_SADNESS		},
	{ "game\\Audio\\Effects\\monster\\TowerGolem\\"	,	snCHAR_SOUND_TOWERGOLEM		},
	{ "game\\Audio\\Effects\\monster\\VampiricBee\\",	snCHAR_SOUND_VAMPRICBEE		},
	{ "game\\Audio\\Effects\\monster\\VampiricMachine\\",snCHAR_SOUND_VAMPRICMACHINE},
	{ "game\\Audio\\Effects\\monster\\Omu\\",			snCHAR_SOUND_OMU			},

	{ "game\\Audio\\Effects\\monster\\AvelinArcher\\",	snCHAR_SOUND_AVELIN_ARCHER	},
	{ "game\\Audio\\Effects\\monster\\AvelinQueen\\",	snCHAR_SOUND_AVELIN_QUEEN	},
	{ "game\\Audio\\Effects\\monster\\Babel\\",			snCHAR_SOUND_BABEL	},


	{ "game\\Audio\\Effects\\monster\\Mystic\\",		snCHAR_SOUND_MYSTIC			},
	{ "game\\Audio\\Effects\\monster\\HEAVYGOBLIN\\",	snCHAR_SOUND_ICEGOBLIN		},
	{ "game\\Audio\\Effects\\monster\\ColdEye\\",		snCHAR_SOUND_COLDEYE		},
	{ "game\\Audio\\Effects\\monster\\Frozen\\",		snCHAR_SOUND_FROZEN			},
	{ "game\\Audio\\Effects\\monster\\STONEGOLEM\\",	snCHAR_SOUND_ICEGOLEM		},
	{ "game\\Audio\\Effects\\monster\\Frost\\",			snCHAR_SOUND_FROST			},
	{ "game\\Audio\\Effects\\monster\\ChaosCara\\",		snCHAR_SOUND_CHAOSCARA		},
	{ "game\\Audio\\Effects\\monster\\DeathKnight\\",	snCHAR_SOUND_DEATHKNIGHT	},


	{ "game\\Audio\\Effects\\monster\\GreateGreven\\",	snCHAR_SOUND_GREATE_GREVEN	},
	{ "game\\Audio\\Effects\\monster\\LizardFolk\\",	snCHAR_SOUND_LIZARDFOLK		},
	{ "game\\Audio\\Effects\\monster\\M_Lord\\",		snCHAR_SOUND_M_LORD			},
	{ "game\\Audio\\Effects\\monster\\Spider\\",		snCHAR_SOUND_SPIDER			},
	{ "game\\Audio\\Effects\\monster\\Stingray\\",		snCHAR_SOUND_STINGRAY		},
	{ "game\\Audio\\Effects\\monster\\Strider\\",		snCHAR_SOUND_STRIDER		},


	{ "game\\Audio\\Effects\\monster\\TurtleCannon\\",	snCHAR_SOUND_TURTLE_CANNON	},
	{ "game\\Audio\\Effects\\monster\\DevilBird\\",		snCHAR_SOUND_DEVIL_BIRD		},
	{ "game\\Audio\\Effects\\monster\\BlizzardGiant\\",	snCHAR_SOUND_BLIZZARD_GIANT	},
	{ "game\\Audio\\Effects\\monster\\Kelvezu\\",		snCHAR_SOUND_KELVEZU		},


	{ "game\\Audio\\Effects\\monster\\DarkPhalanx\\",	snCHAR_SOUND_DARKPHALANX	},
	{ "game\\Audio\\Effects\\monster\\BloodyKnight\\",	snCHAR_SOUND_BLOODYKNIGHT	},
	{ "game\\Audio\\Effects\\monster\\Chimera\\",		snCHAR_SOUND_CHIMERA		},
	{ "game\\Audio\\Effects\\monster\\FireWorm\\",		snCHAR_SOUND_FIREWORM		},
	{ "game\\Audio\\Effects\\monster\\HellHound\\",		snCHAR_SOUND_HELLHOUND		},
	{ "game\\Audio\\Effects\\monster\\DarkGuard\\",		snCHAR_SOUND_DARKGUARD		},
	{ "game\\Audio\\Effects\\monster\\DarkMage\\",		snCHAR_SOUND_DARKMAGE		},

	{ "game\\Audio\\Effects\\monster\\MonMokova\\",		snCHAR_SOUND_MOKOVA			},
	{ "game\\Audio\\Effects\\monster\\MonTempleguard\\",snCHAR_SOUND_TEMPLEGUARD	},
	{ "game\\Audio\\Effects\\monster\\MonSeto\\",		snCHAR_SOUND_SETO			},
	{ "game\\Audio\\Effects\\monster\\MonKingSpider\\",	snCHAR_SOUND_KINGSPIDER		},


	{ "game\\Audio\\Effects\\monster\\d_kn\\",			snCHAR_SOUND_REVIVED_KNIGHT	},
	{ "game\\Audio\\Effects\\monster\\d_magi\\",		snCHAR_SOUND_REVIVED_MAGICIAN },
	{ "game\\Audio\\Effects\\monster\\d_atal\\",		snCHAR_SOUND_REVIVED_ATALANTA },
	{ "game\\Audio\\Effects\\monster\\d_fi\\",			snCHAR_SOUND_REVIVED_FIGTHER },
	{ "game\\Audio\\Effects\\monster\\d_ar\\",			snCHAR_SOUND_REVIVED_ARCHER	},
	{ "game\\Audio\\Effects\\monster\\d_meca\\",		snCHAR_SOUND_REVIVED_MECANICIAN },
	{ "game\\Audio\\Effects\\monster\\d_pa\\",			snCHAR_SOUND_REVIVED_PIKEMAN },
	{ "game\\Audio\\Effects\\monster\\d_pr\\",			snCHAR_SOUND_REVIVED_PRIESTESS },
	{ "game\\Audio\\Effects\\monster\\deadhopt\\",		snCHAR_SOUND_DEADHOPT },
	{ "game\\Audio\\Effects\\monster\\deadkinghopy\\",	snCHAR_SOUND_DEADKINGHOPY },
	{ "game\\Audio\\Effects\\monster\\gorgon\\",		snCHAR_SOUND_GORGON},
	{ "game\\Audio\\Effects\\monster\\hobogolem\\",		snCHAR_SOUND_HOBOGOLEM},


	{ "game\\Audio\\Effects\\monster\\Niken\\",			snCHAR_SOUND_NIKEN			},
	{ "game\\Audio\\Effects\\monster\\Mimic\\",			snCHAR_SOUND_MIMIC			},
	{ "game\\Audio\\Effects\\monster\\KingBat\\",		snCHAR_SOUND_KINGBAT		},
	{ "game\\Audio\\Effects\\monster\\GoblinShaman\\",	snCHAR_SOUND_GOBLINSHAMAN	},
	{ "game\\Audio\\Effects\\monster\\Hest\\",			snCHAR_SOUND_HEST			},


	{ "game\\Audio\\Effects\\monster\\Ruca\\",			snCHAR_SOUND_RUCA			},
	{ "game\\Audio\\Effects\\monster\\NazSenior\\",		snCHAR_SOUND_NAZSENIOR		},
	{ "game\\Audio\\Effects\\monster\\Igolation\\",		snCHAR_SOUND_IGOLATION		},
	{ "game\\Audio\\Effects\\monster\\Kakoa\\",			snCHAR_SOUND_KAKOA			},
	{ "game\\Audio\\Effects\\monster\\Sprin\\",			snCHAR_SOUND_SPRIN			},
	{ "game\\Audio\\Effects\\monster\\UndeadMaple\\",	snCHAR_SOUND_UNDEADMAPLE	},
	{ "game\\Audio\\Effects\\monster\\Xetan\\",			snCHAR_SOUND_XETAN			},



	{ "game\\Audio\\Effects\\monster\\Bebechick\\",			snCHAR_SOUND_BEBECHICK		},
	{ "game\\Audio\\Effects\\monster\\PaPachick\\",			snCHAR_SOUND_PAPACHICK		},


	{ "game\\Audio\\Effects\\npc\\morif\\",				snCHAR_SOUND_NPC_MORIF	},
	{ "game\\Audio\\Effects\\npc\\mollywolf\\",			snCHAR_SOUND_NPC_MOLLYWOLF	},
	{ "game\\Audio\\Effects\\npc\\SkillMaster\\",		snCHAR_SOUND_NPC_SKILLMASTER	},
	{ "game\\Audio\\Effects\\npc\\MagicMaster\\",		snCHAR_SOUND_NPC_MAGICMASTER	},
	{ "game\\Audio\\Effects\\npc\\worldcup\\",			snCHAR_SOUND_WORLDCUP		},


	{ "game\\Audio\\Effects\\npc\\castledoor\\",	snCHAR_SOUND_CASTLE_DOOR		},
	{ "game\\Audio\\Effects\\npc\\crystal_r\\",		snCHAR_SOUND_CASTLE_CRYSTAL_R	},
	{ "game\\Audio\\Effects\\npc\\crystal_g\\",		snCHAR_SOUND_CASTLE_CRYSTAL_G	},
	{ "game\\Audio\\Effects\\npc\\crystal_b\\",		snCHAR_SOUND_CASTLE_CRYSTAL_B	},
	{ "game\\Audio\\Effects\\npc\\crystal_n\\",		snCHAR_SOUND_CASTLE_CRYSTAL_N	},
	{ "game\\Audio\\Effects\\npc\\tower-b\\",		snCHAR_SOUND_CASTLE_TOWER_B		},

	{ "game\\Audio\\Effects\\npc\\Soldier_A\\",		snCHAR_SOUND_CASTLE_SOLDER_A	},
	{ "game\\Audio\\Effects\\npc\\Soldier_B\\",		snCHAR_SOUND_CASTLE_SOLDER_B	},
	{ "game\\Audio\\Effects\\npc\\Soldier_C\\",		snCHAR_SOUND_CASTLE_SOLDER_C	},



	{ "game\\Audio\\Effects\\monster\\wolverin\\"		,	snCHAR_SOUND_S_WOLVERLIN	},
	{ "game\\Audio\\Effects\\monster\\MetalGolem\\"		,	snCHAR_SOUND_S_METALGOLEM	},
	{ "game\\Audio\\Effects\\monster\\Figon\\"			,	snCHAR_SOUND_S_F_ELEMENTAL	},



	{ "game\\Audio\\Effects\\player\\fighter\\"		,	snCHAR_SOUND_FIGHTER	},
	{ "game\\Audio\\Effects\\player\\Mechanician\\"	,	snCHAR_SOUND_MECHANICAN	},
	{ "game\\Audio\\Effects\\player\\archer\\"		,	snCHAR_SOUND_ARCHER		},
	{ "game\\Audio\\Effects\\player\\pikeman\\"		,	snCHAR_SOUND_PIKEMAN	},


	{ "game\\Audio\\Effects\\player\\Knight\\"		,	snCHAR_SOUND_KNIGHT		},
	{ "game\\Audio\\Effects\\player\\Atalanta\\"	,	snCHAR_SOUND_ATALANTA	},
	{ "game\\Audio\\Effects\\player\\Priestess\\"	,	snCHAR_SOUND_PRIESTESS	},
	{ "game\\Audio\\Effects\\player\\Magician\\"	,	snCHAR_SOUND_MAGICIAN	},


	{ "game\\Audio\\Effects\\monster\\Watermelon\\",	snCHAR_SOUND_WATERMELON	}

};








char *szSndWeaponPath = "game\\Audio\\Effects\\weapon\\";

#define	snFIND_EFFECT_MOTION_MAX	9
#define	snFIND_EFFECT_WEAPON_MAX	18

snFIND_EFFECT	snFindEffectsMotion[snFIND_EFFECT_MOTION_MAX] =
{
	{	"attack"		,		CHRMOTION_STATE_ATTACK	},
	{	"damage"		,		CHRMOTION_STATE_DAMAGE	},
	{	"dead"			,		CHRMOTION_STATE_DEAD	},
	{	"neutral"		,		CHRMOTION_STATE_STAND	},
	{	"move"			,		CHRMOTION_STATE_WALK	},
	{	"disappear"		,		CHRMOTION_STATE_WARP	},
	{	"change"		,		CHRMOTION_STATE_WARP	},
	{	"skill"			,		CHRMOTION_STATE_SKILL	},
	{	"hammer"		,		CHRMOTION_STATE_HAMMER	}
};

snFIND_EFFECT	snFindEffectsWeapon[snFIND_EFFECT_WEAPON_MAX] =
{
	{	"one hand swing axe"		,		1	},
	{	"two hand swing axe"		,		2	},
	{	"one hand swing sword"		,		3	},
	{	"two hand swing sword"		,		4	},
	{	"one hand swing spear"		,		5	},
	{	"two hand swing spear"		,		6	},

	{	"one hand scratch"			,		7	},
	{	"bow shoot"					,		8	},
	{	"one hand swing blunt"		,		9	},
	{	"two hand swing blunt"		,		10	},
	{	"throwing"					,		11	},
	{	"one hand miss"				,		12	},
	{	"two hand miss"				,		13	},
	{	"punch hit"					,		14	},
	{	"one hand small swing"		,		15	},
	{	"critical hit"				,		16	},

	{	"one hand casting"			,		17	},
	{	"two hand casting"			,		18	}
};




int	CompareHeadString(char *szCodeString, char *szString)
{
	int cnt;
	int	len;
	char ch;

	len = lstrlen(szCodeString);

	for(cnt = 0; cnt < len; cnt++)
	{
		ch = szString[cnt];
		if(ch == 0) return FALSE;
		if(szCodeString[cnt] != ch)
		{
			if(ch<'A' && ch>'Z')	return FALSE;
			if(szCodeString[cnt] != (ch + 0x20))
				return FALSE;
		}
	}

	return TRUE;
}

DWORD FindMotionState(char *szFile)
{
	int cnt;

	for(cnt = 0; cnt < snFIND_EFFECT_MOTION_MAX; cnt++)
	{
		if(CompareHeadString(snFindEffectsMotion[cnt].lpStringCode, szFile) == TRUE)
		{
			return snFindEffectsMotion[cnt].CharSoundCode;
		}
	}

	return NULL;
}

DWORD FindWeaponState(char *szFile)
{
	int cnt;

	for(cnt = 0; cnt < snFIND_EFFECT_WEAPON_MAX; cnt++)
	{
		if(CompareHeadString(snFindEffectsWeapon[cnt].lpStringCode, szFile) == TRUE)
		{
			return snFindEffectsWeapon[cnt].CharSoundCode;
		}
	}

	return NULL;
}


#define snEFFECT_MAX	1300

int	LoadSoundNum;

snEFFECT	snEffect[snEFFECT_MAX];
int	snEffectCnt;

snEFFECT	snEffectWeapon[snEFFECT_MAX];
int	snEffectWeaponCnt;



int sinSoundNum = 0;
extern char *sinSoundWav[];


char *esSoundWav[] = {
	"game\\Audio\\Effects\\FootSteps\\step01.wav",
	"game\\Audio\\Effects\\FootSteps\\step02.wav",
	"game\\Audio\\Effects\\FootSteps\\stonerun1.wav",
	"game\\Audio\\Effects\\FootSteps\\stonerun2.wav",
	"game\\Audio\\Effects\\FootSteps\\stonerun3.wav",
	"game\\Audio\\Ambient\\stone-mill.wav",
	"game\\Audio\\Effects\\event\\fieldstart.wav",
	"game\\Audio\\Effects\\event\\level UP.wav",
	"game\\Audio\\Effects\\event\\hosound.wav",
	"game\\Audio\\Ambient\\tempskron-town.wav",

	"game\\Audio\\Effects\\monster\\Figon\\impact 1.wav",
	"game\\Audio\\Effects\\FootSteps\\stone-dun1.wav",
	"game\\Audio\\Effects\\FootSteps\\stone-dun2.wav",
	"game\\Audio\\Effects\\FootSteps\\stone-dun3.wav",

	"game\\Audio\\Effects\\FootSteps\\inwater 1.wav",
	"game\\Audio\\Effects\\FootSteps\\inwater 2.wav",
	"game\\Audio\\Effects\\FootSteps\\inwater 3.wav",

	"game\\Audio\\Effects\\FootSteps\\inwater 3.wav",
	"game\\Audio\\Sod\\turn.wav",

	"game\\Audio\\Sod\\SOD-item.wav",

	"game\\Audio\\Effects\\Menu\\Event\\meteo 1.wav",
	"game\\Audio\\Effects\\Menu\\Event\\meteo 2.wav",
	"game\\Audio\\Effects\\Event\\sheltom_b.wav",
	"game\\Audio\\Effects\\Event\\firecracker01.wav",
	"game\\Audio\\Effects\\Event\\firecracker02.wav",
	"game\\Audio\\Effects\\Event\\firecracker03.wav",

	0
};


int esSoundNum = 0;


#define	AMBIENT_SOUND_NUM		9
#define	AMBIENT_SOUND_NUM2		5
#define	CONTINUE_SOUND_NUM		17

int	AmbientSound = -1;
int	AmbientSound2 = -1;
int	AmbientSoundNum = 0;
int	AmbientSoundNum2 = 0;
int	ContinueSoundNum = 0;
int	AmbientObjectSound = 0;

int	ContSoundCount = 0;


char *szAmbientSound[] = {
	"game\\Audio\\Ambient\\tempskron-town.wav",
	"game\\Audio\\Ambient\\forest-day.wav",
	"game\\Audio\\Ambient\\forest-night.wav",
	"game\\Audio\\Ambient\\ruin wind.wav",
	"game\\Audio\\Ambient\\desert wind.wav",
	"game\\Audio\\Ambient\\dungeon.wav",

	"game\\Audio\\Ambient\\temple_amb.wav",
	"game\\Audio\\Ambient\\cave_amb.wav",
	"game\\Audio\\Ambient\\darksanc_amb.wav",

	"game\\Audio\\Ambient\\iron_amb.wav",
	"game\\Audio\\Ambient\\iron_amb2.wav",
	"game\\Audio\\Ambient\\Babel Approach.wav",
	"game\\Audio\\Ambient\\icewind.wav",

	0
};

struct	sSKILL_SOUND_FILE
{
	char	*szFile;
	DWORD	dwCode;
};

int	SkillSoundNum = 0;

sSKILL_SOUND_FILE	SkillSoundWav[] = {
	{	"game\\Audio\\Effects\\Skill\\Learn_Skill.wav",							SKILL_SOUND_LEARN	},

	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Extreme_Shield 01.wav",		SKILL_SOUND_EXTREME_SHIELD	},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Jumping_Crash 01.wav",			SKILL_SOUND_JUMPING_CRASH1	},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Jumping_Crash 02.wav",			SKILL_SOUND_JUMPING_CRASH2	},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Mechanic_Bomb 01.wav",			SKILL_SOUND_MECHANIC_BOMB1	},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Mechanic_Bomb 02.wav",			SKILL_SOUND_MECHANIC_BOMB2	},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Perfect Aim 01.wav",			SKILL_SOUND_PERFECT_AIM	},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Physical_Absorption 01.wav",	SKILL_SOUND_PHYSICAL_ABSORB1	},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Physical_Absorption 02.wav",	SKILL_SOUND_PHYSICAL_ABSORB2	},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Physical_Absorption 03.wav",	SKILL_SOUND_PHYSICAL_ABSORB3	},

	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Pike_Wind 01.wav",				SKILL_SOUND_PIKE_WIND	},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Scout_Hawk 01.wav",			SKILL_SOUND_SCOUT_HAWK1	},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Scout_Hawk 02.wav",			SKILL_SOUND_SCOUT_HAWK2	},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Wind_Arrow 01.wav",			SKILL_SOUND_WIND_ARROW	},

	{	"game\\Audio\\Effects\\Skill\\bow_skill_hit 01.wav",					SKILL_SOUND_ARROW_HIT1 },
	{	"game\\Audio\\Effects\\Skill\\bow_skill_hit 02.wav",					SKILL_SOUND_ARROW_HIT2 },

	{	"game\\Audio\\Effects\\Skill\\Skill_Swing 01.wav",						SKILL_SOUND_SKILL_SWING1 },
	{	"game\\Audio\\Effects\\Skill\\Skill_Swing 02.wav",						SKILL_SOUND_SKILL_SWING2 },

	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Automation 01.wav",			SKILL_SOUND_SKILL_AUTOMATION1 },
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Automation 02.wav",			SKILL_SOUND_SKILL_AUTOMATION2 },
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Automation 03.wav",			SKILL_SOUND_SKILL_AUTOMATION3 },

	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Maximize 01.wav",				SKILL_SOUND_SKILL_MAXIMIZE1 },
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Maximize 01.wav",				SKILL_SOUND_SKILL_MAXIMIZE2 },
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Maximize 01.wav",				SKILL_SOUND_SKILL_MAXIMIZE3 },

	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Spark 01.wav",					SKILL_SOUND_SKILL_SPARK1 },
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Spark 02.wav",					SKILL_SOUND_SKILL_SPARK2 },
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Spark 03.wav",					SKILL_SOUND_SKILL_SPARK3 },

	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Ground Pike 01.wav",			SKILL_SOUND_SKILL_GROUND_PIKE },
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Tornado 01.wav",				SKILL_SOUND_SKILL_TORNADO1 },

	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Falcon 02.wav",				SKILL_SOUND_SKILL_FALCON },
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Falcon Attack 01.wav",			SKILL_SOUND_SKILL_FALCON_ATTACK1 },
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Falcon Attack 02.wav",			SKILL_SOUND_SKILL_FALCON_ATTACK2 },

	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Avalanche 01.wav",				SKILL_SOUND_SKILL_AVALANCHE1 },
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Avalanche 02.wav",				SKILL_SOUND_SKILL_AVALANCHE2 },
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Avalanche 03.wav",				SKILL_SOUND_SKILL_AVALANCHE3 },

	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Expansion 01.wav",				SKILL_SOUND_SKILL_EXPANSION1 },
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Expansion 02.wav",				SKILL_SOUND_SKILL_EXPANSION2 },

	{	"game\\Audio\\Effects\\Skill\\Tempskron\\RoZ 01.wav",					SKILL_SOUND_SKILL_RAGE_OF_ZECRAM1 },
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\RoZ 02.wav",					SKILL_SOUND_SKILL_RAGE_OF_ZECRAM2 },
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\RoZ 04.wav",					SKILL_SOUND_SKILL_RAGE_OF_ZECRAM3 },


	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Roar 01.wav",					SKILL_SOUND_SKILL_ROAR1 },
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Roar 02.wav",					SKILL_SOUND_SKILL_ROAR2 },

	{	"game\\Audio\\Effects\\Skill\\Tempskron\\AofR 01.wav",					SKILL_SOUND_SKILL_ARROW_OF_RANGE },


	{	"game\\Audio\\Effects\\Skill\\Morion\\Casting_M.wav",					SKILL_SOUND_SKILL_CASTING_MAGICIAN },
	{	"game\\Audio\\Effects\\Skill\\Morion\\Casting_P.wav",					SKILL_SOUND_SKILL_CASTING_PRIEST },

	{	"game\\Audio\\Effects\\Skill\\Morion\\Agony 1.wav",						SKILL_SOUND_SKILL_AGONY },
	{	"game\\Audio\\Effects\\Skill\\Morion\\Farina 1.wav",					SKILL_SOUND_SKILL_FARINA },
	{	"game\\Audio\\Effects\\Skill\\Morion\\FireBall 1.wav",					SKILL_SOUND_SKILL_FIREBALL1 },
	{	"game\\Audio\\Effects\\Skill\\Morion\\FireBall 2.wav",					SKILL_SOUND_SKILL_FIREBALL2 },
	{	"game\\Audio\\Effects\\Skill\\Morion\\FireBolt 1.wav",					SKILL_SOUND_SKILL_FIREBOLT1 },
	{	"game\\Audio\\Effects\\Skill\\Morion\\FireBolt 2.wav",					SKILL_SOUND_SKILL_FIREBOLT2 },

	{	"game\\Audio\\Effects\\Skill\\Morion\\Healing 1.wav",					SKILL_SOUND_SKILL_HEALING },
	{	"game\\Audio\\Effects\\Skill\\Morion\\HolyBody 1.wav",					SKILL_SOUND_SKILL_HOLYBODY },
	{	"game\\Audio\\Effects\\Skill\\Morion\\HolyBolt 1.wav",					SKILL_SOUND_SKILL_HOLYBOLT },
	{	"game\\Audio\\Effects\\Skill\\Morion\\HolyMind 1.wav",					SKILL_SOUND_SKILL_HOLYMIND },
	{	"game\\Audio\\Effects\\Skill\\Morion\\MultiSpark 1.wav",				SKILL_SOUND_SKILL_MULTISPARK },
	{	"game\\Audio\\Effects\\Skill\\Morion\\ShieldSpake 1.wav",				SKILL_SOUND_SKILL_SHIELDSTRIKE },
	{	"game\\Audio\\Effects\\Skill\\Morion\\SwordBlast 1.wav",				SKILL_SOUND_SKILL_SWORDBLAST1 },
	{	"game\\Audio\\Effects\\Skill\\Morion\\SwordBlast 2.wav",				SKILL_SOUND_SKILL_SWORDBLAST2 },
	{	"game\\Audio\\Effects\\Skill\\Morion\\VigorSpear 1.wav",				SKILL_SOUND_SKILL_VIGORSPEAR },
	{	"game\\Audio\\Effects\\Skill\\Morion\\Zenith 1.wav",					SKILL_SOUND_SKILL_ZENITH },



	{	"game\\Audio\\Effects\\Skill\\Morion\\HolyValor 1.wav",					SKILL_SOUND_SKILL_HOLY_VALOR1 },

	{	"game\\Audio\\Effects\\Skill\\Morion\\HolyValor 3.wav",					SKILL_SOUND_SKILL_HOLY_VALOR3 },


	{	"game\\Audio\\Effects\\Skill\\Morion\\Brandish 1.wav",					SKILL_SOUND_SKILL_BLANDISH1 },

	{	"game\\Audio\\Effects\\Skill\\Morion\\Brandish 2.wav",					SKILL_SOUND_SKILL_BLANDISH2 },


	{	"game\\Audio\\Effects\\Skill\\Morion\\Piercing 2.wav",					SKILL_SOUND_SKILL_PIERCING },


	{	"game\\Audio\\Effects\\Skill\\Morion\\DrasticSpirit 1.wav",				SKILL_SOUND_SKILL_DRASTICSPIRIT1 },

	{	"game\\Audio\\Effects\\Skill\\Morion\\DrasticSpirit 3.wav",				SKILL_SOUND_SKILL_DRASTICSPIRIT3 },




	{	"game\\Audio\\Effects\\Skill\\Morion\\Windy 1.wav",						SKILL_SOUND_SKILL_WINDY1 },

	{	"game\\Audio\\Effects\\Skill\\Morion\\Windy 3.wav",						SKILL_SOUND_SKILL_WINDY3 },


	{	"game\\Audio\\Effects\\Skill\\Morion\\TwistJavelin.wav",				SKILL_SOUND_SKILL_TWISTJAVELIN },


	{	"game\\Audio\\Effects\\Skill\\Morion\\SoulSucker 2.wav",				SKILL_SOUND_SKILL_SOULSUCKER2 },

	{	"game\\Audio\\Effects\\Skill\\Morion\\SoulSucker 3.wav",				SKILL_SOUND_SKILL_SOULSUCKER3 },

	{	"game\\Audio\\Effects\\Skill\\Morion\\SoulSucker 4.wav",				SKILL_SOUND_SKILL_SOULSUCKER4 },

	{	"game\\Audio\\Effects\\Skill\\Morion\\FireJavelin 1.wav",				SKILL_SOUND_SKILL_FIREJAVELIN },


	{	"game\\Audio\\Effects\\Skill\\Morion\\DivineLightning 1.wav",			SKILL_SOUND_SKILL_DIVINELIGHTNING1 },
	{	"game\\Audio\\Effects\\Skill\\Morion\\DivineLightning 2.wav",			SKILL_SOUND_SKILL_DIVINELIGHTNING2 },
	{	"game\\Audio\\Effects\\Skill\\Morion\\DivineLightning 3.wav",			SKILL_SOUND_SKILL_DIVINELIGHTNING3 },


	{	"game\\Audio\\Effects\\Skill\\Morion\\HolyReflection 1.wav",			SKILL_SOUND_SKILL_HOLYREFLECTION1 },

	{	"game\\Audio\\Effects\\Skill\\Morion\\HolyReflection 2.wav",			SKILL_SOUND_SKILL_HOLYREFLECTION2 },

	{	"game\\Audio\\Effects\\Skill\\Morion\\GrandHealing 1.wav",				SKILL_SOUND_SKILL_GRANDHEALING },


	{	"game\\Audio\\Effects\\Skill\\Morion\\Watornado 1.wav",					SKILL_SOUND_SKILL_WATORNADO1 },
	{	"game\\Audio\\Effects\\Skill\\Morion\\Watornado 2.wav",					SKILL_SOUND_SKILL_WATORNADO2 },



	{	"game\\Audio\\Effects\\Skill\\Morion\\EnchantWpn_add_C 1.wav",			SKILL_SOUND_SKILL_ENCHANTWEAPON_ICE1  },
	{	"game\\Audio\\Effects\\Skill\\Morion\\EnchantWpn_add_C 2.wav",			SKILL_SOUND_SKILL_ENCHANTWEAPON_ICE2 },

	{	"game\\Audio\\Effects\\Skill\\Morion\\EnchantWpn_add_F 1.wav",			SKILL_SOUND_SKILL_ENCHANTWEAPON_FIRE1  },
	{	"game\\Audio\\Effects\\Skill\\Morion\\EnchantWpn_add_F 2.wav",			SKILL_SOUND_SKILL_ENCHANTWEAPON_FIRE2  },

	{	"game\\Audio\\Effects\\Skill\\Morion\\EnchantWpn_add_L 1.wav",			SKILL_SOUND_SKILL_ENCHANTWEAPON_LIGHTNING1  },
	{	"game\\Audio\\Effects\\Skill\\Morion\\EnchantWpn_add_L 2.wav",			SKILL_SOUND_SKILL_ENCHANTWEAPON_LIGHTNING2  },

	{	"game\\Audio\\Effects\\Skill\\Morion\\EnchantWpn_cast.wav",				SKILL_SOUND_SKILL_ENCHANTWEAPON_CAST  },


	{	"game\\Audio\\Effects\\Skill\\Morion\\EnchantWpn_magic_L 1.wav",		SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_LIGHTNING1  },
	{	"game\\Audio\\Effects\\Skill\\Morion\\EnchantWpn_magic_L 2.wav",		SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_LIGHTNING2 },


	{	"game\\Audio\\Effects\\Skill\\Morion\\EnchantWpn_magic_C 1.wav",		SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_ICE1  },
	{	"game\\Audio\\Effects\\Skill\\Morion\\EnchantWpn_magic_C 2.wav",		SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_ICE2  },


	{	"game\\Audio\\Effects\\Skill\\Morion\\DeathRay 1.wav",					SKILL_SOUND_SKILL_DEATHRAY },




	{	"game\\Audio\\Effects\\Skill\\Tempskron\\AvengingCrash 01.wav",			SKILL_SOUND_SKILL_AVANGING_CRASH	},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\ElementalShot 01.wav",			SKILL_SOUND_SKILL_ELEMENTAL_SHOT	},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\BombShot 01.wav",				SKILL_SOUND_SKILL_BOMB_SHOT1		},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\BombShot 02.wav",				SKILL_SOUND_SKILL_BOMB_SHOT2		},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\BoneCrash 01.wav",				SKILL_SOUND_SKILL_BONE_CRASH1		},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\ChainLance 01.wav",			SKILL_SOUND_SKILL_CHAIN_LANCE1		},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\ChainLance 02.wav",			SKILL_SOUND_SKILL_CHAIN_LANCE2		},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\ChainLance 03.wav",			SKILL_SOUND_SKILL_CHAIN_LANCE3		},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Concentration 01.wav",			SKILL_SOUND_SKILL_CONCENTRATION1	},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Concentration 02.wav",			SKILL_SOUND_SKILL_CONCENTRATION2	},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\GoldFalcon 02.wav",			SKILL_SOUND_SKILL_GOLDEN_FALCON		},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\MetalArmor 01.wav",			SKILL_SOUND_SKILL_METAL_ARMOR		},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Perforation 01.wav",			SKILL_SOUND_SKILL_PERFORATION		},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\SparkShield 02.wav",			SKILL_SOUND_SKILL_SPARK_SHIELD		},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\SwiftAxe 01.wav",				SKILL_SOUND_SKILL_SWIFT_AXE1		},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\SwiftAxe 02.wav",				SKILL_SOUND_SKILL_SWIFT_AXE2		},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\VenomSpear 01.wav",			SKILL_SOUND_SKILL_VENOM_SPEAR1		},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\VenomSpear 02.wav",			SKILL_SOUND_SKILL_VENOM_SPEAR2		},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\vanish 01.wav",				SKILL_SOUND_SKILL_VANISH1			},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\vanish 02.wav",				SKILL_SOUND_SKILL_VANISH2			},



	{	"game\\Audio\\Effects\\Skill\\Morion\\DancingSword 1.wav",				SKILL_SOUND_SKILL_DANCING_SWORD		},
	{	"game\\Audio\\Effects\\Skill\\Morion\\DancingSword_atk_1.wav",			SKILL_SOUND_SKILL_DANCING_SWORD_ATK1},
	{	"game\\Audio\\Effects\\Skill\\Morion\\DancingSword_atk_2.wav",			SKILL_SOUND_SKILL_DANCING_SWORD_ATK2},
	{	"game\\Audio\\Effects\\Skill\\Morion\\Diastrophism 2.wav",				SKILL_SOUND_SKILL_DIASTROPHISM		},
	{	"game\\Audio\\Effects\\Skill\\Morion\\DivineInhalation 1.wav",			SKILL_SOUND_SKILL_DIVINE_INHALATION	},
	{	"game\\Audio\\Effects\\Skill\\Morion\\EnergyShield 1.wav",				SKILL_SOUND_SKILL_ENERGY_SHIELD		},
	{	"game\\Audio\\Effects\\Skill\\Morion\\Extinct 1.wav",					SKILL_SOUND_SKILL_EXTINTION			},
	{	"game\\Audio\\Effects\\Skill\\Morion\\FlameBrandish 2.wav",				SKILL_SOUND_SKILL_FLAME_BRANDISH	},
	{	"game\\Audio\\Effects\\Skill\\Morion\\GrandCross 2.wav",				SKILL_SOUND_SKILL_GRAND_CROSS		},
	{	"game\\Audio\\Effects\\Skill\\Morion\\Holy Incantation 1.wav",			SKILL_SOUND_SKILL_HOLY_INCANTATION	},
	{	"game\\Audio\\Effects\\Skill\\Morion\\LightningJavelin 1.wav",			SKILL_SOUND_SKILL_LIGHTNING_JAVELIN1},
	{	"game\\Audio\\Effects\\Skill\\Morion\\LightningJavelin 2.wav",			SKILL_SOUND_SKILL_LIGHTNING_JAVELIN2},
	{	"game\\Audio\\Effects\\Skill\\Morion\\Resurrection 2.wav",				SKILL_SOUND_SKILL_RESURRECTION		},
	{	"game\\Audio\\Effects\\Skill\\Morion\\SpiritElemental 1.wav",			SKILL_SOUND_SKILL_SPIRIT_ELEMENTAL	},
	{	"game\\Audio\\Effects\\Skill\\Morion\\SplitJavelin 1.wav",				SKILL_SOUND_SKILL_SPLIT_JAVELIN1	},
	{	"game\\Audio\\Effects\\Skill\\Morion\\SplitJavelin 2.wav",				SKILL_SOUND_SKILL_SPLIT_JAVELIN2	},
	{	"game\\Audio\\Effects\\Skill\\Morion\\StormJavelin 1.wav",				SKILL_SOUND_SKILL_STORM_JAVELIN1	},
	{	"game\\Audio\\Effects\\Skill\\Morion\\StormJavelin 2.wav",				SKILL_SOUND_SKILL_STORM_JAVELIN2	},
	{	"game\\Audio\\Effects\\Skill\\Morion\\TriumphofValhalla 1.wav",			SKILL_SOUND_SKILL_TRIUMPH_OF_VALHALLA1	},
	{	"game\\Audio\\Effects\\Skill\\Morion\\TriumphofValhalla 3.wav",			SKILL_SOUND_SKILL_TRIUMPH_OF_VALHALLA2  },
	{	"game\\Audio\\Effects\\Skill\\Morion\\VigorBall 1.wav",					SKILL_SOUND_SKILL_VIGOR_BALL1		},
	{	"game\\Audio\\Effects\\Skill\\Morion\\VigorBall 2.wav",					SKILL_SOUND_SKILL_VIGOR_BALL2		},
	{	"game\\Audio\\Effects\\Skill\\Morion\\VirtualLife 1.wav",				SKILL_SOUND_SKILL_VIRTUAL_LIFE		},



	{	"game\\Audio\\Effects\\Skill\\Tempskron\\AssassinEye 01.wav",			SKILL_SOUND_SKILL_ASSASSIN_EYE		},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Berserker 01.wav",				SKILL_SOUND_SKILL_BERSERKER			},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Charging 01.wav",				SKILL_SOUND_SKILL_CHARGING			},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\ChargingStrike 03.wav",		SKILL_SOUND_SKILL_CHARGING_STRIKE	},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Compulsion 01.wav",			SKILL_SOUND_SKILL_COMPULSION1		},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Compulsion 05.wav",			SKILL_SOUND_SKILL_COMPULSION2		},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\Compulsion 06.wav",			SKILL_SOUND_SKILL_COMPULSION3		},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\CycloneStrike 01.wav",			SKILL_SOUND_SKILL_CYCLONE_STRIKE	},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\ForceOfNature 01.wav",			SKILL_SOUND_SKILL_FORCE_OF_NATURE	},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\GodsBless 01.wav",				SKILL_SOUND_SKILL_GODS_BLESS		},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\GodlyShield 01.wav",			SKILL_SOUND_SKILL_GODLY_SHIELD		},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\impulsion 02.wav",				SKILL_SOUND_SKILL_IMPULSION			},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\MetalGolem 01.wav",			SKILL_SOUND_SKILL_METAL_GOLEM		},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\PhoenixShot 01.wav",			SKILL_SOUND_SKILL_PHOENIX_SHOT		},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\ReCallWolverin 01.wav",		SKILL_SOUND_SKILL_RECALL_WOLVERIN	},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\ShadowStrike 01.wav",			SKILL_SOUND_SKILL_SHADOW_STRIKE1	},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\ShadowStrike 02.wav",			SKILL_SOUND_SKILL_SHADOW_STRIKE2	},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\ShadowStrike 03.wav",			SKILL_SOUND_SKILL_SHADOW_STRIKE3	},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\ShadowStrikeFinish 01.wav",	SKILL_SOUND_SKILL_SHADOW_STRIKE4	},
	{	"game\\Audio\\Effects\\Skill\\Tempskron\\vague 01.wav",					SKILL_SOUND_SKILL_VAGUE				},
	{   "game\\Audio\\Effects\\Skill\\Tempskron\\ViolenceStep 01.wav",			SKILL_SOUND_V_STAB },


	{	"game\\Audio\\Effects\\Skill\\Morion\\ChainLightning 01.wav",			SKILL_SOUND_SKILL_CHAIN_LIGHTNING1	},
	{	"game\\Audio\\Effects\\Skill\\Morion\\ChainLightning 02.wav",			SKILL_SOUND_SKILL_CHAIN_LIGHTNING2	},
	{	"game\\Audio\\Effects\\Skill\\Morion\\Distortion 01.wav",				SKILL_SOUND_SKILL_DISTORTION		},
	{	"game\\Audio\\Effects\\Skill\\Morion\\DIvinePiercing 07.wav",			SKILL_SOUND_SKILL_DVINE_PIERCING	},
	{	"game\\Audio\\Effects\\Skill\\Morion\\eXtremeRage 01.wav",				SKILL_SOUND_SKILL_EXTREM_RAGE1		},
	{	"game\\Audio\\Effects\\Skill\\Morion\\eXtremeRage 02.wav",				SKILL_SOUND_SKILL_EXTREM_RAGE2		},
	{	"game\\Audio\\Effects\\Skill\\Morion\\eXtremeRage 03.wav",				SKILL_SOUND_SKILL_EXTREM_RAGE3		},
	{	"game\\Audio\\Effects\\Skill\\Morion\\FireElemental 01.wav",			SKILL_SOUND_SKILL_FIRE_ELEMENTAL	},
	{	"game\\Audio\\Effects\\Skill\\Morion\\FlameWave 01.wav",				SKILL_SOUND_SKILL_FLAME_WAVE1		},
	{	"game\\Audio\\Effects\\Skill\\Morion\\FlameWave 02.wav",				SKILL_SOUND_SKILL_FLAME_WAVE2		},
	{	"game\\Audio\\Effects\\Skill\\Morion\\FlameWaveA 01.wav",				SKILL_SOUND_SKILL_FLAME_WAVE3		},
	{	"game\\Audio\\Effects\\Skill\\Morion\\FrostJavelin 01.wav",				SKILL_SOUND_SKILL_FROST_JAVELIN		},
	{	"game\\Audio\\Effects\\Skill\\Morion\\GlacialSpike 01.wav",				SKILL_SOUND_SKILL_GLACIAL_SPIKE1	},
	{	"game\\Audio\\Effects\\Skill\\Morion\\GlacialSpike 02.wav",				SKILL_SOUND_SKILL_GLACIAL_SPIKE2	},
	{	"game\\Audio\\Effects\\Skill\\Morion\\HallOfValhalla 01.wav",			SKILL_SOUND_SKILL_HALL_OF_VALHALLA	},
	{	"game\\Audio\\Effects\\Skill\\Morion\\Meteo 01.wav",					SKILL_SOUND_SKILL_METEO1			},
	{	"game\\Audio\\Effects\\Skill\\Morion\\Meteo 02.wav",					SKILL_SOUND_SKILL_METEO2			},
	{	"game\\Audio\\Effects\\Skill\\Morion\\Meteo 03.wav",					SKILL_SOUND_SKILL_METEO3			},
	{	"game\\Audio\\Effects\\Skill\\Morion\\Muspell 01.wav",					SKILL_SOUND_SKILL_MUSPELL1			},
	{	"game\\Audio\\Effects\\Skill\\Morion\\Muspell 02.wav",					SKILL_SOUND_SKILL_MUSPELL2			},
	{	"game\\Audio\\Effects\\Skill\\Morion\\RegenField 01.wav",				SKILL_SOUND_SKILL_REGEN_FIELD1		},
	{	"game\\Audio\\Effects\\Skill\\Morion\\RegenField 02.wav",				SKILL_SOUND_SKILL_REGEN_FIELD2		},
	{	"game\\Audio\\Effects\\Skill\\Morion\\SwordofJustice 01.wav",			SKILL_SOUND_SKILL_SWORD_OF_JUSTICE	},
	{	"game\\Audio\\Effects\\Skill\\Morion\\Vengeance 01.wav",				SKILL_SOUND_SKILL_VENGEANCE1		},
	{	"game\\Audio\\Effects\\Skill\\Morion\\Vengeance 02.wav",				SKILL_SOUND_SKILL_VENGEANCE2		},

	{	0,0 }
};




int	InitSoundEffect(HWND hWnd)
{
	int	cnt;
	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;
	char	szFindPath[64];

	LoadSoundNum = 0;

	for(cnt = 0; cnt < NUM_SOUNDS; cnt++)
		sangJuWav_F[cnt] = 1;

	while(1)
	{
		if(sangJuWav2[LoadSoundNum] == NULL) break;
		strcpy_s(sangJuWav[LoadSoundNum], sangJuWav2[LoadSoundNum]);
		LoadSoundNum++;
	}

	snEffectCnt = 0;

	for(cnt = 0; cnt < snFIND_EFFECT_MAX; cnt++)
	{
		strcpy_s(szFindPath, snFindEffects[cnt].lpStringCode);
		lstrcat(szFindPath, "*.wav");


		hFindHandle = FindFirstFile(szFindPath, &fd);
		if(hFindHandle != INVALID_HANDLE_VALUE)
		{
			while(1)
			{

				strcpy_s(sangJuWav[LoadSoundNum], snFindEffects[cnt].lpStringCode);
				lstrcat(sangJuWav[LoadSoundNum], fd.cFileName);

				if(snFindEffects[cnt].CharSoundCode >= 0x1000)
				{

					sangJuWav_F[LoadSoundNum] = 0;
				}


				snEffect[snEffectCnt].RealSoundNum = LoadSoundNum + 1;
				snEffect[snEffectCnt].CharSoundCode = snFindEffects[cnt].CharSoundCode;
				snEffect[snEffectCnt].MotionState = FindMotionState(fd.cFileName);

				snEffectCnt++;
				LoadSoundNum++;


				if(FindNextFile(hFindHandle, &fd) == FALSE) break;
				if(snEffectCnt >= snEFFECT_MAX) break;
			}
		}
		else
		{
			snEffectCnt = snEffectCnt;

		}

		FindClose(hFindHandle);
	}

	snEffectWeaponCnt = 0;

	strcpy_s(szFindPath, szSndWeaponPath);
	lstrcat(szFindPath, "*.wav");


	hFindHandle = FindFirstFile(szFindPath, &fd);
	if(hFindHandle != INVALID_HANDLE_VALUE)
	{
		while(1)
		{

			strcpy_s(sangJuWav[LoadSoundNum], szSndWeaponPath);
			lstrcat(sangJuWav[LoadSoundNum], fd.cFileName);


			snEffectWeapon[snEffectWeaponCnt].RealSoundNum = LoadSoundNum + 1;
			snEffectWeapon[snEffectWeaponCnt].WeaponState = FindWeaponState(fd.cFileName);

			snEffectWeaponCnt++;
			LoadSoundNum++;


			if(FindNextFile(hFindHandle, &fd) == FALSE) break;
			if(snEffectWeaponCnt >= snEFFECT_MAX) break;

		}
		FindClose(hFindHandle);
	}

	sinSoundNum = LoadSoundNum + 1;
	cnt = 0;
	while(1)
	{
		if(sinSoundWav[cnt] == NULL) break;
		strcpy_s(sangJuWav[LoadSoundNum], sinSoundWav[cnt++]);
		LoadSoundNum++;
	}

	esSoundNum = LoadSoundNum + 1;
	cnt = 0;
	while(1)
	{
		if(esSoundWav[cnt] == NULL) break;
		strcpy_s(sangJuWav[LoadSoundNum], esSoundWav[cnt++]);
		LoadSoundNum++;
	}

	SkillSoundNum = LoadSoundNum + 1;
	cnt = 0;
	while(1)
	{
		if(SkillSoundWav[cnt].szFile == NULL) break;
		strcpy_s(sangJuWav[LoadSoundNum], SkillSoundWav[cnt++].szFile);
		LoadSoundNum++;
	}


	AmbientSoundNum = esSoundNum + AMBIENT_SOUND_NUM;
	AmbientSoundNum2 = esSoundNum + AMBIENT_SOUND_NUM2;
	ContinueSoundNum = esSoundNum + CONTINUE_SOUND_NUM;

	sangJuWav[LoadSoundNum][0] = 0;

	InitDX_Wav2(hWnd);

	return TRUE;
}



int CloseSoundEffect()
{

	TermDX_Wav2();

	return TRUE;
}



int	sinPlaySound(int Num, int Volume)
{


	if (cSettings::GetInstance()->cSVol == 0)
		Volume = 0;
	if (cSettings::GetInstance()->cSVol == 1)
		Volume = (30 * Volume) / 100;
	if (cSettings::GetInstance()->cSVol == 2)
		Volume = (40 * Volume) / 100;
	if (cSettings::GetInstance()->cSVol == 3)
		Volume = (50 * Volume) / 100;
	if (cSettings::GetInstance()->cSVol == 4)
		Volume = (60 * Volume) / 100;
	if (cSettings::GetInstance()->cSVol == 5)
		Volume = (70 * Volume) / 100;
	if (cSettings::GetInstance()->cSVol == 6)
		Volume = (80 * Volume) / 100;
	if (cSettings::GetInstance()->cSVol == 7)
		Volume = (90 * Volume) / 100;
	if (cSettings::GetInstance()->cSVol == 8)
		Volume = Volume;

	PlayWav2(sinSoundNum + Num, 0, Volume, 2205);

	return TRUE;
}




int	esPlaySound(int Num, int Volume)
{

	if (!cSettings::GetInstance()->cAmbient)
		return FALSE;

	if (cSettings::GetInstance()->cSVol == 0)
		Volume = 0;
	if (cSettings::GetInstance()->cSVol == 1)
		Volume = (30 * Volume) / 100;
	if (cSettings::GetInstance()->cSVol == 2)
		Volume = (40 * Volume) / 100;
	if (cSettings::GetInstance()->cSVol == 3)
		Volume = (50 * Volume) / 100;
	if (cSettings::GetInstance()->cSVol == 4)
		Volume = (60 * Volume) / 100;
	if (cSettings::GetInstance()->cSVol == 5)
		Volume = (70 * Volume) / 100;
	if (cSettings::GetInstance()->cSVol == 6)
		Volume = (80 * Volume) / 100;
	if (cSettings::GetInstance()->cSVol == 7)
		Volume = (90 * Volume) / 100;
	if (cSettings::GetInstance()->cSVol == 8)
		Volume = Volume;

	PlayWav2(esSoundNum + Num, 0, Volume, 2205);

	return TRUE;
}


int	esPlaySound(int Num, int Volume, int SampleRate)
{

	if (!cSettings::GetInstance()->cAmbient)
		return FALSE;

	if (cSettings::GetInstance()->cSVol == 0)
		Volume = 0;
	if (cSettings::GetInstance()->cSVol == 1)
		Volume = (30 * Volume) / 100;
	if (cSettings::GetInstance()->cSVol == 2)
		Volume = (40 * Volume) / 100;
	if (cSettings::GetInstance()->cSVol == 3)
		Volume = (50 * Volume) / 100;
	if (cSettings::GetInstance()->cSVol == 4)
		Volume = (60 * Volume) / 100;
	if (cSettings::GetInstance()->cSVol == 5)
		Volume = (70 * Volume) / 100;
	if (cSettings::GetInstance()->cSVol == 6)
		Volume = (80 * Volume) / 100;
	if (cSettings::GetInstance()->cSVol == 7)
		Volume = (90 * Volume) / 100;
	if (cSettings::GetInstance()->cSVol == 8)
		Volume = Volume;

	PlayWav2(esSoundNum + Num, 0, Volume, SampleRate);

	return TRUE;
}


int	esObjectSoundNum = 0;
int esObjectVolume = 0;


int esPlayObjectSound(int Num, int x, int y, int z)
{
	int vol;
	int OldSound;
	int SoundNum;

	if(Num < 0)
	{
		if(esObjectSoundNum)
		{
			StopWav(esObjectSoundNum + esSoundNum);
			esObjectSoundNum = 0;
		}
		return TRUE;
	}

	SoundNum = esSoundNum + Num;
	vol = GetDistVolume(x, y, z) + 100;
	if(vol > 400) vol = 400;

	OldSound = esObjectSoundNum;

	if(Num == esObjectSoundNum && vol == esObjectVolume) return TRUE;

	if(vol)
	{
		if(esObjectSoundNum == Num)
		{
			PlayWav_VolChange(SoundNum, vol);
		}
		else
		{
			PlayWav2(SoundNum, 1, vol, 2205);
			esObjectSoundNum = Num;
			if(OldSound)
				StopWav(OldSound + Num);
		}
	}
	else
	{
		if(OldSound)
		{
			StopWav(OldSound + Num);
		}
	}

	esObjectVolume = vol;

	return TRUE;
}


char *szAmbientSound2[] = {
	"game\\Audio\\Ambient\\stone-mill.wav",

	"game\\Audio\\Ambient\\dungeon_pumping_b.wav",
	"game\\Audio\\Ambient\\dungeon_pumping_l.wav",
	"game\\Audio\\Ambient\\dungeon_spin_b.wav",
	"game\\Audio\\Ambient\\lake 1.wav",
	"game\\Audio\\Ambient\\mystic 1.wav",
	"game\\Audio\\Ambient\\mystic 2.wav",
	"game\\Audio\\Ambient\\ship_swaing_l.wav",
	"game\\Audio\\Ambient\\stream.wav",
	"game\\Audio\\Ambient\\town_bell 1.wav",
	"game\\Audio\\Ambient\\town_bell 2.wav",
	"game\\Audio\\Ambient\\town_spin_b.wav",
	"game\\Audio\\Ambient\\town_spin_l.wav",
	"game\\Audio\\Ambient\\waterfall.wav",
	"game\\Audio\\Ambient\\stone-mill2.wav",

	"game\\Audio\\Ambient\\watermill 1.wav",
	"game\\Audio\\Ambient\\windmill 1.wav",
	"game\\Audio\\Ambient\\windmill 2.wav",
	"game\\Audio\\Ambient\\windmill 3.wav",
	"game\\Audio\\Ambient\\windmill 4.wav",
	"game\\Audio\\Ambient\\owl 1.wav",

	"game\\Audio\\Ambient\\dungeon_big-bolt 1.wav",
	"game\\Audio\\Ambient\\dungeon_stonepole.wav",
	"game\\Audio\\Ambient\\zombiemill 1.wav",
	"game\\Audio\\Ambient\\dungeon_weight.wav",
	"game\\Audio\\Ambient\\dungeon_device_side.wav",
	"game\\Audio\\Ambient\\dungeon_device_axe.wav",
	"game\\Audio\\Ambient\\dungeon_cage 1.wav",

	0
};



char *szSodSound[] = {
	"game\\Audio\\Sod\\start.wav",
	"game\\Audio\\Sod\\round1.wav",
	"game\\Audio\\Sod\\round2.wav",
	"game\\Audio\\Sod\\round3.wav",
	"game\\Audio\\Sod\\round4.wav",
	"game\\Audio\\Sod\\round5.wav",
	"game\\Audio\\Sod\\round6.wav",
	"game\\Audio\\Sod\\round7.wav",
	"game\\Audio\\Sod\\round8.wav",
	"game\\Audio\\Sod\\round9.wav",
	"game\\Audio\\Sod\\stage.wav",
	"game\\Audio\\Sod\\complete.wav",
	"game\\Audio\\Sod\\fail.wav",
	"game\\Audio\\Sod\\congratulation.wav",


	"game\\Audio\\Sod\\BGM\\Stage_Complete.wav",
	"game\\Audio\\Sod\\BGM\\Stage_Fail.wav",
	"game\\Audio\\Sod\\BGM\\Ending.wav",

	0
};

#define	CONT_SOUND_MAX	8
#define	CONT_SOUND_MASK	7

int	ContSoundBuff[CONT_SOUND_MAX] = { -1, };
int	ContSoundPush = 0;
int	ContSoundPop = 0;
int	ContSoundNum = -1;

static int	LastVolumeDist = 0xFFFF;
static int  AmbientFlag = 0;


int ResetLastVolumeDist()
{
	int cnt;

	cnt = LastVolumeDist;
	LastVolumeDist = 0xFFFF;
	AmbientFlag = 0;

	return cnt;
}



int GetDistVolume2(int dx, int dy, int dz, int round)
{
	int vol;
	int x, y, z;

	x = (lpCurPlayer->pX - dx) >> FLOATNS;
	y = (lpCurPlayer->pY - dy) >> FLOATNS;
	z = (lpCurPlayer->pZ - dz) >> FLOATNS;

	if(abs(x) < 256 * fONE && abs(y) < 256 * fONE && abs(z) < 256 * fONE)
	{
		vol = x*x + z*z + y*y - round*round;
		vol /= 1100;
	}
	else
		vol = 0xFFFF;

	if(LastVolumeDist > vol) LastVolumeDist = vol;

	if(vol > 400) vol = 400;

	vol = 400 - vol;

	return vol;
}


int esPlayObjectSound2(int AmbNum, int round, int x, int y, int z)
{
	int vol;

	if(AmbNum < 0)
	{

		if(AmbientSound2 >= 0)
		{
			StopWav(AmbientSoundNum2);
			AmbientSound2 = -1;
		}
		return TRUE;
	}

	vol = GetDistVolume2(x, y, z, round);

	if (!cSettings::GetInstance()->cAmbient)
	{
		StopWav(AmbientSoundNum2);
		AmbientSound2 = -1;
		return FALSE;
	}

	if (cSettings::GetInstance()->cSVol == 0)
		vol = 0;
	if (cSettings::GetInstance()->cSVol == 1)
		vol = (30 * vol) / 100;
	if (cSettings::GetInstance()->cSVol == 2)
		vol = (40 * vol) / 100;
	if (cSettings::GetInstance()->cSVol == 3)
		vol = (50 * vol) / 100;
	if (cSettings::GetInstance()->cSVol == 4)
		vol = (60 * vol) / 100;
	if (cSettings::GetInstance()->cSVol == 5)
		vol = (70 * vol) / 100;
	if (cSettings::GetInstance()->cSVol == 6)
		vol = (80 * vol) / 100;
	if (cSettings::GetInstance()->cSVol == 7)
		vol = (90 * vol) / 100;
	if (cSettings::GetInstance()->cSVol == 8)
		vol = vol;

	if(vol > 100)
	{
		vol += 100;
		if(vol > 399) vol = 399;

		if(AmbNum != AmbientSound2 && !AmbientFlag)
		{
			if(CreateBufferFromWaveFile2(szAmbientSound2[AmbNum], AmbientSoundNum2) == FALSE)
				return FALSE;
			PlayWav2(AmbientSoundNum2, 1, vol, 2205);
			AmbientSound2 = AmbNum;
		}
		else
		{
			PlayWav_VolChange(AmbientSoundNum2, vol);
		}
		AmbientFlag++;
	}

	return TRUE;

}

int esContSound()
{
	int cnt;

	if (!cSettings::GetInstance()->cMusic)
		return FALSE;

	int dwVol = 360;

	if (cSettings::GetInstance()->cMVol == 0)
		dwVol = 0;
	if (cSettings::GetInstance()->cMVol == 1)
		dwVol = (30 * dwVol) / 100;
	if (cSettings::GetInstance()->cMVol == 2)
		dwVol = (40 * dwVol) / 100;
	if (cSettings::GetInstance()->cMVol == 3)
		dwVol = (50 * dwVol) / 100;
	if (cSettings::GetInstance()->cMVol == 4)
		dwVol = (60 * dwVol) / 100;
	if (cSettings::GetInstance()->cMVol == 5)
		dwVol = (70 * dwVol) / 100;
	if (cSettings::GetInstance()->cMVol == 6)
		dwVol = (80 * dwVol) / 100;
	if (cSettings::GetInstance()->cMVol == 7)
		dwVol = (90 * dwVol) / 100;
	if (cSettings::GetInstance()->cMVol == 8)
		dwVol = dwVol;

	ContSoundCount++;

	if((ContSoundCount & 0x7) != 0) return FALSE;

	if(ContSoundNum >= 0)
	{
		if(IsPlayWav(ContinueSoundNum) == TRUE)
		{
			return FALSE;
		}

		ContSoundNum = -1;
	}

	if(ContSoundPush > ContSoundPop)
	{
		cnt = ContSoundPop&CONT_SOUND_MASK;
		ContSoundNum = ContSoundBuff[cnt];

		if(CreateBufferFromWaveFile2(szSodSound[ContSoundNum], ContinueSoundNum) == FALSE)
			return FALSE;

		PlayWav2(ContinueSoundNum, 0, 360, 2205);

		ContSoundPop++;

		return TRUE;
	}

	return FALSE;
}


int esPlayContSound(int SoundNum)
{
	int cnt;

	if((ContSoundPush - ContSoundPop) >= CONT_SOUND_MAX) return FALSE;

	cnt = ContSoundPush&CONT_SOUND_MASK;
	ContSoundBuff[cnt] = SoundNum;
	ContSoundPush++;

	return TRUE;
}


int	SkillPlaySound(int Num, int Volume, int Loop)
{
	if (!cSettings::GetInstance()->cSound)
		return FALSE;

	if (cSettings::GetInstance()->cSVol == 0)
		Volume = 0;
	if (cSettings::GetInstance()->cSVol == 1)
		Volume = (30 * Volume) / 100;
	if (cSettings::GetInstance()->cSVol == 2)
		Volume = (40 * Volume) / 100;
	if (cSettings::GetInstance()->cSVol == 3)
		Volume = (50 * Volume) / 100;
	if (cSettings::GetInstance()->cSVol == 4)
		Volume = (60 * Volume) / 100;
	if (cSettings::GetInstance()->cSVol == 5)
		Volume = (70 * Volume) / 100;
	if (cSettings::GetInstance()->cSVol == 6)
		Volume = (80 * Volume) / 100;
	if (cSettings::GetInstance()->cSVol == 7)
		Volume = (90 * Volume) / 100;
	if (cSettings::GetInstance()->cSVol == 8)
		Volume = Volume;

	PlayWav2(SkillSoundNum + Num, Loop, Volume, 2205);

	return TRUE;
}


int	SkillPlaySound(DWORD dwCode, int x, int y, int z, int Flag)
{
	int cnt;

	cnt = 0;
	while(1)
	{
		if(!SkillSoundWav[cnt].szFile) break;
		if(SkillSoundWav[cnt].dwCode == dwCode)
		{
			return SkillPlaySound(cnt, GetDistVolume(x, y, z), Flag);
		}
		cnt++;
	}

	return FALSE;
}


int	SkillStopSound(DWORD dwCode)
{
	int cnt;

	cnt = 0;
	while(1)
	{
		if(!SkillSoundWav[cnt].szFile) break;
		if(SkillSoundWav[cnt].dwCode == dwCode)
		{
			return StopWav(SkillSoundNum + cnt);
		}
		cnt++;
	}

	return FALSE;
}









int	esPlayEffectBgm(int Num)
{

	if(Num < 0)
	{
		if(AmbientSound >= 0)
		{
			StopWav(AmbientSoundNum);
			AmbientSound = Num;
		}
		return TRUE;
	}

	if (!cSettings::GetInstance()->cAmbient)
	{
		StopWav(AmbientSoundNum);
		AmbientSound = Num;
		return FALSE;
	}

	int vol = 400;

	if (cSettings::GetInstance()->cSVol == 0)
		vol = 0;
	if (cSettings::GetInstance()->cSVol == 1)
		vol = (30 * vol) / 100;
	if (cSettings::GetInstance()->cSVol == 2)
		vol = (40 * vol) / 100;
	if (cSettings::GetInstance()->cSVol == 3)
		vol = (50 * vol) / 100;
	if (cSettings::GetInstance()->cSVol == 4)
		vol = (60 * vol) / 100;
	if (cSettings::GetInstance()->cSVol == 5)
		vol = (70 * vol) / 100;
	if (cSettings::GetInstance()->cSVol == 6)
		vol = (80 * vol) / 100;
	if (cSettings::GetInstance()->cSVol == 7)
		vol = (90 * vol) / 100;
	if (cSettings::GetInstance()->cSVol == 8)
		vol = vol;

	if(AmbientSound != Num)
	{
		if(CreateBufferFromWaveFile2(szAmbientSound[Num], AmbientSoundNum) == FALSE)
			return FALSE;

		PlayWav2(AmbientSoundNum, 1, 400, 2205);
		AmbientSound = Num;
	}

	return TRUE;
}


static int	FootStepCount = 0;


int PlayFootStep(smCHAR *lpChar)
{
	int floor;
	int cnt;


	FootStepCount++;

	if(lpChar->OnStageField >= 0)
	{
		floor = StageField[lpChar->OnStageField]->State;

		if(lpChar->WaterHeight != CLIP_OUT &&
		   lpChar->WaterHeight > lpChar->pY && lpChar->WaterHeight < (lpChar->pY + 32 * fONE))
		{

			if(FootStepCount & 1)
			{

				cnt = 14;
				esPlaySound(cnt + ((FootStepCount >> 1) % 3), 400);

			}
			return TRUE;
		}

		switch(floor)
		{
			case FIELD_STATE_VILLAGE:
			case FIELD_STATE_RUIN:

			cnt = 2;
			esPlaySound(cnt + (rand() % 3), 400);
			break;

			case FIELD_STATE_FOREST:
			case FIELD_STATE_DESERT:

			cnt = 0;
			esPlaySound(cnt + (rand() % 2), 400);
			break;

			case FIELD_STATE_DUNGEON:

			cnt = 11;
			esPlaySound(cnt + (rand() % 3), 400);
			break;
		}
	}

	return TRUE;
}



int	CharPlaySound(smCHAR *lpChar)
{
	int cnt;

	DWORD	dwMotionCode;
	DWORD	dwCharSoundCode;
	int	vol;
	int x, y, z;

	int	CodeBuff[32];
	int	CodeBuffCnt = 0;

	x = (lpChar->pX - lpCurPlayer->pX) >> FLOATNS;
	z = (lpChar->pZ - lpCurPlayer->pZ) >> FLOATNS;
	y = (lpChar->pY - lpCurPlayer->pY) >> FLOATNS;

	vol = x*x + z*z + y*y;
	vol /= 1100;

	if(vol > 400) vol = 400;
	if(vol < 0) return TRUE;

	vol = 400 - vol;


	if(lpChar->smCharInfo.State == smCHAR_STATE_USER)
		dwCharSoundCode = lpChar->smCharInfo.JOB_CODE;
	else
		dwCharSoundCode = lpChar->smCharInfo.dwCharSoundCode;



	if(!lpChar->MotionInfo) return FALSE;

	dwMotionCode = lpChar->MotionInfo->State;


	if(dwMotionCode == CHRMOTION_STATE_RESTART)
	{
		esPlaySound(6, vol);
		return TRUE;
	}

	if(dwMotionCode == CHRMOTION_STATE_WALK || dwMotionCode == CHRMOTION_STATE_RUN)
	{

		if(vol < 300) return TRUE;
		dwMotionCode = CHRMOTION_STATE_WALK;
	}



	if(lpChar->smCharInfo.wPlayClass[0] == MONSTER_CLASS_HAMMER && dwMotionCode == CHRMOTION_STATE_ATTACK)
		dwMotionCode = CHRMOTION_STATE_HAMMER;

	for(cnt = 0; cnt < snEffectCnt; cnt++)
	{
		if(snEffect[cnt].CharSoundCode == dwCharSoundCode &&
		   snEffect[cnt].MotionState == dwMotionCode)
		{

			CodeBuff[CodeBuffCnt++] = cnt;

		}
	}

	if(CodeBuffCnt)
	{

		int	Feq;
		Feq = 2205;
		if(lpChar->smCharInfo.wPlayClass[1] && lpChar->smCharInfo.Brood != smCHAR_MONSTER_USER)
		{
			if(lpChar->smCharInfo.wPlayClass[1] < fONE)
				Feq = 3600;
			if(lpChar->smCharInfo.wPlayClass[1] > fONE * 2)
				Feq = 1400;
		}
		if(lpChar->smCharInfo.State == smCHAR_STATE_USER && lpChar->smCharInfo.SizeLevel >= 0x1000)
			Feq = 2800;

		PlayWav2(snEffect[CodeBuff[rand() % CodeBuffCnt]].RealSoundNum, 0, vol, Feq);
		return TRUE;
	}


	return FALSE;
}



int	WeaponPlaySound(smCHAR *lpChar)
{
	int cnt;

	DWORD	dwCode;

	int	vol;
	int x, y, z;
	int	ItemNum;
	int HandType;

	int	CodeBuff[32];
	int	CodeBuffCnt = 0;

	if(lpChar != lpCurPlayer)
	{

		x = (lpChar->pX - lpCurPlayer->pX) >> FLOATNS;
		z = (lpChar->pZ - lpCurPlayer->pZ) >> FLOATNS;
		y = (lpChar->pY - lpCurPlayer->pY) >> FLOATNS;

		vol = x*x + z*z + y*y;
		vol /= 1100;

		if(vol > 400) vol = 400;
		if(vol < 0) return TRUE;

		vol = 400 - vol;
	}
	else
		vol = 400;




	for(cnt = 0; cnt < MAX_ITEM; cnt++)
	{
		if(sItem[cnt].CODE == lpChar->dwActionItemCode)
		{
			ItemNum = cnt;
			HandType = sItem[cnt].Class;
			break;
		}
	}
	if(cnt == MAX_ITEM) return FALSE;

	if(lpChar->AttackCritcal < 0)
	{

		if(HandType == ITEM_CLASS_WEAPON_ONE)
			dwCode = 12;
		else
			dwCode = 13;
	}
	else
	{
		dwCode = 14;

		switch(lpChar->dwActionItemCode&sinITEM_MASK2)
		{
			case sinWA1:

			if(HandType == ITEM_CLASS_WEAPON_ONE)
				dwCode = 1;
			else
				dwCode = 2;
			break;

			case sinWS2:

			if((lpChar->dwActionItemCode&sinITEM_MASK3) <= sin03)
			{

				dwCode = 15;
				break;
			}


			if(HandType == ITEM_CLASS_WEAPON_ONE)
				dwCode = 3;
			else
				dwCode = 4;
			break;

			case sinWP1:

			if(HandType == ITEM_CLASS_WEAPON_ONE)
				dwCode = 5;
			else
				dwCode = 6;
			break;

			case sinWC1:

			dwCode = 7;
			break;

			case sinWS1:

			dwCode = 8;
			break;

			case sinWM1:

			if(lpChar->smCharInfo.JOB_CODE == 8 || lpChar->smCharInfo.JOB_CODE == 7)
			{
				if(lpChar->WeaponEffect) return TRUE;

				if(HandType == ITEM_CLASS_WEAPON_ONE)
					dwCode = 17;
				else
					dwCode = 18;
			}
			else
			{

				if(HandType == ITEM_CLASS_WEAPON_ONE)
					dwCode = 9;
				else
					dwCode = 10;
			}
			break;

			case sinWH1:

			if(HandType == ITEM_CLASS_WEAPON_ONE)
				dwCode = 9;
			else
				dwCode = 10;
			break;

			case sinWT1:

			dwCode = 11;
			break;
		}
	}

	for(cnt = 0; cnt < snEffectWeaponCnt; cnt++)
	{
		if(snEffectWeapon[cnt].WeaponState == dwCode)
		{
			CodeBuff[CodeBuffCnt++] = cnt;
		}
	}

	if(CodeBuffCnt)
	{
		PlayWav2(snEffectWeapon[CodeBuff[rand() % CodeBuffCnt]].RealSoundNum, 0, vol, 2205);

		if((lpChar->AttackCritcal > 0 || (lpChar->AttackCritcal >= 0 && lpChar->AttackEffect)) &&
		   lpChar->dwActionItemCode)
		{

			dwCode = 16;
			CodeBuffCnt = 0;
			for(cnt = 0; cnt < snEffectWeaponCnt; cnt++)
			{
				if(snEffectWeapon[cnt].WeaponState == dwCode)
				{
					CodeBuff[CodeBuffCnt++] = cnt;
				}
			}
			if(CodeBuffCnt)
				PlayWav2(snEffectWeapon[CodeBuff[rand() % CodeBuffCnt]].RealSoundNum, 0, vol, 2205);
		}
		return TRUE;
	}

	return FALSE;
}


int PlayWaponSoundDirect(int x, int y, int z, DWORD dwCode)
{

	int cnt;
	int	vol;

	int	CodeBuff[32];
	int	CodeBuffCnt = 0;


	CodeBuffCnt = 0;
	for(cnt = 0; cnt < snEffectWeaponCnt; cnt++)
	{
		if(snEffectWeapon[cnt].WeaponState == dwCode)
		{
			CodeBuff[CodeBuffCnt++] = cnt;
		}
	}

	vol = GetDistVolume(x, y, z);

	if(CodeBuffCnt && vol > 10)
		PlayWav2(snEffectWeapon[CodeBuff[rand() % CodeBuffCnt]].RealSoundNum, 0, vol, 2205);


	return TRUE;
}




char *szMusicFile[] = {
	"game\\Audio\\bgm\\Field - Desert - Pilgrim.bgm",
	"game\\Audio\\bgm\\Town - Tempskron_Stronghold.bgm",
	"game\\Audio\\bgm\\Town 1 - Tempskron_Ricarten - When wind comes-o.bgm",
	"game\\Audio\\bgm\\wind loop.bgm",
	"game\\Audio\\bgm\\Field - Forest - DarkWood.bgm",
	"game\\Audio\\bgm\\Dungeon - Gloomy Heart.bgm",
	"game\\Audio\\bgm\\Town 2 - Morion_Philliy - Voyage above the Clouds.bgm",


	"game\\Audio\\Sod\\BGM\\Stage_Play1.bgm",
	"game\\Audio\\Sod\\BGM\\Stage_Play1.bgm",
	"game\\Audio\\Sod\\BGM\\Stage_Play3.bgm",
	"game\\Audio\\bgm\\Field - Desert - Pilgrim.bgm",
	"game\\Audio\\bgm\\Ice 1.bgm",

	NULL
};



int	NextMusicNum;
DWORD	dwFadeStartTime = 0;
int LastMusicVolume;
int	PlayingBgmNum = -1;



int PlayBGM_Direct(int MusicNum)
{

	if(cSettings::GetInstance()->cSound && MusicNum >= 0)
	{
		OpenBGM(szMusicFile[MusicNum]);
		PlayBGM();
		dwFadeStartTime = 0;
		PlayingBgmNum = MusicNum;
		NextMusicNum = MusicNum;
		SetVolumeBGM(360);
		LastMusicVolume = 360;
	}
	return TRUE;
}



int ChangeBGM(int MusicNum)
{
	if(cSettings::GetInstance()->cSound)
	{
		if(!dwFadeStartTime)
		{
			if(NextMusicNum == MusicNum) return FALSE;
			NextMusicNum = MusicNum;
			dwFadeStartTime = dwPlayTime;

		}
		else
		{
			NextMusicNum = MusicNum;
		}
	}

	return TRUE;
}

int BGM_Main()
{
	if(dwFadeStartTime)
	{
		int vol = (dwPlayTime - dwFadeStartTime) / 10;
		vol = 360 - vol;

		if(vol <= 0)
		{
			if(NextMusicNum >= 0)
			{
				OpenBGM(szMusicFile[NextMusicNum]);
				PlayBGM();
			}
			else
			{
				StopBGM();
			}

			dwFadeStartTime = 0;
			PlayingBgmNum = NextMusicNum;
		}
		else
		{
			if(LastMusicVolume != vol)
			{
				SetVolumeBGM(vol);
			}
		}

		LastMusicVolume = vol;
	}

	esContSound();

	return TRUE;
}

int GetDistVolume(int dx, int dy, int dz)
{
	int vol;
	int x, y, z;

	x = (lpCurPlayer->pX - dx) >> FLOATNS;
	y = (lpCurPlayer->pY - dy) >> FLOATNS;
	z = (lpCurPlayer->pZ - dz) >> FLOATNS;

	vol = x*x + z*z + y*y;
	vol /= 1100;

	if(vol > 400) vol = 400;

	vol = 400 - vol;

	return vol;
}




const char *TALK_SOUND_DIRECOTRY = { "game\\Audio\\Talk\\" };

char		g_szTalkSoundFullName[128];
char		g_szTalkSoundName[64];
DWORD		g_TalkSoundSum;

char		g_szPlayTalkSoundName[64];
DWORD		g_PlayTalkSoundSum;

static int  s_TalkSoundBuffNum;
static int  s_TalkSoundIsPlay;




int FindTalkSound(char *lpSrcMessage)
{
	g_TalkSoundSum = GetSpeedSum(lpSrcMessage);
	::_ui64toa(g_TalkSoundSum, g_szTalkSoundName, 10);
	strcat(g_szTalkSoundName, ".wav");

	strcpy(g_szTalkSoundFullName, TALK_SOUND_DIRECOTRY);
	strcat(g_szTalkSoundFullName, g_szTalkSoundName);

	FILE *fp = fopen(g_szTalkSoundFullName, "rb");
	if(fp == NULL)
		return FALSE;

	return TRUE;
}





extern int isPlaying(int i);
int IsPlayTalkSound(void)
{
	if(s_TalkSoundBuffNum && s_TalkSoundIsPlay)
	{
		s_TalkSoundIsPlay = isPlaying(s_TalkSoundBuffNum);
		return s_TalkSoundIsPlay;
	}

	return 0;
}





void PlayTalkSound(void)
{
	if(s_TalkSoundBuffNum == 0)
	{
		s_TalkSoundBuffNum = LoadSoundNum;
		sangJuWav_F[s_TalkSoundBuffNum] = 0;
		LoadSoundNum++;
	}

	if(CreateBufferFromWaveFile2(g_szTalkSoundFullName, s_TalkSoundBuffNum) == FALSE)
		return;

	PlayWav2(s_TalkSoundBuffNum, 0, 400, 2205);

	strcpy_s(g_szPlayTalkSoundName, g_szTalkSoundName);
	g_PlayTalkSoundSum = g_TalkSoundSum;
	s_TalkSoundIsPlay = 1;
}





void StopTalkSound(void)
{
	if(s_TalkSoundBuffNum)
		StopWav(s_TalkSoundBuffNum);

	s_TalkSoundIsPlay = 0;
}




