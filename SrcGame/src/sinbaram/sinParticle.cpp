

#include "sinLinkHeader.h"

sINTER_EFFECT sInter_Effect[SIN_MAX_INTER_EFFECT];
sINTER_EFFECT3 sInter_Effect3[4];

int MatInterEffectAging[5];
int MatInterEffectAging2[4];
int MatSuccessEffectAging;
int MatPuzzleEffect;

int  sinAgingSuccessFlag2 = 0;
int  sinAgingSuccessFlagEnd = 0;

DWORD InitCancelMixTime = 0;


int ShowDalayFlag45 = 0;

int InitInterEffect()
{
	char szPath[128];
	int i = 0;

	for(i = 1; i < 5; i++)
	{
		wsprintf(szPath, "Image\\SinImage\\Effect\\InterEffect\\par%d.tga", i);

		MatInterEffectAging2[i - 1] = CreateTextureMaterial(szPath, 0, 0, 0, 0, SMMAT_BLEND_LAMP);
	}

	for(i = 1; i < 6; i++)
	{
		wsprintf(szPath, "Image\\SinImage\\Effect\\InterEffect\\Aging%d.tga", i);
		MatInterEffectAging[i - 1] = CreateTextureMaterial(szPath, 0, 0, 0, 0, SMMAT_BLEND_LAMP);
	}

	MatSuccessEffectAging = CreateTextureMaterial("Image\\SinImage\\Effect\\InterEffect\\par-7.tga", 0, 0, 0, 0, SMMAT_BLEND_LAMP);
	MatPuzzleEffect = CreateTextureMaterial("Image\\SinImage\\Effect\\InterEffect\\P_bok.tga", 0, 0, 0, 0, SMMAT_BLEND_LAMP);

	return TRUE;
}


int MoveSuccessCraftEffect2()
{
	int  i;
	for(i = 0; i < 4; i++)
	{
		if(sInter_Effect3[i].Flag)
		{
			sInter_Effect3[i].MoveX++;
			sInter_Effect3[i].MoveY++;

			sInter_Effect3[i].MoveX *= 2;
			sInter_Effect3[i].MoveY *= 2;

			if(sInter_Effect3[i].MoveX >= 7)
			{
				sInter_Effect3[i].MoveX -= 5;
				sInter_Effect3[i].MoveY -= 5;
			}

			if(sInter_Effect3[i].MoveX >= 200)
			{
				sInter_Effect3[i].MoveX = 200;
				sInter_Effect3[i].MoveY = 200;

				sInter_Effect3[i].Flag = 0;

				sinSuccessCraftEffect();
				sinAgingSuccessFlagEnd = 1;


			}

		}

	}

	return TRUE;
}


int DrawSuccessCraftEffect2()
{
	int i;
	for(i = 0; i < 4; i++)
	{
		if(sInter_Effect3[i].Flag)
		{
			switch(i)
			{
				case 0:
				DrawSprite((sInter_Effect3[i].x - sInter_Effect3[i].MoveX2) + sInter_Effect3[i].MoveX,
						   sInter_Effect3[i].y, sInter_Effect3[i].lpSuccessEffectAging, 0, 0, sInter_Effect3[i].w, sInter_Effect3[i].h);

				break;

				case 1:
				DrawSprite(sInter_Effect3[i].x,
					(sInter_Effect3[i].y - sInter_Effect3[i].MoveY2) + sInter_Effect3[i].MoveY, sInter_Effect3[i].lpSuccessEffectAging, 0, 0, sInter_Effect3[i].w, sInter_Effect3[i].h);

				break;
				case 2:
				DrawSprite((sInter_Effect3[i].x + sInter_Effect3[i].MoveX2) - sInter_Effect3[i].MoveX,
						   sInter_Effect3[i].y, sInter_Effect3[i].lpSuccessEffectAging, 0, 0, sInter_Effect3[i].w, sInter_Effect3[i].h);

				break;
				case 3:
				DrawSprite(sInter_Effect3[i].x,
					(sInter_Effect3[i].y + sInter_Effect3[i].MoveY2) - sInter_Effect3[i].MoveY, sInter_Effect3[i].lpSuccessEffectAging, 0, 0, sInter_Effect3[i].w, sInter_Effect3[i].h);

				break;

			}
		}
	}

	return TRUE;
}



int sinSuccessCraftEffect2()
{
	memset(&sInter_Effect3, 0, sizeof(sINTER_EFFECT3) * 4);

	int i = 0;

	if(cAging.OpenFlag)
	{
		if(sAgingItem.AgingItem[0].Flag)
		{
			for(i = 0; i < 4; i++)
			{
				sInter_Effect3[i].lpSuccessEffectAging = sAgingItem.AgingItem[0].lpItem;
				sInter_Effect3[i].h = sAgingItem.AgingItem[0].h;
				sInter_Effect3[i].w = sAgingItem.AgingItem[0].w;
				sInter_Effect3[i].x = sAgingItem.AgingItem[0].x;
				sInter_Effect3[i].y = sAgingItem.AgingItem[0].y;
				sInter_Effect3[i].Flag = 1;
				sInter_Effect3[i].MoveX2 = 200;
				sInter_Effect3[i].MoveY2 = 200;
				sInter_Effect3[i].MoveX = 1;
				sInter_Effect3[i].MoveY = 1;


			}
		}
	}
	if(cCraftItem.OpenFlag)
	{
		if(sCraftItem.CraftItem[0].Flag)
		{
			for(i = 0; i < 4; i++)
			{
				sInter_Effect3[i].lpSuccessEffectAging = sCraftItem.CraftItem[0].lpItem;
				sInter_Effect3[i].h = sCraftItem.CraftItem[0].h;
				sInter_Effect3[i].w = sCraftItem.CraftItem[0].w;
				sInter_Effect3[i].x = sCraftItem.CraftItem[0].x;
				sInter_Effect3[i].y = sCraftItem.CraftItem[0].y;
				sInter_Effect3[i].Flag = 1;
				sInter_Effect3[i].MoveX2 = 200;
				sInter_Effect3[i].MoveY2 = 200;
				sInter_Effect3[i].MoveX = 1;
				sInter_Effect3[i].MoveY = 1;
			}
		}
	}

	return TRUE;
}



int sinSuccessCraftEffect()
{

	int  i = 0;
	int Count5 = 5;

	for(i = 0; i < SIN_MAX_INTER_EFFECT; i++)
	{
		if(!sInter_Effect[i].Time)
		{
			sInter_Effect[i].Kind = SIN_INTER_EFFECT_AGING_SUCCESS;
			sInter_Effect[i].Time = 1;
			sInter_Effect[i].Face.x = 58 + 11 + rand() % 22;
			sInter_Effect[i].Face.y = 193 + 11 + rand() % 44;
			sInter_Effect[i].Face.width = rand() % 5 + 4;
			sInter_Effect[i].Face.height = sInter_Effect[i].Face.width;
			sInter_Effect[i].Max_Time = rand() % 3 + 5;
			sInter_Effect[i].Face.Transparency = 255;
			sInter_Effect[i].FadeType = 1;
			sInter_Effect[i].Face.r = 255;
			sInter_Effect[i].Face.g = 255;
			sInter_Effect[i].Face.b = 255;
			sInter_Effect[i].Face.MatNum = MatSuccessEffectAging;
			sInter_Effect[i].Gravity = rand() % 10 - 5;
			sInter_Effect[i].Speed2.x = rand() % 10 - 5;
			sInter_Effect[i].Speed2.y = rand() % 10 - 5;

			Count5++;
			if(Count5 > 30)
			{
				Count5 = 0;
				break;

			}

		}
	}
	return TRUE;
}



DWORD SinBaRamDealyTime = 0;
DWORD SinBaRamDealyTime2 = 0;
int   StartInterEffectAging2 = 0;
int   sinCraftItemStartFlag = 0;
int   sinCraftItemStartFlag2 = 0;

int InterEffectAging2Process()
{

	MoveSuccessCraftEffect2();
	if(sinCraftItemStartFlag)
	{
		SinBaRamDealyTime2++;
		if(SinBaRamDealyTime2 > 100)
		{
			StartInterEffectAging2 = 1;
			sinCraftItemStartFlag = 0;
			SinBaRamDealyTime2 = 0;

		}

	}
	if(cCraftItem.OpenFlag || cAging.OpenFlag || SmeltingItem.OpenFlag || ManufactureItem.m_OpenFlag || cMixtureReset.OpenFlag)
	{
		if(sinCraftItemStartFlag2)
		{
			if(!InitCancelMixTime)
			{
				if(cCraftItem.OpenFlag || cCraftItem.iReconItemFlag)
				{
					cCraftItem.sinSendCraftItem();
				}
				if(cAging.OpenFlag)
				{
					cAging.sinSendAgingItem();
				}
				if(SmeltingItem.OpenFlag)
				{
					SmeltingItem.sinSendSmeltingItem();
				}
				if(ManufactureItem.m_OpenFlag)
				{
					ManufactureItem.sinSendManufactureItem();
				}

				if(cMixtureReset.OpenFlag)
				{
					cMixtureReset.sinSendMixtureItemReset();
				}
			}
			InitCancelMixTime++;
			if(InitCancelMixTime > 70 * 10)
			{
				sinCraftItemStartFlag2 = 0;
				ShowDalayFlag45 = 0;
				InitCancelMixTime = 0;
				MixItemNoCopyFlag = 0;
			}
		}

	}
	else
	{
		sinCraftItemStartFlag2 = 0;
		ShowDalayFlag45 = 0;
		InitCancelMixTime = 0;
		MixItemNoCopyFlag = 0;
	}
	if(!StartInterEffectAging2)return FALSE;
	SinBaRamDealyTime++;
	if(SinBaRamDealyTime < 10)return FALSE;
	SinBaRamDealyTime = 0;
	SetInterEffectAging2();



	return TRUE;
}
int sinDelayCount3 = 1;
int sinSmeltingDelayCount = 0;


int	sinMixtureResetDelayCount = 0;



int SetPuzzleEffect(int x, int y)
{
	int i = 0, j = 0, k = 0;
	int Count = 0;
	int CountTemp = 0;
	int FirstFlag = 0;

	for(i = 0; i < SIN_MAX_INTER_EFFECT; i++)
	{
		if(!sInter_Effect[i].Time)
		{
			sInter_Effect[i].Kind = SIN_INTER_EFFECT_AGING2;
			sInter_Effect[i].Time = 1;
			sInter_Effect[i].Face.x = x;
			sInter_Effect[i].Face.y = y;
			sInter_Effect[i].Face.width = rand() % 5 + 10;
			sInter_Effect[i].Face.height = sInter_Effect[i].Face.width;
			sInter_Effect[i].Max_Time = rand() % 10 + 5;
			sInter_Effect[i].Face.Transparency = 255;
			sInter_Effect[i].FadeType = 1;
			sInter_Effect[i].Face.r = 255;
			sInter_Effect[i].Face.g = 255;
			sInter_Effect[i].Face.b = 255;
			sInter_Effect[i].Face.MatNum = MatPuzzleEffect;
			sInter_Effect[i].Direction = CountTemp % 8;

			sInter_Effect[i].Speed.x = rand() % 3 + 1;
			sInter_Effect[i].Speed.y = rand() % 3 + 1;








			CountTemp++;
			if(CountTemp >= MAX_AGING)break;

		}
	}
	return TRUE;
}



int SetInterEffectAging2()
{
	int i = 0, j = 0, k = 0;
	int Count = 0;
	int CountTemp = 0;
	int FirstFlag = 0;


	if(cAging.OpenFlag)
	{
		for(j = sinDelayCount3; j < sinDelayCount3 + 1; j++)
		{
			if(sAgingItem.AgingItem[j].Flag)
			{
				sinDelayCount3++;
				for(i = 0; i < SIN_MAX_INTER_EFFECT; i++)
				{
					if(!sInter_Effect[i].Time)
					{
						sInter_Effect[i].Kind = SIN_INTER_EFFECT_AGING2;
						sInter_Effect[i].Time = 1;
						sInter_Effect[i].Face.x = sAgingItem.AgingItem[j].x + 5;
						sInter_Effect[i].Face.y = sAgingItem.AgingItem[j].y + 5;
						sInter_Effect[i].Face.width = rand() % 5 + 10;
						sInter_Effect[i].Face.height = sInter_Effect[i].Face.width;
						sInter_Effect[i].Max_Time = rand() % 10 + 5;
						sInter_Effect[i].Face.Transparency = 255;
						sInter_Effect[i].FadeType = 1;
						sInter_Effect[i].Face.r = 255;
						sInter_Effect[i].Face.g = 255;
						sInter_Effect[i].Face.b = 255;
						sInter_Effect[i].Face.MatNum = MatInterEffectAging2[sInter_Effect[i].AniCount];
						sInter_Effect[i].Direction = CountTemp % 8;

						sInter_Effect[i].Speed.x = rand() % 3 + 1;
						sInter_Effect[i].Speed.y = rand() % 3 + 1;








						CountTemp++;
						if(CountTemp >= MAX_AGING)
						{

							sAgingItem.AgingItem[j].x = 10000;
							sAgingItem.AgingItem[j].y = 10000;

							CountTemp = 0;
							sinPlaySound(SIN_SOUND_FAILD_MIXITEM);
							break;

						}
					}

				}
				return TRUE;
			}
			else
			{


				sinDelayCount3 = 1;
				StartInterEffectAging2 = 0;
				sinCraftItemStartFlag2 = 1;
				return FALSE;




			}
		}
	}


	if(cCraftItem.OpenFlag)
	{
		for(j = sinDelayCount3; j < sinDelayCount3 + 1; j++)
		{
			if(sCraftItem.CraftItem[j].Flag)
			{
				sinDelayCount3++;
				for(i = 0; i < SIN_MAX_INTER_EFFECT; i++)
				{
					if(!sInter_Effect[i].Time)
					{
						sInter_Effect[i].Kind = SIN_INTER_EFFECT_AGING2;
						sInter_Effect[i].Time = 1;
						sInter_Effect[i].Face.x = sCraftItem.CraftItem[j].x + 5;
						sInter_Effect[i].Face.y = sCraftItem.CraftItem[j].y + 5;
						sInter_Effect[i].Face.width = rand() % 5 + 5;
						sInter_Effect[i].Face.height = sInter_Effect[i].Face.width;
						sInter_Effect[i].Max_Time = rand() % 10 + 5;
						sInter_Effect[i].Face.Transparency = 255;
						sInter_Effect[i].FadeType = 1;
						sInter_Effect[i].Face.r = 255;
						sInter_Effect[i].Face.g = 255;
						sInter_Effect[i].Face.b = 255;
						sInter_Effect[i].Face.MatNum = MatInterEffectAging2[sInter_Effect[i].AniCount];
						sInter_Effect[i].Direction = CountTemp % 8;

						sInter_Effect[i].Speed.x = rand() % 2 + 1;
						sInter_Effect[i].Speed.y = rand() % 2 + 1;








						CountTemp++;
						if(CountTemp >= 24)
						{
							CountTemp = 0;
							sinPlaySound(SIN_SOUND_FAILD_MIXITEM);

							sCraftItem.CraftItem[j].x = 10000;
							sCraftItem.CraftItem[j].y = 10000;
							cCraftItem.ReFormCraftItem();
							break;

						}
					}

				}
				return TRUE;
			}
			else
			{
				sinDelayCount3 = 1;
				StartInterEffectAging2 = 0;
				sinCraftItemStartFlag2 = 1;
				return FALSE;
			}
		}
	}


	if(SmeltingItem.OpenFlag)
	{
		for(j = sinSmeltingDelayCount; j < sinSmeltingDelayCount + 1; j++)
		{
			if(S_smeltingItem.SmeltingItem[j].Flag)
			{
				sinSmeltingDelayCount++;
				for(i = 0; i < SIN_MAX_INTER_EFFECT; i++)
				{
					if(!sInter_Effect[i].Time)
					{
						sInter_Effect[i].Kind = SIN_INTER_EFFECT_AGING2;
						sInter_Effect[i].Time = 1;
						sInter_Effect[i].Face.x = S_smeltingItem.SmeltingItem[j].x + 5;
						sInter_Effect[i].Face.y = S_smeltingItem.SmeltingItem[j].y + 5;
						sInter_Effect[i].Face.width = rand() % 5 + 5;
						sInter_Effect[i].Face.height = sInter_Effect[i].Face.width;
						sInter_Effect[i].Max_Time = rand() % 10 + 5;
						sInter_Effect[i].Face.Transparency = 255;
						sInter_Effect[i].FadeType = 1;
						sInter_Effect[i].Face.r = 255;
						sInter_Effect[i].Face.g = 255;
						sInter_Effect[i].Face.b = 255;
						sInter_Effect[i].Face.MatNum = MatInterEffectAging2[sInter_Effect[i].AniCount];
						sInter_Effect[i].Direction = CountTemp % 8;

						sInter_Effect[i].Speed.x = rand() % 2 + 1;
						sInter_Effect[i].Speed.y = rand() % 2 + 1;








						CountTemp++;
						if(CountTemp >= 5)
						{
							CountTemp = 0;
							sinPlaySound(SIN_SOUND_FAILD_MIXITEM);

							S_smeltingItem.SmeltingItem[j].x = 10000;
							S_smeltingItem.SmeltingItem[j].y = 10000;
							SmeltingItem.ReFormSmeltingItem();
							break;

						}
					}

				}
				return TRUE;
			}
			else
			{
				if(sinSmeltingDelayCount < 4)
				{
					sinSmeltingDelayCount = 4;
				}
				else if(sinSmeltingDelayCount > 4)
				{
					sinSmeltingDelayCount = 0;
					StartInterEffectAging2 = 0;
					sinCraftItemStartFlag2 = 1;
					return FALSE;
				}
			}
		}
	}


	if(ManufactureItem.m_OpenFlag)
	{
		for(j = sinSmeltingDelayCount; j < sinSmeltingDelayCount + 1; j++)
		{
			if(g_sManufactureItem.ManufactureItem[j].Flag)
			{
				sinSmeltingDelayCount++;
				for(i = 0; i < SIN_MAX_INTER_EFFECT; i++)
				{
					if(!sInter_Effect[i].Time)
					{
						sInter_Effect[i].Kind = SIN_INTER_EFFECT_AGING2;
						sInter_Effect[i].Time = 1;
						sInter_Effect[i].Face.x = g_sManufactureItem.ManufactureItem[j].x + 5;
						sInter_Effect[i].Face.y = g_sManufactureItem.ManufactureItem[j].y + 5;
						sInter_Effect[i].Face.width = rand() % 5 + 5;
						sInter_Effect[i].Face.height = sInter_Effect[i].Face.width;
						sInter_Effect[i].Max_Time = rand() % 10 + 5;
						sInter_Effect[i].Face.Transparency = 255;
						sInter_Effect[i].FadeType = 1;
						sInter_Effect[i].Face.r = 255;
						sInter_Effect[i].Face.g = 255;
						sInter_Effect[i].Face.b = 255;
						sInter_Effect[i].Face.MatNum = MatInterEffectAging2[sInter_Effect[i].AniCount];
						sInter_Effect[i].Direction = CountTemp % 8;

						sInter_Effect[i].Speed.x = rand() % 2 + 1;
						sInter_Effect[i].Speed.y = rand() % 2 + 1;








						CountTemp++;
						if(CountTemp >= 24)
						{
							CountTemp = 0;
							sinPlaySound(SIN_SOUND_FAILD_MIXITEM);
							g_sManufactureItem.ManufactureItem[j].x = 10000;
							g_sManufactureItem.ManufactureItem[j].y = 10000;
							ManufactureItem.ReFormManufactureItem();
							break;
						}
					}

				}
				return TRUE;
			}
			else
			{
				sinSmeltingDelayCount = 0;
				StartInterEffectAging2 = 0;
				sinCraftItemStartFlag2 = 1;
				return FALSE;
			}
		}
	}


	if(cMixtureReset.OpenFlag)
	{
		for(j = sinMixtureResetDelayCount; j < sinMixtureResetDelayCount + 1; j++)
		{
			if(sMixtureResetItem.MixtureResetItem[j].Flag)
			{
				sinMixtureResetDelayCount++;

				for(i = 0; i < SIN_MAX_INTER_EFFECT; i++)
				{
					if(!sInter_Effect[i].Time)
					{
						sInter_Effect[i].Kind = SIN_INTER_EFFECT_AGING2;
						sInter_Effect[i].Time = 1;
						sInter_Effect[i].Face.x = sMixtureResetItem.MixtureResetItem[1].x + 5;
						sInter_Effect[i].Face.y = sMixtureResetItem.MixtureResetItem[1].y + 5;
						sInter_Effect[i].Face.width = rand() % 5 + 5;
						sInter_Effect[i].Face.height = sInter_Effect[i].Face.width;
						sInter_Effect[i].Max_Time = rand() % 10 + 5;
						sInter_Effect[i].Face.Transparency = 255;
						sInter_Effect[i].FadeType = 1;
						sInter_Effect[i].Face.r = 255;
						sInter_Effect[i].Face.g = 255;
						sInter_Effect[i].Face.b = 255;
						sInter_Effect[i].Face.MatNum = MatInterEffectAging2[sInter_Effect[i].AniCount];
						sInter_Effect[i].Direction = CountTemp % 8;

						sInter_Effect[i].Speed.x = rand() % 2 + 1;
						sInter_Effect[i].Speed.y = rand() % 2 + 1;

						CountTemp++;
						if(CountTemp >= 24)
						{
							CountTemp = 0;
							sinPlaySound(SIN_SOUND_FAILD_MIXITEM);
							sMixtureResetItem.MixtureResetItem[1].x = 10000;
							sMixtureResetItem.MixtureResetItem[1].y = 10000;
							cMixtureReset.ReformMixtureResetItem();
							break;
						}
					}
				}

				return TRUE;
			}
			else
			{
				sinMixtureResetDelayCount = 0;
				StartInterEffectAging2 = 0;
				sinCraftItemStartFlag2 = 1;

				return FALSE;
			}
		}
	}

	return TRUE;

}


int SetInterEffectMixtureReset()
{
	if(ShowDalayFlag45)return FALSE;
	ShowDalayFlag45 = 1;

	int i = 0, j = 0, k = 0;
	int Count = 0;
	int FirstFlag = 0;


	for(j = 0; j < 3; j++)
	{
		for(k = 0; k < 4; k++)
		{
			for(i = 0; i < SIN_MAX_INTER_EFFECT; i++)
			{
				if(!sInter_Effect[i].Time)
				{
					sInter_Effect[i].Time = 1;
					sInter_Effect[i].Face.x = 58 + (j * 22);
					sInter_Effect[i].Face.y = 193 + (k * 22) + sinInterHeight2;
					sInter_Effect[i].Face.width = 40;
					sInter_Effect[i].Face.height = 40;
					sInter_Effect[i].Face.x -= 9;
					sInter_Effect[i].Face.y -= 9;
					sInter_Effect[i].Kind = SIN_INTER_EFFECT_AGING;



					sInter_Effect[i].Max_Time = 50;
					sInter_Effect[i].Face.Transparency = 255;
					sInter_Effect[i].FadeType = 1;
					sInter_Effect[i].Face.r = 255;
					sInter_Effect[i].Face.g = 255;
					sInter_Effect[i].Face.b = 255;
					sInter_Effect[i].AniCount = k % 4;
					sInter_Effect[i].Face.MatNum = MatInterEffectAging[sInter_Effect[i].AniCount];
					sInter_Effect[i].Direction = -1;
					break;
				}
			}
		}
	}


	for(i = 0; i < SIN_MAX_INTER_EFFECT; i++)
	{
		if(!sInter_Effect[i].Time)
		{
			sInter_Effect[i].Time = 1;
			sInter_Effect[i].Face.x = 218 + 22;
			sInter_Effect[i].Face.y = 193 + sinInterHeight2 + 28;
			sInter_Effect[i].Face.MatNum = MatInterEffectAging[0];
			sInter_Effect[i].Max_Time = 50;
			sInter_Effect[i].Face.width = 40;
			sInter_Effect[i].Face.height = 40;
			sInter_Effect[i].Face.x -= 9;
			sInter_Effect[i].Face.y -= 9;
			sInter_Effect[i].Kind = SIN_INTER_EFFECT_AGING;

			sInter_Effect[i].Face.Transparency = 255;
			sInter_Effect[i].FadeType = 255;
			sInter_Effect[i].Face.r = 255;
			sInter_Effect[i].Face.g = 255;
			sInter_Effect[i].Face.b = 255;
			sInter_Effect[i].AniCount = k % 4;
			sInter_Effect[i].Face.MatNum = MatInterEffectAging[0];
			sInter_Effect[i].Direction = -1;
			break;
		}
	}

	return TRUE;
}




int SetInterEffectAging()
{
	if(ShowDalayFlag45)return FALSE;
	ShowDalayFlag45 = 1;

	int i = 0, j = 0, k = 0;
	int Count = 0;
	int FirstFlag = 0;




	for(j = 0; j < 3; j++)
	{
		for(k = 0; k < 4; k++)
		{
			for(i = 0; i < SIN_MAX_INTER_EFFECT; i++)
			{
				if(!sInter_Effect[i].Time)
				{
					sInter_Effect[i].Time = 1;
					sInter_Effect[i].Face.x = 58 + (j * 22);
					sInter_Effect[i].Face.y = 193 + (k * 22) + sinInterHeight2;
					sInter_Effect[i].Face.width = 40;
					sInter_Effect[i].Face.height = 40;
					sInter_Effect[i].Face.x -= 9;
					sInter_Effect[i].Face.y -= 9;
					sInter_Effect[i].Kind = SIN_INTER_EFFECT_AGING;



					sInter_Effect[i].Max_Time = 50;
					sInter_Effect[i].Face.Transparency = 255;
					sInter_Effect[i].FadeType = 1;
					sInter_Effect[i].Face.r = 255;
					sInter_Effect[i].Face.g = 255;
					sInter_Effect[i].Face.b = 255;
					sInter_Effect[i].AniCount = k % 4;
					sInter_Effect[i].Face.MatNum = MatInterEffectAging[sInter_Effect[i].AniCount];
					sInter_Effect[i].Direction = -1;
					break;
				}
			}
		}
	}
	for(j = 0; j < 3; j++)
	{
		for(k = 0; k < 4; k++)
		{
			for(i = 0; i < SIN_MAX_INTER_EFFECT; i++)
			{
				if(!sInter_Effect[i].Time)
				{
					sInter_Effect[i].Time = 1;
					sInter_Effect[i].Face.x = 218 + (j * 22);
					sInter_Effect[i].Face.y = 193 + (k * 22) + sinInterHeight2;
					sInter_Effect[i].Face.MatNum = MatInterEffectAging[0];

					sInter_Effect[i].Max_Time = 50;
					sInter_Effect[i].Face.width = 40;
					sInter_Effect[i].Face.height = 40;
					sInter_Effect[i].Face.x -= 9;
					sInter_Effect[i].Face.y -= 9;
					sInter_Effect[i].Kind = SIN_INTER_EFFECT_AGING;

					sInter_Effect[i].Face.Transparency = 255;
					sInter_Effect[i].FadeType = 255;
					sInter_Effect[i].Face.r = 255;
					sInter_Effect[i].Face.g = 255;
					sInter_Effect[i].Face.b = 255;
					sInter_Effect[i].AniCount = k % 4;

					sInter_Effect[i].Face.MatNum = MatInterEffectAging[0];
					sInter_Effect[i].Direction = -1;


					break;

				}

			}

		}

	}


	return TRUE;
}


int SetInterEffectSmelting()
{
	if(ShowDalayFlag45)return FALSE;
	ShowDalayFlag45 = 1;

	int i = 0, j = 0, k = 0;
	int Count = 0;
	int FirstFlag = 0;

	for(j = 0; j < 2; j++)
	{
		for(k = 0; k < 2; k++)
		{
			for(i = 0; i < SIN_MAX_INTER_EFFECT; i++)
			{
				if(!sInter_Effect[i].Time)
				{
					sInter_Effect[i].Time = 1;
					sInter_Effect[i].Face.x = 69 + (j * 22);
					sInter_Effect[i].Face.y = 210 + (k * 22) + sinInterHeight2;
					sInter_Effect[i].Face.width = 40;
					sInter_Effect[i].Face.height = 40;
					sInter_Effect[i].Face.x -= 9;
					sInter_Effect[i].Face.y -= 9;
					sInter_Effect[i].Kind = SIN_INTER_EFFECT_AGING;


					sInter_Effect[i].Max_Time = 50;
					sInter_Effect[i].Face.Transparency = 255;
					sInter_Effect[i].FadeType = 1;
					sInter_Effect[i].Face.r = 255;
					sInter_Effect[i].Face.g = 255;
					sInter_Effect[i].Face.b = 255;
					sInter_Effect[i].AniCount = k % 4;
					sInter_Effect[i].Face.MatNum = MatInterEffectAging[sInter_Effect[i].AniCount];
					sInter_Effect[i].Direction = -1;
					break;
				}
			}
		}
	}
	for(i = 0; i < SIN_MAX_INTER_EFFECT; i++)
	{
		if(!sInter_Effect[i].Time)
		{
			sInter_Effect[i].Time = 1;
			sInter_Effect[i].Face.x = 218 + 22;
			sInter_Effect[i].Face.y = 193 + sinInterHeight2 + 28;
			sInter_Effect[i].Face.MatNum = MatInterEffectAging[0];
			sInter_Effect[i].Max_Time = 50;
			sInter_Effect[i].Face.width = 40;
			sInter_Effect[i].Face.height = 40;
			sInter_Effect[i].Face.x -= 9;
			sInter_Effect[i].Face.y -= 9;
			sInter_Effect[i].Kind = SIN_INTER_EFFECT_AGING;

			sInter_Effect[i].Face.Transparency = 255;
			sInter_Effect[i].FadeType = 255;
			sInter_Effect[i].Face.r = 255;
			sInter_Effect[i].Face.g = 255;
			sInter_Effect[i].Face.b = 255;
			sInter_Effect[i].AniCount = k % 4;
			sInter_Effect[i].Face.MatNum = MatInterEffectAging[0];
			sInter_Effect[i].Direction = -1;
			break;
		}
	}
	return TRUE;
}


int SetInterEffectManufacture()
{
	if(ShowDalayFlag45)return FALSE;
	ShowDalayFlag45 = 1;

	int i = 0, j = 0, k = 0;
	int Count = 0;
	int FirstFlag = 0;



	for(j = 0; j < 3; j++)
	{
		for(k = 0; k < 4; k++)
		{
			for(i = 0; i < SIN_MAX_INTER_EFFECT; i++)
			{
				if(!sInter_Effect[i].Time)
				{
					sInter_Effect[i].Time = 1;
					sInter_Effect[i].Face.x = 58 + (j * 22);
					sInter_Effect[i].Face.y = 193 + (k * 22) + sinInterHeight2;
					sInter_Effect[i].Face.width = 40;
					sInter_Effect[i].Face.height = 40;
					sInter_Effect[i].Face.x -= 9;
					sInter_Effect[i].Face.y -= 9;
					sInter_Effect[i].Kind = SIN_INTER_EFFECT_AGING;

					sInter_Effect[i].Max_Time = 50;
					sInter_Effect[i].Face.Transparency = 255;
					sInter_Effect[i].FadeType = 1;
					sInter_Effect[i].Face.r = 255;
					sInter_Effect[i].Face.g = 255;
					sInter_Effect[i].Face.b = 255;
					sInter_Effect[i].AniCount = k % 4;
					sInter_Effect[i].Face.MatNum = MatInterEffectAging[sInter_Effect[i].AniCount];
					sInter_Effect[i].Direction = -1;
					break;
				}
			}
		}
	}

	for(i = 0; i < SIN_MAX_INTER_EFFECT; i++)
	{
		if(!sInter_Effect[i].Time)
		{
			sInter_Effect[i].Time = 1;
			sInter_Effect[i].Face.x = 240;
			sInter_Effect[i].Face.y = 206 + sinInterHeight2;
			sInter_Effect[i].Face.MatNum = MatInterEffectAging[0];
			sInter_Effect[i].Max_Time = 50;
			sInter_Effect[i].Face.width = 40;
			sInter_Effect[i].Face.height = 40;
			sInter_Effect[i].Face.x -= 9;
			sInter_Effect[i].Face.y -= 9;
			sInter_Effect[i].Kind = SIN_INTER_EFFECT_AGING;

			sInter_Effect[i].Face.Transparency = 255;
			sInter_Effect[i].FadeType = 255;
			sInter_Effect[i].Face.r = 255;
			sInter_Effect[i].Face.g = 255;
			sInter_Effect[i].Face.b = 255;
			sInter_Effect[i].AniCount = k % 4;
			sInter_Effect[i].Face.MatNum = MatInterEffectAging[0];
			sInter_Effect[i].Direction = -1;

			break;
		}
	}
	for(i = 0; i < SIN_MAX_INTER_EFFECT; i++)
	{
		if(!sInter_Effect[i].Time)
		{
			sInter_Effect[i].Time = 1;
			sInter_Effect[i].Face.x = 214;
			sInter_Effect[i].Face.y = 238 + sinInterHeight2;
			sInter_Effect[i].Face.MatNum = MatInterEffectAging[0];
			sInter_Effect[i].Max_Time = 50;
			sInter_Effect[i].Face.width = 40;
			sInter_Effect[i].Face.height = 40;
			sInter_Effect[i].Face.x -= 9;
			sInter_Effect[i].Face.y -= 9;
			sInter_Effect[i].Kind = SIN_INTER_EFFECT_AGING;

			sInter_Effect[i].Face.Transparency = 255;
			sInter_Effect[i].FadeType = 255;
			sInter_Effect[i].Face.r = 255;
			sInter_Effect[i].Face.g = 255;
			sInter_Effect[i].Face.b = 255;
			sInter_Effect[i].AniCount = k % 4;
			sInter_Effect[i].Face.MatNum = MatInterEffectAging[0];
			sInter_Effect[i].Direction = -1;

			break;
		}
	}
	for(i = 0; i < SIN_MAX_INTER_EFFECT; i++)
	{
		if(!sInter_Effect[i].Time)
		{
			sInter_Effect[i].Time = 1;
			sInter_Effect[i].Face.x = 264;
			sInter_Effect[i].Face.y = 238 + sinInterHeight2;
			sInter_Effect[i].Face.MatNum = MatInterEffectAging[0];
			sInter_Effect[i].Max_Time = 50;
			sInter_Effect[i].Face.width = 40;
			sInter_Effect[i].Face.height = 40;
			sInter_Effect[i].Face.x -= 9;
			sInter_Effect[i].Face.y -= 9;
			sInter_Effect[i].Kind = SIN_INTER_EFFECT_AGING;

			sInter_Effect[i].Face.Transparency = 255;
			sInter_Effect[i].FadeType = 255;
			sInter_Effect[i].Face.r = 255;
			sInter_Effect[i].Face.g = 255;
			sInter_Effect[i].Face.b = 255;
			sInter_Effect[i].AniCount = k % 4;
			sInter_Effect[i].Face.MatNum = MatInterEffectAging[0];
			sInter_Effect[i].Direction = -1;

			break;
		}
	}
	return TRUE;
}

int sinActiveInterEffect()
{


	int i, count7 = 0;
	for(i = 0; i < SIN_MAX_INTER_EFFECT; i++)
	{
		if(sInter_Effect[i].Time)
		{

			if(sInter_Effect[i].Kind == SIN_INTER_EFFECT_AGING_SUCCESS && (sInter_Effect[i].Time % 15) == 0)
			{
				sInter_Effect[i].Gravity++;

			}
			sInter_Effect[i].Face.x += sInter_Effect[i].Speed2.x;
			sInter_Effect[i].Face.y += sInter_Effect[i].Speed2.y + sInter_Effect[i].Gravity;


			switch(sInter_Effect[i].Direction)
			{
				case 0:
				sInter_Effect[i].Face.x -= sInter_Effect[i].Speed.x;
				sInter_Effect[i].Face.y -= sInter_Effect[i].Speed.y;

				break;
				case 1:
				sInter_Effect[i].Face.x -= sInter_Effect[i].Speed.x;
				sInter_Effect[i].Face.y += sInter_Effect[i].Speed.y;

				break;
				case 2:
				sInter_Effect[i].Face.x += sInter_Effect[i].Speed.x;
				sInter_Effect[i].Face.y -= sInter_Effect[i].Speed.y;

				break;
				case 3:
				sInter_Effect[i].Face.x += sInter_Effect[i].Speed.x;
				sInter_Effect[i].Face.y += sInter_Effect[i].Speed.y;

				break;
				case 4:
				sInter_Effect[i].Face.x += sInter_Effect[i].Speed.x;


				break;
				case 5:
				sInter_Effect[i].Face.x -= sInter_Effect[i].Speed.x;


				break;
				case 6:

				sInter_Effect[i].Face.y -= sInter_Effect[i].Speed.y;

				break;
				case 7:

				sInter_Effect[i].Face.y += sInter_Effect[i].Speed.y;

				break;

			}



			sInter_Effect[i].Time++;
			if(sInter_Effect[i].Kind == SIN_INTER_EFFECT_AGING2)
			{
				if(sInter_Effect[i].Time > sInter_Effect[i].Max_Time)
				{
					sInter_Effect[i].Face.Transparency -= 50;
				}



			}
			else
			{
				if(sInter_Effect[i].Time > sInter_Effect[i].Max_Time)
				{
					if(sInter_Effect[i].AniCount == 3)
					{
						sInter_Effect[i].AniKeyFlag2 = 1;
						sInter_Effect[i].Face.Transparency -= 7;
						if(sInter_Effect[i].Face.Transparency < 0)
						{
							memset(&sInter_Effect[i], 0, sizeof(sINTER_EFFECT));
							sInter_Effect[i].Time = 0;
						}
					}
				}
			}



			if((sInter_Effect[i].Time % 5) == 0 && !sInter_Effect[i].AniKeyFlag2)
			{

				if(sInter_Effect[i].AniCount >= 3)
				{
					sInter_Effect[i].AniKeyFlag = 1;

				}
				if(sInter_Effect[i].AniCount == 0)
				{
					sInter_Effect[i].AniKeyFlag = 0;

				}
				if(sInter_Effect[i].AniKeyFlag)
					sInter_Effect[i].AniCount--;
				else sInter_Effect[i].AniCount++;


				if(sInter_Effect[i].Kind == SIN_INTER_EFFECT_AGING2)
					sInter_Effect[i].Face.MatNum = MatInterEffectAging2[sInter_Effect[i].AniCount];
				if(sInter_Effect[i].Kind == SIN_INTER_EFFECT_AGING)
					sInter_Effect[i].Face.MatNum = MatInterEffectAging[sInter_Effect[i].AniCount];









			}


			if(sInter_Effect[i].Face.Transparency <= 0)
			{
				memset(&sInter_Effect[i], 0, sizeof(sINTER_EFFECT));
				sInter_Effect[i].Time = 0;
			}


		}
	}

	return TRUE;
}


int sinDrawInterEffect()
{
	int i = 0;
	for(i = 0; i < SIN_MAX_INTER_EFFECT; i++)
	{
		if(sInter_Effect[i].Time)
		{
			cInvenTory.sinDrawInvenTexImage(&sInter_Effect[i].Face);

		}

	}
	DrawSuccessCraftEffect2();
	return TRUE;
}



int sinSetParticle(int Kind, int Color, int x, int y, int z)
{

	return TRUE;
}
