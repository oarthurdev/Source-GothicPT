#pragma once

#include "smPacket.h"

#define MAP_SIZE			256
#define MAP_CLIP			0xFF	
#define MAX_CELL			4096
#define MAPTEXTURE_SIZE		64
#define RAYCLIP_ANGLE		ANGLE_45+ANGLE_1

#define RAYCLIP_ADD			5

#define ANGCLIP				ANGLE_MASK
#define CLIP_OUT			-32767
#define SMFLAG_NONE			0xFFFFFFFF




#define	fONE		256
#define FLOATNS		8
#define FLOATDS		8


#define wfONE		32768
#define wFLOATS		15
#define wSHIFT_FLOAT	(wFLOATS-FLOATNS)


#define SizeMAPCELL			64			
#define ShiftMAPCELL_MULT	6		    
#define ShiftMAPCELL_DIV	6		    

#define SHIFT_MAPHEIGHT		(ShiftMAPCELL_MULT-3)
#define AND_SizeMAPCELL		(SizeMAPCELL-1)
#define OR_SizeMAPCELL		(0xFFFFFFFF-AND_SizeMAPCELL)


#define DEFAULT_CONTRAST			300
#define DEFAULT_BRIGHT				160




#define SMCLIP_NEARZ		0x00000001
#define SMCLIP_FARZ			0x00000002
#define SMCLIP_LEFT			0x00000004
#define SMCLIP_RIGHT		0x00000008
#define SMCLIP_TOP			0x00000010
#define SMCLIP_BOTTOM		0x00000020
#define SMCLIP_TEXTURE		0x00000040
#define SMCLIP_DISPLAYOUT	0x00000080
#define SMCLIP_DISPLAYIN	0x00000100

#define SMCLIP_VIEWPORT		( SMCLIP_NEARZ | SMCLIP_FARZ | SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM | SMCLIP_DISPLAYOUT )


#define SMC_A				3
#define SMC_R				2
#define SMC_G				1
#define SMC_B				0








#include "..\\nettype.h"
#ifdef _W_SERVER
#define MAX_TEXTURE		8000
#else
#define MAX_TEXTURE		5000
#endif







struct smMATRIX
{
	int _11, _12, _13, _14;
	int _21, _22, _23, _24;
	int _31, _32, _33, _34;
	int _41, _42, _43, _44;
};


struct smEMATRIX
{
	int _11, _12, _13, _14;
	int _21, _22, _23, _24;
	int _31, _32, _33, _34;
	int _41, _42, _43, _44;
};



struct smDMATRIX
{
	double _11, _12, _13, _14;
	double _21, _22, _23, _24;
	double _31, _32, _33, _34;
	double _41, _42, _43, _44;
};


struct smFMATRIX
{
	float _11, _12, _13, _14;
	float _21, _22, _23, _24;
	float _31, _32, _33, _34;
	float _41, _42, _43, _44;
};

struct smRGB
{
	DWORD r, g, b;
};
struct smLIGHTLEVEL
{
	BYTE		cr, cg, cb;
	BYTE		sr, sg, sb;
};

struct smLIGHT3D
{
	int type;
	int x, y, z;
	int Range;
	short r, g, b;

};

#define	smLIGHT_TYPE_NIGHT		0x00001
#define	smLIGHT_TYPE_LENS		0x00002
#define	smLIGHT_TYPE_PULSE2		0x00004				


#define	SMLIGHT_TYPE_OBJ		0x00008

#define	smLIGHT_TYPE_DYNAMIC	0x80000



struct POINT3D
{
	int x, y, z;
};

struct TPOINT3D
{
	int x, y, z;
	float u, v;
	float zb;
	BYTE	bCol[4];
	BYTE	bSpe[4];
};

struct smLINE3D
{
	POINT3D sp;
	POINT3D ep;
};

struct smTRECT
{
	float u0, v0;
	float u1, v1;
	float u2, v2;
	float u3, v3;
};

struct smTPOINT
{
	int u, v;
};

struct smFTPOINT
{
	float u, v;
};




struct smTEXLINK
{
	float	u[3], v[3];
	DWORD	*hTexture;
	smTEXLINK	*NextTex;
};

struct smVERTEX
{
	int x, y, z;
	int nx, ny, nz;
};

struct smFACE
{
	WORD v[4];
	smFTPOINT t[3];

	smTEXLINK	*lpTexLink;

};

struct smTM_ROT
{
	int frame;
	float x, y, z, w;
};
struct smDTM_ROT
{
	int frame;
	double x, y, z, w;
};



struct smTM_POS
{
	int   frame;
	float x, y, z;
};


struct smTM_SCALE
{
	int frame;
	int x, y, z;
};



struct smRENDVERTEX
{


	int		tx, ty, tz;
	DWORD	ClipStatus;

	float	xy[2];
	float	zb;
	float	rhw;



	int		nx, ny, nz;


	short	sLight[4];

	BYTE	bCol[4];
	BYTE	bSpe[4];

	void	*lpSourceVertex;
};


struct smRENDFACE
{

	smRENDVERTEX	*lpRendVertex[3];
	DWORD			Matrial;
	smTEXLINK		*lpTexLink;
	DWORD			ClipStatus;
	smRENDFACE		*NexRendFace;

};


struct smRENDLIGHT
{
	int type;
	int x, y, z;
	int rx, ry, rz;
	int Range;
	int dRange;
	int r, g, b, a;
};



struct smRENDMATRIAL
{

	int RegistRendList;


	DWORD		MatrialCounter;
	smRENDFACE	*StartFace;
	smRENDFACE	*LastLinkFace;


	DWORD		TexClip_MatrialCounter;
	smRENDFACE	*TexClip_StartFace;
	smRENDFACE	*TexClip_LastLinkFace;
};


struct smTEXRECT
{
	float	left, right;
	float	top, bottom;
};


struct smFACE2D
{
	int			x, y, z;
	int			width, height;
	smTEXRECT	TexRect;
	int			MatNum;
	int			Transparency;
	int			r, g, b;
};



struct smSTAGE_VERTEX
{
	DWORD			sum;
	smRENDVERTEX	*lpRendVertex;


	int				x, y, z;



	short			sDef_Color[4];

};



struct smSTAGE_FACE
{
	DWORD	sum;
	int		CalcSum;

	WORD	Vertex[4];

	smTEXLINK	*lpTexLink;

	short	VectNormal[4];

};




#define		CONFIG_KEY_MONSTER_MAX		5


struct smCONFIG
{
	char	szFile_BackGround[2][64];
	char	szFile_Menu[64];
	char	szFile_Player[64];
	POINT	Posi_Player;
	char	szFile_Enemy[64];
	POINT	Posi_Enemy;

	char	szFile_Stage[64];
	POINT	Posi_Stage;
	char	szFile_StageObject[100][64];
	int		StageObjCnt;

	int		IsStageAniObject[100];

	int		MapBright;
	int		MapContrast;

	POINT3D	MapLightVector;

	struct PowerUser
	{
		AccountTypes sec;
		bool auth;

		PowerUser()
		{
			sec = AccountTypes::SEC_PLAYER;
			auth = false;
		}		
	};
	
	PowerUser security;

	char	szCmdOpenMonster[CONFIG_KEY_MONSTER_MAX][32];
	int		CmdMonsterCount;

	smCONFIG()
	{
		ZeroMemory(szFile_BackGround, sizeof(szFile_BackGround));
		ZeroMemory(szFile_Menu, sizeof(szFile_Menu));
		ZeroMemory(szFile_Player, sizeof(szFile_Player));
		Posi_Player.x = 0;
		Posi_Player.y = 0;
		ZeroMemory(szFile_Enemy, sizeof(szFile_Enemy));
		Posi_Enemy.x = 0;
		Posi_Enemy.y = 0;
		ZeroMemory(szFile_Stage, sizeof(szFile_Stage));
		Posi_Stage.x = 0;
		Posi_Stage.y = 0;
		ZeroMemory(szFile_StageObject, sizeof(szFile_StageObject));
		StageObjCnt = 0;
		ZeroMemory(IsStageAniObject, sizeof(IsStageAniObject));
		MapBright = DEFAULT_BRIGHT;
		MapContrast = DEFAULT_CONTRAST;
		MapLightVector.x = fONE;
		MapLightVector.y = -fONE;
		MapLightVector.z = fONE / 2;
		security.sec = AccountTypes::SEC_PLAYER;
		security.auth = false;
		ZeroMemory(IsStageAniObject, sizeof(szCmdOpenMonster));
		CmdMonsterCount = 0;
	}

	void setSecurity(AccountTypes security)
	{
		this->security.sec = security;
	}

	AccountTypes getSecurity() const
	{
		return this->security.sec;
	}

	void setSecurityAuth(bool value)
	{
		this->security.auth = value;
	}

	bool isSecurityAuth() const
	{
		return this->security.auth;
	}
};




#define MOTION_LIST_MAX			32
#define MOTION_INFO_MAX			512




//#define	MOTION_TOOL_MAX			52
#define	MOTION_TOOL_MAX			104


#define	MOTION_SKIL_MAX			8







#define NPC_MOTION_INFO_MAX		 30
#define TALK_MOTION_INFO_MAX	 30




#define TALK_MOTION_FILE_MAX	 2
#define TALK_MOTION_FILE		 0
#define FACIAL_MOTION_FILE		 1


struct smMOTIONINFO
{
	DWORD	State;



	DWORD	MotionKeyWord_1;
	DWORD	StartFrame;
	DWORD	MotionKeyWord_2;
	DWORD	EndFrame;


	DWORD	EventFrame[4];

	int		ItemCodeCount;
	BYTE	ItemCodeList[MOTION_TOOL_MAX];
	DWORD	dwJobCodeBit;
	BYTE	SkillCodeList[MOTION_SKIL_MAX];


	int		MapPosition;

	DWORD	Repeat;
	CHAR	KeyCode;
	int		MotionFrame;
};

struct _MODELGROUP
{
	int ModelNameCnt;
	char szModelName[4][16];
};

struct smMODELINFO
{
	char szModelFile[64];
	char szMotionFile[64];
	char szSubModelFile[64];

	_MODELGROUP	HighModel;
	_MODELGROUP	DefaultModel;
	_MODELGROUP	LowModel;

	smMOTIONINFO MotionInfo[MOTION_INFO_MAX];
	DWORD MotionCount;

	DWORD FileTypeKeyWord;
	DWORD LinkFileKeyWord;

	char szLinkFile[64];

	char szTalkLinkFile[64];
	char szTalkMotionFile[64];
	smMOTIONINFO TalkMotionInfo[TALK_MOTION_INFO_MAX];
	DWORD TalkMotionCount;

	int	NpcMotionRate[NPC_MOTION_INFO_MAX];
	int	NpcMotionRateCnt[100];

	int	TalkMotionRate[TALK_MOTION_INFO_MAX];
	int	TalkMotionRateCnt[TALK_MOTION_FILE_MAX][100];

};




extern BYTE VRKeyBuff[256];





struct smTEXPOINT
{
	float	u, v;
	DWORD	hTexture;
};

struct smFCOLOR
{
	float	r, g, b;
};


#define smTEXSTATE_FS_NONE		0
#define smTEXSTATE_FS_FORMX		1
#define smTEXSTATE_FS_FORMY		2
#define smTEXSTATE_FS_FORMZ		3
#define smTEXSTATE_FS_SCROLL	4
#define smTEXSTATE_FS_REFLEX	5

#define smTEXSTATE_FS_SCROLL2	6
#define smTEXSTATE_FS_SCROLL3	7
#define smTEXSTATE_FS_SCROLL4	8
#define smTEXSTATE_FS_SCROLL5	9
#define smTEXSTATE_FS_SCROLL6	10
#define smTEXSTATE_FS_SCROLL7	11
#define smTEXSTATE_FS_SCROLL8	12
#define smTEXSTATE_FS_SCROLL9	13
#define smTEXSTATE_FS_SCROLL10	14



#define smTEXSTATE_FS_SCROLLSLOW1	15
#define smTEXSTATE_FS_SCROLLSLOW2	16
#define smTEXSTATE_FS_SCROLLSLOW3	17
#define smTEXSTATE_FS_SCROLLSLOW4	18




struct smTEXTUREHANDLE
{
	char Name[64];
	char NameA[64];
	DRZTEXTURE2 lpD3DTexture;
	DIRECTDRAWSURFACE lpDDSurface;

	DRZTEXTURE2 lpD3DTextureLarge;
	DIRECTDRAWSURFACE lpDDSSysMemory;

	int Width, Height;
	int UsedTime;

	int UseCounter;

	int	MapOpacity;

	DWORD	TexSwapMode;

	smTEXTUREHANDLE *TexChild;

	DWORD loadingFailed;
};



struct ASE_MATERIAL
{
	int			Regist;
	int			RegistNum;

	int			TextureCounter;
	DWORD		UseCounter;

	smFCOLOR	Diffuse;
	float		Transparency;
	float		SelfIllum;
	DWORD		TwoSide;
	DWORD		ScriptState;



	char		BITMAP[8][64];


	DWORD		BitmapStateState[8];
	DWORD		BitmapFormState[8];



	char		MAP_OPACITY[64];


	float		UVW_U_OFFSET[8];
	float		UVW_V_OFFSET[8];
	float		UVW_U_TILING[8];
	float		UVW_V_TILING[8];
	float		UVW_ANGLE[8];

	int			SubPoint;

	int			BlendType;

};




struct smMATERIAL
{
	DWORD			InUse;
	DWORD			TextureCounter;
	smTEXTUREHANDLE	*smTexture[8];

	DWORD			TextureStageState[8];
	DWORD			TextureFormState[8];
	int				ReformTexture;

	int				MapOpacity;


	DWORD			TextureType;
	DWORD			BlendType;

	DWORD			Shade;
	DWORD			TwoSide;
	DWORD			SerialNum;

	smFCOLOR		Diffuse;
	float			Transparency;
	float			SelfIllum;

	int				TextureSwap;
	int				MatFrame;
	int				TextureClip;


	int				UseState;
	int				MeshState;


	int				WindMeshBottom;


	smTEXTUREHANDLE	*smAnimTexture[32];
	DWORD			AnimTexCounter;
	DWORD			FrameMask;
	DWORD			Shift_FrameSpeed;
	DWORD			AnimationFrame;


};




#define SMTEX_TYPE_MULTIMIX		0x0000
#define SMTEX_TYPE_ANIMATION	0x0001



#define SMTEX_AUTOANIMATION		0x100




#define SMMAT_STAT_CHECK_FACE	0x00000001


#define SMMAT_BLEND_NONE		0x00
#define SMMAT_BLEND_ALPHA		0x01
#define SMMAT_BLEND_COLOR		0x02
#define SMMAT_BLEND_SHADOW		0x03
#define SMMAT_BLEND_LAMP		0x04
#define SMMAT_BLEND_ADDCOLOR	0x05
#define SMMAT_BLEND_INVSHADOW	0x06








struct smASE_LIGHT
{

	int	x, y, z;
	int r, g, b;

	int Size;
	int Range;
	int	Dist;
	int Type;
};



struct eCAMERA_TRACE
{
	int x, y, z;
	int tx, ty, tz;

	smEMATRIX	eRotMatrix;
	int AngX, AngY;
};


