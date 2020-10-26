#ifndef _HO_EFFECT_
#define _HO_EFFECT_

#include "smLib3d\smType.h"


#define		CLASS_NONE						10000
#define		CLASS_PRIMITIVE_BILLBOARD		20000
#define		CLASS_PAT						30000

#define		CLASS_ID_PARTICLE_DEST			40000

class HoEffectObject
{
protected:
	float WorldX, WorldY, WorldZ;
	float LocalX, LocalY, LocalZ;

	int		StartFlag;
	int		ClassID;


	int		SkillCode;


	HoEffectObject *Parent;


public:
	HoEffectObject();
	virtual ~HoEffectObject();
	virtual int Main();
	virtual int	Draw(int x, int y, int z, int ax, int ay, int az);

	void SetParentObject(HoEffectObject *parent)
	{
		Parent = parent;
	}

	BOOL		 GetState()
	{
		return StartFlag;
	}
	virtual void SetState(BOOL startFlag)
	{
		StartFlag = startFlag;
	}
	void		 SetClassID(int classID)
	{
		ClassID = classID;
	}
	int          GetClassID()
	{
		return ClassID;
	}

	virtual void TranslateWorld(int x, int y, int z)
	{
		WorldX = (float)x, WorldY = (float)y, WorldZ = (float)z;
	}
	virtual hoPOINT3D GetWorld()
	{
		hoPOINT3D temp;
		temp.x = WorldX;
		temp.y = WorldY;
		temp.z = WorldZ;

		return temp;
	}

	virtual void TranslateLocal(int x, int y, int z)
	{
		LocalX = (float)x, LocalY = (float)y, LocalZ = (float)z;
	}



	virtual void SetEffectEnd()
	{
		StartFlag = FALSE;
	}

	virtual POINT3D GetPos()
	{
		POINT3D pos;
		pos.x = int(WorldX + LocalX);
		pos.y = int(WorldY + LocalY);
		pos.z = int(WorldZ + LocalZ);

		return pos;
	}

	virtual int GetSkillCode()
	{
		return SkillCode;
	}

	virtual void SetSkillCode(int skillCode)
	{
		SkillCode = skillCode;
	}
};

#define MAX_VERTEX			   100
#define MAX_FACE			   40
#define	MAX_TEXLINK			   80


#define	RENDER_NONE				0
#define RENDER_BILLBOARD		1	
#define RENDER_BILLBOARD_PATH	2   



#define	RENDER_FACE				4
#define RENDER_FACEPATH			5   

#define	ANI_NONE				0
#define	ANI_ONE					100
#define	ANI_LOOP				300




class HoPrimitivePolygon : public HoEffectObject
{
public:
	HoPrimitivePolygon();
	~HoPrimitivePolygon();
protected:
	int TimeCount;
	int CurrentFrame;
	int SumCount;

	int	AniDataIndex;
	int	AniType;

	float CurrentBlendValue;
	float BlendStep;

	float SizeX;
	float SizeY;

	smSTAGE_VERTEX		Vertex[MAX_VERTEX];
	int					VertexCount;

	smSTAGE_FACE		Face[MAX_FACE];
	int					FaceCount;

	smTEXLINK			TexLink[MAX_TEXLINK];
	int					TexLinkCount;

	HoPhysicsObject		*Physics;

	virtual void Init();
	virtual	int	Main();
	virtual int Draw(int x, int y, int z, int ax, int ay, int az);


public:
	virtual int StartPathTri(POINT3D &currentPos, POINT3D &destPos, char *iniName);
	virtual int StartParticleTri(POINT3D &currentPos, POINT3D &velocity, char *intName);
	int	CreatePathFace();
};


#define PRIMITIVE_DEFAULT_RECT			0x00000001 
#define PRIMITIVE_DEFAULT_RECT_STRETCH  0x00000008 

#define	PRIMITIVE_PATH_RECT				0x00000002 
#define	PRIMITIVE_PATH_RECT_STRETCH		0x00000004 
#define PRIMITIVE_PATH_OBJECT			(PRIMITIVE_PATH_RECT | PRIMITIVE_PATH_RECT_STRETCH) 

#define MOVE_LINE						0x00000010 
#define MOVE_PARTICLE					0x00000020 
#define MOVE_ANGLE						0X00000040 
#define MOVE_OBJECT						(MOVE_LINE | MOVE_PARTICLE | MOVE_ANGLE) 

#define PRIMITIVE_DEFAULT_RECT_PARTICLE     (PRIMITIVE_DEFAULT_RECT | MOVE_PARTICLE)
#define PRIMITIVE_DEFAULT_RECT_LINE			(PRIMITIVE_DEFAULT_RECT | MOVE_LINE)
#define PRIMITIVE_PATH_RECT_PARTICLE 		(PRIMITIVE_PATH_RECT | MOVE_PARTICLE)		
#define PRIMITIVE_PATH_RECT_LINE		    (PRIMITIVE_PATH_RECT | MOVE_LINE)
#define PRIMITIVE_PATH_RECT_STRETCH_LINE	(PRIMITIVE_PATH_RECT_STRETCH | MOVE_LINE)	



class HoPrimitiveBillboard : public HoEffectObject
{
protected:
	int TimeCount;
	int CurrentFrame;

	int	AniDataIndex;
	int	AniType;

	float CurrentBlendValue;
	float BlendStep;

	float SizeWidth;
	float SizeHeight;
	float PutAngle;

	float SizeStep;
	float AngleStep;

	smFACE2D			Face2d;

	HoPhysicsObject		*Physics;
	POINT3D				DirectionVelocity;
	POINT3D				DirectionAngle;
	POINT3D				DirectionAngleStep;

	int					WorkState;

	hoPOINT3D			LocalStartPos;
protected:
	BOOL				AddFace2D(smFACE2D *face);
public:
	void	SetAniState(int aniType)
	{
		AniType = aniType;
	}
	HoPrimitiveBillboard();
	virtual ~HoPrimitiveBillboard();


	int MoveTo(int x, int y, int z);
	void SetDirectionVelocity(POINT3D velocity)
	{
		DirectionVelocity = velocity;
	}
	void SetWorkState(int workState)
	{
		WorkState = workState;
	}
	virtual void Init();
	virtual	int	Main();
	virtual int Draw(int x, int y, int z, int ax, int ay, int az);

	int StartBillRect(int x, int y, int z, char *iniName, int aniType, int workState = PRIMITIVE_DEFAULT_RECT);
	int StartBillRect(int x, int y, int z, int sizeX, int sizeY, char *iniName, int aniType);


	int StartParticlePath(POINT3D currentPos, POINT3D velocity, POINT size, char *iniName, int aniType, int workState = PRIMITIVE_PATH_RECT_PARTICLE);

	int StartDestPath(POINT3D worldPos, POINT3D localPos, POINT3D destPos, POINT size, char *iniName, int speed, int workState = PRIMITIVE_PATH_RECT_STRETCH_LINE);


	int StartPath(POINT3D currentPos, char *iniName, int aniType);


	void SetPhysics(HoPhysicsObject *object, int primitiveInfo)
	{
		if(object == NULL)
			return;

		Physics = object;
		if(Physics->GetWorkId() == MOVE_PARTICLE)
		{
			WorkState = MOVE_PARTICLE;
			WorkState |= primitiveInfo;
		}
		else if(Physics->GetWorkId() == MOVE_LINE)
		{
			WorkState = MOVE_LINE;
			WorkState |= primitiveInfo;
		}
	}


	void SetSize(POINT size)
	{
		SizeWidth = (float)size.x;
		SizeHeight = (float)size.y;
		Face2d.width = (int)SizeWidth << FLOATNS;
		Face2d.height = (int)SizeHeight << FLOATNS;
	}
};


class HoEffectCircleLine : public HoPrimitiveBillboard
{
public:
	HoEffectCircleLine();
	~HoEffectCircleLine();

	float DxVelocity;
	float DyVelocity;

	float Step;

	int		Start(int x, int y, int z, int sizeX, int sizeY, char *iniName, int aniType);
	int		Main();

	int		CircleTimeCount;
};


class HoEffectTracker : public HoEffectObject
{
public:
	HoEffectTracker();
	~HoEffectTracker();



	int	liveCount;
	BOOL	liveFlag;
	int sparkCount;
	int IMP_SHOT2_liveCount;
	int IMP_SHOT3_liveCount;





	POINT3D DestPos;

	float Vx;
	float Vy;
	float Vz;


	int Start(POINT3D currentPos, POINT3D destPos, int skillCode, HoEffectObject *effectObj = NULL, int level = 1);
	int Main();

	int Level;
	HoEffectObject *EffectObj;
};


#define MAX_2DVERTEX	40
#define STATE_NONE		0
#define STATE_UP		1
#define STATE_DOWN		2
class HoEtc2dPrimitive : public HoEffectObject
{
protected:
	int	TimeCount;
	int CurrentFrame;
	int SumCount;

	int AniDataIndex;

	int CurrentBlendValue;
	int BlendStep;

	D3DTLVERTEX TLVertex[MAX_2DVERTEX];
	int VertexCount;

	HoAnimDataMgr	AnimationData;

	int WorkState;
	int Velocity;

public:
	HoEtc2dPrimitive();
	~HoEtc2dPrimitive();
	int		Load();

	int		StartUp(int x, int y);
	int		StartDown();

	virtual int Init();
	virtual	int	Main();
	virtual int Draw();
};

class HoEtcPrimitiveBillboardMove : public HoPrimitiveBillboard
{
public:
	HoEtcPrimitiveBillboardMove();
	~HoEtcPrimitiveBillboardMove();

private:
	smRENDFACE			*AddRendFace;

	float Step;
public:
	int		MoveState;
	float	TranslateMoveX;
	float	TranslateMoveY;

	int		PrimitiveMoveCount;
	int		PrimitiveStopCount;
public:
	int Draw(int x, int y, int z, int ax, int ay, int az);
	int Start(int x, int y, int z, int sizeX, int sizeY, char *iniName, int aniType);
	int Main();
};



class HoEffectPat : public HoEffectObject
{
protected:
	smPAT3D		*PatObj;

	int		CurrentFrame;
	int		FrameStep;
	int		BlendStep;

	POINT3D Angle;

	int			AniType;

public:
	int		AnimationEnd;
	HoEffectPat();
	~HoEffectPat();


protected:
	void	Init();
public:
	int StartAni(int x, int y, int z, int angleX, int angleY, int angleZ, smPAT3D *pat, int aniType = ANI_ONE);

	int Main();
	int Draw(int x, int y, int z, int ax, int ay, int az);
	void SetBlendStep(int blendStep)
	{
		BlendStep = blendStep;
	}
};


class HoEffectPatGetPos : public HoEffectObject
{

protected:
	smPAT3D *PatObj;

	int CurrentFrame;
	int FrameStep;
	int BlendStep;

	POINT3D Angle;

	smOBJ3D *ObjBip;
public:
	int	AnimationEnd;
	HoEffectPatGetPos();
	~HoEffectPatGetPos();
	void Init();

	int StartAni(int x, int y, int z, int angleX, int angleY, int angleZ, smPAT3D *pat, char *searchObjName = NULL);
	int Main();
	int Draw(int x, int y, int z, int ax, int ay, int az);

};


class HoEffectPatHawk : public HoEffectPat
{

public:
	HoEffectPatHawk();
	~HoEffectPatHawk();

	int Loop;
	smOBJ3D *ObjBip;
	int AngleY;
	POINT3D HawkPos;



	smCHAR *Character;
public:
	void SetEffectEnd()
	{
		Loop = 1;
	};
	int Draw(int x, int y, int z, int ax, int ay, int az);
	int Main();
	int StartAni(int x, int y, int z, int angleX, int angleY, int angleZ, smPAT3D *patBone, smPAT3D *pat, smCHAR *character, int loop = 0);
};





enum
{
	FALCON_GATE_START, FALCON_START, FALCON_KEEP_ON, FALCON_ATTACK, FALCON_TURN_START, FALCON_TURN_PROCESS, FALCON_TURN_END
};
class HoEffectPatFalcon : public HoEffectPat
{
public:
	HoEffectPatFalcon();
	~HoEffectPatFalcon();

	smOBJ3D *ObjBip;
	smCHAR *Character;

	int WorkState;

	POINT3D AttackAngle;
	POINT3D AttackDest;

	int		pDelay;
	int		pCounter;
	int		pEndCounter;
	short	pAttackDamage[2];


	D3DXVECTOR3	ParticleGlowPos;
	int		ParticleGlowID;
	int		ParticleStarID;


public:
	int Draw(int x, int y, int z, int ax, int ay, int az);
	int Main();
	int StartAni(int x, int y, int z, int angleX, int angleY, int angleZ, smPAT3D *patBone, smPAT3D *patAni, smCHAR *character, int SkillPoint);
	int StartGoldenFalconAni(int x, int y, int z, int angleX, int angleY, int angleZ, smPAT3D *patBone, smPAT3D *patAni, smCHAR *character, int liveCount);

};




#define MAX_EFFECTOBJECT_BUFFER		500
#define MAX_TIMEOBJECT_BUFFER		100

#define MAX_MATERIAL_NUM			100
#define MAX_OBJECT_NUM				100


#define EFFECT_NORMAL_HIT1		100
#define EFFECT_NORMAL_HIT2		150

#define EFFECT_CRITICAL_HIT1    200
#define EFFECT_CRITICAL_HIT2    210

#define EFFECT_LEVELUP1		    300

#define EFFECT_ROUND_IMPACT     400
#define EFFECT_GAME_START1		500

#define EFFECT_POTION1			600
#define EFFECT_POTION2			700
#define EFFECT_POTION3			800
#define EFFECT_BROKEN1			850

#define EFFECT_DAMAGE1			900
#define EFFECT_GAS1				1000
#define EFFECT_DUST1			1100
#define EFFECT_LIGHT1			1200
#define EFFECT_BANDI1			1300
#define EFFECT_GATE1			1350

#define EFFECT_TEST1			1400
#define EFFECT_TEST2			2000
#define EFFECT_PARTICLE_BOW1	1500
#define EFFECT_PARTICLE_BOW2	2520
#define EFFECT_FIRE_HIT1		3000
#define EFFECT_FIRE_HIT2		3200
#define EFFECT_RETURN1			3500
#define EFFECT_MECHANICBOMB_DUST1 4000
#define EFFECT_SHIELD1_PARTICLE   5000
#define EFFECT_AGING			  5001

#define SKILL_NONE							500
#define SKILL_HOMING						5500
#define SKILL_METEO							6000
#define SKILL_UP1							6500



#define SKILL_TORNADO2     		6800
#define SKILL_GREAT_SMASH2     	6810



#define SKILL_TORNADO3     		6801
#define SKILL_GREAT_SMASH3     	6811




#define EFFECT_PHYSICAL_ABSORB_DAMAGE		7000
#define SKILL_SHIELD1						20000 
#define SKILL_SHIELD2						20001 
#define EFFECT_SHIELD2_PARTICLE				20002






#define EFFECT_SPARK1						24000
#define EFFECT_SPARK2						24001


#define MONSTER_PIGON_POWER1				29000
#define MONSTER_PIGON_PARTICLE1				29001
#define MONSTER_PIGON_SHOT1					29002

#define MONSTER_PIGON_POWER2				29003
#define MONSTER_PIGON_PARTICLE2				29004


#define MONSTER_PIGON_PARTICLE1_BLH				29005




#define MONSTER_WEB_SHOT1					35000
#define MONSTER_WEB_HIT1					30000

#define MONSTER_IMP_SHOT1					35100
#define MONSTER_IMP_HIT1					35200

#define MONSTER_IMP_SHOT2					35101	
#define MONSTER_IMP_HIT2					35201

#define MONSTER_IMP_SHOT3					35102	
#define MONSTER_IMP_HIT3					35102	


#define MONSTER_MEPHIT_SHOT1				35300
#define MONSTER_MEPHIT_HIT1					35400
#define MONSTER_HEADER_CUTTER_HIT1			35411
#define MONSTER_HULK_HIT1					35422
#define MONSTER_FURY_MAGIC1					35623

#define MONSTER_OMICRON_HIT1				35626
#define MONSTER_DMACHINE_PARTICLE1			35628
#define MONSTER_DMACHINE_MISSILE1			35630
#define MONSTER_DMACHINE_MISSILE2			35631

#define MONSTER_STYGIANLORD_SHOT1			35633
#define MONSTER_STYGIANLORD_PARTICLE1		35634
#define MONSTER_STYGIANLORD_MAGIC1			35635

#define MONSTER_SERQBUS_SHOT1				70000
#define MONSTER_SERQBUS_SHOT2               70001
#define MONSTER_SERQBUS_SHOT3               70002

#define MONSTER_SERQBUS_MAGIC1              70003
#define MONSTER_SERQBUS_MAGIC2              70004
#define MONSTER_SERQBUS_MAGIC3              70005

#define MONSTER_SERQBUS_MAGIC_ATTACK1       70006
#define MONSTER_SERQBUS_MAGIC_ATTACK2       70007
#define MONSTER_SERQBUS_MAGIC_ATTACK3       70008


#define MONSTER_SERQBUS_STATE1				70009
#define MONSTER_SERQBUS_STATE2				70010
#define MONSTER_SERQBUS_STATE3              70011


#define MONSTER_SHADOW_SHOT1                35639


#define MONSTER_MEPHIT_SHOT2				35301	
#define MONSTER_MEPHIT_HIT2					35401



#define MONSTER_FORZENMIST_SHOT1				60601	
#define MONSTER_FORZENMIST_HIT1					60611

#define MONSTER_FORZENMIST_SHOT2				60602	
#define MONSTER_FORZENMIST_HIT2					60612

#define EFFECT_ICE_HIT1					60650
#define EFFECT_ICE_HIT2					60651
#define MONSTER_COLDEYE_SKILL			60680

#define MONSTER_VALENTO_HIT1			60690
#define MONSTER_VALENTO_HIT2			60691

#define MONSTER_POSION_STATE1				60700		

#define MONSTER_MUMMY_SHOT				60710		

#define MONSTER_TURTLECANON_SHOT				60720		

#define EFFECT_FIRE_CRACKER				60730		
#define EFFECT_FIRE_CRACKER_HIT				60731		


#define EFFECT_CHIMERA_SKILL				60740		
#define EFFECT_BLOODKNIGHT_SKILL				60741		




#define ARROW_OF_RAGE_POWER1				35401
#define SKILL_ARROW_OF_RAGE_END				40000 

#define SKILL_RAGE_OF_ZECRAM_POWER1			44000
#define SKILL_RAGE_OF_ZECRAM_HIT1			44001
#define SKILL_RAGE_OF_ZECRAM_HIT2			44002

#define SKILL_AVALANCHE_PARTICLE			50001
#define EFFECT_ARROW_OF_RAGE_HIT1			53000

#define EFFECT_GROUND_PIKE_PARTICLE			54000
#define EFFECT_STUN1						55000
#define EFFECT_FALCON_GATE1					56000


#define EFFECT_TERRAIN_WAVE					60000


#define SKILL_METALARMOR					61000



class HoEffectLight : public HoEffectObject
{
public:
	HoEffectLight();
	~HoEffectLight();
	int Start(int x, int y, int z, int r, int g, int b, int a, int power, int decPower, int endPowerUp = 0);
private:

	int R;
	int G;
	int B;
	int A;
	int Power;
	int DecPower;
	int EndPowerUp;

public:
	int Init();
	int Main();
};



class HoEffectTime
{
public:
	HoEffectTime();
	~HoEffectTime();

	void Init();
	void Main();
	void Draw(int x, int y, int z, int ax, int ay, int az);
	void Start();
	bool AddObject(HoEffectObject *object, int startTime);
	BOOL GetState()
	{
		return StartFlag;
	}
private:

	HoEffectObject	*TimeObjectBuffer[MAX_TIMEOBJECT_BUFFER];
	int				StartTime[MAX_TIMEOBJECT_BUFFER];

	int				DelayTimeCount;
	BOOL			StartFlag;
};


struct hoChrInfoObject
{
	HoEffectObject *object;
	smCHAR *character;
};


class HoEffectMgr
{
public:
	HoEffectMgr();
	~HoEffectMgr();
private:

	HoEffectObject		*EffectZSortBuffer[MAX_EFFECTOBJECT_BUFFER];
	HoEffectObject		*EffectObjectBuffer[MAX_EFFECTOBJECT_BUFFER];

	HoEffectTime		EffectTimeObjectBuffer[MAX_EFFECTOBJECT_BUFFER];
	int					MaterialNum[MAX_MATERIAL_NUM];

	smPAT3D				*PatObj[MAX_OBJECT_NUM];
	int					PatAnimationEnd[MAX_OBJECT_NUM];

	smPAT3D				*PatMissile;

	int					EmptyObjectBufferIndex();
	int					EmptyZSortBufferIndex();
	int					EmptyTimeObjectBufferIndex();

	int					StartBillRectPrimitive(int x, int y, int z, int sizeX, int sizeY, char *iniName);

public:

public:
	int					StartBillRectPrimitive(int x, int y, int z, char *iniName);


public:
	void	Init();
	int		Main();
	int		Draw(int x, int y, int z, int ax, int ay, int az);
	int		Start(int x, int y, int z, int effectType, int level = 1);
	int		Start(int x, int y, int z, int sizeX, int sizeY, int effectType);
	int     Start(int x, int y, int z, int r, int g, int b, int a, int effectType);

	int		Start(int x, int y, int z, int effectType, smCHAR *character);

	int		Start(int x, int y, int z, int effectType, HoEffectObject *parent);

	int		StartSkillDest(int x, int y, int z, int destX, int destY, int destZ, int skillType = SKILL_NONE, int level = 0);
	int		StartSkill(int x, int y, int z, int angleX, int angleY, int angleZ, int skillType = SKILL_NONE, int level = 0);
	int		StartSkill(int x, int y, int z, int angleX, int angleY, int angleZ, smCHAR *character, int skillType = SKILL_NONE, int level = 0);

	int		StartMonsterDest(POINT3D current, POINT3D dest, int effectType);
	int		StartMonsterDest(POINT3D current, POINT3D dest, POINT3D angle, int effectType);
	int		StartMonster(POINT3D current, int effecctType);
	int     StartMonster(POINT3D pos, POINT3D angle, int effectType);


	int		StartChrState(smCHAR *chr, int effectType, int liveCount);

};


class HoNewEffectChrMove : public HoEffectObject
{
public:
	HoNewEffectChrMove();
	~HoNewEffectChrMove();

	smCHAR  *Character;
	int		PartEmitterID;

	int		LiveCount;
	int     TimeCount;
	BOOL    MyCharacterFlag;
	BOOL    FlagShow;
	int		Main();
	int     Start(smCHAR *chr, int skillCode, int liveCount);
	int     StopEffect();
};


class HoNewEffectMove : public HoEffectObject
{
public:
	HoNewEffectMove();
	~HoNewEffectMove();
private:
	smPAT3D		*PatObj;
	int			CurrentFrame;
	POINT3D		DestPos;
	POINT3D     Angle;
	int			PartEmitterID;
	int			PartEmitterIDExt;

	D3DXVECTOR3   Velocity;

	bool		ParticleStartFlag;
	smOBJ3D     *ObjBip;

	float       Length;
	POINT3D     OldPos;
	BOOL		BlendFlag;

	int         BlendStep;
	int			BlendCount;

	int			TimeCount;
public:
	int Start(POINT3D curPos, POINT3D destPos, smPAT3D *pat, int skillCode);
	int Start(POINT3D curPos, POINT3D destPos, int skillCode);
	int Start(POINT3D curPos, POINT3D destPos, POINT3D angle, smPAT3D *pat, int skillCode);

	int Main();
	int Draw(int x, int y, int z, int ax, int ay, int az);

};

extern int InitEffect();
extern int StartTerrainEffect(int x, int y, int z, int effectType);

extern int StartEffect(int x, int y, int z, int sizeX, int sizeY, int effectType);
extern int StartEffect(int x, int y, int z, int effecType, int level = 1);
extern int StartEffect(int x, int y, int z, char *iniName);
extern int StartEffect(int x, int y, int z, int effectType, smCHAR *character);
extern int StartChildEffect(int x, int y, int z, int effectType, HoEffectObject *parent = NULL);


extern int StartEffect(int x, int y, int z, int r, int g, int b, int a, int type);
extern int StartSkillDest(int x, int y, int z, int destX, int destY, int destZ, int skillType, int level = 0);
extern int StartSkill(int x, int y, int z, int angleX, int angleY, int angleZ, int skillType, int level = 0);
extern int StartSkill(int x, int y, int z, int angleX, int angleY, int angleZ, smCHAR *character, int skillType, int level);
extern int StartTracker(POINT3D currentPos, POINT3D destPos);


extern int StartEffectMonsterDest(int x, int y, int z, int destX, int destY, int destZ, int effectType);
extern int StartEffectMonsterDest(int x, int y, int z, int destX, int destY, int destZ, int angleX, int angleY, int angleZ, int effectType);
extern int StartEffectMonster(int x, int y, int z, int effectType);
extern int StartEffectMonster(int x, int y, int z, int angleX, int angleY, int angleZ, int effectType);
extern int StartEffectMonster(int x, int y, int z, int effectType, int liveCount);
extern int StartEffectChrState(smCHAR *chr, int effectType, int liveCount);



extern int MainEffect();
extern int DrawEffect(int x, int y, int z, int ax, int ay, int az);

extern int DrawMenuFlame();
extern int StartMenuFlame(int x, int y);

extern HoAnimDataMgr	AnimDataMgr;
extern HoPhysicsMgr		PhysicsMgr;
extern HoEffectMgr		EffectMgr;

#define CHR_IN_EFFECT_OBJECT_MAX	100
extern hoChrInfoObject ChrInEffectObject[CHR_IN_EFFECT_OBJECT_MAX];
#endif
