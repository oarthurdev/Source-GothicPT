#ifndef LOG_H
#define LOG_H

#include <Windows.h>

#define LOG_ENABLED

#define LOG_ERROR 1
#define LOG_GAME 2
#define LOG_SERVER 3
#define LOG_DEBUG 4


#define GameLogFile "game.log"
#define ServerLogFile "server.log"
#define ErrorLogFile "error.log"
#define DebugLogFile "debug.log"


class Log
{
private:


public:
	Log();
	~Log();

	void output(DWORD type, char* msg, ...);
	void dumpPacket(char* pckname, BYTE* buffer, int size);

	static Log* getInstance();
	


};


#endif //LOG_H