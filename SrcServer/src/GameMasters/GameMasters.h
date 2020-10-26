#ifndef GAME_MASTER_H
#define GAME_MASTER_H

#include <iostream>
#include <vector>
#include <string>
#include "smPacket.h"

using namespace std;

const int MAX_GMS = 100;

class GameMasters
{
private:

	struct GameMaster
	{
		int id;
		char accountId[32];
		char password[30];
		AccountTypes security;
		bool active;

		GameMaster()
		{
			id = -1;
			memset(accountId, 0, sizeof(accountId));
			memset(password, 0, sizeof(password));
			security = AccountTypes::SEC_PLAYER;
			active = false;
		}


	};

	GameMaster* users[MAX_GMS];
	int cursor;

public:
	GameMasters();
	~GameMasters();

	bool readFromDatabase();
	AccountTypes getGameMaster(const std::string &accountId, const std::string &password) const;

	void print() const;

	static GameMasters* getInstance();


private:
	void clear();
};


#endif //GAME_MASTER_H