

#include "sinLinkHeader.h"

#define ASSA_TEST_CODE		0x00010000
#define ASSA_TEST_CODE2		0x00010001
#define ASSA_TEST_CODE3		0x00010002


int AssaParticle_TEST(smCHAR *pChar, char *FileName)
{



	return TRUE;
}


int AssaParticle_TEST2(POINT3D *pPosi, char *FileName)
{

	Assa = SetAssaEffect(0, "GreatHealing.ASE", 0, pPosi, 15000);
	cAssaEffect[Assa]->AniMaxCount = 30;
	cAssaEffect[Assa]->AniDelayTime = 5;

	return TRUE;
}


int sinAssaParticleTestKeyDown()
{



	POINT3D Posi = { lpCurPlayer->pX,lpCurPlayer->pY,lpCurPlayer->pZ };


	return TRUE;
}


void sinAssaParticleTestProcess(cASSAEFFECT *pEffect)
{

	switch(pEffect->CODE)
	{
		case ASSA_TEST_CODE:
		if(pEffect->Time <= 50)
		{

		}

		break;
		case ASSA_TEST_CODE2:

		break;
		case ASSA_TEST_CODE3:
		break;
	}

}

