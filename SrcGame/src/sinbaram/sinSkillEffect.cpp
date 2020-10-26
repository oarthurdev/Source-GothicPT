
#include "sinLinkHeader.h"

#define SIN_COPY_EFFECT			100


#define SIN_PARTICLE_FARINA			10000
#define SIN_PARTICLE_HOLYBODY		10001
#define SIN_PARTICLE_CROSS			10002
#define SIN_PARTICLE_MULTYSPARK		10003
#define SIN_PARTICLE_MULTYSPARK2	10004
#define SIN_PARTICLE_AGONY			10005
#define SIN_PARTICLE_HOLYMIND		10006
#define SIN_PARTICLE_VIGORSPEAR		10007
#define SIN_PARTICLE_HEALING		10008
#define SIN_PARTICLE_FIREBOLT		10009
#define SIN_PARTICLE_SWORDBLAST		10010
#define SIN_PARTICLE_SWORDBLAST2	10011
#define SIN_PARTICLE_HEALING_GATHER	10012
#define SIN_PARTICLE_HOLYMIND2		10013  
#define SIN_EFFECT_HEALING3			10014
#define SIN_PARTICLE_SHEILDSTRIKE	10015
#define SIN_PARTICLE_ZENITH			10016


#define SIN_EFFECT_BOMB5			20001
#define SIN_EFFECT_START_MAGIC		20002

int Index2 = 0;

int MatFarina[9];
int MatHolyBodyCross[4];
int MatMultiSpark[9];
int MatAgony[9];
int MatHolyMind[4];
int MatHolyMindParticle;
int MatVigorSpear[6];
int MatZenith[5];
int MatFireBolt[3];
int MatBomb6[6];
int MatSwordBlast[2];
int MatHolyBody[2];
int MatShieldStrike[2];

int ShieldStrikeTime;


void sinInitSkillEffect()
{
	int i = 0;
	char *Path = "Image\\SinImage\\Effect\\SkillEffect";
	char szBuff[128];

	for(i = 0; i < 9; i++)
	{
		wsprintf(szBuff, "%s\\Farina\\farina0%d.tga", Path, i);
		MatFarina[i] = CreateTextureMaterial(szBuff, 0, 0, 0, 0, SMMAT_BLEND_LAMP);
	}

	for(i = 0; i < 4; i++)
	{
		wsprintf(szBuff, "%s\\HolyBody\\H_BAP0%d.tga", Path, i);
		MatHolyBodyCross[i] = CreateTextureMaterial(szBuff, 0, 0, 0, 0, SMMAT_BLEND_LAMP);
	}
	for(i = 0; i < 9; i++)
	{
		wsprintf(szBuff, "%s\\MultiSpark\\m_spark0%d.tga", Path, i);
		MatMultiSpark[i] = CreateTextureMaterial(szBuff, 0, 0, 0, 0, SMMAT_BLEND_LAMP);
	}
	for(i = 0; i < 9; i++)
	{
		wsprintf(szBuff, "%s\\Agony\\Agony%d.tga", Path, i);
		MatAgony[i] = CreateTextureMaterial(szBuff, 0, 0, 0, 0, SMMAT_BLEND_LAMP);
	}
	for(i = 0; i < 4; i++)
	{
		wsprintf(szBuff, "%s\\HolyMind\\H_MIND0%d.tga", Path, i);
		MatHolyMind[i] = CreateTextureMaterial(szBuff, 0, 0, 0, 0, SMMAT_BLEND_LAMP);
	}
	wsprintf(szBuff, "%s\\HolyMind\\H_Particle.tga", Path, i);
	MatHolyMindParticle = CreateTextureMaterial(szBuff, 0, 0, 0, 0, SMMAT_BLEND_LAMP);
	for(i = 0; i < 7; i++)
	{
		wsprintf(szBuff, "%s\\VigorSpear\\v_spear0%d.tga", Path, i);
		MatVigorSpear[i] = CreateTextureMaterial(szBuff, 0, 0, 0, 0, SMMAT_BLEND_LAMP);
	}
	for(i = 0; i < 5; i++)
	{
		wsprintf(szBuff, "%s\\Zenith\\%dos.tga", Path, i + 1);
		MatZenith[i] = CreateTextureMaterial(szBuff, 0, 0, 0, 0, SMMAT_BLEND_LAMP);
	}
	for(i = 0; i < 3; i++)
	{
		wsprintf(szBuff, "%s\\FireBolt\\FireBolt0%d.tga", Path, i + 1);
		MatFireBolt[i] = CreateTextureMaterial(szBuff, 0, 0, 0, 0, SMMAT_BLEND_LAMP);
	}
	for(i = 0; i < 6; i++)
	{
		wsprintf(szBuff, "%s\\Bomb\\Bomb%d.tga", Path, i + 1);
		MatBomb6[i] = CreateTextureMaterial(szBuff, 0, 0, 0, 0, SMMAT_BLEND_LAMP);
	}

	for(i = 0; i < 2; i++)
	{
		wsprintf(szBuff, "%s\\HolyBody\\HolyBody0%d.tga", Path, i + 1);
		MatHolyBody[i] = CreateTextureMaterial(szBuff, 0, 0, 0, 0, SMMAT_BLEND_LAMP);
	}

	for(i = 0; i < 2; i++)
	{
		wsprintf(szBuff, "%s\\SwordBlast\\SwordBlast0%d.tga", Path, i + 1);
		MatSwordBlast[i] = CreateTextureMaterial(szBuff, 0, 0, 0, 0, SMMAT_BLEND_LAMP);
	}

	for(i = 0; i < 3; i++)
	{
		wsprintf(szBuff, "%s\\ShieldStrike\\sd%d.tga", Path, i + 1);
		MatShieldStrike[i] = CreateTextureMaterial(szBuff, 0, 0, 0, 0, SMMAT_BLEND_LAMP);
	}



}

int KeyCount = 0;
int sinSkillTestKey()
{



	POINT3D Posi = { lpCurPlayer->pX,lpCurPlayer->pY,lpCurPlayer->pZ };


	if(sinGetKeyClick('4'))
	{

		switch(KeyCount)
		{
			case 0:
			sinEffect_Sword_Blast(lpCurPlayer, lpCharSelPlayer);
			break;
			case 1:
			sinEffect_Farina(lpCurPlayer, lpCharSelPlayer);
			break;
			case 2:
			sinEffect_Holy_Body(lpCurPlayer);
			break;
			case 3:
			sinEffect_MultiSpark(lpCurPlayer, lpCharSelPlayer, 7);
			break;
			case 4:
			sinEffect_Agony(lpCurPlayer);
			break;
			case 5:
			sinEffect_HolyMind(lpCurPlayer, 70);
			break;
			case 6:
			sinEffect_VigorSpear(lpCurPlayer, lpCharSelPlayer);
			break;
			case 7:
			sinEffect_Zenith(lpCurPlayer, 4);

			break;
			case 8:
			sinEffect_Healing2(lpCurPlayer);
			break;

		}

	}
	if(sinGetKeyClick('5'))
	{
		KeyCount++;

	}
	if(sinGetKeyClick('6'))
	{
		KeyCount--;

	}
	if(sinGetKeyClick('7'))
	{










	}

	return TRUE;
}

int PassCount = 0;
int SetLightFlag = 0;
void sinSkillEffectMove(cSINEFFECT2 *pEffect)
{
	POINT3D Posi;
	switch(pEffect->CODE)
	{
		case SKILL_HOLY_BODY:
		if(pEffect->Time == 20)
			sinEffect_Light5(&pEffect->Posi, 15000);
		if(pEffect->Index == 1)
			pEffect->Angle.y = -((pEffect->Time * 10) + ANGLE_90)&ANGCLIP;
		else
			pEffect->Angle.y = ((pEffect->Time * 10) + ANGLE_90)&ANGCLIP;


		break;
		case SKILL_FARINA:
		pEffect->sinFace.x += pEffect->MoveSpeed.x;
		pEffect->sinFace.y += pEffect->MoveSpeed.y;
		pEffect->sinFace.z += pEffect->MoveSpeed.z;
		Posi.x = pEffect->sinFace.x;
		Posi.y = pEffect->sinFace.y;
		Posi.z = pEffect->sinFace.z;
		sinEffect_Farina_Particle(&Posi);

		break;
		case SIN_PARTICLE_FARINA:
		sinGetMoveLocation2(pEffect);
		GetMoveLocation(0, 0, 32, pEffect->Angle.x, pEffect->Angle.y, 0);
		pEffect->sinFace.x += GeoResult_X;
		pEffect->sinFace.y += GeoResult_Y;
		pEffect->sinFace.z += GeoResult_Z;

		break;
		case SIN_PARTICLE_CROSS:
		pEffect->sinFace.x += pEffect->MoveSpeed.x;
		pEffect->sinFace.y += pEffect->MoveSpeed.y;
		pEffect->sinFace.z += pEffect->MoveSpeed.z;
		break;
		case SIN_PARTICLE_HOLYBODY:
		pEffect->sinFace.x -= pEffect->MoveSpeed.x;
		pEffect->sinFace.y -= pEffect->MoveSpeed.y;
		pEffect->sinFace.z -= pEffect->MoveSpeed.z;

		break;
		case SKILL_MULTISPARK:
		sinEffect_MultiSpark_Particle2(&pEffect->Posi);
		if(pEffect->ActionTime[0] == pEffect->Time)
		{
			if(pEffect->DesChar)
			{
				pEffect->MoveSpeed.x = (pEffect->DesChar->pX - pEffect->Posi.x) / 15;
				pEffect->MoveSpeed.y = (pEffect->DesChar->pY - pEffect->Posi.y) / 22;
				pEffect->MoveSpeed.z = (pEffect->DesChar->pZ - pEffect->Posi.z) / 15;
			}

		}
		pEffect->Posi.x += pEffect->MoveSpeed.x;
		pEffect->Posi.y += pEffect->MoveSpeed.y;
		pEffect->Posi.z += pEffect->MoveSpeed.z;

		pEffect->sinFace.x = pEffect->Posi.x;
		pEffect->sinFace.y = pEffect->Posi.y;
		pEffect->sinFace.z = pEffect->Posi.z;

		if(pEffect->Time == pEffect->Max_Time - 1)
		{
			if(pEffect->Index == 1)
			{
				sinEffect_SkillHit(pEffect->CODE, &pEffect->Posi);

			}
		}

		break;
		case SIN_PARTICLE_MULTYSPARK:
		sinGetMoveLocation2(pEffect);
		GetMoveLocation(0, 0, 256, pEffect->Angle.x, pEffect->Angle.y, 0);
		pEffect->sinFace.x += GeoResult_X;
		pEffect->sinFace.y += GeoResult_Y;
		pEffect->sinFace.z += GeoResult_Z;

		break;
		case SIN_PARTICLE_AGONY:
		pEffect->sinFace.x += pEffect->MoveSpeed.x;
		pEffect->sinFace.z += pEffect->MoveSpeed.z;
		pEffect->sinFace.y += pEffect->MoveSpeed.y;


		if(pEffect->ActionTime[0] <= pEffect->Time)
		{
			pEffect->sinFace.MatNum = MatAgony[7];
			pEffect->sinFace.y += (pEffect->MoveSpeed.y * 2);

		}

		break;
		case SKILL_AGONY:

		pEffect->MoveSpeed.y += 80;
		pEffect->RotateAngle += 100;
		pEffect->RotatePosi.x = pEffect->RotateDistance.y*GetCos[pEffect->RotateAngle&ANGCLIP] + pEffect->RotateDistance.z*GetSin[pEffect->RotateAngle&ANGCLIP];
		pEffect->RotatePosi.z = -pEffect->RotateDistance.y*GetSin[pEffect->RotateAngle&ANGCLIP] + pEffect->RotateDistance.z*GetCos[pEffect->RotateAngle&ANGCLIP];

		pEffect->RotatePosi.x >>= 16;
		pEffect->RotatePosi.z >>= 16;

		pEffect->sinFace.x = pEffect->pChar->pX + pEffect->RotatePosi.x;
		pEffect->sinFace.z = pEffect->pChar->pZ + pEffect->RotatePosi.z;
		pEffect->sinFace.y = pEffect->pChar->pY + pEffect->MoveSpeed.y;

		Posi.x = pEffect->sinFace.x;
		Posi.y = pEffect->sinFace.y;
		Posi.z = pEffect->sinFace.z;


		sinEffect_Agony_Particle(&Posi);


		pEffect->sinFace.x = 0;
		pEffect->sinFace.z = 0;
		pEffect->sinFace.y = 0;


		break;
		case SKILL_VIGOR_SPEAR:
		pEffect->Posi.x += pEffect->MoveSpeed.x;
		pEffect->Posi.y += pEffect->MoveSpeed.y;

		pEffect->Posi.y -= 70;
		pEffect->Posi.z += pEffect->MoveSpeed.z;
		sinEffect_VigorSpear_Particle(&pEffect->Posi);

		if(sinEfect_CheckCrash(pEffect))
		{

			sinEffect_SkillHit(pEffect->CODE, &pEffect->Posi);
			memset(pEffect, 0, sizeof(cSINEFFECT2));
		}
		break;

		case SIN_PARTICLE_VIGORSPEAR:
		sinGetMoveLocation2(pEffect);
		GetMoveLocation(0, 0, 64, pEffect->Angle.x, pEffect->Angle.y, 0);
		pEffect->sinFace.x += GeoResult_X;
		pEffect->sinFace.y += GeoResult_Y;
		pEffect->sinFace.z += GeoResult_Z;

		break;
		case SKILL_HOLY_MIND:
		pEffect->RotateDistance.z -= 13;
		pEffect->MoveSpeed.y += 64;
		pEffect->RotateAngle += 50;
		pEffect->RotatePosi.x = pEffect->RotateDistance.y*GetCos[pEffect->RotateAngle&ANGCLIP] + pEffect->RotateDistance.z*GetSin[pEffect->RotateAngle&ANGCLIP];
		pEffect->RotatePosi.z = -pEffect->RotateDistance.y*GetSin[pEffect->RotateAngle&ANGCLIP] + pEffect->RotateDistance.z*GetCos[pEffect->RotateAngle&ANGCLIP];

		pEffect->RotatePosi.x >>= 16;
		pEffect->RotatePosi.z >>= 16;

		pEffect->sinFace.x = pEffect->pChar->pX + pEffect->RotatePosi.x;
		pEffect->sinFace.z = pEffect->pChar->pZ + pEffect->RotatePosi.z;
		pEffect->sinFace.y = pEffect->pChar->pY + pEffect->MoveSpeed.y;

		Posi.x = pEffect->sinFace.x;
		Posi.y = pEffect->sinFace.y;
		Posi.z = pEffect->sinFace.z;

		if((pEffect->Time % 50) == 0)
			pEffect->ActionTime[0]++;

		if((pEffect->Time % (pEffect->ActionTime[0] + 1)) == 0)
		{
			sinEffect_HolyMind_Particle(&Posi);
		}


		pEffect->sinFace.x = 0;
		pEffect->sinFace.z = 0;
		pEffect->sinFace.y = 0;

		break;
		case SIN_PARTICLE_HOLYMIND:
		pEffect->sinFace.x += pEffect->MoveSpeed.x;
		pEffect->sinFace.z += pEffect->MoveSpeed.z;
		pEffect->sinFace.y += pEffect->MoveSpeed.y;

		break;
		case SIN_PARTICLE_HOLYMIND2:
		pEffect->sinFace.x = pEffect->pChar->pX;
		pEffect->sinFace.y = pEffect->pChar->pY + pEffect->AddHeight;
		pEffect->sinFace.z = pEffect->pChar->pZ;
		pEffect->FaceAngleY -= 16;
		pEffect->FaceAngleY &= ANGCLIP;
		if(!pEffect->pChar->MotionInfo || pEffect->pChar->MotionInfo->State == CHRMOTION_STATE_DEAD)
		{
			memset(pEffect, 0, sizeof(cSINEFFECT2));

		}
		break;
		case SKILL_ZENITH:
		pEffect->RotateAngle += 25;
		pEffect->RotatePosi.x = pEffect->RotateDistance.y*GetCos[pEffect->RotateAngle&ANGCLIP] + pEffect->RotateDistance.z*GetSin[pEffect->RotateAngle&ANGCLIP];
		pEffect->RotatePosi.z = -pEffect->RotateDistance.y*GetSin[pEffect->RotateAngle&ANGCLIP] + pEffect->RotateDistance.z*GetCos[pEffect->RotateAngle&ANGCLIP];

		pEffect->RotatePosi.x >>= 16;
		pEffect->RotatePosi.z >>= 16;

		pEffect->Posi.x = pEffect->pChar->pX + pEffect->RotatePosi.x;
		pEffect->Posi.z = pEffect->pChar->pZ + pEffect->RotatePosi.z;
		pEffect->Posi.y = pEffect->pChar->pY + 7000;

		pEffect->Angle.y = -((pEffect->RotateAngle * 2) + ANGLE_90)&ANGCLIP;




		break;
		case SIN_PARTICLE_ZENITH:
		pEffect->MoveSpeed.y += 2;
		pEffect->Posi.y -= pEffect->MoveSpeed.y;
		pEffect->RotateAngle += 64;
		pEffect->Angle.y = -((pEffect->RotateAngle * 2) + ANGLE_90)&ANGCLIP;

		break;
		case SIN_PARTICLE_HEALING:
		pEffect->sinFace.x += pEffect->MoveSpeed.x;
		pEffect->sinFace.z += pEffect->MoveSpeed.z;
		pEffect->sinFace.y += pEffect->MoveSpeed.y;
		break;
		case SKILL_HEALING:
		pEffect->RotateAngle += 25;
		pEffect->RotateDistance.z += 16;

		pEffect->RotatePosi.x = pEffect->RotateDistance.y*GetCos[pEffect->RotateAngle&ANGCLIP] + pEffect->RotateDistance.z*GetSin[pEffect->RotateAngle&ANGCLIP];
		pEffect->RotatePosi.z = -pEffect->RotateDistance.y*GetSin[pEffect->RotateAngle&ANGCLIP] + pEffect->RotateDistance.z*GetCos[pEffect->RotateAngle&ANGCLIP];

		pEffect->RotatePosi.x >>= 16;
		pEffect->RotatePosi.z >>= 16;

		pEffect->Posi.x = pEffect->pChar->pX + pEffect->RotatePosi.x;
		pEffect->Posi.z = pEffect->pChar->pZ + pEffect->RotatePosi.z;
		pEffect->MoveSpeed.y += 20;

		pEffect->Posi.y = pEffect->pChar->pY + 7000 + pEffect->MoveSpeed.y;
		pEffect->Angle.y = -((pEffect->RotateAngle) + ANGLE_270)&ANGCLIP;


		pEffect->RotatePosi.x = pEffect->RotateDistance.y*GetCos[pEffect->RotateAngle&ANGCLIP] + 32 * GetSin[pEffect->RotateAngle&ANGCLIP];
		pEffect->RotatePosi.z = -pEffect->RotateDistance.y*GetSin[pEffect->RotateAngle&ANGCLIP] + 32 * GetCos[pEffect->RotateAngle&ANGCLIP];

		pEffect->RotatePosi.x >>= 16;
		pEffect->RotatePosi.z >>= 16;

		pEffect->DesPosi.x = pEffect->Posi.x + (rand() % 1000) - 500;
		pEffect->DesPosi.y = pEffect->Posi.y + (rand() % 1000) - 500;
		pEffect->DesPosi.z = pEffect->Posi.z + (rand() % 1000) - 500;

		pEffect->DesPosi.x += pEffect->RotatePosi.x;
		pEffect->DesPosi.y += pEffect->RotatePosi.z;
		pEffect->DesPosi.y -= 1000;
		if(pEffect->Time < pEffect->Max_Time - 30)
			sinEffect_HealParticle3(&pEffect->DesPosi, MatHolyMind[0], 1, 500, 50, 10);

		break;

		case SIN_EFFECT_HEALING3:
		pEffect->RotatePosi.x = GetCos[pEffect->RotateAngle&ANGCLIP] + pEffect->RotateDistance.z*GetSin[pEffect->RotateAngle&ANGCLIP];
		pEffect->RotatePosi.z = -GetSin[pEffect->RotateAngle&ANGCLIP] + pEffect->RotateDistance.z*GetCos[pEffect->RotateAngle&ANGCLIP];
		pEffect->RotatePosi.x >>= 16;
		pEffect->RotatePosi.z >>= 16;
		pEffect->sinFace.x += pEffect->RotatePosi.x;
		pEffect->sinFace.z += pEffect->RotatePosi.z;
		pEffect->Gravity -= 5;
		pEffect->sinFace.y += pEffect->MoveSpeed.y + pEffect->Gravity;


		pEffect->sinFace.r += 3;
		pEffect->sinFace.g++;
		pEffect->sinFace.b += 2;


		break;



		case SKILL_FIRE_BOLT:
		pEffect->sinFace.x += pEffect->MoveSpeed.x;
		pEffect->sinFace.y += pEffect->MoveSpeed.y;
		pEffect->sinFace.z += pEffect->MoveSpeed.z;

		pEffect->Posi.x = pEffect->sinFace.x;
		pEffect->Posi.y = pEffect->sinFace.y;
		pEffect->Posi.z = pEffect->sinFace.z;

		Posi.x = pEffect->sinFace.x;
		Posi.y = pEffect->sinFace.y;
		Posi.z = pEffect->sinFace.z;
		if(pEffect->ActionTime[0])
		{
			sinEffect_FireBolt_Particle2(&Posi);
			sinEffect_FireBolt_Particle(&Posi);

		}




		break;
		case SIN_PARTICLE_FIREBOLT:
		Posi.x = pEffect->sinFace.x;
		Posi.y = pEffect->sinFace.y;
		Posi.z = pEffect->sinFace.z;






		break;

		case SIN_EFFECT_BOMB5:
		pEffect->Gravity++;
		sinGetMoveLocation2(pEffect);
		GetMoveLocation(0, 0, 64, pEffect->Angle.x, pEffect->Angle.y, 0);
		pEffect->sinFace.x += GeoResult_X;
		if(GeoResult_Y > 0)
			pEffect->sinFace.y += GeoResult_Y;
		pEffect->sinFace.z += GeoResult_Z;
		pEffect->sinFace.y -= pEffect->Gravity;

		Posi.x = pEffect->sinFace.x;
		Posi.y = pEffect->sinFace.y;
		Posi.z = pEffect->sinFace.z;

		if((pEffect->Time % 5) == 0)
		{
			sinEffect_Bomb6_Particle(&Posi);
		}


		break;
		case SKILL_SWORD_BLAST:
		pEffect->Posi.x += pEffect->MoveSpeed.x;
		pEffect->Posi.y += pEffect->MoveSpeed.y;

		pEffect->Posi.y -= 70;

		pEffect->Posi.z += pEffect->MoveSpeed.z;
		sinEffect_Sword_Blast_Particle(&pEffect->Posi);

		break;

		case SIN_PARTICLE_SWORDBLAST:
		sinGetMoveLocation2(pEffect);
		GetMoveLocation(0, 0, 512, pEffect->Angle.x, pEffect->Angle.y, 0);
		pEffect->sinFace.x += GeoResult_X;
		pEffect->sinFace.y += GeoResult_Y;
		pEffect->sinFace.z += GeoResult_Z;

		break;
		case SKILL_SHIELD_STRIKE:
		pEffect->Posi.x = pEffect->sinFace.x;
		pEffect->Posi.y = pEffect->sinFace.y;
		pEffect->Posi.z = pEffect->sinFace.z;
		if((pEffect->Time % 2) == 0)
			sinEffect_Shield_Strike_Particle(&pEffect->Posi);

		break;
		case SIN_PARTICLE_SHEILDSTRIKE:
		sinGetMoveLocation2(pEffect);
		GetMoveLocation(0, 0, 64, pEffect->Angle.x, pEffect->Angle.y, 0);
		pEffect->sinFace.x += GeoResult_X;
		pEffect->sinFace.y += GeoResult_Y;
		pEffect->sinFace.z += GeoResult_Z;


		break;

	}
}

int sinEffect_Sword_Blast(smCHAR *pChar, smCHAR *desChar)
{
	if(!pChar)return FALSE;

	smASE_SetPhysique(0);
	SetDynLight(pChar->pX, pChar->pY, pChar->pZ, 255, 255, 255, 255, 200, 1);
	Index2 = sinSearchEmptyIndex();
	sinEffectDefaultSet(Index2, SIN_EFFECT_MESH, pChar, 0, 10000);
	cSinEffect2[Index2].sinPatMesh = smASE_Read("image\\Sinimage\\Effect\\SkillEffect\\SwordBlast\\SwordBlast.ASE");
	cSinEffect2[Index2].CODE = SKILL_SWORD_BLAST;

	cSinEffect2[Index2].Max_Time = 40;
	cSinEffect2[Index2].Color_A = 150;
	cSinEffect2[Index2].DesChar = desChar;
	if(cSinEffect2[Index2].DesChar)
	{

		GetRadian3D(pChar->pX, pChar->pY, pChar->pZ, cSinEffect2[Index2].DesChar->pX, cSinEffect2[Index2].DesChar->pY, cSinEffect2[Index2].DesChar->pZ);

		cSinEffect2[Index2].Angle.x = GeoResult_X;
		cSinEffect2[Index2].Angle.y = (-(GeoResult_Y&ANGCLIP) + ANGLE_180)&ANGCLIP;


		cSinEffect2[Index2].MoveSpeed.x = (cSinEffect2[Index2].DesChar->pX - cSinEffect2[Index2].pChar->pX) / 20;
		cSinEffect2[Index2].MoveSpeed.y = (cSinEffect2[Index2].DesChar->pY - cSinEffect2[Index2].pChar->pY) / 100;
		cSinEffect2[Index2].MoveSpeed.z = (cSinEffect2[Index2].DesChar->pZ - cSinEffect2[Index2].pChar->pZ) / 20;

	}

	if(cSinEffect2[Index2].sinPatMesh)
		cSinEffect2[Index2].sinPatMesh->smMaterialGroup->ReadTextures();

	sinEffect_SetCharPosi(&cSinEffect2[Index2]);
	return TRUE;

}

int sinEffect_Sword_Blast_Particle(POINT3D *pPosi)
{
	int Size;
	for(int i = 0; i < 15; i++)
	{
		Index2 = sinSearchEmptyIndex();
		sinEffectDefaultSet(Index2, SIN_EFFECT_FACE, 0, pPosi, 0);
		Size = rand() % 500 + 700;
		cSinEffect2[Index2].sinFace.height = Size;
		cSinEffect2[Index2].sinFace.width = Size;
		cSinEffect2[Index2].sinFace.MatNum = MatFarina[8];
		cSinEffect2[Index2].Max_Time = rand() % 10 + 5;
		cSinEffect2[Index2].AlphaTime = 10;
		cSinEffect2[Index2].AlphaAmount = 5;
		cSinEffect2[Index2].AlphaCount = 1;
		cSinEffect2[Index2].CODE = SIN_PARTICLE_SWORDBLAST;
		cSinEffect2[Index2].Angle.x = ((rand() % (4096 / 2)) - ANGLE_90)&ANGCLIP;
		cSinEffect2[Index2].Angle.z = 0;
		cSinEffect2[Index2].Angle.y = rand() % 4096;
		cSinEffect2[Index2].MoveSpeed.z = 512;
		cSinEffect2[Index2].SizeDecreTime = cSinEffect2[Index2].Max_Time - 20;
		cSinEffect2[Index2].SizeAmount = 50;

		for(int j = 0; j < 2; j++)
		{
			sinGetMoveLocation2(&cSinEffect2[Index2]);
			GetMoveLocation(0, 0, 256, cSinEffect2[Index2].Angle.x, cSinEffect2[Index2].Angle.y, 0);
			cSinEffect2[Index2].sinFace.x += GeoResult_X;
			cSinEffect2[Index2].sinFace.y += GeoResult_Y;
			cSinEffect2[Index2].sinFace.z += GeoResult_Z;
		}
	}
	return TRUE;

}


int sinEffect_Holy_Body(smCHAR *pChar)
{
	if(!pChar)return FALSE;

	int TempIndex = 0;
	smASE_SetPhysique(0);
	SetDynLight(pChar->pX, pChar->pY, pChar->pZ, 255, 255, 255, 255, 200, 1);
	Index2 = sinSearchEmptyIndex();
	sinEffectDefaultSet(Index2, SIN_EFFECT_MESH, pChar, 0, 7000);
	cSinEffect2[Index2].sinPatMesh = smASE_Read("image\\Sinimage\\Effect\\SkillEffect\\HolyBody\\h_bodyteg.ASE");
	cSinEffect2[Index2].CODE = SKILL_HOLY_BODY;

	cSinEffect2[Index2].Max_Time = 90;
	cSinEffect2[Index2].AniTime = 5;
	cSinEffect2[Index2].AniMax = 100;
	cSinEffect2[Index2].AniCount = 1;
	cSinEffect2[Index2].AlphaAmount = 20;
	cSinEffect2[Index2].AlphaCount = 2;
	cSinEffect2[Index2].AlphaTime = cSinEffect2[Index2].Max_Time - 50;
	cSinEffect2[Index2].Time = -30;
	cSinEffect2[Index2].Index = 1;
	TempIndex = Index2;

	Index2 = sinSearchEmptyIndex();
	memcpy(&cSinEffect2[Index2], &cSinEffect2[TempIndex], sizeof(cSINEFFECT2));

	cSinEffect2[Index2].Index = 2;
	if(cSinEffect2[Index2].sinPatMesh)
		cSinEffect2[Index2].sinPatMesh->smMaterialGroup->ReadTextures();


	sinEffect_GatherCircleParticle(&cSinEffect2[Index2].Posi, MatVigorSpear[0]);








	return TRUE;
}

int sinEffect_Holy_Body_Cross(smCHAR *pChar)
{
	if(!pChar)return FALSE;
	int Size;
	for(int i = 0; i < 60; i++)
	{
		Index2 = sinSearchEmptyIndex();
		sinEffectDefaultSet(Index2, SIN_EFFECT_FACE, pChar, 0, 5000);
		cSinEffect2[Index2].sinFace.MatNum = MatHolyBodyCross[0];
		cSinEffect2[Index2].lpMatAni = MatHolyBodyCross;
		cSinEffect2[Index2].AniMax = 4;
		cSinEffect2[Index2].AniTime = 10;
		cSinEffect2[Index2].AniCount = i % 3;
		cSinEffect2[Index2].AniReverseNum = 1;
		Size = rand() % 1000 + 1500;

		cSinEffect2[Index2].sinFace.height = Size;
		cSinEffect2[Index2].sinFace.width = Size;
		cSinEffect2[Index2].Max_Time = 30;



		cSinEffect2[Index2].Angle.x = ((rand() % (4096 / 2)) - ANGLE_90)&ANGCLIP;
		cSinEffect2[Index2].Angle.z = 0;
		cSinEffect2[Index2].Angle.y = rand() % 4096;
		cSinEffect2[Index2].Time -= 40 + (i / 10);

		cSinEffect2[Index2].MoveSpeed.z = 256;
		cSinEffect2[Index2].CODE = SIN_PARTICLE_CROSS;


		for(int j = 0; j < 30; j++)
		{
			sinGetMoveLocation2(&cSinEffect2[Index2]);
			GetMoveLocation(0, 0, 256, cSinEffect2[Index2].Angle.x, cSinEffect2[Index2].Angle.y, 0);
			cSinEffect2[Index2].sinFace.x += GeoResult_X;
			cSinEffect2[Index2].sinFace.y += GeoResult_Y;
			cSinEffect2[Index2].sinFace.z += GeoResult_Z;
		}
		cSinEffect2[Index2].MoveSpeed.x = (cSinEffect2[Index2].sinFace.x - pChar->pX) / 30;
		cSinEffect2[Index2].MoveSpeed.y = (cSinEffect2[Index2].sinFace.y - (pChar->pY + 5000)) / 30;
		cSinEffect2[Index2].MoveSpeed.z = (cSinEffect2[Index2].sinFace.z - pChar->pZ) / 30;
		cSinEffect2[Index2].sinFace.r = rand() & 500 - 255;
		cSinEffect2[Index2].sinFace.g = rand() & 500 - 255;
		cSinEffect2[Index2].sinFace.b = rand() & 500 - 255;

	}
	return TRUE;
}

int sinEffect_Holy_Body_Particle(POINT3D *pPosi)
{
	int Size;
	for(int i = 0; i < 30; i++)
	{
		Index2 = sinSearchEmptyIndex();
		sinEffectDefaultSet(Index2, SIN_EFFECT_FACE, 0, pPosi, 5000);
		cSinEffect2[Index2].sinFace.MatNum = MatHolyBodyCross[0];
		cSinEffect2[Index2].lpMatAni = MatHolyBodyCross;
		cSinEffect2[Index2].AniMax = 4;
		cSinEffect2[Index2].AniTime = 10;
		cSinEffect2[Index2].AniCount = i % 3;
		cSinEffect2[Index2].AniReverseNum = 1;
		Size = rand() % 1000 + 1500;

		cSinEffect2[Index2].sinFace.height = Size;
		cSinEffect2[Index2].sinFace.width = Size;
		cSinEffect2[Index2].Max_Time = 15;



		cSinEffect2[Index2].Angle.x = ((rand() % (4096 / 2)) - ANGLE_90)&ANGCLIP;
		cSinEffect2[Index2].Angle.z = 0;
		cSinEffect2[Index2].Angle.y = rand() % 4096;
		cSinEffect2[Index2].Time -= (i + 1 / 3);

		cSinEffect2[Index2].MoveSpeed.z = 256;
		cSinEffect2[Index2].CODE = SIN_PARTICLE_HOLYBODY;


		for(int j = 0; j < 100; j++)
		{
			sinGetMoveLocation2(&cSinEffect2[Index2]);
			GetMoveLocation(0, 0, 256, cSinEffect2[Index2].Angle.x, cSinEffect2[Index2].Angle.y, 0);
			cSinEffect2[Index2].sinFace.x += GeoResult_X;
			cSinEffect2[Index2].sinFace.y += GeoResult_Y;
			cSinEffect2[Index2].sinFace.z += GeoResult_Z;
		}
		cSinEffect2[Index2].MoveSpeed.x = (cSinEffect2[Index2].sinFace.x - pPosi->x) / 30;
		cSinEffect2[Index2].MoveSpeed.y = (cSinEffect2[Index2].sinFace.y - (pPosi->y + 5000)) / 30;
		cSinEffect2[Index2].MoveSpeed.z = (cSinEffect2[Index2].sinFace.z - pPosi->z) / 30;

	}
	return TRUE;
}

int sinEffect_Farina(smCHAR *pChar, smCHAR *desChar)
{
	if(!pChar)return FALSE;
	SetDynLight(pChar->pX, pChar->pY, pChar->pZ, 255, 255, 255, 255, 200, 1);
	Index2 = sinSearchEmptyIndex();
	sinEffectDefaultSet(Index2, SIN_EFFECT_FACE, pChar, 0, 10000);
	cSinEffect2[Index2].sinFace.height = 3000;
	cSinEffect2[Index2].sinFace.width = 3000;
	cSinEffect2[Index2].sinFace.MatNum = MatFarina[0];
	cSinEffect2[Index2].Max_Time = 2000;
	cSinEffect2[Index2].AniTime = 5;
	cSinEffect2[Index2].AniMax = 7;
	cSinEffect2[Index2].lpMatAni = MatFarina;
	cSinEffect2[Index2].CODE = SKILL_FARINA;
	cSinEffect2[Index2].DesChar = desChar;
	if(cSinEffect2[Index2].DesChar)
	{
		cSinEffect2[Index2].MoveSpeed.x = (cSinEffect2[Index2].DesChar->pX - cSinEffect2[Index2].pChar->pX) / 70;
		cSinEffect2[Index2].MoveSpeed.y = (cSinEffect2[Index2].DesChar->pY - cSinEffect2[Index2].pChar->pY) / 70;
		cSinEffect2[Index2].MoveSpeed.z = (cSinEffect2[Index2].DesChar->pZ - cSinEffect2[Index2].pChar->pZ) / 70;
	}

	return TRUE;

}

int sinEffect_Farina_Particle(POINT3D *pPosi)
{
	int Size;
	for(int i = 0; i < 5; i++)
	{
		Index2 = sinSearchEmptyIndex();
		sinEffectDefaultSet(Index2, SIN_EFFECT_FACE, 0, pPosi, 0);
		Size = rand() % 500 + 500;
		cSinEffect2[Index2].sinFace.height = Size;
		cSinEffect2[Index2].sinFace.width = Size;
		cSinEffect2[Index2].sinFace.MatNum = MatFarina[6];
		cSinEffect2[Index2].Max_Time = rand() % 10 + 30;
		cSinEffect2[Index2].AlphaTime = 15;
		cSinEffect2[Index2].AlphaAmount = 5;
		cSinEffect2[Index2].AlphaCount = 1;
		cSinEffect2[Index2].CODE = SIN_PARTICLE_FARINA;
		cSinEffect2[Index2].Angle.x = ((rand() % (4096 / 2)) - ANGLE_90)&ANGCLIP;
		cSinEffect2[Index2].Angle.z = 0;
		cSinEffect2[Index2].Angle.y = rand() % 4096;
		cSinEffect2[Index2].MoveSpeed.z = 64;
	}
	return TRUE;

}

int sinEffect_MultiSpark_Particle2(POINT3D *pPosi)
{
	int Size;
	for(int i = 0; i < 1; i++)
	{
		Index2 = sinSearchEmptyIndex();
		sinEffectDefaultSet(Index2, SIN_EFFECT_FACE, 0, pPosi, 0);
		Size = rand() % 1500 + 1500;
		cSinEffect2[Index2].sinFace.height = Size;
		cSinEffect2[Index2].sinFace.width = Size;
		cSinEffect2[Index2].sinFace.MatNum = MatMultiSpark[6];
		cSinEffect2[Index2].Max_Time = rand() % 3 + 10;
		cSinEffect2[Index2].AlphaTime = 10;
		cSinEffect2[Index2].AlphaAmount = 10;
		cSinEffect2[Index2].AlphaCount = 1;
		cSinEffect2[Index2].CODE = SIN_PARTICLE_FIREBOLT;
		cSinEffect2[Index2].Angle.x = ((rand() % (4096 / 2)) - ANGLE_90)&ANGCLIP;
		cSinEffect2[Index2].Angle.z = 0;
		cSinEffect2[Index2].Angle.y = rand() % 4096;
		cSinEffect2[Index2].MoveSpeed.z = 64;
		sinGetMoveLocation2(&cSinEffect2[Index2]);
		GetMoveLocation(0, 0, 64, cSinEffect2[Index2].Angle.x, cSinEffect2[Index2].Angle.y, 0);
		cSinEffect2[Index2].sinFace.x += GeoResult_X;
		cSinEffect2[Index2].sinFace.y += GeoResult_Y;
		cSinEffect2[Index2].sinFace.z += GeoResult_Z;


		cSinEffect2[Index2].SizeDecreTime = 1;
		cSinEffect2[Index2].SizeAmount = 150;
		cSinEffect2[Index2].sinFace.Transparency = 80;


	}

	return TRUE;
}

int sinEffect_MultiSpark(smCHAR *pChar, smCHAR *desChar, int Num)
{
	if(!pChar)return FALSE;

	float Temp2 = 0;
	SetDynLight(pChar->pX, pChar->pY, pChar->pZ, 255, 255, 255, 255, 140, 1);
	for(int i = 0; i < Num; i++)
	{

		Index2 = sinSearchEmptyIndex();


		sinEffectDefaultSet(Index2, SIN_EFFECT_FACE, pChar, 0, 7000);
		cSinEffect2[Index2].sinFace.height = 3000;
		cSinEffect2[Index2].sinFace.width = 3000;
		cSinEffect2[Index2].sinFace.MatNum = MatMultiSpark[6];
		cSinEffect2[Index2].CODE = SKILL_MULTISPARK;
		cSinEffect2[Index2].Max_Time = 45;
		cSinEffect2[Index2].MoveSpeed.z = 256;
		cSinEffect2[Index2].ActionTime[0] = 30;
		cSinEffect2[Index2].DesChar = desChar;
		if(i == 0)
		{
			cSinEffect2[Index2].Index = 1;
		}
		else
			cSinEffect2[Index2].Index = 0;


		if(cSinEffect2[Index2].DesChar)
		{
			GetRadian3D(pChar->pX, pChar->pY, pChar->pZ, cSinEffect2[Index2].DesChar->pX, cSinEffect2[Index2].DesChar->pY, cSinEffect2[Index2].DesChar->pZ);
			cSinEffect2[Index2].Angle.x = GeoResult_X;

			cSinEffect2[Index2].Angle.y = GeoResult_Y;
		}

		if(Num - 1 == i && (Num % 2) == 1)
		{

			GetMoveLocation(0, fONE * 26, 0, cSinEffect2[Index2].Angle.x, cSinEffect2[Index2].Angle.y, cSinEffect2[Index2].Angle.z);




		}
		else
		{
			if(((i + 1) % 2) == 0)
				Temp2 = 1.0f;
			else
				Temp2 = -1.0f;
			GetMoveLocation((int)((fONE*(10 + 1 + (i * 12)))*Temp2), 0, 0, cSinEffect2[Index2].Angle.x, cSinEffect2[Index2].Angle.y, cSinEffect2[Index2].Angle.z);
			cSinEffect2[Index2].sinFace.x += GeoResult_X;
			cSinEffect2[Index2].sinFace.y += GeoResult_Y;
			cSinEffect2[Index2].sinFace.z += GeoResult_Z;


		}

		if(cSinEffect2[Index2].DesChar)
		{
			cSinEffect2[Index2].DesPosi.x = ((cSinEffect2[Index2].DesChar->pX - cSinEffect2[Index2].pChar->pX) / 4);
			cSinEffect2[Index2].DesPosi.y = ((cSinEffect2[Index2].DesChar->pY - cSinEffect2[Index2].pChar->pY) / 4);
			cSinEffect2[Index2].DesPosi.z = ((cSinEffect2[Index2].DesChar->pZ - cSinEffect2[Index2].pChar->pZ) / 4);
			cSinEffect2[Index2].MoveSpeed.x = ((cSinEffect2[Index2].DesPosi.x + cSinEffect2[Index2].pChar->pX) - cSinEffect2[Index2].sinFace.x) / 20;
			cSinEffect2[Index2].MoveSpeed.y = ((cSinEffect2[Index2].DesPosi.y + cSinEffect2[Index2].pChar->pY + 7000) - cSinEffect2[Index2].sinFace.y) / 20;
			cSinEffect2[Index2].MoveSpeed.z = ((cSinEffect2[Index2].DesPosi.z + cSinEffect2[Index2].pChar->pZ) - cSinEffect2[Index2].sinFace.z) / 20;

		}



		cSinEffect2[Index2].BoneFlag = 1;
	}
	return TRUE;
}



int sinEffect_MultiSpark_Particle(POINT3D *pPosi)
{
	int Size;
	for(int i = 0; i < 3; i++)
	{
		Index2 = sinSearchEmptyIndex();
		sinEffectDefaultSet(Index2, SIN_EFFECT_FACE, 0, pPosi, 0);
		cSinEffect2[Index2].sinFace.MatNum = MatMultiSpark[5];
		Size = rand() % 1000 + 500;

		cSinEffect2[Index2].sinFace.height = Size;
		cSinEffect2[Index2].sinFace.width = Size;
		cSinEffect2[Index2].Max_Time = rand() % 20 + 10;
		cSinEffect2[Index2].Angle.x = ((rand() % (4096 / 2)) - ANGLE_90)&ANGCLIP;
		cSinEffect2[Index2].Angle.z = 0;
		cSinEffect2[Index2].Angle.y = rand() % 4096;
		cSinEffect2[Index2].Time -= i / 5;

		cSinEffect2[Index2].MoveSpeed.z = 256;
		cSinEffect2[Index2].CODE = SIN_PARTICLE_MULTYSPARK;
		cSinEffect2[Index2].AlphaAmount = 5;
		cSinEffect2[Index2].AlphaTime = cSinEffect2[Index2].Max_Time - 20;
		cSinEffect2[Index2].AlphaCount = 1;
		cSinEffect2[Index2].sinFace.Transparency = 170;

	}
	Index2 = sinSearchEmptyIndex();
	sinEffectDefaultSet(Index2, SIN_EFFECT_FACE, 0, pPosi, 0);
	cSinEffect2[Index2].sinFace.MatNum = MatMultiSpark[4];
	Size = 5000;
	cSinEffect2[Index2].Max_Time = 20;
	cSinEffect2[Index2].sinFace.height = Size;
	cSinEffect2[Index2].sinFace.width = Size;
	cSinEffect2[Index2].CODE = SIN_PARTICLE_MULTYSPARK2;
	cSinEffect2[Index2].AlphaAmount = 8;
	cSinEffect2[Index2].AlphaTime = cSinEffect2[Index2].Max_Time - 20;
	cSinEffect2[Index2].AlphaCount = 1;
	cSinEffect2[Index2].sinFace.Transparency = 170;




	return TRUE;
}

int sinEffect_Agony(smCHAR *pChar)
{
	if(!pChar)return FALSE;
	int Size;
	SetDynLight(pChar->pX, pChar->pY, pChar->pZ, 255, 255, 255, 255, 200, 1);
	Index2 = sinSearchEmptyIndex();
	sinEffectDefaultSet(Index2, SIN_EFFECT_FACE, pChar, 0, 0);
	cSinEffect2[Index2].sinFace.MatNum = MatAgony[0];
	Size = 2000;
	cSinEffect2[Index2].sinFace.height = Size;
	cSinEffect2[Index2].sinFace.width = Size;
	cSinEffect2[Index2].Max_Time = 70;
	cSinEffect2[Index2].CODE = SKILL_AGONY;
	cSinEffect2[Index2].AniCount = 1;
	cSinEffect2[Index2].AniMax = 4;
	cSinEffect2[Index2].AniTime = 10;
	cSinEffect2[Index2].lpMatAni = MatHolyMind;

	cSinEffect2[Index2].RotateDistance.z = 128 * 16 * 3;



	return TRUE;
}

int sinEffect_Agony_Particle(POINT3D *pPosi)
{

	int Size;
	Index2 = sinSearchEmptyIndex();
	sinEffectDefaultSet(Index2, SIN_EFFECT_FACE, 0, pPosi, 0);
	cSinEffect2[Index2].sinFace.MatNum = MatAgony[8];

	Size = rand() % 1000 + 500;
	cSinEffect2[Index2].sinFace.height = Size;
	cSinEffect2[Index2].sinFace.width = Size;
	cSinEffect2[Index2].Max_Time = 100;
	cSinEffect2[Index2].CODE = SIN_PARTICLE_AGONY;
	cSinEffect2[Index2].Gravity = rand() % 10 + 5;
	cSinEffect2[Index2].ActionTime[0] = 40;

	cSinEffect2[Index2].AlphaTime = cSinEffect2[Index2].Max_Time - 50;
	cSinEffect2[Index2].AlphaAmount = 5;
	cSinEffect2[Index2].AlphaCount = 1;


	cSinEffect2[Index2].sinFace.x += rand() % 100;
	cSinEffect2[Index2].sinFace.y += rand() % 100;
	cSinEffect2[Index2].sinFace.z += rand() % 100;






	cSinEffect2[Index2].MoveSpeed.x = rand() % 3;
	cSinEffect2[Index2].MoveSpeed.z = rand() % 3;
	cSinEffect2[Index2].MoveSpeed.y = rand() % 50 + 5;





	return TRUE;
}


int sinEffect_HolyMind(smCHAR *pChar, int Time)
{
	int HeightNum = 0;
	if(!pChar)return FALSE;
	int Size;
	SetDynLight(pChar->pX, pChar->pY, pChar->pZ, 255, 255, 255, 255, 200, 1);
	Index2 = sinSearchEmptyIndex();
	sinEffectDefaultSet(Index2, SIN_EFFECT_FACE, pChar, 0, 0);
	cSinEffect2[Index2].sinFace.MatNum = MatHolyMind[0];
	Size = 2000;
	cSinEffect2[Index2].sinFace.height = Size;
	cSinEffect2[Index2].sinFace.width = Size;
	cSinEffect2[Index2].Max_Time = 120;
	cSinEffect2[Index2].CODE = SKILL_HOLY_MIND;
	cSinEffect2[Index2].AniCount = 1;
	cSinEffect2[Index2].AniMax = 4;
	cSinEffect2[Index2].AniTime = 10;
	cSinEffect2[Index2].lpMatAni = MatHolyMind;
	cSinEffect2[Index2].RotateDistance.z = 128 * 16 * 3;
	cSinEffect2[Index2].BoneFlag = 1;




	Index2 = sinSearchEmptyIndex();
	sinEffectDefaultSet(Index2, SIN_EFFECT_FACE, pChar, 0, pChar->PatHeight);
	cSinEffect2[Index2].sinFace.MatNum = MatAgony[0];
	cSinEffect2[Index2].ActionTime[2] = HeightNum;


	Size = 3000;
	cSinEffect2[Index2].sinFace.height = Size;
	cSinEffect2[Index2].sinFace.width = Size;


	int TempResi = 100 - pChar->smCharInfo.Resistance[sITEMINFO_BIONIC];
	cSinEffect2[Index2].Max_Time = (int)(((float)Time*70.0f)*((float)TempResi / 100.0f));


	cSinEffect2[Index2].CODE = SIN_PARTICLE_HOLYMIND2;
	cSinEffect2[Index2].AniCount = 1;
	cSinEffect2[Index2].AniMax = 7;
	cSinEffect2[Index2].AniTime = 10;
	cSinEffect2[Index2].AniReverseNum = 1;
	cSinEffect2[Index2].lpMatAni = MatAgony;
	cSinEffect2[Index2].Time = -120;
	cSinEffect2[Index2].ReSizingAmount = 10;
	cSinEffect2[Index2].ReSizingNum = 1;

	cSinEffect2[Index2].AlphaFadeInFlag = 1;
	cSinEffect2[Index2].sinFace.Transparency = 0;









	return TRUE;
}

int sinEffect_HolyMind_Particle(POINT3D *pPosi)
{

	int Size;
	Index2 = sinSearchEmptyIndex();
	sinEffectDefaultSet(Index2, SIN_EFFECT_FACE, 0, pPosi, 0);
	cSinEffect2[Index2].sinFace.MatNum = MatHolyMind[0];
	Size = rand() % 1000 + 500;
	cSinEffect2[Index2].sinFace.height = Size;
	cSinEffect2[Index2].sinFace.width = Size;
	cSinEffect2[Index2].Max_Time = rand() % 20 + 30;
	cSinEffect2[Index2].CODE = SIN_PARTICLE_HOLYMIND;
	cSinEffect2[Index2].AniCount = 1;
	cSinEffect2[Index2].AniMax = 4;
	cSinEffect2[Index2].AniTime = 10;
	cSinEffect2[Index2].lpMatAni = MatHolyMind;

	cSinEffect2[Index2].Gravity = rand() % 10 + 5;


	cSinEffect2[Index2].AlphaReverse_A = rand() % 255;
	cSinEffect2[Index2].AlphaAmount = 3;
	cSinEffect2[Index2].AlphaReverseNum = 1;
	cSinEffect2[Index2].AlphaTime = 1;

	cSinEffect2[Index2].sinFace.x += rand() % 1000;
	cSinEffect2[Index2].sinFace.y += rand() % 1000;
	cSinEffect2[Index2].sinFace.z += rand() % 1000;


	cSinEffect2[Index2].sinFace.r = rand() % 255;
	cSinEffect2[Index2].sinFace.g = rand() % 255;
	cSinEffect2[Index2].sinFace.b = rand() % 255;

	cSinEffect2[Index2].MoveSpeed.x = rand() % 3;
	cSinEffect2[Index2].MoveSpeed.z = rand() % 3;
	cSinEffect2[Index2].MoveSpeed.y = rand() % 50 + 50;


	return TRUE;
}


int sinEffect_VigorSpear(smCHAR *pChar, smCHAR *desChar)
{
	if(!pChar)return FALSE;
	smASE_SetPhysique(0);
	SetDynLight(pChar->pX, pChar->pY, pChar->pZ, 255, 255, 255, 255, 200, 1);
	Index2 = sinSearchEmptyIndex();
	sinEffectDefaultSet(Index2, SIN_EFFECT_MESH, pChar, 0, 10000);
	cSinEffect2[Index2].sinPatMesh = smASE_Read("image\\Sinimage\\Effect\\SkillEffect\\VigorSpear\\v_spear.ASE");
	cSinEffect2[Index2].CODE = SKILL_VIGOR_SPEAR;

	cSinEffect2[Index2].Max_Time = 100;
	cSinEffect2[Index2].Color_A = 150;
	cSinEffect2[Index2].DesChar = desChar;
	if(cSinEffect2[Index2].DesChar)
	{

		GetRadian3D(pChar->pX, pChar->pY, pChar->pZ, cSinEffect2[Index2].DesChar->pX, cSinEffect2[Index2].DesChar->pY, cSinEffect2[Index2].DesChar->pZ);

		cSinEffect2[Index2].Angle.x = GeoResult_X;
		cSinEffect2[Index2].Angle.y = (-(GeoResult_Y&ANGCLIP) + ANGLE_180)&ANGCLIP;
		cSinEffect2[Index2].MoveSpeed.x = (cSinEffect2[Index2].DesChar->pX - cSinEffect2[Index2].pChar->pX) / 20;
		cSinEffect2[Index2].MoveSpeed.y = (cSinEffect2[Index2].DesChar->pY - cSinEffect2[Index2].pChar->pY) / 20;
		cSinEffect2[Index2].MoveSpeed.z = (cSinEffect2[Index2].DesChar->pZ - cSinEffect2[Index2].pChar->pZ) / 20;
	}
	if(cSinEffect2[Index2].sinPatMesh)
		cSinEffect2[Index2].sinPatMesh->smMaterialGroup->ReadTextures();

	sinEffect_SetCharPosi(&cSinEffect2[Index2]);
	return TRUE;

}

int sinEffect_VigorSpear_Particle(POINT3D *pPosi)
{
	int Size;
	for(int i = 0; i < 5; i++)
	{
		Index2 = sinSearchEmptyIndex();
		sinEffectDefaultSet(Index2, SIN_EFFECT_FACE, 0, pPosi, 0);
		Size = rand() % 500 + 500;
		cSinEffect2[Index2].sinFace.height = Size;
		cSinEffect2[Index2].sinFace.width = Size;
		cSinEffect2[Index2].sinFace.MatNum = MatVigorSpear[0];
		cSinEffect2[Index2].AniMax = 7;
		cSinEffect2[Index2].AniTime = 3;
		cSinEffect2[Index2].AniCount = 1;
		cSinEffect2[Index2].lpMatAni = MatVigorSpear;
		cSinEffect2[Index2].Max_Time = rand() % 10 + 20;
		cSinEffect2[Index2].AlphaTime = 10;
		cSinEffect2[Index2].AlphaAmount = 5;
		cSinEffect2[Index2].AlphaCount = 1;
		cSinEffect2[Index2].CODE = SIN_PARTICLE_VIGORSPEAR;
		cSinEffect2[Index2].Angle.x = ((rand() % (4096 / 2)) - ANGLE_90)&ANGCLIP;
		cSinEffect2[Index2].Angle.z = 0;
		cSinEffect2[Index2].Angle.y = rand() % 4096;
		cSinEffect2[Index2].MoveSpeed.z = 64;
	}
	return TRUE;

}

int sinEffect_Zenith(smCHAR *pChar, int Time)
{
	if(!pChar)return FALSE;
	int TempX = 0, TempZ = 0, TempSize;
	SetDynLight(pChar->pX, pChar->pY, pChar->pZ, 255, 255, 255, 255, 200, 1);
	for(int i = 0; i < 5; i++)
	{
		Index2 = sinSearchEmptyIndex();
		sinEffectDefaultSet(Index2, SIN_EFFECT_MESH, pChar, 0, 7000);
		cSinEffect2[Index2].ObjMat = MatZenith[i];
		cSinEffect2[Index2].pChar = pChar;
		cSinEffect2[Index2].CODE = SKILL_ZENITH;
		cSinEffect2[Index2].Max_Time = Time * 70;
		cSinEffect2[Index2].Index = i + 1;
		TempSize = 500;
		cSinEffect2[Index2].RotateDistance.z = 256 * 8 * 2;
		cSinEffect2[Index2].RotateAngle = 256 * (i + 1) * 3;
		cSinEffect2[Index2].RotatePosi.x = cSinEffect2[Index2].RotateDistance.y*GetCos[cSinEffect2[Index2].RotateAngle&ANGCLIP] + cSinEffect2[Index2].RotateDistance.z*GetSin[cSinEffect2[Index2].RotateAngle&ANGCLIP];
		cSinEffect2[Index2].RotatePosi.z = -cSinEffect2[Index2].RotateDistance.y*GetSin[cSinEffect2[Index2].RotateAngle&ANGCLIP] + cSinEffect2[Index2].RotateDistance.z*GetCos[cSinEffect2[Index2].RotateAngle&ANGCLIP];

		cSinEffect2[Index2].RotatePosi.x <<= 16;
		cSinEffect2[Index2].RotatePosi.z <<= 16;

		cSinEffect2[Index2].Posi.x += cSinEffect2[Index2].RotatePosi.x;
		cSinEffect2[Index2].Posi.z += cSinEffect2[Index2].RotatePosi.z;

		cSinEffect2[Index2].Size.x += TempSize;
		cSinEffect2[Index2].Size.y += TempSize;

		cSinEffect2[Index2].Angle.x = ANGLE_270;

		sinCreateObject(&cSinEffect2[Index2]);
	}

	return TRUE;
}

int sinEffect_Zenith_Particle(POINT3D *pPosi, int R, int G, int B)
{

	Index2 = sinSearchEmptyIndex();
	sinEffectDefaultSet(Index2, SIN_EFFECT_MESH, 0, pPosi, 0);
	cSinEffect2[Index2].ObjMat = MatHolyMind[0];
	cSinEffect2[Index2].CODE = SIN_PARTICLE_ZENITH;
	cSinEffect2[Index2].Max_Time = rand() % 5 + 20;
	cSinEffect2[Index2].Size.x = 200;
	cSinEffect2[Index2].Size.y = 200;
	cSinEffect2[Index2].Color_B = B;
	cSinEffect2[Index2].Color_R = R;
	cSinEffect2[Index2].Color_G = G;

	cSinEffect2[Index2].Angle.x = ANGLE_270;
	sinCreateObject(&cSinEffect2[Index2]);





	return TRUE;
}


int sinEffect_Healing(smCHAR *pChar)
{
	if(!pChar)return FALSE;
	int Size;
	SetDynLight(pChar->pX, pChar->pY, pChar->pZ, 255, 255, 255, 255, 200, 1);

	Index2 = sinSearchEmptyIndex();
	sinEffectDefaultSet(Index2, SIN_EFFECT_FACE, pChar, 0, 13000);
	cSinEffect2[Index2].sinFace.MatNum = MatAgony[0];
	Size = 2000;
	cSinEffect2[Index2].sinFace.height = Size;
	cSinEffect2[Index2].sinFace.width = Size;
	cSinEffect2[Index2].Max_Time = 70;
	cSinEffect2[Index2].CODE = SKILL_HEALING;
	cSinEffect2[Index2].RotateDistance.z = 128 * 24 * 2;
	cSinEffect2[Index2].BoneFlag = 1;
	cSinEffect2[Index2].Index = 1;

	Index2 = sinSearchEmptyIndex();
	sinEffectDefaultSet(Index2, SIN_EFFECT_FACE, pChar, 0, 13000);
	cSinEffect2[Index2].sinFace.MatNum = MatAgony[0];
	Size = 2000;
	cSinEffect2[Index2].sinFace.height = Size;
	cSinEffect2[Index2].sinFace.width = Size;
	cSinEffect2[Index2].Max_Time = 70;
	cSinEffect2[Index2].CODE = SKILL_HEALING;
	cSinEffect2[Index2].RotateDistance.z = 128 * 24 * 2;
	cSinEffect2[Index2].Index = 1;

	cSinEffect2[Index2].RotateAngle = 2048;
	cSinEffect2[Index2].RotatePosi.x = GetCos[cSinEffect2[Index2].RotateAngle&ANGCLIP] + cSinEffect2[Index2].RotateDistance.z*GetSin[cSinEffect2[Index2].RotateAngle&ANGCLIP];
	cSinEffect2[Index2].RotatePosi.z = -GetSin[cSinEffect2[Index2].RotateAngle&ANGCLIP] + cSinEffect2[Index2].RotateDistance.z*GetCos[cSinEffect2[Index2].RotateAngle&ANGCLIP];
	cSinEffect2[Index2].RotatePosi.x >>= 16;
	cSinEffect2[Index2].RotatePosi.z >>= 16;
	cSinEffect2[Index2].sinFace.x += cSinEffect2[Index2].RotatePosi.x;
	cSinEffect2[Index2].sinFace.z += cSinEffect2[Index2].RotatePosi.z;
	cSinEffect2[Index2].BoneFlag = 1;


	return TRUE;
}
int sinEffect_Healing_Particle2(POINT3D *pPosi)
{
	int Size;
	for(int i = 0; i < 1; i++)
	{
		Index2 = sinSearchEmptyIndex();
		sinEffectDefaultSet(Index2, SIN_EFFECT_FACE, 0, pPosi, 0);
		Size = rand() % 1500 + 1500;
		cSinEffect2[Index2].sinFace.height = Size;
		cSinEffect2[Index2].sinFace.width = Size;
		cSinEffect2[Index2].sinFace.MatNum = Matstun;
		cSinEffect2[Index2].Max_Time = rand() % 3 + 10;
		cSinEffect2[Index2].AlphaTime = 10;
		cSinEffect2[Index2].AlphaAmount = 10;
		cSinEffect2[Index2].AlphaCount = 1;

		cSinEffect2[Index2].Angle.x = ((rand() % (4096 / 2)) - ANGLE_90)&ANGCLIP;
		cSinEffect2[Index2].Angle.z = 0;
		cSinEffect2[Index2].Angle.y = rand() % 4096;
		cSinEffect2[Index2].MoveSpeed.z = 64;
		sinGetMoveLocation2(&cSinEffect2[Index2]);
		GetMoveLocation(0, 0, 64, cSinEffect2[Index2].Angle.x, cSinEffect2[Index2].Angle.y, 0);
		cSinEffect2[Index2].sinFace.x += GeoResult_X;
		cSinEffect2[Index2].sinFace.y += GeoResult_Y;
		cSinEffect2[Index2].sinFace.z += GeoResult_Z;


		cSinEffect2[Index2].SizeDecreTime = 1;
		cSinEffect2[Index2].SizeAmount = 150;




	}
	return TRUE;
}

int sinEffect_Healing_Particle(POINT3D *pPosi)
{

	int Size;
	Index2 = sinSearchEmptyIndex();
	sinEffectDefaultSet(Index2, SIN_EFFECT_FACE, 0, pPosi, 0);
	cSinEffect2[Index2].sinFace.MatNum = MatAgony[0];
	Size = rand() % 1000 + 500;
	cSinEffect2[Index2].sinFace.height = Size;
	cSinEffect2[Index2].sinFace.width = Size;
	cSinEffect2[Index2].Max_Time = 70;
	cSinEffect2[Index2].CODE = SIN_PARTICLE_HEALING;
	cSinEffect2[Index2].Gravity = rand() % 10 + 5;
	cSinEffect2[Index2].ActionTime[0] = 70;

	cSinEffect2[Index2].AlphaTime = cSinEffect2[Index2].Max_Time - 50;
	cSinEffect2[Index2].AlphaAmount = 5;
	cSinEffect2[Index2].AlphaCount = 1;


	cSinEffect2[Index2].sinFace.x += rand() % 100;
	cSinEffect2[Index2].sinFace.y += rand() % 100;
	cSinEffect2[Index2].sinFace.z += rand() % 100;

	cSinEffect2[Index2].MoveSpeed.x = rand() % 3;
	cSinEffect2[Index2].MoveSpeed.z = rand() % 3;
	cSinEffect2[Index2].MoveSpeed.y = rand() % 50 + 5;

	return TRUE;
}


int sinEffect_FireBolt_Particle2(POINT3D *pPosi)
{

	int Size;
	Index2 = sinSearchEmptyIndex();
	sinEffectDefaultSet(Index2, SIN_EFFECT_FACE, 0, pPosi, 0);
	Size = rand() % 500 + 500;
	cSinEffect2[Index2].sinFace.height = Size;
	cSinEffect2[Index2].sinFace.width = Size;
	cSinEffect2[Index2].sinFace.MatNum = MatFireBolt[0];
	cSinEffect2[Index2].Max_Time = rand() % 10 + 20;
	cSinEffect2[Index2].AlphaTime = 1;
	cSinEffect2[Index2].AlphaAmount = 20;
	cSinEffect2[Index2].AlphaCount = 1;

	cSinEffect2[Index2].Angle.x = ((rand() % (4096 / 2)) - ANGLE_90)&ANGCLIP;
	cSinEffect2[Index2].Angle.z = 0;
	cSinEffect2[Index2].Angle.y = rand() % 4096;
	cSinEffect2[Index2].MoveSpeed.z = 64;
	sinGetMoveLocation2(&cSinEffect2[Index2]);
	for(int j = 0; j < 5; j++)
	{
		GetMoveLocation(0, 0, 64, cSinEffect2[Index2].Angle.x, cSinEffect2[Index2].Angle.y, 0);
		cSinEffect2[Index2].sinFace.x += GeoResult_X;
		cSinEffect2[Index2].sinFace.y += GeoResult_Y;
		cSinEffect2[Index2].sinFace.z += GeoResult_Z;

	}
	cSinEffect2[Index2].SizeDecreTime = 1;
	cSinEffect2[Index2].SizeAmount = 50;

	return TRUE;
}

int sinEffect_FireBolt_Particle(POINT3D *pPosi)
{
	int Size;
	for(int i = 0; i < 1; i++)
	{
		Index2 = sinSearchEmptyIndex();
		sinEffectDefaultSet(Index2, SIN_EFFECT_FACE, 0, pPosi, 0);
		Size = rand() % 1300 + 1300;
		cSinEffect2[Index2].sinFace.height = Size;
		cSinEffect2[Index2].sinFace.width = Size;
		cSinEffect2[Index2].sinFace.MatNum = MatFireBolt[0];
		cSinEffect2[Index2].Max_Time = rand() % 3 + 5;
		cSinEffect2[Index2].AlphaTime = 1;
		cSinEffect2[Index2].AlphaAmount = 30;
		cSinEffect2[Index2].AlphaCount = 1;
		cSinEffect2[Index2].CODE = SIN_PARTICLE_FIREBOLT;
		cSinEffect2[Index2].Angle.x = ((rand() % (4096 / 2)) - ANGLE_90)&ANGCLIP;
		cSinEffect2[Index2].Angle.z = 0;
		cSinEffect2[Index2].Angle.y = rand() % 4096;
		cSinEffect2[Index2].MoveSpeed.z = 64;
		sinGetMoveLocation2(&cSinEffect2[Index2]);
		GetMoveLocation(0, 0, 64, cSinEffect2[Index2].Angle.x, cSinEffect2[Index2].Angle.y, 0);
		cSinEffect2[Index2].sinFace.x += GeoResult_X;
		cSinEffect2[Index2].sinFace.y += GeoResult_Y;
		cSinEffect2[Index2].sinFace.z += GeoResult_Z;


		cSinEffect2[Index2].SizeDecreTime = 1;
		cSinEffect2[Index2].SizeAmount = 200;

	}
	return TRUE;
}

int sinEffect_FireBolt(smCHAR *pChar, smCHAR *desChar)
{
	if(!pChar)return FALSE;
	int Size;
	SetDynLight(pChar->pX, pChar->pY, pChar->pZ, 255, 255, 255, 255, 200, 1);
	for(int i = 0; i < 10; i++)
	{
		Index2 = sinSearchEmptyIndex();
		sinEffectDefaultSet(Index2, SIN_EFFECT_FACE, pChar, 0, 10000);
		Size = 0;
		if(((i + 1) % 5) == 0)
			cSinEffect2[Index2].ActionTime[0] = 1;

		cSinEffect2[Index2].sinFace.height = Size;
		cSinEffect2[Index2].sinFace.width = Size;
		cSinEffect2[Index2].sinFace.MatNum = MatFireBolt[2];
		cSinEffect2[Index2].Max_Time = rand() % 5 + 10;
		cSinEffect2[Index2].Angle.x = ((rand() % (4096 / 2)) - ANGLE_90)&ANGCLIP;
		cSinEffect2[Index2].Angle.z = 0;
		cSinEffect2[Index2].Angle.y = rand() % 4096;
		cSinEffect2[Index2].MoveSpeed.z = 64;
		for(int j = 0; j < 1; j++)
		{
			sinGetMoveLocation2(&cSinEffect2[Index2]);
			GetMoveLocation(0, 0, 256, cSinEffect2[Index2].Angle.x, cSinEffect2[Index2].Angle.y, 0);
			cSinEffect2[Index2].sinFace.x += GeoResult_X;
			cSinEffect2[Index2].sinFace.y += GeoResult_Y;
			cSinEffect2[Index2].sinFace.z += GeoResult_Z;
		}
		cSinEffect2[Index2].Max_Time = 2000;
		cSinEffect2[Index2].CODE = SKILL_FIRE_BOLT;
		cSinEffect2[Index2].DesChar = desChar;
		if(cSinEffect2[Index2].DesChar)
		{
			cSinEffect2[Index2].MoveSpeed.x = (cSinEffect2[Index2].DesChar->pX - cSinEffect2[Index2].pChar->pX) / 70;
			cSinEffect2[Index2].MoveSpeed.y = (cSinEffect2[Index2].DesChar->pY - cSinEffect2[Index2].pChar->pY) / 70;
			cSinEffect2[Index2].MoveSpeed.z = (cSinEffect2[Index2].DesChar->pZ - cSinEffect2[Index2].pChar->pZ) / 70;
		}
		cSinEffect2[Index2].BoneFlag = 1;
	}

	return TRUE;
}


int sinEffect_Bomb6(POINT3D *pPosi)
{
	int Size;
	for(int i = 0; i < 20; i++)
	{

		Index2 = sinSearchEmptyIndex();
		sinEffectDefaultSet(Index2, SIN_EFFECT_FACE, 0, pPosi, 10000);
		Size = rand() % 500 + 500;
		cSinEffect2[Index2].sinFace.height = Size;
		cSinEffect2[Index2].sinFace.width = Size;
		cSinEffect2[Index2].sinFace.MatNum = MatFireBolt[0];

		cSinEffect2[Index2].RotatePosi.x >>= 16;
		cSinEffect2[Index2].RotatePosi.z >>= 16;
		cSinEffect2[Index2].sinFace.x += cSinEffect2[Index2].RotatePosi.x;
		cSinEffect2[Index2].sinFace.z += cSinEffect2[Index2].RotatePosi.z;

		cSinEffect2[Index2].Max_Time = 1000;
		cSinEffect2[Index2].CODE = SIN_EFFECT_BOMB5;
		cSinEffect2[Index2].Angle.x = ((rand() % (4096 / 2)) - ANGLE_90)&ANGCLIP;
		cSinEffect2[Index2].Angle.z = 0;
		cSinEffect2[Index2].Angle.y = rand() % 4096;
		cSinEffect2[Index2].MoveSpeed.z = 256;
		cSinEffect2[Index2].Gravity = 2;
		cSinEffect2[Index2].Time = (i % 3)*-1;
		cSinEffect2[Index2].BoneFlag = 1;

		for(int j = 0; j < 1; j++)
		{
			sinGetMoveLocation2(&cSinEffect2[Index2]);
			GetMoveLocation(0, 0, 256, cSinEffect2[Index2].Angle.x, cSinEffect2[Index2].Angle.y, 0);
			cSinEffect2[Index2].sinFace.x += GeoResult_X;
			cSinEffect2[Index2].sinFace.y += GeoResult_Y;
			cSinEffect2[Index2].sinFace.z += GeoResult_Z;
		}
	}
	return TRUE;
}

int sinEffect_Bomb6_Particle(POINT3D *pPosi)
{
	int Size;
	Index2 = sinSearchEmptyIndex();
	sinEffectDefaultSet(Index2, SIN_EFFECT_FACE, 0, pPosi, 0);
	Size = rand() % 300 + 300;
	cSinEffect2[Index2].sinFace.height = Size;
	cSinEffect2[Index2].sinFace.width = Size;
	cSinEffect2[Index2].sinFace.MatNum = MatBomb6[5];
	cSinEffect2[Index2].Max_Time = 30;
	cSinEffect2[Index2].AlphaTime = 15;
	cSinEffect2[Index2].AlphaAmount = 30;
	cSinEffect2[Index2].AlphaCount = 1;

	cSinEffect2[Index2].SizeDecreTime = 1;
	cSinEffect2[Index2].SizeAmount = 5;
	return TRUE;
}


int sinEffect_HealParticle3(POINT3D *pPosi, int Mat, int Num, int Size, int Time, int Gravity)
{
	int i;
	int TotalSize = 0;
	int TempIndex = 0;
	for(i = 0; i < Num; i++)
	{
		Index2 = sinSearchEmptyIndex();
		sinEffectDefaultSet(Index2, SIN_EFFECT_FACE, 0, pPosi, 0);
		cSinEffect2[Index2].sinFace.MatNum = Mat;
		TotalSize = rand() % Size + 200;
		cSinEffect2[Index2].sinFace.height = TotalSize;
		cSinEffect2[Index2].sinFace.width = TotalSize;
		cSinEffect2[Index2].Max_Time = rand() % 20 + Time;
		cSinEffect2[Index2].CODE = SIN_EFFECT_HEALING3;
		cSinEffect2[Index2].AniCount = 1;
		cSinEffect2[Index2].AlphaAmount = 10;
		cSinEffect2[Index2].AlphaCount = 1;
		cSinEffect2[Index2].AlphaTime = cSinEffect2[Index2].Max_Time - 22;
		cSinEffect2[Index2].Time = (i % 10)*-1;
		cSinEffect2[Index2].RotateAngle = ((rand() % 4096)) + Num;
		cSinEffect2[Index2].RotateDistance.z = 32;
		cSinEffect2[Index2].RotatePosi.x = GetCos[cSinEffect2[Index2].RotateAngle&ANGCLIP] + cSinEffect2[Index2].RotateDistance.z*GetSin[cSinEffect2[Index2].RotateAngle&ANGCLIP];
		cSinEffect2[Index2].RotatePosi.z = -GetSin[cSinEffect2[Index2].RotateAngle&ANGCLIP] + cSinEffect2[Index2].RotateDistance.z*GetCos[cSinEffect2[Index2].RotateAngle&ANGCLIP];
		cSinEffect2[Index2].RotatePosi.x >>= 16;
		cSinEffect2[Index2].RotatePosi.z >>= 16;
		cSinEffect2[Index2].sinFace.x += cSinEffect2[Index2].RotatePosi.x;
		cSinEffect2[Index2].sinFace.z += cSinEffect2[Index2].RotatePosi.z;
		cSinEffect2[Index2].MoveSpeed.y = rand() % 20 + 10;
		cSinEffect2[Index2].Gravity = Gravity;


		cSinEffect2[Index2].sinFace.r = 24;
		cSinEffect2[Index2].sinFace.g = 107;
		cSinEffect2[Index2].sinFace.b = 74;

		TempIndex = Index2;
		Index2 = sinSearchEmptyIndex();
		memcpy(&cSinEffect2[Index2], &cSinEffect2[TempIndex], sizeof(cSINEFFECT2));




	}
	return TRUE;
}

int sinEffect_Healing2(smCHAR *pChar)
{
	if(!pChar)return FALSE;
	SetDynLight(pChar->pX, pChar->pY, pChar->pZ, 255, 255, 255, 255, 200, 1);

	for(int i = 0; i < 1; i++)
	{

		Index2 = sinSearchEmptyIndex();
		cSinEffect2[Index2].sinPatMesh = smASE_ReadBone("image\\Sinimage\\Effect\\SkillEffect\\Healing\\HIALTEST.ASE");
		smASE_SetPhysique(cSinEffect2[Index2].sinPatMesh);
		sinEffectDefaultSet(Index2, SIN_EFFECT_MESH, pChar, 0, 13000);




		cSinEffect2[Index2].BoneFlag = 1;



		Index2 = sinSearchEmptyIndex();
		sinEffectDefaultSet(Index2, SIN_EFFECT_MESH, pChar, 0, 7000);
		cSinEffect2[Index2].sinPatMesh = smASE_Read("image\\Sinimage\\Effect\\SkillEffect\\Healing\\HIALTEST.ASE");
		cSinEffect2[Index2].sinPatMesh->ZeroNormals();
		smASE_SetPhysique(0);
		cSinEffect2[Index2].Max_Time = 250;
		cSinEffect2[Index2].AniCount = 1;
		cSinEffect2[Index2].AniMax = 30;
		cSinEffect2[Index2].AniTime = 10;

		cSinEffect2[Index2].AniTime = 1;
		cSinEffect2[Index2].Color_A = 150;
		cSinEffect2[Index2].CODE = SKILL_HEALING;
		cSinEffect2[Index2].RotateAngle = 256;
		cSinEffect2[Index2].RotateDistance.z = 256 * 16;
		cSinEffect2[Index2].Angle.y = (-(pChar->Angle.y&ANGCLIP) + ANGLE_180)&ANGCLIP;
		cSinEffect2[Index2].MoveSpeed.y = 200;
		cSinEffect2[Index2].AlphaAmount = 10;
		cSinEffect2[Index2].AlphaTime = cSinEffect2[Index2].Max_Time - 20;
		cSinEffect2[Index2].AlphaCount = 1;


		if(cSinEffect2[Index2].sinPatMesh)
			cSinEffect2[Index2].sinPatMesh->smMaterialGroup->ReadTextures();

	}

	return TRUE;
}


int sinEffect_Shield_Strike(POINT3D *pPosi)
{
	int TempSize = 5000;
	ShieldStrikeTime++;

	Index2 = sinSearchEmptyIndex();
	sinEffectDefaultSet(Index2, SIN_EFFECT_MESH, 0, pPosi, 0);
	cSinEffect2[Index2].ObjMat = MatShieldStrike[2];
	cSinEffect2[Index2].Max_Time = 3;
	cSinEffect2[Index2].Size.x += TempSize;
	cSinEffect2[Index2].Size.y += TempSize;

	cSinEffect2[Index2].Color_A = (255 - ShieldStrikeTime * 5);
	if(cSinEffect2[Index2].Color_A < 150)
		cSinEffect2[Index2].Color_A = 150;
	cSinEffect2[Index2].Angle.y += ShieldStrikeTime * 8;
	cSinEffect2[Index2].Angle.x &= ANGCLIP;


	sinCreateObject(&cSinEffect2[Index2]);





	if(ShieldStrikeTime > 15)return FALSE;
	int Size;
	for(int i = 0; i < 5; i++)
	{
		Index2 = sinSearchEmptyIndex();
		sinEffectDefaultSet(Index2, SIN_EFFECT_FACE, 0, pPosi, 0);
		Size = rand() % 1000 + 1000;
		cSinEffect2[Index2].sinFace.height = Size;
		cSinEffect2[Index2].sinFace.width = Size;
		cSinEffect2[Index2].sinFace.MatNum = MatShieldStrike[0];
		cSinEffect2[Index2].Max_Time = rand() % 3 + 15;
		cSinEffect2[Index2].AlphaTime = 4;
		cSinEffect2[Index2].AlphaAmount = 20;
		cSinEffect2[Index2].AlphaCount = 1;
		cSinEffect2[Index2].CODE = SKILL_SHIELD_STRIKE;
		cSinEffect2[Index2].Angle.x = rand() % 4096;
		cSinEffect2[Index2].Angle.z = 0;
		cSinEffect2[Index2].Angle.y = rand() % 4096;
		cSinEffect2[Index2].MoveSpeed.z = 64;

		sinGetMoveLocation2(&cSinEffect2[Index2]);
		GetMoveLocation(0, 0, 128 * i, cSinEffect2[Index2].Angle.x, cSinEffect2[Index2].Angle.y, 0);
		cSinEffect2[Index2].sinFace.x += GeoResult_X;
		cSinEffect2[Index2].sinFace.y += GeoResult_Y;
		cSinEffect2[Index2].sinFace.z += GeoResult_Z;


		cSinEffect2[Index2].SizeDecreTime = 1;
		cSinEffect2[Index2].SizeAmount = 300;
		cSinEffect2[Index2].sinFace.Transparency = 150;


	}
	return TRUE;
}
int sinEffect_Shield_Strike_Particle(POINT3D *pPosi)
{

	int Size;
	Index2 = sinSearchEmptyIndex();
	sinEffectDefaultSet(Index2, SIN_EFFECT_FACE, 0, pPosi, 0);
	Size = rand() % 300 + 300;
	cSinEffect2[Index2].sinFace.height = Size;
	cSinEffect2[Index2].sinFace.width = Size;
	cSinEffect2[Index2].sinFace.MatNum = MatShieldStrike[1];
	cSinEffect2[Index2].Max_Time = rand() % 10 + 20;
	cSinEffect2[Index2].AlphaTime = 10;
	cSinEffect2[Index2].AlphaAmount = 10;
	cSinEffect2[Index2].AlphaCount = 1;
	cSinEffect2[Index2].Angle.x = rand() % 4096;
	cSinEffect2[Index2].Angle.z = 0;
	cSinEffect2[Index2].Angle.y = rand() % 4096;
	cSinEffect2[Index2].CODE = SIN_PARTICLE_SHEILDSTRIKE;
	cSinEffect2[Index2].sinFace.Transparency = 150;

	return TRUE;
}

int sinEffect_SkillHit(DWORD CODE, POINT3D *pPosi)
{
	switch(CODE)
	{
		case SKILL_FARINA:
		sinEffect_WideLine(pPosi, MatFarina[6], 128, 30);
		sinEffect_BombParticle(pPosi, MatFarina[6], 1000, 30);
		sinEffect_Light5(pPosi, 10000);
		SetDynLight(pPosi->x, pPosi->y, pPosi->z, 255, 95, 253, 255, 230, 1);
		break;
		case SKILL_VIGOR_SPEAR:
		sinEffect_WideLine(pPosi, MatVigorSpear[0], 128, 40);
		sinEffect_BombParticle(pPosi, MatVigorSpear[0], 1000, 30);
		sinEffect_Light5(pPosi, 13000);
		SetDynLight(pPosi->x, pPosi->y, pPosi->z, 125, 212, 250, 255, 230, 1);
		break;
		case SKILL_MULTISPARK:
		sinEffect_WideLine(pPosi, MatMultiSpark[6], 128, 30);
		sinEffect_BombParticle(pPosi, MatMultiSpark[6], 1000, 35);
		sinEffect_Light5(pPosi, 13000);
		SetDynLight(pPosi->x, pPosi->y, pPosi->z, 179, 255, 229, 255, 180, 1);

		break;

	}
	return TRUE;

}


int sinEffect_SetCharPosi(cSINEFFECT2 *pEffect)
{
	if(pEffect->pChar && pEffect->DesChar)
	{
		pEffect->CharPosi.x = pEffect->pChar->pX;
		pEffect->CharPosi.y = pEffect->pChar->pY;
		pEffect->CharPosi.z = pEffect->pChar->pZ;

		pEffect->DesCharPosi.x = pEffect->DesChar->pX;
		pEffect->DesCharPosi.y = pEffect->DesChar->pY;
		pEffect->DesCharPosi.z = pEffect->DesChar->pZ;
	}
	return TRUE;
}



int sinEfect_CheckCrash(cSINEFFECT2 *pEffect)
{
	int Count = 0;
	pEffect->CharPosi.x += pEffect->MoveSpeed.x;
	pEffect->CharPosi.y += pEffect->MoveSpeed.y;
	pEffect->CharPosi.z += pEffect->MoveSpeed.z;

	if(!pEffect->DesChar)return FALSE;
	if(pEffect->MoveSpeed.x >= 0)
	{
		if(pEffect->Posi.x >= pEffect->DesChar->pX + 1000)
		{
			pEffect->CrashCheckCount[0]++;
		}
	}
	else
	{
		if(pEffect->Posi.x <= pEffect->DesChar->pX + 1000)
		{
			pEffect->CrashCheckCount[0]++;
		}
	}

	if(pEffect->MoveSpeed.z >= 0)
	{
		if(pEffect->Posi.z >= pEffect->DesChar->pZ + 1000)
		{
			pEffect->CrashCheckCount[2]++;
		}
	}
	else
	{
		if(pEffect->Posi.z <= pEffect->DesChar->pZ + 1000)
		{
			pEffect->CrashCheckCount[2]++;
		}
	}
	for(int i = 0; i < 3; i++)
	{
		if(pEffect->CrashCheckCount[i])
		{
			Count++;
		}
	}
	if(Count == 2)
	{
		return TRUE;
	}
	return FALSE;
}

int sinEffect_StartMagic(POINT3D *pPosi, int CharFlag, int Type)
{

	if(Type)
	{
		Assa = SetAssaEffect(0, "MAAM2.ASE", 0, pPosi, 1500);
		cAssaEffect[Assa]->AniMaxCount = 20;
		cAssaEffect[Assa]->AniDelayTime = 4;
		Assa = SetAssaEffect(160, "maam2.tga", 0, pPosi, 1500);
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_WORLD;
		cAssaEffect[Assa]->Size.w = 4800 * 10;





		Assa = SetAssaEffect(160, "star05Q_03.bmp", 0, pPosi, 1500);
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_WORLD;
		cAssaEffect[Assa]->Size.w = 6200 * 10;
		cAssaEffect[Assa]->MaxAlphaAmount = 120;





	}
	else
	{

		int TempIndex = 0;
		if(!CharFlag) return FALSE;
		if(CharFlag == 1)
		{
			Assa = SetAssaEffect(0, "MAAM1.ASE", 0, pPosi, 1500);
			cAssaEffect[Assa]->AniMaxCount = 20;
			cAssaEffect[Assa]->AniDelayTime = 4;
			Assa = SetAssaEffect(160, "mama.tga", 0, pPosi, 1500);
			cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_WORLD;
			cAssaEffect[Assa]->Size.w = 5300 * 3;

			Assa = SetAssaEffect(160, "star05C_03.bmp", 0, pPosi, 1500);
			cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_WORLD;
			cAssaEffect[Assa]->Size.w = 6200 * 3;
			cAssaEffect[Assa]->MaxAlphaAmount = 120;
		}

		if(CharFlag == 2)
		{
			Assa = SetAssaEffect(0, "MAAM2.ASE", 0, pPosi, 1500);
			cAssaEffect[Assa]->AniMaxCount = 20;
			cAssaEffect[Assa]->AniDelayTime = 4;
			Assa = SetAssaEffect(160, "maam2.tga", 0, pPosi, 1500);
			cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_WORLD;
			cAssaEffect[Assa]->Size.w = 4800 * 3;

			Assa = SetAssaEffect(160, "star05Q_03.bmp", 0, pPosi, 1500);
			cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_WORLD;
			cAssaEffect[Assa]->Size.w = 6200 * 3;
			cAssaEffect[Assa]->MaxAlphaAmount = 120;
		}

		if (CharFlag == 10)
		{

			Assa = SetAssaEffect(0, "MAAM6.ASE", 0, pPosi, 1500);
			cAssaEffect[Assa]->AniMaxCount = 20;
			cAssaEffect[Assa]->AniDelayTime = 4;
			Assa = SetAssaEffect(160, "ShamanMagic.tga", 0, pPosi, 1500);
			cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_WORLD;
			cAssaEffect[Assa]->Size.w = 4800 * 3;
			cAssaEffect[Assa]->ARotateSpeed.y = 100;
			Assa = SetAssaEffect(160, "star05Q_03.bmp", 0, pPosi, 1500);
			cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_WORLD;
			cAssaEffect[Assa]->Size.w = 6200 * 3;
			cAssaEffect[Assa]->MaxAlphaAmount = 120;
		}

	}



	return TRUE;
}

DWORD dwProcessTime = 0;
void sinProcess7()
{

	if(ShieldStrikeTime)
	{
		dwProcessTime++;
		if(dwProcessTime > 120)
		{
			dwProcessTime = 0;
			ShieldStrikeTime = 0;

		}
	}

}
