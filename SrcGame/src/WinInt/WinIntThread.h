#pragma once




#include <wininet.h>
#pragma comment( lib, "wininet.lib" )





extern HINTERNET g_hInternetOpen;


extern int  CreateWinIntThread(void);
extern void DestroyWinIntThread(void);

extern inline void ErrorWinIntThread(void);
extern inline int  IsErrorWinIntThread(void);
extern inline int  IsWinIntThreadState(void);


extern int WinIntThreadResume(void);
