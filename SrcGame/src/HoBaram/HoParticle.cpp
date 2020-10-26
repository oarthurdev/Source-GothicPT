#include "..\\particle.h"
#include "..\\HoBaram\\HoLinkHeader.h"



int EngineFps = 70;
HoParticle::HoParticle()
{
	Age = -1.0f;

	Color.r = 255.f;
	Color.g = 0.0f;
	Color.b = 0.0f;
	Color.a = 255.f / 2;
	TimeCount = 0;
}

HoParticle::~HoParticle()
{


}


bool HoParticle::Main()
{
	TimeCount++;
	if(TimeCount >= 1)
	{
		if(Age + TimeCount / EngineFps >= LifeTime)
		{
			Age = -1.0f;
			return false;
		}
		else
		{
			Age += TimeCount / EngineFps;
			PrevLocation = Location;
			Location.x += Velocity.x*(TimeCount);
			Location.y += Velocity.y*(TimeCount);
			Location.z += Velocity.z*(TimeCount);

			D3DXVECTOR3	initGravity;
			initGravity.x = 0.0f;
			initGravity.y = -9.8f;
			initGravity.z = 0.0f;

			Velocity.x += (initGravity.x * Gravity * TimeCount);
			Velocity.y += (initGravity.y * Gravity * TimeCount);
			Velocity.z += (initGravity.z * Gravity * TimeCount);

			Color.r += ColorDelta.r * (TimeCount);
			Color.g += ColorDelta.g * (TimeCount);
			Color.b += ColorDelta.b * (TimeCount);

			Alpha += AlphaDelta * (TimeCount);
			Size += SizeDelta * (TimeCount);
			Gravity += GravityDelta * (TimeCount);



		}
		TimeCount = 0;
	}
	return true;
}


HoParticleSystem::HoParticleSystem() : HoEffectObject()
{
	make_pSu = MAX_PARTICLES;

	AutoDieFlag = TRUE;

	ColorStart.r = 0.0f;
	ColorStart.g = 0.0f;
	ColorStart.b = 0.0f;





	ColorEnd.r = 0.0f;
	ColorEnd.g = 0.0f;
	ColorEnd.b = 0.0f;

	AlphaStart = 0.0f;

	AlphaEnd = 0.0f;

	SizeStart = 0.0f;

	SizeEnd = 0.0f;

	Speed = 0.0f;


	Theta = 180.0f;

	Life = 1.0f;


	GravityStart = 0.0f;

	GravityEnd = 0.0f;

	ParticlesPerSec = EngineFps + 1;

	Age = 0.0f;
	EmissionResidue = 0.0f;



	Direction.x = 0.0f;
	Direction.y = 0.0f;
	Direction.z = 0.0f;

	Location.x = 0.0f;
	Location.y = 0.0f;
	Location.z = 0.0f;

	PrevLocation.x = 0.0f;
	PrevLocation.y = 0.0f;
	PrevLocation.z = 0.0f;

	TimeCount = 0.0f;

	ParticlesPerSec = 0;


	Location.x = 0;
	Location.y = 0;
	Location.z = 0;


	PrevLocation.x = Location.x;
	PrevLocation.y = Location.y;
	PrevLocation.z = Location.z;
}

HoParticleSystem::~HoParticleSystem()
{

}

void HoParticleSystem::TranslateWorld(int x, int y, int z)
{
	PrevLocation = Location;
	Location.x = (float)x;
	Location.y = (float)y;
	Location.z = (float)z;
}


int HoParticleSystem::Start(int x, int y, int z, int matNum, int particleCode)
{
	WorldX = (float)x;
	WorldY = (float)y;
	WorldZ = (float)z;

	LocalX = 0;
	LocalY = 0;
	LocalZ = 0;

	make_pSu = MAX_PARTICLES;
	ParticleCode = particleCode;


	switch(particleCode)
	{
		case MONSTER_FORZENMIST_SHOT2:
		case SKILL_METEO:
		case MONSTER_PIGON_SHOT1:
		{
			StartFlag = TRUE;
			MaterialNum = matNum;
			AutoDieFlag = FALSE;

			ColorStart.r = 255.0f;
			ColorStart.g = 100;
			ColorStart.b = 50.0f;

			ColorEnd.r = 255.0f;
			ColorEnd.g = 50.0f;
			ColorEnd.b = 50.0f;

			SizeStart = 12.0f;
			SizeEnd = 1.0f;

			if(particleCode == MONSTER_FORZENMIST_SHOT2)
			{
				ColorStart.r = 50.0f;
				ColorStart.g = 70.0f;
				ColorStart.b = 255.0f;

				ColorEnd.r = 50.0f;
				ColorEnd.g = 50.0f;
				ColorEnd.b = 255.0f;

				SizeStart = 40.0f;
				SizeEnd = 25.0f;
			}
			AlphaStart = 200.0f;
			AlphaEnd = 0.0f;



			Speed = 200.0f;
			Theta = 180.0f;


			Life = 0.10f;
			GravityStart = 0.0f;
			GravityEnd = 0.0f;

			ParticlesPerSec = EngineFps * 10;

			Age = 0.9f;

			Direction.x = 0.0f;
			Direction.y = 0.0f;
			Direction.z = 0.0f;

			TimeCount = 0.0f;

			Location.x = (float)x;
			Location.y = (float)y;
			Location.z = (float)z;

			PrevLocation.x = (float)Location.x;
			PrevLocation.y = (float)Location.y;
			PrevLocation.z = (float)Location.z;
		}
		break;

		case MONSTER_MEPHIT_SHOT1:
		case MONSTER_MEPHIT_SHOT2:
		case MONSTER_IMP_SHOT1:
		{
			StartFlag = TRUE;
			MaterialNum = matNum;
			AutoDieFlag = FALSE;

			ColorStart.r = 230.0f;
			ColorStart.g = 250.f;
			ColorStart.b = 250.0f;





			ColorEnd.r = 0.0f;
			ColorEnd.g = 0.0f;
			ColorEnd.b = 0.0f;


			AlphaStart = 200.0f;

			AlphaEnd = 0.0f;

			SizeStart = 4.0f;
			if(MONSTER_MEPHIT_SHOT2 == particleCode)	SizeStart = 6.0f;


			SizeEnd = 0.5f;

			Speed = 100.0f;


			Theta = 180.0f;


			Life = 0.005f;


			GravityStart = 0.0f;

			GravityEnd = 0.0f;

			ParticlesPerSec = EngineFps * 10;

			Age = 0.9f;



			Direction.x = 0.0f;
			Direction.y = 0.0f;
			Direction.z = 0.0f;

			TimeCount = 0.0f;

			Location.x = (float)x;
			Location.y = (float)y;
			Location.z = (float)z;

			PrevLocation.x = (float)Location.x;
			PrevLocation.y = (float)Location.y;
			PrevLocation.z = (float)Location.z;
		}
		break;

		case MONSTER_IMP_SHOT2:
		case EFFECT_FIRE_CRACKER:
		{
			StartFlag = TRUE;
			MaterialNum = matNum;
			AutoDieFlag = FALSE;

			ColorStart.r = 230.0f;
			ColorStart.g = 250.f;
			ColorStart.b = 250.0f;





			ColorEnd.r = 0.0f;
			ColorEnd.g = 0.0f;
			ColorEnd.b = 0.0f;


			AlphaStart = 200.0f;

			AlphaEnd = 0.0f;


			if(particleCode == MONSTER_IMP_SHOT2)
			{
				SizeStart = 6.0f;


				SizeEnd = 2.5f;
			}
			else if(EFFECT_FIRE_CRACKER == particleCode)
			{
				SizeStart = 3.0f;
				SizeEnd = 1.5f;
			}

			Speed = 100.0f;



			Theta = 180.0f;


			Life = 0.005f;


			GravityStart = 0.0f;

			GravityEnd = 0.0f;

			ParticlesPerSec = EngineFps * 10;

			Age = 0.9f;



			Direction.x = 0.0f;
			Direction.y = 0.0f;
			Direction.z = 0.0f;

			TimeCount = 0.0f;

			Location.x = (float)x;
			Location.y = (float)y;
			Location.z = (float)z;

			PrevLocation.x = (float)Location.x;
			PrevLocation.y = (float)Location.y;
			PrevLocation.z = (float)Location.z;
		}
		break;

		case MONSTER_IMP_SHOT3:
		{
			make_pSu = 2;

			StartFlag = TRUE;
			MaterialNum = matNum;
			AutoDieFlag = FALSE;




			ColorStart.r = 255.0f;
			ColorStart.g = 255.0f;
			ColorStart.b = 255.0f;





			ColorEnd.r = 255.0f;
			ColorEnd.g = 255.0f;
			ColorEnd.b = 255.0f;



			AlphaStart = 255.0f;

			AlphaEnd = 0.0f;
			AlphaEnd = 255.0f;


			SizeStart = 30.0f;




			SizeEnd = 30.0f;

			Speed = 100.0f;


			Theta = 180.0f;


			Life = 0.005f;


			GravityStart = 0.0f;

			GravityEnd = 0.0f;

			ParticlesPerSec = EngineFps * 10;

			Age = 0.9f;



			Direction.x = 0.0f;
			Direction.y = 0.0f;
			Direction.z = 0.0f;

			TimeCount = 0.0f;

			Location.x = (float)x;
			Location.y = (float)y;
			Location.z = (float)z;

			PrevLocation.x = (float)Location.x;
			PrevLocation.y = (float)Location.y;
			PrevLocation.z = (float)Location.z;
		}
		break;


		case MONSTER_FORZENMIST_SHOT1:
		{


			StartFlag = TRUE;
			MaterialNum = matNum;
			AutoDieFlag = FALSE;




			ColorStart.r = 50.0f;
			ColorStart.g = 70.0f;
			ColorStart.b = 255.0f;


			ColorEnd.r = 0.0f;
			ColorEnd.g = 0.0f;
			ColorEnd.b = 0.0f;






			AlphaStart = 200.0f;
			AlphaEnd = 0.0f;



			SizeStart = 15.0f;

			SizeEnd = 15.0f;

			Speed = 100.0f;


			Theta = 180.0f;


			Life = 0.1f;

			GravityStart = 0.0f;
			GravityEnd = 0.0f;

			ParticlesPerSec = EngineFps * 10;

			Age = 0.9f;

			Direction.x = 0.0f;
			Direction.y = 0.0f;
			Direction.z = 0.0f;

			TimeCount = 0.0f;

			Location.x = (float)x;
			Location.y = (float)y;
			Location.z = (float)z;

			PrevLocation.x = (float)Location.x;
			PrevLocation.y = (float)Location.y;
			PrevLocation.z = (float)Location.z;
		}
		break;




	}
	return true;
}


int HoParticleSystem::Main()
{
	if(StartFlag == FALSE)
		return FALSE;

	TimeCount++;
	if(TimeCount >= 1)
	{
		ParticlesAlive = 0;


		for(int i = 0; i < make_pSu; i++)

		{
			if(Particles[i].Age >= 0.0f)
				if(Particles[i].Main())
					ParticlesAlive++;
		}


		if(AutoDieFlag)
			Age -= (TimeCount / EngineFps);

		if(Age < 0)
		{
			if(ParticlesAlive <= 0)
				StartFlag = FALSE;
			Age = -1.0f;
			return FALSE;
		}




		float particleNeeded = ParticlesPerSec*(TimeCount / EngineFps) + EmissionResidue;


		unsigned int particlesCreated = (unsigned int)particleNeeded;

		EmissionResidue = particleNeeded - particlesCreated;

		if(particleNeeded > 0)
		{

			for(int i = 0; i < make_pSu; i++)
			{
				if(!particlesCreated)
					break;

				if(Particles[i].Age < 0.0f)
				{

					Particles[i].Age = 0.0f;
					Particles[i].LifeTime = Life;
					Clamp(Particles[i].LifeTime, MIN_LIFETIME, MAX_LIFETIME);


					Particles[i].Color.r = ColorStart.r;
					Particles[i].Color.g = ColorStart.g;
					Particles[i].Color.b = ColorStart.b;
					Particles[i].Color.a = ColorStart.a;

					Clamp(Particles[i].Color.r, 0.0f, 255.0f);
					Clamp(Particles[i].Color.g, 0.0f, 255.0f);
					Clamp(Particles[i].Color.b, 0.0f, 255.0f);


					Particles[i].ColorDelta.r = (ColorEnd.r - Particles[i].Color.r) / (Particles[i].LifeTime*EngineFps);
					Particles[i].ColorDelta.g = (ColorEnd.g - Particles[i].Color.g) / (Particles[i].LifeTime*EngineFps);
					Particles[i].ColorDelta.b = (ColorEnd.b - Particles[i].Color.b) / (Particles[i].LifeTime*EngineFps);


					Particles[i].Alpha = AlphaStart;
					Clamp(Particles[i].Alpha, MIN_ALPHA, MAX_ALPHA);
					Particles[i].AlphaDelta = (AlphaEnd - Particles[i].Alpha) / (Particles[i].LifeTime*EngineFps);


					Particles[i].Size = SizeStart;
					Clamp(Particles[i].Size, MIN_SIZE, MAX_SIZE);
					Particles[i].SizeDelta = (SizeEnd - Particles[i].Size) / (Particles[i].LifeTime*EngineFps);



					Particles[i].Gravity = GravityStart*9.8f;

					Clamp(Particles[i].Gravity, MIN_GRAVITY*9.8f, MAX_GRAVITY*9.8f);
					Particles[i].GravityDelta = (GravityEnd*9.8f - Particles[i].Gravity) / (Particles[i].LifeTime*EngineFps);


					D3DXVECTOR3 tempVelocity;
					tempVelocity.x = (Location.x - PrevLocation.x) / (TimeCount / EngineFps);
					tempVelocity.y = (Location.y - PrevLocation.y) / (TimeCount / EngineFps);
					tempVelocity.z = (Location.z - PrevLocation.z) / (TimeCount / EngineFps);




					Particles[i].Location.x = PrevLocation.x + tempVelocity.x * RANDOM_NUM * (TimeCount / EngineFps);
					Particles[i].Location.y = PrevLocation.y + tempVelocity.y * RANDOM_NUM * (TimeCount / EngineFps);
					Particles[i].Location.z = PrevLocation.z + tempVelocity.z * RANDOM_NUM * (TimeCount / EngineFps);


					Particles[i].PrevLocation = Location;
					float RandomYaw = RANDOM_NUM   * 3.14159f * 2.0f;
					float RandomPitch = RANDOM_NUM * Theta * 3.14159f / 180.0f;


					Particles[i].Velocity.y = cosf(RandomPitch);
					Particles[i].Velocity.x = sinf(RandomPitch) * cosf(RandomYaw);
					Particles[i].Velocity.z = sinf(RandomPitch) * sinf(RandomYaw);

					float newSpeed = Speed;

					Clamp(newSpeed, MIN_SPEED, MAX_SPEED);


					if(ParticleCode == EFFECT_FIRE_CRACKER)
					{
						Particles[i].Velocity.x *= newSpeed;
						Particles[i].Velocity.y *= newSpeed;
						Particles[i].Velocity.z *= newSpeed;
					}
					else
					{

						Particles[i].Velocity.x *= newSpeed;
						Particles[i].Velocity.y *= newSpeed;
						Particles[i].Velocity.z *= newSpeed;
					}




					particlesCreated--;
					Particles[i].SetParent(this);
				}
			}
		}

		TimeCount = 0;
	}
	return true;
}

void HoParticleSystem::GetLocation(D3DXVECTOR3& vLocation)
{
	vLocation = Location;
}


int HoParticleSystem::Draw(int x, int y, int z, int ax, int ay, int az)
{
	if(StartFlag == FALSE)
		return FALSE;

	if(make_pSu <= 0)
		return FALSE;

	smRender.Init();
	smRender.SetMaterialGroup(smMaterialGroup);
	smMaterialGroup->smMaterial[MaterialNum].TwoSide = TRUE;



	smRender.SetCameraPosi(x, y, z, ax, ay, az);



	for(int i = 0; i < make_pSu; i++)
	{
		if(Particles[i].Age >= 0.0f)
		{
			Face2d.x = int(Particles[i].Location.x);
			Face2d.y = int(Particles[i].Location.y);
			Face2d.z = int(Particles[i].Location.z);

			Face2d.r = int(Particles[i].Color.r);
			Face2d.g = int(Particles[i].Color.g);
			Face2d.b = int(Particles[i].Color.b);

			Face2d.Transparency = int(Particles[i].Alpha);

			Face2d.TexRect.left = 0;
			Face2d.TexRect.top = 0;
			Face2d.TexRect.right = 1;
			Face2d.TexRect.bottom = 1;


			Face2d.width = int(Particles[i].Size) << FLOATNS;
			Face2d.height = int(Particles[i].Size) << FLOATNS;
			Face2d.MatNum = MaterialNum;

			smRender.AddFace2D(&Face2d);
		}
	}

	d3ddev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);



	smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
	smRender.ClipRendFace();
	smRender.GeomVertex2D(FALSE);
	smRender.RenderD3D();




	d3ddev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);





	return TRUE;
}

void HoParticleSystem::Init()
{

	StartFlag = FALSE;

}

HoParticleBow::HoParticleBow()
{

	StartFlag = FALSE;
}

HoParticleBow::~HoParticleBow()
{

}

int HoParticleBow::Main()
{
	if(StartFlag == FALSE)
		return FALSE;

	TimeCount++;
	if(TimeCount >= 1)
	{
		ParticlesAlive = 0;

		for(int i = 0; i < MAX_PARTICLES; i++)
		{
			if(Particles[i].Age >= 0.0f)
				if(Particles[i].Main())
					ParticlesAlive++;
		}


		Age -= (TimeCount / EngineFps);
		if(Age < 0)
		{
			if(ParticlesAlive <= 0)
				StartFlag = FALSE;
			Age = -1.0f;
			return FALSE;
		}





		float particleNeeded = ParticlesPerSec*(TimeCount / EngineFps) + EmissionResidue;


		unsigned int particlesCreated = (unsigned int)particleNeeded;



		EmissionResidue = particleNeeded - particlesCreated;

		if(particleNeeded > 0)
		{
			for(int i = 0; i < MAX_PARTICLES; i++)
			{
				if(!particlesCreated)
					break;

				if(Particles[i].Age < 0.0f)
				{

					Particles[i].Age = 0.0f;
					Particles[i].LifeTime = Life;
					Clamp(Particles[i].LifeTime, MIN_LIFETIME, MAX_LIFETIME);


					Particles[i].Color.r = (ColorStart.r);
					Particles[i].Color.g = (ColorStart.g);
					Particles[i].Color.b = (ColorStart.b);
					Particles[i].Color.a = (ColorStart.a);

					Clamp(Particles[i].Color.r, 0.0f, 255.0f);
					Clamp(Particles[i].Color.g, 0.0f, 255.0f);
					Clamp(Particles[i].Color.b, 0.0f, 255.0f);


					Particles[i].ColorDelta.r = (ColorEnd.r - Particles[i].Color.r) / (Particles[i].LifeTime*EngineFps);
					Particles[i].ColorDelta.g = (ColorEnd.g - Particles[i].Color.g) / (Particles[i].LifeTime*EngineFps);
					Particles[i].ColorDelta.b = (ColorEnd.b - Particles[i].Color.b) / (Particles[i].LifeTime*EngineFps);


					Particles[i].Alpha = AlphaStart;
					Clamp(Particles[i].Alpha, MIN_ALPHA, MAX_ALPHA);
					Particles[i].AlphaDelta = (AlphaEnd - Particles[i].Alpha) / (Particles[i].LifeTime*EngineFps);



					Particles[i].Size = SizeStart;
					Clamp(Particles[i].Size, MIN_SIZE, MAX_SIZE);
					Particles[i].SizeDelta = (SizeEnd - Particles[i].Size) / (Particles[i].LifeTime*EngineFps);


					Particles[i].Gravity = GravityStart*9.8f;

					Clamp(Particles[i].Gravity, MIN_GRAVITY*9.8f, MAX_GRAVITY*9.8f);
					Particles[i].GravityDelta = (GravityEnd*9.8f - Particles[i].Gravity) / (Particles[i].LifeTime*EngineFps);



					D3DXVECTOR3 tempVelocity;
					tempVelocity.x = (Location.x - PrevLocation.x) / (TimeCount / EngineFps);
					tempVelocity.y = (Location.y - PrevLocation.y) / (TimeCount / EngineFps);
					tempVelocity.z = (Location.z - PrevLocation.z) / (TimeCount / EngineFps);


					Particles[i].Location.x = PrevLocation.x + tempVelocity.x * RANDOM_NUM * (TimeCount / EngineFps);
					Particles[i].Location.y = PrevLocation.y + tempVelocity.y * RANDOM_NUM * (TimeCount / EngineFps);
					Particles[i].Location.z = PrevLocation.z + tempVelocity.z * RANDOM_NUM * (TimeCount / EngineFps);

					Particles[i].PrevLocation = Location;
					float RandomYaw = RANDOM_NUM   * 3.14159f * 2.0f;
					float RandomPitch = RANDOM_NUM * Theta * 3.14159f / 180.0f;


					Particles[i].Velocity.y = cosf(RandomPitch);
					Particles[i].Velocity.x = sinf(RandomPitch) * cosf(RandomYaw);
					Particles[i].Velocity.z = sinf(RandomPitch) * sinf(RandomYaw);

					float newSpeed = Speed;

					Clamp(newSpeed, MIN_SPEED, MAX_SPEED);
					Particles[i].Velocity.x *= newSpeed;
					Particles[i].Velocity.y *= newSpeed;
					Particles[i].Velocity.z *= newSpeed;


					particlesCreated--;
					Particles[i].SetParent(this);
				}
			}
		}
		TimeCount = 0;
	}
	return TRUE;
}



int HoParticleBow::Start(int x, int y, int z, int r, int g, int b, int a, int matNum)
{
	if(StartFlag)
		return FALSE;
	StartFlag = TRUE;


	MaterialNum = matNum;

	ColorStart.r = (float)r;
	ColorStart.g = (float)g;
	ColorStart.b = (float)b;

	ColorEnd.r = float(r / 2);
	ColorEnd.g = float(g / 2);
	ColorEnd.b = float(b / 2);

	AlphaStart = (float)a;

	AlphaEnd = 0.0f;

	SizeStart = 1.0f;

	SizeEnd = 1.0f;

	Speed = 150.0f;


	Theta = 180.0f;

	Life = 0.7f;


	GravityStart = 0.0f;

	GravityEnd = 0.0f;

	ParticlesPerSec = EngineFps / 4;

	Age = 0.2f;
	EmissionResidue = 0.0f;

	Direction.x = 0.0f;
	Direction.y = 0.0f;
	Direction.z = 0.0f;

	TimeCount = 0.0f;


	Location.x = (float)x;
	Location.y = (float)y;
	Location.z = (float)z;


	PrevLocation.x = (float)x;
	PrevLocation.y = (float)y;
	PrevLocation.z = (float)z;


	return TRUE;
}


int HoParticleBow::StartFire(int x, int y, int z, int r, int g, int b, int a, int matNum)
{
	if(StartFlag)
		return FALSE;
	StartFlag = TRUE;
	MaterialNum = matNum;



	ColorStart.r = (float)r;
	ColorStart.g = (float)g;
	ColorStart.b = (float)b;





	ColorEnd.r = 0.f;
	ColorEnd.g = 0.f;
	ColorEnd.b = 0.f;

	AlphaStart = (float)a;

	AlphaEnd = 0.0f;

	SizeStart = 6.0f;

	SizeEnd = 4.0f;

	Speed = 100.0f;


	Theta = 180.0f;

	Life = 0.5f;


	GravityStart = 0.0f;

	GravityEnd = 0.0f;

	ParticlesPerSec = EngineFps * 2;

	Age = 0.04f;
	EmissionResidue = 0.0f;

	Direction.x = 0.0f;
	Direction.y = 0.0f;
	Direction.z = 0.0f;

	TimeCount = 0.0f;


	Location.x = (float)x;
	Location.y = (float)y;
	Location.z = (float)z;


	PrevLocation.x = (float)x;
	PrevLocation.y = (float)y;
	PrevLocation.z = (float)z;


	return TRUE;
}

HoParticleTornado::HoParticleTornado()
{

}

HoParticleTornado::~HoParticleTornado()
{

}

int HoParticleTornado::Main()
{
	if(StartFlag)
	{
		HoParticleSystem::Main();
		PrevLocation = Location;

		LocalAngle += ANGLE_360 / 60;
		float hoSin = float(GetSin[LocalAngle&ANGCLIP]);
		float hoCos = float(GetCos[LocalAngle&ANGCLIP]);
		double x;
		double z;

		hoSin = hoSin / 65536.f;
		hoCos = hoCos / 65536.f;

		x = (LocalX*hoCos - LocalZ*hoSin);
		z = (LocalX*hoSin + LocalZ*hoCos);


		Location.x = float(WorldX + x);
		Location.z = float(WorldZ + z);
		Location.y += 100;




		D3DXVECTOR3	attractLocation;
		attractLocation.x = (LocalX + WorldX) - WorldX;
		attractLocation.y = (LocalY + WorldY) - WorldY;
		attractLocation.z = (LocalZ + WorldZ) - WorldZ;


		D3DXVECTOR3 attractDir = attractLocation;
		float length;
		length = (float)sqrt(attractDir.x*attractDir.x + attractDir.y*attractDir.y + attractDir.z*attractDir.z);


		LocalX += attractLocation.x / length * 100;

		LocalZ += attractLocation.z / length * 100;
	}

	return TRUE;
}

int HoParticleTornado::Start(int worldX, int worldY, int worldZ, int startX, int startY, int startZ, int matNum)
{
	LocalAngle = 20;
	WorldX = (float)worldX;
	WorldY = (float)worldY;
	WorldZ = (float)worldZ;


	LocalX = (float)startX;
	LocalY = (float)startY;
	LocalZ = (float)startZ;

	StartFlag = TRUE;
	MaterialNum = matNum;


	ColorStart.r = 255.0f;
	ColorStart.g = 200.0f;
	ColorStart.b = 125.0f;





	ColorEnd.r = 255.0f / 2;
	ColorEnd.g = 200.0f / 2;
	ColorEnd.b = 100.0f / 2;


	AlphaStart = 200.0f;

	AlphaEnd = 0.0f;

	SizeStart = 8.0f;

	SizeEnd = 3.0f;

	Speed = 50.0f;


	Theta = 180.0f;

	Life = 1.0f;


	GravityStart = 0.0f;

	GravityEnd = 0.0f;

	ParticlesPerSec = EngineFps;

	Age = 2.0f;

	EmissionResidue = 0.0f;

	Direction.x = 0.0f;
	Direction.y = 0.0f;
	Direction.z = 0.0f;

	TimeCount = 0.0f;

	Location.x = 0;
	Location.y = WorldY;
	Location.z = 0;

	PrevLocation.x = Location.x;
	PrevLocation.y = Location.y;
	PrevLocation.z = Location.z;

	return TRUE;
}


HoParticleDest::HoParticleDest() : HoParticleSystem()
{
	StartFlag = false;
	SetClassID(CLASS_ID_PARTICLE_DEST);
}

HoParticleDest::~HoParticleDest()
{
	StartFlag = false;
}

int HoParticleDest::Main()
{
	if(StartFlag)
	{
		HoParticleSystem::Main();
		PrevLocation = Location;

		float x = 0.f;
		float z = 0.f;

		if(EndWaveFlag)
		{
			LocalAngle -= ANGLE_360 / (180 + 80);
			float hoSin = float(GetSin[LocalAngle&ANGCLIP]);
			float hoCos = float(GetCos[LocalAngle&ANGCLIP]);
			hoSin = hoSin / 65536.f;
			hoCos = hoCos / 65536.f;

			x = (LocalX*hoCos - LocalZ*hoSin);
			z = (LocalX*hoSin + LocalZ*hoCos);


			Location.x = float(WorldX + x);
			Location.z = float(WorldZ + z);
		}
		else
		{
			Location.x = WorldX + LocalX;
			Location.y = WorldY + LocalY;
			Location.z = WorldZ + LocalZ;
		}


		D3DXVECTOR3	attractLocation;
		attractLocation.x = DestX - (WorldX + LocalX);
		attractLocation.y = DestY - (WorldY + LocalY);
		attractLocation.z = DestZ - (WorldZ + LocalZ);

		D3DXVECTOR3 attractDir = attractLocation;

		float length;
		length = (float)sqrt(attractDir.x*attractDir.x + attractDir.y*attractDir.y + attractDir.z*attractDir.z);

		if(length == 0.0f)
			length = 1.0f;

		PrevLocation = Location;
		LocalX += attractDir.x / length * 850.0f;
		LocalZ += attractDir.z / length * 850.0f;
	}


	return TRUE;
}


int HoParticleDest::Start(int worldX, int worldY, int worldZ, int destX, int destY, int destZ, int matNum, int type)
{

	SetClassID(CLASS_ID_PARTICLE_DEST);
	switch(type)
	{
		case 0:
		{
			EndWaveFlag = FALSE;

			StartFlag = TRUE;
			MaterialNum = matNum;

			ColorStart.r = 255.0f;
			ColorStart.g = 255.0f;
			ColorStart.b = 255.0f;





			ColorEnd.r = 255.0f;
			ColorEnd.g = 255.0f;
			ColorEnd.b = 255.0f;


			AlphaStart = 100.0f;

			AlphaEnd = 0.0f;

			SizeStart = 10.0f;

			SizeEnd = 3.0f;

			Speed = 150.0f;


			Theta = 180.0f;

			Life = 0.4f;


			GravityStart = 0.0f;

			GravityEnd = 0.0f;

			ParticlesPerSec = EngineFps;

			Age = 0.6f;

			EmissionResidue = 0.0f;

			Direction.x = 0.0f;
			Direction.y = 0.0f;
			Direction.z = 0.0f;

			TimeCount = 0.0f;

			DestX = destX;
			DestY = destY;
			DestZ = destZ;

			LocalX = 0;
			LocalY = 0;
			LocalZ = 0;

			WorldX = (float)worldX;
			WorldY = (float)worldY;
			WorldZ = (float)worldZ;

			PrevLocation.x = Location.x;
			PrevLocation.y = Location.y;
			PrevLocation.z = Location.z;

			Location.x = worldX + LocalX;
			Location.y = worldY + LocalY;
			Location.z = worldZ + LocalZ;
			break;
		}

		case 1:
		{
			EndWaveFlag = TRUE;
			LocalAngle = 0;
			StartFlag = TRUE;
			MaterialNum = matNum;

			ColorStart.r = 60.0f;
			ColorStart.g = 60.0f;
			ColorStart.b = 60.0f;


			ColorEnd.r = 0.0f;
			ColorEnd.g = 0.0f;
			ColorEnd.b = 0.0f;


			AlphaStart = 150.0f;
			AlphaEnd = 10.0f;


			SizeStart = 12.0f;

			SizeEnd = 5.0f;

			Speed = 150.0f;


			Theta = 180.0f;

			Life = 0.6f;


			GravityStart = 0.0f;

			GravityEnd = 0.0f;

			ParticlesPerSec = EngineFps / 2;

			Age = 0.4f;

			EmissionResidue = 0.0f;


			Direction.x = 0.0f;
			Direction.y = 0.0f;
			Direction.z = 0.0f;

			TimeCount = 0.0f;

			DestX = destX;
			DestY = destY;
			DestZ = destZ;

			LocalX = 0;
			LocalY = 0;
			LocalZ = 0;

			WorldX = (float)worldX;
			WorldY = (float)worldY;
			WorldZ = (float)worldZ;

			PrevLocation.x = Location.x;
			PrevLocation.y = Location.y;
			PrevLocation.z = Location.z;

			Location.x = worldX + LocalX;
			Location.y = worldY + LocalY;
			Location.z = worldZ + LocalZ;

			break;
		}

		case 2:
		{
			EndWaveFlag = FALSE;

			StartFlag = TRUE;
			MaterialNum = matNum;

			ColorStart.r = 255.0f;
			ColorStart.g = 255.0f;
			ColorStart.b = 255.0f;





			ColorEnd.r = 255.0f;
			ColorEnd.g = 255.0f;
			ColorEnd.b = 255.0f;


			AlphaStart = 100.0f;

			AlphaEnd = 0.0f;

			SizeStart = 8.0f;

			SizeEnd = 3.0f;

			Speed = 50.0f;


			Theta = 180.0f;

			Life = 0.6f;


			GravityStart = 0.0f;

			GravityEnd = 0.0f;

			ParticlesPerSec = EngineFps * 2;

			Age = 0.6f;

			EmissionResidue = 0.0f;

			Direction.x = 0.0f;
			Direction.y = 0.0f;
			Direction.z = 0.0f;

			TimeCount = 0.0f;

			DestX = destX;
			DestY = destY;
			DestZ = destZ;

			LocalX = 0;
			LocalY = 0;
			LocalZ = 0;

			WorldX = (float)worldX;
			WorldY = (float)worldY;
			WorldZ = (float)worldZ;

			PrevLocation.x = Location.x;
			PrevLocation.y = Location.y;
			PrevLocation.z = Location.z;

			Location.x = worldX + LocalX;
			Location.y = worldY + LocalY;
			Location.z = worldZ + LocalZ;
			break;
		}
	}

	return TRUE;
}





void HoParticleSpark::Init()
{
	MaterialNum = CreateTextureMaterial("spark.tga", 0, 0, 0, 0, SMMAT_BLEND_LAMP);
}

void HoParticleSpark::Start(int x, int y, int z, int matNum, int type)
{
	switch(type)
	{
		case 0:
		{
			ColorStart.r = 255.0f;
			ColorStart.g = 255.0f;
			ColorStart.b = 255.0f;





			ColorEnd.r = 0.0f;
			ColorEnd.g = 0.0f;
			ColorEnd.b = 0.0f;


			AlphaStart = 255.0f;

			AlphaEnd = 0.0f;

			SizeStart = 4.0f;

			SizeEnd = 6.0f;

			Speed = 1000.0f;


			Theta = 180.0f;

			Life = 0.5f;


			GravityStart = 0.05f;

			GravityEnd = 0.0f;

			ParticlesPerSec = EngineFps * 2;

			Age = 0.15f;

			EmissionResidue = 0.0f;

			Direction.x = 0.0f;
			Direction.y = 0.0f;
			Direction.z = 0.0f;

			Location.x = 0.0f;
			Location.y = 0.0f;
			Location.z = 0.0f;

			PrevLocation.x = 0.0f;
			PrevLocation.y = 0.0f;
			PrevLocation.z = 0.0f;

			TimeCount = 0.0f;

			Location.x = 0;
			Location.y = 10000;
			Location.z = -115 * fONE;
			Location.z = 0;

			PrevLocation.x = Location.x;
			PrevLocation.y = Location.y;
			PrevLocation.z = Location.z;

			break;
		}

		case 1:
		{
			ColorStart.r = 255.0f;
			ColorStart.g = 255.0f;
			ColorStart.b = 255.0f;





			ColorEnd.r = 0.0f;
			ColorEnd.g = 0.0f;
			ColorEnd.b = 0.0f;


			AlphaStart = 255.0f;

			AlphaEnd = 0.0f;

			SizeStart = 4.0f;

			SizeEnd = 6.0f;

			Speed = 600.0f;


			Theta = 180.0f;

			Life = 0.3f;


			GravityStart = 0.05f;

			GravityEnd = 0.0f;

			ParticlesPerSec = EngineFps * 4;

			Age = 0.15f;

			EmissionResidue = 0.0f;

			Direction.x = 0.0f;
			Direction.y = 0.0f;
			Direction.z = 0.0f;

			Location.x = 0.0f;
			Location.y = 0.0f;
			Location.z = 0.0f;

			PrevLocation.x = 0.0f;
			PrevLocation.y = 0.0f;
			PrevLocation.z = 0.0f;

			TimeCount = 0.0f;

			Location.x = 0;
			Location.y = 10000;
			Location.z = -115 * fONE;
			Location.z = 0;

			PrevLocation.x = Location.x;
			PrevLocation.y = Location.y;
			PrevLocation.z = Location.z;

			break;
		}
	}

	MaterialNum = matNum;
	StartFlag = TRUE;

	WorldX = (float)x;
	WorldY = (float)y;
	WorldZ = (float)z;

	LocalX = 0;
	LocalY = 0;
	LocalZ = 0;


	Location.x = (float)x;
	Location.y = (float)y;
	Location.z = (float)z;


	PrevLocation.x = Location.x;
	PrevLocation.y = Location.y;
	PrevLocation.z = Location.z;
}


HoParticleSpark::HoParticleSpark()
{
	ColorStart.r = 255.0f;
	ColorStart.g = 255.0f;
	ColorStart.b = 255.0f;





	ColorEnd.r = 0.0f;
	ColorEnd.g = 0.0f;
	ColorEnd.b = 0.0f;


	AlphaStart = 255.0f;

	AlphaEnd = 0.0f;

	SizeStart = 4.0f;

	SizeEnd = 6.0f;

	Speed = 1000.0f;


	Theta = 180.0f;

	Life = 0.5f;


	GravityStart = 0.05f;

	GravityEnd = 0.0f;

	ParticlesPerSec = EngineFps * 2;

	Age = 0.15f;

	EmissionResidue = 0.0f;

	Direction.x = 0.0f;
	Direction.y = 0.0f;
	Direction.z = 0.0f;

	Location.x = 0.0f;
	Location.y = 0.0f;
	Location.z = 0.0f;

	PrevLocation.x = 0.0f;
	PrevLocation.y = 0.0f;
	PrevLocation.z = 0.0f;

	TimeCount = 0.0f;

	Location.x = 0;
	Location.y = 10000;
	Location.z = -115 * fONE;
	Location.z = 0;

	PrevLocation.x = Location.x;
	PrevLocation.y = Location.y;
	PrevLocation.z = Location.z;
}

HoParticleSpark::~HoParticleSpark()
{

}


int HoParticleSpark::Draw(int x, int y, int z, int ax, int ay, int az)
{
	if(StartFlag == FALSE)
		return FALSE;

	smRender.Init();
	smRender.SetMaterialGroup(smMaterialGroup);
	smMaterialGroup->smMaterial[MaterialNum].TwoSide = TRUE;


	smRender.SetCameraPosi(x, y, z, ax, ay, az);

	for(int i = 0; i < MAX_PARTICLES; i++)
	{
		if(Particles[i].Age >= 0.0f)
		{
			Face2d.x = int(Particles[i].Location.x);
			Face2d.y = int(Particles[i].Location.y);
			Face2d.z = int(Particles[i].Location.z);

			Face2d.r = int(Particles[i].Color.r);
			Face2d.g = int(Particles[i].Color.g);
			Face2d.b = int(Particles[i].Color.b);
			Face2d.Transparency = int(Particles[i].Alpha);

			Face2d.TexRect.left = 0;
			Face2d.TexRect.top = 0;
			Face2d.TexRect.right = 1;
			Face2d.TexRect.bottom = 1;


			Face2d.width = int(Particles[i].Size) << FLOATNS;
			Face2d.height = int(Particles[i].Size) << FLOATNS;

			Face2d.MatNum = MaterialNum;

			AddFace2D(&Face2d, i);
		}
	}





	smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
	smRender.ClipRendFace();
	smRender.GeomVertex2D(FALSE);
	smRender.RenderD3D();





	return TRUE;
}


#define FLOATS_EM				(FLOATNS+3)
#define SM_DIST_NEARZ			16
#define SMFLOAT_DIST_NEARZ		(SM_DIST_NEARZ<<FLOATNS)


bool HoParticleSpark::AddFace2D(smFACE2D *face, int particleIndex)
{
	if(Particles[particleIndex].Age < 0.0f)
		return false;

	D3DXVECTOR3 begProj = Particles[particleIndex].PrevLocation;

	D3DXVECTOR3 endProj = Location;



	int x, y, z;
	int rx, ry, rz;
	int width, height;

	x = (int)begProj.x;
	y = (int)begProj.y;
	z = (int)begProj.z;


	x -= smRender.CameraPosiX;
	y -= smRender.CameraPosiY;
	z -= smRender.CameraPosiZ;

	rx = x * smRender.mCamera._11 +
		y * smRender.mCamera._21 +
		z * smRender.mCamera._31;

	ry = x * smRender.mCamera._12 +
		y * smRender.mCamera._22 +
		z * smRender.mCamera._32;

	rz = x * smRender.mCamera._13 +
		y * smRender.mCamera._23 +
		z * smRender.mCamera._33;

	begProj.x = float(rx >> FLOATS_EM);
	begProj.y = float(ry >> FLOATS_EM);
	begProj.z = float(rz >> FLOATS_EM);


	begProj.z -= 24 * fONE;
	if(begProj.z < SMFLOAT_DIST_NEARZ) return false;






	x = (int)endProj.x;
	y = (int)endProj.y;
	z = (int)endProj.z;

	x -= smRender.CameraPosiX;
	y -= smRender.CameraPosiY;
	z -= smRender.CameraPosiZ;

	rx = x * smRender.mCamera._11 +
		y * smRender.mCamera._21 +
		z * smRender.mCamera._31;

	ry = x * smRender.mCamera._12 +
		y * smRender.mCamera._22 +
		z * smRender.mCamera._32;

	rz = x * smRender.mCamera._13 +
		y * smRender.mCamera._23 +
		z * smRender.mCamera._33;

	endProj.x = float(rx >> FLOATS_EM);
	endProj.y = float(ry >> FLOATS_EM);
	endProj.z = float(rz >> FLOATS_EM);


	endProj.z -= 24 * fONE;
	if(endProj.z < SMFLOAT_DIST_NEARZ) return false;








	smRENDVERTEX *v[4];
	smRENDFACE	 *rf;
	short		sColor[4];

	sColor[SMC_A] = face->Transparency;
	sColor[SMC_R] = face->r;
	sColor[SMC_G] = face->g;
	sColor[SMC_B] = face->b;

	x = face->x;
	y = face->y;
	z = face->z;


	x -= smRender.CameraPosiX;
	y -= smRender.CameraPosiY;
	z -= smRender.CameraPosiZ;

	rx = x * smRender.mCamera._11 +
		y * smRender.mCamera._21 +
		z * smRender.mCamera._31;

	ry = x * smRender.mCamera._12 +
		y * smRender.mCamera._22 +
		z * smRender.mCamera._32;

	rz = x * smRender.mCamera._13 +
		y * smRender.mCamera._23 +
		z * smRender.mCamera._33;

	x = rx >> FLOATS_EM;
	y = ry >> FLOATS_EM;
	z = rz >> FLOATS_EM;


	z -= 24 * fONE;


	if(z < SMFLOAT_DIST_NEARZ) return false;

	width = face->width >> 1;
	height = face->height >> 1;




	float dx = endProj.x - begProj.x;
	float dy = endProj.y - begProj.y;
	float oolen = (float)sqrt(dx*dx + dy*dy);

	dx = dx / oolen * 150;
	dy = dy / oolen * 150;









	D3DXVECTOR3 persp;
	persp.x = -dy;
	persp.y = +dx;
	persp.z = 0;

	if(abs((int)dx) > 1.0f) begProj.x -= (int)dx;
	if(abs((int)dy) > 1.0f) begProj.y -= (int)dy;


	v[0] = smRender.AddRendVertex(int(endProj.x - persp.x), int(endProj.y - persp.y), int(endProj.z), sColor);
	v[1] = smRender.AddRendVertex(int(endProj.x + persp.x), int(endProj.y + persp.y), int(endProj.z), sColor);
	v[3] = smRender.AddRendVertex(int(begProj.x + persp.x), int(begProj.y + persp.y), int(begProj.z), sColor);
	v[2] = smRender.AddRendVertex(int(begProj.x - persp.x), int(begProj.y - persp.y), int(begProj.z), sColor);


	rf = &smRender.RendFace[smRender.nRendFace++];
	rf->lpRendVertex[0] = v[0];
	rf->lpRendVertex[1] = v[1];
	rf->lpRendVertex[2] = v[2];
	rf->Matrial = face->MatNum;
	rf->ClipStatus = v[0]->ClipStatus | v[1]->ClipStatus | v[2]->ClipStatus;
	rf->lpTexLink = 0;



	smRender.AddRendTempTexLink(rf, 0, face->TexRect.left, face->TexRect.bottom,
								face->TexRect.right, face->TexRect.bottom,
								face->TexRect.left, face->TexRect.top);



	rf = &smRender.RendFace[smRender.nRendFace++];
	rf->lpRendVertex[0] = v[1];
	rf->lpRendVertex[1] = v[3];
	rf->lpRendVertex[2] = v[2];



	rf->Matrial = face->MatNum;
	rf->ClipStatus = v[1]->ClipStatus | v[2]->ClipStatus | v[3]->ClipStatus;
	rf->lpTexLink = 0;


	smRender.AddRendTempTexLink(rf, 0, face->TexRect.right, face->TexRect.bottom,
								face->TexRect.right, face->TexRect.top,
								face->TexRect.left, face->TexRect.top);
	return true;
}




