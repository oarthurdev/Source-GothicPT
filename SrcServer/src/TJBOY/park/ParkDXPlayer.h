#pragma once
#ifndef __PARKDXPLAYER_H__
#define __PARKDXPLAYER_H__

#include <windows.h>
#include <dshow.h>


class CParkPlayer
{
public:
	CParkPlayer(void);
	~CParkPlayer(void);

	void InitPlayer(void);
	BOOL LoadPlayerFile(HWND PlayhWnd, char *szFileName);
	void PlaySize(int x, int y, int cx, int cy);
	void PlayPlayer(void);
	void StopPlayer(void);



public:
	HWND HPlayer;

	IGraphBuilder* pIGraphBuilder;
	IMediaControl* pIMediaControl;
	IMediaEventEx* pIMediaEventEx;
	IVideoWindow* pIVideoWindow;
	IBasicAudio* pIBasicAudio;
	IBasicVideo* pIBasicVideo;
	IMediaSeeking* pIMediaSeeking;
	IMediaPosition* pIMediaPosition;
	IVideoFrameStep* pIVideoFrameStep;

};
#endif

#ifdef CPARKDXPLAYER_CPP
CParkPlayer ParkDXPlay;
#else
extern CParkPlayer ParkDXPlay;
#endif