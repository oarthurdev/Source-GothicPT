





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


static int DownWavIntHttp(SWavDownUrl *lpWavDownInfo);








int CreateWavIntHttp(char *lpWavUrlBasis)
{

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

		return 0;

}


















static int DownWavIntHttp(SWavDownUrl *lpWavDownInfo)
{
		return 0;

}








void MainWavIntHttp(void)
{

}








