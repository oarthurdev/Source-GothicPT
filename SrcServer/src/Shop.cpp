#include "sinbaram\sinLinkHeader.h"
#include "File\File.h"

struct psITEM
{
	int		state;
	int		Serial;
	sITEMINFO	ItemInfo;
};

int	rsRegist_ItemSecCode(rsPLAYINFO *lpPlayInfo, TRANS_ITEMINFO *lpTransItemInfo, int NewItem);
int CreateItem(psITEM *lpsItem, char  *dwCode, int JobCode);
int	rsAddInvenItem(rsPLAYINFO *lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum);

BOOL Shop::CheckTradeCoin(rsPLAYINFO *Player, rsPLAYINFO *Player2, TRANS_TRADEITEMS *lpTransTradeItems)
{
	int UserCoin = 0;
	sTRADE	sTradeCoin;

	if (!Player || !Player2) return FALSE;

	DecodeCompress(lpTransTradeItems->TradeBuff, (BYTE *)&sTradeCoin);

	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[512];
		SQL::GetInstance()->EnterSqlSection();

		wsprintf(szQuery, "SELECT * FROM [SlayonDB].[dbo].[Usuario] WHERE [Login]='%s'", Player->getAccount().c_str());
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(6, &UserCoin);
			}
		}

		SQL::GetInstance()->LeaveSqlSection();

	}

	if (sTradeCoin.Coin > 0)
	{
		if (!UserCoin || UserCoin < sTradeCoin.Coin)
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL Shop::TransferTradeCoin(rsPLAYINFO *Player, rsPLAYINFO *Player2, int nCoin)
{
	if (SQL::GetInstance()->IsConnected())
	{
		int UserCoin = 0, UserCoin2 = 0, ItemPrice = 0;
		char szQuery[512];
		SQL::GetInstance()->EnterSqlSection();

		wsprintf(szQuery, "SELECT * FROM [SlayonDB].[dbo].[Usuario] WHERE [Login]='%s'", Player->getAccount().c_str());
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(6, &UserCoin);
			}
		}


		wsprintf(szQuery, "SELECT * FROM [SlayonDB].[dbo].[Usuario] WHERE [Login]='%s'", Player2->getAccount().c_str());
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(6, &UserCoin2);
			}
			else
			{
				wsprintf(szQuery, "INSERT INTO [SlayonDB].[dbo].[Usuario] ([Login],[Coins]) values('%s',%d)", Player2->getAccount().c_str(), 0);
				SQL::GetInstance()->Execute(szQuery);
			}
		}

		if (!UserCoin || UserCoin < nCoin)
		{
			return FALSE;
		}
		else
		{
			UserCoin -= nCoin;
			UserCoin2 += nCoin;
			wsprintf(szQuery, "UPDATE [SlayonDB].[dbo].[Usuario] SET Coins=%d WHERE [Login]='%s'", UserCoin, Player->getAccount().c_str());
			SQL::GetInstance()->Execute(szQuery);
			wsprintf(szQuery, "UPDATE [SlayonDB].[dbo].[Usuario] SET Coins=%d WHERE [Login]='%s'", UserCoin2, Player2->getAccount().c_str());
			SQL::GetInstance()->Execute(szQuery);
			SendCoinToGame(Player);
			SendCoinToGame(Player2);
		}

		SQL::GetInstance()->LeaveSqlSection();
	}

	return TRUE;
}


void Shop::SendItemToClient(rsPLAYINFO * Player)
{
	if (SQL::GetInstance()->IsConnected())
	{
		int i = 0;
		char szQuery[512];
		SHOP packet;
		ZeroMemory(&packet, sizeof(SHOP));
		packet.size = sizeof(SHOP);
		packet.code = PACKET_SEND_ITEM_GAME;
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT * FROM [SlayonDB].[dbo].[ItemShop]");
		if (SQL::GetInstance()->Execute(szQuery))
		{
			while (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(1, &packet.item[i].SubTag);
				SQL::GetInstance()->GetDataValue(2, packet.item[i].Name);
				SQL::GetInstance()->GetDataValue(3, packet.item[i].itCode);
				SQL::GetInstance()->GetDataValue(4, &packet.item[i].Coin);

				for (int cnt2 = 0; cnt2 < MAX_ITEM; cnt2++)
				{
					if (strcmp(sItem[cnt2].LastCategory, packet.item[i].itCode) == 0)
					{
						packet.item[i].w = sItem[cnt2].w;
						packet.item[i].h = sItem[cnt2].h;
					}
				}

				i++;

				if (i > 69) break;
			}

			Player->lpsmSock->Send((char*)&packet, packet.size, true);
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}


void Shop::SendCoinToGame(rsPLAYINFO * Player)
{
	if (SQL::GetInstance()->IsConnected())
	{
		SHOP_COIN packet;
		char szQuery[512];
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT * FROM [SlayonDB].[dbo].[Usuario] WHERE [Login]='%s'", Player->getAccount().c_str());
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(6, &packet.Coin);
				packet.size = sizeof(SHOP_COIN);
				packet.code = PACKET_SEND_COIN_GAME;
				if (Player->lpsmSock)
					Player->lpsmSock->Send((char *)&packet, packet.size, TRUE);
			}
			else
			{
				packet.size = sizeof(SHOP_COIN);
				packet.code = PACKET_SEND_COIN_GAME;
				packet.Coin = 0;
				if (Player->lpsmSock)
					Player->lpsmSock->Send((char *)&packet, packet.size, TRUE);
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

int Shop::GetCoin(rsPLAYINFO* Player)
{
	int UserCoin = 0;

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
	}
	SQL::GetInstance()->LeaveSqlSection();

	return UserCoin;
}

void Shop::RecvItemToClient(rsPLAYINFO * Player, SHOP_BUY * Shop)
{
	if (SQL::GetInstance()->IsConnected())
	{
		psITEM	*lpsItem;
		lpsItem = new psITEM;
		int UserCoin = 0;
		int Price = 0;
		char szQuery[512];
		SQL::GetInstance()->EnterSqlSection();
		sprintf_s(szQuery, sizeof(szQuery), "SELECT * FROM [SlayonDB].[dbo].[Usuario] WHERE [Login]='%s'", Player->getAccount().c_str());
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
				SQL::GetInstance()->GetDataValue(6, &UserCoin);
			sprintf_s(szQuery, sizeof(szQuery), "SELECT * FROM [SlayonDB].[dbo].[ItemShop] WHERE [CodeIT]='%s'", Shop->item.itCode);
			if (SQL::GetInstance()->Execute(szQuery))
			{
				if (SQL::GetInstance()->Fetch())
					SQL::GetInstance()->GetDataValue(4, &Price);
			}

				if (UserCoin && Price)
				{
					if (UserCoin >= Price)
					{
						UserCoin -= Price;
						sprintf_s(szQuery, sizeof(szQuery), "UPDATE [SlayonDB].[dbo].[Usuario] SET Coins=%d WHERE [Login]='%s'", UserCoin, Player->getAccount().c_str());
						if (SQL::GetInstance()->Execute(szQuery))
						{

								if (CreateItem(lpsItem, Shop->item.itCode, Shop->item.spec) == TRUE)
								{
									TRANS_ITEMINFO		TransItemInfo;
									ReformItem(&lpsItem->ItemInfo);
									TransItemInfo.code = OpCode::OPCODE_PUTITEM;
									TransItemInfo.size = sizeof(TRANS_ITEMINFO);
									memcpy(&TransItemInfo.Item, &lpsItem->ItemInfo, sizeof(sITEMINFO));
									rsRegist_ItemSecCode(Player, &TransItemInfo, 1);
									rsAddInvenItem(Player, TransItemInfo.Item.CODE, TransItemInfo.Item.ItemHeader.Head, TransItemInfo.Item.ItemHeader.dwChkSum);
									if (Player->lpsmSock)
										Player->lpsmSock->Send((char *)&TransItemInfo, TransItemInfo.size, TRUE);
								}
							}

							TRANS_CHATMESSAGE	TransChatMessage;
							if (SQL::GetInstance()->IsConnected())
							{
								char szQuery[512];
								SQL::GetInstance()->EnterSqlSection();
								sprintf_s(szQuery, sizeof(szQuery), "INSERT INTO [LogItemShop].[dbo].[SHOP] ([ID],[ITEM],[COINS]) values('%s','%s','%d')", Player->getAccount().c_str(), Shop->item.Name, UserCoin);
								if (SQL::GetInstance()->Execute(szQuery))
								{
								}

								SQL::GetInstance()->LeaveSqlSection();
							}
							sprintf_s(TransChatMessage.szMessage, sizeof(TransChatMessage.szMessage), "Você comprou o item %s, agora você tem %d de créditos.", Shop->item.Name, UserCoin);
							TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
							TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
							TransChatMessage.dwIP = 3;
							TransChatMessage.dwObjectSerial = 0;

							if (Player->lpsmSock)
								Player->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);

							SendCoinToGame(Player);
						}
					else
					{
						TRANS_CHATMESSAGE	TransChatMessage;
						sprintf_s(TransChatMessage.szMessage, sizeof(TransChatMessage.szMessage), "Você não possui créditos suficientes para comprar esse item.");
						TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
						TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
						TransChatMessage.dwIP = 3;
						TransChatMessage.dwObjectSerial = 0;

						if (Player->lpsmSock)
							Player->lpsmSock->Send((char*)& TransChatMessage, TransChatMessage.size, TRUE);
					}
					SQL::GetInstance()->LeaveSqlSection();
					}
			}

		
		delete lpsItem;
	}
}