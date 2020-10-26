#include "AntiCheat.h"
#include "smwsock.h"
#include "smPacket.h"

#include <vector>
#include <Windows.h>
#include <TlHelp32.h>


typedef LONG NTSTATUS;

bool bLoadedNTDLL = false;

#define STATUS_SUCCESS ((NTSTATUS)0x00000000L)
#define ThreadQuerySetWin32StartAddress 9

typedef NTSTATUS(WINAPI *NTQUERYINFOMATIONTHREAD)(HANDLE, LONG, PVOID, ULONG, PULONG);

extern smWINSOCK *smWsockDataServer;
extern AntiCheat * pcAntiCheat;

std::vector<ChecksumFunction> vChecksumFunction;

AntiCheat::AntiCheat()
{
	ZeroMemory(&dwThreadsID, sizeof(DWORD) * 8);
}

AntiCheat::~AntiCheat()
{
}
#ifdef ANTI_CHEAT_ENABLE
HWND FindWindowPartialName(char * pszWindowName, char * pszTempVar)
{
	char szTempName[256] = { 0 };
	char szTempName2[256] = { 0 };
	char szNameWindow[256] = { 0 };
	int iLenTitle = 0;

	ZeroMemory(szNameWindow, 256);
	for(int i = 0; i < lstrlenA(pszWindowName); i++)
		szNameWindow[i] = tolower(pszWindowName[i]);

	HWND hWndTemp = FindWindowA(NULL, NULL);
	while(hWndTemp != 0)
	{
		iLenTitle = GetWindowTextA(hWndTemp, szTempName, 255);

		lstrcpy(szTempName2, szTempName);

		for(int i = 0; i < lstrlenA(szTempName); i++)
			szTempName[i] = tolower(szTempName[i]);

		if(lstrlenA(szTempName) && strstr(szTempName, szNameWindow))
		{
			lstrcpynA(pszTempVar, szTempName2, 256);
			break;
		}
		hWndTemp = GetWindow(hWndTemp, GW_HWNDNEXT);
	}



	return hWndTemp;
}


BOOL AntiCheat::ChecksumCheckMismatch(ChecksumFunction * pChecksum)
{
	return TRUE;

	DWORD dwSize = pChecksum->dwSize;

	DWORD dwCheckSum = dwChecksumRet = 0;

	DWORD dwOld = 0;
	VirtualProtect((void*)pChecksum->dwAddress, dwSize, PAGE_EXECUTE_READWRITE, &dwOld);


	for(DWORD i = 0; i < dwSize; i++)
	{
		dwCheckSum += (DWORD)(*(BYTE*)(pChecksum->dwAddress + i)) ^ psPacketChecksum->bKey;
	}


	if(dwCheckSum == pChecksum->dwCheckSum)
	{
		VirtualProtect((void*)pChecksum->dwAddress, dwSize, dwOld, NULL);
		return TRUE;
	}


	dwChecksumRet = dwCheckSum;
	VirtualProtect((void*)pChecksum->dwAddress, dwSize, dwOld, NULL);

	return FALSE;
}

BOOL AntiCheat::GetModuleName(DWORD dwThreadID, char * pszBuf, int iSizeBuf)
{
	MODULEENTRY32 moduleEntry32;

	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPALL, GetCurrentProcessId());

	moduleEntry32.dwSize = sizeof(MODULEENTRY32);
	moduleEntry32.th32ModuleID = 1;


	if(Module32First(hSnapshot, &moduleEntry32))
	{

		if(GetModuleHandleA(NULL) == moduleEntry32.hModule)
		{
			lstrcpynA(pszBuf, moduleEntry32.szExePath, iSizeBuf);
		}
		else
		{

			while(Module32Next(hSnapshot, &moduleEntry32))
			{

				if(GetModuleHandleA(NULL) == moduleEntry32.hModule)
				{
					lstrcpynA(pszBuf, moduleEntry32.szExePath, iSizeBuf);
					break;
				}
			}
		}
	}
	CloseHandle(hSnapshot);
	return FALSE;
}

BOOL AntiCheat::AddNewThreadException(DWORD dwThreadID)
{
	if(!dwThreadID)
		return FALSE;


	for(int i = 0; i < _countof(dwThreadsID); i++)
	{
		if(dwThreadsID[i] == dwThreadID)
			return TRUE;
	}

	for(int i = 0; i < _countof(dwThreadsID); i++)
	{
		if(!dwThreadsID[i])
		{
			dwThreadsID[i] = dwThreadID;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL AntiCheat::IsGameModules(char * pszFile)
{
	char path[2048];
	GetModuleFileName(NULL, path, 2048);
	int iSizePathString = lstrlenA(path);
	for(int i = 0; i < iSizePathString; i++)
		path[i] = tolower(path[i]);
	std::string modulePath(path);
	std::string parentStr;
	parentStr = modulePath.replace(modulePath.length() - 8, modulePath.length(), "");

	char szModule[256] = { 0 };
	lstrcpyA(szModule, pszFile);
	int iSizeString = lstrlenA(szModule);
	for(int i = 0; i < iSizeString; i++)
		szModule[i] = tolower(szModule[i]);

	char * extract = strstr(szModule, (parentStr + "Game.exe").c_str());
	if(extract)
	{
		return TRUE;
	}
	extract = strstr(szModule, "windows\\system");
	if(extract)
	{
		return TRUE;
	}
	extract = strstr(szModule, "windows\\syswow64");
	if(extract)
	{
		return TRUE;
	}
	extract = strstr(szModule, "\\gbpsv.exe");
	if(extract)
	{
		return  TRUE;
	}
	extract = strstr(szModule, "\\gbpinj.dll");
	if(extract)
	{
		return  TRUE;
	}

	return FALSE;
}

void AntiCheat::ChecksumFunctionHandler()
{
	for(int i = 0; i < CHECKSUM_FUNCTION_TOTAL; i++)
	{

		if(psPacketChecksum && psPacketChecksum->sCheckSum[i].dwSize)
		{

			if(!ChecksumCheckMismatch(&psPacketChecksum->sCheckSum[i]))
			{

				PacketLogCheat sPacket;
				sPacket.iLength = sizeof(PacketLogCheat);
				sPacket.iHeader = OpCode::FIND_CHEAT;
				sPacket.iCheatID = 8954;
				sPacket.LParam = psPacketChecksum->sCheckSum[i].dwSize;
				sPacket.SParam = psPacketChecksum->sCheckSum[i].dwAddress;
				sPacket.EParam = psPacketChecksum->sCheckSum[i].dwCheckSum;
				sPacket.LxParam = dwChecksumRet;

				smWsockDataServer->Send((char *)&sPacket, sPacket.iLength, TRUE);

				break;
			}
		}
	}
}

DWORD WINAPI GetThreadStartAddress(__in HANDLE hThread)
{
	NTSTATUS ntStatus;
	DWORD dwThreadStartAddr = 0;
	HANDLE hPeusdoCurrentProcess, hNewThreadHandle;
	NTQUERYINFOMATIONTHREAD NtQueryInformationThread;
	if(!bLoadedNTDLL)
	{
		LoadLibraryA("ntdll.dll");
		bLoadedNTDLL = true;
	}
	if((NtQueryInformationThread = (NTQUERYINFOMATIONTHREAD)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtQueryInformationThread")))
	{
		hPeusdoCurrentProcess = GetCurrentProcess();
		if(DuplicateHandle(hPeusdoCurrentProcess, hThread, hPeusdoCurrentProcess, &hNewThreadHandle, THREAD_QUERY_INFORMATION, FALSE, 0))
		{
			ntStatus = NtQueryInformationThread(hNewThreadHandle, ThreadQuerySetWin32StartAddress, &dwThreadStartAddr, sizeof(DWORD), NULL);
			CloseHandle(hNewThreadHandle);
			if(ntStatus != STATUS_SUCCESS) return 0;
		}

	}

	return dwThreadStartAddr;
}

BOOL MatchAddressToModule(__in DWORD dwProcId, __out_bcount(MAX_PATH + 1) LPTSTR lpstrModule, __in DWORD dwThreadStartAddr, __out_opt PDWORD pModuleStartAddr)
{
	BOOL bRet = FALSE;
	HANDLE hSnapshot;
	MODULEENTRY32 moduleEntry32;

	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPALL, dwProcId);

	moduleEntry32.dwSize = sizeof(MODULEENTRY32);
	moduleEntry32.th32ModuleID = 1;

	if(Module32First(hSnapshot, &moduleEntry32))
	{
		if(dwThreadStartAddr >= (DWORD)moduleEntry32.modBaseAddr && dwThreadStartAddr <= ((DWORD)moduleEntry32.modBaseAddr + moduleEntry32.modBaseSize))
		{
			lstrcpyA(lpstrModule, moduleEntry32.szExePath);
		}
		else
		{
			while(Module32Next(hSnapshot, &moduleEntry32))
			{
				if(dwThreadStartAddr >= (DWORD)moduleEntry32.modBaseAddr && dwThreadStartAddr <= ((DWORD)moduleEntry32.modBaseAddr + moduleEntry32.modBaseSize))
				{
					lstrcpyA(lpstrModule, moduleEntry32.szExePath);
					break;
				}
			}
		}
	}

	if(pModuleStartAddr) *pModuleStartAddr = (DWORD)moduleEntry32.modBaseAddr;
	CloseHandle(hSnapshot);

	return bRet;
}


void AntiCheat::FindHackDllThread()
{
	HANDLE hSnapshot, hThread;
	THREADENTRY32 threadEntry32;
	DWORD dwModuleBaseAddr, dwThreadStartAddr;
	TCHAR lpstrModuleName[MAX_PATH + 1] = { 0 };

	CRITICAL_SECTION	cSection;
	InitializeCriticalSection(&cSection);
	EnterCriticalSection(&cSection);


	if((hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, GetCurrentProcessId())) == INVALID_HANDLE_VALUE)
		return;

	threadEntry32.dwSize = sizeof(THREADENTRY32);
	threadEntry32.cntUsage = 0;

	if(Thread32First(hSnapshot, &threadEntry32))
	{
		if(threadEntry32.th32OwnerProcessID == GetCurrentProcessId())
		{
			hThread = OpenThread(THREAD_QUERY_INFORMATION, FALSE, threadEntry32.th32ThreadID);
			dwThreadStartAddr = GetThreadStartAddress(hThread);
			MatchAddressToModule(GetCurrentProcessId(), lpstrModuleName, dwThreadStartAddr, &dwModuleBaseAddr);
			if(!IsGameModules(lpstrModuleName))
			{
				FreeLibraryAndExitThread(GetModuleHandleA(lpstrModuleName), 0);
			}
			CloseHandle(hThread);
		}
		while(Thread32Next(hSnapshot, &threadEntry32))
		{
			if(threadEntry32.th32OwnerProcessID == GetCurrentProcessId())
			{
				hThread = OpenThread(THREAD_QUERY_INFORMATION, FALSE, threadEntry32.th32ThreadID);
				dwThreadStartAddr = GetThreadStartAddress(hThread);
				MatchAddressToModule(GetCurrentProcessId(), lpstrModuleName, dwThreadStartAddr, &dwModuleBaseAddr);
				if(!IsGameModules(lpstrModuleName))
				{
					FreeLibraryAndExitThread(GetModuleHandleA(lpstrModuleName), 0);
				}
				CloseHandle(hThread);
			}
		}
	}
	LeaveCriticalSection(&cSection);
	DeleteCriticalSection(&cSection);
	CloseHandle(hSnapshot);
}

void AntiCheat::WindowFunctionHandler()
{
	char szTempName[256];
	for(int i = 0; i < 50; i++)
	{
		if(lstrlenA(pcAntiCheat->psPacketWindowCheat->szaWindowName[i]) && FindWindowPartialName(pcAntiCheat->psPacketWindowCheat->szaWindowName[i], szTempName))
		{

			PacketLogCheatEx sPacket;
			sPacket.iLength = sizeof(PacketLogCheatEx);
			sPacket.iHeader = OpCode::FIND_CHEAT;
			sPacket.iCheatID = 8955;
			lstrcpyA(sPacket.szParam, szTempName);

			if(smWsockDataServer)
			{
				smWsockDataServer->Send((char *)&sPacket, sPacket.iLength, TRUE);
			}
			else
				exit(0);
			
		}
	}
	return;
}

bool antidebug1()
{
	bool bRet = false;

	__asm
	{
		mov eax, dword ptr fs : [0x18]

		mov eax, dword ptr[eax + 0x30]

		cmp byte ptr[eax + 2], 0
		je blocEnd
		mov bRet, 1
		blocEnd :

	}

	return bRet;
}

DWORD dwTickCount = 0;
DWORD dwTickCount2 = 0;

bool bdebugfound = false;
extern DWORD dwtickhack;

DWORD WINAPI AntiCheat::ThreadAntiCheatHandler()
{
	pcAntiCheat->AddNewThreadException(GetCurrentThreadId());

	while(true)
	{

		if((GetTickCount() - dwTickCount) >= 15000)
		{
			pcAntiCheat->ChecksumFunctionHandler();

			if(pcAntiCheat->psPacketWindowCheat)
				pcAntiCheat->WindowFunctionHandler();

			dwTickCount = GetTickCount();
		}

		if((GetTickCount() - dwTickCount2) >= 1000)
		{
			if(antidebug1())
			{
				bdebugfound = true;
			}

			if(IsDebuggerPresent())
			{
				bdebugfound = true;
			}

			dwtickhack = GetTickCount();
			dwTickCount2 = GetTickCount();
		}
	}
	return TRUE;
}

void AntiCheat::CheckThread()
{
	DWORD dwThreadID = GetCurrentThreadId();
	BOOL bThreadFound = FALSE;


	for(int i = 0; i < _countof(pcAntiCheat->dwThreadsID); i++)
	{
		if(pcAntiCheat->dwThreadsID[i] == dwThreadID)
		{
			bThreadFound = TRUE;
			break;
		}
	}


	if(!bThreadFound)
	{

		char szModuleName[128] = { 0 };
		PacketLogCheat sPacket;
		sPacket.iLength = sizeof(PacketLogCheat);
		sPacket.iHeader = OpCode::FIND_CHEAT;
		sPacket.iCheatID = 8720;
		sPacket.LParam = dwThreadID;

		smWsockDataServer->Send((char *)&sPacket, sPacket.iLength, TRUE);
	}
}

void AntiCheat::ReceivePacketHandler(PacketChecksumFunctionList * psPacket)
{
	if(!psPacketChecksum)
		psPacketChecksum = new PacketChecksumFunctionList;

	ZeroMemory(psPacketChecksum, sizeof(PacketChecksumFunctionList));

	CopyMemory(psPacketChecksum, psPacket, sizeof(PacketChecksumFunctionList));

	if(!hThread)
		hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadAntiCheatHandler, NULL, NULL, NULL);
}

void AntiCheat::HandlePacket(PacketWindowList * psPacket)
{
	if(!psPacketWindowCheat)
		psPacketWindowCheat = new PacketWindowList;

	ZeroMemory(psPacketWindowCheat, sizeof(PacketWindowList));

	CopyMemory(psPacketWindowCheat, psPacket, sizeof(PacketWindowList));
}

#else
HWND FindWindowPartialName(char * pszWindowName, char * pszTempVar)
{
	return NULL;
}


BOOL AntiCheat::ChecksumCheckMismatch(ChecksumFunction * pChecksum)
{
	return FALSE;
}

BOOL AntiCheat::GetModuleName(DWORD dwThreadID, char * pszBuf, int iSizeBuf)
{

	return FALSE;
}

BOOL AntiCheat::AddNewThreadException(DWORD dwThreadID)
{
	return FALSE;
}

BOOL AntiCheat::IsGameModules(char * pszFile)
{
	return FALSE;
}

void AntiCheat::ChecksumFunctionHandler()
{

}

DWORD WINAPI GetThreadStartAddress(__in HANDLE hThread)
{
	return NULL;
}

BOOL MatchAddressToModule(__in DWORD dwProcId, __out_bcount(MAX_PATH + 1) LPTSTR lpstrModule, __in DWORD dwThreadStartAddr, __out_opt PDWORD pModuleStartAddr)
{
	return FALSE;
}


void AntiCheat::FindHackDllThread()
{
}

void AntiCheat::WindowFunctionHandler()
{

}

bool antidebug1()
{
	return false;
}

DWORD dwTickCount = 0;
DWORD dwTickCount2 = 0;

bool bdebugfound = false;
extern DWORD dwtickhack;

DWORD WINAPI AntiCheat::ThreadAntiCheatHandler()
{
	return TRUE;
}

void AntiCheat::CheckThread()
{
}

void AntiCheat::ReceivePacketHandler(PacketChecksumFunctionList * psPacket)
{
}

void AntiCheat::HandlePacket(PacketWindowList * psPacket)
{
}

#endif 
