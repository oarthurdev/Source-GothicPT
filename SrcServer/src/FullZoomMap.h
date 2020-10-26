





#pragma once


extern int				g_iFzmCursorFocusGame;

extern int				g_iFzmCursorPosX;
extern int				g_iFzmCursorPosY;
extern int				g_FzmMouseButton[3];



extern void CreateBeforeFullZoomMap(void);

extern void DrawFzmBackToSurface(int dest_x, int dest_y, DIRECTDRAWSURFACE lpDDS, int x, int y, int width, int height, int Bltflag);
extern void DrawFzmBackToTexture2D(smTEXTUREHANDLE *hTexHandle, int X, int Y, int Angle, int HalfSize, int Blend);

extern int  SetFullZoomMap(int IsSet);
extern void DrawFullZoomMapCharPos(void);
extern void DrawFullZoomMap(void);
extern void MainFullZoomMap(void);
extern int  KeyFullZoomMap(WPARAM wParam);


