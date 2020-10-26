

#include "sinLinkHeader.h"
#include "..\\field.h"


cASSAEFFECT *cAssaEffect[cASSAEFFECT_MAX];
sinEFFECT_ZDEPTH sinEffect_Zdepth3[cASSAEFFECT_MAX];
int Assa;


void AssaEffectKeyDown()
{
	sinAssaSkillEffectKeyDown();
	sinAssaParticleKeyDown();
	sinAssaParticleTestKeyDown();
	YameEffectKeyDown();








	POINT3D Posi = { lpCurPlayer->pX,lpCurPlayer->pY + 10000,lpCurPlayer->pZ };


}

void InitAssaEffect()
{

	InitAssaRes();


	LoadAssaRes();


	memset(cAssaEffect, 0, sizeof(cASSAEFFECT));

}

void DrawAssaEffect(POINT3D *pPosi, POINT3D *pAngle)
{

	int i = 0;
	int IndexCount = 0;



	for(i = 0; i < cASSAEFFECT_MAX; i++)
	{
		if(cAssaEffect[i] && !cAssaEffect[i]->Bone && cAssaEffect[i]->Time > 0)
		{
			smRender.SetCameraPosi(pPosi->x, pPosi->y, pPosi->z, pAngle->x, pAngle->y, pAngle->z);
			for(int j = 0; j < cASSAEFFECT_MAX; j++)
			{
				if(!sinEffect_Zdepth3[j].Index)
				{
					sinEffect_Zdepth3[j].ZDepth = smRender.GetDepthZ(cAssaEffect[i]->Posi.x, cAssaEffect[i]->Posi.y, cAssaEffect[i]->Posi.z);
					sinEffect_Zdepth3[j].Index = i + 1;
					IndexCount++;
					break;
				}
			}
		}
	}

	sinBubbleSort(sinEffect_Zdepth3, IndexCount - 1);
	for(i = 0; i < IndexCount; i++)
	{
		if(sinEffect_Zdepth3[i].Index)
		{
			renderDevice.BeginScene();
			if(cAssaEffect[sinEffect_Zdepth3[i].Index - 1]->pChar)
			{
				if(cAssaEffect[sinEffect_Zdepth3[i].Index - 1]->pChar->FlagShow != 0)
				{
					cAssaEffect[sinEffect_Zdepth3[i].Index - 1]->Draw(pPosi, pAngle);
				}
			}
			else
				cAssaEffect[sinEffect_Zdepth3[i].Index - 1]->Draw(pPosi, pAngle);
			renderDevice.EndScene();
		}
	}
	memset(sinEffect_Zdepth3, 0, sizeof(sinEFFECT_ZDEPTH)*cASSAEFFECT_MAX);

}

void MainAssaEffect()
{

	for(int i = 0; i < cASSAEFFECT_MAX; i++)
	{
		if(cAssaEffect[i])
		{
			cAssaEffect[i]->Time++;
			cAssaEffect[i]->Main();

			if(cAssaEffect[i]->Time > 0)
				MoveAssaEffect(cAssaEffect[i]);

			if(cAssaEffect[i]->Time >= cAssaEffect[i]->Max_Time)
			{
				delete cAssaEffect[i];
				cAssaEffect[i] = NULL;

			}
		}
	}
}

void CloseAssaEffect()
{


}

void MoveAssaEffect(cASSAEFFECT *pEffect)
{
	sinAssaSkillEffectProcess(pEffect);
	sinAssaParticleProcess(pEffect);
	sinAssaParticleTestProcess(pEffect);



	switch(pEffect->FACE_TYPE)
	{
		case ASSAFACE_SCALE:
		pEffect->ScalePosi.x += pEffect->ScaleSpeed.x;
		pEffect->ScalePosi.y += pEffect->ScaleSpeed.y;
		pEffect->ScalePosi.z += pEffect->ScaleSpeed.z;
		break;
		case ASSAFACE_TRACE:

		pEffect->cAssaTrace->AddData(&pEffect->Posi);

		break;

	}



	if(pEffect->MOVECODE == ASSA_MOVE_RANDOM_ROTATE)
	{
		pEffect->Angle.y += pEffect->RAngleSpeed;
		pEffect->Angle.y &= ANGCLIP;
		GetMoveLocation(pEffect->MoveSpeed.x, pEffect->MoveSpeed.y, pEffect->MoveSpeed.z, 0, pEffect->Angle.y, 0);
		POINT3D tempGeoResult;
		tempGeoResult.x = GeoResult_X;
		tempGeoResult.y = GeoResult_Y;
		tempGeoResult.z = GeoResult_Z;
		GetMoveLocation(tempGeoResult.x, tempGeoResult.y, tempGeoResult.z, pEffect->Angle.x, 0, 0);
		if(pEffect->MOVECODESUB & ASSA_CHAR_POSI)
		{
			pEffect->Posi.x = pEffect->pChar->pX + GeoResult_X;
			pEffect->Posi.z = pEffect->pChar->pZ + GeoResult_Z;
			pEffect->Posi.y = pEffect->pChar->pY + GeoResult_Y + pEffect->AddHeight;
		}
		else
		{
			pEffect->Posi.x = pEffect->CenterPosi.x + GeoResult_X;
			pEffect->Posi.z = pEffect->CenterPosi.z + GeoResult_Z;
			pEffect->Posi.y = pEffect->CenterPosi.y + GeoResult_Y;
		}
		return;
	}

	if(pEffect->MOVECODE == ASSA_MOVE_SPREAD)
	{

		pEffect->RPosi.x = pEffect->RDistance.y*GetCos[pEffect->RAngle&ANGCLIP] + pEffect->RDistance.z*GetSin[pEffect->RAngle&ANGCLIP];
		pEffect->RPosi.z = -pEffect->RDistance.y*GetSin[pEffect->RAngle&ANGCLIP] + pEffect->RDistance.z*GetCos[pEffect->RAngle&ANGCLIP];

		pEffect->RPosi.x >>= 16;
		pEffect->RPosi.z >>= 16;
		pEffect->Posi.x += pEffect->RPosi.x;
		pEffect->Posi.z += pEffect->RPosi.z;
		pEffect->MoveSpeed.y -= pEffect->Gravity;
		pEffect->Posi.y += pEffect->MoveSpeed.y;
		return;

	}


	if(pEffect->MOVECODE & ASSA_ROTATE)
	{
		pEffect->RAngle += pEffect->RAngleSpeed;
		pEffect->RPosi.x = pEffect->RDistance.y*GetCos[pEffect->RAngle&ANGCLIP] + pEffect->RDistance.z*GetSin[pEffect->RAngle&ANGCLIP];
		pEffect->RPosi.z = -pEffect->RDistance.y*GetSin[pEffect->RAngle&ANGCLIP] + pEffect->RDistance.z*GetCos[pEffect->RAngle&ANGCLIP];

		pEffect->RPosi.x >>= 16;
		pEffect->RPosi.z >>= 16;
		pEffect->Posi.x = pEffect->CenterPosi.x + pEffect->RPosi.x;
		pEffect->Posi.z = pEffect->CenterPosi.z + pEffect->RPosi.z;

		if(pEffect->MOVECODE & ASSA_CHAR_POSI)
		{
			if(pEffect->pChar)
			{
				pEffect->Posi.x = pEffect->pChar->pX + pEffect->RPosi.x;
				pEffect->Posi.z = pEffect->pChar->pZ + pEffect->RPosi.z;

			}
		}
	}
	if(pEffect->MOVECODE & ASSA_MOVE)
	{
		pEffect->Posi.x += pEffect->MoveSpeed.x;
		pEffect->Posi.y += pEffect->MoveSpeed.y;
		pEffect->Posi.z += pEffect->MoveSpeed.z;



		if(pEffect->MOVECODE & ASSA_CHAR_POSI)
		{
			if(pEffect->pChar)
			{
				pEffect->MovePosi.x += pEffect->MoveSpeed.x;
				pEffect->MovePosi.y += pEffect->MoveSpeed.y;
				pEffect->MovePosi.z += pEffect->MoveSpeed.z;




			}
		}
	}
	if(pEffect->MOVECODE & ASSA_ANGLE_ROTATE)
	{
		if(pEffect->ARotateSpeed.x != 0)
		{
			pEffect->ARotate.x += pEffect->ARotateSpeed.x;
			pEffect->Angle.x = (pEffect->ARotate.x + ANGLE_90)&ANGCLIP;

		}
		if(pEffect->ARotateSpeed.y != 0)
		{
			if(pEffect->ARotateSpeed.y != 10000)
			{
				pEffect->ARotate.y += pEffect->ARotateSpeed.y;
			}
			pEffect->Angle.y = (pEffect->ARotate.y + ANGLE_90)&ANGCLIP;

		}
		if(pEffect->ARotateSpeed.z != 0)
		{
			pEffect->ARotate.z += pEffect->ARotateSpeed.z;
			pEffect->Angle.z = (pEffect->ARotate.z + ANGLE_90)&ANGCLIP;

		}
		if(pEffect->MOVECODE & ASSA_CHAR_POSI)
		{
			if(pEffect->pChar)
			{
				pEffect->Posi.x = pEffect->pChar->pX;
				pEffect->Posi.y = pEffect->pChar->pY + pEffect->AddHeight;
				pEffect->Posi.z = pEffect->pChar->pZ;


			}
		}

	}
	if(pEffect->MOVECODE & ASSA_MOVE_ANGLE_SPEED)
	{
		if(!pEffect->Angle.x && !pEffect->Angle.y && !pEffect->Angle.z)
		{
			pEffect->Angle.x = rand() % 4096;
			pEffect->Angle.y = rand() % 4096;
		}
		AssaGetMoveLocation(pEffect);

	}
	if(pEffect->MOVECODE & ASSA_DECRESIZE)
	{
		if(!pEffect->ReSize.w)pEffect->ReSize.w = pEffect->Size.w / pEffect->Max_Time;
		if(!pEffect->ReSize.h)pEffect->ReSize.h = pEffect->Size.h / pEffect->Max_Time;
		pEffect->Size.w -= pEffect->ReSize.w;
		pEffect->Size.h -= pEffect->ReSize.h;
	}

	if(pEffect->MOVECODE & ASSA_INCRESIZE)
	{
		if(!pEffect->ReSize.w)pEffect->ReSize.w = pEffect->Size.w / pEffect->Max_Time;
		if(!pEffect->ReSize.h)pEffect->ReSize.h = pEffect->Size.h / pEffect->Max_Time;
		pEffect->Size.w += pEffect->ReSize.w;
		pEffect->Size.h += pEffect->ReSize.h;
	}
	if(pEffect->MOVECODE & ASSA_MOVE_GATHER)
	{
		if(pEffect->Temp[9] == 0)
		{
			pEffect->TempPosi.x = pEffect->CenterPosi.x - pEffect->Posi.x;
			pEffect->TempPosi.y = pEffect->CenterPosi.y - pEffect->Posi.y;
			pEffect->TempPosi.z = pEffect->CenterPosi.z - pEffect->Posi.z;
			pEffect->Temp[9] = 1;
		}
		if(pEffect->Posi.x - 500 < pEffect->CenterPosi.x && pEffect->Posi.x + 500 >= pEffect->CenterPosi.x)
		{


		}
		else pEffect->Posi.x += pEffect->TempPosi.x / pEffect->GatherSpeed;
		if(pEffect->Posi.z - 500 < pEffect->CenterPosi.z && pEffect->Posi.z + 500 >= pEffect->CenterPosi.z)
		{


		}
		else pEffect->Posi.z += pEffect->TempPosi.z / pEffect->GatherSpeed;



		if(pEffect->Posi.y - 500 < pEffect->CenterPosi.y && pEffect->Posi.y + 500 >= pEffect->CenterPosi.y)
		{

		}
		else
		{

			pEffect->Posi.y += pEffect->TempPosi.y / pEffect->GatherSpeed;


		}
	}

	if(pEffect->MOVECODE == ASSA_CHAR_POSI)
	{
		if(pEffect->Temp[8] == 0)
		{
			pEffect->TempPosi.x = pEffect->pChar->pX - pEffect->Posi.x;
			pEffect->TempPosi.y = (pEffect->pChar->pY + pEffect->AddHeight) - pEffect->Posi.y;
			pEffect->TempPosi.z = pEffect->pChar->pZ - pEffect->Posi.z;
			pEffect->Temp[8] = 1;
		}
		pEffect->Posi.x = pEffect->pChar->pX + pEffect->TempPosi.x;
		pEffect->Posi.y = pEffect->pChar->pY + pEffect->TempPosi.y + pEffect->AddHeight;
		pEffect->Posi.z = pEffect->pChar->pZ + pEffect->TempPosi.z;
		pEffect->Angle.y = (-(pEffect->pChar->Angle.y&ANGCLIP) + ANGLE_180)&ANGCLIP;

	}
}


void StopAssaEffect(cASSAEFFECT *pEffect)
{

	pEffect->Time = pEffect->Max_Time;
}



int  SetAssaEffect(int MaxTime, char *FileName, smCHAR *pChar, POINT3D *pPosi, int AddHeight, int BlendTpye)
{
	char TempFileName[64];
	char FileFormat[32];

	WORD wBlendType = 0;
	switch(BlendTpye)
	{
		case 0:
		wBlendType = SMMAT_BLEND_LAMP;
		break;
		case 1:
		wBlendType = SMMAT_BLEND_ALPHA;
		break;
		case 2:
		wBlendType = SMMAT_BLEND_COLOR;
		break;
		case 3:
		wBlendType = SMMAT_BLEND_SHADOW;
		break;
		case 4:
		wBlendType = SMMAT_BLEND_ADDCOLOR;
		break;
		case 5:
		wBlendType = SMMAT_BLEND_INVSHADOW;
		break;
	}

	FileFormat[0] = 0;

	strcpy_s(TempFileName, FileName);
	int len = lstrlen(TempFileName);
	for(int i = 0; i < len; i++)
	{
		if(TempFileName[i] == '.')
		{
			strcpy(FileFormat, &TempFileName[i + 1]);
			break;
		}
	}

	for(int i = 0; i < cASSAEFFECT_MAX; i++)
	{
		if(!cAssaEffect[i])
		{

			if(stricmp(FileName, "Bone") == 0)
			{
				cASSAFACE *pFace = new cASSAFACE;
				cAssaEffect[i] = pFace;
				cAssaEffect[i]->Bone = 1;


			}
			if(stricmp(FileFormat, "bmp") == 0 || stricmp(FileFormat, "tga") == 0)
			{
				cASSAFACE *pFace = new cASSAFACE;
				cAssaEffect[i] = pFace;
				cAssaEffect[i]->Face.r = 255;
				cAssaEffect[i]->Face.g = 255;
				cAssaEffect[i]->Face.b = 255;
				cAssaEffect[i]->Face.Transparency = 255;
				cAssaEffect[i]->Face.TexRect = sinTexRect;
				cAssaEffect[i]->Face.MatNum = *(int *)AssaSearchRes(FileName, wBlendType);

			}
			if(stricmp(FileFormat, "ase") == 0)
			{
				cASSAMESH *pMesh = new cASSAMESH;
				cAssaEffect[i] = pMesh;
				cAssaEffect[i]->PatMesh = (smPAT3D *)AssaSearchRes(FileName, wBlendType);

			}
			if(pChar)
			{
				cAssaEffect[i]->Posi.x = pChar->pX;
				cAssaEffect[i]->Posi.y = pChar->pY;
				cAssaEffect[i]->Posi.z = pChar->pZ;
				cAssaEffect[i]->pChar = pChar;
				if(cAssaEffect[i]->pChar == lpCurPlayer)cAssaEffect[i]->MyPointerFlag = 1;

			}
			if(pPosi)
			{
				cAssaEffect[i]->Posi.x = pPosi->x;
				cAssaEffect[i]->Posi.y = pPosi->y;
				cAssaEffect[i]->Posi.z = pPosi->z;
			}
			strcpy_s(cAssaEffect[i]->szFileName, FileName);
			cAssaEffect[i]->AddHeight = AddHeight;
			cAssaEffect[i]->Posi.y += AddHeight;
			cAssaEffect[i]->Max_Time = MaxTime;
			cAssaEffect[i]->CenterPosi = cAssaEffect[i]->Posi;
			if(pChar)
			{
				cAssaEffect[i]->Angle.y = (-(pChar->Angle.y&ANGCLIP) + ANGLE_180)&ANGCLIP;
			}
			return i;
		}
	}
	return FALSE;

}

int AssaSetAngle(cASSAEFFECT *pEffect, int AngleKind)
{
	switch(AngleKind)
	{
		case ASSA_ANG_CHAR:
		if(pEffect->pChar)
		{
			pEffect->Angle.y = (-(pEffect->Angle.y&ANGCLIP) + ANGLE_180)&ANGCLIP;

		}
		break;
		case ASSA_ANG_DESCHAR:
		if(pEffect->pChar && pEffect->desChar)
		{
			GetRadian3D(pEffect->pChar->pX, pEffect->pChar->pY, pEffect->pChar->pZ, pEffect->desChar->pX, pEffect->desChar->pY, pEffect->desChar->pZ);
			pEffect->Angle.x = GeoResult_X;
			pEffect->Angle.y = (-(GeoResult_Y&ANGCLIP) + ANGLE_180)&ANGCLIP;
		}
		break;
		case ASSA_ANG_BONE:
		if(pEffect->pChar && pEffect->desChar)
		{
			GetRadian3D(pEffect->pChar->pX, pEffect->pChar->pY, pEffect->pChar->pZ, pEffect->desChar->pX, pEffect->desChar->pY, pEffect->desChar->pZ);
			pEffect->Angle.x = GeoResult_X;
			pEffect->Angle.y = GeoResult_Y;
		}
		break;

	}
	return TRUE;
}


int AssaSetStartPosi(cASSAEFFECT *pEffect)
{
	if(!pEffect->Angle.x && !pEffect->Angle.y && !pEffect->Angle.z)
	{
		pEffect->Angle.x = rand() % 4096;
		pEffect->Angle.y = rand() % 4096;
	}


	GetMoveLocation(pEffect->StartPosi.x, pEffect->StartPosi.y, pEffect->StartPosi.z, pEffect->Angle.x, pEffect->Angle.y, 0);
	pEffect->Posi.x += GeoResult_X;
	pEffect->Posi.y += GeoResult_Y;
	pEffect->Posi.z += GeoResult_Z;

	return TRUE;
}

int AssaCopyEffect(cASSAEFFECT *pEffect)
{


	return FALSE;
}


int AssaGetAniFileMat(cASSAEFFECT *pEffect)
{

	char TempFileName[64];
	char FirstFileName[64];
	char FileFormat[32];
	char TotalFileName[128];
	char szIndex[2];
	int  FileIndex = 0;
	int  *MatNum = 0;

	strcpy_s(TempFileName, pEffect->szFileName);
	for(int i = 0; i < lstrlen(TempFileName); i++)
	{
		if(TempFileName[i + 1] == '.')
		{
			memcpy(&szIndex, &TempFileName[i], 2);
			TempFileName[i] = '\0'; TempFileName[i + 1] = '\0';
			FileIndex = atoi(szIndex);
			strcpy(FirstFileName, TempFileName);
			strcpy(FileFormat, &TempFileName[i + 2]);
			break;
		}
	}

	for(int i = 0; i < 10; i++)
	{
		wsprintf(TotalFileName, "%s%d.%s", FirstFileName, FileIndex++, FileFormat);
		int *MatNum = (int *)AssaSearchRes(TotalFileName, SMMAT_BLEND_LAMP);
		if(MatNum)
		{
			pEffect->AniMatIndex[i] = *MatNum;
			pEffect->AniMaxCount++;
		}
		else break;

	}
	return TRUE;
}


#define ASSA_ANG_FLOAT	(5+FLOATNS) 
int AssaGetMoveLocation(cASSAEFFECT *pEffect)
{
	int i, j, k;
	int dx, dy, dz;

	int sinX, sinY, sinZ;
	int cosX, cosY, cosZ;

	pEffect->Angle.x &= ANGCLIP;
	pEffect->Angle.y &= ANGCLIP;
	pEffect->Angle.z &= ANGCLIP;

	sinX = sdGetSin[pEffect->Angle.x] >> 2;
	sinY = sdGetSin[pEffect->Angle.y] >> 2;
	sinZ = sdGetSin[pEffect->Angle.z] >> 2;
	cosX = sdGetCos[pEffect->Angle.x] >> 2;
	cosY = sdGetCos[pEffect->Angle.y] >> 2;
	cosZ = sdGetCos[pEffect->Angle.z] >> 2;


	i = (pEffect->MoveSpeed.x * cosZ - pEffect->MoveSpeed.y * sinZ) >> ASSA_ANG_FLOAT;
	j = (pEffect->MoveSpeed.x * sinZ + pEffect->MoveSpeed.y * cosZ) >> ASSA_ANG_FLOAT;
	k = pEffect->MoveSpeed.z;


	dy = (j * cosX - k * sinX) >> ASSA_ANG_FLOAT;
	dz = (j * sinX + k * cosX) >> ASSA_ANG_FLOAT;
	k = dz;


	dx = (k * sinY + i * cosY) >> ASSA_ANG_FLOAT;
	dz = (k * cosY - i * sinY) >> ASSA_ANG_FLOAT;

	pEffect->Posi.x += dx;
	pEffect->Posi.y += dy;
	pEffect->Posi.z += dz;

	return TRUE;
}


int AssaGetCirclePosi(cASSAEFFECT *pEffect, int DistanceZ, int Angle)
{

	POINT3D Posi = { 0,0,0 };
	pEffect->RAngle = Angle;
	pEffect->RDistance.z = DistanceZ;

	Posi.x = GetCos[Angle&ANGCLIP] + DistanceZ*GetSin[Angle&ANGCLIP];
	Posi.z = -GetSin[Angle&ANGCLIP] + DistanceZ*GetCos[Angle&ANGCLIP];

	Posi.x >>= 16;
	Posi.z >>= 16;

	pEffect->Posi.x += Posi.x;
	pEffect->Posi.z += Posi.z;
	pEffect->Posi.y += Posi.y;
	return TRUE;
}


int AssaCheckStageCrash(cASSAEFFECT *pEffect)
{

	int pY;
	int sy;

	if(smGameStage[0])
		pY = smGameStage[0]->GetHeight(pEffect->Posi.x, pEffect->Posi.z);

	if(smGameStage[1])
	{
		sy = smGameStage[1]->GetHeight(pEffect->Posi.x, pEffect->Posi.z);
		if(pY < sy) pY = sy;
	}

	if(pY >= pEffect->Posi.y)return TRUE;

	return FALSE;

}

int cASSAEFFECT::AssaReSetCharPointer()
{

	if(pChar)
	{
		if(pChar != lpCurPlayer && MyPointerFlag)
		{
			pChar = lpCurPlayer;

		}
		if(!pChar->Flag || sinGetLife() == 0)
		{
			Time = Max_Time;
		}

		if(CODE != SKILL_HOLY_REFLECTION && CODE != ASSA_PARTICLE_UNIONCORE)
		{
			if(pChar->OnStageField >= 0 && StageField[pChar->OnStageField]->State == FIELD_STATE_VILLAGE)
			{
				Time = Max_Time;
			}
		}
	}

	return TRUE;
}