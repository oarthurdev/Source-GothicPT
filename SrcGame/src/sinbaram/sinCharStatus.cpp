

#include "sinLinkHeader.h"
#include "Language\\Language.h"
#include "tjboy\\clanmenu\\tjclanDEF.h"
#include "tjboy\\clanmenu\\tjclan.h"
#include "tjboy\\clanmenu\\cE_CViewClanInfo.h"


cCHARSTATUS cCharStatus;
sDISPLAYSTATE sDisplayState[10];
sDISPLAYSTATE sDisplayStateShow;


int OldLevel;

int OldLevelTemp;

int sinLevelPoint = 0;

int sinPointButtonDown = 0;

int ShowCharArrow = 0;

int RegiInfoPosi = 0;

int ReHeight3 = 2;
//POSIÇAÕ DOS STATUS
sCHARRECTPOSI	sCharRectPosi[MAX_CHAR_RECT_POSI] = {

	{"Class"    ,{ 63   , 443 + ReHeight3  , 160 , 454  }},
	{"Name"     ,{ 65   , 463 + ReHeight3  , 160 , 479  }},
	{"Level"    ,{ 85   , 503 + ReHeight3  , 128 , 504  }},
	{"Exp"      ,{ 65   , 543 + ReHeight3  , 160 , 549  }},
	{"Next_Exp" ,{ 65   , 563 + ReHeight3  , 160 , 574  }},
	{"Life"		,{ 380  , 430 + ReHeight3  , 460 , 459  }},
	{"Mana"     ,{ 382  , 455 + ReHeight3  , 460 , 472  }},
	{"Stamina"  ,{ 385  , 478 + ReHeight3  , 460 , 508  }},

	{"Strength" ,{ 585 , 433 + ReHeight3 , 632 , 444  }},
	{"Spirit"   ,{ 585 , 454 + ReHeight3 , 632 , 464  }},
	{"Talent"   ,{ 585 , 473 + ReHeight3 , 632 , 485  }},
	{"Dexterity",{ 585 , 493 + ReHeight3 , 632 , 504  }},
	{"Health"   ,{ 585 , 513 + ReHeight3 , 632 , 524  }},

	{"Coins"   ,{ 215 , 448 , 215  , 468 }},
	{"Minutos" ,{ 260 , 448 , 260  , 469 }},
	{"Fire"     ,{ 305 , 448 , 305 , 469 }},
	{"Lighting" ,{ 215 , 470, 215  , 505 }},
	{"Ice"      ,{ 260 , 470, 260  , 543 }},

	{"Attack_Rating" ,{ 710 , 455 + ReHeight3 - 1 , 769 , 464 }},
	{"Attack_Damage" ,{ 710 , 474 + ReHeight3 - 1 , 769 , 484 }},
	{"Defence"       ,{ 710 , 495 + ReHeight3 - 1 , 769 , 504 }},
	{"Speed"         ,{ 710 , 515 + ReHeight3 - 1 , 769 , 524 }},
	{"Absorption"    ,{ 710 , 534 + ReHeight3 - 1 , 769 , 545 }},
	{"Point"         ,{ 585 , 533 + ReHeight3 - 1 , 632 , 544 }},

	{"LifeRegen"      ,{ 420 , 431 + ReHeight3 , 515  , 440 }},
	{"ManaRegen"      ,{ 420 , 455 + ReHeight3 , 515  , 466 }},
	{"StaminaRegen"   ,{ 420 , 479 + ReHeight3 , 515  , 490 }},

	{"Critical"   ,{ 264 , 490, 264  , 543 }},
	{"Block"      ,{ 264 , 510, 264  , 543 }},
	{"Evade"      ,{ 264 , 530, 264  , 543 }},
	{"AtkSpeed"   ,{ 264 , 550, 264  , 543 }},

};

int RegiBox[5][4] = {
	{ 185 , 445 , 216  , 475 },
	{ 185 , 482 , 216  , 512 },
	{ 185 , 519 , 216  , 550 },
	{ 251 , 445 , 281  , 475 },
	{ 251 , 482 , 281  , 512 },


};

int PointButton[6][4] = {
	{565 + 1,431 + 1,583,449},
	{565 + 1,452 + 1,583,469},
	{565 + 1,472 + 1,583,488},
	{565 + 1,491 + 1,583,508},
	{565 + 1,511 + 1,583,529},
	{565 + 1,531 + 1,583,549},

};

int TempStatePoint[5] = { 0,0,0,0,0 };

int PointButtonPosi = 0;

LPDIRECT3DTEXTURE9	lpStatusMain;


int MatChatBotton_Glay = 0;
LPDIRECT3DTEXTURE9 lpChatButton[5];
LPDIRECT3DTEXTURE9 lpChatButton_Notice[3];
LPDIRECT3DTEXTURE9 lpChatLine;
int NoticeChatIndex = 1;
int NoticeChatIndexNum = 0;
int ChatKindIndex = 0;
int ChatKindIndexNum = 0;




cCHARSTATUS::cCHARSTATUS()
{
	OpenFlag = 0;

}

cCHARSTATUS::~cCHARSTATUS()
{

}


int chatico, chatbar;

void cCHARSTATUS::Init()
{
	Load();


	SkillTextColor[SIN2_ATTACK_RATE] = SIN_TEXT_COLOR_WHITE;
	SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_WHITE;
	SkillTextColor[SIN2_DEFENSE] = SIN_TEXT_COLOR_WHITE;
	SkillTextColor[SIN2_ABSORB] = SIN_TEXT_COLOR_WHITE;
	SkillTextColor[SIN2_SPEED] = SIN_TEXT_COLOR_WHITE;


	MatChatBotton_Glay = CreateTextureMaterial("game\\GUI\\Interface\\Chat\\Chatting06.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);


	

	chatico = CreateTextureMaterial("Image\\SinImage\\help\\scl_icon.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	chatbar = CreateTextureMaterial("Image\\SinImage\\help\\scl_bar.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
}

void cCHARSTATUS::Load()
{
	lpChangeArrow[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Status\\ChangeArrow.bmp");
	lpSelectArrow[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Status\\SelectArrow.bmp");
	lpSelectArrow[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Status\\SelectArrow2.bmp");
	lpStatusPoint = LoadDibSurfaceOffscreen("Image\\SinImage\\Status\\StatusPoint.bmp");

	lpStatusMain = LoadDibSurfaceOffscreen("Image\\SinImage\\Status\\Status.bmp");

	lpChatButton[0] = LoadDibSurfaceOffscreen("game\\GUI\\Interface\\Chat\\ChatTap_01.bmp");
	lpChatButton[1] = LoadDibSurfaceOffscreen("game\\GUI\\Interface\\Chat\\ChatTap_02.bmp");
	lpChatButton[2] = LoadDibSurfaceOffscreen("game\\GUI\\Interface\\Chat\\ChatTap_03.bmp");
	lpChatButton[3] = LoadDibSurfaceOffscreen("game\\GUI\\Interface\\Chat\\ChatTap_04.bmp");
	lpChatButton[4] = LoadDibSurfaceOffscreen("game\\GUI\\Interface\\Chat\\ChatTap_05.bmp");

	lpChatButton_Notice[0] = LoadDibSurfaceOffscreen("game\\GUI\\Interface\\Chat\\ChatTap_N11.bmp");
	lpChatButton_Notice[1] = LoadDibSurfaceOffscreen("game\\GUI\\Interface\\Chat\\ChatTap_N12.bmp");
	lpChatButton_Notice[2] = LoadDibSurfaceOffscreen("game\\GUI\\Interface\\Chat\\ChatTap_N22.bmp");

	lpChatLine = LoadDibSurfaceOffscreen("game\\GUI\\Interface\\Chat\\n_line.bmp");
}

void cCHARSTATUS::Release()
{
	int i;
	for(i = 0; i < 5; i++)
	{
		if(lpRegiBox[i])
		{
			lpRegiBox[i]->Release();
			lpRegiBox[i] = 0;

		}

	}
	if(lpChangeArrow[0])
	{
		lpChangeArrow[0]->Release();
		lpChangeArrow[0] = 0;
	}
	if(lpSelectArrow[0])
	{
		lpSelectArrow[0]->Release();
		lpSelectArrow[0] = 0;
	}
	if(lpSelectArrow[1])
	{
		lpSelectArrow[1]->Release();
		lpSelectArrow[1] = 0;
	}
	if(lpStatusPoint)
	{
		lpStatusPoint->Release();

	}

}

extern BOOL bMic;
void cCHARSTATUS::Draw()
{

	int TempLen = 0;
	int TempCount2 = 0;



	if(sinChatEnter)
	{
		if(SubChatHeight)
		{
			dsDrawTexImage(cInterFace.MatChatDoc[0], 4, 576 - SubChatHeight, 242, 32, 255);
			dsDrawTexImage(cInterFace.MatChatDoc[1], 246, 576 - SubChatHeight, 164, 32, 255);
		}
		else
			dsDrawTexImage(cInterFace.MatChatDoc[0], 4, 576 - SubChatHeight, 296, 32, 255);

	}

	if(cInterFace.ChatFlag)
	{
		if(SubChatHeight)
		{
			dsDrawTexImage(cInterFace.MatChatSmall[0], 0, 294, 300, 116, 255);

			if (ChatBuffCnt >= 10)

			{
				dsDrawTexImage(chatbar, 285, 302, 8, 106, 255);
				dsDrawTexImage(chatico, 281, 302 + 93 - static_cast<int>(ChatScrollPoint*3.0), 16, 16, 255);
			}

		}
		else
		{
			dsDrawTexImage(cInterFace.MatChatDefault[0], 0, 600 - 192, 305, 210, 255);

			if (ChatBuffCnt >= 14)

			{
				dsDrawTexImage(chatbar, 289, 416, 8, 150, 255);
				dsDrawTexImage(chatico, 285, 416 + 133 - static_cast<int>(ChatScrollPoint*4.2), 16, 16, 255);
			}
			//Barra de Chat - menus
			dsDrawTexImage(MatChatBotton_Glay, 100, 564, 256, 16, 255);
			DrawSprite(100 + ChatKindIndex * 40, 564, lpChatButton[ChatKindIndex], 0, 0, 40, 16);


			DrawSprite(4, 564, lpChatButton_Notice[NoticeChatIndex], 0, 0, 45, 16);

			if(NoticeChatIndex == 1)
			{
				DrawSprite(10, 460, lpChatLine, 0, 0, 287, 3);

				

			}
			else
			{

				

			}

		}
	}

	if(sinMoveKindInter[SIN_CHARSTATUS] != 0)
	{
		DrawSprite(0, 600 - sinMoveKindInter[SIN_CHARSTATUS] + 56, lpStatusMain, 0, 0, 800, 200);


		if(ShowCharArrow)
		{

			DrawSprite(251, 565 + (256 - sinMoveKindInter[SIN_CHARSTATUS]), cShop.lpExit, 0, 0, 20, 20);
			DrawSprite(251, 565 - 27 + (256 - sinMoveKindInter[SIN_CHARSTATUS]), cInvenTory.lpExitInfo, 0, 0, 47, 27);
		}

		if(sinChar->StatePoint)
		{
			DrawSprite(520, 531 + (256 - sinMoveKindInter[SIN_CHARSTATUS]), lpStatusPoint, 0, 0, 115, 19);
			for(int i = 0; i < 5; i++)
			{
				DrawSprite(PointButton[i][0], PointButton[i][1] + (256 - sinMoveKindInter[SIN_CHARSTATUS]), lpChangeArrow[0], 0, 0, 18, 17);
			}
			if(sinPointButtonDown)
			{
				if(PointButtonPosi <= 5 && PointButtonPosi != 0)
					DrawSprite(PointButton[PointButtonPosi - 1][0] + 1, PointButton[PointButtonPosi - 1][1] + (256 - sinMoveKindInter[SIN_CHARSTATUS]) + 1, lpSelectArrow[0], 0, 0, 18, 17);

				if(PointButtonPosi == 6)
					DrawSprite(PointButton[PointButtonPosi - 1][0] + 1, PointButton[PointButtonPosi - 1][1] + (256 - sinMoveKindInter[SIN_CHARSTATUS]) + 1, lpSelectArrow[1], 0, 0, 18, 17);
			}
		}

#ifdef  __CLANSUBCHIP__
		if(cldata.myPosition == 100 || cldata.myPosition == 101 || cldata.myPosition == 104)
		{
#else
		if(cldata.myPosition == 100 || cldata.myPosition == 101)
		{
#endif
			if(cldata.hClanMark16)
			{
				TempLen = lstrlen(cldata.name);
				TempCount2 = 6 - (TempLen / 2);
				DrawSprite(CheckEditSize(sCharRectPosi[1].Rect.left, sCharRectPosi[1].Rect.right, cldata.name) - ((12 - TempLen / 2)) - TempCount2,
					sCharRectPosi[1].Rect.top + 15 + (256 - sinMoveKindInter[SIN_CHARSTATUS]), cldata.hClanMark16, 0, 0, 16, 16);
			}
		}		
	}
}

DWORD dwSkillTextTime = 0;
DWORD dwSkillTextTimeFlag = 0;
void cCHARSTATUS::Main()
{

	if(cSkill.SearchContiueSkill(SKILL_FROST_JAVELIN))
	{
		dwSkillTextTime++;
		if(dwSkillTextTime > 70)
		{
			switch(dwSkillTextTimeFlag)
			{
			case 0:
				dwSkillTextTimeFlag = 1;
				break;
			case 1:
				dwSkillTextTimeFlag = 2;
				break;
			case 2:
				dwSkillTextTimeFlag = 1;
				break;
			}
			dwSkillTextTime = 0;
		}
	}
	else dwSkillTextTimeFlag = 0;

	int  i;
	ShowCharArrow = 0;
	RegiInfoPosi = 0;
	PointButtonPosi = 0;


	ChatKindIndexNum = 0;
	if(cInterFace.ChatFlag)
	{
		if(!SubChatHeight)
		{
			for(int t = 0; t < 5; t++)
			{
				if(pCursorPos.x > 100 + (t * 40) && pCursorPos.x < 100 + ((t + 1) * 40) && pCursorPos.y > 563 && pCursorPos.y < 563 + 16)
					ChatKindIndexNum = t + 1;
				switch(ChatKindIndexNum)
				{
				case 1:
					cHelpPet.PetMessage("*ChatTab_All", 0);

					break;
				case 2:
					cHelpPet.PetMessage("*ChatTab_Clan", 0);

					break;
				case 3:
					cHelpPet.PetMessage("*ChatTab_Party", 0);

					break;
				case 4:
					cHelpPet.PetMessage("*ChatTab_Trade", 0);

					break;
				case 5:
					cHelpPet.PetMessage("*ChatTab_Whisper", 0);

					break;
				}

			}
		}
	}


	NoticeChatIndexNum = 0;
	if(cInterFace.ChatFlag)
	{
		if(!SubChatHeight)
		{
			if(pCursorPos.x > 0 && pCursorPos.x < 45 && pCursorPos.y > 563 && pCursorPos.y < 563 + 16)
			{
				NoticeChatIndexNum = 1;
			}
		}
	}
	if(pCursorPos.x > 251 && pCursorPos.x < 269 && pCursorPos.y > 565 && pCursorPos.y < 583)
		ShowCharArrow = 1;
	if(OpenFlag)
	{
		for(i = 0; i < 8; i++)
			if(pCursorPos.x >= RegiBox[i][0] && pCursorPos.x <= RegiBox[i][2] &&
				pCursorPos.y >= RegiBox[i][1] && pCursorPos.y <= RegiBox[i][3])
			{
				RegiInfoPosi = i + 1;

			}
		for(i = 0; i < 6; i++)
			if(pCursorPos.x >= PointButton[i][0] && pCursorPos.x <= PointButton[i][2] &&
				pCursorPos.y >= PointButton[i][1] && pCursorPos.y <= PointButton[i][3])
			{
				PointButtonPosi = i + 1;
			}

	}
	else
	{
		for(i = 0; i < 5; i++)
			TempStatePoint[i] = 0;

	}

	if(sinLoadOK)
		CheckLevel();

}

void cCHARSTATUS::Close()
{

}

void cCHARSTATUS::LButtonDown(int x, int y)
{
	int cnt;


	if(NoticeChatIndexNum)
	{
		NoticeChatIndex++;
		if(NoticeChatIndex >= 3)NoticeChatIndex = 1;

	}

	if(ChatKindIndexNum)
	{
		ChatKindIndex = ChatKindIndexNum - 1;
		SetChatMsgFilter(ChatKindIndex);
		switch(ChatKindIndexNum)
		{
		case 1:
			cHelpPet.PetMessage("*ChatTab_All", 1);

			break;
		case 2:
			cHelpPet.PetMessage("*ChatTab_Clan", 1);

			break;
		case 3:
			cHelpPet.PetMessage("*ChatTab_Party", 1);

			break;
		case 4:
			cHelpPet.PetMessage("*ChatTab_Trade", 1);

			break;
		case 5:
			cHelpPet.PetMessage("*ChatTab_Whisper", 1);

			break;
		}

	}

	if(OpenFlag)
	{
		if(x > 251 && x < 269 && y > 565 && y < 583)
			OpenFlag = SIN_CLOSE;

		if(VRKeyBuff['B'])
		{
			if(sinChar->StatePoint > 9)
			{
				sinPointButtonDown = 1;
				switch(PointButtonPosi)
				{
				case 1:
					CheckCharForm();
					sinChar->Strength += 9;
					sinChar->StatePoint -= 9;
					for(cnt = 0; cnt < 4; cnt++)
						TempStatePoint[cnt] = TempStatePoint[cnt + 1];
					TempStatePoint[4] = POINT_STRENGTH;
					ReformCharForm();
					cInvenTory.SetItemToChar();
					cInvenTory.CheckDamage();

					break;
				case 2:
					CheckCharForm();
					sinChar->Spirit += 9;
					sinChar->StatePoint -= 9;
					for(cnt = 0; cnt < 4; cnt++)
						TempStatePoint[cnt] = TempStatePoint[cnt + 1];
					TempStatePoint[4] = POINT_SPIRIT;
					ReformCharForm();
					cInvenTory.SetItemToChar();
					cInvenTory.CheckDamage();


					break;

				case 3:
					CheckCharForm();
					sinChar->Talent += 9;
					sinChar->StatePoint -= 9;
					for(cnt = 0; cnt < 4; cnt++)
						TempStatePoint[cnt] = TempStatePoint[cnt + 1];
					TempStatePoint[4] = POINT_TALENT;
					ReformCharForm();
					cInvenTory.SetItemToChar();

					break;

				case 4:
					CheckCharForm();
					sinChar->Dexterity += 9;
					sinChar->StatePoint -= 9;
					for(cnt = 0; cnt < 4; cnt++)
						TempStatePoint[cnt] = TempStatePoint[cnt + 1];
					TempStatePoint[4] = POINT_DEXTERITY;
					ReformCharForm();
					cInvenTory.SetItemToChar();
					cInvenTory.CheckDamage();

					break;

				case 5:
					CheckCharForm();
					sinChar->Health += 9;
					sinChar->StatePoint -= 9;
					for(cnt = 0; cnt < 4; cnt++)
						TempStatePoint[cnt] = TempStatePoint[cnt + 1];
					TempStatePoint[4] = POINT_HEALTH;
					ReformCharForm();
					cInvenTory.SetItemToChar();
					cInvenTory.CheckDamage();

					break;

				case 6:
					for(cnt = 4; cnt >= 0; cnt--)
					{
						if(TempStatePoint[cnt])
						{
							switch(TempStatePoint[cnt])
							{
							case POINT_STRENGTH:
								CheckCharForm();
								sinChar->Strength -= 9;
								sinChar->StatePoint += 9;
								TempStatePoint[cnt] = 0;
								ReformCharForm();
								cInvenTory.SetItemToChar();
								cInvenTory.CheckDamage();
								break;
							case POINT_SPIRIT:
								CheckCharForm();
								sinChar->Spirit -= 9;
								sinChar->StatePoint += 9;
								TempStatePoint[cnt] = 0;
								ReformCharForm();
								cInvenTory.SetItemToChar();
								cInvenTory.CheckDamage();
								break;
							case POINT_TALENT:
								CheckCharForm();
								sinChar->Talent -= 9;
								sinChar->StatePoint += 9;
								TempStatePoint[cnt] = 0;
								ReformCharForm();
								cInvenTory.SetItemToChar();
								cInvenTory.CheckDamage();
								break;
							case POINT_DEXTERITY:
								CheckCharForm();
								sinChar->Dexterity -= 9;
								sinChar->StatePoint += 9;
								TempStatePoint[cnt] = 0;
								ReformCharForm();
								cInvenTory.SetItemToChar();
								cInvenTory.CheckDamage();

								break;
							case POINT_HEALTH:
								CheckCharForm();
								sinChar->Health -= 9;
								sinChar->StatePoint += 9;
								TempStatePoint[cnt] = 0;
								ReformCharForm();
								cInvenTory.SetItemToChar();
								cInvenTory.CheckDamage();
								break;

							}
							break;
						}
					}

					break;
				}
			}

		}


		if(sinChar->StatePoint > 0)
		{
			sinPointButtonDown = 1;
			switch(PointButtonPosi)
			{
			case 1:
				CheckCharForm();
				sinChar->Strength++;
				sinChar->StatePoint--;
				for(cnt = 0; cnt < 4; cnt++)
					TempStatePoint[cnt] = TempStatePoint[cnt + 1];
				TempStatePoint[4] = POINT_STRENGTH;
				ReformCharForm();
				cInvenTory.SetItemToChar();
				cInvenTory.CheckDamage();

				break;
			case 2:
				CheckCharForm();
				sinChar->Spirit++;
				sinChar->StatePoint--;
				for(cnt = 0; cnt < 4; cnt++)
					TempStatePoint[cnt] = TempStatePoint[cnt + 1];
				TempStatePoint[4] = POINT_SPIRIT;
				ReformCharForm();
				cInvenTory.SetItemToChar();
				cInvenTory.CheckDamage();


				break;

			case 3:
				CheckCharForm();
				sinChar->Talent++;
				sinChar->StatePoint--;
				for(cnt = 0; cnt < 4; cnt++)
					TempStatePoint[cnt] = TempStatePoint[cnt + 1];
				TempStatePoint[4] = POINT_TALENT;
				ReformCharForm();
				cInvenTory.SetItemToChar();
				cInvenTory.CheckDamage();

				break;

			case 4:
				CheckCharForm();
				sinChar->Dexterity++;
				sinChar->StatePoint--;
				for(cnt = 0; cnt < 4; cnt++)
					TempStatePoint[cnt] = TempStatePoint[cnt + 1];
				TempStatePoint[4] = POINT_DEXTERITY;
				ReformCharForm();
				cInvenTory.SetItemToChar();
				cInvenTory.CheckDamage();

				break;

			case 5:
				CheckCharForm();
				sinChar->Health++;
				sinChar->StatePoint--;
				for(cnt = 0; cnt < 4; cnt++)
					TempStatePoint[cnt] = TempStatePoint[cnt + 1];
				TempStatePoint[4] = POINT_HEALTH;
				ReformCharForm();
				cInvenTory.SetItemToChar();
				cInvenTory.CheckDamage();

				break;

			case 6:
				for(cnt = 4; cnt >= 0; cnt--)
				{
					if(TempStatePoint[cnt])
					{
						switch(TempStatePoint[cnt])
						{
						case POINT_STRENGTH:
							CheckCharForm();
							sinChar->Strength--;
							sinChar->StatePoint++;
							TempStatePoint[cnt] = 0;
							ReformCharForm();
							cInvenTory.SetItemToChar();
							break;
						case POINT_SPIRIT:
							CheckCharForm();
							sinChar->Spirit--;
							sinChar->StatePoint++;
							TempStatePoint[cnt] = 0;
							ReformCharForm();
							cInvenTory.SetItemToChar();
							cInvenTory.CheckDamage();
							break;
						case POINT_TALENT:
							CheckCharForm();
							sinChar->Talent--;
							sinChar->StatePoint++;
							TempStatePoint[cnt] = 0;
							ReformCharForm();
							cInvenTory.SetItemToChar();
							cInvenTory.CheckDamage();
							break;
						case POINT_DEXTERITY:
							CheckCharForm();
							sinChar->Dexterity--;
							sinChar->StatePoint++;
							TempStatePoint[cnt] = 0;
							ReformCharForm();
							cInvenTory.SetItemToChar();
							cInvenTory.CheckDamage();

							break;
						case POINT_HEALTH:
							CheckCharForm();
							sinChar->Health--;
							sinChar->StatePoint++;
							TempStatePoint[cnt] = 0;
							ReformCharForm();
							cInvenTory.SetItemToChar();
							cInvenTory.CheckDamage();
							break;

						}
						break;
					}
				}

				break;
			}

		}

	}


}

void cCHARSTATUS::LButtonUp(int x, int y)
{
	sinPointButtonDown = 0;
}

void cCHARSTATUS::RButtonDown(int x, int y)
{
	if(ChatKindIndexNum)
	{
		switch(ChatKindIndexNum)
		{
		case 1:
			cHelpPet.PetMessage("*ChatTab_All", 2);

			break;
		case 2:
			cHelpPet.PetMessage("*ChatTab_Clan", 2);

			break;
		case 3:
			cHelpPet.PetMessage("*ChatTab_Party", 2);

			break;
		case 4:
			cHelpPet.PetMessage("*ChatTab_Trade", 2);

			break;
		case 5:
			cHelpPet.PetMessage("*ChatTab_Whisper", 2);

			break;
		}

	}

}

void cCHARSTATUS::RButtonUp(int x, int y)
{

}

void cCHARSTATUS::KeyDown()
{

	if(sinGetKeyClick('C'))
	{
		cHelpPet.PetMessage("*CarStatus", 3);
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
	}
}


DWORD CharStatusColor[10] = { RGB(255,255,255) , RGB(255,0,0) ,RGB(255,220,0),
					RGB(142,230,254) , RGB(128,255,128) ,RGB(255,225,0),
					RGB(255,180,200) , RGB(255,230,10) ,   RGB(255,220,0),
					RGB(255,220,0)

};

int sinBackupTextColor = 0;


void cCHARSTATUS::DrawCharText()
{

	CheckChageStateDisplay();
	if(!sinMoveKindInter[SIN_CHARSTATUS])return;

	int TempLen = 0;
	HDC	hdc = NULL;
	char strBuff[128];
	memset(strBuff, 0, sizeof(strBuff));
	
	//SelectObject(hdc, sinFont);
	
	SetFontTextColor( RGB(255, 255, 255));



	wsprintf(strBuff, "%s", cInvenTory.JobName);
	dsTextLineOut( CheckEditSize(sCharRectPosi[0].Rect.left, sCharRectPosi[0].Rect.right, strBuff), sCharRectPosi[0].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]),
		strBuff, lstrlen(strBuff));

	wsprintf(strBuff, "%s", sinCharDisplay.szName);
	dsTextLineOut( CheckEditSize(sCharRectPosi[1].Rect.left, sCharRectPosi[1].Rect.right, strBuff), sCharRectPosi[1].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]),
		strBuff, lstrlen(strBuff));

#ifdef  __CLANSUBCHIP__
	if(cldata.myPosition == 100 ||
		cldata.myPosition == 101 || cldata.myPosition == 104)
	{
#endif
		TempLen = lstrlen(cldata.name);
		wsprintf(strBuff, "%s", cldata.name);
		dsTextLineOut( CheckEditSize(sCharRectPosi[1].Rect.left, sCharRectPosi[1].Rect.right, strBuff) + TempLen, sCharRectPosi[1].Rect.top + 20 + (253 - sinMoveKindInter[SIN_CHARSTATUS]),
			strBuff, lstrlen(strBuff));
	}

	wsprintf(strBuff, "%d", sinCharDisplay.Level);
	dsTextLineOut( CheckEditSize(sCharRectPosi[2].Rect.left, sCharRectPosi[2].Rect.right, strBuff), sCharRectPosi[2].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]),
		strBuff, lstrlen(strBuff));


	if(sinChar->Level > 76)
	{
		wsprintf(strBuff, "%dM", cCharStatus.sinGetNowExp());
		dsTextLineOut( CheckEditSize(sCharRectPosi[3].Rect.left, sCharRectPosi[3].Rect.right, strBuff), sCharRectPosi[3].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]),
			strBuff, lstrlen(strBuff));

	}
	else
	{
		wsprintf(strBuff, "%d", cCharStatus.sinGetNowExp());
		dsTextLineOut( CheckEditSize(sCharRectPosi[3].Rect.left, sCharRectPosi[3].Rect.right, strBuff), sCharRectPosi[3].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]),
			strBuff, lstrlen(strBuff));

	}


	if(sinChar->Level > 76)
	{
		wsprintf(strBuff, "%dM", cCharStatus.sinGetNextExp());
		dsTextLineOut( CheckEditSize(sCharRectPosi[4].Rect.left, sCharRectPosi[4].Rect.right, strBuff), sCharRectPosi[4].Rect.top + (254 - sinMoveKindInter[SIN_CHARSTATUS]),
			strBuff, lstrlen(strBuff));
	}
	else
	{
		wsprintf(strBuff, "%d", cCharStatus.sinGetNextExp());
		dsTextLineOut( CheckEditSize(sCharRectPosi[4].Rect.left, sCharRectPosi[4].Rect.right, strBuff), sCharRectPosi[4].Rect.top + (254 - sinMoveKindInter[SIN_CHARSTATUS]),
			strBuff, lstrlen(strBuff));

	}


	if (AddVirtualLife[1])
	{
		AddVirtualLife[0] = ((int)sinGetLife() * sinVirtualLifePercent) / 100;

	}
	
	if(AddVirtualMana[1])
	{
		AddVirtualMana[0] = ((int)sinGetMana() * sinVirtualManaPercent) / 100;

	}


	if(AddVirtualStamina[1])
	{
		AddVirtualStamina[0] = ((int)sinGetStamina() * sinVirtualStaminaPercent) / 100;

	}

	SetFontTextColor( CharStatusColor[SkillTextColor[SIN2_LIFE]]);
	wsprintf(strBuff, "%d/%d", sinGetLife() + AddVirtualLife[0], sinCharDisplay.Life[1] + AddVirtualLife[1]);
	dsTextLineOut( CheckEditSize(sCharRectPosi[5].Rect.left, sCharRectPosi[5].Rect.right, strBuff), sCharRectPosi[5].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]),
		strBuff, lstrlen(strBuff));

	SetTextColor(hdc, CharStatusColor[SkillTextColor[SIN2_LIFE]]);
	sprintf(strBuff, "%.1f", sinCharDisplay.Life_Regen);
	dsTextLineOut(CheckEditSize(sCharRectPosi[25].Rect.left, sCharRectPosi[24].Rect.right, strBuff), sCharRectPosi[24].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff));



	SetFontTextColor( CharStatusColor[SkillTextColor[SIN2_MANA]]);
	wsprintf(strBuff, "%d/%d", sinGetMana(), sinCharDisplay.Mana[1]);
	dsTextLineOut( CheckEditSize(sCharRectPosi[6].Rect.left, sCharRectPosi[6].Rect.right, strBuff), sCharRectPosi[6].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]),
		strBuff, lstrlen(strBuff));

	SetTextColor(hdc, CharStatusColor[SkillTextColor[SIN2_MANA]]);
	sprintf(strBuff, "%.1f", sinCharDisplay.Mana_Regen);
	dsTextLineOut(CheckEditSize(sCharRectPosi[26].Rect.left, sCharRectPosi[25].Rect.right, strBuff), sCharRectPosi[25].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff));


	SetFontTextColor( CharStatusColor[SkillTextColor[SIN2_STAMINA]]);
	wsprintf(strBuff, "%d/%d", sinGetStamina(), sinCharDisplay.Stamina[1]);
	dsTextLineOut( CheckEditSize(sCharRectPosi[7].Rect.left, sCharRectPosi[7].Rect.right, strBuff), sCharRectPosi[7].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]),
		strBuff, lstrlen(strBuff));

	SetTextColor(hdc, CharStatusColor[SkillTextColor[SIN2_STAMINA]]);
	sprintf(strBuff, "%.1f", sinCharDisplay.Stamina_Regen);
	dsTextLineOut(CheckEditSize(sCharRectPosi[26].Rect.left, sCharRectPosi[26].Rect.right, strBuff), sCharRectPosi[26].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff));

	SetFontTextColor( RGB(255, 255, 255));



	wsprintf(strBuff, "%d", sinCharDisplay.Strength);
	dsTextLineOut( CheckEditSize(sCharRectPosi[8].Rect.left, sCharRectPosi[8].Rect.right, strBuff), sCharRectPosi[8].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]),
		strBuff, lstrlen(strBuff));


	wsprintf(strBuff, "%d", sinCharDisplay.Spirit);
	dsTextLineOut( CheckEditSize(sCharRectPosi[9].Rect.left, sCharRectPosi[9].Rect.right, strBuff), sCharRectPosi[9].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]),
		strBuff, lstrlen(strBuff));



	wsprintf(strBuff, "%d", sinCharDisplay.Talent);
	dsTextLineOut( CheckEditSize(sCharRectPosi[10].Rect.left, sCharRectPosi[10].Rect.right, strBuff), sCharRectPosi[10].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]),
		strBuff, lstrlen(strBuff));



	wsprintf(strBuff, "%d", sinCharDisplay.Dexterity);
	dsTextLineOut( CheckEditSize(sCharRectPosi[11].Rect.left, sCharRectPosi[11].Rect.right, strBuff), sCharRectPosi[11].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]),
		strBuff, lstrlen(strBuff));

	wsprintf(strBuff, "%d", sinCharDisplay.Health);
	dsTextLineOut( CheckEditSize(sCharRectPosi[12].Rect.left, sCharRectPosi[12].Rect.right, strBuff), sCharRectPosi[12].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]),
		strBuff, lstrlen(strBuff));

	if(sinChar->StatePoint)
	{
		wsprintf(strBuff, "%d", sinChar->StatePoint);
		dsTextLineOut( CheckEditSize(sCharRectPosi[23].Rect.left, sCharRectPosi[23].Rect.right, strBuff), sCharRectPosi[23].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]),
			strBuff, lstrlen(strBuff));

	}

	SetFontTextColor( CharStatusColor[SkillTextColor[SIN2_ATTACK_RATE]]);
	wsprintf(strBuff, "%d", sinCharDisplay.Attack_Rating + sDisplayStateShow.Attack_Rate);
	dsTextLineOut( CheckEditSize(sCharRectPosi[18].Rect.left, sCharRectPosi[18].Rect.right, strBuff), sCharRectPosi[18].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]),
		strBuff, lstrlen(strBuff));



	if(dwSkillTextTimeFlag == 1)
	{
		SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_BLUE;
	}
	if(dwSkillTextTimeFlag == 2)
	{
		SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_YELLOW;
	}


	int DisplayDamage2[2] = { 0,0 };
	SetFontTextColor( CharStatusColor[SkillTextColor[SIN2_DAMAGE]]);
	DisplayDamage2[0] = sinCharDisplay.Attack_Damage[0] + sinTempDamage2[0] + sDisplayStateShow.Damage[0];
	DisplayDamage2[1] = sinCharDisplay.Attack_Damage[1] + sinTempDamage2[1] + sDisplayStateShow.Damage[1];
	if(DisplayDamage2[0] < 0)DisplayDamage2[0] = 0;
	if(DisplayDamage2[1] < 0)DisplayDamage2[1] = 0;
	wsprintf(strBuff, "%d-%d", DisplayDamage2[0], DisplayDamage2[1]);
	dsTextLineOut( CheckEditSize(sCharRectPosi[19].Rect.left, sCharRectPosi[19].Rect.right, strBuff), sCharRectPosi[19].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]),
		strBuff, lstrlen(strBuff));

	SetFontTextColor( CharStatusColor[SkillTextColor[SIN2_DEFENSE]]);
	wsprintf(strBuff, "%d", sinCharDisplay.Defence + sDisplayStateShow.Defense);
	dsTextLineOut( CheckEditSize(sCharRectPosi[20].Rect.left, sCharRectPosi[20].Rect.right, strBuff), sCharRectPosi[20].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]),
		strBuff, lstrlen(strBuff));

	SetFontTextColor( CharStatusColor[SkillTextColor[SIN2_ABSORB]]);
	wsprintf(strBuff, "%d", sinCharDisplay.Absorption + sinTempAbsorb + sDisplayStateShow.Absorb);
	dsTextLineOut( CheckEditSize(sCharRectPosi[21].Rect.left, sCharRectPosi[21].Rect.right, strBuff), sCharRectPosi[21].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]),
		strBuff, lstrlen(strBuff));


	SetFontTextColor( CharStatusColor[SkillTextColor[SIN2_SPEED]]);
	wsprintf(strBuff, "%d", sinCharDisplay.Move_Speed);
	dsTextLineOut( CheckEditSize(sCharRectPosi[22].Rect.left, sCharRectPosi[22].Rect.right, strBuff), sCharRectPosi[22].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]),
		strBuff, lstrlen(strBuff));




	SetTextColor(hdc, RGB(255, 255, 255));
	wsprintf(strBuff, "%d", sinCharDisplay.Resistance[0]);
	dsTextLineOut(CheckEditSize(sCharRectPosi[13].Rect.left, sCharRectPosi[13].Rect.right, strBuff), sCharRectPosi[13].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]),
		strBuff, lstrlen(strBuff));

	wsprintf(strBuff, "%d", sinCharDisplay.Resistance[5]);
	dsTextLineOut(CheckEditSize(sCharRectPosi[14].Rect.left, sCharRectPosi[14].Rect.right, strBuff), sCharRectPosi[14].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]),
		strBuff, lstrlen(strBuff));

	wsprintf(strBuff, "%d", sinCharDisplay.Resistance[2]);
	dsTextLineOut(CheckEditSize(sCharRectPosi[15].Rect.left, sCharRectPosi[15].Rect.right, strBuff), sCharRectPosi[15].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]),
		strBuff, lstrlen(strBuff));

	wsprintf(strBuff, "%d", sinCharDisplay.Resistance[4]);
	dsTextLineOut(CheckEditSize(sCharRectPosi[16].Rect.left, sCharRectPosi[16].Rect.right, strBuff), sCharRectPosi[16].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]),
		strBuff, lstrlen(strBuff));

	wsprintf(strBuff, "%d", sinCharDisplay.Resistance[3]);
	dsTextLineOut(CheckEditSize(sCharRectPosi[17].Rect.left, sCharRectPosi[17].Rect.right, strBuff), sCharRectPosi[17].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]),
		strBuff, lstrlen(strBuff));



	wsprintf(strBuff, "%d%%", sinCharDisplay.Critical_Hit);
	dsTextLineOut(CheckEditSize(sCharRectPosi[27].Rect.left, sCharRectPosi[27].Rect.right, strBuff), sCharRectPosi[27].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff));

	int TotalBlock = sinCharDisplay.Chance_Block;
	// Skill Extreme Shield MS
	if (lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_MECHANICIAN) {
		// skill ativa no momento
		int cnt = cSkill.SearchContiueSkill(SKILL_EXTREME_SHIELD);
		if (cnt > 0 && cnt <= 10) {
			if (sInven[1].ItemIndex) {
				if (sinDS1 == (cInvenTory.InvenItem[sInven[1].ItemIndex - 1].CODE & sinITEM_MASK2)) {
					cnt = E_Shield_BlockRate[cnt - 1];
					TotalBlock += cnt;
				}
			}
		}
	}

	// Skill Divine Shield KS
	if (lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_KNIGHT) {
		// skill ativa no momento
		int cnt = cSkill.SearchContiueSkill(SKILL_DIVINE_INHALATION);
		if (cnt > 0 && cnt <= 10) {
			if (sInven[1].ItemIndex) {
				if (sinDS1 == (cInvenTory.InvenItem[sInven[1].ItemIndex - 1].CODE & sinITEM_MASK2)) {
					cnt = D_Inhalation_Block[cnt - 1];
					TotalBlock += cnt;
				}
			}
		}
	}


	wsprintf(strBuff, "%d%%", TotalBlock);
	dsTextLineOut(CheckEditSize(sCharRectPosi[28].Rect.left, sCharRectPosi[28].Rect.right, strBuff), sCharRectPosi[28].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff));

	int TotalEvade = 0;

	// Skill Furtiva do Pikeman
	if (lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_PIKEMAN) {
		// skill ativa no momento
		int cnt = cSkill.SearchContiueSkill(SKILL_VAGUE);
		if (cnt > 0 && cnt <= 10) {
			if (sInven[0].ItemIndex) {
				if (sinWP1 == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE & sinITEM_MASK2)) {
					cnt = Vague_EvasionPercent[cnt - 1];
					TotalEvade += cnt;
				}
			}
		}
	}
	
	// Skill de Evasão da Arqueira
	if (lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_ARCHER) {
		// skill ativa no momento
		int cnt = cSkill.GetSkillPoint(SKILL_EVASION_MASTERY);
		if (cnt > 0 && cnt <= 10) {
			cnt = Evasion_Mastery_AddPercent[cnt - 1];
			TotalEvade += cnt;
		}
	}

	// Skill de Evasão da Sacer.
	if (lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_PRIESTESS) {
		// skill ativa no momento
		int cnt = cSkill.SearchContiueSkill(SKILL_SUMMON_MUSPELL);
		if (cnt > 0 && cnt <= 10) {
			cnt = Summon_Muspell_BlockPercent[cnt - 1];
			TotalEvade += cnt;
		}
	}

	// Skill Da atalanta
	int cnt = cSkill.SearchContiueSkill(SKILL_HALL_OF_VALHALLA);
	if (cnt > 0 && cnt <= 10) {
		cnt = Hall_Of_Valhalla_AddEvation[cnt - 1];
		TotalEvade += cnt;
	}

	// Skill Da Assassina
	int cnt1 = cSkill.SearchContiueSkill(SKILL_ALAS);
	if (cnt1 > 0 && cnt1 <= 10) {
		cnt1 = Alas_EvasionPercent[cnt1 - 1];
		TotalEvade += cnt1;
	}


	// Verifica pelo Scroll de BC 5% de evade.
	if (cSkill.SearchContiueSkillCODE(SCROLL_P_EVASION))
		TotalEvade += 15;
	// Verifica pelo Scroll de BC 5% de evade.
	if (cSkill.SearchContiueSkillCODE(SCROLL_EVASION))
		TotalEvade += 15;

	extern int Skill_AMastery_Evade;
	if (Skill_AMastery_Evade > 0)
		TotalEvade += Skill_AMastery_Evade;

	wsprintf(strBuff, "%d%%", TotalEvade);
	dsTextLineOut(CheckEditSize(sCharRectPosi[29].Rect.left, sCharRectPosi[29].Rect.right, strBuff), sCharRectPosi[29].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff));


	//Ataque Speed - Attack_Speed
	
	wsprintf(strBuff, "%d", sinCharDisplay.Attack_Speed);
	dsTextLineOut(CheckEditSize(sCharRectPosi[30].Rect.left, sCharRectPosi[30].Rect.right, strBuff), sCharRectPosi[30].Rect.top + (253 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff));


}


void cCHARSTATUS::OtherStateShow()
{
	HDC	hdc = NULL;
	char strBuff[128];
	memset(strBuff, 0, sizeof(strBuff));
	
	
	SetFontTextColor( RGB(255, 255, 255));
	wsprintf(strBuff, "°ø°Ý¼Óµµ:%d", sinCharDisplay.Attack_Speed);
	dsTextLineOut( 100, 300, strBuff, lstrlen(strBuff));

	wsprintf(strBuff, "ºí·°À²:%d", sinCharDisplay.Chance_Block);
	dsTextLineOut( 200, 300, strBuff, lstrlen(strBuff));

	wsprintf(strBuff, "Å©¸®Æ¼ÄÃ:%d", sinCharDisplay.Critical_Hit);
	dsTextLineOut( 300, 300, strBuff, lstrlen(strBuff));

	wsprintf(strBuff, "½´ÆÃ±æÀÌ:%d", sinCharDisplay.Shooting_Range);
	dsTextLineOut( 400, 300, strBuff, lstrlen(strBuff));

	

}


void cCHARSTATUS::CheckLevel()
{
	int UpLevelPoint;
	if(OldLevelTemp - 176 != OldLevel)return;
	if(sinChar->Level > OldLevel)
	{
		cInvenTory.SetItemToChar();
		UpLevelPoint = sinChar->Level - OldLevel;
		CheckCharForm();
		if((sinChar->Level % 2) == 0 && sinChar->Level >= 10)
		{
			sinSkill.SkillPoint++;
		}
		if((sinChar->Level % 2) == 0 && sinChar->Level >= 60)
		{
			sinSkill.SkillPoint4++;
		}


		sinLevelPoint = sinChar->Level - OldLevel;

		if((sinQuest_levelLog & QUESTBIT_LEVEL_80_2) == QUESTBIT_LEVEL_80_2)
		{
			if((sinQuest_levelLog & QUESTBIT_LEVEL_90_2) == QUESTBIT_LEVEL_90_2)
			{
				if(sinChar->Level >= 90)
				{
					sinChar->StatePoint += 3;
				}
			}
			if(sinChar->Level >= 80)
			{
				sinChar->StatePoint += 2;
			}
		}
		sinChar->StatePoint += sinLevelPoint * 5;
		OldLevel = sinChar->Level;
		OldLevelTemp = OldLevel + 176;
		ReformCharForm();
		sinSetLife(sinChar->Life[1]);
		sinSetMana(sinChar->Mana[1]);
		sinSetStamina(sinChar->Stamina[1]);
		cInvenTory.CheckDamage();


		if(cHelpPet.PetKind && cHelpPet.PetShow)
		{
			cHelpPet.LevelFlag = 1;
			switch(sinChar->Level)
			{
			case 2:
				cHelpPet.PetMessageHelp("*Level_Message2-1");
				cHelpPet.PetMessageHelp("*Level_Message2-2");
				break;
			case 3:
				cHelpPet.PetMessageHelp("*Level_Message3");
				break;
			case 4:
				cHelpPet.PetMessageHelp("*Level_Message4");
				break;
			case 5:
				cHelpPet.PetMessageHelp("*Level_Message5");
				break;
			case 6:
				cHelpPet.PetMessageHelp("*Level_Message6-1");
				cHelpPet.PetMessageHelp("*Level_Message6-2");
				break;
			case 7:
				cHelpPet.PetMessageHelp("*Level_Message7");
				break;
			case 8:
				cHelpPet.PetMessageHelp("*Level_Message8");
				break;
			case 9:
				cHelpPet.PetMessageHelp("*Level_Message9-1");
				cHelpPet.PetMessageHelp("*Level_Message9-2");
				break;
			case 10:

				cHelpPet.PetMessageHelp("*Level_Message10-1");
				cHelpPet.PetMessageHelp("*Level_Message10-2");
				break;
			}

		}

		ResetEnergyGraph(3);


		void InitHelp();
		InitHelp();



	}
}


void cCHARSTATUS::BackUpsinCharState(smCHAR *pChar)
{
}

int cCHARSTATUS::sinGetNowExp()
{
	INT64 sinExp64 = 0;
	int sinExp = 0;

	sinExp64 = GetXorExp64(sinChar);

	if (sinChar->Level > 76)
	{
		sinExp = (int)(sinExp64 / 1000000);

	}
	else
	{
		sinExp = (int)(sinExp64);
	}

	return sinExp;
}


int cCHARSTATUS::sinGetNextExp()
{
	int sinExp = 0;

	if (sinChar->Level > 76)
	{
		sinExp = (int)((GetNextExp(sinChar->Level) / 1000000));

	}
	else
	{
		sinExp = (int)GetNextExp(sinChar->Level);
	}

	return sinExp;
}


int cCHARSTATUS::InitCharStatus(int kind)
{
	int Total = 0;
	int Total2 = 0;

	switch(kind)
	{
	case 0:
		if(sinChar->wVersion[1] == 1)
		{
			sinSkillPontInitButtonFlag = 0;
			cMessageBox.ShowMessage(MESSAGE_ALREADY_INITSTATE);
			return FALSE;
		}
		sinSkillPontInitButtonFlag = 1;
		sinInitPointPassFlag = 1;
		break;
	}
	cMessageBox.ShowMessage(MESSAGE_GYUNGFUM_OK);
	Total = sinChar->Strength + sinChar->Spirit + sinChar->Talent + sinChar->Dexterity + sinChar->Health + sinChar->StatePoint;

	for(int i = 0; i < 5; i++)
	{
		if(sinChar->JOB_CODE == TempNewCharacterInit[i][0])
		{
			sinChar->Strength = TempNewCharacterInit[i][1];
			sinChar->Spirit = TempNewCharacterInit[i][2];
			sinChar->Talent = TempNewCharacterInit[i][3];
			sinChar->Dexterity = TempNewCharacterInit[i][4];
			sinChar->Health = TempNewCharacterInit[i][5];
			Total2 = sinChar->Strength + sinChar->Spirit + sinChar->Talent + sinChar->Dexterity + sinChar->Health;
			sinChar->StatePoint = Total - Total2;
			sinChar->wVersion[1] = 1;
			ReformCharForm();
			cInvenTory.SetItemToChar();
			return TRUE;
		}
		if(sinChar->JOB_CODE == MorNewCharacterInit[i][0])
		{
			sinChar->Strength = MorNewCharacterInit[i][1];
			sinChar->Spirit = MorNewCharacterInit[i][2];
			sinChar->Talent = MorNewCharacterInit[i][3];
			sinChar->Dexterity = MorNewCharacterInit[i][4];
			sinChar->Health = MorNewCharacterInit[i][5];
			Total2 = sinChar->Strength + sinChar->Spirit + sinChar->Talent + sinChar->Dexterity + sinChar->Health;
			sinChar->StatePoint = Total - Total2;
			sinChar->wVersion[1] = 1;
			ReformCharForm();
			cInvenTory.SetItemToChar();
			return TRUE;
		}

	}

	return TRUE;
}


int cCHARSTATUS::CheckChageStateDisplay()
{

	memset(&sDisplayStateShow, 0, sizeof(sDISPLAYSTATE));
	for(int i = 0; i < 10; i++)
	{
		if(sDisplayState[i].MaxTime)
		{
			sDisplayStateShow.Absorb += sDisplayState[i].Absorb;
			sDisplayStateShow.Attack_Rate += sDisplayState[i].Attack_Rate;
			sDisplayStateShow.Damage[0] += sDisplayState[i].Damage[0];
			sDisplayStateShow.Damage[1] += sDisplayState[i].Damage[1];
			if(sDisplayState[i].PercentDamage[0])
				sDisplayStateShow.Damage[0] += (short)(sinChar->Attack_Damage[0] * sDisplayState[i].PercentDamage[0]) / 100;
			if(sDisplayState[i].PercentDamage[1])
				sDisplayStateShow.Damage[1] += (short)(sinChar->Attack_Damage[1] * sDisplayState[i].PercentDamage[1]) / 100;

			sDisplayStateShow.Defense += sDisplayState[i].Defense;

			if(sDisplayStateShow.Absorb < 0)
				SkillTextColor[SIN2_ABSORB] = SIN_TEXT_COLOR_RED;
			if(sDisplayStateShow.Defense < 0)
				SkillTextColor[SIN2_DEFENSE] = SIN_TEXT_COLOR_RED;
			if(sDisplayStateShow.Damage[0] < 0 || sDisplayStateShow.Damage[1])
				SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_RED;


			if(sDisplayState[i].MaxTime <= dwPlayTime)
			{
				memset(&sDisplayState[i], 0, sizeof(sDISPLAYSTATE));
				cInvenTory.SetItemToChar();
			}

		}

	}

	if(sinQuest_Level90_2.CODE && sinQuest_Level90_2.State >= 2)
	{
		SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_RED;

	}
	return TRUE;
}


int cCHARSTATUS::UseGravityScrool()
{
	float	fstrength, fhealth, ftalent, fLevel, fSpirit;


	fstrength = (float)sinChar->Strength;
	fhealth = (float)sinChar->Health;
	ftalent = (float)sinChar->Talent;
	fSpirit = (float)sinChar->Spirit;
	fLevel = (float)sinChar->Level;


	if(sinChar->GravityScroolCheck[0] == 0)
	{
		sinChar->Weight[1] = (short)(((fstrength * 2) + (fhealth*1.5) + fLevel * 3) + 60);

	}

	if(sinChar->GravityScroolCheck[0] > 0)
	{
		sinChar->Weight[1] = (short)(((fstrength * 2) + (fhealth*1.5) + fLevel * 3) + 60) + (sinChar->GravityScroolCheck[0]) * 50;

	}



	sinChar->wVersion[1] = 1;
	ReformCharForm();
	cInvenTory.SetItemToChar();

	return TRUE;
}


int cCHARSTATUS::InitCharStatus_Attribute(int kind)
{
	int Total, Total2;
	int Brood_code = 0;
	int Job_Num = 0;

	cMessageBox.ShowMessage(MESSAGE_GYUNGFUM_OK);
	Total = sinChar->Strength + sinChar->Spirit + sinChar->Talent + sinChar->Dexterity + sinChar->Health + sinChar->StatePoint;

	for(int i = 0; i < 5; i++)
	{
		if(sinChar->JOB_CODE == TempNewCharacterInit[i][0])
		{
			Brood_code = BROOD_CODE_TEMPSKRON;
			Job_Num = i;
		}
		if(sinChar->JOB_CODE == MorNewCharacterInit[i][0])
		{
			Brood_code = BROOD_CODE_MORAYION;
			Job_Num = i;
		}
	}

	if(Brood_code == BROOD_CODE_TEMPSKRON)
	{
		switch(kind)
		{
		case 1:
			sinChar->Strength = TempNewCharacterInit[Job_Num][1];
			break;
		case 2:
			sinChar->Spirit = TempNewCharacterInit[Job_Num][2];
			break;
		case 3:
			sinChar->Talent = TempNewCharacterInit[Job_Num][3];
			break;
		case 4:
			sinChar->Dexterity = TempNewCharacterInit[Job_Num][4];
			break;
		case 5:
			sinChar->Health = TempNewCharacterInit[Job_Num][5];
			break;
		}
	}
	else
	{
		switch(kind)
		{
		case 1:
			sinChar->Strength = MorNewCharacterInit[Job_Num][1];
			break;
		case 2:
			sinChar->Spirit = MorNewCharacterInit[Job_Num][2];
			break;
		case 3:
			sinChar->Talent = MorNewCharacterInit[Job_Num][3];
			break;
		case 4:
			sinChar->Dexterity = MorNewCharacterInit[Job_Num][4];
			break;
		case 5:
			sinChar->Health = MorNewCharacterInit[Job_Num][5];
			break;
		}
	}

	sinPlaySound(SIN_SOUND_EAT_POTION2);
	StartEffect(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, EFFECT_AGING);

	Total2 = sinChar->Strength + sinChar->Spirit + sinChar->Talent + sinChar->Dexterity + sinChar->Health;
	sinChar->StatePoint = Total - Total2;
	sinChar->wVersion[1] = 1;
	ReformCharForm();
	cInvenTory.SetItemToChar();

	return TRUE;

}
