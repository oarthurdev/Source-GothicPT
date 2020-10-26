#pragma once
#include <Windows.h>
#include <vector>
#include <basetsd.h>
#include <minwinbase.h>

#define OPEN_RECOVERY_AGING_NPC 0x50600030
#define GET_FAILED_ITEMS 0x50600031
#define RECOVER_AGING_ITEM 0x50600032

struct FailedItems {
    char ItemName[32];
    int AgingNum;
    int ItemHead;
    int ItemChkSum;
    SYSTEMTIME Date;
};

struct FailedItemsPckg {
    int size;
    int code;
    int total;
    int price;
    FailedItems FailedItems[20];
};

struct Items
{
    int ID;
    int x, y, w, h;
    bool Selected;
    std::vector<FailedItems*> vItems;
};

class RestaureWindow
{

public:
    static              RestaureWindow* GetInstance() { static RestaureWindow instance; return &instance; }

    void Init();

    bool openFlag = false;
    int BaseX, BaseY;
    int ScrollList;


    INT getFailedItems();
    INT ReceiveFailedItems(FailedItemsPckg* FailedItems);

    void OpenNpc();
    void OpenWindow();
    void CloseWindow();
    void LButtonDown();
    void MouseWheel(short zDelta);

    int Window[20];
private:
};
