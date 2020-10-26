
#include "sinLinkHeader.h"



#include "..\\field.h"

cPCBANGPET cPCBANGPet;
int MatPcBangPetImage[4] = { 0, };


void cPCBANGPET::Init()
{

	Load();
}

void cPCBANGPET::Load()
{

	MatPcBangPetImage[0] = CreateTextureMaterial("Effect\\PcBangPet\\Pet_Phoenimin\\Pet_terry01.TGA", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatPcBangPetImage[1] = CreateTextureMaterial("Effect\\PcBangPet\\Pet_Phoenimin\\Pet_terry01.TGA", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatPcBangPetImage[2] = CreateTextureMaterial("Effect\\PcBangPet\\Pet_Phoenimin\\Pet_terry01.TGA", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatPcBangPetImage[3] = CreateTextureMaterial("Effect\\PcBangPet\\Pet_Phoenimin\\Pet_terry01.TGA", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

}

void cPCBANGPET::Release()
{

}

void cPCBANGPET::Draw()
{

}
void cPCBANGPET::Draw(POINT3D *pPosi, POINT3D *pAngle)
{

}

void cPCBANGPET::DrawText()
{


}

void cPCBANGPET::Close()
{

}

DWORD sinPcBangPetLoadingTime = 0;
void cPCBANGPET::Main()
{

	if(LoadingPet)
	{
		sinPcBangPetLoadingTime++;
		if(sinPcBangPetLoadingTime >= 70 * 3)
		{
			CheckPetData();
			LoadingPet = 0;
			sinPcBangPetLoadingTime = 0;

		}
	}

}

void cPCBANGPET::LButtonDown(int x, int y)
{

}

void cPCBANGPET::LButtonUp(int x, int y)
{

}

void cPCBANGPET::RButtonDown(int x, int y)
{

}

void cPCBANGPET::RButtonUp(int x, int y)
{

}






void cPCBANGPET::KeyDown()
{

}

int cPCBANGPET::GetFileData()
{

	return TRUE;
}

int cPCBANGPET::PetMessage(char *Id, int Index)
{

	return TRUE;
}

int cPCBANGPET::DrawPetMessage()
{

	return TRUE;
}

int cPCBANGPET::PetMessageHelp(char *Id)
{

	return TRUE;
}


int cPCBANGPET::CheckPetData()
{


	if(LoadingPet == 0)
	{
		LoadingPet = 1;
		return FALSE;

	}
	if(PetShow == 1 && PetKind == 0)
	{
		PetKind = 1;
	}




	ShowPet();
	PetShow = 1;

	return TRUE;
}



int cPCBANGPET::PetRandomNormalMessage()
{

	if(!PetKind || !PetShow)return FALSE;


	return TRUE;
}



int cPCBANGPET::PetRandomBattleMessage()
{
	int RandomNum = 0;
	int i = 0;

	return TRUE;
}


int cPCBANGPET::ShowPet()
{
	if(!PetKind) return FALSE;

	switch(PetKind)
	{
		case 1:
		g_HoPCBangAddPet(lpCurPlayer, HoPCBangPet::Type::BurstP);
		break;
		case 2:
		g_HoPCBangAddPet(lpCurPlayer, HoPCBangPet::Type::BurstS);
		break;
		case 3:
		g_HoPCBangAddPet(lpCurPlayer, HoPCBangPet::Type::BurstL);
		break;
		case 4:
		g_HoPCBangAddPet(lpCurPlayer, HoPCBangPet::Type::BurstD);
		break;
	}

	return TRUE;
}
int cPCBANGPET::ClosePet()
{

	PetShow = 0;
	g_HoPCBangDeletePet(lpCurPlayer);

	return TRUE;
}
int cPCBANGPET::PetOnOff(char *szBuff)
{

	return TRUE;
}
