#include "Security.h"
#include <NetType.h>
#include <algorithm>

Security security;

Security::Security()
{
	game_hash.clear();

#ifndef _W_SERVER
	generateGameHash();
#else

#endif

}

Security::~Security()
{
}

Security* Security::getInstance()
{
	return &security;
}



std::string Security::getGameHash() const
{
	return game_hash;
}

bool Security::generateGameHash()
{
	extern int Client_Version;

	md5wrapper md5;

	std::string hash = md5.getHashFromFile("Game.exe");

	if(hash.size() != 32)
		return false;

	game_hash = md5.getHashFromString(hash + std::to_string(Client_Version));
	std::transform(game_hash.begin(), game_hash.end(), game_hash.begin(), toupper);

	return true;
}
