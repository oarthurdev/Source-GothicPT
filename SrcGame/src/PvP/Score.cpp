#include "Score.h"
#include <string>
#include "FontImage.h"
#include "smLib3d\smDsx.h"
#include "playmain.h"
#include "character.h"
#include "field.h"


extern int haSiegeBoardFlag;

Score::Score()
{
	}

Score::~Score()
{

}




void Score::sendAlert()
{
	unsigned int stage = StageField[lpCurPlayer->OnStageField]->FieldCode;

	extern BOOL bReiPVP;

	static unsigned int tick = 0;
	static bool sent = false;

	if(stage == 33 && bReiPVP)
	{

		if((GetTickCount() - tick) > 120000 && !sent)
		{
			smTRANS_COMMAND smPacket;
			smPacket.code = OpCode::SEND_ALERT_PVP;
			smPacket.WParam = 0;
			smPacket.EParam = 0;
			smPacket.size = sizeof(smPacket);

			extern smWINSOCK *smWsockDataServer;

			if(smWsockDataServer)
			{
				smWsockDataServer->Send((char *)&smPacket, smPacket.size, TRUE);
			}

			tick = GetTickCount();
			sent = true;
		}
	}
	else
	{
		if((GetTickCount() - tick) > 120000 && sent)
		{
			sent = !sent;
		}
	}


}

bool Score::drawScore()
{
	char* rankBp = "";
	DrawFontImage("Battle Points: ", smScreenWidth / 3 - 10, 20, D3DCOLOR_RGBA(16, 218, 0, 255), 0.7f);
	DrawFontImage(const_cast<char*>(std::to_string(lpCurPlayer->sBlessCastle_Damage[1]).c_str()), smScreenWidth / 3 - -120, 20, D3DCOLOR_RGBA(220, 0, 0, 255), 0.7f);

	if (lpCurPlayer->sBlessCastle_Damage[1] >= 0) {
		rankBp = "Aprendiz";
	}
	if (lpCurPlayer->sBlessCastle_Damage[1] >= 50) {
		rankBp = "Iniciante";
	}
	if (lpCurPlayer->sBlessCastle_Damage[1] >= 150) {
		rankBp = "Veterano";
	}
	if (lpCurPlayer->sBlessCastle_Damage[1] >= 300) {
		rankBp = "Executor";
	}
	if (lpCurPlayer->sBlessCastle_Damage[1] >= 700) {
		rankBp = "Desafiante";
	}
	if (lpCurPlayer->sBlessCastle_Damage[1] >= 1000) {
		rankBp = "Deus da guerra";
	}
	DrawFontImage(rankBp, smScreenWidth / 3 - 10, 45, D3DCOLOR_RGBA(255, 24, 0, 255), 0.7f);

	return true;
}

bool Score::draw()
{
	unsigned int stage = StageField[lpCurPlayer->OnStageField]->FieldCode;
	bool result = false;

	if(stage == 33 && !haSiegeBoardFlag)
	{
		drawScore();

		result = true;
	}


	sendAlert();

	return result;
}
