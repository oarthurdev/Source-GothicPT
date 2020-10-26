

#include "sinLinkHeader.h"


#define  PARTICLE7_HIT			0x00700001


int sinAssaParticle7KeyDown()
{



	POINT3D Posi = { lpCurPlayer->pX,lpCurPlayer->pY,lpCurPlayer->pZ };

	if(sinGetKeyClick('G'))
	{


	}

	return TRUE;
}


void sinAssaParticle7Process(cASSAEFFECT *pEffect)
{


	switch(pEffect->CODE)
	{
		case PARTICLE7_HIT:
		switch(pEffect->ActionIndex[0])
		{
			case 1:
			if(pEffect->Time < pEffect->Max_Time - 30)
				pEffect->Size.w += 5000;
			else pEffect->Size.w -= 5000;

			break;
		}
		break;
	}

}

int AssaParticle7_Hit(POINT3D *pPosi)
{

	for(int i = 0; i < 1; i++)
	{
		Assa = SetAssaEffect(90, "flare.tga", 0, pPosi, 5000);
		cAssaEffect[Assa]->Size.w = GetRandomPos(7000, 10000);
		cAssaEffect[Assa]->Size.h = GetRandomPos(500, 1200);

		cAssaEffect[Assa]->CODE = PARTICLE7_HIT;
		cAssaEffect[Assa]->NotFadeIn = 1;

		cAssaEffect[Assa]->ActionIndex[0] = 1;





	}

	return TRUE;
}

