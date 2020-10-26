
#ifndef _SINHELPPET_HEADER_

#define _SINHELPPET_HEADER_

#include <string>
#include <map>
#include <vector>


typedef vector<string*> PetMessage;
typedef map< string, PetMessage> PetmsgMap;
typedef vector<int> MessageList;
typedef list<string> MessageKeep;
typedef list<int> MessageIndex;


class cHELPPET
{

public:
	PetmsgMap	PetMsg_Map;
	MessageList BattleM_List;
	MessageKeep Message_Keep;
	MessageIndex BattleMsg_Index;
	MessageIndex NormalMsg_Index;


	smPAT3D		*PatPetMesh_Bone;
	smPAT3D		*PatPetMesh;


	POINT3D		PetPosi;
	POINT3D		PetAngle;
	POINT3D     PetRendPoint;
	RECT		PetRendRect2D;

	POINT3D		CameraPetAngle;
	POINT3D     CameraPetPosi;


	int		AniCount;
	int		AniMaxCount;
	int     AniTime;


	sASSACOLOR Color;


	char szPetBuff[256];
	int MsgFlag;
	int MsgTime;
	int MessageIndex;
	char szTempId[32];

	int HelpMsgFlag;
	int HelpMsgTime;
	char HelpMsgId[32];


	int PetKind;
	int PetShow;


	int PetExp;
	int LevelFlag;


	int LoadingPet;

public:
	cHELPPET()
	{
	};
	~cHELPPET()
	{
	};

	void Init();
	void Load();
	void Release();
	void Draw();
	void Draw(POINT3D *pPosi, POINT3D *pAngle);
	void DrawText();
	void Close();
	void Main();
	void LButtonDown(int x, int y);
	void LButtonUp(int x, int y);
	void RButtonDown(int x, int y);
	void RButtonUp(int x, int y);
	void KeyDown();


	int GetFileData();


	int PetMessage(char *Id, int Index);


	int PetMessageHelp(char *Id);


	int GetPetMessagePosi();


	int DrawPetMessage();


	int CheckPetData();


	int PetRandomBattleMessage();
	int PetRandomNormalMessage();


	int ShowPet();
	int ClosePet();

	int PetOnOff(char *szBuff);

};

extern cHELPPET cHelpPet;
extern int PetMessageOkButtonFlag;







#endif
