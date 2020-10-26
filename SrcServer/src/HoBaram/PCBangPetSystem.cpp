#include "SinBaram\\SinLinkHeader.h"
#include "PCBangPetSystem.h"
#include "..\\playmain.h"
#include "hoAssaParticleEffect.h"
#include "HoNewParticleLinkHeader.h"
#include "..\\effectsnd.h"
POINT3D HoPcBangPetRenderPoint;
#include "..\\damage.h"

DWORD	g_HoPCBangPetAttackSerial = 0;
HoPCBangPet::HoPCBangPet() : m_Type(HoPCBangPet::BurstP),
m_PetMeshRes(NULL),
m_PetBoneRes(NULL),
m_bFsmChangeFlag(false),
m_eCurrentFsmState(PCBang_FsmState::None),
m_eNextFsmState(PCBang_FsmState::None),
m_TargetChar(NULL),
m_iCurrentFrame(80 * 160),
m_bMyCharacterFlag(false),
m_bPetAttacking(false),
m_AttackCharTarget(NULL)
{

}

HoPCBangPet::~HoPCBangPet()
{

}

bool HoPCBangPet::Draw(int x, int y, int z, int angleX, int angleY, int angleZ)
{
	if(m_eCurrentFsmState != PCBang_FsmState::None)
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
		if(m_bPetAttacking)
		{
			GetRadian3D(x, y, z, m_AttackPos.x, m_AttackPos.y, m_AttackPos.z);
			petAngle.x = GeoResult_X;
			petAngle.y = (ANGLE_180 - GeoResult_Y)&ANGCLIP;
			petAngle.z = 0;
		}
		else
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
			HoPcBangPetRenderPoint.z = smRender.GetRect2D(m_CurrentPos.x, m_CurrentPos.y + (He >> 1), m_CurrentPos.z, 44 * fONE, He, &PetRendRect2D, &sPos);
			HoPcBangPetRenderPoint.x = sPos.x;
			HoPcBangPetRenderPoint.y = sPos.y;

		}
	}
	return true;
}


bool HoPCBangPet::Main()
{
	if(GetFsmState() != PCBang_FsmState::None)
	{
		if(m_bMyCharacterFlag)
		{
			if(m_TargetChar != lpCurPlayer)
				m_TargetChar = lpCurPlayer;
		}

		FsmEventProcess(PCBang_FsmStateEvent::EVENT_UPDATE);
	}
	return true;
}

void HoPCBangPet::FsmEventProcess(PCBang_FsmStateEvent eStateEvent)
{
	OnEvent(eStateEvent, m_eCurrentFsmState);


	int safetyCount = 10;
	while(m_bFsmChangeFlag && (--safetyCount >= 0))
	{


		m_bFsmChangeFlag = false;


		OnEvent(PCBang_FsmStateEvent::EVENT_EXIT, m_eCurrentFsmState);


		m_eCurrentFsmState = m_eNextFsmState;


		OnEvent(PCBang_FsmStateEvent::EVENT_INIT, m_eCurrentFsmState);
	}
}










void HoPCBangPet::OnEvent(PCBang_FsmStateEvent eEvent, PCBang_FsmState eFsmState)
{
	if(eFsmState == PCBang_FsmState::Spawn)
	{
		switch(eEvent)
		{
			case PCBang_FsmStateEvent::EVENT_INIT:
			{

				GetMoveLocation(0, 0, 50 * fONE, 0, m_TargetChar->Angle.y + ANGLE_45, 0);

				m_CurrentPos.x = m_TargetChar->pX + GeoResult_X;
				m_CurrentPos.y = m_TargetChar->pY + m_TargetChar->PatHeight + 10 * fONE;
				m_CurrentPos.z = m_TargetChar->pZ + GeoResult_Z;

				break;
			}

			case PCBang_FsmStateEvent::EVENT_UPDATE:
			{
				m_iCurrentFrame += 160;

				if(m_iCurrentFrame >= (145 * 160))
					m_iCurrentFrame = 80 * 160;


				GetMoveLocation(0, 0, -10 * fONE, 0, m_TargetChar->Angle.y + ANGLE_90, 0);
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
					if(m_iCurrentFrame == 80 * 160)
						SetFsmState(HoPCBangPet::PCBang_FsmState::Idle);
				}
				break;
			}

			case PCBang_FsmStateEvent::EVENT_EXIT:
			{
				break;
			}
		}
	}
	else if(eFsmState == PCBang_FsmState::Idle)
	{
		switch(eEvent)
		{
			case PCBang_FsmStateEvent::EVENT_INIT:
			{
				m_iCurrentFrame = 10 * 160;
				m_bAttackTiming = false;
				break;
			}

			case PCBang_FsmStateEvent::EVENT_UPDATE:
			{
				m_iCurrentFrame += 160;

				if(m_TargetChar)
				{
					if(m_TargetChar->Flag == 0 && !m_bMyCharacterFlag)
						SetFsmState(HoPCBangPet::PCBang_FsmState::Vanish);
				}


				GetMoveLocation(0, 0, -10 * fONE, 0, m_TargetChar->Angle.y + ANGLE_90, 0);
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
					if(m_iCurrentFrame >= (145 * 160))
						m_iCurrentFrame = 80 * 160;


				}
				else
				{

					if(m_iCurrentFrame >= (74 * 160))
						m_iCurrentFrame = 10 * 160;
				}

				if(!m_bPetAttacking)
				{
					if(m_TargetChar->chrAttackTarget && m_TargetChar->chrAttackTarget->smCharInfo.Brood != smCHAR_MONSTER_USER &&
					   m_TargetChar->chrAttackTarget->smCharInfo.Life[0] > 0 && m_TargetChar->chrAttackTarget->smCharInfo.State == smCHAR_STATE_ENEMY &&
					   (m_TargetChar->MotionInfo->State == CHRMOTION_STATE_ATTACK || m_TargetChar->MotionInfo->State == CHRMOTION_STATE_SKILL || m_TargetChar->ShootingFlag) &&
					   m_bAttackTiming == false && m_bMyCharacterFlag)
					{
						m_bAttackTiming = true;




						m_bPetAttacking = true;

						if(m_AttackCharTarget == NULL || m_AttackCharTarget != m_TargetChar->chrAttackTarget)
						{
							m_AttackCharTarget = m_TargetChar->chrAttackTarget;
						}



					}
				}

				if(m_bPetAttacking)
				{

					if(m_AttackCharTarget && m_AttackCharTarget->smCharInfo.Life[0] > 0 &&
					   m_AttackCharTarget->smCharInfo.State == smCHAR_STATE_ENEMY && PetNearMonster(m_AttackCharTarget))
					{



						SetFsmState(HoPCBangPet::PCBang_FsmState::SkillPre);
						m_AttackPos.x = m_AttackCharTarget->pX;
						m_AttackPos.y = m_AttackCharTarget->pY + fONE * 20;
						m_AttackPos.z = m_AttackCharTarget->pZ;
						m_AttackChar = m_AttackCharTarget;

					}
					else
					{
						m_AttackCharTarget = NULL;
						m_bPetAttacking = false;
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

			case PCBang_FsmStateEvent::EVENT_EXIT:
			{
				m_bAttackTiming = false;
				break;
			}
		}
	}
	else if(eFsmState == PCBang_FsmState::SkillPre)
	{
		switch(eEvent)
		{
			case PCBang_FsmStateEvent::EVENT_INIT:
			{

				GetMoveLocation(0, 0, -fONE * 2, 0, m_TargetChar->Angle.y, 0);

				m_TargetPos.x = m_TargetChar->pX + GeoResult_X;
				m_TargetPos.y = m_TargetChar->pY + m_TargetChar->PatHeight + 10 * fONE;
				m_TargetPos.z = m_TargetChar->pZ + GeoResult_Z;
				if(m_Type == Type::BurstD)
				{
					if(m_iParticleID != -1)
						g_NewParticleMgr.SetStop(m_iParticleID);
				}
				break;
			}

			case PCBang_FsmStateEvent::EVENT_UPDATE:
			{
				m_iCurrentFrame += 160;

				if(m_iCurrentFrame >= (145 * 160))
					m_iCurrentFrame = 80 * 160;

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
					SetFsmState(HoPCBangPet::PCBang_FsmState::Skill);
				break;
			}

			case PCBang_FsmStateEvent::EVENT_EXIT:
			{
				if(m_Type == Type::BurstD)
				{
					m_iParticleID = g_NewParticleMgr.Start("Skill3MagicianSpiritElemental", m_CurrentPos);
					ObjBip = m_PetBoneRes->GetObjectFromName("Bip01");
					SkillPlaySound(SKILL_SOUND_SKILL_HEALING, m_CurrentPos.x, m_CurrentPos.y, m_CurrentPos.z);
				}
				break;
			}
		}
	}
	else if(eFsmState == PCBang_FsmState::Skill)
	{
		switch(eEvent)
		{
			case PCBang_FsmStateEvent::EVENT_INIT:
			{
				if(m_Type == Type::BurstP || m_Type == Type::BurstS)
				{
					m_iCurrentFrame = 150 * 160;
				}
				else if(m_Type == Type::BurstL)
					m_iCurrentFrame = 150 * 160;
				else if(m_Type == Type::BurstD)
				{
					m_iCurrentFrame = 150 * 160;
				}

				m_bSkillFlag = false;
				break;
			}

			case PCBang_FsmStateEvent::EVENT_UPDATE:
			{

				GetMoveLocation(0, 0, -fONE * 2, 0, m_TargetChar->Angle.y, 0);
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


				m_iCurrentFrame += 80;
				if(m_Type == Type::BurstP || m_Type == Type::BurstS)
				{

					if(m_iCurrentFrame >= (200 * 160))
						SetFsmState(HoPCBangPet::PCBang_FsmState::Idle);
				}
				else if(m_Type == Type::BurstL)
				{
					if(m_iCurrentFrame >= (200 * 160))
						SetFsmState(HoPCBangPet::PCBang_FsmState::Idle);
				}
				else if(m_Type == Type::BurstD)
				{
					if(m_iCurrentFrame >= (200 * 160))
						SetFsmState(HoPCBangPet::PCBang_FsmState::Idle);
				}

				if(m_bSkillFlag == false)
				{
					if(m_Type == Type::BurstP)
					{
						if(m_iCurrentFrame >= (180 * 160))
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
								g_HoPCBangPetAttackSerial = m_AttackChar->dwObjectSerial;
								SendPCBangPetDamage(m_AttackChar, Type::BurstP);
							}
							m_AttackChar = NULL;
						}
					}
					else if(m_Type == Type::BurstS)
					{
						if(m_iCurrentFrame >= (180 * 160))
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
								g_HoPCBangPetAttackSerial = m_AttackChar->dwObjectSerial;
								SendPCBangPetDamage(m_AttackChar, Type::BurstS);
							}

							m_AttackChar = NULL;
						}
					}
					else if(m_Type == Type::BurstL)
					{
						if(m_iCurrentFrame >= (180 * 160))
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
								g_HoPCBangPetAttackSerial = m_AttackChar->dwObjectSerial;
								SendPCBangPetDamage(m_AttackChar, Type::BurstL);
							}

							m_AttackChar = NULL;
						}
					}
					else if(m_Type == Type::BurstD)
					{
						if(m_iCurrentFrame >= (180 * 160) && m_bMyCharacterFlag)
						{
							m_bSkillFlag = true;
							sinSetLife(sinGetLife() + 10 + short(m_TargetChar->smCharInfo.Level / 2));
							if(m_TargetChar)
								g_HoPCBangPetAttackSerial = m_TargetChar->dwObjectSerial;

						}
					}

				}
				break;
			}

			case PCBang_FsmStateEvent::EVENT_EXIT:
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
	else if(eFsmState == PCBang_FsmState::Vanish)
	{
		switch(eEvent)
		{
			case PCBang_FsmStateEvent::EVENT_INIT:
			{

				GetMoveLocation(0, 0, -50 * fONE, 0, m_TargetChar->Angle.y + ANGLE_45, 0);

				m_TargetPos.x = m_TargetChar->pX + GeoResult_X;
				m_TargetPos.y = m_TargetChar->pY + m_TargetChar->PatHeight + 10 * fONE;
				m_TargetPos.z = m_TargetChar->pZ + GeoResult_Z;

				break;
			}

			case PCBang_FsmStateEvent::EVENT_UPDATE:
			{
				m_iCurrentFrame += 160;

				if(m_iCurrentFrame >= (145 * 160))
					m_iCurrentFrame = 80 * 160;

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
					SetFsmState(HoPCBangPet::PCBang_FsmState::None);
				break;
			}

			case PCBang_FsmStateEvent::EVENT_EXIT:
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


BOOL HoPCBangPet::PetNearMonster(smCHAR *lpNearMonster)
{
	int dist, x, y, z;
	int	NearDist;

	NearDist = 300 * 300;

	if(!lpNearMonster) return FALSE;
	if(!lpCurPlayer) return FALSE;


	if(lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_ATTACK && lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_SKILL && !lpCurPlayer->ShootingFlag) return FALSE;



	x = (lpCurPlayer->pX - lpNearMonster->pX) >> FLOATNS;
	y = (lpCurPlayer->pY - lpNearMonster->pY) >> FLOATNS;
	z = (lpCurPlayer->pZ - lpNearMonster->pZ) >> FLOATNS;

	dist = x*x + z*z + y*y;
	if(dist < NearDist)
		return TRUE;
	else
		return FALSE;


}


void HoPCBangPet::SetFsmAttackState(smCHAR *pAttackChar)
{
	SetFsmState(HoPCBangPet::PCBang_FsmState::SkillPre);
	m_AttackPos.x = pAttackChar->pX;
	m_AttackPos.y = pAttackChar->pY + fONE * 20;
	m_AttackPos.z = pAttackChar->pZ;
}

void HoPCBangPet::SetFsmHealState(smCHAR *pHealChar)
{
	SetFsmState(HoPCBangPet::PCBang_FsmState::SkillPre);
	m_AttackPos.x = pHealChar->pX;
	m_AttackPos.y = pHealChar->pY + fONE * 20;
	m_AttackPos.z = pHealChar->pZ;

}

HoPCBangPet::PCBang_FsmState HoPCBangPet::GetFsmState()
{
	return m_eCurrentFsmState;
}

HoPCBangPet::Type HoPCBangPet::GetType()
{
	return m_Type;
}

void HoPCBangPet::SetFsmState(HoPCBangPet::PCBang_FsmState eFsmState)
{
	m_bFsmChangeFlag = true;
	m_eNextFsmState = eFsmState;
}






void HoPCBangPet::SetSpawn(smCHAR *pAttachChar, HoPCBangPet::Type type, smPAT3D *meshRes, smPAT3D *boneRes)
{
	m_TargetChar = pAttachChar;
	m_Type = type;
	m_PetMeshRes = meshRes;
	m_PetBoneRes = boneRes;
	m_eCurrentFsmState = HoPCBangPet::PCBang_FsmState::Spawn;
	if(pAttachChar == lpCurPlayer)
		m_bMyCharacterFlag = true;
	else
		m_bMyCharacterFlag = false;

	SetFsmState(HoPCBangPet::PCBang_FsmState::Spawn);
	m_iParticleID = -1;
	ObjBip = NULL;
}

void HoPCBangPet::SetIdle(smCHAR *pAttachChar, HoPCBangPet::Type type, smPAT3D *meshRes, smPAT3D *boneRes, smCHAR *pAttackChar)
{
	m_TargetChar = pAttachChar;
	m_Type = type;
	m_PetMeshRes = meshRes;
	m_PetBoneRes = boneRes;
	m_eCurrentFsmState = HoPCBangPet::PCBang_FsmState::Idle;
	if(pAttachChar == lpCurPlayer)
		m_bMyCharacterFlag = true;
	else
		m_bMyCharacterFlag = false;

	SetFsmState(HoPCBangPet::PCBang_FsmState::Idle);
	m_iParticleID = -1;
	ObjBip = NULL;


	m_CurrentPos.x = m_TargetChar->pX;
	m_CurrentPos.y = m_TargetChar->pY + m_TargetChar->PatHeight + 5 * fONE;
	m_CurrentPos.z = m_TargetChar->pZ;

	m_TargetPos.x = m_CurrentPos.x;
	m_TargetPos.y = m_CurrentPos.y;
	m_TargetPos.z = m_CurrentPos.z;

}

smCHAR *HoPCBangPet::GetAttachChar()
{
	return m_TargetChar;
}

HoPCBangPetManager::HoPCBangPetManager() : m_BoneBurstP(NULL),
m_BoneBurstS(NULL),
m_BoneBurstL(NULL),
m_BoneBurstD(NULL),
m_MeshBurstP(NULL),
m_MeshBurstS(NULL),
m_MeshBurstL(NULL),
m_MeshBurstD(NULL)
{
	g_HoPCBangPetAttackSerial = 0;
}

HoPCBangPetManager::~HoPCBangPetManager()
{
	Destroy();
}






bool HoPCBangPetManager::Create()
{
	Destroy();
	m_BoneBurstP = smASE_ReadBone("Effect\\PcBangPet\\Pet_Phoenimin\\Phoenix.ASE");
	smASE_SetPhysique(m_BoneBurstP);
	m_BoneBurstS = smASE_ReadBone("Effect\\PcBangPet\\Pet_Phoenimin\\Phoenix.ASE");
	smASE_SetPhysique(m_BoneBurstS);
	m_BoneBurstL = smASE_ReadBone("Effect\\PcBangPet\\Pet_Phoenimin\\Phoenix.ASE");
	smASE_SetPhysique(m_BoneBurstL);
	m_BoneBurstD = smASE_ReadBone("Effect\\PcBangPet\\Pet_Phoenimin\\Phoenix.ASE");
	smASE_SetPhysique(m_BoneBurstD);


	m_MeshBurstP = smASE_Read("Effect\\PcBangPet\\Pet_Phoenimin\\Phoenix.ASE", 0);
	m_MeshBurstS = smASE_Read("Effect\\PcBangPet\\Pet_Phoenimin\\Phoenix.ASE", 0);
	m_MeshBurstL = smASE_Read("Effect\\PcBangPet\\Pet_Phoenimin\\Phoenix.ASE", 0);
	m_MeshBurstD = smASE_Read("Effect\\PcBangPet\\Pet_Phoenimin\\Phoenix.ASE", 0);

	return true;
}


bool HoPCBangPetManager::Destroy()
{
	if(m_BoneBurstP != NULL)
	{
		if(m_MeshBurstP)
		{
			delete m_MeshBurstP;
			m_MeshBurstP = NULL;
		}

		delete m_BoneBurstP;
		m_BoneBurstP = NULL;
	}

	if(m_BoneBurstS != NULL)
	{
		if(m_MeshBurstS)
		{
			delete m_MeshBurstS;
			m_MeshBurstS = NULL;
		}

		delete m_BoneBurstS;
		m_BoneBurstS = NULL;
	}

	if(m_BoneBurstL != NULL)
	{
		if(m_MeshBurstL)
		{
			delete m_MeshBurstL;
			m_MeshBurstL = NULL;
		}

		delete m_BoneBurstL;
		m_BoneBurstL = NULL;
	}

	if(m_BoneBurstD != NULL)
	{
		if(m_MeshBurstD)
		{
			delete m_MeshBurstD;
			m_MeshBurstD = NULL;
		}

		delete m_BoneBurstD;
		m_BoneBurstD = NULL;
	}

	return true;
}






bool HoPCBangPetManager::AddPet(smCHAR *pAttachChar, HoPCBangPet::Type petType)
{
	HoPCBangPet *lowLevelPet = GetEmptyPet(pAttachChar);
	if(lowLevelPet)
	{
		if(petType == HoPCBangPet::Type::BurstP)
			lowLevelPet->SetSpawn(pAttachChar, petType, m_MeshBurstP, m_BoneBurstP);
		else if(petType == HoPCBangPet::Type::BurstS)
			lowLevelPet->SetSpawn(pAttachChar, petType, m_MeshBurstS, m_BoneBurstS);
		else if(petType == HoPCBangPet::Type::BurstL)
			lowLevelPet->SetSpawn(pAttachChar, petType, m_MeshBurstL, m_BoneBurstL);
		else if(petType == HoPCBangPet::Type::BurstD)
			lowLevelPet->SetSpawn(pAttachChar, petType, m_MeshBurstD, m_BoneBurstD);

		return true;
	}

	return false;
}


bool HoPCBangPetManager::AddIdlePet(smCHAR *pAttachChar, int petType, smCHAR *pAttackChar)
{
	HoPCBangPet *PcBangPet = GetEmptyIdlePet(pAttachChar, petType, pAttackChar);
	if(PcBangPet)
	{
		if(petType == HoPCBangPet::Type::BurstP)
			PcBangPet->SetSpawn(pAttachChar, HoPCBangPet::Type::BurstP, m_MeshBurstP, m_BoneBurstP);
		else if(petType == HoPCBangPet::Type::BurstS)
			PcBangPet->SetSpawn(pAttachChar, HoPCBangPet::Type::BurstS, m_MeshBurstS, m_BoneBurstS);
		else if(petType == HoPCBangPet::Type::BurstL)
			PcBangPet->SetSpawn(pAttachChar, HoPCBangPet::Type::BurstL, m_MeshBurstL, m_BoneBurstL);
		else if(petType == HoPCBangPet::Type::BurstD)
			PcBangPet->SetSpawn(pAttachChar, HoPCBangPet::Type::BurstD, m_MeshBurstD, m_BoneBurstD);


		return true;
	}

	return false;
}






void HoPCBangPetManager::DeletePet(smCHAR *pAttachChar)
{
	for(int i = 0; i < MAX_LOWLEVEL_PET; i++)
	{
		if(PcBangPetList[i].GetFsmState() != HoPCBangPet::PCBang_FsmState::None)
		{
			if(PcBangPetList[i].GetAttachChar() == pAttachChar)
				PcBangPetList[i].SetFsmState(HoPCBangPet::PCBang_FsmState::Vanish);
		}
	}
}







HoPCBangPet *HoPCBangPetManager::GetEmptyPet(smCHAR *pAttachChar)
{
	for(int i = 0; i < MAX_LOWLEVEL_PET; i++)
	{
		if(PcBangPetList[i].GetFsmState() != HoPCBangPet::PCBang_FsmState::None)
		{
			if(PcBangPetList[i].GetAttachChar() == pAttachChar)
				PcBangPetList[i].SetFsmState(HoPCBangPet::PCBang_FsmState::Vanish);
		}
	}

	for(int i = 0; i < MAX_LOWLEVEL_PET; i++)
	{
		if(PcBangPetList[i].GetFsmState() == HoPCBangPet::PCBang_FsmState::None)
			return &PcBangPetList[i];
	}

	return NULL;
}








HoPCBangPet *HoPCBangPetManager::GetEmptyIdlePet(smCHAR *pAttachChar, int petType, smCHAR *pAttackChar)
{
	for(int i = 0; i < MAX_LOWLEVEL_PET; i++)
	{
		if(PcBangPetList[i].GetFsmState() != HoPCBangPet::PCBang_FsmState::None)
		{
			if(PcBangPetList[i].GetAttachChar() == pAttachChar)
			{
				if(pAttachChar != NULL)
				{
					if(pAttackChar != NULL)
					{
						if(PcBangPetList[i].GetType() != HoPCBangPet::BurstD)
							PcBangPetList[i].SetFsmAttackState(pAttackChar);
						else
							PcBangPetList[i].SetFsmHealState(pAttackChar);

					}
				}
				return NULL;
			}
		}
	}

	for(int i = 0; i < MAX_LOWLEVEL_PET; i++)
	{
		if(PcBangPetList[i].GetFsmState() == HoPCBangPet::PCBang_FsmState::None)
			return &PcBangPetList[i];
	}

	return NULL;
}


bool HoPCBangPetManager::Draw(int x, int y, int z, int angleX, int angleY, int angleZ)
{
	for(int i = 0; i < MAX_LOWLEVEL_PET; i++)
	{
		if(PcBangPetList[i].GetFsmState() != HoPCBangPet::PCBang_FsmState::None)
			PcBangPetList[i].Draw(x, y, z, angleX, angleY, angleZ);
	}
	return true;
}


bool HoPCBangPetManager::Main()
{
	for(int i = 0; i < MAX_LOWLEVEL_PET; i++)
	{
		if(PcBangPetList[i].GetFsmState() != HoPCBangPet::PCBang_FsmState::None)
			PcBangPetList[i].Main();
	}

	return true;
}





static HoPCBangPetManager s_PcBangPetManager;

bool g_PCBang_CreatePetSystem()
{
	s_PcBangPetManager.Create();
	return true;
}

bool g_PCBang_MainPetSystem()
{
	s_PcBangPetManager.Main();
	return true;
}

bool g_PCBang_DrawPetSystem(int x, int y, int z, int ax, int ay, int az)
{
	s_PcBangPetManager.Draw(x, y, z, ax, ay, az);
	return true;
}

bool g_PCBang_DestroyPetSystem()
{
	s_PcBangPetManager.Destroy();
	return true;
}

bool g_HoPCBangAddPet(smCHAR *pAttachChar, HoPCBangPet::Type petType)
{
	s_PcBangPetManager.AddPet(pAttachChar, petType);
	return true;
}

bool g_HoPCBangAddIdlePet(smCHAR *pAttachChar, int petType, smCHAR *pAttackChar)
{
	s_PcBangPetManager.AddIdlePet(pAttachChar, petType, pAttackChar);

	return true;
}


void g_HoPCBangDeletePet(smCHAR *pAttachChar)
{
	s_PcBangPetManager.DeletePet(pAttachChar);
}
