#include "smlib3d\\smd3d.h"
#include "pbackground.h"
#include "field.h"

extern int ViewPointLen;
extern DWORD smBackColor;

#define DISP_BG_COUNT_MIN	-500

static int BGFace[2][3] = {
	{ 0 ,  1 , 2 },
	{ 1 ,  3 , 2 }
};

smBACKGROUND::smBACKGROUND()
{
	smObjBG = 0;
	lpMaterialGroup = 0;
}


int smBACKGROUND::Init(int BgNum)
{
	int cnt;
	int cntX, cntY;
	int	stepH;
	int tCnt;
	int a, b, c;
	int face[3];
	smTPOINT *tPoint[3];
	smTPOINT tP[128];
	smTPOINT tPT[3];

	int TexCount;

	int u, v;
	int x, y, z;
	int dx, dz;
	int vCnt;
	int fNum;
	int	DsrFlag;


	smObjBG = new smOBJ3D;
	smObjBG->Init(16 * 5 + 1, 512 + 16);


	lpMaterialGroup = new smMATERIAL_GROUP(8);

	BackGroundNum = BgNum;
	DsrFlag = TRUE;



	switch(BgNum)
	{
		case FIELD_BACKIMAGE_RAIN:

		BGMatNum = lpMaterialGroup->CreateTextureMaterial("game\\sky\\RainSky.bmp", 0, FALSE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
		lpMaterialGroup->AddTexture(BGMatNum, "game\\sky\\fsky00.tga");
		lpMaterialGroup->smMaterial[BGMatNum].TextureFormState[1] = smTEXSTATE_FS_SCROLL;
		lpMaterialGroup->smMaterial[BGMatNum].MapOpacity = 0;
		TexCount = 1;
		break;

		case FIELD_BACKIMAGE_NIGHT:

		BGMatNum = lpMaterialGroup->CreateTextureMaterial("game\\sky\\nsky00.bmp", 0, FALSE, FALSE, FALSE, SMMAT_BLEND_ALPHA);

		TexCount = 0;
		break;

		case FIELD_BACKIMAGE_DAY:

		BGMatNum = lpMaterialGroup->CreateTextureMaterial("game\\sky\\fsky00.bmp", 0, FALSE, FALSE, FALSE, SMMAT_BLEND_ALPHA);

		TexCount = 0;
		break;

		case FIELD_BACKIMAGE_GLOWDAY:

		BGMatNum = lpMaterialGroup->CreateTextureMaterial("game\\sky\\fgsky00.bmp", 0, FALSE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
		lpMaterialGroup->AddTexture(BGMatNum, "game\\sky\\fgsky00.tga");
		lpMaterialGroup->smMaterial[BGMatNum].TextureFormState[1] = smTEXSTATE_FS_SCROLL;
		lpMaterialGroup->smMaterial[BGMatNum].MapOpacity = 0;
		TexCount = 1;
		break;

		case FIELD_BACKIMAGE_DESERT:

		BGMatNum = lpMaterialGroup->CreateTextureMaterial("game\\sky\\dsky00.bmp", 0, FALSE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
		lpMaterialGroup->AddTexture(BGMatNum, "game\\sky\\dsky00.tga");
		lpMaterialGroup->smMaterial[BGMatNum].TextureFormState[1] = smTEXSTATE_FS_SCROLL;
		lpMaterialGroup->smMaterial[BGMatNum].MapOpacity = 0;
		TexCount = 1;
		break;

		case FIELD_BACKIMAGE_GLOWDESERT:

		BGMatNum = lpMaterialGroup->CreateTextureMaterial("game\\sky\\dgsky00.bmp", 0, FALSE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
		lpMaterialGroup->AddTexture(BGMatNum, "game\\sky\\dgsky00.tga");
		lpMaterialGroup->smMaterial[BGMatNum].TextureFormState[1] = smTEXSTATE_FS_SCROLL;
		lpMaterialGroup->smMaterial[BGMatNum].MapOpacity = 0;
		TexCount = 1;
		break;
		case FIELD_BACKIMAGE_NIGHTDESERT:

		BGMatNum = lpMaterialGroup->CreateTextureMaterial("game\\sky\\dnsky00.bmp", 0, FALSE, FALSE, FALSE, SMMAT_BLEND_ALPHA);

		TexCount = 0;
		break;

		case FIELD_BACKIMAGE_RUIN1:
		BGMatNum = lpMaterialGroup->CreateTextureMaterial("game\\sky\\RuinSky2.bmp", 0, FALSE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
		lpMaterialGroup->AddTexture(BGMatNum, "game\\sky\\fsky00.tga");
		lpMaterialGroup->smMaterial[BGMatNum].TextureFormState[1] = smTEXSTATE_FS_SCROLL;
		lpMaterialGroup->smMaterial[BGMatNum].MapOpacity = 0;
		TexCount = 1;
		break;

		case FIELD_BACKIMAGE_RUIN2:
		BGMatNum = lpMaterialGroup->CreateTextureMaterial("game\\sky\\RuinSky.bmp", 0, FALSE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
		lpMaterialGroup->AddTexture(BGMatNum, "game\\sky\\fsky00.tga");
		lpMaterialGroup->smMaterial[BGMatNum].TextureFormState[1] = smTEXSTATE_FS_SCROLL;
		lpMaterialGroup->smMaterial[BGMatNum].MapOpacity = 0;
		TexCount = 1;
		break;

		case FIELD_BACKIMAGE_NIGHTRUIN1:
		BGMatNum = lpMaterialGroup->CreateTextureMaterial("game\\sky\\RuinSky2-n.bmp", 0, FALSE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
		lpMaterialGroup->AddTexture(BGMatNum, "game\\sky\\fsky00.tga");
		lpMaterialGroup->smMaterial[BGMatNum].TextureFormState[1] = smTEXSTATE_FS_SCROLL;
		lpMaterialGroup->smMaterial[BGMatNum].MapOpacity = 0;
		TexCount = 1;
		break;

		case FIELD_BACKIMAGE_NIGHTRUIN2:
		BGMatNum = lpMaterialGroup->CreateTextureMaterial("game\\sky\\RuinNsky.bmp", 0, FALSE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
		lpMaterialGroup->smMaterial[BGMatNum].SelfIllum = 1.0f;
		TexCount = 0;
		break;



		case FIELD_BACKIMAGE_NIGHTFALL:

		BGMatNum = lpMaterialGroup->CreateTextureMaterial("game\\sky\\forever-Nsky00.bmp", 0, FALSE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
		TexCount = 0;
		break;

		case FIELD_BACKIMAGE_DAYFALL:

		BGMatNum = lpMaterialGroup->CreateTextureMaterial("game\\sky\\forever-Fsky00.bmp", 0, FALSE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
		lpMaterialGroup->AddTexture(BGMatNum, "game\\sky\\forever-Fsky00.tga");
		lpMaterialGroup->smMaterial[BGMatNum].TextureFormState[1] = smTEXSTATE_FS_SCROLL;
		lpMaterialGroup->smMaterial[BGMatNum].MapOpacity = 0;
		TexCount = 1;
		break;

		case FIELD_BACKIMAGE_GLOWFALL:

		BGMatNum = lpMaterialGroup->CreateTextureMaterial("game\\sky\\forever-Gsky00.bmp", 0, FALSE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
		lpMaterialGroup->AddTexture(BGMatNum, "game\\sky\\forever-Fsky00.tga");
		lpMaterialGroup->smMaterial[BGMatNum].TextureFormState[1] = smTEXSTATE_FS_SCROLL;
		lpMaterialGroup->smMaterial[BGMatNum].MapOpacity = 0;
		TexCount = 1;
		break;

	}


	vCnt = 0;
	tCnt = 0;
	y = -500 * fONE;
	v = -1;


	stepH = ((int)((float)ViewPointLen / 6))*fONE;

	int ViewDist;

	if(DsrFlag)
	{


		y = -1000 * fONE;
		ViewDist = 0;

		v = -1;
	}
	else
		ViewDist = ViewPointLen;

	for(cntY = 0; cntY < 5; cntY++)
	{
		u = 0;
		for(cntX = 0; cntX < 16; cntX++)
		{

			dx = GetSin[cntX * (ANGLE_360 / 16)] >> FLOATDS;
			dz = GetCos[cntX * (ANGLE_360 / 16)] >> FLOATDS;

			x = dx * ViewDist;
			z = dz * ViewDist;

			smObjBG->AddVertex(x, z, y);
			vCnt++;

			tP[tCnt].u = u;
			tP[tCnt].v = v;
			tCnt++;
			u += (256 / 4);
		}

		y += stepH;

		if(DsrFlag)
		{
			if(cntY == 0)
			{
				v = -1;
				y = -400 * fONE;
				ViewDist = ViewPointLen;
			}
			else
			{
				if(cntY >= 3)
					ViewDist = ViewPointLen - (4 * fONE);


				v -= (256 / 3);
			}
		}
		else
			v -= (256 / 5);
	}

	smObjBG->AddVertex(0, 0, y);



	for(cntY = 0; cntY < 4; cntY++)
	{
		for(cntX = 0; cntX < 16; cntX++)
		{

			for(cnt = 0; cnt < 3; cnt++)
			{
				a = BGFace[0][cnt];
				if((a & 1)) b = 1;
				else b = 0;
				if((a & 2)) c = 1;
				else c = 0;

				face[cnt] = ((cntX + b) & 15) + (cntY + c) * 16;
				tPoint[cnt] = &tP[face[cnt]];

				if(cntX == 15 && tPoint[cnt]->u == 0)
				{
					tPT[cnt].u = 256 * 4;
					tPT[cnt].v = tPoint[cnt]->v;
					tPoint[cnt] = &tPT[cnt];
				}


				if((tPoint[cnt]->u & 0xFF) == 0)
				{
					if(b == 0) tPT[cnt].u = tPoint[cnt]->u + 1;
					else tPT[cnt].u = tPoint[cnt]->u - 1;
					tPT[cnt].v = tPoint[cnt]->v;
					tPoint[cnt] = &tPT[cnt];
				}

			}

			fNum = smObjBG->AddFace(face[0], face[1], face[2], tPoint[0], tPoint[1], tPoint[2]);

			for(cnt = 0; cnt < TexCount; cnt++)
				smObjBG->AddTexLinkTP(fNum, 0, tPoint[0], tPoint[1], tPoint[2]);

			smObjBG->SetFaceMaterial(fNum, BGMatNum);



			for(cnt = 0; cnt < 3; cnt++)
			{
				a = BGFace[1][cnt];
				if((a & 1)) b = 1;
				else b = 0;
				if((a & 2)) c = 1;
				else c = 0;

				face[cnt] = ((cntX + b) & 15) + (cntY + c) * 16;
				tPoint[cnt] = &tP[face[cnt]];
				if(cntX == 15 && tPoint[cnt]->u == 0)
				{
					tPT[cnt].u = 256 * 4;
					tPT[cnt].v = tPoint[cnt]->v;
					tPoint[cnt] = &tPT[cnt];
				}

				if((tPoint[cnt]->u & 0xFF) == 0)
				{
					if(b == 0) tPT[cnt].u = tPoint[cnt]->u + 1;
					else tPT[cnt].u = tPoint[cnt]->u - 1;
					tPT[cnt].v = tPoint[cnt]->v;
					tPoint[cnt] = &tPT[cnt];
				}

			}
			fNum = smObjBG->AddFace(face[0], face[1], face[2], tPoint[0], tPoint[1], tPoint[2]);

			for(cnt = 0; cnt < TexCount; cnt++)
				smObjBG->AddTexLinkTP(fNum, 0, tPoint[0], tPoint[1], tPoint[2]);



			smObjBG->SetFaceMaterial(fNum, BGMatNum);
		}
	}
	smObjBG->ZeroNormals();
	smObjBG->ColorEffect = FALSE;

	smObjBG->ClipStates = (SMCLIP_NEARZ | SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);


	smInitColorZClip(21, 17, 14);

	Color_A = 0;
	Color_R = 0;
	Color_G = 0;
	Color_B = 0;

	FadeShowCount = DISP_BG_COUNT_MIN - 10;

	return TRUE;

}

int smBACKGROUND::Close()
{
	if(lpMaterialGroup)
	{
		delete lpMaterialGroup; lpMaterialGroup = 0;
	}
	if(smObjBG)
	{
		delete smObjBG; smObjBG = 0;
	}
	return TRUE;
}

int smBACKGROUND::Main()
{
	if(FadeShowCount < 0)
	{
		FadeShowCount++;
		Color_A = (FadeShowCount >> 1);
	}

	return TRUE;
}

int smBACKGROUND::Draw(int x, int y, int z, int ax, int ay, int az)
{

	POINT3D camera;
	POINT3D	angle;
	int	r, g, b, a, d;

	if(!smObjBG || FadeShowCount < DISP_BG_COUNT_MIN) return FALSE;

	if(y > 911 * fONE) y = 911 * fONE;

	camera.x = 0;
	camera.y = 50 << FLOATNS;
	camera.z = 0;

	angle.x = 0;
	angle.y = -100 * fONE;
	angle.z = 0;

	smObjBG->SetPosi(&camera, &angle);

	camera.x = 0;
	camera.y = y / 8;
	camera.z = 0;

	angle.x = ax;
	angle.y = ay;
	angle.z = az;


	a = smRender.Color_A;
	r = smRender.Color_R;
	g = smRender.Color_G;
	b = smRender.Color_B;

	smRender.Color_A = Color_A;
	smRender.Color_R = Color_R;
	smRender.Color_G = Color_G;
	smRender.Color_B = Color_B;

	d = smRender.AlphaTestDepth;
	smRender.AlphaTestDepth = 0;

	smRender.SetMaterialGroup(lpMaterialGroup);
	smObjBG->TmAnimation(0, 0, 0, 0);
	smObjBG->RenderD3D(&camera, &angle);

	smRender.AlphaTestDepth = d;

	smRender.Color_A = a;
	smRender.Color_R = r;
	smRender.Color_G = g;
	smRender.Color_B = b;

	return TRUE;

}
