

#include "sinLinkHeader.h"



sinSTRING::sinSTRING(void)
{
	m_aString = new char;

}
sinSTRING::sinSTRING(sinSTRING &rString)
{
	if(rString.GetLength() > 0)
	{
		m_aString = new char[rString.GetLength() + 1];
		strcpy(m_aString, rString.GetString());
	}
	else m_aString[0] = '\0';

}
sinSTRING::sinSTRING(char *pString)
{
	if(pString)
	{
		m_aString = new char[lstrlen(pString) + 1];
		strcpy(m_aString, pString);

	}
	else m_aString[0] = '\0';

}

sinSTRING::~sinSTRING(void)
{
	m_aString[0] = '\0';
}


sinSTRING & sinSTRING::operator = (sinSTRING & rString)
{
	if(rString.GetLength() > 0)
		strcpy(m_aString, rString.GetString());
	else m_aString[0] = '\0';
	return *this;
}
sinSTRING & sinSTRING::operator = (char *pString)
{
	if(pString)
		strcpy(m_aString, pString);
	else m_aString[0] = '\0';
	return *this;
}

bool sinSTRING::operator == (sinSTRING &rString)
{
	if(strcmp(rString.GetString(), m_aString) == 0)return TRUE;
	else return FALSE;

}
bool sinSTRING::operator == (char *pString)
{
	if(strcmp(pString, m_aString) == 0)return TRUE;
	else return FALSE;
}
bool sinSTRING::operator != (sinSTRING &rString)
{
	if(strcmp(rString.GetString(), m_aString) != 0)return TRUE;
	else return FALSE;

}

bool sinSTRING::operator != (char *pString)
{
	if(strcmp(pString, m_aString) != 0)return TRUE;
	else return FALSE;
}


char *sinSTRING::GetString(void)
{
	return m_aString;
}
int sinSTRING::GetLength(void)
{
	return strlen(m_aString);
}


int halpRelease(DIRECTDRAWSURFACE lpTemp)
{
	if(!lpTemp) return FALSE;

	if(lpTemp)
	{
		lpTemp->Release();
		lpTemp = 0;
	}
	return TRUE;
}

int haSearchString(char *StrBuffer, char KeyBuffer)
{
	int  TotalNum = 0;

	TotalNum = lstrlen(StrBuffer);

	for(int i = 0; i < TotalNum; i++)
	{
		if(StrBuffer[i] == KeyBuffer)
		{
			return i + 1;
		}
	}
	return 0;
}

int haStringCenter(int PosiX, char *strbuff)
{

	int len = 0;
	int rPosiX = 0;
	len = lstrlen(strbuff);


	if(len % 2)
		rPosiX += 4;

	if(PosiX % 2)
		rPosiX += 1;


	rPosiX = PosiX / 2 - (len / 2 * 8);


	return rPosiX;
}
