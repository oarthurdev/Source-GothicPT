#include <windows.h>
#include <stdio.h>
#include "Util.h"

void MiLae_Debug_txt(char *fmt, ...)
{
	char Buff[4096];
	ZeroMemory(Buff, sizeof(Buff));

	va_list args;
	HANDLE hFile;
	DWORD dwAcess = 0;

	hFile = CreateFile("game_debug.txt", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
					   NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile == INVALID_HANDLE_VALUE) return;




	va_start(args, fmt);
	vsprintf(Buff, fmt, args);
	va_end(args);

	strcat(Buff, "\r\n");
	SetFilePointer(hFile, 0, NULL, FILE_END);
	WriteFile(hFile, Buff, lstrlen(Buff), &dwAcess, NULL);
	CloseHandle(hFile);

}

void ErrorMessage(char *msg, ...)
{
	char Buff[4096];
	va_list args;

	va_start(args, msg);
	vsprintf(Buff, msg, args);
	va_end(args);

	MessageBox(NULL, Buff, "Error Message", MB_OK | MB_ICONWARNING);


}

void ReadScript(char *filename)
{
}

VOID SocketError(HWND Wnd, DWORD err)
{
#define CAPTION  "WinSock Error"
	char szTemp[256];
	switch(err)
	{
		case 10004:
		MessageBox(Wnd, CAPTION, "블럭킹 윈속이 WSACancelBlockingCall 함수에서  취소되었습니다", MB_OK | MB_ICONSTOP);
		break;
		case 10009:
		MessageBox(Wnd, CAPTION, "잘못된 기술자(소켓 핸들)이다", MB_OK | MB_ICONSTOP);
		break;
		case 10013:
		MessageBox(Wnd, CAPTION, "브로드캐스트 어드레스를 위한 데이터그램 소켓의  접속시도가 setsockopt 함수로 SO_BROADCAST가  설정되어있지 않은 상태에서 실패 했습니다.", MB_OK | MB_ICONSTOP);
		break;
		case 10014:
		MessageBox(Wnd, CAPTION, "name 또는 namelen 매개변수가 올바른 형태가 아닙니다.", MB_OK | MB_ICONSTOP);
		break;
		case 10022:
		MessageBox(Wnd, CAPTION, "accept 하기 전에 listen 함수가 불려지지 않았습니다", MB_OK | MB_ICONSTOP);
		break;
		case 10024:
		MessageBox(Wnd, CAPTION, "새로운 소켓에 할당하기 위한 소켓 기술자가 더 이상 남아있지 않습니다", MB_OK | MB_ICONSTOP);
		break;
		case 10035:
		MessageBox(Wnd, CAPTION, "소켓 함수가 비블럭킹 모드로 동작중이다", MB_OK | MB_ICONSTOP);
		break;
		case 10036:
		MessageBox(Wnd, CAPTION, "블록화 함수가 호출 되는 동안 부적절한 소켓 함수가  호출되었다 ", MB_OK | MB_ICONSTOP);
		break;
		case 10037:
		MessageBox(Wnd, CAPTION, "이미 완료된 비동기 명령에 대한 취소가 시도됨 ", MB_OK | MB_ICONSTOP);
		break;
		case 10038:
		MessageBox(Wnd, CAPTION, "지정한 기술자가 소켓 기술자가 아닙니다", MB_OK | MB_ICONSTOP);
		break;
		case 10039:
		MessageBox(Wnd, CAPTION, "해당 함수에 목적지 어드레스가 필요하지만 제공되지 않았음", MB_OK | MB_ICONSTOP);
		break;
		case 10040:
		MessageBox(Wnd, CAPTION, "수신된 메시지가 지정된 버퍼에 저장하기에 너무 커서 손실 되었습니다", MB_OK | MB_ICONSTOP);
		break;
		case 10041:
		MessageBox(Wnd, CAPTION, "지정된 프로토콜이 잘못되었거나 이 소켓에 대해서  잘못된 형식입니다", MB_OK | MB_ICONSTOP);
		break;
		case 10042:
		MessageBox(Wnd, CAPTION, "알 수 없는 옵션이거나, 지원지지 않는 옵션을 사용했습니다. ", MB_OK | MB_ICONSTOP);
		break;
		case 10043:
		MessageBox(Wnd, CAPTION, "지정된 프로토콜이 지원되지 않는 형식입니다. ", MB_OK | MB_ICONSTOP);
		break;
		case 10044:
		MessageBox(Wnd, CAPTION, "지정된 소켓 타입이 지정한 어드레스 체계에서 지원되지 않는 형식입니다", MB_OK | MB_ICONSTOP);
		break;
		case 10045:
		MessageBox(Wnd, CAPTION, "socket이 연결지향형 서비스(SOCK_STREAM)형태가 아닙니다. ex) listen이 UDP socket에서 호출 ", MB_OK | MB_ICONSTOP);
		break;
		case 10046:
		MessageBox(Wnd, CAPTION, "지정된 프로토콜 체계가(PF_*) 지원되지 않습니다", MB_OK | MB_ICONSTOP);
		break;
		case 10047:
		MessageBox(Wnd, CAPTION, "지정된 어드레스 체계가(AF_*) 지원되지 않습니다", MB_OK | MB_ICONSTOP);
		break;
		case 10048:
		MessageBox(Wnd, CAPTION, "지정한 어드레스(IP)가 이미 사용중이다", MB_OK | MB_ICONSTOP);
		break;
		case 10049:
		MessageBox(Wnd, CAPTION, "지정된 어드레스는 로컬 머신에서 사용할 수가 없다", MB_OK | MB_ICONSTOP);
		break;
		case 10050:
		MessageBox(Wnd, CAPTION, "네트웍 서브 시스템에 에러가 발생했습니다", MB_OK | MB_ICONSTOP);
		break;
		case 10051:
		MessageBox(Wnd, CAPTION, "원격 시스템까지 네트웍이 도달할 수 없습니다", MB_OK | MB_ICONSTOP);
		break;
		case 10052:
		MessageBox(Wnd, CAPTION, "연산이 진행되고 있는 도중 접속이 끊겨버렸습니다", MB_OK | MB_ICONSTOP);
		break;
		case 10053:
		MessageBox(Wnd, CAPTION, "연결이 out-of-band나 다른 실패 때문에 끊어져 버렸습니다.", MB_OK | MB_ICONSTOP);
		break;
		case 10054:
		MessageBox(Wnd, CAPTION, "원격 연결지에서 'hard'나 'abortive' 종료를 수행해서 리셋되었습니다.", MB_OK | MB_ICONSTOP);
		break;
		case 10055:
		MessageBox(Wnd, CAPTION, "윈도우 소켓 시스템의 버퍼 공간이 모자라거나, 애플리케이션에 의해 API에게 제공된 공간이 너무 작아서 요청된 정보를 저장 할 수가 없음", MB_OK | MB_ICONSTOP);
		break;
		case 10056:
		MessageBox(Wnd, CAPTION, "지정된 소켓이 이미 연결 되어 있음", MB_OK | MB_ICONSTOP);
		break;
		case 10057:
		MessageBox(Wnd, CAPTION, "지정된 소켓이 이미 연결 되어 있지 않음", MB_OK | MB_ICONSTOP);
		break;
		case 10058:
		MessageBox(Wnd, CAPTION, "소켓이 셧다운(shutdown()) 되었습니다.", MB_OK | MB_ICONSTOP);
		break;
		case 10059:
		MessageBox(Wnd, CAPTION, "지정한 함수에 대한 인자가 너무 많음", MB_OK | MB_ICONSTOP);
		break;
		case 10060:
		MessageBox(Wnd, CAPTION, "접속 시도가 시간초과 되었습니다.", MB_OK | MB_ICONSTOP);
		break;
		case 10061:
		MessageBox(Wnd, CAPTION, "접속시도가 강제로 종료되었습니다", MB_OK | MB_ICONSTOP);
		case 10062:
		MessageBox(Wnd, CAPTION, "WSAELOOP ERROR", MB_OK | MB_ICONSTOP);
		break;
		case 10063:
		MessageBox(Wnd, CAPTION, "WSAENAMETOOLONG ERROR", MB_OK | MB_ICONSTOP);
		break;
		case 10064:
		MessageBox(Wnd, CAPTION, "원경호스트가 다운 되었음", MB_OK | MB_ICONSTOP);
		break;
		case 10065:
		MessageBox(Wnd, CAPTION, "네트웍 시스템 장애 등에 의해서 원격호스트까지도 달 할 수 없습니다.", MB_OK | MB_ICONSTOP);
		break;
		case 10091:
		MessageBox(Wnd, CAPTION, "네트워크 서브 시스템이 아직 통신할 준비가 되어 있지 않음(WSAStartup()이 반환)", MB_OK | MB_ICONSTOP);
		break;
		case 10092:
		MessageBox(Wnd, CAPTION, "요청한 윈도우즈 소켓 버전이 현재 윈도우즈 소켓 시스템에서 지원하지 않습니다.", MB_OK | MB_ICONSTOP);
		break;
		case 10093:
		MessageBox(Wnd, CAPTION, "이 함수를 사용하기 전에 성공적인 WSAStartup 함수의 호출이 없었습니다.", MB_OK | MB_ICONSTOP);
		break;
		case 11001:
		MessageBox(Wnd, CAPTION, "호스트를 찾아낼 수 없습니다.", MB_OK | MB_ICONSTOP);
		break;
		case 11002:
		MessageBox(Wnd, CAPTION, "요청된 정보가 발견되지 않음", MB_OK | MB_ICONSTOP);
		break;
		case 11003:
		MessageBox(Wnd, CAPTION, "회복할 수 없는 에러 발생", MB_OK | MB_ICONSTOP);
		break;
		case 11004:
		MessageBox(Wnd, CAPTION, "잘못된 이름(name)으로 아무런 데이터가 기록되지 않았습니다", MB_OK | MB_ICONSTOP);
		break;
		default:
		wsprintf(szTemp, "알수없는 에러입니다\n에러번호 : %d", err);
		MessageBox(Wnd, CAPTION, szTemp, MB_OK | MB_ICONSTOP);
		break;
	}
}
