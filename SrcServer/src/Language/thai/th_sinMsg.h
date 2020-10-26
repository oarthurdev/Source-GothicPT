 	

#include "sinLinkHeader.h"  

sMESSAGEBOX	sMessageBox[100] = {
	{  "  พื้นที่เก็บไม่พอ "  },
	{  "  น้ำหนักเกิ?"  },
	{  "  ยังไม่สามารถใช้ไอเทมนี้ได้  "  },
	{  "  เงินไม่เพียงพอ  "  },
	{  "  ไอเทมนี้ไม่สามาร?mix ได? "  },
	{  "  จำนวนของที่แลกเปลี่ยนเกินขีดจำกั? "  },
	{  "  การแลกเปลี่ยนถูกยกเลิก  "  },
	{  "  ไม่สามารถเก็บPotion ได? "  },
	{  "  กา?mix ล้มเหล?. "  },
	{  "  ขอบคุณสำหรับ ความกรุณาของท่าน!  " },
	{  "  ไอเทมในคลังสินค้ามีมากเกินไป "  },
	{  "  ไอเทมไม่สามารถ age ได? "  },
	{  "  ไอเทมถูกเปลี่ยนกรุณาตรวจสอบอีกครั้? "  },
	{  "  จำนวนเงินเกินขีดจำกั? "  },
	{  "  กา?aging ล้มเหล?"  },
	{  "  สถิติต่างๆของตัวละครถูกลบแล้? "  },
	{  "  ไม่มีภาพ  "  },
	{  "  ท่านสามารถลบสถิติต่างๆได้ครั้งเดีย? " },
	{  "  ต้องเป็นสมาชิก clan เท่านั้นจึงจะสามารถใช้ได? "  },
	{  "  ท่านต้องอยู่ใน clan ถึงจะสามารถใช้ไอเทมนี้ได? "  },
	{  "  ระดับไอเทมของท่านยังไม่สามารถอัพเกรดได? "  },
	{  "  ระดับการ aging ของท่านอยู่ที่ -1  "  },
	{  "  ระดับการ aging ของท่านอยู่ที่ -2  "  },
	{  "  ระดับการ aging ของท่านอยู่ที่ +1  "  },
	{  "  ระดับการ aging ของท่านอยู่ที่ +2  " },
	{ "  ค่?atk speed ขอ?quest item ลดลง  " },
	{ " ไอเทมเคว?Level Up " },
	{ " ค่?HP เพิ่มขึ้?15  " },
	{ "  puzzle สมบูรณ์แล้วครั?" },
	{ "  puzzle ยังไม่สมบูรณ์ครั? " },
	{ "  ไม่มีไอเทมที่จะขาย " },
	{ "  ไอเทมได้ถูกขายไปแล้ว  " },
	{ " ร้านนี้ได้ถูกปิดไปแล้ว  " },
	{ " ไม่สามารถหาคนขายได?" },
	{ " จำนวนไม่ถูกต้อ?" },
	{ "  คาแรคเตอร์ผู้ชายไม่สามารถใช้ได?" },
	{ "  คาแรคเตอร์ผู้ห?งไม่สามารถใช้ได้ " },
	{ " คาแรคเตอร์ผู้ห?งไม่สามารถใช้ไอเทมนี้ได้  " },
	{ " คาแรคเตอร์ผู้ชายไม่สามารถใช้ไอเทมนี้ได? " },
	{ " ราคาของไอเทมได้มีการเปลี่ยนแปล? " },
	{ " ไม่มีเงินรางวัลสำหรั?clan ที่ห?" },
	{ " เลเวลนี้ไม่สามารถใช้ force orb ได? " },
	{ " force orb ถูกใช้อยู่ขณะนี้  " },
	{ "  กำลังทดสอบระบบ atk pow " },
	{ " จบกระบวนกา?force orb " },
	{ " stat point เพิ่มขึ้?5 " },
	{ " skill point เพิ่มขึ้?1 " },
	{ " stat แล?skill point เพิ่มขึ้?5 แล?1  " },
	{ " stat แล?skill point เพิ่มขึ้? แล?2  " },
	{ "  เสีย exp จากการตายลดล?1% " },
	{ " HP เพิ่มขึ้?40  "  },
	{ " ท่านอยู่ระหว่างทําเควส "  },
	{ " ตั้งแต่ระดับ 80 ขึ้นไป ค่าความสามารถจะเพิ่มเป็น +7 ทุกๆเลเว? "  },
	{ " ตั้งแต่ระดับ 90 ขึ้นไป ค่าความสามารถจะเพิ่มเป็น +10 ทุกๆเลเว? "  },
	{ " จํานวนมอนสเตอร์ที่ล่าเป็นค่าตั้งต้? "  },
	{ " ไม่ผ่านการทดสอบเนื่องจากเลยเวลาที่กําหนด  "  },
	{ " จำนวนทหารรับจ้างเกินแล้ว  " },
	{ " ไอเทมนี้เป็นสกิลไอเทมที่กำลังใช้อยู่ในปัจจุบัน  " },
	{ " ย้ายไป bless castle ไม่ได้ (กรุณาตรวจสอบ client version)  " },
	{ " ไอเทมนี้ไม่สามารถขายในร้านส่วนตัวได้  " },
	{ " ไม่มีเงินภาษีที่จะรับได้ในขณะนี้  " },
	{ " ท่านได้ตอบแบบสอบถามไปแล้? " },
	{ " ขอบคุณที่ช่วยตอบแบบสอบถา? " },
	{ " ซีลไอเทมนี้ไม่เข้ากับเลเวล  " },
	{ " ตั้งไอเทมใหม่แล้? " },
	{ "  ได้รับชัยชนะในการต่อสู้กับ Fury  " },
	{ "  พ่ายแพ้ในการต่อสู้กั?Fury. " },
	{ "  ได้รับไอเทมเป็นรางวั? " },
	{ "  ไอเทมไม่สามารถใช้ร่วมกันได? " },
};


sMESSAGEBOX2 sMessageBox2[20] = {
	{  "  ท่านต้องการซื้อไอเทมนี? "  ,  "  กี่อัน?  " },
	{  "  ท่านต้องการขายไอเทมนี้  "  ,  "  กี่อัน?  "  },
	{  "  ท่านต้องการทิ้งไอเทมนี? "  ,  "  กี่อัน?  " },
	{  "  ท่านต้องการทิ้งเงิ? "  ,  "  จำนวนเท่าไ? "  },
	{  " "  ,  " "  },
	{  " ท่านต้องการโอนเงิน  "  ,  "  จำนวนเท่าไ? "  },
	{  " ท่านต้องการเก็บเงิ? "  ,  "  จำนวนเท่าไ? "  },
	{  " ท่านต้องการถอนเงิน  "  ,  "  จำนวนเท่าไ? "  },
	{ " จะซื้อ  " , " ดาวกี่ดว?  "  },
	{ " จะบริจาค " , "  เงินเท่าไร?  "  }, 
	{ " จะระบุ  " , "  เงินและไอเทม?  "  }, 
	{ " จะซื้อไอเท? " , "  กี่อัน?  " },
	{ " จะรับเงินรางวั? " , "  เท่าไร?  " },
	{ " จะซื้อไอเท? " , " หรือไม?  " }, 
	{ " จะซื้อไอเท? " , " หรือไม?  " }, 
	{ " จะเบิก  " , "  เงินเท่าไร  " },
	{ " จะซื้อ  " , " ทหารรับจ้างกี่คน?  "  },
};

sMESSAGEBOX3 sMessageBox3[MESSAGE3_MAX] = {
	{  "  ท่านจะ  "  ,  "  เรียนสกิลนี้ ?  "  },
	{  "  ท่านต้องกา? "  ,  "  เลื่อนระดั? "  }, 
	{  "  ท่านจะ  "  ,  "  รับภาระกิจนี?  "  },
	{  "  ท่านต้องกา? "  ,  "  ลบค่าสกิลทั้งหมด?  "  },
	{  "  ก่อนที่จะเรียน  "  ,  "  ท่านต้องจ่ายเงินก่อน!  "  },
	{  "  ท่านต้องกา? "  ,  "  ลบค่าสถิติทั้งหม? "  },
	{  "  ท่านจะ  "  ,  "  รับภาระกิจนี??  "  }, 
	{  "  ท่านจะ  "  ,  "  รับไอเทมชิ้นนี?  "  }, 
	{  "  ท่านจะลงทะเบีย?  "  , " Union Core ในชื่อท่าน? " },
	{ " ท่านจะ " , "  รับไอเทมนี? " },
	{ " ท่านต้องการจ?" , "  วาปไปที่นั่น? " },
	{ " "  , "  กรุณาใส่จำนว?" },
	{ "  ท่านต้องการซื้?" , "  Star? " },
	{ "  ท่านต้องการขาย " , "  ไอเทมนี้? " },
	{  "  ท่านจะรั?"  , "  เควสนี? "  }, 
	{  " ท่านจะจ่าย "  , "  ค่าบริจาคหรือไม่? "  }, 
	{  "  กรุณากำหนด?อควา?"  , "  ประกาศสำหรับร้านด้วยครับ "  }, 
	{  "  ท่านจะแลกเปลี่ยน "  , "  ด้วยไอเทมนี้? "  }, 
	{  "  ท่านจะซื้อ "  , "  ไอเทมนี้? "  }, 
	{  "  ท่านจะยกเลิก "  , "  การลงทะเบียน? "  }, 
	{  "  ท่านต้องการจ?"  , "  เปลี่ยนไอเทมนี้หรือไม่? "  }, 
	{  "  ท่านต้องกา?"  , "  เปลี่ยนไอเทม? "  },
	{  "  ท่านกำลั?"  , "  มองหาเควสอยู่เหร? "  }, 
	{  "  ท่านกำลั?"  , "  มองหาเควสอยู่เหร? "  }, 
	{  "  ท่านกำลั?"  , "  มองหาเควสอยู่เหร? "  }, 
	{  "  ท่านกำลั?"  , "  มองหาเควสอยู่เหร? "  }, 
	{  "  ท่านกำลั?"  , "  มองหาเควสอยู่เหร? "  }, 
	{  "  ท่านกำลั?"  , "  มองหาเควสอยู่เหร? "  }, 
	{  "  ท่านกำลั?"  , "  มองหาเควสอยู่เหร? "  }, 
	{  "  เทเลพอร์ทไ?"  , "  หรือไม? "  },
	{  "  จะรับเคว?"  , "  หรือไม? "  },  
	{  "  จะรับเคว?"  , "  หรือไม?"  },  
	{  "  จะรับเคว?"  , "  หรือไม?"  },  
	{  "  จะเปลี่ยนอาชีพ  "  , "  หรือไม? "  }, 
	{  "  จะแลกเป็?"  , "  ไอเทมหรือไม่? "  },
	{  "  เทเลพอร์ทไ?"  , "  หรือไม?"  },
	{  "  จะซื้อ "  ,  "  คริสตัลทาวเวอร?"  }, 
	{  "  ท่านกำลั?"  , "  รับเคว? "  }, 
	{  "  ท่านกำลั?"  , "  รับเคว? "  }, 
	{  "  ท่านกำลั?"  , "  รับเคว? "  }, 
	{  "  ท่านกำลั?"  , "  รับเคว? "  }, 
	{  "  ท่านกำลั?"  , "  รับเคว? "  }, 
	{  "  ท่านกำลั?"  , "  รับเคว? "  }, 
	{  "  ท่านกำลั?"  , "  รับเคว? "  }, 
	{  "  ท่านกำลั?"  , "  ใช้ไอเทม? "  }, 
	{  "  ท่านกำลั?"  , "  รับเคว? "  },
	{  "  ท่านต้องกา?"  , "  รับไอเทม? "  }, 
	{  "  ท่านต้องกา?"  ,  "  ย้ายไปที?Battle Zone? "  }, 
	{"ทฮ ลฺทนฦ๗ฦฎ", "วฯฝรฐฺฝภดฯฑ๎?"},   
	{"พฦภฬลÛภธทฮ", "ฑณศฏวฯฝรฐฺฝภดฯฑ๎? "}, 
	{"ลฺทนฦ๗ฦฎ", "วฯฝรฐฺฝภดฯฑ๎?"},    
	{"พฦภฬลÛภป", "มฆภÛ วฯฝรฐฺฝภดฯฑ๎?"}, 
	{"ลฺทนฦ๗ฦฎ", "วฯฝรฐฺฝภดฯฑ๎?"},    
};

char *SkillMaster[4] = {
	 "  เรียนสกิ?" ,
	 "  เปลี่ยนคลา?" ,
	 "  ออกจากเก?" 
};

char *SkillMaster2[4] = {
	 " "  ,
	 " "  ,
	 " "  

};

char *ReStartMsg[4] = {
	 "  เริ่มจาก Field " ,
	 "  เริ่มจากเมือ?" ,
	 "  ออกจากเก?" ,
	 "  XP ไม่เพียงพอ " 

};
char *ReStartMsg2[4] = {
	 "  ค่าปรับGold/XP 1% " ,
	 " " ,
	 " " ,
	 "  ถ้าจะเริ่มจา?Field " ,

};

char *SkillUseInfoText[10]= {  "  เรียนรู้ทักษ?" , "  กรุณาเลือกทักษ?" , "  ที่จะเรียน " , "  Skill Point ไม่พ?" , "  ที่จะเรียน "  };
char *sinMsgSkillPoint =  "  Skill Points : %d " ;
char *sinMsgEliteSkillPoint = "  Elite Skill Points : %d " ;
char *sinStateName[5]={ "  H P : %d/%d " , "  M P : %d/%d " , "  STM : %d/%d " , "  X P : %d/%d " , "  X P : %dM/%dM " };


char *TownName[3] = { "  เรียกกลับเมือง Ricarten\r " , "  เรียกกลับเมือง Navisko\r " , "  เรียกกลับเมือง Pillai\r " };


char *sinAbilityName[50] = {  "  ATK Power:  \r "  ,  "  Weapon Speed:  \r "  ,  "  Range:  \r "  ,  "  Critical:  \r "  ,  "  Defense Rating:  \r "  ,  "  ATK Rating:  \r "  ,
			  "  Absorb :  \r "  ,  "  Block :  \r "  ,  "  Speed:  \r "  ,  "  Integrity:  \r "  ,  "  ฟื้น MP :  \r "  ,  "  ฟื้น HP :  \r "  ,
			  "  ฟื้น STM :  \r "  ,  "  Organic Type:  \r "  ,  "  Nature Type:  \r "  ,  "  Flame Type:  \r "  ,  "  Frost Type:  \r "  ,  "  Lightning Type:  \r "  ,  "  Poison Type: \r "  ,
			  "  Water Type:  \r "  ,  "  Wind Type:  \r "  ,  "  HP Regen:  \r "  ,  "  MP Regen: \r  "  ,  "  STM Regen: \r "  ,  "  เพิ่มHP: \r "  ,
			  "  เพิ่มMP:  \r "  ,  "  เพิ่มSTM:  \r "  ,  "  เก็บ Potion ได? \r "  ,  "  ต้องการLevel:  \r  "  ,  "  ต้องการStrength:  \r "  ,  "  ต้องการWillpower:  \r "  ,
			  "  ต้องการTalent:  \r "  ,  "  ต้องการAgility:  \r "  ,  "  ต้องการHealth:  \r "  };
			
char *sinSpecialName[50] = { "  Spec. ATK SPD:  \r  " , "  Spec. CRIT:  \r  " , "  Spec. DEF RTG:  \r  " , "  Spec. ABS RTG:  \r  " ,
			 "  Spec. BLK RTG:  \r  " , " Magic APT:  \r " , " Spec. SPD:  \r  " , "  Spec. Organic:  \r  " , "  Spec. Nature:  \r  " ,
			 "  Spec. Flame:  \r  " , "  Spec. Frost:  \r  " , "  Spec. Lightning:  \r  " , "  Spec. Poison:  \r " , "  Spec. Water:  \r  " , "  Spec. Wind:  \r  " ,
			 "  Spec. ATK POW:  \r  " ,  "  Spec. ATK RTG:  \r  " , "  Spec. RNG:  \r  " , "  Spec. Organic ATK:  \r  " , "  Spec. Nature ATK:  \r  " , "  Spec. Flame ATK:  \r  " , "  Spec. Frost ATK:  \r  " ,
			 "  Spec. Lightning ATK:  \r  " , "  Spec. Poison ATK:  \r  " , "  Spec. Water ATK:  \r  " , "  Spec. Wind ATK:  \r  " , "  Max HP Boost:  \r  " , "  Max MP Boost:  \r  " ,
			 "  ฟื้น HP:  \r  " , "  ฟื้น MP:  \r  " , "  ฟื้น STM:  \r  " , " ราคาขา? \r " , " ราคาซื้อ:  \r " };


char *SpecialName3 =  "  %s Spec. \r " ;
char *MixResultTitle = "  ผลของการ mixไอเท?"  ;
char *NowLevelText = "  เลเวลปัจจุบั?\r "  ;
char *NextLevelText = "  เลเวลถัดไป \r "  ;

char *NormalAttckName = "  Default Attack " ;
char *RequirLevel =  " %s (ต้องการLVL : %d)\r " ;
char *UseItemGroupName =  " ไอเทมที่สามารถใช้ร่วมกับทักษะนี้ได?\r " ;

char *PoisonName = "  Poison Type:\r "  ;
char *FireName = "  Flame Type:\r "  ;
char *AttackAreaName = "  ระยะโจมต?\r "  ;
char *Attack_RateName = "  ความแม่นยำ \r "  ;
char *Max_DamageIncre = "  พลังโจมตีสูงสุ?\r "  ;
char *DamageAddName = "  เพิ่มพลังโจมตี: \r "  ;
char *Attack_SpeedAdd = "  เพิ่มความเร็วโจมตี: \r "  ;
char *IncreBlock = "  เพิ่มอัตราการป้องกัน: \r "  ;
char *CountinueTime = "  ระยะเวลา: \r "  ;
char *UseManaName = "  ใช?MP: \r "  ;
char *DamageName = "  พลังโจมต? \r "  ;
char *ShootingRangeName = "  ระยะ: \r "  ;
char *IncreAsorb = "  ลดอัตราความเสียหายจากการโจมต?\r "  ;
char *SecName = " วิ "  ;
char *PlusDamageName = "  เพิ่มพลังโจมตี \r "  ;
char *HitNumName = "  จำนวนครั้ง : \r "  ;
char *DecreLifeName = "  HP ลด : \r "  ;
char *Attck_RateAdd = "  ค่าเพิ่มเติมความแม่นยำ : \r  "  ;
char *Add_CriticalName = "  เพิ่?Critical : \r "  ;
char *Push_AreaName = "  Push-back Length : \r "  ;
char *FireAttackDamageAdd =  "  Flame ATK : \r "  ;
char *IceName = "  Frost Property : \r "  ;
char *IceAttackDamageAdd = "  Frost ATK : \r "  ;
char *StuneRate = "  % Stun : \r "  ;
char *DefenseRateIncre = "  เพิ่มค่าอัตราการป้องกั?\r "  ;
char *WeaponSizeName =  "  เพิ่มขนา?\r "  ;
char *HwakRotationNum = "  Hawk Rotations:\r "  ;
char *WeaponSpeedAddName  = "  เพิ่มความเร็วอาวุธ:\r "  ;
char *IncreAttack_RateName = "  เพิ่มพลังโจมตี:\r "  ;
char *ShootingNumName = "  จำนว?Shots:\r "  ;
char *SeriesShootingCount = "  ยิงต่อเนื่อง :\r "  ;
char *UseStaminaName = "  ใช?Stamina :\r "  ;
char *MasterSkillMoneyName = "  ราคาทักษ?\r "  ;

char *ItemAgingResult;		

char *sinGold = " %d Gold " ;
char *sinGiveItem5 =  "  Gift Item\r " ;
char *sinCopyItem5 =  "  Copied Item\r " ;
char *sinNum7 =  " รอ  " ;
char *sinSkillPointName =  "  Skill Point " ;	
char *sinG_Pike_Time3 =  "  Frozen Time:\r " ;	


char *sinItemLimitTimeOverMsg = "  หมดอายุแล้วค่ะ \r "  ;
char *sinDeadSongPyeunEat = "  ว้าหมดอายุซะแล้ว!  "  ;
char *SmeltingResultTitle = "พฦภฬลÛ มฆทร ฐแฐ๚";		
char *ManufactureResultTitle = "พฦภฬลÛ มฆภÛ ฐแฐ๚";	


char *sinMaxDamageAdd = "  เพิ่มพลังโจมตีสูงสุด + \r "  ;
char *sinDamagePiercing = "  (Piercing attack)\r "  ;
char *sinAddStamina = "  เพิ่มstamina: \r "  ;
char *sinAddLife = "  ฟื้น HP: \r "  ;

char *sinDamageUndead50 = "  เพิ่มความเสียหาย 50% แก?Undead :\r "  ;
char *sinNumCount2 = "  number:\r "  ;
char *sinNumCount3 = " อั?\r "  ;
char *sinDecreDamage = "  ลด damage:\r "  ;
char *sinConvert4 = "  conversion rate:\r "  ;
char *sinIncreElement = "  เพิ่?Element feature:\r "  ;
char *sinPartyIncreElement = "  พลังธาตุของสมาชิกในปาร์ตี้เพิ่มขึ้?50% \r "  ;
char *sinFireBallDamage2 = "  (100% damage to the targeted enemy)\r "  ;
char *sinFireBallDamage3 = "  (targeted area 60 (1/3 damage))\r "  ;
char *sinAddDamage7 = "  เพิ่มdamage : \r "  ;
char *PlusDamageWeapon = "  อาวุ?"  ;
char *SparkDamage = "  โจมตีต่ออั?\r "  ;
char *SparkNum7 = "  จำนวนspark max:\r "  ;
char *StunRage = "  ระยะ Stun : \r "  ;
char *RecvPotion7 =  "  กี่ขวด " ;


char *PartyArea7 =  "  ระยะ Party:\r "  ;
char *Area17 =  "  ระยะ:\r "  ;
char *AddAttack_Rate9 =  "  ความแม่นยำ \r "  ;
char *PiercingRange =  "  ระยะ Piercing: \r "  ;
char *IncreDefense = "  เพิ่มค่าป้องกั?\r "  ;
char *AddShootingRange = "  เพิ่มระยะการยิ?\r "  ;
char *LifeAbsorb = "  Life absorb.: \r "  ;
char *FireDamage = "  Fire Damage: \r "  ;
char *IceDamage = "  Ice Damage: \r "  ;
char *LightningDamage = "  Lighting Damage: \r "  ;
char *AddManaRegen = "  เพิ่มอัตราการฟื้นคืน Mana: \r "  ;
char *LightNum = "  # of Lighting: \r "  ;
char *ReturnDamage = "  สะท้อนพลังโจมต? \r "  ;
char *Area18 = "  ระยะครอบคลุม: \r "  ;
char *IncreMana5 = "  เพิ่มMana: \r "  ;
char *Area19 = "  ระยะครอบคลุม: \r "  ;
char *HelpTitle8 = "  ช่วยเหลื?"  ;
char *QuestTitle8 = "  เควส "  ;
char *ResearchTitle8 = "  แบบสอบถา?"  ;
char *TeleportTitle8 = "  TELEPORT "  ;

char *IncreWeaponAttack_RateName = "  เพิ่มความแม่นยํา: \r "  ;
char *AddMaxDamage = "  เพิ่มพลังโจมตีสูงสุด: \r "  ;
char *LinkCoreName =  "  วาร์ปไปยังสมาชิกในแคลน  \r " ;
char *DesLinkCore =  "  ชื่อ: " ;
char *Itemul =  "  ไอเท?" ;
char *ItemRecvOk =  "  ท่านต้องการรับ? " ;
char *Money5 =  "  Gold " ;
char *Exp5 =  "  ค่าประสบการณ?" ;
char *WingItemName[] = { "  Metal Wing  " , "  Silver Wing  " , "  Gold Wing  " , "  Diamond Wing  "  , "  Chaos Wing  " };
char *WarpGateName[] = { "  Warp Gate  " , "  Ricarten  " , "  Pillai Town  " , "  Land of Dusk  " , "  Bamboo Forest  " , "  Ruinen Village  " , "  Navisko town  " , "  Forbidden Land  " ,  "  Eura Village  "  };
char *sinWarningName5 =  "  Warning!!! " ;
char *ClanCristalName =  "  แคลนคริสตั?\r " ;
char *NowMyShopSell =  "  กำลังขายอยู่ \r " ;
char *SecretNumName =  "  กรุณาใส่หมายเลขรหั?" ;
char *MyShopExpDoc7 =  "  ร้านค้?" ;
char *NotAgingItem2 =  "  ไอเทมนี้ไม่สามาร?age ได?" ;
char *ExpPercent2 =  "  ค่าประสบการณ?%d.%d%s " ;
char *ExpPercent3 = "  ค่าประสบการณ?%d.0%d%s "  ;
char *Mutant7 =  "  Mutant " ;
char *Mechanic7 =  "  Mechanic " ;
char *Demon7  =  "  Demon " ;
char *Nomal7  =  "  Normal  " ;
char *Undead7  = "  Undead "  ;
char *MonsterAddDamage2 =  "  เพิ่?(Damage)\r " ;
char *MonsterAddDamageFire =  "  เพิ่?Fire Damage\r " ;


char *HoldStarNumDoc = "  จำนว?Star ที่มีอยู?"  ;
char *StarItemBuy7 = "  ซื้อ Star ไอเท?"  ;
char *ChangeMoney7 = "  (Star 1 อั?ราคา : 100000 Gold) "  ; 
char *HaWarpGateName[] = {  "  Bless Castle  "  ,};
char *FallGameName = "ภฯฑืทฏม๘ ฝฃ";



char *LightningDamage2 = "  Lightning Damage:\r "  ;
char *SheildDefense = "  เพิ่มค่าการป้องกัน: \r "  ;

char *DemonDamage4  = "  Demon Damage: \r "  ;
char *PoisonDamage3  = "  Poison Attack: \r "  ;
char *PikeNum4   = "  จำนว? \r "  ;
char *poisoningTime  = "  เวลา Poisoning: \r "  ;
char *PlusCriticalName = "  เพิ่?Critical: \r "  ;
char *SpiritFalconDamage2 = "  Spirit Falcon Damage: \r "  ;
char *LifeGegenPlus = "  ฟื้น HP: \r "  ;
char *PlusDamage4 = "  เพิ่มพลังโจมตี: \r "  ;
char *PiercingPercent = "  Piercing Percent: \r "  ;
char *DamageToLife = "  เปลี่ยนค่าความเสียหายเป็?HP: \r "  ;
char *MyMonster7 = "  % การสะก?\r "  ;
char *LifeIncre4 = "  เพิ่มพลังชีวิต: \r "  ;
char *UndeadDamage3 = "  Undead Damage: \r "  ;

char *AttackNum3   = "  โจมตีต่อเนื่อง: \r "  ; 
char *AttackRateMinus = "  ลดความแม่นยำ \r "  ; 
char *MaxDamagePlus2 = "  เพิ่มพลังโจมตีสูงสุด \r "  ; 
char *LightningAddDamage3 = " Lightning :\r "  ; 
char *ReLifePercent4  = "  % สำเร็จ: \r "  ; 
char *GetExp3  = "  รั?Exp:\r "  ; 
char *ResurrectionChar4  = "  Resurrection Character LV "  ; 
char *ExtinctionPercent2  = "  % สำเร็จ: \r "  ; 
char *ExtinctionAmount2  = "  จำนว?Extinction: \r "  ; 
char *IncreLifePercent2 = "  เพิ่?HP: \r "  ; 

char *ReduceDamage3 = "  ลดค่าความเสียหาย: \r "  ; 
char *IncreMagicDamage = "  เพิ่มพลังโจมตีจากการใช?Magic: \r "  ; 
char *AttackDelay3 = "  Attack Delay: \r "  ; 

char *FireDamage2 = "  Fire Damage: \r "  ;
char *IceDamage2 = "  Ice Damage: \r "  ;
char *AddDefense8 = "  เพิ่มพลังป้องกัน: \r "  ;
char *SkillDamage5 = "  Skill Damage: \r "  ;

char *FireDamage3 = "  Fire Damage: \r "  ;
char *AddSpeed7 = "  เพิ่มความเร็?\r "  ;
char *AfterDamage7 = "  After Damage: \r "  ;
char *MonsterSight7 = "  Monster เห็น: \r "  ;



char *LinghtingAddDamage4=  "  Add attack rate on lightning: \r  "  ;
char *MaxBoltNum4=  "  Max voltage: \r  "  ;
char *AddAbsorb4=  "  Add rate on absorb: \r  "  ;
char *IncreArea4=  "  Increasing range: \r  "  ;
char *IncreAttack4=  "  More attacking power: \r  "  ;
char *GolemLife4=  "  Life+strength: \r  "  ;


char *SubAbsorb4=  "  Decreasing absorption: \r  "  ;
char *AreaDamage4=  "  Attacking rate for range: \r  "  ;
char *MaxAttackNum4=  "  Max hits: \r  "  ;
char *LifeUp4=  "  Add vitality: \r  "  ;

char *CriticalAddDamage4=  "  Increase of critical: \r  "  ;
char *MonstervsSubCritical4=  "  Weaken critical of monster: \r  "  ;
char *ChargingAddPercentDamage4=  "  Add attacking rate on charging: \r  "  ;

char *IncreEvasionPercent4=  "  Additinal percentage of evasion: \r  "  ;
char *AddShadowNum4=  "  Increasing combination of ocular: \r  "  ;

char *WolverinLife4=  "  Vitality:\r  "  ;
char *WolverinRate4=  "  Accuracy:\r  "  ;
char *WolverinDefense4=  "  Defence rate:\r  "  ;
char *AddEvasion4=  "  Increasing ability of evasion:\r  "  ;
char *AddDamage4=  "  Increasing attacking rate(physic):\r  "  ;
char *FalconAddDamage4=  "  Increasing attacking rate of falcon:\r  "  ;


char *IncreAttackAbsorb4=  "  Increasing absorption rate:\r  "  ;

char *RectAngleArea4=  "  Attacking at sharp angled range:\r  "  ; 

char *MonsterSubSpeed4=  "  Decreasing speed of attacted monster:\r  "  ;


char *AddLifeRegen4=  "  Add life-regeneration:\r  "  ;
char *AddManaRegen4=  "  Add mana-regeneration:\r  "  ;
char *MagicArea4=  "  Magic affected range:\r  "  ;
char *ChainNum4=  "  A number of affected monster:\r  "  ;
char *ChainRange4=  "  The rage of affected monster:\r  "  ;
char *UndeadDamageAbsorb4=  "  Undead attacking absorption:\r  "  ;
char *UserBlockPercent4=  "  Blocking rate for character:\r  "  ;

char *SecondIncreMana4=  "  Increasing mana rate per second:\r  "  ;
char *FireDamage4=  "  Fire attacking rate:\r  "  ;
char *DecreSpeed4=  "  Decreasing Speed:\r  "  ;
char *DecreAttack4=  "  Decreasing attacking rate:\r  "  ;
char *AddPercentDamage4=  "  Adding attacking rate:\r  "  ;


char *ChainDamage3  = "  ChainDamage)\r  "  ;
char *BrandishDamage3 = "  BrandishDamage  "  ;
char *PhysicalAbsorb3 = "  PhysicalAbsorb  "  ;
char *SparkDamage3  = "  SparkDamage  "  ;
char *BrutalSwingCritical3 = "  BrutalSwingCritical  "  ;
char *Attck_RateAdd5 = "  เพิ่?Attack Rate:\r  " ;
char *Triumph4= " Triumph " ;
char *Use4= " you " ;
char *DivineShield4= " Blocking rate of divine shiled " ;



char *QuestMonsterName[] = { " Bagon " , " Skeleton Warrior " , " Head Cutter " , " Armored Beetle " , " Skeleton Ranger " , " Titan "  ,
          " Forgetten Land Monster " , " Oasis Monster " , " Dungeon 1F Monster " };



char *VampOption[10] ={ " Aging Rating is increased: \r " , " blood sucking: \r " , " Damage: \r " , " Reduce Life : \r " , " good luck: \r " };


char *Quest3ItemName[]={ " Demon Hunter " , " Ancient Revenge " , " Myst " , " Double Side " , " Anaconda " , " Platinum Sword " , " Ghost " };

char *Quset3ItemDoc15 =  " เควสไอเท? " ;
char *Quset3ItemDoc16 =  "  ได้หายไป  " ;

char *SparkDamage10 =  " Spark Damage:\r " ;

char *RequirLevel3 =  " (ต้องการLevel:%d)\r  " ;

char *RecvItemTT =  " ได้รับไอเทมแล้? " ;
char *PuzzleEvent5 =  " Puzzle ที่สมบูรณ์  " ;
char *BabelHorn =  " Babel Horn  " ;
char *NineTailFoxItem =  " NineTail amulet  " ;
char *MyShopItemSell5 =  " ราคาขา?\r  " ;
char *CristalItem   = " คริสตั?7 ชิ้น  " ;
char *StarDust = "Glitering powder";
char *ChristMas = "Merry Christmas";

char *sinDeadCandyEat =  " เฮ้ย! นี่มันเก่าจนหมดอายุแล้วนี่นา!  " ;

char *PotionCntDoc2 =  " ราคาขายต่ออั? " ;
char *ItemPrice7 =  " ราคาไอเท? " ;

char *BuyMyShopItem7 =  "  %s ได้ซื้อไอเทม %s ไป  %d อันเป็นเงิ?%d บา? " ;  
char *BuyMyShopItem8 =  "  ได้ซื้อไอเทม  %s ขอ?%s มา %d อันเป็นเงิ?%d บา? " ;  
char *ItemName87 =  " ไอเท? " ;

char *sinEvent87 =  " คำขอของนักเก็บตัวฉกา? " ;
char *sinAddDamageItem =  " เพิ่มพลังโจมตี: \r " ;
char *sinContinueTimeItem =  " ระยะเวลา: \r " ;
char *BuyPotionMoney =  " จำนวนเงิ? " ;
char *BuyPotionKind =  " จำนว? " ;
char *SheltomName2[] = { " Lucidy " , " Sereno " , "  Fadeo " , " Sparky " , " Raident " , " Transparo " , " Murky " , " Devine " , " Celesto " };

char *AddPercentDamage3=  " เพิ่มพลังโจมตี %: \r " ;

char *sinLuckyBox=  " ถุงนำโชค  " ;

char *SodMessage_Etc[] = {
 " เงินที่จะได้รับจากการเ?าร่ว?Bellatra Clan  " ,
 " มีเพียงหัวหน้า Clan เท่านั้นที่จะรับได? " ,
 " และค่าธรรมเนียมคือ %d%s. " ,
};

char *SodMessage_Clan[] = {
 " เงินทั้งหมดที่ได้คือ  " ,
 " เงินรางวัลจา?Bellatra เมื่อครั้งก่อน  " ,
};

char *SodMessage_Master[] = {
 " เงินทั้งหมดที่ได้คือ  " ,
 " เงินรางวัลจา?Bellatra เมื่อครั้งก่อน  " ,
 " ท่านต้องการจะรับหรือไม? " ,
};

char *OtherClanMaster[] = {
 " ยังมีเงินรางวัลเหลืออยู่บางส่ว? " ,
 " กรุณาระบุยอดเงินที่ต้องการรั? " ,

};

	
char *SiegeMessage_Taxrates[] = {
	 " อัตราภาษีเปลี่ยนเป็น %d%s  " ,
	 " ยอดภาษีที่รวบรวมได้ถึงปัจจุบัน  " ,
	 " gold  " ,
	 " จะเบิกภาษีหรือไม? " ,
	 " อัตราภาษีปัจจุบันคือ %d%s  " ,
};
char *SiegeMessage_MercenrayA[] = {
	 " ทหารกองหนุนริคาร์เทน  " ,
	 " กองต่อสู้ที่มาจากกองหนุน  " ,
	 " ราคาถูกแต่ว่าพลังต่อสู้อ่อนที่สุ? " ,
	 " สมาชิกทหารรับจ้างมากสุ?0 / %d  " ,
};
char *SiegeMessage_MercenrayB[] = {
	 " กองทหารป้องกันรีคาร์เท? " ,
	 " มีความสมดุลของศักยภาพทุกด้าน  " ,	
	 " มีพลังต่อสู้ชั้นกลาง  " ,
	 " สมาชิกทหารรับจ้างมากสุ?20 / %d  " ,
};
char *SiegeMessage_MercenrayC[] = {
	 " กองทหารป้องกันราชอาณาจัก?bless  " ,
	 " ในฐานะทหารรับจ้างชั้นสูงสุ? " ,
	 " พลังต่อสู้แข็งแกร่งที่สุ? " ,
	 " สมาชิกทหารรับจ้างมากสุ?20 / %d  " ,
};
char *SiegeMessage_TowerIce[] = {
	 " ไอซ์ คริสตั? " ,
	 " ธาตุน้ำแข็งความเร็วเคลื่อนที่ตกลงและ  " ,
	 " มีความสามารถพิเศษความเร็วโจมตีลดลง  " ,
	 " ตั้งไอซ์คริสตัลเรียบร้อย  " ,
};
char *SiegeMessage_TowerFire[] = {
	 " ไฟคริสตั? " ,
	 " ด้วยธาตุไฟพลังโจมตีสูงขึ้นสุดแต่ว่? " ,
	 " ไม่มีความสามารถพิเศษ  " ,
	 " ตั้งไฟคริสตัลเรียบร้อย  " ,
};
char *SiegeMessage_TowerLighting[] = {
	 " ไลท์นิ่งคริสตั? " ,
	 " ด้วยธาตุสายฟ้าความเร็วเคลื่อนที่ตกลงแล้ว  " ,
	 " มีความสามารถพิเศษความเร็วโจมตีลดลง  " ,
	 " ตั้งไลท์นิงคริสตัลเรียบร้อ? " ,
};
char *SiegeMessage_MerMoney =  " ค่าใช้จ่ายทหารรับจ้า? " ;
char *SiegeMessage_TowerMoney =  " ค่าใช้จ่ายทาวเวอร์  " ;


char *sinClanMaster7 =  " หัวหน้าแคล? " ;
char *sinPrize7 =  " เงินรางวัล:  " ;

char *sinLevelQuestMonster[]={ " Bargon " , " Muffin " , " Dire Bee " , " Typhoon " , " Ratoo " , " Grotesque " , " Iron Fist " };
char *sinLevelQusetDoc= " Quest> %s %d number of monster needed " ;

char *sinTeleportDoc[] = { " ทางเ?าถํ้าเห็? " , " ทางเ?าถํ้าผึ้? " , " ดินแดนต้องคําสาป  " , " ดินแดนต้องห้าม  " };
char *sinLevelQuest90_2Mon[] = { " Omeca " , " D-Machine " , " Mountain " };
char *sinLevelQusetDoc2= " <เควส> ไปล่?%s มาจํานวน %d ตั?" ;
char *sinLevelQusetDoc3= " <เควส> ไปเอาไอเทมจา?%s  " ;
char *sinLimitTiem2 =  " เวลาที่กําหน? \r " ;
char *sinMinute2 =  " นาที  " ;
char *sinDay4 =  " day " ;
char *sinHour4 =  " hour " ;
char *sinLevelQusetDoc4= " <เควส> ล่?%s %d ตัวเรียบร้อย  " ;

sinSTRING sinTestMsg7( " ร่อแร่ อ่อนๆกันทั้งนั้น!  " );

char *sinMonCodeName[]={
	0,
	 " Bargon " ,
	 " Skeleton Warrior " ,
	 " Head Cutter " ,
	 " Armored Bettle " ,
	 " Skeleton Ranger " ,   
	 " Titan " ,
	 " Muffin " ,
	 " Dire Bee " ,
	 " Typhoon " ,
	 " Ratoo " ,      
	 " Grotesque " ,
	 " Iron Fist " ,
	 " Omega " ,
	 " D-Machine " ,
	 " Mountain " ,      
	 " Skeleton Knight " ,
	 " Solid Snail " ,
	 " Thron Crawler " ,
	 " Mummy " ,
	 " Doom Guard " ,     
	 " Figon " ,    
	 " Stone Giant " ,
	 " Stone Golem " ,
	 " Iron Guard " ,
	 " Avelin " ,      
	 " Avelisk-L " ,
	 " BeEvil " ,
	 " Illusion Knight " ,
	 " Nightmare " ,
	 " Witch " ,      
	 " Heavy Goblin " ,
	 " Dawlin " ,
	 " Stygian " ,
	 " Incubus " ,
	 " Chain Golem " ,     
	 " Dark Specter " ,
	 " Metron " ,
	 " Avelisk Lord " ,
	 " Dusk " ,
	 " Sadness " ,    
	0,
};

char *ChargingTime4= " เพิ่มความเร็วชาร์จ \r  " ;
char *AddIceDamage4= " พลังโจมตีธาตุนํ้าแข็งเพิ่มขึ้น \r  " ;
char *IceTime4= " ระยะเวลา : \r  " ;
char *sinAttackType =  " โจมตีแบบ : \r "  ;
char *sinAttackType2[2] ={ " โจมตีอัตโนมัติ \r  " , " Auto\r " };

char *Won= " Gold " ;


char *CastlItemInfo[] ={
	{ " แม้จะอยู่ในภาวะไร้ศัตรูช่วงหนึ่งแต่ว่า \r  " },  
	{ " อัตราคริติคอ?\r  " },
	{ " อัตราหลบเพิ่?\r  " },
	{ " HP MP Stam ของคนในปาร์ตี้ \r  " },
	{ " ฟื้นทันทีที่ตา?\r  " },
	{ " การโจมตีคริติคอลทาวเวอร์ \r  " },   
	{ " พลังโจมตีเวลาโจมตีเป้าหมาย 20% \r " },
	0,
};
char *CastlItemInfo2[] ={
	{ " พลังโจมตีลดล?/2 \r  " },
	{ " เพิ่มขึ้?% \r  " },
	{ " สูงขึ้?\r  " },
	{ " ฟื้นทั้งหม?\r  " },
	{ " \r " },
	{ " ชดเชยให้ 50% \r  " },
	{ " เพิ่มให้แรงขึ้?\r  " },
	0,
};


char *CharClassTarget[8]={
	 " เป้าหมาย(fighter)\r " ,
	 " เป้าหมาย(mechanician)\r " ,
	 " เป้าหมาย(pikeman)\r " ,
	 " เป้าหมาย(archer)\r " ,
	 " เป้าหมาย(knight)\r " ,
	 " เป้าหมาย(atalanta)\r " ,
	 " เป้าหมาย(magician)\r " ,
	 " เป้าหมาย(priestess)\r " ,
};
char *AttributeTower[4]={
	 " ธาตุ(ไฟ) \r " ,
	 " ธาตุ(น้ำแข็? \r " ,
	 " ธาตุ(สายฟ้า) \r " ,
	 " เวลาแสดงผล %d วินาที \r " ,
};

char *SiegeMessage_MerComplete = " จัดวางทหารรับจ้างเรียบร้อยแล้ว  " ;


char *haQuestMonsterName[]={
	 " Hopy " ,
	 " Rabie " ,
	 " Hobgoblin " ,
	 " NorthGoblin " ,
	 " Skeleton " ,
	 " Corrupt " ,
	 " Cyclops " ,
	 " Bagon " ,
	0,
};
char *ha100LVQuestItemName[]={
	 " Minotaur Axe " ,
	 " Extreme Talon " ,
	 " Dragon Bone Hammer  " ,
	 " Hellfire Scythe " ,
	 " Revenge Bow " ,
	 " Immortal Sword " ,
	 " Salamander Javelin " ,
	 " Gothic Staff " ,
	0,
};

char *ha100LVQuestMonterName[]={
	 " Monsters in the Heart of Perum " ,
	 " Monsters of the Galluvia Valley " ,
	0,
};
char *ha100LVQuestName =  " Fury's phantasma " ;


char *PremiumItemDoc[][2]={
	{ "It makes stat points\r "  , "to be restributed.\r " },   
	{ "It makes skill points\r "  , " to be restributed.\r " },  
	{ "It makes stat/skill points\r " , "to be restributed.\r " },   
	{ "It makes the dead character \r "   , "to be revived.\r " },    
	{ "Becomes invincible for the set time.\r " , "The attack power decrease in 1/2\r " },  
	{ "15% increase \r "   , "on the critical attack.\r " },		
	{ "15% increase of \r "    , "evade chance.\r " },		
};
char *UpKeepItemDoc[] = {
	 "Remaining Time : %dMin" ,
	 "Extra Item Won %d%s Increase" ,
	 "Extra EXP Won %d%s Increase" ,
	 "Attack %d%s Increase" ,
	 "Restore monster's HP(part)",
	 "Restore monster's MP(part)",
	0,
};
char *UpKeepItemName[] = {
	 "Third Eyes " ,
	 "EXP Increase Potion " ,
	 "Vampiric Cuspid",
	 "Mana Recharge Potion",
	0,
};
