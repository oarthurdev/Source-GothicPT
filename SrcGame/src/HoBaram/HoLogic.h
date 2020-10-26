#ifndef _HO_LOGIC_H_
#define _HO_LOGIC_H_





#define PAT_PROCESS		2000
#define PAT_END			3000


#define MAX_BLUR_LIST		15
#define	MAX_BLUR_VERTEX		300
#define	MAX_BLUR_FACE		200
#define	MAX_BLUR_TEXLINK	200



class HoEffectPatDest : public HoEffectPat
{
private:
	int Level;
	int DestX, DestY, DestZ;
	int DestAngleX, DestAngleY, DestAngleZ;


	float VelocityY;
	int   Step;

	HoPrimitiveBillboard PrimitiveBillBoard;

	int SkillType;
	int WorkState;



	BOOL BlurStartFlag;
	POINT3D	PosList[MAX_BLUR_LIST];
	int		PosListCount;

	smSTAGE_VERTEX		Vertex[MAX_BLUR_VERTEX];
	int					VertexCount;

	smSTAGE_FACE		Face[MAX_BLUR_FACE];
	int					FaceCount;

	smTEXLINK			TexLink[MAX_BLUR_TEXLINK];
	int					TexLinkCount;
	int					SumCount;

	int					CreatePathFace();

	int					AniDataIndex;
	int					BlurBlendValue;
	int					BlurTimeCount;
	int					BlurCurrentFrame;
	int					SizeWidth;


public:
	HoEffectPatDest();
	~HoEffectPatDest();

public:
	int Draw(int x, int y, int z, int ax, int ay, int az);
	int Main();


	int StartDest(POINT3D currentPos, POINT3D destPos, smPAT3D *pat, int SkillType, int level = 0);
	int StartAni(int x, int y, int z, int angleX, int angleY, int angleZ, int destX, int destY, int destZ, smPAT3D *pat, char *addEffectName = NULL);
	int EventEnd();



	int StartBlur(char *iniName);
	int MainBlur();
	int	DrawBlur(int x, int y, int z, int ax, int ay, int az);
};





#define		POS_LIST_MAX	15

#define		MAX_SHIELD_VERTEX	300
#define		MAX_SHIELD_FACE		200
#define		MAX_SHIELD_TEXLINK	200

class HoEffectShield : public HoEffectObject
{
public:
	HoEffectShield();
	~HoEffectShield();

	HoPrimitiveBillboard	BackBillBoard;
	HoEffectPat				UnderPat;

	int AniDataIndex;
	int	CurrentFrame;
	int TimeCount;
	int BlendStep;
	int CurrentBlendValue;

	smFACE2D			Face2d;

	int SizeWidth;
	int SizeHeight;

	POINT3D DirectionAngle;
	POINT3D	PosList[POS_LIST_MAX];
	int		PosListCount;

	smSTAGE_VERTEX		Vertex[MAX_SHIELD_VERTEX];
	int					VertexCount;

	smSTAGE_FACE		Face[MAX_SHIELD_FACE];
	int					FaceCount;

	smTEXLINK			TexLink[MAX_SHIELD_TEXLINK];
	int					TexLinkCount;

	int					SumCount;

	smCHAR				*Character;

	int					EndCount;

	int					ShieldType;



protected:

	int	CreatePathFace();
public:
	void Init();
	int Draw(int x, int y, int z, int ax, int ay, int az);
	int Main();
	int Start(int x, int y, int z, int shieldType, int angle, int circleRadius, smCHAR *character);

	void SetUnderPat(smPAT3D *pat, int aniEnd);
};



class HoEffectPower : public HoEffectObject
{
public:
	HoEffectPower();
	~HoEffectPower();

	int  Skill_n;

private:
	HoPrimitiveBillboard	BackBillBoard;

	HoPrimitiveBillboard	ParticleBillBoard[10];

	smCHAR					*Character;
	int						AniDataIndex;


public:
	int Draw(int x, int y, int z, int ax, int ay, int az);
	int Main();
	int Start(int x, int y, int z, int sw, int aniType = ANI_ONE, smCHAR *character = NULL);
};




class HoEffectHitLine : public HoEffectObject
{
public:
	HoEffectHitLine();
	~HoEffectHitLine();




	int  Skill_n;
	int  cntM, cnt0;
	int delayCount;


	POINT3D DestPos;
	float Vx;
	float Vy;
	float Vz;



private:

	POINT3D DirectionAngle;
	POINT3D	PosList[POS_LIST_MAX];
	int		PosListCount;

	smSTAGE_VERTEX		Vertex[MAX_SHIELD_VERTEX];
	int					VertexCount;

	smSTAGE_FACE		Face[MAX_SHIELD_FACE];
	int					FaceCount;

	smTEXLINK			TexLink[MAX_SHIELD_TEXLINK];
	int					TexLinkCount;
	int					SumCount;

	int					CreatePathFace();

	int					AniDataIndex;
	int					CurrentBlendValue;
	int					TimeCount;
	int					CurrentFrame;

	int					SizeHeight;

public:
	int Draw(int x, int y, int z, int ax, int ay, int az);
	int Main();


	int Start(int x, int y, int z, int destX, int destY, int destZ, int sw);
};



#define		STUN_POS_LIST_MAX	10


class HoEffectStun : public HoEffectObject
{
public:
	HoEffectStun();
	~HoEffectStun();


private:

	POINT3D DirectionAngle;
	POINT3D	PosList[POS_LIST_MAX];
	int		PosListCount;

	smSTAGE_VERTEX		Vertex[MAX_SHIELD_VERTEX];
	int					VertexCount;

	smSTAGE_FACE		Face[MAX_SHIELD_FACE];
	int					FaceCount;

	smTEXLINK			TexLink[MAX_SHIELD_TEXLINK];
	int					TexLinkCount;
	int					SumCount;

	int					CreatePathFace();

	int					AniDataIndex;
	int					CurrentBlendValue;
	int					TimeCount;
	int					CurrentFrame;

	int					SizeHeight;

	smCHAR				*Character;

public:
	int Draw(int x, int y, int z, int ax, int ay, int az);
	int Main();
	int Start(int worldX, int worldY, int worldZ, smCHAR *character);
};



#endif
