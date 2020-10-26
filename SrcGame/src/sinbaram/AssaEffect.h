#ifndef _ASSAEFFECT_HEADER_
#define _ASSAEFFECT_HEADER_

#include <Windows.h>
#include "smLib3d\smType.h"


class cASSATrace;

#define cASSAEFFECT_MAX		5000


#define ASSA_ROTATE				0x0000000F 
#define ASSA_MOVE				0x000000F0 
#define ASSA_ANGLE_ROTATE		0x00000F00 
#define ASSA_CHAR_POSI			0x0000F000 
#define ASSA_MOVE_ANGLE_SPEED	0x000F0000 
#define ASSA_DECRESIZE			0x00F00000 
#define ASSA_INCRESIZE			0x0F000000 
#define ASSA_MOVE_GATHER		0xF0000000 


#define ASSA_MOVE_SPREAD		0x70000000 
#define ASSA_MOVE_RANDOM_ROTATE 0x70000001 

#define ASSA_ANG_CHAR			0x00000001 
#define ASSA_ANG_DESCHAR		0x00000002 
#define ASSA_ANG_BONE			0x00000003 


#define ASSAFADEOUT			0		
#define ASSAFADEIN			1


#define ASSAFACE_BILLBOARD	0
#define ASSAFACE_WORLD		1
#define ASSAFACE_SCALE		2
#define ASSAFACE_TRACE		3



#define ASSATYPE_CIRCLE		1



struct sASSACOLOR
{
	int R; int G; int B; int A;
};
struct sASSASIZE
{
	int SameSize; int w; int h;
};


class  cASSAEFFECT
{
public:
	DWORD	MOVECODE;
	DWORD	MOVECODESUB;
	DWORD   CODE;
	int		Time;
	int		Max_Time;
	int		Bone;
	char    szFileName[128];
	int		Power;


	smFACE2D	Face;
	smPAT3D		*PatMesh;
	int			Mat;
	smOBJ3D     *Obj;

	int		Index;
	int		ZDepth;


	cASSATrace *cAssaTrace;


	POINT3D	Posi;
	POINT3D	Angle;
	POINT3D	TempPosi;
	POINT3D	TempAngle;
	POINT3D StartPosi;
	int		AddHeight;
	POINT3D	DesPosi;


	int		AniCount;
	int		AniDelayTime;
	int		AniMaxCount;
	int		AniMatIndex[10];
	int		AniReverse;


	POINT3D	MoveSpeed;
	POINT3D	MovePosi;
	int     GatherSpeed;
	int		Gravity;


	POINT3D	RDistance;
	int		RAngle;
	int		RAngleSpeed;
	POINT3D RPosi;
	POINT3D CenterPosi;


	POINT3D	ARotate;
	POINT3D	ARotateSpeed;
	int     FACEY;


	smCHAR	*pChar;
	smCHAR	*desChar;


	int		NotFadeIn;
	int		NotFadeOut;
	int     MaxAlphaAmount;
	float   AlphaAmount;
	int		AlphaStartTime;

	sASSACOLOR Color;
	sASSACOLOR BackUpColor;


	int FACE_TYPE;


	POINT3D ScalePosi;
	POINT3D ScaleSpeed;

	int CenterFlag;


	int		CrashFlag;


	sASSASIZE Size;
	sASSASIZE ReSize;

	int     Type;


	int		ActionIndex[10];
	int		ActionTime[10];


	DWORD   MOVECODE_List[10];
	int     MOVECODE_Time[10];


	int     ZposiFlag;

	int		Temp[10];
	float	fTemp[10];



	int     MyPointerFlag;

public:
	cASSAEFFECT()
	{
		memset(this, 0, sizeof(cASSAEFFECT));
		cASSATrace *pAssaTrace = new cASSATrace;
		cAssaTrace = pAssaTrace;

	}
	virtual ~cASSAEFFECT()
	{
		if(cAssaTrace)delete cAssaTrace;
	}
	virtual	void Main()
	{
	}
	virtual void Draw(POINT3D *pPosi, POINT3D *pAngle)
	{
	}


	int AssaReSetCharPointer();

};


class cASSAFACE : public cASSAEFFECT
{
public:

	void Main()
	{

		Face.x = this->Posi.x;
		Face.y = this->Posi.y;
		Face.z = this->Posi.z;
		Face.width = this->Size.w;
		Face.height = this->Size.h;
		if(!Face.height)
		{
			this->Size.h = this->Size.w;
			Face.height = Face.width;
		}


		if(!MaxAlphaAmount)
		{
			if(!NotFadeIn)
			{
				if(Time == 1)Face.Transparency = 0;
				AlphaStartTime = (int)((float)Max_Time / 100.0f*25.5f);
				AlphaAmount = 255.0f / (float)AlphaStartTime;
				if(Time <= AlphaStartTime)
				{
					Face.Transparency += (int)AlphaAmount;
					if(Face.Transparency > 255)
						Face.Transparency = 255;
				}
			}
		}
		else
		{
			if(!NotFadeIn)
			{
				if(Time == 1)Face.Transparency = 0;
				AlphaStartTime = (int)((float)Max_Time / 100.0f*25.5f);
				AlphaAmount = (float)MaxAlphaAmount / (float)AlphaStartTime;
				if(Time <= AlphaStartTime)
				{
					if(AlphaAmount < 0) AlphaAmount = 1;
					Face.Transparency += (int)AlphaAmount;
					if(Face.Transparency > MaxAlphaAmount)
						Face.Transparency = MaxAlphaAmount;
				}
			}
			else
			{
				if(Time == 1)
					Face.Transparency = MaxAlphaAmount;
			}
		}


		if(!NotFadeOut)
		{
			if(!MaxAlphaAmount)
			{
				AlphaStartTime = (int)((float)Max_Time / 100.0f*25.5f);
				if((255.0f / (float)AlphaStartTime) >= 1)
				{
					AlphaAmount = 255.0f / (float)AlphaStartTime;

				}
				if(Time > AlphaStartTime && AlphaAmount >= 1)
					Face.Transparency -= (int)AlphaAmount;
			}
			else
			{
				AlphaStartTime = (int)((float)Max_Time / 100.0f*25.5f);
				if(((float)MaxAlphaAmount / (float)AlphaStartTime) >= 1)
				{
					AlphaAmount = (float)MaxAlphaAmount / (float)AlphaStartTime;

				}
				if(Time > AlphaStartTime && AlphaAmount >= 1)
					Face.Transparency -= (int)AlphaAmount;

			}
		}

		if(AniReverse == 2)
		{
			if(AniDelayTime && (Time % AniDelayTime) == 0)
			{
				AniCount--;
				if(AniCount < 1)
				{
					if(AniReverse == 2)AniReverse = 1;

				}
				Face.MatNum = AniMatIndex[AniCount];
			}

		}
		else
		{
			if(Time > 0 && AniDelayTime && (Time % AniDelayTime) == 0)
			{
				Face.MatNum = AniMatIndex[AniCount];
				AniCount++;
				if(AniCount > AniMaxCount - 1)
				{
					if(AniReverse == 1)AniReverse = 2;
					else AniCount = 0;
				}
			}
		}

		AssaReSetCharPointer();

	}
	void Draw(POINT3D *pPosi, POINT3D *pAngle)
	{

		if(!Face.MatNum)return;

		d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

		smRender.Init();

		smMaterialGroup->smMaterial[Face.MatNum].TwoSide = TRUE;

		smRender.SetMaterialGroup(smMaterialGroup);



		smMaterialGroup->SetMaterialAnimFrame(&smMaterial[Face.MatNum], 2);


		smRender.SetCameraPosi(pPosi->x, pPosi->y, pPosi->z, pAngle->x, pAngle->y, pAngle->z);

		switch(FACE_TYPE)
		{
			case ASSAFACE_BILLBOARD:
			if(!AssaAddFace2D(&Face, ZposiFlag, FACEY))return;
			break;
			case ASSAFACE_WORLD:
			if(!AssaAddFaceWorld(&Face, &Angle))return;
			break;
			case ASSAFACE_SCALE:
			if(!AssaAddFace2DLine(&Face, &ScalePosi, CenterFlag))return;
			break;
			case ASSAFACE_TRACE:
			if(!AssaAddFaceTrace(&Face, cAssaTrace))return;
			break;
		}

		smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
		smRender.ClipRendFace();
		smRender.GeomVertex2D(FALSE);
		smRender.RenderD3D();
	}
};


class cASSAMESH : public cASSAEFFECT
{
public:

	void Main()
	{


		if(!Max_Time)
		{
			Max_Time = AniMaxCount*AniDelayTime;
		}
		if(!AniCount)AniCount = 1;
		if(!AniDelayTime)AniDelayTime = 1;


		if(Time > 0 && AniDelayTime && (Time % AniDelayTime) == 0)
		{
			AniCount++;
			if(AniCount >= AniMaxCount)
				AniCount = 0;
		}



		if(!NotFadeIn)
		{
			if(!MaxAlphaAmount)
			{
				if(Time == 1)
				{
					Color.A = -255; Color.R = -255; Color.G = -255; Color.B = -255;
				}
				AlphaStartTime = (int)((float)Max_Time / 100.0f*25.5f);
				if(AlphaStartTime > 255)AlphaStartTime = 255;
				AlphaAmount = 255.0f / (float)AlphaStartTime;
				if(Time <= AlphaStartTime)
				{
					Color.A += (int)AlphaAmount; Color.R += (int)AlphaAmount; Color.G += (int)AlphaAmount; Color.B += (int)AlphaAmount;
					if(Color.A > 0)Color.A = 0;
					if(Color.R > 0)Color.R = 0;
					if(Color.G > 0)Color.G = 0;
					if(Color.B > 0)Color.B = 0;
				}
			}
			else
			{
				if(Time == 1)
				{
					Color.A = -255; Color.R = -255; Color.G = -255; Color.B = -255;
				}
				AlphaStartTime = (int)((float)Max_Time / 100.0f*25.5f);
				if(AlphaStartTime > MaxAlphaAmount)MaxAlphaAmount = 255;
				AlphaAmount = (float)MaxAlphaAmount / (float)AlphaStartTime;
				if(Time <= AlphaStartTime)
				{
					Color.A += (int)AlphaAmount; Color.R += (int)AlphaAmount; Color.G += (int)AlphaAmount; Color.B += (int)AlphaAmount;
					if(Color.A > 0)Color.A = 0;
					if(Color.R > 0)Color.R = 0;
					if(Color.G > 0)Color.G = 0;
					if(Color.B > 0)Color.B = 0;
				}
			}
		}

		if(!NotFadeOut)
		{
			if(!MaxAlphaAmount)
			{
				AlphaStartTime = (int)((float)Max_Time / 100.0f*25.5f);
				if(AlphaStartTime > 255)AlphaStartTime = 255;
				AlphaAmount = 255.0f / (float)AlphaStartTime;
				if(Time >= (Max_Time - AlphaStartTime))
				{
					Color.A -= (int)AlphaAmount;
					Color.R -= (int)AlphaAmount;
					Color.G -= (int)AlphaAmount;
					Color.B -= (int)AlphaAmount;
				}
			}
			else
			{
				AlphaStartTime = (int)((float)Max_Time / 100.0f*25.5f);
				if(AlphaStartTime > MaxAlphaAmount)AlphaStartTime = MaxAlphaAmount;
				AlphaAmount = (float)MaxAlphaAmount / (float)AlphaStartTime;
				if(Time >= (Max_Time - AlphaStartTime))
				{
					Color.A -= (int)AlphaAmount;
					Color.R -= (int)AlphaAmount;
					Color.G -= (int)AlphaAmount;
					Color.B -= (int)AlphaAmount;
				}
			}
		}

		AssaReSetCharPointer();

	}
	void Draw(POINT3D *pPosi, POINT3D *pAngle)
	{

		BackUpColor.R = smRender.Color_R;
		BackUpColor.G = smRender.Color_G;
		BackUpColor.B = smRender.Color_B;
		BackUpColor.A = smRender.Color_A;

		smRender.Color_R = Color.R;
		smRender.Color_G = Color.G;
		smRender.Color_B = Color.B;
		smRender.Color_A = Color.A;
		if(PatMesh)
		{
			PatMesh->Frame = AniCount * 160;
			PatMesh->SetPosi(&Posi, &Angle);
			PatMesh->RenderD3D(pPosi, pAngle);
		}
		smRender.Color_R = BackUpColor.R;
		smRender.Color_G = BackUpColor.G;
		smRender.Color_B = BackUpColor.B;
		smRender.Color_A = BackUpColor.A;

	}

};


void InitAssaEffect();

void DrawAssaEffect(POINT3D *pPosi, POINT3D *pAngle);

void MainAssaEffect();

void MoveAssaEffect(cASSAEFFECT *pEffect);

void CloseAssaEffect();

void StopAssaEffect(cASSAEFFECT *pEffect);

void AssaEffectKeyDown();



int  SetAssaEffect(int MaxTime, char *FileName, smCHAR *pChar, POINT3D *pPosi, int AddHeight = 0, int BlendType = 0);


int AssaGetMoveLocation(cASSAEFFECT *pEffect);


int AssaSetAngle(cASSAEFFECT *pEffect, int AngleKind);


int AssaSetStartPosi(cASSAEFFECT *pEffect);


int AssaGetMoveLocation(cASSAEFFECT *pEffect);


int AssaGetCirclePosi(cASSAEFFECT *pEffect, int DistanceZ, int Angle);


int AssaCheckStageCrash(cASSAEFFECT *pEffect);


int AssaGetAniFileMat(cASSAEFFECT *pEffect);


int AssaCopyEffect(cASSAEFFECT *pEffect);


int AssaReSetCharPointer(cASSAEFFECT *pEffect);

extern int Assa;
extern cASSAEFFECT *cAssaEffect[cASSAEFFECT_MAX];
#endif
