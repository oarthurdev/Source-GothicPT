#define CPARKDXPLAYER_CPP

#include "ParkDXPlayer.h"

#pragma comment(lib,"strmiids.lib")
#pragma comment(lib,"dxguid.lib")

LRESULT CALLBACK DXParkVideoProc(HWND, UINT, WPARAM, LPARAM);


CParkPlayer::CParkPlayer(void)
{
}

CParkPlayer::~CParkPlayer(void)
{
}

void CParkPlayer::InitPlayer(void)
{
	::CoInitialize(NULL);
	pIGraphBuilder = NULL;
	pIMediaControl = NULL;
	pIMediaEventEx = NULL;
	pIVideoWindow = NULL;
	pIBasicAudio = NULL;
	pIBasicVideo = NULL;
	pIMediaSeeking = NULL;
	pIMediaPosition = NULL;
	pIVideoFrameStep = NULL;
}

BOOL CParkPlayer::LoadPlayerFile(HWND PlayhWnd, char *szFileName)
{

	HPlayer = NULL;
	HPlayer = PlayhWnd;

	WCHAR wPath[MAX_PATH];
	MultiByteToWideChar(CP_ACP, 0, szFileName, -1, wPath, MAX_PATH);

	HRESULT hr;
	hr = ::CoCreateInstance(CLSID_FilterGraph, NULL
							, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (LPVOID*)&pIGraphBuilder);
	hr = pIGraphBuilder->RenderFile(wPath, NULL);
	hr = pIGraphBuilder->QueryInterface(IID_IMediaControl, (LPVOID*)&pIMediaControl);
	hr = pIGraphBuilder->QueryInterface(IID_IMediaEventEx, (LPVOID*)&pIMediaEventEx);
	hr = pIGraphBuilder->QueryInterface(IID_IMediaSeeking, (LPVOID*)&pIMediaSeeking);
	hr = pIGraphBuilder->QueryInterface(IID_IMediaPosition, (LPVOID*)&pIMediaPosition);

	hr = pIGraphBuilder->QueryInterface(IID_IVideoWindow, (LPVOID*)&pIVideoWindow);
	hr = pIGraphBuilder->QueryInterface(IID_IBasicVideo, (LPVOID*)&pIBasicVideo);

	hr = pIGraphBuilder->QueryInterface(IID_IBasicAudio, (LPVOID*)&pIBasicAudio);

	if(pIVideoWindow && pIBasicVideo)
	{
		hr = pIVideoWindow->put_Owner((OAHWND)PlayhWnd);
		hr = pIVideoWindow->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS);
	}

	return TRUE;
}



void CParkPlayer::PlayPlayer(void)
{
	pIMediaControl->Run();
	UpdateWindow(HPlayer);
}

void CParkPlayer::PlaySize(int x, int y, int cx, int cy)
{
	HRESULT hr;

	if(pIVideoWindow)
		hr = pIVideoWindow->SetWindowPosition(x, y, cx, cy);

	UpdateWindow(HPlayer);
}

void CParkPlayer::StopPlayer(void)
{
	if(pIMediaControl)
	{
		pIMediaControl->Release();
		pIMediaEventEx->Release();
		pIVideoWindow->Release();
		pIBasicAudio->Release();
		pIBasicVideo->Release();
		pIMediaSeeking->Release();
		pIMediaPosition->Release();

		pIGraphBuilder->Release();
	}
	::CoUninitialize();
}

