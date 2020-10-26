#ifndef	_FILEREAD_HEADER

#define	_FILEREAD_HEADER


extern smCONFIG	smConfig;


smCONFIG *smConfigDecode(char *iniFile);


int ReadCustomCracker(char *szCrackFile, TRANS_FIND_CRACKER *lpTransFindCrack);



int smModelDecode(char *iniFile, smMODELINFO *Info);


int smCharDecode(char *szCharFile, smCHAR_INFO *lpCharInfo, smCHAR_MONSTER_INFO	*lpMonInfo, char *lpDialogMessage = 0, size_t DialogMessageSize = 0);

extern char	szShotCutMessage[10][100];



struct rsSTG_MONSTER
{
	char	szMonsterName[32];
	int		OpenPercentage;

	smCHAR_INFO	*lpCharInfo;
	int		NumOpenStart;
};

#define rsSTG_MONSTER_MAX	50
#define rsBOSS_MONSTER_MAX	16

struct sBOSS_MONSTER
{
	smCHAR_INFO		*MasterMonster;
	smCHAR_INFO		*SlaveMonster;
	int				SlaveCount;
	BYTE			bOpenTime[32];
	int				OpenTimeCount;
};

struct	rsSTG_MONSTER_LIST
{

	rsSTG_MONSTER	rsMonster[rsSTG_MONSTER_MAX];

	int		PecetageCount;
	int		Counter;
	int		LimitMax;
	int		OpenInterval;
	int		OpenLimit;
	DWORD	dwIntervalTime;

	sBOSS_MONSTER	sBossMonsters[rsBOSS_MONSTER_MAX];
	int	BossMonsterCount;

};


#define SPECIAL_JOB_RANDOM_MAX			12


struct	sDEF_ITEMINFO
{

	sITEMINFO Item;

	short	sDurability[2];
	short	sResistance[8][2];
	short	sDamage[4];
	short	sAttack_Rating[2];
	short	sDefence[2];
	float	fBlock_Rating[2];
	float	fAbsorb[2];
	float	fSpeed[2];
	int		Increase_Life[2];
	int		Increase_Mana[2];
	int		Increase_Stamina[2];

	float	fMana_Regen[2];
	float	fLife_Regen[2];
	float	fStamina_Regen[2];



	short	sSpecial_Defence[2];
	float	fSpecial_Absorb[2];
	float	fSpecial_fSpeed[2];

	float	fSpecial_Magic_Mastery[2];
	float	fSpecial_Mana_Regen[2];

	int     Lev_Attack_Rating[2];

	DWORD	dwJobBitCode_Random[SPECIAL_JOB_RANDOM_MAX];
	int		JobBitCodeRandomCount;



	short	sGenDay[2];

	BYTE	*DefCompressData[sizeof(sITEMINFO)];
	int		DefCompressDataLen;
};


struct JOBNAME_BIT
{
	char *szName;
	DWORD dwBitMask;
};

extern JOBNAME_BIT BitMaskJobNames[];



int DecodeOpenMonster(char *szCharFile, rsSTG_MONSTER_LIST *lpStgMonList, smCHAR_INFO *lpCharInfoList, int ListCnt);

int DecodeItemInfo(char *szItemFile, sDEF_ITEMINFO *lpDefItem);

int CreateDefItem(sITEMINFO *lpItem, sDEF_ITEMINFO *lpDefItem, int SpJobCode = 0);
int CreateItemPerf(sITEMINFO* lpItem, sDEF_ITEMINFO* lpDefItem, int SpJobCode);

int CreateDefItem(sITEMINFO *lpItem, sDEF_ITEMINFO *lpDefItem, int SpJobCode, int ItemNormam);


int SetLowerItem(sDEF_ITEMINFO *lpDefItem);


float GetRandomFloatPos(float Min, float Max);
int GetRandomPos(int Min, int Max);


int	Open_SODConfig(char *szFileName, void *lphCoreMonster, int *SodTax, char *szSodText, size_t szSodTextSize, int *SodScoreDiv);


#define		JOB_CODE_MECHANICIAN		0x00000001	
#define		JOB_CODE_FIGHTER			0x00000002	
#define		JOB_CODE_PIKEMAN			0x00000004	
#define		JOB_CODE_ARCHER				0x00000008	

#define		JOB_CODE_MECHANICMASTER		0x00000010	
#define		JOB_CODE_WARRIOR			0x00000020
#define		JOB_CODE_COMBATANT			0x00000040
#define		JOB_CODE_HUNTERMASTER		0x00000080

#define		JOB_CODE_METALLEADER		0x00000100	
#define		JOB_CODE_CHAMPION			0x00000200
#define		JOB_CODE_LANCER				0x00000400
#define		JOB_CODE_DIONS_DISCIPLE		0x00000800

#define		JOB_CODE_HEAVYMETAL			0x00001000	
#define		JOB_CODE_IMMORTALWARRIOR	0x00002000	
#define		JOB_CODE_LANCELOT			0x00004000
#define		JOB_CODE_SAGITTARION		0x00008000


#define		JOB_CODE_KNIGHT				0x00010000
#define		JOB_CODE_ATALANTA			0x00020000
#define		JOB_CODE_PRIEST				0x00040000
#define		JOB_CODE_MAGICIAN			0x00080000

#define		JOB_CODE_PALADIN			0x00100000
#define		JOB_CODE_VALKYRIE			0x00200000
#define		JOB_CODE_SAINTESS			0x00400000
#define		JOB_CODE_WIZARD				0x00800000

#define		JOB_CODE_HOLYKNIGHT			0x01000000
#define		JOB_CODE_BRUNHILD			0x02000000
#define		JOB_CODE_BISHOP				0x04000000
#define		JOB_CODE_ROYALKNIGHT		0x08000000

#define		JOB_CODE_SAINTKNIGHT		0x10000000
#define		JOB_CODE_VALHALLA			0x20000000
#define		JOB_CODE_CELESTIAL			0x40000000
#define		JOB_CODE_ARCHMAGE			0x80000000

#define     JOB_CODE_ASSASSIN           0x0000000A
#define		JOB_CODE_ROGUE      		0x000000A0
#define		JOB_CODE_SHADOW      		0x00000A00
#define		JOB_CODE_SHADOW_WALKER		0x0000A000

#define		JOB_CODE_METALRAGE			0x00001001
#define		JOB_CODE_WARLORD	        0x00002002	
#define		JOB_CODE_BAYLOLUNT			0x00003003
#define		JOB_CODE_ISKAR      		0x00004004
#define		JOB_CODE_SHADOW_MASTER		0x0000A005

#define		JOB_CODE_SHAMAN  			0x000A0000
#define		JOB_CODE_SUMMONER			0x00A00000
#define		JOB_CODE_HIGH_SUMMONER		0x0A000000
#define		JOB_CODE_SOUL_CATCHER		0xA0000000

#define		JOB_CODE_VALIANT			0x10010000		
#define		JOB_CODE_QUEEN_OF_VALHALA	0x20020000	
#define		JOB_CODE_ARC_ANGEL			0x30030000		
#define		JOB_CODE_ELEMENTAL_MASTER	0x40040000
#define		JOB_CODE_SOUL_MASTER		0xA0050000



#define		BROOD_CODE_TEMPSKRON			1
#define		BROOD_CODE_MORAYION				2
#define		BROOD_CODE_SOPPHETIO			4


struct	JOB_DATA_CODE
{
	char	*szName;
	char	*szName2;
	DWORD	JobBitCode;
	DWORD	JobCode;
	DWORD	Brood;

	int     Sight;
	int     LifeFunction;
	int     ManaFunction;
	int     StaminaFunction;
	short   DamageFunction[3];
};


struct	SKILL_DATA_CODE
{
	char	*szSkillName;
	int		dwPlaySkillCode;
};

extern	JOB_DATA_CODE	JobDataBase[];
extern	SKILL_DATA_CODE	SkillDataCode[];


JOB_DATA_CODE	*GetJobDataCode(DWORD BaseJob, int	JobCnt);

extern int NotItemSpecial;

#endif
