#pragma once

#include <Windows.h>

#ifndef _DEBUG
#define ANTI_CHEAT_ENABLE
#endif

struct ChecksumFunction
{
	DWORD										dwSize;
	DWORD										dwAddress;
	DWORD										dwCheckSum;
};

#define CHECKSUM_FUNCTION_TOTAL					400

struct Packet
{
	int										iLength;
	int										iHeader;
};

struct PacketLogCheat: Packet
{
	int										LParam;
	int										iCheatID;
	int										SParam;
	int										EParam;

	int										LxParam;
	int										WxParam;
	int										SxParam;
	int										ExParam;

};

struct PacketLogCheatEx: Packet
{
	int										LParam;
	int										iCheatID;
	int										SParam;
	int										EParam;

	int										LxParam;
	int										WxParam;
	int										SxParam;
	int										ExParam;

	char									szParam[256];
};

struct PacketChecksumFunctionList: Packet
{
	BYTE										bKey;
	ChecksumFunction							sCheckSum[CHECKSUM_FUNCTION_TOTAL];
};

#define WINDOW_CHEATLIST_TOTAL					50

struct PacketWindowList: Packet
{
	int											iCount;
	char										szaWindowName[WINDOW_CHEATLIST_TOTAL][64];
};

class AntiCheat
{
protected:
	struct PacketChecksumFunctionList			* psPacketChecksum = NULL;

	DWORD										dwChecksumRet = 0;
	HANDLE										hThread = NULL;
private:
	BOOL										ChecksumCheckMismatch(struct ChecksumFunction * pChecksum);
	BOOL										GetModuleName(DWORD dwThreadID, char * pszBuf, int iSizeBuf);
	static DWORD WINAPI							EnumWindowsProc(HWND hWnd, LPARAM lParam);
	void										WindowFunctionHandler();
public:

	struct PacketWindowList						* psPacketWindowCheat = NULL;

	DWORD										dwThreadsID[8];

	AntiCheat();
	virtual ~AntiCheat();

	BOOL										AddNewThreadException(DWORD dwThreadID);

	BOOL										IsGameModules(char * pszFile);
	void										ChecksumFunctionHandler();
	void										FindHackDllThread();

	static DWORD WINAPI							ThreadAntiCheatHandler();

	static void __cdecl							CheckThread();

	void										ReceivePacketHandler(struct PacketChecksumFunctionList * psPacket);

	void										HandlePacket(PacketWindowList * psPacket);
};
