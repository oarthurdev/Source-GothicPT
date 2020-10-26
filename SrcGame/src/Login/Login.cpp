#include "Login.h"
#include <string>
#include <smPacket.h>
#include <netplay.h>
#include <Security\Security.h>
#include <algorithm>

#pragma comment(lib, "iphlpapi")    
#include <iphlpapi.h>               

LoginResult	requestLogin(const std::string &username, const std::string &password)
{
	LoginPacket	packet;

	PIP_ADAPTER_INFO AdapterInfo;
	DWORD dwBufLen = sizeof(AdapterInfo);

	AdapterInfo = (IP_ADAPTER_INFO *)malloc(sizeof(IP_ADAPTER_INFO));

	if(GetAdaptersInfo(AdapterInfo, &dwBufLen) == ERROR_BUFFER_OVERFLOW)
	{
		AdapterInfo = (IP_ADAPTER_INFO *)malloc(dwBufLen);
	}

	if(GetAdaptersInfo(AdapterInfo, &dwBufLen) == NO_ERROR)
	{
		PIP_ADAPTER_INFO info = AdapterInfo; 
		sprintf_s(packet.mac, sizeof(packet.mac), "%02X-%02X-%02X-%02X-%02X-%02X", info->Address[0], info->Address[1], info->Address[2], info->Address[3], info->Address[4], info->Address[5]);
	}

	free(AdapterInfo);

	packet.size = sizeof(packet);
	packet.code = OpCode::OPCODE_ID_GETUSERINFO;

	strcpy_s(packet.account, sizeof(packet.account), username.c_str());
	strcpy_s(packet.password, sizeof(packet.password), password.c_str());
	strcpy_s(packet.hash, sizeof(packet.hash), Security::getInstance()->getGameHash().c_str());

	if(smWsockDataServer)
	{
		smWsockDataServer->Send((char *)&packet, packet.size, TRUE);
		return LoginResult::OK;
	}

	return LoginResult::FAILED_CONNECTION;

	
}
