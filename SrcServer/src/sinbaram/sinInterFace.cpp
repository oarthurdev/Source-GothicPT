

#include "sinLinkHeader.h"
#include "tjboy\\clanmenu\\tjclan.h"
#include "..\\field.h"


cINTERFACE	cInterFace;
sSHADOWSTATE sShadowState[3];

int sinBmpLength[5] = { 0,0,0,0,0 };


int sinChatEnter = 0;
int SubChatHeight = 0;
int sinChatDisplayMode = 0;
int sinChatInputMode = 0;



int TestKeyAniFlag = 0;


int ExitButtonClick = 0;
int HelpButtonClick = 0;
int MouseButtonPosi = 0;
int sinMenuBottonPosi = 0;
int sinRunCameraMapPosi = 0;
int SunandMoonFlag[2] = { 0,0 };
int InterButtonDown = 0;
int sinFireShow = 1;


int ReSizelpGage = 0;



int InitStateFlag = 0;



char szInfoMsgBuff5[512];
char szInfoMsgBuff6[128];
POINT InfoMessageBoxPos;



int ReStartFlag = 0;
POINT ReStartMainXY = { 0,0 };
int ReStartIndex = 0;
POINT ReStartTextXY = { 0,0 };
char szReStartMsg[128];
char szReStartMsg2[128];

int RestartCheckExp = 0;
int ReStartOptionIndex = 0;
int ShowExpPercentFlag = 0;



int SkillNpcFlag = 0;
POINT SkillMasterMainXY = { 0,0 };
int SkillMasterIndex = 0;
POINT SkillMasterTextXY = { 0,0 };
char szSkillMasterMsg[128];
char szSkillMasterMsg2[128];
int SkillMasterOptionIndex = 0;


int NotUseSkillEffect[3] = { 0,0,0 };

int SkillMouseButtonPosi[2] = { 0,0 };


int DayOrNightFlag = 0;
int sinGageTime2 = 0;


int ReStartButtonRect[3][4] = {
	{21,22,21 + 44,22 + 44},
	{72,22,72 + 44,22 + 44},
	{123,22,123 + 44,22 + 44},

};

int ButtonRect[6][5] = {
	{648,560,648 + 25,560 + 27},
	{673,560,673 + 25,560 + 27},
	{698,560,698 + 25,560 + 27},
	{723,560,723 + 25,560 + 27},
	{748,560,748 + 25,560 + 27},
	{772,560,772 + 25,560 + 27},

};

int sinMenuRect[3][4] = {
	{692,492,784,511},
	{692,517,784,536},
	{692,542,784,561},


};

int sinRunCameraMap[3][4] = {
	{569,555,569 + 26,555 + 26},
	{569 + 26,555,569 + 26 + 26,555 + 26},
	{569 + 26 + 26,555,569 + 26 + 26 + 26,555 + 26},

};



int ChangeJobButtonclick = 0;



int sinPKWarningExpFlag = 0;
int sinPKWarnigExpTime = 0;
DIRECTDRAWSURFACE lpGrowInterLeft;
DIRECTDRAWSURFACE lpGrowInterMiddle;
DIRECTDRAWSURFACE lpGrowInterRight;



struct HAEFFECT
{
	int   Flag;
	int   Time;
	POINT Posi;
	POINT Size;
	int   Mat;
	int   Alpha;
};
char *HaEffectFilePath[] = {
	0,
	"Assets\\GUI\\Interface\\defense.tga",
	"Assets\\GUI\\Interface\\block.tga",
	"Assets\\GUI\\Interface\\Evade.tga",
	0,
};
#define  MAX_HAEFFECTNUM 10 

int HA_EffectIndex[4] = { 0, };

HAEFFECT HaEffect[MAX_HAEFFECTNUM];



cINTERFACE::cINTERFACE()
{
	memset(&HaEffect, 0, sizeof(HAEFFECT));
}
cINTERFACE::~cINTERFACE()
{


}

void cINTERFACE::Init()
{


	ReStartMainXY.x = (WinSizeX / 2) - (187 / 2);
	ReStartMainXY.y = (WinSizeY / 2) - (127 / 2) - 100;

	ReStartTextXY.x = ReStartMainXY.x + 23;
	ReStartTextXY.y = ReStartMainXY.y + 73;

	SkillMasterMainXY.x = (WinSizeX / 2) - (187 / 2) - 30;
	SkillMasterMainXY.y = (WinSizeY / 2) - (127 / 2) - 100;

	SkillMasterTextXY.x = SkillMasterMainXY.x + 23;
	SkillMasterTextXY.y = SkillMasterMainXY.y + 73;



	InitState();



	MatMenu[0] = CreateTextureMaterial("Assets\\GUI\\Interface\\Menu-1.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatMenu[1] = CreateTextureMaterial("Assets\\GUI\\Interface\\Menu-2.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	MatChatDefault[0] = CreateTextureMaterial("Assets\\GUI\\Interface\\Chat\\ChatDefault-1.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatChatDefault[1] = CreateTextureMaterial("Assets\\GUI\\Interface\\Chat\\ChatDefault-2.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	MatChatSmall[0] = CreateTextureMaterial("Assets\\GUI\\Interface\\Chat\\ChatSmall-1.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatChatSmall[1] = CreateTextureMaterial("Assets\\GUI\\Interface\\Chat\\ChatSmall-2.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	MatChatDoc[0] = CreateTextureMaterial("Assets\\GUI\\Interface\\Chat\\ChatDoc-1.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatChatDoc[1] = CreateTextureMaterial("Assets\\GUI\\Interface\\Chat\\ChatDoc-2.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);


	MatExitMenu = CreateTextureMaterial("Assets\\GUI\\Interface\\ExitMenu.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);


	MatClock = CreateTextureMaterial("Assets\\GUI\\Interface\\Clock.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatComPass = CreateTextureMaterial("Assets\\GUI\\Interface\\Compass.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	MatLife = CreateTextureMaterial("Assets\\GUI\\Interface\\ShadowLife.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatMana = CreateTextureMaterial("Assets\\GUI\\Interface\\ShadowMana.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatStamina = CreateTextureMaterial("Assets\\GUI\\Interface\\ShadowStamina.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);


	Load();


}

void cINTERFACE::Load()
{
	lpLIFE = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\Bar_Life.bmp");
	lpMP = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\Bar_Mana.bmp");
	lpSTM = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\Bar_Stamina.bmp");

	lpButton[0] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\bStatus.bmp");
	lpButton[1] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\bInvenTory.bmp");
	lpButton[2] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\bSkill.bmp");
	lpButton[3] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\bParty.bmp");
	lpButton[4] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\bQuest.bmp");
	lpButton[5] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\bSystem.bmp");

	lpButton2[0] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\bStatus-1.bmp");
	lpButton2[1] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\bInvenTory-1.bmp");
	lpButton2[2] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\bSkill-1.bmp");
	lpButton2[3] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\bParty-1.bmp");
	lpButton2[4] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\bQuest-1.bmp");
	lpButton2[5] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\bSystem-1.bmp");

	lpInfoBox[0] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\ButtonInfo\\StatusInfo.bmp");
	lpInfoBox[1] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\ButtonInfo\\InvenInfo.bmp");
	lpInfoBox[2] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\ButtonInfo\\SkillInfo.bmp");
	lpInfoBox[3] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\ButtonInfo\\PartyInfo.bmp");
	lpInfoBox[4] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\ButtonInfo\\QuestInfo.bmp");
	lpInfoBox[5] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\ButtonInfo\\SystemInfo.bmp");


	lpMenuButton[0] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\Option.bmp");
	lpMenuButton[1] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\Replay.bmp");
	lpMenuButton[2] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\Exit.bmp");


	lpWalk = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\Button\\Walk.bmp");

	lpChatShowButton = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\Chat\\ChatDownButton.bmp");


	lpSun = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\Flash\\Sun.bmp");
	lpMoon = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\Flash\\Moon.bmp");

	lpGage[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Skill\\P-skill.bmp");
	lpGage[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Skill\\P-skill2.bmp");

	lpBar_Anger = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\sinGage\\Bar_Anger.bmp");
	lpBar_Time = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\sinGage\\Bar_Time.bmp");
	lpBar_Exp = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\sinGage\\Bar_Exp.bmp");
	lpButton_Anger = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\sinGage\\Button_Anger.bmp");

	lpRunInfo = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\ButtonInfo\\Run.bmp");
	lpWalkInfo = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\ButtonInfo\\Walk.bmp");

	lpCameraHandInfo = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\ButtonInfo\\Camera_Hand.bmp");
	lpCameraFixInfo = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\ButtonInfo\\Camera_Fix.bmp");
	lpCameraAutoInfo = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\ButtonInfo\\Camera_Auto.bmp");

	lpMapOnInfo = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\ButtonInfo\\MapOn.bmp");
	lpMapOffInfo = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\ButtonInfo\\MapOff.bmp");

	lpMapOnImage = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\Button\\MapOnImage.bmp");
	lpCameraImage[0] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\Button\\AutoCameraImage.bmp");
	lpCameraImage[1] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\Button\\PixCameraImage.bmp");

	lpLIFESpot = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\Bar_LifeSpot.bmp");
	lpSTMSpot = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\Bar_StaminaSpot.bmp");
	lpMANASpot = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\Bar_ManaSpot.bmp");

	lpReStartMain = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\ReStart\\ReStartMain.bmp");
	lpReStartButton[0] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\ReStart\\ReStart_Field.bmp");
	lpReStartButton[1] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\ReStart\\ReStart_Town.bmp");
	lpReStartButton[2] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\ReStart\\ReStart_Exit.bmp");


	lpSelectSkill_Main[0] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\SkillIcon\\G_Select_Skill.bmp");
	lpSelectSkill_Main[1] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\SkillIcon\\Select_Skill.bmp");

	lpSelectChangeJob[0] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\SkillIcon\\G_Select_ChangeJob.bmp");
	lpSelectChangeJob[1] = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\SkillIcon\\Select_ChangeJob.bmp");

	lpTime7 = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\SkillIcon\\Select_ChangeJob.bmp");

	lpGrowInterLeft = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\inter_01.bmp");
	lpGrowInterMiddle = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\inter_02.bmp");
	lpGrowInterRight = LoadDibSurfaceOffscreen("Assets\\GUI\\Interface\\inter_03.bmp");


}

void cINTERFACE::Release()
{
	int i;

	if(lpLIFE)
	{
		lpLIFE->Release();
		lpLIFE = 0;

	}
	if(lpMP)
	{
		lpMP->Release();
		lpMP = 0;
	}
	if(lpSTM)
	{
		lpSTM->Release();
		lpSTM = 0;
	}

	for(i = 0; i < 6; i++)
	{
		if(lpButton[i])
		{
			lpButton[i]->Release();
			lpButton[i] = 0;

		}
		if(lpButton2[i])
		{
			lpButton2[i]->Release();
			lpButton2[i] = 0;
		}
		if(lpInfoBox[i])
		{
			lpInfoBox[i]->Release();
			lpInfoBox[i] = 0;
		}
	}
	for(i = 0; i < 3; i++)
	{
		if(lpMenuButton[i])
		{
			lpMenuButton[i]->Release();
			lpMenuButton[i] = 0;
		}
	}

	if(lpWalk)
	{
		lpWalk->Release();
		lpWalk = 0;
	}
	if(lpChatShowButton)
	{
		lpChatShowButton->Release();
		lpChatShowButton = 0;
	}
	if(lpSun)
	{
		lpSun->Release();
		lpSun = 0;

	}
	if(lpMoon)
	{
		lpMoon->Release();
		lpMoon = 0;
	}
	if(lpGage[0])
	{
		lpGage[0]->Release();
		lpGage[0] = 0;
	}
	if(lpBar_Anger)
	{
		lpBar_Anger->Release();
		lpBar_Anger = 0;
	}
	if(lpBar_Time)
	{
		lpBar_Time->Release();
		lpBar_Time = 0;
	}
	if(lpBar_Exp)
	{
		lpBar_Exp->Release();
		lpBar_Exp = 0;
	}
	if(lpButton_Anger)
	{
		lpButton_Anger->Release();
		lpButton_Anger = 0;
	}

	if(lpRunInfo)
	{
		lpRunInfo->Release();
		lpRunInfo = 0;
	}
	if(lpWalkInfo)
	{
		lpWalkInfo->Release();
		lpWalkInfo = 0;
	}

	if(lpCameraAutoInfo)
	{
		lpCameraAutoInfo->Release();
		lpCameraAutoInfo = 0;
	}
	if(lpCameraHandInfo)
	{
		lpCameraHandInfo->Release();
		lpCameraHandInfo = 0;
	}
	if(lpCameraFixInfo)
	{
		lpCameraFixInfo->Release();
		lpCameraFixInfo = 0;
	}

	if(lpMapOnInfo)
	{
		lpMapOnInfo->Release();
		lpMapOnInfo = 0;
	}
	if(lpMapOffInfo)
	{
		lpMapOffInfo->Release();
		lpMapOffInfo = 0;
	}
	if(lpMapOnImage)
	{
		lpMapOnImage->Release();
		lpMapOnImage = 0;
	}
	if(lpCameraImage[0])
	{
		lpCameraImage[0]->Release();
		lpCameraImage[0] = 0;
	}
	if(lpCameraImage[1])
	{
		lpCameraImage[1]->Release();
		lpCameraImage[1] = 0;
	}

	if(lpLIFESpot)
	{
		lpLIFESpot->Release();
		lpLIFESpot = 0;
	}
	if(lpSTMSpot)
	{
		lpSTMSpot->Release();
		lpSTMSpot = 0;
	}
	if(lpMANASpot)
	{
		lpMANASpot->Release();
		lpMANASpot = 0;
	}
	if(lpReStartMain)
	{
		lpReStartMain->Release();
		lpReStartMain = 0;

	}

	for(i = 0; i < 3; i++)
	{
		if(lpReStartButton[i])
		{
			lpReStartButton[i]->Release();
			lpReStartButton[i] = 0;
		}
	}
	if(lpReStartMain)
	{
		lpReStartMain->Release();
		lpReStartMain = 0;

	}
	for(i = 0; i < 3; i++)
	{
		if(lpReStartButton[i])
		{
			lpReStartButton[i]->Release();
			lpReStartButton[i] = 0;

		}
	}
	for(i = 0; i < 2; i++)
	{
		if(lpSelectSkill_Main[i])
		{
			lpSelectSkill_Main[i]->Release();
			lpSelectSkill_Main[i] = 0;

		}

		if(lpSelectChangeJob[i])
		{
			lpSelectChangeJob[i]->Release();
			lpSelectChangeJob[i] = 0;

		}
	}
}

int sinWinSizeX[] = { 1024,1280,1600 };
int sinWinSizeXindex[] = { 2,6,11 };
int nCheckSkillDraw = 0;
void cINTERFACE::Draw()
{

	int i = 0;
	int j = 0;


	dsDrawTexImage(cInterFace.MatMenu[0], 800 - 256 - 256, 600 - 128, 256, 128, 255);
	dsDrawTexImage(cInterFace.MatMenu[1], 800 - 256, 600 - 64, 256, 64, 255);


	DrawSprite(800, WinSizeY - 64, lpGrowInterLeft, 0, 0, 66, 64, 777);

	for(i = 0; i < 3; i++)
	{
		if(sinWinSizeX[i] == WinSizeX)
		{
			for(j = 0; j < sinWinSizeXindex[i]; j++)
			{
				DrawSprite(800 + 66 + (64 * j), WinSizeY - 64, lpGrowInterMiddle, 0, 0, 64, 64, 777);
			}
		}
	}

	DrawSprite(800 + 66 + (64 * j), WinSizeY - 64, lpGrowInterRight, 0, 0, 40, 64, 777);





	for(i = 0; i < 3; i++)
	{
		if(sShadowState[i].Flag)
		{
			dsDrawColorBox(sShadowState[i].Color, sShadowState[i].Posi.x, sShadowState[i].Posi.y,
						   sShadowState[i].Size.x, sShadowState[i].Size.y);

		}
	}

	DrawSprite(319, 500 + (94 - sinBmpLength[0]), lpLIFE, 0, (94 - sinBmpLength[0]), 16, 94);
	DrawSprite(465, 500 + (94 - sinBmpLength[1]), lpMP, 0, (94 - sinBmpLength[1]), 16, 94);
	DrawSprite(303, 518 + (76 - sinBmpLength[2]), lpSTM, 0, (76 - sinBmpLength[2]), 8, 76);








	if(ExitButtonClick)
	{
		dsDrawTexImage(MatExitMenu, 698, 504, 128, 64, 255);

		if(sinMenuBottonPosi == 1)
			DrawSprite(698, 504, lpMenuButton[0], 0, 0, 96, 19);

		if(sinMenuBottonPosi == 2)
			DrawSprite(692, 517, lpMenuButton[1], 0, 0, 93, 20);

		if(sinMenuBottonPosi == 3)
			DrawSprite(698, 535, lpMenuButton[2], 0, 0, 96, 19);


	}


	if(hFocusWnd && sinChatInputMode && !usehFocus)
	{

		DrawSprite(7, 580 - SubChatHeight, lpChatShowButton, 0, 0, 22, 19);
	}




	if(DayOrNightFlag == 1)
	{
		DrawSprite(363, 589, lpSun, 0, 0, 13, 13);
		DrawSprite(375, 593, lpBar_Time, 0, 0, sinGageTime2, 5);
	}
	else
	{
		DrawSprite(426, 589, lpMoon, 0, 0, 13, 13);
		DrawSprite(375 + (50 - sinGageTime2), 593, lpBar_Time, (50 - sinGageTime2), 0, 50, 5);

	}




	int TempGage = 0;


	if(sinSkill.pLeftSkill)
	{
		TempGage = (int)((41.0f*(float)sinSkill.pLeftSkill->GageLength) / 35.0f);
		DrawSprite(338, 542 + (41 - TempGage), lpGage[0], 0, 41 - TempGage, 16, 41);
	}

	if(sinSkill.pRightSkill)
	{
		TempGage = (int)((41.0f*(float)sinSkill.pRightSkill->GageLength) / 35.0f);
		DrawSprite(446, 542 + (41 - TempGage), lpGage[1], 0, 41 - TempGage, 16, 41);

	}











	if(sinPKWarningExpFlag)
	{
		if(sinPKWarnigExpTime <= 15)
			DrawSprite(485, 508 + (86 - sinBmpLength[3]), lpBar_Exp, 0, (86 - sinBmpLength[3]), 6, 86);


	}
	else
		DrawSprite(485, 508 + (86 - sinBmpLength[3]), lpBar_Exp, 0, (86 - sinBmpLength[3]), 6, 86);





	if(!sInterFlags.RunFlag)
		DrawSprite(575, 565, lpWalk, 0, 0, 24, 25);

	if(sInterFlags.CameraAutoFlag == 1)
		DrawSprite(575 + 24, 565, lpCameraImage[0], 0, 0, 24, 25);

	if(sInterFlags.CameraAutoFlag == 2)
		DrawSprite(575 + 24, 565, lpCameraImage[1], 0, 0, 24, 25);


	if(sInterFlags.MapOnFlag)
	{
		DrawSprite(575 + 24 + 24, 565, lpMapOnImage, 0, 0, 24, 25);
	}

	switch(sinRunCameraMapPosi)
	{
		case 1:
		if(sInterFlags.RunFlag)
		{
			DrawSprite(575 + 12 - (76 / 2), 565 - 29, lpRunInfo, 0, 0, 77, 27);
		}
		else
		{
			DrawSprite(575 + 12 - (76 / 2), 565 - 29, lpWalkInfo, 0, 0, 77, 27);

		}
		break;
		case 2:
		if(sInterFlags.CameraAutoFlag == 0)
		{
			DrawSprite(575 + 24 + 12 - (76 / 2), 565 - 29, lpCameraHandInfo, 0, 0, 77, 27);
			cHelpPet.PetMessage("*Camera_Hand", 0);
		}
		if(sInterFlags.CameraAutoFlag == 2)
		{
			DrawSprite(575 + 24 + 12 - (76 / 2), 565 - 29, lpCameraFixInfo, 0, 0, 77, 27);
			cHelpPet.PetMessage("*Camera_Fix", 0);

		}
		if(sInterFlags.CameraAutoFlag == 1)
		{
			DrawSprite(575 + 26 + 13 - (76 / 2), 565 - 29, lpCameraAutoInfo, 0, 0, 77, 27);
			cHelpPet.PetMessage("*Camera_Auto", 0);

		}
		break;
		case 3:
		if(sInterFlags.MapOnFlag)
		{
			DrawSprite(575 + 24 + 24 + 12 - (76 / 2), 565 - 29, lpMapOffInfo, 0, 0, 77, 27);

		}
		else
		{
			DrawSprite(575 + 24 + 24 + 12 - (76 / 2), 565 - 29, lpMapOnInfo, 0, 0, 77, 27);

		}
		break;

	}

	for(int t = 0; t < 6; t++)
	{
		if(MouseButtonPosi == t + 1)
		{
			if(InterButtonDown)
			{
				DrawSprite(648 + (t * 25), 560, lpButton2[t], 0, 0, 25, 27);

			}
			else
			{
				DrawSprite(648 + (t * 25), 560, lpButton[t], 0, 0, 25, 27);
				DrawSprite(648 - (77 - 23 - 1) + (t * 25), 560 - 27, lpInfoBox[t], 0, 0, 77, 27);
			}
		}
	}






	if(SkillNpcFlag)
	{
		DrawSprite(SkillMasterMainXY.x, SkillMasterMainXY.y, lpReStartMain, 0, 0, 188, 128);
		DrawSprite(SkillMasterMainXY.x + ReStartButtonRect[0][0], SkillMasterMainXY.y + ReStartButtonRect[0][1], lpSelectSkill_Main[0], 0, 0, 44, 44);
		DrawSprite(SkillMasterMainXY.x + ReStartButtonRect[1][0], SkillMasterMainXY.y + ReStartButtonRect[1][1], lpSelectChangeJob[0], 0, 0, 44, 44);
		if(SkillMasterIndex)
		{
			if(SkillMasterIndex == 1 && SkillMasterOkFlag[0])
				DrawSprite(SkillMasterMainXY.x + ReStartButtonRect[SkillMasterIndex - 1][0], SkillMasterMainXY.y + ReStartButtonRect[SkillMasterIndex - 1][1], lpSelectSkill_Main[1], 0, 0, 44, 44);
			if(SkillMasterIndex == 2 && SkillMasterOkFlag[1])
				DrawSprite(SkillMasterMainXY.x + ReStartButtonRect[SkillMasterIndex - 1][0], SkillMasterMainXY.y + ReStartButtonRect[SkillMasterIndex - 1][1], lpSelectChangeJob[1], 0, 0, 44, 44);
			if(SkillMasterIndex == 3)
				DrawSprite(SkillMasterMainXY.x + ReStartButtonRect[SkillMasterIndex - 1][0], SkillMasterMainXY.y + ReStartButtonRect[SkillMasterIndex - 1][1], lpReStartButton[2], 0, 0, 44, 44);

		}
	}


	if(ShowSkillClose)
	{
		DrawSprite(269, 571 + (256 - sinMoveKindInter[SIN_SKILL]), cShop.lpExit, 0, 0, 20, 20);
		DrawSprite(269, 571 - 27 + (256 - sinMoveKindInter[SIN_SKILL]), cInvenTory.lpExitInfo, 0, 0, 47, 27);
	}


	for(int k = 0; k < 10; k++)
	{
		if(HaEffect[k].Flag)
		{
			dsDrawTexImage(HaEffect[k].Mat, HaEffect[k].Posi.x, HaEffect[k].Posi.y, HaEffect[k].Size.x,
						   HaEffect[k].Size.y, HaEffect[k].Alpha);
		}
	}





	renderDevice.EndScene();
	HDC hdc = NULL;

	char strBuff2[256];
	char strBuff[256];
	int len = 0;
	int x = 0, y = 0;

	//renderDevice.lpDDSBack->GetDC(&hdc);

	SelectObject(hdc, hFont);
	SetBkMode(hdc, TRANSPARENT);

	char *lpInput;


	if(hFocusWnd && sinChatInputMode && !usehFocus)
	{



		GetWindowText(hTextWnd, strBuff2, 240);
		strBuff2[242] = 0x0D;
		len = lstrlen(strBuff2);

		SetBkMode(hdc, TRANSPARENT);

		wsprintf(strBuff, "  %s", strBuff2);

		len = lstrlen(strBuff);
		if(len >= 44)
		{
			lpInput = &strBuff[len - 44];
			len = 44;
		}
		else
			lpInput = strBuff;

		if(sinChatInputMode == 1)
		{
			x = 16; y = 584 - SubChatHeight;
		}
		else
		{
			x = 16; y = 584 - SubChatHeight;
		}

		SetTextColor(hdc, RGB(0, 0, 0));

	#ifdef _LANGUAGE_VEITNAM
		dsTextLineOut(hdc, x + 6, y, lpInput, len);
		SetTextColor(hdc, RGB(255, 255, 255));
		dsTextLineOut(hdc, x + 5, y - 1, lpInput, len);
	#else
		dsTextLineOut(hdc, x + 1, y + 1, lpInput, len);
		SetTextColor(hdc, RGB(255, 255, 255));
		dsTextLineOut(hdc, x, y, lpInput, len);
	#endif

	}

#include "Language\\language.h"
#ifdef _LANGUAGE_JAPANESE
#include <imm.h>

	if(ImeChatLen != len || ImePositon.x != len || ImePositon.y != y)
	{
		HIMC	h = ImmGetContext(hwnd);
		COMPOSITIONFORM	cf;

		int addPoint = 0;

		if(smConfig.ScreenSize.y == 600) addPoint = 0;
		else if(smConfig.ScreenSize.y == 768) addPoint = 163;
		else if(smConfig.ScreenSize.y == 1024) addPoint = 420;

		if(h)
		{
			cf.dwStyle = CFS_FORCE_POSITION;
			cf.ptCurrentPos.x = x + 6 * len;
			cf.ptCurrentPos.y = y + addPoint;
			ImmSetCompositionWindow(h, &cf);

			ImePositon.x = len;
			ImePositon.y = y;
			ImeChatLen = len;
		}
	}
#endif


	if(sinChatDisplayMode)
	{
		if(sinChatDisplayMode == 1)
		{
			if(NoticeChatIndex == 1)
			{


				x = 16; y = 570 - SubChatHeight - 125; i = 3;
				DisplayChatMessage3(hdc, x, y, 44, i, 5);


				x = 16; y = 570 - SubChatHeight - 20; i = 8;
				DisplayChatMessage2(hdc, x, y, 44, i);

			}
			else if(NoticeChatIndex == 2)
			{
				x = 16; y = 570 - SubChatHeight - 20; i = 12;
				DisplayChatMessage3(hdc, x, y, 44, i, 5);
			}
			else
			{
				x = 16; y = 570 - SubChatHeight - 20; i = 12;
				DisplayChatMessage2(hdc, x, y, 44, i);
			}
		}
		else
		{
			if(NoticeChatIndex == 2)
			{
				x = 16; y = 570 - SubChatHeight - 5; i = 8;
				DisplayChatMessage3(hdc, x, y, 44, i, 5);
			}
			else
			{
				x = 16; y = 570 - SubChatHeight - 5; i = 8;
				DisplayChatMessage2(hdc, x, y, 44, i);
			}
		}



	}

	//renderDevice.lpDDSBack->ReleaseDC(hdc);

	int dsDrawOffsetArrayBackup = dsDrawOffsetArray;

	dsDrawOffsetArray = dsARRAY_TOP;


	if(SkillMasterFlag == 1)
	{
		for(i = 0; i < SkillUpInfo.x; i++)
		{
			for(int j = 0; j < SkillUpInfo.y; j++)
			{
				if(i == 0 && j == 0)
					dsDrawTexImage(cItem.MatItemInfoBox_TopLeft, SkillUpInfoPosi.x + (i * 16), SkillUpInfoPosi.y + (j * 16), 16, 16, 255);
				if(j == 0 && i != 0 && i + 1 < SkillUpInfo.x)
					dsDrawTexImage(cItem.MatItemInfoBox_TopCenter, SkillUpInfoPosi.x + (i * 16), SkillUpInfoPosi.y + (j * 16), 16, 16, 255);
				if(j == 0 && i + 1 == SkillUpInfo.x)
					dsDrawTexImage(cItem.MatItemInfoBox_TopRight, SkillUpInfoPosi.x + (i * 16), SkillUpInfoPosi.y + (j * 16), 16, 16, 255);

				if(i == 0 && j != 0 && j + 1 != SkillUpInfo.y)
					dsDrawTexImage(cItem.MatItemInfoBox_Left, SkillUpInfoPosi.x + (i * 16), SkillUpInfoPosi.y + (j * 16), 16, 16, 255);
				if(i != 0 && j != 0 && i + 1 != SkillUpInfo.x && j + 1 != SkillUpInfo.y)
					dsDrawTexImage(cItem.MatItemInfoBox_Center, SkillUpInfoPosi.x + (i * 16), SkillUpInfoPosi.y + (j * 16), 16, 16, 255);
				if(i + 1 == SkillUpInfo.x && j != 0 && j + 1 != SkillUpInfo.y)
					dsDrawTexImage(cItem.MatItemInfoBox_Right, SkillUpInfoPosi.x + (i * 16), SkillUpInfoPosi.y + (j * 16), 16, 16, 255);

				if(i == 0 && j + 1 == SkillUpInfo.y)
					dsDrawTexImage(cItem.MatItemInfoBox_BottomLeft, SkillUpInfoPosi.x + (i * 16), SkillUpInfoPosi.y + (j * 16), 16, 16, 255);
				if(i != 0 && j + 1 == SkillUpInfo.y && i + 1 != SkillUpInfo.x)
					dsDrawTexImage(cItem.MatItemInfoBox_BottomCenter, SkillUpInfoPosi.x + (i * 16), SkillUpInfoPosi.y + (j * 16), 16, 16, 255);
				if(j + 1 == SkillUpInfo.y && i + 1 == SkillUpInfo.x)
					dsDrawTexImage(cItem.MatItemInfoBox_BottomRight, SkillUpInfoPosi.x + (i * 16), SkillUpInfoPosi.y + (j * 16), 16, 16, 255);


			}
		}

		if(ShowSkillUpInfo)
		{
			for(i = 0; i < 10; i++)
			{
				if(SkillIconIndex[i])
				{
					DrawSprite(SkillUpInfoPosi.x + SkillIconPosi.x + (i * 18) - 10, SkillUpInfoPosi.y + SkillIconPosi.y, cSkill.lpWeaponIcon[SkillIconIndex[i]], 0, 0, 18, 24);
				}
			}

		}

		renderDevice.EndScene();

		HDC	hdc = NULL;

		int BoldFlag = 0;
		int MasteryLen = 0;
		int MasteryShowX = 0;

		char strBuff[128];
		memset(strBuff, 0, sizeof(strBuff));
		//renderDevice.lpDDSBack->GetDC(&hdc);
		SelectObject(hdc, sinFont);
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(255, 255, 255));

		if(SkillMasterFlag == 1 && !ShowSkillUpInfo)
		{
			SelectObject(hdc, sinBoldFont);
			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, RGB(222, 231, 255));
			dsTextLineOut(hdc, 100, 225 - 80, SkillUseInfoText[0], lstrlen(SkillUseInfoText[0]));


			if(sinSkill.SkillPoint || sinSkill.SkillPoint4)
			{
				SelectObject(hdc, sinFont);
				SetBkMode(hdc, TRANSPARENT);
				SetTextColor(hdc, RGB(255, 255, 255));

				dsTextLineOut(hdc, 100, 260 - 80, SkillUseInfoText[1], lstrlen(SkillUseInfoText[1]));
				dsTextLineOut(hdc, 100, 280 - 80, SkillUseInfoText[2], lstrlen(SkillUseInfoText[2]));
				wsprintf(strBuff, sinMsgSkillPoint, sinSkill.SkillPoint);
				SelectObject(hdc, sinBoldFont);
				SetBkMode(hdc, TRANSPARENT);
				SetTextColor(hdc, RGB(247, 243, 193));
				dsTextLineOut(hdc, 100, 310 - 80, strBuff, lstrlen(strBuff));

				wsprintf(strBuff, sinMsgEliteSkillPoint, sinSkill.SkillPoint4);
				SelectObject(hdc, sinBoldFont);
				SetBkMode(hdc, TRANSPARENT);
				SetTextColor(hdc, RGB(147, 243, 193));
				dsTextLineOut(hdc, 103, 310 - 55, strBuff, lstrlen(strBuff));
			}
			else
			{
				SelectObject(hdc, sinFont);
				SetBkMode(hdc, TRANSPARENT);
				SetTextColor(hdc, RGB(255, 64, 64));

				dsTextLineOut(hdc, 100, 260 - 80, SkillUseInfoText[3], lstrlen(SkillUseInfoText[3]));
				dsTextLineOut(hdc, 100, 280 - 80, SkillUseInfoText[4], lstrlen(SkillUseInfoText[4]));

			}


		}
		//renderDevice.lpDDSBack->ReleaseDC(hdc);
		renderDevice.BeginScene();
	}


	if(SkillMasterFlag && !ShowSkillUpInfo && (CheckQuestButtonShow1 || CheckQuestButtonShow2 || CheckQuestButtonShow3))
	{
		if(sinChangeJobButtonShow || sinChangeJobButtonShow2 || sinChangeJobButtonShow3 || sinChangeJobButtonShow4)
		{
			DrawSprite(240, 380, lpSelectChangeJob[1], 0, 0, 44, 44);
			nCheckSkillDraw = 1;
		}
		else
		{
			DrawSprite(240, 380, lpSelectChangeJob[0], 0, 0, 44, 44);
			nCheckSkillDraw = 2;
		}
	}

	if(SkillMasterFlag && !ShowSkillUpInfo && (nCheckSkillDraw == 1))
	{
		DrawSprite(240, 380, lpSelectChangeJob[1], 0, 0, 44, 44);
	}

	if(SkillMasterFlag && !ShowSkillUpInfo && (nCheckSkillDraw == 2))
	{
		DrawSprite(240, 380, lpSelectChangeJob[0], 0, 0, 44, 44);
	}

	dsDrawOffsetArray = dsDrawOffsetArrayBackup;


	if(SkillInfoShowFlag && !ShowSkillUpInfo)
	{
		if(SkillInfoShowFlag == 2)
			dsDrawOffsetArray = dsARRAY_TOP;
		for(i = 0; i < SkillBoxSize.x; i++)
		{
			for(int j = 0; j < SkillBoxSize.y; j++)
			{
				if(i == 0 && j == 0)
					dsDrawTexImage(cItem.MatItemInfoBox_TopLeft, SkillInfoBoxPosi.x + (i * 16), SkillInfoBoxPosi.y + (j * 16), 16, 16, 255);
				if(j == 0 && i != 0 && i + 1 < SkillBoxSize.x)
					dsDrawTexImage(cItem.MatItemInfoBox_TopCenter, SkillInfoBoxPosi.x + (i * 16), SkillInfoBoxPosi.y + (j * 16), 16, 16, 255);
				if(j == 0 && i + 1 == SkillBoxSize.x)

					dsDrawTexImage(cItem.MatItemInfoBox_TopRight, SkillInfoBoxPosi.x + (i * 16), SkillInfoBoxPosi.y + (j * 16), 16, 16, 255);

				if(i == 0 && j != 0 && j + 1 != SkillBoxSize.y)
					dsDrawTexImage(cItem.MatItemInfoBox_Left, SkillInfoBoxPosi.x + (i * 16), SkillInfoBoxPosi.y + (j * 16), 16, 16, 255);
				if(i != 0 && j != 0 && i + 1 != SkillBoxSize.x && j + 1 != SkillBoxSize.y)
					dsDrawTexImage(cItem.MatItemInfoBox_Center, SkillInfoBoxPosi.x + (i * 16), SkillInfoBoxPosi.y + (j * 16), 16, 16, 255);
				if(i + 1 == SkillBoxSize.x && j != 0 && j + 1 != SkillBoxSize.y)
					dsDrawTexImage(cItem.MatItemInfoBox_Right, SkillInfoBoxPosi.x + (i * 16), SkillInfoBoxPosi.y + (j * 16), 16, 16, 255);

				if(i == 0 && j + 1 == SkillBoxSize.y)
					dsDrawTexImage(cItem.MatItemInfoBox_BottomLeft, SkillInfoBoxPosi.x + (i * 16), SkillInfoBoxPosi.y + (j * 16), 16, 16, 255);
				if(i != 0 && j + 1 == SkillBoxSize.y && i + 1 != SkillBoxSize.x)
					dsDrawTexImage(cItem.MatItemInfoBox_BottomCenter, SkillInfoBoxPosi.x + (i * 16), SkillInfoBoxPosi.y + (j * 16), 16, 16, 255);
				if(j + 1 == SkillBoxSize.y && i + 1 == SkillBoxSize.x)
					dsDrawTexImage(cItem.MatItemInfoBox_BottomRight, SkillInfoBoxPosi.x + (i * 16), SkillInfoBoxPosi.y + (j * 16), 16, 16, 255);


			}
		}
		for(i = 0; i < 10; i++)
		{
			if(SkillIconIndex[i])
			{
				DrawSprite(SkillInfoBoxPosi.x + SkillIconPosi.x + (i * 18), SkillInfoBoxPosi.y + SkillIconPosi.y, cSkill.lpWeaponIcon[SkillIconIndex[i]], 0, 0, 18, 24);

			}
		}
	}

	if(InfoMessageBoxPos.x != 0 || InfoMessageBoxPos.y != 0)
	{
		dsDrawTexImage(cItem.MatItemInfoBox_Center, InfoMessageBoxPos.x - 5, InfoMessageBoxPos.y - 1, lstrlen(szInfoMsgBuff5) * 6, 13, 255);
	}







	cSkill.ShowClearSkillPointButton(SkillInfoBoxPosi.x + (SkillBoxSize.x * 16), SkillInfoBoxPosi.y + (SkillBoxSize.y * 16));

	renderDevice.BeginScene();

}

void cINTERFACE::resize()
{

}

void resizeSin()
{
	cInterFace.resize();
}

DWORD dwCheckTime;
int   CheckNotUseSkillTime[3] = { 0,0,0 };
int   CheckNotUseSkillCount[3] = { 0,0,0 };
int   CheckTime2[3] = { 0,0,0 };
int   CheckExpFlag = 0;
int   CheckExpFlag2 = 0;
int   CheckExpTime = 0;

DWORD dwTestKeyTime = 0;
int   TeskKeyMessageCnt = 0;
char *szTestKeyMsg[6] = { "나!  &(^_^)&    ",
						 "노!  /(^_^)/   ",
						 "나!  *(^_^)*  ",
						 "",
						 "",
						 "", };

void cINTERFACE::Main()
{
	if(GetFieldMapCursor() == TRUE && cInterFace.sInterFlags.MapOnFlag)
	{
		cHelpPet.PetMessage("*Mini_Map", 0);
	}



	if(sinChatEnter)
	{



	}



	if(cInterFace.ChatFlag)
	{
		if(SubChatHeight)
		{
			if(0 < pCursorPos.x && 300 > pCursorPos.x &&
			   294 < pCursorPos.y && 294 + 116 > pCursorPos.y)
			{
				if(!ChatKindIndexNum)
				{
					cHelpPet.PetMessage("*ChatBox", 0);
				}

			}
		}
		else
		{
			if(0 < pCursorPos.x && 305 > pCursorPos.x &&
			   600 - 192 < pCursorPos.y && 600 - 192 + 210 > pCursorPos.y)
			{
				if(!ChatKindIndexNum)
				{
					cHelpPet.PetMessage("*ChatBox", 0);
				}

			}
		}
	}


	if(365 < pCursorPos.x && 435 > pCursorPos.x &&
	   589 < pCursorPos.y && 596 > pCursorPos.y)
	{
		cHelpPet.PetMessage("*DayandNight", 0);

	}


	GetWordTimeDisplay();


	if(sinPKWarningExpFlag)
	{
		sinPKWarnigExpTime++;
		if(sinPKWarnigExpTime > 30)
			sinPKWarnigExpTime = 0;

	}
	else
		sinPKWarnigExpTime = 0;



	if(TestKeyAniFlag)
	{
		dwTestKeyTime++;
		if(dwTestKeyTime > 30)
		{
			dwTestKeyTime = 0;
			SendChatMessageToServer(szTestKeyMsg[TeskKeyMessageCnt]);
			TeskKeyMessageCnt++;
			if(TeskKeyMessageCnt >= 6)
			{
				TestKeyAniFlag = 0;
				dwTestKeyTime = 0;
				TeskKeyMessageCnt = 0;

			}
		}
	}


	sinMenuBottonPosi = 0;

	if(lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_DEAD && lpCurPlayer->FrameCounter > 100)
	{
		ReStartFlag = 1;
		if(!CheckExpFlag && !CheckExpFlag2)
		{
			if(!CheckFieldContExp())
				RestartCheckExp = 1;

			CheckExpFlag = 1;
		}

	}
	if(CheckExpFlag2)
	{
		CheckExpTime++;
		if(CheckExpTime > 100)
		{
			CheckExpFlag2 = 0;
			CheckExpTime = 0;

		}
	}

	if(dwGameHour >= 8 && dwGameHour <= 18)
	{
		SunandMoonFlag[0] = 1;
		SunandMoonFlag[1] = 0;
	}
	else
	{
		SunandMoonFlag[0] = 0;
		SunandMoonFlag[1] = 1;

	}
	if(sinLoadOK)
	{
		if(!InitStateFlag)InitState();
		CheckingState();
	}

	MouseButtonPosi = 0;
	for(int i = 0; i < 6; i++)
	{
		if(ButtonRect[i][0] < pCursorPos.x  && ButtonRect[i][2] > pCursorPos.x  &&
		   ButtonRect[i][1] < pCursorPos.y  && ButtonRect[i][3] > pCursorPos.y)
		{
			MouseButtonPosi = i + 1;
			switch(MouseButtonPosi)
			{
				case 1:
				cHelpPet.PetMessage("*CarStatus", 0);
				break;
				case 2:
				cHelpPet.PetMessage("*InvenTory", 0);
				break;
				case 3:
				cHelpPet.PetMessage("*Skill", 0);
				break;
				case 4:
				cHelpPet.PetMessage("*Party", 0);
				break;
				case 5:
				cHelpPet.PetMessage("*Quest", 0);
				break;
				case 6:
				cHelpPet.PetMessage("*System", 0);
				break;

			}
		}
	}
	sinRunCameraMapPosi = 0;
	for(int i = 0; i < 3; i++)
	{
		if(sinRunCameraMap[i][0] < pCursorPos.x  && sinRunCameraMap[i][2] > pCursorPos.x  &&
		   sinRunCameraMap[i][1] < pCursorPos.y  && sinRunCameraMap[i][3] > pCursorPos.y)
		{
			sinRunCameraMapPosi = i + 1;
			switch(sinRunCameraMapPosi)
			{
				case 1:
				cHelpPet.PetMessage("*RunAndWalk", 0);
				break;
				case 2:

				break;
				case 3:

				break;

			}
		}
	}

	if(ExitButtonClick)
	{
		if(699 < pCursorPos.x && 795 > pCursorPos.x &&
		   535 < pCursorPos.y && 555 > pCursorPos.y)
			sinMenuBottonPosi = 3;

		if(698 < pCursorPos.x && 795 > pCursorPos.x &&
		   504 < pCursorPos.y && 524 > pCursorPos.y)
			sinMenuBottonPosi = 1;









	}


	if(cInvenTory.OpenFlag || cCharStatus.OpenFlag || cSkill.OpenFlag)
	{
		SubChatHeight = 170;
		sinChatInputMode = 0;
		sinChatDisplayMode = 0;
		if(SubChatHeight >= 170)
		{
			SubChatHeight = 170;

		}

	}
	else
		SubChatHeight = 0;

	if(sinChatEnter)
	{
		if(SubChatHeight >= 170)
			sinChatInputMode = 2;
		else
			sinChatInputMode = 1;

	}
	else
		sinChatInputMode = 0;

	if(ChatFlag)
	{
		if(SubChatHeight >= 170)
			sinChatDisplayMode = 2;
		else
			sinChatDisplayMode = 1;

	}
	else
		sinChatDisplayMode = 0;



	CheckingState();
	ShowParaState();
	ShowExpPercent();



	ReStartIndex = 0;
	memset(szReStartMsg, 0, lstrlen(szReStartMsg));
	memset(szReStartMsg2, 0, lstrlen(szReStartMsg2));

	if(ReStartFlag)
	{
		sinMenuBottonPosi = 0;
		for(int i = 0; i < 3; i++)
		{
			if(ReStartMainXY.x + ReStartButtonRect[i][0] < pRealCursorPos.x  && ReStartMainXY.x + ReStartButtonRect[i][2] > pRealCursorPos.x  &&
			   ReStartMainXY.y + ReStartButtonRect[i][1] < pRealCursorPos.y  && ReStartMainXY.y + ReStartButtonRect[i][3] > pRealCursorPos.y)
			{
				if(RestartCheckExp)
				{
					if(i == 0)
					{
						ReStartIndex = i + 1;
						strcpy_s(szReStartMsg, ReStartMsg[3]);
						strcpy_s(szReStartMsg2, ReStartMsg2[3]);

					}
					else
					{
						ReStartIndex = i + 1;
						strcpy_s(szReStartMsg, ReStartMsg[i]);
						strcpy_s(szReStartMsg2, ReStartMsg2[i]);
					}

				}
				else if(i == 0 && lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_CASTLE)
				{
					ReStartIndex = 0;
				}
				else
				{
					ReStartIndex = i + 1;
					strcpy_s(szReStartMsg, ReStartMsg[i]);
					strcpy_s(szReStartMsg2, ReStartMsg2[i]);
				}

			}
		}
		dwCheckTime++;
		if(dwCheckTime > 70 * 20)
		{
			ReStartFlag = 0;
			ReStartOptionIndex = RESTART_TOWN;
			CheckExpFlag = 0;
			CheckExpFlag2 = 1;
			RestartCheckExp = 0;
		}

	}
	else
		dwCheckTime = 0;

	SkillMasterIndex = 0;
	memset(szSkillMasterMsg, 0, lstrlen(szSkillMasterMsg));
	memset(szSkillMasterMsg2, 0, lstrlen(szSkillMasterMsg2));


	if(SkillNpcFlag)
	{

		sinMenuBottonPosi = 0;
		for(int i = 0; i < 3; i++)
		{
			if(SkillMasterMainXY.x + ReStartButtonRect[i][0] < pCursorPos.x  && SkillMasterMainXY.x + ReStartButtonRect[i][2] > pCursorPos.x  &&
			   SkillMasterMainXY.y + ReStartButtonRect[i][1] < pCursorPos.y  && SkillMasterMainXY.y + ReStartButtonRect[i][3] > pCursorPos.y)
			{
				SkillMasterIndex = i + 1;
				strcpy_s(szSkillMasterMsg, SkillMaster[i]);
				strcpy_s(szSkillMasterMsg2, SkillMaster2[i]);

			}
		}
	}

	for(int t = 0; t < 3; t++)
	{
		if(NotUseSkillElement[t])
		{
			CheckNotUseSkillTime[t]++;
			if(CheckNotUseSkillTime[t] > 12)
			{
				if(NotUseSkillEffect[t])NotUseSkillEffect[t] = 0;
				else NotUseSkillEffect[t] = 1;
				CheckNotUseSkillTime[t] = 0;
				CheckNotUseSkillCount[t]++;
				if(CheckNotUseSkillCount[t] > 4)
				{
					CheckNotUseSkillCount[t] = 0;
					CheckNotUseSkillTime[t] = 0;
					NotUseSkillEffect[t] = 0;
					NotUseSkillElement[t] = 0;
					SkillMouseButtonPosi[0] = 0;
					SkillMouseButtonPosi[1] = 0;


				}

			}
		}
		if(NotUseSkillEffect[t])
		{
			CheckTime2[t]++;

		}
		else
			CheckTime2[t] = 0;
		if(CheckTime2[t] > 20)
			NotUseSkillEffect[t] = 0;


	}


	for(int k = 0; k < MAX_HAEFFECTNUM; k++)
	{
		if(HaEffect[k].Flag)
		{
			if(HaEffect[k].Time < 3000)
				HaEffect[k].Time += 20;

			switch(HaEffect[k].Time / 255)
			{
				case 0:
				HaEffect[k].Alpha = 255;
				break;
				case 1:
				HaEffect[k].Alpha = 255;
				break;
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:

				HaEffect[k].Alpha -= 10;
				HaEffect[k].Posi.x -= 1;
				HaEffect[k].Posi.y -= 1;
				HaEffect[k].Size.x += 3;
				HaEffect[k].Size.y += 3;
				if(HaEffect[k].Alpha <= 0)
				{
					HaEffect[k].Alpha = 0;
					HaEffect[k].Time = 0;
					HaEffect[k].Flag = 0;
				}
				break;
			};
		}
	}


}

void cINTERFACE::Close()
{
	Release();
}

void cINTERFACE::LButtonDown(int x, int y)
{

	switch(sinRunCameraMapPosi)
	{
		case 1:

		break;
		case 3:

		break;
	}




	if(365 < pCursorPos.x && 435 > pCursorPos.x &&
	   589 < pCursorPos.y && 596 > pCursorPos.y)
	{
		cHelpPet.PetMessage("*DayandNight", 1);

	}


	if(pCursorPos.x > 315 && pCursorPos.x < 337 && pCursorPos.y > 500 && pCursorPos.y < 594)
	{
		cHelpPet.PetMessage("*Bar_Life", 1);
	}
	if(pCursorPos.x > 463 && pCursorPos.x < 483 && pCursorPos.y > 498 && pCursorPos.y < 595)
	{
		cHelpPet.PetMessage("*Bar_Mana", 1);
	}
	if(pCursorPos.x > 300 && pCursorPos.x < 313 && pCursorPos.y > 513 && pCursorPos.y < 595)
	{
		cHelpPet.PetMessage("*Bar_Stamina", 1);
	}
	if(pCursorPos.x > 483 && pCursorPos.x < 483 + 10 && pCursorPos.y > 513 && pCursorPos.y < 595)
	{
		cHelpPet.PetMessage("*Bar_Exp", 1);
	}
	if(pCursorPos.x > 500 && pCursorPos.x < 570 && pCursorPos.y > 540 && pCursorPos.y < 594)
	{
		cHelpPet.PetMessage("*Exp_Num", 1);
	}
	if(GetFieldMapCursor() == TRUE && cInterFace.sInterFlags.MapOnFlag)
	{
		cHelpPet.PetMessage("*Mini_Map", 1);

	}




	if(cInterFace.ChatFlag)
	{
		if(SubChatHeight)
		{
			if(0 < pCursorPos.x && 300 > pCursorPos.x &&
			   294 < pCursorPos.y && 294 + 116 > pCursorPos.y)
			{
				if(!ChatKindIndexNum)
				{
					cHelpPet.PetMessage("*ChatBox", 1);
				}

			}
		}
		else
		{
			if(0 < pCursorPos.x && 305 > pCursorPos.x &&
			   600 - 192 < pCursorPos.y && 600 - 192 + 210 > pCursorPos.y)
			{
				if(!ChatKindIndexNum)
				{
					cHelpPet.PetMessage("*ChatBox", 1);
				}

			}
		}
	}

	SkillMouseButtonPosi[0] = 1;
	ChangeJobButtonclick = 0;
	ReStartOptionIndex = 0;

	if(x > 7 && 22 > x && y > 579 - SubChatHeight && y < 579 + 19 - SubChatHeight)
	{
		if(!ChatFlag)ChatFlag = 1;
		else ChatFlag = 0;
		if(ChatFlag)sinChatEnter = 1;
	}
	switch(sinRunCameraMapPosi)
	{
		case 1:
		if(sInterFlags.RunFlag)sInterFlags.RunFlag = 0;
		else sInterFlags.RunFlag = 1;
		break;
		case 2:
		sInterFlags.CameraAutoFlag++;
		if(sInterFlags.CameraAutoFlag > 2)sInterFlags.CameraAutoFlag = 0;

		break;
		case 3:
		if(sInterFlags.MapOnFlag)sInterFlags.MapOnFlag = 0;
		else sInterFlags.MapOnFlag = 1;

		break;

	};

	if(sinMenuBottonPosi == 3)
	{
		QuitGame();
	}

	char *HelpFilePath = "image\\Sinimage\\Help\\Help.sin";
	if(sinMenuBottonPosi == 1)
	{
		cSinHelp.sinShowHelp(SIN_HELP_KIND_NORMAL, 208, 61 - 50, 11, 11, RGBA_MAKE(19, 27, 20, 165), HelpFilePath);
		ExitButtonClick = 0;
		HelpBoxKindIndex = SIN_HELP;
	}

	if(MouseButtonPosi)
	{
		InterButtonDown = 1;
		switch(MouseButtonPosi)
		{
			case 1:
			cHelpPet.PetMessage("*CarStatus", 1);
			break;
			case 2:
			cHelpPet.PetMessage("*InvenTory", 1);
			break;
			case 3:
			cHelpPet.PetMessage("*Skill", 1);
			break;
			case 4:
			cHelpPet.PetMessage("*Party", 1);
			break;
			case 5:
			cHelpPet.PetMessage("*Quest", 1);
			break;
			case 6:
			cHelpPet.PetMessage("*System", 1);
			break;
		}

	}
	if(ReStartFlag)
	{
		switch(ReStartIndex)
		{
			case RESTART_TOWN:
			ReStartOptionIndex = RESTART_TOWN;
			ReStartFlag = 0;
			RestartCheckExp = 0;

			break;
			case RESTART_FEILD:
			if(RestartCheckExp)break;
			ReStartOptionIndex = RESTART_FEILD;
			ReStartFlag = 0;
			RestartCheckExp = 0;

			break;
			case RESTART_EXIT:
			ReStartOptionIndex = RESTART_EXIT;
			ReStartFlag = 0;
			RestartCheckExp = 0;

			break;

		}

		CheckExpFlag2 = 1;
		CheckExpFlag = 0;

	}

	if(SkillMasterIndex)
	{

		if(SkillMasterIndex == 1 && SkillMasterOkFlag[0])
		{
			SkillMasterFlag = SkillMasterIndex;
			SkillNpcFlag = 0;
			cSkill.OpenFlag = 1;
			cInterFace.CheckAllBox(SIN_SKILL);

		}
		if(SkillMasterIndex == 2 && SkillMasterOkFlag[1])
		{
			SkillMasterFlag = SkillMasterIndex;
			SkillNpcFlag = 0;

			sinJobList = GetJobDataCode(sinChar->JOB_CODE, sinChar->ChangeJob + 1);
			cMessageBox.ShowMessage3(MESSAGE_CHANGE_JOB, sinJobList->szName2);


		}

		if(SkillMasterIndex == 3)
		{
			SkillMasterFlag = SkillMasterIndex;
			SkillNpcFlag = 0;
		}
	}

}

void cINTERFACE::LButtonUp(int x, int y)
{
	if(MouseButtonPosi)
	{
		switch(MouseButtonPosi)
		{
			case 1:
			if(cCharStatus.OpenFlag)cCharStatus.OpenFlag = SIN_CLOSE;
			else cCharStatus.OpenFlag = SIN_OPEN;
			cInterFace.CheckAllBox(SIN_CHARSTATUS);
			if(cCharStatus.OpenFlag)
			{
				if(!sinFireShow)
				{
					StartMenuFlame(0, 350);
					sinPlaySound(0);

				}
				else
					sinPlaySound(SIN_SOUND_SHOW_INTER);
				sinFireShow = 1;
			}

			break;
			case 2:
			if(cInvenTory.OpenFlag)cInvenTory.OpenFlag = SIN_CLOSE;
			else cInvenTory.OpenFlag = SIN_OPEN;
			cInterFace.CheckAllBox(SIN_INVENTORY);
			if(cInvenTory.OpenFlag)
			{
				if(!sinFireShow)
				{
					StartMenuFlame(0, 350);
					sinPlaySound(0);
				}
				else
					sinPlaySound(SIN_SOUND_SHOW_INTER);

				sinFireShow = 1;
			}

			break;
			case 3:

			if(cSkill.OpenFlag == SIN_CLOSE)cSkill.OpenFlag = SIN_OPEN;
			else cSkill.OpenFlag = SIN_CLOSE;
			cInterFace.CheckAllBox(SIN_SKILL);
			if(cSkill.OpenFlag)
			{
				if(!sinFireShow)
				{
					StartMenuFlame(0, 350);
					sinPlaySound(0);
				}
				else
					sinPlaySound(SIN_SOUND_SHOW_INTER);

				sinFireShow = 1;
			}

			break;

			case 4:
			ShowParty();

			break;

			case 5:
			ShowQuest();

			break;

			case 6:
			if(!ExitButtonClick)ExitButtonClick = 1;
			else ExitButtonClick = 0;
			cInterFace.CheckAllBox(SIN_SYSTEM);

			break;
		}

	}

	InterButtonDown = 0;


}

void cINTERFACE::RButtonDown(int x, int y)
{

	if(GetFieldMapCursor() == TRUE && cInterFace.sInterFlags.MapOnFlag)
	{
		cHelpPet.PetMessage("*Mini_Map", 2);

	}


	if(MouseButtonPosi)
	{
		switch(MouseButtonPosi)
		{
			case 1:
			cHelpPet.PetMessage("*CarStatus", 2);
			break;
			case 2:
			cHelpPet.PetMessage("*InvenTory", 2);
			break;
			case 3:
			cHelpPet.PetMessage("*Skill", 2);
			break;
			case 4:
			cHelpPet.PetMessage("*Party", 2);
			break;
			case 5:
			cHelpPet.PetMessage("*Quest", 2);
			break;
			case 6:
			cHelpPet.PetMessage("*System", 2);
			break;
		}

	}

	switch(sinRunCameraMapPosi)
	{
		case 1:
		cHelpPet.PetMessage("*RunAndWalk", 2);
		break;
		case 2:
		if(sInterFlags.CameraAutoFlag == 0)
		{
			cHelpPet.PetMessage("*Camera_Hand", 2);
		}
		if(sInterFlags.CameraAutoFlag == 2)
		{
			cHelpPet.PetMessage("*Camera_Fix", 2);
		}
		if(sInterFlags.CameraAutoFlag == 1)
		{
			cHelpPet.PetMessage("*Camera_Auto", 2);
		}

		break;
		case 3:

		break;
	}





	if(365 < pCursorPos.x && 435 > pCursorPos.x &&
	   589 < pCursorPos.y && 596 > pCursorPos.y)
	{
		cHelpPet.PetMessage("*DayandNight", 2);

	}


	if(pCursorPos.x > 315 && pCursorPos.x < 337 && pCursorPos.y > 500 && pCursorPos.y < 594)
	{
		cHelpPet.PetMessage("*Bar_Life", 2);
	}
	if(pCursorPos.x > 463 && pCursorPos.x < 483 && pCursorPos.y > 498 && pCursorPos.y < 595)
	{
		cHelpPet.PetMessage("*Bar_Mana", 2);
	}
	if(pCursorPos.x > 300 && pCursorPos.x < 313 && pCursorPos.y > 513 && pCursorPos.y < 595)
	{
		cHelpPet.PetMessage("*Bar_Stamina", 2);
	}
	if(pCursorPos.x > 483 && pCursorPos.x < 483 + 10 && pCursorPos.y > 513 && pCursorPos.y < 595)
	{
		cHelpPet.PetMessage("*Bar_Exp", 2);
	}
	if(pCursorPos.x > 500 && pCursorPos.x < 570 && pCursorPos.y > 540 && pCursorPos.y < 594)
	{
		cHelpPet.PetMessage("*Exp_Num", 2);
	}



	if(cInterFace.ChatFlag)
	{
		if(SubChatHeight)
		{
			if(0 < pCursorPos.x && 300 > pCursorPos.x &&
			   294 < pCursorPos.y && 294 + 116 > pCursorPos.y)
			{
				if(!ChatKindIndexNum)
				{
					cHelpPet.PetMessage("*ChatBox", 2);
				}

			}
		}
		else
		{
			if(0 < pCursorPos.x && 305 > pCursorPos.x &&
			   600 - 192 < pCursorPos.y && 600 - 192 + 210 > pCursorPos.y)
			{
				if(!ChatKindIndexNum)
				{
					cHelpPet.PetMessage("*ChatBox", 2);
				}

			}
		}
	}

	SkillMouseButtonPosi[1] = 1;
}

void cINTERFACE::RButtonUp(int x, int y)
{

}

char InputSecretCode[256];
char sinBuff[256];
int  ResetQuset3Flag = 0;

void cINTERFACE::KeyDown()
{

	if(hFocusWnd)
	{

		if(smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
		{
			GetWindowText(hFocusWnd, InputSecretCode, 90);
			if(InputSecretCode[0])
			{
				if(InputSecretCode[0] == '/')
				{
					memset(sinBuff, 0, sizeof(sinBuff));
					wsprintf(sinBuff, "%s", InputSecretCode);
				}
			}
		}
	}


	if(VRKeyBuff[VK_CONTROL])
	{
		CheckExpPercentControl();

	}
	else
		sinPKWarningExpFlag = 0;







	int t = 0;


	if(sinGetKeyClick(VK_RETURN))
	{
		if(VRKeyBuff[VK_CONTROL])
		{
			if(!ChatFlag)
				ChatFlag = 1;
			else ChatFlag = 0;

		}

		if(!lstrcmpi(sinBuff, "/마군오오오오에요") || !lstrcmpi(sinBuff, "/PassMature"))
		{
			sinBuff[0] = 0;
			sinSecretFlag = 1;
			TestKeyAniFlag = 1;
			cInvenTory.ReFormInvenItem();
			cInvenTory.ReFormPotionNum();
			ReformCharForm();

		}
		if(!lstrcmpi(sinBuff, "/날린다뇨!") || !lstrcmpi(sinBuff, "/FuckingInven!"))
		{
			memset(cInvenTory.InvenItem, 0, sizeof(sITEM) * 100);
			memset(cInvenTory.InvenItemTemp, 0, sizeof(sITEM) * 100);
			cInvenTory.ReFormInvenItem();
			cInvenTory.ReFormPotionNum();
			sinChar->Money = 0;
			ReformCharForm();
			SendSaveMoney();
			SendChatMessageToServer(" T.T Oh, No ~~~");

		}


		char sinTestBuff5[256], sinTestBuff6[256];

		if(smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
		{
			if(sinBuff[0])
			{
				memset(sinTestBuff5, 0, sizeof(sinTestBuff5));
				memset(sinTestBuff6, 0, sizeof(sinTestBuff6));

				sscanf(sinBuff, "%s %s", sinTestBuff5, sinTestBuff6);

				if(!lstrcmp(sinTestBuff5, "/임군100퀘스트") || !lstrcmpi(sinBuff, "/MrIm's100"))
				{
					if(sinTestBuff6[0])
					{
					#ifdef	_WINMODE_DEBUG
						if(atoi(&sinTestBuff6[0]) == 1)
						{
							if(chaQuest.sHaQuest100LV.CODE)
							{
								memset(&chaQuest.sHaQuest100LV, 0, sizeof(sQUEST_ELEMENTARY));
								cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
							}
						}
						if(atoi(&sinTestBuff6[0]) == 2)
						{
							if(haElementaryQuestLog)
								haElementaryQuestLog = (haElementaryQuestLog - QUESTBIT_FURYOFPHANTOM);
							chaQuest.sHaQuest100LV.State = 12;
						}
						SaveGameData();
						SendChatMessageToServer("MrIm: It's me");
						memset(sinTestBuff5, 0, sizeof(sinTestBuff5));
						memset(sinTestBuff6, 0, sizeof(sinTestBuff6));
						memset(sinBuff, 0, sizeof(sinBuff));
					#endif
					}

				}


				if(!lstrcmp(sinTestBuff5, "/임군초보퀘스트") || !lstrcmpi(sinTestBuff5, "/MrIm'sbeginner"))
				{
					if(sinTestBuff6[0])
					{
					#ifdef	_WINMODE_DEBUG
						for(int i = 0; i < 8; i++)
						{
							if(chaQuest.sHaQuestElementary[i].CODE)
							{
								memset(&chaQuest.sHaQuestElementary[i], 0, sizeof(sQUEST_ELEMENTARY));
								cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
							}
						}
						SaveGameData();
						SendChatMessageToServer("MrIm:Reset OK");
						memset(sinTestBuff5, 0, sizeof(sinTestBuff5));
						memset(sinTestBuff6, 0, sizeof(sinTestBuff6));
						memset(sinBuff, 0, sizeof(sinBuff));
					#endif
					}

				}

				if(lstrcmp(sinTestBuff5, "/이방범4차퀘스트") == 0 || lstrcmp(sinTestBuff5, "/Lee4thRankUp") == 0)
				{
					if(sinTestBuff6[0])
					{
					#ifdef	_WINMODE_DEBUG
						ResetQuset3Flag = atoi(sinTestBuff6);

						sinCompleteChangeJob4(ResetQuset3Flag);
						memset(sinTestBuff5, 0, sizeof(sinTestBuff5));
						memset(sinTestBuff6, 0, sizeof(sinTestBuff6));
						memset(sinBuff, 0, sizeof(sinBuff));
					#endif
					}
				}

				if(lstrcmp(sinTestBuff5, "/이방범3차퀘스트") == 0 || lstrcmp(sinTestBuff5, "/Lee3thRankUp") == 0)
				{
					if(sinTestBuff6[0])
					{
					#ifdef	_WINMODE_DEBUG
						ResetQuset3Flag = atoi(sinTestBuff6);
						if(ResetQuset3Flag == 1)
						{
							memset(&sinQuest_ChangeJob3, 0, sizeof(sQUEST_CHANGEJOB3));
							SaveGameData();
							SendChatMessageToServer("MrLee:Retry change Job Quest~ ");
						}
						if(ResetQuset3Flag == 2)
						{
							CheckChangeJob3QuestItem(0);
						}
						memset(sinTestBuff5, 0, sizeof(sinTestBuff5));
						memset(sinTestBuff6, 0, sizeof(sinTestBuff6));
						memset(sinBuff, 0, sizeof(sinBuff));
					#endif
					}
				}
				if(lstrcmp(sinTestBuff5, "/이방범레벨퀘스트") == 0 || lstrcmp(sinTestBuff5, "/LeeResetQuest") == 0)
				{
					if(sinTestBuff6[0])
					{
					#ifdef	_WINMODE_DEBUG
						ResetQuset3Flag = atoi(sinTestBuff6);
						switch(ResetQuset3Flag)
						{
							case 30:
							memset(&sinQuest_Level30, 0, sizeof(sQUEST_CHANGEJOB3));
							SaveGameData();
							SendChatMessageToServer("MrLee: Clear 30th Quest ~");
							break;
							case 55:
							memset(&sinQuest_Level55, 0, sizeof(sQUEST_CHANGEJOB3));
							memset(&sinQuest_Level55_2, 0, sizeof(sQUEST_CHANGEJOB3));
							SaveGameData();
							SendChatMessageToServer("MrLee: Clear 55th Quest ~");
							break;
							case 70:
							memset(&sinQuest_Level70, 0, sizeof(sQUEST_CHANGEJOB3));
							SaveGameData();
							SendChatMessageToServer("MrLee: Clear 70th Quest ~");

							break;
							case 80:
							memset(&sinQuest_Level80, 0, sizeof(sQUEST_CHANGEJOB3));
							SaveGameData();
							SendChatMessageToServer("MrLee: Clear 80th Quest ~");

							break;
							case 85:
							memset(&sinQuest_Level85, 0, sizeof(sQUEST_CHANGEJOB3));
							SaveGameData();
							SendChatMessageToServer("MrLee: Clear 85th Quest ~");

							break;
							case 90:
							memset(&sinQuest_Level90, 0, sizeof(sQUEST_CHANGEJOB3));
							SaveGameData();
							SendChatMessageToServer("MrLee: Clear 90th Quest ~");

							break;

							case 802:
							memset(&sinQuest_Level80_2, 0, sizeof(sQUEST_CHANGEJOB3));
							SaveGameData();
							SendChatMessageToServer("MrLee: Clear 80_2nd Quest ~");

							break;

							case 902:
							memset(&sinQuest_Level90_2, 0, sizeof(sQUEST_CHANGEJOB3));
							SaveGameData();
							SendChatMessageToServer("MrLee: Clear 90_2nd Quest ~(re-connect) ");

							break;
						}
						if(ResetQuset3Flag == 1)
						{
							memset(&sinQuest_ChangeJob3, 0, sizeof(sQUEST_CHANGEJOB3));
							SaveGameData();
							SendChatMessageToServer("MrLee: Try again Quest~");
						}
						if(ResetQuset3Flag == 2)
						{
							CheckChangeJob3QuestItem(0);
						}
						memset(sinTestBuff5, 0, sizeof(sinTestBuff5));
						memset(sinTestBuff6, 0, sizeof(sinTestBuff6));
						memset(sinBuff, 0, sizeof(sinBuff));

					#endif

					}


				}


				if(lstrcmp(sinTestBuff5, "/이방범순찰갔네") == 0 || lstrcmp(sinTestBuff5, "/Level") == 0)
				{
					if(sinTestBuff6[0])
					{
					#ifdef	_WINMODE_DEBUG
						CheckCharForm();
						sinChar->Level = atoi(sinTestBuff6);


						SetExp64(sinChar, ExpLevelTable[sinChar->Level - 1]);
						CodeXorCharInfo_Exp();

						ReformCharForm();
						SendChatMessageToServer("MrLee: OK! finished Level UP /(-_-)/ ");
						memset(sinTestBuff5, 0, sizeof(sinTestBuff5));
						memset(sinTestBuff6, 0, sizeof(sinTestBuff6));
						memset(sinBuff, 0, sizeof(sinBuff));

					#endif

					}
				}

				if (lstrcmp(sinTestBuff5, "/ConcluirQuests") == 0)
				{
					SendChatMessageToServer("Priston: Todas as quest terminadas");
					if (sinQuest_Level30.State < 3 && sinChar->Level >= 30) {
						CheckCharForm();
						sinChar->StatePoint += 5;
						cMessageBox.ShowMessage(MESSAGE_PLUS_STATE_POINT5);
						sinPlaySound(SIN_SOUND_EAT_POTION2);
						sinQuest_levelLog |= QUESTBIT_LEVEL_30;
						sinQuest_Level30.State = 3;
						sinQuest_Level30.BackUpCode = sinQuest_Level30.CODE;
						sinQuest_Level30.CODE = 0;
						EndQuest_Code(sinQuest_Level30.BackUpCode);
						sinQuest_Level30.CODE = 0;
						ReformCharForm();
					}

					if (sinQuest_Level55.State < 2 && sinChar->Level >= 55 && sinChar->JOB_CODE < 5) {
						CheckCharForm();
						sinSkill.SkillPoint += 1;
						cMessageBox.ShowMessage(MESSAGE_PLUS_SKILL_POINT);
						sinPlaySound(SIN_SOUND_EAT_POTION2);
						sinQuest_levelLog |= QUESTBIT_LEVEL_55;
						sinQuest_Level55.State = 3;
						sinQuest_Level55.BackUpCode = sinQuest_Level55.CODE;
						sinQuest_Level55.CODE = 0;
						EndQuest_Code(sinQuest_Level55.BackUpCode);
						sinQuest_Level55.CODE = 0;

						ReformCharForm();

					}
					if (sinQuest_Level55_2.State < 2 && sinChar->Level >= 55 && sinChar->JOB_CODE > 4) {
						CheckCharForm();
						sinSkill.SkillPoint += 1;
						cMessageBox.ShowMessage(MESSAGE_PLUS_SKILL_POINT);
						sinPlaySound(SIN_SOUND_EAT_POTION2);
						sinQuest_levelLog |= QUESTBIT_LEVEL_55;
						sinQuest_Level55_2.State = 3;
						sinQuest_Level55_2.BackUpCode = sinQuest_Level55_2.CODE;
						sinQuest_Level55_2.CODE = 0;
						EndQuest_Code(sinQuest_Level55_2.BackUpCode);
						sinQuest_Level55_2.CODE = 0;
						ReformCharForm();
					}

					if (sinQuest_Level70.State < 2 && sinChar->Level >= 70) {
						CheckCharForm();
						sinChar->StatePoint += 5;
						sinSkill.SkillPoint += 1;
						cMessageBox.ShowMessage(MESSAGE_PLUS_POINT_70);
						sinPlaySound(SIN_SOUND_EAT_POTION2);
						sinQuest_levelLog |= QUESTBIT_LEVEL_70;
						sinQuest_Level70.State = 3;
						sinQuest_Level70.BackUpCode = sinQuest_Level70.CODE;
						sinQuest_Level70.CODE = 0;
						EndQuest_Code(sinQuest_Level70.BackUpCode);
						sinQuest_Level70.CODE = 0;
						ReformCharForm();
					}

					if (sinQuest_Level80.State < 2 && sinChar->Level >= 80) {
						CheckCharForm();
						sinChar->StatePoint += 5;
						sinSkill.SkillPoint += 2;
						cMessageBox.ShowMessage(MESSAGE_PLUS_POINT_80);
						sinPlaySound(SIN_SOUND_EAT_POTION2);
						sinQuest_levelLog |= QUESTBIT_LEVEL_80;
						sinQuest_Level80.State = 3;
						sinQuest_Level80.BackUpCode = sinQuest_Level80.CODE;
						sinQuest_Level80.CODE = 0;
						EndQuest_Code(sinQuest_Level80.BackUpCode);
						sinQuest_Level80.CODE = 0;
						ReformCharForm();
					}

					if (sinQuest_Level85.State < 4 && sinChar->Level >= 85) {
						CheckCharForm();
						sinQuest_levelLog |= QUESTBIT_LEVEL_85;
						sinQuest_Level85.State = 4;
						sinQuest_Level85.BackUpCode = sinQuest_Level85.CODE;
						sinQuest_Level85.CODE = 0;
						EndQuest_Code(sinQuest_Level85.BackUpCode);
						sinQuest_Level85.CODE = 0;
						ReformCharForm();
					}

					if (sinQuest_Level90.State < 3 && sinChar->Level >= 90) {
						CheckCharForm();
						sinQuest_levelLog |= QUESTBIT_LEVEL_90;
						sinQuest_Level90.State = 3;
						sinQuest_Level90.BackUpCode = sinQuest_Level90.CODE;
						sinQuest_Level90.CODE = 0;
						EndQuest_Code(sinQuest_Level90.BackUpCode);
						sinQuest_Level90.CODE = 0;
						ReformCharForm();
						cInvenTory.SetItemToChar();
						if (!cInvenTory.SearchItemCode(sinQT1 | sin07)) {
							SendQuestCommandToServer(SIN_QUEST_CODE_LEVEL90, 0, 0, 0);
						}
					}
					if (sinQuest_Level80_2.State == 3) {
						DeleteQuestItem(sinQT1 | sin09);
						DeleteQuestItem(sinQT1 | sin10);
						DeleteQuestItem(sinQT1 | sin11);
					}
					if (sinQuest_Level80_2.State < 5 && sinChar->Level >= 80) {
						CheckCharForm();
						sinQuest_levelLog |= QUESTBIT_LEVEL_80_2;
						sinQuest_Level80_2.BackUpCode = sinQuest_Level80_2.CODE;
						sinQuest_Level80_2.CODE = 0;
						EndQuest_Code(sinQuest_Level80_2.BackUpCode);
						sinQuest_Level80_2.CODE = 0;
						sinQuest_Level80_2.State = 5;

						if (cInvenTory.SearchItemCode(sinQT1 | sin12)) {
							DeleteQuestItem(sinQT1 | sin12);
						}

						ReformCharStatePoint(sinChar, sinQuest_levelLog);
						ReformCharForm();
						cInvenTory.SetItemToChar();
						sinPlaySound(SIN_SOUND_EAT_POTION2);
						cMessageBox.ShowMessage(MESSAGE_PLUS_POINT_80_2);
						SetQuestBoard();
					}

					if (sinQuest_Level90_2.State < 4 && sinChar->Level >= 90) {
						CheckCharForm();
						sinQuest_levelLog |= QUESTBIT_LEVEL_90_2;
						sinQuest_Level90_2.BackUpCode = sinQuest_Level90_2.CODE;
						sinQuest_Level90_2.CODE = 0;
						EndQuest_Code(sinQuest_Level90_2.BackUpCode);
						sinQuest_Level90_2.CODE = 0;
						sinQuest_Level90_2.State = 4;
						if (cInvenTory.SearchItemCode(sinQT1 | sin13)) {
							DeleteQuestItem(sinQT1 | sin13);
						}
						ReformCharStatePoint(sinChar, sinQuest_levelLog);
						ReformCharForm();
						cInvenTory.SetItemToChar();
						sinPlaySound(SIN_SOUND_EAT_POTION2);
						cMessageBox.ShowMessage(MESSAGE_PLUS_POINT_90_2);
						SetQuestBoard();
					}
					memset(sinTestBuff5, 0, sizeof(sinTestBuff5));
					memset(sinBuff, 0, sizeof(sinBuff));

				}

				if(lstrcmp(sinTestBuff5, "/이방범도와줘요스킬") == 0 || lstrcmp(sinTestBuff5, "/LeeHelpMeSkill") == 0)
				{
				#ifdef	_WINMODE_DEBUG
					cSkill.InitSkillPoint(1);
					SendChatMessageToServer("MrLee: Skill reset/(-_-)/ ");
					memset(sinTestBuff5, 0, sizeof(sinTestBuff5));
					memset(sinTestBuff6, 0, sizeof(sinTestBuff6));
					memset(sinBuff, 0, sizeof(sinBuff));
				#endif
				}
				if(lstrcmp(sinTestBuff5, "/이방범도와줘요스탯") == 0 || lstrcmp(sinTestBuff5, "/LeeHelpMeStat") == 0)
				{
				#ifdef	_WINMODE_DEBUG
					sinChar->wVersion[1] = 0;
					cCharStatus.InitCharStatus();
					cInvenTory.SetItemToChar();
					if(sinChar->Life[1] < sinGetLife())
					{
						sinSetLife(sinChar->Life[1]);
						ReformCharForm();
						ResetEnergyGraph(4);
					}
					SendChatMessageToServer("MrLee: Stat Reset/(-_-)/ ");
					memset(sinTestBuff5, 0, sizeof(sinTestBuff5));
					memset(sinTestBuff6, 0, sizeof(sinTestBuff6));
					memset(sinBuff, 0, sizeof(sinBuff));
				#endif
				}
				if(lstrcmp(sinTestBuff5, "/이방범증정아이템") == 0)
				{
				#ifdef	_WINMODE_DEBUG
					if(MouseItem.Flag)
					{
						MouseItem.sItemInfo.SpecialItemFlag[0] = CHECK_GIVE_ITEM;
					}
					SendChatMessageToServer("이방범: 잘쓰게(-_-)/ ");
					memset(sinTestBuff5, 0, sizeof(sinTestBuff5));
					memset(sinTestBuff6, 0, sizeof(sinTestBuff6));
					memset(sinBuff, 0, sizeof(sinBuff));






				#endif
				}
				if(lstrcmp(sinTestBuff5, "/이방범전업") == 0 || lstrcmp(sinTestBuff5, "/PassRankUp") == 0)
				{
				#ifdef	_WINMODE_DEBUG
					SendChatMessageToServer("MeLee: it's good /(-_-)/ ");
					sinChar->ChangeJob++;
					if(sinChar->ChangeJob > 3)sinChar->ChangeJob = 3;
					cSkill.SearchUseSkill();
					memset(sinTestBuff5, 0, sizeof(sinTestBuff5));
					memset(sinTestBuff6, 0, sizeof(sinTestBuff6));
					memset(sinBuff, 0, sizeof(sinBuff));
				#endif
				}

				if(lstrcmp(sinTestBuff5, "/이방범전업퀘스트") == 0 || lstrcmp(sinTestBuff5, "/LeeResetRankUp") == 0)
				{
					if(sinTestBuff6[0])
					{
					#ifdef	_WINMODE_DEBUG
						ResetQuset3Flag = atoi(sinTestBuff6);
						if(ResetQuset3Flag == 1)
						{
							memset(&sinQuest_ChangeJob, 0, sizeof(sQUEST_CHANGEJOB));
							SaveGameData();
							SendChatMessageToServer("MrLee: Clear Job Quest of Temscron 2th");
						}
						if(ResetQuset3Flag == 2)
						{

							memset(&sinQuest_ChangeJob2, 0, sizeof(sQUEST_CHANGEJOB));
							SaveGameData();
							SendChatMessageToServer("MrLee: Clear Job Quest of Moryon 2th");
						}
						if(ResetQuset3Flag == 3)
						{

							memset(&sinQuest_ChangeJob3, 0, sizeof(sQUEST_CHANGEJOB3));
							SaveGameData();
							SendChatMessageToServer("MrLee: Clear Job Quest of 3th ");
						}
						if(ResetQuset3Flag == 4)
						{
							if(sinChar->ChangeJob == 3)
							{
								sinChar->ChangeJob = 2;
							}
							memset(&sinQuest_ChangeJob4, 0, sizeof(sQUEST_CHANGEJOB3));
							SaveGameData();
							SendChatMessageToServer("MrLee:Reconnect again!! ");
						}

						memset(sinTestBuff5, 0, sizeof(sinTestBuff5));
						memset(sinTestBuff6, 0, sizeof(sinTestBuff6));
						memset(sinBuff, 0, sizeof(sinBuff));
					#endif
					}

				}

				if(lstrcmp(sinTestBuff5, "/이방범포스") == 0 || lstrcmp(sinTestBuff5, "/LeeForce") == 0)
				{
				#ifdef	_WINMODE_DEBUG
					SendChatMessageToServer("MrLee: I like force /(-_-)/ ");
					for(t = 0; t < 10; t++)
					{
						if(ContinueSkill[t].Flag)
						{
							if(ContinueSkill[t].CODE == SKILL_FORCE_ORB)
							{
								ContinueSkill[t].CheckTime = ContinueSkill[t].UseTime * 70;
								cInvenTory.SetItemToChar();
								break;

							}
						}
					}
					memset(sinTestBuff5, 0, sizeof(sinTestBuff5));
					memset(sinTestBuff6, 0, sizeof(sinTestBuff6));
					memset(sinBuff, 0, sizeof(sinBuff));
				#endif
				}
				if(lstrcmp(sinTestBuff5, "/이방범숏키초기화") == 0 || lstrcmp(sinTestBuff5, "/LeeShotKeyReset") == 0)
				{
				#ifdef	_WINMODE_DEBUG
					cSkill.SkillShortKeyInit();
					SendChatMessageToServer("MtLee: ShortKey Skill reset ");
					memset(sinTestBuff5, 0, sizeof(sinTestBuff5));
					memset(sinTestBuff6, 0, sizeof(sinTestBuff6));
					memset(sinBuff, 0, sizeof(sinBuff));
				#endif
				}
			}
		}
	}
	if(!hFocusWnd)
		sinChatEnter = 0;
	else sinChatEnter = 1;
	if(ChatFlag)sinChatEnter = 1;


}

int DefaultLength[4] = { 94,94,76,86 };
float sinOldNowState[4] = { 0,0,0,0 };
float sinOldMaxState[4] = { 0,0,0,0 };


void cINTERFACE::InitState()
{

	float sinTemp;
	float sinMaxState[4] = { (float)sinChar->Life[1],(float)sinChar->Mana[1] ,(float)sinChar->Stamina[1] };
	float sinNowState[4] = { (float)sinGetLife(),(float)sinGetMana() ,(float)sinGetStamina() };

	for(int i = 0; i < 3; i++)
	{
		if(sinMaxState[i])
			sinTemp = (sinNowState[i] / sinMaxState[i]) * 100;
		else
			sinTemp = 0;
		sinBmpLength[i] = (int)((DefaultLength[i] * (sinTemp / 100)));
		sinOldNowState[i] = sinNowState[i];

	}

	if(sinChar->Level < 79)
	{
		sinMaxState[3] = (float)(ExpLevelTable[sinChar->Level] - ExpLevelTable[sinChar->Level - 1]);
		sinNowState[3] = (float)((GetXorExp64(sinChar)) - ExpLevelTable[sinChar->Level - 1]);
	}
	else
	{
		sinMaxState[3] = (float)((ExpLevelTable[sinChar->Level] - ExpLevelTable[sinChar->Level - 1]) / 1000000);
		sinNowState[3] = (float)(((GetXorExp64(sinChar)) - ExpLevelTable[sinChar->Level - 1]) / 1000000);
	}

	InitStateFlag = 1;

}


void cINTERFACE::CheckingState()
{

	float	sinTemp;

	float sinMaxState[4] = { (float)(sinChar->Life[1]),(float)sinChar->Mana[1] ,(float)sinChar->Stamina[1] };
	float sinNowState[4] = { (float)sinGetLife(),(float)sinGetMana() ,(float)sinGetStamina() };




	if(sinChar->Level < 79)
	{
		sinMaxState[3] = (float)(ExpLevelTable[sinChar->Level] - ExpLevelTable[sinChar->Level - 1]);
		sinNowState[3] = (float)((GetXorExp64(sinChar)) - ExpLevelTable[sinChar->Level - 1]);
	}
	else
	{
		sinMaxState[3] = (float)((ExpLevelTable[sinChar->Level] - ExpLevelTable[sinChar->Level - 1]) / 1000000);
		sinNowState[3] = (float)(((GetXorExp64(sinChar)) - ExpLevelTable[sinChar->Level - 1]) / 1000000);
	}

	for(int i = 0; i < 4; i++)
	{
		if(sinOldNowState[i] != sinNowState[i] || sinOldNowState[i] != sinMaxState[i])
		{
			if(sinOldNowState[i] != sinNowState[i])
			{
				sinTemp = ((sinNowState[i]) / sinMaxState[i]) * 100;
				sinBmpLength[i] = (int)((DefaultLength[i] * (sinTemp / 100)));
				if(sinBmpLength[i] > DefaultLength[i])sinBmpLength[i] = DefaultLength[i];
				sinOldNowState[i] = sinNowState[i];

			}

		}
	}

}




void cINTERFACE::ShowParaState()
{

	InfoMessageBoxPos.x = 0;
	InfoMessageBoxPos.y = 0;

	szInfoMsgBuff5[0] = 0;
	strcpy_s(szInfoMsgBuff5, "");


	if(pCursorPos.x > 315 && pCursorPos.x < 337 && pCursorPos.y > 500 && pCursorPos.y < 594)
	{
		if(AddVirtualLife[1])
		{
			AddVirtualLife[0] = (int)((float)sinGetLife() * ((float)sinVirtualLifePercent / 100.f));
		}
		cHelpPet.PetMessage("*Bar_Life", 0);
		wsprintf(szInfoMsgBuff5, sinStateName[0], (int)sinGetLife() + AddVirtualLife[0], (int)sinChar->Life[1] + AddVirtualLife[1]);
		InfoMessageBoxPos.x = 343;
		InfoMessageBoxPos.y = 500;

	}


	if(pCursorPos.x > 463 && pCursorPos.x < 483 && pCursorPos.y > 498 && pCursorPos.y < 595)
	{

		if(AddVirtualMana[1])
		{
			AddVirtualMana[0] = (int)((float)sinGetMana() * ((float)sinVirtualManaPercent / 100.f));
		}
		wsprintf(szInfoMsgBuff5, sinStateName[1], (int)sinGetMana(), (int)sinChar->Mana[1]);
		cHelpPet.PetMessage("*Bar_Mana", 0);
		InfoMessageBoxPos.x = 490;
		InfoMessageBoxPos.y = 498;

	}
	if(pCursorPos.x > 300 && pCursorPos.x < 313 && pCursorPos.y > 513 && pCursorPos.y < 595)
	{

		if(AddVirtualStamina[1])
		{
			AddVirtualStamina[0] = (int)((float)sinGetStamina() * ((float)sinVirtualStaminaPercent / 100.f));
		}
		cHelpPet.PetMessage("*Bar_Stamina", 0);
		wsprintf(szInfoMsgBuff5, sinStateName[2], (int)sinGetStamina(), (int)sinChar->Stamina[1]);
		InfoMessageBoxPos.x = 320;
		InfoMessageBoxPos.y = 513;

	}

	if(pCursorPos.x > 483 && pCursorPos.x < 483 + 10 && pCursorPos.y > 513 && pCursorPos.y < 595)
	{
		cHelpPet.PetMessage("*Bar_Exp", 0);

	}
	if(pCursorPos.x > 500 && pCursorPos.x < 570 && pCursorPos.y > 540 && pCursorPos.y < 594)
	{
		cHelpPet.PetMessage("*Exp_Num", 0);
	}









}


void cINTERFACE::DrawInterText()
{
	HDC	hdc = NULL;

	//renderDevice.lpDDSBack->GetDC(&hdc);
	SelectObject(hdc, sinFont);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));

	if(InfoMessageBoxPos.x != 0 || InfoMessageBoxPos.y != 0)
		dsTextLineOut(hdc, InfoMessageBoxPos.x, InfoMessageBoxPos.y, szInfoMsgBuff5, lstrlen(szInfoMsgBuff5));
	if(ShowExpPercentFlag)
	{
		SetTextColor(hdc, RGB(202, 254, 251));
		dsDrawOffsetArray = dsARRAY_BOTTOM;
		dsTextLineOut(hdc, 511, 552, szInfoMsgBuff6, lstrlen(szInfoMsgBuff6));
		dsDrawOffsetArray = dsARRAY_TOP;

	}



	SetTextColor(hdc, RGB(255, 255, 255));
	if(SkillNpcFlag)
	{
		if(szSkillMasterMsg[0])
		{
			dsTextLineOut(hdc, SkillMasterTextXY.x, SkillMasterTextXY.y + 2, szSkillMasterMsg, lstrlen(szSkillMasterMsg));
		}
		if(szReStartMsg2[0])
		{
			dsTextLineOut(hdc, SkillMasterTextXY.x, SkillMasterTextXY.y + 18, szSkillMasterMsg2, lstrlen(szSkillMasterMsg2));
		}

	}

	//renderDevice.lpDDSBack->ReleaseDC(hdc);

}


void cINTERFACE::CheckAllBox(int ButtonFlag)
{

	int i = 0;
	for(i = 0; i < SIN_MAX_HELP_NUMBER; i++)
	{
		if(sSinHelp[i].KindFlag)
		{
			if((ButtonFlag == SIN_CRAFTITEM || ButtonFlag == SIN_AGING || ButtonFlag == SIN_SMELTING || ButtonFlag == SIN_MANUFACTURE))return;
		}

		if(sSinHelp[i].KindFlag == SIN_HELP_KIND_TELEPORT_SCROLL)
		{
			if(cTrade.OpenFlag)
			{

				SendRequestTrade(cTrade.TradeCharCode, 3);
				cTrade.CancelTradeItem();
			}
			if((ButtonFlag == SIN_MYSHOP || ButtonFlag == SIN_TRADE))return;
		}
	}


	if(cWareHouse.OpenFlag)
	{
		if(ButtonFlag == SIN_TRADE || ButtonFlag == SIN_SHOP ||
		   ButtonFlag == SIN_CRAFTITEM || ButtonFlag == SIN_AGING || ButtonFlag == SIN_MYSHOP
		   || ButtonFlag == SIN_CHARSHOP || ButtonFlag == SIN_SMELTING || ButtonFlag == SIN_MANUFACTURE)return;

	}

	if(MyShopSendButton || cMyShop.OpenFlag || cCharShop.OpenFlag)
	{
		if(ButtonFlag == SIN_TRADE || ButtonFlag == SIN_SHOP || ButtonFlag == SIN_WAREHOUSE ||
		   ButtonFlag == SIN_CRAFTITEM || ButtonFlag == SIN_AGING ||
		   ButtonFlag == SIN_CHARSHOP || ButtonFlag == SIN_SMELTING || ButtonFlag == SIN_MANUFACTURE)return;

	}

	if(cShop.OpenFlag || cCraftItem.OpenFlag || cAging.OpenFlag || cTrade.OpenFlag ||
	   cCharShop.OpenFlag || SmeltingItem.OpenFlag || ManufactureItem.m_OpenFlag || cMixtureReset.OpenFlag)
	{
		if(ButtonFlag == SIN_MYSHOP || ButtonFlag == SIN_CHARSHOP)return;

	}

	if(cShop.OpenFlag || cCraftItem.OpenFlag || cAging.OpenFlag || cTrade.OpenFlag ||
	   cMyShop.OpenFlag || cCharShop.OpenFlag || SmeltingItem.OpenFlag || ManufactureItem.m_OpenFlag)
	{
		if(ButtonFlag == SIN_CHARSHOP)return;

	}

	switch(ButtonFlag)
	{
		case SIN_CHARSTATUS:
		if(cInvenTory.OpenFlag) cInvenTory.OpenFlag = SIN_CLOSE;
		if(cSkill.OpenFlag) cSkill.OpenFlag = SIN_CLOSE;
		ExitButtonClick = 0;

		break;
		case SIN_SKILL:
		if(cCharStatus.OpenFlag)cCharStatus.OpenFlag = SIN_CLOSE;
		if(cInvenTory.OpenFlag) cInvenTory.OpenFlag = SIN_CLOSE;
		ExitButtonClick = 0;

		break;
		case SIN_INVENTORY:
		if(cCharStatus.OpenFlag)cCharStatus.OpenFlag = SIN_CLOSE;
		if(cSkill.OpenFlag) cSkill.OpenFlag = SIN_CLOSE;
		ExitButtonClick = 0;

		break;

		case SIN_TRADE:
		if(cMixtureReset.OpenFlag)	cMixtureReset.OpenFlag = SIN_CLOSE;
		if(cAging.OpenFlag)cAging.OpenFlag = SIN_CLOSE;
		if(cCraftItem.OpenFlag)cCraftItem.OpenFlag = SIN_CLOSE;
		if(cShop.OpenFlag)cShop.OpenFlag = SIN_CLOSE;
		if(cWareHouse.OpenFlag)cWareHouse.OpenFlag = SIN_CLOSE;
		if(cCharStatus.OpenFlag)cCharStatus.OpenFlag = SIN_CLOSE;
		if(!cInvenTory.OpenFlag) cInvenTory.OpenFlag = SIN_OPEN;
		if(cSkill.OpenFlag) cSkill.OpenFlag = SIN_CLOSE;

		if(SmeltingItem.OpenFlag)
		{
			SmeltingItem.OpenFlag = SIN_CLOSE;
		}

		if(ManufactureItem.m_OpenFlag)
		{
			ManufactureItem.m_OpenFlag = SIN_CLOSE;
		}
		cTrade.ReFormTradeItem();
		cInvenTory.ChangeSpecialItem(2);

		break;

		case SIN_SHOP:
		if(cMixtureReset.OpenFlag)	cMixtureReset.OpenFlag = SIN_CLOSE;
		if(cAging.OpenFlag)cAging.OpenFlag = SIN_CLOSE;
		if(cCraftItem.OpenFlag)cCraftItem.OpenFlag = SIN_CLOSE;
		if(cTrade.OpenFlag)cTrade.OpenFlag = SIN_CLOSE;
		if(cWareHouse.OpenFlag)cWareHouse.OpenFlag = SIN_CLOSE;
		if(cSkill.OpenFlag) cSkill.OpenFlag = SIN_CLOSE;
		if(cCharStatus.OpenFlag)cCharStatus.OpenFlag = SIN_CLOSE;

		if(SmeltingItem.OpenFlag)
		{
			SmeltingItem.OpenFlag = SIN_CLOSE;
		}

		if(ManufactureItem.m_OpenFlag)
		{
			ManufactureItem.m_OpenFlag = SIN_CLOSE;
		}
		if(!cInvenTory.OpenFlag) cInvenTory.OpenFlag = SIN_OPEN;
		if(!cShop.OpenFlag) cShop.OpenFlag = SIN_OPEN;
		cInvenTory.ChangeSpecialItem(2);

		break;

		case SIN_SYSTEM:
		if(cInvenTory.OpenFlag) cInvenTory.OpenFlag = SIN_CLOSE;
		if(cSkill.OpenFlag) cSkill.OpenFlag = SIN_CLOSE;
		if(cCharStatus.OpenFlag)cCharStatus.OpenFlag = SIN_CLOSE;

		break;
		case SIN_ALL_CLOSE:
		if(cTrade.OpenFlag)break;
		if(cInvenTory.OpenFlag) cInvenTory.OpenFlag = SIN_CLOSE;
		if(cSkill.OpenFlag) cSkill.OpenFlag = SIN_CLOSE;
		if(cCharStatus.OpenFlag)cCharStatus.OpenFlag = SIN_CLOSE;
		if(cShop.OpenFlag)cShop.OpenFlag = SIN_CLOSE;
		if(cTrade.OpenFlag)cTrade.OpenFlag = SIN_CLOSE;











		ExitButtonClick = 0;
		break;

		case SIN_WAREHOUSE:

		if(g_IsDxProjectZoomIn)break;

		if(cMixtureReset.OpenFlag)	cMixtureReset.OpenFlag = SIN_CLOSE;
		if(cTrade.OpenFlag)cTrade.OpenFlag = SIN_CLOSE;
		if(cShop.OpenFlag)cShop.OpenFlag = SIN_CLOSE;
		if(cSkill.OpenFlag) cSkill.OpenFlag = SIN_CLOSE;
		if(cAging.OpenFlag)cAging.OpenFlag = SIN_CLOSE;
		if(cCraftItem.OpenFlag)cCraftItem.OpenFlag = SIN_CLOSE;
		if(cCharStatus.OpenFlag)cCharStatus.OpenFlag = SIN_CLOSE;
		if(!cInvenTory.OpenFlag) cInvenTory.OpenFlag = SIN_OPEN;
		if(!cWareHouse.OpenFlag) cWareHouse.OpenFlag = SIN_OPEN;

		if(SmeltingItem.OpenFlag)
		{
			SmeltingItem.OpenFlag = SIN_CLOSE;
		}

		if(ManufactureItem.m_OpenFlag)
		{
			ManufactureItem.m_OpenFlag = SIN_CLOSE;
		}
		cWareHouse.ReFormWareHouse();
		cWareHouse.CheckCopyItem();
		cWareHouse.DeleteCopyItem();
		cInvenTory.ChangeSpecialItem(2);


		break;

		case SIN_CRAFTITEM:
		if(cMixtureReset.OpenFlag)	cMixtureReset.OpenFlag = SIN_CLOSE;
		if(cTrade.OpenFlag)cTrade.OpenFlag = SIN_CLOSE;
		if(cShop.OpenFlag)cShop.OpenFlag = SIN_CLOSE;
		if(cSkill.OpenFlag) cSkill.OpenFlag = SIN_CLOSE;
		if(cAging.OpenFlag)cAging.OpenFlag = SIN_CLOSE;
		if(cWareHouse.OpenFlag) cWareHouse.OpenFlag = SIN_CLOSE;
		if(cCharStatus.OpenFlag)cCharStatus.OpenFlag = SIN_CLOSE;
		if(!cInvenTory.OpenFlag) cInvenTory.OpenFlag = SIN_OPEN;
		if(!cCraftItem.OpenFlag) cCraftItem.OpenFlag = SIN_OPEN;

		if(SmeltingItem.OpenFlag)
		{
			SmeltingItem.OpenFlag = SIN_CLOSE;
		}

		if(ManufactureItem.m_OpenFlag)
		{
			ManufactureItem.m_OpenFlag = SIN_CLOSE;
		}
		cCraftItem.ReFormCraftItem();
		cInvenTory.ChangeSpecialItem(2);


		break;
		case SIN_AGING:
		if(cMixtureReset.OpenFlag)	cMixtureReset.OpenFlag = SIN_CLOSE;
		if(cTrade.OpenFlag)cTrade.OpenFlag = SIN_CLOSE;
		if(cShop.OpenFlag)cShop.OpenFlag = SIN_CLOSE;
		if(cSkill.OpenFlag) cSkill.OpenFlag = SIN_CLOSE;
		if(cCraftItem.OpenFlag)cCraftItem.OpenFlag = SIN_CLOSE;
		if(cWareHouse.OpenFlag) cWareHouse.OpenFlag = SIN_CLOSE;
		if(cCharStatus.OpenFlag)cCharStatus.OpenFlag = SIN_CLOSE;
		if(!cInvenTory.OpenFlag) cInvenTory.OpenFlag = SIN_OPEN;
		if(!cAging.OpenFlag)cAging.OpenFlag = SIN_OPEN;

		if(SmeltingItem.OpenFlag)
		{
			SmeltingItem.OpenFlag = SIN_CLOSE;
		}

		if(ManufactureItem.m_OpenFlag)
		{
			ManufactureItem.m_OpenFlag = SIN_CLOSE;
		}
		cInvenTory.ChangeSpecialItem(2);


		break;
		case SIN_MIXTURE_RESET:
		if(cTrade.OpenFlag)			cTrade.OpenFlag = SIN_CLOSE;
		if(cShop.OpenFlag)			cShop.OpenFlag = SIN_CLOSE;
		if(cSkill.OpenFlag)			cSkill.OpenFlag = SIN_CLOSE;
		if(cCraftItem.OpenFlag)		cCraftItem.OpenFlag = SIN_CLOSE;
		if(cWareHouse.OpenFlag)		cWareHouse.OpenFlag = SIN_CLOSE;
		if(cCharStatus.OpenFlag)	cCharStatus.OpenFlag = SIN_CLOSE;
		if(cAging.OpenFlag)			cAging.OpenFlag = SIN_CLOSE;
		if(SmeltingItem.OpenFlag)	SmeltingItem.OpenFlag = SIN_CLOSE;
		if(ManufactureItem.m_OpenFlag)	ManufactureItem.m_OpenFlag = SIN_CLOSE;

		if(!cInvenTory.OpenFlag)	cInvenTory.OpenFlag = SIN_OPEN;
		if(!cMixtureReset.OpenFlag)
		{
			cMixtureReset.OpenFlag = SIN_OPEN;
		}
		cInvenTory.ChangeSpecialItem(2);
		break;
		case SIN_SMELTING:
		if(cMixtureReset.OpenFlag)	cMixtureReset.OpenFlag = SIN_CLOSE;
		if(cTrade.OpenFlag)
		{
			cTrade.OpenFlag = SIN_CLOSE;
		}

		if(cShop.OpenFlag)
		{
			cShop.OpenFlag = SIN_CLOSE;
		}

		if(cSkill.OpenFlag)
		{
			cSkill.OpenFlag = SIN_CLOSE;
		}

		if(cCraftItem.OpenFlag)
		{
			cCraftItem.OpenFlag = SIN_CLOSE;
		}

		if(cWareHouse.OpenFlag)
		{
			cWareHouse.OpenFlag = SIN_CLOSE;
		}

		if(cCharStatus.OpenFlag)
		{
			cCharStatus.OpenFlag = SIN_CLOSE;
		}

		if(cAging.OpenFlag)
		{
			cAging.OpenFlag = SIN_CLOSE;
		}

		if(ManufactureItem.m_OpenFlag)
		{
			ManufactureItem.m_OpenFlag = SIN_CLOSE;
		}
		if(!cInvenTory.OpenFlag)
		{
			cInvenTory.OpenFlag = SIN_OPEN;
		}
		if(!SmeltingItem.OpenFlag)
		{
			SmeltingItem.OpenFlag = SIN_OPEN;
		}
		cInvenTory.ChangeSpecialItem(2);
		break;
		case SIN_MANUFACTURE:
		if(cMixtureReset.OpenFlag)	cMixtureReset.OpenFlag = SIN_CLOSE;
		if(cTrade.OpenFlag)
		{
			cTrade.OpenFlag = SIN_CLOSE;
		}

		if(cShop.OpenFlag)
		{
			cShop.OpenFlag = SIN_CLOSE;
		}

		if(cSkill.OpenFlag)
		{
			cSkill.OpenFlag = SIN_CLOSE;
		}

		if(cCraftItem.OpenFlag)
		{
			cCraftItem.OpenFlag = SIN_CLOSE;
		}

		if(cWareHouse.OpenFlag)
		{
			cWareHouse.OpenFlag = SIN_CLOSE;
		}

		if(cCharStatus.OpenFlag)
		{
			cCharStatus.OpenFlag = SIN_CLOSE;
		}

		if(cAging.OpenFlag)
		{
			cAging.OpenFlag = SIN_CLOSE;
		}
		if(SmeltingItem.OpenFlag)
		{
			SmeltingItem.OpenFlag = SIN_CLOSE;
		}
		if(!cInvenTory.OpenFlag)
		{
			cInvenTory.OpenFlag = SIN_OPEN;
		}
		if(!ManufactureItem.m_OpenFlag)
		{
			ManufactureItem.m_OpenFlag = SIN_OPEN;

			if(!g_Manufacture_ItemInfo[0].ItemCode)
			{
				smTRANS_COMMAND	TransCommand;
				TransCommand.code = OpCode::OPCODE_MANUFACTURE_WEIGHT_PRICE;
				TransCommand.size = sizeof(smTRANS_COMMAND);
				TransCommand.WParam = 0;
				TransCommand.LParam = 0;
				TransCommand.SParam = 0;
				smWINSOCK* lpsmSock;
				lpsmSock = GetAreaServerSock();
				if(lpsmSock)
				{
					lpsmSock->Send((char*)&TransCommand, TransCommand.size, TRUE);
				}
			}
		}
		cInvenTory.ChangeSpecialItem(2);
		break;
		case SIN_MYSHOP:
		if(lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_VILLAGE)
		{
			if(cMixtureReset.OpenFlag)cMixtureReset.OpenFlag = SIN_CLOSE;
			if(cTrade.OpenFlag)cTrade.OpenFlag = SIN_CLOSE;
			if(cShop.OpenFlag)cShop.OpenFlag = SIN_CLOSE;
			if(cSkill.OpenFlag) cSkill.OpenFlag = SIN_CLOSE;
			if(cAging.OpenFlag)cAging.OpenFlag = SIN_CLOSE;
			if(cCraftItem.OpenFlag)cCraftItem.OpenFlag = SIN_CLOSE;
			if(cCharStatus.OpenFlag)cCharStatus.OpenFlag = SIN_CLOSE;

			if(SmeltingItem.OpenFlag)
			{
				SmeltingItem.OpenFlag = SIN_CLOSE;
			}

			if(ManufactureItem.m_OpenFlag)
			{
				ManufactureItem.m_OpenFlag = SIN_CLOSE;
			}
			if(cCharShop.OpenFlag)
			{
				cCharShop.OpenFlag = 0;
				memset(cCharShop.CharShopItem, 0, sizeof(sITEM) * 30);
			}
			if(!cInvenTory.OpenFlag) cInvenTory.OpenFlag = SIN_OPEN;
			if(!cMyShop.OpenFlag) cMyShop.OpenFlag = SIN_OPEN;
			cInvenTory.ChangeSpecialItem(2);
		}

		break;
		case SIN_CHARSHOP:
		if(lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_VILLAGE)
		{
			if(cMixtureReset.OpenFlag)cMixtureReset.OpenFlag = SIN_CLOSE;
			if(cTrade.OpenFlag)cTrade.OpenFlag = SIN_CLOSE;
			if(cShop.OpenFlag)cShop.OpenFlag = SIN_CLOSE;
			if(cSkill.OpenFlag) cSkill.OpenFlag = SIN_CLOSE;
			if(cAging.OpenFlag)cAging.OpenFlag = SIN_CLOSE;
			if(cCraftItem.OpenFlag)cCraftItem.OpenFlag = SIN_CLOSE;
			if(cCharStatus.OpenFlag)cCharStatus.OpenFlag = SIN_CLOSE;

			if(SmeltingItem.OpenFlag)
			{
				SmeltingItem.OpenFlag = SIN_CLOSE;
			}

			if(ManufactureItem.m_OpenFlag)
			{
				ManufactureItem.m_OpenFlag = SIN_CLOSE;
			}
			if(cMyShop.OpenFlag)
			{
				cMyShop.OpenFlag = SIN_CLOSE;
				cMyShop.OpenFlag = 0;
				memset(cMyShop.MyShopItem, 0, sizeof(sITEM) * 30);
				memset(MyShopItemIndex, 0, sizeof(int) * 100);
				MyShopSendButton = 0;
			}
			if(!cInvenTory.OpenFlag) cInvenTory.OpenFlag = SIN_OPEN;
			if(!cCharShop.OpenFlag) cCharShop.OpenFlag = SIN_OPEN;
			cInvenTory.ChangeSpecialItem(2);
		}
		break;

	}



}

int cINTERFACE::DrawClockArrow(int x, int y, int Angle)
{




	float fx[4], fy[4];
	int sinY, cosY;
	int dx[4], dy[4];
	int cnt;

	int sinTimeAngle;
	float TempTime, TempTime2, TempTime3;

	TempTime2 = (float)dwGameHour * 60;
	TempTime3 = (float)(TempTime2 + dwGameMin) / 1440;

	TempTime = (float)TempTime3 * 100;


	sinTimeAngle = (int)(2190 + (780 * (TempTime / 100)));

	sinY = GetSin[sinTimeAngle&ANGCLIP];
	cosY = GetCos[sinTimeAngle&ANGCLIP];

	dx[0] = 8; dy[0] = 48;
	dx[1] = 8; dy[1] = 32;
	dx[2] = -8; dy[2] = 48;
	dx[3] = -8; dy[3] = 32;

	for(cnt = 0; cnt < 4; cnt++)
	{
		fx[cnt] = (float)((dy[cnt] * sinY + dx[cnt] * cosY) >> 8);
		fy[cnt] = (float)((dy[cnt] * cosY - dx[cnt] * sinY) >> 8);
		fx[cnt] /= 256;
		fy[cnt] /= 256;
		fx[cnt] += (float)x;
		fy[cnt] += (float)y;
	}


	psDrawTexImage2(smMaterial[cInterFace.MatClock].smTexture[0], fx, fy, 0, 0, 1, 1, 255, 0);



	return TRUE;
}


int cINTERFACE::DrawCompass(int x, int y, int Angle)
{

	float fx[4], fy[4];
	int sinY, cosY;
	int dx[4], dy[4];
	int cnt;

	sinY = GetSin[Angle&ANGCLIP];
	cosY = GetCos[(Angle + ANGLE_180)&ANGCLIP];

	dx[0] = 8; dy[0] = 13 + 16;
	dx[1] = 8; dy[1] = 13;
	dx[2] = -8; dy[2] = 13 + 16;
	dx[3] = -8; dy[3] = 13;

	for(cnt = 0; cnt < 4; cnt++)
	{
		fx[cnt] = (float)((dy[cnt] * sinY + dx[cnt] * cosY) >> 8);
		fy[cnt] = (float)((dy[cnt] * cosY - dx[cnt] * sinY) >> 8);
		fx[cnt] /= 256;
		fy[cnt] /= 256;
		fx[cnt] += (float)x;
		fy[cnt] += (float)y;
	}


	psDrawTexImage2(smMaterial[cInterFace.MatComPass].smTexture[0], fx, fy, 0, 0, 1, 1, 255, 0);


	return TRUE;
}





int cINTERFACE::CheckExpPercentControl()
{


	return TRUE;
}


int cINTERFACE::GetWordTimeDisplay()
{
	float TempfHour = (float)dwGameHour;

	if(TempfHour >= 23 || TempfHour < 4)
		DayOrNightFlag = 2;
	else
		DayOrNightFlag = 1;

	if(DayOrNightFlag == 1)
	{
		sinGageTime2 = (int)(50.0f*((TempfHour - 4.0f) / 19.0f));
	}
	else
	{
		sinGageTime2 = (int)(50.0f*((TempfHour + 1) / 5.0f));
	}
	if(sinGageTime2 > 50)sinGageTime2 = 50;

	return TRUE;
}


void cINTERFACE::ShowExpPercent()
{


	ShowExpPercentFlag = 1;

	int ExpPercent = 0;
	int ExpPercentSpot = 0;
	int ExpSize = 0;
	int ExpNowSize = 0;

	szInfoMsgBuff6[0] = 0;

	if (sinChar->Level > 75)
	{
		ExpSize = (int)((GetNextExp(sinChar->Level) - GetNextExp(sinChar->Level - 1)) / 1000000);
		ExpNowSize = (int)(cCharStatus.sinGetNowExp() - (GetNextExp(sinChar->Level - 1) / 1000000));
		ExpPercent = (int)(100000.0f / (float)ExpSize * (float)ExpNowSize);
		ExpPercentSpot = (int)(ExpPercent % 1000);
		ExpPercent = ExpPercent / 1000;

		if (ExpPercent >= 100)
		{
			ExpPercent = 99;
			ExpPercentSpot = 999;
		}

		if (ExpPercentSpot < 10)
		{
			wsprintf(szInfoMsgBuff6, "%d.00%d%s", ExpPercent, ExpPercentSpot, "%  ");
		}
		else if (ExpPercentSpot >= 10 && ExpPercentSpot < 100)
		{
			wsprintf(szInfoMsgBuff6, "%d.0%d%s", ExpPercent, ExpPercentSpot, "%  ");
		}
		else
			wsprintf(szInfoMsgBuff6, "%d.%d%s", ExpPercent, ExpPercentSpot, "%  ");

	}
	else
	{
		ExpSize = (int)GetNextExp(sinChar->Level) - (int)GetNextExp(sinChar->Level - 1);
		ExpNowSize = cCharStatus.sinGetNowExp() - (int)GetNextExp(sinChar->Level - 1);
		ExpPercent = (int)(100000.0f / (float)ExpSize * (float)ExpNowSize);
		ExpPercentSpot = (int)(ExpPercent % 1000);
		ExpPercent = ExpPercent / 1000;


		cHelpPet.PetExp = ExpPercent;

		if (ExpPercentSpot < 10)
		{
			wsprintf(szInfoMsgBuff6, "%d.00%d%s", ExpPercent, ExpPercentSpot, "%  ");
		}
		else if (ExpPercentSpot >= 10 && ExpPercentSpot < 100)
		{
			wsprintf(szInfoMsgBuff6, "%d.0%d%s", ExpPercent, ExpPercentSpot, "%  ");
		}
		else
			wsprintf(szInfoMsgBuff6, "%d.%d%s", ExpPercent, ExpPercentSpot, "%  ");

	}

}



int cINTERFACE::SetStringEffect(int Index)
{
	if(!HA_EffectIndex[Index])
	{
		HA_EffectIndex[Index] = CreateTextureMaterial(HaEffectFilePath[Index], 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
		ReadTextures();
	}
	for(int i = 0; i < MAX_HAEFFECTNUM; i++)
	{
		if(!HaEffect[i].Flag)
		{
			HaEffect[i].Flag = 1;
			HaEffect[i].Time = 0;
			HaEffect[i].Mat = HA_EffectIndex[Index];
			HaEffect[i].Posi.x = 354;
			HaEffect[i].Posi.y = 488;
			HaEffect[i].Size.x = 128;
			HaEffect[i].Size.y = 64;
			return true;
		}
	}
	return false;

}

