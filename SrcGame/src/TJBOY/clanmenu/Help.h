#pragma once
#ifndef __LEVELUP_HELP_H__
#define __LEVELUP_HELP_H__
#include "clan_Enti.h"

#define NOTICE_X	208
#define NOTICE_Y	61

#define LEVELUP_HELP			0
#define LEVELUP_HELP_CONTENT		1 


#define HELP_CONTENT	"./image/clanImage/Help/AutoHelp/LevelUp_Content.ini"
#define HELPCONTENT_WIDTH 100
#define HELPCONTENT_HEIGHT 100
#define HEIGHT_MAX 14
#define BOX_WIDTH_COUNT 24 + 4

#define CONTENT_MAX   6

#define DETAIL_SEE ">>자세히보기.."

class CHelp
{
public:
	CHelp();
	~CHelp();
public:
	int Init(int Life);
	int Clear();

	void Main();
	void Draw(BOOL bFlag);
	void Load();

	void HelpEnd();



	void menuInit(int num);
	void SetStartPos(int x, int y);
	void SetHelpN(int num);
	int GetHelpN()
	{
		return m_HelpN;
	}
	void GetHelpContent(char* section, char* key, char* ImageKey);
	void Parsing(char* str);
	void DrawBox(int x, int y, int x_width, int y_height);
	BOOL CheckLevel(int level, int type);
	void Draw_Help_Text(char *str, int x, int y, int sw = 0);
	int  chkMenu(int x, int y, RECT *r);
	int  chkeckMenuN();
	void ClearImage();
	void LoadGuideImage(char* file);
	int dsDrawTexImageFloat(int Mat, float x, float y, float w, float h, int Transp, int specular = 0);
	void Draw_Help_Text3(char *str, int x, int y, int sw = 0);
	void Draw_Help_Text2(char *str, int x, int y, int sw = 0);

	int haGuidHelpLevel_1(DWORD Code);

private:
	int life;
	POINT	m_Start;
	int		m_HelpN;
	BOOL		m_bDraw;
	HBITMAP hTest;
	LPDIRECT3DTEXTURE9	hClose[2];

	int nHelp0, nHelp1;
	int nGuideHelp;
	int nBox1, nBox2, nBox3, nBox4, nBox5, nBox6, nBox7, nBox8, nBox9;

	BOOL m_bIsMouseOver;
	int m_ImageCount;
	int m_ImageSlow;
	char	m_HelpContent[HELPCONTENT_HEIGHT][HELPCONTENT_WIDTH];
	int nHeight_Count;
	RECT scrIconPos;
	int nScl_Bar;

	int Box_x, Box_y;
	int nBoxWidth_Count, nBoxHeight_Count;
	int bottom_left, nStart_x, top_right, nX_Count;
	RECT HelpMenu[30];
	int  HelpMenuSu;
	int			   nGuideImageNum;
	smMATERIAL_GROUP*  GuideImage;
	BOOL		m_bTime;
	BOOL		m_bOnce;
	DWORD       m_dwTime;
	BOOL		m_bIsContentOver;

};


extern CHelp cHelp_Menu;
#endif


#ifdef LEVELUP_HELP_CPP
class CHelp  g_Help;
#else
extern class CHelp  g_Help;
#endif
