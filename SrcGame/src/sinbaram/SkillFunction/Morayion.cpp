

#include "..\\sinLinkHeader.h"



DWORD sinNotToggleSkill_CODE[][5] =
{
	{SKILL_A_MIGAL},
	{SKILL_A_MIDRANDA},
	{SKILL_R_MAKER},
	{SKILL_R_KNIGHT},
	{SKILL_ALAS},
	{SKILL_BLIND},
	{SKILL_INPES},
	{SKILL_HOLY_BODY,SKILL_DRASTIC_SPIRIT,0},
	{SKILL_HOLY_VALOR,0},
	{SKILL_ZENITH,0},
	{SKILL_WINDY,0},
	{SKILL_HOLY_REFLECTION,0},
	{SKILL_SPIRIT_ELEMENTAL,0},
	{SKILL_DANCING_SWORD,0},
	{SKILL_CONCENTRATION,0},
	{SKILL_SWIFT_AXE,0},
	{SKILL_FALCON,0},
	{SKILL_GOLDEN_FALCON,0},
	{SKILL_SCOUT_HAWK,0},
	{SKILL_DIVINE_INHALATION,0},
	{SKILL_METAL_ARMOR,0},
	{SKILL_SPARK_SHIELD,0},
	{SKILL_VANISH,0},
	{SKILL_GODLY_SHIELD,0},
	{SKILL_GOD_BLESS,0},
	{SKILL_FROST_JAVELIN,0},
	{SKILL_REGENERATION_FIELD,0},
	{SKILL_SUMMON_MUSPELL,0},
	{SKILL_FIRE_ELEMENTAL,0},
	{SKILL_DISTORTION,0},

	{SKILL_MAGNETIC_SPHERE,0},
	{SKILL_METAL_GOLEM,0},
	{SKILL_BERSERKER,0},
	{SKILL_ASSASSIN_EYE,0},
	{SKILL_VAGUE,0},
	{SKILL_RECALL_WOLVERIN,0},

	{SCROLL_INVULNERABILITY,0},
	{SCROLL_CRITICAL,0},
	{SCROLL_EVASION,0},
	{STONE_R_FIRECRYTAL,0},
	{STONE_R_ICECRYTAL,0},
	{STONE_R_LINGHTINGCRYTAL,0},
	{STONE_A_FIGHTER,0},
	{STONE_A_MECHANICIAN,0},
	{STONE_A_PIKEMAN,0},
	{STONE_A_ARCHER,0},
	{STONE_A_KNIGHT,0},
	{STONE_A_ATALANTA,0},
	{STONE_A_MAGICIAN,0},
	{STONE_A_PRIESTESS,0},

	0,
};

int sinCheckSkillUseOk(sSKILL *lpSkill)
{

	ContinueSkillCancelFlag = 0;
	int i = 0;


	if(!cSkill.CheckCharSkillInfo())return FALSE;

#define  CHAR_SKILL_MASK 0xFF000000


	int   CharCode[10] = { JOBCODE_MECHANICIAN, JOBCODE_FIGHTER, JOBCODE_ARCHER, JOBCODE_PIKEMAN, JOBCODE_KNIGHT, JOBCODE_ATALANTA, JOBCODE_PRIESTESS, JOBCODE_MAGICIAN,JOBCODE_ASSASSINE,JOBCODE_SHAMAN };
	DWORD CharSkillCode[10] = { GROUP_MECHANICIAN,GROUP_FIGHTER ,  GROUP_ARCHER,GROUP_PIKEMAN,GROUP_KNIGHT,GROUP_ATALANTA,GROUP_PRIESTESS,GROUP_MAGICIAN,GROUP_ASSASSINE,GROUP_SHAMAN};

	for(int j = 0; j < 10; j++)
	{
		if(CharCode[j] == sinChar->JOB_CODE)
		{
			if((lpSkill->CODE & CHAR_SKILL_MASK) != CharSkillCode[j])
			{
				return FALSE;
			}
		}
	}








	if(chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
	{
		if(sinGetMana() - (lpSkill->Skill_Info.UseMana[lpSkill->Point - 1] - ((lpSkill->Skill_Info.UseMana[lpSkill->Point - 1] * chaPremiumitem.m_ManaReducePotionValue / 100) +
			(lpSkill->Skill_Info.UseMana[lpSkill->Point - 1] * 20 / 100))) < 0)
			return FALSE;
	}

	else if(chaPremiumitem.m_ManaReducePotiontime > 0)
	{
		if(sinGetMana() - (lpSkill->Skill_Info.UseMana[lpSkill->Point - 1] - (lpSkill->Skill_Info.UseMana[lpSkill->Point - 1] * chaPremiumitem.m_ManaReducePotionValue / 100)) < 0)
			return FALSE;
	}

	else if(chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
	{
		if(sinGetMana() - (lpSkill->Skill_Info.UseMana[lpSkill->Point - 1] - (lpSkill->Skill_Info.UseMana[lpSkill->Point - 1] * 20 / 100)) < 0)
			return FALSE;
	}

	else
	{
		if((sinGetMana() - lpSkill->Skill_Info.UseMana[lpSkill->Point - 1]) < 0)
			return FALSE;
	}


	int CntSkillNum = 0;
	int k = 0;

	int Index3 = 0;
	if(Index3 = cSkill.SearchContiueSkillIndex(SKILL_FORCE_OF_NATURE))
	{
		if(ContinueSkill[Index3 - 1].Flag == 1 && lpSkill->CODE == SKILL_FORCE_OF_NATURE)
			return FALSE;
	}

	if(Index3 = cSkill.SearchContiueSkillIndex(SKILL_HALL_OF_VALHALLA))
	{
		if(ContinueSkill[Index3 - 1].Flag == 1 && lpSkill->CODE == SKILL_HALL_OF_VALHALLA)
			return FALSE;
	}

	while(1)
	{
		if(!sinNotToggleSkill_CODE[CntSkillNum][0])break;
		for(i = 0; 0 != sinNotToggleSkill_CODE[CntSkillNum][i]; i++)
		{
			if(sinNotToggleSkill_CODE[CntSkillNum][i] == lpSkill->CODE)
			{

				for(k = 0; 0 != sinNotToggleSkill_CODE[CntSkillNum][k]; k++)
				{
					for(int j = 0; j < MAX_CONTINUE_SKILL; j++)
					{
						if(ContinueSkill[j].Flag && ContinueSkill[j].CODE == sinNotToggleSkill_CODE[CntSkillNum][k])
						{
							return FALSE;
						}
					}
				}
			}
		}
		CntSkillNum++;
	}


	int UseFlag = 0;
	int UseFlag2 = 0;

	if(lpSkill->Skill_Info.UseWeaponCode[0])
	{
		UseFlag = 1;
		for(int i = 0; i < 8; i++)
		{
			if(lpSkill->Skill_Info.UseWeaponCode[i])
			{
				if(lpSkill->Skill_Info.UseWeaponCode[i] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE&sinITEM_MASK2))
				{
					UseFlag2 = 1;
					break;
				}
			}
		}
	}


	if(lpSkill->CODE == SKILL_METAL_ARMOR)
	{
		if(sInven[2].ItemIndex)
		{
			if(cInvenTory.InvenItem[sInven[2].ItemIndex - 1].sItemInfo.JobCodeMask == sinChar->JobBitMask)
			{
				if(lpSkill->UseSkillFlag)
				{
					return TRUE;
				}
			}
		}
		return FALSE;
	}

	if(UseFlag)
	{
		if(UseFlag2 && lpSkill->UseSkillFlag)
			return TRUE;
	}
	else
	{
		if(lpSkill->UseSkillFlag)
			return TRUE;
	}


	if(lpSkill->CODE == SKILL_SHIELD_STRIKE || lpSkill->CODE == SKILL_EXTREME_SHIELD || lpSkill->CODE == SKILL_DIVINE_INHALATION || lpSkill->CODE == SKILL_SPARK_SHIELD || lpSkill->CODE == SKILL_GODLY_SHIELD)
	{
		if(lpSkill->UseSkillFlag)
		{
			if(lpSkill->Skill_Info.UseWeaponCode[0] == (cInvenTory.InvenItem[sInven[1].ItemIndex - 1].CODE&sinITEM_MASK2))
			{
				return TRUE;
			}
		}
	}


	if(lpSkill->CODE == SKILL_SOUL_SUCKER)
	{
		if(cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sItemInfo.ItemKindCode == ITEM_KIND_CRAFT ||
		   cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sItemInfo.ItemKindCode == ITEM_KIND_AGING)
		{
			if(lpSkill->Skill_Info.UseWeaponCode[0] == (cInvenTory.InvenItem[sInven[1].ItemIndex - 1].CODE&sinITEM_MASK2))
			{
				if(lpSkill->UseSkillFlag)
				{
					return TRUE;
				}
			}
		}

	}
	return FALSE;
}


int sinUseManaStamina(sSKILL *lpSkill)
{



	if(chaPremiumitem.m_ManaReducePotiontime > 0 && chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
	{
		sinSetMana(sinGetMana() - (lpSkill->Skill_Info.UseMana[lpSkill->Point - 1] -
			((lpSkill->Skill_Info.UseMana[lpSkill->Point - 1] * chaPremiumitem.m_ManaReducePotionValue / 100) +
								   (lpSkill->Skill_Info.UseMana[lpSkill->Point - 1] * 20 / 100))));
	}

	else if(chaPremiumitem.m_ManaReducePotiontime > 0)
	{
		sinSetMana(sinGetMana() - (lpSkill->Skill_Info.UseMana[lpSkill->Point - 1] - (lpSkill->Skill_Info.UseMana[lpSkill->Point - 1] * chaPremiumitem.m_ManaReducePotionValue / 100)));
	}

	else if(chaPremiumitem.m_TerryTime > 0 && sinChar->GravityScroolCheck[1] == 1)
	{
		sinSetMana(sinGetMana() - (lpSkill->Skill_Info.UseMana[lpSkill->Point - 1] - (lpSkill->Skill_Info.UseMana[lpSkill->Point - 1] * 20 / 100)));
	}

	else
	{
		if(lpSkill->Skill_Info.UseMana)
			sinSetMana(sinGetMana() - lpSkill->Skill_Info.UseMana[lpSkill->Point - 1]);
	}



	if(lpSkill->Skill_Info.UseStamina[0])
	{
		if(chaPremiumitem.m_StaminaReducePotiontime <= 0)
		{
			sinSetStamina(sinGetStamina() - (lpSkill->Skill_Info.UseStamina[0] + (lpSkill->Skill_Info.UseStamina[1] * (lpSkill->Point - 1))));
		}
		else
		{
			sinSetStamina(sinGetStamina() - ((lpSkill->Skill_Info.UseStamina[0] + (lpSkill->Skill_Info.UseStamina[1] * (lpSkill->Point - 1)))
											 - ((lpSkill->Skill_Info.UseStamina[0] + (lpSkill->Skill_Info.UseStamina[1] * (lpSkill->Point - 1))) * chaPremiumitem.m_StaminaReducePotionValue / 100)));
		}
	}

	cSkill.CheckSkillMasteryForm(lpSkill);
	lpSkill->Mastery = 0;
	cSkill.ReformSkillMasteryForm(lpSkill);


	lpSkill->UseSKillIncreCount++;
	if(lpSkill->UseSKillIncreCount >= sinMasteryIncreaIndex[lpSkill->Skill_Info.SkillNum] + ((lpSkill->Point - 1) / 3))
	{
		lpSkill->UseSKillIncreCount = 0;
		lpSkill->UseSkillCount += USE_SKILL_MASTERY_COUNT;

	}

	return TRUE;
}


int sinContinueSkillSet(sSKILL *lpSkill)
{
	int i = 0;

	if(lpSkill->CODE == SKILL_ENERGY_SHIELD || lpSkill->CODE == SKILL_COMPULSION)
	{
		for(i = 0; i < MAX_CONTINUE_SKILL; i++)
		{
			if(ContinueSkill[i].Flag)
			{
				if(ContinueSkill[i].CODE == SKILL_ENERGY_SHIELD || ContinueSkill[i].CODE == SKILL_COMPULSION)
				{
					memset(&ContinueSkill[i], 0, sizeof(sSKILL));
					break;
				}
			}
		}
	}

	for(i = 0; i < MAX_CONTINUE_SKILL; i++)
	{
		if(!ContinueSkill[i].Flag)
		{
			memcpy(&ContinueSkill[i], lpSkill, sizeof(sSKILL));
			ContinueSkill[i].Flag = 1;
			cSkill.SearchSkillDoc(&ContinueSkill[i]);
			if((lpSkill->CODE != SKILL_FORCE_ORB && lpSkill->CODE != DELAY_GLOBAL && lpSkill->CODE != QUEST_DIARY && lpSkill->CODE != BATTLE_LEVEL && lpSkill->CODE != PLAYER_ARENA && lpSkill->CODE != CHANGE_JOB3_QUEST &&lpSkill->CODE != CHANGE_ELEMENTARY_QUEST &&
				lpSkill->CODE != BOOSTER_ITEM_LIFE && lpSkill->CODE != BOOSTER_ITEM_MANA && lpSkill->CODE != BOOSTER_ITEM_STAMINA))
				ContinueSkill[i].MatIcon = 0;
			break;

		}
	}

	return TRUE;
}

int sinCheckContinueSkill()
{


	return TRUE;
}

int sinSwitchSkill(sSKILL *pSkill)
{


	return TRUE;
}



int F_DarkBolt()
{

	sinUseManaStamina(pUseSkill);
	return TRUE;
}


int F_DarkWave()
{

	sinUseManaStamina(pUseSkill);
	return TRUE;
}

int F_CurseLazy()
{

	sinUseManaStamina(pUseSkill);
	return TRUE;
}

int F_SpiritualFlare()
{

	sinUseManaStamina(pUseSkill);
	return TRUE;
}

int F_SoulManacle()
{

	sinUseManaStamina(pUseSkill);
	return TRUE;
}

int F_ChasingHunt()
{

	sinUseManaStamina(pUseSkill);
	return TRUE;
}

int F_AdventMigal()
{
	pUseSkill->UseTime = AdventMigal_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	sinSwitchSkill(pUseSkill);

	cInvenTory.SetItemToChar();

	return TRUE;
}

int F_LandGhost()
{

	sinUseManaStamina(pUseSkill);
	return TRUE;
}

int F_RainMaker()
{
	pUseSkill->UseTime = RainMaker_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	sinSwitchSkill(pUseSkill);

	cInvenTory.SetItemToChar();

	return TRUE;

}

int F_Haunt()
{

	sinUseManaStamina(pUseSkill);
	return TRUE;
}


int F_Scratch()
{

	sinUseManaStamina(pUseSkill);
	return TRUE;
}

int F_RBloodyKnight()
{

	pUseSkill->UseTime = BloodyKnight_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	sinSwitchSkill(pUseSkill);
	SummonSkillCodeIndex[3] = 0;

	return TRUE;
}

int F_Judgement()
{

	sinUseManaStamina(pUseSkill);
	return TRUE;
}

int F_AdventMidranda()
{
	pUseSkill->UseTime = AdventMidranda_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	sinSwitchSkill(pUseSkill);
	cInvenTory.SetItemToChar();
	return TRUE;
}

int F_MourningOfPray()
{

	sinUseManaStamina(pUseSkill);
	return TRUE;
}


int F_Sword_Blast()
{

	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_HolyBody()
{
	pUseSkill->UseTime = HolyBody_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	sinSwitchSkill(pUseSkill);
	return TRUE;
}
int F_Physical_Traning()
{

	return TRUE;
}
int F_Double_Crash()
{

	sinUseManaStamina(pUseSkill);
	return TRUE;
}


int F_S_Strike()
{

	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_Farina()
{

	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_D_Mastery()
{


	return TRUE;
}
int F_V_Spear()
{

	sinUseManaStamina(pUseSkill);
	return TRUE;
}


int F_Healing()
{

	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_HolyBolt()
{

	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_M_Spark()
{

	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_HolyMind()
{

	sinUseManaStamina(pUseSkill);
	return TRUE;
}


int F_Agony()
{
	short TempLife, TempLife2, TempMana;
	sinUseManaStamina(pUseSkill);
	TempLife = (short)(((float)sinChar->Life[1] / 100.0f)*(float)Agony_ConvLife[pUseSkill->Point - 1]);
	TempMana = (short)(((float)sinChar->Mana[1] / 100.0f)*(float)Agony_ConvLife[pUseSkill->Point - 1]);
	if((sinGetLife() - TempLife) > 0)
	{
		TempLife2 = sinGetLife() - TempLife;
		sinSetLife(TempLife2);
		TempMana = sinGetMana() + TempMana;
		sinSetMana(TempMana);

	};




	return TRUE;
}
int F_FireBolt()
{

	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_Zenith()
{

	pUseSkill->UseTime = Zenith_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	cInvenTory.SetItemToChar();
	return TRUE;
}
int F_ZenithFromServer(int Time)
{
	for(int i = 0; i < MAX_CONTINUE_SKILL; i++)
	{
		if(!ContinueSkill[i].Flag)
		{
			ContinueSkill[i].Flag = 1;
			ContinueSkill[i].CODE = SKILL_ZENITH;
			ContinueSkill[i].Time[1] = Time;
			ContinueSkill[i].PartyFlag = 1;
			break;

		}
	}
	sinUseManaStamina(pUseSkill);
	return TRUE;
}

int F_FireBall()
{

	sinUseManaStamina(pUseSkill);
	return TRUE;
}


int F_Holy_Valor()
{

	pUseSkill->UseTime = Holy_Valor_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	sinSwitchSkill(pUseSkill);
	return TRUE;
}

int F_Brandish()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_Piercing()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}

int F_Drastic_Spirit()
{
	pUseSkill->UseTime = Drastic_Spirit_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	sinSwitchSkill(pUseSkill);
	cInvenTory.SetItemToChar();
	return TRUE;
}

int F_Windy()
{

	pUseSkill->UseTime = Windy_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	cInvenTory.SetItemToChar();
	return TRUE;
}

int F_Twist_Javelin()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}

int F_Soul_Sucker()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}

int F_Fire_Javelin()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}


int F_Meditation()
{
	return TRUE;
}

int F_Divine_Lightning()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}

int F_Holy_Reflection()
{
	pUseSkill->UseTime = Holy_Reflection_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	return TRUE;
}

int F_Grand_Healing()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}

int F_Mental_Mastery()
{
	return TRUE;
}

int F_Watornado()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}

int F_Enchant_Weapon()
{



	sinUseManaStamina(pUseSkill);
	return TRUE;
}

int F_Dead_Ray()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}



int F_S_Mastery()
{

	return TRUE;
}

int F_D_Inhalation()
{
	pUseSkill->UseTime = D_Inhalation_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	SwitchSkill(pUseSkill);
	cInvenTory.SetItemToChar();
	return TRUE;
}
int F_Holy_Incantation()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_Grand_Cross()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;

}


int F_Split_Javelin()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_T_Of_Valhalla()
{


	sinUseManaStamina(pUseSkill);



	if(!pUseSkill->SkillTaget_CODE)
		SetT_Of_ValhallaFlag2 = 1;


	return TRUE;
}
int F_Lightning_Javelin()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_Storm_Javelin()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}


int F_Vigor_Ball()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_Resurrection()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_Extinction()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_Virtual_Life()
{


	sinUseManaStamina(pUseSkill);


	return TRUE;
}


int F_Energy_Shield()
{
	pUseSkill->UseTime = Energy_Shield_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_Diastrophism()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_Spirit_Elemental()
{
	pUseSkill->UseTime = Spirit_Elemental_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	cInvenTory.SetItemToChar();
	return TRUE;
}
int F_D_Sword()
{
	pUseSkill->UseTime = Dancing_Sword_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	cInvenTory.SetItemToChar();
	return TRUE;
}


int F_Divine_Piercing()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_Godly_Shield()
{
	pUseSkill->UseTime = Godly_Shield_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	SwitchSkill(pUseSkill);
	return TRUE;
}
int F_God_Bless()
{
	pUseSkill->UseTime = God_Bless_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	cInvenTory.SetItemToChar();
	return TRUE;
}
int F_Sword_Of_Justice()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}


int F_Hall_Of_Valhalla()
{

	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_X_Rage()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_Frost_Javelin()
{
	pUseSkill->UseTime = Frost_Javelin_Time[pUseSkill->Point - 1];
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	cInvenTory.SetItemToChar();
	return TRUE;
}
int F_Vengeance()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}


int F_Glacial_Spike()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_Regeneration_Field()
{

	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_Chain_Lightning()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_Summon_Muspell()
{
	pUseSkill->UseTime = Summon_Muspell_Time[pUseSkill->Point - 1];
	sinUseManaStamina(pUseSkill);
	sinContinueSkillSet(pUseSkill);
	return TRUE;
}


int F_Fire_Elemental()
{
	pUseSkill->UseTime = 6 * 60;;
	sinContinueSkillSet(pUseSkill);
	sinUseManaStamina(pUseSkill);
	SummonSkillCodeIndex[1] = 0;
	return TRUE;
}
int F_Flame_Wave()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
int F_Distortion()
{
	pUseSkill->UseTime = Distortion_Time[pUseSkill->Point - 1];

	sinUseManaStamina(pUseSkill);


	return TRUE;
}
int F_Meteo()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}

/// TIER 5

int F_Soul_Breaker()
{
	sinUseManaStamina(pUseSkill);
	return TRUE;
}
