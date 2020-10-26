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
DWORD GetServerTime();


void TShop::SendItemToClient(rsPLAYINFO * Player)
{
	if (SQL::GetInstance()->IsConnected())
	{
		int i = 0;
		char szQuery[512];
		SHOP packet;
		ZeroMemory(&packet, sizeof(SHOP));
		packet.size = sizeof(SHOP);
		packet.code = TPACKET_SEND_ITEM_GAME;
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT * FROM [SlayonDB].[dbo].[ItemShopT]");
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


void TShop::SendCoinToGame(rsPLAYINFO * Player)
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
				SQL::GetInstance()->GetDataValue(7, &packet.Coin);
				packet.size = sizeof(SHOP_COIN);
				packet.code = TPACKET_SEND_COIN_GAME;
				if (Player->lpsmSock)
					Player->lpsmSock->Send((char *)&packet, packet.size, TRUE);
			}
			else
			{
				packet.size = sizeof(SHOP_COIN);
				packet.code = TPACKET_SEND_COIN_GAME;
				packet.Coin = 0;
				if (Player->lpsmSock)
					Player->lpsmSock->Send((char *)&packet, packet.size, TRUE);
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void TShop::RecvItemToClient(rsPLAYINFO * Player, SHOP_BUY * Shop)
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
				SQL::GetInstance()->GetDataValue(3, &UserCoin);
			sprintf_s(szQuery, sizeof(szQuery), "SELECT * FROM [SlayonDB].[dbo].[ItemShopT] WHERE [CodeIT]='%s'", Shop->item.itCode);
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
						sprintf_s(szQuery, sizeof(szQuery), "UPDATE [SlayonDB].[dbo].[Usuario] SET Timer=%d WHERE [Login]='%s'", UserCoin, Player->getAccount().c_str());
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

							TRANS_CHATMESSAGE	TransChatMessage;
							sprintf_s(TransChatMessage.szMessage, sizeof(TransChatMessage.szMessage), "Você comprou o item %s, agora você tem %d de minutos.", Shop->item.Name, UserCoin);
							TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;
							TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
							TransChatMessage.dwIP = 3;
							TransChatMessage.dwObjectSerial = 0;

							if (Player->lpsmSock)
								Player->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);

							SendCoinToGame(Player);
						}
					}
					else
					{
						TRANS_CHATMESSAGE	TransChatMessage;
						sprintf_s(TransChatMessage.szMessage, sizeof(TransChatMessage.szMessage), "Você não possui minutos suficientes para comprar esse item.");
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

