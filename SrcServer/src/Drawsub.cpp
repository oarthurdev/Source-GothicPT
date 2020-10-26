
#include "smlib3d\\smd3d.h"
#include "Drawsub.h"
#include "sinbaram\\sinlinkheader.h"


extern int WinSizeX;
extern int WinSizeY;

int	dsDrawOffsetArray = 0;
int	dsDrawOffset_X = 0;
int	dsDrawOffset_Y = 0;

int DrawFontText(int x, int y, LPCTSTR lpszString, COLORREF Color, int FontType)
{
	SetTextColor(0, Color);

	if (dsDrawOffset_X || dsDrawOffset_Y)
	{
		if (dsDrawOffsetArray & dsARRAY_RIGHT)
			x += dsDrawOffset_X;

		if (dsDrawOffsetArray & dsARRAY_BOTTOM)
			y += dsDrawOffset_Y;
	}

	return TextOut(0, x, y, lpszString, strlen(lpszString));
}
int dsTextLineOut(HDC hdc, int x, int y, LPCTSTR lpszString, int nCount)
{
	if(dsDrawOffset_X || dsDrawOffset_Y)
	{
		if(dsDrawOffsetArray & dsARRAY_RIGHT)
			x += dsDrawOffset_X;

		if(dsDrawOffsetArray & dsARRAY_BOTTOM)
			y += dsDrawOffset_Y;
	}

	return TextOut(hdc, x, y, lpszString, nCount);
}

int dsGetDrawOffset(int *sx, int *sy)
{
	if(dsDrawOffset_X == 0 && dsDrawOffset_Y == 0)
		return TRUE;

	if(dsDrawOffsetArray&dsARRAY_RIGHT)
		*sx += dsDrawOffset_X;

	if(dsDrawOffsetArray&dsARRAY_BOTTOM)
		*sy += dsDrawOffset_Y;

	return TRUE;
}

static POINT BackCursorPos;


int dsMenuCursorPos(POINT *lpCursorPos, int Mode)
{
	int x, y;

	if(Mode)
	{
		BackCursorPos.x = lpCursorPos->x;
		BackCursorPos.y = lpCursorPos->y;

		x = WinSizeX - 800;
		y = WinSizeY - 600;

		if(x > 0)
		{
			if(lpCursorPos->x >= 600 && lpCursorPos->y <= y + 420 && (!sSinWarpGate.ShowFlag || Mode != 1))
			{

				if(MouseItem.Flag)
				{
					lpCursorPos->x = 0;
					return TRUE;
				}


				lpCursorPos->x -= x;
				lpCursorPos->y -= y;
				if(lpCursorPos->x < 600) lpCursorPos->x = 0;
			}
			else
			{
				if(lpCursorPos->y > 400)
				{
					lpCursorPos->y -= y;
					if(lpCursorPos->y < 420)lpCursorPos->y = 0;
				}
			}

		}
	}
	else
	{
		lpCursorPos->x = BackCursorPos.x;
		lpCursorPos->y = BackCursorPos.y;
	}

	return TRUE;
}


int dsDrawColorBoxFloat(DWORD Color, float x, float y, float sizeX, float sizeY)
{
	DRZD3DTLVERTEX tlVertex[16];
	int cnt;


	for(cnt = 0; cnt < 4; cnt++)
	{
		tlVertex[cnt].rhw = 1;
		tlVertex[cnt].color = Color;
		tlVertex[cnt].specular = RGBA_MAKE(0, 0, 0, 0);
		tlVertex[cnt].sz = 0;
	}

	tlVertex[0].sx = x;
	tlVertex[0].sy = y;
	tlVertex[0].tu = 0;
	tlVertex[0].tv = 0;

	tlVertex[1].sx = x;
	tlVertex[1].sy = (y + sizeY);
	tlVertex[1].tu = 0;
	tlVertex[1].tv = 1;

	tlVertex[2].sx = (x + sizeX);
	tlVertex[2].sy = y;
	tlVertex[2].tu = 1;
	tlVertex[2].tv = 0;

	tlVertex[3].sx = (x + sizeX);
	tlVertex[3].sy = (y + sizeY);
	tlVertex[3].tu = 1;
	tlVertex[3].tv = 1;

	renderDevice.SetTexture(0, 0);

	renderDevice.DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_TLVERTEX, tlVertex, 4, NULL);

	return TRUE;
}

int dsDrawColorBox(DWORD Color, int x, int y, int sizeX, int sizeY)
{
	dsGetDrawOffset(&x, &y);

	return dsDrawColorBoxFloat(Color, (float)x, (float)y, (float)sizeX, (float)sizeY);
}


int dsDrawTexImage(int Mat, int x, int y, int w, int h, DWORD Transp, int specular)
{
	dsGetDrawOffset(&x, &y);

	return dsDrawTexImageFloat(Mat, (float)x, (float)y, (float)w, (float)h, Transp, specular);
}


int dsDrawTexImage(int Mat, int x, int y, int w, int h, float surW, float surH, float tLeft, float tTop, float tRight, float tBottom, int Transp)
{
	return dsDrawTexImageFloat(Mat, (float)x, (float)y, (float)w, (float)h, surW, surH, tLeft, tTop, tRight, tBottom, Transp);
}

int dsDrawTexImageFloat(int Mat, float x, float y, float w, float h, float surW, float surH, float tLeft, float tTop, float tRight, float tBottom, int Transp)
{
	DRZD3DTLVERTEX tlVertex[4];
	int cnt;

	for(cnt = 0; cnt < 4; cnt++)
	{
		tlVertex[cnt].rhw = 1;
		tlVertex[cnt].color = RGBA_MAKE(255, 255, 255, Transp);
		tlVertex[cnt].specular = RGBA_MAKE(0, 0, 0, 0);
		tlVertex[cnt].sz = 0;
	}


	tlVertex[0].sx = x;
	tlVertex[0].sy = y;
	tlVertex[0].tu = 1 * (tLeft / surW);
	tlVertex[0].tv = 1 * (tTop / surH);

	tlVertex[1].sx = x;
	tlVertex[1].sy = (y + h);
	tlVertex[1].tu = 1 * (tLeft / surW);


	tlVertex[1].tv = 1 * ((tBottom + 1) / surH);

	tlVertex[2].sx = (x + w);
	tlVertex[2].sy = y;

	tlVertex[2].tu = 1 * ((tRight + 1) / surW);
	tlVertex[2].tv = 1 * (tTop / surH);

	tlVertex[3].sx = (x + w);
	tlVertex[3].sy = (y + h);
	tlVertex[3].tu = 1 * ((tRight + 1) / surW);
	tlVertex[3].tv = 1 * ((tBottom + 1) / surH);



	if(renderDevice.IsDevice() != NULL)
	{



		renderDevice.SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE);
		renderDevice.SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
		renderDevice.SetRenderState(D3DRENDERSTATE_ZFUNC, D3DCMP_LESSEQUAL);




		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREHANDLE, 0);


		renderDevice.SetRenderState(D3DRENDERSTATE_DITHERENABLE, TRUE);

		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREADDRESS, D3DTADDRESS_WRAP);
		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREPERSPECTIVE, TRUE);


		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREMAG, D3DFILTER_LINEAR);
		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREMIN, D3DFILTER_LINEAR);

		renderDevice.SetRenderState(D3DRENDERSTATE_SPECULARENABLE, TRUE);
		renderDevice.SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, FALSE);

		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_MODULATE);

		renderDevice.SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
		renderDevice.SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
		renderDevice.SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);

		smRender.AlphaTestDepth = 60;


		renderDevice.SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFN_POINT);
		renderDevice.SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTFG_POINT);





		if(smMaterial[Mat].smTexture[0] != NULL)
		{
			if(smMaterial[Mat].smTexture[0]->lpD3DTexture != NULL)
			{
				if(FAILED(renderDevice.SetTexture(0, smMaterial[Mat].smTexture[0]->lpD3DTexture)))
				{
					OutputDebugString("SetTexture Error");
					return FALSE;
				}

				if(FAILED(renderDevice.DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_TLVERTEX, tlVertex, 4, NULL)))
				{
					OutputDebugString("DrawPrimitive Error");
					return FALSE;
				}
			}
		}

		renderDevice.SetTextureStageState(cnt, D3DTSS_MINFILTER, D3DTFN_LINEAR);
		renderDevice.SetTextureStageState(cnt, D3DTSS_MAGFILTER, D3DTFG_LINEAR);
	}


	return TRUE;
}


int dsDrawTexImageFloat(int Mat, float x, float y, float w, float h, DWORD dwColor, int specular)
{
	int clipLeft;
	int clipTop;
	int clipRight;
	int clipBottom;
	DWORD dwClr;

	clipLeft = 0;
	clipTop = 0;
	clipRight = WinSizeX;
	clipBottom = WinSizeY;


	if((x >= clipRight) || (y >= clipBottom) || ((x + w) <= clipLeft) || ((y + h) <= clipTop))
		return FALSE;


	float x1 = x;
	float y1 = y;
	float x2 = (x + w);
	float y2 = (y + h);


	DRZD3DTLVERTEX tlVertex[4];
	int cnt;

	if(dwColor < 256)
		dwClr = RGBA_MAKE(255, 255, 255, dwColor);
	else
		dwClr = dwColor;

	for(cnt = 0; cnt < 4; cnt++)
	{
		tlVertex[cnt].rhw = 1.0f;
		tlVertex[cnt].color = dwClr;
		tlVertex[cnt].specular = RGBA_MAKE(specular, specular, specular, 0);
		tlVertex[cnt].sz = 0;
	}

	tlVertex[0].sx = x1;
	tlVertex[0].sy = y1;
	tlVertex[0].tu = 0.0f;
	tlVertex[0].tv = 0.0f;

	tlVertex[1].sx = x1;
	tlVertex[1].sy = y2;
	tlVertex[1].tu = 0.0f;
	tlVertex[1].tv = 1.0f;

	tlVertex[2].sx = x2;
	tlVertex[2].sy = y1;
	tlVertex[2].tu = 1.0f;
	tlVertex[2].tv = 0.0f;

	tlVertex[3].sx = x2;
	tlVertex[3].sy = y2;
	tlVertex[3].tu = 1.0f;
	tlVertex[3].tv = 1.0f;



	if(renderDevice.IsDevice() != NULL)
	{

		renderDevice.SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);
		renderDevice.SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE);
		renderDevice.SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);





		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREHANDLE, 0);




		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREADDRESS, D3DTADDRESS_WRAP);






		renderDevice.SetRenderState(D3DRENDERSTATE_SPECULARENABLE, TRUE);
		renderDevice.SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, FALSE);

		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_MODULATE);

		renderDevice.SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
		renderDevice.SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
		renderDevice.SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);

		smRender.AlphaTestDepth = 60;

		renderDevice.SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFN_POINT);
		renderDevice.SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTFG_POINT);




		if(smMaterial[Mat].smTexture[0] != NULL)
		{
			if(smMaterial[Mat].smTexture[0]->lpD3DTexture != NULL)
			{
				if(FAILED(renderDevice.SetTexture(0, smMaterial[Mat].smTexture[0]->lpD3DTexture)))
				{
					OutputDebugString("SetTexture Error");
					return FALSE;
				}

				if(FAILED(renderDevice.DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_TLVERTEX, tlVertex, 4, NULL)))
				{
					OutputDebugString("DrawPrimitive Error");
					return FALSE;
				}
			}
		}

		renderDevice.SetTextureStageState(cnt, D3DTSS_MINFILTER, D3DTFN_LINEAR);
		renderDevice.SetTextureStageState(cnt, D3DTSS_MAGFILTER, D3DTFG_LINEAR);



	}


	return TRUE;
}

int dsDrawTexImageFloatColor(int Mat, float x, float y, float w, float h, float surW, float surH, float tLeft, float tTop, float tRight, float tBottom, DWORD dwColor)
{
	DRZD3DTLVERTEX tlVertex[4];
	int cnt;

	for(cnt = 0; cnt < 4; cnt++)
	{
		tlVertex[cnt].rhw = 1;
		tlVertex[cnt].color = dwColor;
		tlVertex[cnt].specular = RGBA_MAKE(0, 0, 0, 0);
		tlVertex[cnt].sz = 0;
	}


	tlVertex[0].sx = x;
	tlVertex[0].sy = y;
	tlVertex[0].tu = 1 * (tLeft / surW);
	tlVertex[0].tv = 1 * (tTop / surH);

	tlVertex[1].sx = x;
	tlVertex[1].sy = (y + h);
	tlVertex[1].tu = 1 * (tLeft / surW);


	tlVertex[1].tv = 1 * ((tBottom + 1) / surH);

	tlVertex[2].sx = (x + w);
	tlVertex[2].sy = y;

	tlVertex[2].tu = 1 * ((tRight + 1) / surW);
	tlVertex[2].tv = 1 * (tTop / surH);

	tlVertex[3].sx = (x + w);
	tlVertex[3].sy = (y + h);
	tlVertex[3].tu = 1 * ((tRight + 1) / surW);
	tlVertex[3].tv = 1 * ((tBottom + 1) / surH);



	if(renderDevice.IsDevice() != NULL)
	{



		renderDevice.SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE);
		renderDevice.SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
		renderDevice.SetRenderState(D3DRENDERSTATE_ZFUNC, D3DCMP_LESSEQUAL);




		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREHANDLE, 0);


		renderDevice.SetRenderState(D3DRENDERSTATE_DITHERENABLE, TRUE);

		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREADDRESS, D3DTADDRESS_WRAP);
		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREPERSPECTIVE, TRUE);


		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREMAG, D3DFILTER_LINEAR);
		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREMIN, D3DFILTER_LINEAR);

		renderDevice.SetRenderState(D3DRENDERSTATE_SPECULARENABLE, TRUE);
		renderDevice.SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, FALSE);

		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_MODULATE);

		renderDevice.SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
		renderDevice.SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
		renderDevice.SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);

		smRender.AlphaTestDepth = 60;


		renderDevice.SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFN_POINT);
		renderDevice.SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTFG_POINT);





		if(smMaterial[Mat].smTexture[0] != NULL)
		{
			if(smMaterial[Mat].smTexture[0]->lpD3DTexture != NULL)
			{
				if(FAILED(renderDevice.SetTexture(0, smMaterial[Mat].smTexture[0]->lpD3DTexture)))
				{
					OutputDebugString("SetTexture Error");
					return FALSE;
				}

				if(FAILED(renderDevice.DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_TLVERTEX, tlVertex, 4, NULL)))
				{
					OutputDebugString("DrawPrimitive Error");
					return FALSE;
				}
			}
		}

		renderDevice.SetTextureStageState(cnt, D3DTSS_MINFILTER, D3DTFN_LINEAR);
		renderDevice.SetTextureStageState(cnt, D3DTSS_MAGFILTER, D3DTFG_LINEAR);
	}

	return TRUE;
}
