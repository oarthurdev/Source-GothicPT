#ifndef	_CHARACTER_HEADER
#define	_CHARACTER_HEADER

#include "smPacket.h"
#include "smLib3d\smObj3d.h"
#include "PvP\Score.h"

struct smMOTIONINFO;
struct smTHREADSOCK;

#define PLAYBUFF_SIZE		256
#define PLAYBUFF_MASK		255

#define PLAYCOUNT_PER_SECOND		70


#define DIST_TRANSLEVEL_NEAR	0x12000				
#define DIST_TRANSLEVEL_HIGH	0x48000				
#define DIST_TRANSLEVEL_MHIGH	0xC8000				
#define DIST_TRANSLEVEL_MID		0x120000			
#define DIST_TRANSLEVEL_LOW		0x320000			

#define DIST_TRANSLEVEL_DISCONNECT	0x320000			
#define DIST_TRANSLEVEL_CONNECT		0x120000			


#define	PARTY_GETTING_DIST		(18*64*18*64)

#define	PARTY_GETTING_DIST2		(17*64*17*64)


#define PLAYSERVER_SENDCOUNTER		(70*1)				



#define	ICE_FOOT_COUNT_MAX		20
#define	ICE_FOOT_LIFE_TIME		5000
#define	ICE_FOOT_ALPHA_STEP		(200.f / float(ICE_FOOT_LIFE_TIME))
struct SIceFootInfo
{
	int     Life;
	int     TypeNum;
	DWORD   dwPlayTime;
	POINT3D FootPos;
	POINT3D FootAngle;
};





#define DPAT_MAX		2048

struct smDPAT
{



	smDPAT	*lpTalkLink;


	smDPAT	*smDinaLink;
	smPAT3D	*Pat;

	char	szPatName[64];
	int		UseCount;
	DWORD	dwSpeedFindSum;

	smMODELINFO	*lpModelInfo;

	DWORD	LastUsedTime;
};


class smPATTERN
{
public:

	smPATTERN *BipPattern;

	smDPAT	DinaPat[DPAT_MAX];


	smPATTERN(void);
	~smPATTERN(void);


	void Init();
	int	Close();

	int GetNew();
	int FindFromName(char *szName);
	int FindFromCode(DWORD dwCode);
	smDPAT *LoadCharactor(char *szFileName);
	smDPAT *LoadBipPattern(char *szFileName);

};



#define	DISP_MODE_PATMAIN	1
#define	DISP_MODE_PATSUB	2



#define	DISP_MODE_PATTALK	4


#define CHAR_FRAME_MASK		0x00FFFFFF
#define CHAR_FRAME_SELSHIFT	24	

struct smCHARTOOL
{
	smOBJ3D *ObjBip;
	smPAT3D *PatTool;
	DWORD	dwItemCode;

	int	SizeMax, SizeMin;

	int		ColorBlink;
	short	sColors[4];
	DWORD	DispEffect;
	int		BlinkScale;
	int		EffectKind;

	int		TexMixCode, TexScroll;
};




#define SKILL_PLAY_EXTREME_SHIELD	1
#define SKILL_PLAY_MECHANIC_BOMB	2
#define	SKILL_PLAY_PHYSICAL_ABSORB	3
#define	SKILL_PLAY_POISON_ATTRIBUTE	4
#define	SKILL_PLAY_GREAT_SMASH		5
#define	SKILL_PLAY_MAXIMIZE			6
#define	SKILL_PLAY_AUTOMATION		7
#define	SKILL_PLAY_SPARK			8

#define	SKILL_PLAY_METAL_ARMOR		9
#define	SKILL_PLAY_GRAND_SMASH		10
#define	SKILL_PLAY_SPARK_SHIELD		11
#define	SKILL_PLAY_IMPULSION		12
#define	SKILL_PLAY_COMPULSION		13
#define	SKILL_PLAY_MAGNETIC_SPHERE  14
#define	SKILL_PLAY_METAL_GOLEM		15
#define SKILL_PLAY_PIKEWIND			16
#define SKILL_PLAY_CRITICAL_HIT		17
#define SKILL_PLAY_JUMPING_CRASH	18
#define SKILL_PLAY_GROUND_PIKE		19
#define SKILL_PLAY_TORNADO			20
#define SKILL_PLAY_EXPANSION		21
#define SKILL_PLAY_VENOM_SPEAR		22
#define SKILL_PLAY_BLADE_OF_BLAZE	23	
#define SKILL_PLAY_VANISH			23	
#define SKILL_PLAY_CHAIN_LANCE		24
#define SKILL_PLAY_ASSASSIN_EYE		25
#define SKILL_PLAY_CHARGING_STRIKE	26
#define SKILL_PLAY_VAGUE			27
#define SKILL_PLAY_SHADOW_MASTER	28
#define SKILL_PLAY_RAVING			29
#define SKILL_PLAY_IMPACT			30
#define SKILL_PLAY_TRIPLE_IMPACT	31
#define SKILL_PLAY_BRUTAL_SWING		32
#define SKILL_PLAY_ROAR				33
#define SKILL_PLAY_RAGEOF_ZECRAM	44
#define SKILL_PLAY_CONCENTRATION	45
#define SKILL_PLAY_AVANGING_CRASH	46
#define SKILL_PLAY_SWIFT_AXE		47
#define SKILL_PLAY_BONE_SMASH		48
#define SKILL_PLAY_DESTROYER		49
#define SKILL_PLAY_BERSERKER		50
#define SKILL_PLAY_CYCLONE_STRIKE	51
#define SKILL_PLAY_SCOUT_HAWK		52
#define SKILL_PLAY_WIND_ARROW		53
#define SKILL_PLAY_PERFECT_AIM		54
#define SKILL_PLAY_FALCON			55
#define SKILL_PLAY_ARROWOF_RAGE		56
#define SKILL_PLAY_AVALANCHE		57
#define SKILL_PLAY_ELEMENTAL_SHOT	58
#define SKILL_PLAY_GOLDEN_FALCON	59
#define SKILL_PLAY_BOMB_SHOT		60
#define SKILL_PLAY_PERFORATION		61
#define SKILL_PLAY_RECALL_WOLVERIN	62
#define SKILL_PLAY_PHOENIX_SHOT		63
#define SKILL_PLAY_FORCE_OF_NATURE	64
#define SKILL_PLAY_SWORD_BLAST		65
#define SKILL_PLAY_HOLY_BODY		66
#define SKILL_PLAY_DOUBLE_CRASH		67
#define SKILL_PLAY_HOLY_VALOR		68
#define SKILL_PLAY_BRANDISH			69
#define SKILL_PLAY_PIERCING			70
#define SKILL_PLAY_DRASTIC_SPIRIT	71
#define SKILL_PLAY_FLAME_BRANDISH	72
#define SKILL_PLAY_DIVINE_INHALATION	73
#define SKILL_PLAY_HOLY_INCANTATION		74
#define SKILL_PLAY_GRAND_CROSS			75
#define SKILL_PLAY_DIVINE_PIERCING		76
#define SKILL_PLAY_GODLY_SHIELD			77
#define SKILL_PLAY_GODS_BLESS			78
#define SKILL_PLAY_SWORD_OF_JUSTICE		79
#define SKILL_PLAY_SHIELD_STRIKE	80
#define SKILL_PLAY_FARINA			81
#define SKILL_PLAY_VIGOR_SPEAR		82
#define SKILL_PLAY_WINDY			83
#define SKILL_PLAY_TWIST_JAVELIN	84
#define SKILL_PLAY_SOUL_SUCKER		85
#define SKILL_PLAY_FIRE_JAVELIN		86
#define SKILL_PLAY_SPLIT_JAVELIN	90
#define SKILL_PLAY_TRIUMPH_OF_VALHALLA	91
#define SKILL_PLAY_LIGHTNING_JAVELIN	92
#define SKILL_PLAY_STORM_JAVELIN		93
#define SKILL_PLAY_HALL_OF_VALHALLA		94
#define SKILL_PLAY_X_RAGE				95
#define SKILL_PLAY_FROST_JAVELIN		96
#define SKILL_PLAY_VENGEANCE			97
#define SKILL_PLAY_HEALING			98
#define SKILL_PLAY_HOLY_BOLT		 99
#define SKILL_PLAY_MULTI_SPARK		 100
#define SKILL_PLAY_HOLY_MIND		 101
#define	SKILL_PLAY_DIVINE_LIGHTNING	 102
#define	SKILL_PLAY_HOLY_REFLECTION	 103
#define	SKILL_PLAY_GREAT_HEALING	 104
#define	SKILL_PLAY_VIGOR_BALL		 105
#define	SKILL_PLAY_RESURRECTION		 106
#define	SKILL_PLAY_EXTINCTION		 107
#define	SKILL_PLAY_VIRTUAL_LIFE		 108
#define	SKILL_PLAY_GLACIAL_SPIKE	 109
#define	SKILL_PLAY_REGENERATION_FIELD	110
#define	SKILL_PLAY_CHAIN_LIGHTNING	 112
#define	SKILL_PLAY_SUMMON_MUSPELL	 113
#define SKILL_PLAY_AGONY			 114
#define SKILL_PLAY_FIRE_BOLT		 115
#define SKILL_PLAY_ZENITH			 116
#define SKILL_PLAY_FIRE_BALL		 117
#define SKILL_PLAY_COLUMN_OF_WATER	 118
#define SKILL_PLAY_ENCHANT_WEAPON	 119
#define SKILL_PLAY_DEAD_RAY			 120
#define SKILL_PLAY_ENERGY_SHIELD	 121
#define SKILL_PLAY_DIASTROPHISM		 122
#define SKILL_PLAY_SPIRIT_ELEMENTAL	 123
#define SKILL_PLAY_DANCING_SWORD	 124
#define SKILL_PLAY_FIRE_ELEMENTAL	 125
#define SKILL_PLAY_FLAME_WAVE		 126
#define SKILL_PLAY_DISTORTION		 127
#define SKILL_PLAY_METEO			 128
#define SKILL_PLAY_DIVINE_PIERCING2	 129
#define SKILL_PLAY_DIVINE_PIERCING3	 130
#define SKILL_PLAY_D_HIT 		     131
#define SKILL_PLAY_P_DASH    		 132
#define SKILL_PLAY_M_BLOW        	 133
#define SKILL_PLAY_B_BERSERKER		 134
#define SKILL_PLAY_S_BREAKER         135
#define SKILL_PLAY_C_MOON     	     136
#define SKILL_PLAY_S_BLADE    	     137
#define SKILL_PLAY_H_BENEDIC     	 138
#define SKILL_PLAY_TALARIA           139
#define SKILL_PLAY_G_COUP    	     140
#define SKILL_PLAY_ARCURDA    	     141
#define SKILL_PLAY_S_FEAR        	 142
#define SKILL_PLAY_D_REAPER          143
#define SKILL_PLAY_F_SPEAR   	     144
#define SKILL_PLAY_AMPLIFIED         145
#define SKILL_PLAY_SS_ATTACK         146
#define SKILL_PLAY_SILRAPHIM         147
#define SKILL_PLAY_TENUS     	     148
#define SKILL_PLAY_IGNIS             149
#define SKILL_PLAY_ANIMA             150
#define SKILL_PLAY_S_IMPACT          151
#define SKILL_PLAY_P_ICE     	     152
#define SKILL_PLAY_RAMIEL            153
#define SKILL_PLAY_KRISHNA           154
#define SKILL_PLAY_LAND_M            155
#define SKILL_PLAY_H_SONIC     	     156
#define SKILL_PLAY_R_SMASH           157
#define SKILL_PLAY_P_ENHENCE         158
#define SKILL_PLAY_E_SHOT            159
#define SKILL_PLAY_S_ROPE     	     160
#define SKILL_PLAY_N_SPLASH          161
#define SKILL_PLAY_C_TRAP            162
#define SKILL_PLAY_STINGGER          163
#define SKILL_PLAY_R_HIT             164
#define SKILL_PLAY_D_MASTERY		 165
#define SKILL_PLAY_WISP       	 	 166
#define SKILL_PLAY_V_THRONE  		 167
#define SKILL_PLAY_ALAS      		 168
#define SKILL_PLAY_S_SHOCK		     169
#define SKILL_PLAY_A_MASTERY         170
#define SKILL_PLAY_S_SWORD       	 171
#define SKILL_PLAY_B_UP       		 172
#define SKILL_PLAY_INPES     		 173
#define SKILL_PLAY_BLIND         	 174
#define SKILL_PLAY_F_WIND            175
#define SKILL_PLAY_F_MASTERY         176
#define SKILL_PLAY_V_STAB       	 210     	 
#define SKILL_PLAY_P_SHADOW      	 178
#define SKILL_PLAY_DARKBOLT  		 179
#define SKILL_PLAY_DARKWAVE          180
#define SKILL_PLAY_CURSELAZY		 181
#define SKILL_PLAY_L_PEACE       	 182
#define SKILL_PLAY_S_FLARE    		 183
#define SKILL_PLAY_S_MANACLE     	 184
#define SKILL_PLAY_C_HUNT		     185
#define SKILL_PLAY_A_MIGAL         	 186
#define SKILL_PLAY_R_MAKER       	 187
#define SKILL_PLAY_L_GHOST       	 188
#define SKILL_PLAY_HAUNT     		 189
#define SKILL_PLAY_SCRATCH           190
#define SKILL_PLAY_R_KNIGHT          191
#define SKILL_PLAY_JUDGE         	 192
#define SKILL_PLAY_A_MIDRANDA        193
#define SKILL_PLAY_M_PRAY        	 194


#define SKILL_PLAY_BLESS_ABSORB			195
#define SKILL_PLAY_BLESS_DAMAGE			196
#define SKILL_PLAY_BLESS_EVADE			197
#define SKILL_PLAY_BLESS_SIEGE_ITEM		198

#define SKILL_PLAY_FIRE_CRYSTAL			199
#define SKILL_PLAY_LIGHTNING_CRYSTAL	200
#define SKILL_PLAY_ICE_CRYSTAL			201
#define SKILL_PLAY_CHAOSCARA_VAMP		202

#define SKILL_PLAY_PET_ATTACK		203
#define SKILL_PLAY_PET_ATTACK2		204

#define SKILL_PLAY_SOD_ITEM			205

#define SKILL_PLAY_SPEACIAL			206
#define	SKILL_PLAY_LOVELY_LIFE		207

#define	SKILL_EFFECT_FIREFLOWER		0x12000010



#define	SKILL_APPMASK_EXTREME_SHIELD		0x0001
#define	SKILL_APPMASK_PHYSICAL_ABSORB		0x0002
#define	SKILL_APPMASK_AUTOMATION			0x0004
#define	SKILL_APPMASK_ANGER					0x0008
#define	SKILL_APPMASK_SPARK_SHIELD			0x0010
#define	SKILL_APPMASK_GODLY_SHIELD			0x0020


#define	SKILL_APPMASK_HOLY_BODY				0x00010000







struct	ATTACK_DAMAGE_LIST
{
	DWORD	dwUserCode;
	int		DamageCount;
	int		Count;
};

#define	ATTACK_DAMAGE_LIST_MAX			100


class smCHAR
{
	DWORD Head;

public:

	Score score;

	int		DisplayFlag;

	int		DisplayTools;

	smSTAGE3D	*lpStage;
	DWORD		dwObjectSerial;
	int			AutoPlayer;

	smPAT3D	*Pattern;
	smPAT3D	*Pattern2;
	smPAT3D *AnimPattern;



	smPAT3D *TalkPattern;


	smDPAT  *lpDinaPattern;
	smDPAT  *lpDinaPattern2;

	smDPAT  *lpDinaLeftPattern;
	smDPAT  *lpDinaRightPattern;

	smCHARTOOL	HvLeftHand;
	smCHARTOOL	HvRightHand;

	smMATRIX	HvLeftHand_Matrix;
	smMATRIX	HvRightHand_Matrix;

	int		Rend_HvLeftHand;
	int		Rend_HvRightHand;


	smOBJ3D	*BackObjBip[6];
	smOBJ3D	*AttackObjBip;
	smOBJ3D	*ShieldObjBip;
	smOBJ3D	*ContactObjBip;
	smOBJ3D	*WaistObjBip[2];

	int		AttackToolRange;
	int		AttackAnger;
	int		AttackIce;


	int		Flag;
	int		pX, pY, pZ;
	int		AttackX, AttackY, AttackZ;
	int		PHeight;
	int		FallHeight;
	int		OnStageField;
	int		OnStageFieldState;

	int		PatLoading;

	int		PatWidth;
	int		PatHeight;

	int		PatSizeLevel;

	int		OverLapPosi;
	int		OverLapPosi2;
	smCHAR	*lpCharOverLap;

	POINT3D Posi;
	POINT3D Angle;

	int		MoveMode;
	int		MoveFlag;
	int		MoveCnt;
	int		tx, tz;
	int		TargetMoveCount;
	int		WaterHeight;

	DWORD	dwActionItemCode;
	DWORD	dwItemSetting;
	DWORD	dwActionItemTwoHand;

	short	wStickItems[4];


	int		ShootingMode;
	int		ShootingFlag;
	int		ShootingKind;
	POINT3D	ShootingPosi;

	POINT3D	ShootingAngle;
	int		ShootingCount;

	smCHAR	*chrAttackTarget;
	int		AttackCritcal;
	int		AttackCriticalCount;
	int		AttackExp;
	int		AttackSkil;
	int		AttackEffect;
	int		LastSkillParam;

	int		RecvExp;

	POINT3D	ptNextTarget;
	POINT3D	PosiAround;
	int		DistAroundDbl;
	int		TragetTraceMode;

	POINT3D	PosBeginMove;
	DWORD	PosBeginCount;

	DWORD	dwNextMotionCode;

	int		ChargingFlag;



	DWORD	TalkFrame;
	DWORD	TalkSoundSum;

	SMotionStEndInfo FrameInfo;


	int		action;
	DWORD	frame;
	int		FrameCnt;
	int		FrameStep;
	int		MoveSpeed;
	int		AttackSpeed;

	int		ActionPattern;

	DWORD	dwEventFrameExt[4];

	int		NearPlayCount;
	int		ReopenCount;
	int		AutoMoveStep;
	short	sMoveStepCount[2];

	int		Counter;
	int		FrameCounter;

	int		RendSucess;
	RECT	RendRect2D;
	POINT3D	RendPoint;
	int		FlagShow;


	char	szChatMessage[256];
	DWORD	dwChatMessageTimer;


	char	szTradeMessage[128];
	DWORD	dwTradeMsgCode;


	char	srTransBuff[TRANS_BUFF_SIZE];
	int		srTransBuffSize;


	int		ServerCode;

	smWINSOCK *TransSock;

	int		TransSendWait;
	int		TransLastSendCnt;
	int		TransLastSendTime;
	int		TransMinCnt;
	int		TransLevel;
	int		TransDelayMax;

	smPLAYBUFF	PlayBuff[PLAYBUFF_SIZE];
	int		PlayBuffCnt;
	int		PlayBuffPosi_End;

	DWORD	dwLastTransTime;
	int		LastPlayDataType;

	smCHAR_INFO		smCharInfo;
	smCHAR_MONSTER_INFO	smMonsterInfo;

	int		AnimDispMode;
	int		PatDispMode;

	int		MotionSelectFrame;

	smMODELINFO		*smMotionInfo;
	smMODELINFO		*smMotionInfo2;
	smMOTIONINFO	*MotionInfo;



	smMODELINFO		*lpTalkModelParent;
	smMOTIONINFO	*lpTalkMotionInfo;



	DWORD			OldMotionState;
	DWORD			dwTarget;


	rsPLAYINFO		*lpMasterPlayInfo;

	int						nCheckChar;


	rsPLAYINFO		*lpTargetPlayInfo;
	smCHAR			*lpTargetChar;
	int				AttackUserFlag;
	DWORD			dwTargetLockTime;

	DWORD			dwLinkObjectCode;
	rsPLAYINFO		*lpLinkPlayInfo;
	smCHAR			*lpLinkChar;


	rsPLAYINFO		*lpExpAttackPlayInfo;
	int				ExpAttackLife;
	DWORD			dwExpAttackTime;
	TRANS_ATTACKDATA AttackTrans;
	DWORD			dwAttackPlayTime;

	int				PotionLog;
	int				LevelLog;
	int				CriticalLog;

	int				EnableStateBar;
	int				MotionRecordCount;
	int				OpenStartPostion;

	int				DisplayAlpha;
	int				RendAlpha;
	int				RenderLatter;

	DWORD			dwDispAppSkill;
	DWORD			dwDispAppSkillMask;
	int				HideWeapon;
	int				MotionLoop;
	int				MotionLoopSpeed;
	int				MotionEvent;
	int				WeaponEffect;
	DWORD			dwWeaponEffectTime;
	int				EnchantEffect_Point;

	rsPLAYINFO		*lpCompulsionPlayInfo;
	DWORD			dwCompulsionTime;

	DWORD			dwAssassinEyeTime;
	int 			AssassinEyeParam;



	int				ClanInfoNum;
	DWORD			dwClanInfoTime;
	DWORD			dwClanManageBit;
	int				Clan_CastleMasterFlag;
	int             BlessCrown;

	void			*lpExt1;
	void			*lpExt2;
	void			*lpExt3;
	void			*lpExt4;

	POINT3D			HoSkillPos;
	int				HoSkillCode;
	int				HoSkillMode;

	int				PartyFlag;
	int				PartyParam;


	int				PlaySlowCount;
	int				PlaySlowSpeed;
	int				PlayStunCount;
	int				PlayStopCount;
	int             PlayStunType;
	short			PlayWisp[2];
	short			PlayHolyMind[2];
	short			PlayHolyPower[2];
	short			PlayPoison[2];
	short			PlayHolyIncantation[2];
	int				PlayVanish;
	int				PlayCurseQuest;
	int				PlayVague;
	int				PlayDistortion;
	int             PlayCurseLazy;
	int				PlayInvincible;

	BOOL			CheckFlagIce;


	int				DispPoison;

	DWORD			dwForceOfNatureTime;
	DWORD			dwHallOfValhallaTime;


	int				AttackSkillRange;

	int				EventAttackCount;
	DWORD			dwEventAttackParam;

	short			sAddColorEffect[4];
	int				DispLifeBar;

	DWORD			dwUpdateCharInfoTime;
	DWORD			dwLastRecvAttackTime;

	int				TryAttackCount;


	DWORD			dwForceOrbCode;
	DWORD			dwForceOrbTime;


	DWORD			dwLifeBoosterCode;
	DWORD			dwLifeBoosterTime;

	DWORD			dwManaBoosterCode;
	DWORD			dwManaBoosterTime;

	DWORD			dwStaminaBoosterCode;
	DWORD			dwStaminaBoosterTime;


	DWORD			dwSiegeItem_ScrollCode_Eternal;
	DWORD			dwSiegeItem_ScrollTime_Eternal;
	DWORD			dwSiegeItem_ScrollCode_Fatal;
	DWORD			dwSiegeItem_ScrollTime_Fatal;
	DWORD			dwSiegeItem_ScrollCode_Avert;
	DWORD			dwSiegeItem_ScrollTime_Avert;


	DWORD			dwSkillDelayCode;
	DWORD			dwSkillDelayTime;



	int				PkMode_CharState;
	int				DontMoveFlag;
	DWORD			dwClanCode;

	int				UseObject_VirtualLife;
	short			sObject_VirtualLife[2];
	short			sObject_DisplayLife[2];

	short			sBlessCastle_Damage[2];


	ATTACK_DAMAGE_LIST	*lpAttackDamageList;
	ATTACK_DAMAGE_LIST	*lpAttackDamageList_BlessCastle;

	int PlayCursePvP;
	int PlayGladiador;
	int PlayerGm;
	int PlayerBeta;
	int PlayerTopLevel;
	int BattleLevel;


	smCHAR();
	~smCHAR();
	void Init();
	int Close();

	int SetPosi(int x, int y, int z, int angX, int angY, int angZ);

	int SetTargetPosi(int x, int z);
	int SetTargetPosi2(int x, int z);


	int GetAttackPoint(int *nX, int *nY, int *nZ);

	int GetToolBipPoint(smCHARTOOL *ChrTool, int *nX, int *nY, int *nZ);


	int SetNextTarget(int x, int y, int z);

	int MoveAngle(int step);
	int MoveAngle2(int step);

	int ChangeMoveMode();

	int StartHandEffect(int Mode);

	int SetAction(int nAction);

	int ChangeMotion(int Motion, int DpMode = 0);



	int AutoChangeTalkMotion(int TalkModeType);



	int FindActionFromFrame(int sframe);


	int SetDinaPattern(smDPAT	*lpDPat);
	int SetDinaPattern2(smDPAT	*lpDPat);



	int SetTool(DWORD dwItemCode, int hvPosi);


	int SetPattern(smPAT3D *pat);

	int SetPattern2(smPAT3D *pat);


	int SavePlayBuff();


	int SavePlayBuff2();

	int Main();
	int Draw();
	int VirtualDraw();

	int ShootingMain();

	int	ChargingSkill();
	int EventAttack(int Flag = 0);

	int CheckShootingTest(smCHAR *lpChrTarget);

	int CheckShootingTest_LastAttackTime(smCHAR *lpChar);

	int	SetSmoking(int level);



	SIceFootInfo	m_IceFootInfo[ICE_FOOT_COUNT_MAX];

	void SetIceFoot(int TypeNum, DWORD dwPlayTime, int x, int z);
	int  DrawIceFoot(void);



	int DrawShadow();

	int DrawStateBar(int x, int y);

	int DrawStateBar2(int x, int y);

	int DrawChargingBar(int x, int y, int Charging, int ChargingMax);


	int DrawMotionBlurTool(smCHARTOOL *ChrTool);

	int DrawMotionBlur();


	int SetLoadPattern(char *szName);


	int MakePlayBuffFromPosi(int px, int py, int pz, int anX, int anY, int anZ, int act);

	int MakePlayBuffFromRecvData(smPLAYBUFF *StartBuff, smPLAYBUFF *EndBuff, int len);


	int MakeTransPlayData(char *lpTargetBuff, int SendTime, int pBuffStep = 1);


	int SetTransEffectItems(smEFFECT_ITEM *lpEffectItem);

	int SetTransEffectWeapon(smEFFECT_ITEM *lpEffectItem);


	int TransDelayCheck();

	int SetDistSendCnt(smCHAR *player);


	int SetMotionFromCode(DWORD MotionCode);


	int FindMotionCountFromCode(DWORD MotionCode);


	int FormSetPlayerInfo();


	int SetTransPlayerInfo(smTRNAS_PLAYERINFO *lpTransPlayerInfo);


	int SetTransPlayerInfoQuick(smTRNAS_PLAYERINFO_QUICK *lpTransPlayerInfo);


	DWORD GetAttackTrans_XorCode();

	int ResetAttackTrans();

	int XorAttackTrans();


	int PlayAttack(int EventFlag = 0);


	int RecvPlayData2(char *lpData);

	int RecvPlayData(smTHREADSOCK *RecvData);

	int SendPlayData(smCHAR *player);



	int SendCharInfo(smWINSOCK *lpsmsock);


	int SendPlayDataSock(smWINSOCK *lpsmsock, char *lpTransBuff, int ex, int ey, int ez);


	int SendTransAttack(smCHAR *lpChar, smWINSOCK *lpsmsock, int AttackCode, int Add_Damage = 0, int Resistance = 0);


	int PlayAttackFromPosi(int ex, int ey, int ez, int Dist, int attack = TRUE);


	int BeginSkill(int SkilCode, int Level, smCHAR *lpTarChar, int x, int y, int z);

	int EventSkill();

	int BeginSkill_Monster();

	int EventSkill_Monster();

	int BeginAttack_Monster();

	int EndSkill();

};




#define CHRMOTION_EXT		10

#define hvPOSI_RHAND	0x0001
#define hvPOSI_LHAND	0x0002


#define CHRMOTION_STATE_STAND		0x40
#define CHRMOTION_STATE_WALK		0x50
#define CHRMOTION_STATE_RUN			0x60
#define CHRMOTION_STATE_FALLDOWN	0x80

#define CHRMOTION_STATE_ATTACK		0x100
#define CHRMOTION_STATE_DAMAGE		0x110
#define CHRMOTION_STATE_DEAD		0x120
#define CHRMOTION_STATE_SOMETIME	0x130
#define CHRMOTION_STATE_EAT			0x140
#define CHRMOTION_STATE_SKILL		0x150

#define CHRMOTION_STATE_FALLSTAND	0x170
#define CHRMOTION_STATE_FALLDAMAGE	0x180

#define CHRMOTION_STATE_RESTART		0x200
#define CHRMOTION_STATE_WARP		0x210

#define CHRMOTION_STATE_YAHOO		0x220


#define CHRMOTION_STATE_HAMMER		0x300




#define CHRMOTION_STATE_TALK_AR			0x400
#define CHRMOTION_STATE_TALK_E			0x410
#define CHRMOTION_STATE_TALK_OH			0x420
#define CHRMOTION_STATE_TALK_EYE		0x430
#define CHRMOTION_STATE_TALK_BLANK		0
#define CHRMOTION_STATE_TALK_SMILE		0x440
#define CHRMOTION_STATE_TALK_GRUMBLE	0x450
#define CHRMOTION_STATE_TALK_SORROW		0x460
#define CHRMOTION_STATE_TALK_STARTLED	0x470
#define CHRMOTION_STATE_TALK_NATURE		0x480
#define CHRMOTION_STATE_TALK_SPECIAL	0x490




int smCHAR_SetCameraPosi(int x, int y, int z, int angX, int angY, int angZ);


extern CRITICAL_SECTION	cLoadSection;


int smDPAT_Delete(smDPAT *dPat);

int AnimObjectTree(smOBJ3D *tObj, int frame, int ax, int ay, int az);



int TestSetNewText(char *str);


int InitMotionBlur();


int GetSinItemNumFromCode(DWORD CODE);



int InitPatterns();

int ClosePatterns();

int SetLoadPattern(smCHAR *smChar, char *szName, POINT3D *Posi, POINT3D *Angle);

int SetLoadPattern(smCHAR *smChar, char *szName, char *szName2, POINT3D *Posi, POINT3D *Angle);

int	AddLoaderPattern(smCHAR *lpChar, char *szName, char *szName2 = 0);

int AddLoaderStage(smSTAGE3D *lpStage, char *szName);

int AnimObjectTree(smOBJ3D *tObj, int frame, int ax, int ay, int az);

class scITEM
{

public:
	DWORD	Head;

	int		DisplayFlag;

	int		Flag;
	int		pX, pY, pZ;

	char	szModelName[64];
	char	szName[64];

	DWORD     iClass;

	void	*lpStgArea;

	smPAT3D	*Pattern;
	smDPAT  *lpDinaPattern;

	int		PatLoading;

	int		ItemCode;

	DWORD	dwLastTransTime;

	int		ServerCode;

	POINT3D	RendPoint;


	POINT3D Posi;
	POINT3D Angle;


	scITEM();
	~scITEM();

	void Init();
	int Close();

	int SetPosi(int x, int y, int z);
	int SetTransItem(TRANS_ITEM *lpTransItem);

	int SetPattern(smPAT3D *pat);
	int SetPosi(int x, int y, int z, int angX, int angY, int angZ);
	int Draw();

};

int	AddLoaderItem(scITEM *lpItem, char *szName);

DWORD GetSpeedSum(const char *szName);

extern smPATTERN smBipPattern;
extern smPATTERN smPattern;



int	Ptect_IncAttackCount(int Flag);

DWORD Ptect_GetAttackCount();

extern int	SkillChargingFlag;

extern TRANS_SKIL_ATTACKDATA	Trans_SplashCharList;


extern int smCHAR_CameraX;
extern int smCHAR_CameraY;
extern int smCHAR_CameraZ;


extern int CastleBattleZone_LineZ;
extern int CastleBattleZone_DoorLineZ;
extern int CastleBattleZone_DoorLineX[2];
extern int CastleBattleZone_BridgeZ;
extern int CastleSoulFountain_Area[4];


int UpdateCastleMasterClan(DWORD dwMasterClan);

int SetClanMaster_Player(DWORD dwMasterClan);


#endif
