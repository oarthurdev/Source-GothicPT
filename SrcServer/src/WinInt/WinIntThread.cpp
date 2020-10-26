#include <windows.h>
#include <wininet.h>
#include "WavIntHttp.h"
#include "WinIntThread.h"



HINTERNET					g_hInternetOpen;
int							g_ErrorWinInt;


static HANDLE				s_hWinIntThread;
static int					s_WinIntThreadState;
static int					s_WinIntThreadExit;
static CRITICAL_SECTION		s_WinIntThrCS;


static DWORD WINAPI WinIntThreadProc(LPVOID lpParameter);








int CreateWinIntThread(void)
{


	return TRUE;
}








void DestroyWinIntThread(void)
{
	
}








inline void ErrorWinIntThread(void)
{
}








inline int IsErrorWinIntThread(void)
{
	return g_ErrorWinInt;
}








inline int IsWinIntThreadState(void)
{
	return s_WinIntThreadState;
}

















int WinIntThreadResume(void)
{
	if(IsErrorWinIntThread())
		return 0;

	if(s_WinIntThreadState == 1)
		return 1;

	::EnterCriticalSection(&s_WinIntThrCS);
	::ResumeThread(s_hWinIntThread);
	s_WinIntThreadState = 1;
	::LeaveCriticalSection(&s_WinIntThrCS);
	return 1;
}








static DWORD WINAPI WinIntThreadProc(LPVOID lpParameter)
{
	while(s_WinIntThreadExit == 0)
	{

		MainWavIntHttp();


		s_WinIntThreadState = 0;
		::SuspendThread(s_hWinIntThread);
	}
	return 1;
}



