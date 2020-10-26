

#define   SIN_ADD_FIRE				0x00000001	
#define   SIN_ADD_ICE				0x00000002	
#define   SIN_ADD_LIGHTNING			0x00000004	
#define   SIN_ADD_POISON			0x00000008	
#define   SIN_ADD_BIO				0x00000010	
#define   SIN_ADD_CRITICAL			0x00000020	
#define   SIN_ADD_ATTACK_RATE		0x00000040	
#define   SIN_ADD_DAMAGE_MIN		0x00000080	
#define   SIN_ADD_DAMAGE_MAX		0x00000100	
#define   SIN_ADD_ATTACK_SPEED		0x00000200	
#define   SIN_ADD_ABSORB			0x00000400	
#define   SIN_ADD_DEFENCE			0x00000800	
#define   SIN_ADD_BLOCK_RATE		0x00001000	
#define   SIN_ADD_MOVE_SPEED		0x00002000	
#define   SIN_ADD_LIFE				0x00004000	
#define   SIN_ADD_MANA				0x00008000	
#define   SIN_ADD_STAMINA			0x00010000	
#define   SIN_ADD_LIFEREGEN			0x00020000  
#define   SIN_ADD_MANAREGEN			0x00040000  
#define   SIN_ADD_STAMINAREGEN		0x00080000  

#define   SIN_ADD_NUM				1
#define   SIN_ADD_PERCENT			2














{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{5,0,0,0,0,0,0,0,0},
{SIN_ADD_BIO,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ê∂ëÆê´ +5\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,5,0,0,0,0,0,0,0},
{SIN_ADD_POISON,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ì≈ëÆê´ +5\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,5,0,0,0,0,0,0},
{SIN_ADD_ICE,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ïXëÆê´ +5\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,0,5,0,0,0,0,0},
{SIN_ADD_FIRE,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"âŒëÆê´ +5\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,0,0,5,0,0,0,0},
{SIN_ADD_LIGHTNING,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"óãëÆê´ +5\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,0,0,0,1,0,0,0},
{SIN_ADD_CRITICAL,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ïKéEó¶ +1%\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,0,0,0,0,1,0,0},
{SIN_ADD_ATTACK_RATE,0,0,0,0,0,0,0},
{50,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ñΩíÜóÕ +50\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,0,0,0,0,0,1,0},
{SIN_ADD_STAMINA,0,0,0,0,0,0,0},
{20,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ëÃóÕ +20\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{1,1,0,0,0,0,0,0,0},
{SIN_ADD_ATTACK_RATE,0,0,0,0,0,0,0},
{20,0,0,0,0,0,0,0},
{SIN_ADD_PERCENT,0,0,0,0,0,0,0},
"ñΩíÜóÕ +20%\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{3,3,0,0,0,0,0,0,0},
{SIN_ADD_ATTACK_RATE,0,0,0,0,0,0,0},
{40,0,0,0,0,0,0,0},
{SIN_ADD_PERCENT,0,0,0,0,0,0,0},
"ñΩíÜóÕ +40%\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{1,0,2,0,0,0,0,0,0},
{SIN_ADD_ATTACK_RATE,SIN_ADD_DAMAGE_MIN,0,0,0,0,0,0},
{10,1,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ñΩíÜóÕ +10\rç≈è¨çUåÇóÕ +1\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{1,0,0,2,0,0,0,0,0},
{SIN_ADD_ATTACK_RATE,SIN_ADD_DAMAGE_MAX,0,0,0,0,0,0},
{10,1,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ñΩíÜóÕ +10\rç≈ëÂçUåÇóÕ +1\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{2,0,2,2,0,0,0,0,0},
{SIN_ADD_ATTACK_RATE,SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,0},
{20,1,1,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"ñΩíÜóÕ +20\rç≈è¨çUåÇóÕ +1\rç≈ëÂçUåÇóÕ +1\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{1,0,0,1,1,0,0,0,0},
{SIN_ADD_ATTACK_RATE,0,0,0,0,0,0,0},
{100,0,0,0,0,0,0,0},
{SIN_ADD_PERCENT,0,0,0,0,0,0,0},
"ñΩíÜóÕ +100%\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,1,2,0,0,0,0,0,0},
{SIN_ADD_DAMAGE_MIN,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ç≈è¨çUåÇóÕ +1\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,1,0,2,0,0,0,0,0},
{SIN_ADD_DAMAGE_MAX,0,0,0,0,0,0,0},
{2,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ç≈ëÂçUåÇóÕ +2\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,1,2,2,0,1,0,0,0},
{SIN_ADD_CRITICAL,SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,0},
{2,1,1,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"ïKéEó¶ +2%\rç≈è¨çUåÇóÕ +1\rç≈ëÂçUåÇóÕ +1\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,1,0,4,4,0,0,0,0},
{SIN_ADD_DAMAGE_MAX,0,0,0,0,0,0,0},
{4,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ç≈ëÂçUåÇóÕ +4\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{1,1,0,4,4,0,0,0,0},
{SIN_ADD_ATTACK_RATE,SIN_ADD_DAMAGE_MAX,0,0,0,0,0,0},
{10,4,0,0,0,0,0,0},
{SIN_ADD_PERCENT,SIN_ADD_NUM,0,0,0,0,0,0},
"ñΩíÜóÕ +10%\rç≈ëÂçUåÇóÕ +4\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,1,2,4,1,0,0,0,0},
{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,0,0},
{1,3,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ç≈è¨çUåÇóÕ +1\rç≈ëÂçUåÇóÕ +3\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,1,4,2,1,0,0,0,0},
{SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,0,0},
{2,2,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ç≈è¨çUåÇóÕ +2\rç≈ëÂçUåÇóÕ +2\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,2,2,1,3,0,0,0},
{SIN_ADD_CRITICAL,SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,0},
{4,3,3,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"ïKéEó¶ +4%\rç≈è¨çUåÇóÕ +3\rç≈ëÂçUåÇóÕ +3\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{1,1,2,4,1,0,0,0,0},
{SIN_ADD_ATTACK_RATE,SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,0},
{10,1,4,0,0,0,0,0},
{SIN_ADD_PERCENT,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"ñΩíÜóÕ +10%\rç≈è¨çUåÇóÕ +1\rç≈ëÂçUåÇóÕ +4\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,1,3,5,0,0,1,0,0},
{SIN_ADD_ATTACK_RATE,SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,0},
{40,3,5,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"ñΩíÜóÕ +40\rç≈è¨çUåÇóÕ +3\rç≈ëÂçUåÇóÕ +5\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,0,0,5,3,2,0,0},
{SIN_ADD_CRITICAL,SIN_ADD_ATTACK_RATE,SIN_ADD_DAMAGE_MAX,0,0,0,0,0},
{4,60,6,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_PERCENT,SIN_ADD_NUM,0,0,0,0,0},
"ïKéEó¶ +4%\rñΩíÜóÕ +60%\rç≈ëÂçUåÇóÕ +6\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,2,2,2,2,2,0,0},
{SIN_ADD_ATTACK_RATE,SIN_ADD_CRITICAL,SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0},
{80,2,4,4,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
"ñΩíÜóÕ +80\rïKéEó¶ +2%\rç≈è¨çUåÇóÕ +4\rç≈ëÂçUåÇóÕ +4\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,3,3,0,2,0,2,0},
{SIN_ADD_CRITICAL,SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_MANA,0,0,0,0},
{4,6,6,20,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
"ïKéEó¶ +4%\rç≈è¨çUåÇóÕ +6\rç≈ëÂçUåÇóÕ +6\rãCóÕ +20\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,2,2,0,0,1,3,0},
{SIN_ADD_ATTACK_RATE,SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,SIN_ADD_LIFE,0,0,0,0},
{60,6,6,20,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
"ñΩíÜóÕ +60\rç≈è¨çUåÇóÕ +6\rç≈ëÂçUåÇóÕ +6\rê∂ñΩóÕ +20\r"},




{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,0,0,0,0,0,0,1},
{SIN_ADD_CRITICAL,0,0,0,0,0,0,0},
{4,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ïKéEó¶ +4%\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,0,2,0,0,2,3,3},
{SIN_ADD_ATTACK_RATE,SIN_ADD_CRITICAL,SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,},
{100,3,6,6,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
"ñΩíÜóÕ +100\rïKéEó¶ +3%\rç≈è¨çUåÇóÕ +6\rç≈ëÂçUåÇóÕ +6\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,0,1,0,4,0,2,4},
{SIN_ADD_ATTACK_RATE,SIN_ADD_LIFE,SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,},
{80,30,7,7,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
"ñΩíÜóÕ +80\rê∂ñΩóÕ +30\rç≈è¨çUåÇóÕ +7\rç≈ëÂçUåÇóÕ +7\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,0,0,2,1,2,3,2},
{SIN_ADD_CRITICAL,SIN_ADD_MANA,SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,},
{5,30,7,7,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
"ïKéEó¶ +5%\rãCóÕ +30\rç≈è¨çUåÇóÕ +7\rç≈ëÂçUåÇóÕ +7\r"},


{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,0,0,0,0,5,4,3},
{SIN_ADD_CRITICAL,SIN_ADD_MANA,SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,},
{4,50,7,7,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
"ïKéEó¶ +4%\rãCóÕ +50\rç≈è¨çUåÇóÕ +7\rç≈ëÂçUåÇóÕ +7\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,0,0,0,0,0,5,5},
{SIN_ADD_CRITICAL,SIN_ADD_LIFE,SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,},
{4,50,7,7,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
"ïKéEó¶ +4%\rê∂ñΩóÕ +50\rç≈è¨çUåÇóÕ +7\rç≈ëÂçUåÇóÕ +7\r"},

{{sinWA1,sinWC1,sinWH1,sinWM1,sinWP1,sinWS1,sinWS2,sinWT1},
{0,0,0,0,0,1,1,5,5},
{SIN_ADD_ATTACK_RATE,SIN_ADD_CRITICAL,SIN_ADD_DAMAGE_MIN,SIN_ADD_DAMAGE_MAX,0,0,0,0,},
{80,5,7,7,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0},
"ñΩíÜóÕ +80\rïKéEó¶ +5%\rç≈è¨çUåÇóÕ +7\rç≈ëÂçUåÇóÕ +7\r"},





{{sinDA1,sinDA2,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0,0},
{SIN_ADD_BIO,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ê∂ëÆê´ +5\r"},

{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,5,0,0,0,0,0,0,0},
{SIN_ADD_POISON,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ì≈ëÆê´ +5\r"},

{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,5,0,0,0,0,0,0},
{SIN_ADD_ICE,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ïXëÆê´ +5\r"},

{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,5,0,0,0,0,0},
{SIN_ADD_FIRE,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"âŒëÆê´ +5\r"},

{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,0,5,0,0,0,0},
{SIN_ADD_LIGHTNING,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"óãëÆê´ +5\r"},

{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,0,0,1,0,0,0},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{20,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ñhå‰óÕ +20\r"},

{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,0,0,0,1,0,0},
{SIN_ADD_ABSORB,0,0,0,0,0,0,0},
{0.6f,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ãzé˚óÕ +0.6\r"},

{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0},
{SIN_ADD_STAMINA,0,0,0,0,0,0,0},
{10,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ëÃóÕ +10\r"},

{{sinDA1,sinDA2,0,0,0,0,0,0},
{2,2,0,0,0,0,0,0,0},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{10,0,0,0,0,0,0,0},
{SIN_ADD_PERCENT,0,0,0,0,0,0,0},
"ñhå‰óÕ +10%\r"},

{{sinDA1,sinDA2,0,0,0,0,0,0},
{1,0,2,0,0,0,0,0,0},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{20,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ñhå‰óÕ +20\r"},

{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,2,1,1,0,0,0,0,0},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{15,0,0,0,0,0,0,0},
{SIN_ADD_PERCENT,0,0,0,0,0,0,0},
"ñhå‰óÕ +15%\r"},

{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,3,0,3,0,0,0,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0,0},
{30,0.6f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ñhå‰óÕ +30\rãzé˚óÕ +0.6\r"},

{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,1,0,2,1,1,0,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0,0},
{40,0.4f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ñhå‰óÕ +40\rãzé˚óÕ +0.4\r"},

{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,1,0,0,2,5,0,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0,0},
{45,1.0f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ñhå‰óÕ +45\rãzé˚óÕ +1.0\r"},

{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,1,0,4,0,0,1,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0,0},
{10,1.5f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ñhå‰óÕ +10\rãzé˚óÕ +1.5\r"},

{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,1,0,0,0,0,2,0,0},
{SIN_ADD_ABSORB,0,0,0,0,0,0,0},
{2.0f,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ãzé˚óÕ +2.0\r"},

{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,0,1,2,2,0,0},
{SIN_ADD_ABSORB,0,0,0,0,0,0,0},
{3.0f,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ãzé˚óÕ +3.0\r"},

{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,1,0,0,1,1,3,0,0},
{SIN_ADD_ABSORB,0,0,0,0,0,0,0},
{3.5f,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ãzé˚óÕ +3.5\r"},

{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,4,0,4,0,3,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0,0},
{40,3.0f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ñhå‰óÕ +40\rãzé˚óÕ +3.0\r"},

{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,0,0,3,3,0,0},
{SIN_ADD_ABSORB,0,0,0,0,0,0,0},
{30,0,0,0,0,0,0,0},
{SIN_ADD_PERCENT,0,0,0,0,0,0,0},
"ãzé˚óÕ +30%\r"},

{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,2,0,2,2,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0,0},
{20,3.4f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ñhå‰óÕ +20\rãzé˚óÕ +3.4\r"},

{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,0,1,0,0,4,0},
{SIN_ADD_LIFE,0,0,0,0,0,0,0},
{40,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ê∂ñΩóÕ +40\r"},

{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,1,1,2,0,3,0},
{SIN_ADD_DEFENCE,SIN_ADD_MANA,0,0,0,0,0,0},
{40,30,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ñhå‰óÕ +40\rãCóÕ +30\r"},

{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,0,1,0,3,2,0},
{SIN_ADD_ABSORB,SIN_ADD_LIFE,0,0,0,0,0,0},
{3.5f,20,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ãzé˚óÕ +3.5\rê∂ñΩóÕ +20\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{2,2,2,2,2,2,0,0,0},
{SIN_ADD_BIO,SIN_ADD_FIRE,SIN_ADD_ICE,SIN_ADD_LIGHTNING,SIN_ADD_POISON,0,0,0},
{5,5,5,5,5,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0},
"ê∂ñΩóÕ +5\rì≈ëÆê´ +5\rïXëÆê´ +5\râŒëÆê´ +5\róãëÆê´ +5\r"},




{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{50,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ñhå‰óÕ +50\r"},

{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,0,0,0,2,2,2},
{SIN_ADD_LIFE,0,0,0,0,0,0,0},
{50,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ê∂ñΩóÕ +50\r"},

{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,2,0,2,0,3,3},
{SIN_ADD_DEFENCE,SIN_ADD_MANA,0,0,0,0,0,0},
{50,40,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ñhå‰óÕ +50\rãCóÕ +40\r"},

{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,0,3,0,3,1,3},
{SIN_ADD_ABSORB,SIN_ADD_LIFE,0,0,0,0,0,0},
{4.0f,25,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ãzé˚óÕ +4.0\rê∂ñΩóÕ +25\r"},


{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,0,0,0,1,2,5},
{SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0,0},
{50,4.0f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ñhå‰óÕ +50\rãzé˚óÕ +4.0\r"},

{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,0,0,0,0,5,5},
{SIN_ADD_DEFENCE,SIN_ADD_MANA,0,0,0,0,0,0},
{60,50,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ñhå‰óÕ +60\rãCóÕ +50\r"},

{{sinDA1,sinDA2,0,0,0,0,0,0},
{0,0,0,0,0,1,5,1,5},
{SIN_ADD_ABSORB,SIN_ADD_LIFE,0,0,0,0,0,0},
{4.0f,40,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ãzé˚óÕ +4.0\rê∂ñΩóÕ +40\r"},



{{sinDS1,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0,0},
{SIN_ADD_BIO,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ê∂ëÆê´ +5\r"},

{{sinDS1,0,0,0,0,0,0,0},
{0,5,0,0,0,0,0,0,0},
{SIN_ADD_POISON,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ì≈ëÆê´ +5\r"},

{{sinDS1,0,0,0,0,0,0,0},
{0,0,5,0,0,0,0,0,0},
{SIN_ADD_ICE,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ïXëÆê´ +5\r"},

{{sinDS1,0,0,0,0,0,0,0},
{0,0,0,5,0,0,0,0,0},
{SIN_ADD_FIRE,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"âŒëÆê´ +5\r"},

{{sinDS1,0,0,0,0,0,0,0},
{0,0,0,0,5,0,0,0,0},
{SIN_ADD_LIGHTNING,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"óãëÆê´ +5\r"},

{{sinDS1,0,0,0,0,0,0,0},
{0,0,0,0,0,1,0,0,0},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{10,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ñhå‰óÕ +10\r"},

{{sinDS1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,0,0},
{SIN_ADD_BLOCK_RATE,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ÉuÉçÉbÉNó¶ +1\r"},

{{sinDS1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0},
{SIN_ADD_LIFE,0,0,0,0,0,0,0},
{10,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ê∂ñΩóÕ +10\r"},

{{sinDS1,0,0,0,0,0,0,0},
{2,0,1,0,0,0,0,0,0},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{10,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ñhå‰óÕ +10\r"},

{{sinDS1,0,0,0,0,0,0,0},
{0,2,2,1,0,0,0,0,0},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{10,0,0,0,0,0,0,0},
{SIN_ADD_PERCENT,0,0,0,0,0,0,0},
"ñhå‰óÕ +10%\r"},

{{sinDS1,0,0,0,0,0,0,0},
{0,3,1,0,1,0,0,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0,0},
{15,0.3f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ñhå‰óÕ +15\rãzé˚óÕ +0.3\r"},

{{sinDS1,0,0,0,0,0,0,0},
{0,0,2,0,2,0,0,0,0},
{SIN_ADD_ABSORB,0,0,0,0,0,0,0},
{0.3f,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ãzé˚óÕ +0.3\r"},

{{sinDS1,0,0,0,0,0,0,0},
{0,1,0,0,1,2,0,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0,0},
{10,0.6f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ñhå‰óÕ +10\rãzé˚óÕ +0.6\r"},

{{sinDS1,0,0,0,0,0,0,0},
{0,2,2,2,1,1,0,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0,0},
{20,0.3f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ñhå‰óÕ +20\rãzé˚óÕ +0.3\r"},

{{sinDS1,0,0,0,0,0,0,0},
{0,0,1,0,4,0,1,0,0},
{SIN_ADD_ABSORB,SIN_ADD_BLOCK_RATE,0,0,0,0,0,0},
{0.6f,4,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ãzé˚óÕ +0.6\rÉuÉçÉbÉNó¶ +4%\r"},

{{sinDS1,0,0,0,0,0,0,0},
{0,0,5,0,0,5,1,0,0},
{SIN_ADD_BLOCK_RATE,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ÉuÉçÉbÉNó¶ +5%\r"},

{{sinDS1,0,0,0,0,0,0,0},
{0,4,4,0,0,0,1,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_BLOCK_RATE,0,0,0,0,0,0},
{40,2,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ñhå‰óÕ +40\rÉuÉçÉbÉNó¶ +2%\r"},

{{sinDS1,0,0,0,0,0,0,0},
{0,2,1,1,0,1,2,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_BLOCK_RATE,0,0,0,0,0,0},
{20,4,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ñhå‰óÕ +20\rÉuÉçÉbÉNó¶ +4%\r"},

{{sinDS1,0,0,0,0,0,0,0},
{4,1,0,0,0,1,0,1,0},
{SIN_ADD_DEFENCE,SIN_ADD_MANA,SIN_ADD_STAMINA,0,0,0,0,0},
{40,10,50,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"ñhå‰óÕ +40\rãCóÕ +10\rëÃóÕ +50\r"},

{{sinDS1,0,0,0,0,0,0,0},
{0,0,0,0,0,3,1,2,0},
{SIN_ADD_BLOCK_RATE,SIN_ADD_LIFE,0,0,0,0,0,0},
{3,20,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ÉuÉçÉbÉNó¶ +3%\rê∂ñΩóÕ +20\r"},

{{sinDS1,0,0,0,0,0,0,0},
{0,0,0,0,5,0,0,2,0},
{SIN_ADD_ABSORB,SIN_ADD_MANA,0,0,0,0,0,0},
{1.0f,20,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ãzé˚óÕ +1.0\rãCóÕ +20\r"},

{{sinDS1,0,0,0,0,0,0,0},
{0,0,0,0,3,1,0,2,0},
{SIN_ADD_ABSORB,SIN_ADD_LIFE,0,0,0,0,0,0},
{0.6f,40,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ãzé˚óÕ +0.6\rê∂ñΩóÕ +40\r"},

{{sinDS1,0,0,0,0,0,0,0},
{2,2,2,2,2,2,0,0,0},
{SIN_ADD_BIO,SIN_ADD_POISON,SIN_ADD_LIGHTNING,SIN_ADD_FIRE,SIN_ADD_ICE,0,0,0},
{5,5,5,5,5,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0},
"ê∂ëÆê´ +5\rì≈ëÆê´ +5\rïXëÆê´ +5\râŒëÆê´ +5\róãëÆê´ +5\r"},




{{sinDS1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1},
{SIN_ADD_LIFE,0,0,0,0,0,0,0},
{40,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ê∂ñΩóÕ +40\r"},

{{sinDS1,0,0,0,0,0,0,0},
{0,0,0,1,3,0,2,0,3},
{SIN_ADD_DEFENCE,SIN_ADD_MANA,SIN_ADD_STAMINA,0,0,0,0,0},
{50,20,60,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"ñhå‰óÕ +50\rãCóÕ +20\rëÃóÕ +60\r"},

{{sinDS1,0,0,0,0,0,0,0},
{0,0,0,0,2,3,3,0,2},
{SIN_ADD_BLOCK_RATE,SIN_ADD_LIFE,0,0,0,0,0,0},
{4,30,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ÉuÉçÉbÉNó¶ +4%\rê∂ñΩóÕ +30\r"},

{{sinDS1,0,0,0,0,0,0,0},
{0,0,0,0,0,3,1,2,2},
{SIN_ADD_ABSORB,SIN_ADD_MANA,0,0,0,0,0,0},
{2.0f,30,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ãzé˚óÕ +2.0\rãCóÕ +30\r"},


{{sinDS1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,3,2,3},
{SIN_ADD_DEFENCE,SIN_ADD_BLOCK_RATE,0,0,0,0,0,0},
{60,5,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ñhå‰óÕ +60\rÉuÉçÉbÉNó¶ +5%\r"},

{{sinDS1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,5,5},
{SIN_ADD_ABSORB,SIN_ADD_LIFE,SIN_ADD_MANA,0,0,0,0,0},
{2.0f,20,20,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"ãzé˚óÕ +2.0\rê∂ñΩóÕ +20\rãCóÕ +20\r"},

{{sinDS1,0,0,0,0,0,0,0},
{0,0,0,0,0,2,2,2,5},
{SIN_ADD_BLOCK_RATE,SIN_ADD_LIFE,0,0,0,0,0,0},
{4,50,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ÉuÉçÉbÉNó¶ +4%\rê∂ñΩóÕ +50\r"},



{{sinOM1,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0,0},
{SIN_ADD_BIO,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ê∂ëÆê´ +5\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,5,0,0,0,0,0,0,0},
{SIN_ADD_POISON,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ì≈ëÆê´ +5\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,5,0,0,0,0,0,0},
{SIN_ADD_ICE,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ïXëÆê´ +5\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,0,5,0,0,0,0,0},
{SIN_ADD_FIRE,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"âŒëÆê´ +5\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,0,0,5,0,0,0,0},
{SIN_ADD_LIGHTNING,0,0,0,0,0,0,0},
{5,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"óãëÆê´ +5\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,0,0,0,1,0,0,0},
{SIN_ADD_MANAREGEN,0,0,0,0,0,0,0},
{0.3f,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ãCóÕçƒê∂ +0.3\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,0,0},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{10,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ñhå‰óÕ +10\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0},
{SIN_ADD_MANA,0,0,0,0,0,0,0},
{20,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ãCóÕ +20\r"},

{{sinOM1,0,0,0,0,0,0,0},
{2,0,1,0,0,0,0,0,0},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{10,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ñhå‰óÕ +10\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,2,2,1,0,0,0,0,0},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{10,0,0,0,0,0,0,0},
{SIN_ADD_PERCENT,0,0,0,0,0,0,0},
"ñhå‰óÕ +10%\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,3,1,0,2,0,0,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0,0},
{15,0.4f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ñhå‰óÕ +15\rãzé˚óÕ +0.4\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,4,0,4,0,0,0,0},
{SIN_ADD_ABSORB,0,0,0,0,0,0,0},
{0.8f,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ãzé˚óÕ +0.8\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,1,0,0,2,2,0,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_MANAREGEN,0,0,0,0,0,0},
{10,0.4f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ñhå‰óÕ +10\rãCóÕçƒê∂ +0.4\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,2,2,2,2,1,0,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_MANAREGEN,0,0,0,0,0,0},
{20,0.2f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ñhå‰óÕ +20\rãCóÕçƒê∂ +0.2\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,1,0,4,0,1,0,0},
{SIN_ADD_DEFENCE,0,0,0,0,0,0,0},
{40,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ñhå‰óÕ +40\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,3,0,0,3,1,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_MANAREGEN,0,0,0,0,0,0},
{10,0.6f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ñhå‰óÕ +10\rãCóÕçƒê∂ +0.6\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,5,5,0,0,0,1,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_ABSORB,0,0,0,0,0,0},
{50,1.0f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ñhå‰óÕ +50\rãzé˚óÕ +1.0\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,2,1,1,0,1,2,0,0},
{SIN_ADD_DEFENCE,SIN_ADD_MANAREGEN,0,0,0,0,0,0},
{40,0.4f,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ñhå‰óÕ +40\rãCóÕçƒê∂ +0.4\r"},

{{sinOM1,0,0,0,0,0,0,0},
{5,1,0,0,0,2,0,2,0},
{SIN_ADD_MANAREGEN,SIN_ADD_MANA,0,0,0,0,0,0},
{0.5f,40,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ãCóÕçƒê∂ +0.5\rãCóÕ +40\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,0,0,0,2,1,2,0},
{SIN_ADD_DEFENCE,SIN_ADD_MANAREGEN,SIN_ADD_STAMINA,0,0,0,0,0},
{10,0.4f,40,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"ñhå‰óÕ +10\rãCóÕçƒê∂ +0.4\rëÃóÕ +40\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,0,2,5,0,0,2,0},
{SIN_ADD_MANA,SIN_ADD_STAMINA,0,0,0,0,0,0},
{50,50,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ãCóÕ +50\rëÃóÕ +50\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,0,0,5,2,0,2,0},
{SIN_ADD_ABSORB,SIN_ADD_MANAREGEN,SIN_ADD_LIFE,0,0,0,0,0},
{1.0f,0.6f,20,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"ãzé˚óÕ +1.0\rãCóÕçƒê∂ +0.6\rê∂ñΩóÕ +20\r"},

{{sinOM1,0,0,0,0,0,0,0},
{2,2,2,2,2,2,0,0,0},
{SIN_ADD_BIO,SIN_ADD_POISON,SIN_ADD_ICE,SIN_ADD_FIRE,SIN_ADD_LIGHTNING,0,0,0},
{5,5,5,5,5,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0},
"ê∂ëÆê´ +5\rì≈ëÆê´ +5\rïXëÆê´ +5\râŒëÆê´ +5\róãëÆê´ +5\r"},




{{sinOM1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1},
{SIN_ADD_MANA,0,0,0,0,0,0,0},
{30,0,0,0,0,0,0,0},
{SIN_ADD_NUM,0,0,0,0,0,0,0},
"ãCóÕ +30\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,0,2,0,0,3,2,2},
{SIN_ADD_DEFENCE,SIN_ADD_MANAREGEN,SIN_ADD_STAMINA,0,0,0,0,0},
{20,0.8f,50,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"ñhå‰óÕ +20\rãCóÕçƒê∂ +0.8\rëÃóÕ +50\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,0,0,1,1,2,2,3},
{SIN_ADD_MANA,SIN_ADD_STAMINA,0,0,0,0,0,0},
{60,50,0,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0,0},
"ãCóÕ +60\rëÃóÕ +50\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,0,0,2,0,0,3,3},
{SIN_ADD_ABSORB,SIN_ADD_MANAREGEN,SIN_ADD_LIFE,0,0,0,0,0},
{1.5f,1.0f,30,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"ãzé˚óÕ +1.5\rãCóÕçƒê∂ +1.0\rê∂ñΩóÕ +30\r"},


{{sinOM1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,2,2,4},
{SIN_ADD_DEFENCE,SIN_ADD_MANAREGEN,SIN_ADD_STAMINA,0,0,0,0,0},
{30,1.0f,50,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"ñhå‰óÕ +30\rãCóÕçƒê∂ +1.0\rëÃóÕ +50\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,5,5},
{SIN_ADD_ABSORB,SIN_ADD_MANAREGEN,SIN_ADD_LIFE,0,0,0,0,0},
{2.0f,1.2f,30,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"ãzé˚óÕ +2.0\rãCóÕçƒê∂ +1.2\rê∂ñΩóÕ +30\r"},

{{sinOM1,0,0,0,0,0,0,0},
{0,0,0,0,0,1,5,1,5},
{SIN_ADD_DEFENCE,SIN_ADD_MANAREGEN,SIN_ADD_MANA,0,0,0,0,0},
{20,1.2f,60,0,0,0,0,0},
{SIN_ADD_NUM,SIN_ADD_NUM,SIN_ADD_NUM,0,0,0,0,0},
"ñhå‰óÕ +20\rãCóÕçƒê∂ +1.2\rãCóÕ +60\r"},
