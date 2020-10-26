
#define SIN_MAX_SKILL			182		
#define SIN_MAX_USE_SKILL		17			
#define SIN_MAX_SKILLBOX		17

#define	sinSKILL_MASK1	0xFF000000			
#define	sinSKILL_MASK2	0xFFFF0000
#define	sinSKILL_MASK3	0x0000FFFF

#define SKILL_ALL_WEAPON_USE	0x11000000  




#define GROUP_MECHANICIAN		0x01000000
#define GROUP_FIGHTER			0x02000000
#define GROUP_PIKEMAN			0x03000000
#define	GROUP_ARCHER			0x04000000

#define GROUP_KNIGHT			0x05000000
#define GROUP_ATALANTA			0x06000000
#define GROUP_PRIESTESS			0x07000000
#define	GROUP_MAGICIAN			0x08000000
#define	GROUP_SHAMAN			0x0B000000
#define	GROUP_ASSASSINE			0x0A000000


#define	GROUP_OTHERSKILL		0x09000000
#define	GROUP_SKILL      		0x0A000000


#define	CHANGE_JOB1				0x00010000
#define	CHANGE_JOB2				0x00020000
#define	CHANGE_JOB3				0x00040000
#define	CHANGE_JOB4				0x00080000
#define	CHANGE_JOB5				0x00100000


#define SKILL_1					0x00000001
#define SKILL_2					0x00000002
#define SKILL_3					0x00000003
#define SKILL_4					0x00000004
#define SKILL_5					0x00000005
#define SKILL_6					0x00000006
#define SKILL_7					0x00000007
#define SKILL_8					0x00000008
#define SKILL_9					0x00000009
#define SKILL_10				0x00000010



#define SKILL_SWORD_BLAST		(GROUP_KNIGHT | CHANGE_JOB1 | SKILL_1)
#define SKILL_HOLY_BODY			(GROUP_KNIGHT | CHANGE_JOB1 | SKILL_2)
#define SKILL_PHYSICAL_TRANING	(GROUP_KNIGHT | CHANGE_JOB1 | SKILL_3)
#define SKILL_DOUBLE_CRASH		(GROUP_KNIGHT | CHANGE_JOB1 | SKILL_4)

#define SKILL_HOLY_VALOR		(GROUP_KNIGHT | CHANGE_JOB2 | SKILL_1)
#define SKILL_BRANDISH			(GROUP_KNIGHT | CHANGE_JOB2 | SKILL_2)
#define SKILL_PIERCING			(GROUP_KNIGHT | CHANGE_JOB2 | SKILL_3)
#define SKILL_DRASTIC_SPIRIT	(GROUP_KNIGHT | CHANGE_JOB2 | SKILL_4)

#define SKILL_SWORD_MASTERY 	(GROUP_KNIGHT | CHANGE_JOB3 | SKILL_1)
#define SKILL_DIVINE_INHALATION (GROUP_KNIGHT | CHANGE_JOB3 | SKILL_2)
#define SKILL_HOLY_INCANTATION  (GROUP_KNIGHT | CHANGE_JOB3 | SKILL_3)
#define SKILL_GRAND_CROSS		(GROUP_KNIGHT | CHANGE_JOB3 | SKILL_4)


#define SKILL_SWORD_OF_JUSTICE	(GROUP_KNIGHT | CHANGE_JOB4 | SKILL_1)
#define SKILL_GODLY_SHIELD	    (GROUP_KNIGHT | CHANGE_JOB4 | SKILL_2)
#define SKILL_GOD_BLESS		    (GROUP_KNIGHT | CHANGE_JOB4 | SKILL_3)
#define SKILL_DIVINE_PIERCING	(GROUP_KNIGHT | CHANGE_JOB4 | SKILL_4)

///TIER5

#define SKILL_SOUL_BREAKER	 	(GROUP_KNIGHT | CHANGE_JOB5 | SKILL_1)





#define SKILL_SHIELD_STRIKE		(GROUP_ATALANTA | CHANGE_JOB1 | SKILL_1)
#define SKILL_FARINA			(GROUP_ATALANTA | CHANGE_JOB1 | SKILL_2)
#define SKILL_THROWING_MASTERY	(GROUP_ATALANTA | CHANGE_JOB1 | SKILL_3)
#define SKILL_VIGOR_SPEAR		(GROUP_ATALANTA | CHANGE_JOB1 | SKILL_4)

#define SKILL_WINDY				(GROUP_ATALANTA | CHANGE_JOB2 | SKILL_1)
#define SKILL_TWIST_JAVELIN		(GROUP_ATALANTA | CHANGE_JOB2 | SKILL_2)
#define SKILL_SOUL_SUCKER		(GROUP_ATALANTA | CHANGE_JOB2 | SKILL_3)
#define SKILL_FIRE_JAVELIN		(GROUP_ATALANTA | CHANGE_JOB2 | SKILL_4)

#define SKILL_SPLIT_JAVELIN		(GROUP_ATALANTA | CHANGE_JOB3 | SKILL_1)
#define SKILL_TRIUMPH_OF_VALHALLA (GROUP_ATALANTA | CHANGE_JOB3 | SKILL_2)
#define SKILL_LIGHTNING_JAVELIN (GROUP_ATALANTA | CHANGE_JOB3 | SKILL_3)
#define SKILL_STORM_JAVELIN		(GROUP_ATALANTA | CHANGE_JOB3 | SKILL_4)


#define SKILL_HALL_OF_VALHALLA	(GROUP_ATALANTA | CHANGE_JOB4 | SKILL_1)
#define SKILL_X_RAGE			(GROUP_ATALANTA | CHANGE_JOB4 | SKILL_2)
#define SKILL_FROST_JAVELIN		(GROUP_ATALANTA | CHANGE_JOB4 | SKILL_3)
#define SKILL_VENGEANCE			(GROUP_ATALANTA | CHANGE_JOB4 | SKILL_4)




#define SKILL_HEALING			(GROUP_PRIESTESS | CHANGE_JOB1 | SKILL_1)
#define SKILL_HOLY_BOLT			(GROUP_PRIESTESS | CHANGE_JOB1 | SKILL_2)
#define SKILL_MULTISPARK		(GROUP_PRIESTESS | CHANGE_JOB1 | SKILL_3)
#define SKILL_HOLY_MIND			(GROUP_PRIESTESS | CHANGE_JOB1 | SKILL_4)

#define SKILL_MEDITATION		(GROUP_PRIESTESS | CHANGE_JOB2 | SKILL_1)
#define SKILL_DIVINE_LIGHTNING  (GROUP_PRIESTESS | CHANGE_JOB2 | SKILL_2)
#define SKILL_HOLY_REFLECTION	(GROUP_PRIESTESS | CHANGE_JOB2 | SKILL_3)
#define SKILL_GRAND_HEALING		(GROUP_PRIESTESS | CHANGE_JOB2 | SKILL_4)

#define SKILL_VIGOR_BALL		(GROUP_PRIESTESS | CHANGE_JOB3 | SKILL_1)
#define SKILL_RESURRECTION		(GROUP_PRIESTESS | CHANGE_JOB3 | SKILL_2)
#define SKILL_EXTINCTION		(GROUP_PRIESTESS | CHANGE_JOB3 | SKILL_3)
#define SKILL_VIRTUAL_LIFE		(GROUP_PRIESTESS | CHANGE_JOB3 | SKILL_4)


#define SKILL_GLACIAL_SPIKE		 (GROUP_PRIESTESS | CHANGE_JOB4 | SKILL_1)
#define SKILL_REGENERATION_FIELD (GROUP_PRIESTESS | CHANGE_JOB4 | SKILL_2)
#define SKILL_CHAIN_LIGHTNING	 (GROUP_PRIESTESS | CHANGE_JOB4 | SKILL_3)
#define SKILL_SUMMON_MUSPELL	 (GROUP_PRIESTESS | CHANGE_JOB4 | SKILL_4)




#define SKILL_AGONY				(GROUP_MAGICIAN | CHANGE_JOB1 | SKILL_1)
#define SKILL_FIRE_BOLT			(GROUP_MAGICIAN | CHANGE_JOB1 | SKILL_2)
#define SKILL_ZENITH			(GROUP_MAGICIAN | CHANGE_JOB1 | SKILL_3)
#define SKILL_FIRE_BALL			(GROUP_MAGICIAN | CHANGE_JOB1 | SKILL_4)

#define SKILL_MENTAL_MASTERY	(GROUP_MAGICIAN | CHANGE_JOB2 | SKILL_1)
#define SKILL_WATORNADO         (GROUP_MAGICIAN | CHANGE_JOB2 | SKILL_2)
#define SKILL_ENCHANT_WEAPON	(GROUP_MAGICIAN | CHANGE_JOB2 | SKILL_3)
#define SKILL_DEAD_RAY			(GROUP_MAGICIAN | CHANGE_JOB2 | SKILL_4)

#define SKILL_ENERGY_SHIELD		(GROUP_MAGICIAN | CHANGE_JOB3 | SKILL_1)
#define SKILL_DIASTROPHISM		(GROUP_MAGICIAN | CHANGE_JOB3 | SKILL_2)
#define SKILL_SPIRIT_ELEMENTAL	(GROUP_MAGICIAN | CHANGE_JOB3 | SKILL_3)
#define SKILL_DANCING_SWORD		(GROUP_MAGICIAN | CHANGE_JOB3 | SKILL_4)


#define SKILL_FIRE_ELEMENTAL	(GROUP_MAGICIAN | CHANGE_JOB4 | SKILL_1)
#define SKILL_FLAME_WAVE		(GROUP_MAGICIAN | CHANGE_JOB4 | SKILL_2)
#define SKILL_DISTORTION		(GROUP_MAGICIAN | CHANGE_JOB4 | SKILL_3)
#define SKILL_M_METEO			(GROUP_MAGICIAN | CHANGE_JOB4 | SKILL_4)



#define SKILL_NORMAL_ATTACK     0x11111111	


#define SKILL_EXTREME_SHIELD	(GROUP_MECHANICIAN | CHANGE_JOB1 | SKILL_1)
#define SKILL_MECHANIC_BOMB		(GROUP_MECHANICIAN | CHANGE_JOB1 | SKILL_2)
#define SKILL_PHYSICAL_ABSORB	(GROUP_MECHANICIAN | CHANGE_JOB1 | SKILL_3)
#define SKILL_POISON_ATTRIBUTE	(GROUP_MECHANICIAN | CHANGE_JOB1 | SKILL_4)

#define SKILL_GREAT_SMASH		(GROUP_MECHANICIAN | CHANGE_JOB2 | SKILL_1)
#define SKILL_MAXIMIZE			(GROUP_MECHANICIAN | CHANGE_JOB2 | SKILL_2)
#define SKILL_AUTOMATION		(GROUP_MECHANICIAN | CHANGE_JOB2 | SKILL_3)
#define SKILL_SPARK				(GROUP_MECHANICIAN | CHANGE_JOB2 | SKILL_4)

#define SKILL_METAL_ARMOR		(GROUP_MECHANICIAN | CHANGE_JOB3 | SKILL_1)
#define SKILL_GRAND_SMASH		(GROUP_MECHANICIAN | CHANGE_JOB3 | SKILL_2)
#define SKILL_MECHANIC_WEAPON	(GROUP_MECHANICIAN | CHANGE_JOB3 | SKILL_3)
#define SKILL_SPARK_SHIELD		(GROUP_MECHANICIAN | CHANGE_JOB3 | SKILL_4)


#define SKILL_IMPULSION			(GROUP_MECHANICIAN | CHANGE_JOB4 | SKILL_1)
#define SKILL_COMPULSION		(GROUP_MECHANICIAN | CHANGE_JOB4 | SKILL_2)
#define SKILL_MAGNETIC_SPHERE	(GROUP_MECHANICIAN | CHANGE_JOB4 | SKILL_3)
#define SKILL_METAL_GOLEM		(GROUP_MECHANICIAN | CHANGE_JOB4 | SKILL_4)


#define SKILL_MELEE_MASTERY		(GROUP_FIGHTER | CHANGE_JOB1 | SKILL_1)
#define SKILL_FIRE_ATTRIBUTE	(GROUP_FIGHTER | CHANGE_JOB1 | SKILL_2)
#define SKILL_RAVING			(GROUP_FIGHTER | CHANGE_JOB1 | SKILL_3)
#define SKILL_IMPACT			(GROUP_FIGHTER | CHANGE_JOB1 | SKILL_4)

#define SKILL_TRIPLE_IMPACT		(GROUP_FIGHTER | CHANGE_JOB2 | SKILL_1)
#define SKILL_BRUTAL_SWING		(GROUP_FIGHTER | CHANGE_JOB2 | SKILL_2)
#define SKILL_ROAR				(GROUP_FIGHTER | CHANGE_JOB2 | SKILL_3)
#define SKILL_RAGE_OF_ZECRAM	(GROUP_FIGHTER | CHANGE_JOB2 | SKILL_4)

#define SKILL_CONCENTRATION		(GROUP_FIGHTER | CHANGE_JOB3 | SKILL_1)
#define SKILL_AVANGING_CRASH	(GROUP_FIGHTER | CHANGE_JOB3 | SKILL_2)
#define SKILL_SWIFT_AXE			(GROUP_FIGHTER | CHANGE_JOB3 | SKILL_3)
#define SKILL_BONE_CRASH		(GROUP_FIGHTER | CHANGE_JOB3 | SKILL_4)


#define SKILL_DETORYER			(GROUP_FIGHTER | CHANGE_JOB4 | SKILL_1)
#define SKILL_BERSERKER			(GROUP_FIGHTER | CHANGE_JOB4 | SKILL_2)
#define SKILL_CYCLONE_STRIKE	(GROUP_FIGHTER | CHANGE_JOB4 | SKILL_3)
#define SKILL_BOOST_HEALTH		(GROUP_FIGHTER | CHANGE_JOB4 | SKILL_4)



#define SKILL_PIKE_WIND  		(GROUP_PIKEMAN | CHANGE_JOB1 | SKILL_1)
#define SKILL_ICE_ATTRIBUTE 	(GROUP_PIKEMAN | CHANGE_JOB1 | SKILL_2)
#define SKILL_CRITICAL_HIT      (GROUP_PIKEMAN | CHANGE_JOB1 | SKILL_3)
#define SKILL_JUMPING_CRASH     (GROUP_PIKEMAN | CHANGE_JOB1 | SKILL_4)

#define SKILL_GROUND_PIKE    	(GROUP_PIKEMAN | CHANGE_JOB2 | SKILL_1)
#define SKILL_TORNADO     		(GROUP_PIKEMAN | CHANGE_JOB2 | SKILL_2)
#define SKILL_WEAPONE_DEFENCE_MASTERY      		(GROUP_PIKEMAN | CHANGE_JOB2 | SKILL_3)
#define SKILL_EXPANSION     	(GROUP_PIKEMAN | CHANGE_JOB2 | SKILL_4)

#define SKILL_VENOM_SPEAR    	(GROUP_PIKEMAN | CHANGE_JOB3 | SKILL_1)
#define SKILL_VANISH			(GROUP_PIKEMAN | CHANGE_JOB3 | SKILL_2)
#define SKILL_CRITICAL_MASTERY 	(GROUP_PIKEMAN | CHANGE_JOB3 | SKILL_3)
#define SKILL_CHAIN_LANCE	 	(GROUP_PIKEMAN | CHANGE_JOB3 | SKILL_4)


#define SKILL_ASSASSIN_EYE    	(GROUP_PIKEMAN | CHANGE_JOB4 | SKILL_1)
#define SKILL_CHARGING_STRIKE	(GROUP_PIKEMAN | CHANGE_JOB4 | SKILL_2)
#define SKILL_VAGUE			 	(GROUP_PIKEMAN | CHANGE_JOB4 | SKILL_3)
#define SKILL_SHADOW_MASTER	 	(GROUP_PIKEMAN | CHANGE_JOB4 | SKILL_4)




#define SKILL_SCOUT_HAWK  		(GROUP_ARCHER | CHANGE_JOB1 | SKILL_1)
#define SKILL_SHOOTING_MASTERY  (GROUP_ARCHER | CHANGE_JOB1 | SKILL_2)
#define SKILL_WIND_ARROW		(GROUP_ARCHER | CHANGE_JOB1 | SKILL_3)
#define SKILL_PERFECT_AIM		(GROUP_ARCHER | CHANGE_JOB1 | SKILL_4)

#define SKILL_DIONS_EYE  		(GROUP_ARCHER | CHANGE_JOB2 | SKILL_1)
#define SKILL_FALCON      		(GROUP_ARCHER | CHANGE_JOB2 | SKILL_2)
#define SKILL_ARROW_OF_RAGE		(GROUP_ARCHER | CHANGE_JOB2 | SKILL_3)
#define SKILL_AVALANCHE       	(GROUP_ARCHER | CHANGE_JOB2 | SKILL_4)

#define SKILL_ELEMENTAL_SHOT	(GROUP_ARCHER | CHANGE_JOB3 | SKILL_1)
#define SKILL_GOLDEN_FALCON		(GROUP_ARCHER | CHANGE_JOB3 | SKILL_2)
#define SKILL_BOMB_SHOT    		(GROUP_ARCHER | CHANGE_JOB3 | SKILL_3)
#define SKILL_PERFORATION   	(GROUP_ARCHER | CHANGE_JOB3 | SKILL_4)


#define SKILL_RECALL_WOLVERIN	(GROUP_ARCHER | CHANGE_JOB4 | SKILL_1)
#define SKILL_EVASION_MASTERY	(GROUP_ARCHER | CHANGE_JOB4 | SKILL_2)
#define SKILL_PHOENIX_SHOT   	(GROUP_ARCHER | CHANGE_JOB4 | SKILL_3)
#define SKILL_FORCE_OF_NATURE  	(GROUP_ARCHER | CHANGE_JOB4 | SKILL_4)


#define SKILL_STINGGER  		(GROUP_ASSASSINE | CHANGE_JOB1 | SKILL_1)
#define SKILL_R_HIT             (GROUP_ASSASSINE | CHANGE_JOB1 | SKILL_2)
#define SKILL_D_MASTERY		    (GROUP_ASSASSINE | CHANGE_JOB1 | SKILL_3)
#define SKILL_WISP       		(GROUP_ASSASSINE | CHANGE_JOB1 | SKILL_4)
#define SKILL_V_THRONE  		(GROUP_ASSASSINE | CHANGE_JOB2 | SKILL_1)
#define SKILL_ALAS      		(GROUP_ASSASSINE | CHANGE_JOB2 | SKILL_2)
#define SKILL_S_SHOCK		    (GROUP_ASSASSINE | CHANGE_JOB2 | SKILL_3)
#define SKILL_A_MASTERY       	(GROUP_ASSASSINE | CHANGE_JOB2 | SKILL_4)
#define SKILL_S_SWORD       	(GROUP_ASSASSINE | CHANGE_JOB3 | SKILL_1)
#define SKILL_B_UP       		(GROUP_ASSASSINE | CHANGE_JOB3 | SKILL_2)
#define SKILL_INPES     		(GROUP_ASSASSINE | CHANGE_JOB3 | SKILL_3)
#define SKILL_BLIND         	(GROUP_ASSASSINE | CHANGE_JOB3 | SKILL_4)
#define SKILL_F_WIND         	(GROUP_ASSASSINE | CHANGE_JOB4 | SKILL_1)
#define SKILL_F_MASTERY        	(GROUP_ASSASSINE | CHANGE_JOB4 | SKILL_2)
#define SKILL_V_STAB      	    (GROUP_ASSASSINE | CHANGE_JOB4 | SKILL_3)
#define SKILL_P_SHADOW      	(GROUP_ASSASSINE | CHANGE_JOB4 | SKILL_4)

#define SKILL_DARKBOLT  		(GROUP_SHAMAN | CHANGE_JOB1 | SKILL_1)
#define SKILL_DARKWAVE          (GROUP_SHAMAN | CHANGE_JOB1 | SKILL_2)
#define SKILL_CURSELAZY		    (GROUP_SHAMAN | CHANGE_JOB1 | SKILL_3)
#define SKILL_L_PEACE       	(GROUP_SHAMAN | CHANGE_JOB1 | SKILL_4)
#define SKILL_S_FLARE    		(GROUP_SHAMAN | CHANGE_JOB2 | SKILL_1)
#define SKILL_S_MANACLE     	(GROUP_SHAMAN | CHANGE_JOB2 | SKILL_2)
#define SKILL_C_HUNT		    (GROUP_SHAMAN | CHANGE_JOB2 | SKILL_3)
#define SKILL_A_MIGAL       	(GROUP_SHAMAN | CHANGE_JOB2 | SKILL_4)
#define SKILL_R_MAKER       	(GROUP_SHAMAN | CHANGE_JOB3 | SKILL_1)
#define SKILL_L_GHOST       	(GROUP_SHAMAN | CHANGE_JOB3 | SKILL_2)
#define SKILL_HAUNT     		(GROUP_SHAMAN | CHANGE_JOB3 | SKILL_3)
#define SKILL_SCRATCH         	(GROUP_SHAMAN | CHANGE_JOB3 | SKILL_4)
#define SKILL_R_KNIGHT         	(GROUP_SHAMAN | CHANGE_JOB4 | SKILL_1)
#define SKILL_JUDGE         	(GROUP_SHAMAN | CHANGE_JOB4 | SKILL_2)
#define SKILL_A_MIDRANDA      	(GROUP_SHAMAN | CHANGE_JOB4 | SKILL_3)
#define SKILL_M_PRAY        	(GROUP_SHAMAN | CHANGE_JOB4 | SKILL_4)



#define SKILL_FORCE_ORB			(GROUP_OTHERSKILL | CHANGE_JOB1 | SKILL_1)

#define CHANGE_JOB3_QUEST		(GROUP_OTHERSKILL | CHANGE_JOB1 | SKILL_2)
#define CHANGE_ELEMENTARY_QUEST	(GROUP_OTHERSKILL | CHANGE_JOB1 | SKILL_3)

/*----------------------------------------------------------------------------*
*							BLESS SKILL
*-----------------------------------------------------------------------------*/
#define CLANSKILL_ABSORB        (GROUP_OTHERSKILL | CHANGE_JOB1 | SKILL_4)
#define CLANSKILL_ATTACK        (GROUP_OTHERSKILL | CHANGE_JOB1 | SKILL_5)
#define CLANSKILL_EVASION       (GROUP_OTHERSKILL | CHANGE_JOB1 | SKILL_6)

/*----------------------------------------------------------------------------*
*							BOOSTER SKILL
*-----------------------------------------------------------------------------*/
#define BOOSTER_ITEM_LIFE		(GROUP_OTHERSKILL | CHANGE_JOB1 | SKILL_7)
#define BOOSTER_ITEM_MANA		(GROUP_OTHERSKILL | CHANGE_JOB1 | SKILL_8)
#define BOOSTER_ITEM_STAMINA	(GROUP_OTHERSKILL | CHANGE_JOB1 | SKILL_9)

/*----------------------------------------------------------------------------*
*							SOD SKILL
*-----------------------------------------------------------------------------*/
#define SOD_SKILL_GOLD          (GROUP_SKILL | CHANGE_JOB1 | SKILL_1)
#define SOD_SKILL_SILVER        (GROUP_SKILL | CHANGE_JOB1 | SKILL_2)
#define SOD_SKILL_BRONZE        (GROUP_SKILL | CHANGE_JOB1 | SKILL_3)


#define SKILLDELAY_ITEM_LIFE		(GROUP_OTHERSKILL | CHANGE_JOB2 | SKILL_1)



#define SCROLL_INVULNERABILITY	(GROUP_OTHERSKILL | CHANGE_JOB2 | SKILL_1)
#define SCROLL_CRITICAL			(GROUP_OTHERSKILL | CHANGE_JOB2 | SKILL_2)
#define SCROLL_EVASION			(GROUP_OTHERSKILL | CHANGE_JOB2 | SKILL_3)

#define STONE_R_FIRECRYTAL      (GROUP_OTHERSKILL | CHANGE_JOB2 | SKILL_4)
#define STONE_R_ICECRYTAL       (GROUP_OTHERSKILL | CHANGE_JOB2 | SKILL_5)
#define STONE_R_LINGHTINGCRYTAL (GROUP_OTHERSKILL | CHANGE_JOB2 | SKILL_6)

#define STONE_A_FIGHTER			(GROUP_OTHERSKILL | CHANGE_JOB3 | SKILL_1)
#define STONE_A_MECHANICIAN		(GROUP_OTHERSKILL | CHANGE_JOB3 | SKILL_2)
#define STONE_A_PIKEMAN			(GROUP_OTHERSKILL | CHANGE_JOB3 | SKILL_3)
#define STONE_A_ARCHER			(GROUP_OTHERSKILL | CHANGE_JOB3 | SKILL_4)

#define STONE_A_KNIGHT			(GROUP_OTHERSKILL | CHANGE_JOB3 | SKILL_5)
#define STONE_A_ATALANTA		(GROUP_OTHERSKILL | CHANGE_JOB3 | SKILL_6)
#define STONE_A_MAGICIAN		(GROUP_OTHERSKILL | CHANGE_JOB3 | SKILL_7)
#define STONE_A_PRIESTESS		(GROUP_OTHERSKILL | CHANGE_JOB3 | SKILL_8)

#define SCROLL_P_INVULNERABILITY    (GROUP_OTHERSKILL | CHANGE_JOB4 | SKILL_1)
#define SCROLL_P_CRITICAL		    (GROUP_OTHERSKILL | CHANGE_JOB4 | SKILL_2)
#define SCROLL_P_EVASION		    (GROUP_OTHERSKILL | CHANGE_JOB4 | SKILL_3)




struct sSKILL_INFO
{
	char SkillName[64];
	char SkillDoc[150];
	int  RequireLevel;
	int  UseStamina[2];
	int	 RequireMastery[2];
	int  Element[3];
	DWORD UseWeaponCode[8];
	int(*FuncPointer)();
	DWORD	CODE;
	DWORD   USECODE;
	int *UseMana;


	int     SkillNum;


};


struct sSKILLBOX
{
	RECT BoxRect;
	RECT GageRect;

};


struct sSKILL
{
	char	sSkillName[32];
	DWORD	CODE;
	char    FileName[32];
	char    IconName[32];
	int     Flag;
	int     Use;
	int     Point;
	int     ShortKey;
	int     MousePosi;
	int     Position;
	int     UseTime;
	int     CheckTime;
	int     GageLength;
	int     GageLength2;
	int     Mastery;
	int     UseSKillIncreCount;
	int     UseSkillCount;
	int 	UseSkillMastery;
	int     UseSkillMasteryGage;
	int     UseSkillFlag;
	int     PlusState[5];
	int		Time[2];
	int		PartyFlag;
	int     ElementIndex;
	int     MatIcon;


	int     IconAlpha;
	int     IconPosiX;
	int     IconTime;
	int     IconFlag;

	DWORD   SkillTaget_CODE;
	int     SummonFlag;

	sSKILL_INFO Skill_Info;
};


struct sUSESKILL
{
	sSKILL UseSkill[SIN_MAX_USE_SKILL];
	sSKILLBOX SkillBox[SIN_MAX_USE_SKILL];
	sSKILL *pLeftSkill;
	sSKILL *pRightSkill;
	int   SkillPoint;
	int   SkillPoint4;

};

struct sPASSIVE_INFO
{
	int Flag;
	float DamagePercent;
	DWORD UseWeaponCode[8];
	DWORD CODE;


};


struct sSKILLPASSIVE
{
	sPASSIVE_INFO sPassive_Info[10];
	int Resistance[8];

};



class cSKILL
{

public:

	int OpenFlag;

	int MatSkill[4];
	DWORD UseSkillBox;

	int CheckMasteryData[SIN_MAX_USE_SKILL];
	int CheckSkillPointData[SIN_MAX_USE_SKILL];
	int CheckSkillMasteyData[SIN_MAX_USE_SKILL];

	DIRECTDRAWSURFACE	lpSkillGage[2];
	DIRECTDRAWSURFACE	lpSkillGage2[2];
	DIRECTDRAWSURFACE	lpSkillGage3;
	DIRECTDRAWSURFACE	lpSkillGage4;
	DIRECTDRAWSURFACE	lpSkillGage5;
	DIRECTDRAWSURFACE	lpSkillTitle[4];
	DIRECTDRAWSURFACE    lpSkillButton_Gray[17];
	DIRECTDRAWSURFACE    lpSkillButton[17];
	DIRECTDRAWSURFACE    lpSelectSkill;
	DIRECTDRAWSURFACE    lpShortKey[8];
	DIRECTDRAWSURFACE    lpSkillBoxBack;
	DIRECTDRAWSURFACE    lpWeaponIcon[10];
	DIRECTDRAWSURFACE    lpMasteryInfo;
	DIRECTDRAWSURFACE    lpSkillDown;

public:
	cSKILL();
	~cSKILL();

	void Init();
	void Load();
	void Release();
	void Close();
	void Draw();
	void Main();
	void LButtonDown(int x, int y);
	void LButtonUp(int x, int y);
	void RButtonDown(int x, int y);
	void RButtonUp(int x, int y);
	void KeyDown();
	void LoadUseSkillImage();

	int SearchUseSkill();

	void DrawSkillText();


	void CheckingNowSkillState();


	void CheckSkillMastery();


	int ShowSkillInfo(sSKILL *pSkill, sSKILLBOX *pSkillBox, int Icon = 0);


	int GetInfoBoxSize(sSKILLBOX *pSkillBox, int Col, int Icon = 0);


	int GetSkillMastery(sSKILL *pSkill, sSKILLBOX *pSkillBox);


	int CheckUseSkillState(sSKILL *pSkill);


	int CheckSkillData();


	int InitSkillPoint(int kind = 0);



	int SearchClearSkillPoint(DWORD CODE);

	int ShowClearSkillPointButton(int x, int y);

	int ClearSkillPointSection();


	int ReFormCharSkillInfo();
	int CheckCharSkillInfo();



	int CheckSkillMasteryForm(sSKILL *pSkill = 0, int Index = 0);
	int ReformSkillMasteryForm(sSKILL *pSkill = 0, int Index = 0);


	int CheckSkillPointForm(sSKILL *pSkill);
	int ReformSkillPointForm(sSKILL *pSkill);
	int InitReformSkillPointForm();



	int GetSkillPoint(DWORD CODE);


	int SearchContiueSkill(DWORD CODE);


	int SetVirtualLife(int Time, int Point);


	int UseBoosterItem(sITEM *pItem);


	int SetBoosterItem(DWORD ItemCODE, int Time);


	int SetT_Of_Valhalla(int Point, int LV);

	int SetEnchant_Weapon(int Time, int Point);


	int CheckContinueIcon();


	int SkillBarDraw(sSKILL *pSkill, int x, int y, int Alpha);


	int SearchSkillDoc(sSKILL *pSkill);


	int CancelContinueSkill(DWORD CODE);


	void DrawUp();


	int SkillShortKeyInit();


	int Regeneration_Field(int Time, int Point, int Party = 0);


	int ForeceOfNature(int Time, int Point, int Party = 0);


	int HellOfValhalla(int Time, int Point, int TVPoint, int LV, int Party = 0);


	int SearchContiueSkillIndex(DWORD CODE);


	int SearchContiueSkillCODE(DWORD CODE);


	int CheckMaturedSkill(int ChangeJob);


	int UseSkillDelayItem(sITEM *pItem);
	int SetSkillDelayItem(DWORD ItemCODE, int Time);



};

extern cSKILL	cSkill;
extern sUSESKILL sinSkill;
extern sSKILL_INFO sSkill_Info[SIN_MAX_SKILL];
extern sSKILLBOX sLeftRightSkill[2];
extern sSKILL  *pUseSkill;

extern sSKILL  ContinueSkill[10];
extern sSKILLPASSIVE sSkillPassive;

extern sSKILL sSkill[SIN_MAX_SKILL];

extern int SelectInterSkill;


extern int     SkillInfoShowFlag;
extern POINT	SkillInfoBoxPosi;
extern POINT   SkillInfoTextPosi;
extern POINT   SkillBoxSize;
extern char    szSkillInfoBuff[5000];

extern int     SkillDocLineCnt[6];
extern int     NextSkillLevelLine;



extern sSKILL *pMasterSkill;
extern int  SkillMasterFlag;

extern int ShowSkillUpInfo;

extern int  SkillMasterOkFlag[2];

extern JOB_DATA_CODE *sinJobList;


extern int   SkillIconIndex[10];
extern POINT SkillIconPosi;
extern int   SkillInconCnt;


extern int TestSkillDelayTime[16];


extern int ChangeJobSkillPlus;

extern POINT SkillUpInfo;
extern POINT SkillUpInfoPosi;

extern int ShowSkillClose;

extern DWORD ClearSkillCODE;

extern int ContinueSkillCancelFlag;

extern int SetT_Of_ValhallaFlag;
extern int SetT_Of_ValhallaFlag2;
extern int SetT_Of_ValhallaLV;
extern int SetH_Of_ValhallaLV;
extern int SetT_Of_ValhallaPOINT;



extern int AddVirtualLife[2];
extern int sinVirtualLifeTime;
extern int sinVirtualLifePercent;


extern int AddBoosterLife;
extern int BoosterLifeTime;
extern int BoosterLifePercent;
extern int LifeFlag;
extern short tempLife[];


extern int AddVirtualMana[2];
extern int sinVirtualManaTime;
extern int sinVirtualManaPercent;
extern int ManaFlag;
extern short tempMana[];


extern int AddVirtualStamina[2];
extern int sinVirtualStaminaTime;
extern int sinVirtualStaminaPercent;
extern int StaminaFlag;
extern short tempStamina[];


extern int Mat_BoosterItem[];

extern int MatForceOrb[];
extern int MatQuestTimer;


extern int MatBillingMagicForceOrb[];

extern int SkillButtonIndex;
extern int Skill4ButtonIndex;



extern int ContinueSkillMouseIndex;
extern sSKILL  TempContinueSkill[10];


extern int nMat_SkillDelayItem[];
extern int sinAddSkillDelay;
extern int sinSkillDelayTime;
extern int SkillDelayFlag;