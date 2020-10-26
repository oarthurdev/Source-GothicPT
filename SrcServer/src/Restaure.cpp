#include "Restaure.h"
#include "../../Shared/smPacket.h"
#include "Database\\Database.h"
#include "sinbaram\\sinLinkHeader.h"

#include <iostream>

FailedItemsPckg failedItems = { 0 };
FailedItems getItems = { 0 };

extern int CreateCommandItem(rsPLAYINFO* lpPlayInfo, rsPLAYINFO* lpPlayInfo2, char* szItem);

RestaureItem::RestaureItem()
{
}

RestaureItem::~RestaureItem()
{
}

int setPrice()
{
	shared_ptr<Database> pcDB = Database::GetConnection(DATABASEID_PristonDB);

	int price = 0;

	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT Price FROM Restaure"))
		{
			if (pcDB->Execute())
			{
				pcDB->GetData(&price, 0, 1, PARAMTYPE_Integer);

				if (price)
					return price;
			}
		}
		pcDB->Close();
	}

	return 500; // Padrão
}


int checkCoin(rsPLAYINFO* Player)
{
	int UserCoin = 0;
	int Value = setPrice();
	TRANS_CHATMESSAGE	TransChatMessage;

	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[512];
		SQL::GetInstance()->EnterSqlSection();
		sprintf_s(szQuery, sizeof(szQuery), "SELECT * FROM [SlayonDB].[dbo].[Usuario] WHERE [Login]='%s'", Player->getAccount().c_str());
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
				SQL::GetInstance()->GetDataValue(6, &UserCoin);
		}

		if (UserCoin >= Value)
		{
			UserCoin -= Value;
			sprintf_s(szQuery, sizeof(szQuery), "UPDATE [SlayonDB].[dbo].[Usuario] SET Coins=%d WHERE [Login]='%s'", UserCoin, Player->getAccount().c_str());
			if (SQL::GetInstance()->Execute(szQuery))
			{
				sprintf_s(TransChatMessage.szMessage, sizeof(TransChatMessage.szMessage), "O Item foi restaurado com sucesso!");
				TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
				TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
				TransChatMessage.dwIP = 3;
				TransChatMessage.dwObjectSerial = 0;

				if (Player->lpsmSock)
					Player->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);

				return TRUE;
			}
		}
		else
		{
			sprintf_s(TransChatMessage.szMessage, sizeof(TransChatMessage.szMessage), "Você não possui Coins suficientes.");
			TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
			TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
			TransChatMessage.dwIP = 3;
			TransChatMessage.dwObjectSerial = 0;

			if (Player->lpsmSock)
				Player->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
		}

		SQL::GetInstance()->LeaveSqlSection();
	}

	return FALSE;

}

INT RestaureItem::RecoverItem(rsPLAYINFO* Player, int ItemHead, int ItemChkSum)
{
	if (checkCoin(Player))
	{
		char codeItem[64] = { 0 };
		wsprintf(codeItem, "@%d@%d", ItemHead, ItemChkSum);
		CreateCommandItem(Player, Player, codeItem);

		shared_ptr<Database> pcDB = Database::GetConnection(DATABASEID_LogDB);

		if (pcDB->Open())
		{
			if (pcDB->Prepare("DELETE FROM AgingFailed WHERE ItemHead=? AND ItemChkSum=?"))
			{
				pcDB->BindInputParameter(&ItemHead, 1, PARAMTYPE_Integer);
				pcDB->BindInputParameter(&ItemChkSum, 2, PARAMTYPE_Integer);
				pcDB->Execute();
			}

			pcDB->Close();
		}
	}

	return TRUE;
}

INT RestaureItem::sendFailedItems(rsPLAYINFO* Player)
{

	shared_ptr<Database> pcDB = Database::GetConnection(DATABASEID_LogDB);

	ZeroMemory(&failedItems, sizeof(FailedItemsPckg));
	failedItems.price = setPrice();
	failedItems.size = sizeof(FailedItemsPckg);
	failedItems.code = GET_FAILED_ITEMS;

	if (pcDB->Open())
	{
		if (pcDB->Prepare("SELECT * FROM AgingFailed WHERE ID=? AND Date <= (GETDATE() + 30)"))
		{
			char playerID[32] = { 0 };
			wsprintf(playerID, "%s", Player->getAccount().c_str());

			pcDB->BindInputParameter(playerID, 1, PARAMTYPE_String);

			if (pcDB->Execute(false))
			{
				int i = 0;

				while (pcDB->NextRow())
				{
					pcDB->GetData(failedItems.FailedItems[i].ItemName, 32, 5, PARAMTYPE_String);
					pcDB->GetData(&failedItems.FailedItems[i].AgingNum, 0, 6, PARAMTYPE_Integer);
					pcDB->GetData(&failedItems.FailedItems[i].ItemHead, 0, 7, PARAMTYPE_Integer);
					pcDB->GetData(&failedItems.FailedItems[i].ItemChkSum, 0, 8, PARAMTYPE_Integer);
					pcDB->GetData(&failedItems.FailedItems[i].Date, 0, 9, PARAMTYPE_Time);

					i++;
					if (i >= 20) break;
				}

				failedItems.total = i;
			}
		}
		pcDB->Close();
	}

	Player->lpsmSock->Send((char*)&failedItems, failedItems.size, TRUE);

	return TRUE;
}

