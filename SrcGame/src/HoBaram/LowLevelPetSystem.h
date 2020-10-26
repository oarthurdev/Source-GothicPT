









#ifndef _LowLevelPet_H_
#define _LowLevelPet_H_

#include "smlib3d\\smd3d.h"
#include "..\\smwsock.h"
#include "..\\character.h"

#define PET_TERRY	0
#define PET_NEPSYS  1
#define PET_IO      2
#define PET_MUTE    3






class HoLowLevelPet
{
public:
	enum Type
	{
		Terry,
		Nepsys,
		Io,
		Mute
	};

	enum FsmState
	{
		Spawn,
		Idle,
		SkillPre,
		Skill,
		Vanish,
		None
	};

	enum FsmStateEvent
	{
		EVENT_INIT,
		EVENT_UPDATE,
		EVENT_EXIT
	};

	HoLowLevelPet();
	~HoLowLevelPet();

	void	FsmEventProcess(FsmStateEvent eStateEvent);
	void	OnEvent(FsmStateEvent eEvent, FsmState eFsmState);

	void		SetFsmState(HoLowLevelPet::FsmState eFsmState);
	void		SetFsmAttackState(smCHAR *pAttackChar);
	void        SetFsmHealState(smCHAR *pHealChar);

	FsmState    GetFsmState();
	smCHAR     *GetAttachChar();

	void    SetSpawn(smCHAR *pAttachChar, HoLowLevelPet::Type type, smPAT3D *meshRes, smPAT3D *boneRes);
	void    SetIdle(smCHAR *pAttachChar, HoLowLevelPet::Type type, smPAT3D *meshRes, smPAT3D *boneRes, smCHAR *pAttackChar);

	bool	Main();
	bool	Draw(int x, int y, int z, int angleX, int angleY, int angleZ);

	HoLowLevelPet::Type	GetType();

private:
	Type		m_Type;
	smPAT3D		*m_PetMeshRes;
	smPAT3D     *m_PetBoneRes;
	smCHAR		*m_TargetChar;
	smCHAR      *m_AttackChar;
	int			m_iCurrentFrame;

	FsmState            m_eCurrentFsmState;
	FsmState			m_eNextFsmState;
	bool				m_bFsmChangeFlag;
	bool				m_bMyCharacterFlag;


	POINT3D				m_CurrentPos;
	POINT3D				m_TargetPos;
	POINT3D				m_AttackPos;
	bool				m_bSkillFlag;
	int					m_iParticleID;
	smOBJ3D				*ObjBip;
	bool				m_bAttackTiming;

};








const int MAX_LOWLEVEL_PET = 100;
class HoLowLevelPetManager
{
public:
	HoLowLevelPetManager();
	~HoLowLevelPetManager();

private:
	HoLowLevelPet	LowLevelPetList[MAX_LOWLEVEL_PET];
	smPAT3D			*m_Bone;

	smPAT3D			*m_MeshTerry;
	smPAT3D			*m_MeshNepsys;
	smPAT3D			*m_MeshIo;
	smPAT3D			*m_MeshMute;

private:
	HoLowLevelPet *GetEmptyPet(smCHAR *pAttachChar);
	HoLowLevelPet *GetEmptyIdlePet(smCHAR *pAttachChar, int petType, smCHAR *pAttackChar);
public:
	bool	Create();
	bool    Destroy();

	bool    AddPet(smCHAR *pAttachChar, HoLowLevelPet::Type petType);
	bool	AddIdlePet(smCHAR *pAttachChar, int petType, smCHAR *pAttackChar);

	void    DeletePet(smCHAR *pAttachChar);

	bool	Main();
	bool    Draw(int x, int y, int z, int angleX, int angleY, int angleZ);
};







extern bool g_CreatePetSystem();
extern bool g_MainPetSystem();
extern bool g_DrawPetSystem(int x, int y, int z, int ax, int ay, int az);
extern bool g_DestroyPetSystem();
extern bool g_LowLevelAddPet(smCHAR *pAttachChar, HoLowLevelPet::Type petType);
extern bool g_LowLevelAddIdlePet(smCHAR *pAttachChar, int petType, smCHAR *pAttackChar = NULL);

extern void g_LowLevelDeletePet(smCHAR *pAttachChar);

extern POINT3D HoPetRenderPoint;
extern DWORD  g_LowLevelPetAttackSerial;

#endif
