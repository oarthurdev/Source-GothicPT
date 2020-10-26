#ifndef	_DRAWSUB_HEADER

#define _DRAWSUB_HEADER

#define	dsARRAY_LEFT	0
#define	dsARRAY_TOP		0
#define	dsARRAY_RIGHT	1
#define	dsARRAY_BOTTOM	2


extern int	dsDrawOffsetArray;

extern int	dsDrawOffset_X;
extern int	dsDrawOffset_Y;

int DrawFontText(int x, int y, LPCTSTR lpszString, COLORREF Color, int FontType);
int dsTextLineOut(HDC hdc, int x, int y, LPCTSTR lpszString, int nCount = 0);
int dsGetDrawOffset(int *sx, int *sy);
int dsMenuCursorPos(POINT *lpCursorPos, int Mode);


int dsDrawColorBox(DWORD Color, int x, int y, int sizeX, int sizeY);
int dsDrawColorBoxFloat(DWORD Color, float x, float y, float sizeX, float sizeY);


int dsDrawTexImage(int Mat, int x, int y, int w, int h, DWORD Transp, int specular = 0);

int dsDrawTexImageFloat(int Mat, float x, float y, float w, float h, DWORD dwColor, int specular = 0);

int dsDrawTexImage(int Mat, int x, int y, int w, int h, float surW, float surH, float tLeft, float tTop, float tRight, float tBottom, int Transp);
int dsDrawTexImageFloat(int Mat, float x, float y, float w, float h, float surW, float surH, float tLeft, float tTop, float tRight, float tBottom, int Transp);

int dsDrawTexImageFloatColor(int Mat, float x, float y, float w, float h, float surW, float surH, float tLeft, float tTop, float tRight, float tBottom, DWORD dwColor);

#endif