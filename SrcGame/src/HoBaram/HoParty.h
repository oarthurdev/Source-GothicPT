#ifndef _HO_PARTY_H_
#define _HO_PARTY_H_

#define MAX_PARTY_MEMBER	6

struct hoPartyMember
{
	char	Name[256];
	DWORD	ChrCode;
	int		Life;
	int		Level;

	POINT3D CharacterPos;
	BOOL	JangFlag;

	char	ModelName1[64];
	char	ModelName2[64];
};

#define PARTY_NONE		500
#define PARTY_START		1000
#define PARTY_PROCESS	2000
#define PARTY_END		3000

class HoParty
{
public:
	HoParty();
	~HoParty();







	void quest_Progress_Clear();
	void quest_End_Clear();
	void quest_Progress_Set(char *q_name, char *f_name);
	void quest_End_Set(char *q_name, char *f_name);
	void qN_Pressf_CLEAR();
	void quest_Sel_Progress();


	void latest_Insert(char *namest);
	void friend_Insert(char *id);
	void chat_isLOG(char *id, int flag);
	int  chat_IDs(int dataN, int cnt, char *id);


	void Main_menuSet(int menuN);
	void chat_changeMENU(int sw);
	int chatbuild_INIfiles();

	void chat_WhisperPartyPlayer_close();


	void resize();






	void InitMenuSet(int menuN);


public:
	hoPartyMember	PartyMember[MAX_PARTY_MEMBER];
	int				PartyMemberCount;

	int									PartyPosState;
	int									MouseDownPartyMember;

private:


	int									MouseDownButton;



	int									MatPartyBackGround;
	LPDIRECT3DTEXTURE9				BmpMan[3];

	LPDIRECT3DTEXTURE9				BmpLifeBlue;
	LPDIRECT3DTEXTURE9				BmpLifeRed;

	LPDIRECT3DTEXTURE9				ToolTip[5];
	LPDIRECT3DTEXTURE9				Button[5];

	POINT								BackStartPos;
	POINT								TextStartPos;


	int									MatMessageBoxBackGround;
	POINT								MessageBoxStartPos;

	char								PartyMessageBoxChrName[128];
	DWORD								PartyMessageBoxChrCode;

	LPDIRECT3DTEXTURE9				BmpMessageOk[2];
	LPDIRECT3DTEXTURE9				BmpMessageCancel[2];

	int				MessageBoxDrawCount;
public:
	BOOL			MessageBoxOpenFlag;

	void Init();
	void Load();
	void Close();

	int	 Draw();
	int	 Main();

	int	AddMember(char *member, DWORD chrCode, int life, int level = 1);


	int	 AddMember(hoPartyMember *member, int cnt);
	void AddMember_memberSu(int memberSu);
	int  PARTY_PLAYUPDATE(hoPartyMember *member, int cnt);
	void PARTY_RELEASE();




	int SetParty(char *chrName, DWORD chrCode)
	{
		memset(PartyMessageBoxChrName, 0, sizeof(PartyMessageBoxChrName));
		wsprintf(PartyMessageBoxChrName, "%s", chrName);

		PartyMessageBoxChrCode = chrCode;
		MessageBoxOpenFlag = TRUE;

		return TRUE;
	}

	void DrawPartyMessage(int x, int y);
	void MainPartyMessage(int x, int y);
};


class HoEffectHitBoard
{
public:
	HoEffectHitBoard();
	~HoEffectHitBoard();

	float   BackPutSizeX;
	float   BackPutSizeY;
	float   BackPutAlpha;


	float  TextPutSizeX;
	float  TextPutSizeY;
	float  TextPutAlpha;

	float	CriticalPutSizeX;
	float	CriticalPutSizeY;
	float	CriticalPutAlpha;

	int MatHitBackBoard;
	int MatHitCount;

	BOOL CriticalFlag;
	char BufferNum[256];
	void Load();

	int Draw();
	int Main();

	int Start(char *num, BOOL criticalFlag = FALSE);

private:
	int StartFlag;
};


















#endif
