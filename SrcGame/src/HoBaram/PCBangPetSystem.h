









#ifndef _PC_BANG_Pet_H_
#define _PC_BANG_Pet_H_

#include "smlib3d\\smd3d.h"
#include "..\\smwsock.h"
#include "..\\character.h"

#define PCBANG_PET_BURSTP	0
#define PCBANG_PET_BURSTS	1
#define PCBANG_PET_BURSTL	2
#define PCBANG_PET_BURSTD	3






class HoPCBangPet
{
public:
	enum Type
	{
		BurstP,
		BurstS,
		BurstL,
		BurstD,
		IllusionP,
		IllusionS,
		IllusionL,
		IllusionD,
	};

	enum PCBang_FsmState
	{
		Spawn,
		Idle,
		SkillPre,
		Skill,
		Vanish,
		None
	};

	enum PCBang_FsmStateEvent
	{
		EVENT_INIT,
		EVENT_UPDATE,
		EVENT_EXIT
	};

	HoPCBangPet();
	~HoPCBangPet();

	void	FsmEventProcess(PCBang_FsmStateEvent eStateEvent);
	void	OnEvent(PCBang_FsmStateEvent eEvent, PCBang_FsmState eFsmState);

	void		SetFsmState(HoPCBangPet::PCBang_FsmState eFsmState);
	void		SetFsmAttackState(smCHAR *pAttackChar);
	void        SetFsmHealState(smCHAR *pHealChar);

	PCBang_FsmState    GetFsmState();
	smCHAR     *GetAttachChar();
	BOOL	PetNearMonster(smCHAR *lpNearMonster);

	void    SetSpawn(smCHAR *pAttachChar, HoPCBangPet::Type type, smPAT3D *meshRes, smPAT3D *boneRes);
	void    SetIdle(smCHAR *pAttachChar, HoPCBangPet::Type type, smPAT3D *meshRes, smPAT3D *boneRes, smCHAR *pAttackChar);

	bool	Main();
	bool	Draw(int x, int y, int z, int angleX, int angleY, int angleZ);

	HoPCBangPet::Type	GetType();

private:
	Type		m_Type;
	smPAT3D		*m_PetMeshRes;
	smPAT3D     *m_PetBoneRes;
	smCHAR		*m_TargetChar;
	smCHAR      *m_AttackChar;
	int			m_iCurrentFrame;

	smCHAR      *m_AttackCharTarget;

	PCBang_FsmState            m_eCurrentFsmState;
	PCBang_FsmState			m_eNextFsmState;
	bool				m_bFsmChangeFlag;
	bool				m_bMyCharacterFlag;


	POINT3D				m_CurrentPos;
	POINT3D				m_TargetPos;
	POINT3D				m_AttackPos;
	bool				m_bSkillFlag;
	int					m_iParticleID;
	smOBJ3D				*ObjBip;
	bool				m_bAttackTiming;

	bool				m_bPetAttacking;
};








const int MAX_PCBANG_PET = 100;
class HoPCBangPetManager
{
public:
	HoPCBangPetManager();
	~HoPCBangPetManager();

private:
	HoPCBangPet	PcBangPetList[MAX_PCBANG_PET];
	smPAT3D			*m_BoneBurstP;
	smPAT3D			*m_BoneBurstS;
	smPAT3D			*m_BoneBurstL;
	smPAT3D			*m_BoneBurstD;

	smPAT3D			*m_MeshBurstP;
	smPAT3D			*m_MeshBurstS;
	smPAT3D			*m_MeshBurstL;
	smPAT3D			*m_MeshBurstD;


private:
	HoPCBangPet *GetEmptyPet(smCHAR *pAttachChar);
	HoPCBangPet *GetEmptyIdlePet(smCHAR *pAttachChar, int petType, smCHAR *pAttackChar);
public:
	bool	Create();
	bool    Destroy();

	bool    AddPet(smCHAR *pAttachChar, HoPCBangPet::Type petType);
	bool	AddIdlePet(smCHAR *pAttachChar, int petType, smCHAR *pAttackChar);

	void    DeletePet(smCHAR *pAttachChar);

	bool	Main();
	bool    Draw(int x, int y, int z, int angleX, int angleY, int angleZ);
};







extern bool g_PCBang_CreatePetSystem();
extern bool g_PCBang_MainPetSystem();
extern bool g_PCBang_DrawPetSystem(int x, int y, int z, int ax, int ay, int az);
extern bool g_PCBang_DestroyPetSystem();
extern bool g_HoPCBangAddPet(smCHAR *pAttachChar, HoPCBangPet::Type petType);
extern bool g_HoPCBangAddIdlePet(smCHAR *pAttachChar, int petType, smCHAR *pAttackChar = NULL);

extern void g_HoPCBangDeletePet(smCHAR *pAttachChar);

extern POINT3D HoHoPCBangPetRenderPoint;
extern DWORD  g_HoPCBangPetAttackSerial;

#endif
