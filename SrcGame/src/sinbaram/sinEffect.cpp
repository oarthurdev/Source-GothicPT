
#include "sinLinkHeader.h"


sinEFFECT				sinEffect[SIN_MAX_EFFECT];
sinEFFECT_ZDEPTH		sinEffect_ZDepth[SIN_MAX_EFFECT];
sinEFFECT_PROCESS		sinEffect_Process[SIN_MAX_PROCESS];
smTEXRECT sinTexRect = { 0.0f,1.0f,0.0f,1.0f };


D3DTLVERTEX tlVertex[20];

smFACE2D sinSetFace(int Mat, int x, int y, int z, int w, int h,
					int R, int G, int B, int A)
{
	smFACE2D tFace;

	tFace.MatNum = Mat;
	tFace.x = x;
	tFace.y = y;
	tFace.z = z;

	tFace.width = w;
	tFace.height = h;

	tFace.TexRect.left = sinTexRect.left;
	tFace.TexRect.top = sinTexRect.top;
	tFace.TexRect.right = sinTexRect.right;
	tFace.TexRect.bottom = sinTexRect.bottom;


	tFace.r = R;
	tFace.g = G;
	tFace.b = B;
	tFace.Transparency = A;

	return tFace;
}


int sinStartEffect(int Name, int x, int y, int z)
{

	switch(Name)
	{
		case SIN_EFFECT_RAGE_OF_SINBARAM:




		sinSetEffect(SIN_PARTICLE_ROTATE_RISE, x, y - 10000, z, 1000, 0, 1000);

		break;

	}

	return TRUE;
}


int Count2 = 0;
int sinSetEffect(int CODE, int x, int y, int z, int Size, int Color, int AngleY)
{
	int i, ResultSize;
	for(i = 0; i < SIN_MAX_EFFECT; i++)
	{
		if(sinEffect[i].State == SIN_EFFECT_DEAD)
		{
			sinEffect[i].State = SIN_EFFECT_ALIVE;
			sinEffect[i].CODE = CODE;
			sinEffect[i].Color = Color;
			switch(sinEffect[i].CODE)
			{
				case SIN_PARTICLE_SPOUT:
				ResultSize = Size + rand() % Size;
				sinEffect[i].sinFace = sinSetFace(cSin3D.MatParticleGold[0], x + SIN_RAND_1000 - 1000, y + SIN_RAND_1000, z + SIN_RAND_1000 - 1000, ResultSize, ResultSize, 255, 255, 255, 255);
				sinEffect[i].MoveGravity = SIN_RAND_100;
				sinEffect[i].LifeTime_MAX = SIN_RAND_100 + 50;
				sinEffect[i].RotateRadian = rand() % 4096;
				sinEffect[i].RotateDistance = sinEffect[i].MoveGravity + 10;


				break;
				case SIN_PARTICLE_GATHER:

				break;
				case SIN_PARTICLE_ROTATE_RISE:
				Count2++;
				if(Count2 < 2)break;
				Count2 = 0;

				ResultSize = Size + rand() % Size;

				sinEffect[i].MoveGravity = SIN_RAND_100;
				sinEffect[i].LifeTime_MAX = SIN_RAND_100 + 80;
				sinEffect[i].RotateRadian = rand() % 4096;
				sinEffect[i].RotateDistance = sinEffect[i].MoveGravity + 10;

				sinEffect[i].MoveAngle.x = GetCos[i * 256 & ANGCLIP] + (AngleY + 8 * 256)*GetSin[i * 256 & ANGCLIP];
				sinEffect[i].MoveAngle.z = -GetSin[i * 256 & ANGCLIP] + (AngleY + 8 * 256)*GetCos[i * 256 & ANGCLIP];

				sinEffect[i].MoveAngle.x >>= 16;
				sinEffect[i].MoveAngle.z >>= 16;


				sinEffect[i].sinFace = sinSetFace(cSin3D.MatParticleBlue[0], x + SIN_RAND_1000 - 1000 + sinEffect[i].MoveAngle.x,
												  y + SIN_RAND_1000, z + SIN_RAND_1000 - 1000 + sinEffect[i].MoveAngle.z, ResultSize, ResultSize, 255, 255, 255, 255);

				sinEffect[i].sinFace.r = rand() % 256;
				sinEffect[i].sinFace.g = rand() % 256;







				break;
				case SIN_PARTICLE_WIDE:

				break;
				case SIN_EFFECT_WIDE_LINE:
				sinEffect[i].ObjectMat = cSin3D.MatEffectLine;
				sinEffect[i].ObjectSize.x = 2 * 256;
				sinEffect[i].ObjectSize.z = 16 * 256;

				sinCreateEffectObject(&sinEffect[i]);
				sinEffect[i].LifeTime_MAX = 1000;

				sinEffect[i].ObjectPosi.x = x;
				sinEffect[i].ObjectPosi.y = y;
				sinEffect[i].ObjectPosi.z = z;

				sinEffect[i].MoveAngle.x = ((rand() % (4096 / 2)) - ANGLE_90)&ANGCLIP;
				sinEffect[i].MoveAngle.z = 0;
				sinEffect[i].MoveAngle.y = rand() % 4096;


				sinEffect[i].MoveSpeed.x = 0;
				sinEffect[i].MoveSpeed.z = 256;
				sinEffect[i].MoveSpeed.y = 0;

				break;

				case SIN_EFFECT_RISE_LINE:

				sinEffect[i].ObjectMat = cSin3D.MatEffectLine;
				sinEffect[i].ObjectSize.x = 2 * 256;
				sinEffect[i].ObjectSize.z = (Size * 16) * 256;

				sinCreateEffectObject(&sinEffect[i]);
				sinEffect[i].LifeTime_MAX = 1000;

				sinEffect[i].ObjectPosi.x = x;
				sinEffect[i].ObjectPosi.y = y;
				sinEffect[i].ObjectPosi.z = z;

				sinEffect[i].MoveAngle.x = ANGLE_270;
				sinEffect[i].MoveAngle.z = 0;
				sinEffect[i].MoveAngle.y = AngleY;




				sinEffect[i].MoveSpeed.x = 0;
				sinEffect[i].MoveSpeed.z = 256;
				sinEffect[i].MoveSpeed.y = 0;

				break;

			}
			return i + 1;

		}

	}

	return TRUE;
}


int Count5 = 0;
int sinMoveEffect(sinEFFECT *pEffect)
{
	switch(pEffect->CODE)
	{
		case SIN_PARTICLE_SPOUT:
		pEffect->MoveGravity -= 2;

		pEffect->MoveAngle.x = GetCos[pEffect->RotateRadian&ANGCLIP] + pEffect->RotateDistance*GetSin[pEffect->RotateRadian&ANGCLIP];
		pEffect->MoveAngle.z = -GetSin[pEffect->RotateRadian&ANGCLIP] + pEffect->RotateDistance*GetCos[pEffect->RotateRadian&ANGCLIP];

		pEffect->MoveAngle.x >>= 16;
		pEffect->MoveAngle.z >>= 16;

		pEffect->sinFace.x += pEffect->MoveAngle.x;
		pEffect->sinFace.z += pEffect->MoveAngle.z;
		pEffect->sinFace.y += pEffect->MoveGravity;


		break;
		case SIN_PARTICLE_GATHER:

		break;
		case SIN_PARTICLE_ROTATE_RISE:
		Count5++;
		if(Count5 > 100)Count5 = 0;

		pEffect->MoveGravity += 2;

		pEffect->MoveAngle.x = GetCos[pEffect->RotateRadian * 256 * Count5&ANGCLIP] + (pEffect->RotateDistance / 2)*GetSin[pEffect->RotateRadian * 256 * Count5&ANGCLIP];
		pEffect->MoveAngle.z = -GetSin[pEffect->RotateRadian * 256 * Count5&ANGCLIP] + (pEffect->RotateDistance / 2)*GetCos[pEffect->RotateRadian * 256 * Count5&ANGCLIP];

		pEffect->MoveAngle.x >>= 16;
		pEffect->MoveAngle.z >>= 16;

		pEffect->sinFace.x += pEffect->MoveAngle.x;
		pEffect->sinFace.z += pEffect->MoveAngle.z;
		pEffect->sinFace.y += pEffect->MoveGravity;


		break;
		case SIN_PARTICLE_WIDE:


		break;

		case SIN_EFFECT_WIDE_LINE:

		sinGetMoveLocation(pEffect);


		break;

	}
	return TRUE;
}


int sinEffectAni(sinEFFECT *pEffect)
{

	if((pEffect->CODE & sinEFFECT_MASK2) == SIN_EFFECT_PARTICLE)
	{
		if((pEffect->LifeTime % 7) == 0)
		{
			pEffect->AniCount++;
			if(pEffect->AniCount > 3)pEffect->AniCount = 0;
			switch(pEffect->Color)
			{
				case SIN_PARTICLE_COLOR_GOLD:
				pEffect->sinFace.MatNum = cSin3D.MatParticleGold[pEffect->AniCount];

				break;
				case SIN_PARTICLE_COLOR_BLUE:
				pEffect->sinFace.MatNum = cSin3D.MatParticleBlue[pEffect->AniCount];

				break;
				case SIN_PARTICLE_COLOR_RED:
				pEffect->sinFace.MatNum = cSin3D.MatParticleRed[pEffect->AniCount];

				break;
				case SIN_PARTICLE_COLOR_GREEN:
				pEffect->sinFace.MatNum = cSin3D.MatParticleGreen[pEffect->AniCount];

				break;

			}
		}
	}

	return TRUE;
}

int sinActiveEffect()
{
	int i;
	for(i = 0; i < SIN_MAX_EFFECT; i++)
	{
		if(sinEffect[i].State == SIN_EFFECT_ALIVE)
		{
			sinEffect[i].LifeTime++;
			if((sinEffect[i].LifeTime_MAX - sinEffect[i].LifeTime) < 120)
				sinEffect[i].TypeFade = SIN_EFFECT_TYPE_FADEOUT;

			if(sinEffect[i].LifeTime >= sinEffect[i].LifeTime_MAX)
			{
				memset(&sinEffect[i], 0, sizeof(sinEFFECT));
				continue;
			}

			switch(sinEffect[i].TypeSize)
			{
				case SIN_EFFECT_TYPE_EXPAND:
				sinEffect[i].sinFace.width += sinEffect[i].ChangeSize;
				sinEffect[i].sinFace.height += sinEffect[i].ChangeSize;
				break;
				case SIN_EFFECT_TYPE_DECREASE:
				sinEffect[i].sinFace.width -= sinEffect[i].ChangeSize;
				sinEffect[i].sinFace.height -= sinEffect[i].ChangeSize;
				break;
			}

			switch(sinEffect[i].TypeFade)
			{
				case SIN_EFFECT_TYPE_FADEON:
				sinEffect[i].sinFace.Transparency += 2;

				break;
				case SIN_EFFECT_TYPE_FADEOUT:
				sinEffect[i].sinFace.Transparency -= 2;

				break;

			}

			sinEffectAni(&sinEffect[i]);

			sinMoveEffect(&sinEffect[i]);

		}

	}
	sinEffectProcess();
	return TRUE;
}


int sinBubbleSort(sinEFFECT_ZDEPTH *list, int num)
{
	sinEFFECT_ZDEPTH temp;
	int i, j;

	for(i = num; i > 0; i--)
	{
		for(j = 0; j < i; j++)
		{
			if(list[j].ZDepth < list[j + 1].ZDepth)
			{
				temp = list[j + 1];
				list[j + 1] = list[j];
				list[j] = temp;
			}
		}
	}
	return TRUE;
}


int Count;
int sinDrawEffect(int x, int y, int z, int ax, int ay, int az)
{


	sinPosi2.x = x;
	sinPosi2.y = y;
	sinPosi2.z = z;

	sinAngle2.x = ax;
	sinAngle2.y = ay;
	sinAngle2.z = az;


	int i, j;
	Count = 0;
	POINT3D tPosi, tAngle;

	tPosi.x = x;
	tPosi.y = y;
	tPosi.z = z;
	tAngle.x = ax;
	tAngle.y = ay;
	tAngle.z = az;

	for(i = 0; i < SIN_MAX_EFFECT; i++)
	{
		if(sinEffect[i].State == SIN_EFFECT_ALIVE)
		{
			smRender.SetCameraPosi(x, y, z, ax, ay, az);
			for(j = 0; j < SIN_MAX_EFFECT; j++)
			{
				if(!sinEffect_ZDepth[j].Index)
				{
					if(sinEffect[i].MeshFlag)
						sinEffect_ZDepth[j].ZDepth = smRender.GetDepthZ(sinEffect[i].ObjectPosi.x, sinEffect[i].ObjectPosi.y, sinEffect[i].ObjectPosi.z);

					else
						sinEffect_ZDepth[j].ZDepth = smRender.GetDepthZ(sinEffect[i].sinFace.x, sinEffect[i].sinFace.y, sinEffect[i].sinFace.z);
					sinEffect_ZDepth[j].Index = i + 1;
					Count++;
					break;
				}
			}
		}
	}

	sinBubbleSort(sinEffect_ZDepth, Count - 1);

	for(i = 0; i < Count; i++)
	{
		if(sinEffect_ZDepth[i].Index && sinEffect[sinEffect_ZDepth[i].Index - 1].State == SIN_EFFECT_ALIVE)
		{
			if(sinEffect[i].MeshFlag)
			{
				

				POINT3D angle;
				memcpy(&angle, &sinEffect[sinEffect_ZDepth[i].Index - 1].MoveAngle, sizeof(POINT3D));

				angle.y = (-angle.y + ANGLE_180)&ANGCLIP;

				sinEffect[i].sinPatMesh->SetPosi(&sinEffect[sinEffect_ZDepth[i].Index - 1].ObjectPosi, &angle);



				sinEffect[i].sinPatMesh->TmLastFrame = -1;
				sinEffect[i].sinPatMesh->SetFrame(0);

				smMATRIX	Mat;
				smIdentityMatrix(Mat);

				Mat._22 *= 4;

				smMatrixMult(sinEffect[i].sinPatMesh->obj3d[0]->mWorld, Mat, sinEffect[i].sinPatMesh->obj3d[0]->mWorld);

				sinEffect[i].sinPatMesh->Frame = -1;



				sinEffect[i].sinPatMesh->RenderD3D(&tPosi, &tAngle);
				
			}
			else
				cSin3D.sinDrawTexture(x, y, z, ax, ay, az, &sinEffect[sinEffect_ZDepth[i].Index - 1].sinFace, sinEffect[sinEffect_ZDepth[i].Index - 1].FaceAngle);
			sinEffect_ZDepth[i].Index = 0;

		}

	}

	return TRUE;
}



int sinEffectProcess()
{
	int i, j;
	int px, pz, py = 0;
	for(i = 0; i < SIN_MAX_PROCESS; i++)
	{
		if(sinEffect_Process[i].Kind)
		{
			sinEffect_Process[i].Time++;
			switch(sinEffect_Process[i].Kind)
			{
				case SIN_EFFECT_RAGE_OF_SINBARAM:
				if(sinEffect_Process[i].Time == 1)
				{
					for(j = 0; j < 40; j++)
					{
						px = GetCos[j * 128 & ANGCLIP] + 256 * 16 * GetSin[j * 128 & ANGCLIP];
						pz = -GetSin[j * 128 & ANGCLIP] + 256 * 16 * GetCos[j * 128 & ANGCLIP];

						px >>= 16;
						pz >>= 16;

						sinEffect_Process[i].Index[j] = sinSetEffect(SIN_EFFECT_RISE_LINE, sinEffect_Process[i].Posi.x + px, sinEffect_Process[i].Posi.y,
																	 sinEffect_Process[i].Posi.z + pz, 2, 0, j * 128 & ANGCLIP);
					}

				}
				if(sinEffect_Process[i].Time > 150)
				{
					for(j = 0; j < 40; j++)
					{
						memset(&sinEffect[sinEffect_Process[i].Index[j] - 1], 0, sizeof(sinEFFECT));





					}
				}


				if(sinEffect_Process[i].Time >= 300)sinEffect_Process[i].Kind = 0;

				break;


			}

		}

	}
	return TRUE;
}

int sinSetEffectProcess(int Kind, int x, int y, int z)
{
	int i;
	for(i = 0; i < SIN_MAX_PROCESS; i++)
	{
		if(!sinEffect_Process[i].Kind)
		{
			sinEffect_Process[i].Kind = Kind;
			sinEffect_Process[i].Time = 0;
			sinEffect_Process[i].Posi.x = x;
			sinEffect_Process[i].Posi.y = y;
			sinEffect_Process[i].Posi.z = z;
			memset(sinEffect_Process[i].Index, 0, sizeof(int) * 100);
			break;

		}

	}
	return TRUE;
}

int sinCreateEffectObject(sinEFFECT *pEffect)
{
	smTPOINT tPoint[4];

	smMaterial[pEffect->ObjectMat].SelfIllum = 1;

	tPoint[0].u = 0;
	tPoint[0].v = 0;
	tPoint[1].u = 256;
	tPoint[1].v = 0;
	tPoint[2].u = 0;
	tPoint[2].v = 256;
	tPoint[3].u = 256;
	tPoint[3].v = 256;

	pEffect->sinObj = new smOBJ3D(4, 2);

	pEffect->sinObj->AddVertex(-pEffect->ObjectSize.x, -pEffect->ObjectSize.z, 0);
	pEffect->sinObj->AddVertex(pEffect->ObjectSize.x, -pEffect->ObjectSize.z, 0);
	pEffect->sinObj->AddVertex(-pEffect->ObjectSize.x, pEffect->ObjectSize.z, 0);
	pEffect->sinObj->AddVertex(pEffect->ObjectSize.x, pEffect->ObjectSize.z, 0);

	pEffect->sinObj->AddFace(0, 1, 2, &tPoint[0], &tPoint[1], &tPoint[2]);
	pEffect->sinObj->AddFace(2, 1, 3, &tPoint[2], &tPoint[1], &tPoint[3]);
	pEffect->sinObj->ZeroNormals();

	pEffect->sinObj->SetFaceMaterial(0, pEffect->ObjectMat);
	pEffect->sinObj->SetFaceMaterial(1, pEffect->ObjectMat);


	smMaterial[pEffect->ObjectMat].TwoSide = TRUE;

	pEffect->sinPatMesh = new smPAT3D;
	pEffect->sinPatMesh->AddObject(pEffect->sinObj);
	pEffect->MeshFlag = 1;

	return TRUE;
}



#define SHHH_ANGF_SFLOAT	(5+FLOATNS) 

int sinGetMoveLocation(sinEFFECT *pEffect)
{

	int i, j, k;
	int dx, dy, dz;

	int sinX, sinY, sinZ;
	int cosX, cosY, cosZ;

	pEffect->MoveAngle.x &= ANGCLIP;
	pEffect->MoveAngle.y &= ANGCLIP;
	pEffect->MoveAngle.z &= ANGCLIP;

	sinX = sdGetSin[pEffect->MoveAngle.x] >> 2;
	sinY = sdGetSin[pEffect->MoveAngle.y] >> 2;
	sinZ = sdGetSin[pEffect->MoveAngle.z] >> 2;
	cosX = sdGetCos[pEffect->MoveAngle.x] >> 2;
	cosY = sdGetCos[pEffect->MoveAngle.y] >> 2;
	cosZ = sdGetCos[pEffect->MoveAngle.z] >> 2;


	i = (pEffect->MoveSpeed.x * cosZ - pEffect->MoveSpeed.y * sinZ) >> SHHH_ANGF_SFLOAT;
	j = (pEffect->MoveSpeed.x * sinZ + pEffect->MoveSpeed.y * cosZ) >> SHHH_ANGF_SFLOAT;
	k = pEffect->MoveSpeed.z;


	dy = (j * cosX - k * sinX) >> SHHH_ANGF_SFLOAT;
	dz = (j * sinX + k * cosX) >> SHHH_ANGF_SFLOAT;
	k = dz;


	dx = (k * sinY + i * cosY) >> SHHH_ANGF_SFLOAT;
	dz = (k * cosY - i * sinY) >> SHHH_ANGF_SFLOAT;

	pEffect->ObjectPosi.x += dx;
	pEffect->ObjectPosi.y += dy;
	pEffect->ObjectPosi.z += dz;

	return TRUE;
}



int EffectTestDrawText()
{
	HDC	hdc = NULL;

	char strBuff[128];
	memset(strBuff, 0, sizeof(strBuff));
	
	//SelectObject(hdc, sinFont);
	
	SetFontTextColor( RGB(255, 255, 255));




	
	return TRUE;

}
