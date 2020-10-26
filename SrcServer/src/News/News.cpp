#include "News.h"
#include "File\File.h"
#include "smPacket.h"
#include <string>
#include <iostream>

using namespace std;

extern int OpenBossTimeMin;

void News::welcome()
{
	try
	{
		File file("configs\\Welcome.ini");

		int bosstime = file.readInt("Welcome", "bosstime");
		std::string message = file.readString("Welcome", "message");
	}
	catch(FileException &e)
	{
		cerr << "News::welcome() - " << e.what() << endl;
	}
}

void News::title()
{
	try
	{
		File file("configs\\Welcome.ini");

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
	catch(FileException &e)
	{
		cerr << "News::title() - " << e.what() << endl;
	}
}
