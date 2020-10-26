
#include "..\\HoBaram\\HoLinkHeader.h"
HoPhysicsObject::HoPhysicsObject()
{
	Init();
}


HoPhysicsObject::~HoPhysicsObject()
{
	Init();
}

void HoPhysicsObject::Init()
{
	StartFlag = FALSE;
}

int HoPhysicsObject::Main()
{

	return TRUE;
}

HoPhysicsDest::HoPhysicsDest()
{
	Init();
}

HoPhysicsDest::~HoPhysicsDest()
{

}

void HoPhysicsDest::Init()
{
	StartFlag = FALSE;
	Speed = 800;
}

int HoPhysicsDest::Main()
{
	if(StartFlag == FALSE)
		return FALSE;

	if(StartFlag)
	{
		float length;
		float vx, vy, vz;


		vx = float(DestPos.x - CurrentPos.x);
		vy = float(DestPos.y - CurrentPos.y);
		vz = float(DestPos.z - CurrentPos.z);

		length = (float)sqrt(vx*vx + vy*vy + vz*vz);
		if(length < Speed)
		{
			Init();
		}

		CurrentPos.x += (int)Velocity.x;
		CurrentPos.y += (int)Velocity.y;
		CurrentPos.z += (int)Velocity.z;
	}

	return TRUE;
}

int HoPhysicsDest::Start(POINT3D &currentPos, POINT3D &destPos, int speed)
{

	StartFlag = TRUE;
	CurrentPos = currentPos;
	DestPos = destPos;

	if(speed == 0)
		Speed = 800;
	else
		Speed = speed;

	Velocity.x = 0.f;
	Velocity.y = 0.f;
	Velocity.z = 0.f;

	float length;
	float vx, vy, vz;


	vx = float(DestPos.x - CurrentPos.x);
	vy = float(DestPos.y - CurrentPos.y);
	vz = float(DestPos.z - CurrentPos.z);

	length = (float)sqrt(vx*vx + vy*vy + vz*vz);

	Velocity.x = vx / length*Speed;
	Velocity.y = vy / length*Speed;
	Velocity.z = vz / length*Speed;

	WorkId = MOVE_LINE;
	return TRUE;
}

HoPhysicsParticle::HoPhysicsParticle()
{
	memset(&DestLocalAngle, 0, sizeof(DestLocalAngle));
	memset(&LocalAngleStep, 0, sizeof(LocalAngleStep));

	Init();
}

HoPhysicsParticle::~HoPhysicsParticle()
{

}

void HoPhysicsParticle::Init()
{
	StartFlag = FALSE;
	memset(&DestLocalAngle, 0, sizeof(DestLocalAngle));
	memset(&LocalAngleStep, 0, sizeof(LocalAngleStep));
}

int HoPhysicsParticle::Main()
{
	if(StartFlag == FALSE)
		return FALSE;


	Velocity.y += Gravity;
	DestLocalAngle.x += LocalAngleStep.x;
	DestLocalAngle.y += LocalAngleStep.y;
	DestLocalAngle.z += LocalAngleStep.z;
	Live--;

	if(Live <= 0)
	{
		Init();
	}

	return TRUE;
}

int HoPhysicsParticle::Start(POINT3D &velocity)
{
	StartFlag = TRUE;
	Velocity.x = (float)velocity.x;
	Velocity.y = (float)velocity.y;
	Velocity.z = (float)velocity.z;

	WorkId = MOVE_PARTICLE;
	return TRUE;
}

int HoPhysicsParticle::SetDestAngle(POINT3D destAngle)
{
	LocalAngleStep.x = float(destAngle.x / Live);
	LocalAngleStep.y = float(destAngle.y / Live);
	LocalAngleStep.z = float(destAngle.z / Live);

	return TRUE;
}

HoPhysicsMgr::HoPhysicsMgr()
{
	memset(PhysicsObject, 0, sizeof(PhysicsObject));
	Init();
}

HoPhysicsMgr::~HoPhysicsMgr()
{
	Init();
}

void HoPhysicsMgr::Init()
{
	for(int index = 0; index < MAX_PHYSICS_OBJECT_MAX; index++)
	{
		if(PhysicsObject[index] != NULL)
		{
			delete PhysicsObject[index];
			PhysicsObject[index] = NULL;
		}
	}

	PhysicsObjectBufferCount = 0;
}

int HoPhysicsMgr::Main()
{
	for(int index = 0; index < PhysicsObjectBufferCount; index++)
	{
		if(PhysicsObject[index] != NULL)
		{
			if(PhysicsObject[index]->GetState() == TRUE)
			{
				PhysicsObject[index]->Main();
			}
			else
			{
				delete PhysicsObject[index];
				PhysicsObject[index] = NULL;
			}
		}
	}
	return TRUE;
}

int HoPhysicsMgr::AddObject(HoPhysicsObject *object)
{
	for(int index = 0; index < MAX_PHYSICS_OBJECT_MAX; index++)
	{
		if(PhysicsObject[index] == NULL)
		{
			PhysicsObject[index] = object;
			PhysicsObjectBufferCount++;
			return PhysicsObjectBufferCount - 1;
		}
	}
	return -1;
}
