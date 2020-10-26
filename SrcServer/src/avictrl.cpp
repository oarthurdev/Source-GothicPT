#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <windowsx.h>
#include <commdlg.h>
#include <stdlib.h>
#include <stdarg.h>
#include <mmsystem.h>
#include <vfw.h>

#include <ddraw.h>

#include "avictrl.h"

#define	SCREEN_BPP		16			


PAVISTREAM pas;
LONG lFmtLength;
LPBITMAPINFOHEADER lpSrcFmt;
LPBITMAPINFOHEADER lpTarget;
LONG lLength;
AVISTREAMINFO si;
LPBYTE lpB, lpI;
DWORD lpISize;

LONG lIndex;
LONG lFrames;
HIC hic;
OPENFILENAME ofn;

int VideoWidth, VideoHeight;

int PlayFrame;




int OpenVideoFile(char *AVIFile)

{

	
	return TRUE;

}



void CloseAVIData()
{

}

void AVIDrawSurface(DIRECTDRAWSURFACE *lpDDSSource, int frame)
{}


void AVIFrameRead(int frame){}


