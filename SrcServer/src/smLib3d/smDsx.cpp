#include <math.h>
#include <stdio.h>

#include "smd3d.h"



static LPDEVICEDESC	lpDeviceDesc = NULL;


RenderDevice renderDevice;


extern int ParkPlaying;
extern RECT ParkPlayRect;

extern HWND hwnd;
extern HWND hFocusWnd;

extern DWORD smBackColor;

static DWORD FlagsToBitDepth(DWORD dwFlags)
{
	if(dwFlags & DDBD_1)
		return 1L;
	else if(dwFlags & DDBD_2)
		return 2L;
	else if(dwFlags & DDBD_4)
		return 4L;
	else if(dwFlags & DDBD_8)
		return 8L;
	else if(dwFlags & DDBD_16)
		return 16L;
	else if(dwFlags & DDBD_24)
		return 24L;
	else if(dwFlags & DDBD_32)
		return 32L;
	else
		return 0L;
}


HRESULT WINAPI DeviceEnumCallback(LPGUID lpGuid, LPSTR lpDeviceDescription, LPSTR lpDeviceName, LPD3DDEVICEDESC lpD3DHWDeviceDesc, LPD3DDEVICEDESC lpD3DHELDeviceDesc, LPVOID lpUserArg)
{
	if(!lpUserArg)
		return DDENUMRET_OK;


	LPDEVICEDESC desc, *lpDesc = (LPDEVICEDESC *)lpUserArg;
	if(!*lpDesc)
		desc = *lpDesc = renderDevice.CreateDevice();
	else
		desc = renderDevice.CreateDevice(*lpDesc);


	memcpy(&desc->guid, lpGuid, sizeof(GUID));


	strcpy(desc->szName, lpDeviceName);
	strcpy(desc->szDesc, lpDeviceDescription);



	if(lpD3DHWDeviceDesc->dcmColorModel)
	{
		desc->bIsHardware = TRUE;
		memcpy(&desc->Desc, lpD3DHWDeviceDesc, sizeof(D3DDEVICEDESC));
	}
	else
	{
		desc->bIsHardware = FALSE;
		memcpy(&desc->Desc, lpD3DHELDeviceDesc, sizeof(D3DDEVICEDESC));
	}

	return DDENUMRET_OK;
}


static HRESULT WINAPI EnumZBufferCallback(DDPIXELFORMAT *DDP_Format, VOID *DDP_Desired)
{
	if(DDP_Format->dwFlags == DDPF_ZBUFFER)
	{
		memcpy(DDP_Desired, DDP_Format, sizeof(DDPIXELFORMAT));
		return D3DENUMRET_CANCEL;
	}
	return D3DENUMRET_OK;
}

RenderDevice::RenderDevice()
{
	smFlipCount = 0;

	lpD3DDeviceDesc = NULL;


	lpDD = NULL;
	lpDDSPrimary = NULL;
	lpDDSBack = NULL;
	lpDDClipper = NULL;


	lpD3D = NULL;
	lpD3DDevice = NULL;
	lpD3DViewport = NULL;
	lpDDSZBuffer = NULL;
}

RenderDevice::~RenderDevice()
{

}


LPDEVICEDESC RenderDevice::FindDevice(LPDEVICEDESC lpDesc, LPGUID lpGuid)
{
	LPDEVICEDESC desc = lpDesc;

	while(desc)
	{
		if(!memcmp(lpGuid, &desc->guid, sizeof(GUID)))
			break;

		desc = desc->lpNext;
	}

	return desc;
}

LPDEVICEDESC RenderDevice::FindBestDevice(LPDEVICEDESC lpDesc)
{
	LPDEVICEDESC desc = FindDevice(lpDesc, (LPGUID)&IID_IDirect3DHALDevice);

	if(!desc)
		desc = FindDevice(lpDesc, (LPGUID)&IID_IDirect3DMMXDevice);

	if(!desc)
		desc = FindDevice(lpDesc, (LPGUID)&IID_IDirect3DRGBDevice);

	return desc;
}

LPDEVICEDESC RenderDevice::CreateDevice()
{
	LPDEVICEDESC desc = new DEVICEDESC;
	if(!desc)
		return NULL;

	ZeroMemory(desc, sizeof(DEVICEDESC));

	return desc;
}

LPDEVICEDESC RenderDevice::CreateDevice(LPDEVICEDESC lpDesc)
{
	if(!lpDesc)
		return CreateDevice();

	LPDEVICEDESC desc = new DEVICEDESC;
	if(!desc)
		return NULL;

	ZeroMemory(desc, sizeof(DEVICEDESC));

	LPDEVICEDESC lastDesc = lpDesc;
	while(lastDesc->lpNext)
		lastDesc = lastDesc->lpNext;

	lastDesc->lpNext = desc;

	return desc;
}


BOOL RenderDevice::CreateD3D()
{
	LPDIRECTDRAW lpdd;

	HRESULT hresult = DirectDrawCreate(NULL, &lpdd, NULL);
	if(hresult != DD_OK)
	{
		//Utils_//LOG(LOG_ERROR, "DirectDrawCreate");
		return FALSE;
	}


	hresult = lpdd->QueryInterface(IID_IDirectDraw4, (LPVOID*)&lpDD);
	if(hresult != DD_OK)
	{
		//Utils_//LOG(LOG_ERROR, "lpdd->QueryInterface");
		return FALSE;
	}


	lpdd->Release();


	hresult = lpDD->QueryInterface(IID_IDirect3D3, (LPVOID*)&lpD3D);
	if(hresult != DD_OK)
	{
		//Utils_//LOG(LOG_ERROR, "lpDD3->QueryInterface");
		return FALSE;
	}

	hresult = lpD3D->EnumDevices(DeviceEnumCallback, (LPVOID)&lpDeviceDesc);
	if(hresult != DD_OK)
	{
		//Utils_//LOG(LOG_ERROR, "lpD3D->EnumDevices");
		return FALSE;
	}

	lpD3DDeviceDesc = FindBestDevice(lpDeviceDesc);
	if(!lpD3DDeviceDesc)
		return FALSE;

	return TRUE;
}


void RenderDevice::ReleaseD3D()
{


	DestroyDevice(lpDeviceDesc);




	ReleaseNewRenderTarget();



	if(lpD3DViewport)
	{

		lpD3DDevice->DeleteViewport(lpD3DViewport);

		lpD3DViewport->Release();
		lpD3DViewport = NULL;
	}


	if(lpD3DDevice)
	{
		lpD3DDevice->Release();
		lpD3DDevice = NULL;
	}



	if(lpDDSZBuffer)
	{

		if(lpDDSBack)
			lpDDSBack->DeleteAttachedSurface(0L, lpDDSZBuffer);

		lpDDSZBuffer->Release();
		lpDDSZBuffer = NULL;
	}



	if(lpDDSBack)
	{
		lpDDSBack->Release();
		lpDDSBack = NULL;
	}



	if(lpD3D)
	{
		lpD3D->Release();
		lpD3D = NULL;
	}


	if(lpDDSPrimary)
	{
		lpDDSPrimary->Release();
		lpDDSPrimary = NULL;
	}


	if(lpDD)
	{

		lpDD->RestoreDisplayMode();

		lpDD->Release();
		lpDD = NULL;
	}
}


void RenderDevice::DestroyDevice(LPDEVICEDESC lpDesc)
{
	LPDEVICEDESC desc;

	while(lpDesc->lpNext)
	{
		desc = lpDesc->lpNext;
		lpDesc->lpNext = lpDesc->lpNext->lpNext;

		delete[] desc;
	}

	delete[] lpDesc;
}


BOOL RenderDevice::SetDisplayMode(HWND hWnd, DWORD Width, DWORD Height, DWORD BPP){
	return NULL;
}


BOOL RenderDevice::SetDisplayModeWin(HWND hWnd, DWORD Width, DWORD Height, DWORD BPP)
{
	//Utils_//LOG(LOG_DEBUG, "D3DX SetDisplayModeWin()  Width(%d)  Height(%d)  Color(%d)", Width, Height, BPP);

	if(!lpDD) return FALSE;

	HRESULT hresult = lpDD->SetCooperativeLevel(hWnd, DDSCL_NORMAL);

	if(hresult != DD_OK)
	{
		//Utils_//LOG(LOG_ERROR, "lpDD->SetCooperativeLevel");
		return FALSE;
	}

	DDSURFACEDESC2 ddsd;
	ZeroMemory(&ddsd, sizeof(ddsd));

	ddsd.dwSize = sizeof(ddsd);
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_3DDEVICE;

	hresult = CreateSurface(&ddsd, &lpDDSPrimary, NULL);
	if(hresult != DD_OK)
	{
		//Utils_//LOG(LOG_ERROR, "CreateSurface(lpDDSPrimary)");
		return FALSE;
	}
	
	RECT lpRect;
	GetWindowRect(GetDesktopWindow(), &lpRect);
	int w = lpRect.right - lpRect.left;
	int h = lpRect.bottom - lpRect.top;


	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE | DDSCAPS_VIDEOMEMORY;
	ddsd.dwWidth = w;
	ddsd.dwHeight = h;

	hresult = CreateSurface(&ddsd, &lpDDSBack, NULL);

	if(hresult != DD_OK)
	{
		//Utils_//LOG(LOG_ERROR, "CreateSurface");
		return FALSE;
	}

	lpDD->CreateClipper(0, &lpDDClipper, NULL);
	lpDDClipper->SetHWnd(0, hWnd);
	lpDDSPrimary->SetClipper(lpDDClipper);
	lpDDClipper->Release();


	DDPIXELFORMAT	ddpx;

	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS |
		DDSD_WIDTH |
		DDSD_HEIGHT |
		DDSD_PIXELFORMAT;

	ddsd.dwWidth = w;
	ddsd.dwHeight = h;

	lpD3D->EnumZBufferFormats(lpD3DDeviceDesc->guid, EnumZBufferCallback, (VOID *)&ddpx);

	memcpy(&ddsd.ddpfPixelFormat, &ddpx, sizeof(DDPIXELFORMAT));



	::CopyMemory(&g_ddpfPixelFormatZ, &ddsd.ddpfPixelFormat, sizeof(g_ddpfPixelFormatZ));



	if(lpD3DDeviceDesc->bIsHardware)
		ddsd.ddsCaps.dwCaps = DDSCAPS_ZBUFFER | DDSCAPS_VIDEOMEMORY;
	else
		ddsd.ddsCaps.dwCaps = DDSCAPS_ZBUFFER | DDSCAPS_SYSTEMMEMORY;


	hresult = CreateSurface(&ddsd, &lpDDSZBuffer, NULL);
	if(hresult != DD_OK)
	{
		//Utils_//LOG(LOG_ERROR, "CreateSurface(lpDDSZBuffer)");
		return FALSE;
	}


	hresult = lpDDSBack->AddAttachedSurface(lpDDSZBuffer);
	if(hresult != DD_OK)
	{
		//Utils_//LOG(LOG_ERROR, "lpDDSBack->AddAttachedSurface");
		return FALSE;
	}


	hresult = lpD3D->CreateDevice(lpD3DDeviceDesc->guid,
								  lpDDSBack,
								  &lpD3DDevice,
								  NULL);
	if(hresult != D3D_OK)
	{
		//Utils_//LOG(LOG_ERROR, "lpD3D->CreateDevice");
		return FALSE;
	}


	D3DRect.x1 = 0;
	D3DRect.y1 = 0;
	D3DRect.x2 = w;
	D3DRect.y2 = h;

	return CreateViewport();
}


BOOL RenderDevice::CreateViewport(){
	return NULL;
}


void RenderDevice::InitRender()
{

	lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE);
	lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
	lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZFUNC, D3DCMP_LESSEQUAL);




	lpD3DDevice->SetRenderState(D3DRENDERSTATE_TEXTUREHANDLE, 0);


	lpD3DDevice->SetRenderState(D3DRENDERSTATE_DITHERENABLE, TRUE);

	lpD3DDevice->SetRenderState(D3DRENDERSTATE_TEXTUREADDRESS, D3DTADDRESS_WRAP);
	lpD3DDevice->SetRenderState(D3DRENDERSTATE_TEXTUREPERSPECTIVE, TRUE);


	lpD3DDevice->SetRenderState(D3DRENDERSTATE_TEXTUREMAG, D3DFILTER_LINEAR);
	lpD3DDevice->SetRenderState(D3DRENDERSTATE_TEXTUREMIN, D3DFILTER_LINEAR);

	lpD3DDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE, TRUE);
	lpD3DDevice->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, FALSE);

	lpD3DDevice->SetRenderState(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_MODULATE);

	lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
	lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
	lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);

	smRender.AlphaTestDepth = 60;
	smRender.dwMatDispMask = sMATS_SCRIPT_NOTVIEW;
	smRender.DeviceRendMode = TRUE;
	smRender.ZWriteAuto = FALSE;
}


int RenderDevice::Flip(){
	return NULL;
}

void RenderDevice::updateFrameWin_Video(){}

void RenderDevice::updateFrameWin(){}

bool RenderDevice::autoAdjust(int width, int height)
{
	return true;
}


//bool RenderDevice::autoAdjust(int width, int height)
//{
//	extern BOOL bAdjustWindow;
//	extern void resizeOpening();
//	extern void resizeLogin();
//	extern void resizeSin();
//
//	static int minWidth = 800;
//	static int minHeight = 600;
//	static int maxWidth = 1920;
//	static int maxHeight = 1080;
//
//	if(Settings::getInstance()->getWindowMode())
//	{
//		if(bAdjustWindow)
//		{
//			if(width < minWidth || height < minHeight || width > maxWidth || height > maxHeight)
//			{
//				// Restore 800x600.
//				UINT uWindowStyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
//				SendMessage(hwnd, WM_SYSCOMMAND, SC_RESTORE, 0);
//				SetWindowLong(hwnd, GWL_STYLE, uWindowStyle);
//
//				int X = (maxWidth / 2) - (800 / 2);
//				int Y = (maxHeight / 2) - (600 / 2);
//				RECT Rect = { X, Y, X + 800, Y + 600 };
//				AdjustWindowRect(&Rect, uWindowStyle, FALSE);
//				SetWindowPos(hwnd, HWND_NOTOPMOST, Rect.left, Rect.top,
//					Rect.right - Rect.left, Rect.bottom - Rect.top, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
//
//				width = 800;
//				height = 600;
//			}
//
//			Settings::getInstance()->setWidth(width);
//			Settings::getInstance()->setHeight(height);
//
//			D3DRect.x1 = 0;
//			D3DRect.y1 = 0;
//			D3DRect.x2 = Settings::getInstance()->getWidth();
//			D3DRect.y2 = Settings::getInstance()->getHeight();
//			
//			//Obtêm o endereço das variáveis.
//			extern float g_fWinSizeRatio_X;
//			extern float g_fWinSizeRatio_Y;
//
//			//Atualiza as variáveis.
//			MidX = Settings::getInstance()->getWidth() / 2;
//			MidY = Settings::getInstance()->getHeight() / 2;
//			g_fWinSizeRatio_X = float(Settings::getInstance()->getWidth()) / 800.f;
//
//			extern int WinSizeX;
//			extern int WinSizeY;
//			WinSizeX = Settings::getInstance()->getWidth();
//			WinSizeY = Settings::getInstance()->getHeight();
//
//			g_fWinSizeRatio_Y = float(Settings::getInstance()->getHeight()) / 600.f;
//
//			SetDxProjection((g_PI / 4.4f), Settings::getInstance()->getWidth(), Settings::getInstance()->getHeight(), 20.f, 4000.f);
//
//			resizeOpening();
//			resizeLogin();
//			resizeSin();
//
//			if(Settings::getInstance()->isWideScreen())
//				viewdistZ = (height * 4) / 3;
//			else
//				viewdistZ = width;
//
//			// widescreen
//			//viewdistZ = (Settings::getInstance()->getHeight() * 4) / 3;
//
//			if(renderDevice.IsDevice())
//			{
//				renderDevice.InitRender();
//			}
//		}
//	}
//
//	return true;
//}

void RenderDevice::ClearViewport(DWORD flags)
{
	lpD3DViewport->Clear2(1UL, &renderDevice.D3DRect, flags, smBackColor, 1, 0L);
}

BOOL RenderDevice::IsDevice()
{
	if(lpD3DDevice)
		return TRUE;

	return FALSE;
}

void RenderDevice::SetRenderState(_D3DRENDERSTATETYPE stateType, DWORD value)
{
	if(lpD3DDevice)
	{
		lpD3DDevice->SetRenderState(stateType, value);
	}
}

void RenderDevice::SetTextureStageState(DWORD stage, D3DTEXTURESTAGESTATETYPE type, DWORD value)
{
	lpD3DDevice->SetTextureStageState(stage, type, value);
}

HRESULT RenderDevice::EnumTextureFormats(LPD3DENUMPIXELFORMATSCALLBACK Textures, LPVOID TexturePixelFormat)
{
	return lpD3DDevice->EnumTextureFormats(Textures, TexturePixelFormat);
}

HRESULT RenderDevice::SetTransform(D3DTRANSFORMSTATETYPE type, LPD3DMATRIX matrix)
{
	return lpD3DDevice->SetTransform(type, matrix);
}

HRESULT  RenderDevice::SetTexture(DWORD sampler, DRZTEXTURE2 texture)
{
	return lpD3DDevice->SetTexture(sampler, texture);
}

HRESULT RenderDevice::SetRenderTarget(DIRECTDRAWSURFACE pRenderTarget, DWORD RenderTargetIndex)
{
	return lpD3DDevice->SetRenderTarget(pRenderTarget, RenderTargetIndex);
}

HRESULT RenderDevice::GetRenderTarget(DIRECTDRAWSURFACE* renderTarget)
{
	return lpD3DDevice->GetRenderTarget(renderTarget);

}

HRESULT RenderDevice::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, DWORD VertexTypeDesc, LPVOID Vertices, DWORD VertexCount, DWORD Flags)
{
	return lpD3DDevice->DrawPrimitive(PrimitiveType, VertexTypeDesc, Vertices, VertexCount, Flags);
}

HRESULT RenderDevice::Blt(DIRECTDRAWSURFACE targetSurface, LPRECT lpDestRect, DIRECTDRAWSURFACE srcSurface, LPRECT srcRect, DWORD dwFlags, LPDDBLTFX  lpDDBltFx)
{
	HRESULT hr = NULL;

	if(targetSurface)
	{
		hr = targetSurface->Blt(lpDestRect, srcSurface, srcRect, dwFlags, lpDDBltFx);

		if(FAILED(hr))
		{
			//Utils_//LOG(LOG_ERROR, "DirectX Error - Blt() failed");
		}
	}

	return hr;
}

HRESULT RenderDevice::BltFast(DIRECTDRAWSURFACE targetSurface, DWORD dwX, DWORD dwY, DIRECTDRAWSURFACE srcSurface, LPRECT srcRect, DWORD dwFlags)
{
	HRESULT hr = targetSurface->BltFast(dwX, dwY, srcSurface, srcRect, dwFlags);

	return hr;
}


HRESULT RenderDevice::CreateSurface(LPDDSURFACEDESC2 SurfaceDesc, DIRECTDRAWSURFACE* surface, IUnknown* UnkPointer)
{
	return lpDD->CreateSurface(SurfaceDesc, surface, UnkPointer);
}

HRESULT RenderDevice::BeginScene()
{
	if(lpD3DDevice)
	{
		return lpD3DDevice->BeginScene();
	}

	return NULL;

}

HRESULT RenderDevice::EndScene()
{
	if(lpD3DDevice)
	{
		return lpD3DDevice->EndScene();
	}

	return NULL;
}

