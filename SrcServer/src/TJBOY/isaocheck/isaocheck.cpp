#define __ISAOCHECK_CPP__
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <Winsock.h>
#include <wininet.h>
#include <time.h>

#include "../clanmenu/tjclanDEF.h"

#ifdef USE_PROSTONTALE 
#include "..\\..\\sinbaram\\SinLinkHeader.h"
#include "..\\..\\HoBaram\\HoLinkHeader.h"
#include "Language\language.h"
#include "..\\..\\HoBaram\\HoTextFile.h"
#include "..\\clanmenu\\cE_CViewClanInfo.h"
#endif


#include "..\\clanmenu\\BMPsmooth.h"
#include "..\\clanmenu\\tjclan.h"
#include "..\\clanmenu\\cE_CViewClanInfo.h"

#include <wininet.h>
#pragma comment(lib,"wininet.lib")



#include "isaocheck.h"

extern void fd(char *fmt, ...);
extern void fd2(char *fmt, ...);

#define BUF_LEN 4096

extern char szConnServerName[16];
extern int nClanTicket;

extern BOOL g_bDebugOption;
void debug_fd2(char *fmt, ...)
{
	if(!g_bDebugOption)
		return;

	char buff[4096];

	va_list args;

	va_start(args, fmt);
	vsprintf_s(buff, sizeof(buff), fmt, args);
	va_end(args);

	strcat_s(buff, sizeof(buff), "\r\n");


	int errorMSGdr = 0;

	if(strlen(buff) > 2048)
	{
		buff[1024] = 0;
		errorMSGdr = 1;

		HANDLE hFile;
		DWORD dwAcess = 0;
		hFile = CreateFile("DDD2.txt", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
						   NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		if(hFile != INVALID_HANDLE_VALUE)
		{
			SetFilePointer(hFile, 0, NULL, FILE_END);


			int chk = WriteFile(hFile, buff, lstrlen(buff), &dwAcess, NULL);



			if(errorMSGdr == 1)
			{
				char msg[256] = "..\n메시지가 너무길어서 잘랐음";
				WriteFile(hFile, msg, lstrlen(msg), &dwAcess, NULL);
			}



			CloseHandle(hFile);
		}
		return;
	}

	HANDLE hFile;
	DWORD dwAcess = 0;
	hFile = CreateFile("DDD2.txt", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
					   NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile != INVALID_HANDLE_VALUE)
	{
		SetFilePointer(hFile, 0, NULL, FILE_END);

		int chk = WriteFile(hFile, buff, lstrlen(buff), &dwAcess, NULL);


		if(errorMSGdr == 1)
		{
			char msg[256] = "\n메시지가 너무길어서 잘랐음";
			WriteFile(hFile, msg, lstrlen(msg), &dwAcess, NULL);
		}


		CloseHandle(hFile);
	}
}



BOOL GetHttpRequest(LPSTR httpname, LPSTR Request, DWORD MaxBuffer, int *len)
{
	char szSizeBuffer[32];
	DWORD dwLengthSizeBuffer = sizeof(szSizeBuffer);
	DWORD dwFileSize = 0;
	DWORD dwBytesRead = 0;
	BOOL bSuccessful = FALSE;


	HINTERNET m_Session = NULL;
	m_Session = InternetOpen("AppName",
							 INTERNET_OPEN_TYPE_PRECONFIG,

							 NULL,

							 NULL,

							 0);
	HINTERNET hHttpFile = NULL;
	hHttpFile = InternetOpenUrl(m_Session, (const char *)httpname, NULL,
								0, 0, 0);
	if(hHttpFile)
	{
		BOOL bQuery = HttpQueryInfo(hHttpFile, HTTP_QUERY_CONTENT_LENGTH, szSizeBuffer,
									&dwLengthSizeBuffer, NULL);

		if(bQuery == TRUE)
		{
			dwFileSize = atol(szSizeBuffer);

			dwFileSize > MaxBuffer ? dwFileSize = MaxBuffer : dwFileSize = dwFileSize;

			BOOL bRead = InternetReadFile(hHttpFile, Request, dwFileSize, &dwBytesRead);
			if(bRead)
			{
				bSuccessful = TRUE;
				*len = dwBytesRead;


			}
			InternetCloseHandle(hHttpFile);
		}
	}
	if(hHttpFile) InternetCloseHandle(hHttpFile);
	if(m_Session) InternetCloseHandle(m_Session);
	return bSuccessful;
}



ISAOCHECK::ISAOCHECK()
{

	HSsu = 0;
	for(int i = 0; i < 30; i++)
		fileDATA_HS[i] = NULL;
}

ISAOCHECK::~ISAOCHECK()
{
}

void ISAOCHECK::init()
{
	iCheckFlag = 0;
	hostPORT = 0;
}

void ISAOCHECK::init_HostName_Port(char *hostname, int port)
{
	if(hostname == NULL) return;

	hostPORT = port;
	ZeroMemory(hostName, sizeof(char) * 64);



	strcpy_s(hostName, sizeof(hostName), hostname);

}

void ISAOCHECK::init_HostName_Port1(char *hostname, int port)
{
	if(hostname == NULL) return;

	hostPORT1 = port;
	ZeroMemory(hostName1, sizeof(char) * 64);
	strcpy_s(hostName1, sizeof(hostName1), hostname);
}

void ISAOCHECK::init(int iCheckON, int iTimeOUT)
{
	iCheckFlag = iCheckON;
	iTimeOut = iTimeOUT;
}

void ISAOCHECK::close()
{
}


void ISAOCHECK::main()
{

}



int ISAOCHECK::connect_WEBdb(char *szWriteBuffer, char *szReadBuffer)
{
	char szSizeBuffer[32];
	DWORD dwLengthSizeBuffer = sizeof(szSizeBuffer);
	DWORD dwFileSize = 0;
	DWORD dwBytesRead = 0;

	int iRet = ISAO_ERR_WINSOCK_NOERR;

	ZeroMemory(szReadBuffer, BUF_LEN);


	HINTERNET m_Session = NULL;

	m_Session = InternetOpen("AppName",
							 INTERNET_OPEN_TYPE_PRECONFIG,

							 NULL,

							 NULL,

							 0);
	if(!m_Session)
	{
		iRet = ISAO_ERR_TCP_CONNECT;
		return iRet;
	}
	HINTERNET hHttpFile = NULL;
	hHttpFile = InternetOpenUrl(m_Session, (const char *)szWriteBuffer, NULL,
								0, 0, 0);
	if(hHttpFile)
	{
		BOOL bQuery = HttpQueryInfo(hHttpFile, HTTP_QUERY_CONTENT_LENGTH, szSizeBuffer,
									&dwLengthSizeBuffer, NULL);

		if(bQuery == TRUE)
		{
			dwFileSize = atol(szSizeBuffer);
			dwFileSize > BUF_LEN ? dwFileSize = BUF_LEN :
				dwFileSize = dwFileSize;

			BOOL bRead = InternetReadFile(hHttpFile, szReadBuffer, dwFileSize, &dwBytesRead);
			if(bRead)
			{

				if((bRead == TRUE) && (dwFileSize != dwBytesRead))
				{
					iRet = ISAO_ERR_RECONNECT;
				}


			}
			else iRet = ISAO_ERR_RECONNECT;
			InternetCloseHandle(hHttpFile);
		}
	}
	else
	{
		iRet = ISAO_ERR_TCP_CONNECT;
	}
	if(hHttpFile) InternetCloseHandle(hHttpFile);
	if(m_Session) InternetCloseHandle(m_Session);
	return iRet;
}

int ISAOCHECK::connect_WEBdb_1(char *szWriteBuffer, char *szReadBuffer)
{
	char szSizeBuffer[32];
	DWORD dwLengthSizeBuffer = sizeof(szSizeBuffer);
	DWORD dwFileSize = 0;
	DWORD dwBytesRead = 0;
	int iRet = ISAO_ERR_WINSOCK_NOERR;

	ZeroMemory(szReadBuffer, BUF_LEN);


	HINTERNET m_Session = NULL;
	m_Session = InternetOpen("AppName",
							 INTERNET_OPEN_TYPE_PRECONFIG,

							 NULL,

							 NULL,

							 0);
	if(!m_Session)
	{
		iRet = ISAO_ERR_TCP_CONNECT;
		return iRet;
	}
	HINTERNET hHttpFile = NULL;
	hHttpFile = InternetOpenUrl(m_Session, (const char *)szWriteBuffer, NULL,
								0, 0, 0);
	if(hHttpFile)
	{
		BOOL bQuery = HttpQueryInfo(hHttpFile, HTTP_QUERY_CONTENT_LENGTH, szSizeBuffer,
									&dwLengthSizeBuffer, NULL);

		if(bQuery == TRUE)
		{
			dwFileSize = atol(szSizeBuffer);
			dwFileSize > BUF_LEN ? dwFileSize = BUF_LEN :
				dwFileSize = dwFileSize;

			BOOL bRead = InternetReadFile(hHttpFile, szReadBuffer, dwFileSize, &dwBytesRead);
			if(bRead)
			{
				if((bRead == TRUE) && (dwFileSize != dwBytesRead))
				{
					iRet = ISAO_ERR_RECONNECT;
				}

			}
			else iRet = ISAO_ERR_RECONNECT;
			InternetCloseHandle(hHttpFile);
		}
	}
	else
	{
		iRet = ISAO_ERR_TCP_CONNECT;
		return iRet;
	}
	if(hHttpFile) InternetCloseHandle(hHttpFile);
	if(m_Session) InternetCloseHandle(m_Session);
	return iRet;
}



int ISAOCHECK::connect_WEBdb_BINARY(char *szWriteBuffer, char *szReadBuffer, int *dataSize)
{
	struct timeval tmv;
	struct sockaddr_in server;
	char Value = '\0';
	char Msg[1024] = "";
	SOCKET Fd;

	int iLen;
	int iRet = ISAO_ERR_WINSOCK_NOERR;
	int iSelectRet;

	fd_set fdset;




	WORD   wSocketVersion;
	WSADATA  wsaData;
	int   iError;

	wSocketVersion = MAKEWORD(1, 1);
	iError = WSAStartup(wSocketVersion, &wsaData);
	if(iError != 0)
	{
		return ISAO_ERR_WINSOCK_START;
	}
	if(HIBYTE(wsaData.wVersion) != 1 || LOBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return ISAO_ERR_WINSOCK_VERSION;
	}

	Fd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(hostPORT1);



	struct hostent* ClanHostName = gethostbyname(hostName1);
	memcpy(&server.sin_addr.s_addr, ClanHostName->h_addr_list[0], ClanHostName->h_length);


	if(connect(Fd, (struct sockaddr *)&server, sizeof(server)) == -1)
	{
		return ISAO_ERR_TCP_CONNECT;
	}

	send(Fd, szWriteBuffer, strlen(szWriteBuffer) + 1, 0);

	tmv.tv_sec = iTimeOut;
	tmv.tv_usec = 0;
	FD_ZERO(&fdset);
	FD_SET(Fd, &fdset);
	iSelectRet = select(Fd + 1, &fdset, (fd_set*)NULL, (fd_set*)NULL, &tmv);

	if(iSelectRet > 0 && FD_ISSET(Fd, &fdset))
	{

	}
	else
	{
		iRet = ISAO_ERR_SSL_TIMEOUT;
		goto IsaoCheck_Free;
	}


	time_t startTime, endTime;
	time(&startTime);


	int rcnt = 0;

	while(true)
	{
		iLen = recv(Fd, &szReadBuffer[rcnt], 100, 0);
		rcnt += iLen;

		if(iLen == 0)
		{

			if(rcnt >= 3126)
				break;
		}
		else if(iLen == SOCKET_ERROR)
		{
			int error = WSAGetLastError();
			if(error == 10054)
			{
				iRet = ISAO_ERR_SSL_TIMEOUT;
				goto IsaoCheck_Free;
			}
		}
		else
		{
		}

		time(&endTime);

		if((endTime - startTime) > 10)
		{
			iRet = ISAO_ERR_RECONNECT;
			goto IsaoCheck_Free;
		}
	}

	*dataSize = rcnt;

	if(iLen < 0)
	{
		iRet = ISAO_ERR_SSL_READ;

		goto IsaoCheck_Free;
	}


IsaoCheck_Free:

	closesocket(Fd);
	fd2("\n 웹db 접근 끝남.");

	return iRet;
}


int ISAOCHECK::chk_readbuffer(char *cmd, char *readbuf, int *iRejectC)
{
	int iRejectCode = 111111;
	char *pBuf = strstr(readbuf, cmd);

	if(pBuf == NULL)
		return ISAO_ERR_NONE_REEJCT;


	pBuf = pBuf + strlen(cmd);
	while(true)
	{
		if(*pBuf != ' ')
			break;

		pBuf++;
	}
	sscanf_s(pBuf, "%d", &iRejectCode);

	return iRejectCode;
}



int ISAOCHECK::chk_readStrBuf(char *cmd, char *readbuf, char *retBuf)
{
	int iRejectCode = 111111;
	char *pBuf = strstr(readbuf, cmd);

	if(!pBuf)
		return ISAO_ERR_NONE_REEJCT;


	pBuf = pBuf + strlen(cmd);

	while(true)
	{
		if(*pBuf != ' ')
			break;

		pBuf++;
	}
	sscanf_s(pBuf, "%s", retBuf, strlen(retBuf));

	return iRejectCode;
}

int ISAOCHECK::IsaoCheck(char *id, char *pass, char *ipaddr, long StartTime)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer[BUF_LEN];

	sprintf(szWriteBuffer, "http://%s/login.php?UserID=%s&PassWord=%s", hostName, id, pass);

	ret_chk = connect_WEBdb(szWriteBuffer, szReadBuffer);

	fd2(" 웹 db에서 읽은것 %s ", szReadBuffer);

	switch(ret_chk)
	{
		case ISAO_ERR_WINSOCK_NOERR:

		fd2("From server: ---from--\n%s--end--\n ", szReadBuffer);
		break;
		case ISAO_ERR_WINSOCK_START:
		fd2("WSAStartup()에라");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_WINSOCK_VERSION:
		fd2("버전이 맞지 않음");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_TCP_CONNECT:
		fd2("connect() 접속 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_READ:
		fd2(" recv() 읽기 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_TIMEOUT:
		fd2("---------------- select() 타임아웃 실패");
		goto IsaoCheck_winsockERR;
	};

	ret_chk = chk_readbuffer("account=", szReadBuffer, &iRejectCode);
	switch(ret_chk)
	{
		case 0:

		sprintf(szWriteBuffer, "http://%s/LoginCheck.php?UserID=%s&StartTime=%d", hostName, id, StartTime);

		ret_chk = connect_WEBdb(szWriteBuffer, szReadBuffer);
		ret_chk = chk_readbuffer("account=", szReadBuffer, &iRejectCode);
		switch(ret_chk)
		{
			case 13:
			goto IsaoCheck_Free;
			case 14:
			goto IsaoCheck_Free;
		}
		goto IsaoCheck_Free;
		case 1:
		goto IsaoCheck_Free;
		case 2:

		sprintf(szWriteBuffer, "http://%s/InsertUser.php?UserID=%s&PassWord=%s&UserName=%s", hostName, id, pass, "aaaa");
		ret_chk = connect_WEBdb(szWriteBuffer, szReadBuffer);
		ret_chk = chk_readbuffer("account=", szReadBuffer, &iRejectCode);

		switch(ret_chk)
		{
			case 3:

			sprintf(szWriteBuffer, "http://%s/LoginCheck.php?UserID=%s&StartTime=%d", hostName, id, StartTime);
			ret_chk = connect_WEBdb(szWriteBuffer, szReadBuffer);
			ret_chk = chk_readbuffer("account=", szReadBuffer, &iRejectCode);
			switch(ret_chk)
			{
				case 5:
				goto IsaoCheck_Free;
				case 6:
				goto IsaoCheck_Free;
			}
			goto IsaoCheck_Free;
			case 4:
			goto IsaoCheck_Free;
		}
		goto IsaoCheck_Free;


		case ISAO_ERR_NONE_REEJCT:
		fd2("ISAO_ERR_NONE_REEJCT : 응답번호가 없음");
		goto IsaoCheck_Free;
	}


IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:
	return ret_chk;
}


int ISAOCHECK::IsaoCheck_GameExit(char *id, char *pass, char *ipaddr, long usertime)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer[BUF_LEN];

	sprintf(szWriteBuffer, "http://%s/Login_End.php?UserID=%s&IP=%s&EndTime=%d&UseTime=%d", hostName, id, ipaddr, iTimeOut, usertime);

	ret_chk = connect_WEBdb(szWriteBuffer, szReadBuffer);

	fd2(" 웹 db에서 읽은것 %s ", szReadBuffer);

	switch(ret_chk)
	{
		case ISAO_ERR_WINSOCK_NOERR:

		fd2("From server: ---from--\n%s--end--\n ", szReadBuffer);
		break;
		case ISAO_ERR_WINSOCK_START:
		fd2("WSAStartup()에라");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_WINSOCK_VERSION:
		fd2("버전이 맞지 않음");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_TCP_CONNECT:
		fd2("connect() 접속 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_READ:
		fd2(" recv() 읽기 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_TIMEOUT:
		fd2("---------------- select() 타임아웃 실패");
		goto IsaoCheck_winsockERR;
	};


	ret_chk = chk_readbuffer("account=", szReadBuffer, &iRejectCode);
	switch(ret_chk)
	{
		case 7:
		goto IsaoCheck_Free;

		case 8:
		goto IsaoCheck_Free;

		case ISAO_ERR_NONE_REEJCT:
		fd2("ISAO_ERR_NONE_REEJCT : 응답번호가 없음");
		goto IsaoCheck_Free;
	}


IsaoCheck_Free:

	return ret_chk;


IsaoCheck_winsockERR:
	return ret_chk;
}


int ISAOCHECK::isCheckClanJang(char *ClanZang_id, char* gserver)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer[BUF_LEN];

	sprintf(szWriteBuffer, "http://%s//brnxmainsv//isCheckClanJang.asp?userid=%s&gserver=%s&ticket=%d", hostName, ClanZang_id, gserver, nClanTicket);

	int cnt = 0;
	while(true)
	{
		ret_chk = connect_WEBdb(szWriteBuffer, szReadBuffer);
		if(ret_chk != ISAO_ERR_RECONNECT) break;
		if(cnt > 5) break;
		cnt++;
	}



	debug_fd2("isCheckClanJang() 보낸것 길이 : %d(ret_chk %d) 내용 : %s ", strlen(szWriteBuffer), ret_chk, szWriteBuffer);
	debug_fd2("isCheckClanJang() 받은것 길이 : %d 내용 : %s ", strlen(szReadBuffer), szReadBuffer);







	switch(ret_chk)
	{
		case ISAO_ERR_WINSOCK_NOERR:




		ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode);
		switch(ret_chk)
		{
			case 0:
			break;
			case 1:
			break;
			case 5:
			break;


			break;


			case ISAO_ERR_NONE_REEJCT:
			fd2("ISAO_ERR_NONE_REEJCT : 응답번호가 없음");
			goto IsaoCheck_Free;
		}



		break;
		case ISAO_ERR_WINSOCK_START:
		fd2("WSAStartup()에라");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_WINSOCK_VERSION:
		fd2("버전이 맞지 않음");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_TCP_CONNECT:
		fd2("connect() 접속 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_READ:
		fd2(" recv() 읽기 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_TIMEOUT:
		fd2("---------------- select() 타임아웃 실패");
		goto IsaoCheck_winsockERR;
	};




IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:
	return ret_chk;
}


int ISAOCHECK::isCheckClanName(char *ClanName, char *gserver)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer[BUF_LEN];

	sprintf(szWriteBuffer, "http://%s//brnxmainsv//isCheckClanName.asp?ClName=%s&gserver=%s&ticket=%d", hostName, ClanName, gserver, nClanTicket);

	int cnt = 0;
	while(true)
	{
		ret_chk = connect_WEBdb(szWriteBuffer, szReadBuffer);
		if(ret_chk != ISAO_ERR_RECONNECT) break;
		if(cnt > 5) break;
		cnt++;
	}




	debug_fd2("isCheckClanName() 보낸것 길이 : %d 내용 : %s ", strlen(szWriteBuffer), szWriteBuffer);
	debug_fd2("isCheckClanName() 받은것 길이 : %d 내용 : %s ", strlen(szReadBuffer), szReadBuffer);






	switch(ret_chk)
	{
		case ISAO_ERR_WINSOCK_NOERR:




		ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode);
		switch(ret_chk)
		{
			case 0:
			break;
			case 1:
			break;



			case ISAO_ERR_NONE_REEJCT:
			fd2("ISAO_ERR_NONE_REEJCT : 응답번호가 없음");
			goto IsaoCheck_Free;
		}



		break;
		case ISAO_ERR_WINSOCK_START:
		fd2("WSAStartup()에라");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_WINSOCK_VERSION:
		fd2("버전이 맞지 않음");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_TCP_CONNECT:
		fd2("connect() 접속 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_READ:
		fd2(" recv() 읽기 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_TIMEOUT:
		fd2("---------------- select() 타임아웃 실패");
		goto IsaoCheck_winsockERR;
	};




IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:
	return ret_chk;
}


int ISAOCHECK::ReadClanInfo(char *clanNum, char* ret_Buf)
{
	int ret_chk = 0;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer[BUF_LEN];


	sprintf(szWriteBuffer, "http://%s//brnxmainsv//isCheckClanNum.asp?num=%s&ticket=%d", hostName, clanNum, nClanTicket);

	int cnt = 0;
	while(true)
	{
		ret_chk = connect_WEBdb(szWriteBuffer, szReadBuffer);

		if(ret_chk != ISAO_ERR_RECONNECT)
			break;

		if(cnt > 5)
			break;
		cnt++;
	}



	debug_fd2("ReadClanInfo() 보낸것 길이 : %d 내용 : %s ", strlen(szWriteBuffer), szWriteBuffer);
	debug_fd2("ReadClanInfo() 받은것 길이 : %d 내용 : %s ", strlen(szReadBuffer), szReadBuffer);







	switch(ret_chk)
	{
		case ISAO_ERR_WINSOCK_NOERR:




		ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode);
		switch(ret_chk)
		{
			case 0:
			break;
			case 1:
			strcpy(ret_Buf, szReadBuffer);
			break;

			case ISAO_ERR_NONE_REEJCT:
			fd2("ISAO_ERR_NONE_REEJCT : 응답번호가 없음");
			goto IsaoCheck_Free;
		}



		break;
		case ISAO_ERR_WINSOCK_START:
		fd2("WSAStartup()에라");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_WINSOCK_VERSION:
		fd2("버전이 맞지 않음");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_TCP_CONNECT:
		fd2("connect() 접속 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_READ:
		fd2(" recv() 읽기 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_TIMEOUT:
		fd2("---------------- select() 타임아웃 실패");
		goto IsaoCheck_winsockERR;
	};




IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:
	return ret_chk;
}

int ISAOCHECK::isCheckClanMember(char *pszServerName, char *pszUserName)
{
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer[BUF_LEN];
	int receiveCode;

	ZeroMemory(szReadBuffer, sizeof(szReadBuffer));

	sprintf(szWriteBuffer, "http://%s//brnxmainsv//isCheckClanwon.asp?gserver=%s&clwon=%s", hostName, pszServerName, pszUserName);

	int cnt = 0;

	while(true)
	{
		receiveCode = connect_WEBdb(szWriteBuffer, szReadBuffer);
		if(receiveCode != ISAO_ERR_RECONNECT) break;
		if(cnt > 5) break;
		cnt++;
	}

	if(strlen(szReadBuffer) > 2048)
	{
		szReadBuffer[2048] = 0;
		debug_fd2("isClanMember() 너무길어서 잘랐다.");
	}

	switch(receiveCode)
	{
		case ISAO_ERR_WINSOCK_NOERR:
		{
			receiveCode = chk_readbuffer("Code=", szReadBuffer, &iRejectCode);
			if(receiveCode == ISAO_ERR_NONE_REEJCT)
			{
				fd2("ISAO_ERR_NONE_REEJCT : 응답번호가 없음");
			}
		}

		case ISAO_ERR_WINSOCK_START:
		{
			fd2("WSAStartup()에라");
			break;
		}
		case ISAO_ERR_WINSOCK_VERSION:
		{
			fd2("버전이 맞지 않음");
			break;
		}

		case ISAO_ERR_TCP_CONNECT:
		{
			fd2("connect() 접속 실패");
			break;
		}
		case ISAO_ERR_SSL_READ:
		{
			fd2(" recv() 읽기 실패");
			break;
		}
		case ISAO_ERR_SSL_TIMEOUT:
		{
			fd2("---------------- select() 타임아웃 실패");
			break;
		}
	}

	return receiveCode;
}


int ISAOCHECK::isClanMember(char *ClanZang_id, char* gserver, char* ClanZang_ChaName, char* ret_Buf)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer[BUF_LEN];

	ZeroMemory(szReadBuffer, sizeof(szReadBuffer));

	sprintf_s(szWriteBuffer, sizeof(szWriteBuffer), "http://%s//brnxmainsv//isClanMember.asp?userid=%s&gserver=%s&chname=%s&ticket=%d", hostName, ClanZang_id, gserver, ClanZang_ChaName, nClanTicket);

	int cnt = 0;

	while(true)
	{
		ret_chk = connect_WEBdb(szWriteBuffer, szReadBuffer);

		if(ret_chk != ISAO_ERR_RECONNECT)
			break;

		if(cnt > 5)
			break;

		cnt++;
	}

	if(strlen(szReadBuffer) > 2048)
	{
		szReadBuffer[2048] = 0;
		debug_fd2("isClanMember() 너무길어서 잘랐다.");
	}


	debug_fd2("isClanMember() 보낸것 길이 : %d 내용 : %s ", strlen(szWriteBuffer), szWriteBuffer);
	debug_fd2("isClanMember() 받은것 길이 : %d 내용 : %s ", strlen(szReadBuffer), szReadBuffer);

	switch(ret_chk)
	{
		case ISAO_ERR_WINSOCK_NOERR:

		ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode);
		switch(ret_chk)
		{
			case 0:
			strcpy(ret_Buf, szReadBuffer);
			break;
			case 1:

			case 5:
			case 4:
			case 3:
			case 2:
			strcpy(ret_Buf, szReadBuffer);
			break;


			strcpy(ret_Buf, szReadBuffer);
			break;


			case ISAO_ERR_NONE_REEJCT:
			fd2("ISAO_ERR_NONE_REEJCT : 응답번호가 없음");
			goto IsaoCheck_Free;
		}



		break;
		case ISAO_ERR_WINSOCK_START:
		fd2("WSAStartup()에라");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_WINSOCK_VERSION:
		fd2("버전이 맞지 않음");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_TCP_CONNECT:
		fd2("connect() 접속 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_READ:
		fd2(" recv() 읽기 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_TIMEOUT:
		fd2("---------------- select() 타임아웃 실패");
		goto IsaoCheck_winsockERR;
	};




IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:
	return ret_chk;
}



int ISAOCHECK::joinClanMember(char *ClanZang_ID, char *gserver, char *ClanZang_ChaName, char* ClanName, char* ClanWon, char* ClanWon_ID, int level, DWORD chtype, int joinlevel, char *chipflag)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer[BUF_LEN];

	sprintf(szWriteBuffer,
			"http://%s//brnxmainsv//clanInsertClanWon.asp?userid=%s&gserver=%s&chname=%s&clName=%s&clwon=%s&clwonUserid=%s&lv=%d&ticket=%d&chtype=%d&chlv=%d&chipflag=%s",
			hostName, ClanZang_ID, gserver, ClanZang_ChaName, ClanName, ClanWon, ClanWon_ID, level, nClanTicket, chtype, joinlevel, chipflag);

	int cnt = 0;
	while(true)
	{
		ret_chk = connect_WEBdb(szWriteBuffer, szReadBuffer);

		if(ret_chk != ISAO_ERR_RECONNECT)
			break;

		if(cnt > 5)
			break;
		cnt++;
	}


	debug_fd2("joinClanMember() 보낸것 길이 : %d 내용 : %s ", strlen(szWriteBuffer), szWriteBuffer);
	debug_fd2("joinClanMember() 받은것 길이 : %d 내용 : %s ", strlen(szReadBuffer), szReadBuffer);

	switch(ret_chk)
	{
		case ISAO_ERR_WINSOCK_NOERR:

		ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode);
		switch(ret_chk)
		{
			case 0:
			break;
			case 1:
			break;
			case 2:
			break;
			case 3:
			break;
			case 4:
			break;
			case 100:
			case 101:
			case 102:
			case 103:
			break;

			case ISAO_ERR_NONE_REEJCT:
			fd2("ISAO_ERR_NONE_REEJCT : 응답번호가 없음");
			goto IsaoCheck_Free;
		}


		break;
		case ISAO_ERR_WINSOCK_START:
		fd2("WSAStartup()에라");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_WINSOCK_VERSION:
		fd2("버전이 맞지 않음");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_TCP_CONNECT:
		fd2("connect() 접속 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_READ:
		fd2(" recv() 읽기 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_TIMEOUT:
		fd2("---------------- select() 타임아웃 실패");
		goto IsaoCheck_winsockERR;
	};




IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:
	return ret_chk;
}



int ISAOCHECK::makeClan(char *ClanZang_ID, char* gserver, char* ClanZang_ChaName, char* ClanName, char *explanation, DWORD chtype, int level, char* data)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer[BUF_LEN];

	int chkCnt = 0;

	sprintf(szWriteBuffer, "http://%s/brnx/verificarcl.asp?userid=%s&gserver=%s&chname=%s&clName=%s&expl=%s&ticket=%d&chtype=%d&lv=%d",
			hostName1, ClanZang_ID, gserver, ClanZang_ChaName, ClanName, explanation, nClanTicket, chtype, level);

	int cnt = 0;

	while(true)
	{
		ret_chk = connect_WEBdb_1(szWriteBuffer, szReadBuffer);

		if(ret_chk != ISAO_ERR_RECONNECT)
			break;

		if(cnt > 5)
			break;

		cnt++;
	}

	debug_fd2("makeClan() 보낸것 길이 : %d 내용 : %s ", strlen(szWriteBuffer), szWriteBuffer);
	debug_fd2("makeClan() 받은것 길이 : %d 내용 : %s ", strlen(szReadBuffer), szReadBuffer);


	switch(ret_chk)
	{
		case ISAO_ERR_WINSOCK_NOERR:

		fd2("From server: ---from--\n%s--end--\n ", szReadBuffer);
		break;
		case ISAO_ERR_WINSOCK_START:
		fd2("WSAStartup()에라");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_WINSOCK_VERSION:
		fd2("버전이 맞지 않음");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_TCP_CONNECT:
		fd2("connect() 접속 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_READ:
		fd2(" recv() 읽기 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_TIMEOUT:
		fd2("---------------- select() 타임아웃 실패");
		goto IsaoCheck_winsockERR;
	};




	ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode);
	switch(ret_chk)
	{

		case 0:
		break;
		case 1:
		strcpy(data, szReadBuffer);
		break;
		case 2:
		break;
		case 3:
		break;
		case 4:
		break;
		case 100:
		break;


		case ISAO_ERR_NONE_REEJCT:
		fd2("ISAO_ERR_NONE_REEJCT : 응답번호가 없음");
		goto IsaoCheck_Free;
	}


IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:
	return ret_chk;
}



int ISAOCHECK::read_ClanName(int readClumns)
{
	char *clumns[] = {
		"name",
		"explanation",
		"date",
		"Image",
		"clanZang",
		"clanWon1",
		"clanWon2",
		"clanWon3",
		"clanWon4",
		"clanWon5",
		"clanWon6",
	};

	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer[BUF_LEN];

	sprintf(szWriteBuffer, "http://%s/tjboyh/clan_readClanName.php?columnName=%s&ticket=%d", hostName, clumns[readClumns], nClanTicket);

	ret_chk = connect_WEBdb(szWriteBuffer, szReadBuffer);

	fd2(" 웹 db에서 읽은것 %s ", szReadBuffer);


	switch(ret_chk)
	{
		case ISAO_ERR_WINSOCK_NOERR:

		fd2("From server: ---from--\n%s--end--\n ", szReadBuffer);
		break;
		case ISAO_ERR_WINSOCK_START:
		fd2("WSAStartup()에라");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_WINSOCK_VERSION:
		fd2("버전이 맞지 않음");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_TCP_CONNECT:
		fd2("connect() 접속 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_READ:
		fd2(" recv() 읽기 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_TIMEOUT:
		fd2("---------------- select() 타임아웃 실패");
		goto IsaoCheck_winsockERR;
	};


	ret_chk = chk_readbuffer("account:", szReadBuffer, &iRejectCode);
	switch(ret_chk)
	{
		case 0:
		goto IsaoCheck_Free;
		case 1:
		goto IsaoCheck_Free;
		case 2:
		goto IsaoCheck_Free;

		case ISAO_ERR_NONE_REEJCT:
		fd2("ISAO_ERR_NONE_REEJCT : 응답번호가 없음");
		goto IsaoCheck_Free;
	}


IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:
	return ret_chk;
}


int ISAOCHECK::read_ClanData(char *ClanZang_ID, char* gserver, char* ClanZang_ChaName, char* ret_Buf)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer[BUF_LEN];

	sprintf(szWriteBuffer, "http://%s//brnxmainsv//GetAllMyClanMember.asp?userid=%s&gserver=%s&chname=%s&ticket=%d", hostName, ClanZang_ID, gserver, ClanZang_ChaName, nClanTicket);

	int cnt = 0;

	while(true)
	{
		ret_chk = connect_WEBdb(szWriteBuffer, szReadBuffer);

		if(ret_chk != ISAO_ERR_RECONNECT)
			break;

		if(cnt > 5)
			break;
		cnt++;
	}

	debug_fd2("read_ClanData() 보낸것 길이 : %d 내용 : %s ", strlen(szWriteBuffer), szWriteBuffer);
	debug_fd2("read_ClanData() 받은것 길이 : %d 내용 : %s ", strlen(szReadBuffer), szReadBuffer);


	switch(ret_chk)
	{
		case ISAO_ERR_WINSOCK_NOERR:
		fd2("From server: ---from--\n%s--end--\n ", szReadBuffer);
		break;
		case ISAO_ERR_WINSOCK_START:
		fd2("WSAStartup()에라");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_WINSOCK_VERSION:
		fd2("버전이 맞지 않음");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_TCP_CONNECT:
		fd2("connect() 접속 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_READ:
		fd2(" recv() 읽기 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_TIMEOUT:
		fd2("---------------- select() 타임아웃 실패");
		goto IsaoCheck_winsockERR;
	};



	ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode);
	switch(ret_chk)
	{

		case 0:
		break;
		case 1:
		strcpy(ret_Buf, szReadBuffer);
		break;
		case 100:
		strcpy(ret_Buf, szReadBuffer);
		case 101:
		goto IsaoCheck_Free;

		case ISAO_ERR_NONE_REEJCT:
		fd2("ISAO_ERR_NONE_REEJCT : 응답번호가 없음");
		goto IsaoCheck_Free;
	}


IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:
	return ret_chk;
}



int ISAOCHECK::BreakUPClan(char *ClanZang_ID, char *gserver, char *ClanZang_ChaName, char *ClanName)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer[BUF_LEN];

	sprintf(szWriteBuffer, "http://%s//brnxmainsv//clanRemove.asp?userid=%s&gserver=%s&chname=%s&clName=%s&ticket=%d",
			hostName, ClanZang_ID, gserver, ClanZang_ChaName, ClanName, nClanTicket);

	int cnt = 0;

	while(true)
	{
		ret_chk = connect_WEBdb(szWriteBuffer, szReadBuffer);

		if(ret_chk != ISAO_ERR_RECONNECT)
			break;

		if(cnt > 5)
			break;

		cnt++;
	}

	fd2(" 웹 db에서 읽은것 %s ", szReadBuffer);


	switch(ret_chk)
	{
		case ISAO_ERR_WINSOCK_NOERR:

		fd2("From server: ---from--\n%s--end--\n ", szReadBuffer);
		break;
		case ISAO_ERR_WINSOCK_START:
		fd2("WSAStartup()에라");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_WINSOCK_VERSION:
		fd2("버전이 맞지 않음");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_TCP_CONNECT:
		fd2("connect() 접속 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_READ:
		fd2(" recv() 읽기 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_TIMEOUT:
		fd2("---------------- select() 타임아웃 실패");
		goto IsaoCheck_winsockERR;
	};



	ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode);
	switch(ret_chk)
	{
		case 0:
		break;
		case 1:
		break;
		case 2:
		break;

		case ISAO_ERR_NONE_REEJCT:
		fd2("ISAO_ERR_NONE_REEJCT : 응답번호가 없음");
		goto IsaoCheck_Free;
	}


IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:
	return ret_chk;
}



extern char szNoticeUrl[255];



int ISAOCHECK::connect_WEBdb_NOTICE(char *szWriteBuffer, char *szReadBuffer)
{
	char szSizeBuffer[32];
	DWORD dwLengthSizeBuffer = sizeof(szSizeBuffer);
	DWORD dwFileSize = 0;
	DWORD dwBytesRead = 0;
	int iRet = ISAO_ERR_WINSOCK_NOERR;

	ZeroMemory(szReadBuffer, BUF_LEN);


	HINTERNET m_Session = NULL;
	m_Session = InternetOpen("AppName",
							 INTERNET_OPEN_TYPE_PRECONFIG,

							 NULL,

							 NULL,

							 0);
	if(!m_Session)
	{
		iRet = ISAO_ERR_TCP_CONNECT;
		return iRet;
	}
	HINTERNET hHttpFile = NULL;
	hHttpFile = InternetOpenUrl(m_Session, (const char *)szWriteBuffer, NULL,
								0, 0, 0);
	if(hHttpFile)
	{
		BOOL bQuery = HttpQueryInfo(hHttpFile, HTTP_QUERY_CONTENT_LENGTH, szSizeBuffer,
									&dwLengthSizeBuffer, NULL);

		if(bQuery == TRUE)
		{
			dwFileSize = atol(szSizeBuffer);
			dwFileSize > BUF_LEN ? dwFileSize = BUF_LEN :
				dwFileSize = dwFileSize;

			BOOL bRead = InternetReadFile(hHttpFile, szReadBuffer, dwFileSize, &dwBytesRead);
			if(bRead)
			{
				if((bRead == TRUE) && (dwFileSize != dwBytesRead))
				{
					iRet = ISAO_ERR_RECONNECT;
				}


			}
			else iRet = ISAO_ERR_RECONNECT;
		}
	}
	else
	{
		iRet = ISAO_ERR_TCP_CONNECT;
		return iRet;
	}
	if(hHttpFile) InternetCloseHandle(hHttpFile);
	if(m_Session) InternetCloseHandle(m_Session);
	return iRet;
}

int ConvertURL(char *szURL, char *szServer, size_t szServerSize, char *szPath, size_t szPathSize)
{
	char *lpServer = nullptr;
	char *lpPath = nullptr;
	char szbuff[256] = { 0 };

	strcpy_s(szbuff, szURL);

	int len = lstrlen(szbuff);

	for(int cnt = 0; cnt < len; cnt++)
	{
		if(!lpServer && szbuff[cnt] == '/' && szbuff[cnt + 1] == '/')
		{
			lpServer = &szbuff[cnt + 2];
			cnt += 2;
		}

		if(!lpPath && szbuff[cnt] == '/' && szbuff[cnt + 1] != '/')
			lpPath = &szbuff[cnt];
	}

	if(lpPath)
	{
		if(szPath)
		{
			strcpy_s(szPath, szPathSize, lpPath);
		}

		lpPath[0] = 0;
	}
	else
		if(szPath)
			szPath[0] = 0;

	if(szServer)
	{
		if(lpServer)
		{
			strcpy_s(szServer, szServerSize, lpServer);
		}
		else
		{
			strcpy_s(szServer, szServerSize, szbuff);
		}
	}

	return TRUE;
}


int ISAOCHECK::ReadNotice(char *userid, char *chaname, char *gserver, char *buf)
{
	int ret_chk = 0;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer[BUF_LEN];

	char szServer[256], szPath[256];
	ConvertURL(szNoticeUrl, szServer, sizeof(szServer), szPath, sizeof(szPath));

	sprintf_s(szWriteBuffer, sizeof(szWriteBuffer), "%s?userid=%s&gserver=%s&chname=%s&ticket=%d\r\n\r\n\r\n", szNoticeUrl, userid, gserver, chaname, nClanTicket);

	int cnt = 0;

	while(true)
	{
		ret_chk = connect_WEBdb_NOTICE(szWriteBuffer, szReadBuffer);

		if(ret_chk != ISAO_ERR_RECONNECT)
			break;

		if(cnt > 5)
			break;

		cnt++;
	}

	debug_fd2("ReadNotice() 보낸것 길이 : %d(ret_chk %d) 내용 : %s ", strlen(szWriteBuffer), ret_chk, szWriteBuffer);
	debug_fd2("ReadNotice() 받은것 길이 : %d 내용 : %s ", strlen(szReadBuffer), szReadBuffer);


	switch(ret_chk)
	{
		case ISAO_ERR_WINSOCK_NOERR:
		fd2("From server: ---from--\n%s--end--\n ", szReadBuffer);
		break;
		case ISAO_ERR_WINSOCK_START:
		fd2("WSAStartup()에라");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_WINSOCK_VERSION:
		fd2("버전이 맞지 않음");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_TCP_CONNECT:
		fd2("connect() 접속 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_READ:
		fd2(" recv() 읽기 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_TIMEOUT:
		fd2("---------------- select() 타임아웃 실패");
		goto IsaoCheck_winsockERR;
	};




	ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode);

	switch(ret_chk)
	{
		case 0:
		break;
		case 1:
		strcpy(buf, szReadBuffer);
		break;
		case 2:
		break;
		case 3:
		break;
		case 100:
		case 101:
		case 102:
		case 103:
		goto IsaoCheck_Free;

		case ISAO_ERR_NONE_REEJCT:
		fd2("ISAO_ERR_NONE_REEJCT : 응답번호가 없음");
		goto IsaoCheck_Free;
	}


IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:
	return ret_chk;
}


int ISAOCHECK::Banishiment(char *ClanZang_ID, char *gserver, char *ClanZang_ChaName, char *ClanName, char *ClanWon)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer[BUF_LEN];

	sprintf(szWriteBuffer, "http://%s//brnxmainsv//clanWonRelease.asp?userid=%s&gserver=%s&chname=%s&clName=%s&%s&ticket=%d",
			hostName, ClanZang_ID, gserver, ClanZang_ChaName, ClanName, ClanWon, nClanTicket);

	int cnt = 0;

	while(true)
	{
		ret_chk = connect_WEBdb(szWriteBuffer, szReadBuffer);

		if(ret_chk != ISAO_ERR_RECONNECT)
			break;

		if(cnt > 5)
			break;

		cnt++;
	}

	debug_fd2("Banishiment() 보낸것 길이 : %d(ret_chk %d) 내용 : %s ", strlen(szWriteBuffer), ret_chk, szWriteBuffer);
	debug_fd2("Banishiment() 받은것 길이 : %d 내용 : %s ", strlen(szReadBuffer), szReadBuffer);

	switch(ret_chk)
	{
		case ISAO_ERR_WINSOCK_NOERR:

		fd2("From server: ---from--\n%s--end--\n ", szReadBuffer);
		break;
		case ISAO_ERR_WINSOCK_START:
		fd2("WSAStartup()에라");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_WINSOCK_VERSION:
		fd2("버전이 맞지 않음");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_TCP_CONNECT:
		fd2("connect() 접속 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_READ:
		fd2(" recv() 읽기 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_TIMEOUT:
		fd2("---------------- select() 타임아웃 실패");
		goto IsaoCheck_winsockERR;
	};

	ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode);
	switch(ret_chk)
	{

		case 0:
		break;
		case 1:
		break;
		case 2:
		break;
		case 3:
		break;
		case 100:
		case 101:
		case 102:
		case 103:
		goto IsaoCheck_Free;

		case ISAO_ERR_NONE_REEJCT:
		fd2("ISAO_ERR_NONE_REEJCT : 응답번호가 없음");
		goto IsaoCheck_Free;
	}


IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:
	return ret_chk;
}


int ISAOCHECK::AppointSubChip(char *gserver, char* clanwon)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer[BUF_LEN];


	sprintf(szWriteBuffer, "http://%s//brnxmainsv//ClanSubChipUpdate.asp?chname=%s&gserver=%s&ticket=%d", hostName, clanwon, gserver, 9999);

	int cnt = 0;

	while(true)
	{
		ret_chk = connect_WEBdb(szWriteBuffer, szReadBuffer);

		if(ret_chk != ISAO_ERR_RECONNECT)
			break;

		if(cnt > 5)
			break;

		cnt++;
	}

	debug_fd2("AppointSubChip() 보낸것 길이 : %d 내용 : %s ", strlen(szWriteBuffer), szWriteBuffer);
	debug_fd2("AppointSubChip() 받은것 길이 : %d 내용 : %s ", strlen(szReadBuffer), szReadBuffer);

	switch(ret_chk)
	{
		case ISAO_ERR_WINSOCK_NOERR:
		fd2("From server: ---from--\n%s--end--\n ", szReadBuffer);
		break;
		case ISAO_ERR_WINSOCK_START:
		fd2("WSAStartup()에라");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_WINSOCK_VERSION:
		fd2("버전이 맞지 않음");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_TCP_CONNECT:
		fd2("connect() 접속 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_READ:
		fd2(" recv() 읽기 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_TIMEOUT:
		fd2("---------------- select() 타임아웃 실패");
		goto IsaoCheck_winsockERR;
	}

	ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode);
	switch(ret_chk)
	{

		case 0:
		break;
		case 2:
		break;
		case 1:
		break;
		case 3:
		break;
		case 100:
		case 101:
		case 102:
		case 103:
		goto IsaoCheck_Free;

		case ISAO_ERR_NONE_REEJCT:
		fd2("ISAO_ERR_NONE_REEJCT : 응답번호가 없음");
		goto IsaoCheck_Free;
	}


IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:
	return ret_chk;
}


int ISAOCHECK::ReleaseSubChip(char *gserver, char* clanwon)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer[BUF_LEN];

	sprintf(szWriteBuffer, "http://%s//brnxmainsv//ClanSubChipRelease.asp?chname=%s&gserver=%s&ticket=%d", hostName, clanwon, gserver, 9999);

	int cnt = 0;

	while(true)
	{
		ret_chk = connect_WEBdb(szWriteBuffer, szReadBuffer);

		if(ret_chk != ISAO_ERR_RECONNECT)
			break;

		if(cnt > 5)
			break;
		cnt++;
	}

	debug_fd2("ReleaseSubChip() 보낸것 길이 : %d 내용 : %s ", strlen(szWriteBuffer), szWriteBuffer);
	debug_fd2("ReleaseSubChip() 받은것 길이 : %d 내용 : %s ", strlen(szReadBuffer), szReadBuffer);

	switch(ret_chk)
	{
		case ISAO_ERR_WINSOCK_NOERR:
		fd2("From server: ---from--\n%s--end--\n ", szReadBuffer);
		break;
		case ISAO_ERR_WINSOCK_START:
		fd2("WSAStartup()에라");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_WINSOCK_VERSION:
		fd2("버전이 맞지 않음");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_TCP_CONNECT:
		fd2("connect() 접속 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_READ:
		fd2(" recv() 읽기 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_TIMEOUT:
		fd2("---------------- select() 타임아웃 실패");
		goto IsaoCheck_winsockERR;
	}

	ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode);
	switch(ret_chk)
	{

		case 0:
		break;
		case 2:
		break;
		case 1:
		break;

		case 100:
		case 101:
		case 102:
		case 103:
		goto IsaoCheck_Free;

		case ISAO_ERR_NONE_REEJCT:
		fd2("ISAO_ERR_NONE_REEJCT : 응답번호가 없음");
		goto IsaoCheck_Free;
	}

IsaoCheck_Free:
	return ret_chk;

IsaoCheck_winsockERR:
	return ret_chk;
}


int ISAOCHECK::LeaveClan(char *clanname, char *chaname, char *gserver)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer[BUF_LEN];

	sprintf(szWriteBuffer, "http://%s//brnxmainsv//clanChipChange.asp?chname=%s&gserver=%s&clName=%s&ticket=%d", hostName, chaname, gserver, clanname, nClanTicket);

	int cnt = 0;
	while(true)
	{
		ret_chk = connect_WEBdb(szWriteBuffer, szReadBuffer);

		if(ret_chk != ISAO_ERR_RECONNECT)
			break;

		if(cnt > 5)
			break;
		cnt++;
	}

	debug_fd2("LeaveClan() 보낸것 길이 : %d 내용 : %s ", strlen(szWriteBuffer), szWriteBuffer);
	debug_fd2("LeaveClan() 받은것 길이 : %d 내용 : %s ", strlen(szReadBuffer), szReadBuffer);

	switch(ret_chk)
	{
		case ISAO_ERR_WINSOCK_NOERR:
		fd2("From server: ---from--\n%s--end--\n ", szReadBuffer);
		break;
		case ISAO_ERR_WINSOCK_START:
		fd2("WSAStartup()에라");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_WINSOCK_VERSION:
		fd2("버전이 맞지 않음");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_TCP_CONNECT:
		fd2("connect() 접속 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_READ:
		fd2(" recv() 읽기 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_TIMEOUT:
		fd2("---------------- select() 타임아웃 실패");
		goto IsaoCheck_winsockERR;
	}

	ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode);
	switch(ret_chk)
	{

		case 1:
		break;
		case 2:
		break;
		case 3:
		break;
		case 4:
		break;
		case 5:
		break;
		case 6:
		break;
		case 100:
		case 101:
		case 102:
		case 103:
		goto IsaoCheck_Free;

		case ISAO_ERR_NONE_REEJCT:
		fd2("ISAO_ERR_NONE_REEJCT : 응답번호가 없음");
		goto IsaoCheck_Free;
	}


IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:
	return ret_chk;
}

int ISAOCHECK::Secession(char* clanzang, char* gserver, char* SecessionID, char* clanname)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer[BUF_LEN];

	sprintf(szWriteBuffer, "http://%s//brnxmainsv//clanWonSelfLeave.asp?userid=%s&gserver=%s&chname=%s&clName=%s&ticket=%d",
			hostName, clanzang, gserver, SecessionID, clanname, nClanTicket);

	int cnt = 0;

	while(true)
	{
		ret_chk = connect_WEBdb(szWriteBuffer, szReadBuffer);

		if(ret_chk != ISAO_ERR_RECONNECT)
			break;

		if(cnt > 5)
			break;
		cnt++;
	}

	fd2("Secession() 웹 db에서 읽은것 %s ", szReadBuffer);

	switch(ret_chk)
	{
		case ISAO_ERR_WINSOCK_NOERR:

		fd2("From server: ---from--\n%s--end--\n ", szReadBuffer);
		break;
		case ISAO_ERR_WINSOCK_START:
		fd2("WSAStartup()에라");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_WINSOCK_VERSION:
		fd2("버전이 맞지 않음");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_TCP_CONNECT:
		fd2("connect() 접속 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_READ:
		fd2(" recv() 읽기 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_TIMEOUT:
		fd2("---------------- select() 타임아웃 실패");
		goto IsaoCheck_winsockERR;
	}

	ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode);
	switch(ret_chk)
	{

		case 0:
		break;
		case 1:
		break;
		case 2:
		break;
		case 3:
		break;
		case 4:
		break;
		case 100:
		case 101:
		case 102:
		case 103:
		goto IsaoCheck_Free;

		case ISAO_ERR_NONE_REEJCT:
		fd2("ISAO_ERR_NONE_REEJCT : 응답번호가 없음");
		goto IsaoCheck_Free;
	}


IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:
	return ret_chk;
}

int ISAOCHECK::isKPFlag(char *userid, char *clanname, char *chaname, char *gserver, char *pflag, char *gunbun)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer[BUF_LEN];

	sprintf(szWriteBuffer, "http://%s//brnxmainsv//isKflag.asp?userid=%s&clName=%s&chName=%s&gserver=%s&KFlag=%s&Gubun=%s&ticket=%d",
			hostName, userid, clanname, chaname, gserver, pflag, gunbun, nClanTicket);

	int cnt = 0;

	while(true)
	{
		ret_chk = connect_WEBdb(szWriteBuffer, szReadBuffer);

		if(ret_chk != ISAO_ERR_RECONNECT)
			break;

		if(cnt > 5)
			break;
		cnt++;
	}

	debug_fd2("isPFlag() 보낸것 길이 : %d 내용 : %s ", strlen(szWriteBuffer), szWriteBuffer);
	debug_fd2("isPFlag() 받은것 길이 : %d 내용 : %s ", strlen(szReadBuffer), szReadBuffer);

	switch(ret_chk)
	{
		case ISAO_ERR_WINSOCK_NOERR:
		fd2("From server: ---from--\n%s--end--\n ", szReadBuffer);
		break;
		case ISAO_ERR_WINSOCK_START:
		fd2("WSAStartup()에라");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_WINSOCK_VERSION:
		fd2("버전이 맞지 않음");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_TCP_CONNECT:
		fd2("connect() 접속 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_READ:
		fd2(" recv() 읽기 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_TIMEOUT:
		fd2("---------------- select() 타임아웃 실패");
		goto IsaoCheck_winsockERR;
	}


	ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode);
	switch(ret_chk)
	{
		case 100:
		case 101:
		case 102:
		goto IsaoCheck_Free;
		case ISAO_ERR_TCP_CONNECT:
		case ISAO_ERR_NONE_REEJCT:
		fd2("ISAO_ERR_NONE_REEJCT : 응답번호가 없음");
		goto IsaoCheck_Free;
	}


IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:
	return ret_chk;
}

int ISAOCHECK::isPFlag(char *userid, char *clanname, char *chaname, char *gserver, char *pflag, char *gunbun)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer[BUF_LEN];

	sprintf(szWriteBuffer, "http://%s//brnxmainsv//isPFlag.asp?userid=%s&clName=%s&chName=%s&gserver=%s&PFlag=%s&Gubun=%s&ticket=%d",
			hostName, userid, clanname, chaname, gserver, pflag, gunbun, nClanTicket);

	int cnt = 0;

	while(true)
	{
		ret_chk = connect_WEBdb(szWriteBuffer, szReadBuffer);

		if(ret_chk != ISAO_ERR_RECONNECT)
			break;

		if(cnt > 5)
			break;
		cnt++;
	}

	debug_fd2("isPFlag() 보낸것 길이 : %d 내용 : %s ", strlen(szWriteBuffer), szWriteBuffer);
	debug_fd2("isPFlag() 받은것 길이 : %d 내용 : %s ", strlen(szReadBuffer), szReadBuffer);

	switch(ret_chk)
	{
		case ISAO_ERR_WINSOCK_NOERR:
		fd2("From server: ---from--\n%s--end--\n ", szReadBuffer);
		break;
		case ISAO_ERR_WINSOCK_START:
		fd2("WSAStartup()에라");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_WINSOCK_VERSION:
		fd2("버전이 맞지 않음");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_TCP_CONNECT:
		fd2("connect() 접속 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_READ:
		fd2(" recv() 읽기 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_TIMEOUT:
		fd2("---------------- select() 타임아웃 실패");
		goto IsaoCheck_winsockERR;
	}

	ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode);
	switch(ret_chk)
	{
		case 100:
		case 101:
		case 102:
		goto IsaoCheck_Free;
		case ISAO_ERR_TCP_CONNECT:
		case ISAO_ERR_NONE_REEJCT:
		fd2("ISAO_ERR_NONE_REEJCT : 응답번호가 없음");
		goto IsaoCheck_Free;
	}


IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:
	return ret_chk;
}

int ISAOCHECK::WarhouseRight(char *clname, char *right_str)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer[BUF_LEN];

	sprintf(szWriteBuffer, "http://%s/tjboyh/clan_WarehouseRight.php?clName=%s&whRight=%s&ticket=%d", hostName, clname, right_str, nClanTicket);


	int cnt = 0;

	while(true)
	{
		ret_chk = connect_WEBdb(szWriteBuffer, szReadBuffer);

		if(ret_chk != ISAO_ERR_RECONNECT)
			break;

		if(cnt > 5)
			break;

		cnt++;
	}



	fd2("WarhouseRight() 웹 db에서 읽은것 %s ", szReadBuffer);



	switch(ret_chk)
	{
		case ISAO_ERR_WINSOCK_NOERR:

		fd2("From server: ---from--\n%s--end--\n ", szReadBuffer);
		break;
		case ISAO_ERR_WINSOCK_START:
		fd2("WSAStartup()에라");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_WINSOCK_VERSION:
		fd2("버전이 맞지 않음");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_TCP_CONNECT:
		fd2("connect() 접속 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_READ:
		fd2(" recv() 읽기 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_TIMEOUT:
		fd2("---------------- select() 타임아웃 실패");
		goto IsaoCheck_winsockERR;
	}


	ret_chk = chk_readbuffer("account=", szReadBuffer, &iRejectCode);
	switch(ret_chk)
	{
		case 100:
		case 101:
		case 102:
		goto IsaoCheck_Free;

		case ISAO_ERR_NONE_REEJCT:
		fd2("ISAO_ERR_NONE_REEJCT : 응답번호가 없음");
		goto IsaoCheck_Free;
	}


IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:
	return ret_chk;
}

int ISAOCHECK::updateFlag(char *clname)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer[BUF_LEN];

	sprintf(szWriteBuffer, "http://%s/tjboyh/updateFlag.php?clName=%s&ticket=%d", hostName, clname, nClanTicket);

	int cnt = 0;

	while(true)
	{
		ret_chk = connect_WEBdb(szWriteBuffer, szReadBuffer);

		if(ret_chk != ISAO_ERR_RECONNECT)
			break;

		if(cnt > 5)
			break;

		cnt++;
	}

	fd2("updateFlag() 웹 db에서 읽은것 %s ", szReadBuffer);

	switch(ret_chk)
	{
		case ISAO_ERR_WINSOCK_NOERR:

		fd2("From server: ---from--\n%s--end--\n ", szReadBuffer);
		break;
		case ISAO_ERR_WINSOCK_START:
		fd2("WSAStartup()에라");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_WINSOCK_VERSION:
		fd2("버전이 맞지 않음");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_TCP_CONNECT:
		fd2("connect() 접속 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_READ:
		fd2(" recv() 읽기 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_TIMEOUT:
		fd2("---------------- select() 타임아웃 실패");
		goto IsaoCheck_winsockERR;
	}

	ret_chk = chk_readbuffer("account=", szReadBuffer, &iRejectCode);
	switch(ret_chk)
	{
		case 100:
		case 101:
		case 102:
		goto IsaoCheck_Free;

		case ISAO_ERR_NONE_REEJCT:
		fd2("ISAO_ERR_NONE_REEJCT : 응답번호가 없음");
		goto IsaoCheck_Free;
	}

IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:
	return ret_chk;
}

void clanDATA_save(char *fname, char *buff, int dataLen)
{
	HANDLE hFile;
	char allFname[64];
	sprintf_s(allFname, sizeof(allFname), "%s\\%s\\%s", SAVE_DIR, szConnServerName, fname);

	DWORD dwAcess = 0;
	hFile = CreateFile(allFname, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
					   NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile != INVALID_HANDLE_VALUE)
	{

		int chk = WriteFile(hFile, buff, dataLen, &dwAcess, NULL);

		CloseHandle(hFile);
	}
}

void clanDATA_save2(char *fname, char *buff, int dataLen)
{
	HANDLE hFile;
	char allFname[64];
	sprintf_s(allFname, sizeof(allFname), "%s\\%s", CLANINFO_DIR, fname);

	DWORD dwAcess = 0;
	hFile = CreateFile(allFname, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
					   NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile != INVALID_HANDLE_VALUE)
	{

		int chk = WriteFile(hFile, buff, dataLen, &dwAcess, NULL);

		CloseHandle(hFile);
	}
}

extern char szWavUrl[255];
int ISAOCHECK::GetWavFile(char* FileName)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer[BUF_LEN];

	strcpy_s(szNoticeUrl, sizeof(szNoticeUrl), "211.39.144.158/NPCSound");
	sprintf(szWriteBuffer, "http://%s/%s.yul", szNoticeUrl, FileName);

	int cnt = 0;

	while(true)
	{
		ret_chk = connect_WEBdb(szWriteBuffer, szReadBuffer);

		if(ret_chk != ISAO_ERR_RECONNECT)
			break;

		if(cnt > 5)
			break;

		cnt++;
	}

	debug_fd2("GetWavFile() 보낸것 길이 : %d 내용 : %s ", strlen(szWriteBuffer), szWriteBuffer);
	debug_fd2("GetWavFile() 받은것 길이 : %d 내용 : %s ", strlen(szReadBuffer), szReadBuffer);

	switch(ret_chk)
	{
		case ISAO_ERR_WINSOCK_NOERR:
		fd2("From server: ---from--\n%s--end--\n ", szReadBuffer);
		break;
		case ISAO_ERR_WINSOCK_START:
		fd2("WSAStartup()에라");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_WINSOCK_VERSION:
		fd2("버전이 맞지 않음");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_TCP_CONNECT:
		fd2("connect() 접속 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_READ:
		fd2(" recv() 읽기 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_TIMEOUT:
		fd2("---------------- select() 타임아웃 실패");
		goto IsaoCheck_winsockERR;
	}

	ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode);
	switch(ret_chk)
	{
		case 100:
		case 101:
		case 102:
		goto IsaoCheck_Free;
		case ISAO_ERR_TCP_CONNECT:
		case ISAO_ERR_NONE_REEJCT:
		fd2("ISAO_ERR_NONE_REEJCT : 응답번호가 없음");
		goto IsaoCheck_Free;
	}


IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:
	return ret_chk;
}

int ISAOCHECK::read_ClanImage(char *clanname, char *filename)
{
	int dataSize = 0;
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer[65536];
	char szBMPName[255];

	ZeroMemory(szBMPName, sizeof(char) * 255);

	sprintf_s(szWriteBuffer, sizeof(szWriteBuffer), "http://%s//brnxcontent//%s.bmp", hostName1, filename);

	int cnt = 0;
	BOOL bret_chk = FALSE;

	while(true)
	{
		bret_chk = GetHttpRequest(szWriteBuffer, szReadBuffer, 65536, &dataSize);

		if(bret_chk)
			break;
		else
			cnt++;

		if(cnt > 5)
			break;

	}

	debug_fd2("read_ClanImage() 보낸것 길이 : %d 내용 : %s ", strlen(szWriteBuffer), szWriteBuffer);
	debug_fd2("read_ClanImage() 받은것 길이 : %d 내용 : bmp파일앞의2개만찍음 %c%c. ", strlen(szReadBuffer), szReadBuffer[0], szReadBuffer[1]);


	if((szReadBuffer[0] == 'B') && (szReadBuffer[1] == 'M'))
	{
		char server[4];
		char uniqueclannum[64];




		int nClanMarklen = 0;

		ZeroMemory(server, sizeof(server));
		nClanMarklen = lstrlen(filename);

		if(nClanMarklen == 9)
		{
			server[0] = filename[0];
			strcpy_s(uniqueclannum, sizeof(uniqueclannum), &filename[3]);
		}
		else
		{
			server[0] = filename[0];
			server[1] = filename[1];
			strcpy_s(uniqueclannum, sizeof(uniqueclannum), &filename[4]);
		}


		wsprintf(szBMPName, "%s_%s.%s", server, uniqueclannum, SAVE_EXE);
		clanDATA_save(szBMPName, szReadBuffer, dataSize);

		char path[128];
		char path2[128];
		int bmpSAVE(char *loadfname, char *savefname);
		wsprintf(path, "%s\\%s\\%s", SAVE_DIR, szConnServerName, szBMPName);
		wsprintf(path2, "%s\\%s\\%s_%s_16.%s", SAVE_DIR, szConnServerName, server, uniqueclannum, SAVE_EXE);

		bmpSAVE(path, path2);

		ret_chk = 1;
	}
	else
	{
		ret_chk = 2;
	}

	switch(ret_chk)
	{
		case ISAO_ERR_WINSOCK_NOERR:
		fd2("서버로 부터 읽은 dataSize : %d ", dataSize);
		break;
		case ISAO_ERR_WINSOCK_START:
		fd2("WSAStartup()에라");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_WINSOCK_VERSION:
		fd2("버전이 맞지 않음");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_TCP_CONNECT:
		fd2("connect() 접속 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_READ:
		fd2(" recv() 읽기 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_TIMEOUT:
		fd2("---------------- select() 타임아웃 실패");
		goto IsaoCheck_winsockERR;
	};


IsaoCheck_winsockERR:
	return ret_chk;
}

int ISAOCHECK::read_ClanImage2(char *clanname, char *filename, CLANINFO *ci)
{
	int dataSize = 0;
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer[65536];
	char szBMPName[255];

	ZeroMemory(szBMPName, sizeof(char) * 255);

	sprintf(szWriteBuffer, "http://%s//brnxcontent//%s.bmp", hostName1, filename);


	int cnt = 0;
	BOOL bret_chk = FALSE;
	while(true)
	{
		bret_chk = GetHttpRequest(szWriteBuffer, szReadBuffer, 65536, &dataSize);

		if(bret_chk)
			break;
		else
			cnt++;

		if(cnt > 5)
			break;
	}

	debug_fd2("read_ClanImage2() 보낸것 길이 : %d 내용 : %s ", strlen(szWriteBuffer), szWriteBuffer);
	debug_fd2("read_ClanImage2() 받은것 길이 : %d 내용 : bmp파일앞의2개만찍음 %c%c. ", strlen(szReadBuffer), szReadBuffer[0], szReadBuffer[1]);


	char path[128];
	char path1[128];

	if((szReadBuffer[0] == 'B') && (szReadBuffer[1] == 'M'))
	{
		wsprintf(szBMPName, "%s_%s.%s", ci->ClanInfoHeader.Gserver, ci->ClanInfoHeader.UniqueClaClanInfo_nNum, SAVE_EXE);
		clanDATA_save(szBMPName, szReadBuffer, dataSize);

		int bmpSAVE(char *loadfname, char *savefname);
		wsprintf(path, "%s\\%s\\%s", SAVE_DIR, szConnServerName, szBMPName);
		wsprintf(path1, "%s\\%s\\%s_%s_16.%s", SAVE_DIR, szConnServerName, ci->ClanInfoHeader.Gserver, ci->ClanInfoHeader.UniqueClaClanInfo_nNum, SAVE_EXE);

		bmpSAVE(path, path1);

		ret_chk = 1;
	}
	else
		ret_chk = 2;

	switch(ret_chk)
	{
		case ISAO_ERR_WINSOCK_NOERR:
		fd2("서버로 부터 읽은 dataSize : %d ", dataSize);
		break;
		case ISAO_ERR_WINSOCK_START:
		fd2("WSAStartup()에라");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_WINSOCK_VERSION:
		fd2("버전이 맞지 않음");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_TCP_CONNECT:
		fd2("connect() 접속 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_READ:
		fd2(" recv() 읽기 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_TIMEOUT:
		fd2("---------------- select() 타임아웃 실패");
		goto IsaoCheck_winsockERR;
	}

IsaoCheck_winsockERR:
	return ret_chk;
}

void ISAOCHECK::Convert_bin2HS(char *sorce, int len)
{
	int i, j, Len;
	for(i = 0; i < 30; i++)
	{
		if(fileDATA_HS[i]) delete fileDATA_HS[i];
	}

	HSsu = len / 2048;
	if(len % 2048) HSsu++;
	char byte0, byte1;


	for(j = 0; j < HSsu; j++)
	{
		if(j == (HSsu - 1))
		{
			fileDATA_HS[j] = new char[(len % 2048) * 2 + 1];
			Len = len % 2048;
		}
		else
		{
			fileDATA_HS[j] = new char[(2048 * 2) + 1];
			Len = 2048;
		}

		for(i = 0; i < Len; i++)
		{
			byte0 = *sorce & 0x0f;
			byte1 = (*sorce & 0xf0) >> 4;
			sorce++;

			if(byte0 < 10)
			{
				fileDATA_HS[j][i * 2 + 0] = byte0 + '0';
			}
			else
			{
				fileDATA_HS[j][i * 2 + 0] = (byte0 - 10) + 'A';
			}

			if(byte1 < 10)
			{
				fileDATA_HS[j][i * 2 + 1] = byte1 + '0';
			}
			else
			{
				fileDATA_HS[j][i * 2 + 1] = (byte1 - 10) + 'A';
			}
		}
		fileDATA_HS[j][i * 2] = 0;
	}
}



char *Convert_HS2bin(char *hs_buf, int len)
{
	char byte0, byte1;
	char* dest = new char[len];

	for(int i = 0; i < len; i++)
	{
		byte0 = hs_buf[i * 2 + 0];
		byte1 = hs_buf[i * 2 + 1];

		if(byte0 <= '9')
		{
			byte0 -= '0';
		}
		else
		{
			byte0 -= 'A';
			byte0 += 10;
		}

		if(byte1 <= '9')
		{
			byte1 -= '0';
		}
		else
		{
			byte1 -= 'A';
			byte1 += 10;
		}
		dest[i] = (byte1 << 4) | byte0;
	}
	return dest;
}



char *fileREAD(char *fileName, char *buf, int *len)
{
	DWORD dwAcess = 0;

	HANDLE hFile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile == INVALID_HANDLE_VALUE)
		return 0;

	*len = GetFileSize(hFile, NULL);

	if(*len == 0)
	{
		CloseHandle(hFile);
		return 0;
	}

	char *newBuf = nullptr;

	if(!buf)
		newBuf = new char[*len];
	else
		newBuf = buf;

	ReadFile(hFile, newBuf, *len, &dwAcess, NULL);

	CloseHandle(hFile);

	return newBuf;
}

int ISAOCHECK::write_ClanImageFile(char *fname)
{
	int i = 0;
	int dataSize = 0;
	int ret_chk = 0;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN * 5];
	char szReadBuffer[BUF_LEN * 5];

	char fileName[64];
	char OrigFName[] = "a.bmp";

	sprintf_s(fileName, sizeof(fileName), "%s\\%s\\%s", SAVE_DIR, szConnServerName, fname);

	int len = 0;
	char* fileBuf = fileREAD(fileName, NULL, &len);

	Convert_bin2HS(fileBuf, len);
	if(fileBuf)
		delete fileBuf;

	for(i = 0; i < HSsu; i++)
	{
		sprintf(szWriteBuffer, "POST http://%s/tjboyh/clan_insertClanImage.php?file_name=%s&file_HSsu=%d&file_cnt=%d&file_DATA=%s\r\n\r\n\r\n", hostName, OrigFName, HSsu, i + 1, fileDATA_HS[i]);

		while(true)
		{
			ret_chk = connect_WEBdb(szWriteBuffer, szReadBuffer);

			if(szReadBuffer[0] != 0)
				break;
		}
	}

	switch(ret_chk)
	{
		case ISAO_ERR_WINSOCK_NOERR:


		break;
		case ISAO_ERR_WINSOCK_START:
		fd2("WSAStartup()에라");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_WINSOCK_VERSION:
		fd2("버전이 맞지 않음");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_TCP_CONNECT:
		fd2("connect() 접속 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_READ:
		fd2(" recv() 읽기 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_TIMEOUT:
		fd2("---------------- select() 타임아웃 실패");
		goto IsaoCheck_winsockERR;
	};



IsaoCheck_winsockERR:
	return ret_chk;
}


int ISAOCHECK::WEBdb_Exam()
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[1024];
	char szReadBuffer[1024] = { 0, };


	sprintf(szWriteBuffer, "POST http://%s/tjboyh/ktj_login.php\r\n\r\n\r\n", hostName);
	ret_chk = connect_WEBdb(szWriteBuffer, szReadBuffer);


	fd2(" 웹 db에서 읽은것 %s ", szReadBuffer);

	return ret_chk;
}


void WEBdb_Exam()
{
	iCheck.init_HostName_Port("211.192.180.113", 80);
	iCheck.init(1, 20);
	iCheck.WEBdb_Exam();
}


int ISAOCHECK::read_sod2(char *usid, char *charname, char *gserver, int index, char *szSod2Buff)
{
	int dataSize = 0;
	int ret_chk = 0;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer[65536];
	memset(szSod2Buff, 0, sizeof(szSod2Buff));
	memset(szWriteBuffer, 0, sizeof(szWriteBuffer[BUF_LEN]));
	memset(szReadBuffer, 0, sizeof(szReadBuffer));


	sprintf(szWriteBuffer, "http://%s/brnxmainsv/sod2info.asp?userid=%s&chname=%s&gserver=%s&index=%d", hostName, usid, charname, gserver, index);


	int cnt = 0;
	BOOL bret_chk = FALSE;

	while(true)
	{
		bret_chk = GetHttpRequest(szWriteBuffer, szSod2Buff, 65536, &dataSize);

		if(bret_chk)
			break;
		else
			cnt++;

		if(cnt > 5)
			break;

	}

	switch(ret_chk)
	{
		case ISAO_ERR_WINSOCK_NOERR:
		fd2("서버로 부터 읽은 dataSize : %d ", dataSize);
		break;
		case ISAO_ERR_WINSOCK_START:
		fd2("WSAStartup()에라");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_WINSOCK_VERSION:
		fd2("버전이 맞지 않음");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_TCP_CONNECT:
		fd2("connect() 접속 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_READ:
		fd2(" recv() 읽기 실패");
		goto IsaoCheck_winsockERR;
		case ISAO_ERR_SSL_TIMEOUT:
		fd2("---------------- select() 타임아웃 실패");
		goto IsaoCheck_winsockERR;
	}

IsaoCheck_winsockERR:
	return ret_chk;
}


bool UTF8ToWeb(char *szUTF8, char *szWeb)
{
	int iCount = 0;
	char chHigh;
	char chLow;

	for(int i = 0; szUTF8[i] != 0; i++)
	{
		chHigh = chLow = 0;



		szWeb[iCount] = '%';
		iCount++;


		chHigh = (szUTF8[i] & 0xf0) >> 4;

		if((0 <= chHigh) && (chHigh <= 9))
		{
			szWeb[iCount] = '0' + chHigh;
			iCount++;
		}
		else
		{
			szWeb[iCount] = 'a' + chHigh - 0x0a;
			iCount++;
		}


		chLow = szUTF8[i] & 0x0f;

		if((0 <= chLow) && (chLow <= 9))
		{
			szWeb[iCount] = '0' + chLow;
			iCount++;
		}
		else
		{
			szWeb[iCount] = 'a' + chLow - 0x0a;
			iCount++;
		}

	}
	szWeb[iCount] = 0;

	return true;
}

bool MBCSToUTF8(char *szMBCS, char *szUTF8, int iMBCSCodePage)
{
	wchar_t wUniCode[1024]; memset(wUniCode, 0, sizeof(wUniCode));


	MultiByteToWideCharByCodePage(szMBCS, wUniCode, iMBCSCodePage);


	WideCharToMultiByteByCodePage(wUniCode, szUTF8, CP_UTF8);

	return true;
}

bool MultiByteToWideCharByCodePage(char *szMBCS, wchar_t *szUnicode, int iCodePage)
{
	int iLen = MultiByteToWideChar(iCodePage, 0, szMBCS, lstrlen(szMBCS), NULL, NULL);
	MultiByteToWideChar(iCodePage, 0, szMBCS, lstrlen(szMBCS), szUnicode, iLen);

	return true;
}



bool WideCharToMultiByteByCodePage(wchar_t *szUnicode, char *szMBCS, int iCodePage)
{
	int iLen = WideCharToMultiByte(iCodePage, 0, szUnicode, wcslen(szUnicode), NULL, NULL, NULL, NULL);
	WideCharToMultiByte(iCodePage, 0, szUnicode, wcslen(szUnicode), szMBCS, iLen, NULL, NULL);

	return true;
}

bool MBCSToWeb(char *szMBCS, char *szWeb, int iMBCSCodePage)
{
	char szUTF8[1024]; memset(szUTF8, 0, sizeof(szUTF8));
	MBCSToUTF8(szMBCS, szUTF8, iMBCSCodePage);
	UTF8ToWeb(szUTF8, szWeb);
	return true;
}