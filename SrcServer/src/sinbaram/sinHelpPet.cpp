
#include "sinLinkHeader.h"

#include "tjboy\\clanmenu\\tjclan.h"
#include "tjboy\\clanmenu\\Help.h"
#include "..\\field.h"

cHELPPET cHelpPet;
int MatPetImage[4] = { 0, };
int PetMessageOkButtonFlag = 0;

void cHELPPET::Init()
{

	Load();
}

void cHELPPET::Load()
{

	MatPetImage[0] = CreateTextureMaterial("Image\\SinImage\\PetData\\Pet_terry-pose.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatPetImage[1] = CreateTextureMaterial("Image\\SinImage\\PetData\\Pet_nepsys-pose.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatPetImage[2] = CreateTextureMaterial("Image\\SinImage\\PetData\\Pet_io-pose.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatPetImage[3] = CreateTextureMaterial("Image\\SinImage\\PetData\\Pet-mute-pose.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

}

void cHELPPET::Release()
{

}

void cHELPPET::Draw()
{
	if(PetKind && PetShow)
	{
		if(HelpMsgFlag)
		{
			g_Help.DrawBox(3, 3, 32, 4);
			dsDrawTexImage(MatPetImage[PetKind - 1], 10, 20, 64, 64, 255);
			DrawSprite(522, 94, lpbltr_Button_OK_G, 0, 0, 47, 12);
			if(PetMessageOkButtonFlag)
			{
				DrawSprite(522, 94, lpbltr_Button_OK, 0, 0, 47, 12);
			}

		}
		DrawPetMessage();
	}
}
void cHELPPET::Draw(POINT3D *pPosi, POINT3D *pAngle)
{

}

void cHELPPET::DrawText()
{

	if(!HelpMsgFlag)return;
	HDC	hdc = NULL;
	//renderDevice.lpDDSBack->GetDC(&hdc);
	SelectObject(hdc, sinFont);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));

	for(int i = 0; i < (int)PetMsg_Map[HelpMsgId].size(); i++)
	{
		dsTextLineOut(hdc, 75, 22 + (i * 15), PetMsg_Map[HelpMsgId][i]->c_str(), PetMsg_Map[HelpMsgId][i]->length());

	}

	//renderDevice.lpDDSBack->ReleaseDC(hdc);

}

void cHELPPET::Close()
{

}

DWORD sinPetLoadingTime = 0;
void cHELPPET::Main()
{

	if(LoadingPet)
	{
		sinPetLoadingTime++;
		if(sinPetLoadingTime >= 70 * 3)
		{
			CheckPetData();
			LoadingPet = 0;
			sinPetLoadingTime = 0;

		}
	}

	if(PetKind && PetShow)
	{
		PetRandomNormalMessage();
		PetRandomBattleMessage();
	}

	if(PetKind && PetShow)
	{
		if(MsgFlag)
		{
			MsgTime++;
			if(MsgTime > (70 * 4))
			{
				MsgFlag = 0;
				MsgTime = 0;
				szTempId[0] = 0;
				MessageIndex = -1;
			}
		}
	}

	string TempString;
	if(PetMessageOkButtonFlag != 2)
		PetMessageOkButtonFlag = 0;
	if(HelpMsgFlag)
	{
		HelpMsgTime++;
		if(522 < pCursorPos.x && 522 + 50 > pCursorPos.x &&
		   94 < pCursorPos.y && 94 + 25 > pCursorPos.y)
		{
			if(PetMessageOkButtonFlag != 2)
			{
				PetMessageOkButtonFlag = 1;
			}
		}
		if(HelpMsgTime > (70 * 15) || PetMessageOkButtonFlag == 2)
		{
			PetMessageOkButtonFlag = 0;
			HelpMsgTime = 0;
			HelpMsgFlag = 0;

			if(lstrcmp(HelpMsgId, "*Level_Message10-2") == 0)
			{
				if(sinChar->Level >= 10)
				{
					ClosePet();

				}
			}


			if(!Message_Keep.empty())
			{
				HelpMsgFlag = 1;
				TempString = Message_Keep.front();
				strcpy_s(HelpMsgId, TempString.c_str());
				Message_Keep.pop_front();
			}
		}
	}
}

void cHELPPET::LButtonDown(int x, int y)
{
	if(PetMessageOkButtonFlag)
	{
		PetMessageOkButtonFlag = 2;

	}

}

void cHELPPET::LButtonUp(int x, int y)
{

}

void cHELPPET::RButtonDown(int x, int y)
{

}

void cHELPPET::RButtonUp(int x, int y)
{

}


char *szPetMessageCommand[] = {
	"*PetKind",
	"*PetName",
	"*Welcom_ALL",
	"*Welcom_Tems",
	"*Welcom_Mora",
	"*ChatBox",
	"*ChatTab_All",
	"*ChatTab_Clan",
	"*ChatTab_Party",
	"*ChatTab_Trade",
	"*ChatTab_Whisper",
	"*Bar_Stamina",
	"*Bar_Life",
	"*LeftSkill",
	"*RightSkill",

	"*Bar_Mana",
	"*DayandNight",
	"*Bar_Exp",
	"*Exp_Num",
	"*Potion_ShortKey",

	"*RunAndWalk",
	"*Camera_Hand",
	"*Camera_Auto",
	"*Camera_Fix",
	"*Mini_Map",
	"*CarStatus",
	"*InvenTory",
	"*Skill",
	"*Party",
	"*Quest",
	"*System",
	"*InvenTory_Item",
	"*Drop_Item",
	"*Monster",
	"*Message",


	"*Battle_Message",
	"*Normal_Message",

	"*Level_Message2-1",
	"*Level_Message2-2",
	"*Level_Message3",
	"*Level_Message4",
	"*Level_Message5",
	"*Level_Message6-1",
	"*Level_Message6-2",
	"*Level_Message7",
	"*Level_Message8",
	"*Level_Message9-1",
	"*Level_Message9-2",
	"*Level_Message10-1",
	"*Level_Message10-2",

	"*Special_Message8_Mecha",
	"*Special_Message8_Fighter",
	"*Special_Message8_Pikeman",
	"*Special_Message8_Archer",
	"*Special_Message8_Knight",
	"*Special_Message8_Atalanta",
	"*Special_Message8_Priestess",
	"*Special_Message8_Magician",
	"*Special_Message9",
	"",

};


int sinTestMessageIndex = 0;
void cHELPPET::KeyDown()
{


	int len = 0;
	if(smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
	{
		if(sinGetKeyClick('B'))
		{
			len = lstrlen(szPetMessageCommand[38 + sinTestMessageIndex]);
			if(len)
			{
				PetMessageHelp(szPetMessageCommand[38 + sinTestMessageIndex]);
				sinTestMessageIndex++;
			}
			else
			{
				sinTestMessageIndex = 0;

			}
		}
	}
}

int cHELPPET::GetFileData()
{

	char *szFilePath = "Image\\SinImage\\PetData\\PetMessage.txt";

	char decode[512];
	char decode2[512];
	char line[512];

	FILE	*fp;
	char *p;
	int CmdNum;

	fp = fopen(szFilePath, "rb");
	if(fp == NULL) return FALSE;

	CmdNum = 0;
	while(!feof(fp))
	{
		if(fgets(line, 255, fp) == NULL)	break;
		p = GetWord(decode, line);

		if(lstrcmp(decode, szPetMessageCommand[CmdNum]) == 0)
		{
			while(1)
			{
				if(fgets(line, 255, fp) == NULL)	break;
				GetString(decode, line);
				GetWord(decode2, line);
				if(lstrcmp(decode2, "end") == 0)break;
				PetMsg_Map[szPetMessageCommand[CmdNum]].push_back(new string(decode));

			}
			CmdNum++;
		}
	}
	return TRUE;
}

int cHELPPET::PetMessage(char *Id, int Index)
{

	if(!PetKind || !PetShow)return FALSE;

	if(0 == Index && lstrcmp(Id, szTempId) == 0)
	{
		MsgTime = 1;
		return FALSE;
	}
	MessageIndex = Index;
	strcpy_s(szTempId, Id);
	if(Index <= (int)PetMsg_Map[Id].size() - 1)
	{
	#ifdef	_LANGUAGE_VEITNAM
		wsprintf(szPetBuff, "%s :   %s", PetMsg_Map["*PetName"][PetKind - 1]->c_str(), PetMsg_Map[Id][Index]->c_str());
	#else
		wsprintf(szPetBuff, "%s : %s", PetMsg_Map["*PetName"][PetKind - 1]->c_str(), PetMsg_Map[Id][Index]->c_str());
	#endif
	}


	if(sinChar->Level >= 10)
	{
		MsgFlag = 0;
		MsgTime = 0;
	}
	else
	{
		MsgFlag = 1;
		MsgTime = 0;
	}
	return TRUE;
}

int cHELPPET::DrawPetMessage()
{
	if(MsgFlag)
	{
		PetRendPoint = HoPetRenderPoint;
		DrawCharacterMessage(PetRendPoint.x, PetRendPoint.y, szPetBuff, 30);

	}
	return TRUE;

}

int cHELPPET::PetMessageHelp(char *Id)
{

	if(HelpMsgFlag)
		Message_Keep.push_back(Id);
	else
	{
		HelpMsgFlag = 1;
		strcpy_s(HelpMsgId, Id);
	}
	return TRUE;
}


int cHELPPET::CheckPetData()
{


	if(LoadingPet == 0)
	{
		LoadingPet = 1;
		return FALSE;

	}


	if(sinChar->Level >= 10)return FALSE;
	char szTempBuff[128];


	if(!GetFileData())return FALSE;
	if(PetKind == 0)
	{
		PetKind = GetRandomPos(1, 4);

		wsprintf(szTempBuff, PetMsg_Map["*Welcom_ALL"][0]->c_str(), PetMsg_Map["*PetKind"][PetKind - 1]->c_str());
		PetMsg_Map["*Welcom_ALL"][0]->assign(szTempBuff);

		wsprintf(szTempBuff, PetMsg_Map["*Welcom_ALL"][1]->c_str(), PetMsg_Map["*PetName"][PetKind - 1]->c_str());
		PetMsg_Map["*Welcom_ALL"][1]->assign(szTempBuff);
		PetMessageHelp("*Welcom_ALL");


		if(sinChar->JOB_CODE < 5)
		{
			PetMessageHelp("*Welcom_Tems");

		}
		else
		{
			PetMessageHelp("*Welcom_Mora");

		}
	}


	int i = 0;
	for(i = 0; i < (int)PetMsg_Map["*Normal_Message"].size(); i++)
	{
		NormalMsg_Index.push_back(i);
	}
	for(i = 0; i < (int)PetMsg_Map["*Battle_Message"].size(); i++)
	{
		BattleMsg_Index.push_back(i);
	}
	ShowPet();
	PetShow = 1;

	return TRUE;
}


DWORD dwRandomMsgTime = 0;
int cHELPPET::PetRandomNormalMessage()
{

	if(!PetKind || !PetShow)return FALSE;


	int RandomNum = 0;
	int i = 0;
	dwRandomMsgTime++;
	if(lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_VILLAGE)
	{
		if(dwRandomMsgTime >= 70 * 30)
		{

			if(NormalMsg_Index.size() != 0)
			{
				RandomNum = GetRandomPos((int)NormalMsg_Index.front(), (int)NormalMsg_Index.back());
				NormalMsg_Index.remove(RandomNum);
				PetMessage("*Normal_Message", RandomNum);
				dwRandomMsgTime = 0;
			}
			else
			{
				for(i = 0; i < (int)PetMsg_Map["*Normal_Message"].size(); i++)
				{
					NormalMsg_Index.push_back(i);
				}
			}
		}
	}
	return TRUE;
}
int PetExpMessage[] = { 5,10,20,30,35,40,50,60,70,80,90,100 };
int PetExpIndex = 0;
int ExpMessageFlag = 0;
int cHELPPET::PetRandomBattleMessage()
{
	int RandomNum = 0;
	int i = 0;

	if(LevelFlag)
	{
		PetExpIndex = 0;
		LevelFlag = 0;

	}
	if(lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_ATTACK)
	{
		if(sinChar->Level < 8)
		{
			if(cHelpPet.PetExp > PetExpMessage[PetExpIndex])
			{
				if(BattleMsg_Index.size() != 0)
				{
					RandomNum = GetRandomPos((int)BattleMsg_Index.front(), (int)BattleMsg_Index.back());
					BattleMsg_Index.remove(RandomNum);
					PetMessage("*Battle_Message", RandomNum);
					PetExpIndex++;
				}
				else
				{
					for(i = 0; i < (int)PetMsg_Map["*Battle_Message"].size(); i++)
					{
						BattleMsg_Index.push_back(i);
					}
				}
			}
		}
		else
		{
			if(sinChar->Level == 8 && cHelpPet.PetExp >= 90 && !ExpMessageFlag)
			{
				ExpMessageFlag = 1;
				switch(sinChar->JOB_CODE)
				{
					case 1:
					PetMessageHelp("*Special_Message8_Fighter");
					break;
					case 2:
					PetMessageHelp("*Special_Message8_Mecha");
					break;
					case 3:
					PetMessageHelp("*Special_Message8_Archer");
					break;
					case 4:
					PetMessageHelp("*Special_Message8_Pikeman");
					break;
					case 5:
					PetMessageHelp("*Special_Message8_Atalanta");
					break;
					case 6:
					PetMessageHelp("*Special_Message8_Knight");
					break;
					case 7:
					PetMessageHelp("*Special_Message8_Magician");
					break;
					case 8:
					PetMessageHelp("*Special_Message8_Priestess");
					break;
				}

			}
			if(sinChar->Level == 9 && cHelpPet.PetExp >= 90 && ExpMessageFlag != 2)
			{
				ExpMessageFlag = 2;
				PetMessageHelp("*Special_Message9");

			}
		}
	}
	return TRUE;
}


int cHELPPET::ShowPet()
{

	if(!PetKind || (sinChar->Level >= 10 && cHelpPet.PetShow == 0))return FALSE;

	switch(PetKind)
	{
		case 1:
		g_LowLevelAddPet(lpCurPlayer, HoLowLevelPet::Type::Terry);
		break;
		case 2:
		g_LowLevelAddPet(lpCurPlayer, HoLowLevelPet::Type::Nepsys);
		break;
		case 3:
		g_LowLevelAddPet(lpCurPlayer, HoLowLevelPet::Type::Io);
		break;
		case 4:
		g_LowLevelAddPet(lpCurPlayer, HoLowLevelPet::Type::Mute);
		break;
	}

	return TRUE;
}
int cHELPPET::ClosePet()
{

	PetShow = 0;
	g_LowLevelDeletePet(lpCurPlayer);

	return TRUE;
}
int cHELPPET::PetOnOff(char *szBuff)
{
	if(sinChar->Level >= 10)return FALSE;
	if(lstrcmp(szBuff, "/µµ¿ì¹Ì") == 0)
	{
		PetShow ^= 1;
		switch(PetShow)
		{
			case 0:
			ClosePet();

			break;
			case 1:
			ShowPet();
			break;
		}
	}
	return TRUE;
}