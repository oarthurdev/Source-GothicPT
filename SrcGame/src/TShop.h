#pragma once
#include <Windows.h>


#define smTRANSCODE_OPEN_TSHOP   0x49470005
#define TPACKET_SEND_ITEM_GAME   0x49470006
#define TPACKET_SEND_ITEM_SERVER 0x49470007
#define TPACKET_SEND_COIN_GAME   0x49470008

extern SHOP TList;
extern SHOP_ITEM Tselectitem;

class TShop
{
public:
	static              TShop*	GetInstance() { static TShop instance; return &instance; }
	void                RecvItemToServer(SHOP * Shop);
	void                SendItemToServer(SHOP_ITEM item);
	void                RecvCoinToServer(SHOP_COIN * Shop);
	bool                MouseAction(int x, int y, int w, int h);
	bool                IsOpen() { return fOpen; }
	void                Open();
	void                Init();
	void                Draw();
	void                Close();
	void                Button();
	int                 GetSlot();
	int                 GetScroll();
	void                ButtonScroll(short Dist);
private:
	int                Image[90];
	bool               fOpen;
	int                Scroll;
	int                Tag;
	int                SubTag;
	int                Coin;
};

