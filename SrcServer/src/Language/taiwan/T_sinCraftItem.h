

#define   SIN_ADD_FIRE			0x00000001	
#define   SIN_ADD_ICE			0x00000002	
#define   SIN_ADD_LIGHTNING		0x00000004	
#define   SIN_ADD_POISON			0x00000008	
#define   SIN_ADD_BIO			0x00000010	
#define   SIN_ADD_CRITICAL			0x00000020	
#define   SIN_ADD_ATTACK_RATE		0x00000040	
#define   SIN_ADD_DAMAGE_MIN		0x00000080	
#define   SIN_ADD_DAMAGE_MAX		0x00000100	
#define   SIN_ADD_ATTACK_SPEED		0x00000200	
#define   SIN_ADD_ABSORB			0x00000400	
#define   SIN_ADD_DEFENCE			0x00000800	
#define   SIN_ADD_BLOCK_RATE		0x00001000	
#define   SIN_ADD_MOVE_SPEED		0x00002000	
#define   SIN_ADD_LIFE			0x00004000	
#define   SIN_ADD_MANA			0x00008000	
#define   SIN_ADD_STAMINA			0x00010000	
#define   SIN_ADD_LIFEREGEN		0x00020000 	 
#define   SIN_ADD_MANAREGEN		0x00040000 	 
#define   SIN_ADD_STAMINAREGEN		0x00080000	  

#define   SIN_ADD_NUM				1
#define   SIN_ADD_PERCENT			2
















{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{5,0,0,0,0,0,0,0,0},
{SIN_ADD_BIO,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"體屬性 +5\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,5,0,0,0,0,0,0,0},
{SIN_ADD_POISON,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"毒屬性 +5\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,5,0,0,0,0,0,0},
{SIN_ADD_ICE,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"冰屬性 +5\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,0,5,0,0,0,0,0},
{SIN_ADD_FIRE,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"火屬性 +5\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,0,0,5,0,0,0,0},
{SIN_ADD_LIGHTNING,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"雷屬性 +5\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,0,0,0,1,0,0,0},
{SIN_ADD_CRITICAL,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"耐久度 +1%\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,0,0,0,0,1,0,0},
{SIN_ADD_ATTACK_RATE,0,0,0,0,0,0,0},
{50,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"命中率 +40\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,0,0,0,0,0,1,0},
{SIN_ADD_STAMINA,0,0,0,0,0,0,0},
{20,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"精力值 +20\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,0,0,0,0,0,0,1},
{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,0,0},
{2,2,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"最小攻擊力 +2\r最大攻擊力 +2\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{1,1,0,0,0,0,0,0,0},
{SIN_ADD_ATTACK_RATE,0,0,0,0,0,0,0},
{20,0,0,0,0,0,0,0},
{SIN_ADD_PERCENT,0,0,0,0,0,0,0},
"命中率 +20%\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{3,3,0,0,0,0,0,0,0},
{SIN_ADD_ATTACK_RATE,0,0,0,0,0,0,0},
{40,0,0,0,0,0,0,0},
{SIN_ADD_PERCENT,0,0,0,0,0,0,0},
"命中率 +40%\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{1,0,2,0,0,0,0,0,0},
{SIN_ADD_ATTACK_RATE,SIN_ADD_DAMAGE_MIN,0,0,0,0,0,0},
{10,1,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"命中率 +10\r最小攻擊力 +1\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{1,0,0,2,0,0,0,0,0},
{SIN_ADD_ATTACK_RATE,SIN_ADD_DAMAGE_MAX,0,0,0,0,0,0},
{10,1,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"命中率 +10\r最大攻擊力 +1\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{2,0,2,2,0,0,0,0,0},
{SIN_ADD_ATTACK_RATE,SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,0},
{20,1,1,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"命中率 +20\r最小攻擊力 +1\r最大攻擊力 +1\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{1,0,0,1,1,0,0,0,0},
{SIN_ADD_ATTACK_RATE,0,0,0,0,0,0,0},
{100,0,0,0,0,0,0,0},
{SIN_ADD_PERCENT,0,0,0,0,0,0,0},
"命中率 +100%\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,1,2,0,0,0,0,0,0},
{SIN_ADD_DAMAGE_MIN,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"最小攻擊力 +1\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,1,0,2,0,0,0,0,0},
{SIN_ADD_DAMAGE_MAX,0,0,0,0,0,0,0},
{2,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"最大攻擊力 +2\r"},



{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,1,2,2,0,1,0,0,0},
{SIN_ADD_CRITICAL,SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,0},
{2,1,1,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"耐久度 +2%\r最小攻擊力 +1\r最大攻擊力 +1\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,1,0,4,4,0,0,0,0},
{SIN_ADD_DAMAGE_MAX,0,0,0,0,0,0,0},
{4,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"最大攻擊力 +4\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{1,1,0,4,4,0,0,0,0},
{SIN_ADD_ATTACK_RATE,SIN_ADD_DAMAGE_MAX,0,0,0,0,0,0},
{10,4,0,0,0,0,0,0},
{SIN_ADD_PERCENT,SIN_ADD_NUM,0,0,0,0,0,0},
"命中率 +10%\r最大攻擊力 +4\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,1,2,4,1,0,0,0,0},
{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,0,0},
{1,3,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"最小攻擊力 +1\r最大攻擊力 +3\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,1,4,2,1,0,0,0,0},
{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,0,0},
{2,2,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"最小攻擊力 +2\r最大攻擊力 +2\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,2,2,1,4,0,0,0},
{SIN_ADD_CRITICAL,SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,0},
{4,2,2,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"耐久度 +4%\r最小攻擊力 +2\r最大攻擊力 +2\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{1,1,2,4,1,0,0,0,0},
{SIN_ADD_ATTACK_RATE,SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,0},
{10,1,4,0,0,0,0,0},
{SIN_ADD_PERCENT,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"命中率 +10%\r最小攻擊力 +1\r最大攻擊力 +4\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,1,3,3,0,0,1,0,0},
{SIN_ADD_ATTACK_RATE,SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,0},
{40,3,3,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"命中率+40\r最小攻擊力 +3\r最大攻擊力 +3\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,0,0,5,5,2,0,0},
{SIN_ADD_CRITICAL,SIN_ADD_ATTACK_RATE,SIN_ADD_DAMAGE_MAX,0,0,0,0,0},
{4,60,5,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_PERCENT,SIN_ADD_NUM,0,0,0,0,0},
"耐久度 +4%\r命中率 +60%\r最大攻擊力 +5\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,3,3,2,2,2,0,0},
{SIN_ADD_ATTACK_RATE,SIN_ADD_CRITICAL,SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0},
{80,2,3,3,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
"命中率 +80\r耐久度 +2%\r最小攻擊力 +3\r最大攻擊力 +3\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,4,4,0,2,0,2,0},
{SIN_ADD_CRITICAL,SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_MANA,0,0,0,0},
{4,4,4,20,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
"耐久度 +4%\r最小攻擊力 +4\r最大攻擊力 +4\r魔法值 +20\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,2,2,0,0,1,4,0},
{SIN_ADD_ATTACK_RATE,SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_LIFE,0,0,0,0},
{60,4,4,20,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
"命中率 +60\r最小攻擊力 +4\r最大攻擊力 +4\r生命 +20\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,0,2,1,4,0,0,2},
{SIN_ADD_CRITICAL,SIN_ADD_DAMAGE_MAX,0,0,0,0,0,0},
{4,15,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_PERCENT,SIN_ADD_PERCENT,0,0,0,0,0},
"耐久度 +4%\r最大攻擊力 +15%\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,1,1,3,0,0,0,2},
{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,0,0},
{6,6,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"最小攻擊力 +6\r最大攻擊力 +6\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,1,1,4,0,1,0,4},
{SIN_ADD_ATTACK_RATE,SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,0},
{160,4,4,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"命中率 +160\r最小攻擊力 +4\r最大攻擊力 +4\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,0,0,0,3,0,5,2},
{SIN_ADD_CRITICAL,SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_LIFE,0,0,0,0},
{3,9,9,25,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_PERCENT,SIN_ADD_PERCENT,SIN_ADD_NUM,0,0,0,0},
"耐久度 +3%\r最小攻擊力 +9%\r最大攻擊力 +9%\r生命 +25\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,0,0,0,0,4,4,4},
{SIN_ADD_ATTACK_RATE,SIN_ADD_DAMAGE_MAX,SIN_ADD_STAMINA,0,0,0,0,0},
{80,12,40,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"命中率 +80\r最大攻擊力 +12\r耐力 +40\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,0,0,5,0,0,2,2},
{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_MANA,0,0,0,0,0},
{7,7,10,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"最小攻擊力 +7\r最大攻擊力 +7\r魔法值+10\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{1,1,1,1,1,1,1,1,1},
{SIN_ADD_ATTACK_RATE,SIN_ADD_DAMAGE_MAX,SIN_ADD_MANA,0,0,0,0,0},
{50,5,10,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
"命中率 +50\r最大攻擊力 +5\r魔法值 +10\r"},




{{sinDA1,sinDA2,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0,0},
{SIN_ADD_BIO,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"魔防禦 +5\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,5,0,0,0,0,0,0,0},
{SIN_ADD_POISON,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"毒防禦 +5\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,5,0,0,0,0,0,0},
{SIN_ADD_ICE,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"冰防禦 +5\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,5,0,0,0,0,0},
{SIN_ADD_FIRE,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"火防禦 +5\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,0,5,0,0,0,0},
{SIN_ADD_LIGHTNING,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"雷防禦 +5\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,0,0,1,0,0,0},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{20,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"防禦 +20\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,0,0,0,1,0,0},
{SIN_ADD_ABSORB,0,0,0,0,0,0,0},
{0.6f,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"額防 +0.6\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0},
{SIN_ADD_STAMINA,0,0,0,0,0,0,0},
{10,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"耐力 +10\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{40,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"防禦 +40\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{2,2,0,0,0,0,0,0,0},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{10,0,0,0,0,0,0,0},
{SIN_ADD_PERCENT,0,0,0,0,0,0,0},
"防禦 +10%\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{1,0,2,0,0,0,0,0,0},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{20,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"防禦 +20\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,2,1,1,0,0,0,0,0},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{15,0,0,0,0,0,0,0},
{SIN_ADD_PERCENT,0,0,0,0,0,0,0},
"防禦 +15%\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,3,0,3,0,0,0,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0,0},
{30,0.2f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"防禦 +30\r額防 +0.2\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,1,0,2,1,1,0,0,0},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{40,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"防禦 +40\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,1,0,0,2,2,0,0,0},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{45,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"防禦 +45\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,1,0,4,0,0,1,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0,0},
{10,0.6f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"防禦 +10\r額防 +0.6\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,1,0,0,0,0,2,0,0},
{SIN_ADD_ABSORB,0,0,0,0,0,0,0},
{1.2f,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"額防 +1.2\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,0,1,0,3,0,0},
{SIN_ADD_ABSORB,0,0,0,0,0,0,0},
{1.8f,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"額防 +1.8\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,1,0,0,1,1,4,0,0},
{SIN_ADD_ABSORB,0,0,0,0,0,0,0},
{2.4f,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"額防 +2.4\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,3,0,3,0,3,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0,0},
{30,1.8f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"防禦 +30\r額防 +1.8\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,0,0,3,3,0,0},
{SIN_ADD_ABSORB,0,0,0,0,0,0,0},
{30,0,0,0,0,0,0,0},
{SIN_ADD_PERCENT,0,0,0,0,0,0,0},
"額防 +30%\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,4,0,2,2,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0,0},
{40,1.2f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"防禦 +40\r額防 +1.2\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,0,1,0,0,4,0},
{SIN_ADD_LIFE,0,0,0,0,0,0,0},
{40,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"生命 +40\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,1,1,2,0,3,0},
{SIN_ADD_DEFENCE,SIN_ADD_MANA,0,0,0,0,0,0},
{40,30,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"防禦 +40\r魔法 +30\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,0,1,0,4,2,0},
{SIN_ADD_ABSORB,SIN_ADD_LIFE,0,0,0,0,0,0},
{2.4f,20,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"額防 +2.4\r生命 +20\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,0,1,0,0,4,1},
{SIN_ADD_STAMINA,SIN_ADD_MANA,SIN_ADD_LIFE,0,0,0,0,0},
{40,20,10,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"精力 +40\r魔法 +20\r生命 +10\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,0,4,2,0,0,1},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{80,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"防禦 +80\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,0,2,0,2,0,1},
{SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_STAMINA,0,0,0,0,0},
{40,1.2f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"防禦 +40\r額防 +1.2\r精力 +20\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,0,0,3,0,2,1},
{SIN_ADD_DEFENCE,SIN_ADD_MANA,0,0,0,0,0,0},
{60,20,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"防禦 +60\r魔法 +20\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,0,0,0,5,0,1},
{SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0,0},
{50,3.0f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"防禦 +50\r額防 +3.0\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,0,0,1,0,4,2},
{SIN_ADD_DEFENCE,SIN_ADD_LIFE,0,0,0,0,0,0},
{100,20,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"防禦 +100\r生命 +20\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{2,2,2,2,2,2,0,0,0},
{SIN_ADD_BIO,SIN_ADD_FIRE,SIN_ADD_ICE,SIN_ADD_LIGHTNING,SIN_ADD_POISON,0,0,0},
{5,5,5,5,5,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0},
"魔防禦 +5\r毒防禦 +5\r冰防禦 +5\r火防禦 +5\r雷防禦 +5\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1},
{SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0,0},
{10,1.0f,0,0,0,0,0,0},
{SIN_ADD_PERCENT,SIN_ADD_NUM,0,0,0,0,0,0},
"防禦 +10%\r額防 1.0\r"},





{{sinDS1,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0,0},
{SIN_ADD_BIO,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"魔防禦 +5\r"},


{{sinDS1,0,0,0,0,0,0,0},
{0,5,0,0,0,0,0,0,0},
{SIN_ADD_POISON,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"毒防禦 +5\r"},


{{sinDS1,0,0,0,0,0,0,0},
{0,0,5,0,0,0,0,0,0},
{SIN_ADD_ICE,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"冰防禦 +5\r"},


{{sinDS1,0,0,0,0,0,0,0},
{0,0,0,5,0,0,0,0,0},
{SIN_ADD_FIRE,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"火防禦 +5\r"},


{{sinDS1,0,0,0,0,0,0,0},
{0,0,0,0,5,0,0,0,0},
{SIN_ADD_LIGHTNING,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"雷防禦 +5\r"},


{{sinDS1,0,0,0,0,0,0,0},
{0,0,0,0,0,1,0,0,0},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{10,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"防禦 +10\r"},


{{sinDS1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,0,0},
{SIN_ADD_BLOCK_RATE,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"格擋率 +1\r"},


{{sinDS1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0},
{SIN_ADD_LIFE,0,0,0,0,0,0,0},
{10,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"生命 +10\r"},


{{sinDS1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{20,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"防禦 +20\r"},


{{sinDS1,0,0,0,0,0,0,0},
{2,0,1,0,0,0,0,0,0},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{10,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"防禦 +10\r"},


{{sinDS1,0,0,0,0,0,0,0},
{0,2,2,1,0,0,0,0,0},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{10,0,0,0,0,0,0,0},
{SIN_ADD_PERCENT,0,0,0,0,0,0,0},
"防禦 +10%\r"},


{{sinDS1,0,0,0,0,0,0,0},
{0,3,1,0,1,0,0,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0,0},
{15,0.3f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"防禦 +15\r額防 +0.3\r"},


{{sinDS1,0,0,0,0,0,0,0},
{0,0,2,0,2,0,0,0,0},
{SIN_ADD_ABSORB,0,0,0,0,0,0,0},
{0.3f,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"額防 +0.3\r"},


{{sinDS1,0,0,0,0,0,0,0},
{0,1,0,0,1,2,0,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0,0},
{10,0.6f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"防禦 +10\r額防 +0.6\r"},


{{sinDS1,0,0,0,0,0,0,0},
{0,2,2,2,1,1,0,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0,0},
{20,0.3f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"防禦 +20\r額防 +0.3\r"},


{{sinDS1,0,0,0,0,0,0,0},
{0,0,1,0,2,0,1,0,0},
{SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0,0,0},
{0.6f,2,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"額防 +0.6\r格擋率 2%\r"},


{{sinDS1,0,0,0,0,0,0,0},
{0,0,3,0,0,3,1,0,0},
{SIN_ADD_BLOCK_RATE,0,0,0,0,0,0,0},
{3,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"格擋率 +3%\r"},


{{sinDS1,0,0,0,0,0,0,0},
{0,4,4,0,0,0,1,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_BLOCK_RATE,0,0,0,0,0,0},
{40,1,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"防禦 +40\r格擋率 +1%\r"},


{{sinDS1,0,0,0,0,0,0,0},
{0,2,1,1,0,1,2,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_BLOCK_RATE,0,0,0,0,0,0},
{20,2,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"防禦 +20\r格擋率 +2%\r"},


{{sinDS1,0,0,0,0,0,0,0},
{4,1,0,0,0,1,0,2,0},
{SIN_ADD_DEFENCE,SIN_ADD_MANA,0,0,0,0,0,0},
{40,10,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"防禦 +40\r魔法 +10\r"},


{{sinDS1,0,0,0,0,0,0,0},
{0,0,0,0,0,2,1,2,0},
{SIN_ADD_BLOCK_RATE,SIN_ADD_LIFE,0,0,0,0,0,0},
{2,20,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"格擋率 +2%\r生命 +20\r"},


{{sinDS1,0,0,0,0,0,0,0},
{0,0,0,0,5,0,0,2,0},
{SIN_ADD_ABSORB,SIN_ADD_STAMINA,0,0,0,0,0,0},
{1.0f,50,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"額防 +1.0\r精力 +50\r"},


{{sinDS1,0,0,0,0,0,0,0},
{0,0,0,0,3,1,0,2,0},
{SIN_ADD_ABSORB,SIN_ADD_LIFE,0,0,0,0,0,0},
{0.6f,40,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"額防 +0.6\r生命 +40\r"},


{{sinDS1,0,0,0,0,0,0,0},
{0,0,0,0,0,5,0,0,1},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{50,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"防禦 +50\r"},


{{sinDS1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,2,2},
{SIN_ADD_DEFENCE,SIN_ADD_BLOCK_RATE,SIN_ADD_LIFE,0,0,0,0,0},
{40,2,20,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"防禦 +40\r格擋率 +2%\r生命 +20\r"},


{{sinDS1,0,0,0,0,0,0,0},
{2,2,2,2,2,2,0,0,0},
{SIN_ADD_BIO,SIN_ADD_POISON,SIN_ADD_LIGHTNING,SIN_ADD_FIRE,SIN_ADD_ICE,0,0,0},
{5,5,5,5,5,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0},
"魔防禦 +5\r毒防禦 +5\r冰防禦 +5\r火防禦 +5\r雷防禦 +5\r"},


{{sinDS1,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1},
{SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0,0},
{20,0.5f,0,0,0,0,0,0},
{SIN_ADD_PERCENT,SIN_ADD_NUM,0,0,0,0,0,0},
"防禦 +20%\r額防 +0.5\r"},



{{sinOM1,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0,0},
{SIN_ADD_BIO,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"體屬性 +5\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,5,0,0,0,0,0,0,0},
{SIN_ADD_POISON,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"毒屬性 +5\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,5,0,0,0,0,0,0},
{SIN_ADD_ICE,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"冰屬性 +5\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,0,5,0,0,0,0,0},
{SIN_ADD_FIRE,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"火屬性 +5\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,0,0,5,0,0,0,0},
{SIN_ADD_LIGHTNING,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"雷屬性 +5\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,0,0,0,1,0,0,0},
{SIN_ADD_MANAREGEN,0,0,0,0,0,0,0},
{0.3f,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"魔法值再生 +0.3\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,0,0},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{10,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"防禦力 +10\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0},
{SIN_ADD_MANA,0,0,0,0,0,0,0},
{20,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"魔法值 +20\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1},
{SIN_ADD_ABSORB,0,0,0,0,0,0,0},
{1.0f,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"額外防禦力 +1.0\r"},

{{sinOM1,0,0,0,0,0,0,0},
{2,0,1,0,0,0,0,0,0},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{10,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"防禦力 +10\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,2,2,1,0,0,0,0,0},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{10,0,0,0,0,0,0,0},
{SIN_ADD_PERCENT,0,0,0,0,0,0,0},
"防禦力 +10%\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,3,1,0,2,0,0,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0,0},
{15,0.4f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"防禦力 +15\r額外防禦力 +0.4\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,3,0,3,0,0,0,0},
{SIN_ADD_ABSORB,0,0,0,0,0,0,0},
{0.6f,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"額外防禦力 +0.6\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,1,0,0,2,2,0,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_MANAREGEN,0,0,0,0,0,0},
{10,0.4f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"防禦力 +10\r魔法值再生 +0.4\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,2,2,2,2,1,0,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_MANAREGEN,0,0,0,0,0,0},
{20,0.2f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"防禦力 +20\r魔法值再生 +0.2\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,1,0,4,0,1,0,0},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{40,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"防禦力 +40\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,3,0,0,3,1,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_MANAREGEN,0,0,0,0,0,0},
{10,0.6f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"防禦力 +10\r魔法值再生 +0.6\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,4,4,0,0,0,1,0,0},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{50,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"防禦力 +50\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,2,1,1,0,1,2,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_MANAREGEN,0,0,0,0,0,0},
{40,0.4f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"防禦力 +40\r魔法值再生 +0.4\r"},

{{sinOM1,0,0,0,0,0,0,0},
{4,1,0,0,0,2,0,2,0},
{SIN_ADD_MANAREGEN,SIN_ADD_MANA,0,0,0,0,0,0},
{0.4f,40,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"魔法值再生 +0.4\r魔法值 +40\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,0,0,0,2,1,2,0},
{SIN_ADD_DEFENCE,SIN_ADD_MANAREGEN,SIN_ADD_STAMINA,0,0,0,0,0},
{10,0.4f,20,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"防禦力 +10\r魔法值再生 +0.4\r精力值 +20\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,0,2,5,0,0,2,0},
{SIN_ADD_MANA,SIN_ADD_STAMINA,0,0,0,0,0,0},
{50,50,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"魔法值 +50\r精力值 +50\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,0,0,3,2,0,2,0},
{SIN_ADD_ABSORB,SIN_ADD_MANAREGEN,SIN_ADD_LIFE,0,0,0,0,0},
{0.6f,0.6f,20,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"額外防禦力 +0.6\r魔法值再生 +0.6\r生命值 +20\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,0,0,0,5,0,0,1},
{SIN_ADD_ABSORB,SIN_ADD_MANAREGEN,0,0,0,0,0,0},
{1.0f,1.0f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"額外防禦力 +1.0\r魔法值再生 +1.0\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,2,2,2},
{SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_MANA,0,0,0,0,0},
{20,1.0f,40,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"防禦力 +20\r額外防禦力 +1.0\r魔法值 +40\r"},

{{sinOM1,0,0,0,0,0,0,0},
{2,2,2,2,2,2,0,0,0},
{SIN_ADD_BIO,SIN_ADD_POISON,SIN_ADD_ICE,SIN_ADD_FIRE,SIN_ADD_LIGHTNING,0,0,0},
{5,5,5,5,5,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0},
"體屬性 +5\r毒屬性 +5\r冰屬性 +5\r火屬性 +5\r雷屬性 +5\r"},

{{sinOM1,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1},
{SIN_ADD_DEFENCE,SIN_ADD_ABSORB,SIN_ADD_MANAREGEN,0,0,0,0,0},
{20,1.0f,0.5f,0,0,0,0,0},
{SIN_ADD_PERCENT,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"防禦力 +20%\r額外防禦力 +1.0\r魔法值再生 +0.5\r"},
