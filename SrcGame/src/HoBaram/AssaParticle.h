

#ifndef _ASSA_PARTICLE_
#define _ASSA_PARTICLE_

#define ASSA_SHOT_LASER		100
#define ASSA_SHOT_SPARK		120
#define ASSA_SHOT_WATER		130
#define ASSA_SHOT_FIRE		140
#define ASSA_SHOT_ICE		150
#define ASSA_SHOT_BIGFIRE1	160
#define ASSA_SHOT_SPARK1    170


#define ASSA_SHOT_LASER2	180
#define ASSA_SHOT_LASER3	190
#define ASSA_SHOT_PARKSPARK		200


class cASSAPARTSHOT : public cASSAEFFECT
{
public:
	cASSAPARTSHOT();
	~cASSAPARTSHOT();

	void Main();
	void Draw(POINT3D *pPosi, POINT3D *pAngle);
	void Start(POINT3D *pCurPosi, POINT3D *pDestPosi, int type);
	void Start(POINT3D *pCurPosi, POINT3D *pDestPosi, cASSAEFFECT *pEffect, int type = ASSA_SHOT_WATER);
	void Start(smCHAR *pChar, POINT3D *pDestPosi, int type);
	void SetChainLighting(smCHAR **pCharList, int count);
public:

	int		WidthStep;
	int		State;
	int		EffectType;
	int		TimeCount;

	cASSAEFFECT  *Effect;
	int			 PartNum;
	D3DXVECTOR3	Velocity;


	POINT3D     LocalPos;
	POINT3D   LocalAngle;
	POINT3D    DestAngle;
	POINT3D    ShootingAngle;

	bool	ChainLightingFlag;
	smCHAR *CharList[20];
	int		CharCount;
};



class cASSAPARTSPARK : public cASSAEFFECT
{
public:
	cASSAPARTSPARK();
	~cASSAPARTSPARK();

	void Main();
	void Start(POINT3D *pCurPosi);
	void Start(POINT3D *pCurPosi, char *fileName);

	void Draw(POINT3D *pPosi, POINT3D *pAngle);

public:
	D3DXVECTOR3 Velocity;
};

struct WEAPON_PART_POS
{
	POINT3D pos[4];
	int		posCount;
};

#define	ENCHANT_WEAPON					80
#define ENCHANT_WEAPON_FIRE				100
#define ENCHANT_WEAPON_ICE				200
#define ENCHANT_WEAPON_LIGHT			300
#define ENCHANT_MEMBER_JIN				400
#define IMPULSION_LIGHT                 500

#define HOLY_ACTION						700
#define DRASTIC_ACTION					750
#define HOLY_VALOR_JANG					800
#define HOLY_VALOR_MEMBER				900
#define DRASTIC_SPIRIT_JANG				1000
#define DRASTIC_SPIRIT_MEMBER			1100
#define WINDY_ACTION					1200
#define HOLY_MIND_ATTACK				1300

#define STOP_PART_FLAG					1399
#define AGING_BODY						1400
#define FURY_EYE1						1401
#define CLAN_MONSTER_PART1				1402
#define PIGON_HAND_FIRE					1403
#define CLASS_UP_PART1					1404
#define IRON_MONSTER_CHAINGOLEM1		1405

#define IRON_MONSTER_RUNIC_GUARDIAN_HAND1 1406
#define SHELLTOM_WEAPON					  1407


#define ICE_MONSTER_CHAOSKARA_STAFF		1408
#define ICE_MONSTER_VALENTO_BODY		1409
#define MONSTER_SPIDERTROOPER			1410
#define EFFECT_FIRECRACKER				1411
#define MONSTER_KELVEZU_CIRCLE			1412




class cASSAChar : public cASSAEFFECT
{
public:
	cASSAChar();
	~cASSAChar();

	void Main();
	void Start(smCHAR *pChar, int code, int maxTime = 0, float delay = 0.f);
	void StopEffect();

	int			PartNum;
	int			PartNumExt1;

	int			EnchantPartNum[3];
	DWORD       ItemCode;
	bool        MyCharacterFlag;

	int			State;

	int			EffectType;
	bool        FadeStopFlag;

	BOOL        FlagShow;
};


class CShootingSkillEffect : public cASSAEFFECT
{
public:
	CShootingSkillEffect();
	~CShootingSkillEffect();
	void Start(POINT3D *pCur, smCHAR *destChar, D3DXVECTOR3 *velocity, int delay, char *pEffectName1, char *pEffectName2, unsigned int SkillCode);
	void Main();
private:
	int			ParticleID;
	BOOL		ParticleIDExt1;
	D3DXVECTOR3 Velocity;
	smCHAR *    DestChar;
	POINT3D     Pos;
	int         dwSkillCode;
};


class CKeepSkillEffect : public cASSAEFFECT
{
public:
	CKeepSkillEffect();
	~CKeepSkillEffect();
	void Start(char *FileName, smCHAR *character, int liveCount, unsigned int dwSkillCode);
	void Main();
private:
	int			ParticleID;
	BOOL		MyCharacterFlag;
	BOOL		EndFlag;
};


class cASSAItem : public cASSAEFFECT
{
public:
	cASSAItem();
	~cASSAItem();

	void Main();
	void Start(smCHAR *character, int code);
	int  PartNum;
	void StopEffect();
	bool        MyCharacterFlag;
	BOOL        FlagShow;
	int			EffectType;

};


class cAssaTracePatMeshParticle : public cASSAEFFECT
{
public:
	cAssaTracePatMeshParticle();
	~cAssaTracePatMeshParticle();

	void Main();
	void Start(smCHAR *character, smPAT3D *pat, smOBJ3D *searchObj, char *particleName, int liveTime = 10);

private:
	BOOL	FlagShow;
	int		PartNum;
	smPAT3D *PatObj;
	smOBJ3D *SearchObj;
	BOOL	AttachFlag;

	int		LiveTime;
	int		TimeCount;
};





class cAssaTraceCharMeshParticle : public cASSAEFFECT
{
public:
	cAssaTraceCharMeshParticle();
	~cAssaTraceCharMeshParticle();

	void Main();
	void Start(smCHAR *character, char *meshName, char *particleName, bool attachFlag = true, int liveTime = -1);

	void SetPosLength(int length)
	{
		Length = length;
	}

	void SetScale(float scale)
	{
		Scale = scale;
	}


private:
	BOOL		FlagShow;
	int			PartNum;
	smOBJ3D		*SearchObj;

	BOOL		MyCharacterFlag;
	bool		AttachFlag;

	int			Length;
	float		Scale;

	int			LiveTime;
	int			TimeCount;

};




class cAssaTraceMeshDestParticle : public cASSAEFFECT
{
public:
	cAssaTraceMeshDestParticle();
	~cAssaTraceMeshDestParticle();

	void Main();
	void Draw(POINT3D *pPosi, POINT3D *pAngle);
	void Start(smPAT3D *pat, char *meshName, POINT3D *curPos, POINT3D *destPos, char *particleName);

	void SetRenderMesh(BOOL flag)
	{
		MeshRenderFlag = flag;
	}

private:
	int	PartNum;
	smOBJ3D *SearchObj;
	smPAT3D *PatMesh;
	int CurFrame;

	POINT3D LocalPos;

	BOOL	MeshRenderFlag;
};



class cAssaMotionBlur : public cASSAEFFECT
{
public:
	cAssaMotionBlur();
	~cAssaMotionBlur();

	void Main();
	void Draw(POINT3D *pPosi, POINT3D *pAngle);

	void Start(smCHAR *character, char *meshName1, char *meshName2, int liveTime = 140);
	void SetDelay(int startDelay)
	{
		StartDelay = startDelay;
	}
	void SetAlpha(int alpha)
	{
		Alpha = alpha;
	}
	smOBJ3D		*SearchObj1;
	smOBJ3D     *SearchObj2;
	BOOL		MyCharacterFlag;

	int			LiveTime;
	int			TimeCount;

	int			StartDelay;
	float		Scale;

	int			Alpha;
	void SetScale(float scale)
	{
		Scale = scale;
	}

};


class cAssaTwoPointAni : public cASSAFACE
{
public:
	cAssaTwoPointAni();
	~cAssaTwoPointAni();

	void Main();


	void Start(smCHAR *character, char *meshName1, char *meshName2);

	smOBJ3D		*SearchObj1;
	smOBJ3D     *SearchObj2;
	BOOL		MyCharacterFlag;

	int			LiveTime;
	int			TimeCount;

	int			StartDelay;
};


class AssaSkill3Concentration : public cASSAEFFECT
{
public:
	AssaSkill3Concentration();
	~AssaSkill3Concentration();
	void Start(smCHAR* character, int liveCount);
	void Main();
private:
	int			ParticleID;
	BOOL		MyCharacterFlag;
	BOOL		EndFlag;
};


class AssaSkill3SwiftAxe : public cASSAEFFECT
{
public:
	AssaSkill3SwiftAxe();
	~AssaSkill3SwiftAxe();
	void Start(smCHAR* character, int liveCount);
	void Main();

private:
	int			ParticleID;
	BOOL		MyCharacterFlag;
	BOOL		EndFlag;

};

class AssaSkillWeaponMotionBlur : public cASSAEFFECT
{
public:
	AssaSkillWeaponMotionBlur();
	~AssaSkillWeaponMotionBlur();

	void Main();
	void Draw(POINT3D *pPosi, POINT3D *pAngle);

	void Start(smCHAR *character, int liveTime = 140);
	void SetDelay(int startDelay)
	{
		StartDelay = startDelay;
	}
	BOOL		MyCharacterFlag;

	int			LiveTime;
	int			TimeCount;

	int			StartDelay;
};




class AssaSkill3BombShotExplision : public cASSAEFFECT
{
public:
	AssaSkill3BombShotExplision();
	~AssaSkill3BombShotExplision();
	void Start(POINT3D *pPosi, D3DXVECTOR3 *Velocity, D3DXVECTOR3 *Gravity);
	void Start(POINT3D *pPosi, D3DXVECTOR3 *Velocity, D3DXVECTOR3 *Gravity, char *particleName);

	void Main();

private:

	D3DXVECTOR3   Pos;
	D3DXVECTOR3	Velocity;
	D3DXVECTOR3   Gravity;

	int			ParticleID;
};

enum
{
	ELEMENTAL_FIRE = 0,
	ELEMENTAL_LIGHTING
};

class AssaSkill3ElementalShot : public cASSAEFFECT
{
public:
	AssaSkill3ElementalShot();
	~AssaSkill3ElementalShot();


	void Start(POINT3D* pCur, POINT3D* pDest, int type);
	void Main();

private:

	int			ParticleID;
	POINT3D		ShootingAngle;
	int			Type;

};

class AssaSkill3BombShot : public cASSAEFFECT
{
public:
	AssaSkill3BombShot();
	~AssaSkill3BombShot();


	void Draw(POINT3D *pPosi, POINT3D *pAngle);
	void Start(POINT3D* pCur, POINT3D* pDest);
	void Main();

private:
	int			ParticleID;
	POINT3D     ShootingAngle;
	smPAT3D     *PatMesh;
};

class AssaSkill3Perforation : public cASSAEFFECT
{
public:
	AssaSkill3Perforation();
	~AssaSkill3Perforation();

	void Start(POINT3D* pCur, POINT3D* pDest);
	void Draw(POINT3D *pPosi, POINT3D *pAngle);

	void Main();
private:
	D3DXVECTOR3	Velocity;
	POINT3D		ShootingAngle;
	int			State;
	int			ParticleID;

	smPAT3D*	PatMesh;
	int			State1TimeCount;
};



class AssaSkill3MetalArmor : public cASSAEFFECT
{
public:
	AssaSkill3MetalArmor();
	~AssaSkill3MetalArmor();
	void Start(smCHAR* character, int liveCount);
	void Main();
	void Draw(POINT3D *pPosi, POINT3D *pAngle);

private:
	int			ParticleID;
	BOOL		MyCharacterFlag;

	smPAT3D*	PatMesh;
	int			CurrentFrame;

	BOOL		EndFlag;
	int			MeshBlendStep;
};

class AssaSkill3SparkShield : public cASSAEFFECT
{
public:
	AssaSkill3SparkShield();
	~AssaSkill3SparkShield();

	void Start(smCHAR* character, int liveCount);
	void Main();
private:
	int		ParticleID;
	BOOL	MyCharacterFlag;
	BOOL    EndFlag;
	smOBJ3D		*SearchObj;
};



class AssaSkill3Vanish : public cASSAEFFECT
{
public:
	AssaSkill3Vanish();
	~AssaSkill3Vanish();
	void Start(smCHAR* character);
	void Main();

private:
	int			ParticleID;
	BOOL		MyCharacterFlag;
	BOOL		EndFlag;
};







class AssaSkill3EnergyShield : public cASSAEFFECT
{
public:
	AssaSkill3EnergyShield();
	~AssaSkill3EnergyShield();

	void Start(smCHAR* character, int liveCount);
	void Main();
	void Draw(POINT3D *pPosi, POINT3D *pAngle);
private:
	int		ParticleID;
	BOOL	MyCharacterFlag;
	BOOL    EndFlag;

	smPAT3D	*PatMesh;
	int		CurrentFrame;
	int		MeshBlendStep;
};

class AssaSkill3EnergyShieldDefence : public cASSAEFFECT
{
public:
	AssaSkill3EnergyShieldDefence();
	~AssaSkill3EnergyShieldDefence();

	void Start(smCHAR* character);
	void Main();
private:
	int		ParticleID;
	BOOL	MyCharacterFlag;
	BOOL    EndFlag;
};


class AssaSkill3SpiritElemental : public cASSAEFFECT
{
public:
	AssaSkill3SpiritElemental();
	~AssaSkill3SpiritElemental();
	void Start(smCHAR* character, int liveCount);
	void Main();
	void Draw(POINT3D *pPosi, POINT3D *pAngle);


private:
	smPAT3D		*PatMesh;
	int			ParticleID;

	int			MaxFrame;
	int			CurrentFrame;
	smOBJ3D		*ObjBip;



	int		ParticleIDExt1;
	BOOL	MyCharacterFlag;
	BOOL    EndFlag;
};

enum
{
	DANCING_MAINTAIN = 1,
	DANCING_ATTACK_START1,
	DANCING_ATTACK_START2,
	DANCING_ATTACK_PROCESS,
	DANCING_ATTACK_HIT,
	DANCING_RETURN
};

class AssaSkill3DancingSword : public cASSAEFFECT
{
public:
	AssaSkill3DancingSword();
	~AssaSkill3DancingSword();
	void Start(smCHAR* character, int type, int liveCount, int level);
	void Main();
	void Draw(POINT3D *pPosi, POINT3D *pAngle);

private:
	smPAT3D		*PatMesh;
	int			ParticleID1;
	int			ParticleID2;
	int			ParticleID3;
	int			ParticleID4;

	smOBJ3D		*ObjBip1;
	smOBJ3D		*ObjBip2;
	smOBJ3D		*ObjBip3;
	smOBJ3D		*ObjBip4;

	BOOL		MyCharacterFlag;
	int			CurrentFrame;

	int			State;

	POINT3D		AttackDest;
	POINT3D		AttackLocalPosi;
	POINT3D		AttackAngle;

	float		DetectionLength;


	int			Type;
	BOOL        EndFlag;

	int			AttackTime;
	smCHAR		*AttackMonster;

	int			FrameSpeed;
	BOOL		FrameSpeedFlag;
};




class AssaSkill3DivineInhalation : public cASSAEFFECT
{
public:
	AssaSkill3DivineInhalation();
	~AssaSkill3DivineInhalation();

	void Start(smCHAR* character, int liveCount);
	void Main();
private:
	int		ParticleID;
	BOOL	MyCharacterFlag;
	BOOL    EndFlag;
	smOBJ3D		*SearchObj;
};



class AssaSkill3HolyIncantationShot : public cASSAEFFECT
{
public:
	AssaSkill3HolyIncantationShot();
	~AssaSkill3HolyIncantationShot();


	void Start(smCHAR *character);
	void Main();

private:
	int		ParticleID;
	BOOL	MyCharacterFlag;
};



class AssaSkill3HolyIncantationPart : public cASSAEFFECT
{
public:
	AssaSkill3HolyIncantationPart();
	~AssaSkill3HolyIncantationPart();

	void Start(smCHAR* character, int liveCount);
	void Main();

private:
	int			ParticleID;
	BOOL		MyCharacterFlag;
	BOOL		EndFlag;
};




class AssaSkill3HolyIncantationPartHand : public cASSAEFFECT
{
public:
	AssaSkill3HolyIncantationPartHand();
	~AssaSkill3HolyIncantationPartHand();

	void Start(smCHAR* character, int liveCount);
	void Main();
private:
	int		ParticleID;
	int		ParticleIDExt;
	BOOL	MyCharacterFlag;
	BOOL    EndFlag;
	smOBJ3D		*SearchObj;
};

class AssaSkill3FlameBrandish : public cASSAEFFECT
{
public:
	AssaSkill3FlameBrandish();
	~AssaSkill3FlameBrandish();
	void Start(smCHAR* character);
	void Main();
	void Draw(POINT3D *pPosi, POINT3D *pAngle);


private:
	smPAT3D		*PatMesh;
	int			ParticleID[7];

	int			MaxFrame;
	int			CurrentFrame;
	smOBJ3D		*ObjBip[7];
};



class AssaSkill3VigorBall : public cASSAEFFECT
{
public:
	AssaSkill3VigorBall();
	~AssaSkill3VigorBall();

	void Start(POINT3D* pCur, smCHAR* destChar, D3DXVECTOR3* velocity, int delay);
	void Main();

private:
	int			ParticleID;
	int			ParticleIDExt1;
	D3DXVECTOR3	Velocity;
	smCHAR		*DestChar;
	D3DXVECTOR3   Pos;
};

class AssaSkill3ResurrectionShot : public cASSAEFFECT
{
public:
	AssaSkill3ResurrectionShot();
	~AssaSkill3ResurrectionShot();
	void Start(smCHAR* character, int delay);
	void Main();
	void Draw(POINT3D *pPosi, POINT3D *pAngle);


private:
	smPAT3D		*PatMesh;
	int			ParticleID;
	int			ParticleIDExt1;

	int			MaxFrame;
	int			CurrentFrame;

	smOBJ3D		*ObjBip;
	int			Delay;
	int			TimeCount;

	BOOL		MyCharacterFlag;
	BOOL		EndFlag;
	int			MeshBlendStep;
};

class AssaSkill3ResurrectionPart : public cASSAEFFECT
{
public:
	AssaSkill3ResurrectionPart();
	~AssaSkill3ResurrectionPart();

	void Start(smCHAR* character, int liveCount);
	void Main();

private:
	int			ParticleID;
	BOOL		MyCharacterFlag;
	BOOL		EndFlag;
};


class AssaSkill3Extinction : public cASSAEFFECT
{
public:
	AssaSkill3Extinction();
	~AssaSkill3Extinction();

	void Start(smCHAR* character);
	void Main();

private:
	int			ParticleID;
	BOOL		MyCharacterFlag;
};


class AssaSkillVirtualLifeMember : public cASSAEFFECT
{
public:
	AssaSkillVirtualLifeMember();
	~AssaSkillVirtualLifeMember();
	void Start(smCHAR* character, int liveCount);
	void Main();



private:
	int			ParticleID;
	BOOL		MyCharacterFlag;

	BOOL		EndFlag;
};


class AssaSkillTriumphOfValhallaPart : public cASSAEFFECT
{
public:
	AssaSkillTriumphOfValhallaPart();
	~AssaSkillTriumphOfValhallaPart();
	void Start(smCHAR* character, int liveCount);
	void StartHallOfValhalla(smCHAR* character, int liveCount);
	void Main();

private:
	int			ParticleID;
	int			ParticleIDExt;
	BOOL		MyCharacterFlag;

	smOBJ3D		*ObjBip;
	smOBJ3D		*ObjBipExt;
	BOOL		EndFlag;
};

class AssaSkillTriumphOfValhallaShot : public cASSAEFFECT
{
public:
	AssaSkillTriumphOfValhallaShot();
	~AssaSkillTriumphOfValhallaShot();

	void Start(smCHAR* curChar, smCHAR* destChar, D3DXVECTOR3* velocity, int liveCount);
	void Draw(POINT3D *pPosi, POINT3D *pAngle);
	void Main();

private:
	int			ParticleID;

	D3DXVECTOR3	Velocity;
	smCHAR		*DestChar;
	D3DXVECTOR3   Pos;
	int			LiveCount;

	smOBJ3D     *SearchObj;
};


class AssaSkill3LightingJavelin : public cASSAEFFECT
{
public:
	AssaSkill3LightingJavelin();
	~AssaSkill3LightingJavelin();

private:
	int			AnimationID[4];
	int			AniDelay;
	int			AniIndex;

	POINT3D		ShootingAngle;
	int			ParticleID;

public:
	void StartShort(POINT3D *pCur, POINT3D *pDest);
	void Start(POINT3D* pCur, POINT3D* pDest);
	void Main();
	void Draw(POINT3D *pPosi, POINT3D *pAngle);
};

class AssaSkill3StormJavelin : public cASSAEFFECT
{
public:
	AssaSkill3StormJavelin();
	~AssaSkill3StormJavelin();

private:
	int			TextureID[6];
	int			TextureIDExt1;

	int			AniDelay;
	int			AniIndex;

	POINT3D		ShootingAngle;
	int			ParticleID;

	smPAT3D*	PatMesh;
public:
	void Start(POINT3D* pCur, POINT3D* pDest);
	void Main();
	void Draw(POINT3D *pPosi, POINT3D *pAngle);
	int			BlendStep;


	POINT3D		ScalePosExt;
	D3DXVECTOR3   ScalePosExtStep;
};



class AssaSkill3SplitJavelin : public cASSAEFFECT
{
public:
	AssaSkill3SplitJavelin();
	~AssaSkill3SplitJavelin();

private:
	smPAT3D*	PatMesh;
	POINT3D		ShootingAngle;
	int			CurrentFrame;
	int			Delay;
	int			BlendStep;


public:
	void Start(POINT3D* pCur, POINT3D* pDest, int delay);
	void Main();
	void Draw(POINT3D* pPosi, POINT3D *pAngle);
};







class AssaClassUpWeapon : public cASSAEFFECT
{
public:
	AssaClassUpWeapon();
	~AssaClassUpWeapon();

	void Start(smCHAR* character);
	void Main();
	void RespawnParticle();
	void StopParticle();
	void StopParticleID();
private:

	int			ParticleIDGroup[4];
	BOOL		MyCharacterFlag;
	BOOL		EndFlag;

	POINT3D		LocalPos;
	int			LocalAngle;

	BOOL		LocalPosTransFlag;
};



class AssaNatureSnow : public cASSAEFFECT
{
public:
	AssaNatureSnow();
	~AssaNatureSnow();
	void Start();
	void Main();
private:
	int			ParticleID;
	BOOL		MyCharacterFlag;
	BOOL		EndFlag;
};



class AssaRunicGuardianShot : public cASSAEFFECT
{
public:
	AssaRunicGuardianShot();
	~AssaRunicGuardianShot();
	void Start(POINT3D *pCur, POINT3D *pDest);
	void Main();

private:
	int			ParticleID;
	POINT3D     ShootingAngle;
};




class AssaRunicGuardianBossSkill : public cASSAEFFECT
{
public:
	AssaRunicGuardianBossSkill();
	~AssaRunicGuardianBossSkill();
	void Start(smCHAR* character, int liveCount);
	void Main();

private:
	int			ParticleID;
	BOOL		MyCharacterFlag;
	BOOL		EndFlag;
	int			ShotBlendType;
};


class AssaRunicGuardianBossShot : public cASSAEFFECT
{
public:
	AssaRunicGuardianBossShot();
	~AssaRunicGuardianBossShot();

	void Start(POINT3D *pShotPos, POINT3D *pAttackPos, D3DXVECTOR3* velocity, int BlendType = SMMAT_BLEND_INVSHADOW);
	void Draw(POINT3D *pPosi, POINT3D *pAngle);
	void Main();

	void SetHitFlag(bool flag)
	{
		HitEffectFlag = flag;
	}
private:
	int			ParticleID;

	D3DXVECTOR3	Velocity;
	int			LiveCount;

	D3DXVECTOR3	CurPos;
	D3DXVECTOR3   AttackPos;
	bool		HitEffectFlag;
};

class AssaRunicGuardianBossHit : public cASSAEFFECT
{
public:
	AssaRunicGuardianBossHit();
	~AssaRunicGuardianBossHit();

	void Start(POINT3D* pCur, smCHAR* destChar, D3DXVECTOR3* velocity, int delay, smCHAR **charList = NULL, int charCount = 0);
	void Main();

private:
	int			ParticleID;
	int			ParticleIDExt1;
	D3DXVECTOR3	Velocity;
	smCHAR		*DestChar;
	D3DXVECTOR3   Pos;

	smCHAR      *CharList[100];
	int			CharCount;
	int			TempMyIndex;


};


class AssaSkyParticle : public cASSAEFFECT
{
public:
	AssaSkyParticle();
	~AssaSkyParticle();

	void Start(POINT3D* pCur, POINT3D* pDest, int delay = 0);
	void Main();
	void SetDelay(int delay);
private:
	int			ParticleID;
	D3DXVECTOR3   Pos;
	D3DXVECTOR3   Velocity;
	int			TimeCount;

	int			Delay;
	bool		ParticleSpawnFlag;
};


class AssaRunicGuardianLight : public cASSAEFFECT
{
public:
	AssaRunicGuardianLight();
	~AssaRunicGuardianLight();

private:
	int			AnimationID[3];
	int			AniDelay;
	int			AniIndex;

	int			ParticleID1;
	int         ParticleID2;

	smCHAR		*pCurChar;
	smCHAR      *pDestChar;

	bool		CurMyCharacterFlag;
	bool		DestMyCharacterFlag;

	smOBJ3D		*ObjBip1;

	POINT3D     CurPos;
	POINT3D     DesPos;
	bool		StopFlag;

public:
	void Start(smCHAR* pCurChar, smCHAR* pDesChar, bool ObjectFlag = false, bool firstPartFlag = false, bool secondPartFlag = false);
	void Main();
	void Draw(POINT3D *pPosi, POINT3D *pAngle);
	bool GetCameraCoord(POINT3D &world);
	bool AddFace2DLine(POINT3D *curPos, POINT3D *desPos, int width, int matNum);
};


class AssaShelltomShot : public cASSAEFFECT
{
public:
	AssaShelltomShot();
	~AssaShelltomShot();

	void Start(POINT3D* pCur, POINT3D* pDest, int shellType = 0);
	void Draw(POINT3D *pPosi, POINT3D *pAngle);

	void Main();
private:
	int			ParticleID;
	POINT3D     ShootingAngle;
	smPAT3D     *PatMesh;
	int			m_ShellType;
	float VelocityY;
};


class AssaShelltomUpWeapon : public cASSAEFFECT
{
public:
	AssaShelltomUpWeapon();
	~AssaShelltomUpWeapon();

	void	Start(smCHAR *pCharacter, int timeCount);
	void	Main();

	BOOL	GetCameraCoord(POINT3D &world);
	BOOL	AddFace2DLine(POINT3D *curPos, POINT3D *desPos, int width, int matNum);

private:
	BOOL	MyCharacterFlag;
	BOOL	EndFlag;

	int		ZPos[2];
	int		ParticleID[2];
	int		TimeCount;

};

class AssaShelltomUpWeapon1 : public cASSAEFFECT
{
public:
	AssaShelltomUpWeapon1();
	~AssaShelltomUpWeapon1();

	void	Start(smCHAR *pCharacter, int timeCount);
	void	Main();
	void	Draw(POINT3D *pPosi, POINT3D *pAngle);

private:
	BOOL	MyCharacterFlag;
	BOOL	EndFlag;

	int		TimeCount;
	int		MaterialNum;

	POINT3D		LocalPos;
	int			LocalAngle;

	BOOL		LocalPosTransFlag;

};

#define	MAX_WEAPON_POS	10
class AssaShelltomUpWeapon2 : public cASSAEFFECT
{
public:
	AssaShelltomUpWeapon2();
	~AssaShelltomUpWeapon2();

	void	Start(smCHAR *pCharacter, int timeCount, int shellTomCode);
	void	Main();
	void	Draw(POINT3D *pPosi, POINT3D *pAngle);

private:
	BOOL	EndFlag;
	BOOL	MyCharacterFlag;

	int		MaterialNum;

	int		Width;
	BOOL	ScaleFlag;
	int		ScaleWidth;

	int		WeaponPosCount;
	POINT3D	WeaponPos[MAX_WEAPON_POS];

	int			GlowWidth;
	int			GlowPosIndex;
	BOOL		GlowFlag;
	smFACE2D	GlowFace;
};



class ParkAssaChaosKaraMeteo : public cASSAEFFECT
{
public:
	ParkAssaChaosKaraMeteo();
	~ParkAssaChaosKaraMeteo();

	void Start(POINT3D* pCur, POINT3D* pDest, int delay = 0);
	void Main();
	void SetDelay(int delay);
private:
	int			ParticleID;
	D3DXVECTOR3   Pos;
	D3DXVECTOR3   Velocity;
	int			TimeCount;

	int			Delay;
	bool		ParticleSpawnFlag;
};


class ParkAssaLizardfolk : public cASSAEFFECT
{
public:
	ParkAssaLizardfolk();
	~ParkAssaLizardfolk();

private:
	smPAT3D*	PatMesh;
	POINT3D		ShootingAngle;
	int			CurrentFrame;
	int			Delay;
	int			BlendStep;


public:
	void Start(POINT3D* pCur, POINT3D* pDest, int delay);
	void Main();
	void Draw(POINT3D* pPosi, POINT3D *pAngle);
};


class AssaSkyMeteoParticle : public cASSAEFFECT
{
public:
	AssaSkyMeteoParticle();
	~AssaSkyMeteoParticle();

	void Start(POINT3D* pCur, POINT3D* pDest, int delay = 0, int nType = 0);
	void Main();
	void SetDelay(int delay);
private:
	int			ParticleID;
	D3DXVECTOR3   Pos;
	D3DXVECTOR3   Velocity;
	int			TimeCount;

	int			Delay;
	bool		ParticleSpawnFlag;
	int			nEffectType;
};

#endif


