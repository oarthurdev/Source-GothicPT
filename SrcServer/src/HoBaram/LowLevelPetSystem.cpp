#include "SinBaram\\SinLinkHeader.h"
#include "LowLevelPetSystem.h"
#include "..\\playmain.h"
#include "hoAssaParticleEffect.h"
#include "HoNewParticleLinkHeader.h"
#include "..\\effectsnd.h"
POINT3D HoPetRenderPoint;
#include "..\\damage.h"

DWORD	g_LowLevelPetAttackSerial = 0;
HoLowLevelPet::HoLowLevelPet() : m_Type(HoLowLevelPet::Terry),
m_PetMeshRes(NULL),
m_PetBoneRes(NULL),
m_bFsmChangeFlag(false),
m_eCurrentFsmState(FsmState::None),
m_eNextFsmState(FsmState::None),
m_TargetChar(NULL),
m_iCurrentFrame(10 * 160),
m_bMyCharacterFlag(false)
{

}

HoLowLevelPet::~HoLowLevelPet()
{

}

bool HoLowLevelPet::Draw(int x, int y, int z, int angleX, int angleY, int angleZ)
{
	if(m_eCurrentFsmState != FsmState::None)
	{

		if(m_TargetChar)
		{

			if(m_TargetChar->FlagShow == 0 && !m_bMyCharacterFlag)
				return false;
		}


		POINT3D cameraPos;
		POINT3D cameraAngle;
		cameraPos.x = x;
		cameraPos.y = y;
		cameraPos.z = z;

		cameraAngle.x = angleX;
		cameraAngle.y = angleY;
		cameraAngle.z = angleZ;

		m_PetMeshRes->Frame = m_iCurrentFrame;

		POINT3D petAngle;
		petAngle.x = 0;
		petAngle.y = (ANGLE_180 - m_TargetChar->Angle.y&ANGCLIP);
		petAngle.z = 0;

		smRender.ObjectVertexScale = 256 + 80;
		m_PetMeshRes->SetPosi(&m_CurrentPos, &petAngle);
		m_PetMeshRes->RenderD3D(&cameraPos, &cameraAngle);
		smRender.ObjectVertexScale = 0;

		if(m_bMyCharacterFlag)
		{
			POINT	sPos;
			int	He = 0;

			He = 3000;

			smRender.SetCameraPosi(x, y, z, angleX, angleY, angleZ);

			RECT PetRendRect2D;
			HoPetRenderPoint.z = smRender.GetRect2D(m_CurrentPos.x, m_CurrentPos.y + (He >> 1), m_CurrentPos.z, 44 * fONE, He, &PetRendRect2D, &sPos);
			HoPetRenderPoint.x = sPos.x;
			HoPetRenderPoint.y = sPos.y;

		}
	}
	return true;
}


bool HoLowLevelPet::Main()
{
	if(GetFsmState() != FsmState::None)
	{
		if(m_bMyCharacterFlag)
		{
			if(m_TargetChar != lpCurPlayer)
				m_TargetChar = lpCurPlayer;
		}

		FsmEventProcess(FsmStateEvent::EVENT_UPDATE);
	}
	return true;
}

void HoLowLevelPet::FsmEventProcess(FsmStateEvent eStateEvent)
{
	OnEvent(eStateEvent, m_eCurrentFsmState);


	int safetyCount = 10;
	while(m_bFsmChangeFlag && (--safetyCount >= 0))
	{


		m_bFsmChangeFlag = false;


		OnEvent(FsmStateEvent::EVENT_EXIT, m_eCurrentFsmState);


		m_eCurrentFsmState = m_eNextFsmState;


		OnEvent(FsmStateEvent::EVENT_INIT, m_eCurrentFsmState);
	}
}










void HoLowLevelPet::OnEvent(FsmStateEvent eEvent, FsmState eFsmState)
{
	if(eFsmState == FsmState::Spawn)
	{
		switch(eEvent)
		{
			case FsmStateEvent::EVENT_INIT:
			{
				GetMoveLocation(0, 0, -50 * fONE, 0, m_TargetChar->Angle.y + ANGLE_45, 0);

				m_CurrentPos.x = m_TargetChar->pX + GeoResult_X;
				m_CurrentPos.y = m_TargetChar->pY + m_TargetChar->PatHeight + 10 * fONE;
				m_CurrentPos.z = m_TargetChar->pZ + GeoResult_Z;

				break;
			}

			case FsmStateEvent::EVENT_UPDATE:
			{
				m_iCurrentFrame += 160;

				if(m_iCurrentFrame >= (70 * 160))
					m_iCurrentFrame = 10 * 160;

				GetMoveLocation(0, 0, 10 * fONE, 0, m_TargetChar->Angle.y + ANGLE_90, 0);
				m_TargetPos.x = m_TargetChar->pX + GeoResult_X;
				m_TargetPos.y = m_TargetChar->pY + m_TargetChar->PatHeight + 5 * fONE;
				m_TargetPos.z = m_TargetChar->pZ + GeoResult_Z;

				D3DVECTOR	attractLocation;
				attractLocation.x = float(m_TargetPos.x - m_CurrentPos.x);
				attractLocation.y = float(m_TargetPos.y - m_CurrentPos.y);
				attractLocation.z = float(m_TargetPos.z - m_CurrentPos.z);
				D3DVECTOR attractDir = attractLocation;


				float length;
				length = (float)sqrt(attractDir.x*attractDir.x + attractDir.y*attractDir.y + attractDir.z*attractDir.z);

				if(length > 300.f)
				{
					m_CurrentPos.x += int(((attractLocation.x) / length)*(length / 15.f));
					m_CurrentPos.y += int(((attractLocation.y) / length)*(length / 15.f));
					m_CurrentPos.z += int(((attractLocation.z) / length)*(length / 15.f));
				}
				else
				{
					if(m_iCurrentFrame == 10 * 160)
						SetFsmState(HoLowLevelPet::FsmState::Idle);
				}
				break;
			}

			case FsmStateEvent::EVENT_EXIT:
			{
				break;
			}
		}
	}
	else if(eFsmState == FsmState::Idle)
	{
		switch(eEvent)
		{
			case FsmStateEvent::EVENT_INIT:
			{
				m_iCurrentFrame = 80 * 160;
				m_bAttackTiming = false;
				break;
			}

			case FsmStateEvent::EVENT_UPDATE:
			{
				m_iCurrentFrame += 160;

				if(m_TargetChar)
				{
					if(m_TargetChar->Flag == 0 && !m_bMyCharacterFlag)
						SetFsmState(HoLowLevelPet::FsmState::Vanish);
				}

				GetMoveLocation(0, 0, 10 * fONE, 0, m_TargetChar->Angle.y + ANGLE_90, 0);
				m_TargetPos.x = m_TargetChar->pX + GeoResult_X;
				m_TargetPos.y = m_TargetChar->pY + m_TargetChar->PatHeight + 5 * fONE;
				m_TargetPos.z = m_TargetChar->pZ + GeoResult_Z;

				D3DVECTOR	attractLocation;
				attractLocation.x = float(m_TargetPos.x - m_CurrentPos.x);
				attractLocation.y = float(m_TargetPos.y - m_CurrentPos.y);
				attractLocation.z = float(m_TargetPos.z - m_CurrentPos.z);
				D3DVECTOR attractDir = attractLocation;


				float length;
				length = (float)sqrt(attractDir.x*attractDir.x + attractDir.y*attractDir.y + attractDir.z*attractDir.z);

				if(length > 300.f)
				{
					m_CurrentPos.x += int(((attractLocation.x) / length)*(length / 15.f));
					m_CurrentPos.y += int(((attractLocation.y) / length)*(length / 15.f));
					m_CurrentPos.z += int(((attractLocation.z) / length)*(length / 15.f));
					if(m_iCurrentFrame >= (70 * 160))
						m_iCurrentFrame = 10 * 160;


				}
				else
				{

					if(m_iCurrentFrame >= (230 * 160))
						m_iCurrentFrame = 80 * 160;
				}

				if(m_TargetChar->chrAttackTarget && m_TargetChar->chrAttackTarget->Flag &&
				   m_TargetChar->chrAttackTarget->smCharInfo.Brood != smCHAR_MONSTER_USER &&
				   m_TargetChar->chrAttackTarget->smCharInfo.Life[0] > 0 && m_TargetChar->chrAttackTarget->smCharInfo.State == smCHAR_STATE_ENEMY &&
				   (m_TargetChar->MotionInfo->State == CHRMOTION_STATE_ATTACK || m_TargetChar->MotionInfo->State == CHRMOTION_STATE_SKILL || m_TargetChar->ShootingFlag) &&
				   m_bAttackTiming == false && m_bMyCharacterFlag)
				{
					m_bAttackTiming = true;
					if(m_Type == Type::Terry || m_Type == Type::Nepsys || m_Type == Type::Io || m_Type == Type::Mute)
					{
						bool flag = false;
						int randomCount = rand() % 100;


						if(m_TargetChar->smCharInfo.Level >= 1 && m_TargetChar->smCharInfo.Level <= 5)
						{
							if(randomCount <= 20) flag = true;
						}
						else if(m_TargetChar->smCharInfo.Level >= 6 && m_TargetChar->smCharInfo.Level <= 9)
						{
							if(randomCount <= 23) flag = true;
						}
						else if(m_TargetChar->smCharInfo.Level >= 10 && m_TargetChar->smCharInfo.Level <= 120)
						{
							if(randomCount <= 99) flag = true;
						}


						if(flag)
						{
							SetFsmState(HoLowLevelPet::FsmState::SkillPre);
							m_AttackPos.x = m_TargetChar->chrAttackTarget->pX;
							m_AttackPos.y = m_TargetChar->chrAttackTarget->pY + fONE * 20;
							m_AttackPos.z = m_TargetChar->chrAttackTarget->pZ;
							m_AttackChar = m_TargetChar->chrAttackTarget;
						}
					}

				}

				if(m_bMyCharacterFlag)
				{
					if(m_TargetChar->MotionInfo->State != CHRMOTION_STATE_ATTACK &&
					   m_TargetChar->MotionInfo->State != CHRMOTION_STATE_SKILL &&
					   m_TargetChar->ShootingFlag == FALSE)
					{
						m_bAttackTiming = false;
					}
				}

				break;
			}

			case FsmStateEvent::EVENT_EXIT:
			{
				m_bAttackTiming = false;
				break;
			}
		}
	}
	else if(eFsmState == FsmState::SkillPre)
	{
		switch(eEvent)
		{
			case FsmStateEvent::EVENT_INIT:
			{
				GetMoveLocation(0, 0, fONE * 2, 0, m_TargetChar->Angle.y, 0);

				m_TargetPos.x = m_TargetChar->pX + GeoResult_X;
				m_TargetPos.y = m_TargetChar->pY + m_TargetChar->PatHeight + 10 * fONE;
				m_TargetPos.z = m_TargetChar->pZ + GeoResult_Z;
				if(m_Type == Type::Mute)
				{
					if(m_iParticleID != -1)
						g_NewParticleMgr.SetStop(m_iParticleID);
				}
				break;
			}

			case FsmStateEvent::EVENT_UPDATE:
			{
				m_iCurrentFrame += 160;

				if(m_iCurrentFrame >= (70 * 160))
					m_iCurrentFrame = 10 * 160;

				D3DVECTOR	attractLocation;
				attractLocation.x = float(m_TargetPos.x - m_CurrentPos.x);
				attractLocation.y = float(m_TargetPos.y - m_CurrentPos.y);
				attractLocation.z = float(m_TargetPos.z - m_CurrentPos.z);
				D3DVECTOR attractDir = attractLocation;


				float length;
				length = (float)sqrt(attractDir.x*attractDir.x + attractDir.y*attractDir.y + attractDir.z*attractDir.z);

				if(length > 300.f)
				{
					m_CurrentPos.x += int(((attractLocation.x) / length)*(length / 15.f));
					m_CurrentPos.y += int(((attractLocation.y) / length)*(length / 15.f));
					m_CurrentPos.z += int(((attractLocation.z) / length)*(length / 15.f));
				}
				else
					SetFsmState(HoLowLevelPet::FsmState::Skill);
				break;
			}

			case FsmStateEvent::EVENT_EXIT:
			{






				break;
			}
		}
	}
	else if(eFsmState == FsmState::Skill)
	{
		switch(eEvent)
		{
			case FsmStateEvent::EVENT_INIT:
			{
				if(m_Type == Type::Terry || m_Type == Type::Nepsys)
				{
					m_iCurrentFrame = 240 * 160;
				}
				else if(m_Type == Type::Io)
					m_iCurrentFrame = 310 * 160;
				else if(m_Type == Type::Mute)
				{
					m_iCurrentFrame = 310 * 160;
				}

				m_bSkillFlag = false;
				break;
			}

			case FsmStateEvent::EVENT_UPDATE:
			{
				GetMoveLocation(0, 0, fONE * 2, 0, m_TargetChar->Angle.y, 0);
				m_CurrentPos.x = m_TargetChar->pX + GeoResult_X;
				m_CurrentPos.y = m_TargetChar->pY + m_TargetChar->PatHeight + 10 * fONE;
				m_CurrentPos.z = m_TargetChar->pZ + GeoResult_Z;

				if(m_iParticleID != -1 && ObjBip)
				{
					smMATRIX *mWorld;
					AnimObjectTree(ObjBip, m_iCurrentFrame, 0, m_TargetChar->Angle.y, 0);
					mWorld = &ObjBip->mWorld;

					D3DVECTOR partPos;
					partPos.x = float(m_CurrentPos.x + mWorld->_41);
					partPos.y = float(m_CurrentPos.y + mWorld->_43);
					partPos.z = float(m_CurrentPos.z + mWorld->_42);

					g_NewParticleMgr.SetPos(m_iParticleID, partPos);
				}


				m_iCurrentFrame += 160;
				if(m_Type == Type::Terry || m_Type == Type::Nepsys)
				{
					if(m_iCurrentFrame >= (300 * 160))
						SetFsmState(HoLowLevelPet::FsmState::Idle);
				}
				else if(m_Type == Type::Io)
				{
					if(m_iCurrentFrame >= (370 * 160))
						SetFsmState(HoLowLevelPet::FsmState::Idle);
				}
				else if(m_Type == Type::Mute)
				{
					if(m_iCurrentFrame >= (370 * 160))
						SetFsmState(HoLowLevelPet::FsmState::Idle);
				}

				if(m_bSkillFlag == false)
				{
					if(m_Type == Type::Terry)
					{
						if(m_iCurrentFrame >= (270 * 160))
						{
							m_bSkillFlag = true;
							AssaParticle_FireShot(&m_CurrentPos, &m_AttackPos);
							if((rand() % 2) == 0)
								SkillPlaySound(SKILL_SOUND_SKILL_FIREBOLT1, m_CurrentPos.x, m_CurrentPos.y, m_CurrentPos.z);
							else
								SkillPlaySound(SKILL_SOUND_SKILL_FIREBOLT2, m_CurrentPos.x, m_CurrentPos.y, m_CurrentPos.z);

							if(m_bMyCharacterFlag && m_AttackChar &&
							   m_AttackChar->smCharInfo.Life[0] > 0 &&
							   m_AttackChar->smCharInfo.State == smCHAR_STATE_ENEMY)
							{
								g_LowLevelPetAttackSerial = m_AttackChar->dwObjectSerial;
								SendLowLevelPetDamage(m_AttackChar, Type::Terry);
							}
							m_AttackChar = NULL;
						}
					}
					else if(m_Type == Type::Nepsys)
					{
						if(m_iCurrentFrame >= (270 * 160))
						{
							m_bSkillFlag = true;
							AssaParticle_IceShot(&m_CurrentPos, &m_AttackPos);
							if((rand() % 2) == 0)
								SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_ICE1, m_CurrentPos.x, m_CurrentPos.y, m_CurrentPos.z);
							else
								SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_ICE2, m_CurrentPos.x, m_CurrentPos.y, m_CurrentPos.z);

							if(m_bMyCharacterFlag && m_AttackChar &&
							   m_AttackChar->smCharInfo.Life[0] > 0 &&
							   m_AttackChar->smCharInfo.State == smCHAR_STATE_ENEMY)
							{
								g_LowLevelPetAttackSerial = m_AttackChar->dwObjectSerial;
								SendLowLevelPetDamage(m_AttackChar, Type::Nepsys);
							}

							m_AttackChar = NULL;
						}
					}
					else if(m_Type == Type::Io)
					{
						if(m_iCurrentFrame >= (340 * 160))
						{
							m_bSkillFlag = true;
							AssaParticle_LightShot(&m_CurrentPos, &m_AttackPos);
							if((rand() % 2) == 0)
								SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_LIGHTNING1, m_CurrentPos.x, m_CurrentPos.y, m_CurrentPos.z);
							else
								SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_LIGHTNING2, m_CurrentPos.x, m_CurrentPos.y, m_CurrentPos.z);

							if(m_bMyCharacterFlag && m_AttackChar &&
							   m_AttackChar->smCharInfo.Life[0] > 0 &&
							   m_AttackChar->smCharInfo.State == smCHAR_STATE_ENEMY)
							{
								g_LowLevelPetAttackSerial = m_AttackChar->dwObjectSerial;
								SendLowLevelPetDamage(m_AttackChar, Type::Io);
							}

							m_AttackChar = NULL;
						}
					}



					else if(m_Type == Type::Mute)
					{
						if(m_iCurrentFrame >= (340 * 160))
						{
							m_bSkillFlag = true;
							AssaParticle_LightShot(&m_CurrentPos, &m_AttackPos);
							if((rand() % 2) == 0)
								SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_LIGHTNING1, m_CurrentPos.x, m_CurrentPos.y, m_CurrentPos.z);
							else
								SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_LIGHTNING2, m_CurrentPos.x, m_CurrentPos.y, m_CurrentPos.z);

							if(m_bMyCharacterFlag && m_AttackChar &&
							   m_AttackChar->smCharInfo.Life[0] > 0 &&
							   m_AttackChar->smCharInfo.State == smCHAR_STATE_ENEMY)
							{
								g_LowLevelPetAttackSerial = m_AttackChar->dwObjectSerial;
								SendLowLevelPetDamage(m_AttackChar, Type::Mute);
							}

							m_AttackChar = NULL;
						}
					}





				}
				break;
			}

			case FsmStateEvent::EVENT_EXIT:
			{
				m_bSkillFlag = false;
				if(m_iParticleID != -1)
				{
					g_NewParticleMgr.SetStop(m_iParticleID);
					m_iParticleID = -1;
				}
				ObjBip = NULL;
				break;
			}
		}
	}
	else if(eFsmState == FsmState::Vanish)
	{
		switch(eEvent)
		{
			case FsmStateEvent::EVENT_INIT:
			{
				GetMoveLocation(0, 0, 50 * fONE, 0, m_TargetChar->Angle.y + ANGLE_45, 0);

				m_TargetPos.x = m_TargetChar->pX + GeoResult_X;
				m_TargetPos.y = m_TargetChar->pY + m_TargetChar->PatHeight + 10 * fONE;
				m_TargetPos.z = m_TargetChar->pZ + GeoResult_Z;

				break;
			}

			case FsmStateEvent::EVENT_UPDATE:
			{
				m_iCurrentFrame += 160;

				if(m_iCurrentFrame >= (70 * 160))
					m_iCurrentFrame = 10 * 160;

				D3DVECTOR	attractLocation;
				attractLocation.x = float(m_TargetPos.x - m_CurrentPos.x);
				attractLocation.y = float(m_TargetPos.y - m_CurrentPos.y);
				attractLocation.z = float(m_TargetPos.z - m_CurrentPos.z);
				D3DVECTOR attractDir = attractLocation;


				float length;
				length = (float)sqrt(attractDir.x*attractDir.x + attractDir.y*attractDir.y + attractDir.z*attractDir.z);

				if(length > 300.f)
				{
					m_CurrentPos.x += int(((attractLocation.x) / length)*(length / 15.f));
					m_CurrentPos.y += int(((attractLocation.y) / length)*(length / 15.f));
					m_CurrentPos.z += int(((attractLocation.z) / length)*(length / 15.f));
				}
				else
					SetFsmState(HoLowLevelPet::FsmState::None);
				break;
			}

			case FsmStateEvent::EVENT_EXIT:
			{
				if(m_iParticleID != -1)
				{
					g_NewParticleMgr.SetStop(m_iParticleID);
					m_iParticleID = -1;
				}

				break;
			}
		}
	}
}

void HoLowLevelPet::SetFsmAttackState(smCHAR *pAttackChar)
{
	SetFsmState(HoLowLevelPet::FsmState::SkillPre);
	m_AttackPos.x = pAttackChar->pX;
	m_AttackPos.y = pAttackChar->pY + fONE * 20;
	m_AttackPos.z = pAttackChar->pZ;
}

void HoLowLevelPet::SetFsmHealState(smCHAR *pHealChar)
{
	SetFsmState(HoLowLevelPet::FsmState::SkillPre);
	m_AttackPos.x = pHealChar->pX;
	m_AttackPos.y = pHealChar->pY + fONE * 20;
	m_AttackPos.z = pHealChar->pZ;

}

HoLowLevelPet::FsmState HoLowLevelPet::GetFsmState()
{
	return m_eCurrentFsmState;
}

HoLowLevelPet::Type HoLowLevelPet::GetType()
{
	return m_Type;
}

void HoLowLevelPet::SetFsmState(HoLowLevelPet::FsmState eFsmState)
{
	m_bFsmChangeFlag = true;
	m_eNextFsmState = eFsmState;
}






void HoLowLevelPet::SetSpawn(smCHAR *pAttachChar, HoLowLevelPet::Type type, smPAT3D *meshRes, smPAT3D *boneRes)
{
	m_TargetChar = pAttachChar;
	m_Type = type;
	m_PetMeshRes = meshRes;
	m_PetBoneRes = boneRes;
	m_eCurrentFsmState = HoLowLevelPet::FsmState::Spawn;
	if(pAttachChar == lpCurPlayer)
		m_bMyCharacterFlag = true;
	else
		m_bMyCharacterFlag = false;

	SetFsmState(HoLowLevelPet::FsmState::Spawn);
	m_iParticleID = -1;
	ObjBip = NULL;
}

void HoLowLevelPet::SetIdle(smCHAR *pAttachChar, HoLowLevelPet::Type type, smPAT3D *meshRes, smPAT3D *boneRes, smCHAR *pAttackChar)
{
	m_TargetChar = pAttachChar;
	m_Type = type;
	m_PetMeshRes = meshRes;
	m_PetBoneRes = boneRes;
	m_eCurrentFsmState = HoLowLevelPet::FsmState::Idle;
	if(pAttachChar == lpCurPlayer)
		m_bMyCharacterFlag = true;
	else
		m_bMyCharacterFlag = false;

	SetFsmState(HoLowLevelPet::FsmState::Idle);
	m_iParticleID = -1;
	ObjBip = NULL;


	m_CurrentPos.x = m_TargetChar->pX;
	m_CurrentPos.y = m_TargetChar->pY + m_TargetChar->PatHeight + 5 * fONE;
	m_CurrentPos.z = m_TargetChar->pZ;

	m_TargetPos.x = m_CurrentPos.x;
	m_TargetPos.y = m_CurrentPos.y;
	m_TargetPos.z = m_CurrentPos.z;

}

smCHAR *HoLowLevelPet::GetAttachChar()
{
	return m_TargetChar;
}







HoLowLevelPetManager::HoLowLevelPetManager() : m_Bone(NULL),
m_MeshTerry(NULL),
m_MeshNepsys(NULL),
m_MeshIo(NULL),
m_MeshMute(NULL)
{
	g_LowLevelPetAttackSerial = 0;
}

HoLowLevelPetManager::~HoLowLevelPetManager()
{
	Destroy();
}






bool HoLowLevelPetManager::Create()
{
	Destroy();
	m_Bone = smASE_ReadBone("Effect\\LowLevelPet\\Pet_motion.ASE");
	smASE_SetPhysique(m_Bone);

	m_MeshTerry = smASE_Read("Effect\\LowLevelPet\\Pet_terry.ASE", 0);
	m_MeshNepsys = smASE_Read("Effect\\LowLevelPet\\Pet_nepsys.ASE", 0);
	m_MeshIo = smASE_Read("Effect\\LowLevelPet\\Pet_io.ASE", 0);
	m_MeshMute = smASE_Read("Effect\\LowLevelPet\\Pet_mute.ASE", 0);

	return true;
}


bool HoLowLevelPetManager::Destroy()
{
	if(m_Bone != NULL)
	{
		if(m_MeshTerry)
		{
			delete m_MeshTerry;
			m_MeshTerry = NULL;
		}

		if(m_MeshNepsys)
		{
			delete m_MeshNepsys;
			m_MeshNepsys = NULL;
		}

		if(m_MeshIo)
		{
			delete m_MeshIo;
			m_MeshIo = NULL;
		}

		if(m_MeshMute)
		{
			delete m_MeshMute;
			m_MeshMute = NULL;
		}

		delete m_Bone;
		m_Bone = NULL;
	}
	return true;
}






bool HoLowLevelPetManager::AddPet(smCHAR *pAttachChar, HoLowLevelPet::Type petType)
{
	HoLowLevelPet *lowLevelPet = GetEmptyPet(pAttachChar);
	if(lowLevelPet)
	{
		if(petType == HoLowLevelPet::Type::Terry)
			lowLevelPet->SetSpawn(pAttachChar, petType, m_MeshTerry, m_Bone);
		else if(petType == HoLowLevelPet::Type::Nepsys)
			lowLevelPet->SetSpawn(pAttachChar, petType, m_MeshNepsys, m_Bone);
		else if(petType == HoLowLevelPet::Type::Io)
			lowLevelPet->SetSpawn(pAttachChar, petType, m_MeshIo, m_Bone);
		else if(petType == HoLowLevelPet::Type::Mute)
			lowLevelPet->SetSpawn(pAttachChar, petType, m_MeshMute, m_Bone);

		return true;
	}

	return false;
}


bool HoLowLevelPetManager::AddIdlePet(smCHAR *pAttachChar, int petType, smCHAR *pAttackChar)
{
	HoLowLevelPet *lowLevelPet = GetEmptyIdlePet(pAttachChar, petType, pAttackChar);
	if(lowLevelPet)
	{
		if(petType == HoLowLevelPet::Type::Terry)
			lowLevelPet->SetSpawn(pAttachChar, HoLowLevelPet::Type::Terry, m_MeshTerry, m_Bone);
		else if(petType == HoLowLevelPet::Type::Nepsys)
			lowLevelPet->SetSpawn(pAttachChar, HoLowLevelPet::Type::Nepsys, m_MeshNepsys, m_Bone);
		else if(petType == HoLowLevelPet::Type::Io)
			lowLevelPet->SetSpawn(pAttachChar, HoLowLevelPet::Type::Io, m_MeshIo, m_Bone);
		else if(petType == HoLowLevelPet::Type::Mute)
			lowLevelPet->SetSpawn(pAttachChar, HoLowLevelPet::Type::Mute, m_MeshMute, m_Bone);

		return true;
	}

	return false;
}






void HoLowLevelPetManager::DeletePet(smCHAR *pAttachChar)
{
	for(int i = 0; i < MAX_LOWLEVEL_PET; i++)
	{
		if(LowLevelPetList[i].GetFsmState() != HoLowLevelPet::FsmState::None)
		{
			if(LowLevelPetList[i].GetAttachChar() == pAttachChar)
				LowLevelPetList[i].SetFsmState(HoLowLevelPet::FsmState::Vanish);
		}
	}
}







HoLowLevelPet *HoLowLevelPetManager::GetEmptyPet(smCHAR *pAttachChar)
{
	for(int i = 0; i < MAX_LOWLEVEL_PET; i++)
	{
		if(LowLevelPetList[i].GetFsmState() != HoLowLevelPet::FsmState::None)
		{
			if(LowLevelPetList[i].GetAttachChar() == pAttachChar)
				LowLevelPetList[i].SetFsmState(HoLowLevelPet::FsmState::Vanish);
		}
	}

	for(int i = 0; i < MAX_LOWLEVEL_PET; i++)
	{
		if(LowLevelPetList[i].GetFsmState() == HoLowLevelPet::FsmState::None)
			return &LowLevelPetList[i];
	}

	return NULL;
}








HoLowLevelPet *HoLowLevelPetManager::GetEmptyIdlePet(smCHAR *pAttachChar, int petType, smCHAR *pAttackChar)
{
	for(int i = 0; i < MAX_LOWLEVEL_PET; i++)
	{
		if(LowLevelPetList[i].GetFsmState() != HoLowLevelPet::FsmState::None)
		{
			if(LowLevelPetList[i].GetAttachChar() == pAttachChar)
			{
				if(pAttachChar != NULL)
				{
					if(pAttackChar != NULL)
					{
						if(LowLevelPetList[i].GetType() != HoLowLevelPet::Mute)
							LowLevelPetList[i].SetFsmAttackState(pAttackChar);
						else
							LowLevelPetList[i].SetFsmHealState(pAttackChar);

					}
				}
				return NULL;
			}
		}
	}

	for(int i = 0; i < MAX_LOWLEVEL_PET; i++)
	{
		if(LowLevelPetList[i].GetFsmState() == HoLowLevelPet::FsmState::None)
			return &LowLevelPetList[i];
	}

	return NULL;
}


bool HoLowLevelPetManager::Draw(int x, int y, int z, int angleX, int angleY, int angleZ)
{
	for(int i = 0; i < MAX_LOWLEVEL_PET; i++)
	{
		if(LowLevelPetList[i].GetFsmState() != HoLowLevelPet::FsmState::None)
			LowLevelPetList[i].Draw(x, y, z, angleX, angleY, angleZ);
	}
	return true;
}


bool HoLowLevelPetManager::Main()
{
	for(int i = 0; i < MAX_LOWLEVEL_PET; i++)
	{
		if(LowLevelPetList[i].GetFsmState() != HoLowLevelPet::FsmState::None)
			LowLevelPetList[i].Main();
	}

	return true;
}





static HoLowLevelPetManager s_LowLevelPetManager;

bool g_CreatePetSystem()
{
	s_LowLevelPetManager.Create();
	return true;
}

bool g_MainPetSystem()
{
	s_LowLevelPetManager.Main();
	return true;
}

bool g_DrawPetSystem(int x, int y, int z, int ax, int ay, int az)
{
	s_LowLevelPetManager.Draw(x, y, z, ax, ay, az);
	return true;
}

bool g_DestroyPetSystem()
{
	s_LowLevelPetManager.Destroy();
	return true;
}

bool g_LowLevelAddPet(smCHAR *pAttachChar, HoLowLevelPet::Type petType)
{
	s_LowLevelPetManager.AddPet(pAttachChar, petType);
	return true;
}

bool g_LowLevelAddIdlePet(smCHAR *pAttachChar, int petType, smCHAR *pAttackChar)
{
	s_LowLevelPetManager.AddIdlePet(pAttachChar, petType, pAttackChar);

	return true;
}


void g_LowLevelDeletePet(smCHAR *pAttachChar)
{
	s_LowLevelPetManager.DeletePet(pAttachChar);
}