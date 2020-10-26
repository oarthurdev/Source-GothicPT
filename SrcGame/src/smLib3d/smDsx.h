#ifndef _SMDSX_H_
#define _SMDSX_H_


#include <d3d9.h>
#include <d3d9types.h>
#include "d3dx9.h"



#include <Shlwapi.h>


struct D3DTLVERTEX
{
	float sx;
	float sy;
	float sz;
	float rhw;
	D3DCOLOR color;
	D3DCOLOR specular;
	float tu;
	float tv;
};


extern int WindowMode;
extern int smTextureBPP;
extern int smFlipCount;
extern bool MagFilter;
extern int smScreenWidth, smScreenHeight;

extern LPDIRECT3D9             lpD3D;
extern LPDIRECT3DDEVICE9       d3ddev;
extern D3DPRESENT_PARAMETERS   d3dpp;
extern int                     FontType;
extern int                     FontOpacity;
extern ID3DXFont *             Font;
extern ID3DXFont *             FontBold;
extern ID3DXFont *             FontTitle;
extern ID3DXFont *             FontDamageShadow;
extern D3DCOLOR                FontColor;



BOOL CreateD3D();


void ReleaseD3D();

void OnLostDevice();

void OnResetDevice();

void RestoreDevice();


BOOL SetDisplayMode(HWND hWnd, DWORD Width, DWORD Height, DWORD BPP);


void InitRender();


void BeginRender();


void EndRender();


void DrawTexture(LPDIRECT3DTEXTURE9 Texture, D3DTLVERTEX * Vertex, int AlphaBlend);

void DrawTexture2D(LPDIRECT3DTEXTURE9 lpTexture, RECT destinationRect, RECT sourceRect, int alphaBlend);



extern int MESSAGE(char *t);



typedef struct {
	float r, g, b, a;
} COLORVALUE, *LPCOLORVALUE;

typedef struct {
	float	x, y, z;
} VECTOR, *LPVECTOR;

typedef struct {
	float   tu, tv;
} TVERTEX, *LPTVERTEX;



#pragma comment(lib, "d3d9.lib") 
#pragma comment(lib, "d3dx9.lib") 
#pragma comment( lib, "winmm.lib" )




#pragma comment(lib, "shlwapi.lib")



#endif
