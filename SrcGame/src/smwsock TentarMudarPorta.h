#ifndef	_SMWSOCK_HEADER
#define	_SMWSOCK_HEADER

#include "nettype.h"


#define _PS_TALE

#ifdef _PS_TALE

#define TCP_GAMEPORT		8180

#include "Language\\language.h"


#ifdef _LANGUAGE_BRAZIL					
#define TCP_SERVPORT		12874
#endif





#ifdef _W_SERVER

#ifdef _W_DATA_SERVER
#define CONNECTMAX			4096
#define	CONNECTMAX_MASK		4095
#else

#define CONNECTMAX			1024
#define	CONNECTMAX_MASK		1023
#endif


#else

#define CONNECTMAX			64
#define	CONNECTMAX_MASK		63

#endif


#else


#define CONNECTMAX			1024
#define	CONNECTMAX_MASK		1023

#endif



#define smSOCKBUFF_SIZE	8192

extern int		smTransThreadMode;
extern int		smTransTurbRcvMode;

class smWINSOCK;

struct smTHREADSOCK
{
	smWINSOCK *smMySock;

	SOCKET Sock;

	int RecvLen;
	int RecvCode;

	int BuffCnt;

	int NewData;
	int Sucess;
	int Sleep;
	int SendReady;

	DWORD dwExitThread;
	DWORD dwAcessTime;

	char Buff[smSOCKBUFF_SIZE + 256];
};


struct smTHREAD_ROUTE
{
	smTHREAD_ROUTE	*MyPoint;
	int Sleep;
	int TimeOut;
	smTHREADSOCK	*smThreadSock;
	DWORD dwSleepTime;

	HANDLE	hThread;
};

#define	ENC_PACKET_REC_MAX		16
#define	ENC_PACKET_REC_MASK		15

class smWINSOCK
{
public:
	smWINSOCK *MyPoint;
	DWORD	MyNum;

	SOCKET sock;

	void *ExtData1;
	void *ExtData2;
	void *ExtData3;
	void *ExtData4;

	HANDLE hRecvThread;
	HANDLE hSendThread;

	smTHREADSOCK smRecvState;
	smTHREADSOCK smSendState;

	smTHREAD_ROUTE	*lpsmRecvRoute;
	smTHREAD_ROUTE	*lpsmSendRoute;

	int online;
	int status;
	char szBuff[128];
	char szIPAddr[16];
	DWORD	dwPort;

	DWORD	dwLastRecvTime;
	DWORD	dwDeadLockTime;

	int	WaitReadMessage;
	int	PostReadMessage;

	int	PacketSendQueCnt;

	int	EncPacketSendCount;
	int	EncPacketRecvCount;

	int	EncRecvPackets[ENC_PACKET_REC_MAX];
	int	EncRecvPacketCnt;

	int ConnectDirection;

	SOCKADDR_IN local_sin;
	SOCKADDR_IN acc_sin;
	int acc_sin_len;

	DWORD dwRecvSusCount;

	int	RecvPacketCount;
	int	SendPacketCount;
	int	RecvPopCount;
	int	RecvPopErrorCount;
	int SendPacketErrorCount;
	int RecvPacketErrorCount;

	DWORD	dwEncPacketCode;
	BYTE	bEncXor;
	BYTE	bDecXor;


public:
	smWINSOCK();
	~smWINSOCK();

	int mesAccept(WPARAM wParam, LPARAM lParam);
	int mesReceve(LPARAM lParam);

	int Send(char *SendData, int len, int ImpMode = 0);

	int	CheckEncRecvPacket(int RecvCount);
	int	PushEncRecvPacket(int RecvCount);


	int CloseSocket();

	int ReconnectSock();

	int ConnectSock(char *szIP, WORD port);

	int CreateTransThread(int Mode);



};


extern smWINSOCK	smWSock[CONNECTMAX];

#define WSA_ACCEPT			(WM_USER + 0)
#define WSA_READ			(WM_USER + 1)
#define SWM_SENDSUCCESS     (WM_USER + 10)
#define SWM_RECVSUCCESS     (WM_USER + 11)
#define SWM_MCONNECT		(WM_USER + 12)
#define SWM_MDISCONNECT		(WM_USER + 13)



extern	int	smTransRecvErrorCnt;
extern	int	smTransSendErrorCnt;
extern	int	smTransRecvErrorDisCnt;
extern	int	smTransSendErrorDisCnt;
extern	int smTransClearErrorCnt;
extern	int smRcvBuffOverCount;


void InitBindSock(int port);

void InitGameSocket(int ThreadMode = 0);

void CloseBindSock();

char *smGetMyIp();

DWORD smGetMyIp2();

char *ConvStrIP(DWORD dwIP);


int WSAMessage_Accept(DWORD wParam, DWORD lParam);
int WSAMessage_Read(DWORD wParam, DWORD lParam);


smWINSOCK *smConnectSock(char *szIP, WORD port);

smWINSOCK *smConnectSock3(char *szIP, WORD port);


smWINSOCK *smConnectSock2(char *szIP, WORD port);

smWINSOCK *smFindSocket(char *szIP);

smWINSOCK *smFindSocket2(DWORD dwIP);

int smReconnectSock(smWINSOCK *lpsmSock);


int PushTransSendSocket(smWINSOCK *lpsmsock);

smWINSOCK *PopTransSendSocket();

int PushTransRecvSocket(smWINSOCK *lpsmsock);

smWINSOCK *PopTransRecvSocket();

int ClearTransQueSocket(smWINSOCK *lpsmsock);

int ClearPacketSendQue(smWINSOCK *lpsmSock);


int CheckLostTransThread();

int GetUseingSendThreadCount();

int GetUseingRecvThreadCount();


void smEnterCSectionSocket();

void smLeaveCSectionSocket();


int smCheckWaitMessage();
int smCheckWaitMessage(smWINSOCK *lpsmSock);


DWORD DecodePacket(BYTE *lpPacket, BYTE *lpDecBuff);

int	EncodePacket(DWORD dwKey, DWORD PacketCnt, BYTE *lpPacket, BYTE *lpEncBuff);


int	EncodePacket2(DWORD dwKey, DWORD PacketCnt, BYTE *lpPacket, BYTE *lpEncBuff, BYTE bEncXor);

DWORD DecodePacket2(BYTE *lpPacket, BYTE *lpDecBuff, BYTE bDecXor);




typedef DWORD(*LPFN_EncodePacket)(DWORD dwKey, DWORD PacketCnt, BYTE *lpPacket, BYTE *lpEncBuff);
typedef DWORD(*LPFN_DecodePacket)(BYTE *lpPacket, BYTE *lpDecBuff);

extern LPFN_EncodePacket	fnEncodePacket;
extern LPFN_DecodePacket	fnDecodePacket;

#define	POS_ENC_START	0x0
#define	POS_ENC_PACCODE 0xB
#define POS_ENC_XOR		0x74

#define	POS_DEC_START	0xA0
#define	POS_DEC_XOR		0x11A

#define	ENC_PACKET_ASM_SIZE	0x150

extern BYTE smwsock_EncodePacket_AsmCode[ENC_PACKET_ASM_SIZE];


#endif
