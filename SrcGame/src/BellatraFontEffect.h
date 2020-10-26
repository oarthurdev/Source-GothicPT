





#pragma once


#define	DMAX_BELLATRA_DDS_IMAGELIST				9
#define	DMAX_BELLATRA_TEX_IMAGELIST				21

#define DMAX_BL_MIN_EFFECT_INFO_SUBNUM			40
#define DMAX_BL_MIN_EFFECT_INFO					50

#define DMAX_BL_EFFECT_INFO_SUBNUM				20
#define DMAX_BL_EFFECT_INFO						40

#define DMAX_BL_MIN_EFFECT						20

#define DELAY_LOOP								-1
#define DELAY_STOP								-2


enum EBL_FontEffectType
{
	E_BL_ZERO = 0,
	E_BL_LODING = 1,
	E_BL_CHANGE_TRUE = 2,
	E_BL_CHANGE_FALSE = 3,
	E_BL_FONT_ROUND = 4,
	E_BL_FONT_COUNT_1 = 5,
	E_BL_FONT_COUNT_2 = 6,
	E_BL_FONT_COUNT_3 = 7,
	E_BL_FONT_COUNT_4 = 8,
	E_BL_FONT_COUNT_5 = 9,
	E_BL_FONT_COUNT_6 = 10,
	E_BL_FONT_COUNT_7 = 11,
	E_BL_FONT_COUNT_8 = 12,
	E_BL_FONT_START = 13,
	E_BL_FONT_STAGE = 14,
	E_BL_FONT_COMPLETE = 15,
	E_BL_FONT_FAIL = 16,
	E_BL_FONT_CON = 17,
	E_BL_QUAKE_SEAL = 18,
	E_BL_STUN_SEAL = 19,
	E_BL_FREEZE_SEAL = 20,
	E_BL_RABBIE_SEAL = 21,
	E_BL_STYGIAN_SEAL = 22,
	E_BL_GUARDIAN_SEAL = 23,
	E_BL_POINT_SEAL = 24,
	E_BL_FONT_QUAKE_SEAL = 25,
	E_BL_FONT_STUN_SEAL = 26,
	E_BL_FONT_FREEZE_SEAL = 27,
	E_BL_FONT_RABBIE_SEAL = 28,
	E_BL_FONT_STYGIAN_SEAL = 29,
	E_BL_FONT_GUARDIAN_SEAL = 30,
	E_BL_FONT_POINT_SEAL = 31,
};


enum EBL_IMAGE_TYPE
{
	E_BL_SURFACE = 0,
	E_BL_MAT_GROUP = 1,
	E_BL_FONT_MAT_GROUP = 2,
};



enum EBL_FontEffectPriority
{
	E_BL_PRIORITY_1 = 0,
	E_BL_PRIORITY_2 = 1,
	E_BL_PRIORITY_3 = 2,
};



enum EBL_EVENT_TYPE
{
	E_BL_NO_EVENT = 0,
	E_BL_EVENT_SCORE = 1,
};



struct  SBL_EventScore
{
	int  TeamNum;
	int  TeamMarkBuff[4];
	char szTeamPointBuff[4][32];

	int  EntryTeamNum;
	int  EntryTeamMarkBuff[2];
};



struct  SBL_MinFontEffectInfo
{
	EBL_IMAGE_TYPE	eBL_ImageType;
	int				MaxFrameNum;
	int				FrameMatBuff[DMAX_BL_MIN_EFFECT_INFO_SUBNUM];
	int				DelayTime[DMAX_BL_MIN_EFFECT_INFO_SUBNUM];
	POINT			PosMove[DMAX_BL_MIN_EFFECT_INFO_SUBNUM];
	SIZE			ScaleNum[DMAX_BL_MIN_EFFECT_INFO_SUBNUM];
	POINT3D		    Rot3d[DMAX_BL_MIN_EFFECT_INFO_SUBNUM];
	BYTE			BlendNum[DMAX_BL_MIN_EFFECT_INFO_SUBNUM];
};



struct  SBL_MinFontEffect
{
	SBL_MinFontEffectInfo	*lpBL_MinEffectInfo;
	EBL_FontEffectType		 eBL_Type;

	int						 Life;
	int						 FrameTime;
	int						 FrameNum;

	POINT					 Pos;
	SIZE					 Size;

	float					 fPos_x;
	float					 fPos_y;
	float					 fPosStep_x;
	float					 fPosStep_y;

	float					 fScale_x;
	float					 fScale_y;
	float					 fScaleStep_x;
	float					 fScaleStep_y;

	float					 fAng_x;
	float					 fAng_y;
	float					 fAng_z;
	float					 fAngStep_x;
	float					 fAngStep_y;
	float					 fAngStep_z;

	float					 fBlend;
	float				     fBlendStep;

	EBL_EVENT_TYPE			 eEventNum;
};



struct  SBL_FontEffectInfo
{
	EBL_FontEffectType		 eBL_Type;
	int						 Max_MinEffect_Info;
	int						 MinEffect_InfoBuff[DMAX_BL_EFFECT_INFO_SUBNUM];
	EBL_FontEffectPriority	 eMinEffect_PriorityBuff[DMAX_BL_EFFECT_INFO_SUBNUM];

	POINT					 Pos[DMAX_BL_EFFECT_INFO_SUBNUM];
	SIZE					 Size[DMAX_BL_EFFECT_INFO_SUBNUM];
};




struct  SBL_SetFontEffect
{
	EBL_FontEffectType		 eBL_Type;
	int						 Max_MinEffect_Info;
	EBL_FontEffectPriority	 eMinEffect_PriorityBuff[DMAX_BL_EFFECT_INFO_SUBNUM];
	SBL_MinFontEffect		*lpMinFontEffectPtrBuff[DMAX_BL_EFFECT_INFO_SUBNUM];
};




extern SBL_EventScore		g_EventScore;


extern void	CreateBellatraFontEffect(void);
extern void	DestroyBellatraFontEffect(void);
extern int  SetBellatraFontEffect(EBL_FontEffectType eBL_Type, SBL_SetFontEffect *lpCheckFontEffect = NULL, EBL_EVENT_TYPE eEventNum = E_BL_NO_EVENT);
extern void	MainBellatraFontEffect(void);
extern void	DrawBellatraFontEffect(void);
extern void	DrawBellatraBackToTexture2D(smTEXTUREHANDLE *hTexHandle, int X, int Y, smFMATRIX *lpMatrix, int HalfSize_x, int HalfSize_y, int Blend);





extern int CheckBellatraFontEffect(SBL_SetFontEffect *lpCheckFontEffect, int isKill = 0);
