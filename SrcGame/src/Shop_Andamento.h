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
	LPDIRECT3DTEXTURE9 Image;
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
extern SHOP_ITEM selectitem;

void DrawImage(int Image, int x, int y, int w, int h);

class Shop
{
public:
	static              Shop*	GetInstance() { static Shop instance; return &instance; }
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
	int  GetCoin() { return Coin; };
	void PlusCoin(int Coin);
	void MinusCoin(int Coin);
private:
	int                Image[90];
	bool               fOpen;
	int                Scroll;
	int                Tag;
	int                SubTag;
	int                Coin;
};

