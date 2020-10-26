


#ifdef	_LANGUAGE_KOREAN

#define	ITEM_FORM_ADD1			9
#define	ITEM_FORM_ADD2			7
#define	ITEM_FORM_MULT			77
#define	ITEM_FORM_START_MASK	0xFE63
#define	ITEM_FORM_CODE_MASK		0xF57
#define	ITEM_FORM_CODE_SHIFT	11

#endif


#ifdef	_LANGUAGE_CHINESE

#define	ITEM_FORM_ADD1			5
#define	ITEM_FORM_ADD2			9
#define	ITEM_FORM_MULT			39
#define	ITEM_FORM_START_MASK	0xFEC5
#define	ITEM_FORM_CODE_MASK		0xF57
#define	ITEM_FORM_CODE_SHIFT	15

#endif


#ifdef	_LANGUAGE_THAI
#define	ITEM_FORM_ADD1			11
#define	ITEM_FORM_ADD2			3
#define	ITEM_FORM_MULT			51
#define	ITEM_FORM_START_MASK	0xFCCF
#define	ITEM_FORM_CODE_MASK		0xF5C
#define	ITEM_FORM_CODE_SHIFT	14
#endif


#ifdef	_LANGUAGE_ENGLISH
#define	ITEM_FORM_ADD1			1
#define	ITEM_FORM_ADD2			5
#define	ITEM_FORM_MULT			43
#define	ITEM_FORM_START_MASK	0xF5F5
#define	ITEM_FORM_CODE_MASK		0xFCF
#define	ITEM_FORM_CODE_SHIFT	14
#endif

#ifdef _LANGUAGE_BRAZIL	
#define	ITEM_FORM_ADD1			1
#define	ITEM_FORM_ADD2			5
#define	ITEM_FORM_MULT			43
#define	ITEM_FORM_START_MASK	0xF5F5
#define	ITEM_FORM_CODE_MASK		0xFCF
#define	ITEM_FORM_CODE_SHIFT	14

#endif


#ifdef	_LANGUAGE_JAPANESE

#define	ITEM_FORM_ADD1			2
#define	ITEM_FORM_ADD2			9
#define	ITEM_FORM_MULT			41
#define	ITEM_FORM_START_MASK	0xF555
#define	ITEM_FORM_CODE_MASK		0xF57
#define	ITEM_FORM_CODE_SHIFT	13

#endif



#ifdef	_LANGUAGE_TAIWAN

#define	ITEM_FORM_ADD1			4
#define	ITEM_FORM_ADD2			11
#define	ITEM_FORM_MULT			73
#define	ITEM_FORM_START_MASK	0xFCEC
#define	ITEM_FORM_CODE_MASK		0xF7C
#define	ITEM_FORM_CODE_SHIFT	14

#endif


#ifdef	_NEW_ITEM_FORMCODE2

static DWORD rsReformStateCode2(char *lpState, int size)
{
	int cnt;

	for(cnt = 0; cnt < size; cnt++)
	{
		iFormCode += (((DWORD)lpState[cnt]) + ITEM_FORM_ADD1)*((iFromCnt&ITEM_FORM_CODE_MASK) + ITEM_FORM_ADD2);
		iFromCnt += (cnt + lpState[cnt] + 1)*ITEM_FORM_MULT;
	}

	return iFormCode;
}

static DWORD rsGetRefromItemCode2(sITEMINFO *lpItemInfo, int Key)
{
	iFormCode = (Key*lpItemInfo->CODE)&ITEM_FORM_START_MASK;
	iFromCnt = Key;

	rsReformStateCode2((char *)&lpItemInfo->fMagic_Mastery, sizeof(float));
	rsReformStateCode2((char *)&lpItemInfo->fMana_Regen, sizeof(float));
	rsReformStateCode2((char *)&lpItemInfo->fLife_Regen, sizeof(float));
	rsReformStateCode2((char *)&lpItemInfo->fStamina_Regen, sizeof(float));
	rsReformStateCode2((char *)&lpItemInfo->fIncrease_Life, sizeof(float));
	rsReformStateCode2((char *)&lpItemInfo->fIncrease_Mana, sizeof(float));
	rsReformStateCode2((char *)&lpItemInfo->fIncrease_Stamina, sizeof(float));

	rsReformStateCode2((char *)lpItemInfo->Mana, sizeof(short) * 2);
	rsReformStateCode2((char *)lpItemInfo->Life, sizeof(short) * 2);
	rsReformStateCode2((char *)lpItemInfo->Stamina, sizeof(short) * 2);

	rsReformStateCode2((char *)&lpItemInfo->Money, sizeof(int));
	rsReformStateCode2((char *)&lpItemInfo->JobCodeMask, sizeof(DWORD));
	rsReformStateCode2((char *)&lpItemInfo->JobItem, sizeof(sITEM_SPECIAL));

	rsReformStateCode2((char *)&lpItemInfo->UniqueItem, sizeof(DWORD));
	rsReformStateCode2((char *)lpItemInfo->EffectBlink, sizeof(short) * 2);
	rsReformStateCode2((char *)lpItemInfo->EffectColor, sizeof(short) * 4);
	rsReformStateCode2((char *)lpItemInfo->ScaleBlink, sizeof(short) * 2);
	rsReformStateCode2((char *)&lpItemInfo->DispEffect, sizeof(DWORD));


	rsReformStateCode2((char *)&lpItemInfo->Weight, sizeof(int));
	rsReformStateCode2((char *)&lpItemInfo->Price, sizeof(int));

	rsReformStateCode2((char *)&lpItemInfo->fAbsorb, sizeof(float));
	rsReformStateCode2((char *)&lpItemInfo->Defence, sizeof(int));
	rsReformStateCode2((char *)&lpItemInfo->fBlock_Rating, sizeof(float));

	rsReformStateCode2((char *)&lpItemInfo->Shooting_Range, sizeof(int));
	rsReformStateCode2((char *)&lpItemInfo->Attack_Speed, sizeof(int));

	rsReformStateCode2((char *)&lpItemInfo->Attack_Rating, sizeof(int));
	rsReformStateCode2((char *)&lpItemInfo->Critical_Hit, sizeof(int));

	rsReformStateCode2((char *)&lpItemInfo->fSpeed, sizeof(float));
	rsReformStateCode2((char *)&lpItemInfo->Potion_Space, sizeof(int));

	rsReformStateCode2((char *)lpItemInfo->Resistance, sizeof(short) * 8);
	rsReformStateCode2((char *)lpItemInfo->Damage, sizeof(short) * 2);


	rsReformStateCode2((char *)&lpItemInfo->Health, sizeof(int));
	rsReformStateCode2((char *)&lpItemInfo->Level, sizeof(int));
	rsReformStateCode2((char *)&lpItemInfo->Strength, sizeof(int));
	rsReformStateCode2((char *)&lpItemInfo->Spirit, sizeof(int));
	rsReformStateCode2((char *)&lpItemInfo->Talent, sizeof(int));
	rsReformStateCode2((char *)&lpItemInfo->Dexterity, sizeof(int));

	rsReformStateCode2((char *)&lpItemInfo->CODE, sizeof(DWORD));
	rsReformStateCode2((char *)lpItemInfo->ItemName, 32);

	return iFormCode;
}

#endif


DWORD rsGetItem_ServerForm(sITEMINFO *lpItemInfo)
{
	DWORD dwCode;

#ifdef	_NEW_ITEM_FORMCODE2


	dwCode = rsGetRefromItemCode2(lpItemInfo, lpItemInfo->ItemHeader.dwChkSum);
	dwCode = dwCode ^ ((lpItemInfo->ItemAgingProtect[0] * 7) ^ (lpItemInfo->ItemAgingProtect[1] * 9));
	dwCode += (lpItemInfo->dwCreateTime & 0xFFFF) << 2;
	dwCode = dwCode ^ (lpItemInfo->ItemHeader.Head ^ ((lpItemInfo->ItemHeader.dwChkSum + dwCode) << ITEM_FORM_CODE_SHIFT));

#else


	dwCode = rsGetRefromItemCode(lpItemInfo, lpItemInfo->ItemHeader.dwChkSum);

#ifdef	_NEW_ITEM_FORMCODE
	dwCode = dwCode ^ ((lpItemInfo->ItemAgingProtect[0] * 7) ^ (lpItemInfo->ItemAgingProtect[1] * 9));
	dwCode += lpItemInfo->dwCreateTime >> 8;
#endif

	dwCode = dwCode ^ lpItemInfo->ItemHeader.Head;
#endif

	return dwCode;
}

