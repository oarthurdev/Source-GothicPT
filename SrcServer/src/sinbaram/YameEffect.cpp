

#include "sinLinkHeader.h"



cYAMEEFFECT *cYameEffect[YAMEEFFECT_MAX];
sinEFFECT_ZDEPTH sinEffect_Zdepth4[YAMEEFFECT_MAX];
int Yame;


void YameEffectKeyDown()
{

	POINT3D Posi = { lpCurPlayer->pX,lpCurPlayer->pY + 10000,lpCurPlayer->pZ };

	if(sinGetKeyClick('9'))
	{



	}





}

void InitYameEffect()
{







	memset(cYameEffect, 0, sizeof(cYAMEEFFECT));

}

void DrawYameEffect(POINT3D *pPosi, POINT3D *pAngle)
{

	int i = 0;
	int IndexCount = 0;


	for(i = 0; i < YAMEEFFECT_MAX; i++)
	{
		if(cYameEffect[i] && !cYameEffect[i]->Bone && cYameEffect[i]->Time > 0)
		{
			smRender.SetCameraPosi(pPosi->x, pPosi->y, pPosi->z, pAngle->x, pAngle->y, pAngle->z);
			for(int j = 0; j < YAMEEFFECT_MAX; j++)
			{
				if(!sinEffect_Zdepth4[j].Index)
				{
					sinEffect_Zdepth4[j].ZDepth = smRender.GetDepthZ(cYameEffect[i]->Posi.x, cYameEffect[i]->Posi.y, cYameEffect[i]->Posi.z);
					sinEffect_Zdepth4[j].Index = i + 1;
					IndexCount++;
					break;
				}
			}
		}
	}

	sinBubbleSort(sinEffect_Zdepth4, IndexCount - 1);
	for(i = 0; i < IndexCount; i++)
	{
		if(sinEffect_Zdepth4[i].Index)
		{
			renderDevice.BeginScene();
			if(cYameEffect[sinEffect_Zdepth4[i].Index - 1]->pChar)
			{
				if(cYameEffect[sinEffect_Zdepth4[i].Index - 1]->pChar->FlagShow != 0)
				{
					cYameEffect[sinEffect_Zdepth4[i].Index - 1]->Draw(pPosi, pAngle);
				}
			}
			else
				cYameEffect[sinEffect_Zdepth4[i].Index - 1]->Draw(pPosi, pAngle);
			renderDevice.EndScene();
		}
	}
	memset(sinEffect_Zdepth4, 0, sizeof(sinEFFECT_ZDEPTH)*YAMEEFFECT_MAX);
}

void MainYameEffect()
{

	for(int i = 0; i < YAMEEFFECT_MAX; i++)
	{
		if(cYameEffect[i])
		{
			cYameEffect[i]->Time++;
			cYameEffect[i]->Main();

			if(cYameEffect[i]->Time > 0)


				if(cYameEffect[i]->Time >= cYameEffect[i]->Max_Time)
				{
					delete cYameEffect[i];
					cYameEffect[i] = NULL;

				}
		}
	}
}

void CloseYameEffect()
{


}

void MoveYameEffect(cASSAEFFECT *pEffect)
{

}

void StopYameEffect(cASSAEFFECT *pEffect)
{


}



int  SetYameEffect(int MaxTime, char *FileName, smCHAR *pChar, POINT3D *pPosi, int AddHeight, int BlendTpye)
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

	for(int i = 0; i < YAMEEFFECT_MAX; i++)
	{
		if(!cYameEffect[i])
		{

			if(stricmp(FileName, "Bone") == 0)
			{
				cYAMEFACE *pFace = new cYAMEFACE;
				cYameEffect[i] = pFace;
				cYameEffect[i]->Bone = 1;


			}
			if(stricmp(FileFormat, "bmp") == 0 || stricmp(FileFormat, "tga") == 0)
			{
				cYAMEFACE *pFace = new cYAMEFACE;
				cYameEffect[i] = pFace;
				cYameEffect[i]->Face.r = 255;
				cYameEffect[i]->Face.g = 255;
				cYameEffect[i]->Face.b = 255;
				cYameEffect[i]->Face.Transparency = 255;
				cYameEffect[i]->Face.TexRect = sinTexRect;
				cYameEffect[i]->Face.MatNum = *(int *)AssaSearchRes(FileName, wBlendType);

			}
			if(stricmp(FileFormat, "ase") == 0)
			{
				cYAMEMESH *pMesh = new cYAMEMESH;
				cYameEffect[i] = pMesh;
				cYameEffect[i]->PatMesh = (smPAT3D *)AssaSearchRes(FileName, wBlendType);

			}
			if(pChar)
			{
				cYameEffect[i]->Posi.x = pChar->pX;
				cYameEffect[i]->Posi.y = pChar->pY;
				cYameEffect[i]->Posi.z = pChar->pZ;
				cYameEffect[i]->pChar = pChar;


			}
			if(pPosi)
			{
				cYameEffect[i]->Posi.x = pPosi->x;
				cYameEffect[i]->Posi.y = pPosi->y;
				cYameEffect[i]->Posi.z = pPosi->z;
			}

			cYameEffect[i]->AddHeight = AddHeight;
			cYameEffect[i]->Posi.y += AddHeight;
			cYameEffect[i]->Max_Time = MaxTime;

			if(pChar)
			{
				cYameEffect[i]->Angle.y = (-(pChar->Angle.y&ANGCLIP) + ANGLE_180)&ANGCLIP;
			}
			return i;
		}
	}
	return FALSE;

}
