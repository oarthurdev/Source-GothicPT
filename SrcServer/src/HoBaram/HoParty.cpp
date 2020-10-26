
#include "sinbaram\\SinLinkHeader.h"
#include "..\\HoBaram\\HoLinkHeader.h"


#include "Language\\language.h"
#include "..\\HoBaram\\HoTextFile.h"


#include "tjboy/clanmenu/tjclanDEF.h"
#include "tjboy/clanmenu/tjclan.h"


extern char UserAccount[ACCOUNT_SIZE];
extern char	szConnServerName[16];



void fd222(char *buff)
{
	HANDLE hFile;
	DWORD dwAcess = 0;
	hFile = CreateFile("abc.txt", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
					   NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile != INVALID_HANDLE_VALUE)
	{
		SetFilePointer(hFile, 0, NULL, FILE_END);

		int chk = WriteFile(hFile, buff, lstrlen(buff), &dwAcess, NULL);

		CloseHandle(hFile);
	}
}


void fd(char *fmt, ...)
{
	return;

	char buff[4096] = "abc";

	va_list args;

	va_start(args, fmt);
	vsprintf(buff, fmt, args);
	va_end(args);

	strcat(buff, "\r\n");


	if(strlen(buff) > 1024)
	{
		int abc = 1;
		abc = 2;
	}

	fd222(buff);
}


void fd2(char *fmt, ...)
{
	return;

	char buff[4096];

	va_list args;

	va_start(args, fmt);
	vsprintf(buff, fmt, args);
	va_end(args);

	strcat(buff, "\r\n");

	if(strlen(buff) > 1024)
	{
		int abc = 1;
		abc = 2;
	}

	fd222(buff);
}



int read_INI(char *iniF, char *optStr1, char *optStr, char *rStr)
{
	char folder[] = ".\\";
	char strFilename[128];
	strcpy(strFilename, folder);
	strcat(strFilename, iniF);

	if(rStr == NULL)
	{
		return GetPrivateProfileInt(optStr1, optStr, 0, strFilename);
	}

	return GetPrivateProfileString(optStr1, optStr, NULL, rStr, 128, strFilename);

}

int save_INI(char *iniF, char *optStr1, char *optStr, char *rStr, int value)
{
	char folder[] = ".\\";
	char strFilename[128];
	strcpy(strFilename, folder);
	strcat(strFilename, iniF);
	char buf[64];


	if(rStr == NULL)
	{

		wsprintf(buf, "%d", value);

		return WritePrivateProfileString(
			optStr1, optStr,
			buf,
			strFilename);
	}


	return WritePrivateProfileString(
		optStr1, optStr,
		rStr,
		strFilename);



}







class HoParty_KTJ
{
public:
	HoParty_KTJ();
	~HoParty_KTJ();




	int									MatPartyBackGround;
	int									MatTitle[4 + 2];
	POINT								BackStartPos;
	int xLeft, xRight;

	RECT menuPos[30];
	int menuSu;
	int PmenuN, savePmenuN;
	void InitMenuSet(int menuN);





	int  questSelN;
	void quest_Progress_Clear();
	void quest_End_Clear();
	void quest_Progress_Set(char *q_name, char *f_name);
	int  qNameProgress_SU;
	void quest_End_Set(char *q_name, char *f_name);
	int  qNameEnd_SU;
	int  qNameS_ENDs, qNameE_ENDs;
	void qN_Pressf_CLEAR();

	void quest_Sel_Progress();

	int  qNameS, qNameE;
	int  qNameSelN;
	char qNameb[64][128];
	char qFnameb[64][128];

	char qNameb_E[64][128];
	char qFnameb_E[64][128];


	char q_explation[64][128];
	int  q_explationS;
	char q_explationTitle[128];









	char latestb[9][128];
	int  latestb_LOG[9 + 1];


	int fNameS, fNameE, fNameSu;
	char fNameb[100 + 1][32];
	int  fName_LOG[100 + 1];

	int dNameS, dNameE, dNameSu;
	int dNameSelN;
	char dNameb[100 + 1][32];
	int  dName_LOG[100 + 1];

	int cN_MenuN;
	int cN_Pressf;
	int cN_PressfDBL;
	int cN_PressfDBL_Where;



	void chat_PageChange(int sw);
	void chat_IDdelete();
	void chat_isLOG(char *name, int flag);

	void chat_cN_Pressf(int press);
	void chat_IDinsert(int sw, char *id);

	void chatINI_read();
	void chatINI_save(int menuN);
	void chatDATA_Insert(int menuN, char *str);
	void chatDATA_delete(int menuN, int num);
	void latest_Insert(char *namestr);
	int chat_IDs(int dataN, int cnt, char *id);
	void chat_WhisperPartyPlayer(int num);
	void chat_WhisperPartyPlayer_close();


	int chatbuild_INIfiles();


	void chat_changeMENU(int sw);













	hoPartyMember	PartyMember[MAX_PARTY_MEMBER];
	int				PartyMemberCount;


	int									PartyPosState;
	int									MouseDownPartyMember;

	int									MouseDownButton;



	DIRECTDRAWSURFACE				BmpMan[3];

	DIRECTDRAWSURFACE				BmpLifeBlue;
	DIRECTDRAWSURFACE				BmpLifeRed;

	DIRECTDRAWSURFACE				ToolTip[5];
	DIRECTDRAWSURFACE				Button[5];



	POINT								TextStartPos;


	int									MatMessageBoxBackGround;
	POINT								MessageBoxStartPos;

	char								PartyMessageBoxChrName[128];
	DWORD								PartyMessageBoxChrCode;

	DIRECTDRAWSURFACE				BmpMessageOk[2];
	DIRECTDRAWSURFACE				BmpMessageCancel[2];

	int				MessageBoxDrawCount;
	BOOL			MessageBoxOpenFlag;




	void Init();
	void Load();
	void Close();



	int	 Draw();


	int Main_menuSet(int sw);
	int	 Main(int sw);



	int  AddMember(char *memberName, DWORD chrCode, int life, int level);



	int AddMember(hoPartyMember *member, int cnt);
	void AddMember_memberSu(int memberSu);
	int PARTY_PLAYUPDATE(hoPartyMember *member, int cnt);
	int PARTY_RELEASE();











	int chkeckMenuN();
	void menuSet(int sw);




	void Draw_questExplane(int x, int y);
	void Init_questExplane(char *string, int sw);





	int ReadFileData(char *fname);
	void ReadFileData_moveBuf(char *savebuf, int lineLen);


};

HoParty_KTJ	InterfaceParty_KTJ;




















HoParty	InterfaceParty;



HoParty::HoParty()
{
	MessageBoxDrawCount = 0;
	BackStartPos.x = 800;
	BackStartPos.y = 155;

	TextStartPos.x = BackStartPos.x + 102;
	TextStartPos.y = BackStartPos.y + 38;

	BmpLifeBlue = NULL;
	BmpLifeRed = NULL;

	for(int index = 0; index < 5; index++)
	{
		ToolTip[index] = NULL;
		Button[index] = NULL;
	}

	for(int index = 0; index < 3; index++)
		BmpMan[index] = NULL;


	MessageBoxStartPos.x = 513;
	MessageBoxStartPos.y = 3;
	MatMessageBoxBackGround = -1;

	for(int index = 0; index < 2; index++)
	{
		BmpMessageOk[index] = NULL;
		BmpMessageCancel[index] = NULL;
	}

	MouseDownPartyMember = -1;
	MouseDownButton = -1;
	memset(PartyMember, 0, sizeof(PartyMember));
	PartyMemberCount = 0;
	MatMessageBoxBackGround = -1;

	MessageBoxOpenFlag = FALSE;
	PartyPosState = PARTY_NONE;



}


HoParty::~HoParty()
{
	Close();
}







void HoParty::quest_Progress_Clear()
{
	InterfaceParty_KTJ.quest_Progress_Clear();
}

void HoParty::quest_End_Clear()
{
	InterfaceParty_KTJ.quest_End_Clear();
}

void HoParty::quest_Progress_Set(char *q_name, char *f_name)
{
	InterfaceParty_KTJ.quest_Progress_Set(q_name, f_name);
}

void HoParty::quest_End_Set(char *q_name, char *f_name)
{
	InterfaceParty_KTJ.quest_End_Set(q_name, f_name);
}

void HoParty::qN_Pressf_CLEAR()
{
	InterfaceParty_KTJ.qN_Pressf_CLEAR();
}
void HoParty::quest_Sel_Progress()
{
	InterfaceParty_KTJ.quest_Sel_Progress();
}





void HoParty::latest_Insert(char *namestr)
{
	InterfaceParty_KTJ.latest_Insert(namestr);
}


void HoParty::friend_Insert(char *id)
{
	InterfaceParty_KTJ.chat_IDinsert(3, id);
}


void HoParty::chat_isLOG(char *name, int flag)
{
	InterfaceParty_KTJ.chat_isLOG(name, flag);
}






int HoParty::chat_IDs(int dataN, int cnt, char *id)
{
	return InterfaceParty_KTJ.chat_IDs(dataN, cnt, id);
}



void HoParty::chat_changeMENU(int sw)
{

	InterfaceParty_KTJ.chat_changeMENU(sw);
}


int HoParty::chatbuild_INIfiles()
{
	return InterfaceParty_KTJ.chatbuild_INIfiles();
}


void HoParty::chat_WhisperPartyPlayer_close()
{
	InterfaceParty_KTJ.chat_WhisperPartyPlayer_close();





	void chatlistSPEAKERflagChg(int flag);
	chatlistSPEAKERflagChg(0);
}










void HoParty::Main_menuSet(int menuN)
{
	InterfaceParty_KTJ.Main_menuSet(menuN);
}




void HoParty::InitMenuSet(int menuN)
{
	InterfaceParty_KTJ.InitMenuSet(menuN);
}


void HoParty::Init()
{
	memset(PartyMember, 0, sizeof(PartyMember));
	PartyMemberCount = 0;
	MessageBoxDrawCount = 0;
	Close();
	Load();



	InterfaceParty_KTJ.Init();
}

void HoParty::Close()
{
	if(BmpLifeBlue)
	{
		BmpLifeBlue->Release();
		BmpLifeBlue = NULL;
	}

	if(BmpLifeRed)
	{
		BmpLifeRed->Release();
		BmpLifeRed = NULL;
	}

	for(int index = 0; index < 5; index++)
	{
		if(ToolTip[index] != NULL)
		{
			ToolTip[index]->Release();
			ToolTip[index] = NULL;
		}
	}

	for(int index = 0; index < 4; index++)
	{
		if(Button[index] != NULL)
		{
			Button[index]->Release();
			Button[index] = NULL;
		}
	}

	for(int index = 0; index < 2; index++)
	{
		if(BmpMessageOk[index] != NULL)
		{
			BmpMessageOk[index]->Release();
			BmpMessageOk[index] = NULL;
		}

		if(BmpMessageCancel[index] != NULL)
		{
			BmpMessageCancel[index]->Release();
			BmpMessageCancel[index] = NULL;
		}
	}

	for(int index = 0; index < 3; index++)
	{
		if(BmpMan[index] != NULL)
		{
			BmpMan[index]->Release();
			BmpMan[index] = NULL;
		}
	}



}

void HoParty::Load()
{
	MatPartyBackGround = CreateTextureMaterial("Effect\\Party\\PartyBackGround.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	BmpLifeBlue = LoadDibSurfaceOffscreen("Effect\\Party\\LifeBlue.bmp");
	BmpLifeRed = LoadDibSurfaceOffscreen("Effect\\Party\\LifeRed.bmp");

	char buffer[256];
	for(int index = 0; index < 5; index++)
	{
		memset(buffer, 0, sizeof(buffer));
		wsprintf(buffer, "%s%d%s", "Effect\\Party\\ToolTip", index + 1, ".bmp");
		ToolTip[index] = LoadDibSurfaceOffscreen(buffer);
	}

	for(int index = 0; index < 5; index++)
	{
		memset(buffer, 0, sizeof(buffer));
		wsprintf(buffer, "%s%d%s", "Effect\\Party\\icon-", index + 1, ".bmp");
		Button[index] = LoadDibSurfaceOffscreen(buffer);
	}

	for(int index = 0; index < 3; index++)
	{
		memset(buffer, 0, sizeof(buffer));
		wsprintf(buffer, "%s%d%s", "Effect\\Party\\Man", index + 1, ".bmp");
		BmpMan[index] = LoadDibSurfaceOffscreen(buffer);
	}




	MatMessageBoxBackGround = CreateTextureMaterial("Effect\\Party\\MessageBackGround.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	for(int index = 0; index < 2; index++)
	{
		memset(buffer, 0, sizeof(buffer));
		wsprintf(buffer, "%s%d%s", "Effect\\Party\\Ok", index + 1, ".bmp");
		BmpMessageOk[index] = LoadDibSurfaceOffscreen(buffer);

		memset(buffer, 0, sizeof(buffer));
		wsprintf(buffer, "%s%d%s", "Effect\\Party\\Cancel", index + 1, ".bmp");
		BmpMessageCancel[index] = LoadDibSurfaceOffscreen(buffer);
	}

	ReadTextures();
}

extern int	WhisperPartyPlayer(char *szName);
extern int	PartyButton(int Num, int Button);

BOOL faceFlag = FALSE;
BOOL whisperFlag = FALSE;
BOOL buttonMessageFlag = FALSE;
int HoParty::Draw()
{















	if(renderDevice.IsDevice() == NULL)
		return FALSE;

	if(MouseButton[0] == FALSE)
	{
		faceFlag = FALSE;
		buttonMessageFlag = FALSE;
	}

	if(MouseDblClick == FALSE)
		whisperFlag = FALSE;

	if(PartyPosState == PARTY_START || PartyPosState == PARTY_PROCESS
	   || PartyPosState == PARTY_END)
		InterfaceParty_KTJ.Draw();

	return TRUE;
}

void HoParty::DrawPartyMessage(int x, int y)
{


	if(MessageBoxOpenFlag == TRUE)
	{
		static int PartySpotTimer = 0;
		renderDevice.BeginScene();

		if(MatMessageBoxBackGround != -1)
			dsDrawTexImage(MatMessageBoxBackGround, x, y, 256, 64, 255);
		PartySpotTimer++;

		if(PartySpotTimer > 15)
		{
			dsDrawColorBox(RGBA_MAKE(0, 200, 255, 80), x + 5, y + 5, 160, 53);
			if(PartySpotTimer > 30)
				PartySpotTimer = 0;
		}
		renderDevice.EndScene();


		HDC hdc = NULL;
		HFONT oldFont = NULL;
		//renderDevice.lpDDSBack->GetDC(&hdc);
		oldFont = (HFONT)SelectObject(hdc, hFont);

		SetBkMode(hdc, TRANSPARENT);

		SetTextColor(hdc, RGB(255, 255, 255));

		dsTextLineOut(hdc, x + 36, y + 16, PartyMessageBoxChrName, lstrlen(PartyMessageBoxChrName));
		dsTextLineOut(hdc, x + 28, y + 38, HoText_PartyMessage, lstrlen(HoText_PartyMessage));

		if(oldFont)
			SelectObject(hdc, oldFont);
		//renderDevice.lpDDSBack->ReleaseDC(hdc);




		if(pCursorPos.x > x + 140 && pCursorPos.y > y + 11 &&
		   pCursorPos.x < x + 140 + 23 && pCursorPos.y < y + 11 + 23)
		{
			if(BmpMessageOk[1] != NULL)
				DrawSprite(x + 140, y + 11, BmpMessageOk[1], 0, 0, 23, 23, 1);
			if(MouseButton[0])
			{
				SendJoinPartyUser(PartyMessageBoxChrCode);
				PartyPosState = PARTY_START;
				MessageBoxOpenFlag = FALSE;




				InitMenuSet(1);



			}
		}
		else
		{
			if(BmpMessageOk[0] != NULL)
				DrawSprite(x + 140, y + 11, BmpMessageOk[0], 0, 0, 23, 23, 1);
		}


		if(pCursorPos.x > x + 144 && pCursorPos.y > y + 37 &&
		   pCursorPos.x < x + 144 + 15 && pCursorPos.y < y + 37 + 15)
		{
			if(BmpMessageCancel[0] != NULL)
				DrawSprite(x + 144, y + 37, BmpMessageCancel[1], 0, 0, 15, 15, 1);

			if(MouseButton[0])
				MessageBoxOpenFlag = FALSE;

		}
		else
		{
			if(BmpMessageCancel[0] != NULL)
				DrawSprite(x + 144, y + 37, BmpMessageCancel[0], 0, 0, 15, 15, 1);
		}
	}
}

void HoParty::MainPartyMessage(int x, int y)
{

}

int HoParty::Main()
{
	if(PartyPosState == PARTY_START)
	{
		BackStartPos.x -= 15;
		if(BackStartPos.x <= 549)
		{
			BackStartPos.x = 549;
			PartyPosState = PARTY_PROCESS;
		}
		TextStartPos.x = BackStartPos.x + 102;
	}
	else if(PartyPosState == PARTY_END)
	{
		BackStartPos.x += 15;
		if(BackStartPos.x >= 800)
		{

			void TJBscrollWheelClear_ChatL();
			TJBscrollWheelClear_ChatL();


			void but_exit_chk();
			but_exit_chk();






			MouseDownPartyMember = -1;
			MouseDownButton = -1;
			BackStartPos.x = 800;
			PartyPosState = PARTY_NONE;
		}
		TextStartPos.x = BackStartPos.x + 102;
	}



	if(MessageBoxOpenFlag)
	{
		MessageBoxDrawCount++;
		if(MessageBoxDrawCount > 1400)
		{
			MessageBoxOpenFlag = FALSE;
			MessageBoxDrawCount = 0;
		}
	}



	int chk = InterfaceParty_KTJ.Main(PartyPosState);
	if(chk == PARTY_END)
	{


		void TJBscrollWheelClear_ChatL();
		TJBscrollWheelClear_ChatL();

		PartyPosState = PARTY_END;
	}



	return TRUE;
}


int HoParty::AddMember(char *memberName, DWORD chrCode, int life, int level)
{


	InterfaceParty_KTJ.AddMember(memberName, chrCode, life, level);


	if(memberName == NULL)
		return FALSE;

	if(PartyMemberCount >= MAX_PARTY_MEMBER)
		return FALSE;
	memcpy(PartyMember[PartyMemberCount].Name, memberName, strlen(memberName));
	PartyMember[PartyMemberCount].ChrCode = chrCode;
	PartyMember[PartyMemberCount].Life = life;
	PartyMember[PartyMemberCount].Level = 100;
	PartyMemberCount++;
	return TRUE;
}





int HoParty::AddMember(hoPartyMember *member, int cnt)
{

	InterfaceParty_KTJ.AddMember(member, cnt);



	PartyMember[cnt].ChrCode = member->ChrCode;
	PartyMember[cnt].Life = member->Life;
	PartyMember[cnt].Level = member->Level;
	PartyMember[cnt].CharacterPos.x = member->CharacterPos.x;
	PartyMember[cnt].CharacterPos.z = member->CharacterPos.z;
	PartyMember[cnt].CharacterPos.y = member->CharacterPos.y;
	strcpy_s(PartyMember[cnt].Name, member->Name);
	strcpy_s(PartyMember[cnt].ModelName1, member->ModelName1);
	strcpy_s(PartyMember[cnt].ModelName2, member->ModelName2);
	PartyMember[cnt].JangFlag = member->JangFlag;


	return TRUE;
}

void HoParty::AddMember_memberSu(int memberSu)
{

	InterfaceParty_KTJ.AddMember_memberSu(memberSu);




	PartyMemberCount = memberSu;

}

int HoParty::PARTY_PLAYUPDATE(hoPartyMember *member, int cnt)
{

	InterfaceParty_KTJ.PARTY_PLAYUPDATE(member, cnt);




	if(PartyMember[cnt].ChrCode == member->ChrCode)
	{
		PartyMember[cnt].Life = member->Life;
		PartyMember[cnt].Level = member->Level;
		PartyMember[cnt].CharacterPos.x = member->CharacterPos.x;
		PartyMember[cnt].CharacterPos.z = member->CharacterPos.z;
		return 1;
	}

	return 0;
}


void HoParty::PARTY_RELEASE()
{

	int chk =
		InterfaceParty_KTJ.PARTY_RELEASE();



	PartyMemberCount = 0;
	MouseDownPartyMember = -1;


	if(chk == 0) return;

	PartyPosState = PARTY_END;

}





































int chkMenu(int x, int y, RECT *r)
{
	if(r->left <= x   &&   x <= r->right)
	{
		if(r->top <= y   &&   y <= r->bottom)
			return 1;
	}
	return 0;
}




#define PARTY_BINFOsu 22
DIRECTDRAWSURFACE				binfo_Bmp[PARTY_BINFOsu];
#define PARTY_BUTTONsu 54
DIRECTDRAWSURFACE				butt_Bmp[PARTY_BUTTONsu];



HoParty_KTJ::HoParty_KTJ()
{

	BackStartPos.x = 800;
	BackStartPos.y = 155;


	xLeft = BackStartPos.x - 100;
	xRight = BackStartPos.x;


	questSelN = 5;


	PmenuN = 0;
	savePmenuN = 0;


	cN_MenuN = 0;
	cN_Pressf = 0;
	cN_PressfDBL = 0;
	cN_PressfDBL_Where = 0;




	MessageBoxDrawCount = 0;






	BmpLifeBlue = NULL;
	BmpLifeRed = NULL;

	for(int index = 0; index < 5; index++)
	{
		ToolTip[index] = NULL;
		Button[index] = NULL;
	}

	for(int index = 0; index < 3; index++)
		BmpMan[index] = NULL;


	MessageBoxStartPos.x = 513;
	MessageBoxStartPos.y = 3;
	MatMessageBoxBackGround = -1;

	for(int index = 0; index < 2; index++)
	{
		BmpMessageOk[index] = NULL;
		BmpMessageCancel[index] = NULL;
	}

	MouseDownPartyMember = -1;
	MouseDownButton = -1;
	memset(PartyMember, 0, sizeof(PartyMember));
	PartyMemberCount = 0;
	MatMessageBoxBackGround = -1;

	MessageBoxOpenFlag = FALSE;
	PartyPosState = PARTY_NONE;



	ZeroMemory(binfo_Bmp, sizeof(binfo_Bmp));
	ZeroMemory(butt_Bmp, sizeof(butt_Bmp));


}


HoParty_KTJ::~HoParty_KTJ()
{
	Close();
}

void HoParty_KTJ::InitMenuSet(int menuN)
{
	if(menuN == 1)
	{
		if(savePmenuN == 0)
		{
			PmenuN = menuN;
			savePmenuN = PmenuN;
		}
		else
		{
			PmenuN = savePmenuN;
		}
	}
	else
	{
		PmenuN = menuN;
	}
}
















void HoParty_KTJ::quest_Progress_Clear()
{
	ZeroMemory(qNameb, sizeof(qNameb));
	ZeroMemory(qFnameb, sizeof(qFnameb));
	qNameProgress_SU = 0;
}

void HoParty_KTJ::quest_End_Clear()
{

	ZeroMemory(qNameb_E, sizeof(qNameb_E));
	ZeroMemory(qFnameb_E, sizeof(qFnameb_E));
	qNameEnd_SU = 0;
}


void HoParty_KTJ::quest_Progress_Set(char *q_name, char *f_name)
{
	strcpy(qNameb[qNameProgress_SU], q_name);
	strcpy(qFnameb[qNameProgress_SU], f_name);

	qNameProgress_SU++;
}

void HoParty_KTJ::quest_End_Set(char *q_name, char *f_name)
{
	strcpy(qNameb_E[qNameEnd_SU], q_name);
	strcpy(qFnameb_E[qNameEnd_SU], f_name);
	qNameEnd_SU++;
}



void HoParty_KTJ::qN_Pressf_CLEAR()
{
	extern int qN_Pressf;
	extern int QuestnotCharMove, QuestnotCharMove2;
	qN_Pressf = 0;
	QuestnotCharMove = 0;
	QuestnotCharMove2 = 0;

}



void HoParty_KTJ::quest_Sel_Progress()
{
	questSelN = 5;
}










int HoParty_KTJ::chatbuild_INIfiles()
{
	HANDLE hFile;
	DWORD dwAcess = 0;

	char fname[64];



	if(szConnServerName[0] == 0)
		wsprintf(fname, ".\\savedata\\%s.ini", UserAccount);
	else
		wsprintf(fname, ".\\savedata\\%s\\%s.ini", szConnServerName, UserAccount);


	hFile = CreateFile(fname,
					   GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
		return 1;
	}



	CreateDirectory(".\\savedata", 0);
	char buf[128];

	if(szConnServerName[0] != 0)
	{
		wsprintf(buf, ".\\savedata\\%s", szConnServerName);
		CreateDirectory(buf, 0);
	}


	char inidata0[] = "[FRIEND]\r\n";
	char inidata1[] = "[DENY]\r\n";
	char inidata2[10];


	hFile = CreateFile(fname,
					   GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
					   NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	int chk = WriteFile(hFile, inidata0, lstrlen(inidata0), &dwAcess, NULL);
	for(int i = 0; i < (100 + 1); i++)
	{
		wsprintf(inidata2, "ID%0.2d=\r\n", i);
		WriteFile(hFile, inidata2, lstrlen(inidata2), &dwAcess, NULL);
	}

	chk = WriteFile(hFile, inidata1, lstrlen(inidata1), &dwAcess, NULL);
	for(int i = 0; i < (100 + 1); i++)
	{
		wsprintf(inidata2, "ID%0.2d=\r\n", i);
		WriteFile(hFile, inidata2, lstrlen(inidata2), &dwAcess, NULL);
	}

	CloseHandle(hFile);
	return chk;
}




void HoParty_KTJ::chatINI_read()
{



	char fname[64];

	if(szConnServerName[0] == 0)
		wsprintf(fname, ".\\savedata\\%s.ini", UserAccount);
	else
		wsprintf(fname, ".\\savedata\\%s\\%s.ini", szConnServerName, UserAccount);



	int i, chk;
	char buf[64];

	ZeroMemory((void*)fNameb, sizeof(fNameb));
	i = 0;
	fNameSu = i;
	while(1)
	{
		wsprintf(buf, "ID%0.2d", i);
		chk = read_INI(

			fname,
			"FRIEND", buf, fNameb[i]);
		if(chk == 0) break;
		i++;
	}


	fNameS = 0;
	fNameE = 7;
	fNameSu = i;

	ZeroMemory((void*)dNameb, sizeof(dNameb));
	i = 0;
	while(1)
	{
		wsprintf(buf, "ID%0.2d", i);
		chk = read_INI(

			fname,
			"DENY", buf, dNameb[i]);
		if(chk == 0) break;
		i++;
	}


	dNameS = 0;
	dNameE = 7;
	dNameSu = i;
}





int save_INI(char *iniF, char *optStr1, char *optStr, char *rStr, int value);

void HoParty_KTJ::chatINI_save(int menuN)
{

	char fname[64];


	if(szConnServerName[0] == 0)
		wsprintf(fname, ".\\savedata\\%s.ini", UserAccount);
	else
		wsprintf(fname, ".\\savedata\\%s\\%s.ini", szConnServerName, UserAccount);



	int i;
	char buf[64];

	switch(menuN)
	{
		case 0:
		return;
		case 1:
		for(i = 0; i < 100; i++)
		{
			wsprintf(buf, "ID%0.2d", i);
			save_INI(
				fname,
				"FRIEND", buf, fNameb[i], 0);
		}
		return;

		case 2:
		for(i = 0; i < 100; i++)
		{
			wsprintf(buf, "ID%0.2d", i);
			save_INI(
				fname,
				"DENY", buf, dNameb[i], 0);
		}
		return;
	}
}

void HoParty_KTJ::chatDATA_Insert(int menuN, char *str)
{
	int i, cnt;
	int l;

	switch(menuN)
	{
		case 0:
		return;
		case 1:
		l = strlen(str);
		for(i = 0; i < 100; i++)
		{
			if(l == strlen(fNameb[i]) && (strcmp(str, fNameb[i]) == 0))
			{
				return;
			}
		}

		cnt = 0;
		for(i = 0; i < 100; i++)
		{
			if(fNameb[i][0] == 0)
			{
				wsprintf(fNameb[i], "%s", str);
				cnt++;
				break;
			}
			cnt++;
		}
		fNameSu = cnt;
		return;
		case 2:

		l = strlen(str);
		for(i = 0; i < 100; i++)
		{
			if(l == strlen(dNameb[i]) && (strcmp(str, dNameb[i]) == 0))
			{
				return;
			}
		}



		cnt = 0;
		for(i = 0; i < 100; i++)
		{
			if(dNameb[i][0] == 0)
			{
				wsprintf(dNameb[i], "%s", str);
				cnt++;
				break;
			}
			cnt++;
		}
		dNameSu = cnt;
		return;
	}
}



void HoParty_KTJ::chatDATA_delete(int menuN, int num)
{
	int i, cnt;
	switch(menuN)
	{
		case 0:
		for(i = num; i < 7; i++)
		{
			strncpy(latestb[i], latestb[i + 1], sizeof(latestb[i]));
			latestb_LOG[i] = latestb_LOG[i + 1];
		}
		break;
		case 1:
		for(i = num; i < 100; i++)
		{
			strncpy(fNameb[i], fNameb[i + 1], sizeof(fNameb[i]));
			fName_LOG[i] = fName_LOG[i + 1];
		}

		cnt = 0;
		for(i = 0; i < 100; i++)
		{
			if(fNameb[i][0] == 0)
			{

				break;
			}
			cnt++;
		}
		fNameSu = cnt;


		if(fNameS &&  fNameb[fNameS][0] == 0)
		{
			fNameS -= 7;
			fNameE = fNameS + 7;
		}
		break;



		case 2:
		for(i = num; i < 100; i++)
		{
			strncpy(dNameb[i], dNameb[i + 1], sizeof(dNameb[i]));
			dName_LOG[i] = dName_LOG[i + 1];
		}

		cnt = 0;
		for(i = 0; i < 100; i++)
		{
			if(dNameb[i][0] == 0)
			{

				break;
			}
			cnt++;
		}
		dNameSu = cnt;

		if(dNameS &&  dNameb[dNameS][0] == 0)
		{
			dNameS -= 7;
			dNameE = dNameS + 7;
		}
		break;
	}

}





void HoParty_KTJ::latest_Insert(char *namestr)
{
	int i;



	for(i = 0; i < 7; i++)
	{
		if(latestb[i][0] != 0)
		{
			if(strcmp(latestb[i], namestr) == 0)
			{
				if(strlen(latestb[i]) == strlen(namestr))
				{
					chatDATA_delete(0, i);
					break;
				}
			}
		}
	}



	for(i = 6; i >= 1; i--)
	{
		ZeroMemory(latestb[i], sizeof(latestb[i]));
		strcpy(latestb[i], latestb[i - 1]);
	}
	strcpy(latestb[0], namestr);

}






void HoParty_KTJ::chat_PageChange(int sw)
{
	switch(cN_MenuN)
	{
		case 0:
		break;
		case 1:
		if(sw == 0)
		{
			fNameS -= 7;
			if(fNameS < 0)fNameS = 0;
			fNameE = fNameS + 7;
			if(fNameE > 100) fNameE = 100;
			return;
		}
		fNameS += 7;
		if(fNameb[fNameS][0] == 0) fNameS -= 7;
		fNameE = fNameS + 7;
		if(fNameE > 100) fNameE = 100;
		break;
		case 2:
		if(sw == 0)
		{
			dNameS -= 7;
			if(dNameS < 0)dNameS = 0;
			dNameE = dNameS + 7;

			if(dNameE > 100) dNameE = 100;
			return;
		}
		dNameS += 7;
		if(dNameb[dNameS][0] == 0) dNameS -= 7;
		dNameE = dNameS + 7;
		if(dNameE > 100) dNameE = 100;

		break;
	}
}


void HoParty_KTJ::chat_IDdelete()
{
	int i;
	switch(cN_MenuN)
	{
		case 0:
		break;
		case 1:
		if(cN_Pressf == 0) return;
		i = cN_Pressf - 3;
		i += fNameS;

		chatDATA_delete(cN_MenuN, i);
		chatINI_save(cN_MenuN);
		break;
		case 2:
		if(cN_Pressf == 0) return;
		i = cN_Pressf - 3;
		i += dNameS;

		chatDATA_delete(cN_MenuN, i);
		chatINI_save(cN_MenuN);

		break;
	}
}



void HoParty_KTJ::chat_IDinsert(int sw, char *id)
{
	int i;


	if(sw == 1)
	{
		if(cN_MenuN != 0) return;

		if(cN_Pressf == 0) return;
		i = cN_Pressf - 3;

		chatDATA_Insert(1, latestb[i]);
		chatINI_save(1);

		chatDATA_delete(0, i);
		return;
	}

	if(sw == 2)
	{
		if(cN_MenuN != 0) return;

		if(cN_Pressf == 0) return;
		i = cN_Pressf - 3;

		chatDATA_Insert(2, latestb[i]);
		chatINI_save(2);

		chatDATA_delete(0, i);
	}




	if(sw == 3)
	{
		chatDATA_Insert(1, id);
		chatINI_save(1);
		return;
	}

}








void HoParty_KTJ::chat_isLOG(char *name, int flag)
{
	int i;
	int len = strlen(name);
	for(i = 0; i < 100; i++)
	{
		if((len == strlen(fNameb[i])) ||
			(strcmp(name, fNameb[i]) == 0)
		   )
		{
			fName_LOG[i] = flag;
			return;
		}
	}


	for(i = 0; i < 100; i++)
	{
		if((len == strlen(dNameb[i])) ||
			(strcmp(name, dNameb[i]) == 0)
		   )
		{
			dName_LOG[i] = flag;
			return;
		}
	}
}




void HoParty_KTJ::chat_cN_Pressf(int press)
{
	switch(cN_MenuN)
	{
		case 0:
		press -= 3;
		if(latestb[press][0] == 0)
		{
			cN_Pressf = 0;
			return;
		}

		cN_Pressf = press + 3;
		break;

		case 1:
		press = press - 3;
		press += fNameS;

		if(fNameb[press][0] == 0)
		{
			cN_Pressf = 0;
			return;
		}
		cN_Pressf = (press - fNameS) + 3;
		break;
		case 2:
		press = press - 3;
		press += dNameS;

		if(dNameb[press][0] == 0)
		{
			cN_Pressf = 0;
			return;
		}

		cN_Pressf = (press - dNameS) + 3;
		break;
	}
}




int HoParty_KTJ::chat_IDs(int dataN, int cnt, char *id)
{
	switch(dataN)
	{
		case 0:
		if(cnt > 6) return 0;

		if(latestb[cnt][0] == 0)
		{
			return 0;
		}
		strcpy(id, latestb[cnt]);
		break;

		case 1:
		if(cnt > (100 - 1)) return 0;

		if(fNameb[cnt][0] == 0)
		{
			return 0;
		}
		strcpy(id, fNameb[cnt]);

		break;
		case 2:
		if(cnt > (100 - 1)) return 0;

		if(dNameb[cnt][0] == 0)
		{
			return 0;
		}
		strcpy(id, dNameb[cnt]);

		break;
	}

	return 1;
}





void HoParty_KTJ::chat_WhisperPartyPlayer(int num)
{
	int i;
	switch(cN_MenuN)
	{
		case 0:
		cN_PressfDBL_Where = 0;


		if(num == -1)
		{
			if(cN_PressfDBL == cN_Pressf)
			{
				cN_PressfDBL = 0;
				break;
			}
			cN_PressfDBL = cN_Pressf;
			cN_Pressf = 0;

			i = cN_PressfDBL - 3;
		}
		else
		{
			if(cN_Pressf != num)
			{
				cN_Pressf = num;
				return;
			}
			cN_PressfDBL = num;
			i = cN_PressfDBL - 3;
		}



		WhisperPartyPlayer(latestb[i]);
		break;

		case 1:

		if(num == -1)
		{

			if(cN_PressfDBL == (cN_Pressf + fNameS))
			{
				cN_PressfDBL = 0;
				cN_PressfDBL_Where = 0;
				break;
			}
			i = cN_Pressf - 3;
			i += fNameS;
			cN_Pressf = 0;
		}
		else
		{
			if(cN_Pressf != num)
			{

				cN_Pressf = num;
				return;
			}
			i = num - 3;
			i += fNameS;
		}


		WhisperPartyPlayer(fNameb[i]);
		cN_PressfDBL_Where = 1;
		cN_PressfDBL = i + 3;
		break;

		case 2:
		break;
	}
}


void HoParty_KTJ::chat_WhisperPartyPlayer_close()
{
	cN_PressfDBL = 0;
}





void HoParty_KTJ::chat_changeMENU(int sw)
{
	cN_MenuN = sw;
}

























void HoParty_KTJ::menuSet(int sw)
{
	int i;
	int menuButPosx;
	int menuButPosy;
	int qNamePosx;
	int qNamePosy;

	if(sw == 3)
	{

		void CLANmenu_ChatList(int sw);
		CLANmenu_ChatList(1);
		return;
	}


	int isClanWon = 0;



#ifdef  __CLANSUBCHIP__
	if(cldata.myPosition == 100 || cldata.myPosition == 101 || cldata.myPosition == 104)
	{
	#else
	if(cldata.myPosition == 100 || cldata.myPosition == 101)
	{
	#endif
		isClanWon = 1;
	}

	if(sw == 0)
	{


		chat_WhisperPartyPlayer_close();

		void chatlistSPEAKERflagChg(int flag);
		chatlistSPEAKERflagChg(0);


		menuPos[0].left = BackStartPos.x + 140;
		menuPos[0].top = (BackStartPos.y - 8) + 10;
		menuPos[0].right = BackStartPos.x + (140 + 105);
		menuPos[0].bottom = (BackStartPos.y - 8) + 30;

		menuPos[1].left = -1;
		menuPos[1].top = -1;
		menuPos[1].right = -1;
		menuPos[1].bottom = -1;
		menuPos[2].left = -1;
		menuPos[2].top = -1;
		menuPos[2].right = -1;
		menuPos[2].bottom = -1;
	}
	else
	{


		chat_WhisperPartyPlayer_close();

		void chatlistSPEAKERflagChg(int flag);
		chatlistSPEAKERflagChg(0);


		menuPos[0].left = -1;
		menuPos[0].top = -1;
		menuPos[0].right = -1;
		menuPos[0].bottom = -1;



		savePmenuN = sw;


		menuPos[1].left = BackStartPos.x + 60;
		menuPos[1].top = (BackStartPos.y - 8) + 10;
		menuPos[1].right = BackStartPos.x + 120;
		menuPos[1].bottom = (BackStartPos.y - 8) + 30;


		menuPos[2].left = BackStartPos.x + 120;
		menuPos[2].top = (BackStartPos.y - 8) + 10;
		menuPos[2].right = BackStartPos.x + 180;
		menuPos[2].bottom = (BackStartPos.y - 8) + 30;
	}


	switch(sw)
	{
		case 0:

		menuSu = 3;


		menuButPosx = BackStartPos.x + 100;
		menuButPosy = BackStartPos.y + 220;
		for(i = 0 + 3; i < 5 + 3; i++)
		{
			menuPos[i].left = menuButPosx + ((i - 3) * 23);
			menuPos[i].top = menuButPosy;
			menuPos[i].right = menuPos[i].left + 20;
			menuPos[i].bottom = menuPos[i].top + 20;
		}
		menuSu = 3 + 5;




		qNameS = 0, qNameE = 5;
		qNameSelN = 0;

		qNameS_ENDs = 0, qNameE_ENDs = 5;


		qNamePosx = BackStartPos.x + 110;
		qNamePosy = BackStartPos.y + 40;

		for(i = 0; i < 5; i++)
		{
			menuPos[menuSu].left = qNamePosx;
			menuPos[menuSu].top = qNamePosy;
			menuPos[menuSu].right = menuPos[menuSu].left + (12 * 10);
			menuPos[menuSu].bottom = menuPos[menuSu].top + 20;
			menuSu++;
			qNamePosy += 30;
		}





		menuButPosx = BackStartPos.x - 80;
		menuButPosy = BackStartPos.y + 220;
		i = 0;
		menuPos[menuSu].left = menuButPosx + (i * 23);
		menuPos[menuSu].top = menuButPosy;
		menuPos[menuSu].right = menuPos[menuSu].left + 34;
		menuPos[menuSu].bottom = menuPos[menuSu].top + 20;
		menuSu++;

		i = 2;
		menuPos[menuSu].left = menuButPosx + (i * 23);
		menuPos[menuSu].top = menuButPosy;
		menuPos[menuSu].right = menuPos[menuSu].left + 20;
		menuPos[menuSu].bottom = menuPos[menuSu].top + 20;
		menuSu++;

		i = 3;
		menuPos[menuSu].left = menuButPosx + (i * 23);
		menuPos[menuSu].top = menuButPosy;
		menuPos[menuSu].right = menuPos[menuSu].left + 20;
		menuPos[menuSu].bottom = menuPos[menuSu].top + 20;
		menuSu++;

		i = 5;
		menuPos[menuSu].left = menuButPosx + (i * 23) - 14;
		menuPos[menuSu].top = menuButPosy;
		menuPos[menuSu].right = menuPos[menuSu].left + 20;
		menuPos[menuSu].bottom = menuPos[menuSu].top + 20;
		menuSu++;


		break;

		case 1:
		menuSu = 3;


		menuButPosx = BackStartPos.x + 100;
		menuButPosy = BackStartPos.y + 220;
		for(i = 0 + 3; i < 5 + 3; i++)
		{
			menuPos[i].left = menuButPosx + ((i - 3) * 23);
			menuPos[i].top = menuButPosy;
			menuPos[i].right = menuPos[i].left + 20;
			menuPos[i].bottom = menuPos[i].top + 20;
		}
		menuSu = 3 + 5;


		if(isClanWon == 1)
		{

			menuPos[menuSu].left = BackStartPos.x + 180;
			menuPos[menuSu].top = (BackStartPos.y - 8) + 10;
			menuPos[menuSu].right = BackStartPos.x + 240;
			menuPos[menuSu].bottom = (BackStartPos.y - 8) + 30;
			menuSu = 3 + 5 + 1;
		}



		break;


		case 2:
		menuSu = 3;



		menuButPosx = BackStartPos.x + 100;
		menuButPosy = BackStartPos.y + 55;
		for(i = 0; i < 7; i++)
		{
			menuPos[menuSu].left = menuButPosx;
			menuPos[menuSu].top = menuButPosy;
			menuPos[menuSu].right = menuPos[menuSu].left + (12 * 10);
			menuPos[menuSu].bottom = menuPos[menuSu].top + 18;

			menuButPosy += 20;
			menuSu++;
		}



		menuSu = 3 + 7;

		menuButPosx = BackStartPos.x + 80;
		menuButPosy = BackStartPos.y + 55;
		for(i = 0; i < 7; i++)
		{
			menuPos[menuSu].left = menuButPosx;
			menuPos[menuSu].top = menuButPosy;
			menuPos[menuSu].right = menuPos[menuSu].left + 20;
			menuPos[menuSu].bottom = menuPos[menuSu].top + 18;

			menuButPosy += 20;
			menuSu++;
		}






		menuSu = 3 + 7 + 7;
		menuButPosx = BackStartPos.x + 85;
		menuButPosy = BackStartPos.y + 220;

		for(i = 0; i < 3 + 4; i++)
		{

			menuPos[menuSu].left = menuButPosx + (i * 20);

			if(i >= 3) menuPos[menuSu].left += 5;

			menuPos[menuSu].top = menuButPosy;
			menuPos[menuSu].right = menuPos[menuSu].left + 20;
			menuPos[menuSu].bottom = menuPos[menuSu].top + 20;

			menuSu++;
		}








		menuSu = 3 + 7 + 7 + 7;

		if(isClanWon == 1)
		{

			menuPos[menuSu].left = BackStartPos.x + 180;
			menuPos[menuSu].top = (BackStartPos.y - 8) + 10;
			menuPos[menuSu].right = BackStartPos.x + 240;
			menuPos[menuSu].bottom = (BackStartPos.y - 8) + 30;
			menuSu = 3 + 7 + 7 + 7 + 1;
		}




		break;
	}
	}





void HoParty_KTJ::Init()
{
	Load();

	memset(PartyMember, 0, sizeof(PartyMember));
	PartyMemberCount = 0;




	q_explationS = 0;



}



void HoParty_KTJ::Close()
{
	int i, index;
	for(i = 0; i < PARTY_BINFOsu; i++)
	{
		if(binfo_Bmp[i])
		{
			binfo_Bmp[i]->Release();
			binfo_Bmp[i] = NULL;
		}
	}

	for(i = 0; i < PARTY_BUTTONsu; i++)
	{
		if(butt_Bmp[i])
		{
			butt_Bmp[i]->Release();
			butt_Bmp[i] = NULL;
		}
	}








	if(BmpLifeBlue)
	{
		BmpLifeBlue->Release();
		BmpLifeBlue = NULL;
	}

	if(BmpLifeRed)
	{
		BmpLifeRed->Release();
		BmpLifeRed = NULL;
	}



	for(index = 0; index < 5; index++)
	{
		if(ToolTip[index] != NULL)
		{
			ToolTip[index]->Release();
			ToolTip[index] = NULL;
		}
	}

	for(index = 0; index < 4; index++)
	{
		if(Button[index] != NULL)
		{
			Button[index]->Release();
			Button[index] = NULL;
		}
	}

	for(index = 0; index < 2; index++)
	{
		if(BmpMessageOk[index] != NULL)
		{
			BmpMessageOk[index]->Release();
			BmpMessageOk[index] = NULL;
		}

		if(BmpMessageCancel[index] != NULL)
		{
			BmpMessageCancel[index]->Release();
			BmpMessageCancel[index] = NULL;
		}
	}


	for(index = 0; index < 3; index++)
	{
		if(BmpMan[index] != NULL)
		{
			BmpMan[index]->Release();
			BmpMan[index] = NULL;
		}
	}



}




void HoParty_KTJ::Load()
{
	int i, index;
	MatPartyBackGround =
		CreateTextureMaterial("image\\party\\party_win.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);



	MatTitle[0] =
		CreateTextureMaterial("image\\party\\title-quest.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatTitle[1] =
		CreateTextureMaterial("image\\party\\title-Party.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatTitle[2] =
		CreateTextureMaterial("image\\party\\title-chatting.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatTitle[3] =
		CreateTextureMaterial("image\\party\\quest_win.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);


	MatTitle[4] =
		CreateTextureMaterial("image\\party\\title-NoClan_Party.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatTitle[5] =
		CreateTextureMaterial("image\\party\\title-NoClan_chatting.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);






	char *binfoName[] = {
	"ButtonInfo-1.bmp",
	"ButtonInfo-2.bmp",
	"ButtonInfo-3.bmp",
	"ButtonInfo-4.bmp",
	"ButtonInfo-5.bmp",

	"ButtonInfo-c0.bmp",
	"ButtonInfo-c1.bmp",
	"ButtonInfo-c2.bmp",
	"ButtonInfo-c3.bmp",
	"ButtonInfo-c4.bmp",
	"ButtonInfo-c5.bmp",

	"ButtonInfo-q0.bmp",
	"ButtonInfo-q1.bmp",
	"ButtonInfo-q2.bmp",
	"ButtonInfo-q3.bmp",
	"ButtonInfo-q4.bmp",

	"ButtonInfo-qc.bmp",
	"ButtonInfo-qc-nxt.bmp",
	"ButtonInfo-qc-pre.bmp",


	"ButtonInfo-c6.bmp",
	"ButtonInfo-c7.bmp",
	"ButtonInfo-c8.bmp",
	};

	char buffer[256];
	for(i = 0; i < PARTY_BINFOsu; i++)
	{
		memset(buffer, 0, sizeof(buffer));
		wsprintf(buffer, "image\\party\\%s", binfoName[i]);
		binfo_Bmp[i] = LoadDibSurfaceOffscreen(buffer);
	}

	char *iconName[] = {
	"ButtonCancel.bmp",
	"ButtonCancel_0.bmp",

	"chatting-icon_b.bmp",
	"chattng-icon_off.bmp",
	"chattng-icon_on.bmp",
	"ButtonExit.bmp",
	"close_.bmp",

	"icon-1.bmp",
	"icon-1_.bmp",
	"icon-2.bmp",
	"icon-2_.bmp",
	"icon-3.bmp",
	"icon-3_.bmp",
	"icon-4.bmp",
	"icon-4_.bmp",

	"icon-c1.bmp",
	"icon-c1_.bmp",
	"icon-c2.bmp",
	"icon-c2_.bmp",
	"icon-c3.bmp",
	"icon-c3_.bmp",
	"icon-c4.bmp",
	"icon-c4_.bmp",
	"icon-c5.bmp",
	"icon-c5_.bmp",

	"icon-q1.bmp",
	"icon-q1_.bmp",
	"icon-q2.bmp",
	"icon-q2_.bmp",
	"icon-q3.bmp",
	"icon-q3_.bmp",
	"icon-q4.bmp",
	"icon-q4_.bmp",

	"icon-qc.bmp",
	"icon-qc_.bmp",

	"party_icon.bmp",
	"party_icon_0.bmp",
	"party_man_0.bmp",
	"party_man_1.bmp",
	"party_man_jang.bmp",

	"quest_icon-end.bmp",
	"quest_icon-ing.bmp",


	"LeftArrow.bmp",
	"LeftArrow_.bmp",
	"RightArrow.bmp",
	"RightArrow_.bmp",



	"icon-c6.bmp",
	"icon-c6_.bmp",

	"icon-7.bmp",
	"icon-7_.bmp",
	"icon-8.bmp",
	"icon-8_.bmp",
	"last_man.bmp",

	"chattng-icon-c.bmp",


	};
	for(i = 0; i < PARTY_BUTTONsu; i++)
	{
		if(i == 48)
			i = 48;
		memset(buffer, 0, sizeof(buffer));
		wsprintf(buffer, "image\\party\\%s", iconName[i]);
		butt_Bmp[i] = LoadDibSurfaceOffscreen(buffer);
	}







	BmpLifeBlue = LoadDibSurfaceOffscreen("Effect\\Party\\LifeBlue.bmp");
	BmpLifeRed = LoadDibSurfaceOffscreen("Effect\\Party\\LifeRed.bmp");





	for(index = 0; index < 3; index++)
	{
		memset(buffer, 0, sizeof(buffer));
		wsprintf(buffer, "%s%d%s", "Effect\\Party\\Man", index + 1, ".bmp");
		BmpMan[index] = LoadDibSurfaceOffscreen(buffer);
	}







	chatINI_read();
}

















extern int	WhisperPartyPlayer(char *szName);
extern int	PartyButton(int Num, int Button);





int b_Nis[] = { 25, 27, 29, 31, 5 };
int bi_Nis[] = { 18, 17, 14, 15, 4 };
int b_Nflag[] = { 0, 0, 0, 0, 0, 0, 0,0,0,0, 0,0,0,0,0,0,0,0,0 };
int b2_Nflag[] = { 0, 0, 0, 0, 0, 0, 0,0,0,0, 0,0,0,0,0,0,0,0,0 };
int qN_flag[] = { 0, 0, 0, 0, 0, 0, 0,0,0,0, 0,0,0,0,0,0,0,0,0 };
int qN_Pressf = 0;





int db_Nis[] = { 7, 9, 11, 13, 5 };
int dbi_Nis[] = { 0, 1, 2, 3, 4 };







int cb_Nis[] = { 21, 17, 46,                    42, 50, 48, 5 };
int cbi_Nis[] = { 9, 7,  8,                    17, 21, 20, 4 };
int cb_Nis1[] = { 21, 17, 46,                    42, 44, 19, 5 };
int cbi_Nis1[] = { 9, 7,  8,                    17, 18, 19, 4 };
int cb_Nis2[] = { 21, 17, 46,                    42, 44, 19, 5 };
int cbi_Nis2[] = { 9, 7,  8,                    17, 18, 19, 4 };





int QuestnotCharMove = 0;
int QuestnotCharMove2 = 0;


int HoParty_KTJ::Draw()
{
	int i, j, j2;
	if(renderDevice.IsDevice() == NULL)
		return FALSE;


	int qNamePosx = 0;
	int qNamePosy = 0;
	int mSu = 0;


	HFONT oldFont = NULL;

	if(PmenuN == 1)
		goto menu_dongru;

	if(PmenuN == 2)
		goto menu_frList;

	if(PmenuN == 3)
		goto menu_clanList;



	renderDevice.BeginScene();



	if(qN_Pressf &&  MatTitle[3] != -1)
		dsDrawTexImage(MatTitle[3],
					   BackStartPos.x - 195, BackStartPos.y + 15, 256, 256, 255);

	if(MatPartyBackGround != -1)
		dsDrawTexImage(MatPartyBackGround,
					   BackStartPos.x, BackStartPos.y, 256, 256, 255);

	if(MatTitle[PmenuN] != -1)
		dsDrawTexImage(MatTitle[PmenuN],
					   BackStartPos.x, BackStartPos.y - 8, 256, 32, 255);

	renderDevice.EndScene();

	if(PartyPosState != PARTY_PROCESS) return 1;



	mSu = 3;
	for(i = 0; i < 5; i++)
	{
		if(b_Nflag[i])
		{


			DrawSprite(menuPos[mSu].left - 30, menuPos[mSu].top - 30, binfo_Bmp[bi_Nis[i]], 0, 0, 76, 27, 1);



			DrawSprite(menuPos[mSu].left, menuPos[mSu].top, butt_Bmp[b_Nis[i]], 0, 0, 20, 20, 1);


		}
		else
		{


			DrawSprite(menuPos[mSu].left, menuPos[mSu].top, butt_Bmp[b_Nis[i] + 1], 0, 0, 20, 20, 1);
		}

		if((questSelN - 3) == i)
		{

			DrawSprite(menuPos[mSu].left, menuPos[mSu].top, butt_Bmp[b_Nis[i]], 0, 0, 20, 20, 1);
		}
		mSu++;
	}






	qNamePosx = BackStartPos.x + 116;
	qNamePosy = BackStartPos.y + 40;
	
	HDC hdc = NULL;

	//renderDevice.lpDDSBack->GetDC(&hdc);
	SetBkMode(hdc, TRANSPARENT);

	if(hFont != NULL)
		oldFont = (HFONT)SelectObject(hdc, hFont);
	for(i = qNameS; i < qNameE; i++)
	{

		if(qN_flag[i])
		{
			SetTextColor(hdc, RGB(255, 255, 255));
		}
		else
		{
			SetTextColor(hdc, RGB(255, 190, 107));
			SetTextColor(hdc, RGB(255, 255, 255));
		}

		if(qN_Pressf && (((qN_Pressf - 8) + qNameS) == i))
			SetTextColor(hdc, RGB(255, 0, 0));




		if(questSelN == 5)
		{
		#ifdef _LANGUAGE_ARGENTINA
			dsTextLineOut(hdc, qNamePosx - 30, qNamePosy, qNameb[i], lstrlen(qNameb[i]));
		#else
			dsTextLineOut(hdc, qNamePosx, qNamePosy, qNameb[i], lstrlen(qNameb[i]));
		#endif
		}
		else
		{
		#ifdef _LANGUAGE_ARGENTINA
			dsTextLineOut(hdc, qNamePosx - 30, qNamePosy, qNameb_E[i], lstrlen(qNameb_E[i]));
		#else
			dsTextLineOut(hdc, qNamePosx, qNamePosy, qNameb_E[i], lstrlen(qNameb_E[i]));
		#endif
		}

		qNamePosy += 30;
	}
	if(oldFont)
		SelectObject(hdc, oldFont);
	//renderDevice.lpDDSBack->ReleaseDC(hdc);


	qNamePosx = BackStartPos.x + 110;
	qNamePosy = BackStartPos.y + 40;
	for(i = qNameS; i < qNameE; i++)
	{


		if(questSelN == 5)
		{
			if(qNameb[i][0] == 0) break;
		}
		else
		{
			if(qNameb_E[i][0] == 0) break;
		}


		if(qN_flag[i])
		{

		#ifdef _LANGUAGE_ARGENTINA
			DrawSprite(qNamePosx - 40, qNamePosy, butt_Bmp[40], 0, 0, 14, 15, 1);
		#else
			DrawSprite(qNamePosx - 15, qNamePosy, butt_Bmp[40], 0, 0, 14, 15, 1);
		#endif
		}
		else
		{

		#ifdef _LANGUAGE_ARGENTINA
			DrawSprite(qNamePosx - 40, qNamePosy, butt_Bmp[41], 0, 0, 14, 15, 1);
		#else
			DrawSprite(qNamePosx - 15, qNamePosy, butt_Bmp[41], 0, 0, 14, 15, 1);
		#endif
		}
		qNamePosy += 30;
	}

	qNamePosx = BackStartPos.x - 80;
	qNamePosy = BackStartPos.y + 50;




	if(qN_Pressf == 0)
	{
		QuestnotCharMove = 0;
		QuestnotCharMove2 = 0;
		return 1;
	}


#ifdef _LANGUAGE_ARGENTINA
	Draw_questExplane(BackStartPos.x - 120, BackStartPos.y + 55);
#else
	Draw_questExplane(BackStartPos.x - 105, BackStartPos.y + 55);
#endif

	QuestnotCharMove = 1;
	QuestnotCharMove2 = 1;

	static int bN[] = { 33, 42, 44, 5 };
	static int bSize[] = { 34, 20, 20, 20 };

	static int bi_Nis2[] = { 0, 18, 17, 4 };


	mSu = 3 + 5 + 5;

	for(i = 0; i < 4; i++)
	{
		if(i == 0)
		{
			goto jmp111;
		}

		if(b2_Nflag[i])
		{


			DrawSprite(menuPos[mSu].left - 30, menuPos[mSu].top - 30,
					   binfo_Bmp[bi_Nis2[i]], 0, 0, 76, 27, 1);

			DrawSprite(menuPos[mSu].left, menuPos[mSu].top,
					   butt_Bmp[bN[i]], 0, 0, bSize[i], 20, 1);

		}
		else
		{
			DrawSprite(menuPos[mSu].left, menuPos[mSu].top,
					   butt_Bmp[bN[i] + 1], 0, 0, bSize[i], 20, 1);
		}

	jmp111:
		mSu++;
	}



	return 1;

menu_dongru:

	renderDevice.BeginScene();


	if(MatPartyBackGround != -1)
		dsDrawTexImage(MatPartyBackGround,
					   BackStartPos.x, BackStartPos.y,
					   256, 256, 255);



#ifdef  __CLANSUBCHIP__
	if(cldata.myPosition == 100 || cldata.myPosition == 101 || cldata.myPosition == 104)
	#else
	if(cldata.myPosition == 100 || cldata.myPosition == 101)
	#endif

	{

		if(MatTitle[PmenuN] != -1)
			dsDrawTexImage(MatTitle[PmenuN], BackStartPos.x, BackStartPos.y - 8, 256, 32, 255);

	}
	else
	{

		if(MatTitle[4] != -1)
			dsDrawTexImage(MatTitle[4], BackStartPos.x, BackStartPos.y - 8, 256, 32, 255);
	}




	renderDevice.EndScene();


	if(PartyPosState != PARTY_PROCESS) return 1;


















	TextStartPos.x = BackStartPos.x + 80;
	TextStartPos.y = BackStartPos.y + 38;

	for(int index = 0; index < PartyMemberCount; index++)
	{


		if(BmpLifeBlue != NULL && BmpLifeRed != NULL)
		{

			DrawSprite(TextStartPos.x - 3 + 14, TextStartPos.y + 30 * index - 2 + 15, BmpLifeRed, 0, 0, 94, 4, 1);
			DrawSprite(TextStartPos.x - 3 + 14, TextStartPos.y + 30 * index - 2 + 15, BmpLifeBlue, 0, 0, int((94.f / 100.f)*(float)PartyMember[index].Life), 4, 1);
		}


		if(pCursorPos.x > TextStartPos.x && pCursorPos.y > TextStartPos.y + 30 * index - 10 &&
		   pCursorPos.x < TextStartPos.x + 110 && pCursorPos.y < TextStartPos.y + 30 * index + 18)
		{

			if(BmpMan[1] != NULL && PartyMember[index].JangFlag == FALSE)
				DrawSprite(TextStartPos.x - 4, TextStartPos.y + 30 * index - 2, BmpMan[1], 0, 0, 13, 17, 1);

			if(BmpMan[3] != NULL && PartyMember[index].JangFlag)
				DrawSprite(TextStartPos.x - 4, TextStartPos.y + 30 * index - 2, BmpMan[2], 0, 0, 13, 17, 1);


			if(MouseButton[0] && PartyPosState == PARTY_PROCESS)
			{
				MouseDownPartyMember = index;


				if(strlen(PartyMember[MouseDownPartyMember].Name) != 0 &&
				   strlen(PartyMember[MouseDownPartyMember].ModelName1) != 0 &&
				   strlen(PartyMember[MouseDownPartyMember].ModelName2) != 0 && faceFlag == FALSE)
				{
					if(faceFlag == FALSE)
					{
						faceFlag = TRUE;
						OpenPartyPlayer(PartyMember[MouseDownPartyMember].Name, PartyMember[MouseDownPartyMember].ModelName1, PartyMember[MouseDownPartyMember].ModelName2);
					}
				}
			}


			if(MouseDblClick && whisperFlag == FALSE)
			{

				if(lpCurPlayer->dwObjectSerial != PartyMember[index].ChrCode)
				{
					whisperFlag = TRUE;

					WhisperPartyPlayer(PartyMember[index].Name);
				}
			}

		}
		else
		{

			if(BmpMan[0] != NULL && PartyMember[index].JangFlag == FALSE)
				DrawSprite(TextStartPos.x - 4, TextStartPos.y + 30 * index - 2, BmpMan[0], 0, 0, 13, 17, 1);

			if(BmpMan[3] != NULL && PartyMember[index].JangFlag)
				DrawSprite(TextStartPos.x - 4, TextStartPos.y + 30 * index - 2, BmpMan[2], 0, 0, 13, 17, 1);
		}
	}




	if(PartyPosState == PARTY_PROCESS)
	{

		if(MouseDownPartyMember != -1 && PartyMember[MouseDownPartyMember].JangFlag == FALSE)
			DrawSprite(TextStartPos.x - 4, TextStartPos.y + 30 * MouseDownPartyMember - 2, BmpMan[1], 0, 0, 13, 17, 1);
		if(MouseDownPartyMember != -1 && PartyMember[MouseDownPartyMember].JangFlag == TRUE)
			DrawSprite(TextStartPos.x - 4, TextStartPos.y + 30 * MouseDownPartyMember - 2, BmpMan[2], 0, 0, 13, 17, 1);
	}




	//renderDevice.lpDDSBack->GetDC(&hdc);

	hdc = NULL;
	hFont = NULL;

	if(hFont != NULL)
		oldFont = (HFONT)SelectObject(hdc, hFont);


	SetBkMode(hdc, TRANSPARENT);


	char levelBuffer[256];
	for(int index = 0; index < PartyMemberCount; index++)
	{
		SetTextColor(hdc, RGB(0, 0, 0));
		dsTextLineOut(hdc, TextStartPos.x + 11, TextStartPos.y + 30 * index + 1, PartyMember[index].Name, lstrlen(PartyMember[index].Name));
		memset(levelBuffer, 0, sizeof(levelBuffer));

		wsprintf(levelBuffer, "%s%d", "L", PartyMember[index].Level);
		dsTextLineOut(hdc, TextStartPos.x + 110, TextStartPos.y + 5 + 30 * index + 1, levelBuffer, lstrlen(levelBuffer));
	}



	SetBkMode(hdc, TRANSPARENT);
	for(int index = 0; index < PartyMemberCount; index++)
	{
		if(MouseDownPartyMember != index)
			SetTextColor(hdc, RGB(209, 190, 154));
		else
			SetTextColor(hdc, RGB(255, 150, 0));

		if(pCursorPos.x > TextStartPos.x && pCursorPos.y > TextStartPos.y + 30 * index - 10 &&
		   pCursorPos.x < TextStartPos.x + 110 && pCursorPos.y < TextStartPos.y + 30 * index + 18)
			SetTextColor(hdc, RGB(255, 150, 0));
		dsTextLineOut(hdc, TextStartPos.x + 10, TextStartPos.y + 30 * index, PartyMember[index].Name, lstrlen(PartyMember[index].Name));

		memset(levelBuffer, 0, sizeof(levelBuffer));

		wsprintf(levelBuffer, "%s%d", "L", PartyMember[index].Level);

		SetTextColor(hdc, RGB(255, 190, 107));
		dsTextLineOut(hdc, TextStartPos.x + 110, TextStartPos.y + 5 + 30 * index, levelBuffer, lstrlen(levelBuffer));
	}
	if(oldFont)
		SelectObject(hdc, oldFont);
	//renderDevice.lpDDSBack->ReleaseDC(hdc);










	mSu = 3;
	for(i = 0; i < 5; i++)
	{
		if(b_Nflag[i])
		{



			if(lpCurPlayer->dwObjectSerial != PartyMember[0].ChrCode)
			{
				if(i == 0 || i == 1 || i == 2)
					goto jump0;
			}

			if(PartyMemberCount == 0)
			{
				if(i == 0 || i == 1 || i == 2 || i == 3)
					goto jump0;
			}




			DrawSprite(menuPos[mSu].left - 30, menuPos[mSu].top - 30,
					   binfo_Bmp[dbi_Nis[i]], 0, 0, 76, 27, 1);


			DrawSprite(menuPos[mSu].left, menuPos[mSu].top, butt_Bmp[db_Nis[i]], 0, 0, 20, 20, 1);
		}
		else
		{
		jump0:
			DrawSprite(menuPos[mSu].left, menuPos[mSu].top, butt_Bmp[db_Nis[i] + 1], 0, 0, 20, 20, 1);
		}


		mSu++;
	}






















	for(int index = 0; index < 5; index++)
	{


		if(menuPos[3 + index].left <= pCursorPos.x  && pCursorPos.x <= menuPos[3 + index].right &&
		   menuPos[3 + index].top <= pCursorPos.y  && pCursorPos.y <= menuPos[3 + index].bottom)
		{
			if(lpCurPlayer->dwObjectSerial != PartyMember[0].ChrCode)
			{
				if(index == 0 || index == 1 || index == 2)
					continue;
			}

			if(PartyMemberCount == 0 && index != 4)
				continue;


			DrawSprite(BackStartPos.x + 110 + index * 23, BackStartPos.y + 220, Button[index], 0, 0, 20, 20, 1);

			if(MouseButton[0] && PartyPosState == PARTY_PROCESS)
			{

				if(buttonMessageFlag == FALSE)
				{
					MouseDownButton = index;
					buttonMessageFlag = TRUE;

					PartyButton(MouseDownPartyMember, index);
					MouseDownPartyMember = -1;
				}


				if(MouseDownButton == 4)
					PartyPosState = PARTY_END;
			}
		}
	}



	return 1;


menu_frList:

	renderDevice.BeginScene();


	if(MatPartyBackGround != -1)
		dsDrawTexImage(MatPartyBackGround,
					   BackStartPos.x, BackStartPos.y,
					   256, 256, 255);



#ifdef  __CLANSUBCHIP__
	if(cldata.myPosition == 100 || cldata.myPosition == 101 || cldata.myPosition == 104)
	#else
	if(cldata.myPosition == 100 || cldata.myPosition == 101)
	#endif

	{

		if(MatTitle[PmenuN] != -1)
			dsDrawTexImage(MatTitle[PmenuN], BackStartPos.x, BackStartPos.y - 8, 256, 32, 255);

	}
	else
	{

		if(MatTitle[5] != -1)
			dsDrawTexImage(MatTitle[5], BackStartPos.x, BackStartPos.y - 8, 256, 32, 255);
	}

	renderDevice.EndScene();




	mSu = 3;
	if(PartyPosState != PARTY_PROCESS) return 1;




	int *intp_N, *intp_Ni;
	if(cN_MenuN == 0)
	{
		intp_N = cb_Nis;
		intp_Ni = cbi_Nis;
	}
	else if(cN_MenuN == 1)
	{
		intp_N = cb_Nis1;
		intp_Ni = cbi_Nis1;
	}
	else
	{
		intp_N = cb_Nis2;
		intp_Ni = cbi_Nis2;
	}

	mSu = 3 + 7 + 7;
	for(i = 0; i < 3 + 4; i++)
	{
		if(cN_MenuN == 0 && i == 3)
			goto jmp1;



		if(cN_MenuN == 0 && i == 0) goto jmp1_1;
		if(cN_MenuN == 1 && i == 1) goto jmp1_1;
		if(cN_MenuN == 2 && i == 2) goto jmp1_1;


		if(b_Nflag[i])
		{



			DrawSprite(menuPos[mSu].left - 30, menuPos[mSu].top - 26,
					   binfo_Bmp[intp_Ni[i]], 0, 0, 76, 27, 1);
		jmp1_1:

			DrawSprite(menuPos[mSu].left, menuPos[mSu].top,
					   butt_Bmp[intp_N[i]], 0, 0, 20, 20, 1);
		}
		else
		{
			DrawSprite(menuPos[mSu].left, menuPos[mSu].top,
					   butt_Bmp[intp_N[i] + 1], 0, 0, 20, 20, 1);
		}

	jmp1:
		mSu++;
	}

	
	mSu = 3;


	hdc = NULL;

	//renderDevice.lpDDSBack->GetDC(&hdc);
	SetBkMode(hdc, TRANSPARENT);
	if(hFont != NULL)
		oldFont = (HFONT)SelectObject(hdc, hFont);


	SetTextColor(hdc, RGB(255, 255, 255));
	if(cN_MenuN == 0)
	{






		SetTextColor(hdc, RGB(255, 220, 0));

		dsTextLineOut(hdc, menuPos[mSu].left + 20, menuPos[mSu].top - 24, HoTextFriendNear, lstrlen(HoTextFriendNear));

		j2 = -1;
		for(i = 0; i < 7; i++)
		{

			if(cN_Pressf == 0)
				j = -1;
			else
				j = cN_Pressf - 3;

			if(cN_PressfDBL && cN_PressfDBL_Where == 0)
				j2 = cN_PressfDBL - 3;





			if(j2 == i)
			{
				SetTextColor(hdc, RGB(255, 0, 0));
			}
			else if(j == i)
			{
				SetTextColor(hdc, RGB(255, 200, 100));
			}
			else
			{
				SetTextColor(hdc, RGB(255, 255, 255));
			}

			dsTextLineOut(hdc, menuPos[mSu].left, menuPos[mSu].top, latestb[i], lstrlen(latestb[i]));


			mSu++;
		}



	}
	else if(cN_MenuN == 1)
	{

		int max = (fNameSu / 7);
		if(fNameSu % 7) max++;

		int min = (fNameS / 7);
		if(fNameSu) min++;


		char buf[128];

		wsprintf(buf, HoTextFriendList, min, max);

		SetTextColor(hdc, RGB(255, 220, 0));
		dsTextLineOut(hdc, menuPos[mSu].left + 15, menuPos[mSu].top - 24, buf, strlen(buf));


		for(i = fNameS; i < fNameE; i++)
		{
			j = -1;
			if(cN_Pressf)
			{
				j = cN_Pressf - 3;
				j += fNameS;
			}
			j2 = -1;
			if(cN_PressfDBL && cN_PressfDBL_Where == 1)
			{
				j2 = cN_PressfDBL - 3;
			}

			if(j2 == i)
			{
				SetTextColor(hdc, RGB(255, 0, 0));
			}
			else if(j == i)
			{
				SetTextColor(hdc, RGB(255, 200, 100));
			}
			else
				SetTextColor(hdc, RGB(255, 255, 255));
			dsTextLineOut(hdc, menuPos[mSu].left, menuPos[mSu].top, fNameb[i], lstrlen(fNameb[i]));

			mSu++;
		}


	}
	else
	{
		char buf[128];
		int max = (dNameSu / 7);
		if(dNameSu % 7) max++;

		int min = (dNameS / 7);
		if(dNameSu) min++;


		wsprintf(buf, HoTextFriendRefuse, min, max);

		SetTextColor(hdc, RGB(255, 220, 0));
		dsTextLineOut(hdc, menuPos[mSu].left + 10, menuPos[mSu].top - 24, buf, strlen(buf));

		if(dNameS > 13)
		{
			dNameS = dNameS;
		}

		for(i = dNameS; i < dNameE; i++)
		{

			j = -1;
			if(cN_Pressf)
			{
				j = cN_Pressf - 3;
			}

			if(j == i)
			{
				SetTextColor(hdc, RGB(255, 200, 100));
			}
			else
				SetTextColor(hdc, RGB(255, 255, 255));
			dsTextLineOut(hdc, menuPos[mSu].left, menuPos[mSu].top, dNameb[i], lstrlen(dNameb[i]));

			mSu++;
		}

	}


	if(oldFont)
		SelectObject(hdc, oldFont);
	//renderDevice.lpDDSBack->ReleaseDC(hdc);





	mSu = 3;

	if(cN_MenuN == 0)
	{

		j = cN_PressfDBL - 3;
		for(i = 0; i < 7; i++)
		{

			if(latestb[i][0] == 0) goto jmp10;


			if(cN_PressfDBL && cN_PressfDBL_Where == 0)
			{
				if(j == i)
				{
					DrawSprite(menuPos[mSu].left - 23, menuPos[mSu].top - 3,
							   butt_Bmp[53], 0, 0, 16, 16, 1);
					goto jmp10;
				}
			}






			DrawSprite(menuPos[mSu].left - 23, menuPos[mSu].top - 5,
					   butt_Bmp[52], 0, 0, 20, 20, 1);
		jmp10:

			mSu++;
		}
	}



	if(cN_MenuN == 1)
	{

		for(i = fNameS; i < fNameE; i++)
		{

			if(fNameb[i][0] == 0) goto jmp11;


			if(cN_PressfDBL && cN_PressfDBL_Where == 1)
			{
				j = cN_PressfDBL - 3;
				if(j == i)
				{
					DrawSprite(menuPos[mSu].left - 23, menuPos[mSu].top - 3,
							   butt_Bmp[53], 0, 0, 16, 16, 1);
					goto jmp11;
				}
			}



			DrawSprite(menuPos[mSu].left - 23, menuPos[mSu].top - 2,
					   butt_Bmp[4], 0, 0, 16, 16, 1);




		jmp11:

			mSu++;
		}
	}

	if(cN_MenuN == 2)
	{

		for(i = dNameS; i < dNameE; i++)
		{
			if(dNameb[i][0] == 0) goto jmp12;


			DrawSprite(menuPos[mSu].left - 23, menuPos[mSu].top - 2,
					   butt_Bmp[2], 0, 0, 16, 16, 1);




		jmp12:
			mSu++;
		}
	}


	return TRUE;



menu_clanList:

	void CLANmenu_ChatList_Draw();
	CLANmenu_ChatList_Draw();

	return TRUE;

}










int HoParty_KTJ::Main_menuSet(int sw)
{
	PmenuN = sw;
	BackStartPos.x = 539;
	PartyPosState = PARTY_PROCESS;
	menuSet(PmenuN);
	return 1;
}





void but_exit_chk()
{
	extern int ret_menuN;
	ret_menuN = 0;
	InterfaceParty_KTJ.PmenuN = 2;
}




int HoParty_KTJ::Main(int sw)
{
	int i;
	char namebuf[256];



	PartyPosState = sw;


	if(PartyPosState == PARTY_START)
	{



		if(PmenuN == 1 && PartyMember[0].Name[0] == 0)
			PmenuN = 2;



		BackStartPos.x -= 20;

		if(BackStartPos.x <= 539)

		{

			BackStartPos.x = 539;

			PartyPosState = PARTY_PROCESS;
		}
		menuSet(PmenuN);




		for(i = 0; i < 8; i++)
		{
			b_Nflag[i] = 0;
			b2_Nflag[i] = 0;

			if(i < 5)
				qN_flag[i] = 0;
		}




	}
	else if(PartyPosState == PARTY_END)
	{


		BackStartPos.x += 20;
		if(BackStartPos.x >= 800)

		{
			MouseDownPartyMember = -1;
			MouseDownButton = -1;
			BackStartPos.x = 800;

			PartyPosState = PARTY_NONE;


			qN_Pressf_CLEAR();
		}



	}



	switch(sw)
	{
		case PARTY_START:
		break;

		case PARTY_PROCESS:

		for(i = 0; i < 8; i++)
		{
			b_Nflag[i] = 0;
			b2_Nflag[i] = 0;

			if(i < 5)
				qN_flag[i] = 0;
		}


		i = chkeckMenuN();


		if(PmenuN == 0)
		{
			switch(i)
			{
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				b_Nflag[i - 3] = 1;
				break;

				case 8:
				case 9:
				case 10:
				case 11:
				case 12:
				qN_flag[i - 8] = 0;
				break;


				case 13:

				break;
				case 14:
				b2_Nflag[(i - 13)] = 1;
				break;
				case 15:
				b2_Nflag[(i - 13)] = 1;
				break;
				case 16:
				b2_Nflag[(i - 13)] = 1;
				break;

			}

			if(MouseButton[0])
			{
				if(i != -1)
					MouseButton[0] = 0;
				switch(i)
				{
					case -1: break;
					case 0:	break;
					case 1:
					case 2:
					PmenuN = i;
					menuSet(PmenuN);
					break;


					case 3:

					if(questSelN == 5)
					{
						qNameS -= 8;
						if(qNameS < 0)qNameS = 0;
						qNameE = qNameS + 5;
					}
					else
					{
						qNameS_ENDs -= 8;
						if(qNameS_ENDs < 0)qNameS_ENDs = 0;
						qNameE_ENDs = qNameS_ENDs + 5;
					}

					break;
					case 4:
					if(questSelN == 5)
					{
						qNameS += 8;
						if(qNameb[qNameS][0] == 0)
						{
							qNameS -= 8;
						}
						qNameE = qNameS + 5;
					}
					else
					{

						qNameS_ENDs += 8;
						if(qNameb_E[qNameS][0] == 0)
						{
							qNameS_ENDs -= 8;
						}
						qNameE_ENDs = qNameS_ENDs + 5;

					}

					break;






					case 5:
					if(questSelN == 5) break;
					questSelN = 5;
					qN_Pressf = 0;

					break;


					case 6:
					if(questSelN == 6) break;

					questSelN = 6;
					qN_Pressf = 0;
					break;

					case 7:

					qN_Pressf = 0;
					return PARTY_END;


					case 8:
					case 9:
					case 10:
					case 11:
					case 12:
					if(questSelN == 5)
					{
						if(qNameb[qNameS + (i - 8)][0] == 0)	break;
						if(qN_Pressf == i)
						{
							qN_Pressf = 0;	break;
						}
						qN_Pressf = i;


						strcpy(q_explationTitle, qNameb[qNameS + (i - 8)]);


						wsprintf(namebuf, ".\\image\\party\\party_DATA\\%s", qFnameb[qNameS + (i - 8)]);
						if(ReadFileData(namebuf) == 0)
						{
							ReadFileData(".\\image\\party\\party_DATA\\quest_imsi.txt");
						}
						ZeroMemory((void *)q_explation, sizeof(q_explation));
						ReadFileData_moveBuf((char *)q_explation, 128);


					}
					else
					{

						if(qNameb_E[qNameS_ENDs + (i - 8)][0] == 0)	break;
						if(qN_Pressf == i)
						{
							qN_Pressf = 0;	break;
						}
						qN_Pressf = i;


						strcpy(q_explationTitle, qNameb_E[qNameS_ENDs + (i - 8)]);


						wsprintf(namebuf, ".\\image\\party\\party_DATA\\%s", qFnameb_E[qNameS_ENDs + (i - 8)]);
						if(ReadFileData(namebuf) == 0)
						{
							ReadFileData(".\\image\\party\\party_DATA\\quest_imsi.txt");
						}
						ZeroMemory((void *)q_explation, sizeof(q_explation));
						ReadFileData_moveBuf((char *)q_explation, 128);
					}



					break;




					case 13:
					break;

					case 14:
					if(qN_Pressf == 0) break;
					q_explationS -= 8;
					if(q_explationS < 0)q_explationS = 0;
					break;
					case 15:
					if(qN_Pressf == 0) break;

					q_explationS += 8;
					if(q_explation[q_explationS][0] == 0)
					{
						q_explationS -= 8;
					}
					break;
					case 16:
					b2_Nflag[(i - 13)] = 1;

					qN_Pressf = 0;
					break;

				}
			}

		}
		else if(PmenuN == 1)
		{
			switch(i)
			{
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				b_Nflag[i - 3] = 1;
				break;
			}

			if(MouseButton[0])
			{



				switch(i)
				{
					case -1: break;
					case 1:	break;
					case 0:
					case 2:
					case 8:
					if(i == 8) i = 3;
					PmenuN = i;
					menuSet(PmenuN);


					break;


					case 3:
					case 4:
					case 5:
					case 6:

					break;
					case 7:
					MouseButton[0] = 0;
					return PARTY_END;
				}
			}


		}
		else if(PmenuN == 2)
		{

			switch(i)
			{
				case 3:
				case 4:

				case 5:
				case 6:
				case 7:
				case 8:
				case 9:
				break;




				case 17:
				case 18:
				case 19:

				case 20:
				case 21:
				case 22:
				case 23:
				b_Nflag[i - 17] = 1;
				break;
			}









			if(MouseButton[0])
			{
				if(i != -1)
					MouseButton[0] = 0;
				switch(i)
				{
					case -1: break;
					case 2:  break;
					case 0:
					case 1:
					case 24:
					if(i == 24) i = 3;
					if(cN_PressfDBL != 0) break;

					PmenuN = i;
					menuSet(PmenuN);
					break;


					case 3:
					case 4:
					case 5:
					case 6:
					case 7:
					case 8:
					case 9:

					chat_cN_Pressf(i);
					break;

					case 10:
					case 11:
					case 12:
					case 13:
					case 14:
					case 15:
					case 16:
					chat_WhisperPartyPlayer((i - 10) + 3);
					break;




					case 17:
					cN_MenuN = 0;
					cN_Pressf = 0;
					break;
					case 18:
					cN_MenuN = 1;
					cN_Pressf = 0;

					break;
					case 19:
					cN_MenuN = 2;
					cN_Pressf = 0;
					break;

					case 20:

					chat_PageChange(0);
					cN_Pressf = 0;
					break;
					case 21:

					chat_PageChange(1);

					chat_IDinsert(1, NULL);
					cN_Pressf = 0;
					break;

					case 22:
					chat_IDdelete();

					chat_IDinsert(2, NULL);

					cN_Pressf = 0;
					cN_PressfDBL = 0;
					break;
					case 23:
					cN_Pressf =
						cN_PressfDBL = 0;
					return PARTY_END;
				}
			}





			if(MouseDblClick)
			{
				switch(i)
				{
					case 3:
					case 4:
					case 5:
					case 6:
					case 7:
					case 8:
					case 9:



					chat_WhisperPartyPlayer(-1);
					MouseDblClick = 0;
					break;



				}
			}

		}
		else
		{

			void CLANmenu_ChatList_Main();
			CLANmenu_ChatList_Main();
			extern int ret_menuN;
			switch(ret_menuN)
			{
				case 1:
				case 2:
				PmenuN = ret_menuN;
				menuSet(PmenuN);
				break;
				case 3:

				ret_menuN = 0;
				PmenuN = 2;

				MouseButton[0] = 0;

				void cN_PressfDBL_clear();
				cN_PressfDBL_clear();
				return PARTY_END;
			}
		}



		break;

		case PARTY_END:
		break;
	}

	return TRUE;
}




int HoParty_KTJ::AddMember(char *memberName, DWORD chrCode, int life, int level)
{
	if(memberName == NULL)
		return FALSE;

	if(PartyMemberCount >= MAX_PARTY_MEMBER)
		return FALSE;
	memcpy(PartyMember[PartyMemberCount].Name, memberName, strlen(memberName));
	PartyMember[PartyMemberCount].ChrCode = chrCode;
	PartyMember[PartyMemberCount].Life = life;
	PartyMember[PartyMemberCount].Level = 100;
	PartyMemberCount++;
	return TRUE;
}



int HoParty_KTJ::AddMember(hoPartyMember *member, int cnt)
{
	PartyMember[cnt].ChrCode = member->ChrCode;
	PartyMember[cnt].Life = member->Life;
	PartyMember[cnt].Level = member->Level;
	PartyMember[cnt].CharacterPos.x = member->CharacterPos.x;
	PartyMember[cnt].CharacterPos.z = member->CharacterPos.z;
	PartyMember[cnt].CharacterPos.y = member->CharacterPos.y;
	strcpy_s(PartyMember[cnt].Name, member->Name);
	strcpy_s(PartyMember[cnt].ModelName1, member->ModelName1);
	strcpy_s(PartyMember[cnt].ModelName2, member->ModelName2);
	PartyMember[cnt].JangFlag = member->JangFlag;

	return TRUE;
}

void HoParty_KTJ::AddMember_memberSu(int memberSu)
{
	PartyMemberCount = memberSu;
}

int HoParty_KTJ::PARTY_PLAYUPDATE(hoPartyMember *member, int cnt)
{
	if(PartyMember[cnt].ChrCode == member->ChrCode)
	{
		PartyMember[cnt].Life = member->Life;
		PartyMember[cnt].Level = member->Level;
		PartyMember[cnt].CharacterPos.x = member->CharacterPos.x;
		PartyMember[cnt].CharacterPos.z = member->CharacterPos.z;
		return 1;
	}
	return 0;
}


int HoParty_KTJ::PARTY_RELEASE()
{
	PartyMemberCount = 0;
	MouseDownPartyMember = -1;

	if(PmenuN == 0) return PmenuN;



	void TJBscrollWheelClear_ChatL();
	TJBscrollWheelClear_ChatL();


	PartyPosState = PARTY_END;

	return PmenuN;
}






int HoParty_KTJ::chkeckMenuN()
{
	int i;

	for(i = 0; i < menuSu; i++)
	{
		if(chkMenu(pCursorPos.x, pCursorPos.y, &menuPos[i]))
		{
			return i;
		}
	}
	return -1;
}










void HoParty_KTJ::Draw_questExplane(int x, int y)
{
	int i = 0;
	HDC hdc = NULL;
	HFONT oldFont = NULL;


	//renderDevice.lpDDSBack->GetDC(&hdc);
	SetBkMode(hdc, TRANSPARENT);

	if(hFont != NULL)
		oldFont = (HFONT)SelectObject(hdc, hFont);


	SetTextColor(hdc, RGB(255, 190, 107));
	dsTextLineOut(hdc, x + 30, y - 20, q_explationTitle, lstrlen(q_explationTitle));

	for(i = q_explationS; i < q_explationS + 8; i++)
	{
		SetTextColor(hdc, RGB(255, 190, 107));
		dsTextLineOut(hdc, x, y, q_explation[i], lstrlen(q_explation[i]));
		y += 20;
	}
	if(oldFont)
		SelectObject(hdc, oldFont);
	//renderDevice.lpDDSBack->ReleaseDC(hdc);
}


void HoParty_KTJ::Init_questExplane(char *string, int sw)
{
	if(sw == -1)
	{
		wsprintf(q_explationTitle, string);
		return;
	}
	wsprintf(q_explation[sw], string);
}










char QuestReadBuf[64 * 50];

void HoParty_KTJ::ReadFileData_moveBuf(char *savebuf, int lineLen)
{
	int i, bufC = 0, cnt = 0;
	char c;
	for(i = 0; ; i++)
	{

		while(1)
		{
			c = QuestReadBuf[cnt++];

			if(c == 0) break;
			if(c == 13)
			{
				cnt++;
				break;
			}
			savebuf[i*lineLen + bufC] = c;
			bufC++;
		}


		bufC = 0;
		if(c == 0) break;
	}
}




int HoParty_KTJ::ReadFileData(char *fname)
{

	HANDLE hFile;
	DWORD dwAcess = 0;
	hFile = CreateFile(fname,
					   GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);


	ZeroMemory((void*)QuestReadBuf, sizeof(QuestReadBuf));

	if(hFile != INVALID_HANDLE_VALUE)
	{
		DWORD rbyte;
		int chk = ReadFile(hFile, (LPVOID)QuestReadBuf, sizeof(QuestReadBuf), &rbyte, NULL);


		CloseHandle(hFile);
		return 1;
	}

	return 0;
}











































HoEffectHitBoard EffectHitBoard;

HoEffectHitBoard::HoEffectHitBoard()
{
	MatHitBackBoard = -1;
	MatHitCount = -1;

	memset(BufferNum, 0, sizeof(BufferNum));
}

HoEffectHitBoard::~HoEffectHitBoard()
{

}

void HoEffectHitBoard::Load()
{
	MatHitBackBoard = CreateTextureMaterial("Effect\\Etc\\HitBackBoard.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatHitCount = CreateTextureMaterial("Effect\\Etc\\HitCount.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	ReadTextures();
}


POINT BackSize[4] = { {32, 32}, {32, 32}, {50, 50}, {80, 80} };
float BackSizeStepX = 0.f;
float BackSizeStepY = 0.f;
float BackAlphaStep = 0.f;
int   BackAlpha[4] = { 200, 200, 80, 0 };
int	  Delay[4] = { 5, 5, 5, 10 };
int	  BackFrameCount = 0;
int   BackTimeCount;

POINT TextSize[4] = { {10, 10}, {10, 10}, {20, 20}, {30, 30} };
float TextSizeStepX = 0.f;
float TextSizeStepY = 0.f;
float TextAlphaStep = 0.f;
int   TextAlpha[4] = { 255, 255, 100, 0 };
int	  TextDelay[4] = { 5, 5, 5, 10 };
int	  TextFrameCount = 0;
int   TextTimeCount;


POINT CriticalSize[4] = { {70, 20}, {70, 20}, {70 + 70, 20 + 20}, {70 + 70 * 2, 20 + 20 * 2} };
float CriticalSizeStepX = 0.f;
float CriticalSizeStepY = 0.f;
float CriticalAlphaStep = 0.f;
int   CriticalAlpha[4] = { 255, 255, 200, 0 };
int	  CriticalDelay[4] = { 30, 30, 8, 20 };
int	  CriticalFrameCount = 0;
int   CriticalTimeCount;

int HoEffectHitBoard::Main()
{
	if(StartFlag)
	{
		if(CriticalFlag)
		{
			CriticalPutSizeX += CriticalSizeStepX;
			CriticalPutSizeY += CriticalSizeStepY;
			CriticalPutAlpha += CriticalAlphaStep;
			CriticalTimeCount++;

			if(CriticalTimeCount > CriticalDelay[BackFrameCount])
			{
				if(CriticalFrameCount == 3)
					CriticalFlag = FALSE;

				if(CriticalFrameCount != 3)
				{
					CriticalSizeStepX = (float(CriticalSize[CriticalFrameCount + 1].x) - float(CriticalSize[CriticalFrameCount].x)) / (float)CriticalDelay[CriticalFrameCount];
					CriticalSizeStepY = (float(CriticalSize[CriticalFrameCount + 1].y) - float(CriticalSize[CriticalFrameCount].y)) / (float)CriticalDelay[CriticalFrameCount];
					CriticalAlphaStep = (float(CriticalAlpha[CriticalFrameCount + 1] - CriticalPutAlpha)) / (float)CriticalDelay[CriticalFrameCount];
					CriticalFrameCount++;
				}
				CriticalTimeCount = 0;
			}
		}
		else
		{
			BackPutSizeX += BackSizeStepX;
			BackPutSizeY += BackSizeStepY;
			BackPutAlpha += BackAlphaStep;
			BackTimeCount++;
			if(BackTimeCount >= Delay[BackFrameCount])
			{
				if(BackFrameCount != 3)
				{
					BackSizeStepX = (float(BackSize[BackFrameCount + 1].x) - float(BackSize[BackFrameCount].x)) / (float)Delay[BackFrameCount];
					BackSizeStepY = (float(BackSize[BackFrameCount + 1].y) - float(BackSize[BackFrameCount].y)) / (float)Delay[BackFrameCount];
					BackAlphaStep = (float(BackAlpha[BackFrameCount + 1] - (float)BackAlpha[BackFrameCount])) / (float)Delay[BackFrameCount];
					BackFrameCount++;
				}
				BackTimeCount = 0;
			}

			TextPutSizeX += TextSizeStepX;
			TextPutSizeY += TextSizeStepY;
			TextPutAlpha += TextAlphaStep;
			TextTimeCount++;
			if(TextTimeCount > TextDelay[TextFrameCount])
			{
				if(TextFrameCount == 3)
				{
					StartFlag = FALSE;
				}

				if(TextFrameCount != 3)
				{
					TextSizeStepX = (float(TextSize[TextFrameCount + 1].x) - float(TextSize[TextFrameCount].x)) / (float)TextDelay[TextFrameCount];
					TextSizeStepY = (float(TextSize[TextFrameCount + 1].y) - float(TextSize[TextFrameCount].y)) / (float)TextDelay[TextFrameCount];
					TextAlphaStep = (float(TextAlpha[TextFrameCount + 1] - (float)TextAlpha[TextFrameCount])) / (float)TextDelay[TextFrameCount];

					TextFrameCount++;
				}
				TextTimeCount = 0;
			}
		}
	}
	return TRUE;
}

int HoEffectHitBoard::Start(char *num, BOOL criticalFlag)
{
	BackFrameCount = 0;
	BackTimeCount = 0;

	CriticalFrameCount = 0;
	CriticalTimeCount = 0;

	TextFrameCount = 0;
	TextTimeCount = 0;
	StartFlag = TRUE;

	BackPutSizeX = 64;
	BackPutSizeY = 64;
	BackPutAlpha = 255;

	TextPutSizeX = 10;
	TextPutSizeY = 10;
	TextPutAlpha = 255;

	CriticalPutSizeX = 70;
	CriticalPutSizeY = 20;
	CriticalPutAlpha = 255;

	BackSizeStepX = float((BackSize[BackFrameCount + 1].x - BackSize[BackFrameCount].x) / Delay[BackFrameCount]);
	BackSizeStepY = float((BackSize[BackFrameCount + 1].y - BackSize[BackFrameCount].y) / Delay[BackFrameCount]);
	BackAlphaStep = float((BackAlpha[BackFrameCount + 1] - BackAlpha[BackFrameCount]) / Delay[BackFrameCount]);

	TextSizeStepX = float((TextSize[BackFrameCount + 1].x - TextSize[BackFrameCount].x) / TextDelay[TextFrameCount]);
	TextSizeStepY = float((TextSize[BackFrameCount + 1].y - TextSize[BackFrameCount].y) / TextDelay[TextFrameCount]);
	TextAlphaStep = float((TextAlpha[BackFrameCount + 1] - TextAlpha[BackFrameCount]) / TextDelay[TextFrameCount]);

	if(criticalFlag)
	{
		CriticalSizeStepX = float((CriticalSize[CriticalFrameCount + 1].x - CriticalSize[BackFrameCount].x) / CriticalDelay[CriticalFrameCount]);
		CriticalSizeStepY = float((CriticalSize[CriticalFrameCount + 1].y - CriticalSize[BackFrameCount].y) / CriticalDelay[CriticalFrameCount]);
		CriticalAlphaStep = float((CriticalAlpha[CriticalFrameCount + 1] - CriticalAlpha[BackFrameCount]) / CriticalDelay[CriticalFrameCount]);
	}
	memset(BufferNum, 0, sizeof(BufferNum));
	wsprintf(BufferNum, "%s", num);

	CriticalFlag = criticalFlag;
	return TRUE;
}

int HoEffectHitBoard::Draw()
{
	int x = 725;
	int y = 50;


	if(StartFlag)
	{
		renderDevice.BeginScene();

		if(CriticalFlag == FALSE)
		{
			hoDrawTexImageFloat(MatHitBackBoard, x - BackPutSizeX / 2 + 10, y - BackPutSizeY / 2, BackPutSizeX, BackPutSizeY, 0, 0, 32.f, 32.f, 32.f, 32.f, (int)BackPutAlpha);

			int count;
			for(int index = 0; index < (int)strlen(BufferNum); index++)
			{
				count = 0;
				if(BufferNum[index] == '0')
					count = 9;
				if(BufferNum[index] == '1')
					count = 0;
				if(BufferNum[index] == '2')
					count = 1;
				if(BufferNum[index] == '3')
					count = 2;
				if(BufferNum[index] == '4')
					count = 3;
				if(BufferNum[index] == '5')
					count = 4;
				if(BufferNum[index] == '6')
					count = 5;
				if(BufferNum[index] == '7')
					count = 6;
				if(BufferNum[index] == '8')
					count = 7;
				if(BufferNum[index] == '9')
					count = 8;

				int size = (int)strlen(BufferNum);

				hoDrawTexImageFloat(MatHitCount, float(float(x + index*TextPutSizeX) - ((float)size / 2.f)*TextPutSizeX + 10.f),
									-TextPutSizeY / 2 + y,
									TextPutSizeX, TextPutSizeY,
									float(count * 10), 0.f, 11.f, 14.f, 128.f, 64.f, (int)TextPutAlpha);
			}
		}
		else
		{

			hoDrawTexImageFloat(MatHitCount, x - CriticalPutSizeX / 2 + 20, float(y - 16), CriticalPutSizeX, CriticalPutSizeY, 0.f, 14.f, 128.f, 17.f, 128.f, 64.f, (int)CriticalPutAlpha);
		}

		renderDevice.EndScene();
	}
	return TRUE;
}


