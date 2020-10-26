	

#include "sinLinkHeader.h"


char *WatermelonItem    = "7??????"; 

char *PumpkinItem = "7???????"; 

char *StarItem = "7???????"; 

char *ValentineItem = "7???????? "; 

char *PristonAlphabetItem = "7?? ????????";
char *CandydaysItem = "7????????";
char *ExpireItem = "????";

char *MagicalGreenEmeraldItem = "7????????";    
char *MagicalGreenJadeItem = "7??????";        


char *TearOfKaraItem    ="7???????"; 


char *FindinvestigatorItem = " ";  
char *FindinvestigatorNineItem = "????????";  
char *FindinvestigatorTaleItem = "????????";  

char *BillingMagicForceName = "????????";
char *MagicForceName = "????";

 char *InventoryFull = "?????? ????";
char *InvenSpaceSecure = "???????????";



char *BoosterItemInfo[] ={
    {"?????????\r"},  
    {"????????\r"},
    {"????????\r"},
    0,
};
char *BoosterItemInfo2[] ={
    {"15%?????\r"},
    {"15%?????\r"},
    {"15%?????\r"},
    0,
};

sMESSAGEBOX	sMessageBox[100] = {
	{"Not enough space in inventory"},
	{"You have exceeded the inventory weight limit"},   
	{"Item cannot be used yet"},	   
	{"Not enough gold"},
	{"Item can't be mixed"},
	{"Exceeds maximum number of transaction items"},
	{"Transaction cancelled"},
	{"Potions cannot be stored"},
	{"Item Mixture has failed"},
	{"Thank you for your generous donation"},
	{"Too many items in the warehouse"},
	{"Item can't be aged"},
	{"Item has been changed. Please check"},
	{"Exceeds maximum amount of gold in possession"}, 
	{"Item aging has failed"},
	{"Statistics has been reset"},
	{"Item image isn't prepared"},
	{"You can reset only once"},
	{"Only clan members can use this item "},
	{"You must be in a clan to use this item"},
	{"Unable to transfer due to level restriction"},
	{"Aging level has been decreased by -1"},
	{"Aging level has been decreased by -2"},
	{"Aging level has been increased by +1"},
	{"Aging level has been increased by +2"},
	{"Decreased ATK speed of quest item"},
	{"   Level up The quest item    "},
	{"   Increased HP +15"},
	{"   The puzzle is completed    "},
	{"   The puzzle is wrong    "},
	{"   No more items to sell  "},
	{"The item was sold already"},
	{"The seller's private store is closed"},
	{"   The seller is not found   "},
	{"    The number of items are wrong     "},
	{"    The male character cannot use    "},
	{"    The female character cannot use    "},
	{" The female character cannot acquire the item "},
	{" The male character cannot acquire the item "},
	{"    Item price was changed  "},
	{"    No clan prize money    "},
	{"  Your level can not use the orb  "},
	{"     The Orb is on use now    "},
	{"     ATK POW function is on test    "},
	{"    Force Orb's Maturing has completed    "},
	{"    stat point increased by 5    "},
	{"    skill point increased by 1    "},
	{" stat & skill point increased by 5 and 1"},
	{" stat & skill point increased by 5 and 2"},
	{"   Death penalty Exp decreased by 1  "},
	{"   Vitality increased by 40   " },
	{"You have undergoing Quest" },
	{"Over 80lev, you will get 7 stat-point at each level." },
	{"Over 90lev, you will get 10 stat-point at each level." },
	{"Reset your numbers for training." },
	{"The mission failed by over time." },
	{"Too many mercenary soldiers."},
	{"It is in using skill-item."},
	{"Can't transfer you to Bless Castle, Please request to GM"},	
	{"The item can not be sold to personal shop."},
	{"There is no enough amount of tax to be withdrawn."},
	{"You have already answered the questions."},
	{"Thank you for answering the questions."}, 
	{"The seal-item is not suitable to your level."},
	{"The item was re-constructed."},
	{"Win in the confrontation with Fury."},
	{"Lose in the confrontation with Fury."},
	{"Acquierd items in compensation."},
	{"The allied items can't be used together."},
	{"Able to use later"},
	{"Unable to cancel while sheltom are being mixed."},
	{"Unable to carry weapon while sheltom mixing."},
	{"Same type Hair Tint Potion used."},
	{"Item smelting was failed."}, 
	{"Item manufacture was failed."}, 
	{"When sheltoms are combined, you can not hold ores or crystals."}, 
	{"When runes are combined, you can not hold recipes."}, 
	{"These are not same kind of ores or crystals"}, 
	{"This is not the right way to manufacture"}, 
};


sMESSAGEBOX2 sMessageBox2[20] = {
	{"How many items","do you wanna buy?"},
	{"How many items","do you wanna sell?"},
	{"How many items","do you wanna throw away?"},
	{"How many gold  ","do you wanna throw away?"},
	{"",""}, 
	{"How many gold  "," do you wanna trade?"},
	{"How many gold  ","do you wanna move?"},
	{"How many gold  ","do you wanna get back?"},
	{" How many stars ","do you wanna buy?"},
	{"  How many gold  ","do you wanna donate?"}, 
	{"Do you wanna register","your item money? "}, 
	{"How many items","do you wanna buy?"},  
	{"How many gold  ","do you wanna get back?"}, 
	{"  Do you wanna ","buy the item?"}, 
	{"  Do you wanna ","buy the item?"}, 
	{"How many gold  ","do you want to draw out?"},
	{"How many Mercenary ","would you like to buy?"} 
	
};


sMESSAGEBOX3 sMessageBox3[MESSAGE3_MAX] = {
	{"Do you wanna","acquire the skills?"},
	{"Do you wanna", "rank up?"}, 
	{"Do you wanna", "carry out the quest?"},
	{"Do you wanna","redistribute?"},
	{"It costs gold"," for the event"},
	{"Do you wanna","initialize the STATS?"},			
	{"Do you wanna", "carry out the quest?"}, 
	{"Do you wanna", "receive the item?"}, 
	{"Do you wanna", "register Union Core?"}, 
	{"Do you wanna", "receive the item?"}, 
	{"Do you wanna", "move to ?"}, 
	{"","Please type in the number"}, 
	{"Do you wanna","purchase star item?"}, 
	{"Do you wanna", "sell the item?"}, 
	{"Do you wanna", "the quest?"}, 
	{" Do you wanna", "pay the donation?"}, 
	{" Private Store ", "fffffffffff"}, 
	{"Do you wanna", "exchange to the item? "}, 
	{"Do you wanna", "buy the item?"}, 
	{"Do you wanna ", "cancel the Register?"}, 
	{"Do you wanna", "exchange the item? "}, 
	{"Do you wanna", "exchange the item? "}, 
	{"Do you wanna", "search for the quest?"}, 
	{"Do you wanna", "search for the quest?"}, 
	{"Do you wanna", "search for the quest?"}, 
	{"Do you wanna", "search for the quest?"}, 
	{"Do you wanna", "search for the quest?"}, 
	{"Do you wanna", "search for the quest?"}, 
	{"Do you wanna", "search for the quest?"}, 
	{"Where do you", "want to be teleported"}, 
	{"Do you wanna", "search for the quest?"}, 
	{"Do you wanna", "search for the quest?"}, 
	{"Do you wanna", "search for the quest?"}, 
	{"Do you wanna", "rank up?"}, 
	{"Do you wanna", "exchange the item? "},
	{"Would you teleport to", "somewhere?"},    
	{"Would you like to buy","a crystal tower?"},      
	{"Do you want to", "get the Quest?"}, 
	{"Do you want to", "get the Quest?"}, 
	{"Do you want to", "get the Quest?"}, 
	{"Do you want to", "get the Quest?"}, 
	{"Do you want to", "get the Quest?"}, 
	{"Do you want to", "get the Quest?"}, 
	{"Do you want to", "get the Quest?"}, 
	{"Do you want to", "use this item?"},       
	{"Do you want to ", "get the Quest?"},
	{"Do you want to ", "receive the item?"},   
	{"Do you want to","move to the Battle Zone?"},   
	{"Do you want to", "Teleport?"},
	{"Do you want to", "change? "}, 
	{"Do you want to", "teleport?"},    
	{"Do you want to", " manufacture?"}, 
	{"Do you want to", "teleport?"},    
};


char *SkillMaster[4] = {
	"Learn Skill",
	"Change Class",
	"Quit Game"

};
char *SkillMaster2[4] = {
	"",
	"",
	""

};

char *ReStartMsg[4] = {
	" Restart from field?",
	" Restart from town?",
	" Quit Game?",
	" Not enough XP"

};
char *ReStartMsg2[4] = {
	" Penalty(Gold/XP) 1%",
	"",
	"",
	" to stay in field",

};

char *SkillUseInfoText[10]= { "    Train Skill/Magic     ","    Select a Skill or Magic     ","      To learn or train       ","  Not enough Skill Points ","   to learn or practice " };
char *sinMsgSkillPoint = "    Skill Points : %d";
char *sinMsgEliteSkillPoint = "Elite Skill Points : %d " ;
char *sinStateName[5]={"H P : %d/%d  ","M P : %d/%d  ","STM : %d/%d  ","X P : %d/%d  ","X P : %dM/%dM  "};


char *TownName[3] = {"Recall to Ricarten\r","Recall to Navisko\r","Recall to Pillai\r"};

char *sinAbilityName[50] = {"Attack Power:  \r","Weapon Speed:  \r","Range:  \r","Critical:  \r","Defense Rating:  \r","Attack Rating:  \r",
					"Absorb Rating:  \r","Block Rating:  \r","Speed:  \r","Integrity:  \r","MP Recovery:  \r","HP Recovery :  \r",
					"STM Recovery:  \r","Organic Type:  \r","Nature Type:  \r","Flame Type:  \r","Frost Type:  \r","Lightning Type:  \r","Poison Type: \r",
					"Water Type:  \r","Wind Type:  \r","HP Regen:  \r","MP Regen: \r","STM Regen: \r","Add. HP: \r",
					"Add. MP:  \r","Add. STM:  \r","Potion Storage:  \r","Req. Level:  \r","Req. Strength:  \r","Req. Spirit:  \r",
					"Req. Talent:  \r","Req. Agility:  \r","Req. Health:  \r"};


char *sinSpecialName[50] = {"Spec. ATK SPD:  \r","Spec. CRIT:  \r","Spec. DEF RTG:  \r","Spec. ABS RTG:  \r",
						"Spec. BLK RTG:  \r","Magic APT:  \r","Spec. SPD:  \r","Spec. Organic:  \r","Spec. Nature:  \r",
						"Spec. Flame:  \r","Spec. Frost:  \r","Spec. Lightning:  \r","Spec. Poison:  \r","Spec. Water:  \r","Spec. Wind:  \r",
						"Spec. ATK POW:  \r","Spec. ATK RTG:  \r","Spec. RNG:  \r","Spec. Organic ATK:  \r","Spec. Nature ATK:  \r","Spec. Flame ATK:  \r","Spec. Frost ATK:  \r",
						"Spec. Lightning ATK:  \r","Spec. Poison ATK:  \r","Spec. Water ATK:  \r","Spec. Wind ATK:  \r","Max HP Boost:  \r","Max MP Boost:  \r",
						"HP Recovery:  \r","MP Recovery:  \r","STM Recovery:  \r","Sale Price:  \r","Cost:  \r"};


char *SpecialName3 = "%s Spec. \r";
char *MixResultTitle = "Item Mixture Result";
char *NowLevelText = "Current Level\r";
char *NextLevelText = "Next Level\r";

char *NormalAttckName ="Default Attack";
char *RequirLevel = "%s (Req. LVL:%d)\r";
char *UseItemGroupName = "Compatible Item Group\r";

char *PoisonName = "Poison Type:\r";
char *FireName = "Flame Type:\r";
char *AttackAreaName = "Attack Range:\r";
char *Attack_RateName = "Attack Rating:\r";
char *Max_DamageIncre = "Max Damage Boost:\r";
char *DamageAddName = "Damage Boost:\r";
char *Attack_SpeedAdd = "Attack Speed Boost:\r";
char *IncreBlock = "Block Rating Boost:\r";
char *CountinueTime = "Duration:\r";
char *UseManaName = "MP Usage:\r";
char *DamageName = "Attack Power:\r";
char *ShootingRangeName = "Range:\r";
char *IncreAsorb = "Absorb Rating Boost:\r";
char *SecName = "sec";
char *PlusDamageName = "Add. Damage:\r";
char *HitNumName = "No. of Hits:\r";
char *DecreLifeName = "Life Decreases:\r";
char *Attck_RateAdd = "Add. Attack Power:\r";
char *Add_CriticalName = "Add. Critical:\r";
char *Push_AreaName = "Push-back Length:\r";
char *FireAttackDamageAdd ="Flame Attack:\r";
char *IceName = "Frost Property:\r";
char *IceAttackDamageAdd = "Frost Attack:\r";
char *StuneRate = "Stun Probability:\r";
char *DefenseRateIncre = "Defense Rate Increases:\r";
char *WeaponSizeName ="Weapon Size:\r";
char *HwakRotationNum = "Hawk Rotations:\r";
char *WeaponSpeedAddName  = "Add. Weapon Speed:\r";
char *IncreAttack_RateName = "Attack Rating Increases:\r";
char *ShootingNumName = "No. of Shots:\r";
char *SeriesShootingCount = "Continuous Fire:\r";
char *UseStaminaName = "Stamina Usage:\r";
char *MasterSkillMoneyName = "Skill Cost:\r";

char *ItemAgingResult;		

char *sinGold ="%dGold";
char *sinGiveItem5 = "Gift Item\r";
char *sinCopyItem5 = "Copied Item\r";
char *sinNum7 = "RND";
char *sinSkillPointName = "Skill Point";	
char *sinG_Pike_Time3 = "Frozen Time:\r";	
char *sinItemLimitTimeOverMsg = "Time limit has expired\r";
char *sinDeadSongPyeunEat = "Darn it! It's rotten rice cake!";
char *SmeltingResultTitle = "Result of smelting";		
char *ManufactureResultTitle = "Result of manufacturing";	
char *ManufacturingTitle = "Random";	


char *sinMaxDamageAdd = "Increase in Maximum damage+\r";
char *sinDamagePiercing = "(Piercing attack)\r";
char *sinAddStamina = "Added stamina:\r";
char *sinAddLife = "Life recovery:\r";

char *sinDamageUndead50 = "50% more damages to Undead units:\r";
char *sinNumCount2 = "number:\r";
char *sinNumCount3 = "quantity\r";
char *sinDecreDamage = "Decrease in damage:\r";
char *sinConvert4 = "conversion rate:\r";
char *sinIncreElement = "Increase in element feature:\r";
char *sinPartyIncreElement = "Party member gather 50% increase of element\r";
char *sinFireBallDamage2 = "(100% damage to the targeted enemy)\r";
char *sinFireBallDamage3 = "(targeted area 60 (1/3 damage))\r";
char *sinAddDamage7 = "added damage:\r";
char *PlusDamageWeapon = "weapon";
char *SparkDamage = "damage per unit:\r";
char *SparkNum7 = "# of maximum spark:\r";
char *StunRage = "Stun Range:\r";
char *RecvPotion7 = "Potion";


char *PartyArea7 ="Party Area:\r";
char *Area17 ="Area:\r";
char *AddAttack_Rate9 ="Attack Rating:\r";
char *PiercingRange ="Piercing Range:\r";
char *IncreDefense = "Increase Defense:\r";
char *AddShootingRange = "Increased SHT range:\r";
char *LifeAbsorb = "Life absorb.:\r";
char *FireDamage = "Fire Damage:\r";
char *IceDamage = "Ice Damage:\r";
char *LightningDamage = "Lightning Damage:\r";
char *AddManaRegen = "Add Mana Regen:\r";
char *LightNum = "# of Lightning:\r";
char *ReturnDamage = "Return Damage:\r";
char *Area18 = "Available Range:\r";
char *IncreMana5 = "Increase Mana:\r";
char *Area19 = "Available Area:\r";
char *HelpTitle8 = " H E L P ";
char *QuestTitle8 = " Q U E S T ";
char *ResearchTitle8 = "RESEARCH";
char *TeleportTitle8 = "TELEPORT";

char *IncreWeaponAttack_RateName = "Increased ATK rating:\r";
char *AddMaxDamage = "Increased maximum damage:\r";
char *LinkCoreName = "Teleport to a clan member\r";
char *DesLinkCore = "Name:";
char *Itemul = "item";
char *ItemRecvOk = "Do you want this?";
char *Money5 = "gold";
char *Exp5 = "EXP";
char *WingItemName[6] = {"Metal wing","Silver wing","Gold wing","Diamond wing", "Chaos wing","Extreme Wing"};
char *WarpGateName[10] = {"Warp gate","Ricarten","Pillai","Land of Dusk","Bamboo Forest","Ruinen Village","Navisko Town","Forbidden Land", "Eura Village", "Land of Chaos"};
char *sinWarningName5 = "Warning";
char *ClanCristalName = "Clan members only\r";
char *NowMyShopSell = "On Sale\r";
char *SecretNumName = "Input authentication numbers";
char *MyShopExpDoc7 = "Shop Information";
char *NotAgingItem2 = "'Unable to age item";
char *ExpPercent2 = "EXP : %d.%d%s";
char *ExpPercent3 = "EXP : %d.0%d%s";
char *Mutant7   =   "Mutant";
char *Mechanic7 = "Mechanic";
char *Demon7    = "Demon";
char *Nomal7    = "Normal";
char *Undead7    = "Undead";
char *MonsterAddDamage2 = "add extra damage)\r";
char *MonsterAddDamageFire = "add fire element damage)\r";
char *HaWarpGateName[] = {"Bless Castle",0};
char *FallGameName = "Twisted Forest";
char *EndlessGameName = "Endless Tower";
char *LookHelp = ">>more...";



char *HoldStarNumDoc = "The number of your stars";
char *StarItemBuy7   = "Purchase the stars";
char *ChangeMoney7   = "(The price of one star: 100000)"; 




char *LightningDamage2 = "LightningDamage:\r";
char *SheildDefense = "Increasing Defense:\r";

char *DemonDamage4  = "DemonVSATKpower:\r";
char *PoisonDamage3  = "PoisonDamage:\r";
char *PikeNum4       = "Number of spear:\r";
char *poisoningTime  = "poisoningTime:\r";
char *PlusCriticalName = "Increasing Critical%:\r";
char *SpiritFalconDamage2 = "SpritFalconDamage:\r";
char *LifeGegenPlus = "Increasing HP:\r";
char *PlusDamage4 = "PlusDamage:\r";
char *PiercingPercent = "PiercingPercent:\r";
char *DamageToLife = "DamageToLife:\r";
char *MyMonster7 = "MyMonster:\r";
char *LifeIncre4 = "LifeIncre:\r";
char *UndeadDamage3 = "UndeadDamage:\r";

char *AttackNum3     = "NumberofATK:\r"; 
char *AttackRateMinus = "DecresingATKRATING:\r"; 
char *MaxDamagePlus2 = "MaxDamagePlus:\r"; 
char *LightningAddDamage3 = "LightningAddDamage:\r"; 
char *ReLifePercent4    = "ReLifePercent:\r"; 
char *GetExp3    = "GetExp:\r"; 
char *ResurrectionChar4    = "ResurrectionCharLV"; 
char *ExtinctionPercent2    = "ExtinctionPercen:\r"; 
char *ExtinctionAmount2    = "ExtinctionAmount:\r"; 
char *IncreLifePercent2   = "IncreLifePercent:\r"; 

char *ReduceDamage3 = "ReduceDamage:\r"; 
char *IncreMagicDamage = "IncreMagicDamage:\r"; 
char *AttackDelay3   = "AttackDelay:\r"; 

char *FireDamage2 = "FireDamage:\r";
char *IceDamage2 = "IceDamage:\r";
char *AddDefense8 = "AddDefense:\r";
char *SkillDamage5 = "SkillDamage:\r";

char *FireDamage3 = "FireDamage:\r";
char *AddSpeed7 = "AddSpeed:\r";
char *AfterDamage7 = "AfterDamage:\r";
char *MonsterSight7 = "MonsterSight:\r";



char *LinghtingAddDamage4="Add attack rate on lightning:\r";
char *MaxBoltNum4="Max voltage:\r";
char *AddAbsorb4="Add rate on absorb:\r";
char *IncreArea4="Increasing range:\r";
char *IncreAttack4="More attacking power:\r";
char *GolemLife4="Life+STR:\r";


char *SubAbsorb4="Decreasing absorption:\r";
char *AreaDamage4="Attacking rate for range:\r";
char *MaxAttackNum4="Max hits:\r";
char *LifeUp4="Add vitality:\r";

char *CriticalAddDamage4="Increase of critical:\r";
char *MonstervsSubCritical4="Weaken critical of monster:\r";
char *ChargingAddPercentDamage4="Add attacking rate on charging:\r";

char *IncreEvasionPercent4="Additinal percentage of evasion:\r";
char *AddShadowNum4="Increasing combination of ocular:\r";

char *WolverinLife4="Vitality:\r";
char *WolverinRate4="Accuracy:\r";
char *WolverinDefense4="Defence rate:\r";
char *AddEvasion4="Increasing ability of evasion:\r";
char *AddDamage4="Increasing attacking rate(physic):\r";
char *FalconAddDamage4="Increasing attacking rate of falcon:\r";


char *IncreAttackAbsorb4="Increasing absorption rate:\r";

char *RectAngleArea4="Attacking at sharp angled range:\r"; 

char *MonsterSubSpeed4="Decreasing speed of attacted monster:\r";


char *AddLifeRegen4="Add life-regeneration:\r";
char *AddManaRegen4="Add mana-regeneration:\r";
char *MagicArea4="Magic affected range:\r";
char *ChainNum4="A number of affected monster:\r";
char *ChainRange4="The rage of affected monster:\r";
char *UndeadDamageAbsorb4="Undead attacking absorption:\r";
char *UserBlockPercent4="Blocking rate for character:\r";

char *SecondIncreMana4="Increasing mana rate per second:\r";
char *FireDamage4="Fire attacking rate:\r";
char *DecreSpeed4="Decreasing Speed:\r";
char *DecreAttack4="Decreasing attacking rate:\r";
char *AddPercentDamage4="Adding attacking rate:\r";



char *ChainDamage3    = "ChainDamage)\r";
char *BrandishDamage3 = "BrandishDamage";
char *PhysicalAbsorb3 = "PhysicalAbsorb";
char *SparkDamage3    = "SparkDamage";
char *BrutalSwingCritical3   = "BrutalSwingCritical";
char *Attck_RateAdd5 = "Attck_RateAdd:\r";
char *Triumph4="Triumph";
char *Use4="you";
char *DivineShield4="Blocking rate of divine shiled";


char *QuestMonsterName[] = {"Bargon","Skeleton Warrior","Head Cutter","Armored Beetle ","Skeleton Ranger","Titan" ,
                         "Forbidden Land's Monster","Oasis' Monster","Ancient Prison 1F's Monster"};



char *VampOption[10] ={"Increaseagaing%: \r","Vampire: \r","RefDamage: \r","DecreaseHP: \r","Lucky: \r"};


char *Quest3ItemName[]={"Demon Hunter","Ancient Revenge","Mist","Devil Side","Anaconda","Plated Sword","Ghost"};

char *Quset3ItemDoc15 = "The quest item";
char *Quset3ItemDoc16 = " is gone ";

char *SparkDamage10 = "SparkDamage:\r";

char *RequirLevel3 = "(Required Level:%d)\r";

char *RecvItemTT = "I receive the item";
char *PuzzleEvent5 = "Completed Puzzle";
char *BabelHorn = "The Horn of Babel";
char *NineTailFoxItem = "Nine Tail Amulet";
char *MyShopItemSell5 = "The Price: \r";
char *CristalItem     ="the 7 Crystals";
char *StarDust		= "Glitering powder";
char *ChristMas	= "Shining dust";


char *sinDeadCandyEat = "The taste is sucks!";

char *PotionCntDoc2 = "Selling price per unit";
char *ItemPrice7 = "ItemPrice";

char *BuyMyShopItem7 = "%s player has bought %dnumber of %s by %dGold";
char *BuyMyShopItem8 = "%s player has bought %dnumber of %s by %dGold";
char *ItemName87 = "item";

char *sinEvent87 = "Request of the danger collector";
char *sinAddDamageItem = "AddedATKPOWER: \r";
char *sinContinueTimeItem = "Duration: \r";
char *BuyPotionMoney = "Money:";
char *BuyPotionKind = "Number:";
char *SheltomName2[] = {"Lucidy","Sereneo"," Fadeo","Sparky","Raident","Transparo","Murky","Devine","Celesto", "Mirage", "Inferna", "Enigma"};

char *AddPercentDamage3= "AddATKPOWER%: \r";

char *sinLuckyBox = "Lucky Bag";
char *SodMessage_Etc[]= {
			"The income of The Bellatra management's clan is",
			"Only clan chief takes it.",
			"Now, the tax is %d%s.",
			};
			
char *SodMessage_Clan[] = {
			"The total income follows as ",
			"Bellatra provided the prize yesterday.",
			};
			
char *SodMessage_Master[] = {
			"The total income follows as",
			"Bellatra provided the prize yesterday.",
			"Do you want to redeem?",
			};
			
char *OtherClanMaster[] = {
			"The clan still have the prize",
			"write the redemption gold.",
			};
	
char *SiegeMessage_Taxrates[] = {
	"The tax rate is changed %d%s.",
	"Total of tax has been accumulating",
	"Gold.",
	"Would you like to withdraw the tax?.",
	"The tax rate is now %d%s.",
};
char *SiegeMessage_MercenrayA[] = {
	"Ricarten Militia",
	"It consists of the militia",
	"It has weak fighting ability instead of cheap.",
	"Maximum amount of Mercenary:20 / %d",
};
char *SiegeMessage_MercenrayB[] = {
	"Ricarten Guard",
	"The price, ability are all good balance to become a Mercenary",
	"It has the middle fighting ability.",
	"Maximum amount of Mercenary :20 / %d",
};
char *SiegeMessage_MercenrayC[] = {
	"Bless Royal Guard",
	"The most high level of Mercenary",
	"It has the most fighting ability.",
	"Maximum amount of Mercenary:20 / %d",
};
char *SiegeMessage_TowerIce[] = {
	"Ice Crystal Tower",
	"Ice attribute makes a decrease move speed and",
	"it has ability decrease ATK speed.",
	"Setting of Ice Crystal is completed",
};
char *SiegeMessage_TowerFire[] = {
	"Fire Crystal Tower",
	"Fire attribute makes great ATK Power but",
	"No special ability.",
	"Setting of Fire Crystal is completed",
};
char *SiegeMessage_TowerLighting[] = {
	"Lightning Crystal Tower",
	"Lightning decreses move speed and",
	"it has ability decrease ATK speed.",
	"Setting of Lightning Crystal is completed",
};
char *SiegeMessage_MerMoney   = "Mercenary Money: ";
char *SiegeMessage_TowerMoney = "Tower Money: ";

char *sinClanMaster7 = "ChiefClan";
char *sinPrize7 = "Prize";

char *sinLevelQuestMonster[]={"Bargon","Muffin","Dire Bee","Typhoon","Ratoo","Grotesque","Iron Fist"};
char *sinLevelQusetDoc="Quest> %s %d number of monster needed";

char *sinTeleportDoc[] = {"Mushroom Cave","Beehive Cave","Cursed land","Forbidden land"};
char *sinLevelQuest90_2Mon[] = {"Omega","D-Machine","Mountain"};
char *sinLevelQusetDoc2="<Quest> Hunt %d of %s ";
char *sinLevelQusetDoc3="<Quest> Get the item from %s";
char *sinLimitTiem2 = "Time Limit: \r";
char *sinMinute2 = "minute";
char *sinDay4    = "day";
char *sinHour4   = "hour";
char *sinLevelQusetDoc4="<Quest>  Finished hunting %d of the %s ";

sinSTRING sinTestMsg7("Hurray, Neh Neh Neh Boo Boo, You're losers!");

char *sinMonCodeName[]={
	0,
	"Bargon",
	"Skeleton Warrior",
	"Head Cutter",
	"Armored Bettle",
	"Skeleton Ranger",     
	"Titan",
	"Muffin",
	"Dire Bee",
	"Typhoon",
	"Ratoo",                
	"Grotesque",
	"Iron Fist",
	"Omega",
	"D-Machine",
	"Mountain",              
	"Skeleton Knight",
	"Solid Snail",
	"Thorn Crawler",
	"Mummy",
	"Doom Guard",             
	"Figon",            
	"Stone Giant",
	"Stone Golem",
	"Iron Guard",
	"Avelin",       
	"Avelisk-L",
	"BeEvil",
	"Illusion Knight",
	"Nightmare",
	"Witch",                
	"Heavy Goblin",
	"Dawlin",
	"Stygian",
	"Incubus",
	"Chain Golem",           
	"Dark Specter",
	"Metron",
	"Avelisk Lord",
	"Dusk",
	"Sadnesst",            
	0,
};

char *ChargingTime4="Raise speed for charging:\r";
char *AddIceDamage4="Added Damage of Frost Elemental:\r";
char *IceTime4="Freezed Time:\r";
char *sinAttackType = "Attack Type:\r";
char *sinAttackType2[2] ={"Manual\r","Auto\r"};

char *Won="Gold";


char *CastlItemInfo[] ={
	{"With instant god mode but\r"},  
	{"Critical percent\r"},
	{"Adding evasion percent\r"},
	{"ST,HP,MA of party players\r"},
	{"resurrection immediately.\r"},
	{"ATK of Crystal tower\r"},     
	{"ATK power is 20% on target\r"},
	0,
};
char *CastlItemInfo2[] ={
	{"ATK power decreases in 1/2.\r"},
	{"5% increase.\r"},
	{"increase.\r"},
	{"recover all.\r"},
	{"\r"},
	{"50%offset.\r"},
	{"Add.\r"},
	0,
};


char *CharClassTarget[8]={
	"Target(Fighter)\r",
	"Target(Mechanician)\r",
	"Target(Pikeman)\r",
	"Target(Archer)\r",
	"Target(Knight)\r",
	"Target(Atalanta)\r",
	"Target(Magician)\r",
	"Target(Priestess)\r",
};
char *AttributeTower[4]={
	"Attribute(Fire)\r",
	"Attribute(Ice)\r",
	"Attribute(Lightning)\r",
	"Duration:%dSec\r",
};

char *SiegeMessage_MerComplete ="Setting of Mercenary is completed";


char *haQuestMonsterName[]={
	"Hopy",
	"Rabie",
	"Hobgoblin",
	"NorthGoblin",
	"Skeleton",
	"Corrupt",
	"Cyclops",
	"Bagon",
	0,
};
char *ha100LVQuestItemName[]={
	"Minotaur Axe",
	"Extreme Talon",
	"Dragon Bone Hammer ",
	"Hellfire Scythe",
	"Revenge Bow",
	"Immortal Sword",
	"Salamander Javelin",
	"Gothic Staff",
	0,
};

char *ha100LVQuestMonterName[]={
	"Monsters in the Heart of Perum",
	"Monsters of the Galluvia  Velly",
	0,
};
char *ha100LVQuestName = "Fury's phantasma";


char *PremiumItemDoc[][2]={
	{"It makes stat points\r"     ,"to be restributed.\r"},     
	{"It makes skill points\r"     ," to be restributed.\r"},    
	{"It makes stat/skill points\r"," to be restributed.\r"},     
	{"It makes the dead character \r"    ,"to be revived.\r"},        
	{"Becomes invincible for the set time.\r","The attack power decrease in 1/2\r"},    
	{"15% increase \r"    ,"on the critical attack.\r"},		
	{"15% increase of \r"         ,"evade chance.\r"},		
};
char *UpKeepItemDoc[] = {
	"Remaining Time : %dMin",
	"%d%s Chance of Additional Drop",
	"%d%s EXP Boost",
	"Attack %d%sIncrease",
	"HP Recharge per hit",
	"MP Recharge per hit",
	"Increase capacity by d%",
	"Reduce on usage of MP by %d%s",
	0,
};
char *UpKeepItemName[] = {
	"Third Eyes",
	"EXP Increase Potion",
	"Vampiric Cuspid",
	"Mana Recharging Potion",
	"Might of awell",
	"Mana Reduce Potion",
	"Phoenix",
	0,
};

