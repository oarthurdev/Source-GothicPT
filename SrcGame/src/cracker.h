
#pragma once 

struct TRANS_FIND_CRACKER;

extern DWORD dwExeCheckSum;
extern char szProcessPath[256];

char *FindCracker();

char *FindCracker(TRANS_FIND_CRACKER *lpTransFindCrack);

char *FindCrackCont();

int CheckCrackProcess(int Flag = 0);

DWORD GetModuleCheckSum(char *szModule);

int CheckDLL_Module();

#define WM_NPROTECT_FORCEEXIT (WM_USER + 10010)

#define WM_NPROTECT_EXIT_TWO (WM_USER + 10001)

#define WM_NPROTECT_SPEEDHACK (WM_USER + 10011)
#define WM_NPROTECT_SH_ERROR (WM_USER + 10012)

#define WM_NPROTECT_SOFTICE (WM_USER + 10111)
