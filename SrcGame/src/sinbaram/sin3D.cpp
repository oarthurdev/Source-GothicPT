

#include "sinLinkHeader.h"

#define  _ASSA_EFFECT_START_

cSIN3D cSin3D;

int sinStarParticleKey = 0;
int TestCount2 = 0;

cSIN3D::cSIN3D()
{

}
cSIN3D::~cSIN3D()
{

}

void cSIN3D::Init()
{
	char *PartBlue = "PartBlue";
	char *PartGreen = "PartGreen";
	char *PartRed = "PartRed";
	char *Partyellow = "Partyellow";
	char szPath[128];

	sinEffect2D_Line = CreateTextureMaterial("Image\\SinImage\\Effect\\Return1.tga", 0, 0, 0, 0, SMMAT_BLEND_LAMP);


	for(int i = 1; i < 5; i++)
	{
		wsprintf(szPath, "image\\Sinimage\\Effect\\Particle\\%s%d.tga", Partyellow, i);
		MatParticleGold[i - 1] = CreateTextureMaterial(szPath, 0, 0, 0, 0, SMMAT_BLEND_LAMP);

	}

	Rage_Of_SinBaRam = smASE_Read("Image\\SinImage\\Effect\\test.ase");

	MatWideCircle = CreateTextureMaterial("image\\Sinimage\\Effect\\Effect2D\\WideCircle.tga", 0, 0, 0, 0, SMMAT_BLEND_LAMP);


	MatEffectLine = CreateTextureMaterial("image\\Sinimage\\Effect\\Effect2D\\YellowLine.tga", 0, 0, 0, 0, SMMAT_BLEND_LAMP);

	MatParticle1 = CreateTextureMaterial("image\\Sinimage\\Effect\\Particle\\Particle1.tga", 0, 0, 0, 0, SMMAT_BLEND_LAMP);

	InitInterEffect();
	InitEffect2();
	sinInitSkillEffect();
	sinInitPublicEffect();
#ifdef   _ASSA_EFFECT_START_	
	InitAssaEffect();
#endif
	InitYameEffect();


}

void cSIN3D::Load()
{

}

void cSIN3D::Release()
{

}

void cSIN3D::Draw(int x, int y, int z, int ax, int ay, int az)
{




	POINT3D Posi = { x,y,z };
	POINT3D Angle = { ax , ay , az };
	d3ddev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
#ifdef   _ASSA_EFFECT_START_	
	DrawAssaEffect(&Posi, &Angle);
#endif
	sinDrawEffect(x, y, z, ax, ay, az);
	sinDrawEffect2(x, y, z, ax, ay, az);
	DrawYameEffect(&Posi, &Angle);
	cHelpPet.Draw(&Posi, &Angle);

	d3ddev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);






}

void cSIN3D::Main()
{
	sinActiveEffect();
	sinActiveInterEffect();
	InterEffectAging2Process();

	sinActiveEffect2();


#ifdef   _ASSA_EFFECT_START_	
	MainAssaEffect();
#endif
	MainYameEffect();

}

void cSIN3D::Close()
{
	CloseYameEffect();
}

void cSIN3D::LButtonDown(int x, int y)
{


}

void cSIN3D::LButtonUp(int x, int y)
{

}

void cSIN3D::RButtonDown(int x, int y)
{

}

void cSIN3D::RButtonUp(int x, int y)
{

}


void cSIN3D::KeyDown()
{
	POINT3D Posi;
	Posi.x = (int)lpCurPlayer->pX;
	Posi.y = (int)lpCurPlayer->pY + 13000;
	Posi.z = (int)lpCurPlayer->pZ;



	if(smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
	{
		ParticleTestKey();
		sinSkillTestKey();
		sinPublicEffectTestKey();

	#ifdef   _ASSA_EFFECT_START_	
		AssaEffectKeyDown();
	#endif
		YameEffectKeyDown();









		if(sinGetKeyClick('A'))
		{
			sinReleaseEffect();
			TestCount2 = 0;




		}

















	}
}


int cSIN3D::sinDrawTexture(int x, int y, int z, int AngleX, int AngleY, int AngleZ, smFACE2D *lpFace, int sinAngle)
{

	d3ddev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	smRender.Init();

	smMaterialGroup->smMaterial[lpFace->MatNum].TwoSide = FALSE;

	smRender.SetMaterialGroup(smMaterialGroup);



	smMaterialGroup->SetMaterialAnimFrame(&smMaterial[lpFace->MatNum], 2);


	smRender.SetCameraPosi(x, y, z, AngleX, AngleY, AngleZ);

	if(sinAngle)
	{
		if(smRender.AddFace2D(lpFace, sinAngle))
		{
			smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
			smRender.ClipRendFace();
			smRender.GeomVertex2D(FALSE);
			smRender.RenderD3D();

		}

	}
	else
	{
		if(smRender.AddFace2D(lpFace))
		{
			smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
			smRender.ClipRendFace();
			smRender.GeomVertex2D(FALSE);
			smRender.RenderD3D();

		}
	}

	return TRUE;
}

