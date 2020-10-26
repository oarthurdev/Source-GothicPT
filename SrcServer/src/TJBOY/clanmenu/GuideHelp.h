




























#pragma once

#ifndef __GUIDEHELP_H__
#define __GUIDEHELP_H__

#include "clan_Enti.h"

#define NOTICE_X	208
#define NOTICE_Y	61


#define GUIDEHELP_LIST		0
#define GUIDEHELP_CONTENT    1


#define HELP_CONTENT	"./image/clanImage/Help/AutoHelp/LevelUp_Content.ini"
#define HELPCONTENT_WIDTH 100
#define HELPCONTENT_HEIGHT 100
#define HEIGHT_MAX 14


#define LEVELHELP_MAX   28 

#define LEVELHELP_WIDTH	100
#define LEVELHELP_COUNT_MAX 10

#define GUIDEHLEP_CONTENT_HEIGHT_MAX  13

class CGuideHelp : public CLANEntity
{
public:
	CGuideHelp();
	~CGuideHelp();
public:
	int Init(int Life);
	int Clear();

	void Main();
	void Draw();
	void Load();
	void menuInit(int num);
	void SetHelpN(int num);
	int GetHelpN()
	{
		return m_GuideHelpN;
	}
	void SetStartPos(int x, int y);
	void InitLevelHelpLabel();

	void CheckLevel(int level);
	void GetHelpContent(char* section, char* key, char* ImageKey);
	void Parsing(char* str);
	void CheckLevel(int level, int type);
	void Draw_Help_Text(char *str, int x, int y, int sw = 0);
	void Draw_Help_Text2(char *str, int x, int y, int sw = 0);
	void SetDoing(BOOL bFlag)
	{
		bDoing = bFlag;
	}
	BOOL GetIsOn()
	{
		return bIsOn;
	}
	void Draw_Title_Text(char *str, int x, int y, int sw = 0);
	void ClearImage();
	void LoadGuideImage(char* file);
	int dsDrawTexImageFloat(int Mat, float x, float y, float w, float h, int Transp, int specular = 0);
	void GuidHelpEnd();


private:
	POINT	m_Start;
	int		m_GuideHelpN;
	BOOL		m_bDraw;

	BOOL m_bIsMouseOver;
	BOOL bIsOn;

	char	m_HelpContent[HELPCONTENT_HEIGHT][HELPCONTENT_WIDTH];
	int nHeight_Count;

	RECT scrIconPos;
	int nScl_Bar;

	int nQuetion_Icon, nQuetion_Icon1;
	int nHelp, nHelpSee, nQuideHelp, nDuru, nDuru1;
	int nLine, nScl_Bar_tj, nScl_icon_tj;
	int nGuideList;

	DIRECTDRAWSURFACE hOn;
	DIRECTDRAWSURFACE hOff;

	char LevelHelp[LEVELHELP_MAX][LEVELHELP_WIDTH];
	int nLevelHelpCount;

	BOOL bHelpIcon[50];
	BOOL bDoing;

	int nHelpCountNamugi;

	smMATERIAL_GROUP*  GuideImage;
	int			   nGuideImageNum;
	int				nSaveNamugi;


};

#endif 



#ifdef GUIDEHELP_CPP
class CGuideHelp  g_GuideHelp;
#else
extern class CGuideHelp  g_GuideHelp;
#endif


