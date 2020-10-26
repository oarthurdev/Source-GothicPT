#include "UI.h"
#include "smLib3d\smDsx.h"
#include "smLib3d\smType.h"
#include "smLib3d\smTexture.h"
#include "drawsub.h"
#include "Settings\Settings.h"

#include "drawsub.h"

SettingsUI settingsUI;

SettingsUI::SettingsUI()
{
	status = false;
}

SettingsUI::~SettingsUI()
{

}

void SettingsUI::open()
{
	static unsigned long long timer = 0;

	if((GetTickCount() - timer) > 2000)
	{
		
		int SetMousePlay(int flag);
		SetMousePlay(0);

		status = true;

		timer = GetTickCount();
	}
	else
	{
		int AddChatBuff(char *szMsg);

		AddChatBuff("> Aguarde 2 segundos para abrir o menu novamente.");
	}

}

void SettingsUI::close()
{
	status = false;
}

bool SettingsUI::getStatus() const
{
	return status;
}
