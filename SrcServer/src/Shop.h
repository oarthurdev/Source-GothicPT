#pragma once
#include <Windows.h>


#define smTRANSCODE_OPEN_SHOP   0x484700A7
#define PACKET_SEND_ITEM_GAME   0x49470000
#define PACKET_SEND_ITEM_SERVER 0x49470001
#define PACKET_SEND_COIN_GAME   0x49470002

struct SHOP_ITEM
{
	int  SubTag;
    char Name[32];
	char itCode[32];
    int  Coin;
	int w;
	int h;
	int combobox;
	int spec;
	LPDIRECTDRAWSURFACE4 Image;
};

struct SHOP
{
	int size;
	int code;
	SHOP_ITEM item[70];
};

struct SHOP_BUY
{
	int size;
	int code;
	SHOP_ITEM item;
};

struct SHOP_COIN
{
	int size;
    int code;
	int Coin;
};

extern SHOP List;

class Shop
{
public:
	static              Shop*	GetInstance() { static Shop instance; return &instance; }
	void                SendItemToClient(rsPLAYINFO * Player);
	void                SendCoinToGame(rsPLAYINFO * Player);
	int                 GetCoin(rsPLAYINFO* Player);
	void                RecvItemToClient(rsPLAYINFO * Player, SHOP_BUY * Shop);
	BOOL CheckTradeCoin(rsPLAYINFO *Player, rsPLAYINFO *Player2, TRANS_TRADEITEMS *lpTransTradeItems);
	BOOL TransferTradeCoin(rsPLAYINFO *Player, rsPLAYINFO *Player2, int nCoin);
};

