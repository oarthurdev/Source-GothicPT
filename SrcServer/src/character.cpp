

#include "smlib3d\\smd3d.h"
#include "smwsock.h"

#include "character.h"
#include "Sound\\dxwav.h"
#include "particle.h"
#include "fileread.h"
#include "playmain.h"
#include "drawsub.h"
#include "netplay.h"
#include "field.h"
#include "hobaram\\holinkheader.h"
#include "sinbaram\\sinlinkheader.h"

#include "effectsnd.h"
#include "playsub.h"
#include "skillsub.h"
#include "Language\\language.h"

#include "tjboy\\clanmenu\\tjclanDEF.h"
#include "tjboy\\clanmenu\\tjclan.h"
#include "tjboy\\clanmenu\\cE_CViewClanInfo.h"

#include "damage.h"
#include "Server\\svr_Damage.h"
#include "Server\\onserver.h"
#include "FullZoomMap.h"		



#define DISP_DAMAGE

#ifdef	DISP_DAMAGE
int rsDisplayDamgeToClient(rsPLAYINFO *lpPlayInfo, char *szDmgMsg);
#endif

#define		SUCCUBUS_CURSE_TIME		10


#define		PKMODE_ABSORB			30

extern BYTE VRKeyBuff[256];
extern int MouseButton[3];
extern DWORD dwPlayServTime;

static int MatMBlur;

static smTEXLINK smTexLinkMotionBlur[128];
static smVERTEX MbVertex[64];
static smFACE MbFace[64];

static smTEXLINK smTexLinkMotionBlur2[64];
static smVERTEX MbVertex2[32];
static smFACE MbFace2[32];

#define	AGING_SUB_LEVEL	10

int	SkillChargingFlag = 0;
int	SkillEventDamageCount;

TRANS_SKIL_ATTACKDATA	Trans_SplashCharList;


CRITICAL_SECTION	cLoadSection;



int	SkillShadowMasterEvent[9][7] = {
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0 },

	{ 1, 3, 5, 0, 0, 0, 0 },
	{ 1, 3, 5, 6, 0, 0, 0 },
	{ 1, 2, 3, 4, 6, 0, 0 },
	{ 1, 2, 3, 4, 6, 7, 0 },
	{ 1, 2, 3, 4, 5, 6, 7 },

	{ 1, 2, 3, 4, 5, 6, 7 }
};


int CastleBattleZone_LineZ = -24043 * fONE;
int	CastleBattleZone_DoorLineZ = -25545 * fONE;
int	CastleBattleZone_DoorLineX[2] = { 34407 * fONE, 34695 * fONE };
int	CastleBattleZone_BridgeZ = -25258 * fONE;
int CastleSoulFountain_Area[4] = { 37040 * fONE, 37158 * fONE, -30286 * fONE, -30102 * fONE };


int DrawMotionBlur();



int rsCheckHardCoreEventArea(int x, int y, int z);
extern int	rsHardCoreEventInterLineZ;
extern int	rsHardCoreEventInterLineZ2;
extern int	rsHardCoreEventPosY;
extern int	rsHardCoreEventOutLineZ;
extern rsSERVER_CONFIG		rsServerConfig;


smCHAR *rsOpenSubMonster(smCHAR *lpMainChar, DWORD dwCharSoundCode, int x, int y, int z, int MaxFlag);

int rsGetMonCountFlag(smCHAR *lpChar);


int rsSendTransSkillAttack(smCHAR *lpChar, rsPLAYINFO *lpPlayInfo);

int rsProcessAttack_SkillHolyReflection(rsPLAYINFO *lpPlayInfo, smCHAR *lpChar);

smCHAR *rsFindAroundMonster(smCHAR *lpChar, int RoundDist);

smCHAR *rsSkillDamage_AroundMonster(smCHAR *lpChar);

smCHAR *rsSkillMonster_AroundMonster(smCHAR *lpChar, int RoundDist);



int GetProjPosi(int &x3d, int &y3d, int &z3d, POINT3D *CameraPosi, POINT3D *CameraAngle);

int rsSendTransSkillAttack(smCHAR *lpChar, rsPLAYINFO *lpPlayInfo);


int GetResistancePower(int power, int ResCode)
{
	int rs, result;

	rs = lpCurPlayer->smCharInfo.Resistance[ResCode];

	if (rs < 0) rs = 0;
	if (rs >= 100) rs = 100;
	rs = 100 - rs;

	result = (power*rs) / 100;

	if (result <= 0) result = 4;

	return result;
}




int			Debug_TalkZoomMode;
int			Debug_TalkRepeatMode;
int			Debug_TalkRepeatModeType;

void DrawTalkZoom(smCHAR *lpChar, smPAT3D *lpPattern, float fx, float fy)
{
	if (lpChar == NULL)
		return;

	POINT3D TalkCameraPos;

	smOBJ3D	*lpObj = lpPattern->GetObjectFromName("Head");
	if (lpObj == NULL)
	{
		TalkCameraPos.y = lpChar->PatHeight - 10 * fONE;
		TalkCameraPos.x = 0;
		TalkCameraPos.z = 0;
	}
	else
	{
		smMATRIX *mWorld;
		POINT3D angle;

		ZeroMemory(&angle, sizeof(POINT3D));
		angle.y = (-angle.y + ANGLE_180)&ANGCLIP;

		mWorld = &lpObj->mWorld;

		AnimObjectTree(lpObj, lpChar->frame, angle.x, angle.y, angle.z);

		TalkCameraPos.x = mWorld->_41;
		TalkCameraPos.z = mWorld->_42;
		TalkCameraPos.y = mWorld->_43;
	}

	if (lpChar->smCharInfo.State == smCHAR_STATE_ENEMY)
	{
		TalkCameraPos.y += lpChar->smCharInfo.ArrowPosi[0] * fONE;
		TalkCameraPos.z += lpChar->smCharInfo.ArrowPosi[1] * fONE;
	}


	int x, y, z, w, h;
	int mx, my, he;
	POINT3D angle;
	int dist;
	int	ObjSizeBack;

	mx = MidX;
	my = MidY;

	MidX = (int)((float)WinSizeX * fx);
	MidY = (int)((float)WinSizeY * fy);

	int chrHeight;
	if (lpChar->smCharInfo.State <= TRUE)
		chrHeight = lpChar->PatHeight - 8 * fONE;
	else
		chrHeight = lpChar->PatHeight;

	w = (int)((float)WinSizeX / 4);
	h = (int)((float)WinSizeY / 2);

	w += 20;
	h += 20;

	smRender.SMSHIFT_PERSPECTIVE_WIDTH = RENDCLIP_DEFAULT_SHIFT_PERSPECTIVE_WIDTH * 3;
	smRender.SMMULT_PERSPECTIVE_HEIGHT = RENDCLIP_DEFAULT_MULT_PERSPECTIVE_HEIGHT * 2;

	dist = 30 * fONE;
	he = -1 * fONE;

	dist += TalkCameraPos.y;

	extern int	MatEachBox;

	if (MatEachBox >= 0)
	{
		renderDevice.BeginScene();
		dsDrawTexImage(MatEachBox, MidX - (w >> 1), MidY - (h >> 1), w, h, 255, 0);
		renderDevice.EndScene();
	}

	renderDevice.ClearViewport(D3DCLEAR_ZBUFFER);

	smCHAR_SetCameraPosi(TalkCameraPos.x, TalkCameraPos.y + he, dist + TalkCameraPos.z, 0, ANGLE_180, 0);

	x = lpChar->pX;
	y = lpChar->pY;
	z = lpChar->pZ;
	memcpy(&angle, &lpChar->Angle, sizeof(POINT3D));

	lpChar->pX = 0;
	lpChar->pY = 0;
	lpChar->pZ = 0;
	ZeroMemory(&lpChar->Angle, sizeof(POINT3D));

	ObjSizeBack = lpChar->smCharInfo.wPlayClass[1];
	lpChar->smCharInfo.wPlayClass[1] = 0;

	lpChar->Draw();

	lpChar->smCharInfo.wPlayClass[1] = ObjSizeBack;

	lpChar->pX = x;
	lpChar->pY = y;
	lpChar->pZ = z;
	memcpy(&lpChar->Angle, &angle, sizeof(POINT3D));

	MidX = mx;
	MidY = my;

	smRender.SMSHIFT_PERSPECTIVE_WIDTH = RENDCLIP_DEFAULT_SHIFT_PERSPECTIVE_WIDTH;
	smRender.SMMULT_PERSPECTIVE_HEIGHT = RENDCLIP_DEFAULT_MULT_PERSPECTIVE_HEIGHT;
}



int GetSinItemNumFromCode(DWORD CODE)
{

	for (int j = 0; j < MAX_ITEM; j++)
	{
		if (sItem[j].CODE == CODE)
		{
			return j;
		}

	}
	return -1;
}


int GetDistanceDbl(int x1, int z1, int x2, int z2)
{
	int ax, az;

	ax = (x1 - x2) >> FLOATNS;
	az = (z1 - z2) >> FLOATNS;
	ax *= ax;
	az *= az;
	return ax + az;
}


int CheckLocateBox(int x1, int y1, int z1, int x2, int y2, int z2, int size)
{
	if (abs(x1 - x2) < size && abs(y1 - y2) < size && abs(z1 - z2) < size)
		return TRUE;

	return FALSE;
}


int AnimObjectTree(smOBJ3D *tObj, int frame, int ax, int ay, int az)
{
	smOBJ3D *ObjList[32];
	smOBJ3D *obj;
	int ObjCnt;
	int cnt;

	ObjCnt = 0;
	obj = tObj;

	while (1)
	{
		ObjList[ObjCnt++] = obj;
		if (!obj->pParent) break;
		obj = obj->pParent;
	}

	for (cnt = ObjCnt - 1; cnt >= 0; cnt--)
	{
		ObjList[cnt]->TmAnimation(frame, ax, ay, az);
	}

	return TRUE;
}


char *szBipName_RightHand = "Bip weapon01";
char *szBipName_LeftHand = "Bip01 L Hand";
char *szBipName_Shield = "Bip01 L Forearm";
char *szBipName_Shield2 = "Bip-shield";
char *szBipName_BackSpine = "Bip in01";
char *szBipName_BackSpineCross = "Bip in-bow";
char *szBipName_BackSpineBow = "Bip in-cro";
char *szBipName_RFoot = "Bip01 R Foot";
char *szBipName_LFoot = "Bip01 L Foot";
char *szBipName_Head = "Bip01 Head";




int smCHAR_CameraX;
int smCHAR_CameraY;
int smCHAR_CameraZ;

int smCHAR_CameraAngX;
int smCHAR_CameraAngY;
int smCHAR_CameraAngZ;



int smCHAR_SetCameraPosi(int x, int y, int z, int angX, int angY, int angZ)
{
	smCHAR_CameraX = x;
	smCHAR_CameraY = y;
	smCHAR_CameraZ = z;

	smCHAR_CameraAngX = angX;
	smCHAR_CameraAngY = angY;
	smCHAR_CameraAngZ = angZ;

	return TRUE;
}





DWORD GetSpeedSum(const char *szName)
{
	DWORD cnt;
	DWORD Sum1, Sum2;
	BYTE ch;
	DWORD  dwSum;

	Sum2 = 0;
	dwSum = 0;

	cnt = 0;

	while (1)
	{
		ch = (BYTE)szName[cnt];
		if (ch == 0) break;
		if (ch >= 'a' && ch <= 'z')
		{
			Sum2 += (ch - 0x20)*(cnt + 1);
			dwSum += (ch - 0x20)*(cnt*cnt);
		}
		else
		{
			Sum2 += (ch*(cnt + 1));
			dwSum += ch * (cnt*cnt);
		}
		cnt++;
	}

	Sum1 = cnt;

	return (dwSum << 24) | (Sum1 << 16) | Sum2;
}



smPATTERN::smPATTERN(void)
{
	Init();
}


smPATTERN::~smPATTERN(void)
{
	Close();
}



void smPATTERN::Init()
{
	int cnt;

	for (cnt = 0; cnt < DPAT_MAX; cnt++)
		ZeroMemory(&DinaPat[cnt], sizeof(smDPAT));

	BipPattern = 0;
}


int smPATTERN::Close()
{
	int cnt;



	for (cnt = 0; cnt < DPAT_MAX; cnt++)
	{
		if (DinaPat[cnt].Pat)
		{
			delete DinaPat[cnt].Pat;
			DinaPat[cnt].Pat = 0;
			if (DinaPat[cnt].lpModelInfo)
			{
				delete DinaPat[cnt].lpModelInfo;
				DinaPat[cnt].lpModelInfo = 0;
			}
		}
	}

	return TRUE;
}


int smPATTERN::FindFromName(char *szName)
{
	int cnt;

	for (cnt = 0; cnt < DPAT_MAX; cnt++)
	{
		if (DinaPat[cnt].Pat)
		{
			if (lstrcmpi(szName, DinaPat[cnt].szPatName) == 0)
			{
				return cnt;
			}
		}
	}

	return -1;
}


int smPATTERN::FindFromCode(DWORD dwCode)
{
	int cnt;

	for (cnt = 0; cnt < DPAT_MAX; cnt++)
	{
		if (DinaPat[cnt].Pat && dwCode == DinaPat[cnt].dwSpeedFindSum)
			return cnt;
	}

	return -1;
}


int smPATTERN::GetNew()
{
	int cnt;

	for (cnt = 0; cnt < DPAT_MAX; cnt++)
	{
		if (DinaPat[cnt].Pat == 0)
			return cnt;
	}

	return -1;
}


smDPAT *smPATTERN::LoadBipPattern(char *szFileName)
{
	DWORD dwCode = GetSpeedSum(szFileName);
	int Num = FindFromCode(dwCode);

	if (Num < 0)
	{


		Num = GetNew();
		if (Num >= 0)
		{
			DinaPat[Num].Pat = smASE_ReadBone(szFileName);
			if (DinaPat[Num].Pat)
			{
				DinaPat[Num].smDinaLink = 0;
				strcpy_s(DinaPat[Num].szPatName, szFileName);
				DinaPat[Num].dwSpeedFindSum = dwCode;
				DinaPat[Num].UseCount = 1;
				return &DinaPat[Num];
			}
		}
		else
			return NULL;
	}

	DinaPat[Num].UseCount++;

	return &DinaPat[Num];
}


smDPAT *smPATTERN::LoadCharactor(char *szFileName)
{
	int Num, sframe;
	DWORD cnt;
	smDPAT *dMotionPat;
	smPAT3D	*AnimPat;
	smMODELINFO	modelInfo;


	DWORD dwCode = GetSpeedSum(szFileName);
	Num = FindFromCode(dwCode);

	if (Num < 0)
	{
		if (smModelDecode(szFileName, &modelInfo) == NULL)
			return NULL;



		smASE_SetPhysique(0);

		Num = GetNew();

		if (Num < 0)
			return NULL;

		if (BipPattern && modelInfo.szMotionFile[0])
		{
			dMotionPat = BipPattern->LoadBipPattern(modelInfo.szMotionFile);
			if (dMotionPat)
			{
				smASE_SetPhysique(dMotionPat->Pat);
				DinaPat[Num].smDinaLink = dMotionPat;
			}
			else
				return NULL;
		}
		else
			DinaPat[Num].smDinaLink = 0;



		if (BipPattern && modelInfo.szTalkMotionFile[0])
		{
			smDPAT *lpTalkLink = BipPattern->LoadBipPattern(modelInfo.szTalkMotionFile);
			if (lpTalkLink)
				DinaPat[Num].lpTalkLink = lpTalkLink;
			else
				return NULL;
		}
		else
			DinaPat[Num].lpTalkLink = NULL;

		DinaPat[Num].Pat = smASE_Read(modelInfo.szModelFile);

		if (!DinaPat[Num].Pat)
		{
			if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
			{
				char szErrorMsg[128];

				wsprintf(szErrorMsg, "Loading Error , ( %s )", modelInfo.szModelFile);
				AddChatBuff(szErrorMsg);
			}
			return NULL;
		}

		if (DinaPat[Num].smDinaLink)
			AnimPat = DinaPat[Num].smDinaLink->Pat;
		else
			AnimPat = DinaPat[Num].Pat;


		if (AnimPat && AnimPat->TmFrameCnt > 0)
		{
			for (cnt = 0; cnt < modelInfo.MotionCount; cnt++)
			{
				sframe = AnimPat->TmFrame[modelInfo.MotionInfo[cnt].MotionFrame - 1].StartFrame / 160;
				modelInfo.MotionInfo[cnt].StartFrame += sframe;
				modelInfo.MotionInfo[cnt].EndFrame += sframe;
			}
		}

		DinaPat[Num].lpModelInfo = new smMODELINFO;
		memcpy(DinaPat[Num].lpModelInfo, &modelInfo, sizeof(smMODELINFO));
		strcpy_s(DinaPat[Num].szPatName, szFileName);
		DinaPat[Num].dwSpeedFindSum = dwCode;
		DinaPat[Num].UseCount = 1;
		return &DinaPat[Num];
	}

	DinaPat[Num].UseCount++;
	return &DinaPat[Num];
}


extern smPAT3D *PatKnife;
char *szDefaultCharName = "char\\woman.ini";


int InitLoader();

int CreateLoaderThread();
DWORD WINAPI smLoaderThreadProc(void *pInfo);

struct smDATALOADER
{
	smSTAGE3D	*lpStage;
	smCHAR		*lpChar;
	scITEM		*lpItem;


	char		szLoadName[64];
	char		szLoadName2[64];

	int			Result;
	int			Cancel;
};

#define DATALOADER_MAX		64
#define DATALOADER_MASK		63

smDATALOADER	smLoader[DATALOADER_MAX];
int	smLoaderCnt;
int smLoaderEnd;
int	ThreadLoaderStats;

smPATTERN smBipPattern;
smPATTERN smPattern;


int AddLoaderStage(smSTAGE3D *lpStage, char *szName)
{
	int cnt = smLoaderEnd & DATALOADER_MASK;

	smLoaderEnd++;

	smLoader[cnt].lpStage = lpStage;
	smLoader[cnt].lpChar = 0;
	smLoader[cnt].lpItem = 0;
	smLoader[cnt].Cancel = 0;
	smLoader[cnt].Result = 0;
	strcpy_s(smLoader[cnt].szLoadName, szName);


	CreateLoaderThread();

	return smLoaderEnd;
}


int	AddLoaderPattern(smCHAR *lpChar, char *szName, char *szName2)
{
	int cnt = smLoaderEnd & DATALOADER_MASK;

	smLoaderEnd++;

	smLoader[cnt].lpStage = 0;
	smLoader[cnt].lpChar = lpChar;
	smLoader[cnt].lpItem = 0;
	smLoader[cnt].Cancel = 0;
	smLoader[cnt].Result = 0;
	strcpy_s(smLoader[cnt].szLoadName, szName);

	if (szName2)
		strcpy_s(smLoader[cnt].szLoadName2, szName2);
	else
		smLoader[cnt].szLoadName2[0] = 0;

	smLoader[cnt].lpChar->PatLoading = TRUE;


	CreateLoaderThread();

	return TRUE;
}


int	AddLoaderItem(scITEM *lpItem, char *szName)
{
	int cnt = smLoaderEnd & DATALOADER_MASK;

	smLoaderEnd++;

	smLoader[cnt].lpStage = 0;
	smLoader[cnt].lpChar = 0;
	smLoader[cnt].lpItem = lpItem;
	smLoader[cnt].Cancel = 0;
	smLoader[cnt].Result = 0;
	strcpy_s(smLoader[cnt].szLoadName, szName);

	smLoader[cnt].lpItem->PatLoading = TRUE;


	CreateLoaderThread();

	return TRUE;
}

DWORD WINAPI smLoaderThreadProc(void *pInfo)
{


	int	cnt;
	smDPAT	*smDPat;
	smDPAT  *smDPat2;


	smDPAT *lpPatOld;
	smDPAT *lpPatOld2;




	EnterCriticalSection(&cLoadSection);


	cnt = smLoaderCnt & DATALOADER_MASK;


	if (smLoader[cnt].lpStage)
	{

		if (smSTAGE3D_ReadASE(smLoader[cnt].szLoadName, smLoader[cnt].lpStage))
		{
			if (renderDevice.IsDevice())
			{



				smLoader[cnt].lpStage->smMaterialGroup->ReadTextures(1);



				smLoader[cnt].lpStage->smMaterialGroup->CheckMatreialTextureSwap();
			}
			smLoader[cnt].Result = TRUE;
			smLoader[cnt].lpStage->Head = TRUE;
		}
	}


	if (smLoader[cnt].lpItem)
	{
		smLoader[cnt].lpItem->PatLoading = TRUE;


		lpPatOld = smLoader[cnt].lpItem->lpDinaPattern;
		smDPat = smPattern.LoadCharactor(smLoader[cnt].szLoadName);

		if (smDPat)
		{
			if (renderDevice.IsDevice() && smDPat->UseCount == 1)
			{





				if (smDPat && smDPat->Pat)
				{
					smDPat->Pat->smMaterialGroup->ReadTextures();
					smDPat->Pat->smMaterialGroup->CheckMatreialTextureSwap();
				}
			}




			smLoader[cnt].lpItem->DisplayFlag = 0;

			smLoader[cnt].lpItem->SetPattern(smDPat->Pat);
			smLoader[cnt].lpItem->lpDinaPattern = smDPat;
			strcpy_s(smLoader[cnt].lpItem->szModelName, smDPat->szPatName);
			smLoader[cnt].lpItem->DisplayFlag = TRUE;
		}
		smLoader[cnt].Result = TRUE;

		if (smDPat && lpPatOld)
			smDPAT_Delete(lpPatOld);

		smLoader[cnt].lpItem->PatLoading = FALSE;
	}


	if (smLoader[cnt].lpChar)
	{
		smDPat = 0;
		smDPat2 = 0;

		smLoader[cnt].lpChar->PatLoading = TRUE;


		lpPatOld = smLoader[cnt].lpChar->lpDinaPattern;
		lpPatOld2 = smLoader[cnt].lpChar->lpDinaPattern2;

		smDPat = smPattern.LoadCharactor(smLoader[cnt].szLoadName);

		if (smDPat)
		{



			smLoader[cnt].lpChar->DisplayFlag = 0;
			smLoader[cnt].lpChar->SetDinaPattern(smDPat);
			smLoader[cnt].lpChar->SetMotionFromCode(CHRMOTION_STATE_STAND);



			smLoader[cnt].lpChar->Flag = 1;
			strcpy_s(smLoader[cnt].lpChar->smCharInfo.szModelName, smDPat->szPatName);

			smLoader[cnt].lpChar->smCharInfo.szModelName2[0] = 0;

			if (smDPat->lpModelInfo->szSubModelFile[0])
			{

				smDPat2 = smPattern.LoadCharactor(smDPat->lpModelInfo->szSubModelFile);
			}
			else
			{

				if (smLoader[cnt].szLoadName2[0])
				{
					smDPat2 = smPattern.LoadCharactor(smLoader[cnt].szLoadName2);
					strcpy_s(smLoader[cnt].lpChar->smCharInfo.szModelName2, smDPat2->szPatName);
				}
			}

			smLoader[cnt].lpChar->SetDinaPattern2(smDPat2);


			if (renderDevice.IsDevice() && (smDPat->UseCount == 1 || (smDPat2 && smDPat2->UseCount == 1)))
			{






				if (smDPat && smDPat->Pat)
				{
					smDPat->Pat->smMaterialGroup->ReadTextures();
					smDPat->Pat->smMaterialGroup->CheckMatreialTextureSwap();
				}
				if (smDPat2 && smDPat2->Pat)
				{
					smDPat2->Pat->smMaterialGroup->ReadTextures();
					smDPat2->Pat->smMaterialGroup->CheckMatreialTextureSwap();
				}
			}

			smLoader[cnt].lpChar->DisplayFlag = TRUE;
		}
		else
		{

			//LOG(LOG_DEBUG, "SetDisconnectFlag: 7");
			DisconnectFlag = dwPlayTime;
		}
		smLoader[cnt].Result = TRUE;

		if (lpPatOld)
			smDPAT_Delete(lpPatOld);

		if (lpPatOld2)
			smDPAT_Delete(lpPatOld2);


		smLoader[cnt].lpChar->PatLoading = FALSE;
	}

	smLoaderCnt++;


	LeaveCriticalSection(&cLoadSection);

	ThreadLoaderStats = FALSE;


	return TRUE;
}


int CreateLoaderThread()
{




	smLoaderThreadProc(0);

	return FALSE;
}


int InitLoader()
{
	smLoaderCnt = 0;
	smLoaderEnd = 0;

	return TRUE;
}


int InitPatterns()
{
	smBipPattern.Init();
	smPattern.Init();

	smPattern.BipPattern = &smBipPattern;


	InitLoader();


	InitializeCriticalSection(&cLoadSection);

	return TRUE;
}


int ClosePatterns()
{
	smBipPattern.Close();
	smPattern.Close();

	return TRUE;
}


int smDPAT_Delete(smDPAT *dPat)
{
	if (dPat->UseCount > 0)
	{
		dPat->UseCount--;



		if (dPat->lpTalkLink && dPat->UseCount == 0)
			smDPAT_Delete(dPat->lpTalkLink);


		if (dPat->smDinaLink && dPat->UseCount == 0)
			smDPAT_Delete(dPat->smDinaLink);

		if (dPat->UseCount <= 0)
		{
			delete dPat->Pat;
			dPat->Pat = 0;
			if (dPat->lpModelInfo)
			{
				delete dPat->lpModelInfo;
				dPat->lpModelInfo = 0;
			}
		}
	}
	return NULL;
}


int SetLoadPattern(smCHAR *smChar, char *szName, char *szName2, POINT3D *Posi, POINT3D *Angle)
{
	smDPAT	*smDPat;
	smDPAT	*smDPat2;

	smDPat = 0;
	smDPat2 = 0;

	smDPat = smPattern.LoadCharactor(szName);

	if (smDPat)
	{
		smChar->Init();
		if (Posi && Angle)
			smChar->SetPosi(Posi->x, Posi->y, Posi->z, Angle->x, Angle->y, Angle->z);

		smChar->SetDinaPattern(smDPat);
		smChar->ChangeMotion(0);
		smChar->DisplayFlag = TRUE;
		strcpy_s(smChar->smCharInfo.szModelName, smDPat->szPatName);

		smChar->smCharInfo.szModelName2[0] = 0;

		if (smDPat->lpModelInfo->szSubModelFile[0])
		{

			smDPat2 = smPattern.LoadCharactor(smDPat->lpModelInfo->szSubModelFile);
		}
		else
		{

			if (szName2 && szName2[0])
			{
				smDPat2 = smPattern.LoadCharactor(szName2);
				strcpy_s(smChar->smCharInfo.szModelName2, smDPat2->szPatName);
			}
		}


		smChar->SetDinaPattern2(smDPat2);


		return TRUE;
	}

	return FALSE;
}


int SetLoadPattern(smCHAR *smChar, char *szName, POINT3D *Posi, POINT3D *Angle)
{
	return SetLoadPattern(smChar, szName, 0, Posi, Angle);
}





smCHAR::smCHAR()
{
	Pattern = 0;
	Pattern2 = 0;

	Init();
}

smCHAR::~smCHAR()
{

}

void smCHAR::Init()
{


	TalkPattern = NULL;
	TalkFrame = TalkSoundSum = 0;
	lpTalkModelParent = NULL;
	lpTalkMotionInfo = NULL;

	::ZeroMemory(&FrameInfo, sizeof(SMotionStEndInfo));


	frame = 0;
	action = 0;
	Flag = 0;
	pX = pY = pZ = 0;
	Angle.x = Angle.y = Angle.z = 0;
	MoveFlag = FALSE;
	FrameCnt = 0;
	Counter = 0;

	frame = 0;

	ZeroMemory(PlayBuff, sizeof(smPLAYBUFF) * PLAYBUFF_SIZE);
	PlayBuffCnt = 0;
	PlayBuffPosi_End = 0;

	TransMinCnt = 8;
	TransLevel = 0;
	TransDelayMax = PLAYCOUNT_PER_SECOND * 5;

	lpDinaPattern = 0;
	lpDinaPattern2 = 0;
	PatLoading = 0;

	lpDinaLeftPattern = 0;
	lpDinaRightPattern = 0;

	HvLeftHand.PatTool = 0;
	HvRightHand.PatTool = 0;
	HvLeftHand.dwItemCode = 0;
	HvRightHand.dwItemCode = 0;

	HvLeftHand.ColorBlink = 0;
	HvRightHand.ColorBlink = 0;






	wStickItems[0] = -1;
	wStickItems[1] = -1;
	wStickItems[2] = -1;
	wStickItems[3] = -1;

	DisplayFlag = 0;
	AnimDispMode = 0;
	PatDispMode = DISP_MODE_PATMAIN;
	MotionSelectFrame = 0;

	smMotionInfo = 0;



	smMotionInfo2 = 0;



	DisplayTools = TRUE;

	dwTarget = FALSE;

	if (smStage) lpStage = smStage;


	ptNextTarget.x = 0;
	ptNextTarget.y = 0;
	ptNextTarget.z = 0;


	lpTargetPlayInfo = 0;
	lpTargetChar = 0;

	lpMasterPlayInfo = 0;


	smCharInfo.Life[0] = 100;
	smCharInfo.Life[1] = 100;
	smCharInfo.State = 0;


	dwLastTransTime = dwPlayTime;

	FrameCounter = 0;

	PatWidth = 0;
	PatHeight = 0;
	PatSizeLevel = 0;

	FrameStep = 80;
	MoveSpeed = 250;
	AttackSpeed = fONE;

	lpExt1 = 0;
	lpExt2 = 0;
	lpExt3 = 0;
	lpExt4 = 0;


	dwChatMessageTimer = dwPlayTime;

	srTransBuffSize = 0;

	dwActionItemCode = 0;

	ShootingMode = FALSE;
	ShootingFlag = FALSE;
	chrAttackTarget = 0;

	AttackToolRange = 0;
	AttackAnger = 0;
	AttackIce = 0;
	OnStageField = -1;
	OnStageFieldState = 0;
	OldMotionState = 0;

	OverLapPosi = 0;
	OverLapPosi2 = 0;
	lpCharOverLap = 0;

	TargetMoveCount = 0;

	AttackObjBip = 0;

	NearPlayCount = 256;
	AttackCritcal = 0;

	AutoMoveStep = 0;

	LevelLog = 0;

	dwNextMotionCode = 0;
	PosBeginCount = 0;

	EnableStateBar = 0;
	DisplayAlpha = 0;
	RendAlpha = 0;
	AttackSkil = 0;
	AttackEffect = 0;

	dwDispAppSkill = 0;
	dwDispAppSkillMask = 0;

	HoSkillCode = 0;
	PartyFlag = 0;
	dwAttackPlayTime = 0;

	PlaySlowCount = 0;
	PlaySlowSpeed = 0;
	PlayStunCount = 0;
	PlayStopCount = 0;
	PlayStunType = 0;
	ServerCode = 0;

	PlayWisp[1] = 0;

	PlayHolyMind[1] = 0;
	PlayHolyPower[1] = 0;
	PlayPoison[1] = 0;
	DispPoison = 0;
	PlayHolyIncantation[1] = 0;
	PlayVanish = 0;
	PlayCurseQuest = 0;
	PlayVague = 0;
	PlayDistortion = 0;
	PlayCurseLazy = 0;
	PlayInvincible = 0;


	dwForceOfNatureTime = 0;
	dwHallOfValhallaTime = 0;


	AttackSkillRange = 0;

	RecvExp = 0;

	sAddColorEffect[0] = 0;
	sAddColorEffect[1] = 0;
	sAddColorEffect[2] = 0;
	sAddColorEffect[3] = 0;

	((DWORD *)smCharInfo.wPlayClass)[0] = 0;

	RenderLatter = FALSE;
	dwUpdateCharInfoTime = 0;

	dwTradeMsgCode = 0;
	EventAttackCount = 0;

	dwClanManageBit = 0;

	lpAttackDamageList = 0;
	lpAttackDamageList_BlessCastle = 0;

	dwForceOrbCode = 0;
	dwForceOrbTime = 0;


	dwLifeBoosterCode = 0;
	dwLifeBoosterTime = 0;

	dwManaBoosterCode = 0;
	dwManaBoosterTime = 0;

	dwStaminaBoosterCode = 0;
	dwStaminaBoosterTime = 0;


	dwSkillDelayCode = 0;
	dwSkillDelayTime = 0;

	dwLinkObjectCode = 0;
	lpLinkPlayInfo = 0;
	lpLinkChar = 0;

	PkMode_CharState = 0;
	dwClanCode = 0;
	UseObject_VirtualLife = 0;


#ifndef _W_SERVER


	WeaponEffect = 0;
	dwWeaponEffectTime = 0;

	ClanInfoNum = -1;
	Clan_CastleMasterFlag = 0;
	BlessCrown = 0;
	dwClanInfoTime = 0;
	TryAttackCount = 0;

	((DWORD *)sBlessCastle_Damage)[0] = 0;


#else
	dwTargetLockTime = 0;

	lpCompulsionPlayInfo = 0;
	dwCompulsionTime = 0;

	dwAssassinEyeTime = 0;
	AssassinEyeParam = 0;


	sMoveStepCount[0] = 0;
	sMoveStepCount[1] = 0;

	DontMoveFlag = 0;

	Clan_CastleMasterFlag = 0;
	BlessCrown = 0;

#endif

}

int smCHAR::Close()
{
	Flag = 0;

	if (lpDinaPattern2)
	{
		AddRemoveDynPattern(lpDinaPattern2);

		lpDinaPattern2 = 0;
	}



	if (lpDinaPattern)
	{
		AddRemoveDynPattern(lpDinaPattern);

		lpDinaPattern = 0;
	}

	if (lpDinaLeftPattern)
	{
		AddRemoveDynPattern(lpDinaLeftPattern);

		lpDinaLeftPattern = 0;
	}

	if (lpDinaRightPattern)
	{
		AddRemoveDynPattern(lpDinaRightPattern);

		lpDinaRightPattern = 0;
	}


	Pattern = 0;
	Pattern2 = 0;

	HvLeftHand.PatTool = 0;
	HvRightHand.PatTool = 0;

	smMotionInfo = 0;
	smMotionInfo2 = 0;

	dwDispAppSkill = 0;

	if (lpAttackDamageList)
	{
		delete	lpAttackDamageList;
		lpAttackDamageList = 0;
	}

	return TRUE;
}


int smCHAR::GetToolBipPoint(smCHARTOOL *ChrTool, int *nX, int *nY, int *nZ)
{

	smMATRIX *mWorld;
	POINT3D angle;
	int tx, ty, tz;
	smOBJ3D	*lpObj;
	int pframe;
	int rx, ry, rz;

	if (!DisplayFlag) return FALSE;

	tx = 0;
	ty = 0;
	tz = 0;

	memcpy(&angle, &Angle, sizeof(POINT3D));
	angle.y = (-angle.y + ANGLE_180)&ANGCLIP;
	lpObj = ChrTool->ObjBip;

	if (lpObj)
	{
		mWorld = &lpObj->mWorld;
		pframe = frame;

		AnimObjectTree(lpObj, pframe, angle.x, angle.y, angle.z);

		rx = tx * mWorld->_11 +
			ty * mWorld->_21 +
			tz * mWorld->_31;

		ry = tx * mWorld->_12 +
			ty * mWorld->_22 +
			tz * mWorld->_32;

		rz = tx * mWorld->_13 +
			ty * mWorld->_23 +
			tz * mWorld->_33;

		*nX = pX + (rx >> FLOATNS) + mWorld->_41;
		*nZ = pZ + (ry >> FLOATNS) + mWorld->_42;
		*nY = pY + (rz >> FLOATNS) + mWorld->_43;

		return TRUE;
	}

	return FALSE;
}


int smCHAR::GetAttackPoint(int *nX, int *nY, int *nZ)
{

	smMATRIX *mWorld;
	POINT3D angle;
	int tx, ty, tz;
	smCHARTOOL *ChrTool = 0;
	smOBJ3D	*lpObj;
	int pframe;
	int rx, ry, rz;

	ChrTool = &HvRightHand;

	if (!DisplayFlag) return FALSE;

	tx = 0;
	ty = 0;

	if (ChrTool->PatTool)
		tz = ChrTool->SizeMax / 2;
	else
		tz = 0;

	memcpy(&angle, &Angle, sizeof(POINT3D));
	angle.y = (-angle.y + ANGLE_180)&ANGCLIP;

	if (AttackObjBip && !tz && !ShootingMode)
		lpObj = AttackObjBip;
	else
		lpObj = ChrTool->ObjBip;

	if (lpObj)
	{
		mWorld = &lpObj->mWorld;
		pframe = frame;

		AnimObjectTree(lpObj, pframe, angle.x, angle.y, angle.z);

		rx = tx * mWorld->_11 +
			ty * mWorld->_21 +
			tz * mWorld->_31;

		ry = tx * mWorld->_12 +
			ty * mWorld->_22 +
			tz * mWorld->_32;

		rz = tx * mWorld->_13 +
			ty * mWorld->_23 +
			tz * mWorld->_33;

		*nX = pX + (rx >> FLOATNS) + mWorld->_41;
		*nZ = pZ + (ry >> FLOATNS) + mWorld->_42;
		*nY = pY + (rz >> FLOATNS) + mWorld->_43;

		return TRUE;
	}

	return FALSE;
}


int DefendChance(int iDefenseRating, int iAttackRating)
{
	// Chance to block = ((def - atr) / def) * 100
	if (iDefenseRating <= iAttackRating)
		return 10;

	double def = iDefenseRating;
	double def_rtg = iDefenseRating - iAttackRating;
	double mul = 100.0f;
	double ret = (def_rtg / def) * mul;

	if (ret > 90.0f)
		return 90;
	if (ret < 10.0f)
		return 10;

	return (int)ret;
}

int smCHAR::SetPattern(smPAT3D *pat)
{
	smPAT3D *AnimPat;

	Pattern = pat;

	if (pat->TmParent)
		AnimPat = pat->TmParent;
	else
		AnimPat = pat;

	HvRightHand.ObjBip = AnimPat->GetObjectFromName(szBipName_RightHand);


	if ((HvLeftHand.dwItemCode&sinITEM_MASK2) == sinDS1)
		HvLeftHand.ObjBip = AnimPat->GetObjectFromName(szBipName_Shield);
	else
		HvLeftHand.ObjBip = AnimPat->GetObjectFromName(szBipName_LeftHand);

	BackObjBip[0] = AnimPat->GetObjectFromName(szBipName_BackSpine);
	BackObjBip[1] = AnimPat->GetObjectFromName(szBipName_BackSpineBow);
	BackObjBip[2] = AnimPat->GetObjectFromName(szBipName_BackSpineCross);
	ShieldObjBip = AnimPat->GetObjectFromName(szBipName_Shield2);




	AttackObjBip = 0;


	if (smCharInfo.JOB_CODE == 3 || smCharInfo.JOB_CODE == 5)
		AttackObjBip = AnimPat->GetObjectFromName(szBipName_LFoot);

	if (smCharInfo.JOB_CODE == 7)
		AttackObjBip = AnimPat->GetObjectFromName(szBipName_Head);

	AnimPattern = AnimPat;

	PatHeight = pat->SizeHeight;
	PatWidth = (pat->SizeWidth * 160) >> FLOATNS;



	return TRUE;
}


int smCHAR::SetPattern2(smPAT3D *pat)
{


	Pattern2 = pat;

	return TRUE;
}


DWORD	dwItemCodeFromVillage[] = {
	sinWC1 | sin01 , sinWC1 | sin02 , sinWC1 | sin03 , sinWC1 | sin04 , sinWC1 | sin05 ,
	sinWC1 | sin06 , sinWC1 | sin07 , sinWC1 | sin08 , sinWC1 | sin09 , sinWC1 | sin10 ,
	sinWC1 | sin11 , sinWC1 | sin12 , sinWC1 | sin13 , sinWC1 | sin14 , sinWC1 | sin15 ,
	sinWC1 | sin16 , sinWC1 | sin17 , sinWC1 | sin18 , sinWC1 | sin19 , sinWC1 | sin20 ,
	sinWC1 | sin21 , sinWC1 | sin22 , sinWC1 | sin23 ,

	sinWM1 | sin01 , sinWM1 | sin02 , sinWM1 | sin03 , sinWM1 | sin06 ,
	sinWS2 | sin01 , sinWS2 | sin02 , sinWS2 | sin03 ,

	sinWS1 | sin02, sinWS1 | sin03,
	sinWS1 | sin09,
	0
};


DWORD	dwItemCodeFromVillage_Bow[] = {
	0
};


DWORD	dwItemCodeFromVillage_Cross[] = {
	sinWS1 | sin01,sinWS1 | sin05,sinWS1 | sin06, sinWS1 | sin07,
	sinWS1 | sin11, sinWS1 | sin12,sinWS1 | sin14, sinWS1 | sin15,sinWS1 | sin16,

	0
};

int smCHAR::SetTool(DWORD dwItemCode, int hvPosi)
{
	//LOG(LOG_DEBUG, "smCHAR::SetTool: dwItemCode: %d   hvPosi: %d ", dwItemCode, hvPosi);
	char szToolMeshName[64];
	int cnt, szX, szN;

	szX = szN = 0;

	if (smCharInfo.State != smCHAR_STATE_USER && PkMode_CharState != smCHAR_STATE_USER)
		return FALSE;

	if (dwItemCode)
		sinGetItemInfo(dwItemCode, szToolMeshName);

	switch (hvPosi)
	{
	case hvPOSI_RHAND:
		if (HvRightHand.ObjBip)
		{
			if (lpDinaRightPattern)
			{
				AddRemoveDynPattern(lpDinaRightPattern);

				lpDinaRightPattern = 0;
			}
			if (dwItemCode)
			{
				lpDinaRightPattern = smPattern.LoadCharactor(szToolMeshName);
				if (lpDinaRightPattern)
				{
					HvRightHand.PatTool = lpDinaRightPattern->Pat;
					for (cnt = 0; cnt < lpDinaRightPattern->Pat->nObj3d; cnt++)
					{
						if (szX < lpDinaRightPattern->Pat->obj3d[cnt]->maxY)
							szX = lpDinaRightPattern->Pat->obj3d[cnt]->maxY;
						if (szN < lpDinaRightPattern->Pat->obj3d[cnt]->minY)
							szN = lpDinaRightPattern->Pat->obj3d[cnt]->minY;
					}
					HvRightHand.SizeMax = szX;
					HvRightHand.SizeMin = szN;
					HvRightHand.dwItemCode = dwItemCode;

					HvRightHand.ObjBip = AnimPattern->GetObjectFromName(szBipName_RightHand);
					dwActionItemCode = dwItemCode;


					wStickItems[smPLAYBUFF_ITEM_RIGHT] = GetSinItemNumFromCode(dwItemCode);
				}
				else
				{
					HvRightHand.PatTool = 0;
					HvRightHand.dwItemCode = 0;
					wStickItems[smPLAYBUFF_ITEM_RIGHT] = -1;
				}
			}
			else
			{
				HvRightHand.PatTool = 0;
				HvRightHand.dwItemCode = 0;
				wStickItems[smPLAYBUFF_ITEM_RIGHT] = -1;
			}
		}
		else
			return FALSE;
		break;

	case hvPOSI_LHAND:
		if (HvLeftHand.ObjBip)
		{
			if (lpDinaLeftPattern)
			{
				AddRemoveDynPattern(lpDinaLeftPattern);

				lpDinaLeftPattern = 0;
			}
			if (dwItemCode)
			{

				lpDinaLeftPattern = smPattern.LoadCharactor(szToolMeshName);
				if (lpDinaLeftPattern)
				{
					HvLeftHand.PatTool = lpDinaLeftPattern->Pat;
					for (cnt = 0; cnt < lpDinaLeftPattern->Pat->nObj3d; cnt++)
					{
						if (szX < lpDinaLeftPattern->Pat->obj3d[cnt]->maxY)
							szX = lpDinaLeftPattern->Pat->obj3d[cnt]->maxY;
						if (szN < lpDinaLeftPattern->Pat->obj3d[cnt]->minY)
							szN = lpDinaLeftPattern->Pat->obj3d[cnt]->minY;
					}
					HvLeftHand.SizeMax = szX;
					HvLeftHand.SizeMin = szN;
					HvLeftHand.dwItemCode = dwItemCode;
					wStickItems[smPLAYBUFF_ITEM_LEFT] = GetSinItemNumFromCode(dwItemCode);


					if ((dwItemCode&sinITEM_MASK2) == sinDS1 || (dwItemCode&sinITEM_MASK2) == sinOM1)
					{
						if ((dwItemCode&sinITEM_MASK2) == sinDS1)
						{

							HvLeftHand.ObjBip = AnimPattern->GetObjectFromName(szBipName_Shield);
						}
						else
						{

							HvLeftHand.PatTool = 0;
							HvLeftHand.dwItemCode = 0;
							wStickItems[smPLAYBUFF_ITEM_LEFT] = -1;
						}
					}
					else
					{
						HvLeftHand.ObjBip = AnimPattern->GetObjectFromName(szBipName_LeftHand);
						dwActionItemCode = dwItemCode;

					}
				}
				else
				{
					HvLeftHand.PatTool = 0;
					HvLeftHand.dwItemCode = 0;
					wStickItems[smPLAYBUFF_ITEM_LEFT] = -1;
				}
			}
			else
			{
				HvLeftHand.PatTool = 0;
				HvLeftHand.dwItemCode = 0;
				wStickItems[smPLAYBUFF_ITEM_LEFT] = -1;
			}

		}
		else
			return FALSE;
		break;
	}

	if (dwActionItemCode)
	{
		if (dwActionItemCode != HvLeftHand.dwItemCode && dwActionItemCode != HvRightHand.dwItemCode)
		{
			dwActionItemCode = 0;

		}


		if (dwActionItemCode == HvLeftHand.dwItemCode)
			AttackToolRange = (HvLeftHand.SizeMax * 200) >> 8;

		if (dwActionItemCode == HvRightHand.dwItemCode)
			AttackToolRange = (HvRightHand.SizeMax * 200) >> 8;

		cnt = 0;
		dwItemSetting = 1;

		while (1)
		{
			if (dwItemCodeFromVillage[cnt] == 0) break;
			if (dwItemCodeFromVillage[cnt] == dwActionItemCode)
			{
				dwItemSetting = 0;
				break;
			}
			cnt++;
		}

		cnt = 0;
		while (1)
		{
			if (dwItemCodeFromVillage_Bow[cnt] == 0) break;
			if (dwItemCodeFromVillage_Bow[cnt] == dwActionItemCode)
			{
				dwItemSetting = 2;
				break;
			}
			cnt++;
		}

		cnt = 0;
		while (1)
		{
			if (dwItemCodeFromVillage_Cross[cnt] == 0) break;
			if (dwItemCodeFromVillage_Cross[cnt] == dwActionItemCode)
			{
				dwItemSetting = 3;
				break;
			}
			cnt++;
		}

	}
	else
		AttackToolRange = 0;


	if ((dwActionItemCode&sinITEM_MASK2) == sinWS1 || (dwActionItemCode&sinITEM_MASK2) == sinWT1 ||
		((dwActionItemCode&sinITEM_MASK2) == sinWM1 && (smCharInfo.JOB_CODE == 7 || smCharInfo.JOB_CODE == 8)))
	{

		ShootingMode = TRUE;
	}
	else
		ShootingMode = FALSE;

	if ((smCharInfo.State == smCHAR_STATE_USER || PkMode_CharState == smCHAR_STATE_USER) && dwItemCode == dwActionItemCode)
	{
		if (MotionInfo->State != CHRMOTION_STATE_DEAD && MotionInfo->State != CHRMOTION_STATE_DAMAGE &&
			MotionInfo->State != CHRMOTION_STATE_RESTART)
		{
			SetMotionFromCode(MotionInfo->State);
			AttackCritcal = -1;
		}

		if (dwItemCode)
		{

			for (cnt = 0; cnt < MAX_ITEM; cnt++)
			{
				if (sItem[cnt].CODE == dwItemCode)
				{
					if (sItem[cnt].Class == ITEM_CLASS_WEAPON_TWO && !ShootingMode)
						dwActionItemTwoHand = TRUE;
					else
						dwActionItemTwoHand = FALSE;
					break;
				}
			}
		}
	}


	DisplayTools = TRUE;
	return TRUE;
}

int smCHAR::SetPosi(int x, int y, int z, int angX, int angY, int angZ)
{
	int sy;

	pX = x;
	pZ = z;
	pY = y;

	if (y == 0 && lpStage)
		pY = lpStage->GetHeight(pX, pZ);

	if (pY == 0)
	{

		if (smGameStage[0])
			pY = smGameStage[0]->GetHeight(pX, pZ);

		if (smGameStage[1])
		{
			sy = smGameStage[1]->GetHeight(pX, pZ);
			if (pY < sy) pY = sy;
		}
	}


	pY -= 2 * fONE;

	PHeight = pY;

	Angle.x = angX;
	Angle.y = angY;
	Angle.z = angZ;

	return TRUE;
}

int smCHAR::SetTargetPosi(int x, int z)
{

	tx = x << FLOATNS;
	tz = z << FLOATNS;
	MoveFlag = TRUE;

	Angle.y = GetRadian2D(pX, pZ, tx, tz);

	if (ActionPattern == 0)
	{
		if (MoveMode)
			SetMotionFromCode(CHRMOTION_STATE_RUN);
		else
			SetMotionFromCode(CHRMOTION_STATE_WALK);
	}

	return Angle.y;
}

int smCHAR::SetTargetPosi2(int x, int z)
{

	tx = x << FLOATNS;
	tz = z << FLOATNS;

	Angle.y = GetRadian2D(pX, pZ, tx, tz);

	return Angle.y;
}


int smCHAR::SetNextTarget(int x, int y, int z)
{
	ptNextTarget.x = x;
	ptNextTarget.y = y;
	ptNextTarget.z = z;

	return TRUE;
}

int smCHAR::SetAction(int nAction)
{


	if (nAction == 0) MoveFlag = FALSE;

	return TRUE;

}


int	smCHAR::SetSmoking(int level)
{

	GetMoveLocation(4 * fONE, 0, 0, 0, Angle.y, 0);
	StartEffect(pX + GeoResult_X, pY + 8 * fONE, pZ + GeoResult_Z, 20, 20, EFFECT_DUST1);

	GetMoveLocation(-4 * fONE, 0, 0, 0, Angle.y, 0);
	StartEffect(pX + GeoResult_X, pY + 8 * fONE, pZ + GeoResult_Z, 20, 20, EFFECT_DUST1);

	return TRUE;


}


int smCHAR::MoveAngle2(int step)
{
	int x, z, y;
	int he, hy;
	int OldStageField;
	POINT3D MovePosi;
	int MovLevel[2];

	WaterHeight = CLIP_OUT;

#ifndef _W_SERVER

	if (smConfig.getSecurity() >= AccountTypes::SEC_VIP && VRKeyBuff['N'])
	{
		x = pX + (((GetSin[Angle.y&ANGCLIP] >> FLOATNS) * step) >> FLOATNS);
		z = pZ + (((GetCos[Angle.y&ANGCLIP] >> FLOATNS) * step) >> FLOATNS);
		y = pY;

		pY = y;
		pX = x;
		pZ = z;

		return TRUE;
	}
#else
	if (DontMoveFlag)
		return FALSE;
#endif

	POINT3D Posi;

	he = 0;

	Posi.x = x = pX;
	Posi.y = y = pY;
	Posi.z = z = pZ;

	OldStageField = OnStageField;
	OnStageField = -1;

	if (step == 0 || PHeight < y)
	{
		if (lpStage)
		{
			he = lpStage->GetFloorHeight(x, y, z, Pattern->SizeHeight);
		}
		else
		{
			if (smGameStage[0])
			{
				he = smGameStage[0]->GetFloorHeight(x, y, z, Pattern->SizeHeight);
				OnStageField = 0;
			}

			if (smGameStage[1])
			{
				hy = smGameStage[1]->GetFloorHeight(x, y, z, Pattern->SizeHeight);
				if (he < hy)
				{
					he = hy;
					OnStageField = 1;
				}
			}
		}
		if (he != CLIP_OUT)
			y = he;
		else
			y = -80 * fONE;

		if ((pY - y) > 8 * fONE)
		{
			if (MotionInfo->State != CHRMOTION_STATE_FALLDOWN && (pY - y) > 32 * fONE)
			{
				FallHeight = pY - y;
				SetMotionFromCode(CHRMOTION_STATE_FALLDOWN);
			}
			PHeight = y;
			pY -= 8 * fONE;
		}
		else
		{
			pY = y;
			PHeight = y;
			if (MotionInfo->State == CHRMOTION_STATE_FALLDOWN)
			{
				if (FallHeight > 200 * fONE)
					SetMotionFromCode(CHRMOTION_STATE_FALLDAMAGE);
				else
					SetMotionFromCode(CHRMOTION_STATE_FALLSTAND);

				SetSmoking(0);

			}
		}
		return TRUE;
	}
	else
	{
		if (lpStage && lpStage->CheckNextMove(&Posi, &Angle, &MovePosi, step, Pattern->SizeWidth, Pattern->SizeHeight, OverLapPosi2) > 0)
		{
			x = MovePosi.x;
			y = MovePosi.y;
			z = MovePosi.z;
		}
		else
		{
			MovLevel[0] = 0;
			MovLevel[1] = 0;

			if (smGameStage[0] && (MovLevel[0] = smGameStage[0]->CheckNextMove(&Posi, &Angle, &MovePosi, step, Pattern->SizeWidth, Pattern->SizeHeight, OverLapPosi2)) > 0)
			{

				if (smStage_WaterChk != CLIP_OUT)
					WaterHeight = smStage_WaterChk;


				if (StageField[0]->LimitLevel <= smCharInfo.Level)
				{

					OnStageField = 0;

					he = MovePosi.y;
					x = MovePosi.x;
					y = MovePosi.y;
					z = MovePosi.z;
				}

			}
			if (smGameStage[1] && (MovLevel[1] = smGameStage[1]->CheckNextMove(&Posi, &Angle, &MovePosi, step, Pattern->SizeWidth, Pattern->SizeHeight, OverLapPosi2) > 0))
			{

				if (smStage_WaterChk != CLIP_OUT)
					WaterHeight = smStage_WaterChk;

				if (StageField[1]->LimitLevel <= smCharInfo.Level)
				{
					if (MovLevel[0] && abs(he - MovePosi.y) < fONE * 8)
					{
						if (MovLevel[0] > MovLevel[1])
						{
							x = MovePosi.x;
							y = MovePosi.y;
							z = MovePosi.z;
							OnStageField = 1;
						}
					}
					else
					{
						if (he < MovePosi.y)
						{
							x = MovePosi.x;
							y = MovePosi.y;
							z = MovePosi.z;
							OnStageField = 1;
						}
					}
				}
			}
		}
	}

	pX = x;
	pZ = z;

	if ((pY - y) > 8 * fONE)
	{

		if (MotionInfo->State != CHRMOTION_STATE_FALLDOWN && (pY - y) > 32 * fONE)
		{
			FallHeight = pY - y;
			SetMotionFromCode(CHRMOTION_STATE_FALLDOWN);
		}

		PHeight = y;
		pY -= 8 * fONE;
	}
	else
	{
		pY = y;
		PHeight = y;
		if (MotionInfo->State == CHRMOTION_STATE_FALLDOWN)
		{
			if (FallHeight > 200 * fONE)
				SetMotionFromCode(CHRMOTION_STATE_FALLDAMAGE);
			else
				SetMotionFromCode(CHRMOTION_STATE_FALLSTAND);

			SetSmoking(0);

		}
	}

	if (OnStageField >= 0 && OldStageField != OnStageField)
	{
		OnStageFieldState = StageField[OnStageField]->State;
		if (OldStageField < 0 || OnStageFieldState != StageField[OldStageField]->State)
		{
			SetMotionFromCode(MotionInfo->State);
		}
	}
	if (OnStageField < 0)
		OnStageField = OldStageField;

	return TRUE;
}


int smCHAR::MoveAngle(int step)
{
	return	MoveAngle2(step*fONE);
}

int smCHAR::SetDinaPattern(smDPAT *lpDPat)
{
	TalkPattern = NULL;
	TalkFrame = TalkSoundSum = 0;
	lpTalkModelParent = NULL;
	lpTalkMotionInfo = NULL;

	if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
	{
		Debug_TalkZoomMode = 0;
		Debug_TalkRepeatMode = 0;
		Debug_TalkRepeatModeType = -1;
	}


	lpDinaPattern = lpDPat;
	smMotionInfo = lpDinaPattern->lpModelInfo;
	SetPattern(lpDPat->Pat);

	SetMotionFromCode(CHRMOTION_STATE_STAND);

	return TRUE;
}

int smCHAR::SetDinaPattern2(smDPAT	*lpDPat)
{
	lpDinaPattern2 = lpDPat;

	if (lpDinaPattern2)
	{
		smMotionInfo2 = lpDinaPattern2->lpModelInfo;
		SetPattern2(lpDPat->Pat);

		if (Pattern->TmParent == Pattern2->TmParent)
		{
			AnimDispMode = 0;
			PatDispMode = DISP_MODE_PATMAIN | DISP_MODE_PATSUB;
		}
		else
		{
			AnimDispMode = 1;
			PatDispMode = DISP_MODE_PATMAIN;
		}
	}
	else
	{
		AnimDispMode = 0;
		PatDispMode = DISP_MODE_PATMAIN;
		SetPattern2(0);
	}



	if (lpDinaPattern->lpTalkLink)
	{
		PatDispMode |= DISP_MODE_PATTALK;
		TalkPattern = lpDinaPattern->lpTalkLink->Pat;
	}
	else if (lpDinaPattern2 && lpDinaPattern2->lpTalkLink)
	{
		PatDispMode |= DISP_MODE_PATTALK;
		TalkPattern = lpDinaPattern2->lpTalkLink->Pat;
	}

	if (TalkPattern && (PatDispMode & DISP_MODE_PATTALK))
	{
		if (smMotionInfo->szTalkLinkFile[0])
			lpTalkModelParent = smMotionInfo;
		else if (smMotionInfo2 && smMotionInfo2->szTalkLinkFile[0])
			lpTalkModelParent = smMotionInfo2;
		else
		{

			PatDispMode &= (~DISP_MODE_PATTALK);
			TalkPattern = NULL;
		}
	}


	return TRUE;
}


int smCHAR::ChangeMotion(int Motion, int DpMode)
{

	if (DpMode)
	{

		if (MotionSelectFrame)
		{
			MotionInfo = &smMotionInfo2->MotionInfo[Motion];
			PatDispMode = DISP_MODE_PATSUB;
		}
		else
		{
			MotionInfo = &smMotionInfo->MotionInfo[Motion];
			PatDispMode = DISP_MODE_PATMAIN;
		}
	}
	else
	{

		if (AnimDispMode)
			PatDispMode = DISP_MODE_PATMAIN;

		MotionInfo = &smMotionInfo->MotionInfo[Motion];
		MotionSelectFrame = 0;
	}

	frame = MotionInfo->StartFrame * 160;
	action = Motion;
	FrameCounter = 0;

	AttackSkil = 0;
	HideWeapon = 0;
	MotionLoop = 0;

	dwEventFrameExt[0] = 0;
	dwEventFrameExt[1] = 0;
	dwEventFrameExt[2] = 0;
	dwEventFrameExt[3] = 0;



	FrameInfo.StartFrame = frame;
	FrameInfo.EndFrame = MotionInfo->EndFrame * 160;


	return TRUE;
}



int smCHAR::AutoChangeTalkMotion(int TalkModeType)
{
	if (TalkPattern == NULL)
		return 0;

	int TalkCnt = 0;
	if (lpTalkModelParent->TalkMotionRate[CHRMOTION_EXT])
	{
		TalkCnt = rand() % 100;
		TalkCnt = lpTalkModelParent->TalkMotionRateCnt[TalkModeType][TalkCnt];
	}
	else
		TalkCnt = rand() % lpTalkModelParent->TalkMotionCount;

	lpTalkMotionInfo = &lpTalkModelParent->TalkMotionInfo[TalkCnt];
	TalkFrame = lpTalkMotionInfo->StartFrame * 160;

	return 1;
}



int smCHAR::FindMotionCountFromCode(DWORD MotionCode)
{
	int FindCnt = 0;

	for (DWORD cnt = 0; cnt < smMotionInfo->MotionCount; cnt++)
	{
		if (smMotionInfo->MotionInfo[cnt].State == MotionCode)
			FindCnt++;
	}

	return FindCnt;
}


int smCHAR::SetMotionFromCode(DWORD MotionCode)
{
	int cnt, cnt2, itcnt;
	int FoundNum[64];
	int FindCnt;

	int FoundNum2[64];
	int FindCnt2;
	int StageVillage;
	int	dwActItemCode;
	int	atSkill = 0;
	int	skillCode;
	BYTE	bSkill;

	DWORD	dwJobCodeMask;

	DWORD dwFindCode;

	smMODELINFO	*lpMotionInfo;

	if (smCharInfo.JOB_CODE && smCharInfo.JOB_CODE < 16)
		dwJobCodeMask = BitMaskJobNames[smCharInfo.JOB_CODE - 1].dwBitMask;
	else
		dwJobCodeMask = 0;


	FindCnt = 0;
	FindCnt2 = 0;
	MotionSelectFrame = 0;

	dwActItemCode = dwActionItemCode;

	if (OnStageField >= 0)
	{
		if (StageField[OnStageField]->State == FIELD_STATE_VILLAGE)
		{
			StageVillage = 1;
			dwActItemCode = 0;
		}
		else
			StageVillage = 2;
	}
	else
	{
#ifdef _W_SERVER
		StageVillage = 3;
#else
		if (GameMode == 1) StageVillage = 1;
		else StageVillage = 3;
#endif
	}


	lpMotionInfo = smMotionInfo;

	if (MotionCode == CHRMOTION_STATE_SKILL && AttackSkil)
	{
		atSkill = AttackSkil;
	}

	for (cnt = 0; cnt < (int)smMotionInfo->MotionCount; cnt++)
	{
		if (smMotionInfo->MotionInfo[cnt].State == MotionCode &&
			(!smMotionInfo->MotionInfo[cnt].MapPosition || (smMotionInfo->MotionInfo[cnt].MapPosition&StageVillage)) &&
			(!smMotionInfo->MotionInfo[cnt].dwJobCodeBit || !dwJobCodeMask ||
			(smMotionInfo->MotionInfo[cnt].dwJobCodeBit&dwJobCodeMask)))
		{

			if (atSkill)
			{
				cnt2 = 0;
				skillCode = atSkill & 0xFF;
				while (1)
				{
					bSkill = smMotionInfo->MotionInfo[cnt].SkillCodeList[cnt2];
					if (bSkill == 0) break;
					if (SkillDataCode[bSkill].dwPlaySkillCode == skillCode)
					{
						break;
					}
					cnt2++;
				}
				if (bSkill)
				{
					FoundNum[FindCnt++] = cnt;
					if (FindCnt >= 32) break;
				}
			}
			else
			{
				FoundNum[FindCnt++] = cnt;
				if (FindCnt >= 32) break;
			}
		}
	}


	if (FindCnt == 0 && AnimDispMode && lpDinaPattern2)
	{
		for (cnt = 0; cnt < (int)smMotionInfo2->MotionCount; cnt++)
		{
			if (smMotionInfo2->MotionInfo[cnt].State == MotionCode &&
				(!smMotionInfo2->MotionInfo[cnt].MapPosition || (smMotionInfo2->MotionInfo[cnt].MapPosition&StageVillage)))
			{
				FoundNum[FindCnt++] = cnt;
				if (FindCnt >= 32) break;
			}
		}

		if (FindCnt)
		{
			MotionSelectFrame = 1;
			lpMotionInfo = smMotionInfo2;
		}
	}

	int hand = ITEM_CLASS_WEAPON_ONE;

	if (dwActItemCode)
	{
		for (int i = 0; i < MAX_ITEM; i++)
		{
			if (sItem[i].CODE == dwActionItemCode)
			{
				hand = sItem[i].Class;
				break;
			}
		}
	}


	for (cnt = 0; cnt < FindCnt; cnt++)
	{
		itcnt = lpMotionInfo->MotionInfo[FoundNum[cnt]].ItemCodeCount;
		if (itcnt == 0)
		{
			FoundNum2[FindCnt2++] = FoundNum[cnt];
		}
		else
		{
			if (dwActItemCode)
			{
				for (int cnt2 = 0; cnt2 < itcnt; cnt2++)
				{
					DWORD dwFindCode = lpMotionInfo->MotionInfo[FoundNum[cnt]].ItemCodeList[cnt2];

					switch (dwActItemCode & 0xFFFF0000)
					{
					case sinWA1:
					{
						if (hand == ITEM_CLASS_WEAPON_ONE)
						{
							dwActItemCode = sinWA1 | sin01;
						}
						else
						{
							dwActItemCode = sinWA1 | sin05;
						}
					}
					break;

					case sinWC1:
					{
						dwActItemCode = sinWC1 | sin01;
					}
					break;

					case sinWH1:
					{
						if (hand == ITEM_CLASS_WEAPON_ONE)
						{
							dwActItemCode = sinWA1 | sin01;
						}
						else
						{
							dwActItemCode = sinWA1 | sin31;
						}
					}
					break;

					case sinWM1:
					{
						if (hand == ITEM_CLASS_WEAPON_ONE)
						{
							dwActItemCode = sinWM1 | sin01;
						}
						else
						{
							dwActItemCode = sinWM1 | sin04;
						}
					}
					break;

					case sinWP1:
					{
						if (hand == ITEM_CLASS_WEAPON_ONE)
						{
							dwActItemCode = sinWP1 | sin01;
						}
						else
						{
							dwActItemCode = sinWP1 | sin04;
						}
					}
					break;

					case sinWS1:
					{
						switch (dwActItemCode & 0x0000FFFF)
						{
						case sin04:
						case sin08:
						case sin10:
						case sin13:
						case sin17:
						case sin20:
							dwActItemCode = sinWS1 | sin04;
							break;

						default:
							if (hand == ITEM_CLASS_WEAPON_ONE)
							{
								dwActItemCode = sinWS1 | sin02;
							}
							else
							{
								dwActItemCode = sinWS1 | sin01;
							}
							break;
						}
					}
					break;

					case sinWS2:
					{
						if (hand == ITEM_CLASS_WEAPON_ONE)
						{
							dwActItemCode = sinWS2 | sin01;
						}
						else
						{
							dwActItemCode = sinWS2 | sin05;
						}
					}
					break;

					case sinWT1:
					{
						dwActItemCode = sinWT1 | sin01;
					}
					break;

					}

					if (dwActItemCode == (int)sItem[dwFindCode].CODE)
					{
						FoundNum2[FindCnt2++] = FoundNum[cnt];
						break;
					}
				}
			}
			else
			{
				for (cnt2 = 0; cnt2 < itcnt; cnt2++)
				{
					dwFindCode = lpMotionInfo->MotionInfo[FoundNum[cnt]].ItemCodeList[cnt2];
					if (dwFindCode == 0xFF)
					{
						FoundNum2[FindCnt2++] = FoundNum[cnt];
						break;
					}
				}
			}
		}
	}

	if (FindCnt2 == 0)
	{
		if (FindCnt == 1)
			ChangeMotion(FoundNum[0], AnimDispMode);
		else
			if (FindCnt) ChangeMotion(FoundNum[(rand() % FindCnt)], AnimDispMode);

		if (atSkill) AttackSkil = atSkill;

		return NULL;
	}


	if (FindCnt2 == 1) ChangeMotion(FoundNum2[0], AnimDispMode);
	else
		if (FindCnt2) ChangeMotion(FoundNum2[(rand() % FindCnt2)], AnimDispMode);


	if (atSkill) AttackSkil = atSkill;

	return FindCnt;
}


int smCHAR::FindActionFromFrame(int sframe)
{
	DWORD cnt;
	DWORD compFrame;

	compFrame = sframe / 160;

	for (cnt = 0; cnt < smMotionInfo->MotionCount; cnt++)
	{
		if (smMotionInfo->MotionInfo[cnt].StartFrame<compFrame &&
			smMotionInfo->MotionInfo[cnt].EndFrame>compFrame)
			return cnt;
	}

	return -1;
}

int smCHAR::SavePlayBuff()
{

	PlayBuffCnt = (PlayBuffCnt + 1)&PLAYBUFF_MASK;

	PlayBuff[PlayBuffCnt].angle[0] = Angle.x;
	PlayBuff[PlayBuffCnt].angle[1] = Angle.y;
	PlayBuff[PlayBuffCnt].angle[2] = Angle.z;
	PlayBuff[PlayBuffCnt].angle[3] = action;

	PlayBuff[PlayBuffCnt].x = pX;
	PlayBuff[PlayBuffCnt].y = pY;
	PlayBuff[PlayBuffCnt].z = pZ;

	PlayBuff[PlayBuffCnt].frame = (MotionSelectFrame << CHAR_FRAME_SELSHIFT) | frame;

	if (chrAttackTarget)
		PlayBuff[PlayBuffCnt].dwTargetSerial = chrAttackTarget->dwObjectSerial;
	else
		PlayBuff[PlayBuffCnt].dwTargetSerial = NULL;

	memcpy(PlayBuff[PlayBuffCnt].wStickItems, wStickItems, sizeof(short) * 4);

	return PlayBuffCnt;
}


int smCHAR::SavePlayBuff2()
{

	PlayBuffCnt = (PlayBuffCnt + 1)&PLAYBUFF_MASK;

	PlayBuff[PlayBuffCnt].angle[0] = Angle.x;
	PlayBuff[PlayBuffCnt].angle[1] = Angle.y;
	PlayBuff[PlayBuffCnt].angle[2] = Angle.z;
	PlayBuff[PlayBuffCnt].angle[3] = action;

	PlayBuff[PlayBuffCnt].x = pX;
	PlayBuff[PlayBuffCnt].y = pY;
	PlayBuff[PlayBuffCnt].z = pZ;

	PlayBuff[PlayBuffCnt].frame = (MotionSelectFrame << CHAR_FRAME_SELSHIFT) | frame;

	PlayBuff[PlayBuffCnt].dwTargetSerial = NULL;

	if (lpTargetChar)
		PlayBuff[PlayBuffCnt].dwTargetSerial = lpTargetChar->dwObjectSerial;

	if (lpTargetPlayInfo)
		PlayBuff[PlayBuffCnt].dwTargetSerial = lpTargetPlayInfo->dwObjectSerial;

	memcpy(PlayBuff[PlayBuffCnt].wStickItems, wStickItems, sizeof(short) * 4);

	return PlayBuffCnt;
}


int smCHAR::ChangeMoveMode()
{


	if (MoveMode == 0) MoveMode = 1;
	else MoveMode = 0;

	if (MoveFlag)
	{
		if (MoveMode)
			SetMotionFromCode(CHRMOTION_STATE_RUN);
		else
			SetMotionFromCode(CHRMOTION_STATE_WALK);
	}

	return MoveMode;
}


int smCHAR::CheckShootingTest_LastAttackTime(smCHAR *lpChar)
{
	if (dwLastRecvAttackTime<dwPlayTime && (dwLastRecvAttackTime + 2000)>dwPlayTime)
		return TRUE;

	return CheckShootingTest(lpChar);
}


int smCHAR::CheckShootingTest(smCHAR *lpChrTarget)
{

	int x, y, z;
	int he;
	int step;
	int cnt;

	int angX, angY;
	int	SucessCnt;

	if (lpChrTarget->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_TOWER_B)
		return TRUE;

	GetRadian3D(pX, pY, pZ, lpChrTarget->pX, lpChrTarget->pY, lpChrTarget->pZ);
	angX = GeoResult_X;
	angY = GeoResult_Y;

	ShootingPosi.x = pX;
	ShootingPosi.y = pY + 34 * fONE;
	ShootingPosi.z = pZ;

	ShootingAngle.x = angX;
	ShootingAngle.y = angY;
	ShootingAngle.z = 0;

	SucessCnt = 0;

	step = 16 * fONE;

	GetMoveLocation(0, 0, step, angX, angY, 0);

	for (cnt = 0; cnt < 40; cnt++)
	{
		ShootingPosi.x += GeoResult_X;
		ShootingPosi.y += GeoResult_Y;
		ShootingPosi.z += GeoResult_Z;

		he = TRUE;



		if (lpStage)
		{
			he = lpStage->CheckVecImpact(&ShootingPosi, &ShootingAngle, step);
		}
		else
		{
			if (smGameStage[0])
			{
				he = smGameStage[0]->CheckVecImpact(&ShootingPosi, &ShootingAngle, step);
			}

			if (he == TRUE && smGameStage[1])
			{
				he = smGameStage[1]->CheckVecImpact(&ShootingPosi, &ShootingAngle, step);
			}
		}

		if (chrAttackTarget)
		{

			x = abs(ShootingPosi.x - lpChrTarget->pX);
			z = abs(ShootingPosi.z - lpChrTarget->pZ);
			y = abs(ShootingPosi.y - lpChrTarget->pY);

			if (x < 48 * fONE && z < 48 * fONE && y < 64 * fONE && !SucessCnt)
			{

				SucessCnt = cnt + 2;
			}
		}

		if (SucessCnt && SucessCnt < cnt)
			return TRUE;


		if (he == FALSE)
			return FALSE;


	}

	return TRUE;


}


int smCHAR::ShootingMain()
{

	POINT3D Posi, pos;
	int x, y, z;
	int he;
	int ShootSize;
	int step;
	int r, g, b;
	int EffectFlag;

	he = CLIP_OUT;
	EffectFlag = 0;

	ShootSize = 512;


	if ((dwActionItemCode&sinITEM_MASK2) == sinWS1)
		step = 8 * fONE;
	else
		step = 6 * fONE;

	Posi.x = x = ShootingPosi.x;
	Posi.y = y = ShootingPosi.y;
	Posi.z = z = ShootingPosi.z;

	GetMoveLocation(0, 0, step, ShootingAngle.x, ShootingAngle.y, ShootingAngle.z);
	ShootingPosi.x += GeoResult_X;
	ShootingPosi.y += GeoResult_Y;
	ShootingPosi.z += GeoResult_Z;

	if (smCharInfo.State == smCHAR_STATE_USER)
	{

		if (dwActionItemCode == HvRightHand.dwItemCode)
		{
			if (HvRightHand.PatTool && HvRightHand.ColorBlink && !HvRightHand.EffectKind)
			{

				r = (HvRightHand.sColors[SMC_R] >> 1) + 128;
				g = (HvRightHand.sColors[SMC_G] >> 1) + 128;
				b = (HvRightHand.sColors[SMC_B] >> 1) + 128;

				StartEffect(ShootingPosi.x, ShootingPosi.y, ShootingPosi.z,
					r, g, b, 255, EFFECT_PARTICLE_BOW1);

				EffectFlag++;
			}
		}
		if (dwActionItemCode == HvLeftHand.dwItemCode)
		{
			if (HvLeftHand.PatTool && HvLeftHand.ColorBlink && !HvLeftHand.EffectKind)
			{

				r = (HvLeftHand.sColors[SMC_R] >> 1) + 128;
				g = (HvLeftHand.sColors[SMC_G] >> 1) + 128;
				b = (HvLeftHand.sColors[SMC_B] >> 1) + 128;

				StartEffect(ShootingPosi.x, ShootingPosi.y, ShootingPosi.z,
					r, g, b, 255, EFFECT_PARTICLE_BOW1);

				EffectFlag++;
			}
		}

		switch (ShootingKind)
		{
		case SKILL_PLAY_FARINA:

			sinEffect_Farina_Particle(&ShootingPosi);
			break;
		}
	}



	if (ShootingCount > 60 * 2)
	{
		ShootingFlag = FALSE;
	}

	ShootingCount++;

	if (ShootingFlag > 1 && chrAttackTarget)
	{
		ShootingFlag++;
		if (ShootingFlag > 8) ShootingFlag = FALSE;

		if (EffectFlag)
		{
			StartEffect(chrAttackTarget->pX, ShootingPosi.y, chrAttackTarget->pZ,
				r, g, b, 255, EFFECT_PARTICLE_BOW1);
		}
		return TRUE;
	}

	if (ShootingFlag == 1 && chrAttackTarget && AttackCritcal >= 0)
	{

		x = abs(ShootingPosi.x - chrAttackTarget->pX);
		z = abs(ShootingPosi.z - chrAttackTarget->pZ);
		y = abs(ShootingPosi.y - chrAttackTarget->pY);

		if (x < 64 * fONE && z < 64 * fONE && y < 80 * fONE)
		{
			ShootingFlag++;


			if (ShootingKind == SKILL_PLAY_FARINA)
			{

				Posi.x = chrAttackTarget->pX;
				Posi.y = chrAttackTarget->pY + 22 * fONE;
				Posi.z = chrAttackTarget->pZ;
				sinEffect_SkillHit(SKILL_FARINA, &Posi);
				SetDynLight(chrAttackTarget->pX, chrAttackTarget->pY + 22 * fONE, chrAttackTarget->pZ, 100, 0, 0, 0, 400);
				PlayWaponSoundDirect(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 16);
			}
			else
			{
				if (WeaponEffect)
				{
					pos.x = chrAttackTarget->pX;
					pos.y = chrAttackTarget->pY + 22 * fONE;
					pos.z = chrAttackTarget->pZ;

					switch (WeaponEffect)
					{
					case (sITEMINFO_LIGHTING + 1):
						AssaParticle_LightHit1(&pos);
						SetDynLight(x, y, z, 0, 0, 100, 0, 400);
						if ((rand() % 2) == 0)
							SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_LIGHTNING1, pX, pY, pZ);
						else
							SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_LIGHTNING2, pX, pY, pZ);
						break;
					case (sITEMINFO_FIRE + 1):
						AssaParticle_FireHit1(&pos);
						SetDynLight(x, y, z, 100, 0, 0, 0, 400);
						if ((rand() % 2) == 0)
							SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_FIRE1, pX, pY, pZ);
						else
							SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_FIRE2, pX, pY, pZ);
						break;
					case (sITEMINFO_ICE + 1):
						AssaParticle_IceHit1(&pos);
						SetDynLight(x, y, z, 0, 0, 100, 0, 400);
						if ((rand() % 2) == 0)
							SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_ICE1, pX, pY, pZ);
						else
							SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_ICE2, pX, pY, pZ);
						break;
					}
				}
				else
				{

					if (AttackCritcal)
					{
						StartEffect(chrAttackTarget->pX, chrAttackTarget->pY + 22 * fONE, chrAttackTarget->pZ, EFFECT_CRITICAL_HIT1);
						SetDynLight(chrAttackTarget->pX, chrAttackTarget->pY + 22 * fONE, chrAttackTarget->pZ, 100, 0, 0, 0, 400);
						PlayWaponSoundDirect(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 16);
					}
					else
					{
						StartEffect(chrAttackTarget->pX, chrAttackTarget->pY + 22 * fONE, chrAttackTarget->pZ, EFFECT_NORMAL_HIT1);
						SetDynLight(chrAttackTarget->pX, chrAttackTarget->pY + 22 * fONE, chrAttackTarget->pZ, 40, 0, 0, 0, 400);
					}

					if (dwForceOrbTime > dwPlayTime)
					{
						pos.x = chrAttackTarget->pX;
						pos.y = chrAttackTarget->pY + 22 * fONE;
						pos.z = chrAttackTarget->pZ;

						AssaParticle_ShelltomWeaponHit(&pos);
					}

				}
			}


			PlayWaponSoundDirect(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 14);


			if (this == lpCurPlayer && AttackExp > 0)
			{


				AttackExp = 0;
			}

		}

	}

	return TRUE;
}


extern int MatLight[2];

#define SERVER_CHAR_FRAME_STEP			320
#define SERVER_CHAR_SKIP				4

#define VIEW_HIGH_DIST	36864			
#define VIEW_MID_DIST	102400			


int bb_r, bb_g, bb_b, bb_a;

int SetRenderBlinkColor(smCHARTOOL *smCharTool)
{
	int BlinkMsk;
	int BlinkTime;
	int bTime;
	int Blink, r, g, b, a;

	bb_r = smRender.Color_R;
	bb_g = smRender.Color_G;
	bb_b = smRender.Color_B;
	bb_a = smRender.Color_A;

	if (smCharTool->ColorBlink == 0) return NULL;

	Blink = smCharTool->ColorBlink;
	r = smCharTool->sColors[SMC_R];
	g = smCharTool->sColors[SMC_G];
	b = smCharTool->sColors[SMC_B];
	a = smCharTool->sColors[SMC_A];

	if (Blink < 0)
	{
		smRender.Color_R += r;
		smRender.Color_G += g;
		smRender.Color_B += b;
		smRender.Color_A += a;

		return NULL;
	}

	BlinkTime = (1 << Blink);
	BlinkMsk = BlinkTime - 1;

	bTime = dwPlayTime & BlinkMsk;

	if (dwPlayTime&BlinkTime)
	{
		smRender.Color_R += (bTime*r) >> Blink;
		smRender.Color_G += (bTime*g) >> Blink;
		smRender.Color_B += (bTime*b) >> Blink;
		if (a < 0) smRender.Color_A += (bTime*a) >> Blink;
	}
	else
	{
		bTime = BlinkMsk - bTime;
		smRender.Color_R += (bTime*r) >> Blink;
		smRender.Color_G += (bTime*g) >> Blink;
		smRender.Color_B += (bTime*b) >> Blink;
		if (a < 0) smRender.Color_A += (bTime*a) >> Blink;
	}

	if (a > 0)
		smRender.Color_A -= a;

	bTime = (bTime*fONE) >> Blink;
	if (!bTime) bTime = 1;

	if (smCharTool->TexMixCode >= 0)
	{
		SetItem2PassTexture(smCharTool->TexMixCode, smCharTool->TexScroll);
	}

	return  bTime;
}

int RestoreRenderBlinkColor()
{
	smRender.Color_R = bb_r;
	smRender.Color_G = bb_g;
	smRender.Color_B = bb_b;
	smRender.Color_A = bb_a;

	SetItem2PassTexture(-1);

	return TRUE;
}



int smCHAR::ChargingSkill()
{
	DWORD dwFrame;

	if (this != lpCurPlayer) return FALSE;

	dwFrame = frame - MotionInfo->StartFrame * 160;

	if (SkillChargingFlag && MouseButton[1] == 0) SkillChargingFlag = 0;

	switch (AttackSkil & 0xFF)
	{
	case SKILL_PLAY_PHOENIX_SHOT:
		if (dwFrame >= MotionInfo->EventFrame[0] && dwFrame < MotionInfo->EventFrame[1])
		{
			if (SkillChargingFlag == 0)
			{
				frame = MotionInfo->StartFrame * 160 + MotionInfo->EventFrame[1];
				ChargingFlag = 1;
			}
		}
		break;
	case SKILL_PLAY_CHARGING_STRIKE:
		if (dwFrame >= MotionInfo->EventFrame[0] && dwFrame < MotionInfo->EventFrame[1])
		{
			if (SkillChargingFlag == 0)
			{
				frame = MotionInfo->StartFrame * 160 + MotionInfo->EventFrame[1];
				ChargingFlag = 1;
			}
		}
		break;
	}

	return TRUE;
}


int smCHAR::EventAttack(int Flag)
{
	int shootFlag;
	DWORD compFrame;
	int x, y, z;
	int wp;
	DWORD NearFrame;
	POINT3D	pos, pos2;

	int	cnt, ChrCnt;
	smCHAR *lpCharList[32];



	ChargingSkill();

	if (AttackSkil > 0 || (smCharInfo.State == smCHAR_STATE_ENEMY && MotionInfo->State == CHRMOTION_STATE_SKILL))
	{
		if (Flag || ((MotionInfo->State == CHRMOTION_STATE_ATTACK || MotionInfo->State == CHRMOTION_STATE_SKILL) && MotionInfo->EventFrame[0]))
		{
			compFrame = frame - (MotionInfo->StartFrame * 160);

			if ((MotionInfo->EventFrame[0] > (compFrame - FrameStep) && MotionInfo->EventFrame[0] <= compFrame) ||
				(MotionInfo->EventFrame[1] && MotionInfo->EventFrame[1] > (compFrame - FrameStep) && MotionInfo->EventFrame[1] <= compFrame) ||
				(MotionInfo->EventFrame[2] && MotionInfo->EventFrame[2] > (compFrame - FrameStep) && MotionInfo->EventFrame[2] <= compFrame) ||
				(MotionInfo->EventFrame[3] && MotionInfo->EventFrame[3] > (compFrame - FrameStep) && MotionInfo->EventFrame[3] <= compFrame) ||

				(dwEventFrameExt[0] && dwEventFrameExt[0] > (frame - FrameStep) && dwEventFrameExt[0] <= frame) ||
				(dwEventFrameExt[1] && dwEventFrameExt[1] > (frame - FrameStep) && dwEventFrameExt[1] <= frame) ||
				(dwEventFrameExt[2] && dwEventFrameExt[2] > (frame - FrameStep) && dwEventFrameExt[2] <= frame) ||
				(dwEventFrameExt[3] && dwEventFrameExt[3] > (frame - FrameStep) && dwEventFrameExt[3] <= frame) ||

				(MotionEvent == 0 && MotionInfo->EventFrame[0] <= compFrame))
			{


				MotionEvent++;


				if (this == lpCurPlayer)
				{


					AttackExp = 0;

					if (chrAttackTarget && abs(chrAttackTarget->smCharInfo.Level - smCharInfo.Level) <= AGING_SUB_LEVEL)
					{

						if (AttackCritcal == TRUE)
							sinCheckAgingLevel(SIN_AGING_CRITICAL, false);
						else
							sinCheckAgingLevel(SIN_AGING_ATTACK, false);
					}
				}

				if (EventSkill() == TRUE)
					return TRUE;
			}
		}
	}


	if (MotionInfo->State != CHRMOTION_STATE_ATTACK && MotionInfo->State != CHRMOTION_STATE_SKILL) return FALSE;

	if (ActionPattern)
		shootFlag = 0;
	else
	{
		shootFlag = ShootingFlag;
	}

	if (MotionInfo->EventFrame[0])
	{
		compFrame = frame - (MotionInfo->StartFrame * 160);
		NearFrame = compFrame - FrameStep;

		if (Flag || (MotionInfo->EventFrame[0] > NearFrame && MotionInfo->EventFrame[0] <= compFrame) ||
			(MotionInfo->EventFrame[1] && MotionInfo->EventFrame[1] > NearFrame && MotionInfo->EventFrame[1] <= compFrame))
		{

			MotionEvent++;

			if (smCharInfo.State == smCHAR_STATE_ENEMY)
			{
				CharPlaySound(this);
			}
			else
			{
				WeaponPlaySound(this);
				if (AttackCritcal < 0) return FALSE;
			}


			if (this == lpCurPlayer && AttackExp > 0)
			{





				AttackExp = 0;



				if (chrAttackTarget && abs(chrAttackTarget->smCharInfo.Level - smCharInfo.Level) <= AGING_SUB_LEVEL)
				{

					if (AttackCritcal == TRUE)
						sinCheckAgingLevel(SIN_AGING_CRITICAL, false);
					else
						sinCheckAgingLevel(SIN_AGING_ATTACK, false);
				}

			}


			if (chrAttackTarget == lpCurPlayer)
			{

				AttackMotionCountUp();
			}

			switch (smCharInfo.dwCharSoundCode)
			{
			case snCHAR_SOUND_MUSHROOM:

				StartEffect(pX, pY + (24 * fONE), pZ, EFFECT_GAS1);
				break;

			case snCHAR_SOUND_IMP:

				if (chrAttackTarget)
				{
					if (CheckShootingTest_LastAttackTime(chrAttackTarget) ||
						CheckLocateBox(pX, pY, pZ, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 80 * fONE))
					{

						GetMoveLocation(0, 0, 10 * fONE, 0, Angle.y, 0);
						x = pX + GeoResult_X;
						y = pY + 8 * fONE;
						z = pZ + GeoResult_Z;

						if (smCharInfo.Level < 15)
						{

							StartEffectMonsterDest(x, y, z,
								chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ,
								MONSTER_IMP_SHOT1);
						}
						else
						{

							StartEffectMonsterDest(x, y, z,
								chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ,
								MONSTER_MEPHIT_SHOT1);
						}
					}
					else
					{
						ResetAttackTrans();
					}
				}
				break;

			case snCHAR_SOUND_SHADOW:

				if (chrAttackTarget)
				{
					if (CheckShootingTest_LastAttackTime(chrAttackTarget) ||
						CheckLocateBox(pX, pY, pZ, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 80 * fONE))
					{

						StartEffectMonsterDest(pX, pY + 32 * fONE, pZ,
							chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ,
							MONSTER_IMP_SHOT3);
					}
					else
					{
						ResetAttackTrans();
					}
				}
				break;

			case snCHAR_SOUND_FIGON:

				if (chrAttackTarget)
				{
					if (CheckShootingTest_LastAttackTime(chrAttackTarget) ||
						CheckLocateBox(pX, pY, pZ, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 80 * fONE))
					{

						StartEffectMonsterDest(pX, pY + 32 * fONE, pZ,
							chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ,
							MONSTER_PIGON_SHOT1);
					}
					else
					{
						ResetAttackTrans();
					}
				}
				break;

			case snCHAR_SOUND_WEB:

				if (chrAttackTarget)
				{
					if (CheckShootingTest_LastAttackTime(chrAttackTarget) ||
						CheckLocateBox(pX, pY, pZ, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 80 * fONE))
					{

						GetMoveLocation(0, 0, 32 * fONE, 0, Angle.y, 0);
						StartEffectMonsterDest(pX + GeoResult_X, pY + 12 * fONE, pZ + GeoResult_Z,
							chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ,
							MONSTER_WEB_SHOT1);
					}
					else
					{
						ResetAttackTrans();
					}
				}
				break;

			case snCHAR_SOUND_SKELETONRANGE:

				if (chrAttackTarget)
				{
					if (CheckShootingTest_LastAttackTime(chrAttackTarget))
					{
						ShootingPosi.x = pX;
						ShootingPosi.y = pY + 28 * fONE;
						ShootingPosi.z = pZ;
						GetRadian3D(pX, pY + 28 * fONE, pZ, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ);
						ShootingAngle.x = GeoResult_X;
						ShootingAngle.y = GeoResult_Y;
						ShootingAngle.z = Angle.z;
						ShootingFlag = TRUE;
						ShootingCount = 0;
						dwActionItemCode = sinWS1;
					}
					else
					{
						ResetAttackTrans();
					}
				}
				break;

			case snCHAR_SOUND_WOLVERLIN:

				if (chrAttackTarget)
				{
					GetMoveLocation(0, 0, 50 * fONE, 0, Angle.y, 0);
					x = pX + GeoResult_X;
					z = pZ + GeoResult_Z;
					y = pY + 18 * fONE;


					StartEffectMonster(x, y, z, MONSTER_PIGON_PARTICLE1);
					StartEffectMonster(x, y, z, MONSTER_PIGON_PARTICLE1);
					StartEffectMonster(x, y, z, MONSTER_PIGON_PARTICLE1);
					StartEffectMonster(x, y, z, MONSTER_PIGON_PARTICLE1);

				}
				break;

			case snCHAR_SOUND_EGAN:

				if (chrAttackTarget)
				{
					if (CheckShootingTest_LastAttackTime(chrAttackTarget))
					{
						GetMoveLocation(0, 0, 10 * fONE, 0, Angle.y, 0);
						x = pX + GeoResult_X;
						y = pY + 8 * fONE;
						z = pZ + GeoResult_Z;

						StartEffectMonsterDest(x, y, z,
							chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ,
							MONSTER_IMP_SHOT1);
					}
					else
					{
						ResetAttackTrans();
					}
				}
				break;

			case snCHAR_SOUND_MUTANTTREE:

				if (chrAttackTarget)
				{
					if (CheckShootingTest_LastAttackTime(chrAttackTarget))
					{
						GetMoveLocation(0, 0, 24 * fONE, 0, Angle.y, 0);
						x = pX + GeoResult_X;
						y = pY + 8 * fONE;
						z = pZ + GeoResult_Z;

						sinEffect_MutentTree_Attack(this, chrAttackTarget);
					}
					else
					{
						ResetAttackTrans();
					}
				}
				break;

			case snCHAR_SOUND_HULK:

				if (chrAttackTarget)
				{
					GetMoveLocation(0, 0, 54 * fONE, 0, Angle.y, 0);
					StartEffectMonster(pX + GeoResult_X, pY + 48 * fONE, pZ + GeoResult_Z, MONSTER_HULK_HIT1);
				}
				break;


			case snCHAR_SOUND_DMACHINE:

				if (chrAttackTarget)
				{
					GetMoveLocation(0, 30 * fONE, 10 * fONE, 0, Angle.y, 0);
					StartEffectMonsterDest(pX + GeoResult_X, pY + GeoResult_Y, pZ + GeoResult_Z,
						chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ,
						MONSTER_DMACHINE_MISSILE1);
				}
				break;

			case snCHAR_SOUND_TURTLE_CANNON:

				if (chrAttackTarget)
				{
					ParkAssaParticle_MonsterTurtleCanonNormal(this, chrAttackTarget);
				}
				break;

			case snCHAR_SOUND_SUCCUBUS:

				if (chrAttackTarget)
				{

					if (smCharInfo.Level <= 75)
						wp = MONSTER_SERQBUS_SHOT1;
					else if (smCharInfo.Level < 80)
						wp = MONSTER_SERQBUS_SHOT2;
					else
						wp = MONSTER_SERQBUS_SHOT3;

					GetMoveLocation(0, 20 * fONE, 20 * fONE, 0, Angle.y, 0);
					StartEffectMonsterDest(pX + GeoResult_X, pY + GeoResult_Y, pZ + GeoResult_Z,
						chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ,
						wp);
				}
				break;

			case snCHAR_SOUND_STYGIANLORD:

				if (chrAttackTarget)
				{


					StartEffectMonsterDest(pX, pY, pZ,
						chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ,
						0, Angle.y, 0, MONSTER_STYGIANLORD_SHOT1);
				}
				break;

			case snCHAR_SOUND_MOKOVA:
			case snCHAR_SOUND_OMICRON:

				if (chrAttackTarget)
				{
					GetMoveLocation(0, 0, 68 * fONE, 0, Angle.y, 0);
					StartEffectMonster(pX + GeoResult_X, pY + 22 * fONE, pZ + GeoResult_Z, MONSTER_HULK_HIT1);
				}
				break;

			case snCHAR_SOUND_GUARDIAN_SAINT:

				AssaParticleClanMonsterHit2(this);
				break;

			case snCHAR_SOUND_HYPERMACHINE:
				if (chrAttackTarget)
				{
					pos.x = chrAttackTarget->pX;
					pos.y = chrAttackTarget->pY + 20 * fONE;
					pos.z = chrAttackTarget->pZ;
					AssaParticle_MonsterIronHyperHit1(this, &pos);
				}
				break;

			case snCHAR_SOUND_MOUNTAIN:
				AssaParticle_MonsterIronMountainHit1(this);
				break;

			case snCHAR_SOUND_TOWERGOLEM:
				AssaParticle_MonsterIronTowerGolemHit1(this);
				break;

			case snCHAR_SOUND_OMU:
				AssaParticle_MonsterIronOmuHit1(this);
				break;

			case snCHAR_SOUND_CHAINGOLEM:
			case snCHAR_SOUND_DEADZONE:
			case snCHAR_SOUND_IRONFIST:
			case snCHAR_SOUND_MORGON:
			case snCHAR_SOUND_RAMPAGE:
			case snCHAR_SOUND_VAMPRICBEE:
			case snCHAR_SOUND_IRONGUARD:
			case snCHAR_SOUND_GORGON:
			case snCHAR_SOUND_HOBOGOLEM:

				GetMoveLocation(0, 0, 54 * fONE, 0, Angle.y, 0);
				pos.x = pX + GeoResult_X;
				pos.y = pY + GeoResult_Y + 32 * fONE;
				pos.z = pZ + GeoResult_Z;
				AssaParticle_MonsterIronHit1(&pos);
				break;

			case snCHAR_SOUND_GOBLINSHAMAN:
				if (chrAttackTarget)
				{
					ParkAssaParticle_MummyShot(this, chrAttackTarget);
				}
				break;

			case snCHAR_SOUND_GROTESQUE:
				GetMoveLocation(0, 0, 75 * fONE, 0, Angle.y, 0);
				pos.x = pX + GeoResult_X;
				pos.y = pY + GeoResult_Y + 32 * fONE;
				pos.z = pZ + GeoResult_Z;
				AssaParticle_MonsterIronHit1(&pos);
				break;


			case snCHAR_SOUND_AVELIN_ARCHER:
				if (chrAttackTarget)
				{
					AssaParticle_MonsterAvelArcher(this, chrAttackTarget);
				}
				break;

			case snCHAR_SOUND_AVELIN_QUEEN:
				if (chrAttackTarget)
				{
					AssaParticle_MonsterAvelQueen(this, chrAttackTarget);
				}
				break;

			case snCHAR_SOUND_RUNICGUARDIAN:
				if (chrAttackTarget)
				{
					AssaParticle_MonsterRunicGuardianShot(this, chrAttackTarget);
				}
				break;

			case snCHAR_SOUND_BABEL:

				if (chrAttackTarget)
				{
					if (Trans_SplashCharList.code == OpCode::OPCODE_ATTACK_SLASH_LIST && Trans_SplashCharList.TargetCount > 1)
					{
						ChrCnt = 0;
						for (cnt = 0; cnt < Trans_SplashCharList.TargetCount; cnt++)
						{
							if (cnt >= 32) break;
							lpCharList[ChrCnt] = FindChrPlayer(Trans_SplashCharList.dwTarObjectSerial[cnt]);
							if (lpCharList[ChrCnt]) ChrCnt++;
						}
						AssaParticle_MonsterRunicGuardianBossHit(this, chrAttackTarget, lpCharList, ChrCnt);
						Trans_SplashCharList.code = 0;
					}
					else
						AssaParticle_MonsterRunicGuardianBossHit(this, chrAttackTarget);
				}
				break;

			case snCHAR_SOUND_SADNESS:
				if (chrAttackTarget)
				{
					AssaParticle_MonsterIronSadNessHit1(this);
				}
				break;


			case snCHAR_SOUND_WATERMELON:
				if (chrAttackTarget)
				{
					GetMoveLocation(0, 0, 54 * fONE, 0, Angle.y, 0);
					pos.x = pX + GeoResult_X;
					pos.y = pY + GeoResult_Y + 32 * fONE;
					pos.z = pZ + GeoResult_Z;
					AssaParticle_MonsterIronHit1(&pos);
				}
				break;



			case snCHAR_SOUND_COLDEYE:
				if (chrAttackTarget)
				{
					GetMoveLocation(0, 0, 24 * fONE, 0, Angle.y, 0);
					pos.x = pX + GeoResult_X;
					pos.y = pY + 64 * fONE;
					pos.z = pZ + GeoResult_Z;
					pos2.x = chrAttackTarget->pX;
					pos2.y = chrAttackTarget->pY + 64 * fONE;
					pos2.z = chrAttackTarget->pZ;
					ParkAssaParticle_ColdEye(&pos, &pos2);
				}
				break;

			case snCHAR_SOUND_FROZEN:
				if (chrAttackTarget)
				{
					ParkAssaParticle_MistIceBolt(this, chrAttackTarget);
				}
				break;

			case snCHAR_SOUND_FROST:
				if (chrAttackTarget && MotionInfo->KeyCode == 'U')
				{
					ParksinSkillEffect_AcientPiercing(this);
				}
				break;

			case snCHAR_SOUND_CHAOSCARA:
				if (chrAttackTarget)
				{
					ParkAssaParticle_ChaosKara1(chrAttackTarget);
				}
				break;

			case snCHAR_SOUND_DEATHKNIGHT:
				if (MotionInfo->KeyCode == 'P')
				{
					if (MotionEvent == 1)
						ParkAssaParticle_Valento1(this);
					else
						ParkAssaParticle_Valento3_1(this);
				}
				else if (MotionInfo->KeyCode == 'L')
				{
					if (MotionEvent == 1)
						ParkAssaParticle_Valento2_1(this);
					else
						ParkAssaParticle_Valento2_2(this);
				}
				break;



			case snCHAR_SOUND_GREATE_GREVEN:
			case snCHAR_SOUND_LIZARDFOLK:
			case snCHAR_SOUND_SPIDER:
			case snCHAR_SOUND_STRIDER:
				if (chrAttackTarget)
				{
					GetMoveLocation(0, 0, 68 * fONE, 0, Angle.y, 0);
					StartEffectMonster(pX + GeoResult_X, pY + 22 * fONE, pZ + GeoResult_Z, MONSTER_HULK_HIT1);
				}
				break;

			case snCHAR_SOUND_M_LORD:
				if (chrAttackTarget)
				{
					ParkAssaParticle_MummyShot(this, chrAttackTarget);
				}
				break;



			case snCHAR_SOUND_IGOLATION:
				if (chrAttackTarget && MotionInfo->KeyCode == 'H')
				{
					GetMoveLocation(0, 0, 68 * fONE, 0, Angle.y, 0);
					StartEffectMonster(pX + GeoResult_X, pY + 22 * fONE, pZ + GeoResult_Z, MONSTER_HULK_HIT1);
				}
				break;
			case snCHAR_SOUND_NIKEN:
				if (chrAttackTarget)
				{
					pos.x = chrAttackTarget->pX;
					pos.y = chrAttackTarget->pY;
					pos.z = chrAttackTarget->pZ;

					AssaParticle_SnailShot(this, &pos);
				}
				break;
			case snCHAR_SOUND_XETAN:
				if (chrAttackTarget && MotionInfo->KeyCode == 'G')
				{
					GetMoveLocation(0, 40 * fONE, 20 * fONE, 0, Angle.y, 0);
					StartEffectMonsterDest(pX + GeoResult_X, pY + GeoResult_Y, pZ + GeoResult_Z,
						chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ,
						MONSTER_SERQBUS_SHOT2);
				}
				break;
			case snCHAR_SOUND_SPRIN:
				if (chrAttackTarget && (MotionInfo->KeyCode == 'G' || MotionInfo->KeyCode == 'H'))
				{
					if (CheckShootingTest_LastAttackTime(chrAttackTarget) ||
						CheckLocateBox(pX, pY, pZ, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 80 * fONE))
					{

						GetMoveLocation(0, 0, 32 * fONE, 0, Angle.y, 0);
						StartEffectMonsterDest(pX + GeoResult_X, pY + 12 * fONE, pZ + GeoResult_Z,
							chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ,
							MONSTER_WEB_SHOT1);
					}
					else
					{
						ResetAttackTrans();
					}
				}
				break;




			case snCHAR_SOUND_BEBECHICK:
				if (chrAttackTarget && (MotionInfo->KeyCode == 'H' || MotionInfo->KeyCode == 'J'))
				{

				}
				break;
			case snCHAR_SOUND_PAPACHICK:
				if (chrAttackTarget && MotionInfo->KeyCode == 'H')
				{

				}
				break;



			case snCHAR_SOUND_KELVEZU:
				if (chrAttackTarget)
				{

					if (MotionInfo->KeyCode != 'P')
					{
						ParkKelvezuNormal2(this);
						ParkKelvezuHit(chrAttackTarget);
					}
					else
					{
						ParkKelvezuNormal1(chrAttackTarget);
					}
				}
				break;



			case snCHAR_SOUND_DARKPHALANX:
				if (chrAttackTarget)
				{
					GetMoveLocation(0, 0, 70 * fONE, 0, Angle.y, 0);
					StartEffectMonster(pX + GeoResult_X, pY + 42 * fONE, pZ + GeoResult_Z, MONSTER_HULK_HIT1);
				}
				break;
			case snCHAR_SOUND_BLOODYKNIGHT:
				if (chrAttackTarget)
				{
					GetMoveLocation(0, 0, 70 * fONE, 0, Angle.y, 0);
					StartEffectMonster(pX + GeoResult_X, pY + 42 * fONE, pZ + GeoResult_Z, MONSTER_HULK_HIT1);
				}
				break;

			case snCHAR_SOUND_CHIMERA:
				if (chrAttackTarget)
				{
					GetMoveLocation(0, 0, 70 * fONE, 0, Angle.y, 0);
					StartEffectMonster(pX + GeoResult_X, pY + 42 * fONE, pZ + GeoResult_Z, MONSTER_HULK_HIT1);
				}
				break;

			case snCHAR_SOUND_FIREWORM:
				if (chrAttackTarget)
				{
					ParkAssaParticle_FireWorm(chrAttackTarget, 0);
				}
				break;
			case snCHAR_SOUND_HELLHOUND:
				if (chrAttackTarget)
				{
					ParkAssaParticle_HellHoundNormal(chrAttackTarget);

					GetMoveLocation(0, 0, 70 * fONE, 0, Angle.y, 0);
					StartEffectMonster(pX + GeoResult_X, pY + 42 * fONE, pZ + GeoResult_Z, MONSTER_HULK_HIT1);
				}
				break;
			case snCHAR_SOUND_DARKMAGE:
				if (chrAttackTarget)
				{
					ParkAssaParticle_DarkMageNormal(this, chrAttackTarget);
				}
				break;
			case snCHAR_SOUND_DARKGUARD:

				if (chrAttackTarget)
				{
					if (CheckShootingTest_LastAttackTime(chrAttackTarget))
					{
						ShootingPosi.x = pX;
						ShootingPosi.y = pY + 38 * fONE;
						ShootingPosi.z = pZ;
						GetRadian3D(pX, pY + 38 * fONE, pZ, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ);
						ShootingAngle.x = GeoResult_X;
						ShootingAngle.y = GeoResult_Y;
						ShootingAngle.z = Angle.z;
						ShootingFlag = TRUE;
						ShootingCount = 0;
						dwActionItemCode = sinWS1;
					}
					else
					{
						ResetAttackTrans();
					}
				}
				break;

			case snCHAR_SOUND_TEMPLEGUARD:
				if (MotionInfo->KeyCode != 'I')
				{
					AssaParticle_MonsterIronMorgonHit(this);
				}
				else
				{
					GetMoveLocation(0, 0, 54 * fONE, 0, Angle.y, 0);
					pos.x = pX + GeoResult_X;
					pos.y = pY + GeoResult_Y + 32 * fONE;
					pos.z = pZ + GeoResult_Z;
					AssaParticle_MonsterIronHit1(&pos);
				}
				break;

			case snCHAR_SOUND_SETO:
				if (chrAttackTarget)
				{
					GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);
					StartEffectMonsterDest(pX + GeoResult_X, pY + GeoResult_Y, pZ + GeoResult_Z,
						chrAttackTarget->pX, chrAttackTarget->pY + 20 * fONE, chrAttackTarget->pZ,
						MONSTER_PIGON_SHOT1);

					if (((dwPlayTime >> 4) & 1) == 0)
						SkillPlaySound(SKILL_SOUND_SKILL_FIREBALL1, pX, pY, pZ);
					else
						SkillPlaySound(SKILL_SOUND_SKILL_FIREBALL2, pX, pY, pZ);
				}
				break;

			case snCHAR_SOUND_KINGSPIDER:
				if (chrAttackTarget)
				{
					GetMoveLocation(0, 0, 70 * fONE, 0, Angle.y, 0);
					StartEffectMonster(pX + GeoResult_X, pY + 42 * fONE, pZ + GeoResult_Z, MONSTER_HULK_HIT1);
				}
				break;



			case snCHAR_SOUND_NPC_MORIF:
				if (chrAttackTarget)
				{

					GetMoveLocation(0, 0, 25 * fONE, 0, Angle.y, 0);
					pos.x = pX + GeoResult_X;
					pos.y = pY + GeoResult_Y + 32 * fONE;
					pos.z = pZ + GeoResult_Z;

					pos2.x = chrAttackTarget->pX;
					pos2.y = chrAttackTarget->pY + 12 * fONE;
					pos2.z = chrAttackTarget->pZ;

					AssaParticle_ShelltomShot(&pos, &pos2, rand() % 3);
				}
				break;

			case snCHAR_SOUND_NPC_MOLLYWOLF:
				if (chrAttackTarget)
				{

					GetMoveLocation(0, 0, 25 * fONE, 0, Angle.y, 0);
					pos.x = pX + GeoResult_X;
					pos.y = pY + GeoResult_Y + 32 * fONE;
					pos.z = pZ + GeoResult_Z;

					pos2.x = chrAttackTarget->pX;
					pos2.y = chrAttackTarget->pY + 12 * fONE;
					pos2.z = chrAttackTarget->pZ;

					AssaParticle_BamShot(&pos, &pos2);
				}
				break;

			case snCHAR_SOUND_WORLDCUP:
				if (chrAttackTarget)
				{
					ParkAssaParticle_WorldCupMonsterAttack(this, chrAttackTarget);
				}
				break;

			case snCHAR_SOUND_S_F_ELEMENTAL:
				if (chrAttackTarget)
				{
					GetMoveLocation(0, 0, 25 * fONE, 0, Angle.y, 0);
					pos.x = pX + GeoResult_X;
					pos.y = pY + GeoResult_Y + 32 * fONE;
					pos.z = pZ + GeoResult_Z;

					pos2.x = chrAttackTarget->pX;
					pos2.y = chrAttackTarget->pY + 12 * fONE;
					pos2.z = chrAttackTarget->pZ;

					SkillArchMageFireElementalShot(&pos, &pos2);
				}
				break;

			case snCHAR_SOUND_S_METALGOLEM:
				if (chrAttackTarget)
				{
					if (!smCharInfo.wPlayClass[1])
						GetMoveLocation(0, 0, 54 * fONE, 0, Angle.y, 0);
					else
						GetMoveLocation(0, 0, 54 * smCharInfo.wPlayClass[1], 0, Angle.y, 0);

					StartEffectMonster(pX + GeoResult_X, pY + 48 * fONE, pZ + GeoResult_Z, MONSTER_HULK_HIT1);
				}
				break;

			case snCHAR_SOUND_S_WOLVERLIN:
				if (chrAttackTarget)
				{
					if (!smCharInfo.wPlayClass[1])
						GetMoveLocation(0, 0, 50 * fONE, 0, Angle.y, 0);
					else
						GetMoveLocation(0, 0, 50 * smCharInfo.wPlayClass[1], 0, Angle.y, 0);

					x = pX + GeoResult_X;
					z = pZ + GeoResult_Z;
					y = pY + 18 * fONE;
					StartEffectMonster(x, y, z, MONSTER_PIGON_PARTICLE1);
					StartEffectMonster(x, y, z, MONSTER_PIGON_PARTICLE1);
					StartEffectMonster(x, y, z, MONSTER_PIGON_PARTICLE1);
					StartEffectMonster(x, y, z, MONSTER_PIGON_PARTICLE1);
				}
				break;

			case snCHAR_SOUND_NPC_SKILLMASTER:
				if (chrAttackTarget && GetAttackPoint(&x, &y, &z) == TRUE)
				{
					StartEffect(x, y, z, EFFECT_CRITICAL_HIT1);
					SetDynLight(x, y, z, 40, 0, 0, 0, 400);
				}
				break;

			case snCHAR_SOUND_NPC_MAGICMASTER:
				if (chrAttackTarget)
				{
					GetMoveLocation(0, 0, 25 * fONE, 0, Angle.y, 0);
					StartEffectMonsterDest(pX + GeoResult_X, pY + 32 * fONE, pZ + GeoResult_Z,
						chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ,
						MONSTER_IMP_SHOT1);
				}
				break;

			case snCHAR_SOUND_CASTLE_CRYSTAL_R:
				if (chrAttackTarget)
				{
					y = GetRadian2D(pX, pZ, chrAttackTarget->pX, chrAttackTarget->pZ);
					GetMoveLocation(0, 0, 16 * fONE, 0, y, 0);
					pos.x = pX + GeoResult_X;
					pos.y = pY + GeoResult_Y + 136 * fONE;
					pos.z = pZ + GeoResult_Z;
					pos2.x = chrAttackTarget->pX;
					pos2.y = chrAttackTarget->pY + 12 * fONE;
					pos2.z = chrAttackTarget->pZ;
					AssaParticle_FireShot(&pos, &pos2);

					if ((rand() % 2) == 0)
						SkillPlaySound(SKILL_SOUND_SKILL_FIREBOLT1, pos.x, pos.y, pos.z);
					else
						SkillPlaySound(SKILL_SOUND_SKILL_FIREBOLT2, pos.x, pos.y, pos.z);

				}
				break;

			case snCHAR_SOUND_CASTLE_CRYSTAL_G:
				if (chrAttackTarget)
				{
					y = GetRadian2D(pX, pZ, chrAttackTarget->pX, chrAttackTarget->pZ);
					GetMoveLocation(0, 0, 16 * fONE, 0, y, 0);
					pos.x = pX + GeoResult_X;
					pos.y = pY + GeoResult_Y + 136 * fONE;
					pos.z = pZ + GeoResult_Z;
					pos2.x = chrAttackTarget->pX;
					pos2.y = chrAttackTarget->pY + 12 * fONE;
					pos2.z = chrAttackTarget->pZ;
					AssaParticle_LightShot(&pos, &pos2);

					if ((rand() % 2) == 0)
						SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_LIGHTNING1, pos.x, pos.y, pos.z);
					else
						SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_LIGHTNING2, pos.x, pos.y, pos.z);
				}
				break;

			case snCHAR_SOUND_CASTLE_CRYSTAL_B:
				if (chrAttackTarget)
				{
					y = GetRadian2D(pX, pZ, chrAttackTarget->pX, chrAttackTarget->pZ);
					GetMoveLocation(0, 0, 16 * fONE, 0, y, 0);
					pos.x = pX + GeoResult_X;
					pos.y = pY + GeoResult_Y + 136 * fONE;
					pos.z = pZ + GeoResult_Z;
					pos2.x = chrAttackTarget->pX;
					pos2.y = chrAttackTarget->pY + 12 * fONE;
					pos2.z = chrAttackTarget->pZ;
					AssaParticle_IceShot(&pos, &pos2);

					if ((rand() % 2) == 0)
						SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_ICE1, pos.x, pos.y, pos.z);
					else
						SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_ICE2, pos.x, pos.y, pos.z);

				}
				break;

			case snCHAR_SOUND_CASTLE_SOLDER_A:
			case snCHAR_SOUND_CASTLE_SOLDER_B:
			case snCHAR_SOUND_CASTLE_SOLDER_C:
				if (chrAttackTarget && GetAttackPoint(&x, &y, &z) == TRUE)
				{
					StartEffect(x, y, z, EFFECT_CRITICAL_HIT1);
					SetDynLight(x, y, z, 40, 0, 0, 0, 400);
				}
				break;
			case snCHAR_SOUND_REVIVED_ARCHER:
				if (chrAttackTarget)
				{
					if (CheckShootingTest_LastAttackTime(chrAttackTarget))
					{
						ShootingPosi.x = pX;
						ShootingPosi.y = pY + 38 * fONE;
						ShootingPosi.z = pZ;
						GetRadian3D(pX, pY + 38 * fONE, pZ, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ);
						ShootingAngle.x = GeoResult_X;
						ShootingAngle.y = GeoResult_Y;
						ShootingAngle.z = Angle.z;
						ShootingFlag = TRUE;
						ShootingCount = 0;
						dwActionItemCode = sinWS1;
					}
					else
					{
						ResetAttackTrans();
					}
				}
				break;

			}

			if (this != lpCurPlayer)
			{
				PlayAttack();
			}
			if (smCharInfo.State != smCHAR_STATE_USER && PkMode_CharState != smCHAR_STATE_USER) return TRUE;

			if (!ShootingMode)
			{
				if (GetAttackPoint(&x, &y, &z) == TRUE)
				{
					if (WeaponEffect)
					{
						pos.x = x;
						pos.y = y;
						pos.z = z;

						switch (WeaponEffect)
						{
						case (sITEMINFO_LIGHTING + 1):
							AssaParticle_LightHit1(&pos);
							SetDynLight(x, y, z, 0, 0, 100, 0, 200);
							if ((rand() % 2) == 0)
								SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_LIGHTNING1, pX, pY, pZ);
							else
								SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_LIGHTNING2, pX, pY, pZ);

							break;
						case (sITEMINFO_FIRE + 1):
							AssaParticle_FireHit1(&pos);
							SetDynLight(x, y, z, 100, 0, 0, 0, 200);
							if ((rand() % 2) == 0)
								SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_FIRE1, pX, pY, pZ);
							else
								SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_FIRE2, pX, pY, pZ);
							break;
						case (sITEMINFO_ICE + 1):
							AssaParticle_IceHit1(&pos);
							SetDynLight(x, y, z, 0, 0, 100, 0, 200);
							if ((rand() % 2) == 0)
								SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_ICE1, pX, pY, pZ);
							else
								SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_ICE2, pX, pY, pZ);
							break;
						}
					}
					else
					{
						if (dwActionItemCode)
						{

							if (AttackCritcal == TRUE || AttackEffect)
							{
								StartEffect(x, y, z, EFFECT_CRITICAL_HIT1);
								SetDynLight(x, y, z, 100, 0, 0, 0, 400);
							}
							else
							{
								StartEffect(x, y, z, EFFECT_NORMAL_HIT1);
								SetDynLight(x, y, z, 40, 0, 0, 0, 400);
							}

						}
						else
						{
							StartEffect(x, y, z, EFFECT_NORMAL_HIT1);
						}

						if (dwForceOrbTime > dwPlayTime)
						{
							pos.x = x;
							pos.y = y;
							pos.z = z;

							AssaParticle_ShelltomWeaponHit(&pos);
						}
					}
				}
			}
			else
			{

				wp = (dwActionItemCode&sinITEM_MASK2);
				if (!shootFlag && chrAttackTarget)
				{
					GetAttackPoint(&x, &y, &z);

					if (wp == sinWS1 || wp == sinWT1)
					{


						if (smCharInfo.JOB_CODE == JOBCODE_ATALANTA &&
							(dwDispAppSkill&SKILL_APPMASK_GODLY_SHIELD) && wp == sinWT1)
						{

							pos.x = x;
							pos.y = y;
							pos.z = z;
							pos2.x = chrAttackTarget->pX;
							pos2.y = chrAttackTarget->pY + 24 * fONE;
							pos2.z = chrAttackTarget->pZ;
							SkillFrostJavelin(&pos, &pos2);

							if ((rand() % 2) == 0)
								SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_ICE1, pX, pY, pZ);
							else
								SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_ICE2, pX, pY, pZ);

							return TRUE;
						}

						ShootingPosi.x = x;
						ShootingPosi.y = y;
						ShootingPosi.z = z;

						if (chrAttackTarget)
						{
							GetRadian3D(x, y, z, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ);
							ShootingAngle.x = GeoResult_X;
							ShootingAngle.y = GeoResult_Y;
							ShootingAngle.z = Angle.z;
						}
						else
						{
							ShootingAngle.x = Angle.x;
							ShootingAngle.y = Angle.y;
							ShootingAngle.z = Angle.z;
						}

						ShootingCount = 0;
						ShootingFlag = TRUE;

						if (AttackSkil)
							ShootingKind = AttackSkil & 0xFF;
						else
							ShootingKind = TRUE;

					}

					if (wp == sinWM1)
					{


						if (WeaponEffect)
						{
							switch (WeaponEffect)
							{
							case (sITEMINFO_LIGHTING + 1):
								pos.x = x;
								pos.y = y;
								pos.z = z;
								pos2.x = chrAttackTarget->pX;
								pos2.y = chrAttackTarget->pY + 24 * fONE;
								pos2.z = chrAttackTarget->pZ;
								AssaParticle_LightShot(&pos, &pos2);
								if ((rand() % 2) == 0)
									SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_LIGHTNING1, pX, pY, pZ);
								else
									SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_LIGHTNING2, pX, pY, pZ);
								break;
							case (sITEMINFO_FIRE + 1):
								pos.x = x;
								pos.y = y;
								pos.z = z;
								pos2.x = chrAttackTarget->pX;
								pos2.y = chrAttackTarget->pY + 24 * fONE;
								pos2.z = chrAttackTarget->pZ;
								AssaParticle_FireShot(&pos, &pos2);
								if ((rand() % 2) == 0)
									SkillPlaySound(SKILL_SOUND_SKILL_FIREBOLT1, pX, pY, pZ);
								else
									SkillPlaySound(SKILL_SOUND_SKILL_FIREBOLT2, pX, pY, pZ);
								break;
							case (sITEMINFO_ICE + 1):
								pos.x = x;
								pos.y = y;
								pos.z = z;
								pos2.x = chrAttackTarget->pX;
								pos2.y = chrAttackTarget->pY + 24 * fONE;
								pos2.z = chrAttackTarget->pZ;
								AssaParticle_IceShot(&pos, &pos2);
								if ((rand() % 2) == 0)
									SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_ICE1, pX, pY, pZ);
								else
									SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_MAGIC_ICE2, pX, pY, pZ);
								break;
							}
						}
						else
						{

							StartEffectMonsterDest(x, y, z,
								chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ,
								MONSTER_IMP_SHOT1);
						}
					}

				}
			}
		}
	}

	return TRUE;
}

int smCHAR::Main()
{

	int x, z, y;
	int keycode;
	int cnt;
	DWORD compFrame;
	smPLAYBUFF	*playBuff;
	int OldAction;
	int dist;

	POINT3D OldPos;

	int	frameStep, moveStep;
	smTRANS_COMMAND	smTransCommand;
	smCHAR *lpChar;
	int EvtFrame;
	int dm1, dm2;
	int UserSlowSpeed = 128;



	if (!Pattern || PatLoading || !MotionInfo)
	{

		return FALSE;
	}

	switch (ActionPattern)
	{
	case 0:
		if (MotionInfo->State && MotionInfo->State < 0x100)
		{


			if (sinChangeSetFlag)
			{
				cInvenTory.ChangeABItem(sinChangeSetFlag);
				sinChangeSetFlag = 0;
			}

			if (sinGetLife() == 0)
			{

				sinSetLife(smCharInfo.Life[1] / 2);
				ResetEnergyGraph(0);

			}

			if (PlaySlowCount)
			{
				if (PlaySlowSpeed)
				{
					UserSlowSpeed = PlaySlowSpeed;
				}
				else
					UserSlowSpeed = 128;

				if (PlaySlowSpeed > 200 || PlaySlowSpeed < 0) UserSlowSpeed = 128;
			}

			if (MoveFlag == TRUE)
			{

				cnt = smCharInfo.Move_Speed - 1;
				if (cnt < 0) cnt = 0;
				if (cnt > 8) cnt = 8;




				if (cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin01) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin02) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin03) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin04) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin05) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin06) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin07) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin08) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin09) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin10) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin11) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin12) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin13) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin14) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin15) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin16) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin17) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin18) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin19) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin20) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin21) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin22) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin23) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin24) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin25) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin26) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin27) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin28) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin29) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin30) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin31) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinOE1 | sin01) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinOE1 | sin02) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinOE1 | sin03) ||
					cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.CODE == (sinDB1 | sin32))

				{
					if (DeleteEventItem_TimeOut(&cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo) == TRUE)
						cnt = 1;
					else
						cnt = smCharInfo.Move_Speed;
				}
				MoveSpeed = 250 + 10 * cnt;

				if (PlaySlowCount)
					MoveSpeed = (MoveSpeed*UserSlowSpeed) >> 8;


				if (MoveCnt > 0)
				{
					MoveCnt--;
					if (MoveCnt <= 0)
						MoveFlag = FALSE;
				}

				OldPos.x = pX;
				OldPos.y = pY;
				OldPos.z = pZ;

				if (!ShootingFlag) chrAttackTarget = 0;

				if (smConfig.getSecurity() < AccountTypes::SEC_MODERATOR && !Pattern2) MoveMode = 0;
				if (smCharInfo.Weight[0] > smCharInfo.Weight[1]) MoveMode = 0;

				if (MoveMode == 0 || ShootingFlag || smCharInfo.Stamina[0] == 0)
				{

					if (MotionInfo->State != CHRMOTION_STATE_FALLDOWN &&
						MotionInfo->State != CHRMOTION_STATE_WALK)
						SetMotionFromCode(CHRMOTION_STATE_WALK);

					if (OnStageFieldState != FIELD_STATE_VILLAGE)
						MoveAngle2((MoveSpeed * 180) >> 8);
					else
						MoveAngle2(MoveSpeed);

					dwLastCharMoveTime = dwPlayTime;
				}
				else
				{

					if (MotionInfo->State != CHRMOTION_STATE_FALLDOWN && MotionInfo->State != CHRMOTION_STATE_RUN)
						SetMotionFromCode(CHRMOTION_STATE_RUN);

#ifdef _WINMODE_DEBUG
					if (smConfig.getSecurity() >= AccountTypes::SEC_VIP && VRKeyBuff[VK_SHIFT])
						MoveAngle2(3000);
					else
#endif
						MoveAngle2((MoveSpeed * 460) >> 8);

					dwLastCharMoveTime = dwPlayTime;


					if ((Counter & 0x7) == 0 && WeatherMode < 2)
					{
						if (OnStageField >= 0 && StageField[OnStageField]->FieldCode != rsSOD_FIELD &&
							(StageField[OnStageField]->State == FIELD_STATE_RUIN ||
								StageField[OnStageField]->State == FIELD_STATE_DESERT))
						{

							if ((Counter & 8) == 0)
								GetMoveLocation(4 * fONE, 0, 0, 0, Angle.y, 0);
							else
								GetMoveLocation(-4 * fONE, 0, 0, 0, Angle.y, 0);

							cnt = 10 + ((dwPlayTime >> 2) & 0xF);
							StartEffect(pX + GeoResult_X, pY + 12 * fONE, pZ + GeoResult_Z, cnt, cnt, EFFECT_DUST1);
						}
					}
				}


				if (OverLapPosi || pX != OldPos.x || pZ != OldPos.z)
				{
					lpChar = CheckOtherPlayPosi(pX, pY, pZ);
					if (lpChar)
					{
						if (!OverLapPosi)
						{
							pX = OldPos.x;
							pZ = OldPos.z;
							if (ActionGameMode)
							{
								if (lpChar->smCharInfo.State == smCHAR_STATE_USER)
								{
									if (chrEachMaster != lpChar)
									{
										if (chrEachMaster) CloseEachPlayer();
										OpenEachPlayer(lpChar);
									}
									if (chrEachMaster)
										EachTradeButton = TRUE;

								}
							}
						}

						if (CheckOtherPlayPosi(pX, pY, pZ))
						{
							OverLapPosi = TRUE;
							OverLapPosi2 = FALSE;
						}
						else
						{
							OverLapPosi = FALSE;
							OverLapPosi2 = TRUE;
						}

					}
					else
					{
						OverLapPosi = FALSE;
						OverLapPosi2 = FALSE;
					}
				}

				if (smCharInfo.wPlayerKilling[0] > 0)
				{

					if (pX<PrisonRect.left || pX>PrisonRect.right || pZ<PrisonRect.top || pZ>PrisonRect.bottom)
					{
						pX = OldPos.x;
						pY = OldPos.y;
						pZ = OldPos.z;
					}
				}

				if (OnStageField >= 0 && StageField[OnStageField]->FieldCode == rsCASTLE_FIELD)
				{

					if (pZ<CastleBattleZone_DoorLineZ + 16 * fONE && pZ>CastleBattleZone_DoorLineZ - 48 * fONE &&
						pX > CastleBattleZone_DoorLineX[0] && pX < CastleBattleZone_DoorLineX[1])
					{
						if (rsBlessCastle.CastleMode && rsBlessCastle.DefenceLevel == 0)
						{
							pX = OldPos.x;
							pY = OldPos.y;
							pZ = OldPos.z;
						}
					}
					else
					{


						if (smConfig.getSecurity() < AccountTypes::SEC_MODERATOR && pZ < CastleBattleZone_BridgeZ && !rsBlessCastle.CastleMode)
						{
							if (!smCharInfo.ClassClan || GetClanCode(smCharInfo.ClassClan) != rsBlessCastle.dwMasterClan)
							{
								pX = OldPos.x;
								pY = OldPos.y;
								pZ = OldPos.z;
							}
						}
					}
				}

				if (pX == OldPos.x && pY == OldPos.y && pZ == OldPos.z)
				{
					if (TraceMode_DblClick)
					{
						MoveFlag = 0;
						TraceMode_DblClick = 0;
					}
				}



				int limit_FrameStep = 0;
				if (MoveSpeed > 350)
				{
					limit_FrameStep = 350;
					FrameStep = (80 * limit_FrameStep) / 300;
				}
				else
					FrameStep = (80 * MoveSpeed) / 300;

			}
			else
			{
				if (MotionInfo->State != CHRMOTION_STATE_FALLDOWN && MotionInfo->State != CHRMOTION_STATE_STAND) SetMotionFromCode(CHRMOTION_STATE_STAND);
				if (PHeight < pY) MoveAngle2(0);

				FrameStep = 80;

				if (FrameCounter == 0)
				{

					if (CheckOtherPlayPosi(pX, pY, pZ))
					{
						OverLapPosi = TRUE;
						OverLapPosi2 = FALSE;
					}
				}

			}




			if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
			{
				if (VRKeyBuff[VK_SHIFT] && VRKeyBuff[VK_CONTROL] && TalkPattern)
				{
					if (VRKeyBuff[VK_F1])
						Debug_TalkZoomMode = TRUE;
					else if (VRKeyBuff[VK_F2])
						Debug_TalkZoomMode = FALSE;
					else if (VRKeyBuff[VK_F3])
					{
						Debug_TalkRepeatMode = TRUE;
						Debug_TalkRepeatModeType = TALK_MOTION_FILE;
					}
					else if (VRKeyBuff[VK_F4])
					{
						Debug_TalkRepeatMode = FALSE;
						Debug_TalkRepeatModeType = -1;
					}
					else if (VRKeyBuff[VK_F5])
					{
						Debug_TalkRepeatMode = TRUE;
						Debug_TalkRepeatModeType = FACIAL_MOTION_FILE;
					}
					else if (VRKeyBuff[VK_F6])
					{
						Debug_TalkRepeatMode = FALSE;
						Debug_TalkRepeatModeType = -1;
					}

					if (Debug_TalkRepeatMode == FALSE)
					{
						for (cnt = 0; cnt < (int)lpTalkModelParent->TalkMotionCount; cnt++)
						{
							keycode = lpTalkModelParent->TalkMotionInfo[cnt].KeyCode;
							if (keycode)
							{
								if (VRKeyBuff[keycode])
								{
									lpTalkMotionInfo = &lpTalkModelParent->TalkMotionInfo[cnt];
									TalkFrame = lpTalkMotionInfo->StartFrame * 160;
									break;
								}
							}
						}
					}
				}
				else
				{
					for (cnt = 0; cnt < (int)smMotionInfo->MotionCount; cnt++)
					{
						keycode = smMotionInfo->MotionInfo[cnt].KeyCode;
						if (keycode && keycode >= 'A')
						{
							if (VRKeyBuff[keycode])
							{
								ChangeMotion(cnt);
								break;
							}
						}
					}
				}
			}

		}

		if (MotionInfo->State == CHRMOTION_STATE_ATTACK || MotionInfo->State == CHRMOTION_STATE_SKILL)
		{
			if (!MotionLoop)
			{
				FrameStep = (80 * AttackSpeed) >> FLOATNS;


				if (smCharInfo.JOB_CODE == 8 &&
					MotionInfo->ItemCodeCount && sItem[MotionInfo->ItemCodeList[0]].CODE == (sinWM1 | sin04))
				{
					FrameStep -= 16;
				}
			}
			else
				FrameStep = MotionLoopSpeed;

			if (PlaySlowCount)
				FrameStep = (FrameStep*UserSlowSpeed) >> 8;
		}
		else
		{
			if (MotionInfo->State == CHRMOTION_STATE_DAMAGE || MotionInfo->State == CHRMOTION_STATE_EAT)
			{
				FrameStep = 92;

				if (PlaySlowCount)
					FrameStep = (FrameStep*UserSlowSpeed) >> 8;
			}
		}

		if (PlaySlowCount > 0)
		{
			PlaySlowCount--;
			if (PlaySlowCount == 0 && AttackIce != 0)
			{
				AttackIce = -AttackIce;
			}
		}
		if (PlayDistortion > 0) PlayDistortion--;
		if (PlayCurseLazy > 0) PlayCurseLazy--;
		if (PlayVanish > 0)
		{
			PlayVanish--;
			if (PlayVanish <= 0 && dwM_BlurTime) dwM_BlurTime = dwPlayTime;
		}
		if (PlayStunCount > 0)
			PlayStunCount--;
		if (!PlayStunCount)
			PlayStunType = 0;

		if (AttackIce != 0)
		{

			if (AttackIce > 0 && AttackIce < 160) AttackIce++;
			if (AttackIce < 0) AttackIce++;
			if (MotionInfo->State == CHRMOTION_STATE_DEAD) AttackIce = 0;
		}

		if (PlayInvincible > 0)	PlayInvincible--;


		if (PlayPoison[1] > 0)
		{
			if (DispPoison <= 0) DispPoison = 1;
			PlayPoison[1]--;

			if (PlayPoison[0] && (PlayPoison[1] & 1) == 0 && MotionInfo->State != CHRMOTION_STATE_DEAD)
			{
				sinSetLife(sinGetLife() - PlayPoison[0]);
				if (sinGetLife() <= 0)
				{
					sinSetLife(1);
				}
			}
		}
		else
		{
			if (DispPoison > 0) DispPoison = -DispPoison;
		}

		if (DispPoison != 0)
		{

			if (DispPoison > 0 && DispPoison < 100) DispPoison++;
			if (DispPoison < 0) DispPoison++;
			if (MotionInfo->State == CHRMOTION_STATE_DEAD) DispPoison = 0;
		}




		if (TalkFrame)
		{
			if (TalkFrame >= lpTalkMotionInfo->EndFrame * 160)
				TalkFrame = 0;
			else
				TalkFrame += 80;
		}

		if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
		{
			if (Debug_TalkRepeatMode == TRUE && TalkFrame == 0)
			{
				int TalkCnt = 0;
				if (lpTalkModelParent->TalkMotionRate[CHRMOTION_EXT])
				{
					TalkCnt = rand() % 100;
					TalkCnt = lpTalkModelParent->TalkMotionRateCnt[Debug_TalkRepeatModeType][TalkCnt];
				}
				else
					TalkCnt = rand() % lpTalkModelParent->TalkMotionCount;

				lpTalkMotionInfo = &lpTalkModelParent->TalkMotionInfo[TalkCnt];
				TalkFrame = lpTalkMotionInfo->StartFrame * 160;
			}
		}



		frame += FrameStep;

		EventAttack();


		if (MoveFlag == TRUE)
		{


			int IsStateIce = 0;


			if (OnStageField >= 0)
			{
				if (StageField[OnStageField]->FieldCode != 0 && StageField[OnStageField]->FieldCode != 1 &&
					StageField[OnStageField]->FieldCode != 19 && StageField[OnStageField]->FieldCode != 18 &&
					StageField[OnStageField]->FieldCode != 24 && StageField[OnStageField]->FieldCode != 26 &&
					StageField[OnStageField]->FieldCode != 30 && StageField[OnStageField]->FieldCode != 33 &&
					StageField[OnStageField]->FieldCode != 34)

					WaterHeight = CLIP_OUT;



				if (lpCurPlayer == this && StageField[OnStageField]->State == FIELD_STATE_ICE)
					IsStateIce = 1;


			}


			if (MotionInfo->EventFrame[0])
			{
				compFrame = frame - (MotionInfo->StartFrame * 160);
				if (MotionInfo->EventFrame[0] > (compFrame - FrameStep) && MotionInfo->EventFrame[0] <= compFrame)
				{
					PlayFootStep(this);

					if (WaterHeight != CLIP_OUT && WaterHeight > pY && WaterHeight < (pY + 32 * fONE) && OnStageField >= 0)
					{
						GetMoveLocation(0, 0, 8 * fONE, 0, Angle.y, 0);
						StartTerrainEffect(pX + GeoResult_X, WaterHeight + 128, pZ + GeoResult_Z, EFFECT_TERRAIN_WAVE);
					}



					else if (IsStateIce)
					{
						GetMoveLocation(3 * fONE, 0, 5 * fONE, 0, Angle.y, 0);
						SetIceFoot(0, dwPlayTime, GeoResult_X, GeoResult_Z);
					}

				}

			}

			if (MotionInfo->EventFrame[1])
			{
				compFrame = frame - (MotionInfo->StartFrame * 160);
				if (MotionInfo->EventFrame[1] > (compFrame - FrameStep) && MotionInfo->EventFrame[1] <= compFrame)
				{
					PlayFootStep(this);

					if (WaterHeight != CLIP_OUT && WaterHeight > pY && WaterHeight < (pY + 32 * fONE) && OnStageField >= 0)
					{
						GetMoveLocation(0, 0, 8 * fONE, 0, Angle.y, 0);
						StartTerrainEffect(pX + GeoResult_X, WaterHeight + 128, pZ + GeoResult_Z, EFFECT_TERRAIN_WAVE);
					}



					else if (IsStateIce)
					{
						GetMoveLocation(-3 * fONE, 0, 5 * fONE, 0, Angle.y, 0);
						SetIceFoot(1, dwPlayTime, GeoResult_X, GeoResult_Z);
					}

				}
			}
		}




		if (MotionInfo->State == CHRMOTION_STATE_EAT)
		{

			if (MotionInfo->EventFrame[0])
			{
				compFrame = frame - (MotionInfo->StartFrame * 160);
				if (MotionInfo->EventFrame[0] > (compFrame - FrameStep) && MotionInfo->EventFrame[0] <= compFrame)
				{

					if (UseEtherCoreCode)
					{


						PotionLog = POTION_ETHERCORE;
					}
					else
					{
						if (pUsePotion && pUsePotion->sItemInfo.CODE)
						{

							SendUseItemCodeToServer(&pUsePotion->sItemInfo);
						}

						switch (sinUsePotion())
						{
						case 1:
							StartEffect(pX, pY + 48 * fONE, pZ, EFFECT_POTION1);
							PotionLog = 1;
							ResetEnergyGraph(0);
							break;
						case 2:
							StartEffect(pX, pY + 48 * fONE, pZ, EFFECT_POTION2);
							PotionLog = 2;
							ResetEnergyGraph(1);
							break;
						case 3:
							StartEffect(pX, pY + 48 * fONE, pZ, EFFECT_POTION3);
							PotionLog = 3;
							ResetEnergyGraph(2);
							break;
						case 4:
							StartEffect(pX, pY + 48 * fONE, pZ, EFFECT_POTION3);
							StartEffect(pX, pY + 48 * fONE, pZ, EFFECT_POTION2);
							StartEffect(pX, pY + 48 * fONE, pZ, EFFECT_POTION1);
							PotionLog = 4;
							ResetEnergyGraph(3);

							for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
							{
								if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].dwObjectSerial && chrOtherPlayer[cnt].PartyFlag &&
									chrOtherPlayer[cnt].MotionInfo->State != CHRMOTION_STATE_DEAD && chrOtherPlayer[cnt].RendSucess)
								{

									x = chrOtherPlayer[cnt].pX;
									y = chrOtherPlayer[cnt].pY + 48 * fONE;
									z = chrOtherPlayer[cnt].pZ;

									StartEffect(x, y, z, EFFECT_POTION1);
									StartEffect(x, y, z, EFFECT_POTION2);
									StartEffect(x, y, z, EFFECT_POTION3);

								}
							}
							break;
						case 5:

							SetMotionFromCode(CHRMOTION_STATE_DAMAGE);
							CharPlaySound(lpCurPlayer);
							break;
						case 6:

							break;
						case 7:
							SetMotionFromCode(CHRMOTION_STATE_YAHOO);
							break;
						}

					}
					SetDynLight(pX, pY + 48 * fONE, pZ, 50, 100, 70, 0, 250, 1);
				}
			}
		}


		if (frame >= MotionInfo->EndFrame * 160)
		{


			if (MotionInfo->State == CHRMOTION_STATE_DEAD)
			{
				if (g_IsDxProjectZoomIn)
				{
					SetFullZoomMap(0);
				}
				if (ReStartOptionIndex)
				{

					if (OnStageField >= 0 && ReStartOptionIndex == RESTART_FEILD)
					{

						if (StageField[OnStageField]->FieldCode == rsSOD_FIELD)
							WarpFieldNearPos(rsSOD_VILLAGE, pX, pZ, &x, &z);
						else
							WarpFieldNearPos(StageField[OnStageField]->FieldCode, pX, pZ, &x, &z);

						if (!PlayUsed_Resurrection)
						{
							ContGameExp(this);
						}
						PlayUsed_Resurrection = 0;
						RestartPlayCount = 700;
					}

					if (ReStartOptionIndex == RESTART_TOWN)
					{



						if (OnStageField >= 0 && StageField[OnStageField]->State == FIELD_STATE_CASTLE &&
							smCharInfo.ClassClan && GetClanCode(smCharInfo.ClassClan) == rsBlessCastle.dwMasterClan)
						{

							WarpCastleField(1, &x, &z);
						}
						else
							WarpStartField(&x, &z);

						RestartPlayCount = 700;
						PlayUsed_Resurrection = 0;
					}

					if (ReStartOptionIndex == RESTART_EXIT)
					{

						CheckCharForm();

						sinSetLife(0);
						ResetEnergyGraph(0);

						quit = TRUE;
						SaveGameData();
						QuitSave = TRUE;
						PlayUsed_Resurrection = 0;
					}
					else
					{
						SetPosi(x, 0, z, 0, 0, 0);
						TraceCameraPosi.x = pX;
						TraceCameraPosi.y = pY;
						TraceCameraPosi.z = pZ;
						TraceTargetPosi.x = pX;
						TraceTargetPosi.y = pY;
						TraceTargetPosi.z = pZ;


						if (smCharInfo.State == smCHAR_STATE_ENEMY)
						{

							SetMotionFromCode(CHRMOTION_STATE_STAND);
						}
						else
						{
							SetMotionFromCode(CHRMOTION_STATE_RESTART);
							StartEffect(pX, pY, pZ, EFFECT_GAME_START1);
							SetDynLight(pX, pY, pZ, 100, 100, 100, 0, 200);
							CharPlaySound(this);
						}
						dwBattleTime = 0;
						dwBattleQuitTime = 0;


						OnStageField = -1;
						if (smGameStage[0])
						{
							cnt = smGameStage[0]->GetFloorHeight(pX, pY, pZ, Pattern->SizeHeight);
							lpCurPlayer->OnStageField = 0;
						}
						if (cnt == CLIP_OUT && smGameStage[1])
						{
							lpCurPlayer->OnStageField = 1;
						}
					}

					CheckCharForm();

					sinSetLife(smCharInfo.Life[1] / 2);
					ResetEnergyGraph(0);
					ReformCharForm();
					MoveFlag = FALSE;

					ReStartOptionIndex = 0;
					ReStartFlag = 0;


				}
				else
				{
					frame = MotionInfo->EndFrame * 160 - 80;
				}


				if (cTrade.OpenFlag && !dwTradeMaskTime)
				{
					SendRequestTrade(cTrade.TradeCharCode, 3);
					cTrade.CancelTradeItem();
				}


				if (FrameCounter >= 70 * 10 && lpCurPlayer->OnStageField >= 0)
				{

					sITEMINFO *lpItemInfo = 0;

					if (StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_CASTLE)
						lpItemInfo = FindItemFromCode(sinBC1 | sin05);




					if (lpItemInfo || PlayUsed_Resurrection)
					{
						if (lpItemInfo)
						{
							SendUseItemCodeToServer(lpItemInfo);
							cInvenTory.DeleteInvenItemToServer(lpItemInfo->CODE, lpItemInfo->ItemHeader.Head, lpItemInfo->ItemHeader.dwChkSum);
						}

						lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_RESTART);
						StartEffect(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, EFFECT_GAME_START1);
						SetDynLight(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 100, 100, 100, 0, 200);
						CharPlaySound(lpCurPlayer);
						sinSetLife(lpCurPlayer->smCharInfo.Life[1] / 2);
						ResetEnergyGraph(4);
						lpCurPlayer->MoveFlag = FALSE;
						RestartPlayCount = 350;
						ReStartFlag = 0;
						PlayUsed_Resurrection = 0;
						sSKILL TempSkill;
						for (int j = 0; j < SIN_MAX_SKILL; j++)
						{
							if (sSkill[j].CODE == SCROLL_INVULNERABILITY)
							{
								memcpy(&TempSkill, &sSkill[j], sizeof(sSKILL));
								TempSkill.UseTime = 20;
								sinContinueSkillSet(&TempSkill);
								SwitchSkill(&TempSkill);
								break;
							}
						}

					}
				}

			}
			else
			{

				if (MotionLoop) MotionLoop--;

				if (MotionInfo->State == CHRMOTION_STATE_YAHOO)
					SendClanYahooMotion();

				if (MotionInfo->State == CHRMOTION_STATE_EAT)
				{
					if (UseEtherCoreCode)
					{
						if (OnStageField < 0 ||
							(StageField[OnStageField]->FieldCode != rsSOD_FIELD && StageField[OnStageField]->FieldCode != QUEST_ARENA_FIELD))
						{


							switch (UseEtherCoreCode)
							{
							case (sinEC1 | sin01):
								SaveGameData();
								WarpStartField(START_FIELD_NUM, &pX, &pZ);
								SetPosi(pX, 0, pZ, 0, 0, 0);
								break;
							case (sinEC1 | sin02):
								SaveGameData();
								WarpStartField(START_FIELD_NEBISCO, &pX, &pZ);
								SetPosi(pX, 0, pZ, 0, 0, 0);
								break;
							case (sinEC1 | sin04):
								SaveGameData();
								WarpStartField(START_FIELD_MORYON, &pX, &pZ);
								SetPosi(pX, 0, pZ, 0, 0, 0);
								break;
							}

							TraceCameraPosi.x = pX;
							TraceCameraPosi.y = pY;
							TraceCameraPosi.z = pZ;
							TraceTargetPosi.x = pX;
							TraceTargetPosi.y = pY;
							TraceTargetPosi.z = pZ;

							StartEffect(pX, pY + 48 * fONE, pZ, EFFECT_RETURN1);
							SkillPlaySound(SKILL_SOUND_LEARN, pX, pY, pZ);
							RestartPlayCount = 700;
						}
						MoveFlag = 0;
						MouseButton[0] = 0;
						dwNextMotionCode = 0;
						UseEtherCoreCode = 0;
					}
					else
					{

						ComparePotion();
					}

				}

				if (lpTransVirtualPotion)
				{

					x = (smCharInfo.Life[1] * 40) / 100;
					if (lpTransVirtualPotion->WParam < x) x = lpTransVirtualPotion->WParam;
					sinSetLife(sinGetLife() + x);

					sinSetMana(sinGetMana() + lpTransVirtualPotion->LParam);
					sinSetStamina(sinGetStamina() + lpTransVirtualPotion->SParam);
					ResetEnergyGraph(3);


					ZeroMemory(lpTransVirtualPotion, sizeof(smTRANS_COMMAND));
					delete lpTransVirtualPotion;
					lpTransVirtualPotion = 0;
				}


				if (sinChangeSetFlag && !MotionLoop)
				{
					cInvenTory.ChangeABItem(sinChangeSetFlag);
					sinChangeSetFlag = 0;
				}

				if (dwNextMotionCode && !MotionLoop)
				{


					if (SetMotionFromCode(dwNextMotionCode) == FALSE)
					{
						SetMotionFromCode(CHRMOTION_STATE_STAND);
					}
					else
					{
						if (UseEtherCoreCode && dwNextMotionCode == CHRMOTION_STATE_EAT)
						{

							StartEffect(pX, pY + 48 * fONE, pZ, EFFECT_RETURN1);
							SkillPlaySound(SKILL_SOUND_LEARN, pX, pY, pZ);
						}
					}
					dwNextMotionCode = 0;
				}
				else
				{
					if (MotionInfo->State == CHRMOTION_STATE_ATTACK || MotionInfo->State == CHRMOTION_STATE_SKILL)
					{

						if (MotionInfo->State == CHRMOTION_STATE_SKILL && AttackSkil)
							EndSkill();

						if (AttackSkil && MotionLoop)
						{
							frame = MotionInfo->StartFrame * 160;

							PlaySkillLoop(AttackSkil, this);
						}
						else
						{
							if (!AttAutoCont && MouseButton[0] == 0 && MouseButton[1] == 0 && lpCharMsTrace && lpCharMsTrace == chrAttackTarget)
							{

								if (CancelAttack() == TRUE)
									MoveFlag = FALSE;
							}
							if (MoveFlag && !MsTraceMode)
							{
								Angle.y = GetPlayMouseAngle();
							}
						}
					}
					else
						if (MotionInfo->State == CHRMOTION_STATE_EAT)
						{
							if (!AttAutoCont && MouseButton[0] == 0 && MouseButton[1] == 0 && lpCharMsTrace && lpCharMsTrace == chrAttackTarget)
							{

								if (CancelAttack() == TRUE)
									MoveFlag = FALSE;
							}
						}

					if (MotionInfo->Repeat == TRUE)
					{
						frame = (MotionInfo->StartFrame * 160) + (frame - MotionInfo->EndFrame * 160);
					}
					else
					{
						if (!MotionLoop)
						{
							if (dwNextMotionCode)
							{

								if (SetMotionFromCode(dwNextMotionCode) == FALSE)
								{
									SetMotionFromCode(CHRMOTION_STATE_STAND);
								}
								dwNextMotionCode = 0;
							}
							else
							{
								SetMotionFromCode(CHRMOTION_STATE_STAND);
							}
						}
					}
				}
			}


			AttackSpeed = GetAttackSpeedMainFrame(smCharInfo.Attack_Speed);

			if (dwActionItemTwoHand)
				AttackSpeed += 16;

			for (cnt = 0; cnt < 10; cnt++)
			{
				if (ContinueSkill[cnt].Flag)
				{
					if (ContinueSkill[cnt].CODE == SKILL_SWIFT_AXE)
					{
						if ((dwActionItemCode&sinITEM_MASK2) == sinWA1)
						{
							x = ContinueSkill[cnt].Point - 1;

							if (x >= 0 && x < 10)
							{
								AttackSpeed += (AttackSpeed * Swift_Axe_Speed[x]) / 100;
							}

							break;
						}
					}
				}
			}



			if (!MotionLoop)
			{

				AttackEffect = 0;
			}

			MotionEvent = 0;
		}

		if (AttackAnger > 0)
			AttackAnger--;


		if (dwWeaponEffectTime)
		{
			if (dwWeaponEffectTime < dwPlayTime)
			{
				dwWeaponEffectTime = 0;
				WeaponEffect = 0;
			}
		}

		wStickItems[smPLAYBUFF_ITEM_SKIL] = AttackSkil;


		if (WaterHeight != CLIP_OUT && WaterHeight > pY && WaterHeight < (pY + 32 * fONE) && OnStageField >= 0)
		{

			dist = 0;
			cnt = 0x3F;
			switch (MotionInfo->State)
			{
			case CHRMOTION_STATE_WALK:
				cnt = 0x1F;
				dist = 8;
				break;
			case CHRMOTION_STATE_RUN:
				dist = 14;
			case CHRMOTION_STATE_ATTACK:
			case CHRMOTION_STATE_SKILL:
				cnt = 0xF;
				break;
			}

			if ((Counter&cnt) == 0)
			{
				GetMoveLocation(0, 0, dist << FLOATNS, 0, Angle.y, 0);
				StartTerrainEffect(pX + GeoResult_X, WaterHeight + 128, pZ + GeoResult_Z, EFFECT_TERRAIN_WAVE);

			}
		}


		SavePlayBuff();
		break;

	case 1:
		break;

	case 5:

		if (PlaySlowCount)
		{
			if (PlaySlowSpeed)
			{
				moveStep = (SERVER_CHAR_SKIP*PlaySlowSpeed) >> 8;
				frameStep = (SERVER_CHAR_FRAME_STEP*PlaySlowSpeed) >> 8;
			}
			else
			{
				moveStep = SERVER_CHAR_SKIP >> 1;
				frameStep = SERVER_CHAR_FRAME_STEP >> 1;
			}
		}
		else
		{
			moveStep = SERVER_CHAR_SKIP;
			frameStep = SERVER_CHAR_FRAME_STEP;
		}

		if (MotionInfo->State == CHRMOTION_STATE_WARP)
		{

			frame += frameStep;

			if (frame > MotionInfo->EndFrame * 160)
			{
				Close();
				return TRUE;
			}
			SavePlayBuff2();
			FrameCounter += 3;
			break;
		}



		if (DontMoveFlag)	moveStep = 0;



		if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_BABEL)
		{
			if (smCharInfo.Life[0] > 0)	dwBabelPlayTime = dwPlayServTime + 5000;
		}

		if (MotionInfo->State && MotionInfo->State < 0x100 && moveStep)
		{
			if (MotionInfo->State == CHRMOTION_STATE_WALK || MotionInfo->State == CHRMOTION_STATE_RUN)
			{
				OldPos.x = pX;
				OldPos.y = pY;
				OldPos.z = pZ;

				if (sMoveStepCount[0])
				{

					if (sMoveStepCount[1]) moveStep *= sMoveStepCount[1];

					for (cnt = 0; cnt < sMoveStepCount[0]; cnt++)
					{
						MoveAngle(moveStep);
						if (MotionInfo->State == CHRMOTION_STATE_RUN)
							MoveAngle(moveStep);
					}
				}
				else
				{

					if (smCharInfo.wPlayClass[0] == MONSTER_CLASS_BOSS && smCharInfo.dwCharSoundCode == snCHAR_SOUND_DARKKNIGHT)
					{

						MoveAngle(moveStep * 2);
					}
					else
						MoveAngle(moveStep);

					if (MotionInfo->State == CHRMOTION_STATE_RUN)
					{
						if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_GREVEN)
						{

							if (lpTargetPlayInfo && TragetTraceMode)
							{
								SetTargetPosi2(lpTargetPlayInfo->Position.x >> FLOATNS,
									lpTargetPlayInfo->Position.z >> FLOATNS);
							}
							MoveAngle(moveStep * 2);
							MoveAngle(moveStep * 2);
						}
						else
						{
							if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_WOLVERLIN)
							{

								if (lpTargetPlayInfo && TragetTraceMode)
								{
									SetTargetPosi2(lpTargetPlayInfo->Position.x >> FLOATNS,
										lpTargetPlayInfo->Position.z >> FLOATNS);
								}
								MoveAngle(moveStep * 2);
							}
							else
								MoveAngle(moveStep);
						}
					}
				}

				if (MotionInfo->State != CHRMOTION_STATE_WALK && MotionInfo->State != CHRMOTION_STATE_RUN)
					SetMotionFromCode(CHRMOTION_STATE_WALK);



				if (OverLapPosi || pX != OldPos.x || pZ != OldPos.z)
				{
					lpCharOverLap = CheckOtherPlayPosi(pX, pY, pZ);
					if (lpCharOverLap)
					{
						if (!OverLapPosi)
						{
							pX = OldPos.x;
							pZ = OldPos.z;
							lpCharOverLap = CheckOtherPlayPosi(pX, pY, pZ);
						}

						if (lpCharOverLap)
						{
							OverLapPosi = TRUE;
							OverLapPosi2 = FALSE;
						}
						else
						{
							OverLapPosi = FALSE;
							OverLapPosi2 = TRUE;
						}

					}
					else
					{
						OverLapPosi = FALSE;
						OverLapPosi2 = FALSE;
					}
				}
				if (!OverLapPosi) lpCharOverLap = 0;
			}
			else
			{
				if (MotionInfo->State != CHRMOTION_STATE_STAND) SetMotionFromCode(CHRMOTION_STATE_STAND);
			}
		}

		frame += frameStep;

		if (frame > MotionInfo->EndFrame * 160)
		{

			if (MotionInfo->State == CHRMOTION_STATE_DEAD)
			{
				frame = MotionInfo->EndFrame * 160;
			}
			else
			{

				if (MotionInfo->State == CHRMOTION_STATE_EAT && PotionLog == 1)
				{

					smCharInfo.Life[0] += (smCharInfo.Life[1] >> 1);
					if (smCharInfo.Life[0] > smCharInfo.Life[1])
						smCharInfo.Life[0] = smCharInfo.Life[1];
				}

				if (smMonsterInfo.SkillCurse && smCharInfo.Brood != smCHAR_MONSTER_USER)
				{
					if (MotionInfo->State == CHRMOTION_STATE_ATTACK)
					{
						lpTargetPlayInfo = 0;
					}

					if (lpTargetChar && MotionInfo->State == CHRMOTION_STATE_SKILL)
					{
						lpTargetChar->PlayHolyPower[0] = GetRandomPos(10, 20);
						lpTargetChar->PlayHolyPower[1] = 16 * 20;
						lpTargetChar = 0;
					}
				}

				if ((lpTargetPlayInfo || TargetMoveCount) && MotionInfo->State < 0x100)
					PosBeginCount++;

				if (MotionInfo->Repeat == TRUE)
				{
					frame = (MotionInfo->StartFrame * 160) + (frame - MotionInfo->EndFrame * 160);
				}
				else
				{
					if (MotionInfo->State == CHRMOTION_STATE_DAMAGE && !PlayStunCount && !PlayStopCount &&
						SetMotionFromCode(CHRMOTION_STATE_WALK))
					{
						TargetMoveCount = 2;
					}
					else
						SetMotionFromCode(CHRMOTION_STATE_STAND);
					AutoMoveStep = 1;
				}

				if (PosBeginCount > 4)
				{
					x = (pX - PosBeginMove.x) >> FLOATNS;
					z = (pZ - PosBeginMove.z) >> FLOATNS;
					dist = x * x + z * z;

					PosBeginMove.x = pX;
					PosBeginMove.z = pZ;
					PosBeginCount = 0;

					if (dist < (32 * 32))
					{
						SetTargetPosi(PosiAround.x >> FLOATNS, PosiAround.z >> FLOATNS);
						TragetTraceMode = 0;

						y = (rand() % ANGLE_90) - ANGLE_45;
						Angle.y = (Angle.y + y)&ANGCLIP;

						TargetMoveCount = 10;
						OverLapPosi2 = FALSE;

						ptNextTarget.x = 0;
						ptNextTarget.y = 0;
						ptNextTarget.z = 0;

						if (!SetMotionFromCode(CHRMOTION_STATE_RUN))
						{
							SetMotionFromCode(CHRMOTION_STATE_WALK);
						}


						goto Skip_5;
					}
				}

				if (TargetMoveCount > 0)
				{
					TargetMoveCount--;
					if (TargetMoveCount <= 0) SetMotionFromCode(CHRMOTION_STATE_STAND);
				}

				if (DistAroundDbl && (MotionInfo->State == CHRMOTION_STATE_WALK ||
					MotionInfo->State == CHRMOTION_STATE_RUN))
				{

					x = (pX - PosiAround.x) >> FLOATNS;
					z = (pZ - PosiAround.z) >> FLOATNS;
					dist = x * x + z * z;
					if (dist > DistAroundDbl)
					{
						SetTargetPosi(PosiAround.x >> FLOATNS, PosiAround.z >> FLOATNS);
						ptNextTarget.x = ptNextTarget.z = 0;
						TargetMoveCount = 6;
						TragetTraceMode = 0;
					}
				}

				if (!TargetMoveCount && ptNextTarget.x && ptNextTarget.z)
				{

					SetTargetPosi(ptNextTarget.x >> FLOATNS, ptNextTarget.z >> FLOATNS);
					TragetTraceMode = TRUE;

					if (OverLapPosi && lpCharOverLap)
					{

						Angle.y = GetRadian2D(lpCharOverLap->pX >> FLOATNS, lpCharOverLap->pZ >> FLOATNS,
							pX >> FLOATNS, pZ >> FLOATNS);

						SetMotionFromCode(CHRMOTION_STATE_WALK);
						OverLapPosi2 = FALSE;
						AutoMoveStep = 0;
					}
					else
					{
						if (AutoMoveStep <= 0)
						{
							if (MotionInfo->State == CHRMOTION_STATE_STAND)
							{

								AutoMoveStep = smMonsterInfo.IQ - 5;
								if (AutoMoveStep < 0) AutoMoveStep = 0;

								x = (pX - ptNextTarget.x) >> FLOATNS;
								z = (pZ - ptNextTarget.z) >> FLOATNS;
								dist = x * x + z * z;

								if (smMonsterInfo.IQ >= 6 && dist < (64 * 8 * 64 * 8))
								{
									if (SetMotionFromCode(CHRMOTION_STATE_RUN))
									{
										AutoMoveStep <<= 2;
									}
									else
										SetMotionFromCode(CHRMOTION_STATE_WALK);
								}
								else
									SetMotionFromCode(CHRMOTION_STATE_WALK);
							}
							else
								SetMotionFromCode(CHRMOTION_STATE_STAND);
						}
						else
						{
							SetTargetPosi2(ptNextTarget.x >> FLOATNS, ptNextTarget.z >> FLOATNS);
							AutoMoveStep--;
						}
					}

					ptNextTarget.x = 0;
					ptNextTarget.y = 0;
					ptNextTarget.z = 0;
				}


				if (smMonsterInfo.PotionCount)
				{
					cnt = (smCharInfo.Life[0] * 100) / smCharInfo.Life[1];
					if (cnt < 30)
					{
						if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_NPC_MAGICMASTER)
						{

							smTransCommand.code = OpCode::OPCODE_PROCESS_SKILL2;
							smTransCommand.size = sizeof(smTRANS_COMMAND);
							smTransCommand.WParam = SKILL_PLAY_HEALING;
							smTransCommand.LParam = dwObjectSerial;
							smTransCommand.SParam = 0;
							smTransCommand.EParam = 0;
							if (lpLinkPlayInfo && lpLinkPlayInfo->lpsmSock)
								lpLinkPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

							smCharInfo.Life[0] += (smCharInfo.Life[1] >> 2);
							if (smCharInfo.Life[0] > smCharInfo.Life[1])
								smCharInfo.Life[0] = smCharInfo.Life[1];

						}
						else
						{
							SetMotionFromCode(CHRMOTION_STATE_EAT);
							PotionLog = 1;
						}

						smMonsterInfo.PotionCount--;
					}
				}

				if (dwNextMotionCode)
				{

					if (SetMotionFromCode(dwNextMotionCode) == FALSE)
					{
						SetMotionFromCode(CHRMOTION_STATE_STAND);
					}
					dwNextMotionCode = 0;
				}
				if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_HUNGKY)
				{

					cnt = (smCharInfo.Life[0] * 100) / smCharInfo.Life[1];
					if (cnt < 30 || AttackAnger>80)
					{
						SetMotionFromCode(CHRMOTION_STATE_WARP);
						lpTargetPlayInfo = 0;
					}
				}


				if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_BEBECHICK)
				{

					cnt = (smCharInfo.Life[0] * 100) / smCharInfo.Life[1];
					if (cnt < 30 || AttackAnger>80)
					{
						SetMotionFromCode(CHRMOTION_STATE_WARP);
						lpTargetPlayInfo = 0;
					}
				}

				if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_DEADHOPT)
				{
					cnt = (smCharInfo.Life[0] * 100) / smCharInfo.Life[1];
					if (cnt < 20 || AttackAnger > 80)
					{
						SetMotionFromCode(CHRMOTION_STATE_WARP);
						lpTargetPlayInfo = 0;
					}
				}

			}
		}
	Skip_5:
		if (DontMoveFlag == 2)
		{

			Angle.x = 0;
			Angle.y = 0;
			Angle.z = 0;
		}
		SavePlayBuff2();

		if (lpMasterPlayInfo && lpMasterPlayInfo->lpsmSock && smCharInfo.Life[0] > 0)
		{
			/*
			if (HoSkillCode && lpMasterPlayInfo->lpLinkChar != this)
			{
				smCharInfo.Life[0] = 0;
				SetMotionFromCode(CHRMOTION_STATE_DEAD);
			} */
			//else
			//{

				x = (lpMasterPlayInfo->Position.x - pX) >> FLOATNS;
				z = (lpMasterPlayInfo->Position.z - pZ) >> FLOATNS;
				dist = x * x + z * z;
				if (dist >= (500 * 500))
				{
					if (lpStage)
					{
						y = lpStage->GetHeight(lpMasterPlayInfo->Position.x, lpMasterPlayInfo->Position.z);
						if (y < 0)
						{
							smCharInfo.Life[0] = 0;
							SetMotionFromCode(CHRMOTION_STATE_DEAD);
						}
					}
					if (smCharInfo.Life[0] > 0)
					{
						pX = lpMasterPlayInfo->Position.x;
						pY = lpMasterPlayInfo->Position.y;
						pZ = lpMasterPlayInfo->Position.z;

						ptNextTarget.x = ptNextTarget.z = 0;
						TargetMoveCount = 0;
						TragetTraceMode = 0;

						lpTargetChar = 0;

					}
				}
				else if (dist >= (300 * 300) || (!lpTargetChar && dist >= (150 * 150)))
				{
					SetTargetPosi(lpMasterPlayInfo->Position.x >> FLOATNS, lpMasterPlayInfo->Position.z >> FLOATNS);
					TargetMoveCount = 2;
					TragetTraceMode = 0;
					lpTargetChar = 0;
					if (MotionInfo->State != CHRMOTION_STATE_DEAD && (MotionInfo->State >= 0x100 || MotionInfo->State == CHRMOTION_STATE_STAND))
					{
						if (!SetMotionFromCode(CHRMOTION_STATE_RUN))
							SetMotionFromCode(CHRMOTION_STATE_WALK);
					}
				}
			//}
		}

		if (dwLinkObjectCode)
		{
			switch (smCharInfo.dwCharSoundCode)
			{
			case snCHAR_SOUND_NPC_SKILLMASTER:
			case snCHAR_SOUND_NPC_MAGICMASTER:

				if (smCharInfo.Life[0] <= (smCharInfo.Life[1] >> 4))
				{

					smCharInfo.Life[0] = (smCharInfo.Life[1] >> 4);
					lpTargetPlayInfo = 0;
					lpTargetChar = 0;
					SetMotionFromCode(CHRMOTION_STATE_STAND);

					ActionPattern = 12;
					PosiAround.x = pX;
					PosiAround.y = pY;
					PosiAround.z = pZ;
					DistAroundDbl = 256 * 256;
					if (lpLinkPlayInfo && lpLinkPlayInfo->dwObjectSerial == dwLinkObjectCode && lpLinkPlayInfo->lpsmSock)
					{
						rsProcessQuest(lpLinkPlayInfo, this, SIN_QUEST_CODE_CHANGEJOB4, dwObjectSerial);
					}
					lpChar = rsGetLinkChar(this);
					if (lpChar)
					{
						lpChar->SetMotionFromCode(CHRMOTION_STATE_DEAD);
						lpChar->smCharInfo.Life[0] = 0;
					}

				}
				else
				{
					if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_NPC_MAGICMASTER)
					{

						if ((rand() % 100) < 3 && MotionInfo->State != CHRMOTION_STATE_SKILL && MotionInfo->State != CHRMOTION_STATE_EAT)
						{
							if (lpLinkPlayInfo)
							{
								x = (pX - lpLinkPlayInfo->Position.x) >> FLOATNS;
								z = (pZ - lpLinkPlayInfo->Position.z) >> FLOATNS;
								dist = x * x + z * z;
								if (dist < (300 * 300))
								{
									pX = QUEST_ARENA_NPC_POS_X + ((rand() % 600) - 300)*fONE;
									pZ = QUEST_ARENA_NPC_POS_Z + ((rand() % 600) - 300)*fONE;
								}
							}
						}
					}
				}
				break;

			case snCHAR_SOUND_FURY:

				if (smCharInfo.Life[0] <= 0 && !smMonsterInfo.PotionCount && smCharInfo.Life[1] > 1)
				{

					if (lpLinkPlayInfo && lpLinkPlayInfo->dwObjectSerial == dwLinkObjectCode && lpLinkPlayInfo->lpsmSock)
					{
						rsProcessQuest(lpLinkPlayInfo, this, HAQUEST_CODE_FURYOFPHANTOM, dwObjectSerial);
						smCharInfo.Life[1] = 1;
					}
				}
				break;
			}
		}

		if (lpTargetChar)
		{
			if (smMonsterInfo.SkillCurse && smCharInfo.Brood != smCHAR_MONSTER_USER && lpTargetChar->smCharInfo.Brood != smCHAR_MONSTER_USER)
			{

				if (MotionInfo->State < 0x100)
				{
					TargetMoveCount = 1;
					AutoMoveStep = 1;
					lpTargetChar = 0;
				}
			}
			else if (lpTargetChar->Flag && !PlayStunCount && !PlayStopCount)
			{

				dist = smCharInfo.Shooting_Range + 32;
				if (dist < 80) dist = 80;

				if (MotionInfo->State != CHRMOTION_STATE_DAMAGE &&
					MotionInfo->State != CHRMOTION_STATE_DEAD &&
					MotionInfo->State != CHRMOTION_STATE_EAT)
				{

					if (MotionInfo->State != CHRMOTION_STATE_ATTACK &&
						MotionInfo->State != CHRMOTION_STATE_SKILL && MotionInfo->State != CHRMOTION_STATE_DEAD)
					{

						cnt = GetDistanceDbl(pX, pZ, lpTargetChar->pX, lpTargetChar->pZ);

						dist = dist >> FLOATNS;
						dist *= dist;

						if (cnt < dist && abs(pY - lpTargetChar->pY) < 64 * fONE)
						{

							PosBeginMove.x = 0;
							PosBeginMove.z = 0;
							PosBeginCount = 0;

							dwLastTransTime = dwPlayServTime;

							SetMotionFromCode(CHRMOTION_STATE_ATTACK);

							if (smMonsterInfo.SkillRating > 0 && MotionInfo->State == CHRMOTION_STATE_ATTACK)
							{

								if ((rand() % 100) < smMonsterInfo.SkillRating)
									SetMotionFromCode(CHRMOTION_STATE_SKILL);
							}

							Angle.y = GetRadian2D(pX, pZ, lpTargetChar->pX, lpTargetChar->pZ);
							AttackX = lpTargetChar->pX;
							AttackY = lpTargetChar->pY;
							AttackZ = lpTargetChar->pZ;

						}
						else
						{
							if (cnt > DIST_TRANSLEVEL_LOW)
							{
								lpTargetChar = 0;
							}
						}
					}
				}

				if (smCharInfo.Brood != smCHAR_MONSTER_USER)
				{
					if (FrameCounter == 80 && smCharInfo.dwCharSoundCode == snCHAR_SOUND_BABEL)
					{
						AttackSkillRange = smMonsterInfo.SkillRange*smMonsterInfo.SkillRange;


						smCharInfo.Life[0] += rsGetMonsterLifeRegen(this);

						if (smCharInfo.Life[0] > smCharInfo.Life[1] || smCharInfo.Life[0] < 0)
							smCharInfo.Life[0] = smCharInfo.Life[1];
					}
				}


				if (FrameCounter == 40 && lpTargetChar)
				{

					if (MotionInfo->State == CHRMOTION_STATE_ATTACK || MotionInfo->State == CHRMOTION_STATE_SKILL)
					{

						AttackUserFlag = TRUE;
						AttackAnger++;
						cnt = sinGetPVPAccuracy(smCharInfo.Level, smCharInfo.Attack_Rating, lpTargetChar->smCharInfo.Level, lpTargetChar->smCharInfo.Defence);
						if ((rand() % 100) < cnt && lpTargetChar->smCharInfo.Life[0] > 0)
						{

							if (!lpTargetChar->lpTargetPlayInfo)
							{
								lpTargetChar->lpTargetChar = this;
							}
							else
							{
								dist = GetDistanceDbl(pX, pZ, lpTargetChar->pX, lpTargetChar->pZ);
								if (GetDistanceDbl(pX, pZ, lpTargetChar->lpTargetPlayInfo->Position.x, lpTargetChar->lpTargetPlayInfo->Position.z) > dist)
								{
									lpTargetChar->lpTargetChar = this;
									lpTargetChar->lpTargetPlayInfo = 0;
								}
							}



							if (MotionInfo->State == CHRMOTION_STATE_SKILL && smCharInfo.Attack_Damage[0])
							{
								cnt = GetRandomPos(smMonsterInfo.SkillDamage[0], smMonsterInfo.SkillDamage[1]);

								switch (smCharInfo.dwCharSoundCode)
								{
								case snCHAR_SOUND_GUARDIAN_SAINT:

									rsSkillDamage_AroundMonster(this);
									cnt = 0;
									break;
								}
							}
							else
							{
								cnt = GetRandomPos(smCharInfo.Attack_Damage[0], smCharInfo.Attack_Damage[1]);
							}


							if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_BABEL ||
								smCharInfo.dwCharSoundCode == snCHAR_SOUND_CHAOSCARA ||
								smCharInfo.dwCharSoundCode == snCHAR_SOUND_DEATHKNIGHT ||
								smCharInfo.dwCharSoundCode == snCHAR_SOUND_MOKOVA ||
								smCharInfo.dwCharSoundCode == snCHAR_SOUND_KELVEZU ||
								smCharInfo.dwCharSoundCode == snCHAR_SOUND_MOKOVA)
							{
								cnt *= 8;
								if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_KELVEZU)
								{
									lpTargetChar->smCharInfo.Life[0] = 0;
									cnt = 1;
								}
							}


							if (lpTargetChar)
								cnt -= (cnt*lpTargetChar->smCharInfo.Absorption) / 100;
							else
								cnt = 0;

							if (cnt > 0)
							{
								lpTargetChar->smCharInfo.Life[0] -= cnt;

								if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_WEB)
								{
									if (lpTargetChar->smCharInfo.dwCharSoundCode != snCHAR_SOUND_KELVEZU)
										lpTargetChar->PlaySlowCount = -36;
								}


								if (lpTargetChar->smCharInfo.Life[0] <= 0)
								{
									lpTargetChar->smCharInfo.Life[0] = 0;
									lpTargetChar->SetMotionFromCode(CHRMOTION_STATE_DEAD);
									if (lpMasterPlayInfo && lpMasterPlayInfo->lpsmSock && lpMasterPlayInfo->dwObjectSerial && lpMasterPlayInfo->dwObjectSerial == smCharInfo.Next_Exp)
									{
										lpTargetChar->lpExt2 = lpMasterPlayInfo;

										lpTargetChar->lpExt3 = this;
									}
									else
									{
										if (lpMasterPlayInfo)
										{

											smCharInfo.Life[0] = 0;
											SetMotionFromCode(CHRMOTION_STATE_DEAD);
										}
										else
										{
											lpTargetChar = 0;
										}
									}
								}
								else
								{
									if (lpTargetChar->MotionInfo->State < 0x100)
									{
										lpTargetChar->SetMotionFromCode(CHRMOTION_STATE_DAMAGE);
									}
								}
							}
						}
					}
				}
			}
			else
			{
				SetNextTarget(0, 0, 0);
			}

			if (lpTargetChar && (!lpTargetChar->Flag || lpTargetChar->smCharInfo.Life[0] <= 0))
			{
				lpTargetChar = 0;
				if (MotionInfo->State < 0x100)
				{
					TargetMoveCount = 1;
					AutoMoveStep = 1;
				}
			}


			if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_DEATHKNIGHT && lpTargetChar)
			{
				if (GetDistanceDbl(pX, pZ, lpTargetChar->pX, lpTargetChar->pZ) > 120 * 120)
				{
					lpTargetChar = 0;
					SetNextTarget(0, 0, 0);
				}
			}

		}


		cnt = TRUE;

		switch (smCharInfo.dwCharSoundCode)
		{
		case snCHAR_SOUND_VAMPRICMACHINE:

			if (rsGetMonCountFlag(this) > 3) cnt = FALSE;
			break;

		case snCHAR_SOUND_MYSTIC:
			if (MotionInfo->State == CHRMOTION_STATE_DEAD && FrameCounter < 16)
			{
				AttackSkillRange = smMonsterInfo.SkillRange*smMonsterInfo.SkillRange;
				AttackUserFlag = TRUE;
				FrameCounter = 16;
			}
			if (MotionInfo->State != CHRMOTION_STATE_DEAD)
			{
				if (Counter > 16 * 60 * 2)
				{
					smCharInfo.Life[0] = 0;
					SetMotionFromCode(CHRMOTION_STATE_DEAD);
					AttackSkillRange = smMonsterInfo.SkillRange*smMonsterInfo.SkillRange;
					AttackUserFlag = TRUE;
					FrameCounter = 16;
				}
			}
			if (lpTargetChar && MotionInfo->State == CHRMOTION_STATE_DEAD)
			{
				if (FrameCounter == 16 && lpTargetChar->MotionInfo->State != CHRMOTION_STATE_DEAD && lpTargetChar->smCharInfo.Life[0] > 0)
				{
					lpTargetChar->smCharInfo.Life[0] -= GetRandomPos(smMonsterInfo.SkillDamage[0], smMonsterInfo.SkillDamage[1]) * 2;
					if (lpTargetChar->smCharInfo.Life[0] <= 0)
					{
						lpTargetChar->smCharInfo.Life[0] = 0;
						lpTargetChar->SetMotionFromCode(CHRMOTION_STATE_DEAD);
					}
				}
				lpTargetChar = 0;
			}
			break;

		case snCHAR_SOUND_CHAOSCARA:
			if (MotionInfo->State == CHRMOTION_STATE_SKILL && MotionInfo->KeyCode != 'J')
			{
				smMonsterInfo.SkillRangeRect.left = 0;
				smMonsterInfo.SkillRangeRect.right = 0;
				smMonsterInfo.SkillRangeRect.top = 0;
				smMonsterInfo.SkillRangeRect.bottom = 0;
			}
			break;
		}





		if (!lpTargetChar && lpTargetPlayInfo && cnt)
		{
			if (lpTargetPlayInfo->lpsmSock && !PlayStunCount && !PlayStopCount)
			{

				dist = smCharInfo.Shooting_Range;

				if (MotionInfo->State != CHRMOTION_STATE_DAMAGE &&
					MotionInfo->State != CHRMOTION_STATE_DEAD &&
					MotionInfo->State != CHRMOTION_STATE_EAT && dist >= 0)
				{
					if (PlayAttackFromPosi(
						lpTargetPlayInfo->Position.x,
						lpTargetPlayInfo->Position.y,
						lpTargetPlayInfo->Position.z,
						dist) == TRUE)
					{

						PosBeginMove.x = 0;
						PosBeginMove.z = 0;
						PosBeginCount = 0;

						dwLastTransTime = dwPlayServTime;

						if (smMonsterInfo.SkillRating > 0 && MotionInfo->State == CHRMOTION_STATE_ATTACK)
						{

							if ((rand() % 100) < smMonsterInfo.SkillRating)
							{
								if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_NPC_MAGICMASTER && (rand() % 100) < 20)
								{

									SetMotionFromCode(CHRMOTION_STATE_EAT);
									PotionLog = 2;
								}
								else if (SetMotionFromCode(CHRMOTION_STATE_SKILL) > 0)
								{
									if (smMonsterInfo.SkillCurse)
									{

										switch (smMonsterInfo.SkillCurse)
										{
										case 102:
											lpChar = rsFindAroundMonster(this, 200);
											if (lpChar)
											{
												lpTargetChar = lpChar;
												lpTargetPlayInfo = 0;
												Angle.y = GetRadian2D(pX, pZ, lpTargetChar->pX, lpTargetChar->pZ);
											}
											else
											{

												if (SetMotionFromCode(CHRMOTION_STATE_ATTACK) == FALSE)
													SetMotionFromCode(CHRMOTION_STATE_STAND);
											}
											break;

										case 103:
											lpTargetPlayInfo->dwCurse_Attack_Time = dwPlayServTime + SUCCUBUS_CURSE_TIME * 1000;
											lpTargetPlayInfo->dwCurse_Attack_Param = GetRandomPos(10, 15);
											break;

										case 101:
											lpTargetPlayInfo->dwCurse_Defence_Time = dwPlayServTime + SUCCUBUS_CURSE_TIME * 1000;
											lpTargetPlayInfo->dwCurse_Defence_Param = GetRandomPos(2, 6);

											if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_MYSTIC)
												lpTargetPlayInfo->dwCurse_Defence_Param = GetRandomPos(10, 16);

											break;

										}
									}


									if (smMonsterInfo.SkillRange > 0)
									{


										AttackSkillRange = 0;

										if (smMonsterInfo.SkillDistance)
										{

											GetMoveLocation(0, 0, smMonsterInfo.SkillDistance*fONE, 0, Angle.y, 0);
											x = pX + GeoResult_X;
											z = pZ + GeoResult_Z;

											dist = smMonsterInfo.SkillRange << FLOATNS;

											smMonsterInfo.SkillRangeRect.left = x - dist;
											smMonsterInfo.SkillRangeRect.right = x + dist;
											smMonsterInfo.SkillRangeRect.top = z - dist;
											smMonsterInfo.SkillRangeRect.bottom = z + dist;
										}
									}

									switch (smCharInfo.dwCharSoundCode)
									{
									case snCHAR_SOUND_RATOO:

										rsSkillMonster_AroundMonster(this, 200);
										break;
									case snCHAR_SOUND_NPC_SKILLMASTER:
										cnt = rand() % 100;
										if (cnt < 3 && !rsGetLinkChar(this) && lpLinkPlayInfo)
										{
											if ((cnt & 1) == 0)
											{
												lpChar = OpenMonsterFromSkill(SKILL_PLAY_METAL_GOLEM, pX, pY, pZ, lpLinkPlayInfo, this);
												if (lpChar)
												{
													lpChar->smCharInfo.wPlayClass[1] = fONE + 5 * 15;
													lpChar->sMoveStepCount[0] = 1;
													lpChar->sMoveStepCount[1] = 2;




												}
											}
											else
											{
												lpChar = OpenMonsterFromSkill(SKILL_PLAY_RECALL_WOLVERIN, pX, pY, pZ, lpLinkPlayInfo, this);
												if (lpChar)
												{
													lpChar->smCharInfo.wPlayClass[1] = (fONE / 2) + 5 * 12;
													lpChar->sMoveStepCount[0] = 1;
													lpChar->sMoveStepCount[1] = 2;




												}
											}
										}
										break;
									case snCHAR_SOUND_NPC_MAGICMASTER:
										cnt = rand() % 100;
										if (cnt < 3 && !rsGetLinkChar(this) && lpLinkPlayInfo)
										{
											lpChar = OpenMonsterFromSkill(SKILL_PLAY_FIRE_ELEMENTAL, pX, pY, pZ, lpLinkPlayInfo, this);
											if (lpChar)
											{
												lpChar->sMoveStepCount[0] = 1;
												lpChar->sMoveStepCount[1] = 2;




											}
										}
										break;
									}
								}
							}
						}
					}
				}

				EvtFrame = 0;
				if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_BABEL)
				{
					if (FrameCounter == 40 || FrameCounter == 80)
						EvtFrame = 1;
				}


				if ((!EvtFrame && FrameCounter == 40) || EvtFrame)
				{
					if (MotionInfo->State == CHRMOTION_STATE_ATTACK &&
						rsProcessAttack_SkillHolyReflection(lpTargetPlayInfo, this) == TRUE)
					{

						if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_VAMPRICMACHINE)
						{
							cnt = 0;

							rsOpenSubMonster(this, snCHAR_SOUND_VAMPRICBEE, pX, pY, pZ, 4);
						}
						else
						{
							if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_BABEL && (rand() % 100) < 60)
							{

								rsSendRangeDamage(this, lpTargetPlayInfo, 100, fONE / 2);

								x = (lpTargetPlayInfo->Position.x - pX) >> FLOATNS;
								z = (lpTargetPlayInfo->Position.z - pZ) >> FLOATNS;
								dist = x * x + z * z;
								if (dist > (200 * 200))
								{

									dm1 = smCharInfo.Attack_Damage[0];
									dm2 = smCharInfo.Attack_Damage[1];

									smCharInfo.Attack_Damage[0] = (smCharInfo.Attack_Damage[0] * 70) / 100;
									smCharInfo.Attack_Damage[1] = (smCharInfo.Attack_Damage[1] * 70) / 100;
									cnt = SendTransAttack(0, lpTargetPlayInfo->lpsmSock, 0);

									smCharInfo.Attack_Damage[0] = dm1;
									smCharInfo.Attack_Damage[1] = dm2;
								}
								else
								{

									cnt = SendTransAttack(0, lpTargetPlayInfo->lpsmSock, 0);
								}

							}
							else
							{
								cnt = SendTransAttack(0, lpTargetPlayInfo->lpsmSock, 0);
							}
						}

						if (cnt)
						{

							lpTargetPlayInfo->Send_AttackCount++;
							lpTargetPlayInfo->Send_AttackDamage += cnt;




							if (smCharInfo.wPlayClass[0] == MONSTER_CLASS_HAMMER &&
								lpTargetPlayInfo->smCharInfo.SizeLevel <= 0x1000 || lpTargetPlayInfo->smCharInfo.SizeLevel > 0x1002)
							{

								if (dwEventAttackParam != lpTargetPlayInfo->dwObjectSerial)
								{

									EventAttackCount = 0;
									dwEventAttackParam = lpTargetPlayInfo->dwObjectSerial;
								}

								EventAttackCount++;

								if (EventAttackCount >= 10)
								{

									smTransCommand.size = sizeof(smTRANS_COMMAND);
									smTransCommand.code = OpCode::OPCODE_COMIC_SKIN;
									smTransCommand.WParam = (rand() % 2) + 1;
									smTransCommand.LParam = 60 * 10;
									smTransCommand.SParam = 0;
									smTransCommand.EParam = 0;
									lpTargetPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

									if (smMonsterInfo.UseEventModel && smCharInfo.szModelName2[1])
									{


										Close();

										strcpy_s(smCharInfo.szModelName, smCharInfo.szModelName2 + 1);
										SetLoadPattern(smCharInfo.szModelName);
										smCharInfo.bUpdateInfo[0]++;
										SetMotionFromCode(CHRMOTION_STATE_STAND);

									}

									smCharInfo.wPlayClass[0] = MONSTER_CLASS_NORMAL;
									smMonsterInfo.UseEventModel = 0;
								}

								TRANS_CHATMESSAGE	TransChatMessage;
								wsprintf(TransChatMessage.szMessage, "%s: %d ", smCharInfo.szName, EventAttackCount);
								TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
								TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
								TransChatMessage.dwIP = 0;
								TransChatMessage.dwObjectSerial = dwObjectSerial;

								rsSendCommandUser2(lpTargetPlayInfo, (smTRANS_COMMAND *)&TransChatMessage);
							}
						}

						AttackUserFlag = TRUE;
						AttackAnger++;

						if (lpTargetPlayInfo->BadPlayer == 4 && lpTargetPlayInfo->lpsmSock)
						{
							if ((smCharInfo.Level + 6) > lpTargetPlayInfo->smCharInfo.Level && (rand() % 100) > 92)
							{

								smTransCommand.code = OpCode::OPCODE_DEAD_PLAYER;
								smTransCommand.size = sizeof(smTRANS_COMMAND);
								smTransCommand.WParam = 0;
								smTransCommand.LParam = 0;
								smTransCommand.SParam = 0;
								smTransCommand.EParam = 0;
								lpTargetPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
								lpTargetPlayInfo->BadPlayer = 2;
							}
						}
					}
				}

				EvtFrame = 32;

				if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_BABEL || smCharInfo.dwCharSoundCode == snCHAR_SOUND_DEATHKNIGHT)
				{
					EvtFrame = 120;
					if (FrameCounter == EvtFrame)
					{

						smCharInfo.Life[0] += rsGetMonsterLifeRegen(this);

						if (smCharInfo.Life[0] > smCharInfo.Life[1] || smCharInfo.Life[0] < 0)
							smCharInfo.Life[0] = smCharInfo.Life[1];

					}
				}

				if (FrameCounter == EvtFrame)
				{
					if (MotionInfo->State == CHRMOTION_STATE_SKILL)
					{
						if (smCharInfo.dwCharSoundCode != snCHAR_SOUND_MYSTIC)
						{
							AttackSkillRange = smMonsterInfo.SkillRange*smMonsterInfo.SkillRange;
							if (!AttackSkillRange && lpTargetPlayInfo)
							{

								rsSendTransSkillAttack(this, lpTargetPlayInfo);
							}
							AttackUserFlag = TRUE;
						}
					}
				}

			}
			else
			{
				SetNextTarget(0, 0, 0);
			}
		}


		if (PlaySlowCount > 0)
			PlaySlowCount--;

		if (PlaySlowCount < 0)
			PlaySlowCount++;

		if (PlayStunCount > 0)
			PlayStunCount--;

		if (PlayStopCount > 0)
			PlayStopCount--;

		if (PlayHolyMind[1] > 0)
			PlayHolyMind[1]--;

		if (PlayHolyPower[1] > 0)
			PlayHolyPower[1]--;

		if (PlayWisp[1] > 0)
			PlayWisp[1]--;

		if (PlayCurseLazy > 0)
			PlayCurseLazy--;

		if (PlayPoison[1] > 0)
		{
			PlayPoison[1]--;
			if ((Counter & 0xF) == 0)
			{
				if (smCharInfo.Life[0] > 0 && MotionInfo->State != CHRMOTION_STATE_DEAD)
				{
					smCharInfo.Life[0] -= PlayPoison[0];
					if (smCharInfo.Life[0] < 1)
					{
						smCharInfo.Life[0] = 1;

						PlayPoison[1] = 0;
					}
				}
			}
		}

		if (PlayHolyIncantation[1] > 0)
		{
			PlayHolyIncantation[1]--;
			if (PlayHolyIncantation[1] == 0 && smCharInfo.Brood == smCHAR_MONSTER_USER)
			{
				smCharInfo.Brood = PlayHolyIncantation[0];
				smCharInfo.bUpdateInfo[0]++;
				lpMasterPlayInfo = 0;
			}
		}

		if (UseObject_VirtualLife)
		{

			if (sObject_VirtualLife[0] > 0)
			{
				cnt = (smCharInfo.Life[0] * 100) / smCharInfo.Life[1];
				if (cnt <= 10)
				{
					sObject_VirtualLife[0] --;
					smCharInfo.Life[0] = smCharInfo.Life[1];

					if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_KELVEZU && (sObject_VirtualLife[0] & 0x1) == 0)
					{

						rsOpenSubMonster(this, snCHAR_SOUND_CHAOSCARA, pX + ((rand() % (200 * fONE)) - 100 * fONE), 0, pZ + ((rand() % (200 * fONE)) - 100 * fONE), 8);
						rsOpenSubMonster(this, snCHAR_SOUND_CHAOSCARA, pX + ((rand() % (200 * fONE)) - 100 * fONE), 0, pZ + ((rand() % (200 * fONE)) - 100 * fONE), 8);
					}
					else if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_MOKOVA && (sObject_VirtualLife[0] & 0x1) == 0)
					{

						rsOpenSubMonster(this, snCHAR_SOUND_DARKGUARD, pX + ((rand() % (200 * fONE)) - 100 * fONE), 0, pZ + ((rand() % (200 * fONE)) - 100 * fONE), 8);
						rsOpenSubMonster(this, snCHAR_SOUND_DARKGUARD, pX + ((rand() % (200 * fONE)) - 100 * fONE), 0, pZ + ((rand() % (200 * fONE)) - 100 * fONE), 8);
					}

				}
			}


			cnt = (smCharInfo.Life[0] * 100) / smCharInfo.Life[1];
			sObject_DisplayLife[0] = sObject_VirtualLife[0] * 100;
			sObject_DisplayLife[0] += cnt;
			sObject_DisplayLife[1] = (sObject_VirtualLife[1] + 1) * 100;

			if (sObject_DisplayLife[0] <= 0 && smCharInfo.Life[0] > 0)
			{
				sObject_DisplayLife[0] = 1;
			}

			if (sObject_DisplayLife[0] > sObject_DisplayLife[1])
				sObject_DisplayLife[0] = sObject_DisplayLife[1];

		}

		FrameCounter += 3;
		break;


	case 10:
	case 11:
		if (MotionInfo->State && MotionInfo->State < 0x100)
		{
			if (MotionInfo->State == CHRMOTION_STATE_WALK)
			{
				MoveAngle(SERVER_CHAR_SKIP);
				if (MotionInfo->State != CHRMOTION_STATE_WALK) SetMotionFromCode(CHRMOTION_STATE_WALK);
			}
			else
			{
				if (MotionInfo->State != CHRMOTION_STATE_STAND) SetMotionFromCode(CHRMOTION_STATE_STAND);
			}

		}

		frame += SERVER_CHAR_FRAME_STEP;

		if (frame > MotionInfo->EndFrame * 160)
		{

			if (MotionInfo->State == CHRMOTION_STATE_DEAD)
			{
				frame = MotionInfo->EndFrame * 160;
			}
			else
			{

				if (MotionInfo->Repeat == TRUE)
				{
					frame = (MotionInfo->StartFrame * 160) + (frame - MotionInfo->EndFrame * 160);
				}
				else SetMotionFromCode(CHRMOTION_STATE_STAND);



				if (MotionInfo->State == CHRMOTION_STATE_STAND)
				{
					cnt = rand() % ANGCLIP;
					if (((cnt >> 2) & 3) == 0)
					{

						if (ActionPattern == 10)
						{
							if (!SetMotionFromCode(CHRMOTION_STATE_SOMETIME))
							{
								Angle.y = cnt & ANGCLIP;
								SetMotionFromCode(CHRMOTION_STATE_WALK);
							}
						}
						else
						{
							if (!SetMotionFromCode(TRUE))
							{
								Angle.y = cnt & ANGCLIP;
								SetMotionFromCode(CHRMOTION_STATE_WALK);
							}
						}
					}
					else
					{
						Angle.y = cnt & ANGCLIP;
						SetMotionFromCode(CHRMOTION_STATE_WALK);
					}

					if (MotionInfo->State == CHRMOTION_STATE_WALK)
					{

						x = (pX - PosiAround.x) >> FLOATNS;
						z = (pZ - PosiAround.z) >> FLOATNS;
						dist = x * x + z * z;
						if (dist > DistAroundDbl)
						{
							SetTargetPosi(PosiAround.x >> FLOATNS, PosiAround.z >> FLOATNS);
						}
					}
				}
				else SetMotionFromCode(CHRMOTION_STATE_STAND);

				if (OverLapPosi && lpCharOverLap)
				{

					Angle.y = GetRadian2D(lpCharOverLap->pX >> FLOATNS, lpCharOverLap->pZ >> FLOATNS,
						pX >> FLOATNS, pZ >> FLOATNS);

					SetMotionFromCode(CHRMOTION_STATE_WALK);
					OverLapPosi2 = FALSE;
				}
			}
		}
		SavePlayBuff();
		FrameCounter += 3;
		break;

	case 12:



		if (smMotionInfo->NpcMotionRate[CHRMOTION_EXT])
		{

			if (MotionInfo->State == CHRMOTION_STATE_WARP)
			{

				frame += SERVER_CHAR_FRAME_STEP;
				if (frame > MotionInfo->EndFrame * 160)
				{
					Close();
					return TRUE;
				}
				SavePlayBuff();
				FrameCounter += 3;
				break;
			}


			int TalkCnt = 0;
			if (MotionInfo->State == CHRMOTION_STATE_WALK)
			{
				x = pX; z = pZ;
				MoveAngle(SERVER_CHAR_SKIP);

				if (x == pX && z == pZ)
				{
					TalkCnt = rand() % 100;
					TalkCnt = smMotionInfo->NpcMotionRateCnt[TalkCnt];

					if (TalkCnt == action && smMotionInfo->MotionInfo[TalkCnt].State == CHRMOTION_STATE_WALK)
					{

						x = (pX - PosiAround.x) >> FLOATNS;
						z = (pZ - PosiAround.z) >> FLOATNS;
						dist = x * x + z * z;
						if (dist > DistAroundDbl)
							SetTargetPosi(PosiAround.x >> FLOATNS, PosiAround.z >> FLOATNS);
					}
					else
					{
						frame = MotionInfo->EndFrame * 160;
						MotionInfo->State = CHRMOTION_STATE_STAND;
					}
				}
			}

			frame += SERVER_CHAR_FRAME_STEP;
			if (frame > MotionInfo->EndFrame * 160)
			{
				if (MotionInfo->State == CHRMOTION_STATE_WALK)
					frame = (MotionInfo->StartFrame * 160) + (frame - MotionInfo->EndFrame * 160);
				else if (smCharInfo.dwCharSoundCode != snCHAR_SOUND_FURY)
				{
					if (TalkCnt == 0)
						TalkCnt = rand() % 100;

					ChangeMotion(smMotionInfo->NpcMotionRateCnt[TalkCnt]);
					if (MotionInfo->State == CHRMOTION_STATE_WALK)
					{

						x = (pX - PosiAround.x) >> FLOATNS;
						z = (pZ - PosiAround.z) >> FLOATNS;
						dist = x * x + z * z;
						if (dist > DistAroundDbl)
							SetTargetPosi(PosiAround.x >> FLOATNS, PosiAround.z >> FLOATNS);
					}
					else
						Angle.y = rand() % ANGCLIP;
				}
				else
					SetMotionFromCode(CHRMOTION_STATE_STAND);
			}
		}

		else
		{
			if (MotionInfo->State == CHRMOTION_STATE_WARP)
			{

				frame += SERVER_CHAR_FRAME_STEP;

				if (frame > MotionInfo->EndFrame * 160)
				{
					Close();
					return TRUE;
				}
				SavePlayBuff();
				FrameCounter += 3;
				break;
			}


			if (MotionInfo->State && MotionInfo->State < 0x100)
			{
				if (MotionInfo->State == CHRMOTION_STATE_WALK)
				{
					x = pX; z = pZ;

					MoveAngle(SERVER_CHAR_SKIP);

					if (x == pX && z == pZ)
					{
						Angle.y = rand() % ANGCLIP;
					}

					if (MotionInfo->State != CHRMOTION_STATE_WALK) SetMotionFromCode(CHRMOTION_STATE_WALK);
				}
				else
				{
					if (MotionInfo->State != CHRMOTION_STATE_STAND) SetMotionFromCode(CHRMOTION_STATE_STAND);
				}
			}

			frame += SERVER_CHAR_FRAME_STEP;

			if (frame > MotionInfo->EndFrame * 160)
			{

				if (MotionInfo->State == CHRMOTION_STATE_DEAD)
				{
					frame = MotionInfo->EndFrame * 160;
				}
				else
				{

					if (MotionInfo->Repeat == TRUE)
					{
						frame = (MotionInfo->StartFrame * 160) + (frame - MotionInfo->EndFrame * 160);
					}
					else SetMotionFromCode(CHRMOTION_STATE_STAND);



					if (MotionInfo->State == CHRMOTION_STATE_STAND && smCharInfo.dwCharSoundCode != snCHAR_SOUND_FURY)
					{
						cnt = rand() % ANGCLIP;
						if (((cnt >> 2) & 3) == 0)
						{

							if (!SetMotionFromCode(TRUE))
							{
								if (MoveSpeed) Angle.y = cnt & ANGCLIP;

								if (DistAroundDbl)
									SetMotionFromCode(CHRMOTION_STATE_WALK);
								else
									SetMotionFromCode(CHRMOTION_STATE_STAND);
							}
						}
						else
						{
							SetMotionFromCode(CHRMOTION_STATE_STAND);
						}

						if (MotionInfo->State == CHRMOTION_STATE_WALK)
						{

							x = (pX - PosiAround.x) >> FLOATNS;
							z = (pZ - PosiAround.z) >> FLOATNS;
							dist = x * x + z * z;
							if (dist > DistAroundDbl)
							{
								SetTargetPosi(PosiAround.x >> FLOATNS, PosiAround.z >> FLOATNS);
							}
						}
					}
					else SetMotionFromCode(CHRMOTION_STATE_STAND);

				}
			}
		}

		SavePlayBuff();
		FrameCounter += 3;
		break;





	case 99:

		if (PlayBuffCnt == PlayBuffPosi_End)
		{

			if (MotionInfo->State != CHRMOTION_STATE_STAND && MotionInfo->State != CHRMOTION_STATE_DEAD && MotionInfo->State != CHRMOTION_STATE_WARP &&
				MotionInfo->State != CHRMOTION_STATE_ATTACK && MotionInfo->State != CHRMOTION_STATE_SKILL)
				SetMotionFromCode(CHRMOTION_STATE_STAND);

			frame += 80;
			compFrame = frame / 160;

			if (compFrame >= MotionInfo->EndFrame)
			{
				if (MotionInfo->Repeat)
				{
					ChangeMotion(action, AnimDispMode);
				}
				else
					frame = (MotionInfo->EndFrame) * 160;

				if (MotionInfo->State == CHRMOTION_STATE_ATTACK || MotionInfo->State == CHRMOTION_STATE_SKILL)
					SetMotionFromCode(CHRMOTION_STATE_STAND);

			}
			TransDelayCheck();

		}
		else
		{
			playBuff = &PlayBuff[PlayBuffCnt & PLAYBUFF_MASK];
			OldAction = action;

			Angle.x = playBuff->angle[0];
			Angle.y = playBuff->angle[1];
			Angle.z = playBuff->angle[2];
			action = playBuff->angle[3];

			if (!action)
			{
				action = OldAction;

				x = abs(pX - playBuff->x);
				y = abs(pY - playBuff->y);
				z = abs(pZ - playBuff->z);

				cnt = x + y + z;

				if (cnt > 32)
				{
					if (MotionInfo->State != CHRMOTION_STATE_WALK && MotionInfo->State != CHRMOTION_STATE_RUN)
					{

						if (cnt < 512)
						{

							SetMotionFromCode(CHRMOTION_STATE_WALK);
						}
						else
						{

							if (!SetMotionFromCode(CHRMOTION_STATE_RUN))
								SetMotionFromCode(CHRMOTION_STATE_WALK);
						}
					}
				}
				else
				{
					if (MotionInfo->State != CHRMOTION_STATE_STAND)
					{
						SetMotionFromCode(CHRMOTION_STATE_STAND);
					}
				}
			}

			pX = playBuff->x;
			pY = playBuff->y;
			pZ = playBuff->z;

			PHeight = pY;


			if (!playBuff->dwTargetSerial) chrAttackTarget = 0;
			else
			{
				if (chrAttackTarget && chrAttackTarget->dwObjectSerial == playBuff->dwTargetSerial)
				{

				}
				else
					chrAttackTarget = FindChrPlayer(playBuff->dwTargetSerial);
			}

			if (playBuff->frame < smPLAYBUFF_FRAME_NONE)
			{



				frame = playBuff->frame & CHAR_FRAME_MASK;


				MotionSelectFrame = playBuff->frame >> CHAR_FRAME_SELSHIFT;
				if (AnimDispMode)
				{
					if (MotionSelectFrame)
						PatDispMode = DISP_MODE_PATSUB;
					else
					{
						PatDispMode = DISP_MODE_PATMAIN;
					}
				}

				if (action)
				{

					if (PatDispMode == DISP_MODE_PATSUB)
						MotionInfo = &smMotionInfo2->MotionInfo[action];
					else
						MotionInfo = &smMotionInfo->MotionInfo[action];



					FrameInfo.StartFrame = MotionInfo->StartFrame * 160;
					FrameInfo.EndFrame = MotionInfo->EndFrame * 160;

				}

				if (OldMotionState != MotionInfo->State)
				{

					if (MotionInfo->State >= 0x100 && MotionInfo->State != CHRMOTION_STATE_ATTACK && MotionInfo->State != CHRMOTION_STATE_SKILL)
					{


						CharPlaySound(this);

					}
					else
					{

						if (smCharInfo.State == smCHAR_STATE_ENEMY && MotionInfo->State == CHRMOTION_STATE_STAND && (rand() % 4) == 0)
							CharPlaySound(this);
					}



					if (!MotionEvent && (OldMotionState == CHRMOTION_STATE_ATTACK || OldMotionState == CHRMOTION_STATE_SKILL))
					{
						if (MotionInfo->EventFrame[0])
						{
							EventAttack();

							dwAttackPlayTime = 0;
							ResetAttackTrans();
						}
						PlayAttack();
					}
					MotionEvent = 0;

					if (playBuff->wStickItems[smPLAYBUFF_ITEM_SKIL] >= 0)
					{

						BeginSkill(playBuff->wStickItems[smPLAYBUFF_ITEM_SKIL], 0, chrAttackTarget, 0, 0, 0);

					}

					if (smCharInfo.State == smCHAR_STATE_ENEMY)
					{
						if (MotionInfo->State == CHRMOTION_STATE_SKILL)
							BeginSkill(0, 0, chrAttackTarget, 0, 0, 0);

						if (MotionInfo->State == CHRMOTION_STATE_ATTACK)
							BeginAttack_Monster();

						if (OldMotionState == CHRMOTION_STATE_SKILL)
						{
							PlayAttack();
						}

					}

					switch (MotionInfo->State)
					{
					case CHRMOTION_STATE_RESTART:
						StartEffect(pX, pY, pZ, EFFECT_GAME_START1);
						SetDynLight(pX, pY, pZ, 100, 100, 100, 0, 200);
						CharPlaySound(this);
						break;
					case CHRMOTION_STATE_WARP:
						if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_WOLVERLIN)
						{

							StartEffect(pX, pY + 48 * fONE, pZ, EFFECT_RETURN1);
							SkillPlaySound(SKILL_SOUND_LEARN, pX, pY, pZ);
							SetDynLight(pX, pY, pZ, 50, 100, 70, 0, 300, 1);
							CharPlaySound(this);
						}
						break;

					case CHRMOTION_STATE_DEAD:
						FrameCounter = 0;
						switch (smCharInfo.dwCharSoundCode)
						{
						case snCHAR_SOUND_DEADZONE:
							AssaParticle_MonsterDeadZoneDead(this);
							break;
						case snCHAR_SOUND_HYPERMACHINE:
							AssaParticle_MonsterHyperDead(this);
							break;
						case snCHAR_SOUND_MYSTIC:
							ParkAssaParticle_MisticSpinel(this);
							break;
						case snCHAR_SOUND_DARKMAGE:
							ParkAssaParticle_DarkMageDead(this);
							break;
						}
						break;
					}
				}
			}
			else
			{
				frame += playBuff->frame & 0xFFFF;

			}



			AttackSkil = playBuff->wStickItems[smPLAYBUFF_ITEM_SKIL];
			EventAttack();

			if (smCharInfo.State != smCHAR_STATE_USER &&
				(MotionInfo->State == CHRMOTION_STATE_WALK || MotionInfo->State == CHRMOTION_STATE_RUN))
			{

				if (MotionInfo->EventFrame[0])
				{
					compFrame = frame - (MotionInfo->StartFrame * 160);
					if (MotionInfo->EventFrame[0] > (compFrame - 80) && MotionInfo->EventFrame[0] <= compFrame)
					{
						CharPlaySound(this);
					}
				}

				if (MotionInfo->EventFrame[1])
				{
					compFrame = frame - (MotionInfo->StartFrame * 160);
					if (MotionInfo->EventFrame[1] > (compFrame - 80) && MotionInfo->EventFrame[1] <= compFrame)
					{
						CharPlaySound(this);
					}
				}
			}

			FrameStep = 80;

			if (MotionInfo->State == CHRMOTION_STATE_EAT)
			{

				if (MotionInfo->EventFrame[0])
				{
					compFrame = frame - (MotionInfo->StartFrame * 160);
					if (MotionInfo->EventFrame[0] > (compFrame - FrameStep) && MotionInfo->EventFrame[0] <= compFrame)
					{
						if (smCharInfo.State == smCHAR_STATE_USER)
							cnt = pY + 48 * fONE;
						else
							cnt = pY + PatHeight;

						switch (PotionLog)
						{
						case 1:
							StartEffect(pX, cnt, pZ, EFFECT_POTION1);
							sinPlaySound(SIN_SOUND_EAT_POTION, GetDistVolume(pX, cnt, pZ));
							break;
						case 2:
							StartEffect(pX, cnt, pZ, EFFECT_POTION2);
							sinPlaySound(SIN_SOUND_EAT_POTION, GetDistVolume(pX, cnt, pZ));
							break;
						case 3:
							StartEffect(pX, cnt, pZ, EFFECT_POTION3);
							sinPlaySound(SIN_SOUND_EAT_POTION, GetDistVolume(pX, cnt, pZ));
							break;
						case 4:
							StartEffect(pX, cnt, pZ, EFFECT_POTION3);
							StartEffect(pX, cnt, pZ, EFFECT_POTION2);
							StartEffect(pX, cnt, pZ, EFFECT_POTION1);
							sinPlaySound(SIN_SOUND_EAT_POTION, GetDistVolume(pX, cnt, pZ));
							break;

						case POTION_ETHERCORE:
							StartEffect(pX, pY + 48 * fONE, pZ, EFFECT_RETURN1);
							SkillPlaySound(SKILL_SOUND_LEARN, pX, cnt, pZ);
						}
						SetDynLight(pX, cnt, pZ, 50, 100, 70, 0, 250, 1);
					}
				}
			}

			compFrame = frame / 160;

			if (compFrame < MotionInfo->StartFrame)
				frame = MotionInfo->StartFrame * 160;


			if (compFrame >= MotionInfo->EndFrame)
			{
				if (MotionInfo->Repeat)
				{
					ChangeMotion(action, AnimDispMode);
				}
				else
					frame = (MotionInfo->EndFrame) * 160;

				AttackEffect = 0;
			}




			if ((smCharInfo.State == smCHAR_STATE_USER || PkMode_CharState == smCHAR_STATE_USER) && DisplayFlag)
			{


				if (playBuff->wStickItems[smPLAYBUFF_ITEM_LEFT] != wStickItems[smPLAYBUFF_ITEM_LEFT])
				{
					if (playBuff->wStickItems[smPLAYBUFF_ITEM_LEFT] >= 0)
					{
						SetTool(sItem[playBuff->wStickItems[smPLAYBUFF_ITEM_LEFT]].CODE, hvPOSI_LHAND);
						HvLeftHand.ColorBlink = 0;
						HvLeftHand.DispEffect = 0;
					}
					else
						SetTool(0, hvPOSI_LHAND);
				}

				if (playBuff->wStickItems[smPLAYBUFF_ITEM_RIGHT] != wStickItems[smPLAYBUFF_ITEM_RIGHT])
				{
					if (playBuff->wStickItems[smPLAYBUFF_ITEM_RIGHT] >= 0)
					{
						SetTool(sItem[playBuff->wStickItems[smPLAYBUFF_ITEM_RIGHT]].CODE, hvPOSI_RHAND);
						HvRightHand.ColorBlink = 0;
						HvRightHand.DispEffect = 0;
					}
					else
						SetTool(0, hvPOSI_RHAND);
				}

				if (playBuff->wStickItems[smPLAYBUFF_ITEM_BODY] != wStickItems[smPLAYBUFF_ITEM_BODY])
				{
					SetChrArmor(this, playBuff->wStickItems[smPLAYBUFF_ITEM_BODY]);
					wStickItems[smPLAYBUFF_ITEM_BODY] = playBuff->wStickItems[smPLAYBUFF_ITEM_BODY];
				}
			}



			PlayBuffCnt++;
			MoveCnt = 0;




			if (((MotionInfo->State == CHRMOTION_STATE_ATTACK || MotionInfo->State == CHRMOTION_STATE_DAMAGE) &&
				smCharInfo.dwCharSoundCode == snCHAR_SOUND_MINIG))
			{
				AttackAnger += 2;
				if (AttackAnger > 100) AttackAnger = 100;
			}
			else
			{
				AttackAnger -= 1;
				if (AttackAnger <= 0) AttackAnger = 0;
			}

			if (AttackIce != 0)
			{

				if (AttackIce > 0 && AttackIce < 160) AttackIce++;
				if (AttackIce < 0) AttackIce++;
				if (MotionInfo->State == CHRMOTION_STATE_DEAD) AttackIce = 0;
			}

			if (DispPoison != 0)
			{

				if (DispPoison > 0 && DispPoison < 100) DispPoison++;
				if (DispPoison < 0) DispPoison++;
				if (MotionInfo->State == CHRMOTION_STATE_DEAD) DispPoison = 0;
			}

			if (PlayDistortion > 0)
			{

				PlayDistortion--;
			}

			if (PlayCurseLazy > 0)
			{

				PlayCurseLazy--;
			}

			if ((PlayBuffCnt & 0x3F) == 0 && smCharInfo.State != TRUE)
			{
				OnStageField = -1;
				if (smGameStage[0])
				{
					cnt = smGameStage[0]->GetFloorHeight(pX, pY, pZ, Pattern->SizeHeight);
					OnStageField = 0;
				}
				if (cnt == CLIP_OUT && smGameStage[1])
				{
					OnStageField = 1;
				}
			}

			if (dwAttackPlayTime && dwAttackPlayTime < dwPlayTime)
			{

				PlayAttack(TRUE);
				dwAttackPlayTime = 0;
			}


			OldMotionState = MotionInfo->State;



			DisplayFlag = TRUE;
		}

		if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_WOLVERLIN && smCharInfo.State == smCHAR_STATE_ENEMY)
		{
			if ((Counter & 0x1) == 0 && MotionInfo->State != CHRMOTION_STATE_DEAD && MotionInfo->State == CHRMOTION_STATE_RUN)
			{
				GetMoveLocation(0, 0, ((rand() % 48) - 24)*fONE, 0, Angle.y, 0);
				sinSetEffect(SIN_PARTICLE_SPOUT, pX + GeoResult_X, pY + 30 * fONE, pZ + GeoResult_Z, 1000, SIN_PARTICLE_COLOR_GOLD);
			}
			if (MotionInfo->State == CHRMOTION_STATE_DEAD)
			{
				if (sAddColorEffect[SMC_R] > 0) sAddColorEffect[SMC_R]--;
				if (sAddColorEffect[SMC_G] > 0) sAddColorEffect[SMC_G]--;
				if (sAddColorEffect[SMC_B] > 0) sAddColorEffect[SMC_B]--;
			}
		}

		if (smCharInfo.wPlayClass[0] == MONSTER_CLASS_BOSS)
		{

			if (MotionInfo->State == CHRMOTION_STATE_DEAD)
			{
				if (sAddColorEffect[SMC_R] > 0) sAddColorEffect[SMC_R]--;
				if (sAddColorEffect[SMC_G] > 0) sAddColorEffect[SMC_G]--;
				if (sAddColorEffect[SMC_B] > 0) sAddColorEffect[SMC_B]--;
			}

		}

		if (smCharInfo.wPlayClass[1])
		{
			if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_HOBGOBLIN && smCharInfo.Level == 60)
			{

				cnt = ((smCharInfo.Life[1] - smCharInfo.Life[0]) * 460) / smCharInfo.Life[1];
				cnt += 120;
				smCharInfo.wPlayClass[1] = cnt;
			}
		}


		if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_NPC_MORIF && smCharInfo.Level == 60)
		{

			cnt = ((smCharInfo.Life[1] - smCharInfo.Life[0]) * 700) / smCharInfo.Life[1];
			cnt += 300;
			smCharInfo.wPlayClass[1] = cnt;
		}

		if (smCharInfo.Life[0] != DispLifeBar)
		{
			if (DispLifeBar < smCharInfo.Life[0]) DispLifeBar++;
			else DispLifeBar--;
		}

		if (MotionInfo->State == CHRMOTION_STATE_WARP)
		{
			if (FrameCounter > 10 && smCharInfo.dwCharSoundCode == snCHAR_SOUND_WOLVERLIN)
			{
				if (sAddColorEffect[SMC_A] > -256) sAddColorEffect[SMC_A] -= 8;
				if (sAddColorEffect[SMC_R] > 0) sAddColorEffect[SMC_R] -= 8;
				if (sAddColorEffect[SMC_G] > 0) sAddColorEffect[SMC_G] -= 8;
				if (sAddColorEffect[SMC_B] > 0) sAddColorEffect[SMC_B] -= 8;
				DisplayAlpha = -16;
			}
		}


		if (dwWeaponEffectTime)
		{
			if (dwWeaponEffectTime < dwPlayTime)
			{
				dwWeaponEffectTime = 0;
				WeaponEffect = 0;
			}
		}

		if (PlayVanish > 0) PlayVanish--;
		if (PlayInvincible > 0)	PlayInvincible--;


		if (smCharInfo.ClassClan && ClanInfoNum < 0 && dwClanInfoTime && (dwClanInfoTime + 60 * 1000) < dwPlayTime)
		{

			ClanInfoNum = ReadClanInfo(smCharInfo.ClassClan);
			dwClanInfoTime = dwPlayTime;
		}
		break;

	case 101:

		frame += 80;
		compFrame = frame / 160;

		if (compFrame >= MotionInfo->EndFrame)
		{
			SetMotionFromCode(CHRMOTION_STATE_STAND);



		}



		if (TalkFrame)
		{
			if (TalkFrame >= lpTalkMotionInfo->EndFrame * 160)
				TalkFrame = 0;
			else
				TalkFrame += 80;
		}

		break;

	}

	if (ShootingFlag)
	{

		ShootingMain();
	}

	if (DisplayAlpha < 0)
	{
		DisplayAlpha += 4;
		if (DisplayAlpha > 0) DisplayAlpha = 0;
	}
	if (DisplayAlpha > 0)
	{
		DisplayAlpha -= 4;
		if (DisplayAlpha < 0) DisplayAlpha = 0;
	}


	Counter++;
	FrameCounter++;

	return TRUE;
}


int smCHAR::StartHandEffect(int Mode)
{
	POINT3D angle;
	POINT3D posi;
	smMATRIX *mWorld;
	int x, y, z;

	if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_FIGON)
	{

		memcpy(&angle, &Angle, sizeof(POINT3D));
		angle.y = (-angle.y + ANGLE_180)&ANGCLIP;

		AnimObjectTree(HvLeftHand.ObjBip, frame, angle.x, angle.y, angle.z);
		mWorld = &HvLeftHand.ObjBip->mWorld;
		x = pX + mWorld->_41;
		z = pZ + mWorld->_42;
		y = pY + mWorld->_43;
		StartEffectMonster(x, y, z, MONSTER_PIGON_POWER1);


		AnimObjectTree(HvRightHand.ObjBip, frame, angle.x, angle.y, angle.z);
		mWorld = &HvRightHand.ObjBip->mWorld;
		x = pX + mWorld->_41;
		z = pZ + mWorld->_42;
		y = pY + mWorld->_43;
		StartEffectMonster(x, y, z, MONSTER_PIGON_POWER1);





	}
	if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_SEN)
	{
		if (MotionInfo->State != CHRMOTION_STATE_DEAD)
		{
			memcpy(&angle, &Angle, sizeof(POINT3D));
			angle.y = (-angle.y + ANGLE_180)&ANGCLIP;

			AnimObjectTree(HvLeftHand.ObjBip, frame, angle.x, angle.y, angle.z);
			mWorld = &HvLeftHand.ObjBip->mWorld;
			x = pX + mWorld->_41;
			z = pZ + mWorld->_42;
			y = pY + mWorld->_43;

			posi.x = x;
			posi.y = y;
			posi.z = z;
			sinEffect_Sen(&posi);


		}
	}

	if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_MUTANTTREE)
	{
		if (MotionInfo->State != CHRMOTION_STATE_DEAD)
		{
			memcpy(&angle, &Angle, sizeof(POINT3D));
			angle.y = (-angle.y + ANGLE_180)&ANGCLIP;

			AnimObjectTree(HvLeftHand.ObjBip, frame, angle.x, angle.y, angle.z);
			mWorld = &HvLeftHand.ObjBip->mWorld;
			x = pX + mWorld->_41;
			z = pZ + mWorld->_42;
			y = pY + mWorld->_43;

			posi.x = x;
			posi.y = y + 5 * fONE;
			posi.z = z;
			sinEffect_MutentTree_Smoke(&posi);
		}
	}

	if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_RATOO)
	{
		if (MotionInfo->State != CHRMOTION_STATE_DEAD)
		{
			sinEffect_Ratoo_Aura2(this);
		}
	}


	return TRUE;

}


int smCHAR::VirtualDraw()
{

	POINT	sPos;
	POINT3D CameraPosi, CameraAngle;
	int		He;


	if (!DisplayFlag || !MotionInfo) return FALSE;


	if (ActionPattern == 99)
	{
		if (LastPlayDataType)
		{

			if ((dwLastTransTime + DISPLAY_TRANS_TIME_OVER_FAR) < dwPlayTime)
			{
				dwDispAppSkill = 0;
				return TRUE;
			}
		}
		else
		{

			if ((dwLastTransTime + DISPLAY_TRANS_TIME_OVER) < dwPlayTime)
			{
				dwDispAppSkill = 0;
				return TRUE;
			}
		}
	}
	CameraPosi.x = smCHAR_CameraX;
	CameraPosi.y = smCHAR_CameraY;
	CameraPosi.z = smCHAR_CameraZ;

	CameraAngle.x = smCHAR_CameraAngX;
	CameraAngle.y = smCHAR_CameraAngY;
	CameraAngle.z = smCHAR_CameraAngZ;

	He = PatHeight;
	if (He < 44 * fONE) He = 44 * fONE;

	smRender.SetCameraPosi(CameraPosi.x, CameraPosi.y, CameraPosi.z, CameraAngle.x, CameraAngle.y, CameraAngle.z);
	RendPoint.z = smRender.GetRect2D(pX, pY + (He >> 1), pZ, 44 * fONE, He, &RendRect2D, &sPos);
	RendPoint.x = sPos.x;
	RendPoint.y = sPos.y;

	if (RendPoint.z > 0 && sPos.x > 0 && sPos.x < WinSizeX && sPos.y>0 && sPos.y < WinSizeY)
	{
		RendSucess = TRUE;
		return TRUE;
	}

	return FALSE;
}

int smCHAR::Draw()
{
	POINT3D CameraPosi, CameraAngle;
	POINT3D angle;
	smPAT3D *pat = nullptr;
	POINT sPos;
	POINT3D sPos3;
	int He;

	int dx, dy, dz, dDist;
	_MODELGROUP *lpModelGroup;

	int BlinkFlag = 0;
	smMATRIX Mat;
	int BlinkLevel;
	int BlinkScale;


	RendSucess = 0;
	FlagShow = 0;

	if (!DisplayFlag || !MotionInfo) return FALSE;


	if (lpDinaPattern->UseCount <= 0)
	{
		Close();
		if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR) AddChatBuff("Remove the model error");
		return FALSE;
	}



	if (ActionPattern == 99)
	{
		if (LastPlayDataType)
		{

			if ((dwLastTransTime + DISPLAY_TRANS_TIME_OVER_FAR) < dwPlayTime)
			{
				dwDispAppSkill = 0;
				return TRUE;
			}
		}
		else
		{

			if ((dwLastTransTime + DISPLAY_TRANS_TIME_OVER) < dwPlayTime)
			{
				dwDispAppSkill = 0;
				return TRUE;
			}
		}
	}



	FlagShow = TRUE;

	dx = (smCHAR_CameraX - pX) >> FLOATNS;
	dy = (smCHAR_CameraY - pY) >> FLOATNS;
	dz = (smCHAR_CameraZ - pZ) >> FLOATNS;

	dDist = dx * dx + dy * dy + dz * dz;

	CameraPosi.x = smCHAR_CameraX;
	CameraPosi.y = smCHAR_CameraY;
	CameraPosi.z = smCHAR_CameraZ;

	CameraAngle.x = smCHAR_CameraAngX;
	CameraAngle.y = smCHAR_CameraAngY;
	CameraAngle.z = smCHAR_CameraAngZ;



	memcpy(&angle, &Angle, sizeof(POINT3D));
	angle.y = (-angle.y + ANGLE_180)&ANGCLIP;

	if (ActionGameMode)
	{
		if (angle.y > ANGLE_180)
			angle.y = ANGLE_270;
		else
			angle.y = ANGLE_90;
	}

	Posi.x = pX;
	Posi.y = pY;
	Posi.z = pZ;


	Pattern->SetPosi(&Posi, &angle);



	if (Pattern->TmParent && Pattern->TmParent->MaxFrame > (int)frame)
		Pattern->Frame = frame;
	else
		Pattern->Frame = 80;

	char *ModelNameList[4];

	int	cr, cg, cb, ca, cnt, sR, sG, sB, sA;
	int nl = 0;

	cr = smRender.Color_R;
	cg = smRender.Color_G;
	cb = smRender.Color_B;
	ca = smRender.Color_A;



	sR = sAddColorEffect[SMC_R];
	sG = sAddColorEffect[SMC_G];
	sB = sAddColorEffect[SMC_B];
	sA = sAddColorEffect[SMC_A];

	if (smCharInfo.wPlayClass[0] == MONSTER_CLASS_BOSS)
	{

		cnt = Counter & 0x1F;
		if ((Counter & 0x20) == 0)
		{
			cnt = 0x1F - cnt;
		}
		sR = (sR*cnt) >> 5;
		sG = (sG*cnt) >> 5;
		sB = (sB*cnt) >> 5;
	}


	smRender.Color_R = cr + AttackAnger + sR;
	smRender.Color_G = cg - (AttackAnger >> 1) + sG + abs(DispPoison);
	smRender.Color_B = cb + abs(AttackIce) + sB;
	smRender.Color_A = ca + DisplayAlpha - (abs(AttackIce) >> 1) + sA;

	if (PlayCurseQuest)
	{
		smRender.Color_R += 100;
		smRender.Color_B += 100;
	}
	if (PlayDistortion && MotionInfo->State != CHRMOTION_STATE_DEAD)
	{


		smRender.DistortionMesh = TRUE;
		smRender.Color_R += 80;
		smRender.Color_G += 80;
	}

	if (smCharInfo.wPlayClass[1])
	{

		smRender.ObjectVertexScale = smCharInfo.wPlayClass[1];
	}

	if (DarkLevel > 0 && OnStageField >= 0 && StageField[OnStageField]->State == FIELD_STATE_VILLAGE)
	{

		nl = DarkLevel >> 1;
		smRender.Color_R += nl;
		smRender.Color_G += nl;
		smRender.Color_B += nl;

		if (smRender.nRendLight > 0 && smRender.smRendLight[0].Range == DarkLightRange)
		{
			smRender.smRendLight[0].Range = 0;
			nl = 1;
		}
		else
			nl = 0;
	}


	if (MotionInfo->State == CHRMOTION_STATE_DEAD)
	{
		if (FrameCounter > 400)
		{
			cnt = 100;
			smRender.Color_R -= cnt;
			smRender.Color_G -= cnt;
			smRender.Color_B -= cnt;
		}
		else
		{
			if (FrameCounter > 200)
			{
				cnt = (FrameCounter - 200) >> 1;
				smRender.Color_R -= cnt;
				smRender.Color_G -= cnt;
				smRender.Color_B -= cnt;

			}
		}

		if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_FIGON || smCharInfo.dwCharSoundCode == snCHAR_SOUND_STYGIANLORD ||
			smCharInfo.dwCharSoundCode == snCHAR_SOUND_GUARDIAN_SAINT || smCharInfo.dwCharSoundCode == snCHAR_SOUND_S_F_ELEMENTAL ||
			smCharInfo.dwCharSoundCode == snCHAR_SOUND_CHAOSCARA)
		{

			smRender.Color_A = ca - (FrameCounter << 1);
			if (smRender.Color_A < -400) goto rendSkip;
			DisplayAlpha = 100;
		}
	}



	lpModelGroup = &smMotionInfo->DefaultModel;

	if (dDist < VIEW_HIGH_DIST && smMotionInfo->HighModel.ModelNameCnt)
		lpModelGroup = &smMotionInfo->HighModel;

	if (dDist > VIEW_MID_DIST && smMotionInfo->LowModel.ModelNameCnt)
		lpModelGroup = &smMotionInfo->LowModel;



	if (TalkFrame)
	{
		if (TalkPattern->MaxFrame > (int)TalkFrame)
			TalkPattern->Frame = TalkFrame;
		else
			TalkFrame = 0;
	}



	if (PatDispMode&DISP_MODE_PATMAIN)
	{

		if (Pattern->TmParent) Pattern->TmParent->TmLastFrame = -1;
		else Pattern->TmLastFrame = -1;

		if (lpModelGroup->ModelNameCnt)
		{
			ModelNameList[0] = lpModelGroup->szModelName[0];
			ModelNameList[1] = lpModelGroup->szModelName[1];
			ModelNameList[2] = lpModelGroup->szModelName[2];
			ModelNameList[3] = lpModelGroup->szModelName[3];


			if (TalkFrame && lpTalkMotionInfo->State)
			{
				RendSucess += Pattern->ChoiseRenderD3D(&CameraPosi, &CameraAngle, ModelNameList, lpModelGroup->ModelNameCnt, TalkPattern, &FrameInfo);
			}
			else
			{
				RendSucess += Pattern->ChoiseRenderD3D(&CameraPosi, &CameraAngle, ModelNameList, lpModelGroup->ModelNameCnt, &FrameInfo);
			}
		}

		else
		{
			if (TalkFrame && lpTalkMotionInfo->State)
			{
				RendSucess += Pattern->RenderD3D(&CameraPosi, &CameraAngle, TalkPattern, &FrameInfo);
			}
			else
			{
				RendSucess += Pattern->RenderD3D(&CameraPosi, &CameraAngle, &FrameInfo);
			}
		}

	}



	if (lpDinaPattern2 && Pattern2 && PatDispMode&DISP_MODE_PATSUB)
	{
		lpModelGroup = &lpDinaPattern2->lpModelInfo->DefaultModel;

		if (dDist < VIEW_HIGH_DIST && lpDinaPattern2->lpModelInfo->HighModel.ModelNameCnt)
			lpModelGroup = &lpDinaPattern2->lpModelInfo->HighModel;

		if (dDist > VIEW_MID_DIST && lpDinaPattern2->lpModelInfo->LowModel.ModelNameCnt)
			lpModelGroup = &lpDinaPattern2->lpModelInfo->LowModel;


		Pattern2->SetPosi(&Posi, &angle);
		if (Pattern2->TmParent && Pattern2->TmParent->MaxFrame > (int)frame)
			Pattern2->Frame = frame;


		if (Pattern2->TmParent)
			Pattern2->TmParent->TmLastFrame = -1;
		else
			Pattern2->TmLastFrame = -1;

		if (lpModelGroup->ModelNameCnt)
		{
			ModelNameList[0] = lpModelGroup->szModelName[0];
			ModelNameList[1] = lpModelGroup->szModelName[1];
			ModelNameList[2] = lpModelGroup->szModelName[2];
			ModelNameList[3] = lpModelGroup->szModelName[3];


			if (TalkFrame && lpTalkMotionInfo->State)
				RendSucess += Pattern2->ChoiseRenderD3D(&CameraPosi, &CameraAngle, ModelNameList, lpModelGroup->ModelNameCnt, TalkPattern, &FrameInfo);
			else
				RendSucess += Pattern2->ChoiseRenderD3D(&CameraPosi, &CameraAngle, ModelNameList, lpModelGroup->ModelNameCnt, &FrameInfo);

		}


		else
		{
			if (TalkFrame && lpTalkMotionInfo->State)
				RendSucess += Pattern2->RenderD3D(&CameraPosi, &CameraAngle, TalkPattern, &FrameInfo);
			else
				RendSucess += Pattern2->RenderD3D(&CameraPosi, &CameraAngle, &FrameInfo);
		}

	}


	smRender.ObjectVertexScale = 0;

	if (RendSucess)
	{
		int We = 44 * fONE;
		He = PatHeight;

		if (smCharInfo.wPlayClass[1])
		{

			He = (He*smCharInfo.wPlayClass[1]) >> FLOATNS;
		}

		if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_KELVEZU)
		{
			We = He * 2;
		}

		if (He < 44 * fONE)
		{
			He = 44 * fONE;
		}

		smRender.SetCameraPosi(CameraPosi.x, CameraPosi.y, CameraPosi.z, CameraAngle.x, CameraAngle.y, CameraAngle.z);

		RendPoint.z = smRender.GetRect2D(pX, pY + (He >> 1), pZ, We, He, &RendRect2D, &sPos);
		RendPoint.x = sPos.x;
		RendPoint.y = sPos.y;
	}

	if (!Pattern->TmParent || !DisplayTools)
	{
		smRender.Color_R = cr;
		smRender.Color_G = cg;
		smRender.Color_B = cb;
		if (nl)
			smRender.smRendLight[0].Range = DarkLightRange;
		return TRUE;
	}



	if (MotionInfo->State == CHRMOTION_STATE_ATTACK && dwPlayTime & 0x20)
		BlinkFlag = TRUE;

	if (BlinkFlag && !ShootingMode)
	{
		smRender.Color_R += 80;
		smRender.Color_G += 80;
		smRender.Color_B += 80;
	}

	Rend_HvLeftHand = TRUE;
	Rend_HvRightHand = TRUE;

	if (smCharInfo.State == smCHAR_STATE_USER || PkMode_CharState == smCHAR_STATE_USER)
	{
		if (dwItemSetting == 0 || (OnStageField >= 0 && StageField[OnStageField]->State != FIELD_STATE_VILLAGE && MotionInfo->State != CHRMOTION_STATE_YAHOO))
		{
			if (HvLeftHand.PatTool)
			{
				pat = HvLeftHand.PatTool;

				if ((HvLeftHand.dwItemCode&sinITEM_MASK2) == sinDS1)
				{
					if ((dwDispAppSkill&SKILL_APPMASK_SPARK_SHIELD) && PatSparkShield && smCharInfo.JOB_CODE == JOBCODE_MECHANICIAN)
					{
						if (MotionInfo->State == CHRMOTION_STATE_SKILL && (AttackSkil & 0xFF) == SKILL_PLAY_SPARK_SHIELD && MotionEvent == 0)
							pat = HvLeftHand.PatTool;
						else
							pat = PatSparkShield;
					}
					if ((dwDispAppSkill&SKILL_APPMASK_SPARK_SHIELD) && PatDivineShield && smCharInfo.JOB_CODE == JOBCODE_KNIGHT)
					{
						if (MotionInfo->State == CHRMOTION_STATE_SKILL && (AttackSkil & 0xFF) == SKILL_PLAY_DIVINE_INHALATION && MotionEvent == 0)
							pat = HvLeftHand.PatTool;
						else
							pat = PatDivineShield;
					}
					if ((dwDispAppSkill&SKILL_APPMASK_GODLY_SHIELD) && PatGodlyShield && smCharInfo.JOB_CODE == JOBCODE_KNIGHT)
					{
						if (MotionInfo->State == CHRMOTION_STATE_SKILL && (AttackSkil & 0xFF) == SKILL_PLAY_GODLY_SHIELD && MotionEvent == 0)
							pat = HvLeftHand.PatTool;
						else
							pat = PatGodlyShield;
					}
				}

				if (MotionInfo->State == CHRMOTION_STATE_SKILL &&
					((AttackSkil & 0xFF) == SKILL_PLAY_SHIELD_STRIKE || (AttackSkil & 0xFF) == SKILL_PLAY_SOUL_SUCKER) && ShieldObjBip)
				{

					pat->LinkParentObject(AnimPattern, ShieldObjBip);

					cr = smRender.Color_R;
					cg = smRender.Color_G;
					cb = smRender.Color_B;

					smRender.Color_R += 100;
					smRender.Color_G += 100;
					smRender.Color_B += 80;

				}
				else
				{
					pat->LinkParentObject(AnimPattern, HvLeftHand.ObjBip);
				}

				pat->SetPosi(&Posi, &angle);
				pat->Frame = frame;


				memcpy(&HvLeftHand_Matrix, &HvLeftHand.ObjBip->mWorld, sizeof(smMATRIX));

				if (!HvLeftHand.ColorBlink || !HvLeftHand.sColors[SMC_A])
				{

					BlinkLevel = SetRenderBlinkColor(&HvLeftHand);


					if (HvLeftHand.BlinkScale && BlinkLevel)
					{
						smIdentityMatrix(Mat);
						if (HvLeftHand.BlinkScale < 0)
							BlinkScale = -HvLeftHand.BlinkScale;
						else
							BlinkScale = (BlinkLevel*HvLeftHand.BlinkScale) >> FLOATNS;
						Mat._11 = BlinkScale;
						Mat._22 = BlinkScale;
						Mat._33 = BlinkScale;
						pat->Frame = -1;
						memcpy(&pat->obj3d[0]->mWorld, &HvLeftHand.ObjBip->mWorld, sizeof(smMATRIX));
						smMatrixMult(pat->obj3d[0]->mWorld, Mat, pat->obj3d[0]->mWorld);
					}

					pat->RenderD3D(&CameraPosi, &CameraAngle);
					RestoreRenderBlinkColor();


					if (MotionInfo->State == CHRMOTION_STATE_SKILL && (AttackSkil & 0xFF) == SKILL_PLAY_SHIELD_STRIKE && ShieldObjBip)
					{


						smRender.Color_R = cr;
						smRender.Color_G = cg;
						smRender.Color_B = cb;

						sPos3.x = pat->obj3d[0]->mWorld._41 + pX;
						sPos3.z = pat->obj3d[0]->mWorld._42 + pZ;
						sPos3.y = pat->obj3d[0]->mWorld._43 + pY;
						sinEffect_Shield_Strike(&sPos3);
					}
				}
				else
					Rend_HvLeftHand = FALSE;

				pat->LinkParentObject(0, 0);
				pat->TmLastFrame = -1;
			}



			if (HvRightHand.PatTool && !HideWeapon)
			{
				if ((dwActionItemCode&sinITEM_MASK2) == sinWT1 && ShootingFlag)
				{

				}
				else
				{

					pat = HvRightHand.PatTool;
					pat->LinkParentObject(AnimPattern, HvRightHand.ObjBip);
					pat->SetPosi(&Posi, &angle);
					pat->Frame = frame;


					memcpy(&HvRightHand_Matrix, &HvRightHand.ObjBip->mWorld, sizeof(smMATRIX));

					if (!HvRightHand.ColorBlink || !HvRightHand.sColors[SMC_A])
					{

						BlinkLevel = SetRenderBlinkColor(&HvRightHand);


						if (HvRightHand.BlinkScale && BlinkLevel)
						{
							smIdentityMatrix(Mat);
							if (HvRightHand.BlinkScale < 0)
								BlinkScale = -HvRightHand.BlinkScale;
							else
								BlinkScale = (BlinkLevel*HvRightHand.BlinkScale) >> FLOATNS;

							Mat._11 = BlinkScale;
							Mat._22 = BlinkScale;
							Mat._33 = BlinkScale;
							pat->Frame = -1;
							memcpy(&pat->obj3d[0]->mWorld, &HvRightHand.ObjBip->mWorld, sizeof(smMATRIX));
							smMatrixMult(pat->obj3d[0]->mWorld, Mat, pat->obj3d[0]->mWorld);
						}

						pat->RenderD3D(&CameraPosi, &CameraAngle);
						RestoreRenderBlinkColor();
					}
					else
						Rend_HvRightHand = FALSE;

					pat->LinkParentObject(0, 0);
					pat->TmLastFrame = -1;
				}
			}
		}
		else
		{
			if (dwActionItemCode)
			{

				BlinkScale = 0;


				if (HvLeftHand.dwItemCode == dwActionItemCode)
				{
					pat = HvLeftHand.PatTool;
					if (!HvLeftHand.ColorBlink || !HvLeftHand.sColors[SMC_A])
					{

						BlinkLevel = SetRenderBlinkColor(&HvLeftHand);

						if (HvLeftHand.BlinkScale && BlinkLevel)
						{
							if (HvLeftHand.BlinkScale < 0)
								BlinkScale = -HvLeftHand.BlinkScale;
							else
								BlinkScale = (BlinkLevel*HvLeftHand.BlinkScale) >> FLOATNS;
							memcpy(&pat->obj3d[0]->mWorld, &HvLeftHand.ObjBip->mWorld, sizeof(smMATRIX));
						}
					}
					else
						Rend_HvLeftHand = FALSE;
				}
				if (HvRightHand.dwItemCode == dwActionItemCode)
				{
					pat = HvRightHand.PatTool;
					if (!HvRightHand.ColorBlink || !HvRightHand.sColors[SMC_A])
					{

						BlinkLevel = SetRenderBlinkColor(&HvRightHand);

						if (HvRightHand.BlinkScale && BlinkLevel)
						{
							if (HvRightHand.BlinkScale < 0)
								BlinkScale = -HvRightHand.BlinkScale;
							else
								BlinkScale = (BlinkLevel*HvRightHand.BlinkScale) >> FLOATNS;

							memcpy(&pat->obj3d[0]->mWorld, &HvRightHand.ObjBip->mWorld, sizeof(smMATRIX));
						}
					}
					else
						Rend_HvRightHand = FALSE;
				}

				pat->LinkParentObject(AnimPattern, BackObjBip[dwItemSetting - 1]);
				pat->SetPosi(&Posi, &angle);
				pat->Frame = frame;


				if (BlinkScale)
				{
					smIdentityMatrix(Mat);
					Mat._11 = BlinkScale;
					Mat._22 = BlinkScale;
					Mat._33 = BlinkScale;
					pat->Frame = -1;
					smMatrixMult(pat->obj3d[0]->mWorld, Mat, pat->obj3d[0]->mWorld);
				}


				if (HvLeftHand.dwItemCode == dwActionItemCode)
				{
					memcpy(&HvLeftHand_Matrix, &BackObjBip[dwItemSetting - 1]->mWorld, sizeof(smMATRIX));
					if (Rend_HvLeftHand)
					{
						pat->RenderD3D(&CameraPosi, &CameraAngle);
						RestoreRenderBlinkColor();
					}
				}
				else
				{
					memcpy(&HvRightHand_Matrix, &BackObjBip[dwItemSetting - 1]->mWorld, sizeof(smMATRIX));
					if (Rend_HvRightHand)
					{
						pat->RenderD3D(&CameraPosi, &CameraAngle);
						RestoreRenderBlinkColor();
					}
				}

				pat->LinkParentObject(0, 0);
				pat->TmLastFrame = -1;
			}

			if (HvLeftHand.PatTool &&  dwActionItemCode != HvLeftHand.dwItemCode)
			{
				pat = HvLeftHand.PatTool;
				pat->LinkParentObject(AnimPattern, HvLeftHand.ObjBip);
				pat->SetPosi(&Posi, &angle);
				pat->Frame = frame;

				memcpy(&HvLeftHand_Matrix, &HvLeftHand.ObjBip->mWorld, sizeof(smMATRIX));

				if (!HvLeftHand.ColorBlink || !HvLeftHand.sColors[SMC_A])
				{

					BlinkLevel = SetRenderBlinkColor(&HvLeftHand);


					if (HvLeftHand.BlinkScale && BlinkLevel)
					{
						smIdentityMatrix(Mat);
						if (HvLeftHand.BlinkScale < 0)
							BlinkScale = -HvLeftHand.BlinkScale;
						else
							BlinkScale = (BlinkLevel*HvLeftHand.BlinkScale) >> FLOATNS;

						Mat._11 = BlinkScale;
						Mat._22 = BlinkScale;
						Mat._33 = BlinkScale;
						pat->Frame = -1;
						memcpy(&pat->obj3d[0]->mWorld, &HvLeftHand.ObjBip->mWorld, sizeof(smMATRIX));
						smMatrixMult(pat->obj3d[0]->mWorld, Mat, pat->obj3d[0]->mWorld);
					}
					pat->RenderD3D(&CameraPosi, &CameraAngle);
					RestoreRenderBlinkColor();
				}
				else
					Rend_HvLeftHand = FALSE;

				pat->LinkParentObject(0, 0);
				pat->TmLastFrame = -1;
			}

		}


		if ((MotionInfo->State == CHRMOTION_STATE_ATTACK || MotionInfo->State == CHRMOTION_STATE_SKILL)
			&& (dwActionItemCode&sinITEM_MASK2) == sinWS1
			&& !HvRightHand.PatTool && !ShootingFlag && !HideWeapon)
		{
			pat = PatArrow;
			pat->LinkParentObject(AnimPattern, HvRightHand.ObjBip);
			pat->SetPosi(&Posi, &angle);
			pat->Frame = frame;
			pat->RenderD3D(&CameraPosi, &CameraAngle);
			pat->LinkParentObject(0, 0);
			pat->TmLastFrame = -1;
		}
	}















	if (ShootingFlag)
	{
		memcpy(&angle, &ShootingAngle, sizeof(POINT3D));
		angle.y = (-angle.y + ANGLE_180)&ANGCLIP;

		if ((dwActionItemCode&sinITEM_MASK2) == sinWS1)
			pat = PatArrow;
		else
			pat = HvRightHand.PatTool;
		angle.x = (angle.x - ANGLE_90)&ANGCLIP;






		pat->SetPosi(&ShootingPosi, &angle);
		pat->Frame = 0;
		pat->RenderD3D(&CameraPosi, &CameraAngle);
	}

rendSkip:

	smRender.Color_R = cr;
	smRender.Color_G = cg;
	smRender.Color_B = cb;
	smRender.Color_A = ca;
	if (nl)
		smRender.smRendLight[0].Range = DarkLightRange;
	smRender.DistortionMesh = FALSE;

	return TRUE;
}


int smCHAR::DrawShadow()
{
	int a;
	POINT3D	pos;
	POINT3D angle;
	POINT3D CameraPosi, CameraAngle;

	if (PatSizeLevel < 0 || !MotionInfo) return FALSE;

	CameraPosi.x = smCHAR_CameraX;
	CameraPosi.y = smCHAR_CameraY;
	CameraPosi.z = smCHAR_CameraZ;

	CameraAngle.x = smCHAR_CameraAngX;
	CameraAngle.y = smCHAR_CameraAngY;
	CameraAngle.z = smCHAR_CameraAngZ;

	if (Pattern && PatShadow[PatSizeLevel] && MotionInfo->State != CHRMOTION_STATE_RESTART &&
		RendSucess && RendPoint.z < 12 * 64 * fONE && PlayVanish <= 0)
	{

		pos.x = pX;
		pos.y = PHeight + (1 * fONE);
		pos.z = pZ;


		angle.x = Angle.x;
		angle.y = (-Angle.y + ANGLE_180)&ANGCLIP;
		angle.z = Angle.z;

		a = smRender.Color_A;

		if (MotionInfo->State == CHRMOTION_STATE_DEAD)
			smRender.Color_A = a - (FrameCounter << 1);

		smRender.Color_A -= 160;

		if (smRender.Color_A > -240)
		{
			renderDevice.SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
			smRender.SetMaterialGroup(smMaterialGroup);
			PatShadow[PatSizeLevel]->SetPosi(&pos, &angle);
			PatShadow[PatSizeLevel]->RenderD3D(&CameraPosi, &CameraAngle);
			renderDevice.SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
		}

		smRender.Color_A = a;

	}


	smPAT3D *pat;
	smMATRIX Mat;
	int BlinkLevel, BlinkScale;



	if (RendSucess && !HideWeapon)
	{
		if (!Rend_HvRightHand)
		{
			if (HvRightHand.ColorBlink)
			{
				pat = HvRightHand.PatTool;
				pat->SetPosi(&Posi, &angle);
				pat->Frame = -1;

				BlinkLevel = SetRenderBlinkColor(&HvRightHand);
				memcpy(&pat->obj3d[0]->mWorld, &HvRightHand_Matrix, sizeof(smMATRIX));

				if (HvRightHand.BlinkScale && BlinkLevel)
				{
					smIdentityMatrix(Mat);

					if (HvRightHand.BlinkScale < 0)
						BlinkScale = -HvRightHand.BlinkScale;
					else
						BlinkScale = (BlinkLevel*HvRightHand.BlinkScale) >> FLOATNS;

					Mat._11 = BlinkScale;
					Mat._22 = BlinkScale;
					Mat._33 = BlinkScale;
					smMatrixMult(pat->obj3d[0]->mWorld, Mat, pat->obj3d[0]->mWorld);
				}

				pat->RenderD3D(&CameraPosi, &CameraAngle);
				RestoreRenderBlinkColor();
			}
		}
		if (!Rend_HvLeftHand)
		{
			if (HvLeftHand.ColorBlink)
			{
				pat = HvLeftHand.PatTool;
				pat->SetPosi(&Posi, &angle);
				pat->Frame = -1;

				BlinkLevel = SetRenderBlinkColor(&HvLeftHand);
				memcpy(&pat->obj3d[0]->mWorld, &HvLeftHand_Matrix, sizeof(smMATRIX));

				if (HvLeftHand.BlinkScale && BlinkLevel)
				{
					smIdentityMatrix(Mat);

					if (HvLeftHand.BlinkScale < 0)
						BlinkScale = -HvLeftHand.BlinkScale;
					else
						BlinkScale = (BlinkLevel*HvLeftHand.BlinkScale) >> FLOATNS;

					Mat._11 = BlinkScale;
					Mat._22 = BlinkScale;
					Mat._33 = BlinkScale;
					smMatrixMult(pat->obj3d[0]->mWorld, Mat, pat->obj3d[0]->mWorld);
				}
				pat->RenderD3D(&CameraPosi, &CameraAngle);
				RestoreRenderBlinkColor();
			}
		}


	}

	int r, g, b, c, d;
	int cnt;







	pat = 0;

	if ((dwDispAppSkill&SKILL_APPMASK_EXTREME_SHIELD) &&
		(MotionInfo->State != CHRMOTION_STATE_SKILL || (AttackSkil & 0xFF) != SKILL_PLAY_EXTREME_SHIELD))
	{
		pat = PatEffectShield;
	}

	if (pat)
	{

		if (RendSucess && HvLeftHand.PatTool &&
			(HvLeftHand.dwItemCode&sinITEM_MASK2) == sinDS1)
		{

			memcpy(&angle, &Angle, sizeof(POINT3D));
			angle.y = (-angle.y + ANGLE_180)&ANGCLIP;

			Posi.x = pX;
			Posi.y = pY;
			Posi.z = pZ;
			a = smRender.Color_A;
			r = smRender.Color_R;
			g = smRender.Color_G;
			b = smRender.Color_B;
			smRender.Color_B = +128;




			pat->SetPosi(&Posi, &angle);

			d = dwPlayTime >> 4;
			c = d & 0x3F;
			if ((d & 0x40))
			{
				c = 0x40 - c;
			}

			c += (int)(fONE*0.9f) + c;

			smIdentityMatrix(Mat);
			if (PatEffectShield == pat)
			{
				Mat._11 = c;
				Mat._22 = c;
				Mat._33 = c;
			}

			for (cnt = 0; cnt < pat->nObj3d; cnt++)
			{
				memcpy(&pat->obj3d[cnt]->mWorld, &HvLeftHand_Matrix, sizeof(smMATRIX));
				smMatrixMult(pat->obj3d[cnt]->mWorld, Mat, pat->obj3d[cnt]->mWorld);
			}

			smRender.Color_R = 0;
			smRender.Color_G = 0;
			smRender.Color_B = 0;
			smRender.Color_A = 0;

			pat->Frame = -1;
			pat->RenderD3D(&CameraPosi, &CameraAngle);

			smRender.Color_A = a;
			smRender.Color_R = r;
			smRender.Color_G = g;
			smRender.Color_B = b;

		}
	}


	int s, sz, maxSize;


	if ((AttackSkil & 0xFF) == SKILL_PLAY_EXPANSION && RendSucess && HvRightHand.PatTool && MotionInfo->State == CHRMOTION_STATE_ATTACK)
	{

		sz = Expansion_Size[(AttackSkil >> 8) - 1];

		memcpy(&angle, &Angle, sizeof(POINT3D));
		angle.y = (-angle.y + ANGLE_180)&ANGCLIP;

		Posi.x = pX;
		Posi.y = pY;
		Posi.z = pZ;
		a = smRender.Color_A;
		r = smRender.Color_R;
		smRender.Color_A = -96 - (FrameCounter << 1);
		smRender.Color_R = +128;
		if (smRender.Color_A < -192) smRender.Color_A = -192;

		pat = HvRightHand.PatTool;
		pat->SetPosi(&Posi, &angle);
		pat->Frame = -1;

		smIdentityMatrix(Mat);



		s = FrameCounter << 3;
		maxSize = (sz*fONE) / 100;
		if (s > maxSize) s = maxSize;
		s += (fONE / 4);

		Mat._11 = fONE + s;
		Mat._22 = fONE + s;
		Mat._33 = fONE + s;

		memcpy(&pat->obj3d[0]->mWorld, &HvRightHand_Matrix, sizeof(smMATRIX));
		smMatrixMult(pat->obj3d[0]->mWorld, Mat, pat->obj3d[0]->mWorld);
		pat->RenderD3D(&CameraPosi, &CameraAngle);

		smRender.Color_A = a;
		smRender.Color_R = r;
	}


	if (Clan_CastleMasterFlag && smCharInfo.ClassClan && PatCrown && RendSucess && RendPoint.z < 12 * 64 * fONE && PlayVanish <= 0)
	{

		GetMoveLocation(0, 0, 0 * fONE, 0, Angle.y, 0);

		pos.x = pX + GeoResult_X;
		pos.y = pY + PatHeight + 10 * fONE;
		pos.z = pZ + GeoResult_Z;

		cnt = (dwPlayTime >> 2) & 0xFF;
		if ((cnt & 0x80))
		{
			pos.y += (cnt & 0x7F);
		}
		else
		{
			pos.y += 0x80 - (cnt & 0x7F);
		}

		angle.x = 0;
		angle.y = (dwPlayTime >> 2)&ANGCLIP;
		angle.z = 0;




		renderDevice.SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
		smRender.SetMaterialGroup(smMaterialGroup);
		PatCrown->SetPosi(&pos, &angle);
		PatCrown->RenderD3D(&CameraPosi, &CameraAngle);
		renderDevice.SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);

	}



	return TRUE;

}


void smCHAR::SetIceFoot(int TypeNum, DWORD dwPlayTime, int x, int z)
{
	if (smGameStage[OnStageField] == NULL)
		return;
	int loop = 0;
	for (loop = 0; loop < ICE_FOOT_COUNT_MAX; loop++)
	{
		if (m_IceFootInfo[loop].Life == 0)
			break;
	}

	if (loop >= ICE_FOOT_COUNT_MAX)
		return;

	POINT3D FootPos;
	FootPos.x = pX + x;

	FootPos.y = pY + (10 * fONE);
	FootPos.z = pZ + z;

	POINT3D FaceAngle;
	if (smGameStage[OnStageField]->CheckFaceIceFoot(&FootPos, &FaceAngle, 32 * fONE) == 0)
		return;

	m_IceFootInfo[loop].Life = 1;
	m_IceFootInfo[loop].dwPlayTime = dwPlayTime;
	m_IceFootInfo[loop].TypeNum = TypeNum;
	m_IceFootInfo[loop].FootPos.x = FootPos.x;
	m_IceFootInfo[loop].FootPos.y = FootPos.y;
	m_IceFootInfo[loop].FootPos.z = FootPos.z;
	m_IceFootInfo[loop].FootAngle.x = -(FaceAngle.x - ANGLE_180) & ANGCLIP;
	m_IceFootInfo[loop].FootAngle.y = (-Angle.y) & ANGCLIP;
	m_IceFootInfo[loop].FootAngle.z = (FaceAngle.z - ANGLE_180) & ANGCLIP;
}


int smCHAR::DrawIceFoot(void)
{
	if (MotionInfo == NULL || Pattern == NULL || MotionInfo->State == CHRMOTION_STATE_RESTART || RendSucess == 0)
		return FALSE;

	POINT3D CameraPosi, CameraAngle;

	CameraPosi.x = smCHAR_CameraX;
	CameraPosi.y = smCHAR_CameraY;
	CameraPosi.z = smCHAR_CameraZ;

	CameraAngle.x = smCHAR_CameraAngX;
	CameraAngle.y = smCHAR_CameraAngY;
	CameraAngle.z = smCHAR_CameraAngZ;

	int b_r, b_g, b_b, b_a;
	b_r = smRender.Color_R;
	b_g = smRender.Color_G;
	b_b = smRender.Color_B;
	b_a = smRender.Color_A;

	smRender.Color_R = 0;
	smRender.Color_G = 0;
	smRender.Color_B = 0;
	smRender.Color_A = 0;

	smRender.m_dwRenderType = smRENDER_TYPE_ICE;

	smRender.SetMaterialGroup(::smMaterialGroup);
	renderDevice.SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
	for (int loop = 0; loop < ICE_FOOT_COUNT_MAX; loop++)
	{
		if (m_IceFootInfo[loop].Life)
		{
			float Alpha = float(dwPlayTime - m_IceFootInfo[loop].dwPlayTime) * ICE_FOOT_ALPHA_STEP;
			if (Alpha >= 200)
				m_IceFootInfo[loop].Life = 0;
			else
			{
				smRender.Color_A = -int(Alpha);
				PatIceFoot[m_IceFootInfo[loop].TypeNum]->SetPosi(&m_IceFootInfo[loop].FootPos, &m_IceFootInfo[loop].FootAngle);
				PatIceFoot[m_IceFootInfo[loop].TypeNum]->RenderD3D(&CameraPosi, &CameraAngle);
			}
		}
	}
	renderDevice.SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);

	smRender.Color_R = b_r;
	smRender.Color_G = b_g;
	smRender.Color_B = b_b;
	smRender.Color_A = b_a;

	smRender.m_dwRenderType = 0;
	return TRUE;
}

#define STATE_BAR_WIDTH		180
#define STATE_BAR_HEIGHT	18
#define STATE_BAR_SIZE		180


int smCHAR::DrawStateBar(int x, int y)
{
	return TRUE;
}


int smCHAR::DrawStateBar2(int x, int y) {
	return TRUE;
}


int smCHAR::DrawChargingBar(int x, int y, int Charging, int ChargingMax) {
	return TRUE;
}


int smCHAR::DrawMotionBlur() {
	return TRUE;
}


int smCHAR::DrawMotionBlurTool(smCHARTOOL *ChrTool) {
	return TRUE;
}


int smCHAR::SetLoadPattern(char *szName)
{
	Pattern = 0;
	Flag = 1;
	return AddLoaderPattern((smCHAR *)&Head, szName);

}


DWORD smCHAR::GetAttackTrans_XorCode()
{
	return dwObjectSerial ^ lpCurPlayer->smCharInfo.dwObjectSerial ^ (((DWORD)this) >> 8);
}


int smCHAR::ResetAttackTrans()
{

	AttackTrans.code = GetAttackTrans_XorCode();
	return TRUE;
}


int smCHAR::XorAttackTrans()
{
	int cnt, len;
	DWORD dwCode;

	len = (sizeof(TRANS_ATTACKDATA) / sizeof(DWORD));
	DWORD *lpdwBuff = (DWORD *)&AttackTrans;

	dwCode = GetAttackTrans_XorCode();

	lpdwBuff[0] ^= dwCode;
	lpdwBuff[1] ^= dwCode;

	for (cnt = 2; cnt < len; cnt++)
	{
		lpdwBuff[cnt] ^= dwCode;
		dwCode += dwCode;
	}

	return TRUE;
}


int smCHAR::PlayAttack(int EventFlag)
{
	int cnt, len, act;
	int block, ChanceBlock;
	smCHAR *lpChar;
	int	HolyBody_Undead = 0;
	int x, y, z;
	POINT3D	Pos1;
	int temp;
	int Param1, Param2;
	int	bStunCount;


	TRANS_ATTACKDATA	*lpTransAttackData;

	lpTransAttackData = &AttackTrans;

	XorAttackTrans();

	if (!lpTransAttackData->code || (RestartPlayCount > 0 && RestartPlayCount < 1000) ||
		(UseEtherCoreCode && lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_EAT))
	{

		AttackTrans.code = GetAttackTrans_XorCode();
		if (RestartPlayCount) Ptect_IncAttackCount(0);
		return FALSE;
	}

	if (lpTransAttackData->dwDamageChkSum != dm_GetDamgeChkSum_S2V(lpTransAttackData))
	{
		ResetAttackTrans();
		SendSetHackUser3(8580, lpTransAttackData->Power, 0);
		return FALSE;
	}

	Ptect_IncAttackCount(-1);

	if (lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_DEAD && DisplayFlag)
	{
		len = GetDistanceDbl(lpCurPlayer->pX, lpCurPlayer->pZ, pX, pZ);
		cnt = GetDistanceDbl(lpCurPlayer->pX, lpCurPlayer->pZ, lpTransAttackData->x, lpTransAttackData->z);

		if (smCharInfo.State == smCHAR_STATE_USER || PkMode_CharState == smCHAR_STATE_USER)
		{
			len = 0;
			cnt = 0;
		}

		if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_FIGON || smCharInfo.dwCharSoundCode == snCHAR_SOUND_WEB ||
			smCharInfo.dwCharSoundCode == snCHAR_SOUND_SKELETONRANGE || smCharInfo.dwCharSoundCode == snCHAR_SOUND_IMP ||
			smCharInfo.dwCharSoundCode == snCHAR_SOUND_SCORPION ||

			smCharInfo.dwCharSoundCode == snCHAR_SOUND_NAZ ||
			smCharInfo.dwCharSoundCode == snCHAR_SOUND_NAZSENIOR ||
			smCharInfo.dwCharSoundCode == snCHAR_SOUND_SHADOW ||
			smCharInfo.dwCharSoundCode == snCHAR_SOUND_BEEDOG ||
			smCharInfo.dwCharSoundCode == snCHAR_SOUND_MUTANTTREE ||
			smCharInfo.dwCharSoundCode == snCHAR_SOUND_SUCCUBUS ||
			smCharInfo.dwCharSoundCode == snCHAR_SOUND_BERSERKER ||
			smCharInfo.dwCharSoundCode == snCHAR_SOUND_STYGIANLORD ||

			smCharInfo.dwCharSoundCode == snCHAR_SOUND_AVELIN_ARCHER ||
			smCharInfo.dwCharSoundCode == snCHAR_SOUND_AVELIN_QUEEN ||
			smCharInfo.dwCharSoundCode == snCHAR_SOUND_DMACHINE ||
			smCharInfo.dwCharSoundCode == snCHAR_SOUND_SADNESS ||
			smCharInfo.dwCharSoundCode == snCHAR_SOUND_RUNICGUARDIAN ||
			smCharInfo.dwCharSoundCode == snCHAR_SOUND_BABEL ||
			smCharInfo.dwCharSoundCode == snCHAR_SOUND_HYPERMACHINE ||
			smCharInfo.dwCharSoundCode == snCHAR_SOUND_TURTLE_CANNON ||


			smCharInfo.dwCharSoundCode == snCHAR_SOUND_FROZEN ||
			smCharInfo.dwCharSoundCode == snCHAR_SOUND_CHAOSCARA ||
			smCharInfo.dwCharSoundCode == snCHAR_SOUND_COLDEYE ||
			smCharInfo.dwCharSoundCode == snCHAR_SOUND_M_LORD ||
			smCharInfo.dwCharSoundCode == snCHAR_SOUND_KELVEZU ||

			smCharInfo.dwCharSoundCode == snCHAR_SOUND_DARKGUARD ||
			smCharInfo.dwCharSoundCode == snCHAR_SOUND_DARKMAGE ||
			smCharInfo.dwCharSoundCode == snCHAR_SOUND_FIREWORM ||
			smCharInfo.dwCharSoundCode == snCHAR_SOUND_SETO ||

			smCharInfo.dwCharSoundCode == snCHAR_SOUND_NPC_MAGICMASTER ||
			smCharInfo.dwCharSoundCode == snCHAR_SOUND_NPC_SKILLMASTER ||

			smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_R ||
			smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_G ||
			smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_B ||

			smCharInfo.dwCharSoundCode == snCHAR_SOUND_GOBLINSHAMAN ||

			lpTransAttackData->AttackState == 0x80
			)
		{

			if (len < (460 * 460)) len = 0;

			cnt = 0;

			if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_WEB)
			{
				lpCurPlayer->PlaySlowCount = 70 * 2;
				lpCurPlayer->PlaySlowSpeed = 180;
			}
			if (!EventFlag)
			{
				dwAttackPlayTime = dwPlayTime + 1100;
				XorAttackTrans();
				return TRUE;
			}
		}

		if (lpTransAttackData->sRating[0] < 0)
		{
			Param1 = -lpTransAttackData->sRating[0];
			Param2 = lpTransAttackData->sRating[1];
			lpTransAttackData->sRating[0] = 0;
			lpTransAttackData->sRating[1] = 0;
		}
		else
		{
			Param1 = 0;
			Param2 = 0;
		}



		if (lpCurPlayer->smCharInfo.State == smCHAR_STATE_ENEMY) act = 1;
		else act = 0;

		if (lpTransAttackData->AttackState == 0x80)
		{
			x = (lpTransAttackData->x - lpCurPlayer->pX) >> FLOATNS;
			y = (lpTransAttackData->y - lpCurPlayer->pY) >> FLOATNS;
			z = (lpTransAttackData->z - lpCurPlayer->pZ) >> FLOATNS;
			if ((x*x + y * y + z * z) > (140 * 140))
			{
				cnt = lpTransAttackData->AttackSize;
			}
			act = 1;
		}

		Record_RecvDamageCount++;

		if (cnt < lpTransAttackData->AttackSize && sinGetLife()>0 && (len < (330 * 330) || act) && DisplayAlpha == 0)
		{


			lpChar = this;

			block = FALSE;

			if (lpChar)
			{
				if (lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_ARCHER)
				{
					cnt = cSkill.GetSkillPoint(SKILL_EVASION_MASTERY);
					if (cnt > 0 && cnt <= 10)
					{
						cnt = Evasion_Mastery_AddPercent[cnt - 1];
						if (cnt <= 26)
						{
							if ((rand() % 100) <= cnt)
							{

								cInterFace.SetStringEffect(HA_EVASION);
								block = 100;
								Record_BlockCount++;
							}
						}
					}
				}

				if (lpCurPlayer->smCharInfo.Chance_Block)
				{
					ChanceBlock = sinGetBlockRating(lpChar->smCharInfo.Level);

					if ((lpCurPlayer->HvLeftHand.dwItemCode&sinITEM_MASK2) == sinDS1)
					{
						if (lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_MECHANICIAN && (lpCurPlayer->dwDispAppSkill&SKILL_APPMASK_EXTREME_SHIELD) != 0)
						{
							ChanceBlock += (lpTransAttackData->AttackState >> 16);
						}
						if (lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_KNIGHT && (lpCurPlayer->dwDispAppSkill&SKILL_APPMASK_SPARK_SHIELD) != 0)
						{
							ChanceBlock += (lpTransAttackData->AttackState >> (16 + 8));
						}
						if (lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_KNIGHT && (lpCurPlayer->dwDispAppSkill&SKILL_APPMASK_GODLY_SHIELD) != 0)
						{
							cnt = cSkill.GetSkillPoint(SKILL_DIVINE_INHALATION);
							if (cnt > 0 && D_Inhalation_Block[cnt - 1] <= 10)
							{
								ChanceBlock += D_Inhalation_Block[cnt - 1];
							}
						}
						if (ChanceBlock > 50) ChanceBlock = 50;
					}
				}
				else
					ChanceBlock = 0;

				if ((rand() % 100) < ChanceBlock)
				{

					cInterFace.SetStringEffect(HA_BLOCK);
					block = TRUE;
					Record_BlockCount++;

					if (abs(lpChar->smCharInfo.Level - lpCurPlayer->smCharInfo.Level) <= AGING_SUB_LEVEL)
					{

						sinCheckAgingLevel(SIN_AGING_BLOCK, false);
					}

					if ((lpCurPlayer->dwDispAppSkill&SKILL_APPMASK_SPARK_SHIELD) && lpChar)
					{

						if (lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_MECHANICIAN)
						{

							dm_SendTransDamage(lpChar, 0, 0, 0, 0, SKILL_PLAY_SPARK_SHIELD | 0x100, FALSE);

						}

						if (lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_KNIGHT)
						{
							cnt = (lpTransAttackData->AttackState >> 16) & 0xFF;
							if (cnt > 0)
							{
								sinSetLife((sinGetLife() + cnt));
								ResetEnergyGraph(0);

								if (lpCurPlayer->HvLeftHand.PatTool)
								{
									if (lpCurPlayer->GetToolBipPoint(&lpCurPlayer->HvLeftHand, &x, &y, &z))
									{
										Pos1.x = x;
										Pos1.y = y;
										Pos1.z = z;

										AssaParticle_DivineInhalationDefence(&Pos1);
									}
								}
							}
						}
					}
				}
			}


			if (lpChar && (!block || act))
			{



				if (sizeof(TRANS_ATTACKDATA) == lpTransAttackData->size)
					cnt = sinGetMonsterAccuracy(lpTransAttackData->sRating[0], lpTransAttackData->sRating[1]);
				else
					cnt = sinGetMonsterAccuracy(smCharInfo.Level, smCharInfo.Attack_Rating);

				if (dmAttackCount < 2) cnt <<= 2;


				if ((rand() % 100) <= cnt || act)
				{

					cnt = lpTransAttackData->Power;

					if ((lpCurPlayer->dwDispAppSkill&SKILL_APPMASK_HOLY_BODY))
					{
						if (smCharInfo.Brood == smCHAR_MONSTER_UNDEAD)
						{


							HolyBody_Undead = TRUE;
						}
					}

					if (lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_MAGICIAN)
					{

						temp = lpTransAttackData->AttackState >> 16;
						if (temp > 0)
						{
							AssaParticle_EnergyShieldDefence(lpCurPlayer);
							temp = sinGetMana() - temp;
							if (temp < 0) temp = 0;
							sinSetMana(temp);
							ResetEnergyGraph(1);
						}
					}

					if (lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_PRIESTESS)
					{

						if (lpChar->smCharInfo.Brood == smCHAR_MONSTER_UNDEAD && (lpCurPlayer->dwDispAppSkill&SKILL_APPMASK_GODLY_SHIELD) != 0)
						{
							temp = lpTransAttackData->AttackState >> 16;
							if (temp > 0)
							{
								temp = sinGetLife() + temp;
								sinSetLife(temp);
								ResetEnergyGraph(0);
							}
						}
					}

					bStunCount = lpCurPlayer->PlayStunCount;
					lpCurPlayer->PlayStunCount = 0;

					switch (Param1)
					{
					case SKILL_PLAY_ROAR:
					case SKILL_PLAY_SHIELD_STRIKE:
						if (!bStunCount)
						{
							lpCurPlayer->PlayStunCount = GetResistancePower(Param2 * 70, sITEMINFO_BIONIC);
							AssaParticle_Stune(lpCurPlayer, Param2 + 1);
						}
						break;
					case SKILL_PLAY_GROUND_PIKE:
						lpCurPlayer->PlaySlowCount = GetResistancePower(Param2 * 70, sITEMINFO_ICE);
						lpCurPlayer->PlaySlowSpeed = 180;
						lpCurPlayer->AttackIce = 1;
						break;
					case SKILL_PLAY_GLACIAL_SPIKE:
					case SKILL_PLAY_ICE_CRYSTAL:
						lpCurPlayer->PlaySlowCount = GetResistancePower(Param2 * 70, sITEMINFO_ICE);
						lpCurPlayer->PlaySlowSpeed = 200;
						lpCurPlayer->AttackIce = 1;
						break;
					case SKILL_PLAY_DISTORTION:
						lpCurPlayer->PlaySlowCount = Param2 * 70;
						lpCurPlayer->PlaySlowSpeed = 210;
						lpCurPlayer->PlayDistortion = lpCurPlayer->PlaySlowCount;
						lpCurPlayer->AttackIce = 0;
						break;
					case SKILL_PLAY_ENCHANT_WEAPON:
						lpCurPlayer->PlaySlowCount = GetResistancePower(100, sITEMINFO_ICE);
						lpCurPlayer->PlaySlowSpeed = Param2 * 70;
						lpCurPlayer->AttackIce = 1;
						break;
					case SKILL_PLAY_DANCING_SWORD:
						lpCurPlayer->PlaySlowCount = GetResistancePower(140, sITEMINFO_ICE);
						lpCurPlayer->PlaySlowSpeed = Param2 * 70;
						lpCurPlayer->AttackIce = 1;
						break;
					case SKILL_PLAY_FROST_JAVELIN:
						lpCurPlayer->PlaySlowCount = GetResistancePower(210, sITEMINFO_ICE);
						lpCurPlayer->PlaySlowSpeed = Param2 * 70;
						lpCurPlayer->AttackIce = 1;
						break;
					case SKILL_PLAY_FIRE_CRYSTAL:
						cnt = GetResistancePower(cnt, sITEMINFO_FIRE);
						break;
					case SKILL_PLAY_LIGHTNING_CRYSTAL:
						if (!bStunCount)
						{
							lpCurPlayer->PlayStunCount = GetResistancePower(Param2 * 70, sITEMINFO_LIGHTING);
							AssaParticle_Stune(lpCurPlayer, Param2 + 1);
						}
						break;
					}


					switch (smCharInfo.dwCharSoundCode)
					{
					case snCHAR_SOUND_COLDEYE:
					case snCHAR_SOUND_FROZEN:

						if ((lpTransAttackData->AttackState & 0xFF) == 0x80)
							lpCurPlayer->PlaySlowCount = GetResistancePower(70 * 4, sITEMINFO_ICE);
						lpCurPlayer->PlaySlowSpeed = 200;
						lpCurPlayer->AttackIce = 1;
						break;
					case snCHAR_SOUND_FROST:
					case snCHAR_SOUND_DEATHKNIGHT:
						if ((lpTransAttackData->AttackState & 0xFF) == 0x80)
							lpCurPlayer->PlaySlowCount = GetResistancePower(70 * 6, sITEMINFO_ICE);
						lpCurPlayer->PlaySlowSpeed = 200;
						lpCurPlayer->AttackIce = 1;
						break;

					case snCHAR_SOUND_CHAOSCARA:

						if (Param1 == SKILL_PLAY_CHAOSCARA_VAMP && LastSkillParam)
						{
							sinSetMana(sinGetMana() - cnt);
						}
						break;

					case snCHAR_SOUND_STINGRAY:
						if (chrAttackTarget && (lpTransAttackData->AttackState & 0xFF) == 0x80)
						{
							ParkAssaParticle_Posion(chrAttackTarget, STINGRAY_POSION_TIME);
							if (chrAttackTarget == lpCurPlayer)
							{
								len = GetResistancePower(70 * STINGRAY_POSION_TIME, sITEMINFO_POISON);
								lpCurPlayer->PlayPoison[0] = 1;
								lpCurPlayer->PlayPoison[1] = len;
							}
						}
						break;

					case snCHAR_SOUND_KINGBAT:
						ParkAssaParticle_Posion(chrAttackTarget, STINGRAY_POSION_TIME);
						if (chrAttackTarget == lpCurPlayer)
						{
							len = GetResistancePower(70 * STINGRAY_POSION_TIME, sITEMINFO_POISON);
							lpCurPlayer->PlayPoison[0] = 1;
							lpCurPlayer->PlayPoison[1] = len;
						}
						break;

					case snCHAR_SOUND_DEVIL_BIRD:
						if (chrAttackTarget)
						{
							ParkDevilBirdAttackNormal(chrAttackTarget);
						}
						break;



					case snCHAR_SOUND_BLOODYKNIGHT:
						if (chrAttackTarget && (lpTransAttackData->AttackState & 0xFF) == 0x80)
						{
							ParkAssaParticle_BloodySkillStun(chrAttackTarget);
							lpCurPlayer->PlayStunCount = 70 * 3;
						}
						break;
					case snCHAR_SOUND_HELLHOUND:
						if (chrAttackTarget && (lpTransAttackData->AttackState & 0xFF) == 0x80)
						{
							ParkAssaParticle_HellHoundSkillTaget(chrAttackTarget);
						}
						break;
					case snCHAR_SOUND_CHIMERA:
						if (chrAttackTarget && (lpTransAttackData->AttackState & 0xFF) == 0x80)
						{
							lpCurPlayer->PlayStunCount = 70 * 3;
						}
						break;


					}





					if (PkMode_CharState == smCHAR_STATE_USER)
						cnt = (cnt - ((lpCurPlayer->smCharInfo.Absorption*PKMODE_ABSORB) / 100));
					else
						cnt = (cnt - lpCurPlayer->smCharInfo.Absorption);



					if (cnt <= 0) cnt = 1;

					if (abs(lpChar->smCharInfo.Level - lpCurPlayer->smCharInfo.Level) <= AGING_SUB_LEVEL)
					{


						sinCheckAgingLevel(SIN_AGING_DEFENSE_ARMOR, false);
						sinCheckAgingLevel(SIN_AGING_DEFENSE_ORB, false);
						sinCheckAgingLevel(SIN_AGING_DEFENSE_BOOTS, false);
						sinCheckAgingLevel(SIN_AGING_DEFENSE_GLOVES, false);
						sinCheckAgingLevel(SIN_AGING_DEFENSE_ARMLETS, false);
					}

					CheckCharForm();

					sinSetLife(sinGetLife() - cnt);



					if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_SUCCUBUS)
					{
						if (lpTransAttackData->sRating[0] > 75)
						{
							if (lpTransAttackData->sRating[0] < 80)
								sinSetStamina(sinGetStamina() - ((lpCurPlayer->smCharInfo.Stamina[1] * 6) / 100));
							else
								sinSetMana(sinGetMana() - ((lpCurPlayer->smCharInfo.Mana[1] * 6) / 100));
						}
					}


					StartEffect(lpCurPlayer->pX, lpCurPlayer->pY + 16 * fONE, lpCurPlayer->pZ, EFFECT_DAMAGE1);
					SetDynLight(lpCurPlayer->pX, lpCurPlayer->pY + 16 * fONE, lpCurPlayer->pZ, 160, 0, 0, 0, 180);

					if (((lpCurPlayer->dwDispAppSkill&SKILL_APPMASK_PHYSICAL_ABSORB) && (lpCurPlayer->dwDispAppSkill&SKILL_APPMASK_HOLY_BODY) == 0) || HolyBody_Undead)
					{

						StartEffect(lpCurPlayer->pX, lpCurPlayer->pY + 24 * fONE, lpCurPlayer->pZ, EFFECT_PHYSICAL_ABSORB_DAMAGE);
					}

					if (lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_DAMAGE && lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_EAT && lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_ATTACK &&
						lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_SKILL && cnt > 1)
					{

						lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_DAMAGE);
						CharPlaySound(lpCurPlayer);
					}


					if (sinGetLife() <= 0)
					{
						lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_DEAD);
						sinSetLife(0);
						CharPlaySound(lpCurPlayer);

						SendCommand_AreaServer(OpCode::OPCODE_DEAD_USER, dwObjectSerial, 0, 0, 0);
						SendCommand_DataServer(OpCode::OPCODE_DEAD_USER, dwObjectSerial, 1, 0, 0);
						WeaponEffect = 0;
						dwWeaponEffectTime = 0;

#ifdef LOG_THE_PK
						if (smCharInfo.State != smCHAR_STATE_USER && PkMode_CharState != smCHAR_STATE_USER)
#else
						if (smCharInfo.State != smCHAR_STATE_USER)
#endif
						{
							DeadPlayerExp(lpCurPlayer);
						}
						sinCheckQuest85Die();


						SaveGameData();

#ifdef LOG_THE_PK
						if (smCharInfo.State == smCHAR_STATE_USER || PkMode_CharState == smCHAR_STATE_USER)
#else
						if (smCharInfo.State == smCHAR_STATE_USER)
#endif
						{

							PlayerKilling(dwObjectSerial);
						}
						ResetAttackTrans();
						SetFullZoomMap(0);
						return TRUE;
					}
					ReformCharForm();

				}
				else
				{

					cInterFace.SetStringEffect(HA_DEFANCE);
					Record_DefenceCount++;
				}
			}
			dwBattleTime = dwPlayTime;
		}
	}

	ResetAttackTrans();


	return TRUE;
}


int smCHAR::MakePlayBuffFromPosi(int px, int py, int pz, int anX, int anY, int anZ, int act)
{
	int len;
	int sx, sy, sz;
	int x, y, z;
	int mx, my, mz;
	int PlayBuffPosi;
	int cnt;
	int aY;
	int dist;



	if (!smMotionInfo) return FALSE;

	len = 0x40;


	if (PlayBuffPosi_End <= 0)
	{
		sx = px;
		sy = py;
		sz = pz;
	}
	else
	{
		PlayBuffPosi = (PlayBuffPosi_End - 1) & PLAYBUFF_MASK;
		sx = PlayBuff[PlayBuffPosi].x;
		sy = PlayBuff[PlayBuffPosi].y;
		sz = PlayBuff[PlayBuffPosi].z;
	}

	if (sx == px && sy == py && sz == pz)
		aY = anY;
	else
		aY = GetRadian2D(sx, sz, px, pz);

	x = (px - sx) >> FLOATNS;
	z = (py - sy) >> FLOATNS;

	dist = x * x + z * z;
	if (dist > (110 * 110))
	{


		PlayBuffPosi = PlayBuffPosi_End & PLAYBUFF_MASK;

		PlayBuff[PlayBuffPosi].x = px;
		PlayBuff[PlayBuffPosi].y = py;
		PlayBuff[PlayBuffPosi].z = pz;

		PlayBuff[PlayBuffPosi].angle[0] = 0;
		PlayBuff[PlayBuffPosi].angle[1] = aY;
		PlayBuff[PlayBuffPosi].angle[2] = 0;
		PlayBuff[PlayBuffPosi].angle[3] = 0;

		PlayBuff[PlayBuffPosi].frame = smPLAYBUFF_FRAME_NONE | 80;
		PlayBuff[PlayBuffPosi].dwTargetSerial = 0;

		memcpy(PlayBuff[PlayBuffPosi].wStickItems, wStickItems, sizeof(short) * 4);

		PlayBuffPosi_End++;
		return TRUE;
	}

	mx = ((px - sx) << 8) / len;
	my = ((py - sy) << 8) / len;
	mz = ((pz - sz) << 8) / len;

	x = 0;	y = 0;	z = 0;

	for (cnt = 0; cnt < len; cnt++)
	{
		PlayBuffPosi = (PlayBuffPosi_End + cnt) & PLAYBUFF_MASK;

		PlayBuff[PlayBuffPosi].x = sx + (x >> 8);
		PlayBuff[PlayBuffPosi].y = sy + (y >> 8);
		PlayBuff[PlayBuffPosi].z = sz + (z >> 8);

		PlayBuff[PlayBuffPosi].angle[0] = 0;
		PlayBuff[PlayBuffPosi].angle[1] = aY;
		PlayBuff[PlayBuffPosi].angle[2] = 0;
		PlayBuff[PlayBuffPosi].angle[3] = 0;

		PlayBuff[PlayBuffPosi].frame = smPLAYBUFF_FRAME_NONE | 80;
		PlayBuff[PlayBuffPosi].dwTargetSerial = 0;

		memcpy(PlayBuff[PlayBuffPosi].wStickItems, wStickItems, sizeof(short) * 4);

		x += mx;
		y += my;
		z += mz;
	}
	PlayBuffPosi_End = PlayBuffPosi_End + len;

	return TRUE;
}


int smCHAR::MakePlayBuffFromRecvData(smPLAYBUFF *StartBuff, smPLAYBUFF *EndBuff, int len)
{
	int cnt;
	int x, y, z;
	int px, py, pz;
	int mx, my, mz;
	int PlayBuffPosi;
	int aX, aY, aZ;
	int saX, saY, saZ;
	int taX, taY, taZ;
	int frameState;
	int frameStep;

	if (!smMotionInfo || len <= 1) return FALSE;

	if (!EndBuff)
	{
		PlayBuffPosi = PlayBuffPosi_End & PLAYBUFF_MASK;

		PlayBuff[PlayBuffPosi].x = StartBuff->x;
		PlayBuff[PlayBuffPosi].y = StartBuff->y;
		PlayBuff[PlayBuffPosi].z = StartBuff->z;

		PlayBuff[PlayBuffPosi].angle[0] = StartBuff->angle[0] & ANGCLIP;
		PlayBuff[PlayBuffPosi].angle[1] = StartBuff->angle[1] & ANGCLIP;
		PlayBuff[PlayBuffPosi].angle[2] = StartBuff->angle[2] & ANGCLIP;
		PlayBuff[PlayBuffPosi].angle[3] = StartBuff->angle[3];

		PlayBuff[PlayBuffPosi].frame = StartBuff->frame;
		PlayBuff[PlayBuffPosi].dwTargetSerial = StartBuff->dwTargetSerial;

		memcpy(PlayBuff[PlayBuffPosi].wStickItems, StartBuff->wStickItems, sizeof(short) * 4);
		PlayBuffPosi_End++;
		return TRUE;
	}

	px = StartBuff->x;
	py = StartBuff->y;
	pz = StartBuff->z;

	mx = ((EndBuff->x - px) << 8) / len;
	my = ((EndBuff->y - py) << 8) / len;
	mz = ((EndBuff->z - pz) << 8) / len;

	aX = StartBuff->angle[0];
	aY = StartBuff->angle[1];
	aZ = StartBuff->angle[2];

	taX = ANGLE_180 - EndBuff->angle[0];
	taY = ANGLE_180 - EndBuff->angle[1];
	taZ = ANGLE_180 - EndBuff->angle[2];

	saX = (aX + taX) & ANGCLIP;
	saY = (aY + taY) & ANGCLIP;
	saZ = (aZ + taZ) & ANGCLIP;

	saX = ((saX - ANGLE_180) << 8) / len;
	saY = ((saY - ANGLE_180) << 8) / len;
	saZ = ((saZ - ANGLE_180) << 8) / len;

	if (StartBuff->frame < CHAR_FRAME_MASK)
	{
		frameState = smMotionInfo->MotionInfo[StartBuff->angle[3]].State;
		if (frameState == CHRMOTION_STATE_WALK || frameState == CHRMOTION_STATE_RUN)
		{
			aY = GetRadian2D(px, pz, EndBuff->x, EndBuff->z);
			saY = 0;
		}
	}


	x = 0;
	y = 0;
	z = 0;

	taX = 0;
	taY = 0;
	taZ = 0;

	cnt = len - 1;
	if (cnt <= 0)
	{
		frameStep = 80;
	}
	else
	{
		frameStep = (EndBuff->frame - StartBuff->frame) / cnt;
	}

	if (frameStep >= 4096 || frameStep < 20)
	{
		frameStep = 80;
	}

	for (cnt = 0; cnt < len; cnt++)
	{
		PlayBuffPosi = (PlayBuffPosi_End + cnt) & PLAYBUFF_MASK;

		PlayBuff[PlayBuffPosi].x = px + (x >> 8);
		PlayBuff[PlayBuffPosi].y = py + (y >> 8);
		PlayBuff[PlayBuffPosi].z = pz + (z >> 8);

		PlayBuff[PlayBuffPosi].angle[0] = aX & ANGCLIP;
		PlayBuff[PlayBuffPosi].angle[1] = aY & ANGCLIP;
		PlayBuff[PlayBuffPosi].angle[2] = aZ & ANGCLIP;

		PlayBuff[PlayBuffPosi].angle[3] = StartBuff->angle[3];

		PlayBuff[PlayBuffPosi].frame = smPLAYBUFF_FRAME_NONE | frameStep;

		PlayBuff[PlayBuffPosi].dwTargetSerial = StartBuff->dwTargetSerial;

		memcpy(PlayBuff[PlayBuffPosi].wStickItems, StartBuff->wStickItems, sizeof(short) * 4);

		x += mx;
		y += my;
		z += mz;

		taX += saX;
		taY += saY;
		taZ += saZ;
	}

	PlayBuff[PlayBuffPosi_End&PLAYBUFF_MASK].frame = StartBuff->frame;
	PlayBuff[(PlayBuffPosi_End + len - 1)&PLAYBUFF_MASK].frame = EndBuff->frame;

	PlayBuffPosi_End = PlayBuffPosi_End + len;

	return TRUE;
}


int smCHAR::TransDelayCheck()
{
	int Delay;

	if (TransSock && TransSock->ConnectDirection)
	{
		Delay = PlayCounter - TransLastSendCnt;

		if (Delay > TransDelayMax)
		{
			TransSendWait = 0;
			TransLastSendCnt = PlayCounter - 16;
			return TRUE;
		}
	}

	return FALSE;
}


int smCHAR::SetDistSendCnt(smCHAR *player)
{
	int x, y, z;
	int dist;

	x = (pX - player->pX) >> FLOATNS;
	y = (pY - player->pY) >> FLOATNS;
	z = (pZ - player->pZ) >> FLOATNS;

	dist = x * x + y * y + z * z;

	if (dist < DIST_TRANSLEVEL_HIGH || !DisplayFlag)
	{
		TransMinCnt = 8;
		TransLevel = 0;
		TransDelayMax = PLAYCOUNT_PER_SECOND * 4;
		return TRUE;
	}
	if (dist < DIST_TRANSLEVEL_MID)
	{
		TransMinCnt = PLAYCOUNT_PER_SECOND;
		TransLevel = 1;
		TransDelayMax = PLAYCOUNT_PER_SECOND * 6;
		return TRUE;
	}
	if (dist < DIST_TRANSLEVEL_LOW)
	{
		TransMinCnt = PLAYCOUNT_PER_SECOND * 5;
		TransLevel = 2;
		TransDelayMax = PLAYCOUNT_PER_SECOND * 10;
		return TRUE;
	}

	TransMinCnt = PLAYCOUNT_PER_SECOND * 15;
	TransLevel = 3;
	TransDelayMax = PLAYCOUNT_PER_SECOND * 25;

	return TRUE;
}


int smCHAR::FormSetPlayerInfo()
{
	int cnt = 0;

	if (!Pattern)
	{

		char szBuff[128];

		wsprintf(szBuff, "Mesh Pattern Error [ %s ] ( %s %s )", smCharInfo.szName, smCharInfo.szModelName, smCharInfo.szModelName2);
		//LOG(LOG_ERROR, "Mesh Pattern Error [ %s ] ( %s %s )", smCharInfo.szName, smCharInfo.szModelName, smCharInfo.szModelName2);
		Record_ClinetLogFile(szBuff);
	}


	PHeight = pY;

	smCharInfo.bUpdateInfo[1] = 0xFF;

	if (this != lpCurPlayer && lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_STAND && abs(lpCurPlayer->pX - pX) < 32 * fONE && abs(lpCurPlayer->pZ - pZ) < 32 * fONE)
	{
		if (lpCurPlayer->OnStageField >= 0)
		{
			if (StageField[lpCurPlayer->OnStageField]->CheckStartPoint(lpCurPlayer->pX, lpCurPlayer->pZ) == TRUE)
			{
				lpCurPlayer->MoveFlag = TRUE;
				lpCurPlayer->MoveCnt = 100;
			}
		}
	}


	if (smCharInfo.State != smCHAR_STATE_ENEMY)
	{
		OnStageField = -1;
		if (smGameStage[0] && Pattern)
		{
			cnt = smGameStage[0]->GetFloorHeight(pX, pY, pZ, Pattern->SizeHeight);
			OnStageField = 0;
		}
		if (cnt == CLIP_OUT && smGameStage[1])
		{
			OnStageField = 1;
		}
	}

	PatSizeLevel = smCharInfo.SizeLevel;
	if (PatSizeLevel >= 0x1000) PatSizeLevel = 1;

	if (TransSock && TransSock->ConnectDirection) 	TransSendWait = 0;
	else TransSendWait = 1;

	TransLastSendCnt = PlayCounter;

	TransMinCnt = 8;
	TransLevel = 0;
	TransDelayMax = PLAYCOUNT_PER_SECOND * 4;

	PlayBuffPosi_End = 0;
	PlayBuffCnt = 0;

	DisplayAlpha = -256;
	DispLifeBar = 0;

	switch (smCharInfo.dwCharSoundCode)
	{
	case snCHAR_SOUND_FIGON:

		if (Pattern && Pattern->TmParent)
		{
			HvLeftHand.ObjBip = Pattern->TmParent->GetObjectFromName("Bip01 L Finger1");
			HvRightHand.ObjBip = Pattern->TmParent->GetObjectFromName("Bip01 R Finger1");
		}
		else
		{
			HvLeftHand.ObjBip = 0;
			HvRightHand.ObjBip = 0;
		}
		break;

	case snCHAR_SOUND_ILLUSIONKNIGHT:

		RendAlpha = -180;
		break;

	case snCHAR_SOUND_MUDY:

		RenderLatter = TRUE;
		break;

	case snCHAR_SOUND_WOLVERLIN:

		if (smCharInfo.State == smCHAR_STATE_ENEMY)
		{
			sAddColorEffect[SMC_R] = 100;
			sAddColorEffect[SMC_G] = 100;
		}
		break;

	case snCHAR_SOUND_SEN:

		if (Pattern && Pattern->TmParent)
		{
			HvLeftHand.ObjBip = Pattern->TmParent->GetObjectFromName("Bip01");
		}
		else
		{
			HvLeftHand.ObjBip = 0;
			HvRightHand.ObjBip = 0;
		}
		break;

	case snCHAR_SOUND_MUTANTTREE:

		if (Pattern && Pattern->TmParent)
		{
			HvLeftHand.ObjBip = Pattern->TmParent->GetObjectFromName("Bip05");
		}
		else
		{
			HvLeftHand.ObjBip = 0;
			HvRightHand.ObjBip = 0;
		}
		break;

	case snCHAR_SOUND_SHADOW:

		if (Pattern && Pattern->TmParent)
		{
			HvLeftHand.ObjBip = Pattern->TmParent->GetObjectFromName("Bip01 L UpperArm");
			HvRightHand.ObjBip = Pattern->TmParent->GetObjectFromName("Bip01 R UpperArm");
		}
		else
		{
			HvLeftHand.ObjBip = 0;
			HvRightHand.ObjBip = 0;
		}
		break;

	case snCHAR_SOUND_MRGHOST:
		RendAlpha = -80;
		break;

	case snCHAR_SOUND_FURY:
		AssaParticle_Fury_Eye(this);

		switch (smCharInfo.Level)
		{
		case 118:
			sAddColorEffect[SMC_R] = 100;
			sAddColorEffect[SMC_G] = 100;
			RendAlpha = -80;
			break;
		case 119:
			sAddColorEffect[SMC_R] = 100;
			RendAlpha = -80;
			break;
		case 120:
			sAddColorEffect[SMC_B] = 100;
			RendAlpha = -80;
			break;
		}
		break;

	case snCHAR_SOUND_BEEVIL:
		RenderLatter = TRUE;
		break;

	case snCHAR_SOUND_GUARDIAN_SAINT:
		sAddColorEffect[SMC_R] = 80;
		sAddColorEffect[SMC_G] = 80;
		sAddColorEffect[SMC_B] = 20;

		AssaParticleClanMonster(this);
		break;

	case  snCHAR_SOUND_CHAINGOLEM:
		AssaParticle_MonsterIronChainGolem(this);
		break;

	case snCHAR_SOUND_RUNICGUARDIAN:
		AssaParticle_MonsterRunicGuardianHand(this);
		break;

	case snCHAR_SOUND_BABEL:
		AssaParticle_MonsterRunicGuardianBossWeapon(this);
		break;

	case snCHAR_SOUND_CHAOSCARA:
		ParkAssaParticle_MonsterIceChaosKara(this);
		break;

	case snCHAR_SOUND_DEATHKNIGHT:
		ParkAssaParticle_MonsterIceValentoBody(this);
		break;

	case snCHAR_SOUND_S_F_ELEMENTAL:
		SkillArchMageFireElementalHand(this);
		break;

	case snCHAR_SOUND_NPC_SKILLMASTER:
		if (Pattern && Pattern->TmParent)
			AttackObjBip = Pattern->TmParent->GetObjectFromName("bip01 weapon");
		break;

	case snCHAR_SOUND_NPC_MAGICMASTER:
		if (Pattern && Pattern->TmParent)
			AttackObjBip = Pattern->TmParent->GetObjectFromName("Bip01 staff02");
		break;

	case snCHAR_SOUND_CASTLE_SOLDER_A:
	case snCHAR_SOUND_CASTLE_SOLDER_B:
	case snCHAR_SOUND_CASTLE_SOLDER_C:
		if (Pattern && Pattern->TmParent)
			AttackObjBip = Pattern->TmParent->GetObjectFromName("Bip01 Effect");
		break;

	case snCHAR_SOUND_KELVEZU:
		ParkKelvezuJin(this);
		break;
	case snCHAR_SOUND_REVIVED_KNIGHT:
		if (Pattern && Pattern->TmParent)
		{
			HvRightHand.ObjBip = Pattern->TmParent->GetObjectFromName("Bip01 R Hand");
		}
		break;
	case snCHAR_SOUND_REVIVED_PIKEMAN:
		if (Pattern && Pattern->TmParent)
		{
			AttackObjBip = Pattern->TmParent->GetObjectFromName("bip01 wea");
		}
		break;
	case snCHAR_SOUND_REVIVED_ARCHER:
		if (Pattern && Pattern->TmParent)
		{
			HvRightHand.ObjBip = Pattern->TmParent->GetObjectFromName("Bip01 R Hand");
		}
		break;
	}



	if (smCharInfo.wPlayClass[0] == MONSTER_CLASS_BOSS)
	{

		if (smCharInfo.State == smCHAR_STATE_ENEMY)
		{
			sAddColorEffect[SMC_R] = 130;
			sAddColorEffect[SMC_G] = 50;
			sAddColorEffect[SMC_B] = 70;
		}
	}

	return TRUE;
}


int smCHAR::SetTransPlayerInfo(smTRNAS_PLAYERINFO *lpTransPlayerInfo)
{
	memcpy(&smCharInfo, &lpTransPlayerInfo->smCharInfo, sizeof(smCHAR_INFO));
	ResetAttackTrans();

	if (!PatLoading)
		AddLoaderPattern((smCHAR *)&Head, smCharInfo.szModelName, smCharInfo.szModelName2);

	pX = lpTransPlayerInfo->x;
	pY = lpTransPlayerInfo->y;
	pZ = lpTransPlayerInfo->z;

	FormSetPlayerInfo();

	if (smCharInfo.ClassClan)
	{

		ClanInfoNum = ReadClanInfo(smCharInfo.ClassClan);
		dwClanInfoTime = dwPlayTime;

		if (GetClanCode(smCharInfo.ClassClan) == rsBlessCastle.dwMasterClan)
			Clan_CastleMasterFlag = TRUE;
	}

	PkMode_CharState = 0;

	return TRUE;
}


int smCHAR::SetTransPlayerInfoQuick(smTRNAS_PLAYERINFO_QUICK *lpTransPlayerInfo)
{
	int len = sizeof(smTRNAS_PLAYERINFO_QUICK) - lpTransPlayerInfo->size;

	ZeroMemory(&smCharInfo, sizeof(smCHAR_INFO));
	smCharInfo.Life[0] = 10;
	smCharInfo.Life[1] = 50;

	memcpy(&smCharInfo, &lpTransPlayerInfo->smCharInfo, sizeof(smCHAR_INFO) - len);
	ResetAttackTrans();

	if (!PatLoading)
		AddLoaderPattern((smCHAR *)&Head, smCharInfo.szModelName, smCharInfo.szModelName2);

	pX = lpTransPlayerInfo->x;
	pY = lpTransPlayerInfo->y;
	pZ = lpTransPlayerInfo->z;

	FormSetPlayerInfo();

	if (smCharInfo.ClassClan)
	{

		ClanInfoNum = ReadClanInfo(smCharInfo.ClassClan);
		dwClanInfoTime = dwPlayTime;

		if (GetClanCode(smCharInfo.ClassClan) == rsBlessCastle.dwMasterClan)
			Clan_CastleMasterFlag = TRUE;
	}

	PkMode_CharState = 0;

	return TRUE;
}


int smCHAR::RecvPlayData2(char *lpData)
{
	smPLAYDATA *lpPlayData;
	int RecvCode;
	int cnt;
	int len;
	int LastBuffPosi_End;
	int act;
	char *lpBuff;
	int	Code, Size;
	smCHAR	*lpChar;

	RecvCode = ((int *)lpData)[1];

	switch (RecvCode)
	{
	case OpCode::OPCODE_PLAYDATA1:

		lpPlayData = (smPLAYDATA *)lpData;

		act = lpPlayData->angle[3];

		MakePlayBuffFromPosi(lpPlayData->x, lpPlayData->y, lpPlayData->z, lpPlayData->angle[0], lpPlayData->angle[1], lpPlayData->angle[2], act);
		MoveCnt = 0;


		LastPlayDataType = 1;
		smCharInfo.bUpdateInfo[1] = 0xFF;
		break;

	case OpCode::OPCODE_TRANSPLAYDATA:


		smTRANS_PLAYDATA	*lpTransPlayData;
		smTRANS_PLAYBUFF	*lpTransPlayBuff;
		smTRANS_PLAYBUFF	*lpTransPlayBuff2;

		LastPlayDataType = 0;

		lpTransPlayData = (smTRANS_PLAYDATA *)lpData;
		lpTransPlayBuff = (smTRANS_PLAYBUFF *)(lpData + sizeof(smTRANS_PLAYDATA));

		LastBuffPosi_End = PlayBuffPosi_End;

		smCharInfo.Life[0] = lpTransPlayData->Hp[0];
		smCharInfo.Life[1] = lpTransPlayData->Hp[1];

		if (LevelLog)
		{
			if (smCharInfo.State == smCHAR_STATE_USER && lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_LEVEL] > LevelLog)
			{

				StartEffect(pX, pY + 32 * fONE, pZ, EFFECT_LEVELUP1);
				esPlaySound(7, GetDistVolume(pX, pY, pZ));
			}
		}

		LevelLog = lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_LEVEL];
		PotionLog = lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_POTION] & 0x0F;
		CriticalLog = lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_POTION] >> 4;
		dwDispAppSkill = lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_SKIL];



		if (CriticalLog >= 8) CriticalLog = -1;
		AttackCritcal = CriticalLog;

		if (lpTransPlayData->PlayBuffCnt > 1)
		{

			for (cnt = 0; cnt < lpTransPlayData->PlayBuffCnt - 1; cnt++)
			{
				lpTransPlayBuff2 = lpTransPlayBuff + 1;

				len = lpTransPlayBuff2->BuffCount - lpTransPlayBuff->BuffCount;
				MakePlayBuffFromRecvData(&lpTransPlayBuff->PlayBuff, &lpTransPlayBuff2->PlayBuff, len);

				lpTransPlayBuff++;
			}

			dwTarget = lpTransPlayData->dwTarget;

			if (smCharInfo.bUpdateInfo[1] == 0xFF)
			{

				smCharInfo.bUpdateInfo[1] = lpTransPlayData->bUpdateInfo[1];
			}
			else
			{
				if (lpTransPlayData->bUpdateInfo[1] != smCharInfo.bUpdateInfo[1])
				{

					if (lpTransPlayData->bUpdateInfo[1] < smCharInfo.bUpdateInfo[1])
						LearnSkillEffect(this);

					smCharInfo.bUpdateInfo[1] = lpTransPlayData->bUpdateInfo[1];
				}
			}


			lpTransPlayBuff++;
		}
		else
		{
			MakePlayBuffFromRecvData(&lpTransPlayBuff->PlayBuff, 0, 0);
			if (PlayBuffCnt == PlayBuffPosi_End)
			{

				if (DisplayFlag)
				{

					pX = lpTransPlayBuff->PlayBuff.x;
					pY = lpTransPlayBuff->PlayBuff.y;
					pZ = lpTransPlayBuff->PlayBuff.z;


					if (lpTransPlayBuff->PlayBuff.wStickItems[smPLAYBUFF_ITEM_LEFT] != wStickItems[smPLAYBUFF_ITEM_LEFT])
					{
						if (lpTransPlayBuff->PlayBuff.wStickItems[smPLAYBUFF_ITEM_LEFT] >= 0)
						{
							SetTool(sItem[lpTransPlayBuff->PlayBuff.wStickItems[smPLAYBUFF_ITEM_LEFT]].CODE, hvPOSI_LHAND);
							HvLeftHand.ColorBlink = 0;
							HvLeftHand.DispEffect = 0;
						}
						else
							SetTool(0, hvPOSI_LHAND);
					}


					if (lpTransPlayBuff->PlayBuff.wStickItems[smPLAYBUFF_ITEM_RIGHT] != wStickItems[smPLAYBUFF_ITEM_RIGHT])
					{
						if (lpTransPlayBuff->PlayBuff.wStickItems[smPLAYBUFF_ITEM_RIGHT] >= 0)
						{
							SetTool(sItem[lpTransPlayBuff->PlayBuff.wStickItems[smPLAYBUFF_ITEM_RIGHT]].CODE, hvPOSI_RHAND);
							HvRightHand.ColorBlink = 0;
							HvRightHand.DispEffect = 0;
						}
						else
							SetTool(0, hvPOSI_RHAND);
					}


					if (lpTransPlayBuff->PlayBuff.wStickItems[smPLAYBUFF_ITEM_BODY] != wStickItems[smPLAYBUFF_ITEM_BODY])
					{
						SetChrArmor(this, lpTransPlayBuff->PlayBuff.wStickItems[smPLAYBUFF_ITEM_BODY]);
						wStickItems[smPLAYBUFF_ITEM_BODY] = lpTransPlayBuff->PlayBuff.wStickItems[smPLAYBUFF_ITEM_BODY];
					}
				}
			}

			lpTransPlayBuff++;
		}

		if (lpTransPlayData->bUpdateInfo[0] != smCharInfo.bUpdateInfo[0])
		{

			if (!dwUpdateCharInfoTime || (dwUpdateCharInfoTime + 1000) < dwPlayTime)
			{
				Send_GetCharInfo(dwObjectSerial, ServerCode);

				if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_HUNGKY && !dwUpdateCharInfoTime)
				{

					StartEffect(pX, pY + 48 * fONE, pZ, EFFECT_RETURN1);
					SetDynLight(pX, pY, pZ, 50, 100, 70, 0, 300, 1);


					if (MotionInfo)
					{
						cnt = MotionInfo->State;
						MotionInfo->State = CHRMOTION_STATE_WARP;
						CharPlaySound(this);
						MotionInfo->State = cnt;
					}
				}

				if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_DEADHOPT && !dwUpdateCharInfoTime)
				{
					StartEffect(pX, pY + 48 * fONE, pZ, EFFECT_RETURN1);
					SetDynLight(pX, pY, pZ, 50, 100, 70, 0, 300, 1);

					if (MotionInfo)
					{
						cnt = MotionInfo->State;
						MotionInfo->State = CHRMOTION_STATE_WARP;
						CharPlaySound(this);
						MotionInfo->State = cnt;
					}
				}


				if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_BEBECHICK && !dwUpdateCharInfoTime)
				{
					StartEffect(pX, pY + 48 * fONE, pZ, EFFECT_RETURN1);
					SetDynLight(pX, pY, pZ, 50, 100, 70, 0, 300, 1);

					if (MotionInfo)
					{
						cnt = MotionInfo->State;
						MotionInfo->State = CHRMOTION_STATE_WARP;
						CharPlaySound(this);
						MotionInfo->State = cnt;
					}
				}


				dwUpdateCharInfoTime = dwPlayTime;
			}
		}




		if (lpCurPlayer->OnStageField >= 0 &&
			((StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_CASTLE && CastleBattleZone_LineZ > lpCurPlayer->pZ) ||
			(StageField[lpCurPlayer->OnStageField]->FieldCode == PK_FieldState.FieldCode && PK_FieldState.dwPlay_FieldTime > dwPlayTime && !PartyFlag)
				))
		{


			if (PkMode_CharState == 0 && smCharInfo.State == smCHAR_STATE_USER &&
				(smCharInfo.ClassClan == 0 || smCharInfo.ClassClan != lpCurPlayer->smCharInfo.ClassClan))
			{

				if (StageField[lpCurPlayer->OnStageField]->FieldCode != PK_FieldState.FieldCode || !PartyFlag)
				{
					PkMode_CharState = smCharInfo.State;
					smCharInfo.State = smCHAR_STATE_ENEMY;
				}
			}

		}
		else
		{
			if (PkMode_CharState)
			{

				smCharInfo.State = PkMode_CharState;
				PkMode_CharState = 0;
			}
		}

		int ChkIceFlag = 0;
		int ChkPoisonFlag = 0;
		DWORD	TradeMsgCode = 0;


		PlayVanish = 0;
		TradeMsgCode = dwTradeMsgCode;
		dwTradeMsgCode = 0;
		PlayCurseQuest = 0;

		if (lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_EXT])
		{
			lpBuff = (char *)lpTransPlayBuff;

			for (cnt = 0; cnt < lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_EXT]; cnt++)
			{

				Code = ((int *)lpBuff)[1];
				Size = ((int *)lpBuff)[0];

				switch (Code)
				{
				case OpCode::OPCODE_EFFECT_ITEM:

					SetTransEffectItems((smEFFECT_ITEM *)lpBuff);
					break;

				case OpCode::OPCODE_EFFECT_WEAPON:

					SetTransEffectWeapon((smEFFECT_ITEM *)lpBuff);
					break;

				case OpCode::OPCODE_EFFECT_STUN:

					if (smCharInfo.Life[0] > 0)
					{
						PlayStunType = ((smEFFECT_ITEM *)lpBuff)->ColorBlink;
						AssaParticle_Stune(this, 4);
					}
					break;

				case OpCode::OPCODE_EFFECT_CURSE:

					if (smCharInfo.Life[0] > 0)
						StartEffect_Serqbus_Skill2(this, 4);
					break;

				case OpCode::OPCODE_EFFECT_ICE:

					if (((smEFFECT_ITEM *)lpBuff)->ColorBlink)
					{
						PlayDistortion = 120;
					}
					else
					{
						PlayDistortion = 0;
						if (AttackIce <= 0) AttackIce = 1;
						ChkIceFlag = TRUE;
					}
					break;

				case OpCode::OPCODE_EFFECT_CURSELAZY:
					PlayCurseLazy = ((smEFFECT_ITEM *)lpBuff)->dwItemCode;
					break;

				case OpCode::OPCODE_EFFECT_WISP:
					PlayWisp[0] = ((smEFFECT_ITEM *)lpBuff)->dwItemCode;
					PlayWisp[1] = ((smEFFECT_ITEM *)lpBuff)->ColorBlink;
					break;

				case OpCode::OPCODE_EFFECT_POISION:
					if (DispPoison <= 0) DispPoison = 1;
					ChkPoisonFlag = TRUE;
					break;

				case OpCode::OPCODE_EFFECT_CURSE_QUEST:
					PlayCurseQuest = 1;
					break;

				case OpCode::OPCODE_EFFECT_VANISH:
					PlayVanish = ((smEFFECT_ITEM *)lpBuff)->dwItemCode;
					PlayVague = ((smEFFECT_ITEM *)lpBuff)->ColorBlink;
					break;

				case OpCode::OPCODE_EFFECT_KEEPSKILL:

					switch (((smEFFECT_ITEM *)lpBuff)->dwItemCode)
					{
					case SKILL_PLAY_FORCE_OF_NATURE:
						SkillSagittarionForceOfNature2(this, 5.0f);
						break;
					case SKILL_PLAY_HALL_OF_VALHALLA:
						SkillValhallaHallOfValhallaHandEffect(this, 5.0f);
						break;
					case SKILL_PLAY_BLESS_SIEGE_ITEM:
						PlayInvincible = 70 * 5;
						break;
					}
					break;

				case OpCode::OPCODE_EFFECT_PERSHOP:
					dwTradeMsgCode = ((smEFFECT_ITEM *)lpBuff)->dwItemCode;

					if (TradeMsgCode != dwTradeMsgCode)
					{



						wsprintf(szTradeMessage, "%s :", smCharInfo.szName);

						SendCommand_AreaServer(OpCode::OPCODE_MYSHOP_MESSAGE, 0, dwObjectSerial, dwTradeMsgCode, 0);
					}
					break;

				case OpCode::OPCODE_EFFECT_LOWPET:

					if (((smEFFECT_ITEM *)lpBuff)->ColorBlink)
						lpChar = FindChrPlayer(((smEFFECT_ITEM *)lpBuff)->ColorBlink);
					else
						lpChar = 0;

					switch (((smEFFECT_ITEM *)lpBuff)->dwItemCode)
					{
					case 1:
						g_LowLevelAddIdlePet(this, PET_TERRY, lpChar);
						break;
					case 2:
						g_LowLevelAddIdlePet(this, PET_NEPSYS, lpChar);
						break;
					case 3:
						g_LowLevelAddIdlePet(this, PET_IO, lpChar);
						break;
					case 4:
						g_LowLevelAddIdlePet(this, PET_MUTE, lpChar);
						break;

					}
					break;

				case OpCode::OPCODE_EFFECT_PCBANGPET:

					if (((smEFFECT_ITEM *)lpBuff)->ColorBlink)
						lpChar = FindChrPlayer(((smEFFECT_ITEM *)lpBuff)->ColorBlink);
					else
						lpChar = 0;

					switch (((smEFFECT_ITEM *)lpBuff)->dwItemCode)
					{
					case 1:
						g_HoPCBangAddIdlePet(this, PCBANG_PET_BURSTP, lpChar);
						break;
					case 2:
						g_HoPCBangAddIdlePet(this, PCBANG_PET_BURSTS, lpChar);
						break;
					case 3:
						g_HoPCBangAddIdlePet(this, PCBANG_PET_BURSTL, lpChar);
						break;
					case 4:
						g_HoPCBangAddIdlePet(this, PCBANG_PET_BURSTD, lpChar);
						break;

					}
					break;

				case OpCode::OPCODE_EFFECT_CLANMGR:
					dwClanManageBit = ((smEFFECT_ITEM *)lpBuff)->dwItemCode;
					BlessCrown = ((smEFFECT_ITEM *)lpBuff)->DispEffect;
					break;

				case OpCode::OPCODE_EFFECT_FORCEORB:
					dwForceOrbCode = ((smEFFECT_ITEM *)lpBuff)->dwItemCode;
					dwForceOrbTime = ((smEFFECT_ITEM *)lpBuff)->ColorBlink;
					dwForceOrbTime += dwPlayTime;

					AssaParticle_ShelltomWeapon(this, 70 * 5, ((dwForceOrbCode & 0xFFFF) >> 8) - 1);
					break;

				case OpCode::OPCODE_EFFECT_BLESS_SCORE:

					sBlessCastle_Damage[0] = ((smEFFECT_ITEM *)lpBuff)->sColors[0];
					sBlessCastle_Damage[1] = ((smEFFECT_ITEM *)lpBuff)->sColors[1];
					break;
				}
				lpBuff += Size;
			}
		}
		if (!ChkIceFlag && AttackIce > 0) AttackIce = -AttackIce;
		if (!ChkPoisonFlag && DispPoison > 0) DispPoison = -DispPoison;

	}


	TransSendWait = 0;
	dwLastTransTime = dwPlayTime;

	return TRUE;
}


int smCHAR::RecvPlayData(smTHREADSOCK *pData)
{
	int act;
	smPLAYDATA PlayData;
	smPLAYDATA2 PlayData2;
	smPLAYDATA3 PlayData3;
	smTRNAS_PLAYERINFO	*lpTransPlayerInfo;
	int RecvCode;
	int cnt;
	int len;
	int LastBuffPosi_End;


	RecvCode = ((int *)pData->Buff)[1];

	switch (RecvCode)
	{
	case OpCode::OPCODE_PLAYERINFO:

		lpTransPlayerInfo = (smTRNAS_PLAYERINFO *)pData->Buff;
		SetTransPlayerInfo(lpTransPlayerInfo);
		return TRUE;

	case OpCode::OPCODE_PLAYERINFO_Q:

		SetTransPlayerInfoQuick((smTRNAS_PLAYERINFO_QUICK *)pData->Buff);
		break;

	case OpCode::OPCODE_PLAYDATA1:

		memcpy(&PlayData, pData->Buff, sizeof(smPLAYDATA));

		pX = PlayData.x;
		pY = PlayData.y;
		pZ = PlayData.z;

		Angle.x = PlayData.angle[0] & ANGCLIP;
		Angle.y = PlayData.angle[1] & ANGCLIP;
		Angle.z = PlayData.angle[2] & ANGCLIP;
		act = PlayData.angle[3];

		if (act != action)
			frame = PlayData.frame;

		action = act;

		PlayBuffCnt = PlayBuffPosi_End;
		MoveCnt = 0;

		dwTarget = 0;
		break;

	case OpCode::OPCODE_PLAYDATA2:

		LastBuffPosi_End = PlayBuffPosi_End;
		memcpy(&PlayData2, pData->Buff, sizeof(smPLAYDATA2));
		len = PlayData2.BuffCount[1] - PlayData2.BuffCount[0];
		MakePlayBuffFromRecvData(&PlayData2.PlayBuff[0], &PlayData2.PlayBuff[1], len);
		if ((PlayBuffPosi_End - PlayBuffCnt) > 32) PlayBuffCnt = LastBuffPosi_End;

		dwTarget = PlayData2.dwTarget;
		break;

	case OpCode::OPCODE_PLAYDATA3:

		LastBuffPosi_End = PlayBuffPosi_End;
		memcpy(&PlayData3, pData->Buff, sizeof(smPLAYDATA3));
		len = PlayData3.BuffCount[2] - PlayData3.BuffCount[0];
		MakePlayBuffFromRecvData(&PlayData3.PlayBuff[0], &PlayData3.PlayBuff[2], len);
		len = PlayData3.BuffCount[1] - PlayData3.BuffCount[2];
		MakePlayBuffFromRecvData(&PlayData3.PlayBuff[2], &PlayData3.PlayBuff[1], len);
		if ((PlayBuffPosi_End - PlayBuffCnt) > 32) PlayBuffCnt = LastBuffPosi_End;

		dwTarget = PlayData3.dwTarget;
		break;

	case OpCode::OPCODE_TRANSPLAYDATA:


		smTRANS_PLAYDATA	*lpTransPlayData;
		smTRANS_PLAYBUFF	*lpTransPlayBuff;
		smTRANS_PLAYBUFF	*lpTransPlayBuff2;

		lpTransPlayData = (smTRANS_PLAYDATA *)pData->Buff;
		lpTransPlayBuff = (smTRANS_PLAYBUFF *)(pData->Buff + sizeof(smTRANS_PLAYDATA));

		LastBuffPosi_End = PlayBuffPosi_End;

		smCharInfo.Life[0] = lpTransPlayData->Hp[0];

		for (cnt = 0; cnt < lpTransPlayData->PlayBuffCnt - 1; cnt++)
		{
			lpTransPlayBuff2 = lpTransPlayBuff + 1;

			len = lpTransPlayBuff2->BuffCount - lpTransPlayBuff->BuffCount;
			MakePlayBuffFromRecvData(&lpTransPlayBuff->PlayBuff, &lpTransPlayBuff2->PlayBuff, len);

			lpTransPlayBuff++;
		}

		dwTarget = lpTransPlayData->dwTarget;
		break;

	case OpCode::OPCODE_ATTACKDATA2:
	case OpCode::OPCODE_ATTACKDATA:

		AttackRecvCountUp();

		Record_TotalRecvDamageCount++;

		if (((TRANS_ATTACKDATA *)pData->Buff)->AttackState == 0x80)
		{
			memcpy(&AttackTrans, (TRANS_ATTACKDATA *)pData->Buff, sizeof(TRANS_ATTACKDATA));
			XorAttackTrans();
			if (PkMode_CharState || (lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->FieldCode == rsCASTLE_FIELD))
				PlayAttack(TRUE);
			else
				PlayAttack();
			break;
		}

		if (AttackTrans.code^GetAttackTrans_XorCode())
		{
			PlayAttack(TRUE);
		}

		memcpy(&AttackTrans, (TRANS_ATTACKDATA *)pData->Buff, sizeof(TRANS_ATTACKDATA));
		XorAttackTrans();



		break;
	}

	TransSendWait = 0;
	dwLastTransTime = dwPlayTime;




	return TRUE;
}


int smCHAR::SendPlayData(smCHAR *player)
{
	int SendTime;
	smPLAYDATA PlayData;
	smPLAYDATA2 PlayData2;
	smPLAYDATA3 PlayData3;
	int PlayerBuffCnt;
	int cnt;
	int StartPosi;
	int BuffPosi;
	int mAction;
	int SendMode;



	SendTime = PlayCounter - TransLastSendCnt;

	if (TransSendWait == 0 && SendTime >= TransMinCnt)
	{


		if (lpCharMsTrace && lpCharMsTrace == this)
		{
			PlayData2.dwTarget = TRUE;
			PlayData3.dwTarget = TRUE;
		}
		else
		{
			PlayData2.dwTarget = FALSE;
			PlayData3.dwTarget = FALSE;
		}

		if (TransLevel > 1)
		{

			PlayData.size = sizeof(smPLAYDATA);
			PlayData.code = OpCode::OPCODE_PLAYDATA1;
			PlayData.x = player->pX;
			PlayData.y = player->pY;
			PlayData.z = player->pZ;

			PlayData.angle[0] = player->Angle.x;
			PlayData.angle[1] = player->Angle.y;
			PlayData.angle[2] = player->Angle.z;
			PlayData.angle[3] = player->action;

			PlayData.frame = player->frame;

			if (TransSock->Send((char *)&PlayData, sizeof(smPLAYDATA)))
			{
				TransSendWait = 1;
				TransLastSendCnt = PlayCounter;
				TransLastSendTime = SendTime;
				SetDistSendCnt(player);
			}
		}
		else
		{

			SendMode = 0;
			PlayerBuffCnt = player->PlayBuffCnt&PLAYBUFF_MASK;
			StartPosi = (PlayerBuffCnt - SendTime) & PLAYBUFF_MASK;

			mAction = player->PlayBuff[PlayerBuffCnt].angle[3];

			for (cnt = SendTime; cnt >= 0; cnt--)
			{
				BuffPosi = (StartPosi + cnt) & PLAYBUFF_MASK;
				if (player->PlayBuff[BuffPosi].angle[3] != mAction)
				{
					SendMode = 1;
					memcpy(&PlayData3.PlayBuff[2], &player->PlayBuff[BuffPosi], sizeof(smPLAYBUFF));
					PlayData3.BuffCount[2] = cnt;
					break;
				}
			}

			if (!SendMode)
			{
				memcpy(&PlayData2.PlayBuff[0], &player->PlayBuff[StartPosi], sizeof(smPLAYBUFF));
				memcpy(&PlayData2.PlayBuff[1], &player->PlayBuff[PlayerBuffCnt], sizeof(smPLAYBUFF));
				PlayData2.code = OpCode::OPCODE_PLAYDATA2;
				PlayData2.size = sizeof(smPLAYDATA2);
				PlayData2.BuffCount[0] = 0;
				PlayData2.BuffCount[1] = SendTime;

				if (TransSock->Send((char *)&PlayData2, sizeof(smPLAYDATA2)))
				{
					TransSendWait = 1;
					TransLastSendCnt = PlayCounter;
					TransLastSendTime = SendTime;
					SetDistSendCnt(player);
				}
			}
			else
			{
				memcpy(&PlayData3.PlayBuff[0], &player->PlayBuff[StartPosi], sizeof(smPLAYBUFF));
				memcpy(&PlayData3.PlayBuff[1], &player->PlayBuff[PlayerBuffCnt], sizeof(smPLAYBUFF));
				PlayData3.code = OpCode::OPCODE_PLAYDATA3;
				PlayData3.size = sizeof(smPLAYDATA3);
				PlayData3.BuffCount[0] = 0;
				PlayData3.BuffCount[1] = SendTime;

				if (TransSock->Send((char *)&PlayData3, sizeof(smPLAYDATA3)))
				{
					TransSendWait = 1;
					TransLastSendCnt = PlayCounter;
					TransLastSendTime = SendTime;
					SetDistSendCnt(player);
				}
			}
		}
	}

	return TRUE;
}


int smCHAR::MakeTransPlayData(char *lpTargetBuff, int SendTime, int pBuffStep)
{
	smTRANS_PLAYDATA	*lpTransPlayData;
	smTRANS_PLAYBUFF	*lpTransPlayBuff;
	smEFFECT_ITEM		*lpEffectItem;

	int StartPosi;
	int BuffPosi;
	int BuffPosi_Old;
	int mAction;
	int mFrameSelect;
	DWORD mFrame;
	int	Life;



	int	buffCnt;
	int cnt;
	int LastCnt;
	int	SameAction;

	lpTransPlayData = (smTRANS_PLAYDATA *)lpTargetBuff;
	lpTransPlayBuff = (smTRANS_PLAYBUFF *)(lpTargetBuff + sizeof(smTRANS_PLAYDATA));

	lpTransPlayData->code = OpCode::OPCODE_TRANSPLAYDATA;
	lpTransPlayData->dwObjectSerial = dwObjectSerial;
	lpTransPlayData->dwTarget = 0;
	lpTransPlayData->StartPosi = PlayBuffCnt - SendTime;
	if (this == lpCurPlayer)
	{
		if (MotionInfo && MotionInfo->State == CHRMOTION_STATE_DEAD)
			lpTransPlayData->Hp[0] = 0;
		else
			lpTransPlayData->Hp[0] = sinGetLife();
	}
	else
	{
		lpTransPlayData->Hp[0] = smCharInfo.Life[0];
	}
	lpTransPlayData->Hp[1] = smCharInfo.Life[1];

	if (UseObject_VirtualLife)
	{
		lpTransPlayData->Hp[0] = sObject_DisplayLife[0];
		lpTransPlayData->Hp[1] = sObject_DisplayLife[1];
	}



	if (smCharInfo.State == smCHAR_STATE_ENEMY)
		lpTransPlayData->dwAutoCharCode = smMonsterInfo.dwAutoCharCode;
	else
		lpTransPlayData->dwAutoCharCode = 0;

	smCharInfo.bUpdateInfo[1] = sinSkill.SkillPoint;

	lpTransPlayData->bUpdateInfo[0] = smCharInfo.bUpdateInfo[0];
	lpTransPlayData->bUpdateInfo[1] = smCharInfo.bUpdateInfo[1];
	lpTransPlayData->bUpdateInfo[2] = 0;
	lpTransPlayData->bUpdateInfo[3] = 0;


	int	MainArea, SubArea;

	if (lpCurPlayer && lpCurPlayer->OnStageField >= 0)
	{
		MainArea = (lpCurPlayer->OnStageField) & 1;
		SubArea = (lpCurPlayer->OnStageField + 1) & 1;
	}
	else
	{
		MainArea = 0;
		SubArea = 0;
	}


	if (StageField[0])
		lpTransPlayData->wArea[0] = StageField[MainArea]->FieldCode;
	else
		lpTransPlayData->wArea[0] = -1;

	if (StageField[1])
		lpTransPlayData->wArea[1] = StageField[SubArea]->FieldCode;
	else
		lpTransPlayData->wArea[1] = -1;

	lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_LEVEL] = smCharInfo.Level;
	lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_POTION] = (PotionLog & 0x0F) | ((AttackCritcal & 0xF) << 4);
	lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_EXT] = 0;
	lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_SKIL] = (BYTE)dwDispAppSkill;







	StartPosi = (lpTransPlayData->StartPosi) & PLAYBUFF_MASK;

	buffCnt = 0;


	mAction = PlayBuff[StartPosi].angle[3];
	mFrame = PlayBuff[StartPosi].frame;
	memcpy(&lpTransPlayBuff->PlayBuff, &PlayBuff[StartPosi], sizeof(smPLAYBUFF));
	lpTransPlayBuff->BuffCount = 0;
	lpTransPlayBuff++;
	buffCnt++;
	LastCnt = 0;
	BuffPosi_Old = StartPosi;
	mFrameSelect = PlayBuff[StartPosi].frame >> CHAR_FRAME_SELSHIFT;

	SameAction = TRUE;

	for (cnt = 1; cnt < SendTime - 1; cnt++)
	{
		BuffPosi = (StartPosi + cnt) & PLAYBUFF_MASK;

		if (PlayBuff[BuffPosi].angle[3] != mAction) SameAction = FALSE;

		if (PlayBuff[BuffPosi].frame < mFrame || PlayBuff[BuffPosi].angle[3] != mAction || mFrameSelect != (int)(PlayBuff[BuffPosi].frame >> CHAR_FRAME_SELSHIFT))
		{


			mAction = PlayBuff[BuffPosi_Old].angle[3];
			memcpy(&lpTransPlayBuff->PlayBuff, &PlayBuff[BuffPosi_Old], sizeof(smPLAYBUFF));
			lpTransPlayBuff->BuffCount = (cnt*pBuffStep) - 1;
			lpTransPlayBuff++;
			buffCnt++;



			mAction = PlayBuff[BuffPosi].angle[3];
			mFrame = PlayBuff[BuffPosi].frame;
			memcpy(&lpTransPlayBuff->PlayBuff, &PlayBuff[BuffPosi], sizeof(smPLAYBUFF));
			lpTransPlayBuff->BuffCount = cnt * pBuffStep;
			lpTransPlayBuff++;
			buffCnt++;
			LastCnt = cnt;
			mFrameSelect = PlayBuff[BuffPosi].frame >> CHAR_FRAME_SELSHIFT;
		}

		BuffPosi_Old = BuffPosi;
	}

	BuffPosi = (StartPosi + SendTime - 1) & PLAYBUFF_MASK;


	mAction = PlayBuff[BuffPosi].angle[3];
	memcpy(&lpTransPlayBuff->PlayBuff, &PlayBuff[BuffPosi], sizeof(smPLAYBUFF));
	lpTransPlayBuff->BuffCount = (SendTime*pBuffStep) - 1;
	lpTransPlayBuff++;
	buffCnt++;

	lpTransPlayData->StartPosi = (lpTransPlayData->StartPosi*pBuffStep)&PLAYBUFF_MASK;

	if (SameAction == TRUE && smCharInfo.State == smCHAR_STATE_USER && MotionInfo->State == CHRMOTION_STATE_STAND)
		buffCnt = 1;

	lpTransPlayData->PlayBuffCnt = buffCnt;
	lpTransPlayData->size = sizeof(smTRANS_PLAYDATA) + (sizeof(smTRANS_PLAYBUFF)*buffCnt);




	MotionRecordCount++;





	lpEffectItem = (smEFFECT_ITEM *)(lpTargetBuff + lpTransPlayData->size);

	if (HvLeftHand.PatTool && HvLeftHand.dwItemCode && (HvLeftHand.ColorBlink || HvLeftHand.DispEffect))
	{

		lpEffectItem->code = OpCode::OPCODE_EFFECT_ITEM;
		lpEffectItem->size = sizeof(smEFFECT_ITEM);
		lpEffectItem->dwItemCode = HvLeftHand.dwItemCode;
		lpEffectItem->ColorBlink = HvLeftHand.ColorBlink;
		memcpy(lpEffectItem->sColors, HvLeftHand.sColors, sizeof(short) * 4);
		lpEffectItem->DispEffect = HvLeftHand.DispEffect;
		lpEffectItem->BlinkScale = HvLeftHand.BlinkScale;


		lpTransPlayData->size += lpEffectItem->size;
		lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_EXT] ++;
		lpEffectItem++;
	}

	if (HvRightHand.PatTool && HvRightHand.dwItemCode && (HvRightHand.ColorBlink || HvRightHand.DispEffect))
	{

		lpEffectItem->code = OpCode::OPCODE_EFFECT_ITEM;
		lpEffectItem->size = sizeof(smEFFECT_ITEM);
		lpEffectItem->dwItemCode = HvRightHand.dwItemCode;
		lpEffectItem->ColorBlink = HvRightHand.ColorBlink;
		memcpy(lpEffectItem->sColors, HvRightHand.sColors, sizeof(short) * 4);
		lpEffectItem->DispEffect = HvRightHand.DispEffect;
		lpEffectItem->BlinkScale = HvRightHand.BlinkScale;

		lpTransPlayData->size += lpEffectItem->size;
		lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_EXT] ++;
		lpEffectItem++;
	}

	if (dwWeaponEffectTime)
	{

		lpEffectItem->code = OpCode::OPCODE_EFFECT_WEAPON;
		lpEffectItem->size = sizeof(smEFFECT_ITEM);
		lpEffectItem->dwItemCode = WeaponEffect;
		lpEffectItem->ColorBlink = (dwWeaponEffectTime - dwPlayTime) + 500;
		ZeroMemory(lpEffectItem->sColors, sizeof(short) * 4);
		lpEffectItem->DispEffect = EnchantEffect_Point;
		lpEffectItem->BlinkScale = 0;

		lpTransPlayData->size += lpEffectItem->size;
		lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_EXT] ++;
		lpEffectItem++;
	}

	if (this == lpCurPlayer)
		Life = sinGetLife();
	else
		Life = smCharInfo.Life[0];

	if (PlayStunCount && Life > 0)
	{
		lpEffectItem->code = OpCode::OPCODE_EFFECT_STUN;
		lpEffectItem->size = sizeof(smEFFECT_ITEM);
		lpEffectItem->dwItemCode = PlayStunCount;
		lpEffectItem->ColorBlink = PlayStunType;
		ZeroMemory(lpEffectItem->sColors, sizeof(short) * 4);
		lpEffectItem->DispEffect = 0;
		lpEffectItem->BlinkScale = 0;

		lpTransPlayData->size += lpEffectItem->size;
		lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_EXT] ++;
		lpEffectItem++;
	}

	if (PlayHolyPower[1] && Life > 0)
	{
		lpEffectItem->code = OpCode::OPCODE_EFFECT_CURSE;
		lpEffectItem->size = sizeof(smEFFECT_ITEM);
		lpEffectItem->dwItemCode = PlayHolyPower[1];
		lpEffectItem->ColorBlink = 0;
		ZeroMemory(lpEffectItem->sColors, sizeof(short) * 4);
		lpEffectItem->DispEffect = 0;
		lpEffectItem->BlinkScale = 0;

		lpTransPlayData->size += lpEffectItem->size;
		lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_EXT] ++;
		lpEffectItem++;
	}


	if (PlayCurseLazy && Life > 0) {
		lpEffectItem->code = OpCode::OPCODE_EFFECT_CURSELAZY;
		lpEffectItem->size = sizeof(smEFFECT_ITEM);
		lpEffectItem->dwItemCode = PlayCurseLazy;
		lpEffectItem->ColorBlink = 0;
		ZeroMemory(lpEffectItem->sColors, sizeof(short) * 4);
		lpEffectItem->DispEffect = 0;
		lpEffectItem->BlinkScale = 0;

		lpTransPlayData->size += lpEffectItem->size;
		lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_EXT] ++;
		lpEffectItem++;
	}

	if (PlaySlowCount > 0 && Life > 0)
	{
		if (smCharInfo.State != smCHAR_STATE_USER || AttackIce || PlayDistortion)
		{
			lpEffectItem->code = OpCode::OPCODE_EFFECT_ICE;
			lpEffectItem->size = sizeof(smEFFECT_ITEM);
			lpEffectItem->dwItemCode = PlaySlowCount;
			lpEffectItem->ColorBlink = PlayDistortion;
			ZeroMemory(lpEffectItem->sColors, sizeof(short) * 4);
			lpEffectItem->DispEffect = 0;
			lpEffectItem->BlinkScale = 0;

			lpTransPlayData->size += lpEffectItem->size;
			lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_EXT] ++;
			lpEffectItem++;
		}
	}

	if (PlayPoison[1] && Life > 0)
	{
		lpEffectItem->code = OpCode::OPCODE_EFFECT_POISION;
		lpEffectItem->size = sizeof(smEFFECT_ITEM);
		lpEffectItem->dwItemCode = PlayPoison[0];
		lpEffectItem->ColorBlink = 0;
		ZeroMemory(lpEffectItem->sColors, sizeof(short) * 4);
		lpEffectItem->DispEffect = 0;
		lpEffectItem->BlinkScale = 0;

		lpTransPlayData->size += lpEffectItem->size;
		lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_EXT] ++;
		lpEffectItem++;
	}

	if (PlayCurseQuest && Life > 0)
	{
		lpEffectItem->code = OpCode::OPCODE_EFFECT_CURSE_QUEST;
		lpEffectItem->size = sizeof(smEFFECT_ITEM);
		lpEffectItem->dwItemCode = PlayCurseQuest;
		lpEffectItem->ColorBlink = 0;
		ZeroMemory(lpEffectItem->sColors, sizeof(short) * 4);
		lpEffectItem->DispEffect = 0;
		lpEffectItem->BlinkScale = 0;

		lpTransPlayData->size += lpEffectItem->size;
		lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_EXT] ++;
		lpEffectItem++;
	}

	if (PlayVanish > 0 && Life > 0)
	{
		lpEffectItem->code = OpCode::OPCODE_EFFECT_VANISH;
		lpEffectItem->size = sizeof(smEFFECT_ITEM);
		lpEffectItem->dwItemCode = PlayVanish;
		lpEffectItem->ColorBlink = PlayVague;
		ZeroMemory(lpEffectItem->sColors, sizeof(short) * 4);
		lpEffectItem->DispEffect = 0;
		lpEffectItem->BlinkScale = 0;

		lpTransPlayData->size += lpEffectItem->size;
		lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_EXT] ++;
		lpEffectItem++;
	}

	if (dwForceOfNatureTime > dwPlayTime)
	{
		lpEffectItem->code = OpCode::OPCODE_EFFECT_KEEPSKILL;
		lpEffectItem->size = sizeof(smEFFECT_ITEM);
		lpEffectItem->dwItemCode = SKILL_PLAY_FORCE_OF_NATURE;
		lpEffectItem->ColorBlink = dwForceOfNatureTime - dwPlayTime;
		ZeroMemory(lpEffectItem->sColors, sizeof(short) * 4);
		lpEffectItem->DispEffect = 0;
		lpEffectItem->BlinkScale = 0;

		lpTransPlayData->size += lpEffectItem->size;
		lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_EXT] ++;
		lpEffectItem++;
	}

	if (dwHallOfValhallaTime > dwPlayTime)
	{
		lpEffectItem->code = OpCode::OPCODE_EFFECT_KEEPSKILL;
		lpEffectItem->size = sizeof(smEFFECT_ITEM);
		lpEffectItem->dwItemCode = SKILL_PLAY_HALL_OF_VALHALLA;
		lpEffectItem->ColorBlink = dwHallOfValhallaTime - dwPlayTime;
		ZeroMemory(lpEffectItem->sColors, sizeof(short) * 4);
		lpEffectItem->DispEffect = 0;
		lpEffectItem->BlinkScale = 0;

		lpTransPlayData->size += lpEffectItem->size;
		lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_EXT] ++;
		lpEffectItem++;
	}

	if (PlayInvincible > 0)
	{
		lpEffectItem->code = OpCode::OPCODE_EFFECT_KEEPSKILL;
		lpEffectItem->size = sizeof(smEFFECT_ITEM);
		lpEffectItem->dwItemCode = SKILL_PLAY_BLESS_SIEGE_ITEM;
		lpEffectItem->ColorBlink = PlayInvincible;
		ZeroMemory(lpEffectItem->sColors, sizeof(short) * 4);
		lpEffectItem->DispEffect = 0;
		lpEffectItem->BlinkScale = 0;

		lpTransPlayData->size += lpEffectItem->size;
		lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_EXT] ++;
		lpEffectItem++;
	}


	if (dwTradeMsgCode)
	{
		lpEffectItem->code = OpCode::OPCODE_EFFECT_PERSHOP;
		lpEffectItem->size = sizeof(smEFFECT_ITEM);
		lpEffectItem->dwItemCode = dwTradeMsgCode;
		lpEffectItem->ColorBlink = 0;
		ZeroMemory(lpEffectItem->sColors, sizeof(short) * 4);
		lpEffectItem->DispEffect = 0;
		lpEffectItem->BlinkScale = 0;

		lpTransPlayData->size += lpEffectItem->size;
		lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_EXT] ++;
		lpEffectItem++;
	}

	if (dwForceOrbTime && dwForceOrbTime > dwPlayTime)
	{
		lpEffectItem->code = OpCode::OPCODE_EFFECT_FORCEORB;
		lpEffectItem->size = sizeof(smEFFECT_ITEM);
		lpEffectItem->dwItemCode = dwForceOrbCode;
		lpEffectItem->ColorBlink = dwPlayTime - dwForceOrbTime;
		ZeroMemory(lpEffectItem->sColors, sizeof(short) * 4);
		lpEffectItem->DispEffect = 0;
		lpEffectItem->BlinkScale = 0;

		lpTransPlayData->size += lpEffectItem->size;
		lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_EXT] ++;
		lpEffectItem++;
	}

	if (cHelpPet.PetShow)
	{
		lpEffectItem->code = OpCode::OPCODE_EFFECT_LOWPET;
		lpEffectItem->size = sizeof(smEFFECT_ITEM);
		lpEffectItem->dwItemCode = cHelpPet.PetKind;
		lpEffectItem->ColorBlink = g_LowLevelPetAttackSerial;
		ZeroMemory(lpEffectItem->sColors, sizeof(short) * 4);
		lpEffectItem->DispEffect = 0;
		lpEffectItem->BlinkScale = 0;

		lpTransPlayData->size += lpEffectItem->size;
		lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_EXT] ++;
		lpEffectItem++;

		if (g_LowLevelPetAttackSerial) g_LowLevelPetAttackSerial = 0;
	}



	if (cPCBANGPet.PetShow)
	{
		lpEffectItem->code = OpCode::OPCODE_EFFECT_PCBANGPET;
		lpEffectItem->size = sizeof(smEFFECT_ITEM);
		lpEffectItem->dwItemCode = cPCBANGPet.PetKind;
		lpEffectItem->ColorBlink = g_HoPCBangPetAttackSerial;
		ZeroMemory(lpEffectItem->sColors, sizeof(short) * 4);
		lpEffectItem->DispEffect = 0;
		lpEffectItem->BlinkScale = 0;

		lpTransPlayData->size += lpEffectItem->size;
		lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_EXT] ++;
		lpEffectItem++;

		if (g_HoPCBangPetAttackSerial) g_HoPCBangPetAttackSerial = 0;
	}

	if (dwClanManageBit)
	{
		lpEffectItem->code = OpCode::OPCODE_EFFECT_CLANMGR;
		lpEffectItem->size = sizeof(smEFFECT_ITEM);
		lpEffectItem->dwItemCode = dwClanManageBit;
		lpEffectItem->ColorBlink = BlessCrown;
		ZeroMemory(lpEffectItem->sColors, sizeof(short) * 4);
		lpEffectItem->DispEffect = 0;
		lpEffectItem->BlinkScale = 0;

		lpTransPlayData->size += lpEffectItem->size;
		lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_EXT] ++;
		lpEffectItem++;
	}

#ifndef _W_SERVER
	if (OnStageField >= 0 && StageField[OnStageField]->State == FIELD_STATE_CASTLE)
	{

		if (sBlessCastle_Damage[0] || sBlessCastle_Damage[1])
		{
			lpEffectItem->code = OpCode::OPCODE_EFFECT_BLESS_SCORE;
			lpEffectItem->size = sizeof(smEFFECT_ITEM);
			lpEffectItem->dwItemCode = 0;
			lpEffectItem->ColorBlink = 0;
			lpEffectItem->sColors[0] = sBlessCastle_Damage[0];
			lpEffectItem->sColors[1] = sBlessCastle_Damage[1];
			lpEffectItem->sColors[2] = 0;
			lpEffectItem->sColors[3] = 0;
			lpEffectItem->DispEffect = 0;
			lpEffectItem->BlinkScale = 0;

			lpTransPlayData->size += lpEffectItem->size;
			lpTransPlayData->bEventInfo[TRANS_PLAYDATA_EVENT_EXT] ++;
			lpEffectItem++;
	}
}

#endif

	srTransBuffSize = lpTransPlayData->size;

	return TRUE;
}


int smCHAR::SetTransEffectItems(smEFFECT_ITEM *lpEffectItem)
{
	if (HvRightHand.PatTool && HvRightHand.dwItemCode == lpEffectItem->dwItemCode)
	{
		HvRightHand.ColorBlink = lpEffectItem->ColorBlink;
		memcpy(HvRightHand.sColors, lpEffectItem->sColors, sizeof(short) * 4);
		HvRightHand.DispEffect = lpEffectItem->DispEffect;
		HvRightHand.BlinkScale = lpEffectItem->BlinkScale;


		GetItemKindFromBliankColor(&HvRightHand);
		if (HvRightHand.DispEffect) AssaParticle_ClassUpWeapon(this);

	}

	if (HvLeftHand.PatTool && HvLeftHand.dwItemCode == lpEffectItem->dwItemCode)
	{
		HvLeftHand.ColorBlink = lpEffectItem->ColorBlink;
		memcpy(HvLeftHand.sColors, lpEffectItem->sColors, sizeof(short) * 4);
		HvLeftHand.DispEffect = lpEffectItem->DispEffect;
		HvLeftHand.BlinkScale = lpEffectItem->BlinkScale;


		GetItemKindFromBliankColor(&HvLeftHand);
		if (HvLeftHand.DispEffect) AssaParticle_ClassUpWeapon(this);
	}

	return TRUE;
}


int smCHAR::SetTransEffectWeapon(smEFFECT_ITEM *lpEffectItem)
{
	int	time;

	if (dwWeaponEffectTime && WeaponEffect == lpEffectItem->dwItemCode)
	{
		time = abs((long)dwWeaponEffectTime - (long)dwPlayTime);
		if (abs(time - lpEffectItem->ColorBlink) > 6000)
		{
			switch (lpEffectItem->dwItemCode)
			{
			case (sITEMINFO_FIRE + 1):
				AssaParticle_EnchantWeaponFireMember(this, lpEffectItem->ColorBlink / 1000);
				break;
			case (sITEMINFO_ICE + 1):
				AssaParticle_EnchantWeaponIceMember(this, lpEffectItem->ColorBlink / 1000);
				break;
			case (sITEMINFO_LIGHTING + 1):
				AssaParticle_EnchantWeaponLightMember(this, lpEffectItem->ColorBlink / 1000);
				break;
			}
			dwWeaponEffectTime = dwPlayTime + lpEffectItem->ColorBlink;
			EnchantEffect_Point = lpEffectItem->DispEffect;
		}
	}
	else
	{
		switch (lpEffectItem->dwItemCode)
		{
		case (sITEMINFO_FIRE + 1):
			AssaParticle_EnchantWeaponFireMember(this, lpEffectItem->ColorBlink / 1000);
			break;
		case (sITEMINFO_ICE + 1):
			AssaParticle_EnchantWeaponIceMember(this, lpEffectItem->ColorBlink / 1000);
			break;
		case (sITEMINFO_LIGHTING + 1):
			AssaParticle_EnchantWeaponLightMember(this, lpEffectItem->ColorBlink / 1000);
			break;
		}
		WeaponEffect = lpEffectItem->dwItemCode;
		dwWeaponEffectTime = dwPlayTime + lpEffectItem->ColorBlink;
		EnchantEffect_Point = lpEffectItem->DispEffect;
	}

	return TRUE;
}


int smCHAR::SendPlayDataSock(smWINSOCK *lpsmsock, char *lpTransBuff, int ex, int ey, int ez)
{
	int SendTime;
	smPLAYDATA PlayData;
	int dist;
	int x, y, z;




	if ((PlayBuffCnt & 0x3F) != 0) return FALSE;

	SendTime = 0x40;

	x = (pX - ex) >> FLOATNS;
	y = (pY - ey) >> FLOATNS;
	z = (pZ - ez) >> FLOATNS;

	dist = x * x + y * y + z * z;

	TransLevel = 3;

	if (dist < DIST_TRANSLEVEL_HIGH || !DisplayFlag)
	{
		TransLevel = 0;
	}
	else
	{
		if (dist < DIST_TRANSLEVEL_MID)
		{
			TransLevel = 1;
		}
		else
		{
			if (dist < DIST_TRANSLEVEL_LOW)
			{
				TransLevel = 2;
			}
		}
	}

	if (TransLevel > 1)
	{

		if ((PlayBuffCnt & 0xFF) != 0) return FALSE;

		PlayData.size = sizeof(smPLAYDATA);
		PlayData.code = OpCode::OPCODE_PLAYDATA1;
		PlayData.x = pX;
		PlayData.y = pY;
		PlayData.z = pZ;

		PlayData.angle[0] = Angle.x;
		PlayData.angle[1] = Angle.y;
		PlayData.angle[2] = Angle.z;
		PlayData.angle[3] = action;

		PlayData.frame = frame;
		PlayData.dwObjectSerial = dwObjectSerial;

		if (lpsmsock->Send((char *)&PlayData, sizeof(smPLAYDATA), TRUE))
		{

		}
	}
	else
	{






		if (lpsmsock->Send(lpTransBuff, ((smTRANS_PLAYDATA *)lpTransBuff)->size), TRUE)
		{




		}

	}


	return TRUE;
}


int smCHAR::SendCharInfo(smWINSOCK *lpsmsock)
{

	smTRNAS_PLAYERINFO	TransPlayerInfo;

	memcpy(&TransPlayerInfo.smCharInfo, &smCharInfo, sizeof(smCHAR_INFO));
	TransPlayerInfo.size = sizeof(smTRNAS_PLAYERINFO);
	TransPlayerInfo.code = OpCode::OPCODE_PLAYERINFO;
	TransPlayerInfo.dwObjectSerial = dwObjectSerial;

	TransPlayerInfo.x = pX;
	TransPlayerInfo.y = pY;
	TransPlayerInfo.z = pZ;

	return lpsmsock->Send((char *)&TransPlayerInfo, TransPlayerInfo.size, TRUE);
}


int smCHAR::BeginSkill(int SkilCode, int Level, smCHAR *lpTarChar, int x, int y, int z)
{
	int point;
	int param;
	POINT3D pos;
	int cnt;
	POINT3D	Pos1, Pos2;

	if (smCharInfo.State == smCHAR_STATE_ENEMY && PkMode_CharState != smCHAR_STATE_USER)
	{
		return BeginSkill_Monster();
	}

	AttackEffect = 0;

	point = (SkilCode >> 8) & 0xF;
	param = (SkilCode >> 12) & 0xF;

	switch (SkilCode & 0xFF)
	{

	case SKILL_PLAY_EXTREME_SHIELD:
		SkillPlaySound(SKILL_SOUND_EXTREME_SHIELD, pX, pY, pZ);
		break;

	case SKILL_PLAY_MECHANIC_BOMB:



		HideWeapon = TRUE;
		break;

	case SKILL_PLAY_PHYSICAL_ABSORB:

		dwDispAppSkill |= SKILL_APPMASK_PHYSICAL_ABSORB;
		StartSkill(pX, pY, pZ, 0, Angle.y, 0, SKILL_PHYSICAL_ABSORB);
		StartSkill(pX, pY, pZ, 0, Angle.y, 0, this, SKILL_SHIELD1, point);
		SkillPlaySound(SKILL_SOUND_PHYSICAL_ABSORB1, pX, pY, pZ);

		break;

	case SKILL_PLAY_POISON_ATTRIBUTE:

		StartSkill(pX, pY, pZ, 0, Angle.y, 0, SKILL_UP1);
		SetMotionFromCode(CHRMOTION_STATE_ATTACK);
		break;


	case SKILL_PLAY_RAVING:
	case SKILL_PLAY_IMPACT:

		AttackEffect = TRUE;
		break;

	case SKILL_PLAY_PIKEWIND:

		break;

	case SKILL_PLAY_JUMPING_CRASH:

		AttackEffect = TRUE;
		SkillPlaySound(SKILL_SOUND_JUMPING_CRASH1, pX, pY, pZ);
		break;

	case SKILL_PLAY_SCOUT_HAWK:

		if (HoSkillCode)
		{

			HoSkillCode = 0;
			EffectMgr.Main();
		}

		StartSkill(pX, pY, pZ, 0, Angle.y, 0, this, SKILL_SCOUT_HAWK, point);
		SkillPlaySound(SKILL_SOUND_SCOUT_HAWK1, pX, pY, pZ);
		SkillPlaySound(SKILL_SOUND_SCOUT_HAWK2, pX, pY, pZ);
		HideWeapon = TRUE;
		break;

	case SKILL_PLAY_WIND_ARROW:
		break;

	case SKILL_PLAY_PERFECT_AIM:
		break;

	case SKILL_PLAY_MAXIMIZE:

		dwDispAppSkill |= SKILL_APPMASK_AUTOMATION;
		StartSkill(pX, pY, pZ, Angle.x, Angle.y, Angle.z, SKILL_MAXIMIZE);
		StartSkill(pX, pY, pZ, 0, Angle.y, 0, this, SKILL_SHIELD2, point);
		SkillPlaySound(SKILL_SOUND_SKILL_MAXIMIZE1, pX, pY, pZ);
		break;

	case SKILL_PLAY_AUTOMATION:

		dwDispAppSkill |= SKILL_APPMASK_AUTOMATION;
		StartSkill(pX, pY, pZ, Angle.x, Angle.y, Angle.z, SKILL_AUTOMATION);
		StartSkill(pX, pY, pZ, 0, Angle.y, 0, this, SKILL_SHIELD2, point);
		SkillPlaySound(SKILL_SOUND_SKILL_AUTOMATION1, pX, pY, pZ);
		break;

	case SKILL_PLAY_SPARK:

		HideWeapon = TRUE;
		SkillPlaySound(SKILL_SOUND_SKILL_SPARK1, pX, pY, pZ);
		break;


	case SKILL_PLAY_METAL_ARMOR:

		AssaParticle_MetalArmor(this, Metal_Armor_Time[point - 1]);
		SkillPlaySound(SKILL_SOUND_SKILL_METAL_ARMOR, pX, pY, pZ);
		break;

	case SKILL_PLAY_SPARK_SHIELD:

		SkillPlaySound(SKILL_SOUND_SKILL_SPARK1, pX, pY, pZ);
		break;






	case SKILL_PLAY_GROUND_PIKE:




		break;

	case SKILL_PLAY_TORNADO:


		break;

	case SKILL_PLAY_EXPANSION:
		SkillPlaySound(SKILL_SOUND_SKILL_EXPANSION1, pX, pY, pZ);
		break;

	case SKILL_PLAY_VENOM_SPEAR:
		AssaParticle_VeonmSpearPike(this);
		SkillPlaySound(SKILL_SOUND_JUMPING_CRASH1, pX, pY, pZ);
		break;

	case SKILL_PLAY_CHAIN_LANCE:

		break;

	case SKILL_PLAY_VANISH:
		AssaParticle_Vanish(this);
		SkillPlaySound(SKILL_SOUND_SKILL_VANISH1, pX, pY, pZ);
		break;


	case SKILL_PLAY_FALCON:

		if (HoSkillCode)
		{

			HoSkillCode = 0;
			EffectMgr.Main();
		}

		StartSkill(pX, pY, pZ, 0, 0, 0, this, SKILL_FALCON, point - 1);
		HideWeapon = TRUE;
		SkillPlaySound(SKILL_SOUND_SKILL_FALCON, pX, pY, pZ);
		break;

	case SKILL_PLAY_GOLDEN_FALCON:

		if (HoSkillCode)
		{

			HoSkillCode = 0;
			EffectMgr.Main();
		}

		AssaParticle_GoldenFalcon(this, Golden_Falcon_Time[point - 1]);
		HideWeapon = TRUE;
		SkillPlaySound(SKILL_SOUND_SKILL_GOLDEN_FALCON, pX, pY, pZ);
		break;

	case SKILL_PLAY_RAGEOF_ZECRAM:
		StartSkill(pX, pY + 24 * fONE, pZ, 0, 0, 0, SKILL_RAGE_OF_ZECRAM_POWER1);
		SkillPlaySound(SKILL_SOUND_SKILL_RAGE_OF_ZECRAM3, pX, pY, pZ);
		break;

	case SKILL_PLAY_ROAR:

		StartSkill(pX, pY, pZ, 0, 0, 0, SKILL_ROAR, point);

		if ((dwPlayTime & 1) == 0)
			SkillPlaySound(SKILL_SOUND_SKILL_ROAR1, pX, pY, pZ);
		else
			SkillPlaySound(SKILL_SOUND_SKILL_ROAR2, pX, pY, pZ);

		break;

	case SKILL_PLAY_CONCENTRATION:
		AssaParticle_Concentration(this, Concentration_Time[point - 1]);
		SkillPlaySound(SKILL_SOUND_SKILL_CONCENTRATION1, pX, pY, pZ);
		break;

	case SKILL_PLAY_SWIFT_AXE:
		AssaParticle_SwiftAxe(this, Swift_Axe_Time[point - 1]);
		SkillPlaySound(SKILL_SOUND_SKILL_SWIFT_AXE1, pX, pY, pZ);
		break;


		break;





	case SKILL_PLAY_SWORD_BLAST:
		SkillPlaySound(SKILL_SOUND_SKILL_SWORDBLAST1, pX, pY, pZ);
		break;

	case SKILL_PLAY_BRANDISH:

		SkillPlaySound(SKILL_SOUND_SKILL_BLANDISH1, pX, pY, pZ);
		break;

	case SKILL_PLAY_HOLY_BODY:

		dwDispAppSkill |= SKILL_APPMASK_PHYSICAL_ABSORB;
		sinEffect_Holy_Body(this);
		StartSkill(pX, pY, pZ, 0, Angle.y, 0, this, SKILL_SHIELD1, point);
		SkillPlaySound(SKILL_SOUND_SKILL_HOLYBODY, pX, pY, pZ);
		break;

	case SKILL_PLAY_HOLY_VALOR:
		AssaParticle_HolyValor_Jang(this, Holy_Valor_Time[point - 1]);
		SkillPlaySound(SKILL_SOUND_SKILL_HOLY_VALOR1, pX, pY, pZ);
		break;

	case SKILL_PLAY_PIERCING:

		sinSkillEffect_Piercing(this);
		SkillPlaySound(SKILL_SOUND_SKILL_PIERCING, pX, pY, pZ);
		break;

	case SKILL_PLAY_FLAME_BRANDISH:

		SkillPlaySound(SKILL_SOUND_SKILL_BLANDISH1, pX, pY, pZ);
		break;

	case SKILL_PLAY_DRASTIC_SPIRIT:

		AssaParticle_DrasticSpirit_Jang(this, Drastic_Spirit_Time[point - 1]);
		SkillPlaySound(SKILL_SOUND_SKILL_DRASTICSPIRIT1, pX, pY, pZ);
		break;

	case SKILL_PLAY_DIVINE_INHALATION:

		SkillPlaySound(SKILL_SOUND_SKILL_DIVINE_INHALATION, pX, pY, pZ);
		break;

	case SKILL_PLAY_HOLY_INCANTATION:
		AssaParticle_HolyIncantationHand(this);
		break;


	case SKILL_PLAY_WINDY:

		sinSkillEffect_Windy(this);
		AssaParticle_Windy(this, Windy_Time[point - 1]);
		SkillPlaySound(SKILL_SOUND_SKILL_WINDY1, pX, pY, pZ);
		break;

	case SKILL_PLAY_SPLIT_JAVELIN:
		if (chrAttackTarget && AttackCritcal >= 0 && GetAttackPoint(&x, &y, &z) == TRUE)
		{
			Pos1.x = x;
			Pos1.y = y;
			Pos1.z = z;
			Pos2.x = chrAttackTarget->pX;
			Pos2.y = chrAttackTarget->pY + 28 * fONE;
			Pos2.z = chrAttackTarget->pZ;

			AssaParticle_SplitJavelin(&Pos1, &Pos2, param);
		}

		SkillPlaySound(SKILL_SOUND_SKILL_SPLIT_JAVELIN1, pX, pY, pZ);
		break;

	case SKILL_PLAY_TRIUMPH_OF_VALHALLA:
		SkillPlaySound(SKILL_SOUND_SKILL_TRIUMPH_OF_VALHALLA1, pX, pY, pZ);
		break;



	case SKILL_PLAY_HEALING:
		if (!lpTarChar && this == lpCurPlayer)
		{
			sinEffect_Healing2(this);
			SkillPlaySound(SKILL_SOUND_SKILL_HEALING, pX, pY, pZ);
		}
		else
		{
			if (lpTarChar)
			{
				sinEffect_Healing2(lpTarChar);
				SkillPlaySound(SKILL_SOUND_SKILL_HEALING, lpTarChar->pX, lpTarChar->pY, lpTarChar->pZ);
			}
		}

		SkillPlaySound(SKILL_SOUND_SKILL_CASTING_PRIEST, pX, pY, pZ);

		pos.x = pX;	pos.y = pY;	pos.z = pZ;
		sinEffect_StartMagic(&pos, 1);
		break;

	case SKILL_PLAY_HOLY_MIND:
		if (lpTarChar)
		{
			cnt = lpTarChar->smCharInfo.Resistance[sITEMINFO_BIONIC];
			if (cnt < 0) cnt = 0;
			if (cnt > 100) cnt = 100;
			cnt = (15 * (100 - cnt)) / 100;
			if (cnt > 0)
				AssaParticle_HolyMind_Attack(lpTarChar, cnt);
		}

		SkillPlaySound(SKILL_SOUND_SKILL_HOLYMIND, pX, pY, pZ);
		SkillPlaySound(SKILL_SOUND_SKILL_CASTING_PRIEST, pX, pY, pZ);

		pos.x = pX;	pos.y = pY;	pos.z = pZ;
		sinEffect_StartMagic(&pos, 1);
		break;

	case SKILL_PLAY_HOLY_BOLT:
	case SKILL_PLAY_MULTI_SPARK:
		SkillPlaySound(SKILL_SOUND_SKILL_CASTING_PRIEST, pX, pY, pZ);

		pos.x = pX;	pos.y = pY;	pos.z = pZ;
		sinEffect_StartMagic(&pos, 1);
		break;

	case SKILL_PLAY_DIVINE_LIGHTNING:
		pos.x = pX;	pos.y = pY;	pos.z = pZ;
		sinEffect_StartMagic(&pos, 1);
		SkillPlaySound(SKILL_SOUND_SKILL_CASTING_PRIEST, pX, pY, pZ);
		break;
	case SKILL_PLAY_HOLY_REFLECTION:
		sinSkillEffect_Holy_Reflection(this, Holy_Reflection_Time[point - 1]);
		pos.x = pX;	pos.y = pY;	pos.z = pZ;
		sinEffect_StartMagic(&pos, 1);
		SkillPlaySound(SKILL_SOUND_SKILL_CASTING_PRIEST, pX, pY, pZ);
		SkillPlaySound(SKILL_SOUND_SKILL_HOLYREFLECTION1, pX, pY, pZ);
		break;
	case SKILL_PLAY_GREAT_HEALING:
		sinSkillEffect_Great_Healing(this);
		pos.x = pX;	pos.y = pY;	pos.z = pZ;
		sinEffect_StartMagic(&pos, 1);
		SkillPlaySound(SKILL_SOUND_SKILL_CASTING_PRIEST, pX, pY, pZ);
		SkillPlaySound(SKILL_SOUND_SKILL_GRANDHEALING, pX, pY, pZ);
		break;

	case SKILL_PLAY_VIGOR_BALL:
	case SKILL_PLAY_RESURRECTION:
	case SKILL_PLAY_EXTINCTION:
	case SKILL_PLAY_VIRTUAL_LIFE:
		SkillPlaySound(SKILL_SOUND_SKILL_CASTING_PRIEST, pX, pY, pZ);

		pos.x = pX;	pos.y = pY;	pos.z = pZ;
		sinEffect_StartMagic(&pos, 1);
		break;




	case SKILL_PLAY_AGONY:
		sinEffect_Agony(this);
		SkillPlaySound(SKILL_SOUND_SKILL_CASTING_MAGICIAN, pX, pY, pZ);
		SkillPlaySound(SKILL_SOUND_SKILL_AGONY, pX, pY, pZ);

		pos.x = pX;	pos.y = pY;	pos.z = pZ;
		sinEffect_StartMagic(&pos, 2);
		break;
	case SKILL_PLAY_ZENITH:
		sinEffect_Zenith(this, Zenith_Time[point - 1]);
		SkillPlaySound(SKILL_SOUND_SKILL_CASTING_MAGICIAN, pX, pY, pZ);
		SkillPlaySound(SKILL_SOUND_SKILL_ZENITH, pX, pY, pZ);

		pos.x = pX;	pos.y = pY;	pos.z = pZ;
		sinEffect_StartMagic(&pos, 2);
		break;

	case SKILL_PLAY_FIRE_BALL:
	case SKILL_PLAY_FIRE_BOLT:
		SkillPlaySound(SKILL_SOUND_SKILL_CASTING_MAGICIAN, pX, pY, pZ);

		pos.x = pX;	pos.y = pY;	pos.z = pZ;
		sinEffect_StartMagic(&pos, 2);
		break;

	case SKILL_PLAY_COLUMN_OF_WATER:
		SkillPlaySound(SKILL_SOUND_SKILL_CASTING_MAGICIAN, pX, pY, pZ);
		pos.x = pX;	pos.y = pY;	pos.z = pZ;
		sinEffect_StartMagic(&pos, 2);
		break;
	case SKILL_PLAY_ENCHANT_WEAPON:
		SkillPlaySound(SKILL_SOUND_SKILL_CASTING_MAGICIAN, pX, pY, pZ);
		pos.x = pX;	pos.y = pY;	pos.z = pZ;
		sinEffect_StartMagic(&pos, 2);

		pos.x = pX;
		pos.y = pY;
		pos.z = pZ;

		if (this == lpCurPlayer)
		{
			if (!chrAttackTarget)
			{
				cnt = Enchant_Weapon_Time[point - 1];
				EnchantEffect_Point = point;
				switch ((param))
				{
				case 0:
					AssaParticle_EnchantWeaponIceJang(this, cnt);
					WeaponEffect = sITEMINFO_ICE + 1;
					dwWeaponEffectTime = dwPlayTime + cnt * 1000;
					break;
				case 1:
					AssaParticle_EnchantWeaponLightJang(this, cnt);
					WeaponEffect = sITEMINFO_LIGHTING + 1;
					dwWeaponEffectTime = dwPlayTime + cnt * 1000;
					break;
				case 2:
					AssaParticle_EnchantWeaponFireJang(this, cnt);
					WeaponEffect = sITEMINFO_FIRE + 1;
					dwWeaponEffectTime = dwPlayTime + cnt * 1000;
					break;
				}
			}
		}
		SkillPlaySound(SKILL_SOUND_SKILL_ENCHANTWEAPON_CAST, pX, pY, pZ);
		break;

	case SKILL_PLAY_DEAD_RAY:
		SkillPlaySound(SKILL_SOUND_SKILL_CASTING_MAGICIAN, pX, pY, pZ);
		pos.x = pX;	pos.y = pY;	pos.z = pZ;
		sinEffect_StartMagic(&pos, 2);
		break;

	case SKILL_PLAY_ENERGY_SHIELD:
	case SKILL_PLAY_DIASTROPHISM:
	case SKILL_PLAY_SPIRIT_ELEMENTAL:
	case SKILL_PLAY_DANCING_SWORD:

		SkillPlaySound(SKILL_SOUND_SKILL_CASTING_MAGICIAN, pX, pY, pZ);
		pos.x = pX;	pos.y = pY;	pos.z = pZ;
		sinEffect_StartMagic(&pos, 2);
		break;


	case SKILL_PLAY_COMPULSION:
		SkillPlaySound(SKILL_SOUND_SKILL_COMPULSION1, pX, pY, pZ);
		break;

	case SKILL_PLAY_IMPULSION:
		SkillImpulsionLight(this, 2);
		break;

	case SKILL_PLAY_MAGNETIC_SPHERE:
		SkillPlaySound(SKILL_SOUND_SKILL_SPARK1, pX, pY, pZ);
		break;

	case SKILL_PLAY_METAL_GOLEM:
		SkillPlaySound(SKILL_SOUND_SKILL_METAL_GOLEM, pX, pY, pZ);
		break;

	case SKILL_PLAY_DESTROYER:
		SkillWarriorDestroyerBlade(this, 3.0f);
		break;

	case SKILL_PLAY_BERSERKER:
		SkillPlaySound(SKILL_SOUND_SKILL_BERSERKER, pX, pY, pZ);
		break;

	case SKILL_PLAY_CYCLONE_STRIKE:
		SkillWarriorCycloneStrikeBlade(this, 3);
		SkillPlaySound(SKILL_SOUND_SKILL_CYCLONE_STRIKE, pX, pY, pZ);
		break;

	case SKILL_PLAY_ASSASSIN_EYE:
		SkillPlaySound(SKILL_SOUND_SKILL_ASSASSIN_EYE, pX, pY, pZ);
		break;

	case SKILL_PLAY_CHARGING_STRIKE:
	case SKILL_PLAY_SHADOW_MASTER:
		if (this == lpCurPlayer) SkillEventDamageCount = 0;
		break;

	case SKILL_PLAY_PHOENIX_SHOT:

		break;

	case SKILL_PLAY_VAGUE:
		SkillPlaySound(SKILL_SOUND_SKILL_VAGUE, pX, pY, pZ);
		break;

	case SKILL_PLAY_GODS_BLESS:
		SkillSaintGodBless(this, (float)God_Bless_Time[point - 1]);
		SkillPlaySound(SKILL_SOUND_SKILL_GODS_BLESS, pX, pY, pZ);
		break;

	case SKILL_PLAY_RECALL_WOLVERIN:
		break;

	case SKILL_PLAY_FORCE_OF_NATURE:
		SkillPlaySound(SKILL_SOUND_SKILL_FORCE_OF_NATURE, pX, pY, pZ);
		break;

	case SKILL_PLAY_GODLY_SHIELD:
		SkillPlaySound(SKILL_SOUND_SKILL_GODLY_SHIELD, pX, pY, pZ);
		break;

	case SKILL_PLAY_SWORD_OF_JUSTICE:
		SkillPlaySound(SKILL_SOUND_SKILL_SWORD_OF_JUSTICE, pX, pY, pZ);
		break;

	case SKILL_PLAY_HALL_OF_VALHALLA:
		SkillPlaySound(SKILL_SOUND_SKILL_HALL_OF_VALHALLA, pX, pY, pZ);
		break;
	case SKILL_PLAY_FROST_JAVELIN:
		SkillPlaySound(SKILL_SOUND_SKILL_FROST_JAVELIN, pX, pY, pZ);
		break;

	case SKILL_PLAY_GLACIAL_SPIKE:
		SkillPlaySound(SKILL_SOUND_SKILL_CASTING_PRIEST, pX, pY, pZ);
		pos.x = pX;	pos.y = pY;	pos.z = pZ;
		sinEffect_StartMagic(&pos, 1);
		break;

	case SKILL_PLAY_REGENERATION_FIELD:
		SkillPlaySound(SKILL_SOUND_SKILL_REGEN_FIELD2, pX, pY, pZ);
		pos.x = pX;	pos.y = pY;	pos.z = pZ;
		sinEffect_StartMagic(&pos, 1);
		break;

	case SKILL_PLAY_CHAIN_LIGHTNING:
		SkillPlaySound(SKILL_SOUND_SKILL_CASTING_PRIEST, pX, pY, pZ);

		pos.x = pX;	pos.y = pY;	pos.z = pZ;
		sinEffect_StartMagic(&pos, 1);
		break;

	case SKILL_PLAY_SUMMON_MUSPELL:
		SkillPlaySound(SKILL_SOUND_SKILL_MUSPELL1, pX, pY, pZ);

		pos.x = pX;	pos.y = pY;	pos.z = pZ;
		sinEffect_StartMagic(&pos, 1);
		break;

	case SKILL_PLAY_FIRE_ELEMENTAL:
		SkillPlaySound(SKILL_SOUND_SKILL_FIRE_ELEMENTAL, pX, pY, pZ);

		pos.x = pX;	pos.y = pY;	pos.z = pZ;
		sinEffect_StartMagic(&pos, 2);
		break;

	case SKILL_PLAY_FLAME_WAVE:
		SkillPlaySound(SKILL_SOUND_SKILL_FLAME_WAVE3, pX, pY, pZ);

		pos.x = pX;	pos.y = pY;	pos.z = pZ;
		sinEffect_StartMagic(&pos, 2);
		break;

	case SKILL_PLAY_DISTORTION:
		SkillPlaySound(SKILL_SOUND_SKILL_DISTORTION, pX, pY, pZ);

		pos.x = pX;	pos.y = pY;	pos.z = pZ;
		sinEffect_StartMagic(&pos, 2);
		break;

	case SKILL_PLAY_METEO:
		SkillPlaySound(SKILL_SOUND_SKILL_CASTING_MAGICIAN, pX, pY, pZ);
		pos.x = pX;	pos.y = pY;	pos.z = pZ;
		sinEffect_StartMagic(&pos, 2);
		break;

	}



	return TRUE;
}


int smCHAR::BeginAttack_Monster()
{
	switch (smCharInfo.dwCharSoundCode)
	{
	case snCHAR_SOUND_DARKKNIGHT:

		if (smCharInfo.Level >= 65)
			AssaParticle_DoomGuardHit1(this);
		break;

	case snCHAR_SOUND_GUARDIAN_SAINT:


		break;

	case snCHAR_SOUND_DEATHKNIGHT:
		if (MotionInfo->KeyCode != 'L')
			ParkValentSwordShow(this, 70);
		break;

	case snCHAR_SOUND_DEVIL_BIRD:
		if (MotionInfo->KeyCode != 'B')
			ParkDevilBirdAttackBlur(this);
		break;


	case snCHAR_SOUND_KELVEZU:
		if (MotionInfo->KeyCode == 'P')
		{
			ParkKelvezuWingShow(this, 70);
		}
		else
		{
			ParkKelvezuFingerShow(this, 70);
		}

		break;

	case snCHAR_SOUND_CHIMERA:
		ParkAssaParticle_ChimeraNormal(this);
		break;
	case snCHAR_SOUND_REVIVED_ARCHER:

		break;
	}

	return TRUE;
}


int smCHAR::BeginSkill_Monster()
{
	POINT3D	pos;

	switch (smCharInfo.dwCharSoundCode)
	{
	case snCHAR_SOUND_NAZ:
		GetMoveLocation(0, 0, 100 * fONE, 0, Angle.y, 0);
		StartSkillDest(pX, pY, pZ, pX + GeoResult_X, pY, pZ + GeoResult_Z, SKILL_TORNADO2, 1);
		break;

	case snCHAR_SOUND_FURY:
		StartEffectMonster(pX, pY, pZ, 0, Angle.y, 0, MONSTER_FURY_MAGIC1);
		break;

	case snCHAR_SOUND_DARKKNIGHT:

		if (smCharInfo.Level >= 65)
			AssaParticle_DoomGuardHit2(this);
		break;

	case snCHAR_SOUND_HEAVYGOBLIN:

		AssaParticle_HeavyGoblinHit1(this);
		break;

	case snCHAR_SOUND_ICEGOBLIN:
		ParkAssaParticle_IceGoblinHit1(this);
		break;

	case snCHAR_SOUND_COLDEYE:
		ParkParticle_ColdEyeSkill(this);
		break;

	case snCHAR_SOUND_CHAOSCARA:
		if (MotionInfo->KeyCode == 'J')
		{
			if (chrAttackTarget)
			{
				ParkAssaParticle_ChaosKara2(chrAttackTarget);
			}
			LastSkillParam = 0;
		}
		else
		{
			ParkAssaParticle_ChaosKaraSkill_Monster(this);

			SkillPlay_Monster_Effect(this, SKILL_PLAY_CHAOSCARA_VAMP, 220);
			LastSkillParam = 1;
		}
		break;

	case snCHAR_SOUND_DEATHKNIGHT:
		ParkValentSwordShow(this, 70);
		break;

	case snCHAR_SOUND_DEVIL_BIRD:
		DevilBird_Skill(this);
		break;

	case snCHAR_SOUND_KELVEZU:
		if (MotionInfo->KeyCode == 'I')
		{
			ParkKelvezuWingShow(this, 200);
		}
		else
		{
			ParkKelvezuTaleShow(this, 90);
			ParkKelvezuSkill2(this);
		}
		break;

	case snCHAR_SOUND_NPC_SKILLMASTER:
		switch (MotionInfo->KeyCode)
		{
		case 'A':
			break;
		case 'B':
		case 'N':
		case 'Y':
			AssaMotionBlur(this, "Bip01 R Hand", "bip01 weapon", 80);
			break;
		case 'M':
			break;

		case 'L':
			SkillLancelotChargingStrike(this);
			break;

		}
		break;

	case snCHAR_SOUND_NPC_MAGICMASTER:
		SkillPlaySound(SKILL_SOUND_SKILL_CASTING_MAGICIAN, pX, pY, pZ);
		pos.x = pX;	pos.y = pY;	pos.z = pZ;
		sinEffect_StartMagic(&pos, 2);
		break;


	case snCHAR_SOUND_CASTLE_SOLDER_A:
		AssaMotionBlur(this, "Bip01_w", "Bip01 Effect", 80);
		break;
	case snCHAR_SOUND_CASTLE_SOLDER_B:
		AssaMotionBlur(this, "Bip01 waraxe", "Bip01 Effect", 80);
		break;
	case snCHAR_SOUND_CASTLE_SOLDER_C:
		AssaMotionBlur(this, "Bip01 Sword", "Bip01 Effect", 80);
		break;
	case snCHAR_SOUND_REVIVED_KNIGHT:
		if (chrAttackTarget)
		{
			if (MotionInfo->KeyCode == 'H')
			{


				SkillPlaySound(SKILL_SOUND_SKILL_PIERCING, pX, pY, pZ);
			}
		}
		break;
	case snCHAR_SOUND_REVIVED_PRIESTESS:
		SkillPlaySound(SKILL_SOUND_SKILL_CASTING_MAGICIAN, pX, pY, pZ);
		pos.x = pX;	pos.y = pY;	pos.z = pZ;
		sinEffect_StartMagic(&pos, 2);
		break;
	case snCHAR_SOUND_REVIVED_PIKEMAN:
		if (chrAttackTarget)
		{
			switch (MotionInfo->KeyCode)
			{
			case 'Z':
				AssaMotionBlur(this, "Bip01 R Hand", "bip01 wea", 80);
				break;
			}
		}
		break;
	}

	return TRUE;
}


int smCHAR::EventSkill_Monster()
{
	POINT3D	pos, pos2;
	RECT rect;
	int x, y, z;

	switch (smCharInfo.dwCharSoundCode)
	{
	case snCHAR_SOUND_NAZ:

		break;

	case snCHAR_SOUND_HEADCUTTER:
		GetMoveLocation(0, 0, 60 * fONE, 0, Angle.y, 0);
		StartEffectMonster(pX + GeoResult_X, pY + GeoResult_Y, pZ + GeoResult_Z, 0, Angle.y, 0, MONSTER_HEADER_CUTTER_HIT1);
		break;

	case snCHAR_SOUND_TEMPLEGUARD:
	case snCHAR_SOUND_DMACHINE:
	case snCHAR_SOUND_TURTLE_CANNON:

		if (chrAttackTarget)
		{
			GetMoveLocation(0, 40 * fONE, 0, 0, Angle.y, 0);
			StartEffectMonsterDest(pX + GeoResult_X, pY + GeoResult_Y, pZ + GeoResult_Z,
				chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ,
				MONSTER_DMACHINE_MISSILE2);
		}
		break;
	case snCHAR_SOUND_REVIVED_KNIGHT:
		switch (MotionInfo->KeyCode)
		{
		case 'H':
			if (chrAttackTarget)
			{
				sinSkillEffect_Piercing_Attack(this);
			}
			break;
		case 'Z':
			if (chrAttackTarget && GetAttackPoint(&x, &y, &z) == TRUE)
			{
				pos.x = x;
				pos.y = y;
				pos.z = z;
				if (MotionEvent == 1)
				{
					AssaParticle_GrandCrossHorz(&pos, Angle.y);
					SkillPlaySound(SKILL_SOUND_SKILL_SWING2, pX, pY, pZ);
				}
				else
				{
					AssaParticle_GrandCrossVert(&pos, Angle.y);
					SkillPlaySound(SKILL_SOUND_SKILL_GRAND_CROSS, pX, pY, pZ);
				}
			}
			else
			{


				PlayWaponSoundDirect(pX, pY, pZ, 13);
			}
			break;

		}
		break;

	case snCHAR_SOUND_OMICRON:

		if (chrAttackTarget)
		{
			GetMoveLocation(0, 20 * fONE, 20 * fONE, 0, Angle.y, 0);
			StartEffectMonster(pX + GeoResult_X, pY + GeoResult_Y, pZ + GeoResult_Z,
				0, Angle.y, 0, MONSTER_OMICRON_HIT1);
		}
		break;

	case snCHAR_SOUND_RATOO:

		if (chrAttackTarget)
		{
			AssaParticle_RatooHit1(this);
		}
		break;

	case snCHAR_SOUND_MOKOVA:
	case snCHAR_SOUND_STYGIANLORD:

		if (chrAttackTarget)
		{
			StartEffectMonster(pX, pY, pZ, MONSTER_STYGIANLORD_MAGIC1);
		}
		break;

	case snCHAR_SOUND_SHADOW:

		if (chrAttackTarget)
		{
			GetMoveLocation(0, 140 * fONE, 32 * fONE, 0, Angle.y, 0);
			StartEffectMonsterDest(pX + GeoResult_X, pY + GeoResult_Y, pZ + GeoResult_Z,
				chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ,
				Angle.x, Angle.y, Angle.z, MONSTER_SHADOW_SHOT1);
		}
		break;

	case snCHAR_SOUND_SUCCUBUS:

		if (chrAttackTarget)
		{

			if (smCharInfo.Level <= 75)
			{
				StartEffectMonster(pX, pY, pZ, MONSTER_SERQBUS_MAGIC1);
				StartEffect_Serqbus_Skill1(chrAttackTarget, SUCCUBUS_CURSE_TIME);
				StartEffectMonster(chrAttackTarget->pX, chrAttackTarget->pY + chrAttackTarget->PatHeight, chrAttackTarget->pZ, MONSTER_SERQBUS_MAGIC_ATTACK1);

				if (chrAttackTarget == lpCurPlayer)
				{
					if (!sDisplayState[0].Absorb)
						sDisplayState[0].Absorb = -GetRandomPos(2, 6);
					sDisplayState[0].MaxTime = dwPlayTime + SUCCUBUS_CURSE_TIME * 1000;
				}

			}
			else if (smCharInfo.Level < 80)
			{
				if (chrAttackTarget->smCharInfo.State != smCHAR_STATE_USER)
				{
					StartEffectMonster(pX, pY, pZ, MONSTER_SERQBUS_MAGIC2);
					StartEffectMonster(chrAttackTarget->pX, chrAttackTarget->pY + chrAttackTarget->PatHeight, chrAttackTarget->pZ, MONSTER_SERQBUS_MAGIC_ATTACK2);
				}
			}
			else if (smCharInfo.Level < 90)
			{
				StartEffectMonster(pX, pY, pZ, MONSTER_SERQBUS_MAGIC3);
				StartEffect_Serqbus_Skill3(chrAttackTarget, SUCCUBUS_CURSE_TIME);
				StartEffectMonster(chrAttackTarget->pX, chrAttackTarget->pY + chrAttackTarget->PatHeight, chrAttackTarget->pZ, MONSTER_SERQBUS_MAGIC_ATTACK3);

				if (chrAttackTarget == lpCurPlayer)
				{
					if (!sDisplayState[1].PercentDamage[0])
					{
						sDisplayState[1].PercentDamage[0] = -GetRandomPos(10, 15);
						sDisplayState[1].PercentDamage[1] = sDisplayState[1].PercentDamage[0];
					}
					sDisplayState[1].MaxTime = dwPlayTime + SUCCUBUS_CURSE_TIME * 1000;
				}
			}
			else
			{
				ParkIncubusSummonerSkill(this);
			}
		}
		break;


	case snCHAR_SOUND_EVILPLANT:

		if (smCharInfo.Level >= 60)
		{

			AssaParticle_EvilPlantShot(this);
		}
		else
		{

			AssaParticle_EvilMapleShot(this);
		}
		break;

	case snCHAR_SOUND_STONEGOLEM:

		AssaParticle_StoneGolemShot(this);
		break;


	case snCHAR_SOUND_SOLIDSNAIL:

		if (chrAttackTarget)
		{
			pos.x = chrAttackTarget->pX;
			pos.y = chrAttackTarget->pY;
			pos.z = chrAttackTarget->pZ;

			AssaParticle_SnailShot(this, &pos);
		}

	case snCHAR_SOUND_SCORPION:

		if (chrAttackTarget && smCharInfo.Level == 50)
		{
			pos.x = chrAttackTarget->pX;
			pos.y = chrAttackTarget->pY;
			pos.z = chrAttackTarget->pZ;

			AssaParticle_SnailShot(this, &pos);
		}
		break;

	case snCHAR_SOUND_THORNCRAWLER:

		if (chrAttackTarget)
		{
			pos.x = chrAttackTarget->pX;
			pos.y = chrAttackTarget->pY;
			pos.z = chrAttackTarget->pZ;

			AssaParticle_ThornCrawlerShot(this, &pos);
		}
		break;

	case snCHAR_SOUND_NIGHTMARE:
	case snCHAR_SOUND_HEST:

		AssaParticle_NightMare(this);
		break;

	case snCHAR_SOUND_GUARDIAN_SAINT:

		AssaParticleClanMonsterHit1(this);

		break;

	case snCHAR_SOUND_HYPERMACHINE:

		if (chrAttackTarget)
		{
			pos.x = chrAttackTarget->pX;
			pos.y = chrAttackTarget->pY;
			pos.z = chrAttackTarget->pZ;
			AssaParticle_MonsterIronHyperSkill1(this, &pos);
		}
		break;

	case snCHAR_SOUND_RUNICGUARDIAN:
		if (chrAttackTarget)
		{
			AssaParticle_MonsterIronRunicGuardian(this, chrAttackTarget);
		}
		break;

	case snCHAR_SOUND_BABEL:
		if (chrAttackTarget)
		{
			AssaParticle_MonsterRunicGrardianBossSkill(this);
		}
		break;


	case snCHAR_SOUND_MOUNTAIN:
		AssaParticle_MonsterIronMountainSkill1(this);
		break;

	case snCHAR_SOUND_TOWERGOLEM:
		AssaParticle_MonsterIronTowerGolemSkill1(this);
		break;

	case snCHAR_SOUND_SADNESS:
		AssaParticle_MonsterIronSadNessSkill1(this);
		break;

	case snCHAR_SOUND_IRONFIST:
		AssaParticle_MonsterIronFist(this);
		break;

	case snCHAR_SOUND_MORGON:
	case snCHAR_SOUND_GORGON:
		AssaParticle_MonsterIronMorgonHit(this);
		break;



	case snCHAR_SOUND_ICEGOLEM:
		ParkAssaParticle_IceGolemShot(this);
		break;
	case snCHAR_SOUND_FROST:
		ParkAssaParticle_AcientDia(this);
		break;
	case snCHAR_SOUND_FROZEN:
		if (chrAttackTarget)
		{
			ParkAssaParticle_MistIceBall(this, chrAttackTarget);
		}
		break;

	case snCHAR_SOUND_MYSTIC:
		if (chrAttackTarget)
		{
			StartEffectMonster(pX, pY, pZ, MONSTER_SERQBUS_MAGIC2);
			StartEffect_Serqbus_Skill1(chrAttackTarget, SUCCUBUS_CURSE_TIME);
			StartEffectMonster(chrAttackTarget->pX, chrAttackTarget->pY + chrAttackTarget->PatHeight, chrAttackTarget->pZ, MONSTER_SERQBUS_MAGIC_ATTACK1);

			if (chrAttackTarget == lpCurPlayer)
			{
				if (!sDisplayState[0].Absorb)
					sDisplayState[0].Absorb = -GetRandomPos(10, 16);
				sDisplayState[0].MaxTime = dwPlayTime + SUCCUBUS_CURSE_TIME * 1000;
			}
		}
		break;

	case snCHAR_SOUND_DEATHKNIGHT:
		if (MotionInfo->KeyCode == 'N')
			ParkAssaParticle_Valento1(this);
		break;



	case snCHAR_SOUND_SPIDER:
		ParkAssaParticle_SpiderTrooperHit1(this);
		break;

	case snCHAR_SOUND_STINGRAY:
		ParkAssaParticle_StingRay(this);
		break;

	case snCHAR_SOUND_M_LORD:
		SkillPlay_MummyLord_Effect(this, 200);
		break;

	case snCHAR_SOUND_GOBLINSHAMAN:
		SkillPlay_MummyLord_Effect(this, 200);
		break;




	case snCHAR_SOUND_BLIZZARD_GIANT:
		if (chrAttackTarget)
		{
			ParkBlizzardGiantSkillToTarget(chrAttackTarget);
		}
		break;
	case snCHAR_SOUND_DEVIL_BIRD:
		if (chrAttackTarget)
		{
			ParkDevilBirdSkillToTarget(chrAttackTarget);
		}
		break;

	case snCHAR_SOUND_KELVEZU:
		if (chrAttackTarget)
		{
			if (MotionInfo->KeyCode == 'I')
			{
				ParkKelvezuSkillHit(chrAttackTarget);
				ParkKelvezuSkill1(this);
			}
			else
			{
				ParkKelvezuSkillHit(chrAttackTarget);
			}
		}
		break;



	case snCHAR_SOUND_DARKPHALANX:
		ParkAssaParticle_DarkPhalanx(this);
		break;
	case snCHAR_SOUND_FIREWORM:
		if (chrAttackTarget)
		{
			ParkAssaParticle_FireWorm(chrAttackTarget, 1);
		}
		break;

	case snCHAR_SOUND_CHIMERA:
		if (chrAttackTarget)
		{
			ParkAssaParticle_ChimeraSkill(chrAttackTarget);
		}
		break;

	case snCHAR_SOUND_BLOODYKNIGHT:
		ParkAssaParticle_BloodySkill(this);
		break;
	case snCHAR_SOUND_HELLHOUND:
		ParkAssaParticle_HellHoundSkillAttack(this);
		break;
	case snCHAR_SOUND_DARKGUARD:
		if (chrAttackTarget)
		{
			ParkAssaParticle_DarkGuardSkill(this, chrAttackTarget);
		}
		break;
	case snCHAR_SOUND_DARKMAGE:
		if (chrAttackTarget)
		{
			ParkAssaParticle_DarkMageSkill(chrAttackTarget);
		}
		break;

	case snCHAR_SOUND_SETO:
		SkillArchMageFlameWave(this);
		break;

	case snCHAR_SOUND_KINGSPIDER:

		if (chrAttackTarget)
		{
			GetMoveLocation(0, 0, 68 * fONE, 0, Angle.y, 0);
			StartEffectMonster(pX + GeoResult_X, pY + 22 * fONE, pZ + GeoResult_Z, MONSTER_HULK_HIT1);
		}
		break;



	case snCHAR_SOUND_S_METALGOLEM:
		if (chrAttackTarget)
		{
			if (!smCharInfo.wPlayClass[1])
				GetMoveLocation(0, 0, 54 * fONE, 0, Angle.y, 0);
			else
				GetMoveLocation(0, 0, 54 * smCharInfo.wPlayClass[1], 0, Angle.y, 0);

			StartEffectMonster(pX + GeoResult_X, pY + 48 * fONE, pZ + GeoResult_Z, MONSTER_HULK_HIT1);
		}
		break;

	case snCHAR_SOUND_S_WOLVERLIN:
		if (chrAttackTarget)
		{
			if (!smCharInfo.wPlayClass[1])
				GetMoveLocation(0, 0, 50 * fONE, 0, Angle.y, 0);
			else
				GetMoveLocation(0, 0, 50 * smCharInfo.wPlayClass[1], 0, Angle.y, 0);

			x = pX + GeoResult_X;
			z = pZ + GeoResult_Z;
			y = pY + 18 * fONE;
			StartEffectMonster(x, y, z, MONSTER_PIGON_PARTICLE1);
			StartEffectMonster(x, y, z, MONSTER_PIGON_PARTICLE1);
			StartEffectMonster(x, y, z, MONSTER_PIGON_PARTICLE1);
			StartEffectMonster(x, y, z, MONSTER_PIGON_PARTICLE1);
		}
		break;

	case snCHAR_SOUND_NPC_SKILLMASTER:
		if (chrAttackTarget)
		{
			switch (MotionInfo->KeyCode)
			{
			case 'A':
				StartSkillDest(pX, pY + 24 * fONE, pZ, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ, SKILL_SPARK, 8);
				SkillPlaySound(SKILL_SOUND_SKILL_SPARK2, pX, pY, pZ);
				break;
			case 'B':
				if (GetAttackPoint(&x, &y, &z) == TRUE)
				{
					StartSkill(x, y, z, 0, 0, 0, SKILL_TRIPLE_IMPACT);
					SetDynLight(x, y, z, 100, 0, 0, 0, 300);
					SkillPlaySound(SKILL_SOUND_SKILL_AVANGING_CRASH, pX, pY, pZ);
				}
				break;
			case 'N':
				if (GetAttackPoint(&x, &y, &z) == TRUE)
				{
					pos.x = x;
					pos.y = y;
					pos.z = z;
					AssaParticle_ChainLance(&pos);
				}
				break;
			case 'M':
				GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);
				pos.x = pX + GeoResult_X;
				pos.y = pY + GeoResult_Y;
				pos.z = pZ + GeoResult_Z;
				pos2.x = chrAttackTarget->pX;
				pos2.y = chrAttackTarget->pY + 24 * fONE;
				pos2.z = chrAttackTarget->pZ;
				SkillSagittarionPhoneixShot(this, &pos, &pos2);
				SkillPlaySound(SKILL_SOUND_SKILL_PHOENIX_SHOT, pX, pY, pZ);
				break;
			case 'Y':
				if (GetAttackPoint(&pos.x, &pos.y, &pos.z) == TRUE)
				{
					SkillWarriorDestroyerHit(&pos);
					if (MotionEvent < 3)
						SkillPlaySound(SKILL_SOUND_SKILL_AVANGING_CRASH, pX, pY, pZ);
					else
						SkillPlaySound(SKILL_SOUND_SKILL_EXPANSION2, pX, pY, pZ);
				}
				break;
			case 'L':
				if (GetAttackPoint(&x, &y, &z) == TRUE)
				{
					StartSkill(x, y, z, 0, 0, 0, SKILL_TRIPLE_IMPACT);
					SetDynLight(x, y, z, 100, 0, 0, 0, 400);
					switch (MotionEvent)
					{
					case 1:
						SkillPlaySound(SKILL_SOUND_SKILL_CHAIN_LANCE2, pX, pY, pZ);
						break;
					case 2:
						SkillPlaySound(SKILL_SOUND_SKILL_AVANGING_CRASH, pX, pY, pZ);
						break;
					case 3:
					case 4:
						SkillPlaySound(SKILL_SOUND_SKILL_CHARGING_STRIKE, pX, pY, pZ);
						break;
					}
				}
				break;
			}
		}
		break;
	case snCHAR_SOUND_NPC_MAGICMASTER:
		if (chrAttackTarget)
		{
			switch (MotionInfo->KeyCode)
			{
			case 'R':
				AssaParticle_EnergyShield(this, 5);
				SkillPlaySound(SKILL_SOUND_SKILL_ENERGY_SHIELD, pX, pY, pZ);
				break;
			case 'E':
				sinEffect_MultiSpark(this, chrAttackTarget, 5);
				SkillPlaySound(SKILL_SOUND_SKILL_MULTISPARK, pX, pY, pZ);
				break;
			case 'U':
				GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);
				pos.x = pX + GeoResult_X;
				pos.y = pY + GeoResult_Y;
				pos.z = pZ + GeoResult_Z;
				pos2.x = chrAttackTarget->pX;
				pos2.y = chrAttackTarget->pY + 32 * fONE;
				pos2.z = chrAttackTarget->pZ;

				AssaParticle_DeadLay(&pos, &pos2);
				SkillPlaySound(SKILL_SOUND_SKILL_DEATHRAY, pX, pY, pZ);
				break;
			case 'I':
				GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);
				StartEffectMonsterDest(pX + GeoResult_X, pY + GeoResult_Y, pZ + GeoResult_Z,
					chrAttackTarget->pX, chrAttackTarget->pY + 20 * fONE, chrAttackTarget->pZ,
					MONSTER_PIGON_SHOT1);

				if (((dwPlayTime >> 4) & 1) == 0)
					SkillPlaySound(SKILL_SOUND_SKILL_FIREBALL1, pX, pY, pZ);
				else
					SkillPlaySound(SKILL_SOUND_SKILL_FIREBALL2, pX, pY, pZ);
				break;

			case 'H':
				Angle.y = GetRadian2D(pX, pZ, chrAttackTarget->pX, chrAttackTarget->pZ);
				SkillCelestialGlacialSpike(this);

				GetMoveLocation(0, 0, 64 * fONE, 0, Angle.y, 0);
				SetDynLight(pX + GeoResult_X, pY, pZ + GeoResult_Z, 0, 0, 100, 0, 700);

				if (rand() % 2)
					SkillPlaySound(SKILL_SOUND_SKILL_GLACIAL_SPIKE1, pX, pY, pZ);
				else
					SkillPlaySound(SKILL_SOUND_SKILL_GLACIAL_SPIKE2, pX, pY, pZ);

				if (chrAttackTarget == lpCurPlayer)
				{
					lpCurPlayer->PlaySlowCount = 90;
					lpCurPlayer->AttackIce -= 160;
				}

				break;

			case 'G':
				pos.x = chrAttackTarget->pX;
				pos.y = chrAttackTarget->pY;
				pos.z = chrAttackTarget->pZ;
				SkillArchMageMeteo(&pos);
				SkillPlaySound(SKILL_SOUND_SKILL_METEO1, pX, pY, pZ);
				break;

			}
		}
		break;

	case snCHAR_SOUND_CASTLE_SOLDER_A:
	case snCHAR_SOUND_CASTLE_SOLDER_B:
	case snCHAR_SOUND_CASTLE_SOLDER_C:
		if (chrAttackTarget)
		{
			if (GetAttackPoint(&x, &y, &z) == TRUE)
			{
				StartSkill(x, y, z, 0, 0, 0, SKILL_TRIPLE_IMPACT);
				SetDynLight(x, y, z, 100, 0, 0, 0, 300);
				SkillPlaySound(SKILL_SOUND_SKILL_AVANGING_CRASH, pX, pY, pZ);
			}
		}
		break;

	case snCHAR_SOUND_CASTLE_CRYSTAL_R:
		AssaParticle_CastleRed(this);
		break;

	case snCHAR_SOUND_CASTLE_CRYSTAL_G:
		AssaParticle_CastleGreen(this);
		break;

	case snCHAR_SOUND_CASTLE_CRYSTAL_B:
		AssaParticle_CastleBlue(this);
		break;
	case snCHAR_SOUND_REVIVED_MAGICIAN:
		if (chrAttackTarget)
		{
			switch (MotionInfo->KeyCode)
			{
			case 'O':
				GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);
				pos.x = pX + GeoResult_X;
				pos.y = pY + GeoResult_Y;
				pos.z = pZ + GeoResult_Z;
				pos2.x = chrAttackTarget->pX;
				pos2.y = chrAttackTarget->pY + 32 * fONE;
				pos2.z = chrAttackTarget->pZ;

				AssaParticle_DeadLay(&pos, &pos2);
				SkillPlaySound(SKILL_SOUND_SKILL_DEATHRAY, pX, pY, pZ);
				break;
			case 'Q':
				SkillArchMageFlameWave(this);

				if (rand() % 2)
					SkillPlaySound(SKILL_SOUND_SKILL_FLAME_WAVE1, pX, pY, pZ);
				else
					SkillPlaySound(SKILL_SOUND_SKILL_FLAME_WAVE2, pX, pY, pZ);
				break;
			case 'Z':
				pos.x = chrAttackTarget->pX;
				pos.y = chrAttackTarget->pY;
				pos.z = chrAttackTarget->pZ;
				SkillArchMageMeteo(&pos);
				SkillPlaySound(SKILL_SOUND_SKILL_METEO1, pX, pY, pZ);
				break;
			}
		}
		break;
	case snCHAR_SOUND_REVIVED_ARCHER:
		if (chrAttackTarget)
		{
			switch (MotionInfo->KeyCode)
			{
			case 'O':
				GetAttackPoint(&x, &y, &z);
				StartSkillDest(x, y, z, chrAttackTarget->pX, chrAttackTarget->pY + (24 * fONE), chrAttackTarget->pZ, SKILL_WIND_ARROW);
				SkillPlaySound(SKILL_SOUND_WIND_ARROW, pX, pY, pZ);
				break;
			case 'Z':
				int cnt = frame - MotionInfo->StartFrame * 80;
				if (MotionInfo->EventFrame[1] <= (DWORD)cnt)
				{
					GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);
					pos.x = pX + GeoResult_X;
					pos.y = pY + GeoResult_Y;
					pos.z = pZ + GeoResult_Z;
					pos2.x = chrAttackTarget->pX;
					pos2.y = chrAttackTarget->pY + 24 * fONE;
					pos2.z = chrAttackTarget->pZ;
					SkillSagittarionPhoneixShot(this, &pos, &pos2);
					SkillPlaySound(SKILL_SOUND_SKILL_PHOENIX_SHOT, pX, pY, pZ);
				}
				break;
			}
		}
		break;
	case snCHAR_SOUND_REVIVED_ATALANTA:
		switch (MotionInfo->KeyCode)
		{
		case 'O':
			if (chrAttackTarget && GetAttackPoint(&x, &y, &z) == TRUE)
			{
				pos.x = x;
				pos.y = y;
				pos.z = z;
				pos2.x = chrAttackTarget->pX;
				pos2.y = chrAttackTarget->pY + 28 * fONE;
				pos2.z = chrAttackTarget->pZ;

				AssaParticle_StormJavelin(&pos, &pos2);

				rect.left = -30;
				rect.right = 30;
				rect.top = 0;
				rect.bottom = 240;
				rect.bottom += 20;
				rect.bottom += 20;

				for (int cnt = 0; cnt < dmSelected_CharCnt; cnt++)
				{
					if (lpSelected_Char[cnt])
					{
						AssaParticle_StormJavelinHit(lpSelected_Char[cnt], this, 0.5f);
					}
				}
				switch (rand() % 2)
				{
				case 0:
					SkillPlaySound(SKILL_SOUND_SKILL_STORM_JAVELIN1, pX, pY, pZ);
					break;
				case 1:
					SkillPlaySound(SKILL_SOUND_SKILL_STORM_JAVELIN2, pX, pY, pZ);
					break;
				}
			}
			break;
		case 'Z':
			if (chrAttackTarget)
			{
				GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);
				pos.x = pX + GeoResult_X;
				pos.y = pY + GeoResult_Y;
				pos.z = pZ + GeoResult_Z;
				pos2.x = chrAttackTarget->pX;
				pos2.y = chrAttackTarget->pY + 40 * fONE;
				pos2.z = chrAttackTarget->pZ;

				SkillVengeance(&pos, &pos2);







				if (MotionEvent == 1)
					SkillPlaySound(SKILL_SOUND_SKILL_VENGEANCE1, pX, pY, pZ);
				else
					SkillPlaySound(SKILL_SOUND_SKILL_VENGEANCE2, pX, pY, pZ);
			}
			break;
		}
		break;
	case snCHAR_SOUND_REVIVED_FIGTHER:
		if (chrAttackTarget)
		{
			switch (MotionInfo->KeyCode)
			{
			case 'G':

				AssaParticle_AvangingCrash(this);
				SkillPlaySound(SKILL_SOUND_SKILL_AVANGING_CRASH, pX, pY, pZ);
				break;
			case 'Z':
				if (GetAttackPoint(&pos.x, &pos.y, &pos.z) == TRUE)
				{
					SkillWarriorDestroyerHit(&pos);
					if (MotionEvent < 3)
						SkillPlaySound(SKILL_SOUND_SKILL_AVANGING_CRASH, pX, pY, pZ);
					else
						SkillPlaySound(SKILL_SOUND_SKILL_EXPANSION2, pX, pY, pZ);
				}
				break;
			}
		}
		break;
	case snCHAR_SOUND_REVIVED_MECANICIAN:
		if (chrAttackTarget)
		{
			switch (MotionInfo->KeyCode)
			{
			case 'O':
				StartSkillDest(pX, pY + 24 * fONE, pZ, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ, SKILL_SPARK, 8);
				SkillPlaySound(SKILL_SOUND_SKILL_SPARK2, pX, pY, pZ);
				break;
			case 'Z':
				if (GetAttackPoint(&x, &y, &z) == TRUE)
				{

					StartSkill(x, y, z, 0, Angle.y, 0, SKILL_GREAT_SMASH);
					SkillPlaySound(SKILL_SOUND_SKILL_SWING1, pX, pY, pZ);
				}
				break;
			}
		}
		break;
	case snCHAR_SOUND_REVIVED_PIKEMAN:
		if (chrAttackTarget)
		{
			switch (MotionInfo->KeyCode)
			{
			case 'G':
				if (GetAttackPoint(&x, &y, &z) == TRUE)
				{
					StartEffect(x, y, z, EFFECT_CRITICAL_HIT1);
					SetDynLight(x, y, z, 100, 0, 0, 0, 400);
					SkillPlaySound(SKILL_SOUND_JUMPING_CRASH2, pX, pY, pZ);
				}
				break;
			case 'Z':
				if (GetAttackPoint(&x, &y, &z) == TRUE)
				{
					pos.x = x;
					pos.y = y;
					pos.z = z;
					AssaParticle_ChainLance(&pos);
					switch (MotionEvent)
					{
					case 1:
						SkillPlaySound(SKILL_SOUND_SKILL_CHAIN_LANCE1, pX, pY, pZ);
						break;
					case 2:
						SkillPlaySound(SKILL_SOUND_SKILL_CHAIN_LANCE2, pX, pY, pZ);
						break;
					case 3:
						SkillPlaySound(SKILL_SOUND_SKILL_CHAIN_LANCE3, pX, pY, pZ);
						break;
					}
				}
				break;
			}
		}
		break;
	case snCHAR_SOUND_REVIVED_PRIESTESS:
		if (chrAttackTarget)
		{
			switch (MotionInfo->KeyCode)
			{
			case 'O':
				sinEffect_MultiSpark(this, chrAttackTarget, 5);
				SkillPlaySound(SKILL_SOUND_SKILL_MULTISPARK, pX, pY, pZ);
				break;
			case 'H':
				AssaParticle_VigorBall(this, chrAttackTarget);
				switch (rand() % 2)
				{
				case 0:
					SkillPlaySound(SKILL_SOUND_SKILL_VIGOR_BALL1, pX, pY, pZ);
					break;
				case 1:
					SkillPlaySound(SKILL_SOUND_SKILL_VIGOR_BALL2, pX, pY, pZ);
					break;
				}
				break;
			case 'Z':
				Angle.y = GetRadian2D(pX, pZ, chrAttackTarget->pX, chrAttackTarget->pZ);
				SkillCelestialGlacialSpike(this);
				GetMoveLocation(0, 0, 64 * fONE, 0, Angle.y, 0);
				SetDynLight(pX + GeoResult_X, pY, pZ + GeoResult_Z, 0, 0, 100, 0, 700);
				if (rand() % 2)
					SkillPlaySound(SKILL_SOUND_SKILL_GLACIAL_SPIKE1, pX, pY, pZ);
				else
					SkillPlaySound(SKILL_SOUND_SKILL_GLACIAL_SPIKE2, pX, pY, pZ);

				if (chrAttackTarget == lpCurPlayer)
				{
					lpCurPlayer->PlaySlowCount = 90;
					lpCurPlayer->AttackIce -= 160;
				}
				break;
			}
		}
		break;
	case snCHAR_SOUND_HOBOGOLEM:
		if (chrAttackTarget)
		{
			GetMoveLocation(7000, 30 * fONE, 50 * fONE, 0, Angle.y, 0);
			StartEffectMonsterDest(pX + GeoResult_X, pY + GeoResult_Y, pZ + GeoResult_Z,
				chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ,
				MONSTER_DMACHINE_MISSILE1);
		}
		break;


	case snCHAR_SOUND_SPRIN:
		if (chrAttackTarget && MotionInfo->KeyCode == 'J')
		{
			ParkAssaParticle_HellHoundSkillAttack(this);
		}
		break;
	case snCHAR_SOUND_XETAN:
		if (chrAttackTarget && MotionInfo->KeyCode == 'J')
		{
			ParkAssaParticle_DarkMageSkill(chrAttackTarget);
		}
		break;
	case snCHAR_SOUND_RUCA:
		if (chrAttackTarget && MotionInfo->KeyCode == 'J')
		{
			GetMoveLocation(0, 0, 64 * fONE, 0, Angle.y, 0);
			pos.x = pX + GeoResult_X;
			pos.y = pY + GeoResult_Y + 32 * fONE;
			pos.z = pZ + GeoResult_Z;
			AssaParticle_MonsterIronHit1(&pos);
		}
		break;
	case snCHAR_SOUND_NAZSENIOR:
		if (chrAttackTarget && MotionInfo->KeyCode == 'k')
		{
			GetMoveLocation(0, 0, 100 * fONE, 0, Angle.y, 0);
			StartSkillDest(pX, pY, pZ, pX + GeoResult_X, pY, pZ + GeoResult_Z, SKILL_TORNADO2, 1);
		}
		break;
	case snCHAR_SOUND_UNDEADMAPLE:
		if (chrAttackTarget && MotionInfo->KeyCode == 'J')
		{
			AssaParticle_EvilPlantShot(this);
		}
		break;



	case snCHAR_SOUND_WATERMELON:

		pos.x = pX;
		pos.y = pY;
		pos.z = pZ;
		pos2.x = chrAttackTarget->pX;
		pos2.y = chrAttackTarget->pY + 32 * fONE;
		pos2.z = chrAttackTarget->pZ;

		AssaParticle_IceShot(&pos, &pos2);
		break;

	}

	PlayAttack();
	CharPlaySound(this);

	return TRUE;
}


int smCHAR::EndSkill()
{
	int	point;
	int	param;

	point = (AttackSkil >> 8) & 0xF;
	param = (AttackSkil >> 12) & 0xF;

	switch (AttackSkil & 0xFF)
	{
	case SKILL_PLAY_DIASTROPHISM:
		if (this == lpCurPlayer && MotionEvent < 3)
		{

			dm_SelectRange(pX, pY, pZ, Diastrophism_Area[point - 1], FALSE);


			dm_SendRangeDamage(pX, pY, pZ, 0,
				cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[0],
				cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[1],
				0, 0, AttackSkil);
		}
		break;

	case SKILL_PLAY_METEO:
		if (chrAttackTarget && point)
		{
			if (this == lpCurPlayer && MotionEvent < 4)
			{

				dm_SelectRange(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, Meteo_Area[point - 1], FALSE);

				dm_SendRangeDamage(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 0, 0, 0, 0, 0, lpCurPlayer->AttackSkil);
			}
		}
		break;
	}

	MotionEvent++;

	return TRUE;
}


int smCHAR::EventSkill()
{
	int x, y, z;
	int	point;
	int	param;
	int	damage;
	int	temp;
	int cnt;
	POINT3D	Pos1, Pos2;
	RECT rect;
	smCHAR *lpChar;

	if (smCharInfo.State == smCHAR_STATE_ENEMY && PkMode_CharState != smCHAR_STATE_USER)
	{
		return EventSkill_Monster();
	}

	point = (AttackSkil >> 8) & 0xF;
	param = (AttackSkil >> 12) & 0xF;


	switch (AttackSkil & 0xFF)
	{
	case SKILL_PLAY_EXTREME_SHIELD:

		if (HvLeftHand.PatTool)
		{
			if (GetToolBipPoint(&HvLeftHand, &x, &y, &z))
			{
				StartSkill(x, y, z, 0, 0, 0, SKILL_EXTREME_SHIELD);
			}
		}
		break;

	case SKILL_PLAY_MECHANIC_BOMB:

		if (chrAttackTarget)
		{
			if (point)
			{
				damage = GetRandomPos(Mechanic_Bomb_Damage[point - 1][0], Mechanic_Bomb_Damage[point - 1][1]) / 2;
				StartSkillDest(pX, pY + 30 * fONE, pZ, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, SKILL_MECHANIC_BOMB, point);
				SkillPlaySound(SKILL_SOUND_MECHANIC_BOMB1, pX, pY, pZ);

				if (this == lpCurPlayer)
				{


					dm_SelectRange(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 80 + (point * 5), FALSE);

					dm_SendRangeDamage(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil);
				}
			}
		}
		break;
	case SKILL_PLAY_PHYSICAL_ABSORB:

		break;

	case SKILL_PLAY_RAVING:

		return FALSE;

	case SKILL_PLAY_IMPACT:

		if (this == lpCurPlayer && chrAttackTarget && MotionEvent < 2)
		{
			if (AttackCritcal >= 0)
			{
				temp = smCharInfo.Attack_Rating;
				smCharInfo.Attack_Rating += Impact_Attack_Rating[point - 1];


				cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
				smCharInfo.Attack_Rating = temp;

				if (cnt > 0)
				{
					DamageExp(chrAttackTarget, cnt);
					if (AttackExp)
					{


						AttackExp = 0;
					}
				}
			}
		}
		return FALSE;

	case SKILL_PLAY_PIKEWIND:

		if (point)
		{
			StartSkill(pX, pY, pZ, 0, 0, 0, SKILL_PIKE_WIND, point);
			SkillPlaySound(SKILL_SOUND_PIKE_WIND, pX, pY, pZ);
		}
		break;

	case SKILL_PLAY_CRITICAL_HIT:

		return FALSE;

	case SKILL_PLAY_JUMPING_CRASH:

		if (AttackSkil >= 0)
			SkillPlaySound(SKILL_SOUND_JUMPING_CRASH2, pX, pY, pZ);
		return FALSE;


	case SKILL_PLAY_WIND_ARROW:

		if (chrAttackTarget)
		{
			GetAttackPoint(&x, &y, &z);
			StartSkillDest(x, y, z, chrAttackTarget->pX, chrAttackTarget->pY + (24 * fONE), chrAttackTarget->pZ, SKILL_WIND_ARROW);
			SkillPlaySound(SKILL_SOUND_WIND_ARROW, pX, pY, pZ);
		}
		break;

	case SKILL_PLAY_PERFECT_AIM:

		if (chrAttackTarget)
		{
			GetAttackPoint(&x, &y, &z);
			StartSkillDest(x, y, z, chrAttackTarget->pX, chrAttackTarget->pY + (24 * fONE), chrAttackTarget->pZ, SKILL_PERFECT_AIM);
			SkillPlaySound(SKILL_SOUND_PERFECT_AIM, pX, pY, pZ);
		}
		break;


	case SKILL_PLAY_GREAT_SMASH:

		if (GetAttackPoint(&x, &y, &z) == TRUE)
		{
			if (dwActionItemCode)
			{

				StartSkill(x, y, z, 0, Angle.y, 0, SKILL_GREAT_SMASH);
				SkillPlaySound(SKILL_SOUND_SKILL_SWING1, pX, pY, pZ);
			}
		}
		break;

	case SKILL_PLAY_SPARK:

		if (chrAttackTarget)
		{
			if (point)
			{

				StartSkillDest(pX, pY + 24 * fONE, pZ, chrAttackTarget->pX, chrAttackTarget->pY + 24 * fONE, chrAttackTarget->pZ, SKILL_SPARK, point);


				if (this == lpCurPlayer)
				{


					dm_SelectRange(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 80 + (point * 5), FALSE);

					dm_SendRangeDamage(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 0, 0, 0, 0, 0, lpCurPlayer->AttackSkil);

				}
				SkillPlaySound(SKILL_SOUND_SKILL_SPARK2, pX, pY, pZ);
			}
		}
		break;

	case SKILL_PLAY_GRAND_SMASH:


		if (dwActionItemCode && AttackCritcal >= 0)
		{

			AssaParticle_GrandSmash(this);
			SkillPlaySound(SKILL_SOUND_SKILL_SWING2, pX, pY, pZ);
		}
		else
		{


			PlayWaponSoundDirect(pX, pY, pZ, 13);
		}


		if (this == lpCurPlayer && chrAttackTarget && MotionEvent == 1)
		{
			temp = smCharInfo.Attack_Rating;
			smCharInfo.Attack_Rating += Grand_Smash_AttackRate[point - 1];

			cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
			smCharInfo.Attack_Rating = temp;

			if (!cnt)
				AttackCritcal = -1;
			else
				AttackCritcal = 0;
		}

		break;

	case SKILL_PLAY_SPARK_SHIELD:

		if (HvLeftHand.PatTool)
		{

			AssaParticle_SparkShieldStart(this, Spark_Shield_Time[point - 1]);
			SkillPlaySound(SKILL_SOUND_SKILL_SPARK3, pX, pY, pZ);

		}
		break;


	case SKILL_PLAY_GROUND_PIKE:

		if (point)
		{
			GetMoveLocation(0, 0, 32 * fONE, 0, Angle.y, 0);
			StartSkill(pX + GeoResult_X, pY, pZ + GeoResult_Z, 0, Angle.y, 0, SKILL_GROUND_PIKE, point);
			SetDynLight(pX, pY, pZ, 0, 0, 100, 0, 700);

			SkillPlaySound(SKILL_SOUND_SKILL_GROUND_PIKE, pX, pY, pZ);
		}
		break;

	case SKILL_PLAY_EXPANSION:

		SkillPlaySound(SKILL_SOUND_SKILL_EXPANSION2, pX, pY, pZ);
		if (GetAttackPoint(&x, &y, &z) == TRUE)
		{
			if (dwActionItemCode)
			{
				StartSkill(x, y, z, 0, Angle.y, 0, SKILL_GREAT_SMASH);

				SetDynLight(x, y, z, 100, 0, 0, 0, 400);
			}
		}
		return FALSE;


	case SKILL_PLAY_TORNADO:

		if (chrAttackTarget)
		{
			x = (pX - chrAttackTarget->pX) >> FLOATNS;
			z = (pZ - chrAttackTarget->pZ) >> FLOATNS;

			if ((x*x + z * z) < (50 * 50))
			{
				y = GetRadian2D(pX, pZ, chrAttackTarget->pX, chrAttackTarget->pZ);

				GetMoveLocation(0, 0, 50 * fONE, 0, y, 0);
				x = pX + GeoResult_X;
				z = pZ + GeoResult_Z;
				y = chrAttackTarget->pY;
				StartSkillDest(pX, pY, pZ, x, y, z, SKILL_TORNADO, point);

			}
			else
			{
				StartSkillDest(pX, pY, pZ, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, SKILL_TORNADO, point);
			}

			SkillPlaySound(SKILL_SOUND_SKILL_TORNADO1, pX, pY, pZ);
		}
		break;

	case SKILL_PLAY_VENOM_SPEAR:



		if (this == lpCurPlayer)
		{

			dm_SelectDamageCount(this, VenomSpear_Num[point - 1], VenomSpear_Range[point - 1]);

			dm_SendRangeDamage(pX, pY, pZ, 0, smCharInfo.Attack_Damage[0], smCharInfo.Attack_Damage[1], 0, 0, AttackSkil);
		}
		SkillPlaySound(SKILL_SOUND_SKILL_VENOM_SPEAR1, pX, pY, pZ);

		if (SkillPlay_VenomSpear_Effect(this, point) > 0)
		{
			SkillPlaySound(SKILL_SOUND_SKILL_VENOM_SPEAR2, pX, pY, pZ);
		}
		break;

	case SKILL_PLAY_VANISH:


		SkillPlaySound(SKILL_SOUND_SKILL_VANISH2, pX, pY, pZ);

		if (lpCurPlayer == this)
		{
			PlayVanish = Vanish_Time[point - 1] * 70;
			PlayVague = 0;
			SendProcessSKillToServer(SKILL_PLAY_VANISH, point, 0, 0);

			if (IsCreateNewRenderTarget())
			{
				dwM_BlurTime = dwPlayTime + Vanish_Time[point - 1] * 1000;
				SetFilterEffect(FILTER_EFFECT_SET_MOTION_BLUR, 80);
			}
		}
		break;

	case SKILL_PLAY_CHAIN_LANCE:

		if (chrAttackTarget && GetAttackPoint(&x, &y, &z) == TRUE)
		{
			Pos1.x = x;
			Pos1.y = y;
			Pos1.z = z;
			if (lpCurPlayer->AttackCritcal >= 0)
			{
				AssaParticle_ChainLance(&Pos1);

				switch (MotionEvent)
				{
				case 1:
					SkillPlaySound(SKILL_SOUND_SKILL_CHAIN_LANCE1, pX, pY, pZ);
					break;
				case 2:
					SkillPlaySound(SKILL_SOUND_SKILL_CHAIN_LANCE2, pX, pY, pZ);
					break;
				case 3:
					SkillPlaySound(SKILL_SOUND_SKILL_CHAIN_LANCE3, pX, pY, pZ);
					break;
				}
			}
			else
			{


				PlayWaponSoundDirect(pX, pY, pZ, 13);
			}
		}

		if (this == lpCurPlayer && MotionEvent < 3 && chrAttackTarget)
		{




			cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, TRUE);
			if (!cnt)
				lpCurPlayer->AttackCritcal = -1;
			else
				lpCurPlayer->AttackCritcal = 0;


		}
		break;

	case SKILL_PLAY_FALCON:

		break;

	case SKILL_PLAY_ARROWOF_RAGE:

		if (chrAttackTarget && GetAttackPoint(&x, &y, &z) == TRUE)
		{
			StartSkillDest(x, y, z, chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, SKILL_ARROW_OF_RAGE, point);


			if (this == lpCurPlayer && chrAttackTarget)
			{



				dm_SelectRange(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, A_Rage_Area[point - 1], FALSE);

				dm_SendRangeDamage(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 0, 0, 0, 0, 0, lpCurPlayer->AttackSkil);

			}
			SkillPlaySound(SKILL_SOUND_WIND_ARROW, pX, pY, pZ);
		}
		break;

	case SKILL_PLAY_AVALANCHE:

		if (chrAttackTarget && GetAttackPoint(&x, &y, &z) == TRUE)
		{

			if (AttackCritcal >= 0)
			{
				StartSkillDest(x, y, z, chrAttackTarget->pX, chrAttackTarget->pY + (24 * fONE), chrAttackTarget->pZ, SKILL_AVALANCHE);

				switch (rand() % 3)
				{
				case 0:
					SkillPlaySound(SKILL_SOUND_SKILL_AVALANCHE1, pX, pY, pZ);
					break;
				case 1:
					SkillPlaySound(SKILL_SOUND_SKILL_AVALANCHE2, pX, pY, pZ);
					break;
				case 2:
					SkillPlaySound(SKILL_SOUND_SKILL_AVALANCHE3, pX, pY, pZ);
					break;
				}
			}
			else
				WeaponPlaySound(this);

		}
		break;

	case SKILL_PLAY_ELEMENTAL_SHOT:

		if (chrAttackTarget && GetAttackPoint(&x, &y, &z) == TRUE)
		{
			if (AttackCritcal >= 0)
			{

				Pos1.x = x;
				Pos1.y = y;
				Pos1.z = z;

				Pos2.x = chrAttackTarget->pX;
				Pos2.y = chrAttackTarget->pY + (24 * fONE);
				Pos2.z = chrAttackTarget->pZ;

				if (AttackCritcal >= 0)
				{
					switch (param)
					{
					case 0:
						AssaParticle_ElementalShotFire(&Pos1, &Pos2);


						break;
					case 1:
						AssaParticle_ElementalShotLighting(&Pos1, &Pos2);
						break;
					}
					SkillPlaySound(SKILL_SOUND_SKILL_ELEMENTAL_SHOT, pX, pY, pZ);
				}
			}
		}
		break;

	case SKILL_PLAY_BOMB_SHOT:

		if (chrAttackTarget && GetAttackPoint(&x, &y, &z) == TRUE)
		{
			if (AttackCritcal >= 0)
			{
				Pos1.x = x;
				Pos1.y = y;
				Pos1.z = z;

				Pos2.x = chrAttackTarget->pX;
				Pos2.y = chrAttackTarget->pY + (24 * fONE);
				Pos2.z = chrAttackTarget->pZ;

				AssaParticle_BombShot(&Pos1, &Pos2);

				SkillPlaySound(SKILL_SOUND_SKILL_BOMB_SHOT1, pX, pY, pZ);

			}
		}
		break;

	case SKILL_PLAY_PERFORATION:

		if (chrAttackTarget && GetAttackPoint(&x, &y, &z) == TRUE)
		{
			if (AttackCritcal >= 0)
			{
				Pos1.x = x;
				Pos1.y = y;
				Pos1.z = z;

				Pos2.x = chrAttackTarget->pX;
				Pos2.y = chrAttackTarget->pY + (24 * fONE);
				Pos2.z = chrAttackTarget->pZ;

				AssaParticle_Perforation(&Pos1, &Pos2);
				SkillPlaySound(SKILL_SOUND_SKILL_PERFORATION, pX, pY, pZ);

				rect.left = -40;
				rect.right = 40;
				rect.top = 0;
				rect.bottom = 240;
				rect.bottom += 20;
				rect.bottom += 20;


				dm_SelectRangeBox(this, &rect, FALSE);

				for (cnt = 0; cnt < dmSelected_CharCnt; cnt++)
				{
					if (lpSelected_Char[cnt])
					{
						AssaParticle_PerforationHit(lpSelected_Char[cnt], this, 0.5f);
					}
				}
			}
		}
		break;

	case SKILL_PLAY_TRIPLE_IMPACT:

		if (AttackCritcal >= 0)
		{
			if (GetAttackPoint(&x, &y, &z) == TRUE)
			{
				StartSkill(x, y, z, 0, 0, 0, SKILL_TRIPLE_IMPACT);
				SetDynLight(x, y, z, 100, 0, 0, 0, 400);
			}

			AttackCritcal = 1;
		}
		WeaponPlaySound(this);

		if (this == lpCurPlayer && chrAttackTarget && MotionEvent < T_Impact_Hit[point - 1])
		{
			if (AttackCritcal >= 0)
			{

				cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);

				if (cnt > 0)
				{
					DamageExp(chrAttackTarget, cnt);
					if (AttackExp)
					{


						AttackExp = 0;
					}
				}
			}
		}
		break;

	case SKILL_PLAY_BRUTAL_SWING:

		if (AttackCritcal >= 0)
		{
			if (GetAttackPoint(&x, &y, &z) == TRUE)
			{
				StartSkill(x, y, z, 0, 0, 0, SKILL_BRUTAL_SWING);
				SetDynLight(x, y, z, 100, 0, 0, 0, 400);
				SkillPlaySound(SKILL_SOUND_SKILL_SWING1, pX, pY, pZ);
			}
		}
		else
			WeaponPlaySound(this);
		break;

	case SKILL_PLAY_RAGEOF_ZECRAM:
		if (GetAttackPoint(&x, &y, &z) == TRUE)
		{
			if (MotionEvent == 1)
			{
				StartSkill(x, y, z, 0, 0, 0, SKILL_RAGE_OF_ZECRAM_HIT1);

				AddTimeEffect(SKILL_RAGE_OF_ZECRAM_HIT2, dwPlayTime + 600, x, y, z);

				if (this == lpCurPlayer && chrAttackTarget)
				{



					dm_SelectRange(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 70, FALSE);

					dm_SendRangeDamage(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, 0, 0, lpCurPlayer->AttackSkil);

					SkillPlaySound(SKILL_SOUND_SKILL_RAGE_OF_ZECRAM1, pX, pY, pZ, FALSE);
					SetDynLight(x, y, z, 100, 0, 0, 0, 400);

				}
			}
		}
		break;
	case SKILL_PLAY_ROAR:


		break;

	case SKILL_PLAY_AVANGING_CRASH:

		if (GetAttackPoint(&x, &y, &z) == TRUE)
		{
			Pos1.x = x;
			Pos1.y = y;
			Pos1.z = z;

			if (AttackCritcal >= 0)
			{
				AssaParticle_AvangingCrash(this);
				SkillPlaySound(SKILL_SOUND_SKILL_AVANGING_CRASH, pX, pY, pZ);
			}
			else
			{


				PlayWaponSoundDirect(pX, pY, pZ, 13);
			}
		}

		if (this == lpCurPlayer && MotionEvent == 1 && chrAttackTarget)
		{

			x = lpCurPlayer->smCharInfo.Attack_Rating;

			smCharInfo.Attack_Rating += (smCharInfo.Attack_Rating * A_Crash_AttackRate[point - 1]) / 100;

			cnt = dm_SendTransDamage(chrAttackTarget, cSkill.GetSkillPoint(SKILL_BRUTAL_SWING), 0, 0, 0, AttackSkil, TRUE);

			if (!cnt)
				AttackCritcal = -1;
			else
			{

				DamageExp(chrAttackTarget, cnt);
				AttackCritcal = 0;
			}
			smCharInfo.Attack_Rating = x;
		}

		break;

	case SKILL_PLAY_BONE_SMASH:


		if (AttackCritcal >= 0)
		{
			AssaParticle_BoneSmash1(this);
			SkillPlaySound(SKILL_SOUND_SKILL_BONE_CRASH1, pX, pY, pZ, FALSE);
		}
		else
		{


			PlayWaponSoundDirect(pX, pY, pZ, 13);
		}



		if (this == lpCurPlayer && MotionEvent == 1 && chrAttackTarget)
		{

			cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, TRUE);

			if (!cnt)
				AttackCritcal = -1;
			else
			{

				DamageExp(chrAttackTarget, cnt);
				AttackCritcal = 0;
			}
		}

		break;


	case SKILL_PLAY_HOLY_BODY:
		break;

	case SKILL_PLAY_SWORD_BLAST:

		if (chrAttackTarget)
		{
			sinEffect_Sword_Blast(this, chrAttackTarget);

			SkillPlaySound(SKILL_SOUND_SKILL_SWORDBLAST2, pX, pY, pZ);
		}
		break;

	case SKILL_PLAY_DOUBLE_CRASH:
		if (AttackCritcal >= 0)
		{
			if (GetAttackPoint(&x, &y, &z) == TRUE)
			{
				if (AttackCritcal == 0)
				{
					StartEffect(x, y, z, EFFECT_NORMAL_HIT1);
					SetDynLight(x, y, z, 80, 0, 0, 0, 300);
				}
				else
				{
					StartEffect(x, y, z, EFFECT_CRITICAL_HIT1);
					SetDynLight(x, y, z, 100, 0, 0, 0, 400);
				}
			}
		}
		WeaponPlaySound(this);

		if (this == lpCurPlayer && chrAttackTarget && MotionEvent < 2)
		{


			cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);

			if (cnt > 0)
			{
				lpCurPlayer->AttackCritcal = 0;
				DamageExp(chrAttackTarget, cnt);
				if (AttackExp)
				{


					AttackExp = 0;
				}
			}
			else
				lpCurPlayer->AttackCritcal = -1;
		}
		break;


	case SKILL_PLAY_HOLY_VALOR:
		if (this == lpCurPlayer)
		{

			SendPartySkillToServer(SKILL_PLAY_HOLY_VALOR, point, 200, 0, 0, 0, 0);
		}
		break;

	case SKILL_PLAY_BRANDISH:
		sinSkillEffect_Brandish(this);
		SkillPlaySound(SKILL_SOUND_SKILL_BLANDISH2, pX, pY, pZ);
		break;

	case SKILL_PLAY_PIERCING:
		sinSkillEffect_Piercing_Attack(this);
		break;

	case SKILL_PLAY_FLAME_BRANDISH:
		AssaParticle_FlameBrandish(this);
		SkillPlaySound(SKILL_SOUND_SKILL_FLAME_BRANDISH, pX, pY, pZ);

		if (chrAttackTarget)
		{

			dm_SelectRange(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 80, FALSE);
			for (cnt = 0; cnt < dmSelected_CharCnt; cnt++)
			{
				if (lpSelected_Char[cnt])
				{
					AssaParticle_FlameBrandishHit1(lpSelected_Char[cnt]);
				}
			}
		}
		break;

	case SKILL_PLAY_DIVINE_INHALATION:

		AssaParticle_DivineInhalationStart(this, D_Inhalation_Time[point - 1]);
		break;

	case SKILL_PLAY_HOLY_INCANTATION:
		if (chrAttackTarget)
		{
			AssaParticle_HolyIncantationShot(chrAttackTarget);

			SkillPlaySound(SKILL_SOUND_SKILL_HOLY_INCANTATION, pX, pY, pZ);

			if (this == lpCurPlayer)
				dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil, FALSE);
		}
		break;

	case SKILL_PLAY_GRAND_CROSS:
		if (chrAttackTarget && AttackCritcal >= 0 && GetAttackPoint(&x, &y, &z) == TRUE)
		{
			Pos1.x = x;
			Pos1.y = y;
			Pos1.z = z;
			if (MotionEvent == 1)
			{
				AssaParticle_GrandCrossHorz(&Pos1, Angle.y);
				SkillPlaySound(SKILL_SOUND_SKILL_SWING2, pX, pY, pZ);
			}
			else
			{
				AssaParticle_GrandCrossVert(&Pos1, Angle.y);
				SkillPlaySound(SKILL_SOUND_SKILL_GRAND_CROSS, pX, pY, pZ);
			}
		}
		else
		{


			PlayWaponSoundDirect(pX, pY, pZ, 13);
		}

		if (this == lpCurPlayer && chrAttackTarget && MotionEvent == 1)
		{

			x = smCharInfo.Attack_Rating;

			smCharInfo.Attack_Rating += (smCharInfo.Attack_Rating*Grand_Cross_AttackRate[point - 1]) / 100;

			cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);

			if (cnt > 0)
				lpCurPlayer->AttackCritcal = 0;
			else
				lpCurPlayer->AttackCritcal = -1;

			smCharInfo.Attack_Rating = x;
		}

		break;




	case SKILL_PLAY_SHIELD_STRIKE:
		SkillPlaySound(SKILL_SOUND_SKILL_SHIELDSTRIKE, pX, pY, pZ);
		break;

	case SKILL_PLAY_VIGOR_SPEAR:
		if (chrAttackTarget && GetAttackPoint(&x, &y, &z) == TRUE)
		{
			sinEffect_VigorSpear(this, chrAttackTarget);

			SkillPlaySound(SKILL_SOUND_SKILL_VIGORSPEAR, pX, pY, pZ);
		}
		break;

	case SKILL_PLAY_FARINA:
		if (chrAttackTarget && AttackCritcal >= 0)
			SkillPlaySound(SKILL_SOUND_SKILL_FARINA, pX, pY, pZ);

		return FALSE;

	case SKILL_PLAY_TWIST_JAVELIN:
		if (chrAttackTarget && AttackCritcal >= 0 && GetAttackPoint(&x, &y, &z) == TRUE)
		{

			Pos1.x = x;
			Pos1.y = y;
			Pos1.z = z;
			Pos2.x = chrAttackTarget->pX;
			Pos2.y = chrAttackTarget->pY + 28 * fONE;
			Pos2.z = chrAttackTarget->pZ;

			AssaParticle_TwistJavelinShot(&Pos1, &Pos2);
			SkillPlaySound(SKILL_SOUND_SKILL_TWISTJAVELIN, pX, pY, pZ);
		}
		return FALSE;

	case SKILL_PLAY_SOUL_SUCKER:

		rect.left = -30;
		rect.right = 30;
		rect.top = 0;
		rect.bottom = 200;
		if (Skil_RangeBoxEffect(this, &rect, SKILL_PLAY_SOUL_SUCKER, 0) > 0)
			SkillPlaySound(SKILL_SOUND_SKILL_SOULSUCKER2, pX, pY, pZ);
		else
			SkillPlaySound(SKILL_SOUND_SKILL_SHIELDSTRIKE, pX, pY, pZ);
		break;

	case SKILL_PLAY_FIRE_JAVELIN:
		if (chrAttackTarget && AttackCritcal >= 0 && GetAttackPoint(&x, &y, &z) == TRUE)
		{

			Pos1.x = x;
			Pos1.y = y;
			Pos1.z = z;
			Pos2.x = chrAttackTarget->pX;
			Pos2.y = chrAttackTarget->pY + 28 * fONE;
			Pos2.z = chrAttackTarget->pZ;

			AssaParticle_FireJavelin(&Pos1, &Pos2);
			SkillPlaySound(SKILL_SOUND_SKILL_FIREJAVELIN, pX, pY, pZ);
		}

		return FALSE;

	case SKILL_PLAY_SPLIT_JAVELIN:
		if (chrAttackTarget && AttackCritcal >= 0 && GetAttackPoint(&x, &y, &z) == TRUE)
		{

			SkillPlaySound(SKILL_SOUND_SKILL_SPLIT_JAVELIN2, pX, pY, pZ);

		}
		return TRUE;

	case SKILL_PLAY_TRIUMPH_OF_VALHALLA:
		if (chrAttackTarget)
		{
			if (chrAttackTarget->smCharInfo.State == smCHAR_STATE_USER)
			{
				AssaParticle_TriumphOfValhallaMember(this, chrAttackTarget, T_Of_Valhalla_Time[point - 1]);
				if (this == lpCurPlayer)
				{
					SendProcessSKillToServer(SKILL_PLAY_TRIUMPH_OF_VALHALLA, point, chrAttackTarget->dwObjectSerial, smCharInfo.Level);
				}
			}
		}
		else
		{
			AssaParticle_TriumphOfValhalla(this, T_Of_Valhalla_Time[point - 1]);
		}
		break;

	case SKILL_PLAY_LIGHTNING_JAVELIN:
		if (chrAttackTarget && GetAttackPoint(&x, &y, &z) == TRUE)
		{
			Pos1.x = x;
			Pos1.y = y;
			Pos1.z = z;
			Pos2.x = chrAttackTarget->pX;
			Pos2.y = chrAttackTarget->pY + 28 * fONE;
			Pos2.z = chrAttackTarget->pZ;

			AssaParticle_LightingJavelin(&Pos1, &Pos2);
			switch (rand() % 2)
			{
			case 0:
				SkillPlaySound(SKILL_SOUND_SKILL_LIGHTNING_JAVELIN1, pX, pY, pZ);
				break;
			case 1:
				SkillPlaySound(SKILL_SOUND_SKILL_LIGHTNING_JAVELIN2, pX, pY, pZ);
				break;
			}
		}
		break;

	case SKILL_PLAY_STORM_JAVELIN:
		if (chrAttackTarget && AttackCritcal >= 0 && GetAttackPoint(&x, &y, &z) == TRUE)
		{
			Pos1.x = x;
			Pos1.y = y;
			Pos1.z = z;
			Pos2.x = chrAttackTarget->pX;
			Pos2.y = chrAttackTarget->pY + 28 * fONE;
			Pos2.z = chrAttackTarget->pZ;

			AssaParticle_StormJavelin(&Pos1, &Pos2);

			rect.left = -30;
			rect.right = 30;
			rect.top = 0;
			rect.bottom = 240;
			rect.bottom += 20;
			rect.bottom += 20;


			dm_SelectRangeBox(this, &rect, FALSE);

			for (cnt = 0; cnt < dmSelected_CharCnt; cnt++)
			{
				if (lpSelected_Char[cnt])
				{
					AssaParticle_StormJavelinHit(lpSelected_Char[cnt], this, 0.5f);
				}
			}

			switch (rand() % 2)
			{
			case 0:
				SkillPlaySound(SKILL_SOUND_SKILL_STORM_JAVELIN1, pX, pY, pZ);
				break;
			case 1:
				SkillPlaySound(SKILL_SOUND_SKILL_STORM_JAVELIN2, pX, pY, pZ);
				break;
			}
		}

		return TRUE;




	case SKILL_PLAY_HOLY_BOLT:
		if (chrAttackTarget)
		{
			GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);

			StartEffectMonsterDest(pX + GeoResult_X, pY + GeoResult_Y, pZ + GeoResult_Z,
				chrAttackTarget->pX, chrAttackTarget->pY + 20 * fONE, chrAttackTarget->pZ,
				MONSTER_MEPHIT_SHOT2);

			SkillPlaySound(SKILL_SOUND_SKILL_HOLYBOLT, pX, pY, pZ);
		}
		break;

	case SKILL_PLAY_MULTI_SPARK:
		if (chrAttackTarget)
		{
			sinEffect_MultiSpark(this, chrAttackTarget, param);

			SkillPlaySound(SKILL_SOUND_SKILL_MULTISPARK, pX, pY, pZ);
		}
		break;

	case SKILL_PLAY_DIVINE_LIGHTNING:


		if (this == lpCurPlayer)
		{

			dm_SelectDamageCount(this, Divine_Lightning_Num[point - 1], 180);

			dm_SendRangeDamage(pX, pY, pZ, 0,
				cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[0],
				cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[1],
				0, 0, AttackSkil);
		}

		if (SkillPlay_DivineLightning_Effect(this, point) > 0)
		{
			switch (rand() % 3)
			{
			case 0:
				SkillPlaySound(SKILL_SOUND_SKILL_DIVINELIGHTNING1, pX, pY, pZ);
				break;
			case 1:
				SkillPlaySound(SKILL_SOUND_SKILL_DIVINELIGHTNING2, pX, pY, pZ);
				break;
			case 2:
				SkillPlaySound(SKILL_SOUND_SKILL_DIVINELIGHTNING3, pX, pY, pZ);
				break;
			}
		}
		break;

	case SKILL_PLAY_HOLY_REFLECTION:
		if (this == lpCurPlayer)
		{
			SendProcessSKillToServer(SKILL_PLAY_HOLY_REFLECTION, point, 0, 0);
		}
		break;
	case SKILL_PLAY_GREAT_HEALING:
		if (this == lpCurPlayer)
		{

			int dist, ddist;

			ddist = Grand_Healing_Range[point - 1];
			ddist *= ddist;


			for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
			{
				if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].dwObjectSerial &&
					chrOtherPlayer[cnt].smCharInfo.State == smCHAR_STATE_USER &&
					chrOtherPlayer[cnt].PartyFlag &&
					chrOtherPlayer[cnt].MotionInfo->State != CHRMOTION_STATE_DEAD)
				{

					x = (chrOtherPlayer[cnt].pX - lpCurPlayer->pX) >> FLOATNS;
					y = (chrOtherPlayer[cnt].pY - lpCurPlayer->pY) >> FLOATNS;
					z = (chrOtherPlayer[cnt].pZ - lpCurPlayer->pZ) >> FLOATNS;
					dist = x * x + y * y + z * z;

					if (dist < ddist)
					{
						sinSkillEffect_Great_Healing_Party(&chrOtherPlayer[cnt]);
					}
				}
			}

		}
		break;


	case SKILL_PLAY_VIGOR_BALL:
		if (chrAttackTarget)
		{
			if (this == lpCurPlayer && MotionEvent < 3)
			{
				cnt = dm_SendTransDamage(chrAttackTarget,
					cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[0],
					cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[1],
					0, 0, AttackSkil, FALSE);
			}

			AssaParticle_VigorBall(this, chrAttackTarget);

			switch (rand() % 2)
			{
			case 0:
				SkillPlaySound(SKILL_SOUND_SKILL_VIGOR_BALL1, pX, pY, pZ);
				break;
			case 1:
				SkillPlaySound(SKILL_SOUND_SKILL_VIGOR_BALL2, pX, pY, pZ);
				break;
			}
		}
		break;

	case SKILL_PLAY_RESURRECTION:



		if (this == lpCurPlayer)
		{
			lpChar = FindDeadPartyUser();
			if (lpChar)
			{
				SendProcessSKillToServer(SKILL_PLAY_RESURRECTION, point, lpChar->dwObjectSerial, 0);
				chrAttackTarget = lpChar;
			}
			else
				chrAttackTarget = 0;
		}

		if (chrAttackTarget)
			AssaParticle_ResurrectionShot(chrAttackTarget);

		break;

	case SKILL_PLAY_EXTINCTION:

		break;

	case SKILL_PLAY_VIRTUAL_LIFE:
		if (chrAttackTarget)
		{
			AssaParticle_VirtualLife(chrAttackTarget, Virtual_Life_Time[point - 1]);
		}
		else
		{
			AssaParticle_VirtualLife(this, Virtual_Life_Time[point - 1]);
		}
		SkillPlaySound(SKILL_SOUND_SKILL_VIRTUAL_LIFE, pX, pY, pZ);
		break;



	case SKILL_PLAY_FIRE_BOLT:
		if (chrAttackTarget)
		{

			GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);

			StartEffectMonsterDest(pX + GeoResult_X, pY + GeoResult_Y, pZ + GeoResult_Z,
				chrAttackTarget->pX, chrAttackTarget->pY + 20 * fONE, chrAttackTarget->pZ,
				MONSTER_IMP_SHOT2);

			if (((dwPlayTime >> 4) & 1) == 0)
				SkillPlaySound(SKILL_SOUND_SKILL_FIREBOLT1, pX, pY, pZ);
			else
				SkillPlaySound(SKILL_SOUND_SKILL_FIREBOLT2, pX, pY, pZ);

		}
		break;

	case SKILL_PLAY_FIRE_BALL:
		if (chrAttackTarget)
		{
			GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);
			StartEffectMonsterDest(pX + GeoResult_X, pY + GeoResult_Y, pZ + GeoResult_Z,
				chrAttackTarget->pX, chrAttackTarget->pY + 20 * fONE, chrAttackTarget->pZ,
				MONSTER_PIGON_SHOT1);

			if (((dwPlayTime >> 4) & 1) == 0)
				SkillPlaySound(SKILL_SOUND_SKILL_FIREBALL1, pX, pY, pZ);
			else
				SkillPlaySound(SKILL_SOUND_SKILL_FIREBALL2, pX, pY, pZ);
		}
		break;

	case SKILL_PLAY_COLUMN_OF_WATER:
		if (chrAttackTarget)
		{
			Pos1.x = pX;
			Pos1.y = pY;
			Pos1.z = pZ;
			Pos2.x = chrAttackTarget->pX;
			Pos2.y = chrAttackTarget->pY;
			Pos2.z = chrAttackTarget->pZ;

			AssaParticle_ColumnOfWater(&Pos1, &Pos2, point);

			switch (rand() % 2)
			{
			case 0:
				SkillPlaySound(SKILL_SOUND_SKILL_WATORNADO1, pX, pY, pZ);
				break;
			case 1:
				SkillPlaySound(SKILL_SOUND_SKILL_WATORNADO2, pX, pY, pZ);
				break;
			}
		}
		break;

	case SKILL_PLAY_ENCHANT_WEAPON:
		if (chrAttackTarget)
		{
			AssaParticle_EnchantWeaponJinMember(chrAttackTarget);

			SendProcessSKillToServer(SKILL_PLAY_ENCHANT_WEAPON, point, chrAttackTarget->dwObjectSerial, param);
		}
		else
		{
			if (this == lpCurPlayer)
			{
				SendProcessSKillToServer(SKILL_PLAY_ENCHANT_WEAPON, point, lpCurPlayer->dwObjectSerial, param);
				cSkill.SetEnchant_Weapon(Enchant_Weapon_Time[point - 1], point);
			}
		}
		break;

	case SKILL_PLAY_DEAD_RAY:
		if (chrAttackTarget)
		{
			GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);
			Pos1.x = pX + GeoResult_X;
			Pos1.y = pY + GeoResult_Y;
			Pos1.z = pZ + GeoResult_Z;
			Pos2.x = chrAttackTarget->pX;
			Pos2.y = chrAttackTarget->pY + 32 * fONE;
			Pos2.z = chrAttackTarget->pZ;

			AssaParticle_DeadLay(&Pos1, &Pos2);
			SkillPlaySound(SKILL_SOUND_SKILL_DEATHRAY, pX, pY, pZ);
		}
		break;


	case SKILL_PLAY_ENERGY_SHIELD:
		AssaParticle_EnergyShield(this, Energy_Shield_Time[point - 1]);
		SkillPlaySound(SKILL_SOUND_SKILL_ENERGY_SHIELD, pX, pY, pZ);
		break;

	case SKILL_PLAY_DIASTROPHISM:
		AssaParticle_Diastrophism(this);
		SkillPlaySound(SKILL_SOUND_SKILL_DIASTROPHISM, pX, pY, pZ);

		if (this == lpCurPlayer && MotionEvent < 2)
		{

			dm_SelectRange(pX, pY, pZ, Diastrophism_Area[point - 1], FALSE);


			dm_SendRangeDamage(pX, pY, pZ, 0,
				cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[0],
				cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[1],
				0, 0, AttackSkil);
		}
		break;

	case SKILL_PLAY_SPIRIT_ELEMENTAL:
		AssaParticle_SpiritElemental(this, Spirit_Elemental_Time[point - 1]);
		SkillPlaySound(SKILL_SOUND_SKILL_SPIRIT_ELEMENTAL, pX, pY, pZ);
		break;

	case SKILL_PLAY_DANCING_SWORD:
		switch (param)
		{
		case 0:
			AssaParticle_DancingSwordIce(this, Dancing_Sword_Time[point - 1], point);
			break;

		case 1:
			AssaParticle_DancingSwordFire(this, Dancing_Sword_Time[point - 1], point);
			break;
		}
		SkillPlaySound(SKILL_SOUND_SKILL_DANCING_SWORD, pX, pY, pZ);
		break;



	case SKILL_PLAY_IMPULSION:
		if (point && chrAttackTarget)
		{

			if (GetAttackPoint(&Pos2.x, &Pos2.y, &Pos2.z) == TRUE)
			{
				SkillImpulsionLightHit(&Pos2);
			}

			if (lpCurPlayer != this)
			{

				dm_SelectRange(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, Impulsion_Range[point - 1], TRUE, Impulsion_LightingNum[point - 1]);
			}
			else
			{
				if (MotionEvent == 1)
					dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil, FALSE);
			}

			SkillMetalionImpulsionHit(lpSelected_Char, dmSelected_CharCnt);

			if (dmSelected_CharCnt)
				SkillPlaySound(SKILL_SOUND_SKILL_IMPULSION, pX, pY, pZ);

			SkillPlaySound(SKILL_SOUND_SKILL_CHAIN_LANCE2, pX, pY, pZ);
		}
		break;

	case SKILL_PLAY_COMPULSION:
		if (point)
		{
			SkillMetalionCompulsion(this);
		}
		break;

	case SKILL_PLAY_MAGNETIC_SPHERE:
		if (point)
		{
			SkillMetalionSphere(this, (float)Magnetic_Sphere_Time[point - 1], (float)Magnetic_Sphere_AttackDelay[point - 1]);

			SkillPlaySound(SKILL_SOUND_SKILL_SPARK3, pX, pY, pZ);
		}
		break;

	case SKILL_PLAY_METAL_GOLEM:
		if (point)
		{
			SkillMetalionGolem(this);

		}
		break;

	case SKILL_PLAY_DESTROYER:

		if (chrAttackTarget)
		{
			if (AttackCritcal >= 0)
			{
				GetAttackPoint(&Pos2.x, &Pos2.y, &Pos2.z);
				SkillWarriorDestroyerHit(&Pos2);
				SetDynLight(Pos2.x, Pos2.y, Pos2.z, 100, 0, 0, 0, 400);

				if (MotionEvent < 3)
					SkillPlaySound(SKILL_SOUND_SKILL_AVANGING_CRASH, pX, pY, pZ);
				else
					SkillPlaySound(SKILL_SOUND_SKILL_EXPANSION2, pX, pY, pZ);
			}
			else
			{


				PlayWaponSoundDirect(pX, pY, pZ, 13);
			}


			if (this == lpCurPlayer && MotionEvent < 3)
			{
				cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
				if (!cnt)
					lpCurPlayer->AttackCritcal = -1;
				else
					lpCurPlayer->AttackCritcal = 0;

			}
		}


		break;

	case SKILL_PLAY_BERSERKER:
		if (point)
		{
			SkillWarriorBetserker(this, (float)Berserker_Time[point - 1]);
			AttackAnger = 200;
		}
		break;

	case SKILL_PLAY_CYCLONE_STRIKE:
		if (lpCurPlayer != this)
		{
			dm_SelectRange(pX, pY, pZ, Cyclone_Strike_Area[point - 1], TRUE, Cyclone_Strike_AttackNum[point - 1]);
			dm_AddRangeDamage(chrAttackTarget);
		}

		for (cnt = 0; cnt < dmSelected_CharCnt; cnt++)
		{
			StartEffect(lpSelected_Char[cnt]->pX, lpSelected_Char[cnt]->pY + 16 * fONE, lpSelected_Char[cnt]->pZ, EFFECT_NORMAL_HIT1);
		}
		break;


	case SKILL_PLAY_ASSASSIN_EYE:
		if (point && chrAttackTarget)
		{
			SkillLancelotAssassinEye(chrAttackTarget, (float)Assassin_Eye_Time[point - 1]);
		}
		break;

	case SKILL_PLAY_CHARGING_STRIKE:
		if (chrAttackTarget && point)
		{
			cnt = frame - MotionInfo->StartFrame * 160;

			if (MotionInfo->EventFrame[1] <= (DWORD)cnt)
			{
				SkillLancelotChargingStrike(this);

				if (MotionInfo->EventFrame[2] <= (DWORD)cnt && GetAttackPoint(&x, &y, &z) == TRUE)
				{
					if (AttackCritcal >= 0)
					{
						StartSkill(x, y, z, 0, 0, 0, SKILL_TRIPLE_IMPACT);
						SetDynLight(x, y, z, 100, 0, 0, 0, 400);

						switch (MotionEvent)
						{
						case 2:
							SkillPlaySound(SKILL_SOUND_SKILL_CHAIN_LANCE2, pX, pY, pZ);
							break;
						case 3:
							SkillPlaySound(SKILL_SOUND_SKILL_AVANGING_CRASH, pX, pY, pZ);
							break;
						case 4:
						case 5:
							SkillPlaySound(SKILL_SOUND_SKILL_CHARGING_STRIKE, pX, pY, pZ);
							break;
						}
					}
					else
					{


						PlayWaponSoundDirect(pX, pY, pZ, 13);
					}
				}

				if (this == lpCurPlayer && SkillEventDamageCount < 3)
				{

					if (SkillEventDamageCount == 0)
						SkillStopSound(SKILL_SOUND_SKILL_CHARGING);

					temp = dm_SendTransDamage(chrAttackTarget, ChargingFlag, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);

					if (!temp)
						AttackCritcal = -1;
					else
						AttackCritcal = 0;

					SkillEventDamageCount++;
					MotionLoopSpeed = GetAttackSpeedFrame(7);

					MouseButton[1] = 0;
					CancelAttack();
				}
			}
			else
			{
				if (this == lpCurPlayer) ChargingFlag = 0;
			}

			cnt = (MotionInfo->EventFrame[3] / 160) - MotionInfo->StartFrame;


			dwEventFrameExt[0] = (MotionInfo->StartFrame + 140) * 160;
		}


		break;

	case SKILL_PLAY_VAGUE:
		if (lpCurPlayer == this)
		{
			PlayVanish = Vague_Time[point - 1] * 70;
			PlayVague = point;
			SendProcessSKillToServer(SKILL_PLAY_VAGUE, point, 0, 0);

			if (IsCreateNewRenderTarget())
			{
				dwM_BlurTime = dwPlayTime + Vanish_Time[point - 1] * 1000;
				SetFilterEffect(FILTER_EFFECT_SET_MOTION_BLUR, 80);
			}
		}
		break;

	case SKILL_PLAY_SHADOW_MASTER:

		dwEventFrameExt[0] = (793 - 710 + MotionInfo->StartFrame) * 160;
		dwEventFrameExt[1] = (794 - 710 + MotionInfo->StartFrame) * 160;
		dwEventFrameExt[2] = (795 - 710 + MotionInfo->StartFrame) * 160;


		if (chrAttackTarget && point)
		{
			for (cnt = 0; cnt < 7; cnt++)
			{
				if (SkillShadowMasterEvent[Shadow_Master_ShadowNum[point - 1]][cnt] == MotionEvent)
				{

					if (AttackCritcal >= 0)
					{
						if (GetAttackPoint(&x, &y, &z) == TRUE)
						{
							StartSkill(x, y, z, 0, 0, 0, SKILL_TRIPLE_IMPACT);
							SetDynLight(x, y, z, 100, 0, 0, 0, 400);

							switch (rand() % 3)
							{
							case 0:
								SkillPlaySound(SKILL_SOUND_SKILL_SHADOW_STRIKE1, pX, pY, pZ);
								break;
							case 1:
								SkillPlaySound(SKILL_SOUND_SKILL_SHADOW_STRIKE2, pX, pY, pZ);
								break;
							case 2:
								SkillPlaySound(SKILL_SOUND_SKILL_SHADOW_STRIKE3, pX, pY, pZ);
								break;
							}
						}
						AttackCritcal = 1;
					}
					else
					{

						PlayWaponSoundDirect(pX, pY, pZ, 13);

					}

					if (lpCurPlayer == this && (SkillEventDamageCount + 1) < Shadow_Master_ShadowNum[point - 1])
					{
						x = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
						if (!x)
							lpCurPlayer->AttackCritcal = -1;
						else
							lpCurPlayer->AttackCritcal = 0;

						SkillEventDamageCount++;
					}
					break;
				}
			}
		}
		break;


	case SKILL_PLAY_RECALL_WOLVERIN:
		SkillPlaySound(SKILL_SOUND_SKILL_RECALL_WOLVERIN, pX, pY, pZ);
		break;

	case SKILL_PLAY_PHOENIX_SHOT:
		if (chrAttackTarget && point)
		{

			cnt = frame - MotionInfo->StartFrame * 160;

			if (MotionInfo->EventFrame[1] <= (DWORD)cnt)
			{
				GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);
				Pos1.x = pX + GeoResult_X;
				Pos1.y = pY + GeoResult_Y;
				Pos1.z = pZ + GeoResult_Z;
				Pos2.x = chrAttackTarget->pX;
				Pos2.y = chrAttackTarget->pY + 24 * fONE;
				Pos2.z = chrAttackTarget->pZ;
				SkillSagittarionPhoneixShot(this, &Pos1, &Pos2);



				if (this == lpCurPlayer)
				{

					SkillStopSound(SKILL_SOUND_SKILL_CHARGING);

					if (ChargingFlag != 0)
					{
						dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil, FALSE);
					}
					else
					{
						rect.left = -50;
						rect.right = 50;
						rect.top = 0;
						rect.bottom = 300;
						rect.bottom += 20;
						rect.bottom += 20;


						dm_SelectRangeBox(lpCurPlayer, &rect, FALSE);

						dm_SendRangeDamage(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, 0, 0, lpCurPlayer->AttackSkil);
					}
					lpCurPlayer->MotionLoopSpeed = GetAttackSpeedFrame(7);
					lpCurPlayer->MotionLoop = 1;

					MouseButton[1] = 0;
					CancelAttack();
				}
				SkillPlaySound(SKILL_SOUND_SKILL_PHOENIX_SHOT, pX, pY, pZ);

			}
			else
			{
				if (this == lpCurPlayer) ChargingFlag = 0;
			}
		}
		break;

	case SKILL_PLAY_FORCE_OF_NATURE:
		if (point)
		{
			SkillSagittarionForceOfNature1(this, (float)Force_Of_Nature_Time[point - 1]);
		}
		break;

	case SKILL_PLAY_DIVINE_PIERCING:
		if (chrAttackTarget && point)
		{
			if (AttackCritcal >= 0)	SkillSaintDivinePiercing(this);


			if (Divine_Piercing_AttackNum[point - 1] >= 7)
			{
				dwEventFrameExt[0] = (81 - 10 + MotionInfo->StartFrame) * 160;
				dwEventFrameExt[1] = (102 - 10 + MotionInfo->StartFrame) * 160;
				dwEventFrameExt[2] = (120 - 10 + MotionInfo->StartFrame) * 160;
			}
			else if (Divine_Piercing_AttackNum[point - 1] >= 5)
			{
				dwEventFrameExt[0] = (227 - 150 + MotionInfo->StartFrame) * 160;
			}


			if (MotionEvent == Divine_Piercing_AttackNum[point - 1] && AttackCritcal >= 0)
				SkillPlaySound(SKILL_SOUND_SKILL_DVINE_PIERCING, pX, pY, pZ);
			else
				WeaponPlaySound(this);


			if (lpCurPlayer == this && MotionEvent < Divine_Piercing_AttackNum[point - 1])
			{


				cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);


				if (!cnt)
					lpCurPlayer->AttackCritcal = -1;
				else
					lpCurPlayer->AttackCritcal = 0;
			}

		}
		break;
	case SKILL_PLAY_GODLY_SHIELD:
		if (point)
		{
			SkillSaintGodlyShield(this, (float)Godly_Shield_Time[point - 1]);
		}
		break;
	case SKILL_PLAY_GODS_BLESS:
		break;

	case SKILL_PLAY_SWORD_OF_JUSTICE:
		if (point)
		{
			SkillSwordOfUstice(this);
		}
		break;


	case SKILL_PLAY_HALL_OF_VALHALLA:
		if (point)
		{
			SkillValhallaHallOfValhalla1(this);
			SkillValhallaHallOfValhallaHandEffect(this, (float)Hall_Of_Valhalla_Time[point - 1]);
		}
		break;
	case SKILL_PLAY_X_RAGE:
		if (chrAttackTarget && point)
		{
			GetMoveLocation(0, 0, 24 * fONE, 0, Angle.y, 0);
			Pos1.x = pX + GeoResult_X;
			Pos1.y = pY + GeoResult_Y;
			Pos1.z = pZ + GeoResult_Z;
			Pos2.x = chrAttackTarget->pX;
			Pos2.y = chrAttackTarget->pY + 40 * fONE;
			Pos2.z = chrAttackTarget->pZ;
			SkillValhallaXRage(&Pos1, &Pos2);

			switch (rand() % 3)
			{
			case 0:
				SkillPlaySound(SKILL_SOUND_SKILL_EXTREM_RAGE1, pX, pY, pZ);
				break;
			case 1:
				SkillPlaySound(SKILL_SOUND_SKILL_EXTREM_RAGE2, pX, pY, pZ);
				break;
			case 2:
				SkillPlaySound(SKILL_SOUND_SKILL_EXTREM_RAGE3, pX, pY, pZ);
				break;
			}
		}
		break;
	case SKILL_PLAY_FROST_JAVELIN:
		if (point)
		{
			SkillParticle_FrostJavelin(this, (float)Frost_Javelin_Time[point - 1]);

		}
		break;
	case SKILL_PLAY_VENGEANCE:
		if (chrAttackTarget && point)
		{
			GetMoveLocation(0, 24 * fONE, 24 * fONE, 0, Angle.y, 0);
			Pos1.x = pX + GeoResult_X;
			Pos1.y = pY + GeoResult_Y;
			Pos1.z = pZ + GeoResult_Z;
			Pos2.x = chrAttackTarget->pX;
			Pos2.y = chrAttackTarget->pY + 40 * fONE;
			Pos2.z = chrAttackTarget->pZ;
			if (AttackCritcal >= 0) SkillVengeance(&Pos1, &Pos2);

			if (this == lpCurPlayer && MotionEvent == 1)
			{
				cnt = dm_SendTransDamage(chrAttackTarget, 0, 0, 0, 0, AttackSkil, TRUE);
				if (!cnt)
					AttackCritcal = -1;
			}
			if (MotionEvent == 1)
				SkillPlaySound(SKILL_SOUND_SKILL_VENGEANCE1, pX, pY, pZ);
			else
				SkillPlaySound(SKILL_SOUND_SKILL_VENGEANCE2, pX, pY, pZ);
		}
		break;


	case SKILL_PLAY_GLACIAL_SPIKE:
		if (point && MotionEvent == 1)
		{
			SkillCelestialGlacialSpike(this);

			GetMoveLocation(0, 0, 64 * fONE, 0, Angle.y, 0);
			SetDynLight(pX + GeoResult_X, pY, pZ + GeoResult_Z, 0, 0, 100, 0, 700);

			if (this == lpCurPlayer)
			{
				rect.left = -50;
				rect.right = 50;
				rect.top = 0;
				rect.bottom = 300;
				rect.bottom += 20;
				rect.bottom += 20;


				dm_SelectRangeBox(lpCurPlayer, &rect, FALSE);

				dm_SendRangeDamage(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0,
					cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[0],
					cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[1],
					0, 0, lpCurPlayer->AttackSkil);
			}

			if (rand() % 2)
				SkillPlaySound(SKILL_SOUND_SKILL_GLACIAL_SPIKE1, pX, pY, pZ);
			else
				SkillPlaySound(SKILL_SOUND_SKILL_GLACIAL_SPIKE2, pX, pY, pZ);

		}
		break;
	case SKILL_PLAY_REGENERATION_FIELD:
		if (point)
		{
			SkillCelestialRegnerationField(this, 2.0f);

			if (this == lpCurPlayer)
			{


				if (MouseButton[1] && cSkill.SearchContiueSkill(SKILL_REGENERATION_FIELD))
				{

					frame = MotionInfo->StartFrame * 160 + MotionInfo->EventFrame[0];
				}
				else
				{
					cSkill.CancelContinueSkill(SKILL_REGENERATION_FIELD);
				}
			}
			else
			{
				cnt = Regeneration_Field_Area[point - 1];
				cnt *= cnt;
				if (GetDistanceDbl(pX, pZ, lpCurPlayer->pX, lpCurPlayer->pZ) < cnt && abs(lpCurPlayer->pY - pY) < 16 * fONE)
				{
					cSkill.Regeneration_Field(5, point, 1);
				}
			}
		}
		break;
	case SKILL_PLAY_CHAIN_LIGHTNING:
		if (chrAttackTarget && point)
		{



			dm_SelectDamageChainCount(this, chrAttackTarget, Chain_Lightning_Num[point - 1], Chain_Lightning_Range[point - 1]);

			if (dmSelected_CharCnt > 0)
			{
				if (this == lpCurPlayer)
				{

					dm_SendRangeDamage(pX, pY, pZ, 0,
						cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[0],
						cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[1],
						0, 0, AttackSkil);
				}

				SkillCelestialChainLighting(lpSelected_Char, dmSelected_CharCnt);

				if (rand() % 2)
					SkillPlaySound(SKILL_SOUND_SKILL_CHAIN_LIGHTNING1, pX, pY, pZ);
				else
					SkillPlaySound(SKILL_SOUND_SKILL_CHAIN_LIGHTNING2, pX, pY, pZ);
			}
		}
		break;

	case SKILL_PLAY_SUMMON_MUSPELL:
		if (point)
		{
			SkillCelestialMusPel(this, (float)Summon_Muspell_Time[point - 1], (float)Summon_Muspell_Attack_Delay[point - 1]);
			SkillPlaySound(SKILL_SOUND_SKILL_MUSPELL2, pX, pY, pZ);
		}
		break;


	case SKILL_PLAY_FIRE_ELEMENTAL:
		if (point)
		{

		}
		break;
	case SKILL_PLAY_FLAME_WAVE:
		if (point)
		{
			SkillArchMageFlameWave(this);

			if (rand() % 2)
				SkillPlaySound(SKILL_SOUND_SKILL_FLAME_WAVE1, pX, pY, pZ);
			else
				SkillPlaySound(SKILL_SOUND_SKILL_FLAME_WAVE2, pX, pY, pZ);

			if (this == lpCurPlayer && MotionEvent == 1)
			{

				rect.left = -60;
				rect.right = 60;
				rect.top = 0;
				rect.bottom = 300;
				rect.bottom += 20;
				rect.bottom += 20;


				dm_SelectRangeBox(lpCurPlayer, &rect, FALSE);

				dm_SendRangeDamage(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0,
					cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[0],
					cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[1],
					0, 0, lpCurPlayer->AttackSkil);

			}

		}
		break;
	case SKILL_PLAY_DISTORTION:
		if (point)
		{

		}
		break;

	case SKILL_PLAY_METEO:

		if (chrAttackTarget && point)
		{
			Pos2.x = chrAttackTarget->pX;
			Pos2.y = chrAttackTarget->pY;
			Pos2.z = chrAttackTarget->pZ;
			SkillArchMageMeteo(&Pos2);

			if (this == lpCurPlayer && MotionEvent < 3)
			{

				dm_SelectRange(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, Meteo_Area[point - 1], FALSE);

				dm_SendRangeDamage(chrAttackTarget->pX, chrAttackTarget->pY, chrAttackTarget->pZ, 0,
					cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[0],
					cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[1],
					0, 0, lpCurPlayer->AttackSkil);
			}

			SkillPlaySound(SKILL_SOUND_SKILL_METEO1, pX, pY, pZ);
		}
		break;
	}


	return TRUE;
}


int smCHAR::SendTransAttack(smCHAR *lpChar, smWINSOCK *lpsmsock, int AttackCode, int Add_Damage, int Resistance)
{
	TRANS_ATTACKDATA	TransAttackData;
	smWINSOCK	*lpsmSendSock;
	rsPLAYINFO *lpPlayInfo = 0;
	char szDispDamage[128];
	smTRANS_COMMAND	smTransCommand;

	int	pow;

	int temp;
	int	accuracy;

#ifndef _W_SERVER

	Record_ClinetLogFile("Older attack packets - ::SendTransAttack ");
	quit = 1;
	return TRUE;
#endif



	if (lpsmsock)
	{
		lpPlayInfo = (rsPLAYINFO *)lpsmsock->ExtData1;
	}

	TransAttackData.code = OpCode::OPCODE_ATTACKDATA;
	TransAttackData.size = sizeof(TRANS_ATTACKDATA);

	TransAttackData.x = pX;
	TransAttackData.y = pY;
	TransAttackData.z = pZ;

	TransAttackData.AttackState = 1;
	TransAttackData.AttackSize = 48 * fONE;
	TransAttackData.Power = GetRandomPos(smCharInfo.Attack_Damage[0], smCharInfo.Attack_Damage[1]);

	TransAttackData.sRating[0] = smCharInfo.Level;
	TransAttackData.sRating[1] = smCharInfo.Attack_Rating;

	if (PlayHolyMind[1] > 0)
		TransAttackData.Power -= ((TransAttackData.Power*PlayHolyMind[0]) / 100);

	if (PlayWisp[1] > 0)
		TransAttackData.Power -= ((TransAttackData.Power*PlayWisp[0]) / 100);

	if (!lpPlayInfo) return FALSE;



	if (lpPlayInfo->dwSiegeItem_Scroll_Time && lpPlayInfo->dwSiegeItem_Scroll_Time < dwPlayServTime)
	{
		lpPlayInfo->dwSiegeItem_Scroll_Code = 0;
		lpPlayInfo->dwSiegeItem_Scroll_Time = 0;
	}
	if (lpPlayInfo->dwSiegeItem_Stone1_Time && lpPlayInfo->dwSiegeItem_Stone1_Time < dwPlayServTime)
	{
		lpPlayInfo->dwSiegeItem_Stone1_Code = 0;
		lpPlayInfo->dwSiegeItem_Stone1_Time = 0;
	}

	if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_B)
	{

		TransAttackData.sRating[0] = -SKILL_PLAY_ICE_CRYSTAL;
		TransAttackData.sRating[1] = 3;
	}
	else if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_G)
	{

		TransAttackData.sRating[0] = -SKILL_PLAY_LIGHTNING_CRYSTAL;
		TransAttackData.sRating[1] = 2;
	}
	else if (smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_R)
	{

		TransAttackData.sRating[0] = -SKILL_PLAY_FIRE_CRYSTAL;
		TransAttackData.sRating[1] = 1;
	}

	if (lpPlayInfo->dwSiegeItem_Stone1_Code && lpPlayInfo->dwSiegeItem_Stone1_Code == smCharInfo.dwCharSoundCode)
	{

		TransAttackData.Power /= 2;
		TransAttackData.sRating[0] = smCharInfo.Level;
		TransAttackData.sRating[1] = smCharInfo.Attack_Rating;
	}

	if (lpPlayInfo->dwSiegeItem_Scroll_Code == (sinBC1 | sin01))
	{
		if (lpPlayInfo->Position.Area == rsCASTLE_FIELD) return FALSE;
	}
	if (lpPlayInfo->dwSiegeItem_Scroll_Code == (sinBI1 | sin05))
		return FALSE;


	if (lpPlayInfo->dwSiegeItem_Scroll_Code == (sinBC1 | sin03))
	{
		if (lpPlayInfo->Position.Area == rsCASTLE_FIELD)
		{
			if ((rand() % 100) < (int)lpPlayInfo->dwSiegeItem_Scroll_Param)
			{
#ifdef DISP_DAMAGE
				if (lpPlayInfo->getSecurity() > AccountTypes::SEC_GAMEMASTER)
				{
					wsprintf(szDispDamage, ">%s °ø°Ý Ãß°¡È¸ÇÇ ( Evade Scroll[%d] )", smCharInfo.szName, lpPlayInfo->dwSiegeItem_Scroll_Param);
					rsDisplayDamgeToClient(lpPlayInfo, szDispDamage);
				}
#endif

				smTransCommand.code = OpCode::OPCODE_SUCCESS_EVATION;
				smTransCommand.size = sizeof(smTRANS_COMMAND);
				smTransCommand.WParam = 0;
				smTransCommand.LParam = lpPlayInfo->dwSiegeItem_Scroll_Code;
				smTransCommand.SParam = dwObjectSerial;
				smTransCommand.EParam = 0;
				lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
				return FALSE;
			}
		}
	}

	if (lpPlayInfo->dwSiegeItem_Scroll_Code == (sinBI1 | sin07))
	{
		if ((rand() % 100) < (int)lpPlayInfo->dwSiegeItem_Scroll_Param)
		{
#ifdef DISP_DAMAGE
			if (lpPlayInfo->getSecurity() > AccountTypes::SEC_GAMEMASTER)
			{
				wsprintf(szDispDamage, ">%s °ø°Ý Ãß°¡È¸ÇÇ ( Evade Scroll[%d] )", smCharInfo.szName, lpPlayInfo->dwSiegeItem_Scroll_Param);
				rsDisplayDamgeToClient(lpPlayInfo, szDispDamage);
			}
#endif

			smTransCommand.code = OpCode::OPCODE_SUCCESS_EVATION;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = 0;
			smTransCommand.LParam = lpPlayInfo->dwSiegeItem_Scroll_Code;
			smTransCommand.SParam = dwObjectSerial;
			smTransCommand.EParam = 0;
			lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
			return FALSE;
		}
	}

	if (lpPlayInfo->dwSkill_PhysicalAbsorb_Time)
	{
		if (lpPlayInfo->dwSkill_PhysicalAbsorb_Time > dwPlayServTime)
		{
			TransAttackData.Power -= lpPlayInfo->dwSkill_PhysicalAbsorb_Param;
			if (TransAttackData.Power < 0) return FALSE;
		}
		else
		{
			lpPlayInfo->dwSkill_PhysicalAbsorb_Time = 0;
			lpPlayInfo->dwSkill_PhysicalAbsorb_Param = 0;
		}
	}

	if (lpPlayInfo->dwSkill_MetalArmor_Time)
	{
		if (lpPlayInfo->dwSkill_MetalArmor_Time > dwPlayServTime)
		{
			TransAttackData.Power -= lpPlayInfo->dwSkill_MetalArmor_Param;
			if (TransAttackData.Power < 0) return FALSE;
		}
		else
		{
			lpPlayInfo->dwSkill_MetalArmor_Time = 0;
			lpPlayInfo->dwSkill_MetalArmor_Param = 0;
		}
	}


	if (lpPlayInfo->dwSkill_HolyBody_Time)
	{
		if (lpPlayInfo->dwSkill_HolyBody_Time > dwPlayServTime)
		{
			if (smCharInfo.Brood == smCHAR_MONSTER_UNDEAD)
			{
				TransAttackData.Power -= (TransAttackData.Power*lpPlayInfo->dwSkill_HolyBody_Param) / 100;
				if (TransAttackData.Power < 0) return FALSE;
			}
		}
		else
		{
			lpPlayInfo->dwSkill_HolyBody_Time = 0;
			lpPlayInfo->dwSkill_HolyBody_Param = 0;
		}
	}

	if (lpPlayInfo->dwSkill_ExtreamShield_Time)
	{
		if (lpPlayInfo->dwSkill_ExtreamShield_Time > dwPlayServTime)
		{
			TransAttackData.AttackState |= (lpPlayInfo->dwSkill_ExtreamShield_Param << 16);
			if (TransAttackData.Power < 0) return FALSE;
		}
		else
		{
			lpPlayInfo->dwSkill_ExtreamShield_Time = 0;
			lpPlayInfo->dwSkill_ExtreamShield_Param = 0;
		}
	}


	if (lpPlayInfo->dwSkill_DivineInhalation_Time && smCharInfo.Brood == smCHAR_MONSTER_UNDEAD)
	{
		if (lpPlayInfo->dwSkill_DivineInhalation_Time > dwPlayServTime)
		{

			temp = smCharInfo.Resistance[sITEMINFO_BIONIC];
			if (temp)
			{
				if (temp >= 100) temp = 100;
				if (temp <= -100) temp = -100;
				temp = (D_Inhalation_Life[lpPlayInfo->dwSkill_DivineInhalation_Param] * temp) / 100;
				temp &= 0xFF;
				temp |= D_Inhalation_Block[lpPlayInfo->dwSkill_DivineInhalation_Param] << 8;
				if (temp)
				{
					TransAttackData.AttackState |= (temp << 16);
				}
			}
			if (TransAttackData.Power < 0) return FALSE;
		}
		else
		{
			lpPlayInfo->dwSkill_DivineInhalation_Time = 0;
			lpPlayInfo->dwSkill_DivineInhalation_Param = 0;
		}
	}

	if (lpPlayInfo->dwSkill_VirtualLife_Time)
	{
		if (lpPlayInfo->dwSkill_VirtualLife_Time > dwPlayServTime)
		{
			TransAttackData.Power -= (TransAttackData.Power*lpPlayInfo->dwSkill_VirtualLife_Param) / 100;
			if (TransAttackData.Power < 0) return FALSE;
		}
		else
		{
			lpPlayInfo->dwSkill_VirtualLife_Time = 0;
			lpPlayInfo->dwSkill_VirtualLife_Param = 0;
		}
	}

	if (lpPlayInfo->dwSkill_EnergyShield_Time)
	{
		if (lpPlayInfo->dwSkill_EnergyShield_Time > dwPlayServTime)
		{
			temp = (TransAttackData.Power*lpPlayInfo->dwSkill_EnergyShield_Param) / 100;
			TransAttackData.Power -= temp;
			TransAttackData.AttackState |= (temp << 16);
			if (TransAttackData.Power < 0) return FALSE;
		}
		else
		{
			lpPlayInfo->dwSkill_EnergyShield_Time = 0;
			lpPlayInfo->dwSkill_EnergyShield_Param = 0;
		}
	}

	if (lpPlayInfo->dwSkill_Compulsion_Time)
	{
		if (lpPlayInfo->dwSkill_Compulsion_Time > dwPlayServTime)
		{
			TransAttackData.Power -= lpPlayInfo->dwSkill_Compulsion_Param;
			if (TransAttackData.Power < 0) return FALSE;
		}
		else
		{
			lpPlayInfo->dwSkill_Compulsion_Time = 0;
			lpPlayInfo->dwSkill_Compulsion_Param = 0;
		}
	}

	if (lpPlayInfo->dwSkill_Berserker_Time)
	{
		if (lpPlayInfo->dwSkill_Berserker_Time > dwPlayServTime)
		{
			TransAttackData.Power -= Berserker_SubAbsorb[lpPlayInfo->dwSkill_Berserker_Param];
			if (TransAttackData.Power < 0) return FALSE;
		}
		else
		{
			lpPlayInfo->dwSkill_Berserker_Time = 0;
			lpPlayInfo->dwSkill_Berserker_Param = 0;
		}
	}


	if (lpPlayInfo->dwSkill_RainMaker_Time)
	{
		if (lpPlayInfo->dwSkill_RainMaker_Time > dwPlayServTime)
		{
			TransAttackData.Power -= RainMaker_Absorb[lpPlayInfo->dwSkill_RainMaker_Param];
			if (TransAttackData.Power < 0) return FALSE;
		}
		else {
			lpPlayInfo->dwSkill_RainMaker_Time = 0;
			lpPlayInfo->dwSkill_RainMaker_Param = 0;
		}
	}


	if (lpPlayInfo->dwSkill_Alas_Time)
	{
		if (lpPlayInfo->dwSkill_Alas_Time > dwPlayServTime)
		{
			if ((rand() % 100) < Vague_EvasionPercent[lpPlayInfo->dwSkill_Vague_Param])
			{

#ifdef DISP_DAMAGE
				if (lpPlayInfo->getSecurity() > AccountTypes::SEC_GAMEMASTER)
				{
					wsprintf(szDispDamage, ">%s °ø°Ý Ãß°¡È¸ÇÇ ( Alas[%d] )", smCharInfo.szName, Alas_EvasionPercent[lpPlayInfo->dwSkill_Alas_Param]);
					rsDisplayDamgeToClient(lpPlayInfo, szDispDamage);
				}
#endif


				smTransCommand.code = OpCode::OPCODE_SUCCESS_EVATION;
				smTransCommand.size = sizeof(smTRANS_COMMAND);
				smTransCommand.WParam = 0;
				smTransCommand.LParam = SKILL_PLAY_VAGUE;
				smTransCommand.SParam = dwObjectSerial;
				smTransCommand.EParam = 0;
				lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

				return FALSE;
			}
		}
		else
		{
			lpPlayInfo->dwSkill_Alas_Time = 0;
			lpPlayInfo->dwSkill_Alas_Param = 0;
		}
	}

	if (lpPlayInfo->dwSkill_Vague_Time)
	{
		if (lpPlayInfo->dwSkill_Vague_Time > dwPlayServTime)
		{
			if ((rand() % 100) < Vague_EvasionPercent[lpPlayInfo->dwSkill_Vague_Param])
			{

#ifdef DISP_DAMAGE
				if (lpPlayInfo->getSecurity() > AccountTypes::SEC_GAMEMASTER)
				{
					wsprintf(szDispDamage, ">%s °ø°Ý Ãß°¡È¸ÇÇ ( Vague[%d] )", smCharInfo.szName, Vague_EvasionPercent[lpPlayInfo->dwSkill_Vague_Param]);
					rsDisplayDamgeToClient(lpPlayInfo, szDispDamage);
				}
#endif


				smTransCommand.code = OpCode::OPCODE_SUCCESS_EVATION;
				smTransCommand.size = sizeof(smTRANS_COMMAND);
				smTransCommand.WParam = 0;
				smTransCommand.LParam = SKILL_PLAY_VAGUE;
				smTransCommand.SParam = dwObjectSerial;
				smTransCommand.EParam = 0;
				lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

				return FALSE;
			}
		}
		else
		{
			lpPlayInfo->dwSkill_Vague_Time = 0;
			lpPlayInfo->dwSkill_Vague_Param = 0;
		}
	}

	if (lpPlayInfo->dwSkill_GodlyShied_Time)
	{
		if (lpPlayInfo->dwSkill_GodlyShied_Time > dwPlayServTime)
		{
			TransAttackData.Power -= (TransAttackData.Power*Godly_Shield_AbsorbPercent[lpPlayInfo->dwSkill_GodlyShied_Param]) / 100;
			if (TransAttackData.Power < 0) return FALSE;
		}
		else
		{
			lpPlayInfo->dwSkill_GodlyShied_Time = 0;
			lpPlayInfo->dwSkill_GodlyShied_Param = 0;
		}
	}



	if (lpPlayInfo->dwSkill_HallOfValhalla_Time)
	{
		if (lpPlayInfo->dwSkill_HallOfValhalla_Time > dwPlayServTime)
		{
			if ((rand() % 100) < (int)lpPlayInfo->wSkill_HallOfValhalla_Param[0])
			{
#ifdef DISP_DAMAGE
				if (lpPlayInfo->getSecurity() > AccountTypes::SEC_GAMEMASTER)
				{
					wsprintf(szDispDamage, ">%s °ø°Ý Ãß°¡È¸ÇÇ ( Hall of Valhalla [%d] )", smCharInfo.szName, lpPlayInfo->wSkill_HallOfValhalla_Param[0]);
					rsDisplayDamgeToClient(lpPlayInfo, szDispDamage);
				}
#endif

				smTransCommand.code = OpCode::OPCODE_SUCCESS_EVATION;
				smTransCommand.size = sizeof(smTRANS_COMMAND);
				smTransCommand.WParam = 0;
				smTransCommand.LParam = SKILL_PLAY_HALL_OF_VALHALLA;
				smTransCommand.SParam = dwObjectSerial;
				smTransCommand.EParam = 0;
				lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

				return FALSE;
			}
		}
		else
		{
			lpPlayInfo->dwSkill_HallOfValhalla_Time = 0;
		}
	}

	if (lpPlayInfo->dwSkill_SummonMuspell_Time)
	{
		if (lpPlayInfo->dwSkill_SummonMuspell_Time > dwPlayServTime)
		{

			if ((rand() % 100) < Summon_Muspell_BlockPercent[lpPlayInfo->dwSkill_SummonMuspell_Param])
			{
#ifdef DISP_DAMAGE
				if (lpPlayInfo->getSecurity() > AccountTypes::SEC_GAMEMASTER)
				{
					wsprintf(szDispDamage, ">%s °ø°Ý Ãß°¡ È¸ÇÇ ( Summon Muspell [%d] )", smCharInfo.szName, Summon_Muspell_BlockPercent[lpPlayInfo->dwSkill_SummonMuspell_Param]);
					rsDisplayDamgeToClient(lpPlayInfo, szDispDamage);
				}
#endif

				smTransCommand.code = OpCode::OPCODE_SUCCESS_EVATION;
				smTransCommand.size = sizeof(smTRANS_COMMAND);
				smTransCommand.WParam = 0;
				smTransCommand.LParam = SKILL_PLAY_SUMMON_MUSPELL;
				smTransCommand.SParam = dwObjectSerial;
				smTransCommand.EParam = 0;
				lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

				return FALSE;
			}
			if (smCharInfo.Brood == smCHAR_MONSTER_UNDEAD)
			{

				temp = (TransAttackData.Power*Summon_Muspell_UndeadAbsorbPercent[lpPlayInfo->dwSkill_SummonMuspell_Param]) / 100;
				TransAttackData.AttackState |= (temp << 16);
				if (TransAttackData.Power < 0) return FALSE;
			}
		}
		else
		{
			lpPlayInfo->dwSkill_SummonMuspell_Time = 0;
			lpPlayInfo->dwSkill_SummonMuspell_Param = 0;
		}
	}


	if (lpPlayInfo->dwBlessSkill_Code)
	{
		if (lpPlayInfo->dwBlessSkill_Code == SKILL_PLAY_BLESS_ABSORB)
		{
			if (lpPlayInfo->dwBlessSkill_Time > dwPlayServTime)
			{
				TransAttackData.Power -= lpPlayInfo->dwBlessSkill_Param;
				if (TransAttackData.Power < 0) return FALSE;
			}
			else
			{
				lpPlayInfo->dwBlessSkill_Code = 0;
				lpPlayInfo->dwBlessSkill_Time = 0;
			}
		}
		else if (lpPlayInfo->dwBlessSkill_Code == SKILL_PLAY_BLESS_EVADE)
		{
			if (lpPlayInfo->dwBlessSkill_Time > dwPlayServTime)
			{

				if ((rand() % 100) < (int)lpPlayInfo->dwBlessSkill_Param)
				{
#ifdef DISP_DAMAGE
					if (lpPlayInfo->getSecurity() > AccountTypes::SEC_GAMEMASTER)
					{
						wsprintf(szDispDamage, ">%s Evasão ( Clan Skill [%d] )", smCharInfo.szName, lpPlayInfo->dwBlessSkill_Param);
						rsDisplayDamgeToClient(lpPlayInfo, szDispDamage);
					}
#endif

					smTransCommand.code = OpCode::OPCODE_SUCCESS_EVATION;
					smTransCommand.size = sizeof(smTRANS_COMMAND);
					smTransCommand.WParam = 0;
					smTransCommand.LParam = SKILL_PLAY_BLESS_EVADE;
					smTransCommand.SParam = dwObjectSerial;
					smTransCommand.EParam = 0;
					lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

					return FALSE;
				}
			}
			else
			{
				lpPlayInfo->dwBlessSkill_Code = 0;
				lpPlayInfo->dwBlessSkill_Time = 0;
			}
		}
	}



	if (lpPlayInfo->smCharInfo.Defence)
	{
		int iChanceDefense = 100 - DefendChance(lpPlayInfo->smCharInfo.Defence, TransAttackData.Power);
		//UNITDATA->sCharacterData.iAttackRating = iOldAttackRating;

		int iChance = rand() % 100;


		if (lpPlayInfo->getSecurity() > AccountTypes::SEC_GAMEMASTER)
		{
			//sprintf_s(szDispDamage, ">%s > Chance: %d / %d [%s]", smCharInfo.szName, iChance, iChanceDefense, iChance > iChanceDefense ? "Miss" : "Hit");
			//sDisplayDamgeToClient(lpPlayInfo, szDispDamage);
		}



		if (iChance > iChanceDefense)
		{
			smTransCommand.code = OpCode::OPCODE_SUCCESS_DEFENSE;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = 0;
			smTransCommand.LParam = 0;
			smTransCommand.SParam = lpPlayInfo->dwObjectSerial;
			smTransCommand.EParam = 0;


			if (lpPlayInfo)
				lpPlayInfo->lpsmSock->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
			return FALSE;
		}

	}


	if (lpPlayInfo->dwCurse_Defence_Time)
	{
		if (lpPlayInfo->dwCurse_Defence_Time > dwPlayServTime)
			TransAttackData.Power += lpPlayInfo->dwCurse_Defence_Param;
		else
			lpPlayInfo->dwCurse_Defence_Time = 0;
	}


	if (PlayHolyPower[1])
	{
		TransAttackData.Power += (TransAttackData.Power*PlayHolyPower[0]) / 100;
	}

	if (Add_Damage)
	{
		TransAttackData.Power += (TransAttackData.Power*Add_Damage) / 100;
	}

	if (AttackCritcal)
	{

		TransAttackData.Power = (TransAttackData.Power * 170) / 100;
		TransAttackData.AttackState = 2;
	}


	if (AttackEffect)
		TransAttackData.AttackState = 2;

	if (TransAttackData.Power < 1) TransAttackData.Power = 1;

	if (this == lpCurPlayer && smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR && smConfig.szFile_Player[0])
	{

		if (VRKeyBuff[VK_CONTROL])
			TransAttackData.Power = 200;
		else
			TransAttackData.Power = 30;
	}
	else
	{
		if (lpChar)
		{
			switch (lpChar->smCharInfo.State)
			{
			case smCHAR_STATE_ENEMY:

				dwBattleTime = dwPlayTime;


				temp = smCharInfo.Attack_Rating;

				if (HoSkillCode)
				{
					switch (HoSkillCode)
					{
					case SKILL_SCOUT_HAWK:
						pow = GetSkillPower(this, lpChar, 0, 0, 0);
						if (pow)
						{
							smCharInfo.Attack_Rating += (smCharInfo.Attack_Rating*pow) / 100;
						}
						break;
					}
				}
				accuracy = sinGetAccuracy(lpChar->smCharInfo.Level, lpChar->smCharInfo.Defence);
				smCharInfo.Attack_Rating = temp;
				if ((rand() % 100) > accuracy)
					return FALSE;
				break;

			case smCHAR_STATE_NPC:
				TransAttackData.AttackState = Resistance;
				Resistance = 0;
				break;
			}
		}
	}

	if (Resistance)
	{
		TransAttackData.AttackState |= (Resistance << 16);
		pow = Resistance >> 4;
		if (pow > 0 && pow < 512)
		{
			TransAttackData.Power += pow;
		}
	}

	LastAttackDamage = TransAttackData.Power;
	TransAttackData.dwDestObjectSerial = dwObjectSerial;
	TransAttackData.dwTarObjectSerial = 0;
	TransAttackData.dwChkSum = TransAttackData.Power * 2002 + (TransAttackData.x * TransAttackData.y * TransAttackData.z);
	lpsmSendSock = lpsmsock;


	if (lpChar)
	{
		if (lpChar->TransSock)
			lpsmSendSock = lpChar->TransSock;

		if (lpChar->ServerCode)
		{
			lpsmSendSock = GetServerSock(lpChar->ServerCode);
		}

		TransAttackData.dwTarObjectSerial = lpChar->dwObjectSerial;


		if (lpChar->smCharInfo.State == smCHAR_STATE_ENEMY && lpChar->smCharInfo.Life[1] && lpChar->smCharInfo.Life[0] == lpChar->smCharInfo.Life[1])
		{
			lpChar->EnableStateBar = TRUE;
		}
	}


	if (lpsmSendSock)
	{
		if (!ServerMode)
		{

			Record_SendDamage(lpsmSendSock, TransAttackData.Power);
		}

		pow = TransAttackData.Power;

		if (lpsmsock)
		{
			if (rsServerConfig.CrazyPacketMode && lpPlayInfo && lpPlayInfo->dwDecPacketCode &&
				lpPlayInfo->dwDecPacketTime2 < dwPlayServTime)
			{


				TransAttackData.code = OpCode::OPCODE_ATTACKDATA2;
				TransAttackData.dwDamageChkSum = dm_GetDamgeChkSum_S2V(&TransAttackData);
				rsEncodeDamagePacket(lpPlayInfo, &TransAttackData);
			}
			else
				TransAttackData.dwDamageChkSum = dm_GetDamgeChkSum_S2V(&TransAttackData);
		}

		if (lpsmSendSock->Send((char *)&TransAttackData, TransAttackData.size, TRUE))
		{
			return pow;
		}
	}


	return FALSE;
}


int smCHAR::PlayAttackFromPosi(int ex, int ey, int ez, int Dist, int attack)
{
	int AtDist;
	int	dDist;
	int ay;

	ay = abs(pY - ey);

	if (OnStageField >= 0 && StageField[OnStageField]->FieldCode == rsCASTLE_FIELD)
	{

		if (ShootingMode)
		{
			if (ay > 80 * fONE) return NULL;
		}
		else
		{
			if (ay > 52 * fONE) return NULL;
		}


		if ((pZ<CastleBattleZone_DoorLineZ && ez>CastleBattleZone_DoorLineZ) ||
			(pZ > CastleBattleZone_DoorLineZ && ez < CastleBattleZone_DoorLineZ))
		{
			if (rsBlessCastle.CastleMode && rsBlessCastle.DefenceLevel == 0)
			{
				return NULL;
			}
		}
	}
	else
		if (ay > 64 * fONE) return NULL;

	AtDist = GetDistanceDbl(pX, pZ, ex, ez);
	dDist = (Dist >> FLOATNS);
	dDist *= dDist;

	if (AtDist < dDist)
	{
		if (MotionInfo->State != CHRMOTION_STATE_ATTACK &&
			MotionInfo->State != CHRMOTION_STATE_SKILL && MotionInfo->State != CHRMOTION_STATE_DEAD)
		{

			if (attack)
			{

				if (smCharInfo.State != smCHAR_STATE_USER || (OnStageField >= 0 && StageField[OnStageField]->State != FIELD_STATE_VILLAGE))
				{
					SetMotionFromCode(CHRMOTION_STATE_ATTACK);
					Angle.y = GetRadian2D(pX, pZ, ex, ez);
					AttackX = ex;
					AttackY = ey;
					AttackZ = ez;
				}
			}

			return TRUE;
		}
	}

	return NULL;
}




int InitMotionBlur()
{
	int cnt;
	int TlCnt;
	float fVCnt, fVCnt2;
	float fBlurLevel;
	int MbCnt, MvCnt;


	MatMBlur = CreateTextureMaterial("image\\MotionMask.bmp", NULL, TRUE, FALSE, FALSE, SMMAT_BLEND_ADDCOLOR);



	fBlurLevel = 1.0f / 32;
	TlCnt = 0;
	fVCnt = 0;
	fVCnt2 = 0 + fBlurLevel;

	for (cnt = 0; cnt < 32; cnt++)
	{

		smTexLinkMotionBlur[TlCnt].NextTex = 0;
		smTexLinkMotionBlur[TlCnt].hTexture = 0;
		smTexLinkMotionBlur[TlCnt].v[0] = fVCnt;
		smTexLinkMotionBlur[TlCnt].v[1] = fVCnt;
		smTexLinkMotionBlur[TlCnt].v[2] = fVCnt2;
		smTexLinkMotionBlur[TlCnt].u[0] = 0;
		smTexLinkMotionBlur[TlCnt].u[1] = 1;
		smTexLinkMotionBlur[TlCnt].u[2] = 0;

		TlCnt++;

		smTexLinkMotionBlur[TlCnt].NextTex = 0;
		smTexLinkMotionBlur[TlCnt].hTexture = 0;
		smTexLinkMotionBlur[TlCnt].v[0] = fVCnt2;
		smTexLinkMotionBlur[TlCnt].v[1] = fVCnt;
		smTexLinkMotionBlur[TlCnt].v[2] = fVCnt2;
		smTexLinkMotionBlur[TlCnt].u[0] = 0;
		smTexLinkMotionBlur[TlCnt].u[1] = 1;
		smTexLinkMotionBlur[TlCnt].u[2] = 1;

		TlCnt++;

		fVCnt = fVCnt2;
		fVCnt2 += fBlurLevel;

	}

	MbCnt = 0;
	MvCnt = 0;

	ZeroMemory(MbVertex, sizeof(smVERTEX) * 64);

	for (cnt = 0; cnt < 32; cnt++)
	{

		MbFace[MbCnt].lpTexLink = &smTexLinkMotionBlur[MbCnt];
		MbFace[MbCnt].v[0] = MvCnt;
		MbFace[MbCnt].v[1] = MvCnt + 1;
		MbFace[MbCnt].v[2] = MvCnt + 2;
		MbFace[MbCnt].v[3] = MatMBlur;
		MbCnt++;

		MbFace[MbCnt].lpTexLink = &smTexLinkMotionBlur[MbCnt];
		MbFace[MbCnt].v[0] = MvCnt + 2;
		MbFace[MbCnt].v[1] = MvCnt + 1;
		MbFace[MbCnt].v[2] = MvCnt + 3;
		MbFace[MbCnt].v[3] = MatMBlur;
		MbCnt++;
		MvCnt += 2;

	}





	fBlurLevel = 1.0f / 16;
	TlCnt = 0;
	fVCnt = 0;
	fVCnt2 = 0 + fBlurLevel;

	for (cnt = 0; cnt < 16; cnt++)
	{

		smTexLinkMotionBlur2[TlCnt].NextTex = 0;
		smTexLinkMotionBlur2[TlCnt].hTexture = 0;
		smTexLinkMotionBlur2[TlCnt].v[0] = fVCnt;
		smTexLinkMotionBlur2[TlCnt].v[1] = fVCnt;
		smTexLinkMotionBlur2[TlCnt].v[2] = fVCnt2;
		smTexLinkMotionBlur2[TlCnt].u[0] = 0;
		smTexLinkMotionBlur2[TlCnt].u[1] = 1;
		smTexLinkMotionBlur2[TlCnt].u[2] = 0;

		TlCnt++;

		smTexLinkMotionBlur2[TlCnt].NextTex = 0;
		smTexLinkMotionBlur2[TlCnt].hTexture = 0;
		smTexLinkMotionBlur2[TlCnt].v[0] = fVCnt2;
		smTexLinkMotionBlur2[TlCnt].v[1] = fVCnt;
		smTexLinkMotionBlur2[TlCnt].v[2] = fVCnt2;
		smTexLinkMotionBlur2[TlCnt].u[0] = 0;
		smTexLinkMotionBlur2[TlCnt].u[1] = 1;
		smTexLinkMotionBlur2[TlCnt].u[2] = 1;

		TlCnt++;

		fVCnt = fVCnt2;
		fVCnt2 += fBlurLevel;

	}

	MbCnt = 0;
	MvCnt = 0;

	ZeroMemory(MbVertex, sizeof(smVERTEX) * 32);

	for (cnt = 0; cnt < 16; cnt++)
	{

		MbFace2[MbCnt].lpTexLink = &smTexLinkMotionBlur2[MbCnt];
		MbFace2[MbCnt].v[0] = MvCnt;
		MbFace2[MbCnt].v[1] = MvCnt + 1;
		MbFace2[MbCnt].v[2] = MvCnt + 2;
		MbFace2[MbCnt].v[3] = MatMBlur;
		MbCnt++;

		MbFace2[MbCnt].lpTexLink = &smTexLinkMotionBlur2[MbCnt];
		MbFace2[MbCnt].v[0] = MvCnt + 2;
		MbFace2[MbCnt].v[1] = MvCnt + 1;
		MbFace2[MbCnt].v[2] = MvCnt + 3;
		MbFace2[MbCnt].v[3] = MatMBlur;
		MbCnt++;
		MvCnt += 2;

	}

	return TRUE;
}

int GetProjPosi(int &x3d, int &y3d, int &z3d, POINT3D *CameraPosi, POINT3D *CameraAngle)
{

	int x2d, y2d;
	smMATRIX	trans, rX, rY, rZ, rm;

	int sx, sy, sz;
	int cx, cy, cz;

	cx = x3d - CameraPosi->x;
	cy = y3d - CameraPosi->y;
	cz = z3d - CameraPosi->z;

	smIdentityMatrix(rX);
	smIdentityMatrix(rY);
	smIdentityMatrix(rZ);
	smIdentityMatrix(trans);
	smZeroMatrix(rm);

	smRotateXMatrix(rX, (-CameraAngle->x)&ANGCLIP);
	smRotateYMatrix(rY, (-CameraAngle->y)&ANGCLIP);
	smRotateZMatrix(rZ, (-CameraAngle->z)&ANGCLIP);
	smTranslateMatrix(trans, cx, cy, cz);

	smMatrixMult(rm, trans, rY);
	smMatrixMult(rm, rm, rX);
	smMatrixMult(rm, rm, rZ);


	sx = x3d * rm._11 +
		y3d * rm._21 +
		z3d * rm._31;


	sy = x3d * rm._12 +
		y3d * rm._22 +
		z3d * rm._32;

	sz = x3d * rm._13 +
		y3d * rm._23 +
		z3d * rm._33;

	x3d = (sx >> FLOATNS) + rm._41;
	y3d = (sy >> FLOATNS) + rm._42;
	z3d = (sz >> FLOATNS) + rm._43;


	if (z3d > 0)
	{
		x3d = MidX + ((x3d * viewdistZ) / z3d);
		y3d = MidY - ((y3d * viewdistZ) / z3d);
		z3d >>= FLOATNS;
		return TRUE;

	}
	else
	{
		x2d = CLIP_OUT;
		y2d = CLIP_OUT;
		return FALSE;
	}

}


#define ITEM_TRANS_LIMIT_TIME		10000

scITEM::scITEM()
{
	Init();
}

scITEM::~scITEM()
{
	Close();
}

void scITEM::Init()
{
	ZeroMemory(&Head, sizeof(scITEM));
}

int scITEM::Close()
{

	Flag = 0;

	if (lpDinaPattern)
	{
		AddRemoveDynPattern(lpDinaPattern);

		lpDinaPattern = 0;
	}

	Pattern = 0;

	return TRUE;
}


int scITEM::SetPattern(smPAT3D *pat)
{
	Pattern = pat;
	return TRUE;
}


int scITEM::SetPosi(int x, int y, int z)
{

	int py2 = 0;

	pX = x;
	pZ = z;
	pY = y;

	if (pY == 0)
	{
		if (smGameStage[0])
			pY = smGameStage[0]->GetHeight(pX, pZ);

		if (smGameStage[1])
			py2 = smGameStage[1]->GetHeight(pX, pZ);

		if (py2 > pY)
			pY = py2;
	}

	return TRUE;
}


int scITEM::SetTransItem(TRANS_ITEM *lpTransItem)
{
	dwLastTransTime = dwPlayTime;



	Flag = TRUE;

	strcpy_s(szName, lpTransItem->szName);

	SetPosi(lpTransItem->x, lpTransItem->y, lpTransItem->z);
	lpStgArea = lpTransItem->lpStgArea;

	ItemCode = lpTransItem->ItemCode;


	Angle.y = ((pX + pZ) >> 2)&ANGCLIP;

	if (sinGetItemInfo(ItemCode, szModelName) == FALSE || ItemCode == 0)
		strcpy_s(szModelName, "char\\flag\\flag.ini");



	if (!PatLoading)
		AddLoaderItem(this, szModelName);

	return TRUE;
}

int scITEM::Draw()
{
	POINT3D CameraPosi, CameraAngle;
	POINT3D angle;

	int r, g, b;
	int scale;

	if (ItemCode == 0 && !DisplayDebug)
		return FALSE;


	if (!DisplayFlag || !Pattern)
		return FALSE;


	if (dwPlayTime > (dwLastTransTime + ITEM_TRANS_LIMIT_TIME))
	{
		Close();
		return FALSE;
	}

	CameraPosi.x = smCHAR_CameraX;
	CameraPosi.y = smCHAR_CameraY;
	CameraPosi.z = smCHAR_CameraZ;

	CameraAngle.x = smCHAR_CameraAngX;
	CameraAngle.y = smCHAR_CameraAngY;
	CameraAngle.z = smCHAR_CameraAngZ;

	memcpy(&angle, &Angle, sizeof(POINT3D));

	Posi.x = pX;
	Posi.y = pY + 6 * fONE;
	Posi.z = pZ;

	int	BlinkFlag;

	BlinkFlag = FALSE;

	if ((ItemCode&sinITEM_MASK1) == sinITEM_WEAPON)
		angle.x = ANGLE_90;

	if (ItemCode && (dwPlayTime & 0x80))
		BlinkFlag = TRUE;



	if (lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->FieldCode == rsSOD_FIELD)
	{
		if ((ItemCode&sinITEM_MASK2) == sinPM1 || (ItemCode&sinITEM_MASK2) == sinSD2)
		{
			scale = (dwPlayTime >> 2) & 0x1FF;

			if ((scale & 0x100) != 0)
				scale = fONE - (scale & 0xFF);

			if ((ItemCode&sinITEM_MASK2) == sinPM1)
				scale *= 3;

			smRender.ObjectVertexScale = scale + fONE;
		}
	}

	if (BlinkFlag)
	{
		r = smRender.Color_R;
		g = smRender.Color_G;
		b = smRender.Color_B;

		smRender.Color_R += 100;
		smRender.Color_G += 100;
		smRender.Color_B += 100;

		Pattern->SetPosi(&Posi, &angle);
		Pattern->Frame = 0;
		Pattern->RenderD3D(&CameraPosi, &CameraAngle);

		smRender.Color_R = r;
		smRender.Color_G = g;
		smRender.Color_B = b;
	}
	else
	{
		Pattern->SetPosi(&Posi, &angle);
		Pattern->Frame = 0;
		Pattern->RenderD3D(&CameraPosi, &CameraAngle);
	}

	smRender.ObjectVertexScale = 0;

	return TRUE;
}




DWORD	Ptect_RestartCounter = 0;
DWORD	Ptect_RestartMask = 0;


int	Ptect_IncAttackCount(int Flag)
{
	DWORD	rc;
	smTRANS_COMMAND	smTransCommand;

	rc = Ptect_RestartCounter ^ Ptect_RestartMask;
	Ptect_RestartMask = dwPlayTime;

	switch (Flag)
	{
	case -1:
		rc = 0;
		break;
	case 0:
		rc++;
		break;
	}

	if (rc > 160)
	{

		smTransCommand.code = OpCode::OPCODE_WARNING_BLINK_ATT;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = rc;
		smTransCommand.LParam = 0;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = 0;
		if (smWsockDataServer) smWsockDataServer->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
		rc = 0;
	}

	rc = rc ^ Ptect_RestartMask;
	Ptect_RestartCounter = rc;

	return TRUE;
}


DWORD Ptect_GetAttackCount()
{
	DWORD	rc;
	rc = Ptect_RestartCounter ^ Ptect_RestartMask;
	Ptect_RestartMask = dwPlayTime;
	Ptect_RestartCounter = rc ^ Ptect_RestartMask;

	return rc;
}


int UpdateCastleMasterClan(DWORD dwMasterClan)
{
	int cnt;

	SetClanMaster_Player(dwMasterClan);

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].dwObjectSerial)
		{
			if (chrOtherPlayer[cnt].smCharInfo.ClassClan && GetClanCode(chrOtherPlayer[cnt].smCharInfo.ClassClan) == dwMasterClan)
				lpCurPlayer->Clan_CastleMasterFlag = TRUE;
			else
				lpCurPlayer->Clan_CastleMasterFlag = FALSE;
		}
	}

	return TRUE;
}


int SetClanMaster_Player(DWORD dwMasterClan)
{
	if (lpCurPlayer->smCharInfo.ClassClan && GetClanCode(lpCurPlayer->smCharInfo.ClassClan) == dwMasterClan)
		lpCurPlayer->Clan_CastleMasterFlag = TRUE;
	else
		lpCurPlayer->Clan_CastleMasterFlag = FALSE;

	return lpCurPlayer->Clan_CastleMasterFlag;

}