#pragma once

class cPARTY
{
public:
	void LoadImages();
	void Draw();
	void AddMember(_PARTY_USER* pUser, int MemberNum);
	void UpdateMember(_PARTY_PLAYINFO* pUser);
	bool LButtonDown();
	bool RButtonDown();
	void Clear();
	int	RequestPartyPlayers(smCHAR	*lpChar);
	bool StopMotion();

	int mClass[2][10];
	int mMembers[6];

	enum DEFAULT
	{
		BACKGROUND,
		EXPAND,
		EXPAND_,
		LEADER,
		EXPMODE,
		EXPMODE_,
		HUNTMODE,
		HUNTMODE_,
		MAX_DEFAULT
	};

	int BaseY;

	int mDefault[MAX_DEFAULT];
	int LifeBar;
	int ManaBar;

	_PARTY_USER Members[6];

	int MemberCount;
	bool LeaderFlag;

	bool bExpand;
	int iPartyMode;

	int MenuFlag;

	enum MENU
	{
		TOP,
		MID,
		BOT,
		MAIN,
	};

	int mMenu[4];

	struct sMENUOPT
	{
		char szText[32];
		int w;
		int h;

		int ButtonNum;
		int iX;
		int iY;

		DWORD textColor;
		DWORD hoverColor;
	};

	struct sMENU
	{
		int iX;
		int iY;
		int MemberNum;
		vector<sMENUOPT*> vOption;
	};

	sMENU menu;

	void SetMenu(int x, int y, int memberNum);
	void AddOpt(char* szText, int buttonNum);
};

extern cPARTY cParty;