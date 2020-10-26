

#include "sinLinkHeader.h"
#include "tjboy\\clanmenu\\tjclan.h"
#include "tjboy\\clanmenu\\clan_Enti.h"
#include "tjboy\\isaocheck\\auth.h"
#include "..\\FontImage.h"
#include "..\\bellatraFontEffect.h" 
#include "..\\field.h"
#include "Server\\onserver.h"
#include "Settings\UI.h"

extern BUFF_KILL BuffKill[32];

cSINSOD2 cSinSod2;
cSINSIEGE cSinSiege;
sinMESSAGEBOX_NEW sinMessageBox_New;

LPDIRECT3DTEXTURE9	lpbltr_clanN;
LPDIRECT3DTEXTURE9	lpbltr_clanB;
int Matbltr_Paper291;
int Matbltr_Paper291_Text;

LPDIRECT3DTEXTURE9	lpbltr_ButtonBox;
LPDIRECT3DTEXTURE9	lpbltr_Button_Clan;
LPDIRECT3DTEXTURE9	lpbltr_Button_Clan_G;
LPDIRECT3DTEXTURE9	lpbltr_Button_Prize;
LPDIRECT3DTEXTURE9	lpbltr_Button_Prize_G;
LPDIRECT3DTEXTURE9	lpbltr_Button_OK;
LPDIRECT3DTEXTURE9	lpbltr_Button_OK_G;

int Matbltr_Logo;
LPDIRECT3DTEXTURE9    lpbltr_ClanRank_Title;
int Matbltr_ClanRank_KindBar;
LPDIRECT3DTEXTURE9    Matbltr_ClanRank_ListLine;

BOOL MouseDownFlag = FALSE;

extern int			iSettingsBg;
extern int			iSettingsButton[2];
extern int			iSettingsRelog;
extern int			iSettingsSave;
extern int			iSettingsCheckBox[2];
extern void SaveConfig();
extern void Relog();
extern int iSave;
extern BOOL bIsWidescreen;
extern char ratio[4];
extern int Width, Height;



RECT SodButtonRect[3] = {
	{111,393,111 + 68,393 + 23},
	{189,393,189 + 68,393 + 23},
	{267,393,267 + 68,393 + 23},

};

int MatSod2Box[10];

extern void ReadTexSettings();
extern int GetClick(DWORD x, DWORD y, DWORD L, DWORD A);
extern BOOL bDone;


void cSINSOD2::Init()
{
	char szBuff[128];
	for(int i = 0; i < 9; i++)
	{
		wsprintf(szBuff, "Image\\SinImage\\Help\\box%d.tga", i + 1);
		MatSod2Box[i] = CreateTextureMaterial(szBuff, 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	}
	MatSod2Box[9] = CreateTextureMaterial("Image\\SinImage\\Help\\Box_Line.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Matbltr_Paper291 = CreateTextureMaterial("Image\\SinImage\\Help\\bltr_paper291_145.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Matbltr_Paper291_Text = CreateTextureMaterial("Image\\SinImage\\Help\\bltr_paper_txt.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Matbltr_Logo = CreateTextureMaterial("Image\\SinImage\\Help\\bltr.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Matbltr_ClanRank_KindBar = CreateTextureMaterial("Image\\SinImage\\Help\\bltr_list-title.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	ReadTexSettings();
	Load();
}

void cSINSOD2::Load()
{


	lpbltr_clanN = LoadDibSurfaceOffscreen("Image\\SinImage\\Help\\bltr_clanN.bmp");
	lpbltr_clanB = LoadDibSurfaceOffscreen("Image\\SinImage\\Help\\bltr_clanB.bmp");
	lpbltr_ButtonBox = LoadDibSurfaceOffscreen("Image\\SinImage\\Help\\bltr_box.bmp");
	lpbltr_Button_Clan = LoadDibSurfaceOffscreen("Image\\SinImage\\Help\\bltr_bt1.bmp");
	lpbltr_Button_Clan_G = LoadDibSurfaceOffscreen("Image\\SinImage\\Help\\bltr_bt1_.bmp");
	lpbltr_Button_Prize = LoadDibSurfaceOffscreen("Image\\SinImage\\Help\\bltr_bt2.bmp");
	lpbltr_Button_Prize_G = LoadDibSurfaceOffscreen("Image\\SinImage\\Help\\bltr_bt2_.bmp");
	lpbltr_Button_OK = LoadDibSurfaceOffscreen("Image\\SinImage\\Help\\bltr_bt3.bmp");
	lpbltr_Button_OK_G = LoadDibSurfaceOffscreen("Image\\SinImage\\Help\\bltr_bt3_.bmp");
	lpbltr_ClanRank_Title = LoadDibSurfaceOffscreen("Image\\SinImage\\Help\\bltr_list-title.bmp");
	Matbltr_ClanRank_ListLine = LoadDibSurfaceOffscreen("Image\\SinImage\\Help\\bltr_list-line.bmp");

}

void cSINSOD2::Release()
{

}

void cSINSOD2::Draw()
{


	int i = 0, j = 0, t = 0;


	if(sinMessageBox_New.Flag)
	{
		for(i = 0; i < 9; i++)
		{
			switch(i)
			{
			case 0:
				dsDrawTexImage(MatSod2Box[i], sinMessageBox_New.PosiX, sinMessageBox_New.PosiY
					, 64, 32, 255);
				break;
			case 1:
				dsDrawTexImage(MatSod2Box[i], sinMessageBox_New.PosiX + 64, sinMessageBox_New.PosiY
					, sinMessageBox_New.SizeW - (64 * 2), 32, 255);
				break;

			case 2:
				dsDrawTexImage(MatSod2Box[i], sinMessageBox_New.PosiX + sinMessageBox_New.SizeW - 64, sinMessageBox_New.PosiY
					, 64, 32, 255);
				break;
			case 3:
				dsDrawTexImage(MatSod2Box[i], sinMessageBox_New.PosiX, sinMessageBox_New.PosiY + 32
					, 64, sinMessageBox_New.SizeH - (64 + 32), 255);
				break;
			case 4:
				dsDrawTexImage(MatSod2Box[i], sinMessageBox_New.PosiX + 64 - 1, sinMessageBox_New.PosiY + 32
					, sinMessageBox_New.SizeW - (64 * 2) + 1, sinMessageBox_New.SizeH - (64 + 32), 255);
				break;
			case 5:
				dsDrawTexImage(MatSod2Box[i], sinMessageBox_New.PosiX + sinMessageBox_New.SizeW - 64, sinMessageBox_New.PosiY + 32
					, 64, sinMessageBox_New.SizeH - (64 + 32), 255);
				break;

			case 6:
				dsDrawTexImage(MatSod2Box[i], sinMessageBox_New.PosiX, sinMessageBox_New.PosiY + sinMessageBox_New.SizeH - 64
					, 64, 64, 255);
				break;
			case 7:
				for(t = 0; t < 6; t++)
				{
					dsDrawTexImage(MatSod2Box[i], sinMessageBox_New.PosiX + 64 + (t*(32)), sinMessageBox_New.PosiY + sinMessageBox_New.SizeH - 64
						, 32, 64, 255);



				}
				break;
			case 8:
				dsDrawTexImage(MatSod2Box[i], sinMessageBox_New.PosiX + sinMessageBox_New.SizeW - 64, sinMessageBox_New.PosiY + sinMessageBox_New.SizeH - 64
					, 64, 64, 255);
				break;

			}

		}

		dsDrawTexImage(MatSod2Box[9], sinMessageBox_New.PosiX + 7, sinMessageBox_New.PosiY + 50
			, sinMessageBox_New.SizeW - (7 * 2), 16, 255);

	}

	if(BoxIndex == 1)
	{


		dsDrawTexImage(Matbltr_Logo, 152, 97, 128, 64, 255);


		DrawSprite(97, 156, lpbltr_clanN, 0, 0, 116, 12);


		dsDrawTexImage(Matbltr_Paper291, 78, 241, 291, 145, 255);


		switch(UserType)
		{
		case 1:

			DrawSprite(97, 284, lpbltr_clanB, 0, 0, 49, 49);
			DrawSprite(105, 292, ClanMark_32, 0, 0, 32, 32);
			break;
		case 2:
			dsDrawTexImage(Matbltr_Paper291_Text, 95, 255, 256, 128, 255);

			break;
		case 3:
			dsDrawTexImage(Matbltr_Paper291_Text, 95, 255, 256, 128, 255);

			DrawSprite(189, 393, lpbltr_ButtonBox, 0, 0, 68, 23);

			DrawSprite(199, 399, lpbltr_Button_Prize_G, 0, 0, 47, 12);
			break;
		case 4:

			DrawSprite(97, 284, lpbltr_clanB, 0, 0, 49, 49);
			DrawSprite(105, 292, ClanMark_32, 0, 0, 32, 32);


			DrawSprite(189, 393, lpbltr_ButtonBox, 0, 0, 68, 23);

			DrawSprite(199, 399, lpbltr_Button_Prize_G, 0, 0, 47, 12);
			break;
		case 6:

			DrawSprite(189, 393, lpbltr_ButtonBox, 0, 0, 68, 23);

			DrawSprite(199, 399, lpbltr_Button_Prize_G, 0, 0, 47, 12);

			break;
		}


		DrawSprite(111, 393, lpbltr_ButtonBox, 0, 0, 68, 23);

		DrawSprite(267, 393, lpbltr_ButtonBox, 0, 0, 68, 23);

		DrawSprite(121, 399, lpbltr_Button_Clan_G, 0, 0, 47, 12);

		DrawSprite(277, 399, lpbltr_Button_OK_G, 0, 0, 47, 12);

	}
	vector<string>::size_type k = 0;
	if(BoxIndex == 2)
	{

		DrawSprite(152, 97, lpbltr_ClanRank_Title, 0, 0, 143, 19);


		dsDrawTexImage(Matbltr_ClanRank_KindBar, 78, 147, 512, 32, 255);


		for(j = 0; j < 10; j++)
		{
			DrawSprite(78, 173 + (j * 20), Matbltr_ClanRank_ListLine, 0, 0, 287, 20);

		}

		DrawSprite(189, 393, lpbltr_ButtonBox, 0, 0, 68, 23);

		DrawSprite(199, 399, lpbltr_Button_OK_G, 0, 0, 47, 12);

		for(int t = 0; t < 10; t++)
		{
			if(ClanMarkIndex[t] >= 0)
			{
				DrawSprite(103, 174 + (t * 20), ClanMark[t], 0, 0, 16, 16);
			}
		}
	}


	if(sinMessageBox_New.ButtonIndex)
	{
		if(BoxIndex == 1)
		{
			switch(sinMessageBox_New.ButtonIndex)
			{
			case 1:

				DrawSprite(121, 399, lpbltr_Button_Clan, 0, 0, 47, 12);
				break;
			case 2:

				DrawSprite(199, 399, lpbltr_Button_Prize, 0, 0, 47, 12);

				break;
			case 3:

				DrawSprite(277, 399, lpbltr_Button_OK, 0, 0, 47, 12);
				break;
			}
		}
		if(BoxIndex == 2)
		{
			if(sinMessageBox_New.ButtonIndex == 2)
			{

				DrawSprite(199, 399, lpbltr_Button_OK, 0, 0, 47, 12);
			}
		}
	}
}

void cSINSOD2::DrawText()
{
	int Posi[] = { 103,120,230,296 };
	int i = 0, k = 0;
	vector<string>::size_type j = 0;
	HDC	hdc = NULL;
	
	//SelectObject(hdc, sinFont);
	
	SetFontTextColor( RGB(255, 244, 201));

	char szTempBuff[128];


	if(BoxIndex == 1)
	{
		switch(UserType)
		{
		case 1:
			for(i = 0; i < 3; i++)
			{
				if(i == 2)
				{
					wsprintf(szTempBuff, SodMessage_Etc[i], Tax, "%");
					dsTextLineOut( 97, 182 + (14 * i), szTempBuff, lstrlen(szTempBuff));
				}
				else
				{
					dsTextLineOut( 97, 182 + (14 * i), SodMessage_Etc[i], lstrlen(SodMessage_Etc[i]));
				}
			}

			while(j != sinClanMessage.size())
			{
				dsTextLineOut( 154, 281 + (j * 20), sinClanMessage[j].c_str(), lstrlen(sinClanMessage[j].c_str()));
				j++;
			}


			wsprintf(szTempBuff, "%s : %s", sinClanMaster7, szClanMaster);
			dsTextLineOut( 230, 355, szTempBuff, lstrlen(szTempBuff));


			//SelectObject(hdc, sinBoldFont);
			SetFontTextColor( RGB(255, 244, 201));
			dsTextLineOut( 185, 255, szClanName, lstrlen(szClanName));


			break;
		case 2:
			for(i = 0; i < 2; i++)
			{
				dsTextLineOut( 97, 182 + (14 * i), SodMessage_Clan[i], lstrlen(SodMessage_Clan[i]));
			}

			memset(&szTempBuff, 0, sizeof(szTempBuff));
			NumLineComa(TotalEMoney, szTempBuff);
			dsTextLineOut( 170, 283, szTempBuff, lstrlen(szTempBuff));

			wsprintf(szTempBuff, "%d%s", Tax, "%");
			dsTextLineOut( 170, 301, szTempBuff, lstrlen(szTempBuff));

			memset(&szTempBuff, 0, sizeof(szTempBuff));
			NumLineComa(TotalMoney, szTempBuff);
			dsTextLineOut( 170, 320, szTempBuff, lstrlen(szTempBuff));

			break;
		case 3:
			for(i = 0; i < 3; i++)
			{
				dsTextLineOut( 97, 182 + (14 * i), SodMessage_Master[i], lstrlen(SodMessage_Master[i]));
			}
			memset(&szTempBuff, 0, sizeof(szTempBuff));
			NumLineComa(TotalEMoney, szTempBuff);
			dsTextLineOut( 170, 283, szTempBuff, lstrlen(szTempBuff));

			wsprintf(szTempBuff, "%d%s", Tax, "%");
			dsTextLineOut( 170, 301, szTempBuff, lstrlen(szTempBuff));

			memset(&szTempBuff, 0, sizeof(szTempBuff));
			NumLineComa(TotalMoney, szTempBuff);
			dsTextLineOut( 170, 320, szTempBuff, lstrlen(szTempBuff));

			break;
		case 4:
			for(i = 0; i < 3; i++)
			{
				if(i == 2)
				{
					wsprintf(szTempBuff, SodMessage_Etc[i], Tax, "%");
					dsTextLineOut( 97, 182 + (14 * i), szTempBuff, lstrlen(szTempBuff));
				}
				else
				{
					dsTextLineOut( 97, 182 + (14 * i), SodMessage_Etc[i], lstrlen(SodMessage_Etc[i]));
				}
			}

			while(j != sinClanMessage.size())
			{
				dsTextLineOut( 154, 281 + (j * 20), sinClanMessage[j].c_str(), lstrlen(sinClanMessage[j].c_str()));
				j++;
			}


			wsprintf(szTempBuff, "%s : %s", sinClanMaster7, szClanMaster);
			dsTextLineOut( 230, 355, szTempBuff, lstrlen(szTempBuff));


			//SelectObject(hdc, sinBoldFont);
			SetFontTextColor( RGB(255, 244, 201));
			dsTextLineOut( 185, 255, szClanName, lstrlen(szClanName));

			break;
		case 6:
			for(i = 0; i < 3; i++)
			{
				if(i == 2)
				{
					wsprintf(szTempBuff, SodMessage_Etc[i], Tax, "%");
					dsTextLineOut( 97, 182 + (14 * i), szTempBuff, lstrlen(szTempBuff));

				}
				else
				{
					dsTextLineOut( 97, 182 + (14 * i), SodMessage_Etc[i], lstrlen(SodMessage_Etc[i]));
				}
			}

			//SelectObject(hdc, sinBoldFont);
			SetFontTextColor( RGB(255, 244, 201));
			dsTextLineOut( 185, 255, cldata.name, lstrlen(cldata.name));

			//SelectObject(hdc, sinFont);
			wsprintf(szTempBuff, "%s : ", sinPrize7);
			dsTextLineOut( 110, 283, szTempBuff, lstrlen(szTempBuff));

			memset(&szTempBuff, 0, sizeof(szTempBuff));
			NumLineComa(ClanMoney, szTempBuff);
			dsTextLineOut( 152, 283, szTempBuff, lstrlen(szTempBuff));

			dsTextLineOut( 110, 301, OtherClanMaster[0], lstrlen(OtherClanMaster[0]));
			dsTextLineOut( 110, 320, OtherClanMaster[1], lstrlen(OtherClanMaster[1]));
			break;
		}

		//SelectObject(hdc, sinBoldFont);
		SetFontTextColor( RGB(255, 205, 4));
		dsTextLineOut( 223, 157, szClanName, lstrlen(szClanName));
	}
	char szTempNum[16];
	int  TempNum;
	char szTempBuff2[128];
	memset(&szTempBuff2, 0, sizeof(szTempBuff2));
	if(BoxIndex == 2)
	{
		while(j != sinClanRank.size())
		{
			if((j % 4) != 0)
			{
				//SelectObject(hdc, sinBoldFont);
				SetFontTextColor( RGB(255, 205, 4));
				wsprintf(szTempNum, "%d", k + 1);
				if(k + 1 == 10)
				{
					dsTextLineOut( 82, 177 + (k * 20), szTempNum, lstrlen(szTempNum));
				}
				else
				{
					dsTextLineOut( 86, 177 + (k * 20), szTempNum, lstrlen(szTempNum));
				}
				//SelectObject(hdc, sinFont);
				SetFontTextColor( RGB(255, 255, 255));
				if((j % 4) == 2)
				{
					memset(&szTempBuff2, 0, sizeof(szTempBuff2));
					TempNum = atoi(sinClanRank[j].c_str());
					NumLineComa(TempNum, szTempBuff2);
					dsTextLineOut( 5 + Posi[j % 4], 177 + (k * 20), szTempBuff2, lstrlen(szTempBuff2));

				}
				else
				{
					dsTextLineOut( 5 + Posi[j % 4], 177 + (k * 20), sinClanRank[j].c_str(), lstrlen(sinClanRank[j].c_str()));
				}
			}
			j++;
			if((j % 4) == 0)
			{
				k++;
			}

		}
	}
	
}

DWORD ClanRankFlagTime = 0;
void cSINSOD2::Main()
{

	if(sinMessageBox_New.Flag)
	{
		sinMessageBoxShowFlag = 1;
		sinMessageBox_New.ButtonIndex = 0;
		for(int i = 0; i < 3; i++)
		{
			if(sinMessageBox_New.ButtonRect[i].left< pCursorPos.x  && sinMessageBox_New.ButtonRect[i].right > pCursorPos.x  &&
				sinMessageBox_New.ButtonRect[i].top < pCursorPos.y  && sinMessageBox_New.ButtonRect[i].bottom > pCursorPos.y)
			{
				if(ClanMasterMessageBoxFlag)break;
				if(BoxIndex == 1)
				{
					if((UserType == 3 || UserType == 4 || UserType == 6))
					{
						sinMessageBox_New.ButtonIndex = i + 1;
					}
					else
					{
						if(i == 1)continue;
						sinMessageBox_New.ButtonIndex = i + 1;

					}
				}
				if(BoxIndex == 2)
				{
					if(i != 1)continue;
					sinMessageBox_New.ButtonIndex = i + 1;
				}
			}
		}
		if(BoxIndex == 1)
		{
			if(!ClanMark_32)
			{
				ClanMark_32Time++;
				if(ClanMark_32Time >= 70 * 3)
				{
					ClanMark_32Time = 0;
					ClanMark_32Index = ReadClanInfo_32X32(ClanImageNum);
					ClanMark_32 = ClanInfo[ClanMark_32Index].hClanMark32;
				}
			}
			if(ClanRankFlag)
			{
				ClanRankFlagTime++;
				if(ClanRankFlagTime >= 70 * 2)
				{
					ClanRankFlag = 0;
				}
			}
		}
		if(BoxIndex == 2)
		{
			for(int t = 0; t < 10; t++)
			{
				if(!ClanMark[t])
				{
					ClanMarkLoadTime[t]++;
					if(ClanMarkLoadTime[t] >= 70 * 3)
					{
						ClanMarkLoadTime[t] = 0;
						ClanMarkIndex[t] = ReadClanInfo(ClanMarkNum[t]);
						if(ClanInfo[ClanMarkIndex[t]].hClanMark)
						{
							ClanMark[t] = ClanInfo[ClanMarkIndex[t]].hClanMark;
						}
					}
				}
			}
		}
	}
}

void cSINSOD2::Close()
{

}

void cSINSOD2::LButtonDown(int x, int y)
{

	if(sinMessageBox_New.Flag)
	{
		if(sinMessageBox_New.ButtonIndex)
		{
			if(BoxIndex == 1)
			{
				switch(sinMessageBox_New.ButtonIndex)
				{
				case 1:

					if(!ClanRankFlag)
					{
						sod2INFOindex(UserAccount, sinChar->szName, szConnServerName, 3);
						ClanRankFlag = 1;

					}



					break;
				case 2:
					if(UserType != 6)
					{
						SendClanMoneyToServer(0, 0);
					}
					if(UserType == 6)
					{
						if(ClanMoney)
						{
							cMessageBox.ShowMessage2(MESSAGE_SOD2_GET_MONEY);
							ClanMasterMessageBoxFlag = 1;
						}
						else
						{
							cMessageBox.ShowMessage(MESSAGE_DONT_HAVE_CLANMONEY);
						}
					}
					break;
				case 3:

					CloseSod2MessageBox();
					break;

				}
			}
			if(BoxIndex == 2)
			{
				if(sinMessageBox_New.ButtonIndex == 2)
				{

					CloseSod2MessageBox();
				}
			}
		}
	}
}

void cSINSOD2::LButtonUp(int x, int y)
{


}

void cSINSOD2::RButtonDown(int x, int y)
{

}

void cSINSOD2::RButtonUp(int x, int y)
{

}

void cSINSOD2::KeyDown()
{

}

void cSINSOD2::CloseSod2MessageBox()
{
	memset(&sinMessageBox_New, 0, sizeof(sinMESSAGEBOX_NEW));
	BoxIndex = 0;
	UserType = 0;
	sinMessageBoxShowFlag = 0;
	ClanRankFlag = 0;
}

void cSINSOD2::ShowSod2MessageBox()
{


	sod2INFOindex(UserAccount, sinChar->szName, szConnServerName, 1);

}


int ShowSinMessageBox_New(int PosiX, int PosiY, int SizeW, int SizeH, RECT *rect, int ButtonNum)
{
	if(sinMessageBox_New.Flag)return FALSE;
	sinMessageBox_New.ButtonRect[0] = rect[0];
	sinMessageBox_New.ButtonRect[1] = rect[1];
	sinMessageBox_New.ButtonRect[2] = rect[2];
	sinMessageBox_New.PosiX = PosiX;
	sinMessageBox_New.PosiY = PosiY;
	sinMessageBox_New.SizeW = SizeW;
	sinMessageBox_New.SizeH = SizeH;
	sinMessageBox_New.ButtonNum = ButtonNum;
	sinMessageBox_New.Flag = 1;
	sinMessageBoxShowFlag = 1;
	return TRUE;
}


void cSINSOD2::RecvWebDaTa()
{


}
void cSINSOD2::RecvClanRank(char *szBuff)
{





}


vector<string> cSINSOD2::Split_ClanRankDaTa(const string& s)
{

	vector<string> ret;
	typedef string::size_type string_size;
	string_size i = 0;
	while(i != s.size())
	{
		while(i != s.size())
		{
			if(s[i] & 0x80)break;
			if(isspace(s[i]))
			{
				++i;
			}
			else break;
		}
		string_size j = i;
		while(j != s.size())
		{
			if((j - i) > 200)
			{
				i = s.size();
				j = i;
				break;
			}
			if(s[j] & 0x80)
			{
				j += 2;
				continue;
			}
			if(!isspace(s[j]))
			{
				++j;
			}
			else break;
		}
		if(i != j)
		{
			ret.push_back(s.substr(i, j - i));
			i = j;
		}
	}


	vector<string> ret2;
	string_size k = 0;
	string_size e = 0;
	string STempNum;
	string CodeTemp;
	int TempNumCnt = 0;


	for(int p = 0; p < 10; p++)
	{
		ClanMarkNum[p] = -1;
	}

	i = 0;
	while(i < ret.size())
	{
		while(k != ret[i].size())
		{
			if(ret[i][k] == '=')
			{
				CodeTemp.clear();
				CodeTemp = ret[i].substr(0, k);
				if(i == 0 && CodeTemp == "Code")
				{
					STempNum.clear();
					STempNum = ret[i].substr(k + 1, ret[i].size() - (k + 1));
					if(atoi(STempNum.c_str()) == 2)
					{
						ret2.clear();
						return ret2;
					}
					else break;
				}

				ret2.push_back(ret[i].substr(k + 1, ret[i].size() - (k + 1)));
				if(CodeTemp == "CIMG")
				{
					STempNum.clear();
					STempNum = ret[i].substr(k + 1, ret[i].size() - (k + 1));
					ClanMarkNum[TempNumCnt] = atoi(STempNum.c_str());
					ClanMarkIndex[TempNumCnt] = ReadClanInfo(ClanMarkNum[TempNumCnt]);
					TempNumCnt++;
				}
				k = 0;
				break;
			}
			k++;
		}
		i++;
	}


	for(int t = 0; t < TempNumCnt; t++)
	{
		if(ClanMarkIndex[t] >= 0)
		{
			if(ClanInfo[ClanMarkIndex[t]].hClanMark)
			{
				ClanMark[t] = ClanInfo[ClanMarkIndex[t]].hClanMark;
			}
		}
	}
	return ret2;
}

vector<string> cSINSOD2::Split_ClanMessage(const string& s, const int Len[])
{

	vector<string> ret;
	typedef string::size_type string_size;
	string_size i = 0;
	string_size j = 0;
	int LenCnt = 0;
	while(i < s.size())
	{
		if(s[i] & 0x80)i += 2;
		else i++;
		if((int)i - (int)j >= Len[LenCnt])
		{
			if(Len[LenCnt + 1] == 0)
			{
				ret.push_back(s.substr(j, i - j));
				break;
			}
			ret.push_back(s.substr(j, i - j));
			j = i;
			LenCnt++;
		}
		if(s[i] == '|')
		{
			ret.push_back(s.substr(j, i - j));
			break;
		}
	}


	return ret;
}


vector<string> cSINSOD2::Split_Sod2DaTa(const string& s)
{
	string Temp33;
	vector<string> ret;
	typedef string::size_type string_size;
	string_size i = 0;
	while(i < s.size())
	{
		while(i < s.size())
		{
			if(s[i] == '|')
			{
				++i;
			}
			else break;
		}
		string_size j = i;
		while(j < s.size())
		{
			if((j - i) > 200)
			{
				i = s.size();
				j = i;
				break;
			}
			if(s[j] != '|')
			{
				++j;
			}
			else break;
		}
		if(i != j)
		{
			Temp33 = s.substr(i, j - i);
			ret.push_back(s.substr(i, j - i));
			i = j;
		}
	}


	string Temp;
	string Temp2;
	string_size k = 0;
	string_size e = 0;
	int NumTemp = 0;
	int TempArray[] = { 28,22,26,0 };
	i = 0;
	while(i < ret.size())
	{
		while(k < ret[i].size())
		{
			if(ret[i][k] == '=')
			{
				Temp.clear();
				Temp = ret[i].substr(0, k);

				Temp2.clear();
				Temp2 = ret[i].substr(k + 1, ret[i].size() - (k + 1));



				if(Temp == "Code")
				{
					NumTemp = atoi(Temp2.c_str());
					switch(NumTemp)
					{
					case 0:
					case 5:
					case 6:
						UserType = 1;
						break;
					case 1:
						UserType = 3;
						break;
					case 2:
					case 3:
						UserType = 2;
						break;
					case 4:
						UserType = 4;
						break;
					}

				}
				if(Temp == "CName")
				{
					strcpy_s(szClanName, Temp2.c_str());
				}
				if(Temp == "CNote")
				{

					Temp2.push_back('|');
					sinClanMessage = Split_ClanMessage(Temp2, TempArray);
				}
				if(Temp == "CZang")
				{
					strcpy_s(szClanMaster, Temp2.c_str());

				}
				if(Temp == "CIMG")
				{
					ClanImageNum = atoi(Temp2.c_str());
					ClanMark_32Index = ReadClanInfo_32X32(ClanImageNum);
					ClanMark_32 = ClanInfo[ClanMark_32Index].hClanMark32;

				}
				if(Temp == "TotalEMoney")
				{
					TotalEMoney = atoi(Temp2.c_str());

				}
				if(Temp == "CTax")
				{
					Tax = atoi(Temp2.c_str());

				}
				if(Temp == "TotalMoney")
				{
					TotalMoney = atoi(Temp2.c_str());

				}
				if(Temp == "CClanMoney")
				{
					ClanMoney = atoi(Temp2.c_str());
				}
				k = 0;
				break;
			}
			k++;
		}
		i++;
	}

	return ret;
}



int cSINSOD2::RecvWebData(int Index, const string& s)
{
	vector<string> Temp_V;
	if(bip_port_error)return FALSE;
	if(Index)
	{

		if(Index == 1)
		{
			Temp_V = Split_Sod2DaTa(s);
			if(Temp_V.size() <= 0)return FALSE;
			BoxIndex = 1;
			ShowSinMessageBox_New(62, 78, 381 - 62, 426 - 78, SodButtonRect);




		}
		else if(Index == 3)
		{

			sinClanRank = Split_ClanRankDaTa(s);
			if(sinClanRank.size() <= 0)return FALSE;
			BoxIndex = 2;

		}

	}
	return TRUE;
}


int sinRecvClanMoney(int RemainMoney, int GetMoney)
{

	if(haSiegeMenuFlag)
	{
		if(RemainMoney)
		{
			cSinSiege.TotalTax = RemainMoney;
			cSinSiege.ExpectedTotalTax = RemainMoney;
		}
		if(GetMoney)
		{
			CheckCharForm();
			sinPlusMoney2(GetMoney);
			sinPlaySound(SIN_SOUND_COIN);
			ReformCharForm();
			SendSaveMoney();
			cSinSiege.TotalTax = RemainMoney;
			cSinSiege.ExpectedTotalTax = RemainMoney;

		}
		return TRUE;
	}

	if(cSinSod2.UserType == 4 || cSinSod2.UserType == 3)
	{
		cSinSod2.ClanMoney = RemainMoney;
		if(RemainMoney)
		{
			cMessageBox.ShowMessage2(MESSAGE_SOD2_GET_MONEY);
			cSinSod2.ClanMasterMessageBoxFlag = 1;
			cSinSod2.UserType = 6;
		}
		else
		{
			if(cSinSod2.UserType == 4)
			{
				cSinSod2.UserType = 1;
			}
			else
				cMessageBox.ShowMessage(MESSAGE_DONT_HAVE_CLANMONEY);

		}
	}
	if(GetMoney)
	{
		CheckCharForm();
		sinPlusMoney2(GetMoney);
		sinPlaySound(SIN_SOUND_COIN);
		ReformCharForm();
		SendSaveMoney();
		cSinSod2.ClanMoney = RemainMoney;
	}

	return TRUE;
}


int sinShowSeigeMessageBox()
{

	return TRUE;
}

int RecvSeigeWebData(int Index, char *string)
{



	return TRUE;
}


cHASIEGE chaSiege;


int haSiegeMenuFlag = 0;
int haSiegeMenuKind = 0;
int ScrollButtonFlag = 0;
int GraphLineFlag = 0;
int haSiegeBoardFlag = 0;
int haSiegeMerFlag = 0;



POINT ClanSkillBoxSize = { 0,0 };
POINT ClanSkillBoxPosi = { 0,0 };


int CastleKindIndex = 0;
int TowerIconIndex = 0;
int haSendTowerIndex = 0;
int MenuButtonIndex = 0;


int HaTestMoney = 0;
int HaTaxRate = 0;


sHACLANDATA sHaClanData[HACLAN_MAX];

int  haAlpha = 0;
int  BoardTime = 0;
int  haClanSkillTime = 0;

int  haTotalDamage = 0;
int  haPlayTime[3] = { 0 };



int haMercenrayMoney[3] = { 50000,100000,300000 };
int	haMercenrayIndex = 0;
int haTowerMoney = 500000;


short haCrystalTowerCount[4];

char *haC_CastleWinFilePath = "image\\Sinimage\\help\\CastleWin.sin";
char *haC_CastleLoseFilePath = "image\\Sinimage\\help\\CastleLose.sin";

char *haC_CastleWin_FilePath = "image\\Sinimage\\help\\CastleWining.sin";
char *haC_CastleLose_FilePath = "image\\Sinimage\\help\\CastleLoseing.sin";



char *ScoreBoardName[] = {
	"Battle Point",
	"Con Rate",
	"B.P",
	"PlayTime",
	"Hit  Rate",
	"BLESS CASTLE",
};


int SiegeButtonPosi[][4] = {
	{70    ,70     ,268,302},
	{29 + 70 ,269 + 70 ,68 ,23},
	{144 + 70,269 + 70 ,48 ,23},
	{197 + 70,269 + 70 ,48 ,23},
	{270   ,236 + 70 ,48 ,23},
	{77 + 70 ,21 + 70  ,49 ,11},
	{179 + 70 - 3,21 + 70,49 ,11},
};


int SiegeIconPosi[][4] = {
	{26 + 70,83 + 70 ,16,16},
	{36 + 70,94 + 70 ,30,30},
	{36 + 70,216 + 70,30,30},
	{8 + 70 ,45 + 70 ,51,22},
	{10 + 70 ,63 + 70 ,12,13},
	{26 + 70,59 + 70,16,16},
};

int  haMatPlayMenu[8] = { 0 };
int  haMovieFlag = 0;
int  haMovieKind = 0;
char haMovieName[64];

int haPlayerPosi[4][4] = {
	{64 + 68 + 8,359,32,32},
	{270    ,363,48,23},
};

cHASIEGE::cHASIEGE()
{
	int i;
	for(i = 0; i < 6; i++)
	{
		cSinSiege.TowerTypeDraw[i][1] = 0;
	}
	for(i = 0; i < 4; i++)
	{
		cSinSiege.MercenaryNum[i] = 0;
	}

	bCaptureScreen = FALSE;
	dwTickScreen = 0;

}
cHASIEGE::~cHASIEGE()
{

}

void cHASIEGE::init()
{



}

void cHASIEGE::ImageLoad()
{

	lpSiegeTax = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_tax.bmp");
	lpSiegeDefense = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_menu.bmp");
	lpCastleButton = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_button.bmp");
	lpMercenary = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_box.bmp");

	lpDefenseButton[0] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_soldier_text.bmp");
	lpDefenseButton[1] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_tower_text.bmp");

	lpTax_Ok[0] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_button_ok01_.bmp");


	lpSiegeMercenaryIcon[0] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_soldier_ricaM.bmp");
	lpSiegeMercenaryIcon[1] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_soldier_ricaY.bmp");
	lpSiegeMercenaryIcon[2] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_soldier_bress.bmp");

	lpSiegeMercenaryIcon_[0] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_soldier_ricaM_01.bmp");
	lpSiegeMercenaryIcon_[1] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_soldier_ricaY_01.bmp");
	lpSiegeMercenaryIcon_[2] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_soldier_bress_01.bmp");

	lpSiegeDefeseIcon[0] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_ice.bmp");
	lpSiegeDefeseIcon[1] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_ele.bmp");
	lpSiegeDefeseIcon[2] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_fire.bmp");

	lpSiegeDefeseIcon_[0] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_ice01.bmp");
	lpSiegeDefeseIcon_[1] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_ele01.bmp");
	lpSiegeDefeseIcon_[2] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_fire01.bmp");

	lpSiegeClanskillIcon[0] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_hp.bmp");
	lpSiegeClanskillIcon[1] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_attack.bmp");
	lpSiegeClanskillIcon[2] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_eva.bmp");


	lpSiegeTaxButton = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_button_creat.bmp");
	lpSiegeDefenseButton = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_tax_button_defense.bmp");
	lpSiegeOkButton = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_button_ok.bmp");
	lpSiegeCancelButton = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_button_cancel.bmp");

	lpCastleIcon[0] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_castle_outa.bmp");
	lpCastleIcon[1] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_castle_outb.bmp");
	lpCastleIcon[2] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_castle_ina.bmp");
	lpCastleIcon[3] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_castle_inb.bmp");
	lpCastleIcon[4] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_castle_inc.bmp");
	lpCastleIcon[5] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_castle_ind.bmp");


	lpTaxScroll[0] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_arrow01.bmp");
	lpTaxScroll[1] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_arrow02.bmp");

	lpTaxGraph = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_tax_graph.bmp");
}


void cHASIEGE::Release()
{
	halpRelease(lpSiegeTaxButton);
	halpRelease(lpSiegeDefenseButton);
	halpRelease(lpSiegeOkButton);
	halpRelease(lpSiegeCancelButton);
	halpRelease(lpTaxScroll[0]);
	halpRelease(lpTaxScroll[1]);
	halpRelease(lpTaxGraph);

	for(int i = 0; i < 6; i++)
	{
		halpRelease(lpCastleIcon[i]);
	}
	for(int i = 0; i < 3; i++)
	{
		halpRelease(lpSiegeDefeseIcon[i]);
		halpRelease(lpSiegeClanskillIcon[i]);
		halpRelease(haPlayerButton_G[i]);
		halpRelease(haPlayerButton[i]);
		halpRelease(haPlayerButtonBox[i]);
		halpRelease(haPlayerButtonDown[i]);
	}
	halpRelease(lpTwoerImage);

}




void cHASIEGE::Main()
{
	int i;




	if(haClanSkillTime < 70 * 60 * 10)
	{
		if(haClanSkillTime > 70 * 60 * 7)
		{
			cSkill.CancelContinueSkill(CLANSKILL_ATTACK);
			cSkill.CancelContinueSkill(CLANSKILL_EVASION);
			cSkill.CancelContinueSkill(CLANSKILL_ABSORB);
			haClanSkillTime = 70 * 60 * 10;
		}
		else
		{
			haClanSkillTime++;
		}
	}



	if(haSiegeMenuFlag)
	{
		switch(haSiegeMenuKind)
		{
		case HASIEGE_TAXRATES:
			if(96 < pCursorPos.x && 96 + 218 > pCursorPos.x && SiegeIconPosi[0][1] < pCursorPos.y && SiegeIconPosi[0][1] + 16 > pCursorPos.y)
			{
				GraphLineFlag = 1;
			}
			else
			{
				GraphLineFlag = 0;
			}

			for(i = 1; i < 4; i++)
			{
				if(SiegeButtonPosi[i + 1][0] < pCursorPos.x && SiegeButtonPosi[i + 1][0] + SiegeButtonPosi[i + 1][2]> pCursorPos.x
					&& SiegeButtonPosi[i + 1][1]< pCursorPos.y && SiegeButtonPosi[i + 1][1] + SiegeButtonPosi[i + 1][3] > pCursorPos.y)
				{
					MenuButtonIndex = i + 1;
					break;
				}

				else if(SiegeButtonPosi[1][0]  < pCursorPos.x && SiegeButtonPosi[1][0] + SiegeButtonPosi[1][2]> pCursorPos.x
					&& SiegeButtonPosi[1][1]< pCursorPos.y && SiegeButtonPosi[1][1] + SiegeButtonPosi[1][3] > pCursorPos.y)
				{
					MenuButtonIndex = 7;
					break;
				}
				else
				{
					MenuButtonIndex = 0;
				}
			}
			break;
		case HASIEGE_DEFENSE:


			for(i = 1; i < 6; i++)
			{
				if(SiegeButtonPosi[i + 1][0]  < pCursorPos.x  && SiegeButtonPosi[i + 1][0] + SiegeButtonPosi[i + 1][2]> pCursorPos.x
					&& SiegeButtonPosi[i + 1][1]< pCursorPos.y && SiegeButtonPosi[i + 1][1] + SiegeButtonPosi[i + 1][3] > pCursorPos.y)
				{
					MenuButtonIndex = i + 1;
					break;
				}

				else if(SiegeButtonPosi[1][0]  < pCursorPos.x && SiegeButtonPosi[1][0] + SiegeButtonPosi[1][2]> pCursorPos.x
					&& SiegeButtonPosi[1][1]< pCursorPos.y && SiegeButtonPosi[1][1] + SiegeButtonPosi[1][3]> pCursorPos.y)
				{
					MenuButtonIndex = 8;
					break;
				}
				else
				{
					MenuButtonIndex = 0;
				}
			}

			for(i = 0; i < 3; i++)
			{
				if(SiegeIconPosi[1][0] + i * 84 < pCursorPos.x && SiegeIconPosi[1][0] + SiegeIconPosi[1][2] + i * 84 > pCursorPos.x &&
					SiegeIconPosi[1][1] < pCursorPos.y     && SiegeIconPosi[1][1] + SiegeIconPosi[1][3] > pCursorPos.y)
				{
					TowerIconIndex = i + 1;
					break;

				}
				else if(SiegeIconPosi[2][0] + i * 84 < pCursorPos.x && SiegeIconPosi[2][0] + SiegeIconPosi[2][2] + i * 84 > pCursorPos.x &&
					SiegeIconPosi[2][1] < pCursorPos.y     && SiegeIconPosi[2][1] + SiegeIconPosi[2][3] > pCursorPos.y)
				{
					TowerIconIndex = i + 4;
					break;
				}
				else
				{
					TowerIconIndex = 0;
				}
			}


			for(i = 0; i < 6; i++)
			{
				if(SiegeIconPosi[3][0] + i * 40 < pCursorPos.x && SiegeIconPosi[3][0] + SiegeIconPosi[3][2] + i * 40 > pCursorPos.x &&
					SiegeIconPosi[3][1] < pCursorPos.y     && SiegeIconPosi[3][1] + SiegeIconPosi[3][3]> pCursorPos.y)
				{
					CastleKindIndex = i + 1;
					break;
				}
				else
				{
					CastleKindIndex = 0;
				}
			}
			break;
		}

		if(ScrollButtonFlag == 1)
		{
			if(SiegeIconPosi[0][0] < 96)
			{
				SiegeIconPosi[0][0] = 96;
				ScrollButtonFlag = 0;
			}
			else if(SiegeIconPosi[0][0] > 315)
			{
				SiegeIconPosi[0][0] = 314;
				ScrollButtonFlag = 0;
			}
			else
			{
				if(95 < SiegeIconPosi[0][0] && SiegeIconPosi[0][0] < 316)
					SiegeIconPosi[0][0] = pCursorPos.x;
			}
		}
	}




	if(haSiegeBoardFlag)
	{
		BoardTime++;
		if(BoardTime > 60 * 30)
		{
			haSiegeBoardFlag = 0;
			SetCastleInit();
		}
	}



	if(haMovieFlag)
	{
		for(i = 0; i < 3; i++)
		{
			if(haPlayerPosi[0][0] + i * 34 < pCursorPos.x && haPlayerPosi[0][0] + haPlayerPosi[0][2] + i * 34 > pCursorPos.x &&
				haPlayerPosi[0][1] < pCursorPos.y     && haPlayerPosi[0][1] + haPlayerPosi[0][3] > pCursorPos.y)
			{
				haMovieKind = i + 1;
				break;
			}
			else if(haPlayerPosi[1][0] < pCursorPos.x && haPlayerPosi[1][0] + haPlayerPosi[1][2] > pCursorPos.x &&
				haPlayerPosi[1][1] < pCursorPos.y&& haPlayerPosi[1][1] + haPlayerPosi[1][3] > pCursorPos.y)
			{
				haMovieKind = 4;
				break;
			}
			else
			{
				haMovieKind = 0;
			}
		}

	}

}

int   haStartTga = 0;
int   haTempScore[2] = { 0 };
int	  haStartPosiX = 0, haStartPosiY = 100;
void cHASIEGE::Draw()
{

	int i, j;



	if(haSiegeMenuFlag)
	{
		switch(haSiegeMenuKind)
		{
		case HASIEGE_TAXRATES:
			DrawSprite(SiegeButtonPosi[0][0], SiegeButtonPosi[0][1], lpSiegeTax, 0, 0, SiegeButtonPosi[0][2], SiegeButtonPosi[0][3], 1);
			DrawSprite(SiegeButtonPosi[4][0], SiegeButtonPosi[4][1], lpTax_Ok[0], 0, 0, SiegeButtonPosi[4][2], SiegeButtonPosi[4][3], 1);
			DrawSprite(SiegeIconPosi[5][0], SiegeIconPosi[5][1], lpTaxScroll[1], 0, 0, SiegeIconPosi[5][2], SiegeIconPosi[5][3], 1);
			DrawSprite(SiegeIconPosi[0][0] - 8, SiegeIconPosi[0][1], lpTaxScroll[0], 0, 0, SiegeIconPosi[0][2], SiegeIconPosi[0][3], 1);
			DrawSprite(70 + 26, SiegeIconPosi[0][1] - 10, lpTaxGraph, 0, 0, SiegeIconPosi[0][0] - (70 + 26), 10, 1);

			break;
		case HASIEGE_DEFENSE:
			DrawSprite(SiegeButtonPosi[0][0], SiegeButtonPosi[0][1], lpSiegeDefense, 0, 0, SiegeButtonPosi[0][2], SiegeButtonPosi[0][3], 1);
			DrawSprite(SiegeButtonPosi[0][0] + 10, SiegeButtonPosi[0][1] + 63, lpMercenary, 0, 0, 248, 88, 1);


			if(cSinSiege.ClanSkill)
			{
				DrawSprite(SiegeIconPosi[2][0] + (cSinSiege.ClanSkill - 1) * 84, SiegeIconPosi[2][1], lpSiegeClanskillIcon[cSinSiege.ClanSkill - 1], 0, 0, SiegeIconPosi[2][2], SiegeIconPosi[2][3], 1);
			}


			if(!haSiegeMerFlag)
			{
				DrawSprite(SiegeButtonPosi[0][0] + 10, SiegeButtonPosi[0][1] + 43, lpCastleButton, 0, 0, 249, 22, 1);
				for(i = 0; i < 3; i++)
				{
					DrawSprite(SiegeIconPosi[1][0] + (i * 82), SiegeIconPosi[1][1], lpSiegeDefeseIcon_[i], 0, 0, SiegeIconPosi[1][2], SiegeIconPosi[1][3], 1);
				}


				for(i = 0; i < 6; i++)
				{
					for(j = 0; j < 2; j++)
					{
						if(cSinSiege.TowerTypeDraw[i][0])
						{

							if(cSinSiege.TowerTypeDraw[i][0] == 1)
								DrawSprite(SiegeIconPosi[3][0] + 2, SiegeIconPosi[3][1] - 2, lpCastleIcon[i], 0, 0, SiegeIconPosi[3][2], SiegeIconPosi[3][3], 1);
							else if(cSinSiege.TowerTypeDraw[i][0] == 3)
								DrawSprite(SiegeIconPosi[3][0] + 80 - 1, SiegeIconPosi[3][1] - 2, lpCastleIcon[i], 0, 0, SiegeIconPosi[3][2], SiegeIconPosi[3][3], 1);
							else
								DrawSprite(SiegeIconPosi[3][0] + (cSinSiege.TowerTypeDraw[i][0] - 1) * 40, SiegeIconPosi[3][1] - 2, lpCastleIcon[i], 0, 0, SiegeIconPosi[3][2], SiegeIconPosi[3][3], 1);


							if(cSinSiege.TowerTypeDraw[i][1])
							{
								DrawSprite(SiegeIconPosi[1][0] + (cSinSiege.TowerTypeDraw[i][1] - 1) * 82, SiegeIconPosi[1][1], lpSiegeDefeseIcon[cSinSiege.TowerTypeDraw[i][1] - 1], 0, 0, SiegeIconPosi[1][2], SiegeIconPosi[1][3], 1);
							}
						}
					}
				}
			}

			if(haSiegeMerFlag)
			{
				for(i = 0; i < 3; i++)
				{
					DrawSprite(SiegeIconPosi[1][0] + (i * 82), SiegeIconPosi[1][1], lpSiegeMercenaryIcon_[i], 0, 0, 30, 30, 1);
					if(cSinSiege.MercenaryNum[i])
					{
						DrawSprite(SiegeIconPosi[1][0] + i * 82, SiegeIconPosi[1][1], lpSiegeMercenaryIcon[i], 0, 0, SiegeIconPosi[1][2], SiegeIconPosi[1][3], 1);
					}
				}
				if(TowerIconIndex > 0)
				{
					DrawSprite(SiegeIconPosi[1][0] + (TowerIconIndex - 1) * 82, SiegeIconPosi[1][1], lpSiegeMercenaryIcon[TowerIconIndex - 1], 0, 0, SiegeIconPosi[1][2], SiegeIconPosi[1][3], 1);
				}
			}
			if(!haSiegeMerFlag)
				DrawSprite(SiegeButtonPosi[5][0], SiegeButtonPosi[5][1], lpDefenseButton[1], 0, 0, SiegeButtonPosi[5][2], SiegeButtonPosi[5][3], 1);
			else
				DrawSprite(SiegeButtonPosi[6][0], SiegeButtonPosi[6][1], lpDefenseButton[0], 0, 0, SiegeButtonPosi[6][2], SiegeButtonPosi[6][3], 1);


			if(TowerIconIndex > 0)
			{
				if(TowerIconIndex > 3)
				{
					ClanSkillBoxPosi.x = SiegeIconPosi[2][0] + (TowerIconIndex - 4) * 84;
					ClanSkillBoxPosi.y = SiegeIconPosi[2][1] - 96;
					ClanSkillBoxSize.x = 11;
					ClanSkillBoxSize.y = 6;
				}
				else if(TowerIconIndex < 4 && haSiegeMerFlag)
				{
					ClanSkillBoxPosi.x = SiegeIconPosi[2][0] + (TowerIconIndex - 1) * 84;;
					ClanSkillBoxPosi.y = SiegeIconPosi[2][1] - 216 - 20;
					ClanSkillBoxSize.x = 15;
					ClanSkillBoxSize.y = 7;

				}
				else
				{
					ClanSkillBoxPosi.x = SiegeIconPosi[2][0] + (TowerIconIndex - 1) * 84;;
					ClanSkillBoxPosi.y = SiegeIconPosi[2][1] - 216;
					ClanSkillBoxSize.x = 15;
					ClanSkillBoxSize.y = 6;

				}
				for(i = 0; i < ClanSkillBoxSize.x; i++)
				{
					for(int j = 0; j < ClanSkillBoxSize.y; j++)
					{
						if(i == 0 && j == 0)
							dsDrawTexImage(cItem.MatItemInfoBox_TopLeft, ClanSkillBoxPosi.x + (i * 16), ClanSkillBoxPosi.y + (j * 16), 16, 16, 255);
						if(j == 0 && i != 0 && i + 1 < ClanSkillBoxSize.x)
							dsDrawTexImage(cItem.MatItemInfoBox_TopCenter, ClanSkillBoxPosi.x + (i * 16), ClanSkillBoxPosi.y + (j * 16), 16, 16, 255);
						if(j == 0 && i + 1 == ClanSkillBoxSize.x)
							dsDrawTexImage(cItem.MatItemInfoBox_TopRight, ClanSkillBoxPosi.x + (i * 16), ClanSkillBoxPosi.y + (j * 16), 16, 16, 255);
						if(i == 0 && j != 0 && j + 1 != ClanSkillBoxSize.y)
							dsDrawTexImage(cItem.MatItemInfoBox_Left, ClanSkillBoxPosi.x + (i * 16), ClanSkillBoxPosi.y + (j * 16), 16, 16, 255);
						if(i != 0 && j != 0 && i + 1 != ClanSkillBoxSize.x && j + 1 != ClanSkillBoxSize.y)
							dsDrawTexImage(cItem.MatItemInfoBox_Center, ClanSkillBoxPosi.x + (i * 16), ClanSkillBoxPosi.y + (j * 16), 16, 16, 255);
						if(i + 1 == ClanSkillBoxSize.x && j != 0 && j + 1 != ClanSkillBoxSize.y)
							dsDrawTexImage(cItem.MatItemInfoBox_Right, ClanSkillBoxPosi.x + (i * 16), ClanSkillBoxPosi.y + (j * 16), 16, 16, 255);
						if(i == 0 && j + 1 == ClanSkillBoxSize.y)
							dsDrawTexImage(cItem.MatItemInfoBox_BottomLeft, ClanSkillBoxPosi.x + (i * 16), ClanSkillBoxPosi.y + (j * 16), 16, 16, 255);
						if(i != 0 && j + 1 == ClanSkillBoxSize.y && i + 1 != ClanSkillBoxSize.x)
							dsDrawTexImage(cItem.MatItemInfoBox_BottomCenter, ClanSkillBoxPosi.x + (i * 16), ClanSkillBoxPosi.y + (j * 16), 16, 16, 255);
						if(j + 1 == ClanSkillBoxSize.y && i + 1 == ClanSkillBoxSize.x)
							dsDrawTexImage(cItem.MatItemInfoBox_BottomRight, ClanSkillBoxPosi.x + (i * 16), ClanSkillBoxPosi.y + (j * 16), 16, 16, 255);
					}
				}
			}

			break;
		}
		switch(MenuButtonIndex)
		{
		case 2:
			DrawSprite(SiegeButtonPosi[2][0], SiegeButtonPosi[2][1], lpSiegeOkButton, 0, 0, SiegeButtonPosi[2][2], SiegeButtonPosi[2][3], 1);
			break;
		case 3:
			DrawSprite(SiegeButtonPosi[3][0], SiegeButtonPosi[3][1], lpSiegeCancelButton, 0, 0, SiegeButtonPosi[3][2], SiegeButtonPosi[3][3], 1);
			break;
		case 4:
			if(haSiegeMenuKind == HASIEGE_TAXRATES)
				DrawSprite(SiegeButtonPosi[4][0], SiegeButtonPosi[4][1], lpSiegeOkButton, 0, 0, SiegeButtonPosi[4][2], SiegeButtonPosi[4][3], 1);
			break;
		case 5:
			DrawSprite(SiegeButtonPosi[5][0], SiegeButtonPosi[5][1], lpDefenseButton[1], 0, 0, SiegeButtonPosi[5][2], SiegeButtonPosi[5][3], 1);
			break;
		case 6:
			DrawSprite(SiegeButtonPosi[6][0], SiegeButtonPosi[6][1], lpDefenseButton[0], 0, 0, SiegeButtonPosi[6][2], SiegeButtonPosi[6][3], 1);
			break;
		case 7:
			DrawSprite(SiegeButtonPosi[1][0], SiegeButtonPosi[1][1], lpSiegeDefenseButton, 0, 0, SiegeButtonPosi[1][2], SiegeButtonPosi[1][3], 1);
			break;
		case 8:
			DrawSprite(SiegeButtonPosi[1][0], SiegeButtonPosi[1][1], lpSiegeTaxButton, 0, 0, SiegeButtonPosi[1][2], SiegeButtonPosi[1][3], 1);
			break;

		}

	}


	for (int i = 0; i < 32; i++)
	{
		if (BuffKill[i].flag)
		{
			if (BuffKill[i].x < WinSizeX / 2 + 256 / 2)
			{
				BuffKill[i].x += 8 + BuffKill[i].x / 2;
				if (BuffKill[i].alpha < 255)
					BuffKill[i].alpha += 20;
				else
					BuffKill[i].alpha = 255;
			}
			else
			{
				BuffKill[i].x = WinSizeX / 2 + 256 / 2;
				if (BuffKill[i].alpha > 0)
					BuffKill[i].alpha -= 1;
				else
				{
					BuffKill[i].alpha = 0;
					BuffKill[i].flag = 0;
				}
			}
			dsDrawTexImage(BuffKill[i].image, BuffKill[i].x - 256, BuffKill[i].y, 256, 64, BuffKill[i].alpha);
			break;
		}
	}

	if (EventBattleArena == 2 && StageField[lpCurPlayer->OnStageField]->FieldCode == 50)
	{
		char szBuff[255];
		int WinX = (WinSizeX / 2);

		
		UINT Minutes = (EventBattleArenaTime / 60) % 60;
		UINT Seconds = EventBattleArenaTime % 60;
		wsprintf(szBuff, "Tempo Restante: %02d:%02d", Minutes, Seconds);
		DrawFontImage(szBuff, WinSizeX / 2 - 60, 12, D3DCOLOR_RGBA(100, 100, 255, 255), 0.7f);

		if (Battle.BPlayer1 > 0 && strlen(Battle.NPlayer1) > 0)
		{
			wsprintf(szBuff, "%d", Battle.BPlayer1);
			DrawFontImage(szBuff, WinX - 60, 31, D3DCOLOR_RGBA(200, 0, 0, 255), 0.7f);
			DrawFontImage(Battle.NPlayer1, WinX, 31, D3DCOLOR_RGBA(0, 255, 0, 255), 0.7f);
		}

		if (Battle.BPlayer2 > 0 && strlen(Battle.NPlayer2) > 0)
		{
			wsprintf(szBuff, "%d", Battle.BPlayer2);
			DrawFontImage(szBuff, WinX - 60, 50, D3DCOLOR_RGBA(200, 0, 0, 255), 0.7f);
			DrawFontImage(Battle.NPlayer2, WinX, 50, D3DCOLOR_RGBA(0, 255, 0, 255), 0.7f);
		}

		if (Battle.BPlayer3 > 0 && strlen(Battle.NPlayer3) > 0)
		{
			wsprintf(szBuff, "%d", Battle.BPlayer3);
			DrawFontImage(szBuff, WinX - 60, 69, D3DCOLOR_RGBA(200, 0, 0, 255), 0.7f);
			DrawFontImage(Battle.NPlayer3, WinX, 69, D3DCOLOR_RGBA(0, 255, 0, 255), 0.7f);
		}

	}

	if (EventBattleArena == 3 && StageField[lpCurPlayer->OnStageField]->FieldCode == 32)
	{
		char szBuff[255];
		int WinX = (WinSizeX / 2);

		wsprintf(szBuff, "Inicia em breve");
		DrawFontImage(szBuff, WinSizeX / 2, 12, D3DCOLOR_RGBA(255, 255, 255, 255), 0.7f);

	}

	if (EventBattleArena == 5 && StageField[lpCurPlayer->OnStageField]->FieldCode == 32)
	{
		char szBuff[255];
		int WinX = (WinSizeX / 2);

		UINT Minutes = (EventBattleArenaTime / 60) % 60;
		UINT Seconds = EventBattleArenaTime % 60;
		wsprintf(szBuff, "Tempo Restante: %02d:%02d", Minutes, Seconds);
		DrawFontImage(szBuff, WinSizeX / 2 , 12, D3DCOLOR_RGBA(255, 255, 255, 255), 0.7f);

	}



	if(haSiegeBoardFlag)
	{

		char  TempBuff[64];
		memset(&TempBuff, 0, sizeof(TempBuff));

		if(rsBlessCastle.TimeSec[0] < 10)
		{
			if(haStartPosiX < WinSizeX / 2 + 256 / 2)
			{
				haStartPosiX += 8 + haStartPosiX / 2;
				if(haAlpha < 255)
					haAlpha += 20;
				else
					haAlpha = 255;
			}
			else
			{
				haStartPosiX = WinSizeX / 2 + 256 / 2;
				if(haAlpha > 0)
					haAlpha -= 5;
				else
					haAlpha = 0;
			}
			dsDrawTexImage(haStartTga, haStartPosiX - 256, haStartPosiY, 256, 64, haAlpha);
		}

		DrawFontImage(ScoreBoardName[5], WinSizeX / 2 - 200, 5, D3DCOLOR_RGBA(0, 255, 0, 255), 1.0f);
		DrawFontImage(ScoreBoardName[4], WinSizeX / 2 - 200, 30, D3DCOLOR_RGBA(255, 255, 0, 255), 0.7f);
		DrawFontImage(ScoreBoardName[1], WinSizeX / 2 - 200, 49, D3DCOLOR_RGBA(255, 255, 0, 255), 0.7f);

		DrawFontImage(ScoreBoardName[3], WinSizeX / 2 + 20, 7, D3DCOLOR_RGBA(100, 100, 255, 255), 0.8f);
		wsprintf(TempBuff, "%d:%d:%d", haPlayTime[2], haPlayTime[1], haPlayTime[0]);
		DrawFontImage(TempBuff, WinSizeX / 2 + 115, 7, D3DCOLOR_RGBA(100, 100, 255, 255), 0.8f);

		DrawFontImage(ScoreBoardName[0], WinSizeX / 2 - 360, 7, D3DCOLOR_RGBA(0, 255, 0, 255), 0.7f);
		wsprintf(TempBuff, "%d", lpCurPlayer->sBlessCastle_Damage[1]);
		DrawFontImage(TempBuff, WinSizeX / 2 - 240, 7, D3DCOLOR_RGBA(200, 0, 0, 255), 0.7f);

		if(!haStartTga)
		{
			haStartTga = CreateTextureMaterial("image\\Bellatra\\T_Start_278_65.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
			ReadTextures();
		}

		for(i = 0; i < 10; i++)
		{
			if(sHaClanData[i].Flag)
			{
				if(GetClanCode(lpCurPlayer->smCharInfo.ClassClan) == sHaClanData[i].CLANCODE)
				{
					wsprintf(TempBuff, "%d", sHaClanData[i].Score * 100 / haTotalDamage);
					if(haTempScore[0] == sHaClanData[i].Score * 100 / haTotalDamage)
						DrawFontImage(TempBuff, WinSizeX / 2 - 100, 30, D3DCOLOR_RGBA(255, 255, 0, 255), 0.8f);
					else
						DrawFontImage(TempBuff, WinSizeX / 2 - 100, 29, D3DCOLOR_RGBA(255, 0, 0, 255), 0.8f);
					haTempScore[0] = sHaClanData[i].Score * 100 / haTotalDamage;

					wsprintf(TempBuff, "%d", (int)lpCurPlayer->sBlessCastle_Damage[0] * 100 / sHaClanData[i].Score);
					if(haTempScore[1] == (int)lpCurPlayer->sBlessCastle_Damage[0] * 100 / sHaClanData[i].Score)
						DrawFontImage(TempBuff, WinSizeX / 2 - 100, 49, D3DCOLOR_RGBA(255, 255, 0, 255), 0.8f);
					else
						DrawFontImage(TempBuff, WinSizeX / 2 - 100, 48, D3DCOLOR_RGBA(255, 0, 0, 255), 0.8f);
					haTempScore[1] = (int)lpCurPlayer->sBlessCastle_Damage[0] * 100 / sHaClanData[i].Score;
				}
			}
		}
		int TempCount = 0;
		for(i = 0; i < 5; i++)
		{
			if(sHaClanData[i].Flag)
			{
				
				
				
				wsprintf(TempBuff, "%d", sHaClanData[i].Score);
				if(GetClanCode(lpCurPlayer->smCharInfo.ClassClan) == sHaClanData[i].CLANCODE)
				{
					DrawFontImage(TempBuff, WinSizeX / 2 + 120, 30 + i * 17, D3DCOLOR_RGBA(255, 255, 0, 255), 0.6f);
				}
				else
				{
					DrawFontImage(TempBuff, WinSizeX / 2 + 120, 30 + i * 17, D3DCOLOR_RGBA(255, 128, 0, 255), 0.6f);
				}
				
				DrawSprite(WinSizeX / 2 + 20, 30 + i * 17, sHaClanData[i].lpClanMark, 0, 0, 16, 16, 1);
			}
			if(haCrystalTowerCount[i] && i < 4)
			{
				TempCount += haCrystalTowerCount[i];
				if(lpTwoerImage == NULL)
				{
					lpTwoerImage = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\Tower_image.bmp");
				}
			}
		}
		for(i = 0; i < TempCount; i++)
		{
			DrawSprite(WinSizeX / 2 - 360 + i * 20, 30, lpTwoerImage, 0, 0, 16, 32, 1);
		}
	}


	if(MouseButton[0] == FALSE)
	{
		MouseDownFlag = FALSE;
	}

	int downFlag = -1;

	if(haMovieFlag)
	{
		char szBuff[128];

		for(i = 0; i < 9; i++)
		{
			wsprintf(szBuff, "Image\\SinImage\\Player\\ha_B%d.tga", i + 1);
			if(haMatPlayMenu[i] == NULL)
			{
				haMatPlayMenu[i] = CreateTextureMaterial(szBuff, 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
				ReadTextures();
			}
		}

		for(i = 0; i < 7; i++)
		{
			dsDrawTexImage(haMatPlayMenu[1], 26 + 64 + (i * 32), 70, 32, 64, 255);
			if(i < 6)
			{
				dsDrawTexImage(haMatPlayMenu[3], 64 + (8 * 32), 70 + 64 + (i * 32), 32, 32, 255);
				dsDrawTexImage(haMatPlayMenu[7], 40, 70 + 64 + (i * 32), 32, 32, 255);
			}
			dsDrawTexImage(haMatPlayMenu[5], 26 + 32 + (i * 32), 70 + 64 + (6 * 32), 64, 64, 255);
		}
		dsDrawTexImage(haMatPlayMenu[0], 40, 70, 64, 64, 255);
		dsDrawTexImage(haMatPlayMenu[2], 64 + (i * 32), 70, 64, 64, 255);
		dsDrawTexImage(haMatPlayMenu[4], 64 + (i * 32), 70 + 64 + ((i - 1) * 32), 64, 64, 255);
		dsDrawTexImage(haMatPlayMenu[6], 40, 70 + 64 + ((i - 1) * 32), 64, 64, 255);
		dsDrawTexImage(haMatPlayMenu[5], 26 + 32 + (8 * 32), 70 + 64 + (6 * 32), 18, 64, 255);

		for(i = 0; i < 3; i++)
		{
			wsprintf(szBuff, "Image\\SinImage\\Player\\habox_0%d.bmp", i + 1);
			if(haPlayerButtonBox[i] == NULL)
			{
				haPlayerButtonBox[i] = LoadDibSurfaceOffscreen(szBuff);
			}
			wsprintf(szBuff, "Image\\SinImage\\Player\\ha_S%d_.bmp", i + 1);
			if(haPlayerButton_G[i] == NULL)
			{
				haPlayerButton_G[i] = LoadDibSurfaceOffscreen(szBuff);
			}
			wsprintf(szBuff, "Image\\SinImage\\Player\\ha_S%d.bmp", i + 1);
			if(haPlayerButton[i] == NULL)
			{
				haPlayerButton[i] = LoadDibSurfaceOffscreen(szBuff);
			}
			wsprintf(szBuff, "Image\\SinImage\\Player\\ha0%d.bmp", i + 1);
			if(haPlayerButtonDown[i] == NULL)
			{
				haPlayerButtonDown[i] = LoadDibSurfaceOffscreen(szBuff);
			}
			DrawSprite(haPlayerPosi[0][0] + (i * 34), haPlayerPosi[0][1], haPlayerButton_G[i], 0, 0, haPlayerPosi[0][2], haPlayerPosi[0][3], 1);

		}
		DrawSprite(haPlayerPosi[0][0] + ((ParkPlayMode / 150) * 34), haPlayerPosi[0][1], haPlayerButton[ParkPlayMode / 150], 0, 0, 32, 32, 1);
		DrawSprite(120, 74, haPlayerButtonBox[0], 0, 0, 149, 23, 1);
		DrawSprite(64, 363, haPlayerButtonBox[1], 0, 0, 68, 23, 1);
		DrawSprite(haPlayerPosi[1][0], haPlayerPosi[1][1], haPlayerButtonBox[2], 0, 0, haPlayerPosi[1][2], haPlayerPosi[1][3], 1);
		DrawSprite(78, 368, haPlayerButtonDown[2], 0, 0, 36, 12, 1);
		if(haMovieKind == 4)
		{
			DrawSprite(haPlayerPosi[1][0] + 8, haPlayerPosi[1][1] + 5, haPlayerButtonDown[0], 0, 0, 32, 16, 1);
		}
		else
		{
			DrawSprite(haPlayerPosi[1][0] + 8, haPlayerPosi[1][1] + 5, haPlayerButtonDown[1], 0, 0, 32, 16, 1);
		}


	}

}



int cHASIEGE::ShowSiegeMenu(smTRANS_BLESSCASTLE *pData)
{

	int i;

#ifdef _WINMODE_DEBUG
#else
	if(rsBlessCastle.dwMasterClan != GetClanCode(lpCurPlayer->smCharInfo.ClassClan))return TRUE;
#endif
	SendClanMoneyToServer(0, 0, 1);
	cSinSiege.ClanSkill = pData->ClanSkill;
	for(i = 0; i < 3; i++)
	{
		cSinSiege.MercenaryNum[i] = pData->MercenaryNum[i];
	}
	for(i = 0; i < 6; i++)
	{
		cSinSiege.TowerTypeDraw[i][0] = 0;
		cSinSiege.TowerTypeDraw[0][0] = 1;
		cSinSiege.TowerTypeDraw[i][1] = pData->Tower[i];

	}
	ImageLoad();

	int Temp = 0, Temp2 = 0;
	Temp = (pData->TaxRate * 22) + 96;
	Temp2 = (cSinSiege.TaxRate * 22) + 96 - 8;



	SiegeIconPosi[0][0] = Temp - 2;
	SiegeIconPosi[5][0] = Temp2 - 2;
	HaTaxRate = pData->TaxRate;



	haSiegeMenuFlag = 1;
	haSiegeMenuKind = HASIEGE_TAXRATES;

	return TRUE;
}

int cHASIEGE::ShowSiegeScore(rsUSER_LIST_TOP10 *pData)
{
	int i;

	for(i = 0; i < HACLAN_MAX; i++)
	{
		if(pData->dwUserCode[i] && pData->Damage[i])
		{

			sHaClanData[i].CLANCODE = pData->dwUserCode[i];
			sHaClanData[i].Score = pData->Damage[i];
			haTotalDamage = pData->dwTotalDamage;
			sHaClanData[i].Flag = 1;

			sHaClanData[i].ClanInfoNum = ReadClanInfo(sHaClanData[i].CLANCODE);
			if(sHaClanData[i].ClanInfoNum >= 0)
			{
				strcpy_s(sHaClanData[i].ClanName, ClanInfo[sHaClanData[i].ClanInfoNum].ClanInfoHeader.ClanName);
				sHaClanData[i].lpClanMark = ClanInfo[sHaClanData[i].ClanInfoNum].hClanMark;
			}
		}
	}

	for(i = 0; i < 4; i++)
	{
		haCrystalTowerCount[i] = pData->bCrystalTowerCount[i];
	}


	return TRUE;
}

int cHASIEGE::ShowExitMessage()
{

	haSiegeBoardFlag = 0;
	SetCastleInit();


	if(rsBlessCastle.dwMasterClan == GetClanCode(lpCurPlayer->smCharInfo.ClassClan))
	{
		cSinHelp.sinShowHelp(SIN_HELP_KIND_C_TELEPORT, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), haC_CastleWinFilePath);
	}
	else
	{
		cSinHelp.sinShowHelp(SIN_HELP_KIND_C_TELEPORT, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), haC_CastleLoseFilePath);

	}
	return TRUE;
}

int cHASIEGE::SetCastleInit()
{
	for(int i = 0; i < 3; i++)
	{
		haPlayTime[i] = 0;
	}
	for(int i = 0; i < HACLAN_MAX; i++)
	{
		sHaClanData[i].CLANCODE = 0;
		sHaClanData[i].Flag = 0;
		sHaClanData[i].lpClanMark = 0;
		sHaClanData[i].Score = 0;

		if(i < 4)
		{
			haCrystalTowerCount[i] = 0;
		}
	}
	BoardTime = 60 * 30;

	return TRUE;
}

int cHASIEGE::ShowPlayTime(int StartTime)
{
	if(StartTime == 0)
	{
		SetCastleInit();
		return TRUE;
	}

	haPlayTime[0] = StartTime % 60;
	haPlayTime[1] = StartTime / 60;
	haPlayTime[1] -= StartTime / 3600 * 60;
	haPlayTime[2] = StartTime / 3600;







	if(rsBlessCastle.TimeSec[1] > 0)
	{
		haSiegeBoardFlag = 1;
		BoardTime = 0;
	}
	else
	{
		haSiegeBoardFlag = 0;
		haStartPosiX = 0;
	}
	return TRUE;
}

int cHASIEGE::ShowPickUserKillPoint(int x, int y, int KillCount)
{
	char TempBuff[32];
	memset(&TempBuff, 0, sizeof(TempBuff));

	DrawFontImage(ScoreBoardName[2], x, y, D3DCOLOR_RGBA(0, 255, 0, 255), 0.7f);
	wsprintf(TempBuff, "%d", KillCount);
	DrawFontImage(TempBuff, x + 24, y, D3DCOLOR_RGBA(255, 0, 0, 255), 0.7f);

	return TRUE;
}


int cHASIEGE::SetClanSkill(int ClanSkill)
{
	DWORD SkillCode;

	haClanSkillTime = 0;

	switch(ClanSkill)
	{
	case SIN_CLANSKILL_ABSORB:
		SkillCode = CLANSKILL_ABSORB;
		break;
	case SIN_CLANSKILL_DAMAGE:
		SkillCode = CLANSKILL_ATTACK;
		break;
	case SIN_CLANSKILL_EVASION:
		SkillCode = CLANSKILL_EVASION;
		break;
	}

	if(rsBlessCastle.dwMasterClan == GetClanCode(lpCurPlayer->smCharInfo.ClassClan))
	{
		if(cSkill.SearchContiueSkillCODE(SkillCode) == SkillCode)
		{
			return TRUE;
		}
		else
		{
			cSkill.CancelContinueSkill(CLANSKILL_ATTACK);
			cSkill.CancelContinueSkill(CLANSKILL_EVASION);
			cSkill.CancelContinueSkill(CLANSKILL_ABSORB);
		}
	}
	else
	{
		cSkill.CancelContinueSkill(CLANSKILL_ATTACK);
		cSkill.CancelContinueSkill(CLANSKILL_EVASION);
		cSkill.CancelContinueSkill(CLANSKILL_ABSORB);
		return TRUE;
	}


	sSKILL haClanSkill;

	for(int j = 0; j < SIN_MAX_SKILL; j++)
	{
		if(sSkill[j].CODE == SkillCode)
		{
			memcpy(&haClanSkill, &sSkill[j], sizeof(sSKILL));
			haClanSkill.UseTime = 60;
			sinContinueSkillSet(&haClanSkill);
			break;
		}
	}
	cInvenTory.SetItemToChar();

	return TRUE;
}

int SetSODSkill(int SODSkill)
{
	DWORD SkillCode = 0;

	switch(SODSkill)
	{
	case SIN_SODSKILL_GOLD:
		SkillCode = SOD_SKILL_GOLD;
		break;
	case SIN_SODSKILL_SILVER:
		SkillCode = SOD_SKILL_SILVER;
		break;
	case SIN_SODSKILL_BRONZE:
		SkillCode = SOD_SKILL_BRONZE;
		break;
	}

	if(SODSkill)
	{
		if(cSkill.SearchContiueSkillCODE(SkillCode) == SkillCode)
		{
			return TRUE;
		}
		else
		{
			cSkill.CancelContinueSkill(SOD_SKILL_GOLD);
			cSkill.CancelContinueSkill(SOD_SKILL_SILVER);
			cSkill.CancelContinueSkill(SOD_SKILL_BRONZE);
		}
	}
	else
	{
		cSkill.CancelContinueSkill(SOD_SKILL_GOLD);
		cSkill.CancelContinueSkill(SOD_SKILL_SILVER);
		cSkill.CancelContinueSkill(SOD_SKILL_BRONZE);
		return TRUE;
	}

	sSKILL haClanSkill;

	for(int j = 0; j < SIN_MAX_SKILL; j++)
	{
		if(sSkill[j].CODE == SkillCode)
		{
			memcpy(&haClanSkill, &sSkill[j], sizeof(sSKILL));
			haClanSkill.UseTime = 60;
			sinContinueSkillSet(&haClanSkill);
			break;
		}
	}
	cInvenTory.SetItemToChar();

	return TRUE;
}


int haCastleSkillUseFlag = 0;
int cHASIEGE::SetCastleItemSkill(int ItemKind)
{
	DWORD CastleSkillCode;
	int   CastleSkillUseTime = 0;

	switch(ItemKind)
	{
	case SIN_CASTLEITEMSKILL_S_INVU:
		CastleSkillCode = SCROLL_INVULNERABILITY;
		CastleSkillUseTime = 30;
		break;
	case SIN_CASTLEITEMSKILL_S_CRITICAL:
		CastleSkillCode = SCROLL_CRITICAL;
		CastleSkillUseTime = 30;
		break;
	case SIN_CASTLEITEMSKILL_S_EVASION:
		CastleSkillCode = SCROLL_EVASION;
		CastleSkillUseTime = 30;
		break;
	case SIN_CASTLEITEMSKILL_S_P_LIFE:
		CastleSkillCode = 0;
		break;
	case SIN_CASTLEITEMSKILL_S_RES:
		CastleSkillCode = 0;
		break;
	case SIN_CASTLEITEMSKILL_R_FIRE_C:
		CastleSkillCode = STONE_R_FIRECRYTAL;
		CastleSkillUseTime = 60;
		break;
	case SIN_CASTLEITEMSKILL_R_ICE_C:
		CastleSkillCode = STONE_R_ICECRYTAL;
		CastleSkillUseTime = 60;
		break;
	case SIN_CASTLEITEMSKILL_R_LIGHTING_C:
		CastleSkillCode = STONE_R_LINGHTINGCRYTAL;
		CastleSkillUseTime = 60;
		break;
	case SIN_CASTLEITEMSKILL_A_FIGHTER:
		CastleSkillCode = STONE_A_FIGHTER;
		CastleSkillUseTime = 60;
		break;
	case SIN_CASTLEITEMSKILL_A_MECHANICIAN:
		CastleSkillCode = STONE_A_MECHANICIAN;
		CastleSkillUseTime = 60;
		break;
	case SIN_CASTLEITEMSKILL_A_PIKEMAN:
		CastleSkillCode = STONE_A_PIKEMAN;
		CastleSkillUseTime = 60;
		break;
	case SIN_CASTLEITEMSKILL_A_ARCHER:
		CastleSkillCode = STONE_A_ARCHER;
		CastleSkillUseTime = 60;
		break;
	case SIN_CASTLEITEMSKILL_A_KNIGHT:
		CastleSkillCode = STONE_A_KNIGHT;
		CastleSkillUseTime = 60;
		break;
	case SIN_CASTLEITEMSKILL_A_ATALANTA:
		CastleSkillCode = STONE_A_ATALANTA;
		CastleSkillUseTime = 60;
		break;
	case SIN_CASTLEITEMSKILL_A_MAGICIAN:
		CastleSkillCode = STONE_A_MAGICIAN;
		CastleSkillUseTime = 60;
		break;
	case SIN_CASTLEITEMSKILL_A_PRIESTESS:
		CastleSkillCode = STONE_A_PRIESTESS;
		CastleSkillUseTime = 60;
		break;
	}

	sSKILL haCastleSkill;

	if(cSkill.SearchContiueSkillCODE(CastleSkillCode) == CastleSkillCode && CastleSkillCode != 0)
	{
		cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
		haCastleSkillUseFlag = 0;
		return TRUE;
	}
	haCastleSkillUseFlag = 1;
	if(CastleSkillCode == 0)return TRUE;

	for(int j = 0; j < SIN_MAX_SKILL; j++)
	{
		if(sSkill[j].CODE == CastleSkillCode)
		{
			memcpy(&haCastleSkill, &sSkill[j], sizeof(sSKILL));
			haCastleSkill.UseTime = CastleSkillUseTime;
			sinContinueSkillSet(&haCastleSkill);
			SwitchSkill(&haCastleSkill);
			break;
		}
	}

	return TRUE;
}


int cHASIEGE::SendServerSiegeData()
{
	int i;

	smTRANS_BLESSCASTLE TempBlessCastle;

	TempBlessCastle.TaxRate = HaTaxRate;
	TempBlessCastle.ClanSkill = cSinSiege.ClanSkill;
	TempBlessCastle.Price = cSinSiege.Price;
	for(i = 0; i < 3; i++)
	{
		TempBlessCastle.MercenaryNum[i] = cSinSiege.MercenaryNum[i];
	}
	for(i = 0; i < 6; i++)
	{
		TempBlessCastle.Tower[i] = cSinSiege.TowerTypeDraw[i][1];
	}

	SendBlessCastleToServer(&TempBlessCastle, 0);
	SaveGameData();
	return TRUE;
}



int cHASIEGE::SetCastleMenuInit()
{
	haSiegeMenuFlag = 0;
	haSiegeMenuKind = 0;
	haSiegeMerFlag = 0;
	SiegeIconPosi[0][0] = 70 + 20 - 7;
	SiegeIconPosi[5][0] = 70 + 20 - 7;

	return TRUE;
}

void cHASIEGE::KeyDown()
{

}

void cHASIEGE::LButtonDown(int x, int y)
{

	int i;



	if(haSiegeMenuFlag)
	{

		if(cldata.myPosition == 101)
		{
			if(GraphLineFlag)
			{
				if(SiegeIconPosi[0][0] - 16 < pCursorPos.x && SiegeIconPosi[0][0] + SiegeIconPosi[0][2] + 16 > pCursorPos.x && SiegeIconPosi[0][1] - 16 < pCursorPos.y && SiegeIconPosi[0][1] + SiegeIconPosi[0][3] + 16 > pCursorPos.y)
				{
					ScrollButtonFlag = 1;
				}
				else
				{
					SiegeIconPosi[0][0] = pCursorPos.x;
				}
			}
			if(CastleKindIndex)
			{
				for(i = 0; i < 6; i++)
				{
					if((CastleKindIndex - 1) == i)
					{
						cSinSiege.TowerTypeDraw[CastleKindIndex - 1][0] = CastleKindIndex;
					}
					else
					{
						cSinSiege.TowerTypeDraw[i][0] = 0;

					}
				}
			}
			if(TowerIconIndex)
			{
				if(TowerIconIndex < 4)
				{
					if(haSiegeMerFlag)
					{
						haMercenrayIndex = TowerIconIndex;
						if(cSinSiege.MercenaryNum[haMercenrayIndex - 1] < 20)
						{
							cMessageBox.ShowMessage2(MESSAGE_SIEGE_SET_MERCENRAY);
						}
					}
					else
					{
						for(i = 0; i < 6; i++)
						{
							if(cSinSiege.TowerTypeDraw[i][0])
							{
								haSendTowerIndex = TowerIconIndex;
								if(cSinSiege.TowerTypeDraw[i][1] == 0)
								{
									switch(TowerIconIndex)
									{
									case 1:
										cMessageBox.ShowMessage3(MESSAGE_CASTLE_BUYTOWER, "ICE");
										break;
									case 2:
										cMessageBox.ShowMessage3(MESSAGE_CASTLE_BUYTOWER, "LIGHTING");
										break;
									case 3:
										cMessageBox.ShowMessage3(MESSAGE_CASTLE_BUYTOWER, "FIRE");
										break;
									}
								}
								else
								{
									cSinSiege.TowerTypeDraw[i][1] = TowerIconIndex;
								}
							}
						}
					}
				}
				else
				{

					cSinSiege.ClanSkill = TowerIconIndex - 3;
				}
			}
		}
		switch(MenuButtonIndex)
		{
		case 2:
			if(cldata.myPosition == 101)
			{
				SendServerSiegeData();
				SetCastleMenuInit();
			}
			break;
		case 3:
			SetCastleMenuInit();
			break;
		case 4:
			if(cldata.myPosition == 101)
			{
				if(haSiegeMenuKind == HASIEGE_TAXRATES)
				{

					if((int)cSinSiege.TotalTax <= 0)
					{
						cMessageBox.ShowMessage(MESSAGE_NOT_CASTLE_TOTALMONEY);
					}
					else
					{
						cMessageBox.ShowMessage2(MESSAGE_SIEGE_GET_MONEY);
					}
				}
			}
			break;
		case 5:
			haSiegeMerFlag = 0;
			break;
		case 6:
			haSiegeMerFlag = 1;
			break;
		case 7:
			haSiegeMenuKind = 2;
			break;
		case 8:
			haSiegeMenuKind = 1;
			break;
		}
	}



	if(haMovieFlag)
	{
		switch(haMovieKind)
		{
		case 1:
			ParkPlayMode = 0;
			break;
		case 2:
			ParkPlayMode = 150;
			break;
		case 3:
			ParkPlayMode = 300;
			break;
		case 4:
			haMovieFlag = 0;
			Stop_ParkPlayer();
			break;
		}
	}

}
void cHASIEGE::LButtonUp(int x, int y)
{
	if(haSiegeMenuFlag)
	{
		if(ScrollButtonFlag)
		{
			ScrollButtonFlag = 0;
		}
	}
}

void cHASIEGE::DrawText()
{
	HDC	hdc = NULL;
	
	//SelectObject(hdc, sinFont);
	
	SetFontTextColor( RGB(255, 255, 255));

	char szTempBuff[128];
	char haTempBuffer[128];





	if(haSiegeMenuFlag)
	{

		int  TempCount = 0;
		int  Skilllen = 0;
		int  cnt = 0, cnt1 = 0, cnt2 = 0;
		int  i = 0, j = 0;
		int  stringcut = 18;

		int  LineCount[10] = { 0 };
		char TempBuffer[64];
		int  Taxlen = 0;

		switch(haSiegeMenuKind)
		{
		case HASIEGE_TAXRATES:

			HaTaxRate = SiegeIconPosi[0][0] - (73 + 24 - 9);
			HaTaxRate = HaTaxRate / 22;

			//SelectObject(hdc, sinBoldFont);
			SetFontTextColor( RGB(100, 200, 200));

			wsprintf(szTempBuff, SiegeMessage_Taxrates[4], cSinSiege.TaxRate, "%");
			dsTextLineOut( 97, 112, szTempBuff, lstrlen(szTempBuff));

			wsprintf(szTempBuff, SiegeMessage_Taxrates[0], HaTaxRate, "%");
			dsTextLineOut( 97, 182, szTempBuff, lstrlen(szTempBuff));

			memset(szTempBuff, 0, sizeof(szTempBuff));
			NumLineComa(cSinSiege.TotalTax, szTempBuff);
			lstrcat(szTempBuff, SiegeMessage_Taxrates[2]);

			Taxlen = lstrlen(szTempBuff);
			dsTextLineOut( 247 - ((Taxlen - 8) * 8), 260, szTempBuff, lstrlen(szTempBuff));


			//SelectObject(hdc, sinFont);
			SetFontTextColor( RGB(255, 255, 255));
			wsprintf(szTempBuff, SiegeMessage_Taxrates[1]);
			dsTextLineOut( 97, 244, szTempBuff, lstrlen(szTempBuff));

			SetFontTextColor( RGB(255, 255, 255));
			wsprintf(szTempBuff, SiegeMessage_Taxrates[3], HaTestMoney);
			dsTextLineOut( 97, 310, szTempBuff, lstrlen(szTempBuff));

			break;
		case HASIEGE_DEFENSE:

			int LinePosX = 0;
			int Linelen = 0;
			int LineSetX = 0;


			//SelectObject(hdc, sinBoldFont);
			
			SetFontTextColor( RGB(255, 200, 100));

			if(TowerIconIndex > 3)
			{
				for(i = 0; i < 160; i++)
				{
					if(sSkill_Info[i].CODE == CLANSKILL_ABSORB  && TowerIconIndex - 3 == 1)
					{
						TempCount = i;
						break;
					}
					if(sSkill_Info[i].CODE == CLANSKILL_ATTACK  && TowerIconIndex - 3 == 2)
					{
						TempCount = i;
						break;
					}
					if(sSkill_Info[i].CODE == CLANSKILL_EVASION && TowerIconIndex - 3 == 3)
					{
						TempCount = i;
						break;
					}
				}


				wsprintf(szTempBuff, sSkill_Info[TempCount].SkillName);
				LineSetX = 4;
				Linelen = lstrlen(szTempBuff);
				LinePosX = (ClanSkillBoxSize.x * 16 - (Linelen * 8)) / 2;

				LineSetX += Linelen / 8 * 5;

				dsTextLineOut( ClanSkillBoxPosi.x + LineSetX + LinePosX, ClanSkillBoxPosi.y + 20, szTempBuff, lstrlen(szTempBuff));


				//SelectObject(hdc, sinFont);
				SetFontTextColor( RGB(250, 250, 250));

				Skilllen = lstrlen(sSkill_Info[TempCount].SkillDoc);
				strcpy_s(haTempBuffer, sSkill_Info[TempCount].SkillDoc);


				for(cnt = 0; cnt < Skilllen; cnt++)
				{
					if(cnt1*stringcut + stringcut > cnt)continue;
					if(haTempBuffer[cnt] == ' ')
					{
						if(LineCount[cnt1] - cnt)
							LineCount[cnt1++] = cnt + 1;
					}
				}

				LineCount[cnt1++] = Skilllen;



				for(j = 0; j < cnt1 + 1; j++)
				{

					memset(TempBuffer, 0, sizeof(TempBuffer));
					for(i = 0; cnt2 < LineCount[j * 1]; i++, cnt2++)
					{
						TempBuffer[i] = haTempBuffer[cnt2];
					}

					strcpy_s(szTempBuff, TempBuffer);
					Linelen = lstrlen(szTempBuff);
					LineSetX = 0;
					LineSetX += Linelen / 4 * 5;
					LinePosX = (ClanSkillBoxSize.x * 16 - (Linelen * 8)) / 2;
					dsTextLineOut( ClanSkillBoxPosi.x + LineSetX + LinePosX, ClanSkillBoxPosi.y + 40 + j * 18, szTempBuff, lstrlen(szTempBuff));
				}
			}

			memset(TempBuffer, 0, sizeof(TempBuffer));
			if(TowerIconIndex > 0)
			{
				cSinSiege.MercenaryNumDraw = cSinSiege.MercenaryNum[TowerIconIndex - 1];
				for(i = 0; i < 5; i++)
				{
					switch(TowerIconIndex)
					{
					case 1:
						if(haSiegeMerFlag)
						{
							if(i == 3)
							{
								wsprintf(szTempBuff, SiegeMessage_MercenrayA[i], cSinSiege.MercenaryNumDraw);
							}
							else
								strcpy_s(szTempBuff, SiegeMessage_MercenrayA[i]);
						}
						else
						{
							if(i > 3)break;
							strcpy_s(szTempBuff, SiegeMessage_TowerIce[i]);
						}
						break;
					case 2:
						if(haSiegeMerFlag)
						{
							if(i == 3)
							{
								wsprintf(szTempBuff, SiegeMessage_MercenrayB[i], cSinSiege.MercenaryNumDraw);
							}
							else
								strcpy_s(szTempBuff, SiegeMessage_MercenrayB[i]);

						}

						else
						{
							if(i > 3)break;
							strcpy_s(szTempBuff, SiegeMessage_TowerLighting[i]);
						}
						break;
					case 3:
						if(haSiegeMerFlag)
						{
							if(i == 3)
							{
								wsprintf(szTempBuff, SiegeMessage_MercenrayC[i], cSinSiege.MercenaryNumDraw);
							}
							else
								strcpy_s(szTempBuff, SiegeMessage_MercenrayC[i]);
						}
						else
						{
							if(i > 3)break;
							strcpy_s(szTempBuff, SiegeMessage_TowerFire[i]);
						}
						break;
					}

					int TempIndex = 0;
					int TempIconIndex[3] = { 0 };
					for(int k = 0; k < 6; k++)
					{
						if(cSinSiege.TowerTypeDraw[k][0])
						{
							TempIndex = cSinSiege.TowerTypeDraw[k][0];
							break;
						}
					}
					if(TowerIconIndex)
					{
						if(cSinSiege.MercenaryNum[TowerIconIndex - 1])
						{
							TempIconIndex[TowerIconIndex - 1] = cSinSiege.MercenaryNum[TowerIconIndex - 1];
						}
					}

					//SelectObject(hdc, sinBoldFont);
					LineSetX = 4;
					Linelen = lstrlen(szTempBuff);
					LinePosX = (ClanSkillBoxSize.x * 16 - (Linelen * 8)) / 2;
					LineSetX += Linelen / 8 * 5;


					if(i == 0)
					{
						SetFontTextColor( RGB(100, 100, 200));
					}
					else if(i == 3 && cSinSiege.TowerTypeDraw[TempIndex - 1][1] == TowerIconIndex && !haSiegeMerFlag)
					{
						SetFontTextColor( RGB(200, 200, 100));
					}
					else if(i == 4 && haSiegeMerFlag && cSinSiege.MercenaryNumDraw == 20)
					{
						SetFontTextColor( RGB(200, 200, 100));

					}
					else
					{
						//SelectObject(hdc, sinFont);
						SetFontTextColor( RGB(250, 250, 250));
						Linelen = lstrlen(szTempBuff);
						LineSetX = -4;
						LineSetX += Linelen / 4 * 5;
						LinePosX = (ClanSkillBoxSize.x * 16 - (Linelen * 8)) / 2;

					}
					char TempBuff[32];

					memset(&TempBuff, 0, sizeof(TempBuff));

					switch(i)
					{
					case 0:
						dsTextLineOut( ClanSkillBoxPosi.x + LineSetX + LinePosX, ClanSkillBoxPosi.y + 14, szTempBuff, lstrlen(szTempBuff));
						break;
					case 1:
					case 2:
					case 3:
						if(cSinSiege.TowerTypeDraw[TempIndex - 1][1] == TowerIconIndex && !haSiegeMerFlag)
						{
							dsTextLineOut( ClanSkillBoxPosi.x + LineSetX + LinePosX, ClanSkillBoxPosi.y + 20 + i * 18, szTempBuff, lstrlen(szTempBuff));
						}
						if(cSinSiege.TowerTypeDraw[TempIndex - 1][1] == 0 && !haSiegeMerFlag && i == 3 && TowerIconIndex < 4)
						{
							strcpy_s(szTempBuff, SiegeMessage_TowerMoney);
							NumLineComa(haTowerMoney, TempBuff);
							lstrcat(szTempBuff, TempBuff);
							lstrcat(szTempBuff, Won);

							Linelen = lstrlen(szTempBuff);
							LineSetX = -4;
							LineSetX += Linelen / 4 * 5;
							LinePosX = (ClanSkillBoxSize.x * 16 - (Linelen * 8)) / 2;
							dsTextLineOut( ClanSkillBoxPosi.x + LineSetX + LinePosX, ClanSkillBoxPosi.y + 20 + i * 18, szTempBuff, lstrlen(szTempBuff));

						}
						if(i == 3 && haSiegeMerFlag)
						{
							dsTextLineOut( ClanSkillBoxPosi.x + LineSetX + LinePosX, ClanSkillBoxPosi.y + 20 + i * 18, szTempBuff, lstrlen(szTempBuff));
						}
						else
						{
							dsTextLineOut( ClanSkillBoxPosi.x + LineSetX + LinePosX, ClanSkillBoxPosi.y + 20 + i * 18, szTempBuff, lstrlen(szTempBuff));
						}
						break;
					case 4:
						if(!haSiegeMerFlag || TowerIconIndex > 3) break;

						if(haSiegeMerFlag && cSinSiege.MercenaryNumDraw < 20)
						{
							strcpy_s(szTempBuff, SiegeMessage_MerMoney);
							NumLineComa(haMercenrayMoney[TowerIconIndex - 1], TempBuff);
							lstrcat(szTempBuff, TempBuff);
							lstrcat(szTempBuff, Won);
						}
						else
						{
							strcpy_s(szTempBuff, SiegeMessage_MerComplete);
						}
						Linelen = lstrlen(szTempBuff);
						LineSetX = -4;
						LineSetX += Linelen / 4 * 5;
						LinePosX = (ClanSkillBoxSize.x * 16 - (Linelen * 8)) / 2;
						dsTextLineOut( ClanSkillBoxPosi.x + LineSetX + LinePosX, ClanSkillBoxPosi.y + 20 + i * 18, szTempBuff, lstrlen(szTempBuff));

						break;
					}
				}
			}
			break;
		}
	}




	if(haSiegeBoardFlag)
	{
		//SelectObject(hdc, sinBoldFont);
		for(int i = 0; i < 5; i++)
		{
			if(sHaClanData[i].Flag)
			{
				if(sHaClanData[i].ClanInfoNum >= 0)
				{
					if(sinChar->ClassClan == sHaClanData[i].CLANCODE)
					{
						SetFontTextColor( RGB(200, 200, 0));
					}
					else
					{
						SetFontTextColor( RGB(200, 128, 0));
					}
					strcpy_s(szTempBuff, sHaClanData[i].ClanName);
					dsTextLineOut( WinSizeX / 2 + 40, 32 + i * 17, szTempBuff, lstrlen(szTempBuff));
				}
			}
		}
	}



	if(haMovieFlag)
	{
		//SelectObject(hdc, sinBoldFont);
		SetFontTextColor( RGB(255, 255, 255));
		dsTextLineOut( 152, 80, haMovieName, lstrlen(haMovieName));
	}

	
}


int cSINSIEGE::GetTaxRate()
{
	return TaxRate;
}
int cSINSIEGE::SetTaxRate(int TempTaxRate)
{
	TaxRate = TempTaxRate;
	return TRUE;
}

int cSINSIEGE::GetTotalTax()
{


	return TotalTax;
}
int cSINSIEGE::GetTaxMoney(int Money)
{

	return TRUE;
}


int cHASIEGE::ShowCastlePlayMovie(char *szPath, char *TitleName, int Option)
{

	memset(haMovieName, 0, sizeof(haMovieName));
	strcpy_s(haMovieName, TitleName);

	haMovieFlag = 1;

	if(haMovieFlag)
	{
		Play_ParkPlayer(szPath, 42, 100, 307, 260, 150);
	}
	return TRUE;
}





