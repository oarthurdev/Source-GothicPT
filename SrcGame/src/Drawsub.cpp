
#include "smlib3d\\smd3d.h"
#include "Drawsub.h"
#include "sinbaram\\sinlinkheader.h"

extern int WinSizeX;
extern int WinSizeY;

int	dsDrawOffsetArray = 0;
int	dsDrawOffset_X = 0;
int	dsDrawOffset_Y = 0;

void SetFontOpacity(int Opacity)
{
	FontOpacity = Opacity;
}

int DrawFontText(int x, int y, LPCTSTR lpszString, COLORREF Color, int FontType)
{
	SetFontTextColor(Color);

	if (dsDrawOffset_X || dsDrawOffset_Y)
	{
		if (dsDrawOffsetArray & dsARRAY_RIGHT)
			x += dsDrawOffset_X;

		if (dsDrawOffsetArray & dsARRAY_BOTTOM)
			y += dsDrawOffset_Y;
	}


	RECT rc;
	rc.left = x;
	rc.right = x + smScreenWidth;
	rc.top = y;
	rc.bottom = y + smScreenHeight;

	switch (FontType)
	{
	case 0:
		if (Font)
			return Font->DrawText(NULL, lpszString, strlen(lpszString), &rc, 0, FontColor);
		else
			D3DXCreateFont(d3ddev, 15, 0, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Noto Sans", &Font);
		break;
	case 1:
		if (FontBold)
			return FontBold->DrawText(NULL, lpszString, strlen(lpszString), &rc, 0, FontColor);
		else
			D3DXCreateFont(d3ddev, 15, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Noto Sans", &FontBold);
		break;
	case 2:
		if (FontTitle)
			return FontTitle->DrawText(NULL, lpszString, strlen(lpszString), &rc, 0, FontColor);
		else
			D3DXCreateFont(d3ddev, 15, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Noto Sans", &FontTitle);
		break;
	}


}


int dsTextLineOut(int x, int y, LPCTSTR lpszString, int nCount)
{
	if(dsDrawOffset_X || dsDrawOffset_Y)
	{
		if(dsDrawOffsetArray & dsARRAY_RIGHT)
			x += dsDrawOffset_X;

		if(dsDrawOffsetArray & dsARRAY_BOTTOM)
			y += dsDrawOffset_Y;
	}


	RECT rc;
	rc.left = x;
	rc.right = x + smScreenWidth;
	rc.top = y;
	rc.bottom = y + smScreenHeight;

	switch (FontType)
	{
	case 0:
		if (Font)
			return Font->DrawText(NULL, lpszString, nCount, &rc, 0, FontColor);
		else
			D3DXCreateFont(d3ddev, 15, 0, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Noto Sans", &Font);
		break;
	case 1:
		if (FontBold)
			return FontBold->DrawText(NULL, lpszString, nCount, &rc, 0, FontColor);
		else
			D3DXCreateFont(d3ddev, 15, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Noto Sans", &FontBold);
		break;
	case 2:
		if (FontTitle)
			return FontTitle->DrawText(NULL, lpszString, nCount, &rc, 0, FontColor);
		else
			D3DXCreateFont(d3ddev, 15, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Noto Sans", &FontTitle);
		break;
	}

}

void SetFontTextColor(COLORREF crColor)
{
	FontColor = D3DCOLOR_RGBA(GetRValue(crColor), GetGValue(crColor), GetBValue(crColor), FontOpacity);
}


BOOL GetFontTextExtentPoint(LPCTSTR lpString, int c, LPSIZE  lpSize)
{
	RECT rcRect = { 0,0,0,0 };

	switch (FontType)
	{
	case 0:
		if (Font)
		{
			Font->DrawText(NULL, lpString, c, &rcRect, DT_CALCRECT, FontColor);

			lpSize->cx = rcRect.right - rcRect.left;
			lpSize->cy = rcRect.bottom - rcRect.top;
		}
		break;
	case 1:
		if (FontBold)
		{
			FontBold->DrawText(NULL, lpString, c, &rcRect, DT_CALCRECT, FontColor);

			lpSize->cx = rcRect.right - rcRect.left;
			lpSize->cy = rcRect.bottom - rcRect.top;
		}
		break;
	case 2:
		if (FontTitle)
		{
			FontTitle->DrawText(NULL, lpString, c, &rcRect, DT_CALCRECT, FontColor);

			lpSize->cx = rcRect.right - rcRect.left;
			lpSize->cy = rcRect.bottom - rcRect.top;
		}
		break;
	}

	return TRUE;
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
	D3DTLVERTEX tlVertex[16];
	int cnt;
	for (cnt = 0; cnt < 4; cnt++)
	{
		tlVertex[cnt].rhw = 1;
		tlVertex[cnt].color = Color;
		tlVertex[cnt].specular = D3DCOLOR_RGBA(0, 0, 0, 0);
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
	DrawTexture(0, tlVertex, 1);
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
	D3DTLVERTEX tlVertex[4];
	int cnt;
	for (cnt = 0; cnt < 4; cnt++)
	{
		tlVertex[cnt].rhw = 1;
		tlVertex[cnt].color = D3DCOLOR_RGBA(255, 255, 255, Transp);
		tlVertex[cnt].specular = D3DCOLOR_RGBA(0, 0, 0, 0);
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
	DrawTexture(smMaterial[Mat].smTexture[0]->lpD3DTexture, tlVertex, 1);
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
	if ((x >= clipRight) || (y >= clipBottom) || ((x + w) <= clipLeft) || ((y + h) <= clipTop))
		return FALSE;
	float x1 = x;
	float y1 = y;
	float x2 = (x + w);
	float y2 = (y + h);
	D3DTLVERTEX tlVertex[4];
	int cnt;
	if (dwColor < 256)
		dwClr = D3DCOLOR_RGBA(255, 255, 255, dwColor);
	else
		dwClr = dwColor;
	for (cnt = 0; cnt < 4; cnt++)
	{
		tlVertex[cnt].rhw = 1.f;
		tlVertex[cnt].color = dwClr;
		tlVertex[cnt].specular = D3DCOLOR_RGBA(specular, specular, specular, 0);
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
	DrawTexture(smMaterial[Mat].smTexture[0]->lpD3DTexture, tlVertex, 1);
	return TRUE;
}

int dsDrawTexImageFloatColor(int Mat, float x, float y, float w, float h, float surW, float surH, float tLeft, float tTop, float tRight, float tBottom, DWORD dwColor)
{
	D3DTLVERTEX tlVertex[4];
	int cnt;
	for (cnt = 0; cnt < 4; cnt++)
	{
		tlVertex[cnt].rhw = 1;
		tlVertex[cnt].color = dwColor;
		tlVertex[cnt].specular = D3DCOLOR_RGBA(0, 0, 0, 0);
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
	DrawTexture(smMaterial[Mat].smTexture[0]->lpD3DTexture, tlVertex, 1);
	return TRUE;
}
