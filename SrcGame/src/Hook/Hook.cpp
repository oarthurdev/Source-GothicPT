#include "Hook.h"
#include "vtablehook.h"
#include <Windows.h>
#include "smLib3d\smDsx.h"
#include "NetType.h"

#include <iostream>

using namespace std;

#ifndef _W_SERVER
#ifdef BMFONT

Weight weight = Weight::normal;

void *Detour(BYTE *source, const BYTE *destination, const int length)
{
	DWORD back;

	void *memory = VirtualAlloc(NULL, length + 5, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	BYTE *jmp = (BYTE*)memory;


	VirtualProtect(source, length, PAGE_READWRITE, &back);
	memcpy(jmp, source, length);

	jmp += length;

	jmp[0] = 0xE9;
	*(DWORD*)(jmp + 1) = (DWORD)(source + length - jmp) - 5;

	source[0] = 0xE9;
	*(DWORD*)(source + 1) = (DWORD)(destination - source) - 5;

	VirtualProtect(source, length, back, &back);

	return (jmp - length);
}

BOOL WINAPI hook_DeleteObject(HGDIOBJ hObject)
{
	if(hObject != (HGDIOBJ)0x11111111 && hObject != (HGDIOBJ)0x22222222)
		return _DeleteObject(hObject);
	else
		return 0;
}

HGDIOBJ WINAPI hook_SelectObject(HDC hdc, HGDIOBJ hgdiobj)
{

	if(hgdiobj == (HGDIOBJ)0x11111111)
	{
		weight = Weight::normal;
	}
	else if(hgdiobj == (HGDIOBJ)0x22222222)
	{
		weight = Weight::bold;
	}
	else
	{
		return _SelectObject(hdc, hgdiobj);
	}

	return 0;
}

int WINAPI hook_
{
	return 0;
}

COLORREF WINAPI hook_SetFontTextColor(HDC hdc, COLORREF crColor)
{
	COLORREF prevColor = NULL;

	if(font[weight])
	{
		prevColor = font[weight]->getTextColour();

		font[weight]->setTextColour(crColor);
	}

	return prevColor;
}

BOOL WINAPI hook_dsTextOutLine(HDC hdc, int nXStart, int nYStart, LPCTSTR lpString, int cchString)
{

	if(font[weight])
	{
		font[weight]->drawText(lpString, nXStart, nYStart, cchString);
	}

	return TRUE;
}

HBITMAP WINAPI hook_CreateCompatibleBitmap(HDC hdc, int nWidth, int nHeight)
{
	return _CreateCompatibleBitmap(hdc, nWidth, nHeight);
	
}

HDC WINAPI hook_CreateCompatibleDC(HDC hdc)
{
	return _CreateCompatibleDC(hdc);
	
}


HDC WINAPI hook_CreateDC(LPCTSTR lpszDriver, LPCTSTR lpszDevice, LPCTSTR lpszOutput, const DEVMODE *lpInitData)
{
	return _CreateDC(lpszDriver, lpszDevice, lpszOutput, lpInitData);
}

HBRUSH WINAPI hook_CreateSolidBrush(COLORREF crColor)
{
	return _CreateSolidBrush(crColor);
}

int WINAPI hook_SetDIBitsToDevice(HDC hdc, int XDest, int YDest, DWORD dwWidth, DWORD dwHeight, int XSrc, int YSrc, UINT uStartScan, UINT cScanLines, const VOID*lpvBits, const BITMAPINFO *lpbmi, UINT fuColorUse)
{
	if(hdc)
		return _SetDIBitsToDevice(hdc, XDest, YDest, dwWidth, dwHeight, XSrc, YSrc, uStartScan, cScanLines, lpvBits, lpbmi, fuColorUse);
	else
		return 0;
}

HGDIOBJ WINAPI hook_GetStockObject(int fnObject)
{
	return 0;
}

HFONT WINAPI hook_CreateFont(int nHeight, int nWidth, int nEscapement, int nOrientation, int fnWeight, DWORD fdwItalic, DWORD fdwUnderline, DWORD fdwStrikeOut, DWORD fdwCharSet, DWORD fdwOutputPrecision, DWORD fdwClipPrecision, DWORD fdwQuality, DWORD fdwPitchAndFamily, LPCTSTR lpszFace)
{
	if(fnWeight == FW_THIN)
	{
		return HFONT(0x11111111);
	}
	else if(fnWeight == FW_ULTRABOLD)
	{
		return HFONT(0x22222222);
	}



	return HFONT(0x11111111);
}

BOOL WINAPI hook_GetFontTextExtentPoint(HDC Chdc, LPCTSTR lpString, int cbString, LPSIZE lpSize)
{
	if(font[weight])
	{
		unsigned int width = font[weight]->getTextWidth(lpString, cbString);
		unsigned int height = font[weight]->getTextHeight(lpString);

		lpSize->cx = width;
		lpSize->cy = height;

		return TRUE;
	}

	return FALSE;
}

BOOL WINAPI hook_GetFontTextExtentPoint(HDC hdc, LPCTSTR lpString, int c, LPSIZE lpSize)
{
	return hook_GetFontTextExtentPoint(hdc, lpString, c, lpSize);
}

int WINAPI hook_GetObject(HGDIOBJ hgdiobj, int cbBuffer, LPVOID lpvObject)
{
	return 0;
}

int WINAPI hook_GetDIBits(HDC hdc, HBITMAP hbmp, UINT uStartScan, UINT cScanLines, LPVOID lpvBits, LPBITMAPINFO lpbi, UINT uUsage)
{
	return 0;
}

int WINAPI hook_DeleteDC(HDC hdc)
{
	if(hdc)
		return _DeleteDC(hdc);
	else
		return 0;
}



void hooks()
{
	_GetFontTextExtentPoint = (H_GetFontTextExtentPoint)GetProcAddress(GetModuleHandle("GDI32.dll"), "GetFontTextExtentPointA");
	_GetFontTextExtentPoint = (H_GetFontTextExtentPoint)Detour((BYTE*)_GetFontTextExtentPoint, (BYTE*)&hook_GetFontTextExtentPoint, 5);

	_GetFontTextExtentPoint = (H_GetFontTextExtentPoint)GetProcAddress(GetModuleHandle("GDI32.dll"), "GetFontTextExtentPointA");
	_GetFontTextExtentPoint = (H_GetFontTextExtentPoint)Detour((BYTE*)_GetFontTextExtentPoint, (BYTE*)&hook_GetFontTextExtentPoint, 5);

	_SelectObject = (H_SelectObject)GetProcAddress(GetModuleHandle("GDI32.dll"), "SelectObject");
	_SelectObject = (H_SelectObject)Detour((BYTE*)_SelectObject, (BYTE*)&hook_SelectObject, 5);

	_
	_

	_SetFontTextColor = (H_SetFontTextColor)GetProcAddress(GetModuleHandle("GDI32.dll"), "SetFontTextColor");
	_SetFontTextColor = (H_SetFontTextColor)Detour((BYTE*)_SetFontTextColor, (BYTE*)&hook_SetFontTextColor, 5);

	_dsTextOutLine = (H_dsTextOutLine)GetProcAddress(GetModuleHandle("GDI32.dll"), "dsTextOutLineA");
	_dsTextOutLine = (H_dsTextOutLine)Detour((BYTE*)_dsTextOutLine, (BYTE*)&hook_dsTextOutLine, 5);


	_CreateFont = (H_CreateFont)GetProcAddress(GetModuleHandle("GDI32.dll"), "CreateFontA");
	_CreateFont = (H_CreateFont)Detour((BYTE*)_CreateFont, (BYTE*)&hook_CreateFont, 5);
}

#endif
#endif
