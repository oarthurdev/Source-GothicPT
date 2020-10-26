#include "sinbaram/sinLinkHeader.h"
#include "TJBOY/clanmenu/cE_CViewClanInfo.h"
#include "cTarget.h"
#include "field.h"

extern bool isMousePos(int x, int y, int w, int h);
extern int DrawClanMark_EachBox(LPDIRECT3DTEXTURE9 clanMark, int x, int y);

cTARGET cTarget;

extern POINT3D EachCameraPos;

void cTARGET::DrawTarget()
{
	int mx = MidX;
	int my = MidY;

	MidX = ((WinSizeX - 301) / 2) + 36;
	MidY = 42 + BaseY;

	int sizeBackup = WinSizeX;
	int sizeBackupy = WinSizeY;

	WinSizeX = 800;
	WinSizeY = 600;

	SetDxProjection((g_PI / 4.4f), WinSizeX, WinSizeY, 20.f, 4000.f);

	smRender.SMSHIFT_PERSPECTIVE_WIDTH = RENDCLIP_DEFAULT_SHIFT_PERSPECTIVE_WIDTH * 5;

	smRender.SMMULT_PERSPECTIVE_HEIGHT = (int)(RENDCLIP_DEFAULT_MULT_PERSPECTIVE_HEIGHT + 25.6f) * 11;

	int dist = 300 * fONE;

	d3ddev->Clear(0, 0, 2, smBackColor, 1.0f, 0);


	smCHAR_SetCameraPosi(EachCameraPos.x, EachCameraPos.y + 50, dist + EachCameraPos.z, 0, ANGLE_180, 0);

	chrEachPlayer.AttackAnger = chrEachMaster->AttackAnger;

	WORD ObjSizeBack = chrEachPlayer.smCharInfo.wPlayClass[1];
	chrEachPlayer.smCharInfo.wPlayClass[1] = 0;

	chrEachPlayer.Draw();

	chrEachPlayer.smCharInfo.wPlayClass[1] = ObjSizeBack;

	MidX = mx;
	MidY = my;

	smRender.SMSHIFT_PERSPECTIVE_WIDTH = 0;
	smRender.SMMULT_PERSPECTIVE_HEIGHT = RENDCLIP_DEFAULT_MULT_PERSPECTIVE_HEIGHT;

	WinSizeX = sizeBackup;
	WinSizeY = sizeBackupy;
	SetDxProjection((g_PI / 4.4f), WinSizeX, WinSizeY, 20.f, 4000.f);
}

void cTARGET::Init()
{
	Mat[BACKGROUND] = CreateTextureMaterial("game\\GUI\\Target\\targetoverlay.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TARGETBG] = CreateTextureMaterial("game\\GUI\\Target\\targetbackground.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TARGETCLAN] = CreateTextureMaterial("game\\GUI\\Target\\targetoverlay_Clan.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TARGETHP] = CreateTextureMaterial("game\\GUI\\Target\\targethp.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TYPEDEMON] = CreateTextureMaterial("game\\GUI\\Target\\type\\demon.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TYPEMECHANIC] = CreateTextureMaterial("game\\GUI\\Target\\type\\mechanic.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TYPEMUTANT] = CreateTextureMaterial("game\\GUI\\Target\\type\\mutant.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TYPENORMAL] = CreateTextureMaterial("game\\GUI\\Target\\type\\normal.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TYPENPC] = CreateTextureMaterial("game\\GUI\\Target\\type\\npc.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TYPEPLAYER] = CreateTextureMaterial("game\\GUI\\Target\\type\\player.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TYPEUNDEAD] = CreateTextureMaterial("game\\GUI\\Target\\type\\undead.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MORE] = CreateTextureMaterial("game\\GUI\\Target\\more.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MORE_] = CreateTextureMaterial("game\\GUI\\Target\\more_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[DROPTOP] = CreateTextureMaterial("game\\GUI\\Target\\menu\\topleft.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[DROPMID] = CreateTextureMaterial("game\\GUI\\Target\\menu\\middle.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[DROPBOT] = CreateTextureMaterial("game\\GUI\\Target\\menu\\bottom.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
}

void cTARGET::Draw(smCHAR* lpEachPlayer)
{
	if (!cInterFace.sInterFlags.MapOnFlag)
		return;

	unsigned int stage = lpCurPlayer->OnStageField >= 0 && lpCurPlayer->OnStageField < 2 ? StageField[lpCurPlayer->OnStageField]->FieldCode : 0;
	BaseX = (WinSizeX - 301) / 2;

	if (stage == 30)
		BaseY = 105;
	else
		BaseY = 3;

	if (TargetSerial != lpEachPlayer->dwObjectSerial)
	{
		if (DropDownFlag)
			OpenDropDown();

		TargetSerial = lpEachPlayer->dwObjectSerial;
	}

	dsDrawTexImage(Mat[TARGETBG], BaseX + 7, BaseY + 11, 59, 59, 255);

	DrawTarget();

	dsDrawTexImage(Mat[BACKGROUND], BaseX, BaseY, 301, 81, 255);

	float hppercent = (float)(209 * ((float)lpEachPlayer->smCharInfo.Life[0] / (float)lpEachPlayer->smCharInfo.Life[1]));
	dsDrawTexImage(Mat[TARGETHP], BaseX + 82, BaseY + 39, (int)hppercent, 12, 255);

	int type = TYPENPC;

	switch (chrEachPlayer.smCharInfo.Brood)
	{
	case smCHAR_MONSTER_MUTANT:
		type = TYPEMUTANT;
		break;

	case smCHAR_MONSTER_UNDEAD:
		type = TYPEUNDEAD;
		break;

	case smCHAR_MONSTER_DEMON:
		type = TYPEDEMON;
		break;

	case smCHAR_MONSTER_MECHANIC:
		type = TYPEMECHANIC;
		break;

	case smCHAR_MONSTER_NORMAL:
		type = TYPENORMAL;
		break;

	case smCHAR_MONSTER_USER:
		type = TYPEPLAYER;
		break;
	}

	if (chrEachPlayer.smCharInfo.State == smCHAR_STATE_NPC)
		type = TYPENPC;
	else if (chrEachPlayer.smCharInfo.State == smCHAR_STATE_USER)
		type = TYPEPLAYER;

	dsDrawTexImage(Mat[type], BaseX + 63, BaseY + 34, 16, 16, 255);

	if (type == TYPEPLAYER && EachTradeButton)
	{
		dsDrawTexImage(Mat[MORE], BaseX + 262, BaseY + 15, 26, 26, 255);
		if (isMousePos(BaseX + 262, BaseY + 15, 26, 26) || DropDownFlag)
			dsDrawTexImage(Mat[MORE_], BaseX + 262, BaseY + 15, 26, 26, 255);
	}

	if (DropDownFlag)
	{
		int count = 0;
		for (auto opt : vOptions)
		{
			if (opt.second)
			{
				if (!count)
				{
					dsDrawTexImage(Mat[DROPTOP], BaseX + 301, BaseY + 16, 95, 25, 255);
				}
				else if (count > 0 && count < vOptions.size() - 1)
				{
					dsDrawTexImage(Mat[DROPMID], BaseX + 301, BaseY + 16 + (25 * count), 95, 25, 255);
				}
				else if (count == vOptions.size() - 1)
				{
					dsDrawTexImage(Mat[DROPBOT], BaseX + 301, BaseY + 16 + (25 * count), 95, 26, 255);
				}

				count++;
			}
		}
	}

	if (chrEachPlayer.smCharInfo.ClassClan && chrEachPlayer.ClanInfoNum >= 0)
	{
		dsDrawTexImage(Mat[TARGETCLAN], BaseX + 81, BaseY - 3, 206, 22, 255);
		DrawClanMark_EachBox(ClanInfo[chrEachMaster->ClanInfoNum].hClanMark, BaseX + 99, BaseY + 2);
	}

	Text(lpEachPlayer);
}

void cTARGET::Text(smCHAR* lpEachPlayer)
{
	SIZE size = {};
	char buff[255];
	wsprintf(buff, "%s - Nv.%d", lpEachPlayer->smCharInfo.szName, lpEachPlayer->smCharInfo.Level);
	GetFontTextExtentPoint( buff, lstrlen(buff), &size);

	SetFontTextColor( RGB(255, 255, 255));
	dsTextLineOut(BaseX + (185 - (size.cx / 2)), BaseY + 21, buff, lstrlen(buff));

	ZeroMemory(buff, 255);

	size = {};
	wsprintf(buff, "%d/%d", lpEachPlayer->smCharInfo.Life[0], lpEachPlayer->smCharInfo.Life[1]);
	GetFontTextExtentPoint( buff, lstrlen(buff), &size);
	dsTextLineOut(BaseX + (185 - (size.cx / 2)), BaseY + 38, buff, lstrlen(buff));

	if (DropDownFlag)
	{
		int count = 0;
		for (auto opt : vOptions)
		{
			if (opt.second)
			{
				size = {};
				GetFontTextExtentPoint(opt.second, lstrlen(opt.second), &size);

				if (isMousePos(BaseX + 309 + ((87 - size.cx) / 2), BaseY + 16 + (count * 25) + ((25 - size.cy) / 2), size.cx, size.cy))
					SetFontTextColor( RGB(230, 180, 150));
				else
					SetFontTextColor( RGB(255, 255, 255));

				dsTextLineOut(BaseX + 309 + ((87 - size.cx) / 2), BaseY + 16 + (count * 25) + ((25 - size.cy) / 2), opt.second, lstrlen(opt.second));
				count++;
			}
		}
	}

	if (chrEachPlayer.smCharInfo.ClassClan && chrEachPlayer.ClanInfoNum >= 0)
	{
		size = {};
		GetFontTextExtentPoint( ClanInfo[chrEachMaster->ClanInfoNum].ClanInfoHeader.ClanName, lstrlen(ClanInfo[chrEachMaster->ClanInfoNum].ClanInfoHeader.ClanName), &size);

		SetFontTextColor(RGB(150, 255, 200));
		dsTextLineOut(BaseX + 184 - (size.cx / 2), BaseY + 2, ClanInfo[chrEachMaster->ClanInfoNum].ClanInfoHeader.ClanName, lstrlen(ClanInfo[chrEachMaster->ClanInfoNum].ClanInfoHeader.ClanName));
	}
}

bool cTARGET::LButtonDown()
{
	if (!cInterFace.sInterFlags.MapOnFlag)
		return false;

	bool result = false;

	if (MouseIn())
		result = true;
	else if (DropDownFlag)
	{
		OpenDropDown();
	}

	if (isMousePos(BaseX + 262, BaseY + 15, 26, 26))
	{
		OpenDropDown();
	}

	if (DropDownFlag)
	{
		int count = 0;
		for (auto opt : vOptions)
		{
			if (opt.second)
			{
				SIZE size = {};
				GetFontTextExtentPoint( opt.second, lstrlen(opt.second), &size);

				if (isMousePos(BaseX + 309 + ((87 - size.cx) / 2), BaseY + 16 + (count * 25) + ((25 - size.cy) / 2), size.cx, size.cy))
				{
					handleOption(opt.first);
					break;
				}
				count++;
			}
		}
	}

	return false;
}

bool cTARGET::MouseIn()
{
	return isMousePos(BaseX, BaseY, 301 + 95, 111);
}

bool cTARGET::StopMotion()
{
	if (isMousePos(BaseX + 262, BaseY + 15, 26, 26) || DropDownFlag)
		return true;

	return false;
}

void cTARGET::OpenDropDown()//
{
	if (DropDownFlag)
	{
		vOptions.clear();
		DropDownFlag = 0;
	}
	else
	{
		if (EachTradeButton)
		{
			vOptions.insert(std::pair<int, char*>(1, "Troca"));
			vOptions.insert(std::pair<int, char*>(2, "Grupo"));
			vOptions.insert(std::pair<int, char*>(3, "Adicionar"));
			if (EachTradeButtonMode)
				vOptions.insert(std::pair<int, char*>(4, "Clan"));

			DropDownFlag = 1;
		}
	}
}

extern void g_IsCheckClanMember(smCHAR* pChar);
extern char* mgRequestTrade;
extern char* mgRequestTrade2;

void cTARGET::handleOption(int code)
{
	char szBuff[500];

	switch (code)
	{
	case 1:
		if (GetTradeDistanceFromCode(chrEachMaster->dwObjectSerial) == TRUE)
		{

			SendRequestTrade(chrEachMaster->dwObjectSerial, 0);
			wsprintf(szBuff, mgRequestTrade, chrEachMaster->smCharInfo.szName);
		}
		else
		{
			wsprintf(szBuff, mgRequestTrade2, chrEachMaster->smCharInfo.szName);
		}

		AddChatBuff(szBuff);
		break;

	case 2:
		wsprintf(szBuff, "//party %s", chrEachMaster->smCharInfo.szName);
		SendChatMessageToServer(szBuff);
		break;

	case 3:
		InterfaceParty.latest_Insert(chrEachMaster->smCharInfo.szName);
		InterfaceParty.friend_Insert(chrEachMaster->smCharInfo.szName);

		InterfaceParty.Main_menuSet(2);
		InterfaceParty.chat_changeMENU(1);
		if (InterfaceParty.PartyPosState == PARTY_NONE)	ShowParty();
		break;

	case 4:
		g_IsCheckClanMember(chrEachMaster);
		break;
	}

	OpenDropDown();
}
