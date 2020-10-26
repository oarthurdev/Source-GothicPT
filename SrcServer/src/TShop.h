#pragma once
#include <Windows.h>


#define smTRANSCODE_OPEN_TSHOP   0x49470005
#define TPACKET_SEND_ITEM_GAME   0x49470006
#define TPACKET_SEND_ITEM_SERVER 0x49470007
#define TPACKET_SEND_COIN_GAME   0x49470008

class TShop
{
public:
	static              TShop*	GetInstance() { static TShop instance; return &instance; }
	void                SendItemToClient(rsPLAYINFO * Player);
	void                SendCoinToGame(rsPLAYINFO * Player);
	void                RecvItemToClient(rsPLAYINFO * Player, SHOP_BUY * Shop);
};

