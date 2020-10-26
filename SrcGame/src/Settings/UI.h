#ifndef GUI_SETTINGS_H
#define GUI_SETTINGS_H

#include <vector>
#include <windows.h>
#include <string>
#include "Settings.h"

class SettingsUI
{
private:
	bool status;


public:
	SettingsUI();
	~SettingsUI();

	void open();
	void close();
	
	bool getStatus() const;


	static SettingsUI* getInstance()
	{
		extern SettingsUI settingsUI;

		return &settingsUI;
	}
};


#endif 
