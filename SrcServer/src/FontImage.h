#pragma once

#include <Windows.h>


void CreateFontImage(void);

int  DrawFontImage(char *lpStr, int xPos, int yPos, DWORD rgba, float fRatio = 1.f);
int  DrawSpecialFontImage(int SpecialNum, int xPos, int yPos, DWORD rgba, float fRatio = 1.f);