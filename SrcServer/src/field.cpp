

#include "smlib3d\\smd3d.h"

#include "smwsock.h"
#include "character.h"
#include "avictrl.h"
#include "playmain.h"
#include "fileread.h"

#include "particle.h"
#include "netplay.h"

#include "sinbaram\\sinlinkheader.h"

#include "field.h"
#include "effectsnd.h"
#include "Language\\language.h"

char szFieldDirectory[64];
char szMapDirectory[64];
char szTitleDirectory[64];
DWORD	dwWarpDelayTime = 0;
DWORD	dwNextWarpDelay = 0;
int		WingWarpField = -1;
sFIELD* lpLastWarpField = 0;



#ifdef _LANGUAGE_BRAZIL_FIELDLEVEL
int FieldLimitLevel_Table[] = {
	0,0,0,0,
	0,0,0,0,
	0,0,0,
	55,55,40,50,60,
	1000,
	0,0,0,0,0,
	70,75,
	55,55,65,
	80,85,90,0,90,0,
	0,70,90,90,
	95,100,1000,100,1000
};
#endif


int sFIELD::SetName(char* lpName, char* lpNameMap)
{
	strcpy_s(szName, szFieldDirectory);
	lstrcat(szName, lpName);

	if (lpNameMap)
	{
		wsprintf(szNameMap, "%s%s.tga", szMapDirectory, lpNameMap);
		wsprintf(szNameTitle, "%s%st.tga", szTitleDirectory, lpNameMap);
	}
	else
	{
		szNameMap[0] = 0;
		szNameTitle[0] = 0;
	}

	return TRUE;
}


int sFIELD::SetCenterPos(int x, int z)
{
	cX = x;
	cZ = z;
	return TRUE;
}


int	sFIELD::AddStageObject(char* szStgObjName, int BipAnimation)
{
	if (StgObjCount >= FIELD_STAGE_OBJ_MAX) return FALSE;

	lpStageObjectName[StgObjCount] = szStgObjName;
	StgObjBip[StgObjCount] = BipAnimation;

	StgObjCount++;

	return StgObjCount;
}


int	sFIELD::GetStageObjectName(int num, char* szNameBuff, size_t size)
{
	if (StgObjCount <= num)
	{
		szNameBuff[0] = 0;
		return FALSE;
	}

	strcpy_s(szNameBuff, size, szFieldDirectory);
	lstrcat(szNameBuff, lpStageObjectName[num]);

	return StgObjBip[num];
}

int sFIELD::AddGate(sFIELD* lpsField, int x, int z, int y)
{
	if (GateCount >= FILED_GATE_MAX) return FALSE;

	FieldGate[GateCount].x = x;
	FieldGate[GateCount].y = y;
	FieldGate[GateCount].z = z;
	FieldGate[GateCount].lpsField = lpsField;

	GateCount++;


	lpsField->AddGate2((sFIELD*)&head, x, z, y);

	return TRUE;
}

int sFIELD::AddGate2(sFIELD* lpsField, int x, int z, int y)
{
	if (GateCount >= FILED_GATE_MAX) return FALSE;

	FieldGate[GateCount].x = x;
	FieldGate[GateCount].y = y;
	FieldGate[GateCount].z = z;
	FieldGate[GateCount].lpsField = lpsField;

	GateCount++;

	return TRUE;
}



int sFIELD::AddWarpGate(int x, int z, int y, int size, int height)
{
	if (WarpGateCount >= FILED_GATE_MAX)
		return FALSE;

	WarpGateActiveNum = WarpGateCount;

	WarpGate[WarpGateCount].x = x << FLOATNS;
	WarpGate[WarpGateCount].y = y << FLOATNS;
	WarpGate[WarpGateCount].z = z << FLOATNS;
	WarpGate[WarpGateCount].height = height << FLOATNS;
	WarpGate[WarpGateCount].size = size << FLOATNS;

	WarpGate[WarpGateCount].OutGateCount = 0;

	WarpGateCount++;

	return WarpGateCount;
}


int	sFIELD::AddWarpOutGate(sFIELD* lpsField, int x, int z, int y)
{

	sWARPGATE* lpWarpGate;
	int		cnt;

	lpWarpGate = &WarpGate[WarpGateActiveNum];
	cnt = lpWarpGate->OutGateCount;

	if (cnt >= FILED_GATE_MAX) return FALSE;

	lpWarpGate->OutGate[cnt].lpsField = lpsField;
	lpWarpGate->OutGate[cnt].x = x << FLOATNS;
	lpWarpGate->OutGate[cnt].z = z << FLOATNS;
	lpWarpGate->OutGate[cnt].y = y << FLOATNS;

	lpWarpGate->OutGateCount++;

	if (lpsField == this)
	{
		PosWarpOut.x = x << FLOATNS;
		PosWarpOut.y = y << FLOATNS;
		PosWarpOut.z = z << FLOATNS;
	}

	return lpWarpGate->OutGateCount;
}


int	sFIELD::CheckWarpGate(int x, int y, int z)
{
	int cnt, rnd;
	int dx, dy, dz, dist;
	int	ddist;
	sWARPGATE* lpWarpGate;

	if (dwWarpDelayTime)
	{
		if ((dwWarpDelayTime + 3000) > dwPlayTime) return FALSE;
	}


	for (cnt = 0; cnt < WarpGateCount; cnt++)
	{
		lpWarpGate = &WarpGate[cnt];
		dx = (lpWarpGate->x - x) >> FLOATNS;
		dz = (lpWarpGate->z - z) >> FLOATNS;
		if (!lpWarpGate->y)
			dy = 0;
		else
			dy = abs(y - lpWarpGate->y);
		ddist = lpWarpGate->size >> FLOATNS;
		ddist *= ddist;

		dist = dx * dx + dz * dz;
		if (lpWarpGate->LimitLevel <= lpCurPlayer->smCharInfo.Level &&
			lpWarpGate->OutGateCount && abs(dx) < 1024 && abs(dz) < 1024 &&
			dist < ddist && dy < lpWarpGate->height)
		{

			lpLastWarpField = this;

			if (lpWarpGate->SpecialEffect && !dwNextWarpDelay)
			{

				dwNextWarpDelay = TRUE;

				lpCurPlayer->pX = lpWarpGate->x;
				lpCurPlayer->pY = lpWarpGate->y;
				lpCurPlayer->pZ = lpWarpGate->z;

				lpCurPlayer->MoveFlag = 0;
				CancelAttack();
				MouseButton[0] = 0;
				MouseButton[1] = 0;
				MouseButton[2] = 0;

				if (lpWarpGate->SpecialEffect == 2)
				{
					cSinWarpGate.SerchUseWarpGate();
					dwNextWarpDelay = TRUE;
					dwWarpDelayTime = 0xFFFF0000;
					return TRUE;
				}

				StartEffect(lpCurPlayer->pX, lpCurPlayer->pY + 48 * fONE, lpCurPlayer->pZ, EFFECT_RETURN1);
				SkillPlaySound(SKILL_SOUND_LEARN, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
				dwNextWarpDelay = TRUE;
				dwWarpDelayTime = dwPlayTime - 1000;
				return TRUE;
			}

			if (WingWarpField >= 0)
			{



				int x, z;
				int cnt = 0;


				if (WarpField(WingWarpField, &x, &z))
				{

					lpCurPlayer->SetPosi(sField[WingWarpField].PosWarpOut.x,
						sField[WingWarpField].PosWarpOut.y, sField[WingWarpField].PosWarpOut.z,
						lpCurPlayer->Angle.x, lpCurPlayer->Angle.y, lpCurPlayer->Angle.z);
				}

			}
			else
			{
				rnd = rand() % lpWarpGate->OutGateCount;

				LoadStageFromField(lpWarpGate->OutGate[rnd].lpsField, this);
				lpCurPlayer->SetPosi(lpWarpGate->OutGate[rnd].x,
					lpWarpGate->OutGate[rnd].y, lpWarpGate->OutGate[rnd].z,
					lpCurPlayer->Angle.x, lpCurPlayer->Angle.y, lpCurPlayer->Angle.z);

				if (!lpWarpGate->SpecialEffect)
					RestartPlayCount = 700;
			}

			TraceCameraPosi.x = lpCurPlayer->pX;
			TraceCameraPosi.y = lpCurPlayer->pY;
			TraceCameraPosi.z = lpCurPlayer->pZ;
			TraceTargetPosi.x = lpCurPlayer->pX;
			TraceTargetPosi.y = lpCurPlayer->pY;
			TraceTargetPosi.z = lpCurPlayer->pZ;

			dwWarpDelayTime = dwPlayTime;
			lpCurPlayer->MoveFlag = 0;
			CancelAttack();
			MouseButton[0] = 0;
			MouseButton[1] = 0;
			MouseButton[2] = 0;

			lpCurPlayer->OnStageField = -1;
			if (smGameStage[0])
			{
				rnd = smGameStage[0]->GetFloorHeight(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, lpCurPlayer->Pattern->SizeHeight);
				lpCurPlayer->OnStageField = 0;
			}
			if (rnd == CLIP_OUT && smGameStage[1])
			{
				lpCurPlayer->OnStageField = 1;
			}

			dwNextWarpDelay = 0;
			WingWarpField = -1;

			lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_STAND);

			return TRUE;
		}
	}

	return FALSE;
}


int sFIELD::AddStartPoint(int x, int z)
{
	if (StartPointCnt >= FIELD_START_POINT_MAX) return FALSE;

	StartPoint[StartPointCnt].x = x;
	StartPoint[StartPointCnt].y = z;
	StartPointCnt++;

	return TRUE;
}


int sFIELD::GetStartPoint(int x, int z, int* mx, int* mz)
{
	int cnt;
	int dist;
	int NearDist;
	int	NearCnt;
	int dx, dz;

	if (StartPointCnt == 0)
	{
		*mx = cX * fONE;
		*mz = cZ * fONE;
		return TRUE;
	}

	x >>= FLOATNS;
	z >>= FLOATNS;

	dx = (x - StartPoint[0].x);
	dz = (z - StartPoint[0].y);

	NearDist = dx * dx + dz * dz;
	NearCnt = 0;

	for (cnt = 1; cnt < StartPointCnt; cnt++)
	{
		dx = (x - StartPoint[cnt].x);
		dz = (z - StartPoint[cnt].y);
		dist = dx * dx + dz * dz;
		if (dist < NearDist)
		{
			NearDist = dist; NearCnt = cnt;
		}
	}

	*mx = StartPoint[NearCnt].x << FLOATNS;
	*mz = StartPoint[NearCnt].y << FLOATNS;

	return TRUE;
}


int sFIELD::CheckStartPoint(int x, int z)
{
	int cnt;
	int dx, dz;

	for (cnt = 0; cnt < StartPointCnt; cnt++)
	{
		dx = StartPoint[cnt].x << FLOATNS;
		dz = StartPoint[cnt].y << FLOATNS;

		if (abs(dx - x) < 24 * fONE && abs(dz - z) < 24 * fONE) return TRUE;
	}

	return FALSE;
}


int sFIELD::AddAmbientPos(int x, int y, int z, int round, int AmbCode)
{

	if (AmbentCount >= FIELD_AMBENT_MAX) return FALSE;

	AmbientPos[AmbentCount].x = x * fONE;
	AmbientPos[AmbentCount].y = y * fONE;
	AmbientPos[AmbentCount].z = z * fONE;
	AmbientPos[AmbentCount].round = round;
	AmbientPos[AmbentCount].AmbentNum = AmbCode;

	AmbentCount++;

	return AmbentCount;
}


int	sFIELD::PlayAmbient()
{
	int cnt;

	for (cnt = 0; cnt < AmbentCount; cnt++)
	{

		esPlayObjectSound2(AmbientPos[cnt].AmbentNum, AmbientPos[cnt].round, AmbientPos[cnt].x, AmbientPos[cnt].y, AmbientPos[cnt].z);
	}
	if (ResetLastVolumeDist() > 800)
	{
		esPlayObjectSound2(-1, 0, 0, 0, 0);
	}
	return TRUE;
}


sFIELD	sField[FIELD_MAX];
int FieldCount = 0;
int CustomField = 0;

static int SelCount = 0;



int InitField()
{
	int cnt;

	strcpy_s(szFieldDirectory, "field\\");
	strcpy_s(szMapDirectory, "field\\map\\");
	strcpy_s(szTitleDirectory, "field\\title\\");

	ZeroMemory(sField, sizeof(sFIELD) * FIELD_MAX);

	for (cnt = 0; cnt < FIELD_MAX; cnt++)
		sField[cnt].FieldCode = cnt;

	cnt = 0;


	sField[cnt].SetName("forest\\fore-3.ase", "fore-3");
	sField[cnt].State = FIELD_STATE_FOREST;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_DAY;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWDAY;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHT;
	sField[cnt].BackMusicCode = BGM_CODE_FOREST;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_MAIN;

	sField[cnt].AddStageObject("forest\\3ani-01.ASE");
	sField[cnt].AddStageObject("forest\\3ani-02.ASE");
	sField[cnt].AddStageObject("forest\\3ani-03.ASE");
	sField[cnt].AddStageObject("forest\\3ani-04.ASE");
	sField[cnt].AddStageObject("forest\\3ani-05.ASE");
	sField[cnt].AddStageObject("forest\\3ani-06.ASE");
	sField[cnt].AddStageObject("forest\\3ani-07.ASE");
	sField[cnt].AddStageObject("forest\\3ani-08.ASE");
	sField[cnt].AddStageObject("forest\\3ani-09.ASE");
	sField[cnt].AddStageObject("forest\\3ani-10.ASE");
	sField[cnt].AddStageObject("forest\\3ani-11.ASE");
	sField[cnt].AddStageObject("forest\\3ani-12.ASE");
	sField[cnt].AddStageObject("forest\\3ani-13.ASE");
	sField[cnt].AddStageObject("forest\\3ani-14.ASE");


	sField[cnt].SetCenterPos(-16419, -7054);
	sField[cnt].AddStartPoint(-10585, -11810);
	sField[cnt].AddStartPoint(-13659, -9753);

	sField[cnt].AddWarpGate(-16638, -6737, 267, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[24], 119112, 26028, 510);


	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = FieldLimitLevel_Table[cnt + 24];

	sField[cnt].AddGate(&sField[cnt + 1], -8508, -10576, 0);

	sField[cnt].AddAmbientPos(-13819, 226, -8950, 100, 15);


	cnt = 1;
	sField[cnt].SetName("forest\\fore-2.ase", "fore-2");
	sField[cnt].State = FIELD_STATE_FOREST;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_DAY;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWDAY;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHT;
	sField[cnt].BackMusicCode = BGM_CODE_FOREST;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_MAIN;




	sField[cnt].AddStageObject("forest\\2ani-04.ASE");


	sField[cnt].SetCenterPos(-5427, -9915);
	sField[cnt].AddStartPoint(-2272, -10314);
	sField[cnt].AddStartPoint(-7192, -11175);

	sField[cnt].AddGate(&sField[cnt + 1], -292, -9548, 0);

	sField[cnt].AddAmbientPos(-3775, 171, -14447, 160, 13);


	sField[cnt].AddWarpGate(-3408, -12447, 251, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt], -3265, -12583, 214);
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].SpecialEffect = 2;




	cnt = 2;
	sField[cnt].SetName("forest\\fore-1.ase", "fore-1");
	sField[cnt].State = FIELD_STATE_FOREST;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_DAY;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWDAY;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHT;
	sField[cnt].BackMusicCode = BGM_CODE_FOREST;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_MAIN;

	sField[cnt].SetCenterPos(4184, -11016);
	sField[cnt].AddStartPoint(1350, -13672);
	sField[cnt].AddStartPoint(1761, -10815);
	sField[cnt].AddStartPoint(4777, -10916);

	sField[cnt].AddGate(&sField[cnt + 2], 4844, -6835, 0);
	sField[cnt].AddGate(&sField[cnt + 1], 2275, -14828, 0);


	cnt = 3;
	sField[cnt].SetName("ricarten\\village-2.ase", "village-2");
	sField[cnt].State = FIELD_STATE_VILLAGE;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_DAY;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWDAY;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHT;
	sField[cnt].BackMusicCode = BGM_CODE_TOWN2;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_MAIN;

	sField[cnt].AddStageObject("ricarten\\v-ani01.ASE");
	sField[cnt].AddStageObject("ricarten\\v-ani02.ASE");
	sField[cnt].AddStageObject("ricarten\\v-ani03.ASE");
	sField[cnt].AddStageObject("ricarten\\v-ani04.ASE");
	sField[cnt].AddStageObject("ricarten\\v-ani05.ASE");
	sField[cnt].AddStageObject("ricarten\\v-ani06.ASE");
	sField[cnt].AddStageObject("ricarten\\v-ani07.ASE");
	sField[cnt].AddStageObject("ricarten\\v-ani08.ASE");
	sField[cnt].AddStageObject("ricarten\\v-ani09.ASE");
	sField[cnt].AddStageObject("ricarten\\v-ani10.ASE");
	sField[cnt].AddStageObject("ricarten\\v-ani11.ASE");
	sField[cnt].AddStageObject("ricarten\\v-ani12.ASE");
	sField[cnt].AddStageObject("ricarten\\v-ani13.ASE");
	sField[cnt].AddStageObject("ricarten\\v-ani14.ASE");

#ifdef	WORLDCUP_FIELD

	sField[cnt].AddStageObject("ricarten\\world_ani01.ASE");
	sField[cnt].AddStageObject("ricarten\\world_ani02.ASE");
	sField[cnt].AddStageObject("ricarten\\world_ani03.ASE");
	sField[cnt].AddStageObject("ricarten\\world_ani04.ASE");
	sField[cnt].AddStageObject("ricarten\\world_ani05.ASE");

#endif

	sField[cnt].SetCenterPos(2596, -18738);
	sField[cnt].AddStartPoint(2592, -18566);
	sField[cnt].AddStartPoint(-1047, -16973);


	sField[cnt].AddWarpGate(734, -20119, 312, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt], 822, -19956, 254);
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].SpecialEffect = 2;
	sField[cnt].AddAmbientPos(-1006, 170, -17835, 80, 27);
	sField[cnt].AddAmbientPos(2632, 321, -17285, 80, 27);


	cnt = 4;
	sField[cnt].SetName("Ruin\\ruin-4.ase", "ruin-4");
	sField[cnt].State = FIELD_STATE_RUIN;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_RUIN1;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWRUIN1;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHTRUIN1;
	sField[cnt].BackMusicCode = BGM_CODE_DESERT;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_MAIN;
	sField[cnt].SetCenterPos(1384, -918);
	sField[cnt].AddStartPoint(2578, -5124);
	sField[cnt].AddStartPoint(1873, 3060);
	sField[cnt].AddGate(&sField[cnt + 1], 410, 4902, 0);


	cnt = 5;
	sField[cnt].SetName("Ruin\\ruin-3.ase", "ruin-3");
	sField[cnt].State = FIELD_STATE_RUIN;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_RUIN1;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWRUIN1;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHTRUIN1;
	sField[cnt].BackMusicCode = BGM_CODE_DESERT;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_MAIN;
	sField[cnt].SetCenterPos(4953, 10922);
	sField[cnt].AddStartPoint(875, 7910);
	sField[cnt].AddStartPoint(1576, 14307);
	sField[cnt].AddGate(&sField[cnt + 1], 3051, 16124, 0);



	cnt = 6;
	sField[cnt].SetName("Ruin\\ruin-2.ase", "ruin-2");
	sField[cnt].State = FIELD_STATE_RUIN;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_RUIN2;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWRUIN2;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHTRUIN2;
	sField[cnt].BackMusicCode = BGM_CODE_DESERT;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_MAIN;
	sField[cnt].SetCenterPos(7459, 23984);
	sField[cnt].AddStartPoint(3976, 19645);
	sField[cnt].AddStartPoint(5832, 23751);
	sField[cnt].AddStartPoint(5615, 25117);
	sField[cnt].AddStageObject("ruin\\ruin_ani01.ASE");
	sField[cnt].AddGate(&sField[cnt + 1], 10019, 18031, 0);
	sField[cnt].AddGate(&sField[cnt + 11], 4470, 27774, 0);
	sField[cnt].AddGate(&sField[34], 12713, 23409, 0);

	sField[cnt].AddWarpGate(4428, 22511, 845, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt], 4547, 22616, 817);
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].SpecialEffect = 2;



	cnt = 7;
	sField[cnt].SetName("Ruin\\ruin-1.ase", "ruin-1");
	sField[cnt].State = FIELD_STATE_RUIN;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_RUIN2;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWRUIN2;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHTRUIN2;
	sField[cnt].BackMusicCode = BGM_CODE_DESERT;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_MAIN;

	sField[cnt].SetCenterPos(16362, 14959);
	sField[cnt].AddStartPoint(12242, 16034);
	sField[cnt].AddStartPoint(12194, 8969);
	sField[cnt].AddGate(&sField[cnt + 1], 13319, 7102, 0);

	sField[cnt].AddWarpGate(16809, 15407, 501, 128, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt + 6], -15395, -24185, 0);

	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = FieldLimitLevel_Table[cnt + 6];



	cnt = 8;
	sField[cnt].SetName("desert\\De-1.ase", "De-1");
	sField[cnt].State = FIELD_STATE_DESERT;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_DESERT;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWDESERT;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHTDESERT;
	sField[cnt].BackMusicCode = BGM_CODE_DESERT;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_MAIN;
	sField[cnt].SetCenterPos(15005, -1421);
	sField[cnt].AddStartPoint(13306, 2000);
	sField[cnt].AddStartPoint(13083, -2249);
	sField[cnt].AddGate(&sField[cnt + 2], 13466, -5953, 0);
	sField[cnt].AddGate(&sField[cnt + 1], 20041, -892, 0);



	cnt = 9;
	sField[cnt].SetName("forest\\village-1.ase", "village-1");
	sField[cnt].State = FIELD_STATE_DESERT;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_DESERT;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWDESERT;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHTDESERT;
	sField[cnt].FieldEvent = FIELD_EVENT_NIGHTMARE;
	sField[cnt].BackMusicCode = BGM_CODE_TOWN1;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_MAIN;
	sField[cnt].SetCenterPos(22214, -1182);
	sField[cnt].AddStartPoint(22214, -1182);

	sField[cnt].AddStageObject("forest\\v2-ani01.ASE");

	sField[cnt].AddGate(&sField[cnt + 2], 27110, -479, 0);
	sField[cnt].AddGate(&sField[30], 21840, 1062, 0);


	sField[cnt].AddWarpGate(21936, -1833, 855, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt], 21826, -1712, 825);
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].SpecialEffect = 2;


	cnt = 10;
	sField[cnt].SetName("desert\\De-2.ase", "De-2");
	sField[cnt].State = FIELD_STATE_DESERT;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_DESERT;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWDESERT;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHTDESERT;
	sField[cnt].BackMusicCode = BGM_CODE_DESERT;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_MAIN;
	sField[cnt].SetCenterPos(15887, -11161);
	sField[cnt].AddStartPoint(11859, -11257);
	sField[cnt].AddStartPoint(16169, -12768);


	cnt = 11;
	sField[cnt].SetName("desert\\De-3.ase", "De-3");
	sField[cnt].State = FIELD_STATE_DESERT;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_DESERT;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWDESERT;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHTDESERT;
	sField[cnt].BackMusicCode = BGM_CODE_DESERT;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].SetCenterPos(34758, -1323);
	sField[cnt].AddStartPoint(34758, -1323);
	sField[cnt].AddStartPoint(29424, 322);
	sField[cnt].AddGate(&sField[cnt + 1], 34372, 4277, 0);

	sField[cnt].AddWarpGate(36128, -2162, 804, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[46], -11088, -41570, 343);

	sField[cnt].AddWarpGate(29559, 2499, 828, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[46], -11975, -62457, 209);


	sField[cnt].LimitLevel = FieldLimitLevel_Table[cnt];

	sField[cnt].AddWarpGate(36128, -2162, 804, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt + 11], -11088, -41570, 343);

	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = FieldLimitLevel_Table[cnt + 11];



	cnt = 12;
	sField[cnt].SetName("desert\\De-4.ase", "De-4");
	sField[cnt].State = FIELD_STATE_DESERT;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_DESERT;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWDESERT;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHTDESERT;
	sField[cnt].BackMusicCode = BGM_CODE_DESERT;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;

	sField[cnt].SetCenterPos(43988, 12053);
	sField[cnt].AddStageObject("desert\\d4-ani01.ASE");
	sField[cnt].AddStartPoint(33740, 6491);
	sField[cnt].AddStartPoint(40691, 11056);
	sField[cnt].AddGate(&sField[27], 44545, 13063, 0);

	sField[cnt].AddWarpGate(33979, 6080, 969, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt], 34100, 6214, 940);
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].SpecialEffect = 2;



	cnt = 13;
	sField[cnt].SetName("dungeon\\dun-1.ase", "dun-1");
	sField[cnt].State = FIELD_STATE_DUNGEON;
	sField[cnt].BackImageCode[0] = 0;
	sField[cnt].BackImageCode[1] = 0;
	sField[cnt].BackImageCode[2] = 0;
	sField[cnt].BackMusicCode = BGM_CODE_DUNGEON;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].AddStageObject("dungeon\\dun-1-wheel.ase");
	sField[cnt].SetCenterPos(-15384, -24310);
	sField[cnt].AddWarpGate(-15388, -24073, 100, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt - 6], 16649, 15238, 501);
	sField[cnt].AddWarpGate(-15305, -28824, 1, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt + 1], -6027, -26881, 99);
	sField[cnt].AddAmbientPos(-15385, 100, -24949, 128, 0);
	//sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = FieldLimitLevel_Table[cnt + 1];
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = 40;
	sField[cnt].LimitLevel = 40;



	cnt = 14;
	sField[cnt].SetName("dungeon\\dun-2.ase", "dun-2");
	sField[cnt].State = FIELD_STATE_DUNGEON;
	sField[cnt].BackImageCode[0] = 0;
	sField[cnt].BackImageCode[1] = 0;
	sField[cnt].BackImageCode[2] = 0;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].BackMusicCode = BGM_CODE_DUNGEON;
	sField[cnt].SetCenterPos(-6108, -26880);

	sField[cnt].AddWarpGate(-5908, -26878, 136, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt - 1], -15314, -28718, 58);

	sField[cnt].AddWarpGate(-8019, -25768, 21, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt + 1], 1810, -28802, 0);


	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = FieldLimitLevel_Table[cnt + 1];

	sField[cnt].AddWarpGate(-3918, -27988, 21, 64, 32);

	sField[cnt].AddWarpOutGate(&sField[cnt + 1], 1810, -28802, 0);

	//sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = FieldLimitLevel_Table[cnt + 1];
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = 50;
	sField[cnt].LimitLevel = 50;


	cnt = 15;
	sField[cnt].SetName("dungeon\\dun-3.ase", "dun-3");
	sField[cnt].State = FIELD_STATE_DUNGEON;
	sField[cnt].BackImageCode[0] = 0;
	sField[cnt].BackImageCode[1] = 0;
	sField[cnt].BackImageCode[2] = 0;
	sField[cnt].BackMusicCode = BGM_CODE_DUNGEON;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].SetCenterPos(1827, -28586);


	sField[cnt].AddWarpGate(1810, -28924, 0, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt - 1], -8176, -25775, 77);
	sField[cnt].AddWarpOutGate(&sField[cnt - 1], -3738, -27990, 73);
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = 60;
	sField[cnt].LimitLevel = 60;



	cnt = 16;

	sField[cnt].SetName("room\\office.ase", 0);
	sField[cnt].State = FIELD_STATE_ROOM;
	sField[cnt].BackImageCode[0] = 0;
	sField[cnt].BackImageCode[1] = 0;
	sField[cnt].BackImageCode[2] = 0;
	sField[cnt].BackMusicCode = BGM_CODE_FOREST;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_MAIN;
	sField[cnt].SetCenterPos(-200000, 200000);


	cnt = 17;
	sField[cnt].SetName("forever-fall\\forever-fall-04.ASE", "forever-fall-04");
	sField[cnt].State = FIELD_STATE_FOREST;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_DAYFALL;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWFALL;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHTFALL;
	sField[cnt].BackMusicCode = BGM_CODE_FOREST;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].SetCenterPos(-1583, 37905);
	sField[cnt].AddStartPoint(-2135, 33668);
	sField[cnt].AddStartPoint(4073, 32119);

	sField[cnt].AddStageObject("forever-fall\\4ani-01.ASE");
	sField[cnt].AddStageObject("forever-fall\\4ani-02.ASE");
	sField[cnt].AddStageObject("forever-fall\\4ani-03.ASE");
	sField[cnt].AddStageObject("forever-fall\\4ani-04.ASE");
	sField[cnt].AddStageObject("forever-fall\\4ani-05.ASE");
	sField[cnt].AddStageObject("forever-fall\\4ani-06.ASE");
	sField[cnt].AddStageObject("forever-fall\\4ani-07.ASE");
	sField[cnt].AddStageObject("forever-fall\\4ani-08.ASE");
	sField[cnt].AddStageObject("forever-fall\\4ani-09.ASE");
	sField[cnt].AddStageObject("forever-fall\\4ani-10.ASE");
	sField[cnt].AddStageObject("forever-fall\\4ani-11.ASE");

	sField[cnt].AddGate(&sField[cnt + 1], -2949, 40442, 0);

	sField[cnt].AddAmbientPos(-1448, 827, 34188, 160, 7);
	sField[cnt].AddAmbientPos(618, 531, 35981, 160, 7);


	sField[cnt].AddAmbientPos(2282, 537, 32355, 160, 20);
	sField[cnt].AddAmbientPos(2597, 793, 30745, 0, 20);
	sField[cnt].AddAmbientPos(2562, 641, 32726, 0, 20);
	sField[cnt].AddAmbientPos(3789, 770, 30062, 0, 20);

	sField[cnt].AddAmbientPos(3698, 909, 34179, 60, 14);
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = 10;




	cnt = 18;
	sField[cnt].SetName("forever-fall\\forever-fall-03.ASE", "forever-fall-03");
	sField[cnt].State = FIELD_STATE_FOREST;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_DAYFALL;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWFALL;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHTFALL;
	sField[cnt].BackMusicCode = BGM_CODE_FOREST;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;

	sField[cnt].SetCenterPos(-5823, 43244);
	sField[cnt].AddStartPoint(-1516, 45437);
	sField[cnt].AddStartPoint(-3586, 42886);

	sField[cnt].AddStageObject("forever-fall\\3ani-01.ASE");
	sField[cnt].AddStageObject("forever-fall\\3ani-02.ASE");
	sField[cnt].AddStageObject("forever-fall\\3ani-03.ASE");
	sField[cnt].AddStageObject("forever-fall\\3ani-04.ASE");
	sField[cnt].AddStageObject("forever-fall\\3ani-05.ASE");
	sField[cnt].AddStageObject("forever-fall\\3ani-06.ASE");

	sField[cnt].AddStageObject("forever-fall\\3ani-07.ASE");

	sField[cnt].AddGate(&sField[cnt + 1], -2349, 49830, 0);

	sField[cnt].AddAmbientPos(-3573, 861, 42603, 0, 15);
	sField[cnt].AddAmbientPos(-2160, 943, 42588, 0, 19);


	sField[cnt].AddWarpGate(-4730, 48107, 1173, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt], -4615, 48002, 1146);
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].SpecialEffect = 2;

	sField[cnt].AddWarpGate(-6306, 43241, 779, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[25], 119025, 35680, 499);

	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = FieldLimitLevel_Table[cnt + 7];
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = 55;


	cnt = 19;
	sField[cnt].SetName("forever-fall\\forever-fall-02.ASE", "forever-fall-02");
	sField[cnt].State = FIELD_STATE_FOREST;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_DAYFALL;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWFALL;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHTFALL;
	sField[cnt].BackMusicCode = BGM_CODE_FOREST;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].SetCenterPos(1691, 52599);
	sField[cnt].AddStartPoint(-1024, 45437);
	sField[cnt].AddStartPoint(-1543, 52333);
	sField[cnt].AddStartPoint(-1310, 54945);

	sField[cnt].AddStageObject("forever-fall\\2ani-01.ASE");
	sField[cnt].AddStageObject("forever-fall\\2ani-02.ASE");
	sField[cnt].AddStageObject("forever-fall\\2ani-03.ASE");
	sField[cnt].AddStageObject("forever-fall\\2ani-04.ASE");
	sField[cnt].AddStageObject("forever-fall\\2ani-05.ASE");

	sField[cnt].AddGate(&sField[cnt + 1], 667, 59371, 0);

	sField[cnt].AddAmbientPos(-266, 862, 57971, 100, 13);
	sField[cnt].AddAmbientPos(-5014, 629, 56702, 100, 13);
	sField[cnt].AddAmbientPos(2153, 772, 53576, 80, 13);
	sField[cnt].AddAmbientPos(-395, 542, 56521, 80, 13);
	sField[cnt].AddAmbientPos(-3329, 522, 56469, 20, 15);
	sField[cnt].AddAmbientPos(-39, 604, 54080, 10, 6);
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = 10;



	cnt = 20;
	sField[cnt].SetName("forever-fall\\forever-fall-01.ASE", "forever-fall-01");
	sField[cnt].State = FIELD_STATE_FOREST;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_DAYFALL;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWFALL;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHTFALL;
	sField[cnt].BackMusicCode = BGM_CODE_FOREST;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].SetCenterPos(2032, 71183);
	sField[cnt].AddStartPoint(1875, 69871);
	sField[cnt].AddStartPoint(2637, 60219);

	sField[cnt].AddGate(&sField[cnt + 1], -8508, -10576, 0);

	sField[cnt].AddStageObject("forever-fall\\1ani-01.ase");
	sField[cnt].AddStageObject("forever-fall\\1ani-02.ase");
	sField[cnt].AddStageObject("forever-fall\\1ani-03.ase");
	sField[cnt].AddStageObject("forever-fall\\1ani-04.ase");
	sField[cnt].AddStageObject("forever-fall\\1ani-05.ase");
	sField[cnt].AddStageObject("forever-fall\\1ani-06.ase");
	sField[cnt].AddStageObject("forever-fall\\1ani-07.ase");
	sField[cnt].AddStageObject("forever-fall\\1ani-08.ase");
	sField[cnt].AddStageObject("forever-fall\\1ani-09.ase");
	sField[cnt].AddStageObject("forever-fall\\1ani-10.ase");
	sField[cnt].AddStageObject("forever-fall\\1ani-11.ase");
	sField[cnt].AddStageObject("forever-fall\\1ani-12.ase");
	sField[cnt].AddStageObject("forever-fall\\1ani-13.ase");
	sField[cnt].AddStageObject("forever-fall\\1ani-14.ase");
	sField[cnt].AddStageObject("forever-fall\\1ani-15.ase");
	sField[cnt].AddStageObject("forever-fall\\1ani-16.ase");
	sField[cnt].AddStageObject("forever-fall\\1ani-17.ase");
	sField[cnt].AddStageObject("forever-fall\\1ani-18.ase");
	sField[cnt].AddStageObject("forever-fall\\1ani-19.ase");
	sField[cnt].AddStageObject("forever-fall\\1ani-20.ase");
	sField[cnt].AddStageObject("forever-fall\\1ani-21.ase");
	sField[cnt].AddStageObject("forever-fall\\1ani-22.ase");
	sField[cnt].AddStageObject("forever-fall\\1ani-23.ase");
	sField[cnt].AddStageObject("forever-fall\\1ani-24.ase");
	sField[cnt].AddStageObject("forever-fall\\1ani-25.ase");
	sField[cnt].AddStageObject("forever-fall\\1ani-26.ase");
	sField[cnt].AddStageObject("forever-fall\\1ani-27.ase");

	sField[cnt].AddWarpGate(1962, 71184, 559, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt + 1], 1993, 73134, 449);
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].SpecialEffect = 1;

	sField[cnt].AddAmbientPos(2849, 577, 67330, 30, 18);
	sField[cnt].AddAmbientPos(317, 653, 64957, 10, 19);
	sField[cnt].AddAmbientPos(-1166, 779, 63268, 40, 18);
	sField[cnt].AddAmbientPos(-181, 864, 62576, 10, 18);
	sField[cnt].AddAmbientPos(190, 686, 61850, 10, 18);
	sField[cnt].AddAmbientPos(-1070, 671, 61561, 10, 18);

	sField[cnt].AddAmbientPos(1815, 562, 65414, 100, 8);
	sField[cnt].AddAmbientPos(1800, 603, 61149, 100, 8);
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = 0;



	cnt = 21;
	sField[cnt].SetName("forever-fall\\pilai.ASE", "pilai");
	sField[cnt].State = FIELD_STATE_VILLAGE;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_DAYFALL;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWFALL;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHTFALL;
	sField[cnt].BackMusicCode = BGM_CODE_FILAI;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_MAIN;

	sField[cnt].SetCenterPos(2981, 75486);

	sField[cnt].AddStartPoint(2287, 74131);
	sField[cnt].AddStartPoint(3547, 75500);

	sField[cnt].AddStageObject("forever-fall\\piani-01.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-02.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-03.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-04.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-05.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-06.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-07.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-08.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-09.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-10.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-11.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-12.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-13.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-14.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-15.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-16.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-17.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-18.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-19.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-20.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-21.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-22.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-23.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-24.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-25.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-26.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-27.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-28.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-29.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-30.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-31.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-32.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-33.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-34.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-35.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-36.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-37.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-38.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-39.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-40.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-41.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-42.ase");
	sField[cnt].AddStageObject("forever-fall\\piani-43.ase");


#ifdef	WORLDCUP_FIELD

	sField[cnt].AddStageObject("forever-fall\\ani_world01.ASE");
	sField[cnt].AddStageObject("forever-fall\\ani_world02.ASE");
	sField[cnt].AddStageObject("forever-fall\\ani_world03.ASE");
	sField[cnt].AddStageObject("forever-fall\\ani_world04.ASE");
	sField[cnt].AddStageObject("forever-fall\\ani_world05.ASE");
	sField[cnt].AddStageObject("forever-fall\\ani_world06.ASE");

#endif


	sField[cnt].AddWarpGate(2000, 72907, 474, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt - 1], 1958, 70922, 536);
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].SpecialEffect = 1;

	sField[cnt].AddAmbientPos(3557, 613, 75494, 20, 9);
	sField[cnt].AddAmbientPos(2256, 745, 78247, 50, 6);
	sField[cnt].AddAmbientPos(2066, 463, 73782, 0, 5);
	sField[cnt].AddAmbientPos(3032, 554, 73674, 10, 4);
	sField[cnt].AddAmbientPos(2246, 554, 76696, 0, 14);

	sField[cnt].AddAmbientPos(2531, 544, 74955, 30, 12);
	sField[cnt].AddAmbientPos(2034, 544, 74921, 30, 12);

	sField[cnt].AddAmbientPos(934, 542, 73886, 0, 17);
	sField[cnt].AddAmbientPos(3851, 492, 74639, 0, 17);
	sField[cnt].AddAmbientPos(3326, 666, 76387, 0, 17);


	sField[cnt].AddWarpGate(2245, 78259, 745, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt], 2252, 78041, 754);
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].SpecialEffect = 2;


	cnt = 22;

	sField[cnt].SetName("dungeon\\dun-4.ase", "dun-4");
	sField[cnt].State = FIELD_STATE_DUNGEON;
	sField[cnt].BackImageCode[0] = 0;
	sField[cnt].BackImageCode[1] = 0;
	sField[cnt].BackImageCode[2] = 0;
	sField[cnt].BackMusicCode = BGM_CODE_DUNGEON;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;


	sField[cnt].AddStageObject("dungeon\\dun-4-ani-01.ase");
	sField[cnt].AddStageObject("dungeon\\dun-4-ani-02.ase");
	sField[cnt].AddStageObject("dungeon\\dun-4-ani-03.ase");


	sField[cnt].AddStageObject("dungeon\\dun-4-ani-06.ase");
	sField[cnt].AddStageObject("dungeon\\dun-4-ani-07.ase");
	sField[cnt].AddStageObject("dungeon\\dun-4-ani-08.ase");
	sField[cnt].AddStageObject("dungeon\\dun-4-ani-09.ase");




	sField[cnt].AddStageObject("dungeon\\dun-4-ani-14.ase");
	sField[cnt].AddStageObject("dungeon\\dun-4-ani-15.ase");
	sField[cnt].AddStageObject("dungeon\\dun-4-ani-16.ase");
	sField[cnt].AddStageObject("dungeon\\dun-4-ani-17.ase");
	sField[cnt].AddStageObject("dungeon\\dun-4-ani-18.ase");
	sField[cnt].AddStageObject("dungeon\\dun-4-ani-19.ase");
	sField[cnt].AddStageObject("dungeon\\dun-4-ani-20.ase");
	sField[cnt].AddStageObject("dungeon\\dun-4-ani-21.ase");
	sField[cnt].AddStageObject("dungeon\\dun-4-ani-22.ase");
	sField[cnt].AddStageObject("dungeon\\dun-4-ani-23.ase");
	sField[cnt].AddStageObject("dungeon\\dun-4-ani-24.ase");
	sField[cnt].AddStageObject("dungeon\\dun-4-ani-25.ase");
	sField[cnt].AddStageObject("dungeon\\dun-4-ani-26.ase");
	sField[cnt].AddStageObject("dungeon\\dun-4-ani-27.ase");
	sField[cnt].AddStageObject("dungeon\\dun-4-ani-28.ase");
	sField[cnt].AddStageObject("dungeon\\dun-4-ani-29.ase");
	sField[cnt].AddStageObject("dungeon\\dun-4-ani-30.ase");
	sField[cnt].AddStageObject("dungeon\\dun-4-ani-31.ase");
	sField[cnt].AddStageObject("dungeon\\dun-4-ani-32.ase");
	sField[cnt].AddStageObject("dungeon\\dun-4-ani-33.ase");
	sField[cnt].AddStageObject("dungeon\\dun-4-ani-34.ase");
	sField[cnt].AddStageObject("dungeon\\dun-4-ani-35.ase");
	sField[cnt].AddStageObject("dungeon\\dun-4-ani-36.ase");
	sField[cnt].AddStageObject("dungeon\\dun-4-ani-37.ase");

	sField[cnt].SetCenterPos(-11108, -41681);

	sField[cnt].AddWarpGate(-10860, -41666, 398, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt - 11], 35872, -2016, 804);

	sField[cnt].AddWarpGate(-12089, -40380, 95, 64, 32);

	sField[cnt].AddWarpOutGate(&sField[cnt + 1], -2527, -37196, 727);
	sField[cnt].AddWarpOutGate(&sField[cnt + 1], -3669, -36444, 727);
	sField[cnt].AddWarpOutGate(&sField[cnt + 1], -4795, -37198, 727);


	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = FieldLimitLevel_Table[cnt + 1];
	sField[cnt].LimitLevel = 70;

	sField[cnt].AddAmbientPos(-10857, 343, -42634, 10, 24);
	sField[cnt].AddAmbientPos(-11299, 689, -44077, 10, 24);
	sField[cnt].AddAmbientPos(-12995, 689, -43856, 10, 24);

	sField[cnt].AddAmbientPos(-11698, 343, -43240, 10, 24);
	sField[cnt].AddAmbientPos(-13472, 343, -42494, 10, 24);
	sField[cnt].AddAmbientPos(-13447, 343, -40892, 10, 24);

	sField[cnt].AddAmbientPos(-9956, 343, -40637, 10, 24);
	sField[cnt].AddAmbientPos(-9957, 443, -43232, 10, 24);
	sField[cnt].AddAmbientPos(-14113, 443, -42715, 10, 24);
	sField[cnt].AddAmbientPos(-14245, 343, -40555, 10, 24);

	sField[cnt].AddAmbientPos(-12071, 339, -39600, 10, 25);

	sField[cnt].AddAmbientPos(-10236, 443, -44024, 0, 23);
	sField[cnt].AddAmbientPos(-12637, 339, -38716, 0, 23);



	sField[cnt].AddAmbientPos(-12231, 94, -41732, 10, 27);


	cnt = 23;
	sField[cnt].SetName("dungeon\\dun-5.ase", "dun-5");
	sField[cnt].State = FIELD_STATE_DUNGEON;
	sField[cnt].BackImageCode[0] = 0;
	sField[cnt].BackImageCode[1] = 0;
	sField[cnt].BackImageCode[2] = 0;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].BackMusicCode = BGM_CODE_DUNGEON;
	sField[cnt].SetCenterPos(-3675, -36597);

	sField[cnt].AddStageObject("dungeon\\dun-5-ani-01.ASE");
	sField[cnt].AddStageObject("dungeon\\dun-5-ani-02.ASE");
	sField[cnt].AddStageObject("dungeon\\dun-5-ani-03.ASE");
	sField[cnt].AddStageObject("dungeon\\dun-5-ani-04.ASE");
	sField[cnt].AddStageObject("dungeon\\dun-5-ani-05.ASE");
	sField[cnt].AddStageObject("dungeon\\dun-5-ani-06.ASE");
	sField[cnt].AddStageObject("dungeon\\dun-5-ani-07.ASE");
	sField[cnt].AddStageObject("dungeon\\dun-5-ani-08.ASE");
	sField[cnt].AddStageObject("dungeon\\dun-5-ani-09.ASE");
	sField[cnt].AddStageObject("dungeon\\dun-5-ani-10.ASE");
	sField[cnt].AddStageObject("dungeon\\dun-5-ani-11.ASE");
	sField[cnt].AddStageObject("dungeon\\dun-5-ani-12.ASE");
	sField[cnt].AddStageObject("dungeon\\dun-5-ani-13.ASE");
	sField[cnt].AddStageObject("dungeon\\dun-5-ani-14.ASE");
	sField[cnt].AddStageObject("dungeon\\dun-5-ani-15.ASE");
	sField[cnt].AddStageObject("dungeon\\dun-5-ani-16.ASE");
	sField[cnt].AddStageObject("dungeon\\dun-5-ani-17.ASE");
	sField[cnt].AddStageObject("dungeon\\dun-5-ani-18.ASE");
	sField[cnt].AddStageObject("dungeon\\dun-5-ani-19.ASE");
	sField[cnt].AddStageObject("dungeon\\dun-5-ani-20.ASE");
	sField[cnt].AddStageObject("dungeon\\dun-5-ani-21.ASE");
	sField[cnt].AddStageObject("dungeon\\dun-5-ani-22.ASE");

	sField[cnt].AddAmbientPos(-3660, 730, -36915, 40, 23);

	sField[cnt].AddAmbientPos(-2166, 732, -36125, 0, 24);
	sField[cnt].AddAmbientPos(-5150, 732, -36123, 0, 24);

	sField[cnt].AddAmbientPos(-6175, 762, -41850, 0, 24);
	sField[cnt].AddAmbientPos(-1239, 762, -41850, 0, 24);

	sField[cnt].AddAmbientPos(-1251, 794, -38207, 0, 24);

	sField[cnt].AddAmbientPos(-2424, 732, -38229, 0, 7);
	sField[cnt].AddAmbientPos(-3611, 885, -39747, 0, 7);
	sField[cnt].AddAmbientPos(-4798, 732, -38212, 0, 7);

	sField[cnt].AddWarpGate(-3665, -36334, 762, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt - 1], -12073, -40701, 95);

	sField[cnt].AddWarpGate(-4895, -37132, 762, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt - 1], -12073, -40701, 95);

	sField[cnt].AddWarpGate(-2441, -37137, 762, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt - 1], -12073, -40701, 95);




	sField[cnt].AddWarpGate(-3207, -43830, 553, 128, 32);
	sField[cnt].AddWarpOutGate(&sField[42], -3650, -45312, 116);
	sField[cnt].AddWarpOutGate(&sField[42], -3668, -50022, 3);

	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = FieldLimitLevel_Table[cnt + 19];

	sField[cnt].AddWarpGate(-4025, -43821, 553, 128, 32);
	sField[cnt].AddWarpOutGate(&sField[42], -3650, -45312, 116);
	sField[cnt].AddWarpOutGate(&sField[42], -3668, -50022, 3);

	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = FieldLimitLevel_Table[cnt + 19];
	sField[cnt].LimitLevel = 75;


	cnt = 24;
	sField[cnt].SetName("cave\\Tcave.ase", "Tcave");
	sField[cnt].State = FIELD_STATE_DUNGEON;
	sField[cnt].BackImageCode[0] = 0;
	sField[cnt].BackImageCode[1] = 0;
	sField[cnt].BackImageCode[2] = 0;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_MAIN;
	sField[cnt].BackMusicCode = BGM_CODE_DUNGEON;

	sField[cnt].SetCenterPos(120126, 26064);

	sField[cnt].AddStartPoint(119319, 26034);
	sField[cnt].AddStartPoint(125606, 24541);

	sField[cnt].AddWarpGate(125581, 25086, 480, 80, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt + 2], 158627, 20504, 240);

	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = FieldLimitLevel_Table[cnt + 2];

	sField[cnt].AddWarpGate(118869, 26017, 538, 80, 32);
	sField[cnt].AddWarpOutGate(&sField[0], -16490, -6930, 298);

	sField[cnt].AddStageObject("cave\\Tcave_ani01.ase");
	sField[cnt].AddStageObject("cave\\Tcave_ani02.ase");
	sField[cnt].AddStageObject("cave\\Tcave_ani03.ase");
	sField[cnt].AddStageObject("cave\\Tcave_ani04.ase");
	sField[cnt].AddStageObject("cave\\Tcave_ani05.ase");
	sField[cnt].AddStageObject("cave\\Tcave_ani06.ase");
	sField[cnt].AddStageObject("cave\\Tcave_ani07.ase");
	sField[cnt].AddStageObject("cave\\Tcave_ani08.ase");
	sField[cnt].AddStageObject("cave\\Tcave_ani09.ase");
	sField[cnt].AddStageObject("cave\\Tcave_ani10.ase");
	sField[cnt].AddStageObject("cave\\Tcave_ani11.ase");
	sField[cnt].AddStageObject("cave\\Tcave_ani12.ase");
	sField[cnt].AddStageObject("cave\\Tcave_ani13.ase");
	sField[cnt].AddStageObject("cave\\Tcave_ani14.ase");
	sField[cnt].AddStageObject("cave\\Tcave_ani15.ase");
	sField[cnt].AddStageObject("cave\\Tcave_ani16.ase");


	cnt = 25;
	sField[cnt].SetName("cave\\Mcave.ase", "Mcave");
	sField[cnt].State = FIELD_STATE_DUNGEON;
	sField[cnt].BackImageCode[0] = 0;
	sField[cnt].BackImageCode[1] = 0;
	sField[cnt].BackImageCode[2] = 0;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_MAIN;
	sField[cnt].BackMusicCode = BGM_CODE_DUNGEON;

	sField[cnt].SetCenterPos(119966, 35466);

	sField[cnt].AddStartPoint(119320, 35680);
	sField[cnt].AddStartPoint(124380, 33260);

	sField[cnt].AddWarpGate(124391, 32913, 37, 80, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt + 1], 158543, 19557, 290);

	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = FieldLimitLevel_Table[cnt + 1];



	sField[cnt].AddWarpGate(118808, 35686, 520, 80, 32);
	sField[cnt].AddWarpOutGate(&sField[18], -6056, 43245, 787);

	sField[cnt].AddStageObject("cave\\Mcave_ani01.ASE");
	sField[cnt].AddStageObject("cave\\Mcave_ani02.ASE");
	sField[cnt].AddStageObject("cave\\Mcave_ani03.ASE");
	sField[cnt].AddStageObject("cave\\Mcave_ani04.ASE");
	sField[cnt].AddStageObject("cave\\Mcave_ani05.ASE");
	sField[cnt].AddStageObject("cave\\Mcave_ani06.ASE");
	sField[cnt].AddStageObject("cave\\Mcave_ani07.ASE");
	sField[cnt].AddStageObject("cave\\Mcave_ani08.ASE");
	sField[cnt].AddStageObject("cave\\Mcave_ani09.ASE");
	sField[cnt].AddStageObject("cave\\Mcave_ani10.ASE");
	sField[cnt].AddStageObject("cave\\Mcave_ani11.ASE");
	sField[cnt].AddStageObject("cave\\Mcave_ani12.ASE");
	sField[cnt].AddStageObject("cave\\Mcave_ani13.ASE");
	sField[cnt].AddStageObject("cave\\Mcave_ani14.ASE");
	sField[cnt].AddStageObject("cave\\Mcave_ani15.ASE");
	sField[cnt].AddStageObject("cave\\Mcave_ani16.ASE");
	sField[cnt].AddStageObject("cave\\Mcave_ani17.ASE");


	cnt = 26;
	sField[cnt].SetName("cave\\Dcave.ase", "Dcave");
	sField[cnt].State = FIELD_STATE_DUNGEON;
	sField[cnt].BackImageCode[0] = 0;
	sField[cnt].BackImageCode[1] = 0;
	sField[cnt].BackImageCode[2] = 0;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].BackMusicCode = BGM_CODE_DUNGEON;

	sField[cnt].SetCenterPos(158814, 20070);

	sField[cnt].AddWarpGate(158042, 19525, 330, 120, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt - 1], 124396, 33291, 37);

	sField[cnt].AddWarpGate(158023, 20453, 240, 120, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt - 2], 125566, 24825, 480);

	sField[cnt].AddStageObject("cave\\Dcave_ani01.ASE");
	sField[cnt].AddStageObject("cave\\Dcave_ani02.ASE");
	sField[cnt].AddStageObject("cave\\Dcave_ani03.ASE");
	sField[cnt].AddStageObject("cave\\Dcave_ani04.ASE");
	sField[cnt].AddStageObject("cave\\Dcave_ani05.ASE");
	sField[cnt].AddStageObject("cave\\Dcave_ani06.ASE");
	sField[cnt].AddStageObject("cave\\Dcave_ani07.ASE");
	sField[cnt].AddStageObject("cave\\Dcave_ani08.ASE");
	sField[cnt].AddStageObject("cave\\Dcave_ani09.ASE");
	sField[cnt].AddStageObject("cave\\Dcave_ani10.ASE");
	sField[cnt].AddStageObject("cave\\Dcave_ani11.ASE");
	sField[cnt].AddStageObject("cave\\Dcave_ani12.ASE");
	sField[cnt].AddStageObject("cave\\Dcave_ani13.ASE");
	sField[cnt].AddStageObject("cave\\Dcave_ani14.ASE");


	cnt = 27;
	sField[cnt].SetName("Iron\\iron-1.ASE", "iron-1");
	sField[cnt].State = FIELD_STATE_IRON;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_DAYIRON;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWIRON;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHTIRON1;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].BackMusicCode = -1;


	sField[cnt].SetCenterPos(47617, 13626);

	sField[cnt].AddStartPoint(46905, 13478);
	sField[cnt].AddStartPoint(47357, 20845);
	sField[cnt].AddStartPoint(46741, 21349);

	sField[cnt].LimitLevel = FieldLimitLevel_Table[cnt];

	sField[cnt].AddGate(&sField[cnt + 1], 45316, 21407, 0);

	sField[cnt].AddStageObject("iron\\i1-ani01_Bip.ASE", 1);
	sField[cnt].AddStageObject("iron\\i1-ani02_Bip.ASE", 1);
	sField[cnt].AddStageObject("iron\\i1-ani03_Bip.ASE", 1);
	sField[cnt].AddStageObject("iron\\i1-ani04_Bip.ASE", 1);
	sField[cnt].AddStageObject("iron\\i1-ani05_Bip.ASE", 1);
	sField[cnt].AddStageObject("iron\\i1-ani06_Bip.ASE", 1);
	sField[cnt].AddStageObject("iron\\i1-ani07_Bip.ASE", 1);
	sField[cnt].AddStageObject("iron\\i1-ani08_Bip.ASE", 1);

	sField[cnt].AddStageObject("iron\\i1-ani09_Bip.ASE", 1);
	sField[cnt].AddStageObject("iron\\i1-ani10_Bip.ASE", 1);
	sField[cnt].AddStageObject("iron\\i1-ani11_Bip.ASE", 1);

	sField[cnt].AddStageObject("iron\\iron-ani01.ASE");
	sField[cnt].AddStageObject("iron\\iron-ani02.ASE");
	sField[cnt].AddStageObject("iron\\iron-ani03.ASE");


	cnt = 28;
	sField[cnt].SetName("Iron\\iron-2.ASE", "iron-2");
	sField[cnt].State = FIELD_STATE_IRON;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_DAYIRON;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWIRON;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHTIRON2;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].BackMusicCode = -1;

	sField[cnt].SetCenterPos(33938, 24229);

	sField[cnt].AddStartPoint(35149, 24326);
	sField[cnt].AddStartPoint(44893, 21380);


	sField[cnt].LimitLevel = FieldLimitLevel_Table[cnt];


	sField[cnt].AddGate(&sField[cnt + 1], 33618, 24011, 0);



	sField[cnt].AddStageObject("iron\\i2-bip01.ASE");
	sField[cnt].AddStageObject("iron\\i2-bip02.ASE");
	sField[cnt].AddStageObject("iron\\i2-bip03.ASE");
	sField[cnt].AddStageObject("iron\\i2-bip04_ani.ASE", 1);
	sField[cnt].AddStageObject("iron\\i2-bip05_ani.ASE", 1);
	sField[cnt].AddStageObject("iron\\i2-bip06_ani.ASE", 1);
	sField[cnt].AddStageObject("iron\\i2-bip07_ani.ASE", 1);
	sField[cnt].AddStageObject("iron\\i2-bip08_ani.ASE", 1);
	sField[cnt].AddStageObject("iron\\i2-bip09.ASE");
	sField[cnt].AddStageObject("iron\\i2-bip10.ASE");
	sField[cnt].AddStageObject("iron\\i2-bip11_ani.ASE", 1);
	sField[cnt].AddStageObject("iron\\i2-bip12_ani.ASE", 1);
	sField[cnt].LimitLevel = 85;

	cnt = 29;
	sField[cnt].SetName("Ice\\ice_ura.ASE", "ice_ura");
	sField[cnt].State = FIELD_STATE_ICE;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_DAYSNOW;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWSNOW;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHTSNOW;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].BackMusicCode = BGM_CODE_DESERT;
	sField[cnt].SetCenterPos(32621, 23865);
	sField[cnt].AddStageObject("ice\\ice_ani_01.ASE");

	sField[cnt].AddGate(&sField[cnt + 2], 31848, 27225, 0);

	sField[cnt].AddWarpGate(30407, 22232, 1349, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt], 30610, 22164, 1304);
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].SpecialEffect = 2;
	sField[cnt].LimitLevel = 90;
	sField[cnt].LimitLevel = FieldLimitLevel_Table[cnt];
	sField[cnt].FieldSight = 1;



	cnt = 30;
	sField[cnt].SetName("Sod\\sod-1.ASE", "sod-1");
	sField[cnt].State = FIELD_STATE_RUIN;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_RUIN2;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWRUIN2;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHTRUIN2;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].BackMusicCode = BGM_CODE_CUSTOM;
	sField[cnt].SetCenterPos(22018, 6569);
	sField[cnt].AddStageObject("sod\\s-ani01_Bip.ASE", 1);
	sField[cnt].AddStageObject("sod\\s-ani02_Bip.ASE", 1);
	sField[cnt].AddStageObject("sod\\s-ani03_Bip.ASE", 1);
	sField[cnt].AddStageObject("sod\\s-ani04_Bip.ASE", 1);
	sField[cnt].AddStageObject("sod\\s-ani05_Bip.ASE", 1);
	sField[cnt].AddStageObject("sod\\s-ani06_Bip.ASE", 1);
	sField[cnt].AddStageObject("sod\\s-ani07_Bip.ASE", 1);
	sField[cnt].AddStageObject("sod\\s-ani08_Bip.ASE", 1);
	sField[cnt].AddStageObject("sod\\s-ani09_Bip.ASE", 1);
	sField[cnt].AddStageObject("sod\\s-ani10_Bip.ASE", 1);
	sField[cnt].AddStageObject("sod\\s-ani11_Bip.ASE", 1);
	sField[cnt].AddStageObject("sod\\s-ani12_Bip.ASE", 1);
	sField[cnt].AddStageObject("sod\\s-ani13_Bip.ASE", 1);
	sField[cnt].AddStageObject("sod\\s-ani14_Bip.ASE", 1);
	sField[cnt].AddStageObject("sod\\s-ani15_Bip.ASE", 1);
	sField[cnt].AddStageObject("sod\\s-ani16_Bip.ASE", 1);
	sField[cnt].AddStageObject("sod\\s-ani17_Bip.ASE", 1);
	sField[cnt].AddStageObject("sod\\s-ani18_Bip.ASE", 1);


	cnt = 31;

	sField[cnt].SetName("Ice\\ice1.ASE", "ice1");
	sField[cnt].State = FIELD_STATE_ICE;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_DAYSNOW;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWSNOW;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHTSNOW;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].BackMusicCode = BGM_CODE_ICE;

	sField[cnt].SetCenterPos(32313, 28529);
	sField[cnt].AddGate(&sField[35], 33729, 38029, 0);


	sField[cnt].AddStageObject("ice\\ice_ani_01.ASE");
	sField[cnt].AddStageObject("ice\\ice_bip_leewood01.ASE");
	sField[cnt].AddStageObject("ice\\ice_bip_leewood03.ASE");
	sField[cnt].AddStageObject("ice\\ice_bip_leewood04.ASE");
	sField[cnt].AddStageObject("ice\\ice_bip_leaf01.ASE");
	sField[cnt].AddStageObject("ice\\ice_bip_leaf02.ASE");
	sField[cnt].AddStageObject("ice\\ice_bip_leaf03.ASE");
	sField[cnt].AddStageObject("ice\\ice_bip_leaf04.ASE");
	sField[cnt].AddStageObject("ice\\ice_bip_leaf05.ASE");
	sField[cnt].AddStageObject("ice\\ice_bip_leaf06.ASE");
	sField[cnt].AddStageObject("ice\\ice_bip_leaf07.ASE");
	sField[cnt].LimitLevel = 90;



	cnt = 32;

	sField[cnt].SetName("quest\\quest_IV.ASE", "quest_IV");
	sField[cnt].State = FIELD_STATE_QUEST_ARENA;
	sField[cnt].BackImageCode[0] = 0;
	sField[cnt].BackImageCode[1] = 0;
	sField[cnt].BackImageCode[2] = 0;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].BackMusicCode = BGM_CODE_SOD3;

	sField[cnt].SetCenterPos(22497, 9605);


	cnt = 33;

	sField[cnt].SetName("castle\\castle.ase", "castle");
	sField[cnt].State = FIELD_STATE_CASTLE;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_RUIN2;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWRUIN2;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHTRUIN2;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].BackMusicCode = BGM_CODE_SOD3;

	sField[cnt].SetCenterPos(35225, -23847);

	sField[cnt].AddStartPoint(33920, -23479);
	sField[cnt].AddStartPoint(35247, -23355);
	sField[cnt].AddStartPoint(36164, -23446);

	sField[cnt].AddStageObject("castle\\wf_gate_ani.ASE");

	sField[cnt].AddStageObject("castle\\crystal_ani01.ASE");
	sField[cnt].AddStageObject("castle\\crystal_ani02.ASE");
	sField[cnt].AddStageObject("castle\\crystal_ani03.ASE");
	sField[cnt].AddStageObject("castle\\crystal_ani04.ASE");
	sField[cnt].AddStageObject("castle\\crystal_ani05.ASE");
	sField[cnt].AddStageObject("castle\\crystal_ani06.ASE");


	sField[cnt].AddWarpGate(32527, -30693, 774, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt], 32739, -30474, 711);
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].SpecialEffect = 2;


	cnt = 34;

	sField[cnt].SetName("Greedy\\Greedy.ase", "Greedy");
	sField[cnt].State = FIELD_STATE_ICE;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_DAYGREDDY;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWGREDDY;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHTGREDDY;
	sField[cnt].BackMusicCode = BGM_CODE_DESERT;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_MAIN;

	sField[cnt].SetCenterPos(13930, 23206);
	sField[cnt].LimitLevel = FieldLimitLevel_Table[cnt];

	sField[cnt].AddStageObject("Greedy\\vane1_ani.ASE");
	sField[cnt].AddStageObject("Greedy\\vane2_ani.ASE");
	sField[cnt].AddStageObject("Greedy\\vane3_ani.ASE");
	sField[cnt].AddStageObject("Greedy\\vane4_ani.ASE");
	sField[cnt].AddStageObject("Greedy\\ani_tail.ASE");
	sField[cnt].AddStageObject("Greedy\\ship_ani.ASE");
	sField[cnt].AddStageObject("Greedy\\ship1_ani.ASE");
	sField[cnt].AddStageObject("Greedy\\ship2_ani.ASE");
	sField[cnt].AddStageObject("Greedy\\ship3_ani.ASE");

	sField[cnt].AddStageObject("Greedy\\flower_animi01.ASE");
	sField[cnt].AddStageObject("Greedy\\flower_animi02.ASE");
	sField[cnt].AddStageObject("Greedy\\flower_animi03.ASE");
	sField[cnt].AddStageObject("Greedy\\flower_animi04.ASE");
	sField[cnt].AddStageObject("Greedy\\flower_animi05.ASE");
	sField[cnt].AddStageObject("Greedy\\flower_animi06.ASE");
	sField[cnt].AddStageObject("Greedy\\flower_animi07.ASE");
	sField[cnt].AddStageObject("Greedy\\flower_animi08.ASE");
	sField[cnt].AddStageObject("Greedy\\flower_animi09.ASE");
	sField[cnt].AddStageObject("Greedy\\flower_animi10.ASE");

	sField[cnt].AddStageObject("Greedy\\flower_ani00.ASE");
	sField[cnt].AddStageObject("Greedy\\flower_ani01.ASE");
	sField[cnt].AddStageObject("Greedy\\flower_ani02.ASE");
	sField[cnt].AddStageObject("Greedy\\flower_ani03.ASE");
	sField[cnt].AddStageObject("Greedy\\flower_ani04.ASE");
	sField[cnt].AddStageObject("Greedy\\flower_ani05.ASE");
	sField[cnt].AddStageObject("Greedy\\flower_ani06.ASE");
	sField[cnt].AddStageObject("Greedy\\flower_ani07.ASE");
	sField[cnt].AddStageObject("Greedy\\flower_ani08.ASE");
	sField[cnt].AddStageObject("Greedy\\flower_ani09.ASE");

	sField[cnt].AddStageObject("Greedy\\door.ASE");


	cnt = 35;

	sField[cnt].SetName("Ice\\ice_2.ASE", "ice2");
	sField[cnt].State = FIELD_STATE_ICE;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_DAYSNOW;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWSNOW;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHTSNOW;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].BackMusicCode = BGM_CODE_ICE;
	sField[cnt].LimitLevel = 95;



	sField[cnt].AddGate(&sField[31], 35364, 39518, 0);

	sField[cnt].SetCenterPos(36264, 40182);

	sField[cnt].AddWarpGate(37981, 50790, 1216, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt + 1], 33000, 50036, 1512);


	cnt = 36;

	sField[cnt].SetName("Boss\\Boss.ASE", "Boss");
	sField[cnt].State = FIELD_STATE_DUNGEON;
	sField[cnt].BackImageCode[0] = 0;
	sField[cnt].BackImageCode[1] = 0;
	sField[cnt].BackImageCode[2] = 0;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].BackMusicCode = BGM_CODE_DUNGEON;

	sField[cnt].SetCenterPos(33000, 50036);

	sField[cnt].AddWarpGate(33012, 49926, 1533, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt - 1], 37971, 50460, 1209);
	sField[cnt].LimitLevel = 95;

	cnt = 37;

	sField[cnt].SetName("lost\\lostisland.ASE", "lost");
	sField[cnt].State = FIELD_STATE_RUIN;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_DAYLOST;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWLOST;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHTLOST;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].BackMusicCode = BGM_CODE_DESERT;

	sField[cnt].SetCenterPos(-12555, -1113);

	sField[cnt].AddGate(&sField[cnt + 1], -11586, 7704, 0);

	sField[cnt].AddStageObject("lost\\wf_ani.ASE");
	sField[cnt].AddStageObject("lost\\ani_shop01.ASE");
	sField[cnt].AddStageObject("lost\\ani_shop02.ASE");
	sField[cnt].AddStageObject("lost\\ani_shop03.ASE");
	sField[cnt].AddStageObject("lost\\ani_shop04.ASE");


	sField[cnt].AddWarpGate(-12610, -1349, 694, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt], -12555, -1113, 668);
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].SpecialEffect = 2;
	sField[cnt].LimitLevel = 100;

	cnt = 38;

	sField[cnt].SetName("Losttemple\\lost_temple.ASE", "Losttemple");
	sField[cnt].State = FIELD_STATE_RUIN;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_DAYTEMPLE;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWTEMPLE;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHTTEMPLE;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].BackMusicCode = BGM_CODE_DESERT;

	sField[cnt].SetCenterPos(-11718, 10794);

	sField[cnt].LimitLevel = 105;


	cnt = 39;

	sField[cnt].SetName("Fall_Game\\fall_game.ASE", 0);
	sField[cnt].State = FIELD_STATE_ACTION;
	sField[cnt].BackImageCode[0] = 0;
	sField[cnt].BackImageCode[1] = 0;
	sField[cnt].BackImageCode[2] = 0;
	sField[cnt].BackMusicCode = BGM_CODE_FOREST;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_MAIN;


	sField[cnt].SetCenterPos(5800, 36747);




	sField[cnt].AddWarpGate(5563, 36772, 840, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[21], 2981, 75486, 0);

	sField[cnt].AddWarpGate(11502, 36776, 840, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[21], 2981, 75486, 0);

#define	IN_Z	36875
#define	IN_Y	853
#define	OUT_Z	36750
#define	OUT_Y	830


	sField[cnt].AddWarpGate(7254, IN_Z, IN_Y, 64, 8);

	sField[cnt].AddWarpOutGate(&sField[cnt], 9992, OUT_Z, OUT_Y);

	sField[cnt].AddWarpGate(9992, IN_Z, IN_Y, 64, 8);
	sField[cnt].AddWarpOutGate(&sField[cnt], 7254, OUT_Z, OUT_Y);





	cnt = 40;

	sField[cnt].SetName("endless\\dun-7.ase", "dun-7");
	sField[cnt].State = FIELD_STATE_DUNGEON;
	sField[cnt].BackImageCode[0] = 0;
	sField[cnt].BackImageCode[1] = 0;
	sField[cnt].BackImageCode[2] = 0;
	sField[cnt].BackMusicCode = BGM_CODE_DUNGEON;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].SetCenterPos(14255, -39099);

	sField[cnt].AddWarpGate(14242, -40988, 259, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt + 1], 5255, -37897, 86);

	sField[cnt].AddWarpGate(14246, -38912, 220, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[38], -12272, 11299, 509);

	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = FieldLimitLevel_Table[cnt - 2];
	sField[cnt].LimitLevel = 110;




	cnt = 41;

	sField[cnt].SetName("endless\\dun-8.ase", "dun-8");
	sField[cnt].State = FIELD_STATE_DUNGEON;
	sField[cnt].BackImageCode[0] = 0;
	sField[cnt].BackImageCode[1] = 0;
	sField[cnt].BackImageCode[2] = 0;
	sField[cnt].BackMusicCode = BGM_CODE_DUNGEON;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].SetCenterPos(5255, -37897);

	sField[cnt].AddWarpGate(5253, -37708, 69, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[cnt - 1], 14242, -41199, 220);

	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = FieldLimitLevel_Table[cnt - 1];
	sField[cnt].LimitLevel = 115;


	sField[cnt].AddWarpGate(5254, -41500, 139, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[43], 4896, -42220, 202);
	sField[cnt].AddWarpOutGate(&sField[43], 6408, -42220, 202);

	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = 115;
	sField[cnt].LimitLevel = 115;

	cnt = 42;


	sField[cnt].SetName("dungeon\\Dun-6a.ASE", "dun-6");
	sField[cnt].State = FIELD_STATE_DUNGEON;
	sField[cnt].BackImageCode[0] = 0;
	sField[cnt].BackImageCode[1] = 0;
	sField[cnt].BackImageCode[2] = 0;
	sField[cnt].BackMusicCode = BGM_CODE_DUNGEON;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].SetCenterPos(-3660, -45200);


	sField[cnt].AddStageObject("dungeon\\Dun-6a-ani-001.ASE");
	sField[cnt].AddStageObject("dungeon\\Dun-6a-ani-002.ASE");
	sField[cnt].AddStageObject("dungeon\\Dun-6a-ani-003.ASE");
	sField[cnt].AddStageObject("dungeon\\Dun-6a-ani-004.ASE");
	sField[cnt].AddStageObject("dungeon\\Dun-6a-ani-005.ASE");
	sField[cnt].AddStageObject("dungeon\\Dun-6a-ani-006.ASE");
	sField[cnt].AddStageObject("dungeon\\Dun-6a-ani-007.ASE");
	sField[cnt].AddStageObject("dungeon\\Dun-6a-ani-008.ASE");
	sField[cnt].AddStageObject("dungeon\\Dun-6a-ani-009.ASE");
	sField[cnt].AddStageObject("dungeon\\Dun-6a-ani-010.ASE");
	sField[cnt].AddStageObject("dungeon\\Dun-6a-ani-011.ASE");
	sField[cnt].AddStageObject("dungeon\\Dun-6a-ani-012.ASE");
	sField[cnt].AddStageObject("dungeon\\Dun-6a-ani-013.ASE");
	sField[cnt].AddStageObject("dungeon\\Dun-6a-ani-014.ASE");
	sField[cnt].AddStageObject("dungeon\\Dun-6a-ani-015.ASE");
	sField[cnt].AddStageObject("dungeon\\Dun-6a-ani-016.ASE");
	sField[cnt].AddStageObject("dungeon\\Dun-6a-ani-017.ASE");
	sField[cnt].AddStageObject("dungeon\\Dun-6a-ani-018.ASE");
	sField[cnt].AddStageObject("dungeon\\Dun-6a-ani-019.ASE");


	sField[cnt].AddAmbientPos(-3648, 3, -50013, 0, 7);
	sField[cnt].AddAmbientPos(-4349, 454, -47777, 0, 7);
	sField[cnt].AddAmbientPos(-5130, 454, -47587, 0, 7);
	sField[cnt].AddAmbientPos(-2183, 172, -47864, 0, 7);
	sField[cnt].AddAmbientPos(-1785, 167, -48077, 0, 7);
	sField[cnt].AddAmbientPos(-3725, 116, -46758, 0, 7);
	sField[cnt].AddAmbientPos(-3632, 3, -47999, 0, 7);
	sField[cnt].AddAmbientPos(-627, 229, -45987, 0, 7);
	sField[cnt].AddAmbientPos(-1896, 116, -45010, 0, 7);
	sField[cnt].AddAmbientPos(-5077, 116, -45555, 0, 7);
	sField[cnt].AddAmbientPos(-5289, 116, -46422, 0, 7);


	sField[cnt].AddWarpGate(-3655, -50603, 3, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[23], -2851, -43792, 642);
	sField[cnt].AddWarpOutGate(&sField[23], -4422, -43801, 642);
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = FieldLimitLevel_Table[cnt - 19];
	sField[cnt].LimitLevel = 80;

	cnt = 43;


	sField[cnt].SetName("endless\\dun-9.ASE", "dun-9");
	sField[cnt].State = FIELD_STATE_DUNGEON;
	sField[cnt].BackImageCode[0] = 0;
	sField[cnt].BackImageCode[1] = 0;
	sField[cnt].BackImageCode[2] = 0;
	sField[cnt].BackMusicCode = BGM_CODE_DUNGEON;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].SetCenterPos(4896, -42330);
	sField[cnt].AddStartPoint(4896, -42330);
	sField[cnt].AddStartPoint(6418, -42330);

	sField[cnt].AddWarpGate(4896, -42090, 230, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[41], 5254, -41361, 139);
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = 145;
	sField[cnt].LimitLevel = 145;

	cnt = 44;


	sField[cnt].SetName("Mine\\mine-1.ASE", "mine-1");
	sField[cnt].State = FIELD_STATE_DUNGEON;
	sField[cnt].BackImageCode[0] = 0;
	sField[cnt].BackImageCode[1] = 0;
	sField[cnt].BackImageCode[2] = 0;
	sField[cnt].BackMusicCode = BGM_CODE_DUNGEON;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].SetCenterPos(18053, -31715);
	

	sField[cnt].AddWarpGate(17944, -34641, 246, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[31], 35352, 31928, 829);
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = 145;
	sField[cnt].LimitLevel = 145;

	cnt = 45;


	sField[cnt].SetName("Sod\\sod-2.ASE", "sod-2");
	sField[cnt].State = FIELD_STATE_RUIN;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_RUIN2;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWRUIN2;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHTRUIN2;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].BackMusicCode = BGM_CODE_CUSTOM;
	sField[cnt].SetCenterPos(21600, 17000);
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = 140;

	cnt = 46;


	sField[cnt].SetName("Slab\\Slab.ASE", "Slab");
	sField[cnt].State = FIELD_STATE_DUNGEON;
	sField[cnt].BackImageCode[0] = 0;
	sField[cnt].BackImageCode[1] = 0;
	sField[cnt].BackImageCode[2] = 0;
	sField[cnt].BackMusicCode = BGM_CODE_DUNGEON;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].SetCenterPos(-11976, -62455);

	sField[cnt].AddWarpGate(-12003, -54164, 374, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[11], 12795, -73112, 458);

	sField[cnt].AddWarpGate(-12015, -62994, 171, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[11], 29551, 2366, 826);

	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = 140;
	sField[cnt].LimitLevel = 140;

	cnt = 47;

	// ===================================== NEW FIELD =====================================
	sField[cnt].SetName("AncientW\\ancientW.ASE", "AncientW");
	sField[cnt].State = FIELD_STATE_DUNGEON;
	sField[cnt].BackImageCode[0] = 0;
	sField[cnt].BackImageCode[1] = 0;
	sField[cnt].BackImageCode[2] = 0;
	sField[cnt].BackMusicCode = BGM_CODE_DUNGEON;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].SetCenterPos(12725, -73112);
	sField[cnt].AddStartPoint(12725, -73112);
	sField[cnt].AddStageObject("AncientW\\RotObj01.ASE");
	sField[cnt].AddStageObject("AncientW\\RotObj02.ASE");
	sField[cnt].AddStageObject("AncientW\\RotObj03.ASE");
	sField[cnt].AddStageObject("AncientW\\RotObj04.ASE");
	sField[cnt].AddStageObject("AncientW\\RotObj05.ASE");
	sField[cnt].AddStageObject("AncientW\\RotObj06.ASE");
	sField[cnt].AddStageObject("AncientW\\RotObj07.ASE");
	sField[cnt].AddStageObject("AncientW\\RotObj08.ASE");
	sField[cnt].AddStageObject("AncientW\\RotObj09.ASE");
	sField[cnt].AddStageObject("AncientW\\RotObj10.ASE");
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = 145;
	sField[cnt].LimitLevel = 145;
	cnt = 48;

	// ===================================== NEW FIELD =====================================
	sField[cnt].SetName("SeaA\\SeaA.ASE", "SeaA");
	sField[cnt].State = FIELD_STATE_DUNGEON;
	sField[cnt].BackImageCode[0] = 0;
	sField[cnt].BackImageCode[1] = 0;
	sField[cnt].BackImageCode[2] = 0;
	sField[cnt].BackMusicCode = BGM_CODE_DUNGEON;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].SetCenterPos(-19925, -3858);
	sField[cnt].AddStartPoint(-19925, -3858);
	sField[cnt].AddStageObject("SeaA\\sea_ani01.ASE");
	sField[cnt].AddStageObject("SeaA\\sea_ani02.ASE");
	sField[cnt].AddStageObject("SeaA\\sea_ani03.ASE");
	sField[cnt].AddStageObject("SeaA\\sea_ani04.ASE");
	sField[cnt].AddStageObject("SeaA\\sea_ani05.ASE");
	sField[cnt].AddStageObject("SeaA\\sea_ani06.ASE");
	sField[cnt].AddStageObject("SeaA\\sea_ani07.ASE");
	sField[cnt].AddStageObject("SeaA\\sea_ani08.ASE");
	sField[cnt].AddStageObject("SeaA\\sea_ani09.ASE");
	sField[cnt].AddStageObject("SeaA\\sea_ani10.ASE");
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = 135;
	sField[cnt].LimitLevel = 135;

	cnt = 49;
	// ===================================== NEW FIELD =====================================
	sField[cnt].SetName("SeaA\\Stemple.ASE", "Stemple");
	sField[cnt].State = FIELD_STATE_DUNGEON;
	sField[cnt].BackImageCode[0] = 0;
	sField[cnt].BackImageCode[1] = 0;
	sField[cnt].BackImageCode[2] = 0;
	sField[cnt].BackMusicCode = BGM_CODE_DUNGEON;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].SetCenterPos(-28284, 27144);
	sField[cnt].AddStartPoint(-28284, 27144);
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = 140;
	sField[cnt].LimitLevel = 140;

	cnt = 50;

	sField[cnt].SetName("Custom\\ba1.ase", "ba1");
	sField[cnt].State = FIELD_STATE_RUIN;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_DAYTEMPLE;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWTEMPLE;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHTTEMPLE;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_EXTEND;
	sField[cnt].BackMusicCode = BGM_CODE_DESERT;

	sField[cnt].SetCenterPos(-23833, 22713);
	sField[cnt].LimitLevel = 50;


	sField[cnt].AddWarpGate(-24060, 21613, 1371, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[50], -23849, 22179, 1371);
	sField[cnt].AddWarpGate(-23950, 21613, 1371, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[50], -23849, 22179, 1371);
	sField[cnt].AddWarpGate(-23880, 21613, 1371, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[50], -23849, 22179, 1371);
	sField[cnt].AddWarpGate(-23800, 21613, 1371, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[50], -23849, 22179, 1371);
	sField[cnt].AddWarpGate(-23712, 21613, 1371, 64, 32);
	sField[cnt].AddWarpOutGate(&sField[50], -23849, 22179, 1371);
	// ===================================== NEW FIELD =====================================
	cnt = 51;

	sField[cnt].SetName("old_forest\\old_village-2.ase", "old_village-2");
	sField[cnt].State = FIELD_STATE_VILLAGE;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_DAY;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWDAY;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHT;
	sField[cnt].BackMusicCode = BGM_CODE_TOWN2;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_MAIN;
	sField[cnt].SetCenterPos(1002275, 982802);
	sField[cnt].AddStartPoint(1002993, 982449);


	//MAPAS DE UP 1 AO 108  

	cnt = 52;

	sField[cnt].SetName("old_forest\\old_fore-1.ase", "old_fore-1");
	sField[cnt].State = FIELD_STATE_FOREST;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_DAY;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWDAY;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHT;
	sField[cnt].BackMusicCode = BGM_CODE_FOREST;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_MAIN;
	sField[cnt].SetCenterPos(1004184, 988984);
	sField[cnt].AddStartPoint(1000788, 989894);
	sField[cnt].AddGate(&sField[51], 1002275, 985172, 0);
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = 1;
	sField[cnt].LimitLevel = 1 ;


	cnt = 53;


	sField[cnt].SetName("old_forest\\old_fore-2.ase", "old_fore-2");
	sField[cnt].State = FIELD_STATE_FOREST;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_DAY;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWDAY;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHT;
	sField[cnt].BackMusicCode = BGM_CODE_FOREST;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_MAIN;
	sField[cnt].SetCenterPos(994573, 990085);
	sField[cnt].AddStartPoint(993356, 989515);
	sField[cnt].AddGate(&sField[52], 999708, 990452, 0);
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = 65;
	sField[cnt].LimitLevel = 65;

	cnt = 54;

	sField[cnt].SetName("old_forest\\old_fore-3.ase", "old_fore-3");
	sField[cnt].State = FIELD_STATE_FOREST;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_DAY;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWDAY;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHT;
	sField[cnt].BackMusicCode = BGM_CODE_FOREST;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_MAIN;
	sField[cnt].SetCenterPos(989880, 989360);
	sField[cnt].AddStartPoint(989354, 993667);
	sField[cnt].AddGate(&sField[53], 991492, 989424, 0);
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = 90;
	sField[cnt].LimitLevel = 90;


	cnt = 55;

	sField[cnt].SetName("WindForest\\WindForest2.ase", "WindForest");
	sField[cnt].State = FIELD_STATE_VILLAGE;
	sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_DAY;
	sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWDAY;
	sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHT;
	sField[cnt].BackMusicCode = BGM_CODE_TOWN2;
	sField[cnt].ServerCode = PLAY_SERVER_CODE_MAIN;
	sField[cnt].SetCenterPos(506900, 504998);
	//sField[cnt].AddStartPoint(506900, 504898);
	//sField[cnt].AddStartPoint(506900, 504798);
	sField[cnt].AddGate(&sField[cnt + 1], 506900, 504998, 0);
	sField[cnt].AddStageObject("WindForest\\051.ase");
	sField[cnt].AddStageObject("WindForest\\052.ase");
	sField[cnt].AddStageObject("WindForest\\053.ase");
	sField[cnt].AddStageObject("WindForest\\054.ase");
	sField[cnt].AddStageObject("WindForest\\055.ase");
	sField[cnt].AddStageObject("WindForest\\056.ase");
	sField[cnt].AddStageObject("WindForest\\057.ase");
	sField[cnt].AddStageObject("WindForest\\058.ase");
	sField[cnt].AddStageObject("WindForest\\059.ase");
	sField[cnt].AddStageObject("WindForest\\060.ase");
	sField[cnt].AddStageObject("WindForest\\061.ase");
	sField[cnt].AddStageObject("WindForest\\062.ase");
	sField[cnt].AddStageObject("WindForest\\063.ase");
	sField[cnt].AddStageObject("WindForest\\064.ase");
	sField[cnt].AddStageObject("WindForest\\065.ase");
	sField[cnt].AddStageObject("WindForest\\066.ase");
	sField[cnt].AddStageObject("WindForest\\067.ase");
	sField[cnt].AddStageObject("WindForest\\068.ase");
	sField[cnt].AddStageObject("WindForest\\069.ase");
	sField[cnt].AddStageObject("WindForest\\070.ase");
	sField[cnt].AddStageObject("WindForest\\071.ase");
	sField[cnt].AddStageObject("WindForest\\072.ase");
	sField[cnt].AddStageObject("WindForest\\073.ase");
	sField[cnt].AddStageObject("WindForest\\074.ase");
	sField[cnt].AddStageObject("WindForest\\075.ase");
	sField[cnt].AddStageObject("WindForest\\076.ase");
	sField[cnt].AddStageObject("WindForest\\077.ase");
	sField[cnt].AddStageObject("WindForest\\078.ase");
	sField[cnt].AddStageObject("WindForest\\079.ase");
	sField[cnt].AddStageObject("WindForest\\080.ase");
	sField[cnt].AddStageObject("WindForest\\081.ase");
	sField[cnt].AddStageObject("WindForest\\082.ase");
	sField[cnt].AddStageObject("WindForest\\083.ase");
	sField[cnt].AddStageObject("WindForest\\084.ase");
	sField[cnt].AddStageObject("WindForest\\085.ase");
	sField[cnt].AddStageObject("WindForest\\086.ase");
	sField[cnt].AddStageObject("WindForest\\087.ase");
	sField[cnt].AddStageObject("WindForest\\088.ase");
	sField[cnt].AddStageObject("WindForest\\089.ase");
	sField[cnt].AddStageObject("WindForest\\090.ase");
	sField[cnt].AddStageObject("WindForest\\091.ase");
	sField[cnt].AddStageObject("WindForest\\092.ase");
	sField[cnt].AddStageObject("WindForest\\093.ase");
	sField[cnt].AddStageObject("WindForest\\094.ase");
	sField[cnt].AddStageObject("WindForest\\095.ase");
	sField[cnt].AddStageObject("WindForest\\096.ase");
	sField[cnt].AddStageObject("WindForest\\097.ase");
	sField[cnt].AddStageObject("WindForest\\098.ase");
	sField[cnt].AddStageObject("WindForest\\099.ase");
	sField[cnt].AddStageObject("WindForest\\100.ase");
	sField[cnt].WarpGate[sField[cnt].WarpGateActiveNum].LimitLevel = 0;
	sField[cnt].LimitLevel = 0;

	//newm mapa  

	if (smConfig.szFile_Stage[0])
	{
		CustomField = cnt;
		sField[cnt].SetName(smConfig.szFile_Stage);



		for (int cnt2 = 0; cnt2 < smConfig.StageObjCnt; cnt2++)
		{
			if (smConfig.szFile_StageObject[cnt2][0])
			{
				if (smConfig.IsStageAniObject[cnt2])
					sField[cnt].AddStageObject(smConfig.szFile_StageObject[cnt2], 1);
				else
					sField[cnt].AddStageObject(smConfig.szFile_StageObject[cnt2]);
			}
		}








		if (strstr(smConfig.szFile_Stage, "dun") != 0)
			sField[cnt].State = FIELD_STATE_DUNGEON;
		else if (strstr(smConfig.szFile_Stage, "ice") != 0)
			sField[cnt].State = FIELD_STATE_ICE;
		else
			sField[cnt].State = FIELD_STATE_FOREST;


		sField[cnt].BackImageCode[0] = FIELD_BACKIMAGE_DAY;
		sField[cnt].BackImageCode[1] = FIELD_BACKIMAGE_GLOWDAY;
		sField[cnt].BackImageCode[2] = FIELD_BACKIMAGE_NIGHTDESERT;
		sField[cnt].BackMusicCode = BGM_CODE_TOWN1;
		sField[cnt].ServerCode = PLAY_SERVER_CODE_USER;
		sField[cnt].SetCenterPos(smConfig.Posi_Stage.x >> FLOATNS, smConfig.Posi_Stage.y >> FLOATNS);

		cnt++;
	}

	FieldCount = cnt;


	if (smWsockServer && smWsockServer == smWsockExtendServer)
	{
		for (cnt = 0; cnt < FieldCount; cnt++)
		{
			if (sField[cnt].ServerCode == PLAY_SERVER_CODE_EXTEND)
			{
				sField[cnt].ServerCode = PLAY_SERVER_CODE_USER;
			}
		}
	}

	return TRUE;
}


sFIELD* PlayNearGateField(sFIELD* lpsField, sFIELD* lpsField2, int x, int y, int z)
{
	int dist = 0;
	int dx = 0, dz = 0;
	sFIELD* NearField = nullptr;
	sFIELD* NearFields[2] = { 0, 0 };
	int ndist = DIST_TRANSLEVEL_CONNECT;
	int dists[2] = { ndist, ndist };

	sFIELD* lpfFirst = lpsField;
	sFIELD* lpfSecond = lpsField2;

	if (lpsField)
	{

		NearField = 0;


		for (int cnt = 0; cnt < lpfFirst->GateCount; cnt++)
		{
			if (lpfFirst->FieldGate[cnt].lpsField != lpfSecond)
			{
				dx = (x >> FLOATNS) - lpfFirst->FieldGate[cnt].x;
				dz = (z >> FLOATNS) - lpfFirst->FieldGate[cnt].z;
				dist = dx * dx + dz * dz;
				if (dist < ndist && abs(dx) < 16384 && abs(dz) < 16384)
				{
					NearField = lpfFirst->FieldGate[cnt].lpsField;
					ndist = dist;
				}
			}
		}

		if (NearField)
		{
			NearFields[0] = NearField;
			dists[0] = ndist;
		}
	}

	lpfFirst = lpsField2;
	lpfSecond = lpsField;

	if (lpsField2)
	{

		NearField = 0;


		for (int cnt = 0; cnt < lpfFirst->GateCount; cnt++)
		{
			if (lpfFirst->FieldGate[cnt].lpsField != lpfSecond)
			{
				dx = (x >> FLOATNS) - lpfFirst->FieldGate[cnt].x;
				dz = (z >> FLOATNS) - lpfFirst->FieldGate[cnt].z;
				dist = dx * dx + dz * dz;
				if (dist < ndist && abs(dx) < 16384 && abs(dz) < 16384)
				{
					NearField = lpfFirst->FieldGate[cnt].lpsField;
					ndist = dist;
				}
			}
		}
		if (NearField)
		{
			NearFields[1] = NearField;
			dists[1] = ndist;
		}
	}



	if ((NearFields[0] && NearFields[1]) || (!NearFields[0] && !NearFields[1]))
		return NULL;


	if (NearFields[0])
	{
		LoadStageFromField(NearFields[0], lpsField);
	}
	else
	{
		LoadStageFromField(NearFields[1], lpsField2);
	}

	return NearField;

}


int StartField()
{

	int StartNum;
	int	JobCode;

	JobCode = lpCurPlayer->smCharInfo.JOB_CODE;
	if (JobCode == 0)
		JobCode = NewCharInfo.JobCode;

	if (JobCode > 4 && JobCode != 9 && sField[START_FIELD_MORYON].szName[0])
		StartNum = START_FIELD_MORYON;
	else
		StartNum = START_FIELD_NUM;

	return WarpFieldNearPos(StartNum, 0, 0, (int*)&smConfig.Posi_Player.x, (int*)&smConfig.Posi_Player.y);
}


int WarpNextField(int* mx, int* mz)
{
	if (SelCount >= FieldCount) SelCount = 0;

	LoadStageFromField(&sField[SelCount], 0);

	*mx = sField[SelCount].cX * fONE;
	*mz = sField[SelCount].cZ * fONE;

	SelCount++;

	return TRUE;
}


int WarpCustomField(int* mx, int* mz)
{
	if (smGameStage[0]) delete smGameStage[0];
	if (smGameStage[1]) delete smGameStage[1];
	StageField[0] = 0;
	StageField[1] = 0;
	smGameStage[0] = 0;
	smGameStage[1] = 0;

	LoadStageFromField(&sField[CustomField], 0);

	*mx = sField[CustomField].cX * fONE;
	*mz = sField[CustomField].cZ * fONE;

	return TRUE;
}


int WarpField(int FieldNum, int* mx, int* mz)
{
#ifdef _DEBUG
	//LOG(LOG_DEBUG, "WARP_FIELD: %d", FieldNum);
#endif

	if (FieldNum >= FIELD_MAX || !sField[FieldNum].szName[0])
	{
		return FALSE;
	}

	LoadStageFromField(&sField[FieldNum], 0);

	if (sField[FieldNum].FieldGate[0].lpsField)
		LoadStageFromField(sField[FieldNum].FieldGate[0].lpsField, &sField[FieldNum]);

	*mx = sField[FieldNum].cX * fONE;
	*mz = sField[FieldNum].cZ * fONE;


	return TRUE;
}


int WarpFieldNearPos(int FieldNum, int x, int z, int* mx, int* mz)
{
	LoadStageFromField(&sField[FieldNum], 0);

	if (sField[FieldNum].FieldGate[0].lpsField)
		LoadStageFromField(sField[FieldNum].FieldGate[0].lpsField, &sField[FieldNum]);

	sField[FieldNum].GetStartPoint(x, z, mx, mz);

	if (lpCurPlayer && lpCurPlayer->Pattern && lpCurPlayer->lpDinaPattern)
	{
		if (StageField[0] == &sField[FieldNum])
			lpCurPlayer->OnStageField = 0;

		if (StageField[1] == &sField[FieldNum])
			lpCurPlayer->OnStageField = 1;
	}

	return TRUE;
}

POINT RestartFieldPosi[2] = {
	{ 1797 , -16553 },
	{ 298 , -16727 }
};
int RestartFieldNum = 3;


int WarpStartField(int* mx, int* mz)
{
	int cnt;
	int	StartNum = START_FIELD_NUM;

	if (lpCurPlayer->smCharInfo.JOB_CODE > 4 && lpCurPlayer->smCharInfo.JOB_CODE != 9 && sField[START_FIELD_MORYON].szName[0])
	{
		StartNum = START_FIELD_MORYON;
	}

	if (sField[StartNum].StartPointCnt == 0)
	{

		return WarpField(StartNum, mx, mz);
	}

	cnt = rand() % sField[StartNum].StartPointCnt;

	return WarpFieldNearPos(StartNum,
		sField[StartNum].StartPoint[cnt].x << FLOATNS,
		sField[StartNum].StartPoint[cnt].y << FLOATNS,
		mx, mz);

}

int	PrisonX = 1746 * fONE;
int	PrisonZ = -19756 * fONE;



RECT	PrisonRect = { 1601 * fONE , -19896 * fONE , 1928 * fONE , -19571 * fONE };


int WarpPrisonField(int* mx, int* mz)
{

	LoadStageFromField(&sField[START_FIELD_NUM], 0);

	if (sField[START_FIELD_NUM].FieldGate[0].lpsField)
		LoadStageFromField(sField[START_FIELD_NUM].FieldGate[0].lpsField, &sField[START_FIELD_NUM]);

	*mx = PrisonX;
	*mz = PrisonZ;

	return TRUE;
}


int WarpStartField(int FieldNum, int* mx, int* mz)
{
	int cnt;

	cnt = rand() % sField[FieldNum].StartPointCnt;

	return WarpFieldNearPos(FieldNum,
		sField[FieldNum].StartPoint[cnt].x << FLOATNS,
		sField[FieldNum].StartPoint[cnt].y << FLOATNS,
		mx, mz);
}

int FieldCheckCount = 0;

int FieldMain(int x, int y, int z)
{
	FieldCheckCount++;


	if ((FieldCheckCount & 0x3F) == 0)
		PlayNearGateField(StageField[0], StageField[1], x, y, z);


	return	TRUE;
}



int	WingWarpGate_Field(int dwFieldCode)
{
	int dist, x, y, z;

	dwNextWarpDelay = 1;
	dwWarpDelayTime = 5000;
	WingWarpField = -1;

	if (!lpLastWarpField) return FALSE;
	if (dwFieldCode < 0) return FALSE;
	if (FieldLimitLevel_Table[dwFieldCode] > lpCurPlayer->smCharInfo.Level) return FALSE;

	x = (lpCurPlayer->pX - lpLastWarpField->PosWarpOut.x) >> FLOATNS;
	y = (lpCurPlayer->pY - lpLastWarpField->PosWarpOut.y) >> FLOATNS;
	z = (lpCurPlayer->pZ - lpLastWarpField->PosWarpOut.z) >> FLOATNS;
	dist = x * x + y * y + z * z;

	if (dist > DIST_TRANSLEVEL_LOW) return FALSE;

	StartEffect(lpCurPlayer->pX, lpCurPlayer->pY + 48 * fONE, lpCurPlayer->pZ, EFFECT_RETURN1);
	SkillPlaySound(SKILL_SOUND_LEARN, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
	dwNextWarpDelay = TRUE;
	dwWarpDelayTime = dwPlayTime - 1000;
	WingWarpField = dwFieldCode;

	return TRUE;
}


int WarpField2(int Num)
{
	int x, z;
	int cnt;


	if (WarpField(Num, &x, &z))
	{
		if (sField[Num].State == FIELD_STATE_CASTLE && sField[Num].StartPointCnt)
		{

			cnt = rand() % sField[Num].StartPointCnt;
			x = sField[Num].StartPoint[cnt].x * fONE;
			z = sField[Num].StartPoint[cnt].y * fONE;
		}

		lpCurPlayer->SetPosi(x, 0, z, 0, 0, 0);
		TraceCameraPosi.x = lpCurPlayer->pX;
		TraceCameraPosi.y = lpCurPlayer->pY;
		TraceCameraPosi.z = lpCurPlayer->pZ;
		TraceTargetPosi.x = lpCurPlayer->pX;
		TraceTargetPosi.y = lpCurPlayer->pY;
		TraceTargetPosi.z = lpCurPlayer->pZ;


		lpCurPlayer->OnStageField = -1;
		if (smGameStage[0])
		{
			cnt = smGameStage[0]->GetFloorHeight(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, lpCurPlayer->Pattern->SizeHeight);
			lpCurPlayer->OnStageField = 0;
		}
		if (cnt == CLIP_OUT && smGameStage[1])
		{
			lpCurPlayer->OnStageField = 1;
		}

		return TRUE;
	}


	return FALSE;
}


#define CASTLE_MASTER_POS_MAX	11
POINT	CastleMasterPos[CASTLE_MASTER_POS_MAX] = {
	{ 33931,  -31110 },
	{ 33931,  -31553 },
	{ 33931,  -31996 },
	{ 33973,  -32440 },
	{ 33863,  -32685 },
	{ 34561,  -32342 },
	{ 35242,  -32685 },
	{ 35203,  -32440 },
	{ 35167,  -31993 },
	{ 35169,  -31553 },
	{ 35175,  -31106 }
};



int WarpCastleField(int MasterClan, int* dx, int* dz)
{
	int x, z;
	int cnt;
	int Num = START_FIELD_CASTLE;


	if (WarpField(Num, &x, &z))
	{

		if (MasterClan)
		{
			cnt = rand() % CASTLE_MASTER_POS_MAX;
			x = CastleMasterPos[cnt].x * fONE;
			z = CastleMasterPos[cnt].y * fONE;
		}
		else if (sField[Num].State == FIELD_STATE_CASTLE && sField[Num].StartPointCnt)
		{

			cnt = rand() % sField[Num].StartPointCnt;
			x = sField[Num].StartPoint[cnt].x * fONE;
			z = sField[Num].StartPoint[cnt].y * fONE;
		}

		if (dx && dz)
		{
			*dx = x;
			*dz = z;
		}

		lpCurPlayer->SetPosi(x, 0, z, 0, 0, 0);
		TraceCameraPosi.x = lpCurPlayer->pX;
		TraceCameraPosi.y = lpCurPlayer->pY;
		TraceCameraPosi.z = lpCurPlayer->pZ;
		TraceTargetPosi.x = lpCurPlayer->pX;
		TraceTargetPosi.y = lpCurPlayer->pY;
		TraceTargetPosi.z = lpCurPlayer->pZ;


		lpCurPlayer->OnStageField = -1;
		if (smGameStage[0])
		{
			cnt = smGameStage[0]->GetFloorHeight(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, lpCurPlayer->Pattern->SizeHeight);
			lpCurPlayer->OnStageField = 0;
		}
		if (cnt == CLIP_OUT && smGameStage[1])
		{
			lpCurPlayer->OnStageField = 1;
		}

		return TRUE;
	}


	return FALSE;
}


