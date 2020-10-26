
#include "smlib3d\\smd3d.h"
#include "cracker.h"
#include "smwsock.h"
#include "character.h"
#include "avictrl.h"
#include "playmain.h"
#include "Sound\\dxwav.h"
#include "fileread.h"

#include "particle.h"
#include "netplay.h"

#include "sinbaram\\sinlinkheader.h"
#include "hobaram\\holinkheader.h"

#include "field.h"
#include "effectsnd.h"

#include "record.h"
#include "playsub.h"
#include "skillsub.h"
#include "damage.h"

#include "tjboy\\clanmenu\\tjclanDEF.h"
#include "tjboy\\clanmenu\\tjclan.h"
#include "tjboy\\clanmenu\\cE_CViewClanInfo.h"

#include "Language\\language.h"

#include "damage.h"
#include "AreaServer.h"

#include "Server\onserver.h"



extern int WinSizeX;
extern int WinSizeY;
extern HWND hwnd;
extern int MouseButton[3];


int LoadFieldMap(int PosNum, sFIELD *lpField, smSTAGE3D *lpStage);



smSTAGE3D		*smStage = 0;
smSTAGE3D		*smGameStage[2] = { 0,0 };
sFIELD			*StageField[2] = { 0,0 };


rsRECORD_DBASE	rsRecorder;

char szGameStageName[2][64];
DWORD			dwPlayTime = 0;
DWORD			dwMemError = 8080;

int	smStageCount = 0;
int SkipNextField = 0;

int	NightDayTime = 0;

int invPlayerArmor = 0;

DWORD	dwBattleTime = 0;
DWORD	dwBattleQuitTime = 0;
DWORD	dwCloseBoxTime = 0;

int		RestartPlayCount = 0;

DWORD SkillFalconPoint;

int InvArmorFileCode[] =
{ 0 ,9,1, 5 };

int	DarkLevel = 0;
int	BackColor_R = 0;
int	BackColor_G = 0;
int	BackColor_B = 0;

int	BackColor_mR = 0;
int	BackColor_mG = 0;
int	BackColor_mB = 0;

int	DarkLevel_Fix = 0;

int	DarkLightRange = 180 * fONE;

DWORD	dwGameWorldTime = 0;
DWORD	dwGameHour = 12;
DWORD	dwGameMin = 0;
DWORD	dwGameTimeOffset = 0;

int DarkLight = 0;


int WeatherMode = 0;
int Thunder = 0;


int	PkMode = 0;

int DispApp_SkillPoint = 0;

int rcnt2;

int modelX = 255;
int modelZ = 512;
int wflag = 0;
int wrad = 0;

DWORD	UseEtherCoreCode = 0;

int	RecordFailCount = 0;


int	Record_BlockCount = 0;
int	Record_DefenceCount = 0;
int Record_RecvDamageCount = 0;
int Record_TotalRecvDamageCount = 0;



DWORD	AutoMouse_LastCheckTime = 0;
DWORD	AutoMouse_StartCheckTime = 0;
int		AutoMouse_WM_Count = 0;
int 	AutoMouse_Distance = 0;
int		AutoMouse_Attack_Count = 0;





smPAT3D *PatArrow;

smPAT3D *PatEffectShield = 0;

smPAT3D *PatSparkShield = 0;

smPAT3D *PatDivineShield = 0;

smPAT3D *PatGodlyShield = 0;

smPAT3D *PatCrown = 0;


smPAT3D *PatShadow[SHADOW_PAT_MAX] = { 0,0,0,0 };



smPAT3D *PatIceFoot[ICE_FOOT_PAT_MAX];


int	Moving_DblClick = 0;
POINT3D	MousePos_DblClick;

POINT3D	TracePos_DblClick;
int TraceMode_DblClick = 0;

int	ActionGameMode = 0;



smCHAR		*lpCurPlayer = 0;

DWORD	dwRotPlayDelayTime = 0;




scITEM	scItems[DISP_ITEM_MAX];

smCHAR	chrOtherPlayer[OTHER_PLAYER_MAX];

smCHAR_INFO	smCharInfo_Back;


int	MatEachBox;
int	MatEachMenuBox;
int MatEnergyBox[2];
int MatLight[4];

int	MatEachTradeButton[2];
int MatMonBroodImage[8];


smTRANS_COMMAND	sPartyPosion;
DWORD			dwPartyPosionTime;

DIRECTDRAWSURFACE	lpDDS_ParTradeButton[4][2];
DIRECTDRAWSURFACE	lpDDS_ParTradeToolTip[4];



char *szFlame[8] = {
	"image\\flame1.bmp",
	"image\\flame2.bmp",
	"image\\flame3.bmp",
	"image\\flame4.bmp",
	"image\\flame5.bmp",
	"image\\flame6.bmp",
	"image\\flame7.bmp",
	"image\\flame8.bmp"
};

char *szShine[] = {
	"image\\shine0.bmp",
	"image\\shine2.bmp",
	"image\\shine4.bmp",
	"image\\shine6.bmp",
	"image\\shine8.bmp",
	""
};

char *szBlood1[] = {
	"image\\blood\\b1_001.tga",
	"image\\blood\\b1_002.tga",
	"image\\blood\\b1_003.tga",
	"image\\blood\\b1_004.tga"
};

char *szBlood2[] = {
	"image\\blood\\b2_001.tga",
	"image\\blood\\b2_002.tga",
	"image\\blood\\b2_003.tga",
	"image\\blood\\b2_004.tga"
};


char *szShadowImageFile = "image\\bshadow.bmp";




char *g_IceFootImageFileBuff[ICE_FOOT_PAT_MAX] =
{
	"image\\mk-r.tga",
	"image\\mk-l.tga",
};





void InitStageLoader()
{
	szGameStageName[0][0] = 0;
	szGameStageName[1][0] = 0;
	smGameStage[0] = 0;
	smGameStage[1] = 0;
}


smSTAGE3D *LoadStageFromField(sFIELD *lpField, sFIELD *lpSecondField)
{
	smSTAGE3D *lpstg;
	char *szStageFile;
	int cnt;
	int	Bip;
	char	szBuff[128];

	szStageFile = lpField->szName;

	if(lpField == StageField[0])
		return smGameStage[0];
	if(lpField == StageField[1])
		return smGameStage[1];

	lpstg = new smSTAGE3D;


	lpstg->VectLight.x = smConfig.MapLightVector.x;
	lpstg->VectLight.y = smConfig.MapLightVector.y;
	lpstg->VectLight.z = smConfig.MapLightVector.z;

	lpstg->Bright = smConfig.MapBright;
	lpstg->Contrast = smConfig.MapContrast;


	AddLoaderStage(lpstg, szStageFile);

	if(!lpstg->StageObject)
	{


		wsprintf(szBuff, "Stage Loading Error ( %s )", szStageFile);
		Record_ClinetLogFile(szBuff);
		delete lpstg;
		return NULL;
	}


	for(cnt = 0; cnt < lpField->StgObjCount; cnt++)
	{
		Bip = lpField->GetStageObjectName(cnt, szBuff, sizeof(szBuff));
		if(szBuff[0])
		{
			if(Bip)
				lpstg->StageObject->AddObjectFile(szBuff, szBuff);
			else
				lpstg->StageObject->AddObjectFile(szBuff);
		}
	}

	if(lpField->StgObjCount && renderDevice.IsDevice())
	{
		ReadTextures();
		lpstg->smMaterialGroup->CheckMatreialTextureSwap();
	}

	if(lpSecondField && lpSecondField == StageField[0])
	{
		if(smGameStage[1])
			delete smGameStage[1];
		smGameStage[1] = lpstg;
		StageField[1] = lpField;
		LoadFieldMap(1, lpField, lpstg);
	}
	else
	{
		if(!lpSecondField || lpSecondField == StageField[1])
		{
			if(smGameStage[0])
				delete smGameStage[0];
			smGameStage[0] = lpstg;
			StageField[0] = lpField;
			LoadFieldMap(0, lpField, lpstg);
		}
	}


	if(StageField[0])
		strcpy_s(szGameStageName[0], StageField[0]->szName);

	if(StageField[1])
		strcpy_s(szGameStageName[1], StageField[1]->szName);


	DWORD	dwTime = GetCurrentTime();

	if(dwLastRecvGameServerTime && dwLastRecvGameServerTime < dwTime)
		dwLastRecvGameServerTime = dwTime;
	if(dwLastRecvGameServerTime2 && dwLastRecvGameServerTime2 < dwTime)
		dwLastRecvGameServerTime2 = dwTime;
	if(dwLastRecvGameServerTime3 && dwLastRecvGameServerTime3 < dwTime)
		dwLastRecvGameServerTime3 = dwTime;
	if(dwLastRecvGameServerTime4 && dwLastRecvGameServerTime4 < dwTime)
		dwLastRecvGameServerTime4 = dwTime;

	if(AreaServerMode)
	{

		if(lpWSockServer_Area[0]) lpWSockServer_Area[0]->dwDeadLockTime = dwTime;
		if(lpWSockServer_Area[1]) lpWSockServer_Area[1]->dwDeadLockTime = dwTime;
	}

	return lpstg;
}


smSTAGE3D *LoadStageFromField2(sFIELD *lpField, sFIELD *lpSecondField)
{
	smSTAGE3D *lpstg;
	char *szStageFile;
	int cnt;
	int Bip;
	char szBuff[128];


	szStageFile = lpField->szName;

	if(lpField == StageField[0]) return smGameStage[0];
	if(lpField == StageField[1]) return smGameStage[1];

	lpstg = new smSTAGE3D;


	lpstg->VectLight.x = smConfig.MapLightVector.x;
	lpstg->VectLight.y = smConfig.MapLightVector.y;
	lpstg->VectLight.z = smConfig.MapLightVector.z;

	lpstg->Bright = smConfig.MapBright;
	lpstg->Contrast = smConfig.MapContrast;


	AddLoaderStage(lpstg, szStageFile);

	if(!lpstg->StageObject)
	{


		wsprintf(szBuff, "Stage Loading Error ( %s )", szStageFile);
		Record_ClinetLogFile(szBuff);
		delete lpstg;
		return NULL;
	}


	for(cnt = 0; cnt < lpField->StgObjCount; cnt++)
	{
		Bip = lpField->GetStageObjectName(cnt, szBuff, sizeof(szBuff));
		if(szBuff[0])
		{
			if(Bip)
				lpstg->StageObject->AddObjectFile(szBuff, szBuff);
			else
				lpstg->StageObject->AddObjectFile(szBuff);
		}
	}

	if(lpField->StgObjCount && renderDevice.IsDevice())
	{
		ReadTextures();
		lpstg->smMaterialGroup->CheckMatreialTextureSwap();
	}



	if(lpSecondField && lpSecondField == StageField[0])
	{
		if(smGameStage[1]) delete smGameStage[1];
		smGameStage[1] = lpstg;
		StageField[1] = lpField;

		LoadFieldMap(1, lpField, lpstg);
	}
	else
	{
		if(!lpSecondField || lpSecondField == StageField[1])
		{
			if(smGameStage[0]) delete smGameStage[0];
			smGameStage[0] = lpstg;
			StageField[0] = lpField;

			LoadFieldMap(0, lpField, lpstg);
		}
	}

	if(StageField[0]) strcpy_s(szGameStageName[0], StageField[0]->szName);
	if(StageField[1]) strcpy_s(szGameStageName[1], StageField[1]->szName);

	DWORD	dwTime = GetCurrentTime();
	if(dwLastRecvGameServerTime && dwLastRecvGameServerTime < dwTime) dwLastRecvGameServerTime = dwTime;
	if(dwLastRecvGameServerTime2 && dwLastRecvGameServerTime2 < dwTime) dwLastRecvGameServerTime2 = dwTime;
	if(dwLastRecvGameServerTime3 && dwLastRecvGameServerTime3 < dwTime) dwLastRecvGameServerTime3 = dwTime;
	if(dwLastRecvGameServerTime4 && dwLastRecvGameServerTime4 < dwTime) dwLastRecvGameServerTime4 = dwTime;

	if(AreaServerMode)
	{

		if(lpWSockServer_Area[0]) lpWSockServer_Area[0]->dwDeadLockTime = dwTime;
		if(lpWSockServer_Area[1]) lpWSockServer_Area[1]->dwDeadLockTime = dwTime;
	}

	return lpstg;
}


smSTAGE3D *LoadStage(char *szStageFile)
{
	smSTAGE3D *lpstg;

	if(lstrcmpi(szGameStageName[0], szStageFile) == 0) return smGameStage[0];
	if(lstrcmpi(szGameStageName[1], szStageFile) == 0) return smGameStage[1];

	lpstg = new smSTAGE3D;


	lpstg->VectLight.x = smConfig.MapLightVector.x;
	lpstg->VectLight.y = smConfig.MapLightVector.y;
	lpstg->VectLight.z = smConfig.MapLightVector.z;

	lpstg->Bright = smConfig.MapBright;
	lpstg->Contrast = smConfig.MapContrast;


	AddLoaderStage(lpstg, szStageFile);

	smStageCount = (smStageCount + 1) & 1;

	if(smGameStage[smStageCount]) delete smGameStage[smStageCount];

	smGameStage[smStageCount] = lpstg;

	return lpstg;
}


smSTAGE3D *LoadStage2(char *szStageFile)
{
	smSTAGE3D *lpstg;

	if(lstrcmpi(szGameStageName[0], szStageFile) == 0) return smGameStage[0];
	if(lstrcmpi(szGameStageName[1], szStageFile) == 0) return smGameStage[1];

	lpstg = new smSTAGE3D;


	lpstg->VectLight.x = smConfig.MapLightVector.x;
	lpstg->VectLight.y = smConfig.MapLightVector.y;
	lpstg->VectLight.z = smConfig.MapLightVector.z;

	lpstg->Bright = smConfig.MapBright;
	lpstg->Contrast = smConfig.MapContrast;


	smSTAGE3D_ReadASE(szStageFile, lpstg);
	lpstg->Head = TRUE;

	smStageCount = (smStageCount + 1) & 1;

	if(smGameStage[smStageCount]) delete smGameStage[smStageCount];

	smGameStage[smStageCount] = lpstg;

	return lpstg;
}


int PlayCounter = 0;

char PlayerName[64] = { 0,0,0,0 };


void InitStage()
{


	szGameStageName[0][0] = 0;
	szGameStageName[1][0] = 0;

	InitFieldMap();


	InitField();

	if(GameStartField < 0)
	{

		StartField();
	}
	else
	{

		if(CharacterPosX == PrisonX && CharacterPosZ == PrisonZ)
		{

			WarpPrisonField((int *)&smConfig.Posi_Player.x, (int *)&smConfig.Posi_Player.y);
		}
		else
		{
			WarpFieldNearPos(GameStartField, CharacterPosX, CharacterPosZ, (int *)&smConfig.Posi_Player.x, (int *)&smConfig.Posi_Player.y);
		}
	}



	smRender.Color_R = 0;
	smRender.Color_G = 0;
	smRender.Color_B = 0;
	smRender.Color_A = 0;



	LoadFieldMap(0, StageField[0], smGameStage[0]);


}

void CloseStage()
{



	if(smGameStage[1]) delete smGameStage[1];
	if(smGameStage[0]) delete smGameStage[0];

}


struct _DRAW_LIGHTLIST
{
	smLIGHT3D	*smLight;
	int			x, y, z;
};


_DRAW_LIGHTLIST	DrawLight[64];
_DRAW_LIGHTLIST	DrawLightSmall[64];
int DrawLightCnt;
int DrawLightSmallCnt;


int DrawLightImage(smSTAGE3D *lpStage, int x, int y, int z)
{




	POINT	Pos;
	RECT	Rect;

	int cnt, cnt2;
	int dx, dy, dz, dist;
	int tz;




	int x1, y1, z1, x2, y2, z2, x3, y3, z3;
	smRENDFACE *rendface;
	smRENDVERTEX *rv;
	int flg;






	int type;


	for(cnt = 0; cnt < lpStage->nLight; cnt++)
	{

		type = lpStage->smLight[cnt].type;

		if((type&smLIGHT_TYPE_LENS) &&
			(!(lpStage->smLight[cnt].type&smLIGHT_TYPE_NIGHT) || NightDayTime))
		{

			dx = (x - lpStage->smLight[cnt].x) >> FLOATNS;
			dy = (y - lpStage->smLight[cnt].y) >> FLOATNS;
			dz = (z - lpStage->smLight[cnt].z) >> FLOATNS;
			dist = dx*dx + dy*dy + dz*dz;

			if(dist < DIST_TRANSLEVEL_LOW && abs(dx) < 64 * 38 && abs(dz) < 64 * 38)
			{
				if(tz = smRender.GetRect2D(lpStage->smLight[cnt].x, lpStage->smLight[cnt].y, lpStage->smLight[cnt].z,
					0, 0, &Rect, &Pos))
				{

					if(Pos.x > 0 && Pos.x < WinSizeX && Pos.y>0 && Pos.y < WinSizeY)
					{
						tz -= 64 * fONE;

						if(tz > (64 * 22 * fONE))
						{
							DrawLightSmall[DrawLightSmallCnt].smLight = &lpStage->smLight[cnt];
							DrawLightSmall[DrawLightSmallCnt].x = Pos.x;
							DrawLightSmall[DrawLightSmallCnt].y = Pos.y;
							DrawLightSmall[DrawLightSmallCnt].z = tz;
							DrawLightSmallCnt++;
						}
						else
						{

							for(cnt2 = 0; cnt2 < smRender.nRendFace; cnt2++)
							{
								if(!(smRender.RendFace[cnt2].ClipStatus&SMCLIP_DISPLAYOUT))
								{
									rendface = &smRender.RendFace[cnt2];

									rv = rendface->lpRendVertex[0];
									x1 = (int)rv->xy[0];
									y1 = (int)rv->xy[1];
									z1 = rv->tz;
									rv = rendface->lpRendVertex[1];
									x2 = (int)rv->xy[0];
									y2 = (int)rv->xy[1];
									z2 = rv->tz;
									rv = rendface->lpRendVertex[2];
									x3 = (int)rv->xy[0];
									y3 = (int)rv->xy[1];
									z3 = rv->tz;

									flg = 0;
									if(tz > z1 && tz > z2 && tz > z3)
									{

										if(Pos.x < x1 && Pos.x < x2 && Pos.x < x3) flg++;
										if(Pos.x > x1 && Pos.x > x2 && Pos.x > x3) flg++;
										if(Pos.y < y1 && Pos.y < y2 && Pos.y < y3) flg++;
										if(Pos.y > y1 && Pos.y > y2 && Pos.y > y3) flg++;
										if(flg == 0) break;



									}
								}

							}

							if(cnt2 >= smRender.nRendFace)
							{
								DrawLight[DrawLightCnt].smLight = &lpStage->smLight[cnt];
								DrawLight[DrawLightCnt].x = Pos.x;
								DrawLight[DrawLightCnt].y = Pos.y;
								DrawLight[DrawLightCnt].z = tz;
								DrawLightCnt++;
							}
							else
							{
								DrawLightSmall[DrawLightSmallCnt].smLight = &lpStage->smLight[cnt];
								DrawLightSmall[DrawLightSmallCnt].x = Pos.x;
								DrawLightSmall[DrawLightSmallCnt].y = Pos.y;
								DrawLightSmall[DrawLightSmallCnt].z = tz;
								DrawLightSmallCnt++;
							}

						}

					}
				}
			}
		}
	}

	return TRUE;
}

int DrawLightImage()
{
	smFACE2D face2d;
	int size;
	smRENDFACE *RendFace;
	int cnt;

	smRender.SetMaterialGroup(smMaterialGroup);

	smRender.Init();

	for(cnt = 0; cnt < DrawLightSmallCnt; cnt++)
	{

		size = 40 * fONE;


		if(size > 0)
		{

			face2d.TexRect.left = 0;
			face2d.TexRect.right = 1;
			face2d.TexRect.top = 0;
			face2d.TexRect.bottom = 1;
			face2d.width = size;
			face2d.height = size;
			face2d.Transparency = 255;
			face2d.r = 255; face2d.g = 255; face2d.b = 255;
			face2d.x = DrawLightSmall[cnt].smLight->x;
			face2d.y = DrawLightSmall[cnt].smLight->y;
			face2d.z = DrawLightSmall[cnt].smLight->z;
			face2d.MatNum = MatLight[1];

			RendFace = smRender.AddFace2D(&face2d);
		}
	}

	if(smRender.nRendFace > 0)
	{
		smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
		smRender.ClipRendFace();
		smRender.GeomVertex2D(FALSE);
		smRender.RenderD3D();
	}


	smRender.Init();

	for(cnt = 0; cnt < DrawLightCnt; cnt++)
	{
		size = 160 * fONE;



		if(size > 0)
		{

			face2d.TexRect.left = 0;
			face2d.TexRect.right = 1;
			face2d.TexRect.top = 0;
			face2d.TexRect.bottom = 1;
			face2d.width = size;
			face2d.height = size;
			face2d.Transparency = 255;
			face2d.r = 255; face2d.g = 255; face2d.b = 255;
			face2d.x = DrawLight[cnt].smLight->x;
			face2d.y = DrawLight[cnt].smLight->y;
			face2d.z = DrawLight[cnt].smLight->z;
			face2d.MatNum = MatLight[0];

			RendFace = smRender.AddFace2D(&face2d);
		}
	}

	if(smRender.nRendFace > 0)
	{
		smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
		smRender.ClipRendFace();
		smRender.GeomVertex2D(FALSE);
		for(cnt = 0; cnt < smRender.nRendVertex; cnt++)
		{
			smRender.RendVertex[cnt].zb = 0.001f;
		}

		smRender.RenderD3D();

	}


	return TRUE;

}

int SetStageDynLight(smSTAGE3D *lpStage, int x, int y, int z)
{

	int cnt;
	int dx, dy, dz, dist;
	int type;


	for(cnt = 0; cnt < lpStage->nLight; cnt++)
	{

		dx = (x - lpStage->smLight[cnt].x) >> FLOATNS;
		dy = (y - lpStage->smLight[cnt].y) >> FLOATNS;
		dz = (z - lpStage->smLight[cnt].z) >> FLOATNS;
		dist = dx*dx + dy*dy + dz*dz;




		type = lpStage->smLight[cnt].type;

		if(dist < 0x300000 && (type&smLIGHT_TYPE_DYNAMIC) && abs(dx) < 0x2000 && abs(dz) < 0x2000)
		{
			if((lpStage->smLight[cnt].type&smLIGHT_TYPE_NIGHT) && NightDayTime)
			{



				smRender.AddDynamicLight(lpStage->smLight[cnt].type,
					lpStage->smLight[cnt].x, lpStage->smLight[cnt].y, lpStage->smLight[cnt].z,
					lpStage->smLight[cnt].r, lpStage->smLight[cnt].g, lpStage->smLight[cnt].b,
					0, lpStage->smLight[cnt].Range);

			}
			else
			{
				if(DarkLevel > 0)
				{


					smRender.AddDynamicLight(lpStage->smLight[cnt].type,
						lpStage->smLight[cnt].x, lpStage->smLight[cnt].y, lpStage->smLight[cnt].z,

						(lpStage->smLight[cnt].r*DarkLevel) >> 8,
						(lpStage->smLight[cnt].g*DarkLevel) >> 8,
						(lpStage->smLight[cnt].b*DarkLevel) >> 8,
						0, lpStage->smLight[cnt].Range);

				}
			}
		}
	}

	return TRUE;

}




int doop = 0;



int DisplayStage(int x, int y, int z, int angX, int angY, int angZ)
{







	int cnt;
	int r, g, b, l;



	DrawLightCnt = 0;
	DrawLightSmallCnt = 0;


	smRender.ZWriteAuto = TRUE;



	if(MipMapModeCreate)
		renderDevice.SetTextureStageState(0, D3DTSS_MIPFILTER, D3DTFP_LINEAR);


	for(cnt = 0; cnt < 2; cnt++)
	{
		if(smGameStage[cnt])
		{



			if(DarkLevel > 0 && StageField[cnt]->State == FIELD_STATE_VILLAGE)
			{

				r = smRender.Color_R;
				g = smRender.Color_G;
				b = smRender.Color_B;
				l = smRender.nRendLight;

				smRender.Color_R >>= 1;
				smRender.Color_G >>= 1;
				smRender.Color_B >>= 1;

				if(smRender.nRendLight > 0 && smRender.smRendLight[0].Range == DarkLightRange)
				{
					smRender.smRendLight[0].Range = 0;
					l = 1;
				}
				else
					l = 0;

				if(smGameStage[cnt]->DrawStage2(x, y, z, angX, angY, angZ) == TRUE)
				{




					DrawLightImage(smGameStage[cnt], x, y, z);
					smGameStage[cnt]->StageObject->Draw(x, y, z, angX, angY, angZ);
				}

				smRender.Color_R = r;
				smRender.Color_G = g;
				smRender.Color_B = b;

				if(l) smRender.smRendLight[0].Range = DarkLightRange;



			}
			else
			{
				if(smGameStage[cnt]->DrawStage2(x, y, z, angX, angY, angZ) == TRUE)
				{



					DrawLightImage(smGameStage[cnt], x, y, z);
					smGameStage[cnt]->StageObject->Draw(x, y, z, angX, angY, angZ);
				}
			}

		}
	}

	if(MipMapModeCreate)
		renderDevice.SetTextureStageState(0, D3DTSS_MIPFILTER, D3DTFP_NONE);


	smRender.ZWriteAuto = FALSE;


	if((MaterialFrame & 0x3F) == 0)
	{


		CheckInvenItemCode();
	}

	return TRUE;
}



void CreatePatIceFoot(int Num, int sizeX, int sizeZ)
{
	int MatShadow = CreateTextureMaterial(g_IceFootImageFileBuff[Num], 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	smTPOINT tPoint[4];
	tPoint[0].u = 0;
	tPoint[0].v = 0;
	tPoint[1].u = 256;
	tPoint[1].v = 0;
	tPoint[2].u = 0;
	tPoint[2].v = 256;
	tPoint[3].u = 256;
	tPoint[3].v = 256;

	smOBJ3D *objIceFoot = new smOBJ3D(4, 2);
	objIceFoot->AddVertex(-sizeX, -sizeZ, 0);
	objIceFoot->AddVertex(sizeX, -sizeZ, 0);
	objIceFoot->AddVertex(-sizeX, sizeZ, 0);
	objIceFoot->AddVertex(sizeX, sizeZ, 0);

	objIceFoot->AddFace(0, 1, 2, &tPoint[2], &tPoint[3], &tPoint[0]);
	objIceFoot->AddFace(2, 1, 3, &tPoint[0], &tPoint[3], &tPoint[1]);
	objIceFoot->ZeroNormals();

	objIceFoot->SetFaceMaterial(0, MatShadow);
	objIceFoot->SetFaceMaterial(1, MatShadow);

	PatIceFoot[Num] = new smPAT3D;
	PatIceFoot[Num]->AddObject(objIceFoot);
}


void CreatePatShadow(int Num, int sizeX, int sizeZ)
{
	smTPOINT tPoint[4];
	smOBJ3D *objShadow;

	int MatShadow;

	MatShadow = CreateTextureMaterial(szShadowImageFile, 0, 0, 0, 0, SMMAT_BLEND_SHADOW);
	smMaterial[MatShadow].SelfIllum = 1;

	tPoint[0].u = 0;
	tPoint[0].v = 0;
	tPoint[1].u = 256;
	tPoint[1].v = 0;
	tPoint[2].u = 0;
	tPoint[2].v = 256;
	tPoint[3].u = 256;
	tPoint[3].v = 256;


	objShadow = new smOBJ3D(4, 2);
	objShadow->AddVertex(-sizeX, -sizeZ, 0);
	objShadow->AddVertex(sizeX, -sizeZ, 0);
	objShadow->AddVertex(-sizeX, sizeZ, 0);
	objShadow->AddVertex(sizeX, sizeZ, 0);

	objShadow->AddFace(0, 1, 2, &tPoint[0], &tPoint[1], &tPoint[2]);
	objShadow->AddFace(2, 1, 3, &tPoint[2], &tPoint[1], &tPoint[3]);
	objShadow->ZeroNormals();

	objShadow->SetFaceMaterial(0, MatShadow);
	objShadow->SetFaceMaterial(1, MatShadow);

	PatShadow[Num] = new smPAT3D;
	PatShadow[Num]->AddObject(objShadow);
}

void CreatePatShadow2(int Num, int sizeX, int sizeZ)
{
	smTPOINT tPoint[9];
	smOBJ3D *objShadow;

	int MatShadow;

	MatShadow = CreateTextureMaterial(szShadowImageFile, 0, 0, 0, 0, SMMAT_BLEND_SHADOW);
	smMaterial[MatShadow].SelfIllum = 1;

	tPoint[0].u = 0;
	tPoint[0].v = 0;
	tPoint[1].u = 128;
	tPoint[1].v = 0;
	tPoint[2].u = 256;
	tPoint[2].v = 0;

	tPoint[3].u = 0;
	tPoint[3].v = 128;
	tPoint[4].u = 128;
	tPoint[4].v = 128;
	tPoint[5].u = 256;
	tPoint[5].v = 128;

	tPoint[6].u = 0;
	tPoint[6].v = 256;
	tPoint[7].u = 128;
	tPoint[7].v = 256;
	tPoint[8].u = 256;
	tPoint[8].v = 256;


	objShadow = new smOBJ3D(9, 8);
	objShadow->AddVertex(-sizeX, -sizeZ, 0);
	objShadow->AddVertex(0, -sizeZ, 0);
	objShadow->AddVertex(sizeX, -sizeZ, 0);

	objShadow->AddVertex(-sizeX, 0, 0);
	objShadow->AddVertex(0, 0, 0);
	objShadow->AddVertex(sizeX, 0, 0);

	objShadow->AddVertex(-sizeX, sizeZ, 0);
	objShadow->AddVertex(0, sizeZ, 0);
	objShadow->AddVertex(sizeX, sizeZ, 0);

	objShadow->AddFace(0, 1, 3, &tPoint[0], &tPoint[1], &tPoint[3]);
	objShadow->AddFace(3, 1, 4, &tPoint[3], &tPoint[1], &tPoint[4]);

	objShadow->AddFace(1, 2, 4, &tPoint[0], &tPoint[2], &tPoint[4]);
	objShadow->AddFace(4, 2, 5, &tPoint[4], &tPoint[2], &tPoint[5]);

	objShadow->AddFace(3, 4, 6, &tPoint[3], &tPoint[4], &tPoint[6]);
	objShadow->AddFace(6, 4, 7, &tPoint[6], &tPoint[4], &tPoint[7]);

	objShadow->AddFace(4, 5, 7, &tPoint[4], &tPoint[5], &tPoint[7]);
	objShadow->AddFace(7, 5, 8, &tPoint[7], &tPoint[5], &tPoint[8]);

	objShadow->SetFaceMaterial(0, MatShadow);
	objShadow->SetFaceMaterial(1, MatShadow);
	objShadow->SetFaceMaterial(2, MatShadow);
	objShadow->SetFaceMaterial(3, MatShadow);
	objShadow->SetFaceMaterial(4, MatShadow);
	objShadow->SetFaceMaterial(5, MatShadow);
	objShadow->SetFaceMaterial(6, MatShadow);
	objShadow->SetFaceMaterial(7, MatShadow);

	PatShadow[Num] = new smPAT3D;
	PatShadow[Num]->AddObject(objShadow);
}



int AdminCharMode = 0;

int AdminCharDisable = 0;


static char szDataDirectory[256];
char szCharFileList[256][256];
int CharFileCnt;
int CharPlayCnt = 0;


static char *SetDirectoryFromFile(char *filename)
{
	int len;
	int cnt;

	strcpy_s(szDataDirectory, filename);

	len = lstrlen(szDataDirectory);

	for(cnt = len; cnt >= 0; cnt--)
		if(szDataDirectory[cnt] == '\\') break;

	szDataDirectory[cnt + 1] = NULL;

	return szDataDirectory;
}


int SetCharFileList(char *szCharFile)
{
	CharFileCnt = 0;
	char szFindPath[256];

	SetDirectoryFromFile(szCharFile);

	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;

	strcpy_s(szFindPath, szDataDirectory);
	lstrcat(szFindPath, "\\*.ini");


	hFindHandle = FindFirstFile(szFindPath, &fd);
	if(hFindHandle == INVALID_HANDLE_VALUE)
	{
		FindClose(hFindHandle);
		return 0;
	}
	while(1)
	{
		strcpy_s(szCharFileList[CharFileCnt], szDataDirectory);
		lstrcat(szCharFileList[CharFileCnt], fd.cFileName);
		CharFileCnt++;

		if(FindNextFile(hFindHandle, &fd) == FALSE)
			break;
		if(CharFileCnt > 255)
			break;
	}
	FindClose(hFindHandle);

	return TRUE;
}

void SetNextPlayerPattern()
{
	if(lpCurPlayer->PatLoading)
		return;


	AdminCharDisable = TRUE;

	if(AdminCharMode)
	{
		memcpy(&lpCurPlayer->smCharInfo, &smCharInfo_Back, sizeof(smCHAR_INFO));
		ReformCharForm();
		AdminCharMode = 0;
		lpCurPlayer->PatLoading = TRUE;
		AddLoaderPattern(lpCurPlayer, lpCurPlayer->smCharInfo.szModelName, lpCurPlayer->smCharInfo.szModelName2);
		lpCurPlayer->DisplayTools = TRUE;
		return;
	}

	AdminCharMode = 0;
	lpCurPlayer->PatLoading = TRUE;
	AddLoaderPattern(lpCurPlayer, szCharFileList[CharPlayCnt], lpCurPlayer->smCharInfo.szModelName2);
	lpCurPlayer->DisplayTools = TRUE;

	CharPlayCnt++;
	if(CharPlayCnt >= CharFileCnt) CharPlayCnt = 0;
}

void SetPlayerBodyPattern(char *szBodyFile)
{
	char szBuff[256];

	if(lpCurPlayer->PatLoading)
		return;

	wsprintf(szBuff, "char\\tmABCD\\%s.ini", szBodyFile);
	FILE *fp = fopen(szBuff, "rb");
	if(!fp) return;
	fclose(fp);

	lpCurPlayer->PatLoading = TRUE;
	AddLoaderPattern(lpCurPlayer, szBuff, lpCurPlayer->smCharInfo.szModelName2);
	lpCurPlayer->DisplayTools = TRUE;
}

void SetPlayerPattern(char *szFile)
{
	if(lpCurPlayer->PatLoading)
		return;

	FILE *fp = fopen(szFile, "rb");
	if(!fp) return;
	fclose(fp);

	lpCurPlayer->PatLoading = TRUE;
	AddLoaderPattern(lpCurPlayer, szFile, 0);
	lpCurPlayer->DisplayTools = TRUE;

	ReformCharForm();

	lpCurPlayer->smCharInfo.bUpdateInfo[0]++;
	SendSetObjectSerial(lpCurPlayer->dwObjectSerial);

}

char szNpcFileList[64][64];
int NpcFileCnt;
int NpcPlayCnt = 0;

char *NpcSelectedName = 0;


int SetNpcFileList(char *szNpcDirectory)
{
	NpcFileCnt = 0;
	char szFindPath[256];



	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;

	strcpy_s(szFindPath, szNpcDirectory);
	lstrcat(szFindPath, "*.npc");


	hFindHandle = FindFirstFile(szFindPath, &fd);
	if(hFindHandle == INVALID_HANDLE_VALUE)
	{
		FindClose(hFindHandle);
		return 0;

	}
	while(1)
	{
		strcpy_s(szNpcFileList[NpcFileCnt], szNpcDirectory);
		lstrcat(szNpcFileList[NpcFileCnt], fd.cFileName);
		NpcFileCnt++;

		if(FindNextFile(hFindHandle, &fd) == FALSE)
			break;
		if(NpcFileCnt > 64)
			break;

	}
	FindClose(hFindHandle);

	return TRUE;
}

void SetNextNpcPattern()
{
	if(lpCurPlayer->PatLoading)
		return;

	if(AdminCharMode == 0)
		memcpy(&smCharInfo_Back, &lpCurPlayer->smCharInfo, sizeof(smCHAR_INFO));


	AdminCharDisable = TRUE;

	AdminCharMode = 1;


	lpCurPlayer->smCharInfo.dwCharSoundCode = 0;


	if(smCharDecode(szNpcFileList[NpcPlayCnt], &lpCurPlayer->smCharInfo, 0))
	{
		lpCurPlayer->PatLoading = TRUE;
		AddLoaderPattern(lpCurPlayer, lpCurPlayer->smCharInfo.szModelName);

		lpCurPlayer->DisplayTools = FALSE;
		lpCurPlayer->smCharInfo.SizeLevel = 1;

		NpcSelectedName = szNpcFileList[NpcPlayCnt];

		NpcPlayCnt++;
		if(NpcPlayCnt >= NpcFileCnt) NpcPlayCnt = 0;
	}
	ReformCharForm();
}


int LaunchPartyPostion()
{
	int x, y, z, dist, ddist;
	int cnt;
	smCHAR *lpChar;

	x = lpCurPlayer->pX;
	y = lpCurPlayer->pY + 48 * fONE;
	z = lpCurPlayer->pZ;

	if(sPartyPosion.code == OpCode::OPCODE_PARTY_POTION)
	{

		if(lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_DEAD)
		{
			CheckCharForm();
			if(sPartyPosion.WParam)
			{
				sinSetLife(sinGetLife() + sPartyPosion.WParam);
				StartEffect(x, y, z, EFFECT_POTION1);
			}
			if(sPartyPosion.LParam)
			{
				sinSetMana(sinGetMana() + sPartyPosion.LParam);
				StartEffect(x, y, z, EFFECT_POTION2);
			}
			if(sPartyPosion.SParam)
			{
				sinSetStamina(sinGetStamina() + sPartyPosion.SParam);
				StartEffect(x, y, z, EFFECT_POTION3);
			}
			ResetEnergyGraph(3);
			ReformCharForm();
			sinPlaySound(SIN_SOUND_EAT_POTION, GetDistVolume(x, y, z));

		}



		for(cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
		{
			if(chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].dwObjectSerial && chrOtherPlayer[cnt].PartyFlag &&
				chrOtherPlayer[cnt].dwObjectSerial != sPartyPosion.EParam &&
				chrOtherPlayer[cnt].MotionInfo->State != CHRMOTION_STATE_DEAD &&
				chrOtherPlayer[cnt].RendSucess)
			{

				x = chrOtherPlayer[cnt].pX;
				y = chrOtherPlayer[cnt].pY + 48 * fONE;
				z = chrOtherPlayer[cnt].pZ;

				if(sPartyPosion.WParam) 	StartEffect(x, y, z, EFFECT_POTION1);
				if(sPartyPosion.LParam) 	StartEffect(x, y, z, EFFECT_POTION2);
				if(sPartyPosion.SParam) 	StartEffect(x, y, z, EFFECT_POTION3);
			}
		}


	}

	switch(sPartyPosion.code)
	{
	case OpCode::OPCODE_HEALING:

		if(lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_DEAD)
		{
			CheckCharForm();
			if(sPartyPosion.WParam)
			{
				sinSetLife(sinGetLife() + sPartyPosion.WParam);
			}
			ResetEnergyGraph(0);
			ReformCharForm();
		}
		break;

	case OpCode::OPCODE_GRAND_HEALING:

		if(sPartyPosion.EParam == lpCurPlayer->dwObjectSerial)
		{
			lpChar = lpCurPlayer;
		}
		else
			lpChar = FindAutoPlayer(sPartyPosion.EParam);

		if(!lpChar) break;

		ddist = sPartyPosion.SParam*sPartyPosion.SParam;

		x = (lpCurPlayer->pX - lpChar->pX) >> FLOATNS;
		y = (lpCurPlayer->pY - lpChar->pY) >> FLOATNS;
		z = (lpCurPlayer->pZ - lpChar->pZ) >> FLOATNS;
		dist = x*x + y*y + z*z;
		if(dist < ddist && lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_DEAD)
		{

			if(sPartyPosion.LParam)
			{
				CheckCharForm();
				sinSetLife(sinGetLife() + sPartyPosion.LParam);
				ResetEnergyGraph(0);
				ReformCharForm();
			}

			if(lpChar != lpCurPlayer)
				sinSkillEffect_Great_Healing_Party(lpCurPlayer);
		}



		for(cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
		{
			if(chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].dwObjectSerial && lpChar != &chrOtherPlayer[cnt] &&
				chrOtherPlayer[cnt].PartyFlag && chrOtherPlayer[cnt].MotionInfo->State != CHRMOTION_STATE_DEAD)
			{

				x = (chrOtherPlayer[cnt].pX - lpChar->pX) >> FLOATNS;
				y = (chrOtherPlayer[cnt].pY - lpChar->pY) >> FLOATNS;
				z = (chrOtherPlayer[cnt].pZ - lpChar->pZ) >> FLOATNS;
				dist = x*x + y*y + z*z;

				if(dist < ddist)
				{
					sinSkillEffect_Great_Healing_Party(&chrOtherPlayer[cnt]);
				}
			}
		}
		break;

	case OpCode::OPCODE_VAMPRIC_CUSPID:
		if(lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_DEAD)
		{
			CheckCharForm();
			if(sPartyPosion.WParam)
			{
				sinSetLife(sinGetLife() + sPartyPosion.WParam);
			}
			ResetEnergyGraph(0);
			ReformCharForm();
		}
		break;


	case OpCode::OPCODE_VAMPRIC_CUSPID_EX:
		if(lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_DEAD)
		{
			CheckCharForm();
			if(sPartyPosion.WParam)
			{
				sinSetLife(sinGetLife() + sPartyPosion.WParam);
			}
			ResetEnergyGraph(0);
			ReformCharForm();
		}
		break;

	case OpCode::OPCODE_MANA_RECHARGING:
		if(lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_DEAD)
		{
			CheckCharForm();
			if(sPartyPosion.WParam)
			{
				sinSetMana(sinGetMana() + sPartyPosion.WParam);
			}
			ResetEnergyGraph(1);
			ReformCharForm();
		}
		break;

	}




	sPartyPosion.code = 0;
	dwPartyPosionTime = 0;


	return TRUE;
}


int SetPartyPosion(smTRANS_COMMAND *lpTransCommand)
{
	if(dwPartyPosionTime)
	{

		LaunchPartyPostion();
	}

	dwPartyPosionTime = dwPlayTime + 1000;
	memcpy(&sPartyPosion, lpTransCommand, sizeof(smTRANS_COMMAND));

	return TRUE;
}



char szPlayerCode[32];
int CharacterJob = 0;

char *szAnimShieldEffectFile[] = {
	"Weapons\\test1.tga",
	"Weapons\\test2.tga",
	"Weapons\\test3.tga",
	"Weapons\\test2.tga"
};

char *szBangImage = "weapons\\bang2.bmp";
char *szClowImage = "weapons\\crown.tga";

extern	char *szNpcInfoPath;

DWORD	dwSoD_ResultTime = 0;

sBILLING_INFO	*sBiInfo = 0;

int InitPat3D()
{
	int cnt, cnt2, size;
	POINT3D Posi, Angle;


	DWORD nsize = 62;

	if(!sBiInfo)
	{
		sBiInfo = new sBILLING_INFO;
		ZeroMemory(sBiInfo, sizeof(sBILLING_INFO));
	}

	if(PlayerName[0] == 0)
		GetComputerName(PlayerName, &nsize);

	InterfaceParty.chatbuild_INIfiles();


	rsRecorder.dwRecordTime = 0;
	rsRecorder.dwNextRecordTime = GetCurrentTime() + 10 * 60 * 1000;



#ifdef	_LANGUAGE_THAI		
	cInterFace.sInterFlags.CameraAutoFlag = 0;
#else	
	cInterFace.sInterFlags.CameraAutoFlag = 2;
#endif	

	cInterFace.sInterFlags.MapOnFlag = TRUE;
	cInterFace.sInterFlags.RunFlag = TRUE;

	if(((GetCurrentTime() >> 4) & 1) == 0) strcpy_s(szPlayerCode, "p");
	else strcpy_s(szPlayerCode, "f");



	CreatePatIceFoot(0, 6 * fONE, 6 * fONE);
	CreatePatIceFoot(1, 6 * fONE, 6 * fONE);



	CreatePatShadow(0, 12 * fONE, 10 * fONE);
	CreatePatShadow(1, 17 * fONE, 14 * fONE);
	CreatePatShadow2(2, 26 * fONE, 20 * fONE);
	CreatePatShadow2(3, 38 * fONE, 30 * fONE);




	Posi.x = smConfig.Posi_Player.x;
	Posi.z = smConfig.Posi_Player.y;
	Posi.y = 0;
	Angle.x = 0;
	Angle.y = 0;
	Angle.z = 0;


	invPlayerArmor = 0;



	SetCharFileList("char\\tmABCD\\a001.ini");



#ifdef _W_SERVER

	SetNpcFileList(szNpcInfoPath);
#endif


	LoadOftenArmor();

	LoadOftenFace();

	LoadOftenItem();

	LoadOftenNpc();

	LoadOftenModels();


	sinChar = &lpCurPlayer->smCharInfo;

	CheckCharForm();


	if(CharacterName1[0])
	{
		cnt = NewCharInfo.Dexterity + NewCharInfo.Health + NewCharInfo.Spirit + NewCharInfo.Strength + NewCharInfo.Talent;

		lpCurPlayer->smCharInfo.JOB_CODE = NewCharInfo.JobCode;

		if(cnt < 103)
		{

			lpCurPlayer->smCharInfo.Dexterity = NewCharInfo.Dexterity;
			lpCurPlayer->smCharInfo.Health = NewCharInfo.Health;
			lpCurPlayer->smCharInfo.Spirit = NewCharInfo.Spirit;
			lpCurPlayer->smCharInfo.Strength = NewCharInfo.Strength;
			lpCurPlayer->smCharInfo.Talent = NewCharInfo.Talent;
		}
		else
		{
			lpCurPlayer->smCharInfo.Dexterity = 1;
			lpCurPlayer->smCharInfo.Health = 8;
			lpCurPlayer->smCharInfo.Spirit = 1;
			lpCurPlayer->smCharInfo.Strength = 8;
			lpCurPlayer->smCharInfo.Talent = 1;
			lpCurPlayer->smCharInfo.StatePoint = 0;
		}
	}


	if(CharacterName1[0])
	{
		SetLoadPattern(lpCurPlayer, CharacterName1, CharacterName2, &Posi, &Angle);

		cnt2 = 0;
		for(cnt = 0; cnt < (int)lpCurPlayer->smMotionInfo->MotionCount; cnt++)
		{
			if(lpCurPlayer->smMotionInfo->MotionInfo[cnt].State == CHRMOTION_STATE_DEAD)
			{

				size = lpCurPlayer->smMotionInfo->MotionInfo[cnt].EndFrame - lpCurPlayer->smMotionInfo->MotionInfo[cnt].StartFrame;
				if(size > 8) cnt2++;
			}

			if(lpCurPlayer->smMotionInfo->MotionInfo[cnt].State == CHRMOTION_STATE_ATTACK)
			{
				size = lpCurPlayer->smMotionInfo->MotionInfo[cnt].EndFrame - lpCurPlayer->smMotionInfo->MotionInfo[cnt].StartFrame;

				if(size < 40 && smConfig.getSecurity() < AccountTypes::SEC_MODERATOR)
				{
					DisconnectFlag = GetCurrentTime();
					quit = TRUE;
				}
			}
		}

		if(cnt2 == 0 && smConfig.getSecurity() < AccountTypes::SEC_MODERATOR)
		{

			DisconnectFlag = GetCurrentTime();
			quit = TRUE;
		}
	}
	else
		SetLoadPattern(lpCurPlayer, smConfig.szFile_Player, 0, &Posi, &Angle);


	lpCurPlayer->smCharInfo.Level = 1;

	lpCurPlayer->smCharInfo.Attack_Damage[0] = 5;
	lpCurPlayer->smCharInfo.Attack_Damage[1] = 10;

	strcpy_s(lpCurPlayer->smCharInfo.szName, PlayerName);
	lpCurPlayer->smCharInfo.State = smCHAR_STATE_USER;
	lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_RESTART);

	lpCurPlayer->smCharInfo.SizeLevel = 1;
	lpCurPlayer->PatSizeLevel = 1;

	lpCurPlayer->smCharInfo.Attack_Rating = 100;
	lpCurPlayer->smCharInfo.Next_Exp = 1000;

	lpCurPlayer->smMonsterInfo.dwAutoCharCode = 0;

	lpCurPlayer->smCharInfo.Life[0] = 1000;
	lpCurPlayer->smCharInfo.Life[1] = 1000;

	lpCurPlayer->MoveMode = TRUE;
	lpCurPlayer->MoveCnt = 0;

	PkMode = 0;

	ReformCharForm();



	lpCurPlayer->OnStageField = -1;
	if(smGameStage[0])
	{
		cnt = smGameStage[0]->GetFloorHeight(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, lpCurPlayer->Pattern->SizeHeight);
		lpCurPlayer->OnStageField = 0;
	}
	if(cnt == CLIP_OUT && smGameStage[1])
	{
		lpCurPlayer->OnStageField = 1;
	}


	for(cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		chrOtherPlayer[cnt].Init();
	}


	smMATERIAL *mat;

	smASE_SetPhysique(0);
	PatArrow = smASE_Read("weapons\\arrow.ase");
	PatEffectShield = smASE_Read("weapons\\Test8.ASE");
	PatSparkShield = smASE_Read("weapons\\Mc3_sparkShield.ASE");
	PatDivineShield = smASE_Read("weapons\\Nt3_DivineI.ASE");
	PatGodlyShield = smASE_Read("weapons\\Godly_Shield.ASE");
	PatCrown = smASE_Read("weapons\\Crown.ASE");




	if(PatEffectShield)
	{
		PatEffectShield->Frame = 0;

		mat = PatEffectShield->smMaterialGroup->FindMaterialFromTextureName(szBangImage);
		if(mat)
		{
			mat->BlendType = SMMAT_BLEND_ADDCOLOR;
			mat->SelfIllum = 1;


		}
	}

	if(PatCrown)
	{
		PatCrown->Frame = 0;

		mat = PatCrown->smMaterialGroup->FindMaterialFromTextureName(szClowImage);

		if(mat)
		{
			mat->BlendType = SMMAT_BLEND_ADDCOLOR;
			mat->SelfIllum = 1;
		}
	}



	smASE_SetPhysique(0);


	MatEachBox = CreateTextureMaterial("image\\cw.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);


	MatEachMenuBox = CreateTextureMaterial("image\\cw-1.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	MatEachTradeButton[0] = CreateTextureMaterial("image\\CW-trade0.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	MatEachTradeButton[1] = CreateTextureMaterial("image\\CW-trade1.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);

#ifdef	_NEW_PARTRADE


	lpDDS_ParTradeButton[0][0] = LoadDibSurfaceOffscreen("image\\party\\icon-c5_.bmp");
	lpDDS_ParTradeButton[0][1] = LoadDibSurfaceOffscreen("image\\party\\icon-c5.bmp");

	lpDDS_ParTradeButton[1][0] = LoadDibSurfaceOffscreen("image\\party\\icon-c1_.bmp");
	lpDDS_ParTradeButton[1][1] = LoadDibSurfaceOffscreen("image\\party\\icon-c1.bmp");

	lpDDS_ParTradeButton[2][0] = LoadDibSurfaceOffscreen("image\\party\\icon-c2_.bmp");
	lpDDS_ParTradeButton[2][1] = LoadDibSurfaceOffscreen("image\\party\\icon-c2.bmp");

	lpDDS_ParTradeButton[3][0] = LoadDibSurfaceOffscreen("image\\party\\icon_clan_.bmp");
	lpDDS_ParTradeButton[3][1] = LoadDibSurfaceOffscreen("image\\party\\icon_clan.bmp");


	lpDDS_ParTradeToolTip[0] = LoadDibSurfaceOffscreen("image\\party\\ButtonInfo-c5.bmp");
	lpDDS_ParTradeToolTip[1] = LoadDibSurfaceOffscreen("image\\party\\ButtonInfo-c1.bmp");
	lpDDS_ParTradeToolTip[2] = LoadDibSurfaceOffscreen("image\\party\\ButtonInfo-c0.bmp");
	lpDDS_ParTradeToolTip[3] = LoadDibSurfaceOffscreen("image\\party\\ButtonInfo-c10.bmp");


#endif


	MatEnergyBox[0] = CreateTextureMaterial("image\\Energy_Red.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	MatEnergyBox[1] = CreateTextureMaterial("image\\Energy_Blue.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);


	MatLight[0] = CreateTextureMaterial("image\\glow01.bmp", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ADDCOLOR);
	smMaterial[MatLight[0]].SelfIllum = TRUE;
	MatLight[1] = CreateTextureMaterial("image\\glow02.bmp", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ADDCOLOR);
	smMaterial[MatLight[1]].SelfIllum = TRUE;

	MatMonBroodImage[0] = CreateTextureMaterial("image\\M_Nm.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	MatMonBroodImage[1] = CreateTextureMaterial("image\\M_Mt.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	MatMonBroodImage[2] = CreateTextureMaterial("image\\M_Un.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	MatMonBroodImage[3] = CreateTextureMaterial("image\\M_D.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	MatMonBroodImage[4] = CreateTextureMaterial("image\\M_mc.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);


	InitWeatherSystem();


	InitParticle();

	InitDynLight();

	UseEtherCoreCode = 0;

	dwPartyPosionTime = 0;


	InitTimeEffect();

#ifdef	_SET_PROCTECT_MEM2

	cnt = Check_PlaySubReleaseFunc();
	if(cnt)
	{
		SendSetHackUser2(1120, cnt);
	}
#endif

	ResetEnergyGraph(3);
	ResetInvenItemCode();
	ResetInvenMoney();

	CheckDLL_Module();

	ZeroMemory(&rsBlessCastle, sizeof(rsBLESS_CASTLE));

	return TRUE;

}

int ClosePat3D()
{
	int cnt;

	ClosePatterns();



	if(PatArrow)
	{
		delete PatArrow;
		PatArrow = NULL;
	}

	if(PatEffectShield)
	{
		delete PatEffectShield;
		PatEffectShield = NULL;
	}




	for(cnt = 0; cnt < ICE_FOOT_PAT_MAX; cnt++)
	{
		if(PatIceFoot[cnt])
		{
			delete PatIceFoot[cnt];
			PatIceFoot[cnt] = NULL;
		}
	}



	for(cnt = SHADOW_PAT_MAX - 1; cnt >= 0; cnt--)
		if(PatShadow[cnt]) delete PatShadow[cnt];


	if(lpDDS_ParTradeButton[0][0])	lpDDS_ParTradeButton[0][0]->Release();
	if(lpDDS_ParTradeButton[0][1])	lpDDS_ParTradeButton[0][1]->Release();
	if(lpDDS_ParTradeButton[1][0])	lpDDS_ParTradeButton[1][0]->Release();
	if(lpDDS_ParTradeButton[1][1])	lpDDS_ParTradeButton[1][1]->Release();
	if(lpDDS_ParTradeButton[2][0])	lpDDS_ParTradeButton[2][0]->Release();
	if(lpDDS_ParTradeButton[2][1])	lpDDS_ParTradeButton[2][1]->Release();
	if(lpDDS_ParTradeButton[3][0])	lpDDS_ParTradeButton[3][0]->Release();
	if(lpDDS_ParTradeButton[3][1])	lpDDS_ParTradeButton[3][1]->Release();

	if(lpDDS_ParTradeToolTip[0])	lpDDS_ParTradeToolTip[0]->Release();
	if(lpDDS_ParTradeToolTip[1])	lpDDS_ParTradeToolTip[1]->Release();
	if(lpDDS_ParTradeToolTip[2])	lpDDS_ParTradeToolTip[2]->Release();
	if(lpDDS_ParTradeToolTip[3])	lpDDS_ParTradeToolTip[3]->Release();

	if(sBiInfo) delete sBiInfo;

	return TRUE;
}

int PartCnt = 0;


int		MsTraceCount = 0;
int		MsTraceMode = 0;
RECT	MsSelRect;
POINT	MsSelPos;

int		SelMouseButton = 0;

smCHAR	*lpCharSelPlayer = 0;
smCHAR	*lpCharMsTrace = 0;

scITEM	*lpSelItem = 0;
scITEM	*lpMsTraceItem = 0;

int AttFlag = 0;
int	AttCancel;
int	AttAutoCont = 0;


int TraceAttackPlay()
{
	if(lpCharSelPlayer)
	{
		MsTraceMode = TRUE;
		lpCharMsTrace = lpCharSelPlayer;
		AttFlag = TRUE;
		if(VRKeyBuff[VK_SHIFT] && lpCharSelPlayer->smCharInfo.State == smCHAR_STATE_ENEMY) AttAutoCont = TRUE;
		else AttAutoCont = FALSE;


		if(VRKeyBuff['O'] && smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
			SkillWarriorBetserker(lpCharSelPlayer, 15);

		return TRUE;
	}

	if(lpSelItem)
	{
		MsTraceMode = TRUE;
		lpMsTraceItem = lpSelItem;
		return TRUE;
	}

	return FALSE;

}


int CancelAttack()
{
	SelMouseButton = 0;
	MsTraceMode = FALSE;
	lpCharMsTrace = 0;
	lpMsTraceItem = 0;
	AttFlag = 0;

	return TRUE;
}


int	DamageExp(smCHAR *lpChar, int AttackDamage)
{
	int AttackResult;







	if(AttackDamage && lpChar->smCharInfo.State == smCHAR_STATE_ENEMY &&
		lpChar->smCharInfo.Brood != smCHAR_MONSTER_USER && lpChar->smCharInfo.Life[0] > 0)
	{

		AttackResult = (AttackDamage << 8) / lpChar->smCharInfo.Life[1];
		if(AttackResult > 256) AttackResult = 256;
		AttackResult = (lpChar->smCharInfo.Exp * AttackResult) >> 8;
		AttackResult /= 10;
		if(AttackResult <= 0) AttackResult = 1;
		lpCurPlayer->AttackExp = AttackResult;
	}

	return TRUE;
}

#define AUTO_DEAD_COUNT		(70*60*8)
int AutoDeathCounter = 0;
int FixedWidth = 200;
DWORD	dwClassDelayTime = 0;



int PlayPat3D()
{


	int cnt;
	int attack;
	int	attack_UserMonster;
	int	attack_RegState;

	int wx, wz, x, z;
	int	attackMode;
	sSKILL *lpAttackSkill;
	smWINSOCK *lpsmSock;
	int	skFlag;

#ifdef	_WINMODE_DEBUG

	if(SkipNextField)
	{
		if(SkipNextField == 1)
		{
			WarpNextField(&wx, &wz);
			lpCurPlayer->SetPosi(wx, 0, wz, 0, 0, 0);
			SkipNextField = 0;
			TraceCameraPosi.x = lpCurPlayer->pX;
			TraceCameraPosi.y = lpCurPlayer->pY;
			TraceCameraPosi.z = lpCurPlayer->pZ;
			TraceTargetPosi.x = lpCurPlayer->pX;
			TraceTargetPosi.y = lpCurPlayer->pY;
			TraceTargetPosi.z = lpCurPlayer->pZ;
		}
		else
		{

			WarpCustomField(&wx, &wz);
			lpCurPlayer->SetPosi(wx, 0, wz, 0, 0, 0);
			SkipNextField = 0;
			TraceCameraPosi.x = lpCurPlayer->pX;
			TraceCameraPosi.y = lpCurPlayer->pY;
			TraceCameraPosi.z = lpCurPlayer->pZ;
			TraceTargetPosi.x = lpCurPlayer->pX;
			TraceTargetPosi.y = lpCurPlayer->pY;
			TraceTargetPosi.z = lpCurPlayer->pZ;

		}
	}

#endif





	lpCurPlayer->Main();

	EachPlayerMain();


	AutoDeathCounter++;

	if (PkMode > 0) PkMode--;

#ifdef _LANGUAGE_BRAZIL
	if (VRKeyBuff[VK_CONTROL]) PkMode = FALSE;
#else
	if (VRKeyBuff[VK_CONTROL]) PkMode = TRUE;   // SO MUDAR PARA TRUE 
#endif

	else PkMode = FALSE;



	if(lpCurPlayer->PlayStunCount)
	{
		if(MsTraceMode)
		{
			CancelAttack();
			lpCurPlayer->MoveFlag = 0;
			MouseButton[0] = 0;
			MouseButton[1] = 0;
			MouseButton[2] = 0;
		}
		if(lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_WALK || lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_RUN)
		{
			lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_STAND);
			CancelAttack();
			lpCurPlayer->MoveFlag = 0;
			MouseButton[0] = 0;
			MouseButton[1] = 0;
			MouseButton[2] = 0;
		}
		lpCurPlayer->dwNextMotionCode = 0;
		lpCurPlayer->MotionLoop = 0;
	}


	if(MsTraceMode && lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_ATTACK && lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_EAT &&
		lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_SKILL)
	{

		attackMode = FALSE;
		AttCancel = FALSE;
		attack_UserMonster = FALSE;

		CheckPlaySubFunc2();

		if((MsTraceCount & 0x1F) == 0)
		{


			lpCurPlayer->MoveFlag = TRUE;
			lpCurPlayer->Angle.y = GetMouseSelAngle();
		}

		int AttackRange = 0;
		int	AttackResult = 0;

		lpAttackSkill = 0;

		switch(SelMouseButton)
		{
		case 1:
			if(sinSkill.pLeftSkill && sinSkill.pLeftSkill->CODE != SKILL_NORMAL_ATTACK)
				lpAttackSkill = sinSkill.pLeftSkill;
			break;
		case 2:
			if(sinSkill.pRightSkill && sinSkill.pRightSkill->CODE != SKILL_NORMAL_ATTACK)
				lpAttackSkill = sinSkill.pRightSkill;
			break;
		}


		if(lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_VILLAGE)
			lpAttackSkill = 0;

		if(lpCharMsTrace)
		{
			if(lpCharMsTrace->smCharInfo.Life[0] <= 0 ||
				(lpCharMsTrace->dwLastTransTime + DISPLAY_TRANS_TIME_OVER) < dwPlayTime ||
				cTrade.OpenFlag)
			{

				CancelAttack();
			}
			else
			{

				if(!MouseButton[0] && !MouseButton[1]) AttFlag = 0;

				if(lpCurPlayer->smCharInfo.State == smCHAR_STATE_ENEMY)
				{

					attackMode = TRUE;
				}
				else
				{
					if(PkMode)
						attackMode = TRUE;

				}

				if(lpCharMsTrace->smCharInfo.dwCharSoundCode == snCHAR_SOUND_KELVEZU)
				{
					AttackRange = 130 * fONE;
				}
				else
					AttackRange = 50 * fONE;

				if(lpCurPlayer->dwActionItemCode)
				{
					AttackRange += lpCurPlayer->AttackToolRange;
				}


				if(lpCurPlayer->ShootingMode && lpCharMsTrace->smCharInfo.State)
				{
					if(lpCharMsTrace->smCharInfo.State != smCHAR_STATE_USER || attackMode)
						AttackRange = lpCurPlayer->smCharInfo.Shooting_Range*fONE;




				}

				if(lpCharMsTrace->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_TOWER_B)
					AttackRange += 40 * fONE;

				attack = lpCharMsTrace->smCharInfo.State;

				if(lpCharMsTrace->smCharInfo.State == smCHAR_STATE_USER)
				{
					if(!attackMode ||
						(lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_VILLAGE))
						attack = 0;
				}

				if(lpCharMsTrace->smCharInfo.State == smCHAR_STATE_ENEMY && lpCharMsTrace->smCharInfo.Brood == smCHAR_MONSTER_USER)
				{
					if(!PkMode)
					{
						attack_UserMonster = TRUE;;
						attack = 0;
					}
				}

				if(lpAttackSkill)
				{
					if(lpAttackSkill->CODE == SKILL_HEALING || lpAttackSkill->CODE == SKILL_ENCHANT_WEAPON ||
						lpAttackSkill->CODE == SKILL_VIRTUAL_LIFE || lpAttackSkill->CODE == SKILL_TRIUMPH_OF_VALHALLA)
					{
						if(attack_UserMonster && lpAttackSkill->CODE == SKILL_HEALING)
							attack_UserMonster = 0;

						skFlag = 1;
					}
					else
						skFlag = 0;

					if((lpCharMsTrace->smCharInfo.State == smCHAR_STATE_ENEMY && !attack_UserMonster) ||
						(PkMode && lpCharMsTrace->smCharInfo.State == smCHAR_STATE_USER) || skFlag)
					{


						cnt = GetSkillDistRange(lpAttackSkill, AttackRange, attack);
						if(cnt)
							AttackRange = cnt;

						attack = 0;
					}
				}

				if(!lpCurPlayer->ShootingFlag &&
					lpCurPlayer->PlayAttackFromPosi(
						lpCharMsTrace->pX,
						lpCharMsTrace->pY,
						lpCharMsTrace->pZ,
						AttackRange, attack) == TRUE &&
					lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_EAT)
				{


					LastAttackDamage = 0;
					AutoMouse_Attack_Count++;

					if(lpCharMsTrace->smCharInfo.State == smCHAR_STATE_USER)
					{
						if(lpCharMsTrace->dwTradeMsgCode)
						{
							Send_ShowMyShopItem(lpCharMsTrace);
						}
						else
						{
							EachTradeButton = 1;

#ifdef  __CLANSUBCHIP__
							if((cldata.myPosition == 101 || cldata.myPosition == 104) && !lpCharMsTrace->smCharInfo.ClassClan)
#else
							if(cldata.myPosition == 101 && !lpCharMsTrace->smCharInfo.ClassClan)
#endif
								EachTradeButtonMode = TRUE;
							else
								EachTradeButtonMode = FALSE;
						}

					}
					else
					{
						EachTradeButton = 0;
					}

					if(!lpCharMsTrace->smCharInfo.State)
					{
						OpenEachPlayer(lpCharMsTrace);
						DispEachMode = TRUE;
					}

					lpCurPlayer->chrAttackTarget = lpCharMsTrace;
					lpCurPlayer->AttackExp = 0;

					lpCurPlayer->AttackCritcal = FALSE;


					if(!attack_UserMonster &&
						(lpCharMsTrace->smCharInfo.State != smCHAR_STATE_USER ||
						(lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State != FIELD_STATE_VILLAGE)))
					{

						AttackResult = TRUE;


						if(!PlaySkillAttack(lpAttackSkill, lpCharMsTrace))
						{

							if(attack || lpCharMsTrace->smCharInfo.State != smCHAR_STATE_USER)
							{

								if(lpCurPlayer->ShootingMode && lpCharMsTrace->smCharInfo.State != smCHAR_STATE_NPC)
								{
									if(lpCurPlayer->CheckShootingTest(lpCharMsTrace) == TRUE)
									{

										AttackResult = dm_SendTransDamage(lpCharMsTrace, 0, 0, 0, 0,
											lpCurPlayer->AttackSkil, TRUE);

									}
									else
									{
										lpCurPlayer->AttackCritcal = -1;
										lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_STAND);
									}
								}
								else
								{
									attack_RegState = 0;

									if(lpCharMsTrace->smCharInfo.State == smCHAR_STATE_NPC)
									{
										if(sinQuest_ChangeJob2.CODE)
										{

											attack_RegState = (sinQuest_ChangeJob2.CODE << 16);
											if(sinQuest_ChangeJob2.CODE == SIN_QUEST_CODE_CHANGEJOB2_NPC_M ||
												sinQuest_ChangeJob2.CODE == SIN_QUEST_CODE_CHANGEJOB2_NPC_D)
											{

												if(!cInvenTory.SearchItemCode(sinMA1 | sin01) &&
													!cInvenTory.SearchItemCode(sinQT1 | sin04) &&
													!cInvenTory.SearchItemCode(sinQT1 | sin05))
													attack_RegState |= 1;

											}
										}


										if(dwClassDelayTime < dwPlayTime)
										{
											if(lpCharMsTrace->smCharInfo.wPlayClass[0])
											{
												switch(lpCharMsTrace->smCharInfo.wPlayClass[0])
												{

												case 1001:
													if(lpCurPlayer->smCharInfo.JOB_CODE <= 4 || lpCurPlayer->smCharInfo.JOB_CODE == 9)
														sinCheckLevelQuest30();
													break;
												case 1002:
													if(lpCurPlayer->smCharInfo.JOB_CODE > 4 && lpCurPlayer->smCharInfo.JOB_CODE != 9)
														sinCheckLevelQuest30();
													break;
												case 1003:
													if(lpCurPlayer->smCharInfo.JOB_CODE <= 4 || lpCurPlayer->smCharInfo.JOB_CODE == 9)
														sinCheckLevelQuest55();
													break;
												case 1004:
													if(lpCurPlayer->smCharInfo.JOB_CODE > 4 && lpCurPlayer->smCharInfo.JOB_CODE != 9)
														sinCheckLevelQuest55_2();
													break;
												case 1005:
													sinCheckLevelQuest70();
													sinCheckLevelQuest80();
													sinCheckLevelQuest85();
													break;
												case 1006:
													sinCheckLevelQuest90();
													break;

												case 1010:
													sinCheckLevelQuest80_2(0);
													break;
												case 1011:
													sinCheckLevelQuest80_2(1);
													break;
												case 1012:
													sinCheckLevelQuest80_2(0);
													sinCheckLevelQuest90_2(0);
													break;
												case 1013:
													sinCheckLevelQuest90_2(1);
													chaQuest.showFuryQuest();
													break;
												
												}


												HaCheckQuestNpc(lpCharMsTrace->smCharInfo.wPlayClass[0]);

												dwClassDelayTime = dwPlayTime + 1000 * 5;
											}
										}


									}


									AttackResult = dm_SendTransDamage(lpCharMsTrace, 0, 0, 0, attack_RegState,
										lpCurPlayer->AttackSkil, TRUE);

								}


								if((AttackResult && lpCurPlayer->WeaponEffect == (sITEMINFO_LIGHTING + 1) || AttackResult && lpCurPlayer->WeaponEffect == (sITEMINFO_ICE + 1) || AttackResult && lpCurPlayer->WeaponEffect == (sITEMINFO_FIRE + 1))
									&& lpCurPlayer->EnchantEffect_Point > 0 && lpCurPlayer->EnchantEffect_Point <= 10)
								{


									if(lpCurPlayer->AttackCritcal >= 0)
									{

										dm_SelectRange(lpCharMsTrace->pX, lpCharMsTrace->pY, lpCharMsTrace->pZ, 50, TRUE);

										dm_SendRangeDamage(lpCharMsTrace->pX, lpCharMsTrace->pY, lpCharMsTrace->pZ, 0, 0, 0, 0, 0,
											(SKILL_PLAY_ENCHANT_WEAPON | (lpCurPlayer->EnchantEffect_Point << 8)));
									}
								}
							}
							if(!lpAttackSkill && !AttackResult)
							{
								lpCurPlayer->AttackCritcal = -1;
							}
							else
							{

								DamageExp(lpCharMsTrace, AttackResult);
							}
						}
					}


					if(!AttackResult)	lpCurPlayer->AttackCritcal = -1;

					if(!AttCancel)
					{

						lpCurPlayer->MoveFlag = FALSE;
						lpCurPlayer->CriticalLog = lpCurPlayer->AttackCritcal;

						if(lpCharMsTrace && (lpCharMsTrace->smCharInfo.State == smCHAR_STATE_NPC || lpCharMsTrace->dwTradeMsgCode))
						{
							MouseButton[0] = 0;
							MouseButton[1] = 0;
							AttAutoCont = FALSE;
						}

						if(!AttFlag && !AttAutoCont)
						{
							MsTraceMode = 0;
							lpCharMsTrace = 0;
						}
					}
				}
				else
				{
					if(!lpCharMsTrace->Flag || lpCharMsTrace->MotionInfo->State == CHRMOTION_STATE_DEAD)
					{
						lpCharMsTrace = NULL;
						MsTraceMode = 0;
						lpCurPlayer->MoveFlag = FALSE;
						AttAutoCont = FALSE;
					}
				}
			}
		}

		if(lpMsTraceItem)
		{
			if(lpCurPlayer->PlayAttackFromPosi(
				lpMsTraceItem->pX,
				lpMsTraceItem->pY,
				lpMsTraceItem->pZ,
				8000, FALSE) == TRUE)
			{


				smTRANS_ACITON_ITEM		TransActionItem;
				char	szBuff[64];
				int		len;

				TransActionItem.code = OpCode::OPCODE_PUTITEM;
				TransActionItem.size = sizeof(smTRANS_ACITON_ITEM);

				TransActionItem.x = lpMsTraceItem->pX;
				TransActionItem.y = lpMsTraceItem->pY;
				TransActionItem.z = lpMsTraceItem->pZ;
				TransActionItem.lpStgArea = lpMsTraceItem->lpStgArea;



				if(CheckRecvTrnsItemQue() == TRUE)
				{

					cnt = 0;

					if((lpMsTraceItem->ItemCode&sinITEM_MASK2) == sinCH1)
					{
						switch(lpMsTraceItem->ItemCode)
						{
#ifdef _LANGUAGE_ENGLISH
						case (sinCH1 | sin01):
							if(lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_ATALANTA ||
								lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_ARCHER ||
								lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_PRIESTESS)
							{
								cMessageBox.ShowMessage(MESSAGE_NOT_PICKUP_MALE);
								cnt = 1;
							}
							break;
						case (sinCH1 | sin02):
							if(lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_MECHANICIAN ||
								lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_FIGHTER ||
								lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_PIKEMAN ||
								lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_KNIGHT ||
								lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_MAGICIAN)
							{

								cMessageBox.ShowMessage(MESSAGE_NOT_PICKUP_FEMALE);
								cnt = 1;
							}
							break;

#else
						case (sinCH1 | sin01):
						case (sinCH1 | sin02):

							if(lpCurPlayer->smCharInfo.JOB_CODE != JOBCODE_ATALANTA &&
								lpCurPlayer->smCharInfo.JOB_CODE != JOBCODE_ARCHER &&
								lpCurPlayer->smCharInfo.JOB_CODE != JOBCODE_PRIESTESS &&
								lpCurPlayer->smCharInfo.JOB_CODE != JOBCODE_ASSASSINE)
							{

								cMessageBox.ShowMessage(MESSAGE_NOT_PICKUP_FEMALE);
								cnt = 1;
							}
							break;
#endif
						case (sinCH1 | sin03):
						case (sinCH1 | sin04):

							if(lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_ATALANTA ||
								lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_ARCHER ||
								lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_PRIESTESS ||
								lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_ASSASSINE)
							{

								cMessageBox.ShowMessage(MESSAGE_NOT_PICKUP_MALE);
								cnt = 1;

							}
							break;


						}
					}

					if(!cnt)
					{
						if(lpMsTraceItem->ItemCode == (sinGG1 | sin01))
						{
							strcpy_s(szBuff, lpMsTraceItem->szName);
							len = lstrlen(szBuff);
							for(cnt = 0; cnt < len; cnt++)
							{
								if(szBuff[cnt]<'0' || szBuff[cnt]>'9')
								{
									szBuff[cnt] = 0;
									break;
								}
							}
							cnt = atoi(szBuff);
							if(cInvenTory.CheckMoneyLimit(cnt) == TRUE)
							{
								lpsmSock = GetServerSock(lpMsTraceItem->ServerCode);
								if(lpsmSock)
								{
									lpsmSock->Send((char *)&TransActionItem, TransActionItem.size, TRUE);
								}
							}
						}
						else
						{
							lpsmSock = GetServerSock(lpMsTraceItem->ServerCode);
							if(lpsmSock)
							{
								lpsmSock->Send((char *)&TransActionItem, TransActionItem.size, TRUE);
							}
						}
					}
				}

				MsTraceMode = 0;
				lpMsTraceItem = NULL;
				lpCurPlayer->MoveFlag = FALSE;
				MouseButton[0] = 0;
			}
			else
			{
				if(!lpMsTraceItem->Flag)
				{
					lpMsTraceItem = NULL;
					MsTraceMode = 0;
					lpCurPlayer->MoveFlag = FALSE;
				}
			}
		}


	}
	MsTraceCount++;

	for(cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if(chrOtherPlayer[cnt].Flag)
		{
			chrOtherPlayer[cnt].Main();
			if(chrOtherPlayer[cnt].dwTarget)
			{
				if(lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_DAMAGE &&
					chrOtherPlayer[cnt].MotionInfo->State == CHRMOTION_STATE_ATTACK)

					lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_DAMAGE);
			}
		}
	}


#ifdef _WINMODE_DEBUG



	if(smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR && VRKeyBuff[VK_SHIFT] && !VRKeyBuff[VK_CONTROL])
	{

		if(VRKeyBuff[VK_F4])
		{
			SetNextPlayerPattern();
			VRKeyBuff[VK_F4] = 0;
		}
		if(VRKeyBuff[VK_F3])
		{
			SetNextNpcPattern();
			VRKeyBuff[VK_F3] = 0;
		}
	}
#endif




	MainFieldMap();


	PlayParticle();

	DynLightMain();

	BGMain();


	BGM_Main();


	SodScoreMain();


	PlayCounter++;

	FieldMain(lpCurPlayer->pX, 0, lpCurPlayer->pZ);


	int fldSky, fflag;

	int	RainTime = 0x200;
	int	RainLength = 60 * 7;
	int	BackSel = 0;

	fldSky = -1;
	fflag = 0;

	if((PlayCounter & 0xFF) == 0 && lpCurPlayer->dwObjectSerial)
	{




		if(dwSoD_ResultTime < dwPlayTime)
		{

			dwSoD_ResultTime = dwPlayTime + 12000;
			if(cSinHelp.GetSodRankBoxState() == TRUE)
			{
				SendCommand_AreaServer(OpCode::OPCODE_SOD_RESULT2, 0, 0, 0, 0);
			}
		}

		if(cldata.myPosition)
		{
			if(lpCurPlayer->smCharInfo.ClassClan != cldata.intClanMark)
			{
#ifdef  __CLANSUBCHIP__				
				if(cldata.myPosition == 100 || cldata.myPosition == 101 || cldata.myPosition == 104)
				{
#else
				if(cldata.myPosition == 100 || cldata.myPosition == 101)
				{
#endif

					lpCurPlayer->smCharInfo.ClassClan = cldata.intClanMark;
					lpCurPlayer->dwClanManageBit = cldata.CNFlag;
					lpCurPlayer->smCharInfo.bUpdateInfo[0]++;
					SendUpdateClanInfo();







				}
				else
				{
					cldata.intClanMark = 0;
					lpCurPlayer->smCharInfo.ClassClan = 0;
					lpCurPlayer->smCharInfo.bUpdateInfo[0]++;

					SendUpdateClanInfo();
				}
			}
		}


		if(lpCurPlayer->smCharInfo.wPlayerKilling[0] > 0)
		{
			lpCurPlayer->smCharInfo.wPlayerKilling[0]--;
			if(lpCurPlayer->smCharInfo.wPlayerKilling[0] == 0)
			{


				lpCurPlayer->MoveFlag = FALSE;
				WarpStartField(&x, &z);
				lpCurPlayer->SetPosi(x, 0, z, 0, 0, 0);
				TraceCameraPosi.x = lpCurPlayer->pX;
				TraceCameraPosi.y = lpCurPlayer->pY;
				TraceCameraPosi.z = lpCurPlayer->pZ;
				TraceTargetPosi.x = lpCurPlayer->pX;
				TraceTargetPosi.y = lpCurPlayer->pY;
				TraceTargetPosi.z = lpCurPlayer->pZ;
				lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_RESTART);
				StartEffect(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, EFFECT_GAME_START1);
				SetDynLight(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 100, 100, 100, 0, 200);
				CharPlaySound(lpCurPlayer);


				lpCurPlayer->OnStageField = -1;
				if(smGameStage[0])
				{
					cnt = smGameStage[0]->GetFloorHeight(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, lpCurPlayer->Pattern->SizeHeight);
					lpCurPlayer->OnStageField = 0;
				}
				if(cnt == CLIP_OUT && smGameStage[1])
				{
					lpCurPlayer->OnStageField = 1;
				}
			}
		}


		if(WeatherMode == 0)
		{
			if(dwGameHour < GAME_HOUR_DAY || dwGameHour >= GAME_HOUR_NIGHT)
			{
				BackSel = 2;
			}
			else
			{
				if(dwGameHour >= GAME_HOUR_DAY && dwGameHour < GAME_HOUR_GLOW)
					BackSel = 0;
				else
					BackSel = 1;
			}
		}


		if(lpCurPlayer->OnStageField >= 0)
		{

			if(StageField[lpCurPlayer->OnStageField]->FieldCode == rsSOD_FIELD)
			{

				cnt = rsGetSoD_AreaCode(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
				switch(cnt)
				{
				case 0:
				case 1:
				case 2:
				case 3:
					fldSky = FIELD_BACKIMAGE_SODNONE;
					break;

				case 4:
					fldSky = FIELD_BACKIMAGE_SODSUN;
					break;
				case 5:
					fldSky = FIELD_BACKIMAGE_SODMOON;
					break;
				case 6:
					fldSky = FIELD_BACKIMAGE_SODSKY;
					break;
				}
				if(cnt == 2)
					esPlayEffectBgm(4);
				else
					esPlayEffectBgm(3);

				if(fldSky >= 0) ChangeSky(fldSky);
			}
			else if(StageField[lpCurPlayer->OnStageField]->FieldCode == BabelPlayField && dwBabelPlayTime > dwPlayTime)
			{

				ChangeSky(FIELD_BACKIMAGE_IRONBOSS);
				esPlayEffectBgm(11);
			}
			else
			{
				fldSky = StageField[lpCurPlayer->OnStageField]->BackImageCode[BackSel];

				if(!WeatherMode && fldSky >= 0) ChangeSky(fldSky);

				if(WeatherMode == 0)
				{
					switch(StageField[lpCurPlayer->OnStageField]->State)
					{

					case FIELD_STATE_RUIN:
						esPlayEffectBgm(3);
						break;

					case FIELD_STATE_DESERT:
						esPlayEffectBgm(4);
						break;

					case FIELD_STATE_DUNGEON:
						if(StageField[lpCurPlayer->OnStageField]->FieldCode <= 16 ||
							StageField[lpCurPlayer->OnStageField]->FieldCode == 32)
						{
							esPlayEffectBgm(5);
							break;
						}
						if(StageField[lpCurPlayer->OnStageField]->FieldCode <= 23)
						{
							esPlayEffectBgm(6);
							break;
						}
						if(StageField[lpCurPlayer->OnStageField]->FieldCode <= 25)
						{
							esPlayEffectBgm(7);
							break;
						}
						if(StageField[lpCurPlayer->OnStageField]->FieldCode <= 26)
						{
							esPlayEffectBgm(8);
							break;
						}
						break;


					case FIELD_STATE_FOREST:
						if(dwGameHour < GAME_HOUR_DAY || dwGameHour >= GAME_HOUR_DARKNESS)
						{
							esPlayEffectBgm(2);
						}
						else
						{
							esPlayEffectBgm(1);
						}
						break;

					case FIELD_STATE_VILLAGE:
						esPlayEffectBgm(0);
						break;

					case FIELD_STATE_ROOM:
						esPlayEffectBgm(-1);
						break;

					case FIELD_STATE_IRON:
						esPlayEffectBgm(9);
						break;

					case FIELD_STATE_ICE:
						esPlayEffectBgm(12);
						break;

					}
				}
				else
					esPlayEffectBgm(-1);

				if(StageField[lpCurPlayer->OnStageField]->BackMusicCode)
					ChangeBGM(StageField[lpCurPlayer->OnStageField]->BackMusicCode);
			}

		}
	}

	if((PlayCounter & 0x3) == 0)
	{

		if(StageField[lpCurPlayer->OnStageField]->State != FIELD_STATE_ROOM &&
			(dwGameHour < GAME_HOUR_DAY || dwGameHour >= GAME_HOUR_DARKNESS ||
				StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_DUNGEON))
		{
			NightDayTime = 1;
		}
		else
		{
			NightDayTime = 0;
		}

		cnt = DarkLight;
		if(DarkLevel < cnt)
			DarkLevel++;
		if(DarkLevel > cnt)
			DarkLevel--;

		if((PlayCounter & 0x7) == 0)
		{
			if(BackColor_mR < BackColor_R) BackColor_R--;
			if(BackColor_mR > BackColor_R) BackColor_R++;

			if(BackColor_mG < BackColor_G) BackColor_G--;
			if(BackColor_mG > BackColor_G) BackColor_G++;

			if(BackColor_mB < BackColor_B) BackColor_B--;
			if(BackColor_mB > BackColor_B) BackColor_B++;
		}

		if(smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
		{
			if(DarkLevel_Fix)
				DarkLevel = DarkLevel_Fix;
		}

		if((PlayCounter & 0xFF) == 0)
		{
			Ptect_GetAttackCount();

			if((PlayCounter & 0xFFF) == 0)
			{
				if((PlayCounter & 0x3FFF) == 0)
					SendUsingItemListToServer2();
				else
					SendUsingItemListToServer();
			}

			if(lpCurPlayer->smCharInfo.dwEventTime_T)
			{
				if(GetPlayTime_T() > lpCurPlayer->smCharInfo.dwEventTime_T)
				{

					ChangeBigHeadMode(0, 0);
					StartSkill(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, SKILL_UP1);
					SkillPlaySound(SKILL_SOUND_LEARN, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);


					cnt = PlayerArmor;
					PlayerArmor = -1;
					SetPlayerArmor(cnt);

					cInvenTory.IncreViewDamage(0);

					if(RestartPlayCount < 350) RestartPlayCount = 350;
				}
			}


			if(rsRecorder.dwNextRecordTime < dwPlayTime)
			{

				if(GetSaveResult() == TRUE)
				{

					SaveGameData();

				}
			}
			if(rsRecorder.dwRecordTime && (rsRecorder.dwRecordTime + 1000 * 8) < dwPlayTime)
			{
#ifdef _WINMODE_DEBUG
				if(smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR) AddChatBuff("SaveGame TimeOut / Retry SaveGame");
#endif
				RecordFailCount++;

				rsRecorder.dwRecordTime = 0;

				SaveGameData();
			}


			if(!DisconnectFlag && RecordFailCount >= 6)
			{

				SendSetHackUser2(2700, RecordFailCount);
				DisconnectFlag = dwPlayTime;
#ifdef _WINMODE_DEBUG
				if(smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR) AddChatBuff("SaveGame Failed over times");
#endif
			}


			if(lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_FOREST &&
				(dwGameHour < GAME_HOUR_DAY || dwGameHour >= GAME_HOUR_DARKNESS) && (PlayCounter & 0x1FF) == 0)
			{

				if(((dwPlayTime >> 3) & 1) == 0)
				{
					StartEffect(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, EFFECT_BANDI1);
				}
			}
		}


		if(lpCurPlayer->OnStageField >= 0)
		{

			StageField[lpCurPlayer->OnStageField]->PlayAmbient();
		}
		else
		{
			if(ResetLastVolumeDist() > 800)
			{
				esPlayObjectSound2(-1, 0, 0, 0, 0);
			}
		}


	}



	dsMenuCursorPos(&pCursorPos, 4);

	MainInterfaceParty();
	dsMenuCursorPos(&pCursorPos, 0);



	if(lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField])
	{
		StageField[lpCurPlayer->OnStageField]->CheckWarpGate(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
	}

	if(RestartPlayCount > 0) RestartPlayCount--;


	if((PlayCounter & 0xFFF) == 0)
	{


		CheckCracker(NULL);

		CheckCharForm();

		if(!lpCurPlayer->HoSkillCode && !lpCurPlayer->dwDispAppSkill)
		{

			if(!dwRotPlayDelayTime || dwRotPlayDelayTime < dwPlayTime)
			{
				smCHAR	*lpTempChar;
				smCHAR	*lpOldChar;

				lpOldChar = lpCurPlayer;

				lpTempChar = SelectRotPlayer(lpCurPlayer);
				if(lpTempChar)
				{
					lpCurPlayer = lpTempChar;
					sinChar = &lpCurPlayer->smCharInfo;


					for(cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
					{
						if(chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].chrAttackTarget == lpOldChar)
							chrOtherPlayer[cnt].chrAttackTarget = lpCurPlayer;
					}

				}
			}
		}
		else
		{
			dwRotPlayDelayTime = dwPlayTime + 30 * 1000;
		}

		CheckEnergyGraphError();
	}


	TimeEffectMain();

	CheckEnergyGraph();




#ifdef	_SET_PROCTECT_MEM2

	if((PlayCounter & 0x7FF) == 0)
	{

		cnt = Check_PlaySubReleaseFunc();
		if(cnt)
		{
			SendSetHackUser2(1120, cnt);
		}
	}
#endif


	if(dwPartyPosionTime && dwPartyPosionTime < dwPlayTime)
	{

		LaunchPartyPostion();
	}



	if((PlayCounter & 0x1FF) == 0)
	{
		CheckEnergyGraphError();

		if(AutoMouse_StartCheckTime)
		{
			if((AutoMouse_StartCheckTime + 30000) < dwPlayTime)
			{

				if(AutoMouse_Distance > 20000 && AutoMouse_Attack_Count > 20 && AutoMouse_WM_Count > 110 && (AutoMouse_LastCheckTime + 30 * 60 * 1000) < dwPlayTime)
				{
					AutoMouse_LastCheckTime = dwPlayTime;

					SendSetHackUser2(8100, AutoMouse_WM_Count);

					if(smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
					{
						AddChatBuff(">Warning AutoMouse", 0);
					}
				}


				AutoMouse_StartCheckTime = dwPlayTime;
				AutoMouse_WM_Count = 0;
				AutoMouse_Distance = 0;
				AutoMouse_Attack_Count = 0;
			}
		}
		else
		{
			AutoMouse_StartCheckTime = dwPlayTime;
			AutoMouse_WM_Count = 0;
			AutoMouse_Distance = 0;
			AutoMouse_Attack_Count = 0;
		}


	}

	HackTrap_CheckOpenFlag();

#ifdef _TEST_SERVER

	if(smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR && VRKeyBuff[VK_CONTROL] && VRKeyBuff['N'] && sinGetKeyClick('M'))
	{



		if(!ParkPlaying)
			Play_ParkPlayer("mms:
		else
				Stop_ParkPlayer();

	}
#endif

	return TRUE;
	}

extern int BGMatNum[2];
extern int RestoreTexFlag;
extern POINT	pCursorPos;



int GetMouseSelAngle()
{
	int x1, x2, z1, z2;

	if(lpCharMsTrace)
	{
		x1 = lpCurPlayer->pX >> FLOATNS;
		z1 = lpCurPlayer->pZ >> FLOATNS;

		x2 = lpCharMsTrace->pX >> FLOATNS;
		z2 = lpCharMsTrace->pZ >> FLOATNS;

		return GetRadian2D(x1, z1, x2, z2);
	}

	if(lpMsTraceItem)
	{
		x1 = lpCurPlayer->pX >> FLOATNS;
		z1 = lpCurPlayer->pZ >> FLOATNS;

		x2 = lpMsTraceItem->pX >> FLOATNS;
		z2 = lpMsTraceItem->pZ >> FLOATNS;

		return GetRadian2D(x1, z1, x2, z2);
	}

	return -1;
}


int GetCharAngle(smCHAR *lpChar1, smCHAR *lpChar2)
{
	int x1, x2, z1, z2;

	x1 = lpChar1->pX >> FLOATNS;
	z1 = lpChar1->pZ >> FLOATNS;

	x2 = lpChar2->pX >> FLOATNS;
	z2 = lpChar2->pZ >> FLOATNS;

	return GetRadian2D(x1, z1, x2, z2);
}


int testframe = 0;
int	LastRendSucessCount = 0;
int	DispCharLimitMode = 0;

#define	DISP_CHAR_LIMIT			20
#define	DISP_CHAR_LIMIT_MAX		30
#define	DISP_CHAR_NEAR_DIST		( (10*64)*(10*64) )

int DrawPat3D(int x, int y, int z, int ax, int ay, int az)
{



	int cnt;
	int SelZ;
	int sez;
	RECT	rect;
	RECT	SelRect;
	POINT	SelPos;
	RECT	*lpRect;

	smCHAR	*lpSelChar;
	scITEM	*lpItem;
	int		dx, dz;
	int		pow;

	POINT	sPos;
	int		RendSucessCount;
	int		DispFlag;
	int		r, g, b;
	DWORD	dwDispAppSKill;


	dwDispAppSKill = lpCurPlayer->dwDispAppSkill;
	lpCurPlayer->dwDispAppSkill = 0;

	for(cnt = 0; cnt < 10; cnt++)
	{
		if(ContinueSkill[cnt].Flag)
		{
			switch(ContinueSkill[cnt].CODE)
			{
			case SKILL_EXTREME_SHIELD:
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_EXTREME_SHIELD;
				break;

			case SKILL_PHYSICAL_ABSORB:
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_PHYSICAL_ABSORB;
				break;

			case SKILL_AUTOMATION:
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_AUTOMATION;
				break;

			case SKILL_MAXIMIZE:
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_AUTOMATION;
				break;

			case SKILL_CRITICAL_HIT:
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_ANGER;
				break;

			case SKILL_HOLY_BODY:
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_PHYSICAL_ABSORB;
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_HOLY_BODY;
				DispApp_SkillPoint = ContinueSkill[cnt].Point;
				break;

			case SKILL_ZENITH:
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_ANGER;
				break;

			case SKILL_SPARK_SHIELD:
			case SKILL_DIVINE_INHALATION:
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_SPARK_SHIELD;
				break;

			case SKILL_GODLY_SHIELD:
			case SKILL_FROST_JAVELIN:
			case SKILL_SUMMON_MUSPELL:
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_GODLY_SHIELD;
				break;
			}
		}
	}


	if((lpCurPlayer->dwDispAppSkill&SKILL_APPMASK_PHYSICAL_ABSORB) == 0 && (dwDispAppSKill&SKILL_APPMASK_PHYSICAL_ABSORB) != 0)
	{
		SkillStopSound(SKILL_SOUND_PHYSICAL_ABSORB3);
	}

	if((lpCurPlayer->dwDispAppSkill&SKILL_APPMASK_AUTOMATION) == 0 && (dwDispAppSKill&SKILL_APPMASK_AUTOMATION) != 0)
	{
		SkillStopSound(SKILL_SOUND_SKILL_AUTOMATION3);
	}

	if((lpCurPlayer->dwDispAppSkill&SKILL_APPMASK_HOLY_BODY) == 0 && (dwDispAppSKill&SKILL_APPMASK_HOLY_BODY) != 0)
	{
		SkillStopSound(SKILL_SOUND_PHYSICAL_ABSORB3);
	}






	SelZ = 65536 * 16384;

	smRender.SetCameraPosi(x, y, z, x, ay, az);
	if(smGameStage[0])
		SetStageDynLight(smGameStage[0], x, y, z);
	if(smGameStage[1])
		SetStageDynLight(smGameStage[1], x, y, z);



	smCHAR_SetCameraPosi(x, y, z, ax, ay, az);
	if(!DebugPlayer)
	{

		cnt = RestartPlayCount;
		if(lpCurPlayer->PlayInvincible > 0) cnt = lpCurPlayer->PlayInvincible;

		if(cnt && (cnt & 0x10) == 0)
		{
			r = smRender.Color_R;
			g = smRender.Color_G;
			b = smRender.Color_B;

			smRender.Color_R += 80;
			smRender.Color_B += 80;



			lpCurPlayer->Draw();

			smRender.Color_R = r;
			smRender.Color_G = g;
			smRender.Color_B = b;

		}
		else
		{
			if(lpCurPlayer->PlayVanish <= 0) lpCurPlayer->Draw();
		}


		if(rsBlessCastle.dwMasterClan && lpCurPlayer->smCharInfo.ClassClan)
			SetClanMaster_Player(rsBlessCastle.dwMasterClan);

	}

	lpSelChar = 0;
	RendSucessCount = 0;

	for(cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if(chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].DisplayAlpha == 0)
		{

			DispFlag = TRUE;

			if(DispCharLimitMode)
			{

				dx = (lpCurPlayer->pX - chrOtherPlayer[cnt].pX) >> FLOATNS;
				dz = (lpCurPlayer->pZ - chrOtherPlayer[cnt].pZ) >> FLOATNS;
				if((dx*dx + dz*dz) > DISP_CHAR_NEAR_DIST) DispFlag = FALSE;
			}

			if(DispFlag)
			{

				r = smRender.Color_R;
				g = smRender.Color_G;
				b = smRender.Color_B;


				if(lpCurPlayer->HoSkillCode && chrOtherPlayer[cnt].smCharInfo.Life[0])
				{
					switch(lpCurPlayer->HoSkillCode)
					{
					case SKILL_SCOUT_HAWK:
						pow = GetSkillPower(lpCurPlayer, &chrOtherPlayer[cnt], 0, 0, 0);
						if(pow)
						{


							pow = DarkLevel >> 2;
							smRender.Color_R += 40 + pow;
							smRender.Color_G += 40 + pow;
							smRender.Color_B += 100 + pow;

						}
						break;
					}
				}

				if(lpCharSelPlayer && lpCharSelPlayer == &chrOtherPlayer[cnt])
				{
					smRender.Color_R = r + 40;
					smRender.Color_G = g + 60;
					smRender.Color_B = b + 60;


					DWORD OutLineColor;
					switch(lpCharSelPlayer->smCharInfo.State)
					{
					case smCHAR_STATE_USER:
						OutLineColor = RGBA_MAKE(255, 255, 255, 255);
						break;

					case smCHAR_STATE_NPC:
						OutLineColor = RGBA_MAKE(0, 255, 100, 255);
						break;

					default:
						OutLineColor = RGBA_MAKE(255, 30, 0, 255);
						break;
					}

					int ix = (lpCharSelPlayer->pX - smCHAR_CameraX) >> FLOATNS;
					int iy = (lpCharSelPlayer->pY - smCHAR_CameraY) >> FLOATNS;
					int iz = (lpCharSelPlayer->pZ - smCHAR_CameraZ) >> FLOATNS;

					int Dist = (int)sqrt(ix*ix + iy*iy + iz*iz);
					smRender.SetD3D_OutLine(1, Dist, 1.4f, 0, OutLineColor);


				}

				if(!chrOtherPlayer[cnt].RenderLatter && chrOtherPlayer[cnt].AttackIce == 0 && chrOtherPlayer[cnt].RendAlpha == 0 && chrOtherPlayer[cnt].PlayVanish <= 0)
				{


					if(chrOtherPlayer[cnt].PlayInvincible && (chrOtherPlayer[cnt].PlayInvincible & 0x10) == 0)
					{
						smRender.Color_R += 80;
						smRender.Color_B += 80;
					}

					chrOtherPlayer[cnt].Draw();
				}
				else
				{
					chrOtherPlayer[cnt].VirtualDraw();
				}

				smRender.Color_R = r;
				smRender.Color_G = g;
				smRender.Color_B = b;



				smRender.SetD3D_OutLine(0);


				if(chrOtherPlayer[cnt].RendSucess)
				{

					RendSucessCount++;

					sez = chrOtherPlayer[cnt].RendPoint.z;
					lpRect = &chrOtherPlayer[cnt].RendRect2D;

					if(chrOtherPlayer[cnt].smCharInfo.Life[0] > 0 && sez > (96 * fONE) && sez < SelZ &&
						lpRect->left<pCursorPos.x && lpRect->right>pCursorPos.x &&
						lpRect->top<pCursorPos.y && lpRect->bottom>pCursorPos.y)
					{

						SelZ = sez;
						lpSelChar = &chrOtherPlayer[cnt];
					}
				}
			}
			else
			{
				chrOtherPlayer[cnt].RendSucess = FALSE;
				RendSucessCount++;
			}
		}
	}


	LastRendSucessCount = RendSucessCount;


	if(DispCharLimitMode)
	{
		if(RendSucessCount < DISP_CHAR_LIMIT)
			DispCharLimitMode = FALSE;
	}
	else
	{
		if(RendSucessCount > DISP_CHAR_LIMIT_MAX)
			DispCharLimitMode = TRUE;
	}

	if(VRKeyBuff['A'])
	{
		lpSelChar = 0;
		SelZ = 65536 * 16384;
	}


	lpItem = 0;

	for(cnt = 0; cnt < DISP_ITEM_MAX; cnt++)
	{
		if(scItems[cnt].Flag)
		{
			if(scItems[cnt].ItemCode != 0 || DisplayDebug)
			{
				scItems[cnt].Draw();

				smRender.SetCameraPosi(x, y, z, ax, ay, az);

				sez = smRender.GetRect2D(scItems[cnt].pX, scItems[cnt].pY + (16 * fONE), scItems[cnt].pZ,
					32 * fONE, 32 * fONE, &rect, &sPos);

				scItems[cnt].RendPoint.x = sPos.x;
				scItems[cnt].RendPoint.y = sPos.y;
				scItems[cnt].RendPoint.z = sez;

				if(sez > 0 && sez < SelZ &&
					rect.left<pCursorPos.x && rect.right>pCursorPos.x &&
					rect.top<pCursorPos.y && rect.bottom>pCursorPos.y)
				{

					SelZ = sez;
					lpItem = &scItems[cnt];
					memcpy(&SelRect, &rect, sizeof(RECT));
					memcpy(&SelPos, &sPos, sizeof(POINT));
				}
			}

		}
	}

	if(lpSelChar)
	{
		lpCharSelPlayer = lpSelChar;
		lpItem = 0;
	}
	else
		lpCharSelPlayer = 0;

	if(lpItem)
	{
		lpSelItem = lpItem;
		memcpy(&MsSelRect, &SelRect, sizeof(RECT));
		memcpy(&MsSelPos, &SelPos, sizeof(POINT));
	}
	else
		lpSelItem = 0;



	if(cShop.OpenFlag || cCharShop.OpenFlag)
	{

		lpCharSelPlayer = 0;
		lpSelItem = 0;

		if(CursorClass == SIN_CURSOR_ATTACK ||
			CursorClass == SIN_CURSOR_TALK ||
			CursorClass == SIN_CURSOR_GETITEM2 ||
			CursorClass == SIN_CURSOR_GETITEM1)
		{

			CursorClass = 1;
		}
		return TRUE;
	}

	if(MouseItem.Flag)
	{
		CursorClass = 0;
	}
	else
	{
		CursorClass = 1;

		if(lpCharSelPlayer)
		{
			switch(lpCharSelPlayer->smCharInfo.State)
			{
			case smCHAR_STATE_ENEMY:

				CursorClass = SIN_CURSOR_ATTACK;
				break;
			case smCHAR_STATE_USER:
				break;
			case smCHAR_STATE_NPC:
				CursorClass = SIN_CURSOR_TALK;
				break;
			}
		}

		if(lpSelItem)
		{
			if(MouseButton[0])
				CursorClass = SIN_CURSOR_GETITEM2;
			else
				CursorClass = SIN_CURSOR_GETITEM1;
		}
	}

	return TRUE;
}

int DrawPat3D_Alpha()
{
	int cnt;
	int DispFlag;
	int dx, dz;
	int ap;
	int	RendFalg;
	int BackFrame;
	int cnt2;



	if(lpCurPlayer->PlayVanish > 0)
	{
		ap = lpCurPlayer->DisplayAlpha;
		lpCurPlayer->DisplayAlpha = -160;

		if(lpCurPlayer->PlayVague)
		{
			SetItem2PassTexture(8, smTEXSTATE_FS_SCROLL5);
			lpCurPlayer->DisplayAlpha = -60;
		}
		lpCurPlayer->Draw();

		SetItem2PassTexture(-1);
		lpCurPlayer->DisplayAlpha = ap;
	}

	if((lpCurPlayer->AttackSkil & 0xFF) == SKILL_PLAY_SHADOW_MASTER && lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_SKILL)
	{
		ap = lpCurPlayer->DisplayAlpha;
		BackFrame = lpCurPlayer->frame;
		lpCurPlayer->DisplayAlpha = -140;
		for(cnt2 = 0; cnt2 < 6; cnt2++)
		{
			lpCurPlayer->frame -= 160 * 2;
			if(lpCurPlayer->frame > (lpCurPlayer->MotionInfo->StartFrame * 160))
			{
				lpCurPlayer->Draw();
			}
			lpCurPlayer->DisplayAlpha -= 20;
		}
		lpCurPlayer->frame = BackFrame;
		lpCurPlayer->DisplayAlpha = ap;
	}

	for(cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if(chrOtherPlayer[cnt].Flag)
		{
			RendFalg = 0;
			if(chrOtherPlayer[cnt].DisplayAlpha != 0 || chrOtherPlayer[cnt].RendAlpha != 0 || chrOtherPlayer[cnt].AttackIce != 0 || chrOtherPlayer[cnt].RenderLatter || chrOtherPlayer[cnt].PlayVanish)
			{
				DispFlag = TRUE;

				if(DispCharLimitMode && chrOtherPlayer[cnt].AttackIce == 0)
				{

					dx = (lpCurPlayer->pX - chrOtherPlayer[cnt].pX) >> FLOATNS;
					dz = (lpCurPlayer->pZ - chrOtherPlayer[cnt].pZ) >> FLOATNS;
					if((dx*dx + dz*dz) > DISP_CHAR_NEAR_DIST) DispFlag = FALSE;
				}

				if(chrOtherPlayer[cnt].PlayVanish > 0 && lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->FieldCode == rsCASTLE_FIELD)
				{

					if(lpCharSelPlayer != &chrOtherPlayer[cnt])
					{
						dx = (lpCurPlayer->pX - chrOtherPlayer[cnt].pX) >> FLOATNS;
						dz = (lpCurPlayer->pZ - chrOtherPlayer[cnt].pZ) >> FLOATNS;
						if((dx*dx + dz*dz) > DIST_TRANSLEVEL_NEAR) DispFlag = FALSE;
					}
				}

				if(DispFlag)
				{


					if(lpCharSelPlayer && lpCharSelPlayer == &chrOtherPlayer[cnt])
					{
						DWORD OutLineColor;
						switch(lpCharSelPlayer->smCharInfo.State)
						{
						case smCHAR_STATE_USER:
							OutLineColor = RGBA_MAKE(255, 255, 255, 255);
							break;

						case smCHAR_STATE_NPC:
							OutLineColor = RGBA_MAKE(0, 255, 100, 255);
							break;

						default:
							OutLineColor = RGBA_MAKE(255, 30, 0, 255);
							break;
						}

						int ix = (lpCharSelPlayer->pX - smCHAR_CameraX) >> FLOATNS;
						int iy = (lpCharSelPlayer->pY - smCHAR_CameraY) >> FLOATNS;
						int iz = (lpCharSelPlayer->pZ - smCHAR_CameraZ) >> FLOATNS;

						int Dist = (int)sqrt(ix*ix + iy*iy + iz*iz);
						smRender.SetD3D_OutLine(1, Dist, 1.4f, 0, OutLineColor);
					}


					ap = chrOtherPlayer[cnt].DisplayAlpha;

					if(chrOtherPlayer[cnt].PlayVanish > 0)
					{
						chrOtherPlayer[cnt].DisplayAlpha = -160;
						if(chrOtherPlayer[cnt].PlayVague) SetItem2PassTexture(8, smTEXSTATE_FS_SCROLL5);
					}

					if(chrOtherPlayer[cnt].RendAlpha && ap > chrOtherPlayer[cnt].RendAlpha)
					{

						chrOtherPlayer[cnt].DisplayAlpha = chrOtherPlayer[cnt].RendAlpha;

						if(chrOtherPlayer[cnt].MotionInfo->State >= 0x100 &&
							(chrOtherPlayer[cnt].smCharInfo.dwCharSoundCode == snCHAR_SOUND_ILLUSIONKNIGHT || chrOtherPlayer[cnt].PlayVanish > 0))
						{
							chrOtherPlayer[cnt].DisplayAlpha = ap;
						}

						chrOtherPlayer[cnt].Draw();
						chrOtherPlayer[cnt].DisplayAlpha = ap;

					}
					else
					{
						chrOtherPlayer[cnt].Draw();
					}
					RendFalg++;

					SetItem2PassTexture(-1);
					chrOtherPlayer[cnt].DisplayAlpha = ap;


					smRender.SetD3D_OutLine(0);


				}
			}

			if(RendFalg == 0)
			{
				if((chrOtherPlayer[cnt].AttackSkil & 0xFF) == SKILL_PLAY_SHADOW_MASTER && chrOtherPlayer[cnt].MotionInfo->State == CHRMOTION_STATE_SKILL)
				{
					ap = chrOtherPlayer[cnt].DisplayAlpha;
					BackFrame = chrOtherPlayer[cnt].frame;
					chrOtherPlayer[cnt].DisplayAlpha = -160;
					for(cnt2 = 0; cnt2 < 4; cnt2++)
					{
						chrOtherPlayer[cnt].frame -= 160 * 4;
						if(chrOtherPlayer[cnt].frame > (chrOtherPlayer[cnt].MotionInfo->StartFrame * 160))
						{
							chrOtherPlayer[cnt].Draw();
						}
					}
					chrOtherPlayer[cnt].frame = BackFrame;
					chrOtherPlayer[cnt].DisplayAlpha = ap;
				}
			}
		}
	}

	return TRUE;
}


int DrawPatShadow(int x, int y, int z, int ax, int ay, int az)
{
	int cnt;

	smCHAR_SetCameraPosi(x, y, z, ax, ay, az);





	cnt = 0;

	lpCurPlayer->DrawShadow();



	if(lpCurPlayer->OnStageField >= 0)
	{
		if(StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_ICE)
			lpCurPlayer->DrawIceFoot();
	}


	for(cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if(chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].DisplayAlpha == 0 && chrOtherPlayer[cnt].RendAlpha == 0)
		{

			chrOtherPlayer[cnt].DrawShadow();
		}
	}



	return TRUE;
}

extern BYTE VRKeyBuff[256];

int Draw2DCounter = 0;

int DrawPat2D(int x, int y, int z, int ax, int ay, int az)
{





	int cnt;

	if(lpCurPlayer->Pattern == 0) return FALSE;

	smCHAR_SetCameraPosi(x, y, z, ax, ay, az);
	smRender.SetMaterialGroup(smMaterialGroup);

	for(cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if(chrOtherPlayer[cnt].Flag)
		{
			chrOtherPlayer[cnt].DrawMotionBlur();
		}
	}

	lpCurPlayer->DrawMotionBlur();

	DrawParticle(x, y, z, ax, ay, az);





	Draw2DCounter++;


	DrawLightImage();

	DrawWeather(ax);


	return TRUE;

}

extern int ViewPointLen;

extern DWORD smBackColor;

int BGFace[2][3] = {
	{ 0 ,  1 , 2 },
	{ 1 ,  3 , 2 }
};


DRZTEXTURE2 *hBGTexture;
DRZTEXTURE2 *hBGTexture2;
smOBJ3D *smBackGround;

DIRECTDRAWSURFACE *BackVideoSurface;
int BackVideoFrame;
int LastFrame;

int BGMatNum[2];


#include "pbackground.h"

smBACKGROUND	smBackMesh[2];
smBACKGROUND	*lpCurrentBG;


int InitBackGround()
{




	lpCurrentBG = 0;

	ChangeSky(0);

	return TRUE;
}

int CloseBackGround()
{

	smBackMesh[1].Close();
	smBackMesh[0].Close();
	return TRUE;

}

int BgFrame = 0;

int BGMain()
{
	smBackMesh[0].Main();
	smBackMesh[1].Main();

	if(lpCurrentBG && lpCurrentBG->FadeShowCount == 0)
	{
		if(&smBackMesh[0] != lpCurrentBG && smBackMesh[0].smObjBG)
			smBackMesh[0].Close();

		if(&smBackMesh[1] != lpCurrentBG && smBackMesh[1].smObjBG)
			smBackMesh[1].Close();
	}

	return TRUE;
}

int ChangeBG(int BgNum)
{

	if(!lpCurrentBG)
	{
		smBackMesh[0].Init(BgNum);
		lpCurrentBG = &smBackMesh[0];
		if(smBackMesh[0].lpMaterialGroup)
			smBackMesh[0].lpMaterialGroup->ReadTextures();

		smBackMesh[0].FadeShowCount = 0;

		return TRUE;
	}

	if(lpCurrentBG->BackGroundNum == BgNum) return FALSE;

	if(&smBackMesh[0] != lpCurrentBG && !smBackMesh[0].smObjBG)
	{
		smBackMesh[0].Init(BgNum);
		lpCurrentBG = &smBackMesh[0];
		if(smBackMesh[0].lpMaterialGroup)
			smBackMesh[0].lpMaterialGroup->ReadTextures();
		return TRUE;
	}

	if(&smBackMesh[1] != lpCurrentBG && !smBackMesh[1].smObjBG)
	{
		smBackMesh[1].Init(BgNum);
		lpCurrentBG = &smBackMesh[1];
		if(smBackMesh[1].lpMaterialGroup)
			smBackMesh[1].lpMaterialGroup->ReadTextures();
		return TRUE;
	}

	return FALSE;
}

int DrawBG(int x, int y, int z, int ax, int ay, int az)
{


	if(StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_DUNGEON) return TRUE;
	if(StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_ROOM) return TRUE;

	renderDevice.SetRenderState(D3DRENDERSTATE_ZENABLE, FALSE);

	if(smBackMesh[0].FadeShowCount > smBackMesh[1].FadeShowCount)
	{
		smBackMesh[0].Draw(x, y, z, ax, ay, az);
		smBackMesh[1].Draw(x, y, z, ax, ay, az);
	}
	else
	{
		smBackMesh[1].Draw(x, y, z, ax, ay, az);
		smBackMesh[0].Draw(x, y, z, ax, ay, az);
	}

	renderDevice.SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE);

	return TRUE;
}


RECT	PartyTradeButtonRect[4] = {
	{	00,0, 20, 20	},
	{	25,0, 20, 20	},
	{	50,0, 20, 20	},
	{	75,0, 20, 20	}
};

RECT	PartyTradeToolTipRect = { 1,18,70,28 };

POINT	PartyButtonPoint = { -1, -1 };


int GetPartyTradeButtonPos(int x, int y)
{
	int cnt, sx;
	int AdjustX;
	int MaxCnt;

	int wx, wy;
	if(PartyButtonPoint.x < 0) return -1;

	wx = PartyButtonPoint.x;
	wy = PartyButtonPoint.y;

	if(EachTradeButtonMode)
	{
		AdjustX = -10; MaxCnt = 4;
	}
	else
	{
		AdjustX = 0; MaxCnt = 3;
	}

	for(cnt = 0; cnt < MaxCnt; cnt++)
	{
		sx = PartyTradeButtonRect[cnt].left + AdjustX + wx;
		if(sx<x && (sx + PartyTradeButtonRect[cnt].right)>x &&
			PartyTradeButtonRect[cnt].top + wy<y && (PartyTradeButtonRect[cnt].top + wy + PartyTradeButtonRect[cnt].bottom)>y)
		{

			return cnt;

		}
	}

	return -1;
}


int DisplayPartyTradeButton()
{

	int SelNum;
	int cnt;
	int AdjustX;
	int MaxCnt;

	int wx, wy;
	if(PartyButtonPoint.x < 0) return -1;
	wx = PartyButtonPoint.x;
	wy = PartyButtonPoint.y;

	if(EachTradeButtonMode)
	{
		AdjustX = -10; MaxCnt = 4;
	}
	else
	{
		AdjustX = 0; MaxCnt = 3;
	}

	SelNum = GetPartyTradeButtonPos(pCursorPos.x, pCursorPos.y);

	for(cnt = 0; cnt < MaxCnt; cnt++)
	{
		if(SelNum == cnt)
		{
			if(lpDDS_ParTradeButton[cnt][1])
			{
				DrawSprite(PartyTradeButtonRect[cnt].left + AdjustX + wx, PartyTradeButtonRect[cnt].top + wy,
					lpDDS_ParTradeButton[cnt][1], 0, 0, PartyTradeButtonRect[cnt].right, PartyTradeButtonRect[cnt].bottom);
			}
		}
		else
		{
			if(lpDDS_ParTradeButton[cnt][0])
			{
				DrawSprite(PartyTradeButtonRect[cnt].left + AdjustX + wx, PartyTradeButtonRect[cnt].top + wy,
					lpDDS_ParTradeButton[cnt][0], 0, 0, PartyTradeButtonRect[cnt].right, PartyTradeButtonRect[cnt].bottom);
			}
		}
	}

	if(SelNum >= 0)
	{
		if(lpDDS_ParTradeToolTip[SelNum])
		{
			DrawSprite(PartyTradeButtonRect[SelNum].left - 60 + AdjustX + wx, PartyTradeToolTipRect.top + wy,
				lpDDS_ParTradeToolTip[SelNum], 0, 0, PartyTradeToolTipRect.right, PartyTradeToolTipRect.bottom);
		}
	}

	return TRUE;
}



smCHAR	chrEachPlayer;
smCHAR *chrEachMaster = 0;
int		EachTradeButton = 0;
int		EachTradeButtonMode = 0;
RECT	RectTradeButton;

POINT3D EachCameraPos;
int	DispEachMode = 0;



int FindBipPoint(smPAT3D *lpPat, char *szObjNodeName, int frame, int *nX, int *nY, int *nZ);


int OpenEachPlayer(smCHAR *lpChar)
{
	if(!lpChar || !lpChar->Flag || !lpChar->DisplayFlag) return FALSE;
	if(EachTradeButton) return FALSE;

	memcpy(&chrEachPlayer, lpChar, sizeof(smCHAR));
	chrEachPlayer.SetMotionFromCode(CHRMOTION_STATE_STAND);
	chrEachPlayer.ActionPattern = 101;
	chrEachMaster = lpChar;

	chrEachPlayer.Flag = TRUE;

	if(FindBipPoint(chrEachPlayer.AnimPattern, "Bip01 Head", chrEachPlayer.frame,
		&EachCameraPos.x, &EachCameraPos.y, &EachCameraPos.z) == NULL)
	{

		EachCameraPos.y = chrEachPlayer.PatHeight - 10 * fONE;
		EachCameraPos.x = 0;
		EachCameraPos.z = 0;
	}


	if(lpChar->smCharInfo.State == smCHAR_STATE_ENEMY || lpChar->smCharInfo.State == smCHAR_STATE_NPC)
	{
		EachCameraPos.y += lpChar->smCharInfo.ArrowPosi[0] * fONE;
		EachCameraPos.z += lpChar->smCharInfo.ArrowPosi[1] * fONE;


	}

	return TRUE;
}


int CloseEachPlayer()
{
	chrEachPlayer.Flag = 0;
	chrEachMaster = 0;
	EachTradeButton = 0;

	return TRUE;
}


int EachPlayerMain()
{
	if(!chrEachMaster || !chrEachMaster->Flag || chrEachMaster->dwObjectSerial != chrEachPlayer.dwObjectSerial ||
		chrEachMaster->Pattern != chrEachPlayer.Pattern)
	{
		CloseEachPlayer();
		return TRUE;
	}

	if(chrEachPlayer.Flag)
	{



		if(DispEachMode)
		{
			if(chrEachPlayer.TalkSoundSum && chrEachPlayer.TalkSoundSum != g_PlayTalkSoundSum)
			{
				PlayTalkSound();
				chrEachPlayer.AutoChangeTalkMotion(TALK_MOTION_FILE);
			}
			else if(chrEachPlayer.TalkPattern && chrEachPlayer.TalkFrame == 0)
			{
				if(IsPlayTalkSound())
					chrEachPlayer.AutoChangeTalkMotion(TALK_MOTION_FILE);
				else
					chrEachPlayer.AutoChangeTalkMotion(FACIAL_MOTION_FILE);
			}
		}
		else
		{
			if(IsPlayTalkSound())
				StopTalkSound();

			chrEachPlayer.TalkSoundSum = 0;
			g_PlayTalkSoundSum = 0;
		}


		chrEachPlayer.Main();


		if(chrEachMaster && chrEachMaster->smCharInfo.State == smCHAR_STATE_NPC)
		{
			if(chrEachMaster->MotionInfo->State == CHRMOTION_STATE_ATTACK && chrEachPlayer.MotionInfo->State == CHRMOTION_STATE_STAND)
				chrEachPlayer.SetMotionFromCode(CHRMOTION_STATE_ATTACK);
		}

		if(chrEachMaster->MotionInfo->State == CHRMOTION_STATE_DEAD && chrEachMaster->FrameCounter > 0x50)
			CloseEachPlayer();

	}

	return TRUE;
}

int DrawClanMark_EachBox(DIRECTDRAWSURFACE clanMark, int x, int y)
{
	RECT ddRect;

	ddRect.left = 0;
	ddRect.right = 16;
	ddRect.top = 0;
	ddRect.bottom = 16;

	if(clanMark)
	{

		renderDevice.BltFast(renderDevice.lpDDSBack, x, y, clanMark, &ddRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	}

	return TRUE;
}


int DrawEachPlayer(float fx, float fy, int SizeMode){
	return TRUE;
}


int FindBipPoint(smPAT3D *lpPat, char *szObjNodeName, int frame, int *nX, int *nY, int *nZ)
{
	smOBJ3D	*lpObj = lpPat->GetObjectFromName(szObjNodeName);
	if(!lpObj) return FALSE;


	smMATRIX *mWorld;
	POINT3D angle;

	ZeroMemory(&angle, sizeof(POINT3D));
	angle.y = (-angle.y + ANGLE_180)&ANGCLIP;

	mWorld = &lpObj->mWorld;

	AnimObjectTree(lpObj, frame, angle.x, angle.y, angle.z);

	*nX = mWorld->_41;
	*nZ = mWorld->_42;
	*nY = mWorld->_43;

	return TRUE;
}


int Record_ClinetLogFile(char *szMessage)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	int len;
	char	szFileName[128];
	char	szBuff[256];

	GetLocalTime(&st);
	wsprintf(szFileName, "game.log", st.wMonth, st.wDay);

	hFile = CreateFile("game.log", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE) return FALSE;

	wsprintf(szBuff, "%d-%d (%d:%d:%d) - %s", st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, szMessage);
	len = lstrlen(szBuff);
	if(szBuff[len - 1] != '\n')
	{
		szBuff[len] = '\r';
		szBuff[len + 1] = '\n';
		len += 2;
	}

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, len, &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}


#include "TJBOY\\park\\ParkDXplayer.h"

int ParkPlayInit = 0;
int ParkPlayMode = 0;
int ParkPlaying = 0;
RECT ParkPlayRect;


int Init_ParkPlayer()
{

	ParkPlayInit = TRUE;
	ParkDXPlay.InitPlayer();
	ParkPlayMode = 0;
	ParkPlaying = 0;
	ParkPlayRect.left = 0;
	ParkPlayRect.top = 0;
	ParkPlayRect.right = WinSizeX;
	ParkPlayRect.bottom = WinSizeY;

	return TRUE;



}


int Play_ParkPlayer(char *szPath, int x, int y, int w, int h, int PlayMode)
{
	if(ParkPlaying)
		Stop_ParkPlayer();

	Init_ParkPlayer();

	if(ParkDXPlay.LoadPlayerFile(hwnd, szPath))
	{
		ParkDXPlay.PlaySize(x, y, w, h);
		ParkDXPlay.PlayPlayer();
		ParkPlayMode = PlayMode;
		ParkPlaying = TRUE;

		ParkPlayRect.left = x;
		ParkPlayRect.top = y;
		ParkPlayRect.right = x + w;
		ParkPlayRect.bottom = y + h;

		return TRUE;
	}

	return FALSE;
}


int Stop_ParkPlayer()
{
	ParkDXPlay.StopPlayer();
	ParkPlayMode = 0;
	ParkPlaying = FALSE;

	return TRUE;
}
