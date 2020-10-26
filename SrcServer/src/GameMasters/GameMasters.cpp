#include "GameMasters.h"
#include "Database\Database.h"
#include <iostream>
#include <memory>


using namespace std;


GameMasters gms;

GameMasters::GameMasters()
{
	clear();
}

GameMasters::~GameMasters()
{
}

bool GameMasters::readFromDatabase()
{
	clear();

	std::shared_ptr<Database> db = Database::GetConnection(DATABASEID_AccountDB);

	if(db->Open())
	{
		if(db->Prepare("SELECT * FROM GameMasters WHERE active =?"))
		{
			db->BindInputParameter("True", 1, PARAMTYPE_String);

			if(db->Execute())
			{
				while(true)
				{
					GameMaster *gamemaster = new GameMaster;

					db->GetData(&gamemaster->id, 0, 1, PARAMTYPE_Integer);
					db->GetData(gamemaster->accountId, 32, 2, PARAMTYPE_String);
					db->GetData(gamemaster->password, 30, 3, PARAMTYPE_String);
					db->GetData(&gamemaster->security, 0, 4, PARAMTYPE_Integer);
					db->GetData(&gamemaster->active, 0, 5, PARAMTYPE_Integer);


					users[cursor++] = gamemaster;

					if(!db->NextRow())
						break;
				}
			}
		}


		db->Close();
		return true;
	}

	return false;
}

AccountTypes GameMasters::getGameMaster(const std::string & accountId, const std::string & password) const
{

	for(unsigned int i = 0; i < MAX_GMS; i++)
	{
		if(users[i])
		{
			if(accountId.compare(users[i]->accountId) == 0)
			{
				if(password.compare(users[i]->password) == 0)
				{
					if(users[i]->active)
						return users[i]->security;
					else
						return AccountTypes::SEC_PLAYER;
				}
				else
					return AccountTypes::SEC_PLAYER;
			}
		}
	}

	return AccountTypes::SEC_PLAYER;
}

void GameMasters::print() const
{
	cout << endl;

	for(unsigned int i = 0; i < MAX_GMS; i++)
	{
		if(users[i])
		{
			cout << "id: [" << users[i]->id;
			cout << "] - AccountId: [" << users[i]->accountId;
			cout << "] - Password: [" << users[i]->password;
			cout << "] - security: [" << (int)users[i]->security << "]" << endl;
		}
	}

	cout << endl;
}



GameMasters* GameMasters::getInstance()
{
	return &gms;
}

void GameMasters::clear()
{
	for(unsigned int i = 0; i < MAX_GMS; i++)
	{
		if(users[i])
		{
			users[i] = nullptr;
		}
	}

	cursor = 0;

	ZeroMemory(users, sizeof(users));
}
