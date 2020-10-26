#include "sinbaram/sinLinkHeader.h"
#include "netplay.h"
#include "cQuestWindow.h"
#include "smLib3d/smTexture.h"
#include "drawsub.h"


extern int sinGetKeyClick(int num);
extern bool isMousePos(int x, int y, int w, int h);

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

cQUESTWINDOW cQuestWindow;

void cQUESTWINDOW::Init()
{
	pCurrentTab = 0;

	Mat[BG] = CreateTextureMaterial("game\\GUI\\Quest\\images\\background.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[CLOSE] = CreateTextureMaterial("game\\GUI\\Quest\\images\\close.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[PROGRESS_TAB] = CreateTextureMaterial("game\\GUI\\Quest\\images\\progress_tab.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[PROGRESS_TAB_] = CreateTextureMaterial("game\\GUI\\Quest\\images\\progress_tab_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[LIST_TAB] = CreateTextureMaterial("game\\GUI\\Quest\\images\\list_tab.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[LIST_TAB_] = CreateTextureMaterial("game\\GUI\\Quest\\images\\list_tab_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[SPOILER_DAILY] = CreateTextureMaterial("game\\GUI\\Quest\\images\\spoiler_daily.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[SPOILER_QUESTS] = CreateTextureMaterial("game\\GUI\\Quest\\images\\spoiler_quests.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[SPOILER_PROGRESS] = CreateTextureMaterial("game\\GUI\\Quest\\images\\spoiler_progress.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[SPOILER_FINALIZED] = CreateTextureMaterial("game\\GUI\\Quest\\images\\spoiler_finalized.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[SPOILER_OPEN] = CreateTextureMaterial("game\\GUI\\Quest\\images\\spoiler_open.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[SPOILER_CLOSE] = CreateTextureMaterial("game\\GUI\\Quest\\images\\spoiler_close.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[ACCEPT_QUEST] = CreateTextureMaterial("game\\GUI\\Quest\\images\\accept.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[ACCEPT_QUEST_] = CreateTextureMaterial("game\\GUI\\Quest\\images\\accept_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[CANCEL_QUEST] = CreateTextureMaterial("game\\GUI\\Quest\\images\\cancel.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[CANCEL_QUEST_] = CreateTextureMaterial("game\\GUI\\Quest\\images\\cancel_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[GET_REWARD] = CreateTextureMaterial("game\\GUI\\Quest\\images\\get_reward.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[GET_REWARD_] = CreateTextureMaterial("game\\GUI\\Quest\\images\\get_reward_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
}

void cQUESTWINDOW::AddObject(int ID, int Mat, int Mat_, int x, int y, int w, int h, int Opacity)
{
	sOBJECT* object = new sOBJECT;

	if (object)
	{
		object->ID = ID;
		object->Mat = Mat;
		object->Mat_ = Mat_;
		object->x = x;
		object->y = y;
		object->w = w;
		object->h = h;
		object->Opacity = Opacity;

		vObjects.push_back(object);
	}
}

sTAB* cQUESTWINDOW::AddTab(int ID, int Mat, int Mat_, int x, int y, int w, int h, bool Selected)
{
	sTAB* tab = new sTAB;

	if (tab)
	{
		tab->ID = ID;
		tab->Mat[0] = Mat;
		tab->Mat[1] = Mat_;
		tab->x = x;
		tab->y = y;
		tab->w = w;
		tab->h = h;
		tab->Selected = Selected;

		vTabs.push_back(tab);
		return tab;
	}

	return nullptr;
}

void cQUESTWINDOW::AddSpoiler(sTAB* pTab, int ID, int Mat)
{
	if (!pTab)
		return;

	sSPOILER* spoiler = new sSPOILER;

	if (spoiler)
	{
		spoiler->ID = ID;
		spoiler->Mat = Mat;
		spoiler->State = false;
		spoiler->pQuestWindow = this;

		pTab->vSpoilers.push_back(spoiler);

		smTRANS_COMMAND smTransCommand = {};

		smTransCommand.code = OpCode::OPCODE_SPOILER_INFO;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = ID;

		if (smWsockServer)
			smWsockServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
	}
}

void cQUESTWINDOW::SwitchSpoiler(sSPOILER* pSpoiler)
{
	if (!pCurrentTab)
		return;

	if (!pSpoiler || !pSpoiler->State)
	{
		for (auto Spoiler : pCurrentTab->vSpoilers)
		{
			if (Spoiler)
			{
				Spoiler->State = false;
				Spoiler->SetQuest(0);
			}
		}
	}

	if (!pSpoiler)
	{
		pSelectedSpoiler = 0;
		ScrollList = 0;
		return;
	}

	pSpoiler->State = !pSpoiler->State;

	if (pSpoiler->State)
		pSelectedSpoiler = pSpoiler;
	else
		pSelectedSpoiler = 0;

	ScrollList = 0;
}

sSPOILER* cQUESTWINDOW::GetSpoiler(int ID)
{
	for (auto& Tab : vTabs)
	{
		if (Tab)
		{
			for (auto pSpoiler : Tab->vSpoilers)
			{
				if (pSpoiler && pSpoiler->ID == ID)
					return pSpoiler;
			}
		}
	}
	return nullptr;
}

void cQUESTWINDOW::handlePacket(smTRANS_QUEST_INFO* pTransQuestInfo)
{
	sSPOILER* pSpoiler = GetSpoiler(pTransQuestInfo->SpoilerNum);

	if (!pSpoiler)
		return;

	if (pSpoiler->ResetQuests || pTransQuestInfo->QuestCount < 0)
	{
		pSpoiler->SetQuest(0);

		for (auto quest : pSpoiler->vQuests)
			if (quest)
				delete quest;

		pSpoiler->vQuests.clear();
		pSpoiler->ResetQuests = false;

		if (pTransQuestInfo->QuestCount < 0)
			return;
	}

	for (int i = 0; i < pTransQuestInfo->QuestCount; i++)
	{
		pSpoiler->AddQuest(pTransQuestInfo->QuestInfo[i].QuestID, pTransQuestInfo->QuestInfo[i].QuestKind, pTransQuestInfo->QuestInfo[i].QuestName, pTransQuestInfo->QuestInfo[i].QuestActive);
	}
}

void cQUESTWINDOW::handlePacket(smTRANS_QUEST_FULL* pTransQuestInfo)
{
	sQUEST* pQuest = pSelectedSpoiler->pSelectedQuest;

	if (!pQuest)
		return;

	memcpy(&pQuest->QuestInfo, &pTransQuestInfo->QuestName, sizeof(sFULL_INFO));
}

void cQUESTWINDOW::SelectTab(int TabID)
{
	if (pCurrentTab && pCurrentTab->ID == TabID)
		return;

	SwitchSpoiler(0);

	for (auto tab : vTabs)
	{
		if (tab)
		{
			if (tab->ID != TabID)
				tab->Selected = false;
			else
			{
				tab->Selected = true;
				pCurrentTab = tab;
			}
		}
	}

	ScrollList = 0;
}

void cQUESTWINDOW::Open()
{
	OpenFlag = true;

	// Objects
	AddObject(CLOSE, Mat[CLOSE], Mat[CLOSE], 559, 13, 18, 18, 200);
	AddObject(ACCEPT_QUEST, Mat[ACCEPT_QUEST], Mat[ACCEPT_QUEST], 468, 412, 104, 32, 200);
	AddObject(CANCEL_QUEST, Mat[CANCEL_QUEST], Mat[CANCEL_QUEST], 468, 412, 104, 32, 200);
	AddObject(GET_REWARD, Mat[GET_REWARD], Mat[GET_REWARD], 468, 412, 104, 32, 200);

	// Tabs
	sTAB* pProgress = AddTab(PROGRESS_TAB, Mat[PROGRESS_TAB], Mat[PROGRESS_TAB_], 19, 80, 121, 30, false);
	sTAB* pList = AddTab(LIST_TAB, Mat[LIST_TAB], Mat[LIST_TAB_], 140, 80, 121, 30, false);
	SelectTab(LIST_TAB);

	// Spoilers
	if (pList)
	{
		AddSpoiler(pList, SPOILER_DAILY, Mat[SPOILER_DAILY]);
		AddSpoiler(pList, SPOILER_QUESTS, Mat[SPOILER_QUESTS]);
	}

	if (pProgress)
	{
		AddSpoiler(pProgress, SPOILER_PROGRESS, Mat[SPOILER_PROGRESS]);
		AddSpoiler(pProgress, SPOILER_FINALIZED, Mat[SPOILER_FINALIZED]);
	}

	pSelectedSpoiler = 0;
}

void cQUESTWINDOW::Close()
{
	OpenFlag = false;

	for (auto object : vObjects)
		if (object)
			delete object;

	vObjects.clear();

	for (auto tab : vTabs)
		if (tab)
		{
			for (auto spoiler : tab->vSpoilers)
			{
				if (spoiler)
				{
					for (auto quest : spoiler->vQuests)
						if (quest)
							delete quest;

					delete spoiler;
				}
			}

			delete tab;
		}

	vTabs.clear();

	pCurrentTab = 0;
}

int totalY = 0;

void cQUESTWINDOW::Draw()
{
	if (!OpenFlag)
		return;

	BaseX = (WinSizeX - 586) / 2;
	BaseY = (WinSizeY - 445) / 2;

	dsDrawTexImage(Mat[BG], BaseX, BaseY, 586, 445, 255);

	if (vObjects.size())
	{
		for (auto object : vObjects)
		{
			if (object)
			{
				if (object->ID == ACCEPT_QUEST)
				{
					if (!pSelectedSpoiler || pSelectedSpoiler->ID == SPOILER_PROGRESS || pSelectedSpoiler->ID == SPOILER_FINALIZED || !pSelectedSpoiler->pSelectedQuest || !pSelectedSpoiler->pSelectedQuest->Active)
						continue;
				}
				else if (object->ID == CANCEL_QUEST)
				{
					if (!pSelectedSpoiler || pSelectedSpoiler->ID != SPOILER_PROGRESS || !pSelectedSpoiler->pSelectedQuest || pSelectedSpoiler->pSelectedQuest->Complete)
						continue;
				}
				else if (object->ID == GET_REWARD)
				{
					if (!pSelectedSpoiler || pSelectedSpoiler->ID != SPOILER_PROGRESS || !pSelectedSpoiler->pSelectedQuest || !pSelectedSpoiler->pSelectedQuest->Complete)
						continue;
				}

				if (isMousePos(BaseX + object->x, BaseY + object->y, object->w, object->h))
					dsDrawTexImage(object->Mat_ ? object->Mat_ : object->Mat, BaseX + object->x, BaseY + object->y, object->w, object->h, 255);
				else
					dsDrawTexImage(object->Mat, BaseX + object->x, BaseY + object->y, object->w, object->h, object->Opacity);
			}
		}
	}

	if (vTabs.size())
	{
		for (auto tab : vTabs)
		{
			if (tab)
			{
				if (tab->Selected)
					dsDrawTexImage(tab->Mat[1], BaseX + tab->x, BaseY + tab->y, tab->w, tab->h, 255);
				else
					dsDrawTexImage(tab->Mat[0], BaseX + tab->x, BaseY + tab->y, tab->w, tab->h, 255);
			}
		}

		if (pCurrentTab)
		{
			int iX = BaseX + 33;
			int iY = BaseY + 130 + ScrollList;
			int iTopLimit = BaseY + 120;
			int iBotLimit = BaseY + 423;

			for (auto pSpoiler : pCurrentTab->vSpoilers)
			{
				if (pSpoiler)
				{
					if (iY < iTopLimit && (iTopLimit - iY) < 21)
					{
						dsDrawTexImage(pSpoiler->Mat, iX, iTopLimit > iY ? iTopLimit : iY, 215, 21 - (iTopLimit > iY ? iTopLimit - iY : 0), 215, 21, 0, iTopLimit > iY ? iTopLimit - iY : 0, 215, 21, 255);
						iY += 4;

						if (iY > iTopLimit || (iTopLimit - iY) < 11)
							dsDrawTexImage(Mat[pSpoiler->State ? SPOILER_OPEN : SPOILER_CLOSE], iX + 13, (iTopLimit > iY ? iTopLimit : iY), 13, 11 - (iTopLimit > iY ? iTopLimit - iY : 0), 13, 11, 0, iTopLimit > iY ? iTopLimit - iY : 0, 13, 11, 255);
					}
					else if (iY >= iTopLimit && iY < iBotLimit - 21)
					{
						dsDrawTexImage(pSpoiler->Mat, iX, iY, 215, 21, 255);
						iY += 4;

						dsDrawTexImage(Mat[pSpoiler->State ? SPOILER_OPEN : SPOILER_CLOSE], iX + 13, iY, 13, 11, 255);
					}
					else if (iY > iTopLimit && iY > iBotLimit - 21 && iY < iBotLimit)
					{
						dsDrawTexImage(pSpoiler->Mat, iX, iY, 215, 21 - (iY - (iBotLimit - 21)), 215, 21, 0, 0, 215, 21 - (iY - (iBotLimit - 21)), 255);
						iY += 4;

						if (iY > iBotLimit - 11 && iY < iBotLimit)
							dsDrawTexImage(Mat[pSpoiler->State ? SPOILER_OPEN : SPOILER_CLOSE], iX + 14, iY, 13, 11 - (iY - (iBotLimit - 11)), 13, 11, 0, 0, 13, 11 - (iY - (iBotLimit - 11)), 255);
						else if (iY < iBotLimit)
							dsDrawTexImage(Mat[pSpoiler->State ? SPOILER_OPEN : SPOILER_CLOSE], iX + 13, iY, 13, 11, 255);
					}
					else
						iY += 4;

					iY += 19;

					if (pSpoiler->State && pSpoiler->vQuests.size())
					{
						for (auto pQuest : pSpoiler->vQuests)
						{
							if (pQuest)
							{
								if (isMousePos(iX + 10, iY, 205, 20) || pQuest->Selected)
									SetTextColor(0, RGB(255, 100, 45));
								else if (pQuest->Active)
									SetTextColor(0, RGB(240, 240, 240));
								else
									SetTextColor(0, RGB(150, 150, 150));

								if (iY > iTopLimit - 5 && iY < iBotLimit - 19)
									dsTextLineOut(iX + 10, iY + 1, pQuest->szTitle, lstrlen(pQuest->szTitle));

								iY += 20;
							}
						}

						pSpoiler->DrawQuest(BaseX, BaseY);
					}
				}
			}
			totalY = iY;
		}
	}
}

void cQUESTWINDOW::KeyDown()
{
	if (sinGetKeyClick('L'))
	{
		if (OpenFlag)
			Close();
		else
			Open();
	}

}

void cQUESTWINDOW::LButtonDown()
{
	if (!OpenFlag)
		return;

	for (auto object : vObjects)
	{
		if (object)
		{
			if (object->ID == ACCEPT_QUEST)
			{
				if (!pSelectedSpoiler || pSelectedSpoiler->ID == SPOILER_PROGRESS || pSelectedSpoiler->ID == SPOILER_FINALIZED || !pSelectedSpoiler->pSelectedQuest || !pSelectedSpoiler->pSelectedQuest->Active)
					continue;
			}
			else if (object->ID == CANCEL_QUEST)
			{
				if (!pSelectedSpoiler || pSelectedSpoiler->ID != SPOILER_PROGRESS || !pSelectedSpoiler->pSelectedQuest || pSelectedSpoiler->pSelectedQuest->Complete)
					continue;
			}
			else if (object->ID == GET_REWARD)
			{
				if (!pSelectedSpoiler || pSelectedSpoiler->ID != SPOILER_PROGRESS || !pSelectedSpoiler->pSelectedQuest || !pSelectedSpoiler->pSelectedQuest->Complete)
					continue;
			}

			if (isMousePos(BaseX + object->x, BaseY + object->y, object->w, object->h))
			{
				switch (object->ID)
				{
				case CLOSE:
					Close();
					break;
				case ACCEPT_QUEST:
					pSelectedSpoiler->StartQuest();
					break;
				case CANCEL_QUEST:
					pSelectedSpoiler->CancelQuest();
					break;
				case GET_REWARD:
					pSelectedSpoiler->GetReward();
					break;
				}
				break;
			}
		}
	}

	for (auto tab : vTabs)
	{
		if (tab)
		{
			if (isMousePos(BaseX + tab->x, BaseY + tab->y, tab->w, tab->h))
			{
				switch (tab->ID)
				{
				case PROGRESS_TAB:
				case LIST_TAB:
					SelectTab(tab->ID);
					break;
				}
				break;
			}
		}
	}

	if (pCurrentTab)
	{
		int iX = BaseX + 33;
		int iY = BaseY + 130 + ScrollList;

		for (auto pSpoiler : pCurrentTab->vSpoilers)
		{
			if (pSpoiler)
			{
				if (isMousePos(iX, iY, 215, 20))
				{
					SwitchSpoiler(pSpoiler);
					break;
				}
				iY += 24;

				if (pSpoiler->State)
				{
					for (auto& quest : pSpoiler->vQuests)
					{
						if (quest && !quest->Selected && isMousePos(iX + 10, iY, 205, 20))
						{
							pSpoiler->SetQuest(quest);
						}
						iY += 20;
					}
				}

				int iBotLimit = BaseY + 410;

				if (iY > iBotLimit)
					break;
			}
		}
	}
}

void cQUESTWINDOW::MouseWheel(short zDelta)
{
	if (!OpenFlag)
		return;

	if (zDelta >= 0)
	{
		if (ScrollList < 0)
			ScrollList += 5;
	}
	else
	{
		int iBotLimit = BaseY + 410;

		if (totalY > iBotLimit)
			ScrollList -= 5;
	}
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

extern int AddChatBuff(char* szMsg);

void sSPOILER::AddQuest(int ID, int Kind, char* szTitle, bool Active)
{
	sQUEST* quest = new sQUEST;

	if (quest)
	{
		ZeroMemory(quest, sizeof(sQUEST));

		quest->ID = ID;
		quest->Kind = Kind;
		lstrcpy(quest->szTitle, szTitle);
		quest->Selected = false;
		quest->Active = Active;


		vQuests.push_back(quest);
	}
}

bool sSPOILER::SetQuest(sQUEST* pQuest)
{
	for (auto& quest : vQuests)
	{
		if (quest && quest->Selected)
			quest->Selected = false;
	}

	pSelectedQuest = pQuest;

	if (!pQuest)
		return false;

	pQuest->Selected = true;

	smTRANS_COMMAND QuestCommand = {};

	QuestCommand.code = OpCode::OPCODE_QUEST_INFO;
	QuestCommand.size = sizeof(smTRANS_COMMAND);
	QuestCommand.WParam = pQuest->ID;
	QuestCommand.LParam = pQuest->Kind;
	QuestCommand.SParam = ID;


	if (smWsockServer)
		smWsockServer->Send((char*)&QuestCommand, QuestCommand.size, TRUE);

	return true;
}

void sSPOILER::StartQuest(bool ok)
{
	if (!pSelectedQuest)
		return;

	if (!ok)
	{
		cMessageBox.ShowMessage3(MESSAGE_QUEST_START, "");
		return;
	}

	smTRANS_COMMAND smTransCommand = {};

	smTransCommand.code = OpCode::OPCODE_START_QUEST;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = pSelectedQuest->ID;
	smTransCommand.LParam = ID;
	smTransCommand.SParam = pSelectedQuest->QuestInfo.QuestType;
	smTransCommand.EParam = pSelectedQuest->QuestInfo.PartyFlag;

	if (smWsockServer)
		smWsockServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);

	ResetQuests = true;
	pQuestWindow->GetSpoiler(10)->ResetQuests = true;
}

void sSPOILER::CancelQuest(bool ok)
{
	if (!ok)
	{
		cMessageBox.ShowMessage3(MESSAGE_QUEST_CANCEL, "");
		return;
	}

	smTRANS_COMMAND smTransCommand = {};

	smTransCommand.code = OpCode::OPCODE_CANCEL_QUEST;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = pSelectedQuest->ID;
	smTransCommand.LParam = pSelectedQuest->Kind;
	smTransCommand.SParam = pSelectedQuest->QuestInfo.QuestType;

	if (smWsockServer)
		smWsockServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);

	ResetQuests = true;
	pQuestWindow->GetSpoiler(pSelectedQuest->Kind)->ResetQuests = true;
}

void sSPOILER::GetReward()
{
	smTRANS_COMMAND smTransCommand = {};

	smTransCommand.code = OpCode::OPCODE_GET_REWARD;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = pSelectedQuest->ID;
	smTransCommand.LParam = pSelectedQuest->Kind;
	smTransCommand.SParam = pSelectedQuest->QuestInfo.QuestType;

	if (smWsockServer)
		smWsockServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);

	ResetQuests = true;
	pQuestWindow->GetSpoiler(pSelectedQuest->Kind)->ResetQuests = true;
	pQuestWindow->GetSpoiler(11)->ResetQuests = true;
}

char* szFields[] = {
	"Mata das Acácias",
"Floresta Bamboo",
"Jardim da Liberdade",
"Ricartem",
"Refúgio dos Anciões",
"Castelo dos Perdidos",
"Vila Ruinen",
"Terra Maldita",
"Terra Esquecida",
"Navisko",
"Oásis",
"Campo de Batalha dos Anciões",
"Terra Proibida",
"Calabouço Antigo 1º Andar",
"Calabouço Antigo 2º Andar",
"Calabouço Antigo 3º Andar",
"Sala do GM",
"Floresta dos Espíritos",
"Floresta das Ilusões",
"Vale Tranquilo",
"Estrada dos Ventos",
"Pillai",
"Templo Maldito 1º Andar",
"Templo Maldito 2º Andar",
"Caverna dos Cogumelos",
"Caverna das Abelhas",
"Santuario Sombrio",
"Estrada de Ferro do Caos",
"Coração de Perum",
"Eura",
"SoD",
"Vale Galubia",
"Sala de Quest",
"Castelo Antigo (BC)",
"Lago da Ganância",
"Santuario Congelado",
"Caverna do Kelvezu",
"Ilha Perdida",
"Templo Perdido",
"Mapa 2d",
"Torre sem Fim 1º Andar",
"Torre sem Fim 2º Andar",
"Templo Maldito 3º Andar",
"Torre sem Fim 3º Andar",
"Mina de Gelo 1º Andar",
"T.D.P Ardor",
"Laboratorio Secreto",
"Arma Secreta",
"Abismo do Mar 1º Andar",
"Abismo do Mar 2º Andar",
};

extern int NumLineComa64(INT64 Num, char* pBuff);

void sSPOILER::DrawQuest(int BaseX, int BaseY)
{
	if (!pSelectedQuest)
		return;

	sFULL_INFO* pQuestInfo = &pSelectedQuest->QuestInfo;
	SIZE size = {};
	SIZE size2 = {};
	char buff[500];
	int iY = 140;

	if (pQuestInfo->QuestTitle[0])
	{
		SetTextColor(0, RGB(10, 10, 10));
		GetTextExtentPoint(0, pSelectedQuest->QuestInfo.QuestTitle, lstrlen(pSelectedQuest->QuestInfo.QuestTitle), &size);
		dsTextLineOut(BaseX + 428 - (size.cx / 2), BaseY + 94, pSelectedQuest->QuestInfo.QuestTitle, lstrlen(pSelectedQuest->QuestInfo.QuestTitle));

		char* type = "(Solo)";
		if (pQuestInfo->PartyFlag)
			type = "(Party)";

		SetTextColor(0, RGB(10, 10, 10));
		GetTextExtentPoint(0, type, lstrlen(type), &size2);
		dsTextLineOut(BaseX + 428 - (size2.cx / 2), BaseY + 94 + size.cy + 3, type, lstrlen(type));
	}

	SetTextColor(0, RGB(10, 10, 10));

	if (pQuestInfo->LevelMin > 0)
	{
		wsprintf(buff, "Level Requerido: %d-%d", pQuestInfo->LevelMin, pQuestInfo->LevelMax);
		dsTextLineOut(BaseX + 280, BaseY + 110, buff, lstrlen(buff));
	}

	if (pQuestInfo->QuestDesc[0])
	{
		SetTextColor(0, RGB(10, 10, 10));

		for (int i = 0; i < 5; i++)
		{
			if (pQuestInfo->QuestDesc[0 + (i * 34)])
			{
				dsTextLineOut(BaseX + 322, BaseY + iY, &pQuestInfo->QuestDesc[0 + (i * 34)], lstrlen(&pQuestInfo->QuestDesc[0 + (i * 34)]) > 34 ? 34 : lstrlen(&pQuestInfo->QuestDesc[0 + (i * 34)]));
				iY += 14;
			}
		}

		iY += 5;
	}

	if (pQuestInfo->MonsterCount)
	{
		SetTextColor(0, RGB(10, 10, 10));
		iY = 0;

		bool isComplete = true;

		for (int i = 0; i < pQuestInfo->MonsterCount; i++)
		{
			wsprintf(buff, "%d/%d %s", pQuestInfo->MonsterKilled[i], pQuestInfo->MonsterCounts[i], pQuestInfo->MonsterMaps[i] < 0 ? pQuestInfo->MonsterNames[i] : szFields[pQuestInfo->MonsterMaps[i]]);

			dsTextLineOut(BaseX + 300, BaseY + 240 + iY, buff, lstrlen(buff));
			if (pQuestInfo->MonsterKilled[i] < pQuestInfo->MonsterCounts[i])
				isComplete = false;
			iY += 14;
		}

		pSelectedQuest->Complete = isComplete;
	}

	if (pQuestInfo->RewardCount || pQuestInfo->RewardGold || pQuestInfo->RewardExp || pQuestInfo->RewardClanExp || pQuestInfo->RewardCoin || pQuestInfo->RewardTCoin)
	{
		iY = 350;

		SetTextColor(0, RGB(10, 10, 10));

		if (pQuestInfo->RewardCount)
		{
			for (int i = 0; i < pQuestInfo->RewardCount; i++)//
			{
				wsprintf(buff, "%dx %s", pQuestInfo->RewardCounts[i], pQuestInfo->RewardNames[i]);
				dsTextLineOut(BaseX + 300, BaseY + iY, buff, lstrlen(buff));
				iY += 14;
			}
		}

		if (pQuestInfo->RewardGold)
		{
			ZeroMemory(buff, sizeof(buff));
			NumLineComa(pQuestInfo->RewardGold, buff);
			wsprintf(buff, "%s Gold", buff);
			dsTextLineOut(BaseX + 300, BaseY + iY, buff, lstrlen(buff));
			iY += 14;
		}

		if (pQuestInfo->RewardExp)
		{
			ZeroMemory(buff, sizeof(buff));
			NumLineComa64(pQuestInfo->RewardExp, buff);
			wsprintf(buff, "%s Exp", buff);
			dsTextLineOut(BaseX + 300, BaseY + iY, buff, lstrlen(buff));
			iY += 14;
		}

		if (pQuestInfo->RewardClanExp)
		{
			ZeroMemory(buff, sizeof(buff));
			NumLineComa64(pQuestInfo->RewardClanExp, buff);
			wsprintf(buff, "%s ClanExp", buff);
			dsTextLineOut(BaseX + 300, BaseY + iY, buff, lstrlen(buff));
			iY += 14;
		}

		if (pQuestInfo->RewardCoin)
		{
			ZeroMemory(buff, sizeof(buff));
			NumLineComa(pQuestInfo->RewardCoin, buff);
			wsprintf(buff, "%s Coin", buff);
			dsTextLineOut(BaseX + 300, BaseY + iY, buff, lstrlen(buff));
			iY += 14;
		}

		if (pQuestInfo->RewardTCoin)
		{
			ZeroMemory(buff, sizeof(buff));
			NumLineComa(pQuestInfo->RewardTCoin, buff);
			wsprintf(buff, "%s TCoin", buff);
			dsTextLineOut(BaseX + 300, BaseY + iY, buff, lstrlen(buff));
			iY += 14;
		}
	}

	if (pQuestInfo->EndTime.wDay)
	{
		iY = 406;
		SetTextColor(0, RGB(10, 10, 10));

		dsTextLineOut(BaseX + 300, BaseY + iY, "Concluido em:", lstrlen("Concluido em:"));
		iY += 19;

		SetTextColor(0, RGB(10, 10, 10));

		wsprintf(buff, "%02d/%02d/%02d - %02d:%02d:%02d", pQuestInfo->EndTime.wDay, pQuestInfo->EndTime.wMonth, pQuestInfo->EndTime.wYear, pQuestInfo->EndTime.wHour, pQuestInfo->EndTime.wMinute, pQuestInfo->EndTime.wSecond);
		dsTextLineOut(BaseX + 310, BaseY + iY, buff, lstrlen(buff));
		iY += 14;
	}
}
