

#include "smlib3d\\smd3d.h"

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
#include "Resources\resource.h"
#include "drawsub.h"
#include "Language\\language.h"

#include "tjboy\\clanmenu\\tjclanDEF.h"
#include "tjboy\\clanmenu\\tjclan.h"
#include "tjboy\\clanmenu\\cE_CViewClanInfo.h"

#include "Server\\onserver.h"

#include "BellatraFontEffect.h"
#include "TextMessage.h"
#include "cPartyWindow.h"



#include "WinInt\\WinIntThread.h"
#include "FullZoomMap.h"
#include "FontImage.h"


extern HINSTANCE hinst;



int rsCheckHardCoreEventArea(int x, int y, int z);
extern POINT3D	rsHardCoreEventOpenPos[7][3];



int	CodeXorExp = 0;
int	CodeXorExp_High = 0;
int	CodeXorLife = 0;
int	CodeXorMana = 0;
int	CodeXorStamina = 0;
int	CodeXorMoney = 0;


#define	PLAYSUB_CHECKRESULT			                                                               1884018394

DWORD	dwPlaySub_CheckResult = PLAYSUB_CHECKRESULT;

static char *szArmorDirectory = "char\\tmABCD\\";
static char *szNpcDirectory = "char\\npc\\";

#include "playmodel.h"

int ArmorJobNum[11] = { 0, 1, 0, 3, 2, 5, 4, 7, 6, 8, 9 };

int	PlayerArmor = 0;

#define TEMP_DYNPAT_MAX		2048

smDPAT	*DynTempPat[TEMP_DYNPAT_MAX];

int DynTempPatCnt = 0;

int	PlayUsed_Resurrection = 0;


DWORD	dwSafeCodeSum;

BYTE	dwAsmJmpCode = 0xE0;

DWORD	dwStartFuncPoint = 0;
DWORD	dwFuncLen = 0;
DWORD	dwFuncSafeMemCount;
DWORD	dwFuncSafeMemCode;


DWORD	dwFuncChkTime = 0;
DWORD	dwFuncSafeCode = 0;


char	*lpFuncBackupBuff = 0;



LPDIRECT3DTEXTURE9	lpDDS_CodeSaveBuff = 0;

extern char *szBangImage;

DWORD	*lpCodeVram = 0;


int	PlaySub_StartFunc()
{
	return FALSE;
}


int Code_VRamBuffOpen()
{

	lpCodeVram = new DWORD[256];

	return (DWORD)lpCodeVram;

}

int Code_VramClear()
{
	lpCodeVram[0] = 777;
	lpCodeVram[1] = 0;
	lpCodeVram[2] = 777;
	lpCodeVram[3] = 0;

	return TRUE;
}

int Code_VramSave(DWORD Param1, DWORD Param2, DWORD Param3)
{
	DWORD	dwTime;

	if(lpCodeVram)
	{
		dwTime = GetCurrentTime();

		lpCodeVram[3] = dwTime;
		lpCodeVram[0] = Param1^dwTime;
		lpCodeVram[1] = Param2^dwTime;
		lpCodeVram[2] = Param3^dwTime;
	}

	return TRUE;
}

int Code_VramLoad(DWORD *Param1, DWORD *Param2, DWORD *Param3)
{
	*Param1 = lpCodeVram[0] ^ lpCodeVram[3];
	*Param2 = lpCodeVram[1] ^ lpCodeVram[3];
	*Param3 = lpCodeVram[2] ^ lpCodeVram[3];

	return TRUE;
}

int	Mix_CodeVram()
{
	DWORD	dwTime;
	DWORD	dwNewTime;


	dwTime = (dwPlayTime >> 4) & 0xFF;
	dwNewTime = (dwTime << 24) | (dwTime << 16) | (dwTime << 8) | dwTime;

	dwTime = lpCodeVram[3];

	lpCodeVram[0] = (lpCodeVram[0] ^ dwTime) ^ dwNewTime;
	lpCodeVram[1] = (lpCodeVram[1] ^ dwTime) ^ dwNewTime;
	lpCodeVram[2] = (lpCodeVram[2] ^ dwTime) ^ dwNewTime;
	lpCodeVram[3] = dwNewTime;

	return TRUE;
}





DWORD Check_CodeSafe(DWORD dwStartFunc)
{
	BYTE	*lpFunc;
	DWORD	dwCode;
	DWORD	*lpdwFunc;
	BYTE	JmpCode = 9;
	DWORD	dwHeaderPos = 0x30;

	dwCode = 1697348954;

	dwFuncChkTime = GetCurrentTime();
	DWORD FnCode = dwCode ^ ((dwFuncChkTime << 16) | (dwFuncChkTime & 0xFFFF));

	dwFuncSafeCode = FnCode;
	dwFuncSafeMemCount = 0;
	dwFuncSafeMemCode = 0;

	Code_VramSave(FnCode, dwFuncChkTime, dwCode);

	lpFunc = 0;
	lpdwFunc = 0;

	return dwCode;
}


DWORD Check_CodeSafe2()
{

	DWORD	*lpdwFunc;
	DWORD	dwCode;
	int cnt;

	lpdwFunc = (DWORD *)(dwStartFuncPoint ^ (dwFuncLen << 8));

	if(dwFuncLen > 200000)
		return FALSE;

	for(cnt = 0; cnt < 32; cnt++)
	{


		dwFuncSafeMemCode = dwFuncSafeMemCode + (lpdwFunc[dwFuncSafeMemCount++] * ((dwFuncSafeMemCount & 0x3) + 1));

		if(dwFuncSafeMemCount >= dwFuncLen)
		{
			dwFuncChkTime = GetCurrentTime();
			dwCode = dwFuncSafeMemCode ^ ((dwFuncChkTime << 16) | (dwFuncChkTime & 0xFFFF));
			dwFuncSafeCode = dwCode;

			Code_VramSave(dwCode, dwFuncChkTime, dwFuncSafeMemCode);



			dwFuncSafeMemCount = 0;
			dwFuncSafeMemCode = 0;
			lpdwFunc = 0;

			return TRUE;
		}
	}

	lpdwFunc = 0;
	return FALSE;
}


DWORD	GetSafeCode()
{
	return dwFuncSafeCode ^ ((dwFuncChkTime << 16) | (dwFuncChkTime & 0xFFFF));
}


DWORD	GetSafeCode2()
{
	DWORD	dwCode, dwFnChkTime, dwFnSafeCode;
	DWORD	dwOriginal;

	Code_VramLoad(&dwCode, &dwFnChkTime, &dwFnSafeCode);

	dwOriginal = dwCode ^ ((dwFnChkTime << 16) | (dwFnChkTime & 0xFFFF));

	if((dwOriginal^dwFnSafeCode) == 0) return dwOriginal;
	return FALSE;
}


int	LoadOftenMeshPattern(char *szFileName)
{
	DynTempPat[DynTempPatCnt] = smPattern.LoadCharactor(szFileName);
	if(DynTempPat[DynTempPatCnt])
	{
		DynTempPat[DynTempPatCnt]->UseCount = 99;
		DynTempPatCnt++;
		return TRUE;
	}

	return FALSE;
}

#ifdef _CHECK_MESH

static DWORD dwOftPatSum = 0;

int	LoadOftenMeshPatternCheckSum(char *szFileName)
{
	smPAT3D *lpPat3D;

	DynTempPat[DynTempPatCnt] = smPattern.LoadCharactor(szFileName);
	if(DynTempPat[DynTempPatCnt])
	{
		lpPat3D = DynTempPat[DynTempPatCnt]->Pat;
		int szX = 0; int szN = 0;
		for(int cnt = 0; cnt < lpPat3D->nObj3d; cnt++)
		{
			if(szX < lpPat3D->obj3d[cnt]->maxY)
				szX = lpPat3D->obj3d[cnt]->maxY;
			if(szN < lpPat3D->obj3d[cnt]->minY)
				szN = lpPat3D->obj3d[cnt]->minY;
		}
		DynTempPat[DynTempPatCnt]->UseCount = 99;
		DynTempPatCnt++;

		DWORD dwSpdSum = GetSpeedSum(szFileName);
		DWORD dwSizSum = (szX << 4) | (szN << 1);
		dwOftPatSum += dwSpdSum + (dwSpdSum * dwSizSum) + dwSizSum;
		return TRUE;
	}

	return FALSE;
}


int Send_OftPatSumToDataServer()
{

	smTRANS_COMMAND	smTransCommand;
	smTransCommand.code = OpCode::OPCODE_CHECK_ITEMMESH;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = dwOftPatSum;
	smTransCommand.SParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.EParam = 0;

	dwOftPatSum = 0;

	if(smWsockDataServer)
		return smWsockDataServer->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

	return FALSE;
}
#endif

int	LoadOftenFullPattern()
{
	int cnt, cnt2;
	int	ErrorCount;
	char	szBuff[128];

	ErrorCount = 0;

	for(cnt = 0; cnt < MAX_JOBNUM; cnt++)
	{
		for(cnt2 = 0; cnt2 < ARMOR_FILE_MAX; cnt2++)
		{
			strcpy_s(szBuff, szArmorDirectory);
			lstrcat(szBuff, szArmorNumFile[cnt][cnt2]);

			if(LoadOftenMeshPattern(szBuff) == FALSE)
				ErrorCount++;
		}
	}

	for(cnt = 0; cnt < MAX_JOBNUM; cnt++)
	{
		for(cnt2 = 0; cnt2 < ARMOR_FILE_MAX; cnt2++)
		{
			strcpy_s(szBuff, szArmorDirectory);
			lstrcat(szBuff, szArmorNumFile_Comic[cnt][cnt2]);

			if(LoadOftenMeshPattern(szBuff) == FALSE)
				ErrorCount++;
		}
	}


	for(cnt = 0; cnt < FACE_MODEL_MAX; cnt++)
	{
		for(cnt2 = 0; cnt2 < HEAREPOTION_MAX; cnt2++)
		{
			if(LoadOftenMeshPattern(szModel_FighterFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if(LoadOftenMeshPattern(szModel_MechFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if(LoadOftenMeshPattern(szModel_ArcherFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if(LoadOftenMeshPattern(szModel_PikeFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if(LoadOftenMeshPattern(szModel_KnightFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if(LoadOftenMeshPattern(szModel_AtalantaFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if(LoadOftenMeshPattern(szModel_PristessFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if(LoadOftenMeshPattern(szModel_MagicanFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if (LoadOftenMeshPattern(szModel_AssassineFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if (LoadOftenMeshPattern(szModel_ShamanFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
		}
	}





	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;

	char	szFindPath[64];
	char	szFilePath[64];

	strcpy_s(szFindPath, szNpcDirectory);
	lstrcat(szFindPath, "*.ini");

	hFindHandle = FindFirstFile(szFindPath, &fd);
	if(hFindHandle != INVALID_HANDLE_VALUE)
	{
		while(1)
		{
			strcpy_s(szFilePath, szNpcDirectory);
			lstrcat(szFilePath, fd.cFileName);

			LoadOftenMeshPattern(szFilePath);


			if(FindNextFile(hFindHandle, &fd) == FALSE) break;
		}
	}
	FindClose(hFindHandle);


	return ErrorCount;
}


int LoadOftenModels()
{

	return TRUE;
}

char *szOftenNPC[] = {

	0
};


int LoadFolder_Ini(char *szPath, char *szWildCard, char *szChgExt, int OftSave);

int Make_CharAll_SMD()
{
	LoadOftenFullPattern();
	LoadFolder_Ini("Char\\Npc", "*.ini", 0, 0);
	LoadFolder_Ini("Char\\Monster", "*.ini", 0, 0);

	return TRUE;
}


int LoadOftenNpc()
{
#ifdef _W_SERVER
	LoadFolder_Ini("Char\\Npc", "*.inx", "ini", TRUE);
#else
	int cnt = 0;
	while(1)
	{
		if(!szOftenNPC[cnt])
			break;
		LoadOftenMeshPattern(szOftenNPC[cnt]);
		cnt++;
	}
#endif

	return TRUE;
}


int LoadOftenFace()
{

	int cnt, cnt2;
	int ErrorCount = 0;

	for(cnt = 0; cnt < 6; cnt++)
	{

		for(cnt2 = 0; cnt2 < HEAREPOTION_MAX; cnt2++)
		{
			if(LoadOftenMeshPattern(szModel_FighterFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if(LoadOftenMeshPattern(szModel_MechFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if(LoadOftenMeshPattern(szModel_ArcherFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if(LoadOftenMeshPattern(szModel_PikeFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if(LoadOftenMeshPattern(szModel_KnightFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if(LoadOftenMeshPattern(szModel_AtalantaFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if(LoadOftenMeshPattern(szModel_PristessFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if(LoadOftenMeshPattern(szModel_MagicanFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if (LoadOftenMeshPattern(szModel_AssassineFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
			if (LoadOftenMeshPattern(szModel_ShamanFaceName[cnt][cnt2]) == FALSE)
				ErrorCount++;
		}
	}

	if(ErrorCount)
		return FALSE;

	return TRUE;

}

//Teste Armaduras
int LoadOftenArmor()
{
	int cntW, cntH;
	char szName[128];

	for(cntH = 0; cntH < MAX_JOBNUM; cntH++)
	{
		for(cntW = 0; cntW < 29; cntW++) 
		{
			if(cntW == 0 || cntW >= 10)
			{
				strcpy_s(szName, szArmorDirectory);
				lstrcat(szName, szArmorNumFile[cntH][cntW]);
				LoadOftenMeshPattern(szName);
			}
		}
	}

	return TRUE;
}


int LoadOftenItem()
{
	char szBuff[256];

	for(int cnt = 0; cnt < MAX_ITEM; cnt++)
	{
		if(sItem[cnt].DorpItem == NULL)
		{
			continue;
		}

		wsprintf(szBuff, "Image\\sinImage\\Items\\DropItem\\it%s.ASE", sItem[cnt].DorpItem);

#ifdef _CHECK_MESH
		LoadOftenMeshPatternCheckSum(szBuff);

#else
		LoadOftenMeshPattern(szBuff);
#endif
		if(sItem[cnt].CODE == (sinGG1 | sin01) || sItem[cnt].CODE == (sinGG1 | sin02))
		{
			continue;
		}
	}

#ifdef _CHECK_MESH
	Send_OftPatSumToDataServer();
#endif

	return TRUE;
}


int CheckOftenMeshTextureSwap()
{
	return TRUE;

	for(int cnt = 0; cnt < DynTempPatCnt; cnt++)
	{
		if(DynTempPat[cnt] && DynTempPat[cnt]->Pat && DynTempPat[cnt]->Pat->smMaterialGroup)
		{
			DynTempPat[cnt]->Pat->smMaterialGroup->CheckMatreialTextureSwap();
		}
	}
	return TRUE;
}


int SetPlayerArmor(int armor)
{
	char szbuff[256];

	if(PlayerArmor == armor)
		return FALSE;
	if(lpCurPlayer->PatLoading)
		return FALSE;
	if(!lpCurPlayer->smCharInfo.szModelName2[0])
		return FALSE;
	if(armor == -1)
		armor = 0;

	int jobNum = lpCurPlayer->smCharInfo.JOB_CODE;
	if(armor > ARMOR_FILE_MAX - 1)
		armor = ARMOR_FILE_MAX - 1;
	if(jobNum > MAX_JOBNUM)
		jobNum = 0;

	strcpy_s(szbuff, szArmorDirectory);

	if(lpCurPlayer->smCharInfo.SizeLevel > 0x1000 && lpCurPlayer->smCharInfo.SizeLevel <= 0x1002)
		lstrcat(szbuff, szArmorNumFile_Comic[ArmorJobNum[jobNum]][armor]);
	else
		lstrcat(szbuff, szArmorNumFile[ArmorJobNum[jobNum]][armor]);

	lpCurPlayer->PatLoading = TRUE;
	AddLoaderPattern(lpCurPlayer, szbuff, lpCurPlayer->smCharInfo.szModelName2);

	PlayerArmor = armor;

	return TRUE;
}


int SetChrArmor(smCHAR *lpChar, int ItemNum)
{
	char szbuff[256];
	int armor;
	int jobNum;

	if(!lpChar->DisplayFlag || lpChar->wStickItems[smPLAYBUFF_ITEM_BODY] == ItemNum) return FALSE;
	if(lpChar->PatLoading) return FALSE;
	if(!lpChar->smCharInfo.szModelName2[0]) return FALSE;

	int iExtraCostume = 0;
	if((sItem[ItemNum].CODE&sinITEM_MASK2) == sinCA1 || (sItem[ItemNum].CODE&sinITEM_MASK2) == sinCA2)
		iExtraCostume = 59;

	if(((sItem[ItemNum].CODE&sinITEM_MASK3) >> 8) > 29)
		armor = (((sItem[ItemNum].CODE&sinITEM_MASK3) >> 8) - 17) + iExtraCostume;
	else
		armor = ((sItem[ItemNum].CODE&sinITEM_MASK3) >> 8) + iExtraCostume;

	jobNum = lpChar->smCharInfo.JOB_CODE;
	if(armor > ARMOR_FILE_MAX - 1)
		armor = ARMOR_FILE_MAX - 1;
	if(jobNum > MAX_JOBNUM) jobNum = 0;

	lstrcpy(szbuff, szArmorDirectory);

	if(lpChar->smCharInfo.SizeLevel > 0x1000 && lpChar->smCharInfo.SizeLevel <= 0x1002)
		lstrcat(szbuff, szArmorNumFile_Comic[ArmorJobNum[jobNum]][armor]);
	else
		lstrcat(szbuff, szArmorNumFile[ArmorJobNum[jobNum]][armor]);

	lpChar->PatLoading = TRUE;
	AddLoaderPattern(lpChar, szbuff, lpChar->smCharInfo.szModelName2);

	return TRUE;
}


DWORD GetHairSkinCode(int FaceCode, int HairCode)
{
	return ((FaceCode & 0xFF) << 8) | (HairCode & 0xFF) | ((((FaceCode + 1) + (HairCode + 1) * 3) & 0xFF) << 16);
}


int CheckHairSkinCode(DWORD dwModelCode)
{
	if(dwModelCode)
	{
		int FaceCode = (dwModelCode >> 8) & 0xFF;
		int HairCode = dwModelCode & 0xFF;
		int Sum = (dwModelCode >> 16) & 0xFF;
		if((((FaceCode + 1) + (HairCode + 1) * 3) & 0xFF) == Sum) return TRUE;
	}
	return FALSE;
}


char *GetFaceHairSkin(smCHAR *lpChar)
{

	DWORD dwModelCode = lpChar->smCharInfo.ModelNameCode2;
	int FaceCode = (dwModelCode >> 8) & 0xFF;
	int HairCode = dwModelCode & 0xFF;

	if(CheckHairSkinCode(dwModelCode) == FALSE) return NULL;

	char *szHeadName = 0;

	switch(lpChar->smCharInfo.JOB_CODE)
	{
	case 1:
		szHeadName = szModel_FighterFaceName[FaceCode][HairCode];
		break;
	case 2:
		szHeadName = szModel_MechFaceName[FaceCode][HairCode];
		break;
	case 3:
		szHeadName = szModel_ArcherFaceName[FaceCode][HairCode];
		break;
	case 4:
		szHeadName = szModel_PikeFaceName[FaceCode][HairCode];
		break;
	case 5:
		szHeadName = szModel_AtalantaFaceName[FaceCode][HairCode];
		break;
	case 6:
		szHeadName = szModel_KnightFaceName[FaceCode][HairCode];
		break;
	case 7:
		szHeadName = szModel_MagicanFaceName[FaceCode][HairCode];
		break;
	case 8:
		szHeadName = szModel_PristessFaceName[FaceCode][HairCode];
		break;
	case 9:
		szHeadName = szModel_AssassineFaceName[FaceCode][HairCode];
		break;
	case 10:
		szHeadName = szModel_ShamanFaceName[FaceCode][HairCode];
		break;
	}

	return szHeadName;
}


int FindFaceSkin(smCHAR *lpChar, char *lpHeadName, char ***lpSelFace, char **lpSelFaceName)
{
	int cnt, cnt2;
	int FindCount = 0;
	int FaceCode;
	int HairCode;

	switch(lpChar->smCharInfo.JOB_CODE)
	{
	case JOBCODE_FIGHTER:
		for(cnt = 0; cnt < FACE_MODEL_MAX; cnt++)
		{
			for(cnt2 = 0; cnt2 < HEAREPOTION_MAX; cnt2++)
			{
				if(lstrcmpi(szModel_FighterFaceName[cnt][cnt2], lpHeadName) == 0)
				{
					*lpSelFace = szModel_FighterFaceName[cnt];
					*lpSelFaceName = szModel_FighterFaceName[cnt][cnt2];
					FaceCode = cnt; HairCode = cnt2; FindCount++;
					break;
				}
			}
			if(cnt2 < HEAREPOTION_MAX) break;
		}
		break;
	case JOBCODE_MECHANICIAN:
		for(cnt = 0; cnt < FACE_MODEL_MAX; cnt++)
		{
			for(cnt2 = 0; cnt2 < HEAREPOTION_MAX; cnt2++)
			{
				if(lstrcmpi(szModel_MechFaceName[cnt][cnt2], lpHeadName) == 0)
				{
					*lpSelFace = szModel_MechFaceName[cnt];
					*lpSelFaceName = szModel_MechFaceName[cnt][cnt2];
					FaceCode = cnt; HairCode = cnt2; FindCount++;
					break;
				}
			}
			if(cnt2 < HEAREPOTION_MAX) break;
		}
		break;
	case JOBCODE_ARCHER:
		for(cnt = 0; cnt < FACE_MODEL_MAX; cnt++)
		{
			for(cnt2 = 0; cnt2 < HEAREPOTION_MAX; cnt2++)
			{
				if(lstrcmpi(szModel_ArcherFaceName[cnt][cnt2], lpHeadName) == 0)
				{
					*lpSelFace = szModel_ArcherFaceName[cnt];
					*lpSelFaceName = szModel_ArcherFaceName[cnt][cnt2];
					FaceCode = cnt; HairCode = cnt2; FindCount++;
					break;
				}
			}
			if(cnt2 < HEAREPOTION_MAX) break;
		}
		break;
	case JOBCODE_PIKEMAN:
		for(cnt = 0; cnt < FACE_MODEL_MAX; cnt++)
		{
			for(cnt2 = 0; cnt2 < HEAREPOTION_MAX; cnt2++)
			{
				if(lstrcmpi(szModel_PikeFaceName[cnt][cnt2], lpHeadName) == 0)
				{
					*lpSelFace = szModel_PikeFaceName[cnt];
					*lpSelFaceName = szModel_PikeFaceName[cnt][cnt2];
					FaceCode = cnt; HairCode = cnt2; FindCount++;
					break;
				}
			}
			if(cnt2 < HEAREPOTION_MAX) break;

		}
		break;
	case JOBCODE_ATALANTA:
		for(cnt = 0; cnt < FACE_MODEL_MAX; cnt++)
		{
			for(cnt2 = 0; cnt2 < HEAREPOTION_MAX; cnt2++)
			{
				if(lstrcmpi(szModel_AtalantaFaceName[cnt][cnt2], lpHeadName) == 0)
				{
					*lpSelFace = szModel_AtalantaFaceName[cnt];
					*lpSelFaceName = szModel_AtalantaFaceName[cnt][cnt2];
					FaceCode = cnt; HairCode = cnt2; FindCount++;
					break;
				}
			}
			if(cnt2 < HEAREPOTION_MAX) break;
		}
		break;
	case JOBCODE_KNIGHT:
		for(cnt = 0; cnt < FACE_MODEL_MAX; cnt++)
		{
			for(cnt2 = 0; cnt2 < HEAREPOTION_MAX; cnt2++)
			{
				if(lstrcmpi(szModel_KnightFaceName[cnt][cnt2], lpHeadName) == 0)
				{
					*lpSelFace = szModel_KnightFaceName[cnt];
					*lpSelFaceName = szModel_KnightFaceName[cnt][cnt2];
					FaceCode = cnt; HairCode = cnt2; FindCount++;
					break;
				}
			}
			if(cnt2 < HEAREPOTION_MAX) break;
		}
		break;
	case JOBCODE_MAGICIAN:
		for(cnt = 0; cnt < FACE_MODEL_MAX; cnt++)
		{
			for(cnt2 = 0; cnt2 < HEAREPOTION_MAX; cnt2++)
			{
				if(lstrcmpi(szModel_MagicanFaceName[cnt][cnt2], lpHeadName) == 0)
				{
					*lpSelFace = szModel_MagicanFaceName[cnt];
					*lpSelFaceName = szModel_MagicanFaceName[cnt][cnt2];
					FaceCode = cnt; HairCode = cnt2; FindCount++;
					break;
				}
			}
			if(cnt2 < HEAREPOTION_MAX) break;
		}
		break;
	case JOBCODE_PRIESTESS:
		for(cnt = 0; cnt < FACE_MODEL_MAX; cnt++)
		{
			for(cnt2 = 0; cnt2 < HEAREPOTION_MAX; cnt2++)
			{
				if(lstrcmpi(szModel_PristessFaceName[cnt][cnt2], lpHeadName) == 0)
				{
					*lpSelFace = szModel_PristessFaceName[cnt];
					*lpSelFaceName = szModel_PristessFaceName[cnt][cnt2];
					FaceCode = cnt; HairCode = cnt2; FindCount++;
					break;
				}
			}
			if(cnt2 < HEAREPOTION_MAX) break;
		}
		break;
	case JOBCODE_ASSASSINE:
		for (cnt = 0; cnt < FACE_MODEL_MAX; cnt++)

		{
			for (cnt2 = 0; cnt2 < HEAREPOTION_MAX; cnt2++)

			{
				if (lstrcmpi(szModel_AssassineFaceName[cnt][cnt2], lpHeadName) == 0)

				{
					*lpSelFace = szModel_AssassineFaceName[cnt];
					*lpSelFaceName = szModel_AssassineFaceName[cnt][cnt2];
					FaceCode = cnt; HairCode = cnt2; FindCount++;
					break;
				}
			}
			if (cnt2 < HEAREPOTION_MAX)
				break;
		}
		break;
	case JOBCODE_SHAMAN:
		for (cnt = 0; cnt < FACE_MODEL_MAX; cnt++)

		{
			for (cnt2 = 0; cnt2 < HEAREPOTION_MAX; cnt2++)

			{
				if (lstrcmpi(szModel_ShamanFaceName[cnt][cnt2], lpHeadName) == 0)

				{
					*lpSelFace = szModel_ShamanFaceName[cnt];
					*lpSelFaceName = szModel_ShamanFaceName[cnt][cnt2];
					FaceCode = cnt; HairCode = cnt2; FindCount++;
					break;
				}
			}
			if (cnt2 < HEAREPOTION_MAX)
				break;
		}
		break;
	}

	if(!FindCount)
		return -1;

	return (FaceCode << 8) | HairCode;
}


int	ChangeModelSkin(smCHAR *lpChar, int ComicArmor, int ComicHeadNum, char *szArmor, char *szHead)
{
	char szArmorName[32];
	char szHeadName[32];
	char szbuff1[256];
	char szbuff2[256];

	int len, cnt;
	int jobNum;
	int SelCount;
	int FindArmor, FindHead;
	char *lpArmorFile;
	char *lpHeadFile;


	char **lpSelFace = 0;
	char *lpSelFaceName = 0;

	jobNum = lpChar->smCharInfo.JOB_CODE;
	if(jobNum > MAX_JOBNUM) jobNum = 0;

	if(szArmor) lpArmorFile = szArmor;
	else lpArmorFile = lpChar->smCharInfo.szModelName;

	if(szHead) lpHeadFile = szHead;
	else lpHeadFile = lpChar->smCharInfo.szModelName2;

	szArmorName[0] = 0;
	szHeadName[0] = 0;


	len = lstrlen(lpArmorFile);
	for(cnt = len - 1; cnt >= 0; cnt--)
	{
		if(lpArmorFile[cnt] == '\\')
		{
			strcpy_s(szArmorName, &lpArmorFile[cnt + 1]);
			break;
		}
	}

	strcpy_s(szHeadName, lpHeadFile);


	if(!szArmorName[0] || !szHeadName[0])
		return FALSE;

	SelCount = ComicHeadNum;

	FindArmor = 0;
	FindHead = 0;

	for(cnt = 0; cnt < ARMOR_FILE_MAX; cnt++)
	{
		if(lstrcmpi(szArmorName, szArmorNumFile[ArmorJobNum[jobNum]][cnt]) == 0)
		{
			if(ComicArmor)
				strcpy_s(szArmorName, szArmorNumFile_Comic[ArmorJobNum[jobNum]][cnt]);
			else
				strcpy_s(szArmorName, szArmorNumFile[ArmorJobNum[jobNum]][cnt]);

			FindArmor++;
			break;
		}
	}

	if(!FindArmor)
	{
		for(cnt = 0; cnt < ARMOR_FILE_MAX; cnt++)
		{
			if(lstrcmpi(szArmorName, szArmorNumFile_Comic[ArmorJobNum[jobNum]][cnt]) == 0)
			{
				if(ComicArmor)
					strcpy_s(szArmorName, szArmorNumFile_Comic[ArmorJobNum[jobNum]][cnt]);
				else
					strcpy_s(szArmorName, szArmorNumFile[ArmorJobNum[jobNum]][cnt]);

				FindArmor++;
				break;
			}
		}
	}


	int FindFaceValue = FindFaceSkin(lpChar, szHeadName, &lpSelFace, &lpSelFaceName);
	if(FindFaceValue < 0) return FALSE;
	int HairCode = FindFaceValue & 0xFF;
	int FaceCode = FindFaceValue >> 8;


	if(CheckHairSkinCode(lpChar->smCharInfo.ModelNameCode2) == FALSE)
	{
		lpChar->smCharInfo.ModelNameCode2 = GetHairSkinCode(FaceCode, HairCode);
	}

	switch(jobNum)
	{
	case JOBCODE_FIGHTER:
		strcpy_s(szHeadName, szModel_FighterFaceName[SelCount][HairCode]);
		break;
	case JOBCODE_MECHANICIAN:
		strcpy_s(szHeadName, szModel_MechFaceName[SelCount][HairCode]);
		break;
	case JOBCODE_ARCHER:
		strcpy_s(szHeadName, szModel_ArcherFaceName[SelCount][HairCode]);
		break;
	case JOBCODE_PIKEMAN:
		strcpy_s(szHeadName, szModel_PikeFaceName[SelCount][HairCode]);
		break;
	case JOBCODE_ATALANTA:
		strcpy_s(szHeadName, szModel_AtalantaFaceName[SelCount][HairCode]);
		break;
	case JOBCODE_KNIGHT:
		strcpy_s(szHeadName, szModel_KnightFaceName[SelCount][HairCode]);
		break;
	case JOBCODE_MAGICIAN:
		strcpy_s(szHeadName, szModel_MagicanFaceName[SelCount][HairCode]);
		break;
	case JOBCODE_PRIESTESS:
		strcpy_s(szHeadName, szModel_PristessFaceName[SelCount][HairCode]);
		break;
	case JOBCODE_ASSASSINE:
		strcpy_s(szHeadName, szModel_AssassineFaceName[SelCount][HairCode]);
		break;
	case JOBCODE_SHAMAN:
		strcpy_s(szHeadName, szModel_ShamanFaceName[SelCount][HairCode]);
		break;
	}

	strcpy_s(szbuff1, szArmorDirectory);
	lstrcat(szbuff1, szArmorName);
	strcpy_s(szbuff2, szHeadName);

	lpChar->PatLoading = TRUE;
	AddLoaderPattern(lpChar, szbuff1, szbuff2);

	return TRUE;
}

			 void ResetHairModel()
{
	char szDefaultHeadModel[260] = { 0 };

	char c[2] = { 0 };
	int r = (int)lpCurPlayer->smCharInfo.ChangeJob;
	if(r > 0)
		c[0] = ('a' + (r - 1));

	char cl[2] = { 0 };
	if(r == 2)
		cl[0] = '_';
	else
		cl[0] = '-';

	switch(lpCurPlayer->smCharInfo.JOB_CODE)
	{
	case 1:
		wsprintf(szDefaultHeadModel, "char\\tmABCD\\tmh%sB01%s.inf", cl, c);
		break;
	case 2:
		wsprintf(szDefaultHeadModel, "char\\tmABCD\\tmh%sA01%s.inf", cl, c);
		break;
	case 3:
		wsprintf(szDefaultHeadModel, "char\\tmABCD\\tfh%sD01%s.inf", cl, c);
		break;
	case 4:
		wsprintf(szDefaultHeadModel, "char\\tmABCD\\tmh%sC01%s.inf", cl, c);
		break;
	case 5:
		wsprintf(szDefaultHeadModel, "char\\tmABCD\\Mfh%sB01%s.inf", cl, c);
		break;
	case 6:
		wsprintf(szDefaultHeadModel, "char\\tmABCD\\Mmh%sA01%s.inf", cl, c);
		break;
	case 7:
		wsprintf(szDefaultHeadModel, "char\\tmABCD\\Mmh%sD01%s.inf", cl, c);
		break;
	case 8:
		wsprintf(szDefaultHeadModel, "char\\tmABCD\\Mfh%sC01%s.inf", cl, c);
		break;
	}

	char **lpSelFace = 0;
	char *lpSelFaceName = 0;

	int FindFaceValue = FindFaceSkin(lpCurPlayer, szDefaultHeadModel, &lpSelFace, &lpSelFaceName);

	if(FindFaceValue < 0)
		return;

	int HairCode = FindFaceValue & 0xFF;
	int FaceCode = FindFaceValue >> 8;

	lpCurPlayer->smCharInfo.ModelNameCode2 = GetHairSkinCode(FaceCode, HairCode);

	lstrcpy(lpCurPlayer->smCharInfo.szModelName2, szDefaultHeadModel);

	lpCurPlayer->PatLoading = TRUE;
	AddLoaderPattern(lpCurPlayer, lpCurPlayer->smCharInfo.szModelName, szDefaultHeadModel);
	lpCurPlayer->DisplayTools = TRUE;

	ReformCharForm();

	lpCurPlayer->smCharInfo.bUpdateInfo[0]++;
	SendSetObjectSerial(lpCurPlayer->dwObjectSerial);

	StartSkill(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, SKILL_UP1);
	SkillPlaySound(SKILL_SOUND_LEARN, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);

	SaveGameData();
}


int funcLuckyBox(int BoxType) {
		smTRANS_COMMAND	smTransCommand;
		smTransCommand.code = OPCODE_LUCKYBOX;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
	    smTransCommand.WParam = BoxType;
	    smTransCommand.SParam = 0;
		smTransCommand.LParam = 0;
		smTransCommand.EParam = 0;

				 if (smWsockDataServer)
					 smWsockDataServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);

				 SendSetObjectSerial(lpCurPlayer->dwObjectSerial);
				 SaveGameData();
				 StartSkill(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, SKILL_UP1);
				 SkillPlaySound(SKILL_SOUND_LEARN, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
				 return TRUE;

}

int ChangeHairModel(int HairCode)
{

	smCHAR *lpChar = lpCurPlayer;
	char *lpHeadName = lpChar->smCharInfo.szModelName2;
	char **lpSelFace = 0;
	char *lpSelFaceName = 0;

	if(HairCode < 0 || HairCode >= HEAREPOTION_MAX)
		return FALSE;

	int FindFaceValue = FindFaceSkin(lpChar, lpHeadName, &lpSelFace, &lpSelFaceName);

	if(FindFaceValue < 0 || lpSelFace == 0)
		return FALSE;

	int FaceCode = FindFaceValue >> 8;

	if(lstrcmpi(lpChar->smCharInfo.szModelName2, lpSelFace[HairCode]) == 0)
		return FALSE;

	strcpy_s(lpChar->smCharInfo.szModelName2, lpSelFace[HairCode]);
	lpChar->smCharInfo.ModelNameCode2 = GetHairSkinCode(FaceCode, HairCode);

	lpChar->PatLoading = TRUE;
	AddLoaderPattern(lpChar, lpChar->smCharInfo.szModelName, lpChar->smCharInfo.szModelName2);

	lpCurPlayer->smCharInfo.bUpdateInfo[0]++;
	ReformCharForm();
	SendSetObjectSerial(lpCurPlayer->dwObjectSerial);
	SaveGameData();

	StartSkill(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, SKILL_UP1);
	SkillPlaySound(SKILL_SOUND_LEARN, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);


	return TRUE;
}



//Cores Aging
const int  CONST_AGINGBCOLOR_MAX = 22;

static short	AgingBlinkColor[CONST_AGINGBCOLOR_MAX][6] =
{
	{ 100,	 40,	 90,	0,	-1,	0			},//+4
	{ 120,	100,	 10,	0,	-1,	0			},//+5
	{   0,	110,	 30,	0,	-1,	0			},//+6
	{   0,	 50,	140,	0,	 0,	smTEXSTATE_FS_SCROLL5	},//+7
	{ 100,	  0,	 90,	0,	 1,	smTEXSTATE_FS_SCROLL6	},//+8
	{ 150,	 60,	  0,	0,	 2,	smTEXSTATE_FS_SCROLL6	},//+9
	{ 150,	 10,	  0,	0,	 3,	smTEXSTATE_FS_SCROLL8	},//+10
	{  20,	220,	190,	0,	 4,	smTEXSTATE_FS_SCROLL8	},//+11
	{  10,	220,	 30,	0,	 4,	smTEXSTATE_FS_SCROLL8	},//+12
	{ 170,	 40,	170,	0,	 4,	smTEXSTATE_FS_SCROLL9	},//+13
	{ 150,	 30,	130,	0,	 4,	smTEXSTATE_FS_SCROLL9	},//+14
	{  30,	190,	255,	0,	 4,	smTEXSTATE_FS_SCROLL9	},//+15
	{ 250,	130,	 30,	0,	 4,	smTEXSTATE_FS_SCROLL9	},//+16
	{ 120,	 30,	 30,	0,	 5,	smTEXSTATE_FS_SCROLL10	},//+17
	{ 130,	  0,	255,	0,	 5,	smTEXSTATE_FS_SCROLL10	},//+18
	{ 110,	240,	 252,	0,	 5,	smTEXSTATE_FS_SCROLL10	},//+19
	{ 255,	 255,	255,	0,	 6,	smTEXSTATE_FS_SCROLL4 },//+20
	{ 0, 256, 768, 0, 2, smTEXSTATE_FS_SCROLL9 },
	{ 768, 256, 0, 0, 2, smTEXSTATE_FS_SCROLL9 },
};
//CORES MIX
static short	CraftBlinkColor[6][6] =
{
	{   133,      201,      253,    0,     5,	smTEXSTATE_FS_SCROLL4	},
	{	240,      201,      253,    0,     5,	smTEXSTATE_FS_SCROLL4	},
	{	240,      201,      100,    0,     5,	smTEXSTATE_FS_SCROLL5	},
	{   0,      0,      20,    0,     18,	smTEXSTATE_FS_SCROLL5	}, //MIX DEVINE
	{	255,      51,      204,    0,     15,	smTEXSTATE_FS_SCROLL5	}, //MIX CELESTO
	{   80,      80,      210,    0,     12,	smTEXSTATE_FS_SCROLL5	}, //MIX MIRAGE

};



int GetItemKindFromBliankColor(smCHARTOOL	*lpCharTool)
{
	int cnt;

	lpCharTool->TexMixCode = -1;
	lpCharTool->TexScroll = 0;

	for(cnt = 0; cnt < CONST_AGINGBCOLOR_MAX; cnt++)
	{
		if(AgingBlinkColor[cnt][0] == lpCharTool->sColors[SMC_R] &&
			AgingBlinkColor[cnt][1] == lpCharTool->sColors[SMC_G] &&
			AgingBlinkColor[cnt][2] == lpCharTool->sColors[SMC_B] &&
			AgingBlinkColor[cnt][3] == lpCharTool->sColors[SMC_A])
		{

			lpCharTool->TexMixCode = AgingBlinkColor[cnt][4];
			lpCharTool->TexScroll = AgingBlinkColor[cnt][5];
			return TRUE;
		}
	}

	for(cnt = 0; cnt < 6; cnt++)
	{
		if(CraftBlinkColor[cnt][0] == lpCharTool->sColors[SMC_R] &&
			CraftBlinkColor[cnt][1] == lpCharTool->sColors[SMC_G] &&
			CraftBlinkColor[cnt][2] == lpCharTool->sColors[SMC_B] &&
			CraftBlinkColor[cnt][3] == lpCharTool->sColors[SMC_A])
		{

			lpCharTool->TexMixCode = CraftBlinkColor[cnt][4];//Imagem MixS..
			lpCharTool->TexScroll = CraftBlinkColor[cnt][5];
			return TRUE;
		}
	}


	return NULL;

}


int sinSetCharItem(DWORD CODE, DWORD Posi, BOOL SetFlag)
{
	DWORD	dwCode;
	sITEMINFO *lpItemInfo;
	DWORD	dwMotionCode;
	int		FrameCounter;
	int		cnt;


	switch(Posi)
	{
	case INVENTORY_POS_LHAND:
		if(SetFlag)
		{
			lpCurPlayer->SetTool(CODE, hvPOSI_LHAND);

			lpItemInfo = &cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sItemInfo;
			if(!lpItemInfo->ItemName[0])
				lpItemInfo = &cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo;


			lpCurPlayer->HvLeftHand.ColorBlink = lpItemInfo->EffectBlink[0];
			memcpy(lpCurPlayer->HvLeftHand.sColors, lpItemInfo->EffectColor, sizeof(short) * 4);
			lpCurPlayer->HvLeftHand.DispEffect = lpItemInfo->DispEffect;
			lpCurPlayer->HvLeftHand.BlinkScale = lpItemInfo->ScaleBlink[0];
			lpCurPlayer->HvLeftHand.EffectKind = 0;



			if(lpItemInfo->ItemKindCode == ITEM_KIND_AGING)
			{
				cnt = lpItemInfo->ItemAgingNum[0];
				if(cnt >= 4 && cnt <= CONST_AGINGBCOLOR_MAX)
				{
					cnt -= 4;
					lpCurPlayer->HvLeftHand.ColorBlink = 9;
					lpCurPlayer->HvLeftHand.sColors[SMC_R] = AgingBlinkColor[cnt][0];
					lpCurPlayer->HvLeftHand.sColors[SMC_G] = AgingBlinkColor[cnt][1];
					lpCurPlayer->HvLeftHand.sColors[SMC_B] = AgingBlinkColor[cnt][2];
					lpCurPlayer->HvLeftHand.sColors[SMC_A] = AgingBlinkColor[cnt][3];
				}
			}

			if(lpItemInfo->ItemKindCode == ITEM_KIND_CRAFT)
			{
				cnt = lpItemInfo->ItemAgingNum[0];
				if(cnt >= 6 && cnt <= 10)
				{
					cnt -= 5;
				}
				else
				{
					if(cnt == 0) cnt = 0;
					else cnt = -1;
				}
				if(cnt >= 0)
				{
					lpCurPlayer->HvLeftHand.ColorBlink = 9;
					lpCurPlayer->HvLeftHand.sColors[SMC_R] = CraftBlinkColor[cnt][0];
					lpCurPlayer->HvLeftHand.sColors[SMC_G] = CraftBlinkColor[cnt][1];
					lpCurPlayer->HvLeftHand.sColors[SMC_B] = CraftBlinkColor[cnt][2];
					lpCurPlayer->HvLeftHand.sColors[SMC_A] = CraftBlinkColor[cnt][3];
				}
			}


			GetItemKindFromBliankColor(&lpCurPlayer->HvLeftHand);


			if(lpCurPlayer->HvLeftHand.DispEffect) AssaParticle_ClassUpWeapon(lpCurPlayer);

		}
		else
			lpCurPlayer->SetTool(0, hvPOSI_LHAND);
		break;

	case INVENTORY_POS_RHAND:
		if(SetFlag)
		{
			lpCurPlayer->SetTool(CODE, hvPOSI_RHAND);

			lpItemInfo = &cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo;

			lpCurPlayer->HvRightHand.ColorBlink = lpItemInfo->EffectBlink[0];
			memcpy(lpCurPlayer->HvRightHand.sColors, lpItemInfo->EffectColor, sizeof(short) * 4);
			lpCurPlayer->HvRightHand.DispEffect = lpItemInfo->DispEffect;
			lpCurPlayer->HvRightHand.BlinkScale = lpItemInfo->ScaleBlink[0];
			lpCurPlayer->HvRightHand.EffectKind = 0;



			if(lpItemInfo->ItemKindCode == ITEM_KIND_AGING)
			{
				cnt = lpItemInfo->ItemAgingNum[0];
				if(cnt >= 4 && cnt <= CONST_AGINGBCOLOR_MAX)
				{
					cnt -= 4;
					lpCurPlayer->HvRightHand.ColorBlink = 9;
					lpCurPlayer->HvRightHand.sColors[SMC_R] = AgingBlinkColor[cnt][0];
					lpCurPlayer->HvRightHand.sColors[SMC_G] = AgingBlinkColor[cnt][1];
					lpCurPlayer->HvRightHand.sColors[SMC_B] = AgingBlinkColor[cnt][2];
					lpCurPlayer->HvRightHand.sColors[SMC_A] = AgingBlinkColor[cnt][3];
				}
			}

			if(lpItemInfo->ItemKindCode == ITEM_KIND_CRAFT)
			{

				cnt = lpItemInfo->ItemAgingNum[0];
				if(cnt >= 6 && cnt <= 10)
				{
					cnt -= 5;
				}
				else
				{
					if(cnt == 0) cnt = 0;
					else cnt = -1;
				}
				if(cnt >= 0)
				{
					lpCurPlayer->HvRightHand.ColorBlink = 9;
					lpCurPlayer->HvRightHand.sColors[SMC_R] = CraftBlinkColor[cnt][0];
					lpCurPlayer->HvRightHand.sColors[SMC_G] = CraftBlinkColor[cnt][1];
					lpCurPlayer->HvRightHand.sColors[SMC_B] = CraftBlinkColor[cnt][2];
					lpCurPlayer->HvRightHand.sColors[SMC_A] = CraftBlinkColor[cnt][3];
				}
			}


			GetItemKindFromBliankColor(&lpCurPlayer->HvRightHand);


			if(lpCurPlayer->HvRightHand.DispEffect) AssaParticle_ClassUpWeapon(lpCurPlayer);

		}
		else
			lpCurPlayer->SetTool(0, hvPOSI_RHAND);
		break;

	case INVENTORY_POS_ARMOR:
		dwMotionCode = lpCurPlayer->MotionInfo->State;
		FrameCounter = lpCurPlayer->FrameCounter;


		if(CODE != NULL)
		{

			if(SetFlag)
			{
				dwCode = CODE;


				if((dwCode & sinITEM_MASK3) >> 8 > 29) 
					SetPlayerArmor(((dwCode&sinITEM_MASK3) >> 8) - 17);
				else
					SetPlayerArmor((dwCode & sinITEM_MASK3) >> 8);

				lpCurPlayer->wStickItems[smPLAYBUFF_ITEM_BODY] = GetSinItemNumFromCode(dwCode);
			}
			else
			{
				SetPlayerArmor(0);
				lpCurPlayer->wStickItems[smPLAYBUFF_ITEM_BODY] = -2;
			}
			if(dwMotionCode == CHRMOTION_STATE_DEAD)
			{

				lpCurPlayer->SetMotionFromCode(dwMotionCode);
				lpCurPlayer->frame = (lpCurPlayer->MotionInfo->EndFrame - 1) * 160;
				lpCurPlayer->FrameCounter = FrameCounter;
			}
		}
		else
		{
			SetPlayerArmor(-1);
			lpCurPlayer->wStickItems[smPLAYBUFF_ITEM_BODY] = -2;
		}
		break;

	case INVENTORY_POS_COSTUME:

		if(cInvenTory.CostumeFlag)
		{
			dwMotionCode = lpCurPlayer->MotionInfo->State;
			FrameCounter = lpCurPlayer->FrameCounter;

			if(CODE != NULL)
			{
				if(SetFlag)
				{
					dwCode = CODE;
					if((dwCode&sinITEM_MASK3) >> 8 > 25)
						SetPlayerArmor((((dwCode&sinITEM_MASK3) >> 8) - 17) + 59);
					else
						SetPlayerArmor(((dwCode&sinITEM_MASK3) >> 8) + 59);

					lpCurPlayer->wStickItems[smPLAYBUFF_ITEM_BODY] = GetSinItemNumFromCode(dwCode);
				}
				else
				{
					SetPlayerArmor(0);
					lpCurPlayer->wStickItems[smPLAYBUFF_ITEM_BODY] = -2;
				}

				if(dwMotionCode == CHRMOTION_STATE_DEAD)
				{
					lpCurPlayer->SetMotionFromCode(dwMotionCode);
					lpCurPlayer->frame = (lpCurPlayer->MotionInfo->EndFrame - 1) * 160;
					lpCurPlayer->FrameCounter = FrameCounter;
				}
			}
			else
			{
				SetPlayerArmor(-1);
				lpCurPlayer->wStickItems[smPLAYBUFF_ITEM_BODY] = -2;
			}
		}
		break;
	}
	return TRUE;
}


int sinThrowItemToFeild(sITEM *pItem)
{

	sITEM	sThrowItem;
	int		ThrowItemBackup = 0;

	/*
	if((pItem->sItemInfo.CODE & sinITEM_MASK2) == sinBI1 || (pItem->sItemInfo.CODE & sinITEM_MASK2) == sinBI2)
	{
		if(pItem->sItemInfo.PotionCount == 0)
			return FALSE;
	}
	*/


	if(cWareHouse.OpenFlag)
	{
		if(!cWareHouse.CloseWareHouse())
		{
			pItem->Flag = 0;
			return FALSE;
		}

	}

	if(lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->FieldCode == QUEST_ARENA_FIELD)
	{
		if(pItem->sItemInfo.PotionCount != 100)
			return FALSE;

	}

	if(pItem->sItemInfo.CODE != (sinGG1 | sin01) && !pItem->Flag) return FALSE;

	if(pItem->sItemInfo.PotionCount == 100)
	{


		int BlessCristalCode = -1;
		int BlessSolderTotal;

		switch(pItem->sItemInfo.CODE)
		{
		case sinGP1 | sin14:
			BlessCristalCode = 0;
			break;
		case sinGP1 | sin15:
			BlessCristalCode = 1;
			break;
		case sinGP1 | sin16:
			BlessCristalCode = 2;
			break;
		}
		if(BlessCristalCode >= 0)
		{
			if(!rsBlessCastle.CastleMode ||
				(lpCurPlayer->OnStageField >= 0 && sField[lpCurPlayer->OnStageField].FieldCode != rsCASTLE_FIELD) &&
				!lpCurPlayer->Clan_CastleMasterFlag)
			{

				cMessageBox.ShowMessageEvent(mgBlessCrystal_03);
				return FALSE;
			}

			BlessSolderTotal = rsBlessCastle.bCrystalSolderCount[0] +
				rsBlessCastle.bCrystalSolderCount[1] +
				rsBlessCastle.bCrystalSolderCount[2] +
				rsBlessCastle.bCrystalSolderCount[3];

			if(rsBlessCastle.bCrystalSolderCount[BlessCristalCode] >= srCASLTE_SOLDER_KIND_MAX ||
				BlessSolderTotal >= srCASLTE_SOLDER_CLAN_MAX)
			{

				cMessageBox.ShowMessageEvent(mgBlessCrystal_01);
				return FALSE;
			}
		}
	}




	if(!CheckItemForm(&pItem->sItemInfo))
	{
		SendSetHackUser(80);
		return TRUE;
	}





	if(cShop.OpenFlag || SkillMasterFlag || cCraftItem.OpenFlag || cAging.OpenFlag || SmeltingItem.OpenFlag || ManufactureItem.m_OpenFlag || cMixtureReset.OpenFlag)
	{
		if(pItem->sItemInfo.CODE == (sinGG1 | sin01)) return FALSE;
	}

	if((pItem->sItemInfo.CODE&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
	{

		ThrowItemBackup = 1;
		memcpy(&sThrowItem, pItem, sizeof(sITEM));
		ReformItem(&pItem->sItemInfo);
	}

	if(ThrowPutItem(pItem, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ) == TRUE)
	{
		SubInvenItemCode(&pItem->sItemInfo);
		pItem->Flag = 0;



		return TRUE;
	}

	if(ThrowItemBackup)
		memcpy(pItem, &sThrowItem, sizeof(sITEM));

	return FALSE;
}


int sinActionPotion()
{
	if(sinGetLife() > 0 && lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_EAT
		&& lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_DEAD)
	{
		if(lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_ATTACK || lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_SKILL)
			lpCurPlayer->dwNextMotionCode = CHRMOTION_STATE_EAT;
		else
			lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_EAT);
		return TRUE;
	}

	return FALSE;
}


int	ActionEtherCore(sITEM	*lpItem)
{

	DWORD	dwCode = lpItem->sItemInfo.CODE;

	if(lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_ROOM)
	{

		return TRUE;
	}
	if(lpCurPlayer->smCharInfo.wPlayerKilling[0])
	{

		return TRUE;
	}

	if(sinGetLife() > 0 && lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_DEAD)
	{

		if(lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_ATTACK || lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_SKILL)
			lpCurPlayer->dwNextMotionCode = CHRMOTION_STATE_EAT;
		else
		{
			lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_EAT);
			StartEffect(lpCurPlayer->pX, lpCurPlayer->pY + 48 * fONE, lpCurPlayer->pZ, EFFECT_RETURN1);
			SkillPlaySound(SKILL_SOUND_LEARN, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
		}

		UseEtherCoreCode = dwCode;



		if((lpItem->sItemInfo.CODE&sinITEM_MASK2) == sinEC1)
		{

			SendUseItemCodeToServer(&lpItem->sItemInfo);
		}

		return TRUE;
	}

	return FALSE;
}



int GetDeathPenalty()
{
	sITEMINFO* lpItemInfo;

	int	Penalty = 0;

	if (sInven[4].ItemIndex)
	{
		lpItemInfo = &cInvenTory.InvenItem[sInven[4].ItemIndex - 1].sItemInfo;
		if (lpItemInfo->CODE == (sinOR2 | sin01) && lpItemInfo->ItemKindCode == ITEM_KIND_AGING)
		{
			if (lpItemInfo->ItemAgingNum[0] >= Penalty) Penalty = lpItemInfo->ItemAgingNum[0];
		}
	}

	if (sInven[5].ItemIndex)
	{
		lpItemInfo = &cInvenTory.InvenItem[sInven[5].ItemIndex - 1].sItemInfo;
		if (lpItemInfo->CODE == (sinOR2 | sin01) && lpItemInfo->ItemKindCode == ITEM_KIND_AGING)
		{
			if (lpItemInfo->ItemAgingNum[0] >= Penalty) Penalty = lpItemInfo->ItemAgingNum[0];
		}
	}


	if (lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_CASTLE &&
		StageField[lpCurPlayer->OnStageField]->FieldCode == rsCASTLE_FIELD)
	{
		return 0;
	}

	//Ressu
	lpItemInfo = FindItemFromCode(sinBI1 | sin04);
	if (lpItemInfo) 
	{
		SendUseItemCodeToServer(lpItemInfo);
		cInvenTory.DeleteInvenItemToServer(lpItemInfo->CODE, lpItemInfo->ItemHeader.Head, lpItemInfo->ItemHeader.dwChkSum);
		PlayUsed_Resurrection++;
		return 0;
	}


#ifndef _DEATH_PANALTY
	if (sBiInfo && (sBiInfo->EventPlay[0] & BIMASK_VIP_USER) != 0) return 100;
#endif


#ifdef _LANGUAGE_THAI_RING
	if (Penalty >= 8) return 1000;
	if (Penalty >= 7) return 700;
	if (Penalty >= 6) return 600;
	if (Penalty >= 5) return 500;
	if (Penalty >= 4) return 400;
	if (Penalty >= 3) return 300;
	if (Penalty >= 2) return 200;
	if (Penalty >= 1) return 100;
#endif
	if (Penalty >= 8) return 100;
	if (Penalty >= 6) return 50;

	if ((sinQuest_levelLog & QUESTBIT_LEVEL_85) != 0 && lpCurPlayer->smCharInfo.Level >= 85)
	{

#ifdef _DEATH_PANALTY 
		return 200;
#endif
		return 50;
	}
#ifdef _DEATH_PANALTY 
	return 110;
#endif


	return 33;
}


INT64 ExpLevelTable[] = {
#include "LevelTable.h"
	- 1 };




INT64 LevelTableSum = 23766931515015039;

INT64 CodeXorCharInfo_Exp()
{
	lpCurPlayer->smCharInfo.Exp ^= CodeXorExp;
	lpCurPlayer->smCharInfo.Exp_High ^= CodeXorExp_High;

	INT64 exp1 = lpCurPlayer->smCharInfo.Exp;
	INT64 exp2 = lpCurPlayer->smCharInfo.Exp_High;

	return (exp2 << 32) | (exp1 & 0xFFFFFFFF);
}



INT64 CheckLevelTable()
{
	INT64 cnt = 0;
	INT64 ChkSum = 0;

	while(1)
	{
		if(ExpLevelTable[cnt] == -1) break;
		ChkSum += ExpLevelTable[cnt] * (cnt + 1);
		cnt++;
	}

	return ChkSum;
}


int	CheckLevelExp(int Level, INT64 Exp)
{
	INT64 xp;
	INT64 np;

	if(Level > 0 && Level <= CHAR_LEVEL_MAX)
	{
		xp = ExpLevelTable[Level - 1];
		np = ExpLevelTable[Level];

		if(Exp >= xp && Exp <= np)
		{
			return TRUE;
		}

	}
	return FALSE;
}


int	GetLevelFromExp(INT64 Exp)
{
	for(int cnt = 0; cnt < CHAR_LEVEL_MAX; cnt++)
	{
		if(Exp >= ExpLevelTable[cnt] && Exp < ExpLevelTable[cnt + 1])
		{
			return cnt + 1;
		}
	}

	return NULL;
}


INT64 GetExp64(smCHAR_INFO *smCharInfo)
{
	INT64 exp1, exp2;
	exp1 = (INT64)smCharInfo->Exp;

#ifdef _MODE_EXP64
	exp2 = (INT64)smCharInfo->Exp_High;
#else
	exp2 = 0;
#endif

	return (exp2 << 32) | (exp1 & 0xFFFFFFFF);
}


INT64 GetXorExp64(smCHAR_INFO *smCharInfo)
{
	INT64 exp1, exp2;

	exp1 = (INT64)(smCharInfo->Exp^CodeXorExp);
	exp2 = (INT64)(smCharInfo->Exp_High^CodeXorExp_High);

	return (exp2 << 32) | (exp1 & 0xFFFFFFFF);
}



int	SetExp64(smCHAR_INFO *smCharInfo, INT64 Exp64)
{
#ifdef _MODE_EXP64
	smCharInfo->Exp_High = (int)(Exp64 >> 32);
#endif
	smCharInfo->Exp = (int)(Exp64 & 0xFFFFFFFF);

	return smCharInfo->Exp;
}

bool bcanadd = false;

void setexp()
{
	bcanadd = true;
}

extern int NumLineComa64(INT64 Num, char* pBuff);

int AddExp(INT64 Exp)
{
	if (!bcanadd)
		return FALSE;


	INT64 exp64 = CodeXorCharInfo_Exp();
	//int mlevel = CHAR_LEVEL_MAX - 2;

	bool flag = false;
	// DEFINE O LEVEL MÁXIMO PARA GANHAR EXP NO CASO, 110.
	int mlevel = 130 - 1;

	if (exp64 < ExpLevelTable[mlevel])
	{
		exp64 += Exp;
		flag = true;
	}

	if (flag)
	{
		char szBuf[64] = { 0 };
		char szTemp[32] = { 0 };

		NumLineComa64(Exp, szTemp);

		wsprintf(szBuf, "> Ganhou %s de experiência!", szTemp);
		AddChatBuff(szBuf, 9);
	}

	SetExp64(&lpCurPlayer->smCharInfo, exp64);
	CodeXorCharInfo_Exp();
	ReformCharForm();

	int Level = lpCurPlayer->smCharInfo.Level;
	INT64 iexp = ExpLevelTable[Level];

	/*
	if(LevelTableSum != CheckLevelTable())
	{
		bcanadd = false;
		Log::getInstance()->output(LOG_DEBUG, "SetDisconnectFlag: 33");
		DisconnectFlag = GetCurrentTime();
		return FALSE;
	}
	*/

	while (iexp >= 0 && exp64 >= iexp && lpCurPlayer->smCharInfo.Level < CHAR_LEVEL_MAX)
	{
		AddChatBuff("Upou!");

		lpCurPlayer->smCharInfo.Level++;
		lpCurPlayer->smCharInfo.Next_Exp = (int)ExpLevelTable[Level + 1];
		StartEffect(lpCurPlayer->pX, lpCurPlayer->pY + 32 * fONE, lpCurPlayer->pZ, EFFECT_LEVELUP1);
		esPlaySound(7, 400);
		ReformCharForm();


		if (lpCurPlayer->smCharInfo.ChangeJob > 2) {
			//NAO FAZ NADA 	
		}
		else {
			if (lpCurPlayer->smCharInfo.Level > 59)
			{
				lpCurPlayer->smCharInfo.ChangeJob = 3;
			}
			else if (lpCurPlayer->smCharInfo.Level > 39) {
				lpCurPlayer->smCharInfo.ChangeJob = 2;
			}
			else if (lpCurPlayer->smCharInfo.Level > 19) {
				lpCurPlayer->smCharInfo.ChangeJob = 1;
			}
		}

		SendPlayUpdateInfo();
		SaveGameData();

		Level = lpCurPlayer->smCharInfo.Level;
		iexp = ExpLevelTable[Level];

		extern cCHARSTATUS cCharStatus;
		cCharStatus.CheckLevel();
	}

	bcanadd = false;

	return TRUE;
}


int CheckFieldContExp()
{
	int Level;
	INT64 LowExp;
	INT64 HighExp;
	INT64 exp;
	INT64 exp64;

	Level = lpCurPlayer->smCharInfo.Level;
	if(Level >= 11)
	{
		LowExp = ExpLevelTable[Level - 1];
		HighExp = ExpLevelTable[Level];
		exp = (HighExp - LowExp) / 100;

		exp64 = GetXorExp64(&lpCurPlayer->smCharInfo);

		exp = exp64 - exp;
		if(exp < LowExp)
		{
			return FALSE;
		}
	}
	else
	{
		if(lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State != FIELD_STATE_FOREST)
		{

			return FALSE;
		}
	}

	return TRUE;
}



INT64 GetNextExp(int Level)
{
	return ExpLevelTable[Level];
}


int DeadPlayerExp(smCHAR *lpChar)
{
	int Level;
	INT64 LowExp;
	INT64 HighExp;
	INT64 exp;
	INT64 ep;
	INT64 exp64;
	int Money;
	int ExpLower = 0;
	int	Penalty = GetDeathPenalty();

	Level = lpChar->smCharInfo.Level;
	if(Level >= 11)
	{
		LowExp = ExpLevelTable[Level - 1];
		HighExp = ExpLevelTable[Level];
		if(Penalty)
			exp = (HighExp - LowExp) / Penalty;
		else
			exp = 0;

		exp64 = CodeXorCharInfo_Exp();
		if(exp64 >= LowExp)
		{
			ep = exp64;
			exp64 -= exp;
			if(exp64 < LowExp)
			{
				exp64 = LowExp;
				ExpLower = TRUE;
			}
			SetExp64(&lpCurPlayer->smCharInfo, exp64);
			ep = ep - exp64;
			SetTotalSubExp((int)ep);
		}
		CodeXorCharInfo_Exp();


		if(Penalty)
			Money = lpChar->smCharInfo.Money / Penalty;
		else
			Money = 0;

		lpChar->smCharInfo.Money -= Money;
		if(lpChar->smCharInfo.Money < 0)
		{
			Money = -Money;
			lpChar->smCharInfo.Money = 0;
		}
		SetTotalSubMoney(Money);


		ReformCharForm();
		ResetInvenMoney();
	}

	return ExpLower;
}


int ContGameExp(smCHAR *lpChar)
{
	int Level;
	INT64 LowExp;
	INT64 HighExp;
	INT64 exp;
	INT64 ep;
	INT64 exp64;
	int Money;

	Level = lpChar->smCharInfo.Level;
	if(Level >= 11)
	{
		LowExp = ExpLevelTable[Level - 1];
		HighExp = ExpLevelTable[Level];
		exp = (HighExp - LowExp) / 100;


		exp64 = CodeXorCharInfo_Exp();

		if(exp64 > LowExp)
		{
			ep = exp64;
			exp64 -= exp;
			if(exp64 < LowExp)
				exp64 = LowExp;

			SetExp64(&lpCurPlayer->smCharInfo, exp64);

			ep = ep - exp64;
			SetTotalSubExp((int)ep);
		}

		CodeXorCharInfo_Exp();


		Money = lpChar->smCharInfo.Money / 100;
		lpChar->smCharInfo.Money -= Money;
		if(lpChar->smCharInfo.Money < 0)
		{
			Money = -Money;
			lpChar->smCharInfo.Money = 0;
		}

		SetTotalSubMoney(Money);


		ReformCharForm();
		ResetInvenMoney();
	}

	return TRUE;
}




int GetPlayDefence(smCHAR_INFO *lpAttackCharInfo, smCHAR_INFO *lpDefenceCharInfo)
{
	int defence;

	float ar, def, dLv, aLv;
	int weight;


	ar = (float)lpAttackCharInfo->Attack_Rating;
	aLv = (float)lpAttackCharInfo->Level;
	def = (float)lpDefenceCharInfo->Defence;
	dLv = (float)lpDefenceCharInfo->Level;
	weight = lpDefenceCharInfo->Weight[0];
	defence = (int)(((((ar / (ar + (def / 2))) - ((dLv - aLv) / 50))) * 100)) - (weight / 10000);

	if(defence > 95) defence = 95;

	return defence;
}


int RainMaterial[4][8];


int InitWeatherSystem()
{
	if(cSettings::GetInstance()->cTexture >= 2)
	{
		return FALSE;
	}

	RainMaterial[0][0] = CreateTextureMaterial("game\\sky\\rain\\ll.bmp", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ADDCOLOR);

	RainMaterial[1][0] = CreateTextureMaterial("game\\sky\\rain\\45rain01.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[1][1] = CreateTextureMaterial("game\\sky\\rain\\45rain02.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[1][2] = CreateTextureMaterial("game\\sky\\rain\\45rain03.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[1][3] = CreateTextureMaterial("game\\sky\\rain\\45rain04.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[1][4] = CreateTextureMaterial("game\\sky\\rain\\45rain05.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[1][5] = CreateTextureMaterial("game\\sky\\rain\\45rain06.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);

	RainMaterial[2][0] = CreateTextureMaterial("game\\sky\\rain\\80rain01.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[2][1] = CreateTextureMaterial("game\\sky\\rain\\80rain02.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[2][2] = CreateTextureMaterial("game\\sky\\rain\\80rain03.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[2][3] = CreateTextureMaterial("game\\sky\\rain\\80rain04.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[2][4] = CreateTextureMaterial("game\\sky\\rain\\80rain05.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[2][5] = CreateTextureMaterial("game\\sky\\rain\\80rain06.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);

	RainMaterial[3][0] = CreateTextureMaterial("game\\sky\\rain\\90rain01.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[3][1] = CreateTextureMaterial("game\\sky\\rain\\90rain02.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[3][2] = CreateTextureMaterial("game\\sky\\rain\\90rain03.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[3][3] = CreateTextureMaterial("game\\sky\\rain\\90rain04.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[3][4] = CreateTextureMaterial("game\\sky\\rain\\90rain05.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	RainMaterial[3][5] = CreateTextureMaterial("game\\sky\\rain\\90rain06.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);

	return TRUE;
}


extern int WeatherMode;

int DrawWeather(int ax)
{
	if(cSettings::GetInstance()->cTexture >= 2)
	{
		return FALSE;
	}

	smFACE2D face2d;

	int tm;
	float fx;
	int RainMode;

	if(ax < ANGLE_45 - 256) RainMode = 0;
	else
	{
		if(ax > ANGLE_45 + 256) RainMode = 3;
		else
		{
			if(ax > ANGLE_45) RainMode = 2;
			else RainMode = 1;
		}
	}

	if(WeatherMode == 2)
	{

		if(lpCurPlayer->OnStageField >= 0 &&
			(StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_DUNGEON ||
				StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_ROOM))
			return TRUE;






		smRender.Init();

		switch(RainMode)
		{
		case 0:
			tm = timeGetTime();
			tm = (tm >> 2) & 0x3FF;
			fx = ((float)tm) / 256;

			tm = timeGetTime();
			tm = (tm) & 0x3FF;
			fx = ((float)tm) / 256;

			face2d.TexRect.left = fx;
			face2d.TexRect.right = fx + 3;
			face2d.TexRect.top = fx;
			face2d.TexRect.bottom = fx + 0.5f;
			face2d.width = WinSizeX;
			face2d.height = WinSizeY;
			face2d.Transparency = 255;
			face2d.r = 255; face2d.g = 255; face2d.b = 255;
			face2d.x = 0;
			face2d.z = 0;
			face2d.y = 0;
			face2d.MatNum = RainMaterial[RainMode][0];
			smRender.AddFace2D_Direct(&face2d);

			break;

		case 1:
			tm = timeGetTime() >> 6;

			face2d.TexRect.left = 1;
			face2d.TexRect.right = 0;
			face2d.TexRect.top = 0;
			face2d.TexRect.bottom = 1;
			face2d.width = WinSizeX / 2;
			face2d.height = WinSizeY;
			face2d.Transparency = 160;
			face2d.r = 255; face2d.g = 255; face2d.b = 255;
			face2d.x = 0;
			face2d.z = 0;
			face2d.y = 0;
			face2d.MatNum = RainMaterial[RainMode][tm % 6];
			smRender.AddFace2D_Direct(&face2d);

			face2d.TexRect.left = 0;
			face2d.TexRect.right = 1;
			face2d.TexRect.top = 0;
			face2d.TexRect.bottom = 1;
			face2d.width = WinSizeX / 2;
			face2d.height = WinSizeY;
			face2d.Transparency = 160;
			face2d.r = 255; face2d.g = 255; face2d.b = 255;
			face2d.x = WinSizeX / 2;
			face2d.z = 0;
			face2d.y = 0;
			face2d.MatNum = RainMaterial[RainMode][(tm + 3) % 6];
			smRender.AddFace2D_Direct(&face2d);
			break;

		case 2:

			tm = timeGetTime() >> 6;

			face2d.TexRect.left = 1;
			face2d.TexRect.right = 0;
			face2d.TexRect.top = 0;
			face2d.TexRect.bottom = 1;
			face2d.width = WinSizeX / 2;
			face2d.height = WinSizeY;
			face2d.Transparency = 128;
			face2d.r = 255; face2d.g = 255; face2d.b = 255;
			face2d.x = 0;
			face2d.z = 0;
			face2d.y = 0;
			face2d.MatNum = RainMaterial[RainMode][tm % 6];
			smRender.AddFace2D_Direct(&face2d);

			face2d.TexRect.left = 0;
			face2d.TexRect.right = 1;
			face2d.TexRect.top = 0;
			face2d.TexRect.bottom = 1;
			face2d.width = WinSizeX / 2;
			face2d.height = WinSizeY;
			face2d.Transparency = 128;
			face2d.r = 255; face2d.g = 255; face2d.b = 255;
			face2d.x = WinSizeX / 2;
			face2d.z = 0;
			face2d.y = 0;
			face2d.MatNum = RainMaterial[RainMode][(tm + 3) % 6];
			smRender.AddFace2D_Direct(&face2d);
			break;

		case 3:
			tm = timeGetTime() >> 6;

			face2d.TexRect.left = 0;
			face2d.TexRect.right = 1;
			face2d.TexRect.top = 0;
			face2d.TexRect.bottom = 1;
			face2d.width = WinSizeX / 2;
			face2d.height = WinSizeY / 2;
			face2d.Transparency = 128;
			face2d.r = 255; face2d.g = 255; face2d.b = 255;
			face2d.x = 0;
			face2d.z = 0;
			face2d.y = 0;
			face2d.MatNum = RainMaterial[RainMode][tm % 6];
			smRender.AddFace2D_Direct(&face2d);

			face2d.TexRect.left = 1;
			face2d.TexRect.right = 0;
			face2d.TexRect.top = 0;
			face2d.TexRect.bottom = 1;
			face2d.width = WinSizeX / 2;
			face2d.height = WinSizeY / 2;
			face2d.Transparency = 128;
			face2d.r = 255; face2d.g = 255; face2d.b = 255;
			face2d.x = WinSizeX / 2;
			face2d.z = 0;
			face2d.y = 0;
			face2d.MatNum = RainMaterial[RainMode][(tm + 3) % 6];
			smRender.AddFace2D_Direct(&face2d);


			face2d.TexRect.left = 0;
			face2d.TexRect.right = 1;
			face2d.TexRect.top = 1;
			face2d.TexRect.bottom = 0;
			face2d.width = WinSizeX / 2;
			face2d.height = WinSizeY / 2;
			face2d.Transparency = 128;
			face2d.r = 255; face2d.g = 255; face2d.b = 255;
			face2d.x = 0;
			face2d.z = 0;
			face2d.y = WinSizeY >> 1;
			face2d.MatNum = RainMaterial[RainMode][(tm + 1) % 6];
			smRender.AddFace2D_Direct(&face2d);

			face2d.TexRect.left = 1;
			face2d.TexRect.right = 0;
			face2d.TexRect.top = 1;
			face2d.TexRect.bottom = 0;
			face2d.width = WinSizeX / 2;
			face2d.height = WinSizeY / 2;
			face2d.Transparency = 128;
			face2d.r = 255; face2d.g = 255; face2d.b = 255;
			face2d.x = WinSizeX / 2;
			face2d.z = 0;
			face2d.y = WinSizeY >> 1;
			face2d.MatNum = RainMaterial[RainMode][(tm + 4) % 6];
			smRender.AddFace2D_Direct(&face2d);

		}

		smRender.SetClipStates(0);
		smRender.ClipRendFace();
		smRender.RenderD3D();
	}

	return TRUE;
}


#define DYN_REMOVER_MAX		64
#define DYN_REMOVER_MASK	(DYN_REMOVER_MAX-1)

smDPAT *DynRemoveList[DYN_REMOVER_MAX];
int DynRemoveCnt = 0;
int DynRemovePush = 0;

HANDLE	hRemoverThread = 0;

DWORD WINAPI RemoveDynaPatternThreadProc(void *pInfo)
{
	HANDLE	hThread;

	int Counter = 0;


	int RemoveCnt;

	hThread = GetCurrentThread();

	while(1)
	{
		if(quit) break;

		if((DynRemovePush - DynRemoveCnt) > 32)
		{

			EnterCriticalSection(&cLoadSection);
			EnterCriticalSection(&cDrawSection);

			while(1)
			{
				RemoveCnt = DynRemoveCnt&DYN_REMOVER_MASK;
				smDPAT_Delete(DynRemoveList[RemoveCnt]);
				DynRemoveCnt++;
				if(DynRemovePush <= DynRemoveCnt) break;
			}


			LeaveCriticalSection(&cDrawSection);
			LeaveCriticalSection(&cLoadSection);
		}
		else
			SuspendThread(hThread);

		Counter++;
	}

	ExitThread(TRUE);
	return TRUE;
}

int RemoveDynPatSub()
{
	int RemoveCnt;

	while(1)
	{
		if((DynRemovePush - DynRemoveCnt) > 32)
		{
			while(1)
			{
				RemoveCnt = DynRemoveCnt&DYN_REMOVER_MASK;
				smDPAT_Delete(DynRemoveList[RemoveCnt]);
				DynRemoveCnt++;
				if(DynRemovePush <= DynRemoveCnt) break;
			}
		}
		else
			break;
	}

	return TRUE;
}



int AddRemoveDynPattern(smDPAT *lpDinaPattern)
{



	if(ServerMode)
	{
		if(lpDinaPattern->UseCount > 1)
			smDPAT_Delete(lpDinaPattern);

		return TRUE;
	}


	DynRemoveList[DynRemovePush&DYN_REMOVER_MASK] = lpDinaPattern;
	DynRemovePush++;
	RemoveDynPatSub();

	return DynRemovePush;
}





struct	sCOMPACT_MAP
{
	smTEXTUREHANDLE	*hTexHandle;
	smTEXTUREHANDLE	*hTexTitleHandle;
	RECT	StageRect;
	sFIELD	*lpField;
	int		rx, ry;

};

sCOMPACT_MAP sCompactMap[4];

int MatArrow;
int MatMapBox;
int	MatPartyPos;
int	MatNpcPos;
int	MatBossTime;


int InitFieldMap()
{
	ZeroMemory(sCompactMap, sizeof(sCOMPACT_MAP) * 4);
	MatArrow = CreateTextureMaterial("Image\\ARROW.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatBossTime = CreateTextureMaterial("game\\images\\Battle\\nextboss.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatMapBox = CreateTextureMaterial("Image\\MapBox.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatPartyPos = CreateTextureMaterial("Image\\party.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatNpcPos = CreateTextureMaterial("Image\\npc.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	return TRUE;
}


int LoadFieldMap(int PosNum, sFIELD *lpField, smSTAGE3D *lpStage)
{
	int ReadTexFlag = 0;

	if(!lpField || !lpStage || sCompactMap[PosNum].lpField == lpField)
		return TRUE;

	sCompactMap[PosNum].lpField = lpField;

	memcpy(&sCompactMap[PosNum].StageRect, &lpStage->StageMapRect, sizeof(RECT));

	if(sCompactMap[PosNum].hTexHandle)
	{
		smTexture.Delete(sCompactMap[PosNum].hTexHandle);
		sCompactMap[PosNum].hTexHandle = 0;
	}
	if(sCompactMap[PosNum].hTexTitleHandle)
	{
		smTexture.Delete(sCompactMap[PosNum].hTexTitleHandle);
		sCompactMap[PosNum].hTexTitleHandle = 0;
	}


	if(lpField->szNameMap[0])
	{
		sCompactMap[PosNum].hTexHandle = smTexture.Add(lpField->szNameMap, 0);
		sCompactMap[PosNum].hTexHandle->TexSwapMode = FALSE;

		sCompactMap[PosNum].rx = (lpStage->StageMapRect.right - lpStage->StageMapRect.left) >> FLOATNS;
		sCompactMap[PosNum].ry = (lpStage->StageMapRect.bottom - lpStage->StageMapRect.top) >> FLOATNS;

		ReadTexFlag = TRUE;
	}
	else
	{
		sCompactMap[PosNum].hTexHandle = 0;
		return FALSE;
	}

	if(lpField->szNameTitle[0])
	{
		sCompactMap[PosNum].hTexTitleHandle = smTexture.Add(lpField->szNameTitle, 0);
		sCompactMap[PosNum].hTexTitleHandle->TexSwapMode = FALSE;

		ReadTexFlag = TRUE;
	}
	else
	{
		sCompactMap[PosNum].hTexTitleHandle = 0;
		return FALSE;
	}

	if(ReadTexFlag)	ReadTextures();

	return TRUE;
}

int psDrawTexImage(smTEXTUREHANDLE *hTexHandle, float x, float y, float w, float h,
	float fx, float fy, float fw, float fh, int Transp, int specular);

int psDrawTexImage_Point(smTEXTUREHANDLE *hTexHandle, float x, float y, float w, float h,
	float fx, float fy, float fw, float fh, int Transp, int specular);

int psDrawTexImage2(smTEXTUREHANDLE *hTexHandle, float *x, float *y,
	float fx, float fy, float fw, float fh, int Transp, int specular);

int DrawMapArrow(int x, int y, int Angle);

int DrawFieldMap(sCOMPACT_MAP *lpCompactMap, int px, int py, int size);

int FieldMapDrawMode = 2;

int FieldMapDrawSize[3] = { 8 , 16 , 24 };
int FieldMapViewSize1 = 18 * 64 * fONE;
int FieldMapViewSize2 = 8 * 64 * fONE;


int MainFieldMap()
{
	if(FieldMapViewSize1 > FieldMapViewSize2)
	{
		FieldMapViewSize2 += 2048;
		if(FieldMapViewSize1 < FieldMapViewSize2)
			FieldMapViewSize2 = FieldMapViewSize1;
	}

	if(FieldMapViewSize1 < FieldMapViewSize2)
	{
		FieldMapViewSize2 -= 2048;
		if(FieldMapViewSize1 > FieldMapViewSize2)
			FieldMapViewSize2 = FieldMapViewSize1;
	}


	return TRUE;
}

extern int MatEachBox;

int	DrawMapPartyPlayer(int px, int py);

int	DrawMapNPC(int px, int py);


int	GetFieldMapCursor()
{
	int px = 656 + (WinSizeX - 800);
	int py = 426 + (WinSizeY - 600);

	if(WinSizeX <= 800 && cSkill.OpenFlag) return FALSE;

	if(pCursorPos.x > px && pCursorPos.x<px + 128 && pCursorPos.y>py && pCursorPos.y < py + 128 && lpCurPlayer->dwTradeMsgCode == 0)
	{

		if(lpCurPlayer->OnStageField >= 0 &&
			(StageField[lpCurPlayer->OnStageField]->FieldCode == rsSOD_FIELD || StageField[lpCurPlayer->OnStageField]->FieldCode == QUEST_ARENA_FIELD))
		{

			return FALSE;
		}

		return TRUE;
	}

	return FALSE;
}


int DrawFieldMap()
{

	SYSTEMTIME systemTime;
	GetLocalTime(&systemTime);
	extern int szBossTime;
	char szBuff[32] = { 0 };


	int px = 656 + (WinSizeX - 800);
	int py = 426 + (WinSizeY - 600);
	int sz = 0;
	int flCode = 0;
	int	dSpe = 0;

	if(lpCurPlayer->dwTradeMsgCode)
		return FALSE;


	if (MatBossTime >= 0)
	{
		wsprintf(szBuff, "Boss Time: xx:%d", szBossTime);
		dsDrawTexImage(MatBossTime, px - 5, py - 40, 130, 23, 255, dSpe);
		SetFontTextColor(RGB(255, 255, 255));
		dsTextLineOut(px + 23, py - 36, szBuff, lstrlen(szBuff));
	}


	if(lpCurPlayer->OnStageField >= 0 &&
		(StageField[lpCurPlayer->OnStageField]->FieldCode == rsSOD_FIELD ||
			StageField[lpCurPlayer->OnStageField]->FieldCode == QUEST_ARENA_FIELD ||
			StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_ACTION) ||


		StageField[lpCurPlayer->OnStageField]->FieldCode == 36)
	{
		return FALSE;
	}


	if(lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_DUNGEON)
	{
		FieldMapDrawMode = 1;
	}
	else
	{

		FieldMapDrawMode = 2;
	}



	
	FieldMapViewSize1 = FieldMapDrawSize[FieldMapDrawMode] * 64 * fONE;
	sz = FieldMapViewSize2;

	dsDrawColorBox(D3DCOLOR_RGBA(0, 0, 0, 128), px, py, 128, 128);


	DrawFieldMap(&sCompactMap[1], px + 1, py + 1, sz);

	DrawFieldMap(&sCompactMap[0], px + 1, py + 1, sz);


	DrawMapNPC(px + 64, py + 64);


	//if(InterfaceParty.PartyMemberCount)
	if (cParty.MemberCount)
		DrawMapPartyPlayer(px + 64, py + 64);



	DrawMapArrow(px + 64, py + 64, lpCurPlayer->Angle.y);


	if(GetFieldMapCursor() == TRUE)
		dSpe = 96;
	else
		dSpe = 0;


	if(MatMapBox >= 0)
	{
		dsDrawTexImage(MatMapBox, px, py, 128, 128, 255, dSpe);
	}


	flCode = 0;
	if(lpCurPlayer->OnStageField >= 0)
	{
		if(StageField[lpCurPlayer->OnStageField] == sCompactMap[0].lpField) flCode = 0;
		if(StageField[lpCurPlayer->OnStageField] == sCompactMap[1].lpField) flCode = 1;
	}

	if(sCompactMap[flCode].hTexTitleHandle)
	{

		psDrawTexImage_Point(sCompactMap[flCode].hTexTitleHandle, (float)px, (float)py - 16, 128, 16, 0, 0, 1.0f, 1.0f, 255, dSpe >> 2);
	}

	

	return TRUE;
}



int	DrawMapPartyPlayer(int px, int py)
{
	int cnt;
	int	x, y;
	int	size;
	float sz;
	float sx, sy;
	float fx, fy;
	int dist;

	size = FieldMapViewSize2;
	sz = (float)(FieldMapViewSize2 / 64);
	fx = (float)px;
	fy = (float)py;

	for (cnt = 0; cnt < cParty.MemberCount; cnt++)
		//for (cnt = 0; cnt < cPARTY::GetInstance()->MemberCount; cnt++)
	{
		if (cParty.Members[cnt], lpCurPlayer->dwObjectSerial)
		{
			x = cParty.Members[cnt].x - lpCurPlayer->pX;
			y = cParty.Members[cnt].z - lpCurPlayer->pZ;
			if (abs(x) < size && abs(y) < size)
			{
				sx = fx + (((float)x) / sz);
				sy = fy - (((float)y) / sz);

				x >>= FLOATNS;
				y >>= FLOATNS;
				dist = x * x + y * y;
				if (dist < PARTY_GETTING_DIST2)
					dsDrawTexImageFloat(MatPartyPos, sx - 3, sy - 3, 8, 8, 255, 0);
				else
					dsDrawTexImageFloat(MatPartyPos, sx - 3, sy - 3, 8, 8, D3DCOLOR_RGBA(255, 0, 0, 255), 0);

			}
		}
	}

	return TRUE;
}



int	DrawMapNPC(int px, int py)
{
	int cnt;
	int	x, y;
	int	size;
	float sz;
	float sx, sy;
	float fx, fy;
	int TransNum;

	size = FieldMapViewSize2;
	sz = (float)(FieldMapViewSize2 / 64);
	fx = (float)px;
	fy = (float)py;

	TransNum = 127;


	for(cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if(chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].smCharInfo.State == smCHAR_STATE_NPC)
		{
			x = chrOtherPlayer[cnt].pX - lpCurPlayer->pX;
			y = chrOtherPlayer[cnt].pZ - lpCurPlayer->pZ;
			if(abs(x) < size && abs(y) < size)
			{

				sx = fx + (((float)x) / sz);
				sy = fy - (((float)y) / sz);
				dsDrawTexImageFloat(MatNpcPos, sx - 3, sy - 3, 8, 8, TransNum + 128, 0);
			}
		}
	}

	return TRUE;
}




int DrawMapArrow(int x, int y, int Angle)
{
	float fx[4], fy[4];
	int sinY, cosY;
	int dx[4], dy[4];
	int cnt;

	sinY = GetSin[Angle&ANGCLIP];
	cosY = GetCos[(Angle + ANGLE_180)&ANGCLIP];

	dx[0] = -8; dy[0] = -8;
	dx[1] = -8; dy[1] = 8;
	dx[2] = 8; dy[2] = -8;
	dx[3] = 8; dy[3] = 8;


	for(cnt = 0; cnt < 4; cnt++)
	{
		fx[cnt] = (float)((dy[cnt] * sinY + dx[cnt] * cosY) >> 8);
		fy[cnt] = (float)((dy[cnt] * cosY - dx[cnt] * sinY) >> 8);
		fx[cnt] /= 256;
		fy[cnt] /= 256;
		fx[cnt] += (float)x;
		fy[cnt] += (float)y;
	}


	psDrawTexImage2(smMaterial[MatArrow].smTexture[0], fx, fy, 0, 0, 1, 1, 255, 0);



	return TRUE;
}


int DrawFieldMap(sCOMPACT_MAP *lpCompactMap, int px, int py, int size)
{

	int x, z;
	int w, h;
	int left, right, bottom, top;
	float fx, fy, fw, fh;

	float dx, dy, dw, dh;
	float sc;

	if(!lpCompactMap->lpField || !lpCompactMap->hTexHandle) return FALSE;

	w = lpCompactMap->rx;
	h = lpCompactMap->ry;
	x = (lpCurPlayer->pX - lpCompactMap->StageRect.left);

	z = (lpCompactMap->StageRect.bottom - lpCurPlayer->pZ);

	left = x - size;
	right = x + size;
	top = z - size;
	bottom = z + size;

	dx = (float)px;
	dy = (float)py;
	dw = 126;
	dh = 126;

	float fpx;
	float fpy;
	float fmx, fmy;

	fpx = ((float)((size >> FLOATNS))) / (float)w;
	fpy = ((float)((size >> FLOATNS))) / (float)h;

	fmx = ((float)(x >> FLOATNS)) / (float)w;
	fmy = ((float)(z >> FLOATNS)) / (float)h;

	fx = fmx - fpx;
	fw = fmx + fpx;

	fy = fmy - fpy;
	fh = fmy + fpy;

	if((fx < 0 && fw < 0) || (fx > 1 && fw > 1)) return FALSE;
	if((fy < 0 && fh < 0) || (fy > 1 && fh > 1)) return FALSE;

	if(fx < 0)
	{
		sc = (-fx*(64 / fpx));
		dx = dx + sc;
		dw = dw - sc;
		fx = 0;
	}
	if(fw > 1)
	{
		sc = ((fw - 1)*(64 / fpx));
		dw = dw - sc;
		fw = 1;
	}

	if(fy < 0)
	{
		sc = (-fy*(64 / fpy));
		dy = dy + sc;
		dh = dh - sc;
		fy = 0;
	}
	if(fh > 1)
	{
		sc = ((fh - 1)*(64 / fpy));
		dh = dh - sc;
		fh = 1;
	}

	psDrawTexImage(lpCompactMap->hTexHandle, dx, dy, dw, dh, fx, fy, fw, fh, 255, 0);

	return TRUE;
}

int psDrawTexImage(smTEXTUREHANDLE *hTexHandle, float x, float y, float w, float h,
	float fx, float fy, float fw, float fh, int Transp, int specular)
{
	D3DTLVERTEX tlVertex[4];
	int cnt;
	for (cnt = 0; cnt < 4; cnt++)

	{
		tlVertex[cnt].rhw = 1;
		tlVertex[cnt].color = D3DCOLOR_RGBA(255, 255, 255, Transp);
		tlVertex[cnt].specular = D3DCOLOR_RGBA(specular, specular, specular, 0);
		tlVertex[cnt].sz = 0;
	}
	tlVertex[0].sx = x;
	tlVertex[0].sy = y;
	tlVertex[0].tu = fx;
	tlVertex[0].tv = fy;
	tlVertex[1].sx = x;
	tlVertex[1].sy = y + h;
	tlVertex[1].tu = fx;
	tlVertex[1].tv = fh;
	tlVertex[2].sx = x + w;
	tlVertex[2].sy = y;
	tlVertex[2].tu = fw;
	tlVertex[2].tv = fy;
	tlVertex[3].sx = x + w;
	tlVertex[3].sy = y + h;
	tlVertex[3].tu = fw;
	tlVertex[3].tv = fh;
	MagFilter = true;
	DrawTexture(hTexHandle->lpD3DTexture, tlVertex, true);
	MagFilter = false;
	return TRUE;
}


int psDrawTexImage_Point(smTEXTUREHANDLE *hTexHandle, float x, float y, float w, float h,
	float fx, float fy, float fw, float fh, int Transp, int specular)
{
	D3DTLVERTEX tlVertex[4];
	int cnt;
	for (cnt = 0; cnt < 4; cnt++)

	{
		tlVertex[cnt].rhw = 1;
		tlVertex[cnt].color = D3DCOLOR_RGBA(255, 255, 255, Transp);
		tlVertex[cnt].specular = D3DCOLOR_RGBA(specular, specular, specular, 0);
		tlVertex[cnt].sz = 0;
	}
	tlVertex[0].sx = x;
	tlVertex[0].sy = y;
	tlVertex[0].tu = fx;
	tlVertex[0].tv = fy;
	tlVertex[1].sx = x;
	tlVertex[1].sy = y + h;
	tlVertex[1].tu = fx;
	tlVertex[1].tv = fh;
	tlVertex[2].sx = x + w;
	tlVertex[2].sy = y;
	tlVertex[2].tu = fw;
	tlVertex[2].tv = fy;
	tlVertex[3].sx = x + w;
	tlVertex[3].sy = y + h;
	tlVertex[3].tu = fw;
	tlVertex[3].tv = fh;
	DrawTexture(hTexHandle->lpD3DTexture, tlVertex, true);
	return TRUE;
}


int psDrawTexImage2(smTEXTUREHANDLE *hTexHandle, float *x, float *y, float fx, float fy, float fw, float fh, int Transp, int specular)
{
	D3DTLVERTEX tlVertex[4];
	int cnt;
	for (cnt = 0; cnt < 4; cnt++)

	{
		tlVertex[cnt].rhw = 1;
		tlVertex[cnt].color = D3DCOLOR_RGBA(255, 255, 255, Transp);
		tlVertex[cnt].specular = D3DCOLOR_RGBA(specular, specular, specular, 0);
		tlVertex[cnt].sz = 0;
	}
	tlVertex[0].sx = x[0];
	tlVertex[0].sy = y[0];
	tlVertex[0].tu = fx;
	tlVertex[0].tv = fy;
	tlVertex[1].sx = x[1];
	tlVertex[1].sy = y[1];
	tlVertex[1].tu = fx;
	tlVertex[1].tv = fh;
	tlVertex[2].sx = x[2];
	tlVertex[2].sy = y[2];
	tlVertex[2].tu = fw;
	tlVertex[2].tv = fy;
	tlVertex[3].sx = x[3];
	tlVertex[3].sy = y[3];
	tlVertex[3].tu = fw;
	tlVertex[3].tv = fh;
	DrawTexture(hTexHandle->lpD3DTexture, tlVertex, true);
	return TRUE;
}



int EecodeCompress(BYTE *lpSrcData, BYTE *lpDestData, int size, int DestSize)
{
	int EncCounter;
	int cnt;
	int Counter;
	int pSet;
	BYTE c1, c2;
	int lsize;

	Counter = 0;
	EncCounter = 4;
	lsize = size - 1;

	while(1)
	{
		if(Counter >= size) break;
		if(EncCounter >= DestSize) break;

		c1 = lpSrcData[Counter];
		if(Counter < lsize) c2 = lpSrcData[Counter + 1];
		else c2 = c1;

		if(c1 == 0 && c2 == 0)
		{

			for(cnt = 0; cnt < 0x7F; cnt++)
			{
				if(Counter >= size) break;
				if(lpSrcData[Counter] != 0) break;
				Counter++;
			}
			if(EncCounter >= DestSize) break;
			lpDestData[EncCounter++] = cnt | 0x80;
		}
		else
		{

			pSet = EncCounter;
			EncCounter++;

			for(cnt = 0; cnt < 0x7F; cnt++)
			{

				c1 = lpSrcData[Counter];
				if(Counter < lsize) c2 = lpSrcData[Counter + 1];
				else c2 = c1;

				if(Counter >= size) break;
				if(EncCounter >= DestSize) break;
				if(c1 == 0 && c2 == 0) break;
				lpDestData[EncCounter++] = lpSrcData[Counter++];
			}
			lpDestData[pSet] = cnt;
		}
	}


	((int *)lpDestData)[0] = EncCounter;

	return EncCounter;
}




int DecodeCompress_ItemPotion(rsPLAYINFO *lpPlayInfo, BYTE *lpSrcData, BYTE *lpDestData, int deCount, void *lpTransRecdata)
{

	int DecCounter;
	int cnt;
	int Counter;
	int size;
	int len;
	int dCount = deCount;
	int pCnt;
	TRANS_RECORD_DATA	*lpTransRecordData = (TRANS_RECORD_DATA *)lpTransRecdata;

	sRECORD_ITEM	*lpRecordItem = (sRECORD_ITEM *)lpDestData;

	size = ((int *)lpSrcData)[0];

	Counter = 4;
	DecCounter = 0;

	while(1)
	{
		if(Counter >= size) break;
		if(lpSrcData[Counter] & 0x80)
		{

			len = lpSrcData[Counter++] & 0x7F;
			for(cnt = 0; cnt < len; cnt++)
			{
				if(DecCounter >= dCount)
				{
					if(dCount >= sizeof(sRECORD_ITEM)) goto Skip_Decmp;
					if((lpRecordItem->sItemInfo.CODE&sinITEM_MASK1) != (sinPM1&sinITEM_MASK1))
						return Counter;

					dCount = sizeof(sRECORD_ITEM);
				}
				lpDestData[DecCounter++] = 0;
			}

		}
		else
		{
			len = lpSrcData[Counter++] & 0x7F;
			for(cnt = 0; cnt < len; cnt++)
			{
				if(DecCounter >= dCount)
				{
					if(dCount >= sizeof(sRECORD_ITEM)) goto Skip_Decmp;
					if((lpRecordItem->sItemInfo.CODE&sinITEM_MASK1) != (sinPM1&sinITEM_MASK1))
						return Counter;

					dCount = sizeof(sRECORD_ITEM);
				}
				lpDestData[DecCounter++] = lpSrcData[Counter++];
			}
		}
	}

Skip_Decmp:

	if(lpTransRecordData)
	{

		for(cnt = 0; cnt < lpTransRecordData->ThrowItemCount; cnt++)
		{

			if(lpTransRecordData->ThrowItemInfo[cnt].dwCode == lpRecordItem->sItemInfo.CODE &&
				lpTransRecordData->ThrowItemInfo[cnt].dwKey == lpRecordItem->sItemInfo.ItemHeader.Head &&
				lpTransRecordData->ThrowItemInfo[cnt].dwSum == lpRecordItem->sItemInfo.ItemHeader.dwChkSum)
			{


				return Counter;

			}
		}
	}

	pCnt = lpRecordItem->sItemInfo.PotionCount;
	if(pCnt == 0) pCnt = 1;

	rsAddServerPotion(lpPlayInfo, lpRecordItem->sItemInfo.CODE, pCnt);
	return Counter;
}



int DecodeCompress(BYTE *lpSrcData, BYTE *lpDestData, int dCount)
{

	int DecCounter;
	int cnt;
	int Counter;
	int size;
	int len;

	size = ((int *)lpSrcData)[0];

	Counter = 4;
	DecCounter = 0;

	while(1)
	{
		if(Counter >= size) break;
		if(lpSrcData[Counter] & 0x80)
		{

			len = lpSrcData[Counter++] & 0x7F;
			for(cnt = 0; cnt < len; cnt++)
			{
				if(DecCounter >= dCount) return Counter;
				lpDestData[DecCounter++] = 0;
			}

		}
		else
		{
			len = lpSrcData[Counter++] & 0x7F;
			for(cnt = 0; cnt < len; cnt++)
			{
				if(DecCounter >= dCount) return Counter;
				lpDestData[DecCounter++] = lpSrcData[Counter++];
			}
		}
	}

	return Counter;
}



int DecodeCompress(BYTE *lpSrcData, BYTE *lpDestData)
{
	return DecodeCompress(lpSrcData, lpDestData, 0x7FFFF);
}

int EecodeCompress(BYTE *lpSrcData, BYTE *lpDestData, int size)
{
	return EecodeCompress(lpSrcData, lpDestData, size, 0x7FFFF);
}


smCHAR *CheckOtherPlayPosi(int x, int y, int z)
{
	int cnt;
	int dist;
	int dx, dz;


	if(ServerMode)
		return Serv_CheckOtherPlayPosi(x, y, z);

	for(cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if(chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].smCharInfo.Life[0] > 0 &&
			(chrOtherPlayer[cnt].dwLastTransTime + DISPLAY_TRANS_TIME_OVER) > dwPlayTime)
		{
			if((y - 16 * fONE) < chrOtherPlayer[cnt].pY && (y + 16 * fONE) > chrOtherPlayer[cnt].pY)
			{

				dx = (chrOtherPlayer[cnt].pX - x) >> FLOATNS;
				dz = (chrOtherPlayer[cnt].pZ - z) >> FLOATNS;
				dist = dx*dx + dz*dz;
				if(dist < (16 * 16)) return &chrOtherPlayer[cnt];
			}
		}
	}

	return NULL;
}




int MessageLoading = 0;


int smPlayWindowMessage()
{
	MSG msg;

	MessageLoading = TRUE;

	while(1)
	{
		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{

			TranslateMessage(&msg);
			if(msg.message == WM_SYSKEYDOWN || msg.message == WM_SYSKEYUP) continue;
			DispatchMessage(&msg);
		}
		else
			break;
	}

	MessageLoading = FALSE;
	return TRUE;
}


static DWORD iFormCode;
static DWORD iFromCnt;

static DWORD ReformStateCode(char *lpState, int size)
{
	int cnt;

	for(cnt = 0; cnt < size; cnt++)
	{
		iFormCode += ((DWORD)lpState[cnt])*((iFromCnt & 0x1FFF) + 1);
		iFromCnt++;
	}

	return iFormCode;
}

static DWORD CompareStateCode(char *lpState1, char *lpState2, int size)
{
	int cnt;

	for(cnt = 0; cnt < size; cnt++)
	{
		if(lpState1[cnt] != lpState2[cnt])
			return 1;
	}

	return 0;
}


static DWORD GetRefromItemCode_Old(sITEMINFO *lpItemInfo, int Key)
{

	iFormCode = 0;
	iFromCnt = Key;

	ReformStateCode((char *)&lpItemInfo->CODE, sizeof(DWORD));
	ReformStateCode((char *)lpItemInfo->ItemName, 32);

	ReformStateCode((char *)&lpItemInfo->Weight, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->Price, sizeof(int));

	ReformStateCode((char *)lpItemInfo->Resistance, sizeof(short) * 8);
	ReformStateCode((char *)lpItemInfo->Damage, sizeof(short) * 2);



	ReformStateCode((char *)&lpItemInfo->Shooting_Range, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->Attack_Speed, sizeof(int));

	ReformStateCode((char *)&lpItemInfo->Attack_Rating, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->Critical_Hit, sizeof(int));

	ReformStateCode((char *)&lpItemInfo->fSpeed, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->Potion_Space, sizeof(int));

	ReformStateCode((char *)&lpItemInfo->fMagic_Mastery, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fMana_Regen, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fLife_Regen, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fStamina_Regen, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fIncrease_Life, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fIncrease_Mana, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fIncrease_Stamina, sizeof(float));

	ReformStateCode((char *)&lpItemInfo->Level, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->Strength, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->Spirit, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->Talent, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->Dexterity, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->Health, sizeof(int));

	ReformStateCode((char *)lpItemInfo->Mana, sizeof(short) * 2);
	ReformStateCode((char *)lpItemInfo->Life, sizeof(short) * 2);
	ReformStateCode((char *)lpItemInfo->Stamina, sizeof(short) * 2);

	ReformStateCode((char *)&lpItemInfo->Money, sizeof(int));

	ReformStateCode((char *)&lpItemInfo->JobCodeMask, sizeof(DWORD));

	ReformStateCode((char *)&lpItemInfo->JobItem, sizeof(sITEM_SPECIAL));

	return iFormCode;
}

static DWORD GetRefromItemCode_V10(sITEMINFO *lpItemInfo, int Key)
{

	iFormCode = 0;
	iFromCnt = Key;

	ReformStateCode((char *)&lpItemInfo->CODE, sizeof(DWORD));
	ReformStateCode((char *)lpItemInfo->ItemName, 32);

	ReformStateCode((char *)&lpItemInfo->Weight, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->Price, sizeof(int));

	ReformStateCode((char *)lpItemInfo->Resistance, sizeof(short) * 8);
	ReformStateCode((char *)lpItemInfo->Damage, sizeof(short) * 2);

	ReformStateCode((char *)&lpItemInfo->Defence, sizeof(int));

	ReformStateCode((char *)&lpItemInfo->Shooting_Range, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->Attack_Speed, sizeof(int));

	ReformStateCode((char *)&lpItemInfo->Attack_Rating, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->Critical_Hit, sizeof(int));

	ReformStateCode((char *)&lpItemInfo->fSpeed, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->Potion_Space, sizeof(int));

	ReformStateCode((char *)&lpItemInfo->fMagic_Mastery, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fMana_Regen, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fLife_Regen, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fStamina_Regen, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fIncrease_Life, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fIncrease_Mana, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fIncrease_Stamina, sizeof(float));

	ReformStateCode((char *)&lpItemInfo->Level, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->Strength, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->Spirit, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->Talent, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->Dexterity, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->Health, sizeof(int));

	ReformStateCode((char *)lpItemInfo->Mana, sizeof(short) * 2);
	ReformStateCode((char *)lpItemInfo->Life, sizeof(short) * 2);
	ReformStateCode((char *)lpItemInfo->Stamina, sizeof(short) * 2);

	ReformStateCode((char *)&lpItemInfo->Money, sizeof(int));

	ReformStateCode((char *)&lpItemInfo->JobCodeMask, sizeof(DWORD));

	ReformStateCode((char *)&lpItemInfo->JobItem, sizeof(sITEM_SPECIAL));

	return iFormCode;
}

static int CompareReformItemCode_V10(sITEMINFO *lpItemInfo1, sITEMINFO *lpItemInfo2)
{
	int code = 0;

	code += CompareStateCode((char *)&lpItemInfo1->CODE, (char *)&lpItemInfo2->CODE, sizeof(DWORD));
	code += CompareStateCode((char *)lpItemInfo1->ItemName, (char *)lpItemInfo2->ItemName, 32);

	code += CompareStateCode((char *)&lpItemInfo1->Weight, (char *)&lpItemInfo2->Weight, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->Price, (char *)&lpItemInfo2->Price, sizeof(int));

	code += CompareStateCode((char *)lpItemInfo1->Resistance, (char *)lpItemInfo2->Resistance, sizeof(short) * 8);
	code += CompareStateCode((char *)lpItemInfo1->Damage, (char *)lpItemInfo2->Damage, sizeof(short) * 2);

	code += CompareStateCode((char *)&lpItemInfo1->Defence, (char *)&lpItemInfo2->Defence, sizeof(int));

	code += CompareStateCode((char *)&lpItemInfo1->Shooting_Range, (char *)&lpItemInfo2->Shooting_Range, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->Attack_Speed, (char *)&lpItemInfo2->Attack_Speed, sizeof(int));

	code += CompareStateCode((char *)&lpItemInfo1->Attack_Rating, (char *)&lpItemInfo2->Attack_Rating, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->Critical_Hit, (char *)&lpItemInfo2->Critical_Hit, sizeof(int));

	code += CompareStateCode((char *)&lpItemInfo1->fSpeed, (char *)&lpItemInfo2->fSpeed, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->Potion_Space, (char *)&lpItemInfo2->Potion_Space, sizeof(int));

	code += CompareStateCode((char *)&lpItemInfo1->fMagic_Mastery, (char *)&lpItemInfo2->fMagic_Mastery, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->fMana_Regen, (char *)&lpItemInfo2->fMana_Regen, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->fLife_Regen, (char *)&lpItemInfo2->fLife_Regen, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->fStamina_Regen, (char *)&lpItemInfo2->fStamina_Regen, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->fIncrease_Life, (char *)&lpItemInfo2->fIncrease_Life, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->fIncrease_Mana, (char *)&lpItemInfo2->fIncrease_Mana, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->fIncrease_Stamina, (char *)&lpItemInfo2->fIncrease_Stamina, sizeof(float));

	code += CompareStateCode((char *)&lpItemInfo1->Level, (char *)&lpItemInfo2->Level, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->Strength, (char *)&lpItemInfo2->Strength, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->Spirit, (char *)&lpItemInfo2->Spirit, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->Talent, (char *)&lpItemInfo2->Talent, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->Dexterity, (char *)&lpItemInfo2->Dexterity, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->Health, (char *)&lpItemInfo2->Health, sizeof(int));

	code += CompareStateCode((char *)lpItemInfo1->Mana, (char *)lpItemInfo2->Mana, sizeof(short) * 2);
	code += CompareStateCode((char *)lpItemInfo1->Life, (char *)lpItemInfo2->Life, sizeof(short) * 2);
	code += CompareStateCode((char *)lpItemInfo1->Stamina, (char *)lpItemInfo2->Stamina, sizeof(short) * 2);

	code += CompareStateCode((char *)&lpItemInfo1->Money, (char *)&lpItemInfo2->Money, sizeof(int));

	code += CompareStateCode((char *)&lpItemInfo1->JobCodeMask, (char *)&lpItemInfo2->JobCodeMask, sizeof(DWORD));

	code += CompareStateCode((char *)&lpItemInfo1->JobItem, (char *)&lpItemInfo2->JobItem, sizeof(sITEM_SPECIAL));

	return code;
}

static DWORD GetRefromItemCode(sITEMINFO *lpItemInfo, int Key)
{

	iFormCode = 0;
	iFromCnt = Key;

	ReformStateCode((char *)&lpItemInfo->CODE, sizeof(DWORD));
	ReformStateCode((char *)lpItemInfo->ItemName, 32);

	ReformStateCode((char *)&lpItemInfo->Weight, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->Price, sizeof(int));

	ReformStateCode((char *)lpItemInfo->Resistance, sizeof(short) * 8);
	ReformStateCode((char *)lpItemInfo->Damage, sizeof(short) * 2);

	ReformStateCode((char *)&lpItemInfo->fAbsorb, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->Defence, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->fBlock_Rating, sizeof(float));

	ReformStateCode((char *)&lpItemInfo->Shooting_Range, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->Attack_Speed, sizeof(int));

	ReformStateCode((char *)&lpItemInfo->Attack_Rating, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->Critical_Hit, sizeof(int));

	ReformStateCode((char *)&lpItemInfo->fSpeed, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->Potion_Space, sizeof(int));

	ReformStateCode((char *)&lpItemInfo->fMagic_Mastery, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fMana_Regen, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fLife_Regen, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fStamina_Regen, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fIncrease_Life, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fIncrease_Mana, sizeof(float));
	ReformStateCode((char *)&lpItemInfo->fIncrease_Stamina, sizeof(float));

	ReformStateCode((char *)&lpItemInfo->Level, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->Strength, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->Spirit, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->Talent, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->Dexterity, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->Health, sizeof(int));

	ReformStateCode((char *)lpItemInfo->Mana, sizeof(short) * 2);
	ReformStateCode((char *)lpItemInfo->Life, sizeof(short) * 2);
	ReformStateCode((char *)lpItemInfo->Stamina, sizeof(short) * 2);

	ReformStateCode((char *)&lpItemInfo->Money, sizeof(int));
	ReformStateCode((char *)&lpItemInfo->JobCodeMask, sizeof(DWORD));
	ReformStateCode((char *)&lpItemInfo->JobItem, sizeof(sITEM_SPECIAL));

	ReformStateCode((char *)&lpItemInfo->UniqueItem, sizeof(DWORD));
	ReformStateCode((char *)lpItemInfo->EffectBlink, sizeof(short) * 2);
	ReformStateCode((char *)lpItemInfo->EffectColor, sizeof(short) * 4);
	ReformStateCode((char *)lpItemInfo->ScaleBlink, sizeof(short) * 2);
	ReformStateCode((char *)&lpItemInfo->DispEffect, sizeof(DWORD));

	return iFormCode;
}


#ifdef _W_SERVER

static DWORD rsReformStateCode(char *lpState, int size)
{
	int cnt;

	for(cnt = 0; cnt < size; cnt++)
	{
		iFormCode += ((DWORD)lpState[cnt])*((iFromCnt & 0x7FF) + 1);
		iFromCnt++;
	}

	return iFormCode;
}

static DWORD rsGetRefromItemCode(sITEMINFO *lpItemInfo, int Key)
{

	iFormCode = 0;
	iFromCnt = Key;

	rsReformStateCode((char *)&lpItemInfo->CODE, sizeof(DWORD));
	rsReformStateCode((char *)lpItemInfo->ItemName, 32);

	rsReformStateCode((char *)&lpItemInfo->Weight, sizeof(int));
	rsReformStateCode((char *)&lpItemInfo->Price, sizeof(int));

	rsReformStateCode((char *)lpItemInfo->Resistance, sizeof(short) * 8);
	rsReformStateCode((char *)lpItemInfo->Damage, sizeof(short) * 2);

	rsReformStateCode((char *)&lpItemInfo->fAbsorb, sizeof(float));
	rsReformStateCode((char *)&lpItemInfo->Defence, sizeof(int));
	rsReformStateCode((char *)&lpItemInfo->fBlock_Rating, sizeof(float));

	rsReformStateCode((char *)&lpItemInfo->Shooting_Range, sizeof(int));
	rsReformStateCode((char *)&lpItemInfo->Attack_Speed, sizeof(int));

	rsReformStateCode((char *)&lpItemInfo->Attack_Rating, sizeof(int));
	rsReformStateCode((char *)&lpItemInfo->Critical_Hit, sizeof(int));

	rsReformStateCode((char *)&lpItemInfo->fSpeed, sizeof(float));
	rsReformStateCode((char *)&lpItemInfo->Potion_Space, sizeof(int));

	rsReformStateCode((char *)&lpItemInfo->fMagic_Mastery, sizeof(float));
	rsReformStateCode((char *)&lpItemInfo->fMana_Regen, sizeof(float));
	rsReformStateCode((char *)&lpItemInfo->fLife_Regen, sizeof(float));
	rsReformStateCode((char *)&lpItemInfo->fStamina_Regen, sizeof(float));
	rsReformStateCode((char *)&lpItemInfo->fIncrease_Life, sizeof(float));
	rsReformStateCode((char *)&lpItemInfo->fIncrease_Mana, sizeof(float));
	rsReformStateCode((char *)&lpItemInfo->fIncrease_Stamina, sizeof(float));

	rsReformStateCode((char *)&lpItemInfo->Level, sizeof(int));
	rsReformStateCode((char *)&lpItemInfo->Strength, sizeof(int));
	rsReformStateCode((char *)&lpItemInfo->Spirit, sizeof(int));
	rsReformStateCode((char *)&lpItemInfo->Talent, sizeof(int));
	rsReformStateCode((char *)&lpItemInfo->Dexterity, sizeof(int));
	rsReformStateCode((char *)&lpItemInfo->Health, sizeof(int));

	rsReformStateCode((char *)lpItemInfo->Mana, sizeof(short) * 2);
	rsReformStateCode((char *)lpItemInfo->Life, sizeof(short) * 2);
	rsReformStateCode((char *)lpItemInfo->Stamina, sizeof(short) * 2);

	rsReformStateCode((char *)&lpItemInfo->Money, sizeof(int));
	rsReformStateCode((char *)&lpItemInfo->JobCodeMask, sizeof(DWORD));
	rsReformStateCode((char *)&lpItemInfo->JobItem, sizeof(sITEM_SPECIAL));

	rsReformStateCode((char *)&lpItemInfo->UniqueItem, sizeof(DWORD));
	rsReformStateCode((char *)lpItemInfo->EffectBlink, sizeof(short) * 2);
	rsReformStateCode((char *)lpItemInfo->EffectColor, sizeof(short) * 4);
	rsReformStateCode((char *)lpItemInfo->ScaleBlink, sizeof(short) * 2);
	ReformStateCode((char *)&lpItemInfo->DispEffect, sizeof(DWORD));

	return iFormCode;
}

#ifdef _NEW_ITEM_FORMCODE3
#include "ItemForm2.h"
#else
#include "ItemForm.h"
#endif


int	rsGetItemForm_Server(sITEMINFO *lpItemInfo)
{

	return rsGetItem_ServerForm(lpItemInfo);

}


int	rsReformItem_Server(sITEMINFO *lpItemInfo)
{
	DWORD dwCode;


	dwCode = rsGetItemForm_Server(lpItemInfo);

	lpItemInfo->ItemHeader.dwTime = dwCode;

	return TRUE;
}

#else

int	rsGetItemForm_Server(sITEMINFO *lpItemInfo)
{

	return TRUE;
}

int	rsReformItem_Server(sITEMINFO *lpItemInfo)
{

	return TRUE;
}

#endif



static int CompareReformItemCode(sITEMINFO *lpItemInfo1, sITEMINFO *lpItemInfo2)
{

	int code;

	code = 0;

	code += CompareStateCode((char *)&lpItemInfo1->CODE, (char *)&lpItemInfo2->CODE, sizeof(DWORD));
	code += CompareStateCode((char *)lpItemInfo1->ItemName, (char *)lpItemInfo2->ItemName, 32);

	code += CompareStateCode((char *)&lpItemInfo1->Weight, (char *)&lpItemInfo2->Weight, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->Price, (char *)&lpItemInfo2->Price, sizeof(int));

	code += CompareStateCode((char *)lpItemInfo1->Resistance, (char *)lpItemInfo2->Resistance, sizeof(short) * 8);
	code += CompareStateCode((char *)lpItemInfo1->Damage, (char *)lpItemInfo2->Damage, sizeof(short) * 2);

	code += CompareStateCode((char *)&lpItemInfo1->fAbsorb, (char *)&lpItemInfo2->fAbsorb, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->Defence, (char *)&lpItemInfo2->Defence, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->fBlock_Rating, (char *)&lpItemInfo2->fBlock_Rating, sizeof(float));

	code += CompareStateCode((char *)&lpItemInfo1->Shooting_Range, (char *)&lpItemInfo2->Shooting_Range, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->Attack_Speed, (char *)&lpItemInfo2->Attack_Speed, sizeof(int));

	code += CompareStateCode((char *)&lpItemInfo1->Attack_Rating, (char *)&lpItemInfo2->Attack_Rating, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->Critical_Hit, (char *)&lpItemInfo2->Critical_Hit, sizeof(int));

	code += CompareStateCode((char *)&lpItemInfo1->fSpeed, (char *)&lpItemInfo2->fSpeed, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->Potion_Space, (char *)&lpItemInfo2->Potion_Space, sizeof(int));

	code += CompareStateCode((char *)&lpItemInfo1->fMagic_Mastery, (char *)&lpItemInfo2->fMagic_Mastery, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->fMana_Regen, (char *)&lpItemInfo2->fMana_Regen, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->fLife_Regen, (char *)&lpItemInfo2->fLife_Regen, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->fStamina_Regen, (char *)&lpItemInfo2->fStamina_Regen, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->fIncrease_Life, (char *)&lpItemInfo2->fIncrease_Life, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->fIncrease_Mana, (char *)&lpItemInfo2->fIncrease_Mana, sizeof(float));
	code += CompareStateCode((char *)&lpItemInfo1->fIncrease_Stamina, (char *)&lpItemInfo2->fIncrease_Stamina, sizeof(float));

	code += CompareStateCode((char *)&lpItemInfo1->Level, (char *)&lpItemInfo2->Level, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->Strength, (char *)&lpItemInfo2->Strength, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->Spirit, (char *)&lpItemInfo2->Spirit, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->Talent, (char *)&lpItemInfo2->Talent, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->Dexterity, (char *)&lpItemInfo2->Dexterity, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->Health, (char *)&lpItemInfo2->Health, sizeof(int));

	code += CompareStateCode((char *)lpItemInfo1->Mana, (char *)lpItemInfo2->Mana, sizeof(short) * 2);
	code += CompareStateCode((char *)lpItemInfo1->Life, (char *)lpItemInfo2->Life, sizeof(short) * 2);
	code += CompareStateCode((char *)lpItemInfo1->Stamina, (char *)lpItemInfo2->Stamina, sizeof(short) * 2);

	code += CompareStateCode((char *)&lpItemInfo1->Money, (char *)&lpItemInfo2->Money, sizeof(int));
	code += CompareStateCode((char *)&lpItemInfo1->JobCodeMask, (char *)&lpItemInfo2->JobCodeMask, sizeof(DWORD));
	code += CompareStateCode((char *)&lpItemInfo1->JobItem, (char *)&lpItemInfo2->JobItem, sizeof(sITEM_SPECIAL));

	code += CompareStateCode((char *)&lpItemInfo1->UniqueItem, (char *)&lpItemInfo2->UniqueItem, sizeof(DWORD));
	code += CompareStateCode((char *)lpItemInfo1->EffectBlink, (char *)lpItemInfo2->EffectBlink, sizeof(short) * 2);
	code += CompareStateCode((char *)lpItemInfo1->EffectColor, (char *)lpItemInfo2->EffectColor, sizeof(short) * 4);
	code += CompareStateCode((char *)lpItemInfo1->ScaleBlink, (char *)lpItemInfo2->ScaleBlink, sizeof(short) * 2);
	code += CompareStateCode((char *)&lpItemInfo1->DispEffect, (char *)&lpItemInfo2->DispEffect, sizeof(DWORD));

	return code;
}


static DWORD GetRefromTradeCode(sTRADE *lpTrade, int Key)
{

	int cnt;

	iFormCode = 0;
	iFromCnt = Key;

	for(cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
	{
		if(lpTrade->TradeItem[cnt].Flag)
		{
			ReformStateCode((char *)&lpTrade->TradeItem[cnt].sItemInfo.CODE, sizeof(DWORD));
			ReformStateCode((char *)&lpTrade->TradeItem[cnt].sItemInfo.ItemHeader.dwChkSum, sizeof(DWORD));
		}
	}
	ReformStateCode((char *)&lpTrade->Money, sizeof(int));

	return iFormCode;
}

static DWORD GetRefromCharState(smCHAR_INFO *lpCharInfo, int Key)
{

	iFormCode = 0;
	iFromCnt = Key;



	ReformStateCode((char *)&lpCharInfo->szModelName2, 64);

	ReformStateCode((char *)&lpCharInfo->Level, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->Strength, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->Spirit, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->Talent, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->Dexterity, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->Health, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->Level, sizeof(int));


	ReformStateCode((char *)&lpCharInfo->Accuracy, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->Attack_Rating, sizeof(int));
	ReformStateCode((char *)lpCharInfo->Attack_Damage, sizeof(int) * 2);
	ReformStateCode((char *)&lpCharInfo->Attack_Speed, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->Shooting_Range, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->Critical_Hit, sizeof(int));

	ReformStateCode((char *)&lpCharInfo->Defence, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->Chance_Block, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->Absorption, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->Move_Speed, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->Sight, sizeof(int));
	ReformStateCode((char *)lpCharInfo->Weight, sizeof(short) * 2);

	ReformStateCode((char *)lpCharInfo->Resistance, sizeof(short) * 8);
	ReformStateCode((char *)lpCharInfo->Attack_Resistance, sizeof(short) * 8);

	ReformStateCode((char *)lpCharInfo->Life, sizeof(short) * 2);
	ReformStateCode((char *)lpCharInfo->Mana, sizeof(short) * 2);
	ReformStateCode((char *)lpCharInfo->Stamina, sizeof(short) * 2);

	ReformStateCode((char *)&lpCharInfo->Exp, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->Next_Exp, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->Money, sizeof(int));
	ReformStateCode((char *)&lpCharInfo->StatePoint, sizeof(int));

#ifdef _MODE_EXP64
	ReformStateCode((char *)&lpCharInfo->Exp_High, sizeof(int));
#endif

	return iFormCode;
}


static int ItemFormVersion = 12;
static int ItemFormKey = 0;


int ReformItem(sITEMINFO *lpItemInfo)
{


	DWORD dwCode;

#ifdef _W_SERVER

	extern time_t		tServerTime;

	lpItemInfo->ItemHeader.Head = ItemFormKey + GetCurrentTime();

	dwCode = GetRefromItemCode(lpItemInfo, lpItemInfo->ItemHeader.Head);

	lpItemInfo->ItemHeader.dwChkSum = dwCode;
	lpItemInfo->ItemHeader.dwVersion = ItemFormVersion;
	lpItemInfo->dwCreateTime = (DWORD)tServerTime;

	if(!lpItemInfo->BackUpKey || !lpItemInfo->BackUpChkSum)
	{
		lpItemInfo->BackUpKey = lpItemInfo->ItemHeader.Head;
		lpItemInfo->BackUpChkSum = lpItemInfo->ItemHeader.dwChkSum;
	}

	ReformMixItem(lpItemInfo);
	rsReformItem_Server(lpItemInfo);

	lpItemInfo->Temp0 = lpItemInfo->ItemHeader.dwChkSum + lpItemInfo->CODE;

#else

	if(!lpItemInfo->CODE || lpItemInfo->CODE == (sinGG1 | sin01) || (lpItemInfo->CODE&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
	{
		lpItemInfo->ItemHeader.Head = ItemFormKey + GetCurrentTime();

		dwCode = GetRefromItemCode(lpItemInfo, lpItemInfo->ItemHeader.Head);

		lpItemInfo->ItemHeader.dwChkSum = dwCode;
		lpItemInfo->ItemHeader.dwVersion = ItemFormVersion;
	}
#endif

	ItemFormKey++;

	return TRUE;
}


int ReformItem_AdjustTime(sITEMINFO *lpItemInfo, int TimeAdjust)
{

#ifdef _W_SERVER


	DWORD dwCode;


	extern time_t		tServerTime;

	lpItemInfo->ItemHeader.Head = ItemFormKey + GetCurrentTime();

	dwCode = GetRefromItemCode(lpItemInfo, lpItemInfo->ItemHeader.Head);

	lpItemInfo->ItemHeader.dwChkSum = dwCode;
	lpItemInfo->ItemHeader.dwVersion = ItemFormVersion;
	lpItemInfo->dwCreateTime = (DWORD)tServerTime + TimeAdjust;

	if(!lpItemInfo->BackUpKey || !lpItemInfo->BackUpChkSum)
	{
		lpItemInfo->BackUpKey = lpItemInfo->ItemHeader.Head;
		lpItemInfo->BackUpChkSum = lpItemInfo->ItemHeader.dwChkSum;
	}

	ReformMixItem(lpItemInfo);
	rsReformItem_Server(lpItemInfo);

	lpItemInfo->Temp0 = lpItemInfo->ItemHeader.dwChkSum + lpItemInfo->CODE;

#endif

	ItemFormKey++;

	return TRUE;
}

#ifdef _W_SERVER


int CheckItemForm(sITEMINFO *lpItemInfo)
{
	DWORD dwCode;




	if(lpItemInfo->CODE == (sinGG1 | sin01) || (lpItemInfo->CODE&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1))
	{
		dwCode = GetRefromItemCode(lpItemInfo, lpItemInfo->ItemHeader.Head);
		if(lpItemInfo->ItemHeader.dwChkSum == dwCode) return TRUE;
		return FALSE;
	}



	dwCode = rsGetItemForm_Server(lpItemInfo);

	if(lpItemInfo->ItemHeader.dwTime == dwCode) return TRUE;

	return FALSE;
}

#else


int CheckItemForm(sITEMINFO *lpItemInfo)
{
	DWORD dwCode;

	dwCode = GetRefromItemCode(lpItemInfo, lpItemInfo->ItemHeader.Head);

	if(lpItemInfo->ItemHeader.dwChkSum == dwCode) return TRUE;

	return FALSE;
}

#endif


int CompareItems(sITEMINFO *lpItemInfo1, sITEMINFO *lpItemInfo2)
{

	if(lpItemInfo1->ItemHeader.dwVersion != (DWORD)ItemFormVersion) CheckItemForm(lpItemInfo1);
	if(lpItemInfo2->ItemHeader.dwVersion != (DWORD)ItemFormVersion) CheckItemForm(lpItemInfo2);

	if(lpItemInfo1->CODE != lpItemInfo2->CODE) return FALSE;
	if(lpItemInfo1->ItemHeader.Head != lpItemInfo2->ItemHeader.Head) return FALSE;
	if(lpItemInfo1->ItemHeader.dwChkSum != lpItemInfo2->ItemHeader.dwChkSum) return FALSE;

	if(CompareReformItemCode(lpItemInfo1, lpItemInfo2) == 0)
		return TRUE;

	return FALSE;
}


int ReformCharForm(smCHAR_INFO *lpCharInfo)
{
	DWORD dwCode;

	dwCode = GetRefromCharState(lpCharInfo, 10);

	lpCharInfo->RefomCode = dwCode;

	ItemFormKey++;

	return TRUE;
}


int CheckCharForm(smCHAR_INFO *lpCharInfo)
{
	DWORD dwCode;

	dwCode = GetRefromCharState(lpCharInfo, 10);

	if(lpCharInfo->RefomCode == dwCode) return TRUE;

	return FALSE;
}


int ReformCharForm()
{



	return ReformCharForm(&lpCurPlayer->smCharInfo);

}

#ifndef _GU
#define _GU

#include "AntiCheat\AntiCheat.h"

#endif

extern AntiCheat * pcAntiCheat;

int CheckCharForm()
{
	int val;

	val = CheckCharForm(&lpCurPlayer->smCharInfo);

	pcAntiCheat->CheckThread();

	if(val == FALSE)
	{


		SendSetHackUser(81);

		DisconnectServerCode = 4;
		DisconnectFlag = GetCurrentTime();

	}

	return val;
}


int ReformTrade(void *lpTrade)
{
	DWORD dwCode;

	dwCode = GetRefromTradeCode((sTRADE *)lpTrade, 84);

	((sTRADE *)lpTrade)->CheckMoney = dwCode;

	ItemFormKey++;

	return TRUE;
}


int CheckTrade(void *lpTrade)
{
	DWORD dwCode;

	dwCode = GetRefromTradeCode((sTRADE *)lpTrade, 84);

	if(((sTRADE *)lpTrade)->CheckMoney == (int)dwCode) return TRUE;


	SendSetHackUser2(4000, 0);

	return FALSE;
}




short GetMixItemForm(sITEMINFO *lpItemInfo)
{
	short sCode = 0;

#ifdef _W_SERVER

	DWORD dwCode;
	DWORD dwItemKey;

	if(lpItemInfo->ItemKindCode)
	{
		dwItemKey = lpItemInfo->ItemHeader.dwChkSum;



		dwCode = lpItemInfo->ItemKindCode*(
			lpItemInfo->ItemAgingNum[0] * 3 + lpItemInfo->ItemAgingNum[1] * 7 + lpItemInfo->ItemAgingCount[1] * 17 + 17);

		dwCode = dwCode^dwItemKey;

		sCode = (short)((dwCode >> 16) ^ (dwCode & 0xFFFF));
}
#endif

	return sCode;
}


int ReformMixItem(sITEMINFO *lpItemInfo)
{
#ifdef _W_SERVER
	lpItemInfo->ItemAgingProtect[0] = GetMixItemForm(lpItemInfo);
#endif
	return TRUE;
}


int CheckMixItem(sITEMINFO *lpItemInfo)
{

#ifdef _W_SERVER
	if(GetMixItemForm(lpItemInfo) == lpItemInfo->ItemAgingProtect[0])
	{
		return TRUE;
	}
#else
	return TRUE;
#endif

	return FALSE;
}


float GetItemAbsorb(sITEMINFO *lpItemInfo)
{
	DWORD	dwCode = lpItemInfo->CODE&sinITEM_MASK2;
	float	fAborb = lpItemInfo->fAbsorb;




	if(dwCode == sinDA1)
	{
		switch(lpItemInfo->CODE)
		{

		case (sinDA1 | sin02):
			fAborb += 0.3f;
			break;
		case (sinDA1 | sin03):
			fAborb += 0.6f;
			break;
		case (sinDA1 | sin04):
			fAborb += 1.0f;
			break;
		case (sinDA1 | sin05):
			fAborb += 1.3f;
			break;

		case (sinDA1 | sin06):
			fAborb += 1.6f;
			break;
		case (sinDA1 | sin07):
			fAborb += 1.9f;
			break;
		case (sinDA1 | sin08):
			fAborb += 2.3f;
			break;
		case (sinDA1 | sin09):
			fAborb += 2.6f;
			break;
		case (sinDA1 | sin10):
			fAborb += 3.0f;
			break;

		case (sinDA1 | sin11):
			fAborb += 3.4f;
			break;
		case (sinDA1 | sin12):
			fAborb += 3.7f;
			break;
		case (sinDA1 | sin13):
			fAborb += 4.0f;
			break;
		case (sinDA1 | sin14):
			fAborb += 4.2f;
			break;
		case (sinDA1 | sin15):
			fAborb += 4.5f;
			break;

		case (sinDA1 | sin16):
			fAborb += 4.8f;
			break;
		case (sinDA1 | sin17):
			fAborb += 5.3f;
			break;
		case (sinDA1 | sin18):
			fAborb += 6.0f;
			break;
		case (sinDA1 | sin19):
			fAborb += 7.0f;
			break;
		case (sinDA1 | sin20):
			fAborb += 8.4f;
			break;

		}
	}
	else if(dwCode == sinDA2)
	{
		switch(lpItemInfo->CODE)
		{

		case (sinDA2 | sin02):
			fAborb += 0.3f;
			break;
		case (sinDA2 | sin03):
			fAborb += 0.6f;
			break;
		case (sinDA2 | sin04):
			fAborb += 0.9f;
			break;
		case (sinDA2 | sin05):
			fAborb += 1.2f;
			break;

		case (sinDA2 | sin06):
			fAborb += 1.5f;
			break;
		case (sinDA2 | sin07):
			fAborb += 1.8f;
			break;
		case (sinDA2 | sin08):
			fAborb += 2.1f;
			break;
		case (sinDA2 | sin09):
			fAborb += 2.4f;
			break;
		case (sinDA2 | sin10):
			fAborb += 2.7f;
			break;

		case (sinDA2 | sin11):
			fAborb += 3.0f;
			break;
		case (sinDA2 | sin12):
			fAborb += 3.3f;
			break;
		case (sinDA2 | sin13):
			fAborb += 3.6f;
			break;
		case (sinDA2 | sin14):
			fAborb += 3.9f;
			break;
		case (sinDA2 | sin15):
			fAborb += 4.2f;
			break;

		case (sinDA2 | sin16):
			fAborb += 4.5f;
			break;
		case (sinDA2 | sin17):
			fAborb += 4.9f;
			break;
		case (sinDA2 | sin18):
			fAborb += 5.5f;
			break;
		case (sinDA2 | sin19):
			fAborb += 6.8f;
			break;
		case (sinDA2 | sin20):
			fAborb += 8.0f;
			break;


		}
	}

#ifdef _LANGUAGE_ENGLISH_NEXTUP

	else if(dwCode == sinDB1)
	{
		switch(lpItemInfo->CODE)
		{

		case (sinDB1 | sin01):
			fAborb += 0.0f;
			break;
		case (sinDB1 | sin02):
			fAborb += 0.0f;
			break;
		case (sinDB1 | sin03):
			fAborb += 0.2f;
			break;
		case (sinDB1 | sin04):
			fAborb += 0.3f;
			break;
		case (sinDB1 | sin05):
			fAborb += 0.4f;
			break;

		case (sinDB1 | sin06):
			fAborb += 0.5f;
			break;
		case (sinDB1 | sin07):
			fAborb += 0.6f;
			break;
		case (sinDB1 | sin08):
			fAborb += 0.7f;
			break;
		case (sinDB1 | sin09):
			fAborb += 0.8f;
			break;
		case (sinDB1 | sin10):
			fAborb += 1.1f;
			break;

		case (sinDB1 | sin11):
			fAborb += 1.3f;
			break;
		case (sinDB1 | sin12):
			fAborb += 1.5f;
			break;
		case (sinDB1 | sin13):
			fAborb += 1.7f;
			break;
		case (sinDB1 | sin14):
			fAborb += 1.9f;
			break;
		case (sinDB1 | sin15):
			fAborb += 2.1f;
			break;

		case (sinDB1 | sin16):
			fAborb += 2.3f;
			break;
		case (sinDB1 | sin17):
			fAborb += 2.5f;
			break;
		case (sinDB1 | sin18):
			fAborb += 2.7f;
			break;
		case (sinDB1 | sin19):
			fAborb += 2.9f;
			break;
		case (sinDB1 | sin20):
			fAborb += 3.1f;
			break;

		}
	}
	else if(dwCode == sinDG1)
	{
		switch(lpItemInfo->CODE)
		{

		case (sinDG1 | sin01):
			fAborb += 0.0f;
			break;
		case (sinDG1 | sin02):
			fAborb += 0.0f;
			break;
		case (sinDG1 | sin03):
			fAborb += 0.1f;
			break;
		case (sinDG1 | sin04):
			fAborb += 0.2f;
			break;
		case (sinDG1 | sin05):
			fAborb += 0.3f;
			break;

		case (sinDG1 | sin06):
			fAborb += 0.4f;
			break;
		case (sinDG1 | sin07):
			fAborb += 0.5f;
			break;
		case (sinDG1 | sin08):
			fAborb += 0.6f;
			break;
		case (sinDG1 | sin09):
			fAborb += 0.7f;
			break;
		case (sinDG1 | sin10):
			fAborb += 0.9f;
			break;

		case (sinDG1 | sin11):
			fAborb += 1.1f;
			break;
		case (sinDG1 | sin12):
			fAborb += 1.3f;
			break;
		case (sinDG1 | sin13):
			fAborb += 1.5f;
			break;
		case (sinDG1 | sin14):
			fAborb += 1.7f;
			break;
		case (sinDG1 | sin15):
			fAborb += 1.9f;
			break;

		case (sinDG1 | sin16):
			fAborb += 2.1f;
			break;
		case (sinDG1 | sin17):
			fAborb += 2.3f;
			break;
		case (sinDG1 | sin18):
			fAborb += 2.5f;
			break;
		case (sinDG1 | sin19):
			fAborb += 2.7f;
			break;
		case (sinDG1 | sin20):
			fAborb += 2.9f;
			break;

		}
	}
	else if(dwCode == sinDS1)
	{
		switch(lpItemInfo->CODE)
		{

		case (sinDS1 | sin01):
			fAborb += 0.5f;
			break;
		case (sinDS1 | sin02):
			fAborb += 0.6f;
			break;
		case (sinDS1 | sin03):
			fAborb += 0.7f;
			break;
		case (sinDS1 | sin04):
			fAborb += 0.8f;
			break;
		case (sinDS1 | sin05):
			fAborb += 0.9f;
			break;

		case (sinDS1 | sin06):
			fAborb += 1.0f;
			break;
		case (sinDS1 | sin07):
			fAborb += 1.0f;
			break;
		case (sinDS1 | sin08):
			fAborb += 1.1f;
			break;
		case (sinDS1 | sin09):
			fAborb += 1.3f;
			break;
		case (sinDS1 | sin10):
			fAborb += 1.4f;
			break;

		case (sinDS1 | sin11):
			fAborb += 1.5f;
			break;
		case (sinDS1 | sin12):
			fAborb += 1.6f;
			break;
		case (sinDS1 | sin13):
			fAborb += 1.7f;
			break;
		case (sinDS1 | sin14):
			fAborb += 1.8f;
			break;
		case (sinDS1 | sin15):
			fAborb += 1.9f;
			break;

		case (sinDS1 | sin16):
			fAborb += 2.0f;
			break;
		case (sinDS1 | sin17):
			fAborb += 2.1f;
			break;
		case (sinDS1 | sin18):
			fAborb += 2.2f;
			break;
		case (sinDS1 | sin19):
			fAborb += 2.3f;
			break;
		case (sinDS1 | sin20):
			fAborb += 2.4f;
			break;

		}
	}

#endif
	return	fAborb;
}


#define WAIT_BATTLE_QUIT_TIME		10000


int QuitGame()
{
#ifdef _XIGNCODE_CLIENT

	ZCWAVE_Cleanup();
	ZCWAVE_SysExit();
#endif

	if(quit)
		return TRUE;

	if(dwBattleTime)
	{
		if((dwBattleTime + WAIT_BATTLE_QUIT_TIME) > dwPlayTime)
		{
			dwBattleQuitTime = dwPlayTime;
			return FALSE;
		}
	}


	if(cWareHouse.OpenFlag || cCraftItem.OpenFlag || cTrade.OpenFlag || cAging.OpenFlag || SmeltingItem.OpenFlag || ManufactureItem.m_OpenFlag || cMixtureReset.OpenFlag)
	{
		dwCloseBoxTime = dwPlayTime + 2000;
		return FALSE;
	}

	quit = 1;

	return TRUE;
}

#define CHARINFO_CACHE_MAX		200

smTRNAS_PLAYERINFO	CharInfo_Cache[CHARINFO_CACHE_MAX];
DWORD	dwCharInfo_CacheCode[CHARINFO_CACHE_MAX];
int	CharInfoCacheCnt = 0;


smTRNAS_PLAYERINFO	*GetCharInfoCache(char *lpData)
{
	int cnt = 0;
	smPLAYDATA *lpPlayData = nullptr;
	smTRANS_PLAYDATA *lpTransPlayData = nullptr;
	smTRANS_PLAYBUFF *lpTransPlayBuff = nullptr;
	smTRNAS_PLAYERINFO *lpTransPlayInfo = nullptr;

	int RecvCode = ((int *)lpData)[1];

	DWORD dwChkCode = 0;

	switch(RecvCode)
	{
	case OpCode::OPCODE_PLAYDATA1:
		lpPlayData = (smPLAYDATA *)lpData;
		dwChkCode = lpPlayData->dwAutoCharCode;
		break;
	case OpCode::OPCODE_TRANSPLAYDATA:
		lpTransPlayData = (smTRANS_PLAYDATA *)lpData;
		lpTransPlayBuff = (smTRANS_PLAYBUFF *)(lpData + sizeof(smTRANS_PLAYDATA));
		if(lpTransPlayData->PlayBuffCnt > 0)
			dwChkCode = lpTransPlayData->dwAutoCharCode;
		break;
	}

	if(!dwChkCode) return NULL;

	for(cnt = 0; cnt < CharInfoCacheCnt; cnt++)
	{
		if(dwChkCode == dwCharInfo_CacheCode[cnt])
		{

			lpTransPlayInfo = &CharInfo_Cache[cnt];

			switch(RecvCode)
			{
			case OpCode::OPCODE_PLAYDATA1:

				lpTransPlayInfo->x = lpPlayData->x;
				lpTransPlayInfo->y = lpPlayData->y;
				lpTransPlayInfo->z = lpPlayData->z;
				lpTransPlayInfo->ax = lpPlayData->x;
				lpTransPlayInfo->ay = lpPlayData->y;
				lpTransPlayInfo->az = lpPlayData->z;
				lpTransPlayInfo->dwObjectSerial = lpPlayData->dwObjectSerial;
				lpTransPlayInfo->smCharInfo.dwObjectSerial = lpPlayData->dwObjectSerial;
				break;

			case OpCode::OPCODE_TRANSPLAYDATA:

				lpTransPlayBuff = (smTRANS_PLAYBUFF *)(((char *)lpTransPlayData) + sizeof(smTRANS_PLAYDATA));
				lpTransPlayBuff += lpTransPlayData->PlayBuffCnt - 1;

				lpTransPlayInfo->x = lpTransPlayBuff->PlayBuff.x;
				lpTransPlayInfo->y = lpTransPlayBuff->PlayBuff.y;
				lpTransPlayInfo->z = lpTransPlayBuff->PlayBuff.z;

				lpTransPlayInfo->ax = lpTransPlayBuff->PlayBuff.angle[0];
				lpTransPlayInfo->ay = lpTransPlayBuff->PlayBuff.angle[1];
				lpTransPlayInfo->az = lpTransPlayBuff->PlayBuff.angle[2];
				lpTransPlayInfo->dwObjectSerial = lpTransPlayData->dwObjectSerial;
				lpTransPlayInfo->smCharInfo.dwObjectSerial = lpTransPlayData->dwObjectSerial;
				break;
			}

			lpTransPlayInfo->smCharInfo.Life[0] = lpTransPlayInfo->smCharInfo.Life[1];
			return lpTransPlayInfo;
		}
	}

	return NULL;
}


int SaveCharInfoCache(smTRNAS_PLAYERINFO *lpTransPlayInfo)
{
	int cnt;
	DWORD	dwCode;

	dwCode = GetSpeedSum(lpTransPlayInfo->smCharInfo.szName);


	for(cnt = 0; cnt < CharInfoCacheCnt; cnt++)
	{
		if(dwCode == dwCharInfo_CacheCode[cnt]) return NULL;
	}


	dwCharInfo_CacheCode[CharInfoCacheCnt] = dwCode;
	memcpy(&CharInfo_Cache[CharInfoCacheCnt], lpTransPlayInfo, sizeof(smTRNAS_PLAYERINFO));
	CharInfoCacheCnt++;

	return TRUE;
}


#include "cPartyWindow.h"
int	RequestPartyPlayers(smCHAR* lpChar)
{
	return cParty.RequestPartyPlayers(lpChar);
	/*
		int cnt, cnt2;


		if(lpChar)
		{
			lpChar->PartyFlag = FALSE;

			for(cnt = 0; cnt < InterfaceParty.PartyMemberCount; cnt++)
			{
				if(InterfaceParty.PartyMember[cnt].ChrCode == lpChar->dwObjectSerial)
				{
					lpChar->PartyFlag = TRUE;
					return TRUE;
				}
			}
		}
		else
		{

			for(cnt2 = 0; cnt2 < OTHER_PLAYER_MAX; cnt2++)
			{
				if(chrOtherPlayer[cnt2].Flag && chrOtherPlayer[cnt2].dwObjectSerial)
				{
					chrOtherPlayer[cnt2].PartyFlag = FALSE;
					for(cnt = 0; cnt < InterfaceParty.PartyMemberCount; cnt++)
					{
						if(InterfaceParty.PartyMember[cnt].ChrCode == chrOtherPlayer[cnt2].dwObjectSerial)
						{
							chrOtherPlayer[cnt2].PartyFlag = TRUE;
							break;
						}
					}
				}
			}
		}

		return FALSE;*/
}


smCHAR	chrPartyPlayer;


int OpenPartyPlayer(char* szName, char* szModelFile1, char* szModelFile2)
{

	AddLoaderPattern(&chrPartyPlayer, szModelFile1, szModelFile2);

	chrPartyPlayer.SetMotionFromCode(CHRMOTION_STATE_STAND);
	chrPartyPlayer.ActionPattern = 101;
	chrPartyPlayer.Flag = TRUE;
	chrPartyPlayer.lpStage = 0;
	chrPartyPlayer.OnStageField = lpCurPlayer->OnStageField;

	strcpy_s(chrPartyPlayer.smCharInfo.szName, szName);

	OpenEachPlayer(&chrPartyPlayer);

	return TRUE;
}



char	szLastWhisperName[32] = { 0 };
int		LastWhisperLen = 0;


int	WhisperPartyPlayer(char* szName)
{
	char szBuff[128];
	int len;

	strcpy_s(szLastWhisperName, szName);

	chatlistSPEAKERflagChg(FALSE);
	cInterFace.ChatFlag = TRUE;
	hFocusWnd = hTextWnd;
	wsprintf(szBuff, "/:%s ", szName);
	len = lstrlen(szBuff);
	LastWhisperLen = len;
	SetWindowText(hFocusWnd, szBuff);
	SendMessage(hFocusWnd, EM_SETSEL, len, len);


	SetIME_Mode(TRUE);

	return TRUE;
}


int	SetClanChatting()
{
	char szBuff[128];
	int len;

	szLastWhisperName[0] = 0;
	hFocusWnd = hTextWnd;
	cInterFace.ChatFlag = TRUE;
	wsprintf(szBuff, "/CLAN> ");
	len = lstrlen(szBuff);
	LastWhisperLen = len;
	SetWindowText(hFocusWnd, szBuff);
	SendMessage(hFocusWnd, EM_SETSEL, len, len);

	SetIME_Mode(TRUE);

	return TRUE;
}


int IsClanChatting()
{
	if (lpCurPlayer->smCharInfo.ClassClan)
	{
		if (!chatlistSPEAKERflag())
		{
			chatlistSPEAKERflagChg(TRUE);
			SetClanChatting();
			return TRUE;
		}
		else
		{
			chatlistSPEAKERflagChg(FALSE);
			SetWindowText(hFocusWnd, "");
			return TRUE;
		}
		szLastWhisperName[0] = 0;
	}

	return FALSE;
}


int	PlayAttackCount = 0;
int	MotionAttackCount = 0;



int	AttackRecvCountUp()
{
	PlayAttackCount++;
	return PlayAttackCount;
}


int AttackMotionCountUp()
{
	MotionAttackCount++;
	if(MotionAttackCount > 30)
	{

		CheckPlayAttackCount();
	}

	return MotionAttackCount;
}


int	CheckPlayAttackCount()
{

	if(MotionAttackCount > 30 && PlayAttackCount <= 3)
	{


	}

	MotionAttackCount = 0;
	PlayAttackCount = 0;

	return TRUE;
}

struct	sCOPY_ITEM_INFO
{
	DWORD	dwItemCode;
	int		ChkSum;
	int		Header;
};

sCOPY_ITEM_INFO	sCopyItemList[] = {

	{	0,0,0	}

};


int	CheckCopyItem(sITEMINFO *lpItem)
{
	int cnt;

	cnt = 0;

	if(!lpItem->ItemName[0])	return FALSE;
	if(lpItem->SpecialItemFlag[0])	return FALSE;

	if(!lpItem->BackUpKey || !lpItem->BackUpChkSum)
	{
		lpItem->BackUpKey = lpItem->ItemHeader.Head;
		lpItem->BackUpChkSum = lpItem->ItemHeader.dwChkSum;
	}

	while(1)
	{
		if(sCopyItemList[cnt].dwItemCode == 0) break;


		if(sCopyItemList[cnt].dwItemCode == lpItem->CODE)
		{
			if(sCopyItemList[cnt].ChkSum == (int)lpItem->ItemHeader.dwChkSum &&
				sCopyItemList[cnt].Header == (int)lpItem->ItemHeader.Head)
			{

				lpItem->SpecialItemFlag[0] = CHECK_COPY_ITEM;
				return TRUE;
			}
			if(sCopyItemList[cnt].ChkSum == (int)lpItem->BackUpChkSum &&
				sCopyItemList[cnt].Header == (int)lpItem->BackUpKey)
			{

				lpItem->SpecialItemFlag[0] = CHECK_COPY_ITEM;
				return TRUE;
			}
		}
		cnt++;
	}


	return FALSE;
}



int SetJobFace(char *szModelName)
{

	strcpy_s(lpCurPlayer->smCharInfo.szModelName2, szModelName);
	AddLoaderPattern(lpCurPlayer, lpCurPlayer->smCharInfo.szModelName, lpCurPlayer->smCharInfo.szModelName2);
	lpCurPlayer->smCharInfo.bUpdateInfo[0]++;
	ReformCharForm();


	SendSetObjectSerial(lpCurPlayer->dwObjectSerial);

	return TRUE;
}





#define	_CHANGE_JOB_COUNT_MAX		FACE_MODEL_MAX
#define	_FACE_COUNT_MAX				HEAREPOTION_MAX


int	CheckUserModel(smCHAR_INFO *lpCharInfo)
{
	int cnt, cnt2, len;
	char	szBuff[64];
	char	*lpBuff;


	lpCharInfo->szModelName[31] = 0;
	lpCharInfo->szModelName2[31] = 0;

	len = lstrlen(lpCharInfo->szModelName);
	strcpy_s(szBuff, lpCharInfo->szModelName);
	for(cnt = len - 1; cnt >= 0; cnt--)
	{
		if(szBuff[cnt] == '\\')
		{
			szBuff[cnt + 1] = 0;
			break;
		}
	}

	if(lstrcmpi(szBuff, "char\\tmABCD\\") != 0) return FALSE;
	lpBuff = &lpCharInfo->szModelName[len - 3];
	if(lstrcmpi(lpBuff, "ini") != 0) return FALSE;


	switch(lpCharInfo->JOB_CODE)
	{
	case 0:
		return TRUE;

	case JOBCODE_FIGHTER:
		for(cnt = 0; cnt < _CHANGE_JOB_COUNT_MAX; cnt++)
		{
			for(cnt2 = 0; cnt2 < _FACE_COUNT_MAX; cnt2++)
			{
				if(lstrcmpi(szModel_FighterFaceName[cnt][cnt2], lpCharInfo->szModelName2) == 0)
				{
					return TRUE;
				}
			}
		}
		if(!lpCharInfo->szModelName2[0])
		{

			strcpy_s(lpCharInfo->szModelName2, szModel_FighterFaceName[0][0]);
			return TRUE;
		}
		break;
	case JOBCODE_MECHANICIAN:
		for(cnt = 0; cnt < _CHANGE_JOB_COUNT_MAX; cnt++)
		{
			for(cnt2 = 0; cnt2 < _FACE_COUNT_MAX; cnt2++)
			{
				if(lstrcmpi(szModel_MechFaceName[cnt][cnt2], lpCharInfo->szModelName2) == 0)
				{
					return TRUE;
				}
			}
		}
		if(!lpCharInfo->szModelName2[0])
		{

			strcpy_s(lpCharInfo->szModelName2, szModel_MechFaceName[0][0]);
			return TRUE;
		}
		break;
	case JOBCODE_ARCHER:
		for(cnt = 0; cnt < _CHANGE_JOB_COUNT_MAX; cnt++)
		{
			for(cnt2 = 0; cnt2 < _FACE_COUNT_MAX; cnt2++)
			{
				if(lstrcmpi(szModel_ArcherFaceName[cnt][cnt2], lpCharInfo->szModelName2) == 0)
				{
					return TRUE;
				}
			}
		}
		if(!lpCharInfo->szModelName2[0])
		{

			strcpy_s(lpCharInfo->szModelName2, szModel_ArcherFaceName[0][0]);
			return TRUE;
		}

		break;
	case JOBCODE_PIKEMAN:
		for(cnt = 0; cnt < _CHANGE_JOB_COUNT_MAX; cnt++)
		{
			for(cnt2 = 0; cnt2 < _FACE_COUNT_MAX; cnt2++)
			{
				if(lstrcmpi(szModel_PikeFaceName[cnt][cnt2], lpCharInfo->szModelName2) == 0)
				{
					return TRUE;
				}
			}
		}
		if(!lpCharInfo->szModelName2[0])
		{

			strcpy_s(lpCharInfo->szModelName2, szModel_PikeFaceName[0][0]);
			return TRUE;
		}
		break;
	case JOBCODE_ATALANTA:
		for(cnt = 0; cnt < _CHANGE_JOB_COUNT_MAX; cnt++)
		{
			for(cnt2 = 0; cnt2 < _FACE_COUNT_MAX; cnt2++)
			{
				if(lstrcmpi(szModel_AtalantaFaceName[cnt][cnt2], lpCharInfo->szModelName2) == 0)
				{
					return TRUE;
				}
			}
		}
		if(!lpCharInfo->szModelName2[0])
		{

			strcpy_s(lpCharInfo->szModelName2, szModel_AtalantaFaceName[0][0]);
			return TRUE;
		}
		break;
	case JOBCODE_KNIGHT:
		for(cnt = 0; cnt < _CHANGE_JOB_COUNT_MAX; cnt++)
		{
			for(cnt2 = 0; cnt2 < _FACE_COUNT_MAX; cnt2++)
			{
				if(lstrcmpi(szModel_KnightFaceName[cnt][cnt2], lpCharInfo->szModelName2) == 0)
				{
					return TRUE;
				}
			}
		}
		if(!lpCharInfo->szModelName2[0])
		{

			strcpy_s(lpCharInfo->szModelName2, szModel_KnightFaceName[0][0]);
			return TRUE;
		}
		break;
	case JOBCODE_MAGICIAN:
		for(cnt = 0; cnt < _CHANGE_JOB_COUNT_MAX; cnt++)
		{
			for(cnt2 = 0; cnt2 < _FACE_COUNT_MAX; cnt2++)
			{
				if(lstrcmpi(szModel_MagicanFaceName[cnt][cnt2], lpCharInfo->szModelName2) == 0)
				{
					return TRUE;
				}
			}
		}
		if(!lpCharInfo->szModelName2[0])
		{

			strcpy_s(lpCharInfo->szModelName2, szModel_MagicanFaceName[0][0]);
			return TRUE;
		}
		break;
	case JOBCODE_PRIESTESS:
		for(cnt = 0; cnt < _CHANGE_JOB_COUNT_MAX; cnt++)
		{
			for(cnt2 = 0; cnt2 < _FACE_COUNT_MAX; cnt2++)
			{
				if(lstrcmpi(szModel_PristessFaceName[cnt][cnt2], lpCharInfo->szModelName2) == 0)
				{
					return TRUE;
				}
			}
		}
		if(!lpCharInfo->szModelName2[0])
		{

			strcpy_s(lpCharInfo->szModelName2, szModel_PristessFaceName[0][0]);
			return TRUE;
		}
		break;
	case JOBCODE_ASSASSINE:
		for (cnt = 0; cnt < _CHANGE_JOB_COUNT_MAX; cnt++)
		{
			for (cnt2 = 0; cnt2 < _FACE_COUNT_MAX; cnt2++)
			{
				if (lstrcmpi(szModel_AssassineFaceName[cnt][cnt2], lpCharInfo->szModelName2) == 0)
				{
					return TRUE;
				}
			}
		}
		if (!lpCharInfo->szModelName2[0])
		{

			lstrcpy(lpCharInfo->szModelName2, szModel_AssassineFaceName[0][0]);
			return TRUE;
		}
		break;
	case JOBCODE_SHAMAN:
		for (cnt = 0; cnt < _CHANGE_JOB_COUNT_MAX; cnt++)
		{
			for (cnt2 = 0; cnt2 < _FACE_COUNT_MAX; cnt2++)
			{
				if (lstrcmpi(szModel_ShamanFaceName[cnt][cnt2], lpCharInfo->szModelName2) == 0)
				{
					return TRUE;
				}
			}
		}
		if (!lpCharInfo->szModelName2[0])
		{

			lstrcpy(lpCharInfo->szModelName2, szModel_ShamanFaceName[0][0]);
			return TRUE;
		}
		break;
	}

	return FALSE;
}



int ChangeJobFace()
{
	int cnt1;


	cnt1 = 0;

	StartSkill(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, SKILL_UP1);
	SkillPlaySound(SKILL_SOUND_LEARN, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);

	CheckCharForm();


	ChangeModelSkin(lpCurPlayer, 0, lpCurPlayer->smCharInfo.ChangeJob, 0, 0);
	lpCurPlayer->smCharInfo.bUpdateInfo[0]++;
	ReformCharForm();
	SendSetObjectSerial(lpCurPlayer->dwObjectSerial);

	return FALSE;
}




#define	TIME_EFFECT_BUFF_MAX	16

struct sTIME_EFFECT_BUFF
{
	DWORD	dwCode;
	DWORD	dwTime;
	int		x, y, z;
	smCHAR	*lpChar;
};

sTIME_EFFECT_BUFF TimeEffectBuff[TIME_EFFECT_BUFF_MAX];


int InitTimeEffect()
{
	int cnt;
	for(cnt = 0; cnt < TIME_EFFECT_BUFF_MAX; cnt++)
	{
		TimeEffectBuff[cnt].dwCode = 0;
	}

	return TRUE;
}


int AddTimeEffect(DWORD EffectCode, DWORD dwTime, int x, int y, int z, smCHAR *lpChar)
{
	int cnt;
	for(cnt = 0; cnt < TIME_EFFECT_BUFF_MAX; cnt++)
	{
		if(!TimeEffectBuff[cnt].dwCode)
		{
			TimeEffectBuff[cnt].dwCode = EffectCode;
			TimeEffectBuff[cnt].dwTime = dwTime;
			TimeEffectBuff[cnt].x = x;
			TimeEffectBuff[cnt].y = y;
			TimeEffectBuff[cnt].z = z;
			TimeEffectBuff[cnt].lpChar = lpChar;
			return TRUE;
		}
	}
	return FALSE;
}

int AddTimeEffect(DWORD EffectCode, DWORD dwTime, int x, int y, int z)
{
	return AddTimeEffect(EffectCode, dwTime, x, y, z, 0);
}


int TimeEffectMain()
{
	int cnt;
	for(cnt = 0; cnt < TIME_EFFECT_BUFF_MAX; cnt++)
	{
		if(TimeEffectBuff[cnt].dwCode && TimeEffectBuff[cnt].dwTime < dwPlayTime)
		{

			switch(TimeEffectBuff[cnt].dwCode)
			{
			case SKILL_RAGE_OF_ZECRAM_HIT2:

				StartSkill(TimeEffectBuff[cnt].x, TimeEffectBuff[cnt].y, TimeEffectBuff[cnt].z, 0, 0, 0, SKILL_RAGE_OF_ZECRAM_HIT2);
				SkillPlaySound(SKILL_SOUND_SKILL_RAGE_OF_ZECRAM2, TimeEffectBuff[cnt].x, TimeEffectBuff[cnt].y, TimeEffectBuff[cnt].z);
				SetDynLight(TimeEffectBuff[cnt].x, TimeEffectBuff[cnt].y, TimeEffectBuff[cnt].z, 100, 0, 0, 0, 500);
				break;

			case OpCode::OPCODE_SUCCESS_EVATION:

				cInterFace.SetStringEffect(HA_EVASION);
				break;

			case OpCode::OPCODE_SUCCESS_DEFENSE:

				cInterFace.SetStringEffect(HA_DEFANCE);
				break;

			case SKILL_EFFECT_FIREFLOWER:
				if(TimeEffectBuff[cnt].lpChar && TimeEffectBuff[cnt].lpChar->Flag)
				{
					ParkAssaParticle_FireCracker(TimeEffectBuff[cnt].lpChar, TimeEffectBuff[cnt].x);
					esPlaySound(23 + (rand() % 3), GetDistVolume(TimeEffectBuff[cnt].lpChar->pX, TimeEffectBuff[cnt].lpChar->pY, TimeEffectBuff[cnt].lpChar->pZ));
				}
				break;
			}

			TimeEffectBuff[cnt].dwCode = 0;
		}
	}
	return TRUE;
}

#define		ROT_PLAYER_MAX		128
#define		ROT_PLAYER_MIN		80

smCHAR	*lpChrPlayers[ROT_PLAYER_MAX];



smCHAR *InitRotPlayer()
{
	int cnt;
	for(cnt = 0; cnt < ROT_PLAYER_MAX; cnt++)
		lpChrPlayers[cnt] = 0;

	return SelectRotPlayer(0);
}


int	CloseRotPlayer()
{
	for(int cnt = 0; cnt < ROT_PLAYER_MAX; cnt++)
	{
		if(lpChrPlayers[cnt])
		{
			delete	lpChrPlayers[cnt];
			lpChrPlayers[cnt] = nullptr;
		}
	}

	return TRUE;
}


smCHAR *SelectRotPlayer(smCHAR *lpCurrentChar)
{
	int rnd;
	smCHAR *lpChar;

	rnd = rand() % ROT_PLAYER_MIN;
	lpChar = lpChrPlayers[rnd];
	if(!lpChar)
	{
		lpChar = new smCHAR;
		lpChrPlayers[rnd] = lpChar;
	}

	if(!lpChar) return NULL;


	if(lpCurrentChar && lpCurrentChar != lpChar)
	{
		memcpy(lpChar, lpCurrentChar, sizeof(smCHAR));
	}

	if(!lpCurrentChar && lpChar)
	{
		ZeroMemory(lpChar, sizeof(smCHAR));
	}

	return lpChar;
}






int	PlaySub_EndFunc()
{


	return TRUE;
}




int	Check_PlaySubReleaseFunc()
{
	DWORD	dwStartFunc;
	DWORD	dwEndFunc;
	DWORD	*lpStartFunc;
	int		cnt, len;
	DWORD	dwChkSum;

	dwStartFunc = (DWORD)Code_VRamBuffOpen;
	dwEndFunc = (DWORD)Check_PlaySubReleaseFunc;
	len = (dwEndFunc - dwStartFunc) >> 2;

	dwChkSum = 0;

	lpStartFunc = (DWORD *)dwStartFunc;

	if(len < 0) return FALSE;

	for(cnt = 0; cnt < len; cnt++)
	{
		dwChkSum += (lpStartFunc[cnt] * ((cnt & 0x3FF) + 1));
	}

	dwPlaySub_CheckResult = dwChkSum;

	if(PLAYSUB_CHECKRESULT != dwChkSum)
	{

		return dwChkSum;
	}

	return NULL;
}



sCHK_POTION_COUNT	sPotionTotalCount;
int	tXorPotionCount = 0;


int	XorCheckPotion(sCHK_POTION_COUNT *ChkPotion)
{
	ChkPotion->Pl101 ^= tXorPotionCount;
	ChkPotion->Pl102 ^= tXorPotionCount;
	ChkPotion->Pl103 ^= tXorPotionCount;
	ChkPotion->Pl104 ^= tXorPotionCount;

	ChkPotion->Pm101 ^= tXorPotionCount;
	ChkPotion->Pm102 ^= tXorPotionCount;
	ChkPotion->Pm103 ^= tXorPotionCount;
	ChkPotion->Pm104 ^= tXorPotionCount;

	ChkPotion->Ps101 ^= tXorPotionCount;
	ChkPotion->Ps102 ^= tXorPotionCount;
	ChkPotion->Ps103 ^= tXorPotionCount;
	ChkPotion->Ps104 ^= tXorPotionCount;

	return TRUE;
}


int	ComparePotion()
{
	sCHK_POTION_COUNT	ChkPotionCount;
	int	CompareError = 0;

	XorCheckPotion(&sPotionTotalCount);

	GetInvenPotionCount(&ChkPotionCount);

	if(ChkPotionCount.Pl101 > sPotionTotalCount.Pl101)
		CompareError++;
	if(ChkPotionCount.Pl102 > sPotionTotalCount.Pl102)
		CompareError++;
	if(ChkPotionCount.Pl103 > sPotionTotalCount.Pl103)
		CompareError++;
	if(ChkPotionCount.Pl104 > sPotionTotalCount.Pl104)
		CompareError++;

	if(ChkPotionCount.Pm101 > sPotionTotalCount.Pm101)
		CompareError++;
	if(ChkPotionCount.Pm102 > sPotionTotalCount.Pm102)
		CompareError++;
	if(ChkPotionCount.Pm103 > sPotionTotalCount.Pm103)
		CompareError++;
	if(ChkPotionCount.Pm104 > sPotionTotalCount.Pm104)
		CompareError++;

	if(ChkPotionCount.Ps101 > sPotionTotalCount.Ps101)
		CompareError++;
	if(ChkPotionCount.Ps102 > sPotionTotalCount.Ps102)
		CompareError++;
	if(ChkPotionCount.Ps103 > sPotionTotalCount.Ps103)
		CompareError++;
	if(ChkPotionCount.Ps104 > sPotionTotalCount.Ps104)
		CompareError++;

	int cnt1, cnt2;
	cnt1 = ChkPotionCount.Pl101 + ChkPotionCount.Pl102 + ChkPotionCount.Pl103 + ChkPotionCount.Pl104 +
		ChkPotionCount.Pm101 + ChkPotionCount.Pm102 + ChkPotionCount.Pm103 + ChkPotionCount.Pm104 +
		ChkPotionCount.Ps101 + ChkPotionCount.Ps102 + ChkPotionCount.Ps103 + ChkPotionCount.Ps104;

	cnt2 = sPotionTotalCount.Pl101 + sPotionTotalCount.Pl102 + sPotionTotalCount.Pl103 + sPotionTotalCount.Pl104 +
		sPotionTotalCount.Pm101 + sPotionTotalCount.Pm102 + sPotionTotalCount.Pm103 + sPotionTotalCount.Pm104 +
		sPotionTotalCount.Ps101 + sPotionTotalCount.Ps102 + sPotionTotalCount.Ps103 + sPotionTotalCount.Ps104;

	if(CompareError)
	{


		SendSetHackUser3(1530, CompareError, cnt1 - cnt2);
	}

	tXorPotionCount = dwPlayTime & 0xFFFFFFF;
	memcpy(&sPotionTotalCount, &ChkPotionCount, sizeof(sCHK_POTION_COUNT));
	XorCheckPotion(&sPotionTotalCount);

	return CompareError;
}




int	ResetPotion()
{
	GetInvenPotionCount(&sPotionTotalCount);
	tXorPotionCount = dwPlayTime & 0xFFFFFFF;
	XorCheckPotion(&sPotionTotalCount);

	return TRUE;
}


int	ResetPotion2()
{
	int cnt1, cnt2;
	sCHK_POTION_COUNT	ChkPotionCount;

	XorCheckPotion(&sPotionTotalCount);
	GetInvenPotionCount(&ChkPotionCount);


	cnt1 = ChkPotionCount.Pl101 + ChkPotionCount.Pl102 + ChkPotionCount.Pl103 + ChkPotionCount.Pl104 +
		ChkPotionCount.Pm101 + ChkPotionCount.Pm102 + ChkPotionCount.Pm103 + ChkPotionCount.Pm104 +
		ChkPotionCount.Ps101 + ChkPotionCount.Ps102 + ChkPotionCount.Ps103 + ChkPotionCount.Ps104;

	cnt2 = sPotionTotalCount.Pl101 + sPotionTotalCount.Pl102 + sPotionTotalCount.Pl103 + sPotionTotalCount.Pl104 +
		sPotionTotalCount.Pm101 + sPotionTotalCount.Pm102 + sPotionTotalCount.Pm103 + sPotionTotalCount.Pm104 +
		sPotionTotalCount.Ps101 + sPotionTotalCount.Ps102 + sPotionTotalCount.Ps103 + sPotionTotalCount.Ps104;

	if(cnt1 > (cnt2 + TransRecvItem.Item.PotionCount))
		return TRUE;

	memcpy(&sPotionTotalCount, &ChkPotionCount, sizeof(sCHK_POTION_COUNT));
	tXorPotionCount = dwPlayTime & 0xFFFFFFF;
	XorCheckPotion(&sPotionTotalCount);

	return FALSE;
}


int	IncPotionCount(sCHK_POTION_COUNT *ChkPotion, sITEMINFO *lpItem)
{
	int	PotionCount;

	PotionCount = lpItem->PotionCount;

	if(!PotionCount) return FALSE;

	if(lpItem->CODE == (sinPL1 | sin01))
		ChkPotion->Pl101 += PotionCount;
	if(lpItem->CODE == (sinPL1 | sin02))
		ChkPotion->Pl102 += PotionCount;
	if(lpItem->CODE == (sinPL1 | sin03))
		ChkPotion->Pl103 += PotionCount;
	if(lpItem->CODE == (sinPL1 | sin04))
		ChkPotion->Pl104 += PotionCount;


	if(lpItem->CODE == (sinPM1 | sin01))
		ChkPotion->Pm101 += PotionCount;
	if(lpItem->CODE == (sinPM1 | sin02))
		ChkPotion->Pm102 += PotionCount;
	if(lpItem->CODE == (sinPM1 | sin03))
		ChkPotion->Pm103 += PotionCount;
	if(lpItem->CODE == (sinPM1 | sin04))
		ChkPotion->Pm104 += PotionCount;


	if(lpItem->CODE == (sinPS1 | sin01))
		ChkPotion->Ps101 += PotionCount;
	if(lpItem->CODE == (sinPS1 | sin02))
		ChkPotion->Ps102 += PotionCount;
	if(lpItem->CODE == (sinPS1 | sin03))
		ChkPotion->Ps103 += PotionCount;
	if(lpItem->CODE == (sinPS1 | sin04))
		ChkPotion->Ps104 += PotionCount;

	return TRUE;
}



int GetInvenPotionCount(sCHK_POTION_COUNT *ChkPotion)
{
	int cnt;

	ZeroMemory(ChkPotion, sizeof(sCHK_POTION_COUNT));

	for(cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if(cInvenTory.InvenItem[cnt].Flag)
		{
			IncPotionCount(ChkPotion, &cInvenTory.InvenItem[cnt].sItemInfo);
		}
	}

	for(cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if(cInvenTory.InvenItemTemp[cnt].Flag)
		{
			IncPotionCount(ChkPotion, &cInvenTory.InvenItemTemp[cnt].sItemInfo);
		}
	}

	if(cTrade.OpenFlag)
	{
		for(cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
		{
			if(sTrade.TradeItem[cnt].Flag)
			{
				IncPotionCount(ChkPotion, &sTrade.TradeItem[cnt].sItemInfo);
			}
		}
	}

	if(MouseItem.Flag)
		IncPotionCount(ChkPotion, &MouseItem.sItemInfo);

	return TRUE;
}

int	GetItemCheckCode(sITEMINFO *lpItem)
{
	if(lpItem->CODE < sinPM1 && lpItem->ItemName[0])
	{
		return lpItem->ItemHeader.dwChkSum;
	}
	return 0;
}



DWORD GetInvenItemCode()
{
	int cnt;

	DWORD	dwCode;


	dwCode = 0;

	for(cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if(cInvenTory.InvenItem[cnt].Flag)
		{
			dwCode += GetItemCheckCode(&cInvenTory.InvenItem[cnt].sItemInfo);
		}
	}

	for(cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if(cInvenTory.InvenItemTemp[cnt].Flag)
		{
			dwCode += GetItemCheckCode(&cInvenTory.InvenItemTemp[cnt].sItemInfo);
		}
	}

	if(cTrade.OpenFlag)
	{
		for(cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
		{
			if(sTrade.TradeItem[cnt].Flag)
			{
				dwCode += GetItemCheckCode(&sTrade.TradeItem[cnt].sItemInfo);
			}
		}
	}


	if(MouseItem.Flag)
	{
		dwCode += GetItemCheckCode(&MouseItem.sItemInfo);
	}

	if(cWareHouse.OpenFlag)
	{
		for(cnt = 0; cnt < 100; cnt++)
		{
			if(sWareHouse.WareHouseItem[cnt].Flag)
			{
				dwCode += GetItemCheckCode(&sWareHouse.WareHouseItem[cnt].sItemInfo);
			}
		}
	}

	if(cCraftItem.OpenFlag)
	{
		for(cnt = 0; cnt < 15; cnt++)
		{
			if(sCraftItem.CraftItem[cnt].Flag)
			{
				dwCode += GetItemCheckCode(&sCraftItem.CraftItem[cnt].sItemInfo);
			}
		}
	}

	if(cAging.OpenFlag)
	{
		for(cnt = 0; cnt < 15; cnt++)
		{
			if(sAgingItem.AgingItem[cnt].Flag)
			{
				dwCode += GetItemCheckCode(&sAgingItem.AgingItem[cnt].sItemInfo);
			}
		}
	}


	if(SmeltingItem.OpenFlag)
	{
		for(cnt = 0; cnt < 5; cnt++)
		{
			if(S_smeltingItem.SmeltingItem[cnt].Flag)
			{
				dwCode += GetItemCheckCode(&S_smeltingItem.SmeltingItem[cnt].sItemInfo);
			}
		}
	}


	if(ManufactureItem.m_OpenFlag)
	{
		for(cnt = 0; cnt < 4; cnt++)
		{
			if(g_sManufactureItem.ManufactureItem[cnt].Flag)
			{
				dwCode += GetItemCheckCode(&g_sManufactureItem.ManufactureItem[cnt].sItemInfo);
			}
		}
	}



	if(cMixtureReset.OpenFlag)
	{
		for(cnt = 0; cnt < 2; cnt++)
		{
			if(sMixtureResetItem.MixtureResetItem[cnt].Flag)
			{
				dwCode += GetItemCheckCode(&sMixtureResetItem.MixtureResetItem[cnt].sItemInfo);
			}
		}
	}

	return dwCode;
}


DWORD	dwTotal_InvenItemCode;
DWORD	dwTotal_InvenItemPlayTime;



int	ResetInvenItemCode()
{

	dwTotal_InvenItemCode = GetInvenItemCode();
	dwTotal_InvenItemCode = dwPlayTime^dwTotal_InvenItemCode;
	dwTotal_InvenItemPlayTime = dwPlayTime;

	return TRUE;
}


int SubInvenItemCode(sITEMINFO *lpItem)
{
	DWORD	dwCode;

	dwCode = dwTotal_InvenItemCode^dwTotal_InvenItemPlayTime;
	dwTotal_InvenItemCode = dwCode - GetItemCheckCode(lpItem);

	dwTotal_InvenItemCode = dwPlayTime^dwTotal_InvenItemCode;
	dwTotal_InvenItemPlayTime = dwPlayTime;

	return TRUE;
}



int	CheckInvenItemCode()
{
	DWORD dwCode;
	smTRANS_COMMAND	smTransCommand;

	dwCode = GetInvenItemCode();

	if(dwCode != (dwTotal_InvenItemCode^dwTotal_InvenItemPlayTime))
	{
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = OpCode::OPCODE_SET_BLACKLIST3;
		smTransCommand.WParam = 7010;
		smTransCommand.LParam = dwTotal_InvenItemCode^dwTotal_InvenItemPlayTime;
		smTransCommand.SParam = dwCode;
		if(smWsockDataServer)
		{
			smWsockDataServer->Send((char *)&smTransCommand, sizeof(smTRANS_COMMAND), TRUE);
		}
	}

	dwTotal_InvenItemCode = dwPlayTime^dwCode;
	dwTotal_InvenItemPlayTime = dwPlayTime;

	return TRUE;
}


void CheckPlaySubFunc2()
{
	if(dwPlaySub_CheckResult != PLAYSUB_CHECKRESULT)
	{
		SendSetHackUser2(1120, dwPlaySub_CheckResult);
		DisconnectFlag = dwPlayTime;
	}
}

short	sChkLife[2];
short	sChkMana[2];
short	sChkStamina[2];
int		EnergyGraphErrorCount[4] = { 0,0,0,0 };



int CheckEnergyGraphError()
{
	int Life, Mana, Stamina;
	smTRANS_COMMAND	smTransCommand;


	Life = EnergyGraphErrorCount[0] - EnergyGraphErrorCount[3];
	Mana = EnergyGraphErrorCount[1] - EnergyGraphErrorCount[3];
	Stamina = EnergyGraphErrorCount[2] - EnergyGraphErrorCount[3];



	if(Life > 0 || Mana > 0 || Stamina > 0)
	{
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = OpCode::OPCODE_CLIENT_ERROR;
		smTransCommand.WParam = 0;

		smTransCommand.LParam = Life;
		smTransCommand.SParam = Mana;
		smTransCommand.EParam = Stamina;

		if(smWsockDataServer)
			smWsockDataServer->Send((char *)&smTransCommand, smTransCommand.size, TRUE);
	}

	EnergyGraphErrorCount[3] = lpCurPlayer->pX;
	EnergyGraphErrorCount[0] = EnergyGraphErrorCount[3] + Life;
	EnergyGraphErrorCount[1] = EnergyGraphErrorCount[3] + Life;
	EnergyGraphErrorCount[2] = EnergyGraphErrorCount[3] + Life;

	return TRUE;
}


int	ResetEnergyGraph(int Num)
{
	int	Pos;

	Pos = lpCurPlayer->pZ;

	switch(Num)
	{
	case 0:

		sChkLife[0] = Pos;
		sChkLife[1] = Pos ^ (-1);
		break;

	case 1:

		sChkMana[0] = Pos;
		sChkMana[1] = Pos ^ (-1);
		break;

	case 2:

		sChkStamina[0] = Pos;
		sChkStamina[1] = Pos ^ (-1);
		break;

	case 3:
	case 4:

		sChkLife[0] = Pos;
		sChkLife[1] = Pos ^ (-1);
		sChkMana[0] = Pos;
		sChkMana[1] = Pos ^ (-1);
		sChkStamina[0] = Pos;
		sChkStamina[1] = Pos ^ (-1);
		break;

	}

	return TRUE;
}


int CheckEnergyGraph()
{
	int	Pos;
	int	Grp;
	int	Last_Grp;
	int cnt;

	Pos = lpCurPlayer->pZ;

	Last_Grp = sChkLife[0] ^ sChkLife[1];
	Grp = sinGetLife();
	if(Last_Grp != -1)
	{
		cnt = Grp - Last_Grp;
		if(cnt > 15)
		{
			EnergyGraphErrorCount[0] ++;
		}
	}
	sChkLife[0] = Pos;
	sChkLife[1] = Pos^Grp;

	Last_Grp = sChkMana[0] ^ sChkMana[1];
	Grp = sinGetMana();
	if(Last_Grp != -1)
	{
		cnt = Grp - Last_Grp;
		if(cnt > 15)
		{
			EnergyGraphErrorCount[1] ++;
		}
	}
	sChkMana[0] = Pos;
	sChkMana[1] = Pos^Grp;

	Last_Grp = sChkStamina[0] ^ sChkStamina[1];
	Grp = sinGetStamina();
	if(Last_Grp != -1)
	{
		cnt = Grp - Last_Grp;
		if(cnt > 50)
		{
			EnergyGraphErrorCount[2] ++;
		}
	}
	sChkStamina[0] = Pos;
	sChkStamina[1] = Pos^Grp;

	return TRUE;
}



sITEMINFO *FindInvenItem(DWORD dwItemCode, DWORD dwHead, DWORD dwChkSum)
{
	int cnt;
	sITEMINFO *lpItem;

	if((dwItemCode&sinITEM_MASK1) == (sinPM1&sinITEM_MASK1)) return NULL;

	for(cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if(cInvenTory.InvenItem[cnt].Flag)
		{
			lpItem = &cInvenTory.InvenItem[cnt].sItemInfo;
			if(lpItem->CODE == dwItemCode && lpItem->ItemHeader.Head == dwHead && lpItem->ItemHeader.dwChkSum == dwChkSum)
			{
				return lpItem;
			}
		}
	}

	for(cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if(cInvenTory.InvenItemTemp[cnt].Flag)
		{
			lpItem = &cInvenTory.InvenItemTemp[cnt].sItemInfo;
			if(lpItem->CODE == dwItemCode && lpItem->ItemHeader.Head == dwHead && lpItem->ItemHeader.dwChkSum == dwChkSum)
			{
				return lpItem;
			}
		}
	}

	if(cTrade.OpenFlag)
	{
		for(cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
		{
			if(sTrade.TradeItem[cnt].Flag)
			{
				lpItem = &sTrade.TradeItem[cnt].sItemInfo;
				if(lpItem->CODE == dwItemCode && lpItem->ItemHeader.Head == dwHead && lpItem->ItemHeader.dwChkSum == dwChkSum)
				{
					return lpItem;
				}
			}
		}
	}

	if(MouseItem.Flag)
	{
		lpItem = &MouseItem.sItemInfo;
		if(lpItem->CODE == dwItemCode && lpItem->ItemHeader.Head == dwHead && lpItem->ItemHeader.dwChkSum == dwChkSum)
		{
			return lpItem;
		}
	}

	if(cWareHouse.OpenFlag)
	{
		for(cnt = 0; cnt < 100; cnt++)
		{
			if(sWareHouse.WareHouseItem[cnt].Flag)
			{
				lpItem = &sWareHouse.WareHouseItem[cnt].sItemInfo;
				if(lpItem->CODE == dwItemCode && lpItem->ItemHeader.Head == dwHead && lpItem->ItemHeader.dwChkSum == dwChkSum)
				{
					return lpItem;
				}
			}
		}
	}

	if(cCraftItem.OpenFlag)
	{
		for(cnt = 0; cnt < 15; cnt++)
		{
			if(sCraftItem.CraftItem[cnt].Flag)
			{
				lpItem = &sCraftItem.CraftItem[cnt].sItemInfo;
				if(lpItem->CODE == dwItemCode && lpItem->ItemHeader.Head == dwHead && lpItem->ItemHeader.dwChkSum == dwChkSum)
				{
					return lpItem;
				}
			}
		}
	}

	if(cAging.OpenFlag)
	{
		for(cnt = 0; cnt < 15; cnt++)
		{
			if(sAgingItem.AgingItem[cnt].Flag)
			{
				lpItem = &sAgingItem.AgingItem[cnt].sItemInfo;
				if(lpItem->CODE == dwItemCode && lpItem->ItemHeader.Head == dwHead && lpItem->ItemHeader.dwChkSum == dwChkSum)
				{
					return lpItem;
				}
			}
		}
	}

	if(SmeltingItem.OpenFlag)
	{
		for(cnt = 0; cnt < 5; cnt++)
		{
			if(S_smeltingItem.SmeltingItem[cnt].Flag)
			{
				lpItem = &S_smeltingItem.SmeltingItem[cnt].sItemInfo;
				if(lpItem->CODE == dwItemCode && lpItem->ItemHeader.Head == dwHead && lpItem->ItemHeader.dwChkSum == dwChkSum)
				{
					return lpItem;
				}
			}
		}
	}


	if(ManufactureItem.m_OpenFlag)
	{
		for(cnt = 0; cnt < 4; cnt++)
		{
			if(g_sManufactureItem.ManufactureItem[cnt].Flag)
			{
				lpItem = &g_sManufactureItem.ManufactureItem[cnt].sItemInfo;
				if(lpItem->CODE == dwItemCode && lpItem->ItemHeader.Head == dwHead && lpItem->ItemHeader.dwChkSum == dwChkSum)
				{
					return lpItem;
				}
			}
		}
	}


	if(cMixtureReset.OpenFlag)
	{
		for(cnt = 0; cnt < 2; cnt++)
		{
			if(sMixtureResetItem.MixtureResetItem[cnt].Flag)
			{
				lpItem = &sMixtureResetItem.MixtureResetItem[cnt].sItemInfo;
				if(lpItem->CODE == dwItemCode && lpItem->ItemHeader.Head == dwHead && lpItem->ItemHeader.dwChkSum == dwChkSum)
					return lpItem;
			}
		}
	}

	return NULL;
}


int SendInvenItemError(DWORD dwKind, DWORD dwItemCode, DWORD dwHead, DWORD dwChkSum)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = OpCode::OPCODE_INVEN_ERR_ITEM;
	smTransCommand.WParam = dwKind;

	smTransCommand.LParam = dwItemCode;
	smTransCommand.SParam = dwHead;
	smTransCommand.EParam = dwChkSum;

	if(smWsockDataServer)
		smWsockDataServer->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

	return TRUE;
}

int	GetTotalInvenMoney()
{
	int Money;

	Money = lpCurPlayer->smCharInfo.Money;

	if(cTrade.OpenFlag && sTrade.Money)
		Money += sTrade.Money - 193;

	if(cWareHouse.OpenFlag)
		Money += sWareHouse.Money - 2023;

	return Money;
}

DWORD	dwTotal_CheckMoney = 0;
DWORD	dwTotal_CheckMoneyTime = 0;
#define	TOTAL_CHECK_MONEY_MASK	0x0018cccc
int		NChkMode = 0;



int	ResetInvenMoney()
{
	dwTotal_CheckMoney = GetTotalInvenMoney();
	dwTotal_CheckMoney = dwPlayTime^dwTotal_CheckMoney;
	dwTotal_CheckMoneyTime = dwPlayTime^TOTAL_CHECK_MONEY_MASK;

	return TRUE;
}



int	AddInvenMoney(int Money)
{
	int	m;

	m = dwTotal_CheckMoney ^ (dwTotal_CheckMoneyTime^TOTAL_CHECK_MONEY_MASK);
	m += Money;
	if(m < 0) m = 0;

	dwTotal_CheckMoney = dwPlayTime^m;
	dwTotal_CheckMoneyTime = dwPlayTime^TOTAL_CHECK_MONEY_MASK;

	return TRUE;
}


int	CheckInvenMoney()
{
	DWORD dwCode;
	smTRANS_COMMAND	smTransCommand;

	if(cShop.OpenFlag || SkillMasterFlag || cCraftItem.OpenFlag || cAging.OpenFlag || SmeltingItem.OpenFlag || ManufactureItem.m_OpenFlag || cMixtureReset.OpenFlag)
	{
		NChkMode = TRUE;
		return TRUE;
	}

	if(NChkMode)
	{
		NChkMode = 0;
		ResetInvenMoney();
		if(NChkMode == 0) return TRUE;
		dwCode = 0;
	}
	else
	{
		dwCode = GetTotalInvenMoney();
	}

	if(dwCode != (dwTotal_CheckMoney ^ (dwTotal_CheckMoneyTime^TOTAL_CHECK_MONEY_MASK)))
	{
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = OpCode::OPCODE_INVEN_ERR_MONEY;
		smTransCommand.WParam = 0;
		smTransCommand.LParam = dwCode;
		smTransCommand.SParam = (dwTotal_CheckMoney ^ (dwTotal_CheckMoneyTime^TOTAL_CHECK_MONEY_MASK));
		smTransCommand.EParam = 0;
		if(smWsockDataServer)
		{
			smWsockDataServer->Send((char *)&smTransCommand, sizeof(smTRANS_COMMAND), TRUE);
		}
	}

	dwTotal_CheckMoney = dwPlayTime^dwCode;
	dwTotal_CheckMoneyTime = dwPlayTime^TOTAL_CHECK_MONEY_MASK;

	return TRUE;
}




int SendUsingItemListToServer()
{

	int cnt;
	sITEMINFO *lpItem;

	TRANS_USINGITEM	TransUsingItem;

	ZeroMemory(&TransUsingItem, sizeof(TRANS_USINGITEM));

	TransUsingItem.size = sizeof(TRANS_USINGITEM);
	TransUsingItem.code = OpCode::OPCODE_INVEN_POSITION;

	for(cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if(cInvenTory.InvenItem[cnt].Flag && cInvenTory.InvenItem[cnt].ItemPosition)
		{
			lpItem = &cInvenTory.InvenItem[cnt].sItemInfo;
			if(lpItem->ItemName[0])
			{
				if(TransUsingItem.ItemListCount >= 16) break;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].dwCode = lpItem->CODE;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[0] = cInvenTory.InvenItem[cnt].ItemPosition;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[1] = lpItem->Damage[1];
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[2] = lpItem->Defence;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[3] = (short)lpItem->fBlock_Rating;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[4] = (short)lpItem->fAbsorb;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[5] = lpItem->Attack_Rating;
				TransUsingItem.ItemListCount++;
			}
		}
	}

	for(cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if(cInvenTory.InvenItemTemp[cnt].Flag && cInvenTory.InvenItemTemp[cnt].ItemPosition)
		{
			lpItem = &cInvenTory.InvenItemTemp[cnt].sItemInfo;
			if(lpItem->ItemName[0])
			{
				if(TransUsingItem.ItemListCount >= 16) break;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].dwCode = lpItem->CODE;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[0] = cInvenTory.InvenItemTemp[cnt].ItemPosition | 0x100;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[1] = lpItem->Damage[1];
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[2] = lpItem->Defence;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[3] = (short)lpItem->fBlock_Rating;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[4] = (short)lpItem->fAbsorb;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[5] = lpItem->Attack_Rating;
				TransUsingItem.ItemListCount++;
			}
		}
	}

	smWINSOCK	*lpsmSendSock;

	lpsmSendSock = GetAreaServerSock();
	if(lpsmSendSock)
	{
		return lpsmSendSock->Send((char *)&TransUsingItem, TransUsingItem.size, TRUE);
	}

	return NULL;
}


int SendUsingItemListToServer2()
{

	int cnt;
	sITEMINFO *lpItem;

	TRANS_USINGITEM	TransUsingItem;

	ZeroMemory(&TransUsingItem, sizeof(TRANS_USINGITEM));

	TransUsingItem.size = sizeof(TRANS_USINGITEM);
	TransUsingItem.code = OpCode::OPCODE_INVEN_POSITION2;

	for(cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if(cInvenTory.InvenItem[cnt].Flag && cInvenTory.InvenItem[cnt].ItemPosition)
		{
			lpItem = &cInvenTory.InvenItem[cnt].sItemInfo;
			if(lpItem->ItemName[0])
			{
				if(TransUsingItem.ItemListCount >= 16) break;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].dwCode = lpItem->CODE;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[0] = cInvenTory.InvenItem[cnt].ItemPosition;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[1] = lpItem->Damage[1];
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[2] = lpItem->Defence;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[3] = (short)lpItem->fBlock_Rating;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[4] = (short)lpItem->fAbsorb;
				TransUsingItem.ItemList[TransUsingItem.ItemListCount].Performance[5] = lpItem->Attack_Rating;
				TransUsingItem.ItemListCount++;
			}
		}
	}

	smWINSOCK	*lpsmSendSock;

	lpsmSendSock = GetAreaServerSock();
	if(lpsmSendSock)
	{
		return lpsmSendSock->Send((char *)&TransUsingItem, TransUsingItem.size, TRUE);
	}

	return NULL;
}



DWORD	GetPlayTime_T()
{
	DWORD dwTime;

	if(dwTime_ServerT)
	{
		dwTime = (dwPlayTime - dwTime_ConnectMS) / 1000;
		dwTime = dwTime_ServerT + dwTime;
		return dwTime;
	}

	return NULL;
}



int	ChangeBigHeadMode(int Mode, int Time)
{
	DWORD	dwTime;

	if(Mode)
	{
		if(Mode == 3)
		{
			lpCurPlayer->smCharInfo.SizeLevel = 1;
			ChangeModelSkin(lpCurPlayer, 0, 6, 0, 0);
		}
		else
		{
			lpCurPlayer->smCharInfo.SizeLevel = Mode + 0x1000;
			ChangeModelSkin(lpCurPlayer, 1, lpCurPlayer->smCharInfo.SizeLevel + 3 - 0x1000, 0, 0);
		}
		dwTime = GetPlayTime_T();

		if(dwTime)
			lpCurPlayer->smCharInfo.dwEventTime_T = dwTime + Time;
		else
			lpCurPlayer->smCharInfo.dwEventTime_T = 0;
	}
	else
	{
		lpCurPlayer->smCharInfo.SizeLevel = 1;
		lpCurPlayer->smCharInfo.dwEventTime_T = 0;
		ChangeModelSkin(lpCurPlayer, 0, lpCurPlayer->smCharInfo.ChangeJob, 0, GetFaceHairSkin(lpCurPlayer));
	}

	lpCurPlayer->smCharInfo.bUpdateInfo[0]++;
	ReformCharForm();
	SendSetObjectSerial(lpCurPlayer->dwObjectSerial);

	if(RestartPlayCount < 350) RestartPlayCount = 350;

	return TRUE;
}


int GetAttackSpeedMainFrame(int AttackSpeed)
{
	int cnt;

	cnt = AttackSpeed - 6;
	if(cnt < 0) cnt = 0;
	if(cnt > 6) cnt = 6;

	return fONE + 32 * cnt;
}


int	GetAttackSpeedFrame(int AttackSpeed, int AddSpeed)
{
	int cnt;

	cnt = GetAttackSpeedMainFrame(AttackSpeed);
	if(AddSpeed < 6 && AddSpeed>0)
		cnt += AddSpeed * 32;

	return (80 * cnt) >> FLOATNS;
}


int	GetAttackSpeedFrame(int AttackSpeed)
{
	int cnt;

	cnt = GetAttackSpeedMainFrame(AttackSpeed);

	return (80 * cnt) >> FLOATNS;
}


int LoadFolder_Ini(char *szPath, char *szWildCard, char *szChgExt, int OftSave)
{
	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;
	char	szFindPath[64];
	char	szFilePath[64];
	char	*lpPath;

	HANDLE hFindHandle2;
	WIN32_FIND_DATA	fd2;
	char	szFindPath2[64];

	smDPAT	*lpDPatTest[65536];
	int		DPatCount = 0;
	int		cnt;

	strcpy_s(szFindPath, szPath);
	lstrcat(szFindPath, "\\*.*");

	hFindHandle = FindFirstFile(szFindPath, &fd);
	if(hFindHandle != INVALID_HANDLE_VALUE)
	{
		while(1)
		{
			if((fd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) != 0)
			{
				wsprintf(szFindPath2, "%s\\%s\\%s", szPath, fd.cFileName, szWildCard);

				hFindHandle2 = FindFirstFile(szFindPath2, &fd2);
				if(hFindHandle2 != INVALID_HANDLE_VALUE)
				{
					while(1)
					{
						wsprintf(szFilePath, "%s\\%s\\%s", szPath, fd.cFileName, fd2.cFileName);

						if(OftSave)
						{


							if(szChgExt)
								lpPath = ChangeFileExt(szFilePath, szChgExt);
							else
								lpPath = 0;

							if(!lpPath)
								lpPath = szFilePath;

							strcpy_s(szFilePath, lpPath);

							LoadOftenMeshPattern(szFilePath);
						}
						else
						{

							lpDPatTest[DPatCount] = smPattern.LoadCharactor(szFilePath);
							if(lpDPatTest[DPatCount]) DPatCount++;
							else
							{
								DPatCount = DPatCount;
							}
						}

						if(FindNextFile(hFindHandle2, &fd2) == FALSE)
							break;
					}
					FindClose(hFindHandle2);
				}
			}


			if(FindNextFile(hFindHandle, &fd) == FALSE)
				break;
		}
		FindClose(hFindHandle);
	}

	for(cnt = 0; cnt < DPatCount; cnt++)
	{
		smDPAT_Delete(lpDPatTest[cnt]);
	}

	return TRUE;
}

sSOD_SCORE	sSodScore;
int			SodScoreFlag = 0;
extern SBL_SetFontEffect SoD_SetFontEffect;




int	Sod_SodEffect(int Round)
{

	if(!BellatraEffectInitFlag) return FALSE;

	SetBellatraFontEffect(E_BL_FONT_ROUND);

	switch(Round)
	{
	case 1:
		SetBellatraFontEffect(E_BL_FONT_COUNT_1);
		break;
	case 2:
		SetBellatraFontEffect(E_BL_FONT_COUNT_2);
		break;
	case 3:
		SetBellatraFontEffect(E_BL_FONT_COUNT_3);
		break;
	case 4:
		SetBellatraFontEffect(E_BL_FONT_COUNT_4);
		break;
	case 5:
		SetBellatraFontEffect(E_BL_FONT_COUNT_5);
		break;
	case 6:
		SetBellatraFontEffect(E_BL_FONT_COUNT_6);
		break;
	case 7:
		SetBellatraFontEffect(E_BL_FONT_COUNT_7);
		break;
	case 8:
		SetBellatraFontEffect(E_BL_FONT_COUNT_8);
		break;
	}
	SetBellatraFontEffect(E_BL_FONT_START);

	esPlayContSound(Round);



	return TRUE;
}



SBL_SetFontEffect SoD_SetFontEffect_CloseScreen;
char	szSOD_String[64] = { 0, };
BYTE	bSOD_StringColor[4];
int		SOD_StringCount = 0;
int		TeamScoreSort[4];
int		TeamMarkSort[4] = { 3 , 0 , 2 , 1 };
int		SoDGateFlag;





int	SetSodScoreResult()
{
	int cnt;

	g_EventScore.TeamNum = 0;
	g_EventScore.EntryTeamNum = 0;

	for(cnt = 0; cnt < 4; cnt++)
	{
		g_EventScore.TeamMarkBuff[cnt] = TeamMarkSort[TeamScoreSort[cnt]];
		wsprintf(g_EventScore.szTeamPointBuff[cnt], "%d", sSodScore.TeamScore[TeamScoreSort[cnt]]);
	}
	for(cnt = 0; cnt < 2; cnt++)
	{
		g_EventScore.EntryTeamMarkBuff[cnt] = g_EventScore.TeamMarkBuff[cnt];
	}

	if(sSodScore.Round > 0 && sSodScore.Round <= 4)
	{
		g_EventScore.TeamNum = 4;
		g_EventScore.EntryTeamNum = 2;
	}
	if(sSodScore.Round > 4 && sSodScore.Round <= 6)
	{
		g_EventScore.TeamNum = 2;
		g_EventScore.EntryTeamNum = 1;
	}

	if(!g_EventScore.TeamNum) return FALSE;

	return TRUE;
}



int	SodScoreMain()
{
	int dx, dy, dz;
	int x, z, cnt;




	if(!SodScoreFlag)
	{
		SodScoreFlag = TRUE;
		ZeroMemory(&sSodScore, sizeof(sSOD_SCORE));
	}

	if(SOD_StringCount) SOD_StringCount--;


	if(sSodScore.dwSoD_NextStageTime)
	{

		if(sSodScore.dwSoD_CloseStageTime && sSodScore.dwSoD_CloseStageTime < dwPlayTime)
		{

			if(SoD_SetFontEffect_CloseScreen.eBL_Type != E_BL_CHANGE_TRUE)
			{

				if(SoDGateFlag == TRUE && SetSodScoreResult() == TRUE)
					SetBellatraFontEffect(E_BL_CHANGE_TRUE, &SoD_SetFontEffect_CloseScreen, E_BL_EVENT_SCORE);
				else
					SetBellatraFontEffect(E_BL_CHANGE_TRUE, &SoD_SetFontEffect_CloseScreen);


				esPlaySound(18, 400);
			}

			sSodScore.dwSoD_CloseStageTime = 0;
		}

		if(sSodScore.dwSoD_NextStageTime < dwPlayTime)
		{

			if(SoD_SetFontEffect_CloseScreen.eBL_Type == E_BL_CHANGE_TRUE)
			{
				CheckBellatraFontEffect(&SoD_SetFontEffect_CloseScreen, TRUE);
				SetBellatraFontEffect(E_BL_CHANGE_FALSE, &SoD_SetFontEffect_CloseScreen);
				esPlaySound(18, 400);
			}

			if(sSodScore.SodNextStageNum >= 0 && lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_DEAD)
			{
				if(rsCheckHardCoreEventArea(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ) == TRUE && sSodScore.SodNextStageNum < 100)
				{


					dx = rsHardCoreEventOpenPos[sSodScore.SodNextStageNum][2].x*fONE;
					dy = rsHardCoreEventOpenPos[sSodScore.SodNextStageNum][2].y*fONE;
					dz = rsHardCoreEventOpenPos[sSodScore.SodNextStageNum][2].z*fONE;

					CloseEachPlayer();

					WarpFieldNearPos(rsSOD_FIELD, dx, dz, &x, &z);

					lpCurPlayer->SetPosi(dx, 0, dz, 0, 0, 0);
					TraceCameraPosi.x = lpCurPlayer->pX;
					TraceCameraPosi.y = lpCurPlayer->pY;
					TraceCameraPosi.z = lpCurPlayer->pZ;
					TraceTargetPosi.x = lpCurPlayer->pX;
					TraceTargetPosi.y = lpCurPlayer->pY;
					TraceTargetPosi.z = lpCurPlayer->pZ;


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

					sSodScore.EffectStartCount = 70 * 1;
					sSodScore.EffectCode = sSodScore.NextRound;
				}
			}
			else if(sSodScore.SodNextStageNum == -1)
			{

				dx = sField[rsSOD_VILLAGE].cX*fONE;
				dz = sField[rsSOD_VILLAGE].cZ*fONE;

				CloseEachPlayer();

				WarpFieldNearPos(rsSOD_VILLAGE, dx, dz, &x, &z);

				lpCurPlayer->SetPosi(dx, 0, dz, 0, 0, 0);
				TraceCameraPosi.x = lpCurPlayer->pX;
				TraceCameraPosi.y = lpCurPlayer->pY;
				TraceCameraPosi.z = lpCurPlayer->pZ;
				TraceTargetPosi.x = lpCurPlayer->pX;
				TraceTargetPosi.y = lpCurPlayer->pY;
				TraceTargetPosi.z = lpCurPlayer->pZ;


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
			else if(sSodScore.SodNextStageNum == -2)
			{

				if(SoD_SetFontEffect.eBL_Type == E_BL_LODING)
				{
					CheckBellatraFontEffect(&SoD_SetFontEffect, TRUE);
				}
			}

			lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_STAND);
			lpCurPlayer->dwNextMotionCode = 0;
			sSodScore.dwSoD_NextStageTime = 0;
		}
		else
		{
			if(sSodScore.SodNextStageNum >= 0)
				lpCurPlayer->dwNextMotionCode = CHRMOTION_STATE_YAHOO;
		}

	}

	if(sSodScore.EffectStartCount)
	{
		sSodScore.EffectStartCount--;
		if(sSodScore.EffectStartCount == 0)
		{
			switch(sSodScore.EffectCode)
			{
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:

				Sod_SodEffect(sSodScore.EffectCode);
				break;
			}
		}
	}


	if(sSodScore.ScoreEffectCount)
	{
		sSodScore.ScoreEffectCount -= 8;
		if(sSodScore.ScoreEffectCount < 0)
			sSodScore.ScoreEffectCount = 0;
	}


	if(rsBlessCastle.CastleMode == 3)
	{
		if(rsBlessCastle.dwMasterClan && rsBlessCastle.dwMasterClan == GetClanCode(lpCurPlayer->smCharInfo.ClassClan))
		{
			if(!lpCurPlayer->dwNextMotionCode)
			{
				lpCurPlayer->dwNextMotionCode = CHRMOTION_STATE_YAHOO;
			}
		}
	}


	return TRUE;

}




int SodTeamSort()
{
	int cnt, cnt1;
	int r1, r2;

	for(cnt = 0; cnt < 4; cnt++) TeamScoreSort[cnt] = cnt;



	for(cnt = 0; cnt < 4; cnt++)
	{
		for(cnt1 = cnt; cnt1 < 4; cnt1++)
		{
			r1 = TeamScoreSort[cnt];
			r2 = TeamScoreSort[cnt1];

			if(sSodScore.TeamScore[r1] < sSodScore.TeamScore[r2])
			{
				TeamScoreSort[cnt] = r2;
				TeamScoreSort[cnt1] = r1;
			}
		}
	}

	return TRUE;
}


int	DisplaySodScore()
{
	char szBuff[256];
	int x, y;
	int cnt, cnt2;
	DWORD	dwColor;
	DWORD tM, tS;
	int len;
	int RnkCnt = 0;

	if(!SodScoreFlag)
	{
		SodScoreFlag = TRUE;
		ZeroMemory(&sSodScore, sizeof(sSOD_SCORE));
	}

	if(SOD_StringCount)
	{
		len = lstrlen(szSOD_String);
		if((SOD_StringCount & 0x8) == 0)
		{
			DrawFontImage(szSOD_String, MidX - len * 16, 330,
				D3DCOLOR_RGBA(bSOD_StringColor[0], bSOD_StringColor[1], bSOD_StringColor[2], 255), 2.0f);
		}
	}

	if(sSodScore.dwDispTime > dwPlayTime && rsCheckHardCoreEventArea(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ) == TRUE)
	{

		x = (WinSizeX / 2) - 80; y = 8;

		wsprintf(szBuff, "ROUND %d", sSodScore.Round);
		DrawFontImage(szBuff, x - 40, y, D3DCOLOR_RGBA(80, 255, 40, 255), 0.9f);

		if(sSodScore.dwPlayTime)
		{
			tM = (dwPlayTime - sSodScore.dwPlayTime) / 1000;
			tS = tM % 60;
			tM = tM / 60;
			if(tM > 99 || tM < 0) tM = 99;
		}
		else
		{
			tM = 0;
			tS = 0;
		}

		wsprintf(szBuff, "PlayTime %d:%d", tM, tS);
		DrawFontImage(szBuff, x + 160, y + 2, D3DCOLOR_RGBA(80, 160, 255, 255), 0.7f);

		y += 24;

		wsprintf(szBuff, "Score %d", sSodScore.Score);

		if(sSodScore.ScoreEffectCount)
			DrawFontImage(szBuff, x - 40, y + 8, D3DCOLOR_RGBA(255, 128, 64, 255 - sSodScore.ScoreEffectCount), 0.9f);
		else
			DrawFontImage(szBuff, x - 40, y + 8, D3DCOLOR_RGBA(255, 255, 0, 255), 0.9f);


		SodTeamSort();

		for(cnt = 0; cnt < 4; cnt++)
		{
			cnt2 = TeamScoreSort[cnt];

			if(sSodScore.MyTeam == cnt2)
				dwColor = D3DCOLOR_RGBA(255, 255, 0, 255);
			else
				dwColor = D3DCOLOR_RGBA(255, 128, 0, 255);

			DrawSpecialFontImage(TeamMarkSort[cnt2], x + 160, y, D3DCOLOR_RGBA(255, 255, 255, 255), 0.7f);

			wsprintf(szBuff, "Team %d", sSodScore.TeamScore[cnt2]);
			DrawFontImage(szBuff, x + 190, y, dwColor, 0.7f);
			y += 18;
		}
	}

	return FALSE;
}






