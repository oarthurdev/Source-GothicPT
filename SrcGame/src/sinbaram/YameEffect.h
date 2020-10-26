
#ifndef _YAMEEFFECT_HEADER_

#define _YAMEEFFECT_HEADER_

#define YAMEEFFECT_MAX		5000


#define YAME_DEFAULT_FADE	0x00000000
#define YAME_SMOOTH_FADE	0x00000001
#define YAME_NOT_FADEIN		0x00000010
#define YAME_NOT_FADEOUT	0x00000100



#define YAMEFACE_BILLBOARD	0
#define YAMEFACE_WORLD		1
#define YAMEFACE_SCALE		2
#define YAMEFACE_TRACE		3



struct sYAME_ANI
{
	int		Cnt;
	int		DelayTime;
	int		MaxCnt;
	int		MatIndex[10];
	int		Reverse;

};


struct sYAME_FADE
{
	DWORD   FADE_CODE;
	int     MaxAlpha;
	int     NowAlpha;
	float   AlphaAmount;
	int		AlphaStartTime;

};


struct sYAME_ROTATE
{
	int		RAngle;
	int		RAngleSpeed;
	POINT3D RPosi;
	POINT3D CenterPosi;
};


struct sYAME_ANGLE_ROTATE
{
	POINT3D	ARotate;
	POINT3D	ARotateSpeed;
	int     FACEY;

};


struct sYAME_COLOR
{
	int r;
	int g;
	int b;
	int a;

};


struct sYAME_SCALE
{
	POINT3D ScalePosi;
	POINT3D ScaleSpeed;
	int     CenterFlag;

};

struct sYAME_BILLBOARD
{
	int FaceY;
	int ZposiFlag;

};




class cYAMEEFFECT;


class  cYAMEEFFECT
{
public:

	DWORD   CODE;
	DWORD	MOVECODE;
	int		Time;
	int		Max_Time;
	int		Bone;


	smFACE2D	Face;
	smPAT3D		*PatMesh;

	int		Index;
	int		ZDepth;


	POINT3D	Posi;
	POINT3D	DesPosi;
	POINT3D	Angle;

	int		AddHeight;


	POINT3D	MoveSpeed;


	smCHAR	*pChar;
	smCHAR	*desChar;


	int FACE_TYPE;
	int FACE_POSI;

	int w;
	int h;


	sYAME_ANI	Ani;


	sYAME_FADE  Fade;


	sYAME_ROTATE Rotate;


	sYAME_ANGLE_ROTATE Angle_Rotate;


	sYAME_COLOR	Color;


	sYAME_SCALE	Scale;


	sYAME_BILLBOARD BillBoard;


	cASSATrace *cAssaTrace;



public:
	cYAMEEFFECT()
	{
		memset(this, 0, sizeof(cASSAEFFECT));
		cASSATrace *pAssaTrace = new cASSATrace;
		cAssaTrace = pAssaTrace;

	}
	virtual ~cYAMEEFFECT()
	{
		if(cAssaTrace)delete cAssaTrace;
	}
	virtual	void Main()
	{
	}
	virtual void Draw(POINT3D *pPosi, POINT3D *pAngle)
	{
	}




};


class cYAMEFACE : public cYAMEEFFECT
{
public:

	void Main()
	{
		Face.x = Posi.x;
		Face.y = Posi.y;
		Face.z = Posi.z;
		Face.width = w;
		Face.height = h;
		if(!Face.height)
		{
			h = w;
			Face.height = Face.width;
		}
		if(!Fade.MaxAlpha)Fade.MaxAlpha = 255;

		switch(Fade.FADE_CODE)
		{
			case YAME_DEFAULT_FADE:


			break;
			case YAME_SMOOTH_FADE:

			break;
			case YAME_NOT_FADEIN:

			break;
			case YAME_NOT_FADEOUT:

			break;
		}




	}
	void Draw(POINT3D *pPosi, POINT3D *pAngle)
	{

		if(!Face.MatNum)
			return;

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
			case YAMEFACE_BILLBOARD:

			if(!AssaAddFace2D(&Face, BillBoard.ZposiFlag, BillBoard.FaceY))return;
			break;
			case YAMEFACE_WORLD:

			break;
			case YAMEFACE_SCALE:

			break;
			case YAMEFACE_TRACE:

			break;
		}

		smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
		smRender.ClipRendFace();
		smRender.GeomVertex2D(FALSE);
		smRender.RenderD3D();
	}
};


class cYAMEMESH : public cYAMEEFFECT
{
public:

};


void InitYameEffect();

void DrawYameEffect(POINT3D *pPosi, POINT3D *pAngle);

void MainYameEffect();

void MoveYameEffect(cASSAEFFECT *pEffect);

void CloseYameEffect();

void StopYameEffect(cASSAEFFECT *pEffect);

void YameEffectKeyDown();



int  SetYameEffect(int MaxTime, char *FileName, smCHAR *pChar, POINT3D *pPosi, int AddHeight = 0, int BlendType = 0);

extern int Yame;
extern cYAMEEFFECT *cYameEffect[YAMEEFFECT_MAX];
#endif
