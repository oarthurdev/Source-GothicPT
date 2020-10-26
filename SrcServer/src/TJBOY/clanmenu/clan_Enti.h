#pragma once
#ifndef __CLAN_ENTI_HPP__
#define __CLAN_ENTI_HPP__




class CLANEntity
{
public:
	int				life;
	CLANEntity      *parent;


public:
	CLANEntity();
	~CLANEntity();

	virtual int Init();
	virtual int Clear();


	virtual void Main();
	virtual void RenderMain();


	void	setParent(CLANEntity      *p)
	{
		parent = p;
	}
	void			Kill()
	{
		life = 0;
	};
	int				IsDead()
	{
		return(life);
	};


	virtual void Draw();

	virtual void menuInit(int num);


	void Draw_C_Text(char *str, int x, int y, int sw = 0);
	void Draw_C_Text2(char *str, int x, int y, int sw = 0);
	void Draw_C_Text3(char *str, int x, int y, int sw = 0);



	void Draw_C_TextPark(char *str, int x, int y, int RedColor, int GreenColor, int BlueColor, int sw);







	int  chkMenu(int x, int y, RECT *r);
	int  chkeckMenuN();




	void ParsingIsClanMember(char* data);
	void ParsingIsClanMember2(char *data);
	int chk_readStrBuf(char *cmd, char *readbuf, char *retBuf);
	void ParsingData(char* cmd, char* data, char* save);
	void ParsingMakeClanMoney(char* data, int* money);


	void ParsigClanWon(char* data);

	void ParsingClanWonStrLen();

	void LoadToFile();



	void LoadHelp(char *help);
	void DestroyClanHelpIcon();
	void LoadHelpImage();
	BOOL ReadClanHelpScr(char *filename);
	void ReMoveClanWon(char *src);

	void WriteMyClanInfo();
	int CheckMark(BOOL bFlag);

	void CheckClanExp(char* byte);






	void Load();
	void Load2();

	virtual void Close();
	void copy_LoadResource(CLANEntity *copyDest);
	void copy_LoadResource2(CLANEntity *copyDest);

	inline void SetBase(CLANEntity *copyDest)
	{
		parent = copyDest;
	}

#ifdef USE_PROSTONTALE		
#else
	inline HBITMAP GetClanMark()
	{
		return parent->hMark;
	}
#endif


#ifdef USE_PROSTONTALE		

	int	MatPartyBackGround;
	int	hBoxCorner, hBoxLine;
	int	hBox1, hBox2, hBox3, hBox4, hBox6, hBox7, hBox8, hBox9;
	int	hScl_Bar_tj;
	int	hScl_icon_tj;
	int   hLine;


	inline DIRECTDRAWSURFACE GetClanMark()
	{
		return parent->hMark;
	}


	DIRECTDRAWSURFACE	hBt_Help;
	DIRECTDRAWSURFACE	hMark_box;
	DIRECTDRAWSURFACE	hOk_Gray, hOk_Yellow;
	DIRECTDRAWSURFACE	hCancel_Gray, hCancel_Yellow;
	DIRECTDRAWSURFACE	hYes_Gray, hYes_Yellow;
	DIRECTDRAWSURFACE	hNo_Gray, hNo_Yellow;

	DIRECTDRAWSURFACE	hMark, hClanName;
	DIRECTDRAWSURFACE	hSecession[2];
	DIRECTDRAWSURFACE	hClose[2];
	DIRECTDRAWSURFACE	hIcon;
	DIRECTDRAWSURFACE	hIcon_Click;
	DIRECTDRAWSURFACE	hHelp1;
	DIRECTDRAWSURFACE	hClinetMark;
	DIRECTDRAWSURFACE	hServerMark;
	DIRECTDRAWSURFACE	hWareHouse[2];
	DIRECTDRAWSURFACE	hWHRight[2];
	DIRECTDRAWSURFACE	hClanMark[2];
	DIRECTDRAWSURFACE	hRemove[2];
	DIRECTDRAWSURFACE	hClanRelease[2];
	DIRECTDRAWSURFACE	hHelp[2];
	DIRECTDRAWSURFACE	hOut[2];

	DIRECTDRAWSURFACE	hButton_Box;
	DIRECTDRAWSURFACE	hClanTitle;
	DIRECTDRAWSURFACE	hRemoveToMenu[2];
	DIRECTDRAWSURFACE	hScl_Bar;
	DIRECTDRAWSURFACE	hScl_icon;
	DIRECTDRAWSURFACE	hClanHelpIcon[CLANHELPICON_NUM][4];
	DIRECTDRAWSURFACE    hClanNameInput;

	DIRECTDRAWSURFACE   hTxt_Remove[2];
	DIRECTDRAWSURFACE   hTxt_Release[2];
	DIRECTDRAWSURFACE   hTxt_Mark[2];
	DIRECTDRAWSURFACE   hTxt_Help[2];
	DIRECTDRAWSURFACE   hTxt_Secession[2];
	DIRECTDRAWSURFACE   hTxt_LeaveClan[2];
	DIRECTDRAWSURFACE   hTxt_SubChip[2];
	DIRECTDRAWSURFACE   hSubChip;




	char		szHelpMsg1[HELPMSG_MAX];
	char		szErrorMsg[256];

#else

	HBITMAP	hLine;

	HBITMAP	hBox1, hBox2, hBox3, hBox4, hBox6, hBox7, hBox8, hBox9;
	HBITMAP	MatPartyBackGround;
	HBITMAP	hMark_box;
	HBITMAP	hBt_Help;

	HBITMAP	hOk_Gray, hOk_Yellow;
	HBITMAP	hCancel_Gray, hCancel_Yellow;
	HBITMAP	hYes_Gray, hYes_Yellow;
	HBITMAP	hNo_Gray, hNo_Yellow;

	HBITMAP	hMark, hClanName;
	HBITMAP	hSecession[2];
	HBITMAP	hClose[2];
	HBITMAP	hIcon;
	HBITMAP   hIcon_Click;
	HBITMAP	hHelp1;
	HBITMAP	hClinetMark;
	HBITMAP	hServerMark;
	HBITMAP	hWareHouse[2];
	HBITMAP	hWHRight[2];
	HBITMAP	hClanMark[2];
	HBITMAP	hRemove[2];
	HBITMAP	hClanRelease[2];
	HBITMAP	hHelp[2];
	HBITMAP	hOut[2];
	HBITMAP	hButton_Box;
	HBITMAP	hClanTitle;
	HBITMAP	hRemoveToMenu[2];
	HBITMAP	hScl_Bar;
	HBITMAP	hScl_icon;
	HBITMAP   hClanHelpIcon[CLANHELPICON_NUM][4];

	HBITMAP   hTxt_Remove[2];
	HBITMAP   hTxt_Release[2];
	HBITMAP   hTxt_Mark[2];
	HBITMAP   hTxt_Help[2];
	HBITMAP   hTxt_Secession[2];
	HBITMAP   hTxt_LeaveClan[2];
	HBITMAP   hTxt_SubChip[2];
	HBITMAP   hSubChip;

	HBITMAP    hClanNameInput;

	HWND		m_hClanName;
	char		szErrorMsg[256];

#endif
	BOOL bImageDown;
};

#endif 





#if defined (CLAN_EITI_CPP)


class CLANEntity  cBaseMenu;

#else

extern class CLANEntity  cBaseMenu;


#endif




