#define CE_UPDATECLDATA_CPP

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <math.h>

#include "tjclanDEF.h"

#ifdef USE_PROSTONTALE		

#include "sinbaram\\SinLinkHeader.h"
#include "HoBaram\\HoLinkHeader.h"
#include "Language\\language.h"
#include "HoBaram\\HoTextFile.h"
#endif

#include <stdio.h>
#include "tjclan.h"
#include "cE_CViewClanInfo.h"
#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"
#include "cE_Updatecldata.h"
#include "..\\ygy\\ygyheader.h"




CUpdateCldata::CUpdateCldata()
{
}

CUpdateCldata::~CUpdateCldata()
{
}


void CUpdateCldata::Updatecldata()
{
	static cnt = 0;
	extern char updateis[256];
	wsprintf(updateis, "Updatecldata : %d ", cnt++);

	WebDB.Resume();
	WebDB.Updatcldata(cldata.szID, cldata.gserver, cldata.ChaName);
}



void g_UpdateCldata_Close()
{
	g_UpdateCldata.Close();




#ifdef VOICE_CHAT
	if(bCheckClan)
	{
		if(cldata.intClanMark)
		{

			g_CtrlProcess.SetSelectCha(cldata.szID, cldata.ChaName,
									   cldata.name, (DWORD)cldata.intClanMark, cldata.myPosition);
		}
		else
		{

			g_CtrlProcess.SetSelectCha(cldata.szID, cldata.ChaName,
									   NULL, 0, cldata.myPosition);
		}

	}
#endif


}

extern int downClanSu;
void CUpdateCldata::Close()
{
	if(OpenFlag == 0 && downClanSu == 0)
	{
		WebDB.Suspend();
	}
}