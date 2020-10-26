#pragma once
#include <Windows.h>

#define MAX_IMG_DAMAGE 100

class smCHAR;

class DrawDamage
{
public:

	virtual						~DrawDamage();
	static DrawDamage*				GetInstance() { static DrawDamage instance; return &instance; };

	struct BuffDamage
	{
		int   Flag;
		DWORD Obj;
		int   Damage;
		int   Time;
		int   Alpha;
		int   PosY;
		int TypeAttack;
	};

	BuffDamage DamageList[64];
	BuffDamage CurDamageList[64];

	void						Init();
	void						Main();
	void						Draw();
	void						UpdateTime();

	void						RenderDamage(smCHAR *Object);
	void						AddTargetDamage(int Damage, DWORD Object, int Type = 0);

	void						CurUpdateTime();
	void						CurRenderDamage(smCHAR *Object);
	void						CurAddTargetDamage(int Damage, DWORD Object, int Type = 0);


private:
	DrawDamage();
};
