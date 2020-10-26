
#include "smd3d.h"
#include "Log\Log.h"

DDPIXELFORMAT						g_ddpfPixelFormatZ;

static LPDIRECT3DTEXTURE9			s_lpDDS_NewTarget_Primary;
static LPDIRECT3DTEXTURE9					s_lpD3D_NewTargetTexture_Primary;
static LPDIRECT3DTEXTURE9			s_lpDDS_NewTargetZ_Primary;

static LPDIRECT3DTEXTURE9			s_lpDDS_NewTarget_Back;
static LPDIRECT3DTEXTURE9					s_lpD3D_NewTargetTexture_Back;
static LPDIRECT3DTEXTURE9			s_lpDDS_NewTargetZ_Back;

static LPDIRECT3DTEXTURE9			s_lpDDS_NewTarget_Rate_Back;
static LPDIRECT3DTEXTURE9					s_lpD3D_NewTargetTexture_Rate_Back;
static LPDIRECT3DTEXTURE9			s_lpDDS_NewTargetZ_Rate_Back;


static DRZD3DTLVERTEX				s_TLVertex_NewTarget[4];
static DRZD3DTLVERTEX				s_TLVertex_RateZoomIn[4];
static DRZD3DTLVERTEX				s_TLVertex_RateZoomOut[4];


static eNEW_RENDER_TARGET_TYPE		s_eWorkTarget = ORG_TARGET;
static DWORD						s_dwIsBoolFilterEffect;
static DWORD						s_dwFilterEffectWork;
static DWORD						s_dwFilterEffectRGBAlpha[3];
static int							s_isFirstMotionBlur;

static DWORD						s_dwBlurRGBAlpha = D3DCOLOR_RGBA(255, 255, 255, 255 / 4);
static float						s_texNum = 1.f / 1024.f;




static int  CreateFilterEffectTLVertex(void);
static void RenderOriginalDraw(LPDIRECT3DTEXTURE9 lpD3D_Texture, DRZD3DTLVERTEX *lpTLVertexBuff);
static void RenderAlphaDraw(LPDIRECT3DTEXTURE9 lpD3D_Texture, DRZD3DTLVERTEX *lpTLVertexBuff, DWORD dwRGBAlpha);
static void RenderBlurDraw(LPDIRECT3DTEXTURE9 lpD3D_Texture, DRZD3DTLVERTEX *lpTLVertexBuff);








int CreateNewRenderTarget(void)
{
	HRESULT hresult;
	if(CreateFilterEffectTLVertex() == FALSE || s_lpDDS_NewTarget_Primary || s_lpDDS_NewTarget_Back)
		return 0;

	s_dwIsBoolFilterEffect = 0;

	if(d3ddev->lpDD == NULL || d3ddev == NULL || d3ddev->D3DRect.x2 > 1024 || d3ddev->D3DRect.y2 > 1024)
		return -1;

	if(d3ddev->GetDeviceDesc_MaxTextureHeight() < 1024 || d3ddev->GetDeviceDesc_MaxTextureWidth() < 1024)
		return -2;



	LPDIRECT3DTEXTURE9 lpDDS4;
	d3ddev->GetRenderTarget(&lpDDS4);
	lpDDS4->Release();

	DDSURFACEDESC2 ddsd;
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	ddsd.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
	lpDDS4->GetSurfaceDesc(&ddsd);

	ddsd.dwWidth = 1024;
	ddsd.dwHeight = 1024;

	ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_3DDEVICE;
	if(d3ddev->GetDeviceDesc_IsHardware())
		ddsd.ddsCaps.dwCaps |= DDSCAPS_VIDEOMEMORY;
	else
		ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;



	hresult = d3ddev->CreateSurface(&ddsd, &s_lpDDS_NewTarget_Primary, NULL);
	if(hresult != DD_OK)
	{
		ReleaseNewRenderTarget();
		Log::getInstance()->output(LOG_ERROR, "CreateNewRenderTarget() Error. CreateSurface() #1. NEW Target\n");
		return -3;
	}

	hresult = s_lpDDS_NewTarget_Primary->QueryInterface(IID_IDirect3DTexture2, (LPVOID*)&s_lpD3D_NewTargetTexture_Primary);
	if(hresult != DD_OK)
	{
		ReleaseNewRenderTarget();
		Log::getInstance()->output(LOG_ERROR, "CreateNewRenderTarget() Error. QueryInterface() #1. NEW Target TEXTURE\n");
		return -3;
	}



	hresult = d3ddev->CreateSurface(&ddsd, &s_lpDDS_NewTarget_Back, NULL);
	if(hresult != DD_OK)
	{
		ReleaseNewRenderTarget();
		Log::getInstance()->output(LOG_ERROR, "CreateNewRenderTarget() Error. CreateSurface() #2. NEW Target\n");
		return -3;
	}

	hresult = s_lpDDS_NewTarget_Back->QueryInterface(IID_IDirect3DTexture2, (LPVOID*)&s_lpD3D_NewTargetTexture_Back);
	if(hresult != DD_OK)
	{
		ReleaseNewRenderTarget();
		Log::getInstance()->output(LOG_ERROR, "CreateNewRenderTarget() Error. QueryInterface() #2. NEW Target TEXTURE\n");
		return -3;
	}



	DDSURFACEDESC2 ddsdRate;
	CopyMemory(&ddsdRate, &ddsd, sizeof(ddsdRate));
	ddsdRate.dwWidth = 256;
	ddsdRate.dwHeight = 256;

	hresult = d3ddev->CreateSurface(&ddsdRate, &s_lpDDS_NewTarget_Rate_Back, NULL);
	if(hresult != DD_OK)
	{
		ReleaseNewRenderTarget();
		Log::getInstance()->output(LOG_ERROR, "CreateNewRenderTarget() Error. CreateSurface() #3. NEW Target\n");
		return -3;
	}

	hresult = s_lpDDS_NewTarget_Rate_Back->QueryInterface(IID_IDirect3DTexture2, (LPVOID*)&s_lpD3D_NewTargetTexture_Rate_Back);
	if(hresult != DD_OK)
	{
		ReleaseNewRenderTarget();
		Log::getInstance()->output(LOG_ERROR, "CreateNewRenderTarget() Error. QueryInterface() #3. NEW Target TEXTURE\n");
		return -3;
	}

	DDSURFACEDESC2 ddsdZ;
	ZeroMemory(&ddsdZ, sizeof(ddsdZ));
	ddsdZ.dwSize = sizeof(ddsdZ);
	ddsdZ.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_PIXELFORMAT;
	ddsdZ.dwWidth = ddsd.dwWidth;
	ddsdZ.dwHeight = ddsd.dwHeight;

	::CopyMemory(&ddsdZ.ddpfPixelFormat, &g_ddpfPixelFormatZ, sizeof(g_ddpfPixelFormatZ));
	if(d3ddev->GetDeviceDesc_IsHardware())
		ddsdZ.ddsCaps.dwCaps = DDSCAPS_ZBUFFER | DDSCAPS_VIDEOMEMORY;
	else
		ddsdZ.ddsCaps.dwCaps = DDSCAPS_ZBUFFER | DDSCAPS_SYSTEMMEMORY;



	hresult = d3ddev->CreateSurface(&ddsdZ, &s_lpDDS_NewTargetZ_Primary, NULL);
	if(hresult != DD_OK)
	{
		ReleaseNewRenderTarget();
		Log::getInstance()->output(LOG_ERROR, "CreateNewRenderTarget() Error. CreateSurface() #1. Z Buffer\n");
		return -3;
	}

	hresult = s_lpDDS_NewTarget_Primary->AddAttachedSurface(s_lpDDS_NewTargetZ_Primary);
	if(hresult != DD_OK)
	{
		ReleaseNewRenderTarget();
		Log::getInstance()->output(LOG_ERROR, "CreateNewRenderTarget() Error. AddAttachedSurface() #1.\n");
		return -3;
	}



	hresult = d3ddev->CreateSurface(&ddsdZ, &s_lpDDS_NewTargetZ_Back, NULL);
	if(hresult != DD_OK)
	{
		ReleaseNewRenderTarget();
		Log::getInstance()->output(LOG_ERROR, "CreateNewRenderTarget() Error. CreateSurface() #2. Z Buffer\n");
		return -3;
	}

	hresult = s_lpDDS_NewTarget_Back->AddAttachedSurface(s_lpDDS_NewTargetZ_Back);
	if(hresult != DD_OK)
	{
		ReleaseNewRenderTarget();
		Log::getInstance()->output(LOG_ERROR, "CreateNewRenderTarget() Error. AddAttachedSurface() #2.\n");
		return -3;
	}



	DDSURFACEDESC2 ddsdZRate;
	CopyMemory(&ddsdZRate, &ddsdZ, sizeof(ddsdZRate));
	ddsdZRate.dwWidth = 256;
	ddsdZRate.dwHeight = 256;

	hresult = d3ddev->CreateSurface(&ddsdZRate, &s_lpDDS_NewTargetZ_Rate_Back, NULL);
	if(hresult != DD_OK)
	{
		ReleaseNewRenderTarget();
		Log::getInstance()->output(LOG_ERROR, "CreateNewRenderTarget() Error. CreateSurface() #3. Z Buffer\n");
		return -3;
	}

	hresult = s_lpDDS_NewTarget_Rate_Back->AddAttachedSurface(s_lpDDS_NewTargetZ_Rate_Back);
	if(hresult != DD_OK)
	{
		ReleaseNewRenderTarget();
		Log::getInstance()->output(LOG_ERROR, "CreateNewRenderTarget() Error. AddAttachedSurface() #3.\n");
		return -3;
	}



	hresult = d3ddev->SetRenderTarget(d3ddev->lpDDSBack, 0L);
	if(hresult != DD_OK)
	{
		ReleaseNewRenderTarget();
		Log::getInstance()->output(LOG_ERROR, "CreateNewRenderTarget() Error. ChangeRenderTarget().\n");
		return -4;
	}

	s_dwIsBoolFilterEffect = 1;
	return 1;
}








void ReleaseNewRenderTarget(void)
{

	if(s_lpD3D_NewTargetTexture_Back)
	{
		s_lpD3D_NewTargetTexture_Back->Release();
		s_lpD3D_NewTargetTexture_Back = NULL;
	}

	if(s_lpDDS_NewTargetZ_Back)
	{
		if(s_lpDDS_NewTarget_Back)
			s_lpDDS_NewTarget_Back->DeleteAttachedSurface(0L, s_lpDDS_NewTargetZ_Back);
		s_lpDDS_NewTargetZ_Back->Release();
		s_lpDDS_NewTargetZ_Back = NULL;
	}

	if(s_lpDDS_NewTarget_Back)
	{
		s_lpDDS_NewTarget_Back->Release();
		s_lpDDS_NewTarget_Back = NULL;
	}


	if(s_lpD3D_NewTargetTexture_Rate_Back)
	{
		s_lpD3D_NewTargetTexture_Rate_Back->Release();
		s_lpD3D_NewTargetTexture_Rate_Back = NULL;
	}

	if(s_lpDDS_NewTargetZ_Rate_Back)
	{
		if(s_lpDDS_NewTarget_Rate_Back)
			s_lpDDS_NewTarget_Rate_Back->DeleteAttachedSurface(0L, s_lpDDS_NewTargetZ_Rate_Back);

		s_lpDDS_NewTargetZ_Rate_Back->Release();
		s_lpDDS_NewTargetZ_Rate_Back = NULL;
	}

	if(s_lpDDS_NewTarget_Rate_Back)
	{
		s_lpDDS_NewTarget_Rate_Back->Release();
		s_lpDDS_NewTarget_Rate_Back = NULL;
	}


	if(s_lpD3D_NewTargetTexture_Primary)
	{
		s_lpD3D_NewTargetTexture_Primary->Release();
		s_lpD3D_NewTargetTexture_Primary = NULL;
	}

	if(s_lpDDS_NewTargetZ_Primary)
	{
		if(s_lpDDS_NewTarget_Primary)
			s_lpDDS_NewTarget_Primary->DeleteAttachedSurface(0L, s_lpDDS_NewTargetZ_Primary);

		s_lpDDS_NewTargetZ_Primary->Release();
		s_lpDDS_NewTargetZ_Primary = NULL;
	}

	if(s_lpDDS_NewTarget_Primary)
	{
		s_lpDDS_NewTarget_Primary->Release();
		s_lpDDS_NewTarget_Primary = NULL;
	}


	s_dwIsBoolFilterEffect = 0;
}








inline int IsCreateNewRenderTarget(void)
{
	return s_dwIsBoolFilterEffect;
}








inline int GetRenderTarget(void)
{
	return s_eWorkTarget;
}








int ChangeRenderTarget(eNEW_RENDER_TARGET_TYPE eRTtype)
{
	if(s_dwIsBoolFilterEffect == 0 || s_eWorkTarget == eRTtype)
		return 0;

	switch(eRTtype)
	{
		case ORG_TARGET:
		d3ddev->SetRenderTarget(d3ddev->lpDDSBack, 0L);
		s_eWorkTarget = eRTtype;
		break;

		case NEW_TARGET_PRIMARY:
		d3ddev->SetRenderTarget(s_lpDDS_NewTarget_Primary, 0L);
		s_eWorkTarget = eRTtype;
		break;

		case NEW_TARGET_BACK:
		d3ddev->SetRenderTarget(s_lpDDS_NewTarget_Back, 0L);
		s_eWorkTarget = eRTtype;
		break;

		case NEW_TARGET_RATE_BACK:
		d3ddev->SetRenderTarget(s_lpDDS_NewTarget_Rate_Back, 0L);
		s_eWorkTarget = eRTtype;
		break;
	}

	return 1;
}








inline int GetFilterEffect(void)
{
	return s_dwFilterEffectWork;
}








void SetFilterEffect(eFILTER_EFFECT_TYPE eFEtype, DWORD dwAlpha)
{
	switch(eFEtype)
	{
		case FILTER_EFFECT_NULL:
		s_dwFilterEffectWork = 0;
		break;

		case FILTER_EFFECT_SET_MOTION_BLUR:
		s_isFirstMotionBlur = 1;
		s_dwFilterEffectWork |= FILTER_EFFECT_SET_MOTION_BLUR;
		s_dwFilterEffectRGBAlpha[FILTER_EFFECT_SET_MOTION_BLUR] = D3DCOLOR_RGBA(255, 255, 255, dwAlpha);
		break;

		case FILTER_EFFECT_SET_BRIGHT_CONTRAST:
		s_dwFilterEffectWork |= FILTER_EFFECT_SET_BRIGHT_CONTRAST;
		s_dwFilterEffectRGBAlpha[FILTER_EFFECT_SET_BRIGHT_CONTRAST] = D3DCOLOR_RGBA(255, 255, 255, dwAlpha);
		break;

		case FILTER_EFFECT_DEL_MOTION_BLUR:
		s_dwFilterEffectWork &= (~FILTER_EFFECT_SET_MOTION_BLUR);
		break;

		case FILTER_EFFECT_DEL_BRIGHT_CONTRAST:
		s_dwFilterEffectWork &= (~FILTER_EFFECT_SET_BRIGHT_CONTRAST);
		break;
	}
}








void SetNewTargetTextureState(void)
{
	d3ddev->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFN_LINEAR);
	d3ddev->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTFN_LINEAR);
	d3ddev->SetTextureStageState(0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
	d3ddev->SetTextureStageState(0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);

	d3ddev->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
	d3ddev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	d3ddev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	d3ddev->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
	d3ddev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	d3ddev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	d3ddev->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	d3ddev->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	d3ddev->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	d3ddev->SetTexture(1, NULL);

	d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	d3ddev->SetRenderState(D3DRS_ZENABLE, FALSE);
	d3ddev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
}








void DefaultsNewTargetTextureState(void)
{
	d3ddev->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFG_POINT);
	d3ddev->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTFG_POINT);
	d3ddev->SetTextureStageState(0, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP);
	d3ddev->SetTextureStageState(0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
}









static int CreateFilterEffectTLVertex(void)
{
	DWORD color = D3DCOLOR_RGBA(255, 255, 255, 255);
	int   width = d3ddev->D3DRect.x2 / 4;
	int   height = d3ddev->D3DRect.y2 / 4;
	int   cnt;

	if(width > 256 || height > 256)
		return FALSE;



	for(cnt = 0; cnt < 4; cnt++)
	{
		s_TLVertex_NewTarget[cnt].sz = 1.f;
		s_TLVertex_NewTarget[cnt].rhw = 1.f;
		s_TLVertex_NewTarget[cnt].color = color;
		s_TLVertex_NewTarget[cnt].specular = 0;
	}

	s_TLVertex_NewTarget[0].sx = -0.5f;
	s_TLVertex_NewTarget[0].sy = -0.5f;
	s_TLVertex_NewTarget[0].tu = 0;
	s_TLVertex_NewTarget[0].tv = 0;

	s_TLVertex_NewTarget[1].sx = -0.5f;
	s_TLVertex_NewTarget[1].sy = float(d3ddev->D3DRect.y2) - 0.5f;
	s_TLVertex_NewTarget[1].tu = 0;
	s_TLVertex_NewTarget[1].tv = float(d3ddev->D3DRect.y2) / 1024.f;

	s_TLVertex_NewTarget[2].sx = float(d3ddev->D3DRect.x2) - 0.5f;
	s_TLVertex_NewTarget[2].sy = -0.5f;
	s_TLVertex_NewTarget[2].tu = float(d3ddev->D3DRect.x2) / 1024.f;
	s_TLVertex_NewTarget[2].tv = 0;

	s_TLVertex_NewTarget[3].sx = float(d3ddev->D3DRect.x2) - 0.5f;
	s_TLVertex_NewTarget[3].sy = float(d3ddev->D3DRect.y2) - 0.5f;
	s_TLVertex_NewTarget[3].tu = float(d3ddev->D3DRect.x2) / 1024.f;
	s_TLVertex_NewTarget[3].tv = float(d3ddev->D3DRect.y2) / 1024.f;



	for(cnt = 0; cnt < 4; cnt++)
	{
		s_TLVertex_RateZoomOut[cnt].sz = 1.f;
		s_TLVertex_RateZoomOut[cnt].rhw = 1.f;
		s_TLVertex_RateZoomOut[cnt].color = color;
		s_TLVertex_RateZoomOut[cnt].specular = 0;
	}


	s_TLVertex_RateZoomOut[0].sx = -0.5f;
	s_TLVertex_RateZoomOut[0].sy = -0.5f;
	s_TLVertex_RateZoomOut[0].tu = 0;
	s_TLVertex_RateZoomOut[0].tv = 0;

	s_TLVertex_RateZoomOut[1].sx = -0.5f;
	s_TLVertex_RateZoomOut[1].sy = float(height) - 0.5f;
	s_TLVertex_RateZoomOut[1].tu = 0;
	s_TLVertex_RateZoomOut[1].tv = float(d3ddev->D3DRect.y2) / 1024.f;

	s_TLVertex_RateZoomOut[2].sx = float(width) - 0.5f;
	s_TLVertex_RateZoomOut[2].sy = -0.5f;
	s_TLVertex_RateZoomOut[2].tu = float(d3ddev->D3DRect.x2) / 1024.f;
	s_TLVertex_RateZoomOut[2].tv = 0;

	s_TLVertex_RateZoomOut[3].sx = float(width) - 0.5f;
	s_TLVertex_RateZoomOut[3].sy = float(height) - 0.5f;
	s_TLVertex_RateZoomOut[3].tu = float(d3ddev->D3DRect.x2) / 1024.f;
	s_TLVertex_RateZoomOut[3].tv = float(d3ddev->D3DRect.y2) / 1024.f;



	for(cnt = 0; cnt < 4; cnt++)
	{
		s_TLVertex_RateZoomIn[cnt].sz = 1.f;
		s_TLVertex_RateZoomIn[cnt].rhw = 1.f;
		s_TLVertex_RateZoomIn[cnt].color = color;
		s_TLVertex_RateZoomIn[cnt].specular = 0;
	}

	s_TLVertex_RateZoomIn[0].sx = -0.5f;
	s_TLVertex_RateZoomIn[0].sy = -0.5f;
	s_TLVertex_RateZoomIn[0].tu = 0;
	s_TLVertex_RateZoomIn[0].tv = 0;

	s_TLVertex_RateZoomIn[1].sx = -0.5f;
	s_TLVertex_RateZoomIn[1].sy = float(d3ddev->D3DRect.y2) - 0.5f;
	s_TLVertex_RateZoomIn[1].tu = 0;
	s_TLVertex_RateZoomIn[1].tv = float(height) / 256.f;

	s_TLVertex_RateZoomIn[2].sx = float(d3ddev->D3DRect.x2) - 0.5f;
	s_TLVertex_RateZoomIn[2].sy = -0.5f;
	s_TLVertex_RateZoomIn[2].tu = float(width) / 256.f;
	s_TLVertex_RateZoomIn[2].tv = 0;

	s_TLVertex_RateZoomIn[3].sx = float(d3ddev->D3DRect.x2) - 0.5f;
	s_TLVertex_RateZoomIn[3].sy = float(d3ddev->D3DRect.y2) - 0.5f;
	s_TLVertex_RateZoomIn[3].tu = float(width) / 256.f;
	s_TLVertex_RateZoomIn[3].tv = float(height) / 256.f;



	return TRUE;
}








static void RenderOriginalDraw(LPDIRECT3DTEXTURE9 lpD3D_Texture, DRZD3DTLVERTEX *lpTLVertexBuff)
{
	d3ddev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	d3ddev->SetTexture(0, lpD3D_Texture);
	d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_TLVERTEX, lpTLVertexBuff, 4, NULL);
}








static void RenderAlphaDraw(LPDIRECT3DTEXTURE9 lpD3D_Texture, DRZD3DTLVERTEX *lpTLVertexBuff, DWORD dwRGBAlpha)
{

	d3ddev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	int   cnt = 0;
	DWORD color[4];

	for(cnt = 0; cnt < 4; cnt++)
	{
		color[cnt] = lpTLVertexBuff[cnt].color;
		lpTLVertexBuff[cnt].color = dwRGBAlpha;
	}


	d3ddev->SetTexture(0, lpD3D_Texture);
	d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_TLVERTEX, lpTLVertexBuff, 4, NULL);


	d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	for(cnt = 0; cnt < 4; cnt++)
		lpTLVertexBuff[cnt].color = color[cnt];
}








static void RenderBlurDraw(LPDIRECT3DTEXTURE9 lpD3D_Texture, DRZD3DTLVERTEX *lpTLVertexBuff)
{

	int   cnt = 0;
	DWORD color[4];
	float uv[4][2];

	for(cnt = 0; cnt < 4; cnt++)
	{
		color[cnt] = lpTLVertexBuff[cnt].color;
		lpTLVertexBuff[cnt].color = s_dwBlurRGBAlpha;

		uv[cnt][0] = lpTLVertexBuff[cnt].tu;
		uv[cnt][1] = lpTLVertexBuff[cnt].tv;
	}


	d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	d3ddev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	d3ddev->SetTexture(0, lpD3D_Texture);


	lpTLVertexBuff[0].tu = uv[0][0] + s_texNum;
	lpTLVertexBuff[0].tv = uv[0][1];
	lpTLVertexBuff[1].tu = uv[1][0] + s_texNum;
	lpTLVertexBuff[1].tv = uv[1][1];
	lpTLVertexBuff[2].tu = uv[2][0] + s_texNum;
	lpTLVertexBuff[2].tv = uv[2][1];
	lpTLVertexBuff[3].tu = uv[3][0] + s_texNum;
	lpTLVertexBuff[3].tv = uv[3][1];
	d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_TLVERTEX, lpTLVertexBuff, 4, NULL);


	d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	lpTLVertexBuff[0].tu = uv[0][0];
	lpTLVertexBuff[0].tv = uv[0][1] + s_texNum;
	lpTLVertexBuff[1].tu = uv[1][0];
	lpTLVertexBuff[1].tv = uv[1][1] + s_texNum;
	lpTLVertexBuff[2].tu = uv[2][0];
	lpTLVertexBuff[2].tv = uv[2][1] + s_texNum;
	lpTLVertexBuff[3].tu = uv[3][0];
	lpTLVertexBuff[3].tv = uv[3][1] + s_texNum;
	d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_TLVERTEX, lpTLVertexBuff, 4, NULL);


	lpTLVertexBuff[0].tu = uv[0][0] - s_texNum;
	lpTLVertexBuff[0].tv = uv[0][1];
	lpTLVertexBuff[1].tu = uv[1][0] - s_texNum;
	lpTLVertexBuff[1].tv = uv[1][1];
	lpTLVertexBuff[2].tu = uv[2][0] - s_texNum;
	lpTLVertexBuff[2].tv = uv[2][1];
	lpTLVertexBuff[3].tu = uv[3][0] - s_texNum;
	lpTLVertexBuff[3].tv = uv[3][1];
	d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_TLVERTEX, lpTLVertexBuff, 4, NULL);


	lpTLVertexBuff[0].tu = uv[0][0];
	lpTLVertexBuff[0].tv = uv[0][1] - s_texNum;
	lpTLVertexBuff[1].tu = uv[1][0];
	lpTLVertexBuff[1].tv = uv[1][1] - s_texNum;
	lpTLVertexBuff[2].tu = uv[2][0];
	lpTLVertexBuff[2].tv = uv[2][1] - s_texNum;
	lpTLVertexBuff[3].tu = uv[3][0];
	lpTLVertexBuff[3].tv = uv[3][1] - s_texNum;
	d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_TLVERTEX, lpTLVertexBuff, 4, NULL);


	d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	for(cnt = 0; cnt < 4; cnt++)
	{
		lpTLVertexBuff[cnt].color = color[cnt];

		lpTLVertexBuff[cnt].tu = uv[cnt][0];
		lpTLVertexBuff[cnt].tv = uv[cnt][1];
	}
}








void RenderFilterEffect(void)
{
	if(s_dwFilterEffectWork == FILTER_EFFECT_SET_MOTION_BLUR)
	{
		if(s_isFirstMotionBlur)
		{
			ChangeRenderTarget(NEW_TARGET_PRIMARY);
			d3ddev->ClearViewport(D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET);
			RenderOriginalDraw(s_lpD3D_NewTargetTexture_Back, s_TLVertex_NewTarget);
			s_isFirstMotionBlur = 0;
		}
		else
		{
			ChangeRenderTarget(NEW_TARGET_PRIMARY);
			RenderAlphaDraw(s_lpD3D_NewTargetTexture_Back, s_TLVertex_NewTarget, s_dwFilterEffectRGBAlpha[FILTER_EFFECT_SET_MOTION_BLUR]);
		}

		ChangeRenderTarget(ORG_TARGET);
		RenderOriginalDraw(s_lpD3D_NewTargetTexture_Primary, s_TLVertex_NewTarget);
	}
	else if(s_dwFilterEffectWork == FILTER_EFFECT_SET_BRIGHT_CONTRAST)
	{
		ChangeRenderTarget(NEW_TARGET_RATE_BACK);
		RenderOriginalDraw(s_lpD3D_NewTargetTexture_Back, s_TLVertex_RateZoomOut);

		ChangeRenderTarget(ORG_TARGET);
		RenderBlurDraw(s_lpD3D_NewTargetTexture_Rate_Back, s_TLVertex_RateZoomIn);
		RenderAlphaDraw(s_lpD3D_NewTargetTexture_Back, s_TLVertex_NewTarget, s_dwFilterEffectRGBAlpha[FILTER_EFFECT_SET_BRIGHT_CONTRAST]);
	}
	else if(s_dwFilterEffectWork == (FILTER_EFFECT_SET_MOTION_BLUR | FILTER_EFFECT_SET_BRIGHT_CONTRAST))
	{
		if(s_isFirstMotionBlur)
		{
			ChangeRenderTarget(NEW_TARGET_PRIMARY);
			d3ddev->ClearViewport(D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET);
			RenderOriginalDraw(s_lpD3D_NewTargetTexture_Back, s_TLVertex_NewTarget);
			s_isFirstMotionBlur = 0;
		}
		else
		{
			ChangeRenderTarget(NEW_TARGET_PRIMARY);
			RenderAlphaDraw(s_lpD3D_NewTargetTexture_Back, s_TLVertex_NewTarget, s_dwFilterEffectRGBAlpha[FILTER_EFFECT_SET_MOTION_BLUR]);
		}

		ChangeRenderTarget(NEW_TARGET_RATE_BACK);
		RenderOriginalDraw(s_lpD3D_NewTargetTexture_Primary, s_TLVertex_RateZoomOut);

		ChangeRenderTarget(ORG_TARGET);
		RenderBlurDraw(s_lpD3D_NewTargetTexture_Rate_Back, s_TLVertex_RateZoomIn);
		RenderAlphaDraw(s_lpD3D_NewTargetTexture_Primary, s_TLVertex_NewTarget, s_dwFilterEffectRGBAlpha[FILTER_EFFECT_SET_BRIGHT_CONTRAST]);
	}
}


