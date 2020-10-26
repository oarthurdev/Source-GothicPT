





#include "smlib3d\\smd3d.h"
#include "FontImage.h"




#define DMAX_FONT_IMAGE					126
#define DMAX_SPECIAL_FONT_IMAGE			10


#define DFONT_HEIGHT_PIXEL				26.f




struct SFontImageChInfo
{
	int   IsCh;
	int   iWidehPixel;

	float fTexSt_x;
	float fTexSt_y;
	float fTexEnd_x;
	float fTexEnd_y;
};





static int						s_iFontImageMatNum;
static SFontImageChInfo			s_FontImageChInfo[DMAX_FONT_IMAGE];
static SFontImageChInfo			s_SpecialFontImageChInfo[DMAX_SPECIAL_FONT_IMAGE];








static int DrawFontBackToTexture2D(SFontImageChInfo *lpFontInfo, float fPos_x, float fPos_y, DWORD rgba, float fRatio)
{
	D3DTLVERTEX tlVertex[4];
	for (int cnt = 0; cnt < 4; cnt++)

	{
		tlVertex[cnt].sz = 0;
		tlVertex[cnt].rhw = 1;
		tlVertex[cnt].color = rgba;
		tlVertex[cnt].specular = 0;
	}
	tlVertex[0].sx = fPos_x - 0.5f;
	tlVertex[0].sy = fPos_y - 0.5f;
	tlVertex[0].tu = lpFontInfo->fTexSt_x;
	tlVertex[0].tv = lpFontInfo->fTexSt_y;
	tlVertex[1].sx = fPos_x - 0.5f;
	tlVertex[1].sy = (fPos_y + (DFONT_HEIGHT_PIXEL*fRatio)) - 0.5f;
	tlVertex[1].tu = lpFontInfo->fTexSt_x;
	tlVertex[1].tv = lpFontInfo->fTexEnd_y;
	tlVertex[2].sx = (fPos_x + (lpFontInfo->iWidehPixel*fRatio)) - 0.5f;
	tlVertex[2].sy = fPos_y - 0.5f;
	tlVertex[2].tu = lpFontInfo->fTexEnd_x;
	tlVertex[2].tv = lpFontInfo->fTexSt_y;
	tlVertex[3].sx = (fPos_x + (lpFontInfo->iWidehPixel*fRatio)) - 0.5f;
	tlVertex[3].sy = (fPos_y + (DFONT_HEIGHT_PIXEL*fRatio)) - 0.5f;
	tlVertex[3].tu = lpFontInfo->fTexEnd_x;
	tlVertex[3].tv = lpFontInfo->fTexEnd_y;
	MagFilter = true;
	DrawTexture(smMaterial[s_iFontImageMatNum].smTexture[0]->lpD3DTexture, tlVertex, true);
	MagFilter = false;
	return int(fPos_x + (lpFontInfo->iWidehPixel*fRatio));
}



void CreateFontImage(void)
{
	s_iFontImageMatNum = CreateTextureMaterial("image\\Bellatra\\FontImage.tga", NULL, 0, 0, 0, SMMAT_BLEND_ALPHA);

	FILE *fp = fopen("image\\Bellatra\\FontImagePos.dat", "rb");
	if(fp)
	{
		fread(s_FontImageChInfo, sizeof(s_FontImageChInfo), 1, fp);
		fread(s_SpecialFontImageChInfo, sizeof(s_SpecialFontImageChInfo), 1, fp);
		fclose(fp);
	}
}



int DrawFontImage(char *lpStr, int xPos, int yPos, DWORD rgba, float fRatio)
{
	int  xOffset = xPos;
	int  yOffset = yPos;

	int  len = ::strlen(lpStr);
	int  retNum = 0;

	
	for(int i = 0; i < len; i++)
	{
		if(s_FontImageChInfo[lpStr[i]].IsCh)
			retNum = DrawFontBackToTexture2D(&s_FontImageChInfo[lpStr[i]], float(xOffset), float(yOffset), rgba, fRatio);
		else if(lpStr[i] == 32)
			retNum += int(16 * fRatio);

		xOffset = retNum;
	}

	

	return retNum;
}








int DrawSpecialFontImage(int SpecialNum, int xPos, int yPos, DWORD rgba, float fRatio)
{
	if(SpecialNum < 0 || SpecialNum >= DMAX_SPECIAL_FONT_IMAGE || s_SpecialFontImageChInfo[SpecialNum].IsCh <= 0)
		return 0;

	int retNum = 0;

	
	retNum = DrawFontBackToTexture2D(&s_SpecialFontImageChInfo[SpecialNum], float(xPos), float(yPos), rgba, fRatio);
	

	return retNum;
}


