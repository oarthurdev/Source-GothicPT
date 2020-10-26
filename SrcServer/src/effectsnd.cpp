#include "smlib3d\\smd3d.h"
#include "smwsock.h"

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


#define	snFIND_EFFECT_MAX			166			




snFIND_EFFECT	snFindEffects[snFIND_EFFECT_MAX] = {

	{ "Assets\\Audio\\Effects\\monster\\cyclops\\"	,	snCHAR_SOUND_CYCLOPS	},
	{ "Assets\\Audio\\Effects\\monster\\hob goblin\\"	,	snCHAR_SOUND_HOBGOBLIN	},
	{ "Assets\\Audio\\Effects\\monster\\Imp\\"		,	snCHAR_SOUND_IMP		},
	{ "Assets\\Audio\\Effects\\monster\\miniG\\"		,	snCHAR_SOUND_MINIG		},
	{ "Assets\\Audio\\Effects\\monster\\plant\\"		,	snCHAR_SOUND_PLANT		},
	{ "Assets\\Audio\\Effects\\monster\\skeleton\\"	,	snCHAR_SOUND_SKELETON	},
	{ "Assets\\Audio\\Effects\\monster\\zombi\\"		,	snCHAR_SOUND_ZOMBI		},
	{ "Assets\\Audio\\Effects\\monster\\obit\\"		,	snCHAR_SOUND_OBIT		},

	{ "Assets\\Audio\\Effects\\monster\\hopt\\"		,	snCHAR_SOUND_HOPT		},
	{ "Assets\\Audio\\Effects\\monster\\bargon\\"		,	snCHAR_SOUND_BARGON		},
	{ "Assets\\Audio\\Effects\\monster\\leech\\"		,	snCHAR_SOUND_LEECH		},
	{ "Assets\\Audio\\Effects\\monster\\mushroom\\"	,	snCHAR_SOUND_MUSHROOM	},

	{ "Assets\\Audio\\Effects\\monster\\Arma\\"		,	snCHAR_SOUND_ARMA		},
	{ "Assets\\Audio\\Effects\\monster\\scorpion\\"	,	snCHAR_SOUND_SCORPION	},


	{ "Assets\\Audio\\Effects\\monster\\HeadCutter\\"	,	snCHAR_SOUND_HEADCUTTER	},
	{ "Assets\\Audio\\Effects\\monster\\Sandlem\\"	,	snCHAR_SOUND_SANDLEM	},
	{ "Assets\\Audio\\Effects\\monster\\Web\\"		,	snCHAR_SOUND_WEB		},
	{ "Assets\\Audio\\Effects\\monster\\HopyKing\\"	,	snCHAR_SOUND_HOPYKING	},
	{ "Assets\\Audio\\Effects\\monster\\Crip\\"		,	snCHAR_SOUND_CRIP		},
	{ "Assets\\Audio\\Effects\\monster\\Buma\\"		,	snCHAR_SOUND_BUMA		},
	{ "Assets\\Audio\\Effects\\monster\\Decoy\\"		,	snCHAR_SOUND_DECOY		},
	{ "Assets\\Audio\\Effects\\monster\\Doral\\"		,	snCHAR_SOUND_DORAL		},
	{ "Assets\\Audio\\Effects\\monster\\Figon\\"		,	snCHAR_SOUND_FIGON		},
	{ "Assets\\Audio\\Effects\\monster\\StoneGiant\\"	,	snCHAR_SOUND_STONEGIANT	},
	{ "Assets\\Audio\\Effects\\monster\\Greven\\"		,	snCHAR_SOUND_GREVEN		},
	{ "Assets\\Audio\\Effects\\monster\\illusionknight\\" ,snCHAR_SOUND_ILLUSIONKNIGHT },
	{ "Assets\\Audio\\Effects\\monster\\SkeletonRange\\"	,	snCHAR_SOUND_SKELETONRANGE},
	{ "Assets\\Audio\\Effects\\monster\\SkeletonMelee\\"	,	snCHAR_SOUND_SKELETONMELEE},

	{ "Assets\\Audio\\Effects\\monster\\wolverin\\"		,	snCHAR_SOUND_WOLVERLIN		},


	{ "Assets\\Audio\\Effects\\monster\\Rabie\\"		,	snCHAR_SOUND_RABIE		},
	{ "Assets\\Audio\\Effects\\monster\\Mudy\\"		,	snCHAR_SOUND_MUDY		},
	{ "Assets\\Audio\\Effects\\monster\\Sen\\"		,	snCHAR_SOUND_SEN		},
	{ "Assets\\Audio\\Effects\\monster\\Egan\\"		,	snCHAR_SOUND_EGAN		},
	{ "Assets\\Audio\\Effects\\monster\\BeeDog\\"		,	snCHAR_SOUND_BEEDOG		},
	{ "Assets\\Audio\\Effects\\monster\\MutantPlant\\",	snCHAR_SOUND_MUTANTPLANT},
	{ "Assets\\Audio\\Effects\\monster\\MutantRabie\\",	snCHAR_SOUND_MUTANTRABIE},
	{ "Assets\\Audio\\Effects\\monster\\MutantTree\\"	,	snCHAR_SOUND_MUTANTTREE	},
	{ "Assets\\Audio\\Effects\\monster\\Avelisk\\"	,	snCHAR_SOUND_AVELISK	},
	{ "Assets\\Audio\\Effects\\monster\\Naz\\"		,	snCHAR_SOUND_NAZ		},
	{ "Assets\\Audio\\Effects\\monster\\Mummy\\"		,	snCHAR_SOUND_MUMMY		},
	{ "Assets\\Audio\\Effects\\monster\\Hulk\\"		,	snCHAR_SOUND_HULK		},
	{ "Assets\\Audio\\Effects\\monster\\Hungky\\"		,	snCHAR_SOUND_HUNGKY	},
	{ "Assets\\Audio\\Effects\\monster\\Succubus\\"	,	snCHAR_SOUND_SUCCUBUS	},
	{ "Assets\\Audio\\Effects\\monster\\Dawlin\\"		,	snCHAR_SOUND_DAWLIN		},
	{ "Assets\\Audio\\Effects\\monster\\Shadow\\"		,	snCHAR_SOUND_SHADOW		},
	{ "Assets\\Audio\\Effects\\monster\\Berserker\\"	,	snCHAR_SOUND_BERSERKER	},
	{ "Assets\\Audio\\Effects\\monster\\IronGuard\\"	,	snCHAR_SOUND_IRONGUARD	},
	{ "Assets\\Audio\\Effects\\monster\\Fury\\"		,	snCHAR_SOUND_FURY		},
	{ "Assets\\Audio\\Effects\\monster\\Sliver\\"		,	snCHAR_SOUND_SLIVER		},

	{ "Assets\\Audio\\Effects\\monster\\Ratoo\\"		,	snCHAR_SOUND_RATOO		},
	{ "Assets\\Audio\\Effects\\monster\\Stygianlord\\",	snCHAR_SOUND_STYGIANLORD},
	{ "Assets\\Audio\\Effects\\monster\\Omicron\\"	,	snCHAR_SOUND_OMICRON	},
	{ "Assets\\Audio\\Effects\\monster\\D-Machine\\"	,	snCHAR_SOUND_DMACHINE	},
	{ "Assets\\Audio\\Effects\\monster\\Metron\\"		,	snCHAR_SOUND_METRON		},

	{ "Assets\\Audio\\Effects\\monster\\MrGhost\\"	,	snCHAR_SOUND_MRGHOST	},


	{ "Assets\\Audio\\Effects\\monster\\VAMPIRICBAT\\",	snCHAR_SOUND_VAMPIRICBAT	},
	{ "Assets\\Audio\\Effects\\monster\\MIREKEEPER\\"	,	snCHAR_SOUND_MIREKEEPER		},
	{ "Assets\\Audio\\Effects\\monster\\MUFFIN\\"		,	snCHAR_SOUND_MUFFIN			},
	{ "Assets\\Audio\\Effects\\monster\\SOLIDSNAIL\\"	,	snCHAR_SOUND_SOLIDSNAIL		},
	{ "Assets\\Audio\\Effects\\monster\\BEEVIL\\"		,	snCHAR_SOUND_BEEVIL			},
	{ "Assets\\Audio\\Effects\\monster\\NIGHTMARE\\"	,	snCHAR_SOUND_NIGHTMARE		},
	{ "Assets\\Audio\\Effects\\monster\\STONEGOLEM\\"	,	snCHAR_SOUND_STONEGOLEM		},
	{ "Assets\\Audio\\Effects\\monster\\THORNCRAWLER\\",	snCHAR_SOUND_THORNCRAWLER	},
	{ "Assets\\Audio\\Effects\\monster\\HEAVYGOBLIN\\",	snCHAR_SOUND_HEAVYGOBLIN	},
	{ "Assets\\Audio\\Effects\\monster\\EVILPLANT\\"	,	snCHAR_SOUND_EVILPLANT		},
	{ "Assets\\Audio\\Effects\\monster\\HAUNTINGPLANT\\",	snCHAR_SOUND_HAUNTINGPLANT	},
	{ "Assets\\Audio\\Effects\\monster\\DARKKNIGHT\\"	,	snCHAR_SOUND_DARKKNIGHT		},
	{ "Assets\\Audio\\Effects\\monster\\Guardian-Saint\\",snCHAR_SOUND_GUARDIAN_SAINT	},




	{ "Assets\\Audio\\Effects\\monster\\ChainGolem\\"	,	snCHAR_SOUND_CHAINGOLEM		},
	{ "Assets\\Audio\\Effects\\monster\\DeadZone\\"	,	snCHAR_SOUND_DEADZONE		},
	{ "Assets\\Audio\\Effects\\monster\\Grotesque\\"	,	snCHAR_SOUND_GROTESQUE		},
	{ "Assets\\Audio\\Effects\\monster\\Hypermachine\\",	snCHAR_SOUND_HYPERMACHINE	},
	{ "Assets\\Audio\\Effects\\monster\\IronFist\\"	,	snCHAR_SOUND_IRONFIST		},
	{ "Assets\\Audio\\Effects\\monster\\Morgon\\"		,	snCHAR_SOUND_MORGON			},
	{ "Assets\\Audio\\Effects\\monster\\Mountain\\"	,	snCHAR_SOUND_MOUNTAIN		},
	{ "Assets\\Audio\\Effects\\monster\\Rampage\\"	,	snCHAR_SOUND_RAMPAGE		},
	{ "Assets\\Audio\\Effects\\monster\\RunicGuardian\\",	snCHAR_SOUND_RUNICGUARDIAN	},
	{ "Assets\\Audio\\Effects\\monster\\Sadness\\"	,	snCHAR_SOUND_SADNESS		},
	{ "Assets\\Audio\\Effects\\monster\\TowerGolem\\"	,	snCHAR_SOUND_TOWERGOLEM		},
	{ "Assets\\Audio\\Effects\\monster\\VampiricBee\\",	snCHAR_SOUND_VAMPRICBEE		},
	{ "Assets\\Audio\\Effects\\monster\\VampiricMachine\\",snCHAR_SOUND_VAMPRICMACHINE},
	{ "Assets\\Audio\\Effects\\monster\\Omu\\",			snCHAR_SOUND_OMU			},

	{ "Assets\\Audio\\Effects\\monster\\AvelinArcher\\",	snCHAR_SOUND_AVELIN_ARCHER	},
	{ "Assets\\Audio\\Effects\\monster\\AvelinQueen\\",	snCHAR_SOUND_AVELIN_QUEEN	},
	{ "Assets\\Audio\\Effects\\monster\\Babel\\",			snCHAR_SOUND_BABEL	},


	{ "Assets\\Audio\\Effects\\monster\\Mystic\\",		snCHAR_SOUND_MYSTIC			},
	{ "Assets\\Audio\\Effects\\monster\\HEAVYGOBLIN\\",	snCHAR_SOUND_ICEGOBLIN		},
	{ "Assets\\Audio\\Effects\\monster\\ColdEye\\",		snCHAR_SOUND_COLDEYE		},
	{ "Assets\\Audio\\Effects\\monster\\Frozen\\",		snCHAR_SOUND_FROZEN			},
	{ "Assets\\Audio\\Effects\\monster\\STONEGOLEM\\",	snCHAR_SOUND_ICEGOLEM		},
	{ "Assets\\Audio\\Effects\\monster\\Frost\\",			snCHAR_SOUND_FROST			},
	{ "Assets\\Audio\\Effects\\monster\\ChaosCara\\",		snCHAR_SOUND_CHAOSCARA		},
	{ "Assets\\Audio\\Effects\\monster\\DeathKnight\\",	snCHAR_SOUND_DEATHKNIGHT	},


	{ "Assets\\Audio\\Effects\\monster\\GreateGreven\\",	snCHAR_SOUND_GREATE_GREVEN	},
	{ "Assets\\Audio\\Effects\\monster\\LizardFolk\\",	snCHAR_SOUND_LIZARDFOLK		},
	{ "Assets\\Audio\\Effects\\monster\\M_Lord\\",		snCHAR_SOUND_M_LORD			},
	{ "Assets\\Audio\\Effects\\monster\\Spider\\",		snCHAR_SOUND_SPIDER			},
	{ "Assets\\Audio\\Effects\\monster\\Stingray\\",		snCHAR_SOUND_STINGRAY		},
	{ "Assets\\Audio\\Effects\\monster\\Strider\\",		snCHAR_SOUND_STRIDER		},


	{ "Assets\\Audio\\Effects\\monster\\TurtleCannon\\",	snCHAR_SOUND_TURTLE_CANNON	},
	{ "Assets\\Audio\\Effects\\monster\\DevilBird\\",		snCHAR_SOUND_DEVIL_BIRD		},
	{ "Assets\\Audio\\Effects\\monster\\BlizzardGiant\\",	snCHAR_SOUND_BLIZZARD_GIANT	},
	{ "Assets\\Audio\\Effects\\monster\\Kelvezu\\",		snCHAR_SOUND_KELVEZU		},


	{ "Assets\\Audio\\Effects\\monster\\DarkPhalanx\\",	snCHAR_SOUND_DARKPHALANX	},
	{ "Assets\\Audio\\Effects\\monster\\BloodyKnight\\",	snCHAR_SOUND_BLOODYKNIGHT	},
	{ "Assets\\Audio\\Effects\\monster\\Chimera\\",		snCHAR_SOUND_CHIMERA		},
	{ "Assets\\Audio\\Effects\\monster\\FireWorm\\",		snCHAR_SOUND_FIREWORM		},
	{ "Assets\\Audio\\Effects\\monster\\HellHound\\",		snCHAR_SOUND_HELLHOUND		},
	{ "Assets\\Audio\\Effects\\monster\\DarkGuard\\",		snCHAR_SOUND_DARKGUARD		},
	{ "Assets\\Audio\\Effects\\monster\\DarkMage\\",		snCHAR_SOUND_DARKMAGE		},

	{ "Assets\\Audio\\Effects\\monster\\MonMokova\\",		snCHAR_SOUND_MOKOVA			},
	{ "Assets\\Audio\\Effects\\monster\\MonTempleguard\\",snCHAR_SOUND_TEMPLEGUARD	},
	{ "Assets\\Audio\\Effects\\monster\\MonSeto\\",		snCHAR_SOUND_SETO			},
	{ "Assets\\Audio\\Effects\\monster\\MonKingSpider\\",	snCHAR_SOUND_KINGSPIDER		},


	{ "Assets\\Audio\\Effects\\monster\\d_kn\\",			snCHAR_SOUND_REVIVED_KNIGHT	},
	{ "Assets\\Audio\\Effects\\monster\\d_magi\\",		snCHAR_SOUND_REVIVED_MAGICIAN },
	{ "Assets\\Audio\\Effects\\monster\\d_atal\\",		snCHAR_SOUND_REVIVED_ATALANTA },
	{ "Assets\\Audio\\Effects\\monster\\d_fi\\",			snCHAR_SOUND_REVIVED_FIGTHER },
	{ "Assets\\Audio\\Effects\\monster\\d_ar\\",			snCHAR_SOUND_REVIVED_ARCHER	},
	{ "Assets\\Audio\\Effects\\monster\\d_meca\\",		snCHAR_SOUND_REVIVED_MECANICIAN },
	{ "Assets\\Audio\\Effects\\monster\\d_pa\\",			snCHAR_SOUND_REVIVED_PIKEMAN },
	{ "Assets\\Audio\\Effects\\monster\\d_pr\\",			snCHAR_SOUND_REVIVED_PRIESTESS },
	{ "Assets\\Audio\\Effects\\monster\\deadhopt\\",		snCHAR_SOUND_DEADHOPT },
	{ "Assets\\Audio\\Effects\\monster\\deadkinghopy\\",	snCHAR_SOUND_DEADKINGHOPY },
	{ "Assets\\Audio\\Effects\\monster\\gorgon\\",		snCHAR_SOUND_GORGON},
	{ "Assets\\Audio\\Effects\\monster\\hobogolem\\",		snCHAR_SOUND_HOBOGOLEM},


	{ "Assets\\Audio\\Effects\\monster\\Niken\\",			snCHAR_SOUND_NIKEN			},
	{ "Assets\\Audio\\Effects\\monster\\Mimic\\",			snCHAR_SOUND_MIMIC			},
	{ "Assets\\Audio\\Effects\\monster\\KingBat\\",		snCHAR_SOUND_KINGBAT		},
	{ "Assets\\Audio\\Effects\\monster\\GoblinShaman\\",	snCHAR_SOUND_GOBLINSHAMAN	},
	{ "Assets\\Audio\\Effects\\monster\\Hest\\",			snCHAR_SOUND_HEST			},


	{ "Assets\\Audio\\Effects\\monster\\Ruca\\",			snCHAR_SOUND_RUCA			},
	{ "Assets\\Audio\\Effects\\monster\\NazSenior\\",		snCHAR_SOUND_NAZSENIOR		},
	{ "Assets\\Audio\\Effects\\monster\\Igolation\\",		snCHAR_SOUND_IGOLATION		},
	{ "Assets\\Audio\\Effects\\monster\\Kakoa\\",			snCHAR_SOUND_KAKOA			},
	{ "Assets\\Audio\\Effects\\monster\\Sprin\\",			snCHAR_SOUND_SPRIN			},
	{ "Assets\\Audio\\Effects\\monster\\UndeadMaple\\",	snCHAR_SOUND_UNDEADMAPLE	},
	{ "Assets\\Audio\\Effects\\monster\\Xetan\\",			snCHAR_SOUND_XETAN			},



	{ "Assets\\Audio\\Effects\\monster\\Bebechick\\",			snCHAR_SOUND_BEBECHICK		},
	{ "Assets\\Audio\\Effects\\monster\\PaPachick\\",			snCHAR_SOUND_PAPACHICK		},


	{ "Assets\\Audio\\Effects\\npc\\morif\\",				snCHAR_SOUND_NPC_MORIF	},
	{ "Assets\\Audio\\Effects\\npc\\mollywolf\\",			snCHAR_SOUND_NPC_MOLLYWOLF	},
	{ "Assets\\Audio\\Effects\\npc\\SkillMaster\\",		snCHAR_SOUND_NPC_SKILLMASTER	},
	{ "Assets\\Audio\\Effects\\npc\\MagicMaster\\",		snCHAR_SOUND_NPC_MAGICMASTER	},
	{ "Assets\\Audio\\Effects\\npc\\worldcup\\",			snCHAR_SOUND_WORLDCUP		},


	{ "Assets\\Audio\\Effects\\npc\\castledoor\\",	snCHAR_SOUND_CASTLE_DOOR		},
	{ "Assets\\Audio\\Effects\\npc\\crystal_r\\",		snCHAR_SOUND_CASTLE_CRYSTAL_R	},
	{ "Assets\\Audio\\Effects\\npc\\crystal_g\\",		snCHAR_SOUND_CASTLE_CRYSTAL_G	},
	{ "Assets\\Audio\\Effects\\npc\\crystal_b\\",		snCHAR_SOUND_CASTLE_CRYSTAL_B	},
	{ "Assets\\Audio\\Effects\\npc\\crystal_n\\",		snCHAR_SOUND_CASTLE_CRYSTAL_N	},
	{ "Assets\\Audio\\Effects\\npc\\tower-b\\",		snCHAR_SOUND_CASTLE_TOWER_B		},

	{ "Assets\\Audio\\Effects\\npc\\Soldier_A\\",		snCHAR_SOUND_CASTLE_SOLDER_A	},
	{ "Assets\\Audio\\Effects\\npc\\Soldier_B\\",		snCHAR_SOUND_CASTLE_SOLDER_B	},
	{ "Assets\\Audio\\Effects\\npc\\Soldier_C\\",		snCHAR_SOUND_CASTLE_SOLDER_C	},



	{ "Assets\\Audio\\Effects\\monster\\wolverin\\"		,	snCHAR_SOUND_S_WOLVERLIN	},
	{ "Assets\\Audio\\Effects\\monster\\MetalGolem\\"		,	snCHAR_SOUND_S_METALGOLEM	},
	{ "Assets\\Audio\\Effects\\monster\\Figon\\"			,	snCHAR_SOUND_S_F_ELEMENTAL	},



	{ "Assets\\Audio\\Effects\\player\\fighter\\"		,	snCHAR_SOUND_FIGHTER	},
	{ "Assets\\Audio\\Effects\\player\\Mechanician\\"	,	snCHAR_SOUND_MECHANICAN	},
	{ "Assets\\Audio\\Effects\\player\\archer\\"		,	snCHAR_SOUND_ARCHER		},
	{ "Assets\\Audio\\Effects\\player\\pikeman\\"		,	snCHAR_SOUND_PIKEMAN	},


	{ "Assets\\Audio\\Effects\\player\\Knight\\"		,	snCHAR_SOUND_KNIGHT		},
	{ "Assets\\Audio\\Effects\\player\\Atalanta\\"	,	snCHAR_SOUND_ATALANTA	},
	{ "Assets\\Audio\\Effects\\player\\Priestess\\"	,	snCHAR_SOUND_PRIESTESS	},
	{ "Assets\\Audio\\Effects\\player\\Magician\\"	,	snCHAR_SOUND_MAGICIAN	},


	{ "Assets\\Audio\\Effects\\monster\\Watermelon\\",	snCHAR_SOUND_WATERMELON	}

};








char *szSndWeaponPath = "Assets\\Audio\\Effects\\weapon\\";

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
	"Assets\\Audio\\Effects\\FootSteps\\step01.wav",
	"Assets\\Audio\\Effects\\FootSteps\\step02.wav",
	"Assets\\Audio\\Effects\\FootSteps\\stonerun1.wav",
	"Assets\\Audio\\Effects\\FootSteps\\stonerun2.wav",
	"Assets\\Audio\\Effects\\FootSteps\\stonerun3.wav",
	"Assets\\Audio\\Ambient\\stone-mill.wav",
	"Assets\\Audio\\Effects\\event\\fieldstart.wav",
	"Assets\\Audio\\Effects\\event\\level UP.wav",
	"Assets\\Audio\\Effects\\event\\hosound.wav",
	"Assets\\Audio\\Ambient\\tempskron-town.wav",

	"Assets\\Audio\\Effects\\monster\\Figon\\impact 1.wav",
	"Assets\\Audio\\Effects\\FootSteps\\stone-dun1.wav",
	"Assets\\Audio\\Effects\\FootSteps\\stone-dun2.wav",
	"Assets\\Audio\\Effects\\FootSteps\\stone-dun3.wav",

	"Assets\\Audio\\Effects\\FootSteps\\inwater 1.wav",
	"Assets\\Audio\\Effects\\FootSteps\\inwater 2.wav",
	"Assets\\Audio\\Effects\\FootSteps\\inwater 3.wav",

	"Assets\\Audio\\Effects\\FootSteps\\inwater 3.wav",
	"Assets\\Audio\\Sod\\turn.wav",

	"Assets\\Audio\\Sod\\SOD-item.wav",

	"Assets\\Audio\\Effects\\Menu\\Event\\meteo 1.wav",
	"Assets\\Audio\\Effects\\Menu\\Event\\meteo 2.wav",
	"Assets\\Audio\\Effects\\Event\\sheltom_b.wav",
	"Assets\\Audio\\Effects\\Event\\firecracker01.wav",
	"Assets\\Audio\\Effects\\Event\\firecracker02.wav",
	"Assets\\Audio\\Effects\\Event\\firecracker03.wav",

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
	"Assets\\Audio\\Ambient\\tempskron-town.wav",
	"Assets\\Audio\\Ambient\\forest-day.wav",
	"Assets\\Audio\\Ambient\\forest-night.wav",
	"Assets\\Audio\\Ambient\\ruin wind.wav",
	"Assets\\Audio\\Ambient\\desert wind.wav",
	"Assets\\Audio\\Ambient\\dungeon.wav",

	"Assets\\Audio\\Ambient\\temple_amb.wav",
	"Assets\\Audio\\Ambient\\cave_amb.wav",
	"Assets\\Audio\\Ambient\\darksanc_amb.wav",

	"Assets\\Audio\\Ambient\\iron_amb.wav",
	"Assets\\Audio\\Ambient\\iron_amb2.wav",
	"Assets\\Audio\\Ambient\\Babel Approach.wav",
	"Assets\\Audio\\Ambient\\icewind.wav",

	0
};

struct	sSKILL_SOUND_FILE
{
	char	*szFile;
	DWORD	dwCode;
};

int	SkillSoundNum = 0;

sSKILL_SOUND_FILE	SkillSoundWav[] = {
	{	"Assets\\Audio\\Effects\\Skill\\Learn_Skill.wav",							SKILL_SOUND_LEARN	},

	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Extreme_Shield 01.wav",		SKILL_SOUND_EXTREME_SHIELD	},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Jumping_Crash 01.wav",			SKILL_SOUND_JUMPING_CRASH1	},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Jumping_Crash 02.wav",			SKILL_SOUND_JUMPING_CRASH2	},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Mechanic_Bomb 01.wav",			SKILL_SOUND_MECHANIC_BOMB1	},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Mechanic_Bomb 02.wav",			SKILL_SOUND_MECHANIC_BOMB2	},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Perfect Aim 01.wav",			SKILL_SOUND_PERFECT_AIM	},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Physical_Absorption 01.wav",	SKILL_SOUND_PHYSICAL_ABSORB1	},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Physical_Absorption 02.wav",	SKILL_SOUND_PHYSICAL_ABSORB2	},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Physical_Absorption 03.wav",	SKILL_SOUND_PHYSICAL_ABSORB3	},

	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Pike_Wind 01.wav",				SKILL_SOUND_PIKE_WIND	},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Scout_Hawk 01.wav",			SKILL_SOUND_SCOUT_HAWK1	},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Scout_Hawk 02.wav",			SKILL_SOUND_SCOUT_HAWK2	},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Wind_Arrow 01.wav",			SKILL_SOUND_WIND_ARROW	},

	{	"Assets\\Audio\\Effects\\Skill\\bow_skill_hit 01.wav",					SKILL_SOUND_ARROW_HIT1 },
	{	"Assets\\Audio\\Effects\\Skill\\bow_skill_hit 02.wav",					SKILL_SOUND_ARROW_HIT2 },

	{	"Assets\\Audio\\Effects\\Skill\\Skill_Swing 01.wav",						SKILL_SOUND_SKILL_SWING1 },
	{	"Assets\\Audio\\Effects\\Skill\\Skill_Swing 02.wav",						SKILL_SOUND_SKILL_SWING2 },

	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Automation 01.wav",			SKILL_SOUND_SKILL_AUTOMATION1 },
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Automation 02.wav",			SKILL_SOUND_SKILL_AUTOMATION2 },
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Automation 03.wav",			SKILL_SOUND_SKILL_AUTOMATION3 },

	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Maximize 01.wav",				SKILL_SOUND_SKILL_MAXIMIZE1 },
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Maximize 01.wav",				SKILL_SOUND_SKILL_MAXIMIZE2 },
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Maximize 01.wav",				SKILL_SOUND_SKILL_MAXIMIZE3 },

	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Spark 01.wav",					SKILL_SOUND_SKILL_SPARK1 },
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Spark 02.wav",					SKILL_SOUND_SKILL_SPARK2 },
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Spark 03.wav",					SKILL_SOUND_SKILL_SPARK3 },

	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Ground Pike 01.wav",			SKILL_SOUND_SKILL_GROUND_PIKE },
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Tornado 01.wav",				SKILL_SOUND_SKILL_TORNADO1 },

	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Falcon 02.wav",				SKILL_SOUND_SKILL_FALCON },
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Falcon Attack 01.wav",			SKILL_SOUND_SKILL_FALCON_ATTACK1 },
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Falcon Attack 02.wav",			SKILL_SOUND_SKILL_FALCON_ATTACK2 },

	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Avalanche 01.wav",				SKILL_SOUND_SKILL_AVALANCHE1 },
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Avalanche 02.wav",				SKILL_SOUND_SKILL_AVALANCHE2 },
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Avalanche 03.wav",				SKILL_SOUND_SKILL_AVALANCHE3 },

	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Expansion 01.wav",				SKILL_SOUND_SKILL_EXPANSION1 },
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Expansion 02.wav",				SKILL_SOUND_SKILL_EXPANSION2 },

	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\RoZ 01.wav",					SKILL_SOUND_SKILL_RAGE_OF_ZECRAM1 },
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\RoZ 02.wav",					SKILL_SOUND_SKILL_RAGE_OF_ZECRAM2 },
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\RoZ 04.wav",					SKILL_SOUND_SKILL_RAGE_OF_ZECRAM3 },


	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Roar 01.wav",					SKILL_SOUND_SKILL_ROAR1 },
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Roar 02.wav",					SKILL_SOUND_SKILL_ROAR2 },

	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\AofR 01.wav",					SKILL_SOUND_SKILL_ARROW_OF_RANGE },


	{	"Assets\\Audio\\Effects\\Skill\\Morion\\Casting_M.wav",					SKILL_SOUND_SKILL_CASTING_MAGICIAN },
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\Casting_P.wav",					SKILL_SOUND_SKILL_CASTING_PRIEST },

	{	"Assets\\Audio\\Effects\\Skill\\Morion\\Agony 1.wav",						SKILL_SOUND_SKILL_AGONY },
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\Farina 1.wav",					SKILL_SOUND_SKILL_FARINA },
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\FireBall 1.wav",					SKILL_SOUND_SKILL_FIREBALL1 },
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\FireBall 2.wav",					SKILL_SOUND_SKILL_FIREBALL2 },
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\FireBolt 1.wav",					SKILL_SOUND_SKILL_FIREBOLT1 },
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\FireBolt 2.wav",					SKILL_SOUND_SKILL_FIREBOLT2 },

	{	"Assets\\Audio\\Effects\\Skill\\Morion\\Healing 1.wav",					SKILL_SOUND_SKILL_HEALING },
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\HolyBody 1.wav",					SKILL_SOUND_SKILL_HOLYBODY },
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\HolyBolt 1.wav",					SKILL_SOUND_SKILL_HOLYBOLT },
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\HolyMind 1.wav",					SKILL_SOUND_SKILL_HOLYMIND },
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\MultiSpark 1.wav",				SKILL_SOUND_SKILL_MULTISPARK },
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\ShieldSpake 1.wav",				SKILL_SOUND_SKILL_SHIELDSTRIKE },
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\SwordBlast 1.wav",				SKILL_SOUND_SKILL_SWORDBLAST1 },
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\SwordBlast 2.wav",				SKILL_SOUND_SKILL_SWORDBLAST2 },
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\VigorSpear 1.wav",				SKILL_SOUND_SKILL_VIGORSPEAR },
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\Zenith 1.wav",					SKILL_SOUND_SKILL_ZENITH },



	{	"Assets\\Audio\\Effects\\Skill\\Morion\\HolyValor 1.wav",					SKILL_SOUND_SKILL_HOLY_VALOR1 },

	{	"Assets\\Audio\\Effects\\Skill\\Morion\\HolyValor 3.wav",					SKILL_SOUND_SKILL_HOLY_VALOR3 },


	{	"Assets\\Audio\\Effects\\Skill\\Morion\\Brandish 1.wav",					SKILL_SOUND_SKILL_BLANDISH1 },

	{	"Assets\\Audio\\Effects\\Skill\\Morion\\Brandish 2.wav",					SKILL_SOUND_SKILL_BLANDISH2 },


	{	"Assets\\Audio\\Effects\\Skill\\Morion\\Piercing 2.wav",					SKILL_SOUND_SKILL_PIERCING },


	{	"Assets\\Audio\\Effects\\Skill\\Morion\\DrasticSpirit 1.wav",				SKILL_SOUND_SKILL_DRASTICSPIRIT1 },

	{	"Assets\\Audio\\Effects\\Skill\\Morion\\DrasticSpirit 3.wav",				SKILL_SOUND_SKILL_DRASTICSPIRIT3 },




	{	"Assets\\Audio\\Effects\\Skill\\Morion\\Windy 1.wav",						SKILL_SOUND_SKILL_WINDY1 },

	{	"Assets\\Audio\\Effects\\Skill\\Morion\\Windy 3.wav",						SKILL_SOUND_SKILL_WINDY3 },


	{	"Assets\\Audio\\Effects\\Skill\\Morion\\TwistJavelin.wav",				SKILL_SOUND_SKILL_TWISTJAVELIN },


	{	"Assets\\Audio\\Effects\\Skill\\Morion\\SoulSucker 2.wav",				SKILL_SOUND_SKILL_SOULSUCKER2 },

	{	"Assets\\Audio\\Effects\\Skill\\Morion\\SoulSucker 3.wav",				SKILL_SOUND_SKILL_SOULSUCKER3 },

	{	"Assets\\Audio\\Effects\\Skill\\Morion\\SoulSucker 4.wav",				SKILL_SOUND_SKILL_SOULSUCKER4 },

	{	"Assets\\Audio\\Effects\\Skill\\Morion\\FireJavelin 1.wav",				SKILL_SOUND_SKILL_FIREJAVELIN },


	{	"Assets\\Audio\\Effects\\Skill\\Morion\\DivineLightning 1.wav",			SKILL_SOUND_SKILL_DIVINELIGHTNING1 },
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\DivineLightning 2.wav",			SKILL_SOUND_SKILL_DIVINELIGHTNING2 },
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\DivineLightning 3.wav",			SKILL_SOUND_SKILL_DIVINELIGHTNING3 },


	{	"Assets\\Audio\\Effects\\Skill\\Morion\\HolyReflection 1.wav",			SKILL_SOUND_SKILL_HOLYREFLECTION1 },

	{	"Assets\\Audio\\Effects\\Skill\\Morion\\HolyReflection 2.wav",			SKILL_SOUND_SKILL_HOLYREFLECTION2 },

	{	"Assets\\Audio\\Effects\\Skill\\Morion\\GrandHealing 1.wav",				SKILL_SOUND_SKILL_GRANDHEALING },


	{	"Assets\\Audio\\Effects\\Skill\\Morion\\Watornado 1.wav",					SKILL_SOUND_SKILL_WATORNADO1 },
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\Watornado 2.wav",					SKILL_SOUND_SKILL_WATORNADO2 },



	{	"Assets\\Audio\\Effects\\Skill\\Morion\\EnchantWpn_add_C 1.wav",			SKILL_SOUND_SKILL_ENCHANTWEAPON_ICE1  },
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\EnchantWpn_add_C 2.wav",			SKILL_SOUND_SKILL_ENCHANTWEAPON_ICE2 },

	{	"Assets\\Audio\\Effects\\Skill\\Morion\\EnchantWpn_add_F 1.wav",			SKILL_SOUND_SKILL_ENCHANTWEAPON_FIRE1  },
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\EnchantWpn_add_F 2.wav",			SKILL_SOUND_SKILL_ENCHANTWEAPON_FIRE2  },

	{	"Assets\\Audio\\Effects\\Skill\\Morion\\EnchantWpn_add_L 1.wav",			SKILL_SOUND_SKILL_ENCHANTWEAPON_LIGHTNING1  },
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\EnchantWpn_add_L 2.wav",			SKILL_SOUND_SKILL_ENCHANTWEAPON_LIGHTNING2  },

	{	"Assets\\Audio\\Effects\\Skill\\Morion\\EnchantWpn_cast.wav",				SKILL_SOUND_SKILL_ENCHANTWEAPON_CAST  },


	{	"Assets\\Audio\\Effects\\Skill\\Morion\\EnchantWpn_magic_L 1.wav",		SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_LIGHTNING1  },
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\EnchantWpn_magic_L 2.wav",		SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_LIGHTNING2 },


	{	"Assets\\Audio\\Effects\\Skill\\Morion\\EnchantWpn_magic_C 1.wav",		SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_ICE1  },
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\EnchantWpn_magic_C 2.wav",		SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_ICE2  },


	{	"Assets\\Audio\\Effects\\Skill\\Morion\\DeathRay 1.wav",					SKILL_SOUND_SKILL_DEATHRAY },




	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\AvengingCrash 01.wav",			SKILL_SOUND_SKILL_AVANGING_CRASH	},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\ElementalShot 01.wav",			SKILL_SOUND_SKILL_ELEMENTAL_SHOT	},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\BombShot 01.wav",				SKILL_SOUND_SKILL_BOMB_SHOT1		},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\BombShot 02.wav",				SKILL_SOUND_SKILL_BOMB_SHOT2		},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\BoneCrash 01.wav",				SKILL_SOUND_SKILL_BONE_CRASH1		},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\ChainLance 01.wav",			SKILL_SOUND_SKILL_CHAIN_LANCE1		},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\ChainLance 02.wav",			SKILL_SOUND_SKILL_CHAIN_LANCE2		},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\ChainLance 03.wav",			SKILL_SOUND_SKILL_CHAIN_LANCE3		},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Concentration 01.wav",			SKILL_SOUND_SKILL_CONCENTRATION1	},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Concentration 02.wav",			SKILL_SOUND_SKILL_CONCENTRATION2	},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\GoldFalcon 02.wav",			SKILL_SOUND_SKILL_GOLDEN_FALCON		},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\MetalArmor 01.wav",			SKILL_SOUND_SKILL_METAL_ARMOR		},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Perforation 01.wav",			SKILL_SOUND_SKILL_PERFORATION		},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\SparkShield 02.wav",			SKILL_SOUND_SKILL_SPARK_SHIELD		},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\SwiftAxe 01.wav",				SKILL_SOUND_SKILL_SWIFT_AXE1		},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\SwiftAxe 02.wav",				SKILL_SOUND_SKILL_SWIFT_AXE2		},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\VenomSpear 01.wav",			SKILL_SOUND_SKILL_VENOM_SPEAR1		},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\VenomSpear 02.wav",			SKILL_SOUND_SKILL_VENOM_SPEAR2		},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\vanish 01.wav",				SKILL_SOUND_SKILL_VANISH1			},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\vanish 02.wav",				SKILL_SOUND_SKILL_VANISH2			},



	{	"Assets\\Audio\\Effects\\Skill\\Morion\\DancingSword 1.wav",				SKILL_SOUND_SKILL_DANCING_SWORD		},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\DancingSword_atk_1.wav",			SKILL_SOUND_SKILL_DANCING_SWORD_ATK1},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\DancingSword_atk_2.wav",			SKILL_SOUND_SKILL_DANCING_SWORD_ATK2},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\Diastrophism 2.wav",				SKILL_SOUND_SKILL_DIASTROPHISM		},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\DivineInhalation 1.wav",			SKILL_SOUND_SKILL_DIVINE_INHALATION	},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\EnergyShield 1.wav",				SKILL_SOUND_SKILL_ENERGY_SHIELD		},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\Extinct 1.wav",					SKILL_SOUND_SKILL_EXTINTION			},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\FlameBrandish 2.wav",				SKILL_SOUND_SKILL_FLAME_BRANDISH	},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\GrandCross 2.wav",				SKILL_SOUND_SKILL_GRAND_CROSS		},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\Holy Incantation 1.wav",			SKILL_SOUND_SKILL_HOLY_INCANTATION	},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\LightningJavelin 1.wav",			SKILL_SOUND_SKILL_LIGHTNING_JAVELIN1},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\LightningJavelin 2.wav",			SKILL_SOUND_SKILL_LIGHTNING_JAVELIN2},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\Resurrection 2.wav",				SKILL_SOUND_SKILL_RESURRECTION		},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\SpiritElemental 1.wav",			SKILL_SOUND_SKILL_SPIRIT_ELEMENTAL	},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\SplitJavelin 1.wav",				SKILL_SOUND_SKILL_SPLIT_JAVELIN1	},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\SplitJavelin 2.wav",				SKILL_SOUND_SKILL_SPLIT_JAVELIN2	},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\StormJavelin 1.wav",				SKILL_SOUND_SKILL_STORM_JAVELIN1	},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\StormJavelin 2.wav",				SKILL_SOUND_SKILL_STORM_JAVELIN2	},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\TriumphofValhalla 1.wav",			SKILL_SOUND_SKILL_TRIUMPH_OF_VALHALLA1	},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\TriumphofValhalla 3.wav",			SKILL_SOUND_SKILL_TRIUMPH_OF_VALHALLA2  },
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\VigorBall 1.wav",					SKILL_SOUND_SKILL_VIGOR_BALL1		},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\VigorBall 2.wav",					SKILL_SOUND_SKILL_VIGOR_BALL2		},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\VirtualLife 1.wav",				SKILL_SOUND_SKILL_VIRTUAL_LIFE		},



	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\AssassinEye 01.wav",			SKILL_SOUND_SKILL_ASSASSIN_EYE		},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Berserker 01.wav",				SKILL_SOUND_SKILL_BERSERKER			},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Charging 01.wav",				SKILL_SOUND_SKILL_CHARGING			},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\ChargingStrike 03.wav",		SKILL_SOUND_SKILL_CHARGING_STRIKE	},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Compulsion 01.wav",			SKILL_SOUND_SKILL_COMPULSION1		},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Compulsion 05.wav",			SKILL_SOUND_SKILL_COMPULSION2		},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\Compulsion 06.wav",			SKILL_SOUND_SKILL_COMPULSION3		},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\CycloneStrike 01.wav",			SKILL_SOUND_SKILL_CYCLONE_STRIKE	},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\ForceOfNature 01.wav",			SKILL_SOUND_SKILL_FORCE_OF_NATURE	},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\GodsBless 01.wav",				SKILL_SOUND_SKILL_GODS_BLESS		},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\GodlyShield 01.wav",			SKILL_SOUND_SKILL_GODLY_SHIELD		},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\impulsion 02.wav",				SKILL_SOUND_SKILL_IMPULSION			},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\MetalGolem 01.wav",			SKILL_SOUND_SKILL_METAL_GOLEM		},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\PhoenixShot 01.wav",			SKILL_SOUND_SKILL_PHOENIX_SHOT		},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\ReCallWolverin 01.wav",		SKILL_SOUND_SKILL_RECALL_WOLVERIN	},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\ShadowStrike 01.wav",			SKILL_SOUND_SKILL_SHADOW_STRIKE1	},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\ShadowStrike 02.wav",			SKILL_SOUND_SKILL_SHADOW_STRIKE2	},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\ShadowStrike 03.wav",			SKILL_SOUND_SKILL_SHADOW_STRIKE3	},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\ShadowStrikeFinish 01.wav",	SKILL_SOUND_SKILL_SHADOW_STRIKE4	},
	{	"Assets\\Audio\\Effects\\Skill\\Tempskron\\vague 01.wav",					SKILL_SOUND_SKILL_VAGUE				},


	{	"Assets\\Audio\\Effects\\Skill\\Morion\\ChainLightning 01.wav",			SKILL_SOUND_SKILL_CHAIN_LIGHTNING1	},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\ChainLightning 02.wav",			SKILL_SOUND_SKILL_CHAIN_LIGHTNING2	},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\Distortion 01.wav",				SKILL_SOUND_SKILL_DISTORTION		},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\DIvinePiercing 07.wav",			SKILL_SOUND_SKILL_DVINE_PIERCING	},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\eXtremeRage 01.wav",				SKILL_SOUND_SKILL_EXTREM_RAGE1		},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\eXtremeRage 02.wav",				SKILL_SOUND_SKILL_EXTREM_RAGE2		},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\eXtremeRage 03.wav",				SKILL_SOUND_SKILL_EXTREM_RAGE3		},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\FireElemental 01.wav",			SKILL_SOUND_SKILL_FIRE_ELEMENTAL	},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\FlameWave 01.wav",				SKILL_SOUND_SKILL_FLAME_WAVE1		},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\FlameWave 02.wav",				SKILL_SOUND_SKILL_FLAME_WAVE2		},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\FlameWaveA 01.wav",				SKILL_SOUND_SKILL_FLAME_WAVE3		},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\FrostJavelin 01.wav",				SKILL_SOUND_SKILL_FROST_JAVELIN		},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\GlacialSpike 01.wav",				SKILL_SOUND_SKILL_GLACIAL_SPIKE1	},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\GlacialSpike 02.wav",				SKILL_SOUND_SKILL_GLACIAL_SPIKE2	},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\HallOfValhalla 01.wav",			SKILL_SOUND_SKILL_HALL_OF_VALHALLA	},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\Meteo 01.wav",					SKILL_SOUND_SKILL_METEO1			},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\Meteo 02.wav",					SKILL_SOUND_SKILL_METEO2			},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\Meteo 03.wav",					SKILL_SOUND_SKILL_METEO3			},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\Muspell 01.wav",					SKILL_SOUND_SKILL_MUSPELL1			},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\Muspell 02.wav",					SKILL_SOUND_SKILL_MUSPELL2			},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\RegenField 01.wav",				SKILL_SOUND_SKILL_REGEN_FIELD1		},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\RegenField 02.wav",				SKILL_SOUND_SKILL_REGEN_FIELD2		},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\SwordofJustice 01.wav",			SKILL_SOUND_SKILL_SWORD_OF_JUSTICE	},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\Vengeance 01.wav",				SKILL_SOUND_SKILL_VENGEANCE1		},
	{	"Assets\\Audio\\Effects\\Skill\\Morion\\Vengeance 02.wav",				SKILL_SOUND_SKILL_VENGEANCE2		},

	{	0,0 }
};




int	InitSoundEffect(HWND hWnd)
{
	
	return TRUE;
}



int CloseSoundEffect()
{

	TermDX_Wav2();

	return TRUE;
}



int	sinPlaySound(int Num, int Volume)
{

	PlayWav2(sinSoundNum + Num, 0, Volume, 2205);

	return TRUE;
}




int	esPlaySound(int Num, int Volume)
{

	PlayWav2(esSoundNum + Num, 0, Volume, 2205);

	return TRUE;
}


int	esPlaySound(int Num, int Volume, int SampleRate)
{

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
	"Assets\\Audio\\Ambient\\stone-mill.wav",

	"Assets\\Audio\\Ambient\\dungeon_pumping_b.wav",
	"Assets\\Audio\\Ambient\\dungeon_pumping_l.wav",
	"Assets\\Audio\\Ambient\\dungeon_spin_b.wav",
	"Assets\\Audio\\Ambient\\lake 1.wav",
	"Assets\\Audio\\Ambient\\mystic 1.wav",
	"Assets\\Audio\\Ambient\\mystic 2.wav",
	"Assets\\Audio\\Ambient\\ship_swaing_l.wav",
	"Assets\\Audio\\Ambient\\stream.wav",
	"Assets\\Audio\\Ambient\\town_bell 1.wav",
	"Assets\\Audio\\Ambient\\town_bell 2.wav",
	"Assets\\Audio\\Ambient\\town_spin_b.wav",
	"Assets\\Audio\\Ambient\\town_spin_l.wav",
	"Assets\\Audio\\Ambient\\waterfall.wav",
	"Assets\\Audio\\Ambient\\stone-mill2.wav",

	"Assets\\Audio\\Ambient\\watermill 1.wav",
	"Assets\\Audio\\Ambient\\windmill 1.wav",
	"Assets\\Audio\\Ambient\\windmill 2.wav",
	"Assets\\Audio\\Ambient\\windmill 3.wav",
	"Assets\\Audio\\Ambient\\windmill 4.wav",
	"Assets\\Audio\\Ambient\\owl 1.wav",

	"Assets\\Audio\\Ambient\\dungeon_big-bolt 1.wav",
	"Assets\\Audio\\Ambient\\dungeon_stonepole.wav",
	"Assets\\Audio\\Ambient\\zombiemill 1.wav",
	"Assets\\Audio\\Ambient\\dungeon_weight.wav",
	"Assets\\Audio\\Ambient\\dungeon_device_side.wav",
	"Assets\\Audio\\Ambient\\dungeon_device_axe.wav",
	"Assets\\Audio\\Ambient\\dungeon_cage 1.wav",

	0
};



char *szSodSound[] = {
	"Assets\\Audio\\Sod\\start.wav",
	"Assets\\Audio\\Sod\\round1.wav",
	"Assets\\Audio\\Sod\\round2.wav",
	"Assets\\Audio\\Sod\\round3.wav",
	"Assets\\Audio\\Sod\\round4.wav",
	"Assets\\Audio\\Sod\\round5.wav",
	"Assets\\Audio\\Sod\\round6.wav",
	"Assets\\Audio\\Sod\\round7.wav",
	"Assets\\Audio\\Sod\\round8.wav",
	"Assets\\Audio\\Sod\\round9.wav",
	"Assets\\Audio\\Sod\\stage.wav",
	"Assets\\Audio\\Sod\\complete.wav",
	"Assets\\Audio\\Sod\\fail.wav",
	"Assets\\Audio\\Sod\\congratulation.wav",


	"Assets\\Audio\\Sod\\BGM\\Stage_Complete.wav",
	"Assets\\Audio\\Sod\\BGM\\Stage_Fail.wav",
	"Assets\\Audio\\Sod\\BGM\\Ending.wav",

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
	"Assets\\Audio\\bgm\\Field - Desert - Pilgrim.bgm",
	"Assets\\Audio\\bgm\\Town - Tempskron_Stronghold.bgm",
	"Assets\\Audio\\bgm\\Town 1 - Tempskron_Ricarten - When wind comes-o.bgm",
	"Assets\\Audio\\bgm\\wind loop.bgm",
	"Assets\\Audio\\bgm\\Field - Forest - DarkWood.bgm",
	"Assets\\Audio\\bgm\\Dungeon - Gloomy Heart.bgm",
	"Assets\\Audio\\bgm\\Town 2 - Morion_Philliy - Voyage above the Clouds.bgm",


	"Assets\\Audio\\Sod\\BGM\\Stage_Play1.bgm",
	"Assets\\Audio\\Sod\\BGM\\Stage_Play1.bgm",
	"Assets\\Audio\\Sod\\BGM\\Stage_Play3.bgm",
	"Assets\\Audio\\bgm\\Field - Desert - Pilgrim.bgm",
	"Assets\\Audio\\bgm\\Ice 1.bgm",

	NULL
};



int	NextMusicNum;
DWORD	dwFadeStartTime = 0;
int LastMusicVolume;
int	PlayingBgmNum = -1;



int PlayBGM_Direct(int MusicNum)
{
	return TRUE;
}



int ChangeBGM(int MusicNum)
{

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




const char *TALK_SOUND_DIRECOTRY = { "Assets\\Audio\\Talk\\" };

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




