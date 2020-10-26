#include "jts.h"


int GetTXT(char* FileName, char* SaveFile)
{
	FILE* rFile = NULL;
	int nStrlen = 0;

	rFile = fopen(FileName, "r");

	if(!rFile)
	{
		return -1;
	}
	if(SaveFile[0] != 0)
	{
		memset(SaveFile, 0, sizeof(SaveFile));
	}
	fread(SaveFile, MAXTXTFILE, 1, rFile);
	fclose(rFile);
	nStrlen = strlen(SaveFile);
	if(nStrlen > MAXTXTFILE)
	{
		return 0;
	}

	return 1;
}




int CheckJTS(char* SaveFile, int num)
{
	if((((*(SaveFile + num) & 0xff) >= 129) && ((*(SaveFile + num) & 0xff) <= 159)) || (((*(SaveFile + num) * 0xff) >= 224) && ((*(SaveFile + num) & 0xff) <= 239)))
	{
		if((((*(SaveFile + num + 1) & 0xff) >= 64) && ((*(SaveFile + num + 1) & 0xff) <= 126)) || (((*(SaveFile + num + 1) & 0xff) >= 128) && ((*(SaveFile + num + 1) & 0xff) <= 252)))
		{
			return 2;
		}
	}
	if((((*(SaveFile + num) & 0xff) >= 0x21) && ((*(SaveFile + num) & 0xff) <= 0x7E)) || ((*(SaveFile + num) >= 0xFFFFFFA1) && ((*(SaveFile + num) & 0xff) <= 0xDF)))
	{
		return 1;
	}

	return -1;
}





char* GetCharacterJTS(char* SaveFile, char* SaveCh, int num)
{
	int nCheck = 0;
	int nNum = 0;
	int nCount = 0;

	while(1)
	{
		if(nCount + 1 == num)
		{
			break;
		}
		nCheck = CheckJTS(SaveFile, nNum);
		if(nCheck == 2)
		{
			nNum += 2;
		}
		else
		{
			nNum += 1;
		}

		nCount++;
	}

	nCheck = CheckJTS(SaveFile, nNum);
	if(SaveCh[0] != 0)
	{
		memset(SaveCh, 0, sizeof(SaveCh));
	}

	if(nCheck == 2)
	{
		SaveCh[0] = SaveFile[nNum];
		SaveCh[1] = SaveFile[nNum + 1];
	}
	else
	{
		SaveCh[0] = SaveFile[nNum];
	}

	return SaveCh;
}



int CheckJTS_ptr(char* SaveFile, int pos)
{
	if((((*(SaveFile + pos) & 0xff) >= 0x21) && ((*(SaveFile + pos) & 0xff) <= 0x7E))
	   || (((*(SaveFile + pos) & 0xff) >= 0xA1) && ((*(SaveFile + pos) & 0xff) <= 0xDF)))
	{
		return 1;
	}

	if(((*(SaveFile + pos) >= 129) && (*(SaveFile + pos) <= 159)) || ((*(SaveFile + pos) >= 224) && (*(SaveFile + pos) <= 239)) || ((*(SaveFile + pos) >= 0xFFFFFF81) && (*(SaveFile + pos) <= 0xFFFFFF9F)) || ((*(SaveFile + pos) >= 0XFFFFFFE0) && (*(SaveFile + pos) <= 0XFFFFFFEF)))
	{
		return 2;
	}

	if(((*(SaveFile + pos - 1) >= 129) && (*(SaveFile + pos - 1) <= 159)) || ((*(SaveFile + pos - 1) >= 224) && (*(SaveFile + pos - 1) <= 239)) || ((*(SaveFile + pos - 1) >= 0xFFFFFF81) && (*(SaveFile + pos - 1) <= 0xFFFFFF9F)) || ((*(SaveFile + pos - 1) >= 0XFFFFFFE0) && (*(SaveFile + pos - 1) <= 0XFFFFFFEF)))
	{
		return 3;
	}

	if(*(SaveFile + pos) == 0x0D)
	{
		return 4;
	}

	if(*(SaveFile + pos) == 0x0A)
	{
		return 5;
	}

	return -1;
}


int CheckTHAI_ptr(char* SaveFile, int pos)
{
	if(((*(SaveFile + pos) & 0xff) >= 0x21) && ((*(SaveFile + pos) & 0xff) <= 0x7E))
	{
		return 1;
	}


	if(((((*(SaveFile + pos + 1) & 0xff) >= 0xd4) && ((*(SaveFile + pos + 1) & 0xff) <= 0xff))
		|| (((*(SaveFile + pos + 1) & 0xff) >= 0) && ((*(SaveFile + pos + 1) & 0xff) <= 0x4a)))
	   && ((*(SaveFile + pos) == 1) && (*(SaveFile + pos) == 2)))
	{
		return 2;
	}


	if(*(SaveFile + pos) == 0x0D)
	{
		return 4;
	}

	if(*(SaveFile + pos) == 0x0A)
	{
		return 5;
	}

	return -1;
}




char* GetCharacter_ptr(char* SaveFile, int pos)
{
	int nReturnValue = 0;
	nReturnValue = CheckJTS_ptr(SaveFile, pos);
	switch(nReturnValue)
	{
		case 1:
		return (SaveFile + pos);
		case 2:
		return (SaveFile + pos - 1);
		case 3:
		return (SaveFile + pos);
		case 4:
		return (SaveFile + pos - 1);
		case 5:
		return (SaveFile + pos - 2);
		case -1:
		return 0;
	}
	return 0;
}


int GetPointerPos(char* SaveFile, int pos)
{
	int nPos;
	int nReturnValue = 0;

	nReturnValue = CheckJTS_ptr(SaveFile, pos);

	switch(nReturnValue)
	{
		case 1:
		nPos = pos;
		break;
		case 2:
		nPos = pos - 1;
		break;
		case 3:
		nPos = pos;
		break;
		case 4:
		nPos = pos - 1;
		break;
		case 5:
		nPos = pos - 2;
		case -1:
		return 0;
	}

	return nPos;
}



int IsJTS(char* SaveFile)
{
	int nCount = 0;
	int nStrlen = 0;
	int nReturnValue = -1;
	BOOL bJTS = FALSE;
	nStrlen = strlen(SaveFile);

	while(1)
	{
		if(SaveFile[nCount] == 0)
		{
			if(nStrlen == nCount)
			{
				bJTS = TRUE;
				nReturnValue = -1;
				break;
			}

		}
		if((((*(SaveFile + nCount) & 0xff) >= 0x21) && ((*(SaveFile + nCount) & 0xff) <= 0x7E))
		   || (((*(SaveFile + nCount) & 0xff) >= 0xA1) && ((*(SaveFile + nCount) & 0xff) <= 0xDF)))
		{
			nCount += 1;
		}
		else if((((*(SaveFile + nCount) & 0xff) >= 0x81) && ((*(SaveFile + nCount) & 0xff) <= 0x9F))
				|| (((*(SaveFile + nCount) & 0xff) >= 0xE0) && ((*(SaveFile + nCount) & 0xff) <= 0xEF)))
		{
			if((((*(SaveFile + nCount) & 0xff) >= 0x40) && ((*(SaveFile + nCount) & 0xff) <= 0x7E))
			   || (((*(SaveFile + nCount) & 0xff) >= 0x80) && ((*(SaveFile + nCount) & 0xff) <= 0xFC)))
			{
				nCount += 2;
			}
			else
			{
				bJTS = FALSE;
				nReturnValue = nCount;
				break;
			}
		}
		else
		{
			bJTS = FALSE;
			nReturnValue = nCount;
			break;
		}
	}
	if(!bJTS)
	{
		return nReturnValue;
	}

	return nReturnValue;
}

int IsENG(char* SaveFile)
{
	int nCount = 0;
	int nStrlen = 0;
	int nReturnValue = -1;
	BOOL bJTS = FALSE;
	nStrlen = strlen(SaveFile);

	while(1)
	{
		if(SaveFile[nCount] == 0)
		{
			if(nStrlen == nCount)
			{
				bJTS = TRUE;
				nReturnValue = -1;
				break;
			}

		}
		if((((*(SaveFile + nCount) & 0xff) >= 0x30) && ((*(SaveFile + nCount) & 0xff) <= 0x39)) ||
			(((*(SaveFile + nCount) & 0xff) >= 0x41) && ((*(SaveFile + nCount) & 0xff) <= 0x5a)) ||
		   (((*(SaveFile + nCount) & 0xff) >= 0x61) && ((*(SaveFile + nCount) & 0xff) <= 0x7a)) ||
		   ((*(SaveFile + nCount) & 0xff) == 0x28) ||
		   ((*(SaveFile + nCount) & 0xff) == 0x29) ||
		   ((*(SaveFile + nCount) & 0xff) == 0x5b) ||
		   ((*(SaveFile + nCount) & 0xff) == 0x5d) ||
		   ((*(SaveFile + nCount) & 0xff) == 0x5f) ||
		   ((*(SaveFile + nCount) & 0xff) == 0x2d))
		{
			nCount += 1;
		}
		else
		{
			bJTS = FALSE;
			nReturnValue = nCount;
			break;
		}
	}
	if(!bJTS)
	{
		return nReturnValue;
	}
	return nReturnValue;
}


int IsTHAI(char* SaveFile)
{
	int nCount = 0;
	int nStrlen = 0;
	int nReturnValue = -1;
	BOOL bJTS = FALSE;
	nStrlen = strlen(SaveFile);

	if(SaveFile[0] == 0) return -1;
	while(1)
	{

		if((((*(SaveFile + nCount) & 0xff) >= 0x30) && ((*(SaveFile + nCount) & 0xff) >= 0x39)) ||
			(((*(SaveFile + nCount) & 0xff) >= 0x41) && ((*(SaveFile + nCount) & 0xff) <= 0x5a)) ||
		   (((*(SaveFile + nCount) & 0xff) >= 0x61) && ((*(SaveFile + nCount) & 0xff) <= 0x7a)))

		{
			nCount += 1;
		}
		else if((((*(SaveFile + nCount) & 0xff) == 0x01) || ((*(SaveFile + nCount) & 0xff) == 0x02)))
		{
			if(((((*(SaveFile + nCount + 1) & 0xff) >= 0xd4) && ((*(SaveFile + nCount + 1) & 0xff) <= 0xff))
				|| (((*(SaveFile + nCount + 1) & 0xff) >= 0) && ((*(SaveFile + nCount + 1) & 0xff) <= 0x4a))))
			{
				nCount += 2;
			}
			else
			{
				bJTS = FALSE;
				nReturnValue = nCount;
				break;
			}
		}
		else
		{
			bJTS = FALSE;
			nReturnValue = nCount;
			break;
		}
	}
	if(!bJTS)
	{
		return -1;
	}

	return nReturnValue;
}


int Check_T(char* SaveFile, int num)
{
	if(((*(SaveFile + num) & 0xff) < 0x80))
	{
		return 1;
	}
	else
	{
		if((((*(SaveFile + num) & 0xff) >= 0xA1) && ((*(SaveFile + num) & 0xff) <= 0xF9)))
		{
			if((((*(SaveFile + num + 1) & 0xff) >= 0x40) && ((*(SaveFile + num + 1) & 0xff) <= 0x7E)) || (((*(SaveFile + num + 1) & 0xff) >= 0xA1) && ((*(SaveFile + num + 1) & 0xff) <= 0xFE)))
			{
				return 2;
			}
		}
	}

	return -1;
}



void GetCharacter_T(char* SaveFile, char* SaveCh, int num)
{
	int nCheck = 0;
	int nNum = 0;
	int nCount = 0;

	while(1)
	{
		if(nCount + 1 == num)
		{
			break;
		}
		nCheck = Check_T(SaveFile, nNum);
		if(nCheck == 2)
		{
			nNum += 2;
		}
		else if((nCheck == 1))
		{
			nNum += 1;
		}
		nCount++;
	}

	nCheck = Check_T(SaveFile, nNum);
	if(SaveCh[0] != 0)
	{
		memset(SaveCh, 0, sizeof(SaveCh));
	}

	if(nCheck == 2)
	{
		SaveCh[0] = SaveFile[nNum];
		SaveCh[1] = SaveFile[nNum + 1];
	}
	else if((nCheck == 1))
	{
		SaveCh[0] = SaveFile[nNum];
	}
}


int Check_ptr_T(char* SaveFile, int pos)
{
	if(((*(SaveFile + pos) & 0xff) < 0x80))
	{
		return 1;
	}

	if((((*(SaveFile + pos) & 0xff) >= 0xA1) && ((*(SaveFile + pos) & 0xff) <= 0xF9)))
	{
		return 2;
	}

	if((((*(SaveFile + pos - 1) & 0xff) >= 0xA1) && ((*(SaveFile + pos - 1) & 0xff) <= 0xF9)))
	{
		return 3;
	}

	if(*(SaveFile + pos) == 0x0D)
	{
		return 4;
	}

	if(*(SaveFile + pos) == 0x0A)
	{
		return 5;
	}

	return -1;
}



char* GetCharacter_ptr_T(char* SaveFile, int pos)
{
	int nReturnValue = 0;
	nReturnValue = CheckJTS_ptr(SaveFile, pos);
	switch(nReturnValue)
	{
		case 1:
		return (SaveFile + pos);
		case 2:
		return (SaveFile + pos - 1);
		case 3:
		return (SaveFile + pos);
		case 4:
		return (SaveFile + pos - 1);
		case 5:
		return (SaveFile + pos - 2);
		case -1:
		return 0;
	}
	return 0;
}


int GetPointerPos_T(char* SaveFile, int pos)
{
	int nPos;
	int nReturnValue = 0;

	nReturnValue = CheckJTS_ptr(SaveFile, pos);

	switch(nReturnValue)
	{
		case 1:
		nPos = pos;
		break;
		case 2:
		nPos = pos - 1;
		break;
		case 3:
		nPos = pos;
		break;
		case 4:
		nPos = pos - 1;
		break;
		case 5:
		nPos = pos - 2;
		case -1:
		return 0;
	}

	return nPos;
}

int IsTaiwan(char* SaveFile)
{
	int nCount = 0;
	int nStrlen = 0;
	int nReturnValue = -1;
	BOOL bTaiwan = FALSE;
	nStrlen = strlen(SaveFile);

	while(1)
	{
		if(SaveFile[nCount] == 0)
		{
			if(nStrlen == nCount)
			{
				bTaiwan = TRUE;
				nReturnValue = -1;
				break;
			}
			else
			{
				bTaiwan = FALSE;
				break;
			}
		}
		if(((*(SaveFile + nCount) & 0xff) < 0x80))
		{
			nCount += 1;
		}
		else if((((*(SaveFile + nCount) & 0xff) >= 0xA1) && ((*(SaveFile + nCount) & 0xff) <= 0xF9)))
		{
			if((((*(SaveFile + nCount + 1) & 0xff) >= 0x40) && ((*(SaveFile + nCount + 1) & 0xff) <= 0x7E))
			   || (((*(SaveFile + nCount + 1) & 0xff) >= 0xA1) && ((*(SaveFile + nCount + 1) & 0xff) <= 0xFE)))
			{
				nCount += 2;
			}
			else
			{
				bTaiwan = FALSE;
				nReturnValue = nCount;
				break;
			}
		}
		else
		{
			bTaiwan = FALSE;
			nReturnValue = nCount;
			break;
		}
	}
	if(!bTaiwan)
	{
		return nReturnValue;
	}

	return nReturnValue;
}

