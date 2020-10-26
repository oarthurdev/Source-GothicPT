





#include <windows.h>
#include <wininet.h>
#include "ZipLib.h"
#include "RingBuff.h"
#include "WinIntThread.h"
#include "WavIntHttp.h"




#define MAX_WAV_CONNECT_COUNT		2
#define MAX_WAV_DOWN_COUNT			300

#define MAX_WAV_DOWN_URL			10
static CRingBuff<SWavDownUrl, MAX_WAV_DOWN_URL>		s_WavDownUrlRingBuff;
static SWavDownUrl									s_WavDownUrlBuff[MAX_WAV_DOWN_URL];
static BYTE											s_ZipWavDownBuff[MAX_ZIP_BUFF_SIZE];

static CRITICAL_SECTION								s_WavDownCS;
static char											s_szWavUrlBasis[128];
static int											s_bCreateWavIntHttp;











int CreateWavIntHttp(char *lpWavUrlBasis)
{
	if(g_hInternetOpen && lpWavUrlBasis[0])
		strcpy(s_szWavUrlBasis, lpWavUrlBasis);
	else
		return FALSE;

	if(s_bCreateWavIntHttp == FALSE)
		::InitializeCriticalSection(&s_WavDownCS);

	s_bCreateWavIntHttp = TRUE;
	return TRUE;
}








void DestroyWavIntHttp(void)
{
	if(s_bCreateWavIntHttp == TRUE)
		::DeleteCriticalSection(&s_WavDownCS);

	s_bCreateWavIntHttp = FALSE;
}








int WavIntHttpPush(char *lpRemainderUrl)
{
	if(IsErrorWinIntThread() || s_bCreateWavIntHttp == FALSE)
		return 0;

	SWavDownUrl WavDownInfo;
	::ZeroMemory(&WavDownInfo, sizeof(WavDownInfo));
	::strcpy(WavDownInfo.szRemainderUrl, lpRemainderUrl);

	::EnterCriticalSection(&s_WavDownCS);
	int ret = s_WavDownUrlRingBuff.Push(WavDownInfo);
	::LeaveCriticalSection(&s_WavDownCS);
	return ret;
}










































































void MainWavIntHttp(void)
{
	if(IsErrorWinIntThread() || s_bCreateWavIntHttp == FALSE)
		return;

	DWORD WavDownUrlCount = 0;
	::EnterCriticalSection(&s_WavDownCS);
	s_WavDownUrlRingBuff.TotalPop(s_WavDownUrlBuff, WavDownUrlCount);
	::LeaveCriticalSection(&s_WavDownCS);

	
	
	
	
	
	
	
	
}








