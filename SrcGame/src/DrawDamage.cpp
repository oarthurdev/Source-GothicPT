#include "sinbaram\sinLinkHeader.h"

DrawDamage::DrawDamage()
{
}
void DrawDamage::Init()
{
	ZeroMemory(DamageList, sizeof(DamageList));
	ZeroMemory(CurDamageList, sizeof(DamageList));
}

DrawDamage::~DrawDamage()
{
}

void DrawDamage::Main()
{
}

void DrawDamage::Draw()
{
}

void DrawDamage::UpdateTime()
{
	for (int i = 0; i < 64; i++)
	{
		if (DamageList[i].Flag)
		{
			if (DamageList[i].Time < 3000)
			{
				DamageList[i].Time += 1;
				switch (DamageList[i].Time / 255)
				{
				case 0:
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
					DamageList[i].Alpha -= 2;
					DamageList[i].PosY += 1;
					if (DamageList[i].Alpha <= 0)
						ZeroMemory(&DamageList[i], sizeof(DamageList[i]));
					break;
				};
			}
		}
	}
}


void DrawDamage::CurUpdateTime()
{
	for (int i = 0; i < 64; i++)
	{
		if (CurDamageList[i].Flag)
		{
			if (CurDamageList[i].Time < 3000)
			{
				CurDamageList[i].Time += 1;
				switch (CurDamageList[i].Time / 255)
				{
				case 0:
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
					CurDamageList[i].Alpha -= 2;
					CurDamageList[i].PosY += 1;
					if (CurDamageList[i].Alpha <= 0)
						ZeroMemory(&CurDamageList[i], sizeof(CurDamageList[i]));
					break;
				};
			}
		}
	}
}

void DrawDamage::CurRenderDamage(smCHAR *Object)
{
	for (int i = 0; i < 64; i++)
	{
		if (CurDamageList[i].Flag)
		{
			if (CurDamageList[i].Obj == lpCurPlayer->dwObjectSerial)
			{
				char buff[255] = { 0 };
				if (CurDamageList[i].TypeAttack == 0)
					sprintf_s(buff, "%d", CurDamageList[i].Damage);
				if (CurDamageList[i].TypeAttack == 1)
					sprintf_s(buff, "Defense", CurDamageList[i].Damage);
				if (CurDamageList[i].TypeAttack == 2)
					sprintf_s(buff, "Evade", CurDamageList[i].Damage);
				if (CurDamageList[i].TypeAttack == 3)
					sprintf_s(buff, "Block", CurDamageList[i].Damage);
				RECT rcRect2 = { 0, 0, 0, 0 };
				FontDamageShadow->DrawText(NULL, buff, strlen(buff), &rcRect2, DT_CALCRECT, FontColor);
				RECT rc2;
				rc2.left = Object->RendRect2D.left + (((Object->RendRect2D.right - Object->RendRect2D.left) / 2) - ((rcRect2.right - rcRect2.left) / 2));
				rc2.right = Object->RendRect2D.left + smScreenWidth + rcRect2.right - rcRect2.left;
				rc2.top = Object->RendRect2D.top - CurDamageList[i].PosY - 40;
				rc2.bottom = Object->RendRect2D.top - CurDamageList[i].PosY + smScreenHeight;
				if (CurDamageList[i].TypeAttack == 0)
					FontDamageShadow->DrawText(NULL, buff, strlen(buff), &rc2, DT_LEFT | DT_NOCLIP, D3DCOLOR_RGBA(255, 0, 0, CurDamageList[i].Alpha));
				if (CurDamageList[i].TypeAttack == 1)
					FontDamageShadow->DrawText(NULL, buff, strlen(buff), &rc2, DT_LEFT | DT_NOCLIP, D3DCOLOR_RGBA(0, 136, 194, CurDamageList[i].Alpha));
				if (CurDamageList[i].TypeAttack == 2)
					FontDamageShadow->DrawText(NULL, buff, strlen(buff), &rc2, DT_LEFT | DT_NOCLIP, D3DCOLOR_RGBA(255, 160, 57, CurDamageList[i].Alpha));
				if (CurDamageList[i].TypeAttack == 3)
					FontDamageShadow->DrawText(NULL, buff, strlen(buff), &rc2, DT_LEFT | DT_NOCLIP, D3DCOLOR_RGBA(255, 220, 0, CurDamageList[i].Alpha));
			}
		}
	}
}

void DrawDamage::RenderDamage(smCHAR *Object)
{
	for (int i = 0; i < 64; i++)
	{
		if (DamageList[i].Flag)
		{
			if (DamageList[i].Obj == Object->dwObjectSerial)
			{
				if (FontDamageShadow)
				{
					char buff[255] = { 0 };
					sprintf_s(buff, "%d", DamageList[i].Damage);
					RECT rcRect2 = { 0, 0, 0, 0 };
					FontDamageShadow->DrawText(NULL, buff, strlen(buff), &rcRect2, DT_CALCRECT, FontColor);
					RECT rc2;
					rc2.left = Object->RendRect2D.left + (((Object->RendRect2D.right - Object->RendRect2D.left) / 2) - ((rcRect2.right - rcRect2.left) / 2));
					rc2.right = Object->RendRect2D.left + smScreenWidth + rcRect2.right - rcRect2.left;
					rc2.top = Object->RendRect2D.top - DamageList[i].PosY - 40;
					rc2.bottom = Object->RendRect2D.top - DamageList[i].PosY + smScreenHeight;
					FontDamageShadow->DrawText(NULL, buff, strlen(buff), &rc2, DT_LEFT | DT_NOCLIP, D3DCOLOR_RGBA(255, 165, 0, DamageList[i].Alpha));
				}
			}
		}
	}
}


void  DrawDamage::CurAddTargetDamage(int Damage, DWORD Object, int Type)
{
	for (int i = 0; i < 64; i++)
	{
		if (!CurDamageList[i].Flag)
		{
			CurDamageList[i].Flag = 1;
			CurDamageList[i].Damage = Damage;
			CurDamageList[i].Obj = Object;
			CurDamageList[i].PosY = 0;
			CurDamageList[i].Time = 0;
			CurDamageList[i].Alpha = 255;
			CurDamageList[i].TypeAttack = Type;
			break;
		}
	}
}

void  DrawDamage::AddTargetDamage(int Damage, DWORD Object, int Type)
{
	for (int i = 0; i < 64; i++)
	{
		if (!DamageList[i].Flag)
		{
			DamageList[i].Flag = 1;
			DamageList[i].Damage = Damage;
			DamageList[i].Obj = Object;
			DamageList[i].PosY = 0;
			DamageList[i].Time = 0;
			DamageList[i].Alpha = 255;
			DamageList[i].TypeAttack = Type;
			break;
		}
	}
}
