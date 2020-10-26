

sMESSAGEBOX	sMessageBox[50] = {
	{"物品欄位置不足      "},       
	{"超過了負重能力      "},   
	{"目前不能使用此物品  "},	   
	{"你的錢不夠          "},   			   
	{"物品無法融合        "},
	{"超過了可交易的數量  "},
	{"交易取消了          "},
	{"不能保管藥水        "},
	{"物品融合失敗！      "},
	{"謝謝您的捐贈:)      "},
	{"倉庫已滿，無法保管  "},
	{"這個物品不能升級    "},
	{"對方更換了交易物品，請重新確認  "},
	{"你無法隨身攜帶這麼多錢"}, 
	{"執行失敗            "},
	{"    能力值已經初始化了　   "},			
	{"  找不到道具的圖示　   "},
	{"能力值初始化僅限一次　"},

};

sMESSAGEBOX2 sMessageBox2[20] = {
	{"幾個物品","要買嗎?"},
	{"幾個物品","要賣嗎?"},
	{"幾個物品","要扔掉嗎?"},
	{"多少金錢","要扔掉嗎?"},
	{"",""}, 
	{"多少金錢","要交易嗎?"},
	{"多少金錢","要移動嗎?"},
	{"多少金錢","要回收嗎?"},
	{"  把物品  ","要買嗎?"}, 
	{"  把物品  ","要買嗎?"}, 
	{"  把物品  ","要買嗎?"}, 
	{"  把物品  ","要買嗎?"}, 
	{"  把物品  ","要買嗎?"}, 
	{"  把物品  ","要買嗎?"}, 
	{"  把物品  ","要買嗎?"},  
};

sMESSAGEBOX3 sMessageBox3[10] = {
        {"技能學習 ","要執行嗎?"},
	{"轉職", "要嗎?"}, 
	{"任務","要接嗎?"},
	{"重新分配","要執行嗎?"},
	{"參加活動費用","元"},
	{"能力值初始化 ","要執行嗎?"},			
	{"任務", "要接嗎?"}, 
	{"物品", "要嗎?"}, 
	{" 公會捲軸 ", "要申請嗎?"}, 
	};


char *SkillMaster[4] = {
	"     學習技能",
	"        轉職 ",
	"       離開遊戲 "

};
char *SkillMaster2[4] = {
	"",
	"",
	""

};

char *ReStartMsg[4] = {
	"        回到野外     ",
	"        回到城鎮     ",
	"        離開遊戲     ",
	"       經驗值不足    "

};
char *ReStartMsg2[4] = {
	"   損失1%的錢/經驗值 ",
	"",
	"",
	"      不能回到野外   ",

};

char *SkillUseInfoText[10]= { "      技能/魔法修煉      ","    學習及提升   ","   請選擇技能/魔法    ",
		"  ⑷由於目前您沒有技能點 ","   無法學習技能 " 
  };

char *sinMsgSkillPoint = "     技能點お : %d";

char *sinStateName[5]={
   "生命值 : %d/%d  ",
   "魔法值 : %d/%d  ",
   "精力值 : %d/%d  ",
   "經驗值 : %d/%d  ",
   "經驗值 : %dM/%dM  "};


char *TownName[3] = {"回到瑞卡登城\r","回到納維斯城\r","回到菲樂伊城\r"};

char *sinAbilityName[50] = {"攻擊力: \r","攻擊速度: \r","射程: \r","必  殺: \r","防禦力: \r","命中率: \r",
					"額外防禦力: \r","格擋率: \r","移動速度: \r","耐久度: \r","恢復魔法值: \r","恢復生命值: \r",
					"恢復精力值: \r","體屬性: \r","自然屬性: \r","火屬性: \r","冰屬性: \r","雷屬性: \r","毒屬性: \r",
					"水屬性: \r","風屬性: \r","生命值再生: \r","魔法值再生: \r","精力值再生: \r","生命值提高: \r",
					"魔法值提高: \r","精力值提高: \r","藥水存放數量: \r","等級要求: \r","力量要求: \r","智力要求: \r",
					"才能要求: \r","敏捷要求: \r","體質要求: \r"};



char *sinSpecialName[50] = {"特有攻擊速度: \r","特有必殺: \r","特有防禦力: \r","特有額外防禦力: \r",
						"特有格擋率: \r","魔法熟練度: \r","特有移動速度: \r","特有體屬性: \r","特有自然屬性: \r",
						"特有火屬性: \r","特有冰屬性: \r","特有雷屬性: \r","特有毒屬性: \r","特有水屬性: \r","特有風屬性: \r",
						"特有攻擊力: \r","特有命中率: \r","特有射程距離: \r","特有體攻擊: \r","特有自然攻擊: \r","特有火攻擊: \r","特有冰攻擊: \r",
						"特有雷攻擊: \r","特有毒攻擊: \r","特有水攻擊: \r","特有風攻擊: \r","最大生命值增加: \r","最大魔法值增加: \r",
						"生命值再生: \r","魔法值再生: \r","精力值再生: \r","賣出價格: \r","買入價格: \r"



};


char *SpecialName3 = "%s 特有\r";
char *MixResultTitle = "物品融合的結果";
char *NowLevelText = "目前等級\r";
char *NextLevelText = "下一個等級\r";

char *NormalAttckName ="基本攻擊";
char *RequirLevel = "%s (等級要求:%d)\r";
char *UseItemGroupName = "可用的物品組\r";

char *PoisonName = "毒屬性:\r";
char *FireName = "火屬性:\r";
char *AttackAreaName = "攻擊範圍:\r";
char *Attack_RateName = "命中率:\r";
char *Max_DamageIncre = "最大攻擊力增加:\r";
char *DamageAddName = "攻擊力加強:\r";
char *Attack_SpeedAdd = "攻擊速度增加:\r";
char *IncreBlock = "格擋率增加:\r";
char *CountinueTime = "維持的時間:\r";
char *UseManaName = "使用魔法值:\r";
char *DamageName = "攻擊力:\r";
char *ShootingRangeName = "射程:\r";
char *IncreAsorb = "額外防禦力增加:\r";
char *SecName = "秒";
char *PlusDamageName = "攻擊力增加:\r";
char *HitNumName = "連續攻擊的次數:\r";
char *DecreLifeName = "生命值減少值:\r";
char *Attck_RateAdd = "命中率增加值:\r";
char *Add_CriticalName = "提高必殺率:\r";
char *Push_AreaName = "退後的距離:\r";
char *FireAttackDamageAdd ="提高火屬性的攻擊力 :\r";
char *IceName = "冰屬性:\r";
char *IceAttackDamageAdd = "提高冰屬性的攻擊力:\r";
char *StuneRate = "暈倒的機率:\r";
char *DefenseRateIncre = "防禦機率增加:\r";
char *WeaponSizeName ="武器的大小:\r";
char *HwakRotationNum = "鷹的盤旋數:\r";
char *WeaponSpeedAddName  = "武器的速度加快:\r";
char *IncreAttack_RateName = "命中率增加:\r";
char *ShootingNumName = "發射數量:\r";
char *SeriesShootingCount = "連續發射的箭數:\r";
char *UseStaminaName = "使用精力值:\r";
char *MasterSkillMoneyName = "技能學習的費用:\r";

char *ItemAgingResult = "物品融合的結果";

char *sinGold ="%d元";
char *sinGiveItem5 = "贈送的道具";
char *sinCopyItem5 = "複製好的道具";
char *sinNum7 = "RND";
char *sinSkillPointName = "技能點數";
char *sinG_Pike_Time3 = "凍結時間 :\r";
char *sinItemLimitTimeOverMsg = "已經過了有效期限\r";
char *sinDeadSongPyeunEat = "天啊! 這月餅已經壞掉了!";


char *sinMaxDamageAdd = "最大攻擊力加強+\r";
char *sinDamagePiercing = "(穿貫攻擊)\r";
char *sinAddStamina = "精力增加量:\r";
char *sinAddLife = "生命力恢復值:\r";

char *sinDamageUndead50 = "對不死系列怪獸 50% 攻擊力增加:\r";
char *sinNumCount2 = "數量:\r";
char *sinNumCount3 = "數量\r";
char *sinDecreDamage = "攻擊力減少值:\r";
char *sinConvert4 = "變換量:\r";
char *sinIncreElement = "元素屬性上升值:\r";
char *sinPartyIncreElement = "屬性上升之50%適用於隊員\r";
char *sinFireBallDamage2 = "(很正確的被打的怪獸收到 100% 傷害)\r";
char *sinFireBallDamage3 = "(攻擊範圍 60 (1/3 受傷))\r";
char *sinAddDamage7 = "攻擊力增加:\r";
char *PlusDamageWeapon = "武器";
char *SparkDamage = "平均攻擊力:\r";
char *SparkNum7 = "最大攻擊次數:\r";
char *StunRage = "攻擊距離:\r";


char *PartyArea7 ="戰鬥時隊伍半徑:\r";
char *Area17 ="半徑:\r";
char *AddAttack_Rate9 ="命中率增加:\r";
char *PiercingRange ="貫通距離:\r";
char *IncreDefense = "防禦力增加:\r";
char *AddShootingRange = "攻擊距離增加:\r";
char *LifeAbsorb = "生命值吸收量:\r";
char *FireDamage = "增加火屬性攻擊力:\r";
char *IceDamage = "增加冰屬性攻擊力:\r";
char *LightningDamage = "增加雷屬性攻擊力:\r";
char *AddManaRegen = "增加魔法再生值:\r";
char *LightNum = "閃電次數:\r";
char *ReturnDamage = "反射傷害:\r";
char *Area18 = "有效半徑:\r";
char *IncreMana5 = "增加魔法值:\r";
char *Area19 = "有效距離:\r";
char *HelpTitle8 = "說明";
char *QuestTitle8 = "任務";
char *IncreWeaponAttack_RateName = "武器命中率增加:\r";
char *AddMaxDamage = "最大傷害力增加:\r";
char *LinkCoreName = "移動到公會會員\r";
char *DesLinkCore = "對象:";
