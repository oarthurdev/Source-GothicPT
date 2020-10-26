#ifndef HOOK_H
#define HOOK_H

#include <Windows.h>
#include <ddraw.h>

typedef BOOL(WINAPI *H_GetFontTextExtentPoint)(HDC hdc, LPCTSTR lpString, int c, LPSIZE lpSize);
H_GetFontTextExtentPoint _GetFontTextExtentPoint;

typedef BOOL(WINAPI *H_DeleteObject)(HGDIOBJ hObject);
H_DeleteObject _DeleteObject;

typedef HGDIOBJ(WINAPI *H_SelectObject)(HDC hdc, HGDIOBJ hgdiobj);
H_SelectObject _SelectObject;

typedef int(WINAPI *H_
H_

typedef COLORREF(WINAPI *H_SetFontTextColor)(HDC hdc, COLORREF crColor);
H_SetFontTextColor _SetFontTextColor;

typedef BOOL(WINAPI *H_dsTextOutLine)(HDC hdc, int nXStart, int nYStart, LPCTSTR lpString, int cchString);
H_dsTextOutLine _dsTextOutLine;

typedef BOOL(WINAPI *H_BitBlt)(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, HDC hdcSrc, int nXSrc, int nYSrc, DWORD dwRop);
H_BitBlt _BitBlt;

typedef HBITMAP(WINAPI *H_CreateCompatibleBitmap)(HDC hdc, int nWidth, int nHeight);
H_CreateCompatibleBitmap _CreateCompatibleBitmap;

typedef HDC(WINAPI *H_CreateCompatibleDC)(HDC hdc);
H_CreateCompatibleDC _CreateCompatibleDC;

typedef HDC(WINAPI *H_CreateDC)(LPCTSTR lpszDriver, LPCTSTR lpszDevice, LPCTSTR lpszOutput, const DEVMODE *lpInitData);
H_CreateDC _CreateDC;

typedef HBRUSH(WINAPI *H_CreateSolidBrush)(COLORREF crColor);
H_CreateSolidBrush _CreateSolidBrush;

typedef int(WINAPI *H_SetDIBitsToDevice)(HDC hdc, int XDest, int YDest, DWORD dwWidth, DWORD dwHeight, int XSrc, int YSrc, UINT uStartScan, UINT cScanLines, const VOID*lpvBits, const BITMAPINFO *lpbmi, UINT fuColorUse);
H_SetDIBitsToDevice  _SetDIBitsToDevice;

typedef HGDIOBJ(WINAPI *H_GetStockObject)(int fnObject);
H_GetStockObject  _GetStockObject;

typedef HFONT(WINAPI *H_CreateFont)(int nHeight, int nWidth, int nEscapement, int nOrientation, int fnWeight, DWORD fdwItalic, DWORD fdwUnderline, DWORD fdwStrikeOut, DWORD fdwCharSet, DWORD fdwOutputPrecision, DWORD fdwClipPrecision, DWORD fdwQuality, DWORD fdwPitchAndFamily, LPCTSTR lpszFace);
H_CreateFont  _CreateFont;

typedef BOOL(WINAPI *H_GetTextExtentPoint)(HDC Chdc, LPCTSTR lpString, int cbString, LPSIZE  lpSize);
H_GetTextExtentPoint _GetTextExtentPoint;

typedef int(WINAPI *H_GetObject)(HGDIOBJ hgdiobj, int cbBuffer, LPVOID lpvObject);
H_GetObject _GetObject;

typedef int(WINAPI *H_GetDIBits)(HDC hdc, HBITMAP hbmp, UINT uStartScan, UINT cScanLines, LPVOID lpvBits, LPBITMAPINFO lpbi, UINT uUsage);
H_GetDIBits _GetDIBits;

typedef int(WINAPI *H_DeleteDC)(HDC hdc);
H_DeleteDC  _DeleteDC;

typedef HRESULT(WINAPI *H_DirectDrawCreate)(GUID FAR *lpGUID, LPDIRECTDRAW FAR *lplpDD, IUnknown FAR *pUnkOuter);
H_DirectDrawCreate  _DirectDrawCreate;



#endif 
