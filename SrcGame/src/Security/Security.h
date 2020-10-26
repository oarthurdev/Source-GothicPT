#ifndef SECURITY_H
#define SECURITY_H

#include <string>
#include <MD5\MD5Wrapper.h>

class Security
{
private:
	std::string game_hash;

public:
	Security();
	~Security();


public:
	static Security* getInstance();

	std::string getGameHash() const;

private:
	bool generateGameHash();
};


#endif 
