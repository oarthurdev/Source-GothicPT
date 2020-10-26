#define LEVELUP_HELP_CPP
#include <windows.h>
#include <tchar.h>
#include <math.h>
#include <stdio.h>

#include "tjclanDEF.h"

#ifdef USE_PROSTONTALE		

#include "sinbaram\\SinLinkHeader.h"
#include "HoBaram\\HoLinkHeader.h"
#include "Language\\language.h"
#include "HoBaram\\HoTextFile.h"
#include "cE_CViewClanInfo.h"
#endif
#include "tjscroll.h"
#include "tjclan.h"
#include "clan_enti.h"
#include "cE_Notice.h"


#include "Help.h"
#include "GuideHelp.h"


int  haGuidHelpLevel_1Flag = 0;
CHelp cHelp_Menu;
extern int LevelpUpButton[3];

CHelp::CHelp()
{
	m_HelpN = -1;
	m_bDraw = TRUE;

	nHelp0 = nHelp1 = 0;
	m_ImageCount = 0;
	nBox1 = nBox2 = nBox3 = nBox4 = nBox5 = nBox6 = nBox7 = nBox8 = nBox9 = 0;

	ZeroMemory(m_HelpContent, sizeof(m_HelpContent));
	nHeight_Count = 0;
	Box_x = 5;
	Box_y = 5;
	nBoxWidth_Count = BOX_WIDTH_COUNT;
	nBoxHeight_Count = 5;
	ZeroMemory(HelpMenu, sizeof(HelpMenu));
	top_right = 0;
	nGuideHelp = 0;
	GuideImage = new smMATERIAL_GROUP(1);
	nGuideImageNum = 0;
	for (int i = 0; i < 2; i++)
	{
		hClose[i] = NULL;
	}

	m_bTime = TRUE;
	m_bOnce = FALSE;
	m_dwTime = 0;
}

CHelp::~CHelp()
{
	Clear();
}

int CHelp::Init(int Life)
{
	life = Life;

	return 1;
}

int CHelp::Clear()
{
	for (int i = 0; i < 2; i++)
	{
		if (hClose[i])
		{
			hClose[i]->Release();

			hClose[i] = NULL;
		}
	}
	return 1;
}

void CHelp::Load()
{
	nHelp0 = CreateTextureMaterial("image\\Sinimage\\Help\\help_icon03.tga", 0, 0, 64, 64, SMMAT_BLEND_ALPHA);
	nHelp1 = CreateTextureMaterial("image\\Sinimage\\Help\\help_icon04.tga", 0, 0, 64, 64, SMMAT_BLEND_ALPHA);

	nBox1 = CreateTextureMaterial("image\\Sinimage\\Help\\GH-Box01.tga", 0, 0, 32, 32, SMMAT_BLEND_ALPHA);
	nBox2 = CreateTextureMaterial("image\\Sinimage\\Help\\GH-Box02.tga", 0, 0, 16, 32, SMMAT_BLEND_ALPHA);
	nBox3 = CreateTextureMaterial("image\\Sinimage\\Help\\GH-Box03.tga", 0, 0, 32, 32, SMMAT_BLEND_ALPHA);
	nBox4 = CreateTextureMaterial("image\\Sinimage\\Help\\GH-Box04.tga", 0, 0, 32, 16, SMMAT_BLEND_ALPHA);
	nBox5 = CreateTextureMaterial("image\\Sinimage\\Help\\GH-Box05.tga", 0, 0, 16, 16, SMMAT_BLEND_ALPHA);
	nBox6 = CreateTextureMaterial("image\\Sinimage\\Help\\GH-Box06.tga", 0, 0, 32, 16, SMMAT_BLEND_ALPHA);
	nBox7 = CreateTextureMaterial("image\\Sinimage\\Help\\GH-Box07.tga", 0, 0, 32, 32, SMMAT_BLEND_ALPHA);
	nBox8 = CreateTextureMaterial("image\\Sinimage\\Help\\GH-Box08.tga", 0, 0, 16, 32, SMMAT_BLEND_ALPHA);
	nBox9 = CreateTextureMaterial("image\\Sinimage\\Help\\GH-Box09.tga", 0, 0, 32, 32, SMMAT_BLEND_ALPHA);

	hClose[0] = LoadDibSurfaceOffscreen("image\\clanImage\\MessageBox\\c.bmp");
	hClose[1] = LoadDibSurfaceOffscreen("image\\clanImage\\MessageBox\\c1.bmp");

	nGuideHelp = CreateTextureMaterial("image\\Sinimage\\Help\\help_icon02t.tga", 0, 0, 64, 64, SMMAT_BLEND_ALPHA);
}

void CHelp::Main()
{
	int i;


	if (haGuidHelpLevel_1Flag)
	{
		if (haGuidHelpLevel_1Flag == 1)
			GetHelpContent("Level_1_W", "Key29", "Guide25");
		else
			GetHelpContent("Level_1_D", "Key30", "Guide26");
		menuInit(1);
		m_HelpN = 1;
		haGuidHelpLevel_1Flag = 0;
	}
	switch (m_HelpN)
	{

	case LEVELUP_HELP:
		if (!m_bOnce)
		{
			m_dwTime = dwPlayTime;
			m_bOnce = !m_bOnce;
		}
		if ((dwPlayTime - m_dwTime) >= 700)
		{
			m_dwTime = dwPlayTime;
			m_bTime = !m_bTime;
		}

		i = chkeckMenuN();
		switch (i)
		{
		case 0:
		case 1:
			isDrawClanMenu = 1;
			break;
		default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			isDrawClanMenu = 0;
			break;
		}

		if (LevelpUpButton[0])
		{

			LevelpUpButton[0] = 0;

			switch (i)
			{
			case 1:
			case 0:
				isDrawClanMenu = 1;
				m_HelpN = LEVELUP_HELP_CONTENT;
				menuInit(m_HelpN);
				break;
			default:
				isDrawClanMenu = 0;
				break;

			}
		}
		break;

	case LEVELUP_HELP_CONTENT:
		i = chkeckMenuN();
		switch (i)
		{
		case 0:
			menuMouseOver[0] = 1;
			break;
		case 5:
			isDrawClanMenu = 1;
			break;
		case 1:
			menuMouseOver[1] = 1;
			break;
		default:
			isDrawClanMenu = 0;
			memset(menuMouseOver, -1, sizeof(int) * 30);

			break;
		}
		if (LevelpUpButton[0])
		{

			LevelpUpButton[0] = 0;

			switch (i)
			{
			case 1:
				m_HelpN = -1;
				isDrawClanMenu = 0;
				break;
			case 5:
				isDrawClanMenu = 1;
				break;
			case 0:
				m_HelpN = -1;
				isDrawClanMenu = 0;
				void InitGuideContentHelp();
				InitGuideContentHelp();
				break;
			default:
				isDrawClanMenu = 0;
				break;

			}
		}
		break;


	}
}

void CHelp::SetStartPos(int x, int y)
{
	m_Start.x = x;
	m_Start.y = y;
}


void CHelp::Draw(BOOL bFlag)
{
	int nCap = 0, i = 0;
	if (bFlag)
	{
		switch (m_HelpN)
		{
		case LEVELUP_HELP:

			break;
		}
	}
	else
	{
		switch (m_HelpN)
		{
		case LEVELUP_HELP:




			if (m_bTime)
			{
				
				sinDrawTexImage(nHelp0, (float)HelpMenu[0].left, (float)HelpMenu[0].top, 64, 64);
				
			}
			else
			{
				
				sinDrawTexImage(nHelp1, (float)HelpMenu[0].left, (float)HelpMenu[0].top, 64, 64);
				
			}

			
			sinDrawTexImage(nGuideHelp, (float)HelpMenu[1].left, (float)HelpMenu[1].top, 64, 32);
			
			break;

		case LEVELUP_HELP_CONTENT:
			DrawBox(Box_x, Box_x, BOX_WIDTH_COUNT, nHeight_Count);
			
			sinDrawTexImage(nHelp0, (float)HelpMenu[2].left, (float)HelpMenu[2].top, 64, 64);
			if ((sinChar->Level != 9) && (sinChar->Level != 39))
				dsDrawTexImageFloat(nGuideImageNum, (float)HelpMenu[4].left, (float)HelpMenu[4].top, 64, 64, 255);

			



			for (i = 0; i < nHeight_Count; i++)
			{

				if (m_bIsContentOver && (i >= CONTENT_MAX - 1))
				{
					break;
				}

				Draw_Help_Text(m_HelpContent[i], HelpMenu[3].left, HelpMenu[3].top + nCap, 2);

				nCap += 15;

			}


			if (menuMouseOver[1] > 0) DrawSprite(HelpMenu[1].left, HelpMenu[1].top, hClose[1], 0, 0, 32, 16, 1);
			else	DrawSprite(HelpMenu[1].left, HelpMenu[1].top, hClose[0], 0, 0, 32, 16, 1);

			if (m_bIsContentOver)
			{
				if (menuMouseOver[0] > 0)
				{
					Draw_Help_Text2(LookHelp, HelpMenu[0].left, HelpMenu[0].top);
				}
				else
				{
					Draw_Help_Text3(LookHelp, HelpMenu[0].left, HelpMenu[0].top);
				}
			}



			break;

		}
	}
}

void CHelp::menuInit(int num)
{
	int nScrollPos = 0;
	switch (num)
	{

	case LEVELUP_HELP:
		HelpMenuSu = 2;
		HelpMenu[0].left = m_Start.x + 4 + 5;
		HelpMenu[0].top = m_Start.y + 7 + 5;
		HelpMenu[0].right = HelpMenu[0].left + 64;
		HelpMenu[0].bottom = HelpMenu[0].top + 64;

		HelpMenu[1].left = HelpMenu[0].right - 24;
		HelpMenu[1].top = m_Start.y + 7 + 12;
		HelpMenu[1].right = HelpMenu[1].left + 64;
		HelpMenu[1].bottom = HelpMenu[1].top + 32;


		break;

	case LEVELUP_HELP_CONTENT:
		HelpMenuSu = 6;

		bottom_left = (Box_y + 32) + (nHeight_Count * 13 + 32);
		top_right = (Box_x + 32) + (16 * BOX_WIDTH_COUNT + 32 + 13);

		HelpMenu[2].left = 13 + Box_x + 5;
		HelpMenu[2].top = 13 + Box_y + 5;
		HelpMenu[2].right = HelpMenu[2].left + 64;
		HelpMenu[2].bottom = HelpMenu[2].top + 64;



		bottom_left = (Box_y + 32) + (nHeight_Count * 13);
		top_right = (Box_x + 32) + (16 * BOX_WIDTH_COUNT);





		HelpMenu[3].left = HelpMenu[2].left + 50 + 2;
		HelpMenu[3].top = HelpMenu[2].top + 10;

		HelpMenu[4].left = top_right - 28 + 37;
		HelpMenu[4].top = bottom_left + 4 - 54;

		HelpMenu[0].left = 13 + Box_x + 5 + 50 + 2;
		HelpMenu[0].top = bottom_left + 4;
		HelpMenu[0].right = HelpMenu[0].left + lstrlen(DETAIL_SEE) * 12;
		HelpMenu[0].bottom = HelpMenu[0].top + 12;

		HelpMenu[1].left = top_right - 32;
		HelpMenu[1].top = bottom_left + 4;
		HelpMenu[1].right = HelpMenu[1].left + 32;
		HelpMenu[1].bottom = HelpMenu[1].top + 16;

		HelpMenu[5].left = Box_x;
		HelpMenu[5].top = Box_y;
		HelpMenu[5].right = HelpMenu[5].left + top_right;
		HelpMenu[5].bottom = HelpMenu[5].top + bottom_left;







		break;
	}
}


void CHelp::DrawBox(int x, int y, int x_width, int y_height)
{
#define ALPHA   250

	if (d3ddev == NULL)
		return;

	int nCnt;
	top_right = 0;
	bottom_left = 0;
	int ypos = y + 32;
	int xpos = x + 32;
	nStart_x = x;


	

	dsDrawTexImage(nBox1, x, y, 32, 32, ALPHA);


	top_right = (x + 32) + (16 * x_width);

	dsDrawTexImage(nBox3, top_right, y, 32, 32, ALPHA);


	for (nCnt = 0; nCnt < y_height; nCnt++)
	{

		dsDrawTexImage(nBox4, x, ypos, 32, 16, ALPHA);

		dsDrawTexImage(nBox6, top_right, ypos, 32, 16, ALPHA);

		ypos += 13;
	}
	ypos = y + 32;


	for (nCnt = 0; nCnt < y_height; nCnt++)
	{
		for (int nCnt2 = 0; nCnt2 < x_width; nCnt2++)
		{
			dsDrawTexImage(nBox5, xpos, ypos, 16, 16, ALPHA);
			xpos += 16;
		}
		xpos = x + 32;
		ypos += 13;
	}



	bottom_left = (y + 32) + (ypos - 37);
	dsDrawTexImage(nBox7, x, bottom_left, 32, 32, ALPHA);



	dsDrawTexImage(nBox9, top_right, bottom_left, 32, 32, ALPHA);



	xpos = x + 32;
	for (nCnt = 0; nCnt < x_width; nCnt++)
	{

		dsDrawTexImage(nBox2, xpos, y, 16, 32, ALPHA);
		dsDrawTexImage(nBox8, xpos, bottom_left, 16, 32, ALPHA);


		xpos += 16;
	}

	
}
void CHelp::SetHelpN(int num)
{
	m_HelpN = num;
}

void CHelp::ClearImage()
{
	GuideImage->Close();
}

void CHelp::LoadGuideImage(char* file)
{
	ClearImage();
	GuideImage->Init(1);
	nGuideImageNum = GuideImage->CreateTextureMaterial(file, 0, 0, 128, 128, SMMAT_BLEND_ALPHA);
	GuideImage->ReadTextures();

}


void CHelp::GetHelpContent(char* section, char* key, char* ImageKey)
{
	DWORD dwSaveSize = 100;
	char  szSaveStr[100];
	char  szImageDir[100];
	DWORD dwReturn, dwFileSize = 0, dwRead = 0;
	HANDLE hFile = NULL;
	char *HelpContent;

	ZeroMemory(m_HelpContent, sizeof(m_HelpContent));
	ZeroMemory(szImageDir, sizeof(szImageDir));

	dwReturn = GetPrivateProfileString(section, key, "Error", szSaveStr, 1024, HELP_CONTENT);

	if (dwReturn == 0) return;
	dwReturn = GetPrivateProfileString(section, ImageKey, "Error", szImageDir, 1024, HELP_CONTENT);
	if (dwReturn == 0) return;

	LoadGuideImage(szImageDir);

	hFile = CreateFile(szSaveStr, GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE) return;

	dwFileSize = GetFileSize(hFile, NULL);

	HelpContent = new char[dwFileSize];
	ZeroMemory(HelpContent, sizeof(char)*dwFileSize);

	ReadFile(hFile, HelpContent, dwFileSize, &dwRead, NULL);
	CloseHandle(hFile);

	Parsing(HelpContent);

	delete[] HelpContent;

}

void CHelp::Parsing(char* str)
{
	int nCnt, nCnt2, nCnt3;
	nCnt = nCnt2 = nCnt3 = 0;
	nHeight_Count = 0;
	while (1)
	{
		if (str[nCnt3] == 0) break;

		if (str[nCnt3] == 0x0d)
		{
			nCnt3++;
			if (str[nCnt3] == 0) break;
			if (str[nCnt3] == 0x0a)
			{
				if (str[nCnt3 + 1] == 0x0d) break;
				else
				{
					nCnt3++;
					nCnt++;
					nCnt2 = 0;
				}
			}
			else
			{
				nCnt++;
				nCnt2 = 0;
				m_HelpContent[nCnt][nCnt2] = str[nCnt3];
			}

			continue;
		}
		else
		{
			m_HelpContent[nCnt][nCnt2] = str[nCnt3];
		}
		nCnt3++;
		nCnt2++;
	}

	nHeight_Count = nCnt + 1;
	m_bIsContentOver = FALSE;

	if (nHeight_Count > CONTENT_MAX)
	{
		m_bIsContentOver = TRUE;
		nHeight_Count = 6;
	}
}


BOOL CHelp::CheckLevel(int level, int type)
{
	BOOL IsLevel = FALSE;;
	switch (level)
	{
	case 1:
		if (type < 5)
		{

			GetHelpContent("CreateCha_Temscron", "Key0", "Guide1");
		}
		else
		{

			GetHelpContent("CreateCha_Moraion", "Key1", "Guide2");
		}
		IsLevel = TRUE;
		break;
	case 2:
		GetHelpContent("Level_2", "Key2", "Guide3");
		IsLevel = TRUE;
		break;
	case 3:
		GetHelpContent("Level_3", "Key3", "Guide4");
		IsLevel = TRUE;
		break;
	case 4:
		GetHelpContent("Level_4", "Key4", "Guide5");
		IsLevel = TRUE;
		break;
	case 5:
		GetHelpContent("Level_5", "Key5", "Guide6");
		IsLevel = TRUE;
		break;
	case 6:
		GetHelpContent("Level_6", "Key6", "Guide7");
		IsLevel = TRUE;

		break;
	case 7:
		GetHelpContent("Level_7", "Key24", "Guide26");
		IsLevel = TRUE;
		break;
	case 8:
		GetHelpContent("Level_8", "Key7", "Guide8");
		IsLevel = TRUE;
		break;
	case 9:
		GetHelpContent("Level_9", "Key25", "Guide27");
		IsLevel = TRUE;
		break;
	case 10:

		if (type < 5)
		{

			GetHelpContent("Level_10_Temscron", "Key8", "Guide9");
		}
		else
		{

			GetHelpContent("Level_10_Moraion", "Key9", "Guide10");
		}
		IsLevel = TRUE;
		break;


	case 11:
		GetHelpContent("Level_11", "Key11", "Guide11");
		IsLevel = TRUE;
		break;

	case 12:
		GetHelpContent("Level_12", "Key10", "Guide11");
		IsLevel = TRUE;
		break;
	case 15:
		GetHelpContent("Level_15", "Key11", "Guide12");
		IsLevel = TRUE;
		break;
	case 17:
		GetHelpContent("Level_17", "Key12", "Guide13");
		IsLevel = TRUE;
		break;
	case 20:

		if (type < 5)
		{
			GetHelpContent("Level_20_Temscron", "Key13", "Guide14");
		}
		else
		{
			GetHelpContent("Level_20_Moraion", "Key24", "Guide15");
		}
		IsLevel = TRUE;
		break;
	case 22:
		GetHelpContent("Level_22", "Key14", "Guide16");
		IsLevel = TRUE;
		break;
	case 25:
		GetHelpContent("Level_25", "Key15", "Guide17");
		IsLevel = TRUE;
		break;
	case 30:
		GetHelpContent("Level_30", "Key16", "Guide18");
		IsLevel = TRUE;
		break;
	case 39:
		GetHelpContent("Level_39", "Key26", "Guide26");
		IsLevel = TRUE;
		break;
	case 40:
		GetHelpContent("Level_40", "Key17", "Guide19");
		IsLevel = TRUE;
		break;
	case 50:
		GetHelpContent("Level_50", "Key18", "Guide20");
		IsLevel = TRUE;
		break;
	case 55:
		GetHelpContent("Level_55", "Key19", "Guide21");
		IsLevel = TRUE;
		break;
	case 60:
		GetHelpContent("Level_60", "Key20", "Guide22");
		IsLevel = TRUE;
		break;
	case 65:
		GetHelpContent("Level_65", "Key21", "Guide23");
		IsLevel = TRUE;
		break;
	case 70:
		GetHelpContent("Level_70", "Key22", "Guide24");
		IsLevel = TRUE;
		break;

	case 75:
		GetHelpContent("Level_75", "Key28", "Guide24");
		IsLevel = TRUE;
		break;


	case 79:
		GetHelpContent("Level_79", "Key79", "Guide79");
		IsLevel = TRUE;
		break;


	case 80:
		GetHelpContent("Level_80", "Key23", "Guide25");
		IsLevel = TRUE;
		break;
	}

	return IsLevel;

}


void CHelp::Draw_Help_Text(char *str, int x, int y, int sw)
{
	char strbuf[1024];

	ZeroMemory(strbuf, sizeof(strbuf));

	int strL = strlen(str);
	int cnt = 0;
	int i = 0;

	while (1)
	{
		strbuf[i] = str[cnt];
		cnt++;
		if (strbuf[i] == '\n')
		{
			strbuf[i] = 0;
			i = 0;
		jmp1:



			if (sw == 2)
			{
				SetFontTextColor(RGB(50, 50, 50));

				dsTextLineOut(x + 1, y + 1, strbuf, lstrlen(strbuf));

				SetFontTextColor(RGB(255, 240, 200));
				dsTextLineOut(x, y, strbuf, lstrlen(strbuf));
			}
			else
			{
				SetFontTextColor(RGB(255, 240, 200));
				dsTextLineOut(x, y, strbuf, lstrlen(strbuf));
			}




			ZeroMemory(strbuf, sizeof(strbuf));
			y += 16;

			if (cnt >= strL) break;
		}
		else if (cnt >= strL)
		{
			goto jmp1;
		}
		else
		{
			i++;
		}
	}


	if (sw == 1)
	{
		static int cnt = 0;
		cnt++;
		if (cnt < 20)
		{
			SetFontTextColor(RGB(255, 255, 255));
			dsTextLineOut(x + (lstrlen(str) * 6), y - 16, "|", 1);
		}
		if (cnt >= 40) cnt = 0;
	}

}




int CHelp::chkMenu(int x, int y, RECT *r)
{
	if (r->left <= x && x <= r->right)
		if (r->top <= y && y <= r->bottom)
			return 1;
	return 0;
}
int CHelp::chkeckMenuN()
{
	int i;

	for (i = 0; i < HelpMenuSu; i++)
	{
		if (chkMenu(pCursorPos.x, pCursorPos.y, &HelpMenu[i]))
		{

			return i;
		}
	}
	return -1;
}

int CHelp::dsDrawTexImageFloat(int Mat, float x, float y, float w, float h, int Transp, int specular)
{
	int clipLeft;
	int clipTop;
	int clipRight;
	int clipBottom;
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
	for (cnt = 0; cnt < 4; cnt++)

	{
		tlVertex[cnt].rhw = 1.f;
		tlVertex[cnt].color = D3DCOLOR_RGBA(255, 255, 255, Transp);
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
	DrawTexture(GuideImage->smMaterial[Mat].smTexture[0]->lpD3DTexture, tlVertex, true);
	return TRUE;
}

void CHelp::HelpEnd()
{
	m_HelpN = -1;
	isDrawClanMenu = 0;
}

void CHelp::Draw_Help_Text3(char *str, int x, int y, int sw)
{

	char strbuf[1024];

	ZeroMemory(strbuf, sizeof(strbuf));

	int strL = strlen(str);
	int cnt = 0;
	int i = 0;

	while (1)
	{


		strbuf[i] = str[cnt];
		cnt++;
		if (strbuf[i] == '\n')
		{
			strbuf[i] = 0;
			i = 0;
		jmp1:



			if (sw == 2)
			{
				SetFontTextColor(RGB(100, 100, 100));

				dsTextLineOut(x + 1, y + 1, strbuf, lstrlen(strbuf));

				SetFontTextColor(RGB(255, 240, 200));
				dsTextLineOut(x, y, strbuf, lstrlen(strbuf));
			}
			else
			{
				SetFontTextColor(RGB(255, 240, 200));
				dsTextLineOut(x, y, strbuf, lstrlen(strbuf));
			}




			ZeroMemory(strbuf, sizeof(strbuf));
			y += 16;

			if (cnt >= strL) break;
		}
		else if (cnt >= strL)
		{
			goto jmp1;
		}
		else
		{
			i++;
		}
	}


	if (sw == 1)
	{
		static int cnt = 0;
		cnt++;
		if (cnt < 20)
		{
			SetFontTextColor(RGB(255, 255, 255));
			dsTextLineOut(x + (lstrlen(str) * 6), y - 16, "|", 1);
		}
		if (cnt >= 40) cnt = 0;
	}

}

void CHelp::Draw_Help_Text2(char *str, int x, int y, int sw)
{

	char strbuf[1024];

	ZeroMemory(strbuf, sizeof(strbuf));

	int strL = strlen(str);
	int cnt = 0;
	int i = 0;

	while (1)
	{


		strbuf[i] = str[cnt];
		cnt++;
		if (strbuf[i] == '\n')
		{
			strbuf[i] = 0;
			i = 0;
		jmp1:



			if (sw == 2)
			{
				SetFontTextColor(RGB(100, 100, 100));

				dsTextLineOut(x + 1, y + 1, strbuf, lstrlen(strbuf));

				SetFontTextColor(RGB(255, 200, 100));
				dsTextLineOut(x, y, strbuf, lstrlen(strbuf));
			}
			else
			{
				SetFontTextColor(RGB(255, 200, 100));
				dsTextLineOut(x, y, strbuf, lstrlen(strbuf));
			}




			ZeroMemory(strbuf, sizeof(strbuf));
			y += 16;

			if (cnt >= strL) break;
		}
		else if (cnt >= strL)
		{
			goto jmp1;
		}
		else
		{
			i++;
		}
	}


	if (sw == 1)
	{
		static int cnt = 0;
		cnt++;
		if (cnt < 20)
		{
			SetFontTextColor(RGB(255, 255, 255));
			dsTextLineOut(x + (lstrlen(str) * 6), y - 16, "|", 1);
		}
		if (cnt >= 40) cnt = 0;
	}


}

extern BOOL IsDrawGuideHelp;

void InitGuideContentHelp()
{
	BOOL bisEqual = FALSE;
	int SaveLevel = 0;
	extern int g_LevelLabel[];
	for (int i = 0; g_LevelLabel[i] != 0; i++)
	{
		if (g_LevelLabel[i] == sinChar->Level)
		{
			bisEqual = TRUE;
			SaveLevel = i;
			break;
		}
	}
	if (!bisEqual) return;
	g_GuideHelp.SetDoing(TRUE);
	g_GuideHelp.SetStartPos(0, 0);
	g_GuideHelp.CheckLevel(sinChar->Level);


	g_GuideHelp.CheckLevel(g_LevelLabel[SaveLevel], sinChar->JOB_CODE);
	g_GuideHelp.SetHelpN(GUIDEHELP_CONTENT);
	g_GuideHelp.menuInit(GUIDEHELP_CONTENT);

	IsDrawGuideHelp = TRUE;
}

int CHelp::haGuidHelpLevel_1(DWORD Code)
{
	if ((Code&sinITEM_MASK2) == sinWA1 || (Code&sinITEM_MASK2) == sinWC1 || (Code&sinITEM_MASK2) == sinWH1 || (Code&sinITEM_MASK2) == sinWM1 || (Code&sinITEM_MASK2) == sinWN1 || (Code&sinITEM_MASK2) == sinWD1 ||
		(Code&sinITEM_MASK2) == sinWP1 || (Code&sinITEM_MASK2) == sinWS1 || (Code&sinITEM_MASK2) == sinWS2 || (Code&sinITEM_MASK2) == sinWT1)
	{
		haGuidHelpLevel_1Flag = 1;
	}
	else
		haGuidHelpLevel_1Flag = 2;

	return TRUE;
}
