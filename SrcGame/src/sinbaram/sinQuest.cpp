

#include "sinLinkHeader.h"
#include "..\\field.h"

extern bool bcanadd;

sQUEST_CHANGEJOB	sinQuest_ChangeJob;
sQUEST_CHANGEJOB	sinQuest_ChangeJob2;
sQUEST_CHANGEJOB3   sinQuest_ChangeJob3;
sQUEST_CHANGEJOB3   sinQuest_ChangeJob4;


sQUEST_CHANGEJOB3   sinQuest_Level30;
sQUEST_CHANGEJOB3   sinQuest_Level55;
sQUEST_CHANGEJOB3   sinQuest_Level55_2;
sQUEST_CHANGEJOB3   sinQuest_Level70;
sQUEST_CHANGEJOB3   sinQuest_Level80;
sQUEST_CHANGEJOB3   sinQuest_Level85;
sQUEST_CHANGEJOB3   sinQuest_Level90;

sQUEST_CHANGEJOB3   sinQuest_Level80_2;
sQUEST_CHANGEJOB3   sinQuest_Level90_2;

DWORD sinQuest_levelLog = 0;

sITEM TempQuestItem;

int sinChangeJobButtonShow = 0;
int sinChangeJobButtonShow2 = 0;
int sinChangeJobButtonShow3 = 0;
int sinChangeJobButtonShow4 = 0;

int CheckQuestComplete = 0;
int CheckQuestButtonShow1 = 0;
int CheckQuestButtonShow2 = 0;
int CheckQuestButtonShow3 = 0;

POINT QuestMessageBoxPosi2 = { 50,45 };
POINT QuestMessageBoxSize2 = { 9,10 };


char* QuestFilePath[] = {
	"image\\Sinimage\\Quest\\ChangeJob1.sin",
	"image\\Sinimage\\Quest\\ChangeJob2.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M_M1.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M_M2.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M_M3.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M_D1.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M_D2.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M_D3.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M_Success.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M_M0.sin",
	"image\\Sinimage\\Quest\\ChangeJob2M_D0.sin",
	"image\\Sinimage\\Quest\\ChangeJob1.sin",
};

char* QuestFilePath3[] = {
	"image\\Sinimage\\Quest\\ChangeJob3_0.sin",
	"image\\Sinimage\\Quest\\ChangeJob3_1.sin",
	"image\\Sinimage\\Quest\\ChangeJob3_2.sin",
	"image\\Sinimage\\Quest\\ChangeJob3_3.sin",
	"image\\Sinimage\\Quest\\ChangeJob3_4.sin",
	"image\\Sinimage\\Quest\\ChangeJob3_5.sin",
};


char* WingQuestFilePath_a[] = {
	"image\\Sinimage\\Quest\\M_Wing_a.sin",
	"image\\Sinimage\\Quest\\S_Wing_a.sin",
	"image\\Sinimage\\Quest\\G_Wing_a.sin",
	"image\\Sinimage\\Quest\\D_Wing_a.sin",
	"image\\Sinimage\\Quest\\K_wing_a.sin",
	"image\\Sinimage\\Quest\\E_wing_a.sin",
	"image\\Sinimage\\Quest\\Puzzle.sin",

};

char* WingQuestFilePath_b[] = {
	"image\\Sinimage\\Quest\\M_Wing_b.sin",
	"image\\Sinimage\\Quest\\S_Wing_b.sin",
	"image\\Sinimage\\Quest\\G_Wing_b.sin",
	"image\\Sinimage\\Quest\\D_Wing_b.sin",
	"image\\Sinimage\\Quest\\K_wing_b.sin",
	"image\\Sinimage\\Quest\\E_wing_b.sin",
	"image\\Sinimage\\Quest\\Wing_End.sin",

};

char* WarpGateDoc[] = {
	"image\\Sinimage\\WarpGateDoc\\Default.sin",
	"image\\Sinimage\\WarpGateDoc\\Ricarten.sin",
	"image\\Sinimage\\WarpGateDoc\\Pilai.sin",
	"image\\Sinimage\\WarpGateDoc\\Forest2.sin",
	"image\\Sinimage\\WarpGateDoc\\Forest3.sin",
	"image\\Sinimage\\WarpGateDoc\\Ruinen.sin",
	"image\\Sinimage\\WarpGateDoc\\Nevisco.sin",
	"image\\Sinimage\\WarpGateDoc\\Desert4.sin",
	"image\\Sinimage\\WarpGateDoc\\yura.sin",
	"image\\Sinimage\\WarpGateDoc\\chaoticpost.sin",

};
char* HaWarpGateDoc[] = {
	"image\\Sinimage\\WarpGateDoc\\B_Castle.sin"
};

char* WarningInitPoint[] = {
	"image\\Sinimage\\Help\\WarnigWeight.sin",

};
char* BabelEventDoc = "image\\Sinimage\\Quest\\BaBelEvent.sin";
char* NineTailFoxDoc = "image\\Sinimage\\Quest\\NineTailFoxEvent.sin";
char* StarDustDoc = "image\\Sinimage\\Quest\\StarDust.sin";
char* CristalEventDoc = "image\\Sinimage\\Quest\\CristalEvent.sin";


char* WatermelonDoc = "image\\Sinimage\\Quest\\WatermelonEvent.sin";

char* PumpkinDoc = "image\\Sinimage\\Quest\\PumpkinEvent.sin";

char* StarDoc = "image\\Sinimage\\Quest\\StarEvent.sin";

char* ValentineDoc = "image\\Sinimage\\Quest\\ChocolateEvent.sin";

char* PristonAlphabetDoc = "image\\Sinimage\\Quest\\Priston.sin";

char* CandydaysDoc = "image\\Sinimage\\Quest\\CandydaysEvent.sin";

char* MagicalGreenDoc = "image\\Sinimage\\Quest\\MagicalGreenEvent.sin";

char* TearOfKaraDoc = "image\\Sinimage\\Quest\\KarasTears.sin";


char* Findinvestigator1_1Doc = "image\\Sinimage\\Quest\\Resercher_Start.sin";
char* Findinvestigator1_2Doc = "image\\Sinimage\\Quest\\Resercher_Pass1.sin";
char* Findinvestigator1_3Doc = "image\\Sinimage\\Quest\\Resercher_Pass2.sin";
char* Findinvestigator2_1Doc = "image\\Sinimage\\Quest\\Kamiyu_Start.sin";
char* Findinvestigator2_2Doc = "image\\Sinimage\\Quest\\Kamiyu_Pass.sin";
char* Findinvestigator3_1Doc = "image\\Sinimage\\Quest\\Eto_Start.sin";
char* Findinvestigator3_2Doc = "image\\Sinimage\\Quest\\Eto_Pass.sin";

char* LevelQuest30Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest30start.sin",
	"image\\Sinimage\\Quest\\LevelQuest30Path.sin",
	"image\\Sinimage\\Quest\\LevelQuest30end.sin",

};
char* LevelQuest55Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest55start.sin",
	"image\\Sinimage\\Quest\\LevelQuest55Path.sin",
	"image\\Sinimage\\Quest\\LevelQuest55end.sin",

};

char* LevelQuest55_2Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest55-2start.sin",
	"image\\Sinimage\\Quest\\LevelQuest55-2Path.sin",
	"image\\Sinimage\\Quest\\LevelQuest55-2end.sin",

};

char* LevelQuest70Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest70start.sin",
	"image\\Sinimage\\Quest\\LevelQuest70Path.sin",
	"image\\Sinimage\\Quest\\LevelQuest70end.sin",

};
char* LevelQuest80Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest80start.sin",
	"image\\Sinimage\\Quest\\LevelQuest80Path.sin",
	"image\\Sinimage\\Quest\\LevelQuest80end.sin",

};
char* LevelQuest85Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest85start.sin",
	"image\\Sinimage\\Quest\\LevelQuest85Path.sin",
	"image\\Sinimage\\Quest\\LevelQuest85Path2.sin",
	"image\\Sinimage\\Quest\\LevelQuest85end.sin",

};
char* LevelQuest90Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest90start.sin",
	"image\\Sinimage\\Quest\\LevelQuest90Path.sin",
	"image\\Sinimage\\Quest\\LevelQuest90end.sin",

};

char* LevelQuest80_2Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest80_2start.sin",
	"image\\Sinimage\\Quest\\LevelQuest80_2start2.sin",
	"image\\Sinimage\\Quest\\LevelQuest80_2Path.sin",
	"image\\Sinimage\\Quest\\LevelQuest80_2Path2.sin",
	"image\\Sinimage\\Quest\\LevelQuest80_2end.sin",

};

char* LevelQuest90_2Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest90_2start.sin",
	"image\\Sinimage\\Quest\\LevelQuest90_2start2.sin",
	"image\\Sinimage\\Quest\\LevelQuest90_2Path.sin",
	"image\\Sinimage\\Quest\\LevelQuest90_2Path2.sin",
	"image\\Sinimage\\Quest\\LevelQuest90_2end.sin",

};

char* QuestFilePath4[] = {
	"image\\Sinimage\\Quest\\ChangeJob4_1Start.sin",
	"image\\Sinimage\\Quest\\ChangeJob4_1Path.sin",
	"image\\Sinimage\\Quest\\ChangeJob4_2Start.sin",
	"image\\Sinimage\\Quest\\ChangeJob4_2Path.sin",
	"image\\Sinimage\\Quest\\ChangeJob4_3Start.sin",
	"image\\Sinimage\\Quest\\ChangeJob4_3Path.sin",
	"image\\Sinimage\\Quest\\ChangeJob4_4Start.sin",
	"image\\Sinimage\\Quest\\ChangeJob4_4End.sin",

};


int sinCheckChageJob()
{
	if (sinChar->Level >= 20 && sinChar->ChangeJob <= 0) {
		sinChar->ChangeJob = 1;
	}

	if (sinChar->Level >= 40 && sinChar->ChangeJob <= 1) {
		sinChar->ChangeJob = 2;
	}

	if (sinChar->Level >= 60 && sinChar->ChangeJob <= 2) {
		sinChar->ChangeJob = 3;
	}

	return TRUE;
}


//int sinCheckChageJob()
//{
//	if(CheckQuestButtonShow1 && sinChar->Level >= 20 && sinChar->ChangeJob == 0)
//	{
//		if(!sinQuest_ChangeJob.CODE && sinChar->JOB_CODE <= 4 || sinChar->JOB_CODE == 9)
//			sinChangeJobButtonShow = 1;
//		else
//		{
//			if(!FindLastQuestCode(SIN_QUEST_CODE_CHANGEJOB2_NPC_M) && !FindLastQuestCode(SIN_QUEST_CODE_CHANGEJOB2_NPC_D) && sinChar->ChangeJob < 1)
//				sinChangeJobButtonShow2 = 1;
//		}
//	}
//	if(CheckQuestButtonShow2&& sinChar->Level >= 40 && sinChar->ChangeJob == 1)
//	{
//		if(!sinQuest_ChangeJob3.CODE && !FindLastQuestCode(SIN_QUEST_CODE_CHANGEJOB3))
//		{
//			sinChangeJobButtonShow3 = 1;
//
//			switch(sinChar->ChangeJob)
//			{
//			case 0:	ChangeJobSkillPlus = 5;	break;
//			case 1:	ChangeJobSkillPlus = 9;	break;
//			case 2:	ChangeJobSkillPlus = 13; break;
//			case 3: ChangeJobSkillPlus = 17; break;
//			}
//			for(int i = 1; i < ChangeJobSkillPlus; i++)
//			{
//				if(!sinSkill.UseSkill[i].Point)
//					sinChangeJobButtonShow3 = 0;
//			}
//
//		}
//	}
//	if(CheckQuestButtonShow3 && sinChar->Level >= 60 && sinChar->ChangeJob == 2)
//	{
//		if(!sinQuest_ChangeJob4.CODE)
//		{
//			sinChangeJobButtonShow4 = 1;
//			switch(sinChar->ChangeJob)
//			{
//			case 0:	ChangeJobSkillPlus = 5;	break;
//			case 1:	ChangeJobSkillPlus = 9;	break;
//			case 2:	ChangeJobSkillPlus = 13; break;
//			case 3: ChangeJobSkillPlus = 17; break;
//			}
//			for(int i = 1; i < ChangeJobSkillPlus; i++)
//			{
//				if(!sinSkill.UseSkill[i].Point)
//					sinChangeJobButtonShow4 = 0;
//			}
//		}
//	}
//	return TRUE;
//}
//
int sinLoadQuest(int CODE, void* Buff)
{

	if (CODE == SIN_QUEST_CODE_CHANGEJOB)
	{
		memcpy(&sinQuest_ChangeJob, Buff, sizeof(sQUEST_CHANGEJOB));
	}
	if (CODE == SIN_QUEST_CODE_CHANGEJOB2_NPC_M || CODE == SIN_QUEST_CODE_CHANGEJOB2_NPC_D)
	{
		memcpy(&sinQuest_ChangeJob2, Buff, sizeof(sQUEST_CHANGEJOB));
	}
	if (CODE == SIN_QUEST_CODE_CHANGEJOB3)
	{
		memcpy(&sinQuest_ChangeJob3, Buff, sizeof(sQUEST_CHANGEJOB3));
	}
	if (CODE == SIN_QUEST_CODE_LEVEL30)
	{
		memcpy(&sinQuest_Level30, Buff, sizeof(sQUEST_CHANGEJOB3));
	}
	if (CODE == SIN_QUEST_CODE_LEVEL55)
	{
		memcpy(&sinQuest_Level55, Buff, sizeof(sQUEST_CHANGEJOB3));
	}
	if (CODE == SIN_QUEST_CODE_LEVEL55_2)
	{
		memcpy(&sinQuest_Level55_2, Buff, sizeof(sQUEST_CHANGEJOB3));
	}
	if (CODE == SIN_QUEST_CODE_LEVEL70)
	{
		memcpy(&sinQuest_Level70, Buff, sizeof(sQUEST_CHANGEJOB3));
	}
	if (CODE == SIN_QUEST_CODE_LEVEL80)
	{
		memcpy(&sinQuest_Level80, Buff, sizeof(sQUEST_CHANGEJOB3));
	}
	if (CODE == SIN_QUEST_CODE_LEVEL85)
	{
		memcpy(&sinQuest_Level85, Buff, sizeof(sQUEST_CHANGEJOB3));
	}
	if (CODE == SIN_QUEST_CODE_LEVEL90)
	{
		memcpy(&sinQuest_Level90, Buff, sizeof(sQUEST_CHANGEJOB3));
	}
	if (CODE == SIN_QUEST_CODE_LEVEL80_2)
	{
		memcpy(&sinQuest_Level80_2, Buff, sizeof(sQUEST_CHANGEJOB3));
	}
	if (CODE == SIN_QUEST_CODE_LEVEL90_2)
	{
		memcpy(&sinQuest_Level90_2, Buff, sizeof(sQUEST_CHANGEJOB3));
	}
	if (CODE == SIN_QUEST_CODE_CHANGEJOB4)
	{
		memcpy(&sinQuest_ChangeJob4, Buff, sizeof(sQUEST_CHANGEJOB3));
		if (sinQuest_ChangeJob4.AgingCount)
		{
			if (sinQuest_ChangeJob4.State == 3 || sinQuest_ChangeJob4.State == 1)
			{
				sinSetQuestTimer(&sinQuest_ChangeJob4, sinQuest_ChangeJob4.AgingCount, sinQuest_ChangeJob4.StartLevel);
				if (sinQuest_ChangeJob4.Kind)
					strcpy_s(szQuestMonsterName, sinGetMonsterName(sinQuest_ChangeJob4.Kind));
			}
		}
	}

	if (CODE == HAQUEST_CODE_ELEMENTARY_A)
	{
		memcpy(&chaQuest.sHaQuestElementary[Quest_A], Buff, sizeof(sQUEST_ELEMENTARY));
	}
	if (CODE == HAQUEST_CODE_ELEMENTARY_B)
	{
		chaQuest.QuestKeyCode = Quest_B;
		memcpy(&chaQuest.sHaQuestElementary[Quest_B], Buff, sizeof(sQUEST_ELEMENTARY));
		if (chaQuest.sHaQuestElementary[Quest_B].State == 100)
		{
			chaQuest.sHaQuestElementary[Quest_B].State = 3;
		}
		if (chaQuest.sHaQuestElementary[Quest_B].State == 2 || chaQuest.sHaQuestElementary[Quest_B].State == 3)
		{
			chaQuest.haSetQuestTimer(&chaQuest.sHaQuestElementary[Quest_B]);
			if (sinChar->JOB_CODE < 12)
				strcpy_s(chaQuest.szQuestMonsterName, haQuestMonsterName[0]);
			else
				strcpy_s(chaQuest.szQuestMonsterName, haQuestMonsterName[1]);
		}
	}
	if (CODE == HAQUEST_CODE_ELEMENTARY_C)
	{
		memcpy(&chaQuest.sHaQuestElementary[Quest_C], Buff, sizeof(sQUEST_ELEMENTARY));
	}
	if (CODE == HAQUEST_CODE_ELEMENTARY_D)
	{
		chaQuest.QuestKeyCode = Quest_D;
		memcpy(&chaQuest.sHaQuestElementary[Quest_D], Buff, sizeof(sQUEST_ELEMENTARY));
		if (chaQuest.sHaQuestElementary[Quest_D].State == 100)
		{
			chaQuest.sHaQuestElementary[Quest_D].State = 3;
		}
		if (chaQuest.sHaQuestElementary[Quest_D].State == 2 || chaQuest.sHaQuestElementary[Quest_D].State == 3)
		{
			chaQuest.haSetQuestTimer(&chaQuest.sHaQuestElementary[Quest_D]);
			if (sinChar->JOB_CODE < 12)
				strcpy_s(chaQuest.szQuestMonsterName, haQuestMonsterName[2]);
			else
				strcpy_s(chaQuest.szQuestMonsterName, haQuestMonsterName[3]);
		}

	}
	if (CODE == HAQUEST_CODE_ELEMENTARY_E)
	{
		chaQuest.QuestKeyCode = Quest_E;
		memcpy(&chaQuest.sHaQuestElementary[Quest_E], Buff, sizeof(sQUEST_ELEMENTARY));
		if (chaQuest.sHaQuestElementary[Quest_E].State == 100)
		{
			chaQuest.sHaQuestElementary[Quest_E].State = 3;
		}
		if (chaQuest.sHaQuestElementary[Quest_E].State == 2 || chaQuest.sHaQuestElementary[Quest_E].State == 3)
		{
			chaQuest.haSetQuestTimer(&chaQuest.sHaQuestElementary[Quest_E]);
			if (sinChar->JOB_CODE < 12)
				strcpy_s(chaQuest.szQuestMonsterName, haQuestMonsterName[4]);
			else
				strcpy_s(chaQuest.szQuestMonsterName, haQuestMonsterName[5]);
		}

	}
	if (CODE == HAQUEST_CODE_ELEMENTARY_F)
	{
		chaQuest.QuestKeyCode = Quest_F;
		memcpy(&chaQuest.sHaQuestElementary[Quest_F], Buff, sizeof(sQUEST_ELEMENTARY));
		if (chaQuest.sHaQuestElementary[Quest_F].State == 100)
		{
			chaQuest.sHaQuestElementary[Quest_F].State = 3;
		}
		if (chaQuest.sHaQuestElementary[Quest_F].State == 2 || chaQuest.sHaQuestElementary[Quest_F].State == 3)
		{
			chaQuest.haSetQuestTimer(&chaQuest.sHaQuestElementary[Quest_F]);
			strcpy_s(chaQuest.szQuestMonsterName, haQuestMonsterName[6]);
		}
	}
	if (CODE == HAQUEST_CODE_ELEMENTARY_G)
	{
		memcpy(&chaQuest.sHaQuestElementary[Quest_G], Buff, sizeof(sQUEST_ELEMENTARY));
	}

	if (CODE == HAQUEST_CODE_FURYOFPHANTOM)
	{
		memcpy(&chaQuest.sHaQuest100LV, Buff, sizeof(sQUEST_ELEMENTARY));

		if (chaQuest.sHaQuest100LV.State == 2 || chaQuest.sHaQuest100LV.State == 3)
		{
			chaQuest.haSetQuestTimer(&chaQuest.sHaQuest100LV);
			strcpy_s(chaQuest.szQuestMonsterName, ha100LVQuestMonterName[0]);
		}
		if (chaQuest.sHaQuest100LV.State == 7 || chaQuest.sHaQuest100LV.State == 8)
		{
			chaQuest.haSetQuestTimer(&chaQuest.sHaQuest100LV);
			strcpy_s(chaQuest.szQuestMonsterName, ha100LVQuestMonterName[1]);
		}
	}



	return TRUE;
}


int sinSaveQuest(void* Buff)
{


	int ContinueSkillIndex = 0;
	if (sinQuest_ChangeJob4.CODE == SIN_QUEST_CODE_CHANGEJOB4)
	{
		if (ContinueSkillIndex = cSkill.SearchContiueSkillIndex(CHANGE_JOB3_QUEST))
		{
			sinQuest_ChangeJob4.AgingCount = ContinueSkill[ContinueSkillIndex - 1].UseTime;
			sinQuest_ChangeJob4.StartLevel = ContinueSkill[ContinueSkillIndex - 1].CheckTime;
		}
		memcpy(Buff, &sinQuest_ChangeJob4, sizeof(sQUEST_CHANGEJOB3));
		return sinQuest_ChangeJob4.CODE;
	}


	if (sinQuest_ChangeJob3.CODE == SIN_QUEST_CODE_CHANGEJOB3)
	{
		memcpy(Buff, &sinQuest_ChangeJob3, sizeof(sQUEST_CHANGEJOB3));
		return sinQuest_ChangeJob3.CODE;
	}


	if (sinQuest_ChangeJob.CODE == SIN_QUEST_CODE_CHANGEJOB)
	{

		memcpy(Buff, &sinQuest_ChangeJob, sizeof(sQUEST_CHANGEJOB));
		return sinQuest_ChangeJob.CODE;
	}

	if (sinQuest_ChangeJob2.CODE == SIN_QUEST_CODE_CHANGEJOB2_NPC_M ||
		sinQuest_ChangeJob2.CODE == SIN_QUEST_CODE_CHANGEJOB2_NPC_D)
	{
		memcpy(Buff, &sinQuest_ChangeJob2, sizeof(sQUEST_CHANGEJOB));
		return sinQuest_ChangeJob2.CODE;
	}


	if (sinQuest_Level30.CODE == SIN_QUEST_CODE_LEVEL30)
	{
		memcpy(Buff, &sinQuest_Level30, sizeof(sQUEST_CHANGEJOB3));
		return sinQuest_Level30.CODE;
	}

	if (sinQuest_Level55.CODE == SIN_QUEST_CODE_LEVEL55)
	{
		memcpy(Buff, &sinQuest_Level55, sizeof(sQUEST_CHANGEJOB3));
		return sinQuest_Level55.CODE;
	}

	if (sinQuest_Level55_2.CODE == SIN_QUEST_CODE_LEVEL55_2)
	{
		memcpy(Buff, &sinQuest_Level55_2, sizeof(sQUEST_CHANGEJOB3));
		return sinQuest_Level55_2.CODE;
	}

	if (sinQuest_Level70.CODE == SIN_QUEST_CODE_LEVEL70)
	{
		memcpy(Buff, &sinQuest_Level70, sizeof(sQUEST_CHANGEJOB3));
		return sinQuest_Level70.CODE;
	}

	if (sinQuest_Level80.CODE == SIN_QUEST_CODE_LEVEL80)
	{
		memcpy(Buff, &sinQuest_Level80, sizeof(sQUEST_CHANGEJOB3));
		return sinQuest_Level80.CODE;
	}


	if (sinQuest_Level85.CODE == SIN_QUEST_CODE_LEVEL85)
	{
		memcpy(Buff, &sinQuest_Level85, sizeof(sQUEST_CHANGEJOB3));
		return sinQuest_Level85.CODE;
	}

	if (sinQuest_Level90.CODE == SIN_QUEST_CODE_LEVEL90)
	{
		memcpy(Buff, &sinQuest_Level90, sizeof(sQUEST_CHANGEJOB3));
		return sinQuest_Level90.CODE;
	}


	if (sinQuest_Level80_2.CODE == SIN_QUEST_CODE_LEVEL80_2)
	{
		memcpy(Buff, &sinQuest_Level80_2, sizeof(sQUEST_CHANGEJOB3));
		return sinQuest_Level80_2.CODE;
	}

	if (sinQuest_Level90_2.CODE == SIN_QUEST_CODE_LEVEL90_2)
	{
		memcpy(Buff, &sinQuest_Level90_2, sizeof(sQUEST_CHANGEJOB3));
		return sinQuest_Level90_2.CODE;
	}

	if (chaQuest.sHaQuestElementary[Quest_A].CODE == HAQUEST_CODE_ELEMENTARY_A)
	{
		memcpy(Buff, &chaQuest.sHaQuestElementary[Quest_A], sizeof(sQUEST_ELEMENTARY));
		return chaQuest.sHaQuestElementary[Quest_A].CODE;
	}
	if (chaQuest.sHaQuestElementary[Quest_B].CODE == HAQUEST_CODE_ELEMENTARY_B)
	{
		memcpy(Buff, &chaQuest.sHaQuestElementary[Quest_B], sizeof(sQUEST_ELEMENTARY));
		return chaQuest.sHaQuestElementary[Quest_B].CODE;
	}
	if (chaQuest.sHaQuestElementary[Quest_C].CODE == HAQUEST_CODE_ELEMENTARY_C)
	{
		memcpy(Buff, &chaQuest.sHaQuestElementary[Quest_C], sizeof(sQUEST_ELEMENTARY));
		return chaQuest.sHaQuestElementary[Quest_C].CODE;
	}
	if (chaQuest.sHaQuestElementary[Quest_D].CODE == HAQUEST_CODE_ELEMENTARY_D)
	{
		memcpy(Buff, &chaQuest.sHaQuestElementary[Quest_D], sizeof(sQUEST_ELEMENTARY));
		return chaQuest.sHaQuestElementary[Quest_D].CODE;
	}
	if (chaQuest.sHaQuestElementary[Quest_E].CODE == HAQUEST_CODE_ELEMENTARY_E)
	{
		memcpy(Buff, &chaQuest.sHaQuestElementary[Quest_E], sizeof(sQUEST_ELEMENTARY));
		return chaQuest.sHaQuestElementary[Quest_E].CODE;
	}
	if (chaQuest.sHaQuestElementary[Quest_F].CODE == HAQUEST_CODE_ELEMENTARY_F)
	{
		memcpy(Buff, &chaQuest.sHaQuestElementary[Quest_F], sizeof(sQUEST_ELEMENTARY));
		return chaQuest.sHaQuestElementary[Quest_F].CODE;
	}
	if (chaQuest.sHaQuestElementary[Quest_G].CODE == HAQUEST_CODE_ELEMENTARY_G)
	{
		memcpy(Buff, &chaQuest.sHaQuestElementary[Quest_G], sizeof(sQUEST_ELEMENTARY));
		return chaQuest.sHaQuestElementary[Quest_G].CODE;
	}

	if (chaQuest.sHaQuest100LV.CODE == HAQUEST_CODE_FURYOFPHANTOM)
	{
		memcpy(Buff, &chaQuest.sHaQuest100LV, sizeof(sQUEST_ELEMENTARY));
		return chaQuest.sHaQuest100LV.CODE;
	}
	return FALSE;
}


int sinMorayionNpcChangeJob_Two()
{


	int i = 0;

	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (cInvenTory.InvenItem[i].Flag)
		{
			if (cInvenTory.InvenItem[i].CODE == (sinQT1 | sin04) ||
				cInvenTory.InvenItem[i].CODE == (sinQT1 | sin05))
			{
				sinQuest_ChangeJob2.State = 3;

				cInvenTory.InvenItem[i].Flag = 0;
				cInvenTory.ReFormInvenItem();
				break;
			}
		}
		if (cInvenTory.InvenItemTemp[i].Flag)
		{
			if (cInvenTory.InvenItemTemp[i].CODE == (sinQT1 | sin04) ||
				cInvenTory.InvenItemTemp[i].CODE == (sinQT1 | sin05))
			{
				sinQuest_ChangeJob2.State = 3;
				cInvenTory.InvenItemTemp[i].Flag = 0;
				cInvenTory.ReFormInvenItem();
				break;
			}
		}
	}

	if (sinQuest_ChangeJob2.CODE == SIN_QUEST_CODE_CHANGEJOB2_NPC_M)
	{

		switch (sinQuest_ChangeJob2.State)
		{
		case 1:
			cSinHelp.sinShowHelp(SIN_MESSAGE_DEFAULT, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath[3]);
			sinQuest_ChangeJob2.State = 2;
			break;
		case 2:
			cSinHelp.sinShowHelp(SIN_MESSAGE_DEFAULT, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath[4]);
			break;
		case 3:
			cSinHelp.sinShowHelp(SIN_MESSAGE_DEFAULT, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath[5]);
			sinQuest_ChangeJob2.State = 4;
			sinQuest_ChangeJob2.BackUpCode = sinQuest_ChangeJob2.CODE;
			sinQuest_ChangeJob2.CODE = 0;
			EndQuest_Code(sinQuest_ChangeJob2.BackUpCode);
			sinQuest_ChangeJob2.CODE = 0;
			sinChar->wVersion[1] = 0;


			break;
		}
	}
	if (sinQuest_ChangeJob2.CODE == SIN_QUEST_CODE_CHANGEJOB2_NPC_D)
	{
		switch (sinQuest_ChangeJob2.State)
		{
		case 1:
			cSinHelp.sinShowHelp(SIN_MESSAGE_DEFAULT, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath[6]);
			sinQuest_ChangeJob2.State = 2;
			break;
		case 2:
			cSinHelp.sinShowHelp(SIN_MESSAGE_DEFAULT, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath[7]);
			break;
		case 3:
			cSinHelp.sinShowHelp(SIN_MESSAGE_DEFAULT, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath[8]);
			sinQuest_ChangeJob2.BackUpCode = sinQuest_ChangeJob2.CODE;
			sinQuest_ChangeJob2.CODE = 0;
			EndQuest_Code(sinQuest_ChangeJob2.BackUpCode);
			sinQuest_ChangeJob2.CODE = 0;
			sinChar->wVersion[1] = 0;

			break;
		}
	}
	return TRUE;
}

int sinNpcChangeJob3()
{
	sITEM* pItem = 0;
	int   Count = 0;
	int   i = 0;
	int   TempItemIndex[3] = { 0,0,0 };

	if (!sinQuest_ChangeJob3.CODE)return FALSE;

	if (sinQuest_ChangeJob3.State == 1)
	{
		for (i = 0; i < INVENTORY_MAXITEM * 2; i++)
		{
			if (i < 100)
			{
				if (!cInvenTory.InvenItem[i].Flag)continue;
				pItem = &cInvenTory.InvenItem[i];
			}
			else
			{
				if (!cInvenTory.InvenItemTemp[i - 100].Flag)continue;
				pItem = &cInvenTory.InvenItemTemp[i - 100];
			}

			if (pItem->sItemInfo.CODE == (sinQT1 | sin06))
			{
				TempItemIndex[Count] = i;
				Count++;
			}
		}


		if (Count >= 3)
		{
			sinQuest_ChangeJob3.State = 2;
			memset(&sWingItem_Send, 0, sizeof(sCRAFTITEM_SERVER));
			for (int j = 0; j < Count; j++)
			{
				if (TempItemIndex[j] < 100)
				{

					sWingItem_Send.SheltomCode[j] = cInvenTory.InvenItem[TempItemIndex[j]].sItemInfo.CODE;
					sWingItem_Send.Head[j] = cInvenTory.InvenItem[TempItemIndex[j]].sItemInfo.ItemHeader.Head;
					sWingItem_Send.CheckSum[j] = cInvenTory.InvenItem[TempItemIndex[j]].sItemInfo.ItemHeader.dwChkSum;

				}
				else
				{

					sWingItem_Send.SheltomCode[j] = cInvenTory.InvenItemTemp[TempItemIndex[j]].sItemInfo.CODE;
					sWingItem_Send.Head[j] = cInvenTory.InvenItemTemp[TempItemIndex[j]].sItemInfo.ItemHeader.Head;
					sWingItem_Send.CheckSum[j] = cInvenTory.InvenItemTemp[TempItemIndex[j]].sItemInfo.ItemHeader.dwChkSum;

				}
			}
			cInvenTory.ReFormInvenItem();
		}
	}

	switch (sinQuest_ChangeJob3.State)
	{
	case 1:


		break;
	case 2:
		cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath3[2]);
		return TRUE;
		break;
	case 3:


		break;
	case 4:
		cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath3[4]);
		return TRUE;
		break;
	case 6:
		cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath3[5]);
		break;
	}
	return FALSE;
}



int DeleteQuestItem(DWORD CODE)
{
	sITEM* pItem = 0;
	int i = 0;
	for (i = 0; i < INVENTORY_MAXITEM * 2; i++)
	{
		if (i < 100)
		{
			if (!cInvenTory.InvenItem[i].Flag)continue;
			pItem = &cInvenTory.InvenItem[i];
		}
		else
		{
			if (!cInvenTory.InvenItemTemp[i - 100].Flag)continue;
			pItem = &cInvenTory.InvenItemTemp[i - 100];
		}

		if (pItem->sItemInfo.CODE == CODE)
		{
			pItem->Flag = 0;
			if (i < 100)
			{
				if (pItem->ItemPosition)
				{
					sInven[pItem->ItemPosition - 1].ItemIndex = 0;
					if (pItem->SetModelPosi)
						sinSetCharItem(pItem->CODE, pItem->SetModelPosi, FALSE);

				}
			}
		}
	}
	cInvenTory.ReFormInvenItem();
	ReformCharForm();
	cInvenTory.ReFormPotionNum();
	cInvenTory.SetItemToChar();
	cInvenTory.CheckWeight();
	return TRUE;
}

int  QuestMonsterCount[] = { 30,40,50,25,35,45,50,70,100 };
int CheckChangeJob3QuestItem(DWORD Monster_CODE)
{

	if (Monster_CODE == 100)return false;


	char szTemp[128];
	char szBuff[128];
	memset(&szTemp, 0, sizeof(szTemp));

	if (chaQuest.sHaQuest100LV.CODE)
	{
		if (chaQuest.sHaQuest100LV.Kind)
		{
			if (chaQuest.sHaQuest100LV.State == 2 && StageField[lpCurPlayer->OnStageField]->FieldCode == 28)
			{
				chaQuest.sHaQuest100LV.Monster[0]++;

#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp, sinLevelQusetDoc, chaQuest.sHaQuest100LV.Monster[0], ha100LVQuestMonterName[0]);
#else
				wsprintf(szTemp, sinLevelQusetDoc, ha100LVQuestMonterName[0], chaQuest.sHaQuest100LV.Monster[0]);
#endif

				AddChatBuff(szTemp, 9);
				if (chaQuest.sHaQuest100LV.Monster[0] == chaQuest.sHaQuest100LV.Monster[1])
				{
#ifdef	_LANGUAGE_ENGLISH
					wsprintf(szBuff, sinLevelQusetDoc4, chaQuest.sHaQuest100LV.Monster[1], ha100LVQuestMonterName[0]);
#else
#ifdef	_LANGUAGE_BRAZIL
					wsprintf(szBuff, sinLevelQusetDoc4, chaQuest.sHaQuest100LV.Monster[1], ha100LVQuestMonterName[0]);
#else
#ifdef	_LANGUAGE_ARGENTINA
					wsprintf(szBuff, sinLevelQusetDoc4, chaQuest.sHaQuest100LV.Monster[1], ha100LVQuestMonterName[0]);
#else
#ifdef _LANGUAGE_CHINESE
					wsprintf(szBuff, sinLevelQusetDoc4, chaQuest.sHaQuest100LV.Monster[1], ha100LVQuestMonterName[0]);
#else
					wsprintf(szBuff, sinLevelQusetDoc4, ha100LVQuestMonterName[0], chaQuest.sHaQuest100LV.Monster[1]);
#endif
#endif
#endif
#endif
					cMessageBox.ShowMessageEvent(szBuff);
					chaQuest.sHaQuest100LV.Kind = 0;
					chaQuest.sHaQuest100LV.State = 3;
				}
			}
			if (chaQuest.sHaQuest100LV.State == 7 && StageField[lpCurPlayer->OnStageField]->FieldCode == 31)
			{
				chaQuest.sHaQuest100LV.Monster[0]++;

#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp, sinLevelQusetDoc, chaQuest.sHaQuest100LV.Monster[0], ha100LVQuestMonterName[1]);
#else
				wsprintf(szTemp, sinLevelQusetDoc, ha100LVQuestMonterName[1], chaQuest.sHaQuest100LV.Monster[0]);
#endif

				AddChatBuff(szTemp, 9);
				if (chaQuest.sHaQuest100LV.Monster[0] == chaQuest.sHaQuest100LV.Monster[1])
				{
#ifdef	_LANGUAGE_ENGLISH
					wsprintf(szBuff, sinLevelQusetDoc4, chaQuest.sHaQuest100LV.Monster[1], ha100LVQuestMonterName[1]);
#else
#ifdef	_LANGUAGE_BRAZIL
					wsprintf(szBuff, sinLevelQusetDoc4, chaQuest.sHaQuest100LV.Monster[1], ha100LVQuestMonterName[0]);
#else
#ifdef	_LANGUAGE_ARGENTINA
					wsprintf(szBuff, sinLevelQusetDoc4, chaQuest.sHaQuest100LV.Monster[1], ha100LVQuestMonterName[0]);
#else
#ifdef _LANGUAGE_CHINESE
					wsprintf(szBuff, sinLevelQusetDoc4, chaQuest.sHaQuest100LV.Monster[1], ha100LVQuestMonterName[1]);
#else
					wsprintf(szBuff, sinLevelQusetDoc4, ha100LVQuestMonterName[1], chaQuest.sHaQuest100LV.Monster[1]);
#endif
#endif
#endif
#endif
					cMessageBox.ShowMessageEvent(szBuff);
					chaQuest.sHaQuest100LV.Kind = 0;
					chaQuest.sHaQuest100LV.State = 8;
				}

			}
		}
	}


	if (chaQuest.sHaQuestElementary[Quest_B].CODE)
	{
		if (chaQuest.sHaQuestElementary[Quest_B].Kind && chaQuest.sHaQuestElementary[Quest_B].Kind == Monster_CODE)
		{
			chaQuest.sHaQuestElementary[Quest_B].Monster[0]++;
			if (sinChar->JOB_CODE < 12)
#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp, sinLevelQusetDoc, chaQuest.sHaQuestElementary[Quest_B].Monster[0], haQuestMonsterName[0]);
#else
				wsprintf(szTemp, sinLevelQusetDoc, haQuestMonsterName[0], chaQuest.sHaQuestElementary[Quest_B].Monster[0]);
#endif
			else
#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp, sinLevelQusetDoc, chaQuest.sHaQuestElementary[Quest_B].Monster[0], haQuestMonsterName[1]);
#else
				wsprintf(szTemp, sinLevelQusetDoc, haQuestMonsterName[1], chaQuest.sHaQuestElementary[Quest_B].Monster[0]);
#endif

			AddChatBuff(szTemp, 9);
			if (chaQuest.sHaQuestElementary[Quest_B].Monster[0] == chaQuest.sHaQuestElementary[Quest_B].Monster[1])
			{
#ifdef	_LANGUAGE_ENGLISH
				wsprintf(szBuff, sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_B].Monster[1], szQuestMonsterName);
#else
#ifdef	_LANGUAGE_BRAZIL
				wsprintf(szBuff, sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_B].Monster[1], szQuestMonsterName);
#else
#ifdef	_LANGUAGE_ARGENTINA
				wsprintf(szBuff, sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_B].Monster[1], szQuestMonsterName);
#else
#ifdef	_LANGUAGE_CHINESE
				wsprintf(szBuff, sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_B].Monster[1], szQuestMonsterName);
#else
				wsprintf(szBuff, sinLevelQusetDoc4, szQuestMonsterName, chaQuest.sHaQuestElementary[Quest_B].Monster[1]);
#endif
#endif
#endif
#endif
				cMessageBox.ShowMessageEvent(szBuff);
				chaQuest.sHaQuestElementary[Quest_B].Kind = 0;
				chaQuest.sHaQuestElementary[Quest_B].State = 3;
			}

		}
	}

	if (chaQuest.sHaQuestElementary[Quest_D].CODE)
	{
		if (chaQuest.sHaQuestElementary[Quest_D].Kind && chaQuest.sHaQuestElementary[Quest_D].Kind == Monster_CODE)
		{
			chaQuest.sHaQuestElementary[Quest_D].Monster[0]++;
			if (sinChar->JOB_CODE < 12)
#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp, sinLevelQusetDoc, chaQuest.sHaQuestElementary[Quest_D].Monster[0], haQuestMonsterName[2]);
#else
				wsprintf(szTemp, sinLevelQusetDoc, haQuestMonsterName[2], chaQuest.sHaQuestElementary[Quest_D].Monster[0]);
#endif
			else
#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp, sinLevelQusetDoc, chaQuest.sHaQuestElementary[Quest_D].Monster[0], haQuestMonsterName[3]);
#else
				wsprintf(szTemp, sinLevelQusetDoc, haQuestMonsterName[3], chaQuest.sHaQuestElementary[Quest_D].Monster[0]);
#endif

			AddChatBuff(szTemp, 9);
			if (chaQuest.sHaQuestElementary[Quest_D].Monster[0] == chaQuest.sHaQuestElementary[Quest_D].Monster[1])
			{
#ifdef	_LANGUAGE_ENGLISH
				wsprintf(szBuff, sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_D].Monster[1], szQuestMonsterName);
#else
#ifdef	_LANGUAGE_BRAZIL
				wsprintf(szBuff, sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_D].Monster[1], szQuestMonsterName);
#else
#ifdef	_LANGUAGE_ARGENTINA
				wsprintf(szBuff, sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_D].Monster[1], szQuestMonsterName);
#else
#ifdef	_LANGUAGE_CHINESE
				wsprintf(szBuff, sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_D].Monster[1], szQuestMonsterName);
#else
				wsprintf(szBuff, sinLevelQusetDoc4, szQuestMonsterName, chaQuest.sHaQuestElementary[Quest_D].Monster[1]);
#endif
#endif
#endif
#endif
				cMessageBox.ShowMessageEvent(szBuff);
				chaQuest.sHaQuestElementary[Quest_D].Kind = 0;
				chaQuest.sHaQuestElementary[Quest_D].State = 3;
			}

		}
	}

	if (chaQuest.sHaQuestElementary[Quest_E].CODE)
	{
		if (chaQuest.sHaQuestElementary[Quest_E].Kind && chaQuest.sHaQuestElementary[Quest_E].Kind == Monster_CODE)
		{
			chaQuest.sHaQuestElementary[Quest_E].Monster[0]++;
			if (sinChar->JOB_CODE < 12)
#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp, sinLevelQusetDoc, chaQuest.sHaQuestElementary[Quest_E].Monster[0], haQuestMonsterName[4]);
#else
				wsprintf(szTemp, sinLevelQusetDoc, haQuestMonsterName[4], chaQuest.sHaQuestElementary[Quest_E].Monster[0]);
#endif
			else
#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp, sinLevelQusetDoc, chaQuest.sHaQuestElementary[Quest_E].Monster[0], haQuestMonsterName[5]);
#else
				wsprintf(szTemp, sinLevelQusetDoc, haQuestMonsterName[5], chaQuest.sHaQuestElementary[Quest_E].Monster[0]);
#endif

			AddChatBuff(szTemp, 9);
			if (chaQuest.sHaQuestElementary[Quest_E].Monster[0] == chaQuest.sHaQuestElementary[Quest_E].Monster[1])
			{
#ifdef	_LANGUAGE_ENGLISH
				wsprintf(szBuff, sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_E].Monster[1], szQuestMonsterName);
#else
#ifdef	_LANGUAGE_BRAZIL
				wsprintf(szBuff, sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_E].Monster[1], szQuestMonsterName);
#else
#ifdef	_LANGUAGE_ARGENTINA
				wsprintf(szBuff, sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_E].Monster[1], szQuestMonsterName);
#else
#ifdef	_LANGUAGE_CHINESE
				wsprintf(szBuff, sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_E].Monster[1], szQuestMonsterName);
#else
				wsprintf(szBuff, sinLevelQusetDoc4, szQuestMonsterName, chaQuest.sHaQuestElementary[Quest_E].Monster[1]);
#endif
#endif
#endif
#endif
				cMessageBox.ShowMessageEvent(szBuff);
				chaQuest.sHaQuestElementary[Quest_E].Kind = 0;
				chaQuest.sHaQuestElementary[Quest_E].State = 3;
			}

		}
	}

	if (chaQuest.sHaQuestElementary[Quest_F].CODE)
	{
		if (chaQuest.sHaQuestElementary[Quest_F].Kind && chaQuest.sHaQuestElementary[Quest_F].Kind == Monster_CODE)
		{
			chaQuest.sHaQuestElementary[Quest_F].Monster[0]++;
#ifdef _LANGUAGE_CHINESE
			wsprintf(szTemp, sinLevelQusetDoc, chaQuest.sHaQuestElementary[Quest_F].Monster[0], haQuestMonsterName[6]);
#else
			wsprintf(szTemp, sinLevelQusetDoc, haQuestMonsterName[6], chaQuest.sHaQuestElementary[Quest_F].Monster[0]);
#endif
			AddChatBuff(szTemp, 9);
			if (chaQuest.sHaQuestElementary[Quest_F].Monster[0] == chaQuest.sHaQuestElementary[Quest_F].Monster[1])
			{
#ifdef	_LANGUAGE_ENGLISH
				wsprintf(szBuff, sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_F].Monster[1], szQuestMonsterName);
#else
#ifdef	_LANGUAGE_BRAZIL
				wsprintf(szBuff, sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_F].Monster[1], szQuestMonsterName);
#else
#ifdef	_LANGUAGE_ARGENTINA
				wsprintf(szBuff, sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_F].Monster[1], szQuestMonsterName);
#else
#ifdef	_LANGUAGE_CHINESE
				wsprintf(szBuff, sinLevelQusetDoc4, chaQuest.sHaQuestElementary[Quest_F].Monster[1], szQuestMonsterName);
#else
				wsprintf(szBuff, sinLevelQusetDoc4, szQuestMonsterName, chaQuest.sHaQuestElementary[Quest_F].Monster[1]);
#endif
#endif
#endif
#endif
				cMessageBox.ShowMessageEvent(szBuff);
				chaQuest.sHaQuestElementary[Quest_F].Kind = 0;
				chaQuest.sHaQuestElementary[Quest_F].State = 3;
				SetQuestBoard();
			}

		}
	}


	if (sinQuest_ChangeJob4.CODE)
	{
		if (sinQuest_ChangeJob4.Kind && Monster_CODE == sinQuest_ChangeJob4.Kind && sinQuest_ChangeJob4.State <= 4 || sinQuest_ChangeJob4.State == 9)
		{
			sinQuest_ChangeJob4.Monster[0]++;

#ifdef _LANGUAGE_CHINESE
			wsprintf(szTemp, sinLevelQusetDoc, sinQuest_ChangeJob4.Monster[0], szQuestMonsterName);
#else
			wsprintf(szTemp, sinLevelQusetDoc, szQuestMonsterName, sinQuest_ChangeJob4.Monster[0]);
#endif
			AddChatBuff(szTemp, 9);
			if (sinQuest_ChangeJob4.Monster[0] == sinQuest_ChangeJob4.Monster[1])
			{

#ifdef	_LANGUAGE_ENGLISH
				wsprintf(szBuff, sinLevelQusetDoc4, sinQuest_ChangeJob4.Monster[1], szQuestMonsterName);
#else

#ifdef _LANGUAGE_CHINESE
				wsprintf(szBuff, sinLevelQusetDoc4, sinQuest_ChangeJob4.Monster[1], szQuestMonsterName);
#else
#ifdef	_LANGUAGE_BRAZIL
				wsprintf(szBuff, sinLevelQusetDoc4, sinQuest_ChangeJob4.Monster[1], szQuestMonsterName);
#else
#ifdef	_LANGUAGE_ARGENTINA
				wsprintf(szBuff, sinLevelQusetDoc4, sinQuest_ChangeJob4.Monster[1], szQuestMonsterName);
#else
				wsprintf(szBuff, sinLevelQusetDoc4, szQuestMonsterName, sinQuest_ChangeJob4.Monster[1]);
#endif
#endif			    
#endif
#endif
				cMessageBox.ShowMessageEvent(szBuff);
				sinQuest_ChangeJob4.Kind = 0;
			}
		}
	}


	if (sinQuest_Level30.CODE)
	{
		if (MONSTER_BAGON == Monster_CODE)
		{
			if (sinQuest_Level30.State == 1)
			{
				sinQuest_Level30.Monster[0]++;
#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp, sinLevelQusetDoc, sinQuest_Level30.Monster[0], sinLevelQuestMonster[0]);
#else

				wsprintf(szTemp, sinLevelQusetDoc, sinLevelQuestMonster[0], sinQuest_Level30.Monster[0]);
#endif
				AddChatBuff(szTemp, 9);
				if (sinQuest_Level30.Monster[0] == sinQuest_Level30.Monster[1])
				{

#ifdef _LANGUAGE_BRAZIL
					cMessageBox.ShowMessageEvent("Voce matou 20 Bargons.");
#else
					cMessageBox.ShowMessageEvent("You have killed 20 Bargons.");
#endif
					sinQuest_Level30.State = 2;
				}
			}
		}
	}


	if (sinQuest_Level55.CODE)
	{
		if (MONSTER_MURPIN == Monster_CODE)
		{
			if (sinQuest_Level55.State == 1)
			{
				sinQuest_Level55.Monster[0]++;

#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp, sinLevelQusetDoc, sinQuest_Level55.Monster[0], sinLevelQuestMonster[1]);
#else
				wsprintf(szTemp, sinLevelQusetDoc, sinLevelQuestMonster[1], sinQuest_Level55.Monster[0]);
#endif
				AddChatBuff(szTemp, 9);
				if (sinQuest_Level55.Monster[0] == sinQuest_Level55.Monster[1])
				{
					sinQuest_Level55.State = 2;
				}
			}
		}
	}


	if (sinQuest_Level55_2.CODE)
	{
		if (MONSTER_DIREBEE == Monster_CODE)
		{
			if (sinQuest_Level55_2.State == 1)
			{
				sinQuest_Level55_2.Monster[0]++;

#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp, sinLevelQusetDoc, sinQuest_Level55_2.Monster[0], sinLevelQuestMonster[2]);
#else
				wsprintf(szTemp, sinLevelQusetDoc, sinLevelQuestMonster[2], sinQuest_Level55_2.Monster[0]);
#endif
				AddChatBuff(szTemp, 9);
				if (sinQuest_Level55_2.Monster[0] == sinQuest_Level55_2.Monster[1])
				{
					sinQuest_Level55_2.State = 2;
				}
			}
		}
	}


	if (sinQuest_Level70.CODE)
	{
		if (MONSTER_TYPOON == Monster_CODE)
		{
			if (sinQuest_Level70.State == 1)
			{
				sinQuest_Level70.Monster[0]++;

#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp, sinLevelQusetDoc, sinQuest_Level70.Monster[0], sinLevelQuestMonster[3]);
#else
				wsprintf(szTemp, sinLevelQusetDoc, sinLevelQuestMonster[3], sinQuest_Level70.Monster[0]);
#endif
				AddChatBuff(szTemp, 9);
				if (sinQuest_Level70.Monster[0] == sinQuest_Level70.Monster[1])
				{
					sinQuest_Level70.State = 2;
				}
			}
		}
	}

	if (sinQuest_Level80.CODE)
	{
		if (MONSTER_RATOO == Monster_CODE)
		{
			if (sinQuest_Level80.State == 1)
			{
				sinQuest_Level80.Monster[0]++;

#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp, sinLevelQusetDoc, sinQuest_Level80.Monster[0], sinLevelQuestMonster[4]);
#else
				wsprintf(szTemp, sinLevelQusetDoc, sinLevelQuestMonster[4], sinQuest_Level80.Monster[0]);
#endif
				AddChatBuff(szTemp, 9);
				if (sinQuest_Level80.Monster[0] == sinQuest_Level80.Monster[1])
				{
					sinQuest_Level80.State = 2;
				}
			}
		}
	}

	if (sinQuest_Level85.CODE)
	{
		if (MONSTER_GROTESQUE == Monster_CODE)
		{
			if (sinQuest_Level85.State == 2)
			{
				sinQuest_Level85.Monster[0]++;

#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp, sinLevelQusetDoc, sinQuest_Level85.Monster[0], sinLevelQuestMonster[5]);
#else
				wsprintf(szTemp, sinLevelQusetDoc, sinLevelQuestMonster[5], sinQuest_Level85.Monster[0]);
#endif

				AddChatBuff(szTemp, 9);
				if (sinQuest_Level85.Monster[0] == sinQuest_Level85.Monster[1])
				{
					sinQuest_Level85.State = 3;
				}
			}
		}
	}

	if (sinQuest_Level90.CODE)
	{
		if (MONSTER_IRONFIST == Monster_CODE)
		{
			if (sinQuest_Level90.State == 1)
			{
				sinQuest_Level90.Monster[0]++;

#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp, sinLevelQusetDoc, sinQuest_Level90.Monster[0], sinLevelQuestMonster[6]);
#else
				wsprintf(szTemp, sinLevelQusetDoc, sinLevelQuestMonster[6], sinQuest_Level90.Monster[0]);
#endif

				AddChatBuff(szTemp, 9);
				if (sinQuest_Level90.Monster[0] == sinQuest_Level90.Monster[1])
				{
					sinQuest_Level90.State = 2;
				}
			}
		}
	}
	int sinQuestMonFlag = 0;
	if (sinQuest_Level90_2.CODE)
	{
		if (sinQuest_Level90_2.State == 2)
		{
			switch (sinQuest_Level90_2.Kind)
			{
			case 1:
				if (MONSTER_OMEGA == Monster_CODE)
				{
					sinQuest_Level90_2.Monster[0]++;
					sinQuestMonFlag = 1;
				}
				break;
			case 2:
				if (MONSTER_D_MACHINE == Monster_CODE)
				{
					sinQuest_Level90_2.Monster[0]++;
					sinQuestMonFlag = 1;
				}
				break;
			case 3:
				if (MONSTER_MOUNTAIN == Monster_CODE)
				{
					sinQuest_Level90_2.Monster[0]++;
					sinQuestMonFlag = 1;
				}
				break;

			}
			if (sinQuestMonFlag)
			{

#ifdef _LANGUAGE_CHINESE
				wsprintf(szTemp, sinLevelQusetDoc, sinQuest_Level90_2.Monster[0], sinLevelQuest90_2Mon[sinQuest_Level90_2.Kind - 1]);
#else
				wsprintf(szTemp, sinLevelQusetDoc, sinLevelQuest90_2Mon[sinQuest_Level90_2.Kind - 1], sinQuest_Level90_2.Monster[0]);
#endif

				AddChatBuff(szTemp, 9);
			}

			if (sinQuest_Level90_2.Monster[0] >= sinQuest_Level90_2.Monster[1])
			{
				sinQuest_Level90_2.State = 3;
			}
		}
	}

	sITEM* pItem = 0;
	if (sInven[0].ItemIndex)
	{
		pItem = &cInvenTory.InvenItem[sInven[0].ItemIndex - 1];

	}
	if (!pItem)return FALSE;



	if (pItem->sItemInfo.ItemAgingNum[0] > 3 ||
		pItem->sItemInfo.ItemKindCode != ITEM_KIND_QUEST_WEAPON)return FALSE;

	if (pItem->sItemInfo.ItemKindCode == ITEM_KIND_QUEST_WEAPON)
	{
		switch (sinChar->JOB_CODE)
		{
		case 1:
		case 2:
		case 4:
		case 6:
		case 3:
		case 5:
			if ((pItem->sItemInfo.ItemAgingNum[1] + 1) == Monster_CODE)
			{
				pItem->sItemInfo.ItemAgingCount[0]--;

			}
			break;
		case 7:
		case 8:
			if (pItem->sItemInfo.ItemAgingNum[0] == 1)
			{
				if (StageField[lpCurPlayer->OnStageField]->FieldCode == 8)
					pItem->sItemInfo.ItemAgingCount[0]--;
			}
			if (pItem->sItemInfo.ItemAgingNum[0] == 2)
			{
				if (StageField[lpCurPlayer->OnStageField]->FieldCode == 10)
					pItem->sItemInfo.ItemAgingCount[0]--;
			}
			if (pItem->sItemInfo.ItemAgingNum[0] == 3)
			{
				if (StageField[lpCurPlayer->OnStageField]->FieldCode == 13)
					pItem->sItemInfo.ItemAgingCount[0]--;
			}
			break;
		}
	}

	if ((pItem->sItemInfo.ItemAgingCount[0] < 1) || (ResetQuset3Flag == 2))
	{

		NotChangeSetItemFlag = 1;
		memset(&sAging_Send, 0, sizeof(sCRAFTITEM_SERVER));
		memcpy(&sAging_Send.DesCraftItem, pItem, sizeof(sITEM));
		SendAgingItemToServer(&sAging_Send);

		memcpy(&TempQuestItem, pItem, sizeof(sITEM));





	}
	return TRUE;

}
int SetChangeJob3QuestItem(sITEMINFO* pItem, int Down)
{

	int Temp = 0;
	float fTemp = 0;
	if (pItem->ItemAgingNum[0] > 3)return FALSE;

	switch (pItem->CODE & sinITEM_MASK2)
	{
	case sinWA1:
	case sinWC1:
	case sinWP1:
	case sinWD1:
	case sinWS2:
		if (Down)
		{



		}
		else
		{
			if (pItem->ItemAgingNum[0])
			{
				pItem->fIncrease_Life += 4;
				Temp = GetRandomPos(1, 2);
				pItem->Damage[0] += Temp;
				pItem->Damage[1] += Temp;
				Temp = GetRandomPos(10, 15);
				pItem->Attack_Rating += Temp;
				pItem->ItemKindMask = SIN_ADD_DAMAGE_MIN | SIN_ADD_DAMAGE_MAX | SIN_ADD_ATTACK_RATE | SIN_ADD_LIFE;
			}
			pItem->ItemAgingNum[1] = pItem->ItemAgingNum[0];
			pItem->ItemAgingCount[1] = QuestMonsterCount[pItem->ItemAgingNum[1]];
			pItem->ItemAgingNum[0]++;

		}
		break;
	case sinWS1:
	case sinWT1:
		if (Down)
		{



		}
		else
		{
			if (pItem->ItemAgingNum[0])
			{
				pItem->fIncrease_Life += 4;
				Temp = GetRandomPos(1, 2);
				pItem->Damage[0] += Temp;
				pItem->Damage[1] += Temp;
				Temp = GetRandomPos(10, 15);
				pItem->Attack_Rating += Temp;
				pItem->ItemKindMask = SIN_ADD_DAMAGE_MIN | SIN_ADD_DAMAGE_MAX | SIN_ADD_ATTACK_RATE | SIN_ADD_LIFE;
			}

			pItem->ItemAgingNum[1] = 3 + pItem->ItemAgingNum[0];
			pItem->ItemAgingCount[1] = QuestMonsterCount[pItem->ItemAgingNum[1]];
			pItem->ItemAgingNum[0]++;

		}
		break;
	case sinWN1:
	case sinWM1:
		if (Down)
		{



		}
		else
		{
			if (pItem->ItemAgingNum[0])
			{
				pItem->fIncrease_Life += 4;
				Temp = GetRandomPos(1, 2);
				pItem->Damage[0] += Temp;
				pItem->Damage[1] += Temp;
				Temp = GetRandomPos(3, 6);
				fTemp = (float)Temp / 10.0f;
				pItem->fMana_Regen += fTemp;
				pItem->ItemKindMask = SIN_ADD_DAMAGE_MIN | SIN_ADD_DAMAGE_MAX | SIN_ADD_MANAREGEN | SIN_ADD_LIFE;

			}
			pItem->ItemAgingNum[1] = 6 + pItem->ItemAgingNum[0];
			pItem->ItemAgingCount[1] = QuestMonsterCount[pItem->ItemAgingNum[1]];
			pItem->ItemAgingNum[0]++;

		}
		break;
	}


	pItem->ItemAgingCount[0] = pItem->ItemAgingCount[1];
	ReformItem(pItem);
	return TRUE;
}

int CheckQuestItemDownFlag = 0;

int CheckChangeJob_QuestItem()
{

	int ItemIndex = 0;
	sITEM* pTempItem = 0;

	if (sinQuest_ChangeJob3.CODE && sinQuest_ChangeJob3.State == 5 && sinChar->ChangeJob == 2)
	{
		while (1)
		{
			ItemIndex = cInvenTory.SearchItemIndex(0, ITEM_KIND_QUEST_WEAPON);
			if (ItemIndex)
			{
				if (ItemIndex < 100)
					pTempItem = &cInvenTory.InvenItem[ItemIndex - 1];
				else pTempItem = &cInvenTory.InvenItemTemp[(ItemIndex - 100) - 1];

				if (sinItemTime > pTempItem->sItemInfo.dwCreateTime + (60 * 60 * 24 * 5))
				{


					cInvenTory.DeleteInvenItemToServer(pTempItem->sItemInfo.CODE,
						pTempItem->sItemInfo.ItemHeader.Head, pTempItem->sItemInfo.ItemHeader.dwChkSum);
					DeleteQuestItem(sinOR2 | sin02);
					DeleteQuestItem(sinOR2 | sin03);
					DeleteQuestItem(sinOR2 | sin04);


					if (MouseItem.Flag && MouseItem.sItemInfo.ItemKindCode == ITEM_KIND_QUEST_WEAPON)
					{
						cInvenTory.DeleteInvenItemToServer(MouseItem.sItemInfo.CODE,
							MouseItem.sItemInfo.ItemHeader.Head, MouseItem.sItemInfo.ItemHeader.dwChkSum);
					}
				}
				else break;
			}
			else break;

		}
	}


	if (sinQuest_ChangeJob3.CODE && sinQuest_ChangeJob3.State == 5 && sinChar->ChangeJob == 2)
	{
		if (!cInvenTory.SearchItemCode(0, ITEM_KIND_QUEST_WEAPON))
		{

			switch (sinChar->JOB_CODE)
			{
			case 1:
				strcpy_s(sLost_Item.szDoc, Quest3ItemName[0]);
				sLost_Item.LostItem[0].CODE = (sinWA1 | sin08);
				sLost_Item.LostItem[1].CODE = (sinOR2 | sin02);

				break;
			case 2:
				strcpy_s(sLost_Item.szDoc, Quest3ItemName[1]);
				sLost_Item.LostItem[0].CODE = (sinWC1 | sin08);
				sLost_Item.LostItem[1].CODE = (sinOR2 | sin02);
				break;
			case 3:
				strcpy_s(sLost_Item.szDoc, Quest3ItemName[2]);
				sLost_Item.LostItem[0].CODE = (sinWS1 | sin10);
				sLost_Item.LostItem[1].CODE = (sinOR2 | sin03);
				break;
			case 4:
				strcpy_s(sLost_Item.szDoc, Quest3ItemName[3]);
				sLost_Item.LostItem[0].CODE = (sinWP1 | sin09);
				sLost_Item.LostItem[1].CODE = (sinOR2 | sin02);
				break;
			case 5:
				strcpy_s(sLost_Item.szDoc, Quest3ItemName[4]);
				sLost_Item.LostItem[0].CODE = (sinWT1 | sin09);
				sLost_Item.LostItem[1].CODE = (sinOR2 | sin03);
				break;
			case 6:
				strcpy_s(sLost_Item.szDoc, Quest3ItemName[5]);
				sLost_Item.LostItem[0].CODE = (sinWS2 | sin10);
				sLost_Item.LostItem[1].CODE = (sinOR2 | sin02);
				break;
			case 7:
			case 8:
				strcpy_s(sLost_Item.szDoc, Quest3ItemName[6]);
				sLost_Item.LostItem[0].CODE = (sinWM1 | sin09);
				sLost_Item.LostItem[1].CODE = (sinOR2 | sin04);
				break;
			}
			sinQuest_ChangeJob3.State = 6;
			sLost_Item.Flag = 1;
			cInvenTory.CheckInvenEmpty(&sLost_Item.LostItem[0]);
			cInvenTory.CheckInvenEmpty(&sLost_Item.LostItem[1]);

		}
	}


	ItemIndex = 0;

	if (sinQuest_ChangeJob3.CODE && !CheckQuestItemDownFlag)
	{
		ItemIndex = cInvenTory.SearchItemIndex(0, ITEM_KIND_QUEST_WEAPON);
		if (ItemIndex)
		{
			if (sinChar->Level > sinQuest_ChangeJob3.StartLevel + 2)
			{
				sinQuest_ChangeJob3.StartLevel = sinChar->Level;
				CheckQuestItemDownFlag = 1;
			}
		}
	}

	if (sinChar->ChangeJob >= 1)
	{
		DeleteQuestItem((sinQT1 | sin01));
		DeleteQuestItem((sinQT1 | sin02));
		DeleteQuestItem((sinQT1 | sin03));
		DeleteQuestItem((sinQT1 | sin04));
		DeleteQuestItem((sinQT1 | sin05));
	}
	if (sinChar->ChangeJob >= 2 && !sinQuest_ChangeJob3.CODE)
	{
		DeleteQuestItem((sinQT1 | sin06));
		DeleteQuestItem(sinOR2 | sin02);
		DeleteQuestItem(sinOR2 | sin03);
		DeleteQuestItem(sinOR2 | sin04);

	}
	return TRUE;
}

int sinCheckLevelQuest30()
{
	if (!chaQuest.haQuestCheck())return FALSE;
	if (!CheckNowQuestState(SIN_QUEST_CODE_LEVEL30))return FALSE;
	if (sinChar->Level >= 30 && (sinQuest_levelLog & QUESTBIT_LEVEL_30) == 0)
	{
		switch (sinQuest_Level30.State)
		{
		case 0:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL30, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest30Doc[0]);
			break;
		case 1:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL30, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest30Doc[1]);
			break;
		case 2:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL30, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest30Doc[2]);
			break;

		}
	}

	return TRUE;
}


int sinCheckLevelQuest55()
{
	if (!chaQuest.haQuestCheck())return FALSE;
	if (sinQuest_ChangeJob.CODE || sinQuest_ChangeJob2.CODE || sinQuest_ChangeJob3.CODE || sinQuest_ChangeJob4.CODE)return FALSE;
	if (!CheckNowQuestState(SIN_QUEST_CODE_LEVEL55))return FALSE;
	if (sinChar->Level >= 55 && (sinQuest_levelLog & (QUESTBIT_LEVEL_30 | QUESTBIT_LEVEL_55)) == QUESTBIT_LEVEL_30)
	{
		switch (sinQuest_Level55.State)
		{
		case 0:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL55, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest55Doc[0]);
			break;
		case 1:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL55, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest55Doc[1]);
			break;
		case 2:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL55, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest55Doc[2]);
			break;

		}

	}
	return TRUE;
}


int sinCheckLevelQuest55_2()
{
	if (!chaQuest.haQuestCheck())return FALSE;
	if (sinQuest_ChangeJob.CODE || sinQuest_ChangeJob2.CODE || sinQuest_ChangeJob3.CODE || sinQuest_ChangeJob4.CODE)return FALSE;
	if (!CheckNowQuestState(SIN_QUEST_CODE_LEVEL55_2))return FALSE;
	if (sinChar->Level >= 55 && (sinQuest_levelLog & (QUESTBIT_LEVEL_30 | QUESTBIT_LEVEL_55)) == QUESTBIT_LEVEL_30)
	{
		switch (sinQuest_Level55_2.State)
		{
		case 0:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL55_2, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest55_2Doc[0]);
			break;
		case 1:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL55_2, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest55_2Doc[1]);
			break;
		case 2:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL55_2, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest55_2Doc[2]);
			break;

		}

	}
	return TRUE;
}



int sinCheckLevelQuest70()
{
	if (!chaQuest.haQuestCheck())return FALSE;
	if (!CheckNowQuestState(SIN_QUEST_CODE_LEVEL70))return FALSE;
	if (sinChar->Level >= 70 && (sinQuest_levelLog & (QUESTBIT_LEVEL_55 | QUESTBIT_LEVEL_70)) == QUESTBIT_LEVEL_55)
	{
		switch (sinQuest_Level70.State)
		{
		case 0:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL70, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest70Doc[0]);
			break;
		case 1:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL70, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest70Doc[1]);
			break;
		case 2:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL70, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest70Doc[2]);
			break;

		}
	}
	return TRUE;
}


int sinCheckLevelQuest80()
{
	if (!chaQuest.haQuestCheck())return FALSE;
	if (!CheckNowQuestState(SIN_QUEST_CODE_LEVEL80))return FALSE;
	if (sinChar->Level >= 80 && (sinQuest_levelLog & (QUESTBIT_LEVEL_70 | QUESTBIT_LEVEL_80)) == QUESTBIT_LEVEL_70)
	{
		switch (sinQuest_Level80.State)
		{
		case 0:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL80, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest80Doc[0]);
			break;
		case 1:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL80, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest80Doc[1]);
			break;
		case 2:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL80, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest80Doc[2]);
			break;

		}

	}
	return TRUE;
}


int sinCheckLevelQuest85()
{
	if (!chaQuest.haQuestCheck())return FALSE;
	if (!CheckNowQuestState(SIN_QUEST_CODE_LEVEL85))return FALSE;
	if (sinChar->Level >= 85 && (sinQuest_levelLog & (QUESTBIT_LEVEL_80 | QUESTBIT_LEVEL_85)) == QUESTBIT_LEVEL_80)
	{
		switch (sinQuest_Level85.State)
		{
		case 0:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL85, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest85Doc[0]);
			break;
		case 1:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL85, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest85Doc[1]);
			break;
		case 2:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL85, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest85Doc[2]);
			break;
		case 3:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL85, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest85Doc[3]);
			break;

		}

	}

	return TRUE;
}

int sinCheckQuest85Die()
{

	if (sinQuest_Level85.CODE && sinQuest_Level85.State)
	{
		sinQuest_Level85.State = 1;
		DeleteQuestItem(sinQT1 | sin08);

	}

	if (sinQuest_Level90_2.CODE && sinQuest_Level90_2.State == 2)
	{
		sinQuest_Level90_2.State = 1;
		sinQuest_Level90_2.Monster[0] = 0;
		sinQuest_Level90_2.Monster[1] = 0;
		sinQuest_Level90_2.Kind = 0;
		cMessageBox.ShowMessage(MESSAGE_PLUS_POINT_90_2_MON);
		cInvenTory.SetItemToChar();
		SetQuestBoard();

	}
	return TRUE;
}


int sinCheckLevelQuest90()
{
	if (!chaQuest.haQuestCheck())return FALSE;
	if (!CheckNowQuestState(SIN_QUEST_CODE_LEVEL90))return FALSE;
	if (sinChar->Level >= 90 && (sinQuest_levelLog & (QUESTBIT_LEVEL_85 | QUESTBIT_LEVEL_90)) == QUESTBIT_LEVEL_85)
	{
		switch (sinQuest_Level90.State)
		{
		case 0:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL90, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest90Doc[0]);
			break;
		case 1:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL90, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest90Doc[1]);
			break;
		case 2:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL90, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest90Doc[2]);
			break;

		}
	}

	return TRUE;
}


int sinCheckLevelQuest80_2(int NpcNum)
{
	if (!chaQuest.haQuestCheck())return FALSE;
	if (!CheckNowQuestState(SIN_QUEST_CODE_LEVEL80_2))return FALSE;
	if ((sinQuest_levelLog & QUESTBIT_LEVEL_80_2) == QUESTBIT_LEVEL_80_2)return FALSE;
	if (sinQuest_Level80_2.State >= 5)return FALSE;
	if (sinChar->Level >= 80)
	{
		switch (sinQuest_Level80_2.State)
		{
		case 0:
			if (NpcNum)break;
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL80_2, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest80_2Doc[0]);
			break;
		case 1:
			if (!NpcNum)break;
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL80_2, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest80_2Doc[1]);
			break;
		case 2:
			if (!NpcNum)break;
			if (sinCheckLevelQuest80_2Item())
			{
				sinSetSendItem80_2();
				sinQuest_Level80_2.State = 3;
				sinCheckLevelQuest80_2(1);
			}
			else cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL80_2, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest80_2Doc[2]);
			break;
		case 3:
			if (!NpcNum)break;
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL80_2, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest80_2Doc[3]);
			break;
		case 4:
			if (NpcNum)break;
			if (cInvenTory.SearchItemCode(sinQT1 | sin12))
			{
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL80_2, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest80_2Doc[4]);
			}
			break;

		}
	}

	return TRUE;
}

int sinCheckLevelQuest80_2Item()
{
	if (cInvenTory.SearchItemCode(sinQT1 | sin09) &&
		cInvenTory.SearchItemCode(sinQT1 | sin10) &&
		cInvenTory.SearchItemCode(sinQT1 | sin11))
		return TRUE;
	return FALSE;
}

int sinSetSendItem80_2()
{
	sITEM* pItem = 0;
	int   Count = 0;
	int   i = 0;
	int   TempItemIndex[3] = { 0,0,0 };
	short TempItemIndex2[4] = { 0, };
	memset(&sWingItem_Send, 0, sizeof(sCRAFTITEM_SERVER));
	for (i = 0; i < INVENTORY_MAXITEM * 2; i++)
	{
		if (i < 100)
		{
			if (!cInvenTory.InvenItem[i].Flag)continue;
			pItem = &cInvenTory.InvenItem[i];
		}
		else
		{
			if (!cInvenTory.InvenItemTemp[i - 100].Flag)continue;
			pItem = &cInvenTory.InvenItemTemp[i - 100];
		}

		switch (pItem->sItemInfo.CODE)
		{
		case (sinQT1 | sin09):
			if (sWingItem_Send.SheltomCode[0])break;
			sWingItem_Send.SheltomCode[0] = pItem->sItemInfo.CODE;
			sWingItem_Send.Head[0] = pItem->sItemInfo.ItemHeader.Head;
			sWingItem_Send.CheckSum[0] = pItem->sItemInfo.ItemHeader.dwChkSum;
			break;
		case (sinQT1 | sin10):
			if (sWingItem_Send.SheltomCode[1])break;
			sWingItem_Send.SheltomCode[1] = pItem->sItemInfo.CODE;
			sWingItem_Send.Head[1] = pItem->sItemInfo.ItemHeader.Head;
			sWingItem_Send.CheckSum[1] = pItem->sItemInfo.ItemHeader.dwChkSum;

			break;
		case (sinQT1 | sin11):
			if (sWingItem_Send.SheltomCode[2])break;
			sWingItem_Send.SheltomCode[2] = pItem->sItemInfo.CODE;
			sWingItem_Send.Head[2] = pItem->sItemInfo.ItemHeader.Head;
			sWingItem_Send.CheckSum[2] = pItem->sItemInfo.ItemHeader.dwChkSum;

			break;

		}
	}
	return TRUE;
}


int sinCheckLevelQuest90_2(int NpcNum)
{
	if (NpcNum == 0)
		if (!chaQuest.haQuestCheck())return FALSE;
	if (!CheckNowQuestState(SIN_QUEST_CODE_LEVEL90_2))return FALSE;
	if ((sinQuest_levelLog & QUESTBIT_LEVEL_90_2) == QUESTBIT_LEVEL_90_2)return FALSE;
	if (sinChar->Level >= 90)
	{
		switch (sinQuest_Level90_2.State)
		{
		case 0:
			if (NpcNum)break;
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL90_2, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest90_2Doc[0]);
			break;
		case 1:
			if (!NpcNum)break;
			if (!sinQuest_Level90_2.Kind)
			{
				sinQuest_Level90_2.Kind = GetRandomPos(1, 3);
				sinQuest_Level90_2.Monster[1] = 50;
			}
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL90_2, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest90_2Doc[1]);
			break;
		case 2:
			if (!NpcNum)
			{
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL90_2, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest90_2Doc[2]);
			}
			else
			{
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL90_2, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest90_2Doc[3]);
			}
			break;
		case 3:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL90_2, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest90_2Doc[4]);
			break;

		}

	}
	return TRUE;
}

void* pQuestCode[] = {
  &sinQuest_ChangeJob,
  &sinQuest_ChangeJob2,
  &sinQuest_ChangeJob3,
  &sinQuest_Level30,
  &sinQuest_Level55,
  &sinQuest_Level55_2,
  &sinQuest_Level70,
  &sinQuest_Level80,
  &sinQuest_Level85,
  &sinQuest_Level90,
  &sinQuest_Level80_2,
  &sinQuest_Level90_2,
  &sinQuest_ChangeJob4,
  0,
};

struct QuestCodeFlag
{
	DWORD	CODE;
};


int CheckNowQuestState(DWORD CODE)
{
	int cnt = 0;
	while (1)
	{
		if (pQuestCode[cnt] == 0)break;
		if (((QuestCodeFlag*)pQuestCode[cnt])->CODE && ((QuestCodeFlag*)pQuestCode[cnt])->CODE != CODE)
		{
			cMessageBox.ShowMessage(MESSAGE_QUEST_NOW_EXIT);
			return FALSE;

		}
		cnt++;
	}
	return TRUE;
}


int ClearNowQuest()
{
	int cnt = 0;
	while (1)
	{
		if (pQuestCode[cnt] == 0)break;
		if (((QuestCodeFlag*)pQuestCode[cnt])->CODE)
		{
			((QuestCodeFlag*)pQuestCode[cnt])->CODE = 0;
			return FALSE;

		}
		cnt++;
	}
	return TRUE;
}



int sinChangeJob4MonCode[][2] = {
	{MONSTER_MURPIN,MONSTER_SKELETON_KNIGHT },
	{MONSTER_HEAD_CUTTER,MONSTER_SOLID_SNAIL},
	{MONSTER_THORN_CROWLER,MONSTER_MUMMY},
	{MONSTER_DOOM_GUARD ,MONSTER_FIGON},
	{MONSTER_STONE_GIANT,MONSTER_STONE_COLEM},
	{MONSTER_IRON_GUARD,MONSTER_AVELLRIN},
};
int sinChangeJob4MonCode2[][2] = {
	{MONSTER_AVELRISK_L,MONSTER_BEEBUL},
	{MONSTER_ILLUSION_KNIGHT,MONSTER_NIGHT_MARE },
	{MONSTER_WITCH,MONSTER_HEAVY_GOBLIN},
	{MONSTER_DAWLIN ,MONSTER_STYGIAN},
	{MONSTER_INCUBUS,MONSTER_CHAIN_GOLEM},
	{MONSTER_DARK_SPECTOR,MONSTER_METRON},
};
int sinChangeJob4MonCode3[] = {
	MONSTER_SOLID_SNAIL,
	MONSTER_ILLUSION_KNIGHT,
	MONSTER_AVELRISK_LOAD,
	MONSTER_DUSK,
	MONSTER_CHAIN_GOLEM ,
	MONSTER_SADNESS
};


char* sinGetMonsterName(int CODE)
{

	return sinMonCodeName[CODE];
}

int QuestLevelTable[7] = { 60,65,70,75,80,85,200 };
char szQuestMonsterName[64];
int sinChangeJob4MonSet(sQUEST_CHANGEJOB3* pQuset)
{

	int QuestLevel = 0;
	char szBuff[128];

	for (int i = 0; i < 6; i++)
	{
		if (sinChar->Level >= QuestLevelTable[i] && sinChar->Level < QuestLevelTable[i + 1])
			QuestLevel = i;
	}
	int RandomIndex = 0;
	switch (pQuset->State)
	{
	case 1:
		RandomIndex = GetRandomPos(0, 1);
		if (QuestLevel < 4)
			pQuset->Monster[1] = 50;
		else pQuset->Monster[1] = 30;
		pQuset->Kind = sinChangeJob4MonCode[QuestLevel][RandomIndex];
		strcpy_s(szQuestMonsterName, sinGetMonsterName(pQuset->Kind));

#ifdef	_LANGUAGE_ENGLISH
		wsprintf(szBuff, sinLevelQusetDoc2, pQuset->Monster[1], szQuestMonsterName);
#else

#ifdef	_LANGUAGE_CHINESE
		wsprintf(szBuff, sinLevelQusetDoc2, pQuset->Monster[1], szQuestMonsterName);
#else
#ifdef  _LANGUAGE_BRAZIL
		wsprintf(szBuff, sinLevelQusetDoc2, pQuset->Monster[1], szQuestMonsterName);
#else
#ifdef  _LANGUAGE_ARGENTINA
		wsprintf(szBuff, sinLevelQusetDoc2, pQuset->Monster[1], szQuestMonsterName);
#else
		wsprintf(szBuff, sinLevelQusetDoc2, szQuestMonsterName, pQuset->Monster[1]);
#endif
#endif
#endif
#endif

		cMessageBox.ShowMessageEvent(szBuff);
		sinSetQuestTimer(pQuset);
		break;
	case 2:
		RandomIndex = GetRandomPos(0, 1);
		if (QuestLevel < 4)
			pQuset->Monster[1] = 50;
		else pQuset->Monster[1] = 30;
		pQuset->Kind = sinChangeJob4MonCode2[QuestLevel][RandomIndex];
		strcpy_s(szQuestMonsterName, sinGetMonsterName(pQuset->Kind));
#ifdef	_LANGUAGE_ENGLISH
		wsprintf(szBuff, sinLevelQusetDoc2, pQuset->Monster[1], szQuestMonsterName);
#else

#ifdef	_LANGUAGE_CHINESE
		wsprintf(szBuff, sinLevelQusetDoc2, pQuset->Monster[1], szQuestMonsterName);
#else
#ifdef	_LANGUAGE_BRAZIL
		wsprintf(szBuff, sinLevelQusetDoc2, pQuset->Monster[1], szQuestMonsterName);
#else
#ifdef	_LANGUAGE_ARGENTINA
		wsprintf(szBuff, sinLevelQusetDoc2, pQuset->Monster[1], szQuestMonsterName);
#else
		wsprintf(szBuff, sinLevelQusetDoc2, szQuestMonsterName, pQuset->Monster[1]);
#endif
#endif
#endif
#endif
		cMessageBox.ShowMessageEvent(szBuff);
		sinSetQuestTimer(pQuset);
		break;
	case 4:
		pQuset->Kind = sinChangeJob4MonCode3[QuestLevel];
		strcpy_s(szQuestMonsterName, sinGetMonsterName(pQuset->Kind));
		wsprintf(szBuff, sinLevelQusetDoc3, szQuestMonsterName);
		cMessageBox.ShowMessageEvent(szBuff);
		break;
	}


	return TRUE;

}
int sinCheckChangeJobQuest4()
{
	if (!CheckNowQuestState(SIN_QUEST_CODE_CHANGEJOB4))return FALSE;
	if (sinQuest_ChangeJob4.CODE && sinChar->Level >= 60)
	{
		switch (sinQuest_ChangeJob4.State)
		{
		case 0:
			if (sinQuest_ChangeJob4.Monster[1])
				cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath4[0]);
			break;
		case 1:
			if (sinQuest_ChangeJob4.Monster[0] == sinQuest_ChangeJob4.Monster[1])
			{
				sinQuest_ChangeJob4.State = 2;
				sinCheckChangeJobQuest4();
				SetQuestBoard();
			}
			else
			{
				cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath4[1]);
			}
			break;
		case 2:
			if (cSkill.SearchContiueSkill(CHANGE_JOB3_QUEST))
			{
				cSkill.CancelContinueSkill(CHANGE_JOB3_QUEST);
				sinQuest_ChangeJob4.Monster[0] = 0;
				sinQuest_ChangeJob4.Monster[1] = 0;
				sinQuest_ChangeJob4.Kind = 0;

			}
			cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath4[2]);
			break;
		case 3:
			if (sinQuest_ChangeJob4.Monster[0] == sinQuest_ChangeJob4.Monster[1])
			{
				sinQuest_ChangeJob4.State = 4;
				sinCheckChangeJobQuest4();
				SetQuestBoard();
			}
			else
			{
				cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath4[3]);
			}
			break;
		case 4:
		case 7:
			if (cSkill.SearchContiueSkill(CHANGE_JOB3_QUEST))
			{
				cSkill.CancelContinueSkill(CHANGE_JOB3_QUEST);
				sinQuest_ChangeJob4.Monster[0] = 0;
				sinQuest_ChangeJob4.Monster[1] = 0;
				sinQuest_ChangeJob4.Kind = 0;

			}
			cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath4[4]);
			break;
		case 5:
			if (cInvenTory.SearchItemCode(sinQT1 | sin13))
			{
				sinQuest_ChangeJob4.State = 6;
				sinCheckChangeJobQuest4();
				SetQuestBoard();
			}
			else
			{
				cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath4[5]);
			}
		case 6:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath4[6]);
			break;
		case 8:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath4[7]);
			break;
		}
	}
	return TRUE;
}


int sinSetQuestTimer(sQUEST_CHANGEJOB3* pQuset, int UseTime, int CheckTime)
{

	sSKILL TempSkill;
	memset(&TempSkill, 0, sizeof(sSKILL));

	char* Path = "image\\Sinimage\\skill\\keep\\QuestTimer.tga";
	if (!MatQuestTimer)
	{
		MatQuestTimer = CreateTextureMaterial(Path, 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
		ReadTextures();
	}

	TempSkill.CODE = CHANGE_JOB3_QUEST;
	TempSkill.UseTime = 70 * 70;
	if (UseTime)TempSkill.UseTime = UseTime;
	if (CheckTime)TempSkill.CheckTime = CheckTime;
	TempSkill.Point = 1;
	TempSkill.MatIcon = MatQuestTimer;
	sinContinueSkillSet(&TempSkill);
	sinPlaySound(SIN_SOUND_EAT_POTION2);
	return TRUE;
}


int sinBattleNpcResult(int WinFlag)
{
	if (WinFlag)
	{
		sinQuest_ChangeJob4.State = 8;
		SetQuestBoard();
		cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath4[7]);
	}
	else
	{
		sinQuest_ChangeJob4.State = 4;
		SetQuestBoard();

	}
	return TRUE;
}


int sinCompleteChangeJob4(int Index)
{

	if (cSkill.SearchContiueSkill(CHANGE_JOB3_QUEST))
	{
		cSkill.CancelContinueSkill(CHANGE_JOB3_QUEST);
		sinQuest_ChangeJob4.Monster[0] = 0;
		sinQuest_ChangeJob4.Monster[1] = 0;
		sinQuest_ChangeJob4.Kind = 0;

	}
	switch (Index)
	{
	case 1:
		if (sinQuest_ChangeJob4.State == 8)break;
		sinQuest_ChangeJob4.CODE = SIN_QUEST_CODE_CHANGEJOB4;
		StartQuest_Code(sinQuest_ChangeJob4.CODE);


		cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath4[0]);
		sinQuest_ChangeJob4.State = 1;
		SetQuestBoard();
		sinChangeJob4MonSet(&sinQuest_ChangeJob4);
		SaveGameData();
		break;
	case 2:
		if (sinQuest_ChangeJob4.State == 8)break;
		sinQuest_ChangeJob4.CODE = SIN_QUEST_CODE_CHANGEJOB4;
		StartQuest_Code(sinQuest_ChangeJob4.CODE);

		sinQuest_ChangeJob4.State = 2;
		sinCheckChangeJobQuest4();
		SaveGameData();
		break;
	case 3:
		if (sinQuest_ChangeJob4.State == 8)break;
		sinQuest_ChangeJob4.CODE = SIN_QUEST_CODE_CHANGEJOB4;
		StartQuest_Code(sinQuest_ChangeJob4.CODE);

		sinQuest_ChangeJob4.State = 3;
		sinCheckChangeJobQuest4();
		SaveGameData();
		break;
	case 4:
		if (sinQuest_ChangeJob4.State == 8)break;
		sinQuest_ChangeJob4.CODE = SIN_QUEST_CODE_CHANGEJOB4;
		StartQuest_Code(sinQuest_ChangeJob4.CODE);

		cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath4[7]);
		sinQuest_ChangeJob4.State = 8;
		SetQuestBoard();
		SaveGameData();
		break;
	}
	return TRUE;
}


