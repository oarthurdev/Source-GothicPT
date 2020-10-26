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

	AVIFileInit();

	AVIStreamOpenFromFile(&pas,
						  AVIFile,
						  streamtypeVIDEO,
						  0,
						  OF_READ | OF_SHARE_EXCLUSIVE,
						  NULL);

	AVIStreamFormatSize(pas, 0, &lFmtLength);

	lpSrcFmt = (LPBITMAPINFOHEADER)malloc(lFmtLength);
	lpTarget = (LPBITMAPINFOHEADER)malloc(lFmtLength + (sizeof(RGBQUAD) * 256));

	AVIStreamReadFormat(pas, 0, lpSrcFmt, &lFmtLength);

	lFrames = AVIStreamLength(pas);

	memcpy(lpTarget, lpSrcFmt, lFmtLength);
	lpTarget->biBitCount = SCREEN_BPP;
	lpTarget->biCompression = BI_RGB;
	lpTarget->biSizeImage = lpTarget->biHeight * lpTarget->biWidth;

	VideoWidth = lpTarget->biWidth;
	VideoHeight = lpTarget->biHeight;


	AVIStreamInfo(pas, &si, sizeof AVISTREAMINFO);

	lLength = (ULONG)lpTarget->biSizeImage * (ULONG)(lpSrcFmt->biBitCount >> 3);

	if(si.dwSuggestedBufferSize)
		if((LONG)si.dwSuggestedBufferSize < lLength)
			lLength = (LONG)si.dwSuggestedBufferSize;

	lpB = (LPBYTE)malloc(lLength);
	lpISize = lpTarget->biSizeImage * (SCREEN_BPP / 8);
	lpI = (LPBYTE)malloc(lpISize);

	hic = ICDecompressOpen(ICTYPE_VIDEO, si.fccHandler, lpSrcFmt, lpTarget);

	lpSrcFmt = (LPBITMAPINFOHEADER)realloc(lpSrcFmt, lFmtLength + (sizeof(RGBQUAD) * 256));

	ICDecompressGetPalette(hic, lpSrcFmt, lpTarget);

	PlayFrame = 0;


	return lFrames;

}



void CloseAVIData()
{
	free(lpI);
	free(lpB);
	free(lpTarget);
	free(lpSrcFmt);

	ICClose(hic);
	AVIStreamRelease(pas);
	AVIFileExit();

}


void AVIFrameRead(int frame)
{

	if((frame - PlayFrame) > 15) PlayFrame = frame - 15;

	while(frame > PlayFrame)
	{

		AVIStreamRead(pas, PlayFrame, 1, lpB, lLength, NULL, NULL);
		ICDecompress(hic, 0, lpSrcFmt, lpB, lpTarget, lpI);
		PlayFrame++;
	}
}


