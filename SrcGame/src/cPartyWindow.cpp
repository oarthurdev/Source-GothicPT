#include "sinbaram/sinLinkHeader.h"
#include "cPartyWindow.h"

cPARTY cParty;

bool isMousePos(int x, int y, int w, int h)
{
	if (pRealCursorPos.x > x && pRealCursorPos.x < x + w && pRealCursorPos.y > y && pRealCursorPos.y < y + h)
		return true;

	return false;
}

void cPARTY::LoadImages()
{
	MemberCount = 0;
	bExpand = true;
	MenuFlag = 0;

	mClass[0][0] = CreateTextureMaterial("game\\GUI\\Party\\Class\\Fighter.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mClass[0][1] = CreateTextureMaterial("game\\GUI\\Party\\Class\\Mechanician.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mClass[0][2] = CreateTextureMaterial("game\\GUI\\Party\\Class\\Archer.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mClass[0][3] = CreateTextureMaterial("game\\GUI\\Party\\Class\\Pikeman.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mClass[0][4] = CreateTextureMaterial("game\\GUI\\Party\\Class\\Atalanta.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mClass[0][5] = CreateTextureMaterial("game\\GUI\\Party\\Class\\Knight.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mClass[0][6] = CreateTextureMaterial("game\\GUI\\Party\\Class\\Magician.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mClass[0][7] = CreateTextureMaterial("game\\GUI\\Party\\Class\\Priestess.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mClass[0][8] = CreateTextureMaterial("game\\GUI\\Party\\Class\\Assassin.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mClass[0][9] = CreateTextureMaterial("game\\GUI\\Party\\Class\\Shaman.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	mClass[1][0] = CreateTextureMaterial("game\\GUI\\Party\\Class\\Fighter_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mClass[1][1] = CreateTextureMaterial("game\\GUI\\Party\\Class\\Mechanician_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mClass[1][2] = CreateTextureMaterial("game\\GUI\\Party\\Class\\Archer_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mClass[1][3] = CreateTextureMaterial("game\\GUI\\Party\\Class\\Pikeman_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mClass[1][4] = CreateTextureMaterial("game\\GUI\\Party\\Class\\Atalanta_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mClass[1][5] = CreateTextureMaterial("game\\GUI\\Party\\Class\\Knight_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mClass[1][6] = CreateTextureMaterial("game\\GUI\\Party\\Class\\Magician_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mClass[1][7] = CreateTextureMaterial("game\\GUI\\Party\\Class\\Priestess_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mClass[1][8] = CreateTextureMaterial("game\\GUI\\Party\\Class\\Assassin_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mClass[1][9] = CreateTextureMaterial("game\\GUI\\Party\\Class\\Shaman_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	mMembers[0] = CreateTextureMaterial("game\\GUI\\Party\\Members\\member1.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mMembers[1] = CreateTextureMaterial("game\\GUI\\Party\\Members\\member2.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mMembers[2] = CreateTextureMaterial("game\\GUI\\Party\\Members\\member3.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mMembers[3] = CreateTextureMaterial("game\\GUI\\Party\\Members\\member4.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mMembers[4] = CreateTextureMaterial("game\\GUI\\Party\\Members\\member5.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mMembers[5] = CreateTextureMaterial("game\\GUI\\Party\\Members\\member6.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	mDefault[DEFAULT::BACKGROUND] = CreateTextureMaterial("game\\GUI\\Party\\background.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mDefault[DEFAULT::EXPAND] = CreateTextureMaterial("game\\GUI\\Party\\expand.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mDefault[DEFAULT::EXPAND_] = CreateTextureMaterial("game\\GUI\\Party\\expand_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mDefault[DEFAULT::LEADER] = CreateTextureMaterial("game\\GUI\\Party\\leader.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mDefault[DEFAULT::HUNTMODE] = CreateTextureMaterial("game\\GUI\\Party\\huntmode.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mDefault[DEFAULT::HUNTMODE_] = CreateTextureMaterial("game\\GUI\\Party\\huntmode_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mDefault[DEFAULT::EXPMODE] = CreateTextureMaterial("game\\GUI\\Party\\expmode.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mDefault[DEFAULT::EXPMODE_] = CreateTextureMaterial("game\\GUI\\Party\\expmode_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	LifeBar = CreateTextureMaterial("game\\GUI\\Party\\lifebar.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	ManaBar = CreateTextureMaterial("game\\GUI\\Party\\manabar.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	mMenu[MENU::TOP] = CreateTextureMaterial("game\\GUI\\Party\\Menu\\top.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mMenu[MENU::MID] = CreateTextureMaterial("game\\GUI\\Party\\Menu\\mid.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mMenu[MENU::BOT] = CreateTextureMaterial("game\\GUI\\Party\\Menu\\bot.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	mMenu[MENU::MAIN] = CreateTextureMaterial("game\\GUI\\Party\\Menu\\main.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	iPartyMode = 1;
}

void cPARTY::Draw()
{
	if (!MemberCount)
		return;

	BaseY = ((WinSizeY - 90) - (50 * MemberCount)) / 2;

	dsDrawTexImage(mDefault[bExpand ? DEFAULT::EXPAND : DEFAULT::EXPAND_], 5, BaseY - 30, 18, 14, 255);
	dsDrawTexImage(mDefault[iPartyMode == 2 ? DEFAULT::HUNTMODE : DEFAULT::EXPMODE], 22, BaseY - 30, 15, 15, 255);

	if (!bExpand)
		return;

	if (isMousePos(25, BaseY - 43, 54, 26) || iPartyMode == 1)
		dsDrawTexImage(mDefault[DEFAULT::EXPMODE_], 25, BaseY - 43, 54, 26, 255);
	else
		dsDrawTexImage(mDefault[DEFAULT::EXPMODE], 25, BaseY - 43, 54, 26, 255);
	
	if (isMousePos(85, BaseY - 43, 54, 26) || iPartyMode == 2)
		dsDrawTexImage(mDefault[DEFAULT::HUNTMODE_], 85, BaseY - 43, 54, 26, 255);
	else
		dsDrawTexImage(mDefault[DEFAULT::HUNTMODE], 85, BaseY - 43, 54, 26, 255);

	for (int i = 0; i < MemberCount; i++)
	{
		int iY = BaseY + (i * 50);

		dsDrawTexImage(mDefault[DEFAULT::BACKGROUND], 5, iY, 173, 49, 255);

		if (i == 0)
			dsDrawTexImage(mDefault[DEFAULT::LEADER], 18, iY - 10, 21, 14, 255);

		dsDrawTexImage(mMembers[i], 39, iY + 40, 9, 9, 255);

		dsDrawTexImage(mClass[Members[i].Life[0] > 0 ? 0 : 1][Members[i].JobCode - 1], 11, iY + 8, 34, 34, 255);

		dsDrawTexImage(LifeBar, 51, iY + 26, (Members[i].Life[0] * 119) / Members[i].Life[1], 6, 255);

		dsDrawTexImage(ManaBar, 47, iY + 37, (Members[i].Mana[0] * 123) / Members[i].Mana[1], 5, 255);

		char buff[32];
		wsprintf(buff, "%d", Members[i].Level);

		SetTextColor(0, RGB(255, 238, 100));
		dsTextLineOut(51, iY + 7, buff, lstrlen(buff));
		SetTextColor(0, RGB(255, 255, 255));
		dsTextLineOut(75, iY + 5, Members[i].szName, lstrlen(Members[i].szName));

		if (MenuFlag && MenuFlag == i + 1)
		{
			if (menu.vOption.size() == 1)
			{
				dsDrawTexImage(mMenu[MENU::MAIN], menu.iX, menu.iY, 95, 30, 255);

				if (menu.vOption.size())
				{
					for (auto& opt : menu.vOption)
					{
						if (opt)
						{
							if (isMousePos(opt->iX, opt->iY, opt->w, opt->h))
								SetTextColor(0, opt->hoverColor);
							else
								SetTextColor(0, opt->textColor);

							dsTextLineOut(opt->iX, opt->iY + 3, opt->szText, lstrlen(opt->szText));
						}
					}
				}
			}
			else
			{
				dsDrawTexImage(mMenu[MENU::TOP], menu.iX, menu.iY, 95, 24, 255);

				for (int i = 0; i < menu.vOption.size() - 2; i++)
				{
					dsDrawTexImage(mMenu[MENU::MID], menu.iX, menu.iY + 24 + (24 * i), 95, 24, 255);
				}

				dsDrawTexImage(mMenu[MENU::BOT], menu.iX, menu.iY + 24 + (24 * (menu.vOption.size() - 2)), 95, 25, 255);

				if (menu.vOption.size())
				{
					for (auto& opt : menu.vOption)
					{
						if (opt)
						{
							if (isMousePos(opt->iX, opt->iY, opt->w, opt->h))
								SetTextColor(0, opt->hoverColor);
							else
								SetTextColor(0, opt->textColor);

							dsTextLineOut(opt->iX, opt->iY, opt->szText, lstrlen(opt->szText));
						}
					}
				}
			}


		}
	}
}

void cPARTY::AddMember(_PARTY_USER * pUser, int MemberNum)
{
	if (MemberNum > 5)
		return;

	if (MemberNum == 0)
	{
		ZeroMemory(Members, sizeof(_PARTY_USER) * 6);
		MemberCount = 0;
		if (pUser->dwObjectSerial == lpCurPlayer->dwObjectSerial)
			LeaderFlag = true;
		else
			LeaderFlag = false;
	}

	memcpy(&Members[MemberNum], pUser, sizeof(_PARTY_USER));

	if (MemberNum >= MemberCount)
	{
		MemberCount = MemberNum + 1;
	}
}

void cPARTY::UpdateMember(_PARTY_PLAYINFO * pUser)
{

	for (int i = 0; i < MemberCount; i++)
	{
		if (Members[i].dwObjectSerial == pUser->dwObjectSerial)
		{
			if (i == 0)
			{
				if (pUser->dwObjectSerial == lpCurPlayer->dwObjectSerial)
					LeaderFlag = true;
				else
					LeaderFlag = false;
			}

			Members[i].Life[0] = pUser->Life[0];
			Members[i].Life[1] = pUser->Life[1];
			Members[i].Mana[0] = pUser->Mana[0];
			Members[i].Mana[1] = pUser->Mana[1];
			Members[i].Level = pUser->Level;
			Members[i].x = pUser->x;
			Members[i].z = pUser->z;
			break;
		}
	}
}

bool cPARTY::LButtonDown()
{
	if (!MemberCount)
		return false;

	BaseY = ((WinSizeY - 90) - (50 * MemberCount)) / 2;

	if (isMousePos(5, BaseY - 30, 18, 14))
	{
		bExpand = !bExpand;
		return true;
	}

	if (!bExpand)
		return false;

	if (MenuFlag)
	{
		smTRANS_COMMAND smTransCommand = {};

		for (auto& opt : menu.vOption)
		{
			if (opt)
			{
				if (isMousePos(opt->iX, opt->iY, opt->w, opt->h))
				{
					smTransCommand.size = sizeof(smTRANS_COMMAND);
					smTransCommand.code = OpCode::OPCODE_PARTY_COMMAND;
					smTransCommand.WParam = Members[MenuFlag - 1].dwObjectSerial;
					smTransCommand.LParam = opt->ButtonNum;
					smTransCommand.SParam = 0;

					smWsockServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
				}

				delete opt;
			}
		}

		menu.vOption.clear();
		MenuFlag = 0;
	}
	
	//BOTAOS ONDE CLICA E MUDA PARTY OU HUNT
	if (isMousePos(25, BaseY - 43, 54, 26) && iPartyMode != 1)
	{
		smTRANS_COMMAND smTransCommand = {};

		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = OpCode::OPCODE_PARTY_COMMAND;
		smTransCommand.WParam = lpCurPlayer->dwObjectSerial;
		smTransCommand.LParam = 4;
		smTransCommand.SParam = 1;

		smWsockServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
		return true;
	}

	if (isMousePos(85, BaseY - 43, 54, 26) && iPartyMode != 2)
	{
		smTRANS_COMMAND smTransCommand = {};

		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = OpCode::OPCODE_PARTY_COMMAND;
		smTransCommand.WParam = lpCurPlayer->dwObjectSerial;
		smTransCommand.LParam = 4;
		smTransCommand.SParam = 2;

		smWsockServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
		return true;
	}

	return false;
}

bool cPARTY::RButtonDown()
{
	if (!MemberCount)
		return false;

	BaseY = ((WinSizeY - 90) - (50 * MemberCount)) / 2;

	for (int i = 0; i < MemberCount; i++)
	{
		if (isMousePos(5, BaseY + (i * 50), 173, 49) && (Members[i].dwObjectSerial == lpCurPlayer->dwObjectSerial || LeaderFlag))
		{
			MenuFlag = i + 1;

			SetMenu(178, BaseY + (i * 50) + 10, i);

			if (LeaderFlag)
			{
				if (i == 0)
				{
					AddOpt("Leave", 3);
					AddOpt("Disband", 1);
				}
				else
				{
					AddOpt("Delegate", 0);
					AddOpt("Kick", 2);
				}
			}
			else
			{
				AddOpt("Leave", 3);
			}
			return true;
		}
	}
	return false;
}

void cPARTY::Clear()
{
	MemberCount = 0;
	ZeroMemory(Members, sizeof(_PARTY_USER) * 6);
	bExpand = true;
	LeaderFlag = false;
}

int cPARTY::RequestPartyPlayers(smCHAR * lpChar)
{
	if (lpChar)
	{
		lpChar->PartyFlag = FALSE;

		for (int cnt = 0; cnt < MemberCount; cnt++)
		{
			if (Members[cnt].dwObjectSerial == lpChar->dwObjectSerial)
			{
				lpChar->PartyFlag = TRUE;
				return TRUE;
			}
		}
	}
	else
	{

		for (int cnt2 = 0; cnt2 < OTHER_PLAYER_MAX; cnt2++)
		{
			if (chrOtherPlayer[cnt2].Flag && chrOtherPlayer[cnt2].dwObjectSerial)
			{
				chrOtherPlayer[cnt2].PartyFlag = FALSE;
				for (int cnt = 0; cnt < MemberCount; cnt++)
				{
					if (Members[cnt].dwObjectSerial == chrOtherPlayer[cnt2].dwObjectSerial)
					{
						chrOtherPlayer[cnt2].PartyFlag = TRUE;
						break;
					}
				}
			}
		}
	}

	return FALSE;
}

bool cPARTY::StopMotion()
{
	if (isMousePos(5, BaseY - 30, 18, 14))
		return true;

	return false;
}

void cPARTY::SetMenu(int x, int y, int memberNum)
{
	menu.iX = x;
	menu.iY = y;
	menu.MemberNum = memberNum;

	for (auto& opt : menu.vOption)
	{
		if (opt)
			delete opt;
	}

	menu.vOption.clear();
}

void cPARTY::AddOpt(char * szText, int buttonNum)
{
	sMENUOPT* opt = new sMENUOPT;

	opt->ButtonNum = buttonNum;
	lstrcpy(opt->szText, szText);

	SIZE size = {};
	GetFontTextExtentPoint( opt->szText, lstrlen(opt->szText), &size);
	opt->w = size.cx;
	opt->h = size.cy;

	opt->iX = menu.iX + 11 + ((83 - opt->w) / 2);
	opt->iY = menu.iY + (24 * menu.vOption.size()) + ((24 - opt->h) / 2);

	opt->textColor = RGB(255, 255, 255);
	opt->hoverColor = RGB(230, 180, 150);

	menu.vOption.push_back(opt);
}
