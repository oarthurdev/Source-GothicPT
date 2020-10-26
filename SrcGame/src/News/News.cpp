#include "News.h"
#include "File\File.h"
#include "smPacket.h"
#include <string>

extern int OpenBossTimeMin;

void News::welcome()
{
	try
	{
		File file("Chronos\\Welcome.ini");

		int bosstime = file.readInt("Welcome", "bosstime");
		std::string message = file.readString("Welcome", "message");

		if(player && player->lpsmSock)
		{
			TRANS_CHATMESSAGE packet;
			
			packet.code = OpCode::OPCODE_WHISPERMESSAGE;

			strcpy_s(packet.szMessage, sizeof(packet.szMessage), message.c_str());

			packet.size = 32 + lstrlen(packet.szMessage);
			packet.dwIP = 3;
			packet.dwObjectSerial = 0;

			player->lpsmSock->Send((char *)&packet, packet.size, TRUE);

			memset(packet.szMessage, 0, sizeof(packet.szMessage));

			wsprintf(packet.szMessage, "> Horário do boss: xx:%02d.", OpenBossTimeMin);

			player->lpsmSock->Send((char *)&packet, packet.size, TRUE);

		}
	}
	catch(FileException)
	{
	}
}

void News::title()
{
	try
	{
		File file("Chronos\\Welcome.ini");

		std::string message = file.readString("Title", "message");
		
		ChangeTitle packet;

		packet.size = sizeof(packet);
		packet.opcode = OpCode::CHANGE_WINDOW_TITLE;
		strcpy_s(packet.buffer, sizeof(packet.buffer), message.c_str());


		if(player && player->lpsmSock)
		{
			player->lpsmSock->Send((char*)&packet, packet.size, TRUE);
		}


	}
	catch(FileException)
	{
		
	}
}
