#ifndef _H0_EFFECT_MANAGER_
#define _HO_EFFECT_MANAGER_

#include "smlib3d\\smd3d.h"
#include "smwsock.h"
#include "character.h"
#include "HoEffectController.h"
#include <vector>
#include <string>

class HoEffectTypeInterface
{
protected:
	bool		m_bLiveFlag;
	int			m_iCode;
	float		m_fEndTime;
	smCHAR		*m_pAttachChar;
public:
	HoEffectTypeInterface() : m_bLiveFlag(true),
	                          m_iCode(-1),
	                          m_pAttachChar(NULL),
	                          m_fEndTime(0.f) {};

	virtual ~HoEffectTypeInterface() {};

	bool	IsLive() { return m_bLiveFlag;}
	virtual void UpdateView (int x, int y, int z, int ax, int ay, int az) = 0;
	virtual void Main (float elapsed) = 0;

	void	SetSkillCode(int code) { m_iCode = code; }
	int		GetSkillCode() { return m_iCode; }

	smCHAR *GetAttachChar() { return m_pAttachChar; }
	void	SetEndTime(float endTime) { m_fEndTime = endTime; }
	void	SetAddEndTime(float endTime) { m_fEndTime += endTime; }
};

class HoEffectType_Default : public HoEffectTypeInterface
{
private:
	HoEffectGroup	*m_pEffectGroup;
public:
	HoEffectType_Default() : m_pEffectGroup(NULL) {};
	~HoEffectType_Default();

	void	Init(HoEffectGroup *effectGroup, int x, int y, int z, int angleX, int angleY, int angleZ);
	void	UpdateView(int x, int y, int z, int ax, int ay, int az);
	void	Main(float elapsedTime);
};



class HoEffectType_Attach_Avater : public HoEffectTypeInterface
{
private:
	bool			m_bMyCharacterFlag;
	HoEffectGroup	*m_pEffectGroup;
	float			m_fHeight;
	float			m_fElapsedTime;
	

	int				m_iParticleID;
	bool			m_bParticleDeadFlag;
public:
	HoEffectType_Attach_Avater() : m_pEffectGroup(NULL),
								   m_fHeight(0.f),
	                               m_fElapsedTime(0.f),
	                               
	                               m_bMyCharacterFlag(false),
	                               m_iParticleID(-1),
	                               m_bParticleDeadFlag(false) {};
	~HoEffectType_Attach_Avater();
	
	void	Init(smCHAR *pChar, HoEffectGroup *effectGroup, float endTime, float height = 0.f);
	void	UpdateView(int x, int y, int z, int ax, int ay, int az);
	void	Main(float elapsed);
	void	SetParticleID(int partID) { m_iParticleID = partID; }
};


#define	MAX_ATTACH_OBJECT	10
class HoEffectType_Attach_Obj_Info
{
public:
	HoEffectType_Attach_Obj_Info() : m_pOBJ3D(NULL),
	                                 m_pEffectGroup(NULL) {};
	smOBJ3D         *m_pOBJ3D;
	HoEffectGroup	*m_pEffectGroup;
};

class HoEffectType_Attach_AvaterObject_Info
{
public:
	HoEffectType_Attach_AvaterObject_Info() : m_pAttachChar(NULL) { memset(m_pEffectGroupList, 0, 4*MAX_ATTACH_OBJECT); };
	smCHAR									  *m_pAttachChar;
	HoEffectType_Attach_Obj_Info			  m_Attach_Obj_Info[MAX_ATTACH_OBJECT];
	HoEffectGroup							  *m_pEffectGroupList[MAX_ATTACH_OBJECT]; 
};

enum
{
	SHOT_START,
	SHOT_PROCESS,
	SHOT_END,
	MAX_SHOT_EFFECT,
};

class HoEffectType_Avater_Shot_Info
{
public:
	HoEffectType_Avater_Shot_Info()
	{
		memset(&m_CurrentPos, 0, sizeof(m_CurrentPos));
		memset(&m_AttackPos,  0, sizeof(m_AttackPos));
		memset(m_EffectGroup, 0, sizeof(m_EffectGroup));
		m_LineSize.x = 5.f;
		m_LineSize.y = 5.f;
		m_LineSize.z = 0.f;
		m_fSpeed     = 8.f;
	}

	POINT3D		m_CurrentPos;
	POINT3D		m_AttackPos;
	float		m_fSpeed;
	HoEffectGroup *m_EffectGroup[MAX_SHOT_EFFECT];
	std::string m_LineTextureName;
	point3      m_LineSize;

};


class HoEffectType_Avater_Shot_Default : public HoEffectTypeInterface
{
private:
	point3			 m_CurrentPos;
	point3			 m_AttackPos;
	smCHAR	         *m_AttackChar;
	
	HoEffectGroup	*m_EffectGroup[MAX_SHOT_EFFECT];
	int				 m_ShotState;
	point3			 m_Velocity;
	float			 m_fSpeed;
	
	bool					m_bLineAttachFlag;
	HoEffectLineListModel    m_EffectLineModel;

public:
	HoEffectType_Avater_Shot_Default();
	~HoEffectType_Avater_Shot_Default();

	void	UpdateView(int x, int y, int z, int ax, int ay, int az);
	void	Main(float elapsed);
	void	Init(const HoEffectType_Avater_Shot_Info &info);
};


class HoEffectType_Attach_AvaterToAvater : public HoEffectTypeInterface
{
private:
	smCHAR *m_pAttachChar1;
	smCHAR *m_pAttachChar2;
	
	int									m_iParticleID[2];
	HoEffectGroup						*m_pCurrentEffectGroup;
	HoEffectGroup						*m_pDestEffectGroup;
	
	point3								m_CurrentPos;
	point3								m_DestPos;
public:
	HoEffectBillboardAxialController	m_AxialController;

	HoEffectType_Attach_AvaterToAvater() : m_pAttachChar1(NULL),
										   m_pAttachChar2(NULL),
	                                       m_pCurrentEffectGroup(NULL),
										   m_pDestEffectGroup(NULL) {};
	
	~HoEffectType_Attach_AvaterToAvater();

	void	UpdateView(int x, int y, int z, int ax, int ay, int az);
	void	Main(float elapsedTime);
	
	void	Init(smCHAR *Char1, smCHAR *Char2, const std::string &textureName, int textureCount, float aniDelayTime);
	void	Init(HoEffectGroup *currentEffectGroup, HoEffectGroup *destEffectGroup);
	void	Init(smCHAR *char1, smCHAR *char2, int partID1, int partID2);
};


class HoEffectType_Avater_Blade_Blur : public HoEffectTypeInterface
{
private:
	smCHAR *m_pAttachChar;
	float	m_fElapsedTime;
	float   m_fEndTime;
	bool	m_bMyCharacterFlag;

	smTEXLINK	MotionBlurTexLink[128];
	smVERTEX	MotionBlurVertex[64];
	smFACE		MotionBlurFace[64];
	
	HoEffectTextureNameProperty	m_TextureNameProperty;
public:
	HoEffectType_Avater_Blade_Blur() : m_pAttachChar(NULL),
		                               m_bMyCharacterFlag(false),
							           m_fElapsedTime(0.f),
									   m_fEndTime(0.f) {};
	~HoEffectType_Avater_Blade_Blur() {};

	void	UpdateView(int x, int y, int z, int ax, int ay, int az);
	void	Main(float elapsedTime);
	void	Init(smCHAR *pChar, const std::string &fileName, float endTime);
};




class HoEffectType_Magnetic_Sphere : public HoEffectTypeInterface
{
private:
	smCHAR *m_pAttachChar;
	bool	m_bMyCharacterFlag;
	
	smPAT3D	*m_pMesh;         
	smOBJ3D *m_pObj[3];       
	
	int		m_ParticleID[3];  
	float   m_fElapsedTime;   
	float	m_fEndTime;
	
	float   m_fCurrentFrame;
	float	m_fAttackTime;
	float	m_fAttackTimeCount;
public:
	HoEffectType_Magnetic_Sphere() : m_pAttachChar(NULL),
		                             m_bMyCharacterFlag(false),
									 m_pMesh(NULL),
									 m_fElapsedTime(0.f),
									 m_fEndTime(0.f),
	                                 m_fCurrentFrame(0.f),
									 m_fAttackTime(0.f),
									 m_fAttackTimeCount(0.f)
									 { 
										 memset(m_pObj, 0, 4*3); 
										 m_ParticleID[0] = -1;
										 m_ParticleID[1] = -1;
										 m_ParticleID[2] = -1;
									 };
	~HoEffectType_Magnetic_Sphere() {};
	void	UpdateView(int x, int y, int z, int ax, int ay, int az);
	void	Main(float elapsedTime);
	void	Init(smCHAR *pChar, float endTime, float attackTime);
};

class HoEffectType_PhoneixShot : public HoEffectTypeInterface
{
private:
	smPAT3D *m_pMesh;		
	float	m_Alpha;

	int		m_iParticleID;

	point3  m_CurrentPos;
	point3  m_AttackPos;
	
	point3  m_Velocity;
	point3  m_ShotAngle;

	bool	m_bDeadFlag;
public:
	HoEffectType_PhoneixShot() : m_pMesh(NULL),
								 m_Alpha(255),
								 m_iParticleID(-1),
	                             m_bDeadFlag(false) {};

	void Init(point3 &curPos, point3 &desPos);
	void UpdateView(int x, int y, int z, int ax, int ay, int az);
	void Main(float elapsedTime);
};


class HoEffectType_FireShot : public HoEffectTypeInterface
{
private:
	int		m_iParticleID;
	point3	m_CurrentPos;
	point3  m_AttackPos;
	point3	m_Velocity;

public:
	HoEffectType_FireShot() : m_iParticleID(-1) {};

	void	Init(point3 &curPos, point3 &desPos);
	void	Main(float elapsedTime);
	void UpdateView(int x, int y, int z, int ax, int ay, int az);
};

enum
{
	MUSPEL_NONE,
	MUSPEL_SPAWN,
	MUSPEL_IDLE,
	MUSPEL_ATTACK,
	MUSPEL_DEFENCE,
	MUSPEL_WALK,
	MUSPEL_DEAD
};

enum 
{
	EVENT_INIT,
	EVENT_UPDATE,
	EVENT_EXIT
};

class HoEffectType_MusPel : public HoEffectTypeInterface
{
private:
	smCHAR	   *m_pAttachChar;
	bool		m_bMyCharacterFlag;

	smPAT3D	   *m_pMesh;         
	float		m_fElapsedTime;
	float		m_fEndTime;
	float		m_fCurrentFrame;

	int			m_State;
	int			m_NextState;

	float		m_Alpha;

	int			m_ParticleID;
	smOBJ3D		*m_pObj;

	float		m_fAttackTime;
	float		m_fAttackTimeCount;
	smCHAR      *m_AttackMonster;

	bool		m_bHandEffectFlag;
	bool		m_bHitEffectFlag;
	int			m_HandParticleNum;

	point3		m_CurrentPos;
public:
	HoEffectType_MusPel() : m_pAttachChar(NULL),
							m_bMyCharacterFlag(false),
							m_pMesh(NULL),
							m_fElapsedTime(0.f),
							m_fEndTime(0.f),
							m_fCurrentFrame(0.f),
							m_ParticleID(-1),
							m_pObj(NULL),
							m_State(MUSPEL_NONE),
	                        m_NextState(MUSPEL_NONE),
	                        m_Alpha(0.f),
							m_fAttackTime(0.f),
							m_fAttackTimeCount(0.f),
							m_AttackMonster(NULL),
							m_bHandEffectFlag(false),
							m_bHitEffectFlag(false),
							m_HandParticleNum(-1)
							{SetState(MUSPEL_SPAWN);};
	~HoEffectType_MusPel() {};
	void	UpdateView(int x, int y, int z, int ax, int ay, int az);
	void	Main(float elapsedTime);
	void	Init(smCHAR *pChar, float endTime, float attackTime);
	void    Process();
	void	SetState(int state);
	void	OnEvent(int curState, int curEvent);
};

class HoEffectType_RegenerationField : public HoEffectTypeInterface
{
private:
	bool    m_bMyCharacterFlag;

	smPAT3D *m_pMesh;
	float   m_fCurrentFrame;
	
	int		m_iParticleID;
public:
	HoEffectType_RegenerationField() : m_bMyCharacterFlag(false),
									   m_pMesh(NULL),
									   m_fCurrentFrame(0.f),
	                                   m_iParticleID(-1) {};
	~HoEffectType_RegenerationField() {};
	void	UpdateView(int x, int y, int z, int ax, int ay, int az);
	void	Main(float elapsedTime);
	void	Init(smCHAR *pChar);
};

class HoEffectManager
{
private:
	std::vector<HoEffectTypeInterface *> m_PostEffectTypeList;
	std::vector<HoEffectTypeInterface *> m_EffectTypeList;
	std::vector<HoEffectTypeInterface *> m_MaintainEffectTypeList;

	static HoEffectManager*              m_Instance;
public:
	HoEffectManager() {};
	~HoEffectManager() { Clear(); };
	
	static HoEffectManager*              GetInstance();

	void	UpdateView(int x, int y, int z, int ax, int ay, int az);
	void	Main(float elapsedTime);
	void	AddEffect(HoEffectTypeInterface *effect);
	void    AddPostEffect(HoEffectTypeInterface *effect);
	void    AddMaintainEffect(HoEffectTypeInterface *effect);
	bool	SetMaintainEffect(int code, smCHAR *pAttachChar, float time);
	void	Clear();
	BOOL    GetSkillCode(smCHAR *pChar, int code);
};

#endif
