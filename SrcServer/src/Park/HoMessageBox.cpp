#include "sinbaram\\SinLinkHeader.h"
#include "..\\HoBaram\\HoLinkHeader.h"


HoMessage	ChatMessage;
BOOL    HoMessage::MessageFrameSelectFlag = TRUE;


HoMessage::HoMessage()
{
}

HoMessage::~HoMessage()
{
}


int HoMessage::Init()
{
	return TRUE;
}

void HoMessage::DrawMessageBox(int x, int y, char *message, int boxAttrib, int Color)
{
}


#include "Language\\language.h"


int HoDrawLinearTexImage(int Mat, float x, float y, float w, float h, float texX, float texY, float texW, float texH, DWORD color){
	return TRUE;
}

int HoDrawTexImage(int Mat, float x, float y, float w, float h, float texX, float texY, float texW, float texH, int Transp){
	return TRUE;
}

int HoDrawTexImage(int Mat, int x, int y, int w, int h, int texX, int texY, int texW, int texH, int Transp){
	return TRUE;
}



int HoDrawTexImage(int Mat, int x, int y, int texX, int texY, int texW, int texH, int Transp){
	return TRUE;
}


void HoMessage::DrawClanName(int x, int y, char *clanName)
{
	x = x + 3;
	y = y - 12;

	if(clanName == NULL)
		return;
	int length = strlen(clanName);
	if(length < 1)
		return;


	renderDevice.BeginScene();
	HoDrawTexImage(ClanBoxImage[0], x, y, 16, 14, 0, 0, 16, 14, 255);
	for(int index = 0; index <= length; index++)
	{
		HoDrawTexImage(ClanBoxImage[1], float(x + 16) + (float)index*5.5f, (float)y, 5.5f, 14.f, 0.f, 0.f, 5.5f, 14.f, 255);
	}

	HoDrawTexImage(ClanBoxImage[2], float(x + 16) + (float)(length + 1)*5.5f, (float)y, 16.f, 14.f, 0.f, 0.f, 16.f, 14.f, 255);
	renderDevice.EndScene();

	HDC hdc = NULL;
	//renderDevice.lpDDSBack->GetDC(&hdc);
	if(sinFont != NULL)
		SelectObject(hdc, sinFont);

	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(0, 0, 0));
	dsTextLineOut(hdc, x + 15, y + 3, clanName, lstrlen(clanName));

	SetTextColor(hdc, RGB(230, 255, 160));
	dsTextLineOut(hdc, x + 15, y + 2, clanName, lstrlen(clanName));

	//renderDevice.lpDDSBack->ReleaseDC(hdc);
}

void HoMessage::DrawClanMark(DIRECTDRAWSURFACE clanMark, char *clanName, int x, int y, BOOL frameFlag)
{
	if(clanMark == NULL)
		return;

	if(frameFlag)
	{
		renderDevice.BeginScene();
		HoDrawTexImage(BoxImage3[0], x, y, 0, 0, 8, 8, 255);
		HoDrawTexImage(BoxImage3[2], x + 11 + 6, y, 0, 0, 8, 8, 255);
		HoDrawTexImage(BoxImage3[6], x, y + 5 + 11, 0, 0, 8, 8, 255);
		HoDrawTexImage(BoxImage3[8], x + 11 + 6, y + 5 + 11, 0, 0, 8, 8, 255);


		HoDrawTexImage(BoxImage3[3], x, y + 8, 0, 0, 8, 9, 255);
		HoDrawTexImage(BoxImage3[5], x + 11 + 6, y + 8, 0, 0, 8, 9, 255);


		HoDrawTexImage(BoxImage3[1], x + 8, y, 0, 0, 9, 8, 255);
		HoDrawTexImage(BoxImage3[7], x + 8, y + 8 + 8, 0, 0, 9, 8, 255);
		renderDevice.EndScene();
	}


	RECT surRect;
	surRect.left = 0;
	surRect.top = 0;
	surRect.right = 16;
	surRect.bottom = 16;


	renderDevice.BltFast(renderDevice.lpDDSBack, x + 4, y + 4, clanMark, &surRect, DDBLTFAST_WAIT);

	if(clanName != NULL)
		DrawClanName(x, y, clanName);
}

void HoMessage::DrawTwoLineMessage(int x, int y, char *message1, char *message2, DWORD color1, DWORD color2, DIRECTDRAWSURFACE clanMark, BOOL selected, int bellaMarkIndex)
{

	char MessageOne[64];
	char MessageTwo[64];

	if(message1 != NULL)
		strcpy(MessageOne, message1);

	if(message2 != NULL)
		strcpy(MessageTwo, message2);

	int messageWidth = 0;
	int messageHeight = 2;

	int messageTempLen1 = strlen(MessageOne);
	int messageTempLen2 = strlen(MessageTwo);

	int messageLen = messageTempLen2;
	if(messageTempLen1 > messageTempLen2)
		messageLen = messageTempLen1;

	if(clanMark != NULL)
	{
		if(messageLen < messageTempLen1 + 3)
			messageLen += 3;
	}

	int lineSize = messageLen;
	messageWidth = lineSize;
	x -= messageWidth / 2 * 6 + 18 / 2;
	y -= messageHeight * 14 + 8 * 2 + 8;

	DrawCharacterMessageFrame(x, y, messageWidth, messageHeight, false, selected);
	if(bellaMarkIndex != -1)
		DrawBellaIcon(x + 3 * messageWidth - 6, y - 30, bellaMarkIndex);

	HDC hdc = NULL;
	//renderDevice.lpDDSBack->GetDC(&hdc);
	if(hFont != NULL)
		SelectObject(hdc, hFont);
	SetBkMode(hdc, TRANSPARENT);

	if(color1 == 0)
		SetTextColor(hdc, RGB(255, 255, 255));
	else
		SetTextColor(hdc, color1);

	if(messageTempLen1 > 1)
	{
		if(clanMark == NULL)
			dsTextLineOut(hdc, x + 9 + messageWidth * 6 / 2 - messageTempLen1 * 6 / 2, y + 5 + 2, MessageOne, messageTempLen1);
		else
			dsTextLineOut(hdc, x + 9 + 6 * 3, y + 5 + 2, MessageOne, messageTempLen1);
	}

	if(color2 == 0)
		SetTextColor(hdc, RGB(255, 255, 255));
	else
		SetTextColor(hdc, color2);

	if(messageTempLen2 > 0)
		dsTextLineOut(hdc, x + 9 + messageWidth * 6 / 2 - messageTempLen2 * 6 / 2, y + 5 + 2 + 16, MessageTwo, messageTempLen2);

	//renderDevice.lpDDSBack->ReleaseDC(hdc);


	if(clanMark != NULL)
	{
		if(MessageFrameSelectFlag)
			DrawClanMark(clanMark, NULL, x + 3, y);
		else
			DrawClanMark(clanMark, NULL, x + 7, y + 1);
	}
}

void HoMessage::DrawBellaIcon(int x, int y, int bellaIndex)
{
	if(bellaIndex == 1 ||
	   bellaIndex == 2 ||
	   bellaIndex == 3)
	{
		renderDevice.BeginScene();

		if(bellaIndex == 1)
			HoDrawTexImage(BellaIconImage[0], x, y, 0, 0, 32, 32, 255);
		else if(bellaIndex == 2)
			HoDrawTexImage(BellaIconImage[1], x, y, 0, 0, 32, 32, 255);
		else if(bellaIndex == 3)
			HoDrawTexImage(BellaIconImage[2], x, y, 0, 0, 32, 32, 255);

		renderDevice.EndScene();
	}
}

void HoMessage::DrawClanMessageFrame(int x, int y, int messageWidth, int messageHeight)
{
	renderDevice.BeginScene();

	HoDrawTexImage(ClanBoxImage2[0], x, y, 0, 0, 11, 13, 255);
	HoDrawTexImage(ClanBoxImage2[2], x + 11 + messageWidth * 6, y, 5, 0, 11, 13, 255);
	HoDrawTexImage(ClanBoxImage2[6], x, y + 13 + (messageHeight - 1) * 14 + 14, 0, 3, 11, 13, 255);
	HoDrawTexImage(ClanBoxImage2[8], x + 11 + messageWidth * 6, y + 13 + (messageHeight - 1) * 14 + 14, 5, 3, 11, 13, 255);


	for(int m = 0; m < messageHeight; m++)
	{
		HoDrawTexImage(ClanBoxImage2[3], x, y + 13 + (14 * m), 0, 0, 11, 14, 255);
		HoDrawTexImage(ClanBoxImage2[5], x + 11 + messageWidth * 6, y + 13 + (14 * m), 5, 0, 11, 14, 255);
	}


	for(int m = 0; m < messageWidth; m++)
	{
		HoDrawTexImage(ClanBoxImage2[1], x + 11 + 6 * m, y, 0, 0, 6, 13, 255);
		HoDrawTexImage(ClanBoxImage2[7], x + 11 + 6 * m, y + 13 + (14 * (messageHeight - 1)) + 14, 0, 3, 6, 13, 255);
	}



	for(int n = 0; n < messageHeight; n++)
		for(int m = 0; m < messageWidth; m++)
		{
			if(n == 0)
			{
				HoDrawTexImage(ClanBoxImage2[4], x + 11 + m * 6, y + 13, 0, 0, 6, 14, 255);
			}
			else
			{
				HoDrawTexImage(ClanBoxImage2[4], x + 11 + m * 6, y + 13 + (n - 1) * 14 + 14, 0, 0, 6, 14, 255);
			}
		}
	renderDevice.EndScene();
}

void HoMessage::DrawCharacterMessageFrame(int x, int y, int messageWidth, int messageHeight, bool tailFlag, BOOL selected)
{
	renderDevice.BeginScene();

	if(MessageFrameSelectFlag == TRUE || tailFlag == TRUE)
	{
		HoDrawTexImage(BoxImage3[0], x, y, 0, 0, 11, 5, 255);
		HoDrawTexImage(BoxImage3[2], x + 11 + messageWidth * 6, y, 9, 0, 7, 5, 255);
		HoDrawTexImage(BoxImage3[6], x, y + 5 + (messageHeight - 1) * 16 + 14, 0, 3, 11, 5, 255);
		HoDrawTexImage(BoxImage3[8], x + 11 + messageWidth * 6, y + 5 + (messageHeight - 1) * 16 + 14, 9, 3, 7, 5, 255);
		if(selected)
		{

			HoDrawTexImage(BoxImage4[0], x, y, 0, 0, 11, 5, 255);
			HoDrawTexImage(BoxImage4[2], x + 11 + messageWidth * 6, y, 9, 0, 7, 5, 255);
			HoDrawTexImage(BoxImage4[6], x, y + 5 + (messageHeight - 1) * 16 + 14, 0, 3, 11, 5, 255);
			HoDrawTexImage(BoxImage4[8], x + 11 + messageWidth * 6, y + 5 + (messageHeight - 1) * 16 + 14, 9, 3, 7, 5, 255);
		}



		for(int m = 0; m < messageHeight; m++)
		{
			if(m == 0)
			{
				HoDrawTexImage(BoxImage3[3], x, y + 5, 0, 0, 8, 14, 255);
				HoDrawTexImage(BoxImage3[4], x + 8, y + 5, 0, 0, 3, 14, 255);
				HoDrawTexImage(BoxImage3[5], x + 11 + messageWidth * 6, y + 5, 9, 0, 7, 14, 255);
			}
			else
			{
				HoDrawTexImage(BoxImage3[3], x, y + 5 + (16 * (m - 1)) + 14, 0, 0, 8, 16, 255);
				HoDrawTexImage(BoxImage3[4], x + 8, y + 5 + (16 * (m - 1)) + 14, 0, 0, 3, 16, 255);
				HoDrawTexImage(BoxImage3[5], x + 11 + messageWidth * 6, y + 5 + (16 * (m - 1)) + 14, 9, 0, 7, 16, 255);
			}

			if(selected)
			{
				if(m == 0)
				{
					HoDrawTexImage(BoxImage4[3], x, y + 5, 0, 0, 8, 14, 255);

					HoDrawTexImage(BoxImage4[5], x + 11 + messageWidth * 6, y + 5, 9, 0, 7, 14, 255);
				}
				else
				{
					HoDrawTexImage(BoxImage4[3], x, y + 5 + (16 * (m - 1)) + 14, 0, 0, 8, 16, 255);

					HoDrawTexImage(BoxImage4[5], x + 11 + messageWidth * 6, y + 5 + (16 * (m - 1)) + 14, 9, 0, 7, 16, 255);
				}
			}
		}



		for(int m = 0; m < messageWidth; m++)
		{

			if(tailFlag)
			{
				HoDrawTexImage(BoxImage3[1], x + 11 + 6 * m, y, 0, 0, 6, 5, 255);
				if(selected)
					HoDrawTexImage(BoxImage4[1], x + 11 + 6 * m, y, 0, 0, 6, 5, 255);

				if(m != (messageWidth / 2 - 1) && m != (messageWidth / 2))
				{
					HoDrawTexImage(BoxImage3[7], x + 11 + 6 * m, y + 5 + (16 * (messageHeight - 1)) + 14, 0, 3, 6, 5, 255);
					if(selected)
						HoDrawTexImage(BoxImage4[7], x + 11 + 6 * m, y + 5 + (16 * (messageHeight - 1)) + 14, 0, 3, 6, 5, 255);
				}


				if(m == messageWidth / 2 - 1)
				{

					HoDrawTexImage(BoxImage3[9], x + 11 + 6 * m, y + 5 + (16 * (messageHeight - 1)) + 14, 0, 3, 12, 13, 255);
					if(selected)
						HoDrawTexImage(BoxImage4[9], x + 11 + 6 * m, y + 5 + (16 * (messageHeight - 1)) + 14, 0, 3, 12, 13, 255);
				}
			}
			else
			{
				HoDrawTexImage(BoxImage3[1], x + 11 + 6 * m, y, 0, 0, 6, 5, 255);
				HoDrawTexImage(BoxImage3[7], x + 11 + 6 * m, y + 5 + (16 * (messageHeight - 1)) + 14, 0, 3, 6, 5, 255);

				if(selected)
				{
					HoDrawTexImage(BoxImage4[1], x + 11 + 6 * m, y, 0, 0, 6, 5, 255);
					HoDrawTexImage(BoxImage4[7], x + 11 + 6 * m, y + 5 + (16 * (messageHeight - 1)) + 14, 0, 3, 6, 5, 255);
				}
			}
		}
	}



	for(int n = 0; n < messageHeight; n++)
		for(int m = 0; m < messageWidth; m++)
		{
			if(n == 0)
			{
				HoDrawTexImage(BoxImage3[4], x + 11 + m * 6, y + 5, 0, 0, 6, 14, 255);
			}
			else
			{
				HoDrawTexImage(BoxImage3[4], x + 11 + m * 6, y + 5 + (n - 1) * 16 + 14, 0, 0, 6, 16, 255);
			}
		}
	renderDevice.EndScene();
}


#include <Wingdi.h>
int HoMessage::textarrange(char *teststr, bool clanm)
{
	int		len = 0;
	int		array1 = 0;
	int		array2 = 0;
	int		array3 = 0;
	BOOL	check = 0;

	ZeroMemory(textdata, sizeof(char) * 12 * 64);
	if(clanm)
	{
		textdata[0][0] = 0x20;
		textdata[0][1] = 0x20;
		textdata[0][2] = 0x20;
		textdata[0][3] = 0x20;
		array2 = 4;
	}
	len = (int)strlen(teststr);

	for(int i = 0; i < len; i++)
	{
		textdata[array1][array2] = teststr[i];
		if(array2 >= 30 || i == len - 1)
		{
			if(i != (len - 1) && CheckCode_2Byte(&teststr[i]) == 1 && teststr[i] == 0x20) array2 = -1;
			else if(i != (len - 1) && CheckCode_2Byte(&teststr[i + 1]) == 1 && teststr[i + 1] == 0x20) array2 = -1;
			else if(i != (len - 1) && CheckCode_2Byte(&teststr[i]) == 1 && teststr[i] != 0x20)
			{
				for(array3 = 0; array3 < 6; array3++)
				{
					check = 1;
					if(teststr[i - array3] == 0x20 && CheckCode_2Byte(&teststr[i - array3]) == 1) break;
					check = 0;
				}
				if(check)
				{
					memcpy(textdata[array1 + 1], teststr + (i - (array3 - 1)), array3);
					for(int z = 0; z < array3; z++) textdata[array1][array2 - z] = 0x20;
					array2 = (array3 - 1);
				}
				else
				{
					if(textdata[array1][array2] >= 65 && textdata[array1][array2] <= 90 ||
					   textdata[array1][array2] >= 97 && textdata[array1][array2] <= 122)
					{
						textdata[array1 + 1][0] = textdata[array1][array2];
						textdata[array1][array2] = '-';
						array2 = 0;
					}
					else array2 = -1;
				}
			}
			else if(i != (len - 1) && CheckCode_2Byte(&teststr[i]) == 2)
			{
				if(CheckCode_2Byte(&teststr[i + 1]) == 1 && teststr[i + 1] == 0x20) array2 = -1;
				else
				{
					for(array3 = 0; array3 < 6; array3++)
					{
						check = 1;
						if(teststr[i - array3] == 0x20 && CheckCode_2Byte(&teststr[i - array3]) == 1) break;
						check = 0;
					}
					if(check)
					{
						memcpy(textdata[array1 + 1], teststr + (i - (array3 - 1)), array3);
						for(int z = 0; z < array3; z++) textdata[array1][array2 - z] = 0x20;
						array2 = (array3 - 1);
					}
					else
					{
						if(textdata[array1][array2] >= 65 && textdata[array1][array2] <= 90 ||
						   textdata[array1][array2] >= 97 && textdata[array1][array2] <= 122)
						{
							textdata[array1 + 1][0] = textdata[array1][array2];
							textdata[array1][array2] = '-';
							array2 = 0;
						}
						else array2 = -1;
					}
				}
			}
			array1++;
		}
		array2++;
	}
	return array1;
}

void HoMessage::DrawClanMessage(int x, int y, char *message, int lineSize, DWORD color)
{

	int messageLen = strlen(message);

	int messageWidth = 0;
	int messageHeight = 1;

	if(lineSize != 0 && messageLen > lineSize)
	{
		messageHeight = messageLen / lineSize;
		if(messageHeight%lineSize)
			messageHeight += 1;

		messageWidth = lineSize;
	}
	else
		messageWidth = messageLen;

	if(messageWidth != 0)
		x -= messageWidth * 6 + 20;


	DrawClanMessageFrame(x, y, messageWidth, messageHeight);

	HDC hdc = NULL;
	//renderDevice.lpDDSBack->GetDC(&hdc);
	if(hFont != NULL)

		SelectObject(hdc, hFont);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, color);

#ifdef _LANGUAGE_ENGLISH
	if(lineSize > 10)
	{
		lineSize--;
		if(lineSize < messageWidth)
		{
			messageWidth--;
			lineSize++;
		}

	}
#endif
#ifdef _LANGUAGE_ARGENTINA
	if(lineSize > 10)
	{
		lineSize--;
		if(lineSize < messageWidth)
		{
			messageWidth--;
			lineSize++;
		}

	}
#endif

	char buffer[1024];
	if(lineSize != 0)
	{
		int start = 0;
		int end = 0;
		int lineCount = 0;

		for(int m = 0; m < messageHeight; m++)
		{
			memset(buffer, 0, sizeof(buffer));
			while(1)
			{
				if(message[end] == NULL)
					break;

				if(CheckCode_2Byte(&message[end]) == 2)
				{
					if((lineCount + 2) > messageWidth)
						break;
					lineCount += 2;
					end += 2;

				}
				else
				{
					if((lineCount + 1) > messageWidth)
						break;

					lineCount += 1;
					end += 1;

				}
			}
			memcpy(buffer, &message[start], end - start);

		#ifdef _LANGUAGE_ENGLISH
			if(message[end + 1] && message[end - 1] > ' ' && message[end] > ' ')
			{
				lstrcat(buffer, "-");
			}
			if(message[end + 1] == 0)
			{
				buffer[end - start] = message[end];
			}
		#endif
		#ifdef _LANGUAGE_ARGENTINA
			if(message[end + 1] && message[end - 1] > ' ' && message[end] > ' ')
			{
				lstrcat(buffer, "-");
			}
			if(message[end + 1] == 0)
			{
				buffer[end - start] = message[end];
			}
		#endif
			dsTextLineOut(hdc, x + 11, y + 13 + m * 14, buffer, lstrlen(buffer));

			if(message[end] != NULL)
			{
				start = end;
				lineCount = 0;
			}
			else
				break;
		}
	}
	else
		dsTextLineOut(hdc, x + 11, y + 13, message, lstrlen(message));

	//renderDevice.lpDDSBack->ReleaseDC(hdc);

}
void HoMessage::DrawCharacterMessage(int x, int y, char *message, int lineSize, DIRECTDRAWSURFACE clanMark, char *clanName, DWORD color1, BOOL selected, int bellaMarkIndex){}

void HoMessage::DrawShopSellMessage(int x, int y, char *message, int lineSize, DIRECTDRAWSURFACE clanMark, DWORD color1, BOOL selected){}


void HoMessage::DrawCharacterMessageFrame1(int x, int y, int messageWidth, int messageHeight, int linecount, bool tailFlag, BOOL selected){}



void HoMessage::DrawShopByeMessageFrame1(int x, int y, int messageWidth, int messageHeight, int linecount, bool tailFlag, BOOL selected){}


void HoMessage::DrawShopSellMessageFrame1(int x, int y, int messageWidth, int messageHeight, int linecount, bool tailFlag, BOOL selected){}

void HoMessage::DrawShopSellMessageFrame(int x, int y, int messageWidth, int messageHeight, bool tailFlag, BOOL selected){}

void HoMessage::DrawShopByeMessage(int x, int y, char *message, int lineSize, DIRECTDRAWSURFACE clanMark, DWORD color1, BOOL selected){}

void HoMessage::DrawShopByeMessageFrame(int x, int y, int messageWidth, int messageHeight, bool tailFlag, BOOL selected){}

void HoMessage::Draw(int x, int y, char *message, int lineSize, int addLine, int boxAttrib){}

int DrawCharacterShopSellMessage(int x, int y, char*message, int lineSize, DIRECTDRAWSURFACE clanMark, DWORD charColor, BOOL selected){ return TRUE; }

int DrawCharacterShopByeMessage(int x, int y, char*message, int lineSize, DIRECTDRAWSURFACE clanMark, DWORD charColor, BOOL selected){ return TRUE; }

int DrawCharacterMessage(int x, int y, char *message, int lineSize, DIRECTDRAWSURFACE clanMark, char *clanName, DWORD color1, BOOL selected, int bellaMarkIndex) { return TRUE; }

int DrawTwoLineMessage(int x, int y, char *messageOne, char *messageTwo, DWORD color1, DWORD color2, DIRECTDRAWSURFACE clanMark, BOOL selected, int bellaMarkIndex){ return TRUE; }


int DrawClanMessage(int x, int y, char *message, int lineSize, DWORD color){ return TRUE; }



int DrawMessage(int x, int y, char *message, int lineSize, int boxAttrib){ return TRUE; }

BOOL TextGetDC()
{
	//renderDevice.lpDDSBack->GetDC(&ChatMessage.TextDC);
#ifndef dsTextLineOut_ENGLISH
	SetBkMode(ChatMessage.TextDC, TRANSPARENT);
#endif

	return TRUE;
}

BOOL TextReleaseDC()
{

#ifndef dsTextLineOut_ENGLISH
	if(ChatMessage.OldFont)
		SelectObject(ChatMessage.TextDC, ChatMessage.OldFont);
	//renderDevice.lpDDSBack->ReleaseDC(ChatMessage.TextDC);
#endif
	return TRUE;
}

BOOL TextSelectObject(HFONT font)
{
	if(font != NULL)
	{
		ChatMessage.OldFont = NULL;
		ChatMessage.OldFont = (HFONT)SelectObject(ChatMessage.TextDC, font);
	}

#ifdef dsTextLineOut_ENGLISH
	TEXTMETRIC textMetric;
	GetTextMetrics(ChatMessage.TextDC, &textMetric);
	EngSetFont(textMetric.tmMaxCharWidth);

	if(ChatMessage.OldFont)
		SelectObject(ChatMessage.TextDC, ChatMessage.OldFont);
	//lpDDSBack->ReleaseDC(ChatMessage.TextDC);


#endif

	return TRUE;
}
BOOL TextSetColor(COLORREF color)
{
#ifndef dsTextLineOut_ENGLISH
	SetTextColor(ChatMessage.TextDC, color);
#endif

#ifdef  dsTextLineOut_ENGLISH
	EngSetColor(color);
#endif
	return TRUE;
}

BOOL dsTextLineOut(int x, int y, char *lpszString, int nCount)
{
#ifndef dsTextLineOut_ENGLISH
	dsTextLineOut(ChatMessage.TextDC, x, y, lpszString, nCount);
#endif

#ifdef	dsTextLineOut_ENGLISH
	EngdsTextLineOut(x, y, lpszString, nCount);
#endif
	return TRUE;
}

void	SetMessageFrameSelect(BOOL flag)
{
	ChatMessage.SetMessageFrameSelect(flag);
}

int InitMessageBox()
{
	ChatMessage.Init();
	return TRUE;
}

BOOL	HoButton::ButtonUseFlag = FALSE;
HoButton::HoButton()
{
	ButtonInDownFlag = FALSE;
	State = BUTTON_STATE_NONE;
	SizeWidth = 64;
	SizeHeight = 32;

}

HoButton::~HoButton()
{

}

void HoButton::Init(char *stateFirstIamge, char *stateThirdImage)
{
	StateFirstImage = CreateTextureMaterial(stateFirstIamge, 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

}

void HoButton::InitCrashRect(int left, int top, int right, int bottom)
{
	CrashRect.left = left;
	CrashRect.top = top;
	CrashRect.right = right;
	CrashRect.bottom = bottom;
}

void HoButton::Init(char *stateFirstImage, int sizeWidth, int sizeHeight)
{
	StateFirstImage = CreateTextureMaterial(stateFirstImage, 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	SizeWidth = sizeWidth;
	SizeHeight = sizeHeight;

	CrashRect.left = 0;
	CrashRect.top = 0;
	CrashRect.right = SizeWidth;
	CrashRect.bottom = SizeHeight;
}


BOOL HoButton::Draw(int x, int y, int BlendFlag){ return TRUE; }

BOOL HoButton::Main(int mouseX, int mouseY, int downFlag)
{

	if(mouseX > (PosX + CrashRect.left) && mouseX < PosX + (CrashRect.right)
	   && mouseY >(PosY + CrashRect.top) && mouseY < PosY + (CrashRect.bottom))
	{
		if(ButtonUseFlag == FALSE)
		{
			State = BUTTON_STATE_IN;

			if(downFlag)
			{
				ButtonUseFlag = TRUE;
				ButtonInDownFlag = TRUE;
				State = BUTTON_STATE_DOWN;
			}


			if(ButtonInDownFlag && downFlag == FALSE)
			{
				ButtonInDownFlag = FALSE;
				State = BUTTON_STATE_NONE;
				return TRUE;
			}
		}
	}
	else
	{
		if(ButtonInDownFlag == TRUE)
			State = BUTTON_STATE_IN;
		else
			State = BUTTON_STATE_NONE;

		if(downFlag == FALSE)
			ButtonInDownFlag = FALSE;
	}

	if(downFlag == FALSE)
		ButtonUseFlag = FALSE;
	return FALSE;
}

HoMessageBox::HoMessageBox()
{
	Flag = FALSE;
}

HoMessageBox::~HoMessageBox()
{

}



BOOL HoMessageBox::Main(int mouseX, int mouseY, int downFlag)
{
	if(Flag)
	{
		if(Button[0].Main(mouseX, mouseY, downFlag))
		{
			Flag = FALSE;
			return 1;
		}

		if(Button[1].Main(mouseX, mouseY, downFlag))
		{
			Flag = FALSE;
			return 2;
		}
	}
	return FALSE;
}


BOOL HoMessageBox::Draw(int x, int y, char *message, int Color)
{
	if(Flag)
	{
		Message.DrawMessageBox(x, y, message, BOX_ONE, Color);
		int messageWidth = Message.GetWidth();
		x = Message.PosX;
		y = Message.PosY;

		renderDevice.BeginScene();

		Button[0].Draw(x + messageWidth / 2 - 54 - 13, 40 + y);
		Button[1].Draw(x + messageWidth / 2 + 7, 40 + y);

		renderDevice.EndScene();
	}
	return TRUE;
}

void HoMessageBox::Init()
{
	Button[0].Init("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\Bt_ok.tga", 64, 32);
	Button[1].Init("Assets\\GUI\\Opening\\Select\\UI\\CharSelect\\Bt_cancel.tga", 64, 32);
	Message.Init();
}
