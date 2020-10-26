#ifndef CLI_H
#define CLI_H

#include <string>

class CLI
{
private:
	bool *done;

	struct command
	{

	};

public:
	CLI();
	~CLI();

	bool run(bool *running);
	bool process(const std::string &cmd);

	void handleHelpCommand();
	void handleExitCommand();
	void handleShutdownCommand();
	void handleConnectedCommand();
	void handleKickCommand(const std::string &cmd);

	void handlePrintGMSCommand();
	void handleReloadGMSCommand();

public:
	static CLI* getInstance();


};


#endif //CLI_H