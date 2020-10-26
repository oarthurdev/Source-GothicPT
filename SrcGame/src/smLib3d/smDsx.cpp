#include <math.h>
#include <stdio.h>

#include "smd3d.h"


extern HWND hwnd;

#define WINMODE			01



int WindowMode = WINMODE;
int	smTextureBPP = 16;

int smScreenWidth, smScreenHeight;
int smFlipCount = 0;
bool MagFilter = false;






LPDIRECT3D9             lpD3D = nullptr;
LPDIRECT3DDEVICE9       d3ddev = nullptr;
D3DPRESENT_PARAMETERS   d3dpp = { 0 };
int                     FontType = 0;
int                     FontOpacity = 255;
extern ID3DXFont *      Font = nullptr;
extern ID3DXFont *      FontBold = nullptr;
extern ID3DXFont *      FontTitle = nullptr;
ID3DXFont *      FontDamageShadow = nullptr;
extern D3DCOLOR         FontColor = { 0 };

int MESSAGE(char *t)
{
	FILE *fp;
	fp = fopen("error.log", "wb");
	if (fp != NULL) {
		fwrite(t, lstrlen(t), 1, fp);
		fclose(fp);
	}

	return NULL;
}


BOOL CreateD3D()
{
	if (FAILED(lpD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		MessageBox(0, "Could not Create Direct3D", "Engine Graphic", 0);
		return FALSE;
	}

	return TRUE;
}


void ReleaseD3D()
{
	if (lpD3D)
	{
		lpD3D->Release();
		lpD3D = NULL;
	}

	if (d3ddev)
	{
		d3ddev->Release();
		d3ddev = NULL;
	}

	if (Font)
	{
		Font->Release();
		Font = NULL;
	}

	if (FontBold)
	{
		FontBold->Release();
		FontBold = NULL;
	}

	if (FontTitle)
	{
		FontTitle->Release();
		FontTitle = NULL;
	}

	if (FontDamageShadow)
	{
		FontDamageShadow->Release();
	}

}

BOOL SetDisplayMode(HWND hWnd, DWORD Width, DWORD Height, DWORD BPP)
{
	D3DCAPS9  d3dCaps;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.BackBufferWidth = Width;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.BackBufferHeight = Height;
	d3dpp.hDeviceWindow = hWnd;

	if (BPP == 16)
		d3dpp.BackBufferFormat = D3DFMT_X4R4G4B4;
	if (BPP == 32)
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;

	smTextureBPP = BPP;
	smScreenWidth = Width;
	smScreenHeight = Height;

#ifdef MULTI_THREADED_LOADING
	DWORD dwBehaviourFlags = D3DCREATE_FPU_PRESERVE | D3DCREATE_MULTITHREADED;
#else
	DWORD dwBehaviourFlags = D3DCREATE_FPU_PRESERVE;
#endif

	if (WindowMode)
	{
		d3dpp.Windowed = true;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	}
	else
	{
		d3dpp.Windowed = false;
		d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	}

	HRESULT hr = 0;
	if (FAILED(hr = lpD3D->GetDeviceCaps(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		&d3dCaps)))
	{
		return FALSE;
	}

	if (d3dCaps.DevCaps & D3DDEVCAPS_PUREDEVICE)
	{
		dwBehaviourFlags |= D3DCREATE_PUREDEVICE;
	}

	if ((d3dCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) && (d3dCaps.VertexProcessingCaps != 0))
	{
		dwBehaviourFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		dwBehaviourFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	if (d3dCaps.PresentationIntervals & D3DPRESENT_INTERVAL_IMMEDIATE)
	{
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}

	HRESULT Result = 0;
	Result = lpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, dwBehaviourFlags, &d3dpp, &d3ddev);
	if (FAILED(Result))
	{
		lpD3D->Release();
		lpD3D = NULL;

		if (Result == D3DERR_DEVICELOST)
			MessageBox(NULL, "D3DERR_DEVICELOST", "D3DERR_DEVICELOST", MB_OK);
		if (Result == D3DERR_INVALIDCALL)
			MessageBox(NULL, "D3DERR_DEVICELOST", "D3DERR_DEVICELOST", MB_OK);
		if (Result == D3DERR_NOTAVAILABLE)
			MessageBox(NULL, "D3DERR_NOTAVAILABLE", "D3DERR_NOTAVAILABLE", MB_OK);
		if (Result == D3DERR_OUTOFVIDEOMEMORY)
			MessageBox(NULL, "D3DERR_OUTOFVIDEOMEMORY", "D3DERR_OUTOFVIDEOMEMORY", MB_OK);
		return false;
	}

D3DXCreateFont(d3ddev, 25, 0, FW_MEDIUM, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Noto Sans", &FontDamageShadow);

	return TRUE;
}

void OnLostDevice()
{
	if (Font)
		Font->OnLostDevice();
	if (FontBold)
		FontBold->OnLostDevice();
	if (FontTitle)
		FontTitle->OnLostDevice();
	if (FontDamageShadow)
		FontDamageShadow->OnLostDevice();
}

void OnResetDevice()
{
	if (Font)
		Font->OnResetDevice();
	if (FontBold)
		FontBold->OnResetDevice();
	if (FontTitle)
		FontTitle->OnResetDevice();
	if (FontDamageShadow)
		FontDamageShadow->OnResetDevice();
}

void RestoreDevice()
{
	if (d3ddev)
	{
		HRESULT Result = d3ddev->TestCooperativeLevel();

		switch (Result)
		{
		case D3DERR_DEVICELOST:
			OnLostDevice();
			break;
		case D3DERR_DEVICENOTRESET:
			OnLostDevice();
			Result = d3ddev->Reset(&d3dpp);
			InitRender();
			OnResetDevice();
			break;
		}
	}
}


void InitRender()
{
	d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);
	d3ddev->SetRenderState(D3DRS_CLIPPING, FALSE);
	d3ddev->SetRenderState(D3DRS_CULLMODE, 2);
	d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);
	d3ddev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	d3ddev->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	d3ddev->SetRenderState(D3DRS_LASTPIXEL, FALSE);
	d3ddev->SetRenderState(D3DRS_DITHERENABLE, TRUE);
	d3ddev->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	d3ddev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	d3ddev->SetRenderState(D3DRS_ALPHAFUNC, D3DBLEND_DESTALPHA);
	d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	for (int cnt = 0; cnt < 8; cnt++)
	{
		d3ddev->SetSamplerState(cnt, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		d3ddev->SetSamplerState(cnt, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		d3ddev->SetSamplerState(cnt, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
		d3ddev->SetSamplerState(cnt, D3DSAMP_ADDRESSU, D3DTEXF_POINT);
		d3ddev->SetSamplerState(cnt, D3DSAMP_ADDRESSV, D3DTEXF_POINT);
		d3ddev->SetTexture(cnt, 0);
	}
	smRender.AlphaTestDepth = 60;
	smRender.dwMatDispMask = sMATS_SCRIPT_NOTVIEW;
	smRender.ZWriteAuto = FALSE;
}

extern DWORD smBackColor;


void BeginRender()
{
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
	d3ddev->BeginScene();
}


void EndRender()
{
	d3ddev->EndScene();
	d3ddev->Present(NULL, NULL, NULL, NULL);
}


void DrawTexture(LPDIRECT3DTEXTURE9 Texture, D3DTLVERTEX * Vertex, int AlphaBlend)
{
	d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	d3ddev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	d3ddev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	if (AlphaBlend)
	{
		d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	}
	else

	{
		d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	}

	if (MagFilter)
	{
		d3ddev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		d3ddev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	}
	else
	{
		d3ddev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
		d3ddev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	}

	for (int cnt = 0; cnt < 8; cnt++)
		d3ddev->SetTexture(cnt, 0);
	d3ddev->SetTexture(0, Texture);
	d3ddev->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1);
     
	d3ddev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, Vertex, sizeof(D3DTLVERTEX));
	if (!MagFilter)

	{
		d3ddev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		d3ddev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	}


	d3ddev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
}

void DrawTexture2D(LPDIRECT3DTEXTURE9 lpTexture, RECT destinationRect, RECT sourceRect, int alphaBlend)
{
	if (destinationRect.right > destinationRect.left
		&& destinationRect.bottom > destinationRect.top
		&& destinationRect.right >= 0
		&& destinationRect.bottom >= 0
		&& destinationRect.left < smScreenWidth
		&& destinationRect.top < smScreenHeight
		&& sourceRect.right > sourceRect.left
		&& sourceRect.bottom > sourceRect.top)
	{
		D3DSURFACE_DESC Desc;
		if (lpTexture)
			lpTexture->GetLevelDesc(0, &Desc);

		float u1, v1, u2, v2;

		if (lpTexture)
		{
			u1 = ((float)sourceRect.left + 0.5f) / Desc.Width;
			v1 = ((float)sourceRect.top + 0.5f) / Desc.Height;
			u2 = u1 + ((float)sourceRect.right - sourceRect.left) / Desc.Width;
			v2 = v1 + ((float)sourceRect.bottom - sourceRect.top) / Desc.Height;
		}
		else
		{
			u1 = 0.0f;
			v1 = 0.0f;
			u2 = 1.0f;
			v2 = 1.0f;
		}

		D3DTLVERTEX Vertices[4] =
		{
			{ (float)destinationRect.left, (float)destinationRect.top, 0.0f, 1.0f, D3DCOLOR_XRGB(255,255,255), 0, u1, v1 },
			{ (float)destinationRect.right, (float)destinationRect.top, 0.0f, 1.0f, D3DCOLOR_XRGB(255,255,255), 0, u2, v1 },
			{ (float)destinationRect.left, (float)destinationRect.bottom, 0.0f, 1.0f, D3DCOLOR_XRGB(255,255,255), 0, u1, v2 },
			{ (float)destinationRect.right,(float)destinationRect.bottom, 0.0f, 1.0f, D3DCOLOR_XRGB(255,255,255), 0, u2, v2 },
		};

		DrawTexture(lpTexture ? lpTexture : nullptr, Vertices, alphaBlend);
	}
}
