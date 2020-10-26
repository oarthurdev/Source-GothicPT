
#pragma once


namespace nsPremiumItem{
	enum _Item{
		THIRD_EYES = 1,
		EXPUP_POTION = 2,
		VAMPIRIC_CUS = 3,
		MANA_RECHAR_P = 4,
		MIGHT_OF_AWELL = 5,
		MANA_REDUCE_P = 6,
		PHENIX_PET = 7,
		HELP_PET_TERRY = 8,
		HELP_PET_NEPSYS = 9,
		HELP_PET_IO = 10,
		HELP_PET_MUTE = 11,
		VAMPIRIC_CUS_EX = 12,
		STAMINA_REDUCE_P = 13,
		BIGHEAD1 = 14,
		BIGHEAD2 = 15,
		BIGHEAD3 = 16,
		BIGHEAD4 = 18,
	};
}
using namespace nsPremiumItem;


#define		SINUPKEEPITEM_MAX       18


const DWORD SINITEM_TIME_5MINUTE = (15 * 60 * 1);
const DWORD SINITEM_TIME_10MINUTE = (30 * 60 * 1);
const DWORD SINITEM_TIME_3HOURS = (3 * 60 * 60 * 1);
const DWORD SINITEM_TIME_6HOURS = (6 * 60 * 60 * 1);
const DWORD SINITEM_TIME_12HOURS = (12 * 60 * 60 * 1);
const DWORD SINITEM_TIME_ONEDAY = (24 * 60 * 60 * 1);
const DWORD SINITEM_TIME_SEVENDAY = (7 * 24 * 60 * 60 * 1);
const DWORD SINITEM_TIME_30DAY = (30 * 24 * 60 * 60 * 1);

const DWORD SINITEM_TIME_1HOURS = (1 * 60 * 60 * 1);
const DWORD SINITEM_TIME_2DAYS = (1* 60 * 60 * 24 * 2);
const DWORD SINITEM_TIME_3DAYS = (1 *60 * 60 * 24 * 3);




struct sTelePortCore
{
	short   FieldIndex[2];
	bool    PageButtonFlag[2];
	short   PageIndex;
	short   ItemIndex;
	char    FieldName[64];
};


struct sUpKeepItem
{
	int     TGAImageNumber;
	bool    Visible;
	bool    Infoflag;
	char    Id[32];
	int		PosiX;
	int		PosiY;
	DWORD	IconTime[2];
	short   Alpha;
	short   Alphakind;
	int		Per;
};


class cHaPremiumItem
{
public:
	LPDIRECT3DTEXTURE9  lpUpKeepItemBackImage[SINUPKEEPITEM_MAX];
	sTelePortCore		  TelePortCore;
	sUpKeepItem           UpKeepItem[SINUPKEEPITEM_MAX];
	bool                  UseClickPremiumItemFlag;
	int                   Using_ItemKind;
	int                   UpKeepItemTGAImage[SINUPKEEPITEM_MAX];
	bool                  haItemUseDelayFlag;
	bool                  bUpdateTimeDelayFlag;
	int					  Using_SelectInvenItemIndex;


	DWORD                 m_ThirdEyesTime;
	DWORD                 m_ExpUpPotionTime;
	DWORD                 m_VampiricCuspidTime;
	DWORD                 m_ManaRechargingPTime;
	DWORD				  m_ManaReducePotiontime;
	int					  m_ManaReducePotionValue;
	DWORD				  m_MightofAwellTime;
	int					  m_MightofAwellWeight;
	DWORD				  m_PhenixPetTime;
	DWORD				  m_HelpPetTime;
	DWORD				  m_VampiricCuspidEXTime;
	DWORD				  m_StaminaReducePotiontime;
	int					  m_StaminaReducePotionValue;


	DWORD				  m_TerryTime;

	DWORD				  m_BigHead1;
	DWORD				  m_BigHead2;
	DWORD				  m_BigHead3;
	DWORD				  m_BigHead4;

	int					  iBigHeadLeftTime;
	int					  iBigHeadCounter;
	int					  iBigHeadType;

	DWORD                 VIP;

public:
	cHaPremiumItem();
	~cHaPremiumItem();


	void init();
	void Main();
	void Draw();
	void DrawUp();
	void KeyDown();
	void LButtonDown(int x, int y);
	void LButtonUp(int x, int y);
	int  DrawText();

	int  UsePremiumItem(int kind = 0);
	int  SetPremiumItemSkill(int kind = 0);
	int  UseTeleportScrollItem(short ItemIndex);
	int  CheckWindowOpen();
	int  CheckUpKeepItem();
	void InfoBox(int PoisX, int PosiY, int Width, int Height);
	int  SetUpKeepItem(int kind, DWORD dwTime, bool visible, char* id, int Percent = 0, short ItemType = 0);
	int  cHaPremiumItem::CheckTime(DWORD CurrentTime);


	void SetThirdEyesTime(DWORD Time){ m_ThirdEyesTime = Time; };
	void SetExpUpPotionTime(DWORD Time){ m_ExpUpPotionTime = Time; };
	void SetVampiricCuspidTime(DWORD Time){ m_VampiricCuspidTime = Time; };
	void SetVampiricCuspidEXTime(DWORD Time){ m_VampiricCuspidEXTime = Time; };
	void SetManaRechargingPTime(DWORD Time){ m_ManaRechargingPTime = Time; };
	void SetManaReducePotionTime(DWORD Time){ m_ManaReducePotiontime = Time; };
	void SetManaReducePotionValue(int Value){ m_ManaReducePotionValue = Value; };
	void SetMightOfAwellTime(DWORD Time){ m_MightofAwellTime = Time; };
	void SetMightOfAwellWeight(int Weight){ m_MightofAwellWeight = Weight; };
	void SetPhenixPetTime(DWORD Time){ m_PhenixPetTime = Time; };
	void SetStaminaReducePotionTime(DWORD Time){ m_StaminaReducePotiontime = Time; };
	void SetStaminaReducePotionValue(int Value){ m_StaminaReducePotionValue = Value; };

	void SetBigHead1Time(DWORD Time);
	void SetBigHead2Time(DWORD Time)
	{
		m_BigHead2 = Time;
		if(Time == 0)
		{
			for(int i = 0; i < SINUPKEEPITEM_MAX; i++)
			{
				if(UpKeepItem[i].TGAImageNumber == nsPremiumItem::BIGHEAD2)
				{
					UpKeepItem[i].IconTime[0] = UpKeepItem[i].IconTime[1];
				}
			}
		}
	};
	void SetBigHead3Time(DWORD Time)
	{
		m_BigHead3 = Time;
		if(Time == 0)
		{
			for(int i = 0; i < SINUPKEEPITEM_MAX; i++)
			{
				if(UpKeepItem[i].TGAImageNumber == nsPremiumItem::BIGHEAD3)
				{
					UpKeepItem[i].IconTime[0] = UpKeepItem[i].IconTime[1];
				}
			}
		}
	};
	void SetBigHead4Time(DWORD Time)
	{
		m_BigHead4 = Time;
		if(Time == 0)
		{
			for(int i = 0; i < SINUPKEEPITEM_MAX; i++)
			{
				if(UpKeepItem[i].TGAImageNumber == nsPremiumItem::BIGHEAD4)
				{
					UpKeepItem[i].IconTime[0] = UpKeepItem[i].IconTime[1];
				}
			}
		}
	};


	void SetHelpPetTimeTime(DWORD Time){ m_TerryTime = m_HelpPetTime = Time; };


	int  UseHairtintPotion(int ItemKind);
	int UseLuckyBox(int BoxType);

	int UseAgingMaster(int ItemKind);


	int UseSkillMaster(int ItemKind);


	int UseMoveShop();

	void					SetItemPremiumTime(int iType, int i);

	int						GetBigHeadTime() { return iBigHeadLeftTime; }
	void					SetBigHeadTime(int i) { iBigHeadLeftTime = i; }

	int						GetBigHeadType() { return iBigHeadType; }
	void					SetBigHeadType(int i) { iBigHeadType = i; }


};
extern cHaPremiumItem  chaPremiumitem;
