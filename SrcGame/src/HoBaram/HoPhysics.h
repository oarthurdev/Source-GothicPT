

#ifndef _HO_PHYSICS_H_
#define _HO_PHYSICS_H_

struct hoPOINT3D
{
	float x;
	float y;
	float z;
};

#define MOVE_LINE						0x00000010 
#define MOVE_PARTICLE					0x00000020 
#define MOVE_ANGLE						0X00000040 

class HoPhysicsObject
{
public:
	HoPhysicsObject();
	~HoPhysicsObject();

protected:
	hoPOINT3D	Velocity;
	BOOL		StartFlag;

	int			WorkId;

public:
	virtual void Init();
	virtual int Main();
	virtual hoPOINT3D GetVector()
	{
		return Velocity;
	}
	virtual BOOL GetState()
	{
		return StartFlag;
	}
	virtual void SetState(BOOL startFlag)
	{
		StartFlag = startFlag;
	}
	virtual hoPOINT3D GetAngle()
	{
		hoPOINT3D temp;
		memset(&temp, 0, sizeof(temp));
		return temp;
	}

	int		GetWorkId()
	{
		return WorkId;
	}
};


class HoPhysicsDest : public HoPhysicsObject
{
public:
	HoPhysicsDest();
	~HoPhysicsDest();
private:
	POINT3D		DestPos;
	POINT3D		CurrentPos;
	int			Speed;

public:
	void		Init();
	int			Main();
	int			Start(POINT3D &currentPos, POINT3D &destPos, int speed);
	hoPOINT3D	GetVector()
	{
		return Velocity;
	}
};


class HoPhysicsParticle : public HoPhysicsObject
{
public:
	HoPhysicsParticle();
	~HoPhysicsParticle();

private:
	float		Gravity;
	int			Live;


	hoPOINT3D			DestLocalAngle;
	hoPOINT3D			LocalAngleStep;

public:
	void	Init();
	int		Main();
	int		Start(POINT3D &velocity);
	void	SetGravity(float gravity)
	{
		Gravity = gravity;
	}
	void	SetLive(int live)
	{
		Live = live;
	}
	hoPOINT3D GetVector()
	{
		return Velocity;
	}

	int		SetDestAngle(POINT3D destAngle);
	hoPOINT3D GetAngle()
	{
		return LocalAngleStep;
	}
};

#define MAX_PHYSICS_OBJECT_MAX		100

class HoPhysicsMgr
{
public:
	HoPhysicsMgr();
	~HoPhysicsMgr();

private:
	HoPhysicsObject *PhysicsObject[MAX_PHYSICS_OBJECT_MAX];
	int				 PhysicsObjectBufferCount;


public:
	int AddObject(HoPhysicsObject *object);

	hoPOINT3D	*GetVector(int index)
	{
		if(index < 0 && index >= MAX_PHYSICS_OBJECT_MAX)
			return NULL;

		if(PhysicsObject[index] == NULL)
			return NULL;

		if(PhysicsObject[index]->GetState() == FALSE)
			return NULL;

		return &PhysicsObject[index]->GetVector();
	}

	void Init();
	int Main();
};

#endif
