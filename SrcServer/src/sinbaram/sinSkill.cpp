

#include "sinLinkHeader.h"
#include "..\\skillsub.h"
#include "..\\field.h" 


cSKILL	cSkill;
sUSESKILL sinSkill;
sSKILL  *pUseSkill;
sSKILL  ContinueSkill[10];
sSKILL  TempContinueSkill[10];
int SkillCountTime2[17] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
int ContinueSkillMouseIndex = 0;

JOB_DATA_CODE *sinJobList;

sSKILL *pMasterSkill;

sSKILLPASSIVE sSkillPassive;


int ShowSkillUpInfo = 0;
int  SkillMasterOkFlag[2] = { 0,0 };
int  SkillMasterFlag = 0;

int SkillMasteryShowFlag = 0;
char szUseSkillMastery[32];
POINT UseSkillMasteryPosi = { 0,0 };

int MatForceOrb[12] = { 0 };


int MatBillingMagicForceOrb[3] = { 0 };


int Mat_BoosterItem[9] = { 0 };


int nMat_SkillDelayItem[3] = { 0 };

int MatQuestTimer = 0;



POINT SkillUpInfo = { 13,21 };
POINT SkillUpInfoPosi = { 90,100 };


int     SkillInfoLineCnt = 0;

int     SkillInfoShowFlag = 0;
POINT	SkillInfoBoxPosi = { 0,0 };
POINT   SkillInfoTextPosi = { 0,0 };
POINT   SkillBoxSize = { 0,0 };


char    szSkillInfoBuff[5000];
char    szSkillMasterInfoBuff[5000];

char    szSkillInfoBuff2[5000];
char    szSkillMasterInfoBuff2[5000];


int     SkillDocLineCnt[6] = { 0,0,0,0,0,0 };
int     SkillUseWeaponClass = 0;
int     NextSkillLevelLine = 0;


int ShowSkillClose = 0;
int SkillButtonIndex = 0;
int Skill4ButtonIndex = 0;

int DownButtonUseShorKey = 0;

int DownButtonIndex = 0;
int LDownButtonIndex = 0;
int RDownButtonIndex = 0;

DWORD sinSkillBoxColor = RGBA_MAKE(0, 0, 132, 128);

int ChangeJobSkillPlus = 0;
int UseSkillIndex[2] = { 0,0 };

int SelectInterSkill = 0;


#define	NORMAL_SKILL_INDEX		14
#define MAX_USE_SKILL_POINT		10

#define SIN_MOUSE_POSI_LEFT		1
#define SIN_MOUSE_POSI_RIGHT	2




int   SkillIconIndex[10] = { 0,0,0,0,0,0,0,0,0,0 };
POINT SkillIconPosi = { 0,0 };
int   SkillInconCnt = 0;


int GageLenght[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

DWORD ClearSkillCODE = 0;
POINT ClearSkillButtonPosi = { 0,0 };

int SetT_Of_ValhallaFlag = 0;
int SetT_Of_ValhallaFlag2 = 0;
int SetT_Of_ValhallaLV = 0;

int SetH_Of_ValhallaLV = 0;
int SetT_Of_ValhallaPOINT = 0;

int MatCircleIcon = 0;

sSKILL_INFO sSkill_Info[SIN_MAX_SKILL] = {

#include "sinSkill_Info.h"

};


sSKILL sSkill[SIN_MAX_SKILL] = {


	{"³ë¸Ö¾îÅÃ "		,SKILL_NORMAL_ATTACK	,"Skill_Normal",},


	{"ÀÍ½ºÆ®¸²½¯µå"		,SKILL_EXTREME_SHIELD	,"TM10 Ex_shield","Mc1_E_SHIELD.tga"},
	{"¸ÞÄ«´Ð¹ü"			,SKILL_MECHANIC_BOMB	,"TM12 M_bomb"},
	{"Æ÷ÀÌÁð ¾îÆ®¸®ºäÆ®",SKILL_POISON_ATTRIBUTE ,"TM14 P_attribute"},
	{"ÇÇÁöÄÃ ¾÷¼Ù"		,SKILL_PHYSICAL_ABSORB	,"TM17 Ph_absorb","Mc1_P_ABSORB.tga"},

	{"¶ó¿îµå ÀÓÆåÆ®"	,SKILL_GREAT_SMASH		,"TM20 G_Smash"},
	{"¸Æ½Ã¸¶ÀÌÁî "		,SKILL_MAXIMIZE			,"TM23 Maximize","Mc2_MAXIMIZE.tga"},
	{"¿ÀÅä¸ÞÀÌ¼Ç"		,SKILL_AUTOMATION		,"TM26 Automation","Mc2_AUTOMATION.tga"},
	{"½ºÆÄÅ©"			,SKILL_SPARK			,"TM30 Spark"},

	{"¸ÞÅ» ¾Æ¸Ó"		,SKILL_METAL_ARMOR		,"TM40 M_Armor","Mc3_M_ARMOR.tga"},
	{"±×·£µå ½º¸Þ½¬"	,SKILL_GRAND_SMASH		,"TM43 Grand_Smash"},
	{"¸ÞÄ«´Ð ¿þÆÝ"		,SKILL_MECHANIC_WEAPON	,"TM44 M_Weapon"},
	{"½ºÆÄÆ® ½¯µå"		,SKILL_SPARK_SHIELD		,"TM50 S_Shield","Mc3_S_SHIELD.tga"},


	{"ÀÓÇÃ·¹ÀÌ¼Ç"		,SKILL_IMPULSION		,"TM60 Impulsion"},
	{"ÄÄÇÃ·¹ÀÌ¼Ç"		,SKILL_COMPULSION		,"TM63 Compulsion","Mc4_COMPULSION.tga"},
	{"¸Þ³×Æ½ ÇÇ¾î"		,SKILL_MAGNETIC_SPHERE	,"TM66 M_Sphere","Mc4_M_SPHERE.tga"},
	{"¸ÞÅ» °ñ·½"		,SKILL_METAL_GOLEM		,"TM70 M_Golem","Mc4_M_GOLEM.tga"},


	{"¹èÆ² ¸¶½ºÅÍ¸®"	,SKILL_MELEE_MASTERY	,"TF10 M_mastery"},
	{"ÆÄÀÌÅÍ ¾îÆ®¸®ºäÆ®",SKILL_FIRE_ATTRIBUTE	,"TF12 F_attribute"},
	{"·¹ÀÌºù"			,SKILL_RAVING			,"TF14 raving"},
	{"ÀÓÆÑÆ®"			,SKILL_IMPACT			,"TF17 impact"},

	{"Æ®¸®ÇÃ ÀÓÆÑÆ®"	,SKILL_TRIPLE_IMPACT	,"TF20 T_Impact"},
	{"ºÎ·çÆ² ½ºÀ®"		,SKILL_BRUTAL_SWING		,"TF23 B_Swing"},
	{"·Î¾î"				,SKILL_ROAR				,"TF26 Roar"},
	{"·¹ÀÌÁö¿Àºê Á¦Å©¶÷",SKILL_RAGE_OF_ZECRAM	,"TF30 R_Zecram"},

	{"ÄÁ¼¾Æ®·¹ÀÌ¼Ç"		,SKILL_CONCENTRATION	,"TF40 Concentration","Ft3_CONCENTRATION.tga"},
	{"¾îº¥Â¡ Å©·¡½¬"	,SKILL_AVANGING_CRASH	,"TF43 A_Crash"},
	{"½ºÀ§ÇÁ¿¢½º"		,SKILL_SWIFT_AXE		,"TF46 S_Axe","Ft3_S_AXE.tga"},
	{"º» Å©·¡½¬"		,SKILL_BONE_CRASH		,"TF50 B_Crash"},


	{"µð½ºÅä¸®¾î"		,SKILL_DETORYER		    ,"TF60 Destoryer"},
	{"¹ö¼­Ä¿"		    ,SKILL_BERSERKER		,"TF63 Berserker","Ft4_BERSERKER.tga"},
	{"½ÎÀÌÅ¬·Ð ½ºÆÄÀÌÅ©",SKILL_CYCLONE_STRIKE	,"TF66 C_Strike"},
	{"ºÎ½ºÆ® Çï½º"		,SKILL_BOOST_HEALTH		,"TF70 B_Health"},


	{"ÆÄÀÌÅ©À©µå"   	,SKILL_PIKE_WIND		,"TP10 P_wind"},
	{"¾ÆÀÌ½º ¾îÆ®¸®ºäÆ®",SKILL_ICE_ATTRIBUTE	,"TP12 I_attribute"},
	{"Å©¸®Æ¼ÄÃ Èý"		,SKILL_CRITICAL_HIT		,"TP14 Cri_hit"},
	{"Á¡ÇÎÅ©·¡½¬"		,SKILL_JUMPING_CRASH	,"TP17 J_Crash"},

	{"±×¶ó¿îµåÆÄÀÌÅ©"	,SKILL_GROUND_PIKE		,"TP20 G_Pike"},
	{"Åä³×ÀÌµµ"			,SKILL_TORNADO			,"TP23 Tornado"},
	{"¿þÆÝµðÆæ½º¸¶½ºÅÍ¸®",SKILL_WEAPONE_DEFENCE_MASTERY	,"TP26 W_D_Mastery"},
	{"ÀÍ½ºÆæ¼Ç" 		,SKILL_EXPANSION		,"TP30 Expasion"},

	{"º£³ð ½ºÇÇ¾î"		,SKILL_VENOM_SPEAR		,"TP40 V_Spear"},
	{"ºí·¹ÀÌµå¿Àºêºí·¹ÀÌÁî",SKILL_VANISH        ,"TP43 Vanish","Pk3_VANISH.tga"},
	{"»þÇÁ¸¶½ºÅÍ¸®"		,SKILL_CRITICAL_MASTERY	,"TP46 C_Mastery"},
	{"Ã¼ÀÎ·£½º" 		,SKILL_CHAIN_LANCE		,"TP50 C_Lance"},


	{"¾î½Ø½Å ¾ÆÀÌ"		,SKILL_ASSASSIN_EYE		,"TP60 A_Eye","Pk4_A_EYE.tga"},
	{"Â÷Â¡ ½ºÆ®¶óÀÌÅ©"	,SKILL_CHARGING_STRIKE	,"TP63 C_Strike"},
	{"º£ÀÌ±×"           ,SKILL_VAGUE	        ,"TP66 Vague","Pk4_VAGUE.tga"},
	{"»õµÍ¿ì ¸¶½ºÅÍ"	,SKILL_SHADOW_MASTER	,"TP70 S_Master"},


	{"½ºÄ«¿ô È£Å©"		,SKILL_SCOUT_HAWK		,"TA10 S_hawk","Ac1_S_HAWK.tga"},
	{"½´ÆÃ ¸¶½ºÅÍ¸®"	,SKILL_SHOOTING_MASTERY	,"TA12 S_mastery"},
	{"À©µå ¾Ö·Î¿ì"		,SKILL_WIND_ARROW		,"TA14 W_arrow"},
	{"ÆÛÆåÆ® ¿¡ÀÓ"		,SKILL_PERFECT_AIM		,"TA17 P_aim"},

	{"µð¿Â½º ¾ÆÀÌ"		,SKILL_DIONS_EYE		,"TA20 D_Eye"},
	{"ÆÈÄÜ"				,SKILL_FALCON			,"TA23 Falcon","Ac2_FALCON.tga"},
	{"¾Ö·Î¿ì ¿Àºê·¹ÀÌÁö",SKILL_ARROW_OF_RAGE	,"TA26 A_Rage"},
	{"¾Æ¹ß¶õÃ¼"			,SKILL_AVALANCHE		,"TA30 Avalanchie"},

	{"¿¤·¹¸àÅ»¼¦"		,SKILL_ELEMENTAL_SHOT	,"TA40 E_Shot"},
	{"°ñµçÆÈÄÜ"			,SKILL_GOLDEN_FALCON	,"TA43 G_Falcon","Ac3_G_FALCON.tga"},
	{"¹ü ¼¦"			,SKILL_BOMB_SHOT		,"TA46 B_Shot"},
	{"ÆÛÆ÷·¹ÀÌ¼Ç"		,SKILL_PERFORATION		,"TA50 Perforation"},


	{"¸®ÄÝ ¿ï¹ö¸°"		  ,SKILL_RECALL_WOLVERIN	,"TA60 R_Wolverin","Ac4_R_WOLVERIN.tga"},
	{"ÀÌº£ÀÌ¼Ç ¸¶½ºÅÍ¸®"  ,SKILL_EVASION_MASTERY	,"TA63 E_Mastery"},
	{"ÇÇ´Ð½º ¼¦"          ,SKILL_PHOENIX_SHOT	    ,"TA66 P_Shot"},
	{"Æ÷½º ¿Àºê ³»Ãò·²"	  ,SKILL_FORCE_OF_NATURE	,"TA70 F_O_Nature","Ac4_F_O_NATURE.tga"},



	{"½º¿ö½ººí·¹½ºÆ®"	,SKILL_SWORD_BLAST	    ,"MN10 S_Blast"},
	{"È¦¸® ¹Ùµð"		,SKILL_HOLY_BODY		,"MN12 H_Body","Kt1_H_BODY.tga"},
	{"ÇÇÁöÄÃÆ®·¹ÀÌ´×"	,SKILL_PHYSICAL_TRANING ,"MN14 P_Traning"},
	{"¶°ºí Å©·¡½¬"   	,SKILL_DOUBLE_CRASH     ,"MN17 D_Crash"},

	{"È¦¸® ¹ë·¯"	    ,SKILL_HOLY_VALOR       ,"MN20 H_Valor","Kt2_H_VALOR.tga"},
	{"ºê·£µð½¬"	        ,SKILL_BRANDISH         ,"MN23 Brandish"},
	{"ÇÇ¾î½Ì"	        ,SKILL_PIERCING         ,"MN26 Piercing"},
	{"µå·¹½ºÆ½ ½ºÇÇ¸´"	,SKILL_DRASTIC_SPIRIT   ,"MN30 D_Spirit","Kt2_D_SPIRIT.tga"},

	{"ÇÁ·¹ÀÓ ºê·£µð½¬"	,SKILL_SWORD_MASTERY   ,"MN40 S_Mastery"},
	{"µð¹ÙÀÎÀÎÈ¦·¹ÀÌ¼Ç" ,SKILL_DIVINE_INHALATION,"MN43 D_Inhalation","Kt3_D_INHALATION.tga"},
	{"È¦¸®ÀÎÄµÅ×ÀÌ¼Ç"	,SKILL_HOLY_INCANTATION ,"MN46 H_Incantation"},
	{"±×·£µå Å©·Î½º"	,SKILL_GRAND_CROSS		,"MN50 G_Cross"},


	{"½º¿öµå ¿Àºê Àú½ºÆ½½º"	,SKILL_SWORD_OF_JUSTICE	,"MN60 S_O_Justice"},
	{"°«µé¸® ½¯µå"			,SKILL_GODLY_SHIELD		,"MN63 G_Shield","Kt4_G_SHIELD.tga"},
	{"°« ºí·¹½º"            ,SKILL_GOD_BLESS	    ,"MN66 G_Bless","Kt4_G_BLESS.tga"},
	{"µð¹ÙÀÎ ÇÇ¾î½Ì"		,SKILL_DIVINE_PIERCING	,"MN70 D_Piercing"},


		/// TIER 5

	{ "Soul Breaker"		,SKILL_SOUL_BREAKER	,"MN80 S_Breaker" },

	{"½¯µå ½ºÆ®¶óÀÌÅ©"	,SKILL_SHIELD_STRIKE	,"MA10 S_Strike"},
	{"ÆÄ¸®³ª "			,SKILL_FARINA			,"MA12 Farina"},
	{"µå·ÎÀ×¸¶½ºÅÍ¸®"	,SKILL_THROWING_MASTERY ,"MA14 T_Mastery"},
	{"ºñ°Å ½ºÇÇ¾î"	    ,SKILL_VIGOR_SPEAR      ,"MA17 V_Spear"},

	{"À©µð"	            ,SKILL_WINDY            ,"MA20 Windy","At2_WINDY.tga"},
	{"Æ®À§½ºÆ® Àçºí¸°"	,SKILL_TWIST_JAVELIN    ,"MA23 T_Javelin"},
	{"¼Ò¿ï ½âÄ¿"	    ,SKILL_SOUL_SUCKER      ,"MA26 S_Sucker"},
	{"ÆÄÀÌ¾î Àçºí¸°"	,SKILL_FIRE_JAVELIN     ,"MA30 F_Javelin"},

	{"½ºÇÃ¸´ ÀÚº§¸°"	,SKILL_SPLIT_JAVELIN         ,"MA40 Split_Javelin"},
	{"Æ®¶óÀÌ¾öÇÁ¿Àºê¹ßÇÒ¶ó",SKILL_TRIUMPH_OF_VALHALLA,"MA43 T_Of_Valhalla","At3_T_O_VALHALLA.tga"},
	{"¶óÀÌÆ®´×Àçºí¸°"	,SKILL_LIGHTNING_JAVELIN     ,"MA46 L_Javelin"},
	{"½ºÅè Àçºí¸°"		,SKILL_STORM_JAVELIN         ,"MA50 Storm_Javelin"},


	{"Çï ¿Àºê ¹ßÇÒ¶ó"		,SKILL_HALL_OF_VALHALLA ,"MA60 H_O_Valhalla","At4_H_O_VALHALLA.tga"},
	{"¿¢½º ¶óÁö"			,SKILL_X_RAGE		    ,"MA63 X_Rage"},
	{"ÇÁ·Î½ºÆ® Àçºí¸°"      ,SKILL_FROST_JAVELIN	,"MA66 F_Javelin","At4_F_JAVELIN.tga"},
	{"º¥Ã¾"					,SKILL_VENGEANCE		,"MA70 Vengeance"},



	{"Èú¸µ"				,SKILL_HEALING			,"MP10 Healing"},
	{"È¦¸®º¼Æ® "		,SKILL_HOLY_BOLT		,"MP12 HolyBolt"},
	{"¸ÖÆ¼½ºÆÄÅ©"		,SKILL_MULTISPARK		,"MP14 M_Spark"},
	{"È¦¸®¸¶ÀÎµå"	    ,SKILL_HOLY_MIND	    ,"MP17 HolyMind"},

	{"¸ÞµðÅ×ÀÌ¼Ç"	    ,SKILL_MEDITATION	    ,"MP20 Meditation"},
	{"µð¹ÙÀÎ¶óÀÌÆ®´×"	,SKILL_DIVINE_LIGHTNING ,"MP23 D_Lightning"},
	{"È¦¸® ¸®ÇÃ·º¼Ç"	,SKILL_HOLY_REFLECTION	,"MP26 H_Reflection","Pr2_H_REFLECTION.tga"},
	{"±×·¹ÀÌÆ® Èú¸µ"	,SKILL_GRAND_HEALING	,"MP30 G_Healing"},

	{"ºñ°Å º¼"		    ,SKILL_VIGOR_BALL	    ,"MP40 V_Ball"},
	{"¸®Àú·º¼Ç"			,SKILL_RESURRECTION		,"MP43 Resurrection"},
	{"ÀÍ½ºÆÃ¼Ç"			,SKILL_EXTINCTION		,"MP46 Extinction"},
	{"¹öÃò¾ó ¶óÀÌÇÁ"	,SKILL_VIRTUAL_LIFE		,"MP50 V_Life","Pr3_V_LIFE.tga"},


	{"±Û·¡¼Å ½ºÆÄÀÌÅ©"	 ,SKILL_GLACIAL_SPIKE	  ,"MP60 G_Spike"},
	{"¸®Á¦³Ê·¹ÀÌ¼Ç ÇÊµå" ,SKILL_REGENERATION_FIELD,"MP63 R_Field","Pr4_R_FIELD.tga"},
	{"Ã¼ÀÎ ¶óÀÌÆ®´×"     ,SKILL_CHAIN_LIGHTNING	  ,"MP66 C_Lightning"},
	{"¼­¸ó ¹Â½ºÆç"		 ,SKILL_SUMMON_MUSPELL	  ,"MP70 S_Muspell","Pr4_S_MUSPELL.tga"},




	{"¾î°í´Ï"			,SKILL_AGONY			,"MM10 Agony"},
	{"ÆÄÀÌ¾îº¼Æ® "		,SKILL_FIRE_BOLT		,"MM12 FireBolt"},
	{"Á¦´Ï¾²"			,SKILL_ZENITH			,"MM14 Zenith","Mg1_ZENITH.tga"},
	{"ÆÄÀÌ¾îº¼"			,SKILL_FIRE_BALL	    ,"MM17 FireBall"},

	{"¸ÇÅ» ¸¶½ºÅÍ¸®"	,SKILL_MENTAL_MASTERY   ,"MM20 M_Mastery"},
	{"ÄÝ·ë¿Àºê¿öÅÍ"		,SKILL_WATORNADO	    ,"MM23 Watornado"},
	{"ÀÎÃ¦Æ® ¿þÆù"		,SKILL_ENCHANT_WEAPON	,"MM26 E_Weapon","Mg2_E_WEAPON.tga"},
	{"µ¥µå·¹ÀÌ"			,SKILL_DEAD_RAY  	    ,"MM30 D_Ray"},

	{"¿¡³ÊÁö ½¯µå"		,SKILL_ENERGY_SHIELD    ,"MM40 E_Shield","Mg3_E_SHIELD.tga"},
	{"´ÙÀÌ¾Æ½ºÆ®·ÎÇÇÁò"	,SKILL_DIASTROPHISM	    ,"MM43 Diastrophism"},
	{"½ºÇÇ¸´ ¿¤·¹¸àÅ»"	,SKILL_SPIRIT_ELEMENTAL	,"MM46 S_Elemental","Mg3_S_ELEMENTAL.tga"},
	{"´í½Ì½º¿öµå"		,SKILL_DANCING_SWORD  	,"MM50 D_Sword","Mg3_D_SWORD.tga"},


	{"ÆÄÀÌ¾î ¿¤·¹¸àÅ»"	,SKILL_FIRE_ELEMENTAL	,"MM60 F_Elemental","Mg4_F_ELEMENTAL.tga"},
	{"ÇÃ¶óÀÓ ¿þÀÌºê"    ,SKILL_FLAME_WAVE		,"MM63 F_Wave"},
	{"µð½ºÆ®·Ï¼Ç"       ,SKILL_DISTORTION	    ,"MM66 Distortion","Mg4_DISTORTION.tga"},
	{"¸ÞÅ×¿À"		    ,SKILL_M_METEO		    ,"MM70 Meteo"},


	{"Èí¼ö·Â »ó½Â"	    ,CLANSKILL_ABSORB	 ,"","wa1-1.tga"},
	{"°ø°Ý·Â »ó½Â"      ,CLANSKILL_ATTACK	 ,"","wa1-3.tga"},
	{"È¸ÇÇÀ² »ó½Â"      ,CLANSKILL_EVASION	 ,"","wa1-2.tga"},

		//SOD SKILL
	{ "SOD GOLD"	    ,SOD_SKILL_GOLD	 ,"","SOD1_Skill.tga" },
	{ "SOD SILVER"      ,SOD_SKILL_SILVER	 ,"","SOD2_Skill.tga" },
	{ "SOD BRONZE"      ,SOD_SKILL_BRONZE	 ,"","SOD3_Skill.tga" },


	{"¾ÆÅ¸³ª½Ã¾Æ"			 ,SCROLL_INVULNERABILITY	 ,"","S_Ath.tga"},
	{"µ¥µé¸® ¿¡Áö"			 ,SCROLL_CRITICAL            ,"","S_Dea.tga"},
	{"¾îº£ÀÏ ¿Àºê ÀÌº£ÀÌµå"	 ,SCROLL_EVASION	         ,"","S_Eva.tga"},
	{"µðÆÄÀÌ¾ð½º ½ºÅæ"		 ,STONE_R_FIRECRYTAL	     ,"","F_C_M.tga"},
	{"µðÆÄÀÌ¾ð½º ½ºÅæ"		 ,STONE_R_ICECRYTAL	         ,"","I_C_M.tga"},
	{"µðÆÄÀÌ¾ð½º ½ºÅæ"	     ,STONE_R_LINGHTINGCRYTAL    ,"","L_C_M.tga"},
	{"¸¶ÀÌÆ® ½ºÅæ"			 ,STONE_A_FIGHTER		     ,"","Ft_R.tga"},
	{"¸¶ÀÌÆ® ½ºÅæ"			 ,STONE_A_MECHANICIAN	     ,"","Mc_R.tga"},
	{"¸¶ÀÌÆ® ½ºÅæ"			 ,STONE_A_PIKEMAN		     ,"","Pk_R.tga"},
	{"¸¶ÀÌÆ® ½ºÅæ"	         ,STONE_A_ARCHER			 ,"","Ac_R.tga"},
	{"¸¶ÀÌÆ® ½ºÅæ"           ,STONE_A_KNIGHT			 ,"","Kt_R.tga"},
	{"¸¶ÀÌÆ® ½ºÅæ"           ,STONE_A_ATALANTA		     ,"","At_R.tga"},
	{"¸¶ÀÌÆ® ½ºÅæ"           ,STONE_A_MAGICIAN		     ,"","Mg_R.tga"},
	{"¸¶ÀÌÆ® ½ºÅæ"           ,STONE_A_PRIESTESS		     ,"","Pt_R.tga"},

	{"ÀÌÅÍ³Î ¶óÀÌÇÁ"	     ,SCROLL_P_INVULNERABILITY	 ,"","S_Ath.tga"},
	{"ÆäÀÌÆ² ¿¡Áö"			 ,SCROLL_P_CRITICAL          ,"","S_Dea.tga"},
	{"¾î¹öÆ® ½ºÅ©·Ñ"	     ,SCROLL_P_EVASION	         ,"","S_Eva.tga"},


	{"»ý¸í·Â ºÎ½ºÅÍ",		BOOSTER_ITEM_LIFE,			"",		"Booster_01.tga"},
	{"±â·Â ºÎ½ºÅÍ",			BOOSTER_ITEM_MANA,			"",		"Booster_02.tga"},
	{"±Ù·Â ºÎ½ºÅÍ",			BOOSTER_ITEM_STAMINA,		"",		"Booster_03.tga"},


	{"½ºÅ³ µô·¹ÀÌ",			SKILLDELAY_ITEM_LIFE,			"",		"Booster_01.tga"},

};



sSKILLBOX	sSkillBox[SIN_MAX_SKILLBOX] = {
	{{142,537,142 + 49,537 + 46}},

	{{27 - 10,502,27 + 49 - 10,502 + 46},{27 + 47 - 10,502 + 5,27 + 47 + 5 - 10,502 + 40}},
	{{67 - 10,546,67 + 49 - 10,546 + 46},{67 + 47 - 10,546 + 5,67 + 47 + 5 - 10,546 + 40}},
	{{77 - 10,466,77 + 49 - 10,466 + 46},{77 + 47 - 10,466 + 5,77 + 47 + 5 - 10,466 + 40}},
	{{137 - 10,476,137 + 49 - 10,476 + 46},{137 + 47 - 10,476 + 5,137 + 47 + 5 - 10,476 + 40}},

	{{212 - 15,466,212 + 49 - 15,466 + 46},{212 + 47 - 15,466 + 5,212 + 47 + 5 - 15,466 + 40}},
	{{232 - 15,516,232 + 49 - 15,516 + 46},{232 + 47 - 15,516 + 5,232 + 47 + 5 - 15,516 + 40}},
	{{272 - 15,466,272 + 49 - 15,466 + 46},{272 + 47 - 15,466 + 5,272 + 47 + 5 - 15,466 + 40}},
	{{332,466,332 + 49,466 + 46},{332 + 47,466 + 5,332 + 47 + 5,466 + 40}},

	{{402,476,402 + 49, 476 + 46},{402 + 47,476 + 5,402 + 47 + 5,476 + 40}},
	{{472,456,472 + 49, 456 + 46},{472 + 47,456 + 5,472 + 47 + 5,456 + 40}},
	{{512,506,512 + 49, 506 + 46},{512 + 47,506 + 5,512 + 47 + 5,506 + 40}},
	{{532,456,532 + 49, 456 + 46},{532 + 47,456 + 5,532 + 47 + 5,456 + 40}},

	{{602,481,602 + 49, 481 + 46},{602 + 47,481 + 5,602 + 47 + 5,481 + 40}},
	{{662,511,662 + 49, 511 + 46},{662 + 47,511 + 5,662 + 47 + 5,511 + 40}},
	{{681,461,681 + 49, 461 + 46},{681 + 47,461 + 5,681 + 47 + 5,461 + 40}},
	{{722,511,722 + 49, 511 + 46},{722 + 47,511 + 5,722 + 47 + 5,511 + 40}},


};

sSKILLBOX sLeftRightSkill[2] = {
	{{349,541,349 + 49,541 + 46},{349,558,349 + 5,558 + 35}},
	{{401 + 2,541,401 + 49,541 + 46},{446,558,446 + 5,558 + 35}},

};

int SkillTitle[4][2] = {
	{85,438 - 4},
	{280,438 - 4},
	{470,438 - 9},
	{675,438 - 4},

};

DIRECTDRAWSURFACE	lpSkillMain;
DIRECTDRAWSURFACE	lpSkillMain2;

DIRECTDRAWSURFACE    lpSkillMainLeftB;
DIRECTDRAWSURFACE    lpSkillMainRightB;

int SkillMain2OpenFlag = 0;
int SkillMain2ButtonFlag[2] = { 0,0 };




int Skill4MasterFlag = 0;




int MonsterDamageLine = 0;
int ChainDamageLine = 0;
int MatSkillIconBackGround = 0;

cSKILL::cSKILL()
{
	memset(&ContinueSkill, 0, sizeof(sSKILL) * 10);

}
cSKILL::~cSKILL()
{

}

void cSKILL::Init()
{

	char *FilePath = "Image\\SinImage\\skill\\keep\\";
	char szFilePath[128];
	for(int j = 0; j < SIN_MAX_SKILL; j++)
	{
		if(sSkill[j].IconName)
		{
			wsprintf(szFilePath, "%s%s", FilePath, sSkill[j].IconName);
			sSkill[j].MatIcon = CreateTextureMaterial(szFilePath, 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

		}
	}







	MatCircleIcon = CreateTextureMaterial("Image\\SinImage\\Skill\\keep\\GA_Mon.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);;
	MatSkillIconBackGround = CreateTextureMaterial("Image\\SinImage\\Skill\\keep\\GA_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);;

	SearchUseSkill();
	Load();


	sinSkill.pLeftSkill = &sinSkill.UseSkill[0];
	sinSkill.UseSkill[0].MousePosi = 1;
	sinSkill.pLeftSkill->Position = 1;



}

void cSKILL::Load()
{
	char ShortKeyDirPath[128];
	char WeaponIconPath[128];

	lpSkillDown = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\skilldown.bmp");


	lpSkillMain = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\Skil24.bmp");



	lpSkillMainLeftB = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\LeftArrow.bmp");
	lpSkillMainRightB = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\RightArrow.bmp");




	lpSkillGage[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\Gage.bmp");
	lpSkillGage[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\Gage2.bmp");
	lpSkillGage2[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\Gage-2.bmp");
	lpSkillGage2[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\Gage-22.bmp");
	lpSkillGage3 = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\Gage-3.bmp");
	lpSkillGage4 = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\Gage-4.bmp");
	lpSkillGage5 = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\Gage-5.bmp");

	lpMasteryInfo = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\MasteryInfo.bmp");

	lpSelectSkill = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\SelectSkill.bmp");
	lpSkillBoxBack = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\BOX4040.bmp");

	for(int i = 0; i < 8; i++)
	{
		wsprintf(ShortKeyDirPath, "Image\\SinImage\\skill\\ShortKey\\f%d.bmp", i + 1);
		lpShortKey[i] = LoadDibSurfaceOffscreen(ShortKeyDirPath);

	}
	for(int i = 0; i < 10; i++)
	{
		wsprintf(WeaponIconPath, "Image\\SinImage\\skill\\WeaponIcon\\%d.bmp", i + 1);
		lpWeaponIcon[i] = LoadDibSurfaceOffscreen(WeaponIconPath);

	}

}


void cSKILL::LoadUseSkillImage()
{
	int i = 0;
	char TempDirPath[128];
	char TempTitleDirPath[128];
	char ButtonImageDirPath[128];

	TempDirPath[0] = 0;
	switch(UseSkillBox)
	{
		case GROUP_MECHANICIAN:
		strcpy_s(TempDirPath, "Image\\SinImage\\Skill\\Mecha\\");

		break;
		case GROUP_FIGHTER:
		strcpy_s(TempDirPath, "Image\\SinImage\\Skill\\Fighter\\");

		break;
		case GROUP_PIKEMAN:
		strcpy_s(TempDirPath, "Image\\SinImage\\Skill\\Pikeman\\");

		break;
		case GROUP_ARCHER:
		strcpy_s(TempDirPath, "Image\\SinImage\\Skill\\Archer\\");

		break;
		case GROUP_ATALANTA:
		strcpy_s(TempDirPath, "Image\\SinImage\\Skill\\Atalanta\\");
		break;
		case GROUP_KNIGHT:
		strcpy_s(TempDirPath, "Image\\SinImage\\Skill\\Knight\\");

		break;
		case GROUP_MAGICIAN:
		strcpy_s(TempDirPath, "Image\\SinImage\\Skill\\Magician\\");

		break;
		case GROUP_PRIESTESS:
		strcpy_s(TempDirPath, "Image\\SinImage\\Skill\\Priestess\\");

		break;


	}
	if(!TempDirPath[0])
		return;


	lpSkillButton[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Skill\\Skill_Normal.bmp");
	lpSkillButton_Gray[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Skill\\Skill_Normal.bmp");
	for(i = 0; i < 4; i++)
	{
		wsprintf(TempTitleDirPath, "%s%s%d%s", TempDirPath, "JobTitle\\", i + 1, ".bmp");
		lpSkillTitle[i] = LoadDibSurfaceOffscreen(TempTitleDirPath);

	}


	for(i = 1; i < 17; i++)
	{
		if(sinSkill.UseSkill[i].Flag)
		{
			if(sinSkill.UseSkill[i].FileName[0])
			{
				wsprintf(ButtonImageDirPath, "%s%s%s%s", TempDirPath, "Button\\", sinSkill.UseSkill[i].FileName, ".bmp");
				lpSkillButton[i] = LoadDibSurfaceOffscreen(ButtonImageDirPath);
				wsprintf(ButtonImageDirPath, "%s%s%s%s%s", TempDirPath, "Button\\", sinSkill.UseSkill[i].FileName, "_", ".bmp");
				lpSkillButton_Gray[i] = LoadDibSurfaceOffscreen(ButtonImageDirPath);
			}
		}
	}

}


void cSKILL::Release()
{
	int i = 0;
	if(lpSkillGage[0])
	{
		lpSkillGage[0]->Release();
		lpSkillGage[0] = 0;
	}
	if(lpSkillGage[1])
	{
		lpSkillGage[1]->Release();
		lpSkillGage[1] = 0;


	}
	if(lpSelectSkill)
	{
		lpSelectSkill->Release();
		lpSelectSkill = 0;

	}
	for(i = 0; i < 4; i++)
	{
		if(lpSkillTitle[i])
		{
			lpSkillTitle[i]->Release();
			lpSkillTitle[i] = 0;

		}
	}
	for(i = 0; i < 4; i++)
	{
		if(lpSkillTitle[i])
		{
			lpSkillTitle[i]->Release();
			lpSkillTitle[i] = 0;

		}
	}
	for(i = 0; i < 17; i++)
	{
		if(lpSkillButton[i])
		{
			lpSkillButton[i]->Release();
			lpSkillButton[i] = 0;


		}
		if(lpSkillButton_Gray[i])
		{
			lpSkillButton_Gray[i]->Release();
			lpSkillButton_Gray[i] = 0;

		}
	}
	for(i = 0; i < 8; i++)
	{
		if(lpShortKey[i])
		{
			lpShortKey[i]->Release();
			lpShortKey[i] = 0;

		}
	}
	for(i = 0; i < 10; i++)
	{
		if(lpWeaponIcon[i])
		{
			lpWeaponIcon[i]->Release();
			lpWeaponIcon[i] = 0;
		}
	}

}

int CheckVirtualLifeTime = 0;
int CheckBoosterLifeTime = 0;
int CheckVirtualManaTime = 0;
int CheckVirtualStaminaTime = 0;
int CheckSkillDelayTime = 0;
void cSKILL::DrawUp()
{
	int i = 0;

	for(i = 0; i < MAX_CONTINUE_SKILL; i++)
	{
		if(TempContinueSkill[i].Flag)
		{
			if(TempContinueSkill[i].MatIcon)
			{
				if(!TempContinueSkill[i].IconFlag)
				{
					dsDrawTexImage(MatSkillIconBackGround, 10 + TempContinueSkill[i].IconPosiX, 10, 32, 32, TempContinueSkill[i].IconAlpha);
					SkillBarDraw(&TempContinueSkill[i], 10 + 16 + TempContinueSkill[i].IconPosiX, 10 + 16, TempContinueSkill[i].IconAlpha);
					dsDrawTexImage(TempContinueSkill[i].MatIcon, 10 + TempContinueSkill[i].IconPosiX, 10, 32, 32, TempContinueSkill[i].IconAlpha);
				}
			}
		}
	}

}
void cSKILL::Draw()
{
	int i = 0;














	if(SkillMain2OpenFlag)
	{
		DrawSprite(0, 600 - sinMoveKindInter[SIN_SKILL] + 56, lpSkillMain2, 0, 0, 800, 200);

		if(SkillMain2ButtonFlag[0])
		{
			DrawSprite(13, 600 + 83 - sinMoveKindInter[SIN_SKILL] + 56, lpSkillMainLeftB, 0, 0, 20, 20);
		}
	}

	if(!SkillMain2OpenFlag)
	{
		DrawSprite(0, 600 - sinMoveKindInter[SIN_SKILL] + 56, lpSkillMain, 0, 0, 800, 200);

		if(SkillMain2ButtonFlag[1])
		{
			DrawSprite(766, 600 + 83 - sinMoveKindInter[SIN_SKILL] + 56, lpSkillMainRightB, 0, 0, 20, 20);
		}
	}

	if(OpenFlag && !SkillMain2OpenFlag)
	{
		for(i = 0; i < (int)sinChar->ChangeJob + 1; i++)
		{
			DrawSprite(SkillTitle[i][0], SkillTitle[i][1] + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillTitle[i], 0, 0, 100, 20);
		}

		for(i = 1; i < ChangeJobSkillPlus; i++)
		{
			if(sinSkill.UseSkill[i].Flag && sinSkill.UseSkill[i].Use && SkillMasterFlag)
			{
				if(lpSkillButton[i])
				{
					DrawSprite(sinSkill.SkillBox[i].BoxRect.left, sinSkill.SkillBox[i].BoxRect.top + (256 - sinMoveKindInter[SIN_SKILL]),
							   lpSkillButton[i], 0, 0, 49, 46);
				}
			}
			if(sinSkill.UseSkill[i].Flag && !sinSkill.UseSkill[i].Use  && SkillMasterFlag)
			{
				if(lpSkillButton_Gray[i])
				{
					DrawSprite(sinSkill.SkillBox[i].BoxRect.left, sinSkill.SkillBox[i].BoxRect.top + (256 - sinMoveKindInter[SIN_SKILL]),
							   lpSkillButton_Gray[i], 0, 0, 49, 46);
				}
			}
			if(sinSkill.UseSkill[i].Flag &&  SkillMasterFlag && sinSkill.UseSkill[i].Point >= 10)
			{
				if(lpSkillButton_Gray[i])
				{
					DrawSprite(sinSkill.SkillBox[i].BoxRect.left, sinSkill.SkillBox[i].BoxRect.top + (256 - sinMoveKindInter[SIN_SKILL]),
							   lpSkillButton_Gray[i], 0, 0, 49, 46);
				}
			}
			if(!SkillMasterFlag)
			{
				if(sinSkill.UseSkill[i].Flag && sinSkill.UseSkill[i].Point)
				{
					if(lpSkillButton[i])
					{
						DrawSprite(sinSkill.SkillBox[i].BoxRect.left, sinSkill.SkillBox[i].BoxRect.top + (256 - sinMoveKindInter[SIN_SKILL]),
								   lpSkillButton[i], 0, 0, 49, 46);

					}
				}
				if(sinSkill.UseSkill[i].Flag && !sinSkill.UseSkill[i].Point)
				{
					if(lpSkillButton_Gray[i])
					{
						DrawSprite(sinSkill.SkillBox[i].BoxRect.left, sinSkill.SkillBox[i].BoxRect.top + (256 - sinMoveKindInter[SIN_SKILL]),
								   lpSkillButton_Gray[i], 0, 0, 49, 46);
					}
				}
			}

			if(sinSkill.UseSkill[i].Flag && sinSkill.UseSkill[i].Skill_Info.USECODE == SIN_SKILL_USE_NOT)
			{
				DrawSprite(sinSkill.SkillBox[i].GageRect.left, sinSkill.SkillBox[i].GageRect.top + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillGage4, 0, 0, 5, 35);
			}

			if(sinSkill.UseSkill[i].Flag && (sinSkill.UseSkill[i].Skill_Info.USECODE != SIN_SKILL_USE_NOT || sinSkill.UseSkill[i].Skill_Info.Element[0]))
			{
				DrawSprite(sinSkill.SkillBox[i].GageRect.left, sinSkill.SkillBox[i].GageRect.top + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillGage3, 0, 0, 5, 35);
				DrawSprite(sinSkill.SkillBox[i].GageRect.left, sinSkill.SkillBox[i].GageRect.top + (35 - sinSkill.UseSkill[i].UseSkillMasteryGage) + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillGage2[0], 0, 35 - sinSkill.UseSkill[i].UseSkillMasteryGage, 5, 35);
				if(sinSkill.UseSkill[i].UseSkillMasteryGage >= 3)
					DrawSprite(sinSkill.SkillBox[i].GageRect.left, sinSkill.SkillBox[i].GageRect.top + (35 - sinSkill.UseSkill[i].UseSkillMasteryGage) + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillGage2[1], 0, 0, 5, 3);

			}
			if(sinSkill.UseSkill[i].Flag)
			{
				DrawSprite(sinSkill.SkillBox[i].GageRect.right + 1, sinSkill.SkillBox[i].GageRect.top + (35 - sinSkill.UseSkill[i].GageLength) + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillGage[0], 0, 35 - sinSkill.UseSkill[i].GageLength, 5, 35);
				if(sinSkill.UseSkill[i].GageLength >= 3)
					DrawSprite(sinSkill.SkillBox[i].GageRect.right + 1, sinSkill.SkillBox[i].GageRect.top + (35 - sinSkill.UseSkill[i].GageLength) + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillGage[0], 0, 0, 5, 3);

			}

			if(sinSkill.UseSkill[i].Flag && sinSkill.UseSkill[i].Skill_Info.Element[0])
			{
				DrawSprite(sinSkill.SkillBox[i].GageRect.left, sinSkill.SkillBox[i].GageRect.top + (256 - sinMoveKindInter[SIN_SKILL]), lpSkillGage5, 0, 0, 5, 35);
			}


		}
		if(DownButtonIndex)
		{
			DrawSprite(sinSkill.SkillBox[DownButtonIndex - 1].BoxRect.left + 1, sinSkill.SkillBox[DownButtonIndex - 1].BoxRect.top + 1 + (256 - sinMoveKindInter[SIN_SKILL]),
					   lpSkillButton[DownButtonIndex - 1], 0, 0, 49, 46);

		}
		if(SkillButtonIndex)
		{
			if(sinSkill.UseSkill[SkillButtonIndex - 1].Flag)
			{
				if(DownButtonIndex)
				{
					DrawSprite(sinSkill.SkillBox[SkillButtonIndex - 1].BoxRect.left + 1,
							   sinSkill.SkillBox[SkillButtonIndex - 1].BoxRect.top + 1 + (256 - sinMoveKindInter[SIN_SKILL]),
							   lpSelectSkill, 0, 0, 49, 46);

				}
				else
				{
					DrawSprite(sinSkill.SkillBox[SkillButtonIndex - 1].BoxRect.left,
							   sinSkill.SkillBox[SkillButtonIndex - 1].BoxRect.top + (256 - sinMoveKindInter[SIN_SKILL]),
							   lpSelectSkill, 0, 0, 49, 46);
				}
			}

		}


		for(i = 0; i < ChangeJobSkillPlus; i++)
		{
			if(sinSkill.UseSkill[i].Flag)
			{
				if(sinSkill.UseSkill[i].ShortKey)
				{
					DrawSprite(sinSkill.SkillBox[i].BoxRect.left + 9, sinSkill.SkillBox[i].BoxRect.top - 6 + (256 - sinMoveKindInter[SIN_SKILL]),
							   lpShortKey[sinSkill.UseSkill[i].ShortKey - 1], 0, 0, 16, 16);

				}
			}
		}
	}

	if(SkillMasteryShowFlag)
	{
		DrawSprite(UseSkillMasteryPosi.x, UseSkillMasteryPosi.y + (256 - sinMoveKindInter[SIN_SKILL]), lpMasteryInfo, 0, 0, 39, 27);
	}


	if(sinSkill.pLeftSkill)
	{
		if(sinSkill.pLeftSkill->UseSkillFlag)
			DrawSprite(sLeftRightSkill[0].BoxRect.left, sLeftRightSkill[0].BoxRect.top,
					   lpSkillButton[sinSkill.pLeftSkill->Position - 1], 0, 0, 49, 46);
		else
			DrawSprite(sLeftRightSkill[0].BoxRect.left, sLeftRightSkill[0].BoxRect.top,
					   lpSkillButton_Gray[sinSkill.pLeftSkill->Position - 1], 0, 0, 49, 46);


	}
	else
	{
		DrawSprite(sLeftRightSkill[0].BoxRect.left, sLeftRightSkill[0].BoxRect.top,
				   lpSkillBoxBack, 0, 0, 49, 46);

	}
	if(sinSkill.pRightSkill)
	{
		if(sinSkill.pRightSkill->UseSkillFlag)
			DrawSprite(sLeftRightSkill[1].BoxRect.left, sLeftRightSkill[1].BoxRect.top,
					   lpSkillButton[sinSkill.pRightSkill->Position - 1], 0, 0, 49, 46);
		else
			DrawSprite(sLeftRightSkill[1].BoxRect.left, sLeftRightSkill[1].BoxRect.top,
					   lpSkillButton_Gray[sinSkill.pRightSkill->Position - 1], 0, 0, 49, 46);


	}
	else
	{
		DrawSprite(sLeftRightSkill[1].BoxRect.left, sLeftRightSkill[1].BoxRect.top,
				   lpSkillBoxBack, 0, 0, 49, 46);

	}


}

void cSKILL::Main()
{

	int i = 0, j = 0;
	int k = 0, Num = 0;

	sSKILL  TempSkillData;
	CheckContinueIcon();
	memset(TempContinueSkill, 0, sizeof(sSKILL) * 10);

	for(k = 0; k < MAX_CONTINUE_SKILL; k++)
	{
		if(ContinueSkill[k].Flag)
		{
			if(ContinueSkill[k].MatIcon)
			{
				if(Num * 32 > ContinueSkill[k].IconPosiX)
				{
					ContinueSkill[k].IconPosiX += 2;
				}
				else if(Num * 32 < ContinueSkill[k].IconPosiX)
				{
					ContinueSkill[k].IconPosiX -= 2;

				}
				if(ContinueSkill[k].CheckTime < 255)
				{
					ContinueSkill[k].IconAlpha++;
				}
				if(ContinueSkill[k].CheckTime >= 255)
				{
					ContinueSkill[k].IconAlpha = 255;

				}
				if(((ContinueSkill[k].UseTime * 70) - ContinueSkill[k].CheckTime) < 180)
				{
					ContinueSkill[k].IconAlpha--;
				}
				if(ContinueSkill[k].IconAlpha > 255)ContinueSkill[k].IconAlpha = 255;
				if(ContinueSkill[k].IconAlpha < 0)ContinueSkill[k].IconAlpha = 0;

				if(ContinueSkill[k].CheckTime > (ContinueSkill[k].UseTime - 4) * 70)
				{
					ContinueSkill[k].IconTime++;
					if(ContinueSkill[k].IconTime > 30)
					{
						ContinueSkill[k].IconTime = 0;
						ContinueSkill[k].IconFlag ^= 1;
					}
				}

				memcpy(&TempContinueSkill[Num], &ContinueSkill[k], sizeof(sSKILL));
				Num++;

			}
		}
	}


	int TempXPosi = 0;
	for(i = Num; i > 0; i--)
	{
		for(j = 0; j < i; j++)
		{
			if(TempContinueSkill[j].CheckTime < TempContinueSkill[j + 1].CheckTime)
			{
				if(TempContinueSkill[j].CheckTime != 0)
				{
					TempSkillData = TempContinueSkill[j + 1];
					TempXPosi = TempContinueSkill[j + 1].IconPosiX;
					TempContinueSkill[j + 1] = TempContinueSkill[j];
					TempContinueSkill[j + 1].IconPosiX = TempXPosi;
					TempXPosi = TempContinueSkill[j].IconPosiX;
					TempContinueSkill[j] = TempSkillData;
					TempContinueSkill[j].IconPosiX = TempXPosi;
				}
			}
		}
	}



	if(AddVirtualLife[1])
	{
		CheckVirtualLifeTime++;
		if(CheckVirtualLifeTime >= sinVirtualLifeTime * 70)
		{
			CheckVirtualLifeTime = 0;
			AddVirtualLife[0] = 0;
			AddVirtualLife[1] = 0;
			sinVirtualLifePercent = 0;
		}
	}


	if(AddBoosterLife)
	{
		CheckBoosterLifeTime++;
		if(CheckBoosterLifeTime >= BoosterLifeTime * 70)
		{
			CheckBoosterLifeTime = 0;
			AddBoosterLife = 0;
			BoosterLifePercent = 0;
			tempLife[0] = 0;
			LifeFlag = 0;
		}
	}



	if(AddVirtualLife[1] && !AddBoosterLife)
	{
		for(i = 0; i < 10; i++)
		{
			if(ContinueSkill[i].Flag)
			{
				if(ContinueSkill[i].CODE == SKILL_VIRTUAL_LIFE)
				{
					AddVirtualLife[1] = ((int)sinChar->Life[1] * Virtual_Life_Percent[ContinueSkill[i].Point - 1]) / 100;
				}
			}
		}
	}


	if(AddVirtualMana[1])
	{
		CheckVirtualManaTime++;
		if(CheckVirtualManaTime >= sinVirtualManaTime * 70)
		{
			CheckVirtualManaTime = 0;
			AddVirtualMana[0] = 0;
			AddVirtualMana[1] = 0;
			sinVirtualManaPercent = 0;
			tempMana[0] = 0;
			ManaFlag = 0;
		}
	}


	if(AddVirtualStamina[1])
	{
		CheckVirtualStaminaTime++;
		if(CheckVirtualStaminaTime >= sinVirtualStaminaTime * 70)
		{
			CheckVirtualStaminaTime = 0;
			AddVirtualStamina[0] = 0;
			AddVirtualStamina[1] = 0;
			sinVirtualStaminaPercent = 0;
			tempStamina[0] = 0;
			StaminaFlag = 0;
		}
	}


	if(sinAddSkillDelay)
	{
		CheckSkillDelayTime++;
		if(CheckSkillDelayTime >= sinSkillDelayTime * 70)
		{
			CheckSkillDelayTime = 0;
			sinAddSkillDelay = 0;
			sinSkillDelayTime = 0;
			SkillDelayFlag = 0;
		}
	}

	sinCheckContinueSkill();
	CheckSkillData();
	if(!ClearSkillCODE || !cSkill.OpenFlag || pCursorPos.y < 400)
	{
		ClearSkillCODE = 0;
		SkillInfoShowFlag = 0;

	}

	SkillMasteryShowFlag = 0;
	SelectInterSkill = 0;
	CheckingNowSkillState();


	sinCheckChageJob();

	ShowSkillClose = 0;
	SkillButtonIndex = 0;

	int Space = 0;
	sSKILLBOX TempSkillBox;
	ContinueSkillMouseIndex = 0;
	for(i = 0; i < MAX_CONTINUE_SKILL; i++)
	{
		if(TempContinueSkill[i].Flag)
		{
			if(TempContinueSkill[i].MatIcon)
			{
				if(10 + (Space * 32) < pCursorPos.x && 10 + (Space * 32) + 32 > pCursorPos.x &&
				   10 < pCursorPos.y && 10 + 32 > pCursorPos.y)
				{
					TempSkillBox.BoxRect.left = 10 + (Space * 32);
					TempSkillBox.BoxRect.top = 10 + 32;
					SkillInfoShowFlag = 2;
					ContinueSkillMouseIndex = i + 1;
					ShowSkillInfo(&TempContinueSkill[i], &TempSkillBox, 1);
				}
				Space++;
			}
		}
	}


	if(269 < pCursorPos.x && 287 > pCursorPos.x && 571 < pCursorPos.y && 590 > pCursorPos.y)
		ShowSkillClose = 1;

	if(OpenFlag && !SkillMain2OpenFlag)
	{
		for(int i = 0; i < ChangeJobSkillPlus; i++)
		{
			if(sinSkill.UseSkill[i].Flag)
			{
				if(sinSkill.SkillBox[i].BoxRect.left < pCursorPos.x && sinSkill.SkillBox[i].BoxRect.right > pCursorPos.x &&
				   sinSkill.SkillBox[i].BoxRect.top < pCursorPos.y && sinSkill.SkillBox[i].BoxRect.bottom > pCursorPos.y)
				{
					SkillButtonIndex = i + 1;

					sinSkill.UseSkill[i].Position = i + 1;
					ShowSkillInfo(&sinSkill.UseSkill[i], &sinSkill.SkillBox[i]);
					SkillInfoShowFlag = 1;

					if(sinSkill.UseSkill[i].Point && SkillMasterFlag)
						SearchClearSkillPoint(sinSkill.UseSkill[i].CODE);





				}
				if(sinSkill.SkillBox[i].GageRect.left < pCursorPos.x && sinSkill.SkillBox[i].GageRect.right > pCursorPos.x &&
				   sinSkill.SkillBox[i].GageRect.top < pCursorPos.y && sinSkill.SkillBox[i].GageRect.bottom > pCursorPos.y)
				{
					if(sinSkill.UseSkill[i].Skill_Info.USECODE != SIN_SKILL_USE_NOT)
					{
						GetSkillMastery(&sinSkill.UseSkill[i], &sinSkill.SkillBox[i]);
						SkillMasteryShowFlag = 1;
					}
				}
			}
		}
	}
	for(i = 0; i < 2; i++)
	{
		if(sLeftRightSkill[i].BoxRect.left < pCursorPos.x && sLeftRightSkill[i].BoxRect.right > pCursorPos.x &&
		   sLeftRightSkill[i].BoxRect.top < pCursorPos.y && sLeftRightSkill[i].BoxRect.bottom > pCursorPos.y)
		{
			if(i == 0 && sinSkill.pLeftSkill)
			{
				cHelpPet.PetMessage("*LeftSkill", 0);
				ShowSkillInfo(sinSkill.pLeftSkill, &sLeftRightSkill[i]);
				SkillInfoShowFlag = 1;
				SelectInterSkill = 1;
			}
			if(i == 1 && sinSkill.pRightSkill)
			{
				cHelpPet.PetMessage("*RightSkill", 0);
				ShowSkillInfo(sinSkill.pRightSkill, &sLeftRightSkill[i]);
				SkillInfoShowFlag = 1;
				SelectInterSkill = 2;
			}

		}
	}

	if(OpenFlag&&SkillMain2OpenFlag)
	{

		if(12 < pCursorPos.x && 12 + 20 > pCursorPos.x &&
		   482 < pCursorPos.y && 482 + 20 > pCursorPos.y)
		{
			SkillMain2ButtonFlag[0] = 1;
		}
		else
		{
			SkillMain2ButtonFlag[0] = 0;
		}

	}
	if(OpenFlag && !SkillMain2OpenFlag)
	{

		if(765 < pCursorPos.x && 765 + 20 > pCursorPos.x &&
		   482 < pCursorPos.y && 482 + 20 > pCursorPos.y)
		{
			SkillMain2ButtonFlag[1] = 1;
		}
		else
		{
			SkillMain2ButtonFlag[1] = 0;
		}
	}

}

void cSKILL::Close()
{

}

void cSKILL::LButtonDown(int x, int y)
{

	for(int i = 0; i < 2; i++)
	{
		if(sLeftRightSkill[i].BoxRect.left < pCursorPos.x && sLeftRightSkill[i].BoxRect.right > pCursorPos.x &&
		   sLeftRightSkill[i].BoxRect.top < pCursorPos.y && sLeftRightSkill[i].BoxRect.bottom > pCursorPos.y)
		{
			if(i == 0 && sinSkill.pLeftSkill)
			{
				cHelpPet.PetMessage("*LeftSkill", 1);
			}
			if(i == 1 && sinSkill.pRightSkill)
			{
				cHelpPet.PetMessage("*RightSkill", 1);
			}

		}
	}


	if(ClearSkillButtonPosi.x  < pCursorPos.x  && ClearSkillButtonPosi.x + 45 > pCursorPos.x  &&
	   ClearSkillButtonPosi.y <  pCursorPos.y  && ClearSkillButtonPosi.y + 45 > pCursorPos.y)
	{
		ClearSkillPointSection();

	}


	DownButtonUseShorKey = 0;
	LDownButtonIndex = 0;
	if(ShowSkillClose)
	{
		OpenFlag = 0;
	}

	if(SkillButtonIndex)
	{
		if(sinSkill.UseSkill[SkillButtonIndex - 1].Flag)
		{
			LDownButtonIndex = SkillButtonIndex;
		}
	}

	DownButtonIndex = 0;
	if(ShowSkillClose)
	{
		OpenFlag = 0;
	}
	if(SkillButtonIndex <= 13 && SkillMasterFlag == 1 && sinSkill.SkillPoint)
	{
		if(sinSkill.UseSkill[SkillButtonIndex - 1].Flag && sinSkill.UseSkill[SkillButtonIndex - 1].Use && sinSkill.UseSkill[SkillButtonIndex - 1].Point < 10)
		{
			DownButtonIndex = SkillButtonIndex;
			Skill4ButtonIndex = SkillButtonIndex;
		}
	}
	if(SkillButtonIndex > 13 && SkillMasterFlag == 1 && sinSkill.SkillPoint4)
	{
		if(sinSkill.UseSkill[SkillButtonIndex - 1].Flag && sinSkill.UseSkill[SkillButtonIndex - 1].Use && sinSkill.UseSkill[SkillButtonIndex - 1].Point < 10)
		{
			DownButtonIndex = SkillButtonIndex;
			Skill4ButtonIndex = SkillButtonIndex;
		}
	}


	if(SelectInterSkill)
	{
		if(cSkill.OpenFlag == SIN_CLOSE)cSkill.OpenFlag = SIN_OPEN;
		else cSkill.OpenFlag = SIN_CLOSE;
		cInterFace.CheckAllBox(SIN_SKILL);
		if(cSkill.OpenFlag)
		{
			if(!sinFireShow)
			{
				StartMenuFlame(0, 350);
				sinPlaySound(0);
			}
			else
				sinPlaySound(SIN_SOUND_SHOW_INTER);
			sinFireShow = 1;
		}
	}



	if(SkillMain2ButtonFlag[1])
	{
		SkillMain2ButtonFlag[1] = 0;
		SkillMain2OpenFlag = 1;
		if(!lpSkillMain2)
			lpSkillMain2 = LoadDibSurfaceOffscreen("Image\\SinImage\\skill\\Skil25.bmp");
	}

	if(SkillMain2ButtonFlag[0])
	{
		SkillMain2ButtonFlag[0] = 0;
		SkillMain2OpenFlag = 0;
	}


}

void cSKILL::LButtonUp(int x, int y)
{

	DownButtonIndex = 0;
	LDownButtonIndex = 0;
	if(SkillButtonIndex && !DownButtonUseShorKey)
	{
		if((sinSkill.UseSkill[SkillButtonIndex - 1].Skill_Info.USECODE == SIN_SKILL_USE_LEFT ||
			sinSkill.UseSkill[SkillButtonIndex - 1].Skill_Info.USECODE == SIN_SKILL_USE_ALL) && !SkillMasterFlag
		   &&sinSkill.UseSkill[SkillButtonIndex - 1].Point)
			sinSkill.pLeftSkill = &sinSkill.UseSkill[SkillButtonIndex - 1];

	}




	if(SkillButtonIndex != 1 && SkillMasterFlag == 1)
	{

		if(SkillButtonIndex > 13 && sinSkill.SkillPoint4 > 0)
		{
			if(sinSkill.UseSkill[SkillButtonIndex - 1].Flag && sinSkill.UseSkill[SkillButtonIndex - 1].Use)
			{
				if(sinSkill.UseSkill[SkillButtonIndex - 1].Point < MAX_USE_SKILL_POINT)
				{


					pMasterSkill = &sinSkill.UseSkill[SkillButtonIndex - 1];
					cMessageBox.ShowMessage3(MESSAGE_MASTER_SKILL, sinSkill.UseSkill[SkillButtonIndex - 1].Skill_Info.SkillName);
					ShowSkillUpInfo = 1;

				}
			}
		}

		if(SkillButtonIndex <= 13 && sinSkill.SkillPoint > 0)
		{
			if(sinSkill.UseSkill[SkillButtonIndex - 1].Flag && sinSkill.UseSkill[SkillButtonIndex - 1].Use)
			{
				if(sinSkill.UseSkill[SkillButtonIndex - 1].Point < MAX_USE_SKILL_POINT)
				{


					pMasterSkill = &sinSkill.UseSkill[SkillButtonIndex - 1];
					cMessageBox.ShowMessage3(MESSAGE_MASTER_SKILL, sinSkill.UseSkill[SkillButtonIndex - 1].Skill_Info.SkillName);
					ShowSkillUpInfo = 1;

				}
			}
		}
	}
}

void cSKILL::RButtonDown(int x, int y)
{
	for(int i = 0; i < 2; i++)
	{
		if(sLeftRightSkill[i].BoxRect.left < pCursorPos.x && sLeftRightSkill[i].BoxRect.right > pCursorPos.x &&
		   sLeftRightSkill[i].BoxRect.top < pCursorPos.y && sLeftRightSkill[i].BoxRect.bottom > pCursorPos.y)
		{
			if(i == 0 && sinSkill.pLeftSkill)
			{
				cHelpPet.PetMessage("*LeftSkill", 2);
			}
			if(i == 1 && sinSkill.pRightSkill)
			{
				cHelpPet.PetMessage("*RightSkill", 2);
			}

		}
	}

	DownButtonUseShorKey = 0;
	if(SkillButtonIndex)
	{
		if(sinSkill.UseSkill[SkillButtonIndex - 1].Flag)
		{
			RDownButtonIndex = SkillButtonIndex;
		}
	}
}

void cSKILL::RButtonUp(int x, int y)
{
	RDownButtonIndex = 0;
	LDownButtonIndex = 0;
	if(SkillButtonIndex && !DownButtonUseShorKey)
	{
		if((sinSkill.UseSkill[SkillButtonIndex - 1].Skill_Info.USECODE == SIN_SKILL_USE_RIGHT ||
			sinSkill.UseSkill[SkillButtonIndex - 1].Skill_Info.USECODE == SIN_SKILL_USE_ALL) && !SkillMasterFlag &&
		   sinSkill.UseSkill[SkillButtonIndex - 1].Point)
			sinSkill.pRightSkill = &sinSkill.UseSkill[SkillButtonIndex - 1];
	}

}

void cSKILL::KeyDown()
{



	int i = 0;
	char szKeyBuff[8] = { VK_F1,VK_F2,VK_F3,VK_F4,VK_F5,VK_F6,VK_F7,VK_F8 };
	for(i = 0; i < 8; i++)
	{
		if(sinGetKeyClick(szKeyBuff[i]))
		{
			if(SkillButtonIndex)
			{

				if(LDownButtonIndex)
				{
					if(sinSkill.UseSkill[SkillButtonIndex - 1].Skill_Info.USECODE == SIN_SKILL_USE_LEFT ||
					   sinSkill.UseSkill[SkillButtonIndex - 1].Skill_Info.USECODE == SIN_SKILL_USE_ALL &&
					   sinSkill.UseSkill[SkillButtonIndex - 1].Point && !SkillMasterFlag)
					{
						sinSkill.UseSkill[SkillButtonIndex - 1].ShortKey = i + 1;
						sinSkill.UseSkill[SkillButtonIndex - 1].MousePosi = SIN_MOUSE_POSI_LEFT;
						DownButtonUseShorKey = 1;
					}
				}
				else
				{
					if(RDownButtonIndex)
					{
						if(sinSkill.UseSkill[SkillButtonIndex - 1].Skill_Info.USECODE == SIN_SKILL_USE_RIGHT ||
						   sinSkill.UseSkill[SkillButtonIndex - 1].Skill_Info.USECODE == SIN_SKILL_USE_ALL &&
						   sinSkill.UseSkill[SkillButtonIndex - 1].Point && !SkillMasterFlag)
						{
							sinSkill.UseSkill[SkillButtonIndex - 1].ShortKey = i + 1;
							sinSkill.UseSkill[SkillButtonIndex - 1].MousePosi = SIN_MOUSE_POSI_RIGHT;
							DownButtonUseShorKey = 1;
						}
					}

				}

				for(int j = 0; j < 17; j++)
				{
					if(j == SkillButtonIndex - 1)continue;
					if(sinSkill.UseSkill[SkillButtonIndex - 1].ShortKey == sinSkill.UseSkill[j].ShortKey)
					{
						sinSkill.UseSkill[j].ShortKey = 0;
					}
				}
			}
			else
			{
				for(int j = 0; j < SIN_MAX_USE_SKILL; j++)
				{
					if(i == sinSkill.UseSkill[j].ShortKey - 1)
					{
						if(sinSkill.UseSkill[j].Point)
						{
							if(sinSkill.UseSkill[j].MousePosi == SIN_MOUSE_POSI_LEFT)
							{
								sinSkill.pLeftSkill = &sinSkill.UseSkill[j];

							}
							if(sinSkill.UseSkill[j].MousePosi == SIN_MOUSE_POSI_RIGHT)
							{
								sinSkill.pRightSkill = &sinSkill.UseSkill[j];
							}
						}
					}
				}
			}
		}
	}
	if(sinGetKeyClick('S'))
	{
		cHelpPet.PetMessage("*Skill", 3);
		if(cSkill.OpenFlag)cSkill.OpenFlag = SIN_CLOSE;
		else cSkill.OpenFlag = SIN_OPEN;
		cInterFace.CheckAllBox(SIN_SKILL);
		if(cSkill.OpenFlag)
		{
			if(!sinFireShow)
			{
				StartMenuFlame(0, 350);
				sinPlaySound(0);
			}
			else
				sinPlaySound(SIN_SOUND_SHOW_INTER);
			sinFireShow = 1;
		}
	}

}



int cSKILL::SearchUseSkill()
{

	switch(sinChar->JOB_CODE)
	{
		case 1:
		UseSkillBox = GROUP_FIGHTER;

		break;
		case 2:
		UseSkillBox = GROUP_MECHANICIAN;

		break;
		case 3:
		UseSkillBox = GROUP_ARCHER;

		break;
		case 4:
		UseSkillBox = GROUP_PIKEMAN;

		break;
		case 5:
		UseSkillBox = GROUP_ATALANTA;
		break;
		case 6:
		UseSkillBox = GROUP_KNIGHT;
		break;
		case 7:
		UseSkillBox = GROUP_MAGICIAN;
		break;
		case 8:
		UseSkillBox = GROUP_PRIESTESS;
		break;

	}
	if(!UseSkillBox)
		return FALSE;

	int Index = 0;
	memcpy(&sinSkill.UseSkill[0], &sSkill[0], sizeof(sSKILL));
	sinSkill.UseSkill[0].Flag = 1;
	sinSkill.UseSkill[0].Use = 1;
	sinSkill.UseSkill[0].Skill_Info.USECODE = SIN_SKILL_USE_ALL;
	sinSkill.UseSkill[0].Point = 1;

	for(int i = 0; i < SIN_MAX_SKILL; i++)
	{
		if((sSkill[i].CODE & sinSKILL_MASK1) == UseSkillBox)
		{
			for(int j = 1; j < SIN_MAX_USE_SKILL; j++)
			{
				if(!sinSkill.UseSkill[j].Flag)
				{
					memcpy(&sinSkill.UseSkill[j], &sSkill[i], sizeof(sSKILL));
					for(int k = 0; k < SIN_MAX_SKILL; k++)
					{
						if(sinSkill.UseSkill[j].CODE == sSkill_Info[k].CODE)
						{
							memcpy(&sinSkill.UseSkill[j].Skill_Info, &sSkill_Info[k], sizeof(sSKILL_INFO));
							sinSkill.UseSkill[j].Skill_Info.SkillNum = j - 1;
							break;
						}
					}
					sinSkill.UseSkill[j].Flag = 1;




					break;
				}
			}
		}
	}
	memcpy(&sinSkill.SkillBox, &sSkillBox, sizeof(sSKILLBOX)*SIN_MAX_USE_SKILL);

	LoadUseSkillImage();

	sinSkill.UseSkill[0].Use = 1;
	sinSkill.UseSkill[0].Skill_Info.USECODE = SIN_SKILL_USE_ALL;
	sinSkill.UseSkill[0].Point = 1;
	ReFormCharSkillInfo();
	return FALSE;
}

void cSKILL::DrawSkillText()
{
	HDC	hdc = NULL;
	if(SkillInfoShowFlag || sinMoveKindInter[SIN_SKILL])
	{

		int BoldFlag = 0;
		int MasteryLen = 0;
		int MasteryShowX = 0;

		char strBuff[128];
		memset(strBuff, 0, sizeof(strBuff));
		//renderDevice.lpDDSBack->GetDC(&hdc);
		SelectObject(hdc, sinFont);
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(255, 255, 255));

		if(OpenFlag)
		{

			if(sinSkill.SkillPoint >= 0 || sinSkill.SkillPoint4 >= 0)
			{

				wsprintf(strBuff, "%d", sinSkill.SkillPoint);
				dsTextLineOut(hdc, CheckEditSize(165, 253, strBuff), 578 + (256 - sinMoveKindInter[SIN_SKILL]),
							  strBuff, lstrlen(strBuff));


				wsprintf(strBuff, "%d", sinSkill.SkillPoint4);
				dsTextLineOut(hdc, CheckEditSize(250, 253, strBuff), 578 + (256 - sinMoveKindInter[SIN_SKILL]),
							  strBuff, lstrlen(strBuff));

			}

			if(SkillMasteryShowFlag)
			{
				MasteryLen = lstrlen(szUseSkillMastery);
				strcpy_s(strBuff, szUseSkillMastery);
				MasteryShowX = UseSkillMasteryPosi.x + (12 / MasteryLen);
				if(MasteryLen <= 2)MasteryShowX += 4;
				dsTextLineOut(hdc, MasteryShowX, UseSkillMasteryPosi.y + 6 + (256 - sinMoveKindInter[SIN_SKILL]),
							  strBuff, lstrlen(strBuff));


			}
		}
		int SetTextXposi = 0, SetTextXposi2 = 0;
		char *pSkillInfo[40];
		char *pSkillInfo2[40];
		int len = 0, len2 = 0;
		int Count = 0;
		int Textlen = 0, Textlen2 = 0;
		int TempCnt = 0, TempCnt2 = 0;

		char szSkillInfoBuffBack[5000] = { 0 };
		char szSkillInfoBuff2Back[5000] = { 0 };


		ZeroMemory(pSkillInfo, sizeof(pSkillInfo));
		ZeroMemory(pSkillInfo2, sizeof(pSkillInfo2));


		strcpy_s(szSkillInfoBuffBack, szSkillInfoBuff);
		strcpy_s(szSkillInfoBuff2Back, szSkillInfoBuff2);

		len = lstrlen(szSkillInfoBuff);
		len2 = lstrlen(szSkillInfoBuff2);

		SetTextColor(hdc, RGB(255, 255, 255));


		if(SkillInfoShowFlag && !ShowSkillUpInfo)
		{
			if(SkillInfoShowFlag == 2)
			{
				dsDrawOffsetArray = dsARRAY_TOP;
			}

			for(int i = 0; i < len; i++)
			{
				for(int j = 0; j < len2; j++)
				{
					if(szSkillInfoBuffBack[i] == '\r')
					{
						if(szSkillInfoBuff2Back[j] == '\r')
						{
							pSkillInfo[Count] = &szSkillInfoBuffBack[TempCnt];
							pSkillInfo2[Count] = &szSkillInfoBuff2Back[TempCnt2];
							TempCnt = i + 1;
							TempCnt2 = j + 1;
							szSkillInfoBuffBack[i] = 0;
							szSkillInfoBuff2Back[j] = 0;

							Textlen = lstrlen(pSkillInfo[Count]);
							Textlen2 = lstrlen(pSkillInfo2[Count]);

							SetTextXposi = (SkillInfoBoxPosi.x + 120) - ((Textlen / 2) * 8);

							SIZE sizecheck = { 0 };
							GetTextExtentPoint32(hdc, pSkillInfo[Count], strlen(pSkillInfo[Count]), &sizecheck);

							SetTextXposi2 = SetTextXposi + sizecheck.cx + 2;
							if(Textlen2 > 0)
							{
								if(Textlen > 8)
									SetTextXposi--;
								if(Textlen > 10)
									SetTextXposi -= 2;
							}
							if(Textlen2 < 1)
								SetTextXposi = (SkillInfoBoxPosi.x) + (((SkillBoxSize.x * 16) - ((Textlen / 2) * 11)) / 2) - 10;


							if(Textlen2 > 12)
							{
								SetTextXposi -= 12;
								SetTextXposi2 -= 12;

							}
							SelectObject(hdc, sinFont);
							SetBkMode(hdc, TRANSPARENT);

							// Skill description colour
							//SetTextColor(hdc, RGB(239, 190, 109));
							SetTextColor(hdc, RGB(210, 210, 210));

							BoldFlag = 0;
							if(Count + 1 == 1)
							{
								SelectObject(hdc, sinBoldFont);
								SetBkMode(hdc, TRANSPARENT);
								// Skill name colour
								SetTextColor(hdc, RGB(222, 231, 255));
								dsTextLineOut(hdc, SetTextXposi, SkillInfoBoxPosi.y + 27 + ((Count - 1) * 14), pSkillInfo[Count], Textlen);
								BoldFlag = 1;

							}

							for(int t = 0; t < 6; t++)
							{
								if(Count + 1 == SkillDocLineCnt[t])
								{
									// Skill description colour
									SetTextColor(hdc, RGB(255, 255, 255));
								}
							}
							if(Count + 1 == NextSkillLevelLine)
							{
								// Skill "Next level" colour
								SetTextColor(hdc, RGB(255, 220, 0));
							}

							if(Count + 1 == SkillUseWeaponClass)
							{
								// Skill compatible items colour
								//SetTextColor(hdc, RGB(164, 199, 41));
								SetTextColor(hdc, RGB(117, 207, 0));
							}

							if(SkillMasterFlag == 1)
							{
								if(Count == SkillInfoLineCnt - 1)
								{
									SetTextColor(hdc, RGB(247, 243, 193));
								}
							}
							if(MonsterDamageLine && Count + 1 == MonsterDamageLine)
							{
								SetTextColor(hdc, RGB(220, 120, 255));
							}

							if(ChainDamageLine && Count + 1 == ChainDamageLine)
							{
								SetTextColor(hdc, RGB(170, 170, 255));
							}

							if(!BoldFlag)
							{
								dsTextLineOut(hdc, SetTextXposi, SkillInfoBoxPosi.y + 28 + ((Count - 1) * 15), pSkillInfo[Count], Textlen);

								COLORREF colour = GetTextColor(hdc);
								SetTextColor(hdc, RGB(173, 51, 243));
								dsTextLineOut(hdc, SetTextXposi2, SkillInfoBoxPosi.y + 28 + ((Count - 1) * 15), pSkillInfo2[Count], Textlen2);
								SetTextColor(hdc, colour);
								//dsTextLineOut(hdc, SetTextXposi2 + 1, SkillInfoBoxPosi.y + 28 + ((Count - 1) * 15), pSkillInfo2[Count], Textlen2);
							}

							Count++;
							break;
						}
					}
				}
			}
		}


		SetTextXposi = 0;
		SetTextXposi2 = 0;

		Count = 0;
		Textlen = 0;
		Textlen2 = 0;
		TempCnt = 0;
		TempCnt2 = 0;
		char *pSkillMasterInfo[40];
		char *pSkillMasterInfo2[40];

		char TempSkillInfo[5000];
		char TempSkillInfo2[5000];


		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(255, 255, 255));
		strcpy_s(TempSkillInfo, szSkillMasterInfoBuff);
		strcpy_s(TempSkillInfo2, szSkillMasterInfoBuff2);

		len = lstrlen(szSkillMasterInfoBuff);
		len2 = lstrlen(szSkillMasterInfoBuff2);

		int dsDrawOffsetArrayBackup = dsDrawOffsetArray;


		if(ShowSkillUpInfo)
		{
			dsDrawOffsetArray = dsARRAY_TOP;
			for(int i = 0; i < len; i++)
			{
				for(int j = 0; j < len2; j++)
				{
					if(TempSkillInfo[i] == '\r')
					{
						if(TempSkillInfo2[j] == '\r')
						{
							pSkillMasterInfo[Count] = &TempSkillInfo[TempCnt];
							pSkillMasterInfo2[Count] = &TempSkillInfo2[TempCnt2];

							TempCnt = i + 1;
							TempCnt2 = j + 1;

							TempSkillInfo[i] = 0;
							TempSkillInfo2[j] = 0;
							Textlen = lstrlen(pSkillMasterInfo[Count]);
							Textlen2 = lstrlen(pSkillMasterInfo2[Count]);

							SetTextXposi = (SkillUpInfoPosi.x + 120) - ((Textlen / 2) * 11);
							SetTextXposi2 = (SkillUpInfoPosi.x + 120) + 10;

							if(Textlen2 > 0)
							{
								if(Textlen > 8)
									SetTextXposi--;
								if(Textlen > 10)
									SetTextXposi -= 2;
							}
							if(Textlen2 < 1)
								SetTextXposi = (SkillUpInfoPosi.x) + (((SkillUpInfo.x * 16) - ((Textlen / 2) * 11)) / 2) - 10;


							SelectObject(hdc, sinFont);
							SetBkMode(hdc, TRANSPARENT);

							SetTextColor(hdc, RGB(239, 190, 109));

							BoldFlag = 0;
							if(Count + 1 == 1)
							{
								SelectObject(hdc, sinBoldFont);
								SetBkMode(hdc, TRANSPARENT);
								SetTextColor(hdc, RGB(222, 231, 255));
								dsTextLineOut(hdc, SetTextXposi, SkillUpInfoPosi.y + 27 + ((Count - 1) * 14), pSkillMasterInfo[Count], Textlen);
								BoldFlag = 1;

							}

							for(int t = 0; t < 6; t++)
							{
								if(Count + 1 == SkillDocLineCnt[t])
								{
									SetTextColor(hdc, RGB(255, 255, 255));

								}
							}
							if(Count + 1 == NextSkillLevelLine)
								SetTextColor(hdc, RGB(255, 220, 0));

							if(Count + 1 == SkillUseWeaponClass)
								SetTextColor(hdc, RGB(164, 199, 41));

							if(SkillMasterFlag == 1)
							{
								if(Count == SkillInfoLineCnt - 1)
									SetTextColor(hdc, RGB(247, 243, 193));
							}


							if(!BoldFlag)
							{
								dsTextLineOut(hdc, SetTextXposi, SkillUpInfoPosi.y + 28 + ((Count - 1) * 15), pSkillMasterInfo[Count], Textlen);
								dsTextLineOut(hdc, SetTextXposi2, SkillUpInfoPosi.y + 28 + ((Count - 1) * 15), pSkillMasterInfo2[Count], Textlen2);
								dsTextLineOut(hdc, SetTextXposi2 + 1, SkillUpInfoPosi.y + 28 + ((Count - 1) * 15), pSkillMasterInfo2[Count], Textlen2);
							}
							Count++;
							break;
						}
					}
				}
			}
			dsDrawOffsetArray = dsDrawOffsetArrayBackup;
		}

		SelectObject(hdc, sinFont);
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(255, 255, 255));







		//renderDevice.lpDDSBack->ReleaseDC(hdc);
	}

}

int JobSkillTemp = 0;

void cSKILL::CheckingNowSkillState()
{


	switch(sinChar->ChangeJob)
	{
		case 0:
		ChangeJobSkillPlus = 5;
		break;
		case 1:
		ChangeJobSkillPlus = 9;
		break;
		case 2:
		ChangeJobSkillPlus = 13;
		break;
		case 3:
		ChangeJobSkillPlus = 17;
		break;

	}
	if(JobSkillTemp != ChangeJobSkillPlus)
	{
		JobSkillTemp = ChangeJobSkillPlus;
		cInvenTory.SetItemToChar();
	}

	for(int j = 0; j < ChangeJobSkillPlus; j++)
	{
		if(j > 12)
		{
			if(sinSkill.SkillPoint4)
			{
				sinSkill.UseSkill[j].Flag = 1;
				if(sinSkill.UseSkill[j].Point <= MAX_USE_SKILL_POINT)
				{
					if(sinSkill.UseSkill[j - 1].Point)
					{
						if(sinSkill.UseSkill[j].Skill_Info.RequireLevel + (sinSkill.UseSkill[j].Point * 2) <= sinChar->Level)
							sinSkill.UseSkill[j].Use = 1;
						else
							sinSkill.UseSkill[j].Use = 0;
					}
				}
			}
			else
			{
				sinSkill.UseSkill[j].Use = 0;
			}
			continue;
		}
		if(sinSkill.SkillPoint)
		{
			sinSkill.UseSkill[j].Flag = 1;
			if(sinSkill.UseSkill[j].Point <= MAX_USE_SKILL_POINT)
			{
				if(j == 0)continue;
				if(sinSkill.UseSkill[j - 1].Point)
				{
					if(sinSkill.UseSkill[j].Skill_Info.RequireLevel + (sinSkill.UseSkill[j].Point * 2) <= sinChar->Level)
						sinSkill.UseSkill[j].Use = 1;
					else
						sinSkill.UseSkill[j].Use = 0;
				}
			}
		}
		else
		{
			sinSkill.UseSkill[j].Use = 0;
		}
	}
}




void cSKILL::CheckSkillMastery()
{

	int TempLenght = 0;

	int TempTalent = 0;



	if(sinSkill.pLeftSkill)
	{
		if(!sinSkill.pLeftSkill->Point)
			sinSkill.pLeftSkill->UseSkillFlag = 0;
	}
	if(sinSkill.pRightSkill)
	{
		if(!sinSkill.pRightSkill->Point)
			sinSkill.pRightSkill->UseSkillFlag = 0;
	}

	for(int j = 1; j < SIN_MAX_USE_SKILL; j++)
	{
		if(sinSkill.UseSkill[j].Flag && sinSkill.UseSkill[j].Point)
		{

			CheckSkillMasteryForm(0, j);

			if(sinSkill.UseSkill[j].Mastery == 0)
			{
				sinSkill.UseSkill[j].GageLength = 0;
				sinSkill.UseSkill[j].GageLength2 = 0;
				SkillCountTime2[j] = 0;

			}


			TempTalent = (int)(sinChar->Talent / 3) + (int)sinAdd_fMagic_Mastery;
			if(TempTalent > 50)TempTalent = 50;
			sinSkill.UseSkill[j].UseSkillMastery = (int)(TempTalent * 100) + sinSkill.UseSkill[j].UseSkillCount;
			if(sinSkill.UseSkill[j].Skill_Info.Element[0])
			{
				sinSkill.UseSkill[j].UseSkillMastery = 10000;

			}

			if(sinSkill.UseSkill[j].UseSkillMastery >= 10000)sinSkill.UseSkill[j].UseSkillMastery = 10000;
			if(sinSkill.UseSkill[j].UseSkillMastery)
			{
				sinSkill.UseSkill[j].UseSkillMasteryGage = (int)((35 * ((float)sinSkill.UseSkill[j].UseSkillMastery / 10000)));
				if(sinSkill.UseSkill[j].UseSkillMasteryGage > 35)sinSkill.UseSkill[j].UseSkillMasteryGage = 35;
			}

			sinSkill.UseSkill[j].Mastery = (sinSkill.UseSkill[j].Skill_Info.RequireMastery[0] + (sinSkill.UseSkill[j].Skill_Info.RequireMastery[1] * sinSkill.UseSkill[j].Point) -
				(sinSkill.UseSkill[j].UseSkillMastery / 100));
			if(sinSkill.UseSkill[j].Mastery <= 0) sinSkill.UseSkill[j].Mastery = 1;
			if(sinSkill.UseSkill[j].Mastery > 70)sinSkill.UseSkill[j].Mastery = 70;


			if(sinAddSkillDelay)
			{
				sinSkill.UseSkill[j].Mastery = 1;
			}

			else
			{
				sinSkill.UseSkill[j].Mastery = (sinSkill.UseSkill[j].Skill_Info.RequireMastery[0] + (sinSkill.UseSkill[j].Skill_Info.RequireMastery[1] * sinSkill.UseSkill[j].Point) -
					(sinSkill.UseSkill[j].UseSkillMastery / 100));

				if(sinSkill.UseSkill[j].Mastery <= 0) sinSkill.UseSkill[j].Mastery = 1;
				if(sinSkill.UseSkill[j].Mastery > 70)sinSkill.UseSkill[j].Mastery = 70;
			}


			TempLenght = (int)(35 / ((float)sinSkill.UseSkill[j].Mastery / 2));

			sinSkill.UseSkill[j].GageLength2 += TempLenght;

			if(sinSkill.UseSkill[j].GageLength < sinSkill.UseSkill[j].GageLength2)
			{
				SkillCountTime2[j]++;
				if(SkillCountTime2[j] >= (int)(35 / (float)TempLenght))
				{
					sinSkill.UseSkill[j].GageLength++;
					SkillCountTime2[j] = 0;

				}

			}

			if(sinSkill.UseSkill[j].GageLength >= 35)
			{
				sinSkill.UseSkill[j].GageLength = 35;
				sinSkill.UseSkill[j].GageLength2 = 35;
				sinSkill.UseSkill[j].UseSkillFlag = 1;
				CheckUseSkillState(&sinSkill.UseSkill[j]);


			}
			else
				sinSkill.UseSkill[j].UseSkillFlag = 0;

			ReformSkillMasteryForm(0, j);

		}

	}


}

DWORD UseSkillItemInfo[10] = { 0,sinWA1,sinWM1,sinWH1,sinDS1,sinWP1,sinWS2,sinWC1,sinWS1,sinWT1 };





int cSKILL::ShowSkillInfo(sSKILL *pSkill, sSKILLBOX *pSkillBox, int Icon)
{

	if(ShowSkillUpInfo)return TRUE;

	int PlusMinD = 0;
	int PlusMaxD = 0;

	int DivideMin = 8;
	int DivideMax = 4;

	int sinTemp1 = 0;
	int sinTemp2 = 0;
	int LeftSpot = 0;
	int RightSpot = 0;

	int TempPoint = 0;

	int i = 0;
	int j = 0;


	int TempLife = 0, TempMana = 0;



	int LineCount = 0;
	for(int p = 0; p < 6; p++)
		SkillDocLineCnt[p] = 0;
	for(int p = 0; p < 10; p++)
		SkillIconIndex[p] = 0;
	int CopyCount = 0;
	int	SkillDoclen = 0;
	NextSkillLevelLine = 0;
	SkillUseWeaponClass = 0;
	SkillInconCnt = 0;
	char szTempSkillDoc[256];
	char szTempSkillDoc2[256];

	char *szTemp = "\r";
	memset(&szTempSkillDoc, 0, sizeof(szTempSkillDoc));
	memset(&szTempSkillDoc2, 0, sizeof(szTempSkillDoc2));
	memset(&szSkillInfoBuff, 0, sizeof(szSkillInfoBuff));
	memset(&szSkillInfoBuff2, 0, sizeof(szSkillInfoBuff2));


	if(pSkill->CODE == SKILL_NORMAL_ATTACK)
	{
		wsprintf(szSkillInfoBuff, "%s\r", NormalAttckName);
		strcpy_s(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		GetInfoBoxSize(pSkillBox, LineCount);
		return TRUE;

	}


	if(pSkill->Point)
	{
		if(pSkill->CODE == SKILL_FORCE_ORB || pSkill->CODE == CHANGE_JOB3_QUEST || pSkill->CODE == CHANGE_ELEMENTARY_QUEST)
		{
			wsprintf(szSkillInfoBuff, "%s\r", pSkill->Skill_Info.SkillName);
		}
		else
		{
			wsprintf(szSkillInfoBuff, "%s LV:%d\r", pSkill->Skill_Info.SkillName, pSkill->Point);
		}
		strcpy_s(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;

		if(pSkill->Point < 10)
		{
			if(!Icon)
			{
				wsprintf(szTempSkillDoc2, RequirLevel3, pSkill->Skill_Info.RequireLevel + (pSkill->Point * 2));
				lstrcat(szSkillInfoBuff, szTempSkillDoc2);
				strcpy_s(szTempSkillDoc2, "\r");
				lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
				LineCount++;
			}
		}

	}
	else
	{
		if(pSkill->CODE == CLANSKILL_ABSORB || pSkill->CODE == CLANSKILL_EVASION || pSkill->CODE == CLANSKILL_ATTACK ||
		   pSkill->CODE == SOD_SKILL_GOLD || pSkill->CODE == SOD_SKILL_SILVER || pSkill->CODE == SOD_SKILL_BRONZE ||
		   pSkill->CODE == SCROLL_INVULNERABILITY || pSkill->CODE == SCROLL_CRITICAL || pSkill->CODE == SCROLL_EVASION ||
		   pSkill->CODE == STONE_R_FIRECRYTAL || pSkill->CODE == STONE_R_ICECRYTAL || pSkill->CODE == STONE_R_LINGHTINGCRYTAL ||
		   pSkill->CODE == STONE_A_FIGHTER || pSkill->CODE == STONE_A_MECHANICIAN || pSkill->CODE == STONE_A_PIKEMAN || pSkill->CODE == STONE_A_ARCHER ||
		   pSkill->CODE == STONE_A_KNIGHT || pSkill->CODE == STONE_A_ATALANTA || pSkill->CODE == STONE_A_MAGICIAN || pSkill->CODE == STONE_A_PRIESTESS ||
		   pSkill->CODE == SCROLL_P_INVULNERABILITY || pSkill->CODE == SCROLL_P_CRITICAL || pSkill->CODE == SCROLL_P_EVASION ||
		   pSkill->CODE == BOOSTER_ITEM_LIFE || pSkill->CODE == BOOSTER_ITEM_MANA || pSkill->CODE == BOOSTER_ITEM_STAMINA)
		{
			wsprintf(szSkillInfoBuff, "%s\r", pSkill->Skill_Info.SkillName);
		}
		else
		{
			wsprintf(szSkillInfoBuff, RequirLevel, pSkill->Skill_Info.SkillName, pSkill->Skill_Info.RequireLevel + (pSkill->Point * 2));
		}
		strcpy_s(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;

	}

	SkillDoclen = lstrlen(pSkill->Skill_Info.SkillDoc);

	BYTE ch;
	int StrCnt;
	int cnt, cnt2;


	cnt2 = 0;
	StrCnt = 0;
	for(cnt = 0; cnt < SkillDoclen; cnt++)
	{
		ch = (BYTE)pSkill->Skill_Info.SkillDoc[cnt];

		if(ch >= 0x80)
		{
			szTempSkillDoc[cnt2++] = pSkill->Skill_Info.SkillDoc[cnt++];
			szTempSkillDoc[cnt2++] = pSkill->Skill_Info.SkillDoc[cnt];
			StrCnt += 2;
		}
		else
		{
			szTempSkillDoc[cnt2++] = pSkill->Skill_Info.SkillDoc[cnt];
			StrCnt++;
		}
	#ifdef	_LANGUAGE_JAPANESE      
		if(StrCnt > 26)
		{
			StrCnt = 0;
			szTempSkillDoc[cnt2++] = '\r';
			strcpy_s(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			SkillDocLineCnt[LineCount - 2] = LineCount;
		}

	#else
		if(StrCnt > 30)
		{
			StrCnt = 0;
			szTempSkillDoc[cnt2++] = '\r';
			strcpy_s(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			SkillDocLineCnt[LineCount - 2] = LineCount;
		}
	#endif
	}
	SkillDocLineCnt[LineCount + 1 - 2] = LineCount + 1;


	lstrcat(szSkillInfoBuff, szTempSkillDoc);
	lstrcat(szSkillInfoBuff, szTemp);
	strcpy_s(szTempSkillDoc2, "\r");
	lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
	LineCount++;

	if(pSkill->CODE == SCROLL_P_CRITICAL || pSkill->CODE == SCROLL_P_EVASION)
	{
		strcpy_s(szTempSkillDoc, CountinueTime);
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		wsprintf(szTempSkillDoc2, "%d%s\r", 3600, SecName);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
	}

	else if(pSkill->CODE == BOOSTER_ITEM_LIFE || pSkill->CODE == BOOSTER_ITEM_MANA || pSkill->CODE == BOOSTER_ITEM_STAMINA)
	{
		strcpy_s(szTempSkillDoc, CountinueTime);
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		wsprintf(szTempSkillDoc2, "%d%s\r", pSkill->UseTime, SecName);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
	}
	else if(pSkill->CODE == SOD_SKILL_GOLD)
	{
		lstrcat(szSkillInfoBuff2, "\r");
		lstrcat(szSkillInfoBuff, "A glória é concedida ao\rClã que sobreviveu ao Bellatra.\r\r");
		lstrcat(szSkillInfoBuff2, "\r");
		lstrcat(szSkillInfoBuff, "+ 200 de vida\r");
		lstrcat(szSkillInfoBuff2, "\r");
		lstrcat(szSkillInfoBuff2, "\r");
		lstrcat(szSkillInfoBuff2, "\r");

		LineCount = 5;
	}
	else if(pSkill->CODE == SOD_SKILL_SILVER)
	{
		lstrcat(szSkillInfoBuff2, "\r");
		lstrcat(szSkillInfoBuff, "A glória é concedida ao\rClã que sobreviveu ao Bellatra.\r\r");
		lstrcat(szSkillInfoBuff2, "\r");
		lstrcat(szSkillInfoBuff, "+ 100 de vida\r");
		lstrcat(szSkillInfoBuff2, "\r");
		lstrcat(szSkillInfoBuff2, "\r");
		lstrcat(szSkillInfoBuff2, "\r");

		LineCount = 5;
	}
	else if(pSkill->CODE == SOD_SKILL_BRONZE)
	{
		lstrcat(szSkillInfoBuff2, "\r");
		lstrcat(szSkillInfoBuff, "A glória é concedida ao\rClã que sobreviveu ao Bellatra.\r\r");
		lstrcat(szSkillInfoBuff2, "\r");
		lstrcat(szSkillInfoBuff, "+ 50 de vida\r");
		lstrcat(szSkillInfoBuff2, "\r");
		lstrcat(szSkillInfoBuff2, "\r");
		lstrcat(szSkillInfoBuff2, "\r");

		LineCount = 5;
	}

	lstrcat(szSkillInfoBuff, "\r");
	strcpy_s(szTempSkillDoc2, "\r");
	lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
	LineCount++;



	if(pSkill->Skill_Info.UseWeaponCode[0])
	{
		strcpy_s(szTempSkillDoc, UseItemGroupName);
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		strcpy_s(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		SkillUseWeaponClass = LineCount;
		for(i = 0; i < 8; i++)
		{
			if(pSkill->Skill_Info.UseWeaponCode[i])
			{
				for(int j = 0; j < 10; j++)
				{
					if(pSkill->Skill_Info.UseWeaponCode[i] == UseSkillItemInfo[j])
					{
						SkillIconIndex[i] = j;
						SkillIconPosi.y = (LineCount * 17) + 2;
						SkillInconCnt++;

					}
				}
			}
		}
	}
	if(SkillInconCnt)
	{
		SkillIconPosi.x = ((14 * 16) - (SkillInconCnt * 18)) / 2;
		lstrcat(szSkillInfoBuff, "\r");
		strcpy_s(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		lstrcat(szSkillInfoBuff, "\r");
		strcpy_s(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;

	}


	MonsterDamageLine = 0;
	ChainDamageLine = 0;

	switch(pSkill->CODE)
	{
		case SKILL_MECHANIC_BOMB:
		wsprintf(szTempSkillDoc, "(%s.%s VS %d%s %s", Mutant7, Mechanic7, 50, "%", MonsterAddDamage2);
		strcpy_s(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		case SKILL_SPARK:
		wsprintf(szTempSkillDoc, "(%s VS %d%s %s", Mechanic7, 50, "%", MonsterAddDamage2);
		strcpy_s(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		case SKILL_BRUTAL_SWING:
		wsprintf(szTempSkillDoc, "(%s VS %d%s %s", Demon7, 40, "%", MonsterAddDamage2);
		strcpy_s(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		case SKILL_JUMPING_CRASH:
		wsprintf(szTempSkillDoc, "(%s VS %d%s %s", Demon7, 30, "%", MonsterAddDamage2);
		strcpy_s(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		case SKILL_EXPANSION:
		wsprintf(szTempSkillDoc, "(%s VS %d%s %s", Mutant7, 30, "%", MonsterAddDamage2);
		strcpy_s(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		case SKILL_SWORD_BLAST:
		wsprintf(szTempSkillDoc, "(%s.%s VS %d%s %s", Nomal7, Mutant7, 30, "%", MonsterAddDamage2);
		strcpy_s(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		case SKILL_PIERCING:
		wsprintf(szTempSkillDoc, "(%s VS %d%s %s", Mutant7, 30, "%", MonsterAddDamage2);
		strcpy_s(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		case SKILL_TWIST_JAVELIN:
		wsprintf(szTempSkillDoc, "(%s VS %d%s %s", Demon7, 30, "%", MonsterAddDamage2);
		strcpy_s(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		case SKILL_FIRE_JAVELIN:
		wsprintf(szTempSkillDoc, "(%s VS %d%s %s", Mutant7, 50, "%", MonsterAddDamageFire);
		strcpy_s(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		case SKILL_WIND_ARROW:
		wsprintf(szTempSkillDoc, "(%s VS %d%s %s", Nomal7, 30, "%", MonsterAddDamage2);
		strcpy_s(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		case SKILL_PERFECT_AIM:
		wsprintf(szTempSkillDoc, "(%s VS %d%s %s", Demon7, 30, "%", MonsterAddDamage2);
		strcpy_s(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		case SKILL_METAL_ARMOR:

		wsprintf(szTempSkillDoc, "(%s %d%s %s", PhysicalAbsorb3, 120, "%", ChainDamage3);
		strcpy_s(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		ChainDamageLine = LineCount;
		break;
		case SKILL_SPARK_SHIELD:
		wsprintf(szTempSkillDoc, "(%s VS %d%s %s", Mechanic7, 50, "%", MonsterAddDamage2);
		strcpy_s(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;




		break;
		case SKILL_AVANGING_CRASH:

		wsprintf(szTempSkillDoc, "(%s %d%s %s", BrutalSwingCritical3, 50, "%", ChainDamage3);
		strcpy_s(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		ChainDamageLine = LineCount;
		break;
		case SKILL_LIGHTNING_JAVELIN:
		wsprintf(szTempSkillDoc, "(%s VS %d%s %s", Undead7, 50, "%", MonsterAddDamage2);
		strcpy_s(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		case SKILL_IMPULSION:
		wsprintf(szTempSkillDoc, "(%s VS %d%s %s", Mechanic7, 30, "%", MonsterAddDamage2);
		strcpy_s(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		case SKILL_MAGNETIC_SPHERE:
		wsprintf(szTempSkillDoc, "(%s VS %d%s %s", Mechanic7, 30, "%", MonsterAddDamage2);
		strcpy_s(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		case SKILL_DETORYER:
		wsprintf(szTempSkillDoc, "(%s VS %d%s %s", Demon7, 30, "%", MonsterAddDamage2);
		strcpy_s(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		MonsterDamageLine = LineCount;
		break;
		case SKILL_HALL_OF_VALHALLA:
		wsprintf(szTempSkillDoc, "(%s %d%s %s", Triumph4, 100, "%", ChainDamage3);
		strcpy_s(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		ChainDamageLine = LineCount;
		break;
		case SKILL_GODLY_SHIELD:
		wsprintf(szTempSkillDoc, "(%s %d%s %s", DivineShield4, 100, "%", ChainDamage3);
		strcpy_s(szTempSkillDoc2, "\r");
		lstrcat(szSkillInfoBuff, szTempSkillDoc);
		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
		ChainDamageLine = LineCount;
		break;
	}


	for(i = 0; i < 2; i++)
	{
		if(i == 1 && Icon)break;
		if(i == 1 && pSkill->Point == MAX_USE_SKILL_POINT)break;
		if(i == 0 && !pSkill->Point)continue;
		if(i == 1)
		{
			lstrcat(szSkillInfoBuff, NextLevelText);
			strcpy_s(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			NextSkillLevelLine = LineCount;
		}


		switch(pSkill->CODE)
		{

			case SKILL_EXTREME_SHIELD:
			strcpy_s(szTempSkillDoc, IncreBlock);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", E_Shield_BlockRate[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", E_Shield_UseTime[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;

			case SKILL_MECHANIC_BOMB:
			strcpy_s(szTempSkillDoc, DamageName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", Mechanic_Bomb_Damage[pSkill->Point + i - 1][0], Mechanic_Bomb_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, ShootingRangeName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Mechanic_Bomb_Attack_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;

			case SKILL_PHYSICAL_ABSORB:
			strcpy_s(szTempSkillDoc, IncreAsorb);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", P_Absorb[pSkill->Point + i - 1][0], P_Absorb[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", P_Absorb_UseTime[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			case SKILL_POISON_ATTRIBUTE:
			strcpy_s(szTempSkillDoc, PoisonName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", PlusPoison[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;

			case SKILL_GREAT_SMASH:
			strcpy_s(szTempSkillDoc, IncreAttack_RateName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", G_Smash_Attack_Rate[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, AddMaxDamage);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", G_Smash_Attack_Rage[pSkill->Point + i - 1], G_Smash_Attack_Rage[pSkill->Point + i - 1] + sinChar->Strength / 5);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", G_Smash_Attack_Rage[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;


			case SKILL_MAXIMIZE:
			strcpy_s(szTempSkillDoc, Max_DamageIncre);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Maximize_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Maximize_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;

			case SKILL_AUTOMATION:
			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Automation_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, Attack_SpeedAdd);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Automation_Speed[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Automation_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;


			case SKILL_SPARK:
			strcpy_s(szTempSkillDoc, DamageName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d+(LV/5)\r", Spark_Damage[pSkill->Point + i - 1][0], Spark_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, AttackAreaName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Spark_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;

			case SKILL_METAL_ARMOR:

			strcpy_s(szTempSkillDoc, AddDefense8);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Metal_Armor_Defense[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Metal_Armor_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;


			break;
			case SKILL_GRAND_SMASH:

			strcpy_s(szTempSkillDoc, IncreAttack_RateName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Grand_Smash_AttackRate[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Grand_Smash_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_MECHANIC_WEAPON:
			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", M_Weapon_Mastey[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			lstrcat(szSkillInfoBuff, "\r");
			strcpy_s(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_SPARK_SHIELD:



			strcpy_s(szTempSkillDoc, SparkDamage10);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Spark_Shield_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;


			strcpy_s(szTempSkillDoc, SheildDefense);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Spark_Shield_Defense[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Spark_Shield_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;


			case SKILL_MELEE_MASTERY:
			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Melee_Mastery_DamagePercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			lstrcat(szSkillInfoBuff, "\r");
			strcpy_s(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_FIRE_ATTRIBUTE:
			strcpy_s(szTempSkillDoc, FireName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", PlusFire[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_RAVING:
			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Raving_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, HitNumName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Ravind_Speed[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, DecreLifeName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);

			sinTemp1 = (int)(Raving_UseLife[pSkill->Point + i - 1] * 10);
			RightSpot = sinTemp1 % 10;
			LeftSpot = (sinTemp1 - RightSpot) / 10;

			wsprintf(szTempSkillDoc2, "%d.%d%s\r", LeftSpot, RightSpot, "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			case SKILL_IMPACT:
			strcpy_s(szTempSkillDoc, Attck_RateAdd);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Impact_Attack_Rating[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Impact_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;

			case SKILL_TRIPLE_IMPACT:
			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", T_Impact_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, HitNumName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", T_Impact_Hit[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;

			case SKILL_BRUTAL_SWING:
			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", B_Swing_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, Add_CriticalName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", B_Swing_Critical[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			case SKILL_ROAR:
			strcpy_s(szTempSkillDoc, StunRage);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Roar_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Roar_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;

			case SKILL_RAGE_OF_ZECRAM:
			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", R_Zecram_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, FireAttackDamageAdd);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", R_Zecram_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;

			case SKILL_CONCENTRATION:
			strcpy_s(szTempSkillDoc, Attck_RateAdd5);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Concentration_AttackRate[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Concentration_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;


			break;

			case SKILL_AVANGING_CRASH:
			strcpy_s(szTempSkillDoc, AddAttack_Rate9);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", A_Crash_AttackRate[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", A_Crash_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_SWIFT_AXE:

			strcpy_s(szTempSkillDoc, Attack_SpeedAdd);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Swift_Axe_Speed[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Swift_Axe_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_BONE_CRASH:
			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", B_Crash_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, DemonDamage4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", B_Crash_DemonDamage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;


			case SKILL_PIKE_WIND:
			strcpy_s(szTempSkillDoc, DamageName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", Pike_Wind_Damage[pSkill->Point + i - 1][0], Pike_Wind_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, Push_AreaName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Pike_Wind_Push_Lenght[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;

			case SKILL_ICE_ATTRIBUTE:
			strcpy_s(szTempSkillDoc, IceName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", PlusIce[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			lstrcat(szSkillInfoBuff, "\r");
			strcpy_s(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;


			break;
			case SKILL_CRITICAL_HIT:
			strcpy_s(szTempSkillDoc, Add_CriticalName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Critical_Hit_Critical[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;

			case SKILL_JUMPING_CRASH:
			strcpy_s(szTempSkillDoc, Attck_RateAdd);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Jumping_Crash_Attack_Rating[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, PlusDamageName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Jumping_Crash_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;

			case SKILL_GROUND_PIKE:

			strcpy_s(szTempSkillDoc, sinG_Pike_Time3);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", G_Pike_Time[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;


			strcpy_s(szTempSkillDoc, IceAttackDamageAdd);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", G_Pike_Damage[pSkill->Point + i - 1][0], G_Pike_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, ShootingRangeName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", G_Pike_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;

			case SKILL_TORNADO:
			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Tornado_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, ShootingRangeName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Tornado_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;

			case SKILL_WEAPONE_DEFENCE_MASTERY:
			strcpy_s(szTempSkillDoc, DefenseRateIncre);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", W_D_Mastery_Block[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			lstrcat(szSkillInfoBuff, "\r");
			strcpy_s(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;


			break;

			case SKILL_EXPANSION:
			strcpy_s(szTempSkillDoc, WeaponSizeName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Expansion_Size[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Expansion_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_VENOM_SPEAR:
			PlusMinD = 0;
			PlusMaxD = 0;

			if(sInven[0].ItemIndex && !cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.NotUseFlag)
			{
				PlusMinD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[0];
				PlusMaxD = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[1];
			}
			strcpy_s(szTempSkillDoc, PoisonDamage3);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", VenomSpear_Damage[pSkill->Point + i - 1][0], VenomSpear_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, PikeNum4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s", VenomSpear_Num[pSkill->Point + i - 1], sinNumCount3);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, poisoningTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", VenomSpear_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, ShootingRangeName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", VenomSpear_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;

			case SKILL_VANISH:


			wsprintf(szTempSkillDoc, "%s", AfterDamage7);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Vanish_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, MonsterSight7);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Vanish_Range[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Vanish_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;

			case SKILL_CRITICAL_MASTERY:
			strcpy_s(szTempSkillDoc, PlusCriticalName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Critical_Mastery_Critical[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			lstrcat(szSkillInfoBuff, "\r");
			strcpy_s(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;

			case SKILL_CHAIN_LANCE:
			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Chain_Lance_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;


			break;


			case SKILL_SCOUT_HAWK:
			strcpy_s(szTempSkillDoc, Attck_RateAdd);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Scout_Hawk_Attack_Rate[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, HwakRotationNum);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Scout_Hawk_UseTime[pSkill->Point + i - 1], sinNum7);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			case SKILL_SHOOTING_MASTERY:
			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", S_Mastery_DamagePercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			lstrcat(szSkillInfoBuff, "\r");
			strcpy_s(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;


			break;
			case SKILL_WIND_ARROW:
			strcpy_s(szTempSkillDoc, WeaponSpeedAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Wind_Arrow_Speed[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Wind_Arrow_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			case SKILL_PERFECT_AIM:
			strcpy_s(szTempSkillDoc, IncreAttack_RateName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Perfect_Aim_Attack_Rate[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d+(LV/%d)\r", Perfect_Aim_Damage[pSkill->Point + i - 1], Perfect_Aim_Damage_LV[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			case SKILL_DIONS_EYE:
			strcpy_s(szTempSkillDoc, IncreAttack_RateName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", D_Eye_Attack_Rate[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			lstrcat(szSkillInfoBuff, "\r");
			strcpy_s(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;

			case SKILL_FALCON:
			strcpy_s(szTempSkillDoc, DamageName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", Falcon_Damage[pSkill->Point + i - 1][0], Falcon_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Falcon_Time[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;

			case SKILL_ARROW_OF_RAGE:

			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "LV/%d\r", A_Rage_Damage[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, AttackAreaName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", A_Rage_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;

			case SKILL_AVALANCHE:
			strcpy_s(szTempSkillDoc, WeaponSpeedAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Avalanche_Speed[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Avalanche_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, SeriesShootingCount);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Avalanche_ArrowNum[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			case SKILL_ELEMENTAL_SHOT:
			strcpy_s(szTempSkillDoc, FireDamage);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", Elemental_Shot_Fire[pSkill->Point + i - 1][0], Elemental_Shot_Fire[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;



			strcpy_s(szTempSkillDoc, LightningDamage);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", Elemental_Shot_Lightning[pSkill->Point + i - 1][0], Elemental_Shot_Lightning[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;

			case SKILL_GOLDEN_FALCON:
			strcpy_s(szTempSkillDoc, SpiritFalconDamage2);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Golden_Falcon_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, LifeGegenPlus);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			sinTemp1 = (int)(Golden_Falcon_LifeRegen[pSkill->Point + i - 1] * 10);
			RightSpot = sinTemp1 % 10;
			LeftSpot = (sinTemp1 - RightSpot) / 10;
			wsprintf(szTempSkillDoc2, "%d.%d\r", LeftSpot, RightSpot);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Golden_Falcon_Time[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;

			case SKILL_BOMB_SHOT:
			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", BombShot_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, DemonDamage4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", BombShot_DemonDamage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, PlusDamage4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", BombShot_AddDamage[pSkill->Point + i - 1][0], BombShot_AddDamage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, Area18);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", BombShot_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_PERFORATION:


			strcpy_s(szTempSkillDoc, AddShootingRange);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Perforation_Attack_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Perforation_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, Add_CriticalName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Perforation_Critical[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;





			case SKILL_SWORD_BLAST:
			strcpy_s(szTempSkillDoc, DamageName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d(+LV/2)\r", Sword_Blast_Damage[pSkill->Point + i - 1][0], Sword_Blast_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;


			strcpy_s(szTempSkillDoc, ShootingRangeName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Sword_Blast_ShootingRange[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_HOLY_BODY:
			strcpy_s(szTempSkillDoc, IncreAsorb);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", HolyBody_Absorb[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", HolyBody_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_PHYSICAL_TRANING:
			strcpy_s(szTempSkillDoc, sinAddStamina);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", P_Traning_Stamina[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			lstrcat(szSkillInfoBuff, "\r");
			strcpy_s(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;


			break;
			case SKILL_DOUBLE_CRASH:
			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", D_Crash_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, Add_CriticalName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", D_Crash_Critical[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_HOLY_VALOR:
			strcpy_s(szTempSkillDoc, PartyArea7);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", 300);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Holy_Valor_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Holy_Valor_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_BRANDISH:
			strcpy_s(szTempSkillDoc, Area17);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Brandish_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Brandish_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_PIERCING:
			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Piercing_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, AddAttack_Rate9);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Piercing_Attack_Rating[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, PiercingRange);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", 110);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			case SKILL_DRASTIC_SPIRIT:
			strcpy_s(szTempSkillDoc, IncreDefense);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Drastic_Spirit_Defense[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Drastic_Spirit_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;

			case SKILL_SWORD_MASTERY:
			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Sword_Mastery_DamagePercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			lstrcat(szSkillInfoBuff, "\r");
			strcpy_s(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;


			break;
			case SKILL_DIVINE_INHALATION:
			strcpy_s(szTempSkillDoc, IncreBlock);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", D_Inhalation_Block[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, DamageToLife);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", D_Inhalation_Life[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", D_Inhalation_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;

			case SKILL_HOLY_INCANTATION:
			strcpy_s(szTempSkillDoc, MyMonster7);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", H_Incantation_Success[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, LifeIncre4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", H_Incantation_AddLife[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", H_Incantation_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_GRAND_CROSS:
			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Grand_Cross_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, AddAttack_Rate9);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Grand_Cross_AttackRate[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, UndeadDamage3);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Grand_Cross_UndeadDamage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;




			case SKILL_SHIELD_STRIKE:

			strcpy_s(szTempSkillDoc, sinDamagePiercing);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			strcpy_s(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, DamageName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d(+LV/5)\r", S_Strike_Damage[pSkill->Point + i - 1][0], S_Strike_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;



			break;

			case SKILL_FARINA:
			strcpy_s(szTempSkillDoc, WeaponSpeedAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Farina_Speed[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, IncreAttack_RateName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Farina_AttackRate[pSkill->Point + i - 1], "(+LV)");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_THROWING_MASTERY:
			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", T_Mastery_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			lstrcat(szSkillInfoBuff, "\r");
			strcpy_s(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_VIGOR_SPEAR:
			strcpy_s(szTempSkillDoc, sinAddDamage7);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d+(LV/2)\r", V_Spear_Damage[pSkill->Point + i - 1][0], V_Spear_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;

			case SKILL_WINDY:
			strcpy_s(szTempSkillDoc, IncreWeaponAttack_RateName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Windy_Attack_Rating[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, AddShootingRange);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", 30);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Windy_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;


			break;
			case SKILL_TWIST_JAVELIN:
			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Twist_Javelin_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, AddAttack_Rate9);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Twist_Javelin_Attack_Rating[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_SOUL_SUCKER:
			strcpy_s(szTempSkillDoc, LifeAbsorb);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Soul_Sucker_Absorb[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			case SKILL_FIRE_JAVELIN:
			strcpy_s(szTempSkillDoc, FireDamage);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d+(LV/3)\r", Fire_Javelin_Damage[pSkill->Point + i - 1][0], Fire_Javelin_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			case SKILL_SPLIT_JAVELIN:
			strcpy_s(szTempSkillDoc, AttackNum3);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Split_Javelin_AttackNum[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Split_Javelin_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, sinAbilityName[5]);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Split_Javelin_AttackRate[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;



			break;

			case SKILL_TRIUMPH_OF_VALHALLA:
			strcpy_s(szTempSkillDoc, MaxDamagePlus2);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d+(LV/4)\r", T_Of_Valhalla_Damage[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", T_Of_Valhalla_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_LIGHTNING_JAVELIN:
			strcpy_s(szTempSkillDoc, LightningAddDamage3);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d+(LV/3)\r", Lightning_Javelin_Damage[pSkill->Point + i - 1][0], Lightning_Javelin_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			case SKILL_STORM_JAVELIN:
			strcpy_s(szTempSkillDoc, DamageAddName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Storm_Javelin_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;


			case SKILL_HEALING:
			PlusMinD = 0;
			PlusMaxD = 0;


			PlusMinD += cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[0] / 3;
			PlusMaxD += cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[1] / 3;
			PlusMinD += sinChar->Spirit / 8;
			PlusMaxD += sinChar->Spirit / 6;


			strcpy_s(szTempSkillDoc, sinAddLife);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d(+%d)-%d(+%d)\r", Healing_Heal[pSkill->Point + i - 1][0], PlusMinD, Healing_Heal[pSkill->Point + i - 1][1], PlusMaxD);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			case SKILL_HOLY_BOLT:
			wsprintf(szTempSkillDoc, "%s", DamageName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", HolyBolt_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_MULTISPARK:
			strcpy_s(szTempSkillDoc, SparkDamage);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", M_Spark_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, SparkNum7);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d%s", (M_Spark_Num[pSkill->Point + i - 1] / 2) + 1, M_Spark_Num[pSkill->Point + i - 1], sinNumCount3);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_HOLY_MIND:
			strcpy_s(szTempSkillDoc, sinDecreDamage);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", HolyMind_DecDamage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "15%s\r", SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;

			case SKILL_MEDITATION:
			strcpy_s(szTempSkillDoc, AddManaRegen);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			sinTemp1 = (int)(Meditation_Regen[pSkill->Point + i - 1] * 10);
			RightSpot = sinTemp1 % 10;
			LeftSpot = (sinTemp1 - RightSpot) / 10;
			wsprintf(szTempSkillDoc2, "%d.%d\r", LeftSpot, RightSpot);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			lstrcat(szSkillInfoBuff, "\r");
			strcpy_s(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_DIVINE_LIGHTNING:
			strcpy_s(szTempSkillDoc, AttackAreaName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", 180);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, SparkDamage);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Divine_Lightning_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, LightNum);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Divine_Lightning_Num[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_HOLY_REFLECTION:
			strcpy_s(szTempSkillDoc, ReturnDamage);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Holy_Reflection_Return_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Holy_Reflection_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_GRAND_HEALING:
			PlusMinD = 0;
			PlusMaxD = 0;




			PlusMinD += cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[0] / 3;
			PlusMaxD += cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[1] / 3;
			PlusMinD += sinChar->Spirit / 8;
			PlusMaxD += sinChar->Spirit / 6;


			strcpy_s(szTempSkillDoc, sinAddLife);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d(+%d)-%d(+%d)\r", Grand_Healing[pSkill->Point + i - 1][0], PlusMinD, Grand_Healing[pSkill->Point + i - 1][1], PlusMaxD);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, Area18);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Grand_Healing_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_VIGOR_BALL:
			wsprintf(szTempSkillDoc, "%s", DamageName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Vigor_Ball_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;

			case SKILL_RESURRECTION:
			strcpy_s(szTempSkillDoc, ReLifePercent4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Resurrection_Percent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;



			break;

			case SKILL_EXTINCTION:
			strcpy_s(szTempSkillDoc, ExtinctionPercent2);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d+(LV/5)%s\r", Extinction_Percent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, ExtinctionAmount2);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Extinction_Amount[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			case SKILL_VIRTUAL_LIFE:
			strcpy_s(szTempSkillDoc, IncreLifePercent2);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Virtual_Life_Percent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Virtual_Life_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;


			case SKILL_AGONY:
			strcpy_s(szTempSkillDoc, sinConvert4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Agony_ConvLife[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_FIRE_BOLT:
			
			wsprintf(szTempSkillDoc, "%s", DamageName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", FireBolt_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;



			strcpy_s(szTempSkillDoc, ShootingRangeName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", 200);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_ZENITH:
			strcpy_s(szTempSkillDoc, sinIncreElement);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Zenith_Element[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Zenith_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;




			break;
			case SKILL_FIRE_BALL:

			strcpy_s(szTempSkillDoc, DamageName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", FireBall_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, ShootingRangeName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", FireBall_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, AttackAreaName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", FireBall_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;


			break;
			case SKILL_MENTAL_MASTERY:
			strcpy_s(szTempSkillDoc, IncreMana5);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Mental_Mastery_Mana[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			lstrcat(szSkillInfoBuff, "\r");
			strcpy_s(szTempSkillDoc2, "\r");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;


			break;
			case SKILL_WATORNADO:
			
			strcpy_s(szTempSkillDoc, DamageName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Watornado_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, ShootingRangeName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Watornado_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, AttackAreaName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Watornado_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_ENCHANT_WEAPON:
				strcpy_s(szTempSkillDoc, FireDamage);
				lstrcat(szSkillInfoBuff, szTempSkillDoc);
				wsprintf(szTempSkillDoc2, "%d-%d\r", Enchant_Weapon_Damage_Fire[pSkill->Point + i - 1][0], Enchant_Weapon_Damage_Fire[pSkill->Point + i - 1][1]);
				lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
				LineCount++;

				strcpy_s(szTempSkillDoc, IceDamage);
				lstrcat(szSkillInfoBuff, szTempSkillDoc);
				wsprintf(szTempSkillDoc2, "%d-%d\r", Enchant_Weapon_Damage_Ice[pSkill->Point + i - 1][0], Enchant_Weapon_Damage_Ice[pSkill->Point + i - 1][1]);
				lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
				LineCount++;

				strcpy_s(szTempSkillDoc, LightningDamage);
				lstrcat(szSkillInfoBuff, szTempSkillDoc);
				wsprintf(szTempSkillDoc2, "%d-%d\r", Enchant_Weapon_Damage_Lightning[pSkill->Point + i - 1][0], Enchant_Weapon_Damage_Lightning[pSkill->Point + i - 1][1]);
				lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
				LineCount++;

				strcpy_s(szTempSkillDoc, CountinueTime);
				lstrcat(szSkillInfoBuff, szTempSkillDoc);
				wsprintf(szTempSkillDoc2, "%d%s\r", Enchant_Weapon_Time[pSkill->Point + i - 1], SecName);
				lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
				LineCount++;
			break;
			case SKILL_DEAD_RAY:
			
			strcpy_s(szTempSkillDoc, DamageName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Dead_Ray_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, ShootingRangeName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Dead_Ray_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;

			case SKILL_ENERGY_SHIELD:
			strcpy_s(szTempSkillDoc, ReduceDamage3);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Energy_Shield_DecDamage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Energy_Shield_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;

			case SKILL_DIASTROPHISM:

			strcpy_s(szTempSkillDoc, DamageName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Diastrophism_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, Area18);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Diastrophism_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_SPIRIT_ELEMENTAL:


			strcpy_s(szTempSkillDoc, IncreMagicDamage);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Spirit_Elemental_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Spirit_Elemental_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;

			case SKILL_DANCING_SWORD:
			PlusMinD = 0;
			PlusMaxD = 0;






			PlusMinD += (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[0] / 3);
			PlusMaxD += (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[1] / 3);
			PlusMinD += sinChar->Spirit / 8;
			PlusMaxD += sinChar->Spirit / 6;

			strcpy_s(szTempSkillDoc, FireDamage2);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d(+%d)-%d(+%d)\r", Dancing_Sword_FireDamage[pSkill->Point + i - 1][0], PlusMinD, Dancing_Sword_FireDamage[pSkill->Point + i - 1][1], PlusMaxD);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, IceDamage2);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d(+%d)-%d(+%d)\r", Dancing_Sword_IceDamage[pSkill->Point + i - 1][0], PlusMinD, Dancing_Sword_IceDamage[pSkill->Point + i - 1][1], PlusMaxD);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, AttackDelay3);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Dancing_Sword_AttackDelay[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Dancing_Sword_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_FORCE_ORB:
			if(pSkill->ElementIndex == 1000)
			{
				strcpy_s(szTempSkillDoc, DamageAddName);
				lstrcat(szSkillInfoBuff, szTempSkillDoc);
				wsprintf(szTempSkillDoc2, "%d%s\r", 15, "%");
				lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
				LineCount++;

				strcpy_s(szTempSkillDoc, CountinueTime);
				lstrcat(szSkillInfoBuff, szTempSkillDoc);
				wsprintf(szTempSkillDoc2, "%d%s\r", BillingMagicForceOrbUseTime[pSkill->Point + i - 1], SecName);
				lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
				LineCount++;
			}
			else
			{
				strcpy_s(szTempSkillDoc, sinAddDamage7);
				lstrcat(szSkillInfoBuff, szTempSkillDoc);
				wsprintf(szTempSkillDoc2, "%d\r", ForceOrbDamage[pSkill->Point + i - 1]);
				lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
				LineCount++;
				if(pSkill->Point >= 7 && pSkill->Point <= 10)
				{
					strcpy_s(szTempSkillDoc, DamageAddName);
					lstrcat(szSkillInfoBuff, szTempSkillDoc);
					wsprintf(szTempSkillDoc2, "%d%s\r", 10, "%");
					lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
					LineCount++;
				}
				else if(pSkill->Point == 11)
				{
					strcpy_s(szTempSkillDoc, DamageAddName);
					lstrcat(szSkillInfoBuff, szTempSkillDoc);
					wsprintf(szTempSkillDoc2, "%d%s\r", 15, "%");
					lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
					LineCount++;
				}
				else if(pSkill->Point == 12)
				{
					strcpy_s(szTempSkillDoc, DamageAddName);
					lstrcat(szSkillInfoBuff, szTempSkillDoc);
					wsprintf(szTempSkillDoc2, "%d%s\r", 20, "%");
					lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
					LineCount++;
				}
				strcpy_s(szTempSkillDoc, CountinueTime);
				lstrcat(szSkillInfoBuff, szTempSkillDoc);
				wsprintf(szTempSkillDoc2, "%d%s\r", ForceOrbUseTime[pSkill->Point + i - 1], SecName);
				lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
				LineCount++;
			}
			break;
			break;
			case CHANGE_JOB3_QUEST:
			strcpy_s(szTempSkillDoc, sinLimitTiem2);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", 70, sinMinute2);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;


			wsprintf(szTempSkillDoc, "%s: \r", szQuestMonsterName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "(%d/%d)\r", sinQuest_ChangeJob4.Monster[0], sinQuest_ChangeJob4.Monster[1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case CHANGE_ELEMENTARY_QUEST:
			if(chaQuest.sHaQuest100LV.CODE)
			{
				wsprintf(szTempSkillDoc, "%s: \r", chaQuest.szQuestMonsterName);
				lstrcat(szSkillInfoBuff, szTempSkillDoc);
				wsprintf(szTempSkillDoc2, "(%d/%d)\r", chaQuest.sHaQuest100LV.Monster[0], chaQuest.sHaQuest100LV.Monster[1]);
				lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
				LineCount++;
			}
			else
			{
				wsprintf(szTempSkillDoc, "%s: \r", chaQuest.szQuestMonsterName);
				lstrcat(szSkillInfoBuff, szTempSkillDoc);
				wsprintf(szTempSkillDoc2, "(%d/%d)\r", chaQuest.sHaQuestElementary[chaQuest.QuestKeyCode].Monster[0], chaQuest.sHaQuestElementary[chaQuest.QuestKeyCode].Monster[1]);
				lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
				LineCount++;
			}
			break;




			case SKILL_IMPULSION:
			strcpy_s(szTempSkillDoc, LinghtingAddDamage4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", Impulsion_LightingDamage[pSkill->Point + i - 1][0], Impulsion_LightingDamage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, Area19);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Impulsion_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, MaxBoltNum4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Impulsion_LightingNum[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			case SKILL_COMPULSION:
			strcpy_s(szTempSkillDoc, AddAbsorb4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Compulsion_AddAbsorb[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, IncreArea4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Compulsion_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Compulsion_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			case SKILL_MAGNETIC_SPHERE:
			strcpy_s(szTempSkillDoc, IncreAttack4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", Magnetic_Sphere_AddDamage[pSkill->Point + i - 1][0], Magnetic_Sphere_AddDamage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, Area18);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Magnetic_Sphere_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, AttackDelay3);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Magnetic_Sphere_AttackDelay[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Magnetic_Sphere_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			case SKILL_METAL_GOLEM:
			strcpy_s(szTempSkillDoc, sinAttackType);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			strcpy_s(szTempSkillDoc2, sinAttackType2[SummonSkillCodeIndex[0]]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", 360, SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, DamageName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", Metal_Golem_Damage[pSkill->Point + i - 1][0], Metal_Golem_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, WolverinRate4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Metal_Golem_Hit[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, WolverinDefense4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Metal_Golem_Defense[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, GolemLife4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d+(%d)\r", Metal_Golem_Life[pSkill->Point + i - 1], (sinChar->Strength * 2));
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;

			case SKILL_DETORYER:
			strcpy_s(szTempSkillDoc, AddPercentDamage4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Destoryer_DamagePercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, Add_CriticalName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Destoryer_AddCritical[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			case SKILL_BERSERKER:
			strcpy_s(szTempSkillDoc, PlusDamageName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Berserker_AddAttack[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, SubAbsorb4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Berserker_SubAbsorb[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Berserker_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			case SKILL_CYCLONE_STRIKE:
			strcpy_s(szTempSkillDoc, AddPercentDamage4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Cyclone_Strike_DamagePercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, AreaDamage4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", Cyclone_Strike_AreaDamage[pSkill->Point + i - 1][0], Cyclone_Strike_AreaDamage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, MaxAttackNum4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Cyclone_Strike_AttackNum[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, AttackAreaName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Cyclone_Strike_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			case SKILL_BOOST_HEALTH:
			strcpy_s(szTempSkillDoc, LifeUp4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Boost_Health_Life[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;

			case SKILL_ASSASSIN_EYE:
			strcpy_s(szTempSkillDoc, CriticalAddDamage4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Assassin_Eye_AddCritical[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, MonstervsSubCritical4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Assassin_Eye_M_SubCritical[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Assassin_Eye_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			case SKILL_CHARGING_STRIKE:
			strcpy_s(szTempSkillDoc, AddPercentDamage4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Charging_Strike_DamagePercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, ChargingAddPercentDamage4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Charging_Strike_CharingDamagePercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, ChargingTime4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			if((pSkill->Point + i) == 1)
			{
				wsprintf(szTempSkillDoc2, "%d%s\r", 0, "%");
			}
			else
				wsprintf(szTempSkillDoc2, "%d%s\r", Charging_Strike_Time[(pSkill->Point + i - 1) - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			case SKILL_VAGUE:
			strcpy_s(szTempSkillDoc, IncreEvasionPercent4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Vague_EvasionPercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Vague_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			case SKILL_SHADOW_MASTER:
			strcpy_s(szTempSkillDoc, IncreAttack4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Shadow_Master_DamagePercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, AddShadowNum4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Shadow_Master_ShadowNum[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;

			case SKILL_RECALL_WOLVERIN:

			strcpy_s(szTempSkillDoc, sinAttackType);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			strcpy_s(szTempSkillDoc2, sinAttackType2[SummonSkillCodeIndex[2]]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", 360, SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, DamageName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", Recall_Wolverin_Damage[pSkill->Point + i - 1][0], Recall_Wolverin_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, WolverinRate4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Recall_Wolverin_Hit[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, WolverinDefense4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d+(%d)\r", Recall_Wolverin_Defense[pSkill->Point + i - 1], (sinChar->Dexterity * 2));
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, WolverinLife4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Recall_Wolverin_Life[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			case SKILL_EVASION_MASTERY:
			strcpy_s(szTempSkillDoc, AddEvasion4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Evasion_Mastery_AddPercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;

			case SKILL_PHOENIX_SHOT:

			strcpy_s(szTempSkillDoc, AddPercentDamage4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Phoenix_Shot_DamagePercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, ChargingTime4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			sinTemp1 = (int)((Phoenix_Shot_Time[pSkill->Point + i - 1] + 0.001f) * 10);
			RightSpot = sinTemp1 % 10;
			LeftSpot = (sinTemp1 - RightSpot) / 10;

			wsprintf(szTempSkillDoc2, "%d.%d%s\r", LeftSpot, RightSpot, SecName);

			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			case SKILL_FORCE_OF_NATURE:
			strcpy_s(szTempSkillDoc, AddDamage4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Force_Of_Nature_AddDamage[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, IncreAttack_RateName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Force_Of_Nature_AddHit[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, FalconAddDamage4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Force_Of_Nature_FalconAddDamage[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Force_Of_Nature_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;




			case SKILL_DIVINE_PIERCING:
			strcpy_s(szTempSkillDoc, AddPercentDamage4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Divine_Piercing_DamagePercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, AttackNum3);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Divine_Piercing_AttackNum[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			case SKILL_GODLY_SHIELD:
			strcpy_s(szTempSkillDoc, IncreAttackAbsorb4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Godly_Shield_AbsorbPercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Godly_Shield_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;

			case SKILL_GOD_BLESS:
			strcpy_s(szTempSkillDoc, IncreAttack4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", God_Bless_AddDamage[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", God_Bless_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_SWORD_OF_JUSTICE:
			strcpy_s(szTempSkillDoc, AddPercentDamage4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Sword_Of_Justice_DamagePercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, AttackAreaName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Sword_Of_Justice_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;

			case SKILL_HALL_OF_VALHALLA:
			strcpy_s(szTempSkillDoc, IncreEvasionPercent4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Hall_Of_Valhalla_AddEvation[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Hall_Of_Valhalla_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_X_RAGE:
			strcpy_s(szTempSkillDoc, AddPercentDamage4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", X_Rage_DamagePercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, RectAngleArea4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", X_Rage_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			case SKILL_FROST_JAVELIN:
			strcpy_s(szTempSkillDoc, AddIceDamage4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", Frost_Javelin_IceAddDamage[pSkill->Point + i - 1][0], Frost_Javelin_IceAddDamage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, MonsterSubSpeed4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Frost_Javelin_SpeedSubPercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, IceTime4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Frost_Javelin_IceTime[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Frost_Javelin_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_VENGEANCE:
			strcpy_s(szTempSkillDoc, AddPercentDamage4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Vengeance_DamagePercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;


			strcpy_s(szTempSkillDoc, Add_CriticalName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Vengeance_AddCritical[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;


			strcpy_s(szTempSkillDoc, ShootingRangeName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Vengeance_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;

			case SKILL_GLACIAL_SPIKE:

			strcpy_s(szTempSkillDoc, DamageName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Glacial_Spike_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, AttackAreaName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Glacial_Spike_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;
			break;
			case SKILL_REGENERATION_FIELD:

			strcpy_s(szTempSkillDoc, AddLifeRegen4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			TempLife = (int)(Regeneration_Field_LifeRegen[pSkill->Point + i - 1] * 10 + 0.001f);
			RightSpot = TempLife % 10;
			LeftSpot = (TempLife - RightSpot) / 10;
			wsprintf(szTempSkillDoc2, "%d.%d\r", LeftSpot, RightSpot);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, AddManaRegen4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			TempMana = (int)(Regeneration_Field_ManaRegen[pSkill->Point + i - 1] * 10 + 0.001f);
			RightSpot = TempMana % 10;
			LeftSpot = (TempMana - RightSpot) / 10;
			wsprintf(szTempSkillDoc2, "%d.%d\r", LeftSpot, RightSpot);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Regeneration_Field_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, MagicArea4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Regeneration_Field_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_CHAIN_LIGHTNING:

			strcpy_s(szTempSkillDoc, DamageName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Chain_Lightning_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, ChainNum4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Chain_Lightning_Num[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, ChainRange4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Chain_Lightning_Range[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_SUMMON_MUSPELL:

			strcpy_s(szTempSkillDoc, DamageName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", Summon_Muspell_Damage[pSkill->Point + i - 1][0], Summon_Muspell_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, AttackDelay3);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Summon_Muspell_Attack_Delay[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, UndeadDamageAbsorb4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Summon_Muspell_UndeadAbsorbPercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, UserBlockPercent4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Summon_Muspell_BlockPercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Summon_Muspell_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;

			case SKILL_FIRE_ELEMENTAL:

			strcpy_s(szTempSkillDoc, sinAttackType);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			strcpy_s(szTempSkillDoc2, sinAttackType2[SummonSkillCodeIndex[1]]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;


			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", 360, SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, DamageName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d-%d\r", Fire_Elemental_Damage[pSkill->Point + i - 1][0], Fire_Elemental_Damage[pSkill->Point + i - 1][1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, WolverinRate4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Fire_Elemental_Hit[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, WolverinLife4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", (Fire_Elemental_Life[pSkill->Point + i - 1]));
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_FLAME_WAVE:

			strcpy_s(szTempSkillDoc, FireDamage4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Flame_Wave_FireDamage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, AttackAreaName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Flame_Wave_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_DISTORTION:
			strcpy_s(szTempSkillDoc, DecreSpeed4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Distortion_SpeedSubPercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, DecreAttack4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Distortion_DamageSubPercent[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, MagicArea4);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Distortion_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, CountinueTime);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Distortion_Time[pSkill->Point + i - 1], SecName);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
			case SKILL_M_METEO:
			
			strcpy_s(szTempSkillDoc, DamageName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d%s\r", Meteo_Damage[pSkill->Point + i - 1], "%");
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			strcpy_s(szTempSkillDoc, AttackAreaName);
			lstrcat(szSkillInfoBuff, szTempSkillDoc);
			wsprintf(szTempSkillDoc2, "%d\r", Meteo_Area[pSkill->Point + i - 1]);
			lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
			LineCount++;

			break;
		}

		if(!Icon)
		{
			if(pSkill->Skill_Info.UseMana)
			{
				strcpy_s(szTempSkillDoc, UseManaName);
				lstrcat(szSkillInfoBuff, szTempSkillDoc);





				if(chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
				{
					wsprintf(szTempSkillDoc2, "%d(-%d)\r", pSkill->Skill_Info.UseMana[pSkill->Point + i - 1],
						(pSkill->Skill_Info.UseMana[pSkill->Point + i - 1] * chaPremiumitem.m_ManaReducePotionValue / 100) +
							 (pSkill->Skill_Info.UseMana[pSkill->Point + i - 1] * 20 / 100));
				}


				else if(chaPremiumitem.m_ManaReducePotiontime > 0)
				{
					wsprintf(szTempSkillDoc2, "%d(-%d)\r", pSkill->Skill_Info.UseMana[pSkill->Point + i - 1], (pSkill->Skill_Info.UseMana[pSkill->Point + i - 1] * chaPremiumitem.m_ManaReducePotionValue / 100));
				}


				else if(chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
				{
					wsprintf(szTempSkillDoc2, "%d(-%d)\r", pSkill->Skill_Info.UseMana[pSkill->Point + i - 1], (pSkill->Skill_Info.UseMana[pSkill->Point + i - 1] * 20 / 100));
				}


				else
				{
					wsprintf(szTempSkillDoc2, "%d\r", pSkill->Skill_Info.UseMana[pSkill->Point + i - 1]);
				}


				lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
				LineCount++;
			}

			if(i == 0)
			{
				if(pSkill->Skill_Info.UseStamina[0])
				{
					strcpy_s(szTempSkillDoc, UseStaminaName);
					lstrcat(szSkillInfoBuff, szTempSkillDoc);
					if(chaPremiumitem.m_StaminaReducePotiontime > 0)
					{
						wsprintf(szTempSkillDoc2, "%d(-%d)\r", pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1)), ((pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1))) * chaPremiumitem.m_StaminaReducePotionValue / 100));
					}
					else
					{
						wsprintf(szTempSkillDoc2, "%d\r", pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1)));
					}
					lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
					LineCount++;
					lstrcat(szSkillInfoBuff, "\r");
					strcpy_s(szTempSkillDoc2, "\r");
					lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
					LineCount++;
				}
			}
			if(i == 1)
			{
				if(pSkill->Skill_Info.UseStamina[0])
				{
					strcpy_s(szTempSkillDoc, UseStaminaName);
					lstrcat(szSkillInfoBuff, szTempSkillDoc);
					if(chaPremiumitem.m_StaminaReducePotiontime > 0)
					{
						wsprintf(szTempSkillDoc2, "%d(-%d)\r", pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point)), ((pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point))) * chaPremiumitem.m_StaminaReducePotionValue / 100));
					}
					else
					{
						wsprintf(szTempSkillDoc2, "%d\r", pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point)));
					}
					lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
					LineCount++;
				}

			}
		}
	}

	if(SkillMasterFlag == 1 && pSkill->Point < 10)
	{
		strcpy_s(szTempSkillDoc, MasterSkillMoneyName);
		lstrcat(szSkillInfoBuff, szTempSkillDoc);

	#ifdef HASIEGE_MODE

		wsprintf(szTempSkillDoc2, "%d\r", cShop.haShopItemPrice(sinMasterSkill_Money[pSkill->Skill_Info.SkillNum] + (sinMasterSkill_PlusMoney[pSkill->Skill_Info.SkillNum] * (pSkill->Point))));
	#else
		wsprintf(szTempSkillDoc2, "%d\r", sinMasterSkill_Money[pSkill->Skill_Info.SkillNum] + (sinMasterSkill_PlusMoney[pSkill->Skill_Info.SkillNum] * (pSkill->Point)));
	#endif

		lstrcat(szSkillInfoBuff2, szTempSkillDoc2);
		LineCount++;
	}

	if(!ShowSkillUpInfo)
	{
		strcpy_s(szSkillMasterInfoBuff, szSkillInfoBuff);
		strcpy_s(szSkillMasterInfoBuff2, szSkillInfoBuff2);
	}
	SkillInfoLineCnt = LineCount;
	GetInfoBoxSize(pSkillBox, LineCount, Icon);

	return TRUE;

}

int cSKILL::GetInfoBoxSize(sSKILLBOX *pSkillBox, int Col, int Icon)
{

	int ty, tx;

	SkillBoxSize.x = 14;
	SkillBoxSize.y = Col + 1;

	SkillInfoBoxPosi.x = (pSkillBox->BoxRect.left - 112) + 20;
	SkillInfoBoxPosi.y = pSkillBox->BoxRect.top - (SkillBoxSize.y * 16);

	if(Icon)
	{
		SkillInfoBoxPosi.x = pSkillBox->BoxRect.left;
		SkillInfoBoxPosi.y = pSkillBox->BoxRect.top;

	}

	ty = SkillInfoBoxPosi.y + (SkillBoxSize.y * 16);
	tx = SkillInfoBoxPosi.x + (SkillBoxSize.x * 16);


	if(SkillInfoBoxPosi.y < 0)
		SkillInfoBoxPosi.y = 0;
	if(SkillInfoBoxPosi.x < 0)
		SkillInfoBoxPosi.x = 0;

	if(ty > 600)
		SkillInfoBoxPosi.y -= (ty - 600);
	if(tx > 800)
		SkillInfoBoxPosi.x -= (tx - 800);

	return TRUE;
}



int cSKILL::GetSkillMastery(sSKILL *pSkill, sSKILLBOX *pSkillBox)
{
	int SkillMasteryTemp = 0;
	SkillMasteryTemp = ((int)pSkill->UseSkillMastery / 100);
	wsprintf(szUseSkillMastery, "%d", SkillMasteryTemp);

	UseSkillMasteryPosi.x = pSkillBox->GageRect.left - (34 / 2);
	UseSkillMasteryPosi.y = pSkillBox->GageRect.top - 29;

	return TRUE;
}


int cSKILL::CheckUseSkillState(sSKILL *pSkill)
{
	if(pSkill->Skill_Info.UseMana)
	{


		if(chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1 && chaPremiumitem.m_StaminaReducePotiontime > 0)
		{
			if(sinGetMana() >= pSkill->Skill_Info.UseMana[pSkill->Point - 1] - ((pSkill->Skill_Info.UseMana[pSkill->Point - 1] *
																				 chaPremiumitem.m_ManaReducePotionValue / 100) + (pSkill->Skill_Info.UseMana[pSkill->Point - 1] * 20 / 100)) &&
			   sinGetStamina() >= (pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1))) - ((pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1))) * chaPremiumitem.m_StaminaReducePotionValue / 100))
			{
				pSkill->UseSkillFlag = 1;
			}

			else
				pSkill->UseSkillFlag = 0;
		}


		else if(chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_StaminaReducePotiontime > 0)
		{
			if(sinGetMana() >= pSkill->Skill_Info.UseMana[pSkill->Point - 1] - (pSkill->Skill_Info.UseMana[pSkill->Point - 1] * chaPremiumitem.m_ManaReducePotionValue / 100) &&
			   sinGetStamina() >= (pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1))) - ((pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1))) * chaPremiumitem.m_StaminaReducePotionValue / 100))
			{
				pSkill->UseSkillFlag = 1;
			}
			else
				pSkill->UseSkillFlag = 0;
		}


		else if(chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1 && chaPremiumitem.m_StaminaReducePotiontime > 0)
		{
			if(sinGetMana() >= pSkill->Skill_Info.UseMana[pSkill->Point - 1] - (pSkill->Skill_Info.UseMana[pSkill->Point - 1] * 20 / 100) &&
			   sinGetStamina() >= (pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1))) - ((pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1))) * chaPremiumitem.m_StaminaReducePotionValue / 100))
			{
				pSkill->UseSkillFlag = 1;
			}
			else
				pSkill->UseSkillFlag = 0;
		}


		else if(chaPremiumitem.m_ManaReducePotiontime > 0)
		{
			if(sinGetMana() >= pSkill->Skill_Info.UseMana[pSkill->Point - 1] - (pSkill->Skill_Info.UseMana[pSkill->Point - 1] * chaPremiumitem.m_ManaReducePotionValue / 100) &&
			   sinGetStamina() >= pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1)))
			{
				pSkill->UseSkillFlag = 1;
			}
			else
				pSkill->UseSkillFlag = 0;
		}


		else if(chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
		{
			if(sinGetMana() >= pSkill->Skill_Info.UseMana[pSkill->Point - 1] - (pSkill->Skill_Info.UseMana[pSkill->Point - 1] * 20 / 100) &&
			   sinGetStamina() >= pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1)))
			{
				pSkill->UseSkillFlag = 1;
			}
			else
				pSkill->UseSkillFlag = 0;
		}


		else if(chaPremiumitem.m_StaminaReducePotiontime > 0)
		{
			if(sinGetMana() >= pSkill->Skill_Info.UseMana[pSkill->Point - 1] &&
			   sinGetStamina() >= (pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1))) - ((pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1))) * chaPremiumitem.m_StaminaReducePotionValue / 100))
			{
				pSkill->UseSkillFlag = 1;

			}
			else
				pSkill->UseSkillFlag = 0;
		}


		else
		{
			if(sinGetMana() >= pSkill->Skill_Info.UseMana[pSkill->Point - 1] &&
			   sinGetStamina() >= pSkill->Skill_Info.UseStamina[0] + (pSkill->Skill_Info.UseStamina[1] * (pSkill->Point - 1)))
			{
				pSkill->UseSkillFlag = 1;

			}
			else
				pSkill->UseSkillFlag = 0;
		}
	}
	return TRUE;
}


int SkillDataCheckDelayTime = 0;
int SkillDataCheckFlag2 = 0;

int cSKILL::CheckSkillData()
{
	int i;
	int k;

	SkillDataCheckDelayTime++;
	if(SkillDataCheckDelayTime < 70 * 10)return FALSE;
	SkillDataCheckDelayTime = 0;


	unsigned int SkillDataCheckSum = 0;


	unsigned int SkillInfoDataCheckSum = 0;


	for(i = 0; i < 10; i++)
	{
		k = i + 1;
		SkillDataCheckSum += k*E_Shield_BlockRate[i];
		SkillDataCheckSum += k*E_Shield_UseTime[i];
		SkillDataCheckSum += k*E_Shield_UseMana[i];
		SkillDataCheckSum += k*Mechanic_Bomb_Damage[i][0];
		SkillDataCheckSum += k*Mechanic_Bomb_Damage[i][1];
		SkillDataCheckSum += k*Mechanic_Bomb_Attack_Range[i];
		SkillDataCheckSum += k*Mechanic_Bomb_UseMana[i];
		SkillDataCheckSum += k*P_Absorb[i][0];
		SkillDataCheckSum += k*P_Absorb[i][1];
		SkillDataCheckSum += k*P_Absorb_UseTime[i];
		SkillDataCheckSum += k*P_Absor_bUseMana[i];
		SkillDataCheckSum += k*PlusPoison[i];
		SkillDataCheckSum += (int)(k*Melee_Mastery_DamagePercent[i]);
		SkillDataCheckSum += k*PlusFire[i];
		SkillDataCheckSum += k*Raving_Damage[i];
		SkillDataCheckSum += k*Ravind_Speed[i];
		SkillDataCheckSum += (int)(k*Raving_UseLife[i]);
		SkillDataCheckSum += k*Raving_UseMana[i];
		SkillDataCheckSum += k*Impact_Attack_Rating[i];
		SkillDataCheckSum += k*Impact_Damage[i];
		SkillDataCheckSum += k*Impact_UseMana[i];
		SkillDataCheckSum += k*Pike_Wind_Throw_Height[i];
		SkillDataCheckSum += k*Pike_Wind_Damage[i][0];
		SkillDataCheckSum += k*Pike_Wind_Damage[i][1];
		SkillDataCheckSum += k*Pike_Wind_Push_Lenght[i];
		SkillDataCheckSum += k*Pike_Wind_UseMana[i];
		SkillDataCheckSum += k*PlusIce[i];
		SkillDataCheckSum += k*Critical_Hit_Critical[i];
		SkillDataCheckSum += k*Critical_Hit_UseMana[i];
		SkillDataCheckSum += k*Jumping_Crash_UseMana[i];
		SkillDataCheckSum += k*Jumping_Crash_Attack_Rating[i];
		SkillDataCheckSum += k*Jumping_Crash_Damage[i];
		SkillDataCheckSum += k*Scout_Hawk_Attack_Rate[i];
		SkillDataCheckSum += k*Scout_Hawk_UseTime[i];
		SkillDataCheckSum += k*Scout_Hawk_UseMana[i];
		SkillDataCheckSum += k*S_Mastery_DamagePercent[i];
		SkillDataCheckSum += k*Wind_Arrow_Speed[i];
		SkillDataCheckSum += k*Wind_Arrow_Damage[i];
		SkillDataCheckSum += k*Wind_Arrow_UseMana[i];
		SkillDataCheckSum += k*Perfect_Aim_Attack_Rate[i];
		SkillDataCheckSum += k*Perfect_Aim_Damage[i];
		SkillDataCheckSum += k*Perfect_Aim_Damage_LV[i];
		SkillDataCheckSum += k*Perfect_Aim_UseMana[i];
		SkillDataCheckSum += k*G_Smash_Attack_Rate[i];
		SkillDataCheckSum += k*G_Smash_Attack_Rage[i];
		SkillDataCheckSum += k*G_Smash_UseMana[i];
		SkillDataCheckSum += k*Maximize_Damage[i];
		SkillDataCheckSum += k*Maximize_Time[i];
		SkillDataCheckSum += k*Maximize_UseMana[i];
		SkillDataCheckSum += k*Automation_Damage[i];
		SkillDataCheckSum += k*Automation_Speed[i];
		SkillDataCheckSum += k*Automation_Time[i];
		SkillDataCheckSum += k*Automation_UseMana[i];
		SkillDataCheckSum += k*Spark_Damage[i][0];
		SkillDataCheckSum += k*Spark_Damage[i][1];
		SkillDataCheckSum += k*Spark_Area[i];
		SkillDataCheckSum += k*Spark_UseMana[i];
		SkillDataCheckSum += k*T_Impact_Damage[i];
		SkillDataCheckSum += k*T_Impact_Hit[i];
		SkillDataCheckSum += k*T_Impact_UseMana[i];
		SkillDataCheckSum += k*B_Swing_Damage[i];
		SkillDataCheckSum += k*B_Swing_Critical[i];
		SkillDataCheckSum += k*B_Swing_UseMana[i];
		SkillDataCheckSum += k*Roar_Range[i];
		SkillDataCheckSum += k*Roar_Time[i];
		SkillDataCheckSum += k*Roar_UseMana[i];
		SkillDataCheckSum += k*R_Zecram_Damage[i];
		SkillDataCheckSum += k*R_Zecram_UseMana[i];
		SkillDataCheckSum += k*G_Pike_Damage[i][0];
		SkillDataCheckSum += k*G_Pike_Damage[i][1];
		SkillDataCheckSum += k*G_Pike_Range[i];
		SkillDataCheckSum += k*G_Pike_UseMana[i];
		SkillDataCheckSum += k*G_Pike_Time[i];
		SkillDataCheckSum += k*Tornado_Damage[i];
		SkillDataCheckSum += k*Tornado_Stun[i];
		SkillDataCheckSum += k*Tornado_Range[i];
		SkillDataCheckSum += k*Tornado_UseMana[i];
		SkillDataCheckSum += k*W_D_Mastery_Block[i];
		SkillDataCheckSum += k*Expansion_Size[i];
		SkillDataCheckSum += k*Expansion_UseMana[i];
		SkillDataCheckSum += k*D_Eye_Attack_Rate[i];
		SkillDataCheckSum += k*Falcon_Damage[i][0];
		SkillDataCheckSum += k*Falcon_Damage[i][1];
		SkillDataCheckSum += k*Falcon_Time[i];
		SkillDataCheckSum += k*Falcon_UseMana[i];
		SkillDataCheckSum += k*A_Rage_ArrowNum[i];
		SkillDataCheckSum += k*A_Rage_Damage[i];
		SkillDataCheckSum += k*A_Rage_Area[i];
		SkillDataCheckSum += k*A_Rage_UseMana[i];
		SkillDataCheckSum += k*Avalanche_Speed[i];
		SkillDataCheckSum += k*Avalanche_Damage[i];
		SkillDataCheckSum += k*Avalanche_ArrowNum[i];
		SkillDataCheckSum += k*Avalanche_UseMana[i];
		SkillDataCheckSum += k*Expansion_Damage[i];
	}
	for(i = 0; i < 10; i++)
	{
		k = i + 1;
		SkillDataCheckSum += k*Sword_Blast_UseMana[i];
		SkillDataCheckSum += k*Sword_Blast_Damage[i][0];
		SkillDataCheckSum += k*Sword_Blast_Damage[i][1];
		SkillDataCheckSum += k*Sword_Blast_ShootingRange[i];
		SkillDataCheckSum += k*HolyBody_UseMana[i];
		SkillDataCheckSum += k*HolyBody_Absorb[i];
		SkillDataCheckSum += k*HolyBody_Time[i];
		SkillDataCheckSum += k*P_Traning_Stamina[i];
		SkillDataCheckSum += k*D_Crash_UseMana[i];
		SkillDataCheckSum += k*D_Crash_Damage[i];
		SkillDataCheckSum += k*D_Crash_Critical[i];
		SkillDataCheckSum += k*S_Strike_UseMana[i];
		SkillDataCheckSum += k*S_Strike_Damage[i][0];
		SkillDataCheckSum += k*S_Strike_Damage[i][1];
		SkillDataCheckSum += k*Farina_UseMana[i];
		SkillDataCheckSum += k*Farina_Speed[i];
		SkillDataCheckSum += k*Farina_AttackRate[i];
		SkillDataCheckSum += k*T_Mastery_Damage[i];
		SkillDataCheckSum += k*V_Spear_UseMana[i];
		SkillDataCheckSum += k*V_Spear_Damage[i][0];
		SkillDataCheckSum += k*V_Spear_Damage[i][1];
		SkillDataCheckSum += k*Healing_UseMana[i];
		SkillDataCheckSum += k*Healing_Heal[i][0];
		SkillDataCheckSum += k*Healing_Heal[i][1];
		SkillDataCheckSum += k*HolyBolt_UseMana[i];
		SkillDataCheckSum += k*HolyBolt_Damage[i];
		//SkillDataCheckSum += k*HolyBolt_Damage[i][1];
		SkillDataCheckSum += k*M_Spark_UseMana[i];
		SkillDataCheckSum += k*M_Spark_Damage[i];
		//SkillDataCheckSum += k*M_Spark_Damage[i][1];
		SkillDataCheckSum += k*M_Spark_Num[i];
		SkillDataCheckSum += k*HolyMind_UseMana[i];
		SkillDataCheckSum += k*HolyMind_DecDamage[i];
		SkillDataCheckSum += k*HolyMind_Time[i];
		SkillDataCheckSum += k*Agony_UseMana[i];
		SkillDataCheckSum += k*Agony_ConvLife[i];
		SkillDataCheckSum += k*FireBolt_UseMana[i];
		SkillDataCheckSum += k*FireBolt_Damage[i];
		//SkillDataCheckSum += k*FireBolt_Damage[i][1];
		SkillDataCheckSum += k*Zenith_UseMana[i];
		SkillDataCheckSum += k*Zenith_Element[i];
		SkillDataCheckSum += k*Zenith_Time[i];
		SkillDataCheckSum += k*FireBall_UseMana[i];
		SkillDataCheckSum += k*FireBall_Damage[i];
		//SkillDataCheckSum += k*FireBall_Damage[i][1];
		SkillDataCheckSum += k*FireBall_Range[i];
		SkillDataCheckSum += k*Holy_Valor_Damage[i];
		SkillDataCheckSum += k*Holy_Valor_Time[i];
		SkillDataCheckSum += k*Holy_Valor_Mana[i];
		SkillDataCheckSum += k*Brandish_Range[i];
		SkillDataCheckSum += k*Brandish_Damage[i];
		SkillDataCheckSum += k*Brandish_Mana[i];
		SkillDataCheckSum += k*Piercing_Damage[i];
		SkillDataCheckSum += k*Piercing_Attack_Rating[i];
		SkillDataCheckSum += k*Piercing_Mana[i];
		SkillDataCheckSum += k*Drastic_Spirit_Defense[i];
		SkillDataCheckSum += k*Drastic_Spirit_Time[i];
		SkillDataCheckSum += k*Drastic_Spirit_Mana[i];
		SkillDataCheckSum += k*Windy_Attack_Rating[i];
		SkillDataCheckSum += k*Windy_Time[i];
		SkillDataCheckSum += k*Windy_Mana[i];
		SkillDataCheckSum += k*Twist_Javelin_Damage[i];
		SkillDataCheckSum += k*Twist_Javelin_Attack_Rating[i];
		SkillDataCheckSum += k*Twist_Javelin_Mana[i];
		SkillDataCheckSum += k*Soul_Sucker_Absorb[i];
		SkillDataCheckSum += k*Soul_Sucker_Mana[i];
		SkillDataCheckSum += k*Fire_Javelin_Damage[i][0];
		SkillDataCheckSum += k*Fire_Javelin_Damage[i][1];
		SkillDataCheckSum += k*Fire_Javelin_Mana[i];
		SkillDataCheckSum += k*(int)Meditation_Regen[i];
		SkillDataCheckSum += k*Divine_Lightning_Damage[i];
		//SkillDataCheckSum += k*Divine_Lightning_Damage[i][1];
		SkillDataCheckSum += k*Divine_Lightning_Num[i];
		SkillDataCheckSum += k*Divine_Lightning_Mana[i];
		SkillDataCheckSum += k*Holy_Reflection_Return_Damage[i];
		SkillDataCheckSum += k*Holy_Reflection_Time[i];
		SkillDataCheckSum += k*Holy_Reflection_Mana[i];
		SkillDataCheckSum += k*Grand_Healing[i][0];
		SkillDataCheckSum += k*Grand_Healing[i][1];
		SkillDataCheckSum += k*Grand_Healing_Range[i];
		SkillDataCheckSum += k*Grand_Healing_Mana[i];
		SkillDataCheckSum += k*Mental_Mastery_Mana[i];
		SkillDataCheckSum += k*Watornado_Damage[i];
		//SkillDataCheckSum += k*Watornado_Damage[i][1];
		SkillDataCheckSum += k*Watornado_Area[i];
		SkillDataCheckSum += k*Watornado_Range[i];
		SkillDataCheckSum += k*Watornado_Mana[i];
		SkillDataCheckSum += k*Enchant_Weapon_Damage_Ice[i][0];
		SkillDataCheckSum += k*Enchant_Weapon_Damage_Ice[i][1];
		SkillDataCheckSum += k*Enchant_Weapon_Damage_Fire[i][0];
		SkillDataCheckSum += k*Enchant_Weapon_Damage_Fire[i][1];
		SkillDataCheckSum += k*Enchant_Weapon_Damage_Lightning[i][0];
		SkillDataCheckSum += k*Enchant_Weapon_Damage_Lightning[i][1];
		SkillDataCheckSum += k*Enchant_Weapon_Time[i];
		SkillDataCheckSum += k*Enchant_Weapon_Mana[i];
		SkillDataCheckSum += k*Dead_Ray_Damage[i];
		//SkillDataCheckSum += k*Dead_Ray_Damage[i][1];
		SkillDataCheckSum += k*Dead_Ray_Range[i];
		SkillDataCheckSum += k*Dead_Ray_Mana[i];

	}

	for(i = 0; i < 10; i++)
	{
		k = i + 1;

		SkillDataCheckSum += k*Metal_Armor_Defense[i];
		SkillDataCheckSum += k*Metal_Armor_Time[i];
		SkillDataCheckSum += k*Metal_Armor_UseMana[i];


		SkillDataCheckSum += k*Grand_Smash_AttackRate[i];
		SkillDataCheckSum += k*Grand_Smash_Damage[i];
		SkillDataCheckSum += k*Grand_Smash_UseMana[i];


		SkillDataCheckSum += k*M_Weapon_Mastey[i];


		SkillDataCheckSum += k*Spark_Shield_Damage[i];
		SkillDataCheckSum += k*Spark_Shield_Defense[i];
		SkillDataCheckSum += k*Spark_Shield_Time[i];
		SkillDataCheckSum += k*Spark_Shield_UseMana[i];


		SkillDataCheckSum += k*Concentration_AttackRate[i];
		SkillDataCheckSum += k*Concentration_Time[i];
		SkillDataCheckSum += k*Concentration_UseMana[i];


		SkillDataCheckSum += k*A_Crash_Damage[i];
		SkillDataCheckSum += k*A_Crash_AttackRate[i];
		SkillDataCheckSum += k*A_Crash_UseMana[i];


		SkillDataCheckSum += k*Swift_Axe_Speed[i];
		SkillDataCheckSum += k*Swift_Axe_Time[i];
		SkillDataCheckSum += k*Swift_Axe_UseMana[i];


		SkillDataCheckSum += k*B_Crash_Damage[i];
		SkillDataCheckSum += k*B_Crash_DemonDamage[i];
		SkillDataCheckSum += k*B_Crash_UseMana[i];

		SkillDataCheckSum += k*VenomSpear_Damage[i][0];
		SkillDataCheckSum += k*VenomSpear_Damage[i][1];
		SkillDataCheckSum += k*VenomSpear_Num[i];
		SkillDataCheckSum += k*VenomSpear_Time[i];
		SkillDataCheckSum += k*VenomSpear_Range[i];
		SkillDataCheckSum += k*VenomSpear_UseMana[i];


		SkillDataCheckSum += k*(int)Vanish_Speed[i];
		SkillDataCheckSum += k*Vanish_Damage[i];
		SkillDataCheckSum += k*Vanish_Range[i];
		SkillDataCheckSum += k*Vanish_Time[i];
		SkillDataCheckSum += k*Vanish_UseMana[i];


		SkillDataCheckSum += k*Critical_Mastery_Critical[i];


		SkillDataCheckSum += k*Chain_Lance_Damage[i];
		SkillDataCheckSum += k*Chain_Lance_UseMana[i];

		SkillDataCheckSum += k*Elemental_Shot_Ice[i][0];
		SkillDataCheckSum += k*Elemental_Shot_Ice[i][1];
		SkillDataCheckSum += k*Elemental_Shot_Fire[i][0];
		SkillDataCheckSum += k*Elemental_Shot_Fire[i][1];
		SkillDataCheckSum += k*Elemental_Shot_Lightning[i][0];
		SkillDataCheckSum += k*Elemental_Shot_Lightning[i][1];
		SkillDataCheckSum += k*Elemental_Shot_UseMana[i];


		SkillDataCheckSum += k*Golden_Falcon_Damage[i];
		SkillDataCheckSum += k*(int)Golden_Falcon_LifeRegen[i];
		SkillDataCheckSum += k*Golden_Falcon_Time[i];
		SkillDataCheckSum += k*Golden_Falcon_UseMana[i];


		SkillDataCheckSum += k*BombShot_Damage[i];
		SkillDataCheckSum += k*BombShot_DemonDamage[i];
		SkillDataCheckSum += k*BombShot_AddDamage[i][0];
		SkillDataCheckSum += k*BombShot_AddDamage[i][1];
		SkillDataCheckSum += k*BombShot_Area[i];
		SkillDataCheckSum += k*BombShot_UseMana[i];


		SkillDataCheckSum += k*Perforation_Damage[i];
		SkillDataCheckSum += k*Perforation_Critical[i];
		SkillDataCheckSum += k*Perforation_UseMana[i];
		SkillDataCheckSum += k*Perforation_Attack_Range[i];
	}

	for(i = 0; i < 10; i++)
	{
		k = i + 1;

		SkillDataCheckSum += k*Sword_Mastery_DamagePercent[i];


		SkillDataCheckSum += k*D_Inhalation_Life[i];
		SkillDataCheckSum += k*D_Inhalation_Block[i];
		SkillDataCheckSum += k*D_Inhalation_Time[i];
		SkillDataCheckSum += k*D_Inhalation_UseMana[i];


		SkillDataCheckSum += k*H_Incantation_Success[i];
		SkillDataCheckSum += k*H_Incantation_AddLife[i];
		SkillDataCheckSum += k*H_Incantation_Time[i];
		SkillDataCheckSum += k*H_Incantation_UseMana[i];


		SkillDataCheckSum += k*Grand_Cross_Damage[i];
		SkillDataCheckSum += k*Grand_Cross_AttackRate[i];
		SkillDataCheckSum += k*Grand_Cross_UndeadDamage[i];
		SkillDataCheckSum += k*Grand_Cross_UseMana[i];

		SkillDataCheckSum += k*Split_Javelin_AttackNum[i];
		SkillDataCheckSum += k*Split_Javelin_Damage[i];
		SkillDataCheckSum += k*Split_Javelin_AttackRate[i];
		SkillDataCheckSum += k*Split_Javelin_UseMana[i];


		SkillDataCheckSum += k*T_Of_Valhalla_Damage[i];
		SkillDataCheckSum += k*T_Of_Valhalla_Time[i];
		SkillDataCheckSum += k*T_Of_Valhalla_UseMana[i];


		SkillDataCheckSum += k*Lightning_Javelin_Damage[i][0];
		SkillDataCheckSum += k*Lightning_Javelin_Damage[i][1];
		SkillDataCheckSum += k*Lightning_Javelin_UseMana[i];


		SkillDataCheckSum += k*Storm_Javelin_Damage[i];
		SkillDataCheckSum += k*Storm_Javelin_UseMana[i];

		SkillDataCheckSum += k*Vigor_Ball_Damage[i];
		//SkillDataCheckSum += k*Vigor_Ball_Damage[i][1];
		SkillDataCheckSum += k*Vigor_Ball_UseMana[i];


		SkillDataCheckSum += k*Resurrection_Percent[i];
		SkillDataCheckSum += k*Resurrection_Exp[i];
		SkillDataCheckSum += k*Resurrection_UseMana[i];


		SkillDataCheckSum += k*Extinction_Percent[i];
		SkillDataCheckSum += k*Extinction_Amount[i];
		SkillDataCheckSum += k*Extinction_UseMana[i];


		SkillDataCheckSum += k*Virtual_Life_Percent[i];
		SkillDataCheckSum += k*Virtual_Life_Time[i];
		SkillDataCheckSum += k*Virtual_Life_UseMana[i];

		SkillDataCheckSum += k*Energy_Shield_DecDamage[i];
		SkillDataCheckSum += k*Energy_Shield_Time[i];
		SkillDataCheckSum += k*Energy_Shield_UseMana[i];


		SkillDataCheckSum += k*Diastrophism_Damage[i];
		//SkillDataCheckSum += k*Diastrophism_Damage[i][1];
		SkillDataCheckSum += k*Diastrophism_Area[i];
		SkillDataCheckSum += k*Diastrophism_UseMana[i];


		SkillDataCheckSum += k*(int)Spirit_Elemental_RegenMana[i];
		SkillDataCheckSum += k*Spirit_Elemental_Damage[i];
		SkillDataCheckSum += k*Spirit_Elemental_Time[i];
		SkillDataCheckSum += k*Spirit_Elemental_UseMana[i];


		SkillDataCheckSum += k*Dancing_Sword_IceDamage[i][0];
		SkillDataCheckSum += k*Dancing_Sword_IceDamage[i][1];
		SkillDataCheckSum += k*Dancing_Sword_FireDamage[i][0];
		SkillDataCheckSum += k*Dancing_Sword_FireDamage[i][1];
		SkillDataCheckSum += k*Dancing_Sword_AttackDelay[i];
		SkillDataCheckSum += k*Dancing_Sword_Time[i];
		SkillDataCheckSum += k*Dancing_Sword_UseMana[i];


	}




	for(i = 0; i < 10; i++)
	{
		k = i + 1;

		SkillDataCheckSum += k*Impulsion_LightingDamage[i][0];
		SkillDataCheckSum += k*Impulsion_LightingDamage[i][1];
		SkillDataCheckSum += k*Impulsion_Range[i];
		SkillDataCheckSum += k*Impulsion_LightingNum[i];
		SkillDataCheckSum += k*Impulsion_UseMana[i];

		SkillDataCheckSum += k*Compulsion_AddAbsorb[i];
		SkillDataCheckSum += k*Compulsion_Area[i];
		SkillDataCheckSum += k*Compulsion_Time[i];
		SkillDataCheckSum += k*Compulsion_UseMana[i];

		SkillDataCheckSum += k*Magnetic_Sphere_AddDamage[i][0];
		SkillDataCheckSum += k*Magnetic_Sphere_AddDamage[i][1];
		SkillDataCheckSum += k*Magnetic_Sphere_Area[i];
		SkillDataCheckSum += k*Magnetic_Sphere_AttackDelay[i];
		SkillDataCheckSum += k*Magnetic_Sphere_Time[i];
		SkillDataCheckSum += k*Magnetic_Sphere_UseMana[i];

		SkillDataCheckSum += k*Metal_Golem_Damage[i][0];
		SkillDataCheckSum += k*Metal_Golem_Damage[i][1];
		SkillDataCheckSum += k*Metal_Golem_Hit[i];
		SkillDataCheckSum += k*Metal_Golem_Defense[i];
		SkillDataCheckSum += k*Metal_Golem_Life[i];
		SkillDataCheckSum += k*Metal_Golem_UseMana[i];

		SkillDataCheckSum += k*Destoryer_DamagePercent[i];
		SkillDataCheckSum += k*Destoryer_AddCritical[i];
		SkillDataCheckSum += k*Destoryer_UseMana[i];

		SkillDataCheckSum += k*Berserker_AddAttack[i];
		SkillDataCheckSum += k*Berserker_SubAbsorb[i];
		SkillDataCheckSum += k*Berserker_Time[i];
		SkillDataCheckSum += k*Berserker_UseMana[i];

		SkillDataCheckSum += k*Cyclone_Strike_DamagePercent[i];
		SkillDataCheckSum += k*Cyclone_Strike_AreaDamage[i][0];
		SkillDataCheckSum += k*Cyclone_Strike_AreaDamage[i][1];
		SkillDataCheckSum += k*Cyclone_Strike_AttackNum[i];
		SkillDataCheckSum += k*Cyclone_Strike_Area[i];
		SkillDataCheckSum += k*Cyclone_Strike_UseMana[i];

		SkillDataCheckSum += k*Boost_Health_Life[i];

		SkillDataCheckSum += k*Assassin_Eye_AddCritical[i];
		SkillDataCheckSum += k*Assassin_Eye_M_SubCritical[i];
		SkillDataCheckSum += k*Assassin_Eye_Time[i];
		SkillDataCheckSum += k*Assassin_Eye_UseMana[i];

		SkillDataCheckSum += k*Charging_Strike_DamagePercent[i];
		SkillDataCheckSum += k*Charging_Strike_CharingDamagePercent[i];
		SkillDataCheckSum += k*(int)Charging_Strike_Time[i];
		SkillDataCheckSum += k*Charging_Strike_UseMana[i];

		SkillDataCheckSum += k*Vague_EvasionPercent[i];
		SkillDataCheckSum += k*Vague_Time[i];
		SkillDataCheckSum += k*Vague_UseMana[i];

		SkillDataCheckSum += k*Shadow_Master_DamagePercent[i];
		SkillDataCheckSum += k*Shadow_Master_AddHit[i];
		SkillDataCheckSum += k*Shadow_Master_ShadowNum[i];
		SkillDataCheckSum += k*Shadow_Master_UseMana[i];

		SkillDataCheckSum += k*Recall_Wolverin_Damage[i][0];
		SkillDataCheckSum += k*Recall_Wolverin_Damage[i][1];
		SkillDataCheckSum += k*Recall_Wolverin_Hit[i];
		SkillDataCheckSum += k*Recall_Wolverin_Defense[i];
		SkillDataCheckSum += k*Recall_Wolverin_Life[i];
		SkillDataCheckSum += k*Recall_Wolverin_UseMana[i];

		SkillDataCheckSum += k*Evasion_Mastery_AddPercent[i];

		SkillDataCheckSum += k*Phoenix_Shot_DamagePercent[i];
		SkillDataCheckSum += k*(int)Phoenix_Shot_Time[i];
		SkillDataCheckSum += k*Phoenix_Shot_UseMana[i];

		SkillDataCheckSum += k*Force_Of_Nature_AddDamage[i];
		SkillDataCheckSum += k*Force_Of_Nature_AddHit[i];
		SkillDataCheckSum += k*Force_Of_Nature_FalconAddDamage[i];
		SkillDataCheckSum += k*Force_Of_Nature_Time[i];
		SkillDataCheckSum += k*Force_Of_Nature_UseMana[i];
	}

	for(i = 0; i < 10; i++)
	{
		k = i + 1;


		SkillDataCheckSum += k*Divine_Piercing_DamagePercent[i];
		SkillDataCheckSum += k*Divine_Piercing_AddHit[i];
		SkillDataCheckSum += k*Divine_Piercing_AttackNum[i];
		SkillDataCheckSum += k*Divine_Piercing_UseMana[i];

		SkillDataCheckSum += k*Godly_Shield_AbsorbPercent[i];
		SkillDataCheckSum += k*Godly_Shield_Time[i];
		SkillDataCheckSum += k*Godly_Shield_UseMana[i];

		SkillDataCheckSum += k*God_Bless_AddDamage[i];
		SkillDataCheckSum += k*God_Bless_Time[i];
		SkillDataCheckSum += k*God_Bless_UseMana[i];

		SkillDataCheckSum += k*Sword_Of_Justice_DamagePercent[i];
		SkillDataCheckSum += k*Sword_Of_Justice_Area[i];
		SkillDataCheckSum += k*Sword_Of_Justice_UseMana[i];

		SkillDataCheckSum += k*Hall_Of_Valhalla_AddEvation[i];
		SkillDataCheckSum += k*Hall_Of_Valhalla_Time[i];
		SkillDataCheckSum += k*Hall_Of_Valhalla_UseMana[i];

		SkillDataCheckSum += k*X_Rage_DamagePercent[i];
		SkillDataCheckSum += k*X_Rage_Area[i];
		SkillDataCheckSum += k*X_Rage_UseMana[i];

		SkillDataCheckSum += k*Frost_Javelin_IceAddDamage[i][0];
		SkillDataCheckSum += k*Frost_Javelin_IceAddDamage[i][1];
		SkillDataCheckSum += k*Frost_Javelin_SpeedSubPercent[i];
		SkillDataCheckSum += k*Frost_Javelin_IceTime[i];
		SkillDataCheckSum += k*Frost_Javelin_Time[i];
		SkillDataCheckSum += k*Frost_Javelin_UseMana[i];

		SkillDataCheckSum += k*Vengeance_DamagePercent[i];
		SkillDataCheckSum += k*Vengeance_AddCritical[i];
		SkillDataCheckSum += k*Vengeance_Range[i];
		SkillDataCheckSum += k*Vengeance_UseMana[i];

		SkillDataCheckSum += k*Glacial_Spike_Damage[i];
		//SkillDataCheckSum += k*Glacial_Spike_Damage[i][1];
		SkillDataCheckSum += k*Glacial_Spike_Area[i];
		SkillDataCheckSum += k*Glacial_Spike_UseMana[i];

		SkillDataCheckSum += k*(int)Regeneration_Field_LifeRegen[i];
		SkillDataCheckSum += k*(int)Regeneration_Field_ManaRegen[i];
		SkillDataCheckSum += k*Regeneration_Field_Time[i];
		SkillDataCheckSum += k*Regeneration_Field_Area[i];
		SkillDataCheckSum += k*Regeneration_Field_UseMana[i];

		SkillDataCheckSum += k*Chain_Lightning_Damage[i];
		//SkillDataCheckSum += k*Chain_Lightning_Damage[i][1];
		SkillDataCheckSum += k*Chain_Lightning_Num[i];
		SkillDataCheckSum += k*Chain_Lightning_Range[i];
		SkillDataCheckSum += k*Chain_Lightning_UseMana[i];

		SkillDataCheckSum += k*Summon_Muspell_Damage[i][0];
		SkillDataCheckSum += k*Summon_Muspell_Damage[i][1];
		SkillDataCheckSum += k*Summon_Muspell_Attack_Delay[i];
		SkillDataCheckSum += k*Summon_Muspell_UndeadAbsorbPercent[i];
		SkillDataCheckSum += k*Summon_Muspell_BlockPercent[i];
		SkillDataCheckSum += k*Summon_Muspell_Time[i];
		SkillDataCheckSum += k*Summon_Muspell_UseMana[i];

		SkillDataCheckSum += k*Fire_Elemental_Damage[i][0];
		SkillDataCheckSum += k*Fire_Elemental_Damage[i][1];
		SkillDataCheckSum += k*Fire_Elemental_Hit[i];
		SkillDataCheckSum += k*Fire_Elemental_Life[i];
		SkillDataCheckSum += k*Fire_Elemental_UseMana[i];

		SkillDataCheckSum += k*Flame_Wave_FireDamage[i];
		//SkillDataCheckSum += k*Flame_Wave_FireDamage[i][1];
		SkillDataCheckSum += k*Flame_Wave_Area[i];
		SkillDataCheckSum += k*Flame_Wave_UseMana[i];

		SkillDataCheckSum += k*Distortion_SpeedSubPercent[i];
		SkillDataCheckSum += k*Distortion_DamageSubPercent[i];
		SkillDataCheckSum += k*Distortion_Area[i];
		SkillDataCheckSum += k*Distortion_Time[i];
		SkillDataCheckSum += k*Distortion_UseMana[i];

		SkillDataCheckSum += k*Meteo_Damage[i];
		//SkillDataCheckSum += k*Meteo_Damage[i][1];
		SkillDataCheckSum += k*Meteo_Area[i];
		SkillDataCheckSum += k*Meteo_UseMana[i];

	}

	// CHECKSUM DAS SKILLS
	unsigned int sinSKillInfoData = 612842;
	unsigned int sinSKillData = 2616403;

	// CALCULO DO CHECKSUM
	if(sinSKillData != SkillDataCheckSum)
	{
		SendSetHackUser(5);
	}


	for(i = 0; i < SIN_MAX_SKILL; i++)
	{
		k = i + 1;
		SkillInfoDataCheckSum += k*sSkill_Info[i].RequireLevel;
		SkillInfoDataCheckSum += k*sSkill_Info[i].UseStamina[0];
		SkillInfoDataCheckSum += k*sSkill_Info[i].UseStamina[1];
	}


	if(sinSKillInfoData != SkillInfoDataCheckSum)
	{
		SendSetHackUser(5);

	}

	for(int j = 1; j < SIN_MAX_USE_SKILL; j++)
	{
		if(sinSkill.UseSkill[j].Flag)
		{

			if(!SkillDataCheckFlag2)
			{
				ReformSkillPointForm(&sinSkill.UseSkill[j]);
			}
			if(!CheckSkillPointForm(&sinSkill.UseSkill[j]))return FALSE;
			if(!CheckSkillMasteryForm(&sinSkill.UseSkill[j]))return FALSE;

		}
	}
	SkillDataCheckFlag2 = 1;


	return TRUE;
}



int cSKILL::InitSkillPoint(int kind)
{

	switch(kind)
	{
		case 0:
		if(!sinInitPointPassFlag)
		{
			if(sinChar->wVersion[1] == 1)
			{
				cMessageBox.ShowMessage(MESSAGE_ALREADY_INITSTATE);
				return FALSE;
			}
		}
		break;
	}
	sinInitPointPassFlag = 0;

	CheckingNowSkillState();
	CheckCharForm();
	int Count = 0;
	int Count2 = 0;

	for(int j = 1; j < ChangeJobSkillPlus; j++)
	{
		if(j > 12)
		{
			if(sinSkill.UseSkill[j].Point > 0)
				Count2 += sinSkill.UseSkill[j].Point;
		}
		else
		{
			if(sinSkill.UseSkill[j].Point > 0)
				Count += sinSkill.UseSkill[j].Point;
		}

		cSkill.CheckSkillMasteryForm(0, j);
		CheckSkillPointForm(&sinSkill.UseSkill[j]);
		sinSkill.UseSkill[j].Point = 0;
		sinSkill.UseSkill[j].GageLength = 0;
		sinSkill.UseSkill[j].GageLength2 = 0;
		sinSkill.UseSkill[j].Mastery = 0;
		sinSkill.UseSkill[j].UseSKillIncreCount = 0;
		sinSkill.UseSkill[j].UseSkillCount = 0;
		sinSkill.UseSkill[j].UseSkillMastery = 0;
		sinSkill.UseSkill[j].UseSkillMasteryGage = 0;
		sinSkill.UseSkill[j].Use = 0;
		ReformSkillPointForm(&sinSkill.UseSkill[j]);
		ReformSkillMasteryForm(0, j);

	}
	sinSkill.SkillPoint += Count;
	sinSkill.SkillPoint4 += Count2;
	sinChar->wVersion[1] = 1;
	ReformCharForm();
	cMessageBox.ShowMessage(MESSAGE_GYUNGFUM_OK);
	cInvenTory.SetItemToChar();

	return TRUE;
}


DWORD ClearSkillPointCODE[10] = { 0,0,0,0,0,0,0,0,0,0 };

int cSKILL::SearchClearSkillPoint(DWORD CODE)
{

	for(int i = 0; i < 10; i++)
	{
		if(ClearSkillPointCODE[i] == CODE)
		{
			ClearSkillCODE = ClearSkillPointCODE[i];
			return TRUE;
		}
		else
			ClearSkillCODE = 0;
	}

	return FALSE;

}


int cSKILL::ShowClearSkillPointButton(int x, int y)
{
	ClearSkillButtonPosi.x = -50;
	ClearSkillButtonPosi.y = -50;

	if(ClearSkillCODE && !sinMessageBoxShowFlag)
	{
		ClearSkillButtonPosi.x = x - 57;
		ClearSkillButtonPosi.y = y - 51;
		DrawSprite(ClearSkillButtonPosi.x, ClearSkillButtonPosi.y, lpSkillDown, 0, 0, 50, 44);
	}

	return TRUE;
}


int cSKILL::ClearSkillPointSection()
{

	CheckingNowSkillState();
	CheckCharForm();
	int Count = 0;
	for(int j = 1; j < ChangeJobSkillPlus; j++)
	{
		if(sinSkill.UseSkill[j].Flag && sinSkill.UseSkill[j].Point > 1)
		{
			for(int i = 0; i < 10; i++)
			{
				if(sinSkill.UseSkill[j].CODE == ClearSkillPointCODE[i])
				{
					cSkill.CheckSkillMasteryForm(0, j);
					CheckSkillPointForm(&sinSkill.UseSkill[j]);
					sinSkill.UseSkill[j].Point--;
					sinSkill.UseSkill[j].GageLength = 0;
					sinSkill.UseSkill[j].GageLength2 = 0;
					sinSkill.UseSkill[j].Mastery = 0;
					sinSkill.UseSkill[j].UseSKillIncreCount = 0;
					sinSkill.UseSkill[j].UseSkillCount = 0;
					sinSkill.UseSkill[j].UseSkillMastery = 0;
					sinSkill.UseSkill[j].UseSkillMasteryGage = 0;
					sinSkill.UseSkill[j].Use = 0;
					ReformSkillPointForm(&sinSkill.UseSkill[j]);
					ReformSkillMasteryForm(0, j);
					sinSkill.SkillPoint++;
					ClearSkillCODE = 0;
					LearnSkillEffect(0);
					ReformCharForm();
					return TRUE;
				}
			}
		}
	}
	return TRUE;
}


unsigned int CharSkillInfoData[8] = { 0, };
int   ChangeJob = -1;

int cSKILL::ReFormCharSkillInfo()
{
	int   i = 0, j = 0, k = 0;
	int   CharNum = 0;

	int   CharCode[MAX_JOBNUM] = { JOBCODE_MECHANICIAN, JOBCODE_FIGHTER, JOBCODE_ARCHER, JOBCODE_PIKEMAN, JOBCODE_KNIGHT, JOBCODE_ATALANTA, JOBCODE_PRIESTESS, JOBCODE_MAGICIAN, JOBCODE_ASSASSINE, JOBCODE_SHAMAN };

	for(i = 0; i < MAX_JOBNUM; i++)
	{
		if(sinChar->JOB_CODE == CharCode[i])
		{
			CharNum = i;
			break;
		}
	}

	if(ChangeJob != sinChar->ChangeJob)
	{
		ChangeJob = sinChar->ChangeJob;
		CharSkillInfoData[CharNum] = 0;
		for(j = 1; j < SIN_MAX_USE_SKILL; j++)
		{
			if(sinSkill.UseSkill[j].Flag)
			{
				k = j + 1;
				CharSkillInfoData[CharNum] += k*sinSkill.UseSkill[j].Skill_Info.RequireLevel;
				CharSkillInfoData[CharNum] += k*sinSkill.UseSkill[j].Skill_Info.UseStamina[0];
				CharSkillInfoData[CharNum] += k*sinSkill.UseSkill[j].Skill_Info.UseStamina[1];
			}
		}
	}
	return TRUE;
}


int cSKILL::CheckCharSkillInfo()
{

	int   i = 0, j = 0, k = 0;
	int   CharNum = 0;
	int   CharCode[MAX_JOBNUM] = { JOBCODE_MECHANICIAN, JOBCODE_FIGHTER, JOBCODE_ARCHER, JOBCODE_PIKEMAN, JOBCODE_KNIGHT, JOBCODE_ATALANTA, JOBCODE_PRIESTESS, JOBCODE_MAGICIAN, JOBCODE_ASSASSINE, JOBCODE_SHAMAN };

	unsigned int CharSkillInfoDataCheckSum[8] = { 0, };


	for(i = 0; i < MAX_JOBNUM; i++)
	{
		if(sinChar->JOB_CODE == CharCode[i])
		{
			CharNum = i;
			break;
		}
	}


	for(j = 1; j < SIN_MAX_USE_SKILL; j++)
	{
		if(sinSkill.UseSkill[j].Flag)
		{
			k = j + 1;
			CharSkillInfoDataCheckSum[CharNum] += k*sinSkill.UseSkill[j].Skill_Info.RequireLevel;
			CharSkillInfoDataCheckSum[CharNum] += k*sinSkill.UseSkill[j].Skill_Info.UseStamina[0];
			CharSkillInfoDataCheckSum[CharNum] += k*sinSkill.UseSkill[j].Skill_Info.UseStamina[1];

			if(!sinSkill.UseSkill[j].UseSkillCount)continue;
			if(!CheckSkillMasteyData[j])
			{
				CheckSkillMasteyData[j] = sinSkill.UseSkill[j].UseSkillCount;
			}
			if(CheckSkillMasteyData[j] < (sinSkill.UseSkill[j].UseSkillCount) - 200)
			{
				SendSetHackUser3(55, CheckSkillMasteyData[j], sinSkill.UseSkill[j].UseSkillCount);
				return FALSE;

			}
			else
			{
				CheckSkillMasteyData[j] = sinSkill.UseSkill[j].UseSkillCount;

			}
		}
	}
	if(CharSkillInfoDataCheckSum[CharNum] != CharSkillInfoData[CharNum])
	{

		SendSetHackUser3(51, CharSkillInfoDataCheckSum[CharNum], CharSkillInfoData[CharNum]);
		return FALSE;
	}


	return TRUE;
}

int cSKILL::CheckSkillMasteryForm(sSKILL *pSkill, int Index)
{
	if(pSkill)
	{
		for(int j = 1; j < SIN_MAX_USE_SKILL; j++)
		{
			if(sinSkill.UseSkill[j].Flag)
			{
				if(pSkill->CODE == sinSkill.UseSkill[j].CODE)
				{
					Index = j;
					break;
				}
			}
		}
	}



	int CheckMasteryDataSum = lpCurPlayer->dwObjectSerial + sinSkill.UseSkill[Index].CODE;

	CheckMasteryDataSum += (sinSkill.UseSkill[Index].GageLength*Index);
	CheckMasteryDataSum += (sinSkill.UseSkill[Index].GageLength2*Index);
	CheckMasteryDataSum += (sinSkill.UseSkill[Index].Mastery*Index);

	if(CheckMasteryData[Index] != CheckMasteryDataSum)
	{


		SendSetHackUser3(52, CheckMasteryData[Index], CheckMasteryDataSum);
		return FALSE;

	}

	return TRUE;
}
int cSKILL::ReformSkillMasteryForm(sSKILL *pSkill, int Index)
{

	if(pSkill)
	{
		for(int j = 1; j < SIN_MAX_USE_SKILL; j++)
		{
			if(sinSkill.UseSkill[j].Flag)
			{
				if(pSkill->CODE == sinSkill.UseSkill[j].CODE)
				{
					Index = j;
				}
			}
		}
	}

	CheckMasteryData[Index] = lpCurPlayer->dwObjectSerial + sinSkill.UseSkill[Index].CODE;
	CheckMasteryData[Index] += (sinSkill.UseSkill[Index].GageLength*Index);
	CheckMasteryData[Index] += (sinSkill.UseSkill[Index].GageLength2*Index);
	CheckMasteryData[Index] += (sinSkill.UseSkill[Index].Mastery*Index);

	return TRUE;
}


int cSKILL::CheckSkillPointForm(sSKILL *pSkill)
{
	DWORD	dwXorKey = lpCurPlayer->dwObjectSerial & 0x5F;

	for(int j = 1; j < SIN_MAX_USE_SKILL; j++)
	{
		if(sinSkill.UseSkill[j].Flag &&sinSkill.UseSkill[j].Use &&sinSkill.UseSkill[j].Point)
		{
			if(pSkill->CODE == sinSkill.UseSkill[j].CODE)
			{

				if(CheckSkillPointData[j] != (sinSkill.UseSkill[j].Point^dwXorKey))
				{
					SendSetHackUser3(54, CheckSkillPointData[j], sinSkill.UseSkill[j].Point);
					return FALSE;
				}

			}
		}
	}

	return TRUE;
}


int cSKILL::ReformSkillPointForm(sSKILL *pSkill)
{
	DWORD	dwXorKey = lpCurPlayer->dwObjectSerial & 0x5F;

	for(int j = 1; j < SIN_MAX_USE_SKILL; j++)
	{
		if(sinSkill.UseSkill[j].Flag)
		{
			if(pSkill->CODE == sinSkill.UseSkill[j].CODE)
			{
				CheckSkillPointData[j] = (sinSkill.UseSkill[j].Point^dwXorKey);
				break;
			}
		}
	}
	return TRUE;
}


int cSKILL::InitReformSkillPointForm()
{


	return TRUE;
}


int cSKILL::GetSkillPoint(DWORD CODE)
{
	for(int j = 1; j < SIN_MAX_USE_SKILL; j++)
	{
		if(sinSkill.UseSkill[j].Flag)
		{
			if(CODE == sinSkill.UseSkill[j].CODE)
			{
				return sinSkill.UseSkill[j].Point;
			}
		}
	}

	return 0;
}


int cSKILL::SearchContiueSkill(DWORD CODE)
{
	for(int k = 0; k < 10; k++)
	{
		if(ContinueSkill[k].Flag)
		{
			if(ContinueSkill[k].CODE == CODE)
			{
				return ContinueSkill[k].Point;

			}
		}
	}
	return 0;
}


int cSKILL::SearchContiueSkillIndex(DWORD CODE)
{
	for(int k = 0; k < 10; k++)
	{
		if(ContinueSkill[k].Flag)
		{
			if(ContinueSkill[k].CODE == CODE)
			{
				return k + 1;
			}
		}
	}
	return 0;
}

int cSKILL::SearchContiueSkillCODE(DWORD CODE)
{
	for(int k = 0; k < 10; k++)
	{
		if(ContinueSkill[k].Flag)
		{
			if(ContinueSkill[k].CODE == CODE)
			{
				return ContinueSkill[k].CODE;
			}
		}
	}
	return 0;
}


int AddVirtualLife[2] = { 0,0 };
int sinVirtualLifeTime = 0;
int sinVirtualLifePercent = 0;


int AddBoosterLife = 0;
int BoosterLifeTime = 0;
int BoosterLifePercent = 0;
int LifeFlag = 0;
short tempLife[2] = { 0,0 };


int AddVirtualMana[2] = { 0,0 };
int sinVirtualManaTime = 0;
int sinVirtualManaPercent = 0;
int ManaFlag = 0;
short tempMana[2] = { 0,0 };


int AddVirtualStamina[2] = { 0,0 };
int sinVirtualStaminaTime = 0;
int sinVirtualStaminaPercent = 0;
int StaminaFlag = 0;
short tempStamina[2] = { 0,0 };


int sinAddSkillDelay = 0;
int sinSkillDelayTime = 0;
int SkillDelayFlag = 0;

int cSKILL::SetVirtualLife(int Time, int Point)
{


	for(int i = 0; i < MAX_CONTINUE_SKILL; i++)
	{
		if(ContinueSkill[i].Flag)
		{
			if(ContinueSkill[i].CODE == SKILL_VIRTUAL_LIFE)
			{

				return FALSE;
			}
		}
	}

	for(int i = 0; i < MAX_CONTINUE_SKILL; i++)
	{
		if(!ContinueSkill[i].Flag)
		{
			ContinueSkill[i].Flag = 1;
			ContinueSkill[i].CODE = SKILL_VIRTUAL_LIFE;
			ContinueSkill[i].UseTime = Time;
			ContinueSkill[i].Point = Point;
			SearchSkillDoc(&ContinueSkill[i]);
			break;
		}
	}

	AddVirtualLife[1] = ((int)sinChar->Life[1] * Virtual_Life_Percent[Point - 1]) / 100;
	sinVirtualLifeTime = Time;
	sinVirtualLifePercent = Virtual_Life_Percent[Point - 1];
	CheckVirtualLifeTime = 0;
	cInvenTory.SetItemToChar();
	return TRUE;
}


int cSKILL::UseBoosterItem(sITEM *pItem)
{
	if(lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_VILLAGE)
		return FALSE;

	DWORD BoosterCODE;
	DWORD ItemMask;
	int BoosterTime = 0;
	int cnt = 0;

	ItemMask = pItem->CODE&sinITEM_MASK3;
	if(ItemMask == sin21 || ItemMask == sin24 || ItemMask == sin27) cnt = 0;
	if(ItemMask == sin22 || ItemMask == sin25 || ItemMask == sin28) cnt = 1;
	if(ItemMask == sin23 || ItemMask == sin26 || ItemMask == sin29) cnt = 2;

	switch(ItemMask)
	{
		case sin21:
		case sin22:
		case sin23:
		BoosterCODE = BOOSTER_ITEM_LIFE;
		BoosterTime = BoosterItem_UseTime[cnt];

		AddBoosterLife = ((int)sinChar->Life[1] * BoosterItem_DataPercent[0]) / 100;
		BoosterLifeTime = BoosterTime;
		BoosterLifePercent = BoosterItem_DataPercent[0];
		CheckBoosterLifeTime = 0;
		break;
		case sin24:
		case sin25:
		case sin26:
		BoosterCODE = BOOSTER_ITEM_MANA;
		BoosterTime = BoosterItem_UseTime[cnt];


		AddVirtualMana[1] = ((int)sinChar->Mana[1] * BoosterItem_DataPercent[1]) / 100;
		sinVirtualManaTime = BoosterTime;
		sinVirtualManaPercent = BoosterItem_DataPercent[1];
		CheckVirtualManaTime = 0;
		break;
		case sin27:
		case sin28:
		case sin29:
		BoosterCODE = BOOSTER_ITEM_STAMINA;
		BoosterTime = BoosterItem_UseTime[cnt];


		AddVirtualStamina[1] = ((int)sinChar->Stamina[1] * BoosterItem_DataPercent[2]) / 100;
		sinVirtualStaminaTime = BoosterTime;
		sinVirtualStaminaPercent = BoosterItem_DataPercent[2];
		CheckVirtualStaminaTime = 0;
		break;
	}

	sSKILL TempSkill;

	if(cSkill.SearchContiueSkillCODE(BoosterCODE) == BoosterCODE && BoosterCODE != 0)
	{
		cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
		haCastleSkillUseFlag = 0;
		return TRUE;
	}
	haCastleSkillUseFlag = 1;

	for(int j = 0; j < SIN_MAX_SKILL; j++)
	{
		if(sSkill[j].CODE == BoosterCODE)
		{
			memcpy(&TempSkill, &sSkill[j], sizeof(sSKILL));
			TempSkill.UseTime = BoosterTime;
			sinContinueSkillSet(&TempSkill);
			SwitchSkill(&TempSkill);
			break;
		}
	}

	tempLife[1] = sinChar->Level;
	tempMana[1] = sinChar->Level;
	tempStamina[1] = sinChar->Level;

	sinPlaySound(SIN_SOUND_EAT_POTION2);
	cInvenTory.SetItemToChar();
	return TRUE;
}


int cSKILL::SetBoosterItem(DWORD ItemCODE, int Time)
{
	int UseFlag = 0;
	sSKILL TempSkill;
	memset(&TempSkill, 0, sizeof(sSKILL));
	char *Path = "";

	DWORD ItemMask;
	int cnt = 0;

	ItemMask = ItemCODE&sinITEM_MASK3;

	if(ItemMask == sin21 || ItemMask == sin24 || ItemMask == sin27) cnt = 0;
	if(ItemMask == sin22 || ItemMask == sin25 || ItemMask == sin28) cnt = 1;
	if(ItemMask == sin23 || ItemMask == sin26 || ItemMask == sin29) cnt = 2;

	switch(ItemMask)
	{

		case sin21:
		case sin22:
		case sin23:
		UseFlag = 0;
		Path = "image\\Sinimage\\skill\\keep\\Booster_01.tga";
		TempSkill.CODE = BOOSTER_ITEM_LIFE;
		TempSkill.Point = 0;
		TempSkill.UseTime = BoosterItem_UseTime[cnt];
		TempSkill.CheckTime = (BoosterItem_UseTime[cnt] * 70) - (Time * 70);
		TempSkill.MatIcon = Mat_BoosterItem[UseFlag];
		break;


		case sin24:
		case sin25:
		case sin26:
		UseFlag = 1;
		Path = "image\\Sinimage\\skill\\keep\\Booster_02.tga";
		TempSkill.CODE = BOOSTER_ITEM_MANA;
		TempSkill.Point = 0;
		TempSkill.UseTime = BoosterItem_UseTime[cnt];
		TempSkill.CheckTime = (BoosterItem_UseTime[cnt] * 70) - (Time * 70);
		TempSkill.MatIcon = Mat_BoosterItem[UseFlag];
		break;


		case sin27:
		case sin28:
		case sin29:
		UseFlag = 2;
		Path = "image\\Sinimage\\skill\\keep\\Booster_03.tga";
		TempSkill.CODE = BOOSTER_ITEM_STAMINA;
		TempSkill.Point = 0;
		TempSkill.UseTime = BoosterItem_UseTime[cnt];
		TempSkill.CheckTime = (BoosterItem_UseTime[cnt] * 70) - (Time * 70);
		TempSkill.MatIcon = Mat_BoosterItem[UseFlag];
		break;
	}

	char szBuff[128];
	if(!Mat_BoosterItem[UseFlag])
	{
		wsprintf(szBuff, Path, UseFlag);
		Mat_BoosterItem[UseFlag] = CreateTextureMaterial(szBuff, 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
		ReadTextures();
	}

	sinContinueSkillSet(&TempSkill);

	if(UseFlag == 0)
	{

		AddBoosterLife = ((int)sinChar->Life[1] * BoosterItem_DataPercent[UseFlag]) / 100;
		BoosterLifeTime = Time;
		BoosterLifePercent = BoosterItem_DataPercent[UseFlag];
		CheckBoosterLifeTime = 0;
	}
	else if(UseFlag == 1)
	{

		AddVirtualMana[1] = ((int)sinChar->Mana[1] * BoosterItem_DataPercent[UseFlag]) / 100;
		sinVirtualManaTime = Time;
		sinVirtualManaPercent = BoosterItem_DataPercent[UseFlag];
		CheckVirtualManaTime = 0;
	}
	else if(UseFlag == 2)
	{

		AddVirtualStamina[1] = ((int)sinChar->Stamina[1] * BoosterItem_DataPercent[UseFlag]) / 100;
		sinVirtualStaminaTime = Time;
		sinVirtualStaminaPercent = BoosterItem_DataPercent[UseFlag];
		CheckVirtualStaminaTime = 0;
	}

	cInvenTory.SetItemToChar();

	return TRUE;
}


int cSKILL::SetSkillDelayItem(DWORD ItemCODE, int Time)
{
	int UseFlag = 0;
	sSKILL TempSkill;
	memset(&TempSkill, 0, sizeof(sSKILL));
	char *Path = "";

	DWORD ItemMask;
	int cnt = 0;

	ItemMask = ItemCODE&sinITEM_MASK3;

	if(ItemMask == sin30 || ItemMask == sin33 || ItemMask == sin36) cnt = 0;
	if(ItemMask == sin31 || ItemMask == sin34 || ItemMask == sin37) cnt = 1;
	if(ItemMask == sin32 || ItemMask == sin35 || ItemMask == sin38) cnt = 2;

	switch(ItemMask)
	{

		case sin30:
		case sin31:
		case sin32:
		UseFlag = 0;
		Path = "image\\Sinimage\\skill\\keep\\Booster_01.tga";
		TempSkill.CODE = SKILLDELAY_ITEM_LIFE;
		TempSkill.Point = 0;
		TempSkill.UseTime = nSkillDelay_UseTime[cnt];
		TempSkill.CheckTime = (nSkillDelay_UseTime[cnt] * 70) - (Time * 70);
		TempSkill.MatIcon = nMat_SkillDelayItem[UseFlag];
		break;
	}


	char szBuff[128];
	if(!nMat_SkillDelayItem[UseFlag])
	{
		wsprintf(szBuff, Path, UseFlag);
		nMat_SkillDelayItem[UseFlag] = CreateTextureMaterial(szBuff, 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
		ReadTextures();
	}

	sinContinueSkillSet(&TempSkill);

	if(UseFlag == 0)
	{
		sinAddSkillDelay = 10;
		sinSkillDelayTime = Time;
		BoosterLifePercent = BoosterItem_DataPercent[UseFlag];
		CheckSkillDelayTime = 0;
	}


	cInvenTory.SetItemToChar();

	return TRUE;
}



int cSKILL::UseSkillDelayItem(sITEM *pItem)
{
	DWORD SkillDelayCODE;
	DWORD ItemMask;
	int SkillDelayTime = 0;
	int cnt = 0;

	ItemMask = pItem->CODE&sinITEM_MASK3;
	if(ItemMask == sin30 || ItemMask == sin33 || ItemMask == sin36) cnt = 0;
	if(ItemMask == sin31 || ItemMask == sin34 || ItemMask == sin37) cnt = 1;
	if(ItemMask == sin32 || ItemMask == sin35 || ItemMask == sin38) cnt = 2;

	switch(ItemMask)
	{
		case sin30:
		case sin31:
		case sin32:
		SkillDelayCODE = SKILLDELAY_ITEM_LIFE;
		SkillDelayTime = nSkillDelay_UseTime[cnt];

		sinAddSkillDelay = 10;
		sinSkillDelayTime = SkillDelayTime;
		CheckSkillDelayTime = 0;
		break;
	}

	sSKILL TempSkill;

	if(cSkill.SearchContiueSkillCODE(SkillDelayCODE) == SkillDelayCODE && SkillDelayCODE != 0)
	{
		cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
		haCastleSkillUseFlag = 0;
		return TRUE;
	}
	haCastleSkillUseFlag = 1;

	for(int j = 0; j < SIN_MAX_SKILL; j++)
	{
		if(sSkill[j].CODE == SkillDelayCODE)
		{
			memcpy(&TempSkill, &sSkill[j], sizeof(sSKILL));
			TempSkill.UseTime = SkillDelayTime;
			sinContinueSkillSet(&TempSkill);
			SwitchSkill(&TempSkill);
			break;
		}
	}

	sinPlaySound(SIN_SOUND_EAT_POTION2);
	cInvenTory.SetItemToChar();
	return TRUE;
}



int cSKILL::SetT_Of_Valhalla(int Point, int LV)
{


	for(int i = 0; i < MAX_CONTINUE_SKILL; i++)
	{
		if(ContinueSkill[i].Flag)
		{
			if(ContinueSkill[i].CODE == SKILL_TRIUMPH_OF_VALHALLA || ContinueSkill[i].CODE == SKILL_HALL_OF_VALHALLA)
			{

				return FALSE;
			}
		}
	}

	for(int i = 0; i < MAX_CONTINUE_SKILL; i++)
	{
		if(!ContinueSkill[i].Flag)
		{
			ContinueSkill[i].Flag = 1;
			ContinueSkill[i].CODE = SKILL_TRIUMPH_OF_VALHALLA;
			ContinueSkill[i].UseTime = T_Of_Valhalla_Time[Point - 1];
			ContinueSkill[i].Point = Point;
			SearchSkillDoc(&ContinueSkill[i]);
			break;
		}
	}

	SetT_Of_ValhallaLV = LV;

	if(SetT_Of_ValhallaFlag2)
	{
		SetT_Of_ValhallaFlag2 = 0;
		SetT_Of_ValhallaFlag = 0;
	}
	else
	{
		SetT_Of_ValhallaFlag = 1;

	}
	cInvenTory.SetItemToChar();
	return TRUE;
}


int cSKILL::SetEnchant_Weapon(int Time, int Point)
{


	for(int i = 0; i < MAX_CONTINUE_SKILL; i++)
	{
		if(ContinueSkill[i].Flag)
		{
			if(ContinueSkill[i].CODE == SKILL_ENCHANT_WEAPON)
			{

				return FALSE;
			}
		}
	}

	for(int i = 0; i < MAX_CONTINUE_SKILL; i++)
	{
		if(!ContinueSkill[i].Flag)
		{
			ContinueSkill[i].Flag = 1;
			ContinueSkill[i].CODE = SKILL_ENCHANT_WEAPON;
			ContinueSkill[i].UseTime = Time;
			ContinueSkill[i].Point = Point;
			SearchSkillDoc(&ContinueSkill[i]);
			break;
		}
	}
	cInvenTory.SetItemToChar();
	return TRUE;
}


int cSKILL::ForeceOfNature(int Time, int Point, int Party)
{


	for(int i = 0; i < MAX_CONTINUE_SKILL; i++)
	{
		if(ContinueSkill[i].Flag)
		{
			if(ContinueSkill[i].CODE == SKILL_FORCE_OF_NATURE)
			{
				if(ContinueSkill[i].Flag == 2 && !Party)
				{
					memset(&ContinueSkill[i], 0, sizeof(sSKILL));
					break;
				}
				else return FALSE;
			}
		}
	}

	for(int i = 0; i < MAX_CONTINUE_SKILL; i++)
	{
		if(!ContinueSkill[i].Flag)
		{
			ContinueSkill[i].Flag = Party + 1;
			ContinueSkill[i].CODE = SKILL_FORCE_OF_NATURE;
			ContinueSkill[i].UseTime = Time;
			ContinueSkill[i].Point = Point;
			SearchSkillDoc(&ContinueSkill[i]);
			break;
		}
	}
	cInvenTory.SetItemToChar();
	return TRUE;
}


int cSKILL::HellOfValhalla(int Time, int Point, int TVPoint, int LV, int Party)
{


	for(int i = 0; i < MAX_CONTINUE_SKILL; i++)
	{
		if(ContinueSkill[i].Flag)
		{
			if(ContinueSkill[i].CODE == SKILL_HALL_OF_VALHALLA)
			{
				if(ContinueSkill[i].Flag == 2 && !Party)
				{
					memset(&ContinueSkill[i], 0, sizeof(sSKILL));
					break;
				}
				else return FALSE;
			}
		}
	}

	for(int i = 0; i < MAX_CONTINUE_SKILL; i++)
	{
		if(!ContinueSkill[i].Flag)
		{
			ContinueSkill[i].Flag = Party + 1;
			ContinueSkill[i].CODE = SKILL_HALL_OF_VALHALLA;
			ContinueSkill[i].UseTime = Time;
			ContinueSkill[i].Point = Point;
			SearchSkillDoc(&ContinueSkill[i]);
			break;
		}
	}
	SetT_Of_ValhallaPOINT = TVPoint;
	SetH_Of_ValhallaLV = LV;
	cInvenTory.SetItemToChar();
	return TRUE;
}



int cSKILL::Regeneration_Field(int Time, int Point, int Party)
{


	for(int i = 0; i < MAX_CONTINUE_SKILL; i++)
	{
		if(ContinueSkill[i].Flag)
		{
			if(ContinueSkill[i].CODE == SKILL_REGENERATION_FIELD)
			{
				if(ContinueSkill[i].UseTime > Time)return FALSE;
				ContinueSkill[i].UseTime = Time;
				return TRUE;
			}
		}
	}

	for(int i = 0; i < MAX_CONTINUE_SKILL; i++)
	{
		if(!ContinueSkill[i].Flag)
		{
			ContinueSkill[i].Flag = 1 + Party;
			ContinueSkill[i].CODE = SKILL_REGENERATION_FIELD;
			ContinueSkill[i].UseTime = Time;
			ContinueSkill[i].Point = Point;
			SearchSkillDoc(&ContinueSkill[i]);
			break;
		}
	}
	cInvenTory.SetItemToChar();
	return TRUE;
}


int cSKILL::SearchSkillDoc(sSKILL *pSkill)
{

	for(int i = 0; i < SIN_MAX_SKILL; i++)
	{
		if(pSkill->CODE == sSkill_Info[i].CODE)
		{
			if(pSkill->CODE == SKILL_FORCE_ORB)
			{
			#ifdef _LANGUAGE_CHINESE
				wsprintf(pSkill->Skill_Info.SkillName, "%s%s", SheltomName2[pSkill->Point - 1], sSkill_Info[i].SkillName);
			#else
				if(pSkill->ElementIndex == 1000)
				{
					wsprintf(pSkill->Skill_Info.SkillName, "%s %s", BillingMagicForceName, sSkill_Info[i].SkillName);
				}
				else if(pSkill->ElementIndex == 2000)
				{
					wsprintf(pSkill->Skill_Info.SkillName, "%s %s %s", MagicForceName, SheltomName2[pSkill->Point - 1], sSkill_Info[i].SkillName);
				}
				else
					wsprintf(pSkill->Skill_Info.SkillName, "%s %s", SheltomName2[pSkill->Point - 1], sSkill_Info[i].SkillName);
			#endif

			}
			else
			{
				strcpy_s(pSkill->Skill_Info.SkillName, sSkill_Info[i].SkillName);
			}
			strcpy_s(pSkill->Skill_Info.SkillDoc, sSkill_Info[i].SkillDoc);
			break;

		}

	}

	return TRUE;
}


int cSKILL::SkillBarDraw(sSKILL *pSkill, int x, int y, int Alpha)
{

	DRZD3DTLVERTEX tlVertex[73];

	int Time = 0;

	Time = (int)(((float)pSkill->CheckTime / ((float)pSkill->UseTime*70.0f))*72.0f);

	float fx, fy = 0;

	int i = 0, j = 0;
	int sinY, cosY;
	tlVertex[0].rhw = 1;
	tlVertex[0].color = RGBA_MAKE(0, Alpha, Alpha, Alpha);
	tlVertex[0].specular = RGBA_MAKE(0, 0, 0, 0);
	tlVertex[0].sz = 0;

	tlVertex[0].sx = float(x);
	tlVertex[0].sy = float(y);
	tlVertex[0].tu = 0.5;
	tlVertex[0].tv = 0.5f;


	for(i = 1; i < Time + 1; i++)
	{
		tlVertex[i].rhw = 1;
		if(pSkill->CODE == SKILL_FORCE_ORB)
		{
			tlVertex[i].color = RGBA_MAKE(255, 190, 30, Alpha);
		}
		else
			tlVertex[i].color = RGBA_MAKE(0, 255, 200, Alpha);
		tlVertex[i].specular = RGBA_MAKE(0, 0, 0, 0);
		tlVertex[i].sz = 0;

		sinY = GetSin[(1024 / 2) + (i * 56)&ANGCLIP];
		cosY = GetCos[(1024 / 2) + ((i * 56) + ANGLE_180)&ANGCLIP];

		fx = (float)((10 * sinY + 10 * cosY) >> 8);
		fy = (float)((10 * cosY - 10 * sinY) >> 8);
		fx /= 256;
		fy /= 256;

		tlVertex[i].sx = (float)(fx + x);
		tlVertex[i].sy = (float)(fy + y);
		tlVertex[i].tu = 0.5f;
		tlVertex[i].tv = 0.5f;

	}


	renderDevice.SetTexture(0, 0);
	renderDevice.DrawPrimitive(D3DPT_TRIANGLEFAN,
							   D3DFVF_TLVERTEX,
							   tlVertex,
							   i,
							   NULL);

	return TRUE;
}




int cSKILL::CheckContinueIcon()
{
	for(int i = 0; i < MAX_CONTINUE_SKILL; i++)
	{
		if(ContinueSkill[i].Flag)
		{
			if(!ContinueSkill[i].MatIcon)
			{
				for(int j = 0; j < SIN_MAX_SKILL; j++)
				{
					if(ContinueSkill[i].CODE == sSkill[j].CODE)
					{
						if(sSkill[j].MatIcon)
						{
							ContinueSkill[i].MatIcon = sSkill[j].MatIcon;
							return TRUE;
						}
					}
				}
			}
		}
	}
	return FALSE;
}


int cSKILL::CancelContinueSkill(DWORD CODE)
{

	for(int i = 0; i < MAX_CONTINUE_SKILL; i++)
	{
		if(ContinueSkill[i].Flag)
		{
			if(ContinueSkill[i].CODE == CODE)
			{
				memset(&ContinueSkill[i], 0, sizeof(sSKILL));
				cInvenTory.SetItemToChar();
				break;
			}
		}
	}
	return FALSE;
}


int cSKILL::SkillShortKeyInit()
{
	for(int j = 1; j < SIN_MAX_USE_SKILL; j++)
	{
		sinSkill.UseSkill[j].ShortKey = 0;
	}
	return TRUE;
}


int cSKILL::CheckMaturedSkill(int ChangeJob)
{
	int matured_skill_count = 0;

	switch(ChangeJob)
	{
		case 1:
		for(int j = 1; j < 5; j++)
		{
			if(sinSkill.UseSkill[j].UseSkillCount < 10000 && sinSkill.UseSkill[j].Skill_Info.USECODE != SIN_SKILL_USE_NOT &&
			   sinSkill.UseSkill[j].UseSkillMastery)
			{
				matured_skill_count++;
			}
		}
		break;
		case 2:
		for(int j = 5; j < 9; j++)
		{
			if(sinSkill.UseSkill[j].UseSkillCount < 10000 && sinSkill.UseSkill[j].Skill_Info.USECODE != SIN_SKILL_USE_NOT &&
			   sinSkill.UseSkill[j].UseSkillMastery)
			{
				matured_skill_count++;
			}
		}
		break;
		case 3:
		for(int j = 9; j < 13; j++)
		{
			if(sinSkill.UseSkill[j].UseSkillCount < 10000 && sinSkill.UseSkill[j].Skill_Info.USECODE != SIN_SKILL_USE_NOT &&
			   sinSkill.UseSkill[j].UseSkillMastery)
			{
				matured_skill_count++;
			}
		}
		break;
	}

	if(matured_skill_count <= 4 && matured_skill_count > 0)
		return TRUE;
	else
		return FALSE;
}

